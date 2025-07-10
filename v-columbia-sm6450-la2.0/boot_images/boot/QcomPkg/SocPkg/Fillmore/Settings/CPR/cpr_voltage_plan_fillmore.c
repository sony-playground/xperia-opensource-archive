/*******************************************************************************
 *
 * Copyright (c) 2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 * THIS IS AUTO-GENERATED CPR CONFIG FILE FOR fillmore.
 *
 * DateTime: 2023/12/05 05:47:43
 *
 *******************************************************************************/
#include "cpr_data.h"
#include "cpr_image_target_init.h"
#include "cpr_target_hwio.h"


//hash value of Voltage Plan file (extracted all cell values)
static char voltage_plan_hash_value[] = "A91A27671B1140E0B853CE624994CF6E";


/*******************************************************************************
********************************************************************************
**
** Voltage Plan Data
**
********************************************************************************
********************************************************************************/

static cpr_fuse_data  fuses_0 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_margin_cfg margins_755275 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   54000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   53000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   53000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =    8000, .closedLoop =   61000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =    8000, .closedLoop =   61000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg_rev  quotients_20052951740 =
{
    .count = 2,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 5, .cprRevMin = 0, .cprRevMax = 1,  .quots = ( cpr_quotient[]) {
 									  { .ro =  8, .quotient =  305 },
                                      { .ro =  9, .quotient =  312 },
                                      { .ro = 10, .quotient =  169 },
                                      { .ro = 12, .quotient =  172 },
                                      { .ro = 15, .quotient =  390 } }  } ,
                                      
	{ .count = 5, .cprRevMin = 2, .cprRevMax = 2,  .quots = ( cpr_quotient[]) {
 									  { .ro =  8, .quotient =  305 },
                                      { .ro =  9, .quotient =  312 },
                                      { .ro = 10, .quotient =  169 },
                                      { .ro = 12, .quotient =  172 },
                                      { .ro = 15, .quotient =  390 } }  }  },
};


static cpr_fuse_data  fuses_1381672524 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR0_TARG_VOLT_SVS2) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR0_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_767275 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg_rev  quotients_24113132466 =
{
    .count = 2,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 5, .cprRevMin = 0, .cprRevMax = 1,  .quots = ( cpr_quotient[]) {
 									  { .ro =  8, .quotient =  454 },
                                      { .ro =  9, .quotient =  462 },
                                      { .ro = 10, .quotient =  299 },
                                      { .ro = 12, .quotient =  303 },
                                      { .ro = 15, .quotient =  555 } }  } ,
                                      
	{ .count = 5, .cprRevMin = 2, .cprRevMax = 2,  .quots = ( cpr_quotient[]) {
 									  { .ro =  8, .quotient =  454 },
                                      { .ro =  9, .quotient =  462 },
                                      { .ro = 10, .quotient =  299 },
                                      { .ro = 12, .quotient =  303 },
                                      { .ro = 15, .quotient =  555 } }  }  },
};


static cpr_fuse_data  fuses_6834573577 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR0_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR0_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_863275 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   65000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   65000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =    8000, .closedLoop =   73000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =    8000, .closedLoop =   73000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg_rev  quotients_20078022064 =
{
    .count = 2,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 5, .cprRevMin = 0, .cprRevMax = 1,  .quots = ( cpr_quotient[]) {
 									  { .ro =  8, .quotient =  553 },
                                      { .ro =  9, .quotient =  564 },
                                      { .ro = 10, .quotient =  394 },
                                      { .ro = 12, .quotient =  389 },
                                      { .ro = 15, .quotient =  655 } }  } ,
                                      
	{ .count = 5, .cprRevMin = 2, .cprRevMax = 2,  .quots = ( cpr_quotient[]) {
 									  { .ro =  8, .quotient =  553 },
                                      { .ro =  9, .quotient =  564 },
                                      { .ro = 10, .quotient =  394 },
                                      { .ro = 12, .quotient =  389 },
                                      { .ro = 15, .quotient =  655 } }  }  },
};


static cpr_fuse_data  fuses_2760948111 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR0_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_1075275 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   62000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   62000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   12000, .closedLoop =   74000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   12000, .closedLoop =   84000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg_rev  quotients_17869172900 =
{
    .count = 2,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 6, .cprRevMin = 0, .cprRevMax = 1,  .quots = ( cpr_quotient[]) {
 									  { .ro =  2, .quotient =  901 },
                                      { .ro =  8, .quotient =  695 },
                                      { .ro =  9, .quotient =  709 },
                                      { .ro = 10, .quotient =  530 },
                                      { .ro = 12, .quotient =  541 },
                                      { .ro = 15, .quotient =  814 } }  } ,
                                      
	{ .count = 3, .cprRevMin = 2, .cprRevMax = 2,  .quots = ( cpr_quotient[]) {
 									  { .ro =  3, .quotient =  925 },
                                      { .ro =  4, .quotient =  809 },
                                      { .ro = 15, .quotient =  814 } }  }  },
};


static cpr_fuse_data  fuses_4517252667 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR0_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR0_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_1099275 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   58000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   54000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   54000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   24000, .closedLoop =   78000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   24000, .closedLoop =   94000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg_rev  quotients_14368764905 =
{
    .count = 2,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 5, .cprRevMin = 0, .cprRevMax = 1,  .quots = ( cpr_quotient[]) {
 									  { .ro =  1, .quotient = 1244 },
                                      { .ro =  2, .quotient = 1070 },
                                      { .ro =  8, .quotient =  836 },
                                      { .ro =  9, .quotient =  850 },
                                      { .ro = 15, .quotient =  981 } }  } ,
                                      
	{ .count = 3, .cprRevMin = 2, .cprRevMax = 2,  .quots = ( cpr_quotient[]) {
 									  { .ro =  3, .quotient = 1086 },
                                      { .ro =  4, .quotient =  960 },
                                      { .ro = 15, .quotient =  981 } }  }  },
};


static cpr_fuse_data  fuses_6883781128 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR0_TARG_VOLT_OFFSET_TUR_4_3), CPR_FUSE_MAPPING(CALIBRATION14, CPR0_TARG_VOLT_OFFSET_TUR_2_0) } } },
};


static cpr_margin_cfg margins_879275 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   62000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -20000, .closedLoop =   38000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   38000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -12000, .closedLoop =   46000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =    8000, .closedLoop =   80000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg_rev  quotients_17612857769 =
{
    .count = 2,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 5, .cprRevMin = 0, .cprRevMax = 1,  .quots = ( cpr_quotient[]) {
 									  { .ro =  1, .quotient = 1379 },
                                      { .ro =  2, .quotient = 1217 },
                                      { .ro =  8, .quotient =  957 },
                                      { .ro =  9, .quotient =  973 },
                                      { .ro = 15, .quotient = 1126 } }  } ,
                                      
	{ .count = 3, .cprRevMin = 2, .cprRevMax = 2,  .quots = ( cpr_quotient[]) {
 									  { .ro =  3, .quotient = 1226 },
                                      { .ro =  4, .quotient = 1091 },
                                      { .ro = 15, .quotient = 1126 } }  }  },
};


static cpr_fuse_data  fuses_4525082036 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR0_TARG_VOLT_SUT) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR0_TARG_VOLT_OFFSET_SUT) } } },
};


static cpr_margin_cfg margins_895275 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   62000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -16000, .closedLoop =   42000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   58000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   -8000, .closedLoop =   50000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   -8000, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_kv_cfg  kvs_14127505577 =
{
    .count = 7,
    .kvs   = (cpr_kv[]) { { .ro =  1, .kv =  277 },
                                { .ro =  2, .kv =  265 },
                                { .ro =  8, .kv =  254 },
                                { .ro =  9, .kv =  251 },
                                { .ro = 10, .kv =  225 },
                                { .ro = 12, .kv =  223 },
                                { .ro = 15, .kv =  267 } },
};


/*
 * CX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_18277749650 =
{
    .modesCount      = 8,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_14127505577,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1,
                                                    CPR_VOLTAGE_MODE_TURBO_L2 },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref = 352000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  352000, .floor =  352000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 556000, .freqDelta =       0, .fuses = &fuses_1381672524, .quotients = &quotients_20052951740, .margins = &margins_755275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  984000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_6834573577, .quotients = &quotients_24113132466, .margins = &margins_767275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  984000, .floor =  552000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_2760948111, .quotients = &quotients_20078022064, .margins = &margins_863275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  984000, .floor =  600000, .freq =       0, .interplEnabled = 45} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_4517252667, .quotients = &quotients_17869172900, .margins = &margins_1075275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  984000, .floor =  656000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_6883781128, .quotients = &quotients_14368764905, .margins = &margins_1099275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  984000, .floor =  716000, .freq =       0, .interplEnabled = 54} } },

        // TURBO_L1
        {.fref = 904000, .freqDelta =       0, .fuses = &fuses_4525082036, .quotients = &quotients_17612857769, .margins = &margins_879275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  984000, .floor =  768000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L2
        {.fref = 904000, .freqDelta =       0, .fuses = &fuses_4525082036, .quotients = &quotients_17612857769, .margins = &margins_895275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  984000, .floor =  768000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_version  ver_ANY_1_0_1_255 = { .foundry = CPR_FOUNDRY_ANY, .min = CPR_CHIPINFO_VERSION(1,0), .max = CPR_CHIPINFO_VERSION(1,255) };


static cpr_margin_cfg margins_496239 = {
    .count = 5,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   56000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   48000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   56000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   48000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg_rev  quotients_11520795539 =
{
    .count = 2,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 5, .cprRevMin = 0, .cprRevMax = 1,  .quots = ( cpr_quotient[]) {
 									  { .ro =  2, .quotient =  441 },
                                      { .ro =  8, .quotient =  275 },
                                      { .ro =  9, .quotient =  286 },
                                      { .ro = 14, .quotient =  279 },
                                      { .ro = 15, .quotient =  354 } }  } ,
                                      
	{ .count = 1, .cprRevMin = 2, .cprRevMax = 2,  .quots = ( cpr_quotient[]) {
 									  { .ro = 14, .quotient =  279 } }  }  },
};


static cpr_fuse_data  fuses_7893773833 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR2_TARG_VOLT_SVS3_5_2), CPR_FUSE_MAPPING(CALIBRATION18, CPR2_TARG_VOLT_SVS3_1_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION20, CPR2_TARG_VOLT_OFFSET_SVS3) } } },
};


static cpr_margin_cfg margins_496240 = {
    .count = 5,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   58000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   46000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   58000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   46000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg_rev  quotients_11018238972 =
{
    .count = 2,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 5, .cprRevMin = 0, .cprRevMax = 1,  .quots = ( cpr_quotient[]) {
 									  { .ro =  2, .quotient =  479 },
                                      { .ro =  8, .quotient =  305 },
                                      { .ro =  9, .quotient =  312 },
                                      { .ro = 14, .quotient =  312 },
                                      { .ro = 15, .quotient =  390 } }  } ,
                                      
	{ .count = 1, .cprRevMin = 2, .cprRevMax = 2,  .quots = ( cpr_quotient[]) {
 									  { .ro = 14, .quotient =  312 } }  }  },
};


static cpr_fuse_data  fuses_3851190683 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION20, CPR2_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_532239 = {
    .count = 5,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   42000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   42000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg_rev  quotients_11275109976 =
{
    .count = 2,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 5, .cprRevMin = 0, .cprRevMax = 1,  .quots = ( cpr_quotient[]) {
 									  { .ro =  2, .quotient =  644 },
                                      { .ro =  8, .quotient =  454 },
                                      { .ro =  9, .quotient =  462 },
                                      { .ro = 14, .quotient =  460 },
                                      { .ro = 15, .quotient =  555 } }  } ,
                                      
	{ .count = 1, .cprRevMin = 2, .cprRevMax = 2,  .quots = ( cpr_quotient[]) {
 									  { .ro = 14, .quotient =  460 } }  }  },
};


static cpr_fuse_data  fuses_1245054604 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION20, CPR2_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_564239 = {
    .count = 5,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   46000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   46000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg_rev  quotients_11053636122 =
{
    .count = 2,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 5, .cprRevMin = 0, .cprRevMax = 1,  .quots = ( cpr_quotient[]) {
 									  { .ro =  2, .quotient =  754 },
                                      { .ro =  8, .quotient =  553 },
                                      { .ro =  9, .quotient =  564 },
                                      { .ro = 14, .quotient =  550 },
                                      { .ro = 15, .quotient =  655 } }  } ,
                                      
	{ .count = 1, .cprRevMin = 2, .cprRevMax = 2,  .quots = ( cpr_quotient[]) {
 									  { .ro = 14, .quotient =  550 } }  }  },
};


static cpr_fuse_data  fuses_7510667436 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION18, CPR2_TARG_VOLT_SVSL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION20, CPR2_TARG_VOLT_OFFSET_SVSL1_4_3), CPR_FUSE_MAPPING(CALIBRATION19, CPR2_TARG_VOLT_OFFSET_SVSL1_2_0) } } },
};


static cpr_margin_cfg margins_568239 = {
    .count = 5,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   51000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   51000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg_rev  quotients_12542877611 =
{
    .count = 2,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 5, .cprRevMin = 0, .cprRevMax = 1,  .quots = ( cpr_quotient[]) {
 									  { .ro =  2, .quotient =  816 },
                                      { .ro =  8, .quotient =  612 },
                                      { .ro =  9, .quotient =  625 },
                                      { .ro = 14, .quotient =  609 },
                                      { .ro = 15, .quotient =  721 } }  } ,
                                      
	{ .count = 1, .cprRevMin = 2, .cprRevMax = 2,  .quots = ( cpr_quotient[]) {
 									  { .ro = 14, .quotient =  609 } }  }  },
};


static cpr_fuse_data  fuses_1514610583 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR2_TARG_VOLT_OFFSET_SVSL2) } } },
};


static cpr_margin_cfg margins_748239 = {
    .count = 5,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   58000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   54000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   58000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   54000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg_rev  quotients_11330952056 =
{
    .count = 2,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 5, .cprRevMin = 0, .cprRevMax = 1,  .quots = ( cpr_quotient[]) {
 									  { .ro =  2, .quotient =  901 },
                                      { .ro =  8, .quotient =  695 },
                                      { .ro =  9, .quotient =  709 },
                                      { .ro = 14, .quotient =  691 },
                                      { .ro = 15, .quotient =  814 } }  } ,
                                      
	{ .count = 1, .cprRevMin = 2, .cprRevMax = 2,  .quots = ( cpr_quotient[]) {
 									  { .ro = 14, .quotient =  691 } }  }  },
};


static cpr_fuse_data  fuses_3966539149 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION18, CPR2_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR2_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_660239 = {
    .count = 5,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   62000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   28000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   62000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   28000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg_rev  quotients_14056414200 =
{
    .count = 2,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 5, .cprRevMin = 0, .cprRevMax = 1,  .quots = ( cpr_quotient[]) {
 									  { .ro =  2, .quotient = 1003 },
                                      { .ro =  8, .quotient =  780 },
                                      { .ro =  9, .quotient =  794 },
                                      { .ro = 14, .quotient =  783 },
                                      { .ro = 15, .quotient =  914 } }  } ,
                                      
	{ .count = 1, .cprRevMin = 2, .cprRevMax = 2,  .quots = ( cpr_quotient[]) {
 									  { .ro = 14, .quotient =  783 } }  }  },
};


static cpr_fuse_data  fuses_6240535511 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION18, CPR2_TARG_VOLT_NOML1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR2_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_kv_cfg  kvs_10745775032 =
{
    .count = 5,
    .kvs   = (cpr_kv[]) { { .ro =  2, .kv =  246 },
                                { .ro =  8, .kv =  241 },
                                { .ro =  9, .kv =  238 },
                                { .ro = 14, .kv =  241 },
                                { .ro = 15, .kv =  250 } },
};


/*
 * GFX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_8476102476 =
{
    .modesCount      = 7,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_10745775032,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_SVS_L2,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1 },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS_D1
        {.fref = 540000, .freqDelta =       0, .fuses = &fuses_7893773833, .quotients = &quotients_11520795539, .margins = &margins_496239,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  940000, .floor =  516000, .freq =  230000, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 556000, .freqDelta =   55000, .fuses = &fuses_3851190683, .quotients = &quotients_11018238972, .margins = &margins_496240,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  940000, .floor =  516000, .freq =  285000, .interplEnabled = 12} } },

        // SVS
        {.fref = 628000, .freqDelta =  158000, .fuses = &fuses_1245054604, .quotients = &quotients_11275109976, .margins = &margins_532239,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  940000, .floor =  552000, .freq =  443000, .interplEnabled = 62} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =   97000, .fuses = &fuses_7510667436, .quotients = &quotients_11053636122, .margins = &margins_564239,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  940000, .floor =  600000, .freq =  540000, .interplEnabled = 0} } },

        // SVS_L2
        {.fref = 712000, .freqDelta =   68000, .fuses = &fuses_1514610583, .quotients = &quotients_12542877611, .margins = &margins_568239,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  940000, .floor =  624000, .freq =  608000, .interplEnabled = 42} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =   68000, .fuses = &fuses_3966539149, .quotients = &quotients_11330952056, .margins = &margins_748239,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  940000, .floor =  656000, .freq =  676000, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 800000, .freqDelta =  104000, .fuses = &fuses_6240535511, .quotients = &quotients_14056414200, .margins = &margins_660239,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  940000, .floor =  696000, .freq =  780000, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_743275 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   54000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   50000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   50000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   10000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   10000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg_rev  quotients_6406535740 =
{
    .count = 1,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 4, .cprRevMin = 0, .cprRevMax = 255,  .quots = ( cpr_quotient[]) {
 									  { .ro =  8, .quotient =  275 },
                                      { .ro =  9, .quotient =  286 },
                                      { .ro = 10, .quotient =  150 },
                                      { .ro = 14, .quotient =  279 } }  }  },
};


static cpr_fuse_data  fuses_7243812983 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR1_TARG_VOLT_SVS3) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION17, CPR1_TARG_VOLT_OFFSET_SVS3) } } },
};


static cpr_margin_cfg margins_779275 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   54000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   54000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   10000, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   10000, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg_rev  quotients_7260688207 =
{
    .count = 1,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 4, .cprRevMin = 0, .cprRevMax = 255,  .quots = ( cpr_quotient[]) {
 									  { .ro =  8, .quotient =  305 },
                                      { .ro =  9, .quotient =  312 },
                                      { .ro = 10, .quotient =  169 },
                                      { .ro = 14, .quotient =  312 } }  }  },
};


static cpr_fuse_data  fuses_1936984012 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION17, CPR1_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_867275 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   68000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =    4000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =    4000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   14000, .closedLoop =   70000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   14000, .closedLoop =   70000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg_rev  quotients_10319580578 =
{
    .count = 1,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 5, .cprRevMin = 0, .cprRevMax = 255,  .quots = ( cpr_quotient[]) {
 									  { .ro =  2, .quotient =  644 },
                                      { .ro =  3, .quotient =  665 },
                                      { .ro =  8, .quotient =  454 },
                                      { .ro =  9, .quotient =  462 },
                                      { .ro = 14, .quotient =  460 } }  }  },
};


static cpr_fuse_data  fuses_4703060797 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR1_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION17, CPR1_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_883275 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =    6000, .closedLoop =   62000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =    6000, .closedLoop =   62000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   16000, .closedLoop =   72000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   16000, .closedLoop =   72000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg_rev  quotients_15997796388 =
{
    .count = 1,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 5, .cprRevMin = 0, .cprRevMax = 255,  .quots = ( cpr_quotient[]) {
 									  { .ro =  2, .quotient =  754 },
                                      { .ro =  3, .quotient =  772 },
                                      { .ro =  8, .quotient =  553 },
                                      { .ro =  9, .quotient =  564 },
                                      { .ro = 14, .quotient =  550 } }  }  },
};


static cpr_fuse_data  fuses_3093140611 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION17, CPR1_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_1299275 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   66000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   10000, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   10000, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   50000, .closedLoop =  104000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   50000, .closedLoop =  104000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg_rev  quotients_7125349873 =
{
    .count = 1,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 5, .cprRevMin = 0, .cprRevMax = 255,  .quots = ( cpr_quotient[]) {
 									  { .ro =  2, .quotient =  901 },
                                      { .ro =  3, .quotient =  925 },
                                      { .ro =  8, .quotient =  695 },
                                      { .ro =  9, .quotient =  709 },
                                      { .ro = 14, .quotient =  691 } }  }  },
};


static cpr_fuse_data  fuses_4433096429 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR1_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION17, CPR1_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_1513275 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   68000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   21000, .closedLoop =   66000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   21000, .closedLoop =   66000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   86000, .closedLoop =  131000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   86000, .closedLoop =  131000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg_rev  quotients_12926956847 =
{
    .count = 1,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 5, .cprRevMin = 0, .cprRevMax = 255,  .quots = ( cpr_quotient[]) {
 									  { .ro =  2, .quotient = 1003 },
                                      { .ro =  3, .quotient = 1022 },
                                      { .ro =  8, .quotient =  780 },
                                      { .ro =  9, .quotient =  794 },
                                      { .ro = 14, .quotient =  783 } }  }  },
};


static cpr_fuse_data  fuses_3111824114 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION17, CPR1_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_margin_cfg margins_239 = {
    .count = 5,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 } }
};


static cpr_quotient_cfg_rev  quotients_13323366083 =
{
    .count = 1,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 5, .cprRevMin = 0, .cprRevMax = 255,  .quots = ( cpr_quotient[]) {
 									  { .ro =  2, .quotient = 1070 },
                                      { .ro =  3, .quotient = 1086 },
                                      { .ro =  8, .quotient =  836 },
                                      { .ro =  9, .quotient =  850 },
                                      { .ro = 14, .quotient =  844 } }  }  },
};


static cpr_fuse_data  fuses_5596264989 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR1_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR1_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_kv_cfg  kvs_10953706932 =
{
    .count = 6,
    .kvs   = (cpr_kv[]) { { .ro =  2, .kv =  253 },
                                { .ro =  3, .kv =  254 },
                                { .ro =  8, .kv =  242 },
                                { .ro =  9, .kv =  240 },
                                { .ro = 10, .kv =  213 },
                                { .ro = 14, .kv =  244 } },
};


/*
 * MSS Voltage Plan
 */
static cpr_voltage_plan voltage_plan_18378270005 =
{
    .modesCount      = 7,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_10953706932,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS_D1
        {.fref = 540000, .freqDelta =       0, .fuses = &fuses_7243812983, .quotients = &quotients_6406535740, .margins = &margins_743275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  924000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 556000, .freqDelta =       0, .fuses = &fuses_1936984012, .quotients = &quotients_7260688207, .margins = &margins_779275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  924000, .floor =  516000, .freq =       0, .interplEnabled = 19} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_4703060797, .quotients = &quotients_10319580578, .margins = &margins_867275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  924000, .floor =  552000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_3093140611, .quotients = &quotients_15997796388, .margins = &margins_883275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  924000, .floor =  600000, .freq =       0, .interplEnabled = 45} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_4433096429, .quotients = &quotients_7125349873, .margins = &margins_1299275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  924000, .floor =  656000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_3111824114, .quotients = &quotients_12926956847, .margins = &margins_1513275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  924000, .floor =  696000, .freq =       0, .interplEnabled = 60} } },

        // TURBO
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_5596264989, .quotients = &quotients_13323366083, .margins = &margins_239,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  924000, .floor =  716000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_7 = {
    .count = 5,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   10000, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   10000, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   10000, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   10000, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =      0 } }
};


static cpr_fuse_data  fuses_3615941229 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION21, CPR3_TARG_VOLT_SVS2) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_margin_cfg margins_8 = {
    .count = 5,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =      0 } }
};


static cpr_fuse_data  fuses_1819834641 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION20, CPR3_TARG_VOLT_SUT) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


/*
 * VDDA Voltage Plan
 */
static cpr_voltage_plan voltage_plan_22784616084 =
{
    .modesCount      = 13,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_MIN_SVS,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_L1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_L2,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_SVS_L2,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L2,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1 },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  352000, .floor =  352000, .freq =       0, .interplEnabled = 0} } },

        // MIN_SVS
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =       0, .floor =       0, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =       0, .floor =       0, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS_L1
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =       0, .floor =       0, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS_L2
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =       0, .floor =       0, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 700000, .freqDelta =       0, .fuses = &fuses_3615941229, .quotients = NULL, .margins = &margins_7,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  952000, .floor =  700000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =       0, .floor =       0, .freq =       0, .interplEnabled = 0} } },

        // SVS_L2
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =       0, .floor =       0, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =       0, .floor =       0, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =       0, .floor =       0, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L2
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =       0, .floor =       0, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 892000, .freqDelta =       0, .fuses = &fuses_1819834641, .quotients = NULL, .margins = &margins_8,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  952000, .floor =  892000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =       0, .floor =       0, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_fuse_data  fuses_1838651896 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION43, CPR4_TARG_VOLT_OFFSET_SVS3) } } },
};


static cpr_fuse_data  fuses_1041496878 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION45, CPR4_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_fuse_data  fuses_3800705406 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION45, CPR4_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_908275 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   64000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   60000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   60000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   60000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   60000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg_rev  quotients_17116288907 =
{
    .count = 1,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 5, .cprRevMin = 0, .cprRevMax = 255,  .quots = ( cpr_quotient[]) {
 									  { .ro =  0, .quotient =  755 },
                                      { .ro =  1, .quotient =  928 },
                                      { .ro =  4, .quotient =  526 },
                                      { .ro =  5, .quotient =  666 },
                                      { .ro =  7, .quotient =  768 } }  }  },
};


static cpr_fuse_data  fuses_8773136827 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION22, CPR4_TARG_VOLT_SVSL1_5_3), CPR_FUSE_MAPPING(CALIBRATION21, CPR4_TARG_VOLT_SVSL1_2_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION22, CPR4_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_768239 = {
    .count = 5,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   66000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   66000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   66000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   66000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_fuse_data  fuses_2282394217 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION42, CPR4_TARG_VOLT_OFFSET_SVSL2) } } },
};


static cpr_margin_cfg margins_1084275 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   64000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   57000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   57000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   57000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   57000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg_rev  quotients_7422087187 =
{
    .count = 1,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 5, .cprRevMin = 0, .cprRevMax = 255,  .quots = ( cpr_quotient[]) {
 									  { .ro =  0, .quotient =  893 },
                                      { .ro =  1, .quotient = 1097 },
                                      { .ro =  4, .quotient =  630 },
                                      { .ro =  5, .quotient =  793 },
                                      { .ro =  7, .quotient =  920 } }  }  },
};


static cpr_fuse_data  fuses_5482569589 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION21, CPR4_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION22, CPR4_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_1112275 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   62000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   61000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   61000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   61000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   61000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg_rev  quotients_13024775569 =
{
    .count = 1,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 5, .cprRevMin = 0, .cprRevMax = 255,  .quots = ( cpr_quotient[]) {
 									  { .ro =  0, .quotient = 1050 },
                                      { .ro =  1, .quotient = 1251 },
                                      { .ro =  4, .quotient =  750 },
                                      { .ro =  5, .quotient =  915 },
                                      { .ro =  7, .quotient = 1065 } }  }  },
};


static cpr_fuse_data  fuses_5602951273 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION21, CPR4_TARG_VOLT_NOML1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION22, CPR4_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_quotient_cfg_rev  quotients_13687991568 =
{
    .count = 1,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 5, .cprRevMin = 0, .cprRevMax = 255,  .quots = ( cpr_quotient[]) {
 									  { .ro =  0, .quotient = 1151 },
                                      { .ro =  1, .quotient = 1350 },
                                      { .ro =  4, .quotient =  829 },
                                      { .ro =  5, .quotient =  995 },
                                      { .ro =  7, .quotient = 1160 } }  }  },
};


static cpr_fuse_data  fuses_5861144976 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION21, CPR4_TARG_VOLT_SUT) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION22, CPR4_TARG_VOLT_OFFSET_SUT) } } },
};


static cpr_margin_cfg margins_1084276 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   68000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   56000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   56000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   56000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   56000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_kv_cfg  kvs_9322034970 =
{
    .count = 5,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =  344 },
                                { .ro =  1, .kv =  334 },
                                { .ro =  4, .kv =  266 },
                                { .ro =  5, .kv =  264 },
                                { .ro =  7, .kv =  306 } },
};


/*
 * MX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_22731918259 =
{
    .modesCount      = 11,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_9322034970,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_SVS_L2,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1,
                                                    CPR_VOLTAGE_MODE_TURBO_L2 },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref = 500000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  568000, .floor =  500000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS_D1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_1838651896, .quotients = NULL, .margins = &margins_239,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_1041496878, .quotients = NULL, .margins = &margins_239,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_3800705406, .quotients = NULL, .margins = &margins_239,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_8773136827, .quotients = &quotients_17116288907, .margins = &margins_908275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  924000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L2
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_2282394217, .quotients = &quotients_17116288907, .margins = &margins_768239,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  924000, .floor =  752000, .freq =       0, .interplEnabled = 60} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_5482569589, .quotients = &quotients_7422087187, .margins = &margins_1084275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  924000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_5602951273, .quotients = &quotients_13024775569, .margins = &margins_1112275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  924000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_5861144976, .quotients = &quotients_13687991568, .margins = &margins_1084275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  924000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_5861144976, .quotients = &quotients_13687991568, .margins = &margins_1084276,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  924000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L2
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_5861144976, .quotients = &quotients_13687991568, .margins = &margins_1084276,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  924000, .floor =  800000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_fuse_data  fuses_76500091 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION43, CPR5_TARG_VOLT_OFFSET_SVS3) } } },
};


static cpr_fuse_data  fuses_1427184925 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION45, CPR5_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_fuse_data  fuses_2557821588 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION45, CPR5_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_fuse_data  fuses_5838788779 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR5_TARG_VOLT_SVSL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION24, CPR5_TARG_VOLT_OFFSET_SVSL1_4_2), CPR_FUSE_MAPPING(CALIBRATION23, CPR5_TARG_VOLT_OFFSET_SVSL1_1_0) } } },
};


static cpr_margin_cfg margins_920275 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   66000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   61000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   61000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   61000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   61000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_fuse_data  fuses_3829009392 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION42, CPR5_TARG_VOLT_OFFSET_SVSL2) } } },
};


static cpr_margin_cfg margins_1068275 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   64000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   55000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   55000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   55000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   55000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_fuse_data  fuses_7975437249 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR5_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR5_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_1056275 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   62000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   54000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   54000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   54000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   54000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_fuse_data  fuses_4026425888 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR5_TARG_VOLT_NOML1_5_3), CPR_FUSE_MAPPING(CALIBRATION22, CPR5_TARG_VOLT_NOML1_2_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR5_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_margin_cfg margins_1092275 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   64000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   58000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   58000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   58000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   58000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_fuse_data  fuses_2297732919 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION22, CPR5_TARG_VOLT_SUT) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR5_TARG_VOLT_OFFSET_SUT) } } },
};


static cpr_kv_cfg  kvs_6708054417 =
{
    .count = 5,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =  344 },
                                { .ro =  1, .kv =  333 },
                                { .ro =  4, .kv =  265 },
                                { .ro =  5, .kv =  264 },
                                { .ro =  7, .kv =  307 } },
};


/*
 * MXC Voltage Plan
 */
static cpr_voltage_plan voltage_plan_26815162617 =
{
    .modesCount      = 11,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_6708054417,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_SVS_L2,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1,
                                                    CPR_VOLTAGE_MODE_TURBO_L2 },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref = 500000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  568000, .floor =  500000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS_D1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_76500091, .quotients = NULL, .margins = &margins_239,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_1427184925, .quotients = NULL, .margins = &margins_239,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_2557821588, .quotients = NULL, .margins = &margins_239,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_5838788779, .quotients = &quotients_17116288907, .margins = &margins_908275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  924000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L2
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_3829009392, .quotients = &quotients_17116288907, .margins = &margins_920275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  924000, .floor =  752000, .freq =       0, .interplEnabled = 60} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_7975437249, .quotients = &quotients_7422087187, .margins = &margins_1068275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  924000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_4026425888, .quotients = &quotients_13024775569, .margins = &margins_1056275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  924000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_2297732919, .quotients = &quotients_13687991568, .margins = &margins_1092275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  924000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_2297732919, .quotients = &quotients_13687991568, .margins = &margins_1092275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  924000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L2
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_2297732919, .quotients = &quotients_13687991568, .margins = &margins_1092275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  924000, .floor =  800000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_9 = {
    .count = 5,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 } }
};


static cpr_fuse_data  fuses_1526539627 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION44, CPR6_TARG_VOLT_OFFSET_SVS3) } } },
};


static cpr_fuse_data  fuses_2391644124 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION44, CPR6_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_fuse_data  fuses_3291561244 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION44, CPR6_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_fuse_data  fuses_4620315138 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION24, CPR6_TARG_VOLT_SVSL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION44, CPR6_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_59923 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -10000, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -10000, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -10000, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -10000, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 } }
};


static cpr_fuse_data  fuses_4984531371 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION24, CPR6_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION44, CPR6_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_59924 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -20000, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -20000, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -20000, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -20000, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 } }
};


static cpr_fuse_data  fuses_3543782566 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION24, CPR6_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION44, CPR6_TARG_VOLT_OFFSET_TUR) } } },
};


/*
 * LPI_MX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_14795187783 =
{
    .modesCount      = 7,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref = 500000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  568000, .floor =  500000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS_D1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_1526539627, .quotients = NULL, .margins = &margins_9,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_2391644124, .quotients = NULL, .margins = &margins_9,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_3291561244, .quotients = NULL, .margins = &margins_9,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_4620315138, .quotients = NULL, .margins = &margins_9,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  920000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_4984531371, .quotients = NULL, .margins = &margins_59923,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  920000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_3543782566, .quotients = NULL, .margins = &margins_59924,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  920000, .floor =  800000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_767276 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   52000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   49000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   49000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   16000, .closedLoop =   65000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   16000, .closedLoop =   65000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg_rev  quotients_9927102388 =
{
    .count = 1,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 4, .cprRevMin = 0, .cprRevMax = 255,  .quots = ( cpr_quotient[]) {
 									  { .ro =  2, .quotient =  441 },
                                      { .ro =  3, .quotient =  466 },
                                      { .ro =  8, .quotient =  275 },
                                      { .ro =  9, .quotient =  286 } }  }  },
};


static cpr_fuse_data  fuses_4421947029 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION25, CPR7_TARG_VOLT_SVS3) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION26, CPR7_TARG_VOLT_OFFSET_SVS3) } } },
};


static cpr_margin_cfg margins_735275 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   52000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   12000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   12000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg_rev  quotients_8398824454 =
{
    .count = 1,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 4, .cprRevMin = 0, .cprRevMax = 255,  .quots = ( cpr_quotient[]) {
 									  { .ro =  2, .quotient =  479 },
                                      { .ro =  3, .quotient =  503 },
                                      { .ro =  8, .quotient =  305 },
                                      { .ro =  9, .quotient =  312 } }  }  },
};


static cpr_fuse_data  fuses_3238599513 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION26, CPR7_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_755276 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   54000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   50000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   50000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   12000, .closedLoop =   62000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   12000, .closedLoop =   62000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg_rev  quotients_10912610446 =
{
    .count = 1,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 5, .cprRevMin = 0, .cprRevMax = 255,  .quots = ( cpr_quotient[]) {
 									  { .ro =  2, .quotient =  644 },
                                      { .ro =  3, .quotient =  665 },
                                      { .ro =  8, .quotient =  454 },
                                      { .ro =  9, .quotient =  462 },
                                      { .ro = 15, .quotient =  555 } }  }  },
};


static cpr_fuse_data  fuses_3364113955 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION25, CPR7_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION26, CPR7_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_799275 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   52000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   12000, .closedLoop =   68000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   12000, .closedLoop =   68000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg_rev  quotients_15286693233 =
{
    .count = 1,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 5, .cprRevMin = 0, .cprRevMax = 255,  .quots = ( cpr_quotient[]) {
 									  { .ro =  2, .quotient =  754 },
                                      { .ro =  3, .quotient =  772 },
                                      { .ro =  8, .quotient =  553 },
                                      { .ro =  9, .quotient =  564 },
                                      { .ro = 15, .quotient =  655 } }  }  },
};


static cpr_fuse_data  fuses_1645699429 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION26, CPR7_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_947275 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   50000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   53000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   53000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =    8000, .closedLoop =   61000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =    8000, .closedLoop =   61000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg_rev  quotients_5650949183 =
{
    .count = 1,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 5, .cprRevMin = 0, .cprRevMax = 255,  .quots = ( cpr_quotient[]) {
 									  { .ro =  2, .quotient =  901 },
                                      { .ro =  3, .quotient =  925 },
                                      { .ro =  8, .quotient =  695 },
                                      { .ro =  9, .quotient =  709 },
                                      { .ro = 15, .quotient =  814 } }  }  },
};


static cpr_fuse_data  fuses_3389726214 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION25, CPR7_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION26, CPR7_TARG_VOLT_OFFSET_NOM_4_3), CPR_FUSE_MAPPING(CALIBRATION25, CPR7_TARG_VOLT_OFFSET_NOM_2_0) } } },
};


static cpr_margin_cfg margins_987275 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   54000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   57000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   57000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =    8000, .closedLoop =   65000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =    8000, .closedLoop =   65000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg_rev  quotients_12441957028 =
{
    .count = 1,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 5, .cprRevMin = 0, .cprRevMax = 255,  .quots = ( cpr_quotient[]) {
 									  { .ro =  2, .quotient = 1070 },
                                      { .ro =  3, .quotient = 1086 },
                                      { .ro =  8, .quotient =  836 },
                                      { .ro =  9, .quotient =  850 },
                                      { .ro = 15, .quotient =  981 } }  }  },
};


static cpr_fuse_data  fuses_6048082106 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION25, CPR7_TARG_VOLT_TUR_5), CPR_FUSE_MAPPING(CALIBRATION24, CPR7_TARG_VOLT_TUR_4_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION25, CPR7_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_kv_cfg  kvs_14811256486 =
{
    .count = 5,
    .kvs   = (cpr_kv[]) { { .ro =  2, .kv =  256 },
                                { .ro =  3, .kv =  257 },
                                { .ro =  8, .kv =  244 },
                                { .ro =  9, .kv =  242 },
                                { .ro = 15, .kv =  257 } },
};


/*
 * LPI_CX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_18077834056 =
{
    .modesCount      = 7,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_14811256486,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref = 352000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  352000, .floor =  352000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS_D1
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_4421947029, .quotients = &quotients_9927102388, .margins = &margins_767276,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  520000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 552000, .freqDelta =       0, .fuses = &fuses_3238599513, .quotients = &quotients_8398824454, .margins = &margins_735275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  520000, .freq =       0, .interplEnabled = 19} } },

        // SVS
        {.fref = 624000, .freqDelta =       0, .fuses = &fuses_3364113955, .quotients = &quotients_10912610446, .margins = &margins_755276,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  552000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 680000, .freqDelta =       0, .fuses = &fuses_1645699429, .quotients = &quotients_15286693233, .margins = &margins_799275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  600000, .freq =       0, .interplEnabled = 45} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_3389726214, .quotients = &quotients_5650949183, .margins = &margins_947275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  656000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_6048082106, .quotients = &quotients_12441957028, .margins = &margins_987275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  720000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_727275 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   52000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg_rev  quotients_9518819036 =
{
    .count = 1,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 4, .cprRevMin = 0, .cprRevMax = 255,  .quots = ( cpr_quotient[]) {
 									  { .ro =  8, .quotient =  305 },
                                      { .ro =  9, .quotient =  312 },
                                      { .ro = 10, .quotient =  169 },
                                      { .ro = 12, .quotient =  172 } }  }  },
};


static cpr_fuse_data  fuses_4822984192 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION27, CPR8_TARG_VOLT_SVS2) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION28, CPR8_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_683275 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   52000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   58000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   58000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -10000, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -10000, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg_rev  quotients_11248682175 =
{
    .count = 1,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 6, .cprRevMin = 0, .cprRevMax = 255,  .quots = ( cpr_quotient[]) {
 									  { .ro =  2, .quotient =  644 },
                                      { .ro =  3, .quotient =  665 },
                                      { .ro =  8, .quotient =  454 },
                                      { .ro =  9, .quotient =  462 },
                                      { .ro = 10, .quotient =  299 },
                                      { .ro = 12, .quotient =  303 } }  }  },
};


static cpr_fuse_data  fuses_5167498639 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION27, CPR8_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION28, CPR8_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_651275 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   54000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -24000, .closedLoop =   40000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -24000, .closedLoop =   40000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg_rev  quotients_15799534866 =
{
    .count = 1,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 5, .cprRevMin = 0, .cprRevMax = 255,  .quots = ( cpr_quotient[]) {
 									  { .ro =  2, .quotient =  754 },
                                      { .ro =  3, .quotient =  772 },
                                      { .ro =  8, .quotient =  553 },
                                      { .ro =  9, .quotient =  564 },
                                      { .ro = 12, .quotient =  389 } }  }  },
};


static cpr_fuse_data  fuses_1117228456 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION28, CPR8_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_855275 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -24000, .closedLoop =   40000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -24000, .closedLoop =   40000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg_rev  quotients_8083158581 =
{
    .count = 1,
    .data = ( struct cpr_quotient_cfg[]) { 
	{ .count = 5, .cprRevMin = 0, .cprRevMax = 255,  .quots = ( cpr_quotient[]) {
 									  { .ro =  2, .quotient =  901 },
                                      { .ro =  3, .quotient =  925 },
                                      { .ro =  8, .quotient =  695 },
                                      { .ro =  9, .quotient =  709 },
                                      { .ro = 12, .quotient =  541 } }  }  },
};


static cpr_fuse_data  fuses_4665720654 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION27, CPR8_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION27, CPR8_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_kv_cfg  kvs_8012198519 =
{
    .count = 6,
    .kvs   = (cpr_kv[]) { { .ro =  2, .kv =  261 },
                                { .ro =  3, .kv =  261 },
                                { .ro =  8, .kv =  246 },
                                { .ro =  9, .kv =  243 },
                                { .ro = 10, .kv =  209 },
                                { .ro = 12, .kv =  206 } },
};


/*
 * MM Voltage Plan
 */
static cpr_voltage_plan voltage_plan_9801664310 =
{
    .modesCount      = 4,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_8012198519,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS
        {.fref = 556000, .freqDelta =       0, .fuses = &fuses_4822984192, .quotients = &quotients_9518819036, .margins = &margins_727275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  824000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_5167498639, .quotients = &quotients_11248682175, .margins = &margins_683275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  824000, .floor =  552000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_1117228456, .quotients = &quotients_15799534866, .margins = &margins_651275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  824000, .floor =  600000, .freq =       0, .interplEnabled = 45} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_4665720654, .quotients = &quotients_8083158581, .margins = &margins_855275,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  824000, .floor =  656000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_10 = {
    .count = 5,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -30000, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -30000, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -30000, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 3, .vpIdMax = 3,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -30000, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 } }
};


/*
 * WMSS_CX_1 Voltage Plan
 */
static cpr_voltage_plan voltage_plan_9313894912 =
{
    .modesCount      = 3,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_NOMINAL },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS
        {.fref = 592000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_239,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  648000, .floor =  504000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 672000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_239,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  720000, .floor =  592000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_10,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  864000, .floor =  712000, .freq =       0, .interplEnabled = 0} } }},
};


/*
 * WMSS_CX_2 Voltage Plan
 */
static cpr_voltage_plan voltage_plan_3889553521 =
{
    .modesCount      = 3,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_NOMINAL },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS
        {.fref = 588000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_239,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  588000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 668000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_239,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  728000, .floor =  596000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 744000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_239,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  800000, .floor =  652000, .freq =       0, .interplEnabled = 0} } }},
};


/*
 * NAV_LDO Voltage Plan
 */
static cpr_voltage_plan voltage_plan_3863315186 =
{
    .modesCount      = 1,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_NOMINAL },
    .modes           = (struct cpr_voltage_data[]) {
        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } }},
};


/*
 * Aging configs
 */

static cpr_aging_cfg  aging_cfg_cx =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO_L1,
    .sensorID             = 2,
    .kv                   = 104,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 2, .data = (struct raw_fuse_data[]) {
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D40 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<2) | (1<<1) | (1<<0)},
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D3C & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 27, (1<<31) | (1<<30) | (1<<29) | (1<<28) | (1<<27)} } }
};


static cpr_aging_cfg  aging_cfg_gfx =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO_L1,
    .sensorID             = 0,
    .kv                   = 109,
    .scalingFactor        = 15,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D50 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 17, (1<<24) | (1<<23) | (1<<22) | (1<<21) | (1<<20) | (1<<19) | (1<<18) | (1<<17)} } }
};


static cpr_aging_cfg  aging_cfg_mss =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO,
    .sensorID             = 25,
    .kv                   = 109,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 2, .data = (struct raw_fuse_data[]) {
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D48 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1) | (1<<0)},
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D44 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 30, (1<<31) | (1<<30)} } }
};


static cpr_aging_cfg  aging_cfg_mx =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO,
    .sensorID             = 11,
    .kv                   = 110,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8DA4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 23, (1<<30) | (1<<29) | (1<<28) | (1<<27) | (1<<26) | (1<<25) | (1<<24) | (1<<23)} } }
};


static cpr_aging_cfg  aging_cfg_lpi_cx =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_NOMINAL,
    .sensorID             = 5,
    .kv                   = 111,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D68 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 22, (1<<29) | (1<<28) | (1<<27) | (1<<26) | (1<<25) | (1<<24) | (1<<23) | (1<<22)} } }
};


static cpr_aging_cfg  aging_cfg_mm =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_NOMINAL,
    .sensorID             = 0,
    .kv                   = 113,
    .scalingFactor        = 15,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D70 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 20, (1<<27) | (1<<26) | (1<<25) | (1<<24) | (1<<23) | (1<<22) | (1<<21) | (1<<20)} } }
};


/*
 * Versioned Voltage Plans
 */

static cpr_versioned_voltage_plan cx_vvp = {
    .rail     = CPR_RAIL_CX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_18277749650 },
     },
    .count    = 1,
    .agingCfg = &aging_cfg_cx
};


static cpr_versioned_voltage_plan gfx_vvp = {
    .rail     = CPR_RAIL_GFX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_8476102476 },
     },
    .count    = 1,
    .agingCfg = &aging_cfg_gfx
};


static cpr_versioned_voltage_plan mss_vvp = {
    .rail     = CPR_RAIL_MSS,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_18378270005 },
     },
    .count    = 1,
    .agingCfg = &aging_cfg_mss
};


static cpr_versioned_voltage_plan vdda_vvp = {
    .rail     = CPR_RAIL_VDDA,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_22784616084 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan mx_vvp = {
    .rail     = CPR_RAIL_MX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_22731918259 },
     },
    .count    = 1,
    .agingCfg = &aging_cfg_mx
};


static cpr_versioned_voltage_plan mxc_vvp = {
    .rail     = CPR_RAIL_MXC,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_26815162617 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan lpi_mx_vvp = {
    .rail     = CPR_RAIL_LPI_MX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_14795187783 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan lpi_cx_vvp = {
    .rail     = CPR_RAIL_LPI_CX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_18077834056 },
     },
    .count    = 1,
    .agingCfg = &aging_cfg_lpi_cx
};


static cpr_versioned_voltage_plan mm_vvp = {
    .rail     = CPR_RAIL_MM,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_9801664310 },
     },
    .count    = 1,
    .agingCfg = &aging_cfg_mm
};


static cpr_versioned_voltage_plan wmss_cx_1_vvp = {
    .rail     = CPR_RAIL_WMSS_CX_1,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_9313894912 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan wmss_cx_2_vvp = {
    .rail     = CPR_RAIL_WMSS_CX_2,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_3889553521 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan wmss_cx_3_vvp = {
    .rail     = CPR_RAIL_WMSS_CX_3,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_9313894912 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan nav_ldo_vvp = {
    .rail     = CPR_RAIL_NAV_LDO,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_3863315186 },
     },
    .count    = 1,
    .agingCfg = NULL
};

/*******************************************************************************
********************************************************************************
**
** Enablement Config Data
**
********************************************************************************
********************************************************************************/

/*
 * CPR Controller Thread Config
 */

static cpr_hal_thread_cfg mss_thread_cfg = {
    .upThresh     = 2,
    .dnThresh     = 2,
    .consecUp     = 0,
    .consecDn     = 0,
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27 },
    .sensorsCount = 28,
};


static cpr_hal_thread  mss_thread = {
    .id   = 0,
    .cfg  = &mss_thread_cfg,
};


static cpr_hal_thread_cfg cx_thread_cfg = {
    .upThresh     = 2,
    .dnThresh     = 2,
    .consecUp     = 0,
    .consecDn     = 0,
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53 },
    .sensorsCount = 54,
};


static cpr_hal_thread  cx_thread = {
    .id   = 0,
    .cfg  = &cx_thread_cfg,
};


static cpr_hal_thread_cfg gfx_thread_cfg = {
    .upThresh     = 2,
    .dnThresh     = 2,
    .consecUp     = 0,
    .consecDn     = 0,
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27 },
    .sensorsCount = 28,
};


static cpr_hal_thread  gfx_thread = {
    .id   = 0,
    .cfg  = &gfx_thread_cfg,
};


static cpr_hal_thread_cfg lpi_cx_thread_cfg = {
    .upThresh     = 2,
    .dnThresh     = 2,
    .consecUp     = 0,
    .consecDn     = 0,
    .sensors      = (uint8[]){ 3,4,5 },
    .sensorsCount = 3,
};


static cpr_hal_thread  lpi_cx_thread = {
    .id   = 0,
    .cfg  = &lpi_cx_thread_cfg,
};


static cpr_hal_thread_cfg mm_thread_cfg = {
    .upThresh     = 2,
    .dnThresh     = 2,
    .consecUp     = 0,
    .consecDn     = 0,
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13 },
    .sensorsCount = 14,
};


static cpr_hal_thread  mm_thread = {
    .id   = 0,
    .cfg  = &mm_thread_cfg,
};


static cpr_hal_thread_cfg mx_thread_cfg = {
    .upThresh     = 2,
    .dnThresh     = 2,
    .consecUp     = 0,
    .consecDn     = 0,
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,15,16,17,18,19,20 },
    .sensorsCount = 19,
};


static cpr_hal_thread  mx_thread = {
    .id   = 0,
    .cfg  = &mx_thread_cfg,
};


static cpr_hal_thread_cfg mxc_thread_cfg = {
    .upThresh     = 2,
    .dnThresh     = 2,
    .consecUp     = 0,
    .consecDn     = 0,
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28 },
    .sensorsCount = 29,
};


static cpr_hal_thread  mxc_thread = {
    .id   = 0,
    .cfg  = &mxc_thread_cfg,
};


/*
 * CPR Controller Config
 */

static cpr_hal_controller_cfg cpr3_controller_cfg = {
    .stepQuotMin         = 8,
    .stepQuotMax         = 13,
    .sensorsTotal        = 28,
    .bypassSensors       = NULL,
    .bypassSensorsCount  = 0,
    .disableSensors      = NULL,
    .disableSensorsCount = 0,
    .refClk              = NULL,
    .ahbClk              = NULL,
};


static cpr_hal_controller  cpr3_controller = {
    .base                = 0x2bd80000,
    .type                = CPR_CONTROLLER_TYPE_HW_CL_ONLY,
    .cfg                 = &cpr3_controller_cfg,
    .threads             = (cpr_hal_thread*[]){ &mss_thread },
    .threadsCount        = 1,
};


static cpr_hal_controller_cfg cx_cpr3_controller_cfg = {
    .stepQuotMin         = 8,
    .stepQuotMax         = 12,
    .sensorsTotal        = 54,
    .bypassSensors       = NULL,
    .bypassSensorsCount  = 0,
    .disableSensors      = (uint8[]){ 0,1,4,5,12,13,16,17,19,31 },
    .disableSensorsCount = 10,
    .refClk              = NULL,
    .ahbClk              = NULL,
};


static cpr_hal_controller  cx_cpr3_controller = {
    .base                = 0x628000,
    .type                = CPR_CONTROLLER_TYPE_HW_CL_ONLY,
    .cfg                 = &cx_cpr3_controller_cfg,
    .threads             = (cpr_hal_thread*[]){ &cx_thread },
    .threadsCount        = 1,
};


static cpr_hal_controller_cfg gpu_cpr_controller_cfg = {
    .stepQuotMin         = 8,
    .stepQuotMax         = 19,
    .sensorsTotal        = 28,
    .bypassSensors       = NULL,
    .bypassSensorsCount  = 0,
    .disableSensors      = NULL,
    .disableSensorsCount = 0,
    .refClk              = NULL,
    .ahbClk              = NULL,
};


static cpr_hal_controller  gpu_cpr_controller = {
    .base                = 0x3d9a000,
    .type                = CPR_CONTROLLER_TYPE_HW_CL_ONLY,
    .cfg                 = &gpu_cpr_controller_cfg,
    .threads             = (cpr_hal_thread*[]){ &gfx_thread },
    .threadsCount        = 1,
};


static cpr_hal_controller_cfg lpass_cpr3_controller_cfg = {
    .stepQuotMin         = 8,
    .stepQuotMax         = 13,
    .sensorsTotal        = 6,
    .bypassSensors       = NULL,
    .bypassSensorsCount  = 0,
    .disableSensors      = (uint8[]){ 0,1,2 },
    .disableSensorsCount = 3,
    .refClk              = NULL,
    .ahbClk              = NULL,
};


static cpr_hal_controller  lpass_cpr3_controller = {
    .base                = 0x3430000,
    .type                = CPR_CONTROLLER_TYPE_HW_CL_ONLY,
    .cfg                 = &lpass_cpr3_controller_cfg,
    .threads             = (cpr_hal_thread*[]){ &lpi_cx_thread },
    .threadsCount        = 1,
};


static cpr_hal_controller_cfg mmcx_cpr3_controller_cfg = {
    .stepQuotMin         = 8,
    .stepQuotMax         = 13,
    .sensorsTotal        = 14,
    .bypassSensors       = NULL,
    .bypassSensorsCount  = 0,
    .disableSensors      = NULL,
    .disableSensorsCount = 0,
    .refClk              = NULL,
    .ahbClk              = NULL,
};


static cpr_hal_controller  mmcx_cpr3_controller = {
    .base                = 0x630000,
    .type                = CPR_CONTROLLER_TYPE_HW_CL_ONLY,
    .cfg                 = &mmcx_cpr3_controller_cfg,
    .threads             = (cpr_hal_thread*[]){ &mm_thread },
    .threadsCount        = 1,
};


static cpr_hal_controller_cfg mx_cpr3_controller_cfg = {
    .stepQuotMin         = 7,
    .stepQuotMax         = 13,
    .sensorsTotal        = 50,
    .bypassSensors       = (uint8[]){ 13,14,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49 },
    .bypassSensorsCount  = 31,
    .disableSensors      = (uint8[]){ 13,14,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49 },
    .disableSensorsCount = 31,
    .refClk              = NULL,
    .ahbClk              = NULL,
};


static cpr_hal_controller  mx_cpr3_controller = {
    .base                = 0x638000,
    .type                = CPR_CONTROLLER_TYPE_HW_CL_ONLY,
    .cfg                 = &mx_cpr3_controller_cfg,
    .threads             = (cpr_hal_thread*[]){ &mx_thread },
    .threadsCount        = 1,
};


static cpr_hal_controller_cfg mxc_cpr3_controller_cfg = {
    .stepQuotMin         = 7,
    .stepQuotMax         = 13,
    .sensorsTotal        = 29,
    .bypassSensors       = NULL,
    .bypassSensorsCount  = 0,
    .disableSensors      = NULL,
    .disableSensorsCount = 0,
    .refClk              = NULL,
    .ahbClk              = NULL,
};


static cpr_hal_controller  mxc_cpr3_controller = {
    .base                = 0x62c000,
    .type                = CPR_CONTROLLER_TYPE_HW_CL_ONLY,
    .cfg                 = &mxc_cpr3_controller_cfg,
    .threads             = (cpr_hal_thread*[]){ &mxc_thread },
    .threadsCount        = 1,
};


/*
 * HAL Rail Config
 */

static cpr_rail cpr_rail_cx_cfg = {
    .id               = CPR_RAIL_CX,
    .name             = "CX",
    .hal              = { .controller = &cx_cpr3_controller, .thread = &cx_thread },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


static cpr_rail cpr_rail_gfx_cfg = {
    .id               = CPR_RAIL_GFX,
    .name             = "GFX",
    .hal              = { .controller = &gpu_cpr_controller, .thread = &gfx_thread },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


static cpr_rail cpr_rail_lpi_cx_cfg = {
    .id               = CPR_RAIL_LPI_CX,
    .name             = "LPI_CX",
    .hal              = { .controller = &lpass_cpr3_controller, .thread = &lpi_cx_thread },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


static cpr_rail cpr_rail_lpi_mx_cfg = {
    .id               = CPR_RAIL_LPI_MX,
    .name             = "LPI_MX",
    .hal              = { .controller = NULL, .thread = NULL },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


static cpr_rail cpr_rail_mm_cfg = {
    .id               = CPR_RAIL_MM,
    .name             = "MM",
    .hal              = { .controller = &mmcx_cpr3_controller, .thread = &mm_thread },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


static cpr_rail cpr_rail_mss_cfg = {
    .id               = CPR_RAIL_MSS,
    .name             = "MSS",
    .hal              = { .controller = &cpr3_controller, .thread = &mss_thread },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


static cpr_rail cpr_rail_mx_cfg = {
    .id               = CPR_RAIL_MX,
    .name             = "MX",
    .hal              = { .controller = &mx_cpr3_controller, .thread = &mx_thread },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


static cpr_rail cpr_rail_mxc_cfg = {
    .id               = CPR_RAIL_MXC,
    .name             = "MXC",
    .hal              = { .controller = &mxc_cpr3_controller, .thread = &mxc_thread },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


static cpr_rail cpr_rail_nav_ldo_cfg = {
    .id               = CPR_RAIL_NAV_LDO,
    .name             = "NAV_LDO",
    .hal              = { .controller = NULL, .thread = NULL },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


static cpr_rail cpr_rail_vdda_cfg = {
    .id               = CPR_RAIL_VDDA,
    .name             = "VDDA",
    .hal              = { .controller = NULL, .thread = NULL },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


static cpr_rail cpr_rail_wmss_cx_1_cfg = {
    .id               = CPR_RAIL_WMSS_CX_1,
    .name             = "WMSS_CX_1",
    .hal              = { .controller = NULL, .thread = NULL },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


static cpr_rail cpr_rail_wmss_cx_2_cfg = {
    .id               = CPR_RAIL_WMSS_CX_2,
    .name             = "WMSS_CX_2",
    .hal              = { .controller = NULL, .thread = NULL },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


static cpr_rail cpr_rail_wmss_cx_3_cfg = {
    .id               = CPR_RAIL_WMSS_CX_3,
    .name             = "WMSS_CX_3",
    .hal              = { .controller = NULL, .thread = NULL },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


/*
 * Rail Enablement Config
 */

static cpr_enablement cpr_rail_cx_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_CX,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_SW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 2, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8DA8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8DA4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_gfx_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_GFX,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_HW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 2, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8DA8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8DA4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_lpi_cx_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_LPI_CX,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_SW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 2, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8DA8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8DA4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_lpi_mx_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_LPI_MX,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_OPEN_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 2, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8DA8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8DA4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_mm_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_MM,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_HW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 2, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8DA8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8DA4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_mss_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_MSS,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_HW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 2, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8DA8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8DA4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_mx_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_MX,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_SW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 2, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8DA8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8DA4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_mxc_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_MXC,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_SW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 2, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8DA8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8DA4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_nav_ldo_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_NAV_LDO,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_NONE,
    .fuseMultiplier    = 8000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 2, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8DA8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8DA4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_vdda_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_VDDA,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_OPEN_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 2, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8DA8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8DA4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_wmss_cx_1_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_WMSS_CX_1,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_NONE,
    .fuseMultiplier    = 10000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 2, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8DA8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8DA4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_wmss_cx_2_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_WMSS_CX_2,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_NONE,
    .fuseMultiplier    = 10000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 2, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8DA8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8DA4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_wmss_cx_3_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_WMSS_CX_3,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_NONE,
    .fuseMultiplier    = 10000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 2, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8DA8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8DA4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 0,
};


static cpr_misc_cfg misc_cfg = {
    .cprRev = {.count = 1, .data = (struct raw_fuse_data[]) { {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8DA8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)} } }
};


cpr_settings cpr_settings_fillmore =
{
    .hashValue        = voltage_plan_hash_value,

    .railVVPs         = (cpr_versioned_voltage_plan*[]) { &cx_vvp, &gfx_vvp, &lpi_cx_vvp, &lpi_mx_vvp, &mm_vvp, &mss_vvp, &mx_vvp, &mxc_vvp, &nav_ldo_vvp, &vdda_vvp, &wmss_cx_1_vvp, &wmss_cx_2_vvp, &wmss_cx_3_vvp },
    .rails            = (cpr_rail*[]) { &cpr_rail_cx_cfg, &cpr_rail_gfx_cfg, &cpr_rail_lpi_cx_cfg, &cpr_rail_lpi_mx_cfg, &cpr_rail_mm_cfg, &cpr_rail_mss_cfg, &cpr_rail_mx_cfg, &cpr_rail_mxc_cfg, &cpr_rail_nav_ldo_cfg, &cpr_rail_vdda_cfg, &cpr_rail_wmss_cx_1_cfg, &cpr_rail_wmss_cx_2_cfg, &cpr_rail_wmss_cx_3_cfg },
    .railsCount       = 13,

    .controllers      = (cpr_hal_controller*[]) { &cpr3_controller, &cx_cpr3_controller, &gpu_cpr_controller, &lpass_cpr3_controller, &mmcx_cpr3_controller, &mx_cpr3_controller, &mxc_cpr3_controller },
    .controllersCount = 7,

    .enablements      = (cpr_enablement*[]) { &cpr_rail_cx_enablement_1_0_1_255, &cpr_rail_gfx_enablement_1_0_1_255, &cpr_rail_lpi_cx_enablement_1_0_1_255, &cpr_rail_lpi_mx_enablement_1_0_1_255, &cpr_rail_mm_enablement_1_0_1_255, &cpr_rail_mss_enablement_1_0_1_255, &cpr_rail_mx_enablement_1_0_1_255, &cpr_rail_mxc_enablement_1_0_1_255, &cpr_rail_nav_ldo_enablement_1_0_1_255, &cpr_rail_vdda_enablement_1_0_1_255, &cpr_rail_wmss_cx_1_enablement_1_0_1_255, &cpr_rail_wmss_cx_2_enablement_1_0_1_255, &cpr_rail_wmss_cx_3_enablement_1_0_1_255 },
    .enablementsCount = 13,

    .miscCfg          = &misc_cfg,
};

