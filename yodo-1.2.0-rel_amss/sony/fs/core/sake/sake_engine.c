/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "sake_engine.h"
#include "sake_engine_internal.h"
#include "sake_alg.h"
#include "sake_cert.h"
#include "string.h"
#include "stdlib.h"
#include "fcserr.h"
#include "fcslog.h"

#define HELLO_MESSAGE_MIN_SIZE     38
#define SAKE_VERSION               0x200
#define MIN_CHALLENGE_LEN          20
#define RESPONSE_MESSAGE_MIN_SIZE  27
#define HELLO_MSG_DEFAULT_LENGTH   512

/* Defines used to sanity check RSA signature length */
#define RSA_SIGN_MAX_LEN           512
#define RSA_SIGN_MIN_LEN           128

static uint_fast16_t get_big_ushort(const uint8_t *adr, const uint8_t *endAdr);
static size_t put_big_ushort(uint8_t *adr, uint_fast16_t a);
static size_t sake_str_len(const char *str);
static size_t put_tag(uint8_t *dst, const char *tagName, const char *tagData,
		      size_t tagNbr);

/*
 * Parse the next asn1 tag in the stream. Input has to start with ASN.1
 * sequence (0x82) tag or integer (0x02)
 *
 * @param[in,out] asn_stream          ASN.1 stream to decode
 *
 * @return the length of the payload on success, 0 if not expected input
 */
static size_t get_asn1_length(uint8_t **asn_stream);

static int parse_asn1_rsa_key_and_hash(asn_rsa_public_key_t rsa_pub_key,
				       uint8_t *pub_hash,
				       struct PublicKey *public_key);

static int parse_asn1_crl(struct sake_internal_handle *sake_handle,
			  uint8_t *crl);

int sake_init(sake_handle_t *handle,
	      uint8_t *pub_hash,
	      asn_rsa_public_key_t rsa_pub_key,
	      uint8_t *crl,
	      struct sake_ext_functions ext_functions)
{
	int result = FCSERR_OK;
	struct sake_internal_handle *sake_handle = NULL;

	do {
		/* input param verification */
		if ((!handle) || (!pub_hash) || (!crl) ||
		   !((uint8_t *)rsa_pub_key)) {
			FCS_LOG_ERR("Invalid argument\n");
			result = -FCSERR_EINVAL;
			break;
		}

		sake_handle = (struct sake_internal_handle *)
			malloc(sizeof(struct sake_internal_handle));
		if (!sake_handle) {
			result = -FCSERR_ENOMEM;
			break;
		}

		memset(sake_handle, 0, sizeof(struct sake_internal_handle));

		sake_handle->savedHelloMsg = NULL;
		sake_handle->savedHelloLen = 0;
		sake_handle->savedSsn = DEFAULT_SSN;

		sake_handle->hash_type = HASH_TYPE_INTERNAL;
		sake_handle->hash_digest_size = HASH_SIZE;

		result = parse_asn1_rsa_key_and_hash(rsa_pub_key,
						     pub_hash,
						     &sake_handle->public_key);
		if (result != FCSERR_OK)
			break;

		result = parse_asn1_crl(sake_handle, crl);
		if (result != FCSERR_OK)
			break;

		sake_handle->funcs = ext_functions;

		*handle = (sake_handle_t)sake_handle;
	} while (0);

	if (result != FCSERR_OK) {
		if (sake_handle) {
			if (sake_handle->cert_revocation_list)
				free(sake_handle->cert_revocation_list);

			if (sake_handle)
				free(sake_handle);

		}
	}

	return result;
}

int sake_deinit(sake_handle_t handle)
{
	if (handle) {
		struct sake_internal_handle *sake_handle =
			(struct sake_internal_handle *)handle;

		deinit_public_key(&sake_handle->public_key);

		if (sake_handle->savedHelloMsg) {
			free(sake_handle->savedHelloMsg);
			sake_handle->savedHelloMsg = 0;
		}
		if (sake_handle->cert_revocation_list) {
			free(sake_handle->cert_revocation_list);
			sake_handle->cert_revocation_list = 0;
		}
		free(handle);
	}
	return FCSERR_OK;
}

int sake_get_hello_message(sake_handle_t handle, uint8_t *hello_msg,
			   size_t hello_msg_len)
{
	int result = -FCSERR_ESTATE;
	struct sake_internal_handle *sake_handle =
		(struct sake_internal_handle *)handle;

	if (!sake_handle || !hello_msg) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	if (sake_handle->savedHelloMsg == NULL)
		goto failed;

	if (hello_msg_len < sake_handle->savedHelloLen)
		goto failed;

	memcpy(hello_msg, sake_handle->savedHelloMsg,
	       sake_handle->savedHelloLen);
	result = FCSERR_OK;

failed:
	return result;
}

size_t sake_get_hello_message_length(sake_handle_t handle)
{
	struct sake_internal_handle *sake_handle =
		(struct sake_internal_handle *)handle;
	size_t length = 0;

	if (sake_handle->savedHelloMsg == NULL)
		goto failed;

	if (sake_handle->savedHelloLen == 0)
		goto failed;

	length = sake_handle->savedHelloLen;

failed:
	return length;
}

int sake_compose_hello_message(sake_handle_t handle,
			       size_t *hello_msg_len,
			       const uint8_t *rand_buf,
			       size_t rand_buf_len,
			       const char *imei,
			       const char *dev_id,
			       const char *rev_str,
			       uint_fast16_t ssn)
{
	size_t offs = 0;
	size_t tagLen = 0;
	uint_fast32_t nofTags = 0;
	struct sake_internal_handle *sake_handle = NULL;
	int result = FCSERR_OK;
	uint8_t *hello_msg_int = NULL;

	do {
		/* in parameter check, since its a public interface */
		if ((!hello_msg_len) || (!rand_buf) || (!rev_str) ||
		    (!(void *)handle)) {
			FCS_LOG_ERR("Invalid argument\n");
			result = -FCSERR_EINVAL;
			break;
		}
		if (rand_buf_len < MIN_CHALLENGE_LEN) {
			result = -FCSERR_EINVAL;
			break;
		}
		sake_handle = (struct sake_internal_handle *)handle;

		if (sake_handle->savedHelloMsg) {
			free(sake_handle->savedHelloMsg);
			sake_handle->savedHelloMsg = 0;
		}

		hello_msg_int = (uint8_t *)malloc(HELLO_MSG_DEFAULT_LENGTH);
		if (!hello_msg_int) {
			result = -FCSERR_ENOMEM;
			break;
		}

		offs += put_big_ushort(&hello_msg_int[offs], SAKE_VERSION);

		hello_msg_int[offs++] = 1;                 /* algListLen */
		hello_msg_int[offs++] = HASH_ALG;           /* algList */

		offs += put_big_ushort(&hello_msg_int[offs], rand_buf_len);
		memcpy(&hello_msg_int[offs], rand_buf, rand_buf_len);
		offs += rand_buf_len;

		/* certIdListLen */
		offs += put_big_ushort(&hello_msg_int[offs], 26);
		/* certIdLen */
		offs += put_big_ushort(&hello_msg_int[offs], 24);

		hello_msg_int[offs++] = 254;               /* Identifier */
		/* keyHashLen + CRL version len */
		hello_msg_int[offs++] = PUB_HASH_LEN + 2;
		memcpy(&hello_msg_int[offs],
		       sake_handle->public_key.item_h.data, PUB_HASH_LEN);
		offs += PUB_HASH_LEN;
		/* CRL version */
		offs += put_big_ushort(&hello_msg_int[offs],
			sake_handle->cert_revocation_list_version);

		/* CID Tags */
		if (imei) {
			tagLen += 7 + sake_str_len(imei);
			nofTags++;
		}
		if (dev_id) {
			tagLen += 8 + sake_str_len(dev_id);
			nofTags++;
		}
		tagLen += 6 + sake_str_len(rev_str);
		nofTags++;

		tagLen += nofTags - 1; /* for the ; separator */
		if (offs + 2 + tagLen > HELLO_MSG_DEFAULT_LENGTH) {
			result = -FCSERR_ENOBUFS;
			break;
		}
		/* ClientIdLen */
		offs += put_big_ushort(&hello_msg_int[offs], tagLen);

		nofTags = 0;
		if (imei) {
			char imei_str[] = "IMEI";

			offs += put_tag(&hello_msg_int[offs], imei_str, imei,
					nofTags++);
		}
		if (dev_id) {
			char dev_id_str[] = "DEVID";

			offs += put_tag(&hello_msg_int[offs], dev_id_str,
					dev_id, nofTags++);
		}
		{
			char rev[] = "REV";

			offs += put_tag(&hello_msg_int[offs], rev, rev_str,
					nofTags++);
		}
		/* SSN */
		if ((offs + 2) > HELLO_MSG_DEFAULT_LENGTH) {
			result = -FCSERR_ENOBUFS;
			break;
		}
		offs += put_big_ushort(&hello_msg_int[offs], ssn);
		sake_handle->savedSsn = ssn;

		/* One last sanity check */
		if (offs < HELLO_MESSAGE_MIN_SIZE) {
			result = -FCSERR_ENOBUFS;
			break;
		}
		sake_handle->savedHelloMsg = (uint8_t *)malloc(offs);
		if (!sake_handle->savedHelloMsg) {
			result = -FCSERR_ENOMEM;
			break;
		}
		*hello_msg_len = offs;
		sake_handle->savedHelloLen = offs;
		memcpy(sake_handle->savedHelloMsg, hello_msg_int, offs);

	} while (0);

	if (hello_msg_int)
		free(hello_msg_int);

	return result;
}


int sake_check_response_message(sake_handle_t handle,
				const uint8_t *resp_msg,
				size_t resp_msg_len)
{
	uint8_t sigAlg;
	size_t certLen, nonceLen, sigLen, offs = 0, mainMsgLen, a;
	const uint8_t *cert, *nonce, *sig, *endAdr;
	uint8_t hashRes[HASH_SIZE];
	uint8_t *padded = NULL;
	uint8_t *rsaRes = NULL;
	struct CertificateData myCert = {};
	struct sake_internal_handle *sake_handle = NULL;
	int result = FCSERR_OK;
	hash_context_t context = 0;


	do {
		/* input parameter check */
		if ((!resp_msg) || (!(void *)handle)) {
			FCS_LOG_ERR("Invalid argument\n");
			result = -FCSERR_EINVAL;
			break;
		}
		if (resp_msg_len < RESPONSE_MESSAGE_MIN_SIZE) {
			result = -FCSERR_ENOBUFS;
			break;
		}

		sake_handle = (struct sake_internal_handle *)handle;
		memset(&myCert, 0, sizeof(myCert));
		if (!sake_handle->savedHelloMsg) {
			result = -FCSERR_ESTATE;
			break;
		}

		endAdr = resp_msg + resp_msg_len;

		sigAlg = resp_msg[offs++];
		if (sigAlg != HASH_ALG) {
			FCS_LOG_ERR("Incorrect signature alg %d\n", sigAlg);
			result = -FCSERR_EUNK;
			break;
		}

		certLen = get_big_ushort(&resp_msg[offs], endAdr);
		offs += 2;

		if (resp_msg_len < RESPONSE_MESSAGE_MIN_SIZE + certLen) {
			result = -FCSERR_ENOBUFS;
			break;
		}

		cert = &resp_msg[offs];
		offs += certLen;

		nonceLen = get_big_ushort(&resp_msg[offs], endAdr);
		offs += 2;
		if (nonceLen != 20) {
			result = -FCSERR_ESIZE;
			break;
		}

		nonce = &resp_msg[offs];
		(void)nonce;
		offs += nonceLen;
		mainMsgLen = offs;

		sigLen = get_big_ushort(&resp_msg[offs], endAdr);
		offs += 2;

		if (sigLen < RSA_SIGN_MIN_LEN || sigLen > RSA_SIGN_MAX_LEN) {
			FCS_LOG_ERR("Invalid signature length %d\n", sigLen);
			result = -FCSERR_ESIZE;
			break;
		}

		if (resp_msg_len < RESPONSE_MESSAGE_MIN_SIZE + certLen +
		    sigLen) {
			result = -FCSERR_ESIZE;
			break;
		}
		sig = &resp_msg[offs];

		result = sake_verify_cert_chain(sake_handle, cert, certLen);
		if (result != FCSERR_OK)
			break;

		result = sake_handle->funcs.hash_functions.hash_init(&context,
					sake_handle->hash_type);
		if (result != FCSERR_OK)
			break;
		do {
			result =
				sake_handle->funcs.hash_functions.hash_update(
					context,
					sake_handle->savedHelloMsg,
					sake_handle->savedHelloLen);
			if (result != FCSERR_OK)
				break;
			result = sake_handle->funcs.hash_functions.hash_update(
								context,
								resp_msg,
								mainMsgLen);
			if (result != FCSERR_OK)
				break;
			result =
				sake_handle->funcs.hash_functions.hash_final(
					context, hashRes,
					sake_handle->hash_digest_size);

			if (result != FCSERR_OK)
				break;
		} while (0);

		sake_handle->funcs.hash_functions.hash_deinit(context);
		if (result != FCSERR_OK)
			break;

		padded = malloc(sigLen);
		rsaRes = malloc(sigLen);
		if (!padded || !rsaRes) {
			FCS_LOG_ERR("No memory\n");
			result = -FCSERR_ENOMEM;
			break;
		}

		result = sake_add_padding(hashRes, HASH_SIZE, padded, sigLen);
		if (result != FCSERR_OK)
			break;

		result = sake_get_certificate(&myCert, cert, certLen);
		if (result != FCSERR_OK)
			break;

		result = sake_pub_key_encrypt(sake_handle, sig, sigLen, rsaRes,
					      myCert.publicKey.item_m.data,
					      myCert.publicKey.item_m.len,
					      myCert.publicKey.item_e.data,
					      myCert.publicKey.item_e.len);
		if (result != FCSERR_OK)
			break;

		for (a = 0; a < sigLen; a++) {
			if (padded[a] != rsaRes[a]) {
				result = -FCSERR_EVS;
				break;
			}
		}

		/* Verify that response has been signed with correct SSN */
		if (sake_handle->savedSsn != myCert.ssn) {
			result = -FCSERR_ESTATE;
			break;
		}

		/*
		 * Only release our savedHelloMsg when we are successful
		 * should not need to check if not null
		 */
		if (sake_handle->savedHelloMsg) {
			free(sake_handle->savedHelloMsg);
			sake_handle->savedHelloMsg = 0;
		}
	} while (0);
	/* always free the certificate */
	free(padded);
	free(rsaRes);
	sake_free_certificate(&myCert);
	return result;
}

static uint_fast16_t get_big_ushort(const uint8_t *adr, const uint8_t *endAdr)
{
	/* endadr == first byte that is not allowed to be read */
	uint_fast16_t a;

	if (adr + 2 > endAdr)
		return 0;

	a = adr[0] << 8;
	a |= adr[1];
	return a;
}

static size_t put_big_ushort(uint8_t *adr, uint_fast16_t a)
{
	adr[0] = (a >> 8) & 0xff;
	adr[1] = a & 0xff;
	return 2;
}

static size_t sake_str_len(const char *str)
{
	size_t a;

	for (a = 0; str[a] != 0; a++)
		;
	return a;
}

static size_t put_tag(uint8_t *dst,
		      const char *tagName,
		      const char *tagData,
		      size_t tagNbr)
{
	size_t a = 0;
	size_t l;

	if (tagNbr > 0)
		dst[a++] = ';';

	l = sake_str_len(tagName);
	memcpy(&dst[a], tagName, l);
	a += l;
	dst[a++] = '=';
	dst[a++] = '"';
	l = sake_str_len(tagData);
	memcpy(&dst[a], tagData, l);
	a += l;
	dst[a++] = '"';
	return a;
}

static size_t get_asn1_length(uint8_t **asn_stream)
{
	size_t len_tag = 0;
	size_t payload_len = 0;
	uint8_t *pAsnData = *asn_stream;

	/* we only look for 0x30 SEQUENCE tag and 0x02 INTEGER tag */
	if (pAsnData[0] == 0x30 || pAsnData[0] == 0x02) {
		size_t skip_len = 0;

		len_tag = pAsnData[1];

		if (len_tag == 0x82) {
			skip_len = 4;
			payload_len = (pAsnData[2]<<8) | pAsnData[3];
		} else if (len_tag == 0x81) {
			skip_len = 3;
			payload_len = pAsnData[2];
		} else {
			skip_len = 2;
			payload_len = len_tag;
		}
		*asn_stream = (pAsnData + skip_len);
	}

	return payload_len;
}

static int parse_asn1_rsa_key_and_hash(asn_rsa_public_key_t rsa_pub_key,
				       uint8_t *pub_hash,
				       struct PublicKey *public_key)
{
	int result = FCSERR_OK;

	if (!pub_hash || !public_key) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	do {
		size_t payload_len = 0;
		uint8_t *payload = pub_hash;

		/* start with pub hash */
		payload_len = get_asn1_length(&payload);
		if (payload_len == 0) {
			result = -FCSERR_EINVAL;
			break;
		}

		public_key->item_h.data = (uint8_t *)malloc(payload_len);
		if (!public_key->item_h.data) {
			result = -FCSERR_ENOMEM;
			break;
		}
		public_key->item_h.len = payload_len;
		memcpy(public_key->item_h.data, payload, payload_len);

		payload = (uint8_t *)rsa_pub_key;
		/* read total length */
		payload_len = get_asn1_length(&payload);
		if (payload_len == 0) {
			result = -FCSERR_EINVAL;
			break;
		}

		/* read modulus */
		payload_len = get_asn1_length(&payload);
		if (payload_len == 0) {
			result = -FCSERR_EINVAL;
			break;
		}

		public_key->item_m.data = (uint8_t *)malloc(payload_len);
		if (!public_key->item_m.data) {
			result = -FCSERR_ENOMEM;
			break;
		}
		public_key->item_m.len = payload_len;
		memcpy(public_key->item_m.data, payload, payload_len);
		payload += payload_len;

		/* read exponent */
		payload_len = get_asn1_length(&payload);
		if (payload_len == 0) {
			result = -FCSERR_EINVAL;
			break;
		}

		public_key->item_e.data = (uint8_t *)malloc(payload_len);
		if (!public_key->item_e.data) {
			result = -FCSERR_ENOMEM;
			break;
		}
		public_key->item_e.len = payload_len;
		memcpy(public_key->item_e.data, payload, payload_len);

	} while (0);

	if (result != FCSERR_OK)
		deinit_public_key(public_key);

	return result;
}

static int parse_asn1_crl(struct sake_internal_handle *sake_handle,
			  uint8_t *crl)
{
	int result = FCSERR_OK;

	if (!sake_handle || !crl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	do {
		size_t payload_len = 0;
		uint8_t *payload = crl;
		size_t num_revoked_certs = 0;
		uint8_t crl_version = 0;

		/* get total length */
		payload_len = get_asn1_length(&payload);
		if (payload_len == 0) {
			result = -FCSERR_EINVAL;
			break;
		}

		/* get crl version info */
		payload_len = get_asn1_length(&payload);
		if (payload_len != 1) {
			result = -FCSERR_EINVAL;
			break;
		}
		crl_version = *payload++;

		/* get number of revoked certs */
		payload_len = get_asn1_length(&payload);
		if (payload_len != 1) {
			result = -FCSERR_EINVAL;
			break;
		}
		num_revoked_certs = *payload++;

		payload_len = get_asn1_length(&payload);
		if (payload_len != (num_revoked_certs * CRL_ENTRY_SIZE)) {
			result = -FCSERR_EINVAL;
			break;
		}

		if (num_revoked_certs != 0) {
			unsigned int i = 0;

			sake_handle->cert_revocation_list =
				malloc(num_revoked_certs);
			if (!sake_handle->cert_revocation_list) {
				result = -FCSERR_ENOMEM;
				break;
			}
			sake_handle->cert_revocation_list_len =
				num_revoked_certs;
			sake_handle->cert_revocation_list_version =
				crl_version;
			for (i = 0; i < num_revoked_certs; i++) {
				memcpy(sake_handle->cert_revocation_list[i],
				       payload, CRL_ENTRY_SIZE);
				payload += CRL_ENTRY_SIZE;
			}
		}
	} while (0);

	return result;
}

void deinit_public_key(struct PublicKey *public_key)
{
	if (public_key) {
		if (public_key->item_e.data) {
			free(public_key->item_e.data);
			public_key->item_e.data = 0;
		}
		if (public_key->item_m.data) {
			free(public_key->item_m.data);
			public_key->item_m.data = 0;
		}
		if (public_key->item_h.data) {
			free(public_key->item_h.data);
			public_key->item_h.data = 0;
		}
	}
}
