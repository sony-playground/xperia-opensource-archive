/*
 * Copyright 2016,2021 Sony Corporation.
 * All rights, including trade secret rights, reserved.
 */

/*
 * Interface for TA functionality
 */

#ifndef TA_INTERFACE_H_
#define TA_INTERFACE_H_

#include <stdint.h>
#include "fcserr.h"
#include <stdbool.h>

#define TA_VERSION 2

#define MISC_TA_MAX_PUBLIC_UNIT_ID 65535

/*
 * TA partitions
 */
#define TA_MISC_PART 2

/*
 * Misc TA units
 */
#define TA_FACTORY_MODE_UNIT		2002
#define TA_HWCONFIG_UNIT		2003
#define TA_SIMLOCK_UNIT			2010
#define TA_SIMPINCACHE_REASON		2016
#define TA_BOOT_CONFIGURATION_UNIT	2127
#define TA_SIMLOCK_SIGNATURE_UNIT	2129
#define TA_MODEM_ID                     2150
#define TA_EXT_MODEM_FUSE_TYPE          2151
#define TA_CUSTOMER_ID                  2171
#define TA_KEYSTORE_HMAC_KEY		2164
#define TA_SW_UNIT			2202
#define TA_S1_BOOT_VERSION_UNIT		2207
#define TA_PHONE_NAME			2210
#define TA_RCK				2226
#define TA_RL_DATA_LOW_UNIT		2234
#define TA_RESET_LOCK_STATUS		2237
#define TA_BOOT_PARAM_OVERRIDE_UNIT	2301
#define TA_AUTH_CH			2334
#define TA_XFL_SEC_DATA_UNIT		2335
#define TA_NVLOG_UNIT			2337
#define TA_ENABLE_CONSOLE		2473
#define TA_MASTER_RESET			2550
#define TA_MSN_UNIT			4900
#define TA_PBA_SPACE_NUMBER_UNIT	4901
#define TA_PBA_SPACE_REVISION_UNIT	4902
#define TA_HW_COLOR_ID			4990
#define TA_DK_NUMBER_UNIT		66667
#define TA_GOOGLE_LOCK_STATE		66671
#define TA_KEYSTORE_HMAC_KEY_APPLY	66673
#define TA_XFL_ENABLE_DISPLAY		66674

/*
 * Initilizes TA functionality.
 * Returns a FCSERR_x code.
 */
int ta_init(void);

/*
 * Format TA partition <partition>.
 * Returns a FCSERR_x code.
 */
int format_ta(uint8_t partition);

/*
 * Get size of TA unit <unit> in partition <partition>.
 * The size is returned in <unit_size>.
 * Returns a FCSERR_x code.
 */
int get_ta_unit_size(uint8_t partition, uint32_t unit, int *unit_size);

/*
 * Read TA unit <unit> from partition <partition>.
 * The value is copied to the buffer <buf> which has size <buf_size>.
 * Returns a FCSERR_x code.
 */
int read_ta(uint8_t partition, uint32_t unit, uint8_t *buf, int buf_size);

/*
 * Get size of all TA units in partition <partition>.
 * The size is returned in <ta_size>.
 * If include_hi_ta is true the high ta units are included.
 * Returns a FCSERR_x code.
 */
int get_all_ta_size(uint8_t partition, int *ta_size, bool include_hi_ta);

/*
 * Read all TA units from partition <partition>. Setting include_hi_ta to true
 * will include those in buf.
 * The values of the TA units are copied to the buffer <buf> which has size
 * <buf_size>.
 * Every TA record has three elements:
 * unit number (4 bytes),
 * unit size (4 bytes),
 * unit data (unit size bytes).
 * Returns a FCSERR_x code.
 */
int read_all_ta(uint8_t partition, uint8_t *buf, int buf_size,
		bool include_hi_ta);

/*
 * Write data in <buf> with size <buf_size> to TA unit <unit>, partition
   <partition>.
 * Returns a FCSERR_x code.
 */
int write_ta(uint8_t partition, uint32_t unit, const uint8_t *buf,
		int buf_size);

/*
 * Delete TA unit <unit> in partition <partition>.
 * Returns a FCSERR_x code.
 */
int delete_ta(uint8_t partition, uint32_t unit);

#endif
