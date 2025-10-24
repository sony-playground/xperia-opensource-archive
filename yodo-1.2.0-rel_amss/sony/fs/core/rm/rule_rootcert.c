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
#include "rule_rootcert.h"
#include <stdlib.h>
#include <string.h>
#include "fcserr.h"
#include "fcslog.h"
#include <ks.h>

/**
 * Type definitions and defines
 */

/**
 * Exported functions
 */
int rule_get_roots(
		uint32_t usage,
		struct embed_rootcert_item *embed_rootcert_list,
		size_t embed_rootcert_list_count,
		struct ks_ctx *keystore_hdl,
		uint8_t **rootcert,
		size_t *rootcert_length)
{
	int res = -FCSERR_EINVAL;
	uint32_t i = 0;
	uint32_t usage_flags = 0;
	uint8_t *buffer = NULL;
	size_t buffer_len = 0;
	struct ksstore_blob blob;

	uint32_t nkeys;

	buffer = NULL;
	/* Check in parameters */
	if ((NULL == rootcert) ||
		(NULL == rootcert_length) ||
		(NULL == embed_rootcert_list) ||
		(0 == embed_rootcert_list_count)) {
		FCS_LOG_ERR("Invalid parameter.\n");
		goto rule_get_roots_exit;
	}

	/* check if cert is available in keystore if FLASH UC */
	if (usage == RULE_USAGE_FLASH && keystore_hdl) {
		res = ks_get_nof_keys(
			keystore_hdl, KEYSTORE_DOMAIN_FLASH, &nkeys);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("ks_get_nof_keys failed (%d)\n", res);
			return res;
		}
		for (i = 0; i < nkeys; i++) {
			ks_get_key_by_index(keystore_hdl, KEYSTORE_DOMAIN_FLASH,
					    i, &blob);

			if (blob.type == KS_KEY_TYPE_CERT)
				buffer_len += blob.size;
		}
	}

	/* check if cert is available in keystore if NORMAL KERNEL UC */
	if (usage == RULE_USAGE_NORMAL_KERNEL && keystore_hdl) {
		res = ks_get_nof_keys(
			keystore_hdl, KEYSTORE_DOMAIN_KERNEL, &nkeys);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("ks_get_nof_keys failed (%d)\n", res);
			return res;
		}
		for (i = 0; i < nkeys; i++) {
			ks_get_key_by_index(keystore_hdl,
					KEYSTORE_DOMAIN_KERNEL, i, &blob);

			if (blob.type == KS_KEY_TYPE_CERT)
				buffer_len += blob.size;
		}
	}

	/* check if cert is available in keystore if LOADER KERNEL UC */
	if (usage == RULE_USAGE_LOADER_KERNEL && keystore_hdl) {
		res = ks_get_nof_keys(
			keystore_hdl, KEYSTORE_DOMAIN_XFL, &nkeys);
		if (res != FCSERR_OK) {
			FCS_LOG_WRN("No key in keystore for xfl (%d)\n", res);
			/* Don't return. Check for embedded certs */
		} else {
			for (i = 0; i < nkeys; i++) {
				ks_get_key_by_index(keystore_hdl,
						KEYSTORE_DOMAIN_XFL, i, &blob);

				if (blob.type == KS_KEY_TYPE_CERT)
					buffer_len += blob.size;
			}
		}
	}

	/* Find embedded roots with correct usage and add to length */
	for (i = 0; i < embed_rootcert_list_count; i++) {
		usage_flags = embed_rootcert_list[i].usage_flags;
		if (usage == (usage_flags & usage))
			buffer_len += embed_rootcert_list[i].rootcerts_length;
	}
	buffer = (uint8_t *)malloc(buffer_len);
	if (NULL == buffer) {
		FCS_LOG_ERR("Create of roots buffer failed.\n");
		res = -FCSERR_ENOMEM;
		goto rule_get_roots_exit;
	}

	/* copy ks cert for FLASH */
	buffer_len = 0;
	if (usage == RULE_USAGE_FLASH && keystore_hdl) {
		res = ks_get_nof_keys(
			keystore_hdl, KEYSTORE_DOMAIN_FLASH, &nkeys);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("ks_get_nof_keys failed (%d)\n", res);
			return res;
		}
		for (i = 0; i < nkeys; i++) {
			ks_get_key_by_index(keystore_hdl, KEYSTORE_DOMAIN_FLASH,
					    i, &blob);
			if (blob.type == KS_KEY_TYPE_CERT) {
				memcpy(&buffer[buffer_len],
				       blob.blob, blob.size);
				buffer_len += blob.size;
			}
		}
	}

	/* copy ks cert for NORMAL KERNEL */
	if (usage == RULE_USAGE_NORMAL_KERNEL && keystore_hdl) {
		res = ks_get_nof_keys(
			keystore_hdl, KEYSTORE_DOMAIN_KERNEL, &nkeys);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("ks_get_nof_keys failed (%d)\n", res);
			return res;
		}
		for (i = 0; i < nkeys; i++) {
			ks_get_key_by_index(keystore_hdl,
					KEYSTORE_DOMAIN_KERNEL, i, &blob);
			if (blob.type == KS_KEY_TYPE_CERT) {
				memcpy(&buffer[buffer_len],
				       blob.blob, blob.size);
				buffer_len += blob.size;
			}
		}
	}

	/* copy ks cert for LOADER KERNEL */
	if (usage == RULE_USAGE_LOADER_KERNEL && keystore_hdl) {
		res = ks_get_nof_keys(
			keystore_hdl, KEYSTORE_DOMAIN_XFL, &nkeys);
		if (res != FCSERR_OK) {
			FCS_LOG_WRN("No key in keystore for xfl (%d)\n", res);
			/* Don't return. Check for embedded certs */
		} else {
			for (i = 0; i < nkeys; i++) {
				ks_get_key_by_index(keystore_hdl,
						KEYSTORE_DOMAIN_XFL, i, &blob);
				if (blob.type == KS_KEY_TYPE_CERT) {
					memcpy(&buffer[buffer_len],
					       blob.blob, blob.size);
					buffer_len += blob.size;
				}
			}
		}
	}

	/* Find embedded roots with correct usage and copy to buffer */
	for (i = 0; i < embed_rootcert_list_count; i++) {
		usage_flags = embed_rootcert_list[i].usage_flags;
		if (usage == (usage_flags & usage)) {
			memcpy(&buffer[buffer_len],
				embed_rootcert_list[i].rootcerts,
				embed_rootcert_list[i].rootcerts_length);
			buffer_len += embed_rootcert_list[i].rootcerts_length;
		}
	}
	/* The final implementation will also use KeyStore (KM) */
	*rootcert = buffer;
	*rootcert_length = buffer_len;

	res = FCSERR_OK;

rule_get_roots_exit:
	return res;
}
