/*
  Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
*/

/*------------------------------------------------------------------------------
 * Include Files
 *----------------------------------------------------------------------------*/
#include <Library/BaseLib.h>
#include "hal_mdp_i.h"
#include "hal_mdp_osal.h"

#ifdef __cplusplus
extern "C" {
#endif

/* HAL_MDP_SprInitConfigType
 *
 * MDP SPR init configuration parameters
 */
typedef struct
{
  uint32   uCfg0;
  uint32   uCfg1;
  uint32   uCfg2;
  uint32   uCfg3;
  uint32   uCfg4;
  uint32   uCfg5;
  uint32   uCfg6;
  uint32   uCfg7;
  uint32   uCfg8;
  uint32   uCfg9;
  uint32   uCfg10;
  uint32   aCfg11[4];
  uint32   aCfg12[4];
  uint32   aCfg13[4];
  uint32   aCfg14[5];
  uint32   aCfg15[32];
  int32    aCfg16[16];
  int32    aCfg17[24];
} HAL_MDP_SprInitConfigType;

static  uint32 aDefaultOPRGains[4]                   = { 341,  341,  341,   0};
static  uint32 aDefaultRGBWGains[4]                  = {1024, 1024, 1024, 341};
static  uint32 aDefaultAdaptiveStrengths[5]          = {   0,    4,    8,   12,   16};
static  uint32 aDefaultColorPhaseIncrement[4]        = {   8,    6,    6,   8};
static  uint32 aDefaultColorPhaseRepeat[4]           = {   2,    2,    2,   2};
static  uint32 aDefaultOPROffsets[32]                = {   0,  132,  264,  396,  529,  661,  793,  925,
                                                        1057, 1189, 1321, 1453, 1586, 1718, 1850, 1982,
                                                        2114, 2246, 2378, 2510, 2643, 2775, 2907, 3039,
                                                        3171, 3303, 3435, 3567, 3700, 3832, 3964, 4095};
static  int32 aDefaultColorPhaseMap[4][24]           = {{ -2,    2,    0,    0,    0,    0,    0,    0,
                                                           0,    0,    0,    0,    2,   -2,    0,    0,
                                                           0,    0,    0,    0,    0,    0,    0,    0},
                                                        { -3,    0,    0,    0,    0,    0,   -1,    2,
                                                           1,    1,    0,    0,    1,   -2,    0,    1,
                                                           0,    0,    0,    0,    0,    0,    0,    0},
                                                        { -4,    2,    0,    0,    0,   -1,    2,    2,
                                                           0,   -1,   -1,   -1,    2,    2,   -1,   -1,
                                                          -1,    2,    0,    0,    0,    0,    0,    0},
                                                        { -4,    0,    0,    0,    0,    0,   -2,    2,
                                                           0,    0,    0,    0,    0,   -4,    0,    0,
                                                           0,    0,    2,   -2,    0,    0,    0,    0}};
static  int32 aDefaultFilterCoeffsMap[4][16]         = {{  0,    0,    0,    0,    0,    0,    0,    0,
                                                           0,    0,    0,    0,    0,    0,    0,    0},
                                                        {  0,  512,    0,    0,  -33,  443,  110,   -8,
                                                         -23,  279,  279,  -23,   -8,  110,  443,  -33},
                                                        {128,  256,  128,    0,   86,  241,  164,   21,
                                                          52,  204,  204,   52,   21,  164,  241,   86},
                                                        {  0,  256,  256,    0,    0,  256,  256,    0,
                                                           0,  256,  256,    0,    0,  256,  256,    0}};
static  int32 aDecimationRatioMap[4][4]              = {{  1,    0,    1,    0},
                                                        {  2,    2,    2,    0},
                                                        {  2,    2,    2,    0},
                                                        {  1,    1,    1,    1}};


/****************************************************************************
*
** FUNCTION: HAL_MDP_Get_SPR_BaseOffset()
*/
/*!
* \brief
*     Returns the offset difference of the given stream ID from the base SPR ID
*
* \param [in] eSprId         - SPR ID
* \param [in] eSprId         - SPR ID
*
* \retval uintPtr
*
****************************************************************************/
static HAL_MDSS_ErrorType HAL_MDP_Get_SPR_BaseOffset(HAL_MDP_SprId  eSprId, uintPtr *pSprPtr)
{
  HAL_MDSS_ErrorType   eStatus   = HAL_MDSS_STATUS_SUCCESS;

  if ((HAL_MDP_SPR_MAX <= eSprId) ||
      (NULL            == pSprPtr))
  {
    eStatus = HAL_MDSS_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  {
    *pSprPtr = uMDPSprRegBaseOffset[eSprId];
  }

  return eStatus;
}


/****************************************************************************
*
** FUNCTION: HAL_MDP_SPR_LoadConfig()
*/
/*!
* \brief
*     Load SPR configurations based on the SPR pack type and custom data configurations.
*
* \param [in] eSprPackType     - SPR pack type
* \param [in] psSprDataConfig  - Pointer to SPR data configuration
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
static HAL_MDSS_ErrorType HAL_MDP_SPR_LoadConfig(HAL_MDP_SprPack_Type        eSprPackType,
                                                 HAL_MDP_SprDataConfigType  *psSprDataConfig,
                                                 HAL_MDP_SprInitConfigType  *psSprInitConfig)
{
  HAL_MDSS_ErrorType      eStatus     = HAL_MDSS_STATUS_SUCCESS;
  uint32                  uPackIndex  = eSprPackType - 1;

  if (HAL_MDP_SPR_BYPASS == eSprPackType)
  {
    psSprInitConfig->uCfg1 = 1;
    psSprInitConfig->uCfg2 = 1;
  }
  else
  {
    psSprInitConfig->uCfg0 = 1;
    psSprInitConfig->uCfg1 = 1;
    psSprInitConfig->uCfg2 = 1;
    psSprInitConfig->uCfg3 = 0;
    psSprInitConfig->uCfg4 = (HAL_MDP_SPR_PACK_RGBW == eSprPackType) ? 1 : 0;

    if (0 != psSprDataConfig->uPhaseInc)
    {
      psSprInitConfig->uCfg5 = psSprDataConfig->uPhaseInc;
    }
    else
    {
      psSprInitConfig->uCfg5 = aDefaultColorPhaseIncrement[uPackIndex];
    }

    if (0 != psSprDataConfig->uPhaseRepeat)
    {
      psSprInitConfig->uCfg6 = psSprDataConfig->uPhaseRepeat;
    }
    else
    {
      psSprInitConfig->uCfg6 = aDefaultColorPhaseRepeat[uPackIndex];
    }

    if (HAL_MDP_SPR_FILTER_NONE != psSprDataConfig->eFilterType)
    {
      psSprInitConfig->uCfg7 = psSprDataConfig->eFilterType - 1;
    }
    else
    {
      psSprInitConfig->uCfg7 = HAL_MDP_SPR_FILTER_FOURTAP - 1;
    }

    if (HAL_MDP_SPR_ADAPTIVEMODE_NONE != psSprDataConfig->eAdaptiveMode)
    {
      psSprInitConfig->uCfg8 = psSprDataConfig->eAdaptiveMode - 1;
    }
    else
    {
      psSprInitConfig->uCfg8 = HAL_MDP_SPR_ADAPTIVEMODE_YYGM - 1;
    }

    if (HAL_MDP_SPR_PACK_RGBW == eSprPackType)
    {
      psSprInitConfig->uCfg9 = 512;
      MDSS_OSAL_MEMCPY(&psSprInitConfig->aCfg12, &aDefaultRGBWGains, sizeof(aDefaultRGBWGains));
    }

    psSprInitConfig->uCfg10 = 0;
    MDSS_OSAL_MEMCPY(&psSprInitConfig->aCfg11, &aDecimationRatioMap[uPackIndex], sizeof(aDecimationRatioMap[0]));
    MDSS_OSAL_MEMCPY(&psSprInitConfig->aCfg13, &aDefaultOPRGains, sizeof(aDefaultOPRGains));


    if (TRUE == psSprDataConfig->bAdaptiveStrengthsOverride)
    {
      MDSS_OSAL_MEMCPY(&psSprInitConfig->aCfg14, &psSprDataConfig->aAdaptiveStrengths, sizeof(psSprDataConfig->aAdaptiveStrengths));
    }
    else
    {
      MDSS_OSAL_MEMCPY(&psSprInitConfig->aCfg14, &aDefaultAdaptiveStrengths, sizeof(aDefaultAdaptiveStrengths));
    }

    MDSS_OSAL_MEMCPY(&psSprInitConfig->aCfg15, &aDefaultOPROffsets, sizeof(aDefaultOPROffsets));


    if ((HAL_MDP_SPR_FILTER_NONE != psSprDataConfig->eFilterType) &&
      (TRUE == psSprDataConfig->bFilterCoeffsOverride))
    {
      MDSS_OSAL_MEMCPY(&psSprInitConfig->aCfg16, &psSprDataConfig->aFilterCoeffs, sizeof(psSprDataConfig->aFilterCoeffs));
    }
    else
    {
      MDSS_OSAL_MEMCPY(&psSprInitConfig->aCfg16, aDefaultFilterCoeffsMap[HAL_MDP_SPR_FILTER_FOURTAP - 1], sizeof(aDefaultFilterCoeffsMap[0]));
    }

    if (TRUE == psSprDataConfig->bColorPhaseOffsetsRedOverride)
    {
      MDSS_OSAL_MEMCPY(&psSprInitConfig->aCfg17[0], &psSprDataConfig->aColorPhaseOffsetsRed[0], sizeof(psSprDataConfig->aColorPhaseOffsetsRed));
    }
    else
    {
      // aCfg17[0] ~ aCfg17[5] are used to save the ColorPhaseOffsetsRed
      MDSS_OSAL_MEMCPY(&psSprInitConfig->aCfg17[0], &aDefaultColorPhaseMap[uPackIndex][0], sizeof(aDefaultColorPhaseMap[0]) / 4);
    }

    if (TRUE == psSprDataConfig->bColorPhaseOffsetsGreenOverride)
    {
      MDSS_OSAL_MEMCPY(&psSprInitConfig->aCfg17[6], &psSprDataConfig->aColorPhaseOffsetsGreen[0], sizeof(psSprDataConfig->aColorPhaseOffsetsGreen));
    }
    else
    {
      // aCfg17[6] ~ aCfg17[11] are used to save the ColorPhaseOffsetsGreen
      MDSS_OSAL_MEMCPY(&psSprInitConfig->aCfg17[6], &aDefaultColorPhaseMap[uPackIndex][6], sizeof(aDefaultColorPhaseMap[0]) / 4);
    }

    if (TRUE == psSprDataConfig->bColorPhaseOffsetsBlueOverride)
    {
      MDSS_OSAL_MEMCPY(&psSprInitConfig->aCfg17[12], &psSprDataConfig->aColorPhaseOffsetsBlue[0], sizeof(psSprDataConfig->aColorPhaseOffsetsBlue));
    }
    else
    {
      // aCfg17[12] ~ aCfg17[17] are used to save the ColorPhaseOffsetsBlue
      MDSS_OSAL_MEMCPY(&psSprInitConfig->aCfg17[12], &aDefaultColorPhaseMap[uPackIndex][12], sizeof(aDefaultColorPhaseMap[0]) / 4);
    }

    if (TRUE == psSprDataConfig->bColorPhaseOffsetsWhiteOverride)
    {
      MDSS_OSAL_MEMCPY(&psSprInitConfig->aCfg17[18], &psSprDataConfig->aColorPhaseOffsetsWhite[0], sizeof(psSprDataConfig->aColorPhaseOffsetsWhite));
    }
    else
    {
      // aCfg17[18] ~ aCfg17[23] are used to save the ColorPhaseOffsetsWhite
      MDSS_OSAL_MEMCPY(&psSprInitConfig->aCfg17[18], &aDefaultColorPhaseMap[uPackIndex][18], sizeof(aDefaultColorPhaseMap[0]) / 4);
    }
  }

  return eStatus;
}


/****************************************************************************
*
** FUNCTION: HAL_MDP_SPR_SetupConfig()
*/
/*!
* \brief
*     Load SPR configurations and program registers.
*
* \param [in] eSprId                - SPR ID
* \param [in] eSprPackType          - SPR pack type
* \param [in] psSprDataConfig       - Pointer to SPR data configuration
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_MDP_SPR_SetupConfig(HAL_MDP_SprId               eSprId,
                                           HAL_MDP_SprPack_Type        eSprPackType,
                                           HAL_MDP_SprDataConfigType  *psSprDataConfig)
{
  HAL_MDSS_ErrorType          eStatus       = HAL_MDSS_STATUS_SUCCESS;

  if (NULL == psSprDataConfig)
  {
    eStatus = HAL_MDSS_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  {
    uintPtr  uRegOffset  = 0x00;
    uint32   uRegValue   = 0x00;

    if(HAL_MDSS_STATUS_SUCCESS == HAL_MDP_Get_SPR_BaseOffset(eSprId, &uRegOffset))
    {
      uint32                      uI          = 0x00;
      HAL_MDP_SprInitConfigType   sSprInitConfig;

      MDSS_OSAL_MEMZERO(&sSprInitConfig, sizeof(HAL_MDP_SprInitConfigType));
      HAL_MDP_SPR_LoadConfig(eSprPackType, psSprDataConfig, &sSprInitConfig);
      
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_SPR_0_SPR_CONFIG, SPR_EN,         sSprInitConfig.uCfg0);
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_SPR_0_SPR_CONFIG, IGC_EN,         sSprInitConfig.uCfg1);
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_SPR_0_SPR_CONFIG, GC_EN,          sSprInitConfig.uCfg2);
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_SPR_0_SPR_CONFIG, RGBW_EN,        sSprInitConfig.uCfg4);
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_SPR_0_SPR_CONFIG, OPR_EN,         sSprInitConfig.uCfg3);

      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_SPR_0_SPR_CONFIG, PHASE_INC,      sSprInitConfig.uCfg5);
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_SPR_0_SPR_CONFIG, REPEAT,         sSprInitConfig.uCfg6);
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_SPR_0_SPR_CONFIG, FILTER_METHOD,  sSprInitConfig.uCfg7);
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_SPR_0_SPR_CONFIG, ADAPTIVE_MODE,  sSprInitConfig.uCfg8);

      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_SPR_0_SPR_CONFIG, DECIMATE_R,     sSprInitConfig.aCfg11[0]);
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_SPR_0_SPR_CONFIG, DECIMATE_G,     sSprInitConfig.aCfg11[1]);
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_SPR_0_SPR_CONFIG, DECIMATE_B,     sSprInitConfig.aCfg11[2]);
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_SPR_0_SPR_CONFIG, DECIMATE_W,     sSprInitConfig.aCfg11[3]);
      out_dword(HWIO_MDP_SPR_0_SPR_CONFIG_ADDR + uRegOffset, uRegValue);

      uRegValue = 0x00;
      if (4 == psSprDataConfig->uNumMixers)
      {
        uRegValue  = HWIO_OUT_FLD(uRegValue, MDP_SPR_0_MERGE_CTRL, MERGE_MODE,  3);
      }
      else if (2 == psSprDataConfig->uNumMixers)
      {
        uRegValue  = HWIO_OUT_FLD(uRegValue, MDP_SPR_0_MERGE_CTRL, MERGE_MODE,  1);
      }
      else
      {
        uRegValue  = HWIO_OUT_FLD(uRegValue, MDP_SPR_0_MERGE_CTRL, MERGE_MODE,  0);
      }
      out_dword(HWIO_MDP_SPR_0_MERGE_CTRL_ADDR + uRegOffset, uRegValue);

      if (HAL_MDP_SPR_BYPASS != eSprPackType)
      {
        uRegValue  = 0x00;
        for (uI=0; uI<HAL_MDP_ARRAY_LENGTH(sSprInitConfig.aCfg14); uI++)
        {
          // Each field offset for ADAPTIVE_FILTER is 5
          uRegValue |= (sSprInitConfig.aCfg14[uI] & 0x1F) << (uI * 5);
        }
        out_dword(HWIO_MDP_SPR_0_ADAPTIVE_FILTER_ADDR + uRegOffset, uRegValue);

        uRegValue  = 0x00;
        // Program RED_PHASE_OFFSET using aCfg17[0] ~ aCfg17[5]
        for (uI=0; uI<(HAL_MDP_ARRAY_LENGTH(sSprInitConfig.aCfg17)/4); uI++)
        {
          // Each field offset for RED_PHASE_OFFSET is 5
          uRegValue |= (sSprInitConfig.aCfg17[uI] & 0x1F) << (uI * 5);
        }
        out_dword(HWIO_MDP_SPR_0_RED_PHASE_OFFSET_ADDR + uRegOffset, uRegValue);

        uRegValue  = 0x00;
        // Program GREEN_PHASE_OFFSET using aCfg17[6] ~ aCfg17[11]
        for (uI=0; uI<(HAL_MDP_ARRAY_LENGTH(sSprInitConfig.aCfg17)/4); uI++)
        {
          // Each field offset for GREEN_PHASE_OFFSET is 5
          uRegValue |= (sSprInitConfig.aCfg17[uI+6] & 0x1F) << (uI * 5);
        }
        out_dword(HWIO_MDP_SPR_0_GREEN_PHASE_OFFSET_ADDR + uRegOffset, uRegValue);

        uRegValue  = 0x00;
        // Program BLUE_PHASE_OFFSET using aCfg17[12] ~ aCfg17[17]
        for (uI=0; uI<(HAL_MDP_ARRAY_LENGTH(sSprInitConfig.aCfg17)/4); uI++)
        {
          // Each field offset for BLUE_PHASE_OFFSET is 5
          uRegValue |= (sSprInitConfig.aCfg17[uI+12] & 0x1F) << (uI * 5);
        }
        out_dword(HWIO_MDP_SPR_0_BLUE_PHASE_OFFSET_ADDR + uRegOffset, uRegValue);

        uRegValue  = 0x00;
        // Program WHITE_PHASE_OFFSET using aCfg17[18] ~ aCfg17[19]
        for (uI=0; uI<2; uI++)
        {
          // Each field offset for WHITE_PHASE_OFFSET is 5
          uRegValue |= (sSprInitConfig.aCfg17[uI+18] & 0x1F) << (uI * 5);
        }
        out_dword(HWIO_MDP_SPR_0_WHITE_PHASE_OFFSET_ADDR + uRegOffset, uRegValue);

        // Program registers from MDP_SPR_0_COEFF_0 to MDP_SPR_0_COEFF_7
        for (uI=0; uI<(HAL_MDP_ARRAY_LENGTH(sSprInitConfig.aCfg16)/2); uI++)
        {
          // The address offset for spr coeff registers is 4
          uRegValue  = 0x00;
          uRegValue = HWIO_OUT_FLD(uRegValue, MDP_SPR_0_COEFF_0, COEF_00,  sSprInitConfig.aCfg16[2*uI]);
          uRegValue = HWIO_OUT_FLD(uRegValue, MDP_SPR_0_COEFF_0, COEF_01,  sSprInitConfig.aCfg16[2*uI + 1]);
          out_dword(HWIO_MDP_SPR_0_COEFF_0_ADDR + 4*uI + uRegOffset, uRegValue);
        }

        // Check if OPR has been enabled.
        if (0 != sSprInitConfig.uCfg3)
        {
          uRegValue  = 0x00;
          uRegValue = HWIO_OUT_FLD(uRegValue, MDP_SPR_0_OPR_GAIN, OPR_GAIN_R, sSprInitConfig.aCfg13[0]);
          uRegValue = HWIO_OUT_FLD(uRegValue, MDP_SPR_0_OPR_GAIN, OPR_GAIN_G, sSprInitConfig.aCfg13[1]);
          uRegValue = HWIO_OUT_FLD(uRegValue, MDP_SPR_0_OPR_GAIN, OPR_GAIN_B, sSprInitConfig.aCfg13[2]);
          out_dword(HWIO_MDP_SPR_0_OPR_GAIN_ADDR + uRegOffset, uRegValue);

          uRegValue  = 0x00;
          uRegValue = HWIO_OUT_FLD(uRegValue, MDP_SPR_0_OPR_ACCUM_INIT, OPR_ACCUM_INIT, sSprInitConfig.uCfg10);
          out_dword(HWIO_MDP_SPR_0_OPR_ACCUM_INIT_ADDR + uRegOffset, uRegValue);

          // Program registers from MDP_SPR_0_OPR_OFFSET_0 to MDP_SPR_0_OPR_OFFSET_15
          for (uI=0; uI<(HAL_MDP_ARRAY_LENGTH(sSprInitConfig.aCfg15)/2); uI++)
          {
            // The address offset for SPR opr offset registers is 4
            uRegValue  = 0x00;
            uRegValue = HWIO_OUT_FLD(uRegValue, MDP_SPR_0_OPR_OFFSET_0, OPR_OFFSET_0, sSprInitConfig.aCfg15[2*uI]);
            uRegValue = HWIO_OUT_FLD(uRegValue, MDP_SPR_0_OPR_OFFSET_0, OPR_OFFSET_1, sSprInitConfig.aCfg15[2*uI + 1]);
            out_dword(HWIO_MDP_SPR_0_OPR_OFFSET_0_ADDR + 4*uI + uRegOffset, uRegValue);
          }
        }

        // Check if RGBW type is used.
        if (0 != sSprInitConfig.uCfg4)
        {
          uRegValue  = 0x00;
          uRegValue = HWIO_OUT_FLD(uRegValue, MDP_SPR_0_RGBW_PACK,  PACK_WIDTH, sSprInitConfig.uCfg9);
          out_dword(HWIO_MDP_SPR_0_RGBW_PACK_ADDR + uRegOffset, uRegValue);

          uRegValue  = 0x00;
          uRegValue = HWIO_OUT_FLD(uRegValue, MDP_SPR_0_RGBW_GAIN_0,  CHROMA_GAIN, sSprInitConfig.aCfg12[3]);
          uRegValue = HWIO_OUT_FLD(uRegValue, MDP_SPR_0_RGBW_GAIN_0,  RED_GAIN,    sSprInitConfig.aCfg12[0]);
          out_dword(HWIO_MDP_SPR_0_RGBW_GAIN_0_ADDR + uRegOffset, uRegValue);

          uRegValue  = 0x00;
          uRegValue = HWIO_OUT_FLD(uRegValue, MDP_SPR_0_RGBW_GAIN_1,  GREEN_GAIN, sSprInitConfig.aCfg12[1]);
          uRegValue = HWIO_OUT_FLD(uRegValue, MDP_SPR_0_RGBW_GAIN_1,  BLUE_GAIN, sSprInitConfig.aCfg12[2]);
          out_dword(HWIO_MDP_SPR_0_RGBW_GAIN_1_ADDR + uRegOffset, uRegValue);
        }
      }
    }
  }

  return eStatus;
}

#ifdef __cplusplus
}
#endif
