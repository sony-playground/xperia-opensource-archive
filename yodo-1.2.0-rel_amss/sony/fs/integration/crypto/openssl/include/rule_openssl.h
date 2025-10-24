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
 ******************************************************************************
 * DESCRIPTION:                                                               *
 *   The Rule Verifier is responsible for verifying SOMC specific rules       *
 *   concerning usage of image and binding towards devices.                   *
 *   This file contains the interface setup common openssl specific rule      *
 *   implementation                                                           *
 *                                                                            *
 *****************************************************************************/
#ifndef RULE_OPENSSL_H_
#define RULE_OPENSSL_H_

#include "rule_verifier_intern.h"
#include <openssl/x509.h>

struct rule_attribute *rule_openssl_create_attribute(
		X509_ATTRIBUTE * attr_in);

void rule_openssl_delete_attribute(
		struct rule_attribute *attribute);

int rule_openssl_setup_root_store(X509_STORE **root_store,
	uint8_t                *rootcerts,
	size_t                  rootcerts_length,
	struct rule_verifier *rule_handle);

#endif /* RULE_OPENSSL_H_ */
