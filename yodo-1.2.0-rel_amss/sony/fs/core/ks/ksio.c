/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#include <stdlib.h>
#include "ksio.h"

int ks_io_write(
	struct ks_io_handle *handle, uint8_t *data, uint32_t data_sz)
{
	return handle->write(handle->state, data, data_sz);
}

int ks_io_read(
	struct ks_io_handle *handle, uint8_t *data, uint32_t *data_sz)
{
	return handle->read(handle->state, data, data_sz);
}

int ks_io_delete(struct ks_io_handle *handle)
{
	return handle->destroy(handle->state);
}
