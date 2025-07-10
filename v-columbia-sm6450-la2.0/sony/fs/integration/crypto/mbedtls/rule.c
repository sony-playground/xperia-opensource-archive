/*
 * Copyright 2017, 2021 Sony Corporation.
 * All rights, including trade secret rights, reserved.
 */
#include <mbedtls/version.h>
#if (MBEDTLS_VERSION_NUMBER == 0x03000000)
#include <common.h> // MbedTLSLib/mbedtls/library/common.h
#endif

#include "rule_mbedtls.h"
#include "fcserr.h"
#include "fcslog.h"
#include <mbedtls/x509_crt.h>
#include <mbedtls/oid.h>
#include <string.h>

#define ERROR_BUF_SIZE (2048)

static struct rule_extension *rule_mbedtls_create_extension(
		unsigned char **extension_ptr,
		unsigned char *extensions_end,
		int depth)
{
	struct rule_extension *extension = NULL;
	int vres;
	size_t extension_len = 0;
	unsigned char *oid_ptr = NULL;
	size_t oid_len = 0;
	unsigned char *oid = NULL;
	unsigned char *data_ptr = NULL;
	size_t data_len = 0;
	unsigned char *data = NULL;

	vres = mbedtls_asn1_get_tag(
			extension_ptr,
			extensions_end,
			&extension_len,
			MBEDTLS_ASN1_SEQUENCE |
			MBEDTLS_ASN1_CONSTRUCTED);
	if (vres != 0)
		goto rule_mbedtls_create_extension_end;

	/* Get extnID */
	oid_ptr = *extension_ptr;
	data_ptr = oid_ptr;
	vres = mbedtls_asn1_get_tag(
			&data_ptr,
			extensions_end,
			&data_len,
			MBEDTLS_ASN1_OID);
	if (vres != 0)
		goto rule_mbedtls_create_extension_end;

	/* Get critical (if present) or/and value */
	/* Value (incl header) if critical not present: */
	data_ptr += data_len;
	oid_len = (size_t)(data_ptr - oid_ptr);
	vres = mbedtls_asn1_get_tag(
			&data_ptr,
			extensions_end,
			&data_len,
			MBEDTLS_ASN1_BOOLEAN);
	if (vres == 0) {
		/* Is critical */
		/* Trim value ptr/len */
		data_ptr += data_len;
	} else if (vres == MBEDTLS_ERR_ASN1_UNEXPECTED_TAG) {
		/* Is Value */
		/* data_ptr did not advance */
		vres = 0;
	} else {
		/* Format error */
		goto rule_mbedtls_create_extension_end;
	}

	/* Attribute value should alway be an octet string. */
	/* Remove Octet String Tag */
	vres = mbedtls_asn1_get_tag(
			&data_ptr,
			extensions_end,
			&data_len,
			MBEDTLS_ASN1_OCTET_STRING);
	if (vres != 0) {
		/* Format error */
		goto rule_mbedtls_create_extension_end;
	}

	oid = (unsigned char *)malloc(oid_len + 1);
	if (oid == NULL)
		goto rule_mbedtls_create_extension_end;
	memcpy(oid, oid_ptr, oid_len);
	oid[oid_len] = '\0';

	data = (uint8_t *)malloc(data_len);
	if (data == NULL)
		goto rule_mbedtls_create_extension_end;
	memcpy(data, data_ptr, data_len);

	/* Setup extension struct */
	extension = (struct rule_extension *)malloc(
			sizeof(struct rule_extension));
	if (extension == NULL)
		goto rule_mbedtls_create_extension_end;
	extension->cert_level = depth;
	extension->oid = oid;
	extension->oid_len = oid_len;
	oid = NULL;
	extension->asn1_buffer = data;
	extension->asn1_buffer_len = data_len;
	data = NULL;

	*extension_ptr += extension_len;

rule_mbedtls_create_extension_end:
	free(oid);
	free(data);
	return extension;
}

static void rule_mbedtls_delete_extension(
		struct rule_extension *extension)
{
	if (extension != NULL) {
		free((char *)(extension->oid));
		free((uint8_t *)(extension->asn1_buffer));
		free(extension);
	}
}

static struct rule_cn *rule_mbedtls_create_cn(mbedtls_x509_crt *cert, int depth)
{
	struct rule_cn *cn_out = NULL;
#if (MBEDTLS_VERSION_NUMBER == 0x03000000)
	const mbedtls_asn1_named_data *data = NULL;
#else /* !(MBEDTLS_VERSION_NUMBER == 0x03000000) */
	/* Support MbedTLS 2.16.0 */
	mbedtls_asn1_named_data *data = NULL;
#endif /* !(MBEDTLS_VERSION_NUMBER == 0x03000000) */
	char *cn = NULL;

	data = mbedtls_asn1_find_named_data(
			&(cert->subject),
			MBEDTLS_OID_AT_CN,
			MBEDTLS_OID_SIZE(MBEDTLS_OID_AT_CN));
	if ((data == NULL) ||
			(data->val.len == 0) ||
			(data->val.p == NULL))
		goto rule_mbedtls_create_cn_end;

	cn = (char *)malloc(data->val.len+1);
	if (cn == NULL)
		goto rule_mbedtls_create_cn_end;
	memcpy(cn, data->val.p, data->val.len);
	cn[data->val.len] = '\0';

	/* Setup cn struct */
	cn_out = (struct rule_cn *)malloc(
			sizeof(struct rule_cn));
	if (cn_out == NULL)
		goto rule_mbedtls_create_cn_end;
	cn_out->cert_level = depth;
	cn_out->cn = (void *)cn;
	cn_out->cn_len = (size_t)data->val.len;
	cn = NULL;

rule_mbedtls_create_cn_end:
	free(cn);
	return cn_out;
}

static void rule_mbedtls_delete_cn(
		struct rule_cn *cn)
{
	if (cn != NULL) {
		free((uint8_t *)(cn->cn));
		free(cn);
	}
}

static struct rule_ou *rule_mbedtls_create_ou(mbedtls_x509_crt *cert, int depth)
{
	struct rule_ou *ou_out = NULL;
#if (MBEDTLS_VERSION_NUMBER == 0x03000000)
	const mbedtls_asn1_named_data *data = NULL;
#else /* !(MBEDTLS_VERSION_NUMBER == 0x03000000) */
	/* Support MbedTLS 2.16.0 */
	mbedtls_asn1_named_data *data = NULL;
#endif /* !(MBEDTLS_VERSION_NUMBER == 0x03000000) */
	char *ou = NULL;

	data = mbedtls_asn1_find_named_data(
			&(cert->subject),
			MBEDTLS_OID_AT_ORG_UNIT,
			MBEDTLS_OID_SIZE(MBEDTLS_OID_AT_ORG_UNIT));
	if ((data == NULL) ||
			(data->val.len == 0) ||
			(data->val.p == NULL))
		goto rule_mbedtls_create_ou_end;

	ou = malloc(data->val.len+1);
	if (ou == NULL)
		goto rule_mbedtls_create_ou_end;
	memcpy(ou, data->val.p, data->val.len);
	ou[data->val.len] = '\0';

	/* Setup ou struct */
	ou_out = malloc(sizeof(struct rule_ou));
	if (ou_out == NULL)
		goto rule_mbedtls_create_ou_end;
	ou_out->cert_level = depth;
	ou_out->ou = (void *)ou;
	ou_out->ou_len = data->val.len;
	ou = NULL;

rule_mbedtls_create_ou_end:
	free(ou);
	return ou_out;
}

static void rule_mbedtls_delete_ou(
		struct rule_ou *ou)
{
	if (ou != NULL) {
		free((void *)(ou->ou));
		free(ou);
	}
}

int rule_mbedtls_verify_cb(
		void *context,
		mbedtls_x509_crt *cur_cert,
		int depth,
		uint32_t *flags)
{
	struct rule_extension *extension = NULL;
	struct rule_cn *cn = NULL;
	struct rule_ou *ou = NULL;
	struct rule_verifier *rule_handle = (struct rule_verifier *)context;
	unsigned char *extension_ptr = NULL;
	unsigned char *extensions_end = NULL;
	size_t length = 0;
	int res;
	int res_cb = 0;
	int vres;
	char *error_text = NULL;

	if (rule_handle == NULL) {
		FCS_LOG_ERR("Failed to get rule handle.\n");
		res_cb = MBEDTLS_ERR_X509_BAD_INPUT_DATA;
		goto rule_mbedtls_verify_cb_end;
	}

	/* Ignore date/time info */
	*flags &= ~(MBEDTLS_X509_BADCERT_FUTURE | MBEDTLS_X509_BADCERT_EXPIRED);

	if (*flags == 0) {
		/* Extract subject cn/oid */
		cn = rule_mbedtls_create_cn(cur_cert, depth);
		if (cn == NULL)
			goto rule_mbedtls_extract_extension;
		res = rule_update_subject_cn(rule_handle, cn);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to update cn.\n");
			res_cb = MBEDTLS_ERR_X509_INVALID_NAME;
			goto rule_mbedtls_verify_cb_end;
		}
		ou = rule_mbedtls_create_ou(cur_cert, depth);
		if (ou == NULL)
			goto rule_mbedtls_extract_extension;
		res = rule_update_subject_ou(rule_handle, ou);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to update ou.\n");
			res_cb = MBEDTLS_ERR_X509_INVALID_NAME;
			goto rule_mbedtls_verify_cb_end;
		}

rule_mbedtls_extract_extension:

		/* Extract certificate extensions if present (has 0xA3 tag) and
		 * send them to rule verifier.
		 */
		if (cur_cert->v3_ext.tag != 0xA3 ||
				cur_cert->v3_ext.len == 0 ||
				cur_cert->v3_ext.p == NULL)
			goto rule_mbedtls_verify_cb_end;

		extension_ptr = cur_cert->v3_ext.p;

		vres = mbedtls_asn1_get_tag(
				&extension_ptr,
				extension_ptr + cur_cert->v3_ext.len,
				&length,
				MBEDTLS_ASN1_SEQUENCE |
				MBEDTLS_ASN1_CONSTRUCTED);
		if (vres != 0) {
			FCS_LOG_ERR("Failed to parse extension.\n");
			res_cb = MBEDTLS_ERR_X509_INVALID_FORMAT;
			goto rule_mbedtls_verify_cb_end;
		}

		extensions_end = extension_ptr + length;

		while (extension_ptr < extensions_end) {
			extension = rule_mbedtls_create_extension(
					&extension_ptr,
					extensions_end,
					depth);
			if (extension == NULL) {
				FCS_LOG_ERR("Failed to create ext.\n");
				res_cb = MBEDTLS_ERR_X509_INVALID_EXTENSIONS;
				goto rule_mbedtls_verify_cb_end;
			}
			res = rule_update_unhandled_extensions(
				rule_handle, extension);
			if (res != FCSERR_OK) {
				FCS_LOG_ERR("Failed to update ext.\n");
				res_cb = MBEDTLS_ERR_X509_INVALID_EXTENSIONS;
				goto rule_mbedtls_verify_cb_end;
			}
			rule_mbedtls_delete_extension(extension);
			extension = NULL;
		}

	} else {
		/* Unexpected error. For now just */
		/* log the error code and current cert */
		FCS_LOG_ERR(
			"depth (%d), flags (%x).\n", depth, *flags);

		error_text = malloc(ERROR_BUF_SIZE);
		if (error_text == NULL) {
			FCS_LOG_ERR("Malloc failed!\n");
			res_cb = -FCSERR_ENOMEM;
			goto rule_mbedtls_verify_cb_end;
		}

		vres = mbedtls_x509_crt_info(
				error_text,
				ERROR_BUF_SIZE,
				"",
				cur_cert);
		if (vres >= 0)
			FCS_LOG_ERR("cert (%s).\n", error_text);
	}
rule_mbedtls_verify_cb_end:
	rule_mbedtls_delete_extension(extension);
	rule_mbedtls_delete_cn(cn);
	rule_mbedtls_delete_ou(ou);
	free(error_text);
	return res_cb;
}

