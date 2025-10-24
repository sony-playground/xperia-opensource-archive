/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "storage.h"
#include "fcserr.h"
#include "sparse.h"
#include "fcslog.h"
#include "write_image.h"
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>

int write_image(struct storage_ctx *sctx,
		uint8_t *buf, uint32_t offset,
		size_t bytes_read)
{
	int res = FCSERR_OK;
	ssize_t bytes_written;
	struct sparse_header *sparse_hdr;

	if (sctx == NULL || buf == NULL || bytes_read == 0) {
		FCS_LOG_ERR("Input values\n");
		return -FCSERR_EINVAL;
	}

	sparse_hdr = (struct sparse_header *)buf;
	if (bytes_read > 4 && sparse_hdr->magic == SPARSE_HDR_MAGIC) {
		res = write_sparse_image(sctx, buf, bytes_read);
		if (res < 0) {
			FCS_LOG_ERR("Failed to write sparse image\n");
			return -FCSERR_EINVAL;
		}
	} else {
		/*
		 * Set pointer to start of partition.
		 *
		 * This is needed because we do not close the partition until
		 * we open another partition or are done with all flashing.
		 * This means that if we for some reason would flash a
		 * non-sparse image twice in a row the file pointer would
		 * be pointing in the wrong place.
		 */
		if (storage_lseek(sctx, offset, STORAGE_SEEK_SET) < 0) {
			FCS_LOG_ERR("Failed to seek (errno=%d)\n", errno);
			return -FCSERR_EIO;
		}

		bytes_written = storage_write(sctx, buf, bytes_read);
		if (bytes_written < 0) {
			FCS_LOG_ERR("Write fail (errno=%d)\n", errno);
			return -FCSERR_EIO;
		}
	}

	return res;
}
