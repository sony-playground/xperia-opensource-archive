/*==============================================================================
  @file ChipInfoBSP.c

  ChipInfo BSP data.

================================================================================
        Copyright (c) 2016-2022 Qualcomm Technologies, Inc.
               All Rights Reserved.
        Confidential and Proprietary - Qualcomm Technologies, Inc
================================================================================

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/ChipInfoLib/ChipInfoBSP.c#4 $
  $DateTime: 2022/11/10 03:58:06 $
  $Author: pwbldsvc $

==============================================================================*/

/*==============================================================================
      Include Files
==============================================================================*/
#include "comdef.h"
#include "ChipInfoLocal.h"
#include "ChipInfoLoader.h"
#include "ChipInfoSKU.h"

/*==============================================================================
      Data Definitons
==============================================================================*/
//#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

/*==============================================================================
      Data Definitons
==============================================================================*/

/*
 * ChipInfoDataLUT
 *
 * Array of chip id strings, chip IDs, part numbers, and modem support.
 *
 * This table only needs to contain mappings for targets supported out of this warehouse.
 */
static const ChipInfoDataLUTType ChipInfoDataLUT[] =
{
  { "UNKNOWN",            CHIPINFO_ID_UNKNOWN,              CHIPINFO_PARTNUM_UNKNOWN,           CHIPINFO_MODEM_UNKNOWN    },
  { "SM_KAILUA",          CHIPINFO_ID_SM_KAILUA,            CHIPINFO_PARTNUM_SM_KAILUA,         CHIPINFO_MODEM_SUPPORTED  },
  { "SMP_KAILUA",         CHIPINFO_ID_SMP_KAILUA,           CHIPINFO_PARTNUM_SMP_KAILUA,        CHIPINFO_MODEM_UNKNOWN    },
  { "SXR_AURORA",         CHIPINFO_ID_SXR_AURORA,           CHIPINFO_PARTNUM_SXR_AURORA,        CHIPINFO_MODEM_UNKNOWN    },
  { "QRU_LASSEN",         CHIPINFO_ID_QRU_LASSEN,           CHIPINFO_PARTNUM_QRU_LASSEN,        CHIPINFO_MODEM_SUPPORTED  },
  { "QDU_LASSEN",         CHIPINFO_ID_QDU_LASSEN,           CHIPINFO_PARTNUM_QDU_LASSEN,        CHIPINFO_MODEM_SUPPORTED  },
  { "QDU1010_LASSEN",     CHIPINFO_ID_QDU1010_LASSEN,       CHIPINFO_PARTNUM_QDU1010_LASSEN,    CHIPINFO_MODEM_SUPPORTED  },
  { "QRU1032_LASSEN",     CHIPINFO_ID_QRU1032_LASSEN,       CHIPINFO_PARTNUM_QRU1032_LASSEN,    CHIPINFO_MODEM_SUPPORTED  },
  { "QRU1052_LASSEN",     CHIPINFO_ID_QRU1052_LASSEN,       CHIPINFO_PARTNUM_QRU1052_LASSEN,    CHIPINFO_MODEM_SUPPORTED  },
  { "QRU1062_LASSEN",     CHIPINFO_ID_QRU1062_LASSEN,       CHIPINFO_PARTNUM_QRU1062_LASSEN,    CHIPINFO_MODEM_SUPPORTED  },
  { "SXR_HALLIDAY",       CHIPINFO_ID_SXR_HALLIDAY,         CHIPINFO_PARTNUM_SXR_HALLIDAY,      CHIPINFO_MODEM_UNKNOWN    },
  { "SM_LANAI",           CHIPINFO_ID_SM_LANAI,             CHIPINFO_PARTNUM_SM_LANAI,          CHIPINFO_MODEM_SUPPORTED  },
  { "SMP_LANAI",          CHIPINFO_ID_SMP_LANAI,            CHIPINFO_PARTNUM_SMP_LANAI,         CHIPINFO_MODEM_UNKNOWN    },
  { "SCP_HAMOA",          CHIPINFO_ID_SCP_HAMOA,            CHIPINFO_PARTNUM_SCP_HAMOA,         CHIPINFO_MODEM_UNKNOWN    },
  { "SDX_PINNACLES",      CHIPINFO_ID_SDX_PINNACLES,        CHIPINFO_PARTNUM_SDX_PINNACLES,     CHIPINFO_MODEM_SUPPORTED  },
  { "SDX_PINNACLES_M",    CHIPINFO_ID_SDX_PINNACLES_M,      CHIPINFO_PARTNUM_SDX_PINNACLES_M,   CHIPINFO_MODEM_SUPPORTED  },
  { "SA_PINNACLES",       CHIPINFO_ID_SA_PINNACLES,         CHIPINFO_PARTNUM_SA_PINNACLES,      CHIPINFO_MODEM_SUPPORTED  },
  { "SA_PINNACLES_L",     CHIPINFO_ID_SA_PINNACLES_L,       CHIPINFO_PARTNUM_SA_PINNACLES_L,    CHIPINFO_MODEM_SUPPORTED  },
  { "SSG_AURORA",         CHIPINFO_ID_SSG_AURORA,           CHIPINFO_PARTNUM_SSG_AURORA,        CHIPINFO_MODEM_UNKNOWN    },
  { "SM_KAPITI",          CHIPINFO_ID_SM_KAPITI,            CHIPINFO_PARTNUM_SM_KAPITI,         CHIPINFO_MODEM_SUPPORTED  },
  { "SDX_KUNO_SINGLEDIE", CHIPINFO_ID_SDX_KUNO_SINGLEDIE,   CHIPINFO_PARTNUM_SDX_KUNO_SINGLEDIE, CHIPINFO_MODEM_SUPPORTED  },
  { "SDX_KUNO_HYBRID",    CHIPINFO_ID_SDX_KUNO_HYBRID,      CHIPINFO_PARTNUM_SDX_KUNO_HYBRID,    CHIPINFO_MODEM_SUPPORTED  },
  { "SSG2_AURORA",        CHIPINFO_ID_SSG2_AURORA,          CHIPINFO_PARTNUM_SSG2_AURORA,       CHIPINFO_MODEM_UNKNOWN    },
  { "SG_KAILUA",          CHIPINFO_ID_SG_KAILUA,            CHIPINFO_PARTNUM_SG_KAILUA,         CHIPINFO_MODEM_SUPPORTED  },
  { "SGP_KAILUA",         CHIPINFO_ID_SGP_KAILUA,           CHIPINFO_PARTNUM_SGP_KAILUA,        CHIPINFO_MODEM_UNKNOWN    },
  { "QCS_KAILUA",         CHIPINFO_ID_QCS_KAILUA,           CHIPINFO_PARTNUM_QCS_KAILUA,        CHIPINFO_MODEM_UNKNOWN    },
  { "QCM_KAILUA",         CHIPINFO_ID_QCM_KAILUA,           CHIPINFO_PARTNUM_QCM_KAILUA,        CHIPINFO_MODEM_SUPPORTED  },
};


/*
 * ChipInfoArchFamilyArray
 *
 * Array of default chip ID and family IDs to use if the JTAG ID is not recognized.
 * The product family can be identified using TCSR_SOC_HW_VERSION, which is defined
 * in RTL and is therefore always available. This is typically only needed when
 * parts haven't yet been fused (e.g. RUMI or early during silicon bring up).
 *
 * This array only needs to contain information for product families being supported
 * from this warehouse.
 */
static const ChipInfoArchFamilyDataType ChipInfoArchFamilyArray[] =
{
  { CHIPINFO_ARCH_FAMILY_UNKNOWN,      0,  CHIPINFO_FAMILY_UNKNOWN,     CHIPINFO_ID_UNKNOWN       },
  { CHIPINFO_ARCH_FAMILY_WILDCAT,      3,  CHIPINFO_FAMILY_KAILUA,      CHIPINFO_ID_SM_KAILUA     },
  { CHIPINFO_ARCH_FAMILY_WILDCAT,      6,  CHIPINFO_FAMILY_AURORA,      CHIPINFO_ID_SXR_AURORA    },
  { CHIPINFO_ARCH_FAMILY_WILDCAT,      7,  CHIPINFO_FAMILY_LASSEN,      CHIPINFO_ID_QRU_LASSEN    },
  { CHIPINFO_ARCH_FAMILY_WILDCAT,      9,  CHIPINFO_FAMILY_HAMOA,       CHIPINFO_ID_SCP_HAMOA     },
  { CHIPINFO_ARCH_FAMILY_WILDCAT,     10,  CHIPINFO_FAMILY_HALLIDAY,    CHIPINFO_ID_SXR_HALLIDAY  },
  { CHIPINFO_ARCH_FAMILY_WILDCAT,     11,  CHIPINFO_FAMILY_PINNACLES,   CHIPINFO_ID_SDX_PINNACLES },
  { CHIPINFO_ARCH_FAMILY_WILDCAT,     12,  CHIPINFO_FAMILY_LANAI,       CHIPINFO_ID_SM_LANAI      },
  { CHIPINFO_ARCH_FAMILY_WILDCAT,     13,  CHIPINFO_FAMILY_KAPITI,      CHIPINFO_ID_SM_KAPITI     },
  { CHIPINFO_ARCH_FAMILY_WILDCAT,     13,  CHIPINFO_FAMILY_KUNO,        CHIPINFO_ID_SDX_KUNO_SINGLEDIE },
};


static ChipInfoPartMarketingDataType ChipInfo_MarketingData_Adreno740 =
{
  .ePart = CHIPINFO_PART_GPU,
  .GPUData = {
    .nChipID = 0x43050a00,    // TODO Same as vulkan ID?
    .nVulkanID = 0x43050a00,
    .szName =
    {
      0xcf, 0xa2, 0x17, 0x25, 0xf9, 0x6d, 0x02, 0xa4,
      0x50, 0xd1, 0xf9, 0xfb, 0x3c, 0xb9, 0xea, 0xa0,
      0x76, 0xe4, 0xe4, 0x2c, 0xe4, 0x16, 0xba, 0x11,
      0xcc, 0x4d, 0x7c, 0xf1, 0x82, 0x1a, 0x79, 0x0a
    },
  },
};


static ChipInfoPartMarketingDataType ChipInfo_MarketingData_Adreno740v2 =
{
  .ePart = CHIPINFO_PART_GPU,
  .GPUData = {
    .nChipID = 0x43050a01,    // TODO Same as vulkan ID?
    .nVulkanID = 0x43050a01,
    .szName =
    {
      0xcf, 0xa2, 0x17, 0x25, 0xf9, 0x6d, 0x02, 0xa4,
      0x50, 0xa7, 0xcb, 0xfb, 0x3c, 0xb9, 0xea, 0xa0,
      0x76, 0xe4, 0xe4, 0x2c, 0xe4, 0x16, 0xba, 0x11,
      0xcc, 0x4d, 0x7c, 0xf1, 0x82, 0x1a, 0x79, 0x0a
    },
  },
};


/*
 * This structure is never exposed publicly in full, but
 * each entry in this array will be deep-copied and returned by
 * ChipInfo_GetMarketingData when called with the corresponding
 * ChipInfoPartType.
 *
 * Multiple Family+version+PCode+FeatureCode combinations can share
 * marketing information for a ChipInfoPartType, so they should share
 * pointers in their respective ChipInfo_PartData_* arrays.
 *
 * These are regular pointers, not pointers to const, because the
 * pointed data needs to be modified during deobfuscation. That's done
 * in-place to save space.
 */
static ChipInfoPartMarketingDataType *ChipInfo_PartData_Kailua_v1_DefaultSKU[] =
{
  &ChipInfo_MarketingData_Adreno740,
};

static ChipInfoPartMarketingDataType *ChipInfo_PartData_Kailua_v2_DefaultSKU[] =
{
  &ChipInfo_MarketingData_Adreno740v2,
};

/*
 * Interal LUT of all product management data. The only information
 * exposed publicly is:
 *  ChipInfo_ProductManagementData[family,version,sku].PartMarketingData
 *
 * This publicly exposed PartMarketingData contains pointers to BootIMEM and
 * must be deep-copied into DDR to make it available after XBL.
*/
static struct ChipInfoProductManagementDataType ChipInfo_ProductManagementData[] =
{
  // ... mappings for specific SKUs and versions

  // Default Kailua v1.x mappings
  { CHIPINFO_FAMILY_KAILUA, CHIPINFO_VERSION(1,0), CHIPINFO_VERSION(2,0),       { CHIPINFO_FEATURE_CODE_UNKNOWN, CHIPINFO_P_CODE_UNKNOWN }, ARRAY_SIZE(ChipInfo_PartData_Kailua_v1_DefaultSKU), ChipInfo_PartData_Kailua_v1_DefaultSKU },

  // Default Kailua v2.0+ mappings
  { CHIPINFO_FAMILY_KAILUA, CHIPINFO_VERSION(2,0), CHIPINFO_VERSION(0xff,0xff), { CHIPINFO_FEATURE_CODE_UNKNOWN, CHIPINFO_P_CODE_UNKNOWN }, ARRAY_SIZE(ChipInfo_PartData_Kailua_v2_DefaultSKU), ChipInfo_PartData_Kailua_v2_DefaultSKU },

  // Other chip families/versions.
};


static ChipInfoBSPType ChipInfoBSP =
{
  .aLUT = ChipInfoDataLUT,
  .nNumLUTEntries = ARRAY_SIZE(ChipInfoDataLUT),
  .aArchFamilyData = ChipInfoArchFamilyArray,
  .nNumArchFamilyDataEntries = ARRAY_SIZE(ChipInfoArchFamilyArray),
  .aProductManagementData = ChipInfo_ProductManagementData,
  .nNumFamiliesWithProductManagementData = ARRAY_SIZE(ChipInfo_ProductManagementData),
};


/*==============================================================================
      Functions
==============================================================================*/

ChipInfoBSPType *ChipInfo_GetBSPData
(
  void
)
{
  return &ChipInfoBSP;
}
