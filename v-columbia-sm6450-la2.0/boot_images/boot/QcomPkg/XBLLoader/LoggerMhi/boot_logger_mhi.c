/*===========================================================================

                    BOOT LOGGER MHI DRIVER 

DESCRIPTION
  This file contains the function interface for logging messages during boot
  across the MHI interface.

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2020-2021 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/21/21   ck      Added logger_mhi_deinit
08/10/20   ck      Initial creation leveraging existing UART logger driver

===========================================================================*/


/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include "boot_error_if.h"
#include "boot_config_context.h"
#include "boot_logger_if.h"
#include "boot_mhi_if.h"


/*=============================================================================
            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.
=============================================================================*/

/**
 * Header and formating info.
 * Used to centralize the formatting strings so that if a change was made to
 * these it would propogate throughout the logger module correctly.
 */

static boot_handle _config_context_handle = NULL;
/*=============================================================================
   
                              FUNCTION DEFINITIONS

=============================================================================*/



bl_error_boot_type logger_mhi_init(boot_handle config_context_handle)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_mhi_if_type * mhi_if = NULL;


  /* Validate pointers */
  if (config_context_handle == NULL)
  {
    return_status = GET_ERROR_CODE(BL_ERROR_GROUP_LOGGER, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }

  
  // TBD: we should define an internal structure instead
  _config_context_handle = config_context_handle;


  /* Obtain MHI interface */
  return_status = boot_config_context_get_ptr(_config_context_handle,
                                              CONFIG_CONTEXT_MHI_INTERFACE,
                                              (void **)&mhi_if);
  if (return_status != BL_ERR_NONE)
  {
    goto exit;
  }

  if (mhi_if == NULL)
  {
    return_status = GET_ERROR_CODE(BL_ERROR_GROUP_LOGGER, BL_ERR_NULL_PTR_PASSED);
    goto exit;    
  }


  /* Initialize MHI */
  mhi_if->init();


 exit:  
  return return_status;
}


bl_error_boot_type logger_mhi_deinit(void)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_mhi_if_type * mhi_if = NULL;


  /* Validate pointers */
  if (_config_context_handle == NULL)
  {
    return_status = GET_ERROR_CODE(BL_ERROR_GROUP_LOGGER, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }
 

  /* Obtain MHI interface */
  return_status = boot_config_context_get_ptr(_config_context_handle,
                                              CONFIG_CONTEXT_MHI_INTERFACE,
                                              (void **)&mhi_if);
  if (return_status != BL_ERR_NONE)
  {
    goto exit;
  }

  if (mhi_if == NULL)
  {
    return_status = GET_ERROR_CODE(BL_ERROR_GROUP_LOGGER, BL_ERR_NULL_PTR_PASSED);
    goto exit;    
  }


  /* Shutdown MHI */
  mhi_if->shutdown();


 exit:  
  return return_status;
}


bl_error_boot_type logger_mhi_log_message_raw(char * message,
                                              uint32 data_len)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_mhi_if_type * mhi_if = NULL;


  /* Validate pointers */
  if ((message == NULL) ||
      (_config_context_handle == NULL))
  {
    return_status = GET_ERROR_CODE(BL_ERROR_GROUP_LOGGER, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }


  /* MHI driver cannot handle a call to log a message with a data length of 0. */
  if (data_len == 0)
  {
    goto exit;
  }

  
  /* Obtain MHI interface */
  return_status = boot_config_context_get_ptr(_config_context_handle,
                                              CONFIG_CONTEXT_MHI_INTERFACE,
                                              (void **)&mhi_if);
  if (return_status != BL_ERR_NONE)
  {
    goto exit;
  }

  if (mhi_if == NULL)
  {
    return_status = GET_ERROR_CODE(BL_ERROR_GROUP_LOGGER, BL_ERR_NULL_PTR_PASSED);
    goto exit;    
  }


  /* Send message over MHI */
  return_status = mhi_if->log_message(message,
                                      data_len);
  
  if (return_status != BL_ERR_NONE)
  {
    goto exit;
  }
    

 exit:
  return return_status;
}


static boot_registered_logger_if_type logger_mhi_if = 
{
 logger_mhi_init,
 logger_mhi_deinit,
 logger_mhi_log_message_raw
};


bl_error_boot_type boot_logger_mhi_get_interface(boot_registered_logger_if_type **logger_if)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  
  /* Validate pointers */
  if (logger_if == NULL)
  {
    return_status = GET_ERROR_CODE(BL_ERROR_GROUP_LOGGER, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }


  /* Assign mhi logger interface */
  *logger_if = &logger_mhi_if;
    

 exit:
  return return_status;
}
