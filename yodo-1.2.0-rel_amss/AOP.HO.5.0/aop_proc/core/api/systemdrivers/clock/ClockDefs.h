#ifndef __CLOCKDEFS_H__
#define __CLOCKDEFS_H__

/*
================================================================================
*/
/**
  @file ClockDefs.h
  @brief Public definitions include file for the clock driver.
*/
/*
  ==============================================================================

  Copyright (c) 2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

  ==============================================================================

  $Header: $
  $DateTime: $
  $Author: $

  ==============================================================================
*/

/*==============================================================================
  Includes
==============================================================================*/

#include <stdint.h>
#include <stdbool.h>


/*==============================================================================
  Macros
==============================================================================*/

/* Clock return values */
#define CLOCK_SUCCESS   0
#define CLOCK_ERROR     -1

/* Macro to force an enumeration to be a full 32 bits wide */
#define CLOCK_ENUM_32BITS(name) CLOCK_##name##_32BITS = 0x7FFFFFFF


/*==============================================================================
  Type definitions
==============================================================================*/

/**
 * Clock QDSS levels
 */
typedef enum
{
  CLOCK_QDSS_LEVEL_OFF,
  CLOCK_QDSS_LEVEL_DYNAMIC,
  CLOCK_QDSS_LEVEL_MAX_LEVEL = CLOCK_QDSS_LEVEL_DYNAMIC,
  CLOCK_QDSS_LEVEL_NUM_LEVELS

} ClockQDSSLevelType;

typedef enum
{
  VDD_OFF        = 0x0,
  VDD_RET        = 0x10,
  MIN_SVS        = 0x30,
  LOW_SVS        = 0x40,
  SVS            = 0x80,
  SVS_L1         = 0xC0,
  NOMINAL        = 0x100,
  NOMINAL_L1     = 0x140,
  NOMINAL_L2     = 0x150,
  TURBO          = 0x180,
  TURBO_L1       = 0x1A0,
  MAX            = TURBO_L1,
  VDD_INVALID    = -1,
  VDD_NUM_LEVELS = 11,

  CLOCK_ENUM_32BITS(VDD)

} voltage_rail;

typedef enum
{
  GCC,
  DDRCC,
  NA = 0xFF,

  CLOCK_ENUM_32BITS(MODE)

} clk_mode;

typedef enum
{
  PMIC_CFG_0,
  PMIC_CFG_1,
  PMIC_CFG_2,
  PMIC_CFG_3,
  PMIC_CFG_4,
  PMIC_CFG_5,
  PMIC_CFG_6,
  PMIC_CFG_7,
  PMIC_CFG_8,

  CLOCK_ENUM_32BITS(PMIC)

} ddr_automode;

typedef struct
{
  uint8_t      clk_idx;
  uint32_t     freq_khz;
  uint32_t     clk_period;
  bool         freq_enable;
  clk_mode     mode;
  voltage_rail vddcx;
  voltage_rail vddmx;
  voltage_rail vdda;
  ddr_automode ddr_automode_cfg;
  uint8_t      max_up_idx;
  uint8_t      min_down_idx;
  bool         double_freq_change;

} freq_state;

/**
 * DDR configure settings data from XBL
 */
typedef struct
{
  uint8_t     nNumMCStates;
  uint8_t     nNumSHUBStates;
  freq_state *pMCCfg;
  freq_state *pSHUBCfg;

} DDRCfgType;

#endif /* __CLOCKDEFS_H__ */
