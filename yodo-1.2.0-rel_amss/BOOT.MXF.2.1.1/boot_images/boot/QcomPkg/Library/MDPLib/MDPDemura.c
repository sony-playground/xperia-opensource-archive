/*=============================================================================
Copyright (c) 2020-2022 Qualcomm Technologies International, Ltd.
All Rights Reserved.
Qualcomm Technologies International, Ltd. Confidential and Proprietary. 
=============================================================================*/
#include "MDPLib.h"
#include "MDPLib_i.h"
#include "MDPSystem.h"
#include "hal_mdp.h"
#include <Library/BaseLib.h>
#include "DisplayUtils.h"
#include "HALDSILib.h"
#include "stdio.h"

/*=========================================================================
     Default Defines
==========================================================================*/
#define DISP_DEMURA_FV_LABEL                  L"qmcs"
#define DISP_DEMURA_FILE_NAME_LEN             50
#define DEMURA_HEADER_SIZE                    14
#define DEMURA_CONTROL_1_SIZE                 17
#define DEMURA_CONFIG_0_SIZE_1                28 
#define DEMURA_CONFIG_0_SIZE_2                51
#define DEMURA_HFC_PAGE_ALIGN_4K              (1<<12)
#define DISP_DEMURA_TIMESTAMP_LEN             17
/****************************************************************************
*
** FUNCTION: uReadBytes()
*/
/*!
* \brief
*   Read bytes from input buffer.
*
* \param [in]   pInput           - pointer to input buffer
* \param [in]   uInputLen        - input buffer size
* \param [out]  pOutput          - read data
* \param [in]   uReadByte        - read byte.
*
* \retval uint32, data remaining in input buffer.
*
****************************************************************************/
static uint32 uReadBytes(uint8** pInput, uint32 uInputLen, void* pOutput, uint32 uReadByte)
{
  uint32 uDataRemaining = uInputLen;
  uint32 uByteProcessed = 0;

  while ((uDataRemaining) &&
         (uByteProcessed < uReadByte))
  {
    ((uint8*)pOutput)[uByteProcessed] = (*pInput)[uByteProcessed];
    uDataRemaining--;
    uByteProcessed++;
  }
  (*pInput) += uByteProcessed;

  return uDataRemaining;
}

 /****************************************************************************
*
** FUNCTION: DemuraFileCRCCheck()
*/
/*!
* \brief
*   CRC check for Demura file.
*
* \param [in] pDemuraBuffer    - Demura data buffer
* \param [in] uDemuraDataSize  - Size of the Demura data
*
* \retval MDP_Status
*
****************************************************************************/
 static MDP_Status DemuraFileCRCCheck(uint8* pDemuraBuffer, uint32 uDemuraDataSize)
 {
   MDP_Status          eStatus        = MDP_STATUS_OK;
   uint32              uCRCRead       = 0;
   uint32              uCRCCalc       = 0;
   uint32              uSize          = uDemuraDataSize - 4;
   uint8              *pPayload       = pDemuraBuffer;
   uint32              uCRCPoly       = 0x0fc22f87;
   uint32              uDataRemaining = uDemuraDataSize;

   for (uint32 index = 0; index < uSize; index += 4)
   {
     uint32 constant    = ((uCRCCalc & 0x80000000) > 0x00000000) ? uCRCPoly : 0x00000000;
     uint32 uCurPayload = 0;
     uint8  uCurData;

     uDataRemaining = uReadBytes(&pPayload, uDataRemaining, &uCurData, sizeof(uCurData));
     uCurPayload |= ((uint32)uCurData) << 24;
     uDataRemaining = uReadBytes(&pPayload, uDataRemaining, &uCurData, sizeof(uCurData));
     uCurPayload |= ((uint32)uCurData) << 16;
     uDataRemaining = uReadBytes(&pPayload, uDataRemaining, &uCurData, sizeof(uCurData));
     uCurPayload |= ((uint32)uCurData) << 8;
     uDataRemaining = uReadBytes(&pPayload, uDataRemaining, &uCurData, sizeof(uCurData));
     uCurPayload |= (uint32)uCurData;

     uCRCCalc = (uCRCCalc << 1) ^ constant ^ uCurPayload;
   }

   uDataRemaining = uReadBytes(&pPayload, uDataRemaining, &uCRCRead, sizeof(uCRCRead));

   if (uCRCCalc != uCRCRead)
   {
     MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DemuraFileCRCCheck: Mismatching CRC detected in Demura file CRC Read =0x%x, CRC Calculated = 0x%x\n", uCRCRead, uCRCCalc);
     eStatus = MDP_STATUS_INVALID_STATE;
   }

   return eStatus;
 }

 /****************************************************************************
 *
 ** FUNCTION: DemuraFileParseHeader()
 */
 /*!
 * \brief
 *   Read and check Demura Header .
 *
 * \param [in]     ppDemuraBuffer       - Demura data buffer
 * \param [in]     puDemuraDataSize     - Data size left in Demura buffer
 * \param [in]     uExpectedPanelID     - Expected Panel ID
 * \param [in]     eExpectedSprPackType - Expected SPR type.
 *
 * \retval MDP_Status
 *
 ****************************************************************************/
static MDP_Status DemuraFileParseHeader(uint8 **ppDemuraBuffer, uint32 *puDemuraDataSize, uint64 uExpectedPanelID, uint32 eExpectedSprPackType)
{
  MDP_Status          eStatus = MDP_STATUS_OK;

  if ((NULL ==  ppDemuraBuffer)   ||
      (NULL == *ppDemuraBuffer)   ||
      (NULL == puDemuraDataSize)  ||
      (*puDemuraDataSize < DEMURA_HEADER_SIZE))
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DemuraFileHeaderCheck: Bad parameters\n");
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else
  {
    uint8               uMagicNumberLE[] = "ARUM";
    uint32             *pU32LE           = (uint32*)uMagicNumberLE;
    uint8               uSPRPattern;
    uint8               uCRCRead;
    uint64              uPanelID;
    uint16              uDemuraVersion;
    uint32              uMagicNumRead;
    uint32              uDataRemaining   = *puDemuraDataSize;

    uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &uMagicNumRead, sizeof(uMagicNumRead));

    if (*pU32LE != uMagicNumRead)
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DemuraFileHeaderCheck: Demura Magic number checking failed!\n");
      eStatus = MDP_STATUS_INVALID_STATE;
    }
    else
    {
      uDataRemaining  = uReadBytes(ppDemuraBuffer, uDataRemaining, &uDemuraVersion, sizeof(uDemuraVersion));
      uDataRemaining  = uReadBytes(ppDemuraBuffer, uDataRemaining, &uPanelID,       sizeof(uPanelID));
      uSPRPattern     = ((uPanelID >> 8) & 0xf) + 1;
      uCRCRead        = (uint8)(uPanelID & 0xff);

      if (0x101 != uDemuraVersion)
      {
        MDP_Log_Message(MDP_LOGLEVEL_WARN, "ParseDemuraCorrection: Unknown Demura version = 0x%x\n", uDemuraVersion);
      }
      
      if (uPanelID != uExpectedPanelID)
      {
        MDP_Log_Message(MDP_LOGLEVEL_ERROR, "ParseDemuraCorrection: Panel ID mismatching!, uPanelID from file= 0x%16x, expecting 0x%16x\n",
                                             uPanelID, uExpectedPanelID);
        eStatus = MDP_STATUS_INVALID_STATE;
      }
      else if (uSPRPattern != eExpectedSprPackType)
      {
        MDP_Log_Message(MDP_LOGLEVEL_ERROR, "ParseDemuraCorrection: SPR setting mismatching!, uSPRPattern = %d, expecting = %d\n",
                                             uSPRPattern, eExpectedSprPackType);
        eStatus = MDP_STATUS_INVALID_STATE;
      }
      else
      {
        // Panel id CRC check
        uint8 uCRCCalc = 0;
        uint8 uCRCPoly = 0x9b;

        for (uint8 uCRCByte = 0; uCRCByte < 7; uCRCByte++)
        {
          uint8 uCurbyte = (uPanelID >> ((7 - uCRCByte) << 3)) & 0xFF;
          uCRCCalc ^= uCurbyte;
          for (uint8 uBit = 0; uBit < 8; uBit++)
          {
            uCRCCalc = ((uCRCCalc & 0x80) > 0x00) ? (uCRCCalc << 1) ^ uCRCPoly : (uCRCCalc << 1);
          }
        }

        if (uCRCCalc != uCRCRead)
        {
          MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DemuraFileHeaderCheck: Mismatch in panel ID CRC!, uCRCCalc=0x%x, uCRCRead=0x%x \n",
                                               uCRCCalc, uCRCRead);
          eStatus = MDP_STATUS_INVALID_STATE;
  
        }
      }
    }

    *puDemuraDataSize = uDataRemaining;
  }
  
  return eStatus;
}

/****************************************************************************
*
** FUNCTION: DemuraFileParseControl()
*/
/*!
* \brief
*   Read and check Demura Control.
*
* \param [in]     ppDemuraBuffer       - Demura data buffer
* \param [in]     puDemuraDataSize     - Data size left in Demura buffer
* \param [out]    psHALDemuraCfg       - Demura config
*
* \retval MDP_Status
*
****************************************************************************/
static MDP_Status DemuraFileParseControl(uint8 **ppDemuraBuffer, uint32 *puDemuraDataSize, HAL_MDP_DemuraDataConfigType *psHALDemuraCfg)
{
  MDP_Status    eStatus = MDP_STATUS_OK;
  uint32        uDataRemaining      = *puDemuraDataSize;

  if (uDataRemaining < DEMURA_CONTROL_1_SIZE)
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DemuraFileParseControl: Demura file does not have enough data %d\n", uDataRemaining);
    eStatus = MDP_STATUS_BUFFER_TOO_SMALL;
  }
  else
  {
    uint8   uTemp1;
    uint32  uTemp4;
    uint8   uMetricPreDemuraEn;
    uint8   uMetricPostDemuraEn;
    uint32  i;

    uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &uMetricPreDemuraEn,      sizeof(uMetricPreDemuraEn));
    uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &uMetricPostDemuraEn,     sizeof(uMetricPostDemuraEn));
    uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &psHALDemuraCfg->uCfg0En, sizeof(psHALDemuraCfg->uCfg0En));
    uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &psHALDemuraCfg->uCfg1En, sizeof(psHALDemuraCfg->uCfg1En));
    uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &uTemp1,                  sizeof(uTemp1));
    uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &uTemp4,                  sizeof(uTemp4));
    uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &psHALDemuraCfg->uCfg2En, sizeof(psHALDemuraCfg->uCfg2En));
    uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &psHALDemuraCfg->uCfg3En, sizeof(psHALDemuraCfg->uCfg3En));
    uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &psHALDemuraCfg->uCfg4En, sizeof(psHALDemuraCfg->uCfg4En));
    uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &psHALDemuraCfg->uCfg5En, sizeof(psHALDemuraCfg->uCfg5En));
    uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &uTemp4,                  sizeof(uTemp4));

    if ((uMetricPreDemuraEn) ||
        (uMetricPostDemuraEn))
    {
      uint8 uNumMetricLevels;

      if (uDataRemaining < 1)
      {
        MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DemuraFileParseControl: Demura file does not have enough data %d\n", uDataRemaining);
        eStatus = MDP_STATUS_BUFFER_TOO_SMALL;
      }
      else
      {
        uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &uNumMetricLevels, sizeof(uNumMetricLevels));

        if (uDataRemaining < ( uNumMetricLevels * 8 * sizeof(uint16) * ((uMetricPreDemuraEn ? 1 : 0) + (uMetricPostDemuraEn ? 1 : 0))) )
        {
          MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DemuraFileParseControl: Demura file does not have enough data %d\n", uDataRemaining);
          eStatus = MDP_STATUS_BUFFER_TOO_SMALL;
        }
        else
        {
          for (i = 0; i < uNumMetricLevels; i++)
          {
            uint16   uTemp2;

            if (uMetricPreDemuraEn)
            {
              uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &uTemp2, sizeof(uTemp2));
              uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &uTemp2, sizeof(uTemp2));
              uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &uTemp2, sizeof(uTemp2));
              uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &uTemp2, sizeof(uTemp2));
              uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &uTemp2, sizeof(uTemp2));
              uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &uTemp2, sizeof(uTemp2));
              uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &uTemp2, sizeof(uTemp2));
              uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &uTemp2, sizeof(uTemp2));
            }

            if (uMetricPostDemuraEn)
            {
              uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &uTemp2, sizeof(uTemp2));
              uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &uTemp2, sizeof(uTemp2));
              uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &uTemp2, sizeof(uTemp2));
              uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &uTemp2, sizeof(uTemp2));
              uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &uTemp2, sizeof(uTemp2));
              uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &uTemp2, sizeof(uTemp2));
              uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &uTemp2, sizeof(uTemp2));
              uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &uTemp2, sizeof(uTemp2));
            }
          }
        }
      }
    }

    *puDemuraDataSize = uDataRemaining;
  }

  return eStatus;
}
 
/****************************************************************************
*
** FUNCTION: DemuraFileParseCfg0()
*/
/*!
* \brief
*   Parse Demura config 0.
*
* \param [in]     ppDemuraBuffer       - Demura data buffer
* \param [in]     puDemuraDataSize     - Data size left in Demura buffer
* \param [out]    psHALDemuraCfg       - Demura config
* \param [in ]    eSprPackType         - SPR type
* \param [out]    pHFCData             - HFC data
* \param [out]    pHFCDataSize         - Size of HFC data
*
* \retval MDP_Status
*
****************************************************************************/
static MDP_Status DemuraFileParseCfg0(uint8** ppDemuraBuffer, uint32 *puDemuraDataSize, HAL_MDP_DemuraDataConfigType* psHALDemuraCfg, uint32 eSprPackType, uint8** pHFCData, uint32 *pHFCDataSize )
{
  MDP_Status    eStatus        = MDP_STATUS_OK;
  uint32        uDataRemaining = *puDemuraDataSize;

  if (uDataRemaining < DEMURA_CONFIG_0_SIZE_1)
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DemuraFileParseCfg0: Demura file does not have enough data %d\n", uDataRemaining);
    eStatus = MDP_STATUS_BUFFER_TOO_SMALL;
  }
  else
  {
    uint16        uPanelWidthR;
    uint16        uPanelWidthG;
    uint16        uPanelWidthB;
    uint16        uPanelHeightR;
    uint16        uPanelHeightG;
    uint16        uPanelHeightB;
    uint32        i;

    uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &uPanelWidthR, sizeof(uPanelWidthR));
    uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &uPanelWidthG, sizeof(uPanelWidthG));
    uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &uPanelWidthB, sizeof(uPanelWidthB));

    uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &uPanelHeightR, sizeof(uPanelHeightR));
    uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &uPanelHeightG, sizeof(uPanelHeightG));
    uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &uPanelHeightB, sizeof(uPanelHeightB));

    psHALDemuraCfg->uCfg01Param0Len = DEMURA_CFG1_PARAM_LEN;
    for (i = 0; i < DEMURA_CFG1_PARAM_LEN; i++)
    {
      uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &psHALDemuraCfg->uCfg01Param0[i], sizeof(psHALDemuraCfg->uCfg01Param0[i]));
    }

    if (psHALDemuraCfg->uCfg0En)
    {
      if (uDataRemaining < DEMURA_CONFIG_0_SIZE_2)
      {
        MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DemuraFileParseCfg0: Demura file does not have enough data %d\n", uDataRemaining);
        eStatus = MDP_STATUS_BUFFER_TOO_SMALL;
      }
      else
      {
        uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &psHALDemuraCfg->uC0Depth, sizeof(psHALDemuraCfg->uC0Depth));
        uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &psHALDemuraCfg->uC1Depth, sizeof(psHALDemuraCfg->uC1Depth));
        uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &psHALDemuraCfg->uC2Depth, sizeof(psHALDemuraCfg->uC2Depth));

        if ((0 == psHALDemuraCfg->uC0Depth)||
            (0 == psHALDemuraCfg->uC1Depth)||
            (0 == psHALDemuraCfg->uC2Depth)||
            (psHALDemuraCfg->uC0Depth > 8) ||
            (psHALDemuraCfg->uC1Depth > 8) ||
            (psHALDemuraCfg->uC2Depth > 8))
        {
          MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DemuraFileParseCfg0: Incorrect bit depth: %d %d %d\n",  psHALDemuraCfg->uC0Depth, psHALDemuraCfg->uC1Depth, psHALDemuraCfg->uC2Depth);
          eStatus = MDP_STATUS_INVALID_STATE;
        }
        else
        {
          uint32 uPanelWidth            = ((HAL_MDP_SPR_PACK_PENTILE == eSprPackType) ||
                                           (HAL_MDP_SPR_BYPASS       == eSprPackType) ) ? uPanelWidthG : uPanelWidthG * 3 / 2;;
          uint32 uHFCBitPerPixel        = MDP_GET_PIXELFMTMAP(HAL_MDP_PIXEL_FORMAT_ABGR_8888_32BPP).uBitsPerPixel;
          uint32 uHFCBytePerPixel       = uHFCBitPerPixel / 8 ;
          uint32 uHalfWidth             = uPanelWidth / 2;
          uint64 uHalfWidthTotalBits;
          uint32 uHFCSurfaceFullWidth;
          uint32 uHFCSurfaceHalfWidth;
          uint32 uFullHFCSizeInByte;

          // HFC data is divided into half, and there could have padding for 32 bit alignment so that right half to start in DWORD aligned address.
          if (HAL_MDP_SPR_PACK_PENTILE == eSprPackType)
          {
            uint32 uHalfRedWidth    = uHalfWidth / 2;   // Red channel is down sampled by 2
            uint32 uHalfBlueWidth   = uHalfWidth / 2;   // Blue channel is down sampled by 2
            uint32 uHalfGreenWidth  = uHalfWidth;       // Green channel is fully sampled

            // Total bits of half width = green sample # x green bpp  +  red sample # x red bpp  + blue sample # x blue bpp  
            uHalfWidthTotalBits     = (uHalfGreenWidth * psHALDemuraCfg->uC1Depth) +
                                      (uHalfRedWidth   * psHALDemuraCfg->uC0Depth) +
                                      (uHalfBlueWidth  * psHALDemuraCfg->uC2Depth);
          }
          else
          {
            uHalfWidthTotalBits = uHalfWidth * (psHALDemuraCfg->uC0Depth + psHALDemuraCfg->uC1Depth + psHALDemuraCfg->uC2Depth);
          }

          // Add padding for 32 bit alignment for half width total bits.
          uHalfWidthTotalBits            = MDP_ALIGN(uHalfWidthTotalBits, uHFCBitPerPixel);

          psHALDemuraCfg->uDisplayWidth  = uPanelWidthG;
          psHALDemuraCfg->uDisplayHeight = uPanelHeightG;
          psHALDemuraCfg->uPentile       = (HAL_MDP_SPR_PACK_PENTILE == eSprPackType) ? 1 : 0;
          psHALDemuraCfg->uHFCWidth      = (uHalfWidthTotalBits / uHFCBitPerPixel)  * 2;                    // Total pixel number of whole width.
          uFullHFCSizeInByte             = uPanelHeightG * psHALDemuraCfg->uHFCWidth * uHFCBytePerPixel;    // Total byte of whole HFC data, which should be read from demura file

          // HFC data surface needs to be 32 pixel alignment on half width due to HW fetching requirement. 
          uHFCSurfaceHalfWidth            = MDP_ALIGN(psHALDemuraCfg->uHFCWidth / 2, uHFCBitPerPixel);   // Add padding for 32 pixel alignment.
          uHFCSurfaceFullWidth            = uHFCSurfaceHalfWidth * 2;                                       // Total pixel number of HFC surface width. 

          psHALDemuraCfg->uCfg0Param1Len = DEMURA_CFG0_PARAM_LEN;
          for (i = 0; i < DEMURA_CFG0_PARAM_LEN; i++)
          {
            uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &psHALDemuraCfg->uCfg0Param1[i], sizeof(psHALDemuraCfg->uCfg0Param1[i]));
          }

          psHALDemuraCfg->uCfg0Param0Len = DEMURA_CFG0_PARAM_LEN;
          for (i = 0; i < DEMURA_CFG0_PARAM_LEN; i++)
          {
            uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &psHALDemuraCfg->uCfg0Param0[i], sizeof(psHALDemuraCfg->uCfg0Param0[i]));
          }

          psHALDemuraCfg->uCfg0Param4Len = DEMURA_CFG0_PARAM_LEN;
          for (i = 0; i < DEMURA_CFG0_PARAM_LEN; i++)
          {
            uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &psHALDemuraCfg->uCfg0Param4[i], sizeof(psHALDemuraCfg->uCfg0Param4[i]));
          }

          if (uDataRemaining < (1 << psHALDemuraCfg->uC0Depth) * ( sizeof(psHALDemuraCfg->uCfg0Param2C0[0]) +
                                                                   sizeof(psHALDemuraCfg->uCfg0Param2C1[0]) +
                                                                   sizeof(psHALDemuraCfg->uCfg0Param2C2[0])))
          {
            MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DemuraFileParseCfg0: Demura file does not have enough data %d\n", uDataRemaining);
            eStatus = MDP_STATUS_BUFFER_TOO_SMALL;
          }
          else
          {
            psHALDemuraCfg->uCfg0Param3Len = (1 << psHALDemuraCfg->uC0Depth);
            for (i = 0; i < (1 << psHALDemuraCfg->uC0Depth); i++)
            {
              uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &psHALDemuraCfg->uCfg0Param2C0[i], sizeof(psHALDemuraCfg->uCfg0Param2C0[i]));
            }
            for (i = 0; i < (1 << psHALDemuraCfg->uC1Depth); i++)
            {
              uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &psHALDemuraCfg->uCfg0Param2C1[i], sizeof(psHALDemuraCfg->uCfg0Param2C1[i]));
            }
            for (i = 0; i < (1 << psHALDemuraCfg->uC2Depth); i++)
            {
              uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &psHALDemuraCfg->uCfg0Param2C2[i], sizeof(psHALDemuraCfg->uCfg0Param2C2[i]));
            }

            if (uDataRemaining < (uFullHFCSizeInByte + sizeof(psHALDemuraCfg->uCfg0Param3C0)
                                                     + sizeof(psHALDemuraCfg->uCfg0Param3C1)
                                                     + sizeof(psHALDemuraCfg->uCfg0Param3C2)))
            {
              MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DemuraFileParseCfg0: Demura file does not have enough data %d\n", uDataRemaining);
              eStatus = MDP_STATUS_BUFFER_TOO_SMALL;
            }
            else if (MDP_STATUS_OK != (eStatus = MDP_GetMemoryRegionInfo((uint8*)"Display Demura", pHFCData, pHFCDataSize)))
            {
              MDP_Log_Message(MDP_LOGLEVEL_WARN, "DemuraFileParseCfg0: Get display demura region failed!\n");
              eStatus = MDP_STATUS_FAILED;
            }
            else                                                                                             
            {
              MDP_OSAL_MEMZERO(*pHFCData, *pHFCDataSize);

              // The HFC data in configure file is tightly packed, while the HFC buffer fed to DMA needs to be snapped to 32-bit boundary
              // for HW access. If the width is not aligned, 0 padding is added to each line.
              if (psHALDemuraCfg->uHFCWidth == uHFCSurfaceFullWidth)
              {
                MDP_OSAL_MEMCPY(*pHFCData, *ppDemuraBuffer, uFullHFCSizeInByte);
              }
              else
              {
                uint32 uHFCConfigSrcStride = psHALDemuraCfg->uHFCWidth * uHFCBytePerPixel;
                uint32 uHFCConfigDstStride = uHFCSurfaceFullWidth      * uHFCBytePerPixel;

                for (i = 0; i < psHALDemuraCfg->uDisplayHeight; i++)
                {
                  MDP_OSAL_MEMCPY(*pHFCData + i * uHFCConfigDstStride, *ppDemuraBuffer + i * uHFCConfigSrcStride, uHFCConfigSrcStride);
                }
              }

              *ppDemuraBuffer += uFullHFCSizeInByte;
              uDataRemaining  -= uFullHFCSizeInByte;

              psHALDemuraCfg->uCfg0Param3Len = DEMURA_CFG0_PARAM_LEN;
              for (i = 0; i < DEMURA_CFG0_PARAM_LEN; i++) 
              {
                uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &psHALDemuraCfg->uCfg0Param3C0[i], sizeof(psHALDemuraCfg->uCfg0Param3C0[i]));
              }
              for (i = 0; i < DEMURA_CFG0_PARAM_LEN; i++) 
              {
                uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &psHALDemuraCfg->uCfg0Param3C1[i], sizeof(psHALDemuraCfg->uCfg0Param3C1[i]));
              }
              for (i = 0; i < DEMURA_CFG0_PARAM_LEN; i++)
              {
                uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &psHALDemuraCfg->uCfg0Param3C2[i], sizeof(psHALDemuraCfg->uCfg0Param3C2[i]));
              }
            }
          }
        }
      }
    } 

    *puDemuraDataSize = uDataRemaining;
  }

  return eStatus;
}

/****************************************************************************
*
** FUNCTION: DemuraFileParseCfg1()
*/
/*!
* \brief
*   Parse Demura config 1.
*
* \param [in]     ppDemuraBuffer       - Demura data buffer
* \param [in]     puDemuraDataSize     - Data size left in Demura buffer
* \param [out]    psHALDemuraCfg       - Demura config
* \param [in/out] pReadIndex           - Current Demura buffer read index
*
* \retval MDP_Status
*
****************************************************************************/
static MDP_Status DemuraFileParseCfg1(uint8** ppDemuraBuffer, uint32 *puDemuraDataSize, HAL_MDP_DemuraDataConfigType* psHALDemuraCfg)
{
  MDP_Status    eStatus        = MDP_STATUS_OK;
  uint32        uDataRemaining = *puDemuraDataSize;

  if (psHALDemuraCfg->uCfg1En)
  {
    uint32 i;

    if (uDataRemaining < ( sizeof(psHALDemuraCfg->uCfg1HighIdx)   + 
                           sizeof(psHALDemuraCfg->uCfg1LowIdx)    +
                           sizeof(psHALDemuraCfg->uCfg1Param0C0)  + 
                           sizeof(psHALDemuraCfg->uCfg1Param0C1)  +
                           sizeof(psHALDemuraCfg->uCfg1Param0C2)))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DemuraFileParseCfg1: Demura file does not have enough data %d\n", uDataRemaining);
      eStatus = MDP_STATUS_NO_RESOURCES;
    }
    else
    {
      uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &psHALDemuraCfg->uCfg1HighIdx, sizeof(psHALDemuraCfg->uCfg1HighIdx));
      uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &psHALDemuraCfg->uCfg1LowIdx,  sizeof(psHALDemuraCfg->uCfg1LowIdx));

      psHALDemuraCfg->uCfg1Param0Len = DEMURA_CFG1_PARAM0_LEN;
      for (i = 0; i < DEMURA_CFG1_PARAM0_LEN; i++)
      {
        uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &psHALDemuraCfg->uCfg1Param0C0[i], sizeof(psHALDemuraCfg->uCfg1Param0C0[i]));
        uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &psHALDemuraCfg->uCfg1Param0C1[i], sizeof(psHALDemuraCfg->uCfg1Param0C1[i]));
        uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &psHALDemuraCfg->uCfg1Param0C2[i], sizeof(psHALDemuraCfg->uCfg1Param0C2[i]));
      }
    }
  }

  return eStatus;
}

/****************************************************************************
*
** FUNCTION: DemuraFileParseCfg5()
*/
/*!
* \brief
*   Parse Demura config 5.
*
* \param [in]     ppDemuraBuffer       - Demura data buffer
* \param [in]     puDemuraDataSize     - Data size left in Demura buffer
* \param [out]    psHALDemuraCfg       - Demura config
* \param [in/out] pReadIndex           - Current Demura buffer read index
*
* \retval MDP_Status
*
****************************************************************************/
static MDP_Status DemuraFileParseCfg5(uint8** ppDemuraBuffer, uint32 *puDemuraDataSize, HAL_MDP_DemuraDataConfigType* psHALDemuraCfg)
{
  MDP_Status    eStatus        = MDP_STATUS_OK;
  uint32        uDataRemaining = *puDemuraDataSize;

  if (psHALDemuraCfg->uCfg5En)
  {
    if (uDataRemaining < (sizeof(psHALDemuraCfg->uCfg5Param0) + sizeof(psHALDemuraCfg->uCfg5Param1)))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DemuraFileParseCfg5: Demura file does not have enough data %d\n", uDataRemaining);
      eStatus = MDP_STATUS_NO_RESOURCES;
    }
    else
    {
      uint32 i;

      psHALDemuraCfg->uCfg5Param0Len = DEMURA_CFG5_PARAM01_LEN;
      for (i = 0; i < DEMURA_CFG5_PARAM01_LEN; i++)
      {
        uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &psHALDemuraCfg->uCfg5Param0[i], sizeof(psHALDemuraCfg->uCfg5Param0[i]));
      }

      psHALDemuraCfg->uCfg5Param1Len = DEMURA_CFG5_PARAM01_LEN;
      for (i = 0; i < DEMURA_CFG5_PARAM01_LEN; i++)
      {
        uDataRemaining = uReadBytes(ppDemuraBuffer, uDataRemaining, &psHALDemuraCfg->uCfg5Param1[i], sizeof(psHALDemuraCfg->uCfg5Param1[i]));
      }
    }
  }

  return eStatus;
}
/****************************************************************************
 *
 ** FUNCTION: ParseDemuraCorrection()
 */
 /*!
 * \brief
 *   Read and move data pointer by 8 byte.
 *
 * \param [in]  pPanelConfig     - The display configuration to setup
 * \param [in]  pDemuraBuffer    - Demura data buffer
 * \param [in]  uDemuraDataSize  - Size of the Demura data
 * \param [out] psHALDemuraCfg   - Demura config 
 *
 * \retval MDP_Status
 *
 ****************************************************************************/
 static MDP_Status ParseDemuraCorrection(MDP_Panel_AttrType* pPanelConfig, uint8 *pDemuraBuffer, uint32 uDemuraDataSize, HAL_MDP_DemuraDataConfigType *psHALDemuraCfg)
{
  MDP_Status    eStatus       = MDP_STATUS_OK;
  uint8        *pHFCdata      = NULL;
  uint32        uHFCDataSize  = 0;

  if ((NULL == pPanelConfig)  ||
      (NULL == pDemuraBuffer) ||
      (NULL == psHALDemuraCfg))
  {
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else if (MDP_STATUS_OK != (eStatus = DemuraFileCRCCheck(pDemuraBuffer, uDemuraDataSize)))
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "ParseDemuraCorrection: DemuraFileCRCCheck failed eStatus = 0x%x\n", eStatus);
  }
  else if (MDP_STATUS_OK != (eStatus = DemuraFileParseHeader(&pDemuraBuffer, &uDemuraDataSize,
                                       pPanelConfig->uAttrs.sDsi.sDemuraConfig.uDemuraPanelID, pPanelConfig->uAttrs.sDsi.sDemuraConfig.eSprPackType)))
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "ParseDemuraCorrection: DemuraFileHeaderCheck failed eStatus = 0x%x\n", eStatus);
  }
  else if (MDP_STATUS_OK != (eStatus = DemuraFileParseControl(&pDemuraBuffer, &uDemuraDataSize, psHALDemuraCfg)))
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "ParseDemuraCorrection: DemuraFileParseControl failed eStatus = 0x%x\n", eStatus);
  }
  else if (MDP_STATUS_OK != (eStatus = DemuraFileParseCfg0(&pDemuraBuffer, &uDemuraDataSize, psHALDemuraCfg,
                                       pPanelConfig->uAttrs.sDsi.sDemuraConfig.eSprPackType, &pHFCdata, &uHFCDataSize)))
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "ParseDemuraCorrection: DemuraFileParseCfg0 failed eStatus = 0x%x\n", eStatus);
  }
  else if (MDP_STATUS_OK != (eStatus = DemuraFileParseCfg1(&pDemuraBuffer, &uDemuraDataSize, psHALDemuraCfg)))
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "ParseDemuraCorrection: DemuraFileParseCfg1 failed eStatus = 0x%x\n", eStatus);
  }
  else if (MDP_STATUS_OK != (eStatus = DemuraFileParseCfg5(&pDemuraBuffer, &uDemuraDataSize, psHALDemuraCfg)))
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "ParseDemuraCorrection: DemuraFileParseCfg5 failed eStatus = 0x%x\n", eStatus);
  }
  else
  {
    if (NULL != pPanelConfig->uAttrs.sDsi.sDemuraConfig.pDemuraHFCData)
    {
      MDP_OSAL_FREE(pPanelConfig->uAttrs.sDsi.sDemuraConfig.pDemuraHFCData);
    }

    pPanelConfig->uAttrs.sDsi.sDemuraConfig.uDemuraHFCSize = uHFCDataSize;
    pPanelConfig->uAttrs.sDsi.sDemuraConfig.pDemuraHFCData = pHFCdata;
  }

  return eStatus;
}

/****************************************************************************
*
** FUNCTION: BuildDemuraFileString()
*/
/*!
* \brief
*   Build Demura file name string from Demura Panel ID, format is "demura_config_<demurapanelId>" 
*
* \param [in] pDemuraFileName - buffer for Demura file name
* \param [in] uFileNameLen    - File name buffer length
* \param [in] uDemuraPanelID  - Demura Panel ID
*
* \retval MDP_Status
*
****************************************************************************/
static MDP_Status BuildDemuraFileString(CHAR8* pDemuraFileName, uint32 uFileNameLen, uint64 uDemuraPanelID)
{
  MDP_Status  eStatus     = MDP_STATUS_OK;
 
  if ((NULL == pDemuraFileName)||
      (0    == uDemuraPanelID))
  {
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else
  {
    CHAR8    sTimeStampFileName[DISP_DEMURA_FILE_NAME_LEN];
    uint8   *pTimeStampBuffer       = NULL;
    uint32   uTimeStampBufferSize   = 0;
    uint32   uTimeStapRetSize       = 0;

    // Generate DemuraTn Time stamp file name
    snprintf(sTimeStampFileName, sizeof(sTimeStampFileName), "demura_elapsedtime_%016llx", uDemuraPanelID);

    // Try to read time stamp value 
    if (MDP_STATUS_OK != MDP_Display_LoadFileEx(DISP_DEMURA_FV_LABEL, sTimeStampFileName, (UINT8**)&pTimeStampBuffer, &uTimeStampBufferSize, 0, &uTimeStapRetSize, 0))
    {
      // Fall back to original file name without time stamp
      snprintf(pDemuraFileName, uFileNameLen, "demura_config_%016llx", uDemuraPanelID);
    }
    else if ((uTimeStampBufferSize > DISP_DEMURA_TIMESTAMP_LEN) ||
             (NULL                 == pTimeStampBuffer))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "BuildDemuraFileString: invalid demura time stamp value\n");
      eStatus = MDP_STATUS_NOT_SUPPORTED;
    }
    else
    {
      snprintf(pDemuraFileName, uFileNameLen, "demura_config_%016llx_%s", uDemuraPanelID, pTimeStampBuffer);
    }

    if (NULL != pTimeStampBuffer)
    {
      MDP_OSAL_FREE(pTimeStampBuffer);
    }
  }
  
  return eStatus;
}


/****************************************************************************
*
** FUNCTION: ReadDemuraPanelID()
*/
/*!
* \brief
*  Read Demura panel ID from panel
*
* \param [in] ReadDemuraPanelID       - Display ID
* \param [in] pDemuraReadCmd          - Demura panel id read command
* \param [in] uDemuraReadCmdLen       - Demura panel id read command length
* \param [in] puDemuraPanelID         - Demura panel ID
*
* \retval MDP_Status
*
****************************************************************************/
static MDP_Status ReadDemuraPanelID(MDP_Display_IDType     eDisplayId,
                                    uint8                 *pDemuraReadCmd,
                                    uint32                 uDemuraReadCmdLen,
                                    uint64                *puDemuraPanelID)
{
  MDP_Status Status = MDP_STATUS_NOT_SUPPORTED;

  if ((NULL == pDemuraReadCmd) ||
      (NULL == puDemuraPanelID)||
      (uDemuraReadCmdLen < 2))
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "ReadDemuraPanelID: Invalid parameters!\n");
  }
  else if (MDP_STATUS_OK == DSIDriver_MinimalInit(eDisplayId, 0))          // do minimal DSI init
  {
    uint32                readSize    = sizeof(uint64);

    // clear Demura panel ID
    *puDemuraPanelID = 0;

    // clear the readback buffer
    MDP_OSAL_MEMZERO(puDemuraPanelID, readSize);
    Status = DSIDriver_Read(eDisplayId,
                            pDemuraReadCmd[0],
                            &pDemuraReadCmd[1],
                            2,
                            puDemuraPanelID,
                            &readSize,
                            0);

    // Close the DSI context opened in DSIDriver_MinimalInit()
    DSIDriver_Close(eDisplayId);
  }

  return Status;
}
/****************************************************************************
*
** FUNCTION: SetupCroppingRectangle()
*/
/*!
* \brief
*   Local helper function to update the cropping rectangle information in Dual pipe/Single pipe scenario
*
* \param  [in] pPanelConfig             - Panel configuration
* \param  [in] pSrcRect                 - The source surface information
* \param  [in\Out] pCropRectInfo        - Cropping rectangle information updated in this function
* \param  [in] uPipeIndex               - Pipe index (only used in case of Dual path)
*
*
* \retval void
*
****************************************************************************/
static MDP_Status SetupDemuraRectangle(MDP_Panel_AttrType        *pPanelConfig,
                                       MDPRectType               *pSrcRect,
                                       HAL_MDP_CropRectangleType *pCropRectInfo,
                                       uint32                     uPipeIndex,
                                       uint32                     uFlag)
{
  MDP_Status eStatus = MDP_STATUS_OK;

  if ((NULL == pPanelConfig) ||
      (NULL == pSrcRect)     ||
      (NULL == pCropRectInfo))
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPDemuraSetupConfig: Bad parameters\n");
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else
  {
    uint32   uSrcWidth   = pSrcRect->uWidth;
    uint32   uSrcHeight  = pSrcRect->uHeight;
    uint32   uDestPosX   = 0;
    uint32   uDestPosY   = 0;
    uint32   uDestWidth  = uSrcWidth;
    uint32   uDestHeight = uSrcHeight;

    if (MDP_DUALPIPE_NUM_MIXERS == pPanelConfig->uNumMixers)
    {
      // We split the source surface into two equal halves
      // Left layer displays the left half and the Right layer displays right half 
      // We need to find the Layer at  the current index is left layer or right layer
      HAL_MDP_LayerMixerId eLayerMixerId      = pPanelConfig->sDisplayControlPath[uPipeIndex].eLayerMixerId;
      HAL_MDP_LayerMixerId eOtherLayerMixerId = pPanelConfig->sDisplayControlPath[(uPipeIndex == 0) ? 1 : 0].eLayerMixerId;
      bool32               bLeft              = (eLayerMixerId < eOtherLayerMixerId) ? TRUE : FALSE;

      pCropRectInfo->sSrcRectConfig.uPosX           = (MDP_ROTATE_180 == pPanelConfig->ePhysPanelOrientation) ?
                                                      ((bLeft == TRUE) ? (uSrcWidth / 2) : 0) :
                                                      ((bLeft == TRUE) ? 0 : (uSrcWidth / 2));
      pCropRectInfo->sSrcRectConfig.uPosY           = 0;
      pCropRectInfo->sSrcRectConfig.uWidthInPixels  = (uSrcWidth / 2);
      pCropRectInfo->sSrcRectConfig.uHeightInPixels = uSrcHeight;

      // Destination rect
      pCropRectInfo->sDstRectConfig.uPosX           = (bLeft == TRUE) ? uDestPosX : (uSrcWidth / 2);
      pCropRectInfo->sDstRectConfig.uPosY           = uDestPosY;
      pCropRectInfo->sDstRectConfig.uWidthInPixels  = (uDestWidth / 2);
      pCropRectInfo->sDstRectConfig.uHeightInPixels = uDestHeight;
    }
    else
    {
      // Source fetch
      pCropRectInfo->sSrcRectConfig.uPosX           = 0;
      pCropRectInfo->sSrcRectConfig.uPosY           = 0;
      pCropRectInfo->sSrcRectConfig.uWidthInPixels  = uSrcWidth;
      pCropRectInfo->sSrcRectConfig.uHeightInPixels = uSrcHeight;

      // Destination rect
      pCropRectInfo->sDstRectConfig.uPosX           = uDestPosX;
      pCropRectInfo->sDstRectConfig.uPosY           = uDestPosY;
      pCropRectInfo->sDstRectConfig.uWidthInPixels  = uDestWidth;
      pCropRectInfo->sDstRectConfig.uHeightInPixels = uDestHeight;
    }
  }

  return eStatus;
}

/****************************************************************************
*
** FUNCTION: GetDemuraPipe()
*/
/*!
* \brief
*  Get source pipe for Demura HFC data
*
* \param [in] eDisplayId       - Display ID
* \param [in] uLMIndex         - Layer mixer index
*
* \retval HAL_MDP_SourcePipeId
*
****************************************************************************/
static HAL_MDP_SourcePipeId GetDemuraPipe(MDP_Display_IDType eDisplayId, uint32 uLMIndex)
{
  HAL_MDP_SourcePipeId  eDemuraPipeId     = HAL_MDP_SOURCE_PIPE_NONE;
  MDP_ResourceList      *pResList         = NULL;
  
  if ((eDisplayId >= MDP_DISPLAY_MAX) ||
      (uLMIndex   >= MDP_DUALPIPE_NUM_MIXERS))
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "GetDemuraPipe: Invalid input!\n");
  }
  else if ((MDP_STATUS_OK != MDPGetMDPResourceList(&pResList)) ||
           (NULL          == pResList->pDemuraPipeMapCfg))
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "GetDemuraPipe: Demura is not supported!\n");
  }
  else
  {
    for (uint32 i = 0; pResList->pDemuraPipeMapCfg[i].eDisplayId != MDP_DISPLAY_MAX; i++)
    {
      if (eDisplayId == pResList->pDemuraPipeMapCfg[i].eDisplayId)
      {
        eDemuraPipeId = pResList->pDemuraPipeMapCfg[i].eSourcePipeMapping[uLMIndex];
        break;
      }
    }
  }

  return eDemuraPipeId;
}

static MDP_Status CommitDemuraPipes(HAL_MDP_ControlPathId eControlPathId, HAL_MDP_SourcePipeId eDemuraPipeId, HAL_MDP_DemuraId eDemuraId)
{
  MDP_Status                    eStatus                                      = MDP_STATUS_OK;
  HAL_MDP_ControlPathFlushType  sFlushType;
  const HAL_ControlPath_Flush   aSourcePipeFlushMap[HAL_MDP_SOURCE_PIPE_MAX] = {
     HAL_CONTROL_PATH_FLUSH_NONE,     // HAL_MDP_SOURCE_PIPE_NONE
     HAL_CONTROL_PATH_FLUSH_VIG0,     // HAL_MDP_SOURCE_PIPE_VIG_0
     HAL_CONTROL_PATH_FLUSH_VIG1,     // HAL_MDP_SOURCE_PIPE_VIG_1,
     HAL_CONTROL_PATH_FLUSH_VIG2,     // HAL_MDP_SOURCE_PIPE_VIG_2,
     HAL_CONTROL_PATH_FLUSH_VIG3,     // HAL_MDP_SOURCE_PIPE_VIG_3,

     HAL_CONTROL_PATH_FLUSH_DMA0,     // HAL_MDP_SOURCE_PIPE_DMA_0           = HAL_MDP_SOURCE_PIPE_DMA_BASE,
     HAL_CONTROL_PATH_FLUSH_DMA1,     // HAL_MDP_SOURCE_PIPE_DMA_1,
     HAL_CONTROL_PATH_FLUSH_DMA2,     // HAL_MDP_SOURCE_PIPE_DMA_2,
     HAL_CONTROL_PATH_FLUSH_DMA3,     // HAL_MDP_SOURCE_PIPE_DMA_3,
     HAL_CONTROL_PATH_FLUSH_DMA4,     // HAL_MDP_SOURCE_PIPE_DMA_4,
     HAL_CONTROL_PATH_FLUSH_DMA5,     // HAL_MDP_SOURCE_PIPE_DMA_5,

     HAL_CONTROL_PATH_FLUSH_DMA0,     // HAL_MDP_SOURCE_PIPE_DMA_0_REC1      = HAL_MDP_SOURCE_PIPE_SMART_DMA_BASE,
     HAL_CONTROL_PATH_FLUSH_DMA1,     // HAL_MDP_SOURCE_PIPE_DMA_1_REC1,
     HAL_CONTROL_PATH_FLUSH_DMA2,     // HAL_MDP_SOURCE_PIPE_DMA_2_REC1,
     HAL_CONTROL_PATH_FLUSH_DMA3,     // HAL_MDP_SOURCE_PIPE_DMA_3_REC1,
     HAL_CONTROL_PATH_FLUSH_NONE,     // HAL_MDP_SOURCE_PIPE_DMA_4_REC1,
  };

  MDP_OSAL_MEMZERO(&sFlushType, sizeof(HAL_MDP_ControlPathFlushType));

  if (eDemuraPipeId >= HAL_MDP_SOURCE_PIPE_MAX)
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPDemuraSetupConfig: Unsupported Source Pipe %d\n", eDemuraPipeId);
    eStatus = MDP_STATUS_FAILED;
  }
  else
  {

    sFlushType.uFlushModules |= aSourcePipeFlushMap[eDemuraPipeId];

    if (HAL_MDSS_STATUS_SUCCESS != HAL_MDP_ControlPath_Commit(eControlPathId,
                                                             &sFlushType,
                                                              HAL_MDP_INTERFACE_TYPE_PHYSICAL_CONNECT,
                                                              0))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPDemuraSetupConfig: HAL_MDP_ControlPath_Commit failed!\n");
      eStatus = MDP_STATUS_FAILED;
    }
  }

  return eStatus;
}

/*------------------------------------------------------------------------------------------
 * Public Functions
 *------------------------------------------------------------------------------------------*/

/****************************************************************************
*
** FUNCTION: MDPDemuraSetupConfig()
*/
/*!
* \brief
*  Setup Demura configure
*
* \param [in] pPanelConfig       - The display configuration to setup
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPDemuraSetupConfig(MDP_Panel_AttrType *pPanelConfig)
{
  MDP_Status              eStatus         = MDP_STATUS_OK;

  if ((NULL == pPanelConfig) ||
      (NULL == pPanelConfig->uAttrs.sDsi.sDemuraConfig.psDemuraConfig))
  { 
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPDemuraSetupConfig: Bad parameters\n");
    eStatus = MDP_STATUS_BAD_PARAM;
  }
 else
  {
    HAL_MDP_SourcePipeConfigType              sSourcePipeConfig;
    HAL_MDP_CropRectangleType                 sCropRectInfo;
    HAL_MDP_SurfaceAttrType                   sSurfaceInfo;
    HAL_MDP_PixelExtLayerConfigType           sPixelExtConfig;
    HAL_MDP_FetchModeConfigType               sFetchModeConfig;
    MDPRectType                               sSrcRect;
    uint32                                    uI;

    for (uI = 0; uI < pPanelConfig->uNumMixers; uI++)
    {
      HAL_MDP_LayerType       eLayerType    = HAL_MDP_LAYER_TYPE_DMA;
      HAL_MDP_SourcePipeId    eDemuraPipeId = HAL_MDP_SOURCE_PIPE_NONE;
      HAL_MDP_DemuraId        eDemuraId     = HAL_MDP_DEMURA_NONE;
      uint32                  uHFCWidth     = pPanelConfig->uAttrs.sDsi.sDemuraConfig.psDemuraConfig->uHFCWidth;

      if (HAL_MDP_SOURCE_PIPE_NONE == (eDemuraPipeId = GetDemuraPipe(pPanelConfig->eDisplayId, uI)))
      {
        continue;
      }
      else if (HAL_MDP_SOURCE_PIPE_DMA_3 == eDemuraPipeId)
      {
        eDemuraId = HAL_MDP_DEMURA_0;
      }
      else
      {
        eDemuraId = HAL_MDP_DEMURA_1;
      }

      MDP_OSAL_MEMZERO(&sSurfaceInfo, sizeof(HAL_MDP_SurfaceAttrType));
      sSurfaceInfo.ePixelFormat                           = HAL_MDP_PIXEL_FORMAT_ARGB_8888_32BPP;
      sSurfaceInfo.uWidthInPixel                          = uHFCWidth;
      sSurfaceInfo.uHeightInPixel                         = pPanelConfig->uDisplayHeight;
      sSurfaceInfo.uPlanes.sRgb.uStrideInBytes            = (uHFCWidth/2 + 32 - (uHFCWidth/2)%32) * 8;
      sSurfaceInfo.uPlanes.sRgb.sDeviceAddress.iQuadPart  = (int64)pPanelConfig->uAttrs.sDsi.sDemuraConfig.pDemuraHFCData;

      MDP_OSAL_MEMZERO(&sPixelExtConfig, sizeof(HAL_MDP_PixelExtLayerConfigType));
      MDP_OSAL_MEMZERO(&sCropRectInfo,   sizeof(HAL_MDP_CropRectangleType));
      MDP_OSAL_MEMZERO(&sSrcRect,        sizeof(MDPRectType));
      sSrcRect.uHeight  = sSurfaceInfo.uHeightInPixel;
      sSrcRect.uWidth   = sSurfaceInfo.uWidthInPixel;
      
      if (MDP_STATUS_OK != (eStatus = SetupDemuraRectangle(pPanelConfig, &sSrcRect, &sCropRectInfo, uI, 1)))
      {
        MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPDemuraSetupConfig: SetupDemuraRectangle failed 0x%x\n", eStatus);
      }
      else if (MDP_STATUS_OK != (eStatus = ScaleHelperConfigure(&sPixelExtConfig, &sCropRectInfo, pPanelConfig, 0x0)))
      {
        MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPDemuraSetupConfig: ScaleHelperConfigure failed 0x%x\n", eStatus);
      }
      else
      {
        HAL_MDP_ControlPathConfigType             sControlPathConfig;
        HAL_MDP_ControlPath_FetchPipeActiveType   sFetchPipeActiveCfg;
        HAL_MDP_MultiRectConfigType               sMutliRectConfig;
        HAL_MDP_ControlPath_DSPPFlushType         sDSPPFlushConfig;

        MDP_OSAL_MEMZERO(&sSourcePipeConfig, sizeof(HAL_MDP_SourcePipeConfigType));
        sSourcePipeConfig.psSurfaceInfo         = &sSurfaceInfo;
        sSourcePipeConfig.psCropRectInfo        = &sCropRectInfo;
        sSourcePipeConfig.psPixelExtLayerConfig = &sPixelExtConfig;

        if (sSrcRect.uWidth != sCropRectInfo.sSrcRectConfig.uWidthInPixels)
        {
          // Set MulitRect
          MDP_OSAL_MEMZERO(&sMutliRectConfig, sizeof(sMutliRectConfig));
          sMutliRectConfig.bEnable            = TRUE;
          sMutliRectConfig.eMultiRectType     = HAL_MDP_MULTIRECT_PARALLEL_FETCH;
          sSourcePipeConfig.psMultiRectConfig = &sMutliRectConfig;
        }

        // If the panel is inverted we need to flip the source fetch 180 degrees.
        if (MDP_ROTATE_180 == pPanelConfig->ePhysPanelOrientation)
        {
          // Flip vertically and horizontally to get 180 rotation.  
          MDP_OSAL_MEMZERO(&sFetchModeConfig, sizeof(HAL_MDP_FetchModeConfigType));
          sFetchModeConfig.eFetchConfigType = HAL_MDP_FETCH_DIRECTION_DOWN_TO_UP | HAL_MDP_FETCH_DIRECTION_RIGHT_TO_LEFT;

          sSourcePipeConfig.psFetchInfo = &sFetchModeConfig;
        }

        MDP_OSAL_MEMZERO(&sControlPathConfig,   sizeof(HAL_MDP_ControlPathConfigType));
        MDP_OSAL_MEMZERO(&sFetchPipeActiveCfg,  sizeof(HAL_MDP_ControlPath_FetchPipeActiveType));
        MDP_OSAL_MEMZERO(&sDSPPFlushConfig,     sizeof(HAL_MDP_ControlPath_DSPPFlushType));

        // Setup fetch active pipe
        sFetchPipeActiveCfg.eSourcePipeId          = eDemuraPipeId;
        sFetchPipeActiveCfg.bPipeActive            = TRUE;
        //Setup DSPP Flush
        sDSPPFlushConfig.eDestinationPipeId        = pPanelConfig->sDisplayControlPath[uI].eDestinationPipeId;
        sDSPPFlushConfig.eDsppMoudle               = HAL_MDP_DSPPMODULE_DEMURA | HAL_MDP_DSPPMODULE_SPR;

        sControlPathConfig.psFetchPipeActiveConfig = &sFetchPipeActiveCfg;
        sControlPathConfig.psDsppFlushConfig       = &sDSPPFlushConfig;

        if (HAL_MDSS_STATUS_SUCCESS != HAL_MDP_ControlPath_Setup(pPanelConfig->sDisplayControlPath[uI].eControlPathId,
                                                                &sControlPathConfig,
                                                                 0))
        {
          MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPDemuraSetupConfig: HAL_MDP_ControlPath_Setup failed!\n");
          eStatus = MDP_STATUS_FAILED;
        }
        else if (HAL_MDSS_STATUS_SUCCESS != HAL_MDP_SourcePipe_Setup(eDemuraPipeId,
                                                                     eLayerType,
                                                                    &sSourcePipeConfig,
                                                                     0x0))
        {
          MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPDemuraSetupConfig: HAL_MDP_SourcePipe_Setup failed!\n");
          eStatus = MDP_STATUS_FAILED;
        }
        else if (HAL_MDSS_STATUS_SUCCESS != HAL_MDP_Demura_Setup(eDemuraId, 
                                                                 pPanelConfig->uAttrs.sDsi.sDemuraConfig.psDemuraConfig))
        {
          MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPDemuraSetupConfig: HAL_MDP_Demura_Setup failed\n");
          eStatus = MDP_STATUS_FAILED;
        }
        else if (MDP_STATUS_OK != (eStatus = CommitDemuraPipes(pPanelConfig->sDisplayControlPath[uI].eControlPathId,
                                                               eDemuraPipeId,
                                                               eDemuraId)))
        {
          MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPDemuraSetupConfig: CommitDemuraPipes failed, eStatus = %d\n", eStatus);
        }
      }
    }
  }

  return eStatus;
}

/****************************************************************************
*
** FUNCTION: MDPDemuraLoadConfig()
*/
/*!
* \brief
*   Read Demura file from QMCS partition.
*
* \param [in] pPanelConfig     - The display configuration to setup
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status MDPDemuraLoadConfig(MDP_Panel_AttrType *pPanelConfig)
{
  MDP_Status                      eStatus             = MDP_STATUS_OK;
  uint8                          *pDemuraBuffer       = NULL;
  uint32                          uDemuraBufferSize   = 0;
  uint32                          uDemuraRetSize      = 0;
  CHAR8                           sDemuraFileName[DISP_DEMURA_FILE_NAME_LEN];
  HAL_MDP_DemuraDataConfigType   *pDemuraDataConfig;

  if (NULL == pPanelConfig)
  {
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else if (MDP_STATUS_OK != (eStatus = BuildDemuraFileString(sDemuraFileName, sizeof(sDemuraFileName), pPanelConfig->uAttrs.sDsi.sDemuraConfig.uDemuraPanelID)))
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPDemuraLoadConfig: BuildDemuraFileString failed eStatus= 0x%x!\n", eStatus);
  }
  else if (MDP_STATUS_OK != (eStatus = MDP_Display_LoadFileEx(DISP_DEMURA_FV_LABEL, sDemuraFileName, (UINT8**)&pDemuraBuffer, &uDemuraBufferSize, 0, &uDemuraRetSize, 0)))
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPDemuraLoadConfig: Read Demura Data failed eStatus= 0x%x!\n", eStatus);
  }
  else if (NULL == (pDemuraDataConfig = MDP_OSAL_CALLOC(sizeof(HAL_MDP_DemuraDataConfigType))))
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPDemuraLoadConfig: failed to allocate memory for pDemuraDataConfig!\n");
    eStatus = MDP_STATUS_NO_RESOURCES;
  }
  else if(MDP_STATUS_OK != (eStatus = ParseDemuraCorrection(pPanelConfig, pDemuraBuffer, uDemuraRetSize, pDemuraDataConfig)))
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPDemuraLoadConfig: ParseDemuraCorrection failed, Status = 0x%x\n", eStatus);
    MDP_OSAL_FREE(pDemuraDataConfig);
  }
  else
  {
    if (NULL != pPanelConfig->uAttrs.sDsi.sDemuraConfig.psDemuraConfig)
    {
      MDP_OSAL_FREE(pPanelConfig->uAttrs.sDsi.sDemuraConfig.psDemuraConfig);
    }
 
    pPanelConfig->uAttrs.sDsi.sDemuraConfig.psDemuraConfig = pDemuraDataConfig;
  }

  if (NULL != pDemuraBuffer)
  {
    MDP_OSAL_FREE(pDemuraBuffer);
  }

  return eStatus;
}

/****************************************************************************
*
** FUNCTION: MDPGetDemmuraPanelID()
*/
/*!
* \brief
*   Get display Demura panel ID.
*
* \param [in] pPanelConfig          - The display configuration to setup
* \param [in] pDemuraPanelIDCmd     - Demura panel id read command
* \param [in] uDemuraPanelIDCmdLen  - Demura panel id read command length

*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status MDPGetDemmuraPanelID(MDP_Panel_AttrType *pDisplayInfo, uint8* pDemuraPanelIDCmd, uint32 uDemuraPanelIDCmdLen)
{
  MDP_Status                  eStatus            = MDP_STATUS_OK;

  if ((NULL == pDisplayInfo) ||
      (NULL == pDemuraPanelIDCmd))
  {
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else if (0 != pDisplayInfo->uAttrs.sDsi.sDemuraConfig.uDemuraPanelID)
  {
    // Skip reading Demura panel ID from panel, use override Demura panel ID.
    eStatus = MDP_STATUS_OK;
  }
  else
  {
    uint64 uDemuraPanelID;

    if (MDP_STATUS_OK != (eStatus = ReadDemuraPanelID(pDisplayInfo->eDisplayId, pDemuraPanelIDCmd, uDemuraPanelIDCmdLen, &uDemuraPanelID)))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPGetDemmuraPanelID: Read Demura Panel ID failed eStatus= 0x%x!\n", eStatus);
    }
    else
    {
      pDisplayInfo->uAttrs.sDsi.sDemuraConfig.uDemuraPanelID = uDemuraPanelID;
    }
  }

  return eStatus;
}
