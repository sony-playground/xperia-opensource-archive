/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef MODULE_TEST_H_
#define MODULE_TEST_H_

#include <stdint.h>

/*
 *   Exported module test framework.
 */

/**
 *  Execute module test use case.
 *
 *  @param [in]  fd_out            File handle for output.
 *  @param [in]  data_p            Module test case name string (null term).
 *  @param [in]  size              Max length of data_p buffer.
 *
 *  @returns int
 */
int execute_module(FILE *fd_out, uint8_t *data_p, size_t size);

#endif /* MODULE_TEST_H_ */
