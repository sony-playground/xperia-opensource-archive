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
10/08/21    nvelugu      Created by PMIC config tool V. PGA V. CR#
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
    {"smpb1", NULL},
    {"smpb2", "vrm.ebi"},
    {"smpb3", NULL},
    {"smpb4", NULL},
    {"smpb5", NULL},
    {"smpb6", NULL},
    {"smpb7", NULL},
    {"smpb8", NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_c[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"smpc1", NULL},
    {"smpc2", "vrm.gfx"},
    {"smpc3", NULL},
    {"smpc4", "vrm.mxc"},
    {"smpc5", "vrm.mmcx"},
    {"smpc6", "vrm.mss"},
    {"smpc7", NULL},
    {"smpc8", "vrm.cx"},
    {"smpc9", NULL},
    {"smpc10", "vrm.mx"},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_e[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"smpe1", NULL},
    {"smpe2", NULL},
    {"smpe3", NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_k[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"smpk1", NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_l[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"smpl1", "vrm.mx"},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_m[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"smpm1", "vrm.mxc"},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource bob_c[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"bobc1", NULL },
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_b[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"ldob1", NULL},
    {"ldob2", NULL},
    {"ldob3", NULL},
    {"ldob4", "vrm.lmx"},
    {"ldob5", "vrm.lcx"},
    {"ldob6", NULL},
    {"ldob7", NULL},
    {"ldob8", NULL},
    {"ldob9", NULL},
    {"ldob10", NULL},
    {"ldob11", NULL},
    {"ldob12", NULL},
    {"ldob13", NULL},
    {"ldob14", NULL},
    {"ldob15", NULL},
    {"ldob16", NULL},
    {"ldob17", NULL},
    {"ldob18", "vrm.qf"},
    {"ldob19", NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_c[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"ldoc1", NULL},
    {"ldoc2", NULL},
    {"ldoc3", NULL},
    {"ldoc4", NULL},
    {"ldoc5", NULL},
    {"ldoc6", NULL},
    {"ldoc7", NULL},
    {"ldoc8", NULL},
    {"ldoc9", NULL},
    {"ldoc10", NULL},
    {"ldoc11", NULL},
    {"ldoc12", NULL},
    {"ldoc13", NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_d[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"ldod1", NULL},
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
static pm_pwr_resource *bob1_c_child_dep[] =
{
    &ldo_b[2],
    &ldo_b[7],
    &ldo_c[3],
    &ldo_c[4],
    &ldo_c[5],
    &ldo_c[6],
    &ldo_c[7],
    &ldo_c[9],
    &ldo_c[11],
    &ldo_c[13],
    &ldo_e[7],
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps1_b_child_dep[] =
{
    &ldo_b[11],
    &ldo_b[17],
    &ldo_b[18],
    &ldo_b[19],
    &ldo_c[1],
    &ldo_c[2],
    &ldo_c[8],
    &ldo_c[12],
    &ldo_e[4],
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps1_e_child_dep[] =
{
    &ldo_e[1],
    &ldo_e[2],
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps2_e_child_dep[] =
{
    &ldo_e[3],
    &ldo_e[5],
    &ldo_e[6],
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps7_b_child_dep[] =
{
    &ldo_b[1],
    &ldo_b[4],
    &ldo_b[8],
    &ldo_b[12],
    &ldo_b[13],
    &ldo_b[15],
    &ldo_c[10],
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps8_b_child_dep[] =
{
    &ldo_b[6],
    &ldo_b[9],
    &ldo_b[10],
    &ldo_b[14],
    &ldo_b[16],
    &ldo_d[1],
};

// Component Resource Dependency Information
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info smps_dep_b[] =
{
    {NULL, NULL, 0, 0}, // Invalid zeroth array - NOT USED
    // S1
    {
        NULL, // parent resource
        smps1_b_child_dep, // child resource dependencies
        9, // num vreg children
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
        6, // num vreg children
        0, // num xob children
    },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info smps_dep_c[] =
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
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // S9
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // S10
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
        smps1_e_child_dep, // child resource dependencies
        2, // num vreg children
        0, // num xob children
    },
    // S2
    {
        NULL, // parent resource
        smps2_e_child_dep, // child resource dependencies
        3, // num vreg children
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
pm_pwr_resource_dependency_info smps_dep_k[] =
{
    {NULL, NULL, 0, 0}, // Invalid zeroth array - NOT USED
    // S1
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info smps_dep_l[] =
{
    {NULL, NULL, 0, 0}, // Invalid zeroth array - NOT USED
    // S1
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info smps_dep_m[] =
{
    {NULL, NULL, 0, 0}, // Invalid zeroth array - NOT USED
    // S1
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info bob_dep_c[] =
{
    {NULL, NULL, 0, 0}, // Invalid zeroth array - NOT USED
    // BOB1
    {
        NULL, // parent resource
        bob1_c_child_dep, // child resource dependencies
        11, // num vreg children
        0, // num xob children
    },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_b[] =
{
    {NULL, NULL, 0, 0}, // Invalid zeroth array - NOT USED
    // L1
    {
        &smps_b[7], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L2
    {
        &bob_c[1], // parent resource
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
        &smps_b[8], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L7
    {
        &bob_c[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L8
    {
        &smps_b[7], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L9
    {
        &smps_b[8], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L10
    {
        &smps_b[8], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L11
    {
        &smps_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L12
    {
        &smps_b[7], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L13
    {
        &smps_b[7], // parent resource
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
        &smps_b[7], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L16
    {
        &smps_b[8], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L17
    {
        &smps_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L18
    {
        &smps_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L19
    {
        &smps_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_c[] =
{
    {NULL, NULL, 0, 0}, // Invalid zeroth array - NOT USED
    // L1
    {
        &smps_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L2
    {
        &smps_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L3
    {
        &bob_c[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L4
    {
        &bob_c[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L5
    {
        &bob_c[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L6
    {
        &bob_c[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L7
    {
        &bob_c[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L8
    {
        &smps_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L9
    {
        &bob_c[1], // parent resource
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
        &bob_c[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L12
    {
        &smps_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L13
    {
        &bob_c[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_d[] =
{
    {NULL, NULL, 0, 0}, // Invalid zeroth array - NOT USED
    // L1
    {
        &smps_b[8], // parent resource
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
        &smps_e[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L2
    {
        &smps_e[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L3
    {
        &smps_e[2], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L4
    {
        &smps_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L5
    {
        &smps_e[2], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L6
    {
        &smps_e[2], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L7
    {
        &bob_c[1], // parent resource
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
    smps_dep_c,
    NULL,
    smps_dep_e,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    smps_dep_k,
    smps_dep_l,
    smps_dep_m,
    NULL,
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource_dependency_info* ldo_dep[] =
{
    NULL,
    ldo_dep_b,
    ldo_dep_c,
    ldo_dep_d,
    ldo_dep_e,
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
pm_pwr_resource_dependency_info* bob_dep[] =
{
    NULL,
    NULL,
    bob_dep_c,
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
    smps_c,
    NULL,
    smps_e,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    smps_k,
    smps_l,
    smps_m,
    NULL,
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource* ldo_rsrc[] =
{
    NULL,
    ldo_b,
    ldo_c,
    ldo_d,
    ldo_e,
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
pm_pwr_resource* bob_rsrc[] =
{
    NULL,
    NULL,
    bob_c,
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



