/*====================================================================
 *
 * FILE:        flash_osal_core.c
 *
 * SERVICES:   OS wrapper function implementation for nand driver
 *
 * DESCRIPTION: OS wrapper function implementation for nand driverL
 *
 * PUBLIC CLASSES:  Not Applicable
 *
 * INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A
 *
 * Copyright (c) 2017,2020, 2022 Qualcomm Technologies Incorporated.
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
 *  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/NandCommonLib/flash_osal_core.c#1 $ $DateTime: 2022/08/18 10:15:46 $ $Author: pwbldsvc $
 *
 *
 * when         who     what, where, why
 * ----------   ---     ----------------------------------------------
 * 08/09/22     gk      Ported changes for Pinnacles.
 * 12/08/20     sa      Send right device parameter for xfer step.
 * 07/20/20     sa      Ported changes for Xfer steps.
 * 06/08/20     sa      Ported for Olympic.
 * 03/03/17     eo      Initial Revision
 *==================================================================*/

/*===================================================================
 *
 *                     Include Files
 *
 ====================================================================*/
#include <Uefi.h>
#include <Library/PcdLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Protocol/LoadedImage.h>
#include <Library/CacheMaintenanceLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/QcomBaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UncachedMemoryAllocationLib.h>
#include <Library/TimerLib.h>
#include <Library/ArmLib.h>
#include <api/services/crc.h>

#include "DALSys.h"
#include "flash_osal.h"
#include "flash_nand_partition.h"
#include "flash_nand_config.h"
#include "flash_nand.h"

#define NAND_TPL                   TPL_CALLBACK

/* memory space marker */
#define DEVICE_SPACE_MAGIC_NUMBER  0xDEADCAFE

/* memory alignment */
#define FLASH_MEM_ALIGN_32         0x20//0x1F

static UINTN nand_sync_lock;

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
  uint32  status;

  status = (uint32)AsciiStrCpyS( (char *)dest, (UINTN)len, (const char *)src);
  dest[len-1] ='\0';

  return status;
}

/*
 *  This function does a wait for a desired time in us.
 */
void flash_busy_wait(uint32 wait_time_us)
{
  MicroSecondDelay(wait_time_us);
}

/* This function does cache invalidation on the given address */
void flash_dcache_clean(uint32 addr, uint32 len)
{
  WriteBackInvalidateDataCacheRange( (void *)(uintnt)addr, len);
}

/* This function does cache clean on the given address */
void flash_dcache_inval(uint32 addr, uint32 len)
{
  InvalidateDataCacheRange( (void *)(uintnt)addr, len);
}

uint32 flash_sync_create(void *sync_obj)
{
  NAND_STATUS   status = NAND_DEVICE_DONE;

  return status;
}

/* This function does sync enter */
void flash_sync_enter(void *sync_handle)
{
  nand_sync_lock = gBS->RaiseTPL(NAND_TPL);
}

/* This function does sync enter */
void flash_sync_leave(void *sync_handle)
{
  gBS->RestoreTPL(nand_sync_lock);
}

void flash_memset(void *mem, uint8 val, uint32 size)
{
  SetMem(mem, size, val);
}

void flash_memscpy(void *dst, uint32 dst_size, void *src, uint32 src_size)
{
  return (void)CopyMemS(dst, dst_size, src, src_size);
}

void flash_memcpy(void *dst, void *src, uint32 size)
{
  return (void)CopyMemS(dst, size, src, size);
}

uint32 flash_malloc(uint32 size, void **mem)
{
  NAND_STATUS     status = NAND_DEVICE_DONE;

  if (EFI_SUCCESS != gBS->AllocatePool(EfiBootServicesData,size,mem))
  {
    status = NAND_DEVICE_FAIL;
    DEBUG((EFI_D_INFO, "Allocate memory of size 0x%x	   [FAILED]\n",size));
  }
  return status;
}

void flash_free(void *mem)
{
  gBS->FreePool(mem);
}

uint32 flash_memregion_alloc(void *handle, uint32 size)
{
  NAND_STATUS  status = NAND_DEVICE_DONE;
  DALResult       result;

  result = DALSYS_MemRegionAlloc(DALSYS_MEM_PROPS_EXT_NORM_MEM |
          DALSYS_MEM_PROPS_PHYS_CONT, DALSYS_MEM_ADDR_NOT_SPECIFIED,
          DALSYS_MEM_ADDR_NOT_SPECIFIED, size,handle, NULL );

  if (result != DAL_SUCCESS)
  {
    status = NAND_DEVICE_FAIL;
    handle = NULL;
  }

    return status;
  }

uint32 flash_memregion_info(void *handle, struct flash_osal_meminfo *meminfo)
{
  NAND_STATUS  status = NAND_DEVICE_DONE;
  DALResult       result;

  result = DALSYS_MemInfo(handle, &meminfo->Info);

  if (result != DAL_SUCCESS)
  {
    status = NAND_DEVICE_FAIL;
    handle = NULL;
  }

  return status;
}

uint32 flash_free_memregion(void *handle)
{
  NAND_STATUS	status = NAND_DEVICE_DONE;

  status = DALSYS_DestroyObject(handle);

  return status;
}

/************ Partition Table Handling APIs *****************/

/*
 * Reads the MIBIB from the SMEM
 */
int smem_retrieve_mibib(flash_client_ctxt *client_ctxt)
{
   return smem_retrieve_mibib_internal(client_ctxt);
}

/*
 * Reads the MIBIB from the flash
 */
int nand_retrieve_mibib(flash_client_ctxt *client_ctxt)
{
   return nand_retrieve_mibib_internal(client_ctxt);
}


/* This function is used to update SMEM with the newly read mibib table
 */
int smem_update_mibib( uint32 total_tbl_size )
{
   return smem_update_mibib_internal(total_tbl_size);
}

/* This function is used to set the xfer steps.
 */
int nand_set_xfer_steps(flash_client_ctxt *client_ctxt, struct flash_nand_cfg_data *nand_cfgs, struct flash_nand_params *device)
{
  return NAND_DEVICE_DONE;
}

/* This function is used to get the onfi timing mode.
 */
int nand_get_onfi_timing_mode(flash_client_ctxt *client_ctxt, struct flash_nand_params *param)
{
  return NAND_DEVICE_DONE;
}

