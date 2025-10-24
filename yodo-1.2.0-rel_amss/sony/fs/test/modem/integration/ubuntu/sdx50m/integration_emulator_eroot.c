/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#include "integration_eroot.h"
#include "s1_root_cert_test.h"
#include "x_xfl_root_cert_test.h"
#include "x_conf_root_cert_test.h"
#include "fcserr.h"
#include "rule_types.h"
#include <malloc.h>
#include <string.h>

#include ROOT_USAGE_HWCONF

#define INTEMUL_CERT_COUNT 3
#define INTEMUL_CERT_S1_USAGE (\
	INTEMUL_CERT_S1_USAGE_HWCONF |\
	RULE_USAGE_SIMLOCK |\
	RULE_USAGE_RLOCK |\
	RULE_USAGE_FOTA)
#define INTEMUL_CERT_CONFIG_USAGE (\
	INTEMUL_CERT_CONFIG_USAGE_HWCONF |\
	RULE_USAGE_KEYSTORE)
#define INTEMUL_CERT_XFL_USAGE RULE_USAGE_LOADER_KERNEL

static int intemul_eroot_get(
		struct integration_eroot_context *context,
		struct embed_rootcert_item **embed_rootcert_list,
		size_t *embed_rootcert_list_count)
{
	struct embed_rootcert_item *embedded_roots = NULL;

	if ((context == NULL) ||
			(embed_rootcert_list == NULL) ||
			(embed_rootcert_list_count == NULL))
		return -FCSERR_EINVAL;

	embedded_roots = (struct embed_rootcert_item *)malloc(
		INTEMUL_CERT_COUNT * sizeof(struct embed_rootcert_item));
	if (embedded_roots == NULL)
		return -FCSERR_ENOMEM;

	/* Test S1 root */
	embedded_roots[0].usage_flags = INTEMUL_CERT_S1_USAGE;
	embedded_roots[0].rootcerts = s1_root_cert_test;
	embedded_roots[0].rootcerts_length = sizeof(s1_root_cert_test);

	/* Test Config Root */
	embedded_roots[1].usage_flags = INTEMUL_CERT_CONFIG_USAGE;
	embedded_roots[1].rootcerts = x_conf_root_cert_test;
	embedded_roots[1].rootcerts_length = sizeof(x_conf_root_cert_test);

	/* Test XFL root */
	embedded_roots[2].usage_flags = INTEMUL_CERT_XFL_USAGE;
	embedded_roots[2].rootcerts = x_xfl_root_cert_test;
	embedded_roots[2].rootcerts_length =
		sizeof(x_xfl_root_cert_test);

	*embed_rootcert_list = embedded_roots;
	*embed_rootcert_list_count = INTEMUL_CERT_COUNT;

	return FCSERR_OK;
}

static void intemul_eroot_free(
		struct integration_eroot_context *context,
		struct embed_rootcert_item **rootcert_list)
{
	if (rootcert_list != NULL) {
		free(*rootcert_list);
		*rootcert_list = NULL;
	}
}

const struct integration_eroot_func intemul_eroot_func = {
	.get = intemul_eroot_get,
	.free = intemul_eroot_free
};

