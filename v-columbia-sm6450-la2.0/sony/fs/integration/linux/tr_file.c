/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "transport.h"
#include "fcslog.h"
#include "input_args.h"
#include "fcserr.h"
#include "module_test.h"

#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

struct transport {
	char *path;
	FILE *fd_in;
	FILE *fd_out;
	FILE *fd_data;
};

/* File names for handshaking with host */
const char *GO_HOST_FILE = "/go_host";
const char *GO_DEVICE_FILE = "/go_device";

/*
 * Open connection. It is assumed that the implementation of this interface can
 * retrieve parameters needed.
 */
struct transport *tr_open(void)
{
	struct transport *hdl = NULL;
	char path_out[PATH_MAX] = {0};

	/* Allocate handle */
	hdl = calloc(1, sizeof(struct transport));
	if (!hdl) {
		FCS_LOG_ERR("calloc handle failed\n");
		return NULL;
	}

	hdl->path = input_args_get_gadget();
	if (!strlen(hdl->path)) {
		FCS_LOG_ERR("invalid input, path: %s\n", hdl->path);
		goto fail;
	}

	hdl->fd_in = fopen(hdl->path, "r");
	if (!hdl->fd_in) {
		FCS_LOG_ERR("open %s failed (%d)\n",
			hdl->path, errno);
		goto fail;
	}

	snprintf(path_out, sizeof(path_out), "%s_out", hdl->path);
	hdl->fd_out = fopen(path_out, "w");
	if (!hdl->fd_out) {
		FCS_LOG_ERR("open %s failed (%d_out)\n",
			hdl->path, errno);
		goto fail;
	}

	return hdl;

fail:
	free(hdl);
	return NULL;
}

/*
 * Close and reopen connection for input data
 */
struct transport *tr_reopen(struct transport *handle)
{
	char path_out[PATH_MAX] = {0};

	if (!handle) {
		FCS_LOG_ERR("No handle\n");
		return NULL;
	}

	if (handle->fd_in)
		fclose(handle->fd_in);
	if (handle->fd_out)
		fclose(handle->fd_out);

	FCS_LOG_INF("open %s\n", handle->path);

	handle->fd_in = fopen(handle->path, "r");
	if (!handle->fd_in) {
		FCS_LOG_ERR("tr_open, open %s failed (%d)\n",
			handle->path, errno);
		goto fail;
	}

	snprintf(path_out, sizeof(path_out), "%s_out", handle->path);
	handle->fd_out = fopen(path_out, "w");
	if (!handle->fd_out) {
		FCS_LOG_ERR("tr_open, open %s failed (%d_out)\n",
			handle->path, errno);
		goto fail;
	}

	return handle;

fail:
	free(handle);
	return NULL;
}

/*
 * Close connection and free up resources.
 */
void tr_close(struct transport *handle)
{
	if (!handle)
		return;

	if (handle->fd_in)
		fclose(handle->fd_in);

	if (handle->fd_out)
		fclose(handle->fd_out);

	free(handle);
}

/*
 * Read data from transport interface.
 * The input handle is implementation defined.
 */
int tr_read(struct transport *handle, uint8_t *data_p, size_t size)
{
	int ret = 0;
	char *line = NULL;
	size_t sz;
	char *sstr, *sstr_tmp;
	FILE *fd_wait;
	FILE *fd_go;

	FCS_LOG_INF("enter (%zd) bytes\n", size);

	if (!handle) {
		FCS_LOG_ERR("No handle\n");
		return -FCSERR_EINVAL;
	}

	if (!data_p) {
		FCS_LOG_ERR("Invalid data_p\n");
		return -FCSERR_EINVAL;
	}

	while (1) {

		if (handle->fd_data) {
			ret = fread(data_p, 1, size, handle->fd_data);

			if (ret)
				return ret;

			fclose(handle->fd_data);
		}

		ret = getline(&line, &sz, handle->fd_in);
		FCS_LOG_INF("done - ret (%d), line=%s\n", ret, line);

		if (ret <= 0) {
			FCS_LOG_INF(
				"failed - ret (%d) errno (%d)\n",
				ret, errno);
			free(line);
			/* no more commands in queue
			 * exit the loader
			 */
			exit(0);
		}

		/*
		 * checkpatch fails:
		 * sstr = strchr(line, '\n');
		 * and 'strnchr' not present
		 */
		sstr = line;
		while (1) {
			if (sstr >= line + sz) {
				sstr = NULL;
				break;
			} else if (*sstr == '\n')
				break;
			else if (*sstr == '\0') {
				sstr = NULL;
				break;
			}
			sstr++;
		}

		if (sstr)
			*sstr = 0;

		sstr = strtok(line, " ");

		if (strlen(sstr) != 1) {
			FCS_LOG_ERR(
				"cmd invalid (%s) - line (%s)\n",
				sstr, line);
			free(line);
			return -FCSERR_EIO;
		}

		if (sstr[0] == 'b') {
			sstr = strtok(NULL, " ");
			FCS_LOG_INF("Command b %s\n", sstr);
			handle->fd_data = fopen(sstr, "r");
			free(line);

			if (handle->fd_data == 0) {
				FCS_LOG_ERR("no such file (%s)\n", sstr);
				return -FCSERR_ENOENT;
			}

			return tr_read(handle, data_p, size);
		}

		if (sstr[0] == 'w') {
			fflush(handle->fd_out);
			/* Handshake to the host */
			fd_go = fopen(GO_HOST_FILE, "w");
			if (!fd_go) {
				FCS_LOG_ERR("open %s failed (%d)\n",
					GO_HOST_FILE, errno);
				free(line);
				return -FCSERR_ENOENT;
			}
			fclose(fd_go);

			do {
				fd_wait = fopen(GO_DEVICE_FILE, "r");
				FCS_LOG_INF("Waiting for %s\n", GO_DEVICE_FILE);
				sleep(1);
			} while (fd_wait == 0);
			FCS_LOG_INF("response file exists!\n");
			fclose(fd_wait);
			free(line);
			/*
			 * Delete the handshake file to be prepared for next
			 * time.
			 */
			ret = unlink(GO_DEVICE_FILE);
			if (ret < 0) {
				FCS_LOG_ERR("unlink %s failed (%d)\n",
					GO_DEVICE_FILE, errno);
				return -FCSERR_ENOENT;
			}
			/*
			 * Reopen command file because new commands might
			 * be available.
			 */
			handle = tr_reopen(handle);
			return tr_read(handle, data_p, size);
		}

		if (sstr[0] == 'c') {
			sstr = strtok(NULL, " ");
			/* For fastboot commands with space like oem unlock */
			while ((sstr_tmp = strtok(NULL, " ")))
				snprintf(sstr,
					(strlen(sstr) + strlen(sstr_tmp) + 2),
					"%s %s", sstr, sstr_tmp);
			FCS_LOG_INF("Command %s\n", sstr);
			ret = strlcpy((char *)data_p, sstr, size);
			free(line);
			return ret;
		}

		if (sstr[0] == 'm') {
			sstr = strtok(NULL, " ");
			ret = strlcpy((char *)data_p, sstr, size);
			ret = execute_module(handle->fd_out, data_p, size);
			free(line);
		}

	}

	FCS_LOG_ERR("invalid command (%s)\n", line);
	free(line);
	return -FCSERR_EINVAL;
}

/*
 * Write data from USB interface. The input handle is implementation defined.
 */
int tr_write(struct transport *handle, uint8_t *data_p, size_t size)
{
	int ret = 0;

	FCS_LOG_INF("enter (%zd) bytes\n", size);

	if (!handle) {
		FCS_LOG_ERR("No handle\n");
		return -FCSERR_EINVAL;
	}

	ret = fwrite(data_p, 1, size, handle->fd_out);

	FCS_LOG_INF("usb_write, done - ret (%d)\n", ret);

	if (ret < 0) {
		FCS_LOG_ERR(
			"usb_write failed - ret (%d) errno (%d)\n",
			ret, errno);
		return -FCSERR_EIO;
	} else
		return ret;
}

/*
 * Returns how large reads you can make from tr_read
 */
size_t tr_get_max_read_size(void)
{
	return 4 * 1024 * 1024;
}
