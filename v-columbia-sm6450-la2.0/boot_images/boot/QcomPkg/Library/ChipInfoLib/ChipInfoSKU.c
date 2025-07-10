/*======================================================================
  @file ChipInfoSKU.c

  Logic for translating SKU information from fuses into values that can
  be returned by ChipInfo_GetSKU.

========================================================================
        Copyright (c) 2021 Qualcomm Technologies, Inc.
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


/*======================================================================
      Prototypes
======================================================================*/
static ChipInfoSKUIdType ChipInfo_TranslateSKUId(const uint32_t nSKUId);
static uint32_t ChipInfo_TranslatePCode(const uint32_t nPCode);
static void ChipInfo_ReadSKU_Generic(ChipInfoSKUIdType *eSKU, uint32_t *nProductCode);
static void ChipInfo_ReadSKU_NotSupported(ChipInfoSKUIdType *eSKU, uint32_t *nProductCode);


/*======================================================================
      Functions
======================================================================*/
/*
 * See ChipInfoSKU.h
 */
void ChipInfo_ReadSKU(ChipInfoSKUIdType *eSKU, uint32_t *nProductCode)
{
  if (!HWIO_ADDR(CHIPINFO_SKU_ID_REG) || !HWIO_ADDR(CHIPINFO_P_CODE_REG))
  {
    ChipInfo_ReadSKU_NotSupported(eSKU, nProductCode);
  }
  else
  {
    ChipInfo_ReadSKU_Generic(eSKU, nProductCode);
  }
}


/*
 * Stubbed version of ChipInfo_ReadSKU for targets that don't support
 * this feature
 */
static inline void ChipInfo_ReadSKU_NotSupported(ChipInfoSKUIdType *eSKU, uint32_t *nProductCode)
{
  *eSKU = CHIPINFO_SKU_UNKNOWN;
  *nProductCode = CHIPINFO_PRODUCT_CODE_UNKNOWN;
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
static inline void ChipInfo_ReadSKU_Generic(ChipInfoSKUIdType *eSKU, uint32_t *nProductCode)
{
  uint32_t nVal;
  nVal = HWIO_INF(CHIPINFO_SKU_ID_REG, SKU_ID);
  *eSKU = ChipInfo_TranslateSKUId(nVal);
  nVal = HWIO_INF(CHIPINFO_P_CODE_REG, P_CODE);
  *nProductCode = ChipInfo_TranslatePCode(nVal);
}


/*
 * Translate a SKU_ID fuse value into a ChipInfoSKUIdType enum.
 */
ChipInfoSKUIdType ChipInfo_TranslateSKUId(const uint32_t nRawSKUID)
{
  /*
   * Enum values are a simple 2's complement of the fuse value.
   * However, since this is casting to an enum, we should verify
   * that it's within the range of known enums.
   */
  uint8_t nSKUId = (uint8_t)nRawSKUID;
  uint8_t nTwosComplement = ~nSKUId + 1;
  bool bIsExternalSKU = (nTwosComplement >= CHIPINFO_FIRST_GENERAL_SKU) &&
                        (nTwosComplement <= CHIPINFO_LAST_GENERAL_SKU);
  bool bIsInternalSKU = (nTwosComplement >= CHIPINFO_FIRST_Y_SKU) &&
                        (nTwosComplement <= CHIPINFO_LAST_Y_SKU);
  if (bIsExternalSKU || bIsInternalSKU)
  {
      return (ChipInfoSKUIdType)nTwosComplement;
  }
  return CHIPINFO_SKU_UNKNOWN;
}


/*
 * Translate a P_CODE fuse value into a product_code uint32_t.
 */
uint32_t ChipInfo_TranslatePCode(const uint32_t nRawPCode)
{
  /*
   * Basic 1's complement.
   * Range of valid values is target-specific, but is limited to
   * 1 byte. While it's technically feasible to further validate
   * nPCode, it's:
   *  a. not very maintainable, since each target must reimplement
   *      this function to check the set of valid PCodes for each project.
   *      Every P_CODE addition would require an update to this new
   *      target-specifc function.
   *  b. undocumented at the moment. All we know is that the fuse
   *      contains a 1's complement-able 8-bit integer. To validate
   *      inputs, we'd need to know all the valid product codes.
   *
   * It might be doable once ChipInfo starts using DTB, but the extra
   * validation isn't worth the effort right now.
   */
   uint8_t nPCode = (uint8_t)nRawPCode;
    if (nPCode == 0)
    {
        return CHIPINFO_PRODUCT_CODE_UNKNOWN;
    }
    return (uint32_t)(~nPCode);
}
