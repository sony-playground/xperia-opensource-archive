/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "linux_util.h"
#include "fcsenv_def.h"
#include "fcsos_def.h"
#include "fcserr.h"
#include "fcslog.h"
#include "protocol_util.h"

#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/wait.h>

#define SMALL_PAGE 0x1000
#define SMALL_PAGE_MASK (SMALL_PAGE - 1)
#define BY_NAME "/dev/block/bootdevice/by-name/"
/* One partition information is 128 Bytes.
 * The number of partitions is passed by sector. The sector is 512 Bytes.
 * Therefore, it is passed in multiples of 4 ( 512 / 128 = 4).
 * The shortage is treated as padding.
 */
#define EMMC_ALIGN_GPT_BLOCK 4


struct emmc_vendors {
	const char *vendor_id;
	const char *vendor_name;
};

static struct emmc_vendors emmc_vendor_table[] = {
	{"0x000015", "SAMSUNG"},
	{"0x00001B", "SAMSUNG"},
	{"0x0001CE", "SAMSUNG"},
	{"0x000090", "HYNIX"},
	{"0x0001AD", "HYNIX"},
	{"0x000013", "MICRON"},
	{"0x0000FE", "MICRON"},
	{NULL, 0}
};

static ssize_t convert_vendor_name(char *name)
{
	struct emmc_vendors *vendors;

	for (vendors = emmc_vendor_table;
		vendors->vendor_id != NULL; vendors++) {
		if (strncmp(vendors->vendor_id, name,
			MIN(strlen(vendors->vendor_id), strlen(name))) == 0) {
			return strlcpy(name, vendors->vendor_name,
					strlen(vendors->vendor_name) + 1);
		}
	}

	return sizeof(name);
}

int fcs_read_memmap(off_t addr, uint8_t *buf, size_t len)
{
	uint8_t *mem;
	int fd;
	size_t pl;

	if (buf == NULL) {
		FCS_LOG_ERR("buffer eq NULL\n");
		return -FCSERR_EINVAL;
	}

	fd = open("/dev/mem", O_RDONLY);
	if (fd == -1) {
		FCS_LOG_ERR("failed to open /dev/mem, errno (%d)\n", errno);
		return -FCSERR_ENXIO;
	}

	pl = ((len + (addr & SMALL_PAGE_MASK)) & ~SMALL_PAGE_MASK) + SMALL_PAGE;

	mem = mmap(NULL, pl, PROT_READ, MAP_SHARED, fd,
		   addr & ~SMALL_PAGE_MASK);
	if (mem == (void *)-1) {
		FCS_LOG_ERR("failed to mmap, errno (%d)\n", errno);
		close(fd);
		return -FCSERR_EIO;
	}

	memcpy(buf, mem + (addr & SMALL_PAGE_MASK), len);

	munmap((void *)mem, pl);
	close(fd);

	return FCSERR_OK;
}

int fcs_read_memmap32(off_t addr, uint32_t *value)
{
	uint8_t *buf32 = (uint8_t *)value;

	return fcs_read_memmap(addr, buf32, sizeof(uint32_t));
}

int fcs_urand(uint8_t *buf, uint16_t len)
{
	int ret;

	if (buf == NULL) {
		FCS_LOG_ERR("Invalid pointer\n");
		return -FCSERR_EINVAL;
	}

	FILE *fd = fopen("/dev/urandom", "r");

	if (!fd) {
		FCS_LOG_ERR("func, open %s failed (%d)\n",
			fd, errno);
		return -FCSERR_ENXIO;
	}

	ret = fread(buf, 1, len, fd);
	if (ret < len) {
		FCS_LOG_ERR("read failed - ret (%d) errno (%d)\n", ret, errno);
		fclose(fd);
		return -FCSERR_EIO;
	}

	fclose(fd);
	return FCSERR_OK;
}

int fcs_srand(unsigned int seed)
{
	int ret;

	FILE *fd = fopen("/dev/urandom", "wb");

	if (!fd) {
		FCS_LOG_ERR("func, fwrite %s failed (%d)\n",
			fd, errno);
		return -FCSERR_ENXIO;
	}

	ret = fwrite(&seed, 1, sizeof(seed), fd);
	if (ret != sizeof(seed)) {
		FCS_LOG_ERR("read failed - ret (%d) errno (%d)\n", ret, errno);
		fclose(fd);
		return -FCSERR_EIO;
	}

	fclose(fd);
	return FCSERR_OK;
}

/*
 * Attempts to read version of USB
 */
int fcs_usb_version(char *buf, ssize_t buf_sz)
{
	int fd, res = FCSERR_OK;
	ssize_t i, bytes_read;

	if (buf_sz < 0 || !buf) {
		FCS_LOG_ERR("Bad input parameters\n");
		return -FCSERR_EINVAL;
	}

	fd = open(BCD_USB, O_RDWR);
	if (fd < 0) {
		FCS_LOG_ERR("Failed to open %s (errno=%d)\n", BCD_USB, errno);
		return -FCSERR_EIO;
	}

	bytes_read = read(fd, buf, buf_sz);
	if (bytes_read < 0) {
		FCS_LOG_ERR("Failed to read version (errno=%d)\n", errno);
		res = -FCSERR_EIO;
		goto exit;
	}

	for (i = 0; i < bytes_read; i++) {
		if (i >= buf_sz - 1) {
			FCS_LOG_ERR("Buffer too small\n");
			res = -FCSERR_ENIMP;
			break;
		}
		if (buf[i] == 0xA)
			break;
	}
	buf[i] = '\0';

exit:
	close(fd);

	return res;
}

/*
 * Read the battery capacity (range: 0-100)
 */
int get_battery_capacity(char *buf, ssize_t buf_sz)
{
	/* Biggest returned string is "100", that is 4 chars (including null) */
	const ssize_t min_buf_size = 4;

	int fd;
	ssize_t bytes_read;

	if (!buf) {
		FCS_LOG_ERR("Bad input parameters\n");
		return -FCSERR_EINVAL;
	}

	if (buf_sz < min_buf_size) {
		FCS_LOG_ERR("Buffer too small\n");
		return -FCSERR_ENOBUFS;
	}

	fd = open(BATTERY_CAPACITY, O_RDONLY);
	if (fd < 0) {
		FCS_LOG_ERR("Failed to open %s (errno=%d)\n",
				BATTERY_CAPACITY, errno);
		return -FCSERR_EIO;
	}

	bytes_read = read(fd, buf, buf_sz);
	if (bytes_read < 2 || bytes_read > 4) {
		FCS_LOG_WRN("Failed to read battery capacity\n");
		strlcpy(buf, "N/A", sizeof("N/A"));
	} else {
		/* Last character returned by read() is '\n'. Should be '\0'. */
		buf[bytes_read - 1] = '\0';
	}

	close(fd);
	return FCSERR_OK;
}

/*
 * Get lun on which a partition resides.
 * lun will contain a string representation of the lun.
 * idx will contain the partition index.
 */
int fcs_get_lun_and_index_of_partition(const char *partition,
		ssize_t partition_sz, char *lun, ssize_t lun_sz, int *idx)
{
	int lun_nbr, res = FCSERR_OK;
	char *path = NULL;
	char *device;
	size_t path_sz;
	char *rpath, *sptr, *eptr;
	char buf[PATH_MAX];
	bool is_emmc;

	if (!partition || !lun || lun_sz != 1 || partition_sz < 1) {
		FCS_LOG_ERR("Invalid input parameters\n");
		return -FCSERR_EINVAL;
	}

	is_emmc = (strncmp(FLASH_TYPE, "eMMC", strlen("eMMC") + 1) == 0);
	if (is_emmc)
		device = DEV_BASE_EMMC;
	else
		device = DEV_BASE_UFS;

	path_sz = strlen(BY_NAME) + strlen(partition) + 1;
	path = malloc(path_sz);
	if (!path) {
		FCS_LOG_ERR("Out of memory\n");
		return -FCSERR_ENOMEM;
	}

	strlcpy(path, BY_NAME, path_sz);
	strlcat(path, partition, path_sz);

	rpath = realpath(path, buf);
	if (!rpath) {
		FCS_LOG_ERR("Failed to get path (errno=%d)\n", errno);
		res = -FCSERR_EINVAL;
		goto exit;
	}

	/* Ensure enough data was read into buf */
	if (strlen(buf) <= strlen(device)) {
		FCS_LOG_ERR("Input value\n");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	/* Is result expected? */
	if (strncmp(buf, device, strlen(device)) != 0) {
		res = -FCSERR_EINVAL;
		FCS_LOG_ERR("Failed to parse lun\n");
		goto exit;
	}

	/*
	 * Convert lower case letter to number.
	 * /dev/block/sda -> 0
	 * /dev/block/sdb -> 1 etc.
	 */
	if (is_emmc)
		lun_nbr = 0;
	else
		lun_nbr = buf[strlen(device)] - 'a';

	snprintf(lun, lun_sz + 1, "%d", lun_nbr);
	lun[lun_sz] = 0;

	/* Get partition index */
	sptr = &buf[strlen(device) + 1];
	*idx = strtol(sptr, &eptr, 10) - 1;
	if (sptr == eptr) {
		FCS_LOG_ERR("Failed to get partition index\n");
		res = -FCSERR_EINVAL;
	}

exit:
	free(path);

	return res;
}

int fcs_get_flash_info_data(const char *file_name,
		struct flash_info_data *fi_data)
{
	int i, fp, res = FCSERR_OK;
	ssize_t data_read;

	if (!file_name || !fi_data) {
		FCS_LOG_ERR("Invalid input parameters\n");
		return -FCSERR_EINVAL;
	}

	fp = open(file_name, O_RDONLY);
	if (fp < 0) {
		FCS_LOG_ERR("Failed to open file\n");
		return -FCSERR_ENOTF;
	}

	data_read = read(fp, fi_data->name, fi_data->buf_size);
	if (data_read < 0) {
		FCS_LOG_ERR("Could not read file\n");
		res = -FCSERR_EIO;
		goto exit;
	}

	if (data_read < fi_data->buf_size)
		fi_data->name[data_read] = '\0';
	else {
		FCS_LOG_ERR("Buffer too small\n");
		res = -FCSERR_ENOBUFS;
		goto exit;
	}

	if ((strncmp(file_name, FLASH_VENDOR, strlen(FLASH_VENDOR) + 1) == 0) &&
		(strncmp((const char *)fi_data->type,
			"eMMC", strlen("eMMC") + 1) == 0)) {
		data_read = convert_vendor_name(fi_data->name);
	}

	for (i = 0; i < data_read; i++) {
		if (i >= fi_data->buf_size) {
			FCS_LOG_ERR("Buffer too small");
			res = -FCSERR_ENIMP;
			goto exit;
		}
		if (fi_data->name[i] == 0x20 || fi_data->name[i] == 0xA)
			break;
		fi_data->buf[i] = fi_data->name[i];
	}

	fi_data->index = i;

exit:
	if (fp != -1)
		close(fp);

	return res;
}

int fcs_wait_partition_rescan(char *name, int nbr_part)
{
	char *partition = NULL;
	int res = FCSERR_OK;
	bool is_ufs;
	char *device;
	char lun[2];
	int retry = 0;
	int cur_part = 0;
	int end_pos;

	if (nbr_part == 0) {
		FCS_LOG_ERR("Bad input parameter: nbr_part == 0\n");
		return -FCSERR_EINVAL;
	}

	is_ufs = (strncmp(FLASH_TYPE, "UFS", strlen("UFS") + 1) == 0);
	if (is_ufs)
		device = DEV_BASE_UFS;
	else
		device = DEV_BASE_EMMC;

	if (is_ufs && !name) {
		FCS_LOG_ERR("This is UFS but name is NULL\n");
		return -FCSERR_EINVAL;
	}

	partition = malloc(PATH_MAX);
	if (!partition) {
		FCS_LOG_ERR("Out of memory\n");
		return -FCSERR_ENOMEM;
	}

	strncpy(partition, device, PATH_MAX);

	for (cur_part = 1; cur_part <= nbr_part; cur_part++) {
		if (is_ufs) {
			lun[0] = atoi(name) + 'a';
			lun[1] = '\0';
			strlcat(partition, lun, PATH_MAX);
			end_pos = strlen(partition);
			snprintf(&partition[end_pos], PATH_MAX - end_pos, "%d",
				cur_part);
		} else {
			end_pos = strlen(partition);
			snprintf(&partition[end_pos], PATH_MAX - end_pos, "p%d",
				cur_part);
		}

		do {
			res = access(partition, F_OK);
			retry++;
			if (retry > RESCAN_MAX_ATTEMPTS) {
				FCS_LOG_ERR(
					"Failed to rescan partition: %s\n",
					partition);
				res = -FCSERR_EIO;
				if (device == DEV_BASE_EMMC) {
					if ( cur_part > ( nbr_part - EMMC_ALIGN_GPT_BLOCK ) ) {
						res = FCSERR_OK;
					}
				}
				goto exit;
			}
			usleep(10000);
		} while (res);

		retry = 0;
		*(partition+strlen(device)) = '\0';
	}

exit:
	free(partition);

	return res;
}

int fcs_exec(char *const cmd[], int timeout)
{
	pid_t pid;
	pid_t tpid;
	pid_t epid;
	int res = FCSERR_OK;
	int status;

	/* fork executable */
	pid = fork();
	if (pid < 0) {
		FCS_LOG_ERR("Fork failed\n");
		return -FCSERR_EINVAL;
	} else if (pid == 0) {
		res = execvp(cmd[0], cmd);
		FCS_LOG_ERR("Failed execute %s\n", cmd[0]);
		_exit(-1);
	}

	/* fork timeout */
	if (timeout) {
		tpid = fork();
		if (tpid < 0) {
			FCS_LOG_ERR("Fork failed\n");
			kill(pid, SIGKILL);
			return -FCSERR_EINVAL;
		} else if (tpid == 0) {
			sleep(timeout);
			_exit(0);
		}
	}

	/* wait for execution to finish */
	while (true) {
		epid = wait(&status);

		if (epid == pid) {
			if (WIFSIGNALED(status) || WEXITSTATUS(status) != 0) {
				FCS_LOG_WRN("Exec failed %s.\n", cmd[0]);
				res = -FCSERR_EINVAL;
			}

			goto exit;
		}

		if (timeout && epid == tpid) {
			FCS_LOG_WRN("Timeout reached %d\n", timeout);
			kill(pid, SIGKILL);
		}
	}
exit:
	return res;
}
