/*===========================================================================

                  BOOT SAHARA DISPATCH TABLE DEFINITIONS

DESCRIPTION
  Contains wrapper definition for populating sahara dispatch table

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2020-2021 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when        who      what, where, why
--------    ---      ----------------------------------------------------------
06/04/21    rhy      Removed get_max_packet_size support
05/16/20    rhy      Initial revision.

===========================================================================*/

#include "boot_comdef.h"
#include "boot_media_types.h"
#include "sbl1_hw.h"
#include "boot_config_context.h"
#include "boot_error_if.h"
#include "boot_sahara.h"
#include "boot_mhi_if.h"
#include "boot_qusb_al_bulk_if.h"
#include "boot_sahara_dispatch_tbl.h"

/*=========================================================================

**  Function :  boot_sahara_dispatch_table_init

** ==========================================================================
*/
/*!
* 
* @brief
*   Initialize flashless sahara dispatch table based in boot device.
* 
* @param[in] config context and pointer to media_interface_if
* 
*/
bl_error_boot_type boot_sahara_dispatch_table_init(const boot_handle config_context_handle)
{
    bl_error_boot_type error = BL_ERR_NONE;
    
    boot_media_type boot_device = NO_FLASH;
    boot_sahara_dispatch_tbl *sahara_dispatch_tbl_ptr = NULL;
    boot_mhi_if_type *mhi_if = NULL;
    boot_qusb_al_bulk_if_type *qusb_if = NULL;
    
    boolean nand_pcie_dump = xbl_pcie_fast_boot_enabled();
    
    error = boot_config_context_get_value(config_context_handle, CONFIG_CONTEXT_BOOT_DEVICE, (void *)&boot_device);
    if(error != BL_ERR_NONE)
    {
        return error;
    }
    
    error = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_SAHARA_DISPATCH_TBL, (void **)&sahara_dispatch_tbl_ptr);
    if(error != BL_ERR_NONE)
    {
        return error;
    }
    if(sahara_dispatch_tbl_ptr == NULL)
    {
        return GET_ERROR_CODE(BL_ERROR_GROUP_SAHARA_DISPATCH_TBL, BL_ERR_INTERFACE_FAILURE);
    }

    if(boot_device == PCIE_FLASHLESS || nand_pcie_dump)
    {
        error = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MHI_INTERFACE, (void **)&mhi_if);
        if(error != BL_ERR_NONE)
        {
            return error;
        }
        if(mhi_if == NULL)
        {
            return GET_ERROR_CODE(BL_ERROR_GROUP_SAHARA_DISPATCH_TBL, BL_ERR_INTERFACE_FAILURE);
        }
        
        sahara_dispatch_tbl_ptr->init =     mhi_if->init;
        sahara_dispatch_tbl_ptr->shutdown = mhi_if->shutdown;
        sahara_dispatch_tbl_ptr->poll =     mhi_if->poll;
        sahara_dispatch_tbl_ptr->rx_bulk =  mhi_if->receive;
        sahara_dispatch_tbl_ptr->tx_bulk =  mhi_if->transmit;
        sahara_dispatch_tbl_ptr->get_max_raw_data_size = mhi_if->get_max_raw_data_size;
    }
    else
    {
        error = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_QUSB_AL_BULK_INTERFACE, (void **)&qusb_if);
        if(error != BL_ERR_NONE)
        {
            return error;
        }
        if(qusb_if == NULL)
        {
            return GET_ERROR_CODE(BL_ERROR_GROUP_SAHARA_DISPATCH_TBL, BL_ERR_INTERFACE_FAILURE);
        }
        
        sahara_dispatch_tbl_ptr->init =     qusb_if->boot_qusb_al_bulk_init;
        sahara_dispatch_tbl_ptr->shutdown = qusb_if->boot_usb_al_bulk_shutdown;
        sahara_dispatch_tbl_ptr->poll =     qusb_if->boot_usb_al_bulk_poll;
        sahara_dispatch_tbl_ptr->rx_bulk =  qusb_if->boot_usb_al_bulk_receive;
        sahara_dispatch_tbl_ptr->tx_bulk =  qusb_if->boot_usb_al_bulk_transmit;
        sahara_dispatch_tbl_ptr->get_max_raw_data_size = qusb_if->boot_usb_al_bulk_get_max_raw_data_size;
  }

  return error;
}
    
