/****************************************************************************** 
**  
**   Qualcomm Technologies Incorporated
** 
**   Copyright (c) 2020 Qualcomm Technologies, Inc.
**   All rights reserved.
**   Qualcomm Technologies, Inc. Confidential and Proprietary.
** 
******************************************************************************/

#ifndef UCENV_XBL_CORE_H_
#define UCENV_XBL_CORE_H_

#include <stddef.h>
#include "com_dtypes.h"
#include "uclib_env.h"

#define BAM_RSLT_BUF_SIZE                 256                /** BAM Result Buffer Size, to hold 2 of 128 bytes of struct ce_result_s -- ce_bam.c                 */
#define BAM_CONTAINER_BUF_SIZE            256                /** BAM Container Buffer Size, to hold 4 of cache_line_sz(<= 64 bytes) -- 4*64 = 256                 */
#define BAM_TXRX_DESC_SIZE                304                /** BAM DESC Buffer Size, any number < 0x7FFF and multple of 8 - bami.h                              */
#define BAM_DRV_CTX_SIZE                  2400               /** BAM_DRV_CTX Buffer Size, any number >= (sizeof(cmd_reg_t) + get_ce_ver_cmd_reg_size) -- ce_bam.c */ 

/**
 * To set HW Base Address in ucenv_xbl_core env structure.
 *
 * @param env       [in]: pointer to environment structure
 * @param var       [in]: indicate which base address to be set in enum env_base_addr_var_t
 * @param baseAddr  [in]: the 32bit value of HW base addr to be set
 *
 * @return 0 if successful. negative value otherwise.
 */
int xbl_core_set_env_HW_base(env_t *env, env_base_addr_var_t var, uint32_t baseAddr);

/**
 * To set CE BAM used buf address.
 *
 * @param env     [in]: pointer to environment structure
 * @param var     [in]: indicate which BAM buf address to be set in enum env_bam_var_t
 * @param data    [in]: data of BAM buf address to be set
 *
 * @return 0 if successful. negative value otherwise.
 */
int xbl_core_set_env_bam_buf_addr(env_t *env, env_bam_var_t var, uint8_t* data);

/**
 * To set the CE Lock.
 *
 * @param env     [in]: pointer to environment structure
 * @param lock    [in]: CE lock to be set
 *
 * @return 0 if successful. negative value otherwise.
 */
int xbl_core_set_lock(env_t *env, void* lock);

/**
 * To set the PRNG Lock.
 *
 * @param env     [in]: pointer to environment structure
 * @param lock    [in]: PRNG lock to be set
 *
 * @return 0 if successful. negative value otherwise.
 */
int xbl_core_set_prng_lock(env_t *env, void* lock);

#endif /* UCENV_XBL_CORE_H_ */
