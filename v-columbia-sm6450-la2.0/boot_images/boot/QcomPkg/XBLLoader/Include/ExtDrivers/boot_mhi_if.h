#ifndef BOOT_MHI_IF_H
#define BOOT_MHI_IF_H

/*===========================================================================
                    BOOT MHI IF DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external mhi drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2019-2020 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/10/20   ck      Added log_message function
05/19/20   rhy      Changed return type of mhi_init to void (for wrapper)
08/06/19   ep		Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/

#include "boot_sahara.h"
#include "boot_error_if.h"

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/

typedef struct boot_mhi_if_type
{
  void    (*init)(void);
  void    (*poll)(void);
  void    (*shutdown)(void);
  uint32  (*receive)(byte * rx_buf, 
                     uint32 len, 
                     sahara_rx_cb_type rx_cb, 
                     uint32 * err_code,
                     enum boot_sahara_packet_type);
  uint32  (*transmit)(byte * tx_buf,
                      uint32 len,
                      sahara_tx_cb_type tx_cb,
                      uint32 * err_code);
  uint32  (*get_max_packet_size)(void);
  uint32  (*get_max_raw_data_size)(void);
  boot_boolean (*mhi_edl_check)(void);
  uint32  (*log_message)(char * message,
                         uint32 size);
} boot_mhi_if_type;


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

bl_error_boot_type boot_mhi_get_interface(void *mhi_ptr);

#endif /* BOOT_MHI_IF_H */
