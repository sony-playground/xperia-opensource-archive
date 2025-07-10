/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#include "der_parser.h"
#include "der_parser_intern.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

struct derparser_object *derparser_create_integer(void)
{
	struct derparser_object *res = (struct derparser_object *)malloc(
		sizeof(struct derparser_object));
	if (NULL != res) {
		res->type = DERPARSER_OBJ_TYPE_INTEGER;
		res->value.integer = 0;
	}
	return res;
}

struct derparser_object *derparser_create_boolean(void)
{
	struct derparser_object *res = (struct derparser_object *)malloc(
		sizeof(struct derparser_object));
	if (res != NULL) {
		res->type = DERPARSER_OBJ_TYPE_BOOLEAN;
		res->value.boolean = false;
	}
	return res;
}

struct derparser_object *derparser_create_string(void)
{
	struct derparser_object *res = (struct derparser_object *)malloc(
		sizeof(struct derparser_object));
	if (NULL != res) {
		res->type = DERPARSER_OBJ_TYPE_STRING;
		res->value.string = NULL;
	}
	return res;
}

struct derparser_object *derparser_create_buffer(void)
{
	struct derparser_object *res = (struct derparser_object *)malloc(
		sizeof(struct derparser_object));
	if (NULL != res) {
		res->type = DERPARSER_OBJ_TYPE_BUFFER;
		res->value.buffer.len = 0;
		res->value.buffer.ptr = NULL;
	}
	return res;
}

int derparser_get_integer(struct derparser_object *value)
{
	int res = -1;

	if (NULL != value) {
		if (value->type == DERPARSER_OBJ_TYPE_INTEGER)
			res = value->value.integer;
	}
	return res;
}

bool derparser_get_boolean(struct derparser_object *value)
{
	bool res = false;

	if (value != NULL) {
		if (value->type == DERPARSER_OBJ_TYPE_BOOLEAN)
			res = value->value.boolean;
	}
	return res;
}

char *derparser_get_string(struct derparser_object *value)
{
	char *res = NULL;

	if (NULL != value) {
		if (value->type == DERPARSER_OBJ_TYPE_STRING)
			res = value->value.string;
	}
	return res;
}

size_t derparser_get_buffer(struct derparser_object *value, uint8_t **ptr)
{
	size_t res = 0;

	if ((NULL != value) && (NULL != ptr)) {
		if (value->type == DERPARSER_OBJ_TYPE_BUFFER) {
			*ptr = value->value.buffer.ptr;
			res = value->value.buffer.len;
		}
	}
	return res;
}

void derparser_delete_object(struct derparser_object *value)
{
	if (NULL != value) {
		if (value->type == DERPARSER_OBJ_TYPE_STRING)
			free(value->value.string);
		else if (value->type == DERPARSER_OBJ_TYPE_BUFFER)
			free(value->value.buffer.ptr);
		free(value);
	}
}

