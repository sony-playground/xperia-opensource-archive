#ifndef __PMICTEST_H__
#define __PMICTEST_H__

/*! @file PmicTest.h
 *
 *  PMIC Test 
 *
 *  Copyright (c) 2020-2021 Qualcomm Technologies, Inc.  All Rights Reserved. 
 *  Qualcomm Technologies Proprietary and Confidential.
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
02/26/20   dais    Added Pmic Test Header file

===========================================================================*/

/*===========================================================================
                     INCLUDE FILES FOR MODULE
===========================================================================*/
#include <Protocol/EFIPmicHaptics.h>
#include <Protocol/EFIPmicLpg.h>
#include <Protocol/EFIPmicPon.h>
#include <Protocol/EFIPmicPwrOn.h>
#include <Protocol/EFIPmicWled.h>


/*===========================================================================
                     MACRO DEFINATIONS
===========================================================================*/


/*===========================================================================
                     TYPE DECLARATIONS
===========================================================================*/

/*  PMIC Test AccessControl */

typedef enum
{
    EFI_PM_AC_WRITE,

}EFI_PM_TEST_DRIVER_AC_TYPE_FUNCTION;


//SlaveID, address, data
typedef struct _EFI_PM_TEST_AC_WRITE_PARAM
{
    UINT16         SlaveID;
    UINT16         Address;
    UINT8          Data;
} EFI_PM_TEST_AC_WRITE_PARAM;

typedef union _EFI_PM_TEST_AC_FUNCTION_TYPE
{
    EFI_PM_TEST_AC_WRITE_PARAM       AccessControlWrite;

}EFI_PM_TEST_AC_FUNCTION_TYPE;

/* PMIC Test BOB */

typedef enum
{
   EFI_PM_BOB_VOLT_LEVEL_STATUS, /**<BOB voltage level status*/
}EFI_PM_TEST_DRIVER_BOB_TYPE_FUNCTION;


typedef struct _EFI_PM_BOB_VOLT_LEVEL_STATUS_PARAM
{
   UINT8 PmicChip;
   UINT8 PeripheralIndex;
   UINT32 *VoltLevel;
   
} EFI_PM_TEST_BOB_VOLT_LEVEL_STATUS_PARAM;

typedef union _EFI_PM_TEST_BOB_FUNCTION_TYPE
{
   EFI_PM_TEST_BOB_VOLT_LEVEL_STATUS_PARAM          BobVoltLevelStatus;
}EFI_PM_TEST_BOB_FUNCTION_TYPE;

/* PMIC Test CoinCell  */

typedef enum
{
    EFI_PM_TEST_COINCELL_ENABLE,
    EFI_PM_TEST_COINCELL_GET_STATUS,
    EFI_PM_TEST_COINCELL_SET_CHARGE_CURRENT_LIMIT_RESISTOR, 
    EFI_PM_TEST_COINCELL_SET_CHARGING_VOLTAGE,

}EFI_PM_TEST_DRIVER_COINCELL_TYPE_FUNCTION;


typedef enum 
{
  EFI_PM_COINCELL_RSET_2K1,
  EFI_PM_COINCELL_RSET_1K7,
  EFI_PM_COINCELL_RSET_1K2,
  EFI_PM_COINCELL_RSET_0K8,
  EFI_PM_COINCELL_RSET_INVALID,
}EFI_PM_COINCELL_CHG_RSET_TYPE;

/*! \enum pm_coincell_chg_vset_type
 * \brief Select Charging volatage value
*/
typedef enum 
{
  EFI_PM_COINCELL_VSET_2V5,
  EFI_PM_COINCELL_VSET_3V2,
  EFI_PM_COINCELL_VSET_3V1,
  EFI_PM_COINCELL_VSET_3V0,
  EFI_PM_COINCELL_VSET_INVALID,
}EFI_PM_COINCELL_CHG_VSET_TYPE;


typedef struct _EFI_PM_TEST_COINCELL_ENABLE_PARAM
{
    UINT8       DeviceIndex;
    INT32 enable;
}EFI_PM_TEST_COINCELL_ENABLE_PARAM;

typedef struct _EFI_PM_TEST_COINCELL_GET_STATUS_PARAM
{
    UINT8       DeviceIndex;
    BOOLEAN     *status;

}EFI_PM_TEST_COINCELL_GET_STATUS_PARAM;

typedef struct _EFI_PM_TEST_COINCELL_SET_CHARGE_CURRENT_LIMIT_RESISTOR_PARAM
{
    UINT8       DeviceIndex;
    UINT32     COIN_CHG_RSET_VALUE;

}EFI_PM_TEST_COINCELL_SET_CHARGE_CURRENT_LIMIT_RESISTOR_PARAM;

typedef struct _EFI_PM_TEST_COINCELL_SET_CHARGING_VOLTAGE_PARAM
{
    UINT8       DeviceIndex;
    UINT32     COIN_CHG_VSET_VALUE;

}EFI_PM_TEST_COINCELL_SET_CHARGING_VOLTAGE_PARAM;

typedef union _EFI_PM_TEST_COINCELL_FUNCTION_TYPE
{
    EFI_PM_TEST_COINCELL_ENABLE_PARAM                                 CoincellEnable;
    EFI_PM_TEST_COINCELL_GET_STATUS_PARAM                               CoincellStatus; 
    EFI_PM_TEST_COINCELL_SET_CHARGE_CURRENT_LIMIT_RESISTOR_PARAM        CoincellRsetValue;
    EFI_PM_TEST_COINCELL_SET_CHARGING_VOLTAGE_PARAM                     CoincellVsetValue;

}EFI_PM_TEST_COINCELL_FUNCTION_TYPE;

/* PMIC Test Gpio  */

//typedef enum
//{
    //EFI_PM_GPIO_STATUS_GET,  /**< GPIO status get*/ 
    //EFI_PM_GPIO_CONFIG_BIAS_VOLTAGE, /**<GPIO Config Bias Voltage*/
    //EFI_PM_GPIO_SET_VOLTAGE_SOURCE, /**<GPIO Set Voltage source */
    //EFI_PM_GPIO_CONFIG_DIGITALINPUT, /**<GPIO Config Digital input */
    //EFI_PM_GPIO_CONFIG_DIGITALOUTPUT, /**<GPIO Config Digital output */
    //EFI_PM_GPIO_CONFIG_DIGITAL_INOUT, /**<GPIO Config Digital input/output */
    //EFI_PM_GPIO_SET_INVERSION_CONFIG, /**<GPIO Config set inversion */
    //EFI_PM_GPIO_SET_CURRENT_SOURCE_PULLS, /**<GPIO set current source*/
    //EFI_PM_GPIO_SET_EXT_PIN_CONFIG, /**<GPIO set external pin config*/
    //EFI_PM_GPIO_SET_OUT_BUFFER_DRIVE_STRENGTH, /**<GPIO set buffer drive strength*/
    //EFI_PM_GPIO_SET_SOURCE_CONFIG, /**<GPIO set source config*/
    //EFI_PM_GPIO_SET_OUTPUT_BUFFER_CONFIG, /**<GPIO set buffer config*/
    //EFI_PM_GPIO_ENABLE,
//}EFI_PM_TEST_DRIVER_GPIO_TYPE_FUNCTION;

typedef struct _EFI_PM_GPIO_TYPE_INDEX
{
    UINT8                   GPIOIndex;
//    EFI_PM_GPIO_WHICH_TYPE  GPIOType;
} EFI_PM_TEST_GPIO_TYPE_INDEX;

typedef struct _EFI_PM_GPIO_VOLTAGE_SOURCE_PARAM
{
    EFI_PM_TEST_GPIO_TYPE_INDEX         GPIOTypeIndex;
//    EFI_PM_GPIO_VOLTAGE_SOURCE_TYPE     VoltageSource;
} EFI_PM_TEST_GPIO_SET_VOLTAGE_SOURCE_PARAM, EFI_PM_TEST_GPIO_CONFIG_BIAS_VOLTAGE_PARAM;

typedef struct _EFI_PM_GPIO_CONFIG_DIGITAL_INOUT_PARAM
{
    EFI_PM_TEST_GPIO_TYPE_INDEX                 GPIOTypeIndex;
//    EFI_PM_GPIO_SOURCE_CONFIG_TYPE              GPIOSrc;
//    EFI_PM_GPIO_CURRENT_SOURCE_PULLS_TYPE       GPIOPulls;
//    EFI_PM_GPIO_VOLTAGE_SOURCE_TYPE             VoltageSource;
//    EFI_PM_GPIO_OUT_BUFFER_CONFIG_TYPE          BufferConfig;
//    EFI_PM_GPIO_OUT_BUFFER_DRIVE_STRENGTH_TYPE  BufferStrength;
} EFI_PM_TEST_GPIO_CONFIG_DIGITAL_INOUT_PARAM;

typedef struct _EFI_PM_GPIO_SET_EXT_PIN_CONFIG_PARAM
{
    EFI_PM_TEST_GPIO_TYPE_INDEX         GPIOTypeIndex;
//    EFI_PM_GPIO_EXT_PIN_CONFIG_TYPE     ConfigType;
} EFI_PM_TEST_GPIO_SET_EXT_PIN_CONFIG_PARAM;

typedef struct _EFI_PM_GPIO_SET_INVERSION_CONFIG_PARAM
{
    EFI_PM_TEST_GPIO_TYPE_INDEX  GPIOTypeIndex;
    BOOLEAN                 Inversion;
} EFI_PM_TEST_GPIO_SET_INVERSION_CONFIG_PARAM;

typedef struct _EFI_PM_GPIO_CURRENT_SOURCE_PULLS_PARAM
{
    EFI_PM_TEST_GPIO_TYPE_INDEX             GPIOTypeIndex;
 //   EFI_PM_GPIO_CURRENT_SOURCE_PULLS_TYPE   CurrentSrcPullType;
} EFI_PM_TEST_GPIO_SET_CURRENT_SOURCE_PULLS_PARAM, EFI_PM_TEST_GPIO_SET_OUT_BUFFER_DRIVE_STRENGTH_PARAM;

typedef struct _EFI_PM_GPIO_SET_SOURCE_CONFIG_TYPE_PARAM
{
    EFI_PM_TEST_GPIO_TYPE_INDEX           GPIOTypeIndex;
//    EFI_PM_GPIO_SOURCE_CONFIG_TYPE        SourceConfigType;
} EFI_PM_TEST_GPIO_SET_SOURCE_CONFIG_TYPE_PARAM;

typedef struct _EFI_PM_GPIO_DRIVE_STRENGTH_TYPE_PARAM
{
    EFI_PM_TEST_GPIO_TYPE_INDEX                   GPIOTypeIndex;
//    EFI_PM_GPIO_OUT_BUFFER_DRIVE_STRENGTH_TYPE    DriveStrengthType;
} EFI_PM_TEST_GPIO_DRIVE_STRENGTH_TYPE_PARAM;

typedef struct _EFI_PM_GPIO_OUTPUT_BUFFER_CONFIGURATION_PARAM
{
    EFI_PM_TEST_GPIO_TYPE_INDEX                  GPIOTypeIndex;
//    EFI_PM_GPIO_OUT_BUFFER_CONFIG_TYPE          BufferConfigType;
} EFI_PM_TEST_GPIO_OUTPUT_BUFFER_CONFIGURATION_PARAM;

typedef struct _EFI_PM_GPIO_ENABLE_PARAM
{
    EFI_PM_TEST_GPIO_TYPE_INDEX                  GPIOTypeIndex;
    BOOLEAN                                 enable;
} EFI_PM_TEST_GPIO_ENABLE_PARAM;

typedef union _EFI_PM_TEST_GPIO_FUNCTION_TYPE
{
    EFI_PM_TEST_GPIO_CONFIG_BIAS_VOLTAGE_PARAM       GpioConfigBiasVoltage;
    EFI_PM_TEST_GPIO_CONFIG_DIGITAL_INOUT_PARAM      GpioConfigDigitalInOut; 
    EFI_PM_TEST_GPIO_SET_EXT_PIN_CONFIG_PARAM        GpioSetExtPinConfig;
    EFI_PM_TEST_GPIO_SET_VOLTAGE_SOURCE_PARAM        GpioSetVoltageSource;
    EFI_PM_TEST_GPIO_SET_INVERSION_CONFIG_PARAM      GpioSetInversionConfig;
    EFI_PM_TEST_GPIO_SET_CURRENT_SOURCE_PULLS_PARAM  GpioSetCurrentSourcePull;
    EFI_PM_TEST_GPIO_SET_SOURCE_CONFIG_TYPE_PARAM    GpioSetSourceConfigType;
    EFI_PM_TEST_GPIO_DRIVE_STRENGTH_TYPE_PARAM       GpioDriveStrengthType;
    EFI_PM_TEST_GPIO_OUTPUT_BUFFER_CONFIGURATION_PARAM GpioOutputBufferConfigType;
    EFI_PM_TEST_GPIO_ENABLE_PARAM                GpioEnable;
}EFI_PM_TEST_GPIO_FUNCTION_TYPE;

/* PMIC Test Haptics */

typedef enum
{
    EFI_PM_TEST_HAPTICS_CONFIG_HAPTICS_RATE,
    EFI_PM_TEST_HAPTICS_AUTO_RES_CONFIG,
}EFI_PM_TEST_DRIVER_HAPTICS_TYPE_FUNCTION;


typedef enum
{
  EFI_PM_HAPTICS_LRA_RES_CALIB_FOUR_PERIODS,      /*AFTER EVERY 4 LRA PERIOD*/
  EFI_PM_HAPTICS_LRA_RES_CALIB_EIGHT_PERIODS,     /*AFTER EVERY 8 LRA PERIOD*/
  EFI_PM_HAPTICS_LRA_RES_CALIB_SIXTEEN_PERIODS,   /*AFTER EVERY 16 LRA PERIOD*/
  EFI_PM_HAPTICS_LRA_RES_CALIB_THIRTYTWO_PERIODS, /*AFTER EVERY 32 LRA PERIOD*/
  EFI_PM_HAPTICS_LRA_RES_CALIB_INVALID,           /*INVALID*/
}EFI_PM_HAPTICS_LRA_RES_CALIB_TYPE; 


typedef enum
{
  EFI_PM_HAPTICS_LRA_HIGH_Z_NO_HIGHZ,   /*no high-z*/
  EFI_PM_HAPTICS_LRA_HIGH_Z_HIGHZ_OPT1, /*2 LRA period (ZXD), 1/8 LRA period (QWD)*/
  EFI_PM_HAPTICS_LRA_HIGH_Z_HIGHZ_OPT2, /*3 LRA period (ZXD), 1/4 LRA period (QWD)*/
  EFI_PM_HAPTICS_LRA_HIGH_Z_HIGHZ_OPT3, /*4 LRA period (ZXD), 1/2 LRA period (QWD)*/
  EFI_PM_HAPTICS_LRA_HIGH_Z_INVALID,    /*Invalid*/
}EFI_PM_HAPTICS_LRA_HIGH_Z_TYPE; 

typedef enum
{
  EFI_PM_HAPTICS_LRA_AUTO_RES_MODE_NO_AUTO_RES, /*no auto resonance*/
  EFI_PM_HAPTICS_LRA_AUTO_RES_MODE_ZXD,         /*Zero crossing based discontinuous method (ZXD)*/
  EFI_PM_HAPTICS_LRA_AUTO_RES_MODE_QWD,         /*Quarter wave drive method (QWD)*/
  EFI_PM_HAPTICS_LRA_AUTO_RES_MODE_MAX_QWD,     /*MAX QWD*/
  EFI_PM_HAPTICS_LRA_AUTO_RES_MODE_ZXD_EOP,     /*Zero crossing based discontinuous method with high z after end of pattern*/
  EFI_PM_HAPTICS_LRA_AUTO_RES_MODE_INVALID,     /*Invalid*/
}EFI_PM_HAPTICS_LRA_AUTO_RES_MODE_TYPE; 


typedef struct _EFI_PM_TEST_HAPTICS_CONFIG_HAPTICS_RATE_PARAM
{
    UINT32       DeviceIndex;
   UINT32       config_rate;
} EFI_PM_TEST_HAPTICS_CONFIG_HAPTICS_RATE_PARAM;

typedef struct _EFI_PM_TEST_HAPTICS_AUTO_RES_CONFIG_PARAM
{
    UINT32       DeviceIndex;
    EFI_PM_HAPTICS_LRA_RES_CALIB_TYPE CalibType;
	BOOLEAN CalibEop;
   EFI_PM_HAPTICS_LRA_HIGH_Z_TYPE ZType;
   UINT32 CalDuration;
   EFI_PM_HAPTICS_LRA_AUTO_RES_MODE_TYPE ModeType;
} EFI_PM_TEST_HAPTICS_AUTO_RES_CONFIG_PARAM;

typedef union _EFI_PM_TEST_HAPTICS_FUNCTION_TYPE
{
    EFI_PM_TEST_HAPTICS_CONFIG_HAPTICS_RATE_PARAM                Hapticsconfigrate;
    EFI_PM_TEST_HAPTICS_AUTO_RES_CONFIG_PARAM                    Hapticsautores; 

}EFI_PM_TEST_HAPTICS_FUNCTION_TYPE;

/* PMIC Test LPG */

typedef enum
{
    EFI_PM_TEST_LPG_PATTERN_CONFIG,
    EFI_PM_TEST_LPG_PWN_CLK_SELC,
    EFI_PM_TEST_LPG_PWM_RAMP_GENERATOR_ENABLE, 
    EFI_PM_TEST_LPG_PWM_LUT_INDEX_SET,
    EFI_PM_TEST_LPG_SET_PWM_BIT_SIZE,
    EFI_PM_TEST_LPG_PWM_SRC_SELECT,
    EFI_PM_TEST_LPG_LUT_CONFIG_SET_ARRAY,
    EFI_PM_TEST_LPG_LUT_CONFIG_GET_ARRAY,
    EFI_PM_TEST_LPG_LUT_CONFIG_SET,
    EFI_PM_TEST_LPG_LUT_CONFIG_GET,
    EFI_PM_TEST_LPG_CONFIG_PAUSE_TIME,
    EFI_PM_TEST_LPG_PWM_OUTPUT_ENABLE,
    EFI_PM_TEST_LPG_PWM_RAMP_GENERATOR_START
}EFI_PM_TEST_DRIVER_LPG_TYPE_FUNCTION;

typedef struct _EFI_PM_TEST_LPG_PATTERN_CONFIG_PARAM
{
    UINT32                  PmicChip;
    EFI_PM_LPG_CHAN_TYPE    ChanType;
    BOOLEAN                 RampDir;
    BOOLEAN                 PatternRepeat;
    BOOLEAN                 RampToggle;
    BOOLEAN                 EnPauseHigh;
    BOOLEAN                 EnPauseLow;
} EFI_PM_TEST_LPG_PATTERN_CONFIG_PARAM;

typedef struct _EFI_PM_TEST_LPG_PWN_CLK_SELC_PARAM
{
    UINT32                  PmicChip;
    EFI_PM_LPG_CHAN_TYPE    ChanType;
    EFI_PM_LPG_PWM_CLOCK_TYPE ClkType;
} EFI_PM_TEST_LPG_PWN_CLK_SELC_PARAM;

typedef struct _EFI_PM_TEST_LPG_PWM_RAMP_GENERATOR_ENABLE_PARAM
{
    UINT32                  PmicChip;
    EFI_PM_LPG_CHAN_TYPE    ChanType;
    BOOLEAN                 Enable;
} EFI_PM_TEST_LPG_PWM_RAMP_GENERATOR_ENABLE_PARAM;

typedef struct _EFI_PM_TEST_LPG_PWM_LUT_INDEX_SET_PARAM
{
    UINT32                  PmicChip;
    EFI_PM_LPG_CHAN_TYPE    ChanType;
    UINT32                  LowIndex;
    UINT32                  HighIndex;
} EFI_PM_TEST_LPG_PWM_LUT_INDEX_SET_PARAM;

typedef struct _EFI_PM_TEST_LPG_SET_PWM_BIT_SIZE_PARAM
{
    UINT32                  PmicChip;
    EFI_PM_LPG_CHAN_TYPE    ChanType;
    EFI_PM_LPG_PWM_BIT_SIZE_TYPE PwmSizeType;
} EFI_PM_TEST_LPG_SET_PWM_BIT_SIZE_PARAM;

typedef struct _EFI_PM_TEST_LPG_PWM_SRC_SELECT_PARAM
{
    UINT32                  PmicChip;
    EFI_PM_LPG_CHAN_TYPE    ChanType;
    EFI_PM_LPG_SRC_TYPE     SrcType;
} EFI_PM_TEST_LPG_PWM_SRC_SELECT_PARAM;

typedef struct _EFI_PM_TEST_LPG_LUT_CONFIG_SET_ARRAY_PARAM
{
    UINT32      PmicChip;
    UINT32      StartIndex;
    UINT32      *Value;
    UINT32      Count;
} EFI_PM_TEST_LPG_LUT_CONFIG_SET_ARRAY_PARAM, EFI_PM_TEST_LPG_LUT_CONFIG_GET_ARRAY_PARAM;

typedef struct _EFI_PM_TEST_LPG_LUT_CONFIG_SET_PARAM
{
    UINT32      PmicChip;
    UINT32      LutIndex;
    UINT32      PwmValue;
} EFI_PM_TEST_LPG_LUT_CONFIG_PARAM;

typedef struct _EFI_PM_TEST_LPG_CONFIG_PAUSE_TIME_PARAM
{
    UINT32                  PmicChip;
    EFI_PM_LPG_CHAN_TYPE    ChanType;
    UINT32                  Ramp_Step_Duration;
    UINT32                  Hi_Multiplier;
    UINT32                  Low_Multiplier;
} EFI_PM_TEST_LPG_CONFIG_PAUSE_TIME_PARAM;

typedef struct _EFI_PM_TEST_LPG_PWM_OUTPUT_ENABLE_PARAM
{
   UINT32                PmicChip;
   EFI_PM_LPG_CHAN_TYPE  ChanType;
   BOOLEAN               OutputEnable;
} EFI_PM_TEST_LPG_PWM_OUTPUT_ENABLE_PARAM;

typedef struct _EFI_PM_TEST_LPG_PWM_RAMP_GENERATOR_START_PARAM
{
   UINT32                PmicChip;
   EFI_PM_LPG_CHAN_TYPE  ChanType;
} EFI_PM_TEST_LPG_PWM_RAMP_GENERATOR_START_PARAM;


typedef union _EFI_PM_TEST_LPG_FUNCTION_TYPE
{
    EFI_PM_TEST_LPG_PATTERN_CONFIG_PARAM                LpgPatternConfig;
    EFI_PM_TEST_LPG_PWN_CLK_SELC_PARAM                  LpgPwmClkSel; 
    EFI_PM_TEST_LPG_PWM_RAMP_GENERATOR_ENABLE_PARAM     LpgPwmRampGeneratorEnableParam;
    EFI_PM_TEST_LPG_PWM_LUT_INDEX_SET_PARAM             LpgPwmLutIndexSet;
    EFI_PM_TEST_LPG_SET_PWM_BIT_SIZE_PARAM              LpgSetPwmBitsize;
    EFI_PM_TEST_LPG_PWM_SRC_SELECT_PARAM                LpgPwmSrcSelect;
    EFI_PM_TEST_LPG_LUT_CONFIG_SET_ARRAY_PARAM          LpgLutConfigSetArray;
    EFI_PM_TEST_LPG_LUT_CONFIG_GET_ARRAY_PARAM          LpgLutConfigGetArray;
    EFI_PM_TEST_LPG_LUT_CONFIG_PARAM                    LpgLutConfig;
    EFI_PM_TEST_LPG_CONFIG_PAUSE_TIME_PARAM             LpgConfigPauseTime;
    EFI_PM_TEST_LPG_PWM_OUTPUT_ENABLE_PARAM           LpgPwmOutputEnable;
    EFI_PM_TEST_LPG_PWM_RAMP_GENERATOR_START_PARAM    LpgPwmRampGeneratorStart;

}EFI_PM_TEST_LPG_FUNCTION_TYPE;

/* PMIC Test PON */

typedef enum
{
  EFI_PM_PON_RESET_CFG_WARM_RESET,
  EFI_PM_PON_RESET_CFG_NORMAL_SHUTDOWN,
  /* Shutdown to a state of main battery removal */
  EFI_PM_PON_RESET_CFG_D_VDD_BATT_REMOVE_SHUTDOWN,
   /* Shutdown to a state of main battery and coin cell removal*/
  EFI_PM_PON_RESET_CFG_X_VDD_COIN_CELL_REMOVE_SHUTDOWN,
   /* Shutdown + Auto pwr up */
  EFI_PM_PON_RESET_CFG_HARD_RESET,
  /* Main Batt and coin cell remove Shutdown + Auto pwr up 8: DVDD_HARD_RESET */
  EFI_PM_PON_RESET_CFG_D_VDD_BATT_REMOVE_HARD_RESET,
  EFI_PM_PON_RESET_CFG_D_VDD_COIN_CELL_REMOVE_HARD_RESET,
  EFI_PM_PON_RESET_CFG_X_VDD_COIN_CELL_REMOVE_HARD_RESET,
  EFI_PM_PON_RESET_CFG_IMMEDIATE_X_VDD_COIN_CELL_REMOVE_SHUTDOWN,
  /* Warm Reset and Main Batt/coin cell remove Shutdown */
  EFI_PM_PON_RESET_CFG_WARM_RESET_AND_D_VDD_BATT_REMOVE_SHUTDOWN,
  EFI_PM_PON_RESET_CFG_WARM_RESET_AND_X_VDD_COIN_CELL_REMOVE_SHUTDOWN,
  EFI_PM_PON_RESET_CFG_WARM_RESET_AND_SHUTDOWN,
  /* Warm Reset then Main Batt/coin cell remove Shutdown + Auto pwr up */
  EFI_PM_PON_RESET_CFG_WARM_RESET_THEN_HARD_RESET,
  EFI_PM_PON_RESET_CFG_WARM_RESET_THEN_D_VDD_BATT_REMOVE_HARD_RESET,
  EFI_PM_PON_RESET_CFG_WARM_RESET_THEN_X_VDD_COIN_CELL_REMOVE_HARD_RESET,
  EFI_PM_PON_RESET_CFG_INVALID  
}EFI_PM_PON_RESET_CFG_TYPE;

#if !defined(FEATURE_XBOOT)
typedef enum
{
  EFI_PM_PON_RESET_SOURCE_KPDPWR,           /* Power key */
  EFI_PM_PON_RESET_SOURCE_RESIN,            /* Resin in form MSM */
  EFI_PM_PON_RESET_SOURCE_RESIN_AND_KPDPWR, /* Pwr Key + Resin */
  EFI_PM_PON_RESET_SOURCE_RESIN_OR_KPDPWR,  /* Pwr Key or Resin */
  EFI_PM_PON_RESET_SOURCE_GP1,              /* General purpose-1 */
  EFI_PM_PON_RESET_SOURCE_GP2,              /* General purpose-1 */
  EFI_PM_PON_RESET_SOURCE_INVALID  
}EFI_PM_PON_RESET_SOURCE_TYPE;
#endif /* !defined(FEATURE_XBOOT) */

typedef enum
{
   EFI_PM_PON_OFF,
   EFI_PM_PON_ON,
   EFI_PM_PON_INVALID
}EFI_PM_PON_ON_OFF_TYPE;

typedef enum
{
  EFI_PM_PON_FSM_STATUS_OFF,           /* off state */
  EFI_PM_PON_FSM_STATUS_PON,           /* pon state */
  EFI_PM_PON_FSM_STATUS_POFF,          /* poff state */
  EFI_PM_PON_FSM_STATUS_ON,            /* on state */
  EFI_PM_PON_FSM_STATUS_DVDD_CFG,      /* dvdd_cfg state */
  EFI_PM_PON_FSM_STATUS_RESERVED,      /* reserved */
  EFI_PM_PON_FSM_STATUS_FAULT,         /* fault state  */
  EFI_PM_PON_FSM_STATUS_WARM_RESET,    /* warm reset state */
  EFI_PM_PON_FSM_STATUS_INVALID  
}EFI_PM_PON_FSM_STATUS_TYPE;

typedef struct
{
  UINT32 soft : 1;               /* Software trigger */
  UINT32 ps_hold : 1;            /* PS_HOLD trigger */             
  UINT32 pmic_wd : 1;            /* PMIC Watchdog trigger */             
  UINT32 gp1 : 1;                /* Keypad_Reset1 trigger */             
  UINT32 gp2 : 1;                /* Keypad_Reset2 trigger */             
  UINT32 kpdpwr_and_resin : 1;   /* KPDPWR_N and RESIN_N trigger */
  UINT32 resin : 1;              /* RESIN_N trigger */
  UINT32 kpdpwr : 1;             /* KPDPWR_N trigger */
  UINT32 reserved : 3;           /* Reserved bits */
  UINT32 charger : 1;            /* Charger (BOOT_DONE) trigger */
  UINT32 tft : 1;                /* TFT trigger */
  UINT32 uvlo : 1;               /* UVLO trigger */
  UINT32 otst3 : 1;              /* Overtemp trigger */
  UINT32 stage3 : 1;             /* Stage3 reset trigger */
}EFI_PM_PON_POFF_REASON_TYPE;

typedef struct
{
  UINT32 soft : 1;               /* Software trigger */
  UINT32 ps_hold : 1;            /* PS_HOLD trigger */             
  UINT32 pmic_wd : 1;            /* PMIC Watchdog trigger */             
  UINT32 gp1 : 1;                /* Keypad_Reset1 trigger */             
  UINT32 gp2 : 1;                /* Keypad_Reset2 trigger */             
  UINT32 kpdpwr_and_resin : 1;   /* KPDPWR_N and RESIN_N trigger */
  UINT32 resin : 1;              /* RESIN_N trigger */
  UINT32 kpdpwr : 1;             /* KPDPWR_N trigger */
  UINT32 reserved : 4;           /* Reserved bits */
  UINT32 tft : 1;                /* TFT trigger */
  UINT32 reserved1 : 3;          /* Reserved bits */
}PM_PON_WARM_RESET_REASON_TYPE;


typedef struct
{
  UINT32 soft : 1;               /* Software trigger */
  UINT32 ps_hold : 1;            /* PS_HOLD trigger */             
  UINT32 pmic_wd : 1;            /* PMIC Watchdog trigger */             
  UINT32 gp1 : 1;                /* Keypad_Reset1 trigger */             
  UINT32 gp2 : 1;                /* Keypad_Reset2 trigger */             
  UINT32 kpdpwr_and_resin : 1;   /* KPDPWR_N and RESIN_N trigger */
  UINT32 resin : 1;              /* RESIN_N trigger */
  UINT32 kpdpwr : 1;             /* KPDPWR_N trigger */
  UINT32 reserved : 4;           /* Reserved bits */
  UINT32 tft : 1;                /* TFT trigger */
  UINT32 reserved1 : 3;          /* Reserved bits */
}PM_PON_SOFT_RESET_REASON_TYPE;

typedef struct
{
  UINT32 reserved1 : 6;     /* Reserved bits */
  UINT32 warm_seq  : 1;     /* Warm sequence */
  UINT32 pon_seq   : 1;     /* PON sequence  */
}PM_PON_ON_STATE_REASON_TYPE;


typedef struct
{
  UINT32 hard_reset : 1;     /* Hard reset event trigger */
  UINT32 smpl : 1;           /* SMPL trigger */             
  UINT32 rtc : 1;            /* RTC trigger */             
  UINT32 dc_chg : 1;         /* DC Charger trigger */             
  UINT32 usb_chg : 1;        /* USB Charger trigger */             
  UINT32 pon1 : 1;           /* PON1 trigger */
  UINT32 cblpwr : 1;         /* CBL_PWR1_N trigger */
  UINT32 kpdpwr : 1;         /* KPDPWR_N trigger */
}PM_PON_REASON_TYPE;

typedef struct
{
  UINT32 reserved1 : 4;             /* Reserved bits */  
  UINT32 fault_n : 1;              /* Triggered by FAULT_N being low more than 10 clock cycles (32k clock) */
  UINT32 pbs_watchdog_to : 1;      /* Triggered by PBS_WATCHDOG_TO in FAULT state */
  UINT32 pbs_nack : 1;             /* Triggered by PBS_NACK in FAULT state */
  UINT32 kpdpwr_andor_resin : 1;   /* KPDPWR_N, or RESIN_N, or KPDPWR_AND_RESIN, or KPDPWR_OR_RESIN   */
}EFI_PM_PON_STAGE3_RESET_REASON_TYPE;

typedef struct
{
  UINT32 gp_fault0 : 1;         /* Triggered by general-purpose fault #0 */
  UINT32 gp_fault1 : 1;         /* Triggered by general-purpose fault #1 */
  UINT32 gp_fault2 : 1;         /* general-purpose fault #2 */
  UINT32 gp_fault3 : 1;         /* general-purpose fault #3 */  
  UINT32 mbg_fault : 1;         /* MBG fault event */
  UINT32 ovlo : 1;              /* OVLO event    */
  UINT32 uvlo : 1;              /* UVLO event    */
  UINT32 avdd_rb : 1;           /* AVDD_RB event */          
  UINT32 reserved1 : 3;         /* Reserved bits */  
  UINT32 fault_n : 1;           /* FAULT_N bus */
  UINT32 pbs_watchdog_to : 1;   /* PBS WATCHDOG */
  UINT32 pbs_nack : 1;          /* PBS NACK event */    
  UINT32 restart_pon : 1;       /* RESTART PON */  
  UINT32 otst3 : 1;             /* OTST3 */
}EFI_PM_PON_FAULT_STATE_REASON_TYPE;

typedef struct
{
  UINT32 reserved1 : 2;               /* Reserved bits */
  UINT32 raw_xvdd_rb_occured : 1;     /* raw_xvdd_rb event occured */
  UINT32 raw_dvdd_rb_occured : 1;     /* raw_dvdd_rb event occured  */
  UINT32 immediate_xvdd_shutdown : 1; /* immediate_xvdd_shutdown s2 Reset */
  UINT32 s3_reset : 1;                /* Stage 3 Reset */
  UINT32 fault_seq : 1;               /* fault-handling sequence */
  UINT32 poff_seq : 1;                /* normal powering-off sequence */
}EFI_PM_PON_OFF_STATE_REASON_TYPE;

typedef struct _EFI_PM_TEST_PON_PS_HOLD_CFG_PARAM
{
    UINT8       DeviceIndex;
    EFI_PM_PON_RESET_CFG_TYPE ResetCfgType;
}EFI_PM_TEST_PON_PS_HOLD_CFG_PARAM, EFI_PM_TEST_PON_OVERTEMP_RESET_CFG_PARAM;

typedef struct _EFI_PM_TEST_PON_RESET_SOURCE_CFG_PARAM
{
    UINT8       DeviceIndex;
    EFI_PM_PON_RESET_SOURCE_TYPE ResetSourceType;
    UINT32 S1_timer;
    UINT32 S2_timer;
    EFI_PM_PON_RESET_CFG_TYPE ResetCfgType;
}EFI_PM_TEST_PON_RESET_SOURCE_CFG_PARAM;

typedef struct _EFI_PM_TEST_PON_RESET_SOURCE_CTL_PARAM
{
    UINT8       DeviceIndex;
    EFI_PM_PON_RESET_SOURCE_TYPE ResetSourceType;
    EFI_PM_PON_ON_OFF_TYPE On_Off;
}EFI_PM_TEST_PON_RESET_SOURCE_CTL_PARAM;

typedef struct _EFI_PM_TEST_PON_STAGE3_RESET_SOURCE_CFG_PARAM
{
    UINT8       DeviceIndex;
    EFI_PM_PON_RESET_SOURCE_TYPE ResetSourceType;
    UINT32 S3_timer;
}EFI_PM_TEST_PON_STAGE3_RESET_SOURCE_CFG_PARAM;

typedef struct _EFI_PM_TEST_PON_GET_POFF_REASON_PARAM
{
    UINT8       DeviceIndex;
    EFI_PM_PON_POFF_REASON_TYPE  *Reason;
}EFI_PM_TEST_PON_GET_POFF_REASON_PARAM;

typedef struct _EFI_PM_TEST_PON_GET_WARM_RESET_PARAM
{
    UINT8       DeviceIndex;
    PM_PON_WARM_RESET_REASON_TYPE  *Reason;
}EFI_PM_TEST_PON_GET_WARM_RESET_PARAM;

typedef struct _EFI_PM_TEST_PON_GET_SOFT_RESET_REASON_PARAM
{
    UINT8       DeviceIndex;
    PM_PON_SOFT_RESET_REASON_TYPE  *Reason;
}EFI_PM_TEST_PON_GET_SOFT_RESET_REASON_PARAM;

typedef struct _EFI_PM_TEST_PON_GET_ALL_REASONS_PARAM
{
    UINT8    DeviceIndex;
    UINT64   *Reason;
}EFI_PM_TEST_PON_GET_ALL_REASONS_PARAM;

typedef struct _EFI_PM_TEST_PON_DEBOUNCE_CTL_PARAM
{
    UINT8    DeviceIndex;
    UINT32   Time_delay;
}EFI_PM_TEST_PON_DEBOUNCE_CTL_PARAM;

typedef struct _EFI_PM_TEST_PON_CONFIG_UVLO_PARAM
{
    UINT8    DeviceIndex;
    UINT32   Uvlo_rising_thresh_voltage_in_mv;
    UINT32   Hyst_voltage_in_mv;
   BOOLEAN  uvlo_enable;
}EFI_PM_TEST_PON_CONFIG_UVLO_PARAM;

typedef struct _EFI_PM_TEST_PON_WARM_RESET_STATUS_PARAM
{
    UINT8    DeviceIndex;
    BOOLEAN * Status;
}EFI_PM_TEST_PON_WARM_RESET_STATUS_PARAM,EFI_PM_TEST_PON_UVLO_RESET_STATUS_PARAM;

typedef struct _EFI_PM_TEST_PON_WARM_RESET_STATUS_CLEAR_PARAM
{
    UINT8    DeviceIndex;
}EFI_PM_TEST_PON_WARM_RESET_STATUS_CLEAR_PARAM;

typedef struct _EFI_PM_TEST_PON_TRIGGER_ENABLE_STATUS_PARAM
{
    UINT8    DeviceIndex;
    EFI_PM_PON_TRIGGER_TYPE TriggerType;
    BOOLEAN * Status;
}EFI_PM_TEST_PON_TRIGGER_ENABLE_STATUS_PARAM;

typedef struct _EFI_PM_TEST_PON_GET_FSM_CURRENT_STATE_PARAM
{
    UINT8    DeviceIndex;
    EFI_PM_PON_FSM_STATUS_TYPE *pon_fsm_status;
}EFI_PM_TEST_PON_GET_FSM_CURRENT_STATE_PARAM;

typedef struct _EFI_PM_TEST_PON_GET_ON_REASON_PARAM
{
    UINT8    DeviceIndex;
    PM_PON_ON_STATE_REASON_TYPE *Reason;
}EFI_PM_TEST_PON_GET_ON_REASON_PARAM;

typedef struct _EFI_PM_TEST_PON_GET_PON_REASON_PARAM
{
    UINT8    DeviceIndex;
    PM_PON_REASON_TYPE *Reason;
}EFI_PM_TEST_PON_GET_PON_REASON_PARAM;

typedef struct _EFI_PM_TEST_PON_GET_STAGE3_RESET_REASON_PARAM
{
    UINT8    DeviceIndex;
    EFI_PM_PON_STAGE3_RESET_REASON_TYPE *Reason;
}EFI_PM_TEST_PON_GET_STAGE3_RESET_REASON_PARAM;

typedef struct _EFI_PM_TEST_PON_GET_FAULT_REASON_PARAM
{
    UINT8    DeviceIndex;
    EFI_PM_PON_FAULT_STATE_REASON_TYPE *Reason;
}EFI_PM_TEST_PON_GET_FAULT_REASON_PARAM;

typedef struct _EFI_PM_TEST_PON_GET_OFF_REASON_PARAM
{
    UINT8    DeviceIndex;
    EFI_PM_PON_OFF_STATE_REASON_TYPE *Reason;
}EFI_PM_TEST_PON_GET_OFF_REASON_PARAM;

typedef struct _EFI_PM_APP_LONG_PWR_KEY_HOLD_CHECK_PARAM
{
   BOOLEAN    * is_key_hold_valid;
}EFI_PM_APP_LONG_PWR_KEY_HOLD_CHECK_PARAM;

typedef enum
{
    EFI_PM_TEST_PON_PS_HOLD_CFG,
    EFI_PM_TEST_PON_RESET_SOURCE_CFG,
    EFI_PM_TEST_PON_OVERTEMP_RESET_CFG,
    EFI_PM_TEST_PON_RESET_SOURCE_CTL,
    EFI_PM_TEST_PON_STAGE3_RESET_SOURCE_CFG,
    EFI_PM_TEST_PON_GET_POFF_REASON,
    EFI_PM_TEST_PON_GET_WARM_RESET,
    EFI_PM_TEST_PON_GET_SOFT_RESET_REASON,
    EFI_PM_TEST_PON_GET_ALL_REASONS,
    EFI_PM_TEST_PON_DEBOUNCE_CTL,
    EFI_PM_TEST_PON_CONFIG_UVLO,
    EFI_PM_TEST_PON_WARM_RESET_STATUS,
    EFI_PM_TEST_PON_WARM_RESET_STATUS_CLEAR,
    EFI_PM_TEST_PON_TRIGGER_ENABLE_STATUS,
   // EFI_PM_TEST_PON_GET_SPARE_REG_DATA,
    EFI_PM_TEST_PON_UVLO_RESET_STATUS,
   EFI_PM_TEST_PON_GET_FSM_CURRENT_STATE,
   EFI_PM_TEST_PON_GET_ON_REASON,
   EFI_PM_TEST_PON_GET_PON_REASON,
   EFI_PM_TEST_PON_GET_STAGE3_RESET_REASON,
   EFI_PM_TEST_PON_GET_FAULT_REASON,
   EFI_PM_TEST_PON_GET_OFF_REASON,
   EFI_PM_APP_LONG_PWR_KEY_HOLD_CHECK,
}EFI_PM_TEST_DRIVER_PON_TYPE_FUNCTION;

typedef union _EFI_PM_TEST_PON_FUNCTION_TYPE
{
    EFI_PM_TEST_PON_PS_HOLD_CFG_PARAM           PonPsHoldCfg;
    EFI_PM_TEST_PON_RESET_SOURCE_CFG_PARAM      PonResetSourceCfg;
    EFI_PM_TEST_PON_OVERTEMP_RESET_CFG_PARAM    PonOvertempResetCfg;
    EFI_PM_TEST_PON_RESET_SOURCE_CTL_PARAM      PonResetSourceCtl;
    EFI_PM_TEST_PON_STAGE3_RESET_SOURCE_CFG_PARAM PonStage3ResetSourceCfg;
    EFI_PM_TEST_PON_GET_POFF_REASON_PARAM       PonGetPoffReason;
    EFI_PM_TEST_PON_GET_WARM_RESET_PARAM        PonGetGetWarmResetReason;
    EFI_PM_TEST_PON_GET_SOFT_RESET_REASON_PARAM       PonGetSoftResetReason;
    EFI_PM_TEST_PON_GET_ALL_REASONS_PARAM    PonGetAllPonReasons;
    EFI_PM_TEST_PON_DEBOUNCE_CTL_PARAM       PondebounceCtl;
    EFI_PM_TEST_PON_CONFIG_UVLO_PARAM        PonConfigUVLO;
    EFI_PM_TEST_PON_WARM_RESET_STATUS_PARAM  PonWarmResetStatus;
    EFI_PM_TEST_PON_WARM_RESET_STATUS_CLEAR_PARAM  PonWarmResetStatusClear;
    EFI_PM_TEST_PON_TRIGGER_ENABLE_STATUS_PARAM  PonTriggerEnableStatus;
   // EFI_PM_TEST_PON_GET_SPARE_REG_DATA_PARAM  PonGetSpareRegData;
    EFI_PM_TEST_PON_UVLO_RESET_STATUS_PARAM   PonUvloResetStatus;
   EFI_PM_TEST_PON_GET_FSM_CURRENT_STATE_PARAM PonGetFsmCurrentState;
   EFI_PM_TEST_PON_GET_ON_REASON_PARAM        PonGetonReason;
   EFI_PM_TEST_PON_GET_PON_REASON_PARAM       PonGetPonReason;
   EFI_PM_TEST_PON_GET_STAGE3_RESET_REASON_PARAM PonStage3ResetReason;
   EFI_PM_TEST_PON_GET_FAULT_REASON_PARAM     PonGetFaultReason;
   EFI_PM_TEST_PON_GET_OFF_REASON_PARAM       PonGetOffReason;
   EFI_PM_APP_LONG_PWR_KEY_HOLD_CHECK_PARAM   PonPwrKeyHoldCheck;
   
   
}EFI_PM_TEST_PON_FUNCTION_TYPE;

/* PMIC Test WLED */

typedef enum
{
    EFI_PM_TEST_WLED_EN_AMOLED,
    EFI_PM_TEST_WLED_CONFIG_SINK_MODULATION,
   EFI_PM_TEST_WLED_SET_CURRENT_SENSE_RATIO,
   
}EFI_PM_TEST_DRIVER_WLED_TYPE_FUNCTION;

typedef struct _EFI_PM_TEST_WLED_EN_AMOLED_PARAM
{
    UINT32       DeviceIndex;
    //EFI_PM_WLED_DISPLAY_TYPE display_type;

} EFI_PM_TEST_WLED_EN_AMOLED_PARAM;


typedef struct _EFI_PM_TEST_WLED_CONFIG_SINK_MODULATION_PARAM
{
    UINT32                    DeviceIndex;
   //EFI_PM_WLED_MOD_CLK_TYPE       mode_clk;
   BOOLEAN                    en_phase_stagger;
   //EFI_PM_WLED_MOD_CLK_TYPE       accum_clk;
   BOOLEAN                    en_hybrid_dim;
   //EFI_PM_WLED_PWM_MODE_TYPE      pwm_mode;
   //EFI_PM_WLED_MODE_DIM_MODE_TYPE  dim_mode;
} EFI_PM_TEST_WLED_CONFIG_SINK_MODULATION_PARAM;

typedef struct _EFI_PM_TEST_WLED_SET_CURRENT_SENSE_RATIO_PARAM
{
    UINT32                 DeviceIndex;
    //EFI_PM_WLED_DISPLAY_TYPE   display_type;
   UINT32                  resistance_kohm;
} EFI_PM_TEST_WLED_SET_CURRENT_SENSE_RATIO_PARAM;


typedef union _EFI_PM_TEST_WLED_FUNCTION_TYPE
{
    EFI_PM_TEST_WLED_EN_AMOLED_PARAM                           Wledenamoled;
    EFI_PM_TEST_WLED_CONFIG_SINK_MODULATION_PARAM                   Wledsinkmodulation; 
   EFI_PM_TEST_WLED_SET_CURRENT_SENSE_RATIO_PARAM              Wledcurrentsenseratio;
}EFI_PM_TEST_WLED_FUNCTION_TYPE;


/* PMIC SPMI DEBUG TEST */
typedef enum
{
   EFI_PM_ENABLE_DEBUG_SPMI, 
}EFI_PM_TEST_DRIVER_ENABLE_DEBUG_SPMI_TYPE_FUNCTION;


typedef struct _EFI_PM_TEST_ENABLE_DEBUG_SPMI_PARAM
{
   BOOLEAN                 DebugMode;

} EFI_PM_TEST_SPMI_DEBUG_PARAM;

typedef union _EFI_PM_TEST_ENABLE_DEBUG_SPMI_FUNCTION_TYPE
{
   EFI_PM_TEST_SPMI_DEBUG_PARAM          SpmiDbgMode;
}EFI_PM_TEST_ENABLE_DEBUG_SPMI_FUNCTION_TYPE;

/*===========================================================================
                       FUNCTION PROTOTYPES
===========================================================================*/



#endif // __PMICTEST_H__




