/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */


#include <stdint.h>
#include <stdlib.h>
#include "ksnvio.h"
#include "ksio.h"
#include <fcslog.h>
#include <fcserr.h>

/* Destructor */
int nv_destroy_cb(ks_io_state_t * const handle)
{
	/* Delete the internal (partition) state handle */
	free(handle);
	return FCSERR_OK;

}

int nv_open(struct ks_io_handle **handle, uint32_t partition)
{
	struct nvio_state *the_state;

	if (handle == NULL)
		return -FCSERR_EINVAL;

	*handle = (struct ks_io_handle *)malloc(sizeof(struct ks_io_handle));
	if (*handle == NULL)
		return -FCSERR_ENOMEM;

	(*handle)->read = plf_nv_read_cb;
	(*handle)->write = plf_nv_write_cb;
	(*handle)->destroy = nv_destroy_cb;
	the_state = (struct nvio_state *)malloc(sizeof(struct nvio_state));

	if (the_state == NULL)
	{
		free(*handle);
		*handle = NULL;
		FCS_LOG_ERR("malloc failed %d\n");
		return -FCSERR_ENOMEM;
	}

	the_state->partition = partition;
	(*handle)->state = (ks_io_state_t *)the_state;
	return FCSERR_OK;
}
