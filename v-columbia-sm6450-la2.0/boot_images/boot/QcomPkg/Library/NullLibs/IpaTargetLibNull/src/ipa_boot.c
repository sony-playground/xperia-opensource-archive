/*==============================================================================

IPA_BOOT.C

DESCRIPTION
This file contains the IPA HW boot related implementation

Copyright (c) 2021, Qualcomm Technologies, Inc. All rights reserved.
==============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 08/16/21   ck      Added edit history and copyright

=============================================================================*/

/*==============================================================================

INCLUDE FILES FOR MODULE  

==============================================================================*/
#include "ipa_boot.h"

/*==============================================================================
FUNCTION ipa_boot_init()

DESCRIPTION
This function does the minimal configuration to power on IPA for RAM dump 
collection.

PARAMETERS
none

RETURN VALUE
none

DEPENDENCIES  
This is called only after IPA is clocked. Caller should ensure that this
precondition is met.

SIDE EFFECTS
None

==============================================================================*/
void ipa_boot_init(void)
{
}
