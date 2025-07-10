/*==============================================================================
  @file ChipInfoBSP.c

  ChipInfo BSP data.

================================================================================
        Copyright (c) 2016-2021, 2023 Qualcomm Technologies, Inc.
               All Rights Reserved.
        Confidential and Proprietary - Qualcomm Technologies, Inc
================================================================================

  $Header: //components/rel/core.boot/6.0/QcomPkg/Library/ChipInfoLib/ChipInfoBSP.c#22 $
  $DateTime: 2023/09/26 00:30:00 $
  $Author: pwbldsvc $

==============================================================================*/

/*==============================================================================
      Include Files
==============================================================================*/
#include "comdef.h"
#include "ChipInfoLocal.h"
#include "ChipInfoLoader.h"

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
 * Various HLOS clients still expect to see the old naming convention for
 * Hana variants. Continue to report the legacy names for Hana.
 *
 * This table only needs to contain mappings for targets supported out of this warehouse.
 */
static const ChipInfoDataLUTType ChipInfoDataLUT[] =
{
  { "UNKNOWN",              CHIPINFO_ID_UNKNOWN,              CHIPINFO_PARTNUM_UNKNOWN,              CHIPINFO_MODEM_UNKNOWN    },
  { "SM_WAIPIO",            CHIPINFO_ID_SM_WAIPIO,            CHIPINFO_PARTNUM_SM_WAIPIO,            CHIPINFO_MODEM_SUPPORTED  },
  { "SMP_WAIPIO",           CHIPINFO_ID_SMP_WAIPIO,           CHIPINFO_PARTNUM_SMP_WAIPIO,           CHIPINFO_MODEM_UNKNOWN    },
  { "SM_FILLMORE",          CHIPINFO_ID_SM_FILLMORE,          CHIPINFO_PARTNUM_SM_FILLMORE,          CHIPINFO_MODEM_SUPPORTED  },
  { "SM_KAILUA",            CHIPINFO_ID_SM_KAILUA,            CHIPINFO_PARTNUM_SM_KAILUA,            CHIPINFO_MODEM_SUPPORTED  },
  { "SXR_AURORA",           CHIPINFO_ID_SXR_AURORA,           CHIPINFO_PARTNUM_SXR_AURORA,           CHIPINFO_MODEM_UNKNOWN    },
  { "SM_PALIMA",            CHIPINFO_ID_SM_PALIMA,            CHIPINFO_PARTNUM_SM_PALIMA,            CHIPINFO_MODEM_SUPPORTED  },
  { "SM_PUNA",   			CHIPINFO_ID_SM_PALIMA_LTE_ONLY,   CHIPINFO_PARTNUM_SM_PALIMA_LTE_ONLY,   CHIPINFO_MODEM_SUPPORTED  },
  { "SMP_PALIMA",           CHIPINFO_ID_SMP_PALIMA,           CHIPINFO_PARTNUM_SMP_PALIMA,           CHIPINFO_MODEM_UNKNOWN    },
  { "SM_NETRANI",           CHIPINFO_ID_SM_NETRANI,           CHIPINFO_PARTNUM_SM_NETRANI,           CHIPINFO_MODEM_SUPPORTED  },
  { "SMP_FILLMORE",         CHIPINFO_ID_SMP_FILLMORE,         CHIPINFO_PARTNUM_SMP_FILLMORE,         CHIPINFO_MODEM_UNKNOWN    },
  { "SM_WAIPIO_LTE_ONLY",   CHIPINFO_ID_SM_WAIPIO_LTE_ONLY,   CHIPINFO_PARTNUM_SM_WAIPIO_LTE_ONLY,   CHIPINFO_MODEM_SUPPORTED  },
  { "SM_WALES",             CHIPINFO_ID_SM_FILLMORE_LTE_ONLY, CHIPINFO_PARTNUM_SM_FILLMORE_LTE_ONLY, CHIPINFO_MODEM_SUPPORTED  },
  { "SM_CLARENCE",          CHIPINFO_ID_SM_CLARENCE,          CHIPINFO_PARTNUM_SM_CLARENCE,          CHIPINFO_MODEM_SUPPORTED  },
  { "SM_TOFINO",            CHIPINFO_ID_SM_TOFINO,            CHIPINFO_PARTNUM_SM_TOFINO,            CHIPINFO_MODEM_SUPPORTED  },
  { "QCS_CLARENCE",         CHIPINFO_ID_QCS_CLARENCE,         CHIPINFO_PARTNUM_QCS_CLARENCE,         CHIPINFO_MODEM_UNKNOWN    },
  { "QCM_CLARENCE",         CHIPINFO_ID_QCM_CLARENCE,         CHIPINFO_PARTNUM_QCM_CLARENCE,         CHIPINFO_MODEM_SUPPORTED  },
  { "SMP_CLARENCE",         CHIPINFO_ID_SMP_CLARENCE,         CHIPINFO_PARTNUM_SMP_CLARENCE,         CHIPINFO_MODEM_UNKNOWN    },
  { "SCP_NETRANI",          CHIPINFO_ID_SCP_NETRANI,          CHIPINFO_PARTNUM_SCP_NETRANI,          CHIPINFO_MODEM_UNKNOWN    },
  { "SM_NETRANI7",          CHIPINFO_ID_SM_NETRANI7,          CHIPINFO_PARTNUM_SM_NETRANI7,          CHIPINFO_MODEM_SUPPORTED  },
  { "SCQ_NETRANI",          CHIPINFO_ID_SCQ_NETRANI,          CHIPINFO_PARTNUM_SCQ_NETRANI,          CHIPINFO_MODEM_UNKNOWN    },
  { "SCP_NETRANI",          CHIPINFO_ID_SCP_NETRANI,          CHIPINFO_PARTNUM_SCP_NETRANI,          CHIPINFO_MODEM_UNKNOWN    },
  { "SG_NTERANI",           CHIPINFO_ID_SG_NETRANI,           CHIPINFO_PARTNUM_SG_NETRANI,           CHIPINFO_MODEM_SUPPORTED  },
  { "SCP_NETRANI7",         CHIPINFO_ID_SCP_NETRANI7,         CHIPINFO_PARTNUM_SCP_NETRANI7,         CHIPINFO_MODEM_UNKNOWN    },
  { "SGP_NETRANI",          CHIPINFO_ID_SGP_NETRANI,          CHIPINFO_PARTNUM_SGP_NETRANI,          CHIPINFO_MODEM_UNKNOWN    },
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
  { CHIPINFO_ARCH_FAMILY_WILDCAT,      1,  CHIPINFO_FAMILY_WAIPIO,      CHIPINFO_ID_SM_WAIPIO     },
  { CHIPINFO_ARCH_FAMILY_WILDCAT,      4,  CHIPINFO_FAMILY_FILLMORE,    CHIPINFO_ID_SM_FILLMORE   },
  { CHIPINFO_ARCH_FAMILY_WILDCAT,      3,  CHIPINFO_FAMILY_KAILUA,      CHIPINFO_ID_SM_KAILUA     },
  { CHIPINFO_ARCH_FAMILY_WILDCAT,      6,  CHIPINFO_FAMILY_AURORA,      CHIPINFO_ID_SXR_AURORA    },
  { CHIPINFO_ARCH_FAMILY_WILDCAT,      8,  CHIPINFO_FAMILY_PALIMA,      CHIPINFO_ID_SM_PALIMA     },
  { CHIPINFO_ARCH_FAMILY_WILDCAT,      5,  CHIPINFO_FAMILY_NETRANI,     CHIPINFO_ID_SM_NETRANI    },
  { CHIPINFO_ARCH_FAMILY_WILDCAT,      16,  CHIPINFO_FAMILY_CLARENCE,   CHIPINFO_ID_SM_CLARENCE   },

};


static ChipInfoBSPType ChipInfoBSP =
{
  .aLUT = ChipInfoDataLUT,
  .nNumLUTEntries = ARRAY_SIZE(ChipInfoDataLUT),
  .aArchFamilyData = ChipInfoArchFamilyArray,
  .nNumArchFamilyDataEntries = ARRAY_SIZE(ChipInfoArchFamilyArray),
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
