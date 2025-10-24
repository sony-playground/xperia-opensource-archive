/*===========================================================================

                         Boot SBL QSEE Interface File

GENERAL DESCRIPTION
  This header file contains declarations and definitions for sbl-qsee
  interface utilities.

Copyright 2014-2017,2020-2022 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when       who         what, where, why
--------   ---         --------------------------------------------------
03/16/22   ck          Add overflow check to image addition
08/24/20   rama        Added boot_qsee_get_interface_ptr & boot_qsee_set_param
03/03/17   ds          remove clobber prot
06/25/15   as          Added boot_sbl_qsee_interface_get_loader_entry
06/25/15   as          Added boot_sbl_qsee_interface_get_image_entry
06/22/15   ck          Added boot_sbl_qsee_interface_get_appsbl_entry
10/30/14   kpa         change uint64 datatype to uintnt
10/29/14   ck          Updated to support 64 bit addresses
03/21/14   ck          Initial version  

===========================================================================*/


#include "boot_error_if.h"
#include "boot_qsee_if.h"

static boot_qsee_interface qsee_interface;


/*===========================================================================
**  Function :  boot_qsee_interface_get_image_entry
** ==========================================================================
*/
/*!
*
* @brief
*   Utility function that gets the image entry number.
*
* @par Dependencies
*   None
*
* @retval
*   BL_ERR_NONE on success
*
* @par Side Effects
*   Do not use this function for finding APPSBL.
*
*/
bl_error_boot_type boot_qsee_interface_get_param(secboot_sw_type image_id,
                                                 boot_qsee_param_type parameter_id,
                                                 uintnt * result)
{
  bl_error_boot_type return_value = BL_ERR_NONE;
  uint32 image_count = 0;
  boot_qsee_interface *qsee_interface_ptr = &qsee_interface;


  /* Validate pointers */
  if (result == NULL)
  {
    return_value = GET_ERROR_CODE(BL_ERROR_GROUP_QSEE, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }


  /* Validate parameter_id */
  if(parameter_id >= BOOT_QSEE_PARAM_MAX_ID)
  {
    return_value = GET_ERROR_CODE(BL_ERROR_GROUP_QSEE, BL_ERR_INVALID_PARAMETER);
    goto exit;
  }

  
  /* Find if there is a entry for the requested image_id */
  for (image_count = 0;
       image_count < BOOT_IMAGES_NUM_ENTRIES;
       image_count++)
  {
    /* Check if current image entry matches requested image_id */
    if (qsee_interface_ptr->boot_image_entry[image_count].image_id != image_id)
    {
      continue;
    }


    switch(parameter_id)
    {
      case BOOT_QSEE_PARAM_IMAGE_E_IDENT:
      {
        *((uint32*)result) = qsee_interface_ptr->boot_image_entry[image_count].e_ident;
        goto exit;
      }

      case BOOT_QSEE_PARAM_IMAGE_ENTRY_POINT:
      {
        *result = qsee_interface_ptr->boot_image_entry[image_count].entry_point;
        goto exit;
      }

      case BOOT_QSEE_PARAM_IMAGE_ENTRY_INDEX:
      {
        *((uint32*)result) = image_count;
        goto exit;
      }

      default:
      {
        return_value = GET_ERROR_CODE(BL_ERROR_GROUP_QSEE, BL_ERR_INVALID_PARAMETER);
        goto exit;
      }
    }
  }


  /* If image_count is >= BOOT_IMAGES_NUM_ENTRIES than image was not found.  Return an error. */
  if (image_count >= BOOT_IMAGES_NUM_ENTRIES)
  {
    return_value = GET_ERROR_CODE(BL_ERROR_GROUP_QSEE, BL_ERR_INVALID_PARAMETER);
    goto exit;
  }


 exit:
  return return_value;
}


/*===========================================================================
**  Function :  boot_qsee_get_interface_ptr
** ==========================================================================
*/
/*!
* 
* @brief  
*   Utility function that retrieves the pointer to qsee interface table.
*
* @par Dependencies
*   None
*
* @retval
*   BL_ERR_NONE on success
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type boot_qsee_get_interface_ptr(boot_qsee_interface * qsee_interface_ptr)
{
  bl_error_boot_type return_value = BL_ERR_NONE;


  /* Validate pointers */
  if (qsee_interface_ptr == NULL)
  {
    return_value = GET_ERROR_CODE(BL_ERROR_GROUP_QSEE, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }
  

  *((void**)qsee_interface_ptr) = &qsee_interface;
  

 exit:
  return return_value;
}


/*===========================================================================
**  Function :  boot_qsee_interface_set_param
** ==========================================================================
*/
/*!
* 
* @brief  
*   Utility function that sets the fields in qsee interface table based on the 
*   prameter passed.
*
* @par Dependencies
*   None
*
* @retval
*   BL_ERR_NONE on success
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type boot_qsee_interface_set_param(boot_qsee_param_type parameter_id,
                                                 uintnt value)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_qsee_interface *qsee_interface_ptr = &qsee_interface;
 

  /* Validate parameter_id */ 
  if(parameter_id >= BOOT_QSEE_PARAM_MAX_ID)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_QSEE, BL_ERR_INVALID_PARAMETER);
    goto exit;
  }
  

  switch(parameter_id)
  {
    case BOOT_QSEE_PARAM_RESET_REQUIRED:
    {
      qsee_interface_ptr->reset_required = (uint32)value;
      break;
    }

    case BOOT_QSEE_PARAM_IMAGE_ID:
    {
      /* Validate number_images before dereferencing array */
      if (qsee_interface_ptr->number_images >= BOOT_IMAGES_NUM_ENTRIES)
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_QSEE, BL_ERR_INVALID_PARAMETER);
        goto exit;
      }

      qsee_interface_ptr->boot_image_entry[qsee_interface_ptr->number_images].image_id = (secboot_sw_type)value;
      qsee_interface_ptr->number_images++;
      break;
    }

    case BOOT_QSEE_PARAM_IMAGE_E_IDENT:
    {
      /* Validate number_images before dereferencing array */
      if (qsee_interface_ptr->number_images >= BOOT_IMAGES_NUM_ENTRIES)
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_QSEE, BL_ERR_INVALID_PARAMETER);
        goto exit;
      }

      qsee_interface_ptr->boot_image_entry[qsee_interface_ptr->number_images].e_ident = (uint32)value;
      break;
    }

    case BOOT_QSEE_PARAM_IMAGE_ENTRY_POINT:
    {
      /* Validate number_images before dereferencing array */
      if (qsee_interface_ptr->number_images >= BOOT_IMAGES_NUM_ENTRIES)
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_QSEE, BL_ERR_INVALID_PARAMETER);
        goto exit;
      }

      qsee_interface_ptr->boot_image_entry[qsee_interface_ptr->number_images].entry_point = (uint64)value;
      break;
    }

    case BOOT_QSEE_PARAM_DDR_ENTER_SELF_REFRESH:
    {
      qsee_interface_ptr->ddr_enter_self_refresh = (uint64)value;
      break;
    }

    case BOOT_QSEE_PARAM_DDR_EXIT_SELF_REFRESH:
    {
      qsee_interface_ptr->ddr_exit_self_refresh = (uint64)value;
      break;
    }

    case BOOT_QSEE_PARAM_APPSBL_ENTRY_INDEX:
    {  
      qsee_interface_ptr->appsbl_entry_index = (uint32)value;
      break;
    }

    default:
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_QSEE, BL_ERR_INVALID_PARAMETER);
      goto exit;
    }
  }


 exit:  
  return status;
}


/*===========================================================================
**  Function :  boot_qsee_interface_init
** ==========================================================================
*/
/*!
* 
* @brief  
*   Utility function that initializes the qsee inter face table
*
* @par Dependencies
*   None
*
* @retval
*   BL_ERR_NONE on success
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type boot_qsee_interface_init(void)
{
  boot_qsee_interface *qsee_interface_ptr = &qsee_interface;

  /* Zero out the interface */
  memset(qsee_interface_ptr, 0x0, sizeof(boot_qsee_interface));

  /* Assign the magic numbers and version */
  qsee_interface_ptr->magic_1 = SBL_QSEE_MAGIC_NUMBER_1;
  qsee_interface_ptr->magic_2 = SBL_QSEE_MAGIC_NUMBER_2;
  qsee_interface_ptr->version = SBL_QSEE_INTERFACE_VERSION;  // version 4
  qsee_interface_ptr->reset_required = (uint32) NO_RESET;

  return BL_ERR_NONE;
}


boot_qsee_if_type qsee_if = {
  boot_qsee_interface_init,
  boot_qsee_get_interface_ptr,
  boot_qsee_interface_get_param,
  boot_qsee_interface_set_param
};
