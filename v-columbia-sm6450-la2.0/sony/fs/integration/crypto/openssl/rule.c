/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#include "rule_openssl.h"
#include "fcserr.h"
#include "fcslog.h"

#define RULE_OPENSSL_EXT_DATA_RULE_HANDLE 0

static struct rule_extension *rule_openssl_create_extension(
		struct X509_extension_st *cur_ext,
		int currentLevel)
{
	ASN1_OBJECT *cur_obj = NULL;
	ASN1_OCTET_STRING *cur_data = NULL;
	size_t oid_len = 0;
	unsigned char *oid = NULL;
	unsigned char *data_ptr = NULL;
	uint8_t *data = NULL;
	size_t data_len = 0;
	struct rule_extension *extension = NULL;
	size_t i;

	cur_obj = X509_EXTENSION_get_object(cur_ext);
	if (NULL == cur_obj)
		goto rule_openssl_create_extension_end;

	/* Extract OID */
	oid_len = i2d_ASN1_OBJECT(cur_obj, NULL);
	if (0 >= oid_len)
		goto rule_openssl_create_extension_end;
	oid = (unsigned char *)malloc(oid_len + 1);
	if (NULL == oid)
		goto rule_openssl_create_extension_end;
	data_ptr = oid;
	data_len = i2d_ASN1_OBJECT(cur_obj, &data_ptr);

	/* Extract Data */
	cur_data = X509_EXTENSION_get_data(cur_ext);
	if (NULL == cur_data)
		goto rule_openssl_create_extension_end;

	data_len = M_ASN1_STRING_length(cur_data);
	if (0 >= data_len)
		goto rule_openssl_create_extension_end;
	data = (uint8_t *)malloc(data_len);
	if (NULL == data)
		goto rule_openssl_create_extension_end;
	data_ptr = M_ASN1_STRING_data(cur_data);
	for (i = 0; i < data_len; i++)
		data[i] = data_ptr[i];

	/* Setup extension struct */
	extension = (struct rule_extension *)malloc(
			sizeof(struct rule_extension));
	if (NULL == extension)
		goto rule_openssl_create_extension_end;
	extension->cert_level = currentLevel;
	extension->oid = oid;
	extension->oid_len = oid_len;
	oid = NULL;
	extension->asn1_buffer = data;
	extension->asn1_buffer_len = data_len;
	data = NULL;

rule_openssl_create_extension_end:
	free(oid);
	free(data);
	return extension;
}

static void rule_openssl_delete_extension(
		struct rule_extension *extension)
{
	if (NULL != extension) {
		free((char *)(extension->oid));
		free((uint8_t *)(extension->asn1_buffer));
		free(extension);
	}
}

static struct rule_cn *rule_openssl_create_cn(
		struct x509_st *currentCert,
		int currentLevel)
{
	struct rule_cn *cn_out = NULL;
	X509_NAME *name = NULL;
	int cn_len = 0;
	char *cn = NULL;

	name = X509_get_subject_name(currentCert);
	if (NULL == name)
		goto rule_openssl_create_cn_end;
	cn_len = X509_NAME_get_text_by_NID(name,
			NID_commonName, NULL, 0);
	if (0 >= cn_len)
		goto rule_openssl_create_cn_end;
	cn = (char *)malloc(cn_len+1);
	if (NULL == cn)
		goto rule_openssl_create_cn_end;
	cn_len = X509_NAME_get_text_by_NID(name,
			NID_commonName, cn, cn_len+1);
	if (0 >= cn_len)
		goto rule_openssl_create_cn_end;

	/* Setup cn struct */
	cn_out = (struct rule_cn *)malloc(
			sizeof(struct rule_cn));
	if (NULL == cn_out)
		goto rule_openssl_create_cn_end;
	cn_out->cert_level = currentLevel;
	cn_out->cn = (void *)cn;
	cn_out->cn_len = (size_t)cn_len;
	cn = NULL;

rule_openssl_create_cn_end:
	free(cn);
	return cn_out;
}

static void rule_openssl_delete_cn(
		struct rule_cn *cn)
{
	if (NULL != cn) {
		free((uint8_t *)(cn->cn));
		free(cn);
	}
}

struct rule_attribute *rule_openssl_create_attribute(
		X509_ATTRIBUTE * attr_in)
{
	struct rule_attribute *attr_out = NULL;
	ASN1_OBJECT *attr_obj = NULL;
	ASN1_TYPE *attr_type = NULL;
	size_t oid_len = 0;
	unsigned char *oid = NULL;
	int data_len = 0;
	unsigned char *data = NULL;
	unsigned char *data_ptr = NULL;

	if (0 >= X509_ATTRIBUTE_count(attr_in))
		goto rule_openssl_create_attribute_end;
	attr_obj = X509_ATTRIBUTE_get0_object(attr_in);
	if (NULL == attr_obj)
		goto rule_openssl_create_attribute_end;

	/* Extract OID */
	oid_len = i2d_ASN1_OBJECT(attr_obj, NULL);
	if (0 >= oid_len)
		goto rule_openssl_create_attribute_end;
	oid = (unsigned char *)malloc(oid_len + 1);
	if (NULL == oid)
		goto rule_openssl_create_attribute_end;
	data_ptr = oid;
	data_len = i2d_ASN1_OBJECT(attr_obj, &data_ptr);

	/* Extract Data */
	/* If more than one attribute value ignore them */
	attr_type = X509_ATTRIBUTE_get0_type(attr_in, 0);
	if (NULL == attr_type)
		goto rule_openssl_create_attribute_end;
	data_len = i2d_ASN1_TYPE(attr_type, NULL);
	if (data_len <= 0)
		goto rule_openssl_create_attribute_end;
	data = (unsigned char *)malloc(data_len);
	if (data == NULL)
		goto rule_openssl_create_attribute_end;
	data_ptr = data;
	data_len = i2d_ASN1_TYPE(attr_type, &data_ptr);
	if (data_len <= 0)
		goto rule_openssl_create_attribute_end;

	/* Setup attribute struct */
	attr_out = (struct rule_attribute *)malloc(
			sizeof(struct rule_attribute));
	if (NULL == attr_out)
		goto rule_openssl_create_attribute_end;
	attr_out->oid = oid;
	attr_out->oid_len = oid_len;
	oid = NULL;
	attr_out->asn1_buffer = data;
	attr_out->asn1_buffer_len = (size_t)data_len;
	data = NULL;

rule_openssl_create_attribute_end:
	free(data);
	free(oid);
	return attr_out;
}

void rule_openssl_delete_attribute(
		struct rule_attribute *attribute)
{
	if (NULL != attribute) {
		free((char *)(attribute->oid));
		free((uint8_t *)(attribute->asn1_buffer));
		free(attribute);
	}
}

static struct rule_ou *rule_openssl_create_ou(
		struct x509_st *currentCert,
		int currentLevel)
{
	struct rule_ou *ou_out = NULL;
	X509_NAME *name = NULL;
	int ou_len = 0;
	char *ou = NULL;

	name = X509_get_subject_name(currentCert);
	if (NULL == name)
		goto rule_openssl_create_ou_end;
	ou_len = X509_NAME_get_text_by_NID(name,
			NID_organizationalUnitName, NULL, 0);
	if (0 >= ou_len)
		goto rule_openssl_create_ou_end;
	ou = malloc(ou_len+1);
	if (NULL == ou)
		goto rule_openssl_create_ou_end;
	ou_len = X509_NAME_get_text_by_NID(name,
			NID_organizationalUnitName, ou, ou_len+1);
	if (0 >= ou_len)
		goto rule_openssl_create_ou_end;

	/* Setup ou struct */
	ou_out = malloc(sizeof(struct rule_ou));
	if (NULL == ou_out)
		goto rule_openssl_create_ou_end;
	ou_out->cert_level = currentLevel;
	ou_out->ou = (void *)ou;
	ou_out->ou_len = ou_len;
	ou = NULL;

rule_openssl_create_ou_end:
	free(ou);
	return ou_out;
}

static void rule_openssl_delete_ou(
		struct rule_ou *ou)
{
	if (NULL != ou) {
		free((void *)(ou->ou));
		free(ou);
	}
}

static int rule_openssl_verify_cb(int ok, X509_STORE_CTX *ctx)
{
	X509_STORE *store = NULL;
	struct rule_extension *extension = NULL;
	struct rule_cn *cn = NULL;
	struct rule_ou *ou = NULL;
	int certError = -1;
	X509 *currentCert = NULL;
	X509_EXTENSION *cur_ext = NULL;
	int currentLevel = -1;
	struct rule_verifier *rule_handle = NULL;
	int res;
	int lastpos = -1;

	currentCert = X509_STORE_CTX_get_current_cert(ctx);
	currentLevel = X509_STORE_CTX_get_error_depth(ctx);
	store = X509_STORE_CTX_get0_store(ctx);
	if (NULL == store) {
		FCS_LOG_ERR("Failed to get store.\n");
		ok = 0;
		goto rule_openssl_verify_cb_end;
	}
	rule_handle = (struct rule_verifier *)
		CRYPTO_get_ex_data(&store->ex_data,
			RULE_OPENSSL_EXT_DATA_RULE_HANDLE);
	if (NULL == rule_handle) {
		FCS_LOG_ERR("Failed to get rule handle.\n");
		ok = 0;
		goto rule_openssl_verify_cb_end;
	}
	if (!ok) {
		store = X509_STORE_CTX_get0_store(ctx);
		if (NULL == store) {
			FCS_LOG_ERR("Failed to get store.\n");
			goto rule_openssl_verify_cb_end;
		}
		rule_handle = (struct rule_verifier *)
			CRYPTO_get_ex_data(&store->ex_data,
				RULE_OPENSSL_EXT_DATA_RULE_HANDLE);
		if (NULL == rule_handle) {
			FCS_LOG_ERR("Failed to get rule handle.\n");
			goto rule_openssl_verify_cb_end;
		}
		certError = X509_STORE_CTX_get_error(ctx);
		if ((certError == X509_V_ERR_CERT_NOT_YET_VALID) ||
			(certError == X509_V_ERR_CERT_HAS_EXPIRED)) {
			ok = 1;
			/* Ignore date/time info */
			goto rule_openssl_verify_cb_end;
		}
		if (certError == X509_V_ERR_UNHANDLED_CRITICAL_EXTENSION) {
			lastpos = X509_get_ext_by_critical(
					currentCert, 1, lastpos);
			while (lastpos != -1) {
				cur_ext = X509_get_ext(currentCert, lastpos);
				if (NULL == cur_ext)
					goto rule_openssl_verify_cb_end;
				extension = rule_openssl_create_extension(
					cur_ext, currentLevel);
				if (NULL == extension) {
					FCS_LOG_ERR("Failed to fetch ext.\n");
					goto rule_openssl_verify_cb_end;
				}
				res = rule_update_unhandled_extensions(
					rule_handle, extension);
				if (res != FCSERR_OK) {
					FCS_LOG_ERR("Failed to update ext.\n");
					goto rule_openssl_verify_cb_end;
				}
				rule_openssl_delete_extension(extension);
				extension = NULL;
				lastpos = X509_get_ext_by_critical(
					currentCert, 1, lastpos);
			}
			ok = 1;
		} else {
			/* Unspected error for now just */
			/* log the error code and current cert*/
			currentLevel = X509_STORE_CTX_get_error_depth(ctx);
			FCS_LOG_ERR(
				"verify_cb:\n  cert: %p\n  depth: %d\n  error:%d (%s)\n",
				currentCert, currentLevel, certError,
				X509_verify_cert_error_string(certError));
		}
	} else {
		cn = rule_openssl_create_cn(currentCert, currentLevel);
		if (NULL == cn) {
			FCS_LOG_ERR("Failed to fetch cn.\n");
			ok = 0;
			goto rule_openssl_verify_cb_end;
		}
		res = rule_update_subject_cn(rule_handle, cn);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to update cn.\n");
			ok = 0;
		}
		ou = rule_openssl_create_ou(currentCert, currentLevel);
		if (NULL == ou)
			goto rule_openssl_verify_cb_end;
		res = rule_update_subject_ou(rule_handle, ou);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to update ou.\n");
			ok = 0;
		}
	}
rule_openssl_verify_cb_end:
	rule_openssl_delete_extension(extension);
	rule_openssl_delete_cn(cn);
	rule_openssl_delete_ou(ou);
	return ok;
}

int rule_openssl_setup_root_store(X509_STORE **root_store,
	uint8_t                *rootcerts,
	size_t                  rootcerts_length,
	struct rule_verifier *rule_handle)
{
	int res = FCSERR_OK;
	const unsigned char *certbuffer_ptr = NULL;
	const unsigned char *certbuffer_end = NULL;
	X509 *cert_ptr;

	*root_store = X509_STORE_new();
	if (NULL == *root_store) {
		FCS_LOG_ERR("Failed to create root store\n");
		res = -FCSERR_ENOMEM;
		goto rule_openssl_setup_root_store_end;
	}

	certbuffer_ptr = rootcerts;
	certbuffer_end = &rootcerts[rootcerts_length];
	while (certbuffer_ptr < certbuffer_end) {
		cert_ptr = d2i_X509(NULL,
			(const unsigned char **)&certbuffer_ptr,
			(certbuffer_end - certbuffer_ptr));
		if (NULL == cert_ptr) {
			FCS_LOG_ERR("Failed to parse root cert\n");
			res = -FCSERR_EINFOR;
			goto rule_openssl_setup_root_store_end;
		}
		X509_STORE_add_cert(*root_store, cert_ptr);
	}

	/* Set verify callback function */
	X509_STORE_set_verify_cb(*root_store, rule_openssl_verify_cb);

	/* Setup store ex data */
	if (1 != CRYPTO_set_ex_data(
			&((*root_store)->ex_data),
			RULE_OPENSSL_EXT_DATA_RULE_HANDLE,
			rule_handle)) {
		FCS_LOG_ERR("Failed to set ext_data rule handle.\n");
		res = -FCSERR_ENOMEM;
		goto rule_openssl_setup_root_store_end;
	}

rule_openssl_setup_root_store_end:
	return res;
}

