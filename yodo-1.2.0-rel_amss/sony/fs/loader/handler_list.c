/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdlib.h>
#include "fcserr.h"
#include "fcslog.h"
#include "handler_list.h"

struct list_entry *handler_list_init()
{
	struct list_entry *master_list = malloc(sizeof(struct list_entry));

	if (master_list == NULL) {
		FCS_LOG_ERR("Malloc failed!\n");
		return NULL;
	}

	list_init(master_list);

	return master_list;
}

void handler_list_destroy(struct list_entry *master_list)
{
	struct handler_list *var_list;

	if (!master_list)
		return;

	while (!list_empty(master_list)) {
		var_list = LIST_FIRST(master_list, struct handler_list, list);
		list_remove(&var_list->list);
		free(var_list);
	}

	free(master_list);
}

int handler_list_add_handler(struct list_entry *master_list,
		void *handler, void *data)
{
	struct handler_list *list_item = malloc(sizeof(struct handler_list));

	if (list_item == NULL) {
		FCS_LOG_ERR("Malloc failed!\n");
		return -FCSERR_ENOMEM;
	}

	list_item->handler = handler;
	list_item->data = data;
	list_add_tail(master_list, &(list_item->list));

	return FCSERR_OK;
}

int handler_list_replace_handler(struct list_entry *master_list,
		const void *handler, void *new_handler, void *data)
{
	int res = -FCSERR_ENOTF;
	struct list_entry *e;

	LIST_FOR_EACH(master_list, e)
	{
		struct handler_list *candidate = LIST_DATA(e,
				struct handler_list, list);
		if (candidate->handler == handler) {
			candidate->handler = new_handler;
			candidate->data = data;
			res = FCSERR_OK;
			break;
		}
	}
	return res;
}
