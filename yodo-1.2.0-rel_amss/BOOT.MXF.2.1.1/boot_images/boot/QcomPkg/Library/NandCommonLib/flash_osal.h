#ifndef FLASH_OSAL_H
#define FLASH_OSAL_H

/*====================================================================
 *
 * FILE:        flash_osal.h
 *
 * SERVICES:    OS wrapper function declarations for nand driver
 *
 * DESCRIPTION: OS wrapper functions declarations for nand driver
 *
 * PUBLIC CLASSES:  Not Applicable
 *
 * INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A
 *
 * Copyright (c) 2017,2020 QUALCOMM Technologies Incorporated.
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
 *  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/NandCommonLib/flash_osal.h#1 $ $DateTime: 2022/08/18 10:15:46 $ $Author: pwbldsvc $
 *
 *
 * when         who     what, where, why
 * ----------   ---     ----------------------------------------------
 * 06/08/20     sa      Ported for Olympic.
 * 03/03/17     eo      Initial Revision
 *==================================================================*/

/*===================================================================
 *
 *                     Include Files
 *
 ====================================================================*/

#include "flash_fwk.h"

/*===================================================================
 *
 *                     DEBUG DATA STRUCTURE
 *
 ====================================================================*/

/** @brief
    Information on a piece of memory allocated
  */
struct flash_osal_meminfo
{
  struct DALSYSMemInfo Info;
};

/*===================================================================
 *
 *                     UTIL FUNCTIONS
 *
 ====================================================================*/
/*
 * 32 bit CRC calculation for flash
 */
uint32 flash_crc32_calc(uint8 *mem, uint16 len, uint32 seed);

/*
 * Safe string copy function for flash
 */
uint32 flash_strcpy(uint8 *dest, const uint8 *src, uint32 len);

/*
 *  This function does a wait for a desired time in us.
 */
void flash_busy_wait(uint32 wait_time_us);

/* 
 * This function does cache clean on the given address 
 */
void flash_dcache_clean(uint32 addr, uint32 len);

/*
 * This function does cache invalidation on the given address 
 */
void flash_dcache_inval(uint32 addr, uint32 len);

/*
 * This function creates a sync object 
 */
uint32 flash_sync_create(void *sync_obj);

/*
 * This function does sync enter
 */
void flash_sync_enter(void *sync_handle);

/*
 * This function does sync leave
 */
void flash_sync_leave(void *sync_handle);

/*
 * This function memsets a memory buffer
 */
void flash_memset(void *mem, uint8 val, uint32 size);

/*
 * This function does a memscopy from source
 * buffer to destination buffer
 */
void flash_memscpy(void *dst, uint32 dst_size, void *src, uint32 src_size);
/*
 * This function does a memcopy from source
 * buffer to destination buffer
 */
void flash_memcpy(void *dst, void *src, uint32 size);

/*
 * This function does a memory allocation given 
 * a size specified
 */
uint32 flash_malloc(uint32 size, void **mem);

/*
 * This function does a free up of memory allocated
 */
void flash_free(void *mem);

/*
 * This function does a uncached memory allocation given 
 * a size specified
 */
uint32 flash_memregion_alloc(void *handle, uint32 size);

/*
 * This function returns back virtuak and physical memory for the
    handle allocated using 'flash_memregion_alloc'.
 */
uint32 flash_memregion_info(void *handle, struct flash_osal_meminfo *meminfo);

/*
 * This function does a uncached memory deallocation
 */
uint32 flash_free_memregion(void *handle);

#endif /* FLASH_DAL_UTIL_H */
