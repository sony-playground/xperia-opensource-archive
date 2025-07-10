/*
===========================================================================

FILE:         railway_config.c

DESCRIPTION:
  Per target railway configurations

===========================================================================

                             Edit History

$Date: 2021/10/28 $

when       who     what, where, why
--------   ---     --------------------------------------------------------

===========================================================================
             Copyright (c) 2021 Qualcomm Technologies, Incorporated.
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


#define SDAM1_MEM88_ADDR 0x7098
#define TOKEI_SLAVE_ID 0x0

uint8 g_is_fillmore_pro;
railway_config_data_t * RAILWAY_CONFIG_DATA;

/* -----------------------------------------------------------------------
**                           DATA
** ----------------------------------------------------------------------- */

//
// BEGIN config data; should migrate to the system enumeration data method
//FILLMORE_TODO: Recompare once AOP PMIC changes are in
static railway_config_data_t temp_config_data_fillmore =
{
    .rails     = (railway_rail_config_t[])
    {
        //Must init Mx1 (aka MxA) first, as voting on the other rails will cause Mx changes to occur.
        {
            .vreg_name = "vddmx",
			
			// SMPS10C
            .pmic_chip_id   = 2,
            .pmic_peripheral_index = PM_SMPS_10,

            .pmic_volt_func = pm_smps_volt_level,

            .initial_corner = RAILWAY_NO_REQUEST,
            .default_retention_uv = 568000,
        },
        //Must init MxC first, as voting on the other rails will cause Mx changes to occur.
        {
            .vreg_name = "vddmxc",

            // SMPS4C
            .pmic_chip_id   = 2,
            .pmic_peripheral_index = PM_SMPS_4,

            .pmic_volt_func = pm_smps_volt_level,

            .initial_corner = RAILWAY_NO_REQUEST,
            .default_retention_uv = 568000,
        },
        // VDDCX
        {
            .vreg_name = "vddcx",

            // SMPS8C
            .pmic_chip_id   = 2,
            .pmic_peripheral_index = PM_SMPS_8,

            .pmic_volt_func = pm_smps_volt_level,

            .initial_corner = RAILWAY_NO_REQUEST,
            .default_retention_uv = 352000,
        },

        // VDDA_EBI
        {
            .vreg_name = "vdda_ebi",

            // SMPS2B
            .pmic_chip_id   = 1,
            .pmic_peripheral_index = PM_SMPS_2,

            .pmic_volt_func = pm_smps_volt_level,

            .initial_corner = RAILWAY_RETENTION,
            .default_retention_uv = 352000,
        },

        // VDD_LPI_MX
        {
            .vreg_name = "vdd_lpi_mx",

            // LDO4B
            .pmic_chip_id   = 1,
            .pmic_peripheral_index = PM_LDO_4,

            .pmic_volt_func = NULL, // This rail is to just support PMIC driver to query corner voltage, and Railway driver does not call PMIC API to program its voltage.

            .initial_corner = RAILWAY_NO_REQUEST,
            .default_retention_uv = 568000,
        },

        // VDD_LPI_CX
        {
            .vreg_name = "vdd_lpi_cx",

            // LDO5B
            .pmic_chip_id   = 1,
            .pmic_peripheral_index = PM_LDO_5,        

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
static railway_config_data_t temp_config_data_fillmore_pro =
{
    .rails     = (railway_rail_config_t[])
    {
        //Must init Mx1 (aka MxA) first, as voting on the other rails will cause Mx changes to occur.
        {
            .vreg_name = "vddmx",

            // SMPS1L
            .pmic_chip_id   = 11,
            .pmic_peripheral_index = PM_SMPS_1,

            .pmic_volt_func = pm_smps_volt_level,

            .initial_corner = RAILWAY_NO_REQUEST,
            .default_retention_uv = 568000,
        },
        //Must init MxC first, as voting on the other rails will cause Mx changes to occur.
        {
            .vreg_name = "vddmxc",

            // SMPS1M
            .pmic_chip_id   = 12,
            .pmic_peripheral_index = PM_SMPS_1,

            .pmic_volt_func = pm_smps_volt_level,

            .initial_corner = RAILWAY_NO_REQUEST,
            .default_retention_uv = 568000,
        },
        // VDDCX
        {
            .vreg_name = "vddcx",

            // SMPS8C
            .pmic_chip_id   = 2,
            .pmic_peripheral_index = PM_SMPS_8,

            .pmic_volt_func = pm_smps_volt_level,

            .initial_corner = RAILWAY_NO_REQUEST,
            .default_retention_uv = 352000,
        },

        // VDDA_EBI
        {
            .vreg_name = "vdda_ebi",

            // SMPS2B
            .pmic_chip_id   = 1,
            .pmic_peripheral_index = PM_SMPS_2,

            .pmic_volt_func = pm_smps_volt_level,

            .initial_corner = RAILWAY_RETENTION,
            .default_retention_uv = 352000,
        },

        // VDD_LPI_MX
        {
            .vreg_name = "vdd_lpi_mx",

            // LDO4B
            .pmic_chip_id   = 1,
            .pmic_peripheral_index = PM_LDO_4,

            .pmic_volt_func = NULL, // This rail is to just support PMIC driver to query corner voltage, and Railway driver does not call PMIC API to program its voltage.

            .initial_corner = RAILWAY_NO_REQUEST,
            .default_retention_uv = 568000,
        },

        // VDD_LPI_CX
        {
            .vreg_name = "vdd_lpi_cx",

            // LDO5B
            .pmic_chip_id   = 1,
            .pmic_peripheral_index = PM_LDO_5,        

            .pmic_volt_func = pm_ldo_volt_level,

            .initial_corner = RAILWAY_NO_REQUEST,
            .default_retention_uv = 352000,
        },

    },

    .num_rails = 6,
};


void get_railway_cfg(void)
{
	/* RUMI seeing crash, so first check if TOKEI PMIC present or not */
	pm_model_type g_pmic_model = pm_get_pmic_model(TOKEI_SLAVE_ID);
	if(g_pmic_model == PMIC_IS_PMK8350)
	{
		/* TOKEI pmic present, get pmic config */
		/* Read sdam1.mem088 to identify fillmore pro vs fillmore */
		pm_err_flag_type err_flag = pm_comm_read_byte(TOKEI_SLAVE_ID, SDAM1_MEM88_ADDR, &g_is_fillmore_pro);
		CORE_VERIFY(err_flag == PM_ERR_FLAG_SUCCESS);		
	}
	else
	{
		/* PMIC_IS_UNKNOWN is returned(TOKEI PMIC not present/RUMI), default to normal PMIC cfg, NOT pro*/
		g_is_fillmore_pro = 0;
	}

	if(g_is_fillmore_pro)
	{
		RAILWAY_CONFIG_DATA = &temp_config_data_fillmore_pro;
	}
	else
	{
		RAILWAY_CONFIG_DATA = &temp_config_data_fillmore;
	}
}