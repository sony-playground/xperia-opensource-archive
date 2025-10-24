
/**
 * @file usb4_mem.c
 *
 * @brief USB4 Memory DMA pools.
 *
 * Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 */

/*----------------------------------------------------------------------------
 * Include Files
 *-------------------------------------------------------------------------*/
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UncachedMemoryAllocationLib.h>
#include <Library/MemoryAllocationLib.h>
#include <string.h>       // memset
#include <Usb4Utils.h>
#include "usb4_mem.h"     // DMA API declaration, and structs
// #include "usb4_logger.h"  // Logging utilities
// #include "VVDRV_deo.h"          // DEO mempool and dma
//#include "usb4_utils.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Type Declarations
 *-------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static variables
 *-------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global variables
 *-------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static functions
 *-------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * API functions implementation
 *-------------------------------------------------------------------------*/

void* usb4_mem_alloc(UINT32 size, UINT16 flags)
{
  void* result = NULL;

  result = (void*)AllocatePool(size);
  USB4_ASSERT(result);
  gBS->SetMem(result, size, 0);
    
  return result;
}

void usb4_mem_free(void* buff)
{
  if (buff)
  {
    FreePool(buff);
  }
}


// This API reserved for aligned uncached memory
int usb4_mem_dma_alloc(usb4_buff* buff)
{
  if (NULL == buff)
  {
    USB4_ERROR_STACK_MSG(-1, "NULL input parameter");
    return -1;
  }

  buff->vaddr = (UINT8*)UncachedAllocateAlignedPool(buff->size_bytes, 4096); // Use conservative alignment
  buff->paddr = (UINT64)buff->vaddr;
  usb4_mem_memset(buff->vaddr, 0, buff->size_bytes);
  return 0;
}


void usb4_mem_dma_free(usb4_buff* buff)
{
  if (NULL == buff)
  {
    USB4_ERROR_STACK_MSG(-1, "NULL input parameter");
    return;
  }

  if (NULL == buff->handle)
  {
    return; /* exit gracefully! */
  }

  UncachedFreeAlignedPool(buff->vaddr);
  buff->handle = NULL;
  buff->vaddr = NULL;
  buff->paddr = 0;
}

int usb4_mem_strncmp(const UINT8* buffA, const UINT8* buffB, UINT32 max_bytes)
{
  UINT32 i = 0;
  for (i = 0; i < max_bytes; ++i)
  {
    if (buffA[i] != buffB[i])
    {
      return i;
    }
  }
  return 0;
}

int usb4_mem_memcpy(void* dest, const void* src, UINT32 n)
{
#if 0
  const UINT8* s;
  UINT8* d;
  UINT32 i;
#endif

  if ((NULL == dest) || (NULL == src))
  {
    USB4_ERROR_STACK_MSG(-1, "Null input");
    return -1;
  }

#if 0
  s = (const UINT8*)(src);
  d = (UINT8*)(dest);    

  for (i = 0; i < n; ++i)
  {
    d[i] = s[i];
  }
#endif

  gBS->CopyMem(dest, (void*)src, n);

  return 0;
}

int usb4_mem_memcpy_custom(void* dest, const void* src, UINT32 n)
{
  const UINT8* s;
  UINT8* d;
  UINT32 i;

  if ((NULL == dest) || (NULL == src))
  {
    USB4_ERROR_STACK_MSG(-1, "Null input");
    return -1;
  }

  s = (const UINT8*)(src);
  d = (UINT8*)(dest);    

  for (i = 0; i < n; ++i)
  {
    d[i] = s[i];
  }

  return 0;
}



// ch is val to be set
// n is # of bytes
int usb4_mem_memset(void* buff, int ch, UINT32 n)
{
  if (NULL == buff)
  {
    USB4_ERROR_STACK_MSG(-1, "Null input");
    return -1;
  }
  gBS->SetMem(buff, n, 0);
  return 0;
}

