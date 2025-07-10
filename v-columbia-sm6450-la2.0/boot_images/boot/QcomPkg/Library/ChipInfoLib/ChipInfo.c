/*============================================================================

 FILE:      ChipInfo.c

 DESCRIPTION:
 This file implements the Chip Info APIs common to both XBL Loader and Core

 PUBLIC CLASSES:
 ChipInfo_GetChipVersion
 ChipInfo_GetRawChipVersion
 ChipInfo_GetChipId
 ChipInfo_GetRawChipId
 ChipInfo_GetChipIdString
 ChipInfo_GetChipFamily
 ChipInfo_GetMarketingNameString
 ChipInfo_GetModemSupport
 ChipInfo_GetSerialNumber
 ChipInfo_GetFoundryId
 ChipInfo_GetRawDeviceFamily
 ChipInfo_GetRawDeviceNumber
 ChipInfo_GetQFPROMChipId
 ChipInfo_GetDisabledCPUs
 ChipInfo_GetSKU
 ChipInfo_GetDisabledFeatures
 ChipInfo_IsPartDisabled

 ============================================================================
 Copyright (c) 2016-2017, 2019, 2022, 2023 Qualcomm Technologies, Inc.All rights reserved.
 ============================================================================

 $Header: //components/rel/core.boot/6.0/QcomPkg/Library/ChipInfoLib/ChipInfo.c#6 $
 $DateTime: 2023/05/11 20:39:31 $
 $Author: pwbldsvc $

==========================================================================*/

/*=========================================================================
 Include Files
 ==========================================================================*/

#include "ChipInfoLocal.h"
#include "DALStdErr.h"
#include "DALStdDef.h"
#include "ChipInfoImage.h"
#include "ChipInfoDefs.h"

/*==============================================================================
	DEFINES
==============================================================================*/

#define UNUSED(x) (void)(x)

/*=========================================================================
      Data Definitions
==========================================================================*/
extern ChipInfoCtxtType ChipInfoCtxt;


/*=========================================================================
 Functions
 ==========================================================================*/

/* ===========================================================================
 **  FUNCTION      ChipInfo_GetChipVersion
 **
 **  DESCRIPTION   See ChipInfo.h
 ** ======================================================================== */

ChipInfoVersionType ChipInfo_GetChipVersion(void)
{
  return ChipInfoCtxt.nVersion;
} /* END ChipInfo_GetChipVersion */

/* ===========================================================================
 **  FUNCTION      ChipInfo_GetRawChipVersion
 **
 **  DESCRIPTION   See ChipInfo.h
 ** ======================================================================== */

uint32 ChipInfo_GetRawChipVersion(void)
{
  return ChipInfoCtxt.nRevNumber;
} /* END ChipInfo_GetRawChipVersion */

/* =========================================================================
 **  FUNCTION      Chipinfo_GetChipId
 **
 **  DESCRIPTION   See ChipInfo.h
 ** =========================================================================*/

ChipInfoIdType ChipInfo_GetChipId(void)
{
  return ChipInfoCtxt.eChipInfoId;
} /*  END ChipInfo_GetChipId  */

/* ===========================================================================
 **  FUNCTION      ChipInfo_GetRawChipId
 **
 **  DESCRIPTION   See ChipInfo.h
 ** ======================================================================== */

uint32 ChipInfo_GetRawChipId(void)
{
  return ChipInfoCtxt.nRawPartNum;
} /*  END ChipInfo_GetRawChipId    */

/* ===========================================================================
 **  FUNCTION      ChipInfo_GetChipIdString
 **
 **  DESCRIPTION   See ChipInfo.h
 ** ======================================================================== */

DALResult ChipInfo_GetChipIdString(char *szChipIdStr, uint32 nMaxLen)
{
  uint32 len = 0;
  if (nMaxLen < CHIPINFO_MAX_ID_LENGTH)
  {
    len = nMaxLen;
  }
  else
  {
    len = CHIPINFO_MAX_ID_LENGTH;
  }

  ChipInfo_strcpy(szChipIdStr, ChipInfoCtxt.szChipIdString, len);
  return DAL_SUCCESS;
} /*  END ChipInfo_GetChipIdString    */

/* ===========================================================================
 **  FUNCTION      ChipInfo_GetChipFamily
 **
 **  DESCRIPTION   See ChipInfo.h
 ** ======================================================================== */

ChipInfoFamilyType ChipInfo_GetChipFamily(void)
{
  return ChipInfoCtxt.eFamilyId;
} /* END Chipinfo_GetChipFamily */

/* ===========================================================================
 **  FUNCTION      ChipInfo_GetMarketingNameString
 **
 **  DESCRIPTION   See ChipInfo.h
 ** ======================================================================== */

DALResult ChipInfo_GetMarketingNameString(char *pszMarketingNameStr, uint32 nMaxlen)
{
  ChipInfo_GetChipIdString(pszMarketingNameStr, nMaxlen);
  return DAL_SUCCESS;
} /*  END ChipInfo_GetMarketingNameString    */

/* ===========================================================================
 **  FUNCTION      ChipInfo_GetModemSupport
 **
 **  DESCRIPTION   See ChipInfo.h
 ** ======================================================================== */

ChipInfoModemType ChipInfo_GetModemSupport(void)
{
  return ChipInfoCtxt.nModemSupported;
} /* END Chipinfo_GetModemSupport */

/* ===========================================================================
 **  FUNCTION      ChipInfo_GetSerialNumber
 **
 **  DESCRIPTION   See ChipInfo.h
 ** ======================================================================== */

ChipInfoSerialNumType ChipInfo_GetSerialNumber(void)
{
  return ChipInfoCtxt.nSerialNum;
} /*  END ChipInfo_GetSerialNumber    */

/* ===========================================================================
 **  FUNCTION      ChipInfo_GetFoundryId
 **
 **  DESCRIPTION   See ChipInfo.h
 ** ======================================================================== */

ChipInfoFoundryIdType ChipInfo_GetFoundryId(void)
{
  return ChipInfoCtxt.eFoundryId;
} /*  END ChipInfo_GetFoundryId  */

/* ===========================================================================
 **  FUNCTION      ChipInfo_GetRawChipDeviceFamily
 **
 **  DESCRIPTION   See ChipInfo.h
 ** ======================================================================== */

uint32 ChipInfo_GetRawDeviceFamily(void)
{
  return ChipInfoCtxt.nRawFamilyId;
} /* END ChipInfo_GetRawDeviceFamily */

/* ===========================================================================
 **  FUNCTION      ChipInfo_GetRawChipDeviceNumber
 **
 **  DESCRIPTION   See ChipInfo.h
 ** ======================================================================== */

uint32 ChipInfo_GetRawDeviceNumber(void)
{
  return ChipInfoCtxt.nFamilyDeviceId;
} /* END ChipInfo_GetRawDeviceFamily */

/* ===========================================================================
 **  FUNCTION      ChipInfo_GetQFPROMChipId
 **
 **  DESCRIPTION   See ChipInfo.h
 ** ======================================================================== */

ChipInfoQFPROMChipIdType ChipInfo_GetQFPROMChipId(void)
{
  return ChipInfoCtxt.nQFPROMChipId;
} /* END ChipInfo_GetQFPROMChipId */


/* ===========================================================================
 **  FUNCTION      ChipInfo_GetDisabledCPUs
 **
 **  DESCRIPTION   See ChipInfo.h
 ** ======================================================================== */
DALResult ChipInfo_GetDisabledCPUs(uint32 nCPUCluster, uint32 *pnMask)
{
  if (pnMask == NULL)
  {
    return DAL_ERROR;
  }

  if (nCPUCluster == 0 && !ChipInfoCtxt.nNumClusters)
  {
    /*
     * If this target doesn't have a binning plan, we don't know how many
     * CPU clusters there are for this target, and ChipInfo.nNumClusters
     * will be left at its default value of 0. This is the only case where
     * nNumClusters will be 0.
     *
     * Some clients call this function even if a binning plan isn't defined,
     * because they have target-agnostic code. These clients expect it to
     * return successfully instead of OUT_OF_RANGE for the first cluster (0)
     * when PTE hasn't blown fuses, since there's always at least 1 core
     * that's working (the one that's running this function).
     *
     * ChipInfoCtxt.aCPUClusters will be NULL until it's initialized by
     * the target-specific function. That function will only be defined
     * if we have a binning plan, so it'll still be NULL if we get to this
     * point. We therefore need an explicit case here, where we return
     * successfully with pnMask = "enabled/unknown", instead of
     * just accessing aCPUClusters like the general case below.
     */
    *pnMask = 0;
    return DAL_SUCCESS;
  }

  if (nCPUCluster >= ChipInfoCtxt.nNumClusters)
  {
    return DAL_ERROR_OUT_OF_RANGE_PARAMETER;
  }

  *pnMask = ChipInfoCtxt.aCPUClusters[nCPUCluster];
  return DAL_SUCCESS;
} /* END ChipInfo_GetDisabledCPUs */

/* ===========================================================================
 **  FUNCTION      ChipInfo_GetSKU
 **
 **  DESCRIPTION   See ChipInfo.h
 ** ======================================================================== */

ChipInfoResult ChipInfo_GetSKU(ChipInfoSKUInfoType *pInfo)
{
  if (!pInfo)
  {
    return CHIPINFO_ERROR_INVALID_PARAMETER;
  }

  pInfo->eSKU = ChipInfoCtxt.eSKU;
  pInfo->nProductCode = ChipInfoCtxt.nProductCode;

  if (ChipInfoCtxt.eSKU == CHIPINFO_SKU_UNKNOWN &&
      ChipInfoCtxt.nProductCode == CHIPINFO_PRODUCT_CODE_UNKNOWN)
  {
    return CHIPINFO_ERROR_NOT_SUPPORTED;
  }
  return CHIPINFO_SUCCESS;
} /* END ChipInfo_GetSKU */


/* ===========================================================================
 **  FUNCTION      ChipInfo_GetDisabledFeatures
 **
 **  DESCRIPTION   See ChipInfo.h
 ** ======================================================================== */

ChipInfoResult ChipInfo_GetDisabledFeatures(ChipInfoPartType ePart, uint32 nIdx, uint32 *pnMask)
{
  if (pnMask == NULL  || ePart == CHIPINFO_PART_UNKNOWN )
  {
    return CHIPINFO_ERROR_INVALID_PARAMETER;
  }

  if (ePart >= CHIPINFO_NUM_PARTS)
  {
    return CHIPINFO_ERROR_OUT_OF_RANGE_PARAMETER;
  }

  if (!ChipInfoCtxt.bInitComplete)
  {
    return CHIPINFO_ERROR_NOT_INITIALIZED;
  }
  
  /*
	* Currently nIdx is unused, will be used in future to address the multiple instances of the HW-IP
  */
  UNUSED(nIdx);
  
  *pnMask = ChipInfoCtxt.aDisabledFeatures[ePart];
  return CHIPINFO_SUCCESS;
} /* END ChipInfo_GetDisabledFeatures */

/* ===========================================================================
 **  FUNCTION      ChipInfo_IsPartDisabled
 **
 **  DESCRIPTION   See ChipInfo.h
 ** ======================================================================== */

ChipInfoResult ChipInfo_IsPartDisabled(ChipInfoPartType ePart, uint32 nIdx, boolean *pnMask)
{
  if (pnMask == NULL || ePart == CHIPINFO_PART_UNKNOWN)
  {
    return CHIPINFO_ERROR_INVALID_PARAMETER;
  }
  
  /*
	* Currently nIdx is unused, will be used in future to address the multiple instances of the HW-IP
  */
  UNUSED(nIdx);
  
  if (ePart >= CHIPINFO_NUM_PARTS)
  {
    return CHIPINFO_ERROR_OUT_OF_RANGE_PARAMETER  ;
  }

  if (!ChipInfoCtxt.bInitComplete)
  {
    return CHIPINFO_ERROR_NOT_INITIALIZED;
  }

  *pnMask = ChipInfoCtxt.aDisabledFeatures[ePart]  & 0x1 ? TRUE : FALSE;
  return CHIPINFO_SUCCESS;
} /* END ChipInfo_IsPartDisabled */