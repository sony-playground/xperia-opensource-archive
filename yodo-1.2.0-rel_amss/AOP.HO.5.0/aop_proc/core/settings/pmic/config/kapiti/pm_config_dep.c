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

$Header: //components/rel/aop.ho/5.0/aop_proc/core/settings/pmic/config/kapiti/pm_config_dep.c#1 $ 

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "pm_config_interface.h"

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
smps_c[] =
{
   {NULL,NULL}, // this is invalid place holder
   {"smpc1",NULL},
   {"smpc2",NULL},
   {"smpc3",NULL},
   {"smpc4",NULL},
   {"smpc5",NULL},
   {"smpc6",NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
smps_d[] =
{
   {NULL,NULL}, // this is invalid place holder
   {"smpd1",NULL},
   {"smpd2",NULL},
   {"smpd3",NULL},
   {"smpd4","vrm.lcx"},
   {"smpd5","vrm.gfx"},
   {"smpd6",NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
smps_e[] =
{
   {NULL,NULL}, // this is invalid place holder
   {"smpe1","vrm.mmcx"},
   {"smpe2",NULL},
   {"smpe3","vrm.mx"},
   {"smpe4",NULL},
   {"smpe5",NULL},
   {"smpe6","vrm.cx"},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
smps_f[] =
{
   {NULL,NULL}, // this is invalid place holder
   {"smpf1","vrm.nsp"},
   {"smpf2",NULL},
   {"smpf3","vrm.ebi"},
   {"smpf4",NULL},
   {"smpf5","vrm.mxc"},
   {"smpf6",NULL},
   {"smpf7","vrm.mss"},
   {"smpf8",NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
smps_g[] =
{
   {NULL,NULL}, // this is invalid place holder
   {"smpg1",NULL},
   {"smpg2",NULL},
   {"smpg3",NULL},
   {"smpg4",NULL},
   {"smpg5",NULL},
   {"smpg6",NULL},
};


// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
bob_b[] =
{
   {NULL,NULL}, // this is invalid place holder
   {"bobb1",NULL},
   {"bobb2",NULL},
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
ldo_b[] =
{
   {NULL,NULL}, // this is invalid place holder
   {"ldob1",NULL},
   {"ldob2",NULL},
   {"ldob3",NULL},
   {"ldob4",NULL},
   {"ldob5",NULL},
   {"ldob6",NULL},
   {"ldob7",NULL},
   {"ldob8",NULL},
   {"ldob9",NULL},
   {"ldob10",NULL},
   {"ldob11",NULL},
   {"ldob12",NULL},
   {"ldob13",NULL},
   {"ldob14",NULL},
   {"ldob15",NULL},
   {"ldob16",NULL},
   {"ldob17",NULL},
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
ldo_c[] =
{
   {NULL,NULL}, // this is invalid place holder
   {"ldoc1",NULL},
   {"ldoc2",NULL},
   {"ldoc3",NULL},
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
ldo_d[] =
{
   {NULL,NULL}, // this is invalid place holder
   {"ldod1",NULL},
   {"ldod2","vrm.lmx"},
   {"ldod3",NULL},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
ldo_e[] =
{
   {NULL,NULL}, // this is invalid place holder
   {"ldoe1",NULL},
   {"ldoe2",NULL},
   {"ldoe3",NULL},
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
ldo_f[] =
{
   {NULL,NULL}, // this is invalid place holder
   {"ldof1",NULL},
   {"ldof2",NULL},
   {"ldof3",NULL},
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
ldo_g[] =
{
   {NULL,NULL}, // this is invalid place holder
   {"ldog1",NULL},
   {"ldog2",NULL},
   {"ldog3",NULL},
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
ldo_k[] =
{
   {NULL,NULL}, // this is invalid place holder
   {"ldok1",NULL},
   {"ldok2",NULL},
   {"ldok3",NULL},
   {"ldok4",NULL},
   {"ldok5",NULL},
   {"ldok6",NULL},
   {"ldok7",NULL},
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
ldo_l[] =
{
   {NULL,NULL}, // this is invalid place holder
   {"ldol1",NULL},
   {"ldol2",NULL},
   {"ldol3",NULL},
   {"ldol4",NULL},
   {"ldol5",NULL},
   {"ldol6",NULL},
   {"ldol7",NULL},
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
ldo_m[] =
{
   {NULL,NULL}, // this is invalid place holder
   {"ldom1",NULL},
   {"ldom2",NULL},
   {"ldom3",NULL},
   {"ldom4",NULL},
   {"ldom5",NULL},
   {"ldom6",NULL},
   {"ldom7",NULL},
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
ldo_n[] =
{
   {NULL,NULL}, // this is invalid place holder
   {"ldon1",NULL},
   {"ldon2",NULL},
   {"ldon3",NULL},
   {"ldon4",NULL},
   {"ldon5",NULL},
   {"ldon6",NULL},
   {"ldon7",NULL},
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
clk_a[] =
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
static pm_pwr_resource *
smps4_e_child_dep[] =
{
   //&ldo_c[2],
   &ldo_c[3],
   &ldo_d[1],
   &ldo_d[2],
   //&ldo_d[3],
   &ldo_e[1],
   &ldo_e[2],
   &ldo_f[1],
   &ldo_f[2],
   &ldo_f[3],
};

__attribute__((section("pm_ddr_reclaim_pool"))) 
static pm_pwr_resource *
smps1_g_child_dep[] =
{
   &ldo_k[3],
   &ldo_k[4],
   &ldo_k[7],
   &ldo_l[3],
   &ldo_l[4],
};

__attribute__((section("pm_ddr_reclaim_pool"))) 
static pm_pwr_resource *
smps2_g_child_dep[] =
{
   &ldo_k[1],
   &ldo_k[2],
   &ldo_k[5],
   //&ldo_l[1],
   //&ldo_l[2],
   &ldo_l[5],
};

__attribute__((section("pm_ddr_reclaim_pool"))) 
static pm_pwr_resource *
smps3_g_child_dep[] =
{
   &ldo_l[7],
};

__attribute__((section("pm_ddr_reclaim_pool"))) 
static pm_pwr_resource *
smps4_g_child_dep[] =
{
   &ldo_b[3],
   &ldo_b[11],
   //&ldo_c[1],
   &ldo_e[3],
   &ldo_g[1],
   &ldo_g[2],
   &ldo_g[3],
   &ldo_m[1],
   &ldo_m[2],
   &ldo_n[1],
   &ldo_n[2],
};

__attribute__((section("pm_ddr_reclaim_pool"))) 
static pm_pwr_resource *
smps6_g_child_dep[] =
{
   &ldo_b[1],
   //&ldo_b[4],
   &ldo_b[10],
   &ldo_b[12],
   &ldo_b[15],
   &ldo_k[6],
   &ldo_l[6],
   &ldo_m[5],
   &ldo_m[6],
   &ldo_n[5],
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *
bob1_b_child_dep[] = 
{
   &ldo_b[2],
   &ldo_b[5],
   &ldo_b[6],
   &ldo_b[7],
   &ldo_b[8],
   &ldo_b[9],
   &ldo_b[13],
   &ldo_b[14],
   &ldo_b[16],
   &ldo_m[7],
   &ldo_n[6],
   &ldo_n[7],
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *
bob2_b_child_dep[] = 
{
   &ldo_b[17],
   &ldo_m[3],
   &ldo_m[4],
   &ldo_n[3],
   &ldo_n[4],
};


// Component Resource Dependency Information
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
smps_dep_c[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // S1
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S2
   {
      NULL, //parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S3
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S4
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S5
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S6
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
smps_dep_d[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // S1
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S2
   {
      NULL, //parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S3
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S4
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S5
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S6
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
smps_dep_e[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // S1
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S2
   {
      NULL, //parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S3
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S4
   {
      NULL, //parent resource
      smps4_e_child_dep, // child resource dependencies
      8,  // num vreg children
      0,  // num xob children
   },
   // S5
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S6
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
smps_dep_f[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // S1
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S2
   {
      NULL, //parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S3
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S4
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S5
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S6
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S7
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },   
   // S8
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
smps_dep_g[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // S1
   {
      NULL, //parent resource
      smps1_g_child_dep, // child resource dependencies
      5,  // num vreg children
      0,  // num xob children
   },
   // S2
   {
      NULL, //parent resource
      smps2_g_child_dep,// child resource dependencies
      4,  // num vreg children
      0,  // num xob children
   },
   // S3
   {
      NULL, //parent resource
      smps3_g_child_dep, // child resource dependencies
      1,  // num vreg children
      0,  // num xob children
   },
   // S4
   {
      NULL, //parent resource
      smps4_g_child_dep, // child resource dependencies
      10,  // num vreg children
      0,  // num xob children
   },
   // S5
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S6
   {
      NULL, //parent resource
      smps6_g_child_dep, // child resource dependencies
      9,  // num vreg children
      0,  // num xob children
   },
};


__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
bob_dep_b[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // B1
   {
      NULL, //parent resource
      bob1_b_child_dep, // child resource dependencies
      12,  // num vreg children
      0,  // num xob children
   },
   // B2
   {
      NULL, //parent resource
      bob2_b_child_dep, // child resource dependencies
      5,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
ldo_dep_b[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1
   {
      &smps_g[6], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L2
   {
      &bob_b[1], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L3
   {
      &smps_g[4], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L4
   {
      NULL, //&smps_g[6], //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
    // L5
   {
      &bob_b[1], //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6
   {
      &bob_b[1], //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L7
   {
      &bob_b[1], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L8
   {
      &bob_b[1], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L9
   {
      &bob_b[1], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L10
   {
      &smps_g[6],//parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L11
   {
      &smps_g[4], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L12
   {
      &smps_g[6], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L13
   {
      &bob_b[1], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L14
   {
      &bob_b[1], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L15
   {
      &smps_g[6], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L16
   {
      &bob_b[1], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L17
   {
      &bob_b[2], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
ldo_dep_c[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1
   {
      NULL, //&smps_g[4] //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L2
   {
      NULL, //&smps_e[4]//parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L3
   {
      &smps_e[4],//parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
ldo_dep_d[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1
   {
      &smps_e[4], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L2
   {
      &smps_e[4], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L3
   {
      NULL, //&smps_e[4]//parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
ldo_dep_e[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1
   {
      &smps_e[4], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L2
   {
      &smps_e[4], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L3
   {
      &smps_g[4], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
ldo_dep_f[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1
   {
      &smps_e[4], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L2
   {
      &smps_e[4], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L3
   {
      &smps_e[4], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
ldo_dep_g[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1
   {
      &smps_g[4], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L2
   {
      &smps_g[4], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L3
   {
      &smps_g[4], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
ldo_dep_k[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1
   {
      &smps_g[2], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L2
   {
      &smps_g[2], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L3
   {
      &smps_g[1], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L4
   {
      &smps_g[1], //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
    // L5
   {
      &smps_g[2], //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6
   {
      &smps_g[6], //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L7
   {
      &smps_g[1], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
ldo_dep_l[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1
   {
      NULL,//&smps_g[2], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L2
   {
      NULL,//&smps_g[2], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L3
   {
      &smps_g[1], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L4
   {
      &smps_g[1], //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
    // L5
   {
      &smps_g[2], //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6
   {
      &smps_g[6], //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L7
   {
      &smps_g[3], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
ldo_dep_m[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1
   {
      &smps_g[4],//parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L2
   {
      &smps_g[4], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L3
   {
      &bob_b[2], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L4
   {
      &bob_b[2], //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
    // L5
   {
      &smps_g[6], //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6
   {
      &smps_g[6], //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L7
   {
      &bob_b[1], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
ldo_dep_n[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1
   {
      &smps_g[4], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L2
   {
      &smps_g[4], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L3
   {
      &bob_b[2], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L4
   {
      &bob_b[2], //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
    // L5
   {
      &smps_g[6], //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6
   {
      &bob_b[1], //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L7
   {
      &bob_b[1], //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
clk_dep_a[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // C1
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // C2
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // C3
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // C4
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // C5
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // C6
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // C7
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // C8
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // C9
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // C10
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // C11
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // C12
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // C13
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },   
   // C14
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // C15
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // C16
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};


// resource dependency info
__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource_dependency_info* 
smps_dep[] = 
{
    NULL,
    NULL,
    smps_dep_c, 
    smps_dep_d, 
    smps_dep_e,
    smps_dep_f,
    smps_dep_g,
    NULL,
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource_dependency_info* 
ldo_dep[] = 
{
    NULL,
    ldo_dep_b,
    ldo_dep_c,
    ldo_dep_d, 
    ldo_dep_e,
    ldo_dep_f,
    ldo_dep_g,
    NULL,
    NULL,
    NULL,
    ldo_dep_k,
    ldo_dep_l,
    ldo_dep_m,
    ldo_dep_n,
};


__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource_dependency_info* 
bob_dep[] = 
{
    NULL, 
    bob_dep_b,
    NULL,
    NULL, 
    NULL,
    NULL,
    NULL,
    NULL,
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource_dependency_info* 
vs_dep[] = 
{
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
pm_pwr_resource_dependency_info* 
clk_dep[] = 
{
    clk_dep_a,
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
pm_pwr_resource* 
smps_rsrc[] = 
{
    NULL,
    NULL,
    smps_c, 
    smps_d, 
    smps_e,
    smps_f,
    smps_g,
    NULL,
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource* 
ldo_rsrc[] = 
{
    NULL,
    ldo_b,
    ldo_c,
    ldo_d, 
    ldo_e,
    ldo_f,
    ldo_g,
    NULL,
    NULL,
    NULL,
    ldo_k,
    ldo_l,
    ldo_m,
    ldo_n,
};


__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource* 
bob_rsrc[] = 
{
    NULL, 
    bob_b,
    NULL,
    NULL, 
    NULL,
    NULL,
    NULL,
    NULL,
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource* 
clk_rsrc[] = 
{
    clk_a,
    NULL,
    NULL,
    NULL, 
    NULL,
    NULL, 
    NULL,
    NULL,
};

