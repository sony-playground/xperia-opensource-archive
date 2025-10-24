/**
  Copyright (c) 2021, Qualcomm Technologies, Inc. All rights reserved.
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 08/16/21   ck      Added edit history and copyright

=============================================================================*/
/*==========================================================================

                   INCLUDE FILES

===========================================================================*/
#include "boot_comdef.h"
#include "boot_config_data.h"


const uint8 config_data_table[CONFIG_DATA_TABLE_MAX_SIZE] =
{
  /* Header - corresponds to struct cdt_header in boot_config_data.h */

  0x43, 0x44, 0x54, 0x00,
  0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x00,

  /* Meta data - corresponds to struct cdb_meta in boot_config_data.h */

  0x12, 0x00, 0x06, 0x00,

  /*
   * Block data - corresponds to PlatformInfoCDTType, a locally-defined type in
   *              PlatformInfoLoader.c
   */

  0x03, 0x08, 0x01, 0x00,
  0x00, 0x00,

};

/**
    cdt table size
*/
uint32 config_data_table_size = 26;
