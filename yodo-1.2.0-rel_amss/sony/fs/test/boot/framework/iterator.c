/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "integration_main.h"
#include "iterator.h"
#include "fcserr.h"
#include <stdlib.h>
#include <string.h>

static struct module_info *find_next_module(
		struct iterator_info *it, const char *match)
{
	struct module_info *p_module = NULL;
	unsigned int cmp_len = 0;

	while (it->cur_module < it->n_modules) {
		p_module = &(it->module[it->cur_module]);
		if (NULL == p_module ||
				NULL == p_module->name ||
				NULL == p_module->func) {
			p_module = NULL;
			break;
		}
		cmp_len = strlen(p_module->name) > strlen(match) ?
					strlen(match) : strlen(p_module->name);
		if (0 == strncmp(p_module->name, match, cmp_len))
			break;
		p_module = NULL;
		(it->cur_module)++;
	}
	return p_module;
}

int add_module(struct iterator_info *it, const char *name, fcsmt_func_t func)
{
	struct module_info *next_allocation = NULL;

	if (NULL == it)
		return -FCSERR_EINVAL;
	if ((it->module == NULL) || (it->n_allocated <= it->n_modules)) {
		next_allocation = malloc(sizeof(struct module_info) *
					(it->n_allocated+10));
		if (NULL == next_allocation)
			return -FCSERR_ENOMEM;
		if (NULL != it->module) {
			memcpy(next_allocation, it->module,
				sizeof(struct module_info) * it->n_modules);
			free(it->module);
		}
		it->n_allocated += 10;
		it->module = next_allocation;
	}
	it->module[it->n_modules].name = name;
	it->module[it->n_modules].func = func;
	(it->n_modules)++;

	return FCSERR_OK;
}

int setup_iterator(struct iterator_info **it,
			struct iterator_tcstate *state,
			void (*export_tcstate)(
				struct iterator_tcstate *tcstate))
{
	struct iterator_info *loc = NULL;

	if (NULL == it || NULL == export_tcstate)
		return -FCSERR_EINVAL;

	loc = malloc(sizeof(struct iterator_info));
	if (NULL == loc)
		return -FCSERR_ENOMEM;
	loc->n_modules = 0;
	loc->n_allocated = 0;
	loc->cur_module = 0;
	loc->cur_module_item = -1;
	loc->tcstate.n_failed = 0;
	loc->tcstate.n_executed = 0;
	loc->tcstate.next_module = 0;
	loc->tcstate.next_module_item = -1;
	loc->export_tcstate = export_tcstate;
	loc->module = NULL;

	if (NULL != state) {
		loc->tcstate.n_failed = state->n_failed;
		loc->tcstate.n_executed = state->n_executed;
		loc->tcstate.next_module = state->next_module;
		loc->cur_module = state->next_module;
		loc->tcstate.next_module_item = state->next_module_item;
		loc->cur_module_item = state->next_module_item;
	}

	*it = loc;

	return FCSERR_OK;
}

void teardown_iterator(struct iterator_info *it)
{
	free(it);
}

int execute_module(fcsmt_log_t log,
		struct iterator_info *it,
		const char *match)
{
	int res = -FCSERR_ENOTF;
	unsigned int n_failed_loc = 0;
	unsigned int n_executed_loc = 0;
	struct module_info *p_module = NULL;

	if (NULL == log || NULL == it || NULL == match)
		return -FCSERR_EINVAL;

	if (NULL == it->module || 0 == it->n_modules)
		return -FCSERR_EINVAL;

	if (it->tcstate.next_module_item >= 0) {
		it->cur_module = it->tcstate.next_module;
		if (it->cur_module >= it->n_modules)
			return -FCSERR_ENOTF;
		p_module = &(it->module[it->cur_module]);
		if (NULL == p_module ||
				NULL == p_module->name ||
				NULL == p_module->func)
			return -FCSERR_EINVAL;
		it->cur_module_item = it->tcstate.next_module_item;
		it->tcstate.next_module_item = -1;
	} else {
		p_module = find_next_module(it, match);
		if (p_module == NULL)
			return -FCSERR_ENOTF;
		it->cur_module_item = -1;
		it->tcstate.next_module_item = -1;
	}

	log("Executing tests in module %s\n", p_module->name);

	n_failed_loc = it->tcstate.n_failed;
	n_executed_loc = it->tcstate.n_executed;
	if (it->cur_module_item < 0)
		it->cur_module_item = 0;
	res = p_module->func(it, log, match);

	if (res != FCSERR_OK) {
		log("Failed to run tests in module %s\n", p_module->name);
		return res;
	}
	if (n_executed_loc < it->tcstate.n_executed) {
		if (n_failed_loc < it->tcstate.n_failed)
			log("%u tests failed in module %s\n",
				it->tcstate.n_failed - n_failed_loc,
				p_module->name);
		else
			log("Tests succeeded in module %s\n",
				p_module->name);
	}
	/* Check next test case */
	if (it->tcstate.next_module_item >= 0) {
		p_module = NULL;
		if (it->cur_module < it->n_modules) {
			p_module = &(it->module[it->cur_module]);
			if (NULL == p_module ||
					NULL == p_module->name ||
					NULL == p_module->func) {
				p_module = NULL;
			}
		}
	} else {
		(it->cur_module)++;
		p_module = find_next_module(it, match);
		it->cur_module_item = -1;
		it->tcstate.next_module = it->cur_module;
		it->tcstate.next_module_item = -1;
	}
	export_tcstate(it);

	return FCSERR_OK;
}

void print_modules(fcsmt_log_t log,
		struct iterator_info *it)
{
	int i;
	struct module_info *p_module = NULL;

	if (NULL == log || NULL == it) {
		log("print_modules: Wrong inparam\n");
		return;
	}

	log("print_modules:\n");
	for (i = 0; i < it->n_modules; i++) {
		p_module = &(it->module[i]);
		if (NULL == p_module || NULL == p_module->name) {
			log("print_modules: Invalid module setup.\n");
			return;
		}
		log("%s\n", p_module->name);
	}
}

int set_next_module_item(struct iterator_info *it,
			int module_item)
{
	if (NULL == it)
		return -FCSERR_EINVAL;
	it->tcstate.next_module_item = module_item;
	it->tcstate.next_module = it->cur_module;

	return FCSERR_OK;
}

int inc_n_executed(struct iterator_info *it)
{
	if (NULL == it)
		return -FCSERR_EINVAL;
	(it->tcstate.n_executed)++;

	return FCSERR_OK;
}


int inc_n_failed(struct iterator_info *it)
{
	if (NULL == it)
		return -FCSERR_EINVAL;
	(it->tcstate.n_failed)++;

	return FCSERR_OK;
}


int get_n_executed(struct iterator_info *it)
{
	if (NULL == it)
		return 0;

	return it->tcstate.n_executed;
}


int get_n_failed(struct iterator_info *it)
{
	if (NULL == it)
		return 0;

	return it->tcstate.n_failed;
}


int more_modules(struct iterator_info *it)
{
	if (NULL == it)
		return 0;
	return (it->cur_module < it->n_modules);
}

void export_tcstate(struct iterator_info *it)
{
	if (NULL == it)
		return;

	if (more_modules(it)) {
		/* Present the next test case state */
		it->export_tcstate(
			&(it->tcstate));
	} else {
		it->export_tcstate(NULL);
	}
}

