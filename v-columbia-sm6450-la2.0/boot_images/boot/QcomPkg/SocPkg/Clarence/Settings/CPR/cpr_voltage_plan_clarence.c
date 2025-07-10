/*******************************************************************************
 *
 * Copyright (c) 2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 * THIS IS AUTO-GENERATED CPR CONFIG FILE FOR clarence.
 *
 * DateTime: 2023/12/05 05:58:30
 *
 *******************************************************************************/
#include "cpr_data.h"
#include "cpr_image_target_init.h"
#include "cpr_target_hwio.h"


//hash value of Voltage Plan file (extracted all cell values)
static char voltage_plan_hash_value[] = "C5C4C68379F33502B237DDE6C5F4B5D3";


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


static cpr_margin_cfg margins_236086 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -10000, .closedLoop =   43000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   45000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_8139354119 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  5, .quotient =  482 },
                                      { .ro =  8, .quotient =  305 },
                                      { .ro =  9, .quotient =  312 },
                                      { .ro = 12, .quotient =  172 },
                                      { .ro = 14, .quotient =  312 } },
};


static cpr_fuse_data  fuses_3607267309 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION13, CPR0_TARG_VOLT_SVS2) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR0_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_218086 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -10000, .closedLoop =   38000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -12000, .closedLoop =   47000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_10964677915 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  5, .quotient =  665 },
                                      { .ro =  8, .quotient =  454 },
                                      { .ro =  9, .quotient =  462 },
                                      { .ro = 12, .quotient =  303 },
                                      { .ro = 14, .quotient =  460 } },
};


static cpr_fuse_data  fuses_2170855085 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION13, CPR0_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR0_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_182086 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -20000, .closedLoop =   35000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -24000, .closedLoop =   43000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_5859481069 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  5, .quotient =  782 },
                                      { .ro =  8, .quotient =  553 },
                                      { .ro =  9, .quotient =  564 },
                                      { .ro = 12, .quotient =  389 },
                                      { .ro = 14, .quotient =  550 } },
};


static cpr_fuse_data  fuses_3171792585 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR0_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_268086 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   -2000, .closedLoop =   36000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -24000, .closedLoop =   36000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_9856993243 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  901 },
                                      { .ro =  4, .quotient =  809 },
                                      { .ro =  8, .quotient =  695 },
                                      { .ro =  9, .quotient =  709 } },
};


static cpr_fuse_data  fuses_4158495916 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION13, CPR0_TARG_VOLT_NOM_5_1), CPR_FUSE_MAPPING(CALIBRATION12, CPR0_TARG_VOLT_NOM_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR0_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_252086 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   -8000, .closedLoop =   32000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -28000, .closedLoop =   37000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_5452524593 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1003 },
                                      { .ro =  4, .quotient =  900 },
                                      { .ro =  8, .quotient =  780 },
                                      { .ro =  9, .quotient =  794 } },
};


static cpr_fuse_data  fuses_1952839088 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION13, CPR0_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_margin_cfg margins_354086 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   10000, .closedLoop =   46000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   -8000, .closedLoop =   55000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_7159562043 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1070 },
                                      { .ro =  4, .quotient =  960 },
                                      { .ro =  8, .quotient =  836 },
                                      { .ro =  9, .quotient =  850 } },
};


static cpr_fuse_data  fuses_7139878447 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION9, CPR0_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION13, CPR0_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_margin_cfg margins_218087 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -20000, .closedLoop =   28000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -32000, .closedLoop =   32000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_6366453001 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1217 },
                                      { .ro =  4, .quotient = 1091 },
                                      { .ro =  8, .quotient =  957 },
                                      { .ro =  9, .quotient =  973 } },
};


static cpr_fuse_data  fuses_5309047477 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION9, CPR0_TARG_VOLT_TURL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION10, CPR0_TARG_VOLT_OFFSET_TURL1_4), CPR_FUSE_MAPPING(CALIBRATION9, CPR0_TARG_VOLT_OFFSET_TURL1_3_0) } } },
};


static cpr_kv_cfg  kvs_18707358628 =
{
    .count = 7,
    .kvs   = (cpr_kv[]) { { .ro =  2, .kv =  278 },
                                { .ro =  4, .kv =  272 },
                                { .ro =  5, .kv =  289 },
                                { .ro =  8, .kv =  265 },
                                { .ro =  9, .kv =  266 },
                                { .ro = 12, .kv =  241 },
                                { .ro = 14, .kv =  266 } },
};


/*
 * CX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_10045887300 =
{
    .modesCount      = 8,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_18707358628,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1 },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref = 352000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  352000, .floor =  352000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 556000, .freqDelta =       0, .fuses = &fuses_3607267309, .quotients = &quotients_8139354119, .margins = &margins_236086,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  656000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_2170855085, .quotients = &quotients_10964677915, .margins = &margins_218086,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  732000, .floor =  552000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_3171792585, .quotients = &quotients_5859481069, .margins = &margins_182086,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  796000, .floor =  600000, .freq =       0, .interplEnabled = 46} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_4158495916, .quotients = &quotients_9856993243, .margins = &margins_268086,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  824000, .floor =  656000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_1952839088, .quotients = &quotients_5452524593, .margins = &margins_252086,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  696000, .freq =       0, .interplEnabled = 60} } },

        // TURBO
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_7139878447, .quotients = &quotients_7159562043, .margins = &margins_354086,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  716000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref = 904000, .freqDelta =       0, .fuses = &fuses_5309047477, .quotients = &quotients_6366453001, .margins = &margins_218087,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  968000, .floor =  768000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_version  ver_ANY_1_0_1_255 = { .foundry = CPR_FOUNDRY_ANY, .min = CPR_CHIPINFO_VERSION(1,0), .max = CPR_CHIPINFO_VERSION(1,255) };


static cpr_margin_cfg margins_162086 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -20000, .closedLoop =   32000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   24000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_9160277692 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  275 },
                                      { .ro =  9, .quotient =  286 },
                                      { .ro = 10, .quotient =  150 },
                                      { .ro = 14, .quotient =  279 } },
};


static cpr_fuse_data  fuses_3858684739 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR1_TARG_VOLT_SVS3) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR1_TARG_VOLT_OFFSET_SVS3) } } },
};


static cpr_margin_cfg margins_244086 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -10000, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =    8000, .closedLoop =   40000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_7101552781 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  305 },
                                      { .ro =  9, .quotient =  312 },
                                      { .ro = 10, .quotient =  169 },
                                      { .ro = 14, .quotient =  312 } },
};


static cpr_fuse_data  fuses_313137749 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR1_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_212086 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -18000, .closedLoop =   40000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =    4000, .closedLoop =   38000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
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


static cpr_fuse_data  fuses_4548009007 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR1_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR1_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_186086 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -24000, .closedLoop =   44000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   -4000, .closedLoop =   28000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
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


static cpr_fuse_data  fuses_1082848685 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR1_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_302086 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -20000, .closedLoop =   40000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =    8000, .closedLoop =   42000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
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


static cpr_fuse_data  fuses_6429118265 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR1_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR1_TARG_VOLT_OFFSET_NOM_4_2), CPR_FUSE_MAPPING(CALIBRATION15, CPR1_TARG_VOLT_OFFSET_NOM_1_0) } } },
};


static cpr_margin_cfg margins_324086 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -10000, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   16000, .closedLoop =   36000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
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


static cpr_fuse_data  fuses_6802656916 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION10, CPR1_TARG_VOLT_NOML1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR1_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_kv_cfg  kvs_12349781790 =
{
    .count = 6,
    .kvs   = (cpr_kv[]) { { .ro =  2, .kv =  287 },
                                { .ro =  3, .kv =  288 },
                                { .ro =  8, .kv =  267 },
                                { .ro =  9, .kv =  268 },
                                { .ro = 10, .kv =  235 },
                                { .ro = 14, .kv =  270 } },
};


/*
 * MSS Voltage Plan
 */
static cpr_voltage_plan voltage_plan_11386718975 =
{
    .modesCount      = 6,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_12349781790,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1 },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS_D1
        {.fref = 540000, .freqDelta =       0, .fuses = &fuses_3858684739, .quotients = &quotients_9160277692, .margins = &margins_162086,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  640000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 556000, .freqDelta =       0, .fuses = &fuses_313137749, .quotients = &quotients_7101552781, .margins = &margins_244086,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  656000, .floor =  516000, .freq =       0, .interplEnabled = 18} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_4548009007, .quotients = &quotients_13594457200, .margins = &margins_212086,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  732000, .floor =  552000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_1082848685, .quotients = &quotients_10357983203, .margins = &margins_186086,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  796000, .floor =  600000, .freq =       0, .interplEnabled = 46} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_6429118265, .quotients = &quotients_8682795327, .margins = &margins_302086,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  824000, .floor =  656000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_6802656916, .quotients = &quotients_7768896922, .margins = &margins_324086,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  696000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_50 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 } }
};


static cpr_fuse_data  fuses_6058320704 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION12, CPR4_TARG_VOLT_OFFSET_SVS2_4_3), CPR_FUSE_MAPPING(CALIBRATION11, CPR4_TARG_VOLT_OFFSET_SVS2_2_0) } } },
};


static cpr_quotient_cfg  quotients_7951826470 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  0, .quotient =  658 },
                                      { .ro =  4, .quotient =  454 },
                                      { .ro =  6, .quotient =  505 } },
};


static cpr_quotient_cfg  quotients_5577016373 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  0, .quotient =  755 },
                                      { .ro =  4, .quotient =  526 },
                                      { .ro =  6, .quotient =  588 } },
};


static cpr_fuse_data  fuses_5363218938 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION10, CPR4_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION11, CPR4_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_344086 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   52000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   60000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_5255497865 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  0, .quotient =  893 },
                                      { .ro =  4, .quotient =  630 },
                                      { .ro =  6, .quotient =  711 } },
};


static cpr_fuse_data  fuses_2941978161 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR4_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION11, CPR4_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_164050 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   52000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_8135290379 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  0, .quotient =  893 },
                                      { .ro =  3, .quotient =  689 },
                                      { .ro =  4, .quotient =  630 },
                                      { .ro =  6, .quotient =  711 } },
};


static cpr_fuse_data  fuses_3039350174 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR4_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION11, CPR4_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_256086 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   16000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   12000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_8811437170 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  0, .quotient = 1050 },
                                      { .ro =  3, .quotient =  797 },
                                      { .ro =  4, .quotient =  750 },
                                      { .ro =  6, .quotient =  851 } },
};


static cpr_fuse_data  fuses_4454585393 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR4_TARG_VOLT_NOML1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION11, CPR4_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_margin_cfg margins_360086 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   32000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   48000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_7584357329 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  0, .quotient = 1082 },
                                      { .ro =  3, .quotient =  818 },
                                      { .ro =  4, .quotient =  751 },
                                      { .ro =  6, .quotient =  850 } },
};


static cpr_fuse_data  fuses_6366063426 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION10, CPR4_TARG_VOLT_TURL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION11, CPR4_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_margin_cfg margins_264086 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   32000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_14816031439 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  0, .quotient = 1151 },
                                      { .ro =  3, .quotient =  867 },
                                      { .ro =  4, .quotient =  829 },
                                      { .ro =  6, .quotient =  943 } },
};


static cpr_fuse_data  fuses_7010169925 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION10, CPR4_TARG_VOLT_TURL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION11, CPR4_TARG_VOLT_OFFSET_TURL1_4_1), CPR_FUSE_MAPPING(CALIBRATION10, CPR4_TARG_VOLT_OFFSET_TURL1_0) } } },
};


static cpr_kv_cfg  kvs_6954345919 =
{
    .count = 4,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =  386 },
                                { .ro =  3, .kv =  261 },
                                { .ro =  4, .kv =  296 },
                                { .ro =  6, .kv =  339 } },
};


/*
 * MX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_18775065359 =
{
    .modesCount      = 9,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_6954345919,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1 },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref = 524000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  568000, .floor =  524000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS_D1
        {.fref = 716000, .freqDelta =       0, .fuses = &fuses_6058320704, .quotients = NULL, .margins = &margins_50,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  716000, .floor =  716000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 716000, .freqDelta =       0, .fuses = &fuses_6058320704, .quotients = &quotients_7951826470, .margins = &margins_50,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  716000, .floor =  716000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 716000, .freqDelta =       0, .fuses = &fuses_5363218938, .quotients = &quotients_5577016373, .margins = &margins_50,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  716000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_2941978161, .quotients = &quotients_5255497865, .margins = &margins_344086,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  796000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_3039350174, .quotients = &quotients_8135290379, .margins = &margins_164050,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  824000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_4454585393, .quotients = &quotients_8811437170, .margins = &margins_256086,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_6366063426, .quotients = &quotients_7584357329, .margins = &margins_360086,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_7010169925, .quotients = &quotients_14816031439, .margins = &margins_264086,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  800000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_20000 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -60000, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -80000, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 } }
};


static cpr_margin_cfg margins_25000 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -55000, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -80000, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 } }
};


static cpr_fuse_data  fuses_3052870533 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION12, CPR5_TARG_VOLT_SVSL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_margin_cfg margins_21000 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -40000, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -61000, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 } }
};


static cpr_fuse_data  fuses_5106903476 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION20, CPR5_TARG_VOLT_NOM_5), CPR_FUSE_MAPPING(CALIBRATION19, CPR5_TARG_VOLT_NOM_4_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_margin_cfg margins_18000 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -60000, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -78000, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 } }
};


static cpr_fuse_data  fuses_999010366 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR5_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


/*
 * LPI_MX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_14978588712 =
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
         .subModes        = (cpr_freq_data[]){ {.ceiling =  568000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS_D1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_50,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_50,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_20000,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_3052870533, .quotients = NULL, .margins = &margins_25000,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  792000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_5106903476, .quotients = NULL, .margins = &margins_21000,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  824000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_999010366, .quotients = NULL, .margins = &margins_18000,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  800000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_234086 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -12000, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   40000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_9864543760 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  441 },
                                      { .ro =  6, .quotient =  340 },
                                      { .ro =  8, .quotient =  275 },
                                      { .ro =  9, .quotient =  286 } },
};


static cpr_fuse_data  fuses_3258876441 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION12, CPR6_TARG_VOLT_SVS3) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION33, CPR6_TARG_VOLT_OFFSET_SVS3) } } },
};


static cpr_margin_cfg margins_207086 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -15000, .closedLoop =   44000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   32000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_7968837938 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  479 },
                                      { .ro =  6, .quotient =  369 },
                                      { .ro =  8, .quotient =  305 },
                                      { .ro =  9, .quotient =  312 } },
};


static cpr_fuse_data  fuses_4262293240 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION33, CPR6_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_213086 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -19000, .closedLoop =   55000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -12000, .closedLoop =   32000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_13660993195 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  644 },
                                      { .ro =  6, .quotient =  532 },
                                      { .ro =  8, .quotient =  454 },
                                      { .ro =  9, .quotient =  462 } },
};


static cpr_fuse_data  fuses_4492654367 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION22, CPR6_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION33, CPR6_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_216086 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -28000, .closedLoop =   71000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -28000, .closedLoop =   30000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_5050880251 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  754 },
                                      { .ro =  6, .quotient =  634 },
                                      { .ro =  8, .quotient =  553 },
                                      { .ro =  9, .quotient =  564 } },
};


static cpr_fuse_data  fuses_908476604 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION33, CPR6_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_279086 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -27000, .closedLoop =   72000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -32000, .closedLoop =   22000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_7340982356 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  901 },
                                      { .ro =  6, .quotient =  809 },
                                      { .ro =  8, .quotient =  695 },
                                      { .ro =  9, .quotient =  709 } },
};


static cpr_fuse_data  fuses_7303284098 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION22, CPR6_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION33, CPR6_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_333086 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -15000, .closedLoop =   62000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -16000, .closedLoop =   45000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_6153098906 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1070 },
                                      { .ro =  6, .quotient =  962 },
                                      { .ro =  8, .quotient =  836 },
                                      { .ro =  9, .quotient =  850 } },
};


static cpr_fuse_data  fuses_4550080802 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION22, CPR6_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION12, CPR6_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_kv_cfg  kvs_9987920228 =
{
    .count = 4,
    .kvs   = (cpr_kv[]) { { .ro =  2, .kv =  287 },
                                { .ro =  6, .kv =  279 },
                                { .ro =  8, .kv =  269 },
                                { .ro =  9, .kv =  269 } },
};


/*
 * LPI_CX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_15280750420 =
{
    .modesCount      = 7,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_9987920228,
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
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_3258876441, .quotients = &quotients_9864543760, .margins = &margins_234086,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  640000, .floor =  520000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 552000, .freqDelta =       0, .fuses = &fuses_4262293240, .quotients = &quotients_7968837938, .margins = &margins_207086,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  656000, .floor =  520000, .freq =       0, .interplEnabled = 18} } },

        // SVS
        {.fref = 624000, .freqDelta =       0, .fuses = &fuses_4492654367, .quotients = &quotients_13660993195, .margins = &margins_213086,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  736000, .floor =  552000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 680000, .freqDelta =       0, .fuses = &fuses_908476604, .quotients = &quotients_5050880251, .margins = &margins_216086,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  792000, .floor =  600000, .freq =       0, .interplEnabled = 46} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_7303284098, .quotients = &quotients_7340982356, .margins = &margins_279086,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  824000, .floor =  656000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_4550080802, .quotients = &quotients_6153098906, .margins = &margins_333086,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  720000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_19914 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -20000, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 } }
};


static cpr_fuse_data  fuses_3407686375 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION32, CPR9_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_fuse_data  fuses_1312892015 =
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
static cpr_voltage_plan voltage_plan_2187298979 =
{
    .modesCount      = 2,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1 },
    .modes           = (struct cpr_voltage_data[]) {
        // SVS
        {.fref = 624000, .freqDelta =       0, .fuses = &fuses_3407686375, .quotients = NULL, .margins = &margins_19914,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  736000, .floor =  552000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 680000, .freqDelta =       0, .fuses = &fuses_1312892015, .quotients = NULL, .margins = &margins_50,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  600000, .freq =       0, .interplEnabled = 0} } }},
};


/*
 * WMSS_CX_1 Voltage Plan
 */
static cpr_voltage_plan voltage_plan_9197092121 =
{
    .modesCount      = 3,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_NOMINAL },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS
        {.fref = 588000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_50,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  504000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 668000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_50,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  724000, .floor =  596000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_50,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  864000, .floor =  712000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_124914 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -25000, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =      0 } }
};


static cpr_fuse_data  fuses_1718781794 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION10, CPR3_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_margin_cfg margins_119914 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 2, .vpIdMax = 2,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -20000, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =      0 } }
};


static cpr_fuse_data  fuses_1532118070 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION10, CPR3_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


/*
 * VDDA Voltage Plan
 */
static cpr_voltage_plan voltage_plan_22156251060 =
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
        {.fref = 700000, .freqDelta =       0, .fuses = &fuses_1718781794, .quotients = NULL, .margins = &margins_124914,
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
        {.fref = 892000, .freqDelta =       0, .fuses = &fuses_1532118070, .quotients = NULL, .margins = &margins_119914,
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
    .sensorID             = 43,
    .kv                   = 100,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D38 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 20, (1<<27) | (1<<26) | (1<<25) | (1<<24) | (1<<23) | (1<<22) | (1<<21) | (1<<20)} } }
};


static cpr_aging_cfg  aging_cfg_mss =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_NOMINAL_L1,
    .sensorID             = 9,
    .kv                   = 107,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D40 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 23, (1<<30) | (1<<29) | (1<<28) | (1<<27) | (1<<26) | (1<<25) | (1<<24) | (1<<23)} } }
};


static cpr_aging_cfg  aging_cfg_mx =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO,
    .sensorID             = 34,
    .kv                   = 104,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = (uint8[]) {27, 28, 29, 37, 38},
    .bypassSensorIDsCount = 5,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 2, .data = (struct raw_fuse_data[]) {
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D58 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1) | (1<<0)},
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D54 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 30, (1<<31) | (1<<30)} } }
};


static cpr_aging_cfg  aging_cfg_lpi_cx =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO,
    .sensorID             = 5,
    .kv                   = 104,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 2, .data = (struct raw_fuse_data[]) {
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D64 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<0)},
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D60 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 25, (1<<31) | (1<<30) | (1<<29) | (1<<28) | (1<<27) | (1<<26) | (1<<25)} } }
};


/*
 * Versioned Voltage Plans
 */

static cpr_versioned_voltage_plan cx_vvp = {
    .rail     = CPR_RAIL_CX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_10045887300 },
     },
    .count    = 1,
    .agingCfg = &aging_cfg_cx
};


static cpr_versioned_voltage_plan mss_vvp = {
    .rail     = CPR_RAIL_MSS,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_11386718975 },
     },
    .count    = 1,
    .agingCfg = &aging_cfg_mss
};


static cpr_versioned_voltage_plan mx_vvp = {
    .rail     = CPR_RAIL_MX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_18775065359 },
     },
    .count    = 1,
    .agingCfg = &aging_cfg_mx
};


static cpr_versioned_voltage_plan lpi_mx_vvp = {
    .rail     = CPR_RAIL_LPI_MX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_14978588712 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan lpi_cx_vvp = {
    .rail     = CPR_RAIL_LPI_CX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_15280750420 },
     },
    .count    = 1,
    .agingCfg = &aging_cfg_lpi_cx
};


static cpr_versioned_voltage_plan wlan_vvp = {
    .rail     = CPR_RAIL_WLAN,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_2187298979 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan wmss_cx_1_vvp = {
    .rail     = CPR_RAIL_WMSS_CX_1,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_9197092121 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan vdda_vvp = {
    .rail     = CPR_RAIL_VDDA,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_22156251060 },
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
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44 },
    .sensorsCount = 45,
};


static cpr_hal_thread  cx_thread = {
    .id   = 0,
    .cfg  = &cx_thread_cfg,
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
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,30,31,32,33,34,35,36,39,40,41,42 },
    .sensorsCount = 38,
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
    .sensorsTotal        = 45,
    .bypassSensors       = NULL,
    .bypassSensorsCount  = 0,
    .disableSensors      = (uint8[]){ 3,4,11,12,13,14,23,24,35,44 },
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
    .sensorsTotal        = 43,
    .bypassSensors       = (uint8[]){ 27,28,29,37,38 },
    .bypassSensorsCount  = 5,
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
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D58 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 6, (1<<8) | (1<<7) | (1<<6)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_lpi_cx_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_LPI_CX,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_SW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D58 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 6, (1<<8) | (1<<7) | (1<<6)} } },
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
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D58 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 6, (1<<8) | (1<<7) | (1<<6)} } },
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
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D58 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 6, (1<<8) | (1<<7) | (1<<6)} } },
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
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D58 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 6, (1<<8) | (1<<7) | (1<<6)} } },
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
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D58 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 6, (1<<8) | (1<<7) | (1<<6)} } },
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
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D58 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 6, (1<<8) | (1<<7) | (1<<6)} } },
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
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D58 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 6, (1<<8) | (1<<7) | (1<<6)} } },
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
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D58 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 6, (1<<8) | (1<<7) | (1<<6)} } },
    .enable            = 0,
};


static cpr_misc_cfg misc_cfg = {
    .cprRev = {.count = 1, .data = (struct raw_fuse_data[]) { {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8D58 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 6, (1<<8) | (1<<7) | (1<<6)} } }
};


cpr_settings cpr_settings_clarence =
{
    .hashValue        = voltage_plan_hash_value,

    .railVVPs         = (cpr_versioned_voltage_plan*[]) { &cx_vvp, &lpi_cx_vvp, &lpi_mx_vvp, &mss_vvp, &mx_vvp, &nav_ldo_vvp, &vdda_vvp, &wlan_vvp, &wmss_cx_1_vvp },
    .rails            = (cpr_rail*[]) { &cpr_rail_cx_cfg, &cpr_rail_lpi_cx_cfg, &cpr_rail_lpi_mx_cfg, &cpr_rail_mss_cfg, &cpr_rail_mx_cfg, &cpr_rail_nav_ldo_cfg, &cpr_rail_vdda_cfg, &cpr_rail_wlan_cfg, &cpr_rail_wmss_cx_1_cfg },
    .railsCount       = 9,

    .controllers      = (cpr_hal_controller*[]) { &cpr3_controller, &cx_cpr3_controller, &lpass_cpr3_controller, &mx_cpr3_controller },
    .controllersCount = 4,

    .enablements      = (cpr_enablement*[]) { &cpr_rail_cx_enablement_1_0_1_255, &cpr_rail_lpi_cx_enablement_1_0_1_255, &cpr_rail_lpi_mx_enablement_1_0_1_255, &cpr_rail_mss_enablement_1_0_1_255, &cpr_rail_mx_enablement_1_0_1_255, &cpr_rail_nav_ldo_enablement_1_0_1_255, &cpr_rail_vdda_enablement_1_0_1_255, &cpr_rail_wlan_enablement_1_0_1_255, &cpr_rail_wmss_cx_1_enablement_1_0_1_255 },
    .enablementsCount = 9,

    .miscCfg          = &misc_cfg,
};

