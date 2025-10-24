/*=======================================================================
 * FILE:        nand_wrapper.c
 *
 * SERVICES:    None
 *
 * GENERAL DESCRIPTION
 *    This file implements wrapper functions for
 *    read/write APIs in flash driver.
 *
 * Copyright (c) 2010-2015, 2018, 2020-2021 Qualcomm Technologies Incorporated.
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
 *  $Header: //components/dev/core.boot/5.1.1/glosch.core.boot.5.1.1.nand_cfg_olympic/QcomPkg/Library/NandJtagToolsLib/nand_wrapper.c#1 $ $DateTime: 2022/04/04 03:16:28 $ $Author: glosch $
 *
 *
 * when         who     what, where, why
 * ----------   ---     ----------------------------------------------
 * 01/07/21     sa      Fix NAND read for JTAG tools.
 * 06/11/20     sa      Ported to Olympic.
 * 11/16/18     sa      Added support for Multipage read.
 * 01/28/15     sb      Remove KW Banned Functions
 * 09/10/10     bb      Fix for unaligned memcpy failure with RVCT 4.0
 * 04/15/10     jz      Code cleanups
 * 02/18/09     jz      Renamed nand_ to flash_prog_ for nand tool
 * 11/26/08     bb      Initial Revision
 *==================================================================*/

/*===================================================================
 *
 *                     Include Files
 *
 ====================================================================*/

#include "nand_wrapper.h"
#include "stringl/stringl.h"

/* Buffers to be display main and spare data in JTAG tool. 
   These variables are used to store the buffer address passed by the clients.
*/
static uint8 *buffer_page_main_read = NULL;
static uint8 *buffer_page_spare_read = NULL;

/*
 * Initializes page data parameters and returns buffer size to use.
 * Store the buffers to be read by the tool later to display.
 */
static __inline uint32 get_buf_param(struct flash_info *dev_info,
  uint32 op_type,  uint32 page_count, void *buffer)
{
  
  uintnt buffer_size = 0;
  uintnt page_size = 0;
  void   *sbuffer = NULL;
  
  page_size = dev_info->nand_info.page_size_bytes;
 
  switch (op_type)
  {
    case NAND_ACCESS_RAW:
      buffer_page_main_read = buffer;
      buffer_page_spare_read = NULL;
      buffer_size = (dev_info->nand_info.total_page_size_bytes) * page_count;
      break;

    case NAND_ACCESS_MAIN:
      buffer_page_main_read = buffer;
      buffer_page_spare_read = NULL;
      buffer_size = (dev_info->nand_info.page_size_bytes) * page_count;
      break;

    case NAND_ACCESS_MAIN_SPARE:
      buffer_size = (dev_info->nand_info.total_page_size_bytes) * page_count ;
   
      sbuffer = (buffer_size > (page_size * page_count))?
           (void *)((uintnt)buffer + (page_size * page_count)): NULL;
           buffer_page_main_read = buffer;
      buffer_page_spare_read = sbuffer;
      break;

    case NAND_ACCESS_SPARE:
      buffer_size = (dev_info->nand_info.max_spare_udata_bytes) * page_count;

      buffer_page_main_read = NULL;
      sbuffer = (void *)((uintnt)buffer + (page_size * page_count));
      buffer_page_spare_read = sbuffer;  
      break;
  }

  return buffer_size;
}


/*
 * Wrapper function for flash write pages driver API
 */
int flash_prog_write_page(nand_handle_t handle, struct flash_info *dev_info,
   uint32 page, uint32 write_type, void *buffer)
{
  int result = FLASH_DEVICE_DONE;

  uint32 buffer_size = get_buf_param(dev_info, write_type, 1, buffer);

  result = nand_write(handle, write_type, page, 1, buffer, buffer_size);

  return result;
}

/*
 * Wrapper function for flash write pages with udata
 */
int flash_prog_write_page_and_udata (nand_handle_t handle, struct flash_info *dev_info,
  uint32 page, uint32 write_type, void *buffer, void *spare_udata,
  uint32 spare_udata_blen)
{
  int result = FLASH_DEVICE_DONE;

  uint32 buffer_size = get_buf_param(dev_info, write_type, 1, buffer);

  result = nand_write(handle, write_type, page, 1, buffer, buffer_size);

  return result;
} /* End of flash_nand_write_page_and_udata */


/*
 * Wrapper function for flash read multiple pages driver API
 */
int flash_prog_read_pages(nand_handle_t handle, struct flash_info *dev_info,
  uint32 page, uint32 num_pages, uint32 read_type, void *buffer)
{
  int result = FLASH_DEVICE_DONE;

  uint32 buffer_size = get_buf_param(dev_info, read_type, num_pages, buffer);
  
  result = nand_read(handle, read_type, page, num_pages, buffer, buffer_size);

  return result;
}

/*
 * Wrapper function for flash read pages with udata
 */
int flash_prog_read_pages_and_udata (nand_handle_t handle, struct flash_info *dev_info,
  uint32 page, uint32 num_pages, uint32 read_type, void *buffer, void *spare_udata,
  uint32 spare_udata_blen)
{
  int result = FLASH_DEVICE_DONE;     /* return status of read page operation */

  uint32 buffer_size = get_buf_param(dev_info, read_type, num_pages, buffer);

  result = nand_read(handle, read_type, page, num_pages, buffer, buffer_size);

  /* Copy the spare bytes to the user buffer */
  memscpy(spare_udata, spare_udata_blen, buffer_page_spare_read, spare_udata_blen);

  return result;

} /* End of flash_nand_read_page_and_udata */

/*
 * Wrapper for memcpy API. Introduced as a
 * Workaround for unaligned memcpy failure with RVCT 4.0
 */
void* nand_memcpy(void *out, const void *in, uintnt n)
{
  uintnt s_addr, d_addr;

  s_addr = (uintnt) out;
  d_addr = (uintnt) in;

  if ((s_addr & 0x3) || (d_addr & 0x3))
  {
    uintnt i;

    for (i=0; i<n; ++i)
    {
      *((char*)out+i) = *((char*)in+i);
    }
  }
  else
  {
    memscpy(out, n, in, n);
  }

  return out;
}

