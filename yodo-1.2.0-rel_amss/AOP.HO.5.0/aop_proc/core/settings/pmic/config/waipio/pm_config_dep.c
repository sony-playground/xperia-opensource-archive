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

$Header: //components/rel/aop.ho/5.0/aop_proc/core/settings/pmic/config/waipio/pm_config_dep.c#1 $ 

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "pm_config_interface.h"

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
smps_b[] =
{
   {NULL,NULL}, // this is invalid place holder
   {"smpb1",NULL},
   {"smpb2",NULL},
   {"smpb3",NULL},
   {"smpb4",NULL},
   {"smpb5","vrm.gfx"},
   {"smpb6",NULL},
   {"smpb7",NULL},
   {"smpb8",NULL},
   {"smpb9",NULL},
   {"smpb10","vrm.qf"},
   {"smpb11",NULL},
   {"smpb12",NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
smps_c[] =
{
   {NULL,NULL}, // this is invalid place holder
   {"smpc1",NULL},
   {"smpc2","vrm.mxc"},
   {"smpc3",NULL},
   {"smpc4","vrm.mss"},
   {"smpc5",NULL},
   {"smpc6","vrm.cx"},
   {"smpc7",NULL},
   {"smpc8",NULL},
   {"smpc9",NULL},
   {"smpc10",NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
smps_e[] =
{
   {NULL,NULL}, // this is invalid place holder
   {"smpe1",NULL},
   {"smpe2",NULL},
   {"smpe3",NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
smps_h[] =
{
   {NULL,NULL}, // this is invalid place holder
   {"smph1",NULL},
   {"smph2","vrm.ebi"},
   {"smph3",NULL},
   {"smph4","vrm.mmcx"},
   {"smph5",NULL},
   {"smph6","vrm.mx"},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
bob_c[] =
{
   {NULL,NULL}, // this is invalid place holder
   {"bobc1",NULL},
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
   {"ldob8","vrm.lcx"},
   {"ldob9",NULL},
   {"ldob10",NULL},
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
ldo_c[] =
{
   {NULL,NULL}, // this is invalid place holder
   {"ldoc1",NULL},
   {"ldoc2",NULL},
   {"ldoc3",NULL},
   {"ldoc4",NULL},
   {"ldoc5",NULL},
   {"ldoc6",NULL},
   {"ldoc7",NULL},
   {"ldoc8",NULL},
   {"ldoc9",NULL},
   {"ldoc10",NULL},
   {"ldoc11",NULL},
   {"ldoc12",NULL},
   {"ldoc13",NULL},
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
ldo_d[] =
{
   {NULL,NULL}, // this is invalid place holder
   {"ldod1",NULL},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
ldo_e[] =
{
   {NULL,NULL}, // this is invalid place holder
   {"ldoe1",NULL},
   {"ldoe2",NULL},
   {"ldoe3",NULL},
   {"ldoe4",NULL},
   {"ldoe5",NULL},
   {"ldoe6",NULL},
   {"ldoe7",NULL},
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
ldo_f[] =
{
   {NULL,NULL}, // this is invalid place holder
   {"ldof1",NULL},
   {"ldof2",NULL},
   {"ldof3",NULL},
   {"ldof4",NULL},
   {"ldof5",NULL},
   {"ldof6",NULL},
   {"ldof7",NULL},
   {"ldof8",NULL},
   {"ldof9",NULL},
   {"ldof10",NULL},
   {"ldof11",NULL},
   {"ldof12",NULL},
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
ldo_h[] =
{
   {NULL,NULL}, // this is invalid place holder
   {"ldoh1","vrm.lmx"},
   {"ldoh2",NULL},
   {"ldoh3",NULL},
   {"ldoh4",NULL},
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
ldo_i[] =
{
   {NULL,NULL}, // this is invalid place holder
   {"ldoi1",NULL},
   {"ldoi2",NULL},
   {"ldoi3",NULL},
   {"ldoi4",NULL},
   {"ldoi5",NULL},
   {"ldoi6",NULL},
   {"ldoi7",NULL},
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
ldo_j[] =
{
   {NULL,NULL}, // this is invalid place holder
   {"ldoj1",NULL},
   {"ldoj2",NULL},
   {"ldoj3",NULL},
   {"ldoj4",NULL},
   {"ldoj5",NULL},
   {"ldoj6",NULL},
   {"ldoj7",NULL},
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource
clk_a[] =
{
   {NULL,NULL}, // this is invalid place holder
   {NULL,NULL}, //51
   {NULL,NULL}, //52
   {NULL,NULL}, //53
   {"rfclka1",NULL}, //54
   {"rfclka2",NULL}, //55
   {"rfclka3",NULL}, //56
   {"rfclka4",NULL}, //57
   {"rfclka5",NULL}, //58
   {"lnbclka1","vrm.xob"}, //59
   {"lnbclka2",NULL}, //5a
   {"lnbclka3",NULL}, //5b
   {NULL,NULL},  //5c
   {NULL,NULL},  //5d
   {"divclka1",NULL},   //5e
   {NULL,NULL},
   {NULL,NULL},
};

// Component Resource Child Depend Structure Creation
__attribute__((section("pm_ddr_reclaim_pool"))) 
static pm_pwr_resource *
smps11_b_child_dep[] =
{
  &ldo_b[1],
  &ldo_b[3],
  //&ldo_b[4],
  //&ldo_b[5],
  &ldo_h[1],
  &ldo_h[2],
  &ldo_h[3],
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *
smps12_b_child_dep[] = 
{
  //&ldo_b[6],
  &ldo_b[9],
  //&ldo_b[10],
  &ldo_c[10],
  &ldo_d[1],
  //&ldo_i[1], //Unused
  &ldo_i[2],
  &ldo_j[1],
  &ldo_j[2],
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *
smps1_c_child_dep[] =
{
  &ldo_c[1],
  &ldo_c[2],
  &ldo_c[8],
  &ldo_c[12],
  &ldo_e[4],
  &ldo_f[4],
  //&ldo_f[10],
  //&ldo_h[4],
  //&ldo_i[5], //unused
  &ldo_j[3],
  &ldo_j[4],
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *
smps1_e_child_dep[] = 
{
  &ldo_e[3],
  &ldo_e[5],
  &ldo_e[6],
  &ldo_f[1],
  &ldo_f[2],
  //&ldo_f[3],
  //&ldo_f[7],
  //&ldo_f[8],
  //&ldo_f[9],
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *
smps2_e_child_dep[] =
{
  &ldo_e[1],
  &ldo_e[2],
  &ldo_f[5],
  &ldo_f[6],
  //&ldo_f[11],
  //&ldo_f[12],
};

/*__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *
smps2_h_child_dep[] =
{
  //&ldo_b[8],
};*/

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *
bob1_c_child_dep[] = 
{
  &ldo_b[2],
  &ldo_b[7],
  &ldo_c[3],
  &ldo_c[4],
  &ldo_c[5],
  &ldo_c[6],
  &ldo_c[7],
  &ldo_c[9],
  //&ldo_c[11], //unused
  &ldo_c[13],
  &ldo_e[7],
  &ldo_i[3],
  &ldo_i[4],
  &ldo_i[6],
  &ldo_i[7],
  &ldo_j[5],
  &ldo_j[6],
  &ldo_j[7],
};

// Component Resource Dependency Information
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
smps_dep_b[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // S1
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S2
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S3
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S4
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S5
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children 5
      0,  // num xob children 
   },
   // S6
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S7
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S8
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S9
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S10
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S11
   {
      NULL, // parent resource
      smps11_b_child_dep, // child resource dependencies
      5,  // num vreg children
      0,  // num xob children
   },
   // S12
   {
      NULL, // parent resource
      smps12_b_child_dep, // child resource dependencies
      6,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
smps_dep_c[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // S1
   {
      NULL, // parent resource
      smps1_c_child_dep, // child resource dependencies
      8,  // num vreg children
      0,  // num xob children
   },
   // S2
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S3
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S4
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S5
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S6
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S7
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S8
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S9
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S10
   {
      NULL, // parent resource
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
      NULL, 
      smps1_e_child_dep, // child resource dependencies
      5,  // num vreg children
      0,  // num xob children
   },
   // S2
   {
      NULL,
      smps2_e_child_dep, // child resource dependencies
      4,  // num vreg children
      0,  // num xob children
   },
   // S3
   {
      NULL,
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
smps_dep_h[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // S1
   {
      NULL, 
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S2
   {
      NULL,
      NULL,//smps2_h_child_dep, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S3
   {
      NULL,
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S4
   {
      NULL,
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S5
   {
      NULL,
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S6
   {
      NULL,
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
bob_dep_c[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // B1
   {
      NULL,
      bob1_c_child_dep, // child resource dependencies
      17,  // num vreg children
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
      &smps_b[11],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2
   {
      &bob_c[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3
   {
      &smps_b[11],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L4
   {
      NULL, //&smps_b[11],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L5
   {
      NULL, //&smps_b[11],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6
   {
      NULL, //&smps_b[12],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L7
   {
      &bob_c[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L8
   {
      NULL, //&smps_h[2],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L9
   {
      &smps_b[12],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L10
   {
      NULL, //&smps_b[12],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
ldo_dep_c[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1
   {
      &smps_c[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2
   {
      &smps_c[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3
   {
      &bob_c[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L4
   {
      &bob_c[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L5
   {
      &bob_c[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6
   {
      &bob_c[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L7
   {
      &bob_c[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L8
   {
      &smps_c[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L9
   {
      &bob_c[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L10
   {
      &smps_b[12],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L11
   {
      NULL,//&bob_c[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L12
   {
      &smps_c[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L13
   {
      &bob_c[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
ldo_dep_d[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1
   {
      &smps_b[12],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
ldo_dep_e[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1
   {
      &smps_e[2],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2
   {
      &smps_e[2],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3
   {
      &smps_e[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L4
   {
      &smps_c[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L5
   {
      &smps_e[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6
   {
      &smps_e[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L7
   {
      &bob_c[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
ldo_dep_f[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1
   {
      &smps_e[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2
   {
      &smps_e[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3
   {
      NULL, //&smps_e[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L4
   {
      &smps_c[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L5
   {
      &smps_e[2],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6
   {
      &smps_e[2],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L7
   {
      NULL, //&smps_e[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L8
   {
      NULL, //&smps_e[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L9
   {
      NULL, //&smps_e[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L10
   {
      NULL, //&smps_c[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L11
   {
      NULL, // &smps_e[2],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L12
   {
      NULL, //&smps_e[2],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
ldo_dep_h[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1
   {
      &smps_b[11],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2
   {
      &smps_b[11],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3
   {
      &smps_b[11],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L4
   {
      NULL, //&smps_c[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
ldo_dep_i[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1
   {
      NULL, //&smps_b[12], //unused
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2
   {
      &smps_b[12], //&smps_b[12],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3
   {
      &bob_c[1], //&bob_c[1],
      NULL,      // child resource dependencies
      0,         // num vreg children
      0,         // num xob children
   },
   // L4
   {
      &bob_c[1], //&bob_c[1],
      NULL,      // child resource dependencies
      0,         // num vreg children
      0,         // num xob children
   },
    // L5
   {
      NULL,       //&smps_c[1], unused
      NULL,       // child resource dependencies
      0,          // num vreg children
      0,          // num xob children
   },
   // L6
   {
      &bob_c[1], //&bob_c[1],
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L7
   {
      &bob_c[1], //&bob_c[1],
      NULL,      // child resource dependencies
      0,         // num vreg children
      0,         // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
ldo_dep_j[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1
   {
      &smps_b[12], //&smps_b[12],
      NULL,        // child resource dependencies
      0,           // num vreg children
      0,           // num xob children
   },
   // L2
   {
      &smps_b[12], //&smps_b[12],
      NULL,        // child resource dependencies
      0,           // num vreg children
      0,           // num xob children
   },
   // L3
   {
      &smps_c[1], //&smps_c[1],
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L4
   {
      &smps_c[1], //&smps_c[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
    // L5
   {
      &bob_c[1], //&bob_c[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6
   {
      &bob_c[1], //&bob_c[1],
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L7
   {
      &bob_c[1], //&bob_c[1],
      NULL,      // child resource dependencies
      0,         // num vreg children
      0,         // num xob children
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
    smps_dep_b, 
    smps_dep_c, 
    NULL, 
    smps_dep_e,
    NULL,
    NULL,
    smps_dep_h,
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
    NULL,
    ldo_dep_h,
    ldo_dep_i,
    ldo_dep_j,
};


__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource_dependency_info* 
bob_dep[] = 
{
    NULL, 
    NULL,
    bob_dep_c,
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
    smps_b,
    smps_c, 
    NULL, 
    smps_e,
    NULL,
    NULL,
    smps_h,
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
    NULL,
    ldo_h,
    ldo_i,
    ldo_j,
};


__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource* 
bob_rsrc[] = 
{
    NULL, 
    NULL,
    bob_c,
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

