/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#ifndef ASN1_PDU_RULE_H_
#define ASN1_PDU_RULE_H_

#include "der_parser.h"

extern const struct asn1_item asn1pdu_keyusage[];

extern const struct asn1_item asn1pdu_devicebinding[];

extern const struct asn1_item asn1pdu_signatureusage[];

extern const struct asn1_item asn1pdu_simlockprotection[];

extern const char *ASN1PDU_MATCH_HWC[];
extern const char *ASN1PDU_MATCH_SL[];
extern const char *ASN1PDU_MATCH_LOADER[];
extern const char *ASN1PDU_MATCH_NORMAL[];
extern const char *ASN1PDU_MATCH_FOTA[];
extern const char *ASN1PDU_MATCH_RAMDUMP[];
extern const char *ASN1PDU_MATCH_FLASH[];
extern const char *ASN1PDU_MATCH_KEYSTORE[];
extern const char *ASN1PDU_MATCH_RLOCK[];
extern const char *ASN1PDU_MATCH_BINDING_DEV_ID[];
extern const char *ASN1PDU_MATCH_BINDING_IMEI[];
extern const char *ASN1PDU_MATCH_BINDING_DEV_ID_LIST[];
extern const char *ASN1PDU_MATCH_SEQUENCE[];
extern const char *ASN1PDU_MATCH_START[];
extern const char *ASN1PDU_MATCH_LENGTH[];

#endif /* ASN1_PDU_RULE_H_ */
