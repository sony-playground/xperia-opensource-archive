/*============================================================================
  FILE:         VAdcSettings.c

  OVERVIEW:     Settings for VADC.

  DEPENDENCIES: None

                Copyright (c) 2017-2022 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Proprietary and Confidential.
============================================================================*/
/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.  Please
  use ISO format for dates.

  $Header: //components/dev/core.boot/6.1/hadigal.core.boot.6.1.kai_pmic_adc_boot/QcomPkg/SocPkg/Kailua/Settings/ADC/core/VAdcSettings.c#1 $

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
#if 0
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
 * second column is temperature in mC. The scaling is T(°C) = 25+(25*VADC-24.885)/0.0894 */

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
 * second column is temperature in mC. The scaling is T(°C) = VADC/0.0033 - 277.12 */

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

const char gVAdcDTPathPM8550b[] = "/sw/pmic/adc/vadc/spmi-vadc@7";     

/*----------------------------------------------------------------------------
 * PMK8550 Settings
 * -------------------------------------------------------------------------*/
/*
 * VAdc channel configuration.
 */
VAdcChannelConfigType gVAdcChannelsPMK8550[] =
{
};

uint32 guNumVAdcChannelsPMK8550 = ARRAY_LENGTH(gVAdcChannelsPMK8550);

/*----------------------------------------------------------------------------
 * PM8550 Settings
 * -------------------------------------------------------------------------*/
/*
 * VAdc channel configuration.
 */
VAdcChannelConfigType gVAdcChannelsPM8550[] =
{
};

uint32 guNumVAdcChannelsPM8550 = ARRAY_LENGTH(gVAdcChannelsPM8550);

/*----------------------------------------------------------------------------
 * PM8550B Settings
 * -------------------------------------------------------------------------*/
/*
 * VAdc channel configuration.
 */
VAdcChannelConfigType gVAdcChannelsPM8550B[] =
{
};

uint32 guNumVAdcChannelsPM8550B = ARRAY_LENGTH(gVAdcChannelsPM8550B);
#endif
