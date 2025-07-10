/*******************************************************************************
 *
 * Copyright (c) 2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 * THIS IS AUTO-GENERATED CPR CONFIG FILE FOR palima.
 *
 * DateTime: 2023/12/05 06:03:48
 *
 *******************************************************************************/
#include "cpr_data.h"
#include "cpr_image_target_init.h"
#include "cpr_target_hwio.h"


//hash value of Voltage Plan file (extracted all cell values)
static char voltage_plan_hash_value[] = "B50926DA5098BD597C04D6B647FE9486";


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


static cpr_margin_cfg margins_1158333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   24000, .closedLoop =   75000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   24000, .closedLoop =   75000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   24000, .closedLoop =   75000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =   24000, .closedLoop =   75000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =    8000, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =    8000, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_10520941446 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  5, .quotient =  272 },
                                      { .ro =  8, .quotient =  182 },
                                      { .ro = 14, .quotient =  286 },
                                      { .ro = 15, .quotient =  183 } },
};


static cpr_fuse_data  fuses_6348353758 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW7_LSB, CPR0_TARG_VOLT_SVS2) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW7_MSB, CPR0_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_1250333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   24000, .closedLoop =   85000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   24000, .closedLoop =   85000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   24000, .closedLoop =   85000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =   24000, .closedLoop =   85000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =    4000, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =    4000, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_4676959054 =
{
    .count = 2,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  414 },
                                      { .ro = 15, .quotient =  301 } },
};


static cpr_fuse_data  fuses_5691737190 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW7_LSB, CPR0_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW7_MSB, CPR0_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_1250334 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   24000, .closedLoop =   87000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   24000, .closedLoop =   87000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   24000, .closedLoop =   87000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =   24000, .closedLoop =   87000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =       0, .closedLoop =   62000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =       0, .closedLoop =   62000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_831233196 =
{
    .count = 2,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  543 },
                                      { .ro = 15, .quotient =  415 } },
};


static cpr_fuse_data  fuses_1551373501 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW7_MSB, CPR0_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_1266333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =   70000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   70000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   70000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =       0, .closedLoop =   70000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =       0, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =       0, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_3427754079 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  803 },
                                      { .ro =  6, .quotient =  659 },
                                      { .ro =  9, .quotient =  511 } },
};


static cpr_fuse_data  fuses_7534396309 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW7_LSB, CPR0_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW7_MSB, CPR0_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_quotient_cfg  quotients_2447557633 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  997 },
                                      { .ro =  6, .quotient =  875 },
                                      { .ro =  9, .quotient =  711 } },
};


static cpr_fuse_data  fuses_5442359623 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW7_MSB, CPR0_TARG_VOLT_OFFSET_TUR_4_3), CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW7_LSB, CPR0_TARG_VOLT_OFFSET_TUR_2_0) } } },
};


static cpr_margin_cfg margins_1458333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   16000, .closedLoop =   84000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   16000, .closedLoop =   84000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   16000, .closedLoop =   84000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =   16000, .closedLoop =   84000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =       0, .closedLoop =   68000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =       0, .closedLoop =   68000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_5173277213 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient = 1146 },
                                      { .ro =  6, .quotient = 1027 },
                                      { .ro =  9, .quotient =  860 } },
};


static cpr_fuse_data  fuses_4048016517 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW7_LSB, CPR0_TARG_VOLT_SUT) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW7_LSB, CPR0_TARG_VOLT_OFFSET_SUT) } } },
};


static cpr_margin_cfg margins_1338333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =    4000, .closedLoop =   72000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =    4000, .closedLoop =   72000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =    4000, .closedLoop =   72000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =    4000, .closedLoop =   72000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =    4000, .closedLoop =   72000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =    4000, .closedLoop =   72000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_fuse_data  fuses_6329452902 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW7_LSB, CPR0_TARG_VOLT_SUT) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW36_MSB, CPR0_TARG_VOLT_OFFSET_TURL0) } } },
};


static cpr_margin_cfg margins_1842333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   32000, .closedLoop =  100000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   32000, .closedLoop =  100000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   32000, .closedLoop =  100000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =   32000, .closedLoop =  100000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   32000, .closedLoop =  100000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =   32000, .closedLoop =  100000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_fuse_data  fuses_3817711595 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW7_LSB, CPR0_TARG_VOLT_SUT) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW36_MSB, CPR0_TARG_VOLT_OFFSET_TURL2) } } },
};


static cpr_kv_cfg  kvs_32180226977 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =  334 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =  306 },
                                { .ro =  6, .kv =  310 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =  276 },
                                { .ro =  9, .kv =  282 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =    0 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  320 },
                                { .ro = 15, .kv =  290 } },
};


/*
 * CX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_18426875048 =
{
    .modesCount      = 9,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_32180226977,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1,
                                                    CPR_VOLTAGE_MODE_TURBO_L2,
                                                    CPR_VOLTAGE_MODE_TURBO_L3 },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref = 352000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  352000, .floor =  352000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_6348353758, .quotients = &quotients_10520941446, .margins = &margins_1158333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_5691737190, .quotients = &quotients_4676959054, .margins = &margins_1250333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_1551373501, .quotients = &quotients_831233196, .margins = &margins_1250334,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_7534396309, .quotients = &quotients_3427754079, .margins = &margins_1266333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  776000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_5442359623, .quotients = &quotients_2447557633, .margins = &margins_1266333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  716000, .freq =       0, .interplEnabled = 57} } },

        // TURBO_L1
        {.fref = 856000, .freqDelta =       0, .fuses = &fuses_4048016517, .quotients = &quotients_5173277213, .margins = &margins_1458333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  952000, .floor =  760000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L2
        {.fref = 856000, .freqDelta =       0, .fuses = &fuses_6329452902, .quotients = &quotients_5173277213, .margins = &margins_1338333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  952000, .floor =  760000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L3
        {.fref = 856000, .freqDelta =       0, .fuses = &fuses_3817711595, .quotients = &quotients_5173277213, .margins = &margins_1842333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  952000, .floor =  760000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_version  ver_ANY_1_0_1_255 = { .foundry = CPR_FOUNDRY_ANY, .min = CPR_CHIPINFO_VERSION(1,0), .max = CPR_CHIPINFO_VERSION(1,255) };


static cpr_margin_cfg margins_1200333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   32000, .closedLoop =   74000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   32000, .closedLoop =   74000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   32000, .closedLoop =   74000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =   32000, .closedLoop =   74000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   32000, .closedLoop =   74000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =   32000, .closedLoop =   74000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_3497487807 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  230 } },
};


static cpr_fuse_data  fuses_12127991025 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW9_MSB, CPR2_TARG_VOLT_SVS3_5_2), CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW9_LSB, CPR2_TARG_VOLT_SVS3_1_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW22_LSB, CPR2_TARG_VOLT_OFFSET_LSVS_D2_4_3), CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW21_MSB, CPR2_TARG_VOLT_OFFSET_LSVS_D2_2_0) } } },
};


static cpr_fuse_data  fuses_9060723049 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW9_MSB, CPR2_TARG_VOLT_SVS3_5_2), CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW9_LSB, CPR2_TARG_VOLT_SVS3_1_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW10_LSB, CPR2_TARG_VOLT_OFFSET_SVS3) } } },
};


static cpr_margin_cfg margins_1272333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   24000, .closedLoop =   84000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   24000, .closedLoop =   84000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   24000, .closedLoop =   84000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =   24000, .closedLoop =   84000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   24000, .closedLoop =   84000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =   24000, .closedLoop =   84000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_2297840139 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  258 } },
};


static cpr_fuse_data  fuses_1148903009 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW21_MSB, CPR2_TARG_VOLT_OFFSET_LSVS_D0) } } },
};


static cpr_margin_cfg margins_1224333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   16000, .closedLoop =   84000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   16000, .closedLoop =   84000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   16000, .closedLoop =   84000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =   16000, .closedLoop =   84000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   16000, .closedLoop =   84000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =   16000, .closedLoop =   84000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_3672117569 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  286 } },
};


static cpr_fuse_data  fuses_2079617938 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW10_LSB, CPR2_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_1272334 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   16000, .closedLoop =   88000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   16000, .closedLoop =   88000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   16000, .closedLoop =   88000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =   16000, .closedLoop =   88000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   16000, .closedLoop =   88000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =   16000, .closedLoop =   88000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_2280628238 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  350 } },
};


static cpr_fuse_data  fuses_4171226186 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW9_LSB, CPR2_TARG_VOLT_SVSL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW36_MSB, CPR2_TARG_VOLT_OFFSET_LSVSL1) } } },
};


static cpr_margin_cfg margins_1158334 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   16000, .closedLoop =   71000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   16000, .closedLoop =   71000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   16000, .closedLoop =   71000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =   16000, .closedLoop =   71000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   16000, .closedLoop =   71000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =   16000, .closedLoop =   71000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_3785471894 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  414 } },
};


static cpr_fuse_data  fuses_1648668983 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW10_LSB, CPR2_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_990333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   16000, .closedLoop =   57000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   16000, .closedLoop =   57000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   16000, .closedLoop =   57000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =   16000, .closedLoop =   57000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   16000, .closedLoop =   57000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =   16000, .closedLoop =   57000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_3377097901 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  479 } },
};


static cpr_fuse_data  fuses_3878784290 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW9_LSB, CPR2_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW36_MSB, CPR2_TARG_VOLT_OFFSET_SVSL0) } } },
};


static cpr_margin_cfg margins_1074333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   16000, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   16000, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   16000, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =   16000, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   16000, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =   16000, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_1953991889 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  542 } },
};


static cpr_fuse_data  fuses_3824969281 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW10_LSB, CPR2_TARG_VOLT_OFFSET_SVSL1_4_3), CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW9_MSB, CPR2_TARG_VOLT_OFFSET_SVSL1_2_0) } } },
};


static cpr_margin_cfg margins_1182333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   16000, .closedLoop =   73000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   16000, .closedLoop =   73000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   16000, .closedLoop =   73000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =   16000, .closedLoop =   73000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   16000, .closedLoop =   73000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =   16000, .closedLoop =   73000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_683300777 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  594 } },
};


static cpr_fuse_data  fuses_5808342264 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW9_LSB, CPR2_TARG_VOLT_NOML1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW9_MSB, CPR2_TARG_VOLT_OFFSET_SVSL2) } } },
};


static cpr_margin_cfg margins_1410333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =    8000, .closedLoop =   76000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =    8000, .closedLoop =   76000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =    8000, .closedLoop =   76000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =    8000, .closedLoop =   76000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =    8000, .closedLoop =   76000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =    8000, .closedLoop =   76000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_3897927467 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  645 } },
};


static cpr_fuse_data  fuses_2155423499 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW9_MSB, CPR2_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_1230333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   -8000, .closedLoop =   69000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   -8000, .closedLoop =   69000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   -8000, .closedLoop =   69000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =   -8000, .closedLoop =   69000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   -8000, .closedLoop =   69000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =   -8000, .closedLoop =   69000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_2896600840 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  764 } },
};


static cpr_fuse_data  fuses_4161797221 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW9_MSB, CPR2_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_margin_cfg margins_1062333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =  -16000, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -16000, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -16000, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =  -16000, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =  -16000, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =  -16000, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_1240774937 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  866 } },
};


static cpr_fuse_data  fuses_1521952445 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW9_MSB, CPR2_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_margin_cfg margins_510333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =  -56000, .closedLoop =   33000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -56000, .closedLoop =   33000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -56000, .closedLoop =   33000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =  -56000, .closedLoop =   33000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =  -56000, .closedLoop =   33000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =  -56000, .closedLoop =   33000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_175100294 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient = 1037 } },
};


static cpr_fuse_data  fuses_6786394831 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW9_LSB, CPR2_TARG_VOLT_SUT) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW9_MSB, CPR2_TARG_VOLT_OFFSET_SUT) } } },
};


static cpr_kv_cfg  kvs_35634596411 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =  330 },
                                { .ro =  3, .kv =  331 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =  310 },
                                { .ro =  6, .kv =    0 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =    0 },
                                { .ro =  9, .kv =  291 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =  385 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  324 },
                                { .ro = 15, .kv =    0 } },
};


/*
 * GFX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_24034179149 =
{
    .modesCount      = 13,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_35634596411,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_MIN_SVS,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_L1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_L2,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L0,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_SVS_L2,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1 },
    .modes           = (struct cpr_voltage_data[]) {
        // MIN_SVS
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_12127991025, .quotients = &quotients_3497487807, .margins = &margins_1200333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS_D1
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_9060723049, .quotients = &quotients_3497487807, .margins = &margins_1200333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_1148903009, .quotients = &quotients_2297840139, .margins = &margins_1272333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 20} } },

        // LOW_SVS_L1
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_2079617938, .quotients = &quotients_3672117569, .margins = &margins_1224333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 50} } },

        // LOW_SVS_L2
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_4171226186, .quotients = &quotients_2280628238, .margins = &margins_1272334,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_1648668983, .quotients = &quotients_3785471894, .margins = &margins_1158334,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 50} } },

        // SVS_L0
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_3878784290, .quotients = &quotients_3377097901, .margins = &margins_990333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_3824969281, .quotients = &quotients_1953991889, .margins = &margins_1074333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // SVS_L2
        {.fref = 704000, .freqDelta =       0, .fuses = &fuses_5808342264, .quotients = &quotients_683300777, .margins = &margins_1182333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  768000, .floor =  640000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_2155423499, .quotients = &quotients_3897927467, .margins = &margins_1410333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  776000, .floor =  660000, .freq =       0, .interplEnabled = 15} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_4161797221, .quotients = &quotients_2896600840, .margins = &margins_1230333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  688000, .freq =       0, .interplEnabled = 41} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_1521952445, .quotients = &quotients_1240774937, .margins = &margins_1062333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  716000, .freq =       0, .interplEnabled = 63} } },

        // TURBO_L1
        {.fref = 856000, .freqDelta =       0, .fuses = &fuses_6786394831, .quotients = &quotients_175100294, .margins = &margins_510333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  760000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_quotient_cfg  quotients_14080841326 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  5, .quotient =  219 },
                                      { .ro =  6, .quotient =  237 },
                                      { .ro =  8, .quotient =  139 },
                                      { .ro = 12, .quotient =  492 },
                                      { .ro = 14, .quotient =  230 } },
};


static cpr_fuse_data  fuses_6242647411 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW8_LSB, CPR1_TARG_VOLT_SVS3) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW8_MSB, CPR1_TARG_VOLT_OFFSET_SVS3) } } },
};


static cpr_margin_cfg margins_1134333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   16000, .closedLoop =   69000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   16000, .closedLoop =   69000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   16000, .closedLoop =   69000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =   16000, .closedLoop =   69000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   16000, .closedLoop =   69000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =   16000, .closedLoop =   69000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_16689446886 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  5, .quotient =  272 },
                                      { .ro =  6, .quotient =  298 },
                                      { .ro =  8, .quotient =  182 },
                                      { .ro = 12, .quotient =  583 },
                                      { .ro = 14, .quotient =  286 } },
};


static cpr_fuse_data  fuses_2808018135 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW8_MSB, CPR1_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_1602333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   40000, .closedLoop =   96000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   40000, .closedLoop =   96000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   40000, .closedLoop =   96000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =   40000, .closedLoop =   96000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   40000, .closedLoop =   96000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =   40000, .closedLoop =   96000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_10488530112 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  5, .quotient =  401 },
                                      { .ro =  6, .quotient =  427 },
                                      { .ro =  8, .quotient =  297 },
                                      { .ro = 12, .quotient =  753 },
                                      { .ro = 14, .quotient =  414 } },
};


static cpr_fuse_data  fuses_3547227197 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW8_LSB, CPR1_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW8_MSB, CPR1_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_1470333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   32000, .closedLoop =   89000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   32000, .closedLoop =   89000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   32000, .closedLoop =   89000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =   32000, .closedLoop =   89000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   32000, .closedLoop =   89000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =   32000, .closedLoop =   89000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_5896948818 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  5, .quotient =  530 },
                                      { .ro =  6, .quotient =  555 },
                                      { .ro =  8, .quotient =  403 },
                                      { .ro = 12, .quotient =  914 },
                                      { .ro = 14, .quotient =  543 } },
};


static cpr_fuse_data  fuses_2746177624 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW8_MSB, CPR1_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_1998333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   48000, .closedLoop =  105000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   48000, .closedLoop =  105000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   48000, .closedLoop =  105000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =   48000, .closedLoop =  105000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   48000, .closedLoop =  105000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =   48000, .closedLoop =  105000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_9684787337 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  5, .quotient =  635 },
                                      { .ro =  8, .quotient =  505 },
                                      { .ro = 12, .quotient = 1059 },
                                      { .ro = 14, .quotient =  645 } },
};


static cpr_fuse_data  fuses_2409201182 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW8_LSB, CPR1_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW8_MSB, CPR1_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_2322333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   64000, .closedLoop =  124000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   64000, .closedLoop =  124000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   64000, .closedLoop =  124000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =   64000, .closedLoop =  124000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   64000, .closedLoop =  124000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =   64000, .closedLoop =  124000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_10101489653 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  5, .quotient =  734 },
                                      { .ro =  8, .quotient =  601 },
                                      { .ro = 12, .quotient = 1177 },
                                      { .ro = 14, .quotient =  764 } },
};


static cpr_fuse_data  fuses_122242650 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW8_MSB, CPR1_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_quotient_cfg  quotients_4631931985 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  5, .quotient =  819 },
                                      { .ro =  8, .quotient =  684 },
                                      { .ro = 12, .quotient = 1278 },
                                      { .ro = 14, .quotient =  866 } },
};


static cpr_fuse_data  fuses_2292510293 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW8_LSB, CPR1_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW8_LSB, CPR1_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_kv_cfg  kvs_38704097471 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =    0 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =  302 },
                                { .ro =  6, .kv =  308 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =  271 },
                                { .ro =  9, .kv =    0 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =  401 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  318 },
                                { .ro = 15, .kv =    0 } },
};


/*
 * MSS Voltage Plan
 */
static cpr_voltage_plan voltage_plan_18394366151 =
{
    .modesCount      = 7,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_38704097471,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS_D1
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_6242647411, .quotients = &quotients_14080841326, .margins = &margins_1074333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_2808018135, .quotients = &quotients_16689446886, .margins = &margins_1134333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 33} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_3547227197, .quotients = &quotients_10488530112, .margins = &margins_1602333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_2746177624, .quotients = &quotients_5896948818, .margins = &margins_1470333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  760000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_2409201182, .quotients = &quotients_9684787337, .margins = &margins_1998333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  816000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_122242650, .quotients = &quotients_10101489653, .margins = &margins_2322333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  872000, .floor =  688000, .freq =       0, .interplEnabled = 54} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_2292510293, .quotients = &quotients_4631931985, .margins = &margins_2322333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  872000, .floor =  716000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_17 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =      0 } }
};


static cpr_fuse_data  fuses_2919846070 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW10_MSB, CPR3_TARG_VOLT_SVS2) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_fuse_data  fuses_3110463891 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW10_LSB, CPR3_TARG_VOLT_SUT) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


/*
 * VDDA Voltage Plan
 */
static cpr_voltage_plan voltage_plan_26584785766 =
{
    .modesCount      = 13,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_D1,
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

        // LOW_SVS_D1
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
        {.fref = 704000, .freqDelta =       0, .fuses = &fuses_2919846070, .quotients = NULL, .margins = &margins_17,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  824000, .floor =  688000, .freq =       0, .interplEnabled = 0} } },

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
        {.fref = 892000, .freqDelta =       0, .fuses = &fuses_3110463891, .quotients = NULL, .margins = &margins_17,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  952000, .floor =  892000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =       0, .floor =       0, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_1080333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =   60000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   60000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   60000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =       0, .closedLoop =   60000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =       0, .closedLoop =   60000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =       0, .closedLoop =   60000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_12835090235 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  580 },
                                      { .ro =  5, .quotient =  586 },
                                      { .ro =  6, .quotient =  280 },
                                      { .ro =  7, .quotient =  224 },
                                      { .ro = 14, .quotient =  753 },
                                      { .ro = 15, .quotient =  599 } },
};


static cpr_fuse_data  fuses_6648516906 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW10_MSB, CPR4_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW11_LSB, CPR4_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_1320333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =   60000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   60000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   60000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =       0, .closedLoop =   60000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =       0, .closedLoop =   60000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =       0, .closedLoop =   60000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_margin_cfg margins_1332333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =   61000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   61000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   61000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =       0, .closedLoop =   61000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =       0, .closedLoop =   61000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =       0, .closedLoop =   61000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_7603973636 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  624 },
                                      { .ro =  5, .quotient =  630 },
                                      { .ro =  6, .quotient =  296 },
                                      { .ro =  7, .quotient =  241 },
                                      { .ro = 14, .quotient =  802 },
                                      { .ro = 15, .quotient =  645 } },
};


static cpr_fuse_data  fuses_4547663609 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW10_MSB, CPR4_TARG_VOLT_NOML1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW11_LSB, CPR4_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_margin_cfg margins_1368333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =   64000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   64000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   64000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =       0, .closedLoop =   64000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =       0, .closedLoop =   64000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =       0, .closedLoop =   64000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_10035238806 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  684 },
                                      { .ro =  5, .quotient =  711 },
                                      { .ro =  6, .quotient =  326 },
                                      { .ro =  7, .quotient =  273 },
                                      { .ro = 14, .quotient =  890 },
                                      { .ro = 15, .quotient =  738 } },
};


static cpr_fuse_data  fuses_5069676604 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW11_LSB, CPR4_TARG_VOLT_TUR_5_3), CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW10_MSB, CPR4_TARG_VOLT_TUR_2_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW11_LSB, CPR4_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_margin_cfg margins_1392333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =   66000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   66000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   66000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =       0, .closedLoop =   66000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =       0, .closedLoop =   66000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =       0, .closedLoop =   66000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_10798429868 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  801 },
                                      { .ro =  5, .quotient =  804 },
                                      { .ro =  6, .quotient =  361 },
                                      { .ro =  7, .quotient =  304 },
                                      { .ro = 14, .quotient =  991 },
                                      { .ro = 15, .quotient =  830 } },
};


static cpr_fuse_data  fuses_990733764 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW10_MSB, CPR4_TARG_VOLT_SUT) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW11_LSB, CPR4_TARG_VOLT_OFFSET_SUT) } } },
};


static cpr_kv_cfg  kvs_29155255631 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =    0 },
                                { .ro =  4, .kv =  305 },
                                { .ro =  5, .kv =  306 },
                                { .ro =  6, .kv =  111 },
                                { .ro =  7, .kv =  107 },
                                { .ro =  8, .kv =    0 },
                                { .ro =  9, .kv =    0 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =    0 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  328 },
                                { .ro = 15, .kv =  319 } },
};


/*
 * MX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_21271807872 =
{
    .modesCount      = 8,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_29155255631,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_SVS_L2,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1,
                                                    CPR_VOLTAGE_MODE_TURBO_L3 },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref = 540000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  680000, .floor =  500000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L2
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_6648516906, .quotients = &quotients_12835090235, .margins = &margins_1080333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  804000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_6648516906, .quotients = &quotients_12835090235, .margins = &margins_1320333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  804000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_4547663609, .quotients = &quotients_7603973636, .margins = &margins_1332333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_5069676604, .quotients = &quotients_10035238806, .margins = &margins_1368333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_990733764, .quotients = &quotients_10798429868, .margins = &margins_1392333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L3
        {.fref = 884000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  884000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_1224334 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =   72000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   72000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   72000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =       0, .closedLoop =   72000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =       0, .closedLoop =   72000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =       0, .closedLoop =   72000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_fuse_data  fuses_6614219138 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW11_MSB, CPR5_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW11_MSB, CPR5_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_1416333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =   68000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   68000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   68000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =       0, .closedLoop =   68000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =       0, .closedLoop =   68000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =       0, .closedLoop =   68000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_margin_cfg margins_2148333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   40000, .closedLoop =  109000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   40000, .closedLoop =  109000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   40000, .closedLoop =  109000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =   40000, .closedLoop =  109000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   40000, .closedLoop =  109000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =   40000, .closedLoop =  109000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_fuse_data  fuses_2066137572 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW11_MSB, CPR5_TARG_VOLT_NOML1_5_3), CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW11_LSB, CPR5_TARG_VOLT_NOML1_2_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW11_MSB, CPR5_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_margin_cfg margins_1896333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   24000, .closedLoop =   96000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   24000, .closedLoop =   96000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   24000, .closedLoop =   96000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =   24000, .closedLoop =   96000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   24000, .closedLoop =   96000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =   24000, .closedLoop =   96000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_fuse_data  fuses_4292379192 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW11_MSB, CPR5_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW12_LSB, CPR5_TARG_VOLT_OFFSET_TUR_4_2), CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW11_MSB, CPR5_TARG_VOLT_OFFSET_TUR_1_0) } } },
};


static cpr_margin_cfg margins_1440333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =    8000, .closedLoop =   66000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =    8000, .closedLoop =   66000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =    8000, .closedLoop =   66000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =    8000, .closedLoop =   66000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =    8000, .closedLoop =   66000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =    8000, .closedLoop =   66000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_fuse_data  fuses_2561910408 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW11_LSB, CPR5_TARG_VOLT_SUT) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW11_MSB, CPR5_TARG_VOLT_OFFSET_SUT) } } },
};


static cpr_kv_cfg  kvs_30010946785 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =    0 },
                                { .ro =  4, .kv =  305 },
                                { .ro =  5, .kv =  306 },
                                { .ro =  6, .kv =  111 },
                                { .ro =  7, .kv =  107 },
                                { .ro =  8, .kv =    0 },
                                { .ro =  9, .kv =    0 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =    0 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  328 },
                                { .ro = 15, .kv =  318 } },
};


/*
 * MXC Voltage Plan
 */
static cpr_voltage_plan voltage_plan_18928944076 =
{
    .modesCount      = 8,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_30010946785,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_SVS_L2,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1,
                                                    CPR_VOLTAGE_MODE_TURBO_L3 },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref = 540000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  552000, .floor =  540000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L2
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_6614219138, .quotients = &quotients_12835090235, .margins = &margins_1224334,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  804000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_6614219138, .quotients = &quotients_12835090235, .margins = &margins_1416333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  804000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_2066137572, .quotients = &quotients_7603973636, .margins = &margins_2148333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_4292379192, .quotients = &quotients_10035238806, .margins = &margins_1896333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_2561910408, .quotients = &quotients_10798429868, .margins = &margins_1440333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L3
        {.fref = 884000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  884000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_18 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 } }
};


static cpr_fuse_data  fuses_3502625455 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW12_LSB, CPR6_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_fuse_data  fuses_229257390 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW12_LSB, CPR6_TARG_VOLT_NOML1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_fuse_data  fuses_3311970560 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW12_LSB, CPR6_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


/*
 * LPI_MX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_13001212439 =
{
    .modesCount      = 5,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref = 536000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  552000, .floor =  536000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_3502625455, .quotients = NULL, .margins = &margins_18,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  808000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_229257390, .quotients = NULL, .margins = &margins_18,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  808000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_3311970560, .quotients = NULL, .margins = &margins_18,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  848000, .floor =  800000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_1038333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   20000, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   20000, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   20000, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =   20000, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   20000, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =   20000, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_17847638086 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  5, .quotient =  219 },
                                      { .ro =  6, .quotient =  237 },
                                      { .ro =  8, .quotient =  139 },
                                      { .ro =  9, .quotient =  142 },
                                      { .ro = 14, .quotient =  230 },
                                      { .ro = 15, .quotient =  142 } },
};


static cpr_fuse_data  fuses_4301001310 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW12_MSB, CPR7_TARG_VOLT_SVS3) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW13_LSB, CPR7_TARG_VOLT_OFFSET_SVS3) } } },
};


static cpr_margin_cfg margins_1086333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   20000, .closedLoop =   63000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   20000, .closedLoop =   63000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   20000, .closedLoop =   63000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =   20000, .closedLoop =   63000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   20000, .closedLoop =   63000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =   20000, .closedLoop =   63000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_18008829833 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  5, .quotient =  272 },
                                      { .ro =  6, .quotient =  298 },
                                      { .ro =  8, .quotient =  182 },
                                      { .ro =  9, .quotient =  185 },
                                      { .ro = 14, .quotient =  286 },
                                      { .ro = 15, .quotient =  183 } },
};


static cpr_fuse_data  fuses_1415255673 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW13_LSB, CPR7_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_978333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =    8000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =    8000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =    8000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =    8000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =    8000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =    8000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_6950126808 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  6, .quotient =  427 },
                                      { .ro =  9, .quotient =  301 },
                                      { .ro = 14, .quotient =  414 },
                                      { .ro = 15, .quotient =  301 } },
};


static cpr_fuse_data  fuses_4872694234 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW12_MSB, CPR7_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW13_LSB, CPR7_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_942333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =    4000, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =    4000, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =    4000, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =    4000, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =    4000, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =    4000, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_3274901664 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  6, .quotient =  555 },
                                      { .ro =  9, .quotient =  410 },
                                      { .ro = 14, .quotient =  543 },
                                      { .ro = 15, .quotient =  415 } },
};


static cpr_fuse_data  fuses_1651098260 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW13_LSB, CPR7_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_1170333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =    4000, .closedLoop =   58000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =    4000, .closedLoop =   58000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =    4000, .closedLoop =   58000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =    4000, .closedLoop =   58000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =    4000, .closedLoop =   58000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =    4000, .closedLoop =   58000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_10307577723 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  803 },
                                      { .ro =  6, .quotient =  659 },
                                      { .ro =  9, .quotient =  511 },
                                      { .ro = 14, .quotient =  645 },
                                      { .ro = 15, .quotient =  512 } },
};


static cpr_fuse_data  fuses_5140376407 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW12_MSB, CPR7_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW13_LSB, CPR7_TARG_VOLT_OFFSET_NOM_4_3), CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW12_MSB, CPR7_TARG_VOLT_OFFSET_NOM_2_0) } } },
};


static cpr_quotient_cfg  quotients_5575129731 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  997 },
                                      { .ro =  6, .quotient =  875 },
                                      { .ro =  9, .quotient =  711 },
                                      { .ro = 14, .quotient =  866 },
                                      { .ro = 15, .quotient =  724 } },
};


static cpr_fuse_data  fuses_6953200874 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW12_MSB, CPR7_TARG_VOLT_TUR_5), CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW12_LSB, CPR7_TARG_VOLT_TUR_4_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW12_MSB, CPR7_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_kv_cfg  kvs_30481413631 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =  337 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =  305 },
                                { .ro =  6, .kv =  309 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =  274 },
                                { .ro =  9, .kv =  279 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =    0 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  320 },
                                { .ro = 15, .kv =  287 } },
};


/*
 * LPI_CX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_13711991536 =
{
    .modesCount      = 7,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_30481413631,
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
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_4301001310, .quotients = &quotients_17847638086, .margins = &margins_1038333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_1415255673, .quotients = &quotients_18008829833, .margins = &margins_1086333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 33} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_4872694234, .quotients = &quotients_6950126808, .margins = &margins_978333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_1651098260, .quotients = &quotients_3274901664, .margins = &margins_942333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_5140376407, .quotients = &quotients_10307577723, .margins = &margins_1170333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  776000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_6953200874, .quotients = &quotients_5575129731, .margins = &margins_1266333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  716000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_1110333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   12000, .closedLoop =   69000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   12000, .closedLoop =   69000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   12000, .closedLoop =   69000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =   12000, .closedLoop =   69000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   12000, .closedLoop =   69000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =   12000, .closedLoop =   69000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_3947908659 =
{
    .count = 2,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  286 },
                                      { .ro = 15, .quotient =  183 } },
};


static cpr_fuse_data  fuses_4768396955 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW13_MSB, CPR8_TARG_VOLT_SVS2) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW14_LSB, CPR8_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_1050333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =    8000, .closedLoop =   66000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =    8000, .closedLoop =   66000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =    8000, .closedLoop =   66000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =    8000, .closedLoop =   66000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =    8000, .closedLoop =   66000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =    8000, .closedLoop =   66000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_fuse_data  fuses_5476917476 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW13_MSB, CPR8_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW14_LSB, CPR8_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_954333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =    4000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =    4000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =    4000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =    4000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =    4000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =    4000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_fuse_data  fuses_307304906 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW14_LSB, CPR8_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_930333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =  -16000, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -16000, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -16000, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =  -16000, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =  -16000, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =  -16000, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_8005663709 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  6, .quotient =  659 },
                                      { .ro =  9, .quotient =  511 },
                                      { .ro = 14, .quotient =  645 },
                                      { .ro = 15, .quotient =  512 } },
};


static cpr_fuse_data  fuses_280137029 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW13_MSB, CPR8_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW13_MSB, CPR8_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_quotient_cfg  quotients_3992206218 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  6, .quotient =  875 },
                                      { .ro =  9, .quotient =  711 },
                                      { .ro = 14, .quotient =  866 },
                                      { .ro = 15, .quotient =  724 } },
};


static cpr_fuse_data  fuses_5768210463 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW13_MSB, CPR8_TARG_VOLT_TUR_5_2), CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW13_LSB, CPR8_TARG_VOLT_TUR_1_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW13_MSB, CPR8_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_kv_cfg  kvs_32668879075 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =    0 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =    0 },
                                { .ro =  6, .kv =  312 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =    0 },
                                { .ro =  9, .kv =  283 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =    0 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  322 },
                                { .ro = 15, .kv =  292 } },
};


/*
 * MM Voltage Plan
 */
static cpr_voltage_plan voltage_plan_12949050863 =
{
    .modesCount      = 5,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_32668879075,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_4768396955, .quotients = &quotients_3947908659, .margins = &margins_1110333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_5476917476, .quotients = &quotients_4676959054, .margins = &margins_1050333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_307304906, .quotients = &quotients_3274901664, .margins = &margins_954333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_280137029, .quotients = &quotients_8005663709, .margins = &margins_930333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  776000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_5768210463, .quotients = &quotients_3992206218, .margins = &margins_1266333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  716000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_333 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 } }
};


static cpr_margin_cfg margins_19 = {
    .count = 6,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =  -30000, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -30000, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -30000, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 3, .cprRevMax = 3, .openLoop =  -30000, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 4, .cprRevMax = 4, .openLoop =  -30000, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 5, .cprRevMax = 5, .openLoop =  -30000, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 } }
};


/*
 * WMSS_CX_1 Voltage Plan
 */
static cpr_voltage_plan voltage_plan_7097588994 =
{
    .modesCount      = 3,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_NOMINAL },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS
        {.fref = 592000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  648000, .floor =  504000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 672000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  720000, .floor =  592000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_19,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  864000, .floor =  712000, .freq =       0, .interplEnabled = 0} } }},
};


/*
 * WMSS_CX_2 Voltage Plan
 */
static cpr_voltage_plan voltage_plan_5716214427 =
{
    .modesCount      = 3,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_NOMINAL },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS
        {.fref = 588000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  588000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 668000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_333,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  728000, .floor =  596000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 744000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_333,
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
    .sensorID             = 13,
    .kv                   = 78,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 2, .data = (struct raw_fuse_data[]) {
                                 {QFPROM_CORR_REG_BASE | (0x221C28C8 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<2) | (1<<1) | (1<<0)},
                                 {QFPROM_CORR_REG_BASE | (0x221C28C4 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 27, (1<<31) | (1<<30) | (1<<29) | (1<<28) | (1<<27)} } }
};


static cpr_aging_cfg  aging_cfg_gfx =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO_L1,
    .sensorID             = 0,
    .kv                   = 78,
    .scalingFactor        = 15,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {QFPROM_CORR_REG_BASE | (0x221C28D8 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<24) | (1<<23) | (1<<22) | (1<<21) | (1<<20) | (1<<19) | (1<<18) | (1<<17)} } }
};


static cpr_aging_cfg  aging_cfg_mss =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO,
    .sensorID             = 25,
    .kv                   = 87,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 2, .data = (struct raw_fuse_data[]) {
                                 {QFPROM_CORR_REG_BASE | (0x221C28D0 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1) | (1<<0)},
                                 {QFPROM_CORR_REG_BASE | (0x221C28CC & (QFPROM_CORR_REG_BASE_SIZE - 1)), 30, (1<<31) | (1<<30)} } }
};


static cpr_aging_cfg  aging_cfg_mx =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO,
    .sensorID             = 11,
    .kv                   = 87,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {QFPROM_CORR_REG_BASE | (0x221C292C & (QFPROM_CORR_REG_BASE_SIZE - 1)), 23, (1<<30) | (1<<29) | (1<<28) | (1<<27) | (1<<26) | (1<<25) | (1<<24) | (1<<23)} } }
};


static cpr_aging_cfg  aging_cfg_lpi_cx =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_NOMINAL,
    .sensorID             = 9,
    .kv                   = 96,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {QFPROM_CORR_REG_BASE | (0x221C28F0 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 22, (1<<29) | (1<<28) | (1<<27) | (1<<26) | (1<<25) | (1<<24) | (1<<23) | (1<<22)} } }
};


static cpr_aging_cfg  aging_cfg_mm =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO,
    .sensorID             = 18,
    .kv                   = 87,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {QFPROM_CORR_REG_BASE | (0x221C28F8 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 20, (1<<27) | (1<<26) | (1<<25) | (1<<24) | (1<<23) | (1<<22) | (1<<21) | (1<<20)} } }
};


/*
 * Versioned Voltage Plans
 */

static cpr_versioned_voltage_plan cx_vvp = {
    .rail     = CPR_RAIL_CX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_18426875048 },
     },
    .count    = 1,
    .agingCfg = &aging_cfg_cx
};


static cpr_versioned_voltage_plan gfx_vvp = {
    .rail     = CPR_RAIL_GFX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_24034179149 },
     },
    .count    = 1,
    .agingCfg = &aging_cfg_gfx
};


static cpr_versioned_voltage_plan mss_vvp = {
    .rail     = CPR_RAIL_MSS,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_18394366151 },
     },
    .count    = 1,
    .agingCfg = &aging_cfg_mss
};


static cpr_versioned_voltage_plan vdda_vvp = {
    .rail     = CPR_RAIL_VDDA,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_26584785766 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan mx_vvp = {
    .rail     = CPR_RAIL_MX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_21271807872 },
     },
    .count    = 1,
    .agingCfg = &aging_cfg_mx
};


static cpr_versioned_voltage_plan mxc_vvp = {
    .rail     = CPR_RAIL_MXC,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_18928944076 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan lpi_mx_vvp = {
    .rail     = CPR_RAIL_LPI_MX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_13001212439 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan lpi_cx_vvp = {
    .rail     = CPR_RAIL_LPI_CX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_13711991536 },
     },
    .count    = 1,
    .agingCfg = &aging_cfg_lpi_cx
};


static cpr_versioned_voltage_plan mm_vvp = {
    .rail     = CPR_RAIL_MM,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_12949050863 },
     },
    .count    = 1,
    .agingCfg = &aging_cfg_mm
};


static cpr_versioned_voltage_plan wmss_cx_1_vvp = {
    .rail     = CPR_RAIL_WMSS_CX_1,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_7097588994 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan wmss_cx_2_vvp = {
    .rail     = CPR_RAIL_WMSS_CX_2,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_5716214427 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan wmss_cx_3_vvp = {
    .rail     = CPR_RAIL_WMSS_CX_3,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_7097588994 },
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
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24 },
    .sensorsCount = 25,
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
    .sensors      = (uint8[]){ 3,4,7,8,9 },
    .sensorsCount = 5,
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
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26 },
    .sensorsCount = 27,
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
    .sensors      = (uint8[]){ 0,1,2,5,6,7,8,11,12,13,14,15,16,17,18,19,20,21,22,23,24 },
    .sensorsCount = 21,
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
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34 },
    .sensorsCount = 35,
};


static cpr_hal_thread  mxc_thread = {
    .id   = 0,
    .cfg  = &mxc_thread_cfg,
};


/*
 * CPR Controller Config
 */

static cpr_hal_controller_cfg cpr3_controller_cfg = {
    .stepQuotMin         = 11,
    .stepQuotMax         = 16,
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
    .stepQuotMin         = 11,
    .stepQuotMax         = 13,
    .sensorsTotal        = 57,
    .bypassSensors       = NULL,
    .bypassSensorsCount  = 0,
    .disableSensors      = (uint8[]){ 1,2,3,5,6,7,8,9,10,12,45,46,47,48,53,54,55,56 },
    .disableSensorsCount = 18,
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
    .stepQuotMin         = 12,
    .stepQuotMax         = 15,
    .sensorsTotal        = 25,
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
    .stepQuotMin         = 11,
    .stepQuotMax         = 13,
    .sensorsTotal        = 10,
    .bypassSensors       = NULL,
    .bypassSensorsCount  = 0,
    .disableSensors      = (uint8[]){ 0,1,2,5,6 },
    .disableSensorsCount = 5,
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
    .stepQuotMin         = 11,
    .stepQuotMax         = 13,
    .sensorsTotal        = 27,
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
    .stepQuotMin         = 4,
    .stepQuotMax         = 13,
    .sensorsTotal        = 60,
    .bypassSensors       = (uint8[]){ 3,4,9,10,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59 },
    .bypassSensorsCount  = 39,
    .disableSensors      = (uint8[]){ 3,4,9,10,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59 },
    .disableSensorsCount = 39,
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
    .stepQuotMin         = 4,
    .stepQuotMax         = 13,
    .sensorsTotal        = 35,
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
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 20, (1<<23) | (1<<22) | (1<<21) | (1<<20)} } },
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
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 20, (1<<23) | (1<<22) | (1<<21) | (1<<20)} } },
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
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 20, (1<<23) | (1<<22) | (1<<21) | (1<<20)} } },
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
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 20, (1<<23) | (1<<22) | (1<<21) | (1<<20)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_mm_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_MM,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_HW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 20, (1<<23) | (1<<22) | (1<<21) | (1<<20)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_mss_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_MSS,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_HW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 20, (1<<23) | (1<<22) | (1<<21) | (1<<20)} } },
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
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 20, (1<<23) | (1<<22) | (1<<21) | (1<<20)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_mxc_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_MXC,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_SW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 20, (1<<23) | (1<<22) | (1<<21) | (1<<20)} } },
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
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 20, (1<<23) | (1<<22) | (1<<21) | (1<<20)} } },
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
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 20, (1<<23) | (1<<22) | (1<<21) | (1<<20)} } },
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
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 20, (1<<23) | (1<<22) | (1<<21) | (1<<20)} } },
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
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 20, (1<<23) | (1<<22) | (1<<21) | (1<<20)} } },
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
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 20, (1<<23) | (1<<22) | (1<<21) | (1<<20)} } },
    .enable            = 0,
};


static cpr_misc_cfg misc_cfg = {
    .cprRev = {.count = 1, .data = (struct raw_fuse_data[]) { {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 20, (1<<23) | (1<<22) | (1<<21) | (1<<20)} } }
};


cpr_settings cpr_settings_palima =
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

