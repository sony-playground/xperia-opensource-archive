/**************************************************************************
 * FILE: devprg_target.h
 *
 * This is target specific file; has all the # includes required to build
 * Device Programmer for a specific target. Also has prototype of APIs
 * to be supported across all targets.
 *
 * Copyright (c) 2017,2022 Qualcomm Technologies, Inc.
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
2017-07-13   svl   Create.

===========================================================================*/

#ifndef __DEVPRG_TARGET_H__
#define __DEVPRG_TARGET_H__

#include "comdef.h"
#include "secboot_hw.h"
#include "secboot.h"
#include "boot_fastcall_tz.h"
#include "sec_img_auth.h"
#include "ChipInfo.h"

/* Get the SOC main serial number.
 *
 * Gets the MSM serial number.
 *
 * param serial_number [out]Serial number for the chip.
 *
 * return 0 on success, -1 on error.
 **/
int devprg_get_soc_serial_number(uint32 *serial_number);

/* Get the SOC Chip ID.
 *
 * Gets the MSM Chip ID.
 *
 * param chip_id [out]The chip ID.
 *
 * return 0 on success, -1 on error.
 **/
int devprg_get_soc_chip_id(uint32 *chip_id);

/* Checks if secure boot is enabled.
 *
 * return 0 if secure boot is not enabled, 1 if it is enabled.
 */
int devprg_is_secure_boot_enabled(void);

/* Authenticates a blob of data signed for device programmer image ID. */
int devprg_authenticate_blob(uint8 *buf, uint32 size,
                             uint8 **data_out, uint32 *data_size);

int devprg_target_init(void);
void devprg_target_reset(void);
void devprg_target_reset_edl(void);
void devprg_target_poweroff(void);

#endif /* __DEVPRG_TARGET_H__ */
