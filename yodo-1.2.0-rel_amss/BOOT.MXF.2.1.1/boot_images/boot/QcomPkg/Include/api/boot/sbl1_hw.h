#ifndef SBL1_HW_H
#define SBL1_HW_H

/*=============================================================================

                         SBL1 Hardware Initialization

GENERAL DESCRIPTION
  This file does basic hardware initialization at power up.

Copyright 2010-2021 by Qualcomm Technologies Inc.  All Rights Reserved.
=============================================================================*/

/*=============================================================================

                            EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Include/api/boot/sbl1_hw.h#1 $

when       who       what, where, why
--------   ---       ----------------------------------------------------------
06/28/21   ck        Renamed xbl_pcie_dump_enabled to xbl_pcie_fast_boot_enabled
03/22/21   ds        EUD pre/post DP enable changes
01/24/21   rama      Removed sbl1_hw_btns_capture
01/21/21   rhy       Added sbl1_pre_ddr_clock_init
01/14/21   rama      Added boot_eud_init
04/20/20   rhy       Removed sbl1_hw_get_reset_status()
03/30/20   rhy       Added PMIC init for SDX
10/18/11   dh        Initial revision
=============================================================================*/

/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include "boot_comdef.h"
#include "boot_framework.h"
#include "boot_error_if.h"


typedef enum eud_init_type{
  EUD_PRE_DP_ENABLE,
  EUD_POST_DP_ENABLE
}eud_init_type;

/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

===========================================================================*/

/*===========================================================================

**  Function :  sbl1_hw_init

** ==========================================================================
*/
/*!
* 
* @brief
*   This function performs hardware initialization.
* 
*   Only common hardware that is needed for flash
*   initialization is initialized here.
* 
* 
* @par Dependencies
*   None
* 
* @retval
*   None
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type sbl1_hw_init(boot_handle config_context_handle);


/*===========================================================================

**  Function :  sbl1_ddr_init

** ==========================================================================
*/
/*!
* 
* @brief
*   Initialize DDR device.
* * 
* @par Dependencies 
*  Following Api's need to be called first:
*  	sbl2_hw_init : To have ddr clocks setup.
*  	sbl2_ddr_set_params : To have DDR config parameters setup.
* 
* @retval
*   None
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type sbl1_ddr_init(boot_handle config_context_handle);

/*===========================================================================

**  Function :  sbl1_do_ddr_training

** ==========================================================================
*/
/*!
*
* @brief
*   Train DDR if applicable.
* *
* @par Dependencies
*  Following Api's need to be called first:
*    sbl1_ddr_init : To setup ddr.
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/
bl_error_boot_type sbl1_do_ddr_training(boot_handle config_context_handle);

/*===========================================================================

**  Function :  sbl1_hw_dload_init

** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes the necessary clocks for dload.
*   We only do so when auth is disabled 
* 
*
* @par Dependencies
*   None
* 
* @retval
*   None
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type sbl1_hw_dload_init(boot_handle config_context_handle);


/*===========================================================================

**  Function :  sbl1_hw_init_secondary

** ==========================================================================
*/
/*!
* 
* @brief
*   This function performs secondary hardware initialization.
* 
* @param[in] bl_shared_data Pointer to shared data
* 
* @par Dependencies
*   None
* 
* @retval
*   None
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type sbl1_hw_init_secondary(boot_handle config_context_handle);

/*===========================================================================

**  Function :  sbl1_hw_pre_ddr_init

** ==========================================================================
*/
/*!
* 
* @brief
*  Initialize PMIC and railway driver. API used for hw initialization that
*  must occur before DDR init.
* 
* @param[in] bl_shared_data Pointer to shared data
* 
* @par Dependencies
*  	This Api needs to be called :
*  Before: sbl1_ddr_init
*
* 
* @retval
*   None
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type sbl1_hw_pre_ddr_init(boot_handle config_context_handle);

/*===========================================================================

**  Function :  sbl1_ddr_set_params

** ==========================================================================
*/
/*!
* 
* @brief
*   Set DDR configuration parameters.
* 
* @param[in] bl_shared_data Pointer to shared data
* 
* @par Dependencies
*  	This Api needs to be called :
*  Before: sbl1_ddr_init, sbl1_ddr_init_for_dload and qsee_exec_func
*  After: boot_config_data_table_init
* 
* @retval
*   None
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type sbl1_ddr_set_params(boot_handle config_context_handle);

/*===========================================================================

**  Function :  sbl1_ddr_set_default_params

** ==========================================================================
*/
/*!
* 
* @brief
*   Set DDR configuration parameters
* 
* @param[in] bl_shared_data Pointer to shared data
* 
* @par Dependencies
*  	This Api needs to be called :
*  Before: sbl1_ddr_init, boot_config_data_table_init
*  After: 
* 
* @retval
*   None
* 
* @par Side Effects
*   None
* 
*/
void sbl1_ddr_set_default_params(boot_handle config_context_handle);

/*===========================================================================

**  Function :  sbl1_check_device_temp

** ==========================================================================
*/
/*!
* 
* @brief
*   This function does a temperature check. If the device is too hot
*   we wait few seconds to allow it to cool below certain threshold.
* 
* @param[in] 
*   None 
*     
* @par Dependencies
*   Must be called after DALSYS_InitMod
*   
* @retval
*   None
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type boot_check_device_temp(boot_handle config_context_handle);


/*===========================================================================

**  Function :  sbl1_load_ddr_training_data

** ==========================================================================
*/
/*!
* 
* @brief
*   If ddr training is required, read the ddr training data from partition
*   and pass it to ddr driver.
* 
* @param[in] 
*   None 
*     
* @par Dependencies
*   Must be called before sbl1_ddr_init
*   
* @retval
*   None
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type sbl1_load_ddr_training_data();


/*===========================================================================

**  Function :  sbl1_wait_for_ddr_training

** ==========================================================================
*/
/*!
* 
* @brief
*   Execute DDR training sequence. If ddr training data is updated, save it
*   to storage device.
* 
* @param[in] 
*   bl_shared_data Pointer to shared data 
*     
* @par Dependencies
*   Must be called after sbl1_ddr_init
*   
* @retval
*   None
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type sbl1_wait_for_ddr_training(boot_handle config_context_handle);


/*===========================================================================

**  Function :  sbl1_hw_deinit

** ==========================================================================
*/
/*!
* 
* @brief
*   This function deinit the hardware that's not needed beyond sbl1
* 
* @param[in] bl_shared_data Pointer to shared data
* 
* 
* @retval
*   None
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type sbl1_hw_deinit(boot_handle config_context_handle);

/*===========================================================================

**  Function :  sbl1_pm_aop_pre_init_wrapper

** ==========================================================================
*/
/*!
*
* @brief
*   Do pre init procedure for AOP.
*
* @param[in]
*   bl_shared_data Pointer to shared data
*
* @par Dependencies
*   Must be called before loading AOP
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/
bl_error_boot_type sbl1_pm_aop_pre_init_wrapper(boot_handle config_context_handle);

/*===========================================================================

**  Function :  sbl1_hw_play_vibr

** ==========================================================================
*/
/*!
*
* @brief
*   This function calls PMIC API to play power on vibration
*
* @param[in] bl_shared_data Pointer to shared data
*
* @par Dependencies
*   None
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/
bl_error_boot_type sbl1_hw_play_vibr(boot_handle config_context_handle);

/*===========================================================================

**  Function :  sbl1_hw_pmic_init

** ==========================================================================
*/
/*!
*
* @brief
*   This function initialize PMIC
*
* @par Dependencies
*   None
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/
bl_error_boot_type sbl1_hw_pmic_init(boot_handle);

/*===========================================================================
**  Function :  xbl_pcie_fast_boot_enabled
** ==========================================================================
*/
/*!
*
* @brief
*   This function will check whether PCIe is
*   enabled via the fast boot register.
*
* @par Dependencies
*   Must be called after sbl1_ddr_init
*
* @retval
*   TRUE - if PCIe is enabled
*   FALSE - otherwise
*
* @par Side Effects
*   None
*
*/
boolean xbl_pcie_fast_boot_enabled(void);
boolean xbl_pcie_reset_sep_enabled (void);

/*===========================================================================

**  Function :  boot_eud_init

** ==========================================================================
*/
/*!
*
* @brief
*   This function performs EUD initialization after checking debug state.
*
*
* @param[in] boot_handle config_context_handle passed by caller
*
* @par Dependencies
*   None
*
* @retval
*   BL_ERR_NONE on success
*
* @par Side Effects
*   None
*
*/
bl_error_boot_type boot_eud_init(boot_handle config_context_handle, eud_init_type init_type);

/*===========================================================================

**  Function :  sbl1_pre_ddr_clock_init

** ==========================================================================
*/
/*!
*
* @brief
*   Get the ddr type by reading the CDT and initialize
*   pre DDR clock
*
* @param[in] boot_handle
*
* @par Dependencies
*    This Api needs to be called :
*  Before: sbl1_ddr_init
*  After: boot_config_data_table_init
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/
bl_error_boot_type sbl1_pre_ddr_clock_init(boot_handle);

#endif /* SBL1_HW_H */