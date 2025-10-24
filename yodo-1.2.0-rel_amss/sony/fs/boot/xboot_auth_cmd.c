/*
 * Copyright (c) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "xboot_auth_cmd.h"

#include "xboot_pal_include.h"
#include "xboot_pal_types.h"
#include "authenticate.h"
#include "auth_ch.h"
#include "fcserr.h"
#include "fcslog.h"
#include "ta_interface.h"
#include "rpmbio.h"
#include "xboot_glue.h"
#include "sake_nonce.h"
#include "core.h"
#include "xflattest.h"
#include "xflattest_int.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static int xboot_sake_auth(uint8_t *cmd, size_t sz, int *state)
{
	int res;
	struct authenticate_ctx *ctx = NULL;
	struct auth_ch_auth *xcmd = (struct auth_ch_auth *)cmd;

	if (!cmd || !state) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	/* xcmd + 1 equals to moving the pointer sizeof(_variable_) number of
	 * bytes forward. The below statement will send in the buffer appended
	 * after the struct into authenticate_init. This data is in this case
	 * the revision string. The same pattern is used further down below in
	 * this file.
	 */
	res = authenticate_init(
		&ctx, xcmd->ssn, (char *)(xcmd + 1), xcmd->rev_str_sz);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Authenticate init failed (%d)\n", res);
		return res;
	}

	/* check response buffer */
	res = authenticate_verify_response(
		&ctx, (uint8_t *)(xcmd + 1) + xcmd->rev_str_sz,
		xcmd->response_sz);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Authenticate failed (%d)\n", res);
		goto exit;
	}

	res = authenticate_get_level(ctx, (uint8_t *)state);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get level (%d)\n", res);
		goto exit;
	}

exit:
	authenticate_destroy(ctx);

	return res;
}

static int xboot_reset_vbmeta_arb(uint8_t *cmd, size_t sz, int state)
{
	/* check authentication state */
	if (state != AUTH_LEVEL_PRODUCTION &&
	    state != AUTH_LEVEL_CUSTOMER_SERVICE) {
		FCS_LOG_ERR("Not authenticated %d\n", state);
		return -FCSERR_ESTATE;
	}

	/* erase userdata and set recovery mode */
	if (!xbpal_erase_user_sensitive()) {
		FCS_LOG_ERR("Failed to erase user sensitive data\n");
		return -FCSERR_ESTATE;
	}

	/* reset counters */
	if (xbpal_reset_vbmeta_counters()) {
		FCS_LOG_ERR("Reset failed\n");
		return -FCSERR_EIO;
	}

	return FCSERR_OK;
}

static int xboot_oem_lock(uint8_t *cmd, size_t sz, int state)
{
	if (state != AUTH_LEVEL_PRODUCTION) {
		FCS_LOG_ERR("Not production authenticated %d\n", state);
		return -FCSERR_ESTATE;
	}

	if (xboot_lock_bootloader()) {
		FCS_LOG_ERR("Bootloader lock failed\n");
		return -FCSERR_EIO;
	}

	return FCSERR_OK;
}

static int xboot_get_auth_cmd_sz(struct auth_ch_cmd *cmd, size_t *sz)
{
	if (!cmd || !sz) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	if (cmd->magic != AUTH_CH_MAGIC) {
		FCS_LOG_ERR("Invalid magic %x\n", cmd->magic);
		return -FCSERR_EDATA;
	}

	if (cmd->version != AUTH_CH_VERSION) {
		FCS_LOG_ERR("Invalid version %x\n", cmd->version);
		return -FCSERR_EINVAL;
	}

	*sz = cmd->sz;

	return FCSERR_OK;
}

static int xboot_exec_auth_cmd(struct auth_ch_cmd *cmd, int *state)
{
	if (!cmd || !state) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	switch (cmd->id) {
	case AUTH_CH_SAKE_AUTH:
		return xboot_sake_auth(
			(uint8_t *)(cmd + 1), cmd->sz, state);
	case AUTH_CH_RESET_VBMETA_ARB:
		return xboot_reset_vbmeta_arb(
			(uint8_t *)(cmd + 1), cmd->sz, *state);
	case AUTH_CH_OEM_LOCK:
		return xboot_oem_lock(
			(uint8_t *)(cmd + 1), cmd->sz, *state);
	default:
		FCS_LOG_ERR("Invalid cmd %u\n", cmd->id);
		return -FCSERR_EINVAL;
	}
}

int xboot_gen_nonce(void)
{
	int res;
	struct xfl_sec_data data;
	bool is_fused;

	res = core_is_fused(&is_fused);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Get fused info failed (%d)\n", res);
		return res;
	}

	res = read_xfl_sec_data(&data);
	if (res != FCSERR_OK) {
		if (!is_fused) {
			/* If the device is not fused, xfl_sec_data is read
			 * from MiscTA. Invalid MiscTA should not cause
			 * this function to fail. Return here, nonce will be
			 * generated in xboot_get_auth_ch_nonce().
			 */
			return FCSERR_OK;
		}
		FCS_LOG_ERR("Failed to read xfl_sec_data (%d)\n", res);
		return res;
	}

	fcs_urand(data.sake_nonce, sizeof(data.sake_nonce));
	res = write_xfl_sec_data(&data);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to write xfl_sec_data (%d)\n", res);
		return res;
	}

	return FCSERR_OK;
}

int xboot_auth_cmd(struct xboot_ctx *ctx)
{
	int unit_size = 0;
	uint8_t *unit_buf = NULL;
	uint8_t *cmd_buf = NULL;
	int ret;
	size_t cmd_size;
	int state = AUTH_LEVEL_NONE;

	if (!ctx) {
		FCS_LOG_ERR("Invalid param\n");
		ret = -FCSERR_EINVAL;
		goto exit;
	}

	ret = get_ta_unit_size(TA_MISC_PART, TA_AUTH_CH, &unit_size);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("get_ta_unit_size returned err=%d\n", ret);
		goto exit;
	}

	/* If unit_size < sizeof auth_ch_cmd there is no request to handle =>
	 * End with OK.
	 */
	if (unit_size < sizeof(struct auth_ch_cmd))
		goto exit;

	unit_buf = malloc(unit_size);
	if (unit_buf == NULL) {
		FCS_LOG_ERR("Failed to allocate memory\n");
		ret = -FCSERR_ENOMEM;
		goto exit;
	}

	ret = read_ta(TA_MISC_PART, TA_AUTH_CH, unit_buf, unit_size);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("read_ta returned err %d\n", ret);
		goto exit;
	}

	cmd_buf = unit_buf;
	while (cmd_buf < unit_buf + unit_size) {
		ret = xboot_get_auth_cmd_sz(
			(struct auth_ch_cmd *)cmd_buf, &cmd_size);
		if (ret == -FCSERR_EDATA) {
			/* Magic in TA data is invalid, this is ok.
			 * This case might happen when we only have
			 * authenticated but no loader auth boot cmds
			 * are sent
			 */
			ret = FCSERR_OK;
			goto exit;
		}
		if (ret != FCSERR_OK) {
			FCS_LOG_ERR("Get size failed %d\n", ret);
			goto exit;
		}

		/* make sure that we do not read outside the buffer */
		if (cmd_buf + cmd_size + sizeof(struct auth_ch_cmd) >
		    unit_buf + unit_size) {
			/* the data in the TA is invalid */
			FCS_LOG_ERR("Cmd buffer data invalid\n");
			ret = -FCSERR_ESTATE;
			goto exit;
		}

		ret = xboot_exec_auth_cmd(
			(struct auth_ch_cmd *)cmd_buf, &state);
		if (ret != FCSERR_OK) {
			FCS_LOG_ERR("Exec failed %d\n", ret);
			goto exit;
		}

		/* go to next cmd */
		cmd_buf += cmd_size + sizeof(struct auth_ch_cmd);
	}

exit:
	/* Wipe unit */
	delete_ta(TA_MISC_PART, TA_AUTH_CH);

	free(unit_buf);

	return ret;
}

int sake_get_nonce(uint8_t *nonce, size_t len)
{
	int res = FCSERR_OK;
	struct xfl_sec_data data;
	int i = 0;
	uint32_t sum = 0;
	static bool get_nonce = false;
	static uint8_t  cached_sake_nonce[XFLATTEST_NONCE_LEN] = {};

	if (nonce == NULL || len < SAKE_NONCE_LEN) {
		FCS_LOG_ERR("Incorrect input\n");
		return -FCSERR_EINVAL;
	}

	if (get_nonce == false) {
		res = read_xfl_sec_data(&data);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to read xfl_sec_data (%d)\n", res);
			/* continue and try to clear nonce anyway (if needed) */
		}

		/* check if nonce is 0 */
		for (; i < sizeof(data.sake_nonce); i++)
			sum |= data.sake_nonce[i];
		if (!sum) {
			FCS_LOG_ERR("Incorrect nonce\n", res);
			res = -FCSERR_ESTATE;
			goto exit;
		}

		memcpy(cached_sake_nonce, data.sake_nonce, sizeof(data.sake_nonce));

		/* clear sake_nonce */
		memset(data.sake_nonce, 0, sizeof(data.sake_nonce));
		res = write_xfl_sec_data(&data);
		if (res != FCSERR_OK)
			FCS_LOG_ERR("Failed to write xfl_sec_data (%d)\n", res);

		get_nonce = true;
	}

	memcpy(nonce, cached_sake_nonce, sizeof(data.sake_nonce));

exit:
	return res;
}
