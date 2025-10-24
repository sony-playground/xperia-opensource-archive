/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#ifndef DER_PARSER_H_
#define DER_PARSER_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/*
 * DESCRIPTION:
 *   The DER Parser is responsible for parse DER formats specificly rules
 *   concerning usage of image and binding towards devices.
 *   This file contains the interface used by Rule Verifier implementation.
 */

/*
 * Value object type
 */
struct derparser_object;

/*
 * Iterator type
 */
struct iterator_info;

/*
 * ASN1 config item type
 */
struct asn1_item;

/*
 * ASN1 type handler function
 */
typedef int (*type_handler_t)(struct iterator_info *iterator,
	const struct asn1_item **select_item,
	struct derparser_object *value);

struct asn1_item {
	uint32_t param;
	const char *name;
	type_handler_t handler;
	size_t items_count;
	const struct asn1_item *items;
};

/*
 * ASN1 param defines
 */
#define ASN1ITEM_PARAM_IMPLICIT			(0x200)
#define ASN1ITEM_PARAM_OPTIONAL			(0x100)
#define ASN1ITEM_PARAM_IS_OPTIONAL(param)	((0x100 & param) >> 8)
#define ASN1ITEM_PARAM_TYPE(param)		(0x0FF & param)

/*
 * Value object create functions
 */
struct derparser_object *derparser_create_integer(void);

struct derparser_object *derparser_create_boolean(void);

struct derparser_object *derparser_create_string(void);

struct derparser_object *derparser_create_buffer(void);

/*
 * Value object get functions
 */
int derparser_get_integer(struct derparser_object *value);

bool derparser_get_boolean(struct derparser_object *value);

char *derparser_get_string(struct derparser_object *value);

size_t derparser_get_buffer(struct derparser_object *value, uint8_t **ptr);

/*
 * Value object detele function
 */
void derparser_delete_object(struct derparser_object *value);

/*
 * Iterator functions
 */
/*
 * Create iterator for DER content
 *
 * Create iterator for content starting at beginning of content
 * If match pattern path is provided parse until match else
 * parse until end.
 *
 * @param [out] iterator       New Iterator handle
 * @param [in]  format         Exptected ASN1 format
 * @param [in]  inbuf_len      Length of DER content
 * @param [in]  inbuf          DER content
 * @param [in]  match          Match pattern path (optional)
 *
 * returns int
 */
int derparser_create_iterator(
	struct iterator_info **iterator,
	const struct asn1_item *format,
	size_t inbuf_len,
	uint8_t *inbuf,
	const char **match);

/*
 * Create iterator for subset of DER content
 *
 * Create iterator for subset of DER content starting at parent position
 *
 * @param [out] iterator       New Iterator handle
 * @param [in]  parent         Parent iterator handle
 *
 * returns int
 */
int derparser_create_subset_iterator(
	struct iterator_info **iterator,
	struct iterator_info *parent,
	const char **match);

/*
 * Create iterator for adjacent content of iterator
 *
 * Create iterator for adjacent content of iterator starting at current
 * iterators end position and ending at parents end position.
 * If no adjacent content parameter adjacent will be NULL.
 * Iteration with current iterator should be finished.
 *
 * @param [out] adjacent       New iterator handle
 * @param [in]  iterator       Current iterator handle
 * @param [in]  parent         Parent iterator handle
 *
 * returns int
 */
int derparser_create_adjacent_iterator(
	struct iterator_info **adjacent,
	struct iterator_info *iterator,
	struct iterator_info *parent,
	const char **match);

/*
 * Delete iterator
 *
 * @param [in]  iterator       Iterator handle
 *
 * returns none
 */
void derparser_delete_iterator(
	struct iterator_info *iterator);


/*
 * Parse through the content from iterator position
 *
 * Parse through the content from iterator position. If pattern match stop
 * parsing.
 *
 * @param [in]  iterator       Iterator handle
 * @param [out] value          Object receiving DER content at match position
 *
 * returns int:
 *    < 0 : Error
 *    0   : Format is OK but no match.
 *    1   : Format is OK and match.
 */
int derparser_next(
	struct iterator_info *iterator,
	struct derparser_object *value);

/*
 * ASN1 Type handler functions
 */
int type_handler_enum(struct iterator_info *iterator,
	const struct asn1_item **select_item,
	struct derparser_object *value);

int type_handler_int(struct iterator_info *iterator,
	const struct asn1_item **select_item,
	struct derparser_object *value);

int type_handler_bool(struct iterator_info *iterator,
	const struct asn1_item **select_item,
	struct derparser_object *value);

int type_handler_octet(struct iterator_info *iterator,
	const struct asn1_item **select_item,
	struct derparser_object *value);

int type_handler_object(struct iterator_info *iterator,
	const struct asn1_item **select_item,
	struct derparser_object *value);

int type_handler_utf8(struct iterator_info *iterator,
	const struct asn1_item **select_item,
	struct derparser_object *value);

int type_handler_choice(
	struct iterator_info *iterator,
	const struct asn1_item **select_item,
	struct derparser_object *value);

int type_handler_seq(struct iterator_info *iterator,
	const struct asn1_item **select_item,
	struct derparser_object *value);

int type_handler_seq_of(
	struct iterator_info *iterator,
	const struct asn1_item **select_item,
	struct derparser_object *value);

int type_handler_set_of(
	struct iterator_info *iterator,
	const struct asn1_item **select_item,
	struct derparser_object *value);

int type_handler_any(struct iterator_info *iterator,
	const struct asn1_item **select_item,
	struct derparser_object *value);

int type_handler_none(struct iterator_info *iterator,
	const struct asn1_item **select_item,
	struct derparser_object *value);


#endif

