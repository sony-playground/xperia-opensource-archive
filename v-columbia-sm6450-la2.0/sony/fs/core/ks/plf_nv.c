/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */


#include <stdint.h>
#include <stdlib.h>
#include "plf_nv.h"
#include "fcserr.h"

typedef struct plf_nv_t
{
	plf_nv_read_cb_t  read;
	plf_nv_write_cb_t write;
} plf_rpmb_t;


int plf_nv_write(plf_nv_t * const handle, const uint8_t partition,
			const uint8_t * const data, const uint32_t data_sz){
	return handle->write(partition, data, data_sz);
}

int plf_nv_read(plf_nv_t * const handle, const uint8_t partition,
		uint8_t **data, uint32_t *data_sz){
	return handle->read(partition, data, data_sz);
}


int plf_nv_create(plf_nv_t **handle,
			plf_nv_write_cb_t write_cb,
			plf_nv_read_cb_t read_cb)
{
	if (handle == NULL || write_cb == NULL || read_cb == NULL)
		return -FCSERR_EINVAL;

	*handle = (plf_nv_t *)malloc(sizeof(plf_nv_t));
	if (*handle == NULL)
		return -FCSERR_ENOMEM;

	(*handle)->read = read_cb;
	(*handle)->write = write_cb;

	return FCSERR_OK;
}


void plf_nv_destroy(plf_nv_t * const handle);


