/*==============================================================================

FILE:      Busywait.c

DESCRIPTION: This file implements the busywait routine using Qtimer registers. 

===========================================================================
             Copyright (c) 2014 QUALCOMM Technologies, Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
===========================================================================

                              EDIT HISTORY

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 13/08/20  amarsing Migrated from ArmTimer to QcomTimer.
 11/14/14  pbitra   Created.

=============================================================================*/

#include <Library/TimerLib.h>


/*===========================================================================

                           DATA DEFINITIONS

============================================================================*/



/*==========================================================================

  FUNCTION      busywait
==========================================================================*/
void busywait
(
  UINT32 pause_time_us
)
{
  MicroSecondDelay(pause_time_us);
} /* END busywait */
