/*===========================================================================

                    BOOT MHI IF DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external mhi drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2019-2022 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/03/22   ck      Added mhi_boot_set_dma_enable
06/04/21   rhy     Removed get_max_packet_size support
01/21/21   ck      Added virtual instances logic
08/11/20   ck      Added log_message function
04/01/20   rhy     Added mhi edl check.
08/06/19   ep     Initial Creation.

===========================================================================*/

/*==========================================================================
                               INCLUDE FILES
===========================================================================*/
#include "boot_mhi_if.h"
#include "mhi_boot.h"


/* MHI can be used for multiple uses.  I.E. data transfer and boot messaging.
   Data transfer and boot messaging logic is not coupled so one could close
   MHI on the other.  Use a counter to create "virtual instances" and ensure
   the driver is not initialized multiple times, and not closed when still
   in use. */
static unsigned char _mhi_open_instances = 0;


/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/

/*===========================================================================
**  Function :  boot_mhi_boot_init
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_mhi_get_interface
*
* @par Dependencies
*   None 
* 
*/
void boot_mhi_boot_init(void)
{
  /* Only initialize once */
  if (_mhi_open_instances == 0)
  {
    /* return type of the following is uint32*/
    mhi_boot_init();
  }


  /* Increment open instances */
  _mhi_open_instances += 1;
}


/*===========================================================================
**  Function :  boot_mhi_boot_shutdown
** ==========================================================================
*/
/*!
* 
* @brief
*   This function shuts down a boot_mhi_get_interface
*
* @par Dependencies
*   None 
* 
*/
void boot_mhi_boot_shutdown(void)
{
  /* If no instances are open then just return */
  if (_mhi_open_instances == 0)
  {
    return;
  }


  /* Decrement open instances */
  _mhi_open_instances -= 1;


  /* If all instances are now closed then shutdown MHI */
  if (_mhi_open_instances == 0)
  {
    /* return type of the following is uint32*/
    mhi_boot_shutdown();
  }
}


/*===========================================================================
**  Function :  boot_mhi_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_mhi_get_interface
*
* @par Dependencies
*   None 
* 
*/

bl_error_boot_type boot_mhi_get_interface(void *mhi_ptr)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  
  do
  {
    if(mhi_ptr == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_MHI, BL_ERR_INVALID_PARAMETER);
      break;
    }
    
    boot_mhi_if_type *mhi_if = (boot_mhi_if_type *)mhi_ptr;
    
    mhi_if->init                  = boot_mhi_boot_init;
    mhi_if->poll                  = mhi_boot_poll;
    mhi_if->shutdown              = boot_mhi_boot_shutdown;
    mhi_if->receive               = mhi_boot_rx_bulk;
    mhi_if->transmit              = mhi_boot_tx_bulk;
    mhi_if->get_max_raw_data_size = mhi_boot_get_max_raw_data_size;
    mhi_if->mhi_edl_check         = mhi_boot_edl_check;
    mhi_if->log_message           = mhi_boot_log_message;
    mhi_if->set_dma_enable        = mhi_boot_set_dma_enable;
   
  } while(FALSE);
  
  return return_status;
}

