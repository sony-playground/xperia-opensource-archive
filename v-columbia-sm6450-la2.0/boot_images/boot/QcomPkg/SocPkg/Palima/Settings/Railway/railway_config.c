/*
===========================================================================

FILE:         railway_config.c

DESCRIPTION:
  Per target railway configurations

===========================================================================

                             Edit History

$Date: 2021/09/14 $

when       who     what, where, why
--------   ---     --------------------------------------------------------

===========================================================================
             Copyright (c) 2018, 2021 Qualcomm Technologies, Incorporated.
                    All Rights Reserved.
              QUALCOMM Proprietary and Confidential
===========================================================================
*/

/* -----------------------------------------------------------------------
**                           INCLUDES
** ----------------------------------------------------------------------- */

#include "railway_config.h"
#include "pm_ldo.h"
#include "pm_smps.h"
#include "pm_version.h" 

/* -----------------------------------------------------------------------
**                           DATA
** ----------------------------------------------------------------------- */

//
// BEGIN config data; should migrate to the system enumeration data method
//
static railway_config_data_t temp_config_data =
{
    .rails     = (railway_rail_config_t[])
    {
        //Must init Mx1 (aka MxA) first, as voting on the other rails will cause Mx changes to occur.
        {
            .vreg_name = "vddmx",

            // SMPS6H
            .pmic_chip_id   = 7,
            .pmic_peripheral_index = PM_SMPS_6,

            .pmic_volt_func = pm_smps_volt_level,

            .initial_corner = RAILWAY_NO_REQUEST,
            .default_retention_uv = 568000,
        },
        //Must init MxC first, as voting on the other rails will cause Mx changes to occur.
        {
            .vreg_name = "vddmxc",

            // SMPS2C
            .pmic_chip_id   = 2,
            .pmic_peripheral_index = PM_SMPS_2,

            .pmic_volt_func = pm_smps_volt_level,

            .initial_corner = RAILWAY_NO_REQUEST,
            .default_retention_uv = 568000,
        },
        // VDDCX
        {
            .vreg_name = "vddcx",

            // SMPS6C
            .pmic_chip_id   = 2,
            .pmic_peripheral_index = PM_SMPS_6,

            .pmic_volt_func = pm_smps_volt_level,

            .initial_corner = RAILWAY_NO_REQUEST,
            .default_retention_uv = 352000,
        },

        // VDDA_EBI
        {
            .vreg_name = "vdda_ebi",

            // SMPS2H
            .pmic_chip_id   = 7,
            .pmic_peripheral_index = PM_SMPS_2,

            .pmic_volt_func = pm_smps_volt_level,

            .initial_corner = RAILWAY_RETENTION,
            .default_retention_uv = 352000,
        },

        // VDD_LPI_MX
        {
            .vreg_name = "vdd_lpi_mx",

            // LDO1H
            .pmic_chip_id   = 7,
            .pmic_peripheral_index = PM_LDO_1,

            .pmic_volt_func = NULL, // This rail is to just support PMIC driver to query corner voltage, and Railway driver does not call PMIC API to program its voltage.

            .initial_corner = RAILWAY_NO_REQUEST,
            .default_retention_uv = 568000,
        },

        // VDD_LPI_CX
        {
            .vreg_name = "vdd_lpi_cx",

            // LDO8B
            .pmic_chip_id   = 1,
            .pmic_peripheral_index = PM_LDO_8,

            .pmic_volt_func = pm_ldo_volt_level,

            .initial_corner = RAILWAY_NO_REQUEST,
            .default_retention_uv = 352000,
        },

    },

    .num_rails = 6,
};
//
// END config data
//

railway_config_data_t * RAILWAY_CONFIG_DATA = &temp_config_data;

void get_railway_cfg(void)
{
}