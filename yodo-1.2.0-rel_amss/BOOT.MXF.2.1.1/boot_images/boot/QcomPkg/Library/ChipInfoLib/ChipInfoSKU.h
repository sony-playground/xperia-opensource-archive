#ifndef CHIPINFO_SKU_H
#define CHIPINFO_SKU_H

/* =====================================================================

 FILE:  ChipInfoSku.h

 DESCRIPTION: XBLLoader/SBL-specific internal header file for ChipInfo
              that defines a common interface for SKU processing.

              This is its own header that's visible to both common and
              target-specific code, to allow  target specific SKU
              handling for the few target that need it.
 =======================================================================

       Copyright (c) 2021, 2022 QUALCOMM Technologies Incorporated.
                       All Rights Reserved.
              QUALCOMM Proprietary and Confidential.
 =======================================================================

 $Header: //components/dev/core.boot/6.0/vpopuri.core.boot.6.0.cr3077478_ChipInfo_GetSku_20211214/QcomPkg/Library/ChipInfoLib/ChipInfoSKU.h#1 $
 $DateTime: 2021/12/14 16:43:12 $
 $Author: vpopuri $

 =====================================================================*/

/*======================================================================
 Includes
 =====================================================================*/
#include "ChipInfoDefs.h"
#include <stdint.h>
#include "ChipInfoLocal.h"


/*======================================================================
 Type definitions
 =====================================================================*/

/*
 * Container for all product management information for a specific
 * product family.
 */
typedef struct ChipInfoProductManagementDataType
{
  ChipInfoFamilyType eFamily;
  ChipInfoVersionType nMinVersion;
  ChipInfoVersionType nMaxVersion;
  ChipInfoSKUType SKU;
  uint32_t nNumPartMarketingDataEntries;
  ChipInfoPartMarketingDataType **PartMarketingData;
} ChipInfoProductManagementDataType;


/*======================================================================
 Functions
 =====================================================================*/

/*
 * Read SKU_ID and P_CODE fuses, translate them to logical value,
 * return them in the corresponding parameter.
 */
void ChipInfo_ReadSKU(ChipInfoFeatureCodeType *nSkuId, uint32_t *nProductCode);

/*
 * Stores product marketing data for the current chip in ChipInfoCtxt.
 */
void ChipInfo_UpdatePartMarketingData(ChipInfoCtxtType *pCtxt);

#endif /* CHIPINFO_SKU_H */
