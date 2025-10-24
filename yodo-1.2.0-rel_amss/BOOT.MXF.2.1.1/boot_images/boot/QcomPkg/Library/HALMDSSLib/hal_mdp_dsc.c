/*! \file */

/*
===========================================================================

FILE:         hal_mdp_dsc.c

DESCRIPTION:  This file contains a list of functions to work with Display Stream
              Compression (DSC) Encoder module

===========================================================================
===========================================================================
Copyright (c) 2012 - 2021 Qualcomm Technologies, Inc.
All Rights Reserved.
Qualcomm Technologies Proprietary and Confidential.
===========================================================================
*/

/*------------------------------------------------------------------------------
 * Include Files
 *----------------------------------------------------------------------------*/
#include "hal_mdp_i.h"
#include "hal_mdp_osal.h"
#include "hal_mdp_dsc.h"

#ifdef __cplusplus
extern "C" {
#endif


#define DSC_CORE_MAX    1       /* only use first core to support RGB format only */

DSC_DesciptorType   gDSCDesciptor[DSC_CORE_MAX];


/*------------------------------------------------------------------------
 * Private Function Definitions
 *------------------------------------------------------------------------ */

int Ceil(double fNumber)
{
  int  num;

  if(fNumber >= 0)
  {
    if(fNumber == (int)fNumber )
    {
       num = fNumber;
    }
    else
    {
       num = fNumber;
       num++;
    }
  }
  else
  {
    num = fNumber;
  }

  return num;
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_Validate_DSCId()
*/
/*!
* \brief
*     Validates that DSC Id is within allowed range
*
* \param [in] eDSCEncEngineId    - none, 0, 1, 2 etc.
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_MDP_Validate_DSCId(HAL_MDP_DSCId  eDSCEncEngineId)
{
  HAL_MDSS_ErrorType   eStatus = HAL_MDSS_STATUS_SUCCESS;

  if ((HAL_MDP_DSC_NONE == eDSCEncEngineId) ||
	  (HAL_MDP_DSC_MAX  <= eDSCEncEngineId))
  {
	eStatus = HAL_MDSS_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  return eStatus;
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_Get_DSC_Core_BaseOffset()
*/
/*!
* \brief
*     Returns register offset of DSC Core
*
* \param [in] eDSCId    - none, 0, 1, 2 etc.
*
* \retval uint32
*
****************************************************************************/
static  uintPtr HAL_MDP_Get_DSC_Core_BaseOffset(HAL_MDP_DSCId  eDSCId)
{
   uintPtr   uRegOffset  = 0x00000000;
   uint32    uCoreIndex  = HAL_MDP_DSC_CORE_0;

   if (HAL_MDSS_STATUS_SUCCESS == HAL_MDP_Validate_DSCId(eDSCId))
   {
      if ((eDSCId >= HAL_MDP_DSC_4) &&
          (eDSCId <= HAL_MDP_DSC_5))
      {
         uCoreIndex = HAL_MDP_DSC_CORE_2;
      }
      else if ((eDSCId >= HAL_MDP_DSC_2) &&
               (eDSCId <= HAL_MDP_DSC_3))
      {
         uCoreIndex = HAL_MDP_DSC_CORE_1;
      }
      else
      {
         uCoreIndex = HAL_MDP_DSC_CORE_0;
      }

      uRegOffset  = uMDPDSCCoreBaseOffset[uCoreIndex];
   }
   return uRegOffset;
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_Get_DSC_Encoder_BaseOffset()
*/
/*!
* \brief
*     Returns register offset of DSC Encoder
*
* \param [in] eDSCId    - none, 0, 1, 2 etc.
*
* \retval uint32
*
****************************************************************************/
static  uintPtr HAL_MDP_Get_DSC_Encoder_BaseOffset(HAL_MDP_DSCId  eDSCId)
{
   uintPtr   uRegOffset  = 0x00000000;

   if (HAL_MDSS_STATUS_SUCCESS == HAL_MDP_Validate_DSCId(eDSCId))
   {
      uRegOffset  = uMDPDSCEncBaseOffset[eDSCId];
   }
   return uRegOffset;
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_Get_DSC_Ctl_BaseOffset()
*/
/*!
* \brief
*     Returns register offset of DSC Ctl
*
* \param [in] eDSCId    - none, 0, 1, 2 etc.
*
* \retval uint32
*
****************************************************************************/
static  uintPtr HAL_MDP_Get_DSC_Ctl_BaseOffset(HAL_MDP_DSCId  eDSCId)
{
   uintPtr   uRegOffset  = 0x00000000;

   if (HAL_MDSS_STATUS_SUCCESS == HAL_MDP_Validate_DSCId(eDSCId))
   {
      uRegOffset  = uMDPDSCCtlBaseOffset[eDSCId];
   }
   return uRegOffset;
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_DSC_Init()
*/
/*!
* \brief
*     Initialize DSC encoder parameters 
*
* \param [in] pDSCInfo    - Encoder Parameter Configuration information to select the control/data flow
*
* \retval void
*
****************************************************************************/
static void HAL_MDP_DSC_Init(DSC_DesciptorType *pDSC)
{
   const DSCConfigType     *pConfig = pDSC->pConfig;

   pDSC->dsc_version_major = pConfig->uMajor;
   pDSC->dsc_version_minor = pConfig->uMinor;
   pDSC->bits_per_component = pConfig->uBPC;
   pDSC->convert_rgb        = (pConfig->eColorSpace == HAL_MDP_DSCCOLORSPACE_RGB ? 1 : 0);

   pDSC->native_420         = (pConfig->eChroma == HAL_MDP_DSCCHROMA_YUV420 ? 1 : 0);
   pDSC->native_422         = (pConfig->eChroma == HAL_MDP_DSCCHROMA_YUV422 ? 1 : 0);
   pDSC->simple_422         = 0;

   if (pConfig->eChroma == HAL_MDP_DSCCHROMA_RGB444)
   {
      pDSC->bits_per_pixel     = pConfig->fBPP;
   }
   else
   {
      pDSC->bits_per_pixel     = pConfig->fBPP * 2;
   }


   /* below variables are always fixed */
   pDSC->vbr_enable           = 0;
   pDSC->pps_identifier       = 0;
   pDSC->rc_model_size        = 8192;
   pDSC->rc_edge_factor       = 6;
   pDSC->rc_tgt_offset_hi     = 3;
   pDSC->rc_tgt_offset_low    = 3;
   pDSC->rc_buf_thresh        = rc_buf_thresh_list;

   /* below are from Looked up base on config (Profile) index */
   pDSC->rc_parameter         = &rc_parameters_table[pDSC->dsc_config_index];
   pDSC->rc_mini_qp           = &rc_range_miniqp_table[pDSC->dsc_config_index][0];
   pDSC->rc_max_qp            = &rc_range_maxqp_table[pDSC->dsc_config_index][0];
   pDSC->rc_offset            = &rc_range_offset_table[pDSC->dsc_config_index][0];

   pDSC->pConfig              = &gDSCProfile_table[pDSC->dsc_config_index];
   pDSC->pCoreConfig          = &gDSCCoreConfig_table[pDSC->core_config_index];

}

/****************************************************************************
*
** FUNCTION: HAL_MDP_DSC_Calculated_final_offset()
*/
/*!
* \brief
*     Initialize DSC encoder parameters 
*
* \param [in] pDSCInfo    - Encoder Parameter Configuration information
*
* \retval void
*
****************************************************************************/
static void HAL_MDP_DSC_Calculated_final_offset(DSC_DesciptorType *pDSC)
{
   pDSC->final_offset  = pDSC->rc_model_size - pDSC->rc_parameter->initial_xmit_delay * pDSC->bits_per_pixel + pDSC->num_extra_mux_bits;
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_DSC_Calculated_bpg_offset()
*/
/*!
* \brief
*     Initialize DSC encoder parameters 
*
* \param [in] pDSCInfo    - Encoder Parameter Configuration information
*
* \retval void
*
****************************************************************************/
static void HAL_MDP_DSC_Calculated_bpg_offset(DSC_DesciptorType *pDSC)
{

   pDSC->nfl_bpg_offset       = Ceil((double)(2048 * pDSC->first_line_bpg_offset) / (pDSC->slice_height - 1));

   pDSC->slice_bpg_offset     = Ceil((2048 * (double)(pDSC->rc_model_size - pDSC->rc_parameter->initial_fullness_offset + pDSC->num_extra_mux_bits) /pDSC->groups_total));

   if (pDSC->pConfig->eChroma == HAL_MDP_DSCCHROMA_YUV420)
   {
      pDSC->nsl_bpg_offset    = Ceil((double)(2048 * pDSC->rc_parameter->second_line_bpg_offset) / (pDSC->slice_height - 1));
   }
   else
   {
      pDSC->nsl_bpg_offset    = 0;
   }
}
/****************************************************************************
*
** FUNCTION: HAL_MDP_DSC_Calculated_chunk_size()
*/
/*!
* \brief
*     Initialize DSC encoder parameters 
*
* \param [in] pDSCInfo    - Encoder Parameter Configuration information
*
* \retval void
*
****************************************************************************/

static void HAL_MDP_DSC_Calculated_chunk_size(DSC_DesciptorType *pDSC)
{
   pDSC->chunk_size = Ceil((double)(pDSC->slice_width_mod * pDSC->bits_per_pixel) / 8);
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_DSC_Calculate_line_bpg_offset()
*/
/*!
* \brief
*     calculate MDP DSC Controller configure parameters
*
* \param [in] pDSCInfo    - Encoder Parameter Configuration information to select the control/data flow
*
* \retval void
*
****************************************************************************/
static void HAL_MDP_DSC_Calculated_first_line_bpg_offset(DSC_DesciptorType *pDSC)
{
   const DSCConfigType     *pConfig = pDSC->pConfig;

   if (pConfig->uMinor == 1)
   {
      if (pConfig->uSCR == 1)
      {
         pDSC->first_line_bpg_offset = 15;
      }
      else
      {
         pDSC->first_line_bpg_offset = 12;
      }
   }
   else
   {
       pDSC->first_line_bpg_offset    = MIN(((pDSC->slice_height < 8) ? pDSC->first_line_bpg_offset_b : pDSC->first_line_bpg_offset_a), 
                                            ((pDSC->uncompressed_bpg_rate  - 3) * pDSC->bits_per_pixel));
   }
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_DSC_Calculated()
*/
/*!
* \brief
*     calculate DSC Encodercalculated parameters
*
* \param [in] pDSCInfo    - Encoder Parameter Configuration information to select the control/data flow
*
* \retval void
*
****************************************************************************/
static void HAL_MDP_DSC_Calculated(DSC_DesciptorType *pDSC)
{

   pDSC->initial_dec_delay        = pDSC->hrd_delay - pDSC->rc_parameter->initial_xmit_delay;
   pDSC->initial_scale_value      = (8 * pDSC->rc_model_size / (pDSC->rc_model_size - pDSC->rc_parameter->initial_fullness_offset));

   pDSC->scale_increment_interval = (pDSC->final_scale_value > 9) ? pDSC->scale_increment_interval_temp : 0;

   pDSC->scale_decrement_interval = (pDSC->initial_scale_value > 8) ? (pDSC->groups_per_line/(pDSC->initial_scale_value - 8)) : 4095;

}

/****************************************************************************
*
** FUNCTION: HAL_MDP_DSC_Temp()
*/
/*!
* \brief
*     calculate DSC Temp prarmeters
*
* \param [in] pDSCInfo    - Encoder Parameter Configuration information to select the control/data flow
*
* \retval void
*
****************************************************************************/
static void HAL_MDP_DSC_Calculate_Temp(DSC_DesciptorType *pDSC)
{
   const DSCConfigType     *pConfig = pDSC->pConfig;

   pDSC->slice_width_mod            = (pConfig->eChroma == HAL_MDP_DSCCHROMA_RGB444) ? pDSC->slice_width : (pDSC->slice_width / 2);

   if (pConfig->eChroma == HAL_MDP_DSCCHROMA_YUV422)
   {
      pDSC->uncompressed_bpg_rate   = 3 * pDSC->bits_per_component * 4;
   }
   else
   {
      pDSC->uncompressed_bpg_rate   = ((3 * pDSC->bits_per_component) + ((pConfig->eColorSpace == HAL_MDP_DSCCOLORSPACE_YUV) ? 0 : 2)) * 3;
   }

   pDSC->first_line_bpg_offset_a    = 12 + (0.09 * (MIN(34, pDSC->slice_height - 8)));
   pDSC->first_line_bpg_offset_b    = 2 * (pDSC->slice_height - 1);

   pDSC->pixels_per_group           = 3;

   pDSC->groups_per_line            = (pDSC->slice_width_mod + pDSC->pixels_per_group - 1) / pDSC->pixels_per_group;


  HAL_MDP_DSC_Calculated_first_line_bpg_offset(pDSC);

   pDSC->min_rate_buffer_size        = pDSC->rc_model_size - pDSC->rc_parameter->initial_fullness_offset + pDSC->rc_parameter->initial_xmit_delay * pDSC->bits_per_pixel + pDSC->groups_per_line * pDSC->first_line_bpg_offset;

   pDSC->hrd_delay                   =  Ceil((double)pDSC->min_rate_buffer_size / pDSC->bits_per_pixel);

   pDSC->max_se_size_y               =  4 * pDSC->bits_per_component + 4;
   pDSC->max_se_size_c               =  4 * (pDSC->bits_per_component + pDSC->convert_rgb);
   pDSC->mux_word_size               =  (pDSC->bits_per_component >= 12 ? 64 : 48);

   if (pDSC->native_420)
   {
      pDSC->num_extra_mux_bits_temp  =  3 * pDSC->mux_word_size + (4 * pDSC->bits_per_component + 4) + 2 *  (4 * pDSC->bits_per_component) - 2;
   }
   else if (pDSC->native_422)
   {
      pDSC->num_extra_mux_bits_temp  =  4 * pDSC->mux_word_size + (4 * pDSC->bits_per_component + 4) + 3 *  (4 * pDSC->bits_per_component) - 2;
   }
   else
   {
      pDSC->num_extra_mux_bits_temp  =  3 * (pDSC->mux_word_size + (4 * pDSC->bits_per_component + 4) - 2);
   }

   HAL_MDP_DSC_Calculated_chunk_size(pDSC);

   pDSC->slice_bits                  = 8 * pDSC->slice_height * pDSC->chunk_size;

   pDSC->num_extra_mux_bits          = pDSC->num_extra_mux_bits_temp - (pDSC->mux_word_size - ((pDSC->slice_bits - pDSC->num_extra_mux_bits_temp) % pDSC->mux_word_size));

   HAL_MDP_DSC_Calculated_final_offset(pDSC);

   pDSC->final_scale_value           = (8 * pDSC->rc_model_size) / (pDSC->rc_model_size - pDSC->final_offset);


   pDSC->groups_total                = pDSC->groups_per_line * pDSC->slice_height;

   HAL_MDP_DSC_Calculated_bpg_offset(pDSC);

   pDSC->scale_increment_interval_temp =  (2048 * pDSC->final_offset) / ((pDSC->final_scale_value  - 9) * (pDSC->nfl_bpg_offset + pDSC->slice_bpg_offset + pDSC->nsl_bpg_offset));

}

/****************************************************************************
*
** FUNCTION: HAL_MDP_DSC_Calculate_MDP()
*/
/*!
* \brief
*     calculate MDP DSC Controller configure parameters
*
* \param [in] pDSCInfo    - Encoder Parameter Configuration information to select the control/data flow
*
* \retval void
*
****************************************************************************/
static void HAL_MDP_DSC_Calculate_Mdp(DSC_DesciptorType *pDSC)
{
   const DSCConfigType     *pConfig  = pDSC->pConfig;

   pDSC->slice_width_mod_3     = pDSC->slice_width % 3;

   pDSC->slice_last_group_size = (pDSC->slice_width_mod_3 == 0) ? 2 : ((pDSC->slice_width_mod_3 == 1) ? 0 : 1);

   pDSC->linebuffer_depth      = pDSC->bits_per_component + 1;
   pDSC->enable_422            = (pConfig->eChroma == HAL_MDP_DSCCHROMA_YUV422) ? 1 : 0;
   pDSC->enable_10bits_input   = (pDSC->bits_per_component == 10) ? 1 : 0;
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_DSC_Calculate_initial_lines()
*/
/*!
* \brief
*     calculate DSC initial line
*
* \param [in] pDSCInfo    - Encoder Parameter Configuration information to select the control/data flow
*
* \retval void
*
****************************************************************************/
static void HAL_MDP_DSC_Calculate_initial_lines(DSC_DesciptorType *pDSC)
{
   const DSCConfigType     *pConfig = pDSC->pConfig;
   const DSCCoreConfigType *pCore   = pDSC->pCoreConfig;

   if (pDSC->native_420 || pDSC->native_422)
   {
      pDSC->CompressBppGroup          = pConfig->fBPP * 2;
   }
   else
   {
      pDSC->CompressBppGroup          = pConfig->fBPP;
   }

   pDSC->max_muxword_size             =  (pCore->rtl_max_bpc >= 12 ? 64 : 48);
   pDSC->muxWordSize                  =  (pDSC->bits_per_component >= 12 ? 64 : 48);
   pDSC->ChunkBits                    = pDSC->chunk_size * 8;
   pDSC->rtl_num_components           = (pDSC->native_422 || pDSC->native_420) ? 4 : 3;
   pDSC->ob_data_width_4comps         = (pCore->rtl_output_data_width >= pDSC->max_muxword_size * 2) ?  pCore->rtl_output_data_width : pCore->rtl_output_data_width * 2;
   pDSC->ob_data_width_3comps         = (pCore->rtl_output_data_width >= pDSC->max_muxword_size) ?  pCore->rtl_output_data_width : pCore->rtl_output_data_width * 2;
   pDSC->ob_data_width                = (pDSC->rtl_num_components == 4) ? pDSC->ob_data_width_4comps : pDSC->ob_data_width_3comps;
   pDSC->ContainerSliceWidth          = (pDSC->native_422) ? pDSC->slice_width / 2: pDSC->slice_width;
   pDSC->output_rate                  = (pDSC->output_profile == BURST) ? pDSC->CompressBppGroup : pDSC->ob_data_width;
   pDSC->output_rate_ratio            = (float)pDSC->CompressBppGroup / pDSC->output_rate;
   pDSC->output_rate_ratio_complement = (float)1 - pDSC->output_rate_ratio;
   pDSC->output_ratio_offset          = pDSC->split_panel_enable * pDSC->multiplex_mode_enable * pDSC->de_raster_enable * (pDSC->num_of_active_hs > 1) * pDSC->output_rate_ratio * pDSC->num_of_active_hs * pDSC->output_rate_ratio_complement;
   pDSC->output_rate_extra_budget_bits = Ceil((double)(pDSC->output_rate_ratio_complement - pDSC->output_ratio_offset) * pDSC->ChunkBits);
   pDSC->multi_hs_extra_budget_bits_a  = pDSC->split_panel_enable * pDSC->de_raster_enable;
   pDSC->multi_hs_extra_budget_bits_b  = Ceil((float)(pDSC->num_of_active_hs - 1)/pDSC->num_of_active_hs * pDSC->ChunkBits) - pDSC->output_rate_extra_budget_bits;
   pDSC->multi_hs_extra_budget_bits_c  = pDSC->split_panel_enable * pDSC->multiplex_mode_enable;
   pDSC->multi_hs_extra_budget_bits_d  = (pDSC->num_of_active_ss > 1) * (pDSC->output_rate > pDSC->CompressBppGroup);

   if (pDSC->multi_hs_extra_budget_bits_a)
   {
      pDSC->multi_hs_extra_budget_bits = pDSC->multi_hs_extra_budget_bits_b;
   }
   else
   {
       if (pDSC->multi_hs_extra_budget_bits_c)
       {
          pDSC->multi_hs_extra_budget_bits = pDSC->ChunkBits;
       }
       else
       {
          if (pDSC->multi_hs_extra_budget_bits_d)
          {
             pDSC->multi_hs_extra_budget_bits = pDSC->ChunkBits;
          }
          else
          {
             pDSC->multi_hs_extra_budget_bits = pDSC->output_rate_extra_budget_bits;
          }
       }
    }

   pDSC->max_se_size            =  (pDSC->pCoreConfig->rtl_max_bpc + 1) * 4;
   pDSC->max_ssm_delay          = pDSC->max_se_size  + pDSC->max_muxword_size - 1;
   pDSC->obuf_latency           = Ceil((double)(9 * pDSC->ob_data_width + pDSC->muxWordSize) / pDSC->CompressBppGroup) + 1;
   pDSC->input_ssm_out_latency  =  pDSC->pCoreConfig->pipeline_latency + (3 * (pDSC->max_ssm_delay + 2) * pDSC->num_of_active_ss);
   pDSC->base_hs_latency        = pDSC->rc_parameter->initial_xmit_delay + pDSC->input_ssm_out_latency + pDSC->obuf_latency;
   pDSC->multi_hs_extra_latency = Ceil((double)pDSC->multi_hs_extra_budget_bits / pDSC->CompressBppGroup);
   pDSC->initial_lines          = Ceil((double)(pDSC->base_hs_latency + pDSC->multi_hs_extra_latency) / pDSC->ContainerSliceWidth);

}

/****************************************************************************
*
** FUNCTION: HAL_MDP_DSC_ProfileIndex()
*/
/*!
* \brief
*     get profile index base on minor, chrome 
*
* \param [in] pDSCInfo    - Encoder Parameter Configuration information to select the control/data flow
*
* \retval void
*
****************************************************************************/
static int HAL_MDP_DSC_ProfileIndex(HAL_MDP_DSCInfoType   *pDSCInfo)
{
   HAL_MDP_DSC_EncoderConfigType   *pDSCEncConfig = pDSCInfo->pDSCEncoderCfg;
   const DSCConfigType             *pProfile      = &gDSCProfile_table[0];
   uint32                           uProfileIndex = 0;

   while (uProfileIndex < DSC_PROFILE_MAX_INDEX)
   {
      if ((pDSCEncConfig->uDSCMajor        == pProfile->uMajor) && 
          (pDSCEncConfig->uDSCMinor        == pProfile->uMinor) &&
          (pDSCEncConfig->uDSCScr          == pProfile->uSCR)   &&
          (pDSCEncConfig->eDSCChromaFormat == pProfile->eChroma))
      {
         if ((pDSCEncConfig->uBPC == pProfile->uBPC) && 
             (pDSCEncConfig->uBPP == (uint32)pProfile->fBPP))
         {
            break;
         }

      } 
      pProfile++;
      uProfileIndex++;
   }

   if (uProfileIndex >= DSC_PROFILE_MAX_INDEX)
   {
      uProfileIndex = 0;       /* can not find, use first entry */
   }

   return uProfileIndex;
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_DSC_CoreIndex()
*/
/*!
* \brief
*     get profile index base on minor, chrome 
*
* \param [in] pDSCInfo    - Encoder Parameter Configuration information to select the control/data flow
*
* \retval void
*
****************************************************************************/
static int HAL_MDP_DSC_CoreIndex(HAL_MDP_DSCId   eDSCId)
{
   HAL_MDP_DSC_CoreFormatIndex eDSCCoreFormatIndex = HAL_MDP_DSC_V1_2a_2HS_2SS_2IN_10BIT_V1_2; //set default to RGB format
   
   if ((NULL                    != pgsMdpHwInfo->pDSCEncoderFormat) && 
       (HAL_MDSS_STATUS_SUCCESS == HAL_MDP_Validate_DSCId(eDSCId)))
   {  
      eDSCCoreFormatIndex = pgsMdpHwInfo->pDSCEncoderFormat[eDSCId];
   }

   return eDSCCoreFormatIndex;
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_DSC_Commit()
*/
/*!
* \brief
*     Commit MDP DSC controller and encoder register -- for Lahaina
*
* \param [in] pDSCInfo    - Encoder Parameter Configuration information
*
* \retval void
*
****************************************************************************/
static void HAL_MDP_DSC_ENC_Commit(HAL_MDP_DSCId           eDSCId, 
                                   HAL_MDP_DSCInfoType    *pDSCInfo)
{
  if ((NULL == pDSCInfo)                  ||
      (NULL == pDSCInfo->pDSCEncoderCfg)  ||
      (NULL == pDSCInfo->pDSC))
  {
  }
  else
  {
    HAL_MDP_DSC_EncoderConfigType *pDSCEncConfig = pDSCInfo->pDSCEncoderCfg;
    DSC_DesciptorType             *pDSC          = pDSCInfo->pDSC;
    uintPtr                        uCoreOffset   = 0x00000000;
    uintPtr                        uBlkRegOffset = 0x00000000;
    uint32                         uRegValue     = 0x00000000;
    uint32                         uActiveSSNum  = 1;
    uint32                         uData;
    float                          fFraction;

    // Sanity check of active SS and HS number, default to 1 to recovery from error input
    if (0 != pDSC->num_of_active_ss)
    {
      uActiveSSNum = pDSC->num_of_active_ss;
    } 

    uCoreOffset   = HAL_MDP_Get_DSC_Core_BaseOffset(eDSCId);
    uBlkRegOffset = uCoreOffset;

    uRegValue   = in_dword(HWIO_MDP_DSC_0_DSC_CMN_ENC_MAIN_CONF_ADDR + uBlkRegOffset);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_CMN_ENC_MAIN_CONF, SPLIT_PANEL_ENABLE,    pDSCEncConfig->bSplitDisplayEnable);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_CMN_ENC_MAIN_CONF, MULTIPLEX_MODE_ENABLE, pDSCEncConfig->bHardSliceMuxEnable);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_CMN_ENC_MAIN_CONF, MULTIPLEX_OUT_SEL,     0);     /* Data output always on the lower dsc, dsc-0 */
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_CMN_ENC_MAIN_CONF, MULTIPLEX_EOC_ENABLE,  0);     /* zero insertion is not supported */
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_CMN_ENC_MAIN_CONF, NUM_OF_SS,             uActiveSSNum);
    out_dword(HWIO_MDP_DSC_0_DSC_CMN_ENC_MAIN_CONF_ADDR + uBlkRegOffset, uRegValue);

    // DSC_X_ENC
    uBlkRegOffset  = HAL_MDP_Get_DSC_Encoder_BaseOffset(eDSCId);
    uBlkRegOffset += uCoreOffset;

    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_ENC_DF_CTRL, INITIAL_LINES, pDSC->initial_lines);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_ENC_DF_CTRL, VIDEO_MODE, pDSC->video_mode);
  
    if (1 == uActiveSSNum)
    {
      // If total active slice is 1
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_ENC_DF_CTRL, OB_MAX_ADDR, pDSC->pCoreConfig->ob_max_addr_1ss);
    }
    else
    {
      // If total active slice are greater than 1
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_ENC_DF_CTRL, OB_MAX_ADDR, pDSC->pCoreConfig->ob_max_addr_2ss);
    }

    out_dword(HWIO_MDP_DSC_0_DSC_0_ENC_ENC_DF_CTRL_ADDR + uBlkRegOffset, uRegValue);

    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_MAIN_CONF, DSC_VERSION_MINOR, pDSC->dsc_version_minor);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_MAIN_CONF, NATIVE_422, pDSC->native_422);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_MAIN_CONF, NATIVE_420, pDSC->native_420);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_MAIN_CONF, BLOCK_PRED_ENABLE, pDSC->block_pred_enable);

    uData       = (uint8)pDSC->bits_per_pixel;
    uData      &= 0x3f;   /* 6 bits */
    uData     <<= 4;

    /* fraction parts of bpp */
    fFraction   = pDSC->bits_per_pixel - (uint32)pDSC->bits_per_pixel;
    fFraction  *= 10000;
    fFraction  *= 16;
    fFraction  /= 10000;
    uData      |= (((uint8)fFraction) & 0x0f);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_MAIN_CONF, BITS_PER_PIXEL, uData);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_MAIN_CONF, LINEBUF_DEPTH, pDSC->linebuffer_depth);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_MAIN_CONF, CONVERT_RGB, pDSC->convert_rgb);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_MAIN_CONF, BITS_PER_COMPONENT, pDSC->bits_per_component);
    out_dword(HWIO_MDP_DSC_0_DSC_0_ENC_DSC_MAIN_CONF_ADDR + uBlkRegOffset, uRegValue);

    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_PICTURE_SIZE, PICTURE_HEIGHT, pDSC->picture_height);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_PICTURE_SIZE, PICTURE_WIDTH, pDSC->picture_width);
    out_dword(HWIO_MDP_DSC_0_DSC_0_ENC_DSC_PICTURE_SIZE_ADDR + uBlkRegOffset, uRegValue);

    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_SLICE_SIZE, SLICE_HEIGHT, pDSC->slice_height);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_SLICE_SIZE, SLICE_WIDTH, pDSC->slice_width);
    out_dword(HWIO_MDP_DSC_0_DSC_0_ENC_DSC_SLICE_SIZE_ADDR + uBlkRegOffset, uRegValue);

    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_MISC_SIZE, CHUNK_SIZE, pDSC->chunk_size);
    out_dword(HWIO_MDP_DSC_0_DSC_0_ENC_DSC_MISC_SIZE_ADDR + uBlkRegOffset, uRegValue);

    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_HRD_DELAYS, INITIAL_DEC_DELAY, pDSC->initial_dec_delay);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_HRD_DELAYS, INITIAL_XMIT_DELAY, pDSC->rc_parameter->initial_xmit_delay);
    out_dword(HWIO_MDP_DSC_0_DSC_0_ENC_DSC_HRD_DELAYS_ADDR + uBlkRegOffset, uRegValue);

    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_SCALE, INITIAL_SCALE_VALUE, pDSC->initial_scale_value);
    out_dword(HWIO_MDP_DSC_0_DSC_0_ENC_DSC_RC_SCALE_ADDR + uBlkRegOffset, uRegValue);

    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_SCALE_INC_DEC, SCALE_DECREMENT_INTERVAL, pDSC->scale_decrement_interval);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_SCALE_INC_DEC, SCALE_INCREMENT_INTERVAL, pDSC->scale_increment_interval);
    out_dword(HWIO_MDP_DSC_0_DSC_0_ENC_DSC_RC_SCALE_INC_DEC_ADDR + uBlkRegOffset, uRegValue);

    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_OFFSETS_1, SECOND_LINE_BPG_OFFSET, pDSC->rc_parameter->second_line_bpg_offset);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_OFFSETS_1, FIRST_LINE_BPG_OFFSET, pDSC->first_line_bpg_offset);
    out_dword(HWIO_MDP_DSC_0_DSC_0_ENC_DSC_RC_OFFSETS_1_ADDR + uBlkRegOffset, uRegValue);

    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_OFFSETS_2, SLICE_BPG_OFFSET, pDSC->slice_bpg_offset);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_OFFSETS_2, NFL_BPG_OFFSET, pDSC->nfl_bpg_offset);
    out_dword(HWIO_MDP_DSC_0_DSC_0_ENC_DSC_RC_OFFSETS_2_ADDR + uBlkRegOffset, uRegValue);

    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_OFFSETS_3, FINAL_OFFSET, pDSC->final_offset);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_OFFSETS_3, INITIAL_OFFSET, pDSC->rc_parameter->initial_fullness_offset);
    out_dword(HWIO_MDP_DSC_0_DSC_0_ENC_DSC_RC_OFFSETS_3_ADDR + uBlkRegOffset, uRegValue);

    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_OFFSETS_4, SECOND_LINE_OFFSET_ADJ, pDSC->rc_parameter->second_line_offset_adj);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_OFFSETS_4, NSL_BPG_OFFSET, pDSC->nsl_bpg_offset);
    out_dword(HWIO_MDP_DSC_0_DSC_0_ENC_DSC_RC_OFFSETS_4_ADDR + uBlkRegOffset, uRegValue);

    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_FLATNESS_QP, FLATNESS_DET_THRESH, pDSC->rc_parameter->flatness_det_thresh);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_FLATNESS_QP, FLATNESS_MAX_QP, pDSC->rc_parameter->flatness_max_qp);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_FLATNESS_QP, FLATNESS_MIN_QP, pDSC->rc_parameter->flatness_min_qp);
    out_dword(HWIO_MDP_DSC_0_DSC_0_ENC_DSC_FLATNESS_QP_ADDR + uBlkRegOffset, uRegValue);

    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MODEL_SIZE, RC_MODEL_SIZE, pDSC->rc_model_size);
    out_dword(HWIO_MDP_DSC_0_DSC_0_ENC_DSC_RC_MODEL_SIZE_ADDR + uBlkRegOffset, uRegValue);

    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_CONFIG, RC_TGT_OFFSET_LO, pDSC->rc_tgt_offset_low);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_CONFIG, RC_TGT_OFFSET_HI, pDSC->rc_tgt_offset_hi);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_CONFIG, RC_QUANT_INCR_LIMIT1, pDSC->rc_parameter->rc_quant_incr_limit1);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_CONFIG, RC_QUANT_INCR_LIMIT0, pDSC->rc_parameter->rc_quant_incr_limit0);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_CONFIG, RC_EDGE_FACTOR, pDSC->rc_edge_factor);
    out_dword(HWIO_MDP_DSC_0_DSC_0_ENC_DSC_RC_CONFIG_ADDR + uBlkRegOffset, uRegValue);


    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_BUF_THRESH_0, RC_BUF_THRESH_3, pDSC->rc_buf_thresh[3] >> 6);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_BUF_THRESH_0, RC_BUF_THRESH_2, pDSC->rc_buf_thresh[2] >> 6);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_BUF_THRESH_0, RC_BUF_THRESH_1, pDSC->rc_buf_thresh[1] >> 6);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_BUF_THRESH_0, RC_BUF_THRESH_0, pDSC->rc_buf_thresh[0] >> 6);
    out_dword(HWIO_MDP_DSC_0_DSC_0_ENC_DSC_RC_BUF_THRESH_0_ADDR + uBlkRegOffset, uRegValue);

    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_BUF_THRESH_1, RC_BUF_THRESH_7, pDSC->rc_buf_thresh[7] >> 6);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_BUF_THRESH_1, RC_BUF_THRESH_6, pDSC->rc_buf_thresh[6] >> 6);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_BUF_THRESH_1, RC_BUF_THRESH_5, pDSC->rc_buf_thresh[5] >> 6);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_BUF_THRESH_1, RC_BUF_THRESH_4, pDSC->rc_buf_thresh[4] >> 6);
    out_dword(HWIO_MDP_DSC_0_DSC_0_ENC_DSC_RC_BUF_THRESH_1_ADDR + uBlkRegOffset, uRegValue);

    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_BUF_THRESH_2, RC_BUF_THRESH_11, pDSC->rc_buf_thresh[11] >> 6);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_BUF_THRESH_2, RC_BUF_THRESH_10, pDSC->rc_buf_thresh[10] >> 6);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_BUF_THRESH_2, RC_BUF_THRESH_9, pDSC->rc_buf_thresh[9] >> 6);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_BUF_THRESH_2, RC_BUF_THRESH_8, pDSC->rc_buf_thresh[8] >> 6);
    out_dword(HWIO_MDP_DSC_0_DSC_0_ENC_DSC_RC_BUF_THRESH_2_ADDR + uBlkRegOffset, uRegValue);


    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_BUF_THRESH_3, RC_BUF_THRESH_13, pDSC->rc_buf_thresh[13] >> 6);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_BUF_THRESH_3, RC_BUF_THRESH_12, pDSC->rc_buf_thresh[12] >> 6);
    out_dword(HWIO_MDP_DSC_0_DSC_0_ENC_DSC_RC_BUF_THRESH_3_ADDR + uBlkRegOffset, uRegValue);

    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MIN_QP_0, RANGE_MIN_QP_4, pDSC->rc_mini_qp[4]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MIN_QP_0, RANGE_MIN_QP_3, pDSC->rc_mini_qp[3]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MIN_QP_0, RANGE_MIN_QP_2, pDSC->rc_mini_qp[2]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MIN_QP_0, RANGE_MIN_QP_1, pDSC->rc_mini_qp[1]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MIN_QP_0, RANGE_MIN_QP_0, pDSC->rc_mini_qp[0]);
    out_dword(HWIO_MDP_DSC_0_DSC_0_ENC_DSC_RC_MIN_QP_0_ADDR + uBlkRegOffset, uRegValue);

    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MIN_QP_1, RANGE_MIN_QP_9, pDSC->rc_mini_qp[9]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MIN_QP_1, RANGE_MIN_QP_8, pDSC->rc_mini_qp[8]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MIN_QP_1, RANGE_MIN_QP_7, pDSC->rc_mini_qp[7]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MIN_QP_1, RANGE_MIN_QP_6, pDSC->rc_mini_qp[6]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MIN_QP_1, RANGE_MIN_QP_5, pDSC->rc_mini_qp[5]);
    out_dword(HWIO_MDP_DSC_0_DSC_0_ENC_DSC_RC_MIN_QP_1_ADDR + uBlkRegOffset, uRegValue);

    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MIN_QP_2, RANGE_MIN_QP_14, pDSC->rc_mini_qp[14]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MIN_QP_2, RANGE_MIN_QP_13, pDSC->rc_mini_qp[13]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MIN_QP_2, RANGE_MIN_QP_12, pDSC->rc_mini_qp[12]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MIN_QP_2, RANGE_MIN_QP_11, pDSC->rc_mini_qp[11]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MIN_QP_2, RANGE_MIN_QP_10, pDSC->rc_mini_qp[10]);
    out_dword(HWIO_MDP_DSC_0_DSC_0_ENC_DSC_RC_MIN_QP_2_ADDR + uBlkRegOffset, uRegValue);

    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MAX_QP_0, RANGE_MAX_QP_4, pDSC->rc_max_qp[4]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MAX_QP_0, RANGE_MAX_QP_3, pDSC->rc_max_qp[3]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MAX_QP_0, RANGE_MAX_QP_2, pDSC->rc_max_qp[2]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MAX_QP_0, RANGE_MAX_QP_1, pDSC->rc_max_qp[1]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MAX_QP_0, RANGE_MAX_QP_0, pDSC->rc_max_qp[0]);
    out_dword(HWIO_MDP_DSC_0_DSC_0_ENC_DSC_RC_MAX_QP_0_ADDR + uBlkRegOffset, uRegValue);

    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MAX_QP_1, RANGE_MAX_QP_9, pDSC->rc_max_qp[9]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MAX_QP_1, RANGE_MAX_QP_8, pDSC->rc_max_qp[8]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MAX_QP_1, RANGE_MAX_QP_7, pDSC->rc_max_qp[7]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MAX_QP_1, RANGE_MAX_QP_6, pDSC->rc_max_qp[6]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MAX_QP_1, RANGE_MAX_QP_5, pDSC->rc_max_qp[5]);
    out_dword(HWIO_MDP_DSC_0_DSC_0_ENC_DSC_RC_MAX_QP_1_ADDR + uBlkRegOffset, uRegValue);

    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MAX_QP_2, RANGE_MAX_QP_14, pDSC->rc_max_qp[14]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MAX_QP_2, RANGE_MAX_QP_13, pDSC->rc_max_qp[13]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MAX_QP_2, RANGE_MAX_QP_12, pDSC->rc_max_qp[12]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MAX_QP_2, RANGE_MAX_QP_11, pDSC->rc_max_qp[11]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_MAX_QP_2, RANGE_MAX_QP_10, pDSC->rc_max_qp[10]);
    out_dword(HWIO_MDP_DSC_0_DSC_0_ENC_DSC_RC_MAX_QP_2_ADDR + uBlkRegOffset, uRegValue);


    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_RANGE_BPG_OFFSETS_0, RANGE_BPG_OFFSET_4, pDSC->rc_offset[4]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_RANGE_BPG_OFFSETS_0, RANGE_BPG_OFFSET_3, pDSC->rc_offset[3]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_RANGE_BPG_OFFSETS_0, RANGE_BPG_OFFSET_2, pDSC->rc_offset[2]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_RANGE_BPG_OFFSETS_0, RANGE_BPG_OFFSET_1, pDSC->rc_offset[1]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_RANGE_BPG_OFFSETS_0, RANGE_BPG_OFFSET_0, pDSC->rc_offset[0]);
    out_dword(HWIO_MDP_DSC_0_DSC_0_ENC_DSC_RC_RANGE_BPG_OFFSETS_0_ADDR + uBlkRegOffset, uRegValue);

    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_RANGE_BPG_OFFSETS_1, RANGE_BPG_OFFSET_9, pDSC->rc_offset[9]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_RANGE_BPG_OFFSETS_1, RANGE_BPG_OFFSET_8, pDSC->rc_offset[8]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_RANGE_BPG_OFFSETS_1, RANGE_BPG_OFFSET_7, pDSC->rc_offset[7]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_RANGE_BPG_OFFSETS_1, RANGE_BPG_OFFSET_6, pDSC->rc_offset[6]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_RANGE_BPG_OFFSETS_1, RANGE_BPG_OFFSET_5, pDSC->rc_offset[5]);
    out_dword(HWIO_MDP_DSC_0_DSC_0_ENC_DSC_RC_RANGE_BPG_OFFSETS_1_ADDR + uBlkRegOffset, uRegValue);

    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_RANGE_BPG_OFFSETS_2, RANGE_BPG_OFFSET_14, pDSC->rc_offset[14]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_RANGE_BPG_OFFSETS_2, RANGE_BPG_OFFSET_13, pDSC->rc_offset[13]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_RANGE_BPG_OFFSETS_2, RANGE_BPG_OFFSET_12, pDSC->rc_offset[12]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_RANGE_BPG_OFFSETS_2, RANGE_BPG_OFFSET_11, pDSC->rc_offset[11]);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_ENC_DSC_RC_RANGE_BPG_OFFSETS_2, RANGE_BPG_OFFSET_10, pDSC->rc_offset[10]);
    out_dword(HWIO_MDP_DSC_0_DSC_0_ENC_DSC_RC_RANGE_BPG_OFFSETS_2_ADDR + uBlkRegOffset, uRegValue);



    // DSC_X_CTL
    /*
    * ppb0 --> dsc-0-0
    * ppb1 --> dsc-0-1
    * ppb2 --> dsc-1-0
    * ppb3 --> dsc-1-1
    * see gMDP_ModulesMap[]
    * PP selection will be updated in MDPSetupPipe() once topology is determinded.
    */
    uBlkRegOffset  = HAL_MDP_Get_DSC_Ctl_BaseOffset(eDSCId);
    uBlkRegOffset += uCoreOffset;

    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_CTL, INPUT_XBAR_MUX_SEL, eDSCId - HAL_MDP_DSC_0);
    out_dword(HWIO_MDP_DSC_0_DSC_0_CTL_ADDR + uBlkRegOffset, uRegValue);  /* Ctl 0 */

    /* DSC_0_CFG: input data format */
    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_CFG, MULTIPLEX_MODE_ENABLE, pDSC->multiplex_mode_enable);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_CFG, SPLIT_PANEL_ENABLE,    pDSC->split_panel_enable);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_CFG, BIT_WIDTH,            (pDSC->bits_per_component == 10) ? 0 : 1);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_CFG, FORMAT,               (pDSC->pConfig->eChroma == HAL_MDP_DSCCHROMA_RGB444) ? 0 : 1);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_CFG, COLOR_SPACE,           pDSC->pConfig->eColorSpace);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_CFG, ENC_EN, 1);
    /*
    * MERGE_EN, CMD_MODE, BYTE_ALIGN and BYTE_ALIGNMENT are for 4HS merge (dual hard slice used to produce one frame image)
    */
    out_dword(HWIO_MDP_DSC_0_DSC_0_CFG_ADDR + uBlkRegOffset, uRegValue);  /* Ctl 0 */

    uRegValue   = 0x00;
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_DATA_IN_SWAP, ENDIAN, 0);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_DATA_IN_SWAP, BYTE5,  0x05);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_DATA_IN_SWAP, BYTE4,  0x04);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_DATA_IN_SWAP, BYTE3,  0x03);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_DATA_IN_SWAP, BYTE2,  0x02);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_DATA_IN_SWAP, BYTE1,  0x01);
    uRegValue   = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_DATA_IN_SWAP, BYTE0,  0x00);
    out_dword(HWIO_MDP_DSC_0_DSC_0_DATA_IN_SWAP_ADDR + uBlkRegOffset, uRegValue);
  }

}

/****************************************************************************
*
** FUNCTION: HAL_MDP_DSC_Prepare_PPS()
*/
/*!
* \brief
*     Prepares the 128-Byte PPS packet for the given encoder parameters
*
* \param [in] pDSCInfo    - Encoder Parameter Configuration information
* \param [in] uFlags                   - Reserved
*
* \retval void
*
****************************************************************************/
static void HAL_MDP_DSC_Prepare_PPS(HAL_MDP_DSCInfoType   *pDSCInfo, uint32 uFlags)
{
   DSC_DesciptorType             *pDSC = pDSCInfo->pDSC;
   uint8                         *pPkt = pDSCInfo->pPacketData;
   uint8                          uData;
   float                          fFraction;
   int                            i;

   MDSS_OSAL_MEMZERO(pPkt, 128);  /* 128 bytes */

   uData        = pDSC->dsc_version_major << 4;
   uData       |= pDSC->dsc_version_minor;
   pPkt[0]      =  uData;                           /* major + minor */

   pPkt[1]      = 0;                                /* pps_identify */

   pPkt[2]      = 0;                                /* reserved */

   uData        = pDSC->bits_per_component << 4;
   uData       |= (((uint8)pDSC->linebuffer_depth) & 0x0f);
   pPkt[3]      = uData; 

   uData        = ((((uint8)pDSC->block_pred_enable) & 0x01) << 5) |
                  ((((uint8)pDSC->convert_rgb) & 0x01) << 4) |
                  ((((uint8)pDSC->simple_422) & 0x01) << 3)  |
                  ((((uint8)pDSC->vbr_enable) & 0x01) << 2);

   pPkt[4]      =  uData;

   uData        = (uint8)pDSC->bits_per_pixel;
   uData       &= 0x3f;   /* 6 bits */
   uData      >>= 4;
   pPkt[4]     |= uData;       /* upper 2 bits of 6 bits of bpp */

   uData        = (uint8)pDSC->bits_per_pixel;
   uData       &= 0x0f;          /* lower 4 bits of 6 bits of bpp */
   pPkt[5]      = uData << 4;

   /* fraction parts of bpp */
   fFraction    = pDSC->bits_per_pixel - (uint32)pDSC->bits_per_pixel;
   fFraction   *= 10000;
   fFraction   *= 16;
   fFraction   /= 10000;
   uData        = (uint8)fFraction;
   uData       &= 0x0f;
   pPkt[5]     |= uData;      /* 4 bits of fraction parts of bpp */


   pPkt[6]      = (uint8)(pDSC->frame_height >> 8);
   pPkt[7]      = (uint8)(pDSC->frame_height);


   pPkt[8]      = (uint8)(pDSC->frame_width >> 8);
   pPkt[9]      = (uint8)(pDSC->frame_width);

   pPkt[10]     = (uint8)(pDSC->slice_height >> 8);
   pPkt[11]     = (uint8)(pDSC->slice_height);

   pPkt[12]     = (uint8)(pDSC->slice_width >> 8);
   pPkt[13]     = (uint8)(pDSC->slice_width);

   pPkt[14]     = (uint8)(pDSC->chunk_size >> 8);
   pPkt[15]     = (uint8)(pDSC->chunk_size);

   uData        = (pDSC->rc_parameter->initial_xmit_delay >> 8);
   pPkt[16]     = uData & 0x03;
   pPkt[17]     = (uint8)(pDSC->rc_parameter->initial_xmit_delay); 

   pPkt[18]     = (uint8)(pDSC->initial_dec_delay >> 8);
   pPkt[19]     = (uint8)(pDSC->initial_dec_delay);

   pPkt[20]     = 0x00;           /* reserved */

   uData        = pDSC->initial_scale_value;
   uData       &= 0x3f;
   pPkt[21]     = uData;

   pPkt[22]     = (uint8)(pDSC->scale_increment_interval >> 8);
   pPkt[23]     = (uint8)(pDSC->scale_increment_interval);

   uData        = (uint8)(pDSC->scale_decrement_interval >> 8);
   uData       &= 0x0f;
   pPkt[24]     = uData;
   pPkt[25]     = (uint8)(pDSC->scale_decrement_interval);

   pPkt[26]     = 0x00;           /* reserved */

   uData        = (uint8)(pDSC->first_line_bpg_offset);
   uData       &= 0x1f;
   pPkt[27]     = uData;

   pPkt[28]     = (uint8)(pDSC->nfl_bpg_offset >> 8);
   pPkt[29]     = (uint8)(pDSC->nfl_bpg_offset);

   pPkt[30]     = (uint8)(pDSC->slice_bpg_offset >> 8);
   pPkt[31]     = (uint8)(pDSC->slice_bpg_offset);

   pPkt[32]     = (uint8)(pDSC->rc_parameter->initial_fullness_offset >> 8);
   pPkt[33]     = (uint8)(pDSC->rc_parameter->initial_fullness_offset);

   pPkt[34]     = (uint8)(pDSC->final_offset >> 8);
   pPkt[35]     = (uint8)(pDSC->final_offset);

   uData        = pDSC->rc_parameter->flatness_min_qp;
   uData       &= 0x1f;
   pPkt[36]     = uData;

   uData        = pDSC->rc_parameter->flatness_max_qp;
   uData       &= 0x1f;
   pPkt[37]     = uData;


   /* rc parameter set -- start from 38 */
   pPkt[38]     = (uint8)(pDSC->rc_model_size >> 8);
   pPkt[39]     = (uint8)(pDSC->rc_model_size);

   uData        = pDSC->rc_edge_factor;
   uData       &= 0x0f;
   pPkt[40]     = uData;

   uData        = pDSC->rc_parameter->rc_quant_incr_limit0; 
   uData       &= 0x1f;
   pPkt[41]     = uData;

   uData        = pDSC->rc_parameter->rc_quant_incr_limit1; 
   uData       &= 0x1f;
   pPkt[42]     = uData;

   uData        = pDSC->rc_tgt_offset_hi; 
   uData       &= 0x0f;
   uData      <<= 4;
   uData       |= (uint8)(pDSC->rc_tgt_offset_low & 0x0f); 
   pPkt[43]     = uData;


   /* rc buffer thresh -- start from 44 */
   for (i = 0; i < RC_BUF_THRESH_MAX; i++)
   {
      uData        =  pDSC->rc_buf_thresh[i] >> 6;
      pPkt[44 + i] = uData;
   }

   /* rc range mini QP */
   for (i = 0; i < DSC_RC_RANGE_MAX; i++)
   {
      uint8 tmp;

      uData             =  pDSC->rc_mini_qp[i];
      uData           <<= 3;
      tmp               = pDSC->rc_max_qp[i];         /* range_mini_qp */
      tmp              &= 0x1f;
      tmp             >>= 2;
      uData            |= tmp;
      pPkt[58 + 2 * i]  = uData;

      uData             =  pDSC->rc_max_qp[i];         /* range_max_qp */
      uData           <<= 6;
      tmp               = pDSC->rc_offset[i];          /* range_bpg_offset */
      tmp              &= 0x3f;
      uData            |= tmp;
      pPkt[58 + 2 * i + 1]  = uData;
   }

   if (pDSC->dsc_version_minor == 2)
   {
      uData     = pDSC->native_420;
      uData    &= 0x01;
      uData   <<= 1;
      uData    |= (pDSC->native_422 & 0x01);
      pPkt[88]  = uData;

      uData     = pDSC->rc_parameter->second_line_bpg_offset;
      uData    &= 0x1f;
      pPkt[89]  = uData;

      uData     = (pDSC->nsl_bpg_offset >> 8);
      pPkt[90]  = uData;
      pPkt[91]  = pDSC->nsl_bpg_offset;

      uData     = (pDSC->rc_parameter->second_line_offset_adj >> 8);
      pPkt[92]  = uData;
      pPkt[93]  = pDSC->rc_parameter->second_line_offset_adj;
   }
   else
   {
      pPkt[88]  = 0x00;    // RESERVED
      pPkt[89]  = 0x00;    // RESERVED
      pPkt[90]  = 0x00;    // RESERVED
      pPkt[91]  = 0x00;    // RESERVED
      pPkt[92]  = 0x00;    // RESERVED
      pPkt[93]  = 0x00;    // RESERVED
   }

   /* byte 94 to 127 are all 0 */
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_DSC_Prepare()
*/
/*!
* \brief
*     Initializes the base data structures before preparing the encoder register configurations
*
* \param [in] pDSCInfo    - Encoder Parameter Configuration information
* \param [in] uFlags      - Reserved (must be 0x00)
*
* \retval void
*
****************************************************************************/
static void HAL_MDP_DSC_Prepare(HAL_MDP_DSCId  eDSCId, HAL_MDP_DSCInfoType   *pDSCInfo, uint32 uFlags)
{
   HAL_MDP_DSC_EncoderConfigType   *pCfg = pDSCInfo->pDSCEncoderCfg;
   DSC_DesciptorType               *pDSC = &gDSCDesciptor[0];   /* from global database */

   MDSS_OSAL_MEMZERO(pDSC, sizeof(*pDSC));

   pDSCInfo->pDSC = pDSC;      /* save */

   pDSC->dsc_config_index    = HAL_MDP_DSC_ProfileIndex(pDSCInfo); /* profile index */
   pDSC->core_config_index   = HAL_MDP_DSC_CoreIndex(eDSCId);    /* core index */

   /* Width of each HS to be programmed to DSC encoder register */
   if ((pCfg->bSplitMuxActive) ||
       (0 == pCfg->uNumOfActiveHS))
   {
     pDSC->picture_width     = pCfg->uInputFrameWidthInPixels;
   }
   else
   {
     pDSC->picture_width     = pCfg->uInputFrameWidthInPixels / pCfg->uNumOfActiveHS;
   }
   pDSC->picture_height      = pCfg->uInputFrameHeightInPixels;

   /* PPS Stream byte[8:9] take full panel width, no matter how many slices the panel is divided */
   pDSC->frame_width         = pCfg->uInputFrameWidthInPixels;
   pDSC->frame_height        = pCfg->uInputFrameHeightInPixels;

   pDSC->slice_width         = pCfg->uSliceWidth;
   pDSC->slice_height        = pCfg->uSliceHeight;

   pDSC->output_profile      = NOBURST;
   pDSC->de_raster_enable    = FALSE;

   pDSC->video_mode          = pCfg->bVideoMode;

   pDSC->block_pred_enable   = pCfg->bBlockPredEnable;

   pDSC->num_of_active_ss    = pCfg->uNumOfActiveSS;               /** soft slice */
   pDSC->num_of_active_hs    = pCfg->uNumOfActiveHS;               /** hard slice */

   pCfg->uSlicePerPacket     = pDSC->num_of_active_ss;

   pDSC->multiplex_mode_enable = pCfg->bHardSliceMuxEnable;
   pDSC->split_panel_enable    = pCfg->bSplitDisplayEnable; 


   if ((pCfg->bSplitDisplayEnable == TRUE) && 
       (pCfg->bHardSliceMuxEnable == FALSE))
   {
      pCfg->uSlicePerPacket    /= 2;
   }

   pDSC->pConfig             = &gDSCProfile_table[pDSC->dsc_config_index];
   pDSC->pCoreConfig         = &gDSCCoreConfig_table[pDSC->core_config_index];

   HAL_MDP_DSC_Init(pDSC);

   HAL_MDP_DSC_Calculate_Temp(pDSC);

   HAL_MDP_DSC_Calculated(pDSC);

   HAL_MDP_DSC_Calculate_Mdp(pDSC);

   HAL_MDP_DSC_Calculate_initial_lines(pDSC);

   HAL_MDP_DSC_Prepare_PPS(pDSCInfo, 0);
}


/****************************************************************************
*
** FUNCTION: HAL_MDP_DSC_ENC_ContextInit()
*/
/*!
* \brief
*     Initializes the base data structures before preparing the encoder register configurations
*
* \param [in] pDSCEncConfig    - Encoder Parameter Configuration information to select the control/data flow
* \param [in] uFlags           - Reserved (must be 0x00)
*
* \retval void
*
****************************************************************************/
static void HAL_MDP_DSC_ENC_ContextInit( HAL_MDP_DSCInfoType   *pDSCInfo, uint32 uFlags)
{

   HAL_MDP_DSC_EncoderConfigType *pDSCEncConfig = pDSCInfo->pDSCEncoderCfg;

   // Detect whether the data-path is for SPLIT_MUX or DUAL_PANEL mode
   if(TRUE == pDSCEncConfig->bSplitMuxActive)
   {
      pDSCEncConfig->bSplitDisplayEnable     = TRUE;   /* split */
      pDSCEncConfig->bHardSliceMuxEnable     = TRUE;   /* and merge */
   }
   else
   {
      if(TRUE == pDSCEncConfig->bSplitDispActive)
      {
         pDSCEncConfig->bSplitDisplayEnable     = TRUE;    /* slpit */
         pDSCEncConfig->bHardSliceMuxEnable     = FALSE;   /* no merge */
      }
   }

   // Interface Mode (Video or Command)
   if(HAL_MDP_INTERFACE_MODE_VIDEO == pDSCEncConfig->eInterfaceMode)
   {
      pDSCEncConfig->bVideoMode  = TRUE;
   }
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_DSC_ConfigPPMux()
*/
/*!
* \brief
*     Configures the data flow for the DSC encoder modules from PingPong XBAR Mux.
*
* \param [in] eDSCId              - none, 0, 1, 2 etc.
* \param [in] ePingPongId         - PingPong ID that feed data into DSC encoder modules.
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
static HAL_MDSS_ErrorType HAL_MDP_DSC_ConfigPPMux(HAL_MDP_DSCId          eDSCId,
                                                  HAL_MDP_PingPongId     ePingPongId)
{
   HAL_MDSS_ErrorType   eStatus       = HAL_MDSS_STATUS_SUCCESS;
   
   if ((eDSCId      >= HAL_MDP_DSC_MAX) ||
       (ePingPongId >= HAL_MDP_PINGPONG_MAX))
   { 
     eStatus = HAL_MDSS_STATUS_FAILED_INVALID_INPUT_PARAMETER;
   }
   else
   {
     uintPtr  uCoreOffset   = HAL_MDP_Get_DSC_Core_BaseOffset(eDSCId);
     uintPtr  uBlkRegOffset = HAL_MDP_Get_DSC_Ctl_BaseOffset(eDSCId) + uCoreOffset;
     uint32   uRegValue     = 0x00000000;

     // If PingPong is none, disconnect PP from DSC
     uRegValue = HWIO_OUT_FLD(uRegValue, MDP_DSC_0_DSC_0_CTL, INPUT_XBAR_MUX_SEL, ((HAL_MDP_PINGPONG_NONE == ePingPongId)? HWIO_MDP_DSC_0_DSC_0_CTL_INPUT_XBAR_MUX_SEL_BMSK : (ePingPongId - HAL_MDP_PINGPONG_0)));
     out_dword(HWIO_MDP_DSC_0_DSC_0_CTL_ADDR + uBlkRegOffset, uRegValue);
   }

   return eStatus;
}
/****************************************************************************
*
** FUNCTION: HAL_MDP_DSC_Setup()
*/
/*!
* \brief
*     Configures the control/data flow for the DSC encoder modules and also
*     configured the encoder configuration parameters to compress the pixel data
*
* \param [in] eDSCId    - none, 0, 1, 2 etc.
* \param [in] pDSCConfig         - Basic configuration parameters for DSC encoder
* \param [in] uFlags             - Reserved
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_MDP_DSC_Setup(HAL_MDP_DSCId          eDSCId,
                                     HAL_MDP_DSCInfoType   *pDSCInfo,
                                     uint32                 uFlags)
{
   HAL_MDSS_ErrorType   eStatus        = HAL_MDSS_STATUS_SUCCESS;

   if (NULL != pDSCInfo->pePingPongId)
   {
     eStatus = HAL_MDP_DSC_ConfigPPMux(eDSCId, *pDSCInfo->pePingPongId);
   }

   if(NULL != pDSCInfo->pDSCEncoderCfg)
   {
     HAL_MDP_DSC_ENC_Commit(eDSCId, pDSCInfo);
   }

   return eStatus;
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_DSC_GetPropery()
*/
/*!
* \brief
*     Used to extract the various types of information from DSC encoder module
*
* \param [in]     eDSCId             - none, 0, 1, 2 etc.
* \param [in/out] pDSCInfo           - Input information to extract the required data and
*                                      Output information prepared by HAL driver as response to 
*                                      the requested information.
* \param [in]     uFlags             - Reserved
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_MDP_DSC_GetPropery(HAL_MDP_DSCId          eDSCId,
                                          HAL_MDP_DSCInfoType   *pDSCInfo,
                                          uint32                 uFlags)
{
   HAL_MDSS_ErrorType             eStatus       = HAL_MDSS_STATUS_SUCCESS;
   HAL_MDP_DSC_EncoderConfigType *pDSCEncConfig = pDSCInfo->pDSCEncoderCfg;

   if(NULL != pDSCEncConfig)
   {
      // Initialize the DSC Context
      HAL_MDP_DSC_ENC_ContextInit(pDSCInfo, uFlags);

      HAL_MDP_DSC_Prepare(eDSCId, pDSCInfo, uFlags);
   }

   return eStatus;
}



#ifdef __cplusplus
}
#endif
