/*
 Copyright (c) 2021-2022 Qualcomm Technologies, Inc.
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


/*------------------------------------------------------------------------------
 * Defines
 *----------------------------------------------------------------------------*/
/** Format: HAL_MDP_<MAJOR>_<MINOR>_<STEP>_XXX */
#define  HAL_MDP_9_0_0_NUM_OF_RGB_LAYERS                       0          /** RGB Source Surface Pixel Processors       */
#define  HAL_MDP_9_0_0_NUM_OF_VIG_LAYERS                       4          /** VIG Source Surface Pixel Processors       */
#define  HAL_MDP_9_0_0_NUM_OF_DMA_LAYERS                       6          /** DMA Source Surface Pixel Processors       */
#define  HAL_MDP_9_0_0_NUM_OF_CURSOR_LAYERS                    0          /** CURSOR Source Surface Pixel Processors    */
#define  HAL_MDP_9_0_0_NUM_OF_LAYER_MIXERS                     6          /** Layer Mixers                              */
#define  HAL_MDP_9_0_0_NUM_OF_DSPP                             4          /** Destination Surface Pixel Processor       */
#define  HAL_MDP_9_0_0_NUM_OF_PHYSICAL_INTERFACES              4          /** INTF_x (x = 0, 1, 2 and 3)                */
#define  HAL_MDP_9_0_0_NUM_OF_WRITEBACK_INTERFACES             2          /** WB_0, WB_1 and WB_2                       */
#define  HAL_MDP_9_0_0_NUM_OF_CONTROL_PATHS                    6          /** MDP_CTL_x (x = 0, 1, 2, 3, 4 and 5)       */
#define  HAL_MDP_9_0_0_NUM_OF_DATA_PATHS                       2          /** MDP_WB_x (x = 0, 1, 2, 3, and 4)          */
#define  HAL_MDP_9_0_0_NUM_OF_PINGPONGS                        6          /** Pingpong blocks                           */
#define  HAL_MDP_9_0_0_NUM_OF_WATCHDOGS                        0          /** Watch Dogs                                */
#define  HAL_MDP_9_0_0_NUM_OF_AXI_PORTS                        2          /** Number of AXI ports                       */
#define  HAL_MDP_9_0_0_NUM_OF_VBIF_CLIENTS                     16         /** Number of VBIF clients                    */

#define  HAL_MDP_9_0_0_NUM_OF_CHROMA_BLOCKS                    1          /** Number of Chroma blocks                   */

/** RGB and VG and DMA IGC LUT Size */
#define  HAL_MDP_9_0_0_SSPP_IGC_LUT_SIZE                       256
#define  HAL_MDP_9_0_0_SSPP_IGC_NUM_OF_COLOR_COMPONENTS        3          /** Color 0, 1 and 2                          */

/** DSPP IGC LUT Size */
#define  HAL_MDP_9_0_0_DSPP_IGC_LUT_SIZE                       256
#define  HAL_MDP_9_0_0_DSPP_IGC_NUM_OF_COLOR_COMPONENTS        3          /** Color 0, 1 and 2                          */

/** QSEED */

/** LAYER MIXER */
#define  HAL_MDP_9_0_0_LAYER_MIXER_MAX_BLEND_STAGES            11         /** Blend Stage                               */

/** QOS */
#define HAL_MDP_9_0_0_MAX_MDPCORE_CLK_FREQ                     514000000  /** MDP core maximum working clock frequency in Hz */

#define HAL_MDP_9_0_0_QOS_REQPRI_WATERMARK_REGS_COUNT          3


/* QoS priority re-mapping for real time read clients; real time clients are ViG, RGB, and DMA in line mode;*/
#define HAL_MDP_9_0_0_QOS_REMAPPER_REALTIME_CLIENTS            HAL_MDP_QOS_REMAPPER_INFO(                \
                                                               HAL_MDP_TRFCTRL_LATENCY_REALTIME,         \
                                                               HAL_MDP_TRFCTRL_LATENCY_REALTIME,         \
                                                               HAL_MDP_TRFCTRL_LATENCY_REALTIME,         \
                                                               HAL_MDP_TRFCTRL_LATENCY_REALTIME )
/* QoS priority re-mapping for non-real time read clients; non-real time clients are DMA in block mode;*/
#define HAL_MDP_9_0_0_QOS_REMAPPER_NONREALTIME_CLIENTS         HAL_MDP_QOS_REMAPPER_INFO(                \
                                                               HAL_MDP_TRFCTRL_LATENCY_NON_REALTIME,     \
                                                               HAL_MDP_TRFCTRL_LATENCY_NON_REALTIME,     \
                                                               HAL_MDP_TRFCTRL_LATENCY_NON_REALTIME,     \
                                                               HAL_MDP_TRFCTRL_LATENCY_NON_REALTIME )

/** VBIF max burst length */
#define HAL_MDP_9_0_0_VBIF_MAX_DDR_RD_BURST_SIZE               7
#define HAL_MDP_9_0_0_VBIF_MAX_DDR_WR_BURST_SIZE               7
#define HAL_MDP_9_0_0_VBIF_MAX_RD_OT_SIZE                      0    /* 0 to use default value */
#define HAL_MDP_9_0_0_VBIF_MAX_WR_OT_SIZE                      0    /* 0 to use default value */

#define HAL_MDP_9_0_0_VBIF_ROUND_ROBIN_QOS_ARB                 HWIO_VBIF_VBIF_ROUND_ROBIN_QOS_ARB_RR_QOS_EN_BMSK

/** Clock control */
#define HAL_MDP_9_0_0_HYSTERISIS_DEFAULT                       1

/** HSIC register range */
#define HAL_MDP_9_0_0_PICTURE_ADJUST_MIN_HUE                  (-768)   // -180 degree
#define HAL_MDP_9_0_0_PICTURE_ADJUST_MAX_HUE                  (-768)   // 180 degree
#define HAL_MDP_9_0_0_PICTURE_ADJUST_MIN_UNCHANGE_HUE          0       // value for unchange hue going to the min hue direction
#define HAL_MDP_9_0_0_PICTURE_ADJUST_MAX_UNCHANGE_HUE         (-1536)  // value for unchange hue going to the max hue direction
#define HAL_MDP_9_0_0_PICTURE_ADJUST_MIN_SATURATION           (-128)   
#define HAL_MDP_9_0_0_PICTURE_ADJUST_MAX_SATURATION            127
#define HAL_MDP_9_0_0_PICTURE_ADJUST_UNCHANGE_SATURATION       0
#define HAL_MDP_9_0_0_PICTURE_ADJUST_MIN_INTENSITY            (-128) 
#define HAL_MDP_9_0_0_PICTURE_ADJUST_MAX_INTENSITY             127 
#define HAL_MDP_9_0_0_PICTURE_ADJUST_UNCHANGE_INTENSITY        0
#define HAL_MDP_9_0_0_PICTURE_ADJUST_MIN_CONTRAST             (-128)
#define HAL_MDP_9_0_0_PICTURE_ADJUST_MAX_CONTRAST              127
#define HAL_MDP_9_0_0_PICTURE_ADJUST_UNCHANGE_CONTRAST         0

/** Highest bank bit configuration */
#define  HAL_MDP_9_0_0_UBWC_DEFAULT_HIGHEST_BANK_BIT          (HAL_MDP_UBWC_HIGHEST_BANK_BIT_15)
#define  HAL_MDP_9_0_0_UBWC_DEFAULT_MAL_SIZE                  (HAL_MDP_UBWC_MAL_32_BYTES)
#define  HAL_MDP_9_0_0_UBWC_DEFAULT_LVL1_SWIZZLING_MODE       (HAL_MDP_UBWC_SWIZZLING_MODE_DISABLE)
#define  HAL_MDP_9_0_0_UBWC_DEFAULT_LVL2_SWIZZLING_MODE       (HAL_MDP_UBWC_SWIZZLING_MODE_ENABLE)
#define  HAL_MDP_9_0_0_UBWC_DEFAULT_LVL3_SWIZZLING_MODE       (HAL_MDP_UBWC_SWIZZLING_MODE_ENABLE)
#define  HAL_MDP_9_0_0_UBWC_DEFAULT_BANK_SPREAD_MODE          (HAL_MDP_UBWC_BANK_SPREAD_MODE_ENABLE)
#define  HAL_MDP_9_0_0_UBWC_DEFAULT_MAJOR_REVISION            4
#define  HAL_MDP_9_0_0_UBWC_DEFAULT_MINOR_REVISION            3
#define  HAL_MDP_9_0_0_UBWC_DEFAULT_MAX_DDR_CHANNELS          8

/* Display flag to enable PFS feature */
#define  HAL_MDP_DISPLAY_FLAG_ENABLE_PFS                      0x10000000

/** Multirect parameters */
#define HAL_MDP_9_0_0_MULTIRECT_PARALLEL_MAX_WIDTH           (2560)
#define HAL_MDP_9_0_0_MULTIRECT_TIMEMULTIPLEX_MIN_LINES      (8)


/*------------------------------------------------------------------------
 * Global Data Definitions
 *------------------------------------------------------------------------ */

/* 
 * MDP has a set of MDP_CLK_STATUSx registers to read the active/idle state of the MDP modules (SSPP, DSPP etc).
 * The following tables provide a mapping information of MDP_CLK_STATUSx register and BitFieldMask for each MDP module
 *
 *    (a)   gsSSPPModuleStatusRegInfo        --> Mapping table for SSPPx (VIGx, RGBx, CURSORx and DMAx) modules
 *    (b)   gsDSPPStatusRegInfo              --> Mapping table for DSPPx modules
 *    (c)   gsPingPongStatusRegInfo          --> Mapping table for PING-PONGx modules
 *    (c)   gsWBStatusRegInfo                --> Mapping table for WBx modules
 */
static HAL_MDP_ModuleStatusRegInfo     gsSSPPModuleStatusRegInfo[HAL_MDP_SOURCE_PIPE_MAX] =
{
 //{ uRegAddrOffset  uBitFieldMask                                              }
   { 0x00000000,     0x00000000                                                 },    // HAL_MDP_SOURCE_PIPE_NONE
   { 0x00000000,     HWIO_MDP_VP_0_VIG_0_SSPP_CLK_STATUS_CLK_ACTIVE_BMSK        },    // HAL_MDP_SOURCE_PIPE_VIG_0
   { 0x00000000,     HWIO_MDP_VP_0_VIG_1_SSPP_CLK_STATUS_CLK_ACTIVE_BMSK        },    // HAL_MDP_SOURCE_PIPE_VIG_1
   { 0x00000000,     HWIO_MDP_VP_0_VIG_2_SSPP_CLK_STATUS_CLK_ACTIVE_BMSK        },    // HAL_MDP_SOURCE_PIPE_VIG_2
   { 0x00000000,     HWIO_MDP_VP_0_VIG_3_SSPP_CLK_STATUS_CLK_ACTIVE_BMSK        },    // HAL_MDP_SOURCE_PIPE_VIG_3
   { 0x00000000,     HWIO_MDP_VP_0_DMA_0_SSPP_CLK_STATUS_CLK_ACTIVE_BMSK        },    // HAL_MDP_SOURCE_PIPE_DMA_0 
   { 0x00000000,     HWIO_MDP_VP_0_DMA_1_SSPP_CLK_STATUS_CLK_ACTIVE_BMSK        },    // HAL_MDP_SOURCE_PIPE_DMA_1
   { 0x00000000,     HWIO_MDP_VP_0_DMA_2_SSPP_CLK_STATUS_CLK_ACTIVE_BMSK        },    // HAL_MDP_SOURCE_PIPE_DMA_2
   { 0x00000000,     HWIO_MDP_VP_0_DMA_3_SSPP_CLK_STATUS_CLK_ACTIVE_BMSK        },    // HAL_MDP_SOURCE_PIPE_DMA_3
   { 0x00000000,     HWIO_MDP_VP_0_DMA_4_SSPP_CLK_STATUS_CLK_ACTIVE_BMSK        },    // HAL_MDP_SOURCE_PIPE_DMA_4
   { 0x00000000,     HWIO_MDP_VP_0_DMA_5_SSPP_CLK_STATUS_CLK_ACTIVE_BMSK        },    // HAL_MDP_SOURCE_PIPE_DMA_5 
};

static HAL_MDP_ModuleStatusRegInfo    gsDSPPStatusRegInfo[HAL_MDP_DESTINATION_PIPE_MAX] = 
{
 //{ uRegAddrOffset  uBitFieldMask                                    }
   { 0x00000000,     0x00000000                                       },    // HAL_MDP_DESTINATION_PIPE_NONE
   { 0x00000000,     HWIO_MDP_CLK_STATUS3_LM_DSPP0_CLK_ACTIVE_BMSK    },    // HAL_MDP_DESTINATION_PIPE_0
   { 0x00000000,     HWIO_MDP_CLK_STATUS4_LM_DSPP1_CLK_ACTIVE_BMSK    },    // HAL_MDP_DESTINATION_PIPE_1
   { 0x00000000,     HWIO_MDP_CLK_STATUS5_LM_DSPP2_CLK_ACTIVE_BMSK    },    // HAL_MDP_DESTINATION_PIPE_2
   { 0x00000000,     HWIO_MDP_CLK_STATUS7_LM_DSPP3_CLK_ACTIVE_BMSK    },    // HAL_MDP_DESTINATION_PIPE_3
};

static HAL_MDP_ModuleStatusRegInfo    gsPingPongStatusRegInfo[HAL_MDP_PINGPONG_MAX] = 
{
 //{ uRegAddrOffset  uBitFieldMask                                    }
   { 0x00000000,     0x00000000                                       },    // HAL_MDP_PINGPONG_NONE
   { 0x00000000,     HWIO_MDP_CLK_STATUS3_PP0_CLK_ACTIVE_BMSK         },    // HAL_MDP_PINGPONG_0
   { 0x00000000,     HWIO_MDP_CLK_STATUS4_PP1_CLK_ACTIVE_BMSK         },    // HAL_MDP_PINGPONG_1
   { 0x00000000,     HWIO_MDP_CLK_STATUS5_PP2_CLK_ACTIVE_BMSK         },    // HAL_MDP_PINGPONG_2
   { 0x00000000,     HWIO_MDP_CLK_STATUS7_PP3_CLK_ACTIVE_BMSK         },    // HAL_MDP_PINGPONG_3
   { 0x00000000,     HWIO_MDP_CLK_STATUS8_PP4_CLK_ACTIVE_BMSK         },    // HAL_MDP_PINGPONG_4
   { 0x00000000,     HWIO_MDP_CLK_STATUS9_PP5_CLK_ACTIVE_BMSK         },    // HAL_MDP_PINGPONG_5
   { 0x00000000,     0x00000000                                       },    // HAL_MDP_PINGPONG_6
};

static HAL_MDP_ModuleStatusRegInfo    gsWBStatusRegInfo[HAL_MDP_INTERFACE_MAX - HAL_MDP_INTERFACE_WRITEBACK_TYPE_BASE] = 
{
 //{ uRegAddrOffset     uBitFieldMask                                    }
   { 0x00000000,        0x00000000                                       },    // HAL_MDP_INTERFACE_WRITEBACK_TYPE_BASE
   { 0x00000000,        0x00000000                                       },    // HAL_MDP_INTERFACE_MEMORY_WB_BLK_MODE_0
   { 0x00000000,        0x00000000                                       },    // HAL_MDP_INTERFACE_MEMORY_WB_BLK_MODE_1
   { 0x00000000,        0x00000000                                       },    // HAL_MDP_INTERFACE_MEMORY_WB_LINE_MODE_0
   { 0x00000000,        0x00000000                                       },    // HAL_MDP_INTERFACE_MEMORY_WB_LINE_MODE_1
 //  { 0x00000000,        HWIO_MDP_CLK_STATUS5_WB2_CLK_ACTIVE_BMSK         },    // HAL_MDP_INTERFACE_MEMORY_WB_LINEAR_MODE
};

uint32 gTwoDFilterA_LUT[HAL_MDP_QSEED_ENTRIE_SIZE_IN_REGISTERS*HAL_MDP_QSEED_COEFF_LUT_A_ENTRIES] =
{
  0x3bf93b36, 0xf4396d80, 0xf2341cfb, 0x1f3e7d00,
  0x15ff4e1e, 0xf26e66ff, 0xfa481179, 0x1f3e3e00,
  0x000e5309, 0x00a551fc, 0x125206f8, 0x1f9e3f00,
  0x4ef9151e, 0xf8226680, 0xf0483779, 0x1fff7cff,
  0x21f82110, 0xf052677f, 0xfa6d2977, 0x1f1f7c7f,
  0x06fd2a03, 0xf485587f, 0x1a8016f9, 0x1f3f3d00,
  0x53fc0009, 0xfc0d5180, 0xf05252f8, 0x01c2407c,
  0x2af90603, 0xf42d5800, 0xf88042f9, 0x1fa37d7f,
  0x0bf80bfe, 0xf0595100, 0x16a42cfe, 0x1f02fc00,
  0x3b353bf9, 0xf4396c79, 0x01f71c80, 0x06a03d79,
  0x144a24f9, 0xf26d667d, 0xfffd2580, 0x03c03cf8,
  0x00530efc, 0x00a55189, 0xf80d2900, 0x013fbc78,
  0x241e14f9, 0xf24b6678, 0x01fd3680, 0x095ffcfd,
  0x072807fc, 0xf48059fb, 0xfa0f4000, 0x051f7d7b,
  0xfa2afdff, 0x0cb24183, 0xf22d4000, 0x01bebe79,
  0x0e0900fc, 0xf05251f8, 0xfc0d5280, 0x0a7f0009,
  0xfd0dfaff, 0xf88041f9, 0xf42d5900, 0x055e4303,
  0xf80bf800, 0x16a42bfe, 0xf0595200, 0x017e05fe,
  0x2df32df3, 0x002cc180, 0x01f21600, 0x1e600000,
  0xfdfd24f3, 0xf087af00, 0x01fc1180, 0x1e600000,
  0xf21111f9, 0xe4fc7e79, 0xf20f0780, 0x1f200000,
  0xfaf1faf7, 0xee7aa07f, 0xf61e3d7f, 0x1e3efbff,
  0xf1f4f4fd, 0xe2e571fd, 0xe84e277f, 0x1e9e7cff,
  0xf2f2f2ff, 0xe49d4eff, 0xe49d4eff, 0x1e5cb97f,
  0x00000000, 0x00008000, 0x00000000, 0x80000000,
  0xdf000000, 0xf06edd80, 0x00000000, 0x40000000,
  0xe9000000, 0xd3178b80, 0x00000000, 0x20000000,
  0xe3f9e302, 0xf25fc001, 0xfc182f80, 0x3f3fbc81,
  0xeceeee01, 0xd8f27801, 0xf63d1e80, 0x3f7f3e00,
  0xf3f3f301, 0xe6994c81, 0xe6994c81, 0x1e7cf981,
  0x2df32df3, 0x002cc180, 0x01f21600, 0x1e600000,
  0xfdfd24f3, 0xf087af00, 0x01fc1180, 0x1e600000,
  0xf21111f9, 0xe4fc7e79, 0xf20f0780, 0x1f200000,
  0xfaf1faf7, 0xee7aa07f, 0xf61e3d7f, 0x1e3efbff,
  0xf1f4f4fd, 0xe2e571fd, 0xe84e277f, 0x1e9e7cff,
  0xf2f2f2ff, 0xe49d4eff, 0xe49d4eff, 0x1e5cb97f,
  0x00000000, 0x00008000, 0x00000000, 0x80000000,
  0xdf000000, 0xf06edd80, 0x00000000, 0x40000000,
  0xe9000000, 0xd3178b80, 0x00000000, 0x20000000,
  0xe3f9e302, 0xf25fc001, 0xfc182f80, 0x3f3fbc81,
  0xeceeee01, 0xd8f27801, 0xf63d1e80, 0x3f7f3e00,
  0xf3f3f301, 0xe6994c81, 0xe6994c81, 0x1e7cf981

};
uint32 gTwoDFilterB_LUT[HAL_MDP_QSEED_ENTRIE_SIZE_IN_REGISTERS*HAL_MDP_QSEED_COEFF_LUT_B_ENTRIES] =
{
  0x26fb462a, 0xf2526b80, 0xf43f177a, 0x1f1e7d80,
  0x08055213, 0xf68a5e7e, 0x044f0b79, 0x1f5e3e80,
  0x36f81c18, 0xf4376800, 0xf45a2ff9, 0x1f7fbc00,
  0x12fa270a, 0xf06a6100, 0x06771f79, 0x1f1f7c80,
  0x3dfb0207, 0xf81b5700, 0xf2694bf8, 0x0062fefe,
  0x19f80900, 0xf2425600, 0x0294387b, 0x1f433c80,
  0x26402ff9, 0xf25269fa, 0x01fa2200, 0x05403cf9,
  0x085018fb, 0xf68a5c82, 0xfc042880, 0x027ffc78,
  0x13240dfa, 0xf06660f9, 0xfe053d00, 0x073fbcfc,
  0xff2a01fe, 0xfe9a4eff, 0xf61c4100, 0x033f3dfa,
  0x030bfdfe, 0xf2694bf8, 0xf81b5700, 0x07bec107,
  0xfa0cf900, 0x0294377b, 0xf2425700, 0x033e0480,
  0x0ff72bf2, 0xf854be80, 0x01f51480, 0x1e400000,
  0xf4061bf6, 0xe8c199fd, 0xfa040c80, 0x1ec00000,
  0xf3f3f8fb, 0xe8ab8a00, 0xf2323180, 0x1e5efc80,
  0xf3000000, 0xfc177b00, 0x00010080, 0x80000000,
  0xe1000000, 0xe4beb780, 0x00000000, 0x20000000,
  0xe5f4e802, 0xe8a49f81, 0xfa292780, 0x3f3f7d00,
  0x0ff72bf2, 0xf854be80, 0x01f51480, 0x1e400000,
  0xf4061bf6, 0xe8c199fd, 0xfa040c80, 0x1ec00000,
  0xf3f3f8fb, 0xe8ab8a00, 0xf2323180, 0x1e5efc80,
  0xf3000000, 0xfc177b00, 0x00010080, 0x80000000,
  0xe1000000, 0xe4beb780, 0x00000000, 0x20000000,
  0xe5f4e802, 0xe8a49f81, 0xfa292780, 0x3f3f7d00

};
uint32 gTwoDFilterC_LUT[HAL_MDP_QSEED_ENTRIE_SIZE_IN_REGISTERS*HAL_MDP_QSEED_COEFF_LUT_C_ENTRIES] =
{
  0x46f8262a, 0xf62e6b80, 0xf23f297a, 0x1f7ebc80,
  0x1cfb3618, 0xf05f6800, 0xfc5a1bf9, 0x1f1ebd00,
  0x02033d07, 0xfa97577e, 0x16690df8, 0x1f7e7e00,
  0x52fa0813, 0xfa165e00, 0xf04f4579, 0x00a0bdfe,
  0x27f8120a, 0xf23e6100, 0xfa773579, 0x1f40fc00,
  0x09fa1900, 0xf2705600, 0x1894217b, 0x1f007c80,
  0x2f2a26f9, 0xf24469f9, 0x01fa2900, 0x08003cfa,
  0x0d3913fa, 0xf27a60fc, 0xfc053300, 0x049ffc79,
  0xfd3d03fe, 0x04ae4b87, 0xf61b3480, 0x017f3cf8,
  0x181308fb, 0xf0515cf8, 0xfe044500, 0x0a1fbd82,
  0x0119fffe, 0xf6824efa, 0xf81c4d00, 0x055effff,
  0xf919fa00, 0x12ae3700, 0xf0424a00, 0x019e40fb,
  0xfdf50af5, 0xf083ac00, 0xfc082400, 0x1e403e00,
  0xf1fffffb, 0xe2f97cfb, 0xec2b15ff, 0x1edf3e7f,
  0xf1f1f1ff, 0xe2c4617f, 0xe6753aff, 0x1e7d7aff,
  0xe0fbea02, 0xf06bd580, 0xfe0b1400, 0x3fbffe80,
  0xeaf2f201, 0xd50e8701, 0xfc190c80, 0x3fdfbf00,
  0xf0efef01, 0xe0c86401, 0xee683401, 0x3efe3c01,
  0xfdf50af5, 0xf083ac00, 0xfc082400, 0x1e403e00,
  0xf1fffffb, 0xe2f97cfb, 0xec2b15ff, 0x1edf3e7f,
  0xf1f1f1ff, 0xe2c4617f, 0xe6753aff, 0x1e7d7aff,
  0xe0fbea02, 0xf06bd580, 0xfe0b1400, 0x3fbffe80,
  0xeaf2f201, 0xd50e8701, 0xfc190c80, 0x3fdfbf00,
  0xf0efef01, 0xe0c86401, 0xee683401, 0x3efe3c01

};
uint32 gTwoDFilterD_LUT[HAL_MDP_QSEED_ENTRIE_SIZE_IN_REGISTERS*HAL_MDP_QSEED_COEFF_LUT_D_ENTRIES] =
{
  0x2ff92f21, 0xf2466b00, 0xf44e2379, 0x1f3ebc80,
  0x0dff3b0f, 0xf27b61ff, 0x06631478, 0x1f3ebd80,
  0x3bf90d0f, 0xf6286180, 0xf4633df8, 0x1fe0fcff,
  0x16f81604, 0xf0565e00, 0x06882b7a, 0x1f00fc00,
  0x1c321cf9, 0xf05d67fa, 0x01fe2e80, 0x06403c7a,
  0x033c0bfc, 0xfa945780, 0xfa0e3480, 0x02ff7cf9,
  0x0b1703fc, 0xf26957f9, 0xfa0e4a00, 0x079f7e80,
  0xfb19fbfe, 0xfe9d44fc, 0xf2304eff, 0x033e7ffc,
  0x0ef20ef3, 0xf852b980, 0x01fe2900, 0x1e403e00,
  0xf3f904f7, 0xe6bf987d, 0xf41a1e7f, 0x1e7f7e7f,
  0xf2f2f2fd, 0xea917800, 0xee514880, 0x1e5dfa80,
  0xe8fee801, 0xfa2cee80, 0x00041600, 0x3fc03e80,
  0xe2f7ee02, 0xe4b8b101, 0xfe111000, 0x3fbfff00,
  0xeaf4ea02, 0xec888381, 0xf6474400, 0x3e9efb01,
  0x0ef20ef3, 0xf852b980, 0x01fe2900, 0x1e403e00,
  0xf3f904f7, 0xe6bf987d, 0xf41a1e7f, 0x1e7f7e7f,
  0xf2f2f2fd, 0xea917800, 0xee514880, 0x1e5dfa80,
  0xe8fee801, 0xfa2cee80, 0x00041600, 0x3fc03e80,
  0xe2f7ee02, 0xe4b8b101, 0xfe111000, 0x3fbfff00,
  0xeaf4ea02, 0xec888381, 0xf6474400, 0x3e9efb01
};

/* Map for VBIF clients for QOS remapper values for all cleints (RT & NRT) */
static HAL_MDP_VBIFQOSRemappersType gSVBIFQOSRemap_9_0_0[HAL_MDP_VBIF_CLIENT_MAX] =
{
    /*     uVBIFQosRemapper00            uVBIFQosRemapper01               uVBIFQosRemapper10                uVBIFQosRemapper11*/
    //Client C0:  HAL_MDP_VBIF_CLIENT_VIG0
    { HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_NON_REALTIME },
    //Client C1:  HAL_MDP_VBIF_CLIENT_DMA0
    { HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_NON_REALTIME },
    //Client C2 : HAL_MDP_VBIF_CLIENT_CURSOR0
    { HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_NON_REALTIME },
    //Client C3 : HAL_MDP_VBIF_CLIENT_NONE0
    { HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_NON_REALTIME },
    //Client C4 : HAL_MDP_VBIF_CLIENT_VIG1
    { HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_NON_REALTIME },
    //Client C5 : HAL_MDP_VBIF_CLIENT_DMA1
    { HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_NON_REALTIME },
    //Client C6 : HAL_MDP_VBIF_CLIENT_WB2
    { HAL_MDP_TRFCTRL_LATENCY_NON_REALTIME, HAL_MDP_TRFCTRL_LATENCY_NON_REALTIME, HAL_MDP_TRFCTRL_LATENCY_NON_REALTIME, HAL_MDP_TRFCTRL_LATENCY_NON_REALTIME },
    //Client C7 : HAL_MDP_VBIF_CLIENT_DSIDMA
    { HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_NON_REALTIME },
    //Client C8 : HAL_MDP_VBIF_CLIENT_VIG2
    { HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_NON_REALTIME },
    //Client C9 : HAL_MDP_VBIF_CLIENT_DMA2
    { HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_NON_REALTIME },
    //Client C10 : HAL_MDP_VBIF_CLIENT_CURSOR1
    { HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_NON_REALTIME },
    //Client C11: HAL_MDP_VBIF_CLIENT_NONE1
    { HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_NON_REALTIME },
    //Client C12 : HAL_MDP_VBIF_CLIENT_VIG3
    { HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_NON_REALTIME },
    //Client C13 : HAL_MDP_VBIF_CLIENT_DMA3
    { HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_REALTIME, HAL_MDP_TRFCTRL_LATENCY_NON_REALTIME },
    //Client C0 : HAL_MDP_VBIF_CLIENT_ROT_RD
    { HAL_MDP_TRFCTRL_LATENCY_NON_REALTIME, HAL_MDP_TRFCTRL_LATENCY_NON_REALTIME, HAL_MDP_TRFCTRL_LATENCY_NON_REALTIME, HAL_MDP_TRFCTRL_LATENCY_NON_REALTIME },
    //Client C1 : HAL_MDP_VBIF_CLIENT_ROT_WR
    { HAL_MDP_TRFCTRL_LATENCY_NON_REALTIME, HAL_MDP_TRFCTRL_LATENCY_NON_REALTIME, HAL_MDP_TRFCTRL_LATENCY_NON_REALTIME, HAL_MDP_TRFCTRL_LATENCY_NON_REALTIME },
};


/*
* This is the mapping between VBIF client ID to VBIF HW block ID
*/
const HAL_MDP_VbifId gsVbifClientToHwIdMap_9_0_0[HAL_MDP_VBIF_CLIENT_MAX] =
{
  HAL_MDP_VBIF_0,      //   HAL_MDP_VBIF_CLIENT_VIG0 = 0x00000000,   // xin0  (RT Port)
  HAL_MDP_VBIF_0,      //   HAL_MDP_VBIF_CLIENT_RGB0,                // Invalid client
  HAL_MDP_VBIF_0,      //   HAL_MDP_VBIF_CLIENT_DMA0,                // xin1  (RT Port)
  HAL_MDP_VBIF_0,      //   HAL_MDP_VBIF_CLIENT_WB0,                 // Invalid client 
  HAL_MDP_VBIF_0,      //   HAL_MDP_VBIF_CLIENT_VIG1,                // xin4  (RT Port)
  HAL_MDP_VBIF_0,      //   HAL_MDP_VBIF_CLIENT_RGB1,                // Invalid client
  HAL_MDP_VBIF_0,      //   HAL_MDP_VBIF_CLIENT_WB2,                 // xin6   (RT Port)
  HAL_MDP_VBIF_0,      //   HAL_MDP_VBIF_CLIENT_CURSOR,              // Invalid client
  HAL_MDP_VBIF_0,      //   HAL_MDP_VBIF_CLIENT_VIG2,                // xin8   (RT Port)
  HAL_MDP_VBIF_0,      //   HAL_MDP_VBIF_CLIENT_RGB2,                // Invalid client
  HAL_MDP_VBIF_0,      //   HAL_MDP_VBIF_CLIENT_DMA1,                // xin5   (RT Port)
  HAL_MDP_VBIF_0,      //   HAL_MDP_VBIF_CLIENT_WB1,                 // Invalid client
  HAL_MDP_VBIF_0,      //   HAL_MDP_VBIF_CLIENT_VIG3,                // xin12  (RT Port)
  HAL_MDP_VBIF_0,      //   HAL_MDP_VBIF_CLIENT_RGB3,                // Invalid client
  HAL_MDP_VBIF_0,      //   HAL_MDP_VBIF_CLIENT_CURSOR0,             // xin2  (RT Port)
  HAL_MDP_VBIF_0,      //   HAL_MDP_VBIF_CLIENT_CURSOR1,             // xin10  (RT Port)  
  HAL_MDP_VBIF_0,      //   HAL_MDP_VBIF_CLIENT_DMA2,                // xin9   (RT Port)
  HAL_MDP_VBIF_0,      //   HAL_MDP_VBIF_CLIENT_DMA3,                // xin13  (RT Port)
  HAL_MDP_VBIF_1,      //   HAL_MDP_VBIF_CLIENT_ROT_RD,              // xin0  (NRT Port)
  HAL_MDP_VBIF_1,      //   HAL_MDP_VBIF_CLIENT_ROT_WR,              // xin1  (NRT Port)
  HAL_MDP_VBIF_0,      //   HAL_MDP_VBIF_CLIENT_DSIDMA,              // xin7   (RT Port)
};


/*
* This is SSPP Danger/Safe/CREQ LUT for Linear format
* Macrotile format has different values
*/
HAL_MDP_QoSLutInfo  gLinearQoSInfo =
{
  0x0000FFFF,                   /* MDSS_VP_0_*_DANGER_LUT   = [0000_0000_3333_3333], 32 bits, each number for 2 bits */
  {
    0x0000FF00,                 /* MDSS_VP_0_*_SAFE_LUT     = [1111_1111_0000_0000], 16 bits, each number for 1 bit, corresponding to portrait panel  */
    0x0000FFF0,                 /* MDSS_VP_0_*_SAFE_LUT     = [1111_1111_1111_0000], 16 bits, each number for 1 bit, corresponding to landscape panel and fFLRequire0 < 4.5 */
  },
  {
    {0x44556666, 0x00112233},   /* MDSS_VP_0_*_CREQ_LUT_0/1 = [0011_2233_4455_6666] 32 bits, corresponding to QSEED Disabled */
    {0x66666666, 0x00112233}    /* MDSS_VP_0_*_CREQ_LUT_0/1 = [0011_2233_6666_6666] 32 bits, corresponding to QSEED Enabled  */
     
  },
};

HAL_MDP_SSPPQoSInfo gsSSPPQoSInfo_9_0_0 =
{
    &gLinearQoSInfo,
    NULL,
    NULL
};

HAL_MDP_DSC_CoreFormatIndex gsDSCEncoderFormatType_8_0_0[HAL_MDP_DSC_MAX] =
{
  HAL_MDP_DSC_V1_2a_2HS_2SS_2IN_10BIT_V1_2,           // HAL_MDP_DSC_NONE
  HAL_MDP_DSC_V1_2a_2HS_2SS_2IN_10BIT_V1_2,           // HAL_MDP_DSC_0
  HAL_MDP_DSC_V1_2a_2HS_2SS_2IN_10BIT_V1_2,           // HAL_MDP_DSC_1
  HAL_MDP_DSC_V1_2a_2HS_2SS_2IN_10BIT_V1_2_420_422,   // HAL_MDP_DSC_2
  HAL_MDP_DSC_V1_2a_2HS_2SS_2IN_10BIT_V1_2_420_422,   // HAL_MDP_DSC_3
  HAL_MDP_DSC_V1_2a_2HS_2SS_2IN_10BIT_V1_2_420_422,   // HAL_MDP_DSC_4
  HAL_MDP_DSC_V1_2a_2HS_2SS_2IN_10BIT_V1_2_420_422,   // HAL_MDP_DSC_5
};

/****************************************************************************
*
** FUNCTION: HAL_MDP_SetHWBlockRegOffsets_9_0_0()
*/
/*!
* \brief
*     set MDP HW block register offsets
*
*
****************************************************************************/
static void HAL_MDP_SetHWBlockRegOffsets_9_0_0(void)
{
  /* Control path HW block register offset */
  uMDPControlPathRegBaseOffset[HAL_MDP_CONTROL_PATH_NONE]           = 0x00000000;
  uMDPControlPathRegBaseOffset[HAL_MDP_CONTROL_PATH_0]              = 0x00000000;
  uMDPControlPathRegBaseOffset[HAL_MDP_CONTROL_PATH_1]              = (MDP_CTL_1_REG_BASE_OFFS - MDP_CTL_0_REG_BASE_OFFS);
  uMDPControlPathRegBaseOffset[HAL_MDP_CONTROL_PATH_2]              = (MDP_CTL_2_REG_BASE_OFFS - MDP_CTL_0_REG_BASE_OFFS);
  uMDPControlPathRegBaseOffset[HAL_MDP_CONTROL_PATH_3]              = (MDP_CTL_3_REG_BASE_OFFS - MDP_CTL_0_REG_BASE_OFFS);
  uMDPControlPathRegBaseOffset[HAL_MDP_CONTROL_PATH_4]              = (MDP_CTL_4_REG_BASE_OFFS - MDP_CTL_0_REG_BASE_OFFS);
  uMDPControlPathRegBaseOffset[HAL_MDP_CONTROL_PATH_5]              = (MDP_CTL_5_REG_BASE_OFFS - MDP_CTL_0_REG_BASE_OFFS);
  uMDPControlPathRegBaseOffset[HAL_MDP_CONTROL_PATH_6]              = 0x00000000;
  uMDPControlPathRegBaseOffset[HAL_MDP_CONTROL_PATH_7]              = 0x00000000;

  /* Data path HW block register offset */
  uMDPDataPathRegBaseOffset[HAL_MDP_DATA_PATH_NONE]                 = 0x00000000;
  uMDPDataPathRegBaseOffset[HAL_MDP_DATA_PATH_0]                    = 0x00000000;
  uMDPDataPathRegBaseOffset[HAL_MDP_DATA_PATH_1]                    = 0x00000000;
  uMDPDataPathRegBaseOffset[HAL_MDP_DATA_PATH_2]                    = 0x00000000;
  uMDPDataPathRegBaseOffset[HAL_MDP_DATA_PATH_3]                    = 0x00000000;
  uMDPDataPathRegBaseOffset[HAL_MDP_DATA_PATH_4]                    = 0x00000000;
  uMDPDataPathRegBaseOffset[HAL_MDP_DATA_PATH_5]                    = 0x00000000;
  uMDPDataPathRegBaseOffset[HAL_MDP_DATA_PATH_6]                    = 0x00000000;
  uMDPDataPathRegBaseOffset[HAL_MDP_DATA_PATH_7]                    = 0x00000000;

  /* Destination (DSPP) HW block register offset */
  uMDPDSPPRegBaseOffset[HAL_MDP_DESTINATION_PIPE_NONE]              = 0x00000000;
  uMDPDSPPRegBaseOffset[HAL_MDP_DESTINATION_PIPE_0]                 = 0x00000000;
  uMDPDSPPRegBaseOffset[HAL_MDP_DESTINATION_PIPE_1]                 = (MDP_VP_0_DSPP_1_REG_BASE_OFFS - MDP_VP_0_DSPP_0_REG_BASE_OFFS);
  uMDPDSPPRegBaseOffset[HAL_MDP_DESTINATION_PIPE_2]                 = (MDP_VP_0_DSPP_2_REG_BASE_OFFS - MDP_VP_0_DSPP_0_REG_BASE_OFFS);
  uMDPDSPPRegBaseOffset[HAL_MDP_DESTINATION_PIPE_3]                 = (MDP_VP_0_DSPP_3_REG_BASE_OFFS - MDP_VP_0_DSPP_0_REG_BASE_OFFS);
  uMDPDSPPRegBaseOffset[HAL_MDP_DESTINATION_PIPE_4]                 = 0x00000000;

  /* Physical interface HW block register offset */
  uMDPPhyInterfaceRegBaseOffset[HAL_MDP_PHYSICAL_INTERFACE_ID_NONE] = 0x00000000;
  uMDPPhyInterfaceRegBaseOffset[HAL_MDP_PHYSICAL_INTERFACE_0]       = 0x00000000;                                             // DP0 - Stream0
  uMDPPhyInterfaceRegBaseOffset[HAL_MDP_PHYSICAL_INTERFACE_1]       = (MDP_INTF_1_REG_BASE_OFFS - MDP_INTF_0_REG_BASE_OFFS);  // DSI0
  uMDPPhyInterfaceRegBaseOffset[HAL_MDP_PHYSICAL_INTERFACE_2]       = (MDP_INTF_2_REG_BASE_OFFS - MDP_INTF_0_REG_BASE_OFFS);  // DSI1
  uMDPPhyInterfaceRegBaseOffset[HAL_MDP_PHYSICAL_INTERFACE_3]       = (MDP_INTF_3_REG_BASE_OFFS - MDP_INTF_0_REG_BASE_OFFS);  // DP0 - Stream1
  uMDPPhyInterfaceRegBaseOffset[HAL_MDP_PHYSICAL_INTERFACE_4]       = (MDP_INTF_4_REG_BASE_OFFS - MDP_INTF_0_REG_BASE_OFFS);  // DP1 - Stream0
  uMDPPhyInterfaceRegBaseOffset[HAL_MDP_PHYSICAL_INTERFACE_5]       = (MDP_INTF_5_REG_BASE_OFFS - MDP_INTF_0_REG_BASE_OFFS);  // DP3 - Stream0
  uMDPPhyInterfaceRegBaseOffset[HAL_MDP_PHYSICAL_INTERFACE_6]       = (MDP_INTF_6_REG_BASE_OFFS - MDP_INTF_0_REG_BASE_OFFS);  // DP2 - Stream0
  uMDPPhyInterfaceRegBaseOffset[HAL_MDP_PHYSICAL_INTERFACE_7]       = (MDP_INTF_7_REG_BASE_OFFS - MDP_INTF_0_REG_BASE_OFFS);  // DP2 - Stream1
  uMDPPhyInterfaceRegBaseOffset[HAL_MDP_PHYSICAL_INTERFACE_8]       = (MDP_INTF_8_REG_BASE_OFFS - MDP_INTF_0_REG_BASE_OFFS);  // DP1 - Stream1


  /* Layer mixer HW block register offset */
  uMDPLayerMixerRegBaseOffset[HAL_MDP_LAYER_MIXER_NONE]             = 0x00000000;
  uMDPLayerMixerRegBaseOffset[HAL_MDP_LAYER_MIXER_0]                = 0x00000000;
  uMDPLayerMixerRegBaseOffset[HAL_MDP_LAYER_MIXER_1]                = (MDP_VP_0_LAYER_1_REG_BASE_OFFS - MDP_VP_0_LAYER_0_REG_BASE_OFFS);
  uMDPLayerMixerRegBaseOffset[HAL_MDP_LAYER_MIXER_2]                = (MDP_VP_0_LAYER_2_REG_BASE_OFFS - MDP_VP_0_LAYER_0_REG_BASE_OFFS);
  uMDPLayerMixerRegBaseOffset[HAL_MDP_LAYER_MIXER_3]                = (MDP_VP_0_LAYER_3_REG_BASE_OFFS - MDP_VP_0_LAYER_0_REG_BASE_OFFS);
  uMDPLayerMixerRegBaseOffset[HAL_MDP_LAYER_MIXER_4]                = (MDP_VP_0_LAYER_4_REG_BASE_OFFS - MDP_VP_0_LAYER_0_REG_BASE_OFFS);
  uMDPLayerMixerRegBaseOffset[HAL_MDP_LAYER_MIXER_5]                = (MDP_VP_0_LAYER_5_REG_BASE_OFFS - MDP_VP_0_LAYER_0_REG_BASE_OFFS);
  uMDPLayerMixerRegBaseOffset[HAL_MDP_LAYER_MIXER_6]                = 0x00000000;

  /* Layer mixer blending stage register offset */
  uMDPLayerMixerBlendStateRegBaseOffset[HAL_MDP_BLEND_STAGE_0]  = 0x00000000;
  uMDPLayerMixerBlendStateRegBaseOffset[HAL_MDP_BLEND_STAGE_1]  = (HWIO_MDP_VP_0_LAYER_0_BLENDn_OP_OFFS(1) - HWIO_MDP_VP_0_LAYER_0_BLENDn_OP_OFFS(0));
  uMDPLayerMixerBlendStateRegBaseOffset[HAL_MDP_BLEND_STAGE_2]  = (HWIO_MDP_VP_0_LAYER_0_BLENDn_OP_OFFS(2) - HWIO_MDP_VP_0_LAYER_0_BLENDn_OP_OFFS(0));
  uMDPLayerMixerBlendStateRegBaseOffset[HAL_MDP_BLEND_STAGE_3]  = (HWIO_MDP_VP_0_LAYER_0_BLENDn_OP_OFFS(3) - HWIO_MDP_VP_0_LAYER_0_BLENDn_OP_OFFS(0));
  uMDPLayerMixerBlendStateRegBaseOffset[HAL_MDP_BLEND_STAGE_4]  = (HWIO_MDP_VP_0_LAYER_0_BLENDn_OP_OFFS(4) - HWIO_MDP_VP_0_LAYER_0_BLENDn_OP_OFFS(0));
  uMDPLayerMixerBlendStateRegBaseOffset[HAL_MDP_BLEND_STAGE_5]  = (HWIO_MDP_VP_0_LAYER_0_BLENDn_OP_OFFS(5) - HWIO_MDP_VP_0_LAYER_0_BLENDn_OP_OFFS(0));
  uMDPLayerMixerBlendStateRegBaseOffset[HAL_MDP_BLEND_STAGE_6]  = (HWIO_MDP_VP_0_LAYER_0_BLENDn_OP_OFFS(6) - HWIO_MDP_VP_0_LAYER_0_BLENDn_OP_OFFS(0));
  uMDPLayerMixerBlendStateRegBaseOffset[HAL_MDP_BLEND_STAGE_7]  = (HWIO_MDP_VP_0_LAYER_0_BLENDn_OP_OFFS(7) - HWIO_MDP_VP_0_LAYER_0_BLENDn_OP_OFFS(0));
  uMDPLayerMixerBlendStateRegBaseOffset[HAL_MDP_BLEND_STAGE_8]  = (HWIO_MDP_VP_0_LAYER_0_BLENDn_OP_OFFS(8) - HWIO_MDP_VP_0_LAYER_0_BLENDn_OP_OFFS(0));
  uMDPLayerMixerBlendStateRegBaseOffset[HAL_MDP_BLEND_STAGE_9]  = (HWIO_MDP_VP_0_LAYER_0_BLENDn_OP_OFFS(9) - HWIO_MDP_VP_0_LAYER_0_BLENDn_OP_OFFS(0));
  uMDPLayerMixerBlendStateRegBaseOffset[HAL_MDP_BLEND_STAGE_10] = (HWIO_MDP_VP_0_LAYER_0_BLENDn_OP_OFFS(10) - HWIO_MDP_VP_0_LAYER_0_BLENDn_OP_OFFS(0));

  /* PingPong HW block register offset */
  uMDPPingPongRegBaseOffset[HAL_MDP_PINGPONG_NONE]                  = 0x00000000;
  uMDPPingPongRegBaseOffset[HAL_MDP_PINGPONG_0]                     = 0x00000000;
  uMDPPingPongRegBaseOffset[HAL_MDP_PINGPONG_1]                     = (MDP_PPB_1_REG_BASE - MDP_PPB_0_REG_BASE);
  uMDPPingPongRegBaseOffset[HAL_MDP_PINGPONG_2]                     = (MDP_PPB_2_REG_BASE - MDP_PPB_0_REG_BASE);
  uMDPPingPongRegBaseOffset[HAL_MDP_PINGPONG_3]                     = (MDP_PPB_3_REG_BASE - MDP_PPB_0_REG_BASE);
  uMDPPingPongRegBaseOffset[HAL_MDP_PINGPONG_4]                     = (MDP_PPB_4_REG_BASE - MDP_PPB_0_REG_BASE);
  uMDPPingPongRegBaseOffset[HAL_MDP_PINGPONG_5]                     = (MDP_PPB_5_REG_BASE - MDP_PPB_0_REG_BASE);
  uMDPPingPongRegBaseOffset[HAL_MDP_PINGPONG_6]                     = 0x00000000;

  /* DSC Core register offset */
  uMDPDSCCoreBaseOffset[HAL_MDP_DSC_CORE_0]                          = 0x00000000;
  uMDPDSCCoreBaseOffset[HAL_MDP_DSC_CORE_1]                          = (MDP_DSC_1_REG_BASE_OFFS - MDP_DSC_0_REG_BASE_OFFS);
  uMDPDSCCoreBaseOffset[HAL_MDP_DSC_CORE_2]                          = (MDP_DSC_2_REG_BASE_OFFS - MDP_DSC_0_REG_BASE_OFFS);

 /* DSC ENC register offset */
  uMDPDSCEncBaseOffset[HAL_MDP_DSC_NONE]                            = 0x00000000;
  uMDPDSCEncBaseOffset[HAL_MDP_DSC_0]                               = 0x00000000;
  uMDPDSCEncBaseOffset[HAL_MDP_DSC_1]                               = (MDP_DSC_0_DSC_1_ENC_REG_BASE_OFFS - MDP_DSC_0_DSC_0_ENC_REG_BASE_OFFS);
  uMDPDSCEncBaseOffset[HAL_MDP_DSC_2]                               = 0x00000000;
  uMDPDSCEncBaseOffset[HAL_MDP_DSC_3]                               = (MDP_DSC_1_DSC_1_ENC_REG_BASE_OFFS - MDP_DSC_1_DSC_0_ENC_REG_BASE_OFFS);
  uMDPDSCEncBaseOffset[HAL_MDP_DSC_4]                               = 0x00000000;
  uMDPDSCEncBaseOffset[HAL_MDP_DSC_5]                               = (MDP_DSC_2_DSC_1_ENC_REG_BASE_OFFS - MDP_DSC_2_DSC_0_ENC_REG_BASE_OFFS);

 /* DSC Ctl register offset */
  uMDPDSCCtlBaseOffset[HAL_MDP_DSC_NONE]                            = 0x00000000;
  uMDPDSCCtlBaseOffset[HAL_MDP_DSC_0]                               = 0x00000000;
  uMDPDSCCtlBaseOffset[HAL_MDP_DSC_1]                               = (MDP_DSC_0_DSC_1_REG_BASE_OFFS - MDP_DSC_0_DSC_0_REG_BASE_OFFS);
  uMDPDSCCtlBaseOffset[HAL_MDP_DSC_2]                               = 0x00000000;
  uMDPDSCCtlBaseOffset[HAL_MDP_DSC_3]                               = (MDP_DSC_1_DSC_1_REG_BASE_OFFS - MDP_DSC_1_DSC_0_REG_BASE_OFFS);
  uMDPDSCCtlBaseOffset[HAL_MDP_DSC_4]                               = 0x00000000;
  uMDPDSCCtlBaseOffset[HAL_MDP_DSC_5]                               = (MDP_DSC_2_DSC_1_REG_BASE_OFFS - MDP_DSC_2_DSC_0_REG_BASE_OFFS);
  
  /* VDCM Core register offset */
  uMDPVDCMCoreBaseOffset[HAL_MDP_VDCM_CORE_0]                       = 0x00000000;
  
  /* VDCM Enc register offset*/
  uMDPVDCMEncBaseOffset[HAL_MDP_VDCM_NONE]                          = 0x00000000;
  uMDPVDCMEncBaseOffset[HAL_MDP_VDCM_0]                             = 0x00000000;
  uMDPVDCMEncBaseOffset[HAL_MDP_VDCM_1]                             = 0x00000000;
  uMDPVDCMEncBaseOffset[HAL_MDP_VDCM_2]                             = (MDP_VDC_0_VDC_1_ENC_REG_BASE_OFFS - MDP_VDC_0_VDC_0_ENC_REG_BASE_OFFS);
  uMDPVDCMEncBaseOffset[HAL_MDP_VDCM_3]                             = (MDP_VDC_0_VDC_1_ENC_REG_BASE_OFFS - MDP_VDC_0_VDC_0_ENC_REG_BASE_OFFS);

  /* VDCM Ctl register offset */
  uMDPVDCMCtlBaseOffset[HAL_MDP_VDCM_NONE]                          = 0x00000000;
  uMDPVDCMEncBaseOffset[HAL_MDP_VDCM_0]                             = 0x00000000;
  uMDPVDCMEncBaseOffset[HAL_MDP_VDCM_1]                             = (MDP_VDC_0_VDC_01_REG_BASE_OFFS - MDP_VDC_0_VDC_00_REG_BASE_OFFS);
  uMDPVDCMEncBaseOffset[HAL_MDP_VDCM_2]                             = (MDP_VDC_0_VDC_10_REG_BASE_OFFS - MDP_VDC_0_VDC_00_REG_BASE_OFFS);
  uMDPVDCMEncBaseOffset[HAL_MDP_VDCM_3]                             = (MDP_VDC_0_VDC_11_REG_BASE_OFFS - MDP_VDC_0_VDC_00_REG_BASE_OFFS);

  /* Source (SSPP) HW block register offset */
  uMDPSSPPRegBaseOffset[HAL_MDP_SOURCE_PIPE_NONE]                   = 0x00000000;
  uMDPSSPPRegBaseOffset[HAL_MDP_SOURCE_PIPE_VIG_0]                  = 0x00000000;
  uMDPSSPPRegBaseOffset[HAL_MDP_SOURCE_PIPE_VIG_1]                  = (MDP_VP_0_VIG_1_SSPP_REG_BASE_OFFS - MDP_VP_0_VIG_0_SSPP_REG_BASE_OFFS);
  uMDPSSPPRegBaseOffset[HAL_MDP_SOURCE_PIPE_VIG_2]                  = (MDP_VP_0_VIG_2_SSPP_REG_BASE_OFFS - MDP_VP_0_VIG_0_SSPP_REG_BASE_OFFS);
  uMDPSSPPRegBaseOffset[HAL_MDP_SOURCE_PIPE_VIG_3]                  = (MDP_VP_0_VIG_3_SSPP_REG_BASE_OFFS - MDP_VP_0_VIG_0_SSPP_REG_BASE_OFFS);
  uMDPSSPPRegBaseOffset[HAL_MDP_SOURCE_PIPE_DMA_0]                  = (MDP_VP_0_DMA_0_SSPP_REG_BASE_OFFS - MDP_VP_0_VIG_0_SSPP_REG_BASE_OFFS);
  uMDPSSPPRegBaseOffset[HAL_MDP_SOURCE_PIPE_DMA_1]                  = (MDP_VP_0_DMA_1_SSPP_REG_BASE_OFFS - MDP_VP_0_VIG_0_SSPP_REG_BASE_OFFS);
  uMDPSSPPRegBaseOffset[HAL_MDP_SOURCE_PIPE_DMA_2]                  = (MDP_VP_0_DMA_2_SSPP_REG_BASE_OFFS - MDP_VP_0_VIG_0_SSPP_REG_BASE_OFFS);
  uMDPSSPPRegBaseOffset[HAL_MDP_SOURCE_PIPE_DMA_3]                  = (MDP_VP_0_DMA_3_SSPP_REG_BASE_OFFS - MDP_VP_0_VIG_0_SSPP_REG_BASE_OFFS);
  uMDPSSPPRegBaseOffset[HAL_MDP_SOURCE_PIPE_DMA_4]                  = (MDP_VP_0_DMA_4_SSPP_REG_BASE_OFFS - MDP_VP_0_VIG_0_SSPP_REG_BASE_OFFS);
  uMDPSSPPRegBaseOffset[HAL_MDP_SOURCE_PIPE_DMA_5]                  = (MDP_VP_0_DMA_5_SSPP_REG_BASE_OFFS - MDP_VP_0_VIG_0_SSPP_REG_BASE_OFFS);;
  uMDPSSPPRegBaseOffset[HAL_MDP_SOURCE_PIPE_DMA_0_REC1]             = (MDP_VP_0_DMA_0_SSPP_REG_BASE_OFFS - MDP_VP_0_VIG_0_SSPP_REG_BASE_OFFS);
  uMDPSSPPRegBaseOffset[HAL_MDP_SOURCE_PIPE_DMA_1_REC1]             = (MDP_VP_0_DMA_1_SSPP_REG_BASE_OFFS - MDP_VP_0_VIG_0_SSPP_REG_BASE_OFFS);
  uMDPSSPPRegBaseOffset[HAL_MDP_SOURCE_PIPE_DMA_2_REC1]             = (MDP_VP_0_DMA_2_SSPP_REG_BASE_OFFS - MDP_VP_0_VIG_0_SSPP_REG_BASE_OFFS);
  uMDPSSPPRegBaseOffset[HAL_MDP_SOURCE_PIPE_DMA_3_REC1]             = (MDP_VP_0_DMA_3_SSPP_REG_BASE_OFFS - MDP_VP_0_VIG_0_SSPP_REG_BASE_OFFS);
  uMDPSSPPRegBaseOffset[HAL_MDP_SOURCE_PIPE_DMA_4_REC1]             = (MDP_VP_0_DMA_4_SSPP_REG_BASE_OFFS - MDP_VP_0_VIG_0_SSPP_REG_BASE_OFFS);
  uMDPSSPPRegBaseOffset[HAL_MDP_SOURCE_PIPE_DMA_5_REC1]             = (MDP_VP_0_DMA_5_SSPP_REG_BASE_OFFS - MDP_VP_0_VIG_0_SSPP_REG_BASE_OFFS);

  /* Source (SSPP) Layer (Scalar) HW block register offset */
  uMDPLayerRegBaseOffset[HAL_MDP_SOURCE_PIPE_NONE]                   = 0x00000000;
  uMDPLayerRegBaseOffset[HAL_MDP_SOURCE_PIPE_VIG_0]                  = 0x00000000;
  uMDPLayerRegBaseOffset[HAL_MDP_SOURCE_PIPE_VIG_1]                  = (MDP_VP_0_VIG_1_QSEED3_REG_BASE_OFFS - MDP_VP_0_VIG_0_QSEED3_REG_BASE_OFFS);
  uMDPLayerRegBaseOffset[HAL_MDP_SOURCE_PIPE_VIG_2]                  = (MDP_VP_0_VIG_2_QSEED3_REG_BASE_OFFS - MDP_VP_0_VIG_0_QSEED3_REG_BASE_OFFS);
  uMDPLayerRegBaseOffset[HAL_MDP_SOURCE_PIPE_VIG_3]                  = (MDP_VP_0_VIG_3_QSEED3_REG_BASE_OFFS - MDP_VP_0_VIG_0_QSEED3_REG_BASE_OFFS);
  uMDPLayerRegBaseOffset[HAL_MDP_SOURCE_PIPE_DMA_0]                  = 0x00000000;
  uMDPLayerRegBaseOffset[HAL_MDP_SOURCE_PIPE_DMA_1]                  = 0x00000000;
  uMDPLayerRegBaseOffset[HAL_MDP_SOURCE_PIPE_DMA_2]                  = 0x00000000;
  uMDPLayerRegBaseOffset[HAL_MDP_SOURCE_PIPE_DMA_3]                  = 0x00000000;
  uMDPLayerRegBaseOffset[HAL_MDP_SOURCE_PIPE_DMA_4]                  = 0x00000000;
  uMDPLayerRegBaseOffset[HAL_MDP_SOURCE_PIPE_DMA_5]                  = 0x00000000;

  /* Destination scaler HW block register offset*/
  uMDPDestScalerRegBaseOffset[HAL_MDP_DESTINATION_PIPE_NONE]         = 0x00000000;
  uMDPDestScalerRegBaseOffset[HAL_MDP_DESTINATION_PIPE_0]            = 0x00000000;
  uMDPDestScalerRegBaseOffset[HAL_MDP_DESTINATION_PIPE_1]            = (MDP_DEST_SCALER_1_REG_BASE_OFFS - MDP_DEST_SCALER_0_REG_BASE_OFFS);
  uMDPDestScalerRegBaseOffset[HAL_MDP_DESTINATION_PIPE_2]            = (MDP_DEST_SCALER_2_REG_BASE_OFFS - MDP_DEST_SCALER_0_REG_BASE_OFFS);
  uMDPDestScalerRegBaseOffset[HAL_MDP_DESTINATION_PIPE_3]            = (MDP_DEST_SCALER_3_REG_BASE_OFFS - MDP_DEST_SCALER_0_REG_BASE_OFFS);
  uMDPDestScalerRegBaseOffset[HAL_MDP_DESTINATION_PIPE_4]            = 0x00000000;

  /* Vbif register offset */
  uMDPVbifRegBaseOffset[HAL_MDP_VBIF_0]                              = 0x00000000;
  uMDPVbifRegBaseOffset[HAL_MDP_VBIF_1]                              = (VBIF_NRT_MDSS_VBIF_ROT_REG_BASE - VBIF_MDSS_VBIF_SDE_REG_BASE);

  /* Physical Interface TEAR check register offset */
  uMDPIntfTearRegBaseOffset[HAL_MDP_PHYSICAL_INTERFACE_ID_NONE]      = 0x00000000;
  uMDPIntfTearRegBaseOffset[HAL_MDP_PHYSICAL_INTERFACE_0]            = 0x00000000;
  uMDPIntfTearRegBaseOffset[HAL_MDP_PHYSICAL_INTERFACE_1]            = 0x00000000;
  uMDPIntfTearRegBaseOffset[HAL_MDP_PHYSICAL_INTERFACE_2]            = (MDP_INTF_2_TEAR_REG_BASE_OFFS - MDP_INTF_1_TEAR_REG_BASE_OFFS);
  uMDPIntfTearRegBaseOffset[HAL_MDP_PHYSICAL_INTERFACE_3]            = 0x00000000;
  uMDPIntfTearRegBaseOffset[HAL_MDP_PHYSICAL_INTERFACE_4]            = 0x00000000;
  uMDPIntfTearRegBaseOffset[HAL_MDP_PHYSICAL_INTERFACE_5]            = 0x00000000;

  /* 3D Mux register offset */
  uMDP3DMuxRegBaseOffset[HAL_MDP_3DMUX_0]                            = 0x00000000;
  uMDP3DMuxRegBaseOffset[HAL_MDP_3DMUX_1]                            = (MDP_MERGE_3D_1_REG_BASE_OFFS - MDP_MERGE_3D_0_REG_BASE_OFFS);
  uMDP3DMuxRegBaseOffset[HAL_MDP_3DMUX_2]                            = (MDP_MERGE_3D_2_REG_BASE_OFFS - MDP_MERGE_3D_0_REG_BASE_OFFS);

  /* SPR HW block register offset */
  uMDPSprRegBaseOffset[HAL_MDP_SPR_NONE]                             = 0x00000000;
  uMDPSprRegBaseOffset[HAL_MDP_SPR_0]                                = 0x00000000;
  uMDPSprRegBaseOffset[HAL_MDP_SPR_1]                                = (MDP_SPR_1_REG_BASE_OFFS - MDP_SPR_0_REG_BASE_OFFS);

  /* Demura HW block register offset */
  uMDPDemuraRegBaseOffset[HAL_MDP_DEMURA_NONE]                       = 0x00000000;
  uMDPDemuraRegBaseOffset[HAL_MDP_DEMURA_0]                          = 0x00000000;
  uMDPDemuraRegBaseOffset[HAL_MDP_DEMURA_1]                          = (MDP_DEMURA_1_REG_BASE_OFFS - MDP_DEMURA_0_REG_BASE_OFFS);

  /* Interface stream-based MISR configuration register offsets */
  uMDPIntfMisrStreamRegBaseOffset[HAL_MDP_INTERFACE_STREAM_VIDEO_0] = 0x00000000;
}



/****************************************************************************
*
** FUNCTION: HAL_MDP_ReadHardwareInfo_9_0_0()
*/
/*!
* \brief
*     Reads the hardware capabilities for the given MDP Version(5.x.0)
*
* \param [out]  psHwInfo            - Hardware information
* \param [out]  psMdpHwInfo         - MDP hardware information 
*
* \retval NONE
*
****************************************************************************/
void HAL_MDP_ReadHardwareInfo_9_0_0(HAL_MDP_HwInfo             *psHwInfo,
                                    HAL_MDP_Hw_Private_Info    *psMdpHwInfo)
{
   // Calculate block offsets for blocks that have multiple instances, ex. VIGs or DSPPs.
   HAL_MDP_SetHWBlockRegOffsets_9_0_0();

   if(NULL != psHwInfo)
   {
      psHwInfo->uNumOfRGBLayers                                                        = HAL_MDP_9_0_0_NUM_OF_RGB_LAYERS;
      psHwInfo->uNumOfVIGLayers                                                        = HAL_MDP_9_0_0_NUM_OF_VIG_LAYERS;
      psHwInfo->uNumOfDMALayers                                                        = HAL_MDP_9_0_0_NUM_OF_DMA_LAYERS;
      psHwInfo->uNumOfCursorLayers                                                     = HAL_MDP_9_0_0_NUM_OF_CURSOR_LAYERS;
      psHwInfo->uNumOfLayerMixers                                                      = HAL_MDP_9_0_0_NUM_OF_LAYER_MIXERS;
      psHwInfo->uNumOfDSPPs                                                            = HAL_MDP_9_0_0_NUM_OF_DSPP;
      psHwInfo->uNumOfBltEngines                                                       = HAL_MDP_9_0_0_NUM_OF_WRITEBACK_INTERFACES;
      psHwInfo->uNumOfControlPaths                                                     = HAL_MDP_9_0_0_NUM_OF_CONTROL_PATHS;
      psHwInfo->uNumOfDataPaths                                                        = HAL_MDP_9_0_0_NUM_OF_DATA_PATHS;
      psHwInfo->uNumOfLayerMixerBlendStages                                            = HAL_MDP_9_0_0_LAYER_MIXER_MAX_BLEND_STAGES;
      psHwInfo->uNumOfPhyInterfaces                                                    = HAL_MDP_9_0_0_NUM_OF_PHYSICAL_INTERFACES;
      psHwInfo->uNumOfPingPongs                                                        = HAL_MDP_9_0_0_NUM_OF_PINGPONGS;
      psHwInfo->uNumOfWatchDogs                                                        = HAL_MDP_9_0_0_NUM_OF_WATCHDOGS;
      psHwInfo->uNumOfAxiPorts                                                         = HAL_MDP_9_0_0_NUM_OF_AXI_PORTS;
      psHwInfo->uNumOfVbifClients                                                      = HAL_MDP_9_0_0_NUM_OF_VBIF_CLIENTS;       
      psHwInfo->eGamutType                                                             = HAL_MDP_GAMUT_8BITGAMUT_TYPE;
      psHwInfo->uNumOfChromaDownBlocks                                                 = HAL_MDP_9_0_0_NUM_OF_CHROMA_BLOCKS;
      psHwInfo->eGCLUTType                                                             = HAL_MDP_GCLUT_LINEAR_TYPE;
      psHwInfo->eGamutType                                                             = HAL_MDP_GAMUT_WIDEGAMUT_TYPE;
      psHwInfo->ePCCType                                                               = HAL_MDP_PCC_TYPE3;

      if (PcdGet32(PcdPrimaryFlags) & HAL_MDP_DISPLAY_FLAG_ENABLE_PFS)
      {
        psHwInfo->uFeatureFlags                                                        = HAL_MDP_FLAG_FEATURE_PROGRAMMABLE_FETCH_START;
      }
   }

   if(NULL != psMdpHwInfo)
   {
      /** Color Space Conversion(CSC) - Limited REC601 - YUV to RGB */
      psMdpHwInfo->pCSC_ColorYUVToRGBEncodingInfo[HAL_MDP_COLOR_ENCODING_REC601]       =  &gMDP_CSC_YuvToRgb_Limited_Rec601;
      /** Color Space Conversion(CSC) - Limited REC601 - RGB to YUV */
      psMdpHwInfo->pCSC_ColorRGBToYUVEncodingInfo[HAL_MDP_COLOR_ENCODING_REC601]       =  &gMDP_CSC_RgbToYuv_Limited_Rec601;
      /** Color Space Conversion(CSC) - Full REC601 - YUV to RGB */
      psMdpHwInfo->pCSC_ColorYUVToRGBEncodingInfo[HAL_MDP_COLOR_ENCODING_FULL_REC601]  =  &gMDP_CSC_YuvToRgb_Full_Rec601; 
      /** Color Space Conversion(CSC) - Full REC601 - RGB to YUV */
      psMdpHwInfo->pCSC_ColorRGBToYUVEncodingInfo[HAL_MDP_COLOR_ENCODING_FULL_REC601]  =  &gMDP_CSC_RgbToYuv_Full_Rec601;
      /** Color Space Conversion(CSC) - Limited REC709 - YUV to RGB */
      psMdpHwInfo->pCSC_ColorYUVToRGBEncodingInfo[HAL_MDP_COLOR_ENCODING_REC709]       =  &gMDP_CSC_YuvToRgb_Limited_Rec709;
      /** Color Space Conversion(CSC) - Limited REC709 - RGB to YUV */
      psMdpHwInfo->pCSC_ColorRGBToYUVEncodingInfo[HAL_MDP_COLOR_ENCODING_REC709]       =  &gMDP_CSC_RgbToYuv_Limited_Rec709;
      /** Color Space Conversion(CSC) - Full REC709 - YUV to RGB */
      psMdpHwInfo->pCSC_ColorYUVToRGBEncodingInfo[HAL_MDP_COLOR_ENCODING_FULL_REC709]  =  &gMDP_CSC_YuvToRgb_Full_Rec709;
      /** Color Space Conversion(CSC) - Full REC709 - RGB to YUV */
      psMdpHwInfo->pCSC_ColorRGBToYUVEncodingInfo[HAL_MDP_COLOR_ENCODING_FULL_REC709]  =  &gMDP_CSC_RgbToYuv_Full_Rec709;    

      // QSEED
      psMdpHwInfo->pTwoDFilterA                                                        = gTwoDFilterA_LUT; 
      psMdpHwInfo->uTwoDFilterACoeffCnt                                                = sizeof(gTwoDFilterA_LUT)/sizeof(gTwoDFilterA_LUT[0]);            /**< QSEED 2DFilterA Coefficient count */
      psMdpHwInfo->pTwoDFilterB                                                        = gTwoDFilterB_LUT; 
      psMdpHwInfo->uTwoDFilterBCoeffCnt                                                = sizeof(gTwoDFilterB_LUT)/sizeof(gTwoDFilterB_LUT[0]);            /**< QSEED 2DFilterB Coefficient count */
      psMdpHwInfo->pTwoDFilterC                                                        = gTwoDFilterC_LUT; 
      psMdpHwInfo->uTwoDFilterCCoeffCnt                                                = sizeof(gTwoDFilterC_LUT)/sizeof(gTwoDFilterC_LUT[0]);            /**< QSEED 2DFilterC Coefficient count */
      psMdpHwInfo->pTwoDFilterD                                                        = gTwoDFilterD_LUT; 
      psMdpHwInfo->uTwoDFilterDCoeffCnt                                                = sizeof(gTwoDFilterD_LUT)/sizeof(gTwoDFilterD_LUT[0]);            /**< QSEED 2DFilterD Coefficient count */
      
      // DSC
      psMdpHwInfo->pDSCEncoderFormat                                                  = &gsDSCEncoderFormatType_8_0_0[0];

      // QOS & VBIF
      psMdpHwInfo->uVBIFMaxDdrRdBurstSize                                              = HAL_MDP_9_0_0_VBIF_MAX_DDR_RD_BURST_SIZE;
      psMdpHwInfo->uVBIFMaxDdrWrBurstSize                                              = HAL_MDP_9_0_0_VBIF_MAX_DDR_WR_BURST_SIZE;
      psMdpHwInfo->uVBIFMaxRdOT                                                        = HAL_MDP_9_0_0_VBIF_MAX_RD_OT_SIZE;
      psMdpHwInfo->uVBIFMaxWrOT                                                        = HAL_MDP_9_0_0_VBIF_MAX_WR_OT_SIZE;      
      
      psMdpHwInfo->uVBIFRoundRobinQosArb                                               = HAL_MDP_9_0_0_VBIF_ROUND_ROBIN_QOS_ARB;
      psMdpHwInfo->pVBIFQOSRemappers                                                   = &gSVBIFQOSRemap_9_0_0[0];
      psMdpHwInfo->pVBIFClientToHWIDMap                                                = &gsVbifClientToHwIdMap_9_0_0[0];

      // SSPP QoS (Danger, Safe, CReq) setting
      psMdpHwInfo->psSSPPQoSInfo                                                       = &gsSSPPQoSInfo_9_0_0;
      psMdpHwInfo->sIpFxnTbl.SSPPQosConfig                                             = &HAL_MDP_SSPP_SetQosConfig_9_0_0;

      //Picture adjustment(HSIC) 
      psMdpHwInfo->sPictureAdjustInfo.iMinHue                                          = HAL_MDP_9_0_0_PICTURE_ADJUST_MIN_HUE;
      psMdpHwInfo->sPictureAdjustInfo.iMaxHue                                          = HAL_MDP_9_0_0_PICTURE_ADJUST_MAX_HUE;
      psMdpHwInfo->sPictureAdjustInfo.iMinUnchangeHue                                  = HAL_MDP_9_0_0_PICTURE_ADJUST_MIN_UNCHANGE_HUE;
      psMdpHwInfo->sPictureAdjustInfo.iMaxUnchangeHue                                  = HAL_MDP_9_0_0_PICTURE_ADJUST_MAX_UNCHANGE_HUE;
      psMdpHwInfo->sPictureAdjustInfo.iMinSaturation                                   = HAL_MDP_9_0_0_PICTURE_ADJUST_MIN_SATURATION;
      psMdpHwInfo->sPictureAdjustInfo.iMaxSaturation                                   = HAL_MDP_9_0_0_PICTURE_ADJUST_MAX_SATURATION;
      psMdpHwInfo->sPictureAdjustInfo.iUnchangeSaturation                              = HAL_MDP_9_0_0_PICTURE_ADJUST_UNCHANGE_SATURATION;
      psMdpHwInfo->sPictureAdjustInfo.iMinIntensity                                    = HAL_MDP_9_0_0_PICTURE_ADJUST_MIN_INTENSITY;
      psMdpHwInfo->sPictureAdjustInfo.iMaxIntensity                                    = HAL_MDP_9_0_0_PICTURE_ADJUST_MAX_INTENSITY;
      psMdpHwInfo->sPictureAdjustInfo.iUnchangeIntensity                               = HAL_MDP_9_0_0_PICTURE_ADJUST_UNCHANGE_INTENSITY;
      psMdpHwInfo->sPictureAdjustInfo.iMinContrast                                     = HAL_MDP_9_0_0_PICTURE_ADJUST_MIN_CONTRAST;
      psMdpHwInfo->sPictureAdjustInfo.iMaxContrast                                     = HAL_MDP_9_0_0_PICTURE_ADJUST_MAX_CONTRAST;
      psMdpHwInfo->sPictureAdjustInfo.iUnchangeContrast                                = HAL_MDP_9_0_0_PICTURE_ADJUST_UNCHANGE_CONTRAST;

      psMdpHwInfo->uHysterisisValue                                                    = HAL_MDP_9_0_0_HYSTERISIS_DEFAULT;

      // Histogram config function

      // Histogram lock function
      
      // Initialize the module's status register details
      psMdpHwInfo->gpsModuleStatusRegInfo[HAL_MDP_MODULE_TYPE_NONE]                    = (uint32 *)NULL;
      psMdpHwInfo->gpsModuleStatusRegInfo[HAL_MDP_MODULE_SOURCE_PIPE]                  = (uint32 *)&gsSSPPModuleStatusRegInfo;
      psMdpHwInfo->gpsModuleStatusRegInfo[HAL_MDP_MODULE_LAYERMIXER]                   = (uint32 *)NULL;
      psMdpHwInfo->gpsModuleStatusRegInfo[HAL_MDP_MODULE_DESTINATION_PIPE]             = (uint32 *)&gsDSPPStatusRegInfo;
      psMdpHwInfo->gpsModuleStatusRegInfo[HAL_MDP_MODULE_INTERFACE]                    = (uint32 *)NULL;
      psMdpHwInfo->gpsModuleStatusRegInfo[HAL_MDP_MODULE_CONTROL_PATH]                 = (uint32 *)NULL;
      psMdpHwInfo->gpsModuleStatusRegInfo[HAL_MDP_MODULE_DATA_PATH]                    = (uint32 *)NULL;
      psMdpHwInfo->gpsModuleStatusRegInfo[HAL_MDP_MODULE_SMP]                          = (uint32 *)NULL;
      psMdpHwInfo->gpsModuleStatusRegInfo[HAL_MDP_MODULE_TRAFFIC_SHAPER]               = (uint32 *)NULL;
      psMdpHwInfo->gpsModuleStatusRegInfo[HAL_MDP_MODULE_VBIF]                         = (uint32 *)NULL;
      psMdpHwInfo->gpsModuleStatusRegInfo[HAL_MDP_MODULE_PINGPONG]                     = (uint32 *)&gsPingPongStatusRegInfo;
      psMdpHwInfo->gpsModuleStatusRegInfo[HAL_MDP_MODULE_PHYSICAL_INTERFACE]           = (uint32 *)NULL;
      psMdpHwInfo->gpsModuleStatusRegInfo[HAL_MDP_MODULE_WRITEBACK_INTERFACE]          = (uint32 *)&gsWBStatusRegInfo;

      // Multi-rect paramters
      psMdpHwInfo->pMultiRectMappingTable                                              = gMultiRectMappingTable;
      psMdpHwInfo->uMaxParallelModeWidth                                               = HAL_MDP_9_0_0_MULTIRECT_PARALLEL_MAX_WIDTH;
      psMdpHwInfo->uMinTimeMultiplexModeLines                                          = HAL_MDP_9_0_0_MULTIRECT_TIMEMULTIPLEX_MIN_LINES;

      // UBWC Config
      psMdpHwInfo->sUBWCConfig.uHighestBankBit                                         = HAL_MDP_9_0_0_UBWC_DEFAULT_HIGHEST_BANK_BIT;
      psMdpHwInfo->sUBWCConfig.uMALSize                                                = HAL_MDP_9_0_0_UBWC_DEFAULT_MAL_SIZE;
      psMdpHwInfo->sUBWCConfig.uLvl1BankSwizzling                                      = HAL_MDP_9_0_0_UBWC_DEFAULT_LVL1_SWIZZLING_MODE;
      psMdpHwInfo->sUBWCConfig.uLvl2BankSwizzling                                      = HAL_MDP_9_0_0_UBWC_DEFAULT_LVL2_SWIZZLING_MODE;
      psMdpHwInfo->sUBWCConfig.uLvl3BankSwizzling                                      = HAL_MDP_9_0_0_UBWC_DEFAULT_LVL3_SWIZZLING_MODE;
      psMdpHwInfo->sUBWCConfig.uBankSpread                                             = HAL_MDP_9_0_0_UBWC_DEFAULT_BANK_SPREAD_MODE;
      psMdpHwInfo->sUBWCConfig.uMajorRevision                                          = HAL_MDP_9_0_0_UBWC_DEFAULT_MAJOR_REVISION;
      psMdpHwInfo->sUBWCConfig.uMinorRevision                                          = HAL_MDP_9_0_0_UBWC_DEFAULT_MINOR_REVISION;
      psMdpHwInfo->sUBWCConfig.uMaxDDRChannels                                         = HAL_MDP_9_0_0_UBWC_DEFAULT_MAX_DDR_CHANNELS;
      psMdpHwInfo->sUBWCConfig.uPredictionMode                                         = 1;  /* X=C */

      psMdpHwInfo->eMisrCfgMethod                                                      = HAL_MDP_MISR_CONFIG_METHOD_0;
      //DST PACK PATTERN
      psMdpHwInfo->pDstPackPatternInfo                                                 = (uint32 *)&guSrcUnpackInfo;

      psMdpHwInfo->eBWC                                                                = HAL_MDP_COMPRESSION_UBWC;
      psMdpHwInfo->eMacroTileFormat                                                    = HAL_MDP_MACRO_TILE_A5X;
   }
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_ReadHardwareInfo_8_1_0()
*/
/*!
* \brief
*     Reads the hardware capabilities for the given MDP Version(6.x.0)
*
* \param [out]  psHwInfo            - Hardware information
* \param [out]  psMdpHwInfo         - MDP hardware information
*
* \retval NONE
*
****************************************************************************/
void HAL_MDP_ReadHardwareInfo_8_1_0(HAL_MDP_HwInfo            *psHwInfo,
                                    HAL_MDP_Hw_Private_Info   *psMdpHwInfo)
{
  // Place holder for MDSS 8.1.0
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_ReadHardwareInfo_9_1_0()
*/
/*!
* \brief
*     Reads the hardware capabilities for the given MDP Version(6.x.0)
*
* \param [out]  psHwInfo            - Hardware information
* \param [out]  psMdpHwInfo         - MDP hardware information
*
* \retval NONE
*
****************************************************************************/
void HAL_MDP_ReadHardwareInfo_9_1_0(HAL_MDP_HwInfo            *psHwInfo,
                                    HAL_MDP_Hw_Private_Info   *psMdpHwInfo)
{
  // Place holder for MDSS 9.1.0
}

#ifdef __cplusplus
}
#endif
