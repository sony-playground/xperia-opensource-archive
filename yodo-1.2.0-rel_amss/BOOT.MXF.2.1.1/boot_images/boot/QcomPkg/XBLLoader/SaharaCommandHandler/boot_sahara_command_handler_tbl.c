/*===========================================================================

                  BOOT SAHARA COMMAND HANDLER TABLE DEFINITIONS

DESCRIPTION
  Contains wrapper definition for populating sahara command handler table

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright 2020-2022 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when        who      what, where, why
--------    ---      ----------------------------------------------------------
06/16/21    ds       clear dload cookie
03/02/21    ck       Enhanced boot_force_reset
10/14/20    rhy      Enable boot_force_reset with hard and warm reset
10/09/20    rhy      Added boot_force_reset. Feature not supported.
07/02/20    rhy     Initial revision.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_config_context.h"
#include "boot_error_if.h"
#include "boot_sahara_command_handler_if.h"
#include "MIbib.h"
#include "HALhwio.h"
#include "ChipInfoHWIO.h"
#include "boot_ddr_if.h"
#include "boot_edk2_cache_if.h"
#include <boot_logger_if.h>
#include "limits.h"
#include "boot_reset_if.h"
#include "HALbootHWIO.h"
#include <boot_crashdump.h>
#include "boot_mbn_loader.h"

extern boolean xbl_pcie_reset_sep_enabled (void);

/* ==========================================================================

**  Function :  boot_read_serial_number

** ==========================================================================
*/
/*!
*
* @brief
*   Return Serial number
*
* @param[in] config context and pointer to media_interface_if
*
*/
static bl_error_boot_type boot_read_serial_number(uint32* serial_num)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  do
  {
    if (serial_num == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_SAHARA_CMD_HANDLER, BL_ERR_NULL_PTR_PASSED);
      break;
    }
    
    *serial_num = HWIO_IN(CHIP_UNIQUE_ID_0);

  } while (FALSE);

  return return_status;
}




/* ==========================================================================

**  Function :  boot_get_ddr_training

** ==========================================================================
*/
/*!
*
* @brief
*   Return training data from DDR.
*/
static bl_error_boot_type boot_get_ddr_training
(
  uint32* tr_data_size,
  uint8**  ddr_training_data_ptr
)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_edk2_cache_if_type *edk2_cache_if = NULL;
  boot_ddr_if_type *ddr_if =  NULL;
  boot_mbn_if_type *mbn_if =  NULL;
  uint32 mbn_header_size =    0;
  image_type image_id =   TRDATA_IMG;

  do
  {
    if (tr_data_size == NULL || ddr_training_data_ptr == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_SAHARA_CMD_HANDLER, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    /* Initialize the size to 0 */
    *tr_data_size = 0;

    /* Get interface for EDK2 cache */
    return_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_EDK2_CACHE_INTERFACE, (void **)&edk2_cache_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }
    if (edk2_cache_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_SAHARA_CMD_HANDLER, BL_ERR_INTERFACE_FAILURE);
      break;
    }

    /* Get interface for DDR */
    return_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_DDR_INTERFACE, (void **)&ddr_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }
    if (ddr_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_SAHARA_CMD_HANDLER, BL_ERR_INTERFACE_FAILURE);
      break;
    }

    /* Get interface for MBN loader */
    return_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_MBN_LOADER_INTERFACE, (void **)&mbn_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }
    if (mbn_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_SAHARA_CMD_HANDLER, BL_ERR_INTERFACE_FAILURE);
      break;
    }

    /* Call DDR training data */
    *ddr_training_data_ptr = (uint8*)ddr_if->params_get_training_data(tr_data_size);

    if (*ddr_training_data_ptr == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_SAHARA_CMD_HANDLER, BL_ERROR_GET_DDR_TRAINING_DATA_FAIL);
      break;
    }

    /* Flush and invalidate */
    edk2_cache_if->WriteBackInvalidateDataCacheRange((void *)(*ddr_training_data_ptr), (*tr_data_size));

    if ((*tr_data_size) == 0 || *ddr_training_data_ptr == NULL)
    {
      *tr_data_size = 0;
      *ddr_training_data_ptr = NULL;
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_SAHARA_CMD_HANDLER, BL_ERROR_GET_DDR_TRAINING_DATA_FAIL);
      boot_log_message("Received training data of size 0");
      break;
    }

    /* Prepare the MBN header packet */
    return_status = mbn_if->boot_mbn_header_size(&mbn_header_size);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    /* Check for 32bit address for MBN */
    if (!TRUNC_CHECK_64BIT_TO_32BIT(*ddr_training_data_ptr))
    {
      boot_log_message("Received training data points to address greater than 32 bit arch");
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_SAHARA_CMD_HANDLER, BL_ERR_INTERFACE_FAILURE);
      break;
    }
    return_status = mbn_if->boot_mbn_header_init((uint32)((uint64)*ddr_training_data_ptr), *tr_data_size, image_id, mbn_header_size);

  } while (FALSE);

  return return_status;
}

/* ==========================================================================

**  Function :  boot_force_reset

** ==========================================================================
*/
/*!
*
* @brief
*   Currently feature not supported.
*/
static bl_error_boot_type boot_force_reset(void)
{
  boot_reset_if_type *reset_if = NULL;
  bl_error_boot_type return_status = BL_ERR_NONE;


  do
  {
    return_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_RESET_INTERFACE, (void **)&reset_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    if (reset_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_SAHARA_CMD_HANDLER, BL_ERR_INTERFACE_FAILURE);
      break;
    }


    if (xbl_pcie_reset_sep_enabled())
    {
      return_status = reset_if->hw_reset(BOOT_WARM_RESET_TYPE);
      if (return_status != BL_ERR_NONE)
      {
        break;
      }
    }    
    else 
    {
      /* Clear ID so the downloader is not entered again on the next boot. */
      HWIO_TCSR_TCSR_BOOT_MISC_DETECT_OUTM(SBL_DLOAD_MODE_BIT_MASK | SBL_MINIDUMP_MODE_BIT_MASK,0);
    
      return_status = reset_if->hw_reset(BOOT_HARD_RESET_TYPE);
      if (return_status != BL_ERR_NONE)
      {
        break;
      }
    }        
  }while(FALSE);
    
  return return_status;
}

/* ==========================================================================

**  Function :  boot_sahara_command_handler_table_get_interface

** ==========================================================================
*/
/*!
*
* @brief
*   Initialize flashless sahara command handler table.
*
* @param[in] config context and pointer to media_interface_if
*
*/
bl_error_boot_type boot_sahara_command_handler_table_get_interface(void *sahara_cmd_handler_if)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  do
  {
    if (sahara_cmd_handler_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_SAHARA_CMD_HANDLER, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    boot_sahara_command_handler_if *sahara_cmd_handler_ptr = (boot_sahara_command_handler_if *)sahara_cmd_handler_if;

    sahara_cmd_handler_ptr->read_serial_number = boot_read_serial_number;

    sahara_cmd_handler_ptr->get_ddr_training = boot_get_ddr_training;

    sahara_cmd_handler_ptr->reset = boot_force_reset;

  } while (FALSE);

  return return_status;
}
