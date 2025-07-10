#ifndef HAL_MDP_DSC_2_H
#define HAL_MDP_DSC_2_H
/*=============================================================================
 
  File: hal_mdp_dsc.h
 
  Header file for common mdss driver
  
 
  Copyright (c) 2019-2021 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
=============================================================================*/

/*=============================================================================
   At XBLRamdump linker, the data section size almost be used up.
   To avoid increasing data section size which will cause linker error,
   Make all tables declared in this file as "const" which will have tables
   be relocated to rodata section instead of data section.
   
   To increase data section size, you have to reduce RAMDUMP code (text) szie.
   at Soc_cust.h, decrease size of SCL_RAMDUMP_CODE_SIZE
=============================================================================*/
#include "hal_mdp.h"

typedef enum {
   V1_2_RGB444_8BPC_8BPP,
   V1_2_RGB444_8BPC_12BPP,
   V1_2_RGB444_10BPC_8BPP,
   V1_2_RGB444_10BPC_9BPP,
   V1_2_RGB444_10BPC_10BPP,
   V1_2_RGB444_10BPC_15BPP,

   V1_2_YUV422_8BPC_7BPP,
   V1_2_YUV422_8BPC_8BPP,
   V1_2_YUV422_10BPC_7BPP,
   V1_2_YUV422_10BPC_8BPP,
   V1_2_YUV422_10BPC_10BPP,
   V1_2_YUV420_8BPC_6BPP,
   V1_2_YUV420_10BPC_6BPP,
   V1_2_YUV420_10BPC_7_5BPP,     /* 7.5 bpp */

   V1_1SCR_RGB444_8BPC_8BPP,
   V1_1SCR_RGB444_8BPC_12BPP,
   V1_1SCR_RGB444_10BPC_8BPP,
   V1_1SCR_RGB444_10BPC_10BPP,
   V1_1SCR_RGB444_10BPC_15BPP,

   V1_1_RGB444_8BPC_8BPP,
   V1_1_RGB444_8BPC_12BPP,
   V1_1_RGB444_10BPC_8BPP,
   V1_1_RGB444_10BPC_10BPP,
   V1_1_RGB444_10BPC_15BPP,
   DSC_PROFILE_MAX_INDEX,
} DSCProfileIndex;

typedef enum {
   BURST,
   NOBURST,
} DSCOutputProfile;

typedef struct
{
   uint32                     uMajor;
   uint32                     uMinor;
   HAL_MDP_DSCChromaType      eChroma;
   HAL_MDP_DSCColorSpaceType  eColorSpace;
   uint32                     uBPC;         /* source bpc */
   float                      fBPP;         /* target bpp */
   uint32                     uSCR;         /* sub revision */
} DSCConfigType;

const DSCConfigType gDSCProfile_table[] =
{
   /* version 1.2,  RGB */
   { 1, 2, HAL_MDP_DSCCHROMA_RGB444, HAL_MDP_DSCCOLORSPACE_RGB,  8,  8.0, 0}, /*   V1_2_RGB444_8BPC_8BPP     */
   { 1, 2, HAL_MDP_DSCCHROMA_RGB444, HAL_MDP_DSCCOLORSPACE_RGB,  8, 12.0, 0}, /*   V1_2_RGB444_8BPC_12BPP    */
   { 1, 2, HAL_MDP_DSCCHROMA_RGB444, HAL_MDP_DSCCOLORSPACE_RGB, 10,  8.0, 0}, /*   V1_2_RGB444_10BPC_8BPP    */
   { 1, 2, HAL_MDP_DSCCHROMA_RGB444, HAL_MDP_DSCCOLORSPACE_RGB, 10,  9.0, 0}, /*   V1_2_RGB444_10BPC_9BPP    */
   { 1, 2, HAL_MDP_DSCCHROMA_RGB444, HAL_MDP_DSCCOLORSPACE_RGB, 10, 10.0, 0}, /*   V1_2_RGB444_10BPC_10BPP   */
   { 1, 2, HAL_MDP_DSCCHROMA_RGB444, HAL_MDP_DSCCOLORSPACE_RGB, 10, 15.0, 0}, /*   V1_2_RGB444_10BPC_15BPP   */

   /* version 1.2,  YUV */
   { 1, 2, HAL_MDP_DSCCHROMA_YUV422, HAL_MDP_DSCCOLORSPACE_YUV,  8,  7.0, 0}, /*   V1_2_YUV422_8BPC_7BPP               */
   { 1, 2, HAL_MDP_DSCCHROMA_YUV422, HAL_MDP_DSCCOLORSPACE_YUV,  8,  8.0, 0}, /*   V1_2_YUV422_8BPC_8BPP               */
   { 1, 2, HAL_MDP_DSCCHROMA_YUV422, HAL_MDP_DSCCOLORSPACE_YUV, 10,  7.0, 0}, /*   V1_2_YUV422_10BPC_7BPP              */
   { 1, 2, HAL_MDP_DSCCHROMA_YUV422, HAL_MDP_DSCCOLORSPACE_YUV, 10,  8.0, 0}, /*   V1_2_YUV422_10BPC_8BPP              */
   { 1, 2, HAL_MDP_DSCCHROMA_YUV422, HAL_MDP_DSCCOLORSPACE_YUV, 10, 10.0, 0}, /*   V1_2_YUV422_10BPC_10BPP             */
   { 1, 2, HAL_MDP_DSCCHROMA_YUV420, HAL_MDP_DSCCOLORSPACE_YUV,  8,  6.0, 0}, /*   V1_2_YUV420_8BPC_6BPP               */
   { 1, 2, HAL_MDP_DSCCHROMA_YUV420, HAL_MDP_DSCCOLORSPACE_YUV, 10,  6.0, 0}, /*   V1_2_YUV420_10BPC_6BPP              */
   { 1, 2, HAL_MDP_DSCCHROMA_YUV420, HAL_MDP_DSCCOLORSPACE_YUV, 10,  7.5, 0}, /*   V1_2_YUV420_10BPC_7_5BPP,   7.5 bpp */

   /* version 1.1, RGB, SCR = 1 */
   { 1, 1, HAL_MDP_DSCCHROMA_RGB444, HAL_MDP_DSCCOLORSPACE_RGB,  8,  8.0, 1}, /*   V1_1SCR_RGB444_8BPC_8BPP     */
   { 1, 1, HAL_MDP_DSCCHROMA_RGB444, HAL_MDP_DSCCOLORSPACE_RGB,  8, 12.0, 1}, /*   V1_1SCR_RGB444_8BPC_12BPP    */
   { 1, 1, HAL_MDP_DSCCHROMA_RGB444, HAL_MDP_DSCCOLORSPACE_RGB, 10,  8.0, 1}, /*   V1_1SCR_RGB444_10BPC_8BPP    */
   { 1, 1, HAL_MDP_DSCCHROMA_RGB444, HAL_MDP_DSCCOLORSPACE_RGB, 10, 10.0, 1}, /*   V1_1SCR_RGB444_10BPC_10BPP   */
   { 1, 1, HAL_MDP_DSCCHROMA_RGB444, HAL_MDP_DSCCOLORSPACE_RGB, 10, 15.0, 1}, /*   V1_1SCR_RGB444_10BPC_15BPP   */

   /* version 1.1, RGB, SCR = 0 */
   { 1, 1, HAL_MDP_DSCCHROMA_RGB444, HAL_MDP_DSCCOLORSPACE_RGB,  8,  8.0, 0}, /*   V1_1_RGB444_8BPC_8BPP        */
   { 1, 1, HAL_MDP_DSCCHROMA_RGB444, HAL_MDP_DSCCOLORSPACE_RGB,  8, 12.0, 0}, /*   V1_1_RGB444_8BPC_12BPP       */
   { 1, 1, HAL_MDP_DSCCHROMA_RGB444, HAL_MDP_DSCCOLORSPACE_RGB, 10,  8.0, 0}, /*   V1_1_RGB444_10BPC_8BPP       */
   { 1, 1, HAL_MDP_DSCCHROMA_RGB444, HAL_MDP_DSCCOLORSPACE_RGB, 10, 10.0, 0}, /*   V1_1_RGB444_10BPC_10BPP      */
   { 1, 1, HAL_MDP_DSCCHROMA_RGB444, HAL_MDP_DSCCOLORSPACE_RGB, 10, 15.0, 0}, /*   V1_1_RGB444_10BPC_15BPP      */
}; 

typedef struct
{
   uint32 rtl_max_bpc;
   uint32 rtl_nb_hs_enc;
   uint32 rtl_nb_ss_enc;
   uint32 rtl_output_data_width;
   uint32 rtl_native_420_enable;
   uint32 rtl_native_422_enable;
   uint32 rtl_deraster_enable;
   uint32 pipeline_latency;
   uint32 ob_max_addr_1ss;
   uint32 ob_max_addr_2ss;
} DSCCoreConfigType;

const DSCCoreConfigType gDSCCoreConfig_table[] =
{
   {10, 2, 2, 64, 1, 1, 0, 28, 1199, 599},
   {10, 2, 2, 64, 0, 0, 0, 28, 2399, 1199},
};


/*************************************************************************
   rc buffer threshold
**************************************************************************/
#define RC_BUF_THRESH_MAX  14
const uint32 rc_buf_thresh_list[14] = { 896, 1792, 2688, 3584, 4480, 5376, 6272, 6720, 7168, 7616, 7744, 7872, 8000, 8064};


/*************************************************************************
   rc buffer parameters
**************************************************************************/
typedef struct
{
   uint32 rc_quant_incr_limit0;
   uint32 rc_quant_incr_limit1;
   uint32 initial_fullness_offset;
   uint32 initial_xmit_delay;
   uint32 second_line_bpg_offset;
   uint32 second_line_offset_adj;
   uint32 flatness_min_qp;
   uint32 flatness_max_qp;
   uint32 flatness_det_thresh;
} DSC_RC_ParameterType;

const DSC_RC_ParameterType rc_parameters_table[DSC_PROFILE_MAX_INDEX] =
{
   /* V1.2 */
   { 11, 11, 6144, 512,  0,  0,  3, 12, 2},  // V1_2_RGB444_8BPC_8BPP
   { 11, 11, 2048, 341,  0,  0,  3, 12, 2},  // V1_2_RGB444_8BPC_12BPP
   { 15, 15, 6144, 512,  0,  0,  7, 16, 8},  // V1_2_RGB444_10BPC_8BPP
   { 15, 15, 5888, 455,  0,  0,  7, 16, 8},  // V1_2_RGB444_10BPC_9BPP
   { 15, 15, 5632, 410,  0,  0,  7, 16, 8},  // V1_2_RGB444_10BPC_10BPP
   { 15, 15, 2048, 273,  0,  0,  7, 16, 8},  // V1_2_RGB444_10BPC_15BPP

   { 11, 11, 5632, 410,  0,  0,  3, 12, 2},  // V1_2_YUV422_8BPC_7BPP
   { 11, 11, 2048, 341,  0,  0,  3, 12, 2},  // V1_2_YUV422_8BPC_8BPP
   { 15, 15, 5632, 410,  0,  0,  7, 16, 8},  // V1_2_YUV422_10BPC_7BPP
   { 15, 15, 2048, 341,  0,  0,  7, 16, 8},  // V1_2_YUV422_10BPC_8BPP
   { 15, 15, 2048, 273,  0,  0,  7, 16, 8},  // V1_2_YUV422_10BPC_10BPP
   { 11, 11, 2048, 341, 12, 512, 3, 12, 2},  // V1_2_YUV420_8BPC_6BPP
   { 15, 15, 2048, 341, 12, 512, 7, 16, 8},  // V1_2_YUV420_10BPC_6BPP
   { 15, 15, 2048, 256, 12, 512, 7, 16, 8},  // V1_2_YUV420_10BPC_7_5BPP

   /* V1.1  + SCR*/
   { 11, 11, 6144, 512,  0,   0, 3, 12, 2},  // V1_1SCR_RGB444_8BPC_8BPP
   { 11, 11, 2048, 341,  0,   0, 3, 12, 2},  // V1_1SCR_RGB444_8BPC_12BPP
   { 15, 15, 6144, 512,  0,   0, 7, 16, 8},  // V1_1SCR_RGB444_10BPC_8BPP
   { 15, 15, 5632, 410,  0,   0, 7, 16, 8},  // V1_1SCR_RGB444_10BPC_10BPP
   { 15, 15, 2048, 273,  0,   0, 7, 16, 8},  // V1_1SCR_RGB444_10BPC_15BPP

   /* V1.1 */
   { 11, 11, 6144, 512,  0,   0, 3, 12, 2},  // V1_1_RGB444_8BPC_8BPP
   { 11, 11, 2048, 341,  0,   0, 3, 12, 2},  // V1_1_RGB444_8BPC_12BPP
   { 15, 15, 6144, 512,  0,   0, 7, 16, 8},  // V1_1_RGB444_10BPC_8BPP
   { 15, 15, 5632, 410,  0,   0, 7, 16, 8},  // V1_1_RGB444_10BPC_10BPP
   { 15, 15, 2048, 273,  0,   0, 7, 16, 8},  // V1_1_RGB444_10BPC_15BPP
};

/*************************************************************************
   rc range mini qp
**************************************************************************/
#define DSC_RC_RANGE_MAX   15

const uint8 rc_range_miniqp_table[DSC_PROFILE_MAX_INDEX][DSC_RC_RANGE_MAX] =
{
   /* V1.2 */
   { 0, 0, 1, 1, 3, 3, 3, 3, 3, 3, 5, 5, 5,  9, 12},  // V1_2_RGB444_8BPC_8BPP
   { 0, 0, 1, 1, 3, 3, 3, 3, 3, 3, 5, 5, 5,  7, 10},  // V1_2_RGB444_8BPC_12BPP
   { 0, 4, 5, 5, 7, 7, 7, 7, 7, 7, 9, 9, 9, 13, 16},  // V1_2_RGB444_10BPC_8BPP
   { 0, 4, 5, 5, 7, 7, 7, 7, 7, 7, 9, 9, 9, 12, 15},  // V1_2_RGB444_10BPC_9BPP
   { 0, 4, 5, 6, 7, 7, 7, 7, 7, 7, 9, 9, 9, 11, 15},  // V1_2_RGB444_10BPC_10BPP
   { 0, 2, 3, 4, 5, 5, 5, 6, 6, 7, 8, 8, 9, 11, 12},  // V1_2_RGB444_10BPC_15BPP

   { 0, 0, 1, 2, 3, 3, 3, 3, 3, 3, 5, 5, 5,  7, 11},  // V1_2_YUV422_8BPC_7BPP
   { 0, 0, 1, 1, 3, 3, 3, 3, 3, 3, 5, 5, 5,  7, 10},  // V1_2_YUV422_8BPC_8BPP
   { 0, 4, 5, 6, 7, 7, 7, 7, 7, 7, 9, 9, 9, 11, 15},  // V1_2_YUV422_10BPC_7BPP
   { 0, 2, 3, 4, 6, 7, 7, 7, 7, 7, 9, 9, 9, 11, 14},  // V1_2_YUV422_10BPC_8BPP
   { 0, 2, 3, 4, 5, 5, 5, 6, 6, 7, 8, 8, 9, 11, 12},  // V1_2_YUV422_10BPC_10BPP
   { 0, 0, 1, 1, 3, 3, 3, 3, 3, 3, 5, 5, 5,  7, 10},  // V1_2_YUV420_8BPC_6BPP
   { 0, 2, 3, 4, 6, 7, 7, 7, 7, 7, 9, 9, 9, 11, 14},  // V1_2_YUV420_10BPC_6BPP
   { 0, 2, 3, 4, 5, 5, 5, 6, 6, 7, 8, 8, 9, 11, 12},  // V1_2_YUV420_10BPC_7_5BPP

   /* V1.1 + SCR */
   { 0, 0, 1, 1, 3, 3, 3, 3, 3, 3, 5, 5, 5,  9, 12},  // V1_1SCR_RGB444_8BPC_8BPP
   { 0, 0, 1, 1, 3, 3, 3, 3, 3, 3, 5, 5, 5,  7, 10},  // V1_1SCR_RGB444_8BPC_12BPP
   { 0, 4, 5, 5, 7, 7, 7, 7, 7, 7, 9, 9, 9, 13, 16},  // V1_1SCR_RGB444_10BPC_8BPP
   { 0, 4, 5, 6, 7, 7, 7, 7, 7, 7, 9, 9, 9, 11, 15},  // V1_1SCR_RGB444_10BPC_10BPP
   { 0, 2, 3, 4, 5, 5, 5, 6, 6, 7, 8, 8, 9, 11, 12},  // V1_1SCR_RGB444_10BPC_15BPP

   /* V1.1 */
   { 0, 0, 1, 1, 3, 3, 3, 3, 3, 3, 5, 5, 5,  7, 13},  // V1_1_RGB444_8BPC_8BPP
   { 0, 0, 1, 1, 3, 3, 3, 3, 3, 3, 5, 5, 5,  7, 13},  // V1_1_RGB444_8BPC_12BPP
   { 0, 4, 5, 5, 7, 7, 7, 7, 7, 7, 9, 9, 9, 11, 17},  // V1_1_RGB444_10BPC_8BPP
   { 0, 4, 5, 6, 7, 7, 7, 7, 7, 7, 9, 9, 9, 11, 15},  // V1_1_RGB444_10BPC_10BPP
   { 0, 2, 3, 4, 5, 5, 5, 6, 6, 7, 8, 8, 9, 11, 12},  // V1_1_RGB444_10BPC_15BPP
};


/*************************************************************************
   rc range max qp
**************************************************************************/
const uint8 rc_range_maxqp_table[DSC_PROFILE_MAX_INDEX][DSC_RC_RANGE_MAX] =
{
   /* V1.2 */
   { 4, 4, 5,  6,  7,  7,  7,  8,  9, 10, 10, 11, 11, 12, 13},  // V1_2_RGB444_8BPC_8BPP
   { 2, 4, 5,  6,  7,  7,  7,  8,  8,  9,  9,  9,  9, 10, 11},  // V1_2_RGB444_8BPC_12BPP
   { 8, 8, 9, 10, 11, 11, 11, 12, 13, 14, 14, 15, 15, 16, 17},  // V1_2_RGB444_10BPC_8BPP
   { 7, 8, 9, 10, 11, 11, 11, 12, 13, 13, 14, 14, 15, 15, 16},  // V1_2_RGB444_10BPC_9BPP
   { 7, 8, 9, 10, 11, 11, 11, 12, 13, 13, 14, 14, 15, 15, 16},  // V1_2_RGB444_10BPC_10BPP
   { 2, 5, 5,  6,  6,  7,  7,  8,  9,  9, 10, 11, 11, 12, 13},  // V1_2_RGB444_10BPC_15BPP

   { 3, 4, 5,  6,  7,  7,  7,  8,  9,  9, 10, 10, 11, 11, 12},  // V1_2_YUV422_8BPC_7BPP
   { 2, 4, 5,  6,  7,  7,  7,  8,  8,  9,  9,  9,  9, 10, 11},  // V1_2_YUV422_8BPC_8BPP
   { 7, 8, 9, 10, 11, 11, 11, 12, 13, 13, 14, 14, 15, 15, 16},  // V1_2_YUV422_10BPC_7BPP
   { 2, 5, 7,  8,  9, 10, 11, 12, 12, 13, 13, 13, 13, 14, 15},  // V1_2_YUV422_10BPC_8BPP
   { 2, 5, 5,  6,  6,  7,  7,  8,  9,  9, 10, 11, 11, 12, 13},  // V1_2_YUV422_10BPC_10BPP
   { 2, 4, 5,  6,  7,  7,  7,  8,  8,  9,  9,  9,  9, 10, 12},  // V1_2_YUV420_8BPC_6BPP
   { 2, 5, 7,  8,  9, 10, 11, 12, 12, 13, 13, 13, 13, 14, 15},  // V1_2_YUV420_10BPC_6BPP
   { 2, 5, 5,  6,  6,  7,  7,  8,  9,  9, 10, 11, 11, 12, 13},  // V1_2_YUV420_10BPC_7_5BPP

   /* V1.1 + SCR */
   { 4, 4, 5,  6,  7,  7,  7,  8,  9, 10, 10, 11, 11, 12, 13},  // V1_1SCR_RGB444_8BPC_8BPP
   { 2, 4, 5,  6,  7,  7,  7,  8,  8,  9,  9,  9,  9, 10, 11},  // V1_1SCR_RGB444_8BPC_12BPP
   { 8, 8, 9, 10, 11, 11, 11, 12, 13, 14, 14, 15, 15, 16, 17},  // V1_1SCR_RGB444_10BPC_8BPP
   { 7, 8, 9, 10, 11, 11, 11, 12, 13, 13, 14, 14, 15, 15, 16},  // V1_1SCR_RGB444_10BPC_10BPP
   { 2, 5, 5,  6,  6,  7,  7,  8,  9,  9, 10, 11, 11, 12, 13},  // V1_1SCR_RGB444_10BPC_15BPP

   /* V1.1 */
   { 4, 4, 5,  6,  7,  7,  7,  8,  9, 10, 11, 12, 13, 13, 15},  // V1_1_RGB444_8BPC_8BPP
   { 2, 4, 5,  6,  7,  7,  7,  8,  9, 10, 11, 12, 13, 13, 15},  // V1_1_RGB444_8BPC_12BPP
   { 4, 8, 9, 10, 11, 11, 11, 12, 13, 14, 15, 16, 17, 17, 19},  // V1_1_RGB444_10BPC_8BPP
   { 7, 8, 9, 10, 11, 11, 11, 12, 13, 13, 14, 14, 15, 15, 16},  // V1_1_RGB444_10BPC_10BPP
   { 2, 5, 5,  6,  6,  7,  7,  8,  9,  9, 10, 11, 11, 12, 13},  // V1_1_RGB444_10BPC_15BPP
};

/*************************************************************************
   rc range offset
**************************************************************************/
const int8 rc_range_offset_table[DSC_PROFILE_MAX_INDEX][DSC_RC_RANGE_MAX] =
{
   /* V1.2 */
   {  2, 0, 0, -2, -4, -6, -8, -8, -8, -10, -10, -12, -12, -12, -12},  // V1_2_RGB444_8BPC_8BPP
   {  2, 0, 0, -2, -4, -6, -8, -8, -8, -10, -10, -12, -12, -12, -12},  // V1_2_RGB444_8BPC_12BPP
   {  2, 0, 0, -2, -4, -6, -8, -8, -8, -10, -10, -12, -12, -12, -12},  // V1_2_RGB444_10BPC_8BPP
   {  2, 0, 0, -2, -4, -6, -8, -8, -8, -10, -10, -11, -12, -12, -12},  // V1_2_RGB444_10BPC_9BPP
   {  2, 0, 0, -2, -4, -6, -8, -8, -8, -10, -10, -10, -12, -12, -12},  // V1_2_RGB444_10BPC_10BPP
   { 10, 8, 6,  4,  2,  0, -2, -4, -6,  -8, -10, -10, -12, -12, -12},  // V1_2_RGB444_10BPC_15BPP

   {  2, 0, 0, -2, -4, -6, -8, -8, -8, -10, -10, -10, -12, -12, -12},  // V1_2_YUV422_8BPC_7BPP
   {  2, 0, 0, -2, -4, -6, -8, -8, -8, -10, -10, -12, -12, -12, -12},  // V1_2_YUV422_8BPC_8BPP
   {  2, 0, 0, -2, -4, -6, -8, -8, -8, -10, -10, -10, -12, -12, -12},  // V1_2_YUV422_10BPC_7BPP
   {  2, 0, 0, -2, -4, -6, -8, -8, -8, -10, -10, -12, -12, -12, -12},  // V1_2_YUV422_10BPC_8BPP
   { 10, 8, 6,  4,  2,  0, -2, -4, -6,  -8, -10, -10, -12, -12, -12},  // V1_2_YUV422_10BPC_10BPP
   {  2, 0, 0, -2, -4, -6, -8, -8, -8, -10, -10, -12, -12, -12, -12},  // V1_2_YUV420_8BPC_6BPP
   {  2, 0, 0, -2, -4, -6, -8, -8, -8, -10, -10, -12, -12, -12, -12},  // V1_2_YUV420_10BPC_6BPP
   { 10, 8, 6,  4,  2,  0, -2, -4, -6,  -8, -10, -10, -12, -12, -12},  // V1_2_YUV420_10BPC_7_5BPP
 
   /* V1.1 + SCR */
   {  2, 0, 0, -2, -4, -6, -8, -8, -8, -10, -10, -12, -12, -12, -12},  // V1_1SCR_RGB444_8BPC_8BPP
   {  2, 0, 0, -2, -4, -6, -8, -8, -8, -10, -10, -12, -12, -12, -12},  // V1_1SCR_RGB444_8BPC_12BPP
   {  2, 0, 0, -2, -4, -6, -8, -8, -8, -10, -10, -12, -12, -12, -12},  // V1_1SCR_RGB444_10BPC_8BPP
   {  2, 0, 0, -2, -4, -6, -8, -8, -8, -10, -10, -10, -12, -12, -12},  // V1_1SCR_RGB444_10BPC_10BPP
   { 10, 8, 6,  4,  2,  0, -2, -4, -6,  -8, -10, -10, -12, -12, -12},  // V1_1SCR_RGB444_10BPC_15BPP

   /* V1.1 */
   {  2, 0, 0, -2, -4, -6, -8, -8, -8, -10, -10, -12, -12, -12, -12},  // V1_1_RGB444_8BPC_8BPP
   {  2, 0, 0, -2, -4, -6, -8, -8, -8, -10, -10, -12, -12, -12, -12},  // V1_1_RGB444_8BPC_12BPP
   {  2, 0, 0, -2, -4, -6, -8, -8, -8, -10, -10, -12, -12, -12, -12},  // V1_1_RGB444_10BPC_8BPP
   {  2, 0, 0, -2, -4, -6, -8, -8, -8, -10, -10, -10, -12, -12, -12},  // V1_1_RGB444_10BPC_10BPP
   { 10, 8, 6,  4,  2,  0, -2, -4, -6,  -8, -10, -10, -12, -12, -12},  // V1_1_RGB444_10BPC_15BPP
};

/*************************************************************************/

typedef struct
{
   uint32                dsc_config_index;
   uint32                frame_width;
   uint32                frame_height;
   uint32                slice_width;
   uint32                slice_height;
   uint32                ICH_rest_manual_value;
   uint32                ICH_reset_manual_override;
   uint32                ICH_disable;
   uint32                full_ICH_error_precision;
   uint32                video_mode;
   uint32                block_pred_enable;
   uint32                core_config_index;
   uint32                de_raster_enable;
   uint32                multiplex_mode_enable;
   uint32                split_panel_enable;
   uint32                output_profile;
   uint32                num_of_active_ss;
   uint32                num_of_active_hs;

   /* automatic */
   uint32                dsc_version_major;
   uint32                dsc_version_minor;
   uint32                bits_per_component;
   uint32                convert_rgb;
   uint32                simple_422;
   uint32                native_420;
   uint32                native_422;
   float                 bits_per_pixel;
   uint32                picture_width;
   uint32                picture_height;

   const DSCConfigType          *pConfig;        /* base on dsc_config_index */
   const DSCCoreConfigType      *pCoreConfig;    /* base on core_config_index */

   /* always fixed */
   uint32                        vbr_enable;
   uint32                        pps_identifier;
   uint32                        rc_model_size;                 /* 32 */
   uint32                        rc_edge_factor;                /* 6 */
   uint32                        rc_tgt_offset_hi;              /* 3 */
   uint32                        rc_tgt_offset_low;             /* 3 */
   const uint32                 *rc_buf_thresh;

   /* looked up */
   const DSC_RC_ParameterType   *rc_parameter;  /* base on dsc_config_index */
   const uint8                  *rc_mini_qp;    /* base on dsc_config_index */
   const uint8                  *rc_max_qp;     /* base on dsc_config_index */
   const int8                   *rc_offset;     /* base on dsc_config_index */

   /* calculated */
   uint32                  first_line_bpg_offset;
   uint32                  chunk_size;
   uint32                  initial_dec_delay;
   uint32                  initial_scale_value;
   uint32                  scale_increment_interval;
   uint32                  scale_decrement_interval;
   uint32                  nfl_bpg_offset;
   uint32                  slice_bpg_offset;
   uint32                  final_offset;
   uint32                  nsl_bpg_offset;

   /* temp */
   uint32                  slice_width_mod;
   uint32                  uncompressed_bpg_rate;
   uint32                  first_line_bpg_offset_a;
   uint32                  first_line_bpg_offset_b;
   uint32                  pixels_per_group;
   uint32                  groups_per_line;
   uint32                  hrd_delay;
   uint32                  min_rate_buffer_size;
   uint32                  max_se_size_y;
   uint32                  max_se_size_c;
   uint32                  mux_word_size;
   uint32                  num_extra_mux_bits_temp_420;
   uint32                  num_extra_mux_bits_temp_422;
   uint32                  num_extra_mux_bits_temp_444;
   uint32                  num_extra_mux_bits_temp;
   uint32                  num_extra_mux_bits;
   uint32                  final_scale_value;
   uint32                  scale_increment_interval_temp;
   uint32                  groups_total;
   uint32                  slice_bits;

   /* Mdp */
   uint32                  slice_width_mod_3;
   uint32                  slice_last_group_size;
   uint32                  linebuffer_depth;
   uint32                  enable_422;
   uint32                  enable_10bits_input;

   /* initial lines */
   uint32                  CompressBppGroup;
   uint32                  muxWordSize;
   uint32                  ChunkBits;
   uint32                  rtl_num_components;
   uint32                  ob_data_width_4comps;
   uint32                  ob_data_width_3comps;
   uint32                  ob_data_width;
   uint32                  ContainerSliceWidth;
   uint32                  output_rate;
   float                   output_rate_ratio;
   float                   output_ratio_offset;
   float                   output_rate_ratio_complement;
   uint32                  output_rate_extra_budget_bits;
   uint32                  multi_hs_extra_budget_bits_a;
   uint32                  multi_hs_extra_budget_bits_b;
   uint32                  multi_hs_extra_budget_bits_c;
   uint32                  multi_hs_extra_budget_bits_d;
   uint32                  multi_hs_extra_budget_bits;
   uint32                  max_muxword_size;
   uint32                  max_se_size;
   uint32                  max_ssm_delay;
   uint32                  obuf_latency;
   uint32                  input_ssm_out_latency;
   uint32                  base_hs_latency;
   uint32                  multi_hs_extra_latency;
   uint32                  initial_lines;
} DSC_DesciptorType;

#endif /* HAL_MDP_DSC2_H */
