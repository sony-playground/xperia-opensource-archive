/******************************************************************************
 *                     ____                                                   *
 *                    / ___|  ___  _ __                                       *
 *                    \___ \ / _ \| '_ \| | | |                               *
 *                    ___ ) | (_) | | | | |_| |                               *
 *                    |____/ \___/|_| |_|\__, |                               *
 *                                        |___/                               *
 *                                                                            *
 ******************************************************************************
 * Copyright (c) 2016 Sony Mobile Communications Inc.                         *
 * All rights, including trade secret rights, reserved.                       *
 *****************************************************************************/
#include "cms_verifier.h"
#include "../rm/rule_verifier_intern.h"
#include "../rm/rule_openssl.h"
#include "fcserr.h"
#include "fcslog.h"
#include <openssl/err.h>
#include <openssl/cms.h>
#include <string.h>

#define CMS_VERIFY_EXT_DATA_RULE_HANDLE 0

const unsigned int cms_verify_flag = 0;

static int cms_get_embedded_payload(CMS_ContentInfo *cms,
		uint8_t **embedded_payload,
		size_t *embedded_payload_length) {
	int res = FCSERR_OK;
	int len = 0;
	unsigned char *buffer = NULL;

	ASN1_OCTET_STRING **pos = NULL;

	pos = CMS_get0_content(cms);
	if ((NULL != pos) && (NULL != *pos)) {
		len = (*pos)->length;
		if (len <= 0) {
			FCS_LOG_ERR("Length of payload is wrong.\n");
			res = -FCSERR_EINFOR;
			goto cms_get_embedded_payload_end;
		}
		buffer = malloc(len);
		if (NULL == buffer) {
			FCS_LOG_ERR("Allocation of payload buffer failed.\n");
			res = -FCSERR_ENOMEM;
			goto cms_get_embedded_payload_end;
		}
		memcpy(buffer, (*pos)->data, len);
	}
	*embedded_payload_length = len;
	*embedded_payload = buffer;

cms_get_embedded_payload_end:
	return res;
}

static int cms_process_attributes(CMS_ContentInfo *cms_info,
	struct rule_verifier *rule_handle)
{
	int res = FCSERR_OK;
	CMS_SignerInfo *si = NULL;

	STACK_OF(CMS_SignerInfo) * sinfos = NULL;
	int attr_count = 0;
	X509_ATTRIBUTE *attr = NULL;
	struct rule_attribute *attr_rule = NULL;
	int i;

	sinfos = CMS_get0_SignerInfos(cms_info);
	if (NULL == sinfos) {
		FCS_LOG_ERR("Failed to get signer infos.\n");
		res = -FCSERR_EINFOR;
		goto cms_process_attributes_end;
	}

	if (1 != sk_CMS_SignerInfo_num(sinfos)) {
		FCS_LOG_ERR("Unsupported number of signers.\n");
		res = -FCSERR_EINFOR;
		goto cms_process_attributes_end;
	}

	si = sk_CMS_SignerInfo_value(sinfos, 0);
	if (NULL == si) {
		FCS_LOG_ERR("Failed to get signer info.\n");
		res = -FCSERR_EINFOR;
		goto cms_process_attributes_end;
	}
	attr_count = CMS_signed_get_attr_count(si);
	if (0 >= attr_count) {
		FCS_LOG_ERR("Failed to get signer attribute.\n");
		res = -FCSERR_EINFOR;
		goto cms_process_attributes_end;
	}
	for (i = 0; i < attr_count; i++) {
		attr = CMS_signed_get_attr(si, i);
		if (NULL == attr) {
			FCS_LOG_ERR("Failed to get signer attr.\n");
			res = -FCSERR_EINFOR;
			goto cms_process_attributes_end;
		}
		attr_rule = rule_openssl_create_attribute(attr);
		if (NULL == attr_rule) {
			FCS_LOG_ERR("Failed to fetch attribute.\n");
			res = -FCSERR_EINFOR;
			goto cms_process_attributes_end;
		}
		res = rule_update_unhandled_attributes(
				rule_handle, attr_rule);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to update attribute.\n");
			goto cms_process_attributes_end;
		}
		rule_openssl_delete_attribute(attr_rule);
		attr_rule = NULL;
	}

cms_process_attributes_end:
	rule_openssl_delete_attribute(attr_rule);
	return res;
}

int cms_verify(uint8_t         *cms,
	size_t                  cms_length,
	struct rule_verifier *rule,
	uint8_t                *rootcerts,
	size_t                  rootcerts_length,
	uint8_t                *external_payload,
	size_t                  external_payload_length,
	uint8_t               **embedded_payload,
	size_t                 *embedded_payload_length)
{
	int res = -FCSERR_EINVAL;
	CMS_ContentInfo *cms_info = NULL;
	BIO *cms_bio = NULL;
	BIO *ext_pl_bio = NULL;
	X509_STORE *root_store = NULL;

	/* Check in parameters */
	if ((NULL == cms) ||
			(0 == cms_length) ||
			(NULL == rule) ||
			(NULL == rootcerts) ||
			(0 == rootcerts_length) ||
			((NULL == external_payload) &&
			 (0 < external_payload_length)) ||
			(NULL == embedded_payload &&
			 NULL != embedded_payload_length) ||
			(NULL == embedded_payload_length &&
			 NULL != embedded_payload)) {
		FCS_LOG_ERR("Invalid parameter.\n");
		goto cms_verify_exit;
	}

	cms_bio = BIO_new_mem_buf((void *)cms, cms_length);
	if (NULL == cms_bio) {
		FCS_LOG_ERR("Failed to create cms buffer\n");
		res = -FCSERR_EINVAL;
		goto cms_verify_exit;
	}

	cms_info = d2i_CMS_bio(cms_bio, NULL);
	if (NULL == cms_info) {
		FCS_LOG_ERR("Failed to parse cms\n");
		res = -FCSERR_EINFOR;
		goto cms_verify_exit;
	}

	if (NULL != external_payload) {
		ext_pl_bio = BIO_new_mem_buf((void *)external_payload,
			external_payload_length);
		if (NULL == ext_pl_bio) {
			FCS_LOG_ERR("Failed to create payload buffer\n");
			res = -FCSERR_EINVAL;
			goto cms_verify_exit;
		}
	}

	res = rule_openssl_setup_root_store(&root_store,
		rootcerts,
		rootcerts_length,
		rule);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to setup root store: (%d)\n", res);
		goto cms_verify_exit;
	}

	res = cms_process_attributes(cms_info, rule);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to process attributes: (%d)\n", res);
		goto cms_verify_exit;
	}

	if (1 != CMS_verify(cms_info, NULL, root_store,
			ext_pl_bio, NULL, cms_verify_flag)) {
		FCS_LOG_ERR(
			"CMS_verify failed. Reason: %s\n",
			ERR_error_string(ERR_get_error(), NULL));
		res = -FCSERR_EVS;
		goto cms_verify_exit;
	}

	res = rule_final(rule);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to finalize rule check: (%d)\n", res);
		goto cms_verify_exit;
	}

	if (NULL != embedded_payload && NULL != embedded_payload_length)
		res = cms_get_embedded_payload(cms_info,
			embedded_payload,
			embedded_payload_length);

cms_verify_exit:
	if (NULL != root_store)
		X509_STORE_free(root_store);
	CMS_ContentInfo_free(cms_info);
	BIO_free(ext_pl_bio);
	BIO_free(cms_bio);
	return res;
}
