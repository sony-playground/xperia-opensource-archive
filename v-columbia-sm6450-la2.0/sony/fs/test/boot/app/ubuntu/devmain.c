/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include "iterator.h"
#include "integration_main.h"
#include "integration_emulator.h"
#include "fcserr.h"
#include "gen_tests.h"

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

/* strlcat based on OpenBSDs strlcat */
size_t strlcat(char *dest, const char *src, size_t size)
{
	char *d = dest;
	const char *s = src;
	size_t n = size;
	size_t dlen;

	/* Find the end of dest and adjust bytes left but don't go past end */
	while (n-- != 0 && *d != '\0')
		d++;
	dlen = d - dest;
	n = size - dlen;

	if (n == 0)
		return(dlen + strnlen(s, size));
	while (*s != '\0') {
		if (n != 1) {
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';

	return(dlen + (s - src));        /* count does not include NUL */
}

char *strnstr(const char *in, const char *str, size_t max_len)
{
	int i;
	size_t str_len;

	/* segfault here if str is not NULL terminated */
	str_len = strnlen(str, max_len);
	if (0 == str_len)
		return (char *)in;

	for (i = 0; i <= (int)(max_len-str_len); i++) {
		if ((in[0] == str[0]) &&
			(0 == strncmp(in, str, str_len)))
			return (char *)in;

		in++;
	}
	return NULL;
}

/* strlcpy based on OpenBSDs strlcpy */
size_t strlcpy(char *dest, const char *src, size_t size)
{
	char *d = dest;
	const char *s = src;
	size_t n = size;

	/* Copy as many bytes as will fit */
	if (n != 0 && --n != 0) {
		do {
			*d = *s;
			if (*d == 0) {
				d++;
				s++;
				break;
			}
			d++;
			s++;
		} while (--n != 0);
	}

	/* Not enough room in dest, add NUL and traverse rest of src */
	if (n == 0) {
		if (size != 0)
			*d = '\0';        /* NUL-terminate dest */
		while (*s++)
			;
	}

	return(s - src - 1);        /* count does not include NUL */
}

static struct integration_hwstate *parse_hwstate(
	struct integration_hwstate *dest,
	const char *state)
{
	int nconv = 0;
	unsigned int startup_flags;
	unsigned int wb_reason;
	unsigned int reset_detect;
	unsigned int usb_vbus_detect;
	unsigned int usb_otg_detect;
	unsigned int pwr_button_pressed_time;
	unsigned int vldwn_button_pressed_time;
	unsigned int vlup_button_pressed_time;

	if (NULL == dest || NULL == state)
		return NULL;

	nconv = sscanf(state, "%u %u %u %u %u %u %u %u\n",
			&startup_flags,
			&wb_reason,
			&reset_detect,
			&usb_vbus_detect,
			&usb_otg_detect,
			&pwr_button_pressed_time,
			&vldwn_button_pressed_time,
			&vlup_button_pressed_time);
	if (8 != nconv)
		return NULL;

	dest->startup_flags = startup_flags;
	dest->wb_reason = wb_reason;
	dest->reset_detect = reset_detect;
	dest->usb_vbus_detect = usb_vbus_detect;
	dest->usb_otg_detect = usb_otg_detect;
	dest->pwr_button_pressed_time = pwr_button_pressed_time;
	dest->vldwn_button_pressed_time = vldwn_button_pressed_time;
	dest->vlup_button_pressed_time = vlup_button_pressed_time;

	return dest;
}

static void main_export_hwstate(
		struct integration_hwstate *state)
{
	printf("\nPARAM HWSTATE <<<<<<\n");
	if (state != NULL) {
		printf("--hwstate=\"%u %u %u %u %u %u %u %u\"",
				state->startup_flags,
				state->wb_reason,
				state->reset_detect,
				state->usb_vbus_detect,
				state->usb_otg_detect,
				state->pwr_button_pressed_time,
				state->vldwn_button_pressed_time,
				state->vlup_button_pressed_time);
	}
	printf("\n>>>>>>> HWSTATE PARAM\n");
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

	if (NULL == dest || NULL == state)
		return NULL;

	nconv = sscanf(state, "%u %u %u %d\n",
			&n_failed,
			&n_executed,
			&next_module,
			&next_module_item);
	if (4 != nconv)
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
	struct integration_hwstate hwstate;
	struct integration_hwstate *hwstate_ptr = NULL;
	struct iterator_tcstate tcstate;
	struct iterator_tcstate *tcstate_ptr = NULL;

	testlog("Hello World of Testers!\n");

	for (i = 1; i < argc; i++) {
		if (0 == strncmp(argv[i], "--match=", 8))
			match = &argv[i][8];
		else if (0 == strncmp(argv[i], "--tcstate=", 10)) {
			if ((strlen(argv[i]) - 10) < 0) {
				testlog("Wrong size of tcstate!\n");
				goto exit;
			}
			tcstate_ptr = parse_tcstate(&tcstate, &argv[i][10]);
			if (NULL == tcstate_ptr) {
				testlog("Wrong format of tcstate!\n");
				goto exit;
			}
		} else if (0 == strncmp(argv[i], "--hwstate=", 10)) {
			if ((strlen(argv[i]) - 10) < 0) {
				testlog("Wrong size of hwstate!\n");
				goto exit;
			}
			hwstate_ptr = parse_hwstate(&hwstate, &argv[i][10]);
			if (NULL == hwstate_ptr) {
				testlog("Wrong format of hwstate!\n");
				goto exit;
			}
		} else if (0 == strncmp(argv[i], "--list", 6)) {
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

	res = integration_emulator_setup(intlog,
				it, hwstate_ptr, main_export_hwstate);
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

