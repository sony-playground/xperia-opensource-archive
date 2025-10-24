#ifndef __PMIC_SBL_BOOT_TARGET_H__
#define __PMIC_SBL_BOOT_TARGET_H__

/*! \file pm_sbl_boot_target.h
*  \n
*  \brief This file contains PMIC device initialization function and globals declaration.
*  \n
*  \n &copy; Copyright 2016-2022 Qualcomm Technologies Inc, All Rights Reserved
*/
/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/target/kailua/system/src/pm_sbl_boot_target.h#2 $
$Author: pwbldsvc $
$DateTime: 2022/08/22 21:24:44 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
09/13/17   aab     Added target specific fn: pm_spmi_tgt_vrm_init() 
02/05/16   aab     Added active/retentsion level config reg address
02/05/16   aab     Creation
========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "com_dtypes.h"
#include "pm_err_flags.h"
#include "SpmiBusCfg.h"
#include "pm_config_sbl.h"



/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/
// Order in pm_pbs_seq_a / pm_pbs_seq_b / pm_pbs_seq_c   /pm_pbs_seq_d
// Which is PBS2_RAM     / PBS1_RAM     / PBS3_RAM       /Kohala PBS_RAM
#define PBS_CRC_CHECK_STATUS_ADDR   {0x72A6, 0x72A3, 0x72A9, 0x72AC}
#define PBS_CRC_CHECK_VALUE_ADDR    {0x72A7, 0x72A4, 0x72AA, 0x72AD}

/*===========================================================================

                        FUNCTION PROTOTYPES 

===========================================================================*/
pm_err_flag_type 
pm_spmi_tgt_vrm_init(SpmiBusCfg_Ppid *pm_vrm_rsrc_arr, uint32 *vrm_cfg_index, uint8 vrm_rsrc_arr_size);

pm_err_flag_type 
pm_tgt_mgpi_cfg(SpmiBusCfg_MgpiPortCfg** mgpi_port_cfg_ptr);

pm_err_flag_type 
pm_set_oledb_default_config();

pm_err_flag_type 
pm_tgt_aop_pre_init(void);

pm_err_flag_type 
pm_sbl_epm_en( uint8 value );
  
pm_err_flag_type 
pm_sbl_epm_mode( uint8 value );
  
pm_err_flag_type 
pm_sbl_epm_config( uint8 buck_en, uint8 buck_gang, uint8 buck_sid, uint8 buck_pid );

pm_err_flag_type 
pm_config_cpucp_uls(void);
#endif //__PMIC_SBL_BOOT_TARGET_H__
