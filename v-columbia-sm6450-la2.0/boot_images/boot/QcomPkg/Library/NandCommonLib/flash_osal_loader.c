/*====================================================================
 *
 * FILE:        flash_osal_loader.c
 *
 * SERVICES:   OS wrapper function implementation for nand driver
 *
 * DESCRIPTION: OS wrapper function implementation for nand driverL
 *
 * PUBLIC CLASSES:  Not Applicable
 *
 * INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A
 *
 * Copyright (c) 2020 Qualcomm Technologies Incorporated.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *==================================================================*/

/*===================================================================
 *
 *                       EDIT HISTORY FOR FILE
 *
 *   This section contains comments describing changes made to the
 *   module. Notice that changes are listed in reverse chronological
 *   order.
 *
 *  $Header: //components/rel/core.boot/6.0/QcomPkg/Library/NandCommonLib/flash_osal_loader.c#1 $ $DateTime: 2020/06/18 10:10:50 $ $Author: pwbldsvc $
 *
 *
 * when         who     what, where, why
 * ----------   ---     ----------------------------------------------
 * 06/04/20     sa      Initial Revision
 *==================================================================*/

/*===================================================================
 *
 *                     Include Files
 *
 ====================================================================*/

#include "DALSys.h"
#include "busywait.h"
#include <Library/ArmLib.h>
#include <api/services/crc.h>

#include "flash_osal.h"

#define NAND_TPL                   TPL_CALLBACK

/* memory space marker */
#define DEVICE_SPACE_MAGIC_NUMBER  0xDEADCAFE

/* memory alignment */
#define FLASH_MEM_ALIGN_32         0x20//0x1F

/*
 * 32 bit CRC calculation for flash
 */
uint32 flash_crc32_calc(uint8 *mem, uint16 len, uint32 seed)
{
  return crc_32_calc(mem, len, seed);
}

/*
 * Safe string copy function for flash
 */
uint32 flash_strcpy(uint8 *dest, const uint8 *src, uint32 len)
{
  uint32  status = NAND_DEVICE_DONE;

  DALSYS_memscpy(dest, len, (void *)src, len);

  return status;
}

/*
 *  This function does a wait for a desired time in us.
 */
void flash_busy_wait(uint32 wait_time_us)
{
  busywait(wait_time_us);
}

/* This function does cache invalidation on the given address */
void flash_dcache_clean(uint32 addr, uint32 len)
{
  DALSYS_CacheCommand(DALSYS_CACHE_CMD_CLEAN, (uint32)addr, len);
}

/* This function does cache clean on the given address */
void flash_dcache_inval(uint32 addr, uint32 len)
{
  DALSYS_CacheCommand(DALSYS_CACHE_CMD_INVALIDATE, (uint32)addr, len);
}

uint32 flash_sync_create(void *sync_obj)
{
  NAND_STATUS   status = NAND_DEVICE_DONE;

  //DALSYS_SyncCreate(sync_obj);

  return status;
}

/* This function does sync enter */
void flash_sync_enter(void *sync_handle)
{
  DALSYS_SyncEnter(sync_handle);
}

/* This function does sync enter */
void flash_sync_leave(void *sync_handle)
{
  DALSYS_SyncLeave(sync_handle);
}

void flash_memset(void *mem, uint8 val, uint32 size)
{
  DALSYS_memset(mem, val, size);
}

void flash_memscpy(void *dst, uint32 dst_size, void *src, uint32 src_size)
{
  DALSYS_memscpy(dst, dst_size, src, src_size);
}

void flash_memcpy(void *dst, void *src, uint32 size)
{
  DALSYS_memscpy(dst, size,src,size);
}

uint32 flash_malloc(uint32 size, void **mem)
{
  NAND_STATUS     status = NAND_DEVICE_DONE;
  DALResult       result;

  result = DALSYS_Malloc(size, mem);
  if (result != DAL_SUCCESS)
  {
    status = NAND_DEVICE_FAIL;
    *mem = NULL;
  }

  return status;
}

void flash_free(void *mem)
{
  DALSYS_Free(mem);
}

uint32 flash_memregion_alloc(struct flash_osal_meminfo *meminfo, uint32 size)
{
  NAND_STATUS  status = NAND_DEVICE_DONE;

  DALSYS_MemRegionAlloc(DALSYS_MEM_PROPS_UNCACHED |
          DALSYS_MEM_PROPS_PHYS_CONT, DALSYS_MEM_ADDR_NOT_SPECIFIED,
          DALSYS_MEM_ADDR_NOT_SPECIFIED, size,meminfo->handle, NULL );

  return status;
}


uint32 flash_free_memregion(struct flash_osal_meminfo *meminfo)
{
  NAND_STATUS	status = NAND_DEVICE_DONE;

  DALSYS_DestroyObject(meminfo);

  return status;
}
