/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#ifndef ASN1_PDU_CMS_H_
#define ASN1_PDU_CMS_H_

#include "der_parser.h"

extern const struct asn1_item asn1pdu_cms[];

extern const char *ASN1PDU_MATCH_CMS_CNTTYPE[];
extern const char *ASN1PDU_MATCH_CMS_SIGN_VERSION[];
extern const char *ASN1PDU_MATCH_CMS_SIGN_DIGESTALG[];
extern const char *ASN1PDU_MATCH_CMS_SD_ENCAP_CNTTYPE[];
extern const char *ASN1PDU_MATCH_CMS_SD_ENCAP_CNT[];
extern const char *ASN1PDU_MATCH_CMS_SD_SI_VERSION[];
extern const char *ASN1PDU_MATCH_CMS_SD_SI_DIGESTALG[];
extern const char *ASN1PDU_MATCH_CMS_CERT[];
extern const char *ASN1PDU_MATCH_CMS_SIGNATTRS[];
extern const char *ASN1PDU_MATCH_CMS_SIGNALG[];
extern const char *ASN1PDU_MATCH_CMS_SIGNATURE[];
extern const char *ASN1PDU_MATCH_CMS_SIGNATTR[];
extern const char *ASN1PDU_MATCH_CMS_ATTR_TYPE[];
extern const char *ASN1PDU_MATCH_CMS_ATTR_VALUE[];

/* contentType: id-signedData */
extern const uint8_t asn1pdu_cms_expect_contentType[];
extern size_t asn1pdu_cms_expect_contentType_len;

/* SignedData: version */
extern const uint8_t asn1pdu_cms_expect_signdata_version[];
extern size_t asn1pdu_cms_expect_signdata_version_len;

/* SignedData: digestAlgorithms */
extern const uint8_t asn1pdu_cms_expect_signdata_digestalg[];
extern size_t asn1pdu_cms_expect_signdata_digestalg_len;

/* SignedData.EncapsulatedContentInfo: contentType (data) */
extern const uint8_t asn1pdu_cms_expect_sd_encap_contentType[];
extern size_t asn1pdu_cms_expect_sd_encap_contentType_len;

/* SignedData.SignerInfo: version */
extern const uint8_t asn1pdu_cms_expect_sd_si_version[];
extern size_t asn1pdu_cms_expect_sd_si_version_len;

/* SignedData.SignerInfo: digest algorithm (sha256) */
extern const uint8_t asn1pdu_cms_expect_sd_si_digestalg[];
extern size_t asn1pdu_cms_expect_sd_si_digestalg_len;

/* Object identifier: id-contentType */
extern const uint8_t asn1pdu_cms_object_contentType[];
extern size_t asn1pdu_cms_object_contentType_len;

/* Object identifier: id-data */
extern const uint8_t asn1pdu_cms_object_id_data[];
extern size_t asn1pdu_cms_object_id_data_len;

/* Object identifier: id-messageDigest */
extern const uint8_t asn1pdu_cms_object_digest_payload[];
extern size_t asn1pdu_cms_object_digest_payload_len;

/* Object identifier: id-signingTime */
extern const uint8_t asn1pdu_cms_object_sign_time[];
extern size_t asn1pdu_cms_object_sign_time_len;

/* SignedData.SignerInfo: signatureAlgorithm (pkcs1) */
extern const uint8_t asn1pdu_cms_signalg_pkcs1[];
extern size_t asn1pdu_cms_signalg_pkcs1_len;

/* SignedData.SignerInfo: signatureAlgorithm (rsassa_pss) */
extern const uint8_t asn1pdu_cms_signalg_rsassa_pss[];
extern const uint8_t asn1pdu_cms_signalg_rsassa_pss_4k[];
extern size_t asn1pdu_cms_signalg_rsassa_pss_len;

#endif /* ASN1_PDU_CMS_H_ */
