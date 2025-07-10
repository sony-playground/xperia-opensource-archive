/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include "iterator.h"
#include "fcserr.h"
#include "gen_tests.h"
#include "integration_emulator.h"

void fcslog(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);

	/* print to stdout */
	vprintf(fmt, ap);

	va_end(ap);
}

void testlog(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);

	/* print to stdout */
	printf("\nTEST <<<<<<\n");
	vprintf(fmt, ap);
	printf(">>>>>>> TEST\n\n");

	va_end(ap);
}

void intlog(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);

	/* print to stdout */
	printf("\nINTEGRATION <<<<<<\n");
	vprintf(fmt, ap);
	printf(">>>>>>> INTEGRATION\n\n");

	va_end(ap);
}

static struct iterator_tcstate *parse_tcstate(
	struct iterator_tcstate *dest,
	const char *state)
{
	int nconv = 0;
	unsigned int n_failed;
	unsigned int n_executed;
	unsigned int next_module;
	int next_module_item;

	if (dest == NULL || state == NULL)
		return NULL;

	nconv = sscanf(state, "%u %u %u %d\n",
			&n_failed,
			&n_executed,
			&next_module,
			&next_module_item);
	if (nconv != 4)
		return NULL;

	dest->n_failed = n_failed;
	dest->n_executed = n_executed;
	dest->next_module = next_module;
	dest->next_module_item = next_module_item;

	return dest;
}

void main_export_tcstate(
		struct iterator_tcstate *tcstate)
{
	printf("\nPARAM TCSTATE <<<<<<\n");
	if (tcstate != NULL) {
		printf("--tcstate=\"%u %u %u %d\"",
				tcstate->n_failed,
				tcstate->n_executed,
				tcstate->next_module,
				tcstate->next_module_item);
	}
	printf("\n>>>>>>> TCSTATE PARAM\n");
}

int main(int argc, char *argv[])
{
	int res = FCSERR_OK;
	int i;
	bool list_testcases = false;
	struct iterator_info *it = NULL;
	const char *match = "";
	struct iterator_tcstate tcstate;
	struct iterator_tcstate *tcstate_ptr = NULL;

	testlog("Hello World of Testers!\n");

	for (i = 1; i < argc; i++) {
		if (strncmp(argv[i], "--match=", 8) == 0)
			match = &argv[i][8];
		else if (strncmp(argv[i], "--tcstate=", 10) == 0) {
			if ((strlen(argv[i]) - 10) < 0) {
				testlog("Wrong size of tcstate!\n");
				goto exit;
			}
			tcstate_ptr = parse_tcstate(&tcstate, &argv[i][10]);
			if (tcstate_ptr == NULL) {
				testlog("Wrong format of tcstate!\n");
				goto exit;
			}
		} else if (strncmp(argv[i], "--list", 6) == 0) {
			list_testcases = true;
		} else {
			testlog("Unknown switch!\n");
			goto exit;
		}
	}

	res = setup_iterator(&it, tcstate_ptr, main_export_tcstate);
	if (res != FCSERR_OK) {
		testlog("Failed to create test iterator!\n");
		goto exit;
	}
	res = setup_modules(it);
	if (res != FCSERR_OK) {
		testlog("Failed to setup_modules!\n");
		goto exit;
	}

	if (list_testcases) {
		print_modules(fcslog, it);
		goto exit;
	}

	res = integration_emulator_setup(intlog, it);
	if (res != FCSERR_OK) {
		testlog("Failed to setup integration!\n");
		goto exit;
	}

	res = execute_module(testlog,
		it,
		match);
	if (res != FCSERR_OK) {
		testlog("Function execute_module failed!\n");
		goto exit;
	}

	if (!more_modules(it))
		testlog("execute_module done! n_failed:%d, n_executed:%d\n",
			get_n_failed(it), get_n_executed(it));

exit:
	integration_emulator_teardown();
	teardown_iterator(it);
	return 0;
}

