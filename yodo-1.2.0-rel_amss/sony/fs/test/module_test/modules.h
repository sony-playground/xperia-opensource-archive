/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#ifndef MODULES_H_
#define MODULES_H_

#include <stdlib.h>

extern int execute_module_fota(FILE *fd_out, uint8_t *data_p, size_t size);
extern int execute_module_derparser(FILE *fd_out, uint8_t *data_p, size_t size);
extern int execute_module_asahi(FILE *fd_out, uint8_t *data_p, size_t size);

#endif /* MODULES_H_ */


