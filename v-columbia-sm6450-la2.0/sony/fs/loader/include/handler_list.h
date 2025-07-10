/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef HANDLER_LIST_H_
#define HANDLER_LIST_H_

#include "fcslist.h"

/**
 * The internal structure for the handler_list,
 * do NOT access the variables inside directly,
 * please use the wrapper functions.
 */
struct handler_list {
	void *handler;    /* The callback */
	void *data;       /* data passed to the callback */
	struct list_entry list; /* list data */
};

/**
 * Init a new list and allocate space for it.
 *
 * @return a s1 list
 */
struct list_entry *handler_list_init();

/**
 * Cleanup and destroy the handler_list,
 * and free all memory allocated by the init function.
 *
 * @param master_list that holds all the pointers to the list.
 */
void handler_list_destroy(struct list_entry *master_list);

/**
 * Insert a handler at the end of the list.
 *
 * @param master_list the list we work with.
 * @param handler the handler we like to add in the list.
 * @param data Data associated with the handler
 * @return FCSERR
 */
int handler_list_add_handler(struct list_entry *master_list, void *handler,
		void *data);

/**
 * Replace matching handler with provided handler.
 *
 * @param master_list the list we work with.
 * @param handler the handler we like to replace.
 * @param new_handler the handler we would like to use instead.
 * @param data Data associated with the new handler.
 * @return FCSERR
 */
int handler_list_replace_handler(struct list_entry *master_list,
		const void *handler, void *new_handler, void *data);

#endif /* HANDLER_LIST_H_ */
