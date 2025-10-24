/*=======================================================================
 * FILE:        nand_wrapper.h
 *
 * SERVICES:    None
 *
 * GENERAL DESCRIPTION
 *    Declarations for read/write API wrapper functions
 *    in flash driver.
 *
 * Copyright (c) 2008-2010, 2018, 2020-2021 QUALCOMM Technologies Incorporated.
 * All Rights Reserved.
 * QUALCOMM Confidential and Proprietary
 *=======================================================================*/

/*===================================================================
 *
 *                       EDIT HISTORY FOR FILE
 *
 *   This section contains comments describing changes made to the
 *   module. Notice that changes are listed in reverse chronological
 *   order.
 *
 *  $Header: //components/dev/core.boot/5.1.1/glosch.core.boot.5.1.1.nand_cfg_olympic/QcomPkg/Library/NandJtagToolsLib/nand_wrapper.h#1 $ $DateTime: 2022/04/04 03:16:28 $ $Author: glosch $
 *
 *
 * when         who     what, where, why
 * ----------   ---     ----------------------------------------------
 * 01/07/21     sa      Added new API's for multipage reads.
 * 06/11/20     sa      Ported to Olympic.
 * 04/20/20     sa      Removed unused code, nand_sim.h
 * 11/16/18     sa      Added support for Multipage read.
 * 09/10/10     bb      Fix for unaligned memcpy failure with RVCT 4.0
 * 08/12/10     nr      Added FLASHLOG wrapper
 * 02/18/09     jz      Renamed nand_ to flash_prog_ for nand tool
 * 01/09/09     mm      Removed DAL Framework files for mibib.mbn
 *                      generation.
 * 11/26/08     bb      Initial Revision
 *==================================================================*/

/*===================================================================
 *
 *                     Include Files
 *
 ====================================================================*/

#include "DALFramework.h"
#include "nand_api.h"
#include "nand_core.h"

#ifdef FLASH_LOG_H
  #include FLASH_LOG_H
#else
  #define FLASHLOG(l, x)
#endif

struct flash_page_iovec
{
  uint32 start_page;       /**< Logical page used to start the operation */
  uint32 total_page_count;       /**< Number of pages to operate */
  uint32 main_size_bytes;  /**< Length of main data to read/write from a page in bytes */
  uint32 spare_size_bytes; /**< Length of spare data to read from a page in bytes */
};
/*
 * Wrapper for memcpy API. Introduced as a
 * Workaround for unaligned memcpy failure with RVCT 4.0
 */
void* nand_memcpy(void *out, const void *in, uintnt n);

/*
 * Wrapper function for flash write pages driver API
 */
int flash_prog_write_page(nand_handle_t handle, struct flash_info *dev_info,
  uint32 page, uint32 write_type, void *buffer);

/*
 * Wrapper function for flash write pages with udata
 */
int flash_prog_write_page_and_udata (nand_handle_t handle, struct flash_info *dev_info,
  uint32 page, uint32 write_type, void *buffer, void *spare_udata,
  uint32 spare_udata_blen);

/*
 * Wrapper function for flash read multiple pages driver API
 */
int flash_prog_read_pages(nand_handle_t handle, struct flash_info *dev_info,
  uint32 page, uint32 page_count, uint32 read_type, void *buffer);


/*
 * Wrapper function for flash read multiple pages with udata
 */
int flash_prog_read_pages_and_udata (nand_handle_t handle, struct flash_info *dev_info,
	uint32 page, uint32 page_count, uint32 read_type, void *buffer, void *spare_buffer, 
	uint32 spare_udata_len);

