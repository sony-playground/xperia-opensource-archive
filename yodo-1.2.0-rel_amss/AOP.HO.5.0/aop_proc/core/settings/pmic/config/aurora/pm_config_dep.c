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
27/09/21    bde      Created by PMIC config tool V. PGA V. CR#
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/

#include "pm_config_interface.h"

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_a[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"smpa1", "vrm.cx"},
    {"smpa2", "vrm.gfx"},
    {"smpa3", NULL},
    {"smpa4", NULL},
    {"smpa5", NULL},
    {"smpa6", NULL},
    {"smpa7", NULL},
    {"smpa8", NULL},
    {"smpa9", NULL},
    {"smpa10", NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_a[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"ldoa1", NULL},
    {"ldoa2", NULL},
    {"ldoa3", NULL},
    {"ldoa4", NULL},
    {"ldoa5", NULL},
    {"ldoa6", NULL},
    {"ldoa7", NULL},
    {"ldoa8", "vrm.lmx"},
    {"ldoa9", "vrm.lcx"},
    {"ldoa10", NULL},
    {"ldoa11", NULL},
    {"ldoa12", NULL},
    {"ldoa13", NULL},
    {"ldoa14", NULL},
    {"ldoa15", NULL},
    {"ldoa16", NULL},
    {"ldoa17", NULL},
    {"ldoa18", NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource clk_a[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"lnbclka1", NULL},
    {"lnbclka2", NULL},
    {"lnbclka3", NULL},
    {"rfclka1", "vrm.xob"},
    {"rfclka2", NULL},
    {"rfclka3", NULL},
    {NULL, NULL},
    {NULL, NULL},
    {"clkdista", NULL},
    {"sleepclka1", NULL},
    {"divclka1", NULL},
    {"divclka2", NULL},
    {NULL, NULL},
};


// Component Resource Child Depend Structure Creation

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps4_a_child_dep[] =
{
    &ldo_a[1],
    &ldo_a[8],
    &ldo_a[11],
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps5_a_child_dep[] =
{
    &ldo_a[7],
    &ldo_a[12],
    &ldo_a[14],
    &ldo_a[15],
};

// Component Resource Dependency Information
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info smps_dep_a[] =
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
        smps4_a_child_dep, // child resource dependencies
        3, // num vreg children
        0, // num xob children
    },
    // S5
    {
        NULL, // parent resource
        smps5_a_child_dep, // child resource dependencies
        4, // num vreg children
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
pm_pwr_resource_dependency_info ldo_dep_a[] =
{
    {NULL, NULL, 0, 0}, // Invalid zeroth array - NOT USED
    // L1
    {
        &smps_a[4], // parent resource
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
        NULL, // parent resource
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
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L7
    {
        &smps_a[5], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L8
    {
        &smps_a[4], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L9
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L10
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L11
    {
        &smps_a[4], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L12
    {
        &smps_a[5], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L13
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L14
    {
        &smps_a[5], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L15
    {
        &smps_a[5], // parent resource
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
    // CLK_DIST
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
    // DIV_CLK1
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // DIV_CLK2
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
};

// resource dependency info
__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource_dependency_info* smps_dep[] =
{
    smps_dep_a,
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
pm_pwr_resource_dependency_info* ldo_dep[] =
{
    ldo_dep_a,
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
pm_pwr_resource_dependency_info* bob_dep[] =
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
    smps_a,
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
pm_pwr_resource* ldo_rsrc[] =
{
    ldo_a,
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
pm_pwr_resource* bob_rsrc[] =
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



