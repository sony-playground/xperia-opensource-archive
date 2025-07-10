/*=============================================================================
  Copyright (c) 2008, 2014, 2020 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary

=============================================================================*/
/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 08/12/14   aa     Added Function declarations for public API to support String 
                   based devices
 08/12/14   aa     Added history 

=============================================================================*/

#ifndef __DALDEVICE_COMMON_H__
#define __DALDEVICE_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DALStdDef.h"

typedef struct DalDeviceInfo DalDeviceInfo;
struct DalDeviceInfo
{
   uint32 sizeOfActual;
   uint32 Version;
   char Name[32];
};

typedef struct DalDeviceHandle DalDeviceHandle;
typedef struct DalDevice DalDevice;
struct DalDevice
{
   DALResult (*Attach)(const char*,DALDEVICEID,DalDeviceHandle **);
   uint32    (*Detach)(DalDeviceHandle *);
   DALResult (*Init)(DalDeviceHandle *);
   DALResult (*DeInit)(DalDeviceHandle *);
   DALResult (*Open)(DalDeviceHandle *, uint32);
   DALResult (*Close)(DalDeviceHandle *);
   DALResult (*Info)(DalDeviceHandle *, DalDeviceInfo *, uint32);
   DALResult (*PowerEvent)(DalDeviceHandle *, DalPowerCmd, DalPowerDomain);
   DALResult (*SysRequest)(DalDeviceHandle *, DalSysReq, const void *, uint32,
                           void *,uint32, uint32*);
};
//Users will define interface in the following manner
typedef struct DalInterface DalInterface;
struct DalInterface
{
   struct DalDevice DalDevice;
   //User will add their prototypes here.
};

struct DalDeviceHandle
{
   uint32 dwDalHandleId;
   const DalInterface *pVtbl;
   void         *pClientCtxt;
};

typedef struct DalDeviceHandle * DALDEVICEHANDLE;

#ifdef __cplusplus
}
#endif

#endif
