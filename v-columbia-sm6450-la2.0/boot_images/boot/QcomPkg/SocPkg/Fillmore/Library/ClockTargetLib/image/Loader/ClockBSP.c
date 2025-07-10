/*
==============================================================================

FILE:         ClockBSP.c

DESCRIPTION:
  This file contains the clock driver BSP data.

  Auto-generated from the following IPCat controller releases:

    SM7450v1 (fillmore_1.0):
      PLL_HSR   : 7.0
      AOSS_CC   : waipio_aoss_cc_z_aoss_cc_5.0_p3q3r8.1_fp10 [waipio_aoss_cc.r6]
      APSS_CC   : fillmore_apss_cc_fillmore_apss_1.0_p3q3r88_fp13 [fillmore_apss_cc.r2]
      GCC       : fillmore_gcc_z_fillmore_clk_ctl_1.0_p3q3r24_fp18 [fillmore_gcc.r13]
      GPU_CC    : fillmore_gpu_cc_z_gpu_cc_fillmore_5.2_p3q2r5_fp6 [fillmore_gpu_cc.r3]


  Generated using the following clockdrivergen settings:

CLOCKDRIVERGEN_CONFIG = \
{'db_override': {'GCC': {'cbc': {'GCC_UFS_0_CLKREF_EN': {'func_group': 'ufs_phy'},
                                 'GCC_USB3_0_CLKREF_EN': {'func_group': 'usb30_prim'},
                                 'gcc_aggre_ufs_phy_axi_clk': {'func_group': 'ufs_phy'},
                                 'gcc_aggre_usb3_prim_axi_clk': {'func_group': 'usb30_prim'},
                                 'gcc_cfg_noc_usb3_prim_axi_clk': {'func_group': 'usb30_prim'}}}},
 'filter_warning': 'sw',
 'generators': [{'options': {'clock_flags': {'gcc_gpll0': ['DO_NOT_DISABLE'],
                                             'gcc_ufs_phy_rx_symbol_0_clk': ['NO_POLL_AFTER_ENABLE'],
                                             'gcc_ufs_phy_rx_symbol_1_clk': ['NO_POLL_AFTER_ENABLE'],
                                             'gcc_ufs_phy_tx_symbol_0_clk': ['NO_POLL_AFTER_ENABLE'],
                                             'gcc_usb3_prim_phy_pipe_clk': ['NO_POLL_AFTER_ENABLE']},
                             'domain_freq_config_format': '  {{{{ {FREQ:>10}, '
                                                          '{VREG:<30} {{{{ '
                                                          '{SEL:<6} {DIV:<6} '
                                                          '{M:<6} {N:<6} '
                                                          '{DFS:<4} }}}}, '
                                                          '{SRCIDX:<45}, '
                                                          '{SRCFREQIDX:<20}, '
                                                          '{{VERSION}} }}}},  '
                                                          '{COMMENT}\n',
                             'env': ['boot'],
                             'explicit_ownership': True,
                             'hal_ctl_structs': {'aoss_cc_pll1': 'HAL_clk_xbl_PongoevoFillmorePLLControl',
                                                 'apss_cc_gold_pll': 'HAL_clk_xbl_ZondaevoV2PLLControl',
                                                 'apss_cc_gold_plus_pll': 'HAL_clk_xbl_ZondaevoV2PLLControl',
                                                 'apss_cc_l3_pll': 'HAL_clk_xbl_ZondaevoV2PLLControl',
                                                 'apss_cc_silver_pll': 'HAL_clk_xbl_ZondaevoV2PLLControl'},
                             'ignore_env_for_pll_settings': True,
                             'include_all_freqs': ['.*sdc.*'],
                             'include_boot_enable_list': True,
                             'include_debug_mux': False,
                             'include_default_freqs': False,
                             'include_domain_array': False,
                             'include_file': {'ClockBSPExtern.h': True,
                                              'HALclkTest.c': False},
                             'include_fmax': False,
                             'include_funcgroups': ['core',
                                                    'boot_rom',
                                                    'ddrss',
                                                    'sdcc.*',
                                                    'ufs_phy',
                                                    'usb30_prim'],
                             'include_master_enums': True,
                             'include_only_clocknames': ['.*qup.*wrap._s.*',
                                                         'gcc_memnoc_clk',
                                                         'gcc_shrm_clk'],
                             'include_only_fmax': {'.*': ['nominal']},
                             'include_only_freqs': {'.*qup.*wrap._s.*': [7372800,
                                                                         14745600,
                                                                         19200000,
                                                                         48000000]},
                             'include_pllout_hw_ctl': True,
                             'include_power_domains': False,
                             'include_source_map': False,
                             'include_source_name': False,
                             'include_unique_id': False,
                             'include_voltage_control': False,
                             'include_xo_voting': False,
                             'no_static_scope': ['.*'],
                             'source_freq_config_format': '  {{{{ {{{{ '
                                                          '{ALPHA}, '
                                                          'HAL_CLK_PLL_FRAC_MODE_{FRACMODE}, '
                                                          '{POST:<30}, {L:<4} '
                                                          '}}}}, '
                                                          '{{VERSION}}}}}},\n'},
                 'output_dir': 'image/Loader',
                 'type': 'dalclock'}],
 'target': ['fillmore']}

==============================================================================

$Header: //components/rel/core.boot/6.0/QcomPkg/SocPkg/Fillmore/Library/ClockTargetLib/image/Loader/ClockBSP.c#13 $

==============================================================================
            Copyright (c) 2022 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================

*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "ClockBSP.h"
#include "HALclkHWIO.h"
#include "HALhwio.h"


/*=========================================================================
      Externs
==========================================================================*/
extern HAL_clk_xbl_SourceControlType          HAL_clk_xbl_LucidevoPLLControl;
extern HAL_clk_xbl_SourceControlType          HAL_clk_xbl_PongoevoPLLControl;
extern HAL_clk_xbl_SourceControlType          HAL_clk_xbl_ZondaevoPLLControl;

/*
 * Custom control structures.
 */
extern HAL_clk_xbl_SourceControlType      HAL_clk_xbl_PongoevoFillmorePLLControl;
extern HAL_clk_xbl_SourceControlType      HAL_clk_xbl_ZondaevoV2PLLControl;


/*=========================================================================
      Data Declarations
==========================================================================*/


/*=========================================================================
      Source Register Settings
==========================================================================*/

static const ClockSourceRegSettingsType ClockSourceRegSettings_AOSSCC_AOSSCCPLL0[] =
{
  {
    .HALSettings = {
      .nConfigCtl   = 0x20485699,
      .nConfigCtl1  = 0x00182261,
      .nConfigCtl2  = 0x32AA299C,
      .nTestCtl     = 0x00000000,
      .nTestCtl1    = 0x00000000,
      .nTestCtl2    = 0x00000000,
      .nUserCtl     = 0x00000000,
      .nUserCtl1    = 0x00000805,
    },
  },
};

static const ClockSourceRegSettingsType ClockSourceRegSettings_AOSSCC_AOSSCCPLL1[] =
{
  {
    .HALSettings = {
      .nConfigCtl   = 0x60004F61,
      .nConfigCtl1  = 0x0001C808,
      .nConfigCtl2  = 0x00000000,
      .nConfigCtl3  = 0x040001AC,
      .nTestCtl     = 0x00000000,
      .nTestCtl1    = 0x0081C6DE,
      .nTestCtl2    = 0x40100000,
      .nTestCtl3    = 0x440001B0,
      .nTestCtl4    = 0x000003D8,
      .nUserCtl     = 0x00000000,
      .nUserCtl1    = 0x00250002,
    },
  },
};

static const ClockSourceRegSettingsType ClockSourceRegSettings_APSSCC_APSSCCGOLDPLL[] =
{
  {
    .HALSettings = {
      .nConfigCtl   = 0x08200800,
      .nConfigCtl1  = 0x05028001,
      .nConfigCtl2  = 0x00000000,
      .nTestCtl     = 0x00000000,
      .nTestCtl1    = 0x00000000,
      .nTestCtl2    = 0x00000000,
      .nUserCtl     = 0x00000000,
      .nUserCtl1    = 0x00000000,
    },
  },
};


/*=========================================================================
      Source BSP
==========================================================================*/

/*
 * ClockSourceBSP_AOSSCC_AOSSCCPLL0
 *
 * Used by:
 *   ClockSource_AOSSCC_AOSSCCPLL0
 */
static const ClockSourceFreqConfigType ClockSourceBSP_AOSSCC_AOSSCCPLL0[] =
{
  { { 0x00004000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidevo.nEven = 2}       , 31   }, },
};
static const ClockSourceFreqConfigType ClockSourceBSPCal_AOSSCC_AOSSCCPLL0[] =
{
  { { 0x00000000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                     , 68   }, },
};

/*
 * ClockSourceBSP_AOSSCC_AOSSCCPLL1
 *
 * Used by:
 *   ClockSource_AOSSCC_AOSSCCPLL1
 */
static const ClockSourceFreqConfigType ClockSourceBSP_AOSSCC_AOSSCCPLL1[] =
{
  { { 0x00000000, HAL_CLK_PLL_FRAC_MODE_UNKNOWN, {.Pongoevo.nEven = 2}       , 2    }, },
};

/*
 * ClockSourceBSP_APSSCC_APSSCCGOLDPLL
 *
 * Used by:
 *   ClockSource_APSSCC_APSSCCGOLDPLL
 */
static const ClockSourceFreqConfigType ClockSourceBSP_APSSCC_APSSCCGOLDPLL[] =
{
  { { 0x00000000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                     , 78   }, },
};

/*
 * ClockSourceBSP_APSSCC_APSSCCGOLDPLUSPLL
 *
 * Used by:
 *   ClockSource_APSSCC_APSSCCGOLDPLUSPLL
 */
static const ClockSourceFreqConfigType ClockSourceBSP_APSSCC_APSSCCGOLDPLUSPLL[] =
{
  { { 0x00000000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                     , 92   }, },
};

/*
 * ClockSourceBSP_APSSCC_APSSCCL3PLL
 *
 * Used by:
 *   ClockSource_APSSCC_APSSCCL3PLL
 */
static const ClockSourceFreqConfigType ClockSourceBSP_APSSCC_APSSCCL3PLL[] =
{
  { { 0x00000000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                     , 63   }, },
};

/*
 * ClockSourceBSP_APSSCC_APSSCCSILVERPLL
 *
 * Used by:
 *   ClockSource_APSSCC_APSSCCSILVERPLL
 */
static const ClockSourceFreqConfigType ClockSourceBSP_APSSCC_APSSCCSILVERPLL[] =
{
  { { 0x00000000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                     , 71   }, },
};

/*
 * ClockSourceBSP_GCC_GCCGPLL0
 *
 * Used by:
 *   ClockSource_GCC_GCCGPLL0
 */
static const ClockSourceFreqConfigType ClockSourceBSP_GCC_GCCGPLL0[] =
{
  { { 0x00004000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidevo.nEven = 2, .Lucidevo.nOdd = 3}, 31   }, },
};

/*
 * ClockSourceBSP_GCC_GCCGPLL1
 *
 * Used by:
 *   ClockSource_GCC_GCCGPLL1
 */
static const ClockSourceFreqConfigType ClockSourceBSP_GCC_GCCGPLL1[] =
{
  { { 0x00008555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                     , 55   }, },
};

/*
 * ClockSourceBSP_GCC_GCCGPLL2
 *
 * Used by:
 *   ClockSource_GCC_GCCGPLL2
 */
static const ClockSourceFreqConfigType ClockSourceBSP_GCC_GCCGPLL2[] =
{
  { { 0x00004AAA, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                     , 57   }, },
};

/*
 * ClockSourceBSP_GCC_GCCGPLL4
 *
 * Used by:
 *   ClockSource_GCC_GCCGPLL4
 */
static const ClockSourceFreqConfigType ClockSourceBSP_GCC_GCCGPLL4[] =
{
  { { 0x0000FAAA, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                     , 41   }, },
};

/*
 * ClockSourceBSP_GCC_GCCGPLL5
 *
 * Used by:
 *   ClockSource_GCC_GCCGPLL5
 */
static const ClockSourceFreqConfigType ClockSourceBSP_GCC_GCCGPLL5[] =
{
  { { 0x00009800, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                     , 48   }, },
};

/*
 * ClockSourceBSP_GCC_GCCGPLL6
 *
 * Used by:
 *   ClockSource_GCC_GCCGPLL6
 */
static const ClockSourceFreqConfigType ClockSourceBSP_GCC_GCCGPLL6[] =
{
  { { 0x00001000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                     , 39   }, },
};

/*
 * ClockSourceBSP_GCC_GCCGPLL7
 *
 * Used by:
 *   ClockSource_GCC_GCCGPLL7
 */
static const ClockSourceFreqConfigType ClockSourceBSP_GCC_GCCGPLL7[] =
{
  { { 0x00000AAA, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                     , 26   }, },
};

/*
 * ClockSourceBSP_GCC_GCCGPLL8
 *
 * Used by:
 *   ClockSource_GCC_GCCGPLL8
 */
static const ClockSourceFreqConfigType ClockSourceBSP_GCC_GCCGPLL8[] =
{
  { { 0x00007D55, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                     , 18   }, },
};

/*
 * ClockSourceBSP_GCC_GCCGPLL9
 *
 * Used by:
 *   ClockSource_GCC_GCCGPLL9
 */
static const ClockSourceFreqConfigType ClockSourceBSP_GCC_GCCGPLL9[] =
{
  { { 0x00001555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                     , 42   }, },
};


/*=========================================================================
      Sources
==========================================================================*/

ClockSourceNodeType ClockSource_XO =
{
  .nFlags       = 0x0,
};

ClockSourceNodeType ClockSource_AOSSCC_AOSSCCPLL0 =
{
  .nFlags                     = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP                       = ClockSourceBSP_AOSSCC_AOSSCCPLL0,
  .nBSPLen                    = SIZEOF_ARRAY(ClockSourceBSP_AOSSCC_AOSSCCPLL0),
  .nConfigMask                = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE,
  .nAddr                      = HWIO_ADDR(AOSS_CC_PLL0_PLL_MODE),
  .pmControl                  = &HAL_clk_xbl_LucidevoPLLControl,
  .pCalibrationFreqConfig     = ClockSourceBSPCal_AOSSCC_AOSSCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_AOSSCC_AOSSCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_AOSSCC_AOSSCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_AOSSCC_AOSSCCPLL0),
};

ClockSourceNodeType ClockSource_AOSSCC_AOSSCCPLL1 =
{
  .nFlags                     = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP                       = ClockSourceBSP_AOSSCC_AOSSCCPLL1,
  .nBSPLen                    = SIZEOF_ARRAY(ClockSourceBSP_AOSSCC_AOSSCCPLL1),
  .nConfigMask                = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE,
  .nAddr                      = HWIO_ADDR(AOSS_CC_PLL1_PLL_MODE),
  .pmControl                  = &HAL_clk_xbl_PongoevoFillmorePLLControl,
  .pCalibrationFreqConfig     = ClockSourceBSP_AOSSCC_AOSSCCPLL1,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSP_AOSSCC_AOSSCCPLL1),
  .pRegSettings               = ClockSourceRegSettings_AOSSCC_AOSSCCPLL1,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_AOSSCC_AOSSCCPLL1),
};

ClockSourceNodeType ClockSource_APSSCC_APSSCCGOLDPLL =
{
  .nFlags                     = 0x0,
  .aBSP                       = ClockSourceBSP_APSSCC_APSSCCGOLDPLL,
  .nBSPLen                    = SIZEOF_ARRAY(ClockSourceBSP_APSSCC_APSSCCGOLDPLL),
  .nConfigMask                = 0x0,
  .nAddr                      = HWIO_ADDR(APSS_CC_GOLD_PLL_MODE),
  .pmControl                  = &HAL_clk_xbl_ZondaevoV2PLLControl,
  .pCalibrationFreqConfig     = ClockSourceBSP_APSSCC_APSSCCGOLDPLL,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSP_APSSCC_APSSCCGOLDPLL),
  .pRegSettings               = ClockSourceRegSettings_APSSCC_APSSCCGOLDPLL,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_APSSCC_APSSCCGOLDPLL),
};

ClockSourceNodeType ClockSource_APSSCC_APSSCCGOLDPLUSPLL =
{
  .nFlags                     = 0x0,
  .aBSP                       = ClockSourceBSP_APSSCC_APSSCCGOLDPLUSPLL,
  .nBSPLen                    = SIZEOF_ARRAY(ClockSourceBSP_APSSCC_APSSCCGOLDPLUSPLL),
  .nConfigMask                = 0x0,
  .nAddr                      = HWIO_ADDR(APSS_CC_GOLDPLUS_PLL_MODE),
  .pmControl                  = &HAL_clk_xbl_ZondaevoV2PLLControl,
  .pCalibrationFreqConfig     = ClockSourceBSP_APSSCC_APSSCCGOLDPLUSPLL,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSP_APSSCC_APSSCCGOLDPLUSPLL),
  .pRegSettings               = ClockSourceRegSettings_APSSCC_APSSCCGOLDPLL,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_APSSCC_APSSCCGOLDPLL),
};

ClockSourceNodeType ClockSource_APSSCC_APSSCCL3PLL =
{
  .nFlags                     = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP                       = ClockSourceBSP_APSSCC_APSSCCL3PLL,
  .nBSPLen                    = SIZEOF_ARRAY(ClockSourceBSP_APSSCC_APSSCCL3PLL),
  .nConfigMask                = CLOCK_CONFIG_PLL_EARLY_OUTPUT_ENABLE,
  .nAddr                      = HWIO_ADDR(APSS_CC_L3_PLL_MODE),
  .pmControl                  = &HAL_clk_xbl_ZondaevoV2PLLControl,
  .pCalibrationFreqConfig     = ClockSourceBSP_APSSCC_APSSCCL3PLL,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSP_APSSCC_APSSCCL3PLL),
  .pRegSettings               = ClockSourceRegSettings_APSSCC_APSSCCGOLDPLL,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_APSSCC_APSSCCGOLDPLL),
};

ClockSourceNodeType ClockSource_APSSCC_APSSCCSILVERPLL =
{
  .nFlags                     = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP                       = ClockSourceBSP_APSSCC_APSSCCSILVERPLL,
  .nBSPLen                    = SIZEOF_ARRAY(ClockSourceBSP_APSSCC_APSSCCSILVERPLL),
  .nConfigMask                = CLOCK_CONFIG_PLL_EARLY_OUTPUT_ENABLE,
  .nAddr                      = HWIO_ADDR(APSS_CC_SILVER_PLL_MODE),
  .pmControl                  = &HAL_clk_xbl_ZondaevoV2PLLControl,
  .pCalibrationFreqConfig     = ClockSourceBSP_APSSCC_APSSCCSILVERPLL,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSP_APSSCC_APSSCCSILVERPLL),
  .pRegSettings               = ClockSourceRegSettings_APSSCC_APSSCCGOLDPLL,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_APSSCC_APSSCCGOLDPLL),
};

ClockSourceNodeType ClockSource_GCC_GCCGPLL0 =
{
  .nFlags                     = CLOCK_FLAG_DO_NOT_DISABLE |
                                CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP                       = ClockSourceBSP_GCC_GCCGPLL0,
  .nBSPLen                    = SIZEOF_ARRAY(ClockSourceBSP_GCC_GCCGPLL0),
  .nConfigMask                = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE |
                                CLOCK_CONFIG_PLL_EVEN_OUTPUT_HW_CTL |
                                CLOCK_CONFIG_PLL_FSM_MODE_ENABLE |
                                CLOCK_CONFIG_PLL_MAIN_OUTPUT_HW_CTL |
                                CLOCK_CONFIG_PLL_ODD_OUTPUT_ENABLE |
                                CLOCK_CONFIG_PLL_ODD_OUTPUT_HW_CTL,
  .nAddr                      = HWIO_ADDR(GCC_GPLL0_PLL_MODE),
  .VoterRegister              = {HWIO_ADDR(GCC_PROC_CLK_PLL_ENA_VOTE), 0x1},
  .pmControl                  = &HAL_clk_xbl_LucidevoPLLControl,
  .pCalibrationFreqConfig     = ClockSourceBSPCal_AOSSCC_AOSSCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_AOSSCC_AOSSCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_AOSSCC_AOSSCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_AOSSCC_AOSSCCPLL0),
};

ClockSourceNodeType ClockSource_GCC_GCCGPLL1 =
{
  .nFlags                     = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP                       = ClockSourceBSP_GCC_GCCGPLL1,
  .nBSPLen                    = SIZEOF_ARRAY(ClockSourceBSP_GCC_GCCGPLL1),
  .nConfigMask                = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE |
                                CLOCK_CONFIG_PLL_MAIN_OUTPUT_HW_CTL,
  .nAddr                      = HWIO_ADDR(GCC_GPLL1_PLL_MODE),
  .VoterRegister              = {HWIO_ADDR(GCC_PROC_CLK_PLL_ENA_VOTE), 0x2},
  .pmControl                  = &HAL_clk_xbl_LucidevoPLLControl,
  .pCalibrationFreqConfig     = ClockSourceBSPCal_AOSSCC_AOSSCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_AOSSCC_AOSSCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_AOSSCC_AOSSCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_AOSSCC_AOSSCCPLL0),
};

ClockSourceNodeType ClockSource_GCC_GCCGPLL2 =
{
  .nFlags                     = 0x0,
  .aBSP                       = ClockSourceBSP_GCC_GCCGPLL2,
  .nBSPLen                    = SIZEOF_ARRAY(ClockSourceBSP_GCC_GCCGPLL2),
  .nConfigMask                = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE |
                                CLOCK_CONFIG_PLL_MAIN_OUTPUT_HW_CTL,
  .nAddr                      = HWIO_ADDR(GCC_GPLL2_PLL_MODE),
  .VoterRegister              = {HWIO_ADDR(GCC_PROC_CLK_PLL_ENA_VOTE), 0x4},
  .pmControl                  = &HAL_clk_xbl_LucidevoPLLControl,
  .pCalibrationFreqConfig     = ClockSourceBSPCal_AOSSCC_AOSSCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_AOSSCC_AOSSCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_AOSSCC_AOSSCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_AOSSCC_AOSSCCPLL0),
};

ClockSourceNodeType ClockSource_GCC_GCCGPLL4 =
{
  .nFlags                     = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP                       = ClockSourceBSP_GCC_GCCGPLL4,
  .nBSPLen                    = SIZEOF_ARRAY(ClockSourceBSP_GCC_GCCGPLL4),
  .nConfigMask                = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE |
                                CLOCK_CONFIG_PLL_MAIN_OUTPUT_HW_CTL,
  .nAddr                      = HWIO_ADDR(GCC_GPLL4_PLL_MODE),
  .VoterRegister              = {HWIO_ADDR(GCC_PROC_CLK_PLL_ENA_VOTE), 0x10},
  .pmControl                  = &HAL_clk_xbl_LucidevoPLLControl,
  .pCalibrationFreqConfig     = ClockSourceBSPCal_AOSSCC_AOSSCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_AOSSCC_AOSSCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_AOSSCC_AOSSCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_AOSSCC_AOSSCCPLL0),
};

ClockSourceNodeType ClockSource_GCC_GCCGPLL5 =
{
  .nFlags                     = 0x0,
  .aBSP                       = ClockSourceBSP_GCC_GCCGPLL5,
  .nBSPLen                    = SIZEOF_ARRAY(ClockSourceBSP_GCC_GCCGPLL5),
  .nConfigMask                = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE |
                                CLOCK_CONFIG_PLL_MAIN_OUTPUT_HW_CTL,
  .nAddr                      = HWIO_ADDR(GCC_GPLL5_PLL_MODE),
  .VoterRegister              = {HWIO_ADDR(GCC_PROC_CLK_PLL_ENA_VOTE), 0x20},
  .pmControl                  = &HAL_clk_xbl_LucidevoPLLControl,
  .pCalibrationFreqConfig     = ClockSourceBSPCal_AOSSCC_AOSSCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_AOSSCC_AOSSCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_AOSSCC_AOSSCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_AOSSCC_AOSSCCPLL0),
};

ClockSourceNodeType ClockSource_GCC_GCCGPLL6 =
{
  .nFlags                     = 0x0,
  .aBSP                       = ClockSourceBSP_GCC_GCCGPLL6,
  .nBSPLen                    = SIZEOF_ARRAY(ClockSourceBSP_GCC_GCCGPLL6),
  .nConfigMask                = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE |
                                CLOCK_CONFIG_PLL_MAIN_OUTPUT_HW_CTL,
  .nAddr                      = HWIO_ADDR(GCC_GPLL6_PLL_MODE),
  .VoterRegister              = {HWIO_ADDR(GCC_PROC_CLK_PLL_ENA_VOTE), 0x40},
  .pmControl                  = &HAL_clk_xbl_LucidevoPLLControl,
  .pCalibrationFreqConfig     = ClockSourceBSPCal_AOSSCC_AOSSCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_AOSSCC_AOSSCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_AOSSCC_AOSSCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_AOSSCC_AOSSCCPLL0),
};

ClockSourceNodeType ClockSource_GCC_GCCGPLL7 =
{
  .nFlags                     = 0x0,
  .aBSP                       = ClockSourceBSP_GCC_GCCGPLL7,
  .nBSPLen                    = SIZEOF_ARRAY(ClockSourceBSP_GCC_GCCGPLL7),
  .nConfigMask                = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE |
                                CLOCK_CONFIG_PLL_MAIN_OUTPUT_HW_CTL,
  .nAddr                      = HWIO_ADDR(GCC_GPLL7_PLL_MODE),
  .VoterRegister              = {HWIO_ADDR(GCC_PROC_CLK_PLL_ENA_VOTE), 0x80},
  .pmControl                  = &HAL_clk_xbl_LucidevoPLLControl,
  .pCalibrationFreqConfig     = ClockSourceBSPCal_AOSSCC_AOSSCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_AOSSCC_AOSSCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_AOSSCC_AOSSCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_AOSSCC_AOSSCCPLL0),
};

ClockSourceNodeType ClockSource_GCC_GCCGPLL8 =
{
  .nFlags                     = 0x0,
  .aBSP                       = ClockSourceBSP_GCC_GCCGPLL8,
  .nBSPLen                    = SIZEOF_ARRAY(ClockSourceBSP_GCC_GCCGPLL8),
  .nConfigMask                = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE |
                                CLOCK_CONFIG_PLL_MAIN_OUTPUT_HW_CTL,
  .nAddr                      = HWIO_ADDR(GCC_GPLL8_PLL_MODE),
  .VoterRegister              = {HWIO_ADDR(GCC_PROC_CLK_PLL_ENA_VOTE), 0x100},
  .pmControl                  = &HAL_clk_xbl_LucidevoPLLControl,
  .pCalibrationFreqConfig     = ClockSourceBSPCal_AOSSCC_AOSSCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_AOSSCC_AOSSCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_AOSSCC_AOSSCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_AOSSCC_AOSSCCPLL0),
};

ClockSourceNodeType ClockSource_GCC_GCCGPLL9 =
{
  .nFlags                     = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP                       = ClockSourceBSP_GCC_GCCGPLL9,
  .nBSPLen                    = SIZEOF_ARRAY(ClockSourceBSP_GCC_GCCGPLL9),
  .nConfigMask                = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE |
                                CLOCK_CONFIG_PLL_MAIN_OUTPUT_HW_CTL,
  .nAddr                      = HWIO_ADDR(GCC_GPLL9_PLL_MODE),
  .VoterRegister              = {HWIO_ADDR(GCC_PROC_CLK_PLL_ENA_VOTE), 0x200},
  .pmControl                  = &HAL_clk_xbl_LucidevoPLLControl,
  .pCalibrationFreqConfig     = ClockSourceBSPCal_AOSSCC_AOSSCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_AOSSCC_AOSSCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_AOSSCC_AOSSCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_AOSSCC_AOSSCCPLL0),
};


static ClockSourceNodeType *aSources[] =
{
  &ClockSource_AOSSCC_AOSSCCPLL0,
  &ClockSource_AOSSCC_AOSSCCPLL1,
  &ClockSource_APSSCC_APSSCCGOLDPLL,
  &ClockSource_APSSCC_APSSCCGOLDPLUSPLL,
  &ClockSource_APSSCC_APSSCCL3PLL,
  &ClockSource_APSSCC_APSSCCSILVERPLL,
  &ClockSource_GCC_GCCGPLL0,
  &ClockSource_GCC_GCCGPLL1,
  &ClockSource_GCC_GCCGPLL2,
  &ClockSource_GCC_GCCGPLL4,
  &ClockSource_GCC_GCCGPLL5,
  &ClockSource_GCC_GCCGPLL6,
  &ClockSource_GCC_GCCGPLL7,
  &ClockSource_GCC_GCCGPLL8,
  &ClockSource_GCC_GCCGPLL9,
  &ClockSource_XO,
};


/*=========================================================================
      Domain BSP
==========================================================================*/

/*
 * ClockDomainBSP_AOSSCC_AOSSCCAOP
 *
 * Used by:
 *   ClockDomain_AOSSCC_AOSSCCAOP
 */
static ClockMuxConfigType ClockDomainBSP_AOSSCC_AOSSCCAOP[] =
{
  {  400000000, RAIL_VOLTAGE_LEVEL_NOM,        { 4,     3,     0,     0,     0xFF }, 0 /* ClockSource_AOSSCC_AOSSCCPLL0 */        ,  0 /* 600.0   Mhz */ ,  },   /* Mux[4] = AOSS_CC_PLL0_OUT_MAIN */
};

/*
 * ClockDomainBSP_AOSSCC_AOSSCCEUDAT
 *
 * Used by:
 *   ClockDomain_AOSSCC_AOSSCCEUDAT
 */
static ClockMuxConfigType ClockDomainBSP_AOSSCC_AOSSCCEUDAT[] =
{
  {   60000000, RAIL_VOLTAGE_LEVEL_NOM,        { 1,     10,    0,     0,     0xFF }, 0 /* ClockSource_AOSSCC_AOSSCCPLL0 */        ,  0 /* 300.0   Mhz */ ,  },   /* Mux[1] = AOSS_CC_PLL0_OUT_EVEN */
};

/*
 * ClockDomainBSP_AOSSCC_AOSSCCIBI
 *
 * Used by:
 *   ClockDomain_AOSSCC_AOSSCCIBI
 */
static ClockMuxConfigType ClockDomainBSP_AOSSCC_AOSSCCIBI[] =
{
  {   38400000, RAIL_VOLTAGE_LEVEL_MIN_SVS,    { 6,     2,     0,     0,     0xFF }, 1 /* ClockSource_AOSSCC_AOSSCCPLL1 */        ,  0 /* 38.0    Mhz */ ,  },   /* Mux[6] = AOSS_CC_PLL1_OUT_MAIN */
};

/*
 * ClockDomainBSP_AOSSCC_AOSSCCRO
 *
 * Used by:
 *   ClockDomain_AOSSCC_AOSSCCRO
 *   ClockDomain_AOSSCC_AOSSCCSPMIAODSER
 *   ClockDomain_AOSSCC_AOSSCCSWAOTS
 */
static ClockMuxConfigType ClockDomainBSP_AOSSCC_AOSSCCRO[] =
{
  {   19200000, RAIL_VOLTAGE_LEVEL_RET,        { 3,     2,     0,     0,     0xFF }, 1 /* ClockSource_AOSSCC_AOSSCCPLL1 */        ,  0 /* 19.0    Mhz */ ,  },   /* Mux[3] = AOSS_CC_PLL1_OUT_EVEN */
};

/*
 * ClockDomainBSP_AOSSCC_AOSSCCSWAO
 *
 * Used by:
 *   ClockDomain_AOSSCC_AOSSCCSWAO
 */
static ClockMuxConfigType ClockDomainBSP_AOSSCC_AOSSCCSWAO[] =
{
  {  300000000, RAIL_VOLTAGE_LEVEL_NOM,        { 1,     2,     0,     0,     0xFF }, 0 /* ClockSource_AOSSCC_AOSSCCPLL0 */        ,  0 /* 300.0   Mhz */ ,  },   /* Mux[1] = AOSS_CC_PLL0_OUT_EVEN */
};

/*
 * ClockDomainBSP_APSSCC_APSSCCGOLDMUX
 *
 * Used by:
 *   ClockDomain_APSSCC_APSSCCGOLDMUX
 *   ClockDomain_APSSCC_APSSCCGOLDPLUSMUX
 */
static ClockMuxConfigType ClockDomainBSP_APSSCC_APSSCCGOLDMUX[] =
{
  {  600000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 1,     2,     0,     0,     0xFF }, 6 /* ClockSource_GCC_GCCGPLL0 */             ,  0 /* 600.0   Mhz */ ,  },   /* Mux[1] = GCC_GPLL0_DIV */
};

/*
 * ClockDomainBSP_APSSCC_APSSCCL3MUX
 *
 * Used by:
 *   ClockDomain_APSSCC_APSSCCL3MUX
 */
static ClockMuxConfigType ClockDomainBSP_APSSCC_APSSCCL3MUX[] =
{
  { 1209600000, RAIL_VOLTAGE_LEVEL_NOM,        { 2,     2,     0,     0,     0xFF }, 4 /* ClockSource_APSSCC_APSSCCL3PLL */       ,  0 /* 1209.0  Mhz */ ,  },   /* Mux[2] = APSS_CC_L3_PLL_OUT_EARLY */
};

/*
 * ClockDomainBSP_APSSCC_APSSCCSILVERMUX
 *
 * Used by:
 *   ClockDomain_APSSCC_APSSCCSILVERMUX
 */
static ClockMuxConfigType ClockDomainBSP_APSSCC_APSSCCSILVERMUX[] =
{
  { 1363200000, RAIL_VOLTAGE_LEVEL_NOM,        { 2,     2,     0,     0,     0xFF }, 5 /* ClockSource_APSSCC_APSSCCSILVERPLL */   ,  0 /* 1363.0  Mhz */ ,  },   /* Mux[2] = APSS_CC_SILVER_PLL_OUT_EARLY */
};

/*
 * ClockDomainBSP_GCC_GCCAGGRENOC
 *
 * Used by:
 *   ClockDomain_GCC_GCCAGGRENOC
 *   ClockDomain_GCC_GCCCNOCCENTERQX
 *   ClockDomain_GCC_GCCCNOCPCIEQX
 *   ClockDomain_GCC_GCCSYSNOC
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCAGGRENOC[] =
{
  {  200000000, RAIL_VOLTAGE_LEVEL_NOM,        { 1,     6,     0,     0,     0x04 }, 6 /* ClockSource_GCC_GCCGPLL0 */             ,  0 /* 600.0   Mhz */ ,  },   /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP3_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCCE1
 *
 * Used by:
 *   ClockDomain_GCC_GCCCE1
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCCE1[] =
{
  {  171428571, RAIL_VOLTAGE_LEVEL_NOM,        { 1,     7,     0,     0,     0x03 }, 6 /* ClockSource_GCC_GCCGPLL0 */             ,  0 /* 600.0   Mhz */ ,  },   /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP11_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCCNOCPERIPH
 *
 * Used by:
 *   ClockDomain_GCC_GCCCNOCPERIPH
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCCNOCPERIPH[] =
{
  {  100000000, RAIL_VOLTAGE_LEVEL_NOM,        { 1,     12,    0,     0,     0x04 }, 6 /* ClockSource_GCC_GCCGPLL0 */             ,  0 /* 600.0   Mhz */ ,  },   /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP2_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCCONFIGNOC
 *
 * Used by:
 *   ClockDomain_GCC_GCCCONFIGNOC
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCCONFIGNOC[] =
{
  {   75000000, RAIL_VOLTAGE_LEVEL_NOM,        { 1,     16,    0,     0,     0x04 }, 6 /* ClockSource_GCC_GCCGPLL0 */             ,  0 /* 600.0   Mhz */ ,  },   /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP2_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCCONFIGNOCDDRSSSF
 *
 * Used by:
 *   ClockDomain_GCC_GCCCONFIGNOCDDRSSSF
 *   ClockDomain_GCC_GCCSYSNOCSFAXI
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCCONFIGNOCDDRSSSF[] =
{
  {  403000000, RAIL_VOLTAGE_LEVEL_NOM,        { 5,     4,     0,     0,     0x04 }, 9 /* ClockSource_GCC_GCCGPLL4 */             ,  0 /* 806.0   Mhz */ ,  },   /* Mux[5] = GCC_GPLL4_OUT_MAIN_PWRGRP1_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCCPUSSGPLL0
 *
 * Used by:
 *   ClockDomain_GCC_GCCCPUSSGPLL0
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCCPUSSGPLL0[] =
{
  {  600000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 1,     2,     0,     0,     0xFF }, 6 /* ClockSource_GCC_GCCGPLL0 */             ,  0 /* 600.0   Mhz */ ,  },   /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP9_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCDPM
 *
 * Used by:
 *   ClockDomain_GCC_GCCDPM
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCDPM[] =
{
  {  200000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     3,     0,     0,     0xFF }, 6 /* ClockSource_GCC_GCCGPLL0 */             ,  0 /* 300.0   Mhz */ ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP118_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCGPUMEMNOCGFX
 *
 * Used by:
 *   ClockDomain_GCC_GCCGPUMEMNOCGFX
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCGPUMEMNOCGFX[] =
{
  {  533000000, RAIL_VOLTAGE_LEVEL_NOM,        { 4,     4,     0,     0,     0x05 }, 7 /* ClockSource_GCC_GCCGPLL1 */             ,  0 /* 1066.0  Mhz */ ,  },   /* Mux[4] = GCC_GPLL1_OUT_MAIN_PWRGRP3_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCMEMNOC
 *
 * Used by:
 *   ClockDomain_GCC_GCCMEMNOC
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCMEMNOC[] =
{
  {  806000000, RAIL_VOLTAGE_LEVEL_NOM,        { 5,     2,     0,     0,     0x05 }, 9 /* ClockSource_GCC_GCCGPLL4 */             ,  0 /* 806.0   Mhz */ ,  },   /* Mux[5] = GCC_GPLL4_OUT_MAIN_PWRGRP3_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCMMUTCU
 *
 * Used by:
 *   ClockDomain_GCC_GCCMMUTCU
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCMMUTCU[] =
{
  {  403000000, RAIL_VOLTAGE_LEVEL_NOM,        { 5,     4,     0,     0,     0x05 }, 9 /* ClockSource_GCC_GCCGPLL4 */             ,  0 /* 806.0   Mhz */ ,  },   /* Mux[5] = GCC_GPLL4_OUT_MAIN_PWRGRP1_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCQUPV3WRAP0S0
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP0S0
 *   ClockDomain_GCC_GCCQUPV3WRAP0S1
 *   ClockDomain_GCC_GCCQUPV3WRAP0S2
 *   ClockDomain_GCC_GCCQUPV3WRAP0S3
 *   ClockDomain_GCC_GCCQUPV3WRAP0S4
 *   ClockDomain_GCC_GCCQUPV3WRAP0S5
 *   ClockDomain_GCC_GCCQUPV3WRAP0S6
 *   ClockDomain_GCC_GCCQUPV3WRAP0S7
 *   ClockDomain_GCC_GCCQUPV3WRAP1S0
 *   ClockDomain_GCC_GCCQUPV3WRAP1S1
 *   ClockDomain_GCC_GCCQUPV3WRAP1S2
 *   ClockDomain_GCC_GCCQUPV3WRAP1S3
 *   ClockDomain_GCC_GCCQUPV3WRAP1S4
 *   ClockDomain_GCC_GCCQUPV3WRAP1S5
 *   ClockDomain_GCC_GCCQUPV3WRAP1S6
 *   ClockDomain_GCC_GCCQUPV3WRAP1S7
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCQUPV3WRAP0S0[] =
{
  {    7372800, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     2,     384,   15625, 0xFF }, 6 /* ClockSource_GCC_GCCGPLL0 */             ,  0 /* 300.0   Mhz */ ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP106_CLKGEN_ACGC_CLK */
  {   14745600, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     2,     768,   15625, 0xFF }, 6 /* ClockSource_GCC_GCCGPLL0 */             ,  0 /* 300.0   Mhz */ ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP106_CLKGEN_ACGC_CLK */
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 0,     2,     0,     0,     0x00 }, 15 /* ClockSource_XO */                      ,  0 /* 19.0    Mhz */ ,  },   /* Mux[0] = BI_TCXO */
  {   48000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     2,     4,     25,    0x02 }, 6 /* ClockSource_GCC_GCCGPLL0 */             ,  0 /* 300.0   Mhz */ ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP106_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCSDCC2APPS
 *
 * Used by:
 *   ClockDomain_GCC_GCCSDCC2APPS
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCSDCC2APPS[] =
{
  {     400000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 0,     24,    1,     4,     0xFF }, 15 /* ClockSource_XO */                      ,  0 /* 19.0    Mhz */ ,  },   /* Mux[0] = BI_TCXO */
  {   25000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     24,    0,     0,     0xFF }, 6 /* ClockSource_GCC_GCCGPLL0 */             ,  0 /* 300.0   Mhz */ ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP105_CLKGEN_ACGC_CLK */
  {   50000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     12,    0,     0,     0xFF }, 6 /* ClockSource_GCC_GCCGPLL0 */             ,  0 /* 300.0   Mhz */ ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP105_CLKGEN_ACGC_CLK */
  {  100000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     6,     0,     0,     0xFF }, 6 /* ClockSource_GCC_GCCGPLL0 */             ,  0 /* 300.0   Mhz */ ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP105_CLKGEN_ACGC_CLK */
  {  202000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     { 2,     8,     0,     0,     0xFF }, 14 /* ClockSource_GCC_GCCGPLL9 */            ,  0 /* 808.0   Mhz */ ,  },   /* Mux[2] = GCC_GPLL9_OUT_MAIN */
};

/*
 * ClockDomainBSP_GCC_GCCSHRM
 *
 * Used by:
 *   ClockDomain_GCC_GCCSHRM
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCSHRM[] =
{
  {  403000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     { 5,     4,     0,     0,     0x02 }, 9 /* ClockSource_GCC_GCCGPLL4 */             ,  0 /* 806.0   Mhz */ ,  },   /* Mux[5] = GCC_GPLL4_OUT_MAIN_PWRGRP3_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCSYSNOCGCAXI
 *
 * Used by:
 *   ClockDomain_GCC_GCCSYSNOCGCAXI
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCSYSNOCGCAXI[] =
{
  {  300000000, RAIL_VOLTAGE_LEVEL_NOM,        { 1,     4,     0,     0,     0x04 }, 6 /* ClockSource_GCC_GCCGPLL0 */             ,  0 /* 600.0   Mhz */ ,  },   /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP1_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCUFSPHYAXI
 *
 * Used by:
 *   ClockDomain_GCC_GCCUFSPHYAXI
 *   ClockDomain_GCC_GCCUFSPHYICECORE
 *   ClockDomain_GCC_GCCUFSPHYUNIPROCORE
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCUFSPHYAXI[] =
{
  {  300000000, RAIL_VOLTAGE_LEVEL_NOM,        { 1,     4,     0,     0,     0xFF }, 6 /* ClockSource_GCC_GCCGPLL0 */             ,  0 /* 600.0   Mhz */ ,  },   /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP14_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCUSB30PRIMMASTER
 *
 * Used by:
 *   ClockDomain_GCC_GCCUSB30PRIMMASTER
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCUSB30PRIMMASTER[] =
{
  {  200000000, RAIL_VOLTAGE_LEVEL_NOM,        { 1,     6,     0,     0,     0xFF }, 6 /* ClockSource_GCC_GCCGPLL0 */             ,  0 /* 600.0   Mhz */ ,  },   /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP6_CLKGEN_ACGC_CLK */
};


/*=========================================================================
      Domain Source Maps
==========================================================================*/


/*=========================================================================
      Domain FMAX
==========================================================================*/


/*=========================================================================
      Domains
==========================================================================*/

ClockDomainNodeType ClockDomain_AOSSCC_AOSSCCAOP =
{
  .aBSP      = ClockDomainBSP_AOSSCC_AOSSCCAOP,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_AOSSCC_AOSSCCAOP),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(AOSS_CC_AOP_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_AOSSCC_AOSSCCEUDAT =
{
  .aBSP      = ClockDomainBSP_AOSSCC_AOSSCCEUDAT,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_AOSSCC_AOSSCCEUDAT),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(AOSS_CC_EUD_AT_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_AOSSCC_AOSSCCIBI =
{
  .aBSP      = ClockDomainBSP_AOSSCC_AOSSCCIBI,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_AOSSCC_AOSSCCIBI),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(AOSS_CC_IBI_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_AOSSCC_AOSSCCRO =
{
  .aBSP      = ClockDomainBSP_AOSSCC_AOSSCCRO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_AOSSCC_AOSSCCRO),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(AOSS_CC_RO_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_AOSSCC_AOSSCCSPMIAODSER =
{
  .aBSP      = ClockDomainBSP_AOSSCC_AOSSCCRO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_AOSSCC_AOSSCCRO),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(AOSS_CC_SPMI_AOD_SER_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_AOSSCC_AOSSCCSWAO =
{
  .aBSP      = ClockDomainBSP_AOSSCC_AOSSCCSWAO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_AOSSCC_AOSSCCSWAO),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(AOSS_CC_SWAO_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_AOSSCC_AOSSCCSWAOTS =
{
  .aBSP      = ClockDomainBSP_AOSSCC_AOSSCCRO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_AOSSCC_AOSSCCRO),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(AOSS_CC_SWAO_TS_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_APSSCC_APSSCCGOLDMUX =
{
  .aBSP      = ClockDomainBSP_APSSCC_APSSCCGOLDMUX,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_APSSCC_APSSCCGOLDMUX),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(APSS_CC_GOLD_MUX_GFMUXR),
  .nGenType  = CLOCK_DOMAIN_TYPE_MUX,
};

ClockDomainNodeType ClockDomain_APSSCC_APSSCCGOLDPLUSMUX =
{
  .aBSP      = ClockDomainBSP_APSSCC_APSSCCGOLDMUX,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_APSSCC_APSSCCGOLDMUX),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(APSS_CC_GOLD_PLUS_MUX_GFMUXR),
  .nGenType  = CLOCK_DOMAIN_TYPE_MUX,
};

ClockDomainNodeType ClockDomain_APSSCC_APSSCCL3MUX =
{
  .aBSP      = ClockDomainBSP_APSSCC_APSSCCL3MUX,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_APSSCC_APSSCCL3MUX),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(APSS_CC_L3_MUX_GFMUXR),
  .nGenType  = CLOCK_DOMAIN_TYPE_MUX,
};

ClockDomainNodeType ClockDomain_APSSCC_APSSCCSILVERMUX =
{
  .aBSP      = ClockDomainBSP_APSSCC_APSSCCSILVERMUX,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_APSSCC_APSSCCSILVERMUX),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(APSS_CC_SILVER_MUX_GFMUXR),
  .nGenType  = CLOCK_DOMAIN_TYPE_MUX,
};

ClockDomainNodeType ClockDomain_GCC_GCCAGGRENOC =
{
  .aBSP      = ClockDomainBSP_GCC_GCCAGGRENOC,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCAGGRENOC),
  .eMaster   = CLOCK_MASTER_RPMH,
  .nCGRAddr   = HWIO_ADDR(GCC_AGGRE_NOC_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCCE1 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCCE1,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCCE1),
  .eMaster   = CLOCK_MASTER_RPMH,
  .nCGRAddr   = HWIO_ADDR(GCC_CE1_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCCNOCCENTERQX =
{
  .aBSP      = ClockDomainBSP_GCC_GCCAGGRENOC,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCAGGRENOC),
  .eMaster   = CLOCK_MASTER_RPMH,
  .nCGRAddr   = HWIO_ADDR(GCC_CNOC_CENTER_QX_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCCNOCPCIEQX =
{
  .aBSP      = ClockDomainBSP_GCC_GCCAGGRENOC,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCAGGRENOC),
  .eMaster   = CLOCK_MASTER_RPMH,
  .nCGRAddr   = HWIO_ADDR(GCC_CNOC_PCIE_QX_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCCNOCPERIPH =
{
  .aBSP      = ClockDomainBSP_GCC_GCCCNOCPERIPH,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCCNOCPERIPH),
  .eMaster   = CLOCK_MASTER_RPMH,
  .nCGRAddr   = HWIO_ADDR(GCC_CNOC_PERIPH_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCCONFIGNOC =
{
  .aBSP      = ClockDomainBSP_GCC_GCCCONFIGNOC,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCCONFIGNOC),
  .eMaster   = CLOCK_MASTER_RPMH,
  .nCGRAddr   = HWIO_ADDR(GCC_CONFIG_NOC_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCCONFIGNOCDDRSSSF =
{
  .aBSP      = ClockDomainBSP_GCC_GCCCONFIGNOCDDRSSSF,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCCONFIGNOCDDRSSSF),
  .eMaster   = CLOCK_MASTER_RPMH,
  .nCGRAddr   = HWIO_ADDR(GCC_CONFIG_NOC_DDRSS_SF_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCCPUSSGPLL0 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCCPUSSGPLL0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCCPUSSGPLL0),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(GCC_CPUSS_GPLL0_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCDPM =
{
  .aBSP      = ClockDomainBSP_GCC_GCCDPM,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCDPM),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(GCC_DPM_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCGPUMEMNOCGFX =
{
  .aBSP      = ClockDomainBSP_GCC_GCCGPUMEMNOCGFX,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCGPUMEMNOCGFX),
  .eMaster   = CLOCK_MASTER_RPMH,
  .nCGRAddr   = HWIO_ADDR(GCC_GPU_MEMNOC_GFX_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCMEMNOC =
{
  .aBSP      = ClockDomainBSP_GCC_GCCMEMNOC,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCMEMNOC),
  .eMaster   = CLOCK_MASTER_RPMH,
  .nCGRAddr   = HWIO_ADDR(GCC_MEMNOC_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCMMUTCU =
{
  .aBSP      = ClockDomainBSP_GCC_GCCMMUTCU,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCMMUTCU),
  .eMaster   = CLOCK_MASTER_RPMH,
  .nCGRAddr   = HWIO_ADDR(GCC_MMU_TCU_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0S0 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP0_S0_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0S1 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP0_S1_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0S2 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP0_S2_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0S3 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP0_S3_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0S4 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP0_S4_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0S5 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP0_S5_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0S6 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP0_S6_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0S7 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP0_S7_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S0 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP1_S0_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S1 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP1_S1_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S2 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP1_S2_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S3 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP1_S3_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S4 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP1_S4_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S5 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP1_S5_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S6 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP1_S6_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S7 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP1_S7_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCSDCC2APPS =
{
  .aBSP      = ClockDomainBSP_GCC_GCCSDCC2APPS,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCSDCC2APPS),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(GCC_SDCC2_APPS_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCSHRM =
{
  .aBSP      = ClockDomainBSP_GCC_GCCSHRM,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCSHRM),
  .eMaster   = CLOCK_MASTER_RPMH,
  .nCGRAddr   = HWIO_ADDR(GCC_SHRM_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCSYSNOC =
{
  .aBSP      = ClockDomainBSP_GCC_GCCAGGRENOC,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCAGGRENOC),
  .eMaster   = CLOCK_MASTER_RPMH,
  .nCGRAddr   = HWIO_ADDR(GCC_SYS_NOC_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCSYSNOCGCAXI =
{
  .aBSP      = ClockDomainBSP_GCC_GCCSYSNOCGCAXI,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCSYSNOCGCAXI),
  .eMaster   = CLOCK_MASTER_RPMH,
  .nCGRAddr   = HWIO_ADDR(GCC_SYS_NOC_GC_AXI_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCSYSNOCSFAXI =
{
  .aBSP      = ClockDomainBSP_GCC_GCCCONFIGNOCDDRSSSF,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCCONFIGNOCDDRSSSF),
  .eMaster   = CLOCK_MASTER_RPMH,
  .nCGRAddr   = HWIO_ADDR(GCC_SYS_NOC_SF_AXI_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCUFSPHYAXI =
{
  .aBSP      = ClockDomainBSP_GCC_GCCUFSPHYAXI,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCUFSPHYAXI),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(GCC_UFS_PHY_AXI_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCUFSPHYICECORE =
{
  .aBSP      = ClockDomainBSP_GCC_GCCUFSPHYAXI,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCUFSPHYAXI),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(GCC_UFS_PHY_ICE_CORE_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCUFSPHYUNIPROCORE =
{
  .aBSP      = ClockDomainBSP_GCC_GCCUFSPHYAXI,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCUFSPHYAXI),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(GCC_UFS_PHY_UNIPRO_CORE_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};

ClockDomainNodeType ClockDomain_GCC_GCCUSB30PRIMMASTER =
{
  .aBSP      = ClockDomainBSP_GCC_GCCUSB30PRIMMASTER,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCUSB30PRIMMASTER),
  .eMaster   = CLOCK_MASTER_DEFAULT,
  .nCGRAddr   = HWIO_ADDR(GCC_USB30_PRIM_MASTER_CMD_RCGR),
  .nGenType  = CLOCK_DOMAIN_TYPE_RCG,
};


/*=========================================================================
      Clocks
==========================================================================*/

static ClockNodeType aClocks[] =
{
  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCMEMNOC                                             */
  /*-----------------------------------------------------------------------*/

  {
    .szName      = "gcc_memnoc_clk",
    .pDomain     = &ClockDomain_GCC_GCCMEMNOC,
    .nFlags      = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_MEMNOC_CBCR),
    .mHWVotable  = {0, 0},
  },
  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0S0                                       */
  /*-----------------------------------------------------------------------*/

  {
    .szName      = "gcc_qupv3_wrap0_s0_clk",
    .pDomain     = &ClockDomain_GCC_GCCQUPV3WRAP0S0,
    .nFlags      = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP0_S0_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x400},
  },
  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0S1                                       */
  /*-----------------------------------------------------------------------*/

  {
    .szName      = "gcc_qupv3_wrap0_s1_clk",
    .pDomain     = &ClockDomain_GCC_GCCQUPV3WRAP0S1,
    .nFlags      = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP0_S1_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x800},
  },
  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0S2                                       */
  /*-----------------------------------------------------------------------*/

  {
    .szName      = "gcc_qupv3_wrap0_s2_clk",
    .pDomain     = &ClockDomain_GCC_GCCQUPV3WRAP0S2,
    .nFlags      = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP0_S2_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x1000},
  },
  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0S3                                       */
  /*-----------------------------------------------------------------------*/

  {
    .szName      = "gcc_qupv3_wrap0_s3_clk",
    .pDomain     = &ClockDomain_GCC_GCCQUPV3WRAP0S3,
    .nFlags      = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP0_S3_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x2000},
  },
  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0S4                                       */
  /*-----------------------------------------------------------------------*/

  {
    .szName      = "gcc_qupv3_wrap0_s4_clk",
    .pDomain     = &ClockDomain_GCC_GCCQUPV3WRAP0S4,
    .nFlags      = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP0_S4_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x4000},
  },
  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0S5                                       */
  /*-----------------------------------------------------------------------*/

  {
    .szName      = "gcc_qupv3_wrap0_s5_clk",
    .pDomain     = &ClockDomain_GCC_GCCQUPV3WRAP0S5,
    .nFlags      = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP0_S5_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x8000},
  },
  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0S6                                       */
  /*-----------------------------------------------------------------------*/

  {
    .szName      = "gcc_qupv3_wrap0_s6_clk",
    .pDomain     = &ClockDomain_GCC_GCCQUPV3WRAP0S6,
    .nFlags      = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP0_S6_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x10000},
  },
  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0S7                                       */
  /*-----------------------------------------------------------------------*/

  {
    .szName      = "gcc_qupv3_wrap0_s7_clk",
    .pDomain     = &ClockDomain_GCC_GCCQUPV3WRAP0S7,
    .nFlags      = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP0_S7_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x20000},
  },
  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S0                                       */
  /*-----------------------------------------------------------------------*/

  {
    .szName      = "gcc_qupv3_wrap1_s0_clk",
    .pDomain     = &ClockDomain_GCC_GCCQUPV3WRAP1S0,
    .nFlags      = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP1_S0_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x400000},
  },
  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S1                                       */
  /*-----------------------------------------------------------------------*/

  {
    .szName      = "gcc_qupv3_wrap1_s1_clk",
    .pDomain     = &ClockDomain_GCC_GCCQUPV3WRAP1S1,
    .nFlags      = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP1_S1_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x800000},
  },
  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S2                                       */
  /*-----------------------------------------------------------------------*/

  {
    .szName      = "gcc_qupv3_wrap1_s2_clk",
    .pDomain     = &ClockDomain_GCC_GCCQUPV3WRAP1S2,
    .nFlags      = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP1_S2_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x1000000},
  },
  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S3                                       */
  /*-----------------------------------------------------------------------*/

  {
    .szName      = "gcc_qupv3_wrap1_s3_clk",
    .pDomain     = &ClockDomain_GCC_GCCQUPV3WRAP1S3,
    .nFlags      = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP1_S3_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x2000000},
  },
  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S4                                       */
  /*-----------------------------------------------------------------------*/

  {
    .szName      = "gcc_qupv3_wrap1_s4_clk",
    .pDomain     = &ClockDomain_GCC_GCCQUPV3WRAP1S4,
    .nFlags      = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP1_S4_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x4000000},
  },
  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S5                                       */
  /*-----------------------------------------------------------------------*/

  {
    .szName      = "gcc_qupv3_wrap1_s5_clk",
    .pDomain     = &ClockDomain_GCC_GCCQUPV3WRAP1S5,
    .nFlags      = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP1_S5_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x8000000},
  },
  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S6                                       */
  /*-----------------------------------------------------------------------*/

  {
    .szName      = "gcc_qupv3_wrap1_s6_clk",
    .pDomain     = &ClockDomain_GCC_GCCQUPV3WRAP1S6,
    .nFlags      = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP1_S6_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x10000000},
  },
  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S7                                       */
  /*-----------------------------------------------------------------------*/

  {
    .szName      = "gcc_qupv3_wrap1_s7_clk",
    .pDomain     = &ClockDomain_GCC_GCCQUPV3WRAP1S7,
    .nFlags      = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP1_S7_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x40000},
  },
  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCSHRM                                               */
  /*-----------------------------------------------------------------------*/

  {
    .szName      = "gcc_shrm_clk",
    .pDomain     = &ClockDomain_GCC_GCCSHRM,
    .nFlags      = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_SHRM_CBCR),
    .mHWVotable  = {0, 0},
  },
};


/*=========================================================================
      Functional Groups
==========================================================================*/

static ClockGroupType aClockGroups[] =
{
  {
    .szName = "core",
    .aDomains = (ClockDomainNodeType*[]){
      &ClockDomain_APSSCC_APSSCCGOLDMUX,
      &ClockDomain_APSSCC_APSSCCGOLDPLUSMUX,
      &ClockDomain_APSSCC_APSSCCL3MUX,
      &ClockDomain_APSSCC_APSSCCSILVERMUX,
    },
    .nDomains = 4,
    .nResetAddr = 0,
  },
  {
    .szName = "boot_rom",
    .aClocks = (ClockNodeType[]){
      {
        .pDomain     = &ClockDomain_GCC_GCCCONFIGNOC,
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_BOOT_ROM_AHB_CBCR),
        .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x400},
      },
    },
    .nClocks = 1,
    .nResetAddr = HWIO_ADDR(GCC_BOOT_ROM_BCR),
  },
  {
    .szName = "ddrss",
    .aClocks = (ClockNodeType[]){
      {
        .pDomain     = &ClockDomain_GCC_GCCMEMNOC,
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_MEMNOC_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .pDomain     = &ClockDomain_GCC_GCCSHRM,
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_SHRM_CBCR),
        .mHWVotable  = {0, 0},
      },
    },
    .nClocks = 2,
    .aDomains = (ClockDomainNodeType*[]){
      &ClockDomain_GCC_GCCMEMNOC,
      &ClockDomain_GCC_GCCSHRM,
    },
    .nDomains = 2,
    .nResetAddr = 0,
  },
  {
    .szName = "sdcc2",
    .aClocks = (ClockNodeType[]){
      {
        .pDomain     = &ClockDomain_GCC_GCCCNOCPERIPH,
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_SDCC2_AHB_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .pDomain     = &ClockDomain_GCC_GCCSDCC2APPS,
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_SDCC2_APPS_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_SDCC2_AT_CBCR),
        .mHWVotable  = {0, 0},
      },
    },
    .nClocks = 3,
    .aDomains = (ClockDomainNodeType*[]){
      &ClockDomain_GCC_GCCSDCC2APPS,
    },
    .nDomains = 1,
    .nResetAddr = HWIO_ADDR(GCC_SDCC2_BCR),
  },
  {
    .szName = "ufs_phy",
    .aClocks = (ClockNodeType[]){
      {
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_UFS_0_CLKREF_EN),
        .mHWVotable  = {0, 0},
      },
      {
        .pDomain     = &ClockDomain_GCC_GCCUFSPHYAXI,
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_AGGRE_UFS_PHY_AXI_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .pDomain     = &ClockDomain_GCC_GCCCONFIGNOC,
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_UFS_PHY_AHB_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .pDomain     = &ClockDomain_GCC_GCCUFSPHYAXI,
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_UFS_PHY_AXI_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .pDomain     = &ClockDomain_GCC_GCCUFSPHYICECORE,
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_UFS_PHY_ICE_CORE_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_UFS_PHY_PHY_AUX_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .nFlags      = CLOCK_FLAG_NO_POLL_AFTER_ENABLE,
        .nBranchAddr = HWIO_ADDR(GCC_UFS_PHY_RX_SYMBOL_0_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .nFlags      = CLOCK_FLAG_NO_POLL_AFTER_ENABLE,
        .nBranchAddr = HWIO_ADDR(GCC_UFS_PHY_RX_SYMBOL_1_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .nFlags      = CLOCK_FLAG_NO_POLL_AFTER_ENABLE,
        .nBranchAddr = HWIO_ADDR(GCC_UFS_PHY_TX_SYMBOL_0_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .pDomain     = &ClockDomain_GCC_GCCUFSPHYUNIPROCORE,
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_UFS_PHY_UNIPRO_CORE_CBCR),
        .mHWVotable  = {0, 0},
      },
    },
    .nClocks = 10,
    .aDomains = (ClockDomainNodeType*[]){
      &ClockDomain_GCC_GCCUFSPHYAXI,
      &ClockDomain_GCC_GCCUFSPHYICECORE,
      &ClockDomain_GCC_GCCUFSPHYUNIPROCORE,
    },
    .nDomains = 3,
    .aPowerDomains = (uint32_t[]){
      HWIO_ADDR(GCC_UFS_PHY_GDSCR),
    },
    .nPowerDomains = 1,
    .nResetAddr = HWIO_ADDR(GCC_UFS_PHY_BCR),
  },
  {
    .szName = "usb30_prim",
    .aClocks = (ClockNodeType[]){
      {
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_USB3_0_CLKREF_EN),
        .mHWVotable  = {0, 0},
      },
      {
        .pDomain     = &ClockDomain_GCC_GCCUSB30PRIMMASTER,
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_AGGRE_USB3_PRIM_AXI_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .pDomain     = &ClockDomain_GCC_GCCUSB30PRIMMASTER,
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_CFG_NOC_USB3_PRIM_AXI_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .pDomain     = &ClockDomain_GCC_GCCUSB30PRIMMASTER,
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_USB30_PRIM_MASTER_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_USB30_PRIM_MOCK_UTMI_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_USB30_PRIM_SLEEP_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_USB3_PRIM_PHY_AUX_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_USB3_PRIM_PHY_COM_AUX_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .nFlags      = CLOCK_FLAG_NO_POLL_AFTER_ENABLE,
        .nBranchAddr = HWIO_ADDR(GCC_USB3_PRIM_PHY_PIPE_CBCR),
        .mHWVotable  = {0, 0},
      },
    },
    .nClocks = 9,
    .aDomains = (ClockDomainNodeType*[]){
      &ClockDomain_GCC_GCCUSB30PRIMMASTER,
    },
    .nDomains = 1,
    .aPowerDomains = (uint32_t[]){
      HWIO_ADDR(GCC_USB30_PRIM_GDSCR),
    },
    .nPowerDomains = 1,
    .nResetAddr = HWIO_ADDR(GCC_USB30_PRIM_BCR),
  },
};

/*=========================================================================
      Enable Lists
==========================================================================*/

static uint32_t aPDEnable[] =
{
  HWIO_ADDR(GCC_ANOC_PCIE_GDSCR),
  HWIO_ADDR(GCC_IPA_GDSCR),
  HWIO_ADDR(GCC_MMNOC_GDSCR),
  HWIO_ADDR(GCC_TURING_TBU_GDSCR),
};

static uint32_t aBranchEnable[] =
{
  HWIO_ADDR(AOSS_CC_AOP_RO_CBCR),
  HWIO_ADDR(AOSS_CC_IBI_CTRL0_CBCR),
  HWIO_ADDR(AOSS_CC_IBI_CTRL1_CBCR),
  HWIO_ADDR(AOSS_CC_IBI_CTRL2_CBCR),
  HWIO_ADDR(AOSS_CC_IBI_CTRL3_CBCR),
  HWIO_ADDR(AOSS_CC_PWR_MUX_CTRL_CBCR),
  HWIO_ADDR(AOSS_CC_SPMI2_AOD_SER_CBCR),
  HWIO_ADDR(AOSS_CC_SPMI2_SER_CBCR),
  HWIO_ADDR(AOSS_CC_SPMI_AOD_SER_CBCR),
  HWIO_ADDR(AOSS_CC_SPMI_CFG_AHB_CBCR),
  HWIO_ADDR(AOSS_CC_SPMI_SER_CBCR),
  HWIO_ADDR(AOSS_CC_WCSS_TS_CBCR),
  // HWIO_ADDR(GCC_AGGRE_CNOC_PERIPH_AHB_CBCR), /* Defaults on. */
  // HWIO_ADDR(GCC_AGGRE_CNOC_PERIPH_NORTH_AHB_CBCR), /* Open Clocks   */
  // HWIO_ADDR(GCC_AGGRE_CNOC_PERIPH_WEST_AHB_CBCR), /* Open Clocks   */
  // HWIO_ADDR(GCC_AGGRE_NOC_AHB_CBCR), /* Defaults on. */
  HWIO_ADDR(GCC_AGGRE_NOC_AUDIO_TBU_CBCR),
  // HWIO_ADDR(GCC_AGGRE_NOC_AXI_CBCR), /* Defaults on. */
  // HWIO_ADDR(GCC_AGGRE_NOC_CENTER_AXI_CBCR), /* Defaults on. */
  //HWIO_ADDR(GCC_AGGRE_NOC_EAST_AXI_CBCR), /* Open Clocks   */
  // HWIO_ADDR(GCC_AGGRE_NOC_EAST_TUNNEL_CBCR), /* Open Clocks   */
  HWIO_ADDR(GCC_AGGRE_NOC_IPA_CBCR),
  // HWIO_ADDR(GCC_AGGRE_NOC_NORTH_AXI_CBCR), /* Open Clocks   */
  // HWIO_ADDR(GCC_AGGRE_NOC_NORTH_TUNNEL_CBCR), /* Open Clocks   */
  HWIO_ADDR(GCC_AGGRE_NOC_QOSGEN_EXTREF_CBCR),
  HWIO_ADDR(GCC_AGGRE_NOC_SOUTH_AHB_CFG_CBCR),
  // HWIO_ADDR(GCC_AGGRE_NOC_SOUTH_AXI_CBCR), /* Defaults on. */
  HWIO_ADDR(GCC_AGGRE_NOC_SOUTH_TUNNEL_CBCR),
  // HWIO_ADDR(GCC_AGGRE_NOC_TBU1_CBCR), /* Defaults on. */
  // HWIO_ADDR(GCC_AGGRE_NOC_TBU2_CBCR), /* Defaults on. */
  HWIO_ADDR(GCC_AGGRE_NOC_WEST_TUNNEL_CBCR),
  // HWIO_ADDR(GCC_AHB2PHY_NORTH_CBCR), /* Defaults on. */
  // HWIO_ADDR(GCC_AHB_CBCR), /* Defaults on. */
  // HWIO_ADDR(GCC_AOSS_CNOC_M_AHB_CBCR), /* Defaults on. */
  // HWIO_ADDR(GCC_AOSS_CNOC_S_AHB_CBCR), /* Defaults on. */
  // HWIO_ADDR(GCC_CFG_NOC_AH2PHY_XO_CBCR), /* Defaults on. */
  // HWIO_ADDR(GCC_CFG_NOC_AHB_CBCR), /* Defaults on. */
  // HWIO_ADDR(GCC_CFG_NOC_DCH_AHB_CBCR), /* Open Clocks   */
  // HWIO_ADDR(GCC_CFG_NOC_EAST_AHB_CBCR),  /* Open Clocks   */
  // HWIO_ADDR(GCC_CFG_NOC_LPASS_AHB_CBCR), /* Defaults on. */
  // HWIO_ADDR(GCC_CFG_NOC_LPASS_SOUTH_AHB_CBCR), /* Defaults on. */
  // HWIO_ADDR(GCC_CFG_NOC_MMNOC_AHB_CBCR),  /* Open Clocks   */
  // HWIO_ADDR(GCC_CFG_NOC_NORTH_AHB_CBCR), /* Defaults on. */
  HWIO_ADDR(GCC_CFG_NOC_PCIE_AHB_CBCR),
  // HWIO_ADDR(GCC_CFG_NOC_SOUTH_AHB_CBCR), /* Defaults on. */
 //  HWIO_ADDR(GCC_CFG_NOC_WEST_AHB_CBCR), /* Open Clocks   */
  // HWIO_ADDR(GCC_CM_PHY_REFGEN1_CBCR), /* Defaults on. */
  // HWIO_ADDR(GCC_CM_PHY_REFGEN2_CBCR), /* Defaults on. */
  // HWIO_ADDR(GCC_CNOC_APSS_QH_CBCR), /* Defaults on. */
  // HWIO_ADDR(GCC_CNOC_CENTER_GC_QX_CBCR), /* Defaults on. */
  // HWIO_ADDR(GCC_CNOC_CENTER_QX_CBCR), /* Defaults on. */
  // HWIO_ADDR(GCC_CNOC_NORTH_SF_QX_CBCR), /* Open Clocks   */
  // HWIO_ADDR(GCC_CNOC_PCIE_QX_CBCR), /* Defaults on. */
  // HWIO_ADDR(GCC_CNOC_PERIPH_CBCR), /* Defaults on. */
  // HWIO_ADDR(GCC_CNOC_PERIPH_LPASS_CBCR), /* Open Clocks   */
  // HWIO_ADDR(GCC_CNOC_PERIPH_NORTH_CBCR), /* Open Clocks   */
  // HWIO_ADDR(GCC_CNOC_PERIPH_WEST_CBCR), /* Open Clocks   */
  // HWIO_ADDR(GCC_CNOC_SF_QX_CBCR), /* Defaults on. */
  // HWIO_ADDR(GCC_CPUSS_CONFIG_NOC_SF_CBCR), /* Defaults on. */
  HWIO_ADDR(GCC_DCC_AHB_CBCR),
  // HWIO_ADDR(GCC_DDRSS_CFG_AHB_CBCR), /* Defaults on. */
  // HWIO_ADDR(GCC_DDRSS_CONFIG_NOC_SF_CBCR), /* Defaults on. */
  HWIO_ADDR(GCC_DDRSS_GPU_AXI_CBCR),
  HWIO_ADDR(GCC_DDRSS_MMNOC_HF_QX_CBCR),
  HWIO_ADDR(GCC_DDRSS_MMNOC_SF_CBCR),
  HWIO_ADDR(GCC_DDRSS_MODEM_CBCR),
  HWIO_ADDR(GCC_DDRSS_PWRCTL_CBCR),
  HWIO_ADDR(GCC_DDRSS_SNOC_GC_AXI_CBCR),
  // HWIO_ADDR(GCC_DDRSS_SNOC_SF_AXI_CBCR), /* Defaults on. */
  // HWIO_ADDR(GCC_DDRSS_TCU_CBCR), /* Defaults on. */
  HWIO_ADDR(GCC_DDRSS_TURING_Q6_AXI_CBCR),
  //HWIO_ADDR(GCC_DPM_CB_CBCR), /* Open Clock */
  //HWIO_ADDR(GCC_DPM_CBCR), /* Open Clock */
  //HWIO_ADDR(GCC_DPM_CX_AHB_CBCR), /*  Open Clock */
  //HWIO_ADDR(GCC_DPM_MX_AHB_CBCR), /*  Open Clock */
  HWIO_ADDR(GCC_GPU_CFG_AHB_CBCR),
  // HWIO_ADDR(GCC_IMEM_CFG_AHB_CBCR), /* Defaults on. */
  // HWIO_ADDR(GCC_IMEM_CFG_QX_CBCR), /* Defaults on. */
  HWIO_ADDR(GCC_IPA_2X_CBCR),
  HWIO_ADDR(GCC_IPA_AHB_CBCR),
  HWIO_ADDR(GCC_IPA_CBCR),
  HWIO_ADDR(GCC_IPA_TPDM_APB_CBCR),
  HWIO_ADDR(GCC_IPA_TPDM_AT_CBCR),
  HWIO_ADDR(GCC_IPA_XO_CBCR),
  // HWIO_ADDR(GCC_MEMNOC_CBCR), /* Defaults on. */
  // HWIO_ADDR(GCC_MEMRED_P2S_CBCR), /* Defaults on. */
  HWIO_ADDR(GCC_MMNOC_HF_AHB_CFG_CBCR),
  HWIO_ADDR(GCC_MMNOC_HF_AT_CBCR),
  HWIO_ADDR(GCC_MMNOC_HF_PWRCTL_CBCR),
  HWIO_ADDR(GCC_MMNOC_HF_QX_CBCR),
  HWIO_ADDR(GCC_MMNOC_HF_TSCTR_CBCR),
  HWIO_ADDR(GCC_MMNOC_QOSGEN_EXTREF_CBCR),
  HWIO_ADDR(GCC_MMNOC_SF_AHB_CFG_CBCR),
  HWIO_ADDR(GCC_MMNOC_SF_AT_CBCR),
  HWIO_ADDR(GCC_MMNOC_SF_CBCR),
  HWIO_ADDR(GCC_MMNOC_SF_PWRCTL_CBCR),
  HWIO_ADDR(GCC_MMNOC_SF_TSCTR_CBCR),
  HWIO_ADDR(GCC_MMNOC_TBU_HF0_CBCR),
  HWIO_ADDR(GCC_MMNOC_TBU_HF1_CBCR),
  HWIO_ADDR(GCC_MMNOC_TBU_HF2_CBCR),
  HWIO_ADDR(GCC_MMNOC_TBU_HF3_CBCR),
  HWIO_ADDR(GCC_MMNOC_TBU_SF0_CBCR),
  HWIO_ADDR(GCC_MMNOC_TBU_SF1_CBCR),
  HWIO_ADDR(GCC_MMSS_QM_AHB_CBCR),
  HWIO_ADDR(GCC_MMSS_QMIP_CORE_CBCR),
  // HWIO_ADDR(GCC_MMU_TCU_CBCR), /* Defaults on. */
  HWIO_ADDR(GCC_MSS_Q6_MEMNOC_AXI_CBCR),
  HWIO_ADDR(GCC_NOC_CENTER_DCD_XO_CBCR),
  HWIO_ADDR(GCC_NOC_DCH_DCD_XO_CBCR),
  HWIO_ADDR(GCC_NOC_EAST_DCD_XO_CBCR),
  HWIO_ADDR(GCC_NOC_LPASS_DCD_XO_CBCR),
  HWIO_ADDR(GCC_NOC_MMNOC_CNOC_DCD_XO_CBCR),
  HWIO_ADDR(GCC_NOC_MMNOC_HF_DCD_XO_CBCR),
  HWIO_ADDR(GCC_NOC_MMNOC_SF_DCD_XO_CBCR),
  HWIO_ADDR(GCC_NOC_NORTH_DCD_XO_CBCR),
  HWIO_ADDR(GCC_NOC_SOUTH_DCD_XO_CBCR),
  HWIO_ADDR(GCC_NOC_WEST_DCD_XO_CBCR),
  HWIO_ADDR(GCC_PIMEM_AHB_CBCR),
  HWIO_ADDR(GCC_PIMEM_AXI_CBCR),
  HWIO_ADDR(GCC_PMU_AHB_CBCR),
  HWIO_ADDR(GCC_PMU_CORE_CBCR),
  HWIO_ADDR(GCC_QREFS_VBG_CAL_CBCR),
  HWIO_ADDR(GCC_RBCPR_CX_AHB_CBCR),
  HWIO_ADDR(GCC_RBCPR_CX_CBCR),
  HWIO_ADDR(GCC_RBCPR_MMCX_AHB_CBCR),
  HWIO_ADDR(GCC_RBCPR_MMCX_CBCR),
  HWIO_ADDR(GCC_RBCPR_MXA_AHB_CBCR),
  HWIO_ADDR(GCC_RBCPR_MXA_CBCR),
  HWIO_ADDR(GCC_RBCPR_MXC_AHB_CBCR),
  HWIO_ADDR(GCC_RBCPR_MXC_CBCR),
  HWIO_ADDR(GCC_SHRM_CBCR),
  // HWIO_ADDR(GCC_SLEEP_CBCR), /* Defaults on. */
  // HWIO_ADDR(GCC_SYS_NOC_AHB_CFG_CBCR), /* Defaults on. */
  // HWIO_ADDR(GCC_SYS_NOC_AXI_CBCR), /* Defaults on. */
  // HWIO_ADDR(GCC_SYS_NOC_GC_AXI_CBCR), /* Defaults on. */
  HWIO_ADDR(GCC_SYS_NOC_QOSGEN_EXTREF_CBCR),
  // HWIO_ADDR(GCC_SYS_NOC_SF_AXI_CBCR), /* Defaults on. */
  // HWIO_ADDR(GCC_TCSR_ACC_SERIAL_CBCR), /* Defaults on. */
  // HWIO_ADDR(GCC_TCU_CFG_QX_CBCR), /* Defaults on. */
  HWIO_ADDR(GCC_TURING_Q6_TBU0_CBCR),
  HWIO_ADDR(GCC_TURING_Q6_TBU1_CBCR),
  // HWIO_ADDR(GCC_XO_CBCR), /* Defaults on. */
  // HWIO_ADDR(GCC_XO_DIV16_CBCR), /* Defaults on. */
  // HWIO_ADDR(GPUCC_GPU_CC_RBCPR_AHB_CBCR), /* Defaults on. */
  HWIO_ADDR(GPUCC_GPU_CC_RBCPR_CBCR),
};

static HAL_clk_xbl_RegisterMaskType aBranchVote[] =
{
  /*
   * gcc_aggre_noc_pcie_tbu_clk
   * gcc_ce1_ahb_clk
   * gcc_ce1_axi_clk
   * gcc_ce1_clk
   * gcc_cfg_noc_pcie_anoc_ahb_clk
   * gcc_cpuss_ahb_clk
   * gcc_ddrss_pcie_sf_tbu_clk
   * gcc_prng_ahb_clk
   * gcc_sys_noc_cpuss_ahb_clk
   * gcc_tcsr_ahb_clk
   * gcc_tlmm_ahb_clk
   * gcc_tlmm_clk
   */
   { HWIO_ADDR(GCC_BOOT_CLK_BRANCH_ENA_VOTE), 0x3C217B },

  /*
   * gcc_anoc_pcie_pwrctl_clk
   * gcc_noc_pcie_north_dcd_xo_clk
   * gcc_qmip_aggre_noc_ahb_clk
   * gcc_qupv3_wrap0_core_2x_clk
   * gcc_qupv3_wrap0_core_clk
   * gcc_qupv3_wrap1_core_2x_clk
   * gcc_qupv3_wrap1_core_clk
   * gcc_qupv3_wrap_0_m_ahb_clk
   * gcc_qupv3_wrap_0_s_ahb_clk
   * gcc_qupv3_wrap_1_m_ahb_clk
   * gcc_qupv3_wrap_1_s_ahb_clk
   */
   { HWIO_ADDR(GCC_BOOT_CLK_BRANCH_ENA_VOTE_1), 0xE03C03C0 },

  /*
   * gcc_anoc_pcie_qosgen_extref_clk
   * gcc_ddrss_mss_q6_axi_clk
   * gcc_ddrss_wpss_axi_clk
   * gcc_q6_noc_mss_q6_axi_clk
   * gcc_q6_noc_wpss_axi_clk
   */
   { HWIO_ADDR(GCC_BOOT_CLK_BRANCH_ENA_VOTE_2), 0x392000 },
};

/*=========================================================================
      Main BSP
==========================================================================*/

ClockBSPType ClockBSP =
{
  .aClocks           = aClocks,
  .nNumClocks        = SIZEOF_ARRAY(aClocks),
  .aSources          = aSources,
  .nNumSources       = SIZEOF_ARRAY(aSources),
  .nFlags            = 0x0,
  .SafeMuxConfig     = { 0, 2, 0, 0 },
  .aClockGroups      = aClockGroups,
  .nNumClockGroups   = SIZEOF_ARRAY(aClockGroups),
  .aPDEnable         = aPDEnable,
  .nNumPDEnables     = SIZEOF_ARRAY(aPDEnable),
  .aBranchEnable     = aBranchEnable,
  .nNumBranchEnables = SIZEOF_ARRAY(aBranchEnable),
  .aBranchVote       = aBranchVote,
  .nNumBranchVotes   = SIZEOF_ARRAY(aBranchVote),
};

