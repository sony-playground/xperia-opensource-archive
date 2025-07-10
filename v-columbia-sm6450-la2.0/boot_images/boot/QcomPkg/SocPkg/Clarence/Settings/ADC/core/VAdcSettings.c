/*============================================================================
  FILE:         VAdcSettings.c

  OVERVIEW:     Settings for VADC.

  DEPENDENCIES: None

                Copyright (c) 2017-2023 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Proprietary and Confidential.
============================================================================*/
/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.  Please
  use ISO format for dates.

  $Header: //components/dev/core.boot/6.0/aravapal.core.boot.6.0.tip_dev/QcomPkg/SocPkg/Clarence/Settings/ADC/core/VAdcSettings.c#1 $

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2017-11-10  jjo  Initial revision.

============================================================================*/
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "VAdcBsp.h"
#include "AdcInputs.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define ARRAY_LENGTH(a) (sizeof(a) / sizeof((a)[0]))

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/
/*
 * System Thermistor Table
 *
 * The first column in the table is thermistor resistance R_T in ohms
 * and the second column is the temperature in degrees C.
 *
 *               VDD ___
 *                      |
 *                      >
 *                P_PU  <
 *                      >
 *                      |
 *                      |
 *                      |- - - V_T
 *                      |
 *                      >
 *                R_T   <   100 kOhms (NTCG104EF104FB)
 *                      >
 *                      |
 *                      |
 *                     Gnd
 *
 */
static AdcMapPtInt32toInt32Type adcMap_NTCG104EF104FB[] =
{
   { 4251000, -40 },
   { 3004900, -35 },
   { 2148900, -30 },
   { 1553800, -25 },
   { 1135300, -20 },
   {  837800, -15 },
   {  624100, -10 },
   {  469100, -5 },
   {  355600, 0 },
   {  271800, 5 },
   {  209400, 10 },
   {  162500, 15 },
   {  127000, 20 },
   {  100000, 25 },
   {   79200, 30 },
   {   63200, 35 },
   {   50700, 40 },
   {   40900, 45 },
   {   33200, 50 },
   {   27100, 55 },
   {   22200, 60 },
   {   18300, 65 },
   {   15200, 70 },
   {   12600, 75 },
   {   10600, 80 },
   {    8890, 85 },
   {    7500, 90 },
   {    6360, 95 },
   {    5410, 100 },
   {    4620, 105 },
   {    3970, 110 },
   {    3420, 115 },
   {    2950, 120 },
   {    2560, 125 }
};

AdcIntTableType gVAdcSysThermTable =
{
   .pTable  = adcMap_NTCG104EF104FB,
   .uLength = ARRAY_LENGTH(adcMap_NTCG104EF104FB),
};

/*
 * USB input current scaling
 *
 * The first column in the table is ADC input voltage in mV and the
 * second column is current in mA. The scaling is 0.32V/A.
 *
 */
static AdcMapPtInt32toInt32Type adcMap_UsbInI[] =
{
   {    0,    0 },
   { 1875, 5859 },
};

AdcIntTableType gVAdcUsbInITable =
{
   .pTable  = adcMap_UsbInI,
   .uLength = ARRAY_LENGTH(adcMap_UsbInI),
};

/* ICHG_FB 
 * The first column in the table is ADC input voltage in mV and the
 * second column is current in mA. The scaling is 0.16V/A. */
static AdcMapPtInt32toInt32Type adcMap_Ibatt[] =
{
   {    0,     0 },
   { 1875, 11719 },
};

AdcIntTableType gVAdcIbattTable =
{
   .pTable  = adcMap_Ibatt,
   .uLength = ARRAY_LENGTH(adcMap_Ibatt),
};

/* SMB temperature sensor
 * The first column in the table is ADC input voltage in mV and the
 * second column is temperature in mC. The scaling is T(�C) = 25+(25*VADC-24.885)/0.0894 */

static AdcMapPtInt32toInt32Type adcMap_SmbTemp[] =
{
   {    0, -253356 },
   { 1875,  270973 },
};

AdcIntTableType gVAdcSmbTempTable =
{
   .pTable  = adcMap_SmbTemp,
   .uLength = ARRAY_LENGTH(adcMap_SmbTemp),
};

/* 
 * PMIC7 family chip die sensor
 * Input is in uV, output in Temp
 * */
static AdcMapPtInt32toInt32Type adcMap_ChipDieTemp[] =
{
   { 433700, -60000 },
   { 473100, -40000 },
   { 512400, -20000 },
   { 551500, 0  },
   { 590500, 20000 },
   { 629300, 40000 },
   { 667900, 60000 },
   { 706400, 80000 },
   { 744600, 100000 },
   { 782500, 120000 },
   { 820100, 140000 }
};

AdcIntTableType gVAdcChipDieTempTable =
{
   .pTable  = adcMap_ChipDieTemp,
   .uLength = ARRAY_LENGTH(adcMap_ChipDieTemp),
};

/* Charger temperature sensor
 * The first column in the table is ADC input voltage in mV and the
 * second column is temperature in mC. The scaling is T(�C) = VADC/0.0033 - 277.12 */

static AdcMapPtInt32toInt32Type adcMap_ChargerTemp[] =
{
   { 0,   -277120 },
   { 1875, 291062 },
};

AdcIntTableType gVAdcChargerTempTable =
{
   .pTable  = adcMap_ChargerTemp,
   .uLength = ARRAY_LENGTH(adcMap_ChargerTemp),
};

static AdcMapPtInt32toInt32Type adcMap_UsbInI_PM7250B[] =
{
   {    0,    0 },
   { 1875, 9375 },
};

static AdcMapPtInt32toInt32Type adcMap_UsbInI_PMI632[] =
{
   {    0,    0 },
   { 1875, 4687 },
};

AdcIntTableType gVAdcUsbInITable_PM7250B =
{
   .pTable  = adcMap_UsbInI_PM7250B,
   .uLength = ARRAY_LENGTH(adcMap_UsbInI_PM7250B),
};

AdcIntTableType gVAdcUsbInITable_PMI632 =
{
   .pTable  = adcMap_UsbInI_PMI632,
   .uLength = ARRAY_LENGTH(adcMap_UsbInI_PMI632),
};

const char gVAdcDTPathPM8350b[] = "/sw/pmic/adc/vadc/spmi-vadc@3";     

/*----------------------------------------------------------------------------
 * PMK8350 Settings
 * -------------------------------------------------------------------------*/
/*
 * VAdc channel configuration.
 */
VAdcChannelConfigType gVAdcChannelsPMK8350[] =
{
};

uint32 guNumVAdcChannelsPMK8350 = ARRAY_LENGTH(gVAdcChannelsPMK8350);

/*----------------------------------------------------------------------------
 * PM8350 Settings
 * -------------------------------------------------------------------------*/
/*
 * VAdc channel configuration.
 */
VAdcChannelConfigType gVAdcChannelsPM8350[] =
{
};

uint32 guNumVAdcChannelsPM8350 = ARRAY_LENGTH(gVAdcChannelsPM8350);

/*----------------------------------------------------------------------------
 * PM8350B Settings
 * -------------------------------------------------------------------------*/
/*
 * VAdc channel configuration.
 */
VAdcChannelConfigType gVAdcChannelsPM8350B[] =
{
};

uint32 guNumVAdcChannelsPM8350B = ARRAY_LENGTH(gVAdcChannelsPM8350B);

/*----------------------------------------------------------------------------
 * PM7250B Settings
 * -------------------------------------------------------------------------*/
/*
 * VAdc channel configuration.
 */
VAdcChannelConfigType gVAdcChannelsPM7250B[] =
{
   /* PMIC_TEMP2 (internal sensor) */
   {
      .pszName                   = ADC_INPUT_PMIC_TEMP2,
      .uAdcHardwareChannel       = 0x6,
      .eSettlingDelay            = VADC_SETTLING_DELAY_0_US,
      .eAverageMode              = VADC_AVERAGE_1_SAMPLE,
      .eDecimationRatio          = VADC_DECIMATION_RATIO_1024,
      .eCalMethod                = VADC_CAL_METHOD_ABSOLUTE,
      .scalingFactor             = {1, 1},  /* {num, den} */
      .eScalingMethod            = VADC_SCALE_DIE_TEMP_TO_MILLIDEGREES,
      .uPullUp                   = 0,
      .pIntTable                 = NULL,
   },

   /* USB_IN (USB_IN pin) */
   {
      .pszName                   = ADC_INPUT_USB_IN,
      .uAdcHardwareChannel       = 0x8,
      .eSettlingDelay            = VADC_SETTLING_DELAY_0_US,
      .eAverageMode              = VADC_AVERAGE_1_SAMPLE,
      .eDecimationRatio          = VADC_DECIMATION_RATIO_1024,
      .eCalMethod                = VADC_CAL_METHOD_ABSOLUTE,
      .scalingFactor             = {1, 16},  /* {num, den} */
      .eScalingMethod            = VADC_SCALE_TO_MILLIVOLTS,
      .uPullUp                   = 0,
      .pIntTable                 = NULL,
   },
   
   /* USB_IN_I_MA_PM_I */
   {
      .pszName                   = ADC_INPUT_USB_IN_I,
      .uAdcHardwareChannel       = 0x7,
      .eSettlingDelay            = VADC_SETTLING_DELAY_0_US,
      .eAverageMode              = VADC_AVERAGE_1_SAMPLE,
      .eDecimationRatio          = VADC_DECIMATION_RATIO_1024,
      .eCalMethod                = VADC_CAL_METHOD_ABSOLUTE,
      .scalingFactor             = {1, 1},  /* {num, den} */
      .eScalingMethod            = VADC_SCALE_INTERPOLATE_FROM_MILLIVOLTS,
      .uPullUp                   = 0,
      .pIntTable                 = &gVAdcUsbInITable_PM7250B,
   },
   
   /* VBATT (VBATT_SNS pin) */
   {
      .pszName                   = ADC_INPUT_VBATT,
      .uAdcHardwareChannel       = 0x84,
      .eSettlingDelay            = VADC_SETTLING_DELAY_0_US,
      .eAverageMode              = VADC_AVERAGE_1_SAMPLE,
      .eDecimationRatio          = VADC_DECIMATION_RATIO_1024,
      .eCalMethod                = VADC_CAL_METHOD_ABSOLUTE,
      .scalingFactor             = {1, 3},  /* {num, den} */
      .eScalingMethod            = VADC_SCALE_TO_MILLIVOLTS,
      .uPullUp                   = 0,
      .pIntTable                 = NULL,
   },
   
   /* CHG_TEMP (internal sensor) */
   {
      .pszName                   = ADC_INPUT_CHG_TEMP,
      .uAdcHardwareChannel       = 0x9,
      .eSettlingDelay            = VADC_SETTLING_DELAY_0_US,
      .eAverageMode              = VADC_AVERAGE_1_SAMPLE,
      .eDecimationRatio          = VADC_DECIMATION_RATIO_1024,
      .eCalMethod                = VADC_CAL_METHOD_ABSOLUTE,
      .scalingFactor             = {1, 1},  /* {num, den} */
      .eScalingMethod            = VADC_SCALE_CHG_TEMP_TO_MILLIDEGREES,
      .uPullUp                   = 0,
      .pIntTable                 = NULL,
   },
   
   /* BATT_THERM (BAT_THERM pin) */
   {
      .pszName                   = ADC_INPUT_BATT_THERM,
      .uAdcHardwareChannel       = 0x4a,
      .eSettlingDelay            = VADC_SETTLING_DELAY_100_US,
      .eAverageMode              = VADC_AVERAGE_1_SAMPLE,
      .eDecimationRatio          = VADC_DECIMATION_RATIO_1024,
      .eCalMethod                = VADC_CAL_METHOD_RATIOMETRIC,
      .scalingFactor             = {1, 1},  /* {num, den} */
      .eScalingMethod            = VADC_SCALE_THERMISTOR,
      .uPullUp                   = 100000,
      .pIntTable                 = &gVAdcSysThermTable,
   },

   /* BATT_THERM_PU_30K (BAT_THERM pin) */
   {
      .pszName                   = ADC_INPUT_BATT_THERM_PU_30K,
      .uAdcHardwareChannel       = 0x2a,
      .eSettlingDelay            = VADC_SETTLING_DELAY_100_US,
      .eAverageMode              = VADC_AVERAGE_1_SAMPLE,
      .eDecimationRatio          = VADC_DECIMATION_RATIO_1024,
      .eCalMethod                = VADC_CAL_METHOD_RATIOMETRIC,
      .scalingFactor             = {1, 1},  /* {num, den} */
      .eScalingMethod            = VADC_SCALE_THERMISTOR,
      .uPullUp                   = 30000,
      .pIntTable                 = &gVAdcSysThermTable,
   },

   /* BATT_THERM_PU_400K (BAT_THERM pin) */
   {
      .pszName                   = ADC_INPUT_BATT_THERM_PU_400K,
      .uAdcHardwareChannel       = 0x6a,
      .eSettlingDelay            = VADC_SETTLING_DELAY_100_US,
      .eAverageMode              = VADC_AVERAGE_1_SAMPLE,
      .eDecimationRatio          = VADC_DECIMATION_RATIO_1024,
      .eCalMethod                = VADC_CAL_METHOD_RATIOMETRIC,
      .scalingFactor             = {1, 1},  /* {num, den} */
      .eScalingMethod            = VADC_SCALE_THERMISTOR,
      .uPullUp                   = 400000,
      .pIntTable                 = &gVAdcSysThermTable,
   },

   /* BATT_ID_OHMS (BAT_ID pin) */
   {
      .pszName                   = ADC_INPUT_BATT_ID_OHMS,
      .uAdcHardwareChannel       = 0x4b,
      .eSettlingDelay            = VADC_SETTLING_DELAY_100_US,
      .eAverageMode              = VADC_AVERAGE_1_SAMPLE,
      .eDecimationRatio          = VADC_DECIMATION_RATIO_1024,
      .eCalMethod                = VADC_CAL_METHOD_RATIOMETRIC,
      .scalingFactor             = {1, 1},  /* {num, den} */
      .eScalingMethod            = VADC_SCALE_RESISTOR_DIVIDER,
      .uPullUp                   = 100000,
      .pIntTable                 = NULL,
   },

   /* BATT_ID_OHMS_PU_30K (BAT_ID pin) */
   {
      .pszName                   = ADC_INPUT_BATT_ID_OHMS_PU_30K,
      .uAdcHardwareChannel       = 0x2b,
      .eSettlingDelay            = VADC_SETTLING_DELAY_100_US,
      .eAverageMode              = VADC_AVERAGE_1_SAMPLE,
      .eDecimationRatio          = VADC_DECIMATION_RATIO_1024,
      .eCalMethod                = VADC_CAL_METHOD_RATIOMETRIC,
      .scalingFactor             = {1, 1},  /* {num, den} */
      .eScalingMethod            = VADC_SCALE_RESISTOR_DIVIDER,
      .uPullUp                   = 30000,
      .pIntTable                 = NULL,
   },

   /* BATT_ID_OHMS_PU_400K (BAT_ID pin) */
   {
      .pszName                   = ADC_INPUT_BATT_ID_OHMS_PU_400K,
      .uAdcHardwareChannel       = 0x6b,
      .eSettlingDelay            = VADC_SETTLING_DELAY_100_US,
      .eAverageMode              = VADC_AVERAGE_1_SAMPLE,
      .eDecimationRatio          = VADC_DECIMATION_RATIO_1024,
      .eCalMethod                = VADC_CAL_METHOD_RATIOMETRIC,
      .scalingFactor             = {1, 1},  /* {num, den} */
      .eScalingMethod            = VADC_SCALE_RESISTOR_DIVIDER,
      .uPullUp                   = 400000,
      .pIntTable                 = NULL,
   },
};

uint32 guNumVAdcChannelsPM7250B = ARRAY_LENGTH(gVAdcChannelsPM7250B);

/*----------------------------------------------------------------------------
 * PMI632 Settings
 * -------------------------------------------------------------------------*/
/*
 * VAdc channel configuration.
 */
VAdcChannelConfigType gVAdcChannelsPMI632[] =
{
   /* PMIC_TEMP2 (internal sensor) */
   {
      .pszName                   = ADC_INPUT_PMIC_TEMP2,
      .uAdcHardwareChannel       = 0x6,
      .eSettlingDelay            = VADC_SETTLING_DELAY_0_US,
      .eAverageMode              = VADC_AVERAGE_1_SAMPLE,
      .eDecimationRatio          = VADC_DECIMATION_RATIO_1024,
      .eCalMethod                = VADC_CAL_METHOD_ABSOLUTE,
      .scalingFactor             = {1, 1},  /* {num, den} */
      .eScalingMethod            = VADC_SCALE_DIE_TEMP_TO_MILLIDEGREES,
      .uPullUp                   = 0,
      .pIntTable                 = NULL,
   },

   /* USB_IN (USB_IN pin) */
   {
      .pszName                   = ADC_INPUT_USB_IN,
      .uAdcHardwareChannel       = 0x8,
      .eSettlingDelay            = VADC_SETTLING_DELAY_0_US,
      .eAverageMode              = VADC_AVERAGE_1_SAMPLE,
      .eDecimationRatio          = VADC_DECIMATION_RATIO_1024,
      .eCalMethod                = VADC_CAL_METHOD_ABSOLUTE,
      .scalingFactor             = {1, 16},  /* {num, den} */
      .eScalingMethod            = VADC_SCALE_TO_MILLIVOLTS,
      .uPullUp                   = 0,
      .pIntTable                 = NULL,
   },
   
   /* USB_IN_I_MA_PM_I */
   {
      .pszName                   = ADC_INPUT_USB_IN_I,
      .uAdcHardwareChannel       = 0x7,
      .eSettlingDelay            = VADC_SETTLING_DELAY_0_US,
      .eAverageMode              = VADC_AVERAGE_1_SAMPLE,
      .eDecimationRatio          = VADC_DECIMATION_RATIO_1024,
      .eCalMethod                = VADC_CAL_METHOD_ABSOLUTE,
      .scalingFactor             = {1, 1},  /* {num, den} */
      .eScalingMethod            = VADC_SCALE_INTERPOLATE_FROM_MILLIVOLTS,
      .uPullUp                   = 0,
      .pIntTable                 = &gVAdcUsbInITable_PMI632,
   },
   
   /* VBATT (VBATT_SNS pin) */
   {
      .pszName                   = ADC_INPUT_VBATT,
      .uAdcHardwareChannel       = 0x84,
      .eSettlingDelay            = VADC_SETTLING_DELAY_0_US,
      .eAverageMode              = VADC_AVERAGE_1_SAMPLE,
      .eDecimationRatio          = VADC_DECIMATION_RATIO_1024,
      .eCalMethod                = VADC_CAL_METHOD_ABSOLUTE,
      .scalingFactor             = {1, 3},  /* {num, den} */
      .eScalingMethod            = VADC_SCALE_TO_MILLIVOLTS,
      .uPullUp                   = 0,
      .pIntTable                 = NULL,
   },
   
   /* CHG_TEMP (internal sensor) */
   {
      .pszName                   = ADC_INPUT_CHG_TEMP,
      .uAdcHardwareChannel       = 0x9,
      .eSettlingDelay            = VADC_SETTLING_DELAY_0_US,
      .eAverageMode              = VADC_AVERAGE_1_SAMPLE,
      .eDecimationRatio          = VADC_DECIMATION_RATIO_1024,
      .eCalMethod                = VADC_CAL_METHOD_ABSOLUTE,
      .scalingFactor             = {1, 1},  /* {num, den} */
      .eScalingMethod            = VADC_SCALE_CHG_TEMP_TO_MILLIDEGREES,
      .uPullUp                   = 0,
      .pIntTable                 = NULL,
   },
   
   /* BATT_THERM (BAT_THERM pin) */
   {
      .pszName                   = ADC_INPUT_BATT_THERM,
      .uAdcHardwareChannel       = 0x4a,
      .eSettlingDelay            = VADC_SETTLING_DELAY_100_US,
      .eAverageMode              = VADC_AVERAGE_1_SAMPLE,
      .eDecimationRatio          = VADC_DECIMATION_RATIO_1024,
      .eCalMethod                = VADC_CAL_METHOD_RATIOMETRIC,
      .scalingFactor             = {1, 1},  /* {num, den} */
      .eScalingMethod            = VADC_SCALE_THERMISTOR,
      .uPullUp                   = 100000,
      .pIntTable                 = &gVAdcSysThermTable,
   },

   /* BATT_THERM_PU_30K (BAT_THERM pin) */
   {
      .pszName                   = ADC_INPUT_BATT_THERM_PU_30K,
      .uAdcHardwareChannel       = 0x2a,
      .eSettlingDelay            = VADC_SETTLING_DELAY_100_US,
      .eAverageMode              = VADC_AVERAGE_1_SAMPLE,
      .eDecimationRatio          = VADC_DECIMATION_RATIO_1024,
      .eCalMethod                = VADC_CAL_METHOD_RATIOMETRIC,
      .scalingFactor             = {1, 1},  /* {num, den} */
      .eScalingMethod            = VADC_SCALE_THERMISTOR,
      .uPullUp                   = 30000,
      .pIntTable                 = &gVAdcSysThermTable,
   },

   /* BATT_THERM_PU_400K (BAT_THERM pin) */
   {
      .pszName                   = ADC_INPUT_BATT_THERM_PU_400K,
      .uAdcHardwareChannel       = 0x6a,
      .eSettlingDelay            = VADC_SETTLING_DELAY_100_US,
      .eAverageMode              = VADC_AVERAGE_1_SAMPLE,
      .eDecimationRatio          = VADC_DECIMATION_RATIO_1024,
      .eCalMethod                = VADC_CAL_METHOD_RATIOMETRIC,
      .scalingFactor             = {1, 1},  /* {num, den} */
      .eScalingMethod            = VADC_SCALE_THERMISTOR,
      .uPullUp                   = 400000,
      .pIntTable                 = &gVAdcSysThermTable,
   },

   /* BATT_ID_OHMS (BAT_ID pin) */
   {
      .pszName                   = ADC_INPUT_BATT_ID_OHMS,
      .uAdcHardwareChannel       = 0x4b,
      .eSettlingDelay            = VADC_SETTLING_DELAY_100_US,
      .eAverageMode              = VADC_AVERAGE_1_SAMPLE,
      .eDecimationRatio          = VADC_DECIMATION_RATIO_1024,
      .eCalMethod                = VADC_CAL_METHOD_RATIOMETRIC,
      .scalingFactor             = {1, 1},  /* {num, den} */
      .eScalingMethod            = VADC_SCALE_RESISTOR_DIVIDER,
      .uPullUp                   = 100000,
      .pIntTable                 = NULL,
   },

   /* BATT_ID_OHMS_PU_30K (BAT_ID pin) */
   {
      .pszName                   = ADC_INPUT_BATT_ID_OHMS_PU_30K,
      .uAdcHardwareChannel       = 0x2b,
      .eSettlingDelay            = VADC_SETTLING_DELAY_100_US,
      .eAverageMode              = VADC_AVERAGE_1_SAMPLE,
      .eDecimationRatio          = VADC_DECIMATION_RATIO_1024,
      .eCalMethod                = VADC_CAL_METHOD_RATIOMETRIC,
      .scalingFactor             = {1, 1},  /* {num, den} */
      .eScalingMethod            = VADC_SCALE_RESISTOR_DIVIDER,
      .uPullUp                   = 30000,
      .pIntTable                 = NULL,
   },

   /* BATT_ID_OHMS_PU_400K (BAT_ID pin) */
   {
      .pszName                   = ADC_INPUT_BATT_ID_OHMS_PU_400K,
      .uAdcHardwareChannel       = 0x6b,
      .eSettlingDelay            = VADC_SETTLING_DELAY_100_US,
      .eAverageMode              = VADC_AVERAGE_1_SAMPLE,
      .eDecimationRatio          = VADC_DECIMATION_RATIO_1024,
      .eCalMethod                = VADC_CAL_METHOD_RATIOMETRIC,
      .scalingFactor             = {1, 1},  /* {num, den} */
      .eScalingMethod            = VADC_SCALE_RESISTOR_DIVIDER,
      .uPullUp                   = 400000,
      .pIntTable                 = NULL,
   },
};

uint32 guNumVAdcChannelsPMI632 = ARRAY_LENGTH(gVAdcChannelsPMI632);