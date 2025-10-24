/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

/*
 * Implements protocol.h
 */

/* Uncomment to measure fastboot command execution time */
/* NOTE: USB transfer time is not included */
/* #define CFG_FASTBOOT_MEASURE_TIME */

#include "protocol.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "fcserr.h"
#include "transport.h"
#include "ta_interface.h"
#include "fcslog.h"
#include "storage.h"
#include "write_image.h"
#include "fcslist.h"
#include "ta_interface.h"
#include "power.h"
#include "partman.h"
#include "protocol_util.h"
#include "security_properties.h"
#include "fcsenv.h"
#include "fcsenv_def.h"
#include "fcs_defines.h"
#include "convert.h"
#include "rule_rootcert.h"
#include "rule_verifier.h"
#include "cms_verifier.h"
#include "loader.h"
#include "safe_boot.h"
#include <eroot.h>
#include <core.h>
#include "authenticate.h"
#include <ks.h>
#include <ks_util.h>
#include "transport_verifier.h"
#include "uevent_handler.h"
#include "rooting_status.h"
#include "auth_ch.h"
#include "digest_types.h"
#include "sec_data_utils.h"
#include "xflattest_int.h"
#include "ab_int.h"
#include "fcs_fastboot_partitions.h"
#include <inttypes.h>
#include "flash_handler.h"
#include "fcsgfx.h"
#include "fcslog_ta.h"
#include "fcs_prop.h"

#ifdef CFG_FASTBOOT_MEASURE_TIME
#include <time.h>
#endif

#define FASTBOOT_BUFFER_SIZE 64
#define MAX_DLS (100*1024*1024L)
#define FB_PART_LIST_SIZE (64 * 1024L)
#define FB_MAX_DUMP_SIZE (2048*1024*1024LL)

/*
 * This constant is used for the size of the variable value in handle_getvar().
 * We subtract with 4 because each response begins with "OKAY", "INFO", "FAIL"
 * or "DATA".
 * We add 1 to the size to be able to handle null terminated strings in the
 * variable value. (When the fastboot buffer is sent over USB and the buffer
 * is full, then it does not need to be null terminated.)
 */
#define GETVAR_VALUE_SIZE (FASTBOOT_BUFFER_SIZE - 4 + 1)

#define FB_VERSION "0.4"
#define FB_SONY_VERSION "0.54"

#define BOOT_MAGIC "bootloader"

#define FASTBOOT_TMP_STORAGE STORAGE_HEAP_NAME

#define MAX_RETRY_COUNT 5

static unsigned int get_max_download_size(void);
static int prot_receive_data(struct protocol *ctx);
static int prot_send_data(struct protocol *ctx, uint8_t *buf, uint32_t size);
static int handle_flash(struct loader_ctx *ldr_ctx);
static int handle_download(struct loader_ctx *ldr_ctx);
static int handle_getvar(struct loader_ctx *ldr_ctx);
static int handle_format_ta(struct loader_ctx *ldr_ctx);
static int handle_read_ta(struct loader_ctx *ldr_ctx);
static int handle_read_all_ta(struct loader_ctx *ldr_ctx);
static int handle_reboot(struct loader_ctx *ldr_ctx);
static int handle_continue(struct loader_ctx *ldr_ctx);
static int handle_write_ta(struct loader_ctx *ldr_ctx);
static int handle_oem_unlock(struct loader_ctx *ldr_ctx);
static int handle_oem_lock(struct loader_ctx *ldr_ctx);
static int handle_notsupported(struct protocol *ctx);
static int hex2uint(const char *in, unsigned int *out);
static int write_to_flash(struct protocol *ctx, const char *partition);
static int handle_signature(struct loader_ctx *ldr_ctx);
static int handle_signature_download(struct loader_ctx *ldr_ctx);
static int fb_gpt_sanity_check(struct protocol *ctx, const char *lun,
		int *nbr_part);
static int fb_prepare_secondary_table(struct protocol *ctx, const char *lun);
static int fb_patch_primary_table(struct protocol *ctx, const char *lun);
static void write_to_flash_final(struct protocol *ctx);
static int devid_to_buffer(struct protocol *ctx,
		uint8_t **outbuf, size_t *outbuf_len);
static int write_to_buffer(struct protocol *ctx,
		uint8_t **outbuf, size_t *outbuf_len);
static int handle_gptinfo(struct loader_ctx *ldr_ctx);
static int handle_digest(struct loader_ctx *ldr_ctx);
static int handle_getstorageinfo(struct loader_ctx *ldr_ctx);
static int handle_getrootkeyhash(struct loader_ctx *ldr_ctx);
static int handle_set_security(struct loader_ctx *ldr_ctx);
static int handle_get_security(struct loader_ctx *ldr_ctx);
static int handle_challenge(struct loader_ctx *ldr_ctx);
static int handle_response(struct loader_ctx *ldr_ctx);
static int handle_charge(struct loader_ctx *ldr_ctx);
static int handle_set_ship_mode(struct loader_ctx *ldr_ctx);
static int handle_enable_display(struct loader_ctx *ldr_ctx);
static int handle_disable_display(struct loader_ctx *ldr_ctx);
static int fastboot_add_cmd(const char *name,
		int (*func)(struct loader_ctx *ldr_ctx), uint8_t auth_level);
static int extract_partition_and_unit(const uint8_t *arg,
		uint8_t *partition, uint32_t *unit);
static int parse_args(const char *args,
		int *lun, ssize_t *start, ssize_t *end);
static int erase(struct protocol *ctx);
static int fastboot_get_has_slot(const char *partition, char *val);
static int fastboot_get_partition_size(const char *partition, char *val);
static int fastboot_get_partition_type(const char *partition, char *val);
static int fastboot_get_rollback_counter(const char *index, char *val);
static bool is_bootloader(const char *partition);
static char *get_string_arg_from_cmd(const char *cmd_name, const uint8_t *cmd);
static int get_partition_list(struct protocol *ctx, uint8_t *ptn_list,
		size_t *len);
static int list_has_slot_in_getvar_all(struct protocol *ctx);
static int list_rollback_index_in_getvar_all(struct protocol *ctx);
static int list_partition_info_in_getvar_all(struct protocol *ctx);
static int is_slot(const char *part, bool *part_is_slot);
static int sync_and_purge(struct protocol *ctx);
static int sync_powerdown(struct protocol *ctx);
static void set_purge(struct protocol *ctx, bool do_purge);

#define FB_GEN_RESP(ctx, msg, args...)					\
	snprintf((char *)((ctx)->resp), FASTBOOT_BUFFER_SIZE + 1, msg, ##args)


/* Fastboot commands */
const char *CMD_GETVAR = "getvar:";
const char *CMD_DOWNLOAD = "download:";
const char *CMD_FLASH = "flash:";
const char *CMD_FORMAT_TA = "Format-TA:";
const char *CMD_READ_TA = "Read-TA:";
const char *CMD_READ_ALL_TA = "Read-all-TA:";
const char *CMD_WRITE_TA = "Write-TA:";
const char *CMD_POWERDOWN = "powerdown";
const char *CMD_REBOOT = "reboot";
const char *CMD_CONTINUE = "continue";
const char *CMD_REBOOT_BOOTLOADER = "reboot-bootloader";
const char *CMD_REBOOT_VENDOR_BOOTLOADER = "Reboot-bootloader";
const char *CMD_REBOOT_RECOVERY = "reboot-recovery";
const char *CMD_REBOOT_FASTBOOT = "reboot-fastboot";
const char *CMD_ERASE = "erase:";
const char *CMD_SECURE_ERASE = "Secure-erase:";
const char *CMD_ERASE_SECTOR = "Erase-sector:";
const char *CMD_SECURE_ERASE_SECTOR = "Secure-erase-sector:";
const char *CMD_READ_PARTITION = "Read-partition:";
const char *CMD_READ_SECTOR = "Read-sector:";
const char *CMD_GET_PARTITION_LIST = "Get-partition-list";
const char *CMD_REPARTITION = "Repartition"; /* Repartition with dl binary */
const char *CMD_GETLOG = "Getlog"; /* Sends log file if there is one */
const char *CMD_GETNVLOG = "Getnvlog"; /* Sends log file from nv memory */
const char *CMD_DIGEST = "Digest:";
const char *CMD_SIGNATURE_DL = "signature:";
const char *CMD_SIGNATURE = "signature";
const char *CMD_SET_SECURITY = "Set-security";
const char *CMD_GPTINFO = "Get-gpt-info";
const char *CMD_GETUFSINFO = "Get-ufs-info";
const char *CMD_GETEMMCINFO = "Get-emmc-info";
const char *CMD_SAKE_CHALLENGE = "SAKE-Authenticate:challenge";
const char *CMD_SAKE_RESPONSE = "SAKE-Authenticate:response";
const char *CMD_GETROOTKEYHASH = "Get-root-key-hash";
const char *CMD_CHARGE = "Charge:";
const char *CMD_OEM_UNLOCK = "oem unlock";
const char *CMD_OEM_LOCK = "oem lock";
const char *CMD_SYNC = "Sync";
const char *CMD_SET_ACTIVE = "set_active";
const char *CMD_RESET_ROLLBACK_COUNTER = "Reset-rollback-counter";
const char *CMD_RESET_FRP = "Reset-frp";
const char *CMD_SET_SHIP_MODE = "Set-ship-mode";
const char *CMD_ENABLE_DISPLAY = "Enable-display";
const char *CMD_DISABLE_DISPLAY = "Disable-display";

const char *VIRTPART_REPART = "partitionimage";
const char *DUMP_APPSLOG = "Read-partition:appslog";

#define FB_PARSE_CMD(s, c)						\
	((strlen(s) <= strlen((const char *)c) &&			\
	  (memcmp(c, s, strlen(s)) == 0)))

struct protocol {
	struct transport *tr_hdl; /* transport handle */
	uint8_t cmd[FASTBOOT_BUFFER_SIZE+1];
	uint8_t resp[FASTBOOT_BUFFER_SIZE+1];
	unsigned int data_left;
	struct storage_ctx *sctx;
	int erase_type;
	bool do_purge;
};

struct fastboot_variable_entry {
	char *name;
	int (*get_value)(char *val);
	struct list_entry list;
};

struct fastboot_command_entry {
	char *name;
	int (*handle)(struct loader_ctx *ldr_ctx);
	uint8_t auth_level;
	struct list_entry list;
};

struct cms_valid_sin_entry {
	char *part_name;
	struct transport_verifier *transport_handle;
	struct list_entry list;
};

static LIST(fastboot_var_list);
static LIST(fastboot_cmd_list);
static LIST(cms_valid_sin);

static int reset_slot_parameters(char *pname)
{
	int res;
	bool partition_is_slot;

	res = is_slot(pname, &partition_is_slot);
	if (res) {
		FCS_LOG_ERR("Failed to do slot check\n");
		return res;
	}

	/* If the partition is not a slot-partition skip this step */
	if (partition_is_slot) {
		char slot[] = "x";

		slot[0] = pname[strlen(pname) - 1];
		res = ab_reset_slot(slot);
		if (res) {
			FCS_LOG_ERR("Failed to reset slot: %d\n", res);
			return res;
		}
	}

	return FCSERR_OK;
}

static bool is_bootloader(const char *partition)
{
	int res;
	size_t slot_count, plen, mlen;

	if (!partition) {
		FCS_LOG_ERR("Invalid argument\n");
		return false;
	}

	plen = strlen(partition);
	mlen = strlen(BOOT_MAGIC);

	res = partman_get_slot_count(&slot_count);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get slot\n");
		return false;
	}

	/*
	 * If platform has no slots the only possibility for this being the
	 * bootloader is if partition == BOOT_MAGIC.
	 */
	if (!slot_count && !strncmp(partition, BOOT_MAGIC, plen + 1))
		return true;

	/* Looking for <BOOT_MAGIC>_a or <BOOT_MAGIC>_b */
	if (slot_count == 2 && plen == mlen + strlen("_?")) {
		/* Check if partition == BOOT_MAGIC except slot suffix */
		if (!strncmp(partition, BOOT_MAGIC, mlen)) {
			/* Now check the slot suffix */
			if (partition[plen - 2] == '_' &&
					(partition[plen - 1] == 'a' ||
					 partition[plen - 1] == 'b'))
				return true;
		}
	}

	return false;
}

static int verify_download_sha256(struct transport_verifier *transport_handle)
{
	int res = FCSERR_OK;
	struct storage_ctx *rdctx = NULL;
	uint8_t *buf = NULL;
	ssize_t buf_size, bytes_read, bytes_left;
	struct digest *dgst = NULL;
	uint8_t *hash;
	uint32_t hash_len;

	if (!transport_handle) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	rdctx = storage_open_by_name(FASTBOOT_TMP_STORAGE,
					STORAGE_RAMDISK_NAME);
	if (!rdctx) {
		FCS_LOG_ERR("Unable to open ramdisk file %s\n",
				STORAGE_RAMDISK_NAME);
		return -FCSERR_EINVAL;
	}

	bytes_left = pu_get_part_size(rdctx);
	if (bytes_left < 0) {
		FCS_LOG_ERR("IO Error\n");
		res = -FCSERR_EIO;
		goto verify_download_end;
	}

	buf_size = (bytes_left < get_max_download_size()) ?
		bytes_left : get_max_download_size();
	buf = malloc(buf_size);
	if (buf == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		res = -FCSERR_ENOMEM;
		goto verify_download_end;
	}

	res = digest_sha256_init(&dgst);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR(
			"Fail to init download hash\n");
		goto verify_download_end;
	}

	do {
		bytes_read = storage_read(rdctx, buf, buf_size);
		if (bytes_read < 0) {
			FCS_LOG_ERR("Read fail\n");
			res = -FCSERR_EIO;
			goto verify_download_end;
		}

		res = digest_sha256_update(dgst, buf, buf_size);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR(
				"Fail to calculate download hash\n");
			goto verify_download_end;
		}

		bytes_left -= bytes_read;
	} while (bytes_left);

	res = digest_sha256_final(dgst, &hash, &hash_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR(
			"Fail to finalize download hash\n");
		goto verify_download_end;
	}

	res = transport_verify_hash(transport_handle, hash, hash_len);

verify_download_end:
	free(buf);
	digest_sha256_deinit(dgst);
	storage_close(rdctx);
	return res;
}

/*
 * if part has slots part_is_slot will be true, otherwise false.
 */
static int is_slot(const char *part, bool *part_is_slot)
{
	size_t plen;

	if (!part || !part_is_slot) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	*part_is_slot = false;

	plen = strlen(part);
	if (plen < 3 || plen > PATH_MAX) {
		/* No room for slots */
		return FCSERR_OK;
	}

	if (part[plen - 2] == '_' &&
			(part[plen - 1] == 'a' || part[plen - 1] == 'b'))
		*part_is_slot = true;

	return FCSERR_OK;
}

static int remove_auth_partition(const char *part)
{
	struct cms_valid_sin_entry *sin;
	bool part_is_slot;
	int res;

	if (!part) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	res = is_slot(part, &part_is_slot);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Bad input parameters\n");
		return res;
	}

	LIST_FOR_EACH_DATA(&cms_valid_sin, sin, list) {
		if (part_is_slot) {
			/* Remove partition without slot from list */
			if (!strncmp(part, sin->part_name, strlen(part) - 2))
				list_remove(&sin->list);
			/* Remove partition including slot from list */
			if (!strncmp(part, sin->part_name, strlen(part) + 1))
				list_remove(&sin->list);
		} else {
			if (!strncmp(part, sin->part_name, strlen(part) + 1))
				list_remove(&sin->list);
		}

	}

	return FCSERR_OK;
}

static int add_auth_partition(const char *name,
		struct transport_verifier *transport_handle)
{
	struct cms_valid_sin_entry *ent;
	size_t part_name_size;

	if (!name) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ent = malloc(sizeof(struct cms_valid_sin_entry));
	if (!ent) {
		FCS_LOG_ERR("Unable to allocate memory\n");
		return -FCSERR_ENOMEM;
	}

	part_name_size = strlen(name) + 1;
	ent->part_name = malloc(part_name_size);

	if (!ent->part_name) {
		free(ent);
		FCS_LOG_ERR("Unable to allocate memory\n");
		return -FCSERR_ENOMEM;
	}

	strlcpy(ent->part_name, name, part_name_size);
	ent->transport_handle = transport_handle;

	list_add_tail(&cms_valid_sin, &ent->list);

	return FCSERR_OK;
}

/*
 * Extract the argument from the command:
 * E g: <cmd>:<arg>
 * Return empty string if there is no <arg> in the command
 */
static char *get_string_arg_from_cmd(const char *cmd_name, const uint8_t *cmd)
{
	char *str = NULL;
	size_t str_len;

	if (!cmd_name || !cmd) {
		FCS_LOG_ERR("Invalid argument\n");
		return NULL;
	}

	/* Make sure we parse the right command */
	if (strncmp(cmd_name, (char *)cmd, strlen(cmd_name)))
		return NULL;
	/* Are there arguments after the command? */
	if (strlen((char *)cmd) >= strlen(cmd_name))
		str_len = strlen((char *)cmd) - strlen(cmd_name);
	else {
		FCS_LOG_ERR("Input value fail\n");
		return NULL;
	}

	/* Allocate argument string and copy argument to it */
	str = (char *)malloc(str_len + 1);
	if (str == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		return NULL;
	}

	strlcpy(str, (char *)cmd+strlen(cmd_name),
			str_len + 1);

	/* Get rid of the ':' if there is one */
	if (str[0] == ':')
		strlcpy(str, &str[1], str_len + 1);

	return str;
}

static int is_partition_allowed(const char *cmspart,
				const char *part,
				bool *allowed)
{
	size_t cms_len, part_len;

	*allowed = false;

	if (!part || !cmspart) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	cms_len = strlen(cmspart);
	part_len = strlen(part);

	/* Complete match? */
	if ((cms_len == part_len) &&
		(!strncmp(cmspart, part, cms_len))) {
		*allowed = true;
		return FCSERR_OK;
	}

	/* Check if cmspart is <partition> (without slot suffix)
	 * and if part contains slot suffix
	 * (<partition>_a or <partition>_b)
	 */
	if (((cms_len + strlen("_?")) == part_len) &&
			!strncmp(cmspart, part, cms_len)) {
		/* Check for correct slot suffix */
		if ((part[part_len - 2] == '_') &&
			(part[part_len - 1] == 'a' ||
			part[part_len - 1] == 'b')) {
			*allowed = true;
		}
	}

	return FCSERR_OK;
}

static int check_cmd_auth(struct loader_ctx *ldr_ctx,
		struct fastboot_command_entry *cmd,
		bool *cmd_authenticated)
{
	char *cmdarg = NULL;
	char *partition = NULL;
	bool allowed;
	bool found_part = false;
	bool is_restricted = true;
	uint8_t ta_partition = 0;
	uint32_t unit = 0;
	int res = FCSERR_OK;
	struct cms_valid_sin_entry *sin;
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl || !cmd || !cmd_authenticated) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	*cmd_authenticated = false;

	/*
	 * Read and write to High MiscTA units should not
	 * be allowed if not authenticated.
	 */
	if (FB_PARSE_CMD(CMD_READ_TA, ctx->cmd)) {
		res = extract_partition_and_unit(
			&ctx->cmd[strlen(CMD_READ_TA)],
			&ta_partition, &unit);
	} else if (FB_PARSE_CMD(CMD_WRITE_TA,
			ctx->cmd)) {
		res = extract_partition_and_unit(
			&ctx->cmd[strlen(CMD_WRITE_TA)],
			&ta_partition, &unit);
	}

	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Fail to extract partition and/or unit");
		return res;
	}

	if ((ta_partition == TA_MISC_PART) &&
		(unit > MISC_TA_MAX_PUBLIC_UNIT_ID) &&
		(ldr_ctx->auth_level != AUTH_LEVEL_PRODUCTION)) {
		*cmd_authenticated = false;
		return FCSERR_OK;
	}

	if ((cmd->auth_level == AUTH_LEVEL_NONE) ||
		cmd->auth_level == ldr_ctx->auth_level) {
		*cmd_authenticated = true;
	}

	if (FB_PARSE_CMD(CMD_ERASE, ctx->cmd)) {
		partition = get_string_arg_from_cmd(CMD_ERASE, ctx->cmd);
		found_part = true;
	} else if (FB_PARSE_CMD(CMD_FLASH, ctx->cmd)) {
		partition = get_string_arg_from_cmd(CMD_FLASH, ctx->cmd);
		found_part = true;
	} else if (FB_PARSE_CMD(CMD_SECURE_ERASE, ctx->cmd)) {
		partition = get_string_arg_from_cmd(CMD_SECURE_ERASE, ctx->cmd);
		found_part = true;
	} else if (FB_PARSE_CMD(CMD_REPARTITION, ctx->cmd)) {
		cmdarg = get_string_arg_from_cmd(CMD_REPARTITION, ctx->cmd);
		if (cmdarg == NULL) {
			FCS_LOG_ERR("Out of memory\n");
			return -FCSERR_ENOMEM;
		}
		partition = (char *)malloc(
			strlen(VIRTPART_REPART) + strlen(cmdarg) + 2);
		if (partition == NULL) {
			FCS_LOG_ERR("Out of memory\n");
			return -FCSERR_ENOMEM;
		}
		strlcpy(partition,
			VIRTPART_REPART,
			strlen(VIRTPART_REPART) + strlen(cmdarg) + 2);
		if (strlen(cmdarg) > 0) {
			strlcat(partition,
				":",
				strlen(VIRTPART_REPART) + strlen(cmdarg) + 2);
			strlcat(partition,
				cmdarg,
				strlen(VIRTPART_REPART) + strlen(cmdarg) + 2);
		}
		found_part = true;
	} else if (FB_PARSE_CMD(DUMP_APPSLOG, ctx->cmd)) {
		/* Reading apps_log partition does not require authentication */
		*cmd_authenticated = true;
		return FCSERR_OK;
	} else if (FB_PARSE_CMD(CMD_RESET_ROLLBACK_COUNTER, ctx->cmd)) {
		if (ldr_ctx->auth_level == AUTH_LEVEL_PRODUCTION)
			*cmd_authenticated = true;
	} else if (FB_PARSE_CMD(CMD_RESET_FRP, ctx->cmd)) {
		if (ldr_ctx->auth_level == AUTH_LEVEL_PRODUCTION)
			*cmd_authenticated = true;
	}

	/*
	 * Check if the transport signature for the partition
	 * is verified, cms_valid_sin should contain all partition
	 * names for which the transport signature was verified
	 * in the signature command.
	 */
	if (found_part) {
		if (partition == NULL) {
			FCS_LOG_ERR("Input value fail\n");
			return -FCSERR_EINVAL;
		}

		/* We should always allow to flash/erase a new keystore without
		 * verification. Only allow flashing xflkeystore partition,
		 * not bak partition.
		 */
		if ((FB_PARSE_CMD(CMD_FLASH, ctx->cmd) ||
				FB_PARSE_CMD(CMD_ERASE, ctx->cmd)) &&
				strncmp(partition, "xflkeystore",
					sizeof("xflkeystore")) == 0) {
			*cmd_authenticated = true;
			res = FCSERR_OK;
			goto exit;
		}

		/* If the bootloader is unlocked allow flashing or erasing
		 * any partition without restriction as long as the device
		 * is unfused. But if the device is fused, allow flashing or
		 * erasing only platform specific selected partitions.
		 */
		if ((FB_PARSE_CMD(CMD_FLASH, ctx->cmd) ||
			FB_PARSE_CMD(CMD_ERASE, ctx->cmd))) {
			res = is_partition_restricted(partition,
							&is_restricted);
			if (res == FCSERR_OK && !is_restricted) {
				*cmd_authenticated = true;
				res = FCSERR_OK;
			}
		}

		LIST_FOR_EACH_DATA(&cms_valid_sin, sin, list) {
			res = is_partition_allowed(sin->part_name,
					partition,
					&allowed);
			if (res == FCSERR_OK) {
				if (!allowed)
					continue;
			} else {
				goto exit;
			}

			/*
			 * FLASH and REPARTITION has downloaded content
			 * which should be verified.
			 */
			if (FB_PARSE_CMD(CMD_FLASH, ctx->cmd) ||
				FB_PARSE_CMD(CMD_REPARTITION, ctx->cmd)) {
				res = verify_download_sha256(
					sin->transport_handle);
				if (res != FCSERR_OK) {
					list_remove(&sin->list);
					free(sin->part_name);
					transport_deinit(sin->transport_handle);
					free(sin);

					FCS_LOG_ERR(
					"Fail to verify download\n");
					break;
				}
				if (!transport_has_more(
						sin->transport_handle)) {
					list_remove(&sin->list);
					free(sin->part_name);
					transport_deinit(sin->transport_handle);
					free(sin);
				}
			}
			*cmd_authenticated = true;
			break;
		}
	}

exit:
	/*
	 * If something went wrong, remove authenticated state. For instance
	 * if a hash verification fails it should not allow flashing of file
	 * even if you are authenticated.
	 */
	if (res)
		*cmd_authenticated = false;

	free(cmdarg);
	free(partition);

	return res;
}
static int handle_powerdown(struct loader_ctx *ldr_ctx)
{
	int ret;
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	FCS_LOG_INF("Shutdown device\n");

	/* make sure that all data is written to flash */
	write_to_flash_final(ctx);

	ret = sync_powerdown(ctx);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Sync failed (%d)\n", ret);
		FB_GEN_RESP(ctx, "FAILSync failed");
		return ret;
	}

	/* send ok that we have received cmd */
	FB_GEN_RESP(ctx, "OKAY");
	(void)prot_send_response(ctx);

	/* Leave the display content on*/
	ret = fcsgfx_deinit(false);
	if (ret != FCSERR_OK)
		FCS_LOG_ERR("fcsgfx_deinit failed (%d)\n", ret);

	ret = power_shutdown(POWER_SHUTDOWN_ON_USB_REMOVAL);
	/*
	 * If something failed device will not power down. In this case we
	 * return to fastboot protocol.
	 */
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Shutdown failed (%d)\n", ret);
		FB_GEN_RESP(ctx, "FAILShutdown");
		return ret;
	}

	exit(0);
}

static int handle_reboot_bootloader(struct loader_ctx *ldr_ctx)
{
	int ret = FCSERR_OK;
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	FCS_LOG_INF("Reboot bootloader\n");

	/* make sure that all data is written to flash */
	write_to_flash_final(ctx);

	ret = sync_powerdown(ctx);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Sync failed (%d)\n", ret);
		FB_GEN_RESP(ctx, "FAILSync failed");
		return ret;
	}

	/* send ok that we have received cmd */
	FB_GEN_RESP(ctx, "OKAY");
	(void)prot_send_response(ctx);

	ret = power_shutdown(POWER_REBOOT_XFL);
	if (ret != FCSERR_OK)
		goto exit_reboot_bootloader;

	exit(0);
exit_reboot_bootloader:
	/*
	 * If something failed device will not power down. In this case we
	 * return to fastboot protocol.
	 */
	FCS_LOG_ERR("reboot-bootloader failed (%d)\n", ret);
	FB_GEN_RESP(ctx, "FAILreboot-bootloader");
	return ret;
}

static int handle_reboot_vendor_bootloader(struct loader_ctx *ldr_ctx)
{
	int ret = FCSERR_OK;
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	FCS_LOG_INF("Reboot vendor bootloader\n");

	/* make sure that all data is written to flash */
	write_to_flash_final(ctx);

	ret = sync_powerdown(ctx);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Sync failed (%d)\n", ret);
		FB_GEN_RESP(ctx, "FAILSync failed");
		return ret;
	}

	/* send ok that we have received cmd */
	FB_GEN_RESP(ctx, "OKAY");
	(void)prot_send_response(ctx);

	ret = power_shutdown(POWER_REBOOT_FASTBOOT);
	if (ret != FCSERR_OK)
		goto exit_reboot_vendor_bootloader;

	exit(0);
exit_reboot_vendor_bootloader:
	/*
	 * If something failed device will not power down. In this case we
	 * return to fastboot protocol.
	 */
	FCS_LOG_ERR("Reboot-bootloader failed (%d)\n", ret);
	FB_GEN_RESP(ctx, "FAILReboot-bootloader");
	return ret;
}

static int handle_reboot_recovery(struct loader_ctx *ldr_ctx)
{
	int ret = FCSERR_OK;
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	FCS_LOG_INF("Reboot to recovery \n");

	/* make sure that all data is written to flash */
	write_to_flash_final(ctx);

	ret = sync_powerdown(ctx);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Sync failed (%d)\n", ret);
		FB_GEN_RESP(ctx, "FAILSync failed");
		return ret;
	}

	/* send ok that we have received cmd */
	FB_GEN_RESP(ctx, "OKAY");
	(void)prot_send_response(ctx);

	ret = power_shutdown(POWER_REBOOT_RECOVERY);
	if (ret != FCSERR_OK)
		goto exit_reboot_vendor_bootloader;

	exit(0);
exit_reboot_vendor_bootloader:
	/*
	 * If something failed device will not power down. In this case we
	 * return to fastboot protocol.
	 */
	FCS_LOG_ERR("Reboot-recovery failed (%d)\n", ret);
	FB_GEN_RESP(ctx, "FAILReboot-recovery");
	return ret;
}

static int handle_reboot_fastboot(struct loader_ctx *ldr_ctx)
{
	return handle_reboot_recovery(ldr_ctx);
}

static int handle_reboot(struct loader_ctx *ldr_ctx)
{
	int ret = FCSERR_OK;
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	FCS_LOG_INF("Reboot device\n");

	/* make sure that all data is written to flash */
	write_to_flash_final(ctx);

	ret = sync_powerdown(ctx);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Sync failed (%d)\n", ret);
		FB_GEN_RESP(ctx, "FAILSync failed");
		return ret;
	}

	/* send ok that we have received cmd */
	FB_GEN_RESP(ctx, "OKAY");
	(void)prot_send_response(ctx);

	ret = power_shutdown(POWER_REBOOT_SYSTEM);
	if (ret != FCSERR_OK)
		goto exit_reboot;

	exit(0);
exit_reboot:
	/*
	 * If something failed device will not power down. In this case we
	 * return to fastboot protocol.
	 */
	FCS_LOG_ERR("Reboot failed (%d)\n", ret);
	FB_GEN_RESP(ctx, "FAILreboot");
	return ret;
}

static int handle_oem_unlock(struct loader_ctx *ldr_ctx)
{
	int ret = FCSERR_OK;
	size_t rck_len;
	size_t offset;
	char *rck = NULL;
	uint8_t rck_h[RCK_H_LENGTH];
	uint8_t rooting_status;
	uint8_t allow_unlock;
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	ret = bootloader_unlock_allowed(&allow_unlock, &rooting_status);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get unlock allowed state\n");
		FB_GEN_RESP(ctx, "FAILFailed to get allowed state");
		return ret;
	}

	if (!allow_unlock) {
		if (rooting_status == BOOT_UNLOCKED) {
			FCS_LOG_ERR("Bootloader already unlocked\n");
			FB_GEN_RESP(ctx, "FAILBootloader already unlocked");
			return ret;
		}
		FCS_LOG_ERR("Command not allowed\n");
		FB_GEN_RESP(ctx, "FAILCommand not allowed");
		return ret;
	}

	if (strlen((char *)ctx->cmd) > (strlen(CMD_OEM_UNLOCK)) + 2) {
		/*
		 * The command format is "oem unlock [0x]1234567890ABCDEF". The
		 * parameter is " 1234567890ABCDEF" or " 0x1234567890ABCDEF".
		 * We remove the space, and 0x if prefixed, at the beginning
		 * when assigning the RCK value by setting the offset properly.
		 */
		if (ctx->cmd[(strlen(CMD_OEM_UNLOCK) + 2)] == 'x')
			offset = 3;
		else
			offset = 1;
		rck_len = strlen((char *)ctx->cmd)
				- strlen(CMD_OEM_UNLOCK) - offset;
	} else {
		FCS_LOG_ERR("Input value fail\n");
		FB_GEN_RESP(ctx, "FAILInput value fail");
		return -FCSERR_EINVAL;
	}

	if (rck_len != RCK_LENGTH) {
		FCS_LOG_ERR("Incorrect format for unlock data\n");
		FB_GEN_RESP(ctx, "FAILIncorrect format for unlock data");
		return -FCSERR_EINVAL;
	}

	rck = (char *)calloc(1, RCK_LENGTH + 1);
	if (rck == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		FB_GEN_RESP(ctx, "FAILOut of memory");
		return -FCSERR_ENOMEM;
	}

	strlcpy(rck,
		(char *)ctx->cmd + strlen(CMD_OEM_UNLOCK) + offset,
		RCK_LENGTH + 1);

	ret = get_simlock_rck_h(rck_h);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get RCK hash\n");
		FB_GEN_RESP(ctx, "FAILFailed to get RCK hash");
		goto exit;
	}

	ret = verify_rck(rck_h, (unsigned char *)rck, RCK_LENGTH);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Incorrect RCK\n");
		FB_GEN_RESP(ctx, "FAILCommand did not succeed");
		goto exit;
	}

	ret = write_ta(TA_MISC_PART, TA_RCK, (uint8_t *)rck, RCK_LENGTH);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Failed to write to miscTA\n");
		FB_GEN_RESP(ctx, "FAILFailed to write to miscTA");
		goto exit;
	}

	FB_GEN_RESP(ctx, "OKAY");
	(void)prot_send_response(ctx);
	/* Clean up before reboot */
	free(rck);
	rck = NULL;

	/* Reboot to let the boot handle unlocking of the bootloader */
	ret = power_shutdown(POWER_REBOOT_XFL);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Reboot to unlock bootloader failed (%d)\n",
				ret);
		FB_GEN_RESP(ctx, "FAILReboot to unlock bootloader");
	}

exit:
	if (rck)
		free(rck);
	return ret;
}

static int handle_oem_lock(struct loader_ctx *ldr_ctx)
{
	int ret = FCSERR_OK;
	uint32_t auth_ch_magic = AUTH_CH_MAGIC;
	int ta_sz = 0;
	uint8_t *ta_buf;
	uint8_t rooting_status;
	uint8_t allow_unlock;
	struct auth_ch_cmd ch_cmd = {};
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	ret = bootloader_unlock_allowed(&allow_unlock, &rooting_status);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get unlock allowed state\n");
		FB_GEN_RESP(ctx, "FAILFailed to get allowed state");
		return ret;
	}

	if (rooting_status != BOOT_UNLOCKED) {
		FCS_LOG_ERR("Bootloader already locked\n");
		FB_GEN_RESP(ctx, "FAILBootloader already locked");
		return ret;
	}

	ret = get_ta_unit_size(TA_MISC_PART, TA_AUTH_CH, &ta_sz);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("get_ta_unit_size returned err=%d\n", ret);
		FB_GEN_RESP(ctx, "FAILFailed to read TA size");
		return ret;
	}

	ta_buf = malloc(ta_sz + sizeof(struct auth_ch_cmd));
	if (ta_buf == NULL) {
		FB_GEN_RESP(ctx, "FAILFailed to allocate memory");
		return -FCSERR_ENOMEM;
	}

	/*
	 * The command should be appended in the authentication channel.
	 * For that reason, first read its contents, if any.
	 */
	if (ta_sz > 0) {
		ret = read_ta(TA_MISC_PART, TA_AUTH_CH, ta_buf, ta_sz);
		if (ret != FCSERR_OK) {
			FB_GEN_RESP(ctx, "FAILFailed to read TA");
			goto exit;
		}
	}
	memcpy(ta_buf, &auth_ch_magic, sizeof(auth_ch_magic));

	ch_cmd.magic = AUTH_CH_MAGIC;
	ch_cmd.version = AUTH_CH_VERSION;
	ch_cmd.id = AUTH_CH_OEM_LOCK;
	ch_cmd.sz = 0;

	memcpy(ta_buf + ta_sz, &ch_cmd, sizeof(struct auth_ch_cmd));
	ta_sz += sizeof(struct auth_ch_cmd);

	ret = write_ta(TA_MISC_PART, TA_AUTH_CH, ta_buf, ta_sz);
	if (ret != FCSERR_OK) {
		FB_GEN_RESP(ctx, "FAILFailed to write TA");
		goto exit;
	}
	FB_GEN_RESP(ctx, "OKAY");
	(void)prot_send_response(ctx);
	/* Clean up before reboot */
	free(ta_buf);
	ta_buf = NULL;

	/* Reboot to let the boot handle locking of the bootloader */
	ret = power_shutdown(POWER_REBOOT_XFL);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Reboot to lock bootloader failed (%d)\n",
				ret);
		FB_GEN_RESP(ctx, "FAILReboot to lock bootloader");
	}

exit:
	if (ta_buf)
		free(ta_buf);
	return ret;
}

static int handle_continue(struct loader_ctx *ldr_ctx)
{
	int ret = FCSERR_OK;
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	FCS_LOG_INF("Reboot device\n");

	/* make sure that all data is written to flash */
	write_to_flash_final(ctx);

	/* send ok that we have received cmd */
	FB_GEN_RESP(ctx, "OKAY");
	(void)prot_send_response(ctx);

	/* Reboot with System warmboot reason will boot into app SW */
	ret = power_shutdown(POWER_REBOOT_SYSTEM);

	if (ret != FCSERR_OK)
		goto exit_continue;

	exit(0);
exit_continue:
	/*
	 * If something failed device will not power down. In this case we
	 * return to fastboot protocol.
	 */
	FCS_LOG_ERR("Reboot failed (%d)\n", ret);
	FB_GEN_RESP(ctx, "FAILcontinue");
	return ret;
}

static int fb_erase_overlap(struct protocol *ctx, const char *lun)
{
	struct storage_ctx *rdctx;
	ssize_t sz;
	uint8_t *buf = NULL;
	int res;

	if (!ctx) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	rdctx = storage_open_by_name(FASTBOOT_TMP_STORAGE,
					STORAGE_RAMDISK_NAME);
	if (rdctx == NULL) {
		FCS_LOG_ERR("Unable to open ramdisk file %s\n",
				STORAGE_RAMDISK_NAME);
		FB_GEN_RESP(ctx, "FAILRamdisk open failed");
		return -FCSERR_EINVAL;
	}

	sz = pu_get_part_size(rdctx);
	if (sz < 0) {
		FCS_LOG_ERR("IO Error\n");
		FB_GEN_RESP(ctx, "FAILIO Error");
		res = -FCSERR_EIO;
		goto exit;
	}

	buf = (uint8_t *)malloc(sz);
	if (buf == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		FB_GEN_RESP(ctx, "FAILOut of memory");
		res = -FCSERR_ENOMEM;
		goto exit;
	}

	res = storage_read(rdctx, buf, sz);
	if (res != sz) {
		FCS_LOG_ERR("Read fail\n");
		FB_GEN_RESP(ctx, "FAILRead fail");
		if (res >= 0)
			res = -FCSERR_EIO;
		goto exit;
	}

	res = partman_erase_overlap(buf, sz, lun);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Erase of overlapping partitions failed: (%d)\n",
			res);
		FB_GEN_RESP(ctx, "FAILPartition erase fail");
		res = -FCSERR_EIO;
	}

exit:
	free(buf);
	(void)storage_close(rdctx);
	return res;
}

static int fb_gpt_sanity_check(struct protocol *ctx, const char *lun,
		int *nbr_part)
{
	struct storage_ctx *rdctx;
	ssize_t sz;
	uint8_t *buf = NULL;
	int res;

	if (!ctx) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	rdctx = storage_open_by_name(FASTBOOT_TMP_STORAGE,
				STORAGE_RAMDISK_NAME);
	if (rdctx == NULL) {
		FCS_LOG_ERR("Unable to open ramdisk file %s\n",
				STORAGE_RAMDISK_NAME);
		FB_GEN_RESP(ctx, "FAILRamdisk open failed");
		return -FCSERR_EINVAL;
	}

	sz = pu_get_part_size(rdctx);
	if (sz < 0) {
		FCS_LOG_ERR("IO Error\n");
		FB_GEN_RESP(ctx, "FAILIO Error");
		res = -FCSERR_EIO;
		goto exit;
	}

	buf = (uint8_t *)malloc(sz);
	if (buf == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		FB_GEN_RESP(ctx, "FAILOut of memory");
		res = -FCSERR_ENOMEM;
		goto exit;
	}

	res = storage_read(rdctx, buf, sz);
	if (res != sz) {
		FCS_LOG_ERR("Read fail\n");
		FB_GEN_RESP(ctx, "FAILRead fail");
		if (res >= 0)
			res = -FCSERR_EIO;
		goto exit;
	}

	res = partman_gpt_sanity_check(buf, sz, lun, nbr_part);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Sanity check of gpt table failed\n");
		FB_GEN_RESP(ctx, "FAILGPT sanity check fail");
		res = -FCSERR_EINVAL;
		goto exit;
	}

exit:
	free(buf);
	(void)storage_close(rdctx);
	return res;
}

static int fb_patch_primary_table(struct protocol *ctx, const char *lun)
{
	struct storage_ctx *rdctx = NULL;
	uint8_t *buf = NULL;
	ssize_t buf_sz;
	int res = FCSERR_OK;

	if (!ctx) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	rdctx = storage_open_by_name(FASTBOOT_TMP_STORAGE,
					STORAGE_RAMDISK_NAME);
	if (rdctx == NULL) {
		FCS_LOG_ERR("Unable to open ramdisk file %s\n",
				STORAGE_RAMDISK_NAME);
		FB_GEN_RESP(ctx, "FAILRamdisk open failed");
		return -FCSERR_EINVAL;
	}

	buf_sz = pu_get_part_size(rdctx);
	if (buf_sz < 0) {
		FCS_LOG_ERR("IO Error\n");
		FB_GEN_RESP(ctx, "FAILIO Error");
		res = -FCSERR_EIO;
		goto exit;
	}

	buf = (uint8_t *)malloc(buf_sz);
	if (buf == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		FB_GEN_RESP(ctx, "FAILOut of memory");
		res = -FCSERR_ENOMEM;
		goto exit;
	}

	res = storage_read(rdctx, buf, buf_sz);
	if (res != buf_sz) {
		FCS_LOG_ERR("Read fail\n");
		FB_GEN_RESP(ctx, "FAILRead fail");
		if (res >= 0)
			res = -FCSERR_EIO;
		goto exit;
	}

	res = partman_patch_primary_gpt(buf, buf_sz, lun);
	if (res < 0) {
		FCS_LOG_ERR("Failed to patch gpt: (%d)\n", res);
		FB_GEN_RESP(ctx, "FAILFailed to patch primary gpt");
		goto exit;
	}

	/* Reset file pointer to start */
	if (storage_lseek(rdctx, 0, STORAGE_SEEK_SET) < 0) {
		FCS_LOG_ERR("IO error (errno=%d)\n", errno);
		FB_GEN_RESP(ctx, "FAILIO Error");
		res = -FCSERR_EIO;
		goto exit;
	}

	/* Update gpt table on ramdisk */
	res = storage_write(rdctx, buf, buf_sz);
	if (res != buf_sz) {
		FCS_LOG_ERR("IO error\n");
		FB_GEN_RESP(ctx, "FAILIO Error");
		res = -FCSERR_EIO;
		goto exit;
	}
	res = FCSERR_OK;

exit:
	free(buf);
	storage_close(rdctx);

	return res;
}

static int fb_prepare_secondary_table(struct protocol *ctx, const char *lun)
{
	struct storage_ctx *rdctx = NULL;
	ssize_t buf_sz;
	uint8_t *buf = NULL;
	int res;

	if (!ctx) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	rdctx = storage_open_by_name(FASTBOOT_TMP_STORAGE,
				STORAGE_RAMDISK_NAME);
	if (rdctx == NULL) {
		FCS_LOG_ERR("Unable to open ramdisk file %s\n",
				STORAGE_RAMDISK_NAME);
		FB_GEN_RESP(ctx, "FAILRamdisk open failed");
		return -FCSERR_EINVAL;
	}

	buf_sz = pu_get_part_size(rdctx);
	if (buf_sz < 0) {
		FCS_LOG_ERR("IO Error\n");
		FB_GEN_RESP(ctx, "FAILIO Error");
		res = -FCSERR_EIO;
		goto exit;
	}

	buf = (uint8_t *)malloc(buf_sz);
	if (buf == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		FB_GEN_RESP(ctx, "FAILOut of memory");
		res = -FCSERR_ENOMEM;
		goto exit;
	}

	res = storage_read(rdctx, buf, buf_sz);
	if (res != buf_sz) {
		FCS_LOG_ERR("Read fail\n");
		FB_GEN_RESP(ctx, "FAILRead fail");
		if (res >= 0)
			res = -FCSERR_EIO;
		goto exit;
	}

	/* Reset file pointer to start */
	if (storage_lseek(rdctx, 0, STORAGE_SEEK_SET) < 0) {
		FCS_LOG_ERR("IO error (errno=%d)\n", errno);
		FB_GEN_RESP(ctx, "FAILIO Error");
		res = -FCSERR_EIO;
		goto exit;
	}

	res = partman_prepare_secondary_gpt(rdctx, buf, buf_sz, lun);
	if (res < 0) {
		FCS_LOG_ERR("Failed to get secondary gpt (%d)\n", res);
		if (lun)
			FCS_LOG_ERR("lun: %c\n", *lun);
		FB_GEN_RESP(ctx, "FAILSecondary gpt fail");
		res = -FCSERR_EIO;
		goto exit;
	}

exit:
	free(buf);
	if (rdctx)
		storage_close(rdctx);
	return res;
}

/*
 * Commits previous downloaded data to flash
 */
static int handle_repartition(struct loader_ctx *ldr_ctx)
{
	int res;
	size_t len;
	char *name;
	int nbr_part;
	uint8_t *mbuf = NULL;
	uint8_t *bbuf = NULL;
	ssize_t part_sz, mbuf_sz, bbuf_sz, data_read, data_written;
	struct storage_ctx *sctx = NULL;
	struct protocol *ctx;
	bool is_ufs;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	if (strlen((char *)ctx->cmd) > strlen(CMD_REPARTITION)) {
		len = strlen((char *)ctx->cmd) - strlen(CMD_REPARTITION);
		/* sanity check */
		if (len < 2 || ctx->cmd[strlen(CMD_REPARTITION)] != ':' ||
		    len > FASTBOOT_BUFFER_SIZE - strlen(CMD_REPARTITION) - 1) {
			FCS_LOG_ERR("Invalid command %s\n", (char *)ctx->cmd);
			FB_GEN_RESP(ctx, "FAILInvalid command");
			return -FCSERR_EINVAL;
		}
		/* Parameter entered, check so that we are on UFS */
		name = (char *)(ctx->cmd + strlen(CMD_REPARTITION) + 1);
	} else {
		/* No parameter entered, check so that we are on eMMC */
		name = NULL;
	}

	/*
	 * Check so that Repartition-command is called correctly for UFS and
	 * eMMC respectively.
	 * UFS must have a target device as parameter and eMMC not.
	 */
	is_ufs = (strncmp(FLASH_TYPE, "UFS", strlen("UFS") + 1) == 0);
	if (is_ufs && !name) {
		FCS_LOG_ERR("This is UFS; name MUST NOT be NULL, but it is\n");
		FB_GEN_RESP(ctx, "FAILInvalid command");
		return -FCSERR_EINVAL;
	} else if (!is_ufs && name) {
		FCS_LOG_WRN("This is eMMC; name MUST be NULL, but it is not\n");
		name = NULL;
	}

	/* make sure that all data is written to flash */
	write_to_flash_final(ctx);

	/* Check so that lun/flash is not too small for partitions in table */
	res = fb_gpt_sanity_check(ctx, name, &nbr_part);
	if (res != FCSERR_OK)
		goto exit;

	/* Read main keystore */
	sctx = storage_open_by_name(NULL, "xflkeystore");
	if (!sctx) {
		FCS_LOG_ERR("Failed to open partition\n");
		res = -FCSERR_EIO;
		goto exit;
	}

	mbuf_sz = pu_get_part_size(sctx);
	if (mbuf_sz < 0) {
		FCS_LOG_ERR("Failed to get partition size\n");
		res = -FCSERR_EIO;
		goto exit;
	}

	mbuf = malloc(mbuf_sz);
	if (!mbuf) {
		FCS_LOG_ERR("Out of memory\n");
		res = -FCSERR_ENOMEM;
		goto exit;
	}

	data_read = storage_read(sctx, mbuf, mbuf_sz);
	if (data_read != mbuf_sz) {
		FCS_LOG_ERR("Failed to read partition\n");
		res = -FCSERR_EIO;
		goto exit;
	}

	storage_close(sctx);
	sctx = NULL;

	/* Read backup keystore */
	sctx = storage_open_by_name(NULL, "xflkeystorebak");
	if (!sctx) {
		FCS_LOG_ERR("Failed to open partition\n");
		res = -FCSERR_EIO;
		goto exit;
	}

	bbuf_sz = pu_get_part_size(sctx);
	if (bbuf_sz < 0) {
		FCS_LOG_ERR("Failed to get partition size\n");
		res = -FCSERR_EIO;
		goto exit;
	}

	bbuf = malloc(bbuf_sz);
	if (!bbuf) {
		FCS_LOG_ERR("Out of memory\n");
		res = -FCSERR_ENOMEM;
		goto exit;
	}

	data_read = storage_read(sctx, bbuf, bbuf_sz);
	if (data_read != bbuf_sz) {
		FCS_LOG_ERR("Failed to read partition\n");
		res = -FCSERR_EIO;
		goto exit;
	}

	storage_close(sctx);
	sctx = NULL;

	res = fb_erase_overlap(ctx, name);
	if (res != FCSERR_OK)
		goto exit;

	res = fb_patch_primary_table(ctx, name);
	if (res != FCSERR_OK)
		goto exit;

	/* Write primary */
	res = write_to_flash(ctx, name);
	if (res != FCSERR_OK)
		goto exit;

	res = fb_prepare_secondary_table(ctx, name);
	if (res != FCSERR_OK)
		goto exit;

	/* BLKRRPART ioctl called in storage_rrpart
	 * will fail if some other process
	 * is using /dev/block/sd'X' block device.
	 * qseecomd is using the ssd partition.
	 * Stop the qseecomd service and start it again
	 * after repartition is finished.
	 */
	res = deinit_xflattest();
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("deinit_xflattest failed (%d)\n", res);
		goto exit;
	}

	/* Write secondary */
	res = write_to_flash(ctx, name);
	if (res != FCSERR_OK)
		goto exit;

	res = storage_rrpart(NULL, name);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("rrpart failed (%d)\n", res);
		goto exit;
	}

	res = fcs_wait_partition_rescan(name, nbr_part);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("fcs_wait_partition_rescan failed (%d)\n", res);
		goto exit;
	}

	res = init_xflattest();
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("init_xflattest failed (%d)\n", res);
		goto exit;
	}

	/* Write back keystore */
	sctx = storage_open_by_name(NULL, "xflkeystore");
	if (!sctx) {
		FCS_LOG_ERR("Failed to open partition\n");
		res = -FCSERR_EIO;
		goto exit;
	}

	part_sz = pu_get_part_size(sctx);
	if (mbuf_sz < 0) {
		FCS_LOG_ERR("Failed to get partition size\n");
		res = -FCSERR_EIO;
		goto exit;
	}

	if (part_sz < mbuf_sz) {
		FCS_LOG_ERR("Keystore can't be retained\n");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	data_written = storage_write(sctx, mbuf, mbuf_sz);
	if (data_written != mbuf_sz) {
		FCS_LOG_ERR("Flash write failed\n");
		res = -FCSERR_EIO;
		goto exit;
	}

	storage_close(sctx);
	sctx = NULL;

	/* Write back keystore-bak */
	sctx = storage_open_by_name(NULL, "xflkeystorebak");
	if (!sctx) {
		FCS_LOG_ERR("Failed to open partition\n");
		res = -FCSERR_EIO;
		goto exit;
	}

	part_sz = pu_get_part_size(sctx);
	if (bbuf_sz < 0) {
		FCS_LOG_ERR("Failed to get partition size\n");
		res = -FCSERR_EIO;
		goto exit;
	}

	if (part_sz < bbuf_sz) {
		FCS_LOG_ERR("Keystore can't be retained\n");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	data_written = storage_write(sctx, bbuf, bbuf_sz);
	if (data_written != bbuf_sz) {
		FCS_LOG_ERR("Flash write failed\n");
		res = -FCSERR_EIO;
		goto exit;
	}

	storage_close(sctx);
	sctx = NULL;

	write_to_flash_final(ctx);

exit:
	if (res == FCSERR_OK)
		FB_GEN_RESP(ctx, "OKAY");
	else
		FB_GEN_RESP(ctx, "FAILRepartition");

	if (sctx)
		storage_close(sctx);

	if (mbuf)
		free(mbuf);
	if (bbuf)
		free(bbuf);

	return res;
}

static int handle_get_partition_list(struct loader_ctx *ldr_ctx)
{
	int res = FCSERR_OK;
	size_t len = 0;
	uint8_t *data;
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	data = calloc(FB_PART_LIST_SIZE, 1);
	if (data == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		FB_GEN_RESP(ctx, "FAILOut of memory");
		return -FCSERR_ENOMEM;
	}

	res = get_partition_list(ctx, data, &len);
	if (res != FCSERR_OK || !len) {
		FCS_LOG_ERR("get_partition_list failed (%d)\n", res);
		FB_GEN_RESP(ctx, "FAILGet Partition list failed");
		goto err;
	}

	FB_GEN_RESP(ctx, "DATA%08zx", len);
	res = prot_send_response(ctx);
	if (res != FCSERR_OK)
		goto err;

	res = prot_send_data(ctx, data, len);
	if (res != FCSERR_OK)
		goto err;

	FB_GEN_RESP(ctx, "OKAY");

err:
	if (data)
		free(data);
	return res;
}

static int handle_getnvlog(struct loader_ctx *ldr_ctx)
{
	int res;
	ssize_t logsize;
	uint8_t *buf = NULL;
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	logsize = get_fcsnvlog_size();

	if (logsize > 0) {
		buf = malloc(logsize);
		if (buf == NULL)
			return -FCSERR_ENOMEM;

		res = get_fcsnvlog(buf, logsize);
		if (res != FCSERR_OK) {
			free(buf);
			FB_GEN_RESP(ctx, "FAILCould not read logfile: (%d)\n",
					res);
			return res;
		}

		/* Send response */
		FB_GEN_RESP(ctx, "DATA%08zx", logsize);
		res = prot_send_response(ctx);
		res = prot_send_data(ctx, buf, logsize);
		free(buf);
		FB_GEN_RESP(ctx, "OKAY");
	} else {
		FCS_LOG_INF("There is no log file.\n");

		/* Send response for no log file, case */
		FB_GEN_RESP(ctx, "DATA%08x", 0);
		res = prot_send_response(ctx);
		FB_GEN_RESP(ctx, "OKAYNo log to send");
	}

	return res;
}

static int handle_getlog(struct loader_ctx *ldr_ctx)
{
	int res = FCSERR_OK;
	ssize_t logsize;
	uint8_t *buf = NULL;
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	logsize = get_fcslog_size();
	if (logsize > 0) {
		buf = malloc(logsize);
		res = get_fcslog(buf, logsize);

		if (res != 1) {
			free(buf);
			FB_GEN_RESP(ctx, "FAILCould not read logfile: (%d)\n",
					res);
			return res;
		}

		/* Send response */
		FB_GEN_RESP(ctx, "DATA%08zx", logsize);
		res = prot_send_response(ctx);
		res = prot_send_data(ctx, buf, logsize);
		free(buf);
		FB_GEN_RESP(ctx, "OKAY");
	} else {
		FCS_LOG_INF("There is no log file.\n");

		/* Send response for no log file, case */
		FB_GEN_RESP(ctx, "DATA%08x", 0);
		res = prot_send_response(ctx);
		FB_GEN_RESP(ctx, "OKAYNo log to send");
	}

	return res;
}

static int handle_read_partition(struct loader_ctx *ldr_ctx)
{
	int res = FCSERR_OK;
	char *pname;
	long long psize; /* partition size */
	long long bytes_left;
	long long dsize; /* data chunk size */
	struct storage_ctx *sctx;
	void *data = NULL;
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	pname = (char *)((ctx->cmd)+strlen(CMD_READ_PARTITION));
	FCS_LOG_INF("Reading %s\n", pname);

	sctx = storage_open_by_name(NULL, pname);
	if (sctx == NULL) {
		FCS_LOG_ERR("%s does not exist\n", pname);
		FB_GEN_RESP(ctx, "FAILPartition does not exist.");
		return -FCSERR_EINVAL;
	}

	psize = pu_get_part_size(sctx);
	if (psize < 0) {
		FCS_LOG_ERR("IO Error\n");
		FB_GEN_RESP(ctx, "FAILIO Error");
		res = -FCSERR_EIO;
		goto exit;
	}

	dsize = MIN(MAX_USB_WRITE, psize);
	data = malloc(dsize);
	if (data == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		FB_GEN_RESP(ctx, "FAILOut of memory");
		goto exit;
	}

	do {
		if (psize > FB_MAX_DUMP_SIZE) {
			bytes_left = FB_MAX_DUMP_SIZE;
			psize -= FB_MAX_DUMP_SIZE;
		} else {
			bytes_left = psize;
			psize = 0;
		}
		FB_GEN_RESP(ctx, "DATA%08llx", bytes_left);
		res = prot_send_response(ctx);
		if (res != FCSERR_OK)
			goto exit;

		/* Send partition data */
		while (bytes_left) {
			res = storage_read(sctx, data, dsize);
			if (res != dsize) {
				FCS_LOG_ERR("Failed to read storage (%d)\n",
						res);
				FB_GEN_RESP(ctx, "FAILRead from storage");
				if (res >= 0)
					res = -FCSERR_EIO;
				goto exit;
			}
			res = prot_send_data(ctx, data, dsize);
			if (res != FCSERR_OK)
				goto exit;

			bytes_left = bytes_left - dsize;
			dsize = MIN(MAX_USB_WRITE, bytes_left);
		}
		dsize = MIN(MAX_USB_WRITE, psize);
	} while (psize > 0);

	FB_GEN_RESP(ctx, "OKAY");

exit:
	free(data);
	if (sctx)
		storage_close(sctx);
	return res;
}

static int handle_read_sector(struct loader_ctx *ldr_ctx)
{
	int res = FCSERR_OK;
	char *args;
	int lun = 0;
	ssize_t ssize, bytes_left, dsize;
	ssize_t start, end, psize, dump_sz;
	struct storage_ctx *sctx = NULL;
	void *data = NULL;
	char clun[2];
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	/* args will point at "[:l]:s:e" */
	args = (char *)((ctx->cmd)+strlen(CMD_READ_SECTOR));
	FCS_LOG_INF("Reading %s\n", args);

	/* Get the parameters */
	res = parse_args(args, &lun, &start, &end);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to parse parameters: %d\n", res);
		return -FCSERR_EINVAL;
	}

	/*
	 * lun can only be a value between 0 and 7, but it will be set to
	 * -1 in the case of it being omitted by caller.
	 */
	if (lun < -1 || lun > 7) {
		FCS_LOG_ERR("Bad input parameters\n");
		return -FCSERR_EINVAL;
	}

	snprintf(clun, sizeof(clun), "%d", lun);
	sctx = storage_open_by_name(NULL, (lun != -1) ? clun : NULL);
	if (sctx == NULL) {
		FCS_LOG_ERR("%s does not exist\n", args);
		FB_GEN_RESP(ctx, "FAILPartition does not exist.");
		return -FCSERR_EINVAL;
	}

	/* Get size of the current lun/device */
	psize = pu_get_part_size(sctx);
	if (psize < 0) {
		FCS_LOG_ERR("IO Error\n");
		FB_GEN_RESP(ctx, "FAILIO Error");
		res = -FCSERR_EIO;
		goto exit;
	}

	ssize = storage_get_ssz(sctx);
	if (ssize <= 0) {
		FCS_LOG_ERR("Failed to read sector size: %zd\n", ssize);
		return -FCSERR_EIO;
	}

	/* Sanity check of input parameters */
	if (start > psize/ssize || end > psize/ssize) {
		FCS_LOG_ERR("Trying to read outside of lun/drive\n");
		goto exit;
	} else if (start > end) {
		FCS_LOG_ERR("Incorrect range\n");
		goto exit;
	}

	/* Size of data to dump (in bytes) */
	dump_sz = (end - start + 1)*ssize;

	dsize = MIN(MAX_USB_WRITE, dump_sz);
	data = malloc(dump_sz);
	if (data == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		FB_GEN_RESP(ctx, "FAILOut of memory");
		goto exit;
	}

	/* Go to position where we want to start reading our data */
	if (storage_lseek(sctx, (off_t)start*ssize, STORAGE_SEEK_SET) < 0) {
		FCS_LOG_ERR("Failed to seek (errno=%d)\n", errno);
		res = -FCSERR_EIO;
		goto exit;
	}
	do {
		if (dump_sz > FB_MAX_DUMP_SIZE) {
			bytes_left = FB_MAX_DUMP_SIZE;
			dump_sz -= FB_MAX_DUMP_SIZE;
		} else {
			bytes_left = dump_sz;
			dump_sz = 0;
		}
		FB_GEN_RESP(ctx, "DATA%08zx", bytes_left);
		res = prot_send_response(ctx);
		if (res != FCSERR_OK)
			goto exit;

		/* Send partition data */
		while (bytes_left) {
			res = storage_read(sctx, data, dsize);
			if (res != dsize) {
				FCS_LOG_ERR("Failed to read storage (%d)\n",
						res);
				FB_GEN_RESP(ctx, "FAILRead from storage");
				if (res >= 0)
					res = -FCSERR_EIO;
				goto exit;
			}
			res = prot_send_data(ctx, data, dsize);
			if (res != FCSERR_OK)
				goto exit;

			bytes_left = bytes_left - dsize;
			dsize = MIN(MAX_USB_WRITE, bytes_left);
		}
		dsize = MIN(MAX_USB_WRITE, dump_sz);
	} while (dump_sz > 0);

	FB_GEN_RESP(ctx, "OKAY");

exit:
	free(data);
	if (sctx)
		storage_close(sctx);
	return res;
}

static int erase(struct protocol *ctx)
{
	int res = FCSERR_OK;
	char *pname;
	bool secure_erase = true;

	if (!ctx || ctx->erase_type == SB_ERASE_NONE) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	/* make sure that all data is written to flash */
	write_to_flash_final(ctx);

	if (ctx->erase_type == SB_ERASE_SECURE) {
		pname = (char *)((ctx->cmd)+strlen(CMD_SECURE_ERASE));
		secure_erase = true;
	} else {
		pname = (char *)((ctx->cmd)+strlen(CMD_ERASE));
		secure_erase = false;
	}

	FCS_LOG_INF("Erase %s\n", pname);

	/*
	 * Do not perform erase on partition BOOT_MAGIC and do not clear
	 * erase_type until after boot upgrade is done.
	 */
	if (is_bootloader(pname)) {
		FCS_LOG_INF("Erase handled separately in bootloader case\n");
		FB_GEN_RESP(ctx, "OKAY");

		return res;
	}

	res = partman_erase(pname, secure_erase);
	if (res == -FCSERR_ENOENT) {
		FB_GEN_RESP(ctx, "FAILNo such partition");
		goto exit;
	}
	if (res < 0) {
		FB_GEN_RESP(ctx, "FAILErase %s failed", pname);
		goto exit;
	}

	res = reset_slot_parameters(pname);
	if (res) {
		FCS_LOG_ERR("Failed to reset slot parameters. (%d)\n", res);
		FB_GEN_RESP(ctx, "FAILSlot parameters not updated\n");
		goto exit;
	}

	FB_GEN_RESP(ctx, "OKAY");

exit:
	/* Remove erase configuration */
	ctx->erase_type = SB_ERASE_NONE;

	return res;
}

static int erase_sector(struct protocol *ctx)
{
	int res = FCSERR_OK;
	int lun = 0;
	char *args;
	ssize_t start, end;
	bool secure_erase = true;

	if (!ctx) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	/* args will point at "[:l]:s:e" */
	if (ctx->erase_type == SB_ERASE_SECURE) {
		args = (char *)((ctx->cmd)+strlen(CMD_SECURE_ERASE_SECTOR));
		secure_erase = true;
	} else {
		args = (char *)((ctx->cmd)+strlen(CMD_ERASE_SECTOR));
		secure_erase = false;
	}

	/* Get the parameters */
	res = parse_args(args, &lun, &start, &end);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to parse parameters: %d\n", res);
		FB_GEN_RESP(ctx, "FAILInput parameters");
		return -FCSERR_EINVAL;
	}

	res = partman_erase_sector(lun, start, end, secure_erase);
	if (res < 0) {
		FB_GEN_RESP(ctx, "FAILErase sector(s) failed");
		goto exit;
	}

	FB_GEN_RESP(ctx, "OKAY");

exit:
	/* Remove erase configuration */
	ctx->erase_type = SB_ERASE_NONE;

	return res;
}

static int sync_and_purge(struct protocol *ctx)
{
	int res = FCSERR_OK;

	if (!ctx) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	sync();

	res = storage_purge();
	if (res < 0) {
		FB_GEN_RESP(ctx, "FAILPurge failed");
		return res;
	}

	FB_GEN_RESP(ctx, "OKAY");

	return res;
}

static int sync_powerdown(struct protocol *ctx)
{
	int ret;

	if (!ctx) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	/*
	 * If the erase command has been called, and no Sync command
	 * has been called after it, make sure we do purge before we
	 * shutdown.
	 */
	if (ctx->do_purge) {
		/*
		 * Sync and purge will be done now, so make sure it is not
		 * done again on USB removal.
		 */
		purge_usb_removal(false);
		ret = sync_and_purge(ctx);
		if (ret < 0) {
			FCS_LOG_ERR("Purge failed (%d)\n", ret);
			/*
			 * Do not return error here if there is no Purge
			 * support in the Kernel for the UFS memory.
			 */
			if (ret != -FCSERR_PERM)
				return ret;
		}
	}

	return FCSERR_OK;
}

static void set_purge(struct protocol *ctx, bool do_purge)
{
	ctx->do_purge = do_purge;
	purge_usb_removal(do_purge);
}

static int handle_erase_sector(struct loader_ctx *ldr_ctx)
{
	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ldr_ctx->prot_hdl->erase_type = SB_ERASE_NORMAL;
	/*
	 * Make sure purge is called on shutdown, if no
	 * Secure-erase or Sync are issued later.
	 */
	set_purge(ldr_ctx->prot_hdl, true);
	return erase_sector(ldr_ctx->prot_hdl);
}

static int handle_secure_erase_sector(struct loader_ctx *ldr_ctx)
{
	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ldr_ctx->prot_hdl->erase_type = SB_ERASE_SECURE;
	/*
	 * erase_type = SB_ERASE_SECURE, makes sure purge is
	 * called at the end of the command. No need to
	 * do purge on shutdown.
	 */
	set_purge(ldr_ctx->prot_hdl, false);
	return erase_sector(ldr_ctx->prot_hdl);
}

static int handle_erase(struct loader_ctx *ldr_ctx)
{
	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ldr_ctx->prot_hdl->erase_type = SB_ERASE_NORMAL;
	/*
	 * Make sure purge is called on shutdown, if no
	 * Secure-erase or Sync are issued later.
	 */
	set_purge(ldr_ctx->prot_hdl, true);
	return erase(ldr_ctx->prot_hdl);
}

static int handle_secure_erase(struct loader_ctx *ldr_ctx)
{
	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ldr_ctx->prot_hdl->erase_type = SB_ERASE_SECURE;
	/*
	 * erase_type = SB_ERASE_SECURE, makes sure purge is
	 * called at the end of the command. No need to
	 * do purge on shutdown.
	 */
	set_purge(ldr_ctx->prot_hdl, false);
	return erase(ldr_ctx->prot_hdl);
}

static int handle_sync(struct loader_ctx *ldr_ctx)
{
	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	set_purge(ldr_ctx->prot_hdl, false);
	return sync_and_purge(ldr_ctx->prot_hdl);
}

static int parse_active_slot(char *buf, size_t buf_sz,
		char *active_slot, char *inactive_slot)
{
	int res = FCSERR_OK;

	if (!buf || !active_slot || !inactive_slot) {
		res = -FCSERR_EINVAL;
		goto exit;
	}

	/*
	 * buf should contain 1 or 2 chars, either "_?" or "?" where ? is the
	 * slot.
	 */
	if (buf_sz == 1) {
		*active_slot = buf[0];
	} else if (buf_sz == 2) {
		if (buf[0] != '_') {
			res = -FCSERR_EINVAL;
			goto exit;
		}
		*active_slot = buf[1];
	} else {
		res = -FCSERR_EINVAL;
		goto exit;
	}

	/* Is it a valid slot? */
	if (*active_slot != 'a' && *active_slot != 'b') {
		FCS_LOG_ERR("Invalid slot\n");
		res = -FCSERR_EINVAL;
	}

	*inactive_slot = (*active_slot == 'a') ? 'b' : 'a';

exit:
	if (res)
		FCS_LOG_ERR("Bad input parameters\n");

	return res;
}

/*
 * set_active command should look like this:
 * "set_active _?"
 * or
 * "set_active ?"
 * Where ? is the slot.
 */
static int handle_set_active(struct loader_ctx *ldr_ctx)
{
	char *slot;
	size_t cmd_len, slot_count;
	int res;
	char active_slot, inactive_slot;
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	res = partman_get_slot_count(&slot_count);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get slot count\n");
		FB_GEN_RESP(ctx, "FAILFailed to get slot count");
		return res;
	} else if (slot_count != 2) {
		FCS_LOG_ERR("Slots are not supported on this device\n");
		FB_GEN_RESP(ctx, "FAILSlots not supported on this device");
		return -FCSERR_ENIMP;
	}

	cmd_len = strlen((char *)(ctx->cmd));
	if (cmd_len < strlen(CMD_SET_ACTIVE) + strlen("?") + 1) {
		FCS_LOG_ERR("Bad input parameters\n");
		FB_GEN_RESP(ctx, "FAILBad input parameters");
		return -FCSERR_EINVAL;
	}

	/* slot should point to argument after "set_active" cmd */
	slot = (char *)((ctx->cmd)+strlen(CMD_SET_ACTIVE) + 1);

	res = parse_active_slot(slot, strlen(slot),
			&active_slot, &inactive_slot);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to parse slot (%d)\n", res);
		FB_GEN_RESP(ctx, "FAILFailed to parse slot");
		return res;
	}

	res = ab_set_active(active_slot);

	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to set active slot\n");
		FB_GEN_RESP(ctx, "FAILFailed to set active slot");
	} else {
		FB_GEN_RESP(ctx, "OKAY");
	}

	return res;
}

static int handle_reset_rollback_counter(struct loader_ctx *ldr_ctx)
{
	int res = FCSERR_OK;
	uint32_t auth_ch_magic = AUTH_CH_MAGIC;
	int ta_sz = 0;
	uint8_t *ta_buf;
	struct auth_ch_cmd ch_cmd = {};
	struct protocol *ctx;
	char active_slot;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	res = get_ta_unit_size(TA_MISC_PART, TA_AUTH_CH, &ta_sz);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("get_ta_unit_size returned err=%d\n", res);
		FB_GEN_RESP(ctx, "FAILFailed to read TA size");
		return res;
	}

	ta_buf = malloc(ta_sz + sizeof(struct auth_ch_cmd));
	if (ta_buf == NULL) {
		FB_GEN_RESP(ctx, "FAILFailed to allocate memory");
		return -FCSERR_ENOMEM;
	}

	/*
	 * The command should be appended in the authentication channel.
	 * For that reason, first read its contents, if any.
	 */
	if (ta_sz > 0) {
		res = read_ta(TA_MISC_PART, TA_AUTH_CH, ta_buf, ta_sz);
		if (res != FCSERR_OK) {
			FB_GEN_RESP(ctx, "FAILFailed to read TA");
			goto exit;
		}
	}
	memcpy(ta_buf, &auth_ch_magic, sizeof(auth_ch_magic));

	ch_cmd.magic = AUTH_CH_MAGIC;
	ch_cmd.version = AUTH_CH_VERSION;
	ch_cmd.id = AUTH_CH_RESET_VBMETA_ARB;
	ch_cmd.sz = 0;

	memcpy(ta_buf + ta_sz, &ch_cmd, sizeof(struct auth_ch_cmd));
	ta_sz += sizeof(struct auth_ch_cmd);

	res = write_ta(TA_MISC_PART, TA_AUTH_CH, ta_buf, ta_sz);
	if (res != FCSERR_OK) {
		FB_GEN_RESP(ctx, "FAILFailed to write TA");
		goto exit;
	}

	res = ab_get_active(&active_slot);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get active slot\n");
		FB_GEN_RESP(ctx, "Failed to get active slot");
		goto exit;
	}

	res = ab_set_active(active_slot);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to set active slot\n");
		FB_GEN_RESP(ctx, "FAILFailed to set active slot");
		goto exit;
	}

	FB_GEN_RESP(ctx, "OKAY");

exit:
	free(ta_buf);
	return res;
}

static int handle_reset_frp(struct loader_ctx *ldr_ctx)
{
	int res = FCSERR_OK;
	struct protocol *ctx;

	if (!ldr_ctx) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	/*
	 * Make sure purge is called on shutdown, if no
	 * Secure-erase or Sync are issued later.
	 */
	set_purge(ctx, true);

	res = partman_erase(FRP_PARTITION_NAME, false);
	if (res != FCSERR_OK) {
		FB_GEN_RESP(ctx, "FAILFailed to erase frp");
		return res;
	}

	FB_GEN_RESP(ctx, "OKAY");

	return res;
}

static int fastboot_add_func(const char *name, int (*func)(char *val))
{
	struct fastboot_variable_entry *ent;
	size_t name_size;

	if (!name || !func) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	if (!list_empty(&fastboot_var_list)) {
		LIST_FOR_EACH_DATA(&fastboot_var_list, ent, list) {
			if (strncmp(ent->name, name,
					strlen(ent->name)+1) == 0) {
				FCS_LOG_ERR("Variable already defined\n");
				return -FCSERR_EINVAL;
			}
		}
	}

	ent = calloc(1, sizeof(struct fastboot_variable_entry));
	if (!ent) {
		FCS_LOG_ERR("Unable to allocate memory\n");
		return -FCSERR_ENOMEM;
	}
	name_size = strlen(name) + 1;
	ent->name = calloc(1, name_size);
	if (!ent->name) {
		free(ent);
		FCS_LOG_ERR("Unable to allocate memory\n");
		return -FCSERR_ENOMEM;
	}

	strlcpy(ent->name, name, name_size);
	ent->get_value = func;

	list_add_tail(&fastboot_var_list, &ent->list);

	return FCSERR_OK;
}

static int fastboot_add_cmd(const char *name,
		int (*func)(struct loader_ctx *ldr_ctx),
		uint8_t auth_level)
{
	struct fastboot_command_entry *ent;
	size_t name_size;

	if (!name || !func) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	if (!list_empty(&fastboot_cmd_list)) {
		LIST_FOR_EACH_DATA(&fastboot_cmd_list, ent, list) {
			if (strncmp(ent->name, name,
					strlen(ent->name)+1) == 0) {
				FCS_LOG_ERR("Command already defined\n");
				return -FCSERR_EINVAL;
			}
		}
	}

	ent = calloc(1, sizeof(struct fastboot_command_entry));
	if (!ent) {
		FCS_LOG_ERR("Unable to allocate memory\n");
		return -FCSERR_ENOMEM;
	}

	name_size = strlen(name) + 1;
	ent->name = calloc(1, name_size);
	if (!ent->name) {
		free(ent);
		FCS_LOG_ERR("Unable to allocate memory\n");
		return -FCSERR_ENOMEM;
	}

	strlcpy(ent->name, name, name_size);
	ent->handle = func;
	ent->auth_level = auth_level;

	list_add_tail(&fastboot_cmd_list, &ent->list);

	return FCSERR_OK;
}

static int fastboot_get_variable(const char *getvar_var_name, char *value)
{
	struct fastboot_variable_entry *var;
	char *partition;
	char *index;
	int res = -FCSERR_ENOTF;

	if (!getvar_var_name || !value) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	if (list_empty(&fastboot_var_list)) {
		FCS_LOG_ERR("List empty\n");
		return -FCSERR_ESTATE;
	}

	LIST_FOR_EACH_DATA(&fastboot_var_list, var, list) {
		if (strncmp(getvar_var_name, var->name,
			    strlen(var->name)+1) == 0) {
			return var->get_value(value);
		}
	}

	/* has-slot, partition-type and partition-size
	 * can be asked for any partition
	 *
	 * Rollback-index is parameterized.
	 */
	if (strncmp(getvar_var_name, "has-slot:",
				strlen("has-slot:")) == 0) {
		partition = get_string_arg_from_cmd("has-slot:",
			(uint8_t *)getvar_var_name);
		if (partition) {
			res = fastboot_get_has_slot(partition, value);
			free(partition);
		}
		return res;
	} else if (strncmp(getvar_var_name, "partition-type:",
				strlen("partition-type:")) == 0) {
		partition = get_string_arg_from_cmd("partition-type:",
			(uint8_t *)getvar_var_name);
		if (partition) {
			res = fastboot_get_partition_type(partition, value);
			free(partition);
		}
		return res;
	} else if (strncmp(getvar_var_name, "partition-size:",
				strlen("partition-size:")) == 0) {
		partition = get_string_arg_from_cmd("partition-size:",
			(uint8_t *)getvar_var_name);
		if (partition) {
			res = fastboot_get_partition_size(partition, value);
			free(partition);
		}
		return res;
	} else if (strncmp(getvar_var_name, "Rollback-index:",
				strlen("Rollback-index:")) == 0) {
		index = get_string_arg_from_cmd("Rollback-index:",
			(uint8_t *)getvar_var_name);
		if (index) {
			res = fastboot_get_rollback_counter(index, value);
			free(index);
		}
		return res;
	}

	/* Failed to find variable in list */
	FCS_LOG_ERR("%s: Could not find variable %s\n", __func__,
		getvar_var_name);
	return -FCSERR_ENOTF;
}

void fastboot_send_fail(struct protocol *ctx, const char *reason)
{
	/*
	 * Compose error message containing the unsupported parameter
	 * if there is room for it in one buffer size.
	 */
	if (strlen("FAIL") + strlen(reason) +  strlen(" not supported!") <=
			FASTBOOT_BUFFER_SIZE)
		FB_GEN_RESP(ctx, "FAIL%s %s", reason, "not supported");
	/*
	 * Else just send a standard fail message.
	 */
	else
		FB_GEN_RESP(ctx, "FAILNot supported");

}

void fastboot_send_okay(struct protocol *ctx, const char *reason)
{
	/*
	 * Compose response message containing the answer
	 * if there is room for it in one buffer size.
	 */
	if (strlen("OKAY") + strlen(reason)  <= FASTBOOT_BUFFER_SIZE)
		FB_GEN_RESP(ctx, "OKAY%s", reason);
	/*
	 * Else just send a standard OK message.
	 */
	else
		FB_GEN_RESP(ctx, "OKAY");

}

static int fastboot_get_version(char *val)
{
	if (!val) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	strlcpy(val, FB_VERSION, GETVAR_VALUE_SIZE);
	return FCSERR_OK;
}

static int fastboot_get_has_slot(const char *partition, char *val)
{
	int res, ret;
	bool has_slot = false;
	size_t slot_count = 0;

	if (!partition || !val) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	res = partman_has_slot(partition, &has_slot);
	if (res == -FCSERR_ENOTF) {
		ret = partman_get_slot_count(&slot_count);
		if (ret != FCSERR_OK) {
			res = ret;
			goto exit;
		}

		/*
		 * BOOT_MAGIC and PRELOADER are virtual partitions and not
		 * present in the partition table. Check if is one of those
		 * we are asking for.
		 */
		if (!strncmp(BOOT_MAGIC, partition,
			strlen(BOOT_MAGIC) + 1) ||
			!strncmp(PRELOADER, partition,
			strlen(PRELOADER) + 1)) {
			if (slot_count)
				has_slot = true;
			res = FCSERR_OK;
		}
	}

	if (has_slot) {
		strlcpy(val, "yes", GETVAR_VALUE_SIZE);
	} else if (!has_slot && res == FCSERR_OK) {
		strlcpy(val, "no", GETVAR_VALUE_SIZE);
	} else if (!has_slot && res == -FCSERR_ENOTF) {
		snprintf(val, GETVAR_VALUE_SIZE,
			"Partition %s does not exist", partition);
		res = FCSERR_OK;
	}

exit:
	return res;
}

static bool is_valid_partition(const char *ptn)
{
	/*
	 * Return true if partition is in the list of allowed
	 * partitions to flash or erase.
	 */
	int i;
	bool is_valid = false;

	if (!ptn) {
		FCS_LOG_ERR("Invalid argument\n");
		return false;
	}

	for (i = 0; i < no_of_allowed_ptns; i++)
		if (strncmp(ptn, allowed_ptns[i],
				strlen(allowed_ptns[i]) + 1) == 0)
			return true;

	return is_valid;
}

static int fastboot_get_partition_size(const char *partition, char *val)
{
	struct storage_ctx *sctx = NULL;
	ssize_t size = 0;
	bool valid;

	if (!partition || !val) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	valid = is_valid_partition(partition);
	if (!valid) {
		FCS_LOG_ERR("Partition %s is not valid\n", partition);
		return -FCSERR_EINVAL;
	}

	sctx = storage_open_by_name(NULL, partition);
	if (sctx == NULL) {
		FCS_LOG_ERR("Failed to open %s\n", partition);
		return -FCSERR_EINVAL;
	}

	size = pu_get_part_size(sctx);
	storage_close(sctx);

	if (size < 0) {
		FCS_LOG_ERR("IO Error\n");
		return -FCSERR_EIO;
	}

	snprintf(val, GETVAR_VALUE_SIZE, "0x%zx", size);

	return FCSERR_OK;
}

static int fastboot_get_partition_type(const char *partition, char *val)
{
	bool valid = false;
	int res = FCSERR_OK;

	if (!partition || !val) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	valid = is_valid_partition(partition);
	if (!valid) {
		FCS_LOG_ERR("Partition %s is not valid\n", partition);
		return -FCSERR_EINVAL;
	}

	res = pu_get_part_type(partition, val, GETVAR_VALUE_SIZE);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get partition type\n");
		strlcpy(val, "<empty>", GETVAR_VALUE_SIZE);
	}

	return res;
}

static int fastboot_get_slot_count(char *val)
{
	int res;
	size_t slot_count;

	if (!val) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	res = partman_get_slot_count(&slot_count);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get slot count\n");
		strlcpy(val, "0", sizeof("0"));
		return res;
	}

	/*
	 * Slot count should not be 1, that means we have a bad partition table.
	 */
	if (slot_count == 1) {
		FCS_LOG_ERR("Bad slot count (%zd)\n", slot_count);
		res = -FCSERR_ETBL;
	}

	snprintf(val, GETVAR_VALUE_SIZE, "%zd", slot_count);

	return res;
}

static int fastboot_get_maxdownloadsize(char *val)
{
	if (!val) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	snprintf(val, GETVAR_VALUE_SIZE, "%u", get_max_download_size());
	return FCSERR_OK;
}

static int fastboot_get_sonyversion(char *val)
{
	if (!val) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	strlcpy(val, FB_SONY_VERSION, GETVAR_VALUE_SIZE);
	return FCSERR_OK;
}

static int fastboot_get_loaderversion(char *val)
{
	if (!val) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	/* BUILD_NUMBER is macro set from Jenkins or build system */
	snprintf(val, GETVAR_VALUE_SIZE, "%s", BUILD_NUMBER);
	return FCSERR_OK;
}

static int fastboot_get_serialno(char *val)
{
	return get_miscta_unit_data(TA_MSN_UNIT, val, GETVAR_VALUE_SIZE);
}

static int fastboot_get_bootversion(char *val)
{
	return get_miscta_unit_data(
			TA_S1_BOOT_VERSION_UNIT, val, GETVAR_VALUE_SIZE);
}

static int fastboot_get_swversion(char *val)
{
	return get_miscta_unit_data(TA_SW_UNIT, val, GETVAR_VALUE_SIZE);
}

static int fastboot_get_product_name(char *val)
{
	return get_miscta_unit_data(TA_PHONE_NAME, val, GETVAR_VALUE_SIZE);
}

static int fastboot_get_phoneid(char *val)
{
	return get_phone_id(val, GETVAR_VALUE_SIZE);
}

static int fastboot_get_rootingstatus(char *val)
{
	return get_rooting_status_string(val, GETVAR_VALUE_SIZE);
}

static int fastboot_get_has_been_unlocked(char *val)
{
	int res;
	uint32_t has_been_unlocked;

	if (!val) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	res = sec_data_get_has_been_unlocked(&has_been_unlocked);

	if (res != FCSERR_OK) {
		FCS_LOG_INF("Failed to get has_been_unlocked flag\n");
		return res;
	}

	snprintf(val, GETVAR_VALUE_SIZE, "%s",
			has_been_unlocked == HAS_BEEN_UNLOCKED_MAGIC ?
			"yes" : "no");

	return FCSERR_OK;
}

static int fastboot_get_deviceid(char *val)
{
	uint8_t bbuf[(GETVAR_VALUE_SIZE - 1) / 2];
	int res = core_get_dieid(bbuf, sizeof(bbuf));

	if (res != FCSERR_OK)
		return res;

	res = bin_to_ascii(val, GETVAR_VALUE_SIZE, bbuf, core_get_dieid_len());

	return res;
}

static int fastboot_get_platformid(char *val)
{
	uint8_t bbuf[(GETVAR_VALUE_SIZE - 1) / 2];
	int res = fcsenv_get_platformid(bbuf, sizeof(bbuf));

	if (res != FCSERR_OK)
		return res;

	res = bin_to_ascii(
		val, GETVAR_VALUE_SIZE, bbuf, fcsenv_get_platformid_len());

	return res;
}

static int fastboot_get_frp_partition(char *val)
{
	strlcpy(val, FRP_PARTITION_NAME, GETVAR_VALUE_SIZE);
	return FCSERR_OK;
}

static int fastboot_get_secure(char *val)
{
	return fastboot_get_secure_state(val, GETVAR_VALUE_SIZE);
}

static int fastboot_get_sector_size(char *val)
{
	int res;
	struct storage_ctx *sctx = NULL;
	ssize_t ssize;

	if (!val) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	sctx = storage_open_by_name(NULL, NULL);
	if (!sctx) {
		FCS_LOG_ERR("Could not open raw device\n");
		return -FCSERR_EIO;
	}

	ssize = storage_get_ssz(sctx);
	if (ssize > 0)
		res = FCSERR_OK;
	else
		res = ssize;

	snprintf(val, GETVAR_VALUE_SIZE, "%zd", ssize);
	storage_close(sctx);

	return res;
}

static int fastboot_get_storage_info(char *val)
{
	int res = FCSERR_OK;

	res = pu_get_flash_info(val, GETVAR_VALUE_SIZE);
	if (res < 0)
		FCS_LOG_INF("Failed to get flash info\n");

	return res;
}

static int fastboot_get_keystore_counter(char *val)
{
	int res = FCSERR_OK;
	uint32_t ks_counter;
	int retry_cnt = MAX_RETRY_COUNT;

	if (!val) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	do {
		res = sec_data_get_ks_counter(&ks_counter);
		if (res == FCSERR_OK) {
			break;
		} else {
			FCS_LOG_ERR("Retry get keystore counter\n");
			retry_cnt--;
		}
	} while (retry_cnt > 0);

	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get keystore counter\n");
		return res;
	}

	snprintf(val, GETVAR_VALUE_SIZE, "%u", ks_counter);

	return res;
}

static int fastboot_get_keystore_xcs(char *val)
{
	int res = FCSERR_OK;
	uint32_t is_xcs_rot;

	if (!val) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	res = sec_data_get_xcs_rot(&is_xcs_rot);

	if (res != FCSERR_OK) {
		FCS_LOG_INF("Failed to get xcs rot\n");
		return res;
	}

	snprintf(val, GETVAR_VALUE_SIZE, "%s", is_xcs_rot ? "yes" : "no");

	return res;
}

static int fastboot_get_sake_root(char *val)
{
	struct authenticate_ctx *auth_ctx = NULL;
	int res = FCSERR_OK;

	res = authenticate_init(&auth_ctx, SAKE_SSN_PRODUCTION,
				BUILD_NUMBER, strlen(BUILD_NUMBER));
	if (res != FCSERR_OK) {
		res = -FCSERR_ESTATE;
		goto exit;
	}

	res = authenticate_get_sake_root_name(
			&auth_ctx, val, GETVAR_VALUE_SIZE);
exit:
	authenticate_destroy(auth_ctx);
	return res;
}

static int fastboot_get_default_security(char *val)
{
	int res = FCSERR_OK;

	res = get_default_security(val, GETVAR_VALUE_SIZE);

	if (res < 0)
		FCS_LOG_ERR("Failed to get default security\n");

	return res;
}

static int fastboot_get_s1_root(char *val)
{
	int res = FCSERR_OK;

	res = get_s1_root(val, GETVAR_VALUE_SIZE);

	if (res < 0)
		FCS_LOG_ERR("Failed to get S1_Root\n");

	return res;
}

static int fastboot_get_security_state(char *val)
{
	int res = FCSERR_OK;
	struct ks_ctx *ks_ctx = NULL;
	uint8_t sha256hash[SHA256_HASH_OUT_SIZE];
	uint8_t *hmac_key = NULL;
	uint32_t hmac_key_len = 0;
	int retry_cnt = MAX_RETRY_COUNT;

	res = core_get_hmac_key(&hmac_key, &hmac_key_len);
	if (res != FCSERR_OK) {
		hmac_key = NULL;
		hmac_key_len = 0;
		FCS_LOG_INF("Can't get hmac key: (%d)\n", res);
	}

	do {
		res = ksutil_keystore_init(&ks_ctx, true, XFLKEYSTORE_PRIM,
				hmac_key, hmac_key_len);
		if (res == FCSERR_OK) {
			break;
		} else {
			FCS_LOG_ERR("Retry hmac key\n");
			retry_cnt--;
		}
	} while (retry_cnt > 0);

	if (res != FCSERR_OK) {
		FCS_LOG_ERR("keystore init failed: (%d)\n", res);
		goto exit;
	}

	res = ks_get_hash(ks_ctx, sha256hash, SHA256_HASH_OUT_SIZE);
	if (res < 0) {
		FCS_LOG_ERR("Failed to get keystore hash (%d)\n", res);
		goto exit;
	}

	res = base64_encode(sha256hash,
				SHA256_HASH_OUT_SIZE,
				val,
				GETVAR_VALUE_SIZE);

exit:
	free(hmac_key);
	ks_destroy(ks_ctx);
	return res;
}


static int fastboot_get_stored_security_state(char *val)
{
	int res = FCSERR_OK;
	uint8_t sha256hash[SHA256_HASH_OUT_SIZE];

	res = sec_data_get_keystore_hash(sha256hash, SHA256_HASH_OUT_SIZE);

	if (res == FCSERR_OK)
		res = base64_encode(sha256hash,
				SHA256_HASH_OUT_SIZE,
				val,
				GETVAR_VALUE_SIZE);

	return res;
}

static int fastboot_get_usb_version(char *val)
{
	return fcs_usb_version(val, GETVAR_VALUE_SIZE);
}

static int fastboot_get_battery_capacity(char *val)
{
	return get_battery_capacity(val, GETVAR_VALUE_SIZE);
}

static int fastboot_get_current_slot(char *val)
{
	int res = FCSERR_OK;
	char active_slot;

	if (!val) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	res = ab_get_active(&active_slot);
	if (res != FCSERR_OK) {
		FCS_LOG_INF("Failed to get active slot\n");
		return res;
	}

	snprintf(val, GETVAR_VALUE_SIZE, "%c", active_slot);

	return FCSERR_OK;
}

static int fastboot_get_slot_successful(char slot, char *val)
{
	int res = FCSERR_OK;
	bool successful;

	if (!val) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	res = ab_get_successful(slot, &successful);
	if (res != FCSERR_OK) {
		FCS_LOG_INF("Failed to get successful slot\n");
		return res;
	}

	snprintf(val, GETVAR_VALUE_SIZE, "%s", successful ? "yes" : "no");

	return res;
}

static int fastboot_get_slot_successful_a(char *val)
{
	return fastboot_get_slot_successful('a', val);
}

static int fastboot_get_slot_successful_b(char *val)
{
	return fastboot_get_slot_successful('b', val);
}

static int fastboot_get_slot_unbootable(char slot, char *val)
{
	int res = FCSERR_OK;
	bool unbootable;

	if (!val) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	res = ab_get_unbootable(slot, &unbootable);
	if (res != FCSERR_OK) {
		FCS_LOG_INF("Failed to get unbootable slot\n");
		return res;
	}

	snprintf(val, GETVAR_VALUE_SIZE, "%s", unbootable ? "yes" : "no");

	return res;
}

static int fastboot_get_slot_unbootable_a(char *val)
{
	return fastboot_get_slot_unbootable('a', val);
}

static int fastboot_get_slot_unbootable_b(char *val)
{
	return fastboot_get_slot_unbootable('b', val);
}

static int fastboot_get_slot_retry_count(char slot, char *val)
{
	int res = FCSERR_OK;
	int retry_count;

	if (!val) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	res = ab_get_retry_count(slot, &retry_count);
	if (res != FCSERR_OK) {
		FCS_LOG_INF("Failed to get retry count, (%d)\n", res);
		return res;
	}

	snprintf(val, GETVAR_VALUE_SIZE, "%d", retry_count);

	return res;
}

static int fastboot_get_slot_retry_count_a(char *val)
{
	return fastboot_get_slot_retry_count('a', val);
}

static int fastboot_get_slot_retry_count_b(char *val)
{
	return fastboot_get_slot_retry_count('b', val);
}


static int fastboot_get_rollback_index_count(char *val)
{
	if (!val) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}
	snprintf(val, GETVAR_VALUE_SIZE, "%u",
		 sec_data_get_num_rollback_counters());
	return FCSERR_OK;
}

static int fastboot_get_x_conf(char *val)
{
	uint8_t hash[4]; /* maximum 2 roots included */
	int res;
	int nroots;

	if (!val) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	res = get_x_conf_root_hash(hash, sizeof(hash), &nroots);
	if (res != FCSERR_OK)
		return res;

	/* due to legacy requirements the test root (if available) needs to be
	 * written first and get_x_conf_root_hash will output in reverse order,
	 * so make the switch if needed here
	 */
	snprintf(val, GETVAR_VALUE_SIZE, "%02x%02x",
		 hash[2 * (nroots - 1)], hash[2 * (nroots - 1) + 1]);
	if (nroots == 2)
		snprintf(val + 4, GETVAR_VALUE_SIZE, ",%02x%02x",
			 hash[0], hash[1]);

	return FCSERR_OK;
}

static int fastboot_get_rollback_counter(const char *index, char *val)
{
	int res;
	uint32_t rb_index;
	uint64_t rb_cnt_val;

	if (!index || !val) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	rb_index = strtol(index, NULL, 10);

	res = sec_data_get_rollback_counter(rb_index, &rb_cnt_val);
	if (res != FCSERR_OK)
		return res;

	snprintf(val, GETVAR_VALUE_SIZE, "%" PRIu64, rb_cnt_val);
	return res;
}

static int fastboot_get_suid(char *val)
{
	int res;
	uint8_t bbuf[(GETVAR_VALUE_SIZE - 1) / 2];

	if (!val) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	res = read_suid_data(bbuf, sizeof(bbuf));
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to read suid from RPMB (%d)\n", res);
		return res;
	}

	res = bin_to_ascii(val, GETVAR_VALUE_SIZE, bbuf, get_suid_len());

	return res;
}

static int fastboot_get_sd_status(char *val)
{
	int res = FCSERR_OK;
	bool has_card = true;

	if (!val) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	res = core_has_sd_card(&has_card);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get SD-card status (%d)\n", res);
		return res;
	}

	snprintf(val, GETVAR_VALUE_SIZE, "%s", (has_card ? "yes" : "no"));

	return res;
}

static void fastboot_init_getvar(void)
{
	fastboot_add_func("version", fastboot_get_version);
	fastboot_add_func("max-download-size", fastboot_get_maxdownloadsize);
	fastboot_add_func("Version-sony", fastboot_get_sonyversion);
	fastboot_add_func("Loader-version", fastboot_get_loaderversion);
	fastboot_add_func("serialno", fastboot_get_serialno);
	fastboot_add_func("version-bootloader", fastboot_get_bootversion);
	fastboot_add_func("version-baseband", fastboot_get_swversion);
	fastboot_add_func("product", fastboot_get_product_name);
	fastboot_add_func("Phone-id", fastboot_get_phoneid);
	fastboot_add_func("Rooting-status", fastboot_get_rootingstatus);
	fastboot_add_func("Has-been-unlocked", fastboot_get_has_been_unlocked);
	fastboot_add_func("Device-id", fastboot_get_deviceid);
	fastboot_add_func("Platform-id", fastboot_get_platformid);
	fastboot_add_func("Frp-partition", fastboot_get_frp_partition);
	fastboot_add_func("secure", fastboot_get_secure);
	fastboot_add_func("Sector-size", fastboot_get_sector_size);
	if (strncmp(FLASH_TYPE, "UFS", strlen("UFS") + 1) == 0)
		fastboot_add_func("Ufs-info", fastboot_get_storage_info);
	if (strncmp(FLASH_TYPE, "eMMC", strlen("eMMC") + 1) == 0)
		fastboot_add_func("Emmc-info", fastboot_get_storage_info);
	fastboot_add_func("Keystore-counter", fastboot_get_keystore_counter);
	fastboot_add_func("Keystore-xcs", fastboot_get_keystore_xcs);
	fastboot_add_func("Sake-root", fastboot_get_sake_root);
	fastboot_add_func("Default-security", fastboot_get_default_security);
	fastboot_add_func("S1-root", fastboot_get_s1_root);
	fastboot_add_func("Security-state", fastboot_get_security_state);
	fastboot_add_func("USB-version", fastboot_get_usb_version);
	fastboot_add_func("Battery", fastboot_get_battery_capacity);
	fastboot_add_func("slot-count", fastboot_get_slot_count);
	fastboot_add_func("current-slot", fastboot_get_current_slot);
	fastboot_add_func("slot-successful:a", fastboot_get_slot_successful_a);
	fastboot_add_func("slot-successful:b", fastboot_get_slot_successful_b);
	fastboot_add_func("slot-unbootable:a", fastboot_get_slot_unbootable_a);
	fastboot_add_func("slot-unbootable:b", fastboot_get_slot_unbootable_b);
	fastboot_add_func("slot-retry-count:a",
		fastboot_get_slot_retry_count_a);
	fastboot_add_func("slot-retry-count:b",
		fastboot_get_slot_retry_count_b);
	fastboot_add_func("Stored-security-state",
		fastboot_get_stored_security_state);
	fastboot_add_func("Rollback-index-count",
		fastboot_get_rollback_index_count);
	fastboot_add_func("X-conf", fastboot_get_x_conf);
	fastboot_add_func("Soc-unique-id", fastboot_get_suid);
	fastboot_add_func("SD-card-inserted", fastboot_get_sd_status);
}

static int fastboot_init_commands(void)
{
	int res;

	res = fastboot_add_cmd(CMD_FORMAT_TA,
		handle_format_ta,
		AUTH_LEVEL_PRODUCTION);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_ERASE,
		handle_erase,
		AUTH_LEVEL_PRODUCTION);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_SECURE_ERASE,
		handle_secure_erase,
		AUTH_LEVEL_PRODUCTION);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_ERASE_SECTOR,
		handle_erase_sector,
		AUTH_LEVEL_PRODUCTION);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_SECURE_ERASE_SECTOR,
		handle_secure_erase_sector,
		AUTH_LEVEL_PRODUCTION);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_REPARTITION,
		handle_repartition,
		AUTH_LEVEL_PRODUCTION);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_FLASH,
		handle_flash,
		AUTH_LEVEL_PRODUCTION);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_SET_SECURITY,
		handle_set_security,
		AUTH_LEVEL_PRODUCTION);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_READ_PARTITION,
		handle_read_partition,
		AUTH_LEVEL_PRODUCTION);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_READ_SECTOR,
		handle_read_sector,
		AUTH_LEVEL_PRODUCTION);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_READ_ALL_TA,
		handle_read_all_ta,
		AUTH_LEVEL_NONE);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_GETVAR,
		handle_getvar,
		AUTH_LEVEL_NONE);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_DOWNLOAD,
		handle_download,
		AUTH_LEVEL_NONE);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_READ_TA,
		handle_read_ta,
		AUTH_LEVEL_NONE);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_WRITE_TA,
		handle_write_ta,
		AUTH_LEVEL_NONE);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_POWERDOWN,
		handle_powerdown,
		AUTH_LEVEL_NONE);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_REBOOT_BOOTLOADER,
		handle_reboot_bootloader,
		AUTH_LEVEL_NONE);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_REBOOT_VENDOR_BOOTLOADER,
		handle_reboot_vendor_bootloader,
		AUTH_LEVEL_NONE);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_REBOOT_RECOVERY,
		handle_reboot_recovery,
		AUTH_LEVEL_NONE);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_REBOOT_FASTBOOT,
		handle_reboot_fastboot,
		AUTH_LEVEL_NONE);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_REBOOT,
		handle_reboot,
		AUTH_LEVEL_NONE);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_CONTINUE,
		handle_continue,
		AUTH_LEVEL_NONE);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_GET_PARTITION_LIST,
		handle_get_partition_list,
		AUTH_LEVEL_NONE);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_GETLOG,
		handle_getlog,
		AUTH_LEVEL_NONE);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_GETNVLOG,
		handle_getnvlog,
		AUTH_LEVEL_NONE);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_DIGEST,
		handle_digest,
		AUTH_LEVEL_NONE);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_SIGNATURE_DL,
		handle_signature_download,
		AUTH_LEVEL_NONE);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_SIGNATURE,
		handle_signature,
		AUTH_LEVEL_NONE);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_GPTINFO,
		handle_gptinfo,
		AUTH_LEVEL_NONE);
	if (res != FCSERR_OK)
		return res;

	if (strncmp(FLASH_TYPE, "UFS", strlen("UFS") + 1) == 0) {
		res = fastboot_add_cmd(CMD_GETUFSINFO,
				handle_getstorageinfo,
				AUTH_LEVEL_NONE);
		if (res != FCSERR_OK)
			return res;
	}

	if (strncmp(FLASH_TYPE, "eMMC", strlen("eMMC") + 1) == 0) {
		res = fastboot_add_cmd(CMD_GETEMMCINFO,
				handle_getstorageinfo,
				AUTH_LEVEL_NONE);
		if (res != FCSERR_OK)
			return res;
	}

	res = fastboot_add_cmd(CMD_SAKE_CHALLENGE,
		handle_challenge,
		AUTH_LEVEL_NONE);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_SAKE_RESPONSE,
		handle_response,
		AUTH_LEVEL_NONE);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_GETROOTKEYHASH,
		handle_getrootkeyhash,
		AUTH_LEVEL_NONE);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_CHARGE,
		handle_charge,
		AUTH_LEVEL_NONE);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_OEM_UNLOCK,
		handle_oem_unlock,
		AUTH_LEVEL_PRODUCTION);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_OEM_LOCK,
		handle_oem_lock,
		AUTH_LEVEL_PRODUCTION);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_SYNC,
		handle_sync,
		AUTH_LEVEL_NONE);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_SET_ACTIVE,
		handle_set_active,
		AUTH_LEVEL_NONE);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_RESET_ROLLBACK_COUNTER,
		handle_reset_rollback_counter,
		AUTH_LEVEL_CUSTOMER_SERVICE);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_RESET_FRP,
		handle_reset_frp,
		AUTH_LEVEL_CUSTOMER_SERVICE);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_SET_SHIP_MODE,
		handle_set_ship_mode,
		AUTH_LEVEL_NONE);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_ENABLE_DISPLAY,
		handle_enable_display,
		AUTH_LEVEL_PRODUCTION);
	if (res != FCSERR_OK)
		return res;

	res = fastboot_add_cmd(CMD_DISABLE_DISPLAY,
		handle_disable_display,
		AUTH_LEVEL_PRODUCTION);
	if (res != FCSERR_OK)
		return res;

	return res;
}

struct protocol *prot_init()
{
	struct protocol *ctx = calloc(1, sizeof(struct protocol));

	if (!ctx) {
		FCS_LOG_ERR("calloc of handle failed\n");
		return NULL;
	}

	ctx->tr_hdl = tr_open();
	if (!ctx->tr_hdl) {
		FCS_LOG_ERR("tr_open failed\n");
		free(ctx);
		return NULL;
	}
	ctx->data_left = 0;

	fastboot_init_getvar();

	if (fastboot_init_commands() != FCSERR_OK) {
		free(ctx);
		return NULL;
	}

	return ctx;
}

void prot_final(struct protocol *ctx)
{
	tr_close(ctx->tr_hdl);
}

int prot_receive_cmd(struct protocol *ctx)
{
	int res;

	if (!ctx) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	res = tr_read(ctx->tr_hdl, ctx->cmd, FASTBOOT_BUFFER_SIZE);
	if (res < 0) {
		res = -FCSERR_EIO;
		return res;
	}
	ctx->cmd[res] = '\0';

	res = fcsgfx_log((char *)ctx->cmd, true);
	if (res != FCSERR_OK)
		FCS_LOG_WRN("fcsgfx_log failed %d\n", res);

	return FCSERR_OK;
}

static int prot_receive_data(struct protocol *ctx)
{
	int res = FCSERR_OK;
	int data_read, data_written = 0;
	unsigned int buffer_size;
	struct storage_ctx *rdctx = NULL; /* ramdisk context */
	uint8_t *buf = NULL;

	if (!ctx) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	if (ctx->data_left == 0) {
		(void)storage_unlink_by_name(FASTBOOT_TMP_STORAGE,
					STORAGE_RAMDISK_NAME);
		return FCSERR_OK;
	}

	buffer_size = (ctx->data_left < get_max_download_size()) ?
		ctx->data_left : get_max_download_size();

	buf = (uint8_t *)malloc(buffer_size);
	if (buf == NULL) {
		FCS_LOG_ERR("Out of memory!\n");
		FB_GEN_RESP(ctx, "FAILOut of memory");
		res = -FCSERR_ENOMEM;
		return res;
	}

	(void)storage_unlink_by_name(FASTBOOT_TMP_STORAGE,
					STORAGE_RAMDISK_NAME);
	rdctx = storage_open_by_name(FASTBOOT_TMP_STORAGE,
					STORAGE_RAMDISK_NAME);
	if (rdctx == NULL) {
		FCS_LOG_ERR("Unable to open ramdisk file %s\n",
				STORAGE_RAMDISK_NAME);
		FB_GEN_RESP(ctx, "FAILRamdisk open failed");
		res = -FCSERR_EIO;
		goto prot_receive_data_error;
	}

	do {
		/*
		 * Get data from USB
		 */
		data_read = tr_read(ctx->tr_hdl,
				buf,
				(ctx->data_left < tr_get_max_read_size()) ?
				ctx->data_left : tr_get_max_read_size());
		if (data_read < 0) {
			res = data_read;
			FB_GEN_RESP(ctx, "FAILRead fail");
			goto prot_receive_data_error;
		}

		/*
		 * Calculate how much data is left to read.
		 */
		ctx->data_left = ctx->data_left - data_read;

		/*
		 * Write data to file in ramdisk
		 */
		data_written = storage_write(rdctx, buf, data_read);
		if (data_written != data_read) {
			FCS_LOG_ERR("Write fail\n");
			FB_GEN_RESP(ctx, "FAILWrite fail");
			res = -FCSERR_EIO;
			goto prot_receive_data_error;
		}
	} while (ctx->data_left);

prot_receive_data_error:
	if (rdctx != NULL)
		storage_close(rdctx);
	free(buf);

	return res;
}

static int prot_send_data(struct protocol *ctx, uint8_t *buf, uint32_t size)
{
	int data_written;
	uint32_t offset = 0;
	int chunk_size;

	if (!ctx || !buf || (size == 0)) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}


	do {
		if (size > MAX_USB_WRITE)
			chunk_size = MAX_USB_WRITE;
		else
			chunk_size = size;

		data_written = tr_write(ctx->tr_hdl, buf + offset, chunk_size);

		if (data_written != chunk_size) {
			FCS_LOG_ERR("Failed to send data (%d)\n", data_written);
			FB_GEN_RESP(ctx, "FAILSend data");
			return -FCSERR_EIO;
		}

		offset += chunk_size;
		size -= chunk_size;

	} while (size != 0);

	return FCSERR_OK;
}

static int handle_digest(struct loader_ctx *ldr_ctx)
{
	int res;
	uint8_t digest[SHA256_HASH_OUT_SIZE];
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	if (strlen((char *)ctx->cmd) <= strlen(CMD_DIGEST)) {
		FCS_LOG_ERR("Invalid parameters\n");
		FB_GEN_RESP(ctx, "FAILInvalid input parameters");
		res = -FCSERR_EINVAL;
		return res;
	}

	res = pu_digest_partition(
		(char *)&ctx->cmd[strlen(CMD_DIGEST)],
		digest, sizeof(digest));
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get digest\n");
		FB_GEN_RESP(ctx, "FAILFailed to get digest");
		return res;
	}

	/* Send response */
	FB_GEN_RESP(ctx, "DATA%08x", SHA256_HASH_OUT_SIZE);
	res = prot_send_response(ctx);
	if (res != FCSERR_OK)
		return res;

	res = prot_send_data(ctx, digest, SHA256_HASH_OUT_SIZE);
	if (res != FCSERR_OK)
		goto exit;

	FB_GEN_RESP(ctx, "OKAY");
exit:
	return res;
}

int prot_proc_cmd(struct loader_ctx *ldr_ctx)
{
	int res = FCSERR_OK;
	struct fastboot_command_entry *cmd;
	bool cmd_found = false;
	bool cmd_auth = false;
	char *part = NULL;
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

#ifdef CFG_FASTBOOT_MEASURE_TIME
	clock_t start = clock();
	clock_t stop;
#endif

	if (list_empty(&fastboot_cmd_list)) {
		FCS_LOG_ERR("Fastboot command list is empty\n");
		return -FCSERR_EINVAL;
	}

	LIST_FOR_EACH_DATA(&fastboot_cmd_list, cmd, list) {
		if (FB_PARSE_CMD(cmd->name, ctx->cmd)) {
			cmd_found = true;
			res = check_cmd_auth(ldr_ctx, cmd, &cmd_auth);

			if (res != FCSERR_OK) {
				if (res == -FCSERR_EVHSH)
					FB_GEN_RESP(ctx,
					"FAILCheck payload hash");
				else if (res == -FCSERR_EINVAL)
					FB_GEN_RESP(ctx,
					"FAILInvalid parameters");
				else
					FB_GEN_RESP(ctx,
					"FAILCheck cmd authentication");
				return res;
			}

			if (cmd_auth) {
				res = cmd->handle(ldr_ctx);
				/*
				 * If this command fails and it was in an
				 * attempt to flash a sparse image with multiple
				 * sparse files, the partition needs to be
				 * removed from auth-list here.
				 */
				if (res != FCSERR_OK) {
					part = get_string_arg_from_cmd(
							CMD_FLASH,
							ctx->cmd);
					if (part)
						res = remove_auth_partition(
								part);
				}

#ifdef CFG_FASTBOOT_MEASURE_TIME
				stop = clock();
				FCS_LOG("cmd %s took %d us\n",
					ctx->cmd, stop - start);
#endif

				goto exit;
			}

			FCS_LOG_ERR(
				"Authentication required for command %s\n",
				ctx->cmd);
			FB_GEN_RESP(ctx, "FAILCommand not authenticated");
			res = -FCSERR_AUTH;

		}
	}

	if (cmd_found == false) {
		FCS_LOG_ERR("NOT SUP %s\n", ctx->cmd);
		res = handle_notsupported(ctx);
	}

exit:
	free(part);

	return res;
}

int prot_send_response(struct protocol *ctx)
{
	int res;

	if (!ctx) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	res = tr_write(ctx->tr_hdl, ctx->resp, strlen((const char *)ctx->resp));
	if (res < 0) {
		FCS_LOG_ERR("Send response fail (%d)\n", res);
		FB_GEN_RESP(ctx, "FAILSend response");
		res = -FCSERR_EIO;
	} else {

		res = fcsgfx_log((char *)ctx->resp, true);
		if (res != FCSERR_OK)
			FCS_LOG_WRN("fcsgfx_log failed %d\n", res);

		/* Ignore the errors from fcsgfx_log */
		res = FCSERR_OK;
		/*
		 * Set buffer to 0.
		 */
		memset(ctx->resp, 0, FASTBOOT_BUFFER_SIZE+1);
	}

	return res;
}

/*
 * Commits data to flash
 */
static int handle_flash(struct loader_ctx *ldr_ctx)
{
	int res = FCSERR_OK;
	size_t part_name_len;
	char *partition = NULL;
	struct storage_ctx *hctx = NULL;
	ssize_t file_size, data_read;
	uint8_t *file_buf = NULL;
	char slot;
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	if (strlen((char *)ctx->cmd) > strlen(CMD_FLASH))
		part_name_len = strlen((char *)ctx->cmd) - strlen(CMD_FLASH);
	else {
		FCS_LOG_ERR("Input value fail\n");
		FB_GEN_RESP(ctx, "FAILInput value fail");
		return -FCSERR_EINVAL;
	}

	partition = (char *)calloc(1, part_name_len + 1);
	if (partition == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		FB_GEN_RESP(ctx, "FAILOut of memory");
		return -FCSERR_ENOMEM;
	}
	strlcpy(partition,
			(char *)ctx->cmd+strlen(CMD_FLASH),
			part_name_len + 1);

	/* If it's the boot we treat it special */
	if (is_bootloader(partition)) {
		hctx = storage_open_by_name(FASTBOOT_TMP_STORAGE,
					STORAGE_RAMDISK_NAME);
		if (hctx == NULL) {
			FCS_LOG_ERR("Unable to open file\n");
			FB_GEN_RESP(ctx, "FAILOpen failed");
			return -FCSERR_EINVAL;
		}

		file_size = pu_get_part_size(hctx);
		if (file_size < 0) {
			FCS_LOG_ERR("Failed to get file size (%zd)\n",
				file_size);
			FB_GEN_RESP(ctx, "FAILIO Error");
			res = -FCSERR_EINVAL;
			goto exit;
		}

		file_buf = malloc(file_size);
		if (file_buf == NULL) {
			FCS_LOG_ERR("Out of memory\n");
			FB_GEN_RESP(ctx, "FAILOut of memory");
			res = -FCSERR_ENOMEM;
			goto exit;
		}

		data_read = storage_read(hctx, file_buf, file_size);
		if (data_read != file_size) {
			FCS_LOG_ERR("IO Error\n");
			FB_GEN_RESP(ctx, "FAILIO Error");
			res = -FCSERR_EIO;
			goto exit;
		}

		/* If we have slots this will be it */
		slot = partition[strlen(partition) - 1];
		res = do_safe_boot_upgrade(file_buf, file_size,
				ctx->erase_type, slot);
		/* Clear erase_type */
		ctx->erase_type = SB_ERASE_NONE;
		if (res == FCSERR_OK)
			FB_GEN_RESP(ctx, "OKAY");
		else
			FB_GEN_RESP(ctx, "FAILBoot update failed");

		storage_close(hctx);
		goto exit;
	}

	res = write_to_flash(ctx, partition);
	if (res) {
		FCS_LOG_ERR("Failed to write to flash\n");
		goto exit;
	}

	res = reset_slot_parameters(partition);
	if (res) {
		FCS_LOG_ERR("Failed to reset slot parameters. (%d)\n", res);
		FB_GEN_RESP(ctx, "FAILSlot parameters not updated\n");
		goto exit;
	}

exit:
	free(file_buf);
	free(partition);

	return res;
}

static int write_to_flash(struct protocol *ctx, const char *partition)
{
	int res = FCSERR_OK;
	struct storage_ctx *rdctx = NULL; /* ramdisk context */
	uint8_t *buf = NULL;
	ssize_t buf_size, bytes_read, bytes_left, partition_size;
	uint32_t offset = 0;

	if (!ctx) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	/*
	 * Open partition if it exists, do nothing if it is already opened
	 * and return error if it isn't open and doesn't exist.
	 */
	if (ctx->sctx == NULL) {
		ctx->sctx = storage_open_by_name(NULL, partition);
	} else if ((partition == NULL && storage_get_name(ctx->sctx) == NULL) ||
		   (partition != NULL &&
		    strncmp(storage_get_name(ctx->sctx), partition,
			    strlen(partition)))) {
		write_to_flash_final(ctx);
		ctx->sctx = storage_open_by_name(NULL, partition);
	}

	if (ctx->sctx == NULL) {
		FCS_LOG_ERR("Partition does not exist\n");
		if (partition)
			FCS_LOG_ERR("Partition: %s\n", partition);
		FB_GEN_RESP(ctx, "FAILPartition does not exist.");
		return -FCSERR_EINVAL;
	}

	partition_size = pu_get_part_size(ctx->sctx);
	if (partition_size < 0) {
		FCS_LOG_ERR("IO Error\n");
		FB_GEN_RESP(ctx, "FAILIO Error");
		res = -FCSERR_EIO;
		goto handle_flash_error;
	}

	rdctx = storage_open_by_name(FASTBOOT_TMP_STORAGE,
				STORAGE_RAMDISK_NAME);
	if (rdctx == NULL) {
		FCS_LOG_ERR("Unable to open ramdisk file %s\n",
				STORAGE_RAMDISK_NAME);
		FB_GEN_RESP(ctx, "FAILRamdisk open failed");
		return -FCSERR_EINVAL;
	}

	bytes_left = pu_get_part_size(rdctx);
	if (bytes_left < 0) {
		FCS_LOG_ERR("IO Error\n");
		FB_GEN_RESP(ctx, "FAILIO Error");
		res = -FCSERR_EIO;
		goto handle_flash_error;
	}

	if (bytes_left > partition_size) {
		FCS_LOG_ERR("File does not fit in partition\n");
		FB_GEN_RESP(ctx, "FAILFile does not fit in partition");
		res = -FCSERR_EPART;
		goto handle_flash_error;
	}

	buf_size = (bytes_left < (ssize_t)get_max_download_size()) ?
		bytes_left : (ssize_t)get_max_download_size();
	buf = (uint8_t *)malloc(buf_size);
	if (buf == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		FB_GEN_RESP(ctx, "FAILOut of memory");
		res = -FCSERR_ENOMEM;
		goto handle_flash_error;
	}

	if (partition != NULL) {
		res = pre_flash_handler(ctx->sctx, partition, &offset);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Pre-flash handler failed (%d)\n", res);
			FB_GEN_RESP(ctx, "FAILPre-flash handler failed");
			res = -FCSERR_EIO;
			goto handle_flash_error;
		}
	}

	do {
		bytes_read = storage_read(rdctx, buf, buf_size);
		if (bytes_read < 0) {
			FCS_LOG_ERR("Read fail\n");
			FB_GEN_RESP(ctx, "FAILRead fail");
			res = -FCSERR_EIO;
			goto handle_flash_error;
		}

		res = write_image(ctx->sctx, buf, offset, bytes_read);
		if (res) {
			FCS_LOG_ERR("Write fail: %x\n", res);
			FB_GEN_RESP(ctx, "FAILWrite fail");
			res = -FCSERR_EIO;
			goto handle_flash_error;
		}
		bytes_left -= bytes_read;
	} while (bytes_left);

	FB_GEN_RESP(ctx, "OKAY");

handle_flash_error:
	free(buf);
	storage_close(rdctx);
	if (res)
		write_to_flash_final(ctx);

	return res;
}

static void write_to_flash_final(struct protocol *ctx)
{
	if (ctx && ctx->sctx) {
		storage_close(ctx->sctx);
		ctx->sctx = NULL;
	}
}

/*
 * Should return ramdisk size if no other constraint is known.
 */
static unsigned int get_max_download_size(void)
{
	size_t maxdls = MAX_DLS;

	return maxdls;
}

/*
 * This function will not return until complete image is downloaded to ramdisk.
 * Host:   "download:00001234"
 * Client: "DATA00001234"
 * Host:   < 0x1234 bytes >
 * handle_download returns when all data is received
 */
static int handle_download(struct loader_ctx *ldr_ctx)
{
	int res = FCSERR_OK;
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	if (strlen((const char *)ctx->cmd) !=
			strlen("download:0123ABCD")) {
		res = -FCSERR_EINVAL;
		FCS_LOG_ERR("Invalid parameters\n");
		FB_GEN_RESP(ctx, "FAILInvalid parameters");
		return res;
	}

	res = hex2uint((const char *)ctx->cmd +
			strlen(CMD_DOWNLOAD),
			&(ctx->data_left));
	if (res < 0) {
		FCS_LOG_ERR("Invalid parameters\n");
		FB_GEN_RESP(ctx, "FAILInvalid parameters");
		return res;
	}

	/* Make sure we don't receive too large requests */
	if (ctx->data_left > get_max_download_size()) {
		FCS_LOG_ERR("Too large download request\n");
		FB_GEN_RESP(ctx, "FAILToo large download request");
		res = -FCSERR_EINVAL;
		return res;
	}

	/*
	 * Reply "DATA0123ABCD" if it's OK to receive 0123ABCD Bytes of data.
	 */
	FB_GEN_RESP(ctx, "DATA%s",
		    (const char *)ctx->cmd + strlen(CMD_DOWNLOAD));

	res = prot_send_response(ctx);
	if (res != FCSERR_OK)
		return res;

	res = prot_receive_data(ctx);
	if (res < 0)
		return res;

	FB_GEN_RESP(ctx, "OKAY");

	/*
	 * Return and let main protocol loop handle response.
	 */

	return res;
}

static int get_partition_list(struct protocol *ctx, uint8_t *ptn_list,
				size_t *len)
{
	int res = FCSERR_OK;
	struct storage_dir *d;
	struct storage_dirent dent = {};

	if (!ctx || !ptn_list || !len) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	d = storage_opendir(NULL);
	if (d == NULL) {
		FCS_LOG_ERR("Invalid dir\n");
		FB_GEN_RESP(ctx, "FAILInvalid dir");
		return -FCSERR_EIO;
	}

	*len = 0;

	do {
		res = storage_readdir(d, &dent);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("storage_readdir failed (%d)\n", res);
			FB_GEN_RESP(ctx, "FAILReaddir failed");
			goto err;
		}
		if (strlen(dent.d_name) != 0) {
			if (*dent.d_name == '.')
				continue;

			if ((*len) + strlen(dent.d_name) + 1 >
			    FB_PART_LIST_SIZE) {
				FCS_LOG_ERR("Overflow (%zd)\n", *len);
				FB_GEN_RESP(ctx, "FAILOverflow");
				goto err;
			}

			memcpy(ptn_list + (*len), dent.d_name,
				strlen(dent.d_name));
			*len += strlen(dent.d_name);
			*(ptn_list + (*len)++) = ',';
		} else if (*len) {
			/* remove trailing ',' at the end */
			*(ptn_list + (--(*len))) = 0;
		}
	} while (strlen(dent.d_name));

	res = storage_closedir(d);
	d = NULL;
	if (res != FCSERR_OK) {
		FB_GEN_RESP(ctx, "FAILIO Error");
		FCS_LOG_ERR("closedir failed (%d)\n", res);
		return res;
	}

err:
	if (d)
		storage_closedir(d);

	return res;
}

static int handle_getvar_all(struct protocol *ctx)
{
	struct fastboot_variable_entry *var;
	int res;
	char value[GETVAR_VALUE_SIZE];

	if (!ctx) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	if (list_empty(&fastboot_var_list)) {
		FCS_LOG_ERR("List empty\n");
		fastboot_send_fail(ctx, "all");
		return FCSERR_OK;
	}

	LIST_FOR_EACH_DATA(&fastboot_var_list, var, list) {
		res = var->get_value(value);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("get_value failed for %s\n", var->name);
		} else {
			FB_GEN_RESP(ctx, "INFO%s:%s", var->name, value);
			res = prot_send_response(ctx);
			if (res != FCSERR_OK)
				return -FCSERR_PERM;
		}
	}

	/*
	 * Special treatment for:
	 * 1 - Rollback-index,
	 * 2 - has-slot and
	 * 3 - partition_info (partition_type and partition_size)
	 */
	res = list_rollback_index_in_getvar_all(ctx);
	if (res != FCSERR_OK)
		FCS_LOG_ERR("list_rollback_index failed (%d)\n", res);

	res = list_has_slot_in_getvar_all(ctx);
	if (res != FCSERR_OK)
		FCS_LOG_ERR("list_has_slot failed (%d)\n", res);

	res = list_partition_info_in_getvar_all(ctx);
	if (res != FCSERR_OK)
		FCS_LOG_ERR("list_partition_info failed (%d)\n", res);

	FB_GEN_RESP(ctx, "OKAY");
	return FCSERR_OK;
}

static int list_has_slot_in_getvar_all(struct protocol *ctx)
{
	int res = FCSERR_OK;
	char value[GETVAR_VALUE_SIZE];
	uint8_t *p_list;
	char *ptn_name = NULL;
	size_t len = 0;

	if (!ctx) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	p_list = calloc(FB_PART_LIST_SIZE, 1);
	if (p_list == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		return -FCSERR_ENOMEM;
	}

	res = get_partition_list(ctx, p_list, &len);
	if (res != FCSERR_OK || !len) {
		FCS_LOG_ERR("get_partition_list failed (%d)\n", res);
		goto err;
	}

	ptn_name = strtok((char *)p_list, ",");
	while (ptn_name != NULL) {
		if (ptn_name[strlen(ptn_name) - 2] == '_') {
			if (ptn_name[strlen(ptn_name) - 1] == 'a')
				ptn_name[strlen(ptn_name) - 2] = '\0';
			else {
				ptn_name = strtok(NULL, ",");
				continue;
			}
		}
		res = fastboot_get_has_slot(ptn_name, value);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("fastboot_get_has_slot failed (%d)\n", res);
			goto err;
		}
		FB_GEN_RESP(ctx, "INFOhas-slot:%s:%s", ptn_name, value);
		res = prot_send_response(ctx);
		if (res != FCSERR_OK)
			goto err;
		ptn_name = strtok(NULL, ",");
	}

	/* Add virtual partition bootloader */
	FB_GEN_RESP(ctx, "INFOhas-slot:%s:yes", BOOT_MAGIC);
	res = prot_send_response(ctx);
	if (res != FCSERR_OK)
		goto err;

	/* Add virtual partition preloader if it exists */
	if (strlen(PRELOADER) > 0) {
		FB_GEN_RESP(ctx, "INFOhas-slot:%s:yes", PRELOADER);
		res = prot_send_response(ctx);
		if (res != FCSERR_OK)
			goto err;
	}

err:
	if (p_list)
		free(p_list);

	return res;
}

static int list_rollback_index_in_getvar_all(struct protocol *ctx)
{
	int res = FCSERR_OK;
	char response[FASTBOOT_BUFFER_SIZE + 1];
	uint32_t rb_index;
	uint64_t rb_cnt_val;
	uint32_t num_rollback_counters = sec_data_get_num_rollback_counters();

	if (!ctx) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	for (rb_index = 0; rb_index < num_rollback_counters; rb_index++) {
		res = sec_data_get_rollback_counter(rb_index, &rb_cnt_val);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR(
				"sec_data_get_rollback_counter failed (%d)\n",
				res);
			return res;
		}
		snprintf(response, FASTBOOT_BUFFER_SIZE + 1,
				"INFORollback-index:%u:%" PRIu64,
				rb_index, rb_cnt_val);
		FB_GEN_RESP(ctx, "%s", response);
		res = prot_send_response(ctx);
		if (res != FCSERR_OK)
			return res;
	}

	return FCSERR_OK;
}

static int list_partition_info_in_getvar_all(struct protocol *ctx)
{
	int res = FCSERR_OK;
	char value[GETVAR_VALUE_SIZE];
	int i;

	if (!ctx) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	/*
	 * Add variables partition-type and partition-size.
	 * Limit the number of partition_info to the number of
	 * allowed partitions to flash and erase on a fused and unlocked
	 * device. This is reasonable than spamming getvar_all result with
	 * partition_info for all available partitions or limiting it
	 * to only two partitions as well.
	 */
	for (i = 0; i < no_of_allowed_ptns; i++) {

		res = fastboot_get_partition_type(allowed_ptns[i], value);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to get partition-type:%s\n",
				allowed_ptns[i]);
			strlcpy(value, "<empty>", GETVAR_VALUE_SIZE);
		}
		FB_GEN_RESP(ctx, "INFOpartition-type:%s:%s",
				allowed_ptns[i], value);
		res = prot_send_response(ctx);
		if (res != FCSERR_OK)
			return res;

		res = fastboot_get_partition_size(allowed_ptns[i], value);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to get partition-size:%s\n",
				allowed_ptns[i]);
			strlcpy(value, "<empty>", GETVAR_VALUE_SIZE);
		}
		FB_GEN_RESP(ctx, "INFOpartition-size:%s:%s",
			allowed_ptns[i], value);
		res = prot_send_response(ctx);
		if (res != FCSERR_OK)
			return res;
	}

	return FCSERR_OK;
}

static int handle_getvar(struct loader_ctx *ldr_ctx)
{
	int res = FCSERR_OK;
	char *getvar_var;
	char value[GETVAR_VALUE_SIZE];
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	getvar_var = (char *)((ctx->cmd)+strlen(CMD_GETVAR));

	/* Special treatment for all */
	if (strncmp(getvar_var, "all", strlen("all") + 1) == 0)
		return handle_getvar_all(ctx);

	memset(value, 0, GETVAR_VALUE_SIZE);
	res = fastboot_get_variable(getvar_var, value);
	if (res == FCSERR_OK)
		fastboot_send_okay(ctx, value);
	else
		fastboot_send_fail(ctx, getvar_var);

	return res;
}

static int extract_partition_and_unit(const uint8_t *arg,
		uint8_t *partition,
		uint32_t *unit)
{
	int res = FCSERR_OK;
	char buf[20];
	char *endptr;
	long value;

	if (!arg || !partition || !unit) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	/* First argument should be a partition between 0-9 */

	if (arg[0] < '0' || arg[0] > '9') {
		res = -FCSERR_EINVAL;
		return res;
	}

	*partition = arg[0] - '0';

	/* Next character should be ':' */
	if (arg[1] != ':') {
		res = -FCSERR_EINVAL;
		return res;
	}

	/* Next 1-5 characters should be unit number in decimal */
	/* Make sure we have a null terminated string */
	strlcpy(buf, (const char *)&arg[2], sizeof(buf));

	errno = 0;    /* To distinguish success/failure after call */
	/* Convert to integer */
	value = strtol(buf, &endptr, 10);

	/* Check for various possible errors */
	if ((errno == ERANGE && (value == LONG_MAX || value == LONG_MIN)) ||
	    (errno != 0 && value == 0)) {
		res = -FCSERR_EINVAL;
		return res;
	}

	if (endptr == buf) {
		/* No digits were found */
		res = -FCSERR_EINVAL;
		return res;
	}

	*unit = (uint32_t) value;
	return res;
}

static int parse_args(
		const char *args, int *lun, ssize_t *start, ssize_t *end)
{
	int res = FCSERR_OK;
	size_t arg_len, num_args = 0;
	size_t index = 0;
	const char *args_p;

	if (!args || !lun || !start || !end) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	arg_len = strlen(args);

	/* Determine number of :-separated arguments */
	while (arg_len > index) {
		if (args[index] == ':')
			num_args++;
		index++;
	}

	args_p = args;
	if (num_args == 1) {
		/* No LUN given */
		*lun = -1;
		*start = atoll(args_p);
		while (*args_p++ != ':')
			;
		*end = atoll(args_p);
	} else if (num_args == 2) {
		*lun = atoll(args_p);
		while (*args_p++ != ':')
			;
		*start = atoll(args_p);
		while (*args_p++ != ':')
			;
		*end = atoll(args_p);
	} else {
		FCS_LOG_ERR("Failed to parse arguments\n");
		res = -FCSERR_EINVAL;
	}

	return res;
}

static int handle_format_ta(struct loader_ctx *ldr_ctx)
{
	int res = FCSERR_OK;
	uint8_t partition = 0;
	uint8_t tmp;
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;
	tmp = ctx->cmd[strlen(CMD_FORMAT_TA)];

	/* Partition number should be between 0-9 */
	if (tmp < '0' || tmp > '9' ||
	    ctx->cmd[strlen(CMD_FORMAT_TA) + 1] != '\0') {
		res = -FCSERR_EINVAL;
		FB_GEN_RESP(ctx, "FAILInvalid parameters");
		return res;
	}

	partition = tmp - '0';
	res = format_ta(partition);

	if (res == FCSERR_OK)
		FB_GEN_RESP(ctx, "OKAY");
	else
		FB_GEN_RESP(ctx,
			"FAILUnable to format TA partition %u, err=%d",
			partition, res);

	return res;
}

static int handle_read_ta(struct loader_ctx *ldr_ctx)
{
	int res = FCSERR_OK;
	uint8_t partition;
	uint32_t unit;
	int buf_size;
	uint8_t *buf = NULL;
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	/* Extract partition and unit number from command */
	res = extract_partition_and_unit(&ctx->cmd[strlen(CMD_READ_TA)],
		&partition, &unit);

	if (res != FCSERR_OK) {
		FB_GEN_RESP(ctx,
			"FAILUnable to extract partition and/or unit");
		FCS_LOG_ERR("%s\n", ctx->resp);
		goto exit_handle_read_ta;
	}

	FCS_LOG_INF("%s: partition=%u, unit=%u\n", __func__, partition, unit);

	/* Get size of unit */
	res = get_ta_unit_size(partition, unit, &buf_size);
	if (res != FCSERR_OK) {
		FB_GEN_RESP(ctx,
			"FAILUnable to get size of TA unit %u, error=%d",
			unit, res);
		FCS_LOG_ERR("%s\n", ctx->resp);
		res = -FCSERR_EINVAL;
		goto exit_handle_read_ta;
	}

	buf = (uint8_t *)malloc(buf_size);
	if (buf == NULL) {
		FB_GEN_RESP(ctx, "FAILOut of memory");
		FCS_LOG_ERR("%s\n", ctx->resp);
		res = -FCSERR_ENOMEM;
		goto exit_handle_read_ta;
	}

	/* Read TA unit */
	res = read_ta(partition, unit, buf, buf_size);
	if (res == -FCSERR_ENOTF) {
		FB_GEN_RESP(ctx, "FAILUnit %u does not exist", unit);
		FCS_LOG_INF("%s\n", ctx->resp);
		/* This is not an error */
		res = FCSERR_OK;
		goto exit_handle_read_ta;
	}

	if (res != FCSERR_OK) {
		FB_GEN_RESP(ctx, "FAILUnable to read TA unit %u, error=%d",
			unit, res);
		FCS_LOG_INF("%s\n", ctx->resp);
		goto exit_handle_read_ta;
	}

	/* Reply with size of data to send data */
	FB_GEN_RESP(ctx, "DATA%08x", buf_size);

	res = prot_send_response(ctx);
	if (res  != FCSERR_OK)
		goto exit_handle_read_ta;


	if (buf_size) {
		res = prot_send_data(ctx, buf, buf_size);
		if (res != FCSERR_OK)
			goto exit_handle_read_ta;
	}

	FB_GEN_RESP(ctx, "OKAY");

exit_handle_read_ta:

	free(buf);
	return res;
}

static int handle_read_all_ta(struct loader_ctx *ldr_ctx)
{
	int res = FCSERR_OK;
	uint8_t partition;
	uint8_t tmp;
	uint8_t *buf = NULL;
	int buf_size = 0;
	bool include_hi_ta = false;
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;
	tmp = ctx->cmd[strlen(CMD_READ_ALL_TA)];

	/* Partition number should be between 0-9 */
	if (tmp < '0' || tmp > '9' ||
	    ctx->cmd[strlen(CMD_READ_ALL_TA) + 1] != '\0') {
		res = -FCSERR_EINVAL;
		FB_GEN_RESP(ctx, "FAILInvalid parameters");
		return res;
	}

	partition = tmp - '0';

	/* If we are authenticated for production we read full TA */
	if (ldr_ctx->auth_level == AUTH_LEVEL_PRODUCTION)
		include_hi_ta = true;

	/* Get size of all units */
	res = get_all_ta_size(partition, &buf_size, include_hi_ta);
	if (res != FCSERR_OK) {
		FB_GEN_RESP(ctx,
			"FAILUnable to get size of all TA units, error=%d",
			res);
		FCS_LOG_ERR("%s\n", ctx->resp);
		res = -FCSERR_EINVAL;
		goto exit_handle_read_all_ta;
	}

	if (buf_size > 0) {
		buf = (uint8_t *)malloc(buf_size);
		if (buf == NULL) {
			FB_GEN_RESP(ctx, "FAILOut of memory");
			FCS_LOG_ERR("%s\n", ctx->resp);
			res = -FCSERR_ENOMEM;
			goto exit_handle_read_all_ta;
		}

		/* Read all TA units */
		res = read_all_ta(partition, buf, buf_size, include_hi_ta);
		if (res != FCSERR_OK) {
			FB_GEN_RESP(ctx,
				"FAILUnable to read all TA units, error=%d",
				res);
			FCS_LOG_ERR("%s\n", ctx->resp);
			goto exit_handle_read_all_ta;
		}
	}

	/* Reply with size of data to send data */
	FB_GEN_RESP(ctx, "DATA%08x", buf_size);

	res = prot_send_response(ctx);
	if (res != FCSERR_OK)
		goto exit_handle_read_all_ta;

	if (buf_size > 0) {
		res = prot_send_data(ctx, buf, buf_size);
		if (res != FCSERR_OK)
			goto exit_handle_read_all_ta;
	}

	FB_GEN_RESP(ctx, "OKAY");

exit_handle_read_all_ta:
	free(buf);
	return res;
}

static int handle_write_ta(struct loader_ctx *ldr_ctx)
{
	int res = FCSERR_OK;
	uint8_t partition;
	uint32_t unit;
	uint8_t *buf = NULL;
	struct storage_ctx *rdctx = NULL; /* ramdisk context */
	ssize_t bytes_downloaded;
	ssize_t bytes_read;
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	/* Extract partition and unit number from command */
	res = extract_partition_and_unit(&ctx->cmd[strlen(CMD_WRITE_TA)],
		&partition, &unit);

	if (res != FCSERR_OK) {
		FB_GEN_RESP(ctx, "FAILUnable to extract partition and/or unit");
		FCS_LOG_ERR("%s\n", ctx->resp);
		goto exit_handle_write_ta;
	}

	FCS_LOG_INF("%s: partition=%u, unit=%u\n", __func__, partition, unit);

	/* Open file with downloaded data */
	rdctx = storage_open_by_name(FASTBOOT_TMP_STORAGE,
				STORAGE_RAMDISK_NAME);
	if (rdctx == NULL) {
		FB_GEN_RESP(ctx, "FAILFAILRamdisk open failed");
		FCS_LOG_ERR("%s\n", ctx->resp);
		res = -FCSERR_EINVAL;
		goto exit_handle_write_ta;
	}

	bytes_downloaded = pu_get_part_size(rdctx);
	if (bytes_downloaded < 0) {
		FB_GEN_RESP(ctx, "FAILIO Error");
		FCS_LOG_ERR("%s\n", ctx->resp);
		res = -FCSERR_EIO;
		goto exit_handle_write_ta;
	}

	buf = (uint8_t *)malloc(bytes_downloaded);
	if (buf == NULL) {
		FB_GEN_RESP(ctx, "FAILOut of memory");
		FCS_LOG_ERR("%s\n", ctx->resp);
		res = -FCSERR_ENOMEM;
		goto exit_handle_write_ta;
	}

	bytes_read = storage_read(rdctx, buf, bytes_downloaded);
	if (bytes_read != bytes_downloaded) {
		FB_GEN_RESP(ctx, "FAILRead fail");
		FCS_LOG_ERR("%s\n", ctx->resp);
		res = -FCSERR_EIO;
		goto exit_handle_write_ta;
	}

	res = write_ta(partition, unit, buf, bytes_downloaded);
	if (res != FCSERR_OK) {
		FB_GEN_RESP(ctx, "FAILUnable to write to TA unit %u", unit);
		goto exit_handle_write_ta;
	}

	FB_GEN_RESP(ctx, "OKAY");

exit_handle_write_ta:
	if (rdctx)
		(void)storage_close(rdctx);

	free(buf);
	return res;
}

/*
 * Verify previously downloaded data (CMS, rfc5652)
 * Host:   "signature"
 * Client: "OKAY" / "FAIL<reason>"
 * or
 * Called by "handle_signature_download".
 */
static int handle_signature(struct loader_ctx *ldr_ctx)
{
	int res = FCSERR_OK;
	uint8_t *cmsbuf = NULL;
	size_t cmsbuf_len = 0;
	size_t devid_len = 0;
	uint8_t *devid = NULL;
	struct embed_rootcert_item *embed_rootcert_list = NULL;
	size_t embed_rootcert_list_count = 0;
	struct rule_verifier *rule_handle = NULL;
	uint8_t *rootcerts = NULL;
	size_t rootcerts_length = 0;
	uint8_t *payload = NULL;
	size_t payload_length = 0;
	uint32_t usage;
	char *partition = NULL;
	struct ks_ctx *ks_ctx = NULL;
	struct transport_verifier *transport_handle = NULL;
	uint8_t *hmac_key = NULL;
	uint32_t hmac_key_len = 0;
	struct protocol *ctx;
	struct dev_binding binding = {};

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	res = write_to_buffer(ctx, &cmsbuf, &cmsbuf_len);
	if (res < 0)
		return res;

	res = devid_to_buffer(ctx, &devid, &devid_len);
	if (res < 0)
		goto handle_signature_end;
	binding.die_id = devid;
	binding.die_id_sz = devid_len;

	/*
	 * Verify downloaded CMS data and set up secure flash engine.
	 */

	res = get_embedded_roots(
		&embed_rootcert_list, &embed_rootcert_list_count);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get embedded_roots from env: (%d)\n",
			res);
		FB_GEN_RESP(ctx, "FAILInitialization failure");
		goto handle_signature_end;
	}

	res = core_get_hmac_key(&hmac_key, &hmac_key_len);
	if (res != FCSERR_OK) {
		hmac_key = NULL;
		hmac_key_len = 0;
		FCS_LOG_INF("Can't get hmac key: (%d)\n", res);
	}

	res = ksutil_keystore_init(&ks_ctx, true, XFLKEYSTORE_PRIM,
			hmac_key, hmac_key_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("keystore init failed: (%d)\n", res);
		FB_GEN_RESP(ctx, "FAILFailed to init keystore");
		goto handle_signature_end;
	}

	res = rule_get_roots(RULE_USAGE_FLASH,
			embed_rootcert_list,
			embed_rootcert_list_count,
			ks_ctx,
			&rootcerts,
			&rootcerts_length);
	if (res < 0) {
		FCS_LOG_ERR("Failed to get roots: (%d)\n", res);
		FB_GEN_RESP(ctx, "FAILFailed to init verify");
		goto handle_signature_end;
	}

	res = rule_init(&rule_handle, &binding, RULE_USAGE_FLASH);
	if (res < 0) {
		FCS_LOG_ERR("Failed to init rule session\n");
		FB_GEN_RESP(ctx, "FAILFailed to init verify");
		goto handle_signature_end;
	}

	res = cms_verify(cmsbuf, cmsbuf_len,
				rule_handle,
				rootcerts, rootcerts_length,
				NULL, 0,
				&payload, &payload_length);
	if (res < 0) {
		FCS_LOG_ERR("Failed to verify cms\n");
		FB_GEN_RESP(ctx, "FAILFailed to verify cms");
		goto handle_signature_end;
	}

	res = rule_get_actual_usage(rule_handle, &usage, &partition);
	if (res < 0) {
		FCS_LOG_ERR("Failed to get actual usage\n");
		FB_GEN_RESP(ctx, "FAILFailed to verify usage");
		goto handle_signature_end;
	}

	/* Setup iteration over payload hashes */
	res = transport_init(&transport_handle,
			payload,
			payload_length);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to setup payload verify\n");
		FB_GEN_RESP(ctx, "FAILFailed to verify payload");
		goto handle_signature_end;
	}

	/* Remove partition from auth list if it's already there */
	res = remove_auth_partition(partition);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to remove partition from auth list\n");
		FB_GEN_RESP(ctx, "FAILFailed to remove auth part");
		goto handle_signature_end;
	}

	res = add_auth_partition(partition, transport_handle);
	if (res < 0) {
		FCS_LOG_ERR("Failed to set authenticated part\n");
		FB_GEN_RESP(ctx, "FAILFailed to set auth partition");
		goto handle_signature_end;
	}
	transport_handle = NULL;
	FB_GEN_RESP(ctx, "OKAY");

handle_signature_end:
	transport_deinit(transport_handle);
	free_embedded_roots(&embed_rootcert_list);
	ks_destroy(ks_ctx);
	free(payload);
	free(rootcerts);
	rule_deinit(rule_handle);
	free(devid);
	free(cmsbuf);
	free(hmac_key);
	return res;
}

/*
 * NOTE: This command is obsolete and here only for legacy reasons.
 *
 * This function will not return until complete CMS (rfc5652) is
 * downloaded to ramdisk
 * and verified.
 * Host:   "signature:00001234"
 * Client: "DATA00001234"
 * Host:   < 0x1234 bytes >
 * handle_signature_download returns when all data is received and verified.
 */
static int handle_signature_download(struct loader_ctx *ldr_ctx)
{
	int res;
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	if (strlen((const char *)ctx->cmd) != strlen("signature:0123ABCD")) {
		FCS_LOG_ERR("Invalid parameters\n");
		FB_GEN_RESP(ctx, "FAILInvalid parameters");
		res = -FCSERR_EINVAL;
		return res;
	}

	res = hex2uint((const char *)ctx->cmd + strlen(CMD_SIGNATURE_DL),
			&(ctx->data_left));
	if (res < 0) {
		FCS_LOG_ERR("Invalid parameters\n");
		FB_GEN_RESP(ctx, "FAILInvalid parameters");
		return res;
	}

	/* Make sure we don't receive too large requests */
	if (ctx->data_left > get_max_download_size()) {
		FCS_LOG_ERR("Too large signature request\n");
		FB_GEN_RESP(ctx, "FAILToo large signature request");
		res = -FCSERR_EINVAL;
		return res;
	}

	/*
	 * Reply "DATA0123ABCD" if it's OK to receive 0123ABCD Bytes of data.
	 */
	FB_GEN_RESP(ctx, "DATA%s",
			(const char *)ctx->cmd + strlen(CMD_SIGNATURE_DL));

	res = prot_send_response(ctx);
	if (res != FCSERR_OK)
		return res;

	res = prot_receive_data(ctx);
	if (res < 0)
		return res;

	/* Process the signature just downloaded */
	res = handle_signature(ldr_ctx);

	return res;
}

static int devid_to_buffer(struct protocol *ctx,
		uint8_t **outbuf, size_t *outbuf_len)
{
	int res = FCSERR_OK;
	size_t devid_len = 0;
	uint8_t *devid = NULL;

	if (!ctx || !outbuf || !outbuf_len) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	devid_len = core_get_dieid_len();
	if (devid_len == 0) {
		FCS_LOG_ERR("Failed to alloc devid\n");
		FB_GEN_RESP(ctx, "FAILGet DevID");
		res = -FCSERR_ENOMEM;
		goto devid_to_buffer_end;
	}

	devid = (uint8_t *)malloc(devid_len);
	if (devid == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		FB_GEN_RESP(ctx, "FAILGet DevID");
		res = -FCSERR_ENOMEM;
		goto devid_to_buffer_end;
	}

	res = core_get_dieid(devid, devid_len);
	if (res < 0) {
		FCS_LOG_ERR("Failed to get devid\n");
		FB_GEN_RESP(ctx, "FAILGet DevID");
		goto devid_to_buffer_end;
	}

	*outbuf_len = devid_len;
	*outbuf = devid;
	devid = NULL;

devid_to_buffer_end:
	free(devid);
	return res;
}

static int write_to_buffer(struct protocol *ctx,
		uint8_t **outbuf, size_t *outbuf_len)
{
	int res = FCSERR_OK;
	struct storage_ctx *rdctx = NULL; /* ramdisk context */
	uint8_t *buf = NULL;
	ssize_t bytes_read, buf_size;

	if (!ctx || !outbuf || !outbuf_len) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	rdctx = storage_open_by_name(FASTBOOT_TMP_STORAGE,
			STORAGE_RAMDISK_NAME);
	if (rdctx == NULL) {
		FCS_LOG_ERR("Unable to open ramdisk file %s\n",
				STORAGE_RAMDISK_NAME);
		FB_GEN_RESP(ctx, "FAILRamdisk open failed");
		res = -FCSERR_EINVAL;
		goto write_to_buffer_end;
	}

	buf_size = pu_get_part_size(rdctx);
	if (buf_size < 0) {
		FCS_LOG_ERR("IO Error\n");
		FB_GEN_RESP(ctx, "FAILIO Error");
		res = -FCSERR_EIO;
		goto write_to_buffer_end;
	}


	buf = (uint8_t *)malloc(buf_size);
	if (buf == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		FB_GEN_RESP(ctx, "FAILOut of memory");
		res = -FCSERR_ENOMEM;
		goto write_to_buffer_end;
	}

	bytes_read = storage_read(rdctx, buf, buf_size);
	if (bytes_read < 0) {
		FCS_LOG_ERR("Read fail\n");
		FB_GEN_RESP(ctx, "FAILRead fail");
		res = -FCSERR_EIO;
		goto write_to_buffer_end;
	}

	*outbuf_len = buf_size;
	*outbuf = buf;
	buf = NULL;

	/*
	 * Close partition
	 */

write_to_buffer_end:
	free(buf);
	storage_close(rdctx);

	return res;
}

/*
 * Set security properties of the device according to
 * downloaded data.
 *
 * Host:   "download:00000014"
 * Client: "DATA00000014"
 * Host:   <security properties>
 * Client: "OKAY"
 * Host:   "Set-security"
 * Client: "OKAY"
 */
static int handle_set_security(struct loader_ctx *ldr_ctx)
{
	int res = FCSERR_OK;
	struct storage_ctx *rdctx = NULL; /* ramdisk context */
	uint8_t *buf = NULL;
	ssize_t bytes_downloaded;
	ssize_t bytes_read;
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	/* Open file with downloaded data */
	rdctx = storage_open_by_name(FASTBOOT_TMP_STORAGE,
			STORAGE_RAMDISK_NAME);
	if (rdctx == NULL) {
		FB_GEN_RESP(ctx, "FAILRamdisk open failed");
		FCS_LOG_ERR("%s\n", ctx->resp);
		res = -FCSERR_EINVAL;
		goto exit;
	}

	bytes_downloaded = pu_get_part_size(rdctx);
	if (bytes_downloaded < 0) {
		FB_GEN_RESP(ctx, "FAILIO Error");
		FCS_LOG_ERR("%s\n", ctx->resp);
		res = -FCSERR_EIO;
		goto exit;
	}

	buf = (uint8_t *)malloc(bytes_downloaded);
	if (buf == NULL) {
		FB_GEN_RESP(ctx, "FAILOut of memory");
		FCS_LOG_ERR("%s\n", ctx->resp);
		res = -FCSERR_ENOMEM;
		goto exit;
	}

	bytes_read = storage_read(rdctx, buf, bytes_downloaded);
	if (bytes_read != bytes_downloaded) {
		FB_GEN_RESP(ctx, "FAILRead fail");
		FCS_LOG_ERR("%s\n", ctx->resp);
		res = -FCSERR_EIO;
		goto exit;
	}

	res = handle_security_properties(buf, bytes_downloaded,
			ldr_ctx->sec_prop_list);
	if (res != FCSERR_OK) {
		FB_GEN_RESP(ctx, "FAILUnable to set security properties %d",
				res);
		goto exit;
	}

	FB_GEN_RESP(ctx, "OKAY");

exit:
	if (rdctx)
		(void)storage_close(rdctx);

	free(buf);
	return res;
}

static int handle_notsupported(struct protocol *ctx)
{
	if (!ctx) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}
	FB_GEN_RESP(ctx, "FAILCommand not supported");
	return FCSERR_OK;
}

static int hex2uint(const char *in, unsigned int *out)
{
	int i = 0;
	unsigned int number = 0;
	char ch = '\0';
	unsigned int nibble = 0;

	if (!in || !out) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	/*
	 * Converts the 8 chars to unsigned int.
	 */
	for (i = 0; i < 8; i++) {
		ch = in[i];
		if (ch >= '0' && ch <= '9')
			nibble = ch - '0';
		else if (ch >= 'A' && ch <= 'F')
			nibble = ch - 'A' + 10;
		else if (ch >= 'a' && ch <= 'f')
			nibble = ch - 'a' + 10;
		else
			return -FCSERR_EINVAL;
		number = (number << 4) + nibble;
	}
	*out = number;
	return FCSERR_OK;
}

static int handle_gptinfo(struct loader_ctx *ldr_ctx)
{
	int res;
	char *name;
	uint8_t *buf = NULL;
	ssize_t buf_sz = 0;
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	name = get_string_arg_from_cmd(CMD_GPTINFO, ldr_ctx->prot_hdl->cmd);

	/* Call with buf == NULL to get the size to allocate */
	res = partman_get_gpt_info(buf, &buf_sz, name);
	if (res != FCSERR_OK) {
		FB_GEN_RESP(ctx, "FAILIO Error");
		FCS_LOG_ERR("Failed to get gpt size (%d)\n", res);
		return res;
	}

	buf = malloc(buf_sz);
	if (buf == NULL) {
		FB_GEN_RESP(ctx, "FAILFailed to allocate memory");
		FCS_LOG_ERR("Failed to allocate memory\n");
		return -FCSERR_ENOMEM;
	}

	/* Get the gpt data */
	res = partman_get_gpt_info(buf, &buf_sz, name);
	if (res != FCSERR_OK) {
		FB_GEN_RESP(ctx, "FAILIO Error");
		FCS_LOG_ERR("Failed to get gpt data (%d)\n", res);
		goto exit;
	}

	/* Send response */
	FB_GEN_RESP(ctx, "DATA%08zx", buf_sz);
	res = prot_send_response(ctx);
	if (res != FCSERR_OK)
		goto exit;

	res = prot_send_data(ctx, buf, buf_sz);
	if (res != FCSERR_OK)
		goto exit;

	FB_GEN_RESP(ctx, "OKAY");

exit:
	free(name);
	free(buf);

	return res;
}

static int handle_getstorageinfo(struct loader_ctx *ldr_ctx)
{
	int res = FCSERR_OK;
	struct storage_ctx *sctx = NULL;
	ssize_t buf_sz = 0;
	uint8_t *buf = NULL;
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	sctx = storage_open_by_name(NULL, NULL);
	if (sctx == NULL) {
		FCS_LOG_ERR("Failed to open device\n");
		FB_GEN_RESP(ctx, "FAILIO Error");
		return -FCSERR_EIO;
	}

	storage_get_storage_info(sctx, buf, &buf_sz);

	buf = malloc(buf_sz);
	if (buf == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		FB_GEN_RESP(ctx, "FAILOut of memory");
		res = -FCSERR_ENOMEM;
		goto exit;
	}

	storage_get_storage_info(sctx, buf, &buf_sz);

	/* Send response */
	FB_GEN_RESP(ctx, "DATA%08zx", buf_sz);
	res = prot_send_response(ctx);
	if (res != FCSERR_OK)
		goto exit;

	res = prot_send_data(ctx, buf, buf_sz);
	if (res != FCSERR_OK)
		goto exit;

	FB_GEN_RESP(ctx, "OKAY");

exit:
	free(buf);
	storage_close(sctx);

	return res;
}

static int handle_challenge(struct loader_ctx *ldr_ctx)
{
	int res = FCSERR_OK;
	struct authenticate_ctx *auth_ctx = NULL;
	char *ssn;
	uint16_t sake_ssn;
	uint8_t challenge_buf[255];
	size_t challenge_len = sizeof(challenge_buf);
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	ssn = (char *)ctx->cmd + strlen(CMD_SAKE_CHALLENGE);

	/* Check if authentication level is sent in command */
	if (*ssn == ',') {
		/* Parse sake_ssn from command */
		ssn++;
		if (strncmp(ssn, "0", sizeof("0")) == 0) {
			sake_ssn = SAKE_SSN_CUSTOMER_SERVICE;
		} else if (strncmp(ssn, "1", sizeof("1")) == 0) {
			sake_ssn = SAKE_SSN_PRODUCTION;
		} else {
			FCS_LOG_WRN("SSN not supported\n");
			FB_GEN_RESP(ctx, "FAILSSN not supported");
			return FCSERR_OK;
		}
	} else if (*ssn == '\0') {
		/* Set PRODUCTION as default if no level is sent in command */
		sake_ssn = SAKE_SSN_PRODUCTION;
	} else {
		FCS_LOG_WRN("Malformed command\n");
		FB_GEN_RESP(ctx, "FAILMalformed command");
		return FCSERR_OK;
	}

	/* Save sake_ssn */
	ldr_ctx->ssn = sake_ssn;

	/* Initialize authentication */
	res = authenticate_init(&auth_ctx, sake_ssn, BUILD_NUMBER,
				strlen(BUILD_NUMBER));
	if (res != FCSERR_OK)
		goto fail;

	/* Generate SAKE hello message */
	res = authenticate_generate_challenge(&auth_ctx,
					      challenge_buf,
					      &challenge_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Generate sake hello failed (%d)\n", res);
		FB_GEN_RESP(ctx, "FAILGenerate data");
		goto fail;
	}

	/* Send response */
	FB_GEN_RESP(ctx, "DATA%08zx", challenge_len);
	res = prot_send_response(ctx);
	if (res != FCSERR_OK)
		goto fail;

	/* Send SAKE hello message */
	res = prot_send_data(ctx, challenge_buf, challenge_len);
	if (res != FCSERR_OK)
		goto fail;

	/* Send response */
	FB_GEN_RESP(ctx, "OKAY");
fail:
	authenticate_destroy(auth_ctx);
	return res;
}

static int handle_response(struct loader_ctx *ldr_ctx)
{
	int res = FCSERR_OK;
	struct authenticate_ctx *auth_ctx = NULL;
	struct storage_ctx *rdctx = NULL; /* ramdisk context */
	uint8_t *buf = NULL;
	ssize_t sz = 0;
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	/* Get sake_ssn from context */
	uint16_t sake_ssn = ldr_ctx->ssn;

	/* No text is allowed to come after "response" */
	if (ctx->cmd[strlen(CMD_SAKE_RESPONSE)] != '\0') {
		FCS_LOG_WRN("Malformed command\n");
		FB_GEN_RESP(ctx, "FAILMalformed command");
		return FCSERR_OK;
	}

	/* Initialize authentication */
	res = authenticate_init(&auth_ctx, sake_ssn, BUILD_NUMBER,
				strlen(BUILD_NUMBER));
	if (res != FCSERR_OK)
		goto fail;

	/* Open file with SakeDeviceCertificate */
	rdctx = storage_open_by_name(FASTBOOT_TMP_STORAGE,
				     STORAGE_RAMDISK_NAME);
	if (rdctx == NULL) {
		FCS_LOG_ERR("Unable to open ramdisk file %s\n",
				STORAGE_RAMDISK_NAME);
		FB_GEN_RESP(ctx, "FAILRamdisk open failed");
		res = -FCSERR_EINVAL;
		goto fail;
	}

	/* Get size of SakeDeviceCertificate */
	sz = pu_get_part_size(rdctx);
	if (sz < 0) {
		FCS_LOG_ERR("IO Error\n");
		FB_GEN_RESP(ctx, "FAILIO Error");
		res = -FCSERR_EIO;
		goto fail;
	}

	/* Allocate buffer for SakeDeviceCertificate */
	buf = malloc(sz);
	if (buf == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		FB_GEN_RESP(ctx, "FAILOut of memory");
		res = -FCSERR_ENOMEM;
		goto fail;
	}

	/* Read SakeDeviceCertificate and write to buffer */
	res = storage_read(rdctx, buf, sz);
	if (res != sz) {
		FCS_LOG_ERR("Read fail\n");
		FB_GEN_RESP(ctx, "FAILRead fail");
		res = -FCSERR_EIO;
		goto fail;
	}

	/* Verify SakeDeviceCertificate */
	res = authenticate_verify_response(&auth_ctx, buf, sz);
	if (res != FCSERR_OK) {
		FCS_LOG_WRN("Authenticate failed (%d)\n", res);
		FB_GEN_RESP(ctx, "FAILAuthentication failed");
		res = FCSERR_OK;
		goto fail;
	}

	/* Get authentication level */
	res = authenticate_get_level(auth_ctx, &(ldr_ctx->auth_level));
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Authenticate failed (%d)\n", res);
		FB_GEN_RESP(ctx, "FAILAuthentication failed");
		goto fail;
	}

	/* Send response */
	FB_GEN_RESP(ctx, "OKAY");
fail:
	authenticate_destroy(auth_ctx);
	if (rdctx)
		storage_close(rdctx);
	free(buf);
	return res;
}

static int handle_getrootkeyhash(struct loader_ctx *ldr_ctx)
{
	int res = FCSERR_OK;
	uint8_t *buf = NULL;
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	buf = malloc(core_get_root_key_hash_len());
	if (buf == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		FB_GEN_RESP(ctx, "FAILOut of memory");
		res = -FCSERR_ENOMEM;
		goto exit;
	}

	res = core_get_root_key_hash(buf, core_get_root_key_hash_len());
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get root key hash (%d)\n", res);
		FB_GEN_RESP(ctx, "FAILFailed to get root key hash");
		goto exit;
	}

	/* Send response */
	FB_GEN_RESP(ctx, "DATA%08x", core_get_root_key_hash_len());
	res = prot_send_response(ctx);
	if (res != FCSERR_OK)
		goto exit;

	res = prot_send_data(ctx, buf, core_get_root_key_hash_len());
	if (res != FCSERR_OK)
		goto exit;

	FB_GEN_RESP(ctx, "OKAY");

exit:
	free(buf);
	return res;
}

static int handle_charge(struct loader_ctx *ldr_ctx)
{
	char *cmd_arg = NULL;
	int bat_capacity;
	int res = FCSERR_OK;
	struct uevent_par u_par;
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	cmd_arg = get_string_arg_from_cmd(CMD_CHARGE, ctx->cmd);

	if (cmd_arg == NULL) {
		FCS_LOG_ERR("Input value fail\n");
		FB_GEN_RESP(ctx, "FAILInput value fail");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	bat_capacity = strtol(cmd_arg, NULL, 10);

	if (bat_capacity > 100 || bat_capacity < 0) {
		FCS_LOG_ERR("Input value fail\n");
		FB_GEN_RESP(ctx, "FAILInput value fail");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	u_par.battery_capacity = bat_capacity;
	FCS_LOG_INF("bat_capacity = (%d)\n", bat_capacity);

	res = uevent_handle_update(u_par);
	if (res < 0) {
		FB_GEN_RESP(ctx, "FAILCharging fail");
		FCS_LOG_ERR("uevent_handle_update failed (%d)\n", res);
		goto exit;
	}

	FB_GEN_RESP(ctx, "OKAY");
exit:
	free(cmd_arg);
	return res;
}

static int handle_set_ship_mode(struct loader_ctx *ldr_ctx)
{
	int res;
	struct protocol *ctx;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}
	ctx = ldr_ctx->prot_hdl;

	res = fcs_prop_set(FCS_PROP_SET_SHIPMODE);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to set system property (%d)\n", res);
		FB_GEN_RESP(ctx, "FAILSet ship mode failed");
		return res;
	}
	res = handle_powerdown(ldr_ctx);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to powerdown (%d)\n", res);
		FB_GEN_RESP(ctx, "FAILSet ship mode failed");
		return res;
	}

	return FCSERR_OK;
}

static int handle_enable_display(struct loader_ctx *ldr_ctx)
{
	int res;
	struct protocol *ctx;
	const uint8_t miscta_enable = 1;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	res = write_ta(TA_MISC_PART, TA_XFL_ENABLE_DISPLAY,
			&miscta_enable, sizeof(miscta_enable));

	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to write to MiscTA (%d)\n", res);
		FB_GEN_RESP(ctx, "FAILEnable display");
		return res;
	}

	res = fcsgfx_init();

	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to init display (%d)\n", res);
		FB_GEN_RESP(ctx, "FAILEnable display");
		return res;
	}

	FB_GEN_RESP(ctx, "OKAY");

	return FCSERR_OK;
}

static int handle_disable_display(struct loader_ctx *ldr_ctx)
{
	int res;
	struct protocol *ctx;
	const uint8_t miscta_disable = 0;

	if (!ldr_ctx || !ldr_ctx->prot_hdl) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ctx = ldr_ctx->prot_hdl;

	res = write_ta(TA_MISC_PART, TA_XFL_ENABLE_DISPLAY,
			&miscta_disable, sizeof(miscta_disable));

	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to write to MiscTA (%d)\n", res);
		FB_GEN_RESP(ctx, "FAILDisable display");
		return res;
	}

	res = fcsgfx_deinit(true);

	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to deinit display (%d)\n", res);
		FB_GEN_RESP(ctx, "FAILDisable display");
		return res;
	}

	FB_GEN_RESP(ctx, "OKAY");

	return FCSERR_OK;
}
