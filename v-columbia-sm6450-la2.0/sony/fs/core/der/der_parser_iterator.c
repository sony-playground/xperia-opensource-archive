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
#include <string.h>

static struct iterator_info *derparser_create_sub_iterator(
	struct iterator_info *parent,
	const struct asn1_item *sel_item,
	int match_position)
{
	struct iterator_info *new_iterator = NULL;

	new_iterator = malloc(
		sizeof(struct iterator_info));
	if (new_iterator == NULL)
		goto derparser_create_sub_iterator_end;
	parent->sub_iterator = new_iterator;
	new_iterator->this = sel_item;
	new_iterator->item_ptr = parent->item_ptr;
	new_iterator->item_begin = parent->item_ptr;
	new_iterator->item_end = parent->item_end;
	new_iterator->match_position = match_position;
	new_iterator->match = parent->match;
	new_iterator->parent_iterator = parent;
	new_iterator->sub_iterator = NULL;
	new_iterator->local = NULL;
	new_iterator->suppress_log = parent->suppress_log;

derparser_create_sub_iterator_end:
	return new_iterator;
}

struct iterator_info *derparser_create_unlinked_sub_iterator(
	struct iterator_info *parent,
	const struct asn1_item *sel_item)
{
	struct iterator_info *new_iterator = NULL;

	new_iterator = malloc(
		sizeof(struct iterator_info));
	if (new_iterator == NULL)
		goto derparser_create_sub_iterator_end;
	new_iterator->this = sel_item;
	new_iterator->item_ptr = parent->item_ptr;
	new_iterator->item_begin = parent->item_ptr;
	new_iterator->item_end = parent->item_end;
	new_iterator->match_position = 0;
	new_iterator->match = NULL;
	new_iterator->parent_iterator = NULL;
	new_iterator->sub_iterator = NULL;
	new_iterator->local = NULL;
	new_iterator->suppress_log = true;

derparser_create_sub_iterator_end:
	return new_iterator;
}

static void derparser_delete_sub_iterator(
	struct iterator_info *parent)
{
	struct iterator_info *sub_iterator = parent->sub_iterator;

	if (sub_iterator != NULL) {
		free(sub_iterator->local);
		free(sub_iterator);
		parent->sub_iterator = NULL;
	}
}

int derparser_create_iterator(
	struct iterator_info **iterator,
	const struct asn1_item *format,
	size_t inbuf_len,
	uint8_t *inbuf,
	const char **match)
{
	int res = FCSERR_OK;
	struct iterator_info *new_iterator = NULL;
	uint8_t *buf_ptr = NULL;

	if ((iterator == NULL) ||
		(format == NULL) ||
		(inbuf_len == 0) ||
		(inbuf == NULL)) {
		FCS_LOG_ERR("Wrong params\n");
		res = -FCSERR_EINVAL;
		goto derparser_create_iterator_end;
	}

	new_iterator = malloc(
		sizeof(struct iterator_info) + inbuf_len);
	if (new_iterator == NULL) {
		FCS_LOG_ERR("Failed to allocate iterator info.\n");
		res = -FCSERR_ENOMEM;
		goto derparser_create_iterator_end;
	}
	/* Directly after iterator we place the copy of inbuf */
	buf_ptr = &((uint8_t *)new_iterator)[sizeof(struct iterator_info)];
	memcpy(buf_ptr, inbuf, inbuf_len);
	new_iterator->this = format;
	new_iterator->item_ptr = buf_ptr;
	new_iterator->item_begin = buf_ptr;
	new_iterator->item_end = &buf_ptr[inbuf_len];
	new_iterator->match_position = 0;
	new_iterator->match = match;
	new_iterator->parent_iterator = NULL;
	new_iterator->sub_iterator = NULL;
	new_iterator->local = NULL;
	new_iterator->suppress_log = false;
	*iterator = new_iterator;

derparser_create_iterator_end:
	return res;
};

int derparser_create_subset_iterator(
	struct iterator_info **iterator,
	struct iterator_info *parent,
	const char **match)
{
	int res = FCSERR_OK;
	struct iterator_info *cur_iter = NULL;
	struct iterator_info *new_iterator = NULL;

	if ((iterator == NULL) ||
		(parent == NULL)) {
		FCS_LOG_ERR("Wrong params\n");
		res = -FCSERR_EINVAL;
		goto derparser_create_subset_iterator_end;
	}

	/* Advance to last sub_iterator */
	cur_iter = parent;
	while (cur_iter->sub_iterator != NULL)
		cur_iter = cur_iter->sub_iterator;

	new_iterator = malloc(
		sizeof(struct iterator_info));
	if (new_iterator == NULL) {
		FCS_LOG_ERR("Failed to allocate iterator info.\n");
		res = -FCSERR_ENOMEM;
		goto derparser_create_subset_iterator_end;
	}
	new_iterator->this = cur_iter->this;
	new_iterator->item_ptr = cur_iter->item_begin;
	new_iterator->item_begin = cur_iter->item_begin;
	new_iterator->item_end = cur_iter->item_end;
	new_iterator->match_position = 0;
	new_iterator->match = match;
	new_iterator->parent_iterator = NULL;
	new_iterator->sub_iterator = NULL;
	new_iterator->local = NULL;
	new_iterator->suppress_log = parent->suppress_log;
	*iterator = new_iterator;

derparser_create_subset_iterator_end:
	return res;
};

int derparser_create_adjacent_iterator(
	struct iterator_info **adjacent,
	struct iterator_info *iterator,
	struct iterator_info *parent,
	const char **match)
{
	int res = FCSERR_OK;
	struct iterator_info *cur_iter = NULL;
	struct iterator_info *new_iterator = NULL;

	if ((adjacent == NULL) ||
		(iterator == NULL) ||
		(parent == NULL)) {
		FCS_LOG_ERR("Wrong params\n");
		res = -FCSERR_EINVAL;
		goto derparser_create_adjacent_iterator_end;
	}

	if (iterator->item_end != iterator->item_ptr) {
		FCS_LOG_ERR("Iterator is not finished\n");
		res = -FCSERR_EINVAL;
		goto derparser_create_adjacent_iterator_end;
	}

	/* Advance to last sub_iterator */
	cur_iter = parent;
	while (cur_iter->sub_iterator != NULL)
		cur_iter = cur_iter->sub_iterator;

	/* Check if we have adjacent content */
	if (cur_iter->item_end <= iterator->item_end) {
		/* No more content */
		*adjacent = NULL;
		goto derparser_create_adjacent_iterator_end;
	}

	new_iterator = malloc(
		sizeof(struct iterator_info));
	if (new_iterator == NULL) {
		FCS_LOG_ERR("Failed to allocate iterator info.\n");
		res = -FCSERR_ENOMEM;
		goto derparser_create_adjacent_iterator_end;
	}
	new_iterator->this = cur_iter->this;
	new_iterator->item_ptr = iterator->item_ptr;
	new_iterator->item_begin = iterator->item_ptr;
	new_iterator->item_end = cur_iter->item_end;
	new_iterator->match_position = 0;
	new_iterator->match = match;
	new_iterator->parent_iterator = NULL;
	new_iterator->sub_iterator = NULL;
	new_iterator->local = NULL;
	new_iterator->suppress_log = parent->suppress_log;
	*adjacent = new_iterator;

derparser_create_adjacent_iterator_end:
	return res;
};

void derparser_delete_iterator(
	struct iterator_info *iterator)
{
	struct iterator_info *cur_iter = NULL;

	if (iterator != NULL) {
		/* Advance to sub_iterator */
		cur_iter = iterator;
		while (cur_iter->sub_iterator != NULL)
			cur_iter = cur_iter->sub_iterator;
		/* Go back cleanup */
		while (cur_iter->parent_iterator != NULL) {
			cur_iter = cur_iter->parent_iterator;
			derparser_delete_sub_iterator(cur_iter);
		}
		/* Ground level cleanup */
		free(cur_iter->local);
		free(cur_iter);
	}
}

int derparser_next(struct iterator_info *iterator,
		struct derparser_object *value)
{
	int res = -FCSERR_EINFOR;
	int next_match_position = 0;
	const char **temp_match = NULL;
	bool found = false;
	struct iterator_info *cur_iter = NULL;
	const struct asn1_item *sel_item = NULL;

	if (iterator == NULL) {
		FCS_LOG_ERR("Wrong params\n");
		res = -FCSERR_EINVAL;
		goto derparser_next_end;
	}

	/* Advance to last sub_iterator */
	cur_iter = iterator;
	while (cur_iter != NULL && cur_iter->sub_iterator != NULL)
		cur_iter = cur_iter->sub_iterator;
	if (cur_iter == NULL) {
		FCS_LOG_ERR("Internal error\n");
		res = -FCSERR_ESTATE;
		goto derparser_next_end;
	}

	/* Advance one item */
	if (cur_iter->this == NULL) {
		FCS_LOG_ERR("Wrong reference format\n");
		res = -FCSERR_EINFOR;
		goto derparser_next_end;
	}
	/* Reset iterator state to beginning */
	cur_iter->item_ptr = cur_iter->item_begin;
	res = cur_iter->this->handler(
				cur_iter,
				&sel_item,
				NULL);
	if (res < 0)
		goto derparser_next_end;
	if (sel_item != NULL) {
		/* Going down into sub item */
		next_match_position = 0;
		if (cur_iter->match != NULL) {
			temp_match = &(cur_iter->match[
					cur_iter->match_position]);
			if (strncmp(cur_iter->this->name, temp_match[0],
					strlen(cur_iter->this->name) + 1) == 0)
				next_match_position =
					(cur_iter->match_position) + 1;
		}
		cur_iter = derparser_create_sub_iterator(
			cur_iter, sel_item, next_match_position);
		if (cur_iter == NULL) {
			FCS_LOG_ERR("Failed to allocate iterator info.\n");
			res = -FCSERR_ENOMEM;
			goto derparser_next_end;
		}
#ifdef DERPARSER_DBG
		FCS_LOG_INF("%s => %s\n",
			cur_iter->parent_iterator->this->name,
			cur_iter->this->name);
#endif
	} else {
		/* Leaving this item */
		if (cur_iter->parent_iterator == NULL) {
			/* End of format or opt search */
			if (cur_iter->item_end < cur_iter->item_ptr) {
				if (!iterator->suppress_log)
					FCS_LOG_ERR(
						"Unexpected end of data.\n");
				res = -FCSERR_EINFOR;
				goto derparser_next_end;
			} else  {
				res = FCSERR_OK;
				goto derparser_next_end;
			}
		}
#ifdef DERPARSER_DBG
		FCS_LOG_INF("%s => %s\n",
			cur_iter->this->name,
			cur_iter->parent_iterator->this->name);
#endif
		cur_iter = cur_iter->parent_iterator;
		if (cur_iter == NULL || cur_iter->sub_iterator == NULL) {
			FCS_LOG_ERR("Internal error\n");
			res = -FCSERR_ESTATE;
			goto derparser_next_end;
		}
		cur_iter->item_ptr = cur_iter->sub_iterator->item_ptr;
		derparser_delete_sub_iterator(cur_iter);
	}

	/* Start search for match */
	while (cur_iter != NULL) {
		/* Advance one item */
		if (cur_iter->this == NULL) {
			FCS_LOG_ERR("Wrong reference format\n");
			res = -FCSERR_EINFOR;
			goto derparser_next_end;
		}
		found = 0;
		next_match_position = 0;
		if (cur_iter->match != NULL) {
			temp_match = &(cur_iter->match[
					cur_iter->match_position]);
			if (strncmp(cur_iter->this->name, temp_match[0],
					strlen(cur_iter->this->name) + 1)
					== 0) {
				next_match_position =
					(cur_iter->match_position) + 1;
				temp_match = &(cur_iter->match[
						next_match_position]);
				/* Check pattern completely matched and
					new iterator */
				found = ((temp_match[0][0] == '\0') &&
					(cur_iter->item_ptr ==
						cur_iter->item_begin));
			}
		}
		if (found) {
			/* Found match */
			res = cur_iter->this->handler(
						cur_iter,
						&sel_item,
						value);
			if (res < 0)
				goto derparser_next_end;
			res = 1;
			goto derparser_next_end;
		} else {
			res = cur_iter->this->handler(
						cur_iter,
						&sel_item,
						NULL);
			if (res < 0)
				goto derparser_next_end;
		}
		if (sel_item != NULL) {
			/* Going down into sub item */
			cur_iter = derparser_create_sub_iterator(
				cur_iter, sel_item, next_match_position);
			if (cur_iter == NULL) {
				FCS_LOG_ERR(
					"Failed to allocate iterator info.\n");
				res = -FCSERR_ENOMEM;
				goto derparser_next_end;
			}
#ifdef DERPARSER_DBG
			FCS_LOG_INF("%s => %s\n",
				cur_iter->parent_iterator->this->name,
				cur_iter->this->name);
#endif
		} else {
			/* Leaving this item (Go up one level) */
			if (cur_iter->parent_iterator == NULL) {
				/* End of format or opt search */
				if (cur_iter->item_end < cur_iter->item_ptr) {
					if (!iterator->suppress_log)
						FCS_LOG_ERR(
						"Unexpected end of data.\n");
					res = -FCSERR_EINFOR;
					goto derparser_next_end;
				} else  {
					res = FCSERR_OK;
					goto derparser_next_end;
				}
			}
#ifdef DERPARSER_DBG
			FCS_LOG_INF("%s => %s\n",
				cur_iter->this->name,
				cur_iter->parent_iterator->this->name);
#endif
			cur_iter = cur_iter->parent_iterator;
			if (cur_iter == NULL ||
					cur_iter->sub_iterator == NULL) {
				FCS_LOG_ERR("Internal error\n");
				res = -FCSERR_ESTATE;
				goto derparser_next_end;
			}
			cur_iter->item_ptr = cur_iter->sub_iterator->item_ptr;
			derparser_delete_sub_iterator(cur_iter);
		}
	}

derparser_next_end:
	return res;
}

