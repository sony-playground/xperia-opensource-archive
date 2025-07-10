/** @file TargetResetLib.h
   
  Contains TargetReset specific library functions.

  Copyright (c) 2013, 2021 by Qualcomm Technologies, Inc. All Rights Reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 04/27/21   am      Added SaveSysRegInInfoBlk function
 06/17/13   vk      Initial Version
=============================================================================*/
#ifndef __TARGET_RESET_LIB_H__
#define __TARGET_RESET_LIB_H__

#include <Uefi.h>

VOID
TargetPanic (VOID);

VOID
SaveSysRegInInfoBlk (VOID);
#endif /* __TARGET_RESET_LIB_H_ */
