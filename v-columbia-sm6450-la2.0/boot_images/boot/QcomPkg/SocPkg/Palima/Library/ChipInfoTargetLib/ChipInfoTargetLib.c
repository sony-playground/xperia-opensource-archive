/*==============================================================================
  @file ChipInfoTargetLib.c

  ChipInfo functions for the XBL Loader ChipInfo Driver.

================================================================================
        Copyright (c) 2017, 2019 Qualcomm Technologies, Inc.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
================================================================================

  $Header: //components/rel/core.boot/6.0/QcomPkg/SocPkg/Palima/Library/ChipInfoTargetLib/ChipInfoTargetLib.c#1 $
  $DateTime: 2021/09/12 20:53:48 $
  $Author: pwbldsvc $

==============================================================================*/

/*==============================================================================
      Include Files
==============================================================================*/
#include "ChipInfoHWIO.h"
#include "ChipInfoLocal.h"
#include "HALhwio.h"

/*==============================================================================
**  Macros
**============================================================================*/

/**
 * Chipset-specific numbers of cores and clusters.
 * CHIPINFO_PARTIALGOODS_NUM_CLUSTERS is different from
 * ChipInfoDefs.h/CHIPINFO_MAX_CPU_CLUSTERS since the latter is a global
 * maximum across all supported chips, while the former only applies to
 * the current chip.
 */
#define CHIPINFO_PARTIALGOODS_NUM_CLUSTERS                    1

/**
 * The PARTIAL_GOOD fuses contain a bitmask of all the defective bins,
 * with bit0 = Bin A, bit1 = Bin B, etc. If Bins A and B are both defective,
 * the fuses would hold 0b0011. Bins A through D are supported.
 * This macro expects uppercase letters only. It will be used to mask the
 * contents of the PARTIAL_GOOD fuses to identify the blown fuses.
 */
#define CHIPINFO_PARTIALGOODS_BIN(x)                          0x1 << ((char)(x) - 'A')

/*
 * Sub bin fuses are in QFPROM_CORR_PTE_ROW1_LSB[1:20], 5 bits per sub-bin.
 * NOTE: bit 0 of this fuse is not sub-bining related.
 */
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_SUB_BINA_BMSK           0x0000003e
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_SUB_BINA_SHFT           1
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_SUB_BINB_BMSK           0x000007c0
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_SUB_BINB_SHFT           6
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_SUB_BINC_BMSK           0x0000f800
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_SUB_BINC_SHFT           11
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_SUB_BIND_BMSK           0x001f0000
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_SUB_BIND_SHFT           16

/*
 * Macro to check if sub-binning is enabled for the specified bin.
 *
 */
#define CHIPINFO_SUB_BINNING_ENABLED(val)                     ((val) & (0x1 << 4))


/**
 * Statically allocate the CPU clusters array so we don't need to do dynamic
 * allocation and have a dependency on heap.
 */
#define CHIPINFO_CLUSTER0_GOLD_PLUS_CORES_MASK   0x1
#define CHIPINFO_CLUSTER0_GOLD_PLUS_CORES_SHFT   7
#define CHIPINFO_CLUSTER0_GOLD_CORES_MASK        0x7
#define CHIPINFO_CLUSTER0_GOLD_CORES_SHFT        4
#define CHIPINFO_CLUSTER0_SILVER_CORES_MASK      0xE /* Silver-0 can't be defective. */
#define CHIPINFO_CLUSTER0_SILVER_CORES_SHFT      0
#define _CHIPINFO_MASK_CPU_CORES(c, x)    \
  CHIPINFO_CLUSTER##c##_##x##_CORES_MASK << CHIPINFO_CLUSTER##c##_##x##_CORES_SHFT
#define CHIPINFO_MASK_CLUSTER0(x) _CHIPINFO_MASK_CPU_CORES(0, x)


uint32 aCPUClusters[CHIPINFO_PARTIALGOODS_NUM_CLUSTERS] = { 0 };


/*==============================================================================
**  Functions
**============================================================================*/

/*==============================================================================
  FUNCTION      ChipInfo_InitChipset

  DESCRIPTION   Chipset-specific initialization sequences, including reading
                PTE fuses to determine which parts are defective

==============================================================================*/
void ChipInfo_InitChipset(ChipInfoCtxtType *pChipInfoCtxt)
{
  if (pChipInfoCtxt == NULL)
  {
    return;
  }

  pChipInfoCtxt->nNumClusters = CHIPINFO_PARTIALGOODS_NUM_CLUSTERS;
  pChipInfoCtxt->aCPUClusters = aCPUClusters;

  /*
   * Binning plan is not yet defined.
   * NOTE: A quick perusal at the fuse assignments shows that PARTIAL_GOOD is split
   *      across two fuses at the moment. This isn't great, but isn't needed right
   *      now either. The fuse assignemnts have not yet been reviewed with PTE
   *      so this isn't yet confirmed.
   */
}
