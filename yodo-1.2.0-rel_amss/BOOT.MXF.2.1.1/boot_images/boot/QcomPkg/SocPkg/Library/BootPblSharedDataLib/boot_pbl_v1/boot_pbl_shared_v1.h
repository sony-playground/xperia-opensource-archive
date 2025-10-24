/****************************************************************************** 
**  
**   Qualcomm Technologies Incorporated
** 
**   Copyright (c) 2020 Qualcomm Technologies, Inc.
**   All rights reserved.
**   Qualcomm Technologies, Inc. Confidential and Proprietary.
** 
******************************************************************************/

#ifndef BOOT_PBL_SHARED_V1_H
#define BOOT_PBL_SHARED_V1_H

 /**===========================================================================
 **
 **                        PRIMARY BOOT LOADER
 **                        ------------------- 
 ** FILE 
 **     boot_pbl_shared_v1.h
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

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Library/BootPblSharedDataLib/boot_pbl_v1/boot_pbl_shared_v1.h#1 $

  when       who    what, where, why
  --------   ----   ---------------------------------------------------
  07/24/20   rama   Initial version created
 
============================================================================*/

#include <pbl_sbl_shared.h>
/******************************************************************************
                                MODULE INCLUDES
                         ADD NEW ONES UNDER THIS LINE
******************************************************************************/
/* Shared data structure Version */
/* Version Format: 0xMMMMNNNN
          MMMM : Major Version 
          NNNN : Minor Version */
#define PBL_DEBUG_SHARED_DATA_VERSION        0x00010000
#define PBL_XBL_SC_SHARED_DATA_VERSION       0x00010000
#define PBL_TIMESTAMP_SHARED_DATA_VERSION    0x00010000

/*---------------------------------------------------------------------------
  Defines the data structure that is filled with data that is shared with
  the BL image. It may be necessary for the BL to make a deep copy of
  this structure for its own use if it wipes out PBL memory.
---------------------------------------------------------------------------*/
typedef struct _pbl_apps_xbl_sc_shared_data_entry_type{
  pbl_apps_xbl_shared_data_param_id_type param_id;
  uintnt                                 param_val;
  boolean                                is_valid_entry;
}pbl_apps_xbl_sc_shared_data_entry_type;

typedef struct boot_pbl_shared_data_type{
  uint32   version;
  uint32   num_of_entries;
  pbl_apps_xbl_sc_shared_data_entry_type  shared_data_entry[PBL_APPS_XBL_SHARED_DATA_PARAM_ID_MAX];
}boot_pbl_shared_data_type;

/* Shared data coming from PBL */

#endif /*BOOT_PBL_SHARED_V1_H*/