/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

/*
 * This file implements transport.h
 */

#include "transport.h"

#include <linux/usb/functionfs.h>
#include <linux/usb/ch9.h>
#include <linux/limits.h>
#include <sys/ioctl.h>

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <pthread.h>
#include <poll.h>

#include "fcslog.h"
#include "fcsenv_def.h"
#include "fcserr.h"
#include "input_args.h"
#include "fcs_prop.h"

#define FFS_EP_ADDR_IN	  1
#define FFS_EP_ADDR_OUT	  2

#define EP0_BUF_SIZE	  4096
#define FFS_XFL		  "XFL"

#define MIN(x, y) ((x) < (y)?(x):(y))

static pthread_t ep0_thread;
static pthread_mutex_t ffs_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t ffs_enabled = PTHREAD_COND_INITIALIZER;

struct func_desc {
	struct usb_interface_descriptor ffs_interface;
	struct usb_endpoint_descriptor_no_audio ffs_ep_in_desc;
	struct usb_endpoint_descriptor_no_audio ffs_ep_out_desc;
} __packed;

#ifdef CFG_USB3
struct ss_func_desc {
	struct usb_interface_descriptor intf;
	struct usb_endpoint_descriptor_no_audio ffs_ep_in_desc;
	struct usb_ss_ep_comp_descriptor ffs_ep_in_comp;
	struct usb_endpoint_descriptor_no_audio ffs_ep_out_desc;
	struct usb_ss_ep_comp_descriptor ffs_ep_out_comp;
} __packed;

static const struct {
	struct usb_functionfs_descs_head_v2 ffs_head;
	__le32 fs_count;
	__le32 hs_count;
	__le32 ss_count;
	struct func_desc ffs_fs_desc, ffs_hs_desc;
	struct ss_func_desc ffs_ss_desc;
} __packed ffs_desc = {
	.ffs_head = {
		.magic = __cpu_to_le32(
			FUNCTIONFS_DESCRIPTORS_MAGIC_V2),
		.length = __cpu_to_le32(sizeof(ffs_desc)),
		.flags =
		FUNCTIONFS_HAS_FS_DESC |
		FUNCTIONFS_HAS_HS_DESC |
		FUNCTIONFS_HAS_SS_DESC,
	},
	.fs_count = __cpu_to_le32(3),
	.hs_count = __cpu_to_le32(3),
	.ss_count = __cpu_to_le32(5),
	.ffs_fs_desc = {
		.ffs_interface = {
			.bLength = USB_DT_INTERFACE_SIZE,
			.bDescriptorType = USB_DT_INTERFACE,
			.bNumEndpoints = 2,
			.bInterfaceClass = USB_CLASS_VENDOR_SPEC,
			.bInterfaceSubClass = 0x42,
			.bInterfaceProtocol = 0x3,
			.iInterface = 1,
		},
		.ffs_ep_in_desc = {
			.bLength = USB_DT_ENDPOINT_SIZE,
			.bDescriptorType = USB_DT_ENDPOINT,
			.bEndpointAddress = USB_DIR_IN | FFS_EP_ADDR_IN,
			.bmAttributes = USB_ENDPOINT_XFER_BULK,
		},
		.ffs_ep_out_desc = {
			.bLength = USB_DT_ENDPOINT_SIZE,
			.bDescriptorType = USB_DT_ENDPOINT,
			.bEndpointAddress = USB_DIR_OUT | FFS_EP_ADDR_OUT,
			.bmAttributes = USB_ENDPOINT_XFER_BULK,
		},
	},
	.ffs_hs_desc = {
		.ffs_interface = {
			.bLength = USB_DT_INTERFACE_SIZE,
			.bDescriptorType = USB_DT_INTERFACE,
			.bNumEndpoints = 2,
			.bInterfaceClass = USB_CLASS_VENDOR_SPEC,
			.bInterfaceSubClass = 0x42,
			.bInterfaceProtocol = 0x3,
			.iInterface = 1,
		},
		.ffs_ep_in_desc = {
			.bLength = USB_DT_ENDPOINT_SIZE,
			.bDescriptorType = USB_DT_ENDPOINT,
			.bEndpointAddress = USB_DIR_IN | FFS_EP_ADDR_IN,
			.bmAttributes = USB_ENDPOINT_XFER_BULK,
			.wMaxPacketSize = __cpu_to_le16(512),
		},
		.ffs_ep_out_desc = {
			.bLength = USB_DT_ENDPOINT_SIZE,
			.bDescriptorType = USB_DT_ENDPOINT,
			.bEndpointAddress = USB_DIR_OUT | FFS_EP_ADDR_OUT,
			.bmAttributes = USB_ENDPOINT_XFER_BULK,
			.wMaxPacketSize = __cpu_to_le16(512),
		},
	},
	.ffs_ss_desc = {
		.intf = {
			.bLength = USB_DT_INTERFACE_SIZE,
			.bDescriptorType = USB_DT_INTERFACE,
			.bInterfaceNumber = 0,
			.bNumEndpoints = 2,
			.bInterfaceClass = USB_CLASS_VENDOR_SPEC,
			.bInterfaceSubClass = 0x42,
			.bInterfaceProtocol = 0x3,
			.iInterface = 1,
		},
		.ffs_ep_in_desc = {
			.bLength = USB_DT_ENDPOINT_SIZE,
			.bDescriptorType = USB_DT_ENDPOINT,
			.bEndpointAddress = FFS_EP_ADDR_IN | USB_DIR_IN,
			.bmAttributes = USB_ENDPOINT_XFER_BULK,
			.wMaxPacketSize = __cpu_to_le16(1024),
		},
		.ffs_ep_in_comp = {
			.bLength = USB_DT_SS_EP_COMP_SIZE,
			.bDescriptorType = USB_DT_SS_ENDPOINT_COMP,
			.bMaxBurst = 4,
		},
		.ffs_ep_out_desc = {
			.bLength = USB_DT_ENDPOINT_SIZE,
			.bDescriptorType = USB_DT_ENDPOINT,
			.bEndpointAddress = FFS_EP_ADDR_OUT | USB_DIR_OUT,
			.bmAttributes = USB_ENDPOINT_XFER_BULK,
			.wMaxPacketSize = __cpu_to_le16(1024),
		},
		.ffs_ep_out_comp = {
			.bLength = USB_DT_SS_EP_COMP_SIZE,
			.bDescriptorType = USB_DT_SS_ENDPOINT_COMP,
			.bMaxBurst = 4,
		},
	},
};
#else /* CFG_USB3 */
static const struct {
	struct usb_functionfs_descs_head ffs_head;
	struct func_desc ffs_fs_desc, ffs_hs_desc;
} __packed ffs_desc = {
	.ffs_head = {
		.magic = __cpu_to_le32(FUNCTIONFS_DESCRIPTORS_MAGIC),
		.length = __cpu_to_le32(sizeof(ffs_desc)),
		.fs_count = __cpu_to_le32(3),
		.hs_count = __cpu_to_le32(3),
	},
	.ffs_fs_desc = {
		.ffs_interface = {
			.bLength = USB_DT_INTERFACE_SIZE,
			.bDescriptorType = USB_DT_INTERFACE,
			.bNumEndpoints = 2,
			.bInterfaceClass = USB_CLASS_VENDOR_SPEC,
			.bInterfaceSubClass = 0x42,
			.bInterfaceProtocol = 0x3,
			.iInterface = 1,
		},
		.ffs_ep_in_desc = {
			.bLength = USB_DT_ENDPOINT_SIZE,
			.bDescriptorType = USB_DT_ENDPOINT,
			.bEndpointAddress = USB_DIR_IN | FFS_EP_ADDR_IN,
			.bmAttributes = USB_ENDPOINT_XFER_BULK,
		},
		.ffs_ep_out_desc = {
			.bLength = USB_DT_ENDPOINT_SIZE,
			.bDescriptorType = USB_DT_ENDPOINT,
			.bEndpointAddress = USB_DIR_OUT | FFS_EP_ADDR_OUT,
			.bmAttributes = USB_ENDPOINT_XFER_BULK,
		},
	},
	.ffs_hs_desc = {
		.ffs_interface = {
			.bLength = USB_DT_INTERFACE_SIZE,
			.bDescriptorType = USB_DT_INTERFACE,
			.bNumEndpoints = 2,
			.bInterfaceClass = USB_CLASS_VENDOR_SPEC,
			.bInterfaceSubClass = 0x42,
			.bInterfaceProtocol = 0x3,
			.iInterface = 1,
		},
		.ffs_ep_in_desc = {
			.bLength = USB_DT_ENDPOINT_SIZE,
			.bDescriptorType = USB_DT_ENDPOINT,
			.bEndpointAddress = USB_DIR_IN | FFS_EP_ADDR_IN,
			.bmAttributes = USB_ENDPOINT_XFER_BULK,
			.wMaxPacketSize = __cpu_to_le16(512),
		},
		.ffs_ep_out_desc = {
			.bLength = USB_DT_ENDPOINT_SIZE,
			.bDescriptorType = USB_DT_ENDPOINT,
			.bEndpointAddress = USB_DIR_OUT | FFS_EP_ADDR_OUT,
			.bmAttributes = USB_ENDPOINT_XFER_BULK,
			.wMaxPacketSize = __cpu_to_le16(512),
		},
	},
};
#endif /* CFG_USB3 */

static const struct {
	struct usb_functionfs_strings_head ffs_string_head;
	struct {
		__le16 id;
		const char zlp[sizeof(FFS_XFL)];
	} __packed ffs_string;
} __packed ffs_strings = {
	.ffs_string_head = {
		.magic = __cpu_to_le32(FUNCTIONFS_STRINGS_MAGIC),
		.length = __cpu_to_le32(sizeof(ffs_strings)),
		.str_count = __cpu_to_le32(1),
		.lang_count = __cpu_to_le32(1),
	},
	.ffs_string = {
		__cpu_to_le16(0x409), FFS_XFL
	}
};

struct transport {
	char *path;
	int fd0;
	int fd_in;
	int fd_out;
};

static void *ffs_ep0_loop(void *handle)
{
	uint8_t buf[EP0_BUF_SIZE];
	struct usb_functionfs_event *ev = (struct usb_functionfs_event *)buf;
	int ret;
	struct pollfd fds;
	struct transport *hdl = (struct transport *)handle;

	FCS_LOG_INF("ep0 thread started\n");

	fds.fd = hdl->fd0;
	fds.events = POLLIN;

	while (1) {
		ret = poll(&fds, 1, -1);

		if (ret < 0) {
			FCS_LOG_ERR("ep0 poll error (%d)\n", errno);
			break;
		}

		if (fds.revents != POLLIN)
			continue;

		ret = read(hdl->fd0, buf, EP0_BUF_SIZE);

		if (ret < 0) {
			FCS_LOG_ERR("ep0 poll error (%d)\n",
				errno);
			break;
		}

		FCS_LOG_INF("ep0 event received, rev %d\n",
			ev->type);
		switch (ev->type) {
		case FUNCTIONFS_ENABLE:
			pthread_mutex_lock(&ffs_mutex);
			pthread_cond_signal(&ffs_enabled);
			pthread_mutex_unlock(&ffs_mutex);
			break;
		case FUNCTIONFS_SETUP:
			if (ev->u.setup.bRequestType & USB_DIR_IN) {
				ret = write(hdl->fd0, NULL, 0);
				if (ret < 0)
					FCS_LOG_ERR("write failed, %d\n", ret);
				else
					FCS_LOG_INF("write reply done\n");
			} else {
				ret = read(hdl->fd0, NULL, 0);
				if (ret < 0)
					FCS_LOG_ERR("read failed, %d\n", ret);
				else
					FCS_LOG_INF("read reply done\n");
			}
			break;
		default:
			break;
		}
	}

	return NULL;
}

struct transport *tr_open(void)
{
	struct transport *hdl = NULL;
	size_t ret, path_size;
	char ep[PATH_MAX] = {0};
	char *path = input_args_get_gadget();

	if (!strlen(path)) {
		FCS_LOG_ERR("usb_open, invalid input, path: %s\n", path);
		return NULL;
	}

	/* Allocate handle */
	hdl = calloc(1, sizeof(struct transport));
	if (!hdl) {
		FCS_LOG_ERR("usb_open calloc handle failed\n");
		return NULL;
	}

	hdl->fd0 = -1;
	hdl->fd_in = -1;
	hdl->fd_out = -1;

	/* Copy gadgetfs device path */
	path_size = strlen(path) + 1;
	hdl->path = calloc(1, path_size);
	if (!hdl->path) {
		FCS_LOG_ERR("usb_open, calloc handle->path failed\n");
		goto fail;
	}
	strlcpy(hdl->path, path, path_size);

	snprintf(ep, sizeof(ep), "%s/ep0", hdl->path);
	hdl->fd0 = open(ep, O_RDWR);
	if (hdl->fd0 < 0) {
		FCS_LOG_ERR("usb_open, open %s/ep0 failed (%d)\n",
			hdl->path, errno);
		goto fail;
	}

	ret = write(hdl->fd0, &ffs_desc, sizeof(ffs_desc));
	if (ret != sizeof(ffs_desc)) {
		FCS_LOG_ERR("usb_open, write desc failed (%d)\n", errno);
		goto fail;
	}

	ret = write(hdl->fd0, &ffs_strings, sizeof(ffs_strings));
	if (ret != sizeof(ffs_strings)) {
		FCS_LOG_ERR("usb_open, write strings failed, r(%d), e(%d)\n",
			ret, errno);
		goto fail;
	}

	pthread_mutex_lock(&ffs_mutex);
	pthread_create(&ep0_thread, 0, ffs_ep0_loop, hdl);

	snprintf(ep, sizeof(ep), "%s/ep%d", path, FFS_EP_ADDR_IN);
	hdl->fd_in = open(ep, O_RDWR);
	if (hdl->fd_in < 0) {
		FCS_LOG_ERR("usb_open, open (%s) failed (%d)\n", ep, errno);
		pthread_mutex_unlock(&ffs_mutex);
		goto fail;
	}

	snprintf(ep, sizeof(ep), "%s/ep%d", path, FFS_EP_ADDR_OUT);
	hdl->fd_out = open(ep, O_RDWR);
	if (hdl->fd_out < 0) {
		FCS_LOG_ERR("usb_open, open (%s) failed (%d)\n", ep, errno);
		pthread_mutex_unlock(&ffs_mutex);
		goto fail;
	}

	if (fcs_prop_set(FCS_PROP_FFS_READY) != FCSERR_OK) {
		FCS_LOG_ERR("Prop set failed\n");
		pthread_mutex_unlock(&ffs_mutex);
		goto fail;
	}

	/*
	 * Wait for ep0 thread to enable
	 */
	pthread_cond_wait(&ffs_enabled, &ffs_mutex);
	pthread_mutex_unlock(&ffs_mutex);

	return hdl;

fail:
	if (hdl->fd0 != -1)
		close(hdl->fd0);

	free(hdl->path);
	free(hdl);

	return NULL;
}

void tr_close(struct transport *hdl)
{
	int ret;

	if (!hdl)
		return;

	if (hdl->fd_in > 0) {
		ret = ioctl(hdl->fd_in, FUNCTIONFS_CLEAR_HALT);
		if (ret < 0)
			FCS_LOG_WRN("usb_close, fd_in clear_halt return %d\n",
				ret);
		close(hdl->fd_in);
		hdl->fd_in = -1;
	}

	if (hdl->fd_out > 0) {
		ret = ioctl(hdl->fd_out, FUNCTIONFS_CLEAR_HALT);
		if (ret < 0)
			FCS_LOG_WRN("usb_close, fd_out clear_halt return %d\n",
				ret);
		close(hdl->fd_out);
		hdl->fd_out = -1;
	}

	if (hdl->fd0 > 0) {
		close(hdl->fd0);
		hdl->fd0 = -1;
	}

	free(hdl->path);
	free(hdl);
}

int tr_read(struct transport *hdl, uint8_t *data_p, size_t size)
{
	int ret = 0;

	FCS_LOG_INF("usb_read, enter (%zd) bytes\n", size);

	if (!hdl) {
		FCS_LOG_ERR("No handle\n");
		return -FCSERR_EINVAL;
	}

	/* Read system call can be interrupted by a signal. */
	do {
		ret = read(hdl->fd_out, data_p, size);
	} while (ret < 0 && errno == EINTR);

	FCS_LOG_INF("usb_read, done - ret (%d)\n", ret);

	if (ret < 0) {
		FCS_LOG_ERR("usb_read failed - ret (%d) errno (%d)\n",
			ret, errno);
		return -FCSERR_EIO;
	} else
		return ret;
}

int tr_write(struct transport *hdl, uint8_t *data_p, size_t size)
{
	int ret = 0;

	FCS_LOG_INF("usb_write, enter (%zd) bytes\n", size);

	if (!hdl) {
		FCS_LOG_ERR("No handle\n");
		return -FCSERR_EINVAL;
	}

	/* Write system call can be interrupted by a signal. */
	do {
		ret = write(hdl->fd_in, data_p, size);
	} while (ret < 0 && errno == EINTR);

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
	return MAX_USB_READ;
}
