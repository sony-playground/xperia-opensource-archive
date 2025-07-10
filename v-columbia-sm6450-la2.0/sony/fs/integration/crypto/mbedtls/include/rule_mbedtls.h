/******************************************************************************
 *                     ____                                                   *
 *                    / ___|  ___  _ __                                       *
 *                    \___ \ / _ \| '_ \| | | |                               *
 *                    ___ ) | (_) | | | | |_| |                               *
 *                    |____/ \___/|_| |_|\__, |                               *
 *                                        |___/                               *
 *                                                                            *
 ******************************************************************************
 * Copyright (c) 2017 Sony Mobile Communications Inc.                         *
 * All rights, including trade secret rights, reserved.                       *
 ******************************************************************************
 * DESCRIPTION:                                                               *
 *   The Rule Verifier is responsible for verifying SOMC specific rules       *
 *   concerning usage of image and binding towards devices.                   *
 *   This file contains the interface setup common mbedtls specific rule      *
 *   implementation                                                           *
 *                                                                            *
 *****************************************************************************/
#ifndef RULE_MBEDTLS_H_
#define RULE_MBEDTLS_H_

#include "rule_verifier_intern.h"
#include <mbedtls/x509_crt.h>

int rule_mbedtls_verify_cb(
		void *context,
		mbedtls_x509_crt *cur_cert,
		int depth,
		uint32_t *flags);

#endif /* RULE_MBEDTLS_H_ */
