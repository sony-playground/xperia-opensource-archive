/*===========================================================================

                    BOOT USB DLOAD IF DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external usb dload drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2019-2020 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when        who      what, where, why
--------    ---      ----------------------------------------------------------
05/20/20    rhy      Added wrapper for qusb init with generic Super Speed
08/05/2019  rhy     Initial revision.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_qusb_al_bulk_if.h"
#include "qusb_al_fast_enum.h"

/* read completion callback - currently not used */
typedef void (* sahara_rx_cb_type) (uint32 bytes_read, uint32 err_code);

/* write completion callback - currently not used */
typedef void (* sahara_tx_cb_type) (uint32 bytes_written, uint32 err_code);

static uint32 boot_qusb_al_bulk_receive(  uint8 *rx_buf, 
                                        uint32 len, 
                                        sahara_rx_cb_type rx_cb, 
                                        uint32 * err_code, 
                                        enum boot_sahara_packet_type type)
{
    return qusb_al_bulk_receive(rx_buf, len, rx_cb, err_code);
}

static void boot_qusb_init()
{
    /*  USB team recommends initializing with the highest possible
        speed as the USB driver negotiates the highest speed the 
        hardware block can handle. I.E. Init with Super Speed Plus, 
        even if the HW can only support High Speed. */
    qusb_al_bulk_init(QUSB_MAX_SPEED_SUPER);
}

boot_qusb_al_bulk_if_type qusb_al_bulk_if =
{
    boot_qusb_init,
     
    qusb_al_bulk_shutdown,
    
    qusb_al_bulk_poll,
    
    boot_qusb_al_bulk_receive,
    
    qusb_al_bulk_transmit,
    
    qusb_al_bulk_get_max_raw_data_size,
    
    qusb_al_bulk_get_max_packet_size,
    
    qusb_al_do_fast_enum,
    
};
