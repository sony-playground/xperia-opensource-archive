#ifndef BOOT_CACHELIB_IF_H
#define BOOT_CACHELIB_IF_H
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
#include <Library/CacheMaintenanceLib.h>

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 

typedef struct boot_edk2_cache_if_type
{
  void (*InvalidateInstructionCache)(void);
  void* (*InvalidateInstructionCacheRange)(void* Address, UINTN Length);
  void (*WriteBackInvalidateDataCache)(void);
  void* (*WriteBackInvalidateDataCacheRange)(void* Address, UINTN Length);
  void (*WriteBackDataCache)(void);
  void* (*WriteBackDataCacheRange)(void* Address, UINTN Length);
  void (*InvalidateDataCache)(void);
  void* (*InvalidateDataCacheRange)(void* Address, UINTN Length);
} boot_edk2_cache_if_type;

extern boot_edk2_cache_if_type edk2_cache_if; 
#endif /* BOOT_EDK2_CACHE_IF_H */
