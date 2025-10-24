/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#ifndef DER_PARSER_INTERNAL_H_
#define DER_PARSER_INTERNAL_H_

#include "der_parser.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/*
 * Value object type
 */
enum derparser_obj_type {
	DERPARSER_OBJ_TYPE_STRING,
	DERPARSER_OBJ_TYPE_INTEGER,
	DERPARSER_OBJ_TYPE_BOOLEAN,
	DERPARSER_OBJ_TYPE_BUFFER
};

struct derparser_object {
	enum derparser_obj_type type;
	union {
		char *string;
		int integer;
		bool boolean;
		struct {
			size_t   len;
			uint8_t *ptr;
		} buffer;
	} value;
};

/*
 * Iterator type
 */
struct iterator_info {
	const struct asn1_item *this;
	uint8_t *item_ptr;
	uint8_t *item_begin;
	uint8_t *item_end;
	int match_position;
	const char **match;
	struct iterator_info *parent_iterator;
	struct iterator_info *sub_iterator;
	bool suppress_log;
	void *local;
};

/*
 * Iterator functions
 */
struct iterator_info *derparser_create_unlinked_sub_iterator(
	struct iterator_info *parent,
	const struct asn1_item *sel_item);

/*
 * ASN1 Type handler functions
 */

#endif

