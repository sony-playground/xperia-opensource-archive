/**
  @file DbiDumpVariantLib.h
 
  SDI ram dumps 

  Copyright (c) 2021 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Confidential and Proprietary.
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 08/19/21   ka      Initial Version

 =============================================================================*/

#ifndef _DBIDUMPVARIANTLIB_H_
#define _DBIDUMPVARIANTLIB_H_

#include <Library/DbiDumpLib.h>
#include <Library/UefiBootServicesTableLib.h>

/* Create APREG SHM bridge region */
EFI_STATUS AddShmBridgeRegion (VOID);

#endif /* _DBIDUMPVARIANTLIB_H_ */

