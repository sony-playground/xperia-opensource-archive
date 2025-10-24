/*======================================================================
  @file ChipInfoSKU.c

  Logic for translating SKU information from fuses into values that can
  be returned by ChipInfo_GetSKU.

========================================================================
        Copyright (c) 2021, 2022 Qualcomm Technologies, Inc.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
========================================================================

  $Header: //components/dev/core.boot/6.0/vpopuri.core.boot.6.0.cr3077478_ChipInfo_GetSku_20211214/QcomPkg/Library/ChipInfoLib/ChipInfoSKU.c#1 $
  $DateTime: 2021/12/14 16:43:12 $
  $Author: vpopuri $

======================================================================*/

/*======================================================================
      Include Files
======================================================================*/
#include <stdint.h>
#include <stdbool.h>
#include "HALhwio.h"
#include "ChipInfo.h"
#include "ChipInfoDefs.h"
#include "ChipInfoSKU.h"
#include "ChipInfoHWIO.h"
#include "ChipInfoLoader.h"

/*======================================================================
      Macros
======================================================================*/
/*
 * These macors are only useful until we get the set of FEATURE_CODEs
 * supported for each product, since that's what we really want to check:
 * we want to ensure that the value we read from the fuse is valid for
 * the product we're running on. These macros are a stopgap sanity check
 * until we have that level of granularity in ChipInfo.
 *
 * They shouldn't be part of the interface since they're only
 * used for fuse validation, and they'll be removed once SKU information
 * is generated. They should move into an internal generated
 * header, or into the generated file that will support SKU->PartName
 * mappings with a function to get these limits.
 *
 * While these values might arguably be useful to CPT, CPT has a better
 * source of truth: QPMD.
 */

#define CHIPINFO_FIRST_GENERAL_FEATURE_CODE CHIPINFO_FEATURE_CODE_AA
#define CHIPINFO_LAST_GENERAL_FEATURE_CODE CHIPINFO_FEATURE_CODE_AH
#define CHIPINFO_FIRST_Y_FEATURE_CODE CHIPINFO_FEATURE_CODE_Y0
#define CHIPINFO_LAST_Y_FEATURE_CODE CHIPINFO_FEATURE_CODE_YF
#define CHIPINFO_Y_FEATURE_CODE_BASE (CHIPINFO_FIRST_Y_FEATURE_CODE - 1)
#define CHIPINFO_P_CODE_MAX CHIPINFO_P_CODE_7

/*
 * These macros shouldn't be part of the interface because I don't
 * believe that they'll always be disallowed. While these PCodes might
 * be confused with others depending on the font (I ~ 1 and Z ~ 2),
 * other ambiguous PCodes are still valid, e.g.:
 *  - O ~ 0,
 *  - D,Q ~ 0
 *  - S ~ 5
 *  - B ~ 8
 *  - G ~ 6
 * I suspect that these will become project-specific. It's trivial to
 * add disallowed characters as a generator option, so these macros
 * should move into the same header as the FEATURE_CODE ones and be
 * exposed to this file through an internal function.
 */
#define CHIPINFO_DISALLOWED_P_CODE_I 237
#define CHIPINFO_DISALLOWED_P_CODE_Z 231

#define SIZEOF_ARRAY(arr) (sizeof((arr))/sizeof((arr)[0]))


/*======================================================================
      Prototypes
======================================================================*/
static ChipInfoFeatureCodeType ChipInfo_TranslateSKUIdToFeatureCode(uint32_t nSKUId);
static uint32_t ChipInfo_TranslatePCode(uint32_t ePCode);
static void ChipInfo_ReadSKU_Generic(ChipInfoFeatureCodeType *eFeatureCode, ChipInfoPCodeType *ePCode);
static void ChipInfo_ReadSKU_NotSupported(ChipInfoFeatureCodeType *eFeatureCode, ChipInfoPCodeType *ePCode);

/*======================================================================
      Functions
======================================================================*/
/*
 * See ChipInfoSKU.h
 */
void ChipInfo_ReadSKU(ChipInfoFeatureCodeType *eFeatureCode, ChipInfoPCodeType *ePCode)
{
  if (!HWIO_ADDR(CHIPINFO_SKU_ID_REG) || !HWIO_ADDR(CHIPINFO_P_CODE_REG))
  {
    ChipInfo_ReadSKU_NotSupported(eFeatureCode, ePCode);
  }
  else
  {
    ChipInfo_ReadSKU_Generic(eFeatureCode, ePCode);
  }
}

/*
 * Stubbed version of ChipInfo_ReadSKU for targets that don't support
 * this feature
 */
static inline void ChipInfo_ReadSKU_NotSupported(ChipInfoFeatureCodeType *eFeatureCode, ChipInfoPCodeType *ePCode)
{
  *eFeatureCode = CHIPINFO_FEATURE_CODE_UNKNOWN;
  *ePCode = CHIPINFO_P_CODE_UNKNOWN;
}

/*
 * Target-agnostic version of ChipInfo_ReadSKU.
 * If this feature isn't supported at all for some target, simply define
 * a 0x0 BMSK and SHFT for the SKU_ID and P_CODE regs in ChipInfoHWIO.h.
 * This results in a write of 0x0 to each address.
 *
 * If this feature is supported on a target but the fuses don't follow
 * the standard format, define a chipset-specific version of this
 * function with the special handling.
 */
static inline void ChipInfo_ReadSKU_Generic(ChipInfoFeatureCodeType *eFeatureCode, ChipInfoPCodeType *ePCode)
{
  uint32_t nVal;
  nVal = HWIO_INF(CHIPINFO_SKU_ID_REG, SKU_ID);
  *eFeatureCode = ChipInfo_TranslateSKUIdToFeatureCode(nVal);
  nVal = HWIO_INF(CHIPINFO_P_CODE_REG, P_CODE);
  *ePCode = ChipInfo_TranslatePCode(nVal);
}

/*
 * Translate a SKU_ID fuse value into a ChipInfoFeatureCodeType enum.
 */
ChipInfoFeatureCodeType ChipInfo_TranslateSKUIdToFeatureCode(uint32_t nRawSKUID)
{
  /*
   * External feature codes grow towards 0:
   *  SKU_ID fuse   meaning     enum value
   *  0x00          undefined   UNKNOWN (0)
   *  0xff          AA          1
   *  0xfe          AB          2
   *  0xfd          AC          3
   *  0xfc          AD          4
   *  ...
   *
   * Enum values are the 8-bit 2's complement of the fuse value.
   * However, the enums themselves are 32-bits, but only the bottom
   * few bits are defined.
   */
  bool bIsExternalSKU = false, bIsInternalSKU = false;
  uint8_t nTwosComplement = (uint8_t)(~nRawSKUID + 1);
  bIsExternalSKU = (nTwosComplement >= CHIPINFO_FIRST_GENERAL_FEATURE_CODE) &&
                   (nTwosComplement <= CHIPINFO_LAST_GENERAL_FEATURE_CODE);
  if (bIsExternalSKU)
  {
    return (ChipInfoFeatureCodeType)nTwosComplement;
  }

  /*
   * Internal feature codes grow upwards:
   *  SKU_ID fuse   meaning     enum value
   *  0x00          undefined   UNKNOWN (0)
   *  0x01          Y0          0xf1
   *  0x02          Y2          0xf2
   *  0x03          Y3          0xf3
   *  ...
   *  0x0e          YD          0xff
   *  0x0f          YE          0x100
   *
   * So enum value = fuse_value + 0xf0.
   * SKU_ID fuse values are still 8 bits.
   * FeatureCodes are > 8 bits.
   */
  nRawSKUID += CHIPINFO_Y_FEATURE_CODE_BASE;
  bIsInternalSKU = (nRawSKUID >= CHIPINFO_FIRST_Y_FEATURE_CODE) &&
                   (nRawSKUID <= CHIPINFO_LAST_Y_FEATURE_CODE);
  if (bIsInternalSKU)
  {
    return (ChipInfoFeatureCodeType)nRawSKUID;
  }
  return CHIPINFO_FEATURE_CODE_UNKNOWN;
}

/*
 * Translate a P_CODE fuse value into a ChipInfoFeatureCodeType.
 */
ChipInfoFeatureCodeType ChipInfo_TranslatePCode(uint32_t nRawPCode)
{
  /*
   *  Fuse          P_Code Meaning    Enum Value
   *  0x00          UNDEFINED         0
   *  0xff (255)    0                 1
   *  0xfe (254)    1                 2
   *  0xfd (253)    2                 3
   *  ...
   *  0xf6 (246)    9                 10
   *  0xf5 (245)    A                 11
   *  0xf4 (244)    B                 12
   *  ...
   *  0xed (237)    I                 DISALLOWED (actually 19)
   *  ...
   *  0xe7 (231)    O                 DISALLOWED (actually 25)
   *  ...
   *  0xdc (220)    Z                 36
   *
   * enum value = 256 - fuse value, or equivalently,
   * enum values are the 8-bit 2's complement of the fuse values,
   * with a handful of "disallowed" exceptions.
   */
  bool bIsDisallowedPCode = (nRawPCode == CHIPINFO_DISALLOWED_P_CODE_I ||
                             nRawPCode == CHIPINFO_DISALLOWED_P_CODE_Z);
  if (!nRawPCode || bIsDisallowedPCode)
  {
    return CHIPINFO_P_CODE_UNKNOWN;
  }

  nRawPCode = (uint8_t)(~nRawPCode + 1);
  if (nRawPCode > CHIPINFO_P_CODE_MAX)
  {
    return CHIPINFO_P_CODE_UNKNOWN;
  }

  /*
   * TODO: Chipset-specific PCode validation based on QPMD data
   */
  return (ChipInfoPCodeType)nRawPCode;
}


/*
 * Return the first ProductManagementData entry that matches the current
 * chip family, version, and SKU.
 */
static inline ChipInfoProductManagementDataType *ChipInfo_GetProductManagementData
(
  ChipInfoCtxtType *pCtxt
)
{
  ChipInfoFamilyType eFamily = pCtxt->eFamilyId;
  ChipInfoFeatureCodeType eFeatureCode = pCtxt->eFeatureCode;
  ChipInfoPCodeType ePCode = pCtxt->ePCode;
  ChipInfoVersionType nVersion = pCtxt->nVersion;

  ChipInfoBSPType *pBSP = ChipInfo_GetBSPData();
  ChipInfoProductManagementDataType *pData = NULL;
  bool MatchesFamily;
  bool MatchesAllVersions, MatchesVersionRange;
  bool MatchesSKU, MatchesAllSKUs;

  for (int product = 0; product < pBSP->nNumFamiliesWithProductManagementData; product++)
  {
    pData= &pBSP->aProductManagementData[product];

    MatchesFamily = eFamily == pBSP->aProductManagementData[product].eFamily;
    MatchesAllVersions = !pData->nMinVersion && !pData->nMaxVersion;
    MatchesVersionRange = pData->nMinVersion <= nVersion && pData->nMaxVersion > nVersion;
    MatchesSKU = pData->SKU.eFeatureCode == eFeatureCode && pData->SKU.ePCode == ePCode;
    MatchesAllSKUs = pData->SKU.eFeatureCode == CHIPINFO_FEATURE_CODE_UNKNOWN &&
                    pData->SKU.ePCode == CHIPINFO_P_CODE_UNKNOWN;

    if (MatchesFamily &&
        (MatchesAllVersions || MatchesVersionRange) &&
        (MatchesSKU || MatchesAllSKUs))
    {
      return pData;
    }
  }
  return NULL;
}

/*
 * De-obfuscates marketing name strings in place.
 * Since this modifies the source data, this function must be called
 * once per PartMarketingData entry (or an odd number of times).
 *
 * This obfuscation isn't meant to be cryptographically secure. All it
 * needs to do is prevent the strings from showing up if someone runs
 * `strings` on the XBL elf.
 */
static inline void ChipInfo_DeobfuscateMarketingData
(
  ChipInfoPartMarketingDataType *pPartData
)
{
  /*
   * Psuedorandom obfuscation key. Same length as the strings being
   * deobfuscated. Marketing strings in the BSP were obfuscated wtih an
   * XOR cipher. This function repeats the XOR to restore plaintext.
   */
  const uint8_t key[CHIPINFO_MAX_PART_MARKETING_NAME_LENGTH] =
  {
    0x8e, 0xc6, 0x65, 0x40, 0x97, 0x02, 0x35, 0x90,
    0x60, 0xd1, 0xf9, 0xfb, 0x3c, 0xb9, 0xea, 0xa0,
    0x76, 0xe4, 0xe4, 0x2c, 0xe4, 0x16, 0xba, 0x11,
    0xcc, 0x4d, 0x7c, 0xf1, 0x82, 0x1a, 0x79, 0x0a
  };

  switch(pPartData->ePart)
  {
    case CHIPINFO_PART_GPU:
      for (uint8_t byte = 0; byte < sizeof(key); byte++)
      {
        pPartData->GPUData.szName[byte] ^= key[byte];
      }
      return;

    default:
      return;
  }
}

void ChipInfo_UpdatePartMarketingData(ChipInfoCtxtType *pCtxt)
{
  ChipInfoProductManagementDataType *pProduct = NULL;
  ChipInfoPartMarketingDataType **pData = NULL;

  pProduct = ChipInfo_GetProductManagementData(pCtxt);
  if (!pProduct || !pProduct->PartMarketingData || !pProduct->nNumPartMarketingDataEntries)
  {
    return;
  }

  pData = pProduct->PartMarketingData;
  for (int i = 0; i < pProduct->nNumPartMarketingDataEntries; i++)
  {
    ChipInfo_DeobfuscateMarketingData(pData[i]);
  }

  pCtxt->pPartMarketingData = pData;
  pCtxt->nNumPartsWithMarketingData = pProduct->nNumPartMarketingDataEntries;
}

