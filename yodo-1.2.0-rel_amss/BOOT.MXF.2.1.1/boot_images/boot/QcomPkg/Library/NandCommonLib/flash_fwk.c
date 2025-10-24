/*=============================================================================
 *
 * FILE:      flash_dal_fwk.c
 *
 * DESCRIPTION: Function definitions specific to Flash DAL framework
 *
 * PUBLIC CLASSES:  Not Applicable
 *
 * INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A
 *
 * Copyright (c) 2008-2010,2012-2013,2016, 2019-2021 QUALCOMM Technologies Incorporated.
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
 *  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/NandCommonLib/flash_fwk.c#1 $ $DateTime: 2022/08/18 10:15:46 $ $Author: pwbldsvc $
 *
 *
 * when         who     what, where, why
 * ----------   ---     ----------------------------------------------
 * 10/06/21     sa      Add the client to linklist only if nand_open succeeds.
 * 04/08/21     sa      Free the flash_dev_ctxt only if nand is not initialised.
 * 12/07/20     sa      Update NAND info on SMEM.
 * 07/08/20     sa      Added new API 'nand_update_partition_tbl_smem'.
 * 06/04/20     sa      Removed unused variables.
 * 09/20/19     sa      Added logic to support mibib update.
 * 09/13/19     sa      Changed FLASH_NUM_PART_ENTRIES to FLASH_PART_ENTRY_TOTAL.
 * 07/11/16     eo      Update custom EEPROM support
 * 01/29/13     sv      Fix KW error - Memory leak issue
 * 09/05/12     bb/sv   Call entry layer APIs directly
 * 03/19/12     sv      Add SPI NOR power management support
 * 03/19/12     eo      Support for erase blocks by size
 * 09/15/10     bb      Added support for multiple device IDs
 * 05/11/10     eo      Added NOR API support
 * 12/28/09     sc      Added 2x support in DAL
 * 02/23/09     bb      Read/Write API changes with iovec design changes
 * 11/24/08     mm      Support for UUID
 * 08/28/08     dp      Initial Revision
 *==================================================================*/

/*===================================================================
 *
 *                     Include Files
 *
 ====================================================================*/

#include "flash_fwk.h"
#include "flash_osal.h"
#include "flash_nand_entry.h"
#include "flash_nand.h"
#include "smem.h"

/***********************************************************************
 *   Data structures
 ***********************************************************************/	
flash_driver_ctxt_t flash_internal_clients;

/* NAND info to share via SMEM */
static struct nand_dev_info *smem_flash_dev_info;

/*------------------------------------------------------------------------------
 *   Following functions are defined in base IQI CS Interface.
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
  Following functions are extended in flash_handle Interface available to flash
  clients

  open_partition      =  flash_fwk_open_partition,
  get_info            =  flash_fwk_get_info,
  get_status          =  flash_fwk_get_status,
  erase_blocks        =  flash_fwk_erase_blocks,
  erase_suspend       =  flash_fwk_erase_suspend,
  erase_resume        =  flash_fwk_erase_resume,
  block_set_state     =  flash_fwk_block_set_state,
  block_get_state     =  flash_fwk_block_get_state,
  write_pages         =  flash_fwk_write_pages,
  write_partial_page  =  flash_fwk_write_partial_page,
  read_pages          =  flash_fwk_read_pages,
  read_otp_page       =  flash_fwk_read_otp_page,
  copy_pages          =  flash_fwk_copy_pages
  get_uuid            = flash_fwk_get_uuid,
  erase_blocks_by_size = flash_fwk_erase_blocks_by_size,
  set_power_mode      =  flash_fwk_set_power_mode
------------------------------------------------------------------------------*/
	
/* This function invokes the flash_dal_get_info which in turn calls
 * the get_info API of the flash driver
 */
NAND_STATUS nand_get_info(nand_handle_t handle, struct nand_info *nand_info)
{
  int status = NAND_DEVICE_NOT_FOUND;
  flash_client_ctxt *client_ctxt = ((flash_client_ctxt *)handle);

  if (client_ctxt->IsValid == TRUE)
  {
  status = nand_entry_get_info(client_ctxt, nand_info);
  }

  return status;
}

/* This function invokes the flash_dal_erase_blocks which in turn
 * invokes the client context erase block API.
 */
NAND_STATUS nand_erase(nand_handle_t handle, uint32 start_block, uint32 block_count)
{
  int status = NAND_DEVICE_NOT_FOUND;
  flash_client_ctxt *client_ctxt = ((flash_client_ctxt *)handle);

  if (client_ctxt->IsValid == TRUE)
  {
    status = nand_entry_erase_blocks(client_ctxt, start_block, block_count);
  }

  return status;
}

/* This function invokes the flash_dal_flash_dal_block_set_state which
 *  inturn invokes the client context flash_dal_block_set_state API.
 */
NAND_STATUS nand_block_set_state(nand_handle_t handle, uint32 block,
  enum nand_block_state block_state)
{
  int status = NAND_DEVICE_NOT_FOUND;
  flash_client_ctxt *client_ctxt = ((flash_client_ctxt *)handle);

  if (client_ctxt->IsValid == TRUE)
  {
    status = nand_entry_block_set_state(client_ctxt, block, block_state);
  }

  return status;
}

/* This function invokes the flash_dal_flash_dal_block_get_state which
 * inturn invokes the client context flash_dal_block_get_state API.
 */
NAND_STATUS nand_block_get_state(nand_handle_t handle, uint32 block, 
  enum nand_block_state *block_state)
{
  int status = NAND_DEVICE_NOT_FOUND;
  flash_client_ctxt *client_ctxt = ((flash_client_ctxt *)handle);

  if (client_ctxt->IsValid == TRUE)
  {
    status = nand_entry_block_get_state(client_ctxt, block, block_state);
  }

  return status;
}

/* This function invokes the flash_dal_write_pages which in
 * turn invokes the client context write_pages API.
 */
NAND_STATUS nand_write(nand_handle_t handle,
  enum page_access_opcode opcode, uint32 start_page, uint32 page_count, void *buffer, uint32 buffer_size)
{
  int status = NAND_DEVICE_NOT_FOUND;
  flash_client_ctxt *client_ctxt = ((flash_client_ctxt *)handle);

  if (client_ctxt->IsValid == TRUE)
  {
    status = nand_entry_write_pages(client_ctxt, opcode, start_page, page_count, buffer, buffer_size);
  }

  return status;
}

/* This function invokes the flash_dal_read_pages which in turn invokes
 * the client context read_pages API.
 */
NAND_STATUS nand_read(nand_handle_t handle,
  enum page_access_opcode opcode, uint32 start_page, uint32 page_count, void *buffer, uint32 buffer_size)
{
  int status = NAND_DEVICE_NOT_FOUND;
  flash_client_ctxt *client_ctxt = ((flash_client_ctxt *)handle);

  if (client_ctxt->IsValid == TRUE)
  {
    status = nand_entry_read_pages(client_ctxt, opcode, start_page, page_count, buffer, buffer_size);
  }

  return status;
}

/* This function is used to add new elements to the linklist for 
 * each partition.  
 */
static flash_client_ctxt * nand_add_client_element()
{
  flash_client_ctxt *client_ctxt = NULL; 
  /* This will store the last allocated element */
  int err;

  /* Allocate memory for the element. */
  if ((err = flash_malloc(sizeof(flash_client_ctxt), 
		  (void **)&client_ctxt)) != NAND_DEVICE_DONE)
  {
    return NULL;
  }
  
  /* memset the client_ctxt */
  flash_memset(client_ctxt, 0x0, sizeof(flash_client_ctxt));

  if (flash_internal_clients.flash_handle == NULL)
  {
    /* Alocates memory for flash dev context */
    if ((err = flash_malloc(sizeof(flash_dev_ctxt), 
       (void **)&client_ctxt->flash_dev_ctxt)) == NAND_DEVICE_DONE)
    {
      flash_memset(client_ctxt->flash_dev_ctxt, 0x0, sizeof(flash_dev_ctxt));
    }
    else
    {
      flash_free(client_ctxt);
      client_ctxt = NULL;
    }

	/* Store the flash_dev_ctxt for future use */
	flash_internal_clients.flash_handle = client_ctxt;
  }
  else
  { 
    /* Intialize the flash device handle. All the clients point to same dev handle */
    client_ctxt->flash_dev_ctxt = 
    flash_internal_clients.flash_handle->flash_dev_ctxt;
  }
  
  return client_ctxt;  
}

/* This function is used to search for a partition handle in flash_internal_clients struct.
 * If the client is found , handle to the partition is returned. 
 */
static flash_client_ctxt * nand_find_client_element(const uint8 *partition_name)
{
  flash_client_ctxt *ptr = flash_internal_clients.flash_handle;
    	
  while (ptr != NULL)
  { 
    if (strcmp(&ptr->client_data.partition_name[0], (const char *)partition_name ) == 0)
    {
      break;
    }
    ptr = ptr->node;
  }

  return ptr;
}

/* This is a wrapper function to call 'nand_entry_open_partition' and 
 * set respective status variables.
 */
NAND_STATUS nand_open_partition_wrapper(flash_client_ctxt *client_ctxt, 
  const uint8 *partition_name)
{ 
  NAND_STATUS status = NAND_DEVICE_FAIL;
  static flash_client_ctxt *last_elem =	NULL;

  status = nand_entry_open_partition(client_ctxt,
                 (const unsigned char *)partition_name);
  
  if (NAND_DEVICE_DONE == status)
  {
    /* Increment client references */
    client_ctxt->refs += 1;
    flash_internal_clients.clnt_cnt += 1;
    client_ctxt->IsValid = TRUE;

    /* Store the 1st element.
       This will be the 1st element in flash_internal_clients */
    if(last_elem == NULL)
    {
      last_elem = client_ctxt;
    }
    else
    {
      /* Since this is not the 1st element, add elements to the end of linklist */
      last_elem->node = client_ctxt;
      last_elem = last_elem->node;
    }
				  
  }
  else	
  {
    /* If the 1st or only client is invalid, free the device context too */
	if (flash_internal_clients.nand_initialized == FALSE)
    {    
      flash_free(client_ctxt->flash_dev_ctxt);
	  flash_internal_clients.flash_handle = NULL;
    }
    flash_free(client_ctxt);
    status = NAND_DEVICE_FAIL;
  }
  return status;	
}

NAND_STATUS nand_open(uint32 dev_id, const uint8 *partition_name, 
  nand_handle_t *handle)
{
  int status = NAND_DEVICE_FAIL;
  flash_client_ctxt *client_ctxt =	NULL;

  if (NULL == handle)
  {
    return status;
  }

  if (FALSE == flash_internal_clients.nand_initialized)
  {	
    /* Allocate the element */
    if ((client_ctxt = nand_add_client_element()) == NULL)
      return status;

    /*-------------------------------------------------------------------------
      Initialize Synchronization Object for this device.
      This is used to synchronize between client calls and interrupt context
      on our variables and HAL.
      --------------------------------------------------------------------------
     */
    if(NAND_DEVICE_DONE != flash_sync_create((void *)client_ctxt->flash_dev_ctxt))
    {
      return status;
    }
	
    status = nand_entry_device_probe(client_ctxt);

    if (NAND_DEVICE_DONE == status)
    {
      status = nand_open_partition_wrapper(client_ctxt, partition_name);
    }

    if (NAND_DEVICE_DONE == status)
    {
      flash_internal_clients.nand_initialized = TRUE;
    }
  }
  else /* flash_internal_clients.nand_initialized != FALSE */
  {
    /* If nand_initalized != FALSE, the list is initialized. 
       Search for element in the list, If not found, malloc a new element 
     */
    client_ctxt = nand_find_client_element(partition_name);

    /* Return the handle if the partition is found */
    if ( client_ctxt != NULL )
    {
      status = NAND_DEVICE_DONE;
      client_ctxt->refs += 1;
      flash_internal_clients.clnt_cnt += 1;
    }
    else 
    {
      /* If client_ctxt is NULL , open the partition and add it to the linklist */
      if ((client_ctxt = nand_add_client_element()) != NULL )
      {
        status = nand_open_partition_wrapper(client_ctxt, partition_name);
      }
    }
  }
  
  *handle = (NAND_DEVICE_DONE == status)?((nand_handle_t *)client_ctxt) : NULL;
  
  return status;
}

NAND_STATUS nand_close(nand_handle_t handle, uint32 close_all)
{
  int status = NAND_DEVICE_DONE;
  flash_client_ctxt *client_ctxt = ((flash_client_ctxt *)handle);

  FLASHLOG(4, ("Flash close Called\n"));

  	
  if (client_ctxt->IsValid != TRUE)
  {
    return NAND_DEVICE_NOT_FOUND;
  }

  /* if close_all == 1, means we need to close all references to a partition */
  do
  {
    if (client_ctxt->refs > 0)
    {
      client_ctxt->refs -= 1;
      flash_internal_clients.clnt_cnt -= 1;
    }
  }
  while ( (client_ctxt->refs > 0) && close_all );

  if (!client_ctxt->refs)
  {
    client_ctxt->IsValid = FALSE;
    status = nand_entry_close(client_ctxt);
  }
  
  if (flash_internal_clients.clnt_cnt == 0)
  {
    flash_internal_clients.nand_initialized = 0;
    status = nand_entry_deinit (client_ctxt);
    memset(&flash_internal_clients ,0 , sizeof(flash_driver_ctxt_t));
  }
  
  return status;
}

/* This function is called during BLOCKIORefresh event. When 
 * BLOCKIORefresh event occurs, we set the flag. If 'mibib_from_nand'
 * is set, new mibib table will be read from NAND.
 */
NAND_STATUS nand_reinit()
{
    
  flash_client_ctxt *client_ctxt = 
  flash_internal_clients.flash_handle;
  
  /* Before we get the new MIBIB and save it in smem, we
    need to deinit the nand driver. Handles will be reinit later. 
   */
  if (flash_internal_clients.nand_initialized == TRUE)
  {
    while (client_ctxt != NULL)
    {
      nand_close(client_ctxt, 1);
      client_ctxt = client_ctxt->node;
    }
  }

  flash_internal_clients.mibib_from_nand = TRUE;

  return NAND_DEVICE_DONE;
}

NAND_STATUS nand_update_partition_tbl_smem(void)
{
  if(nand_partition_table.parti_table == NULL)
  {
    FLASHLOG(5,("Can't copy table to SMEM. Table not present in NAND.\n"));
	return NAND_DEVICE_FAIL;	
  }

  /* Copy NAND info on SMEM to be used by TZ */
  smem_flash_dev_info =  (struct nand_dev_info*) 
      smem_alloc(SMEM_FLASH_DEVICE_INFO ,sizeof(nand_dev_info));
  if (NULL == smem_flash_dev_info)
  {
    return NAND_DEVICE_FAIL;
  }
  flash_memscpy((uint32 *)smem_flash_dev_info,sizeof(nand_dev_info), 
      (void *) &nand_dev_info, sizeof(nand_dev_info));

  /* Finally, copy the partition table on SMEM */
  return smem_update_mibib_internal(nand_partition_table.parti_table_size_bytes);
  
}

int flash_fwk_attach(const char *pszArg, DALDEVICEID dev_id, 
  DalDeviceHandle **handle_dal_device)
{
  int status = NAND_DEVICE_DONE;
	
  FLASHLOG(4, ("Flash fwk attach\n"));
  return status;
}

