#ifndef BOOT_EDK2_ARMLIB_IF_H
#define BOOT_EDK2_ARMLIB_IF_H
/*===========================================================================

                    BOOT SMEM IF DEFINITIONS

DESCRIPTION
  Contains definition for smem if 

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2019 by QUALCOMM Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
05/21/20   rama    Initial revision

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <Library/ArmLib.h>

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 

typedef struct boot_edk2_armlib_if_type
{
  void (*ArmDataSynchronizationBarrier)(void);
  void (*ArmDataMemoryBarrier) (void);
  //UINT32 (*ArmReadCpacr) (void);
  void (*ArmWriteCpacr) (UINT32 Access);
  void (*ArmInstructionSynchronizationBarrier) (void);
  void (*ArmInvalidateDataCache) (void);
  void (*ArmInvalidateInstructionCache) (void);
  //void(*ArmEnableCachesAndMmu) (void);
  void (*ArmDisableCachesAndMmu) (void);
} boot_edk2_armlib_if_type;

extern boot_edk2_armlib_if_type edk2_armlib_if; 
#endif /* BOOT_EDK2_ARMLIB_IF_H */