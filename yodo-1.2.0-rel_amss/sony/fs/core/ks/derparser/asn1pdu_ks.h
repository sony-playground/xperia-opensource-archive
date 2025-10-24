/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#ifndef ASN1_PDU_KS_H_
#define ASN1_PDU_KS_H_

#include "der_parser.h"

extern const struct asn1_item asn1pdu_ks[];

extern const char *ASN1PDU_MATCH_KS_VERSION[];
extern const char *ASN1PDU_MATCH_KS_XCS[];
extern const char *ASN1PDU_MATCH_KS_DB_ENTRY[];
extern const char *ASN1PDU_MATCH_KS_DB_ENTRY_DOMAIN[];
extern const char *ASN1PDU_MATCH_KS_DB_ENTRY_CERTIFICATE[];
extern const char *ASN1PDU_MATCH_KS_DB_ENTRY_PUBLICKEY[];

/* KeyStore: version */
extern const uint8_t asn1pdu_ks_expect_version[];
extern size_t asn1pdu_ks_expect_version_len;

#endif /* ASN1_PDU_KS_H_ */
