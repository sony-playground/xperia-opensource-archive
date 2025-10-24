/**
 * @file:  cpr_defs.h
 * @brief:
 *
 * Copyright (c) 2015-2019 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 * $DateTime: 2022/08/18 10:15:46 $
 * $Header: //components/rel/core.boot/6.1.1/QcomPkg/Include/cpr_defs.h#1 $
 * $Change: 39147961 $
 */
#ifndef CPR_DEFS_H
#define CPR_DEFS_H

#include "comdef.h"
#include "railway.h"

typedef enum
{
    CPR_VOLTAGE_MODE_OFF                 = RAILWAY_NO_REQUEST,
    CPR_VOLTAGE_MODE_RETENTION           = RAILWAY_RETENTION,
    CPR_VOLTAGE_MODE_MIN_SVS             = RAILWAY_SVS_MIN,
    CPR_VOLTAGE_MODE_LOW_SVS_D2          = RAILWAY_SVS_LOW_D2,
    CPR_VOLTAGE_MODE_LOW_SVS_D1          = RAILWAY_SVS_LOW_D1,
    CPR_VOLTAGE_MODE_LOW_SVS_D0          = RAILWAY_SVS_LOW_D0,
    CPR_VOLTAGE_MODE_LOW_SVS             = RAILWAY_SVS_LOW,
    CPR_VOLTAGE_MODE_LOW_SVS_P1          = RAILWAY_SVS_LOW_P1,
    CPR_VOLTAGE_MODE_LOW_SVS_L1          = RAILWAY_SVS_LOW_L1,
    CPR_VOLTAGE_MODE_LOW_SVS_L2          = RAILWAY_SVS_LOW_L2,
    CPR_VOLTAGE_MODE_SVS                 = RAILWAY_SVS,
    CPR_VOLTAGE_MODE_SVS_L0              = RAILWAY_SVS_L0,
    CPR_VOLTAGE_MODE_SVS_L1              = RAILWAY_SVS_HIGH,
    CPR_VOLTAGE_MODE_SVS_L2              = RAILWAY_SVS_SUPER_HIGH,
    CPR_VOLTAGE_MODE_NOMINAL             = RAILWAY_NOMINAL,
    CPR_VOLTAGE_MODE_NOMINAL_L0          = RAILWAY_NOMINAL_L0,
    CPR_VOLTAGE_MODE_NOMINAL_L1          = RAILWAY_NOMINAL_L1,
    CPR_VOLTAGE_MODE_NOMINAL_L2          = RAILWAY_NOMINAL_L2,
    CPR_VOLTAGE_MODE_TURBO               = RAILWAY_TURBO,
    CPR_VOLTAGE_MODE_TURBO_L0            = RAILWAY_TURBO_L0,
    CPR_VOLTAGE_MODE_TURBO_L1            = RAILWAY_TURBO_L1,
    CPR_VOLTAGE_MODE_TURBO_L2            = RAILWAY_TURBO_L2,
    CPR_VOLTAGE_MODE_TURBO_L3            = RAILWAY_TURBO_L3,
    CPR_VOLTAGE_MODE_SUPER_TURBO         = RAILWAY_SUPER_TURBO,
    CPR_VOLTAGE_MODE_SUPER_TURBO_NO_CPR  = RAILWAY_SUPER_TURBO_NO_CPR,

    CPR_VOLTAGE_MODE_COUNT               = RAILWAY_CORNERS_COUNT,
} cpr_voltage_mode;

typedef enum
{
    // Core rails
    CPR_RAIL_MX     = 0x100,
    CPR_RAIL_CX,
    CPR_RAIL_MSS,
    CPR_RAIL_GFX,
    CPR_RAIL_VDDA,
    CPR_RAIL_WLAN,
    CPR_RAIL_MM,
    CPR_RAIL_MXC,
    CPR_RAIL_NSP,

    // APC rails
    CPR_RAIL_APC0   = 0x200,
    CPR_RAIL_APC1,
    CPR_RAIL_APC2,
    CPR_RAIL_APC3,
    CPR_RAIL_APC4,
    CPR_RAIL_APC5,
    CPR_RAIL_CBF,
    CPR_RAIL_APCC_LVT,
    CPR_RAIL_APCC_SLVT,
    CPR_RAIL_APCC_M4M,

    // SSC rails
    CPR_RAIL_SSC_MX = 0x300,
    CPR_RAIL_SSC_CX,

    // LPI rails
    CPR_RAIL_LPI_MX = 0x400,
    CPR_RAIL_LPI_CX,

    CPR_RAIL_MSS_LDO = 0x500,
    CPR_RAIL_TURING_LDO,
    CPR_RAIL_NAV_LDO,

    CPR_RAIL_WMSS_CX_1 = 0x600,
    CPR_RAIL_WMSS_CX_2,
    CPR_RAIL_WMSS_CX_3,

    CPR_RAIL_WMSS_CX_SUB6_0 = 0x700,
    CPR_RAIL_WMSS_CX_SUB6_1,
    CPR_RAIL_WMSS_CX_SUB6_2,
    CPR_RAIL_WMSS_CX_SUB6_3,
    CPR_RAIL_WMSS_CX_SUB6_4,
    CPR_RAIL_WMSS_CX_SUB6_5,
    CPR_RAIL_WMSS_CX_SUB6_6,
    CPR_RAIL_WMSS_CX_SUB6_7,
    CPR_RAIL_WMSS_CX_MMWAVE_0,
    CPR_RAIL_WMSS_CX_MMWAVE_1,
    CPR_RAIL_WMSS_CX_MMWAVE_2,
    CPR_RAIL_WMSS_CX_MMWAVE_3,
    CPR_RAIL_WMSS_CX_MMWAVE_4,
    CPR_RAIL_WMSS_CX_MMWAVE_5,
    CPR_RAIL_WMSS_CX_MMWAVE_6,
    CPR_RAIL_WMSS_CX_MMWAVE_7
} cpr_domain_id;

typedef enum {
    CPR_DOMAIN_TYPE_MODE_BASED,
    CPR_DOMAIN_TYPE_FREQ_BASED
} cpr_domain_type;

typedef struct
{
    cpr_domain_type type;
    union
    {
        cpr_voltage_mode mode;
        uint32 freq;
    } u;
} cpr_domain_info;

typedef cpr_domain_id cpr_rail_id_t;
typedef cpr_voltage_mode cpr_voltage_mode_t;

#endif //CPR_DEFS_H
