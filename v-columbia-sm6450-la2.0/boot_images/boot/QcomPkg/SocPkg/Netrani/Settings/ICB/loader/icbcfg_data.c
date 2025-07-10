/*==============================================================================

FILE:      icbcfg_data.c

DESCRIPTION: This file implements the ICB Configuration driver.

PUBLIC CLASSES:  Not Applicable

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A

Edit History

$Header: //components/rel/core.boot/6.0/QcomPkg/SocPkg/Netrani/Settings/ICB/loader/icbcfg_data.c#6 $
$DateTime: 2023/01/21 20:41:56 $
$Author: pwbldsvc $
$Change: 42996466 $

When        Who    What, where, why
----------  ---    -----------------------------------------------------------
2021/05/28  sds    Update for r2
2021/05/07  sds    LLCC HSR v37
2020/05/15  sds    Created

                Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
                             All Rights Reserved.
                          QUALCOMM Proprietary/GTDR
==============================================================================*/
#include "icbcfg_hwio.h"
#include "../../../../../Library/ICBLib/icbcfgi.h"
#include "../../../Library/ICBTargetLib/icbcfg_hwio_target.h"

/*---------------------------------------------------------------------------*/
/*          Macro and constant definitions                                   */
/*---------------------------------------------------------------------------*/
//#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof((arr)[0]))

/*============================================================================
                        DEVICE CONFIG PROPERTY DATA
============================================================================*/

/*---------------------------------------------------------------------------*/
/*          Properties data for device ID  = "icbcfg/boot"                   */
/*---------------------------------------------------------------------------*/

/* ICBcfg Boot Configuration Data*/

/*---------------------------------------------------------------------------*/
/* NETRANI v1                                                                 */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Init Config Segments                                                      */
/*---------------------------------------------------------------------------*/
icbcfg_data_type icbcfg_qm_cfg_data_netrani_v1[] =
{
  /* Enable QM core cgc */
  ICBCFG_HWIO_DW(QM_CORE_CLK_CGC_CNTRL, 0x1),

  /* Stall timers */
  ICBCFG_HWIO_DW(QM_PRE_STALL_TIMEOUT_CNT_URG_0, 0x60),
  ICBCFG_HWIO_DW(QM_PRE_STALL_TIMEOUT_CNT_URG_1, 0x27),
  ICBCFG_HWIO_DW(QM_PRE_STALL_TIMEOUT_CNT_URG_2, 0x27),
  ICBCFG_HWIO_DW(QM_PRE_STALL_TIMEOUT_CNT_URG_3, 0x27),
  ICBCFG_HWIO_DW(QM_POST_STALL_TIMEOUT_CNT_URG_0, 0x60),
  ICBCFG_HWIO_DW(QM_POST_STALL_TIMEOUT_CNT_URG_1, 0x27),
  ICBCFG_HWIO_DW(QM_POST_STALL_TIMEOUT_CNT_URG_2, 0x27),
  ICBCFG_HWIO_DW(QM_POST_STALL_TIMEOUT_CNT_URG_3, 0x27),
  ICBCFG_HWIO_DW(QM_POST_STALL_WDW_OVERLAP_CNTL, 0x1),
  ICBCFG_HWIO_DW(QM_SMMU_INV_PRE_STALL_TIMEOUT_CNT_URG_0, 0x780),
  ICBCFG_HWIO_DW(QM_SMMU_INV_PRE_STALL_TIMEOUT_CNT_URG_1, 0x300),
  ICBCFG_HWIO_DW(QM_SMMU_INV_PRE_STALL_TIMEOUT_CNT_URG_2, 0x300),
  ICBCFG_HWIO_DW(QM_SMMU_INV_PRE_STALL_TIMEOUT_CNT_URG_3, 0x300),
  ICBCFG_HWIO_DW(QM_SMMU_INV_POST_STALL_WDW_OVERLAP_CNTL, 0x1),

  /* SAFE client overrides */
  ICBCFG_HWIO_DW(QM_DSP_SAFE_MASK_CNTRL, 0x3),
  ICBCFG_HWIO_DW(QM_SAFE_OVERRIDE_VALUE, 0x8),
  ICBCFG_HWIO_DW(QM_SAFE_OVERRIDE_EN,    0x8),

  ICBCFG_HWIO_DW(QM_DANGER_OVERRIDE_VALUE,    0x100),

	/* Titan RT */
  ICBCFG_HWIO_DW(QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_EN, 0x1),

  /* Titan Non-RT */
  ICBCFG_HWIO_DW(QM_CLNT_1_DANGER_AGGR_CNTRL, 0x3),
  ICBCFG_HWIOI_DW(QM_CLNT_1_THROTTLE_LEVEL_QOS_n, 4, 0xEE000004),
  ICBCFG_HWIOI_DW(QM_CLNT_1_THROTTLE_LEVEL_QOS_n, 6, 0xEE000006),
  ICBCFG_HWIO_DW(QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_EN, 0x1),

	/* Modem 5G */
  ICBCFG_HWIO_DW(QM_CLNT_2_DANGER_AGGR_CNTRL, 0x3),
  ICBCFG_HWIOI_DW(QM_CLNT_2_THROTTLE_LEVEL_QOS_n, 4, 0xEE000004),
  ICBCFG_HWIOI_DW(QM_CLNT_2_THROTTLE_LEVEL_QOS_n, 6, 0xEE000006),
  ICBCFG_HWIO_DW(QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_EN, 0x1),

	/* PCIe */
  ICBCFG_HWIO_DW(QM_CLNT_3_DANGER_AGGR_CNTRL, 0x3),
  ICBCFG_HWIOI_DW(QM_CLNT_3_THROTTLE_LEVEL_QOS_n, 4, 0xEE000004),
  ICBCFG_HWIOI_DW(QM_CLNT_3_THROTTLE_LEVEL_QOS_n, 6, 0xEE000006),
  ICBCFG_HWIO_DW(QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_EN, 0x1),

	/* SNOC/AgNoC */
  ICBCFG_HWIO_DW(QM_CLNT_4_DANGER_AGGR_CNTRL, 0x3),
  ICBCFG_HWIOI_DW(QM_CLNT_4_THROTTLE_LEVEL_QOS_n, 4, 0xEE000004),
  ICBCFG_HWIOI_DW(QM_CLNT_4_THROTTLE_LEVEL_QOS_n, 6, 0xEE000006),
  ICBCFG_HWIO_DW(QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_EN, 0x1),

	/* DPU NRT/SysTCU */
  ICBCFG_HWIO_DW(QM_CLNT_5_DANGER_AGGR_CNTRL, 0x3),
  ICBCFG_HWIOI_DW(QM_CLNT_5_THROTTLE_LEVEL_QOS_n, 4, 0xEE000004),
  ICBCFG_HWIOI_DW(QM_CLNT_5_THROTTLE_LEVEL_QOS_n, 6, 0xEE000006),
  ICBCFG_HWIO_DW(QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_EN, 0x1),

	/* IRIS VCodec/V-CPU */
  ICBCFG_HWIO_DW(QM_CLNT_6_DANGER_AGGR_CNTRL, 0x3),
  ICBCFG_HWIOI_DW(QM_CLNT_6_THROTTLE_LEVEL_QOS_n, 4, 0xEE000004),
  ICBCFG_HWIOI_DW(QM_CLNT_6_THROTTLE_LEVEL_QOS_n, 6, 0xEE000006),
  ICBCFG_HWIO_DW(QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_EN, 0x1),

	/* IRIS CVP/CV-CPU */
  ICBCFG_HWIO_DW(QM_CLNT_7_DANGER_AGGR_CNTRL, 0x3),
  ICBCFG_HWIOI_DW(QM_CLNT_7_THROTTLE_LEVEL_QOS_n, 4, 0xEE000004),
  ICBCFG_HWIOI_DW(QM_CLNT_7_THROTTLE_LEVEL_QOS_n, 6, 0xEE000006),
  ICBCFG_HWIO_DW(QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_EN, 0x1),

	/* GPU/GPUTCU */
  ICBCFG_HWIO_DW(QM_CLNT_8_DANGER_AGGR_CNTRL, 0x7),
  ICBCFG_HWIOI_DW(QM_CLNT_8_THROTTLE_LEVEL_QOS_n, 1, 0xEE000001),
  ICBCFG_HWIOI_DW(QM_CLNT_8_THROTTLE_LEVEL_QOS_n, 3, 0xEE000003),
  ICBCFG_HWIOI_DW(QM_CLNT_8_THROTTLE_LEVEL_QOS_n, 4, 0xEE000004),
  ICBCFG_HWIOI_DW(QM_CLNT_8_THROTTLE_LEVEL_QOS_n, 6, 0xEE000006),
  ICBCFG_HWIOI_DW(QM_CLNT_8_THROTTLE_LEVEL_QOS_n, 7, 0xAA000000),
  ICBCFG_HWIO_DW(QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_EN, 0x3),

	/* CPU */
  ICBCFG_HWIO_DW(QM_CLNT_9_DANGER_AGGR_CNTRL, 0x7),
  ICBCFG_HWIOI_DW(QM_CLNT_9_THROTTLE_LEVEL_QOS_n, 1, 0xEE000001),
  ICBCFG_HWIOI_DW(QM_CLNT_9_THROTTLE_LEVEL_QOS_n, 3, 0xEE000003),
  ICBCFG_HWIOI_DW(QM_CLNT_9_THROTTLE_LEVEL_QOS_n, 4, 0xEE000004),
  ICBCFG_HWIOI_DW(QM_CLNT_9_THROTTLE_LEVEL_QOS_n, 6, 0xEE000006),
  ICBCFG_HWIOI_DW(QM_CLNT_9_THROTTLE_LEVEL_QOS_n, 7, 0xAA000000),
  ICBCFG_HWIO_DW(QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_EN, 0x1),

	/* NSP/HCP/Audio-ML */
  ICBCFG_HWIO_DW(QM_DSP_DANGER_AGGR_CNTRL, 0x7),
  ICBCFG_HWIO_DW(QM_DSP_PRIORITY_MODE_SEL, 0x1),
  ICBCFG_HWIO_DW(QM_DSP_SYSTEM_DANGER_OUTPUT_EN, 0x1),
  ICBCFG_HWIOI_DW(QM_CLNT_10_THROTTLE_LEVEL_QOS_n, 1, 0xEE000001),
  ICBCFG_HWIOI_DW(QM_CLNT_10_THROTTLE_LEVEL_QOS_n, 3, 0xEE000003),
  ICBCFG_HWIOI_DW(QM_CLNT_10_THROTTLE_LEVEL_QOS_n, 4, 0xEE000004),
  ICBCFG_HWIOI_DW(QM_CLNT_10_THROTTLE_LEVEL_QOS_n, 6, 0xEE000006),
  ICBCFG_HWIOI_DW(QM_CLNT_10_THROTTLE_LEVEL_QOS_n, 7, 0xAA000000),
  ICBCFG_HWIO_DW(QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_EN, 0x3),

  /* Throttle level generation */
  ICBCFG_HWIO_DW(QM_THROTTLE_LEVEL_LEGACY_SELECT, 0x0),
  ICBCFG_HWIOI_DW(QM_THROTTLE_LEVEL_QOS_n, 7, 0x7FC),
  ICBCFG_HWIOF_READ_DW(MCCC_CLK_PERIOD,PERIOD),
  ICBCFG_HWIOF_WRITE_DW(QM_PERIOD_BUS_CFG,PERIOD_BUS_SW),
  ICBCFG_HWIOF_DW(QM_PERIOD_BUS_CFG, PERIOD_BUS_LOAD_SW, 0x1),
  ICBCFG_HWIOF_DW(QM_PERIOD_BUS_CFG, PERIOD_BUS_SW_OVERRIDE, 0x0),
  ICBCFG_HWIOI_DW(QOS_FREQ_BAND_BNDRY_n, 0, 0x97B),
  ICBCFG_HWIO_DW(QM_DANGER_SAFE_CNTRL,0x1),

  /* AP throttles and shapers */
  ICBCFG_HWIOF_DW(APP0_BWMON_THROTTLE_0_CGC_CNTRL, THROTTLE_CGC_EN, 0x1),
  ICBCFG_HWIOF_DW(APP0_BWMON_THROTTLE_0_GRANT_PERIOD, GRANT_PERIOD, 0x3e8),
  ICBCFG_HWIO_DW(APP0_BWMON_THROTTLE_0_THRESHOLD_03, 0xFFFF07D0),
  ICBCFG_HWIO_DW(APP0_BWMON_THROTTLE_0_THRESHOLD_02, 0xFFFF0064),
  ICBCFG_HWIO_DW(APP0_BWMON_THROTTLE_0_THRESHOLD_01, 0x0064FFFF),
  ICBCFG_HWIO_DW(APP0_BWMON_THROTTLE_0_THRESHOLD_00, 0x00000064),
  ICBCFG_HWIOF_DW(APP0_BWMON_THROTTLE_0_PEAK_ACCUM_CREDIT, PEAK_ACCUM_CREDIT, 0x100),
  ICBCFG_HWIO_DW(APP0_BWMON_THROTTLE_0_CNTRL, 0xDE01),


  /* GPU throttles and shapers */
  ICBCFG_HWIOF_DW(GPU_BWMON_THROTTLE_0_CGC_CNTRL, THROTTLE_CGC_EN, 0x1),
  ICBCFG_HWIOF_DW(GPU_BWMON_THROTTLE_0_GRANT_PERIOD, GRANT_PERIOD, 0x3e8),
  ICBCFG_HWIO_DW(GPU_BWMON_THROTTLE_0_THRESHOLD_03, 0xFFFF03E8),
  ICBCFG_HWIO_DW(GPU_BWMON_THROTTLE_0_THRESHOLD_02, 0xFFFF0032),
  ICBCFG_HWIO_DW(GPU_BWMON_THROTTLE_0_THRESHOLD_01, 0x0000FFFF),
  ICBCFG_HWIO_DW(GPU_BWMON_THROTTLE_0_THRESHOLD_00, 0x0000FFFF),
  ICBCFG_HWIOF_DW(GPU_BWMON_THROTTLE_0_PEAK_ACCUM_CREDIT, PEAK_ACCUM_CREDIT, 0x100),
  ICBCFG_HWIO_DW(GPU_BWMON_THROTTLE_0_CNTRL, 0x5E01),

  ICBCFG_HWIOF_DW(GPU_BWMON_THROTTLE_1_CGC_CNTRL, THROTTLE_CGC_EN, 0x1),
  ICBCFG_HWIOF_DW(GPU_BWMON_THROTTLE_1_GRANT_PERIOD, GRANT_PERIOD, 0x3e8),
  ICBCFG_HWIO_DW(GPU_BWMON_THROTTLE_1_THRESHOLD_03, 0xFFFF03E8),
  ICBCFG_HWIO_DW(GPU_BWMON_THROTTLE_1_THRESHOLD_02, 0xFFFF0032),
  ICBCFG_HWIO_DW(GPU_BWMON_THROTTLE_1_THRESHOLD_01, 0x0000FFFF),
  ICBCFG_HWIO_DW(GPU_BWMON_THROTTLE_1_THRESHOLD_00, 0x0000FFFF),
  ICBCFG_HWIOF_DW(GPU_BWMON_THROTTLE_1_PEAK_ACCUM_CREDIT, PEAK_ACCUM_CREDIT, 0x100),
  ICBCFG_HWIO_DW(GPU_BWMON_THROTTLE_1_CNTRL, 0x5E01),
  
  /* CDSP throttles and shapers */
  ICBCFG_HWIOF_DW(CDSP_BWMON_THROTTLE_0_CGC_CNTRL, THROTTLE_CGC_EN, 0x1),
  ICBCFG_HWIOF_DW(CDSP_BWMON_THROTTLE_0_GRANT_PERIOD, GRANT_PERIOD, 0x3e8),
  ICBCFG_HWIO_DW(CDSP_BWMON_THROTTLE_0_THRESHOLD_03, 0xFFFF03E8),
  ICBCFG_HWIO_DW(CDSP_BWMON_THROTTLE_0_THRESHOLD_02, 0xFFFF0032),
  ICBCFG_HWIO_DW(CDSP_BWMON_THROTTLE_0_THRESHOLD_01, 0x0000FFFF),
  ICBCFG_HWIO_DW(CDSP_BWMON_THROTTLE_0_THRESHOLD_00, 0x0000FFFF),
  ICBCFG_HWIOF_DW(CDSP_BWMON_THROTTLE_0_PEAK_ACCUM_CREDIT, PEAK_ACCUM_CREDIT, 0x100),
  ICBCFG_HWIO_DW(CDSP_BWMON_THROTTLE_0_CNTRL, 0x5E01),
  
  ICBCFG_HWIOF_DW(CDSP_BWMON_THROTTLE_1_CGC_CNTRL, THROTTLE_CGC_EN, 0x1),
  ICBCFG_HWIOF_DW(CDSP_BWMON_THROTTLE_1_GRANT_PERIOD, GRANT_PERIOD, 0x3e8),
  ICBCFG_HWIO_DW(CDSP_BWMON_THROTTLE_1_THRESHOLD_03, 0xFFFF03E8),
  ICBCFG_HWIO_DW(CDSP_BWMON_THROTTLE_1_THRESHOLD_02, 0xFFFF0032),
  ICBCFG_HWIO_DW(CDSP_BWMON_THROTTLE_1_THRESHOLD_01, 0x0000FFFF),
  ICBCFG_HWIO_DW(CDSP_BWMON_THROTTLE_1_THRESHOLD_00, 0x0000FFFF),
  ICBCFG_HWIOF_DW(CDSP_BWMON_THROTTLE_1_PEAK_ACCUM_CREDIT, PEAK_ACCUM_CREDIT, 0x100),
  ICBCFG_HWIO_DW(CDSP_BWMON_THROTTLE_1_CNTRL, 0x5E01),
  
    /* SNOC throttle and shaper */
  ICBCFG_HWIOF_DW(SNOC_THROTTLE_THROTTLE_0_CGC_CNTRL, THROTTLE_CGC_EN, 0x1),
  ICBCFG_HWIOF_DW(SNOC_THROTTLE_THROTTLE_0_GRANT_PERIOD, GRANT_PERIOD, 0x3e8),
  ICBCFG_HWIO_DW(SNOC_THROTTLE_THROTTLE_0_THRESHOLD_03, 0xFFFF),
  ICBCFG_HWIO_DW(SNOC_THROTTLE_THROTTLE_0_THRESHOLD_02, 0xFFFFFFFF),
  ICBCFG_HWIO_DW(SNOC_THROTTLE_THROTTLE_0_THRESHOLD_01, 0x0000FFFF),
  ICBCFG_HWIO_DW(SNOC_THROTTLE_THROTTLE_0_THRESHOLD_00, 0x0000FFFF),
  ICBCFG_HWIOF_DW(SNOC_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT, PEAK_ACCUM_CREDIT, 0x100),
  ICBCFG_HWIO_DW(SNOC_THROTTLE_THROTTLE_0_CNTRL, 0x5001),
  #if 0
    /* WPSS throttle and shaper */
  ICBCFG_HWIOF_DW(GCC_WPSS_THROTTLE_AHB_CBCR, CLK_ENABLE, 0x1),
  ICBCFG_WAIT_HWIOF_DW(GCC_WPSS_THROTTLE_AHB_CBCR, CLK_OFF, 0x0),
  ICBCFG_HWIOF_DW(WLAN_Q6_THROTTLE_THROTTLE_0_CGC_CNTRL, THROTTLE_CGC_EN, 0x1),
  ICBCFG_HWIOF_DW(WLAN_Q6_THROTTLE_THROTTLE_0_GRANT_PERIOD, GRANT_PERIOD, 0x3e8),
  ICBCFG_HWIO_DW(WLAN_Q6_THROTTLE_THROTTLE_0_THRESHOLD_03, 0xFFFF),
  ICBCFG_HWIO_DW(WLAN_Q6_THROTTLE_THROTTLE_0_THRESHOLD_02, 0xFFFFFFFF),
  ICBCFG_HWIO_DW(WLAN_Q6_THROTTLE_THROTTLE_0_THRESHOLD_01, 0x0000FFFF),
  ICBCFG_HWIO_DW(WLAN_Q6_THROTTLE_THROTTLE_0_THRESHOLD_00, 0x0000FFFF),
  ICBCFG_HWIOF_DW(WLAN_Q6_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT, PEAK_ACCUM_CREDIT, 0x100),
  ICBCFG_HWIO_DW(WLAN_Q6_THROTTLE_THROTTLE_0_CNTRL, 0x5001),
  ICBCFG_HWIOF_DW(GCC_WPSS_THROTTLE_AHB_CBCR, CLK_ENABLE, 0x0),
#endif
   /* ANOC throttle and shaper */
  ICBCFG_HWIOF_DW(ANOC_THROTTLE_THROTTLE_0_CGC_CNTRL, THROTTLE_CGC_EN, 0x1),
  ICBCFG_HWIOF_DW(ANOC_THROTTLE_THROTTLE_0_GRANT_PERIOD, GRANT_PERIOD, 0x3e8),
  ICBCFG_HWIO_DW(ANOC_THROTTLE_THROTTLE_0_THRESHOLD_03, 0xFFFF),
  ICBCFG_HWIO_DW(ANOC_THROTTLE_THROTTLE_0_THRESHOLD_02, 0xFFFFFFFF),
  ICBCFG_HWIO_DW(ANOC_THROTTLE_THROTTLE_0_THRESHOLD_01, 0x0000FFFF),
  ICBCFG_HWIO_DW(ANOC_THROTTLE_THROTTLE_0_THRESHOLD_00, 0x0000FFFF),
  ICBCFG_HWIOF_DW(ANOC_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT, PEAK_ACCUM_CREDIT, 0x100),
  ICBCFG_HWIO_DW(ANOC_THROTTLE_THROTTLE_0_CNTRL, 0x5001),

  ICBCFG_HWIOF_DW(ANOC_THROTTLE_THROTTLE_1_CGC_CNTRL, THROTTLE_CGC_EN, 0x1),
  ICBCFG_HWIOF_DW(ANOC_THROTTLE_THROTTLE_1_GRANT_PERIOD, GRANT_PERIOD, 0x3e8),
  ICBCFG_HWIO_DW(ANOC_THROTTLE_THROTTLE_1_THRESHOLD_03, 0xFFFF),
  ICBCFG_HWIO_DW(ANOC_THROTTLE_THROTTLE_1_THRESHOLD_02, 0xFFFFFFFF),
  ICBCFG_HWIO_DW(ANOC_THROTTLE_THROTTLE_1_THRESHOLD_01, 0x0000FFFF),
  ICBCFG_HWIO_DW(ANOC_THROTTLE_THROTTLE_1_THRESHOLD_00, 0x0000FFFF),
  ICBCFG_HWIOF_DW(ANOC_THROTTLE_THROTTLE_1_PEAK_ACCUM_CREDIT, PEAK_ACCUM_CREDIT, 0x100),
  ICBCFG_HWIO_DW(ANOC_THROTTLE_THROTTLE_1_CNTRL, 0x5001),

  /* GPU TCU throttle and shaper */
  ICBCFG_HWIOF_DW(GCC_QMIP_GPU_AHB_CBCR, CLK_ENABLE, 0x1),
  ICBCFG_WAIT_HWIOF_DW(GCC_QMIP_GPU_AHB_CBCR, CLK_OFF, 0x0),
  ICBCFG_HWIOF_DW(GPU_TCU_THROTTLE_THROTTLE_0_CGC_CNTRL, THROTTLE_CGC_EN, 0x1),
  ICBCFG_HWIOF_DW(GPU_TCU_THROTTLE_THROTTLE_0_GRANT_PERIOD, GRANT_PERIOD, 0x3e8),
  ICBCFG_HWIO_DW(GPU_TCU_THROTTLE_THROTTLE_0_THRESHOLD_03, 0xFFFF),
  ICBCFG_HWIO_DW(GPU_TCU_THROTTLE_THROTTLE_0_THRESHOLD_02, 0xFFFFFFFF),
  ICBCFG_HWIO_DW(GPU_TCU_THROTTLE_THROTTLE_0_THRESHOLD_01, 0x0000FFFF),
  ICBCFG_HWIO_DW(GPU_TCU_THROTTLE_THROTTLE_0_THRESHOLD_00, 0x0000FFFF),
  ICBCFG_HWIOF_DW(GPU_TCU_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT, PEAK_ACCUM_CREDIT, 0x100),
  ICBCFG_HWIO_DW(GPU_TCU_THROTTLE_THROTTLE_0_CNTRL, 0x5001),
  ICBCFG_HWIOF_DW(GCC_QMIP_GPU_AHB_CBCR, CLK_ENABLE, 0x0),
  
  /* LPASS throttle and shaper */
  ICBCFG_HWIOF_DW(GCC_QMIP_LPASS_TBU_AHB_CBCR, CLK_ENABLE, 0x1),
  ICBCFG_WAIT_HWIOF_DW(GCC_QMIP_LPASS_TBU_AHB_CBCR, CLK_OFF, 0x0),
  ICBCFG_HWIOF_DW(LPASS_THROTTLE_THROTTLE_0_CGC_CNTRL, THROTTLE_CGC_EN, 0x1),
  ICBCFG_HWIOF_DW(LPASS_THROTTLE_THROTTLE_0_GRANT_PERIOD, GRANT_PERIOD, 0x3e8),
  ICBCFG_HWIO_DW(LPASS_THROTTLE_THROTTLE_0_THRESHOLD_03, 0xFFFF),
  ICBCFG_HWIO_DW(LPASS_THROTTLE_THROTTLE_0_THRESHOLD_02, 0xFFFFFFFF),
  ICBCFG_HWIO_DW(LPASS_THROTTLE_THROTTLE_0_THRESHOLD_01, 0x0000FFFF),
  ICBCFG_HWIO_DW(LPASS_THROTTLE_THROTTLE_0_THRESHOLD_00, 0x0000FFFF),
  ICBCFG_HWIOF_DW(LPASS_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT, PEAK_ACCUM_CREDIT, 0x100),
  ICBCFG_HWIO_DW(LPASS_THROTTLE_THROTTLE_0_CNTRL, 0x5001),
  ICBCFG_HWIOF_DW(GCC_QMIP_LPASS_TBU_AHB_CBCR, CLK_ENABLE, 0x0),
 
};

icbcfg_prop_seg_type icbcfg_qm_cfg_seg_netrani_v1 = 
{
  /* Length of the config  data array */
  ARRAY_SIZE(icbcfg_qm_cfg_data_netrani_v1),
  /* Pointer to config data array */ 
  icbcfg_qm_cfg_data_netrani_v1                                    
};

/*---------------------------------------------------------------------------*/
/* Init Config Segment list                                                  */
/*---------------------------------------------------------------------------*/
icbcfg_prop_seg_type *icbcfg_boot_segs_netrani_v1[] =
{
  &icbcfg_qm_cfg_seg_netrani_v1,
};

icbcfg_prop_type icbcfg_boot_prop_netrani_v1 =
{
  /* Length of the config  data array */
  ARRAY_SIZE(icbcfg_boot_segs_netrani_v1),
  /* Pointer to config data array */
  icbcfg_boot_segs_netrani_v1
};

/*---------------------------------------------------------------------------*/
/* PostInit Config Segments                                                  */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* GEMNOC Config Segment                                                     */
/*---------------------------------------------------------------------------*/
icbcfg_data_type icbcfg_gemnoc_cfg_data_netrani_v1[] =
{
  ICBCFG_DEFAULT(),
};

icbcfg_prop_seg_type icbcfg_gemnoc_cfg_seg_netrani_v1 =
{
  /* Length of the config  data array */
  ARRAY_SIZE(icbcfg_gemnoc_cfg_data_netrani_v1),
  /* Pointer to config data array */
  icbcfg_gemnoc_cfg_data_netrani_v1
};

/*---------------------------------------------------------------------------*/
/* LLCC Config Segment                                                       */
/*---------------------------------------------------------------------------*/
icbcfg_data_type icbcfg_llcc_cfg_data_netrani_v1[] =
{
  ICBCFG_HWIO_DW(MC_BROADCAST_ANDMC_COMMON_ISU_BEAC_HMSSSELFAUTH_LOCK, 0x1),
  ICBCFG_HWIO_DW(MC_BROADCAST_ANDMC_COMMON_ISU_BEAC_HPROTNS_LOCK,      0x1),
  ICBCFG_HWIO_DW(MC_BROADCAST_ANDMC_COMMON_ISU_BEAC_HSECUREPROC_LOCK,  0x1),
  ICBCFG_HWIO_DW(MC_BROADCAST_ANDMC_COMMON_ISU_BEAC_HTMEROM_LOCK,  0x1),
  ICBCFG_HWIO_DW(MC_BROADCAST_ANDMC_COMMON_ISU_BEAC_HTMEFW_LOCK,  0x1),
  
  ICBCFG_HWIO_DW(MC_BROADCAST_ORMC_COMMON_ISU_LOAD_CONFIG,  0x1),
};

icbcfg_prop_seg_type icbcfg_llcc_cfg_seg_netrani_v1 =
{
  /* Length of the config  data array */
  ARRAY_SIZE(icbcfg_llcc_cfg_data_netrani_v1),
  /* Pointer to config data array */
  icbcfg_llcc_cfg_data_netrani_v1
};

/*---------------------------------------------------------------------------*/
/* LLCC Config Segment                                                       */
/*---------------------------------------------------------------------------*/
icbcfg_data_type icbcfg_wa_data_netrani_v1[] =
{
#if 0
  /* QCTDD07436397: Disable ECO for GPU. */
  ICBCFG_HWIO_DW(GEM_NOC_SW_CGC_DISABLE_SBM_FLAGOUTSET0_LOW, 0x1),
#endif
  /*Diable DVM*/
  ICBCFG_HWIOF_DW(GEM_NOC_FENCINGCTL_TARGET0_LOW, HWEN, 0x0),
  ICBCFG_HWIOF_DW(GEM_NOC_FENCINGCTL_TARGET1_LOW, HWEN, 0x0),
};

icbcfg_prop_seg_type icbcfg_wa_seg_netrani_v1 =
{
  /* Length of the config  data array */
  ARRAY_SIZE(icbcfg_wa_data_netrani_v1),
  /* Pointer to config data array */
  icbcfg_wa_data_netrani_v1
};

/*---------------------------------------------------------------------------*/
/* PostInit Config Segment list                                              */
/*---------------------------------------------------------------------------*/
icbcfg_prop_seg_type *icbcfg_post_boot_segs_netrani_v1[] =
{
  &icbcfg_gemnoc_cfg_seg_netrani_v1,
  &icbcfg_llcc_cfg_seg_netrani_v1,
  &icbcfg_wa_seg_netrani_v1,
};

icbcfg_prop_type icbcfg_post_prop_netrani_v1 =
{
  /* Length of the config  data array */
  ARRAY_SIZE(icbcfg_post_boot_segs_netrani_v1),
  /* Pointer to config data array */
  icbcfg_post_boot_segs_netrani_v1
};

icbcfg_mem_region_type map_ddr_regions_netrani_v1[] =
{
  { 0x080000000ULL, 0x100000000ULL },
  { 0x800000000ULL, 0x1000000000ULL },
};

/* Translation block base addresses. */
uint8 *trans_bases_netrani_v1[] =
{
  (uint8 *)HWIO_ADDR(MC0_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG),
  (uint8 *)HWIO_ADDR(MC1_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG),
};

icbcfg_device_config_type netrani_v1 =
{
  /* Chip version information for this device data. */
  CHIPINFO_FAMILY_NETRANI,      /**< Chip family */
  false,                       /**< Exact match for version? */
  0,                           /**< Chip version */

  /* Device information. */
  ARRAY_SIZE(map_ddr_regions_netrani_v1), /**< Number of regions in the DDR map */
  map_ddr_regions_netrani_v1,             /**< Array of mappable DDR regions */
  6,                                     /**< Number of mapping segments. */
  2,                                     /**< Number of channels. */
  36,                                    /**< Address width in bits. */
  ICBCFG_ADDR_TRANS_MC,                /**< Address translator hardware type. */
  trans_bases_netrani_v1,                 /**< Translation block base addresses. */

  /* Prop lists. */
  &icbcfg_boot_prop_netrani_v1,           /**< Init time prop list. */
  &icbcfg_post_prop_netrani_v1,           /**< Post-init time prop list. */
};

/*---------------------------------------------------------------------------*/
/* TARGET LIST                                                               */
/*---------------------------------------------------------------------------*/
icbcfg_device_config_type *configs_netrani[] =
{
  &netrani_v1,
};

/*---------------------------------------------------------------------------*/
/* EXPORTED TARGET DEFINITION                                                */
/*---------------------------------------------------------------------------*/
icbcfg_info_type icbcfg_info =
{
  ARRAY_SIZE(configs_netrani),
  configs_netrani,
};
