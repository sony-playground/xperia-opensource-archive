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
11/30/22    rajivr      clk resources update
10/31/22    rajivr      Initial changes
08/11/22    rajivr      Created, PMIC stubbing code change
11/25/22    rajivr      FR83960 changes, enhancements in XO Crystal OFF
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
    {"smpa1", "vrm.mss"},
    {"smpa2", NULL},
    {"smpa3", NULL},
    {"smpa4", NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_a[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"ldoa1", "vrm.mx"},
    {"ldoa2", "vrm.mxc"},
    {"ldoa3", NULL},
    {"ldoa4", NULL},
    {"ldoa5", NULL},
    {"ldoa6", "vrm.qf"},
    {"ldoa7", NULL},
    {"ldoa8", NULL},
    {"ldoa9", NULL},
    {"ldoa10", NULL},
    {"ldoa11", NULL},
    {"ldoa12", NULL},
    {"ldoa13", NULL},
    {"ldoa14", NULL},
    {"ldoa15", NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource clk_a[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"clk_dist", NULL}, //51
    {NULL, NULL}, //52
    {NULL, NULL}, //53
    {"clka1", "rfclka1"}, //54
    {"clka2", NULL}, //55
    {"clka3", NULL}, //56
    {NULL, NULL}, //57
    {NULL, NULL}, //58
    {"clka4", "vrm.xob"}, //59
    {"clka5", NULL}, //5A
    {NULL, NULL}, //5B
    {NULL, NULL}, //5C
    {NULL, NULL}, //5D
    {"divclk1", NULL}, //5E
    {NULL, NULL}, //5F					  
    {"sleepclka1", NULL}, //60
    {"sleepclka2", NULL}, //61
    {NULL, NULL}, //62
};


// Component Resource Child Depend Structure Creation


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps2_a_child_dep[] =
{
    //&ldo_a[3], Removed for Dyn ACC
    &ldo_a[9],
    &ldo_a[12],
    //&ldo_a[14], Removed for Dyn ACC
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps3_a_child_dep[] =
{
    &ldo_a[1],
    &ldo_a[2],
    &ldo_a[4],
    &ldo_a[8],
    &ldo_a[13],
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps4_a_child_dep[] =
{
    &ldo_a[5],
    &ldo_a[6],
    &ldo_a[7],
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
        smps2_a_child_dep, // child resource dependencies
        2, // num vreg children
        0, // num xob children
    },
    // S3
    {
        NULL, // parent resource
        smps3_a_child_dep, // child resource dependencies
        5, // num vreg children
        0, // num xob children
    },
    // S4
    {
        NULL, // parent resource
        smps4_a_child_dep, // child resource dependencies
        3, // num vreg children
        0, // num xob children
    },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_a[] =
{
    {NULL, NULL, 0, 0}, // Invalid zeroth array - NOT USED
    // L1
    {
        &smps_a[3], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L2
    {
        &smps_a[3], // parent resource
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
        &smps_a[3], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L5
    {
        &smps_a[4], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L6
    {
        &smps_a[4], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L7
    {
        &smps_a[4], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L8
    {
        &smps_a[3], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L9
    {
        &smps_a[2], // parent resource
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
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L12
    {
        &smps_a[2], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L13
    {
        &smps_a[3], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L14
    {
        NULL, // parent resource
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
    // CLK1_RF
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // CLK2_RF
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // CLK3_RF
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
    // CLK4_LN
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // CLK5_LN
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
    // SLEEP_CLK2
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
	// TXCO CAL
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
