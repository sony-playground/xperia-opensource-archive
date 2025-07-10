/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#include "sparse.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "fcserr.h"
#include "fcslog.h"
#include "storage.h"
#include "lz4.h"
#include <errno.h>

#define SPARSE_HEADER_SIZE      (28)
#define CHUNK_HEADER_SIZE       (12)

static int handle_chunk_type_fill(struct storage_ctx *sctx,
		struct chunk_header *chdr,
		struct sparse_header *shdr,
		uint8_t *buf,
		unsigned int *blks_written,
		size_t *index);
static int handle_chunk_type_lz4(struct storage_ctx *sctx,
		struct chunk_header *chdr,
		struct sparse_header *shdr,
		uint8_t *buf,
		unsigned int *blks_written,
		size_t *index);
static int fill_buf(uint32_t fill_val,
		uint8_t *fbuf,
		size_t buf_sz,
		size_t blk_sz);

int write_sparse_image(struct storage_ctx *sctx,
		uint8_t *buf,
		size_t bytes_read)
{
	int res = FCSERR_OK;
	struct sparse_header *shdr;
	struct chunk_header *chdr;
	unsigned int chunk;
	size_t chunk_sz;
	unsigned int blks_written = 0;
	size_t index = 0;
	off_t partsize, offset;

	if (sctx == NULL || buf == NULL ||
			(bytes_read < sizeof(struct sparse_header))) {
		FCS_LOG_ERR("Wrong input values.\n");
		return -FCSERR_EINVAL;
	}
	shdr = (struct sparse_header *)buf;
	if (shdr->file_hdr_sz != sizeof(struct sparse_header)) {
		FCS_LOG_ERR("Sparse header size mismatch\n");
		return -FCSERR_EHDR;
	}
	if (shdr->chunk_hdr_sz != sizeof(struct chunk_header)) {
		FCS_LOG_ERR("Chunk header size mismatch\n");
		return -FCSERR_EHDR;
	}
	if (shdr->blk_sz == 0 || (shdr->blk_sz % 0x200) != 0) {
		FCS_LOG_ERR("Broken block size in sparse header\n");
		return -FCSERR_EHDR;
	}

	/*
	 * Make sure image fits in partition
	 */
	partsize = storage_lseek(sctx, 0, STORAGE_SEEK_END);
	if (partsize < 0) {
		FCS_LOG_ERR("Failed to seek (errno=%d)\n", errno);
		return -FCSERR_EIO;
	}

	if (storage_lseek(sctx, 0, STORAGE_SEEK_SET) < 0) {
		FCS_LOG_ERR("Failed to seek (errno=%d)\n", errno);
		return -FCSERR_EIO;
	}

	if (((ssize_t)shdr->blk_sz * (ssize_t)shdr->total_blks) > partsize) {
		FCS_LOG_ERR("Image too big for partition\n");
		return -FCSERR_EPART;
	}

	index += sizeof(struct sparse_header);
	if (index > bytes_read) {
		FCS_LOG_ERR("Index is out of bounds\n");
		return -FCSERR_EOOB;
	}
	for (chunk = 0; chunk < shdr->total_chunks; chunk++) {
		chdr = (struct chunk_header *)(buf + index);
		index += sizeof(struct chunk_header);
		if (index > bytes_read) {
			FCS_LOG_ERR("Index is out of bounds\n");
			return -FCSERR_EOOB;
		}
		chunk_sz = shdr->blk_sz*chdr->chunk_sz;

		switch (chdr->chunk_type) {
		case CHUNK_TYPE_RAW:
			if (chdr->total_sz !=
					(shdr->chunk_hdr_sz +
					 chunk_sz)) {
				FCS_LOG_ERR("Wrong chunk size\n");
				return -FCSERR_EHDR;
			}
			if (index + chunk_sz > bytes_read) {
				FCS_LOG_ERR("Buffer overflow\n");
				return -FCSERR_EOOB;
			}

			offset = (off_t)blks_written*shdr->blk_sz;
			if (storage_lseek(sctx, offset, STORAGE_SEEK_SET) < 0) {
				FCS_LOG_ERR("Failed to seek (errno=%d)\n",
						errno);
				return -FCSERR_EIO;
			}

			if (storage_write(sctx, buf+index, chunk_sz) < 0) {
				FCS_LOG_ERR("Failed to write (errno=%d)\n",
						errno);
				return -FCSERR_EIO;
			}

			index += chunk_sz;
			blks_written += chdr->chunk_sz;
			break;
		case CHUNK_TYPE_FILL:
			res = handle_chunk_type_fill(sctx,
					chdr,
					shdr,
					buf,
					&blks_written,
					&index);
			if (res < 0)
				FCS_LOG_ERR("Fill record handling failed\n");
			break;
		case CHUNK_TYPE_DONT_CARE:
			if (blks_written > UINT_MAX - chdr->chunk_sz) {
				FCS_LOG_ERR("FAIL: Chunk size is broken");
				return -FCSERR_EHDR;
			}

			blks_written += chdr->chunk_sz;
			break;
		case CHUNK_TYPE_CRC:
			FCS_LOG_ERR("CHUNK_TYPE_CRC Not supported\n");
			return -FCSERR_ENIMP;
		case CHUNK_TYPE_LZ4:
			res = handle_chunk_type_lz4(sctx,
					chdr,
					shdr,
					buf,
					&blks_written,
					&index);
			if (res < 0)
				FCS_LOG_ERR("LZ4 chunk handling failed\n");
			break;
		default:
			FCS_LOG_ERR("Unknown chunk type: %X\n",
				chdr->chunk_type);
			return -FCSERR_EUNK;
		}
	}

	return res;
}

uint8_t *get_sparse_headers_to_offset(ssize_t *hdr_sz, ssize_t block_size,
		ssize_t offset, ssize_t chunk_sz)
{
	uint8_t *buf;
	struct sparse_header *shdr;
	struct chunk_header *chdr;

	if (hdr_sz == NULL || block_size == 0 || chunk_sz == 0) {
		FCS_LOG_ERR("Broken input parameters\n");
		return NULL;
	}

	*hdr_sz = SPARSE_HEADER_SIZE + 2 * CHUNK_HEADER_SIZE;
	buf = malloc(*hdr_sz);
	if (buf == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		*hdr_sz = 0;
		return NULL;
	}

	shdr = (struct sparse_header *)buf;
	/* Add sparse header */
	shdr->magic = SPARSE_HDR_MAGIC;
	shdr->major_version = 1;
	shdr->minor_version = 0;
	shdr->file_hdr_sz = SPARSE_HEADER_SIZE;
	shdr->chunk_hdr_sz = CHUNK_HEADER_SIZE;
	shdr->blk_sz = block_size;
	shdr->total_blks = offset + chunk_sz;
	shdr->total_chunks = 2;
	shdr->image_checksum = 0;

	chdr = (struct chunk_header *)(buf + SPARSE_HEADER_SIZE);
	/* Add DON'T CARE chunk header */
	chdr->chunk_type = CHUNK_TYPE_DONT_CARE;
	chdr->reserved1 = 0;
	chdr->chunk_sz = offset;
	chdr->total_sz = CHUNK_HEADER_SIZE;
	chdr++;
	/* Add the chunk header for the secondary gpt */
	chdr->chunk_type = CHUNK_TYPE_RAW;
	chdr->reserved1 = 0;
	chdr->chunk_sz = chunk_sz;
	chdr->total_sz = CHUNK_HEADER_SIZE + chunk_sz * block_size;

	return buf;
}

void destroy_sparse_headers(uint8_t *hdr)
{
	if (hdr != NULL)
		free(hdr);
}

static int handle_chunk_type_fill(struct storage_ctx *sctx,
		struct chunk_header *chdr,
		struct sparse_header *shdr,
		uint8_t *buf,
		unsigned int *blks_written,
		size_t *index)
{
	int res = FCSERR_OK;
	uint32_t fill_written = 0;
	uint32_t fill_val;
	uint8_t *fbuf = NULL;
	off_t offset;

	if (!sctx || !chdr || !shdr || !buf || !blks_written || !index) {
		FCS_LOG_ERR("NULL buffer(s)\n");
		return -FCSERR_EINVAL;
	}

	if (chdr->total_sz != shdr->chunk_hdr_sz + sizeof(fill_val)) {
		FCS_LOG_ERR("Broken fill record\n");
		return -FCSERR_EINVAL;
	}

	fill_val = *(uint32_t *)(buf + *index);
	fbuf = (uint8_t *)malloc(shdr->blk_sz);
	if (!fbuf) {
		FCS_LOG_ERR("Out of memory\n");
		return -FCSERR_ENOMEM;
	}

	res = fill_buf(fill_val, fbuf, shdr->blk_sz, shdr->blk_sz);
	if (res < 0) {
		FCS_LOG_ERR("Creating fill buffer fail.\n");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	offset = (off_t)(*blks_written)*shdr->blk_sz;
	if (storage_lseek(sctx, offset, STORAGE_SEEK_SET) < 0) {
		FCS_LOG_ERR("Failed to seek (errno=%d)\n", errno);
		res = -FCSERR_EIO;
		goto exit;
	}

	while (chdr->chunk_sz > fill_written) {
		if (storage_write(sctx, fbuf, shdr->blk_sz) < 0) {
			FCS_LOG_ERR("Failed to write (errno=%d)\n", errno);
			res = -FCSERR_EIO;
			goto exit;
		}
		fill_written++;
	}

	*index += sizeof(fill_val);
	*blks_written += chdr->chunk_sz;

exit:
	free(fbuf);

	return res;
}

static int handle_chunk_type_lz4(struct storage_ctx *sctx,
		struct chunk_header *chdr,
		struct sparse_header *shdr,
		uint8_t *buf,
		unsigned int *blks_written,
		size_t *index)
{
	int res = FCSERR_OK;
	int decomp_sz, comp_sz = 0;
	int decomp_res = 0;
	uint8_t *decomp_buf = NULL;
	off_t offset;

	if (!sctx || !chdr || !shdr || !buf || !blks_written || !index) {
		FCS_LOG_ERR("NULL buffer(s)\n");
		return -FCSERR_EINVAL;
	}

	/* In bytes */
	comp_sz = chdr->total_sz - sizeof(struct chunk_header);
	/* In blocks */
	decomp_sz = chdr->chunk_sz;
	decomp_buf = (uint8_t *)malloc(decomp_sz*shdr->blk_sz);
	if (!decomp_buf) {
		FCS_LOG_ERR("Out of memory!\n");
		return -FCSERR_ENOMEM;
	}

	decomp_res = LZ4_decompress_safe((char *)(buf + *index),
			(char *)decomp_buf,
			comp_sz,
			decomp_sz*shdr->blk_sz);
	if (decomp_res < 0) {
		FCS_LOG_ERR("Failed to decompress block: %d\n", decomp_res);
		res = -FCSERR_ELZ4;
		goto exit;
	}

	offset = (off_t)(*blks_written)*shdr->blk_sz;
	if (storage_lseek(sctx, offset, STORAGE_SEEK_SET) < 0) {
		FCS_LOG_ERR("Failed to seek (errno=%d)\n", errno);
		res = -FCSERR_EIO;
		goto exit;
	}

	if (storage_write(sctx, decomp_buf, decomp_sz*shdr->blk_sz) < 0) {
		FCS_LOG_ERR("Failed to write (errno=%d)\n", errno);
		res = -FCSERR_EIO;
		goto exit;
	}

	*blks_written += decomp_sz;
	*index += chdr->total_sz - sizeof(struct chunk_header);

exit:
	free(decomp_buf);

	return res;
}

/*
 * Fills blk_sz bytes of fbuf with value of fill_val.
 */
static int fill_buf(uint32_t fill_val,
		uint8_t *fbuf,
		size_t buf_sz,
		size_t blk_sz)
{
	unsigned int i = 0;

	if (!fbuf) {
		FCS_LOG_ERR("NULL pointer\n");
		return -FCSERR_EINVAL;
	}

	if (buf_sz < blk_sz) {
		FCS_LOG_ERR("Fill buffer too small for block size.\n");
		return -FCSERR_EINVAL;
	}

	if (blk_sz % sizeof(fill_val)) {
		FCS_LOG_ERR("Foobar blk_sz\n");
		return -FCSERR_EINVAL;
	}

	for (i = 0; i < blk_sz; i += sizeof(fill_val))
		memcpy(fbuf+i, &fill_val, sizeof(fill_val));

	return FCSERR_OK;
}
