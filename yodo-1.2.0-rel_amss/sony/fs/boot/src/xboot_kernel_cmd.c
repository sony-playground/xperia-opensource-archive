/*
 * Copyright (c) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <string.h>
#include "fcserr.h"
#include "fcslog.h"
#include "xboot_kernel_cms.h"
#include "eroot.h"
#include "rule_rootcert.h"
#include "rule_verifier.h"
#include "digest.h"
#include "cms_verifier.h"

int xboot_get_cms_len(uint8_t *cms_hdr, uint16_t *cms_len)
{
	if (cms_len == NULL) {
		FCS_LOG_ERR("Invalid parameter\n");
		return -FCSERR_EINVAL;
	}

	if (cms_hdr[0] != 0x30 || cms_hdr[1] != 0x82) {
		FCS_LOG_ERR("Invalid cms header info\n");
		return -FCSERR_EMAGIC;
	}

	*cms_len = (uint16_t)cms_hdr[2] << 8 | cms_hdr[3];

	return FCSERR_OK;
}

int xboot_verify_kernel_cms(uint8_t *kernel_buf, size_t kernel_len,
		uint8_t *cms_buf, uint16_t cms_len,
		uint32_t usage, struct xboot_ctx *boot_ctx)
{
	int res;
	struct embed_rootcert_item *embed_rootcert_list = NULL;
	size_t embed_rootcert_list_count = 0;
	uint8_t *rootcerts = NULL;
	size_t rootcerts_length = 0;
	struct rule_verifier *rule_handle = NULL;
	struct dev_binding binding = {};
	uint8_t *embedded_payload = NULL;
	size_t embedded_payload_length = 0;

	if (kernel_buf == NULL || kernel_len == 0 || cms_buf == NULL ||
			cms_len == 0 || boot_ctx == NULL) {
		FCS_LOG_ERR("Invalid parameter\n");
		return -FCSERR_EINVAL;
	}

	res = get_embedded_roots(
		&embed_rootcert_list, &embed_rootcert_list_count);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get embedded_roots from env: (%d)\n",
			res);
		goto exit;
	}

	res = rule_get_roots(usage,
			embed_rootcert_list,
			embed_rootcert_list_count,
			boot_ctx->ks,
			&rootcerts,
			&rootcerts_length);
	if (res < 0) {
		FCS_LOG_ERR("Failed to get roots: (%d)\n", res);
		goto exit;
	}

	res = rule_init(&rule_handle, &binding, usage);
	if (res < 0) {
		FCS_LOG_ERR("Failed to init rule session: (%d)\n", res);
		goto exit;
	}

	res = cms_verify(cms_buf, cms_len,
				rule_handle,
				rootcerts, rootcerts_length,
				NULL, 0,
				&embedded_payload, &embedded_payload_length);
	if (res < 0) {
		FCS_LOG_ERR("Failed to verify cms: (%d)\n", res);
		goto exit;
	}

	res = digest_sha256_verify(kernel_buf, kernel_len, embedded_payload);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to verify sha256 hash: (%d)\n", res);
		goto exit;
	}

exit:
	free_embedded_roots(&embed_rootcert_list);
	free(rootcerts);
	rule_deinit(rule_handle);
	free(embedded_payload);
	return res;
}
