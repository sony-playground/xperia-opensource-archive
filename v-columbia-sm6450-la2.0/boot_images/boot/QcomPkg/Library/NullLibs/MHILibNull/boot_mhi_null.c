/*===========================================================================

                    BOOT MHI IF DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external mhi drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2020 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/30/20   rhy     Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/

#include "mhi_boot.h"

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/
uint32 mhi_boot_init()
{
    return BULK_SUCCESS;
}

void mhi_boot_poll()
{}

void mhi_boot_shutdown()
{}

uint32 mhi_boot_rx_bulk(byte * rx_buf, 
                        uint32 len, 
                        sahara_rx_cb_type rx_cb, 
                        uint32 * err_code,
                        enum boot_sahara_packet_type type)
{ return 0; }

uint32 mhi_boot_tx_bulk(byte * tx_buf,
                         uint32 len,
                         sahara_tx_cb_type tx_cb,
                         uint32 * err_code)
{ return 0; }

uint32 mhi_boot_get_max_packet_size()
{ return 0; }

uint32 mhi_boot_get_max_raw_data_size()
{ return 0; }

boot_boolean mhi_boot_edl_check()
{ return FALSE; }