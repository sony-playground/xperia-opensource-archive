/****************************************************************************** 
**  
**   Qualcomm Technologies Incorporated
** 
**   Copyright (c) 2014,2016-2020,2022 Qualcomm Technologies, Inc.
**   All rights reserved.
**   Qualcomm Technologies, Inc. Confidential and Proprietary.
** 
******************************************************************************/

#ifndef PBL_BL_SHARED_H
#define PBL_BL_SHARED_H

 /**===========================================================================
 **
 **                        PRIMARY BOOT LOADER
 **                        ------------------- 
 ** FILE 
 **     pbl_bl_shared.h
 ** 
 ** GENERAL DESCRIPTION 
 **     This header file contains PBL-BL shared data structure
 **     specific details.
 ** 
 **     Any new shared data that has to be passed to BL should be
 **     added in this file. Any dependencies, like enums, defines etc ...
 **     that are supposed to be passed in this structure should be present
 **     in this file.
 ** 
 **     BL code relies heavily on this structure and hence
 **     everytime there is a change in the shared data-structure
 **     (additions/deletions of fields/new values etc) ... structure
 **     version should be incremented appropriately.
 ** 
 **     Any new shared data field that has to be added has to be
 **     at the end of the structure.
 **
 **     NOTE:
 **     -----
 **
 **     ANY CHANGES INT THIS FILE OR ANY FIELDS RELATED TO THE 
 **     SHARED DATA STRUCTURE MUST BE REVIEWED WITH BL IMAGE
 **     OWNERS.
 **
 **==========================================================================*/


/*===========================================================================

                           EDIT HISTORY FOR FILE

  This section contains comments describing changes made to the module..
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Library/BootPblSharedDataLib/Include/pbl_sbl_shared.h#1 $

  when       who    what, where, why
  --------   ----   ---------------------------------------------------
  06/22/22   rhy    Added PBL Current GUID entered
  06/08/22   ds     update for Lanai E3
  09/24/20   ds     update for E3
  09/16/20   rama   Fix PBL interface parameter casting issue
  07/23/20   rama   Changes to make pbl_sbl_shared.h version agnostic
============================================================================*/


/******************************************************************************
                                MODULE INCLUDES
                         ADD NEW ONES UNDER THIS LINE
******************************************************************************/
#include <boot_comdef.h>
#include <boot_media_types.h>
#include <boot_error_if.h>
#include <string.h>

/******************************************************************************
                         PUBLIC TYPES and TYPE-DEFINES
                         ADD NEW ONES UNDER THIS LINE  
******************************************************************************/

/* Parameter ID for the data to be accessed from PBL shared data */
typedef enum _pbl_apps_xbl_shared_data_param_id_type{
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_PBL_FW_VERSION,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_PBL_PATCH_VERSION,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_RMB_MBOX_BASE_ADDR,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_CPU_BOOT_SPEED_HZ,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_BOOT_MEDIA_TYPE,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_IS_EDL_MODE,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_DEV_PROG_ELF_ENTRY_ADDR,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_XBL_CONFIG_ELF_ENTRY_ADDR,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_XBL_SC_EXT_ELF_ENTRY_ADDR,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_PBL_TIMESTAMPS_BUFFER_ADDR,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_PBL_TIMESTAMPS_BUFFER_SIZE,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_PBL_DEBUG_SHARED_INFO_ADDR,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_PBL_DEBUG_SHARED_INFO_SIZE,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_XBL_SC_DEBUG_LOG_ADDR,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_XBL_SC_DEBUG_LOG_SIZE,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_TME_CPU_PBL_ROM_BYPASS_FUSE,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_PBL_CURRENT_GUID_ENTERED,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_MAX,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_SIZE                           = 0x7FFFFFFFF,
}pbl_apps_xbl_shared_data_param_id_type;

typedef struct boot_pbl_shared_data_if_type
{
  
  bl_error_boot_type (*init)(void* pbl_bl_shared);
  
  bl_error_boot_type (*get_value)(pbl_apps_xbl_shared_data_param_id_type parameter_id, uintnt* result);
  
} boot_pbl_shared_data_if_type;

/******************************************************************************
                            PUBLIC DATA DECLARATION
                         ADD NEW ONES UNDER THIS LINE  
******************************************************************************/

/*===========================================================================

**  Function :  boot_pbl_shared_data_get_interface

** ==========================================================================
*/
/*!
* 
* @brief
*   This funcion initialzes a boot_pbl_shared_data_if interface
*
* @param[in]
*   pointer to store interface address
*
* @par Dependencies
*   None
*   
* @retval
*   BL_ERROR_NONE on success
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type boot_pbl_shared_data_get_interface(void *pbl_shared_data_if);


#endif /* PBL_BL_SHARED_H */
/*=============================================================================
                                  END OF FILE
=============================================================================*/

