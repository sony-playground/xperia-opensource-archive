/*===========================================================================

                    BOOT POWER IF DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external power drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2019 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who    what, where, why
--------   ---    ----------------------------------------------------------
08/05/19   ep     Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_error_if.h"
#include "railway.h"
#include "cpr.h"
#include "boot_power_if.h"

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 


/*===========================================================================
**  Function :  boot_power_get_interface
** ==========================================================================
*/
 
boot_power_if_type power_if = {
  railway_init,
  cpr_init,
  cpr_externalize_state,
  aop_mini_dump_init
};
