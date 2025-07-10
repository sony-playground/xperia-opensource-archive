/*******************************************************************************
 *
 * Copyright (c) 2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 * THIS IS AUTO-GENERATED CPR CONFIG FILE FOR waipio.
 *
 * DateTime: 2023/12/05 05:41:31
 *
 *******************************************************************************/
#include "cpr_data.h"
#include "cpr_image_target_init.h"
#include "cpr_target_hwio.h"


//hash value of Voltage Plan file (extracted all cell values)
static char voltage_plan_hash_value[] = "F99E36D0893989FD08FF8C1665658D19";


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


static cpr_margin_cfg margins_249040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   40000, .closedLoop =   86000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_9291165103 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  336 },
                                      { .ro =  9, .quotient =  365 },
                                      { .ro = 10, .quotient =  210 },
                                      { .ro = 12, .quotient =  224 },
                                      { .ro = 15, .quotient =  424 } },
};


static cpr_fuse_data  fuses_3255791880 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW7_LSB, CPR0_TARG_VOLT_SVS2) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW7_MSB, CPR0_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_175040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   12000, .closedLoop =   63000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_12029526960 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  483 },
                                      { .ro =  9, .quotient =  516 },
                                      { .ro = 10, .quotient =  343 },
                                      { .ro = 12, .quotient =  357 },
                                      { .ro = 15, .quotient =  591 } },
};


static cpr_fuse_data  fuses_6795546843 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW7_LSB, CPR0_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW7_MSB, CPR0_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_147040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   55000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_5323485889 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  573 },
                                      { .ro =  9, .quotient =  619 },
                                      { .ro = 10, .quotient =  436 },
                                      { .ro = 12, .quotient =  456 },
                                      { .ro = 15, .quotient =  693 } },
};


static cpr_fuse_data  fuses_3464103763 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW7_MSB, CPR0_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_195040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_13830658778 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  941 },
                                      { .ro =  4, .quotient =  828 },
                                      { .ro =  6, .quotient =  874 },
                                      { .ro =  8, .quotient =  724 },
                                      { .ro =  9, .quotient =  775 },
                                      { .ro = 15, .quotient =  860 } },
};


static cpr_fuse_data  fuses_5674476035 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW7_LSB, CPR0_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW7_MSB, CPR0_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_211040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   67000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_12005546524 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  0, .quotient = 1192 },
                                      { .ro =  1, .quotient = 1243 },
                                      { .ro =  2, .quotient = 1045 },
                                      { .ro =  7, .quotient = 1114 },
                                      { .ro =  9, .quotient =  879 },
                                      { .ro = 15, .quotient =  967 } },
};


static cpr_fuse_data  fuses_1513134881 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW7_MSB, CPR0_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_margin_cfg margins_215040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   69000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_14737171641 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  0, .quotient = 1264 },
                                      { .ro =  1, .quotient = 1311 },
                                      { .ro =  2, .quotient = 1114 },
                                      { .ro =  7, .quotient = 1188 },
                                      { .ro =  9, .quotient =  949 },
                                      { .ro = 15, .quotient = 1038 } },
};


static cpr_fuse_data  fuses_5741285492 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW7_MSB, CPR0_TARG_VOLT_OFFSET_TUR_4_3), CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW7_LSB, CPR0_TARG_VOLT_OFFSET_TUR_2_0) } } },
};


static cpr_margin_cfg margins_227040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   75000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_17204601896 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  0, .quotient = 1392 },
                                      { .ro =  1, .quotient = 1437 },
                                      { .ro =  2, .quotient = 1245 },
                                      { .ro =  7, .quotient = 1309 },
                                      { .ro =  9, .quotient = 1110 },
                                      { .ro = 15, .quotient = 1205 } },
};


static cpr_fuse_data  fuses_3434864866 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW7_LSB, CPR0_TARG_VOLT_SUT) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW7_LSB, CPR0_TARG_VOLT_OFFSET_SUT) } } },
};


static cpr_kv_cfg  kvs_29180137837 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =  239 },
                                { .ro =  1, .kv =  240 },
                                { .ro =  2, .kv =  237 },
                                { .ro =  3, .kv =    0 },
                                { .ro =  4, .kv =  280 },
                                { .ro =  5, .kv =    0 },
                                { .ro =  6, .kv =  282 },
                                { .ro =  7, .kv =  223 },
                                { .ro =  8, .kv =  271 },
                                { .ro =  9, .kv =  269 },
                                { .ro = 10, .kv =  240 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =  240 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =    0 },
                                { .ro = 15, .kv =  281 } },
};


/*
 * CX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_21371602810 =
{
    .modesCount      = 9,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_29180137837,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1,
                                                    CPR_VOLTAGE_MODE_SUPER_TURBO_NO_CPR },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  352000, .floor =  352000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 584000, .freqDelta =       0, .fuses = &fuses_3255791880, .quotients = &quotients_9291165103, .margins = &margins_249040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  684000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 656000, .freqDelta =       0, .fuses = &fuses_6795546843, .quotients = &quotients_12029526960, .margins = &margins_175040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  760000, .floor =  576000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 712000, .freqDelta =       0, .fuses = &fuses_3464103763, .quotients = &quotients_5323485889, .margins = &margins_147040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  624000, .freq =       0, .interplEnabled = 43} } },

        // NOMINAL
        {.fref = 784000, .freqDelta =       0, .fuses = &fuses_5674476035, .quotients = &quotients_13830658778, .margins = &margins_195040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  868000, .floor =  676000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_1513134881, .quotients = &quotients_12005546524, .margins = &margins_211040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  716000, .freq =       0, .interplEnabled = 31} } },

        // TURBO
        {.fref = 868000, .freqDelta =       0, .fuses = &fuses_5741285492, .quotients = &quotients_14737171641, .margins = &margins_215040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  924000, .floor =  740000, .freq =       0, .interplEnabled = 52} } },

        // TURBO_L1
        {.fref = 944000, .freqDelta =       0, .fuses = &fuses_3434864866, .quotients = &quotients_17204601896, .margins = &margins_227040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling = 1004000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // SUPER_TURBO_NO_CPR
        {.fref = 1004000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling = 1004000, .floor = 1004000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_version  ver_ANY_1_0_1_255 = { .foundry = CPR_FOUNDRY_ANY, .min = CPR_CHIPINFO_VERSION(1,0), .max = CPR_CHIPINFO_VERSION(1,255) };


static cpr_margin_cfg margins_328099 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 2, .openLoop =       0, .closedLoop =   66000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 3, .cprRevMax = 7, .openLoop =   24000, .closedLoop =   66000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_714638645 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  290 } },
};


static cpr_fuse_data  fuses_8353458498 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW9_MSB, CPR2_TARG_VOLT_SVS3_5_2), CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW9_LSB, CPR2_TARG_VOLT_SVS3_1_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW10_LSB, CPR2_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_310099 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 2, .openLoop =  -16000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 3, .cprRevMax = 7, .openLoop =   16000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_2904992169 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  439 } },
};


static cpr_fuse_data  fuses_2416996329 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW10_LSB, CPR2_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_406099 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 2, .openLoop =       0, .closedLoop =   76000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 3, .cprRevMax = 7, .openLoop =   32000, .closedLoop =   76000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_354099 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 2, .openLoop =   -8000, .closedLoop =   69000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 3, .cprRevMax = 7, .openLoop =   16000, .closedLoop =   69000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_3577248570 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  530 } },
};


static cpr_fuse_data  fuses_7364190841 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW9_LSB, CPR2_TARG_VOLT_SVSL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW10_LSB, CPR2_TARG_VOLT_OFFSET_SVSL1_4_3), CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW9_MSB, CPR2_TARG_VOLT_OFFSET_SVSL1_2_0) } } },
};


static cpr_margin_cfg margins_402099 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 2, .openLoop =       0, .closedLoop =   77000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 3, .cprRevMax = 7, .openLoop =   24000, .closedLoop =   77000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_418099 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 2, .openLoop =       0, .closedLoop =   81000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 3, .cprRevMax = 7, .openLoop =   24000, .closedLoop =   81000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_1326455381 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  589 } },
};


static cpr_fuse_data  fuses_3215405778 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW9_MSB, CPR2_TARG_VOLT_OFFSET_SVSL2) } } },
};


static cpr_margin_cfg margins_614099 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 2, .openLoop =       0, .closedLoop =  104000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 3, .cprRevMax = 7, .openLoop =   48000, .closedLoop =  104000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_1562141003 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  672 } },
};


static cpr_fuse_data  fuses_2947686763 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW9_LSB, CPR2_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW9_MSB, CPR2_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_690099 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 2, .openLoop =       0, .closedLoop =  119000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 3, .cprRevMax = 7, .openLoop =   64000, .closedLoop =  119000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_2386395360 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  758 } },
};


static cpr_fuse_data  fuses_4710604682 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW9_LSB, CPR2_TARG_VOLT_NOML1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW9_MSB, CPR2_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_margin_cfg margins_702099 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 2, .openLoop =       0, .closedLoop =  122000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 3, .cprRevMax = 7, .openLoop =   64000, .closedLoop =  122000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_2679930468 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  815 } },
};


static cpr_fuse_data  fuses_2675281751 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW9_MSB, CPR2_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_margin_cfg margins_774099 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 2, .openLoop =       0, .closedLoop =  136000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 3, .cprRevMax = 7, .openLoop =   80000, .closedLoop =  136000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_2472744089 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  940 } },
};


static cpr_fuse_data  fuses_7189446118 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW9_LSB, CPR2_TARG_VOLT_SUT) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW9_MSB, CPR2_TARG_VOLT_OFFSET_SUT) } } },
};


static cpr_kv_cfg  kvs_34125314129 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =    0 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =    0 },
                                { .ro =  6, .kv =    0 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =    0 },
                                { .ro =  9, .kv =    0 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =    0 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  266 },
                                { .ro = 15, .kv =    0 } },
};


/*
 * GFX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_25044200157 =
{
    .modesCount      = 10,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_34125314129,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_L1,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L0,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_SVS_L2,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1 },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS
        {.fref = 556000, .freqDelta =       0, .fuses = &fuses_8353458498, .quotients = &quotients_714638645, .margins = &margins_328099,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  656000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS_L1
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_2416996329, .quotients = &quotients_2904992169, .margins = &margins_310099,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  716000, .floor =  536000, .freq =       0, .interplEnabled = 57} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_2416996329, .quotients = &quotients_2904992169, .margins = &margins_406099,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  732000, .floor =  552000, .freq =       0, .interplEnabled = 57} } },

        // SVS_L0
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_7364190841, .quotients = &quotients_3577248570, .margins = &margins_354099,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  788000, .floor =  592000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_7364190841, .quotients = &quotients_3577248570, .margins = &margins_402099,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  796000, .floor =  600000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L2
        {.fref = 712000, .freqDelta =       0, .fuses = &fuses_3215405778, .quotients = &quotients_1326455381, .margins = &margins_418099,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  624000, .freq =       0, .interplEnabled = 42} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_2947686763, .quotients = &quotients_1562141003, .margins = &margins_614099,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  824000, .floor =  656000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_4710604682, .quotients = &quotients_2386395360, .margins = &margins_690099,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  696000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_2675281751, .quotients = &quotients_2679930468, .margins = &margins_702099,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  716000, .freq =       0, .interplEnabled = 32} } },

        // TURBO_L1
        {.fref = 904000, .freqDelta =       0, .fuses = &fuses_7189446118, .quotients = &quotients_2472744089, .margins = &margins_774099,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  968000, .floor =  768000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_302099 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 2, .openLoop =       0, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 3, .cprRevMax = 7, .openLoop =    8000, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_7950278734 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  246 },
                                      { .ro =  9, .quotient =  269 },
                                      { .ro = 14, .quotient =  256 },
                                      { .ro = 15, .quotient =  317 } },
};


static cpr_fuse_data  fuses_7235493532 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW8_LSB, CPR1_TARG_VOLT_SVS3) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW8_MSB, CPR1_TARG_VOLT_OFFSET_SVS3) } } },
};


static cpr_margin_cfg margins_338099 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 2, .openLoop =    8000, .closedLoop =   61000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 3, .cprRevMax = 7, .openLoop =   16000, .closedLoop =   61000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_10497814491 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  279 },
                                      { .ro =  9, .quotient =  304 },
                                      { .ro = 14, .quotient =  290 },
                                      { .ro = 15, .quotient =  356 } },
};


static cpr_fuse_data  fuses_238806686 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW8_MSB, CPR1_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_350099 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 2, .openLoop =    8000, .closedLoop =   66000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 3, .cprRevMax = 7, .openLoop =    8000, .closedLoop =   66000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_9434320922 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  421 },
                                      { .ro =  9, .quotient =  454 },
                                      { .ro = 14, .quotient =  439 },
                                      { .ro = 15, .quotient =  523 } },
};


static cpr_fuse_data  fuses_6400365702 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW8_LSB, CPR1_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW8_MSB, CPR1_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_402100 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 2, .openLoop =   16000, .closedLoop =   75000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 3, .cprRevMax = 7, .openLoop =   16000, .closedLoop =   75000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_10628811778 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  519 },
                                      { .ro =  9, .quotient =  551 },
                                      { .ro = 14, .quotient =  530 },
                                      { .ro = 15, .quotient =  628 } },
};


static cpr_fuse_data  fuses_3499167844 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW8_MSB, CPR1_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_606099 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 2, .openLoop =   36000, .closedLoop =   96000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 3, .cprRevMax = 7, .openLoop =   36000, .closedLoop =   96000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_7200322053 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  655 },
                                      { .ro =  9, .quotient =  705 },
                                      { .ro = 14, .quotient =  672 },
                                      { .ro = 15, .quotient =  784 } },
};


static cpr_fuse_data  fuses_4191318810 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW8_LSB, CPR1_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW8_MSB, CPR1_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_818099 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 2, .openLoop =   72000, .closedLoop =  131000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 3, .cprRevMax = 7, .openLoop =   72000, .closedLoop =  131000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_9845772929 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  737 },
                                      { .ro =  9, .quotient =  791 },
                                      { .ro = 14, .quotient =  758 },
                                      { .ro = 15, .quotient =  875 } },
};


static cpr_fuse_data  fuses_2986368825 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW8_MSB, CPR1_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_margin_cfg margins_614100 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 2, .openLoop =   36000, .closedLoop =   98000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 3, .cprRevMax = 7, .openLoop =   36000, .closedLoop =   98000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_8766969973 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  792 },
                                      { .ro =  9, .quotient =  849 },
                                      { .ro = 14, .quotient =  815 },
                                      { .ro = 15, .quotient =  935 } },
};


static cpr_fuse_data  fuses_6027291304 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW8_LSB, CPR1_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW8_LSB, CPR1_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_kv_cfg  kvs_37026506899 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =    0 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =    0 },
                                { .ro =  6, .kv =    0 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =  263 },
                                { .ro =  9, .kv =  261 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =    0 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  269 },
                                { .ro = 15, .kv =  285 } },
};


/*
 * MSS Voltage Plan
 */
static cpr_voltage_plan voltage_plan_11888173162 =
{
    .modesCount      = 7,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_37026506899,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS_D1
        {.fref = 540000, .freqDelta =       0, .fuses = &fuses_7235493532, .quotients = &quotients_7950278734, .margins = &margins_302099,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  680000, .floor =  680000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 556000, .freqDelta =       0, .fuses = &fuses_238806686, .quotients = &quotients_10497814491, .margins = &margins_338099,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  680000, .floor =  680000, .freq =       0, .interplEnabled = 19} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_6400365702, .quotients = &quotients_9434320922, .margins = &margins_350099,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  732000, .floor =  680000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_3499167844, .quotients = &quotients_10628811778, .margins = &margins_402100,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  796000, .floor =  680000, .freq =       0, .interplEnabled = 45} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_4191318810, .quotients = &quotients_7200322053, .margins = &margins_606099,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  824000, .floor =  680000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_2986368825, .quotients = &quotients_9845772929, .margins = &margins_818099,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  696000, .freq =       0, .interplEnabled = 60} } },

        // TURBO
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_6027291304, .quotients = &quotients_8766969973, .margins = &margins_614100,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  716000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_64960 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   33000, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =      0 } }
};


static cpr_fuse_data  fuses_424139257 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW10_MSB, CPR3_TARG_VOLT_SVS_5_1), CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW10_LSB, CPR3_TARG_VOLT_SVS_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_margin_cfg margins_97960 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =      0 } }
};


static cpr_fuse_data  fuses_2714839418 =
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
static cpr_voltage_plan voltage_plan_23338820795 =
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
        {.fref = 700000, .freqDelta =       0, .fuses = &fuses_424139257, .quotients = NULL, .margins = &margins_64960,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  800000, .floor =  700000, .freq =       0, .interplEnabled = 0} } },

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
        {.fref = 892000, .freqDelta =       0, .fuses = &fuses_2714839418, .quotients = NULL, .margins = &margins_97960,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  952000, .floor =  892000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =       0, .floor =       0, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_320082 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =       0, .closedLoop =   50000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 7, .openLoop =       0, .closedLoop =   50000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_6504684466 =
{
    .count = 2,
    .quots = (cpr_quotient[]) { { .ro =  0, .quotient =  756 },
                                      { .ro =  4, .quotient =  519 } },
};


static cpr_fuse_data  fuses_6490927279 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW11_LSB, CPR4_TARG_VOLT_SVSL1_5_3), CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW10_MSB, CPR4_TARG_VOLT_SVSL1_2_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW11_LSB, CPR4_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_436082 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =       0, .closedLoop =   59000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 7, .openLoop =       0, .closedLoop =   59000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_5091104467 =
{
    .count = 2,
    .quots = (cpr_quotient[]) { { .ro =  0, .quotient =  894 },
                                      { .ro =  4, .quotient =  622 } },
};


static cpr_fuse_data  fuses_5490243851 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW10_MSB, CPR4_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW11_LSB, CPR4_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_quotient_cfg  quotients_10301225351 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  0, .quotient = 1051 },
                                      { .ro =  1, .quotient = 1234 },
                                      { .ro =  4, .quotient =  742 },
                                      { .ro =  5, .quotient =  887 },
                                      { .ro =  7, .quotient = 1031 } },
};


static cpr_fuse_data  fuses_4917894785 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW10_MSB, CPR4_TARG_VOLT_NOML1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW11_LSB, CPR4_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_margin_cfg margins_452082 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =       0, .closedLoop =   63000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 7, .openLoop =       0, .closedLoop =   63000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_15456002170 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  0, .quotient = 1152 },
                                      { .ro =  1, .quotient = 1334 },
                                      { .ro =  4, .quotient =  820 },
                                      { .ro =  5, .quotient =  967 },
                                      { .ro =  7, .quotient = 1126 } },
};


static cpr_fuse_data  fuses_5121251345 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW10_MSB, CPR4_TARG_VOLT_SUT) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW11_LSB, CPR4_TARG_VOLT_OFFSET_SUT) } } },
};


static cpr_kv_cfg  kvs_32057870016 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =  376 },
                                { .ro =  1, .kv =  350 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =    0 },
                                { .ro =  4, .kv =  287 },
                                { .ro =  5, .kv =  277 },
                                { .ro =  6, .kv =    0 },
                                { .ro =  7, .kv =  327 },
                                { .ro =  8, .kv =    0 },
                                { .ro =  9, .kv =    0 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =    0 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =    0 },
                                { .ro = 15, .kv =    0 } },
};


/*
 * MX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_20263054042 =
{
    .modesCount      = 8,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_32057870016,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1,
                                                    CPR_VOLTAGE_MODE_SUPER_TURBO_NO_CPR },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  680000, .floor =  504000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_6490927279, .quotients = &quotients_6504684466, .margins = &margins_320082,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  796000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_5490243851, .quotients = &quotients_5091104467, .margins = &margins_436082,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  824000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_4917894785, .quotients = &quotients_10301225351, .margins = &margins_436082,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_5121251345, .quotients = &quotients_15456002170, .margins = &margins_452082,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_5121251345, .quotients = &quotients_15456002170, .margins = &margins_452082,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // SUPER_TURBO_NO_CPR
        {.fref = 888000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  888000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_332082 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =       0, .closedLoop =   53000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 7, .openLoop =       0, .closedLoop =   53000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_fuse_data  fuses_9260316007 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW11_MSB, CPR5_TARG_VOLT_SVSL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW12_LSB, CPR5_TARG_VOLT_OFFSET_SVSL1_4_2), CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW11_MSB, CPR5_TARG_VOLT_OFFSET_SVSL1_1_0) } } },
};


static cpr_fuse_data  fuses_3642184457 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW11_MSB, CPR5_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW11_MSB, CPR5_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_432082 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =       0, .closedLoop =   58000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 7, .openLoop =       0, .closedLoop =   58000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_fuse_data  fuses_7106858240 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW11_MSB, CPR5_TARG_VOLT_NOML1_5_3), CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW11_LSB, CPR5_TARG_VOLT_NOML1_2_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW11_MSB, CPR5_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_margin_cfg margins_448082 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =       0, .closedLoop =   62000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 7, .openLoop =       0, .closedLoop =   62000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_fuse_data  fuses_3894182779 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW11_LSB, CPR5_TARG_VOLT_SUT) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW11_MSB, CPR5_TARG_VOLT_OFFSET_SUT) } } },
};


static cpr_kv_cfg  kvs_31938118327 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =  376 },
                                { .ro =  1, .kv =  350 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =    0 },
                                { .ro =  4, .kv =  287 },
                                { .ro =  5, .kv =  277 },
                                { .ro =  6, .kv =    0 },
                                { .ro =  7, .kv =  323 },
                                { .ro =  8, .kv =    0 },
                                { .ro =  9, .kv =    0 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =    0 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =    0 },
                                { .ro = 15, .kv =    0 } },
};


/*
 * MXC Voltage Plan
 */
static cpr_voltage_plan voltage_plan_19722146129 =
{
    .modesCount      = 8,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_31938118327,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1,
                                                    CPR_VOLTAGE_MODE_SUPER_TURBO_NO_CPR },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  680000, .floor =  504000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_9260316007, .quotients = &quotients_6504684466, .margins = &margins_332082,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  796000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_3642184457, .quotients = &quotients_5091104467, .margins = &margins_436082,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  824000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_7106858240, .quotients = &quotients_10301225351, .margins = &margins_432082,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_3894182779, .quotients = &quotients_15456002170, .margins = &margins_448082,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_3894182779, .quotients = &quotients_15456002170, .margins = &margins_448082,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // SUPER_TURBO_NO_CPR
        {.fref = 888000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  888000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_57960 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 } }
};


static cpr_fuse_data  fuses_752145195 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW12_LSB, CPR6_TARG_VOLT_SVSL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_fuse_data  fuses_3085591611 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW12_LSB, CPR6_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_fuse_data  fuses_3288672710 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW12_LSB, CPR6_TARG_VOLT_NOML1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_fuse_data  fuses_993091732 =
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
static cpr_voltage_plan voltage_plan_5077175115 =
{
    .modesCount      = 6,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  500000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_57960,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_752145195, .quotients = NULL, .margins = &margins_57960,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  792000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_3085591611, .quotients = NULL, .margins = &margins_57960,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  824000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_3288672710, .quotients = NULL, .margins = &margins_57960,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_993091732, .quotients = NULL, .margins = &margins_57960,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  800000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_191040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =    8000, .closedLoop =   73000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_9962588195 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  417 },
                                      { .ro =  3, .quotient =  464 },
                                      { .ro =  7, .quotient =  402 },
                                      { .ro =  8, .quotient =  246 },
                                      { .ro =  9, .quotient =  269 },
                                      { .ro = 15, .quotient =  317 } },
};


static cpr_fuse_data  fuses_2056079218 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW12_MSB, CPR7_TARG_VOLT_SVS3) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW13_LSB, CPR7_TARG_VOLT_OFFSET_SVS3) } } },
};


static cpr_margin_cfg margins_165040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =    8000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_13832946597 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  453 },
                                      { .ro =  3, .quotient =  504 },
                                      { .ro =  7, .quotient =  449 },
                                      { .ro =  8, .quotient =  279 },
                                      { .ro =  9, .quotient =  304 },
                                      { .ro = 15, .quotient =  356 } },
};


static cpr_fuse_data  fuses_10185389 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW13_LSB, CPR7_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_151040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   57000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_12175664698 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  614 },
                                      { .ro =  3, .quotient =  665 },
                                      { .ro =  7, .quotient =  636 },
                                      { .ro =  8, .quotient =  421 },
                                      { .ro =  9, .quotient =  454 },
                                      { .ro = 15, .quotient =  523 } },
};


static cpr_fuse_data  fuses_4177383747 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW12_MSB, CPR7_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW13_LSB, CPR7_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_155040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_16912600182 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  722 },
                                      { .ro =  3, .quotient =  773 },
                                      { .ro =  7, .quotient =  748 },
                                      { .ro =  8, .quotient =  519 },
                                      { .ro =  9, .quotient =  551 },
                                      { .ro = 15, .quotient =  628 } },
};


static cpr_fuse_data  fuses_3929267629 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW13_LSB, CPR7_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_201040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   62000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_12161578564 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  866 },
                                      { .ro =  3, .quotient =  926 },
                                      { .ro =  7, .quotient =  928 },
                                      { .ro =  8, .quotient =  655 },
                                      { .ro =  9, .quotient =  705 },
                                      { .ro = 15, .quotient =  784 } },
};


static cpr_fuse_data  fuses_5246178175 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW12_MSB, CPR7_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW13_LSB, CPR7_TARG_VOLT_OFFSET_NOM_4_3), CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW12_MSB, CPR7_TARG_VOLT_OFFSET_NOM_2_0) } } },
};


static cpr_margin_cfg margins_219040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =    8000, .closedLoop =   67000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_16367725253 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1018 },
                                      { .ro =  3, .quotient = 1087 },
                                      { .ro =  7, .quotient = 1095 },
                                      { .ro =  8, .quotient =  792 },
                                      { .ro =  9, .quotient =  849 },
                                      { .ro = 15, .quotient =  935 } },
};


static cpr_fuse_data  fuses_7781915863 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW12_MSB, CPR7_TARG_VOLT_TUR_5), CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW12_LSB, CPR7_TARG_VOLT_TUR_4_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW12_MSB, CPR7_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_kv_cfg  kvs_32128429238 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =  280 },
                                { .ro =  3, .kv =  281 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =    0 },
                                { .ro =  6, .kv =    0 },
                                { .ro =  7, .kv =  288 },
                                { .ro =  8, .kv =  264 },
                                { .ro =  9, .kv =  263 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =    0 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =    0 },
                                { .ro = 15, .kv =  287 } },
};


/*
 * LPI_CX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_12746351313 =
{
    .modesCount      = 7,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_32128429238,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  352000, .floor =  352000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS_D1
        {.fref = 540000, .freqDelta =       0, .fuses = &fuses_2056079218, .quotients = &quotients_9962588195, .margins = &margins_191040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  640000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 552000, .freqDelta =       0, .fuses = &fuses_10185389, .quotients = &quotients_13832946597, .margins = &margins_165040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  656000, .floor =  520000, .freq =       0, .interplEnabled = 19} } },

        // SVS
        {.fref = 624000, .freqDelta =       0, .fuses = &fuses_4177383747, .quotients = &quotients_12175664698, .margins = &margins_151040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  736000, .floor =  552000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 680000, .freqDelta =       0, .fuses = &fuses_3929267629, .quotients = &quotients_16912600182, .margins = &margins_155040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  792000, .floor =  600000, .freq =       0, .interplEnabled = 45} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_5246178175, .quotients = &quotients_12161578564, .margins = &margins_201040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  824000, .floor =  656000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_7781915863, .quotients = &quotients_16367725253, .margins = &margins_219040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  720000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_135040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   49000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_9219610957 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  7, .quotient =  449 },
                                      { .ro =  8, .quotient =  279 },
                                      { .ro = 10, .quotient =  160 },
                                      { .ro = 12, .quotient =  172 } },
};


static cpr_fuse_data  fuses_6014268725 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW13_MSB, CPR8_TARG_VOLT_SVS3) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW14_LSB, CPR8_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_quotient_cfg  quotients_8016040690 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  7, .quotient =  636 },
                                      { .ro =  8, .quotient =  421 },
                                      { .ro = 10, .quotient =  287 },
                                      { .ro = 12, .quotient =  304 } },
};


static cpr_fuse_data  fuses_5158711283 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW13_MSB, CPR8_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW14_LSB, CPR8_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_157040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_10328484250 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  7, .quotient =  748 },
                                      { .ro =  8, .quotient =  519 },
                                      { .ro = 10, .quotient =  375 },
                                      { .ro = 12, .quotient =  389 } },
};


static cpr_fuse_data  fuses_1944260130 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW14_LSB, CPR8_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_quotient_cfg  quotients_13283276118 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  866 },
                                      { .ro =  3, .quotient =  926 },
                                      { .ro =  7, .quotient =  928 },
                                      { .ro =  8, .quotient =  655 },
                                      { .ro = 10, .quotient =  516 },
                                      { .ro = 12, .quotient =  542 } },
};


static cpr_fuse_data  fuses_6608573654 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW13_MSB, CPR8_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW13_MSB, CPR8_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_quotient_cfg  quotients_16703158729 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1018 },
                                      { .ro =  3, .quotient = 1087 },
                                      { .ro =  7, .quotient = 1095 },
                                      { .ro =  8, .quotient =  792 },
                                      { .ro = 10, .quotient =  651 },
                                      { .ro = 12, .quotient =  680 } },
};


static cpr_fuse_data  fuses_7593822161 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW13_MSB, CPR8_TARG_VOLT_TUR_5_2), CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW13_LSB, CPR8_TARG_VOLT_TUR_1_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW13_MSB, CPR8_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_kv_cfg  kvs_37829991154 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =  257 },
                                { .ro =  3, .kv =  256 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =    0 },
                                { .ro =  6, .kv =    0 },
                                { .ro =  7, .kv =  287 },
                                { .ro =  8, .kv =  266 },
                                { .ro =  9, .kv =    0 },
                                { .ro = 10, .kv =  252 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =  250 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =    0 },
                                { .ro = 15, .kv =    0 } },
};


/*
 * MM Voltage Plan
 */
static cpr_voltage_plan voltage_plan_7030615631 =
{
    .modesCount      = 5,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_37829991154,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS
        {.fref = 556000, .freqDelta =       0, .fuses = &fuses_6014268725, .quotients = &quotients_9219610957, .margins = &margins_135040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  656000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_5158711283, .quotients = &quotients_8016040690, .margins = &margins_147040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  732000, .floor =  552000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_1944260130, .quotients = &quotients_10328484250, .margins = &margins_157040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  796000, .floor =  600000, .freq =       0, .interplEnabled = 45} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_6608573654, .quotients = &quotients_13283276118, .margins = &margins_201040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  824000, .floor =  656000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_7593822161, .quotients = &quotients_16703158729, .margins = &margins_211040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  716000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_2040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 } }
};


static cpr_margin_cfg margins_27960 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =  -30000, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 } }
};


/*
 * WMSS_CX_1 Voltage Plan
 */
static cpr_voltage_plan voltage_plan_5085917834 =
{
    .modesCount      = 3,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_NOMINAL },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS
        {.fref = 592000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  648000, .floor =  504000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 672000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  720000, .floor =  592000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_27960,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  864000, .floor =  712000, .freq =       0, .interplEnabled = 0} } }},
};


/*
 * WMSS_CX_2 Voltage Plan
 */
static cpr_voltage_plan voltage_plan_5310229551 =
{
    .modesCount      = 3,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_NOMINAL },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS
        {.fref = 588000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  588000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 668000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  728000, .floor =  596000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 744000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_2040,
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


static cpr_margin_cfg margins_350116 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 3, .openLoop =   20000, .closedLoop =   66000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 7, .openLoop =   12000, .closedLoop =   58000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_14051469277 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  364 },
                                      { .ro =  9, .quotient =  373 },
                                      { .ro = 10, .quotient =  220 },
                                      { .ro = 12, .quotient =  224 },
                                      { .ro = 15, .quotient =  452 } },
};


static cpr_margin_cfg margins_334116 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 3, .openLoop =   12000, .closedLoop =   63000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 7, .openLoop =    8000, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_8563304893 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  517 },
                                      { .ro =  9, .quotient =  525 },
                                      { .ro = 10, .quotient =  359 },
                                      { .ro = 12, .quotient =  356 },
                                      { .ro = 15, .quotient =  617 } },
};


static cpr_margin_cfg margins_292116 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 3, .openLoop =       0, .closedLoop =   55000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 7, .openLoop =       0, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_9542529216 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  611 },
                                      { .ro =  9, .quotient =  624 },
                                      { .ro = 10, .quotient =  449 },
                                      { .ro = 12, .quotient =  456 },
                                      { .ro = 15, .quotient =  722 } },
};


static cpr_margin_cfg margins_338116 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 3, .openLoop =   -8000, .closedLoop =   51000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 7, .openLoop =   -8000, .closedLoop =   51000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_11568573630 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  977 },
                                      { .ro =  8, .quotient =  766 },
                                      { .ro =  9, .quotient =  780 },
                                      { .ro = 10, .quotient =  599 },
                                      { .ro = 12, .quotient =  606 } },
};


static cpr_margin_cfg margins_458116 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 3, .openLoop =       0, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 7, .openLoop =   24000, .closedLoop =   83000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_fuse_data  fuses_4333982597 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW7_LSB, CPR0_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW6_MSB, CPR0_TARG_VOLT_OFFSET_NOML0) } } },
};


static cpr_margin_cfg margins_626116 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 3, .openLoop =    8000, .closedLoop =  107000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 7, .openLoop =   40000, .closedLoop =  107000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_13576567397 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1087 },
                                      { .ro =  8, .quotient =  866 },
                                      { .ro =  9, .quotient =  881 },
                                      { .ro = 10, .quotient =  697 },
                                      { .ro = 12, .quotient =  708 } },
};


static cpr_margin_cfg margins_514116 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 3, .openLoop =    4000, .closedLoop =  105000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 7, .openLoop =    4000, .closedLoop =   73000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_12424175344 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1161 },
                                      { .ro =  8, .quotient =  933 },
                                      { .ro =  9, .quotient =  948 },
                                      { .ro = 10, .quotient =  762 },
                                      { .ro = 12, .quotient =  775 } },
};


static cpr_margin_cfg margins_670116 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 3, .openLoop =   16000, .closedLoop =  117000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 7, .openLoop =   44000, .closedLoop =  113000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_fuse_data  fuses_2573036577 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW6_MSB, CPR0_TARG_VOLT_OFFSET_TURL0) } } },
};


static cpr_margin_cfg margins_324116 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 3, .openLoop =  -32000, .closedLoop =   83000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 7, .openLoop =  -40000, .closedLoop =   40000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_5409333330 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1289 },
                                      { .ro =  8, .quotient = 1089 },
                                      { .ro =  9, .quotient = 1106 },
                                      { .ro = 10, .quotient =  914 },
                                      { .ro = 12, .quotient =  932 } },
};


static cpr_margin_cfg margins_554116 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 3, .openLoop =   -8000, .closedLoop =  107000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 7, .openLoop =   16000, .closedLoop =   91000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_fuse_data  fuses_7121817623 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW7_LSB, CPR0_TARG_VOLT_SUT) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW6_MSB, CPR0_TARG_VOLT_OFFSET_TURL2) } } },
};


static cpr_kv_cfg  kvs_36999093172 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =  237 },
                                { .ro =  3, .kv =    0 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =    0 },
                                { .ro =  6, .kv =    0 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =  271 },
                                { .ro =  9, .kv =  269 },
                                { .ro = 10, .kv =  248 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =  247 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =    0 },
                                { .ro = 15, .kv =  281 } },
};


/*
 * CX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_30214000242 =
{
    .modesCount      = 12,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_36999093172,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L0,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L0,
                                                    CPR_VOLTAGE_MODE_TURBO_L1,
                                                    CPR_VOLTAGE_MODE_TURBO_L2,
                                                    CPR_VOLTAGE_MODE_SUPER_TURBO_NO_CPR },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  352000, .floor =  352000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 584000, .freqDelta =       0, .fuses = &fuses_3255791880, .quotients = &quotients_14051469277, .margins = &margins_350116,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  684000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 656000, .freqDelta =       0, .fuses = &fuses_6795546843, .quotients = &quotients_8563304893, .margins = &margins_334116,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  760000, .floor =  576000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 712000, .freqDelta =       0, .fuses = &fuses_3464103763, .quotients = &quotients_9542529216, .margins = &margins_292116,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  624000, .freq =       0, .interplEnabled = 43} } },

        // NOMINAL
        {.fref = 784000, .freqDelta =       0, .fuses = &fuses_5674476035, .quotients = &quotients_11568573630, .margins = &margins_338116,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  868000, .floor =  676000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L0
        {.fref = 784000, .freqDelta =       0, .fuses = &fuses_4333982597, .quotients = &quotients_11568573630, .margins = &margins_458116,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  868000, .floor =  676000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_1513134881, .quotients = &quotients_13576567397, .margins = &margins_626116,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  940000, .floor =  716000, .freq =       0, .interplEnabled = 31} } },

        // TURBO
        {.fref = 868000, .freqDelta =       0, .fuses = &fuses_5741285492, .quotients = &quotients_12424175344, .margins = &margins_514116,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  976000, .floor =  740000, .freq =       0, .interplEnabled = 52} } },

        // TURBO_L0
        {.fref = 868000, .freqDelta =       0, .fuses = &fuses_2573036577, .quotients = &quotients_12424175344, .margins = &margins_670116,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  976000, .floor =  740000, .freq =       0, .interplEnabled = 52} } },

        // TURBO_L1
        {.fref = 944000, .freqDelta =       0, .fuses = &fuses_3434864866, .quotients = &quotients_5409333330, .margins = &margins_324116,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling = 1032000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L2
        {.fref = 944000, .freqDelta =       0, .fuses = &fuses_7121817623, .quotients = &quotients_5409333330, .margins = &margins_554116,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling = 1032000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // SUPER_TURBO_NO_CPR
        {.fref = 1032000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling = 1032000, .floor = 1032000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_version  ver_ANY_2_0_2_255 = { .foundry = CPR_FOUNDRY_ANY, .min = CPR_CHIPINFO_VERSION(2,0), .max = CPR_CHIPINFO_VERSION(2,255) };


static cpr_margin_cfg margins_392065 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   24000, .closedLoop =   66000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 1, .cprRevMax = 7, .openLoop =   32000, .closedLoop =   82000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_3452375071 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  279 } },
};


static cpr_fuse_data  fuses_10643722119 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW9_MSB, CPR2_TARG_VOLT_SVS3_5_2), CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW9_LSB, CPR2_TARG_VOLT_SVS3_1_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW10_LSB, CPR2_TARG_VOLT_OFFSET_SVS3) } } },
};


static cpr_margin_cfg margins_390065 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   24000, .closedLoop =   66000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 1, .cprRevMax = 7, .openLoop =   32000, .closedLoop =   81000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_227345446 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  312 } },
};


static cpr_fuse_data  fuses_1269891408 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW10_LSB, CPR2_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_326065 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 0, .openLoop =    8000, .closedLoop =   52000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 1, .cprRevMax = 7, .openLoop =   24000, .closedLoop =   75000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_2844648776 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  460 } },
};


static cpr_margin_cfg margins_448065 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   24000, .closedLoop =   68000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 1, .cprRevMax = 7, .openLoop =   36000, .closedLoop =   91000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_400065 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   16000, .closedLoop =   69000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 1, .cprRevMax = 7, .openLoop =   24000, .closedLoop =   76000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_2204294332 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  550 } },
};


static cpr_margin_cfg margins_440065 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   24000, .closedLoop =   77000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 1, .cprRevMax = 7, .openLoop =   24000, .closedLoop =   84000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_450065 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   24000, .closedLoop =   81000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 1, .cprRevMax = 7, .openLoop =   24000, .closedLoop =   85000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_2240753156 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  609 } },
};


static cpr_margin_cfg margins_674065 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   48000, .closedLoop =  104000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 1, .cprRevMax = 7, .openLoop =   48000, .closedLoop =  110000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_1519787391 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  691 } },
};


static cpr_margin_cfg margins_700065 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   56000, .closedLoop =  111000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 1, .cprRevMax = 7, .openLoop =   48000, .closedLoop =  112000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_2889951013 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  783 } },
};


static cpr_margin_cfg margins_688065 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   56000, .closedLoop =  114000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 1, .cprRevMax = 7, .openLoop =   40000, .closedLoop =  107000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_2513222327 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  844 } },
};


static cpr_margin_cfg margins_704065 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   72000, .closedLoop =  128000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 1, .cprRevMax = 7, .openLoop =   24000, .closedLoop =  101000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_1361961583 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  976 } },
};


/*
 * GFX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_16726372957 =
{
    .modesCount      = 11,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_34125314129,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_L1,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L0,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_SVS_L2,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1 },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS_D1
        {.fref = 540000, .freqDelta =       0, .fuses = &fuses_10643722119, .quotients = &quotients_3452375071, .margins = &margins_392065,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  640000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 556000, .freqDelta =       0, .fuses = &fuses_1269891408, .quotients = &quotients_227345446, .margins = &margins_390065,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  656000, .floor =  516000, .freq =       0, .interplEnabled = 12} } },

        // LOW_SVS_L1
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_2416996329, .quotients = &quotients_2844648776, .margins = &margins_326065,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  716000, .floor =  536000, .freq =       0, .interplEnabled = 62} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_2416996329, .quotients = &quotients_2844648776, .margins = &margins_448065,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  732000, .floor =  552000, .freq =       0, .interplEnabled = 62} } },

        // SVS_L0
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_7364190841, .quotients = &quotients_2204294332, .margins = &margins_400065,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  788000, .floor =  592000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_7364190841, .quotients = &quotients_2204294332, .margins = &margins_440065,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  796000, .floor =  600000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L2
        {.fref = 712000, .freqDelta =       0, .fuses = &fuses_3215405778, .quotients = &quotients_2240753156, .margins = &margins_450065,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  828000, .floor =  624000, .freq =       0, .interplEnabled = 42} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_2947686763, .quotients = &quotients_1519787391, .margins = &margins_674065,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  868000, .floor =  656000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_4710604682, .quotients = &quotients_2889951013, .margins = &margins_700065,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  912000, .floor =  696000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_2675281751, .quotients = &quotients_2513222327, .margins = &margins_688065,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  928000, .floor =  716000, .freq =       0, .interplEnabled = 32} } },

        // TURBO_L1
        {.fref = 904000, .freqDelta =       0, .fuses = &fuses_7189446118, .quotients = &quotients_1361961583, .margins = &margins_704065,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  968000, .floor =  768000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_784202 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 0, .openLoop =  120000, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 1, .cprRevMax = 3, .openLoop =   12000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   12000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 7, .openLoop =   12000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_9160277692 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  275 },
                                      { .ro =  9, .quotient =  286 },
                                      { .ro = 10, .quotient =  150 },
                                      { .ro = 14, .quotient =  279 } },
};


static cpr_margin_cfg margins_864202 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 0, .openLoop =  100000, .closedLoop =   69000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 1, .cprRevMax = 3, .openLoop =   20000, .closedLoop =   67000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   20000, .closedLoop =   67000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 7, .openLoop =   28000, .closedLoop =   75000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_7101552781 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  305 },
                                      { .ro =  9, .quotient =  312 },
                                      { .ro = 10, .quotient =  169 },
                                      { .ro = 14, .quotient =  312 } },
};


static cpr_margin_cfg margins_794202 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   80000, .closedLoop =   58000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 1, .cprRevMax = 3, .openLoop =    4000, .closedLoop =   75000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   12000, .closedLoop =   67000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 7, .openLoop =   16000, .closedLoop =   71000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
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


static cpr_margin_cfg margins_934202 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   40000, .closedLoop =   67000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 1, .cprRevMax = 3, .openLoop =   20000, .closedLoop =   96000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   28000, .closedLoop =   88000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 7, .openLoop =   28000, .closedLoop =   88000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
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


static cpr_margin_cfg margins_1196202 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   28000, .closedLoop =   88000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 1, .cprRevMax = 3, .openLoop =   24000, .closedLoop =  102000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   32000, .closedLoop =   94000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 7, .openLoop =   40000, .closedLoop =  102000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
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


static cpr_margin_cfg margins_1530202 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   56000, .closedLoop =  115000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 1, .cprRevMax = 3, .openLoop =   44000, .closedLoop =  138000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   60000, .closedLoop =  122000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 7, .openLoop =   64000, .closedLoop =  128000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
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


static cpr_margin_cfg margins_1446202 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 0, .openLoop =   20000, .closedLoop =   82000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 1, .cprRevMax = 3, .openLoop =   44000, .closedLoop =  141000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   60000, .closedLoop =  125000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 7, .openLoop =   64000, .closedLoop =  131000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_8498876739 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1070 },
                                      { .ro =  3, .quotient = 1086 },
                                      { .ro =  8, .quotient =  836 },
                                      { .ro =  9, .quotient =  850 },
                                      { .ro = 14, .quotient =  844 } },
};


static cpr_kv_cfg  kvs_36360964041 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =  268 },
                                { .ro =  3, .kv =  268 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =    0 },
                                { .ro =  6, .kv =    0 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =  263 },
                                { .ro =  9, .kv =  261 },
                                { .ro = 10, .kv =  200 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =    0 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  269 },
                                { .ro = 15, .kv =    0 } },
};


/*
 * MSS Voltage Plan
 */
static cpr_voltage_plan voltage_plan_19212093443 =
{
    .modesCount      = 7,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_36360964041,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS_D1
        {.fref = 540000, .freqDelta =       0, .fuses = &fuses_7235493532, .quotients = &quotients_9160277692, .margins = &margins_784202,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  680000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 556000, .freqDelta =       0, .fuses = &fuses_238806686, .quotients = &quotients_7101552781, .margins = &margins_864202,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  680000, .floor =  516000, .freq =       0, .interplEnabled = 19} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_6400365702, .quotients = &quotients_13594457200, .margins = &margins_794202,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  732000, .floor =  552000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_3499167844, .quotients = &quotients_10357983203, .margins = &margins_934202,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  796000, .floor =  600000, .freq =       0, .interplEnabled = 45} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_4191318810, .quotients = &quotients_8682795327, .margins = &margins_1196202,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  840000, .floor =  656000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_2986368825, .quotients = &quotients_7768896922, .margins = &margins_1530202,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  696000, .freq =       0, .interplEnabled = 60} } },

        // TURBO
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_6027291304, .quotients = &quotients_8498876739, .margins = &margins_1446202,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  932000, .floor =  716000, .freq =       0, .interplEnabled = 0} } }},
};


/*
 * VDDA Voltage Plan
 */
static cpr_voltage_plan voltage_plan_22605401505 =
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
        {.fref = 700000, .freqDelta =       0, .fuses = &fuses_424139257, .quotients = NULL, .margins = &margins_97960,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  800000, .floor =  700000, .freq =       0, .interplEnabled = 0} } },

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
        {.fref = 892000, .freqDelta =       0, .fuses = &fuses_2714839418, .quotients = NULL, .margins = &margins_97960,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  952000, .floor =  892000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =       0, .floor =       0, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_182040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   60000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_fuse_data  fuses_539020497 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW12_MSB, CPR7_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_quotient_cfg  quotients_9525308185 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  0, .quotient =  755 },
                                      { .ro =  1, .quotient =  928 },
                                      { .ro =  4, .quotient =  526 },
                                      { .ro =  5, .quotient =  666 },
                                      { .ro =  7, .quotient =  768 } },
};


static cpr_margin_cfg margins_226040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   62000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_11185200723 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  0, .quotient =  893 },
                                      { .ro =  1, .quotient = 1097 },
                                      { .ro =  4, .quotient =  630 },
                                      { .ro =  5, .quotient =  793 },
                                      { .ro =  7, .quotient =  920 } },
};


static cpr_margin_cfg margins_230040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   64000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_13256362721 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  0, .quotient = 1050 },
                                      { .ro =  1, .quotient = 1251 },
                                      { .ro =  4, .quotient =  750 },
                                      { .ro =  5, .quotient =  915 },
                                      { .ro =  7, .quotient = 1065 } },
};


static cpr_margin_cfg margins_236040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   67000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_13373089957 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  0, .quotient = 1151 },
                                      { .ro =  1, .quotient = 1350 },
                                      { .ro =  4, .quotient =  829 },
                                      { .ro =  5, .quotient =  995 },
                                      { .ro =  7, .quotient = 1160 } },
};


/*
 * MX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_18285098620 =
{
    .modesCount      = 8,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_32057870016,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1,
                                                    CPR_VOLTAGE_MODE_SUPER_TURBO_NO_CPR },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  568000, .floor =  540000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_539020497, .quotients = NULL, .margins = &margins_182040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  796000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_6490927279, .quotients = &quotients_9525308185, .margins = &margins_182040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  796000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_5490243851, .quotients = &quotients_11185200723, .margins = &margins_226040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  824000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_4917894785, .quotients = &quotients_13256362721, .margins = &margins_230040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_5121251345, .quotients = &quotients_13373089957, .margins = &margins_236040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_5121251345, .quotients = &quotients_13373089957, .margins = &margins_236040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // SUPER_TURBO_NO_CPR
        {.fref = 888000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  888000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_fuse_data  fuses_1685321579 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIBRATION_ROW14_LSB, CPR8_TARG_VOLT_OFFSET_SVS3) } } },
};


/*
 * MXC Voltage Plan
 */
static cpr_voltage_plan voltage_plan_13952638652 =
{
    .modesCount      = 8,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_31938118327,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1,
                                                    CPR_VOLTAGE_MODE_SUPER_TURBO_NO_CPR },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  568000, .floor =  540000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_1685321579, .quotients = NULL, .margins = &margins_182040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  796000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_9260316007, .quotients = &quotients_9525308185, .margins = &margins_182040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  796000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_3642184457, .quotients = &quotients_11185200723, .margins = &margins_226040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  824000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_7106858240, .quotients = &quotients_13256362721, .margins = &margins_230040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_3894182779, .quotients = &quotients_13373089957, .margins = &margins_236040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_3894182779, .quotients = &quotients_13373089957, .margins = &margins_236040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // SUPER_TURBO_NO_CPR
        {.fref = 888000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  888000, .freq =       0, .interplEnabled = 0} } }},
};


/*
 * LPI_MX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_4508715460 =
{
    .modesCount      = 6,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  568000, .floor =  536000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_57960,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_752145195, .quotients = NULL, .margins = &margins_57960,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  792000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_3085591611, .quotients = NULL, .margins = &margins_57960,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  824000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_3288672710, .quotients = NULL, .margins = &margins_57960,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_993091732, .quotients = NULL, .margins = &margins_57960,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  800000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_145040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =    4000, .closedLoop =   52000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_14764207919 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  441 },
                                      { .ro =  3, .quotient =  466 },
                                      { .ro =  8, .quotient =  275 },
                                      { .ro =  9, .quotient =  286 },
                                      { .ro = 14, .quotient =  279 } },
};


static cpr_margin_cfg margins_147041 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =    4000, .closedLoop =   53000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_10305704784 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  479 },
                                      { .ro =  3, .quotient =  503 },
                                      { .ro =  8, .quotient =  305 },
                                      { .ro =  9, .quotient =  312 },
                                      { .ro = 14, .quotient =  312 } },
};


static cpr_margin_cfg margins_123040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   -8000, .closedLoop =   47000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_14864565190 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  644 },
                                      { .ro =  3, .quotient =  665 },
                                      { .ro =  8, .quotient =  454 },
                                      { .ro =  9, .quotient =  462 },
                                      { .ro = 14, .quotient =  460 },
                                      { .ro = 15, .quotient =  555 } },
};


static cpr_quotient_cfg  quotients_11598641394 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  754 },
                                      { .ro =  3, .quotient =  772 },
                                      { .ro =  8, .quotient =  553 },
                                      { .ro =  9, .quotient =  564 },
                                      { .ro = 14, .quotient =  550 },
                                      { .ro = 15, .quotient =  655 } },
};


static cpr_margin_cfg margins_185040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   54000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_10025442006 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  901 },
                                      { .ro =  3, .quotient =  925 },
                                      { .ro =  8, .quotient =  695 },
                                      { .ro =  9, .quotient =  709 },
                                      { .ro = 14, .quotient =  691 },
                                      { .ro = 15, .quotient =  814 } },
};


static cpr_quotient_cfg  quotients_12532555177 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1070 },
                                      { .ro =  3, .quotient = 1086 },
                                      { .ro =  8, .quotient =  836 },
                                      { .ro =  9, .quotient =  850 },
                                      { .ro = 14, .quotient =  844 },
                                      { .ro = 15, .quotient =  981 } },
};


static cpr_kv_cfg  kvs_34852141409 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =  280 },
                                { .ro =  3, .kv =  281 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =    0 },
                                { .ro =  6, .kv =    0 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =  264 },
                                { .ro =  9, .kv =  263 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =    0 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  272 },
                                { .ro = 15, .kv =  278 } },
};


/*
 * LPI_CX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_11754071848 =
{
    .modesCount      = 7,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_34852141409,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  352000, .floor =  352000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS_D1
        {.fref = 540000, .freqDelta =       0, .fuses = &fuses_2056079218, .quotients = &quotients_14764207919, .margins = &margins_145040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  640000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 552000, .freqDelta =       0, .fuses = &fuses_10185389, .quotients = &quotients_10305704784, .margins = &margins_147041,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  656000, .floor =  520000, .freq =       0, .interplEnabled = 19} } },

        // SVS
        {.fref = 624000, .freqDelta =       0, .fuses = &fuses_4177383747, .quotients = &quotients_14864565190, .margins = &margins_123040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  736000, .floor =  552000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 680000, .freqDelta =       0, .fuses = &fuses_3929267629, .quotients = &quotients_11598641394, .margins = &margins_155040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  792000, .floor =  600000, .freq =       0, .interplEnabled = 45} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_5246178175, .quotients = &quotients_10025442006, .margins = &margins_185040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  824000, .floor =  656000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_7781915863, .quotients = &quotients_12532555177, .margins = &margins_195040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  720000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_139040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =    4000, .closedLoop =   49000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_9229197076 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  305 },
                                      { .ro = 10, .quotient =  169 },
                                      { .ro = 12, .quotient =  172 },
                                      { .ro = 15, .quotient =  390 } },
};


static cpr_margin_cfg margins_153040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =    4000, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_9178302566 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  454 },
                                      { .ro = 10, .quotient =  299 },
                                      { .ro = 12, .quotient =  303 },
                                      { .ro = 15, .quotient =  555 } },
};


static cpr_margin_cfg margins_185041 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =    8000, .closedLoop =   70000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_6574141983 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  553 },
                                      { .ro = 10, .quotient =  394 },
                                      { .ro = 12, .quotient =  389 },
                                      { .ro = 15, .quotient =  655 } },
};


static cpr_margin_cfg margins_223040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =    4000, .closedLoop =   71000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_13160302242 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  901 },
                                      { .ro =  3, .quotient =  925 },
                                      { .ro =  8, .quotient =  695 },
                                      { .ro = 10, .quotient =  530 },
                                      { .ro = 12, .quotient =  541 },
                                      { .ro = 15, .quotient =  814 } },
};


static cpr_quotient_cfg  quotients_17128542174 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1070 },
                                      { .ro =  3, .quotient = 1086 },
                                      { .ro =  8, .quotient =  836 },
                                      { .ro = 10, .quotient =  667 },
                                      { .ro = 12, .quotient =  679 },
                                      { .ro = 15, .quotient =  981 } },
};


static cpr_kv_cfg  kvs_39347674303 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =  257 },
                                { .ro =  3, .kv =  256 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =    0 },
                                { .ro =  6, .kv =    0 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =  266 },
                                { .ro =  9, .kv =    0 },
                                { .ro = 10, .kv =  252 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =  250 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =    0 },
                                { .ro = 15, .kv =  288 } },
};


/*
 * MM Voltage Plan
 */
static cpr_voltage_plan voltage_plan_14382448822 =
{
    .modesCount      = 5,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_39347674303,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS
        {.fref = 556000, .freqDelta =       0, .fuses = &fuses_6014268725, .quotients = &quotients_9229197076, .margins = &margins_139040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  656000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_5158711283, .quotients = &quotients_9178302566, .margins = &margins_153040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  732000, .floor =  552000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_1944260130, .quotients = &quotients_6574141983, .margins = &margins_185041,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  796000, .floor =  600000, .freq =       0, .interplEnabled = 45} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_6608573654, .quotients = &quotients_13160302242, .margins = &margins_223040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  824000, .floor =  656000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_7593822161, .quotients = &quotients_17128542174, .margins = &margins_211040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  716000, .freq =       0, .interplEnabled = 0} } }},
};


/*
 * Aging configs
 */

static cpr_aging_cfg  aging_cfg_cx =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO_L1,
    .sensorID             = 13,
    .kv                   = 83,
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
    .kv                   = 88,
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
    .kv                   = 95,
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
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO_L1,
    .sensorID             = 11,
    .kv                   = 95,
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
    .kv                   = 102,
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
    .kv                   = 95,
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
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_21371602810 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_30214000242 },
     },
    .count    = 2,
    .agingCfg = &aging_cfg_cx
};


static cpr_versioned_voltage_plan gfx_vvp = {
    .rail     = CPR_RAIL_GFX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_25044200157 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_16726372957 },
     },
    .count    = 2,
    .agingCfg = &aging_cfg_gfx
};


static cpr_versioned_voltage_plan mss_vvp = {
    .rail     = CPR_RAIL_MSS,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_11888173162 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_19212093443 },
     },
    .count    = 2,
    .agingCfg = &aging_cfg_mss
};


static cpr_versioned_voltage_plan vdda_vvp = {
    .rail     = CPR_RAIL_VDDA,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_23338820795 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_22605401505 },
     },
    .count    = 2,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan mx_vvp = {
    .rail     = CPR_RAIL_MX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_20263054042 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_18285098620 },
     },
    .count    = 2,
    .agingCfg = &aging_cfg_mx
};


static cpr_versioned_voltage_plan mxc_vvp = {
    .rail     = CPR_RAIL_MXC,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_19722146129 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_13952638652 },
     },
    .count    = 2,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan lpi_mx_vvp = {
    .rail     = CPR_RAIL_LPI_MX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_5077175115 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_4508715460 },
     },
    .count    = 2,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan lpi_cx_vvp = {
    .rail     = CPR_RAIL_LPI_CX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_12746351313 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_11754071848 },
     },
    .count    = 2,
    .agingCfg = &aging_cfg_lpi_cx
};


static cpr_versioned_voltage_plan mm_vvp = {
    .rail     = CPR_RAIL_MM,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_7030615631 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_14382448822 },
     },
    .count    = 2,
    .agingCfg = &aging_cfg_mm
};


static cpr_versioned_voltage_plan wmss_cx_1_vvp = {
    .rail     = CPR_RAIL_WMSS_CX_1,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_5085917834 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_5085917834 },
     },
    .count    = 2,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan wmss_cx_2_vvp = {
    .rail     = CPR_RAIL_WMSS_CX_2,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_5310229551 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_5310229551 },
     },
    .count    = 2,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan wmss_cx_3_vvp = {
    .rail     = CPR_RAIL_WMSS_CX_3,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_5085917834 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_5085917834 },
     },
    .count    = 2,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan nav_ldo_vvp = {
    .rail     = CPR_RAIL_NAV_LDO,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_3863315186 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_3863315186 },
     },
    .count    = 2,
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
    .stepQuotMin         = 8,
    .stepQuotMax         = 19,
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
    .stepQuotMin         = 8,
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
    .stepQuotMin         = 8,
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
    .stepQuotMin         = 7,
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
    .stepQuotMin         = 7,
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
    .railCPRRevFuse    = {.count = 2, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2930 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {QFPROM_CORR_REG_BASE | (0x221C292C & (QFPROM_CORR_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_cx_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_CX,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_SW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 3, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {QFPROM_CORR_REG_BASE | (0x221C2930 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {QFPROM_CORR_REG_BASE | (0x221C292C & (QFPROM_CORR_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_gfx_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_GFX,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_HW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 3, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {QFPROM_CORR_REG_BASE | (0x221C2930 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {QFPROM_CORR_REG_BASE | (0x221C292C & (QFPROM_CORR_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_gfx_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_GFX,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_HW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 3, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {QFPROM_CORR_REG_BASE | (0x221C2930 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {QFPROM_CORR_REG_BASE | (0x221C292C & (QFPROM_CORR_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
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
                   {QFPROM_CORR_REG_BASE | (0x221C2930 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {QFPROM_CORR_REG_BASE | (0x221C292C & (QFPROM_CORR_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_lpi_cx_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_LPI_CX,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_SW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 3, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {QFPROM_CORR_REG_BASE | (0x221C2930 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {QFPROM_CORR_REG_BASE | (0x221C292C & (QFPROM_CORR_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
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
                   {QFPROM_CORR_REG_BASE | (0x221C2930 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {QFPROM_CORR_REG_BASE | (0x221C292C & (QFPROM_CORR_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_lpi_mx_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_LPI_MX,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_OPEN_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 3, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {QFPROM_CORR_REG_BASE | (0x221C2930 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {QFPROM_CORR_REG_BASE | (0x221C292C & (QFPROM_CORR_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_mm_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_MM,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_HW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 3, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {QFPROM_CORR_REG_BASE | (0x221C2930 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {QFPROM_CORR_REG_BASE | (0x221C292C & (QFPROM_CORR_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_mm_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_MM,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_HW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 3, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {QFPROM_CORR_REG_BASE | (0x221C2930 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {QFPROM_CORR_REG_BASE | (0x221C292C & (QFPROM_CORR_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_mss_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_MSS,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_HW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 3, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {QFPROM_CORR_REG_BASE | (0x221C2930 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {QFPROM_CORR_REG_BASE | (0x221C292C & (QFPROM_CORR_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_mss_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_MSS,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_HW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 3, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {QFPROM_CORR_REG_BASE | (0x221C2930 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {QFPROM_CORR_REG_BASE | (0x221C292C & (QFPROM_CORR_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
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
                   {QFPROM_CORR_REG_BASE | (0x221C2930 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {QFPROM_CORR_REG_BASE | (0x221C292C & (QFPROM_CORR_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_mx_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_MX,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_SW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 3, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {QFPROM_CORR_REG_BASE | (0x221C2930 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {QFPROM_CORR_REG_BASE | (0x221C292C & (QFPROM_CORR_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
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
                   {QFPROM_CORR_REG_BASE | (0x221C2930 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {QFPROM_CORR_REG_BASE | (0x221C292C & (QFPROM_CORR_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_mxc_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_MXC,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_SW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 3, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {QFPROM_CORR_REG_BASE | (0x221C2930 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {QFPROM_CORR_REG_BASE | (0x221C292C & (QFPROM_CORR_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_nav_ldo_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_NAV_LDO,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_NONE,
    .fuseMultiplier    = 8000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 3, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {QFPROM_CORR_REG_BASE | (0x221C2930 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {QFPROM_CORR_REG_BASE | (0x221C292C & (QFPROM_CORR_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_nav_ldo_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_NAV_LDO,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_NONE,
    .fuseMultiplier    = 8000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 3, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {QFPROM_CORR_REG_BASE | (0x221C2930 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {QFPROM_CORR_REG_BASE | (0x221C292C & (QFPROM_CORR_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
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
                   {QFPROM_CORR_REG_BASE | (0x221C2930 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {QFPROM_CORR_REG_BASE | (0x221C292C & (QFPROM_CORR_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_vdda_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_VDDA,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_OPEN_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 3, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {QFPROM_CORR_REG_BASE | (0x221C2930 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {QFPROM_CORR_REG_BASE | (0x221C292C & (QFPROM_CORR_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_wmss_cx_1_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_WMSS_CX_1,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_NONE,
    .fuseMultiplier    = 10000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 3, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {QFPROM_CORR_REG_BASE | (0x221C2930 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {QFPROM_CORR_REG_BASE | (0x221C292C & (QFPROM_CORR_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_wmss_cx_1_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_WMSS_CX_1,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_NONE,
    .fuseMultiplier    = 10000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 3, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {QFPROM_CORR_REG_BASE | (0x221C2930 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {QFPROM_CORR_REG_BASE | (0x221C292C & (QFPROM_CORR_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_wmss_cx_2_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_WMSS_CX_2,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_NONE,
    .fuseMultiplier    = 10000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 3, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {QFPROM_CORR_REG_BASE | (0x221C2930 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {QFPROM_CORR_REG_BASE | (0x221C292C & (QFPROM_CORR_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_wmss_cx_2_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_WMSS_CX_2,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_NONE,
    .fuseMultiplier    = 10000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 3, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {QFPROM_CORR_REG_BASE | (0x221C2930 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {QFPROM_CORR_REG_BASE | (0x221C292C & (QFPROM_CORR_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_wmss_cx_3_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_WMSS_CX_3,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_NONE,
    .fuseMultiplier    = 10000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 3, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {QFPROM_CORR_REG_BASE | (0x221C2930 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {QFPROM_CORR_REG_BASE | (0x221C292C & (QFPROM_CORR_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_wmss_cx_3_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_WMSS_CX_3,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_NONE,
    .fuseMultiplier    = 10000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 3, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2934 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {QFPROM_CORR_REG_BASE | (0x221C2930 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {QFPROM_CORR_REG_BASE | (0x221C292C & (QFPROM_CORR_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 0,
};


static cpr_misc_cfg misc_cfg = {
    .cprRev = {.count = 1, .data = (struct raw_fuse_data[]) { {QFPROM_CORR_REG_BASE | (0x221C2930 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)} } }
};


cpr_settings cpr_settings_waipio =
{
    .hashValue        = voltage_plan_hash_value,

    .railVVPs         = (cpr_versioned_voltage_plan*[]) { &cx_vvp, &gfx_vvp, &lpi_cx_vvp, &lpi_mx_vvp, &mm_vvp, &mss_vvp, &mx_vvp, &mxc_vvp, &nav_ldo_vvp, &vdda_vvp, &wmss_cx_1_vvp, &wmss_cx_2_vvp, &wmss_cx_3_vvp },
    .rails            = (cpr_rail*[]) { &cpr_rail_cx_cfg, &cpr_rail_gfx_cfg, &cpr_rail_lpi_cx_cfg, &cpr_rail_lpi_mx_cfg, &cpr_rail_mm_cfg, &cpr_rail_mss_cfg, &cpr_rail_mx_cfg, &cpr_rail_mxc_cfg, &cpr_rail_nav_ldo_cfg, &cpr_rail_vdda_cfg, &cpr_rail_wmss_cx_1_cfg, &cpr_rail_wmss_cx_2_cfg, &cpr_rail_wmss_cx_3_cfg },
    .railsCount       = 13,

    .controllers      = (cpr_hal_controller*[]) { &cpr3_controller, &cx_cpr3_controller, &gpu_cpr_controller, &lpass_cpr3_controller, &mmcx_cpr3_controller, &mx_cpr3_controller, &mxc_cpr3_controller },
    .controllersCount = 7,

    .enablements      = (cpr_enablement*[]) { &cpr_rail_cx_enablement_1_0_1_255, &cpr_rail_cx_enablement_2_0_2_255, &cpr_rail_gfx_enablement_1_0_1_255, &cpr_rail_gfx_enablement_2_0_2_255, &cpr_rail_lpi_cx_enablement_1_0_1_255, &cpr_rail_lpi_cx_enablement_2_0_2_255, &cpr_rail_lpi_mx_enablement_1_0_1_255, &cpr_rail_lpi_mx_enablement_2_0_2_255, &cpr_rail_mm_enablement_1_0_1_255, &cpr_rail_mm_enablement_2_0_2_255, &cpr_rail_mss_enablement_1_0_1_255, &cpr_rail_mss_enablement_2_0_2_255, &cpr_rail_mx_enablement_1_0_1_255, &cpr_rail_mx_enablement_2_0_2_255, &cpr_rail_mxc_enablement_1_0_1_255, &cpr_rail_mxc_enablement_2_0_2_255, &cpr_rail_nav_ldo_enablement_1_0_1_255, &cpr_rail_nav_ldo_enablement_2_0_2_255, &cpr_rail_vdda_enablement_1_0_1_255, &cpr_rail_vdda_enablement_2_0_2_255, &cpr_rail_wmss_cx_1_enablement_1_0_1_255, &cpr_rail_wmss_cx_1_enablement_2_0_2_255, &cpr_rail_wmss_cx_2_enablement_1_0_1_255, &cpr_rail_wmss_cx_2_enablement_2_0_2_255, &cpr_rail_wmss_cx_3_enablement_1_0_1_255, &cpr_rail_wmss_cx_3_enablement_2_0_2_255 },
    .enablementsCount = 26,

    .miscCfg          = &misc_cfg,
};

