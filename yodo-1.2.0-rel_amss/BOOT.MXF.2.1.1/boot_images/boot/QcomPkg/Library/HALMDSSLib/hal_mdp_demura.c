/*
  Copyright (c) 2020 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
*/

/*------------------------------------------------------------------------------
 * Include Files
 *----------------------------------------------------------------------------*/
#include "hal_mdp_i.h"

#ifdef __cplusplus
extern "C" {
#endif

/* -------------------------------------------------------------------------------------
 * Local defines
 * ------------------------------------------------------------------------------------ */
#define HAL_MDP_DEMURA_BRGT_ADJ_DEFAULT   0x04000400
#define HAL_MDP_DEMURA_CFG3ABADJ_DEFAULT  0x400
  /*------------------------------------------------------------------------
 * Private Function Definitions
 *------------------------------------------------------------------------ */


 /****************************************************************************
 *
 ** FUNCTION: HAL_MDP_Get_Demura_BaseOffset()
 */
 /*!
 * \brief
 *     Returns the offset difference of the given stream ID from the base Demura ID
 *
 * \param [in]  eDemuraId          - Demura ID
 * \param [out] pRegOffset         - Demura reg offset
 *
 * \retval HAL_MDSS_ErrorType
 *
 ****************************************************************************/
static HAL_MDSS_ErrorType HAL_MDP_Get_Demura_BaseOffset(HAL_MDP_DemuraId  eDemuraId, uintPtr* pRegOffset)
{
  HAL_MDSS_ErrorType   eStatus = HAL_MDSS_STATUS_SUCCESS;

  if ((HAL_MDP_DEMURA_MAX  <= eDemuraId) ||
      (NULL                == pRegOffset)||
      (HAL_MDP_DEMURA_NONE == eDemuraId))
  {
    eStatus = HAL_MDSS_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  {
    *pRegOffset = uMDPDemuraRegBaseOffset[eDemuraId];
  }

  return eStatus;
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_Demura_Setup()
*/
/*!
* \brief
*     Configures the Demura HW
*
* \param [in] eDemuraId             - Demura ID
* \param [in] psDemuraDataConfig    - Pointer to Demura data configuration
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_MDP_Demura_Setup( HAL_MDP_DemuraId              eDemuraId,
                                         HAL_MDP_DemuraDataConfigType *psDemuraDataConfig)
{
  HAL_MDSS_ErrorType          eStatus     = HAL_MDSS_STATUS_SUCCESS;
  uintPtr                     uRegOffset  = 0x00;

  if ((NULL == psDemuraDataConfig)                 ||
      (0    == psDemuraDataConfig->uDisplayWidth)  ||
      (0    == psDemuraDataConfig->uDisplayHeight) ||
      (HAL_MDSS_STATUS_SUCCESS != (eStatus = HAL_MDP_Get_Demura_BaseOffset(eDemuraId, &uRegOffset))))
  {
    eStatus = HAL_MDSS_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  {
    uint32  i         = 0x00;
    uint32  uTemp1    = 0x00;
    uint32  uTemp2    = 0x00;
    uint32  uRegValue = 0x00;


    out_dword(uRegOffset + HWIO_MDP_DEMURA_0_BRGT_ADJ_ADDR, HAL_MDP_DEMURA_BRGT_ADJ_DEFAULT);

    if (psDemuraDataConfig->uCfg0En)
    { 
      uRegValue = 0;
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_LEVEL_CONFIG0, LVL_0_END, psDemuraDataConfig->uCfg0Param1[0]);
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_LEVEL_CONFIG0, LVL_1_END, psDemuraDataConfig->uCfg0Param1[1]);
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_LEVEL_CONFIG0, LVL_2_END, psDemuraDataConfig->uCfg0Param1[2]);
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_LEVEL_CONFIG0, LVL_3_END, psDemuraDataConfig->uCfg0Param1[3]);
      out_dword(uRegOffset + HWIO_MDP_DEMURA_0_LEVEL_CONFIG0_ADDR, uRegValue);

      uRegValue = 0;
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_LEVEL_CONFIG1, LVL_4_END, psDemuraDataConfig->uCfg0Param1[4]);
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_LEVEL_CONFIG1, LVL_5_END, psDemuraDataConfig->uCfg0Param1[5]);
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_LEVEL_CONFIG1, LVL_6_END, psDemuraDataConfig->uCfg0Param1[6]);
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_LEVEL_CONFIG1, LVL_7_END, psDemuraDataConfig->uCfg0Param1[7]);
      out_dword(uRegOffset + HWIO_MDP_DEMURA_0_LEVEL_CONFIG1_ADDR, uRegValue);

      for (i = 0; i < (DEMURA_CFG1_PARAM_LEN>>1); i ++)
      {
        uRegValue = 0;
        uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_LEVEL_OFFSET0, OFFSET_0, psDemuraDataConfig->uCfg01Param0[i * 2]);
        uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_LEVEL_OFFSET0, OFFSET_1, psDemuraDataConfig->uCfg01Param0[i * 2 + 1]);
        out_dword(uRegOffset + HWIO_MDP_DEMURA_0_LEVEL_OFFSET0_ADDR + 4 * i, uRegValue);
      }

      for (i = 0; i < DEMURA_CFG1_PARAM_LEN; i++)
      {
        out_dword(uRegOffset + HWIO_MDP_DEMURA_0_LEVEL_SCALE0_ADDR + 4 * i, psDemuraDataConfig->uCfg0Param0[i]);
      }

      for (i = 0; i < (DEMURA_CFG0_PARAM_LEN>>2); i++)
      {
        uRegValue = 0;
        uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_R_HFC_OFFSET_0, R_HFC_OFF_0, psDemuraDataConfig->uCfg0Param3C0[i * 4]);
        uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_R_HFC_OFFSET_0, R_HFC_OFF_1, psDemuraDataConfig->uCfg0Param3C0[i * 4 + 1]);
        uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_R_HFC_OFFSET_0, R_HFC_OFF_2, psDemuraDataConfig->uCfg0Param3C0[i * 4 + 2]);
        uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_R_HFC_OFFSET_0, R_HFC_OFF_3, psDemuraDataConfig->uCfg0Param3C0[i * 4 + 3]);
        out_dword(uRegOffset + HWIO_MDP_DEMURA_0_R_HFC_OFFSET_0_ADDR + i * 4, uRegValue);

        uRegValue = 0;
        uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_G_HFC_OFFSET_0, G_HFC_OFF_0, psDemuraDataConfig->uCfg0Param3C1[i * 4]);
        uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_G_HFC_OFFSET_0, G_HFC_OFF_1, psDemuraDataConfig->uCfg0Param3C1[i * 4 + 1]);
        uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_G_HFC_OFFSET_0, G_HFC_OFF_2, psDemuraDataConfig->uCfg0Param3C1[i * 4 + 2]);
        uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_G_HFC_OFFSET_0, G_HFC_OFF_3, psDemuraDataConfig->uCfg0Param3C1[i * 4 + 3]);
        out_dword(uRegOffset + HWIO_MDP_DEMURA_0_G_HFC_OFFSET_0_ADDR + i * 4, uRegValue);

        uRegValue = 0;
        uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_B_HFC_OFFSET_0, B_HFC_OFF_0, psDemuraDataConfig->uCfg0Param3C2[i * 4]);
        uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_B_HFC_OFFSET_0, B_HFC_OFF_1, psDemuraDataConfig->uCfg0Param3C2[i * 4 + 1]);
        uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_B_HFC_OFFSET_0, B_HFC_OFF_2, psDemuraDataConfig->uCfg0Param3C2[i * 4 + 2]);
        uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_B_HFC_OFFSET_0, B_HFC_OFF_3, psDemuraDataConfig->uCfg0Param3C2[i * 4 + 3]);
        out_dword(uRegOffset + HWIO_MDP_DEMURA_0_B_HFC_OFFSET_0_ADDR + i * 4, uRegValue);
      }

      uRegValue = psDemuraDataConfig->uDisplayWidth >> 1;
      out_dword(uRegOffset + HWIO_MDP_DEMURA_0_HFC_SAMPLE_CNT_ADDR, uRegValue);

      psDemuraDataConfig->uCfg3ABAdj = HAL_MDP_DEMURA_CFG3ABADJ_DEFAULT;
      out_dword(uRegOffset + HWIO_MDP_DEMURA_0_OPR_ACL_ADJ_ADDR, psDemuraDataConfig->uCfg3ABAdj);
        
      for (i = 0; i < (DEMURA_CFG1_PARAM_LEN >> 2); i++)
      {
        uRegValue = 0;
        uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_LEVEL_GAIN0, GAIN0, psDemuraDataConfig->uCfg0Param4[i * 4]);
        uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_LEVEL_GAIN0, GAIN1, psDemuraDataConfig->uCfg0Param4[i * 4 + 1]);
        uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_LEVEL_GAIN0, GAIN2, psDemuraDataConfig->uCfg0Param4[i * 4 + 2]);
        uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_LEVEL_GAIN0, GAIN3, psDemuraDataConfig->uCfg0Param4[i * 4 + 3]);
        out_dword(uRegOffset + HWIO_MDP_DEMURA_0_LEVEL_GAIN0_ADDR + 4 * i, uRegValue);
      }

      uRegValue = 0;
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_HFC_CTL_DATA, HFC_SELECT,        0);
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_HFC_CTL_DATA, HFC_INDEX_UPDATE,  1);
      out_dword(uRegOffset + HWIO_MDP_DEMURA_0_HFC_CTL_DATA_ADDR, uRegValue);
      if ((1 << psDemuraDataConfig->uC0Depth) < DEMURA_CFG0_PARAM2_LEN)
      {
        for (i = 0; i < (1 << psDemuraDataConfig->uC0Depth); i++)
        {
          uTemp1 = (uint32)(psDemuraDataConfig->uCfg0Param2C0[i] & 0xFFFFFFFF);
          uTemp2 = (uint32)((psDemuraDataConfig->uCfg0Param2C0[i] & 0xFFFFFFFF00000000)>>32);

          out_dword(uRegOffset + HWIO_MDP_DEMURA_0_HFC_DATA_ADDR, uTemp1);
          out_dword(uRegOffset + HWIO_MDP_DEMURA_0_HFC_DATA_ADDR, uTemp2);
        }
      }

      uRegValue = 0;
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_HFC_CTL_DATA, HFC_SELECT,        1);
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_HFC_CTL_DATA, HFC_INDEX_UPDATE,  1);
      out_dword(uRegOffset + HWIO_MDP_DEMURA_0_HFC_CTL_DATA_ADDR, uRegValue);
      if ((1 << psDemuraDataConfig->uC1Depth) < DEMURA_CFG0_PARAM2_LEN)
      {
        for (i = 0; i < (1 << psDemuraDataConfig->uC1Depth); i++)
        {
          uTemp1 = (uint32)(psDemuraDataConfig->uCfg0Param2C1[i] & 0xFFFFFFFF);
          uTemp2 = (uint32)((psDemuraDataConfig->uCfg0Param2C1[i] & 0xFFFFFFFF00000000) >> 32);

          out_dword(uRegOffset + HWIO_MDP_DEMURA_0_HFC_DATA_ADDR, uTemp1);
          out_dword(uRegOffset + HWIO_MDP_DEMURA_0_HFC_DATA_ADDR, uTemp2);
        }
      }

      uRegValue = 0;
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_HFC_CTL_DATA, HFC_SELECT,        2);
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_HFC_CTL_DATA, HFC_INDEX_UPDATE,  1);
      out_dword(uRegOffset + HWIO_MDP_DEMURA_0_HFC_CTL_DATA_ADDR, uRegValue);
      if ((1 << psDemuraDataConfig->uC2Depth) < DEMURA_CFG0_PARAM2_LEN)
      {
        for (i = 0; i < (1 << psDemuraDataConfig->uC2Depth); i++)
        {
          uTemp1 = (uint32)(psDemuraDataConfig->uCfg0Param2C2[i] & 0xFFFFFFFF);
          uTemp2 = (uint32)((psDemuraDataConfig->uCfg0Param2C2[i] & 0xFFFFFFFF00000000) >> 32);

          out_dword(uRegOffset + HWIO_MDP_DEMURA_0_HFC_DATA_ADDR, uTemp1);
          out_dword(uRegOffset + HWIO_MDP_DEMURA_0_HFC_DATA_ADDR, uTemp2);
        }
      }
    }

    if (psDemuraDataConfig->uCfg1En)
    {
      uTemp1 = psDemuraDataConfig->uCfg01Param0[psDemuraDataConfig->uCfg1HighIdx];
      uTemp2 = psDemuraDataConfig->uCfg01Param0[psDemuraDataConfig->uCfg1LowIdx];
      if (uTemp1 > uTemp2)
      {
        uRegValue = uTemp1 - uTemp2;
      }
      else
      {
        uRegValue = 1;
      }
      uRegValue = (1 << 22) / uRegValue;
      out_dword(uRegOffset + HWIO_MDP_DEMURA_0_LFC_SCALE_ADDR, uRegValue);

      if (psDemuraDataConfig->uDisplayWidth < psDemuraDataConfig->uDisplayHeight)
      {
        uTemp1 = (8  * (1 << 21)) / psDemuraDataConfig->uDisplayWidth;
        uTemp2 = (16 * (1 << 21)) / psDemuraDataConfig->uDisplayHeight;
      }
      else
      {
        uTemp1 = (16 * (1 << 21)) / psDemuraDataConfig->uDisplayWidth;
        uTemp2 = (8  * (1 << 21)) / psDemuraDataConfig->uDisplayHeight;
      }
      uRegValue = 0;
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_LFC_PHASE_H_INC, PHASE_INC_H_RB_HALF, (psDemuraDataConfig->uPentile ? 1 : 0));
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_LFC_PHASE_H_INC, PHASE_INC_H, uTemp1);
      out_dword(uRegOffset + HWIO_MDP_DEMURA_0_LFC_PHASE_H_INC_ADDR, uRegValue);
      out_dword(uRegOffset + HWIO_MDP_DEMURA_0_LFC_PHASE_V_INC_ADDR, uTemp2);

      if (HAL_MDP_DEMURA_1 == eDemuraId)
      {
        uRegValue = uTemp1 * (psDemuraDataConfig->uDisplayWidth >> 1);
        out_dword(uRegOffset + HWIO_MDP_DEMURA_0_LFC_PHASE_H_OFFSET_ADDR, 0x7FFDA0);
      }

      for (i = 0; i < DEMURA_CFG1_PARAM0_LEN; i++)
      {
        uRegValue = 0;
        uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_LFC_DATA, LFC_DATA_R, psDemuraDataConfig->uCfg1Param0C0[i]);
        uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_LFC_DATA, LFC_DATA_G, psDemuraDataConfig->uCfg1Param0C1[i]);
        uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_LFC_DATA, LFC_DATA_B, psDemuraDataConfig->uCfg1Param0C2[i]);

        if (0 == i)
        {
          uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_LFC_DATA, LFC_INDEX_UPDATE, 1);
        }

        out_dword(uRegOffset + HWIO_MDP_DEMURA_0_LFC_DATA_ADDR, uRegValue);
      }
    }

    if (psDemuraDataConfig->uCfg3En)
    {
      uRegValue = 0;
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_OPR_ACL_LEVEL_0, OPR_ACL_LVL_0, psDemuraDataConfig->uCfg3Param0A[0]);
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_OPR_ACL_LEVEL_0, OPR_ACL_LVL_1, psDemuraDataConfig->uCfg3Param0A[1]);
      out_dword(uRegOffset + HWIO_MDP_DEMURA_0_OPR_ACL_LEVEL_0_ADDR, uRegValue);

      uRegValue = 0;
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_OPR_ACL_LEVEL_1, OPR_ACL_LVL_2, psDemuraDataConfig->uCfg3Param0A[2]);
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_OPR_ACL_LEVEL_1, OPR_ACL_LVL_3, psDemuraDataConfig->uCfg3Param0A[3]);
      out_dword(uRegOffset + HWIO_MDP_DEMURA_0_OPR_ACL_LEVEL_1_ADDR, uRegValue);

      uRegValue = 0;
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_OPR_ACL_BRGT_LEVEL_0, OPR_ACL_BRGT_LVL_0, psDemuraDataConfig->uCfg3Param0B[0]);
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_OPR_ACL_BRGT_LEVEL_0, OPR_ACL_BRGT_LVL_1, psDemuraDataConfig->uCfg3Param0B[1]);
      out_dword(uRegOffset + HWIO_MDP_DEMURA_0_OPR_ACL_BRGT_LEVEL_0_ADDR, uRegValue);

      uRegValue = 0;
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_OPR_ACL_BRGT_LEVEL_1, OPR_ACL_BRGT_LVL_2, psDemuraDataConfig->uCfg3Param0B[2]);
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_OPR_ACL_BRGT_LEVEL_1, OPR_ACL_BRGT_LVL_3, psDemuraDataConfig->uCfg3Param0B[3]);
      out_dword(uRegOffset + HWIO_MDP_DEMURA_0_OPR_ACL_BRGT_LEVEL_1_ADDR, uRegValue);
    }

    if (psDemuraDataConfig->uCfg5En)
    {
      uRegValue = 0;
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_OPR_LEVEL_0, OPR_LVL_0, psDemuraDataConfig->uCfg5Param0[0]);
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_OPR_LEVEL_0, OPR_LVL_1, psDemuraDataConfig->uCfg5Param0[1]);
      out_dword(uRegOffset + HWIO_MDP_DEMURA_0_OPR_LEVEL_0_ADDR, uRegValue);

      uRegValue = 0;
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_OPR_LEVEL_1, OPR_LVL_2, psDemuraDataConfig->uCfg5Param0[2]);
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_OPR_LEVEL_1, OPR_LVL_3, psDemuraDataConfig->uCfg5Param0[3]);
      out_dword(uRegOffset + HWIO_MDP_DEMURA_0_OPR_LEVEL_1_ADDR, uRegValue);

      uRegValue = 0;
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_OPR_BRGT_LEVEL_0, OPR_BRGT_LVL_0, psDemuraDataConfig->uCfg5Param1[0]);
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_OPR_BRGT_LEVEL_0, OPR_BRGT_LVL_1, psDemuraDataConfig->uCfg5Param1[1]);
      out_dword(uRegOffset + HWIO_MDP_DEMURA_0_OPR_BRGT_LEVEL_0_ADDR, uRegValue);

      uRegValue = 0;
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_OPR_BRGT_LEVEL_1, OPR_BRGT_LVL_2, psDemuraDataConfig->uCfg5Param1[2]);
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_OPR_BRGT_LEVEL_1, OPR_BRGT_LVL_3, psDemuraDataConfig->uCfg5Param1[3]);
      out_dword(uRegOffset + HWIO_MDP_DEMURA_0_OPR_BRGT_LEVEL_1_ADDR, uRegValue);
    }

    uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_DEMURA_CONFIG, HFC_EN,         psDemuraDataConfig->uCfg0En);
    uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_DEMURA_CONFIG, LFC_EN,         psDemuraDataConfig->uCfg1En);
    uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_DEMURA_CONFIG, PORTRAIT_EN,    psDemuraDataConfig->uCfg2En);
    uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_DEMURA_CONFIG, ACL_ADAPT_EN,   psDemuraDataConfig->uCfg3En);
    uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_DEMURA_CONFIG, BRGT_ADAPT_EN,  0);
    uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_DEMURA_CONFIG, BPC_R,          psDemuraDataConfig->uC0Depth);
    uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_DEMURA_CONFIG, BPC_G,          psDemuraDataConfig->uC1Depth);
    uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_DEMURA_CONFIG, BPC_B,          psDemuraDataConfig->uC2Depth);
    uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_DEMURA_CONFIG, HFC_SRC_SEL,    psDemuraDataConfig->uSrcID);
    uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_DEMURA_CONFIG, LFC_HIGH_IDX,   psDemuraDataConfig->uCfg1HighIdx);
    uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DEMURA_0_DEMURA_CONFIG, LFC_LOW_IDX,    psDemuraDataConfig->uCfg1LowIdx);
    out_dword(uRegOffset + HWIO_MDP_DEMURA_0_DEMURA_CONFIG_ADDR, uRegValue);

  }

  return eStatus;
}




#ifdef __cplusplus
}
#endif
