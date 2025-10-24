/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "core.h"
#include "fcslog.h"
#include "fcserr.h"
#include "authenticate.h"
#include <openssl/evp.h>
#include "sake_root.h"
#include "string.h"
#include <openssl/x509.h>
#include "sake_engine_internal.h"
#include "convert.h"
#include <ks.h>
#include <ks_util.h>
#include "rule_types.h"
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/bn.h>
#include <stdlib.h>
#include "ta_interface.h"
#include "sake_nonce.h"
#include "auth_ch.h"

#define PUBKEY_EXP_SIZE 3
#define SAKE_ROOT_NAME_OFFS 2
#define SAKE_ROOT_NAME_LEN 2

struct authenticate_ctx {
	struct sake_setup *root;
	uint16_t ssn;
	uint8_t nonce[SAKE_NONCE_LEN];
	char *rev_str;
};

enum item_array_type {
	ITEM_ARRAY_EXPONENT = 1,
	ITEM_ARRAY_MODULUS
};

struct item_array {
	uint32_t length;
	uint8_t *data;
};

struct authenticate_internal_handle {
	sake_handle_t sake_handle;
	char *imei;
	char *die_id;
	uint8_t rand_buf[255];
	size_t rand_buf_len;
	char *rev_str;
	uint16_t ssn;
};

#define ASN1_TYPE_INTEGER	(0x02)
#define ASN1_SEQUENCE		(0x30)
#define ASN1_LEN_MASK		(0x80)
#define ASN1_LEN_ONE_BYTE	(0x81)
#define ASN1_LEN_TWO_BYTES	(0x82)
#define ASN1_HEADER_OFFS	(0x09)

/*
 * Parses the length from an ASN.1 blob. For now, only length in the following
 * formats
 * are supported:
 *
 * -------------------------------------------
 *     [ IDX ][idx+1][idx+2]
 * -------------------------------------------
 *     [<H7F ]
 * -------------------------------------------
 *     [ H81 ][ Hxx ]
 * -------------------------------------------
 *     [ H82 ][HMBxx][HLBxx]
 * -------------------------------------------
 */
static int asn1_get_length(const uint8_t *asn1, uint32_t *idx, uint32_t *length)
{
	if (!asn1 || !idx || !length) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	if (asn1[*idx] & ASN1_LEN_MASK) {
		switch (asn1[*idx]) {
		case ASN1_LEN_ONE_BYTE:
			*length = asn1[*idx+1];
			*idx += 2;
			break;

		case ASN1_LEN_TWO_BYTES:
			*length = (asn1[*idx+1] << 8) + asn1[*idx+2];
			*idx += 3;
			break;

		default:
			return -FCSERR_EINVAL;
		}
	} else {
		*length = asn1[*idx];
		(*idx)++;
	}

	return FCSERR_OK;
}

static int extract_public_key_parts(asn_rsa_public_key_t asn1,
				    struct item_array *item,
				    enum item_array_type iat)
{
	uint32_t idx = 0;
	uint32_t length_total, length_modulus, length_exponent;
	uint8_t *modulus = NULL;
	uint8_t *exponent = NULL;
	int status = FCSERR_OK;

	if ((!asn1) || (!item))
		return -FCSERR_EINVAL;


	/* ASN.1 - START-TAG */
	if (asn1[idx] != ASN1_SEQUENCE)
		return -FCSERR_EINVAL;

	idx++;
	/* ASN.1 - TOTAL LENGTH */
	status = asn1_get_length(asn1, &idx, &length_total);
	if (status != FCSERR_OK)
		return status;

	/* ASN.1 - LENGTH MODULUS */
	if (asn1[idx] != ASN1_TYPE_INTEGER)
		return -FCSERR_EINVAL;

	idx++;
	status = asn1_get_length(asn1, &idx, &length_modulus);
	if (status != FCSERR_OK)
		return status;

	/* ASN.1 - KEYDATA - MODULUS */
	modulus = &asn1[idx];
	idx += length_modulus;

	/* ASN.1 - LENGTH EXPONENT */
	if (asn1[idx] != ASN1_TYPE_INTEGER)
		return -FCSERR_EINVAL;

	idx++;
	status = asn1_get_length(asn1, &idx, &length_exponent);
	if (status != FCSERR_OK)
		return status;

	/* ASN.1 - KEYDATA - EXPONENT */
	exponent = &asn1[idx];
	idx += length_exponent;

	switch (iat) {
	case ITEM_ARRAY_EXPONENT:
		item->data = exponent;
		item->length = length_exponent;
		break;
	case ITEM_ARRAY_MODULUS:
		item->data = modulus;
		item->length = length_modulus;
		break;

	default:
		status = -FCSERR_EINVAL;
		break;
	}

	return status;
}

static int rsa_encrypt_nopad(const uint8_t *in_buffer_p,
			     size_t in_buffer_size,
			     uint8_t *out_buffer_p,
			     size_t out_buffer_size,
			     const asn_rsa_public_key_t public_key)
{
	int res = FCSERR_OK;
	struct item_array item_m, item_e;

	if (in_buffer_size != out_buffer_size)
		return -FCSERR_EINVAL;

	RSA *pubkey = RSA_new();
	BIGNUM *modul = BN_new();
	BIGNUM *expon = BN_new();

	res = extract_public_key_parts(public_key, &item_m,
				       ITEM_ARRAY_MODULUS);
	if (res != FCSERR_OK)
		goto error;

	res = extract_public_key_parts(public_key, &item_e,
				       ITEM_ARRAY_EXPONENT);
	if (res != FCSERR_OK)
		goto error;

	BN_bin2bn(item_m.data, item_m.length, modul);
	BN_bin2bn(item_e.data, item_e.length, expon);

	pubkey->n = modul;
	pubkey->e = expon;
	modul = NULL;
	expon = NULL;

	res = RSA_public_encrypt(in_buffer_size, in_buffer_p, out_buffer_p,
				 pubkey, RSA_NO_PADDING);

	if (res < 0)
		res = -FCSERR_ENIMP;
	else
		res = FCSERR_OK;

error:
	RSA_free(pubkey);
	BN_free(modul);
	BN_free(expon);
	return res;
}

static int hash_init(hash_context_t *context, hash_type_t hash_type)
{
	int res = FCSERR_OK;
	EVP_MD_CTX *mdctx;

	if (context == NULL) {
		FCS_LOG_ERR("Invalid pointer\n");
		return -FCSERR_EINVAL;
	}

	if (hash_type != SHA256_HASH) {
		FCS_LOG_ERR("Unsupporter algorithm\n");
		return -FCSERR_ENIMP;
	}

	mdctx = EVP_MD_CTX_create();
	if (mdctx == NULL) {
		FCS_LOG_ERR("Failed to create digest ctx.\n");
		res = -FCSERR_ENOMEM;
		goto error;
	}

	if (EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) != 1) {
		FCS_LOG_ERR("Failed to init digest ctx.\n");
		res = -FCSERR_EHCLC;
	}
	*context = (hash_context_t)mdctx;
error:
	return res;
}

static int hash_update(hash_context_t context, const uint8_t *data,
		       size_t length)
{
	int res = FCSERR_OK;
	EVP_MD_CTX *mdctx = (EVP_MD_CTX *)context;

	if (mdctx == NULL || data == NULL) {
		FCS_LOG_ERR("Invalid pointer\n");
		return -FCSERR_EINVAL;
	}

	if (EVP_DigestUpdate(mdctx, data, length) != 1) {
		FCS_LOG_ERR("Failed to update digest.\n");
		res = -FCSERR_EHCLC;
	}

	return res;
}

static int hash_final(hash_context_t context, uint8_t *digest,
		      size_t digest_size)
{
	EVP_MD_CTX *mdctx = (EVP_MD_CTX *)context;
	unsigned int digest_len;

	if (context == NULL || digest == NULL) {
		FCS_LOG_ERR("Invalid pointer\n");
		return -FCSERR_EINVAL;
	}

	if (EVP_DigestFinal_ex(mdctx, digest, &digest_len) != 1) {
		FCS_LOG_ERR("Failed to update digest.\n");
		return -FCSERR_EHCLC;
	}

	if (digest_len != digest_size) {
		FCS_LOG_ERR("Uncorrect digest size.\n");
		return -FCSERR_EHCLC;
	}

	return FCSERR_OK;
}

static int hash_deinit(hash_context_t context)
{
	if (context != NULL) {
		EVP_MD_CTX_destroy(context);
		context = NULL;
	}
	return FCSERR_OK;
}

static int hash_get_hash_size(hash_context_t context, size_t *size_p)
{
	if (context == NULL || size_p == NULL) {
		FCS_LOG_ERR("Invalid pointer\n");
		return -FCSERR_EINVAL;
	}

	*size_p = HASH_SIZE;
	return FCSERR_OK;
}

static char *bin2ascii(const uint8_t *buf, size_t sz)
{
	const char digits[] = "0123456789abcdef";
	char *tmp;
	uint32_t i;
	unsigned char lo, hi;

	if (buf == NULL) {
		FCS_LOG_ERR("Invalid pointer\n");
		return NULL;
	}

	tmp = malloc(2*sz + 1);
	if (tmp == NULL) {
		FCS_LOG_ERR("Malloc devid failed\n");
		return NULL;
	}

	for (i = 0; i < (2*sz - 1); i += 2) {
		hi = (buf[i>>1] & 0xF0) >> 4;
		lo = (buf[i>>1] & 0x0F) >> 0;

		tmp[i]   = (uint8_t)digits[hi];
		tmp[i+1] = (uint8_t)digits[lo];
	}

	tmp[i] = '\0';
	return tmp;
}

static int internal_init(struct authenticate_internal_handle **auth_hdl,
			     struct sake_ext_functions *sake_ext_funcs)
{
	int res = FCSERR_OK;
	size_t devid_len = 0;
	uint8_t *devid = NULL;

	if (auth_hdl == NULL || sake_ext_funcs == NULL) {
		FCS_LOG_ERR("Invalid pointer\n");
		return -FCSERR_EINVAL;
	}

	devid_len = core_get_dieid_len();
	devid = malloc(devid_len);
	if (devid == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		res = -FCSERR_ENOMEM;
		goto error;
	}

	res = core_get_dieid(devid, devid_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get dev id from env: (%d)\n", res);
		res = -FCSERR_ESTATE;
		goto error;
	}

	*auth_hdl = (struct authenticate_internal_handle *)
		malloc(sizeof(struct authenticate_internal_handle));
	if (auth_hdl == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		return -FCSERR_ENOMEM;
	}

	(*auth_hdl)->die_id = bin2ascii(devid, devid_len);
	sake_ext_funcs->hash_functions.hash_init = hash_init;
	sake_ext_funcs->hash_functions.hash_update = hash_update;
	sake_ext_funcs->hash_functions.hash_final = hash_final;
	sake_ext_funcs->hash_functions.hash_deinit = hash_deinit;
	sake_ext_funcs->hash_functions.hash_get_hash_size = hash_get_hash_size;
	sake_ext_funcs->rsa_functions.encrypt_no_pad = rsa_encrypt_nopad;

	res = sake_get_nonce((*auth_hdl)->rand_buf, SAKE_NONCE_LEN);

	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get nonce\n");
		goto error;
	}
	(*auth_hdl)->rand_buf_len = SAKE_NONCE_LEN;
	(*auth_hdl)->imei = NULL;

error:
	free(devid);
	return res;
}

static int internal_deinit(struct authenticate_internal_handle *auth_hdl)
{
	if (auth_hdl != NULL) {
		free(auth_hdl->die_id);
		free(auth_hdl);
	}

	return FCSERR_OK;
}

static int get_sake_key_from_keystore(struct ks_ctx *keystore_ctx,
				      struct ksstore_blob *ksblob)
{
	int res = FCSERR_OK;
	uint32_t nkeys;

	if (keystore_ctx == NULL || ksblob == NULL)
		return -FCSERR_EINVAL;

	res = ks_get_nof_keys(keystore_ctx, KEYSTORE_DOMAIN_SAKE, &nkeys);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("ks_get_nof_keys failed\n");
		return res;
	}

	/* It can only be 0 or 1 SAKE certificate in keystore */
	if (nkeys == 1) {
		res = ks_get_key_by_index(keystore_ctx, KEYSTORE_DOMAIN_SAKE,
					   nkeys-1, ksblob);
	} else {
		res = -FCSERR_ESTATE;
	}

	return res;
}

/* Digest is generated with sha1 on RSA public key in PEM format */
static int calc_pubkey_digest(struct ksstore_blob *ksblob, char *buf,
			     size_t buf_len, size_t *root_name_len)
{
	int res = FCSERR_OK;
	X509 *cert = NULL;
	EVP_PKEY *pubkey = NULL;
	EVP_MD_CTX *mdctx = NULL;
	BUF_MEM *bufmem = NULL;
	unsigned int digest_len;
	uint8_t *digest = NULL;
	BIO *mem = NULL;

	if (ksblob == NULL || buf == NULL)
		return -FCSERR_EINVAL;

	cert = d2i_X509(NULL, (const unsigned char **)&(ksblob->blob),
			ksblob->size);
	if (!cert) {
		FCS_LOG_ERR("d2i_X509 failed\n");
		return -FCSERR_ESTATE;
	}

	pubkey = X509_get_pubkey(cert);
	if (pubkey == NULL) {
		FCS_LOG_ERR("X509_get_pubkey failed\n");
		res = -FCSERR_ESTATE;
		goto error;
	}

	mem = BIO_new(BIO_s_mem());
	if (mem == NULL) {
		res = -FCSERR_ENOMEM;
		goto error;
	}

	if (!PEM_write_bio_PUBKEY(mem, pubkey)) {
		FCS_LOG_ERR("PEM_write_bio_PUBKEY failed\n");
		res = -FCSERR_ESTATE;
		goto error;
	}

	BIO_get_mem_ptr(mem, &bufmem);

	mdctx = EVP_MD_CTX_create();
	if (mdctx == NULL) {
		FCS_LOG_ERR("Failed to create digest ctx.\n");
		res = -FCSERR_ENOMEM;
		goto error;
	}

	digest_len = EVP_MD_size(EVP_sha1());
	digest = malloc(digest_len);
	if (digest == NULL) {
		FCS_LOG_ERR("Memory allocation failed!\n");
		res = -FCSERR_ENOMEM;
		goto error;
	}

	res = -FCSERR_EHCLC;
	if (EVP_DigestInit_ex(mdctx, EVP_sha1(), NULL) != 1) {
		FCS_LOG_ERR("Failed to init digest ctx.\n");
		goto error;
	}

	if (EVP_DigestUpdate(mdctx, bufmem->data, bufmem->length) != 1) {
		FCS_LOG_ERR("Failed to update digest.\n");
		goto error;
	}

	if (EVP_DigestFinal_ex(mdctx, digest, &digest_len) != 1) {
		FCS_LOG_ERR("Failed to finalize digest.\n");
		goto error;
	}

	if (digest_len != (unsigned int)EVP_MD_size(EVP_sha1())) {
		FCS_LOG_ERR("Digest size error.\n");
		goto error;
	}

	*root_name_len = SAKE_ROOT_NAME_LEN;

	if (*root_name_len <= buf_len)
		memcpy(buf, digest, *root_name_len);
	else {
		res = -FCSERR_ENOBUFS;
		goto error;
	}

	res = FCSERR_OK;
error:
	free(digest);
	if (mem != NULL)
		BIO_free(mem);
	if (mdctx != NULL)
		EVP_MD_CTX_destroy(mdctx);
	if (cert != NULL)
		X509_free(cert);
	if (pubkey != NULL)
		EVP_PKEY_free(pubkey);

	return res;
}

static int get_sake_data(struct sake_setup **buf)
{
	int res = FCSERR_OK;
	struct ksstore_blob ksblob;
	size_t len;
	char digest[SAKE_ROOT_NAME_LEN];
	X509 *cert = NULL;
	EVP_PKEY *pubkey = NULL;
	RSA *rsa = NULL;
	struct ks_ctx *keystore_ctx = NULL;
	uint8_t *tmp_blob;
	size_t size = sizeof(struct sake_setup);
	uint8_t *hmac_key = NULL;
	uint32_t hmac_key_len = 0;
	int test_cert_allowed = 0;

	if (buf == NULL)
		return -FCSERR_EINVAL;

	test_cert_allowed = fcsenv_test_cert_allowed();

	*buf = malloc(size);
	if (*buf == NULL)
		return -FCSERR_ENOMEM;
	memset(*buf, 0, size);

	/* Set embedded SAKE data initially */
	if (test_cert_allowed != 1)
		memcpy(*buf, &sake_data_live, size);
	else
		memcpy(*buf, &sake_data_test, size);

	res = core_get_hmac_key(&hmac_key, &hmac_key_len);
	if (res != FCSERR_OK) {
		hmac_key = NULL;
		hmac_key_len = 0;
		FCS_LOG_INF("Can't get hmac key: (%d)\n", res);
	}

	res = ksutil_keystore_init(&keystore_ctx, true,
				   XFLKEYSTORE_PRIM, hmac_key, hmac_key_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("No valid keystore present\n");
		return FCSERR_OK;
	}

	res = get_sake_key_from_keystore(keystore_ctx, &ksblob);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get key. (%d)\n", res);
		res = FCSERR_OK;
		goto exit;
	}

	/* Save this pointer since OpenSSL d2i_X509() increments
	 * the pointer to the blob.
	 */
	tmp_blob = ksblob.blob;

	res = calc_pubkey_digest(&ksblob, digest, sizeof(digest),
				 &len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Get pubkey hash failed (%d)\n", res);
		res = FCSERR_OK;
		goto exit;
	}

	/* Restore keystore blob pointer */
	ksblob.blob = tmp_blob;
	cert = d2i_X509(NULL, (const unsigned char **)&ksblob.blob,
			ksblob.size);
	if (!cert) {
		FCS_LOG_ERR("d2i_X509 failed\n");
		goto exit;
	}

	pubkey = X509_get_pubkey(cert);
	if (pubkey == NULL) {
		FCS_LOG_ERR("X509_get_pubkey failed\n");
		goto exit;
	}

	rsa = EVP_PKEY_get1_RSA(pubkey);
	if (rsa == NULL) {
		FCS_LOG_ERR("EVP_PKEY_get1_RSA failed\n");
		goto exit;
	}

	/* Replace Modulus and exponent */
	BN_bn2bin(rsa->n, (*buf)->rsa_pub_key+ASN1_HEADER_OFFS);
	BN_bn2bin(rsa->e, (*buf)->rsa_pub_key+
		  sizeof((*buf)->rsa_pub_key)-PUBKEY_EXP_SIZE);

	/* replace public key hash */
	memcpy(&(*buf)->pub_hash[SAKE_ROOT_NAME_OFFS], digest, len);

exit:
	if (rsa != NULL)
		RSA_free(rsa);
	if (pubkey != NULL)
		EVP_PKEY_free(pubkey);
	if (cert != NULL)
		X509_free(cert);
	ks_destroy(keystore_ctx);
	free(hmac_key);

	return res;
}

int authenticate_init(struct authenticate_ctx **ctx, uint16_t sake_ssn,
		      const char *rev_str, size_t rev_str_len)
{
	int res = FCSERR_OK;

	if (ctx == NULL || rev_str == NULL)
		return -FCSERR_EINVAL;

	*ctx = malloc(sizeof(struct authenticate_ctx));
	if (*ctx == NULL)
		return -FCSERR_ENOMEM;
	(*ctx)->rev_str = malloc(rev_str_len + 1);
	if ((*ctx)->rev_str == NULL)
		return -FCSERR_ENOMEM;

	memcpy((*ctx)->rev_str, rev_str, rev_str_len);
	(*ctx)->rev_str[rev_str_len] = '\0';
	(*ctx)->root = NULL;
	(*ctx)->ssn = sake_ssn;
	return res;
}

void authenticate_destroy(struct authenticate_ctx *ctx)
{
	if (ctx != NULL) {
		free(ctx->root);
		free(ctx->rev_str);
	}
	free(ctx);
}

int authenticate_generate_challenge(struct authenticate_ctx **ctx,
				    uint8_t *challenge_buf,
				    size_t *challenge_len)
{
	int res = FCSERR_OK;
	struct authenticate_internal_handle *hdl = NULL;
	struct sake_ext_functions sake_ext_funcs = {};
	size_t hello_msg_len;

	/* At this moment, *challenge_len shall be the size of the buffer */

	if (challenge_buf == NULL || challenge_len == NULL)
		return -FCSERR_EINVAL;

	res = get_sake_data(&(*ctx)->root);
	if (res != FCSERR_OK)
		return res;

	res = internal_init(&hdl, &sake_ext_funcs);
	if (res != FCSERR_OK)
		goto error;

	res = sake_init(&hdl->sake_handle, (*ctx)->root->pub_hash,
			(*ctx)->root->rsa_pub_key, (*ctx)->root->crl,
			sake_ext_funcs);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to initialize SAKE (%d)\n", res);
		res = -FCSERR_ESTATE;
		goto error;
	}

	res = sake_compose_hello_message(hdl->sake_handle, &hello_msg_len,
					 hdl->rand_buf, hdl->rand_buf_len,
					 hdl->imei, hdl->die_id,
					 (*ctx)->rev_str, (*ctx)->ssn);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to compose sake_hello\n");
		res = -FCSERR_ESTATE;
		goto error;
	}

	if (hello_msg_len > *challenge_len) {
		FCS_LOG_ERR("The challenge buffer is too small\n");
		res = -FCSERR_ENOBUFS;
		goto error;
	}

	/* From now on, *challenge_len will be the length of the message */
	*challenge_len = hello_msg_len;

	res = sake_get_hello_message(hdl->sake_handle, challenge_buf,
			       *challenge_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get sake_hello\n");
		res = -FCSERR_ESTATE;
		goto error;
	}
error:
	internal_deinit(hdl);
	return res;
}

int authenticate_verify_response(struct authenticate_ctx **ctx,
				 uint8_t *response_buf,
				 ssize_t response_buf_len)
{
	int res = FCSERR_OK;
	size_t hello_msg_len = 0;
	struct authenticate_internal_handle *hdl = NULL;
	struct sake_ext_functions sake_ext_funcs = {};
	struct auth_ch_cmd ch_cmd = {};
	struct auth_ch_auth ch_auth = {};
	uint8_t *sake_hello = NULL;
	size_t auth_ch_buf_len = 0;
	uint8_t *auth_ch_buf = NULL, *p = NULL;

	if (response_buf == NULL)
		return -FCSERR_EINVAL;

	res = get_sake_data(&(*ctx)->root);
	if (res != FCSERR_OK)
		return res;

	res = internal_init(&hdl, &sake_ext_funcs);
	if (hdl == NULL || res != FCSERR_OK)
		goto error;

	res = sake_init(&hdl->sake_handle, (*ctx)->root->pub_hash,
			(*ctx)->root->rsa_pub_key, (*ctx)->root->crl,
			sake_ext_funcs);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("sake_init failed\n");
		goto error;
	}

	res = sake_compose_hello_message(hdl->sake_handle, &hello_msg_len,
					 hdl->rand_buf, hdl->rand_buf_len,
					 hdl->imei, hdl->die_id,
					 (*ctx)->rev_str, (*ctx)->ssn);
	if (res != FCSERR_OK || hello_msg_len == 0) {
		FCS_LOG_ERR("sake_compose_hello_message failed\n");
		goto error;
	}

	sake_hello = malloc(hello_msg_len);
	if (sake_hello == NULL) {
		res = -FCSERR_ENOMEM;
		goto error;
	}

	res = sake_get_hello_message(hdl->sake_handle, sake_hello,
				     hello_msg_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("get hello failed\n");
		goto error;
	}

	res = sake_check_response_message(hdl->sake_handle, response_buf,
					  response_buf_len);
	if  (res != FCSERR_OK) {
		FCS_LOG_ERR("sake_check_response failed\n");
		goto error;
	}

	auth_ch_buf_len = sizeof(struct auth_ch_cmd) +
		sizeof(struct auth_ch_auth) +
		(int)strlen((*ctx)->rev_str) + 1 + response_buf_len;

	auth_ch_buf = malloc(auth_ch_buf_len);
	if (auth_ch_buf == NULL) {
		res = -FCSERR_ENOMEM;
		goto error;
	}

	p = auth_ch_buf;
	ch_cmd.magic = 0;
	ch_cmd.version = AUTH_CH_VERSION;
	ch_cmd.id = AUTH_CH_SAKE_AUTH;
	ch_cmd.sz = sizeof(struct auth_ch_auth) + strlen((*ctx)->rev_str) + 1 +
		response_buf_len;

	ch_auth.ssn = (*ctx)->ssn;
	ch_auth.rev_str_sz = strlen((*ctx)->rev_str) + 1;
	ch_auth.response_sz = response_buf_len;

	memcpy(p, &ch_cmd, sizeof(struct auth_ch_cmd));
	p += sizeof(struct auth_ch_cmd);
	memcpy(p, &ch_auth, sizeof(struct auth_ch_auth));
	p += sizeof(struct auth_ch_auth);

	memcpy(p, (*ctx)->rev_str, ch_auth.rev_str_sz);
	p += ch_auth.rev_str_sz;
	memcpy(p, response_buf, response_buf_len);

	res = write_ta(TA_MISC_PART, TA_AUTH_CH, auth_ch_buf, auth_ch_buf_len);
	if (res != FCSERR_OK)
		FCS_LOG_ERR("Write to TA failed %d\n", res);
error:
	free(sake_hello);
	internal_deinit(hdl);
	return res;
}

int authenticate_get_sake_root_name(struct authenticate_ctx **ctx,
				    char *buf, size_t buf_len)
{
	int res = FCSERR_OK;
	size_t digest_len = 0;
	uint8_t *digest = NULL;
	struct ks_ctx *keystore_ctx = NULL;
	struct ksstore_blob ksblob;
	uint8_t *hmac_key = NULL;
	uint32_t hmac_key_len = 0;

	if (!ctx || !(*ctx) || !buf) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	res = core_get_hmac_key(&hmac_key, &hmac_key_len);
	if (res != FCSERR_OK) {
		hmac_key = NULL;
		hmac_key_len = 0;
		FCS_LOG_INF("Can't get hmac key: (%d)\n", res);
	}

	res = ksutil_keystore_init(&keystore_ctx, true, XFLKEYSTORE_PRIM,
			hmac_key, hmac_key_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("ksutil_keystore_init failed %d\n", res);
		goto exit;
	}

	res = get_sake_key_from_keystore(keystore_ctx, &ksblob);
	if (res != FCSERR_OK)
		goto exit;

	/* Calculate digest for keystore pubkey */
	res = calc_pubkey_digest(&ksblob, buf, buf_len, &digest_len);
	if (res == FCSERR_OK) {
		digest = malloc(digest_len);
		if (digest == NULL)
			goto exit;

		memcpy(digest, buf, digest_len);
		res = bin_to_ascii(buf, buf_len, digest, digest_len);
		if (res != FCSERR_OK)
			FCS_LOG_ERR("bin_to_ascii failed %d\n", res);
		free(digest);
		ks_destroy(keystore_ctx);
		free(hmac_key);
		return res;
	}
exit:
	ks_destroy(keystore_ctx);
	free(hmac_key);

	/* Get embedded rsa pubkey data if keystore fails */
	res = get_sake_data(&(*ctx)->root);
	if (res != FCSERR_OK)
		return res;

	res = bin_to_ascii(buf, buf_len,
		&((*ctx)->root->pub_hash[SAKE_ROOT_NAME_OFFS]),
		SAKE_ROOT_NAME_LEN);
	if (res != FCSERR_OK)
		FCS_LOG_ERR("bin_to_ascii failed %d\n", res);

	return res;
}

int authenticate_get_level(struct authenticate_ctx *ctx,
			   uint8_t *auth_level)
{
	if (ctx == NULL || auth_level == NULL)
		return -FCSERR_EINVAL;

	if (ctx->ssn == SAKE_SSN_PRODUCTION)
		*auth_level = AUTH_LEVEL_PRODUCTION;
	else if (ctx->ssn == SAKE_SSN_CUSTOMER_SERVICE)
		*auth_level = AUTH_LEVEL_CUSTOMER_SERVICE;
	else
		*auth_level = AUTH_LEVEL_NONE;
	return FCSERR_OK;
}
