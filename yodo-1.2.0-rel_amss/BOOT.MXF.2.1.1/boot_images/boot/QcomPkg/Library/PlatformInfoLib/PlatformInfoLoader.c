/**
  @file PlatformInfo.c

  Interface implementation file for the PlatformInfo driver.
*/
/*
  ====================================================================

  Copyright (c) 2011, 2022 Qualcomm Technologies, Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================


  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "PlatformInfoInternal.h"

#include "Library/BaseLib.h"
#include "com_dtypes.h"
#include "pm_version.h"
#include "smem.h"
#include "DDIChipInfo.h"
#include "DALDeviceId.h"
#include "Library/CoreMsgRam.h"
#include "DTBExtnLib.h"
#include "ChipInfo.h"


/*=========================================================================
      Type Definitions
==========================================================================*/

/*
 * PlatformInfoRPMType
 *
 */
typedef struct
{
  DalPlatformInfoPlatformInfoType   PlatformInfo;
  uint32                            nNumKVPS;
  PlatformInfoKVPSType              aKVPS[];
} PlatformInfoRPMType;

/*
 * PlatformInfoKVPSCDTType
 *
 *
 */
typedef struct PACK(PlatformInfoKVPSCDTType)
{
  uint8 nKey;
  uint8 nValue;
} PlatformInfoKVPSCDTType;

/*
 * PlatformInfoCDTType
 *
 * Storage structure which mimics the format of the EEPROM platform ID section.
 */
typedef struct PACK(PlatformInfoCDTType)
{
  uint8                 nVersion;
  uint8                 nPlatform;
  uint8                 nHWVersionMajor;
  uint8                 nHWVersionMinor;
  uint8                 nSubtype;
  uint8                 nNumKVPS;
  PlatformInfoKVPSCDTType  aKVPS[];
} PlatformInfoCDTType;

/*
 * PlatformInfoPmicFamilyType
 *
 * An enum to define Chip Family type.
 */
typedef enum
{
  PLATFORMINFO_PMIC_FAMILY_A     = 0,
  PLATFORMINFO_PMIC_FAMILY_B     = 1,
}PlatformInfoPmicFamilyType;


/*=========================================================================
      Global data and Typedefs
==========================================================================*/

#define PLATINFO_DTB_NODE "/soc/PlatformInfo"


PlatformInfoCDTType gPlatInfoCDTDefault = {
  .nVersion        = 0x03,
  .nPlatform       = 0x08,
  .nHWVersionMajor = 0x01,
  .nHWVersionMinor = 0x00,
  .nSubtype        = 0x00,
  .nNumKVPS        = 0x00,
};


/*=========================================================================
      Function Prototypes
==========================================================================*/

static DALResult PlatformInfo_InitGlblCtxt (PlatformInfoDrvCtxt *pDrvCtxt);
static DALResult PlatformInfo_InitSMem     (PlatformInfoDrvCtxt *pDrvCtxt);
static DALResult PlatformInfo_CDTInit (PlatformInfoDrvCtxt *pDrvCtxt, PlatformInfoCDTType *pPlatformInfo);


/*=========================================================================
      Function Definitions
==========================================================================*/

/* =========================================================================
**  Function : PlatformInfo_Init
** =========================================================================*/
/**
  See PlatformInfo.h
*/
DALResult PlatformInfo_Init
(
  void
)
{
  PlatformInfoDrvCtxt *pDrvCtxt = PlatformInfo_GetDrvCtxt();

  if (pDrvCtxt->bInitialized)
  {
    return DAL_SUCCESS;
  }

  /*
   * Only detect if loading scripts haven't already set the platform
   * type manually.
   */
  if (pDrvCtxt->PlatformInfo.platform == DALPLATFORMINFO_TYPE_UNKNOWN)
  {
    pDrvCtxt->PlatformInfo.platform = PlatformInfo_DetectPlatformType();
  }

  pDrvCtxt->bInitialized = TRUE;
  return DAL_SUCCESS;
}


/* =========================================================================
**  Function : PlatformInfo_InitGlblCtxt
** =========================================================================*/
/**
  This function allocates and fills in the global context.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.

  @return
  None.
*/

static DALResult PlatformInfo_InitGlblCtxt
(
  PlatformInfoDrvCtxt *pDrvCtxt
)
{
  DALResult eResult;
  uint32 nSize, nKVPSSize;

  /*-----------------------------------------------------------------------*/
  /* Ensure global context has been initialized.                           */
  /*-----------------------------------------------------------------------*/

  DALGLBCTXT_Init();

  /*-----------------------------------------------------------------------*/
  /* Allocate the context.                                                 */
  /*-----------------------------------------------------------------------*/

  nKVPSSize = pDrvCtxt->nNumKVPS * sizeof(PlatformInfoKVPSType);
  nSize = sizeof(PlatformInfoGlbCtxType) + nKVPSSize;

  eResult = DALGLBCTXT_AllocCtxt("DAL_PLATFORM_INFO", nSize,
    0, (void **)&pDrvCtxt->pGlbCtxt);

  /*-----------------------------------------------------------------------*/
  /* Fill it in if possible.                                               */
  /*-----------------------------------------------------------------------*/

  if (eResult != DAL_SUCCESS)
  {
    return DAL_ERROR;
  }

  pDrvCtxt->pGlbCtxt->PlatformInfo = pDrvCtxt->PlatformInfo;
  pDrvCtxt->pGlbCtxt->nNumKVPS = pDrvCtxt->nNumKVPS;
  DALSYS_memscpy(pDrvCtxt->pGlbCtxt->aKVPS, nKVPSSize, pDrvCtxt->aKVPS, nKVPSSize);

  return DAL_SUCCESS;

} /* PlatformInfo_InitGlblCtxt */


/* =========================================================================
**  Function : PlatformInfo_InitSmem
** =========================================================================*/
/*
  Initializes and populates the SMEM (socinfo) location in which to store
  chip, platform, and build information.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.
*/

static DALResult PlatformInfo_InitSMem
(
  PlatformInfoDrvCtxt *pDrvCtxt
)
{
  DalPlatformInfoSMemType *pSMem;
  DalPlatformInfoSMemPMICType *aPMICInfo;
  DalDeviceHandle *phChipInfo = NULL;
  pm_device_info_type PmicDeviceInfo;
  DALResult eResult = DAL_SUCCESS;
  pm_err_flag_type ePMICErr;
  uint32 i, nPMICIndex, nNumPMICs;
  uint32 nSize, nPMICArraySize;
  uint32 nClusterArraySize = 0, nNumClusters = 0, nClusterIdx, nMask;
  uint32 nDefectivePartsArraySize = 0, nPartIdx;
  uint32 *aClusterArray, *aDefectivePartsArray;
  ChipInfoSKUType SKUInfo = {0};
  msg_ram_err smem_err;
  ChipInfoResult eChipInfoResult;
  ChipInfoPartMarketingDataType *aSMemMarketingData = NULL;
  // This could be a few hundred bytes if all CHIPINFO_NUM_PARTS have
  // mappings for this Family+SKU.
  ChipInfoPartMarketingDataType aLocalMarketingData[CHIPINFO_NUM_PARTS] = {0};
  uint32 nMarketingDataArraySize = 0, nNumMarketingDataEntries = 0;

  /*-----------------------------------------------------------------------*/
  /* Calculate array sizes and allocate SMEM.                              */
  /*-----------------------------------------------------------------------*/

  // TODO this loop is repeated further below. This first loop gets the
  // number of PMICs so smem_alloc can be called with the correct amount,
  // and the second loop fills SMEM with PMIC info, but that leads to
  // duplicated work. Depending on how limited stack space is in XBL, it
  // might be more efficient to store all the pmic info on the stack in
  // this loop, figure out how much SMEM space to allocate, then memcpy
  // from the stack into SMEM.
  for (i = 0, nNumPMICs = 0;; i++)
  {
    ePMICErr = pm_get_pmic_info(i, &PmicDeviceInfo);
    if (ePMICErr == PM_ERR_FLAG_FEATURE_NOT_SUPPORTED)
    {
      break;
    }

    if (PmicDeviceInfo.ePmicModel != PMIC_IS_UNKNOWN)
    {
      nNumPMICs++;
    }
  }

  nPMICArraySize = sizeof(DalPlatformInfoSMemPMICType) * nNumPMICs;

  eResult = DAL_DeviceAttach(DALDEVICEID_CHIPINFO, &phChipInfo);
  if (eResult == DAL_SUCCESS)
  {
    // TODO this loop is repeated below. See the comment above the
    // preceding pm_get_pmic_info loop.
    for (nNumClusters = 0;; nNumClusters++)
    {
      eResult = DalChipInfo_GetDefectiveCPUs(phChipInfo, nNumClusters, &nMask);
      if (eResult == DAL_ERROR_OUT_OF_RANGE_PARAMETER)
      {
        break;
      }
    }
    nClusterArraySize = sizeof(uint32) * nNumClusters;

    nDefectivePartsArraySize = sizeof(uint32) * CHIPINFO_NUM_PARTS;

    for (nPartIdx = 0; nPartIdx < CHIPINFO_NUM_PARTS; nPartIdx++)
    {
      // aLocalMarketingData is *not* indexed by ChipInfoPartType.
      // CHIPINFO_NUM_PARTS is just the max number of parts which might
      // have marketing information. aLocalMarketingData is not sparse:
      // all parts with marketing data are filled in at the start of the
      // array. This makes it easy to memcpy into SMEM further below,
      // since we can copy the first nMarketingDataArraySize bytes instead
      // of looping through aLocalMarketingData again and checking if
      // the mappings are valid before calling memcpy.
      eChipInfoResult = ChipInfo_GetMarketingData(nPartIdx, &aLocalMarketingData[nNumMarketingDataEntries]);
      if (eChipInfoResult == CHIPINFO_SUCCESS)
      {
        nNumMarketingDataEntries++;
      }
    }
    nMarketingDataArraySize = sizeof(ChipInfoPartMarketingDataType) * nNumMarketingDataEntries;
  }


  nSize = sizeof(DalPlatformInfoSMemType) + nClusterArraySize + nDefectivePartsArraySize + nMarketingDataArraySize + nPMICArraySize ;

  pSMem = (DalPlatformInfoSMemType *) smem_alloc(SMEM_HW_SW_BUILD_ID, nSize);
  if (pSMem == NULL)
  {
    return DAL_ERROR;
  }

  DALSYS_memset(pSMem, 0, nSize);

  /*-----------------------------------------------------------------------*/
  /* Get misc information.                                                 */
  /*-----------------------------------------------------------------------*/

  pSMem->nFormat = DALPLATFORMINFO_SMEM_FORMAT;


  /*-----------------------------------------------------------------------*/
  /* Get chip information.                                                 */
  /*-----------------------------------------------------------------------*/

  if (phChipInfo != NULL)
  {
    DalChipInfo_GetChipId(phChipInfo, (DalChipInfoIdType *)&pSMem->eChipId);
    DalChipInfo_GetChipVersion(phChipInfo, &pSMem->nChipVersion);
    DalChipInfo_GetRawChipId(phChipInfo, &pSMem->nRawChipId);
    DalChipInfo_GetRawChipVersion(phChipInfo, &pSMem->nRawChipVersion);
    DalChipInfo_GetFoundryId(phChipInfo,
      (DalChipInfoFoundryIdType *)&pSMem->nFoundryId);
    DalChipInfo_GetSerialNumber(phChipInfo, &pSMem->nChipSerial);
    DalChipInfo_GetChipFamily(phChipInfo, &pSMem->nChipFamily);
    DalChipInfo_GetRawDeviceFamily(phChipInfo, &pSMem->nRawDeviceFamily);
    DalChipInfo_GetRawDeviceNumber(phChipInfo, &pSMem->nRawDeviceNumber);
    DalChipInfo_GetChipIdString(phChipInfo, pSMem->szChipIdStr, DALPLATFORMINFO_SMEM_MAX_CHIP_ID_LENGTH);
    DalChipInfo_GetQFPROMChipId(phChipInfo, &pSMem->nQFPROMChipId);
    DalChipInfo_GetModemSupport(phChipInfo, &pSMem->nModemSupported);

    pSMem->nNumClusters = nNumClusters;
    pSMem->nClusterArrayOffset = sizeof(DalPlatformInfoSMemType);
    aClusterArray = (uint32 *)((uintnt)pSMem + pSMem->nClusterArrayOffset);
    for (nClusterIdx = 0; nClusterIdx < nNumClusters; nClusterIdx++)
    {
      eResult = DalChipInfo_GetDefectiveCPUs(phChipInfo, nClusterIdx, &nMask);
      if (eResult != DAL_SUCCESS)
      {
        break;
      }
      aClusterArray[nClusterIdx] = nMask;
    }

    pSMem->nNumDefectiveParts = CHIPINFO_NUM_PARTS;
    pSMem->nDefectivePartsArrayOffset = sizeof(DalPlatformInfoSMemType) + nClusterArraySize;
    aDefectivePartsArray = (uint32 *)((uintnt)pSMem + pSMem->nDefectivePartsArrayOffset);
    for (nPartIdx = 0; nPartIdx < CHIPINFO_NUM_PARTS; nPartIdx++)
    {
      eResult = DalChipInfo_GetDefectivePart(phChipInfo, nPartIdx, &nMask);
      if (eResult != DAL_SUCCESS)
      {
        break;
      }
      aDefectivePartsArray[nPartIdx] = nMask;
    }

    /*
     * No return value check since it isn't relevant to this function.
     * Just copy SKUInfo into SMEM directly. If it's invalid, ChipInfo
     * will need to handle it.
    */
    ChipInfo_GetSKU(&SKUInfo);
    pSMem->eFeatureCode = SKUInfo.eFeatureCode;
    pSMem->ePCode = SKUInfo.ePCode;
    pSMem->nPartNameMapOffset = pSMem->nDefectivePartsArrayOffset + nDefectivePartsArraySize;
    pSMem->nNumPartNameMappings = nNumMarketingDataEntries;

    aSMemMarketingData = (ChipInfoPartMarketingDataType *)((uintnt)pSMem + pSMem->nPartNameMapOffset);
    DALSYS_memscpy(
      aSMemMarketingData,
      nMarketingDataArraySize,
      aLocalMarketingData,
      nMarketingDataArraySize);
  }

  /*-----------------------------------------------------------------------*/
  /* Get platform information.                                             */
  /*-----------------------------------------------------------------------*/

  pSMem->ePlatformType = pDrvCtxt->PlatformInfo.platform;
  pSMem->nPlatformVersion = pDrvCtxt->PlatformInfo.version;
  pSMem->nPlatformSubtype = pDrvCtxt->PlatformInfo.subtype;
  pSMem->bFusion = pDrvCtxt->PlatformInfo.fusion;

  /*-----------------------------------------------------------------------*/
  /* Get PMIC information.                                                 */
  /*-----------------------------------------------------------------------*/

  pSMem->nNumPMICs = nNumPMICs;
  pSMem->nPMICArrayOffset = sizeof(DalPlatformInfoSMemType)
    + nClusterArraySize + nDefectivePartsArraySize + nMarketingDataArraySize;
  aPMICInfo =
    (DalPlatformInfoSMemPMICType *)((uintnt)pSMem + pSMem->nPMICArrayOffset);

  for (i = 0, nPMICIndex = 0;; i++)
  {
    ePMICErr = pm_get_pmic_info(i, &PmicDeviceInfo);
    if (ePMICErr == PM_ERR_FLAG_FEATURE_NOT_SUPPORTED || nPMICIndex >= nNumPMICs)
    {
      break;
    }

    if (PmicDeviceInfo.ePmicModel != PMIC_IS_UNKNOWN)
    {
      aPMICInfo[nPMICIndex].nPMICModel =
        ((PLATFORMINFO_PMIC_FAMILY_B << 16) | (PmicDeviceInfo.ePmicModel));

      aPMICInfo[nPMICIndex].nPMICVersion =
        DALPLATFORMINFO_VERSION(PmicDeviceInfo.nPmicAllLayerRevision,
                                PmicDeviceInfo.nPmicMetalRevision);

      nPMICIndex++;
    }
  }

  /*
   * Copy up to three PMICs from main array into legacy array.
   */
  DALSYS_memscpy(pSMem->aPMICInfo, sizeof(pSMem->aPMICInfo),
    aPMICInfo, nPMICArraySize);

  /*
   * Store the SMEM base address in MSG_RAM so that images without SMEM
   * which have access to MSG_RAM (like AOP) can retrieve ChipInfo as well.
   */
  smem_err = msg_ram_set_smem_address(SMEM_HW_SW_BUILD_ID, (uint32)(uintptr_t)pSMem);
  if (smem_err != MSG_RAM_SET_SUCCESS)
  {
    DALSYS_Free(pSMem);
    return DAL_ERROR;
  }

  return DAL_SUCCESS;

} /* END PlatformInfo_InitSMem */


/* =========================================================================
**  Function : PlatformInfo_InitRPM
** =========================================================================*/
/*
  Initialize and populate the IMEM location used to communicate to RPM.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.
*/

static DALResult PlatformInfo_InitRPM
(
  PlatformInfoDrvCtxt *pDrvCtxt
)
{
  PlatformInfoRPMType *pRPM;
  uint32 nKVPSSize;
  DALResult eResult;

  eResult = PlatformInfo_GetPropertyValue("rpm_buffer_addr", (void **)&pRPM);
  if (eResult != DAL_SUCCESS)
  {
    return DAL_ERROR;
  }

  pRPM->PlatformInfo = pDrvCtxt->PlatformInfo;
  pRPM->nNumKVPS = pDrvCtxt->nNumKVPS;
  if (pRPM->nNumKVPS > 0)
  {
    nKVPSSize = pRPM->nNumKVPS * sizeof(PlatformInfoKVPSType);
    DALSYS_memscpy(pRPM->aKVPS, nKVPSSize, pDrvCtxt->aKVPS, nKVPSSize);
  }

  return DAL_SUCCESS;

} /* END PlatformInfo_InitRPM */


/* =========================================================================
**  Function : PlatformInfo_DeviceTreeInit
** =========================================================================*/
/*
  Initialize and populate the platform info by reading device tree.

  @param **ppPlatformInfo [out] -- pointer to platform info structure that will
                                   contain the data read from device tree.
*/

static DALResult PlatformInfo_DeviceTreeInit
(
  PlatformInfoCDTType **ppPlatformInfo
)
{
  void *blob = NULL;
  fdt_node_handle node;
  uint32_t nPlatInfoSize = 0;
  int nDTResult = 0;
  DALResult eResult = DAL_SUCCESS;

  nDTResult = fdt_get_node_handle(&node, blob, PLATINFO_DTB_NODE);
  if (nDTResult != 0)
  {
    return DAL_ERROR;
  }

  /*
   * Platform info was located in the device tree.
   * Allocate memory to store the platform info.
   */
  nDTResult = fdt_get_prop_size(&node, "PlatformInfo", &nPlatInfoSize);
  if (nDTResult != 0)
  {
    return DAL_ERROR;
  }

  eResult = DALSYS_Malloc(nPlatInfoSize, (void **)ppPlatformInfo);
  if (eResult != DAL_SUCCESS)
  {
    return eResult;
  }

  /*
   * Populate the data
   */
  nDTResult = fdt_get_uint8_prop_list(&node, "PlatformInfo", (uint8_t*)*ppPlatformInfo, nPlatInfoSize);
  if (nDTResult != 0)
  {
    return DAL_ERROR;
  }

  return DAL_SUCCESS;

} /* END PlatformInfo_DeviceTreeInit */


/* =========================================================================
**  Function : PlatformInfo_CDTInit
** =========================================================================*/
/*
  Populate the platform information based on data from the CDT.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.
  @param *pPlatformInfo [in] -- Pointer to the CDT data.
*/

static DALResult PlatformInfo_CDTInit
(
  PlatformInfoDrvCtxt *pDrvCtxt,
  PlatformInfoCDTType *pPlatformInfo
)
{
  static boolean bCDTInitialized = FALSE;
  DALResult eResult;
  uint32 nSize, i, nVal;

  if (bCDTInitialized == TRUE)
  {
    return DAL_SUCCESS;
  }

  if (pPlatformInfo == NULL)
  {
    /*
     * Platform info was not found in storage media. Try to read device tree.
     */
    eResult = PlatformInfo_DeviceTreeInit(&pPlatformInfo);
    if (eResult != DAL_SUCCESS || pPlatformInfo == NULL)
    {
      /*
       * Platform info could not be read from device tree.
       * Fall back to default values.
       */
      pPlatformInfo = &gPlatInfoCDTDefault;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Get platform type.                                                    */
  /*-----------------------------------------------------------------------*/
  /*
   * Only update the platform type if it hasn't already been set through
   * scripts or detecting pre-sil.
   */
  if (pDrvCtxt->PlatformInfo.platform == DALPLATFORMINFO_TYPE_UNKNOWN)
  {
    pDrvCtxt->PlatformInfo.platform =
      (DalPlatformInfoPlatformType)pPlatformInfo->nPlatform;
  }


  /*-----------------------------------------------------------------------*/
  /* Get platform version.                                                 */
  /*-----------------------------------------------------------------------*/

  pDrvCtxt->PlatformInfo.version =
    DALPLATFORMINFO_VERSION(pPlatformInfo->nHWVersionMajor,
                            pPlatformInfo->nHWVersionMinor);

  /*-----------------------------------------------------------------------*/
  /* Get platform sub-type.                                                */
  /*-----------------------------------------------------------------------*/

  if (pPlatformInfo->nVersion >= 2)
  {
    pDrvCtxt->PlatformInfo.subtype = pPlatformInfo->nSubtype;
  }

  /*-----------------------------------------------------------------------*/
  /* Get key-value pairs.                                                  */
  /*-----------------------------------------------------------------------*/

  if (pPlatformInfo->nVersion >= 3)
  {
    pDrvCtxt->nNumKVPS = pPlatformInfo->nNumKVPS;
    if (pDrvCtxt->nNumKVPS > 0)
    {
      nSize = pDrvCtxt->nNumKVPS * sizeof(PlatformInfoKVPSType);
      eResult = DALSYS_Malloc(nSize, (void **)&pDrvCtxt->aKVPS);
      if (eResult != DAL_SUCCESS)
      {
        return DAL_ERROR;
      }

      for (i = 0; i < pDrvCtxt->nNumKVPS; i++)
      {
        pDrvCtxt->aKVPS[i].nKey = pPlatformInfo->aKVPS[i].nKey;
        pDrvCtxt->aKVPS[i].nValue = pPlatformInfo->aKVPS[i].nValue;
      }
    }

    /*-----------------------------------------------------------------------*/
    /* Get Fusion.                                                           */
    /*-----------------------------------------------------------------------*/

    eResult =
      PlatformInfo_GetKeyValue(DALPLATFORMINFO_KEY_FUSION, &nVal);
    if (eResult == DAL_SUCCESS)
    {
      pDrvCtxt->PlatformInfo.fusion = nVal;
    }
  }

  bCDTInitialized = TRUE;
  return DAL_SUCCESS;

} /* END PlatformInfo_CDTInit */


/* =========================================================================
**  Function : PlatformInfo_CDTConfigPreDDR
** =========================================================================*/
/*
  See DDIPlatformInfo.h
*/

DALResult PlatformInfo_CDTConfigPreDDR
(
  void                *pPlatformInfo
)
{
  PlatformInfoDrvCtxt *pDrvCtxt = PlatformInfo_GetDrvCtxt();
  DALResult eResult;

  /*
   * Initialize CDT data.
   */
  eResult = PlatformInfo_CDTInit(pDrvCtxt, (PlatformInfoCDTType *)pPlatformInfo);
  if (eResult != DAL_SUCCESS)
  {
    return DAL_ERROR;
  }

  /*
   * Initialize the location for communication to RPM.
   */
  PlatformInfo_InitRPM(pDrvCtxt);

  return DAL_SUCCESS;

} /* END PlatformInfo_CDTConfigPreDDR*/


/* =========================================================================
**  Function : PlatformInfo_CDTConfigPostDDR
** =========================================================================*/
/*
  See DDIPlatformInfo.h
*/

DALResult PlatformInfo_CDTConfigPostDDR
(
  void                *pPlatformInfo
)
{
  PlatformInfoDrvCtxt *pDrvCtxt = PlatformInfo_GetDrvCtxt();
  DALResult eResult;

  /*
   * Initialize CDT data.
   */
  eResult = PlatformInfo_CDTInit(pDrvCtxt, (PlatformInfoCDTType *)pPlatformInfo);
  if (eResult != DAL_SUCCESS)
  {
    return DAL_ERROR;
  }

  /*
   * Initialize the DAL global context.
   */
  PlatformInfo_InitGlblCtxt(pDrvCtxt);

  /*
   * Initialize the SMEM (socinfo) location.
   */
  eResult = PlatformInfo_InitSMem(pDrvCtxt);
  if (eResult != DAL_SUCCESS)
  {
    return DAL_ERROR;
  }

  return DAL_SUCCESS;
}

