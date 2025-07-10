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
 *   This interface contains constants for rule validation.                   *
 *                                                                            *
 *****************************************************************************/
#ifndef RULE_TYPES_H_
#define RULE_TYPES_H_

#include <stdlib.h>
#include <stdint.h>

/**
 *  Image usages flags.
 */
#define RULE_USAGE_NONE			((uint32_t)0x0)
#define RULE_USAGE_HWCONFIG		((uint32_t)0x1)
#define RULE_USAGE_SIMLOCK		((uint32_t)0x2)
#define RULE_USAGE_LOADER_KERNEL	((uint32_t)0x4)
#define RULE_USAGE_NORMAL_KERNEL	((uint32_t)0x8)
#define RULE_USAGE_FOTA_KERNEL		((uint32_t)0x10)
#define RULE_USAGE_RAMDUMP_KERNEL	((uint32_t)0x20)
#define RULE_USAGE_FLASH		((uint32_t)0x40)
#define RULE_USAGE_PARTTBL		((uint32_t)0x80)
#define RULE_USAGE_KEYSTORE		((uint32_t)0x100)
#define RULE_USAGE_FOTA			((uint32_t)0x200)
#define RULE_USAGE_RLOCK		((uint32_t)0x400)
#define RULE_USAGE_VBMETA		((uint32_t)0x800)

/**
 *  Root cert type flags.
 */
#define CERT_DOMAIN_OTHER		((uint8_t)0x0)
#define CERT_DOMAIN_S1			((uint8_t)0x1)
#define CERT_DOMAIN_CONFIG		((uint8_t)0x2)

/**
 *  Keystore domains.
 */
#define KEYSTORE_DOMAIN_FLASH  ((uint8_t)0)
#define KEYSTORE_DOMAIN_KERNEL ((uint8_t)1)
#define KEYSTORE_DOMAIN_XFL    ((uint8_t)3)
#define KEYSTORE_DOMAIN_SAKE   ((uint8_t)4)
#define KEYSTORE_DOMAIN_VBMETA ((uint8_t)5)

/**
 *  Embedded root certificate item for a usage.
 *  The rootcert is a buffer of DER encoded certificates. ASN1 sizes
 *  separate the certificates.
 *  An usage occupies one bit of usage_flags (See RULE_USAGE_*).
 *  A root cert type occupies one bit of cert_domain_flags
 *  (See CERT_DOMAIN_*).
 */
struct embed_rootcert_item {
	uint32_t usage_flags;
	const uint8_t *rootcerts;
	size_t rootcerts_length;
	uint8_t cert_domain_flags;
};


#endif /* RULE_TYPES_H_ */
