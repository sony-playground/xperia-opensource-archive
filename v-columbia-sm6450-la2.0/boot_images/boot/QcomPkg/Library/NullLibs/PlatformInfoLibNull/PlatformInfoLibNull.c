/**
  @file PlatformInfoLibNull.c
*/
/*
  ====================================================================
  Copyright (c) 2021 Qualcomm Technologies, Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.
  ====================================================================
*/

#include "PlatformInfoDefs.h"
#include "PlatformInfoInternal.h"
#include "DALStdDef.h"
#include "DALStdErr.h"


DALResult PlatformInfo_Init(void)
{
  return DAL_SUCCESS;
}


DalPlatformInfoPlatformType PlatformInfo_Platform(void)
{
  return DALPLATFORMINFO_TYPE_UNKNOWN;
} 


uint32 PlatformInfo_PlatformSubtype(void)
{
  return 0;
}


uint32 PlatformInfo_PlatformVersion(void)
{
  return 0;
}


boolean PlatformInfo_IsFusion(void)
{
  return FALSE;
}


DALResult PlatformInfo_GetPlatformInfo(DalPlatformInfoPlatformInfoType *pInfo)
{
  return DAL_SUCCESS;
}


DALResult PlatformInfo_GetKeyValue(DalPlatformInfoKeyType eKey,
                                   uint32 * nValue)
{
  return DAL_SUCCESS;
}


PlatformInfoDrvCtxt *PlatformInfo_GetDrvCtxt(void)
{
  return NULL;
}


DalPlatformInfoPlatformType PlatformInfo_DetectPlatformType(void)
{
  return DALPLATFORMINFO_TYPE_UNKNOWN;
}
