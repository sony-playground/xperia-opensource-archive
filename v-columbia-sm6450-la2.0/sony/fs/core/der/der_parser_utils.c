/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "der_parser_utils.h"
#include "fcslog.h"
#include <string.h>
#include "fcserr.h"

/*
 * Local functions
 */

/*
 * The function derparser_util_get_object will with the callback function
 * derparser_util_get_first_object_cb return the first content matching
 * the search pattern (match parameter in derparser_util_get_object).
 * The object which receives the content is provided as
 * callback_context.
 */
static int derparser_util_get_first_object_cb(
	void *callback_context,
	int res,
	int index,
	struct derparser_object **current,
	bool *stop)
{
	if (index == 0) {
		/* Setup dest object for the search */
		/* The dest obj is the context */
		*current = (struct derparser_object *)callback_context;
		*stop = false;
	} else {
		/* Check the result of the search */
		if (res == 1)
			res = FCSERR_OK;
		else if (res == 0)
			res = -FCSERR_ENOTF;
		*stop = true;
	}
	return res;
}

/*
 * Exported functions
 */
int derparser_util_get_object(
	struct iterator_info *root_iterator,
	const char **match,
	void *callback_context,
	derparser_util_get_object_cb callback)
{
	int res = FCSERR_OK;
	struct iterator_info *iterator = NULL;
	struct derparser_object *obj = NULL;
	bool stop = false;
	int idx = 0;

	if (root_iterator == NULL || match == NULL || callback == NULL) {
		FCS_LOG_ERR("Wrong parameters\n");
		res = -FCSERR_EINVAL;
		goto derparser_util_get_object_exit;
	}

	res = derparser_create_subset_iterator(
			&iterator,
			root_iterator,
			match);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to create iterator for field\n");
		goto derparser_util_get_object_exit;
	}
	res = callback(callback_context, res, idx, &obj, &stop);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("First callback failed\n");
		goto derparser_util_get_object_exit;
	}
	while (!stop) {
		idx++;
		res = derparser_next(iterator, obj);
		res = callback(callback_context, res, idx, &obj, &stop);
	}

derparser_util_get_object_exit:
	derparser_delete_iterator(iterator);
	return res;
}

int derparser_util_get_buffer(
	struct iterator_info *root_iterator,
	const char **match,
	uint8_t *buffer,
	size_t min_size,
	size_t max_size,
	size_t *content_len)
{
	int res = FCSERR_OK;
	struct derparser_object *buf_obj = NULL;
	uint8_t *buf;
	size_t buf_len;

	buf_obj = derparser_create_buffer();

	res = derparser_util_get_object(
			root_iterator,
			match,
			buf_obj,
			derparser_util_get_first_object_cb);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to find object\n");
		goto derparser_util_get_buffer_exit;
	}

	/* Check if we have a buffer */
	buf_len = derparser_get_buffer(buf_obj, &buf);
	if ((buf_len == 0) || (buf == NULL)) {
		FCS_LOG_ERR("Failed to get buffer\n");
		res = -FCSERR_ENOTF;
		goto derparser_util_get_buffer_exit;
	}
	/* Check field size */
	if ((buf_len < min_size) || (buf_len > max_size)) {
		FCS_LOG_ERR("Wrong field size\n");
		res = -FCSERR_EINVAL;
		goto derparser_util_get_buffer_exit;
	}
	memcpy(buffer, buf, buf_len);
	*content_len = buf_len;
	res = FCSERR_OK;

derparser_util_get_buffer_exit:
	derparser_delete_object(buf_obj);
	return res;
}

int derparser_util_get_integer(
	struct iterator_info *root_iterator,
	const char **match,
	int *value,
	int min_value,
	int max_value)
{
	int res = FCSERR_OK;
	struct derparser_object *int_obj = NULL;

	int_obj = derparser_create_integer();

	res = derparser_util_get_object(
			root_iterator,
			match,
			int_obj,
			derparser_util_get_first_object_cb);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to find object\n");
		goto derparser_util_get_integer_exit;
	}

	/* Check field value */
	if ((derparser_get_integer(int_obj) < min_value) ||
			(derparser_get_integer(int_obj) > max_value)) {
		FCS_LOG_ERR("Wrong field value\n");
		res = -FCSERR_EINVAL;
		goto derparser_util_get_integer_exit;
	}
	*value = derparser_get_integer(int_obj);
	res = FCSERR_OK;

derparser_util_get_integer_exit:
	derparser_delete_object(int_obj);
	return res;
}

int derparser_util_get_boolean(
	struct iterator_info *root_iterator,
	const char **match,
	bool *value)
{
	int res = FCSERR_OK;
	struct derparser_object *bool_obj = NULL;

	bool_obj = derparser_create_boolean();

	res = derparser_util_get_object(
			root_iterator,
			match,
			bool_obj,
			derparser_util_get_first_object_cb);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to find object\n");
		goto derparser_util_get_boolean_exit;
	}

	*value = derparser_get_boolean(bool_obj);
	res = FCSERR_OK;

derparser_util_get_boolean_exit:
	derparser_delete_object(bool_obj);
	return res;
}

