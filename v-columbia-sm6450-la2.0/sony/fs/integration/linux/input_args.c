/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "input_args.h"

#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <stdint.h>

#include <linux/limits.h>

#include "fcserr.h"

/*
 * Definitions of input arg flags
 */
#define ARGS_DEBUG 1

/*
 * g - USB gadget device path
 * s - Flash device path
 * l - Log file path
 * d - Debug, do not reboot when disconnect USB cable
 */
#define ARGS_STR "g::s::l::p::d::"

struct input_args_lilo {
	char gadget_path[PATH_MAX + 1];
	char flash_name[PATH_MAX + 1];
	char log_path[PATH_MAX + 1];
	size_t trbuf_size;
	uint32_t flags;
};

/*
 * Static container of input variables
 */
static struct input_args_lilo input_args = {
	{0},
	{0},
	{0},
	1024,
	0
};

static struct option lopts[] = {
	{"gadget-dev", required_argument, NULL, 'g'},
	{"flash-dev", required_argument, NULL, 's'},
	{"log-path", optional_argument, NULL, 'l'},
	{"trbuf-size", optional_argument, NULL, 'p'},
	{"debug", optional_argument, NULL, 'd'},
	{0, 0, NULL, 0},
};

char *input_args_get_gadget(void)
{
	return input_args.gadget_path;
}

char *input_args_get_flash(void)
{
	return input_args.flash_name;
}

char *input_args_get_log(void)
{
	return input_args.log_path;
}

int input_args_get_debug(void)
{
	return (input_args.flags & ARGS_DEBUG);
}

size_t input_args_get_trbuf_size(void)
{
	return input_args.trbuf_size;
}

int input_args_set(int argc, char **argv)
{
	int opt;
	int nopt;

	/* Standard values if not given as parameter */
	strlcpy(input_args.gadget_path, "/dev/fs", PATH_MAX);
	strlcpy(input_args.flash_name, "emmc", PATH_MAX);

	while ((opt = getopt_long(argc, argv, ARGS_STR, lopts, &nopt)) != -1) {
		switch (opt) {
		case 'g':
			strlcpy(input_args.gadget_path, optarg, PATH_MAX);
			break;
		case 's':
			strlcpy(input_args.flash_name, optarg, PATH_MAX);
			break;
		case 'l':
			strlcpy(input_args.log_path, optarg, PATH_MAX);
			break;
		case 'p':
			input_args.trbuf_size = atoi(optarg);
			break;
		case 'd':
			input_args.flags |= ARGS_DEBUG;
			break;
		default:
			return -FCSERR_EINVAL;
		}
	}
	return FCSERR_OK;
}
