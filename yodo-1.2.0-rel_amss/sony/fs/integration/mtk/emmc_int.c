/*
 * Copyright (C) 2019 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "storage_int.h"
#include "storage_file.h"
#include "fcslog.h"
#include "fcserr.h"
#include "emmc.h"
#include "emmc_int.h"
#include <linux/mmc/core.h>
#include <linux/mmc/ioctl.h>
#include <asm-generic/ioctl.h>

/*
 * implements storage_set_bootdevice
 */
int storage_emmc_set_bootdevice(struct storage_ctx *ctx, int index)
{
        int ret = FCSERR_OK;
        struct storage_file_ctx *fctx = NULL;

        if (index < 1 || index > 2) {
                FCS_LOG_ERR("Invalid boot device index %d\n", index);
                return -FCSERR_EINVAL;
        }
        if (ctx == NULL) {
                FCS_LOG_ERR("Invalid storage context\n");
                return -FCSERR_EINVAL;
        }
        fctx = (struct storage_file_ctx *)ctx->ictx;

        FCS_LOG_INF("Enable boot device %d in eCSD config\n", index);

        /* Clear active boot index */
        ret = storage_emmc_send_switch_cmd(fctx->fd,
                MMC_SWITCH_MODE_CLEAR_BITS, EXT_CSD_PART_CONFIG,
                        EXT_CSD_PARTITION_CONFIG_CLR);
        if (ret) {
                FCS_LOG_ERR("Failed to clear partition config (%d)\n", ret);
                return ret;
        }

        /* Set active boot index in bit 3-5 of EXT_CSD_PART_CONFIG */
        ret = storage_emmc_send_switch_cmd(fctx->fd,
                MMC_SWITCH_MODE_SET_BITS, EXT_CSD_PART_CONFIG,
                        index << EXT_CSD_PARTITION_CONFIG_SHIFT);
        if (ret)
                FCS_LOG_ERR("Failed to set partition config (%d)\n", ret);

        return ret;
}

