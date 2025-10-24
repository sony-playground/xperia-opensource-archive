/*******************************************************************************
 *
 * Copyright (c) 2024 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 * THIS IS AUTO-GENERATED CPR CONFIG FILE FOR kailua.
 *
 * DateTime: 2024/01/22 00:13:16
 *
 *******************************************************************************/
#include "cpr_data.h"
#include "cpr_image_target_init.h"
#include "cpr_target_hwio.h"


//hash value of Voltage Plan file (extracted all cell values)
static char voltage_plan_hash_value[] = "6421C29D9E3B628DDBD7A6B061A40260";


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


static cpr_margin_cfg margins_199040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   20000, .closedLoop =   71000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_11652401061 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  415 },
                                      { .ro =  6, .quotient =  298 },
                                      { .ro = 12, .quotient =  584 },
                                      { .ro = 14, .quotient =  287 },
                                      { .ro = 15, .quotient =  184 } },
};


static cpr_fuse_data  fuses_3758236327 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR0_TARG_VOLT_SVS2) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR0_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_177040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   12000, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_15930779535 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  457 },
                                      { .ro =  6, .quotient =  336 },
                                      { .ro = 12, .quotient =  634 },
                                      { .ro = 14, .quotient =  325 },
                                      { .ro = 15, .quotient =  219 } },
};


static cpr_fuse_data  fuses_5084327236 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION13, CPR0_TARG_VOLT_OFFSET_SVS1_4_2), CPR_FUSE_MAPPING(CALIBRATION12, CPR0_TARG_VOLT_OFFSET_SVS1_1_0) } } },
};


static cpr_margin_cfg margins_149040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_10004822861 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  554 },
                                      { .ro =  6, .quotient =  427 },
                                      { .ro = 12, .quotient =  754 },
                                      { .ro = 14, .quotient =  415 },
                                      { .ro = 15, .quotient =  301 } },
};


static cpr_fuse_data  fuses_4497788059 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR0_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR0_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_125040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   -8000, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_10522565847 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  690 },
                                      { .ro =  6, .quotient =  556 },
                                      { .ro = 12, .quotient =  915 },
                                      { .ro = 14, .quotient =  543 },
                                      { .ro = 15, .quotient =  415 } },
};


static cpr_fuse_data  fuses_3312830647 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR0_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_169040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   -8000, .closedLoop =   50000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_7692158588 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  804 },
                                      { .ro =  6, .quotient =  659 },
                                      { .ro = 12, .quotient = 1060 },
                                      { .ro = 14, .quotient =  646 },
                                      { .ro = 15, .quotient =  512 } },
};


static cpr_fuse_data  fuses_5671055679 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR0_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR0_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_127040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =  -24000, .closedLoop =   37000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_14204197009 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  908 },
                                      { .ro =  6, .quotient =  776 },
                                      { .ro = 12, .quotient = 1177 },
                                      { .ro = 14, .quotient =  765 },
                                      { .ro = 15, .quotient =  627 } },
};


static cpr_fuse_data  fuses_2935888439 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR0_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_margin_cfg margins_133040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =  -24000, .closedLoop =   40000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_8749653431 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  998 },
                                      { .ro =  6, .quotient =  876 },
                                      { .ro = 12, .quotient = 1278 },
                                      { .ro = 14, .quotient =  867 },
                                      { .ro = 15, .quotient =  725 } },
};


static cpr_fuse_data  fuses_1135908467 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR0_TARG_VOLT_OFFSET_TUR_4_3), CPR_FUSE_MAPPING(CALIBRATION14, CPR0_TARG_VOLT_OFFSET_TUR_2_0) } } },
};


static cpr_margin_cfg margins_141040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =  -24000, .closedLoop =   44000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_7761718965 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient = 1147 },
                                      { .ro =  6, .quotient = 1027 },
                                      { .ro = 12, .quotient = 1430 },
                                      { .ro = 14, .quotient = 1037 },
                                      { .ro = 15, .quotient =  888 } },
};


static cpr_fuse_data  fuses_1009336094 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR0_TARG_VOLT_SUT) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR0_TARG_VOLT_OFFSET_SUT) } } },
};


static cpr_kv_cfg  kvs_41397929827 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =  336 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =    0 },
                                { .ro =  6, .kv =  306 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =    0 },
                                { .ro =  9, .kv =    0 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =  400 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  321 },
                                { .ro = 15, .kv =  306 } },
};


/*
 * CX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_20762159100 =
{
    .modesCount      = 10,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_41397929827,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_P1,
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
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_3758236327, .quotients = &quotients_11652401061, .margins = &margins_199040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS_P1
        {.fref = 588000, .freqDelta =       0, .fuses = &fuses_5084327236, .quotients = &quotients_15930779535, .margins = &margins_177040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  696000, .floor =  544000, .freq =       0, .interplEnabled = 30} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_4497788059, .quotients = &quotients_10004822861, .margins = &margins_149040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_3312830647, .quotients = &quotients_10522565847, .margins = &margins_125040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_5671055679, .quotients = &quotients_7692158588, .margins = &margins_169040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  776000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_2935888439, .quotients = &quotients_14204197009, .margins = &margins_127040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  688000, .freq =       0, .interplEnabled = 30} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_1135908467, .quotients = &quotients_8749653431, .margins = &margins_133040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  716000, .freq =       0, .interplEnabled = 57} } },

        // TURBO_L1
        {.fref = 856000, .freqDelta =       0, .fuses = &fuses_1009336094, .quotients = &quotients_7761718965, .margins = &margins_141040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  760000, .freq =       0, .interplEnabled = 0} } },

        // SUPER_TURBO_NO_CPR
        {.fref = 904000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  904000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_version  ver_ANY_1_0_1_255 = { .foundry = CPR_FOUNDRY_ANY, .min = CPR_CHIPINFO_VERSION(1,0), .max = CPR_CHIPINFO_VERSION(1,255) };


static cpr_margin_cfg margins_193040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   20000, .closedLoop =   68000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_10159314403 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  343 },
                                      { .ro =  3, .quotient =  346 },
                                      { .ro =  6, .quotient =  238 },
                                      { .ro = 12, .quotient =  493 },
                                      { .ro = 14, .quotient =  230 } },
};


static cpr_fuse_data  fuses_2755099661 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION68, CPR9_TARG_VOLT_SVS3) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION69, CPR9_TARG_VOLT_OFFSET_SVS3) } } },
};


static cpr_margin_cfg margins_235040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   32000, .closedLoop =   83000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_12364116920 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  410 },
                                      { .ro =  3, .quotient =  415 },
                                      { .ro =  6, .quotient =  298 },
                                      { .ro = 12, .quotient =  584 },
                                      { .ro = 14, .quotient =  287 } },
};


static cpr_fuse_data  fuses_3648631753 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION69, CPR9_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_257040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   36000, .closedLoop =   92000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_10628634186 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  547 },
                                      { .ro =  3, .quotient =  554 },
                                      { .ro =  6, .quotient =  427 },
                                      { .ro = 12, .quotient =  754 },
                                      { .ro = 14, .quotient =  415 } },
};


static cpr_fuse_data  fuses_3392222239 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION29, CPR9_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION69, CPR9_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_269040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   40000, .closedLoop =   96000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_9749052530 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  690 },
                                      { .ro =  6, .quotient =  556 },
                                      { .ro = 12, .quotient =  915 },
                                      { .ro = 14, .quotient =  543 } },
};


static cpr_fuse_data  fuses_4276219356 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION69, CPR9_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_289040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   32000, .closedLoop =   90000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_4710262411 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  804 },
                                      { .ro =  6, .quotient =  659 },
                                      { .ro = 12, .quotient = 1060 },
                                      { .ro = 14, .quotient =  646 } },
};


static cpr_fuse_data  fuses_5899060159 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION29, CPR9_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION69, CPR9_TARG_VOLT_OFFSET_NOM_4_2), CPR_FUSE_MAPPING(CALIBRATION68, CPR9_TARG_VOLT_OFFSET_NOM_1_0) } } },
};


static cpr_margin_cfg margins_343040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   48000, .closedLoop =  109000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_10299494829 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  908 },
                                      { .ro =  6, .quotient =  776 },
                                      { .ro = 12, .quotient = 1177 },
                                      { .ro = 14, .quotient =  765 } },
};


static cpr_fuse_data  fuses_1709344017 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION68, CPR9_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_margin_cfg margins_325040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   40000, .closedLoop =  104000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_8624803768 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  998 },
                                      { .ro =  6, .quotient =  876 },
                                      { .ro = 12, .quotient = 1278 },
                                      { .ro = 14, .quotient =  867 } },
};


static cpr_fuse_data  fuses_83474837 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION68, CPR9_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_margin_cfg margins_285040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   24000, .closedLoop =   92000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_5472423872 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient = 1147 },
                                      { .ro =  6, .quotient = 1027 },
                                      { .ro = 12, .quotient = 1430 },
                                      { .ro = 14, .quotient = 1037 } },
};


static cpr_fuse_data  fuses_3801094447 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION68, CPR9_TARG_VOLT_SUT) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION68, CPR9_TARG_VOLT_OFFSET_SUT) } } },
};


static cpr_kv_cfg  kvs_37465521396 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =  328 },
                                { .ro =  3, .kv =  332 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =    0 },
                                { .ro =  6, .kv =  307 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =    0 },
                                { .ro =  9, .kv =    0 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =  400 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  322 },
                                { .ro = 15, .kv =    0 } },
};


/*
 * NSP Voltage Plan
 */
static cpr_voltage_plan voltage_plan_15814510605 =
{
    .modesCount      = 9,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_37465521396,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1,
                                                    CPR_VOLTAGE_MODE_SUPER_TURBO_NO_CPR },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS_D1
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_2755099661, .quotients = &quotients_10159314403, .margins = &margins_193040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_3648631753, .quotients = &quotients_12364116920, .margins = &margins_235040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 33} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_3392222239, .quotients = &quotients_10628634186, .margins = &margins_257040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_4276219356, .quotients = &quotients_9749052530, .margins = &margins_269040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_5899060159, .quotients = &quotients_4710262411, .margins = &margins_289040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  776000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_1709344017, .quotients = &quotients_10299494829, .margins = &margins_343040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  688000, .freq =       0, .interplEnabled = 30} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_83474837, .quotients = &quotients_8624803768, .margins = &margins_325040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  716000, .freq =       0, .interplEnabled = 57} } },

        // TURBO_L1
        {.fref = 856000, .freqDelta =       0, .fuses = &fuses_3801094447, .quotients = &quotients_5472423872, .margins = &margins_285040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  760000, .freq =       0, .interplEnabled = 0} } },

        // SUPER_TURBO_NO_CPR
        {.fref = 904000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  904000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_214040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   32000, .closedLoop =   80000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_3497487807 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  230 } },
};


static cpr_fuse_data  fuses_7871244440 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR2_TARG_VOLT_SVS3_5_2), CPR_FUSE_MAPPING(CALIBRATION18, CPR2_TARG_VOLT_SVS3_1_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION13, CPR2_TARG_VOLT_OFFSET_LSVSD1) } } },
};


static cpr_margin_cfg margins_220040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   32000, .closedLoop =   83000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_2917605847 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  287 } },
};


static cpr_fuse_data  fuses_6828135083 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION18, CPR2_TARG_VOLT_SVSL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION9, CPR2_TARG_VOLT_OFFSET_LSVS) } } },
};


static cpr_margin_cfg margins_245040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   32000, .closedLoop =   88000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_2527495936 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  415 } },
};


static cpr_fuse_data  fuses_3130713520 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION18, CPR2_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION20, CPR2_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_quotient_cfg  quotients_57719879 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  543 } },
};


static cpr_fuse_data  fuses_7219979654 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION20, CPR2_TARG_VOLT_OFFSET_SVSL1_4_3), CPR_FUSE_MAPPING(CALIBRATION19, CPR2_TARG_VOLT_OFFSET_SVSL1_2_0) } } },
};


static cpr_margin_cfg margins_225040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   24000, .closedLoop =   82000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_683300777 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  594 } },
};


static cpr_fuse_data  fuses_2561139130 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION18, CPR2_TARG_VOLT_NOML1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR2_TARG_VOLT_OFFSET_SVSL2) } } },
};


static cpr_margin_cfg margins_217040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =    8000, .closedLoop =   66000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_1901917841 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  646 } },
};


static cpr_fuse_data  fuses_4265385271 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR2_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_175040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   -8000, .closedLoop =   53000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_3684806558 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  765 } },
};


static cpr_fuse_data  fuses_426360533 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR2_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_quotient_cfg  quotients_1056147855 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  867 } },
};


static cpr_fuse_data  fuses_2219864713 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR2_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_margin_cfg margins_21040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =  -64000, .closedLoop =    4000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_175100294 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient = 1037 } },
};


static cpr_fuse_data  fuses_4100700558 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION18, CPR2_TARG_VOLT_SUT) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR2_TARG_VOLT_OFFSET_SUT) } } },
};


static cpr_kv_cfg  kvs_35469660446 =
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
                                { .ro = 14, .kv =  311 },
                                { .ro = 15, .kv =    0 } },
};


/*
 * GFX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_19418509048 =
{
    .modesCount      = 9,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_35469660446,
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
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_7871244440, .quotients = &quotients_3497487807, .margins = &margins_214040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_6828135083, .quotients = &quotients_2917605847, .margins = &margins_220040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_3130713520, .quotients = &quotients_2527495936, .margins = &margins_245040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_7219979654, .quotients = &quotients_57719879, .margins = &margins_245040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 71} } },

        // SVS_L2
        {.fref = 704000, .freqDelta =       0, .fuses = &fuses_2561139130, .quotients = &quotients_683300777, .margins = &margins_225040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  768000, .floor =  640000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_4265385271, .quotients = &quotients_1901917841, .margins = &margins_217040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  776000, .floor =  660000, .freq =       0, .interplEnabled = 15} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_426360533, .quotients = &quotients_3684806558, .margins = &margins_175040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  688000, .freq =       0, .interplEnabled = 41} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_2219864713, .quotients = &quotients_1056147855, .margins = &margins_133040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  716000, .freq =       0, .interplEnabled = 63} } },

        // TURBO_L1
        {.fref = 856000, .freqDelta =       0, .fuses = &fuses_4100700558, .quotients = &quotients_175100294, .margins = &margins_21040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  760000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_219040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   28000, .closedLoop =   77000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_8896276442 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  5, .quotient =  220 },
                                      { .ro =  6, .quotient =  238 },
                                      { .ro =  8, .quotient =  139 },
                                      { .ro =  9, .quotient =  143 },
                                      { .ro = 14, .quotient =  230 } },
};


static cpr_fuse_data  fuses_5882290193 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR1_TARG_VOLT_SVS3) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION17, CPR1_TARG_VOLT_OFFSET_SVS3) } } },
};


static cpr_margin_cfg margins_231040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   28000, .closedLoop =   83000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_14982640343 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  5, .quotient =  272 },
                                      { .ro =  6, .quotient =  298 },
                                      { .ro =  8, .quotient =  182 },
                                      { .ro =  9, .quotient =  186 },
                                      { .ro = 14, .quotient =  287 } },
};


static cpr_fuse_data  fuses_1753063010 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION17, CPR1_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_267040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   36000, .closedLoop =   97000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_9113335701 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  554 },
                                      { .ro =  6, .quotient =  427 },
                                      { .ro = 12, .quotient =  754 },
                                      { .ro = 14, .quotient =  415 } },
};


static cpr_fuse_data  fuses_3890707496 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR1_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION17, CPR1_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_239040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   28000, .closedLoop =   87000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_fuse_data  fuses_711658270 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION17, CPR1_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_329040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   44000, .closedLoop =  104000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_fuse_data  fuses_5610956086 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR1_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION17, CPR1_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_331040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   44000, .closedLoop =  105000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_fuse_data  fuses_4086167228 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION9, CPR1_TARG_VOLT_NOML1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION17, CPR1_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_kv_cfg  kvs_36118145732 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =  334 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =  284 },
                                { .ro =  6, .kv =  317 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =  240 },
                                { .ro =  9, .kv =  247 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =  384 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  330 },
                                { .ro = 15, .kv =    0 } },
};


/*
 * MSS Voltage Plan
 */
static cpr_voltage_plan voltage_plan_15859819535 =
{
    .modesCount      = 6,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_36118145732,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1 },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS_D1
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_5882290193, .quotients = &quotients_8896276442, .margins = &margins_219040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 618000, .freqDelta =       0, .fuses = &fuses_1753063010, .quotients = &quotients_14982640343, .margins = &margins_231040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  730000, .floor =  558000, .freq =       0, .interplEnabled = 33} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_3890707496, .quotients = &quotients_9113335701, .margins = &margins_267040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_711658270, .quotients = &quotients_9749052530, .margins = &margins_239040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_5610956086, .quotients = &quotients_4710262411, .margins = &margins_329040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  776000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_4086167228, .quotients = &quotients_10299494829, .margins = &margins_331040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  688000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_97960 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =      0 } }
};


static cpr_fuse_data  fuses_4323143398 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION21, CPR3_TARG_VOLT_SVS_5_1), CPR_FUSE_MAPPING(CALIBRATION20, CPR3_TARG_VOLT_SVS_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_fuse_data  fuses_3860757830 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION4, CPR3_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


/*
 * VDDA Voltage Plan
 */
static cpr_voltage_plan voltage_plan_4914612450 =
{
    .modesCount      = 3,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  352000, .floor =  352000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 704000, .freqDelta =       0, .fuses = &fuses_4323143398, .quotients = NULL, .margins = &margins_97960,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  824000, .floor =  688000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 892000, .freqDelta =       0, .fuses = &fuses_3860757830, .quotients = NULL, .margins = &margins_97960,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  952000, .floor =  892000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_114040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   26000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_fuse_data  fuses_561489839 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION57, CPR4_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_quotient_cfg  quotients_7132628595 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  484 },
                                      { .ro =  5, .quotient =  494 },
                                      { .ro =  7, .quotient =  190 },
                                      { .ro = 15, .quotient =  501 } },
};


static cpr_fuse_data  fuses_3943499182 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION21, CPR4_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION65, CPR4_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_150040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   44000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_fuse_data  fuses_3896616199 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION22, CPR4_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_quotient_cfg  quotients_15362003720 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  580 },
                                      { .ro =  5, .quotient =  586 },
                                      { .ro =  6, .quotient =  280 },
                                      { .ro =  7, .quotient =  225 },
                                      { .ro = 14, .quotient =  754 },
                                      { .ro = 15, .quotient =  599 } },
};


static cpr_fuse_data  fuses_4926725550 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION21, CPR4_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION22, CPR4_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_152040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   45000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_12669259804 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  625 },
                                      { .ro =  5, .quotient =  631 },
                                      { .ro =  6, .quotient =  297 },
                                      { .ro =  7, .quotient =  241 },
                                      { .ro = 14, .quotient =  802 },
                                      { .ro = 15, .quotient =  646 } },
};


static cpr_fuse_data  fuses_1671846299 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION22, CPR4_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_margin_cfg margins_162040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   50000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_10690692936 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  685 },
                                      { .ro =  5, .quotient =  712 },
                                      { .ro =  6, .quotient =  326 },
                                      { .ro =  7, .quotient =  273 },
                                      { .ro = 14, .quotient =  890 },
                                      { .ro = 15, .quotient =  739 } },
};


static cpr_fuse_data  fuses_7650331853 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION47, CPR4_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION55, CPR4_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_margin_cfg margins_160040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   49000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_13045659672 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  801 },
                                      { .ro =  5, .quotient =  805 },
                                      { .ro =  6, .quotient =  361 },
                                      { .ro =  7, .quotient =  305 },
                                      { .ro = 14, .quotient =  992 },
                                      { .ro = 15, .quotient =  831 } },
};


static cpr_fuse_data  fuses_7625489310 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION21, CPR4_TARG_VOLT_SUT) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION22, CPR4_TARG_VOLT_OFFSET_SUT) } } },
};


static cpr_kv_cfg  kvs_31577744404 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =    0 },
                                { .ro =  4, .kv =  302 },
                                { .ro =  5, .kv =  304 },
                                { .ro =  6, .kv =  107 },
                                { .ro =  7, .kv =  109 },
                                { .ro =  8, .kv =    0 },
                                { .ro =  9, .kv =    0 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =    0 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  317 },
                                { .ro = 15, .kv =  317 } },
};


/*
 * MX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_21032932404 =
{
    .modesCount      = 9,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_31577744404,
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
         .subModes        = (cpr_freq_data[]){ {.ceiling =  680000, .floor =  504000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 716000, .freqDelta =       0, .fuses = &fuses_561489839, .quotients = NULL, .margins = &margins_114040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  716000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 716000, .freqDelta =       0, .fuses = &fuses_3943499182, .quotients = &quotients_7132628595, .margins = &margins_114040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  716000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_3896616199, .quotients = NULL, .margins = &margins_150040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_4926725550, .quotients = &quotients_15362003720, .margins = &margins_150040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  804000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_1671846299, .quotients = &quotients_12669259804, .margins = &margins_152040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  752000, .freq =       0, .interplEnabled = 33} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_7650331853, .quotients = &quotients_10690692936, .margins = &margins_162040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_7625489310, .quotients = &quotients_13045659672, .margins = &margins_160040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // SUPER_TURBO_NO_CPR
        {.fref = 884000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  884000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_fuse_data  fuses_502386656 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION67, CPR5_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_fuse_data  fuses_6294273368 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION4, CPR5_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION66, CPR5_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_142040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   40000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_fuse_data  fuses_3049317940 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION24, CPR5_TARG_VOLT_OFFSET_SVSL1_4_2), CPR_FUSE_MAPPING(CALIBRATION23, CPR5_TARG_VOLT_OFFSET_SVSL1_1_0) } } },
};


static cpr_fuse_data  fuses_7072571919 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR5_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR5_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_fuse_data  fuses_3257226972 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR5_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_fuse_data  fuses_5120540568 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION8, CPR5_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION66, CPR5_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_fuse_data  fuses_6549006324 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION22, CPR5_TARG_VOLT_SUT) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR5_TARG_VOLT_OFFSET_SUT) } } },
};


/*
 * MXC Voltage Plan
 */
static cpr_voltage_plan voltage_plan_13886711214 =
{
    .modesCount      = 9,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_31577744404,
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
         .subModes        = (cpr_freq_data[]){ {.ceiling =  680000, .floor =  504000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 716000, .freqDelta =       0, .fuses = &fuses_502386656, .quotients = NULL, .margins = &margins_114040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  716000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 716000, .freqDelta =       0, .fuses = &fuses_6294273368, .quotients = &quotients_7132628595, .margins = &margins_114040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  716000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_3049317940, .quotients = NULL, .margins = &margins_142040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_7072571919, .quotients = &quotients_15362003720, .margins = &margins_150040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  804000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_3257226972, .quotients = &quotients_12669259804, .margins = &margins_152040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  752000, .freq =       0, .interplEnabled = 33} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_5120540568, .quotients = &quotients_10690692936, .margins = &margins_162040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_6549006324, .quotients = &quotients_13045659672, .margins = &margins_160040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // SUPER_TURBO_NO_CPR
        {.fref = 884000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  884000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_57960 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 } }
};


static cpr_fuse_data  fuses_1366833670 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION24, CPR6_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_fuse_data  fuses_2541485367 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION24, CPR6_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


/*
 * LPI_MX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_4865986440 =
{
    .modesCount      = 4,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  680000, .floor =  508000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_57960,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_1366833670, .quotients = NULL, .margins = &margins_57960,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  808000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_2541485367, .quotients = NULL, .margins = &margins_57960,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  848000, .floor =  800000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_157040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =    8000, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_8654532549 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  346 },
                                      { .ro =  6, .quotient =  238 },
                                      { .ro = 12, .quotient =  493 },
                                      { .ro = 14, .quotient =  230 } },
};


static cpr_fuse_data  fuses_6050743291 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION25, CPR7_TARG_VOLT_SVS3) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION26, CPR7_TARG_VOLT_OFFSET_SVS3) } } },
};


static cpr_margin_cfg margins_139040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   51000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_9268682324 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  415 },
                                      { .ro =  6, .quotient =  298 },
                                      { .ro = 12, .quotient =  584 },
                                      { .ro = 14, .quotient =  287 } },
};


static cpr_fuse_data  fuses_2831105666 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION26, CPR7_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_fuse_data  fuses_4119804821 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION25, CPR7_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION26, CPR7_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_quotient_cfg  quotients_11588991692 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  684 },
                                      { .ro =  3, .quotient =  690 },
                                      { .ro =  6, .quotient =  556 },
                                      { .ro = 12, .quotient =  915 },
                                      { .ro = 14, .quotient =  543 } },
};


static cpr_fuse_data  fuses_3749688245 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION26, CPR7_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_quotient_cfg  quotients_6680693687 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  794 },
                                      { .ro =  3, .quotient =  804 },
                                      { .ro =  6, .quotient =  659 },
                                      { .ro = 12, .quotient = 1060 },
                                      { .ro = 14, .quotient =  646 } },
};


static cpr_fuse_data  fuses_8488855585 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION25, CPR7_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION26, CPR7_TARG_VOLT_OFFSET_NOM_4_3), CPR_FUSE_MAPPING(CALIBRATION25, CPR7_TARG_VOLT_OFFSET_NOM_2_0) } } },
};


static cpr_quotient_cfg  quotients_10265023869 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1006 },
                                      { .ro =  3, .quotient =  998 },
                                      { .ro =  6, .quotient =  876 },
                                      { .ro = 12, .quotient = 1278 },
                                      { .ro = 14, .quotient =  867 } },
};


static cpr_fuse_data  fuses_3841763400 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION25, CPR7_TARG_VOLT_TUR_5), CPR_FUSE_MAPPING(CALIBRATION24, CPR7_TARG_VOLT_TUR_4_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION25, CPR7_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_kv_cfg  kvs_34996362712 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =  336 },
                                { .ro =  3, .kv =  339 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =    0 },
                                { .ro =  6, .kv =  316 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =    0 },
                                { .ro =  9, .kv =    0 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =  401 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  327 },
                                { .ro = 15, .kv =    0 } },
};


/*
 * LPI_CX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_12530311290 =
{
    .modesCount      = 7,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_34996362712,
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
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_6050743291, .quotients = &quotients_8654532549, .margins = &margins_157040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_2831105666, .quotients = &quotients_9268682324, .margins = &margins_139040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 33} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_4119804821, .quotients = &quotients_10628634186, .margins = &margins_125040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_3749688245, .quotients = &quotients_11588991692, .margins = &margins_125040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_8488855585, .quotients = &quotients_6680693687, .margins = &margins_169040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  776000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_3841763400, .quotients = &quotients_10265023869, .margins = &margins_133040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  716000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_175041 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   12000, .closedLoop =   63000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_11872526988 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  6, .quotient =  298 },
                                      { .ro =  8, .quotient =  182 },
                                      { .ro =  9, .quotient =  186 },
                                      { .ro = 15, .quotient =  184 } },
};


static cpr_fuse_data  fuses_4464519061 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION4, CPR8_TARG_VOLT_SVS2) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION28, CPR8_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_161040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =    4000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_3083782155 =
{
    .count = 2,
    .quots = (cpr_quotient[]) { { .ro =  6, .quotient =  427 },
                                      { .ro = 15, .quotient =  301 } },
};


static cpr_fuse_data  fuses_5696893757 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION27, CPR8_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION28, CPR8_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_89040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =  -20000, .closedLoop =   36000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_3913935002 =
{
    .count = 2,
    .quots = (cpr_quotient[]) { { .ro =  6, .quotient =  556 },
                                      { .ro = 15, .quotient =  415 } },
};


static cpr_fuse_data  fuses_1146359799 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION28, CPR8_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_121040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =  -24000, .closedLoop =   34000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_3683830766 =
{
    .count = 2,
    .quots = (cpr_quotient[]) { { .ro =  6, .quotient =  659 },
                                      { .ro = 15, .quotient =  512 } },
};


static cpr_fuse_data  fuses_2791127490 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION27, CPR8_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION27, CPR8_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_205040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_2301822947 =
{
    .count = 2,
    .quots = (cpr_quotient[]) { { .ro =  6, .quotient =  876 },
                                      { .ro = 15, .quotient =  725 } },
};


static cpr_fuse_data  fuses_5786907032 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION27, CPR8_TARG_VOLT_TUR_5_2), CPR_FUSE_MAPPING(CALIBRATION26, CPR8_TARG_VOLT_TUR_1_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION27, CPR8_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_kv_cfg  kvs_38480332529 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =    0 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =    0 },
                                { .ro =  6, .kv =  316 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =  331 },
                                { .ro =  9, .kv =  346 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =    0 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =    0 },
                                { .ro = 15, .kv =  312 } },
};


/*
 * MM Voltage Plan
 */
static cpr_voltage_plan voltage_plan_11451373189 =
{
    .modesCount      = 5,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_38480332529,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS
        {.fref = 588000, .freqDelta =       0, .fuses = &fuses_4464519061, .quotients = &quotients_11872526988, .margins = &margins_175041,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  532000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_5696893757, .quotients = &quotients_3083782155, .margins = &margins_161040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_1146359799, .quotients = &quotients_3913935002, .margins = &margins_89040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_2791127490, .quotients = &quotients_3683830766, .margins = &margins_121040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  776000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_5786907032, .quotients = &quotients_2301822947, .margins = &margins_205040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  716000, .freq =       0, .interplEnabled = 0} } }},
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


static cpr_margin_cfg margins_191040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   14000, .closedLoop =   70000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_137040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   -4000, .closedLoop =   52000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_195040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_margin_cfg margins_151040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =  -16000, .closedLoop =   45000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_kv_cfg  kvs_34833711298 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =  332 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =    0 },
                                { .ro =  6, .kv =  315 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =    0 },
                                { .ro =  9, .kv =    0 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =  384 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  327 },
                                { .ro = 15, .kv =  307 } },
};


/*
 * CX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_16863772278 =
{
    .modesCount      = 9,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_34833711298,
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
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_3758236327, .quotients = &quotients_11652401061, .margins = &margins_199040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_4497788059, .quotients = &quotients_10004822861, .margins = &margins_191040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_3312830647, .quotients = &quotients_10522565847, .margins = &margins_137040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_5671055679, .quotients = &quotients_7692158588, .margins = &margins_195040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  776000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_2935888439, .quotients = &quotients_14204197009, .margins = &margins_151040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  688000, .freq =       0, .interplEnabled = 30} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_1135908467, .quotients = &quotients_8749653431, .margins = &margins_133040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  716000, .freq =       0, .interplEnabled = 57} } },

        // TURBO_L1
        {.fref = 856000, .freqDelta =       0, .fuses = &fuses_1009336094, .quotients = &quotients_7761718965, .margins = &margins_141040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  760000, .freq =       0, .interplEnabled = 0} } },

        // SUPER_TURBO_NO_CPR
        {.fref = 904000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  904000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_version  ver_ANY_2_0_2_255 = { .foundry = CPR_FOUNDRY_ANY, .min = CPR_CHIPINFO_VERSION(2,0), .max = CPR_CHIPINFO_VERSION(2,255) };


static cpr_margin_cfg margins_181040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   16000, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_221040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   24000, .closedLoop =   80000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_265040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   24000, .closedLoop =   82000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_margin_cfg margins_295040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   32000, .closedLoop =   93000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_margin_cfg margins_253040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   16000, .closedLoop =   80000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_margin_cfg margins_225041 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =    4000, .closedLoop =   72000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_kv_cfg  kvs_36155236745 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =  333 },
                                { .ro =  3, .kv =  332 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =    0 },
                                { .ro =  6, .kv =  313 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =    0 },
                                { .ro =  9, .kv =    0 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =  389 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  324 },
                                { .ro = 15, .kv =    0 } },
};


/*
 * NSP Voltage Plan
 */
static cpr_voltage_plan voltage_plan_22741829045 =
{
    .modesCount      = 9,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_36155236745,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1,
                                                    CPR_VOLTAGE_MODE_SUPER_TURBO_NO_CPR },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS_D1
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_2755099661, .quotients = &quotients_10159314403, .margins = &margins_181040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_3648631753, .quotients = &quotients_12364116920, .margins = &margins_235040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 33} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_3392222239, .quotients = &quotients_10628634186, .margins = &margins_221040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_4276219356, .quotients = &quotients_9749052530, .margins = &margins_245040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_5899060159, .quotients = &quotients_4710262411, .margins = &margins_265040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  796000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_1709344017, .quotients = &quotients_10299494829, .margins = &margins_295040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  688000, .freq =       0, .interplEnabled = 30} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_83474837, .quotients = &quotients_8624803768, .margins = &margins_253040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  876000, .floor =  716000, .freq =       0, .interplEnabled = 57} } },

        // TURBO_L1
        {.fref = 856000, .freqDelta =       0, .fuses = &fuses_3801094447, .quotients = &quotients_5472423872, .margins = &margins_225041,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  924000, .floor =  760000, .freq =       0, .interplEnabled = 0} } },

        // SUPER_TURBO_NO_CPR
        {.fref = 924000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  924000, .floor =  924000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_166040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   16000, .closedLoop =   64000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 } }
};


static cpr_fuse_data  fuses_4802249284 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR2_TARG_VOLT_SVS3_5_2), CPR_FUSE_MAPPING(CALIBRATION18, CPR2_TARG_VOLT_SVS3_1_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION13, CPR2_TARG_VOLT_OFFSET_LSVSD2) } } },
};


static cpr_fuse_data  fuses_4238985413 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION18, CPR2_TARG_VOLT_SVSL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION10, CPR2_TARG_VOLT_OFFSET_LSVSD0) } } },
};


static cpr_margin_cfg margins_226040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   32000, .closedLoop =   86000, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_223040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   24000, .closedLoop =   81000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_fuse_data  fuses_3261405477 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION18, CPR2_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION13, CPR2_TARG_VOLT_OFFSET_LSVSL1) } } },
};


static cpr_margin_cfg margins_247040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   32000, .closedLoop =   89000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_207040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   16000, .closedLoop =   77000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_fuse_data  fuses_45000067 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION13, CPR2_TARG_VOLT_OFFSET_SVSL0) } } },
};


static cpr_margin_cfg margins_255040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   32000, .closedLoop =   93000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_231041 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   24000, .closedLoop =   85000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_233040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =    8000, .closedLoop =   74000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_margin_cfg margins_195041 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   -8000, .closedLoop =   63000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_margin_cfg margins_151041 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =  -24000, .closedLoop =   49000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_margin_cfg margins_33040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =  -64000, .closedLoop =   10000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_margin_cfg margins_327040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   32000, .closedLoop =  109000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_fuse_data  fuses_4282965107 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION18, CPR2_TARG_VOLT_SUT) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION13, CPR2_TARG_VOLT_OFFSET_LSVSD3) } } },
};


static cpr_kv_cfg  kvs_36463685202 =
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
                                { .ro = 14, .kv =  324 },
                                { .ro = 15, .kv =    0 } },
};


/*
 * GFX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_27618799637 =
{
    .modesCount      = 14,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_36463685202,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS_D2,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_D0,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_L1,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L0,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_SVS_L2,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1,
                                                    CPR_VOLTAGE_MODE_TURBO_L2 },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS_D2
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_4802249284, .quotients = &quotients_3497487807, .margins = &margins_166040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS_D1
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_7871244440, .quotients = &quotients_3497487807, .margins = &margins_214040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS_D0
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_4238985413, .quotients = &quotients_2917605847, .margins = &margins_220040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_6828135083, .quotients = &quotients_2917605847, .margins = &margins_226040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS_L1
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_3261405477, .quotients = &quotients_2527495936, .margins = &margins_223040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_3130713520, .quotients = &quotients_2527495936, .margins = &margins_247040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L0
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_45000067, .quotients = &quotients_57719879, .margins = &margins_207040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 71} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_7219979654, .quotients = &quotients_57719879, .margins = &margins_255040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 71} } },

        // SVS_L2
        {.fref = 704000, .freqDelta =       0, .fuses = &fuses_2561139130, .quotients = &quotients_683300777, .margins = &margins_231041,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  768000, .floor =  632000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_4265385271, .quotients = &quotients_1901917841, .margins = &margins_233040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  776000, .floor =  648000, .freq =       0, .interplEnabled = 15} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_426360533, .quotients = &quotients_3684806558, .margins = &margins_195041,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  668000, .freq =       0, .interplEnabled = 41} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_2219864713, .quotients = &quotients_1056147855, .margins = &margins_151041,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  676000, .freq =       0, .interplEnabled = 63} } },

        // TURBO_L1
        {.fref = 856000, .freqDelta =       0, .fuses = &fuses_4100700558, .quotients = &quotients_175100294, .margins = &margins_33040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  692000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L2
        {.fref = 856000, .freqDelta =       0, .fuses = &fuses_4282965107, .quotients = &quotients_175100294, .margins = &margins_327040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  944000, .floor =  720000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_205041 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   24000, .closedLoop =   72000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_211040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   24000, .closedLoop =   75000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_313040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   40000, .closedLoop =   98000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_margin_cfg margins_323040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   40000, .closedLoop =  103000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_kv_cfg  kvs_33562298290 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =  341 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =  291 },
                                { .ro =  6, .kv =  314 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =  247 },
                                { .ro =  9, .kv =  252 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =  397 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  324 },
                                { .ro = 15, .kv =    0 } },
};


/*
 * MSS Voltage Plan
 */
static cpr_voltage_plan voltage_plan_10964855768 =
{
    .modesCount      = 6,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_33562298290,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1 },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS_D1
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_5882290193, .quotients = &quotients_8896276442, .margins = &margins_205041,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_1753063010, .quotients = &quotients_14982640343, .margins = &margins_211040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 33} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_3890707496, .quotients = &quotients_9113335701, .margins = &margins_245040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_711658270, .quotients = &quotients_9749052530, .margins = &margins_223040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_5610956086, .quotients = &quotients_4710262411, .margins = &margins_313040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_4086167228, .quotients = &quotients_10299494829, .margins = &margins_323040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  688000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_fuse_data  fuses_3180609963 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION4, CPR3_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


/*
 * VDDA Voltage Plan
 */
static cpr_voltage_plan voltage_plan_8429959293 =
{
    .modesCount      = 4,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  352000, .floor =  352000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 704000, .freqDelta =       0, .fuses = &fuses_4323143398, .quotients = NULL, .margins = &margins_97960,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  824000, .floor =  688000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_3180609963, .quotients = NULL, .margins = &margins_97960,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  840000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 892000, .freqDelta =       0, .fuses = &fuses_3860757830, .quotients = NULL, .margins = &margins_97960,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  952000, .floor =  892000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_142041 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =  100000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 } }
};


static cpr_margin_cfg margins_174040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   56000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_7253740401 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  423 },
                                      { .ro =  5, .quotient =  433 },
                                      { .ro = 15, .quotient =  437 } },
};


static cpr_margin_cfg margins_222040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   60000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_8059555480 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  580 },
                                      { .ro =  5, .quotient =  586 },
                                      { .ro = 14, .quotient =  754 },
                                      { .ro = 15, .quotient =  599 } },
};


static cpr_margin_cfg margins_224040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   61000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_8785973691 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  625 },
                                      { .ro =  5, .quotient =  631 },
                                      { .ro = 14, .quotient =  802 },
                                      { .ro = 15, .quotient =  646 } },
};


static cpr_margin_cfg margins_230040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   64000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_5499925808 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  685 },
                                      { .ro =  5, .quotient =  712 },
                                      { .ro = 14, .quotient =  890 },
                                      { .ro = 15, .quotient =  739 } },
};


static cpr_margin_cfg margins_234040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   66000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_9047674644 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  801 },
                                      { .ro =  5, .quotient =  805 },
                                      { .ro = 14, .quotient =  992 },
                                      { .ro = 15, .quotient =  831 } },
};


static cpr_kv_cfg  kvs_32001544255 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =    0 },
                                { .ro =  4, .kv =  308 },
                                { .ro =  5, .kv =  309 },
                                { .ro =  6, .kv =    0 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =    0 },
                                { .ro =  9, .kv =    0 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =    0 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  327 },
                                { .ro = 15, .kv =  322 } },
};


/*
 * MX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_22514054256 =
{
    .modesCount      = 9,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_32001544255,
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
         .subModes        = (cpr_freq_data[]){ {.ceiling =  680000, .floor =  504000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 716000, .freqDelta =       0, .fuses = &fuses_561489839, .quotients = NULL, .margins = &margins_142041,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  716000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 716000, .freqDelta =       0, .fuses = &fuses_3943499182, .quotients = &quotients_7253740401, .margins = &margins_174040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  716000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_3896616199, .quotients = NULL, .margins = &margins_142041,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_4926725550, .quotients = &quotients_8059555480, .margins = &margins_222040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  804000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_1671846299, .quotients = &quotients_8785973691, .margins = &margins_224040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  752000, .freq =       0, .interplEnabled = 33} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_7650331853, .quotients = &quotients_5499925808, .margins = &margins_230040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_7625489310, .quotients = &quotients_9047674644, .margins = &margins_234040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // SUPER_TURBO_NO_CPR
        {.fref = 884000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  884000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_262040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =  100000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_kv_cfg  kvs_29467738361 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =    0 },
                                { .ro =  4, .kv =  308 },
                                { .ro =  5, .kv =  309 },
                                { .ro =  6, .kv =    0 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =    0 },
                                { .ro =  9, .kv =    0 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =    0 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  327 },
                                { .ro = 15, .kv =  321 } },
};


/*
 * MXC Voltage Plan
 */
static cpr_voltage_plan voltage_plan_16829462161 =
{
    .modesCount      = 9,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_29467738361,
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
         .subModes        = (cpr_freq_data[]){ {.ceiling =  680000, .floor =  504000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 716000, .freqDelta =       0, .fuses = &fuses_502386656, .quotients = NULL, .margins = &margins_262040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  716000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 716000, .freqDelta =       0, .fuses = &fuses_6294273368, .quotients = &quotients_7253740401, .margins = &margins_174040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  716000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_3049317940, .quotients = NULL, .margins = &margins_262040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_7072571919, .quotients = &quotients_8059555480, .margins = &margins_222040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  804000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_3257226972, .quotients = &quotients_8785973691, .margins = &margins_224040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  752000, .freq =       0, .interplEnabled = 33} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_5120540568, .quotients = &quotients_5499925808, .margins = &margins_230040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_6549006324, .quotients = &quotients_9047674644, .margins = &margins_234040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // SUPER_TURBO_NO_CPR
        {.fref = 884000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  884000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_129040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   -8000, .closedLoop =   50000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


/*
 * LPI_CX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_12547009959 =
{
    .modesCount      = 7,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_34996362712,
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
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_6050743291, .quotients = &quotients_8654532549, .margins = &margins_157040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_2831105666, .quotients = &quotients_9268682324, .margins = &margins_139040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 33} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_4119804821, .quotients = &quotients_10628634186, .margins = &margins_129040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_3749688245, .quotients = &quotients_11588991692, .margins = &margins_125040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_8488855585, .quotients = &quotients_6680693687, .margins = &margins_169040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  776000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_3841763400, .quotients = &quotients_10265023869, .margins = &margins_133040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  716000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_163040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =    8000, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_167040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =    4000, .closedLoop =   63000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_97040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =  -20000, .closedLoop =   40000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_135040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =  -20000, .closedLoop =   39000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_margin_cfg margins_135041 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =  -24000, .closedLoop =   41000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_kv_cfg  kvs_30955179410 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =    0 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =    0 },
                                { .ro =  6, .kv =  319 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =  266 },
                                { .ro =  9, .kv =  271 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =    0 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =    0 },
                                { .ro = 15, .kv =  310 } },
};


/*
 * MM Voltage Plan
 */
static cpr_voltage_plan voltage_plan_10940734866 =
{
    .modesCount      = 5,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_30955179410,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_4464519061, .quotients = &quotients_11872526988, .margins = &margins_163040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_5696893757, .quotients = &quotients_3083782155, .margins = &margins_167040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_1146359799, .quotients = &quotients_3913935002, .margins = &margins_97040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_2791127490, .quotients = &quotients_3683830766, .margins = &margins_135040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  776000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_5786907032, .quotients = &quotients_2301822947, .margins = &margins_135041,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  716000, .freq =       0, .interplEnabled = 0} } }},
};


/*
 * Aging configs
 */

static cpr_aging_cfg  aging_cfg_cx =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO_L1,
    .sensorID             = 31,
    .kv                   = 117,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 2, .data = (struct raw_fuse_data[]) {
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C27E8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<2) | (1<<1) | (1<<0)},
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C27E4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 27, (1<<31) | (1<<30) | (1<<29) | (1<<28) | (1<<27)} } }
};


static cpr_aging_cfg  aging_cfg_nsp =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO_L1,
    .sensorID             = 0,
    .kv                   = 117,
    .scalingFactor        = 15,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C2824 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 12, (1<<19) | (1<<18) | (1<<17) | (1<<16) | (1<<15) | (1<<14) | (1<<13) | (1<<12)} } }
};


static cpr_aging_cfg  aging_cfg_gfx =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO_L1,
    .sensorID             = 0,
    .kv                   = 117,
    .scalingFactor        = 15,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8B68 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 17, (1<<24) | (1<<23) | (1<<22) | (1<<21) | (1<<20) | (1<<19) | (1<<18) | (1<<17)} } }
};


static cpr_aging_cfg  aging_cfg_mss =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_NOMINAL_L1,
    .sensorID             = 10,
    .kv                   = 131,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 2, .data = (struct raw_fuse_data[]) {
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8B60 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1) | (1<<0)},
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8B5C & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 30, (1<<31) | (1<<30)} } }
};


static cpr_aging_cfg  aging_cfg_mx =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO,
    .sensorID             = 21,
    .kv                   = 119,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C284C & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 23, (1<<30) | (1<<29) | (1<<28) | (1<<27) | (1<<26) | (1<<25) | (1<<24) | (1<<23)} } }
};


static cpr_aging_cfg  aging_cfg_lpi_cx =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO,
    .sensorID             = 3,
    .kv                   = 128,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C2810 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 22, (1<<29) | (1<<28) | (1<<27) | (1<<26) | (1<<25) | (1<<24) | (1<<23) | (1<<22)} } }
};


static cpr_aging_cfg  aging_cfg_mm =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO,
    .sensorID             = 6,
    .kv                   = 128,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8B88 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 20, (1<<27) | (1<<26) | (1<<25) | (1<<24) | (1<<23) | (1<<22) | (1<<21) | (1<<20)} } }
};


/*
 * Versioned Voltage Plans
 */

static cpr_versioned_voltage_plan cx_vvp = {
    .rail     = CPR_RAIL_CX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_20762159100 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_16863772278 },
     },
    .count    = 2,
    .agingCfg = &aging_cfg_cx
};


static cpr_versioned_voltage_plan nsp_vvp = {
    .rail     = CPR_RAIL_NSP,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_15814510605 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_22741829045 },
     },
    .count    = 2,
    .agingCfg = &aging_cfg_nsp
};


static cpr_versioned_voltage_plan gfx_vvp = {
    .rail     = CPR_RAIL_GFX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_19418509048 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_27618799637 },
     },
    .count    = 2,
    .agingCfg = &aging_cfg_gfx
};


static cpr_versioned_voltage_plan mss_vvp = {
    .rail     = CPR_RAIL_MSS,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_15859819535 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_10964855768 },
     },
    .count    = 2,
    .agingCfg = &aging_cfg_mss
};


static cpr_versioned_voltage_plan vdda_vvp = {
    .rail     = CPR_RAIL_VDDA,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_4914612450 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_8429959293 },
     },
    .count    = 2,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan mx_vvp = {
    .rail     = CPR_RAIL_MX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_21032932404 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_22514054256 },
     },
    .count    = 2,
    .agingCfg = &aging_cfg_mx
};


static cpr_versioned_voltage_plan mxc_vvp = {
    .rail     = CPR_RAIL_MXC,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_13886711214 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_16829462161 },
     },
    .count    = 2,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan lpi_mx_vvp = {
    .rail     = CPR_RAIL_LPI_MX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_4865986440 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_4865986440 },
     },
    .count    = 2,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan lpi_cx_vvp = {
    .rail     = CPR_RAIL_LPI_CX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_12530311290 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_12547009959 },
     },
    .count    = 2,
    .agingCfg = &aging_cfg_lpi_cx
};


static cpr_versioned_voltage_plan mm_vvp = {
    .rail     = CPR_RAIL_MM,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_11451373189 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_10940734866 },
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
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49 },
    .sensorsCount = 50,
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
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30 },
    .sensorsCount = 31,
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
    .sensors      = (uint8[]){ 0,1,2,3 },
    .sensorsCount = 4,
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
    .sensors      = (uint8[]){ 0,1,2,5,6,7,8,9,10,11,12,13,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36 },
    .sensorsCount = 33,
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
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51 },
    .sensorsCount = 52,
};


static cpr_hal_thread  mxc_thread = {
    .id   = 0,
    .cfg  = &mxc_thread_cfg,
};


static cpr_hal_thread_cfg nsp_thread_cfg = {
    .upThresh     = 2,
    .dnThresh     = 2,
    .consecUp     = 0,
    .consecDn     = 0,
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11 },
    .sensorsCount = 12,
};


static cpr_hal_thread  nsp_thread = {
    .id   = 0,
    .cfg  = &nsp_thread_cfg,
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
    .sensorsTotal        = 50,
    .bypassSensors       = NULL,
    .bypassSensorsCount  = 0,
    .disableSensors      = (uint8[]){ 1,2,3,5,6,7,8,9,10,11,12,14,21,32,33,34,35,36,46,47,48,49 },
    .disableSensorsCount = 22,
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
    .sensorsTotal        = 31,
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
    .sensorsTotal        = 4,
    .bypassSensors       = NULL,
    .bypassSensorsCount  = 0,
    .disableSensors      = NULL,
    .disableSensorsCount = 0,
    .refClk              = NULL,
    .ahbClk              = NULL,
};


static cpr_hal_controller  lpass_cpr3_controller = {
    .base                = 0x6e70000,
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
    .sensorsTotal        = 89,
    .bypassSensors       = (uint8[]){ 3,4,14,15,17,18,19,20,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88 },
    .bypassSensorsCount  = 60,
    .disableSensors      = (uint8[]){ 3,4,14,15,17,18,19,20,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88 },
    .disableSensorsCount = 60,
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
    .sensorsTotal        = 52,
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


static cpr_hal_controller_cfg nsp_cx_cpr3_controller_cfg = {
    .stepQuotMin         = 8,
    .stepQuotMax         = 12,
    .sensorsTotal        = 12,
    .bypassSensors       = NULL,
    .bypassSensorsCount  = 0,
    .disableSensors      = NULL,
    .disableSensorsCount = 0,
    .refClk              = NULL,
    .ahbClk              = NULL,
};


static cpr_hal_controller  nsp_cx_cpr3_controller = {
    .base                = 0x63c000,
    .type                = CPR_CONTROLLER_TYPE_HW_CL_ONLY,
    .cfg                 = &nsp_cx_cpr3_controller_cfg,
    .threads             = (cpr_hal_thread*[]){ &nsp_thread },
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


static cpr_rail cpr_rail_nsp_cfg = {
    .id               = CPR_RAIL_NSP,
    .name             = "NSP",
    .hal              = { .controller = &nsp_cx_cpr3_controller, .thread = &nsp_thread },
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
    .railCPRRevFuse    = {.count = 3, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC0 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BBC & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
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
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC0 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BBC & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
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
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC0 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BBC & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
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
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC0 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BBC & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_lpi_cx_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_LPI_CX,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_SW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 3, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC0 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BBC & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
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
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC0 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BBC & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_lpi_mx_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_LPI_MX,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_OPEN_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 3, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC0 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BBC & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
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
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC0 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BBC & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
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
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC0 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BBC & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
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
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC0 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BBC & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
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
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC0 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BBC & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
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
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC0 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BBC & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_mx_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_MX,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_SW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 3, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC0 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BBC & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
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
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC0 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BBC & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_mxc_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_MXC,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_SW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 3, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC0 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BBC & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
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
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC0 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BBC & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
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
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC0 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BBC & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
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
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC0 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BBC & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_nsp_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_NSP,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_HW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 3, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC0 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BBC & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_nsp_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_NSP,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_HW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 3, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC0 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BBC & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_vdda_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_VDDA,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_OPEN_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 3, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC0 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BBC & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
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
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC0 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BBC & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
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
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC0 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BBC & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
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
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC0 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BBC & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
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
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC0 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BBC & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
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
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC0 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BBC & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
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
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC0 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BBC & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
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
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 19, (1<<19)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC0 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<1) | (1<<0)},
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BBC & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 31, (1<<31)} } },
    .enable            = 0,
};


static cpr_misc_cfg misc_cfg = {
    .cprRev = {.count = 1, .data = (struct raw_fuse_data[]) { {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC4 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 19, (1<<19)} } }
};


cpr_settings cpr_settings_kailua =
{
    .hashValue        = voltage_plan_hash_value,

    .railVVPs         = (cpr_versioned_voltage_plan*[]) { &cx_vvp, &gfx_vvp, &lpi_cx_vvp, &lpi_mx_vvp, &mm_vvp, &mss_vvp, &mx_vvp, &mxc_vvp, &nav_ldo_vvp, &nsp_vvp, &vdda_vvp, &wmss_cx_1_vvp, &wmss_cx_2_vvp, &wmss_cx_3_vvp },
    .rails            = (cpr_rail*[]) { &cpr_rail_cx_cfg, &cpr_rail_gfx_cfg, &cpr_rail_lpi_cx_cfg, &cpr_rail_lpi_mx_cfg, &cpr_rail_mm_cfg, &cpr_rail_mss_cfg, &cpr_rail_mx_cfg, &cpr_rail_mxc_cfg, &cpr_rail_nav_ldo_cfg, &cpr_rail_nsp_cfg, &cpr_rail_vdda_cfg, &cpr_rail_wmss_cx_1_cfg, &cpr_rail_wmss_cx_2_cfg, &cpr_rail_wmss_cx_3_cfg },
    .railsCount       = 14,

    .controllers      = (cpr_hal_controller*[]) { &cpr3_controller, &cx_cpr3_controller, &gpu_cpr_controller, &lpass_cpr3_controller, &mmcx_cpr3_controller, &mx_cpr3_controller, &mxc_cpr3_controller, &nsp_cx_cpr3_controller },
    .controllersCount = 8,

    .enablements      = (cpr_enablement*[]) { &cpr_rail_cx_enablement_1_0_1_255, &cpr_rail_cx_enablement_2_0_2_255, &cpr_rail_gfx_enablement_1_0_1_255, &cpr_rail_gfx_enablement_2_0_2_255, &cpr_rail_lpi_cx_enablement_1_0_1_255, &cpr_rail_lpi_cx_enablement_2_0_2_255, &cpr_rail_lpi_mx_enablement_1_0_1_255, &cpr_rail_lpi_mx_enablement_2_0_2_255, &cpr_rail_mm_enablement_1_0_1_255, &cpr_rail_mm_enablement_2_0_2_255, &cpr_rail_mss_enablement_1_0_1_255, &cpr_rail_mss_enablement_2_0_2_255, &cpr_rail_mx_enablement_1_0_1_255, &cpr_rail_mx_enablement_2_0_2_255, &cpr_rail_mxc_enablement_1_0_1_255, &cpr_rail_mxc_enablement_2_0_2_255, &cpr_rail_nav_ldo_enablement_1_0_1_255, &cpr_rail_nav_ldo_enablement_2_0_2_255, &cpr_rail_nsp_enablement_1_0_1_255, &cpr_rail_nsp_enablement_2_0_2_255, &cpr_rail_vdda_enablement_1_0_1_255, &cpr_rail_vdda_enablement_2_0_2_255, &cpr_rail_wmss_cx_1_enablement_1_0_1_255, &cpr_rail_wmss_cx_1_enablement_2_0_2_255, &cpr_rail_wmss_cx_2_enablement_1_0_1_255, &cpr_rail_wmss_cx_2_enablement_2_0_2_255, &cpr_rail_wmss_cx_3_enablement_1_0_1_255, &cpr_rail_wmss_cx_3_enablement_2_0_2_255 },
    .enablementsCount = 28,

    .miscCfg          = &misc_cfg,
};

