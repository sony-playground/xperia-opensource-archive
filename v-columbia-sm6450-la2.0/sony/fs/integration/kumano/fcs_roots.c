/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <rule_types.h>
#include "s1_root_cert_test.h"
#include "s1_root_cert_live.h"
#include "x_xfl_root_cert_live.h"
#include "x_xfl_root_cert_test.h"
#include "x_conf_root_cert_live.h"
#include "x_conf_root_cert_test.h"
#include "eroot_int.h"

#define EROOT_CERT_CONFIG_USAGE (\
	RULE_USAGE_HWCONFIG |\
	RULE_USAGE_SIMLOCK |\
	RULE_USAGE_KEYSTORE)

#define EROOT_CERT_S1_USAGE (\
	RULE_USAGE_SIMLOCK |\
	RULE_USAGE_RLOCK |\
	RULE_USAGE_FOTA)

#define EROOT_CERT_XFL_USAGE RULE_USAGE_LOADER_KERNEL

/* Terminate the array by {RULE_USAGE_NONE, 0, 0, CERT_DOMAIN_OTHER} */

const struct embed_rootcert_item fcsenv_roots_live[] = {
	{EROOT_CERT_CONFIG_USAGE,
	 x_conf_root_cert_live, sizeof(x_conf_root_cert_live),
	 CERT_DOMAIN_CONFIG},
	{EROOT_CERT_S1_USAGE,
	 s1_root_cert_live, sizeof(s1_root_cert_live),
	 CERT_DOMAIN_S1},
	{EROOT_CERT_XFL_USAGE,
	 x_xfl_root_cert_live, sizeof(x_xfl_root_cert_live),
	 CERT_DOMAIN_OTHER},
	{RULE_USAGE_NONE, 0, 0, CERT_DOMAIN_OTHER}
};

const struct embed_rootcert_item fcsenv_roots_test[] = {
	{EROOT_CERT_CONFIG_USAGE,
	 x_conf_root_cert_test, sizeof(x_conf_root_cert_test),
	 CERT_DOMAIN_CONFIG},
	{EROOT_CERT_S1_USAGE,
	 s1_root_cert_test, sizeof(s1_root_cert_test),
	 CERT_DOMAIN_S1},
	{EROOT_CERT_XFL_USAGE,
	 x_xfl_root_cert_test, sizeof(x_xfl_root_cert_test),
	 CERT_DOMAIN_OTHER},
	{RULE_USAGE_NONE, 0, 0, CERT_DOMAIN_OTHER}
};

