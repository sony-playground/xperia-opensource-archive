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

$Header: //components/dev/aop.ho/5.0/vinodv.aop.ho.5.0.hamoa1/aop_proc/core/settings/pmic/config/kailua/pm_config_dep.c#1 $ 

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "pm_config_interface.h"

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource bob_b[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"bobb1",NULL},
  {"bobb2",NULL},
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_b[] =
{
  {NULL,NULL},  // this is invalid place holder
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
static pm_pwr_resource ldo_c[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"ldoc1",NULL},
  {"ldoc2",NULL},
  {"ldoc3",NULL},
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_d[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"ldod1",NULL},
  {"ldod2",NULL},
  {"ldod3",NULL},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_e[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"ldoe1","vrm.lmx"},
  {"ldoe2",NULL},
  {"ldoe3",NULL},
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_f[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"ldof1",NULL},
  {"ldof2",NULL},
  {"ldof3",NULL},
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_g[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"ldog1",NULL},
  {"ldog2",NULL},
  {"ldog3",NULL},
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_i[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"ldoi1",NULL},
  {"ldoi2",NULL},
  {"ldoi3",NULL},
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_j[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"ldoj1",NULL},
  {"ldoj2",NULL},
  {"ldoj3",NULL},
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_m[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"ldom1",NULL},
  {"ldom2",NULL},
  {"ldom3",NULL},
  {"ldom4",NULL},
  {"ldom5",NULL},
  {"ldom6",NULL},
  {"ldom7",NULL},
};


// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_c[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"smpc1","vrm.nsp"},
  {"smpc2",NULL},
  {"smpc3","vrm.mxc"},
  {"smpc4",NULL},
  {"smpc5","vrm.lcx"},
  {"smpc6","vrm.mx"},
  {"smpc7","vrm.mxg"},
  {"smpc8",NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_d[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"smpd1",NULL},
  {"smpd2",NULL},
  {"smpd3",NULL},
  {"smpd4",NULL},
  {"smpd5",NULL},
  {"smpd6",NULL},
  {"smpd7",NULL},
  {"smpd8",NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_e[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"smpe1",NULL},
  {"smpe2",NULL},
  {"smpe3",NULL},
  {"smpe4",NULL},
  {"smpe5",NULL},
  {"smpe6",NULL},
  {"smpe7",NULL},
  {"smpe8",NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_f[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"smpf1",NULL},
  {"smpf2",NULL},
  {"smpf3",NULL},
  {"smpf4",NULL},
  {"smpf5",NULL},
  {"smpf6",NULL},
  {"smpf7",NULL},
  {"smpf8",NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_g[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"smpg1","vrm.gfx"},
  {"smpg2",NULL},
  {"smpg3",NULL},
  {"smpg4",NULL},
  {"smpg5",NULL},
  {"smpg6",NULL},
  {"smpg7",NULL},
  {"smpg8",NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_i[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"smpi1",NULL},
  {"smpi2",NULL},
  {"smpi3",NULL},
  {"smpi4","vrm.ebi"},
  {"smpi5",NULL},
  {"smpi6",NULL},
  {"smpi7",NULL},
  {"smpi8",NULL},
};

// Component Resource Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_j[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"smpj1","vrm.cx"},
  {"smpj2",NULL},
  {"smpj3",NULL},
  {"smpj4",NULL},
  {"smpj5",NULL},
  {"smpj6","vrm.mmcx"},
  {"smpj7",NULL},
  {"smpj8",NULL},
};
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource clk_a[] =
{
   {NULL,NULL}, // this is invalid place holder
   {NULL,NULL}, //51
   {NULL,NULL}, //52
   {NULL,NULL}, //53
   {"clka1","NULL"}, //54
   {"clka2","NULL"}, //55
   {"clka3","rfclka3"}, //56
   {"clka4","rfclka4"}, //57
   {"clka5","rfclka5"}, //58
   {"clka6","vrm.xob"}, //59
   {"clka7","vrm.xob1"}, //5a
   {"clka8","rfclka8"}, //5b
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
  &ldo_b[2],
  &ldo_b[5],
  &ldo_b[8],
  &ldo_b[9],
  &ldo_b[13],
  &ldo_b[14],
  &ldo_b[16],
  &ldo_m[5],
  &ldo_m[7],
};
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *bob2_b_child_dep[] =
{
  &ldo_b[6],
  &ldo_b[7],
  &ldo_b[17],
};
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps4_c_child_dep[] =
{
  &ldo_b[1],
  &ldo_b[4],
  &ldo_b[10],
  &ldo_b[15],
  &ldo_d[3],
  &ldo_i[1],
  &ldo_m[3],
  &ldo_m[4],
  &ldo_m[6],
};
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps1_f_child_dep[] =
{
  &ldo_c[2],
  &ldo_c[3],
  &ldo_d[1],
  &ldo_d[2],
  &ldo_e[1],
  &ldo_e[2],
  &ldo_i[3],
  &ldo_j[1],
  &ldo_j[3],
};
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps5_j_child_dep[] =
{
  &ldo_b[3],
  &ldo_b[11],
  &ldo_b[12],
  &ldo_c[1],
  &ldo_e[3],
  &ldo_f[1],
  &ldo_f[2],
  &ldo_f[3],
  &ldo_i[2],
  &ldo_j[2],
  &ldo_m[1],
  &ldo_m[2],
};


__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info bob_dep_b[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // BOB1
   {
      NULL,// parent resource
      bob1_b_child_dep,// child resource dependencies
      9,  // num vreg children
      0,  // num xob children
   },
   // BOB2
   {
      NULL,// parent resource
      bob2_b_child_dep,// child resource dependencies
      3,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info clk_dep_a[] =
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

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_b[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1B
   {
      &smps_c[4],// parent resource S4C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2B
   {
	    &bob_b[1],// parent resource BOB1
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3B
   {
      &smps_j[5],// parent resource S5J
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L4B
   {
      &smps_c[4],// parent resource S4C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L5B
   {
	    &bob_b[1],// parent resource BOB1
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6B
   {
	    &bob_b[2],// parent resource BOB2
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L7B
   {
	    &bob_b[2],// parent resource BOB2
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L8B
   {
	    &bob_b[1],// parent resource BOB1
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L9B
   {
	   &bob_b[1],// parent resource BOB1
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L10B
   {
      &smps_c[4],// parent resource S4C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L11B
   {
      &smps_j[5],// parent resource S5J
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L12B
   {
      &smps_j[5],// parent resource S5J
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L13B
   {
	    &bob_b[1],// parent resource BOB1
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L14B
   {
	    &bob_b[1],// parent resource BOB1
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L15B
   {
      &smps_c[4],// parent resource S4C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L16B
   {
	    &bob_b[1],// parent resource BOB1
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L17B
   {
	    &bob_b[2],// parent resource BOB2
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_c[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1C
   {
      &smps_j[5],// parent resource S5J
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2
   {
      &smps_f[1],// parent resource S1F
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3C
   {
      &smps_f[1],// parent resource S1F
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_d[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1D
   {
      &smps_f[1],// parent resource S1F
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2D
   {
      &smps_f[1],// parent resource S1F
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3D
   {
      &smps_c[4],// parent resource S4C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_e[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1E
   {
      &smps_f[1],// parent resource S1F
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2E
   {
      &smps_f[1],// parent resource S1F
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3E
   {
      &smps_j[5],// parent resource S5J
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_f[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1F
   {
      &smps_j[5],// parent resource S5J
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2F
   {
      &smps_j[5],// parent resource S5J
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3F
   {
      &smps_j[5],// parent resource S5J
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_g[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1G
   {
      NULL,// parent resource UNUSED
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2G
   {
      NULL,// parent resource UNUSED
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3G
   {
      NULL,// parent resource UNUSED
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_i[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1I
   {
      &smps_c[4],// parent resource S4C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2I
   {
      &smps_j[5],// parent resource S5J
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3I
   {
      &smps_f[1],// parent resource S1F
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_j[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1J
   {
      &smps_f[1],// parent resource S1F
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2J
   {
      &smps_j[5],// parent resource S5J
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3J
   {
      &smps_f[1],// parent resource S1F
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_m[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1M
   {
      &smps_j[5],// parent resource S5J
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2M
   {
      &smps_j[5],// parent resource S5J
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3M
   {
      &smps_c[4],// parent resource S4C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L4M
   {
      &smps_c[4],// parent resource S4C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L5M
   {
	    &bob_b[1],// parent resource BOB1
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6M
   {
      &smps_c[4],// parent resource S4C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L7M
   {
	    &bob_b[1],// parent resource BOB1
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

// Component Resource Dependency Information
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info smps_dep_c[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // S1C
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S2C
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S3C
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S4C
   {
      NULL,// parent resource
      smps4_c_child_dep,// child resource dependencies
      9,  // num vreg children
      0,  // num xob children
   },
   // S5C
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S6C
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S7C
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S8C
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info smps_dep_d[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // S1D
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S2D
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S3D
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S4D
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S5D
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S6D
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S7D
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S8D
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info smps_dep_e[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // S1E
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S2E
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S3E
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S4E
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S5E
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S6E
   {
      NULL,// parent resource
      NULL,// child resource dependencies
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
pm_pwr_resource_dependency_info smps_dep_f[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // S1F
   {
      NULL,// parent resource
      smps1_f_child_dep,// child resource dependencies
      9,  // num vreg children
      0,  // num xob children
   },
   // S2F
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S3F
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S4F
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S5F
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S6F
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S7F
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S8F
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info smps_dep_g[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // S1G
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S2G
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S3G
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S4G
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S5G
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S6G
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S7G
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },   
   // S8G
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info smps_dep_i[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // S1I
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S2I
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S3I
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S4I
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S5I
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S6I
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S7I
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S8I
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info smps_dep_j[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // S1J
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S2J
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S3J
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S4J
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S5J
   {
      NULL,// parent resource
      smps5_j_child_dep,// child resource dependencies
      12,  // num vreg children
      0,  // num xob children
   },
   // S6J
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S7J
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S8J
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

// resource dependency info
__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource_dependency_info* smps_dep[] =
{
  NULL,
  NULL,
  smps_dep_c,
  smps_dep_d,
  smps_dep_e,
  smps_dep_f,
  smps_dep_g,
  NULL,
  smps_dep_i,
  smps_dep_j,
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
  ldo_dep_c,
  ldo_dep_d,
  ldo_dep_e,
  ldo_dep_f,
  ldo_dep_g,
  NULL,
  ldo_dep_i,
  ldo_dep_j,
  NULL,
  NULL,
  ldo_dep_m,
  NULL,
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
  NULL,
  smps_c,
  smps_d,
  smps_e,
  smps_f,
  smps_g,
  NULL,
  smps_i,
  smps_j,
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
  ldo_c,
  ldo_d,
  ldo_e,
  ldo_f,
  ldo_g,
  NULL,
  ldo_i,
  ldo_j,
  NULL,
  NULL,
  ldo_m,
  NULL,
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
