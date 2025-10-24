#ifndef BOOT_EDK2_MMU_IF_H
#define BOOT_EDK2_MMU_IF_H
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
5/21/20   rama     Initial Revision

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <Library/ArmMmuLib.h>
#include <ArmMmuLibEfiAttributesMap.h>

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 

typedef struct boot_edk2_mmu_if_type
{
  EFI_STATUS (*ArmConfigureMmu)(ARM_MEMORY_REGION_DESCRIPTOR *MemoryTable, void **TranslationTableBase OPTIONAL, UINTN *TranslationTableSize);
  EFI_STATUS (*ArmSetMemoryAttributes)(EFI_PHYSICAL_ADDRESS Address, UINT64 Length,UINT64 Attributes);
} boot_edk2_mmu_if_type;

extern boot_edk2_mmu_if_type edk2_mmu_if;
#endif /* BOOT_EDK2_MMU_IF_H */
