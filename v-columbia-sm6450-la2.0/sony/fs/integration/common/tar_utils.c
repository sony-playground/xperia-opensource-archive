/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include "fcslog.h"
#include "fcserr.h"
#include "ab_int.h"
#include "partman.h"
#include "tar_utils.h"

#define CMD2 "dev/block/bootdevice/by-name/"

static char *cmd[] = {"tar", "-xf", NULL, "-C",
	NULL, NULL};

int extract_tar_from_partition(char *target_dir, char *partition)
{
	int res = FCSERR_OK;
	pid_t pid;
	int status;
	bool has_slot = false;
	char active_slot;
	char slot_suffix[] = "_?";
	size_t cmd2_sz;
	size_t cmd4_sz;

	if (target_dir == NULL || partition == NULL) {
		FCS_LOG_ERR("Invalid parameter\n");
		return -FCSERR_EINVAL;
	}

	/* Start building the command for extracting applications */
	res = partman_has_slot(partition, &has_slot);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to check if partition has slot\n");
		goto exit;
	}

	/* Make room for partition name and slot if has_slot is true */
	cmd2_sz = strlen(CMD2) + strlen(partition) +
		((has_slot) ? strlen("_?") : 0) + 1;
	cmd[2] = malloc(cmd2_sz);
	if (!cmd[2]) {
		FCS_LOG_ERR("Out of memory\n");
		res = -FCSERR_ENOMEM;
		goto exit;
	}
	strlcpy(cmd[2], CMD2, cmd2_sz);
	strlcat(cmd[2], partition, cmd2_sz);

	/* Add slot suffix if we have slots */
	if (has_slot) {
		/* Find out which tzxfl to boot */
		res = ab_get_active(&active_slot);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to get active slot\n");
			goto exit;
		}
		slot_suffix[1] = active_slot;
		strlcat(cmd[2], slot_suffix, cmd2_sz);
	}

	cmd4_sz = strlen(target_dir) + 1;
	cmd[4] = malloc(cmd4_sz);
	if (!cmd[4]) {
		FCS_LOG_ERR("Out of memory\n");
		res = -FCSERR_ENOMEM;
		goto exit;
	}
	strlcpy(cmd[4], target_dir, cmd4_sz);

	pid = fork();
	if (pid < 0) {
		FCS_LOG_ERR("Fork failed\n");
		res = -FCSERR_EINVAL;
		goto exit;
	} else if (pid == 0) {
		res = execvp(cmd[0], cmd);
		FCS_LOG_ERR("Failed to untar archive\n");
		res = -FCSERR_EINVAL;
		goto exit;
	} else {
		if ((waitpid(pid, &status, 0) < 0) || WIFSIGNALED(status) ||
				WEXITSTATUS(status) != 0) {
			FCS_LOG_ERR("Bad fuseapp archive.\n");
			res = -FCSERR_EINVAL;
			goto exit;
		}
	}

exit:
	/* Free whole cmd structure */
	free(cmd[2]);
	cmd[2] = NULL;
	free(cmd[4]);
	cmd[4] = NULL;
	return res;
}
