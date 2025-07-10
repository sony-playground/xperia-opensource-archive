 /*****************************************************************************
 * NandLibNull.c
 *
 * Copyright (c) 2020 Qualcomm Technologies Incorporated.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 *****************************************************************************/
/*=============================================================================
                        Edit History


  when       who     what, where, why
----------   ---     ----------------------------------------------------------- 
05/29/2020   sa      Updated new API.
03/30/2020   ck      Initial version

=============================================================================*/
#include "nand_api.h"


NAND_STATUS nand_open (uint32 dev_id,
                       const uint8 * partition_name,
                       nand_handle_t *handle)
{
  /* Validate pointers */
  if (handle == NULL)
  {
    return NAND_DEVICE_INVALID_PARAMETER;
  }


  /* Memory for handle would be malloc'ed here and assigned to handle double pointer.
     Instead just hard wire for simulation. */
  *handle = (void *)0xA5A5A5A5;


  return NAND_DEVICE_DONE;
}


NAND_STATUS nand_close (nand_handle_t handle,
                        uint32 close_all)
{
  /* Validate pointers */
  if (handle == NULL)
  {
    return NAND_DEVICE_INVALID_PARAMETER;
  }


  /* Handle memory would be free here. */


  return NAND_DEVICE_DONE;
}


NAND_STATUS nand_get_info (nand_handle_t handle,
                           struct nand_info * nand_info)
{
  /* Verify pointers */
  if ((handle == NULL) ||
      (nand_info == NULL))
  {
    return NAND_DEVICE_INVALID_PARAMETER;
  }


  /* Assign page size in bytes to non 0 value */
  nand_info->page_size_bytes = 4096;


  return NAND_DEVICE_DONE;
}


NAND_STATUS nand_block_set_state (nand_handle_t handle,
                                  uint32 block,
                                  enum nand_block_state block_state)
{
  /* Validate pointers */
  if (handle == NULL)
  {
    return NAND_DEVICE_INVALID_PARAMETER;
  }


  return NAND_DEVICE_DONE;
}


NAND_STATUS nand_block_get_state (nand_handle_t handle,
                                  uint32 block,
                                  enum nand_block_state * block_state)
{
  /* Validate pointers */
  if ((handle == NULL) ||
      (block_state == NULL))
  {
    return NAND_DEVICE_INVALID_PARAMETER;
  }


  return NAND_DEVICE_DONE;
}


NAND_STATUS nand_erase (nand_handle_t handle,
                        uint32 start_block,
                        uint32 block_count)
{
  /* Validate pointers */
  if (handle == NULL)
  {
    return NAND_DEVICE_INVALID_PARAMETER;
  }


  return NAND_DEVICE_DONE;
}


NAND_STATUS nand_write (nand_handle_t handle,
                        enum page_access_opcode opcode,
                        uint32 start_page,
                        uint32 page_count,
                        void * buffer,
                        uint32 buffer_size)
{
  /* Validate pointers */
  if ((handle == NULL) ||
      (buffer == NULL))
  {
    return NAND_DEVICE_INVALID_PARAMETER;
  }


  return NAND_DEVICE_DONE;
}


NAND_STATUS nand_read (nand_handle_t handle,
                       enum page_access_opcode opcode,
                       uint32 start_page,
                       uint32 page_count, 
                       void * buffer,
                       uint32 buffer_size)
{
  /* Validate pointers */
  if ((handle == NULL) ||
      (buffer == NULL))
  {
    return NAND_DEVICE_INVALID_PARAMETER;
  }


  return NAND_DEVICE_DONE;
}


NAND_STATUS nand_reinit (void)
{
  return NAND_DEVICE_DONE;
}


NAND_STATUS nand_update_partition_tbl_smem(void)
{
  return NAND_DEVICE_DONE;
}