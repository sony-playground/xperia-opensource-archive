/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "certificate_chain.h"
#include "rule_verifier_intern.h"
#include "fcserr.h"
#include "fcslog.h"
#include "der_parser.h"
#include "der_parser_utils.h"
#include <string.h>

static const struct asn1_item asn1pdu_attribute_items[] = {
	{
		.param =  0,
		.name = "type",
		.handler = type_handler_object,
		.items_count = 0,
		.items = NULL
	},
	{
		.param =  0,
		.name = "value",
		.handler = type_handler_any,
		.items_count = 0,
		.items = NULL
	}
};

static const struct asn1_item asn1pdu_attributes_items[] = {
	{
		.param =  0,
		.name = "attribute",
		.handler = type_handler_seq,
		.items_count = sizeof(asn1pdu_attribute_items)/
				sizeof(struct asn1_item),
		.items = asn1pdu_attribute_items
	}
};

static const struct asn1_item asn1pdu_rdnSequence_items[] = {
	{
		.param = 0,
		.name = "attributes",
		.handler = type_handler_set_of,
		.items_count = sizeof(asn1pdu_attributes_items)/
				sizeof(struct asn1_item),
		.items = asn1pdu_attributes_items
	}
};

static const struct asn1_item asn1pdu_name_items[] = {
	{
		.param = 0,
		.name = "rdnSequence",
		.handler = type_handler_seq,
		.items_count = sizeof(asn1pdu_rdnSequence_items)/
				sizeof(struct asn1_item),
		.items = asn1pdu_rdnSequence_items
	}
};

static const struct asn1_item asn1pdu_tbsCert_items[] = {
	{
		.param = 0xA0,
		.name = "version",
		.handler = type_handler_any,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = 0,
		.name = "serialNumber",
		.handler = type_handler_any,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = 0,
		.name = "signature",
		.handler = type_handler_any,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = 0,
		.name = "issuer",
		.handler = type_handler_choice,
		.items_count = sizeof(asn1pdu_name_items)/
				sizeof(struct asn1_item),
		.items = asn1pdu_name_items
	},
	{
		.param = 0,
		.name = "validity",
		.handler = type_handler_any,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = 0,
		.name = "subject",
		.handler = type_handler_choice,
		.items_count = sizeof(asn1pdu_name_items)/
				sizeof(struct asn1_item),
		.items = asn1pdu_name_items
	},
	{
		.param = 0,
		.name = "subjectPublicKeyInfo",
		.handler = type_handler_any,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = ASN1ITEM_PARAM_OPTIONAL |
			ASN1ITEM_PARAM_IMPLICIT | 0xA1,
		.name = "issuerUniqueID",
		.handler = type_handler_any,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = ASN1ITEM_PARAM_OPTIONAL |
			ASN1ITEM_PARAM_IMPLICIT | 0xA2,
		.name = "subjectUniqueID",
		.handler = type_handler_any,
		.items_count = 0,
		.items = NULL
	},
	{
		.param = ASN1ITEM_PARAM_OPTIONAL | 0xA3,
		.name = "extensions",
		.handler = type_handler_any,
		.items_count = 0,
		.items = NULL
	}
};

static const struct asn1_item asn1pdu_cert_items[] = {
	{
		.param =  0,
		.name = "tbsCertificate",
		.handler = type_handler_seq,
		.items_count = sizeof(asn1pdu_tbsCert_items)/
				sizeof(struct asn1_item),
		.items = asn1pdu_tbsCert_items
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
		.handler = type_handler_any,
		.items_count = 0,
		.items = NULL
	}
};

const struct asn1_item asn1pdu_simple_cert[] = {
	{
		.param = 0,
		.name = "certificate",
		.handler = type_handler_seq,
		.items_count = sizeof(asn1pdu_cert_items)/
				sizeof(struct asn1_item),
		.items = asn1pdu_cert_items
	}
};

const char *ASN1PDU_MATCH_CERT_SUBJECT[] = {
	"certificate", "tbsCertificate", "subject", "\0" };
const char *ASN1PDU_MATCH_CERT_ISSUER[] = {
	"certificate", "tbsCertificate", "issuer", "\0" };
const char *ASN1PDU_MATCH_CERT_NAME_ATTRIBUTE[] = {
	"rdnSequence", "attributes", "attribute", "\0" };
const char *ASN1PDU_MATCH_TYPE[] = {
	"type", "\0" };
const char *ASN1PDU_MATCH_VALUE[] = {
	"value", "\0" };

/* common name object id */
const uint8_t asn1pdu_cert_name_cn[] = {
	0x55, 0x04, 0x03
};


static int cc_create_first_cert_iterator(
		struct iterator_info **iterator,
		struct iterator_info *base_iterator)
{
	int res = -FCSERR_EINVAL;

	/* Set up initial iterator and do sanity check on content */
	res = derparser_create_subset_iterator(
			iterator,
			base_iterator,
			(const char **)(NULL));
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to create iterator\n");
		goto cc_exit;
	}
	res = derparser_next(*iterator, NULL);
	if (res < 0) {
		FCS_LOG_ERR("Failed to parse certificate\n");
		goto cc_exit;
	}
cc_exit:
	if (res != FCSERR_OK) {
		derparser_delete_iterator(*iterator);
		*iterator = NULL;
	}
	return res;
}

static int cc_create_next_cert_iterator(
		struct iterator_info **iterator,
		struct iterator_info *base_iterator)
{
	int res = -FCSERR_EINVAL;
	struct iterator_info *current_iterator = *iterator;
	struct iterator_info *next_iterator = NULL;

	/* Set up initial iterator and do sanity check on content */
	res = derparser_create_adjacent_iterator(
			&next_iterator,
			*iterator,
			base_iterator,
			(const char **)(NULL));
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to create iterator\n");
		goto cc_exit;
	}

	if (next_iterator == NULL) {
		*iterator = next_iterator;
		next_iterator = NULL;
		goto cc_exit;
	}

	res = derparser_next(next_iterator, NULL);
	if (res < 0) {
		FCS_LOG_ERR("Failed to parse certificate\n");
		goto cc_exit;
	}
	*iterator = next_iterator;
	next_iterator = NULL;
cc_exit:
	derparser_delete_iterator(current_iterator);
	derparser_delete_iterator(next_iterator);
	return res;
}

static int cc_find_name(
		struct iterator_info **name_iterator,
		struct iterator_info *base_iterator,
		const char **match,
		struct derparser_object *name)
{
	int res = -FCSERR_EINVAL;
	struct iterator_info *iterator = NULL;

	/* Set up initial iterator and do search */
	res = derparser_create_subset_iterator(
			&iterator,
			base_iterator,
			match);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to create iterator\n");
		goto cc_exit;
	}
	res = derparser_next(iterator, name);
	if (res < 0) {
		FCS_LOG_ERR("Failed to parse certificate\n");
		goto cc_exit;
	} else if (res == 0) {
		res = -FCSERR_ENOTF;
		FCS_LOG_ERR("Name was not found\n");
		goto cc_exit;
	}
	if (name_iterator != NULL) {
		*name_iterator = iterator;
		iterator = NULL;
	}
	res = FCSERR_OK;
cc_exit:
	derparser_delete_iterator(iterator);
	iterator = NULL;
	return res;
}

static bool cc_is_name_equal(
		struct derparser_object *name1,
		struct derparser_object *name2)
{
	uint8_t *name1_data;
	size_t name1_len;
	uint8_t *name2_data;
	size_t name2_len;

	name1_len = derparser_get_buffer(name1, &name1_data);
	name2_len = derparser_get_buffer(name2, &name2_data);
	if ((name1_len == name2_len) &&
			(memcmp(name1_data, name2_data, name1_len) == 0))
		return true;
	return false;
}

static int cc_send_cn_to_rm(
		struct rule_verifier *rule,
		unsigned int *level,
		struct iterator_info *base_iterator)
{
	int res = FCSERR_OK;
	struct iterator_info *iterator = NULL;
	uint8_t buffer[0x70];
	size_t buffer_len = 0;
	struct rule_cn cn_info;

	res = derparser_create_subset_iterator(
			&iterator,
			base_iterator,
			ASN1PDU_MATCH_CERT_NAME_ATTRIBUTE);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to create iterator for attribute\n");
		goto cc_exit;
	}
	while (true) {
		res = derparser_next(iterator, NULL);
		if (res < 0) {
			FCS_LOG_ERR("Failed to parse attribute\n");
			goto cc_exit;
		} else if (res == 0) {
			res = -FCSERR_ENOTF;
			FCS_LOG_ERR("Attribute was not found\n");
			goto cc_exit;
		}
		/* Get attribute type */
		res = derparser_util_get_buffer(
				iterator,
				ASN1PDU_MATCH_TYPE,
				buffer,
				0,
				sizeof(buffer),
				&buffer_len);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to get type\n");
			goto cc_exit;
		}
		/* Check if attribute is CN type */
		if (buffer_len != sizeof(asn1pdu_cert_name_cn))
			continue;
		if (memcmp(buffer,
				asn1pdu_cert_name_cn,
				buffer_len) != 0)
			continue;
		/* Get attribute value */
		res = derparser_util_get_buffer(
				iterator,
				ASN1PDU_MATCH_VALUE,
				buffer,
				0,
				sizeof(buffer),
				&buffer_len);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to get value\n");
			goto cc_exit;
		}
		/* Send CN to Rule Verifier and
		 * remove type and length from buffer
		 */
		cn_info.cert_level = *level;
		cn_info.cn = &buffer[2];
		cn_info.cn_len = buffer_len - 2;
		res = rule_update_subject_cn(rule, &cn_info);
		if (res == FCSERR_OK)
			(*level)++;
		break;
	}

cc_exit:
	derparser_delete_iterator(iterator);
	return res;
}

/**
 * Exported functions
 */

int certificatechain_verify(
		struct rule_verifier *rule,
		uint8_t  *certchain_buffer,
		size_t  certchain_buffer_length,
		uint8_t  *rootcert_buffer,
		size_t  rootcert_buffer_length)
{
	int res = -FCSERR_EINVAL;
	struct iterator_info *certchain_iterator = NULL;
	struct iterator_info *root_iterator = NULL;
	struct iterator_info *cert_iterator = NULL;
	struct iterator_info *name_iterator = NULL;
	struct derparser_object *subject = NULL;
	struct derparser_object *issuer = NULL;
	unsigned int level = 0;

	/* Check in parameters */
	if ((rule == NULL) ||
		(certchain_buffer == NULL) ||
		(certchain_buffer_length == 0) ||
		(rootcert_buffer == NULL) ||
		(rootcert_buffer_length == 0)) {
		return -FCSERR_EINVAL;
	}

	/* CNs of cert chain must be sent to rule_verifier */

	/* Create base iterators for use in other iterators */
	res = derparser_create_iterator(
			&certchain_iterator,
			asn1pdu_simple_cert,
			certchain_buffer_length,
			(uint8_t *)(certchain_buffer),
			(const char **)(NULL));
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to create iterator\n");
		goto cc_verify_exit;
	}

	res = derparser_create_iterator(
			&root_iterator,
			asn1pdu_simple_cert,
			rootcert_buffer_length,
			(uint8_t *)(rootcert_buffer),
			(const char **)(NULL));
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to create iterator\n");
		goto cc_verify_exit;
	}

	/* Create subject object */
	subject = derparser_create_buffer();
	if (subject == NULL) {
		res = -FCSERR_ENOMEM;
		FCS_LOG_ERR("Failed to create subject object\n");
		goto cc_verify_exit;
	}

	/* Loop through certificate chain */
	/* Set up initial iterator and do sanity check on content */
	res = cc_create_first_cert_iterator(&cert_iterator, certchain_iterator);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to create iterator\n");
		goto cc_verify_exit;
	}
	while (cert_iterator != NULL) {
		/* Read and process subject */
		res = cc_find_name(&name_iterator, cert_iterator,
				ASN1PDU_MATCH_CERT_SUBJECT, subject);
		if (res < 0) {
			FCS_LOG_ERR("Failed to get subject\n");
			goto cc_verify_exit;
		}
		/* Send it to rule_verifier */
		res = cc_send_cn_to_rm(rule, &level, name_iterator);
		if (res < 0) {
			FCS_LOG_ERR("Failed to send cn\n");
			goto cc_verify_exit;
		}

		/* Cleanup name iterator before next cert */
		derparser_delete_iterator(name_iterator);
		name_iterator = NULL;

		/* Check if subject matches previous issuer */
		if (issuer != NULL) {
			if (!cc_is_name_equal(subject, issuer)) {
				res = -FCSERR_EVCC;
				FCS_LOG_ERR("No matching subject\n");
				goto cc_verify_exit;
			}
		} else {
			/* Create issuer object */
			issuer = derparser_create_buffer();
			if (issuer == NULL) {
				res = -FCSERR_ENOMEM;
				FCS_LOG_ERR("Failed to create issuer object\n");
				goto cc_verify_exit;
			}
		}

		/* Read and process issuer */
		res = cc_find_name(NULL, cert_iterator,
				ASN1PDU_MATCH_CERT_ISSUER, issuer);
		if (res < 0) {
			FCS_LOG_ERR("Failed to get issuer\n");
			goto cc_verify_exit;
		}

		/* Next cert */
		res = cc_create_next_cert_iterator(&cert_iterator,
						certchain_iterator);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to create iterator\n");
			goto cc_verify_exit;
		}
	}

	/* Cleanup iterators before root cert loop */
	derparser_delete_iterator(name_iterator);
	name_iterator = NULL;
	derparser_delete_iterator(cert_iterator);
	cert_iterator = NULL;

	if (issuer == NULL) {
		res = -FCSERR_EVCC;
		FCS_LOG_ERR("No issuer???\n");
		goto cc_verify_exit;
	}

	/* Loop through root certificate list to find root of cert chain */
	/* Set up initial iterator and do sanity check on content */
	res = cc_create_first_cert_iterator(&cert_iterator, root_iterator);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to create iterator\n");
		goto cc_verify_exit;
	}
	while (cert_iterator != NULL) {
		/* Read and process subject */
		res = cc_find_name(&name_iterator, cert_iterator,
				ASN1PDU_MATCH_CERT_SUBJECT, subject);
		if (res < 0) {
			FCS_LOG_ERR("Failed to get subject\n");
			goto cc_verify_exit;
		}

		/* Is root cert found? */
		if (cc_is_name_equal(subject, issuer)) {
			/* Yes, send it to rule_verifier */
			res = cc_send_cn_to_rm(rule, &level, name_iterator);
			if (res < 0) {
				FCS_LOG_ERR("Failed to send cn\n");
				goto cc_verify_exit;
			}
			break;
		}

		/* Cleanup name iterator before next cert */
		derparser_delete_iterator(name_iterator);
		name_iterator = NULL;

		/* Next cert */
		res = cc_create_next_cert_iterator(&cert_iterator,
						root_iterator);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to create iterator\n");
			goto cc_verify_exit;
		}
	}

	if (cert_iterator == NULL) {
		res = -FCSERR_EVCC;
		FCS_LOG_ERR("No matching root\n");
		goto cc_verify_exit;
	}
	derparser_delete_iterator(cert_iterator);
	cert_iterator = NULL;

	/* No extension => No restrictions on certificate */

	res = rule_final(rule);

cc_verify_exit:
	derparser_delete_object(issuer);
	derparser_delete_object(subject);
	derparser_delete_iterator(name_iterator);
	derparser_delete_iterator(cert_iterator);
	derparser_delete_iterator(root_iterator);
	derparser_delete_iterator(certchain_iterator);
	return res;
}

