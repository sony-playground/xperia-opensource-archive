#ifndef BOOT_QUSB_AL_BULK_IF_H
#define BOOT_QUSB_AL_BULK_IF_H

/*=============================================================================

                         QUSB Interface

GENERAL DESCRIPTION
  Contains wrapper definition for external QUSB drivers

Copyright 2020 by Qualcomm Technologies Inc.  All Rights Reserved.
=============================================================================*/

/*=============================================================================

                            EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

when       who       what, where, why
--------   ---       ----------------------------------------------------------
05/19/20   rhy       Changed argument of usb init to void (for wrapper)
03/24/20   rhy       Initial revision
=============================================================================*/

/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include "qusb_al_bulk.h"

typedef struct boot_qusb_al_bulk_if_type
{    
    void (*boot_qusb_al_bulk_init) (void);
     
    void (*boot_usb_al_bulk_shutdown)(void);
    
    void (*boot_usb_al_bulk_poll)(void);
    
    uint32 (*boot_usb_al_bulk_receive) (byte *, 
                                        uint32 , 
                                        sahara_rx_cb_type , 
                                        uint32 *,
                                        enum boot_sahara_packet_type);
    
    uint32 (*boot_usb_al_bulk_transmit)(byte *,    
                                        uint32 ,       
                                        sahara_tx_cb_type , 
                                        uint32 *);
    
    uint32 (*boot_usb_al_bulk_get_max_raw_data_size)(void);
    
    uint32 (*boot_usb_al_bulk_get_max_packet_size)(void);
    
    void (*boot_qusb_al_do_fast_enum)(qusb_max_speed_required_t);
    
} boot_qusb_al_bulk_if_type;

extern boot_qusb_al_bulk_if_type qusb_al_bulk_if;

#endif /* BOOT_QUSB_AL_BULK_IF_H */