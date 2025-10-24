
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

$Header: $
 Version : 1.0
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/

#include "pm_config_interface.h"

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_b[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"ldob1","vrm.qlnk"},
  {"ldob2",NULL},
  {"ldob3","vrm.ebi"},
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
  {"ldob17","vrm.mx"},
  {"ldob18",NULL},
  {"ldob19",NULL},
  {"ldob20",NULL},
  {"ldob21",NULL},
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_b[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"smpb1","vrm.mss"},
  {"smpb2",NULL},
  {"smpb3","vrm.mxc"},
  {"smpb4",NULL},
  {"smpb5","vrm.cx"},
  {"smpb6",NULL},
  {"smpb7",NULL},
  {"smpb8",NULL},
  {"smpb9",NULL},
  {"smpb10",NULL},
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_k[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"smpk1",NULL},
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
   {"clka4",NULL}, //57
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
static pm_pwr_resource *smps2_b_child_dep_row[] =
{
  &ldo_b[1],
  &ldo_b[2],
  &ldo_b[12],
  &ldo_b[15],
  &ldo_b[18],
};
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps3_b_child_dep_row[] =
{
  &ldo_b[14],
};
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps4_b_child_dep_row[] =
{
  &ldo_b[5],
  &ldo_b[6],
};
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps7_b_child_dep_row[] =
{
  &ldo_b[3],
  &ldo_b[4],
  &ldo_b[7],
  &ldo_b[16],
  &ldo_b[19],
  &ldo_b[20],
  &ldo_b[21],
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps8_b_child_dep_row[] =
{
  &ldo_b[8],
  &ldo_b[9],
  &ldo_b[17],
};

//child-parent changes
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource *smps7_b_child_dep[] =
{
  &ldo_b[3],
  &ldo_b[4],
  &ldo_b[16],
  &ldo_b[20],
  &ldo_b[21],
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource *smps8_b_child_dep[] =
{
  &ldo_b[7],
  &ldo_b[8],
  &ldo_b[9],
  &ldo_b[17],
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource *smps10_b_child_dep[] =
{
  &ldo_b[19],
};

// Component Resource Dependency Information
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
   // L1B
   {
      &smps_b[2],// parent resource S2B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2B
   {
      &smps_b[2],// parent resource S2B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3B
   {
      &smps_b[7],// parent resource S7B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L4B
   {
      &smps_b[7],// parent resource S7B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L5B
   {
      &smps_b[4],// parent resource S4B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6B
   {
      &smps_b[4],// parent resource S4B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L7B
   {
      &smps_b[7],// parent resource S7B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L8B
   {
      &smps_b[8],// parent resource S8B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L9B
   {
      &smps_b[8],// parent resource S8B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L10B
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L11B
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L12B
   {
      &smps_b[2],// parent resource S2B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L13B
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L14B
   {
      &smps_b[3],// parent resource S3B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L15B
   {
      &smps_b[2],// parent resource S2B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L16B
   {
      &smps_b[7],// parent resource S7B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L17B
   {
      &smps_b[8],// parent resource S8B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L18B
   {
      &smps_b[2],// parent resource S2B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L19B
   {
      &smps_b[7],// parent resource S7B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L20B
   {
      &smps_b[7],// parent resource S7B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L21B
   {
      &smps_b[7],// parent resource S7B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info smps_dep_b[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // S1B
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S2B
   {
      NULL,// parent resource
      smps2_b_child_dep_row,// child resource dependencies
      5,  // num vreg children
      0,  // num xob children
   },
   // S3B
   {
      NULL,// parent resource
      smps3_b_child_dep_row,// child resource dependencies
      1,  // num vreg children
      0,  // num xob children
   },
   // S4B
   {
      NULL,// parent resource
      smps4_b_child_dep_row,// child resource dependencies
      2,  // num vreg children
      0,  // num xob children
   },
   // S5B
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S6B
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S7B
   {
      NULL,// parent resource
      smps7_b_child_dep_row,// child resource dependencies
      7,  // num vreg children
      0,  // num xob children
   },
   // S8B
   {
      NULL,// parent resource
      smps8_b_child_dep_row,// child resource dependencies
      3,  // num vreg children
      0,  // num xob children
   },
   // S9B
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S10B
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info smps_dep_k[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // S1k
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
  smps_dep_b,
  NULL,
  NULL,
  NULL,
  NULL,
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
  NULL,
  smps_b,
  NULL,
  NULL,
  NULL,
  NULL,
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

