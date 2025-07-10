/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

/*
 * Protocol help functions
 */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>

#include "sec_data_utils.h"
#include "protocol_util.h"
#include "fcslog.h"
#include "fcserr.h"
#include "fcsenv.h"
#include "fcs_defines.h"
#include "ta_interface.h"
#include "hwconf.h"
#include "fcsenv_def.h"
#include "fcs_fastboot_partitions.h"
#include "rooting_status.h"
#include <eroot.h>
#include <core.h>
#include "linux_util.h"
#include <cryp_util.h>
#include <digest.h>

#define PU_DIGEST_CHUNK (4 * 1024 * 1024)
#define PU_DIGEST_TIMEOUT 1

#define PU_IDLE    0
#define PU_RUNNING 1

/* Constants for parsing S1_Roots */
#define CN_LEN_IDX 43
#define CN_IDX 44

#define FCSERR_EONE     (1)    /* for functions typically returning ssize_t */

/* mutex and cond used to signal when a read and hash is done */
static pthread_mutex_t pu_hash_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t pu_read_done = PTHREAD_COND_INITIALIZER;
static pthread_cond_t pu_hash_done = PTHREAD_COND_INITIALIZER;

struct digest_context {
	uint8_t *buf;
	size_t len;
	int hstate;
	int res;
	struct digest *dgst;
};

static int init_hwconfig(hwconfig_t *handle_p)
{
	int res = FCSERR_OK;
	size_t devid_len = 0;
	uint8_t *devid = NULL;
	struct embed_rootcert_item *embed_rootcert_list = NULL;
	size_t embed_rootcert_list_count = 0;

	devid_len = core_get_dieid_len();

	devid = malloc(devid_len);
	if (devid == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		res = -FCSERR_ENOMEM;
		goto endfunction_init_hwconfig;
	}

	res = core_get_dieid(devid, devid_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get dev id from env: (%d)\n", res);
		goto endfunction_init_hwconfig;
	}

	res = get_embedded_roots(
		&embed_rootcert_list, &embed_rootcert_list_count);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get embedded_roots from env: (%d)\n",
			res);
		goto endfunction_init_hwconfig;
	}

	res = setup_hwconfig(devid, devid_len,
			embed_rootcert_list, embed_rootcert_list_count,
			handle_p);

endfunction_init_hwconfig:
	free_embedded_roots(&embed_rootcert_list);
	free(devid);
	return res;
}

/*
 * Get data from miscta unit <ta_unit>. <buf> will be
 * null terminated and populated with data from <ta_unit> up
 * to max <buf_size>
 */
int get_miscta_unit_data(int ta_unit, char *buf, int buf_size)
{
	int res = FCSERR_OK;
	uint8_t *ta_buf = NULL;
	int ta_buf_size = 0;

	if (!buf || (buf_size < 1)) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	/* Get size of unit */
	res = get_ta_unit_size(TA_MISC_PART, ta_unit, &ta_buf_size);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Invalid unit (%d), error=%d\n", TA_MSN_UNIT, res);
		return res;
	}

	ta_buf = malloc(ta_buf_size);

	if (ta_buf == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		return -FCSERR_ENOMEM;
	}

	res = read_ta(TA_MISC_PART, ta_unit, ta_buf, ta_buf_size);
	if (res != FCSERR_OK) {
		FCS_LOG_INF("Unable to read TA unit %d, error=%d\n",
			ta_unit, res);
		/* If unit is not found return an empty string and FCSERR_OK */
		buf[0] = '\0';
		free(ta_buf);
		return FCSERR_OK;
	}

	memcpy(buf, ta_buf, MIN(buf_size - 1, ta_buf_size));
	buf[MIN(buf_size - 1, ta_buf_size)] = 0;

	free(ta_buf);
	return res;
}

/*
 * Read phone id from HWConfig and return the result in <buf> which has
 * size <buf_size>. Result is converted to ASCII and the resulting string is
 * null terminated. Format: 0000:<imei_1>[,0000:<imei_2>]
 * Returns a FCSERR_x code.
 */
int get_phone_id(char *buf, int buf_size)
{
	int res = FCSERR_OK;
	unsigned int i, j;
	uint8_t imei_count = 0;
	size_t imei_length = 0;
	char *parse_buff = NULL;
	char ascii_buff[32];
	hwconfig_t hwconf = NULL;

	if (buf == NULL) {
		FCS_LOG_ERR("Invalid argument, buf is NULL\n");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	buf[0] = '\0';

	res = init_hwconfig(&hwconf);
	if (res) {
		FCS_LOG_ERR("hwconfig init failed (%d)\n", res);
		goto exit;
	}

	res = get_imei_count(&imei_count, hwconf);
	if (res) {
		FCS_LOG_ERR("get_imei_count failed (%d)\n", res);
		goto exit;
	}

	/*
	 * "," + "0000:" => 6 bytes
	 * Hexstring => 2 * MAX_PHONEID_SIZE
	 */
	if (imei_count * (6 + 2 * MAX_PHONEID_SIZE) + 1 > buf_size) {
		FCS_LOG_ERR("Buffer to small\n");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	for (i = 0; i < imei_count; i++) {

		parse_buff = calloc(1, MAX_PHONEID_SIZE + 1);
		if (!parse_buff) {
			FCS_LOG_ERR("Unable to allocate buffer for IMEI id\n");
			res = -FCSERR_ENOMEM;
			goto exit;
		}

		res = get_imei(i, (uint8_t *)parse_buff, MAX_PHONEID_SIZE + 1,
				&imei_length, hwconf);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Unable to parse phone id, error=%d\n",
				res);
			goto exit;
		}

		strlcat(buf, "0000:", buf_size);

		/*
		 * Reads 1 byte at a time and converts it to 2 ascii chars and
		 * stores it in same buf. Skip last byte of imei.
		 */
		for (j = 0; j < imei_length - 1; j++)
			snprintf(&ascii_buff[j * 2], 3, "%02X",
				*(parse_buff+j));

		ascii_buff[j * 2 + 1] = '\0';
		strlcat(buf, ascii_buff, buf_size);

		/* If more IMEI records exists */
		if ((i + 1) < imei_count)
			strlcat(buf, ",", buf_size);

		free(parse_buff);
		parse_buff = NULL;
	}

exit:
	if (hwconf)
		teardown_hwconfig(hwconf);
	if (parse_buff)
		free(parse_buff);

	return res;
}

int get_s1_root(char *buf, size_t buf_size)
{
	int res = FCSERR_OK;
	int i, index = 0;

	struct embed_rootcert_item *eroot_list = NULL;
	size_t eroot_count = 0;

	if (buf == NULL || buf_size == 0) {
		FCS_LOG_ERR("Invalid input parameters\n");
		return -FCSERR_EINVAL;
	}

	res = get_embedded_roots(
		&eroot_list, &eroot_count);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get embedded_roots from env: (%d)\n",
			res);
		goto exit;
	}

	for (i = 0; i < (int)eroot_count; i++) {
		/* Locate the S1_Roots */
		if (eroot_list[i].cert_domain_flags & CERT_DOMAIN_S1) {
			/* Make sure there's room for a S1_ROOT CN */
			if (index + eroot_list[i].rootcerts[CN_LEN_IDX] >=
					(int)buf_size) {
				FCS_LOG_ERR("Buffer too small\n");
				res = -FCSERR_EINVAL;
				goto exit;
			}
			if (index != 0) {
				/* If more than one root separate them with , */
				buf[index++] = ',';
			}
			memcpy(&buf[index],
					&eroot_list[i].rootcerts[CN_IDX],
					eroot_list[i].rootcerts[CN_LEN_IDX]);

			index += eroot_list[i].rootcerts[CN_LEN_IDX];
			buf[index] = '\0';
		}
	}

	if (index == 0) {
		FCS_LOG_ERR("No S1-root found\n");
		res = -FCSERR_ESTATE;
		goto exit;
	}

exit:
	if (eroot_list != NULL)
		free_embedded_roots(&eroot_list);

	return res;
}

int get_x_conf_root_hash(uint8_t *buf, size_t buf_len, int *nroots)
{
	int res = FCSERR_OK;
	uint32_t i;
	uint8_t hash[DIGEST_SHA1_HASH_SIZE];

	struct embed_rootcert_item *eroot_list = NULL;
	size_t eroot_count = 0;

	uint8_t *bt = buf;

	if (buf == NULL || buf_len == 0 || nroots == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		return -FCSERR_EINVAL;
	}
	*nroots = 0;

	res = get_embedded_roots(&eroot_list, &eroot_count);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get embedded_roots from env: (%d)\n",
			res);
		goto exit;
	}

	for (i = 0; i < eroot_count; i++) {
		/* Locate the X config root */
		if (eroot_list[i].cert_domain_flags & CERT_DOMAIN_CONFIG) {
			res = cryp_get_pk_hash(
				eroot_list[i].rootcerts,
				eroot_list[i].rootcerts_length,
				hash, sizeof(hash));
			if (res != FCSERR_OK) {
				FCS_LOG_ERR("Get PK hash failed\n");
				goto exit;
			}
			/* copy the first 2 bytes if there is enough space */
			if ((bt - buf + 2) > (long)buf_len) {
				FCS_LOG_ERR("Buffer is too small\n");
				res = -FCSERR_EINVAL;
				goto exit;
			}

			(*nroots)++;
			memcpy(bt, hash, 2);
			bt += 2;
		}
	}

	if (*nroots == 0) {
		FCS_LOG_ERR("No root found\n");
		res = -FCSERR_ESTATE;
		goto exit;
	}

exit:
	free_embedded_roots(&eroot_list);
	return res;
}

/*
 * Populates <buf> with ASCII coded rooting status.
 * Returns a FCSERR_x code.
 */
int get_rooting_status_string(char *buf, unsigned int buf_size)
{
	int res;
	uint8_t rooting_status;
	uint32_t is_xcs_rot;
	uint8_t rck_h[RCK_H_LENGTH];

	if (!buf) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	/* Get rooting status from sec data */
	res = sec_data_get_rooting_status(&rooting_status);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get rooting status: (%d)\n", res);
		return res;
	}

	/* Rooting is not allowed if the keystore is XCS */
	res = sec_data_get_xcs_rot(&is_xcs_rot);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get xcs rot\n");
		return res;
	}

	if (is_xcs_rot) {
		FCS_LOG_INF("Unlock not allowed with XCS keystore\n");
		rooting_status = BOOT_NOT_UNLOCKABLE;
	} else if (rooting_status != BOOT_UNLOCKED) {
		/* Recalculate rooting status based on the simlock */
		res = get_simlock_unlock_data(&rooting_status, rck_h);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to get rooting status: (%d)\n",
					res);
			rooting_status = BOOT_NOT_UNLOCKABLE;
			res = FCSERR_OK;
		}
	}


	switch (rooting_status) {
	case BOOT_NOT_UNLOCKABLE:
		snprintf(buf, MIN(buf_size, sizeof("NOT_ROOTABLE")),
				"NOT_ROOTABLE");
		break;
	case BOOT_UNLOCKABLE:
		snprintf(buf, MIN(buf_size, sizeof("ROOTABLE")),
				"ROOTABLE");
		break;
	case BOOT_UNLOCKED:
		snprintf(buf, MIN(buf_size, sizeof("ROOTED")),
				"ROOTED");
		break;
	case BOOT_UNLOCKABLE_SIMLOCK_LOCKED:
		snprintf(buf, MIN(buf_size, sizeof("SL_ROOTABLE")),
				"SL_ROOTABLE");
		break;
	case BOOT_UNLOCKABLE_SIMLOCK_UNLOCKED:
		snprintf(buf, MIN(buf_size, sizeof("SL_UNL_ROOTABLE")),
				"SL_UNL_ROOTABLE");
		break;
	default:
		snprintf(buf, MIN(buf_size, sizeof("ERROR")), "ERROR");
		break;
	}

	return res;

}

int fastboot_get_secure_state(char *buf, size_t buf_size)
{
	int res = FCSERR_OK;
	uint8_t rooting_status;

	if (!buf) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	/* Get rooting status */
	res = sec_data_get_rooting_status(&rooting_status);
	if (res) {
		FCS_LOG_ERR("Failed to get rooting status: (%d)\n", res);
		return res;
	}

	if (rooting_status == BOOT_UNLOCKED)
		snprintf(buf, MIN(buf_size, sizeof("no")), "no");
	else
		snprintf(buf, MIN(buf_size, sizeof("yes")), "yes");

	return FCSERR_OK;
}

int bootloader_unlock_allowed(uint8_t *allow_unlock, uint8_t *rooting_status)
{
	int res = FCSERR_OK;
	uint8_t ggl_allow_unlock;
	uint8_t rck_h[RCK_H_LENGTH];
	uint32_t is_xcs_rot;

	if (!allow_unlock || !rooting_status) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	*allow_unlock = 0;
	*rooting_status = BOOT_NOT_UNLOCKABLE;

	/* Get rooting status from sec data */
	res = sec_data_get_rooting_status(rooting_status);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get rooting status: (%d)\n", res);
		return res;
	}

	/* Rooting is not allowed if the keystore is XCS */
	res = sec_data_get_xcs_rot(&is_xcs_rot);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get xcs rot\n");
		return res;
	}

	if (is_xcs_rot) {
		FCS_LOG_INF("Unlock not allowed with XCS keystore\n");
		return FCSERR_OK;
	}

	if (*rooting_status == BOOT_UNLOCKED) {
		FCS_LOG_INF("Bootloader already unlocked\n");
		return FCSERR_OK;
	}

	/* Recalculate rooting status based on the simlock */
	res = get_simlock_unlock_data(rooting_status, rck_h);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get rooting status: (%d)\n", res);
		return res;
	}

	res = google_allow_unlock(&ggl_allow_unlock);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get bootloader unlock allowed state\n");
		return res;
	}

	if (((*rooting_status != BOOT_UNLOCKABLE) &&
	    (*rooting_status != BOOT_UNLOCKABLE_SIMLOCK_UNLOCKED)) ||
	    !ggl_allow_unlock)
		return res;

	*allow_unlock = 1;

	return res;
}

int get_simlock_rck_h(uint8_t *rck_h)
{
	int ret;
	uint8_t unlock_status;

	ret = get_simlock_unlock_data(&unlock_status, rck_h);
	if (ret != FCSERR_OK)
		FCS_LOG_ERR("Failed to get unlock data: (%d)\n", ret);

	return ret;
}

int get_default_security(char *buf, size_t buf_size)
{
	int res = FCSERR_OK;
	bool is_fused = true;

	if (buf == NULL) {
		FCS_LOG_ERR("Invalid argument, buf is NULL\n");
		return -FCSERR_EINVAL;
	}

	res = core_is_fused(&is_fused);
	if (res < 0) {
		FCS_LOG_ERR("Failed to get fuse status\n");
		return res;
	}

	if (is_fused)
		strlcpy(buf, "ON", buf_size);
	else
		strlcpy(buf, "OFF", buf_size);

	return res;
}

int is_partition_restricted(char *partition, bool *is_restricted)
{
	int res = FCSERR_OK;
	int i;
	uint8_t rooting_status;
	bool is_fused = false;

	if (partition == NULL || is_restricted == NULL) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	*is_restricted = true;

	res = sec_data_get_rooting_status(&rooting_status);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get rooting status\n");
		return res;
	}

	if (rooting_status != BOOT_UNLOCKED) {
		FCS_LOG_INF("Bootloader is locked, partition is restricted\n");
		return FCSERR_OK;
	}

	res = core_is_fused(&is_fused);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get fuse status\n");
		return res;
	}

	if (is_fused) {
		for (i = 0; i < no_of_allowed_ptns; i++) {
			if (strncmp(partition, allowed_ptns[i],
					strlen(allowed_ptns[i]) + 1) == 0) {
				*is_restricted = false;
				return FCSERR_OK;
			}
		}
	} else {
		*is_restricted = false;
	}

	return FCSERR_OK;
}

static void *pu_hash_loop(void *param)
{
	struct digest_context *ctx = (struct digest_context *)param;
	int res = FCSERR_OK;
	int wres = 0;
	struct timespec t;

	while (1) {

		if (clock_gettime(CLOCK_REALTIME, &t) == -1) {
			FCS_LOG_ERR("Timeout\n");
			res = -FCSERR_ETIME;
			goto exit;
		}
		t.tv_sec += PU_DIGEST_TIMEOUT;

		pthread_mutex_lock(&pu_hash_mutex);
		while (ctx->hstate == PU_IDLE) {
			wres = pthread_cond_timedwait(
				&pu_read_done, &pu_hash_mutex, &t);
			if (wres == ETIMEDOUT) {
				FCS_LOG_ERR("Flash read timeout\n");
				res = -FCSERR_EIO;
				pthread_mutex_unlock(&pu_hash_mutex);
				goto exit;
			}
		}
		pthread_mutex_unlock(&pu_hash_mutex);

		if (ctx->len == 0)
			goto exit;

		res = digest_sha224_update(ctx->dgst, ctx->buf, ctx->len);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to update digest: (%d)\n", res);
			goto exit;
		}

		/* signal hash is done */
		pthread_mutex_lock(&pu_hash_mutex);
		ctx->hstate = PU_IDLE;
		pthread_cond_signal(&pu_hash_done);
		pthread_mutex_unlock(&pu_hash_mutex);
	}

exit:
	ctx->res = res;
	return NULL;
}

static int pu_digest_sync(
	struct digest_context *dctx, uint8_t *buf, size_t len)
{
	int res;
	struct timespec t;

	if (!dctx) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	if (clock_gettime(CLOCK_REALTIME, &t) == -1) {
		FCS_LOG_ERR("Timeout\n");
		return -FCSERR_ETIME;
	}
	t.tv_sec += PU_DIGEST_TIMEOUT;

	/* wait for hash to be done */
	pthread_mutex_lock(&pu_hash_mutex);
	while (dctx->hstate != PU_IDLE) {
		res = pthread_cond_timedwait(&pu_hash_done, &pu_hash_mutex, &t);

		if (res == ETIMEDOUT) {
			FCS_LOG_ERR("Flash read timeout\n");
			pthread_mutex_unlock(&pu_hash_mutex);
			return -FCSERR_EIO;
		}
	}
	dctx->buf = buf;
	dctx->len = len;
	dctx->hstate = PU_RUNNING;
	pthread_cond_signal(&pu_read_done);
	pthread_mutex_unlock(&pu_hash_mutex);

	return FCSERR_OK;
}

int pu_digest_partition(const char *part, uint8_t *val, size_t len)
{
	struct storage_ctx *sctx = NULL;
	ssize_t sz;
	int res = FCSERR_OK;
	uint8_t *buf = NULL;
	unsigned int i = 0;
	unsigned int nchunks;
	size_t chunk_size;
	size_t proc_data = 0;
	struct digest *dgst = NULL;
	uint8_t *calc_hash = NULL;
	uint32_t calc_hash_length = 0;
	struct digest_context dctx;
	static pthread_t digesthread;
	bool join = false;

	if (!val) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	sctx = storage_open_by_name(NULL, part);
	if (sctx == NULL) {
		FCS_LOG_ERR("Failed to open storage\n");
		if (part)
			FCS_LOG_ERR("Partition: %s\n", part);
		return -FCSERR_EINVAL;
	}

	sz = pu_get_part_size(sctx);
	if (sz < 0) {
		FCS_LOG_ERR("IO Error\n");
		res = -FCSERR_EIO;
		goto exit;
	}

	buf = (uint8_t *)malloc(PU_DIGEST_CHUNK * 2);
	if (buf == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		res = -FCSERR_ENOMEM;
		goto exit;
	}

	chunk_size = (MIN(sz, PU_DIGEST_CHUNK));
	nchunks = (sz / chunk_size);
	if (sz % chunk_size)
		nchunks++;

	res = digest_sha256_init(&dgst);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to init digest calculation: (%d)\n", res);
		goto exit;
	}

	dctx.dgst = dgst;
	dctx.hstate = PU_IDLE;
	dctx.res = FCSERR_OK;
	pthread_create(&digesthread, 0, pu_hash_loop, &dctx);
	join = true;

	/*
	 * This implementation assumes reading from flash is slower than
	 * hashing.
	 */
	while (proc_data < (size_t)sz) {

		res = storage_read(sctx, buf + i * PU_DIGEST_CHUNK, chunk_size);
		if ((size_t)res != chunk_size) {
			FCS_LOG_ERR("Read fail\n");
			if (res >= 0)
				res = -FCSERR_EIO;
			goto exit;
		}

		res = pu_digest_sync(
			&dctx, buf + i * PU_DIGEST_CHUNK, chunk_size);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Sync failed\n");
			goto exit;
		}

		i = !i;
		proc_data += chunk_size;
		chunk_size = MIN(sz - proc_data, PU_DIGEST_CHUNK);
	}

	res = pu_digest_sync(&dctx, NULL, 0);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Sync failed\n");
		goto exit;
	}
	pthread_join(digesthread, NULL);
	join = false;

	if (dctx.res != FCSERR_OK) {
		FCS_LOG_ERR("hash thread returned an error\n");
		goto exit;
	}

	res = digest_sha256_final(dgst, &calc_hash, &calc_hash_length);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to finalize digest: (%d)\n", res);
		goto exit;
	}

	if (len < calc_hash_length) {
		FCS_LOG_ERR("hash length larger than buffer size\n");
		res = -FCSERR_ENOMEM;
		goto exit;
	}
	memcpy(val, calc_hash, calc_hash_length);

exit:
	if (join)
		pthread_join(digesthread, NULL);
	digest_sha256_deinit(dgst);
	free(buf);
	storage_close(sctx);
	return res;
}

ssize_t pu_get_part_size(struct storage_ctx *ctx)
{
	ssize_t size;
	off_t current_pos;

	/* Save file pointer position */
	current_pos = storage_lseek(ctx, 0, STORAGE_SEEK_CUR);
	if (current_pos < 0) {
		FCS_LOG_ERR("Seek failed (errno=%d)\n", errno);
		return -FCSERR_EONE;
	}

	size = storage_lseek(ctx, 0, STORAGE_SEEK_END);
	if (size < 0) {
		FCS_LOG_ERR("Seek failed (errno=%d)\n", errno);
		return size;
	}

	/* Restore file pointer */
	if (storage_lseek(ctx, current_pos, STORAGE_SEEK_SET) < 0) {
		FCS_LOG_ERR("Seek failed (errno=%d)\n", errno);
		return -FCSERR_EONE;
	}

	return size;
}

int pu_get_part_type(const char *ptn, char *type, size_t type_size)
{
	int i;

	if (!ptn || !type) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	for (i = 0; i < no_of_ext4_ptns; i++)
		if (strncmp(ptn, ext4_ptns[i], strlen(ext4_ptns[i]) + 1) == 0) {
			strlcpy(type, "ext4", type_size);
			return FCSERR_OK;
		}
	// since most of the partitions are labeled as raw
	strlcpy(type, "raw", type_size);

	return FCSERR_OK;
}

/* Writes a comma separated list of flash vendor, model and revision in val */
int pu_get_flash_info(char *buf, int buf_size)
{
	int res = FCSERR_OK;
	char *name = NULL;
	struct flash_info_data fi_data;

	if (!buf) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	name = malloc(buf_size);
	if (name == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		res = -FCSERR_ENOMEM;
		goto exit;
	}

	fi_data.name = name;
	fi_data.buf = buf;
	fi_data.buf_size = buf_size;
	fi_data.index = 0;
	fi_data.type = FLASH_TYPE;

	/* Get vendor */
	res = fcs_get_flash_info_data(FLASH_VENDOR, &fi_data);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to read the flash memory vendor name\n");
		goto exit;
	}

	fi_data.buf[fi_data.index] = ',';
	fi_data.index++;
	fi_data.buf += fi_data.index;

	/* Get model(UFS storage)/OEMID(eMMC storage) */
	res = fcs_get_flash_info_data(FLASH_MODEL, &fi_data);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to read flash memory model/oemid\n");
		goto exit;
	}

	fi_data.buf[fi_data.index] = ',';
	fi_data.index++;
	fi_data.buf += fi_data.index;

	/* Finally get revision */
	res = fcs_get_flash_info_data(FLASH_REVISION, &fi_data);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to read flash memory revision\n");
		goto exit;
	}

	fi_data.buf[fi_data.index] = '\0';

exit:
	free(name);

	return res;
}
