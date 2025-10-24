/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "asn1pdu_ks.h"

/*
 * DESCRIPTION:
 *   This file contains format definition of KeyStore.
 *
 */

static const struct asn1_item asn1pdu_ks_db_entry_data[] = {
	{
		.param = 0xA0,
		.name = "certificate",
		.handler = type_handler_octet,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = 0xA1,
		.name = "publickey",
		.handler = type_handler_octet,
		.items_count = 0,
		.items = NULL
	}
};

static const struct asn1_item asn1pdu_ks_db_entry_items[] = {
	{
		.param = 0,
		.name = "domain",
		.handler = type_handler_int,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = 0,
		.name = "data",
		.handler = type_handler_choice,
		.items_count = sizeof(asn1pdu_ks_db_entry_data)/
				sizeof(struct asn1_item),
		.items = asn1pdu_ks_db_entry_data
	}
};

static const struct asn1_item asn1pdu_ks_db_entry[] = {
	{
		.param = 0,
		.name = "entry",
		.handler = type_handler_seq,
		.items_count = sizeof(asn1pdu_ks_db_entry_items)/
				sizeof(struct asn1_item),
		.items = asn1pdu_ks_db_entry_items
	}
};

static const struct asn1_item asn1pdu_ks_items[] = {
	{
		.param = 0,
		.name = "version",
		.handler = type_handler_any,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = 0,
		.name = "xcs",
		.handler = type_handler_bool,
		.items_count = 0,
		.items = NULL
	},

	{
		.param = 0,
		.name = "db",
		.handler = type_handler_seq_of,
		.items_count = sizeof(asn1pdu_ks_db_entry)/
				sizeof(struct asn1_item),
		.items = asn1pdu_ks_db_entry
	}
};

const struct asn1_item asn1pdu_ks[] = {
	{
		.param = 0,
		.name = "keystore",
		.handler = type_handler_seq,
		.items_count = sizeof(asn1pdu_ks_items)/
				sizeof(struct asn1_item),
		.items = asn1pdu_ks_items
	}
};

const char *ASN1PDU_MATCH_KS_VERSION[] = {
	"keystore", "version", "\0" };
const char *ASN1PDU_MATCH_KS_XCS[] = {
	"keystore", "xcs", "\0" };
const char *ASN1PDU_MATCH_KS_DB_ENTRY[] = {
	"keystore", "db", "entry", "\0" };
const char *ASN1PDU_MATCH_KS_DB_ENTRY_DOMAIN[] = {
	"entry", "domain", "\0" };
const char *ASN1PDU_MATCH_KS_DB_ENTRY_CERTIFICATE[] = {
	"entry", "data", "certificate", "\0" };
const char *ASN1PDU_MATCH_KS_DB_ENTRY_PUBLICKEY[] = {
	"entry", "data", "publickey", "\0" };

/* KeyStore: version */
const uint8_t asn1pdu_ks_expect_version[] = {
	0x02, 0x01, 0x01
};
size_t asn1pdu_ks_expect_version_len =
	sizeof(asn1pdu_ks_expect_version);

