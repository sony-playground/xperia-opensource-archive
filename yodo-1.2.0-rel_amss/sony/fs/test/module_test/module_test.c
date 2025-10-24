/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "modules.h"
#include "fcserr.h"
#include <stdlib.h>
#include <string.h>

int execute_module(FILE *fd_out, uint8_t *data_p, size_t size)
{
	if (0 == strncmp("fota:", (char *)data_p, 5))
		return execute_module_fota(fd_out, data_p, size);
	if (0 == strncmp("derparser:", (char *)data_p, 10))
		return execute_module_derparser(fd_out, data_p, size);
	if (0 == strncmp("asahi:", (char *)data_p, 6))
		return execute_module_asahi(fd_out, data_p, size);
	fprintf(fd_out, "ERRORunknown testcase:%s", data_p);
	return FCSERR_OK;
}


