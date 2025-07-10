#ifndef IPA_BOOT_H
#define IPA_BOOT_H
/*==============================================================================

                IPA_BOOT.H

DESCRIPTION
  This file contains the required details for IPA Booot

Copyright (c) 2020 Qualcomm Technologies Incorporated. 
All Rights Reserved.
Qualcomm Confidential and Proprietary
==============================================================================*/



/*==============================================================================

                          INCLUDE FILES FOR MODULE

==============================================================================*/

#include "comdef.h"

/*==============================================================================

                           DEFINITIONS

==============================================================================*/

void ipa_boot_init(void);

/*==============================================================================
FUNCTION ipa_dma_hw_init()

DESCRIPTION
This function is used to load the GSI, IPA Sequencers and initialize the HW for 
DMA purposes. 
This API is called for PCIE flashless boot config in SBL

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
void ipa_dma_hw_init(void);

/*==============================================================================
FUNCTION ipa_dma_hw_deinit()

DESCRIPTION
This function is to be called once all the DMA transfers are completed and just before
MHI shutdown is completed. 

This function stops all the GSI DMA channels and implements a TCSR IPA HALT Seq WA
for a NOC IDLE HW bug.

PARAMETERS
none

RETURN VALUE
IPA_DMA_SUCCESS - on success
IPA_DMA_ERROR - the operation failed
IPA_DMA_EINVAL - the channel is synchronous or asynchronous but not working in
IPA_DMA_ASYNC_INT_MODE_POLL

DEPENDENCIES
This is called only after IPA is clocked and just before shutdown sequence. 
Caller should ensure that this precondition is met.

SIDE EFFECTS
None
==============================================================================*/
int32 ipa_dma_hw_deinit(void);

void ipa_core_hw_init(void);

#endif /* IPA_BOOT_H */

