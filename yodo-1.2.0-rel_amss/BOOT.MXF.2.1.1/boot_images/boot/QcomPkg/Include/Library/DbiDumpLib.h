/**
  @file DbiDumpLib.h
 
  SDI ram dumps 

  Copyright (c) 2016,2021 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Confidential and Proprietary.
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 08/19/21   ka      relocate UefiBootServicesTableLib.h to DbiDumpVariantLib.h
 10/24/16   ai      Initial Version

 =============================================================================*/

#ifndef _DBIDUMPLIB_H_
#define _DBIDUMPLIB_H_

#include <Library/DBIDump.h>

/* Setup DBI Dump Table only */
VOID SetupDBIDumpTable(VOID);

/* Init DBI Dump Table and set crashdump cookie */
EFI_STATUS InitDbiDump(VOID); 

/* Save Cpu Context to UefiInfoBlock */
EFI_STATUS SaveUefiContext(EFI_SYSTEM_CONTEXT SystemContext);

#endif /* _DBIDUMPLIB_H_ */

