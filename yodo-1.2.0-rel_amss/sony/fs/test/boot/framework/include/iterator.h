/*
 * Copyright (c) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#ifndef ITERATOR_H_
#define ITERATOR_H_

struct iterator_info;

struct iterator_tcstate {
	unsigned int n_failed;
	unsigned int n_executed;
	unsigned int next_module;
	int next_module_item;
};

typedef void (*fcsmt_log_t)(const char *fmt, ...);
typedef int (*fcsmt_func_t)(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match);

struct module_info {
	const char *name;
	fcsmt_func_t func;
};

struct iterator_info {
	unsigned int cur_module;
	int cur_module_item;
	struct iterator_tcstate tcstate;
	void (*export_tcstate)(
			struct iterator_tcstate *tcstate);
	unsigned int n_allocated;
	unsigned int n_modules;
	struct module_info *module;
};

extern int setup_modules(struct iterator_info *it);

int add_module(struct iterator_info *it, const char *name, fcsmt_func_t func);

int setup_iterator(struct iterator_info **it,
			struct iterator_tcstate *state,
			void (*export_tcstate)(
				struct iterator_tcstate *tcstate));

void teardown_iterator(struct iterator_info *it);

int set_next_module_item(struct iterator_info *it,
			int module_item);

int inc_n_executed(struct iterator_info *it);

int inc_n_failed(struct iterator_info *it);

int get_n_executed(struct iterator_info *it);

int get_n_failed(struct iterator_info *it);

void export_tcstate(struct iterator_info *it);

int execute_module(fcsmt_log_t log,
		struct iterator_info *it,
		const char *match);

int more_modules(struct iterator_info *it);

void print_modules(fcsmt_log_t log,
		struct iterator_info *it);

#endif

