/** @file ButtonsBootLibNull.c

    Stub functions for Buttons Boot Lib
		 
    Copyright (c) 2020, Qualcomm Technologies, Inc. All rights reserved.
**/
		 
/*=============================================================================
                              EDIT HISTORY
 
	 
when       who     what, where, why
--------   ---     -----------------------------------------------------------
03/04/20   ck      Added CaptureBootButtonsState
02/10/20   ck      Initial revision
	 
=============================================================================*/
#include "com_dtypes.h"

/* Public API, capture button status */
void CaptureBootButtonsState()
{
}

int32 BootButtonsStateRead(uint32 *ButtonState)
{
   return 0;
}

