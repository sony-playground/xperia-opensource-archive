#ifndef CHIPINFOLOCAL_H
#define CHIPINFOLOCAL_H

/*==========================================================================

FILE:   ChipInfoLocal.h

DESCRIPTION:  Internal function and data structure declarations for ChipInfo
              shared across all images.

PUBLIC CLASSES:  Not Applicable

============================================================================
       Copyright (c) 2016-2017, 2022, 2023 QUALCOMM Technologies Inc.All rights reserved.
============================================================================

  $Header: //components/rel/core.boot/6.0/QcomPkg/Library/ChipInfoLib/ChipInfoLocal.h#5 $
  $DateTime: 2023/05/11 20:39:31 $
  $Author: pwbldsvc $

==========================================================================*/

#include "ChipInfo.h"
#include "ChipInfoDefs.h"
#include <stdint.h>
#include <stdbool.h>

/* -----------------------------------------------------------------------
**                           MACROS
** ----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------
**                           TYPES
** ----------------------------------------------------------------------- */

/**
 * ChipInfoType
 *
 * Container for all chip info
 */
typedef struct
{
  bool                      bInitComplete;        /*  Driver has been initialized */
  uint32_t                  nRawPartNum;          /*  JTAG ID/Device Number */
  ChipInfoIdType              eChipInfoId;          /*  Sequential ID, unique across all chips */
  ChipInfoVersionType         nVersion;             /*  Major and Minor versions   */
  uint32_t                  nRevNumber;           /*  HW Revision number. e.g. 0 = v1.0, 1 = v1.1, 2 = v2.0 */
  ChipInfoFamilyType          eFamilyId;            /*  Internal ChipInfo family (not architectural family)  */
  uint32_t                  nFamilyDeviceId;      /*  Device ID within this family, unique within the family */
  uint32_t                  nRawFamilyId;         /*  Architectural family number  */
  ChipInfoFoundryIdType       eFoundryId;           /*  The foundry in which the chip was manufactured  */
  ChipInfoSerialNumType       nSerialNum;           /*  Unique (within chip family) serial number  */
  ChipInfoQFPROMChipIdType    nQFPROMChipId;        /*  Chip ID read from QFPROM fuses  */
  ChipInfoModemType           nModemSupported;      /*  Modem hardware is/isnt' supported on this platform */
  char                        szChipIdString[CHIPINFO_MAX_ID_LENGTH]; /*  The chip's name as a string, e.g. "MSM8998" */
  uint32_t                  nNumClusters;
  uint32_t                 *aCPUClusters;         /*  Bitmasks of disabled CPU cores for each of nClusters clusters */
  uint32_t                  aDisabledFeatures[CHIPINFO_NUM_PARTS]; /*  Parts specific fuse data for supported parts (cam/video/modem etc) */
  ChipInfoSKUIdType         eSKU;                 /*  SKU enum for this device */
  uint32_t                  nProductCode;         /*  P_CODE for this device */
} ChipInfoCtxtType;



#endif /* CHIPINFOLOCAL_H */
