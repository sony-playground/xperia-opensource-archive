/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#ifndef DER_PARSER_UTILS_H_
#define DER_PARSER_UTILS_H_

#include "der_parser.h"

/*
 * DESCRIPTION:
 *   The DER Parser Utils provides help functions to access fields
 *   in a DER structure.
 */

/*
 * Callback function to handle a field hit.
 *
 * @param [in] callback_context  pointer to implementation specific context
 * @param [in] res               result of the search (derparser_next(..))
 * @param [in] index             index of call (0: before first search)
 * @param [out] current          return object used in next search
 * @param [out] stop             stop/continue search
 *
 * @returns Success or error indication
 */
typedef int (*derparser_util_get_object_cb)(
	void *callback_context,
	int res,
	int index,
	struct derparser_object **current,
	bool *stop);

/*
 * General search function for single field of array.
 */
int derparser_util_get_object(
	struct iterator_info *root_iterator,
	const char **match,
	void *callback_context,
	derparser_util_get_object_cb callback);

/*
 * Find a single buffer.
 */
int derparser_util_get_buffer(
	struct iterator_info *root_iterator,
	const char **match,
	uint8_t *buffer,
	size_t min_size,
	size_t max_size,
	size_t *content_len);

/*
 * Find a single integer.
 */
int derparser_util_get_integer(
	struct iterator_info *root_iterator,
	const char **match,
	int *value,
	int min_value,
	int max_value);

/*
 * Find a single boolean.
 */
int derparser_util_get_boolean(
	struct iterator_info *root_iterator,
	const char **match,
	bool *value);

#endif

