/*==============================================================================

FILE:      icbcfg_data.c

DESCRIPTION: This file implements the ICB Configuration driver.

PUBLIC CLASSES:  Not Applicable

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A

Edit History

$Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Kailua/Settings/ICB/loader/icbcfg_data.c#2 $
$DateTime: 2022/10/17 15:26:32 $
$Author: pwbldsvc $
$Change: 40340147 $

When        Who    What, where, why
----------  ---    -----------------------------------------------------------
2022/10/17  sds    LLCC HSR v36
2021/05/17  sds    Created
2021/08/03  bc     Updated to HSR v12
2022/15/04  as     Updated QMIP

                Copyright (c) 2022 Qualcomm Technologies, Inc.
                             All Rights Reserved.
                          QUALCOMM Proprietary/GTDR
==============================================================================*/
#include "icbcfg_hwio.h"
#include "icbcfg_hwio_target.h"
#include "../../../../../Library/ICBLib/icbcfgi.h"

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
/* KAILUA v1                                                                 */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* EarlyInit Config Segments                                                 */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* ARCG Config Segment                                                       */
/*---------------------------------------------------------------------------*/
icbcfg_data_type icbcfg_arcg_cfg_data_kailua_v1[] =
{
  /* CNOC_MAIN */
	ICBCFG_HWIO_DW(CNOC_CNOC_MAIN_CNOC_MAIN_CSRUNIT_CSRUNIT_RCG_CNOC_CENTER_SF_QX_CLK_FORCECLKON_LOW, 0x1),
	ICBCFG_HWIO_DW(CNOC_CNOC_MAIN_CNOC_MAIN_CSRUNIT_CSRUNIT_RCG_CNOC_NORTH_SF_QX_CLK_FORCECLKON_LOW, 0x1),
	ICBCFG_HWIO_DW(CNOC_CNOC_MAIN_CNOC_CENTER_SF_QX_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0x100),
	ICBCFG_HWIO_DW(CNOC_CNOC_MAIN_CNOC_NORTH_SF_QX_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0x100),
  ICBCFG_HWIO_DW(CNOC_CNOC_MAIN_CNOC_MAIN_RCG_ENABLE_SBM_FLAGOUTSET0_LOW, 0x00000003),
	ICBCFG_HWIO_DW(CNOC_CNOC_MAIN_CNOC_MAIN_CSRUNIT_CSRUNIT_RCG_CNOC_CENTER_SF_QX_CLK_FORCECLKON_LOW, 0x0),
	ICBCFG_HWIO_DW(CNOC_CNOC_MAIN_CNOC_MAIN_CSRUNIT_CSRUNIT_RCG_CNOC_NORTH_SF_QX_CLK_FORCECLKON_LOW, 0x0),

  ICBCFG_HWIO_DW(CNOC_CNOC_MAIN_CSRUNIT_CSRUNIT_SLAVE_RCG_QHS_AOSS_LOW, 0x00000001),
  ICBCFG_HWIO_DW(CNOC_CNOC_MAIN_CSRUNIT_CSRUNIT_SLAVE_RCG_XS_PCIE_0_LOW, 0x00000009),
  ICBCFG_HWIO_DW(CNOC_CNOC_MAIN_CSRUNIT_CSRUNIT_SLAVE_RCG_XS_PCIE_1_LOW, 0x00000009),

	/* CNOC_CFG */
  ICBCFG_HWIO_DW(CNOC_CNOC_CFG_CSRUNIT_RCG_CSRUNIT_SLAVE_RCG_QHS0_CENTER_LOW, 0x00000001),
  ICBCFG_HWIO_DW(CNOC_CNOC_CFG_CSRUNIT_RCG_CSRUNIT_SLAVE_RCG_QHS0_MMNOC_LOW, 0x0000000F),
  ICBCFG_HWIO_DW(CNOC_CNOC_CFG_CSRUNIT_RCG_CSRUNIT_SLAVE_RCG_QHS0_NORTH_LOW, 0x0000081E),
  ICBCFG_HWIO_DW(CNOC_CNOC_CFG_CSRUNIT_RCG_CSRUNIT_SLAVE_RCG_QHS0_SOUTH_LOW, 0x00000007),
  ICBCFG_HWIO_DW(CNOC_CNOC_CFG_CSRUNIT_RCG_CSRUNIT_SLAVE_RCG_QHS0_WEST_LOW, 0x00000007),
  ICBCFG_HWIO_DW(CNOC_CNOC_CFG_CSRUNIT_RCG_CSRUNIT_SLAVE_RCG_QHS1_CENTER_LOW, 0x0000007F),
  ICBCFG_HWIO_DW(CNOC_CNOC_CFG_CSRUNIT_RCG_CSRUNIT_SLAVE_RCG_QHS_AHB2PHY1_LOW, 0x00000001),
  ICBCFG_HWIO_DW(CNOC_CNOC_CFG_CSRUNIT_RCG_CSRUNIT_SLAVE_RCG_QHS_GPUSS_CFG_LOW, 0x00000001),
  ICBCFG_HWIO_DW(CNOC_CNOC_CFG_CSRUNIT_RCG_CSRUNIT_SLAVE_RCG_QHS_MSS_CFG_LOW, 0x00000001),
  ICBCFG_HWIO_DW(CNOC_CNOC_CFG_CSRUNIT_RCG_CSRUNIT_SLAVE_RCG_QHS_PDM_LOW, 0x00000001),
  ICBCFG_HWIO_DW(CNOC_CNOC_CFG_CSRUNIT_RCG_CSRUNIT_SLAVE_RCG_QSS0_CENTER_LOW, 0x0000001F),
  ICBCFG_HWIO_DW(CNOC_CNOC_CFG_CSRUNIT_RCG_CSRUNIT_SLAVE_RCG_QSS0_EAST_LOW, 0x00000003),
  ICBCFG_HWIO_DW(CNOC_CNOC_CFG_CSRUNIT_RCG_CSRUNIT_SLAVE_RCG_QSS0_MMNOC_LOW, 0x0000007F),
  ICBCFG_HWIO_DW(CNOC_CNOC_CFG_CSRUNIT_RCG_CSRUNIT_SLAVE_RCG_QSS_PCIE_THROTTLE_CFG_LOW, 0x00000001),
  ICBCFG_HWIO_DW(CNOC_CNOC_CFG_CSRUNIT_RCG_CSRUNIT_SLAVE_RCG_XS_SYS_TCU_CFG_LOW, 0x00000001),
};

icbcfg_prop_seg_type icbcfg_arcg_cfg_seg_kailua_v1 =
{
  /* Length of the config  data array */
  ARRAY_SIZE(icbcfg_arcg_cfg_data_kailua_v1),
  /* Pointer to config data array */
  icbcfg_arcg_cfg_data_kailua_v1
};

/*---------------------------------------------------------------------------*/
/* EarlyInit Config Segment list                                             */
/*---------------------------------------------------------------------------*/
icbcfg_prop_seg_type *icbcfg_early_init_segs_kailua_v1[] =
{
  &icbcfg_arcg_cfg_seg_kailua_v1,
};

icbcfg_prop_type icbcfg_early_prop_kailua_v1 =
{
  /* Length of the config  data array */
  ARRAY_SIZE(icbcfg_early_init_segs_kailua_v1),
  /* Pointer to config data array */
  icbcfg_early_init_segs_kailua_v1
};

/*---------------------------------------------------------------------------*/
/* Init Config Segments                                                      */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* QM Config Segment                                                         */
/*---------------------------------------------------------------------------*/
icbcfg_data_type icbcfg_qm_cfg_data_kailua_v1[] =
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

  /* Titan RT, Modem 5G*/
  ICBCFG_HWIO_DW(QM_CLNT_0_DANGER_AGGR_CNTRL, 0x3),
  ICBCFG_HWIOI_DW(QM_CLNT_0_THROTTLE_LEVEL_QOS_n, 4, 0xEE000004),
  ICBCFG_HWIOI_DW(QM_CLNT_0_THROTTLE_LEVEL_QOS_n, 6, 0xEE000006),
  ICBCFG_HWIO_DW(QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_EN, 0x1),

  /* Titan Non-RT */
  ICBCFG_HWIO_DW(QM_CLNT_1_DANGER_AGGR_CNTRL, 0x3),
  ICBCFG_HWIOI_DW(QM_CLNT_1_THROTTLE_LEVEL_QOS_n, 4, 0xEE000004),
  ICBCFG_HWIOI_DW(QM_CLNT_1_THROTTLE_LEVEL_QOS_n, 6, 0xEE000006),
  ICBCFG_HWIO_DW(QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_EN, 0x1),

  /* AML0 */
  ICBCFG_HWIO_DW(QM_CLNT_2_DANGER_AGGR_CNTRL, 0x3),
  ICBCFG_HWIOI_DW(QM_CLNT_2_THROTTLE_LEVEL_QOS_n, 7, 0xEE000003),
  ICBCFG_HWIO_DW(QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_EN, 0x3),
 
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
 
	/* AML1 */
  ICBCFG_HWIO_DW(QM_CLNT_5_DANGER_AGGR_CNTRL, 0x3),
  ICBCFG_HWIOI_DW(QM_CLNT_5_THROTTLE_LEVEL_QOS_n, 7, 0xEE000003),
  ICBCFG_HWIO_DW(QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_EN, 0x3),
 
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
  ICBCFG_HWIO_DW(QM_CLNT_8_DANGER_AGGR_CNTRL, 0x3),
  ICBCFG_HWIO_DW(QM_CLNT_8_DANGER_AGGR_MODEM_CNTRL, 0x1),
  ICBCFG_HWIOI_DW(QM_CLNT_8_THROTTLE_LEVEL_QOS_n, 2, 0xEE000002),
  ICBCFG_HWIOI_DW(QM_CLNT_8_THROTTLE_LEVEL_QOS_n, 3, 0xEE000003),
  ICBCFG_HWIOI_DW(QM_CLNT_8_THROTTLE_LEVEL_QOS_n, 4, 0xEE000004),
  ICBCFG_HWIOI_DW(QM_CLNT_8_THROTTLE_LEVEL_QOS_n, 6, 0xEE000006),
  ICBCFG_HWIOI_DW(QM_CLNT_8_THROTTLE_LEVEL_QOS_n, 7, 0xAA000000),
  ICBCFG_HWIO_DW(QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_EN, 0x3),
 
	/* CPU */
  ICBCFG_HWIO_DW(QM_CLNT_9_DANGER_AGGR_CNTRL, 0x3),
  ICBCFG_HWIO_DW(QM_CLNT_9_DANGER_AGGR_MODEM_CNTRL, 0x1),
  ICBCFG_HWIOI_DW(QM_CLNT_9_THROTTLE_LEVEL_QOS_n, 2, 0xEE000002),
  ICBCFG_HWIOI_DW(QM_CLNT_9_THROTTLE_LEVEL_QOS_n, 3, 0xEE000003),
  ICBCFG_HWIOI_DW(QM_CLNT_9_THROTTLE_LEVEL_QOS_n, 4, 0xEE000004),
  ICBCFG_HWIOI_DW(QM_CLNT_9_THROTTLE_LEVEL_QOS_n, 6, 0xEE000006),
  ICBCFG_HWIOI_DW(QM_CLNT_9_THROTTLE_LEVEL_QOS_n, 7, 0xAA000000),
  ICBCFG_HWIO_DW(QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_EN, 0x1),
 
	/* NSP/HCP/Audio-ML */
  ICBCFG_HWIO_DW(QM_DSP_DANGER_AGGR_CNTRL, 0x3),
  ICBCFG_HWIO_DW(QM_DSP_PRIORITY_MODE_SEL, 0x1),
  ICBCFG_HWIO_DW(QM_DSP_SYSTEM_DANGER_OUTPUT_EN, 0x1),
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
  ICBCFG_HWIOF_DW(APP_BWMON_THROTTLE_0_CGC_CNTRL, THROTTLE_CGC_EN, 0x1),
  ICBCFG_HWIOF_DW(APP_BWMON_THROTTLE_0_GRANT_PERIOD, GRANT_PERIOD, 0x3e8),
  ICBCFG_HWIO_DW(APP_BWMON_THROTTLE_0_THRESHOLD_03, 0x0000FFFF),
  ICBCFG_HWIO_DW(APP_BWMON_THROTTLE_0_THRESHOLD_02, 0x03E80032),
  ICBCFG_HWIO_DW(APP_BWMON_THROTTLE_0_THRESHOLD_01, 0x0032FFFF),
  ICBCFG_HWIO_DW(APP_BWMON_THROTTLE_0_THRESHOLD_00, 0x00000032),
  ICBCFG_HWIOF_DW(APP_BWMON_THROTTLE_0_PEAK_ACCUM_CREDIT, PEAK_ACCUM_CREDIT, 0x100),
  ICBCFG_HWIO_DW(APP_BWMON_THROTTLE_0_CNTRL, 0xDC01),
 
  ICBCFG_HWIOF_DW(APP_BWMON_THROTTLE_1_CGC_CNTRL, THROTTLE_CGC_EN, 0x1),
  ICBCFG_HWIOF_DW(APP_BWMON_THROTTLE_1_GRANT_PERIOD, GRANT_PERIOD, 0x3e8),
  ICBCFG_HWIO_DW(APP_BWMON_THROTTLE_1_THRESHOLD_03, 0x0000FFFF),
  ICBCFG_HWIO_DW(APP_BWMON_THROTTLE_1_THRESHOLD_02, 0x03E80032),
  ICBCFG_HWIO_DW(APP_BWMON_THROTTLE_1_THRESHOLD_01, 0x0032FFFF),
  ICBCFG_HWIO_DW(APP_BWMON_THROTTLE_1_THRESHOLD_00, 0x00000032),
  ICBCFG_HWIOF_DW(APP_BWMON_THROTTLE_1_PEAK_ACCUM_CREDIT, PEAK_ACCUM_CREDIT, 0x100),
  ICBCFG_HWIO_DW(APP_BWMON_THROTTLE_1_CNTRL, 0xDC01),
 
  /* GPU throttles and shapers */
  ICBCFG_HWIOF_DW(GPU_BWMON_THROTTLE_0_CGC_CNTRL, THROTTLE_CGC_EN, 0x1),
  ICBCFG_HWIOF_DW(GPU_BWMON_THROTTLE_0_GRANT_PERIOD, GRANT_PERIOD, 0x3e8),
  ICBCFG_HWIO_DW(GPU_BWMON_THROTTLE_0_THRESHOLD_03, 0x0000FFFF),
  ICBCFG_HWIO_DW(GPU_BWMON_THROTTLE_0_THRESHOLD_02, 0x03E80032),
  ICBCFG_HWIO_DW(GPU_BWMON_THROTTLE_0_THRESHOLD_01, 0x0000FFFF),
  ICBCFG_HWIO_DW(GPU_BWMON_THROTTLE_0_THRESHOLD_00, 0x0000FFFF),
  ICBCFG_HWIOF_DW(GPU_BWMON_THROTTLE_0_PEAK_ACCUM_CREDIT, PEAK_ACCUM_CREDIT, 0x100),
  ICBCFG_HWIO_DW(GPU_BWMON_THROTTLE_0_CNTRL, 0x5C01),
 
  ICBCFG_HWIOF_DW(GPU_BWMON_THROTTLE_1_CGC_CNTRL, THROTTLE_CGC_EN, 0x1),
  ICBCFG_HWIOF_DW(GPU_BWMON_THROTTLE_1_GRANT_PERIOD, GRANT_PERIOD, 0x3e8),
  ICBCFG_HWIO_DW(GPU_BWMON_THROTTLE_1_THRESHOLD_03, 0x0000FFFF),
  ICBCFG_HWIO_DW(GPU_BWMON_THROTTLE_1_THRESHOLD_02, 0x03E80032),
  ICBCFG_HWIO_DW(GPU_BWMON_THROTTLE_1_THRESHOLD_01, 0x0000FFFF),
  ICBCFG_HWIO_DW(GPU_BWMON_THROTTLE_1_THRESHOLD_00, 0x0000FFFF),
  ICBCFG_HWIOF_DW(GPU_BWMON_THROTTLE_1_PEAK_ACCUM_CREDIT, PEAK_ACCUM_CREDIT, 0x100),
  ICBCFG_HWIO_DW(GPU_BWMON_THROTTLE_1_CNTRL, 0x5C01),

};

icbcfg_prop_seg_type icbcfg_qm_cfg_seg_kailua_v1 = 
{
  /* Length of the config  data array */
  ARRAY_SIZE(icbcfg_qm_cfg_data_kailua_v1),
  /* Pointer to config data array */ 
  icbcfg_qm_cfg_data_kailua_v1                                    
};

/*---------------------------------------------------------------------------*/
/* GEMNOC Early Config Segment                                               */
/*---------------------------------------------------------------------------*/
icbcfg_data_type icbcfg_gemnoc_early_cfg_data_kailua_v1[] =
{
  /* GEMNOC ARCG sequence */
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_CNOC_SF_CLK_FORCECLKON_LOW,    0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_GEMNOC_CFG_CLK_FORCECLKON_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_GEMNOC_CLK_FORCECLKON_LOW,     0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_GPU_CLK_FORCECLKON_LOW,        0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_LPASS_CLK_FORCECLKON_LOW,      0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_MDSP_CLK_FORCECLKON_LOW,       0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_MNOC_HF_CLK_FORCECLKON_LOW,    0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_MNOC_SF_CLK_FORCECLKON_LOW,    0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_MODEM_CLK_FORCECLKON_LOW,      0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_NSP_NOC_CLK_FORCECLKON_LOW,    0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_PCIE_SF_CLK_FORCECLKON_LOW,    0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_PWRCTL_CLK_FORCECLKON_LOW,     0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_SNOC_GC_CLK_FORCECLKON_LOW,    0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_SNOC_SF_CLK_FORCECLKON_LOW,    0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_SYS_TCU_CLK_FORCECLKON_LOW,    0x1),
  ICBCFG_HWIO_DW(GEM_NOC_CNOC_SF_CLK_RCGCONTROLLER_WAKEUP_LOW, 0x00000009),
  ICBCFG_HWIO_DW(GEM_NOC_GEMNOC_CFG_CLK_RCGCONTROLLER_WAKEUP_LOW, 0x00000007),
  ICBCFG_HWIO_DW(GEM_NOC_GEMNOC_CLK_RCGCONTROLLER_WAKEUP_LOW, 0x0000000C),
  ICBCFG_HWIO_DW(GEM_NOC_GPU_CLK_RCGCONTROLLER_WAKEUP_LOW, 0x00000013),
  ICBCFG_HWIO_DW(GEM_NOC_MDSP_CLK_RCGCONTROLLER_WAKEUP_LOW, 0x0000000D),
  ICBCFG_HWIO_DW(GEM_NOC_MNOC_HF_CLK_RCGCONTROLLER_WAKEUP_LOW, 0x00000009),
  ICBCFG_HWIO_DW(GEM_NOC_MNOC_SF_CLK_RCGCONTROLLER_WAKEUP_LOW, 0x0000000F),
  ICBCFG_HWIO_DW(GEM_NOC_MODEM_CLK_RCGCONTROLLER_WAKEUP_LOW, 0x0000000D),
  ICBCFG_HWIO_DW(GEM_NOC_NSP_NOC_CLK_RCGCONTROLLER_WAKEUP_LOW, 0x0000000C),
  ICBCFG_HWIO_DW(GEM_NOC_PCIE_SF_CLK_RCGCONTROLLER_WAKEUP_LOW, 0x0000000A),
  ICBCFG_HWIO_DW(GEM_NOC_PWRCTL_CLK_RCGCONTROLLER_WAKEUP_LOW, 0x00000008),
  ICBCFG_HWIO_DW(GEM_NOC_SNOC_GC_CLK_RCGCONTROLLER_WAKEUP_LOW, 0x00000007),
  ICBCFG_HWIO_DW(GEM_NOC_SNOC_SF_CLK_RCGCONTROLLER_WAKEUP_LOW, 0x00000009),
  ICBCFG_HWIO_DW(GEM_NOC_SYS_TCU_CLK_RCGCONTROLLER_WAKEUP_LOW, 0x0000000A),
  ICBCFG_HWIO_DW(GEM_NOC_CNOC_SF_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0xFF),
  ICBCFG_HWIO_DW(GEM_NOC_GEMNOC_CFG_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0xFF),
  ICBCFG_HWIO_DW(GEM_NOC_GEMNOC_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0xFF),
  ICBCFG_HWIO_DW(GEM_NOC_GPU_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0xFF),
  ICBCFG_HWIO_DW(GEM_NOC_LPASS_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0xFF),
  ICBCFG_HWIO_DW(GEM_NOC_MDSP_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0xFF),
  ICBCFG_HWIO_DW(GEM_NOC_MNOC_HF_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0xFF),
  ICBCFG_HWIO_DW(GEM_NOC_MNOC_SF_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0xFF),
  ICBCFG_HWIO_DW(GEM_NOC_MODEM_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0xFF),
  ICBCFG_HWIO_DW(GEM_NOC_NSP_NOC_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0xFF),
  ICBCFG_HWIO_DW(GEM_NOC_PCIE_SF_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0xFF),
  ICBCFG_HWIO_DW(GEM_NOC_PWRCTL_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0xFF),
  ICBCFG_HWIO_DW(GEM_NOC_SNOC_GC_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0xFF),
  ICBCFG_HWIO_DW(GEM_NOC_SNOC_SF_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0xFF),
  ICBCFG_HWIO_DW(GEM_NOC_SYS_TCU_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0xFF),
  ICBCFG_HWIO_DW(GEM_NOC_NANORCGEN_SBM_FLAGOUTSET0_LOW, 0x7FDF),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_CNOC_SF_CLK_FORCECLKON_LOW,    0x0),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_GEMNOC_CFG_CLK_FORCECLKON_LOW, 0x0),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_GEMNOC_CLK_FORCECLKON_LOW,     0x0),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_GPU_CLK_FORCECLKON_LOW,        0x0),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_LPASS_CLK_FORCECLKON_LOW,      0x0),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_MDSP_CLK_FORCECLKON_LOW,       0x0),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_MNOC_HF_CLK_FORCECLKON_LOW,    0x0),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_MNOC_SF_CLK_FORCECLKON_LOW,    0x0),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_MODEM_CLK_FORCECLKON_LOW,      0x0),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_NSP_NOC_CLK_FORCECLKON_LOW,    0x0),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_PCIE_SF_CLK_FORCECLKON_LOW,    0x0),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_PWRCTL_CLK_FORCECLKON_LOW,     0x0),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_SNOC_GC_CLK_FORCECLKON_LOW,    0x0),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_SNOC_SF_CLK_FORCECLKON_LOW,    0x0),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_SYS_TCU_CLK_FORCECLKON_LOW,    0x0),

	/* GEMNOC HSR */
  ICBCFG_HWIO_DW(GEM_NOC_ALM_GPU_TCU_DYNATTR_CACHEINDEXVAL_LOW, 0x0000000B),
  ICBCFG_HWIO_DW(GEM_NOC_ALM_GPU_TCU_DYNATTR_MAINCTL_LOW, 0x00100000),
  ICBCFG_HWIO_DW(GEM_NOC_ALM_SYS_TCU_DYNATTR_CACHEINDEXVAL_LOW, 0x00000012),
  ICBCFG_HWIO_DW(GEM_NOC_ALM_SYS_TCU_DYNATTR_MAINCTL_LOW, 0x00100000),
  ICBCFG_HWIO_DW(GEM_NOC_QNS_LLCC0_POC_DBG_CFG_LOW, 0x00020000),
  ICBCFG_HWIO_DW(GEM_NOC_QNS_LLCC1_POC_DBG_CFG_LOW, 0x00020000),
  ICBCFG_HWIO_DW(GEM_NOC_QNS_LLCC2_POC_DBG_CFG_LOW, 0x00020000),
  ICBCFG_HWIO_DW(GEM_NOC_QNS_LLCC3_POC_DBG_CFG_LOW, 0x00020000),
  ICBCFG_HWIO_DW(GEM_NOC_QCIDIRECTORY_EVEN_SNOOPFILTER_QNS_LLCC0_CTL_MAINCTL_LOW, 0x00000004),
  ICBCFG_HWIO_DW(GEM_NOC_QCIDIRECTORY_EVEN_SNOOPFILTER_QNS_LLCC2_CTL_MAINCTL_LOW, 0x00000004),
  ICBCFG_HWIO_DW(GEM_NOC_QCIDIRECTORY_ODD_SNOOPFILTER_QNS_LLCC1_CTL_MAINCTL_LOW, 0x00000004),
  ICBCFG_HWIO_DW(GEM_NOC_QCIDIRECTORY_ODD_SNOOPFILTER_QNS_LLCC3_CTL_MAINCTL_LOW, 0x00000004),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_GEMNOC_CFG_CLK_ACTIVEDIS_LOW, 0x00000001),

  /* DCNOC ARCG */
  ICBCFG_HWIO_DW(DC_NOC_DCH_CSRUNIT_RCG_CSRUNIT_RCG_DC_NOC_CLK_DCH_FORCECLKON_LOW, 0x1),
  ICBCFG_HWIO_DW(DC_NOC_DCH_SBM_NRCG_CONTROLLER_SBM_FLAGOUTSET0_LOW, 0x1),
  ICBCFG_HWIO_DW(DC_NOC_DCH_CSRUNIT_SLVRCG_CSRUNIT_SLAVE_RCG_QHS_DPM_LOW, 0x1),
  ICBCFG_HWIO_DW(DC_NOC_DCH_CSRUNIT_SLVRCG_CSRUNIT_SLAVE_RCG_QSS_QMIP_LOW, 0xF),
  ICBCFG_HWIO_DW(DC_NOC_DCH_CSRUNIT_RCG_CSRUNIT_RCG_DC_NOC_CLK_DCH_FORCECLKON_LOW, 0x0),
};

icbcfg_prop_seg_type icbcfg_gemnoc_early_cfg_seg_kailua_v1 = 
{
  /* Length of the config  data array */
  ARRAY_SIZE(icbcfg_gemnoc_early_cfg_data_kailua_v1),
  /* Pointer to config data array */ 
  icbcfg_gemnoc_early_cfg_data_kailua_v1                                    
};

/*---------------------------------------------------------------------------*/
/* Init Config Segment list                                                  */
/*---------------------------------------------------------------------------*/
icbcfg_prop_seg_type *icbcfg_boot_segs_kailua_v1[] =
{
  &icbcfg_qm_cfg_seg_kailua_v1,
  &icbcfg_gemnoc_early_cfg_seg_kailua_v1,
};

icbcfg_prop_type icbcfg_boot_prop_kailua_v1 =
{
  /* Length of the config  data array */
  ARRAY_SIZE(icbcfg_boot_segs_kailua_v1),
  /* Pointer to config data array */
  icbcfg_boot_segs_kailua_v1
};

/*---------------------------------------------------------------------------*/
/* PostInit Config Segments                                                  */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* GEMNOC Post Config Segment                                                */
/*---------------------------------------------------------------------------*/
icbcfg_data_type icbcfg_gemnoc_cfg_data_kailua_v1[] =
{
	ICBCFG_DEFAULT(),
};

icbcfg_prop_seg_type icbcfg_gemnoc_cfg_seg_kailua_v1 =
{
  /* Length of the config  data array */
  ARRAY_SIZE(icbcfg_gemnoc_cfg_data_kailua_v1),
  /* Pointer to config data array */
  icbcfg_gemnoc_cfg_data_kailua_v1
};

/*---------------------------------------------------------------------------*/
/* LLCC Config Segment                                                       */
/*---------------------------------------------------------------------------*/
icbcfg_data_type icbcfg_llcc_cfg_data_kailua_v1[] =
{
  /* Modem Victim mode */
  ICBCFG_HWIO_DW(LLCC_BROADCAST_ORLLCC_FEAC_TCM_ADDR_BASE_CFG, 0x0080002B),
  ICBCFG_HWIO_DW(LLCC_BROADCAST_ORLLCC_FEAC_VICTIM_ZONE2_CFG0, 0xFF004500),
  ICBCFG_HWIO_DW(LLCC_BROADCAST_ORLLCC_FEAC_VICTIM_ZONE2_CFG1, 0x00000080),

  /* SCID overrides */
  ICBCFG_HWIO_DW(LLCC_BROADCAST_ORLLCC_TRP_RWE_OVERRIDE_CFG0,                0x00000020),
  ICBCFG_HWIO_DW(LLCC_BROADCAST_ORLLCC_TRP_RD_NOALLOC_ON_MISS_OVERRIDE_CFG0, 0x40040820),

  /* TRP Algorithm */
  ICBCFG_HWIO_DW(LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG0, 0x00100000),
  ICBCFG_HWIO_DW(LLCC_BROADCAST_ORLLCC_TRP_ALGO_CFG5, 0x40000000),
  ICBCFG_HWIOI_DW(LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG, 30, 0x02000048),
  ICBCFG_HWIOI_DW(LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE2_CFG, 30, 0x00FFFFFF),

  /* LLCC TAG sequence */
  ICBCFG_HWIO_DW(LLCC_BROADCAST_ORLLCC_TRP_NC_AS_C_OVERRIDE_CFG,  0xFFFFFFFF),
  ICBCFG_HWIO_DW(LLCC_BROADCAST_ANDLLCC_TRP_C_AS_NC_OVERRIDE_CFG, 0x00000000),

  /* Island Overrides */
  ICBCFG_HWIOI_DW(LLCC_BROADCAST_ORLLCC_LPI_SHARED_SCT_n_TYPE_CFG, 3,  0x00000002),
  ICBCFG_HWIOI_DW(LLCC_BROADCAST_ORLLCC_LPI_SHARED_SCT_n_TYPE_CFG, 12, 0x00000003),
  ICBCFG_HWIOI_DW(LLCC_BROADCAST_ORLLCC_LPI_SHARED_SCT_n_TYPE_CFG, 15, 0x00000003),
  ICBCFG_HWIOI_DW(LLCC_BROADCAST_ORLLCC_LPI_SHARED_SCT_n_TYPE_CFG, 18, 0x00000001),
  ICBCFG_HWIOI_DW(LLCC_BROADCAST_ORLLCC_LPI_SHARED_SCT_n_TYPE_CFG, 27, 0x00000001),
  ICBCFG_HWIOI_DW(LLCC_BROADCAST_ORLLCC_LPI_SHARED_SCT_n_TYPE_CFG, 29, 0x00000001),
  ICBCFG_HWIOI_DW(LLCC_BROADCAST_ORLLCC_LPI_SHARED_SCT_n_TYPE_CFG, 30, 0x00000001),
  ICBCFG_HWIOI_DW(LLCC_BROADCAST_ORLLCC_LPI_SHARED_SCT_n_TYPE_CFG, 31, 0x00000001),
  ICBCFG_HWIO_DW(LLCC_BROADCAST_ORLLCC_LPI_SHARED_ISLAND_UIMAGE_CFG, 0x00180FF8),

	/* Set locks */
  ICBCFG_HWIO_DW(LLCC_BROADCAST_ANDLLCC_BEAC0_LLCC_BEAC_HMSSSELFAUTH_LOCK, 0x1),
  ICBCFG_HWIO_DW(LLCC_BROADCAST_ANDLLCC_BEAC0_LLCC_BEAC_HPROTNS_LOCK,      0x1),
  ICBCFG_HWIO_DW(LLCC_BROADCAST_ANDLLCC_BEAC0_LLCC_BEAC_HSECUREPROC_LOCK,  0x1),
};

icbcfg_prop_seg_type icbcfg_llcc_cfg_seg_kailua_v1 =
{
  /* Length of the config  data array */
  ARRAY_SIZE(icbcfg_llcc_cfg_data_kailua_v1),
  /* Pointer to config data array */
  icbcfg_llcc_cfg_data_kailua_v1
};

/*---------------------------------------------------------------------------*/
/* LLCC Config Segment                                                       */
/*---------------------------------------------------------------------------*/
icbcfg_data_type icbcfg_wa_data_kailua_v1[] =
{
  ICBCFG_DEFAULT(),
};

icbcfg_prop_seg_type icbcfg_wa_seg_kailua_v1 =
{
  /* Length of the config  data array */
  ARRAY_SIZE(icbcfg_wa_data_kailua_v1),
  /* Pointer to config data array */
  icbcfg_wa_data_kailua_v1
};

/*---------------------------------------------------------------------------*/
/* PostInit Config Segment list                                              */
/*---------------------------------------------------------------------------*/
icbcfg_prop_seg_type *icbcfg_post_boot_segs_kailua_v1[] =
{
  &icbcfg_gemnoc_cfg_seg_kailua_v1,
  &icbcfg_llcc_cfg_seg_kailua_v1,
  &icbcfg_wa_seg_kailua_v1,
};

icbcfg_prop_type icbcfg_post_prop_kailua_v1 =
{
  /* Length of the config  data array */
  ARRAY_SIZE(icbcfg_post_boot_segs_kailua_v1),
  /* Pointer to config data array */
  icbcfg_post_boot_segs_kailua_v1
};

icbcfg_mem_region_type map_ddr_regions_kailua_v1[] =
{
  { 0x080000000ULL, 0x100000000ULL },
  { 0x800000000ULL, 0x1000000000ULL },
};

/* Translation block base addresses. */
uint8 *trans_bases_kailua_v1[] =
{
  (uint8 *)HWIO_ADDR(LLCC0_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG),
  (uint8 *)HWIO_ADDR(LLCC1_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG),
  (uint8 *)HWIO_ADDR(LLCC2_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG),
  (uint8 *)HWIO_ADDR(LLCC3_LLCC_BEAC0_LLCC_BEAC_ADDR_TRANSLATOR_CFG),
};

icbcfg_device_config_type kailua_v1 =
{
  /* Chip version information for this device data. */
  .family =              CHIPINFO_FAMILY_KAILUA,      /**< Chip family */
  .match =               false,                       /**< Exact match for version? */
  .version =             0,                           /**< Chip version */
                                        
  /* Device information. */
  .map_ddr_region_count = ARRAY_SIZE(map_ddr_regions_kailua_v1), /**< Number of regions in the DDR map */
  .map_ddr_regions =  map_ddr_regions_kailua_v1,             /**< Array of mappable DDR regions */
  .num_segments =     6,                                     /**< Number of mapping segments. */
  .num_channels =     4,                                     /**< Number of channels. */
  .addr_width =       36,                                    /**< Address width in bits. */
  .trans_type =       ICBCFG_ADDR_TRANS_LLCC,                /**< Address translator hardware type. */
  .trans_bases =      trans_bases_kailua_v1,                 /**< Translation block base addresses. */
                                        
  /* Prop lists. */
  .prop_data =        &icbcfg_boot_prop_kailua_v1,           /**< Init time prop list. */
  .post_prop_data =   &icbcfg_post_prop_kailua_v1,           /**< Post-init time prop list. */
  .early_prop_data =  &icbcfg_early_prop_kailua_v1,          /**< Early init pop list. */
};

/*---------------------------------------------------------------------------*/
/* TARGET LIST                                                               */
/*---------------------------------------------------------------------------*/
icbcfg_device_config_type *configs_kailua[] =
{
  &kailua_v1,
};
                                        
/*---------------------------------------------------------------------------*/
/* EXPORTED TARGET DEFINITION                                                */
/*---------------------------------------------------------------------------*/
icbcfg_info_type icbcfg_info =
{
  ARRAY_SIZE(configs_kailua),
  configs_kailua,
};
