/*=============================================================================

                       Boot DDR Information

GENERAL DESCRIPTION
  This module implements functions that update and share ddr info in SBL

Copyright 2010-2011, 2013, 2015, 2017, 2020-2022 by Qualcomm Technologies Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who             what, where, why
--------   ---         --------------------------------------------------
06/08/22   krd         Removed unused variable max_ddr_channels as it is not being used
02/12/21   mkma        add null check
12/25/20   kns         Add size of shub_freq_plan_entry structure to DDRINFO_UEFI_SMEM_ID
12/08/20   rama        ported error handler changes in boot_share_extended_ddr_info
07/22/20   dai         Added get_ddr_region_param API
09/26/17   daisond     Use max ddr channels received using boot_ddr_get_max_channels API
05/25/17   dai         Added support for filling ddr details in shared memory
10/05/15   ck          Corrected copyright
08/07/15   kpa         added support for passing highest bank bit information to ram
                       partition table
06/14/13   dh          Update SBL_DDR_SIZE to MAX_DDR_INTERFACE_NUM
05/23/11   plc         Add support for retrieving partition information
                       for each DDR device
07/22/10   dh          Initial version created by Kedar

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_ddr_info_if.h"
#include "boot_smem_if.h"
#include "boot_ddr_if.h"
#include "boot_ddr_types.h"
#include "boot_config_context.h"


/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
#define MAX_DDR_INTERFACE_NUM     8


#define DDR_INFO_ID  0xFF231599

typedef struct boot_ddr_info
{
  // common for all objects
  boot_handle_common_type handle_data;

  boot_ddr_device_info_type boot_ddr_size_info;
  boot_boolean boot_ddr_info_set;

  boot_memory_mgr_if_type *mem_if;

} boot_ddr_info;


static boot_ddr_info *ddr_info_ptr = NULL;


/*=========================================================================

                       FUNCTION DEFINITIONS

=========================================================================*/


/*===========================================================================

**  Function :  boot_ddr_info_deinit

** ==========================================================================
*/
/*!
 * @brief This function does init
 * @return None.
 *
 */
bl_error_boot_type boot_ddr_info_deinit(void)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    if (ddr_info_ptr == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_DDR_INFO, BL_ERR_UNINITIALIZED_VARIABLE);
      break;
    }

    return_status = ddr_info_ptr->mem_if->free(ddr_info_ptr);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    ddr_info_ptr = NULL;

  } while (FALSE);

  return return_status;
}

/*===========================================================================

**  Function :  boot_ddr_info_init

** ==========================================================================
*/
/*!
 * @brief This function does init
 * @return None.
 *
 */

bl_error_boot_type boot_ddr_info_init(boot_handle config_context_handle)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_ddr_info *di_ptr = NULL;
  boot_memory_mgr_if_type *mem_if = NULL;

  do
  {
    if (ddr_info_ptr != NULL)
    {
      return_status = boot_ddr_info_deinit();
      if (return_status != BL_ERR_NONE)
      {
        break;
      }
    }

    return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    return_status = mem_if->malloc(sizeof(boot_ddr_info), (void *)&di_ptr);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }
    else if (di_ptr == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_DATA, BL_ERR_MEMORY_ALLOC_FAIL);
      break;
    }

    di_ptr->boot_ddr_info_set = FALSE;

    di_ptr->handle_data.config_context_handle = config_context_handle;
    di_ptr->handle_data.id = DDR_INFO_ID;

    di_ptr->mem_if = mem_if;

    ddr_info_ptr = di_ptr;

  } while (FALSE);

  return return_status;

}



/*===========================================================================

**  Function :  boot_share_extended_ddr_info

** ==========================================================================
*/
/*!
*
* @brief
*    This function gets the ddr partition information from ddr driver and
*    adds it to shared data structure, including number of partitions for
*    each DDR device.
*
* @param[out] shared_dev_info Pointer to the shared device information
* @param[in] ddr_available Pointer to the DDR size information
* @param[in] ddr_available_partition Pointer to DDR partition information
*
* @par Dependencies
*   None
*
* @retval
*   None
*
* @par Side Effects
*   None
*/
bl_error_boot_type boot_share_extended_ddr_info
(
  boot_ddr_device_info_type *shared_dev_info
)
{
  static boot_ddr_info_type ddr_info[MAX_DDR_INTERFACE_NUM];
  static boot_extended_ddr_info_type ddr_partition_info[MAX_DDR_INTERFACE_NUM];
  uint8 i;
  uint32 param_size=0;
  boot_ddr_if_type *ddr_if;
  bl_error_boot_type status = BL_ERR_NONE;


  if (shared_dev_info == NULL)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_DDR_INFO, BL_ERR_INVALID_PARAMETER);
    goto exit;
  }

  status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_DDR_INTERFACE, (void **)&ddr_if);
  if (status != BL_ERR_NONE)
  {
    goto exit;
  }

  shared_dev_info->ddr_info = ddr_info;
  shared_dev_info->ddr_partition_info = ddr_partition_info;
  shared_dev_info->noofddr = 0;

  shared_dev_info->noofddr = ddr_if->get_num_of_ddr_regions();
  for (i=0; i<shared_dev_info->noofddr; i++)
  {
    param_size=0;
    status = ddr_if->get_ddr_region_param(i, REGION_SIZE, NULL, &param_size);
    if (status != BL_ERR_NONE)
    {
      goto exit;
    }
    status = ddr_if->get_ddr_region_param(i, REGION_SIZE, &(shared_dev_info->ddr_info[i].ramsize), &param_size);
    if (status != BL_ERR_NONE)
    {
      goto exit;
    }
    param_size=0;
    status = ddr_if->get_ddr_region_param(i, REGION_START_ADDRESS, NULL, &param_size);
    if (status != BL_ERR_NONE)
    {
      goto exit;
    }
    status = ddr_if->get_ddr_region_param(i, REGION_START_ADDRESS, &(shared_dev_info->ddr_info[i].cs_addr), &param_size);
    if (status != BL_ERR_NONE)
    {
      goto exit;
    }
    param_size=0;
    status = ddr_if->get_ddr_region_param(i, NUM_PARTITIONS, NULL, &param_size);
    if (status != BL_ERR_NONE)
    {
      goto exit;
    }
    status = ddr_if->get_ddr_region_param(i, NUM_PARTITIONS, &(shared_dev_info->ddr_partition_info[i].num_partitions), &param_size);
    if (status != BL_ERR_NONE)
    {
      goto exit;
    }
    param_size=0;
    status = ddr_if->get_ddr_region_param(i, REGION_START_ADDRESS, NULL, &param_size);
    if (status != BL_ERR_NONE)
    {
      goto exit;
    }
    status = ddr_if->get_ddr_region_param(i, REGION_START_ADDRESS, &(shared_dev_info->ddr_partition_info[i].sdram_addr), &param_size);
    if (status != BL_ERR_NONE)
    {
      goto exit;
    }
    param_size=0;
    status = ddr_if->get_ddr_region_param(i, HIGHEST_BANK_BIT, NULL, &param_size);
    if (status != BL_ERR_NONE)
    {
      goto exit;
    }
    status = ddr_if->get_ddr_region_param(i, HIGHEST_BANK_BIT, &(shared_dev_info->ddr_partition_info[i].highest_bank_bit), &param_size);
    if (status != BL_ERR_NONE)
    {
      goto exit;
    }
  }

exit:
  return status;
}

/*===========================================================================

**  Function :  boot_set_ddr_info

** ==========================================================================
*/
/*!
*
* @brief
*   This function extracts pointer for DDR info from shared data structure.
*   should only be called after the ddr_shared_info pointer inside
*   bl_shared_data is initialized
*
* @param[in] bl_shared_data Pointer to the shared data structure
*
* @par Dependencies
*   None
*
* @retval
*   pointer to structure containing ddr information (ddr_size_info )
*
* @par Side Effects
*   None
*
*/
bl_error_boot_type boot_set_ddr_info(boot_ddr_device_info_type *ddr_shared_info_ptr)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    if (ddr_info_ptr == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_DDR_INFO, BL_ERR_UNINITIALIZED_VARIABLE);
      break;
    }
    if (ddr_shared_info_ptr == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_DDR_INFO, BL_ERR_INVALID_PARAMETER);
      break;
    }

    ddr_info_ptr->boot_ddr_size_info = *ddr_shared_info_ptr;
    ddr_info_ptr->boot_ddr_info_set = TRUE;

  } while (FALSE);

  return return_status;
}


/*===========================================================================

**  Function :  boot_get_ddr_info

** ==========================================================================
*/
/*!
*
* @brief
*   This function returns information about DDR.
*
* @par Dependencies
*   None
*
* @retval
*   pointer to structure containing ddr information (ddr_size_info )
*
* @par Side Effects
*   None
*
*/
boot_ddr_device_info_type *boot_get_ddr_info(void)
{
  boot_ddr_device_info_type *ret = NULL;

  do
  {
    if (ddr_info_ptr == NULL)
    {
      break;
    }

    if (!ddr_info_ptr->boot_ddr_info_set)
    {
      break;
    }

    ret = &ddr_info_ptr->boot_ddr_size_info;
  } while (FALSE);

  return ret;
}



/*===========================================================================

**  Function :  boot_populate_ddr_details_shared_table

** ==========================================================================
* @brief
*    This function initializes ddr details required in shared memory.

* @param[in] bl_shared_data Pointer to the shared data structure
*
* @par Dependencies
*   None
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/


bl_error_boot_type boot_populate_ddr_details_shared_table(boot_handle config_context_handle)
{
  ddr_details_entry_ptr_type ddr_details_entry_ptr = NULL;
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_smem_if_type *smem_if = NULL;
  boot_ddr_if_type *ddr_if = NULL;

  do
  {
    return_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_SMEM_INTERFACE, (void **)&smem_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    return_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_DDR_INTERFACE, (void **)&ddr_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    ddr_details_entry_ptr = (ddr_details_entry_ptr_type)smem_if->alloc(DDRINFO_UEFI_SMEM_ID, (sizeof(ddr_details_entry) + sizeof(DDR_REGIONS_ENTRY)+ sizeof(shub_freq_plan_entry)+ sizeof(ddr_misc_info)));

    /* verify shared memory allocation for ddr_det_entry_ptr_type didn't fail */
    if (ddr_details_entry_ptr == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_DDR_INFO, BL_ERR_UNINITIALIZED_VARIABLE);
      break;
    }

    /* verify if ddr info table is in shared memory region */
    if ((((uintnt)ddr_details_entry_ptr) > SCL_SHARED_RAM_BASE) &&
        (((uintnt)ddr_details_entry_ptr + sizeof(ddr_details_entry) + sizeof(DDR_REGIONS_ENTRY) + sizeof(shub_freq_plan_entry)+ sizeof(ddr_misc_info))
         <=(SCL_SHARED_RAM_BASE + SCL_SHARED_RAM_SIZE)))
    {
    }
    else
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_DDR_INFO, BL_ERR_UNINITIALIZED_VARIABLE);
      break;
    }

    if ((ddr_if != NULL) && (ddr_if->get_ddr_details_table != NULL))
      ddr_if->get_ddr_details_table(ddr_details_entry_ptr);

  } while (FALSE);

  return return_status;
}



/*===========================================================================
**  Function :  boot_ddr_info_get_interface
** ==========================================================================
*/
/*!
*
* @brief
*   This function initializes a boot_ddr_info_get_interface object
*
* @par Dependencies
*   None
*
*/
/*
bl_error_boot_type boot_ddr_info_get_interface(void *ptr)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    boot_ddr_info_if_type *ddr_info_if = (boot_ddr_info_if_type *)ptr;
    if(ddr_info_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_DDR_INFO, BL_ERR_INVALID_PARAMETER);
      break;
    }

    ddr_info_if->init = boot_ddr_info_init;
    ddr_info_if->deinit = boot_ddr_info_deinit;
    ddr_info_if->share_extended_ddr_info = boot_share_extended_ddr_info;
    ddr_info_if->set_ddr_info = boot_set_ddr_info;
    ddr_info_if->get_ddr_info = boot_get_ddr_info;
    ddr_info_if->populate_ddr_details_shared_table = boot_populate_ddr_details_shared_table;

  } while(FALSE);

  return return_status;
}
*/


boot_ddr_info_if_type ddr_info_if =
{
  boot_ddr_info_init,
  boot_ddr_info_deinit,
  boot_share_extended_ddr_info,
  boot_set_ddr_info,
  boot_get_ddr_info,
  boot_populate_ddr_details_shared_table
};
