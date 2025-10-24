/** @file
  Stub Lock lib Implementation
   
  Copyright (c) 2017, 2019, 2020 Qualcomm Technologies Inc. All rights reserved.
  
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 04/15/20   cm       Match LockLib.c functions
 07/24/17   yg       Initial version

=============================================================================*/

#include <Uefi.h>
#include <PiDxe.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/HobLib.h>
#include <Library/KernelLib.h>
typedef struct 
{
   UINT32     Sig;
   UINT32     Flags;
   //Mutex     *MutexPtr;
   UINTN      NestLevel;
   UINT32     MaxNest;
   UINT32     InactivityCnt;
} 
LockType;

BOOLEAN 
InitLockLib (VOID)
{
  return FALSE;
}

VOID* 
InitLegacyLock (OPTIONAL CONST CHAR8 *LockStrID)
{
	//LockType *LockPtr;
	return NULL;
	
}

VOID
DestroyLegacyLock (VOID* Handle)
{
 
}

VOID* 
InitLegacyRecursiveLock (OPTIONAL CONST CHAR8 *LockStrID)
{
    //LockType *LockPtr;
	return NULL;
}

VOID 
LegacyLock (VOID* Handle)
{
  
}

VOID 
LegacyUnLock (VOID* Handle)
{
 
}
