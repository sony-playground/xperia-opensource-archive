/*******************************************************************************
 *
 * Copyright (c) 2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 * THIS IS AUTO-GENERATED CPR CONFIG FILE FOR netrani.
 *
 * DateTime: 2023/12/05 05:53:18
 *
 *******************************************************************************/
#include "cpr_data.h"
#include "cpr_image_target_init.h"
#include "cpr_target_hwio.h"


//hash value of Voltage Plan file (extracted all cell values)
static char voltage_plan_hash_value[] = "66AE4F65C6F41734E71618CC788380AD";


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


static cpr_margin_cfg margins_353093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   80000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   -5000, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_12505620831 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  374 },
                                      { .ro =  7, .quotient =  514 },
                                      { .ro =  9, .quotient =  312 },
                                      { .ro = 12, .quotient =  172 },
                                      { .ro = 15, .quotient =  390 } },
};


static cpr_fuse_data  fuses_3538512663 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR0_TARG_VOLT_SVS2) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR0_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_290093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   76000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -20000, .closedLoop =   44000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_11759349565 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  540 },
                                      { .ro =  7, .quotient =  702 },
                                      { .ro =  9, .quotient =  462 },
                                      { .ro = 12, .quotient =  303 },
                                      { .ro = 15, .quotient =  555 } },
};


static cpr_fuse_data  fuses_10210256516 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR0_TARG_VOLT_SVS_5), CPR_FUSE_MAPPING(CALIBRATION14, CPR0_TARG_VOLT_SVS_4_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR0_TARG_VOLT_OFFSET_SVS_4_1), CPR_FUSE_MAPPING(CALIBRATION13, CPR0_TARG_VOLT_OFFSET_SVS_0) } } },
};


static cpr_margin_cfg margins_244093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   66000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -28000, .closedLoop =   35000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_9072533381 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  650 },
                                      { .ro =  7, .quotient =  822 },
                                      { .ro =  9, .quotient =  564 },
                                      { .ro = 12, .quotient =  389 },
                                      { .ro = 15, .quotient =  655 } },
};


static cpr_fuse_data  fuses_1743252866 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION13, CPR0_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_392093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   86000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =    8000, .closedLoop =   71000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_288093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   51000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -24000, .closedLoop =   30000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_10790229927 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  901 },
                                      { .ro =  3, .quotient =  925 },
                                      { .ro =  4, .quotient =  809 },
                                      { .ro =  9, .quotient =  709 },
                                      { .ro = 15, .quotient =  814 } },
};


static cpr_fuse_data  fuses_3536796482 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR0_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION13, CPR0_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_436093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   71000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   12000, .closedLoop =   66000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_margin_cfg margins_294093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   62000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -28000, .closedLoop =   24000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_8523025071 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1003 },
                                      { .ro =  3, .quotient = 1022 },
                                      { .ro =  4, .quotient =  900 },
                                      { .ro =  9, .quotient =  794 },
                                      { .ro = 15, .quotient =  914 } },
};


static cpr_fuse_data  fuses_1501413221 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION13, CPR0_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_margin_cfg margins_502093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   82000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   28000, .closedLoop =   80000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_margin_cfg margins_316093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   49000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -12000, .closedLoop =   40000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_13592913483 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1070 },
                                      { .ro =  3, .quotient = 1086 },
                                      { .ro =  4, .quotient =  960 },
                                      { .ro =  9, .quotient =  850 },
                                      { .ro = 15, .quotient =  981 } },
};


static cpr_fuse_data  fuses_6195197516 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR0_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION13, CPR0_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_fuse_data  fuses_4648330622 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR0_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION30, CPR6_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_margin_cfg margins_284093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   65000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -32000, .closedLoop =   18000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_9050100868 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1217 },
                                      { .ro =  3, .quotient = 1226 },
                                      { .ro =  4, .quotient = 1091 },
                                      { .ro =  9, .quotient =  973 },
                                      { .ro = 15, .quotient = 1126 } },
};


static cpr_fuse_data  fuses_1818666672 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR0_TARG_VOLT_TURL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION13, CPR0_TARG_VOLT_OFFSET_TURL1) } } },
};


static cpr_margin_cfg margins_420093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   73000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =    8000, .closedLoop =   58000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_kv_cfg  kvs_16239393970 =
{
    .count = 7,
    .kvs   = (cpr_kv[]) { { .ro =  2, .kv =  281 },
                                { .ro =  3, .kv =  280 },
                                { .ro =  4, .kv =  276 },
                                { .ro =  7, .kv =  292 },
                                { .ro =  9, .kv =  267 },
                                { .ro = 12, .kv =  241 },
                                { .ro = 15, .kv =  275 } },
};


/*
 * CX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_32641029637 =
{
    .modesCount      = 13,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_16239393970,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_SVS_L2,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L0,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L2,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L0,
                                                    CPR_VOLTAGE_MODE_TURBO_L1,
                                                    CPR_VOLTAGE_MODE_TURBO_L2 },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref = 352000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  352000, .floor =  352000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 556000, .freqDelta =       0, .fuses = &fuses_3538512663, .quotients = &quotients_12505620831, .margins = &margins_353093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  984000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_10210256516, .quotients = &quotients_11759349565, .margins = &margins_290093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  984000, .floor =  552000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_1743252866, .quotients = &quotients_9072533381, .margins = &margins_244093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  984000, .floor =  600000, .freq =       0, .interplEnabled = 46} } },

        // SVS_L2
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_1743252866, .quotients = &quotients_9072533381, .margins = &margins_392093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  984000, .floor =  600000, .freq =       0, .interplEnabled = 46} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_3536796482, .quotients = &quotients_10790229927, .margins = &margins_288093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  984000, .floor =  656000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L0
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_3536796482, .quotients = &quotients_10790229927, .margins = &margins_436093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  984000, .floor =  656000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_1501413221, .quotients = &quotients_8523025071, .margins = &margins_294093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  984000, .floor =  696000, .freq =       0, .interplEnabled = 60} } },

        // NOMINAL_L2
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_1501413221, .quotients = &quotients_8523025071, .margins = &margins_502093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  984000, .floor =  696000, .freq =       0, .interplEnabled = 60} } },

        // TURBO
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_6195197516, .quotients = &quotients_13592913483, .margins = &margins_316093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  984000, .floor =  719000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L0
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_4648330622, .quotients = &quotients_13592913483, .margins = &margins_502093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  984000, .floor =  719000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref = 904000, .freqDelta =       0, .fuses = &fuses_1818666672, .quotients = &quotients_9050100868, .margins = &margins_284093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  984000, .floor =  768000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L2
        {.fref = 904000, .freqDelta =       0, .fuses = &fuses_1818666672, .quotients = &quotients_9050100868, .margins = &margins_420093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  984000, .floor =  768000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_version  ver_ANY_1_0_1_255 = { .foundry = CPR_FOUNDRY_ANY, .min = CPR_CHIPINFO_VERSION(1,0), .max = CPR_CHIPINFO_VERSION(1,255) };


static cpr_margin_cfg margins_258093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   58000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   -4000, .closedLoop =   53000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_12920762542 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  441 },
                                      { .ro =  8, .quotient =  275 },
                                      { .ro =  9, .quotient =  286 },
                                      { .ro = 14, .quotient =  279 },
                                      { .ro = 15, .quotient =  354 } },
};


static cpr_fuse_data  fuses_5373536976 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION27, CPR2_TARG_VOLT_SVS3) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION26, CPR2_TARG_VOLT_OFFSET_SVS3) } } },
};


static cpr_margin_cfg margins_298093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   54000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_10607272682 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  479 },
                                      { .ro =  8, .quotient =  305 },
                                      { .ro =  9, .quotient =  312 },
                                      { .ro = 14, .quotient =  312 },
                                      { .ro = 15, .quotient =  390 } },
};


static cpr_fuse_data  fuses_884424972 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION26, CPR2_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_298094 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   63000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   -4000, .closedLoop =   53000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_13848280991 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  644 },
                                      { .ro =  8, .quotient =  454 },
                                      { .ro =  9, .quotient =  462 },
                                      { .ro = 14, .quotient =  460 },
                                      { .ro = 15, .quotient =  555 } },
};


static cpr_fuse_data  fuses_11417382916 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION27, CPR2_TARG_VOLT_SVS_5_2), CPR_FUSE_MAPPING(CALIBRATION26, CPR2_TARG_VOLT_SVS_1_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION26, CPR2_TARG_VOLT_OFFSET_SVS_4_3), CPR_FUSE_MAPPING(CALIBRATION25, CPR2_TARG_VOLT_OFFSET_SVS_2_0) } } },
};


static cpr_margin_cfg margins_308093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   73000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -12000, .closedLoop =   52000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_8475028992 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  754 },
                                      { .ro =  8, .quotient =  553 },
                                      { .ro =  9, .quotient =  564 },
                                      { .ro = 14, .quotient =  550 },
                                      { .ro = 15, .quotient =  655 } },
};


static cpr_fuse_data  fuses_2339071620 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION25, CPR2_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_310093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   72000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -12000, .closedLoop =   54000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_5647622824 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  816 },
                                      { .ro =  8, .quotient =  612 },
                                      { .ro =  9, .quotient =  625 },
                                      { .ro = 14, .quotient =  609 },
                                      { .ro = 15, .quotient =  721 } },
};


static cpr_fuse_data  fuses_2797241965 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION25, CPR2_TARG_VOLT_OFFSET_SVSL2) } } },
};


static cpr_margin_cfg margins_362093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   -8000, .closedLoop =   46000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_8622199992 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  901 },
                                      { .ro =  8, .quotient =  695 },
                                      { .ro =  9, .quotient =  709 },
                                      { .ro = 14, .quotient =  691 },
                                      { .ro = 15, .quotient =  814 } },
};


static cpr_fuse_data  fuses_4179602449 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION26, CPR2_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR2_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_402093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   74000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   52000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_7362899532 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1003 },
                                      { .ro =  8, .quotient =  780 },
                                      { .ro =  9, .quotient =  794 },
                                      { .ro = 14, .quotient =  783 },
                                      { .ro = 15, .quotient =  914 } },
};


static cpr_fuse_data  fuses_4017886964 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR2_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_margin_cfg margins_412093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   73000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =    4000, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_10041505580 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1070 },
                                      { .ro =  8, .quotient =  836 },
                                      { .ro =  9, .quotient =  850 },
                                      { .ro = 14, .quotient =  844 },
                                      { .ro = 15, .quotient =  981 } },
};


static cpr_fuse_data  fuses_5893569410 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION26, CPR2_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR2_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_margin_cfg margins_388093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   79000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   -8000, .closedLoop =   44000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_6514980031 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1217 },
                                      { .ro =  8, .quotient =  957 },
                                      { .ro =  9, .quotient =  973 },
                                      { .ro = 14, .quotient =  976 },
                                      { .ro = 15, .quotient = 1126 } },
};


static cpr_fuse_data  fuses_6749312716 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION26, CPR2_TARG_VOLT_TURL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR2_TARG_VOLT_OFFSET_TURL1) } } },
};


static cpr_kv_cfg  kvs_11612681903 =
{
    .count = 5,
    .kvs   = (cpr_kv[]) { { .ro =  2, .kv =  281 },
                                { .ro =  8, .kv =  269 },
                                { .ro =  9, .kv =  268 },
                                { .ro = 14, .kv =  268 },
                                { .ro = 15, .kv =  276 } },
};


/*
 * GFX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_23454837570 =
{
    .modesCount      = 9,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_11612681903,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_SVS_L2,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1 },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS_D1
        {.fref = 540000, .freqDelta =       0, .fuses = &fuses_5373536976, .quotients = &quotients_12920762542, .margins = &margins_258093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  984000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 556000, .freqDelta =       0, .fuses = &fuses_884424972, .quotients = &quotients_10607272682, .margins = &margins_298093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  984000, .floor =  516000, .freq =       0, .interplEnabled = 18} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_11417382916, .quotients = &quotients_13848280991, .margins = &margins_298094,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  984000, .floor =  552000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_2339071620, .quotients = &quotients_8475028992, .margins = &margins_308093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  984000, .floor =  600000, .freq =       0, .interplEnabled = 46} } },

        // SVS_L2
        {.fref = 712000, .freqDelta =       0, .fuses = &fuses_2797241965, .quotients = &quotients_5647622824, .margins = &margins_310093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  984000, .floor =  624000, .freq =       0, .interplEnabled = 68} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_4179602449, .quotients = &quotients_8622199992, .margins = &margins_362093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  984000, .floor =  656000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_4017886964, .quotients = &quotients_7362899532, .margins = &margins_402093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  984000, .floor =  696000, .freq =       0, .interplEnabled = 60} } },

        // TURBO
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_5893569410, .quotients = &quotients_10041505580, .margins = &margins_412093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  984000, .floor =  716000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref = 904000, .freqDelta =       0, .fuses = &fuses_6749312716, .quotients = &quotients_6514980031, .margins = &margins_388093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  984000, .floor =  768000, .freq =  780000, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_286093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   53000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   55000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_9160277692 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  275 },
                                      { .ro =  9, .quotient =  286 },
                                      { .ro = 10, .quotient =  150 },
                                      { .ro = 14, .quotient =  279 } },
};


static cpr_fuse_data  fuses_3039171588 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR1_TARG_VOLT_SVS3_5), CPR_FUSE_MAPPING(CALIBRATION22, CPR1_TARG_VOLT_SVS3_4_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION22, CPR1_TARG_VOLT_OFFSET_SVS3) } } },
};


static cpr_margin_cfg margins_332093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   62000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =    8000, .closedLoop =   65000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_7101552781 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  305 },
                                      { .ro =  9, .quotient =  312 },
                                      { .ro = 10, .quotient =  169 },
                                      { .ro = 14, .quotient =  312 } },
};


static cpr_fuse_data  fuses_3136468450 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION22, CPR1_TARG_VOLT_OFFSET_SVS2_4_1), CPR_FUSE_MAPPING(CALIBRATION21, CPR1_TARG_VOLT_OFFSET_SVS2_0) } } },
};


static cpr_margin_cfg margins_302093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_13594457200 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  644 },
                                      { .ro =  3, .quotient =  665 },
                                      { .ro =  8, .quotient =  454 },
                                      { .ro =  9, .quotient =  462 },
                                      { .ro = 14, .quotient =  460 } },
};


static cpr_fuse_data  fuses_3838161838 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION22, CPR1_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION21, CPR1_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_314093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   69000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   -8000, .closedLoop =   57000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_10357983203 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  754 },
                                      { .ro =  3, .quotient =  772 },
                                      { .ro =  8, .quotient =  553 },
                                      { .ro =  9, .quotient =  564 },
                                      { .ro = 14, .quotient =  550 } },
};


static cpr_fuse_data  fuses_1714796285 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION21, CPR1_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_406093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   65000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =    8000, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_8682795327 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  901 },
                                      { .ro =  3, .quotient =  925 },
                                      { .ro =  8, .quotient =  695 },
                                      { .ro =  9, .quotient =  709 },
                                      { .ro = 14, .quotient =  691 } },
};


static cpr_fuse_data  fuses_6200273351 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION22, CPR1_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION21, CPR1_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_428093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   20000, .closedLoop =   69000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_7768896922 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1003 },
                                      { .ro =  3, .quotient = 1022 },
                                      { .ro =  8, .quotient =  780 },
                                      { .ro =  9, .quotient =  794 },
                                      { .ro = 14, .quotient =  783 } },
};


static cpr_fuse_data  fuses_6218030842 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION22, CPR1_TARG_VOLT_NOML1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION21, CPR1_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_kv_cfg  kvs_8757828008 =
{
    .count = 6,
    .kvs   = (cpr_kv[]) { { .ro =  2, .kv =  291 },
                                { .ro =  3, .kv =  291 },
                                { .ro =  8, .kv =  273 },
                                { .ro =  9, .kv =  271 },
                                { .ro = 10, .kv =  236 },
                                { .ro = 14, .kv =  273 } },
};


/*
 * MSS Voltage Plan
 */
static cpr_voltage_plan voltage_plan_17238881940 =
{
    .modesCount      = 6,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_8757828008,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1 },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS_D1
        {.fref = 540000, .freqDelta =       0, .fuses = &fuses_3039171588, .quotients = &quotients_9160277692, .margins = &margins_286093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  896000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 556000, .freqDelta =       0, .fuses = &fuses_3136468450, .quotients = &quotients_7101552781, .margins = &margins_332093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  896000, .floor =  516000, .freq =       0, .interplEnabled = 18} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_3838161838, .quotients = &quotients_13594457200, .margins = &margins_302093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  896000, .floor =  552000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_1714796285, .quotients = &quotients_10357983203, .margins = &margins_314093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  896000, .floor =  600000, .freq =       0, .interplEnabled = 46} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_6200273351, .quotients = &quotients_8682795327, .margins = &margins_406093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  896000, .floor =  656000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_6218030842, .quotients = &quotients_7768896922, .margins = &margins_428093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  896000, .floor =  696000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_57 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 } }
};


static cpr_margin_cfg margins_180057 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   60000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_12070062533 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  0, .quotient =  755 },
                                      { .ro =  2, .quotient =  456 },
                                      { .ro =  4, .quotient =  526 },
                                      { .ro =  5, .quotient =  666 },
                                      { .ro =  6, .quotient =  588 },
                                      { .ro =  7, .quotient =  768 } },
};


static cpr_fuse_data  fuses_4059296135 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION29, CPR4_TARG_VOLT_SVSL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION28, CPR4_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_182057 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   61000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_456093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   61000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   67000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_13855633628 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  0, .quotient =  893 },
                                      { .ro =  2, .quotient =  550 },
                                      { .ro =  4, .quotient =  630 },
                                      { .ro =  5, .quotient =  793 },
                                      { .ro =  6, .quotient =  711 },
                                      { .ro =  7, .quotient =  920 } },
};


static cpr_fuse_data  fuses_7065788242 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION29, CPR4_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION28, CPR4_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_448093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   64000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   60000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_11589791812 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  0, .quotient = 1050 },
                                      { .ro =  2, .quotient =  656 },
                                      { .ro =  4, .quotient =  750 },
                                      { .ro =  5, .quotient =  915 },
                                      { .ro =  6, .quotient =  851 },
                                      { .ro =  7, .quotient = 1065 } },
};


static cpr_fuse_data  fuses_4232528123 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION29, CPR4_TARG_VOLT_NOML1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION28, CPR4_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_margin_cfg margins_514093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   77000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   80000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_15428340219 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  0, .quotient = 1082 },
                                      { .ro =  2, .quotient =  656 },
                                      { .ro =  4, .quotient =  751 },
                                      { .ro =  5, .quotient =  942 },
                                      { .ro =  6, .quotient =  850 },
                                      { .ro =  7, .quotient = 1091 } },
};


static cpr_fuse_data  fuses_4446229344 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION28, CPR4_TARG_VOLT_TURL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION28, CPR4_TARG_VOLT_OFFSET_TURL1) } } },
};


static cpr_margin_cfg margins_424093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   57000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   55000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_17879112057 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  0, .quotient = 1151 },
                                      { .ro =  2, .quotient =  725 },
                                      { .ro =  4, .quotient =  829 },
                                      { .ro =  5, .quotient =  995 },
                                      { .ro =  6, .quotient =  943 },
                                      { .ro =  7, .quotient = 1160 } },
};


static cpr_kv_cfg  kvs_10668712725 =
{
    .count = 6,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =  392 },
                                { .ro =  2, .kv =  256 },
                                { .ro =  4, .kv =  298 },
                                { .ro =  5, .kv =  305 },
                                { .ro =  6, .kv =  336 },
                                { .ro =  7, .kv =  345 } },
};


/*
 * MX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_31379834113 =
{
    .modesCount      = 14,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_10668712725,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_SVS_L2,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L0,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L2,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L0,
                                                    CPR_VOLTAGE_MODE_TURBO_L1,
                                                    CPR_VOLTAGE_MODE_TURBO_L2 },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref = 524000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  568000, .floor =  524000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS_D1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_57,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_57,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_57,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_4059296135, .quotients = &quotients_12070062533, .margins = &margins_180057,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L2
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_4059296135, .quotients = &quotients_12070062533, .margins = &margins_182057,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_7065788242, .quotients = &quotients_13855633628, .margins = &margins_456093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L0
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_7065788242, .quotients = &quotients_13855633628, .margins = &margins_456093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_4232528123, .quotients = &quotients_11589791812, .margins = &margins_448093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L2
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_4232528123, .quotients = &quotients_11589791812, .margins = &margins_448093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_4446229344, .quotients = &quotients_15428340219, .margins = &margins_514093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L0
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_4446229344, .quotients = &quotients_15428340219, .margins = &margins_514093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_4446229344, .quotients = &quotients_17879112057, .margins = &margins_424093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L2
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_4446229344, .quotients = &quotients_17879112057, .margins = &margins_424093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  800000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_59943 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 } }
};


static cpr_margin_cfg margins_9993 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -20000, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -30000, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 } }
};


static cpr_fuse_data  fuses_3657820087 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION30, CPR5_TARG_VOLT_SVSL1_5_2), CPR_FUSE_MAPPING(CALIBRATION29, CPR5_TARG_VOLT_SVSL1_1_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_fuse_data  fuses_1064837929 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION29, CPR5_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_fuse_data  fuses_897110386 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION29, CPR5_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


/*
 * LPI_MX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_14330894631 =
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
        {.fref = 504000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS_D1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_59943,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_59943,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_59943,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_3657820087, .quotients = NULL, .margins = &margins_9993,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_1064837929, .quotients = NULL, .margins = &margins_9993,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_897110386, .quotients = NULL, .margins = &margins_9993,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  800000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_268093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   53000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   46000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_13823818759 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  441 },
                                      { .ro =  3, .quotient =  466 },
                                      { .ro =  4, .quotient =  345 },
                                      { .ro =  8, .quotient =  275 },
                                      { .ro =  9, .quotient =  286 } },
};


static cpr_fuse_data  fuses_2663570999 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION32, CPR6_TARG_VOLT_SVS3) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION31, CPR6_TARG_VOLT_OFFSET_SVS3) } } },
};


static cpr_margin_cfg margins_272093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   53000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_13460262604 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  479 },
                                      { .ro =  3, .quotient =  503 },
                                      { .ro =  4, .quotient =  374 },
                                      { .ro =  8, .quotient =  305 },
                                      { .ro =  9, .quotient =  312 } },
};


static cpr_fuse_data  fuses_4239643765 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION31, CPR6_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_318093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   72000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   52000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_15800972104 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  644 },
                                      { .ro =  3, .quotient =  665 },
                                      { .ro =  4, .quotient =  540 },
                                      { .ro =  8, .quotient =  454 },
                                      { .ro =  9, .quotient =  462 },
                                      { .ro = 15, .quotient =  555 } },
};


static cpr_fuse_data  fuses_6487005908 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION32, CPR6_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION31, CPR6_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_348093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   74000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   65000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_13588903944 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  754 },
                                      { .ro =  3, .quotient =  772 },
                                      { .ro =  4, .quotient =  650 },
                                      { .ro =  8, .quotient =  553 },
                                      { .ro =  9, .quotient =  564 },
                                      { .ro = 15, .quotient =  655 } },
};


static cpr_fuse_data  fuses_5892343331 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION31, CPR6_TARG_VOLT_OFFSET_SVSL1_4_2), CPR_FUSE_MAPPING(CALIBRATION30, CPR6_TARG_VOLT_OFFSET_SVSL1_1_0) } } },
};


static cpr_margin_cfg margins_392094 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   67000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   54000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_12602881936 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  901 },
                                      { .ro =  3, .quotient =  925 },
                                      { .ro =  4, .quotient =  809 },
                                      { .ro =  8, .quotient =  695 },
                                      { .ro =  9, .quotient =  709 },
                                      { .ro = 15, .quotient =  814 } },
};


static cpr_fuse_data  fuses_5137948433 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION32, CPR6_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION30, CPR6_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_384093 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   58000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_13684290078 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1070 },
                                      { .ro =  3, .quotient = 1086 },
                                      { .ro =  4, .quotient =  960 },
                                      { .ro =  8, .quotient =  836 },
                                      { .ro =  9, .quotient =  850 },
                                      { .ro = 15, .quotient =  981 } },
};


static cpr_fuse_data  fuses_1227181443 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION32, CPR6_TARG_VOLT_TUR_5_2), CPR_FUSE_MAPPING(CALIBRATION31, CPR6_TARG_VOLT_TUR_1_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_kv_cfg  kvs_14275367714 =
{
    .count = 6,
    .kvs   = (cpr_kv[]) { { .ro =  2, .kv =  289 },
                                { .ro =  3, .kv =  290 },
                                { .ro =  4, .kv =  279 },
                                { .ro =  8, .kv =  271 },
                                { .ro =  9, .kv =  270 },
                                { .ro = 15, .kv =  280 } },
};


/*
 * LPI_CX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_15762355325 =
{
    .modesCount      = 7,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_14275367714,
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
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_2663570999, .quotients = &quotients_13823818759, .margins = &margins_268093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  520000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 552000, .freqDelta =       0, .fuses = &fuses_4239643765, .quotients = &quotients_13460262604, .margins = &margins_272093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  520000, .freq =       0, .interplEnabled = 18} } },

        // SVS
        {.fref = 624000, .freqDelta =       0, .fuses = &fuses_6487005908, .quotients = &quotients_15800972104, .margins = &margins_318093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  552000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 680000, .freqDelta =       0, .fuses = &fuses_5892343331, .quotients = &quotients_13588903944, .margins = &margins_348093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  600000, .freq =       0, .interplEnabled = 46} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_5137948433, .quotients = &quotients_12602881936, .margins = &margins_392094,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  656000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_1227181443, .quotients = &quotients_13684290078, .margins = &margins_384093,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  720000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_fuse_data  fuses_3099748859 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION33, CPR9_TARG_VOLT_SVS_5_4), CPR_FUSE_MAPPING(CALIBRATION32, CPR9_TARG_VOLT_SVS_3_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_fuse_data  fuses_2395079338 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION32, CPR9_TARG_VOLT_SVSL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


/*
 * WLAN Voltage Plan
 */
static cpr_voltage_plan voltage_plan_6406790425 =
{
    .modesCount      = 2,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1 },
    .modes           = (struct cpr_voltage_data[]) {
        // SVS
        {.fref = 624000, .freqDelta =       0, .fuses = &fuses_3099748859, .quotients = NULL, .margins = &margins_57,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  552000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 680000, .freqDelta =       0, .fuses = &fuses_2395079338, .quotients = NULL, .margins = &margins_57,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  600000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_29943 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 3,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -30000, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 } }
};


/*
 * WMSS_CX_1 Voltage Plan
 */
static cpr_voltage_plan voltage_plan_3800902664 =
{
    .modesCount      = 3,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_NOMINAL },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS
        {.fref = 592000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_57,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  648000, .floor =  504000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 672000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_57,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  720000, .floor =  592000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_29943,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  864000, .floor =  712000, .freq =       0, .interplEnabled = 0} } }},
};


/*
 * WMSS_CX_2 Voltage Plan
 */
static cpr_voltage_plan voltage_plan_7570848883 =
{
    .modesCount      = 3,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_NOMINAL },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS
        {.fref = 588000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_57,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  588000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 668000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_57,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  728000, .floor =  596000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 744000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_57,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  800000, .floor =  652000, .freq =       0, .interplEnabled = 0} } }},
};


/*
 * WMSS_CX_3 Voltage Plan
 */
static cpr_voltage_plan voltage_plan_9017840005 =
{
    .modesCount      = 3,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_NOMINAL },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS
        {.fref = 588000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_57,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  504000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 668000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_57,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  724000, .floor =  596000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_57,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  864000, .floor =  712000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_fuse_data  fuses_1224745928 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION27, CPR3_TARG_VOLT_SVS2) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_fuse_data  fuses_2483969481 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION27, CPR3_TARG_VOLT_TURL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


/*
 * VDDA Voltage Plan
 */
static cpr_voltage_plan voltage_plan_23139760074 =
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
        {.fref = 700000, .freqDelta =       0, .fuses = &fuses_1224745928, .quotients = NULL, .margins = &margins_57,
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
        {.fref = 892000, .freqDelta =       0, .fuses = &fuses_2483969481, .quotients = NULL, .margins = &margins_57,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  952000, .floor =  892000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =       0, .floor =       0, .freq =       0, .interplEnabled = 0} } }},
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
    .sensorID             = 15,
    .kv                   = 93,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 2, .data = (struct raw_fuse_data[]) {
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D34 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1) | (1<<0)},
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D30 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 30, (1<<31) | (1<<30)} } }
};


static cpr_aging_cfg  aging_cfg_gfx =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO_L1,
    .sensorID             = 0,
    .kv                   = 94,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D5C & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 1, (1<<8) | (1<<7) | (1<<6) | (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1)} } }
};


static cpr_aging_cfg  aging_cfg_mss =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_NOMINAL_L1,
    .sensorID             = 9,
    .kv                   = 103,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D54 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 3, (1<<10) | (1<<9) | (1<<8) | (1<<7) | (1<<6) | (1<<5) | (1<<4) | (1<<3)} } }
};


static cpr_aging_cfg  aging_cfg_mx =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO,
    .sensorID             = 25,
    .kv                   = 106,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8E04 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 8, (1<<15) | (1<<14) | (1<<13) | (1<<12) | (1<<11) | (1<<10) | (1<<9) | (1<<8)} } }
};


static cpr_aging_cfg  aging_cfg_lpi_cx =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO,
    .sensorID             = 5,
    .kv                   = 99,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D78 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 4, (1<<11) | (1<<10) | (1<<9) | (1<<8) | (1<<7) | (1<<6) | (1<<5) | (1<<4)} } }
};


/*
 * Versioned Voltage Plans
 */

static cpr_versioned_voltage_plan cx_vvp = {
    .rail     = CPR_RAIL_CX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_32641029637 },
     },
    .count    = 1,
    .agingCfg = &aging_cfg_cx
};


static cpr_versioned_voltage_plan gfx_vvp = {
    .rail     = CPR_RAIL_GFX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_23454837570 },
     },
    .count    = 1,
    .agingCfg = &aging_cfg_gfx
};


static cpr_versioned_voltage_plan mss_vvp = {
    .rail     = CPR_RAIL_MSS,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_17238881940 },
     },
    .count    = 1,
    .agingCfg = &aging_cfg_mss
};


static cpr_versioned_voltage_plan mx_vvp = {
    .rail     = CPR_RAIL_MX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_31379834113 },
     },
    .count    = 1,
    .agingCfg = &aging_cfg_mx
};


static cpr_versioned_voltage_plan lpi_mx_vvp = {
    .rail     = CPR_RAIL_LPI_MX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_14330894631 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan lpi_cx_vvp = {
    .rail     = CPR_RAIL_LPI_CX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_15762355325 },
     },
    .count    = 1,
    .agingCfg = &aging_cfg_lpi_cx
};


static cpr_versioned_voltage_plan wlan_vvp = {
    .rail     = CPR_RAIL_WLAN,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_6406790425 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan wmss_cx_1_vvp = {
    .rail     = CPR_RAIL_WMSS_CX_1,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_3800902664 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan wmss_cx_2_vvp = {
    .rail     = CPR_RAIL_WMSS_CX_2,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_7570848883 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan wmss_cx_3_vvp = {
    .rail     = CPR_RAIL_WMSS_CX_3,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_9017840005 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan vdda_vvp = {
    .rail     = CPR_RAIL_VDDA,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_23139760074 },
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
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24 },
    .sensorsCount = 25,
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
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56 },
    .sensorsCount = 57,
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
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9 },
    .sensorsCount = 10,
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


static cpr_hal_thread_cfg mx_thread_cfg = {
    .upThresh     = 2,
    .dnThresh     = 2,
    .consecUp     = 0,
    .consecDn     = 0,
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,32,33,34,35,36,37,38,39,40,41,42,43,46,47,48 },
    .sensorsCount = 43,
};


static cpr_hal_thread  mx_thread = {
    .id   = 0,
    .cfg  = &mx_thread_cfg,
};


/*
 * CPR Controller Config
 */

static cpr_hal_controller_cfg cpr3_controller_cfg = {
    .stepQuotMin         = 8,
    .stepQuotMax         = 13,
    .sensorsTotal        = 25,
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
    .sensorsTotal        = 57,
    .bypassSensors       = NULL,
    .bypassSensorsCount  = 0,
    .disableSensors      = (uint8[]){ 0,1,5,6,12,13,14,27,28,31,43 },
    .disableSensorsCount = 11,
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
    .sensorsTotal        = 10,
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


static cpr_hal_controller_cfg mx_cpr3_controller_cfg = {
    .stepQuotMin         = 7,
    .stepQuotMax         = 13,
    .sensorsTotal        = 49,
    .bypassSensors       = (uint8[]){ 28,29,30,31,44,45 },
    .bypassSensorsCount  = 6,
    .disableSensors      = NULL,
    .disableSensorsCount = 0,
    .refClk              = NULL,
    .ahbClk              = NULL,
};


static cpr_hal_controller  mx_cpr3_controller = {
    .base                = 0x62c000,
    .type                = CPR_CONTROLLER_TYPE_HW_CL_ONLY,
    .cfg                 = &mx_cpr3_controller_cfg,
    .threads             = (cpr_hal_thread*[]){ &mx_thread },
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


static cpr_rail cpr_rail_wlan_cfg = {
    .id               = CPR_RAIL_WLAN,
    .name             = "WLAN",
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
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D30 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_gfx_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_GFX,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_HW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D30 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_lpi_cx_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_LPI_CX,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_SW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D30 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_lpi_mx_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_LPI_MX,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_OPEN_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D30 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_mss_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_MSS,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_HW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D30 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_mx_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_MX,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_SW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D30 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_nav_ldo_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_NAV_LDO,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_NONE,
    .fuseMultiplier    = 8000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D30 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_vdda_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_VDDA,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_OPEN_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D30 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_wlan_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_WLAN,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_OPEN_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D30 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_wmss_cx_1_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_WMSS_CX_1,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_NONE,
    .fuseMultiplier    = 10000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D30 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_wmss_cx_2_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_WMSS_CX_2,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_NONE,
    .fuseMultiplier    = 10000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D30 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_wmss_cx_3_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_WMSS_CX_3,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_NONE,
    .fuseMultiplier    = 10000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D30 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 0,
};


static cpr_misc_cfg misc_cfg = {
    .cprRev = {.count = 1, .data = (struct raw_fuse_data[]) { {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D30 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<26) | (1<<25) | (1<<24)} } }
};


cpr_settings cpr_settings_netrani =
{
    .hashValue        = voltage_plan_hash_value,

    .railVVPs         = (cpr_versioned_voltage_plan*[]) { &cx_vvp, &gfx_vvp, &lpi_cx_vvp, &lpi_mx_vvp, &mss_vvp, &mx_vvp, &nav_ldo_vvp, &vdda_vvp, &wlan_vvp, &wmss_cx_1_vvp, &wmss_cx_2_vvp, &wmss_cx_3_vvp },
    .rails            = (cpr_rail*[]) { &cpr_rail_cx_cfg, &cpr_rail_gfx_cfg, &cpr_rail_lpi_cx_cfg, &cpr_rail_lpi_mx_cfg, &cpr_rail_mss_cfg, &cpr_rail_mx_cfg, &cpr_rail_nav_ldo_cfg, &cpr_rail_vdda_cfg, &cpr_rail_wlan_cfg, &cpr_rail_wmss_cx_1_cfg, &cpr_rail_wmss_cx_2_cfg, &cpr_rail_wmss_cx_3_cfg },
    .railsCount       = 12,

    .controllers      = (cpr_hal_controller*[]) { &cpr3_controller, &cx_cpr3_controller, &gpu_cpr_controller, &lpass_cpr3_controller, &mx_cpr3_controller },
    .controllersCount = 5,

    .enablements      = (cpr_enablement*[]) { &cpr_rail_cx_enablement_1_0_1_255, &cpr_rail_gfx_enablement_1_0_1_255, &cpr_rail_lpi_cx_enablement_1_0_1_255, &cpr_rail_lpi_mx_enablement_1_0_1_255, &cpr_rail_mss_enablement_1_0_1_255, &cpr_rail_mx_enablement_1_0_1_255, &cpr_rail_nav_ldo_enablement_1_0_1_255, &cpr_rail_vdda_enablement_1_0_1_255, &cpr_rail_wlan_enablement_1_0_1_255, &cpr_rail_wmss_cx_1_enablement_1_0_1_255, &cpr_rail_wmss_cx_2_enablement_1_0_1_255, &cpr_rail_wmss_cx_3_enablement_1_0_1_255 },
    .enablementsCount = 12,

    .miscCfg          = &misc_cfg,
};

