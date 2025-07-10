/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "power.h"
#include "fcsenv_def.h"
#include "fcserr.h"
#include "fcslog.h"
#include "input_args.h"
#include "uevent_handler.h"
#include <poll.h>
#include <pthread.h>
#include <unistd.h>
#include <asm/types.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <linux/netlink.h>
#include "fcs_prop.h"
#include "fcsenv_def.h"
#include "protocol_util.h"
#include <storage.h>

#define UEVENT_HANDLER_POLL_FD		(2)
#define UEVENT_BUFFER			(10 * 1024)
#define EVENT_UNHANDLED			(0)
#define EVENT_BATTERY_PWSUP		(1)
#define EVENT_USB_PWSUP			(2)
#define UEVENT_USB_PRESENT_MAX_RETRIES  (3)

struct uevent_handle_par {
	uint8_t battery_capacity;
	int pipe_in;
};

static pthread_t uevent_thread_id;

static bool l_purge;

void purge_usb_removal(bool purge)
{
	l_purge = purge;
}

static int set_charging(bool state)
{
#ifdef DISABLE_CHARGING_CMD
	(void)(state); /* Unused parameter */
	return FCSERR_OK;
#else
	int fd, res;
	char charging_state;

	fd = open(CHARGING_SYSFS_NODE, O_RDWR);

	if (fd < 0) {
		FCS_LOG_ERR("failed to open %s, errno = %d\n",
				CHARGING_SYSFS_NODE, errno);
		return -FCSERR_EOPEN;
	}

	res = read(fd, &charging_state, sizeof(charging_state));

	if (res <= 0) {
		FCS_LOG_ERR("failed to read from %s, errno = %d\n",
				CHARGING_SYSFS_NODE, errno);
		close(fd);
		return -FCSERR_EIO;
	}

	/* Write to sysfs only if the charging state is changed */
	if (state) {
		if (memcmp(&charging_state, CHARGING_ENABLE,
				sizeof(charging_state)))
			res = write(fd, CHARGING_ENABLE, 1);
	} else {
		if (memcmp(&charging_state, CHARGING_DISABLE,
				sizeof(charging_state)))
			res = write(fd, CHARGING_DISABLE, 1);
	}

	if (res <= 0) {
		FCS_LOG_ERR("failed to write to %s, errno = %d\n",
				CHARGING_SYSFS_NODE, errno);
		close(fd);
		return -FCSERR_EIO;
	}

	close(fd);
	return FCSERR_OK;
#endif
}

static int uevent_handle_charging(const char *buf, const int len,
		int *pos, struct uevent_handle_par *uevent_par)
{
	uint32_t capacity_level;
	char *endptr;
	char *curr_entry;
	int i;
	int res;

	if ((buf == NULL) || (pos == NULL) ||
		(uevent_par == NULL) || (len <= 0)) {
		return -FCSERR_EINVAL;
	}

	i = *pos;

	while (i < len) {
		curr_entry = (char *) buf + i;
		i += strlen(curr_entry) + 1;

		if (!strncmp(curr_entry, BATTERY_POWER_SUPPLY_CAPACITY,
				strlen(BATTERY_POWER_SUPPLY_CAPACITY))) {
			capacity_level = strtol(
					curr_entry +
					strlen(BATTERY_POWER_SUPPLY_CAPACITY),
					&endptr, 10);
			if (endptr == curr_entry) {
				FCS_LOG_ERR("Failed to parse capacity level\n");
				return -FCSERR_EINVAL;
			}

			if (capacity_level >= uevent_par->battery_capacity) {
				res = set_charging(false);
				if (res != 0) {
					FCS_LOG_ERR("set_charging failed %d\n",
							res);
					return res;
				}
			}
			break;
		}
	}

	*pos = i;
	return FCSERR_OK;
}

static int uevent_handle_shutdown(const char *buf, const int len,
		int *pos) {
	char *curr_entry;
	int i;
	int debug_flag;
	int ret;

	if ((buf == NULL) || (pos == NULL) || (len <= 0))
		return -FCSERR_EINVAL;

	i = *pos;

	while (i < len) {
		curr_entry = (char *) buf + i;
		i += strlen(curr_entry) + 1;

		FCS_LOG_INF("Name %s\n", curr_entry);

		if (!strncmp(curr_entry, USB_PWSUP_PRESENT_UEVENT,
				strlen(USB_PWSUP_PRESENT_UEVENT))) {
			FCS_LOG_INF("SHUTDOWN!\n");
			debug_flag = input_args_get_debug();

			if (debug_flag == 0) {
				sleep(2);

				if (fcs_prop_get_shipmode()) {
					int res = set_ship_mode();
					if (res != FCSERR_OK) {
						//shutdown normally if shipmode setting fails.
						FCS_LOG_ERR("Failed to set ship mode (%d)\n", res);
					}
				}

				if (l_purge) {
					sync();

					ret = storage_purge();
					if (ret != FCSERR_OK) {
						FCS_LOG_ERR(
							"purge failed (%d)\n",
							ret);
						return ret;
					}
				}

				ret = fcs_prop_set(FCS_PROP_SHUTDOWN);
				if (ret != FCSERR_OK) {
					FCS_LOG_ERR("prop set failed (%d)\n",
							ret);
					return -FCSERR_EIO;
				}
			}
		}
	}

	*pos = i;
	return FCSERR_OK;
}

static int check_usb_present(void)
{
	int fd_pwsup_present = 0;
	char *usb_pwsup_sysfs = USB_SYSFS_NODE;
	char usb_pwsup_present;
	int debug_flag;
	int i = 0;

	/* Shut down if usb is not present when starting */
	fd_pwsup_present = open(usb_pwsup_sysfs, O_RDONLY);

	if (fd_pwsup_present < 0) {
		FCS_LOG_ERR("Error could not open sysfs file %s, errno (%d)\n",
				usb_pwsup_sysfs, errno);
		return -FCSERR_EOPEN;
	}

	while (i++ < UEVENT_USB_PRESENT_MAX_RETRIES) {
		if (read(fd_pwsup_present, &usb_pwsup_present, 1) != 1) {
			FCS_LOG_ERR(
				"Could not read from sysfs file %s, errno (%d).\n",
				usb_pwsup_sysfs, errno);
			close(fd_pwsup_present);
			return -FCSERR_EIO;
		}

		lseek(fd_pwsup_present, 0, SEEK_SET);

		if (usb_pwsup_present == '0')
			sleep(1);
		else
			break;
	}

	debug_flag = input_args_get_debug();

	if ((usb_pwsup_present == '0') && (debug_flag == 0)) {
		close(fd_pwsup_present);
		sleep(2);
		return fcs_prop_set(FCS_PROP_SHUTDOWN);
	}

	close(fd_pwsup_present);
	return FCSERR_OK;
}

static int get_event_from_entry(char *buff, int buff_len)
{
	char *curr_entry;
	int i = 0;

	if ((buff == NULL) || (buff_len <= 0))
		return -FCSERR_EINVAL;

	while (i < buff_len) {
		curr_entry = (char *) buff + i;
		i += strlen(curr_entry) + 1;

		if (!strncmp(curr_entry, BATTERY_PWSUP_NAME_UEVENT,
					strlen(BATTERY_PWSUP_NAME_UEVENT)))
			return EVENT_BATTERY_PWSUP;

		if (!strncmp(curr_entry, USB_PWSUP_NAME_UEVENT,
					strlen(USB_PWSUP_NAME_UEVENT)))
			return EVENT_USB_PWSUP;
	}

	return EVENT_UNHANDLED;
}

static void *uevent_handler_thread(void *arg)
{
	struct pollfd pfd[UEVENT_HANDLER_POLL_FD];
	struct uevent_handle_par uevent_par =
			*((struct uevent_handle_par *)(arg));
	char buf[UEVENT_BUFFER];
	int res = 0;
	int ev_type = EVENT_UNHANDLED;

	struct sockaddr_nl addr = {
	.nl_family = AF_NETLINK,
	.nl_pad = 0,
	.nl_pid = getpid(),
	.nl_groups = 0xffffffff,
	};

	if (check_usb_present() != FCSERR_OK)
		goto exit;

	if (uevent_par.battery_capacity == 0)
		res = set_charging(false);
	else
		res = set_charging(true);

	if (res != 0) {
		FCS_LOG_ERR("set_charging failed\n");
	}

	pfd[0].fd = socket(AF_NETLINK, SOCK_DGRAM, NETLINK_KOBJECT_UEVENT);
	pfd[1].fd = uevent_par.pipe_in;

	if ((pfd[0].fd == -1) || (pfd[1].fd == -1)) {
		FCS_LOG_ERR("Invalid fd: pfd[0].fd = %d, pfd[1].fd = %d\n",
				pfd[0].fd, pfd[1].fd);
		goto exit;
	}

	pfd[0].events = POLLIN;
	pfd[1].events = POLLIN;

	/* Listen to netlink socket */
	if (bind(pfd[0].fd, (struct sockaddr *) &addr, sizeof(addr))) {
		FCS_LOG_ERR("Failed to bind to socket, errno = %d\n", errno);
		goto exit;
	}

	while (-1 != poll(pfd, UEVENT_HANDLER_POLL_FD, -1)) {
		int len = 0, i = 0;


		if (pfd[0].revents & POLLIN) {
			len = recv(pfd[0].fd, buf, sizeof(buf), MSG_DONTWAIT);
			if (len == -1) {
				FCS_LOG_ERR("recv failed , errno = %d\n",
						errno);
				goto exit;
			}

			buf[len] = '\0';

			ev_type = get_event_from_entry(buf, len);

			if (ev_type < 0)
				goto exit;

			if (ev_type == EVENT_BATTERY_PWSUP) {
				res = uevent_handle_charging(buf, len, &i,
						&uevent_par);
				if (res != FCSERR_OK) {
					FCS_LOG_ERR("handle_charg failed %d\n",
							res);
				}
			}
			if (ev_type == EVENT_USB_PWSUP) {
				res = uevent_handle_shutdown(buf, len, &i);
				if (res != FCSERR_OK) {
					FCS_LOG_ERR("handle_shutd failed %d\n",
							res);
					goto exit;
				}
			}
		}

		if (pfd[1].revents & POLLIN) {
			struct uevent_handle_par uevent_par_update;
			int nbytes = 0;

			nbytes = read(pfd[1].fd, &uevent_par_update,
					sizeof(uevent_par_update));

			if (nbytes != sizeof(uevent_par_update)) {
				FCS_LOG_ERR("Failed to read fd, errno=%d\n",
						errno);
				goto exit;
			}

			/* Stop charging if updated battery capacity
			 * level is 0
			 */
			if (uevent_par_update.battery_capacity == 0)
				res = set_charging(false);
			else
				res = set_charging(true);

			if (res != 0) {
				FCS_LOG_ERR("set_charging failed\n");
			}

			uevent_par.battery_capacity =
					uevent_par_update.battery_capacity;
		}
	}

exit:
	/* We should never end up here
	 * try to disable charging and shutdown the device
	 * if debug flag is not set
	 */
	if (input_args_get_debug() == 0)
		fcs_prop_set(FCS_PROP_SHUTDOWN);

	set_charging(false);
	return NULL;
}

int uevent_handle_update(struct uevent_par update_par)
{
	static struct uevent_handle_par uevent_thread_par;
	static int pipe_fd[2] = { -1, -1 };
	int nbytes = 0;
	int status = 0;

	uevent_thread_par.battery_capacity =
			update_par.battery_capacity;

	if ((pipe_fd[0] == -1) || (pipe_fd[1] == -1)) {
		if (pipe(pipe_fd) < 0) {
			FCS_LOG_ERR("Failed to open pipe\n");
			return -FCSERR_EOPEN;
		}
		uevent_thread_par.pipe_in = pipe_fd[0];
		status = pthread_create(&uevent_thread_id, NULL,
				&uevent_handler_thread,
				(void *) &uevent_thread_par);
		if (status != 0) {
			FCS_LOG_ERR(
				"Failed to create uevent parser thread error = %d!\n",
				status);
			return -status;
		}
	}

	nbytes = write(pipe_fd[1], &uevent_thread_par,
				sizeof(uevent_thread_par));

	if (nbytes != sizeof(uevent_thread_par)) {
		FCS_LOG_ERR("Failed to write to pipe\n");
		return -FCSERR_EIO;
	}

	return FCSERR_OK;
}

void uevent_thread_join(void)
{
	pthread_join(uevent_thread_id, NULL);
}
