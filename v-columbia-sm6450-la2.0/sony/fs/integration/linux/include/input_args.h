/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCS_INPUT_ARGS_H_
#define FCS_INPUT_ARGS_H_

#include <stddef.h>

/*
 * Get USB gadget path
 */
char *input_args_get_gadget(void);

/*
 * Get flash storage name
 */
char *input_args_get_flash(void);

/*
 * Get log file path. A NULL terminated string indicates this has not been set
 * and stdout is used.
 */
char *input_args_get_log(void);

/*
 * Get debug flag. Non zero indicates debug is on.
 */
int input_args_get_debug(void);

/*
 * Get transfer buffer size
 */
size_t input_args_get_trbuf_size(void);

/*
 * Set and parse input arguments
 */
int input_args_set(int argc, char **argv);

#endif
