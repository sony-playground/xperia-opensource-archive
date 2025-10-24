#ifndef SBL1_MC_H
#define SBL1_MC_H

/*===========================================================================

                      SBL1 Main Control Header File

GENERAL DESCRIPTION
  This file contains the main control for SBL1 execution.

Copyright 2019-2022 Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.boot/6.1.1/QcomPkg/XBLLoader/sbl1_mc.h#1 $ 
$DateTime: 2022/08/18 10:15:46 $ 
$Author: pwbldsvc $

when        who      what, where, why
----------  ---      ----------------------------------------------------------
07/08/22    ck       Updated sbl1_boot_logger_deinit return value
05/15/21    ds       added wdog enable
01/22/21    rhy      Added sbl1_save_data_to_ddr_partition
08/24/20    rama     Removed sbl1_get_shared_data
07/23/20    rama     changed pbl_shared data to void*
05/29/20    rama     Change boot_logger_deinit to use config_context_handle

===========================================================================*/


/*===========================================================================
                           INCLUDE FILES
===========================================================================*/
#include <pbl_sbl_shared.h>
#include <boot_framework.h>
/*===========================================================================
                      PUBLIC FUNCTION DECLARATIONS
===========================================================================*/

/*===========================================================================
**  Function :  sbl1_main_ctl
** ==========================================================================
*/
/*!
* 
* @brief
*   The RPM Main Controller performs the following functions:
*       - Initializes indirect vector table in IMEM
*       - Always calls the cold boot process. (warm boot not supported)
* 
* @param[in] pbl_shared Pointer to shared data
* 
* @par Dependencies
*   None
* 
* @retval
*   None
* 
* @par Side Effects
*   This function never returns.
* 
*/
void sbl1_main_ctl(void *pbl_shared);


/*===========================================================================
**  Function :  sbl1_boot_logger_deinit
** ==========================================================================
*/
/*!
* 
* @brief
*   This function stops the boot logger and dumps the log information. Should
*   be called right before exiting the bootloader 
*
* @par Dependencies
*   Called after sbl1_boot_logger_init()
* 
*/
bl_error_boot_type sbl1_boot_logger_deinit(boot_handle config_context_handle);


/*===========================================================================
**  Function :  sbl1_hw_platform_pre_ddr
** ==========================================================================
*/
/*!
* 
* @brief
*       Parse cdt table to get start of sw-platform id CDB.
*       Call platform-id API and pass pointer to start of sw-platform id CDB.
*       Call hw_init_smem to store platform id to SMEM
* 
* @par Dependencies
*   None
*   
* @retval
*   None
* 
* @par Side Effects
*   None
*/
bl_error_boot_type sbl1_hw_platform_pre_ddr(boot_handle config_context_handle);


/*===========================================================================
**  Function :  sbl1_hw_platform_smem
** ==========================================================================
*/
/*!
* 
* @brief
*       Parse cdt table to get start of sw-platform id CDB.
*       Call platform-id API and pass pointer to start of sw-platform id CDB.
*       Call hw_init_smem to store platform id to SMEM
* 
* @par Dependencies
*   None
*   
* @retval
*   None
* 
* @par Side Effects
*   None
*/
bl_error_boot_type sbl1_hw_platform_smem(boot_handle config_context_handle);

/*===========================================================================
**  Function :  sbl1_post_ddr_init
** ==========================================================================
*/
/*!
* 
* @brief
*   This funcion will initialize the data section in DDR and relocate boot log to DDR
*   After execution of this function SBL1 will enter Sahara in stead of PBL
*   emergency dload mode in case of error
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
bl_error_boot_type sbl1_post_ddr_init(boot_handle config_context_handle);


/*===========================================================================
**  Function :  sbl1_post_ddr_training_init
** ==========================================================================
*/
/*!
* 
* @brief
*   This funcion will initialize the data section in DDR, populate ddr size information
*   then relocate page table from IMEM to DDR and map all memory regions required by SBL1 
*   in page table.
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
void sbl1_post_ddr_training_init(void);

/*===========================================================================
**  Function :  sbl1_relocate_page_table_to_ddr
** ==========================================================================
*/
/*!
* 
* @brief
*   This funcion will relocate page table from imem to DDR and map all avaliable
*   DDR memory to page table
* 
* @param[in] bl_shared_data Pointer to shared data
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
bl_error_boot_type sbl1_relocate_page_table_to_ddr(boot_handle config_context_handle);


/*===========================================================================
**  Function :  sbl1_efs_handle_cookies
** ==========================================================================
*/
/*!
* 
* @brief
*   Calls efs cookie handling api to perform efs backup/restore action
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
bl_error_boot_type sbl1_efs_handle_cookies(boot_handle config_context_handle);

/*===========================================================================
**  Function :  sbl1_tlmm_init
** ==========================================================================
*/
/*!
* 
* @brief
*   SBL1 wrapper to Initialize Tlmm and gpio for low power config
*
* @param[in] shared_data Pointer to shared data
*        
* @par Dependencies
*   must be called after boot_smem_init
*   
* @retval
*   None
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type sbl1_tlmm_init(boot_handle config_context_handle);


/*===========================================================================
**  Function :  sbl1_load_ddr_training_data_from_partition
** ==========================================================================
*/
/*!
* 
* @brief
*   This funcion will read the ddr training data from ddr parition
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
bl_error_boot_type sbl1_load_ddr_training_data_from_partition
(
  boot_handle config_context_handle,
  uint8* ddr_training_data_buf,
  uint32 ddr_training_data_size
);

/*===========================================================================
**  Function :  sbl1_save_ddr_training_data_to_partition
** ==========================================================================
*/
/*!
* 
* @brief
*   This funcion will save ddr training data to ddr partition
* 
* @param[in] ddr_training_data_ptr Pointer to ddr training data
*
* @param[in] ddr_training_data_size size of ddr training data
*     
* @par Dependencies
*   Must be called after ddr_post_init
*   
* @retval
*   None
* 
* @par Side Effects
*   None
* 
*/
void sbl1_save_ddr_training_data_to_partition
(
  uint8* ddr_training_data_ptr,
  uint32 ddr_training_data_size,
  uint32 ddr_training_data_offset
);

/*===========================================================================
**  Function :  boot_read_l2esr
** ==========================================================================
*/
/*!
* 
* @brief
*   Returns the value of L2ESR register
**        
* @par Dependencies
*  None
*   
*/
uint32 boot_read_l2esr(void);

/*===========================================================================
**  Function :  sbl1_save_data_to_ddr_partition
** ==========================================================================
*/
/*!
*
* @brief
*   This funcion will save ddr training data to ddr partition
*
* @param[in] ddr_data_ptr Pointer to ddr data
*
* @param[in] ddr_data_size size of ddr data to be written
*
* @par Dependencies
*   Must be called after ddr_post_init
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/
bl_error_boot_type sbl1_save_data_to_ddr_partition(uint8*, uint32, uint32);


/*===========================================================================
**  Function :  xbl_enable_sec_wdog
** ==========================================================================
*/
/*!
*
* @brief
*   enable sec wdog with default time
*
* @param[in] None
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/
void xbl_enable_sec_wdog(void);

#endif  /* SBL1_MC_H */

