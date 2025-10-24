/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#include "cms_verifier.h"
#include "rule_verifier_intern.h"
#include "der_parser.h"
#include "asn1pdu_cms.h"
#include "fcserr.h"
#include "fcslog.h"
#include "digest.h"
#include "certificate_chain.h"
#include "signature.h"
#include <string.h>

static uint8_t *cms_add_header(
	uint8_t type,
	uint8_t *payload,
	size_t payload_len,
	size_t *new_buf_len)
{
	uint8_t head[4];
	size_t head_len = 0;
	uint8_t *new_buf = NULL;

	if (new_buf_len == NULL)
		goto cms_add_header_exit;
	head[0] = type;
	if (payload_len < 0x80) {
		head[1] = payload_len;
		head_len = 2;
	} else if (payload_len < 0x100) {
		head[1] = 0x81;
		head[2] = payload_len;
		head_len = 3;
	} else {
		head[1] = 0x82;
		head[2] = payload_len >> 8;
		head[3] = payload_len & 0xFF;
		head_len = 4;
	}
	new_buf = malloc(payload_len + head_len);
	if (new_buf == NULL)
		goto cms_add_header_exit;
	memcpy(new_buf, head, head_len);
	memcpy(&new_buf[head_len], payload, payload_len);
	*new_buf_len = payload_len + head_len;
cms_add_header_exit:
	return new_buf;
}

static int cms_get_field_buffer(
	struct iterator_info *root_iterator,
	const char **match,
	struct derparser_object *buf_obj)
{
	int res = FCSERR_OK;
	struct iterator_info *iterator = NULL;
	uint8_t *buf;
	size_t buf_len;

	res = derparser_create_subset_iterator(
			&iterator,
			root_iterator,
			match);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to create iterator for signattr\n");
		goto cms_get_field_buffer_exit;
	}
	res = derparser_next(iterator, buf_obj);
	if (res == 0) {
		FCS_LOG_ERR("Failed to find attr type\n");
		res = -FCSERR_ENOTF;
		goto cms_get_field_buffer_exit;
	} else if (res < 0) {
		FCS_LOG_ERR("Failed to parse cms for attr type\n");
		goto cms_get_field_buffer_exit;
	}
	/* Check if we have a buffer */
	buf_len = derparser_get_buffer(buf_obj, &buf);
	if ((buf_len == 0) || (buf == NULL)) {
		res = -FCSERR_ENODATA;
		goto cms_get_field_buffer_exit;
	}
	res = FCSERR_OK;

cms_get_field_buffer_exit:
	derparser_delete_iterator(iterator);
	return res;
}

static int cms_verify_field(
	struct iterator_info *root_iterator,
	const char **match,
	const uint8_t *expected,
	size_t expected_len)
{
	int res = FCSERR_OK;
	struct derparser_object *buf_obj = NULL;
	uint8_t *buf;
	size_t buf_len;

	buf_obj = derparser_create_buffer();
	if (buf_obj == NULL) {
		FCS_LOG_ERR("Failed to create buffer object\n");
		res = -FCSERR_ENOMEM;
		goto cms_verify_field_exit;
	}

	res = cms_get_field_buffer(
			root_iterator,
			match,
			buf_obj);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("cms_get_field_buffer failed (%d)\n", res);
		goto cms_verify_field_exit;
	}

	buf_len = derparser_get_buffer(buf_obj, &buf);
	if ((buf_len != expected_len) ||
		(memcmp(buf, expected, buf_len) != 0)) {
		FCS_LOG_ERR("Expected field content does not match actual.\n");
		res = -FCSERR_EDATA;
	}

cms_verify_field_exit:
	derparser_delete_object(buf_obj);
	return res;
}

static int cms_get_signed_attribute(
	struct iterator_info *root_iterator,
	const uint8_t *type_id,
	size_t type_id_len,
	struct derparser_object *attr_value)
{
	int res = FCSERR_OK;
	struct iterator_info *iterator = NULL;
	struct derparser_object *attr_type = NULL;
	uint8_t *buf;
	size_t buf_len;

	attr_type = derparser_create_buffer();
	if (attr_type == NULL) {
		FCS_LOG_ERR("Failed to create type buffer for signattr\n");
		res = -FCSERR_ENOMEM;
		goto cms_get_signed_attribute_exit;
	}

	/* Get signing attributes */
	res = derparser_create_subset_iterator(
			&iterator,
			root_iterator,
			(const char **)(ASN1PDU_MATCH_CMS_SIGNATTR));
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to create iterator for signcert\n");
		goto cms_get_signed_attribute_exit;
	}
	res = derparser_next(iterator, NULL);
	while (res > 0) {
		/* Get Type */
		res = cms_get_field_buffer(iterator,
				(const char **)(ASN1PDU_MATCH_CMS_ATTR_TYPE),
				attr_type);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to find attr type\n");
			goto cms_get_signed_attribute_exit;
		}

		/* Is this the requested type? */
		buf_len = derparser_get_buffer(attr_type, &buf);
		if ((buf_len == type_id_len) &&
			(buf != NULL) &&
			(memcmp(type_id, buf, type_id_len) == 0)) {
			/* Yes */

			/* Get Value */
			res = cms_get_field_buffer(iterator,
				(const char **)(ASN1PDU_MATCH_CMS_ATTR_VALUE),
				attr_value);
			goto cms_get_signed_attribute_exit;
		}
		res = derparser_next(iterator, NULL);
	}
	if (res < 0) {
		FCS_LOG_ERR("Failed to parse cms for signed attribute\n");
	} else {
		FCS_LOG_ERR("Failed to find signed attribute\n");
		res = -FCSERR_ENOTF;
	}

cms_get_signed_attribute_exit:
	derparser_delete_object(attr_type);
	derparser_delete_iterator(iterator);
	return res;
}

static int cms_is_known_attribute(
	struct derparser_object *attr_type)
{
	int res = -FCSERR_ENOTF;
	uint8_t *buf;
	size_t buf_len;

	buf_len = derparser_get_buffer(attr_type, &buf);
	if ((buf_len == 0) || (buf == NULL)) {
		FCS_LOG_ERR("Failed to get buffer\n");
		res = -FCSERR_ENOBUFS;
		goto cms_is_known_attribute_exit;
	}

	if ((buf_len == asn1pdu_cms_object_contentType_len) &&
		(memcmp(asn1pdu_cms_object_contentType,
			buf, buf_len) == 0)) {
		/* Yes, is contentType, skip it */
		res = FCSERR_OK;
		goto cms_is_known_attribute_exit;
	}

	if ((buf_len == asn1pdu_cms_object_sign_time_len) &&
		(memcmp(asn1pdu_cms_object_sign_time,
			buf, buf_len) == 0)) {
		/* Yes, is signingTime, skip it */
		res = FCSERR_OK;
		goto cms_is_known_attribute_exit;
	}

	if ((buf_len == asn1pdu_cms_object_digest_payload_len) &&
		(memcmp(asn1pdu_cms_object_digest_payload,
			buf, buf_len) == 0)) {
		/* Yes, is payload digest, skip it */
		res = FCSERR_OK;
		goto cms_is_known_attribute_exit;
	}

cms_is_known_attribute_exit:
	return res;
}

static int cms_get_unhandled_attributes(
	struct iterator_info *root_iterator,
	size_t *attr_count,
	uint32_t index,
	struct derparser_object *attr_type,
	struct derparser_object *attr_value)
{
	int res = FCSERR_OK;
	struct iterator_info *iterator = NULL;
	struct derparser_object *alloc_attr_type = NULL;
	struct derparser_object *cur_attr_type = NULL;
	size_t count = 0;

	if (attr_type != NULL)
		cur_attr_type = attr_type;
	else {
		alloc_attr_type = derparser_create_buffer();
		if (alloc_attr_type == NULL) {
			FCS_LOG_ERR(
			"Failed to create type buffer for signattr\n");
			res = -FCSERR_ENOMEM;
			goto cms_get_unhandled_attributes_exit;
		}
		cur_attr_type = alloc_attr_type;
	}

	/* Get signing attributes */
	res = derparser_create_subset_iterator(
			&iterator,
			root_iterator,
			(const char **)(ASN1PDU_MATCH_CMS_SIGNATTR));
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to create iterator for signcert\n");
		goto cms_get_unhandled_attributes_exit;
	}
	res = derparser_next(iterator, NULL);
	while (res > 0) {
		/* Get Type */
		res = cms_get_field_buffer(iterator,
				(const char **)(ASN1PDU_MATCH_CMS_ATTR_TYPE),
				cur_attr_type);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to find attr type\n");
			goto cms_get_unhandled_attributes_exit;
		}

		/* Is this an known type? */
		res = cms_is_known_attribute(cur_attr_type);
		if (res == FCSERR_OK) {
			res = derparser_next(iterator, NULL);
			continue;
		} else if (res != -FCSERR_ENOTF) {
			FCS_LOG_ERR("Failed to check known attr\n");
			goto cms_get_unhandled_attributes_exit;
		}

		/* No, count it. */
		count++;

		/* Do we want the content of an attribute? */
		if ((attr_type == NULL) || (attr_value == NULL)) {
			res = derparser_next(iterator, NULL);
			continue;
		}
		/* Do we want the content for current attribute? */
		if ((index + 1) != count) {
			res = derparser_next(iterator, NULL);
			continue;
		}

		/* Get Value */
		res = cms_get_field_buffer(iterator,
				(const char **)(ASN1PDU_MATCH_CMS_ATTR_VALUE),
				attr_value);
		goto cms_get_unhandled_attributes_exit;
	}
	if (res < 0) {
		FCS_LOG_ERR("Failed to parse cms for signed attribute\n");
	} else {
		if (attr_count != NULL) {
			*attr_count = count;
			res = FCSERR_OK;
		} else {
			FCS_LOG_ERR("Failed to find signed attribute\n");
			res = -FCSERR_ENOTF;
		}
	}

cms_get_unhandled_attributes_exit:
	derparser_delete_object(alloc_attr_type);
	derparser_delete_iterator(iterator);
	return res;
}

static int cms_verify_static_fields(struct iterator_info *root_iterator)
{
	int res = FCSERR_OK;
	struct derparser_object *attr_value = NULL;
	uint8_t *buf;
	size_t buf_len;

	res = cms_verify_field(root_iterator,
			ASN1PDU_MATCH_CMS_CNTTYPE,
			asn1pdu_cms_expect_contentType,
			asn1pdu_cms_expect_contentType_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Unexpected contentType\n");
		goto cms_check_static_fields_exit;
	}

	res = cms_verify_field(root_iterator,
			ASN1PDU_MATCH_CMS_SIGN_VERSION,
			asn1pdu_cms_expect_signdata_version,
			asn1pdu_cms_expect_signdata_version_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Unexpected SignData version\n");
		goto cms_check_static_fields_exit;
	}

	res = cms_verify_field(root_iterator,
			ASN1PDU_MATCH_CMS_SIGN_DIGESTALG,
			asn1pdu_cms_expect_signdata_digestalg,
			asn1pdu_cms_expect_signdata_digestalg_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Unexpected SignData digest algorithm\n");
		goto cms_check_static_fields_exit;
	}

	res = cms_verify_field(root_iterator,
			ASN1PDU_MATCH_CMS_SD_ENCAP_CNTTYPE,
			asn1pdu_cms_expect_sd_encap_contentType,
			asn1pdu_cms_expect_sd_encap_contentType_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Unexpected SignData encaps type\n");
		goto cms_check_static_fields_exit;
	}

	res = cms_verify_field(root_iterator,
			ASN1PDU_MATCH_CMS_SD_SI_VERSION,
			asn1pdu_cms_expect_sd_si_version,
			asn1pdu_cms_expect_sd_si_version_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Unexpected SignData SignInfo version\n");
		goto cms_check_static_fields_exit;
	}

	res = cms_verify_field(root_iterator,
			ASN1PDU_MATCH_CMS_SD_SI_DIGESTALG,
			asn1pdu_cms_expect_sd_si_digestalg,
			asn1pdu_cms_expect_sd_si_digestalg_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Unexpected SignData SignInfo digestalg\n");
		goto cms_check_static_fields_exit;
	}

	attr_value = derparser_create_buffer();
	if (attr_value == NULL) {
		FCS_LOG_ERR("Failed to create type buffer for signattr\n");
		res = -FCSERR_ENOMEM;
		goto cms_check_static_fields_exit;
	}

	res = cms_get_signed_attribute(root_iterator,
			asn1pdu_cms_object_contentType,
			asn1pdu_cms_object_contentType_len,
			attr_value);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get signed attribute contentType\n");
		goto cms_check_static_fields_exit;
	}
	buf_len = derparser_get_buffer(attr_value, &buf);
	if ((buf_len == 0) || (buf == NULL)) {
		FCS_LOG_ERR("Failed to get buffer\n");
		res = -FCSERR_ENOTF;
		goto cms_check_static_fields_exit;
	}

	if ((buf_len != asn1pdu_cms_object_id_data_len+2) ||
		(buf[0] != 0x06) ||
		(buf[1] != asn1pdu_cms_object_id_data_len) ||
		(0 != memcmp(&buf[2],
			asn1pdu_cms_object_id_data,
			asn1pdu_cms_object_id_data_len))) {
		FCS_LOG_ERR("SignAttr ContentType is not id-data.\n");
		res = -FCSERR_EDATA;
	}

cms_check_static_fields_exit:
	derparser_delete_object(attr_value);
	return res;
}

static int cms_signattr_digest_update(
	struct iterator_info *root_iterator,
	struct digest *dgst)
{
	int res = FCSERR_OK;
	struct derparser_object *signattrs = NULL;
	uint8_t *buf;
	size_t buf_len;
	uint8_t *hash_data_buf = NULL;
	size_t hash_data_buf_len = 0;

	signattrs = derparser_create_buffer();
	if (signattrs == NULL) {
		FCS_LOG_ERR("Failed to create buffer for signattrs\n");
		res = -FCSERR_ENOMEM;
		goto cms_signattr_digest_update_exit;
	}

	res = cms_get_field_buffer(
			root_iterator,
			(const char **)(ASN1PDU_MATCH_CMS_SIGNATTRS),
			signattrs);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get signattrs\n");
		goto cms_signattr_digest_update_exit;
	}

	buf_len = derparser_get_buffer(signattrs, &buf);

	/* Add EXPLICIT SET OF (0x31) tag with length before signAttrs
		as described by specification */
	hash_data_buf = cms_add_header(
				0x31, buf, buf_len, &hash_data_buf_len);
	if (hash_data_buf == NULL) {
		FCS_LOG_ERR("Failed to add header to signattrs\n");
		res = -FCSERR_ENOMEM;
		goto cms_signattr_digest_update_exit;
	}
	res = digest_sha256_update(
			dgst,
			hash_data_buf,
			hash_data_buf_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to update digest with content\n");
		goto cms_signattr_digest_update_exit;
	}

cms_signattr_digest_update_exit:
	free(hash_data_buf);
	derparser_delete_object(signattrs);
	return res;
}

static int cms_get_embedded_payload(
	struct iterator_info *root_iterator,
	uint8_t **embedded_payload,
	size_t *embedded_payload_length)
{
	int res = FCSERR_OK;
	struct derparser_object *embedcontent = NULL;
	uint8_t *buf;
	size_t buf_len;
	uint8_t *out_buf = NULL;

	embedcontent = derparser_create_buffer();
	if (embedcontent == NULL) {
		FCS_LOG_ERR("Failed to create type buffer for embcontent\n");
		res = -FCSERR_ENOMEM;
		goto cms_get_embedded_payload_exit;
	}

	res = cms_get_field_buffer(
			root_iterator,
			(const char **)(ASN1PDU_MATCH_CMS_SD_ENCAP_CNT),
			embedcontent);

	if (res == -FCSERR_ENODATA) {
		*embedded_payload = NULL;
		*embedded_payload_length = 0;
		/* Valid use case. Payload can be empty */
		res = FCSERR_OK;
		goto cms_get_embedded_payload_exit;
	}

	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get embedcontent\n");
		goto cms_get_embedded_payload_exit;
	}

	buf_len = derparser_get_buffer(embedcontent, &buf);

	out_buf = malloc(buf_len);
	if (out_buf == NULL) {
		FCS_LOG_ERR("Failed to create out buffer for embcontent\n");
		res = -FCSERR_ENOMEM;
		goto cms_get_embedded_payload_exit;
	}
	memcpy(out_buf, buf, buf_len);
	*embedded_payload = out_buf;
	*embedded_payload_length = buf_len;
	res = FCSERR_OK;

cms_get_embedded_payload_exit:
	derparser_delete_object(embedcontent);
	return res;
}

static int cms_verify_payload(
	struct iterator_info *root_iterator,
	uint8_t *payload,
	size_t payload_length)
{
	int res = FCSERR_OK;
	struct derparser_object *attr_value = NULL;
	uint8_t *attr_buf;
	size_t attr_buf_len;
	struct digest *dgst = NULL;
	uint8_t *calc_hash = NULL;
	uint32_t calc_hash_length = 0;

	res = digest_sha256_init(&dgst);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to init digest session\n");
		goto cms_verify_payload_exit;
	}
	res = digest_sha256_update(
			dgst,
			payload,
			payload_length);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to update digest with content\n");
		goto cms_verify_payload_exit;
	}
	res = digest_sha256_final(
			dgst,
			&calc_hash,
			&calc_hash_length);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to finalize digest session\n");
		goto cms_verify_payload_exit;
	}

	attr_value = derparser_create_buffer();
	if (attr_value == NULL) {
		FCS_LOG_ERR("Failed to create type buffer for signattr\n");
		res = -FCSERR_ENOMEM;
		goto cms_verify_payload_exit;
	}

	/* Get attribute */
	res = cms_get_signed_attribute(root_iterator,
		asn1pdu_cms_object_digest_payload,
		asn1pdu_cms_object_digest_payload_len,
		attr_value);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get fs attribute.\n");
		goto cms_verify_payload_exit;
	}

	attr_buf_len = derparser_get_buffer(attr_value, &attr_buf);
	if (attr_buf_len == 0) {
		FCS_LOG_ERR("Failed to get fs attribute buffer.\n");
		res = -FCSERR_ENOMEM;
		goto cms_verify_payload_exit;
	}

	/* Check the hash buffers. */
	/* The payload should be protected by a otctet with a single
	   sha256 hash => 2 bytes header (0x04, 0x20) + 32 bytes.
	*/
	if ((attr_buf_len != 34) ||
			(attr_buf[0] != 0x04) ||
			(attr_buf[1] != 0x20)) {
		FCS_LOG_ERR("Unexptected format of digest attribute.\n");
		res = -FCSERR_EFORMAT;
		goto cms_verify_payload_exit;
	}
	if ((calc_hash_length != attr_buf_len - 2) ||
			(memcmp(&attr_buf[2],
				calc_hash,
				calc_hash_length) != 0)) {
		FCS_LOG_ERR("Payload digest verify failed.\n");
		res = -FCSERR_EVHSH;
		goto cms_verify_payload_exit;
	}

	res = FCSERR_OK;

cms_verify_payload_exit:
	if (dgst != NULL)
		digest_sha256_deinit(dgst);
	derparser_delete_object(attr_value);
	return res;
}

static int cms_process_attributes(
	struct iterator_info *root_iterator,
	struct rule_verifier *rule_handle)
{
	int res = FCSERR_OK;
	struct rule_attribute attr_rule;
	struct derparser_object *attr_type = NULL;
	struct derparser_object *attr_value = NULL;
	size_t attr_count = 0;
	uint8_t *type_buf;
	size_t type_buf_len;
	uint8_t *value_buf;
	size_t value_buf_len;
	uint8_t *alloc_buf = NULL;
	size_t alloc_buf_len = 0;
	unsigned int i;

	attr_type = derparser_create_buffer();
	if (attr_type == NULL) {
		FCS_LOG_ERR("Failed to create type buffer for signattr\n");
		res = -FCSERR_ENOMEM;
		goto cms_process_attributes_exit;
	}

	attr_value = derparser_create_buffer();
	if (attr_value == NULL) {
		FCS_LOG_ERR("Failed to create value buffer for signattr\n");
		res = -FCSERR_ENOMEM;
		goto cms_process_attributes_exit;
	}

	res = cms_get_unhandled_attributes(
		root_iterator,
		&attr_count,
		0, NULL, NULL);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get unhandled attr count.\n");
		goto cms_process_attributes_exit;
	}

	for (i = 0; i < attr_count; i++) {
		/* Get attribute */
		res = cms_get_unhandled_attributes(
			root_iterator,
			NULL,
			i,
			attr_type,
			attr_value);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to get unhandled attribute.\n");
			goto cms_process_attributes_exit;
		}

		type_buf_len = derparser_get_buffer(attr_type, &type_buf);
		if (type_buf_len == 0) {
			FCS_LOG_ERR("Failed to get unhdl attr type buf.\n");
			goto cms_process_attributes_exit;
		}

		value_buf_len = derparser_get_buffer(attr_value, &value_buf);
		if (value_buf_len == 0) {
			FCS_LOG_ERR("Failed to get unhdl attr value buf.\n");
			goto cms_process_attributes_exit;
		}

		/* Function rule_update_unhandled_attributes expects
			Object (0x06) header to be present */
		alloc_buf = cms_add_header(
				0x06, type_buf, type_buf_len, &alloc_buf_len);
		if (alloc_buf == NULL) {
			FCS_LOG_ERR("Failed to add_header to attr.\n");
			res = -FCSERR_ENOMEM;
			goto cms_process_attributes_exit;
		}

		/* Setup attribute struct */
		attr_rule.oid = alloc_buf;
		attr_rule.oid_len = alloc_buf_len;
		attr_rule.asn1_buffer = value_buf;
		attr_rule.asn1_buffer_len = value_buf_len;

		res = rule_update_unhandled_attributes(
				rule_handle, &attr_rule);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to update fs attribute.\n");
			goto cms_process_attributes_exit;
		}
		free(alloc_buf);
		alloc_buf = NULL;
	}

cms_process_attributes_exit:
	free(alloc_buf);
	derparser_delete_object(attr_type);
	derparser_delete_object(attr_value);
	return res;
}

static int cms_verify_signed_attributes(
	struct iterator_info *root_iterator,
	struct rule_verifier *rule,
	uint8_t              *rootcerts,
	size_t                rootcerts_length)
{
	int res = -FCSERR_EINVAL;
	struct derparser_object *signcert = NULL;
	uint8_t *signcert_buf;
	size_t signcert_buf_len;
	struct derparser_object *signalg = NULL;
	uint8_t *signalg_buf;
	size_t signalg_buf_len;
	struct derparser_object *signature = NULL;
	uint8_t *sign_buf;
	size_t sign_buf_len;
	struct digest *dgst = NULL;
	uint8_t *calc_hash = NULL;
	uint32_t calc_hash_length = 0;

	/* Get signing cert */
	signcert = derparser_create_buffer();
	if (signcert == NULL) {
		FCS_LOG_ERR("Failed to create buffer signcert\n");
		res = -FCSERR_ENOMEM;
		goto cms_verify_signed_attributes_exit;
	}
	res = cms_get_field_buffer(
			root_iterator,
			(const char **)(ASN1PDU_MATCH_CMS_CERT),
			signcert);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get signing cert (%d)\n", res);
		goto cms_verify_signed_attributes_exit;
	}
	signcert_buf_len = derparser_get_buffer(signcert, &signcert_buf);

	/* Get Hash of signed attributes */
	res = digest_sha256_init(&dgst);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to init digest session\n");
		goto cms_verify_signed_attributes_exit;
	}
	res = cms_signattr_digest_update(root_iterator, dgst);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to update signattrs digest session\n");
		goto cms_verify_signed_attributes_exit;
	}
	res = digest_sha256_final(
			dgst,
			&calc_hash,
			&calc_hash_length);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to finalize digest session\n");
		goto cms_verify_signed_attributes_exit;
	}

	/* Get signature algorithm */
	signalg = derparser_create_buffer();
	if (signalg == NULL) {
		FCS_LOG_ERR("Failed to create buffer signalg\n");
		res = -FCSERR_ENOMEM;
		goto cms_verify_signed_attributes_exit;
	}
	res = cms_get_field_buffer(
			root_iterator,
			(const char **)(ASN1PDU_MATCH_CMS_SIGNALG),
			signalg);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get signing alg (%d)\n", res);
		goto cms_verify_signed_attributes_exit;
	}
	signalg_buf_len = derparser_get_buffer(signalg, &signalg_buf);

	/* Get signature */
	signature = derparser_create_buffer();
	if (signature == NULL) {
		FCS_LOG_ERR("Failed to create buffer signcert\n");
		res = -FCSERR_ENOMEM;
		goto cms_verify_signed_attributes_exit;
	}
	res = cms_get_field_buffer(
			root_iterator,
			(const char **)(ASN1PDU_MATCH_CMS_SIGNATURE),
			signature);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get signature (%d)\n", res);
		goto cms_verify_signed_attributes_exit;
	}
	sign_buf_len = derparser_get_buffer(signature, &sign_buf);

	/* Process FS Attribute */
	res = cms_process_attributes(root_iterator, rule);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to process FS attribute: (%d)\n", res);
		goto cms_verify_signed_attributes_exit;
	}

	/* Verify signed Attributes */
	res = certificatechain_verify(
			rule,
			signcert_buf, signcert_buf_len,
			rootcerts, rootcerts_length);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to verify cert chain: (%d)\n", res);
		goto cms_verify_signed_attributes_exit;
	}
	if ((asn1pdu_cms_signalg_rsassa_pss_len == signalg_buf_len) &&
		((memcmp(asn1pdu_cms_signalg_rsassa_pss,
				signalg_buf,
				signalg_buf_len) == 0) ||
		(memcmp(asn1pdu_cms_signalg_rsassa_pss_4k,
				signalg_buf,
				signalg_buf_len) == 0))) {
		res = signature_verify_rsassa_pss(
			signcert_buf, signcert_buf_len,
			sign_buf, sign_buf_len,
			calc_hash, calc_hash_length);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR(
			"Failed to verify signature: (%d)\n", res);
			goto cms_verify_signed_attributes_exit;
		}
	} else if ((asn1pdu_cms_signalg_pkcs1_len == signalg_buf_len) &&
		(memcmp(asn1pdu_cms_signalg_pkcs1,
				signalg_buf,
				signalg_buf_len) == 0)) {
		res = signature_verify(
			signcert_buf, signcert_buf_len,
			sign_buf, sign_buf_len,
			calc_hash, calc_hash_length);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR(
			"Failed to verify signature: (%d)\n", res);
			goto cms_verify_signed_attributes_exit;
		}
	} else {
		FCS_LOG_ERR("Unknown signature algorithm\n");
		res = -FCSERR_EVS;
		goto cms_verify_signed_attributes_exit;
	}

cms_verify_signed_attributes_exit:
	if (dgst != NULL)
		digest_sha256_deinit(dgst);
	derparser_delete_object(signature);
	derparser_delete_object(signalg);
	derparser_delete_object(signcert);
	return res;
}

int cms_verify(uint8_t         *cms,
	size_t                  cms_length,
	struct rule_verifier *rule,
	uint8_t                *rootcerts,
	size_t                  rootcerts_length,
	uint8_t                *external_payload,
	size_t                  external_payload_length,
	uint8_t               **embedded_payload,
	size_t                 *embedded_payload_length)
{
	int res = -FCSERR_EINVAL;
	struct iterator_info *root_iterator = NULL;
	struct iterator_info *iterator = NULL;
	uint8_t *payload = NULL;
	size_t payload_len = 0;

	/* Check in parameters */
	if ((cms == NULL) ||
			(cms_length == 0) ||
			(rule == NULL) ||
			(rootcerts == NULL) ||
			(rootcerts_length == 0) ||
			((external_payload == NULL) &&
			 (external_payload_length > 0)) ||
			/*
			 * Allow either the external or the embedded
			 * payload to be NULL.
			 */
			(((external_payload == NULL) ||
			 external_payload_length == 0) &&
			((embedded_payload == NULL) ||
			(embedded_payload_length == NULL)))) {
		FCS_LOG_ERR("Invalid parameter.\n");
		goto cms_verify_exit;
	}

	/* Create a base iterator for use in other iterators */
	res = derparser_create_iterator(
			&root_iterator,
			asn1pdu_cms,
			cms_length,
			(uint8_t *)(cms),
			(const char **)(NULL));
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to create iterator\n");
		goto cms_verify_exit;
	}

	/* Sanity check on content */
	res = derparser_create_subset_iterator(
			&iterator,
			root_iterator,
			(const char **)(NULL));
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to create iterator\n");
		goto cms_verify_exit;
	}
	res = derparser_next(iterator, NULL);
	if (res < 0) {
		FCS_LOG_ERR("Failed to parse cms\n");
		goto cms_verify_exit;
	}
	derparser_delete_iterator(iterator);
	iterator = NULL;

	/* Verify static fields */
	res = cms_verify_static_fields(root_iterator);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to verify static fields\n");
		goto cms_verify_exit;
	}

	/* Verify signed attributes with signature */
	res = cms_verify_signed_attributes(
			root_iterator,
			rule,
			rootcerts,
			rootcerts_length);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to verify signed attributes\n");
		goto cms_verify_exit;
	}

	if (external_payload == NULL) {
		/* Get embedded content */
		res = cms_get_embedded_payload(
				root_iterator,
				&payload,
				&payload_len);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to get embedcontent\n");
			goto cms_verify_exit;
		}

		/* Verify embedded content with signed attribute */
		res = cms_verify_payload(
				root_iterator,
				payload,
				payload_len);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to verify embedcontent\n");
			goto cms_verify_exit;
		}
		*embedded_payload = payload;
		*embedded_payload_length = payload_len;
	} else {
		/* Verify external content with signed attribute */
		res = cms_verify_payload(
				root_iterator,
				external_payload,
				external_payload_length);
		if (res != FCSERR_OK)
			FCS_LOG_ERR("Failed to verify extern content\n");

	}

cms_verify_exit:
	derparser_delete_iterator(iterator);
	derparser_delete_iterator(root_iterator);
	return res;
}

