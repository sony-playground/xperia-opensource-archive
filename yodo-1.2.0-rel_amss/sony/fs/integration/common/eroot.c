/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <eroot.h>
#include <rule_types.h>
#include <fcserr.h>
#include <fcslog.h>
#include <core.h>
#include <eroot_int.h>

static int get_nbr_certs(const struct embed_rootcert_item *rootcert_list)
{
	int i = 0;

	while (rootcert_list[i].usage_flags != RULE_USAGE_NONE)
		i++;

	return i;
}

static void add_certs(
	const struct embed_rootcert_item *src, struct embed_rootcert_item *dst)
{
	int i = 0;

	while (src[i].usage_flags != RULE_USAGE_NONE) {
		dst[i] = src[i];
		i++;
	}
}

int get_embedded_roots(
	struct embed_rootcert_item **rootcert_list,
	size_t *rootcert_list_count)
{
	int nlive;
	int ntest;
	int test_cert_allowed;

	/* Check in parameters */
	if (!rootcert_list || !rootcert_list_count) {
		FCS_LOG_ERR("Invalid parameter.\n");
		return -FCSERR_EINVAL;
	}

	nlive = get_nbr_certs(fcsenv_roots_live);
	ntest = get_nbr_certs(fcsenv_roots_test);

	test_cert_allowed = core_is_test_cert_allowed();
	if (test_cert_allowed != 1)
		FCS_LOG_INF("Test cert not allowed\n");
	else
		FCS_LOG_INF("Test cert allowed\n");

	if (test_cert_allowed != 1)
		*rootcert_list_count = nlive;
	else
		*rootcert_list_count = ntest + nlive;

	*rootcert_list = (struct embed_rootcert_item *)malloc(
		*rootcert_list_count * sizeof(struct embed_rootcert_item));

	if (!*rootcert_list) {
		FCS_LOG_ERR("Malloc failed\n");
		return -FCSERR_ENOMEM;
	}

	/* add all live certs */
	add_certs(fcsenv_roots_live, *rootcert_list);

	/* if fused unit, return here and do not add more roots */
	if (test_cert_allowed != 1)
		return FCSERR_OK;

	/* add all test certs */
	add_certs(fcsenv_roots_test, &((*rootcert_list)[nlive]));

	return FCSERR_OK;
}

void free_embedded_roots(struct embed_rootcert_item **rootcert_list)
{
	free(*rootcert_list);
}
