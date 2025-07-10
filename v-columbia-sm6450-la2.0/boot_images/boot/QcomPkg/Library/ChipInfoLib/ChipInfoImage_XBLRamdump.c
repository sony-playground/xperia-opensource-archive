/*
 ===============================================================================

FILE: ChipInfoImage.c

DESCRIPTION:  Image-specific implementations of external functions used by
              ChipInfo which are accessed using different APIs on each image

 ================================================================================
 Copyright (c) 2017, 2019, 2023 Qualcomm Technologies Inc. All rights reserved.
 ================================================================================

 $Header: //components/dev/core.boot/6.1/nnunna.core.boot.6.1.lanai_qultivate/QcomPkg/Library/ChipInfoLib/ChipInfoImage_XBLLoader.c#1 $
 $DateTime: 2023/04/18 21:55:34 $
 $Author: nnunna $

 =============================================================================*/

/*=============================================================================
  Include Files
  =============================================================================*/
#include <string.h>
#include "Library/MemoryAllocationLib.h"
#include "ChipInfoImage.h"
#include "PlatformInfoDefs.h"
#include "smem.h"
#include "DALSys.h"
#include <stdlib.h>
#include <stdio.h>

/*=============================================================================
  Macros
  =============================================================================*/


/*=============================================================================
  Data definitions
  =============================================================================*/


/*=============================================================================
  Functions
  =============================================================================*/
DalPlatformInfoSMemType *
ChipInfo_GetSocInfo
(
  void
)
{
  DalPlatformInfoSMemType *pSMem;
  uint32 nSize;

  pSMem = (DalPlatformInfoSMemType *)smem_get_addr(SMEM_HW_SW_BUILD_ID, &nSize);
  if (pSMem == NULL || nSize == 0)
  {
  return NULL;
}

  return pSMem;
}

void
ChipInfo_UnmapSMem
(
  void
)
{
  // Nothing to unmap
  return;
}

void *
ChipInfo_malloc
(
  uint32 nSize
)
{
  void* pAddr = NULL;
  
  if(DALSYS_Malloc(nSize,(void **)&pAddr)==DAL_SUCCESS);
  return (void*)(pAddr);
}


void *
ChipInfo_memcpy
(
  void *restrict pDest,
  uint32 nDestLen,
  const void *restrict pSrc,
  uint32 nSrcLen
)
{

  if (pDest == NULL || nDestLen == 0 || pSrc == NULL || nSrcLen == 0)
  {
  return NULL;
}

  return memcpy(pDest, pSrc, nDestLen);
}


char *
ChipInfo_strcpy
(
  char *szDest,
  const char *szSrc,
  uint32 nDestLen
)
{
  if (szDest == NULL || szSrc == NULL || nDestLen == 0)
  {
    return NULL;
  }

  strlcpy(szDest, szSrc, nDestLen);
  return szDest;
}
