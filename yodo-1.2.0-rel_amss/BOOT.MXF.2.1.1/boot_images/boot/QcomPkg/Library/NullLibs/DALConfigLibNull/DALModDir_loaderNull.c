/**
  Copyright (c) 2021, Qualcomm Technologies, Inc. All rights reserved.
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 08/16/21   ck      Added edit history and copyright

=============================================================================*/


#include "DALStdDef.h" 
#include "DALReg.h" 
#include "DALSysTypes.h"

static DALREG_DriverInfo * DALDriverInfoArr[] = {NULL};

DALREG_DriverInfoList gDALModDriverInfoList = {1, DALDriverInfoArr}; 



StringDevice DAL_Mod_driver_list[] = {
};

DALProps gDALModStringDeviceInfoList = {NULL, 0 ,1, DAL_Mod_driver_list};
