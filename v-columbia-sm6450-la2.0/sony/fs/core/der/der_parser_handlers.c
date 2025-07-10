/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#include "der_parser.h"
#include "der_parser_intern.h"
#include "fcserr.h"
#include "fcslog.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* Variants of headers */
#define DERPARSER_HNDL_TYPE_EXPLICIT     0
#define DERPARSER_HNDL_TYPE_TAG_EXPLICIT 1
#define DERPARSER_HNDL_TYPE_IMPLICIT     2
#define DERPARSER_HNDL_TYPE_TAG_IMPLICIT 3

/* ASN.1 types */
#define DERPARSER_TYPE_BOOLEAN           0x01
#define DERPARSER_TYPE_INTEGER           0x02
#define DERPARSER_TYPE_OCTET_STRING      0x04
#define DERPARSER_TYPE_OBJECT_IDENTIFIER 0x06
#define DERPARSER_TYPE_ENUMERATED        0x0A
#define DERPARSER_TYPE_UTF8STRING        0x0C
#define DERPARSER_TYPE_SEQUENCE          0x30

static int derparser_get_type(
	struct iterator_info *iterator,
	uint8_t **ptr, uint8_t *end)
{
	int res = FCSERR_OK;

	if ((NULL == ptr) || (NULL == end)) {
		if (!iterator->suppress_log)
			FCS_LOG_ERR("Wrong params\n");
		res = -FCSERR_EINVAL;
		goto derparser_get_type_end;
	}
	if (&(*ptr)[1] > end) {
		if (!iterator->suppress_log)
			FCS_LOG_ERR("Unexpected end\n");
		res = -FCSERR_ESIZE;
		goto derparser_get_type_end;
	}
	res = (*ptr)[0];
	(*ptr)++;
derparser_get_type_end:
	return res;
}

static int derparser_get_length(
	struct iterator_info *iterator,
	uint8_t **ptr, uint8_t *end)
{
	int res = 0;

	if ((NULL == ptr) || (NULL == end)) {
		if (!iterator->suppress_log)
			FCS_LOG_ERR("Wrong params\n");
		res = -FCSERR_EINVAL;
		goto derparser_get_length_end;
	}
	if (&(*ptr)[1] > end) {
		if (!iterator->suppress_log)
			FCS_LOG_ERR("Unexpected end\n");
		res = -FCSERR_ESIZE;
		goto derparser_get_length_end;
	}
	res = (*ptr)[0];
	if (res < 0x80) {
		(*ptr)++;
		goto derparser_get_length_end;
	}
	if (res == 0x81) {
		if (&(*ptr)[2] > end) {
			if (!iterator->suppress_log)
				FCS_LOG_ERR("Unexpected end\n");
			res = -FCSERR_ESIZE;
			goto derparser_get_length_end;
		}
		res = (int)((*ptr)[1]);
		(*ptr) += 2;
		goto derparser_get_length_end;
	}
	if (res == 0x82) {
		if (&(*ptr)[3] > end) {
			if (!iterator->suppress_log)
				FCS_LOG_ERR("Unexpected end\n");
			res = -FCSERR_ESIZE;
			goto derparser_get_length_end;
		}
		res = (int)((*ptr)[1])*256 + (int)((*ptr)[2]);
		(*ptr) += 3;
		goto derparser_get_length_end;
	}
	if (!iterator->suppress_log)
		FCS_LOG_ERR("Unexpected length format %x\n", res);
	res = -FCSERR_EINFOR;

derparser_get_length_end:
	return res;
}

static int derparser_handle_header(
	struct iterator_info *iterator,
	uint8_t **ptr,
	uint8_t *handler_type,
	int *type,
	int *length)
{
	int res = FCSERR_OK;
	uint8_t *iptr = NULL;
	int expected_tag = 0;
	int tag = 0;
	int tag_length = 0;
	uint8_t *tag_end = NULL;

	*ptr = iterator->item_begin;
	expected_tag = (int)ASN1ITEM_PARAM_TYPE(iterator->this->param);
	/* Determine type of header */
	if (ASN1ITEM_PARAM_IMPLICIT & iterator->this->param)
		if (0 != expected_tag)
			*handler_type = DERPARSER_HNDL_TYPE_TAG_IMPLICIT;
		else
			*handler_type = DERPARSER_HNDL_TYPE_IMPLICIT;
	else {
		if (0 != expected_tag)
			*handler_type = DERPARSER_HNDL_TYPE_TAG_EXPLICIT;
		else
			*handler_type = DERPARSER_HNDL_TYPE_EXPLICIT;
	}
	switch (*handler_type) {
	case DERPARSER_HNDL_TYPE_TAG_EXPLICIT:
		/* Expected format: <Tag byte><Length><Type byte><Length> */
		tag = derparser_get_type(iterator,
				ptr, iterator->item_end);
		tag_length = derparser_get_length(iterator,
				ptr, iterator->item_end);
		if (expected_tag != tag) {
			if (!iterator->suppress_log)
				FCS_LOG_ERR(
					"Unexpected tag %02x, expected %02x\n",
					tag, expected_tag);
			res = -FCSERR_EINFOR;
			goto derparser_handle_header_end;
		}
		if ((tag_length < 0) ||
				((*ptr) + tag_length > iterator->item_end)) {
			if (!iterator->suppress_log)
				FCS_LOG_ERR("Unexpected end\n");
			res = -FCSERR_EINFOR;
			goto derparser_handle_header_end;
		}
		tag_end = &(*ptr)[tag_length];
		*type = derparser_get_type(iterator,
				ptr, iterator->item_end);
		*length = derparser_get_length(iterator,
				ptr, iterator->item_end);
		if ((*length < 0) ||
				((*ptr) + (*length) > iterator->item_end)) {
			if (!iterator->suppress_log)
				FCS_LOG_ERR("Unexpected end\n");
			res = -FCSERR_EINFOR;
			goto derparser_handle_header_end;
		}
		iterator->item_end = &(*ptr)[*length];
		if (tag_end != iterator->item_end) {
			if (!iterator->suppress_log)
				FCS_LOG_ERR("Unexpected end\n");
			res = -FCSERR_EINFOR;
			goto derparser_handle_header_end;
		}
		break;

	case DERPARSER_HNDL_TYPE_TAG_IMPLICIT:
		/* Expected format: <Tag byte><Length> */
		tag = derparser_get_type(iterator,
				ptr, iterator->item_end);
		*length = derparser_get_length(iterator,
				ptr, iterator->item_end);
		if (expected_tag != tag) {
			if (!iterator->suppress_log)
				FCS_LOG_ERR("Unexpected tag %02x\n", tag);
			res = -FCSERR_EINFOR;
			goto derparser_handle_header_end;
		}
		if ((*length < 0) ||
				((*ptr) + (*length) > iterator->item_end)) {
			if (!iterator->suppress_log)
				FCS_LOG_ERR("Unexpected end\n");
			res = -FCSERR_EINFOR;
			goto derparser_handle_header_end;
		}
		iterator->item_end = &(*ptr)[*length];
		*type = 0;
		break;

	case DERPARSER_HNDL_TYPE_IMPLICIT:
		/* Expected format: No header */
		*length = 0;
		for (iptr = iterator->item_begin;
				iptr < iterator->item_end; iptr++) {
			(*length)++;
		}
		*ptr = iterator->item_begin;
		*type = 0;
		break;

	case DERPARSER_HNDL_TYPE_EXPLICIT:
		/* Expected format: <Type byte><Length> */
		*type = derparser_get_type(iterator,
				ptr, iterator->item_end);
		*length = derparser_get_length(iterator,
				ptr, iterator->item_end);
		if (((*length) < 0) ||
				((*ptr) + (*length) > iterator->item_end)) {
			if (!iterator->suppress_log)
				FCS_LOG_ERR("Unexpected end\n");
			res = -FCSERR_EINFOR;
			goto derparser_handle_header_end;
		}
		iterator->item_end = &(*ptr)[*length];
		break;

	default:
		FCS_LOG_ERR("Unexpected header variant\n");
		res = -FCSERR_EINFOR;
	}
derparser_handle_header_end:
	return res;
}

static int derparser_check_optional(
	struct iterator_info *iterator,
	const struct asn1_item *item)
{
	int res = FCSERR_OK;
	struct iterator_info *opt_iterator = NULL;

	opt_iterator = derparser_create_unlinked_sub_iterator(
		iterator,
		item);
	if (NULL == opt_iterator) {
		FCS_LOG_ERR("Failed to create sub iterator.\n");
		res = -FCSERR_ENOMEM;
		goto derparser_check_optional_end;
	}
	res = derparser_next(opt_iterator, NULL);
	if (res < 0)
		goto derparser_check_optional_end;
	if (opt_iterator->item_begin == opt_iterator->item_ptr) {
		if (!iterator->suppress_log)
			FCS_LOG_ERR("Zero length field!\n");
		res = -FCSERR_EINFOR;
		goto derparser_check_optional_end;
	}
	if (opt_iterator->item_end < opt_iterator->item_ptr) {
		if (!iterator->suppress_log)
			FCS_LOG_ERR("Unexpected length of field\n");
		res = -FCSERR_EINFOR;
	}

derparser_check_optional_end:
	derparser_delete_iterator(opt_iterator);
	return res;
}

int type_handler_enum(
	struct iterator_info *iterator,
	const struct asn1_item **select_item,
	struct derparser_object *value)
{
	int res = FCSERR_OK;
	uint8_t handler_type = 0;
	int type = 0;
	uint8_t *ptr = NULL;
	int length = 0;
	const char *name = NULL;
	size_t name_len = 0;
	int enum_val = 0;

	if ((NULL == iterator) ||
		(NULL == iterator->this) ||
		(0 == iterator->this->items_count) ||
		(NULL == iterator->this->items) ||
		(NULL == select_item)) {
		FCS_LOG_ERR("Wrong params\n");
		res = -FCSERR_EINVAL;
		goto type_handler_enum_end;
	}

	res = derparser_handle_header(
			iterator,
			&ptr,
			&handler_type,
			&type,
			&length);

	if (res < 0)
		goto type_handler_enum_end;

	if (((handler_type == DERPARSER_HNDL_TYPE_EXPLICIT) ||
		(handler_type == DERPARSER_HNDL_TYPE_TAG_EXPLICIT)) &&
			(type != DERPARSER_TYPE_ENUMERATED)) {
		if (!iterator->suppress_log)
			FCS_LOG_ERR("Unexpected type\n");
		res = -FCSERR_EINFOR;
		goto type_handler_enum_end;
	}

	if ((0x01 != length) ||
			(*ptr >= iterator->this->items_count)) {
		if (!iterator->suppress_log)
			FCS_LOG_ERR("Unexpected enum value\n");
		res = -FCSERR_EINFOR;
		goto type_handler_enum_end;
	}

	enum_val = *ptr;
	ptr++;
	if ((NULL  == iterator->item_ptr) ||
		(iterator->item_ptr < ptr)) {
		/* Beginning of enum */
		*select_item = &iterator->this->items[enum_val];
		iterator->item_ptr = ptr;
	} else if (iterator->item_ptr == iterator->item_end) {
		/* End of enum */
		*select_item = NULL;
	} else {
		/* Unexpected state */
		FCS_LOG_ERR("Unexpected end\n");
		res = -FCSERR_ESTATE;
		goto type_handler_enum_end;
	}
	if (NULL != value) {
		if (value->type == DERPARSER_OBJ_TYPE_INTEGER)
			value->value.integer = enum_val;
		else if (value->type == DERPARSER_OBJ_TYPE_STRING) {
			name = iterator->this->items[enum_val].name;
			name_len = strlen(name);
			free(value->value.string);
			value->value.string = (char *)malloc(name_len + 1);
			if (NULL == value->value.string) {
				FCS_LOG_ERR("Failed to alloc variable\n");
				res = -FCSERR_ENOMEM;
				goto type_handler_enum_end;
			}
			memcpy(value->value.string, name, name_len);
			value->value.string[name_len] = '\0';
		} else {
			FCS_LOG_ERR("Unpermitted variable\n");
			res = -FCSERR_PERM;
			goto type_handler_enum_end;
		}
	}

type_handler_enum_end:
	return res;
}

int type_handler_int(
	struct iterator_info *iterator,
	const struct asn1_item **select_item,
	struct derparser_object *value)
{
	int res = FCSERR_OK;
	uint8_t handler_type = 0;
	int type = 0;
	uint8_t *ptr = NULL;
	int length = 0;
	unsigned int neg_base = 0;
	unsigned int temp = 0;
	unsigned int n_value_bytes = 0;
	unsigned int idx_byte = 0;

	if ((NULL == iterator) ||
		(NULL == iterator->this) ||
		(0 != iterator->this->items_count) ||
		(NULL != iterator->this->items) ||
		(NULL == select_item)) {
		FCS_LOG_ERR("Wrong params\n");
		res = -FCSERR_EINVAL;
		goto type_handler_int_end;
	}

	res = derparser_handle_header(
			iterator,
			&ptr,
			&handler_type,
			&type,
			&length);

	if (res < 0)
		goto type_handler_int_end;

	if (((handler_type == DERPARSER_HNDL_TYPE_EXPLICIT) ||
		(handler_type == DERPARSER_HNDL_TYPE_TAG_EXPLICIT)) &&
			(type != DERPARSER_TYPE_INTEGER)) {
		if (!iterator->suppress_log)
			FCS_LOG_ERR("Unexpected type\n");
		res = -FCSERR_EINFOR;
		goto type_handler_int_end;
	}

	iterator->item_ptr = iterator->item_end;
	*select_item = NULL;

	neg_base = 0;
	temp = 0;
	idx_byte = 0;
	n_value_bytes = 0;
	while (ptr < iterator->item_end) {
		if (n_value_bytes + 1 > sizeof(int)) {
			FCS_LOG_ERR("Unexpected size of integer (%d)\n",
				n_value_bytes + 1);
			res = -FCSERR_ESIZE;
			goto type_handler_int_end;
		}
		if (idx_byte == 0) {
			/* First byte: update sign */
			neg_base = *ptr & 0x80;
			temp = *ptr & 0x7f;

			/* Update value byte count */
			if (*ptr != 0) {
				/*
				 * First byte not zero
				 */
				n_value_bytes++;
			}
		} else {
			neg_base <<= 8;
			temp <<= 8;
			temp += *ptr;

			/* Update value byte count */
			if (n_value_bytes > 0) {
				/*
				 * No initial byte
				 */
				n_value_bytes++;
			} else if (*ptr & 0x80) {
				/*
				 * Initial byte
				 * M S Bit is set but is not sign bit
				 * M S Byte must not be used to
				 * preserve the positive sign
				 */
				n_value_bytes += 2;
			} else if (*ptr) {
				/*
				 * Initial byte
				 * M S Bit is not set
				 * M S Byte may be used
				 */
				n_value_bytes++;
			}
		}
		ptr++;
		idx_byte++;
	}

	if (NULL != value) {
		if (value->type != DERPARSER_OBJ_TYPE_INTEGER) {
			FCS_LOG_ERR("Unpermitted variable\n");
			res = -FCSERR_PERM;
			goto type_handler_int_end;
		}
		value->value.integer = -neg_base + temp;
	}

type_handler_int_end:
	return res;
}

int type_handler_bool(
	struct iterator_info *iterator,
	const struct asn1_item **select_item,
	struct derparser_object *value)
{
	int res = FCSERR_OK;
	uint8_t handler_type = 0;
	int type = 0;
	uint8_t *ptr = NULL;
	int length = 0;
	bool temp = false;
	int i = 0;

	if ((iterator == NULL) ||
		(iterator->this == NULL) ||
		(iterator->this->items_count != 0) ||
		(iterator->this->items != NULL) ||
		(select_item == NULL)) {
		FCS_LOG_ERR("Wrong params\n");
		res = -FCSERR_EINVAL;
		goto type_handler_bool_end;
	}

	res = derparser_handle_header(
			iterator,
			&ptr,
			&handler_type,
			&type,
			&length);

	if (res < 0)
		goto type_handler_bool_end;

	if (((handler_type == DERPARSER_HNDL_TYPE_EXPLICIT) ||
		(handler_type == DERPARSER_HNDL_TYPE_TAG_EXPLICIT)) &&
		(type != DERPARSER_TYPE_BOOLEAN)) {
		if (!iterator->suppress_log)
			FCS_LOG_ERR("Unexpected type\n");
		res = -FCSERR_EINFOR;
		goto type_handler_bool_end;
	}

	iterator->item_ptr = iterator->item_end;
	*select_item = NULL;

	while (ptr < iterator->item_end) {
		i++;
		if (i > 1)
			break;
		if (*ptr)
			temp = true;
		ptr++;
	}
	if (i != 1) {
		FCS_LOG_ERR("Unexpected size of boolean (%d)\n", i);
		res = -FCSERR_ESIZE;
		goto type_handler_bool_end;
	}

	if (value != NULL) {
		if (value->type != DERPARSER_OBJ_TYPE_BOOLEAN) {
			FCS_LOG_ERR("Unpermitted variable\n");
			res = -FCSERR_PERM;
			goto type_handler_bool_end;
		}
		value->value.boolean = temp;
	}

type_handler_bool_end:
	return res;
}

int type_handler_octet(
	struct iterator_info *iterator,
	const struct asn1_item **select_item,
	struct derparser_object *value)
{
	int res = FCSERR_OK;
	uint8_t handler_type = 0;
	int type = 0;
	uint8_t *ptr = NULL;
	int length = 0;
	uint8_t *iptr = NULL;

	if ((NULL == iterator) ||
		(NULL == iterator->this) ||
		(0 != iterator->this->items_count) ||
		(NULL != iterator->this->items) ||
		(NULL == select_item)) {
		FCS_LOG_ERR("Wrong params\n");
		res = -FCSERR_EINVAL;
		goto type_handler_octet_end;
	}

	res = derparser_handle_header(
			iterator,
			&ptr,
			&handler_type,
			&type,
			&length);

	if (res < 0)
		goto type_handler_octet_end;

	if (((handler_type == DERPARSER_HNDL_TYPE_EXPLICIT) ||
		(handler_type == DERPARSER_HNDL_TYPE_TAG_EXPLICIT)) &&
			(type != DERPARSER_TYPE_OCTET_STRING)) {
		if (!iterator->suppress_log)
			FCS_LOG_ERR("Unexpected type\n");
		res = -FCSERR_EINFOR;
		goto  type_handler_octet_end;
	}

	iterator->item_ptr = iterator->item_end;
	*select_item = NULL;

	if (NULL != value) {
		if (value->type != DERPARSER_OBJ_TYPE_BUFFER) {
			FCS_LOG_ERR("Unpermitted variable\n");
			res = -FCSERR_PERM;
			goto type_handler_octet_end;
		}
		free(value->value.buffer.ptr);

		/* Valid use case. Value buffer can be empty */
		if (length == 0) {
			value->value.buffer.len = 0;
			value->value.buffer.ptr = NULL;
			goto type_handler_octet_end;
		}

		value->value.buffer.ptr = (uint8_t *)malloc(length);
		if (value->value.buffer.ptr == NULL) {
			FCS_LOG_ERR("Failed to alloc variable\n");
			res = -FCSERR_ENOMEM;
			goto type_handler_octet_end;
		}
		length = 0;
		for (iptr = ptr; iptr < iterator->item_end; iptr++) {
			value->value.buffer.ptr[length] = *iptr;
			length++;
		}
		value->value.buffer.len = length;
	}

type_handler_octet_end:
	return res;
}

int type_handler_object(
	struct iterator_info *iterator,
	const struct asn1_item **select_item,
	struct derparser_object *value)
{
	int res = FCSERR_OK;
	uint8_t handler_type = 0;
	int type = 0;
	uint8_t *ptr = NULL;
	int length = 0;
	uint8_t *iptr = NULL;

	if ((NULL == iterator) ||
		(NULL == iterator->this) ||
		(0 != iterator->this->items_count) ||
		(NULL != iterator->this->items) ||
		(NULL == select_item)) {
		FCS_LOG_ERR("Wrong params\n");
		res = -FCSERR_EINVAL;
		goto type_handler_object_end;
	}

	res = derparser_handle_header(
			iterator,
			&ptr,
			&handler_type,
			&type,
			&length);

	if (res < 0)
		goto type_handler_object_end;

	if (((handler_type == DERPARSER_HNDL_TYPE_EXPLICIT) ||
		(handler_type == DERPARSER_HNDL_TYPE_TAG_EXPLICIT)) &&
			(type != DERPARSER_TYPE_OBJECT_IDENTIFIER)) {
		if (!iterator->suppress_log)
			FCS_LOG_ERR("Unexpected type\n");
		res = -FCSERR_EINFOR;
		goto  type_handler_object_end;
	}

	iterator->item_ptr = iterator->item_end;
	*select_item = NULL;

	if (NULL != value) {
		if (value->type != DERPARSER_OBJ_TYPE_BUFFER) {
			FCS_LOG_ERR("Unpermitted variable\n");
			res = -FCSERR_PERM;
			goto type_handler_object_end;
		}
		free(value->value.buffer.ptr);
		value->value.buffer.ptr = (uint8_t *)malloc(length);
		if (value->value.buffer.ptr == NULL) {
			FCS_LOG_ERR("Failed to alloc variable\n");
			res = -FCSERR_ENOMEM;
			goto type_handler_object_end;
		}
		length = 0;
		for (iptr = ptr; iptr < iterator->item_end; iptr++) {
			value->value.buffer.ptr[length] = *iptr;
			length++;
		}
		value->value.buffer.len = length;
	}

type_handler_object_end:
	return res;
}

int type_handler_utf8(
	struct iterator_info *iterator,
	const struct asn1_item **select_item,
	struct derparser_object *value)
{
	int res = FCSERR_OK;
	uint8_t handler_type = 0;
	int type = 0;
	uint8_t *ptr = NULL;
	int length = 0;
	uint8_t *iptr = NULL;

	if ((NULL == iterator) ||
		(NULL == iterator->this) ||
		(0 != iterator->this->items_count) ||
		(NULL != iterator->this->items) ||
		(NULL == select_item)) {
		FCS_LOG_ERR("Wrong params\n");
		res = -FCSERR_EINVAL;
		goto type_handler_utf8_end;
	}

	res = derparser_handle_header(
			iterator,
			&ptr,
			&handler_type,
			&type,
			&length);

	if (res < 0)
		goto type_handler_utf8_end;

	if (((handler_type == DERPARSER_HNDL_TYPE_EXPLICIT) ||
		(handler_type == DERPARSER_HNDL_TYPE_TAG_EXPLICIT)) &&
			(type != DERPARSER_TYPE_UTF8STRING)) {
		if (!iterator->suppress_log)
			FCS_LOG_ERR("Unexpected type\n");
		res = -FCSERR_EINFOR;
		goto  type_handler_utf8_end;
	}

	iterator->item_ptr = iterator->item_end;
	*select_item = NULL;

	if (NULL != value) {
		if (value->type == DERPARSER_OBJ_TYPE_STRING) {
			free(value->value.string);
			value->value.string = (char *)malloc(length+1);
			if (value->value.string == NULL) {
				FCS_LOG_ERR("Failed to alloc variable\n");
				res = -FCSERR_ENOMEM;
				goto type_handler_utf8_end;
			}
			length = 0;
			for (iptr = ptr;
					iptr < iterator->item_end; iptr++) {
				value->value.string[length] = *iptr;
				if (*iptr > 0x7F)
					value->value.string[length] = '?';
				length++;
			}
			value->value.string[length] = '\0';
		} else if (value->type == DERPARSER_OBJ_TYPE_BUFFER) {
			free(value->value.buffer.ptr);
			value->value.buffer.ptr = (uint8_t *)malloc(length);
			if (value->value.buffer.ptr == NULL) {
				FCS_LOG_ERR("Failed to alloc variable\n");
				res = -FCSERR_ENOMEM;
				goto type_handler_utf8_end;
			}
			length = 0;
			for (iptr = ptr;
					iptr < iterator->item_end; iptr++) {
				value->value.buffer.ptr[length] = *iptr;
				length++;
			}
			value->value.buffer.len = length;
		} else {
			FCS_LOG_ERR("Unpermitted variable\n");
			res = -FCSERR_PERM;
			goto type_handler_utf8_end;
		}
	}

type_handler_utf8_end:
	return res;
}

int type_handler_choice(
	struct iterator_info *iterator,
	const struct asn1_item **select_item,
	struct derparser_object *value)
{
	int res = FCSERR_OK;
	const char *name = NULL;
	size_t name_len = 0;
	size_t buffer_len = 0;
	size_t i = 0;
	uint8_t handler_type = 0;
	int type = 0;
	uint8_t *ptr = NULL;
	int length = 0;

	if ((NULL == iterator) ||
		(NULL == iterator->this) ||
		(0 == iterator->this->items_count) ||
		(NULL == iterator->this->items) ||
		(NULL == select_item)) {
		FCS_LOG_ERR("Wrong params\n");
		res = -FCSERR_EINVAL;
		goto type_handler_choice_end;
	}

	/* This is a lookup handler not an actual field
	   => No header
	*/

	/* If item_ptr is greater than item_begin
	   => returning from sub item.
	*/
	if (iterator->item_begin < iterator->item_ptr) {
		*select_item = NULL;
		goto type_handler_choice_end;
	}

	/* Try if item is valid. If valid use that otherwise try next */
	for (i = 0; i < iterator->this->items_count; i++) {
		res = derparser_check_optional(
				iterator,
				&(iterator->this->items[i]));
		if (res == FCSERR_OK)
			break;
		else if (res != -FCSERR_EINFOR)
			goto type_handler_choice_end;
	}
	if (i == iterator->this->items_count) {
		if (!iterator->suppress_log)
			FCS_LOG_ERR("Unexpected choice\n");
		res = -FCSERR_EINFOR;
		goto type_handler_choice_end;
	}
	*select_item = &iterator->this->items[i];

	if (NULL != value) {
		if (value->type == DERPARSER_OBJ_TYPE_INTEGER)
			value->value.integer = i;
		else if (value->type == DERPARSER_OBJ_TYPE_STRING) {
			name = iterator->this->items[i].name;
			name_len = strlen(name);
			free(value->value.string);
			value->value.string = (char *)malloc(name_len + 1);
			if (NULL == value->value.string) {
				FCS_LOG_ERR("Failed to alloc variable\n");
				res = -FCSERR_ENOMEM;
				goto type_handler_choice_end;
			}
			memcpy(value->value.string, name, name_len);
			value->value.string[name_len] = '\0';
		} else if (value->type == DERPARSER_OBJ_TYPE_BUFFER) {
			res = derparser_handle_header(
					iterator,
					&ptr,
					&handler_type,
					&type,
					&length);

			if (res < 0)
				goto type_handler_choice_end;
			buffer_len = &ptr[length] - iterator->item_begin;
			free(value->value.buffer.ptr);
			value->value.buffer.ptr = malloc(buffer_len);
			if (value->value.buffer.ptr == NULL) {
				FCS_LOG_ERR("Failed to alloc variable\n");
				res = -FCSERR_ENOMEM;
				goto type_handler_choice_end;
			}
			memcpy(value->value.buffer.ptr,
				iterator->item_begin,
				buffer_len);
			value->value.buffer.len = buffer_len;
		} else {
			FCS_LOG_ERR("Unpermitted variable\n");
			res = -FCSERR_PERM;
			goto type_handler_choice_end;
		}
	}

type_handler_choice_end:
	return res;
}

static int type_handler_any_of_intern(
	int expected_type,
	struct iterator_info *iterator,
	const struct asn1_item **select_item,
	struct derparser_object *value)
{
	int res = FCSERR_OK;
	uint8_t handler_type = 0;
	int type = 0;
	uint8_t *ptr = NULL;
	int length = 0;
	uint8_t *iptr = NULL;

	if ((NULL == iterator) ||
		(NULL == iterator->this) ||
		(1 != iterator->this->items_count) ||
		(NULL == iterator->this->items) ||
		(NULL == select_item)) {
		FCS_LOG_ERR("Wrong params\n");
		res = -FCSERR_EINVAL;
		goto type_handler_any_of_intern_end;
	}

	res = derparser_handle_header(
			iterator,
			&ptr,
			&handler_type,
			&type,
			&length);

	if (res < 0)
		goto type_handler_any_of_intern_end;

	if (((handler_type == DERPARSER_HNDL_TYPE_EXPLICIT) ||
		(handler_type == DERPARSER_HNDL_TYPE_TAG_EXPLICIT)) &&
			(type != expected_type)) {
		if (!iterator->suppress_log)
			FCS_LOG_ERR("Unexpected type\n");
		res = -FCSERR_EINFOR;
		goto  type_handler_any_of_intern_end;
	}

	if ((NULL  == iterator->item_ptr) ||
			((iterator->item_ptr < ptr) &&
			(iterator->item_ptr < &ptr[length]))) {
		/* Beginning of sequence */
		*select_item = &iterator->this->items[0];
		iterator->item_ptr = ptr;
		/* Empty list */
		if (iterator->item_ptr >= &ptr[length]) {
			/* End of sequence (no items) */
			*select_item = NULL;
		}
	} else if (iterator->item_ptr >= &ptr[length]) {
		/* End of sequence */
		*select_item = NULL;
	} else {
		/* Inside sequence */
		*select_item = &iterator->this->items[0];
	}

	if (NULL != value) {
		if (value->type != DERPARSER_OBJ_TYPE_BUFFER) {
			FCS_LOG_ERR("Unpermitted variable\n");
			res = -FCSERR_PERM;
			goto type_handler_any_of_intern_end;
		}
		free(value->value.buffer.ptr);
		value->value.buffer.ptr = (uint8_t *)malloc(length);
		if (value->value.buffer.ptr == NULL) {
			FCS_LOG_ERR("Failed to alloc variable\n");
			res = -FCSERR_ENOMEM;
			goto type_handler_any_of_intern_end;
		}
		length = 0;
		for (iptr = ptr; iptr < iterator->item_end; iptr++) {
			value->value.buffer.ptr[length] = *iptr;
			length++;
		}
		value->value.buffer.len = length;
	}

type_handler_any_of_intern_end:
	return res;
}

int type_handler_seq_of(
	struct iterator_info *iterator,
	const struct asn1_item **select_item,
	struct derparser_object *value)
{
	return type_handler_any_of_intern(DERPARSER_TYPE_SEQUENCE,
		iterator, select_item, value);
}

int type_handler_set_of(
	struct iterator_info *iterator,
	const struct asn1_item **select_item,
	struct derparser_object *value)
{
	return type_handler_any_of_intern(0x31,
		iterator, select_item, value);
}

struct type_handler_seq_info {
	uint32_t index;
	uint8_t *ptr;
};

/*
 * Skip optional items from *index and update current index.
 */
static int type_handler_seq_skip_optional(
	struct iterator_info *iterator,
	uint32_t *index)
{
	int res = FCSERR_OK;
	const struct asn1_item *next_item = NULL;

	if (*index >= iterator->this->items_count)
		goto type_handler_seq_skip_optional_end;
	next_item = &iterator->this->items[*index];
	while ((next_item != NULL) &&
		(ASN1ITEM_PARAM_IS_OPTIONAL((next_item)->param))) {
		(*index)++;
		if (*index >= iterator->this->items_count)
			goto type_handler_seq_skip_optional_end;
		next_item = &iterator->this->items[*index];
	}
	if (next_item == NULL) {
		FCS_LOG_ERR("Unexpected state\n");
		res = -FCSERR_ESTATE;
	}
type_handler_seq_skip_optional_end:
	return res;
}

/*
 * Walk through item array from *index and if item is
 * - Mandatory: return item and current index.
 * - Optional: Test if item match content
 *               If no match goto next item.
 *               else return item and current index.
 * - No more items: return NULL and current index.
 */
static int type_handler_seq_check_optional(
	struct iterator_info *iterator,
	uint32_t *index,
	const struct asn1_item **next_item)
{
	int res = FCSERR_OK;

	if (*index >= iterator->this->items_count) {
		if (!iterator->suppress_log)
			FCS_LOG_ERR("Index out of range.\n");
		res = -FCSERR_EINFOR;
		goto type_handler_seq_check_optional_end;
	}
	*next_item = &iterator->this->items[*index];

	while ((*next_item != NULL) &&
			ASN1ITEM_PARAM_IS_OPTIONAL((*next_item)->param) &&
			ASN1ITEM_PARAM_TYPE((*next_item)->param) !=
			iterator->item_ptr[0]) {
		res = derparser_check_optional(iterator, *next_item);
		if (res != -FCSERR_EINFOR)
			goto type_handler_seq_check_optional_end;
		(*index)++;
		if (*index >= iterator->this->items_count)
			*next_item = NULL;
		else
			*next_item = &iterator->this->items[*index];
	}
	res = FCSERR_OK;

type_handler_seq_check_optional_end:
	return res;
}

int type_handler_seq(
	struct iterator_info *iterator,
	const struct asn1_item **select_item,
	struct derparser_object *value)
{
	int res = FCSERR_OK;
	uint8_t handler_type = 0;
	int type = 0;
	uint8_t *ptr = NULL;
	int length = 0;
	struct type_handler_seq_info *info = NULL;
	const struct asn1_item *next_item = NULL;
	size_t buffer_len = 0;


	if ((NULL == iterator) ||
		(NULL == iterator->this) ||
		(0 == iterator->this->items_count) ||
		(NULL == iterator->this->items) ||
		(NULL == select_item)) {
		FCS_LOG_ERR("Wrong params\n");
		res = -FCSERR_EINVAL;
		goto type_handler_seq_end;
	}
	if (NULL == iterator->local) {
		iterator->local = (void *)malloc(
			sizeof(struct type_handler_seq_info));
		if (NULL == iterator->local) {
			FCS_LOG_ERR("Failed to allocate iterator info.\n");
			res = -FCSERR_ENOMEM;
			goto type_handler_seq_end;
		}
		info = (struct type_handler_seq_info *)(iterator->local);
		info->index = 0;
		info->ptr = iterator->item_begin;
	}
	info = (struct type_handler_seq_info *)(iterator->local);

	res = derparser_handle_header(
			iterator,
			&ptr,
			&handler_type,
			&type,
			&length);

	if (res < 0)
		goto type_handler_seq_end;

	if (((handler_type == DERPARSER_HNDL_TYPE_EXPLICIT) ||
		(handler_type == DERPARSER_HNDL_TYPE_TAG_EXPLICIT)) &&
			(type != DERPARSER_TYPE_SEQUENCE)) {
		if (!iterator->suppress_log)
			FCS_LOG_ERR("Unexpected type\n");
		res = -FCSERR_EINFOR;
		goto type_handler_seq_end;
	}

	if ((NULL  == iterator->item_ptr) ||
			((iterator->item_ptr < ptr) &&
			(iterator->item_ptr < &ptr[length]))) {
		/* Beginning of sequence */
		iterator->item_ptr = ptr;
		info->ptr = ptr;
		info->index = 0;
		/* Are optional items present? */
		res = type_handler_seq_check_optional(
				iterator,
				&(info->index),
				&next_item);
		if (res < 0)
			goto type_handler_seq_end;
		if (next_item == NULL) {
			/* Still content left to process,
			 * but no more items in format specification.
			 * The handler has found unspecified content.
			 */
			if (!iterator->suppress_log)
				FCS_LOG_ERR("Unspecified content\n");
			res = -FCSERR_EINFOR;
			goto type_handler_seq_end;
		}
		*select_item = next_item;
	} else if (iterator->item_ptr >= &ptr[length]) {
		/* End of sequence */
		if (iterator->item_ptr > info->ptr) {
			info->ptr = iterator->item_ptr;
			(info->index)++;
		}
		/* Make sure remaining items are optional. */
		res = type_handler_seq_skip_optional(
				iterator,
				&(info->index));
		if (res < 0)
			goto type_handler_seq_end;
		if (info->index != iterator->this->items_count) {
			if (!iterator->suppress_log)
				FCS_LOG_ERR("Unexpected end\n");
			res = -FCSERR_EINFOR;
			goto type_handler_seq_end;
		}
		*select_item = NULL;
	} else {
		/* Inside sequence */
		if (iterator->item_ptr > info->ptr) {
			info->ptr = iterator->item_ptr;
			(info->index)++;
		}
		/* Are optional items present? */
		res = type_handler_seq_check_optional(
				iterator,
				&(info->index),
				&next_item);
		if (res < 0)
			goto type_handler_seq_end;
		if (next_item == NULL) {
			/* Still content left to process,
			 * but no more items in format specification.
			 * The handler has found unspecified content.
			 */
			if (!iterator->suppress_log)
				FCS_LOG_ERR("Unspecified content\n");
			res = -FCSERR_EINFOR;
			goto type_handler_seq_end;
		}
		*select_item = next_item;
	}

	if (NULL != value) {
		if (value->type == DERPARSER_OBJ_TYPE_BUFFER) {
			buffer_len = &ptr[length] - iterator->item_begin;
			free(value->value.buffer.ptr);
			value->value.buffer.ptr = malloc(buffer_len);
			if (value->value.buffer.ptr == NULL) {
				FCS_LOG_ERR("Failed to alloc variable\n");
				res = -FCSERR_ENOMEM;
				goto type_handler_seq_end;
			}
			memcpy(value->value.buffer.ptr,
				iterator->item_begin,
				buffer_len);
			value->value.buffer.len = buffer_len;
		} else {
			FCS_LOG_ERR("Unpermitted variable\n");
			res = -FCSERR_PERM;
			goto type_handler_seq_end;
		}
	}

type_handler_seq_end:
	return res;
}

int type_handler_any(
	struct iterator_info *iterator,
	const struct asn1_item **select_item,
	struct derparser_object *value)
{
	int res = FCSERR_OK;
	uint8_t handler_type = 0;
	int type = 0;
	uint8_t *ptr = NULL;
	int length = 0;
	uint8_t *iptr = NULL;
	size_t i = 0;

	if ((NULL == iterator) ||
		(NULL == iterator->this) ||
		((0 < iterator->this->items_count) &&
		(NULL == iterator->this->items)) ||
		(NULL == select_item)) {
		FCS_LOG_ERR("Wrong params\n");
		res = -FCSERR_EINVAL;
		goto type_handler_any_end;
	}

	res = derparser_handle_header(
			iterator,
			&ptr,
			&handler_type,
			&type,
			&length);

	if (res < 0)
		goto type_handler_any_end;

	for (i = 0; i < iterator->this->items_count; i++) {
		if (iterator->this->items[i].param == (uint32_t)type) {
			if (!iterator->suppress_log)
				FCS_LOG_ERR("Unexpected type\n");
			res = -FCSERR_EINFOR;
			goto type_handler_any_end;
		}
	}
	if ((iterator->this->items_count > 0) &&
			(i == iterator->this->items_count)) {
		if (!iterator->suppress_log)
			FCS_LOG_ERR("Unexpected type\n");
		res = -FCSERR_EINFOR;
		goto type_handler_any_end;
	}

	iterator->item_ptr = iterator->item_end;
	*select_item = NULL;

	if (NULL != value) {
		if (value->type == DERPARSER_OBJ_TYPE_BUFFER) {
			free(value->value.buffer.ptr);
			/* Allocate space for both max header and payload */
			value->value.buffer.ptr = (uint8_t *)malloc(length+8);
			if (value->value.buffer.ptr == NULL) {
				FCS_LOG_ERR("Failed to alloc variable\n");
				res = -FCSERR_ENOMEM;
				goto type_handler_any_end;
			}
			length = 0;
			/* Any content: Include header */
			for (iptr = iterator->item_begin;
					iptr < iterator->item_end; iptr++) {
				value->value.buffer.ptr[length] = *iptr;
				length++;
			}
			value->value.buffer.len = length;
		} else {
			FCS_LOG_ERR("Unpermitted variable\n");
			res = -FCSERR_PERM;
			goto type_handler_any_end;
		}
	}

type_handler_any_end:
	return res;
}

int type_handler_none(
	struct iterator_info *iterator,
	const struct asn1_item **select_item,
	struct derparser_object *value)
{
	int res = FCSERR_OK;

	(void)(value); /* Unused parameter */

	if ((NULL == iterator) ||
		(NULL == iterator->this) ||
		(0 != iterator->this->items_count) ||
		(NULL != iterator->this->items) ||
		(NULL == select_item)) {
		FCS_LOG_ERR("Incorrect parameters\n");
		res = -FCSERR_EINVAL;
		goto type_handler_any_end;
	}

	iterator->item_ptr = iterator->item_end;
	*select_item = NULL;

type_handler_any_end:
	return res;
}
