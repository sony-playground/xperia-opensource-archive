/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdio.h>
#include <unistd.h>

#include "input_args.h"
#include "fcslog.h"
#include "loader.h"
#include "uevent_handler.h"

int main(int argc, char **argv)
{
	int res;
	struct loader_ctx ctx;
	struct uevent_par u_par;

	res = input_args_set(argc, argv);
	if (res < 0) {
		FCS_LOG_ERR("args_set failed (%x)\n", res);
		return res;
	}

	/* Default charge the battery to 70% */
	u_par.battery_capacity = 70;

	res = uevent_handle_update(u_par);
	if (res < 0) {
		FCS_LOG_ERR("uevent_handle_update failed (%x)\n", res);
		return res;
	}

	res = loader_main(&ctx);

	uevent_thread_join();

	return 0;
}
