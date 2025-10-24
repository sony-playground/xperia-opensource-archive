/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "core.h"
#include "loader.h"
#include "fcslog.h"
#include "fcserr.h"
#include "handler_list.h"
#include "protocol.h"
#include "security_properties.h"
#include "storage.h"
#include "ta_interface.h"
#include "otp.h"
#include "xflattest_int.h"
#include "fcsgfx.h"

int loader_main(struct loader_ctx *ctx)
{
	int res;

	core_crypto_setup();
	res = storage_init();
	if (res) {
		FCS_LOG_ERR("storage_init failed (%d)\n", res);
		return res;
	}

	res = ta_init();
	if (res) {
		FCS_LOG_ERR("ta_init failed (%d)\n", res);
		return res;
	}

	ctx->prot_hdl = prot_init();
	if (!ctx->prot_hdl) {
		FCS_LOG_ERR("prot_init failed\n");
		return -FCSERR_EIO;
	}

	ctx->sec_prop_list = handler_list_init();
	if (!ctx->sec_prop_list) {
		FCS_LOG_ERR("handler_list_init failed\n");
		return -FCSERR_ENOMEM;
	}

	res = handler_list_add_handler(ctx->sec_prop_list,
			&set_devicekey, (void *)DEVICEKEY);
	if (res) {
		FCS_LOG_ERR("handler_list_add_handler failed (%d)\n", res);
		return res;
	}

	res = otp_init(ctx->sec_prop_list);
	if  (res) {
		FCS_LOG_ERR("otp_init failed (%d)\n", res);
		return res;
	}

	res = init_xflattest();
	if (res) {
		FCS_LOG_ERR("init_xflattest failed (%d)\n", res);
		return res;
	}

	ctx->auth_level = 0;

	res = fcsgfx_init();
	if (res)
		FCS_LOG_WRN("gfx_init failed (%d)\n", res);

	while (1) {
		/* We will only break the loop if we get communication errors */

		/* Print "Ready" in the status bar of the display */
		res = fcsgfx_ready();
		if (res)
			FCS_LOG_WRN("fcsgfx_ready failed (%d)\n", res);

		/* get fastboot cmd */
		res = prot_receive_cmd(ctx->prot_hdl);
		if (res) {
			FCS_LOG_ERR("prot_receive_cmd failed (%d)\n", res);
			break;
		}

		/* Print "Working..." in the status bar of the display */
		res = fcsgfx_running();
		if (res)
			FCS_LOG_WRN("fcsgfx_running failed (%d)\n", res);

		/* execute cmd */
		res = prot_proc_cmd(ctx);
		if (res)
			FCS_LOG_ERR("prot_proc_cmd failed (%d)\n", res);

		/* response */
		res = prot_send_response(ctx->prot_hdl);
		if (res) {
			FCS_LOG_ERR("prot_send_response failed (%d)\n", res);
			break;
		}
	}

	prot_final(ctx->prot_hdl);
	core_crypto_cleanup();

	return FCSERR_OK;
}
