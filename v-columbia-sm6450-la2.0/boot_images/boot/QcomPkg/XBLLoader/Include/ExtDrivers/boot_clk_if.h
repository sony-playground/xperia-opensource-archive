#ifndef BOOT_CLK_IF_H
#define BOOT_CLK_IF_H
/*===========================================================================

                    BOOT CLK IF DEFINITIONS

DESCRIPTION
  Contains if definition for external clock drivers

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
06/19/20   rama    Updated boot_clk_if_type
08/02/19   ep      Created the file

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_framework.h"
#include "boot_error_if.h"
#include "ClockBoot.h"
#include "Clock.h"

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 




typedef struct boot_clk_if_type
{
  bl_error_boot_type (*init)(void);
  bl_error_boot_type (*init_group)(const char *szName);
  ClockResult (*exit_boot)(void);
  uint32 (*get_freq_khz)(const char *szName);
  bl_error_boot_type (*set_freq)(const char *szName, uint32_t nfreq, ClockFrequencyType eMatch);
  bl_error_boot_type (*initRPM)(void);
} boot_clk_if_type;


/*===========================================================================
**  Function :  boot_clk_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_clk_get_interface
*
* @par Dependencies
*   None 
* 
*/

bl_error_boot_type boot_clk_get_interface(void *ptr);

extern boot_clk_if_type clk_if;


#endif /* BOOT_CLK_IF_H */