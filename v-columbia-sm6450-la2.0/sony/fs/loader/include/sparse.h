/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCS_SPARSE_H_
#define FCS_SPARSE_H_

#define SPARSE_HDR_MAGIC	0xed26ff3a
#define CHUNK_TYPE_RAW		0xCAC1
#define CHUNK_TYPE_FILL		0xCAC2
#define CHUNK_TYPE_DONT_CARE	0xCAC3
#define CHUNK_TYPE_CRC		0xCAC4
#define CHUNK_TYPE_LZ4		0xCAC5

#include <stdint.h>
#include <stdbool.h>
#include "storage.h"

int write_sparse_image(struct storage_ctx *sctx,
		uint8_t *buf,
		size_t bytes_read);

/*
 * Creates a sparse header with chunk headers that will start/point at
 * given offset.
 * This function will allocate memory needed. destroy_sparse_headers should
 * be called afterwards for cleanup.
 *
 * returns pointer to buffer containing the sparse headers
 * hdr_sz: will contain the size of the buffer that is returned by function
 * block_size: Must fultill blocksize % 4096 == 0.
 * chunk_sz: Number of data blocks of size block_size of the data.
 */
uint8_t *get_sparse_headers_to_offset(ssize_t *hdr_sz, ssize_t block_size,
		ssize_t offset, ssize_t chunk_sz);
void destroy_sparse_headers(uint8_t *hdr);

struct sparse_header {
	/* 0xed26ff3a */
	uint32_t magic;
	/* (0x1) - reject images with higher major versions */
	uint16_t major_version;
	/* (0x0) - allow images with higer minor versions */
	uint16_t minor_version;
	/* 28 bytes for first revision of the file format */
	uint16_t file_hdr_sz;
	/* 12 bytes for first revision of the file format */
	uint16_t chunk_hdr_sz;
	/* block size in bytes, must be a multiple of 4 (4096) */
	uint32_t blk_sz;
	/* total blocks in the non-sparse output image */
	uint32_t total_blks;
	/* total chunks in the sparse input image */
	uint32_t total_chunks;
	/* CRC32 checksum of the original data, counting "don't care" */
	uint32_t image_checksum;
	/* as 0. Standard 802.3 polynomial, use a Public Domain */
	/* table implementation */
};

struct chunk_header {
	/* 0xCAC1 -> raw; 0xCAC2 -> fill; 0xCAC3 -> don't care */
	uint16_t chunk_type;
	uint16_t reserved1;
	/* in blocks in output image */
	uint32_t chunk_sz;
	/* in bytes of chunk input file including chunk header and data */
	uint32_t total_sz;
};

#endif
