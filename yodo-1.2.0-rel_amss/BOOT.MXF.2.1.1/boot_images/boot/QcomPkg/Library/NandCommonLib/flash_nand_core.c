/*=============================================================================
 *
 * FILE:      flash_nand_core.c
 *
 * DESCRIPTION: This file initializes the flash NAND core APIs
 *              using predefined HAL APIs.
 *
 * PUBLIC CLASSES:  Not Applicable
 *
 * INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A
 *
 * Copyright (c) 2009-2012, 2014 ,2019-2020 Qualcomm Technologies, Inc. All Rights Reserved
 * All Rights Reserved.
 * QUALCOMM Confidential and Proprietary
 *===========================================================================*/

/*===================================================================
 *
 *                       EDIT HISTORY FOR FILE
 *
 *   This section contains comments describing changes made to the
 *   module. Notice that changes are listed in reverse chronological
 *   order.
 *
 *  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/NandCommonLib/flash_nand_core.c#1 $ $DateTime: 2022/08/18 10:15:46 $ $Author: pwbldsvc $
 *
 *
 * when         who     what, where, why
 * ----------   ---     ----------------------------------------------
 * 08/10/20     sa      Remove malloc for block erase status.
 * 06/21/20     sa      Cleanup.
 * 06/04/20     sa      Moved from flash.h to nand_api.h
 * 05/03/19     sa      Enbled Storage Profiling feature.
 * 02/15/19     sa      Added support for pagescope/multipage.
 * 09/19/14     eo      Add bad block management support
 * 09/05/12     sv      cleanups
 * 07/30/12     sv      Remove Spare only read/write codes
 * 07/27/12     sv      BAM based NAND drvier/Remove 2x support codes
 * 03/19/12     sv      Adapt fo SPI NOR power management changes
 * 03/19/12     eo      Support for erase blocks by size
 * 05/20/11     bb      Flash driver Optimization
 * 11/12/10     jz      hal_id cleanup
 * 10/24/10     sb      Fix for Hexagon compilation error on 9K
 * 08/11/10     nr      Added stats framework support
 * 06/15/10     jz      Updated for 2X support
 * 06/14/10     sb      Fix for compilation error with Hexagon 2.0-GCC4.x
 * 05/11/10     eo      Modified VTBL for NOR support
 * 02/12/10     wt      Modified Babylon Marker for 2X support
 * 12/28/09     sc      Added 2x support in DAL
 * 11/24/09     jz      Fixed compiler warnings
 * 10/23/09     mh      Add support for multiple hal_ids per client
 * 10/15/09     sv      Update Babylon marker names
 * 08/11/09     bb      Added Support for optimized multi r/w-copy APIs
 * 08/07/09     bb      Bringing back changes after WM7 release
 * 08/07/09     bb      Stamping Version 2 for WM7 release
 * 07/14/09     eo      Remove extern function declaration
 * 05/29/09     mh      Change nand_read_id signature to use hal_id
 * 05/11/09     bb      Support for babylon
 * 03/26/09     bb      Added predefined support with DM
 * 02/02/09     dp      Initial Revision
 *==================================================================*/

/*===================================================================
 *
 *                     Include Files
 *
 ====================================================================*/

#include "flash_nand_entry.h"
#include "flash_nand.h"
#include "flash_osal.h"
#include "StorageCommon.h"

/*------------------------------------------------------------------------------
  Variables local to this file.
------------------------------------------------------------------------------*/

//flash_vtbl nand_base_vtbl = {NULL};

/*------------------------------------------------------------------------------
  Variables global in this driver.
------------------------------------------------------------------------------*/

/* HAL workspace buffer address */
extern uint32 hal_ws_buffer;

/* HAL workspace buffer size in bytes */
extern uint32 hal_ws_buffer_size;

/*------------------------------------------------------------------------------
  Extern variable(s) and function(s).
------------------------------------------------------------------------------*/

/* NAND entry init data */
extern struct nand_entry_data nand_entry_init_data;

/*------------------------------------------------------------------------------
  Following functions are local to this driver.
------------------------------------------------------------------------------*/

static void nand_set_buff_desc(struct flash_hal_buffer_desc *dest_desc,
  struct flash_hal_buffer_desc *src_desc, uint32 data_size, uint32 page_count)
{
    uint32 total_data_size = data_size * page_count;
    dest_desc->buff_vaddr = src_desc->buff_vaddr + total_data_size;
    dest_desc->buff_paddr = src_desc->buff_paddr + total_data_size;
    dest_desc->buff_size  = src_desc->buff_size - total_data_size;
    dest_desc->num_pages  = src_desc->num_pages - page_count;
 }

/* This function will be used to read more than 1 page. */
static int nand_read_mpages(flash_client_ctxt *client_ctxt,
  struct flash_hal_predef_page_data *page_data)
{
  int    result = NAND_DEVICE_DONE;
  uint32 read_sync_state = 1, buff_desc_count;
  uint32 hal_id, page_count, page_read_count = 1;
  struct flash_hal_buffer_desc *buf_desc;
  struct flash_hal_predef_op_list *op_list;
  struct flash_hal_buffer_desc saved_buf_desc[2]; 
  enum   flash_hal_status hal_status = FLASH_HAL_FAIL;
  enum   flash_hal_status hal_erased_status = FLASH_HAL_ERASED_PAGE;

  /* IMPORTANT NOTE : This code assumes that we are already
     in the critical section lock. The unlock/lock will be done
     when demand paging enabled
     (when nand_entry_init_data.multi_rw_support_count = 1).

     The SYNC enter/relase in this code done only when
     FLASH_MULTI_RW_SUPPORT_COUNT = 1. Otherwise the code
     assumes the Synchronization is handled in the higher
     layers (flash_nand_entry.c).

     When multi count is 1, the code releases the lock
     after every page operation except for the last page.
     And re-enters for the next page. flash_nand_entry will
     be releasing the lock for the last page.
   */

  hal_id = client_ctxt->client_data.hal_id;
  buf_desc = page_data->buff_desc;
  page_count = page_data->total_pages;
  buff_desc_count = page_data->buff_desc_count;
    
  /* Save the buffer descriptors */
  nand_set_buff_desc(&saved_buf_desc[0], buf_desc, 0, 0);
  nand_set_buff_desc(&saved_buf_desc[1], (buf_desc + 1), 0, 0);

  /* This will be used to limit the number of pages to read when pagecope/multipage is disabled.
      If multipage is disabled, please change 'FLASH_MULTI_R_SUPPORT_COUNT' to '1' page count  */
  page_read_count = (page_count < nand_entry_init_data.multi_read_support_count) ?
        page_count : nand_entry_init_data.multi_read_support_count;

  while ((page_count) && ((NAND_DEVICE_DONE == result) || (NAND_DEVICE_FAIL_PAGE_ERASED == result)))
  {
    if (!read_sync_state)
    {
      //DALSYS_SyncEnter(client_ctxt->flash_dev_ctxt->handle_dev_sync);
      flash_sync_enter(client_ctxt->flash_dev_ctxt->handle_dev_sync);
      read_sync_state = 1;
    }

    if(page_read_count >= 3)
    {        
	  page_data->total_pages = page_read_count;
      flash_hal_read_mpages(hal_id, page_data, &op_list, &hal_status);
    }
	else
	{
	  page_read_count = 1;
	  page_data->total_pages = page_read_count;
    flash_hal_read_page(hal_id, page_data, &op_list, &hal_status);
    }

    if (FLASH_HAL_SUCCESS != hal_status)
    {
      if (FLASH_HAL_ERASED_PAGE == hal_status)
      {
        result = NAND_DEVICE_FAIL_PAGE_ERASED;
        FLASHLOG(4, ("Reading Page : Erase page detected!\n"));
      }
      else
      {
        result = NAND_DEVICE_FAIL;
        FLASHLOG(3, ("Reading Page : FAILED\n"));
      }
    }

    if (FLASH_HAL_ERASED_PAGE != hal_status)
    {
      hal_erased_status = hal_status;
    }
	
    page_count -= page_read_count;

    if ((page_count) && ((NAND_DEVICE_DONE == result) || (NAND_DEVICE_FAIL_PAGE_ERASED == result)))
    {
      //DALSYS_SyncLeave(client_ctxt->flash_dev_ctxt->handle_dev_sync);
      flash_sync_leave(client_ctxt->flash_dev_ctxt->handle_dev_sync);
      read_sync_state = 0;

      /* The Buffer descriptor ajustment
           This logic is to avoid extra memcopy of client passed
           buf_desc data to a local buffer. We pass the client buff_desc
           directly down to the HAL. This buff_desc needs adjustments
           when the number of pages in the current buffer descriptor
           larger than FLASH_MULTI_RW_SUPPORT_COUNT.

           Eg. Client requests to read 10 pages, when multi count is 3

           The save-restore uses a temperory buff_desc_save_info
           data structure to hold the saved data. And it is
           required to give back the client, what it passed.
       */

      nand_set_buff_desc(buf_desc, buf_desc, page_data->main_size_bytes, 
        page_read_count);

      nand_set_buff_desc((buf_desc + 1), (buf_desc + 1), page_data->spare_size_bytes, 
        page_read_count);

      /* Update the page_data fields for next transfer */
      page_data->start_page += page_read_count;

      if (page_count < page_read_count)
      {
        page_read_count = page_count;
      }

      page_data->total_pages = page_read_count;
      page_data->buff_desc_count = buff_desc_count;
      page_data->buff_desc = buf_desc;
    }
  }

  /* Restore the buffer descriptors */
  nand_set_buff_desc(buf_desc, &saved_buf_desc[0], 0, 0);
  nand_set_buff_desc((buf_desc + 1), &saved_buf_desc[1], 0, 0);

  if (FLASH_HAL_ERASED_PAGE != hal_erased_status)
  {
    result = (FLASH_HAL_SUCCESS == hal_erased_status)? NAND_DEVICE_DONE: NAND_DEVICE_FAIL;
  }

  return result;
}


static int nand_write_mpages(flash_client_ctxt *client_ctxt,
  struct flash_hal_predef_page_data *page_data)
{
  int    result = NAND_DEVICE_DONE;
  uint32 write_sync_state = 1, buff_desc_count;
  uint32 hal_id, page_count, page_write_count = 1;
  struct flash_hal_buffer_desc *buf_desc;
  struct flash_hal_predef_op_list *op_list;
  struct flash_hal_buffer_desc saved_buf_desc[2]; 
  enum   flash_hal_status hal_status = FLASH_HAL_FAIL;

  hal_id = client_ctxt->client_data.hal_id;
  buf_desc = page_data->buff_desc;
  page_count = page_data->total_pages;
  buff_desc_count = page_data->buff_desc_count;

  /* Save the buffer descriptors */
  nand_set_buff_desc(&saved_buf_desc[0], buf_desc, 0, 0);
  nand_set_buff_desc(&saved_buf_desc[1], (buf_desc + 1), 0, 0);

  page_write_count =
    (page_count < nand_entry_init_data.multi_write_support_count) ?
    page_count : nand_entry_init_data.multi_write_support_count;

  page_data->total_pages = page_write_count;

  while ((page_count) && (NAND_DEVICE_DONE == result))
  {
    /* IMPORTANT NOTE : This code assumes that we are already
       in the critical section lock. The unlock/lock will be done
       when demand paging enabled
       (when nand_entry_init_data.multi_rw_support_count = 1).

       The SYNC enter/relase in this code done only when
       FLASH_MULTI_RW_SUPPORT_COUNT = 1. Otherwise the code
       assumes the Synchronization is handled in the higher
       layers (flash_nand_entry.c).

       When multi count is 1, the code releases the lock
       after every page operation except for the last page.
       And re-enters for the next page. flash_nand_entry will
       be releasing the lock for the last page.
     */

    if (!write_sync_state)
    {
      //DALSYS_SyncEnter(client_ctxt->flash_dev_ctxt->handle_dev_sync);
      flash_sync_enter(client_ctxt->flash_dev_ctxt->handle_dev_sync);
      write_sync_state = 1;
    }

    flash_hal_write_page(hal_id, page_data, &op_list, &hal_status);

    if (FLASH_HAL_SUCCESS != hal_status)
    {
      result = NAND_DEVICE_FAIL;
      FLASHLOG(3, ("Writing Page : FAILED\n"));
    }

    page_count -= page_write_count;

    if ((page_count) && (NAND_DEVICE_DONE == result))
    {
      //DALSYS_SyncLeave(client_ctxt->flash_dev_ctxt->handle_dev_sync);
      flash_sync_leave(client_ctxt->flash_dev_ctxt->handle_dev_sync);
      write_sync_state = 0;

      /* The Buffer descriptor ajustment
           This logic is to avoid extra memcopy of client passed
           buf_desc data to a local buffer. We pass the client buff_desc
           directly down to the HAL. This buff_desc needs adjustments
           when the number of pages in the current buffer descriptor
           larger than FLASH_MULTI_RW_SUPPORT_COUNT.

           Eg. Client requests to write 10 pages, when multi count is 3

           The save-restore uses a temperory buff_desc_save_info
           data structure to hold the saved data. And it is
           required to give back the client, what it passed.
       */
      nand_set_buff_desc(buf_desc, buf_desc, page_data->main_size_bytes, 
        page_write_count);

      nand_set_buff_desc((buf_desc + 1), (buf_desc + 1), 
        page_data->spare_size_bytes, page_write_count);

      /* Update the page_data fields for next transfer */
      page_data->start_page += page_write_count;

      if (page_count < page_write_count)
      {
        page_write_count = page_count;
      }

      page_data->total_pages = page_write_count;
      page_data->buff_desc_count = buff_desc_count;
    }
  }

  /* Restore the buffer descriptors */
  nand_set_buff_desc(buf_desc, &saved_buf_desc[0], 0, 0);
  nand_set_buff_desc((buf_desc + 1), &saved_buf_desc[1], 0, 0);
  
  return result;
}


/*
 * Erases a block.
 */
static int nand_erase_block(flash_client_ctxt *client_ctxt, uint32 block,
  uint32 num_blocks)
{
  int    result = NAND_DEVICE_DONE;
  uint32 phys_page = 0;
  uint32 hal_id;
  struct flash_hal_predef_block_data blocks_data;
  struct flash_hal_predef_op_list *op_list;
  enum flash_hal_status hal_status = FLASH_HAL_FAIL;

  hal_id = client_ctxt->client_data.hal_id;

  FLASHLOG(5, ("Client: %d, Block : 0x%x\n", hal_id,
    NAND_LB_TO_PB(client_ctxt, block)));

  /* Get the first physical page in the given logical block */
  phys_page = NAND_SLP_TO_SPP(client_ctxt, block);

  /* Pass physical address for DM or virtual address in non-dm */
  blocks_data.pages_per_block = client_ctxt->client_data.pages_per_block;
  blocks_data.start_addr = phys_page;
  blocks_data.num_blocks = num_blocks;

  flash_hal_erase_block(hal_id, &blocks_data, &op_list, &hal_status);

  if (FLASH_HAL_SUCCESS != hal_status)
  {
    result = NAND_DEVICE_FAIL;
    FLASHLOG(3, ("Erasing Block 0x%x: FAILED\n", NAND_LB_TO_PB(client_ctxt, block)));
  }

  return result;
}

/*
 * Read NAND device ID and manufacture ID
 */
int nand_read_id(uint32 hal_id, struct flash_hal_buffer_desc *buff_desc)
{
  int    result = NAND_DEVICE_DONE;
  struct flash_hal_predef_op_list *op_list;
  enum   flash_hal_status hal_status = FLASH_HAL_FAIL;

  flash_hal_read_id(hal_id, buff_desc, &op_list, &hal_status);

  if ((FLASH_HAL_SUCCESS != hal_status) &&
     (FLASH_HAL_FAIL_MPU_ERR != hal_status))
  {
    FLASHLOG(3, ("\nNAND device probe failure\n"));
    result = NAND_DEVICE_FAIL;
  }

  return result;
}

/*
 * Erase NAND blocks
 */
int nand_erase_blocks(flash_client_ctxt *client_ctxt,
  struct nand_block_vector *block_vector, uint32 iovec_count)
{
  uint32 block = 0;
  uint32 erase_sync_state = 1;
  uint32 tmp_block_count = 0;
  int    result = NAND_DEVICE_DONE;

  (void)nand_erase_block;

  /* For each element in the IOVECTOR */
  while (iovec_count--)
  {
    tmp_block_count = 0;

    block = block_vector->start_block;

    STOR_PROFILE_START;

    /* Set the block fail and result */
    block_vector->end_result = NAND_DEVICE_DONE;
    block_vector->last_failed_block = -1;

    /* For the range of blocks specified in the structure */
    while (tmp_block_count < block_vector->block_count)
    {
      /* IMPORTANT NOTE : This code assumes that we are already
         in the critical section lock. The unlock/lock will be done
         when demand paging enabled
         (when nand_entry_init_data.multi_rw_support_count = 1).

         The SYNC enter/release in this code done after every block
         erase. Currently the flash HAL doesn't support erase of
         more than one block. So this code erased one block at a
         time irrespective of FLASH_MULTI_RW_SUPPORT_COUNT.

         The code releases the lock after every page operation except
         for the last block. And re-enters for the next block.
         flash_nand_entry will be releasing the lock for the last block.
       */
      if (!erase_sync_state)
      {
        flash_sync_enter(client_ctxt->flash_dev_ctxt->handle_dev_sync);
        erase_sync_state = 1;
      }

      /* Erase the logical block */
      result = nand_erase_block(client_ctxt, block, 1);

      /* Set the overall result as failure if one erase fails */
      if (NAND_DEVICE_DONE != result)
      {
        block_vector->end_result = result; 
        block_vector->last_failed_block = block;
      }

      tmp_block_count++;

      if ((tmp_block_count < block_vector->block_count) &&
          (NAND_DEVICE_DONE == result))
      {
        flash_sync_leave(client_ctxt->flash_dev_ctxt->handle_dev_sync);
        erase_sync_state = 0;
      }

      block++;
    }

    STOR_PROFILE_END(NAND_PROFILE_ERASE_BIT_MASK, "NAND_ERASE", block_vector->start_block, block_vector->block_count);

    block_vector++;
  }

  return result;
}

/*
 * Sets the state of NAND block
 */
int nand_set_block_state(flash_client_ctxt *client_ctxt,
  uint32 block, enum nand_block_state block_state)
{
  int    result = NAND_DEVICE_DONE;
  uint32 page, write_fails = 0, index = 0;
  struct nand_dev_pdata  *nand_pdata = GET_PDATA(client_ctxt);
  struct flash_nand_params      *config_data = NULL;
  struct flash_bad_block_layout *bb_info;

  switch (block_state)
  {
    case NAND_BLOCK_OK:
      {
        result = nand_erase_block(client_ctxt, block, 1);
      }
      break;
    case NAND_BLOCK_BAD:
      {
        uintnt spare_buffer;
        struct flash_hal_buffer_desc buf_desc[2];
        struct flash_hal_predef_page_data page_data;

        page = (block << client_ctxt->client_data.block_size_shift);

        /* Convert the Logical page to physical page */
        page = NAND_LP_TO_PP(client_ctxt, page);
        
        FLASHLOG(3, ("    Physical page - 0x%x\n", page));

        config_data = nand_pdata->config_data;
        bb_info = NAND_BB_INFO(config_data);

        //DALSYS_memset(nand_pdata->raw_page_buffer ,0x0,
        //  client_ctxt->client_data.total_page_size_bytes);
        flash_memset(nand_pdata->raw_page_buffer ,0x0,
          client_ctxt->client_data.total_page_size_bytes);

        flash_hal_set_ecc_state (client_ctxt->client_data.hal_id,
          FLASH_HAL_HW_ECC_DISABLE);

        spare_buffer = (uintnt) nand_pdata->raw_page_buffer;

        buf_desc[0].buff_paddr = flash_vtop_get_physical(spare_buffer);
        buf_desc[0].buff_vaddr = spare_buffer;
        buf_desc[0].buff_size = client_ctxt->client_data.total_page_size_bytes;
        buf_desc[0].num_pages = 1;

        buf_desc[1].buff_paddr = 0;
        buf_desc[1].buff_vaddr = 0;
        buf_desc[1].buff_size = 0;
        buf_desc[1].num_pages = 1;

        page_data.total_pages = 1;
        page_data.main_size_bytes =
          client_ctxt->client_data.total_page_size_bytes;
        page_data.spare_size_bytes = 0;
        page_data.buff_desc_count = 2;
        page_data.buff_desc = &buf_desc[0];

        if (DO_CACHE_MAINTENANCE)
        {
          flash_dcache_clean(spare_buffer,
            client_ctxt->client_data.total_page_size_bytes);
        }

        /* Write to all pages within block */
        while ((index++ < FLASH_MAX_BB_ENTRIES) && (bb_info->byte_length))
        {
          page_data.start_page = page + bb_info->page;

          if (NAND_DEVICE_DONE != nand_write_mpages(client_ctxt, &page_data))
          {
            //result = NAND_DEVICE_FAIL;
            //break;
            write_fails++;
          }
          else
          {
            FLASHLOG (5, ("Writing Bad block:0x%x - PASSED\n", page));
          }

          ++bb_info;
        }

        if (write_fails < FLASH_MAX_BB_ENTRIES)
        {
          result = NAND_DEVICE_DONE;
        }
        else
        {
          result = NAND_DEVICE_FAIL;
        }
      }
      break;
    default:
      result = NAND_DEVICE_FAIL;
      break;
  }

  return result;
}

/*
 * Gets the NAND block status
 */
static int nand_get_block_status(flash_client_ctxt *client_ctxt, uint32  block,
   enum nand_block_state *block_state)
{
  int    result = NAND_DEVICE_DONE;
  uint32 spare_mask, bb_col_offset, hal_id;
  uintnt bb_buffer, phys_page, index = 0;
  struct flash_hal_predef_op_list *op_list;
  enum flash_hal_status hal_status = FLASH_HAL_FAIL;
  struct nand_dev_pdata *nand_pdata = GET_PDATA(client_ctxt);
  struct flash_bad_block_layout *bb_info;
  struct flash_hal_predef_spare_data spare_data;

  bb_info = NAND_BB_INFO(nand_pdata->config_data);
  hal_id = client_ctxt->client_data.hal_id;
  bb_buffer = (uintnt) nand_pdata->raw_page_buffer;

  spare_mask = (nand_pdata->config_data->dev_width == FLASH_HAL_8_BIT_WIDTH)?
    0xFF : 0xFFFF;

  bb_col_offset = NAND_SET_COL_ADDR(nand_pdata->config_data->dev_width,
    bb_info->byte_offset);

  /* Get the physical block number */
  block = NAND_LB_TO_PB(client_ctxt, block);

  FLASHLOG(5, ("nand_get_block_status  Client: %x, block: 0x%x  \n", hal_id,
    block));

  /* Disable ECC */
  flash_hal_set_ecc_state(hal_id, FLASH_HAL_HW_ECC_DISABLE);

  *block_state = NAND_BLOCK_OK;

  spare_data.col_offset = bb_col_offset;
  spare_data.spare_size_bytes = bb_info->byte_length;
  spare_data.buff_desc.buff_paddr = flash_vtop_get_physical(bb_buffer);
  spare_data.buff_desc.buff_vaddr = bb_buffer;
  spare_data.buff_desc.buff_size = bb_info->byte_length;

  while ((index++ < FLASH_MAX_BB_ENTRIES) && (bb_info->byte_length))
  {
    *(uintnt *)bb_buffer = 0x0;

    if (DO_CACHE_MAINTENANCE)
    {
      flash_dcache_inval(bb_buffer, bb_info->byte_length);
    }

    FLASHLOG(5, ("Page :%x, offset:%x\n",bb_info->page, bb_col_offset));

    phys_page = (block * nand_pdata->config_data->pages_per_block) +
      bb_info->page;

    spare_data.page = phys_page;

    STOR_PROFILE_START;
  
    flash_hal_read_bb_marker(hal_id, &spare_data, &op_list, &hal_status);

	STOR_PROFILE_END(NAND_PROFILE_BB_BIT_MASK, "NAND_BB", block, 1);

    if (FLASH_HAL_SUCCESS != hal_status)
    {
      result = NAND_DEVICE_FAIL;
      FLASHLOG(3, ("Reading BB Marker : FAILED\n"));
    }

    FLASHLOG(5, ("Bad Block Byte: %x, mask:%x\n", *(uint32 *)bb_buffer,
      spare_mask));

    if ((((*(uintnt *)bb_buffer) & spare_mask) != spare_mask) ||
      (NAND_DEVICE_DONE != result))
    {
      *block_state = NAND_BLOCK_BAD;
      break;
    }

    ++bb_info;
  }

  return result;
}

int nand_get_block_state(flash_client_ctxt *client_ctxt, uint32 block,
   enum nand_block_state *block_state)
{
  int    result = NAND_DEVICE_DONE;

  result = nand_get_block_status(client_ctxt, block, block_state);

  return result;
}

/*
 * Writes page_count pages in NAND device
 */
int nand_write_pages(flash_client_ctxt *client_ctxt,
  enum page_access_opcode write_type, struct nand_mem_desc_buf *buffer_desc,
  struct nand_page_iovec *page_data_iovec)
{
  int    result = NAND_DEVICE_DONE;
  uint32 phys_page = 0;
  uint32 main_size_bytes = 0, spare_size_bytes = 0;
  struct nand_mem_desc_buf *buf_desc;
  struct flash_hal_predef_page_data page_data;

  /* Set the ECC state according to write type */
  if (NAND_ACCESS_RAW != write_type)
  {
    flash_hal_set_ecc_state(client_ctxt->client_data.hal_id,
      (enum flash_hal_ecc_state)client_ctxt->client_data.ecc_state);
  }
  else
  {
    flash_hal_set_ecc_state(client_ctxt->client_data.hal_id,
      FLASH_HAL_HW_ECC_DISABLE);
  }

  /* Set the spare data details to null by default */
  buf_desc = &buffer_desc[0];

  switch (write_type)
  {
    case NAND_ACCESS_MAIN:
    case NAND_ACCESS_RAW:
      spare_size_bytes = 0;
      main_size_bytes = page_data_iovec->main_size_bytes;
      break;
    case NAND_ACCESS_MAIN_SPARE:
      main_size_bytes = page_data_iovec->main_size_bytes;
      spare_size_bytes = page_data_iovec->spare_size_bytes;
      break;
    case NAND_ACCESS_SPARE:
      main_size_bytes = 0;
      spare_size_bytes = page_data_iovec->spare_size_bytes;
      break;
    default:
      main_size_bytes = 0;
      spare_size_bytes = 0;
  }

  phys_page = NAND_LP_TO_PP(client_ctxt, page_data_iovec->start_page);

  page_data.start_page = phys_page;
  page_data.total_pages = page_data_iovec->total_page_count;
  page_data.main_size_bytes = main_size_bytes;
  page_data.spare_size_bytes = spare_size_bytes;
  page_data.buff_desc_count = 2;
  page_data.buff_desc = (struct flash_hal_buffer_desc *) buf_desc;

  STOR_PROFILE_START;

  result = nand_write_mpages(client_ctxt, &page_data);

  STOR_PROFILE_END(NAND_PROFILE_WRITE_BIT_MASK, "NAND_WRITE", page_data_iovec->start_page, page_data_iovec->total_page_count);
  
  return result;
}


/*
 * Reads page_count pages in NAND device
 */
int nand_read_pages(flash_client_ctxt *client_ctxt,
  enum page_access_opcode read_type, struct nand_mem_desc_buf *buffer_desc,
  struct nand_page_iovec *page_data_iovec)
{
  int    result = NAND_DEVICE_DONE;
  uint32 phys_page = 0;
  uint32 main_size_bytes = 0, spare_size_bytes = 0;
  struct nand_mem_desc_buf *buf_desc;
  struct flash_hal_predef_page_data page_data;

  if (NAND_ACCESS_RAW != read_type)
  {
    flash_hal_set_ecc_state(client_ctxt->client_data.hal_id,
      (enum flash_hal_ecc_state)client_ctxt->client_data.ecc_state);
  }
  else
  {
    flash_hal_set_ecc_state(client_ctxt->client_data.hal_id,
      FLASH_HAL_HW_ECC_DISABLE);
  }

  /* Get the buffer descriptor ptr */
  buf_desc = &buffer_desc[0];

  switch (read_type)
  {
    case NAND_ACCESS_MAIN:
    case NAND_ACCESS_RAW:
      spare_size_bytes = 0;
      main_size_bytes = page_data_iovec->main_size_bytes;
      break;
    case NAND_ACCESS_MAIN_SPARE:
      main_size_bytes = page_data_iovec->main_size_bytes;
      spare_size_bytes = page_data_iovec->spare_size_bytes;
      break;
    case NAND_ACCESS_SPARE:
      main_size_bytes = 0;
      spare_size_bytes = page_data_iovec->spare_size_bytes;
      break;
    default:
      main_size_bytes = 0;
      spare_size_bytes = 0;
  }

  phys_page = NAND_LP_TO_PP(client_ctxt, page_data_iovec->start_page);

  page_data.start_page = phys_page;
  page_data.total_pages = page_data_iovec->total_page_count;
  page_data.main_size_bytes = main_size_bytes;
  page_data.spare_size_bytes = spare_size_bytes;
  page_data.buff_desc_count = 2;
  page_data.buff_desc = (struct flash_hal_buffer_desc *) buf_desc;

  
  STOR_PROFILE_START;
  
  result = nand_read_mpages(client_ctxt, &page_data);

  STOR_PROFILE_END(NAND_PROFILE_READ_BIT_MASK, "NAND_READ", page_data_iovec->start_page, page_data_iovec->total_page_count);
  
  return result;
}
