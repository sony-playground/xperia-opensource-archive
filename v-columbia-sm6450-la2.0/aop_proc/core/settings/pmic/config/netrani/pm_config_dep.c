/*! \file pm_config_dep.c
 *
 *  \brief This file contains pmic resource dependencies.
 *
 *  &copy; Copyright 2016 - 2018 Qualcomm Technologies Inc, All Rights Reserved
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.

$Header:

when        who         what, where, why
--------    ---         ---------------------------------------------------
22/10/21    arua      Created by PMIC config tool V. PGA V. CR#
21/09/22    arua      vrm.qf alias updated
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/

#include "pm_config_interface.h"

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_b[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"smpb1", "vrm.cx"},
    {"smpb2", NULL},
    {"smpb3", "vrm.gfx"},
    {"smpb4", NULL},
    {"smpb5", "vrm.ebi"},
    {"smpb6", NULL},
    {"smpb7", NULL},
	{"smpb8", NULL},
	{"smpb9", NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_e[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"smpe1", "vrm.mss"},
    {"smpe2", NULL},
    {"smpe3", "vrm.mx"},
    {"smpe4", NULL},
    {"smpe5", NULL},
    {"smpe6", NULL},
    {"smpe7", NULL},
    {"smpe8", NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_g[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"smpg1", NULL},
    {"smpg2", NULL},
    {"smpg3", NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource bob_e[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"bobe1", NULL },
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_b[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"ldob1", NULL},
    {"ldob2", "vrm.lcx"},
    {"ldob3", NULL},
    {"ldob4", NULL},
    {"ldob5", NULL},
    {"ldob6", NULL},
    {"ldob7", NULL},
    {"ldob8", NULL},
    {"ldob9", "vrm.lmx"},
    {"ldob10", NULL},
    {"ldob11", NULL},
    {"ldob12", NULL},
    {"ldob13", NULL},
    {"ldob14", NULL},
    {"ldob15", NULL},
    {"ldob16", NULL},
    {"ldob17", NULL},
    {"ldob18", NULL},
    {"ldob19", NULL},
    {"ldob20", NULL},
    {"ldob21", NULL},
    {"ldob22", NULL},
    {"ldob23", "vrm.qf"},
    {"ldob24", NULL},
    {"ldob25", NULL},
    {"ldob26", NULL},
    {"ldob27", NULL},
    {"ldob28", NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_e[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"ldoe1", NULL},
    {"ldoe2", NULL},
    {"ldoe3", NULL},
    {"ldoe4", NULL},
    {"ldoe5", NULL},
    {"ldoe6", NULL},
    {"ldoe7", NULL},
    {"ldoe8", NULL},
    {"ldoe9", NULL},
    {"ldoe10", NULL},
    {"ldoe11", NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_g[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"ldog1", NULL},
    {"ldog2", NULL},
    {"ldog3", NULL},
    {"ldog4", NULL},
    {"ldog5", NULL},
    {"ldog6", NULL},
    {"ldog7", NULL},
};


// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource clk_a[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"clkdista", NULL},
    {NULL, NULL},
    {NULL, NULL},
    {"rfclka1", NULL},
    {"rfclka2", NULL},
    {"rfclka3", NULL},
    {"rfclka4", NULL},
    {"rfclka5", NULL},
    {"lnbclka1", "vrm.xob"},
    {"lnbclka2", NULL},
    {"lnbclka3", NULL},
    {NULL, NULL},
    {NULL, NULL},
    {"divclka1", NULL},
    {NULL, NULL},
    {"sleepclka1", NULL},
};


// Component Resource Child Depend Structure Creation


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *bob1_e_child_dep[] =
{
    &ldo_b[24],
    &ldo_b[25],
    &ldo_b[26],
    &ldo_b[27],
    &ldo_b[28],
    &ldo_e[4],
    &ldo_e[5],
    &ldo_e[6],
    &ldo_e[7],
    &ldo_e[9],
	&ldo_e[10],
	&ldo_e[11],
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps1_g_child_dep[] =
{
    &ldo_g[3],
    &ldo_g[5],
    &ldo_g[6],
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps7_b_child_dep[] =
{
    &ldo_b[3],
    &ldo_b[4],
    &ldo_b[6],
    &ldo_b[7],
    &ldo_b[9],
    &ldo_b[10],
    &ldo_b[11],
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps8_b_child_dep[] =
{
    &ldo_b[12],
    &ldo_b[13],
    &ldo_b[14],
    &ldo_g[2],
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps8_e_child_dep[] =
{
    &ldo_b[18],
    &ldo_b[19],
    &ldo_b[20],
    &ldo_b[21],
    &ldo_b[22],
    &ldo_b[23],
    &ldo_e[1],
    &ldo_e[8],
    &ldo_g[4],
};

// Component Resource Dependency Information
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info smps_dep_b[] =
{
    {NULL, NULL, 0, 0}, // Invalid zeroth array - NOT USED
    // S1
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // S2
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // S3
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // S4
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // S5
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // S6
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // S7
    {
        NULL, // parent resource
        smps7_b_child_dep, // child resource dependencies
        7, // num vreg children
        0, // num xob children
    },
	// S8
    {
        NULL, // parent resource
        smps8_b_child_dep, // child resource dependencies
        4, // num vreg children
        0, // num xob children
    },
	// S9
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info smps_dep_e[] =
{
    {NULL, NULL, 0, 0}, // Invalid zeroth array - NOT USED
    // S1
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // S2
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // S3
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // S4
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // S5
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
	// S6
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
	// S7
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
	// S8
    {
        NULL, // parent resource
        smps8_e_child_dep, // child resource dependencies
        9, // num vreg children
        0, // num xob children
    },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info smps_dep_g[] =
{
    {NULL, NULL, 0, 0}, // Invalid zeroth array - NOT USED
    // S1
    {
        NULL, // parent resource
        smps1_g_child_dep, // child resource dependencies
        3, // num vreg children
        0, // num xob children
    },
    // S2
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // S3
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info bob_dep_e[] =
{
    {NULL, NULL, 0, 0}, // Invalid zeroth array - NOT USED
    // BOB1
    {
        NULL, // parent resource
        bob1_e_child_dep, // child resource dependencies
        12, // num vreg children
        0, // num xob children
    },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_b[] =
{
    {NULL, NULL, 0, 0}, // Invalid zeroth array - NOT USED
    // L1
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L2
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L3
    {
        &smps_b[7], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L4
    {
        &smps_b[7], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L5
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L6
    {
        &smps_b[7], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L7
    {
        &smps_b[7], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L8
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L9
    {
        &smps_b[7], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L10
    {
        &smps_b[7], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L11
    {
        &smps_b[7], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L12
    {
        &smps_b[8], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L13
    {
        &smps_b[8], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L14
    {
        &smps_b[8], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L15
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L16
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L17
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L18
    {
        &smps_e[8], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L19
    {
        &smps_e[8], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L20
    {
        &smps_e[8], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L21
    {
        &smps_e[8], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L22
    {
        &smps_e[8], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L23
    {
        &smps_e[8], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L24
    {
        &bob_e[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L25
    {
        &bob_e[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L26
    {
        &bob_e[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L27
    {
        &bob_e[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L28
    {
        &bob_e[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_e[] =
{
    {NULL, NULL, 0, 0}, // Invalid zeroth array - NOT USED
    // L1
    {
        &smps_e[8], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L2
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L3
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L4
    {
        &bob_e[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L5
    {
        &bob_e[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L6
    {
        &bob_e[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L7
    {
        &bob_e[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L8
    {
        &smps_e[8], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L9
    {
        &bob_e[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L10
    {
        &bob_e[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L11
    {
        &bob_e[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_g[] =
{
    {NULL, NULL, 0, 0}, // Invalid zeroth array - NOT USED
    // L1
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L2
    {
        &smps_b[8], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L3
    {
        &smps_g[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L4
    {
        &smps_e[8], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L5
    {
        &smps_g[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L6
    {
        &smps_g[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L7
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info clk_dep_a[] =
{
    {NULL, NULL, 0, 0}, // Invalid zeroth array - NOT USED
    // CLK_DIST
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // EMPTY
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // EMPTY
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // RF_CLK1
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // RF_CLK2
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // RF_CLK3
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // RF_CLK4
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // RF_CLK5
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // LN_BB_CLK1
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // LN_BB_CLK2
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // LN_BB_CLK3
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // EMPTY
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // EMPTY
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // DIV_CLK1
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // EMPTY
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // SLEEP_CLK1
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
};

// resource dependency info
__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource_dependency_info* smps_dep[] =
{
    NULL,
    smps_dep_b,
    NULL,
    NULL,
    smps_dep_e,
    NULL,
    smps_dep_g,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource_dependency_info* ldo_dep[] =
{
    NULL,
    ldo_dep_b,
    NULL,
    NULL,
    ldo_dep_e,
    NULL,
    ldo_dep_g,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource_dependency_info* bob_dep[] =
{
    NULL,
    NULL,
    NULL,
    NULL,
    bob_dep_e,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource_dependency_info* clk_dep[] =
{
    clk_dep_a,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource_dependency_info* vs_dep[] =
{
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

// resource info
__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource* smps_rsrc[] =
{
    NULL,
    smps_b,
    NULL,
    NULL,
    smps_e,
    NULL,
    smps_g,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource* ldo_rsrc[] =
{
    NULL,
    ldo_b,
    NULL,
    NULL,
    ldo_e,
    NULL,
    ldo_g,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource* bob_rsrc[] =
{
    NULL,
    NULL,
    NULL,
    NULL,
    bob_e,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource* clk_rsrc[] =
{
    clk_a,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};



