/**
 * @file:  railway_target.c
 * @brief: Railway target specific config and initialization.
 *
 * Copyright (c) 2015-2017 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 * $DateTime: 2021/09/12 20:53:48 $
 * $Header: //components/rel/core.boot/6.0/QcomPkg/SocPkg/Palima/Library/RailwayTargetLib/railway_target.c#1 $
 * $Change: 32852088 $
 */
#include "railway_config.h"
#include "railway_internal.h"
#include "CoreVerify.h"
#include "railway.h"
#include "cpr_fuses_hwio.h"
#include "msmhwio.h"
#include "aoss_misc_hwio.h"

typedef struct
{
    uint32 address;
    uint8 offset;
    uint8 mask;
} fuse_t;

typedef struct
{
    const uint32 *retention_table;
    const fuse_t  fuse;
} pvs_data_t;

/* -----------------------------------------------------------------------
**                           FUNCTIONS
** ----------------------------------------------------------------------- */

static uint32 read_fuse_value(const fuse_t *fuse)
{
    return ( __inpdw(fuse->address) >> fuse->offset ) & (uint32)fuse->mask;
}

static uint32 set_sleep_voltage(int rail_id, pvs_data_t *pvs_data_ptr)
{
    uint32 lookup_val = read_fuse_value( &pvs_data_ptr->fuse );
    CORE_VERIFY(lookup_val < 8);

    railway_set_retention_voltage(rail_id, pvs_data_ptr->retention_table[lookup_val]);

    return lookup_val;
}

void mx_pre_cb(const railway_settings *settings, void* cookie)
{
    uint32 acc = 0;
    railway_rail_state_t *rail_data = &railway.rail_state[mx_rail_id];

    if ((rail_data->constrained_target.mode >= RAILWAY_TURBO) &&
        (rail_data->current_active.mode < RAILWAY_TURBO))
    {
        //Set ACC bits
        acc = 1;
    }
    else if ((rail_data->constrained_target.mode <= RAILWAY_TURBO) &&
        (rail_data->current_active.mode > RAILWAY_TURBO))
    {
        //Unset ACC bits
        acc = 0;
    }

    HWIO_MXA_MEM_RA_SEL_COMP_DATA_OUTM(
            HWIO_MXA_MEM_RA_SEL_COMP_DATA_COMP_OUTPUT_OVERRIDE_VAL_BMSK,
            acc<<HWIO_MXA_MEM_RA_SEL_COMP_DATA_COMP_OUTPUT_OVERRIDE_VAL_SHFT);
    HWIO_MXA_MEM_RA_SEL_COMP_DATA_OUTM(
            HWIO_MXA_MEM_RA_SEL_COMP_DATA_COMP_OUTPUT_OVERRIDE_EN_BMSK,
            acc<<HWIO_MXA_MEM_RA_SEL_COMP_DATA_COMP_OUTPUT_OVERRIDE_EN_SHFT);
    HWIO_MXC_MEM_RA_SEL_COMP_DATA_OUTM(
            HWIO_MXC_MEM_RA_SEL_COMP_DATA_COMP_OUTPUT_OVERRIDE_VAL_BMSK,
            acc<<HWIO_MXC_MEM_RA_SEL_COMP_DATA_COMP_OUTPUT_OVERRIDE_VAL_SHFT);
    HWIO_MXC_MEM_RA_SEL_COMP_DATA_OUTM(
            HWIO_MXC_MEM_RA_SEL_COMP_DATA_COMP_OUTPUT_OVERRIDE_EN_BMSK,
            acc<<HWIO_MXC_MEM_RA_SEL_COMP_DATA_COMP_OUTPUT_OVERRIDE_EN_SHFT);
}

void railway_target_init(void)
{
    cx_rail_id     = railway_get_rail_id("vddcx");
    mx_rail_id     = railway_get_rail_id("vddmx");
    mxc_rail_id    = railway_get_rail_id("vddmxc");
    ebi_rail_id    = railway_get_rail_id("vdda_ebi");
    ssc_cx_rail_id = railway_get_rail_id("vdd_lpi_cx");

    //init time request for lowest active level
    railway_init_voter(cx_rail_id, RAILWAY_RPM_CX_VOTER_ID, RAILWAY_NOMINAL);
    railway_init_voter(mx_rail_id, RAILWAY_RPM_MX_VOTER_ID, RAILWAY_NOMINAL);
    railway_init_voter(mxc_rail_id, RAILWAY_RPM_MX_VOTER_ID, RAILWAY_NOMINAL);
    railway_init_voter(ebi_rail_id, RAILWAY_RPM_EBI_VOTER_ID, RAILWAY_SVS );
    railway_init_voter(ssc_cx_rail_id, RAILWAY_RPM_SSC_CX_VOTER_ID,
            RAILWAY_SVS_MIN);

    railway_set_callback(mx_rail_id, RAILWAY_PRECHANGE_CB, mx_pre_cb, NULL);
}
