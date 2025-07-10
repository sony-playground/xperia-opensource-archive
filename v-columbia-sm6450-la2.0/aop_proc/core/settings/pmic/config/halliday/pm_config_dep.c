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
05/13/22    rajivr      Initial Halliday version
07/13/22    rajivr      vrm.ebi aliasing update to S4D
07/19/22    rajivr      Code change for Dynamic ACC feature
07/27/22    rajivr      Added smps_dep_d in smps_dep 
09/30/22    rajivr      Exposing L7B as vrm.qf in cmd_db
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
    {"smpb2", NULL},
    {"smpb3", NULL},
    {"smpb4", "vrm.mmcx"},
    {"smpb5", NULL},
    {"smpb6", NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_c[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"smpc1", NULL},
    {"smpc2", NULL},
    {"smpc3", "vrm.mx"},
    {"smpc4", NULL},
    {"smpc5", NULL},
    {"smpc6", NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_d[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"smpd1", NULL},
    {"smpd2", NULL},
    {"smpd3", NULL},
    {"smpd4", "vrm.ebi"},
    {"smpd5", NULL},
    {"smpd6", "vrm.cx"},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_f[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"smpf1", NULL},
    {"smpf2", "vrm.mxc"},
    {"smpf3", NULL},
    {"smpf4", NULL},
    {"smpf5", "vrm.gfx"},
    {"smpf6", NULL},
    {"smpf7", NULL},
    {"smpf8", NULL},
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
static pm_pwr_resource bob_b[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"bobb1", NULL },
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_b[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"ldob1", NULL},
    {"ldob2", NULL},
    {"ldob3", NULL},
    {"ldob4", NULL},
    {"ldob5", NULL},
    {"ldob6", NULL},
    {"ldob7", "vrm.qf"},
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
    {"ldob18", NULL},
    {"ldob19", NULL},
    {"ldob20", NULL},
    {"ldob21", NULL},
    {"ldob22", NULL},
    {"ldob23", NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_c[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"ldoc1", "vrm.lcx"},
    {"ldoc2", NULL},
    {"ldoc3", NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_d[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"ldod1", NULL},
    {"ldod2", NULL},
    {"ldod3", NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_f[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"ldof1", "vrm.lmx"},
    {"ldof2", NULL},
    {"ldof3", NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_m[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"ldom1", NULL},
    {"ldom2", NULL},
    {"ldom3", NULL},
    {"ldom4", NULL},
    {"ldom5", NULL},
    {"ldom6", NULL},
    {"ldom7", NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_n[]  =
{
    {NULL, NULL}, // this is invalid place holder
    {"ldon1", NULL},
    {"ldon2", NULL},
    {"ldon3", NULL},
    {"ldon4", NULL},
    {"ldon5", NULL},
    {"ldon6", NULL},
    {"ldon7", NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource clk_a[]  =
{
   {NULL,NULL}, // this is invalid place holder
   {NULL,NULL}, //51
   {NULL,NULL}, //52
   {NULL,NULL}, //53
   {"clka1","rfclka1"}, //54
   {"clka2","rfclka2"}, //55
   {"clka3","rfclka3"}, //56
   {"clka4","rfclka4"}, //57
   {"clka5",NULL}, //58
   {"clka6","vrm.xob"}, //59
   {"clka7",NULL}, //5a
   {"clka8",NULL}, //5b
   {"clka9",NULL},  //5c
   {NULL,NULL},  //5d
   {"clka11",NULL},   //5e
   {NULL,NULL},
   {NULL,NULL},
};


// Component Resource Child Depend Structure Creation


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *bob1_b_child_dep[] =
{
    &ldo_b[12],
    &ldo_b[13],
    &ldo_b[14],
    &ldo_b[15],
    &ldo_b[16],
    &ldo_b[17],
    &ldo_b[18],
    &ldo_b[19],
    &ldo_b[20],
    &ldo_b[21],
    &ldo_b[22],
    &ldo_b[23],
    &ldo_m[3],
    &ldo_m[4],
    &ldo_m[5],
    &ldo_m[6],
    &ldo_m[7],
    &ldo_n[3],
    &ldo_n[4],
    &ldo_n[5],
    &ldo_n[6],
    &ldo_n[7],
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps1_b_child_dep[] =
{
    &ldo_b[4],
    &ldo_b[5],
    &ldo_b[6],
    &ldo_b[7],
    &ldo_b[8],
    &ldo_b[9],
    &ldo_b[10],
    &ldo_b[11],
    &ldo_f[3],
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps2_b_child_dep[] =
{
    &ldo_b[2],
    &ldo_b[3],
    //&ldo_c[2],
    &ldo_c[3],
    &ldo_d[3],
    &ldo_m[1],
    &ldo_m[2],
    &ldo_n[1],
    &ldo_n[2],
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps3_b_child_dep[] =
{
    &ldo_b[1],
    &ldo_d[1],
    &ldo_d[2],
    &ldo_f[1],
    //&ldo_f[2],
};

/*__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps4_d_child_dep[] =
{
    &ldo_c[1],
};*/

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
        smps2_b_child_dep, // child resource dependencies
        8, // num vreg children
        0, // num xob children
    },
    // S3
    {
        NULL, // parent resource
        smps3_b_child_dep, // child resource dependencies
        4, // num vreg children
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
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info smps_dep_d[] =
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
        NULL, //smps4_d_child_dep, // child resource dependencies
        1, // num vreg children
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
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info smps_dep_f[] =
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
pm_pwr_resource_dependency_info bob_dep_b[] =
{
    {NULL, NULL, 0, 0}, // Invalid zeroth array - NOT USED
    // BOB1
    {
        NULL, // parent resource
        bob1_b_child_dep, // child resource dependencies
        22, // num vreg children
        0, // num xob children
    },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_b[] =
{
    {NULL, NULL, 0, 0}, // Invalid zeroth array - NOT USED
    // L1
    {
        &smps_b[3], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L2
    {
        &smps_b[2], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L3
    {
        &smps_b[2], // parent resource
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
        &smps_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L6
    {
        &smps_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L7
    {
        &smps_b[1], // parent resource
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
        &smps_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L10
    {
        &smps_b[1], // parent resource
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
        &bob_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L13
    {
        &bob_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L14
    {
        &bob_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L15
    {
        &bob_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L16
    {
        &bob_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L17
    {
        &bob_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L18
    {
        &bob_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L19
    {
        &bob_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L20
    {
        &bob_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L21
    {
        &bob_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L22
    {
        &bob_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L23
    {
        &bob_b[1], // parent resource
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
        NULL, //&smps_d[4], // parent resource
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
        &smps_b[2], // parent resource
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
        &smps_b[3], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L2
    {
        &smps_b[3], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L3
    {
        &smps_b[2], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_f[] =
{
    {NULL, NULL, 0, 0}, // Invalid zeroth array - NOT USED
    // L1
    {
        &smps_b[3], // parent resource
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
        &smps_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_m[] =
{
    {NULL, NULL, 0, 0}, // Invalid zeroth array - NOT USED
    // L1
    {
        &smps_b[2], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L2
    {
        &smps_b[2], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L3
    {
        &bob_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L4
    {
        &bob_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L5
    {
        &bob_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L6
    {
        &bob_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L7
    {
        &bob_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_n[] =
{
    {NULL, NULL, 0, 0}, // Invalid zeroth array - NOT USED
    // L1
    {
        &smps_b[2], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L2
    {
        &smps_b[2], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L3
    {
        &bob_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L4
    {
        &bob_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L5
    {
        &bob_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L6
    {
        &bob_b[1], // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // L7
    {
        &bob_b[1], // parent resource
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
    // CLK4_RF
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // CLK5_RF
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // CLK6_LN
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // CLK7_LN
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // CLK8_LN
    {
        NULL, // parent resource
        NULL, // child resource dependencies
        0, // num vreg children
        0, // num xob children
    },
    // CLK9_LN
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
    // CLK11_DIV
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
    smps_dep_d,
    NULL,
    smps_dep_f,
    NULL,
    NULL,
    NULL,
    NULL,
    smps_dep_k,
    NULL,
    NULL,
    NULL,
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource_dependency_info* ldo_dep[] =
{
    NULL,
    ldo_dep_b,
    ldo_dep_c,
    ldo_dep_d,
    NULL,
    ldo_dep_f,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ldo_dep_m,
    ldo_dep_n,
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource_dependency_info* bob_dep[] =
{
    NULL,
    bob_dep_b,
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
    NULL,
    smps_b,
    smps_c,
    smps_d,
    NULL,
    smps_f,
    NULL,
    NULL,
    NULL,
    NULL,
    smps_k,
    NULL,
    NULL,
    NULL,
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource* ldo_rsrc[] =
{
    NULL,
    ldo_b,
    ldo_c,
    ldo_d,
    NULL,
    ldo_f,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ldo_m,
    ldo_n,
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource* bob_rsrc[] =
{
    NULL,
    bob_b,
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



