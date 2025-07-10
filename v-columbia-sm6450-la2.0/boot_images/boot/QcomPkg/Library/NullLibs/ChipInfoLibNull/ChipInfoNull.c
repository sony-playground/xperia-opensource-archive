/*============================================================================

 FILE:      ChipInfoNull.c

 ============================================================================
 Copyright (c) 2016-2017, 2019, 2021 Qualcomm Technologies, Inc.
 All Rights Reserved.
 QUALCOMM Proprietary/GTDR
 ============================================================================*/

#include "com_dtypes.h"
#include "ChipInfoDefs.h"
#include "DALStdErr.h"
#include "DALStdDef.h"
#include "ChipInfoLocal.h"

extern ChipInfoCtxtType ChipInfoCtxt;

ChipInfoVersionType ChipInfo_GetChipVersion(void)
{
  return 0;
} 

uint32 ChipInfo_GetRawChipVersion(void)
{
  return 0;
}

ChipInfoIdType ChipInfo_GetChipId(void)
{
  return CHIPINFO_ID_UNKNOWN;
}

uint32 ChipInfo_GetRawChipId(void)
{
  return 0;
}

DALResult ChipInfo_GetChipIdString(char *szChipIdStr, uint32 nMaxLen)
{
  return DAL_SUCCESS;
}

ChipInfoFamilyType ChipInfo_GetChipFamily(void)
{
  return CHIPINFO_FAMILY_UNKNOWN;
}

DALResult ChipInfo_GetMarketingNameString(char *pszMarketingNameStr, uint32 nMaxlen)
{
  return DAL_SUCCESS;
}

ChipInfoModemType ChipInfo_GetModemSupport(void)
{
  return 0;
}

ChipInfoSerialNumType ChipInfo_GetSerialNumber(void)
{
  return 0;
}

ChipInfoFoundryIdType ChipInfo_GetFoundryId(void)
{
  return CHIPINFO_FOUNDRYID_UNKNOWN;
}

uint32 ChipInfo_GetRawDeviceFamily(void)
{
  return 0;
}

uint32 ChipInfo_GetRawDeviceNumber(void)
{
  return 0;
}

ChipInfoQFPROMChipIdType ChipInfo_GetQFPROMChipId(void)
{
  return 0;
}

DALResult ChipInfo_GetDefectivePart(ChipInfoPartType ePart, uint32 *pnMask)
{
  return DAL_SUCCESS;
}

DALResult ChipInfo_GetDefectiveCPUs(uint32 nCPUCluster, uint32 *pnMask)
{
  return DAL_SUCCESS;
}

