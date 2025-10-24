
/*! \file pm_config_dep.c
 *
 *  \brief This file contains pmic resource dependencies.
 *
 *  &copy; Copyright 2016 - 2022 Qualcomm Technologies Inc, All Rights Reserved
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/settings/pmic/config/lanai/pm_config_dep.c#4 $
 Version : 1.0
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/

#include "pm_config_interface.h"

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
  {"ldob15","vrm.qf"},
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
  {"ldod2","vrm.lmx"},
  {"ldod3",NULL},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_e[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"ldoe1",NULL},
  {"ldoe2",NULL},
  {"ldoe3",NULL},
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
  {"ldoi3","vrm.qlnk"},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_k[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"ldok1",NULL},
  {"ldok2",NULL},
  {"ldok3",NULL},
  {"ldok4",NULL},
  {"ldok5",NULL},
  {"ldok6",NULL},
  {"ldok7",NULL},
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


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_n[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"ldon1",NULL},
  {"ldon2",NULL},
  {"ldon3",NULL},
  {"ldon4",NULL},
  {"ldon5",NULL},
  {"ldon6",NULL},
  {"ldon7",NULL},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_c[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"smpc1",NULL},
  {"smpc2",NULL},
  {"smpc3",NULL},
  {"smpc4",NULL},
  {"smpc5",NULL},
  {"smpc6",NULL},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_d[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"smpd1",NULL},
  {"smpd2",NULL},
  {"smpd3","vrm.mxc"},
  {"smpd4","vrm.lcx"},
  {"smpd5","vrm.gfx"},
  {"smpd6",NULL},
};


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
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_g[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"smpg1","vrm.nsp2"},
  {"smpg2",NULL},
  {"smpg3",NULL},
  {"smpg4","vrm.ebi"},
  {"smpg5","vrm.mss"},
  {"smpg6",NULL},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_i[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"smpi1","vrm.mmcx"},
  {"smpi2",NULL},
  {"smpi3","vrm.mx"},
  {"smpi4",NULL},
  {"smpi5",NULL},
  {"smpi6","vrm.nsp1"},
  {"smpi7",NULL},
  {"smpi8","vrm.cx"},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource clk_a[] =
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
  &ldo_b[2],
  &ldo_b[5],
  &ldo_b[6],
  &ldo_b[7],
  &ldo_b[8],
  &ldo_b[9],
  &ldo_b[13],
  &ldo_b[14],
  &ldo_b[16],
  &ldo_m[6],
  &ldo_m[7],
  &ldo_n[7],
};
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *bob2_b_child_dep[] =
{
  &ldo_b[17],
  &ldo_m[3],
  &ldo_m[4],
  &ldo_n[5],
  &ldo_n[6],
};
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps1_c_child_dep[] =
{
  &ldo_b[3],
  &ldo_b[11],
  &ldo_c[1],
  &ldo_c[2],
  &ldo_c[3],
  &ldo_e[1],
  &ldo_g[2],
  &ldo_m[1],
  &ldo_m[2],
  &ldo_n[1],
  &ldo_n[2],
};
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps2_c_child_dep[] =
{
  &ldo_d[3],
  &ldo_k[7],
};
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps3_c_child_dep[] =
{
  &ldo_d[1],
  &ldo_d[2],
  &ldo_e[2],
  &ldo_e[3],
  &ldo_g[1],
  &ldo_g[3],
  &ldo_i[2],
  &ldo_k[1],
  &ldo_k[2],
  &ldo_k[5],
};
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps4_c_child_dep[] =
{
  &ldo_k[3],
  &ldo_k[4],
};
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps6_c_child_dep[] =
{
  &ldo_b[1],
  &ldo_b[4],
  &ldo_b[10],
  &ldo_b[12],
  &ldo_b[15],
  &ldo_k[6],
  &ldo_m[5],
  &ldo_n[3],
  &ldo_n[4],
};
// Component Resource Dependency Information
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info bob_dep_b[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // BOB1
   {
      NULL,// parent resource
      bob1_b_child_dep,// child resource dependencies
      12,  // num vreg children
      0,  // num xob children
   },
   // BOB2
   {
      NULL,// parent resource
      bob2_b_child_dep,// child resource dependencies
      5,  // num vreg children
      0,  // num xob children
   },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info clk_dep_a[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // CLK1_RF
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // CLK2_RF
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // CLK3_RF
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // CLK4_RF
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // CLK5_RF
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // CLK6_LN
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // CLK7_LN
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // CLK8_LN
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // CLK9_LN
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // EMPTY
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // CLK11_DIV
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // EMPTY
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // SLEEP_CLK1
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_b[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L01B
   {
      &smps_c[6],// parent resource S6C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L02B
   {
	  &bob_b[1],// parent resource BOB1
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L03B
   {
      &smps_c[1],// parent resource S1C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L04B
   {
      &smps_c[6],// parent resource S6C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L05B
   {
	  &bob_b[1],// parent resource BOB1
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L06B
   {
	  &bob_b[1],// parent resource BOB1
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L07B
   {
	  &bob_b[1],// parent resource BOB1
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L08B
   {
	  &bob_b[1],// parent resource BOB1
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L09B
   {
	  &bob_b[1],// parent resource BOB1
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L10B
   {
      &smps_c[6],// parent resource S6C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L11B
   {
      &smps_c[1],// parent resource S1C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L12B
   {
      &smps_c[6],// parent resource S6C
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
      &smps_c[6],// parent resource S6C
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
      &smps_c[1],// parent resource S1C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2C
   {
      &smps_c[1],// parent resource S1C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3C
   {
      &smps_c[1],// parent resource S1C
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
      &smps_c[3],// parent resource S3C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2D
   {
      &smps_c[3],// parent resource S3C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3D
   {
      &smps_c[2],// parent resource S2C
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
      &smps_c[1],// parent resource S1C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2E
   {
      &smps_c[3],// parent resource S3C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3E
   {
      &smps_c[3],// parent resource S3C
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
      &smps_c[3],// parent resource S3C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2G
   {
      &smps_c[1],// parent resource S1C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3G
   {
      &smps_c[3],// parent resource S3C
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
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2I
   {
      &smps_c[3],// parent resource S3C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3I
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_k[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1K
   {
      &smps_c[3],// parent resource S3C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2K
   {
      &smps_c[3],// parent resource S3C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3K
   {
      &smps_c[4],// parent resource S4C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L4K
   {
      &smps_c[4],// parent resource S4C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L5K
   {
      &smps_c[3],// parent resource S3C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6K
   {
      &smps_c[6],// parent resource S6C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L7K
   {
      &smps_c[2],// parent resource S2C
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
      &smps_c[1],// parent resource S1C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2M
   {
      &smps_c[1],// parent resource S1C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3M
   {
	  &bob_b[2],// parent resource BOB2
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L4M
   {
	  &bob_b[2],// parent resource BOB2
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L5M
   {
      &smps_c[6],// parent resource S6C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6M
   {
	  &bob_b[1],// parent resource BOB1
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


__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_n[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1N
   {
      &smps_c[1],// parent resource S1C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2N
   {
      &smps_c[1],// parent resource S1C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3N
   {
      &smps_c[6],// parent resource S6C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L4N
   {
      &smps_c[6],// parent resource S6C
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L5N
   {
	  &bob_b[2],// parent resource BOB2
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6N
   {
	  &bob_b[2],// parent resource BOB2
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L7N
   {
	  &bob_b[1],// parent resource BOB1
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};


__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info smps_dep_c[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // S1C
   {
      NULL,// parent resource
      smps1_c_child_dep,// child resource dependencies
      11,  // num vreg children
      0,  // num xob children
   },
   // S2C
   {
      NULL,// parent resource
      smps2_c_child_dep,// child resource dependencies
      2,  // num vreg children
      0,  // num xob children
   },
   // S3C
   {
      NULL,// parent resource
      smps3_c_child_dep,// child resource dependencies
      10,  // num vreg children
      0,  // num xob children
   },
   // S4C
   {
      NULL,// parent resource
      smps4_c_child_dep,// child resource dependencies
      2,  // num vreg children
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
      smps6_c_child_dep,// child resource dependencies
      9,  // num vreg children
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

// resource dependency info
__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource_dependency_info* smps_dep[] =
{
  NULL,
  NULL,
  smps_dep_c,
  smps_dep_d,
  smps_dep_e,
  NULL,
  smps_dep_g,
  NULL,
  smps_dep_i,
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
  ldo_dep_c,
  ldo_dep_d,
  ldo_dep_e,
  NULL,
  ldo_dep_g,
  NULL,
  ldo_dep_i,
  NULL,
  ldo_dep_k,
  NULL,
  ldo_dep_m,
  ldo_dep_n,
  NULL,
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
  NULL,
  smps_g,
  NULL,
  smps_i,
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
  ldo_c,
  ldo_d,
  ldo_e,
  NULL,
  ldo_g,
  NULL,
  ldo_i,
  NULL,
  ldo_k,
  NULL,
  ldo_m,
  ldo_n,
  NULL,
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
  NULL,
  NULL,
};

