#ifndef __PMIC_CONFIG_SBL_COMMON_H__
#define __PMIC_CONFIG_SBL_COMMON_H__

/*! \file  pm_config_sbl_common.h
 *
 *  \brief  File Contains the PMIC Set Mode Implementation
 *  \details This file extract the common elements from pm_config_sbl.c and 
 *  pm_config_sbl_coderam.c file
 *
 *  &copy; Copyright 2021-2022 Qualcomm Technologies Inc, All Rights Reserved
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/framework/inc/pm_config_sbl_common.h#1 $
$DateTime: 2022/08/18 10:15:46 $  $Author: pwbldsvc $


when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/16/21   rh      Creation
===========================================================================*/
#define RELOAD_PBS_STATE_RELOAD   0
#define RELOAD_PBS_STATE_SKIP     1

struct sbl_config_info{
  void *pdm_config_ds_buff;
  uint32 config_buff_size;
  void *pbs_ram_buff;
  uint32 pbs_ram_buff_size;
  uint32 xbl_cfg_h;
  uint8 reload_pbs_state;
};

typedef struct sbl_config_info sbl_config_info_t;

pm_err_flag_type
pm_sbl_validate_cond_config( pm_sbl_config_info_type *sbl_config_info_ds,
                             pm_sbl_cond_seq_type   *cond_ds_ptr,
                             uint8    cond_start_index,
                             uint8    cond_end_index,
                             boolean  *valid_cfg );


pm_err_flag_type
pm_config_sbl_oem_psi( void );

pm_err_flag_type 
pm_config_read_init(sbl_config_info_t *info, uint32 buf_size, uint32 cfg_size);

void 
*pm_config_allocate_and_read(sbl_config_info_t *info, uint32 offset, uint32 size);

void 
pm_config_read_into_pbs_ram_buf(sbl_config_info_t *info, uint32 offset, uint32 size, void **pbs_ram_buff);

void 
pm_sbl_config_check_psi_crc(sbl_config_info_t *info, uint32 sid, uint32 pbs_ram_idx, uint32 ram_config_offset);

void 
config_free_buffer(sbl_config_info_t *info, void *buf);

pm_err_flag_type 
pm_psi_set_base_address(uintnt address);

pm_err_flag_type 
pm_psi_get_base_address(uintnt* address);

void
pm_sbl_config_check_psi_crc_v2(uint8 *reload_pbs_state, uint32 sid, uint32 pbs_ram_idx, void *pbs_ram);

#endif
