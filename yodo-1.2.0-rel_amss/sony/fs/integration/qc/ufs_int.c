/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "fcslog.h"
#include "fcserr.h"
#include "ufs_int.h"

#include <scsi/ufs/ioctl.h>
#include <scsi/ufs/ufs.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

static int ufs_ioctl_get_descriptor(int fd, void *buf, size_t buf_sz,
		uint8_t descriptor, int descriptor_len)
{
	int ret = FCSERR_OK;
	struct ufs_ioctl_query_data *query = NULL;

	query = malloc(sizeof(struct ufs_ioctl_query_data) + buf_sz);
	if (query == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		return -FCSERR_ENOMEM;
	}

	query->opcode = UPIU_QUERY_OPCODE_READ_DESC;
	query->buf_size = descriptor_len;
	query->idn = descriptor;

	ret = ioctl(fd, UFS_IOCTL_QUERY, query);
	if (ret < 0) {
		FCS_LOG_ERR("UFS ioctl query fail (%d, %s)\n",
				ret,  strerror(errno));
		goto exit;
	}
	memcpy(buf, query->buffer, buf_sz);

exit:
	if (query)
		free(query);
	return ret;
}

int ufs_ioctl_get_unit_desc(int fd, void *buf, size_t buf_sz)
{
	return ufs_ioctl_get_descriptor(fd, buf, buf_sz,
			QUERY_DESC_IDN_UNIT, UNIT_DESCRIPTOR_LEN);
}

int ufs_ioctl_get_device_desc(int fd, void *buf, size_t buf_sz)
{
	return ufs_ioctl_get_descriptor(fd, buf, buf_sz,
			QUERY_DESC_IDN_DEVICE, DEVICE_DESCRIPTOR_LEN);
}

int ufs_ioctl_purge(int fd)
{
#ifdef CFG_STUB_UFS_PURGE
	(void)fd; /* Avoid warning about unused parameter */
	FCS_LOG_ERR("UFS purge is not implemented\n");
	return FCSERR_OK;
#else
	int ret = FCSERR_OK;
	struct ufs_ioctl_query_data *idata;

	idata = malloc(sizeof(struct ufs_ioctl_query_data) +
			4 * sizeof(unsigned char));
	if (!idata) {
		FCS_LOG_ERR("failed to allocate memory for purge\n");
		ret = -FCSERR_ENOMEM;
		goto exit;
	}

	idata->opcode = UPIU_QUERY_OPCODE_SET_FLAG;
	idata->idn = QUERY_FLAG_IDN_PURGE_ENABLE;
	idata->buf_size = 0;
	ret = ioctl(fd, UFS_IOCTL_QUERY, idata);
	if (ret) {
		FCS_LOG_ERR("failed to enable purge (%d, %s)\n",
				ret,  strerror(errno));
		goto exit;
	}

	while (1) {
		idata->opcode = UPIU_QUERY_OPCODE_READ_ATTR;
		idata->idn = QUERY_ATTR_IDN_PURGE_STATUS;
		idata->buf_size = 4;
		ret = ioctl(fd, UFS_IOCTL_QUERY, idata);
		if (ret) {
			FCS_LOG_ERR("failed to read purge status (%d, %s)\n",
					ret,  strerror(errno));
			break;
		}

		switch (idata->buffer[0]) {
		case PURGE_STATUS_IDLE:
			goto exit;
		case PURGE_STATUS_IN_PROGRESS:
			break;
		case PURGE_STATUS_STOPPED:
			FCS_LOG_ERR("purge failed due to interruption\n");
			ret = -FCSERR_EAGAIN;
			goto exit;
		case PURGE_STATUS_COMPLETED:
			FCS_LOG_INF("purge completed\n");
			goto exit;
		case PURGE_STATUS_BUSY:
			FCS_LOG_ERR("purge failed due to busy\n");
			sleep(5);
			ret = -FCSERR_EBUSY;
			goto exit;
		case PURGE_STATUS_GENERAL_ERROR:
			FCS_LOG_ERR("purge failed due to general error\n");
			ret = -FCSERR_EIO;
			goto exit;
		default:
			FCS_LOG_ERR("purge failed due to unknown error\n");
			ret = -FCSERR_EINVAL;
			goto exit;
		}
		sleep(1);
	}

exit:
	if (idata)
		free(idata);
	return ret;
#endif
}

int ufs_ioctl_set_bootdevice(int fd, int lun)
{
	int res = FCSERR_OK;
	struct ufs_ioctl_query_data *query = NULL;
	size_t query_size = sizeof(struct ufs_ioctl_query_data) +
		UFS_ATTR_DATA_SIZE;

	query = (struct ufs_ioctl_query_data *)malloc(query_size);
	if (!query) {
		FCS_LOG_ERR("Out of memory\n");
		return -FCSERR_ENOMEM;
	}

	query->idn = QUERY_ATTR_IDN_BOOT_LU_EN;
	query->buf_size = UFS_ATTR_DATA_SIZE;
	query->opcode = UPIU_QUERY_OPCODE_READ_ATTR;
	query->buffer[0] = 0;

	if (ioctl(fd, UFS_IOCTL_QUERY, query)) {
		FCS_LOG_ERR("ioctl(%d, UFS_IOCTL_QUERY) failed:%s\n",
				fd, strerror(errno));
		res = -FCSERR_EIO;
		goto exit;
	}

	/* Set well known lun */
	query->opcode = UPIU_QUERY_OPCODE_WRITE_ATTR;
	query->buffer[0] = lun;

	if (ioctl(fd, UFS_IOCTL_QUERY, query)) {
		FCS_LOG_ERR("ioctl(%d, UFS_IOCTL_QUERY) failed:%s\n",
				fd, strerror(errno));
		res = -FCSERR_EIO;
		goto exit;
	}

exit:
	if (query)
		free(query);
	return res;
}
