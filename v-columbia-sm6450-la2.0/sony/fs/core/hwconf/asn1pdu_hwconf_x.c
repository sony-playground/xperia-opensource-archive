/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "asn1pdu_hwconf_x.h"

/*
 * DESCRIPTION:
 *   This file contains format definition of HwConfig X.
 *
 */

static const struct asn1_item asn1pdu_hwconf_x_imei[] = {
	{
		.param = 0,
		.name = "entry",
		.handler = type_handler_utf8,
		.items_count = 0,
		.items = NULL
	}
};

static const struct asn1_item asn1pdu_hwconf_x_items[] = {
	{
		.param = 0,
		.name = "version",
		.handler = type_handler_int,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = 0,
		.name = "isprototype",
		.handler = type_handler_bool,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = 0,
		.name = "imeilist",
		.handler = type_handler_seq_of,
		.items_count = sizeof(asn1pdu_hwconf_x_imei)/
				sizeof(struct asn1_item),
		.items = asn1pdu_hwconf_x_imei
	},
	{
		.param = 0,
		.name = "devicekey",
		.handler = type_handler_octet,
		.items_count = 0,
		.items = NULL
	}
};

const struct asn1_item asn1pdu_hwconf_x[] = {
	{
		.param = 0,
		.name = "hwconfig",
		.handler = type_handler_seq,
		.items_count = sizeof(asn1pdu_hwconf_x_items)/
				sizeof(struct asn1_item),
		.items = asn1pdu_hwconf_x_items
	}
};

const char *ASN1PDU_MATCH_HWCONF_X_VERSION[] = {
	"hwconfig", "version", "\0" };
const char *ASN1PDU_MATCH_HWCONF_X_ISPROTOTYPE[] = {
	"hwconfig", "isprototype", "\0" };
const char *ASN1PDU_MATCH_HWCONF_X_IMEILIST_ENTRY[] = {
	"hwconfig", "imeilist", "entry", "\0" };
const char *ASN1PDU_MATCH_HWCONF_X_DK[] = {
	"hwconfig", "devicekey", "\0" };

