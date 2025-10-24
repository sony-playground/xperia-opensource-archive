/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <transport.h>
#include <fcslog.h>
#include <fcserr.h>
#include <module_test.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#define TRP_PIPE_FLAGS 0666

#define TRP_CMD_SZ (1 * 1024 * 1024)

#define TRP_GEN_RESP(buf, msg, args...)				\
	snprintf((char *)(buf), TRP_CMD_SZ, msg, ##args)
#define TRP_CHECK_CMD(cmd, buf, size)		\
	((size_t)size == strlen(cmd) && strncmp(cmd, buf, strlen(cmd)) == 0)

static pthread_t cmd_thread;

struct transport {
	char *path;
};

struct tr_cmd {
	char *cmd;
	char *data;
};

static int tr_cmd_process(struct tr_cmd *ctx, void *buf, int sz)
{
	(void)ctx;
	FILE *fd_out;
	size_t osz = 0;

	/* process stuff */
	if (TRP_CHECK_CMD("exit", buf, sz)) {
		FCS_LOG("EXIT");
		exit(0);
	} else if (TRP_CHECK_CMD("modtst", buf, 6)) {

		if (strlen(buf) < 8) {
			FCS_LOG_ERR("no arguments provided\n");
			TRP_GEN_RESP(buf, "ERRORmodtst, no arguments");
			goto exit;
		}

		fd_out = fopen("/ocmd", "w+");

		(void)execute_module(fd_out, ((uint8_t *)buf) + 7, sz - 7);

		fseek(fd_out, 0L, SEEK_SET);
		osz = fread(buf, 1, TRP_CMD_SZ, fd_out);
		((uint8_t *)buf)[osz] = 0;
		fclose(fd_out);
	}

exit:
	return strlen(buf);
}

static void *tr_cmd_loop(void *param)
{
	int ret;
	void *buf = malloc(TRP_CMD_SZ);
	FILE *fcmd;
	FILE *fres;
	struct tr_cmd ctx;

	(void)param;

	ctx.cmd = NULL;
	ctx.data = NULL;

	if (!buf) {
		FCS_LOG_ERR("malloc failed, exit\n");
		/* kill loader */
		exit(-1);
	}

	while (1) {
		FCS_LOG_INF("Wait for cmd\n");

		fcmd = fopen("/trp_cmd", "r");
		if (!fcmd) {
			FCS_LOG_ERR("Open failed (%d)\n", errno);
			/* kill loader */
			exit(-1);
		}

		ret = fread(buf, 1, TRP_CMD_SZ, fcmd);
		if (ret)
			ret = tr_cmd_process(&ctx, buf, ret);
		fclose(fcmd);

		FCS_LOG_INF("Send res\n");
		fres = fopen("/trp_res", "w");
		if (!fres) {
			FCS_LOG_ERR("Open failed (%d)\n", errno);
			/* kill loader */
			exit(-1);
		}

		if (ret)
			fwrite(buf, 1, ret, fres);
		else
			fwrite("ERRORno response", 1, 16, fres);

		fclose(fres);

	}
}

struct transport *tr_open(void)
{
	struct transport *hdl = NULL;

	umask(0);

	/* Allocate handle */
	hdl = calloc(1, sizeof(struct transport));
	if (!hdl) {
		FCS_LOG_ERR("calloc handle failed\n");
		return NULL;
	}

	/* just print in case of fail */
	if (mkfifo("/trp_in", TRP_PIPE_FLAGS))
		FCS_LOG_INF("mkfifo failed\n");
	if (mkfifo("/trp_out", TRP_PIPE_FLAGS))
		FCS_LOG_INF("mkfifo failed\n");
	if (mkfifo("/trp_cmd", TRP_PIPE_FLAGS))
		FCS_LOG_INF("mkfifo failed\n");
	if (mkfifo("/trp_res", TRP_PIPE_FLAGS))
		FCS_LOG_INF("mkfifo failed\n");

	/* create cmd thread */
	pthread_create(&cmd_thread, 0, tr_cmd_loop, hdl);

	return hdl;
}

/*
 * Close connection and free up resources.
 */
void tr_close(struct transport *handle)
{
	if (!handle)
		return;

	free(handle);
}

/*
 * Read data from transport interface.
 * The input handle is implementation defined.
 */
int tr_read(struct transport *handle, uint8_t *data_p, size_t size)
{
	int ret = 0;
	FILE *fin;

	FCS_LOG_INF("enter (%zd) bytes\n", size);

	if (!handle) {
		FCS_LOG_ERR("No handle\n");
		return -FCSERR_EINVAL;
	}

	if (!data_p) {
		FCS_LOG_ERR("Invalid data_p\n");
		return -FCSERR_EINVAL;
	}

	FCS_LOG_INF("Wait for data\n");
	fin = fopen("/trp_in", "r");
	if (!fin) {
		FCS_LOG_ERR("Open failed (%d)\n", errno);
		return -FCSERR_EIO;
	}

	if (fin)
		ret = fread(data_p, 1, size, fin);

	fclose(fin);

	return ret;
}


int tr_write(struct transport *handle, uint8_t *data_p, size_t size)
{
	int ret = 0;
	FILE *fout;

	FCS_LOG_INF("enter (%zd) bytes\n", size);

	if (!handle) {
		FCS_LOG_ERR("No handle\n");
		return -FCSERR_EINVAL;
	}

	fout = fopen("/trp_out", "w");
	if (!fout) {
		FCS_LOG_ERR("Open failed (%d)\n", errno);
		return -FCSERR_EIO;
	}


	ret = fwrite(data_p, 1, size, fout);
	fclose(fout);

	FCS_LOG_INF("usb_write, done - ret (%d)\n", ret);

	if (ret < 0) {
		FCS_LOG_ERR("usb_write failed - ret (%d) errno (%d)\n",
			    ret, errno);
		return -FCSERR_EIO;
	} else
		return ret;
}

size_t tr_get_max_read_size(void)
{
	return 100 * 1024 * 1024;
}
