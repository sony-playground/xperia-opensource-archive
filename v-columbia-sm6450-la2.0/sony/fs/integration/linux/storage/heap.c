/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "storage.h"
#include "storage_int.h"
#include "fcslist.h"
#include "fcslog.h"
#include "fcserr.h"

#include <string.h>
#include <stdlib.h>

#define MIN(x, y) ((x) < (y)?(x):(y))
#define MIN_BUF_SIZE (100*1024*1024L)

struct storage_heap_ctx {
	char *name;
	void *buf;
	uint32_t buf_size;
	uint32_t len;
	uint32_t pos;
};

struct storage_heap_entry {
	struct storage_heap_ctx ctx;
	struct list_entry list;
};

static LIST(storage_heap_list);

struct storage_ctx *storage_heap_open(const char *dev, const char *name)
{
	struct storage_heap_entry *ent;
	struct storage_ctx *sctx;

	FCS_LOG_INF("open %s\n", name);

	if (!dev || !name) {
		FCS_LOG_INF("invalid input\n");
		return NULL;
	}

	if (strncmp(dev, STORAGE_HEAP_NAME, strlen(STORAGE_HEAP_NAME))) {
		FCS_LOG_INF("invalid device\n");
		return NULL;
	}

	sctx = calloc(1, sizeof(struct storage_ctx));
	if (!sctx) {
		FCS_LOG_ERR("out of memory\n");
		return NULL;
	}
	sctx->desc = *(storage_get_desc(STORAGE_HEAP_NAME));

	if (!list_empty(&storage_heap_list)) {
		LIST_FOR_EACH_DATA(&storage_heap_list, ent, list) {
			if (strncmp(ent->ctx.name, name,
				    strlen(ent->ctx.name) + 1) == 0) {
				ent->ctx.pos = 0;
				sctx->ictx = &ent->ctx;
				return sctx;
			}
		}
	}

	ent = calloc(1, sizeof(struct storage_heap_entry));
	if (!ent) {
		FCS_LOG_ERR("could not allocate memory\n");
		goto err;
	}

	if (storage_set_name(sctx, name)) {
		FCS_LOG_ERR("could not set name\n");
		goto err;
	}

	ent->ctx.name = malloc(strlen(name) + 1);
	if (ent->ctx.name == NULL) {
		FCS_LOG_ERR("could not allocate memory\n");
		goto err;
	}
	memcpy(ent->ctx.name, name, strlen(name) + 1);

	ent->ctx.buf = malloc(MIN_BUF_SIZE);
	if (!ent->ctx.buf) {
		FCS_LOG_ERR("could not allocate memory\n");
		goto err;
	}
	ent->ctx.buf_size = MIN_BUF_SIZE;

	list_add_tail(&storage_heap_list, &ent->list);

	sctx->ictx = &ent->ctx;
	return sctx;

err:
	if (ent) {
		free(ent->ctx.buf);
		free(ent->ctx.name);
	}
	free(ent);
	free(sctx);
	return NULL;
}

ssize_t storage_heap_read(struct storage_ctx *ctx, void *buf, ssize_t count)
{
	struct storage_heap_ctx *hctx;
	size_t len;

	if (!ctx || !ctx->ictx) {
		FCS_LOG_ERR("invalid ctx\n");
		return -FCSERR_EINVAL;
	}

	if (count == 0)
		return 0;

	if (!buf) {
		FCS_LOG_ERR("invalid buffer\n");
		return -FCSERR_ENOBUFS;
	}

	hctx = (struct storage_heap_ctx *)ctx->ictx;
	if (!hctx->buf)
		return 0;

	len = MIN((uint32_t)count, hctx->len - hctx->pos);
	memcpy(buf, hctx->buf, len);
	hctx->pos += len;

	return len;
}

ssize_t storage_heap_write(
	struct storage_ctx *ctx, const void *buf, ssize_t count)
{
	struct storage_heap_ctx *hctx;
	uint8_t *tmpp;

	if (!ctx || !ctx->ictx) {
		FCS_LOG_ERR("invalid ctx\n");
		return -FCSERR_EINVAL;
	}

	if (count == 0)
		return 0;

	if (!buf) {
		FCS_LOG_ERR("invalid buffer\n");
		return -FCSERR_ENOBUFS;
	}

	hctx = (struct storage_heap_ctx *)ctx->ictx;
	if (!hctx->buf) {
		hctx->buf = malloc(count + hctx->pos);
		hctx->len = count + hctx->pos;
		hctx->buf_size = hctx->len;
	} else if (count + hctx->pos > hctx->buf_size) {
		hctx->buf = realloc(hctx->buf, count + hctx->pos);
		hctx->len = count + hctx->pos;
		hctx->buf_size = hctx->len;
	} else if (count + hctx->pos > hctx->len) {
		hctx->len = count + hctx->pos;
	}

	if (!hctx->buf) {
		FCS_LOG_ERR("out of memory\n");
		return -FCSERR_ENOMEM;
	}

	tmpp = hctx->buf;
	tmpp += hctx->pos;
	memcpy(tmpp, buf, count);
	hctx->pos += count;

	return count;
}

int storage_heap_close(struct storage_ctx *ctx)
{
	(void)(ctx); /* Unused parameter */

	return FCSERR_OK;
}

off_t storage_heap_lseek(struct storage_ctx *ctx, off_t offset, int whence)
{
	struct storage_heap_ctx *hctx;

	if (!ctx || !ctx->ictx) {
		FCS_LOG_ERR("invalid ctx\n");
		return -FCSERR_EINVAL;
	}

	hctx = (struct storage_heap_ctx *)ctx->ictx;

	switch (whence) {
	case STORAGE_SEEK_SET:
		hctx->pos = offset;
		break;
	case STORAGE_SEEK_CUR:
		hctx->pos = hctx->pos + offset;
		break;
	case STORAGE_SEEK_END:
		hctx->pos = hctx->len + offset;
		break;
	default:
		FCS_LOG_ERR("invalid whence\n");
		return -FCSERR_EINVAL;
	}

	return hctx->pos;
}

/*
 * We actually do not free memory. Use this storage type with care
 */
int storage_heap_unlink(const char *dev, const char *path)
{
	struct storage_heap_entry *ent;

	if (!dev || !path) {
		FCS_LOG_INF("invalid input\n");
		return -FCSERR_ENOENT;
	}

	if (strncmp(dev, STORAGE_HEAP_NAME, strlen(STORAGE_HEAP_NAME))) {
		FCS_LOG_INF("invalid device\n");
		return -FCSERR_ENOENT;
	}

	if (!list_empty(&storage_heap_list))
		LIST_FOR_EACH_DATA(&storage_heap_list, ent, list)
			if (strncmp(ent->ctx.name, path,
				    strlen(ent->ctx.name) + 1) == 0) {

				ent->ctx.pos = 0;
				ent->ctx.len = 0;

				return FCSERR_OK;
			}

	FCS_LOG_WRN("could not find %s\n", path);
	return -FCSERR_EINVAL;
}
