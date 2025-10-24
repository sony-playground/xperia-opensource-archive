/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <rule_types.h>
#include "fcsenv_def.h"
#include "s1_root_cert_test.h"
#include "s1_root_cert_live.h"
#include "x_keystore_root_cert_test.h"
#include "x_keystore_root_cert_live.h"
#include "x_xfl_root_cert_live.h"
#include "x_xfl_root_cert_test.h"
#include "fcserr.h"
#include "fcslog.h"
#include "core.h"

#define NBR_OF_CERT_PROD 3
#define NBR_OF_CERT_TEST 6

void fcsenv_free_embedded_roots(
		struct embed_rootcert_item *fcsenv_embedded_roots)
{
	free(fcsenv_embedded_roots);
}

struct embed_rootcert_item *fcsenv_get_embedded_roots(size_t *number_of_roots)
{
	int res = FCSERR_OK;
	static struct embed_rootcert_item *fcsenv_embedded_roots;
	uint32_t hwid;

	res = core_get_hwid(&hwid);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get hwid (%d)\n", res);
		return NULL;
	}

	if (hwid != 0) {
		FCS_LOG_INF("Unit is fused with hwid != 0\n");
		*number_of_roots = NBR_OF_CERT_PROD;
		fcsenv_embedded_roots = (struct embed_rootcert_item *)malloc(
			NBR_OF_CERT_PROD * sizeof(struct embed_rootcert_item));

	} else {
		FCS_LOG_INF("Unit is not fused or fused with hwid 0\n");
		*number_of_roots = NBR_OF_CERT_TEST;
		fcsenv_embedded_roots = (struct embed_rootcert_item *)malloc(
			NBR_OF_CERT_TEST * sizeof(struct embed_rootcert_item));
	}
	if (fcsenv_embedded_roots == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		res = -FCSERR_ENOMEM;
		*number_of_roots = 0;
		goto fail;
	}

	/* Live S1 root */
	fcsenv_embedded_roots[0].usage_flags = EROOT_CERT_S1_USAGE;
	fcsenv_embedded_roots[0].rootcerts = s1_root_cert_live;
	fcsenv_embedded_roots[0].rootcerts_length = sizeof(s1_root_cert_live);

	/* Live keystore root */
	fcsenv_embedded_roots[1].usage_flags = EROOT_CERT_XKEYSTORE_USAGE;
	fcsenv_embedded_roots[1].rootcerts = x_keystore_root_cert_live;
	fcsenv_embedded_roots[1].rootcerts_length =
		sizeof(x_keystore_root_cert_live);

	/* Live XFL root */
	fcsenv_embedded_roots[2].usage_flags = EROOT_CERT_XFL_USAGE;
	fcsenv_embedded_roots[2].rootcerts = x_xfl_root_cert_live;
	fcsenv_embedded_roots[2].rootcerts_length =
		sizeof(x_xfl_root_cert_live);

	/* if fused unit, return here and do not att more roots */
	if (hwid != 0)
		return fcsenv_embedded_roots;

	/* Test S1 root */
	fcsenv_embedded_roots[3].usage_flags = EROOT_CERT_S1_USAGE;
	fcsenv_embedded_roots[3].rootcerts = s1_root_cert_test;
	fcsenv_embedded_roots[3].rootcerts_length = sizeof(s1_root_cert_test);

	/* Test keystore root */
	fcsenv_embedded_roots[4].usage_flags = EROOT_CERT_XKEYSTORE_USAGE;
	fcsenv_embedded_roots[4].rootcerts = x_keystore_root_cert_test;
	fcsenv_embedded_roots[4].rootcerts_length =
		sizeof(x_keystore_root_cert_test);

	/* Test XFL root */
	fcsenv_embedded_roots[5].usage_flags = EROOT_CERT_XFL_USAGE;
	fcsenv_embedded_roots[5].rootcerts = x_xfl_root_cert_test;
	fcsenv_embedded_roots[5].rootcerts_length =
		sizeof(x_xfl_root_cert_test);

fail:
	return fcsenv_embedded_roots;
}
