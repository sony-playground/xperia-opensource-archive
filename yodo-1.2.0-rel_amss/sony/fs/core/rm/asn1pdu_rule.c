/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "asn1pdu_rule.h"

/*
 * DESCRIPTION:
 *   This file contains format definition of certication extensions and
 *   signed attributes. Format definition document:
 *     git: platform/vendor/semc/s1/docs
 *     file: rearchitecture/keyusage.asn
 *
 */

static const struct asn1_item asn1pdu_boot_items[] = {
	{
		.param = 0,
		.name = "normal",
		.handler = type_handler_none,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = 0,
		.name = "fota",
		.handler = type_handler_none,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = 0,
		.name = "ramdumper",
		.handler = type_handler_none,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = 0,
		.name = "service",
		.handler = type_handler_none,
		.items_count = 0,
		.items = NULL
	}
};

static const struct asn1_item asn1pdu_config_items[] = {
	{
		.param = 0,
		.name = "simlock",
		.handler = type_handler_none,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = 0,
		.name = "hwconfig",
		.handler = type_handler_none,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = 0,
		.name = "keystore",
		.handler = type_handler_none,
		.items_count = 0,
		.items = NULL
	}
};

static const struct asn1_item asn1pdu_purpose_items[] = {
	{
		.param = 0,
		.name = "flash",
		.handler = type_handler_utf8,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = 0xA0,
		.name = "boot",
		.handler = type_handler_enum,
		.items_count = sizeof(asn1pdu_boot_items)/
				sizeof(struct asn1_item),
		.items = asn1pdu_boot_items
	},
	{
		.param = 0xA1,
		.name = "config",
		.handler = type_handler_enum,
		.items_count = sizeof(asn1pdu_config_items)/
				sizeof(struct asn1_item),
		.items = asn1pdu_config_items
	}
};

static const struct asn1_item asn1pdu_purpose[] = {
	{
		.param = 0,
		.name = "purpose",
		.handler = type_handler_choice,
		.items_count = sizeof(asn1pdu_purpose_items)/
				sizeof(struct asn1_item),
		.items = asn1pdu_purpose_items
	}
};

const struct asn1_item asn1pdu_keyusage[] = {
	{
		.param = 0,
		.name = "keyusage",
		.handler = type_handler_seq_of,
		.items_count = sizeof(asn1pdu_purpose)/
				sizeof(struct asn1_item),
		.items = asn1pdu_purpose
	}
};

static const struct asn1_item asn1pdu_binding_deviceidlist_item[] = {
	{
		.param = 0,
		.name = "deviceid",
		.handler = type_handler_octet,
		.items_count = 0,
		.items = NULL
	}
};

static const struct asn1_item asn1pdu_binding_items[] = {
	{
		.param = 0,
		.name = "deviceid",
		.handler = type_handler_octet,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = 0,
		.name = "imei",
		.handler = type_handler_utf8,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = 0,
		.name = "deviceidlist",
		.handler = type_handler_seq_of,
		.items_count = sizeof(asn1pdu_binding_deviceidlist_item)/
				sizeof(struct asn1_item),
		.items = asn1pdu_binding_deviceidlist_item
	}
};

const struct asn1_item asn1pdu_devicebinding[] = {
	{
		.param = 0,
		.name = "binding",
		.handler = type_handler_choice,
		.items_count = sizeof(asn1pdu_binding_items)/
				sizeof(struct asn1_item),
		.items = asn1pdu_binding_items
	}
};

static const struct asn1_item asn1pdu_signatureusage_items[] = {
	{
		.param = 0,
		.name = "purpose",
		.handler = type_handler_choice,
		.items_count = sizeof(asn1pdu_purpose_items)/
				sizeof(struct asn1_item),
		.items = asn1pdu_purpose_items
	},
	{
		.param = ASN1ITEM_PARAM_OPTIONAL,
		.name = "binding",
		.handler = type_handler_choice,
		.items_count = sizeof(asn1pdu_binding_items)/
				sizeof(struct asn1_item),
		.items = asn1pdu_binding_items
	},
	{
		.param = ASN1ITEM_PARAM_OPTIONAL,
		.name = "sequence",
		.handler = type_handler_int,
		.items_count = 0,
		.items = NULL
	}
};

const struct asn1_item asn1pdu_signatureusage[] = {
	{
		.param = 0,
		.name = "signatureusage",
		.handler = type_handler_seq,
		.items_count = sizeof(asn1pdu_signatureusage_items)/
				sizeof(struct asn1_item),
		.items = asn1pdu_signatureusage_items
	}
};

static const struct asn1_item asn1pdu_simlockprotection_items[] = {
	{
		.param = 0,
		.name = "start",
		.handler = type_handler_int,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = 0,
		.name = "length",
		.handler = type_handler_int,
		.items_count = 0,
		.items = NULL
	}
};

const struct asn1_item asn1pdu_simlockprotection[] = {
	{
		.param = 0,
		.name = "simlockprotection",
		.handler = type_handler_seq,
		.items_count = sizeof(asn1pdu_simlockprotection_items)/
				sizeof(struct asn1_item),
		.items = asn1pdu_simlockprotection_items
	}
};

const char *ASN1PDU_MATCH_HWC[] = {
	"purpose", "config", "hwconfig", "\0" };
const char *ASN1PDU_MATCH_SL[] = {
	"purpose", "config", "simlock", "\0" };
const char *ASN1PDU_MATCH_LOADER[] = {
	"purpose", "boot", "service", "\0" };
const char *ASN1PDU_MATCH_NORMAL[] = {
	"purpose", "boot", "normal", "\0" };
const char *ASN1PDU_MATCH_FOTA[] = {
	"purpose", "boot", "fota", "\0" };
const char *ASN1PDU_MATCH_RAMDUMP[] = {
	"purpose", "boot", "ramdumper", "\0" };
const char *ASN1PDU_MATCH_FLASH[] = {
	"purpose", "flash", "\0" };
const char *ASN1PDU_MATCH_KEYSTORE[] = {
	"purpose", "config", "keystore", "\0" };
const char *ASN1PDU_MATCH_RLOCK[] = {
	"purpose", "config", "rlock", "\0" };
const char *ASN1PDU_MATCH_BINDING_DEV_ID[] = {
	"binding", "deviceid", "\0" };
const char *ASN1PDU_MATCH_BINDING_IMEI[] = {
	"binding", "imei", "\0" };
const char *ASN1PDU_MATCH_BINDING_DEV_ID_LIST[] = {
	"binding", "deviceidlist", "deviceid", "\0" };
const char *ASN1PDU_MATCH_SEQUENCE[] = {
	"sequence", "\0" };
const char *ASN1PDU_MATCH_START[] = {
	"start", "\0" };
const char *ASN1PDU_MATCH_LENGTH[] = {
	"length", "\0" };
