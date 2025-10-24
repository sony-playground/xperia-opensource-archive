/**************************************************************************
 * FILE: devprg_target.c
 *
 * This is target specific file; has definitions of APIs as per target
 * If target doesn't support a functionality then a dummy API has to be
 * maintained in its place.
 *
 * Copyright (c) 2017,2020,2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Qualcomm Proprietary
 *
 *************************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when         who   what, where, why
----------   ---   ---------------------------------------------------------
2022-01-27   wek   Add support to get chip ID.
2021-06-08   wek   Update VIP/Authentication call for TME.
2020-12-17   wek   Initialize secure boot variable to 1.
2020-06-27   wek   Invalidate indirect_arg_list buffers.
2020-05-10   ds    move to edk2 arm mmu/cache lib
2017-07-14   svl   Create.

===========================================================================*/

#include "boot_reset_if.h"
#include "boot_crashdump.h"
#include "pm.h"
#include "pm_pon.h"
#include <Library/CacheMaintenanceLib.h>
#include "devprg_firehose.h"
#include "devprg_log.h"
#include "devprg_target.h"
#include <boot_config_context.h>
#include <seclib_syscall.h>


void devprg_target_reset(void)
{
  boot_hw_reset(BOOT_HARD_RESET_TYPE);
}

void devprg_target_poweroff(void) {
  boot_hw_powerdown();
}

void devprg_target_reset_edl(void)
{
  boot_dload_transition_pbl_forced_dload(CONFIG_CONTEXT_CRT_HANDLE);
}

int devprg_target_init(void)
{
  return 0;
}

int devprg_get_soc_serial_number(uint32 *serial_number)
{
  *serial_number = ChipInfo_GetSerialNumber();

  return 0;
}

int devprg_get_soc_chip_id(uint32 *chip_id)
{
  *chip_id = ChipInfo_GetQFPROMChipId();

  return 0;
}

bl_error_boot_type boot_seclib_is_auth_enabled(uint32 *is_auth_enabled);
int devprg_is_secure_boot_enabled(void)
{
  boot_tzt_result_regs_t result;
  int scm_result;
  result.reg[0] = 1;

  scm_result = boot_fastcall_tz(SECLIB_AUTH_ENABLED_STATUS_ID,
                                SECLIB_AUTH_ENABLED_STATUS_PARAM_ID,
                                0,0,0,0, &result);
  if (scm_result == SMC_SUCCESS && result.reg[0] == 0)
    return 0;
  return 1;
}

static dp_res_t boot_sec_img_auth_verify_signature(uint8 *buf, uint32 size, uint32 sw_id, uint32 sw_ver, uint8 **data_address, uint32 *data_size)
{
  dp_res_t result;
  int smc_status;
  boot_tzt_result_regs_t rsp_regs;
  uint64 buf_addr = (uint64)buf;
  if ((buf_addr % DEVPRG_VIP_BUFFER_ALIGNMENT) != 0)
  {
    DP_LOGE("Authenticate module requires buffer to be %d (0x%x) aligned, input buffer is not aligned Addr 0x%x size 0x%x",
            DEVPRG_VIP_BUFFER_ALIGNMENT, DEVPRG_VIP_BUFFER_ALIGNMENT, buf_addr, size);
	return DEVPRG_ERROR_INVAL_PARAM;
  }
  WriteBackInvalidateDataCacheRange(buf, size);

  memset(&rsp_regs, 0, sizeof(rsp_regs));

  smc_status = boot_fastcall_tz (SECLIB_AUTHENTICATE_SMC_ID,
                                 SECLIB_AUTHENTICATE_PARAM_ID,
                                 buf,
                                 size,
                                 sw_id,
                                 sw_ver,
                                 &rsp_regs);

  if (smc_status == SMC_SUCCESS && rsp_regs.reg[0] == 0)
  {
    result = DEVPRG_SUCCESS;
    *data_address = (uint8 *)rsp_regs.reg[1];
    *data_size = rsp_regs.reg[2];
  }
  else
  {
    DP_LOGE("VIP img authentication failed with smc_status = 0x%x, rsp_0 = 0x%x", smc_status, rsp_regs.reg[0]);
    result = DEVPRG_ERROR_AUTHENTICATION;
    *data_address = buf;
    *data_size = 0;
  }

  return result;
}

int devprg_authenticate_blob(uint8 *buf, uint32 size,
                             uint8 **data_out, uint32 *data_size)
{
  uint32 sw_id = VIP_SW_ID;
  uint32 sw_ver = 0;
  dp_res_t result;
  DP_LOGD("Requesting VIP img authentication elf_buf = 0x%x, elf_buf_len = %d", buf, size);
  result = boot_sec_img_auth_verify_signature(buf, size, sw_id, sw_ver, data_out, data_size);
  if (result == DEVPRG_SUCCESS)
  {
    DP_LOGD("Returned from verifying VIP img authentication: data = 0x%x, data_len = %d", *data_out, *data_size);
    return 1;
  }
  DP_LOGE("Verifying signature failed with %d", result);
  return 0;
}
