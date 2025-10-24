/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "ks_parser.h"
#include "asn1pdu_ks.h"
#include "der_parser.h"
#include "fcserr.h"
#include "fcslog.h"
#include <stdlib.h>

static int ks_add_entry(struct ks_main *keystore,
		int domain,
		enum ks_entry_data_pr present,
		uint8_t *buffer,
		size_t buffer_len)
{
	int res = FCSERR_OK;
	struct ks_entry *entry = NULL;
	struct ks_entry **pre_array = keystore->db.list.array;
	int pre_count = keystore->db.list.count;

	/* Create entry */
	entry = malloc(sizeof(struct ks_entry));
	if (entry == NULL) {
		FCS_LOG_ERR("Failed to allocate entry\n");
		res = -FCSERR_ENOMEM;
		goto exit;
	}
	/* Fill entry */
	entry->domain = domain;
	entry->data.present = present;
	if (present == KS_ENTRY_DATA_PR_CERTIFICATE) {
		entry->data.choice.certificate.buf = buffer;
		entry->data.choice.certificate.size = buffer_len;
	} else {
		entry->data.choice.publickey.buf = buffer;
		entry->data.choice.publickey.size = buffer_len;
	}

	/* Add entry to list structure */
	(keystore->db.list.count)++;
	keystore->db.list.array = malloc(keystore->db.list.count *
					sizeof(struct ks_entry *));
	if (keystore->db.list.array != NULL) {
		if (pre_array != NULL) {
			memcpy(keystore->db.list.array,
				pre_array,
				pre_count *
					sizeof(struct ks_entry *));
			free(pre_array);
		}
		keystore->db.list.array[pre_count] = entry;
		entry = NULL;
		/* Entry is now owned by structure */
	} else {
		keystore->db.list.array = pre_array;
		keystore->db.list.count = pre_count;
		res = -FCSERR_ENOMEM;
		FCS_LOG_ERR("Failed to add entry\n");
	}

exit:
	free(entry);
	return res;
}

static int ks_get_internal(
		struct iterator_info *root_iterator,
		const char **match,
		struct derparser_object *value)
{
	int res = -FCSERR_EINVAL;
	struct iterator_info *iterator = NULL;

	res = derparser_create_subset_iterator(
			&iterator,
			root_iterator,
			match);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to create iterator\n");
		goto exit;
	}
	res = derparser_next(iterator, value);
	if (res < 0)
		FCS_LOG_ERR("Failed to get value\n");
	else if (res == 0)
		res = -FCSERR_ENOTF;
	else
		res = FCSERR_OK;
exit:
	derparser_delete_iterator(iterator);
	return res;
}

static int ks_verify(
		struct iterator_info *root_iterator,
		const char **match,
		const uint8_t *value,
		size_t value_len)
{
	int res = -FCSERR_EINVAL;
	struct derparser_object *value_object = NULL;
	uint8_t *local_buffer; /* Do not free */
	size_t local_buffer_len;

	if (value == NULL || value_len == 0) {
		FCS_LOG_ERR("Wrong params\n");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	value_object = derparser_create_buffer();
	if (value_object == NULL) {
		FCS_LOG_ERR("Failed to create buffer object\n");
		res = -FCSERR_ENOMEM;
		goto exit;
	}

	res = ks_get_internal(
		root_iterator,
		match,
		value_object);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to find field\n");
		goto exit;
	}

	local_buffer_len = derparser_get_buffer(value_object, &local_buffer);
	if ((local_buffer_len != value_len) ||
			(memcmp(local_buffer, value, value_len) != 0)) {
		FCS_LOG_ERR("Unexpected field value\n");
		res = -FCSERR_EINFOR;
	}
exit:
	derparser_delete_object(value_object);
	return res;
}

static int ks_get_int(
		struct iterator_info *root_iterator,
		const char **match,
		int *value)
{
	int res = -FCSERR_EINVAL;
	struct derparser_object *value_object = NULL;

	if (value == NULL) {
		FCS_LOG_ERR("Wrong params\n");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	value_object = derparser_create_integer();
	if (value_object == NULL) {
		FCS_LOG_ERR("Failed to create integer object\n");
		res = -FCSERR_ENOMEM;
		goto exit;
	}

	res = ks_get_internal(
		root_iterator,
		match,
		value_object);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to find integer\n");
		goto exit;
	}
	*value = derparser_get_integer(value_object);
exit:
	derparser_delete_object(value_object);
	return res;
}

static int ks_get_buffer(
		struct iterator_info *root_iterator,
		const char **match,
		uint8_t **value,
		size_t *value_len)
{
	int res = -FCSERR_EINVAL;
	struct derparser_object *value_object = NULL;
	uint8_t *local_buffer; /* Do not free */

	if (value == NULL || value_len == NULL) {
		FCS_LOG_ERR("Wrong params\n");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	value_object = derparser_create_buffer();
	if (value_object == NULL) {
		FCS_LOG_ERR("Failed to create buffer object\n");
		res = -FCSERR_ENOMEM;
		goto exit;
	}

	res = ks_get_internal(
		root_iterator,
		match,
		value_object);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to find buffer\n");
		goto exit;
	}
	*value_len = derparser_get_buffer(value_object, &local_buffer);
	*value = malloc(*value_len);
	if (*value == NULL) {
		FCS_LOG_ERR("Failed to allocate buffer\n");
		res = -FCSERR_ENOMEM;
	}
	memcpy(*value, local_buffer, *value_len);

exit:
	derparser_delete_object(value_object);
	return res;
}

static int ks_get_bool(
		struct iterator_info *root_iterator,
		const char **match,
		bool *value)
{
	int res = -FCSERR_EINVAL;
	struct derparser_object *value_object = NULL;

	if (value == NULL) {
		FCS_LOG_ERR("Wrong params\n");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	value_object = derparser_create_boolean();
	if (value_object == NULL) {
		FCS_LOG_ERR("Failed to create boolean\n");
		res = -FCSERR_ENOMEM;
		goto exit;
	}

	res = ks_get_internal(
		root_iterator,
		match,
		value_object);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to find boolean\n");
		goto exit;
	}
	*value = derparser_get_boolean(value_object);
exit:
	derparser_delete_object(value_object);
	return res;
}

void ks_free(struct ks_main *keystore)
{
	int i;

	if (keystore == NULL)
		return;
	if (keystore->db.list.array != NULL) {
		for (i = 0; i < keystore->db.list.count; i++) {
			struct ks_entry *entry =
				keystore->db.list.array[i];
			if (entry == NULL)
				continue;
			if (entry->data.present ==
				KS_ENTRY_DATA_PR_CERTIFICATE) {
				free(entry->data.choice.certificate.buf);
			} else if (entry->data.present ==
				KS_ENTRY_DATA_PR_PUBLICKEY) {
				free(entry->data.choice.publickey.buf);
			}
		}
		free(keystore->db.list.array);
	}
	free(keystore);
}

int ks_parse(const uint8_t *buffer,
		size_t size,
		struct ks_main **keystore_ptr)
{
	int res = -FCSERR_EINVAL;
	struct ks_main *keystore = NULL;
	struct iterator_info *root_iterator = NULL;
	struct iterator_info *iterator = NULL;
	bool xcs = false;
	int domain = 0;
	enum ks_entry_data_pr present = KS_ENTRY_DATA_PR_NOTHING;
	uint8_t *value_buffer = NULL;
	size_t value_buffer_len = 0;

	if (buffer == NULL ||
		size == 0 ||
		keystore_ptr == NULL) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	/* Create a base iterator for use in other iterators */
	res = derparser_create_iterator(
			&root_iterator,
			asn1pdu_ks,
			size,
			(uint8_t *)buffer,
			(const char **)(NULL));
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to create iterator\n");
		goto exit;
	}

	/* Sanity check on content */
	res = derparser_create_subset_iterator(
			&iterator,
			root_iterator,
			(const char **)(NULL));
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to create iterator\n");
		goto exit;
	}
	res = derparser_next(iterator, NULL);
	if (res < 0) {
		FCS_LOG_ERR("Failed to parse keystore\n");
		goto exit;
	}
	derparser_delete_iterator(iterator);
	iterator = NULL;

	/* Check version */
	res = ks_verify(root_iterator,
			ASN1PDU_MATCH_KS_VERSION,
			asn1pdu_ks_expect_version,
			asn1pdu_ks_expect_version_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Unexpected version\n");
		goto exit;
	}

	keystore = malloc(sizeof(struct ks_main));
	if (keystore == NULL) {
		FCS_LOG_ERR("Failed to allocate keystore\n");
		res = -FCSERR_ENOMEM;
		goto exit;
	}
	keystore->version = 1;
	keystore->xcs = 0;
	keystore->db.list.count = 0;
	keystore->db.list.array = NULL;

	/* Get XCS */
	res = ks_get_bool(root_iterator,
		ASN1PDU_MATCH_KS_XCS,
		&xcs);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Get xcs failed with %d\n", res);
		goto exit;
	}
	if (xcs)
		keystore->xcs = 1;

	/* Iterate entries */
	res = derparser_create_subset_iterator(
			&iterator,
			root_iterator,
			(const char **)(ASN1PDU_MATCH_KS_DB_ENTRY));
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to create entry iterator\n");
		goto exit;
	}
	/* Find first entry */
	res = derparser_next(iterator, NULL);
	if (res < 0) {
		FCS_LOG_ERR("Failed to parse keystore\n");
		goto exit;
	}
	while (res > 0) {
		/* Extract entry data */
		res = ks_get_int(iterator,
			ASN1PDU_MATCH_KS_DB_ENTRY_DOMAIN,
			&domain);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Get domain failed with %d\n", res);
			goto exit;
		}
		res = ks_get_buffer(iterator,
			ASN1PDU_MATCH_KS_DB_ENTRY_CERTIFICATE,
			&value_buffer, &value_buffer_len);
		if (res == FCSERR_OK) {
			present = KS_ENTRY_DATA_PR_CERTIFICATE;
		} else if (res == -FCSERR_ENOTF) {
			present = KS_ENTRY_DATA_PR_PUBLICKEY;
			res = ks_get_buffer(iterator,
				ASN1PDU_MATCH_KS_DB_ENTRY_PUBLICKEY,
				&value_buffer, &value_buffer_len);
		}
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to read entry data\n");
			goto exit;
		}
		/* Add entry to list */
		res = ks_add_entry(keystore,
				domain,
				present,
				value_buffer,
				value_buffer_len);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to add to keystore\n");
			goto exit;
		}
		/* Buffer is now owned by structure */
		value_buffer = NULL;

		/* Find next entry */
		res = derparser_next(iterator, NULL);
		if (res < 0) {
			FCS_LOG_ERR("Failed to parse keystore\n");
			goto exit;
		}
	}

	*keystore_ptr = keystore;
	keystore = NULL;

exit:
	free(value_buffer);
	ks_free(keystore);
	derparser_delete_iterator(iterator);
	derparser_delete_iterator(root_iterator);
	return res;
}

