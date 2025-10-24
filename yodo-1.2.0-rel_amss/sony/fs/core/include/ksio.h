/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef KS_IO_H_
#define KS_IO_H_

#include <stdint.h>
#include "kstypes.h"

typedef struct ks_io_state_t ks_io_state_t;

/**
 * @brief IO write access function
 * @param[in] handle    Handle to IO object
 * @param[in] data      The data to write
 * @param[in] data_sz   Size of data
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int ks_io_write(
	struct ks_io_handle *handle, uint8_t *data, uint32_t data_sz);

/**
 * @brief IO read access function
 * @param[in]  handle     Handle to IO object
 * @param[out] data       output buffer
 * @param[in/out] data_sz Max size to read.
 *			  Returns size actually read.
 *
 * Set data = NULL and input data_size = 0 will
 * return size of data
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int ks_io_read(
	struct ks_io_handle *handle, uint8_t *data, uint32_t *data_sz);

int ks_io_delete(struct ks_io_handle *handle);

/**
 * @brief Destroy IO handle
 *
 * This function shall be called when IO handle  use is over
 *
 * @param[in] handle   Opaque handle
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int ks_io_destroy(struct ks_io_handle *handle);

/**
 * @brief IO Write function pointer prototype
 *
 * @param[in] data      The data to write
 * @param[in] data_sz   Size of data
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
typedef int(*ks_io_write_cb_t)(ks_io_state_t *state,
				uint8_t *data, uint32_t data_sz);

/**
 * @brief IO read function pointer prototype
 *
 * @param[out] data      Data read
 * @param[out] data_sz   Size of data
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
typedef int(*ks_io_read_cb_t)(ks_io_state_t *state,
				uint8_t *data, uint32_t *data_sz);

/**
 * @brief IO interal destroy function prototype
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
typedef int(*ks_io_destroy_cb_t)(ks_io_state_t *state);

struct ks_io_handle
{
	ks_io_read_cb_t    read;
	ks_io_write_cb_t   write;
	ks_io_destroy_cb_t destroy;
	ks_io_state_t	   *state;
};

#endif
