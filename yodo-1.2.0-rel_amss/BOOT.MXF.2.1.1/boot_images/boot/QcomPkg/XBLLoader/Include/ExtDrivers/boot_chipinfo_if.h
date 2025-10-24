#ifndef BOOT_CHIPINFO_IF_H
#define BOOT_CHIPINFO_IF_H

/*===========================================================================

                    BOOT CHIPINFO IF DEFINITIONS

DESCRIPTION
  Contains definition for chip info interface

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2022 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/05/22   rama    Initial Revision
===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <boot_error_if.h>
#include <ChipInfo.h>


/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 




typedef struct boot_chipinfo_if_type
{
  bl_error_boot_type (*get_chip_version)(ChipInfoVersionType *);
  bl_error_boot_type (*get_raw_chip_version)(uint32 *);
  bl_error_boot_type (*get_chip_id)(ChipInfoIdType *);
  bl_error_boot_type (*get_raw_chip_id)(uint32 *);
  bl_error_boot_type (*get_chip_id_string)(char *, uint32);
  bl_error_boot_type (*get_chip_family)(ChipInfoFamilyType *);
  bl_error_boot_type (*get_marketing_name_string) (char *, uint32);
  bl_error_boot_type (*get_modem_support) (ChipInfoModemType *);
  bl_error_boot_type (*get_serial_number) (ChipInfoSerialNumType *);
  bl_error_boot_type (*get_foundry_id) (ChipInfoFoundryIdType *);
  bl_error_boot_type (*get_raw_device_family) (uint32 *);
  bl_error_boot_type (*get_raw_device_number) (uint32 *);
  bl_error_boot_type (*get_qfprom_chip_id) (ChipInfoQFPROMChipIdType *);
  bl_error_boot_type (*get_defective_part) (ChipInfoPartType, uint32 *);
  bl_error_boot_type (*get_defective_cpus) (uint32, uint32 *);
  bl_error_boot_type (*get_chipinfo_data) (ChipInfoIdType *, ChipInfoVersionType *, ChipInfoFamilyType *);
  bl_error_boot_type (*init) (void);
  
} boot_chipinfo_if_type;


typedef enum
{
  BL_ERR_CHIPINFO_INTERFACE_FAILURE = BL_ERR_CUSTOM_ERRORS_START
}boot_chipinfo_error_type;


extern boot_chipinfo_if_type chipinfo_if;

#endif /* BOOT_CHIPINFO_IF_H */
