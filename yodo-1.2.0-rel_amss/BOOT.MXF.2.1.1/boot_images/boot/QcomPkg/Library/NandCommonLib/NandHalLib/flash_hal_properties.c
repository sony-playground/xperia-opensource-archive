/*====================================================================
 *
 * FILE: flash_hal_properties.c
 *
 * SERVICES: Set properties for Flash HAL
 *
 * DESCRIPTION: This file contain the interface API to set the
 *              properties for FLASH HAL.
 *
 * PUBLIC CLASSES AND STATIC FUNCTIONS:
 *
 * INITIALIZATION AND SEQUENCING REQUIREMENTS:
 *
 * Copyright (c) 2009-2010,2012,2020 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Confidential and Proprietary
 *==================================================================*/

/*===================================================================
 *
 *                       EDIT HISTORY FOR FILE
 *
 *   This section contains comments describing changes made to the
 *   module. Notice that changes are listed in reverse chronological
 *   order.
 *
 *  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/NandCommonLib/NandHalLib/flash_hal_properties.c#1 $ $DateTime: 2022/08/18 10:15:46 $ $Author: pwbldsvc $
 *
 *
 * when         who     what, where, why
 * ----------   ---     ----------------------------------------------
 * 06/08/20     sa      Ported for Olympic.
 * 09/05/12     sv      add cache maintenance APIS support
 * 07/30/12     sv      Remove DM specific codes
 * 02/15/12     sb      Add support for memutils in assembly
 * 10/21/10     sv      Add support to set wait API through hal properties
 * 02/05/10     mcg     Support to get DMOV configs from DAL
 * 07/21/09     sv      Initial Revision
 *==================================================================*/

/*===================================================================
 *
 *                     Include Files
 *
 ====================================================================*/

#include <flashi_hal.h>
#include "flash_osal.h"

/* Function declarations */
void *memcpy(void *dest, const void *src, size_t num_bytes);
void *memset(void *dest, int c, size_t num_bytes);
//void flash_hal_asm_memcpy(void *dest, const void *src, uint32 num_bytes);

/* Flash HAL Property structure which has the desired memory config
 * properties that can be configured from Flash DAL
 */
struct flash_hal_mem_cfg
{
  void *(*memcpy_fptr)(void *, uintnt, const void *, size_t); /* fptr to memscpy routine */
  void *(*memset_fptr)(void *, int, size_t);          /* fptr to memset routine */
};

/*
 * Flash HAL Property structure which has the desired wait properties 
 * that can be configured from Flash DAL
 */
struct flash_hal_wait_cfg
{
  void (*wait_fptr)(uint32); /* fptr to wait routine */
};

struct flash_hal_cache_cfg
{
  void (*cache_inval_fptr)(uint32 addr, uint32 len);
  void (*cache_clean_fptr)(uint32 addr, uint32 len);
};

/* Default property values used by Flash HAL */
struct flash_hal_properties
{
  struct flash_hal_mem_cfg mem_cfg;
  struct flash_hal_wait_cfg wait_cfg;
  struct flash_hal_cache_cfg cache_cfg;
};

struct flash_hal_properties flash_hal_prop_tbl = 
{
  {0, 0},   /* flash_hal_mem_cfg */
  {0},      /* flash_hal_wait_cfg */
  {0, 0}    /* flash_hal_cache_cfg */
};

/* memscpy wrapper for Flash HAL */
void *__memscpy(void *dest, uintnt dest_size, const void *src, size_t src_size)
{
  flash_memscpy(dest, dest_size, (void *)src, src_size);  
  return dest;
};

/* memcpy routine which copies data from source to destination
 * in a loop. This is introduced since some processors has issues
 * with standard memcpy routine while accessing uncached memory
 */
void *flash_hal_handle_unc_memcpy(void *dest, uintnt dest_num_bytes, 
  const void *src, size_t num_bytes)
{
  uint8 *  c_dest  = (uint8 *)  dest;
  uint8 *  c_src   = (uint8 *)  src;
  uintnt * l_dest  = (uintnt *) dest;
  uintnt * l_src   = (uintnt *) src;

  if (((((uintnt)dest) & 3) || (((uintnt)src) & 3)) && num_bytes)
  {
    while (((((uintnt)c_dest) & 3) || (((uintnt)c_src) & 3)) && num_bytes)
    {
      *c_dest++ = *c_src++;
      num_bytes--;
    }
  }

  l_dest = (uintnt *) c_dest;
  l_src = (uintnt *) c_src;

  while (num_bytes>=4)
  {
    *l_dest++= *l_src++;
    num_bytes -= 4;
  }

  c_dest = (uint8 *) l_dest;
  c_src = (uint8 *) l_src;

  if (num_bytes)
  {
    while (num_bytes--)
    {
      *c_dest++ = *c_src++;
    }
  }

  return dest;
}

/* memcpy routine in assembly. This is introduced in boot level flash driver
 * to improve the bootup time 
 */
void *flash_hal_handle_opti_memcpy(void *dest, uintnt dest_num_bytes, 
  const void *src, size_t num_bytes)
{
  __memscpy(dest, dest_num_bytes, src, num_bytes);
  return dest;
}

/* memset routine which sets memory location(s) with
 * a byte data. This is introduced since some processors has issues
 * with standard memset routine while accessing uncached memory
 */
void *flash_hal_handle_unc_memset(void *dest, int c, size_t num_bytes)
{
  uint32 i;
  uint8 *dest_ptr;

  dest_ptr = (uint8 *)dest;

  /*TBD: Optimizations */
  for(i = 0; i < num_bytes; i++)
  {
    dest_ptr[i] = (uint8)c;
  }
  return dest;
}

/* Configure the properties for Flash HAL */
void flash_hal_set_property(enum flash_hal_property id, void *value)
{
  switch (id)
  {
    case FLASH_HAL_PROPERTY_USE_STD_MEMUTIL:
      flash_hal_prop_tbl.mem_cfg.memcpy_fptr = __memscpy;
      flash_hal_prop_tbl.mem_cfg.memset_fptr = memset;
      break;

    case FLASH_HAL_PROPERTY_USE_INT_MEMUTIL:
      flash_hal_prop_tbl.mem_cfg.memcpy_fptr = flash_hal_handle_unc_memcpy;
      flash_hal_prop_tbl.mem_cfg.memset_fptr = flash_hal_handle_unc_memset;
      break;

    case FLASH_HAL_PROPERTY_USE_INT_ASM_MEMUTIL:
      flash_hal_prop_tbl.mem_cfg.memcpy_fptr = flash_hal_handle_opti_memcpy;
      flash_hal_prop_tbl.mem_cfg.memset_fptr = flash_hal_handle_unc_memset;
      break;

    case FLASH_HAL_PROPERTY_WAIT_CFG:
      flash_hal_prop_tbl.wait_cfg.wait_fptr = (void (*)(uint32))value;
      break;

    case FLASH_HAL_PROPERTY_CACHE_INVAL_CFG:
      flash_hal_prop_tbl.cache_cfg.cache_inval_fptr = (void (*)(uint32, uint32))value;
      break;

    case FLASH_HAL_PROPERTY_CACHE_CLEAN_CFG:
      flash_hal_prop_tbl.cache_cfg.cache_clean_fptr = (void (*)(uint32, uint32))value;
      break;

    default:
      break;
  }
}

/* memory copy wrapper for Flash HAL */
void *flash_hal_memcpy(void *dest, const void* src, uint32 len)
{
  return flash_hal_prop_tbl.mem_cfg.memcpy_fptr(dest, len, src, len);
}

/* memory set wrapper for Flash HAL */
void *flash_hal_memset(void *dest, int c, uint32 len)
{
  return  flash_hal_prop_tbl.mem_cfg.memset_fptr(dest, c, len);
}


/* wait wrapper for Flash HAL */
void flash_hal_busywait(uint32 wait_time_us)
{
  flash_hal_prop_tbl.wait_cfg.wait_fptr(wait_time_us);
}

/* cache clean wrapper for Flash HAL */
void flash_hal_cache_clean(uint32 addr, uint32 len)
{
  if(flash_hal_prop_tbl.cache_cfg.cache_clean_fptr)
  {
    flash_hal_prop_tbl.cache_cfg.cache_clean_fptr(addr, len);
  }
}

/* cache invalidate wrapper for Flash HAL */
void flash_hal_cache_inval(uint32 addr, uint32 len)
{
  if(flash_hal_prop_tbl.cache_cfg.cache_inval_fptr)
  {
    flash_hal_prop_tbl.cache_cfg.cache_inval_fptr(addr, len);
  }
}
