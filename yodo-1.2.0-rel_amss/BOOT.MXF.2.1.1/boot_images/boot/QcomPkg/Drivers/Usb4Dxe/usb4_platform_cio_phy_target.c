/**---------------------------------------------------------------------------
 *
 *  @file  :  usb4_platform_cio_phy.cpp
 *
 *  @brief :  usb4 PHY implementation
 *
 *   Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/

#include <Protocol/EFIUsb4Config.h>
#include <Library/MemoryAllocationLib.h>
#include <Usb4Log.h>
#include <Usb4Utils.h>
//#include "VVHAL_usb4_timer.h"
//#include "VVHAL_usb4_logger.h"
//#include "VVHAL_usb4_utils.h"
#include "Usb4Hwio.h"
#include "HALhwio.h"
#include "hwio_qusb4phy_swi.h"
#include "hwio_qusb4phy_module_names.h"
#include "hwio_refgen_swi.h"
#include "usb4_platform.h" // Absorbed usb4_platform_cio_phy

//#include "VVHAL_usb4_hwio.h"
//#include "VVHAL_usb4_hwioreg_core.h"


// Add this definition to avoid use of string names in entry.reg_name
#define USB4_TINY_BUILD


/* Offset from start of relevant module */
#define USB4_PHY_REG_NAME(reg_name)\
 AHB2PHY_0QUSB4PHY_##reg_name

#define USB4_PHY_MODULE_NAME(reg_name)\
 MODULE_OF_##reg_name

/* Offset from start of relevant module */
#define USB4_PHY_REG_OFFSET(reg_name)\
 HWIO_AHB2PHY_0QUSB4PHY_##reg_name##_OFFS

#define USB4_PHY_MODULE_OFFSET(module_name)\
    AHB2PHY_0QUSB4PHY_##module_name##_REG_BASE_OFFS

#define USB4_PHY_MODULE_ADDRESS(module_name) \
     (usb4_platform_cio_phy_ctx->m_phyBaseAddress + USB4_PHY_MODULE_OFFSET(module_name))

#define USB4_PHY_REGISTER_BASE(reg_name) \
        USB4_PHY_MODULE_ADDRESS(USB4_PHY_MODULE_NAME(reg_name))

#define USB4_PHY_REGISTER_OFFSET(module_name, reg_name) \
     (USB4_PHY_MODULE_OFFSET(module_name) + USB4_PHY_REG_OFFSET(reg_name))

#if 0
#define USB4_PHY_SEQUENCE_ENTRY(reg_name, reg_value) \
     {USB4_PHY_REGISTER_OFFSET(MODULE_OF_##reg_name, reg_name), reg_value, 0, #reg_name}

#define USB4_PHY_SEQUENCE_ENTRY_EX(reg_name, reg_value, delay_us) \
     {USB4_PHY_REGISTER_OFFSET(MODULE_OF_##reg_name, reg_name), reg_value, delay_us, #reg_name}

#ifndef USB4_TINY_BUILD
#define USB4_PHY_PRINT_ENTRY(entry) \
                USB4_LOG_DEBUG("data.out eaxi:0x%x %%LONG 0x%x    ;%s\n", \
                  USB4_LOWER32(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset), entry.reg_value, entry.reg_name);
#else  /* USB4_TINY_BUILD */
#define USB4_PHY_PRINT_ENTRY (entry)
#endif /* USB4_TINY_BUILD */
#endif

#define USB4_PHY_SEQUENCE_ENTRY(reg_name, reg_value) \
     {USB4_PHY_REGISTER_OFFSET(MODULE_OF_##reg_name, reg_name), reg_value, 0}

#define USB4_PHY_SEQUENCE_ENTRY_EX(reg_name, reg_value, delay_us) \
     {USB4_PHY_REGISTER_OFFSET(MODULE_OF_##reg_name, reg_name), reg_value, delay_us}

#define USB4_PHY_PRINT_ENTRY(entry) \
  Usb4Log2(USB4_LOG_PHY, Usb4PhyPrint__Params__addr_val, 0, \
    USB4_LOWER32(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset), entry.reg_value);


/* ==================   Refgen MACROS  ====================*/

#define USB4_REFGEN_OFFSET(phy, refgen, reg_name)\
        HWIO_AHB2PHY_##phy##PHY_REFGEN_##refgen##_##reg_name##_OFFS

#define USB4_REFGEN_MODULE_OFFSET(phy, refgen)\
        AHB2PHY_##phy##PHY_REFGEN_##refgen##_PHY_REFGEN_##refgen##_CM_PHY_REFGEN_REG_BASE_OFFS

#define USB4_REFGEN_REGISTER_OFFSET(phy, refgen, reg_name) \
     (USB4_REFGEN_MODULE_OFFSET(phy, refgen) + USB4_REFGEN_OFFSET(phy, refgen, reg_name))

#ifndef USB4_TINY_BUILD
#define USB4_REFGEN_SEQUENCE_ENTRY(phy, refgen, reg_name, reg_value) \
     {USB4_REFGEN_REGISTER_OFFSET(phy, refgen, reg_name), reg_value, 0, #reg_name }
#else  /* USB4_TINY_BUILD */
#define USB4_REFGEN_SEQUENCE_ENTRY(phy, refgen, reg_name, reg_value) \
     {USB4_REFGEN_REGISTER_OFFSET(phy, refgen, reg_name), reg_value, 0}
#endif /* USB4_TINY_BUILD */



typedef struct
{
    UINT32 reg_offset;
    UINT32 reg_value;
    UINT32 delay_us; /* Delay to take after a write */
#ifndef USB4_TINY_BUILD
    const char *reg_name; /**< NULL terminated string containing the register name*/
#endif                    /* USB4_POR_TEST_REDUCE_MEMORY */
} USB4_phy_sequence_entry;

const USB4_phy_sequence_entry assert_reset[] = {
            USB4_PHY_SEQUENCE_ENTRY(USB43DP_COM_SW_RESET , 0x01),
            USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_SW_RESET    , 0x01)
    };

const USB4_phy_sequence_entry deassert_reset[] = {
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_COM_PHY_MODE_CTRL   , 0x04),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_COM_RESET_OVRD_CTRL1, 0x15),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_COM_POWER_DOWN_CTRL , 0x01),
        USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_POWER_DOWN_CONTROL , 0x01)
    };

const USB4_phy_sequence_entry start_phy[] = {
            USB4_PHY_SEQUENCE_ENTRY(USB43DP_COM_SW_RESET   , 0x00),
            USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_SW_RESET      , 0x00),
            USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_START_CONTROL , 0x03),
    };

const USB4_phy_sequence_entry configure_phy_no_ssc[] = {
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_SSC_EN_CENTER, 0x0),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_SSC_PER1,      0x0)
    };
const USB4_phy_sequence_entry configure_phy_usb4_ssc[] = {
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_SSC_EN_CENTER, 0x01),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_SSC_PER1,      0x31)
    };
const USB4_phy_sequence_entry configure_phy_tbt3_ssc[] = {
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_SSC_EN_CENTER, 0x01),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_SSC_PER1,      0x0b)
    };

const USB4_phy_sequence_entry configure_phy_1[] = {
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_SSC_PER2,            0x01 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_SSC_STEP_SIZE1_MODE0,0xF1 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_SSC_STEP_SIZE2_MODE0,0x0C ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_SSC_STEP_SIZE1_MODE1,0x3E ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_SSC_STEP_SIZE2_MODE1,0x0F ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_SYSCLK_BUF_ENABLE,   0x0A ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_CP_CTRL_MODE0,       0x02 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_CP_CTRL_MODE1,       0x02 ),
    };

uint32 b_usb4_override_pll_sequence = TRUE;

const USB4_phy_sequence_entry configure_phy_pll_original[] = {
    USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_PLL_RCTRL_MODE0,     0x16 ),
    USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_PLL_RCTRL_MODE1,     0x16 ),
    USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_PLL_CCTRL_MODE0,     0x36 ),
    USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_PLL_CCTRL_MODE1,     0x36 ),
};

const USB4_phy_sequence_entry configure_phy_pll_modified[] = {
    USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_PLL_RCTRL_MODE0,     0x1F ),
    USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_PLL_RCTRL_MODE1,     0x1F ),
    USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_PLL_CCTRL_MODE0,     0x3F ),
    USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_PLL_CCTRL_MODE1,     0x3F ),
};

const USB4_phy_sequence_entry configure_phy_diff_clock = USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_SYSCLK_EN_SEL,0x04);
const USB4_phy_sequence_entry configure_phy_se_clock =   USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_SYSCLK_EN_SEL,0x1A);

const USB4_phy_sequence_entry configure_phy_2[] = {
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_LOCK_CMP_EN,0x04 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_LOCK_CMP1_MODE0,0x34 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_LOCK_CMP2_MODE0,0x82 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_LOCK_CMP1_MODE1,0x46 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_LOCK_CMP2_MODE1,0x86 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_DEC_START_MODE0,0x04 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_DEC_START_MSB_MODE0,0x01 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_DEC_START_MODE1,0x0C ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_DEC_START_MSB_MODE1,0x01 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_DIV_FRAC_START1_MODE0,0xAB ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_DIV_FRAC_START2_MODE0,0xAA ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_DIV_FRAC_START3_MODE0,0x06 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_DIV_FRAC_START1_MODE1,0x00 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_DIV_FRAC_START2_MODE1,0xE0 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_DIV_FRAC_START3_MODE1,0x08 ),
    };

const USB4_phy_sequence_entry configure_phy_usb4_freq = USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_VCO_TUNE_MAP,0x00);
const USB4_phy_sequence_entry configure_phy_tbt3_freq = USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_VCO_TUNE_MAP,0x06);

const USB4_phy_sequence_entry configure_phy_3[] = {
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_VCO_TUNE1_MODE0                        , 0xBA ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_VCO_TUNE2_MODE0                        , 0x00 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_VCO_TUNE1_MODE1                        , 0x3D ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_VCO_TUNE2_MODE1                        , 0x00 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_HSCLK_SEL                              , 0x11 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_HSCLK_HS_SWITCH_SEL                    , 0x00 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_CORECLK_DIV_MODE0                      , 0x04 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_CORECLK_DIV_MODE1                      , 0x04 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_CMN_CONFIG                             , 0x76 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_CORE_CLK_EN                            , 0x70 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_PLL_IVCO                               , 0x0F ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_INTEGLOOP_GAIN0_MODE0                  , 0x20 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_INTEGLOOP_GAIN0_MODE1                  , 0x20 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_TXA_LANE_MODE_1                         , 0xF5 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_TXA_LANE_MODE_2                         , 0xC2 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_TXA_LANE_MODE_3                         , 0x10 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_SIGDET_CNTRL                        , 0x04 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_SIGDET_DEGLITCH_CNTRL               , 0x0E ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_SIGDET_ENABLES                      , 0x00 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_RX_MODE_RATE2_B0                    , 0xE4 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_RX_MODE_RATE2_B1                    , 0xE4 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_RX_MODE_RATE2_B2                    , 0xE4 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_RX_MODE_RATE2_B3                    , 0x23 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_RX_MODE_RATE2_B4                    , 0x34 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_RX_MODE_RATE2_B5                    , 0x30 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_RX_MODE_RATE2_B6                    , 0x8E ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_RX_MODE_RATE2_B7                    , 0x00 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_RX_MODE_RATE3_B0                    , 0xB7 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_RX_MODE_RATE3_B1                    , 0x77 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_RX_MODE_RATE3_B2                    , 0xAF ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_RX_MODE_RATE3_B3                    , 0x97 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_RX_MODE_RATE3_B4                    , 0x6F ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_RX_MODE_RATE3_B5                    , 0x8A ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_RX_MODE_RATE3_B6                    , 0xFF ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_RX_MODE_RATE3_B7                    , 0x00 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_UCDR_FASTLOCK_COUNT_LOW_RATE2       , 0x18 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_UCDR_FASTLOCK_COUNT_HIGH_RATE2      , 0x0A ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_UCDR_FASTLOCK_COUNT_LOW_RATE3       , 0x30 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_UCDR_FASTLOCK_COUNT_HIGH_RATE3      , 0x14 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_UCDR_PI_CTRL1                       , 0xE0 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_UCDR_PI_CTRL2                       , 0x48 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_UCDR_SB2_GAIN2_RATE2                , 0x18 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_UCDR_SB2_GAIN1_RATE3                , 0x1F ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_UCDR_SB2_GAIN2_RATE3                , 0x1F ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_RX_IVCM_CAL_CODE_OVERRIDE           , 0x00 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_RX_IVCM_CAL_CTRL2                   , 0x80 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_RX_SUMMER_CAL_SPD_MODE              , 0x1B ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_CTLE_POST_CAL_OFFSET            , 0x28 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_UCDR_PI_CONTROLS                    , 0x15 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_UCDR_FO_GAIN_RATE3                  , 0x05 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_UCDR_SO_GAIN_RATE3                  , 0x04 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_RX_IVCM_POSTCAL_OFFSET              , 0x78 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_VGA_CAL_CNTRL1                      , 0x00 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_VGA_CAL_MAN_VAL                     , 0x0F ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_DAC_ENABLE1                     , 0xCC ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_DAC_ENABLE2                     , 0x08 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_3                               , 0x45 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_TAP3_CTRL                       , 0x06 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_TAP4_CTRL                       , 0x06 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_TAP5_CTRL                       , 0x06 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_GM_CAL                              , 0x0F ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_TXB_LANE_MODE_1                         , 0xF5 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_TXB_LANE_MODE_2                         , 0xC2 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_TXB_LANE_MODE_3                         , 0x10 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_SIGDET_CNTRL                        , 0x04 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_SIGDET_DEGLITCH_CNTRL               , 0x0E ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_SIGDET_ENABLES                      , 0x00 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_RX_MODE_RATE2_B0                    , 0xE4 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_RX_MODE_RATE2_B1                    , 0xE4 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_RX_MODE_RATE2_B2                    , 0xE4 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_RX_MODE_RATE2_B3                    , 0x23 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_RX_MODE_RATE2_B4                    , 0x34 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_RX_MODE_RATE2_B5                    , 0x30 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_RX_MODE_RATE2_B6                    , 0x8E ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_RX_MODE_RATE2_B7                    , 0x00 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_RX_MODE_RATE3_B0                    , 0xB7 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_RX_MODE_RATE3_B1                    , 0x77 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_RX_MODE_RATE3_B2                    , 0xAF ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_RX_MODE_RATE3_B3                    , 0x97 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_RX_MODE_RATE3_B4                    , 0x6F ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_RX_MODE_RATE3_B5                    , 0x8A ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_RX_MODE_RATE3_B6                    , 0xFF ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_RX_MODE_RATE3_B7                    , 0x00 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_UCDR_FASTLOCK_COUNT_LOW_RATE2       , 0x18 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_UCDR_FASTLOCK_COUNT_HIGH_RATE2      , 0x0A ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_UCDR_FASTLOCK_COUNT_LOW_RATE3       , 0x30 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_UCDR_FASTLOCK_COUNT_HIGH_RATE3      , 0x14 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_UCDR_PI_CTRL1                       , 0xE0 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_UCDR_PI_CTRL2                       , 0x48 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_UCDR_SB2_GAIN2_RATE2                , 0x18 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_UCDR_SB2_GAIN1_RATE3                , 0x1F ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_UCDR_SB2_GAIN2_RATE3                , 0x1F ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_RX_IVCM_CAL_CODE_OVERRIDE           , 0x00 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_RX_IVCM_CAL_CTRL2                   , 0x80 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_RX_SUMMER_CAL_SPD_MODE              , 0x1B ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_CTLE_POST_CAL_OFFSET            , 0x28 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_UCDR_PI_CONTROLS                    , 0x15 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_UCDR_FO_GAIN_RATE3                  , 0x05 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_UCDR_SO_GAIN_RATE3                  , 0x04 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_RX_IVCM_POSTCAL_OFFSET              , 0x78 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_VGA_CAL_CNTRL1                      , 0x00 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_VGA_CAL_MAN_VAL                     , 0x0F ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_DAC_ENABLE1                     , 0xCC ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_DAC_ENABLE2                     , 0x08 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_3                               , 0x45 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_TAP3_CTRL                       , 0x06 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_TAP4_CTRL                       , 0x06 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_TAP5_CTRL                       , 0x06 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_GM_CAL                              , 0x0F ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_LFPS_DET_HIGH_COUNT_VAL                        , 0xF8 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_REFGEN_REQ_CONFIG1                             , 0x05 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_RX_SIGDET_LVL                                  , 0xAA ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_RX_SIGDET_DTCT_CNTRL                           , 0x1F ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_Q_PI_INTRINSIC_BIAS_RATE32          , 0x3F ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_Q_PI_INTRINSIC_BIAS_RATE32          , 0x3F ),
        // USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_TXA_TX_DRV_LVL                           , 0x30 ),
        // USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_TXB_TX_DRV_LVL                           , 0x30 ),
        // USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_AUXDATA_TB                           , 0xFF ),
        // USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_AUXDATA_TB                           , 0xFF ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_RX_INTERFACE_MODE                   , 0x05),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_RX_INTERFACE_MODE                   , 0x05),
        USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_POWER_STATE_CONFIG2                            , 0x3D),
        USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_L0_INSIG_SW_CTRL1                              , 0x01 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_L1_INSIG_SW_CTRL1                              , 0x01 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_L0_INSIG_MX_CTRL1                              , 0x00 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_L1_INSIG_MX_CTRL1                              , 0x00 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_FOM_EQ_CONFIG1                                 , 0xFF),
        USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_FOM_EQ_CONFIG2                                 , 0xDF),
        USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_FOM_EQ_CONFIG3                                 , 0x1F),
        USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_FOM_EQ_CONFIG4                                 , 0x11),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_EOM_CTRL                            , 0x20 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_EOM_CTRL                            , 0x20 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_CMN_IPTRIM                             , 0x12 ),

        USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_G3_EQ_CONFIG3                                  , 0x32 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_VTHRESH_CAL_MAN_VAL_RATE3           , 0x78 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_1                               , 0x00 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_2                               , 0x20 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_TAP3_MANVAL_KTAP                , 0x00 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_TAP4_MANVAL_KTAP                , 0x00 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_TAP5_MANVAL_KTAP                , 0x00 ),

        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_VTHRESH_CAL_MAN_VAL_RATE3           , 0x78 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_1                               , 0x00 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_2                               , 0x20 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_TAP3_MANVAL_KTAP                , 0x00 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_TAP4_MANVAL_KTAP                , 0x00 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_TAP5_MANVAL_KTAP                , 0x00 ),

        USB4_PHY_SEQUENCE_ENTRY(USB4_QSERDES_PLL_SVS_MODE_CLK_SEL                       , 0x0A ),

    
        /* This is not documented yed - need to enable FLL clock generation */
        //USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_WAKEUP_CLK_CONFIG1                             , 0x01 ),
    };

BOOLEAN g_usb4_override_dfe_rxa = FALSE;//TRUE;
const UINT32 g_usb4_rxa_vth =      0x7F;
const UINT32 g_usb4_rxa_dfe_tap1 = 0x04;
const UINT32 g_usb4_rxa_dfe_tap2 = 0x03;
const UINT32 g_usb4_rxa_dfe_tap3 = 0x00;
const UINT32 g_usb4_rxa_dfe_tap4 = 0x0F;
const UINT32 g_usb4_rxa_dfe_tap5 = 0x00;

BOOLEAN g_usb4_override_dfe_rxb = FALSE;//TRUE;
const UINT32 g_usb4_rxb_vth =      0x7B;
const UINT32 g_usb4_rxb_dfe_tap1 = 0x02;
const UINT32 g_usb4_rxb_dfe_tap2 = 0x01;
const UINT32 g_usb4_rxb_dfe_tap3 = 0x01;
const UINT32 g_usb4_rxb_dfe_tap4 = 0x0F;
const UINT32 g_usb4_rxb_dfe_tap5 = 0x00;


USB4_phy_sequence_entry configure_phy_dfe_override_rxa[]={
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_EOM_CTRL                            , 0x20 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_RX_MARG_CTRL2                       , 0xC0 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_AUXDATA_TB                          , 0x00 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_VTHRESH_CAL_CNTRL2                  , 0x1F ),

        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_DAC_ENABLE1                     , 0x88 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_DAC_ENABLE2                     , 0x08 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_RCLK_AUXDATA_SEL                    , 0xC0 ),

        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_3                               , 0x23),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_4                               , 0xAA),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_4                               , 0xAF),

        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_TAP3_CTRL                       , 0xAC),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_TAP3_CTRL                       , 0x3C),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_TAP4_CTRL                       , 0xAC),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_TAP4_CTRL                       , 0x3C),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_TAP5_CTRL                       , 0xAC),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_TAP5_CTRL                       , 0x3C),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_VTHRESH_CAL_CNTRL1                  , 0x14),

        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_VTHRESH_CAL_CNTRL1                  , 0x14),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_3                               , 0x23),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_TAP3_CTRL                       , 0xAc),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_TAP4_CTRL                       , 0xAc),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_TAP5_CTRL                       , 0xAc),

        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_VTHRESH_CAL_MAN_VAL_RATE3           , g_usb4_rxa_vth ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_1                               , g_usb4_rxa_dfe_tap1 << 3),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_2                               , g_usb4_rxa_dfe_tap2 << 3),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_TAP3_MANVAL_KTAP                , g_usb4_rxa_dfe_tap3 << 3),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_TAP4_MANVAL_KTAP                , g_usb4_rxa_dfe_tap4 << 3),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXA_DFE_TAP5_MANVAL_KTAP                , g_usb4_rxa_dfe_tap5 << 3)
};

USB4_phy_sequence_entry configure_phy_dfe_override_rxb[]={
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_EOM_CTRL                            , 0x20 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_RX_MARG_CTRL2                       , 0xC0 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_AUXDATA_TB                          , 0x00 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_VTHRESH_CAL_CNTRL2                  , 0x1F ),

        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_DAC_ENABLE1                     , 0x88 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_DAC_ENABLE2                     , 0x08 ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_RCLK_AUXDATA_SEL                    , 0xC0 ),

        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_3                               , 0x23),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_4                               , 0xAA),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_4                               , 0xAF),

        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_TAP3_CTRL                       , 0xAC),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_TAP3_CTRL                       , 0x3C),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_TAP4_CTRL                       , 0xAC),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_TAP4_CTRL                       , 0x3C),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_TAP5_CTRL                       , 0xAC),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_TAP5_CTRL                       , 0x3C),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_VTHRESH_CAL_CNTRL1                  , 0x14),

        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_VTHRESH_CAL_CNTRL1                  , 0x14),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_3                               , 0x23),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_TAP3_CTRL                       , 0xAc),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_TAP4_CTRL                       , 0xAc),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_TAP5_CTRL                       , 0xAc),

        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_VTHRESH_CAL_MAN_VAL_RATE3           , g_usb4_rxb_vth ),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_1                               , g_usb4_rxb_dfe_tap1 << 3),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_2                               , g_usb4_rxb_dfe_tap2 << 3),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_TAP3_MANVAL_KTAP                , g_usb4_rxb_dfe_tap3 << 3),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_TAP4_MANVAL_KTAP                , g_usb4_rxb_dfe_tap4 << 3),
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_QSERDES_RXB_DFE_TAP5_MANVAL_KTAP                , g_usb4_rxb_dfe_tap5 << 3)
};

const USB4_phy_sequence_entry configure_phy_pipe_clock_disable_in_C3_independent_of_powerdown = USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_POWER_STATE_CONFIG1,0x9F);
const USB4_phy_sequence_entry configure_phy_pipe_clock_disable_in_C3_delayed_until_powerdown = USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_POWER_STATE_CONFIG1,0xDF);

const USB4_phy_sequence_entry configure_phy_4[] = {
        USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_G2_EQ_CONFIG1                        , 0x4B ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_G2_EQ_CONFIG5                        , 0x00 ),
    };

const USB4_phy_sequence_entry configure_phy_default_cable_presets[] = {
        USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_PRESET_P14_P15_PRE                  , 0x13 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_PRESET_P14_P15_POST                 , 0x13 ),
    };

const USB4_phy_sequence_entry configure_phy_linear_redriver_cable_presets[] = {
        USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_PRESET_P14_P15_PRE                  , 0x14 ),
        USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_PRESET_P14_P15_POST                 , 0x10 ),
    };

const USB4_phy_sequence_entry pcs_config_L0[] = {
        USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_L0_BIST_CTRL              , 0x00),
        USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_L0_PRBS_SEED0             , 0x3C),
        USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_L0_PRBS_SEED1             , 0x4A),
    };

const USB4_phy_sequence_entry pcs_config_L1[] = {
        USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_L1_BIST_CTRL              , 0x00),
        USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_L1_PRBS_SEED0             , 0x3C),
        USB4_PHY_SEQUENCE_ENTRY(USB4_PCS_L1_PRBS_SEED1             , 0x4A),
    };

const USB4_phy_sequence_entry eom_init_rxa[] = {
        USB4_PHY_SEQUENCE_ENTRY   (USB43DP_QSERDES_TXA_RESET_GEN_MUXES          , 0x03),
        USB4_PHY_SEQUENCE_ENTRY   (USB43DP_QSERDES_RXA_CDR_RESET_OVERRIDE       , 0x0A),
        USB4_PHY_SEQUENCE_ENTRY   (USB43DP_QSERDES_RXA_EOM_CTRL                 , 0x91),
        USB4_PHY_SEQUENCE_ENTRY   (USB43DP_QSERDES_RXA_AUX_CONTROL              , 0x40),
        USB4_PHY_SEQUENCE_ENTRY   (USB43DP_QSERDES_RXA_RCLK_AUXDATA_SEL         , 0xfc),
        USB4_PHY_SEQUENCE_ENTRY   (USB43DP_QSERDES_RXA_RX_MARG_CTRL2            , 0x80),
        USB4_PHY_SEQUENCE_ENTRY   (USB43DP_QSERDES_RXA_RX_MARG_VERTICAL_CTRL    , 0x02),
        USB4_PHY_SEQUENCE_ENTRY_EX(USB43DP_QSERDES_RXA_AUXDATA_TB               , 0x80, 1000),
        USB4_PHY_SEQUENCE_ENTRY   (USB43DP_QSERDES_RXA_RX_MARG_CTRL_4           , 0x33),
        USB4_PHY_SEQUENCE_ENTRY_EX(USB43DP_QSERDES_RXA_RX_MARG_CTRL3            , 0x4c, 1000),
        USB4_PHY_SEQUENCE_ENTRY   (USB43DP_QSERDES_RXA_RX_MARG_CTRL3            , 0x48),
        USB4_PHY_SEQUENCE_ENTRY_EX(USB43DP_QSERDES_RXA_RCLK_AUXDATA_SEL         , 0xfc, 1000),
        USB4_PHY_SEQUENCE_ENTRY   (USB43DP_QSERDES_RXA_RCLK_AUXDATA_SEL         , 0xf4)
    };

const USB4_phy_sequence_entry eom_init_rxb[] = {
        USB4_PHY_SEQUENCE_ENTRY   (USB43DP_QSERDES_TXB_RESET_GEN_MUXES          , 0x03),
        USB4_PHY_SEQUENCE_ENTRY   (USB43DP_QSERDES_RXB_CDR_RESET_OVERRIDE       , 0x0A),
        USB4_PHY_SEQUENCE_ENTRY   (USB43DP_QSERDES_RXB_EOM_CTRL                 , 0x91),
        USB4_PHY_SEQUENCE_ENTRY   (USB43DP_QSERDES_RXB_AUX_CONTROL              , 0x40),
        USB4_PHY_SEQUENCE_ENTRY   (USB43DP_QSERDES_RXB_RCLK_AUXDATA_SEL         , 0xfc),
        USB4_PHY_SEQUENCE_ENTRY   (USB43DP_QSERDES_RXB_RX_MARG_CTRL2            , 0x80),
        USB4_PHY_SEQUENCE_ENTRY   (USB43DP_QSERDES_RXB_RX_MARG_VERTICAL_CTRL    , 0x02),
        USB4_PHY_SEQUENCE_ENTRY_EX(USB43DP_QSERDES_RXB_AUXDATA_TB               , 0x80, 1000),
        USB4_PHY_SEQUENCE_ENTRY   (USB43DP_QSERDES_RXB_RX_MARG_CTRL_4           , 0x33),
        USB4_PHY_SEQUENCE_ENTRY_EX(USB43DP_QSERDES_RXB_RX_MARG_CTRL3            , 0x4c, 1000),
        USB4_PHY_SEQUENCE_ENTRY   (USB43DP_QSERDES_RXB_RX_MARG_CTRL3            , 0x48),
        USB4_PHY_SEQUENCE_ENTRY_EX(USB43DP_QSERDES_RXB_RCLK_AUXDATA_SEL         , 0xfc, 1000),
        USB4_PHY_SEQUENCE_ENTRY   (USB43DP_QSERDES_RXB_RCLK_AUXDATA_SEL         , 0xf4)
    };


const USB4_phy_sequence_entry eom_validate_rxa[] = {
        USB4_PHY_SEQUENCE_ENTRY(   USB43DP_QSERDES_RXA_RX_MARG_CTRL_4           , 0x23),
        USB4_PHY_SEQUENCE_ENTRY_EX(USB43DP_QSERDES_RXA_RX_MARG_CTRL_4           , 0x33, 1000),
        USB4_PHY_SEQUENCE_ENTRY_EX(USB43DP_QSERDES_RXA_RX_MARG_CTRL3            , 0x4c, 1000),
        USB4_PHY_SEQUENCE_ENTRY   (USB43DP_QSERDES_RXA_RX_MARG_CTRL3            , 0x48),
        USB4_PHY_SEQUENCE_ENTRY_EX(USB43DP_QSERDES_RXA_RCLK_AUXDATA_SEL         , 0xfc, 1000),
        USB4_PHY_SEQUENCE_ENTRY(   USB43DP_QSERDES_RXA_RCLK_AUXDATA_SEL         , 0xf4),
        USB4_PHY_SEQUENCE_ENTRY(   USB43DP_QSERDES_RXA_RX_MARG_CTRL_4           , 0x23)
    };

const USB4_phy_sequence_entry eom_validate_rxb[] = {
        USB4_PHY_SEQUENCE_ENTRY(   USB43DP_QSERDES_RXB_RX_MARG_CTRL_4           , 0x23),
        USB4_PHY_SEQUENCE_ENTRY_EX(USB43DP_QSERDES_RXB_RX_MARG_CTRL_4           , 0x33, 1000),
        USB4_PHY_SEQUENCE_ENTRY_EX(USB43DP_QSERDES_RXB_RX_MARG_CTRL3            , 0x4c, 1000),
        USB4_PHY_SEQUENCE_ENTRY   (USB43DP_QSERDES_RXB_RX_MARG_CTRL3            , 0x48),
        USB4_PHY_SEQUENCE_ENTRY_EX(USB43DP_QSERDES_RXB_RCLK_AUXDATA_SEL         , 0xfc, 1000),
        USB4_PHY_SEQUENCE_ENTRY(   USB43DP_QSERDES_RXB_RCLK_AUXDATA_SEL         , 0xf4),
        USB4_PHY_SEQUENCE_ENTRY(   USB43DP_QSERDES_RXB_RX_MARG_CTRL_4           , 0x23)
    };

//TODO: Do I need to configure both ref-gens per AHB PHY block?
const USB4_phy_sequence_entry configure_refgen_enable_0[] = {
        USB4_REFGEN_SEQUENCE_ENTRY(0, 0, RSM_CNTRL, 0x00),
        USB4_REFGEN_SEQUENCE_ENTRY(0, 0, RESTRIM_BYPASS_CODE, 0x4e),
        USB4_REFGEN_SEQUENCE_ENTRY(0, 1, RSM_CNTRL, 0x00),
        USB4_REFGEN_SEQUENCE_ENTRY(0, 1, RESTRIM_BYPASS_CODE, 0x4e)
    };

const USB4_phy_sequence_entry configure_refgen_enable_1[] = {
        USB4_REFGEN_SEQUENCE_ENTRY(2, 2, RSM_CNTRL, 0x00),
        USB4_REFGEN_SEQUENCE_ENTRY(2, 2, RESTRIM_BYPASS_CODE, 0x4e),
        USB4_REFGEN_SEQUENCE_ENTRY(2, 3, RSM_CNTRL, 0x00),
        USB4_REFGEN_SEQUENCE_ENTRY(2, 3, RESTRIM_BYPASS_CODE, 0x4e)
    };

const USB4_phy_sequence_entry dp_pll_base_configuration[] = {
        USB4_PHY_SEQUENCE_ENTRY(USB43DP_COM_RESET_OVRD_CTRL2         , 0x83),
        USB4_PHY_SEQUENCE_ENTRY(DP_DP_PHY_PD_CTL                     , 0x79),
    };

const USB4_phy_sequence_entry dp_pll_base_configuration_no_ssc = USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_SSC_EN_CENTER         , 0x00);
const USB4_phy_sequence_entry dp_pll_base_configuration_ssc = USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_SSC_EN_CENTER            , 0x01);

const USB4_phy_sequence_entry dp_pll_base_configuration_1[] = {
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_SSC_PER1              , 0x36),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_SSC_PER2              , 0x01),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_CP_CTRL_MODE0         , 0x06),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_CP_CTRL_MODE1         , 0x06),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_PLL_RCTRL_MODE0       , 0x16),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_PLL_RCTRL_MODE1       , 0x16),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_PLL_CCTRL_MODE0       , 0x36),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_PLL_CCTRL_MODE1       , 0x36),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_SYSCLK_EN_SEL         , 0x3B),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_LOCK_CMP_EN           , 0x08),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_DEC_START_MODE0       , 0x69),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_DEC_START_MODE1       , 0x8C),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_DIV_FRAC_START1_MODE0 , 0x00),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_DIV_FRAC_START2_MODE0 , 0x80),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_DIV_FRAC_START3_MODE0 , 0x07),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_DIV_FRAC_START1_MODE1 , 0x00),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_DIV_FRAC_START2_MODE1 , 0x00),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_DIV_FRAC_START3_MODE1 , 0x0A),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_VCO_TUNE1_MODE0       , 0xA0),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_VCO_TUNE2_MODE0       , 0x03),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_VCO_TUNE1_MODE1       , 0x85),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_VCO_TUNE2_MODE1       , 0x01),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_CORECLK_DIV_MODE0     , 0x0A),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_CORECLK_DIV_MODE1     , 0x0A),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_CMN_CONFIG            , 0x02),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_CORE_CLK_EN           , 0x30),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_CLK_ENABLE1           , 0x0C),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_BG_TIMER              , 0x0A),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE0 , 0x3F),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE0 , 0x00),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE1 , 0x3F),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE1 , 0x00),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_CLK_SELECT            , 0x30)
    };

const USB4_phy_sequence_entry DPClk8p1[] = {
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE0  , 0x45),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE0  , 0x06),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_LOCK_CMP1_MODE0       , 0x2F),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_LOCK_CMP2_MODE0       , 0x2A),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_VCO_TUNE_MAP          , 0x02),
        USB4_PHY_SEQUENCE_ENTRY(DP_DP_PHY_VCO_DIV                    , 0x00),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_HSCLK_SEL             , 0x00),

        USB4_PHY_SEQUENCE_ENTRY(DP_DP_PHY_TX2_TX3_LANE_CTL           , 0X01),
        USB4_PHY_SEQUENCE_ENTRY_EX(DP_DP_PHY_CFG                     , 0X04,  1),
        USB4_PHY_SEQUENCE_ENTRY_EX(DP_DP_PHY_CFG                     , 0X00,  1),
        USB4_PHY_SEQUENCE_ENTRY_EX(DP_DP_PHY_CFG                     , 0X08,  1),
};

const USB4_phy_sequence_entry DPClk5p4[] = {
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE1  , 0x5C),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE1  , 0x08),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_LOCK_CMP1_MODE1       , 0x1F),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_LOCK_CMP2_MODE1       , 0x1C),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_VCO_TUNE_MAP          , 0x06),
        USB4_PHY_SEQUENCE_ENTRY(DP_DP_PHY_VCO_DIV                    , 0x02),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_HSCLK_SEL             , 0x10),

        USB4_PHY_SEQUENCE_ENTRY(DP_DP_PHY_TX2_TX3_LANE_CTL           , 0X01),
        USB4_PHY_SEQUENCE_ENTRY_EX(DP_DP_PHY_CFG                     , 0X04,  1),
        USB4_PHY_SEQUENCE_ENTRY_EX(DP_DP_PHY_CFG                     , 0X00,  1),
        USB4_PHY_SEQUENCE_ENTRY_EX(DP_DP_PHY_CFG                     , 0X08,  1),
};

const USB4_phy_sequence_entry DPClk2p7[] = {
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE0  , 0x45),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE0  , 0x06),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_LOCK_CMP1_MODE0       , 0x0F),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_LOCK_CMP2_MODE0       , 0x0E),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_VCO_TUNE_MAP          , 0x02),
        USB4_PHY_SEQUENCE_ENTRY(DP_DP_PHY_VCO_DIV                    , 0x01),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_HSCLK_SEL             , 0x03),

        USB4_PHY_SEQUENCE_ENTRY(DP_DP_PHY_TX2_TX3_LANE_CTL           , 0X01),
        USB4_PHY_SEQUENCE_ENTRY_EX(DP_DP_PHY_CFG                     , 0X04,  1),
        USB4_PHY_SEQUENCE_ENTRY_EX(DP_DP_PHY_CFG                     , 0X00,  1),
        USB4_PHY_SEQUENCE_ENTRY_EX(DP_DP_PHY_CFG                     , 0X08,  1),
};

const USB4_phy_sequence_entry DPClk1p62[] = {
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE0  , 0x45),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE0  , 0x06),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_LOCK_CMP1_MODE0       , 0x6F),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_LOCK_CMP2_MODE0       , 0x08),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_VCO_TUNE_MAP          , 0x02),
        USB4_PHY_SEQUENCE_ENTRY(DP_DP_PHY_VCO_DIV                    , 0x01),
        USB4_PHY_SEQUENCE_ENTRY(DP_QSERDES_PLL_HSCLK_SEL             , 0x05),

        USB4_PHY_SEQUENCE_ENTRY(DP_DP_PHY_TX2_TX3_LANE_CTL           , 0X01),
        USB4_PHY_SEQUENCE_ENTRY_EX(DP_DP_PHY_CFG                     , 0X04,  1),
        USB4_PHY_SEQUENCE_ENTRY_EX(DP_DP_PHY_CFG                     , 0X00,  1),
        USB4_PHY_SEQUENCE_ENTRY_EX(DP_DP_PHY_CFG                     , 0X08,  1),
};



int Usb4PlatformCioPhyInit(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx, UINT32 coreIndex, UINT8* coreBaseAddress)
{
#if 0 // Deprecated
    usb4_platform_cio_phy_ctx->m_numLanes = 0; // Emulation but initialize to 0 anyway
    usb4_platform_cio_phy_ctx->m_isUsb4Device = 0; // Emulation but initialize to 0 anyway
#endif

    usb4_platform_cio_phy_ctx->m_coreIndex = coreIndex;
    usb4_platform_cio_phy_ctx->m_coreBaseAddress = coreBaseAddress;
    if(0 == usb4_platform_cio_phy_ctx->m_coreIndex)
    {
        usb4_platform_cio_phy_ctx->m_phyBaseAddress = (UINT8*)(AHB2PHY_0AHB2PHY_0_BASE);
    }
    else
    {
        /* normalized offsets for the 2nd instance:
        1. add offset of the 1st module from the 2nd instance
        2. remove the offset of the 1st module from 1st instance since we use
        only 1st instance regs */
        usb4_platform_cio_phy_ctx->m_phyBaseAddress = (UINT8*)(AHB2PHY_2AHB2PHY_2_BASE
                            + 0x3000
                            - USB4_PHY_MODULE_OFFSET(QUSB4PHY_CM_USB4_USB3_DP_CON));
    }
    return 0;
}

int Usb4PlatformCioPhyAssertReset(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx)
{
    Usb4Log(USB4_LOG_PHY, Usb4PlatformCioPhyAssertReset__Info, 0);
    for (UINT32 i=0; i< ARR_SIZE(assert_reset);++i)
    {
        USB4_phy_sequence_entry entry = assert_reset[i];
        USB4_PHY_PRINT_ENTRY(entry);
        out_dword_usb(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
    }

    return 0;
};

int Usb4PlatformCioPhyDeAssertReset(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx)
{
    Usb4Log(USB4_LOG_PHY, Usb4PlatformCioPhyDeAssertReset__Info, 0);
    for (UINT32 i=0; i< ARR_SIZE(deassert_reset);++i)
    {
        USB4_phy_sequence_entry entry = deassert_reset[i];
        USB4_PHY_PRINT_ENTRY(entry);
        out_dword_usb(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
    }

    return 0;
};

int Usb4PlatformCioPhyStart(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx, USB4_phyConfig* pPhyConfig)
{
    UINT32 elapsed_ms = 0;
    UINT32 phyStatus;
    usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;

    Usb4Log(USB4_LOG_PHY, Usb4PlatformCioPhyStart__Info, 0);
    for (UINT32 i=0; i< ARR_SIZE(start_phy);++i)
    {
        USB4_phy_sequence_entry entry = start_phy[i];
        USB4_PHY_PRINT_ENTRY(entry);
        out_dword_usb(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
    }

    /* Wait for PHY operational
     *[Russ] You can monitor USB4_PCS_PCS_STATUS1.PHYSTATUS (wait for it to go low) or USB4_PCS_PCS_STATUS1.ACTIVE_STATE_STATUS (wait for it to go high). */
    USB4_ASSERT(0 == usb4_timer_Start(&timer));
    while(elapsed_ms < 1000)
    {
        USB4_ASSERT(0 == usb4_timer_GetElapsed_ms(&timer, &elapsed_ms));
        phyStatus = HWIO_INXF(USB4_PHY_REGISTER_BASE(USB4_PCS_PCS_STATUS1), USB4_PHY_REG_NAME(USB4_PCS_PCS_STATUS1), PHYSTATUS);
        if (0 == phyStatus)
        {
            /* According to Tobey, need to wait for PLL to lock - experimental code*/
            if (USB4_DpPll_Config_Disable != pPhyConfig->dpPllCfg)
            {
                usb4_utils_timer timer;
                timer.m_source = USB4_TIMER_SOURCE_QTIMER;
                UINT8 c_ready = 0;
                UINT32 elapsed_ms = 0;

                USB4_ASSERT(0 == usb4_timer_Start(&timer));
                while(elapsed_ms < 1000)
                {
                    USB4_ASSERT(0 == usb4_timer_GetElapsed_ms(&timer, &elapsed_ms));
                    c_ready = HWIO_INXF(USB4_PHY_REGISTER_BASE(DP_QSERDES_PLL_C_READY_STATUS), USB4_PHY_REG_NAME(DP_QSERDES_PLL_C_READY_STATUS), C_READY);
                    if (1 == c_ready)
                    {
                        // USB4_LOG_INFO("DP PHY C_READY is up!\n");
                        Usb4Log(USB4_LOG_PHY, Usb4PlatformCioPhyStartDpPhyCReadyIsUp__Info, 0);
                        return 0;
                    }
                    usb4_timer_Sleep_ms(&timer, 150);
                }
                
                // USB4_ERROR_STACK_MSG(-1,"DP PHY C_READY didn't come up");
                Usb4Log(USB4_LOG_PHY, Usb4PlatformCioPhyStartDpPhyCReadyDidntComeUp__Error, 0);
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    return 0;
}

int Usb4PlatformCioPhyConfigure(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx, USB4_phyConfig* pPhyConfig)
{
#if 0
    UINT8* base = NULL;
    UINT32 val;
#endif

    usb4_platform_cio_phy_ctx->m_numLanes = pPhyConfig->numLanes;
    /* Configure REFGEN */
    USB4_ASSERT(0 == Usb4PlatformCioPhyConfigureREFGEEN(usb4_platform_cio_phy_ctx, TRUE));

    Usb4PlatformCioPhyAssertReset(usb4_platform_cio_phy_ctx);
    Usb4PlatformCioPhyDeAssertReset(usb4_platform_cio_phy_ctx);

    Usb4Log(USB4_LOG_PHY, Usb4PlatformCioPhyConfigure__Info, 0);
    if (pPhyConfig->bSscEnabled)
    {
        if (pPhyConfig->bIsUsb4Device)
        {
            for (UINT32 i=0; i< ARR_SIZE(configure_phy_usb4_ssc);++i)
            {
                USB4_phy_sequence_entry entry = configure_phy_usb4_ssc[i];
                USB4_PHY_PRINT_ENTRY(entry);
                out_dword_usb(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
            }
        }
        else
        {
            for (UINT32 i=0; i< ARR_SIZE(configure_phy_tbt3_ssc);++i)
            {
                USB4_phy_sequence_entry entry = configure_phy_tbt3_ssc[i];
                USB4_PHY_PRINT_ENTRY(entry);
                out_dword_usb(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
            }
        }
    }
    else
    {
        for (UINT32 i=0; i< ARR_SIZE(configure_phy_no_ssc);++i)
        {
            USB4_phy_sequence_entry entry = configure_phy_no_ssc[i];
            USB4_PHY_PRINT_ENTRY(entry);
            out_dword_usb(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
        }
    }

    for (UINT32 i=0; i< ARR_SIZE(configure_phy_1);++i)
    {
        USB4_phy_sequence_entry entry = configure_phy_1[i];
        USB4_PHY_PRINT_ENTRY(entry);
        out_dword_usb(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
    }

    if (TRUE == b_usb4_override_pll_sequence)
    {
        for (UINT32 i=0; i< ARR_SIZE(configure_phy_pll_modified);++i)
        {
            USB4_phy_sequence_entry entry = configure_phy_pll_modified[i];
            USB4_PHY_PRINT_ENTRY(entry);
            out_dword(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
        }
    }
    else
    {
        for (UINT32 i=0; i< ARR_SIZE(configure_phy_pll_original);++i)
        {
            USB4_phy_sequence_entry entry = configure_phy_pll_original[i];
            USB4_PHY_PRINT_ENTRY(entry);
            out_dword(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
        }
    }

    if (pPhyConfig->bUseDiffClock)
    {
        USB4_phy_sequence_entry entry = configure_phy_diff_clock;
        USB4_PHY_PRINT_ENTRY(entry);
        out_dword_usb(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
    }
    else
    {
        USB4_phy_sequence_entry entry = configure_phy_se_clock;
        USB4_PHY_PRINT_ENTRY(entry);
        out_dword_usb(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
    }

    for (UINT32 i=0; i< ARR_SIZE(configure_phy_2);++i)
    {
        USB4_phy_sequence_entry entry = configure_phy_2[i];
        USB4_PHY_PRINT_ENTRY(entry);
        out_dword_usb(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
    }

    if (pPhyConfig->bIsUsb4Device)
    {
        USB4_phy_sequence_entry entry = configure_phy_usb4_freq;
        USB4_PHY_PRINT_ENTRY(entry);
        out_dword_usb(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
    }
    else
    {
        USB4_phy_sequence_entry entry = configure_phy_tbt3_freq;
        USB4_PHY_PRINT_ENTRY(entry);
        out_dword_usb(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
    }

    for (UINT32 i=0; i< ARR_SIZE(configure_phy_3);++i)
    {
        USB4_phy_sequence_entry entry = configure_phy_3[i];
        USB4_PHY_PRINT_ENTRY(entry);
        out_dword_usb(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
    }

    if (g_usb4_override_dfe_rxa)
    {
        for (UINT32 i=0; i< ARR_SIZE(configure_phy_dfe_override_rxa);++i)
        {
            USB4_phy_sequence_entry entry = configure_phy_dfe_override_rxa[i];
            USB4_PHY_PRINT_ENTRY(entry);
            out_dword(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
        }
    }

    if (g_usb4_override_dfe_rxb)
    {
        for (UINT32 i=0; i< ARR_SIZE(configure_phy_dfe_override_rxb);++i)
        {
            USB4_phy_sequence_entry entry = configure_phy_dfe_override_rxb[i];
            USB4_PHY_PRINT_ENTRY(entry);
            out_dword(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
        }
    }

    if (pPhyConfig->pipeClockDisableInC3IndependentOfPowerdown)
    {
        USB4_phy_sequence_entry entry = configure_phy_pipe_clock_disable_in_C3_independent_of_powerdown;
        USB4_PHY_PRINT_ENTRY(entry);
        out_dword_usb(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
    }
    else
    {
        USB4_phy_sequence_entry entry = configure_phy_pipe_clock_disable_in_C3_delayed_until_powerdown;
        USB4_PHY_PRINT_ENTRY(entry);
        out_dword_usb(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
    }

    for (UINT32 i=0; i< ARR_SIZE(configure_phy_4);++i)
    {
        USB4_phy_sequence_entry entry = configure_phy_4[i];
        USB4_PHY_PRINT_ENTRY(entry);
        out_dword(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
    }

    if (pPhyConfig->useLinearRedriverCableOptimizedPreset)
    {
        for (UINT32 i=0; i< ARR_SIZE(configure_phy_linear_redriver_cable_presets);++i)
        {
            USB4_phy_sequence_entry entry = configure_phy_linear_redriver_cable_presets[i];
            USB4_PHY_PRINT_ENTRY(entry);
            out_dword(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
        }
    }
    else
    {
        for (UINT32 i=0; i< ARR_SIZE(configure_phy_default_cable_presets);++i)
        {
            USB4_phy_sequence_entry entry = configure_phy_default_cable_presets[i];
            USB4_PHY_PRINT_ENTRY(entry);
            out_dword(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
        }
    }

    USB4_ASSERT(0 == Usb4PlatformCioPhyConfigureDPPLL(usb4_platform_cio_phy_ctx, pPhyConfig));

    return  Usb4PlatformCioPhyStart(usb4_platform_cio_phy_ctx, pPhyConfig);
};

int Usb4PlatformCioPhyInitEyeMonitoring(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx, UINT32 initStage)
{
    usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;


    switch(initStage)
    {
        case 0:
            HWIO_OUTX(USB4_PHY_REGISTER_BASE(USB4_PCS_TEST_CONTROL1),
                           USB4_PHY_REG_NAME(USB4_PCS_TEST_CONTROL1),
                                             1);
            break;
        case 1:
            for (uint32 i=0; i< ARR_SIZE(pcs_config_L0);++i)
            {
                USB4_phy_sequence_entry entry = pcs_config_L0[i];
                out_dword(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
                if (entry.delay_us > 0)
                {
                    USB4_ASSERT(0==usb4_timer_Sleep_us(&timer, entry.delay_us))
                }
            }
            if (1 != usb4_platform_cio_phy_ctx->m_numLanes)
            {
                for (uint32 i=0; i< ARR_SIZE(pcs_config_L1);++i)
                {
                    USB4_phy_sequence_entry entry = pcs_config_L1[i];
                    out_dword(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
                    if (entry.delay_us > 0)
                    {
                        USB4_ASSERT(0==usb4_timer_Sleep_us(&timer, entry.delay_us))
                    }
                }
            }
            break;
        case 2:
            HWIO_OUTX(USB4_PHY_REGISTER_BASE(USB4_PCS_BIST_CTRL),
                           USB4_PHY_REG_NAME(USB4_PCS_BIST_CTRL),
                                             2);
            break;
        case 3:
        default:
            for (uint32 i=0; i< ARR_SIZE(eom_init_rxa);++i)
            {
                USB4_phy_sequence_entry entry_a = eom_init_rxa[i];
                USB4_phy_sequence_entry entry_b = eom_init_rxb[i];
                out_dword(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry_a.reg_offset, entry_a.reg_value);
                if (1 != usb4_platform_cio_phy_ctx->m_numLanes)
                {
                    out_dword(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry_b.reg_offset, entry_b.reg_value);
                }
                if (entry_a.delay_us > 0)
                {
                    USB4_ASSERT(0==usb4_timer_Sleep_us(&timer, entry_a.delay_us))
                }
            }
            break;
    }
    return 0;
}

int Usb4PlatformCioPhyStartEyeMonitoring(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx, USB4_eyeMonitorungConfigure* pEyeMonitorungConfigure)
{
//    UINT32 maxh = 0x40;
//    UINT32 maxv = 0x80;

    HWIO_OUTX(USB4_PHY_REGISTER_BASE(USB43DP_QSERDES_RXA_AUX_CONTROL),
                   USB4_PHY_REG_NAME(USB43DP_QSERDES_RXA_AUX_CONTROL),
                   pEyeMonitorungConfigure->maxh | pEyeMonitorungConfigure->hor);

    if (1 != usb4_platform_cio_phy_ctx->m_numLanes)
    {
        HWIO_OUTX(USB4_PHY_REGISTER_BASE(USB43DP_QSERDES_RXB_AUX_CONTROL),
                   USB4_PHY_REG_NAME(USB43DP_QSERDES_RXB_AUX_CONTROL),
                   pEyeMonitorungConfigure->maxh | pEyeMonitorungConfigure->hor);
    }

    HWIO_OUTX(USB4_PHY_REGISTER_BASE(USB43DP_QSERDES_RXA_AUXDATA_TB),
                   USB4_PHY_REG_NAME(USB43DP_QSERDES_RXA_AUXDATA_TB),
                   pEyeMonitorungConfigure->maxv | pEyeMonitorungConfigure->vert);

    if (1 != usb4_platform_cio_phy_ctx->m_numLanes)
    {
        HWIO_OUTX(USB4_PHY_REGISTER_BASE(USB43DP_QSERDES_RXB_AUXDATA_TB),
                   USB4_PHY_REG_NAME(USB43DP_QSERDES_RXB_AUXDATA_TB),
                   pEyeMonitorungConfigure->maxv | pEyeMonitorungConfigure->vert);
    }
    return 0;
};
int Usb4PlatformCioPhyGetEyeMonitoringStatus(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx, USB4_eyeMonitorungStatus* pEyeMonitorungStatus)
{
    usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;

    for (UINT32 i=0; i< ARR_SIZE(eom_validate_rxa);++i)
    {
        USB4_phy_sequence_entry entry_a = eom_validate_rxa[i];
        out_dword(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry_a.reg_offset, entry_a.reg_value);
        if (1 != usb4_platform_cio_phy_ctx->m_numLanes)
        {
            USB4_phy_sequence_entry entry_b = eom_validate_rxb[i];
            out_dword(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry_b.reg_offset, entry_b.reg_value);
        }
        if (entry_a.delay_us > 0)
        {
            USB4_ASSERT(0==usb4_timer_Sleep_us(&timer, entry_a.delay_us))
        }
    }

    pEyeMonitorungStatus->rxa_errors = ((0xFF &
            HWIO_INX(USB4_PHY_REGISTER_BASE(USB43DP_QSERDES_RXA_IA_ERROR_COUNTER_HIGH),
                          USB4_PHY_REG_NAME(USB43DP_QSERDES_RXA_IA_ERROR_COUNTER_HIGH))) << 8) |
           (0xFF & HWIO_INX(USB4_PHY_REGISTER_BASE(USB43DP_QSERDES_RXA_IA_ERROR_COUNTER_LOW),
                                 USB4_PHY_REG_NAME(USB43DP_QSERDES_RXA_IA_ERROR_COUNTER_LOW)));
    if (1 != usb4_platform_cio_phy_ctx->m_numLanes)
    {
        pEyeMonitorungStatus->rxb_errors = ((0xFF &
            HWIO_INX(USB4_PHY_REGISTER_BASE(USB43DP_QSERDES_RXB_IA_ERROR_COUNTER_HIGH),
                          USB4_PHY_REG_NAME(USB43DP_QSERDES_RXB_IA_ERROR_COUNTER_HIGH))) << 8) |
           (0xFF & HWIO_INX(USB4_PHY_REGISTER_BASE(USB43DP_QSERDES_RXB_IA_ERROR_COUNTER_LOW),
                                 USB4_PHY_REG_NAME(USB43DP_QSERDES_RXB_IA_ERROR_COUNTER_LOW)));
    }
    return 0;
};

int Usb4PlatformCioPhyConfigureREFGEEN(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx, BOOLEAN bEnable)
{
    if (bEnable)
    {
        if(0 == usb4_platform_cio_phy_ctx->m_coreIndex)
        {
            for (UINT32 i=0; i< ARR_SIZE(configure_refgen_enable_0);++i)
            {
                USB4_phy_sequence_entry entry = configure_refgen_enable_0[i];
                out_dword_usb(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
            }
        }
        else
        {
            for (UINT32 i=0; i< ARR_SIZE(configure_refgen_enable_1);++i)
            {
                USB4_phy_sequence_entry entry = configure_refgen_enable_1[i];
                out_dword_usb(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
            }
        }
    }
    else
    {
        Usb4Log(USB4_LOG_PHY, Usb4PlatformCioPhyConfigureREFGEEN__Error, 0);
        return -1;
    }
    return 0;
}

// TODO: AC ERROR typecasting of USB4_DpPll_Config vs. USB4_phyConfig appears inconsistent
int Usb4PlatformCioPhyConfigureDPPLL(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx, USB4_phyConfig* pPhyConfig)
{
    usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;

    HWIO_OUTXF(USB4_PHY_REGISTER_BASE(USB43DP_COM_PHY_MODE_CTRL),
            USB4_PHY_REG_NAME(USB43DP_COM_PHY_MODE_CTRL), DP_TUNNELING_CLOCK_GEN_EN, 0); /* Disable */

    for (UINT32 i=0; i< ARR_SIZE(dp_pll_base_configuration);++i)
    {
        USB4_phy_sequence_entry entry = dp_pll_base_configuration[i];
        out_dword_usb(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
    }

    if (pPhyConfig->bSscEnabled)
    {
        USB4_phy_sequence_entry entry = dp_pll_base_configuration_ssc;
        out_dword_usb(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
    }
    else
    {
        USB4_phy_sequence_entry entry = dp_pll_base_configuration_no_ssc;
        out_dword_usb(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
    }

    for (UINT32 i=0; i< ARR_SIZE(dp_pll_base_configuration_1);++i)
    {
        USB4_phy_sequence_entry entry = dp_pll_base_configuration_1[i];
        out_dword_usb(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
    }

    if (USB4_DpPll_Config_Disable != pPhyConfig->dpPllCfg) /* According to Tobey, should be done before choice of frequency */
    {
        HWIO_OUTXF(USB4_PHY_REGISTER_BASE(USB43DP_COM_PHY_MODE_CTRL),
            USB4_PHY_REG_NAME(USB43DP_COM_PHY_MODE_CTRL), DP_TUNNELING_CLOCK_GEN_EN, 1); /* Enable */
    }

    switch(pPhyConfig->dpPllCfg)
    {
        case USB4_DpPll_Config_8p1:
            for (UINT32 i=0; i< ARR_SIZE(DPClk8p1);++i)
            {
                USB4_phy_sequence_entry entry = DPClk8p1[i];
                out_dword_usb(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
                if (entry.delay_us)
                {
                    USB4_ASSERT(0 == usb4_timer_Sleep_us(&timer, entry.delay_us));
                }
            }
            break;
        case USB4_DpPll_Config_5p4:
            for (UINT32 i=0; i< ARR_SIZE(DPClk5p4);++i)
            {
                USB4_phy_sequence_entry entry = DPClk5p4[i];
                out_dword_usb(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
                if (entry.delay_us)
                {
                    USB4_ASSERT(0 == usb4_timer_Sleep_us(&timer, entry.delay_us));
                }
            }
            break;
        case USB4_DpPll_Config_2p7:
            for (UINT32 i=0; i< ARR_SIZE(DPClk2p7);++i)
            {
                USB4_phy_sequence_entry entry = DPClk2p7[i];
                out_dword_usb(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
                if (entry.delay_us)
                {
                    USB4_ASSERT(0 == usb4_timer_Sleep_us(&timer, entry.delay_us));
                }
            }
            break;
        case USB4_DpPll_Config_1p62:
            for (UINT32 i=0; i< ARR_SIZE(DPClk1p62);++i)
            {
                USB4_phy_sequence_entry entry = DPClk1p62[i];
                out_dword_usb(usb4_platform_cio_phy_ctx->m_phyBaseAddress + entry.reg_offset, entry.reg_value);
                if (entry.delay_us)
                {
                    USB4_ASSERT(0 == usb4_timer_Sleep_us(&timer, entry.delay_us));
                }
            }
            break;
        default:
            break;
    }

    return 0;
}

int Usb4PlatformCioPhyConfigureDebugBus(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx, USB4_phyDebugBusConfig* pDebugBusConfig)
{
    HWIO_OUTXF(USB4_PHY_REGISTER_BASE(USB4_PCS_L0_TEST_CONTROL2),
                    USB4_PHY_REG_NAME(USB4_PCS_L0_TEST_CONTROL2), PRE_DEBUG_BUS_IDX10, pDebugBusConfig->L0_PRE_DEBUG_BUS_IDX10);

    HWIO_OUTXF(USB4_PHY_REGISTER_BASE(USB4_PCS_L1_TEST_CONTROL2),
                    USB4_PHY_REG_NAME(USB4_PCS_L1_TEST_CONTROL2), PRE_DEBUG_BUS_IDX10, pDebugBusConfig->L1_PRE_DEBUG_BUS_IDX10);

    HWIO_OUTXF(USB4_PHY_REGISTER_BASE(USB4_PCS_L0_TEST_CONTROL3),
                    USB4_PHY_REG_NAME(USB4_PCS_L0_TEST_CONTROL3), PRE_DEBUG_BUS_IDX32, pDebugBusConfig->L0_PRE_DEBUG_BUS_IDX32);

    HWIO_OUTXF(USB4_PHY_REGISTER_BASE(USB4_PCS_L1_TEST_CONTROL3),
                    USB4_PHY_REG_NAME(USB4_PCS_L1_TEST_CONTROL3), PRE_DEBUG_BUS_IDX32, pDebugBusConfig->L1_PRE_DEBUG_BUS_IDX32);

    HWIO_OUTXF(USB4_PHY_REGISTER_BASE(USB4_PCS_TEST_CONTROL4),
                    USB4_PHY_REG_NAME(USB4_PCS_TEST_CONTROL4), DEBUG_BUS_IDX0, pDebugBusConfig->DEBUG_BUS_IDX0);

    HWIO_OUTXF(USB4_PHY_REGISTER_BASE(USB4_PCS_TEST_CONTROL5),
                    USB4_PHY_REG_NAME(USB4_PCS_TEST_CONTROL5), DEBUG_BUS_IDX1, pDebugBusConfig->DEBUG_BUS_IDX1);

    HWIO_OUTXF(USB4_PHY_REGISTER_BASE(USB4_PCS_TEST_CONTROL6),
                    USB4_PHY_REG_NAME(USB4_PCS_TEST_CONTROL6), DEBUG_BUS_IDX2, pDebugBusConfig->DEBUG_BUS_IDX2);

    HWIO_OUTXF(USB4_PHY_REGISTER_BASE(USB4_PCS_TEST_CONTROL7),
                    USB4_PHY_REG_NAME(USB4_PCS_TEST_CONTROL7), DEBUG_BUS_IDX3, pDebugBusConfig->DEBUG_BUS_IDX3);

    HWIO_OUTXF(USB4_PHY_REGISTER_BASE(USB4_QSERDES_PLL_DEBUG_BUS_SEL),
                    USB4_PHY_REG_NAME(USB4_QSERDES_PLL_DEBUG_BUS_SEL), DEBUG_BUS_SEL, pDebugBusConfig->PLL_DEBUG_BUS_SEL);

    HWIO_OUTXF(USB4_PHY_REGISTER_BASE(USB43DP_QSERDES_TXA_DEBUG_BUS_SEL),
                    USB4_PHY_REG_NAME(USB43DP_QSERDES_TXA_DEBUG_BUS_SEL), DEBUGBUS_SEL, pDebugBusConfig->TXA_DEBUG_BUS_SEL);

    HWIO_OUTXF(USB4_PHY_REGISTER_BASE(USB43DP_QSERDES_TXB_DEBUG_BUS_SEL),
                    USB4_PHY_REG_NAME(USB43DP_QSERDES_TXB_DEBUG_BUS_SEL), DEBUGBUS_SEL, pDebugBusConfig->TXB_DEBUG_BUS_SEL);

    return 0;
}

int Usb4PlatformCioPhyReadDebugBus(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx, USB4_phyDebugBusStatus* pDebugBusStatus)
{
    pDebugBusStatus->debug_bus_0_status = HWIO_INX(USB4_PHY_REGISTER_BASE(USB4_PCS_DEBUG_BUS_0_STATUS),
                                                        USB4_PHY_REG_NAME(USB4_PCS_DEBUG_BUS_0_STATUS));

    pDebugBusStatus->debug_bus_1_status = HWIO_INX(USB4_PHY_REGISTER_BASE(USB4_PCS_DEBUG_BUS_1_STATUS),
                                                        USB4_PHY_REG_NAME(USB4_PCS_DEBUG_BUS_1_STATUS));

    pDebugBusStatus->debug_bus_2_status = HWIO_INX(USB4_PHY_REGISTER_BASE(USB4_PCS_DEBUG_BUS_2_STATUS),
                                                        USB4_PHY_REG_NAME(USB4_PCS_DEBUG_BUS_2_STATUS));

    pDebugBusStatus->debug_bus_3_status = HWIO_INX(USB4_PHY_REGISTER_BASE(USB4_PCS_DEBUG_BUS_3_STATUS),
                                                        USB4_PHY_REG_NAME(USB4_PCS_DEBUG_BUS_3_STATUS));
    return 0;
}

int Usb4PlatformCioPhyConfigureDebugClk(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx, USB4_phyDebugClockConfig* pDebugClkConfig)
{
    HWIO_OUTXF(USB4_PHY_REGISTER_BASE(USB4_PCS_TEST_CONTROL3),
                    USB4_PHY_REG_NAME(USB4_PCS_TEST_CONTROL3), DEBUG_CLK_MUX_SEL, pDebugClkConfig->PCS_TC3_DEBUG_CLK_MUX_SEL);

    HWIO_OUTXF(USB4_PHY_REGISTER_BASE(USB4_QSERDES_PLL_DEBUG_BUS_SEL),
                    USB4_PHY_REG_NAME(USB4_QSERDES_PLL_DEBUG_BUS_SEL), CLK_DEBUG_SEL, pDebugClkConfig->PLL_CLK_DEBUG_SEL);

    HWIO_OUTXF(USB4_PHY_REGISTER_BASE(USB43DP_QSERDES_TXA_DEBUG_BUS_SEL),
                    USB4_PHY_REG_NAME(USB43DP_QSERDES_TXA_DEBUG_BUS_SEL), CLK_DEBUG_SEL, pDebugClkConfig->TXA_CLK_DEBUG_SEL);

    HWIO_OUTXF(USB4_PHY_REGISTER_BASE(USB43DP_QSERDES_TXB_DEBUG_BUS_SEL),
                    USB4_PHY_REG_NAME(USB43DP_QSERDES_TXB_DEBUG_BUS_SEL), CLK_DEBUG_SEL, pDebugClkConfig->TXB_CLK_DEBUG_SEL);

    HWIO_OUTXF(USB4_PHY_REGISTER_BASE(USB43DP_COM_DBG_CLK_MUX_CTRL),
                    USB4_PHY_REG_NAME(USB43DP_COM_DBG_CLK_MUX_CTRL), DEBUG_CLK_SEL, pDebugClkConfig->CLK_MUX_CTRL_DEBUG_CLK_SEL);

    HWIO_OUTXF(USB4_PHY_REGISTER_BASE(USB4_PCS_TEST_CONTROL3),
                    USB4_PHY_REG_NAME(USB4_PCS_TEST_CONTROL3), DEBUG_CLK_DIV_SEL, pDebugClkConfig->DEBUG_CLK_DIV_SEL);

    HWIO_OUTXF(USB4_PHY_REGISTER_BASE(USB43DP_COM_DBG_CLK_MUX_CTRL),
                    USB4_PHY_REG_NAME(USB43DP_COM_DBG_CLK_MUX_CTRL), DEBUG_CLK_DIV, pDebugClkConfig->CLK_MUX_CTRL_DEBUG_CLK_DIV);
    return 0;
}


int Usb4PlatformCioPhyPowerDown(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx)
{
    HWIO_OUTXF(USB4_PHY_REGISTER_BASE(    USB4_PCS_POWER_DOWN_CONTROL),
                        USB4_PHY_REG_NAME(USB4_PCS_POWER_DOWN_CONTROL), SW_PWRDN_B, 1);
    HWIO_OUTXF(USB4_PHY_REGISTER_BASE(    USB3_PCS_POWER_DOWN_CONTROL),
                        USB4_PHY_REG_NAME(USB3_PCS_POWER_DOWN_CONTROL), SW_PWRDN_B, 1);
    HWIO_OUTXF(USB4_PHY_REGISTER_BASE(    DP_DP_PHY_PD_CTL),
                        USB4_PHY_REG_NAME(DP_DP_PHY_PD_CTL), PWRDN_B, 1);
    return 0;
}
