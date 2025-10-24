/** @file AllocPagePoolLib.c

  Implementation of page allocator in XBL_Loader

  Copyright (c) 2020 Qualcomm Technologies Inc. All rights reserved. 

**/

/*=============================================================================
                              EDIT HISTORY

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 08/25/20   ck      Added AllocatePages
 05/10/20   ds      initial revision
=============================================================================*/

#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include "DALSys.h"
#include "SizeInfo.h"

STATIC UINT64 LdrPgAllocCount = 0;

VOID *
EFIAPI
AllocateAlignedPages(IN UINTN Pages, UINTN Alignment)
{
  VOID *MemP = NULL;
  DALResult ret = 0;
  
  LdrPgAllocCount+=Pages;

  ret = DALSYS_Memalign((Pages * SIZE_4KB), Alignment, &MemP);
  if(ret != DAL_SUCCESS)
  {
    return NULL;
  }
  return MemP;
}


VOID *
EFIAPI
AllocatePages(IN UINTN Pages)
{
  VOID *MemP = NULL;
  DALResult ret = 0;
  
  LdrPgAllocCount+=Pages;

  ret = DALSYS_Memalign((Pages * SIZE_4KB), SIZE_4KB, &MemP);
  if(ret != DAL_SUCCESS)
  {
    return NULL;
  }
  return MemP;
}


VOID EFIAPI FreePages(VOID *Buffer, UINTN Pages)
{
  DALSYS_Free(Buffer);
}

