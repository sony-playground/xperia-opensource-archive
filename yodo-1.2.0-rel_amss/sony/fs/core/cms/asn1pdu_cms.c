/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "asn1pdu_cms.h"

/*
 * DESCRIPTION:
 *   This file contains format definition of CMS (RFC5652).
 *
 */

static const struct asn1_item asn1pdu_cms_content_sd_eci_items[] = {
	{
		.param = 0,
		.name = "eContentType",
		.handler = type_handler_any,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = ASN1ITEM_PARAM_OPTIONAL | 0xA0,
		.name = "eContent",
		.handler = type_handler_octet,
		.items_count = 0,
		.items = NULL
	}
};

static const struct asn1_item asn1pdu_cms_cert_choice_items[] = {
	{
		.param = 0,
		.name = "certificate",
		.handler = type_handler_any,
		.items_count = 0,
		.items = NULL
	}
};

static const struct asn1_item asn1pdu_cms_cert_choices[] = {
	{
		.param = 0,
		.name = "certificate_choice",
		.handler = type_handler_choice,
		.items_count = sizeof(asn1pdu_cms_cert_choice_items)/
				sizeof(struct asn1_item),
		.items = asn1pdu_cms_cert_choice_items
	}
};

static const struct asn1_item asn1pdu_cms_attribute_value[] = {
	{
		.param = 0,
		.name = "attrValue",
		.handler = type_handler_any,
		.items_count = 0,
		.items = NULL
	}
};

static const struct asn1_item asn1pdu_cms_attribute[] = {
	{
		.param = 0,
		.name = "attrType",
		.handler = type_handler_object,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = 0,
		.name = "attrValues",
		.handler = type_handler_set_of,
		.items_count = sizeof(asn1pdu_cms_attribute_value)/
				sizeof(struct asn1_item),
		.items = asn1pdu_cms_attribute_value
	}
};

static const struct asn1_item asn1pdu_cms_content_sd_si_sa_set[] = {
	{
		.param = 0,
		.name = "signedAttr",
		.handler = type_handler_seq,
		.items_count = sizeof(asn1pdu_cms_attribute)/
				sizeof(struct asn1_item),
		.items = asn1pdu_cms_attribute
	}
};

static const struct asn1_item asn1pdu_cms_content_sd_si[] = {
	{
		.param = 0,
		.name = "version",
		.handler = type_handler_any,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = 0,
		.name = "sid",
		.handler = type_handler_any,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = 0,
		.name = "digestAlgorithm",
		.handler = type_handler_any,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = ASN1ITEM_PARAM_OPTIONAL |
				ASN1ITEM_PARAM_IMPLICIT | 0xA0,
		.name = "signedAttrs",
		.handler = type_handler_set_of,
		.items_count = sizeof(asn1pdu_cms_content_sd_si_sa_set)/
				sizeof(struct asn1_item),
		.items = asn1pdu_cms_content_sd_si_sa_set
	},
	{
		.param = 0,
		.name = "signatureAlgorithm",
		.handler = type_handler_any,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = 0,
		.name = "signature",
		.handler = type_handler_octet,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = ASN1ITEM_PARAM_OPTIONAL |
				ASN1ITEM_PARAM_IMPLICIT | 0xA1,
		.name = "unsignedAttrs",
		.handler = type_handler_any,
		.items_count = 0,
		.items = NULL
	}
};

static const struct asn1_item asn1pdu_cms_content_sd_sis[] = {
	{
		.param = 0,
		.name = "signerInfo",
		.handler = type_handler_seq,
		.items_count = sizeof(asn1pdu_cms_content_sd_si)/
				sizeof(struct asn1_item),
		.items =  asn1pdu_cms_content_sd_si
	}
};

static const struct asn1_item asn1pdu_cms_content_sd_items[] = {
	{
		.param = 0,
		.name = "version",
		.handler = type_handler_any,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = 0,
		.name = "digestAlgorithms",
		.handler = type_handler_any,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = 0,
		.name = "encapsulatedContentInfo",
		.handler = type_handler_seq,
		.items_count = sizeof(asn1pdu_cms_content_sd_eci_items)/
				sizeof(struct asn1_item),
		.items =  asn1pdu_cms_content_sd_eci_items
	},
	{
		.param = ASN1ITEM_PARAM_OPTIONAL |
			ASN1ITEM_PARAM_IMPLICIT | 0xA0,
		.name = "certificates",
		.handler = type_handler_set_of,
		.items_count = sizeof(asn1pdu_cms_cert_choices)/
				sizeof(struct asn1_item),
		.items = asn1pdu_cms_cert_choices
	},
	{
		.param = ASN1ITEM_PARAM_OPTIONAL |
			ASN1ITEM_PARAM_IMPLICIT | 0xA1,
		.name = "crls",
		.handler = type_handler_any,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = 0,
		.name = "signerInfos",
		.handler = type_handler_set_of,
		.items_count = sizeof(asn1pdu_cms_content_sd_sis)/
				sizeof(struct asn1_item),
		.items = asn1pdu_cms_content_sd_sis
	}
};

static const struct asn1_item asn1pdu_cms_items[] = {
	{
		.param = 0,
		.name = "contentType",
		.handler = type_handler_any,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = 0xA0,
		.name = "content",
		.handler = type_handler_seq,
		.items_count = sizeof(asn1pdu_cms_content_sd_items)/
				sizeof(struct asn1_item),
		.items = asn1pdu_cms_content_sd_items
	}
};

const struct asn1_item asn1pdu_cms[] = {
	{
		.param = 0,
		.name = "cms",
		.handler = type_handler_seq,
		.items_count = sizeof(asn1pdu_cms_items)/
				sizeof(struct asn1_item),
		.items = asn1pdu_cms_items
	}
};

const char *ASN1PDU_MATCH_CMS_CNTTYPE[] = {
	"cms", "contentType", "\0" };
const char *ASN1PDU_MATCH_CMS_SIGN_VERSION[] = {
	"cms", "content", "version", "\0" };
const char *ASN1PDU_MATCH_CMS_SIGN_DIGESTALG[] = {
	"cms", "content", "digestAlgorithms", "\0" };
const char *ASN1PDU_MATCH_CMS_SD_ENCAP_CNTTYPE[] = {
	"encapsulatedContentInfo", "eContentType", "\0" };
const char *ASN1PDU_MATCH_CMS_SD_ENCAP_CNT[] = {
	"encapsulatedContentInfo", "eContent", "\0" };
const char *ASN1PDU_MATCH_CMS_SD_SI_VERSION[] = {
	"signerInfos", "signerInfo", "version", "\0" };
const char *ASN1PDU_MATCH_CMS_SD_SI_DIGESTALG[] = {
	"signerInfos", "signerInfo", "digestAlgorithm", "\0" };

const char *ASN1PDU_MATCH_CMS_CERT[] = {
	"certificates", "certificate_choice", "certificate", "\0" };
const char *ASN1PDU_MATCH_CMS_SIGNATTRS[] = {
	"signerInfos", "signerInfo", "signedAttrs", "\0" };
const char *ASN1PDU_MATCH_CMS_SIGNALG[] = {
	"signerInfos", "signerInfo", "signatureAlgorithm", "\0" };
const char *ASN1PDU_MATCH_CMS_SIGNATURE[] = {
	"signerInfos", "signerInfo", "signature", "\0" };
const char *ASN1PDU_MATCH_CMS_SIGNATTR[] = {
	"signerInfos", "signerInfo", "signedAttrs", "signedAttr", "\0" };
const char *ASN1PDU_MATCH_CMS_ATTR_TYPE[] = {
	"attrType", "\0" };
const char *ASN1PDU_MATCH_CMS_ATTR_VALUE[] = {
	"attrValues", "attrValue", "\0" };

/* contentType: id-signedData */
const uint8_t asn1pdu_cms_expect_contentType[] = {
	0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d,
	0x01, 0x07, 0x02
};
size_t asn1pdu_cms_expect_contentType_len =
	sizeof(asn1pdu_cms_expect_contentType);

/* SignedData: version */
const uint8_t asn1pdu_cms_expect_signdata_version[] = {
	0x02, 0x01, 0x01
};
size_t asn1pdu_cms_expect_signdata_version_len =
	sizeof(asn1pdu_cms_expect_signdata_version);

/* SignedData: digestAlgorithms */
const uint8_t asn1pdu_cms_expect_signdata_digestalg[] = {
	0x31, 0x0d, 0x30, 0x0b, 0x06, 0x09, 0x60, 0x86,
	0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01
};
size_t asn1pdu_cms_expect_signdata_digestalg_len =
	sizeof(asn1pdu_cms_expect_signdata_digestalg);

/* SignedData.EncapsulatedContentInfo: contentType (data) */
const uint8_t asn1pdu_cms_expect_sd_encap_contentType[] = {
	0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d,
	0x01, 0x07, 0x01
};
size_t asn1pdu_cms_expect_sd_encap_contentType_len =
	sizeof(asn1pdu_cms_expect_sd_encap_contentType);

/* SignedData.SignerInfo: version */
const uint8_t asn1pdu_cms_expect_sd_si_version[] = {
	0x02, 0x01, 0x01
};
size_t asn1pdu_cms_expect_sd_si_version_len =
	sizeof(asn1pdu_cms_expect_sd_si_version);

/* SignedData.SignerInfo: digest algorithm (sha256) */
const uint8_t asn1pdu_cms_expect_sd_si_digestalg[] = {
	0x30, 0x0b, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01,
	0x65, 0x03, 0x04, 0x02, 0x01
};
size_t asn1pdu_cms_expect_sd_si_digestalg_len =
	sizeof(asn1pdu_cms_expect_sd_si_digestalg);

/* Object identifier: id-contentType */
const uint8_t asn1pdu_cms_object_contentType[] = {
	0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x09, 0x03
};
size_t asn1pdu_cms_object_contentType_len =
	sizeof(asn1pdu_cms_object_contentType);

/* Object identifier: id-data */
const uint8_t asn1pdu_cms_object_id_data[] = {
	0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x07, 0x01
};
size_t asn1pdu_cms_object_id_data_len =
	sizeof(asn1pdu_cms_object_id_data);

/* Object identifier: id-messageDigest */
const uint8_t asn1pdu_cms_object_digest_payload[] = {
	0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x09, 0x04
};
size_t asn1pdu_cms_object_digest_payload_len =
	sizeof(asn1pdu_cms_object_digest_payload);

/* Object identifier: id-signingTime */
const uint8_t asn1pdu_cms_object_sign_time[] = {
	0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x09,
	0x05
};
size_t asn1pdu_cms_object_sign_time_len =
	sizeof(asn1pdu_cms_object_sign_time);

/* SignedData.SignerInfo: signatureAlgorithm (pkcs1) */
const uint8_t asn1pdu_cms_signalg_pkcs1[] = {
	0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86,
	0xf7, 0x0d, 0x01, 0x01, 0x01, 0x05, 0x00
};
size_t asn1pdu_cms_signalg_pkcs1_len =
	sizeof(asn1pdu_cms_signalg_pkcs1);

/* SignedData.SignerInfo: signatureAlgorithm (rsassa_pss) */
const uint8_t asn1pdu_cms_signalg_rsassa_pss[] = {
	0x30, 0x3e, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86,
	0xf7, 0x0d, 0x01, 0x01, 0x0a, 0x30, 0x31, 0xa0,
	0x0d, 0x30, 0x0b, 0x06, 0x09, 0x60, 0x86, 0x48,
	0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0xa1, 0x1a,
	0x30, 0x18, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86,
	0xf7, 0x0d, 0x01, 0x01, 0x08, 0x30, 0x0b, 0x06,
	0x09, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04,
	0x02, 0x01, 0xa2, 0x04, 0x02, 0x02, 0x00, 0xde
};
const uint8_t asn1pdu_cms_signalg_rsassa_pss_4k[] = {
	0x30, 0x3e, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86,
	0xf7, 0x0d, 0x01, 0x01, 0x0a, 0x30, 0x31, 0xa0,
	0x0d, 0x30, 0x0b, 0x06, 0x09, 0x60, 0x86, 0x48,
	0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0xa1, 0x1a,
	0x30, 0x18, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86,
	0xf7, 0x0d, 0x01, 0x01, 0x08, 0x30, 0x0b, 0x06,
	0x09, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04,
	0x02, 0x01, 0xa2, 0x04, 0x02, 0x02, 0x01, 0xde
};
size_t asn1pdu_cms_signalg_rsassa_pss_len =
	sizeof(asn1pdu_cms_signalg_rsassa_pss);

