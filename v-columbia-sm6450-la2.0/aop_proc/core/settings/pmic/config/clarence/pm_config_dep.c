#
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
when        who         what, where, why
--------    ---         ---------------------------------------------------
07/09/22    arua      Initial AOP Config
06/12/22    arua      Dynamic Modem Buck
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/

#include "pm_config_interface.h"

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_b[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"ldob1",NULL},
  {"ldob2","vrm.lcx"},
  {"ldob3",NULL},
  {"ldob4",NULL},
  {"ldob5",NULL},
  {"ldob6",NULL},
  {"ldob7",NULL},
  {"ldob8","vrm.lmx"},
  {"ldob9",NULL},
  {"ldob10",NULL},
  {"ldob11",NULL},
  {"ldob12",NULL},
  {"ldob13",NULL},
  {"ldob14",NULL},
  {"ldob15",NULL},
  {"ldob16",NULL},
  {"ldob17",NULL},
  {"ldob18",NULL},
  {"ldob19",NULL},
  {"ldob20",NULL},
  {"ldob21","vrm.qf"},
  {"ldob22",NULL},
  {"ldob23",NULL},
  {"ldob24",NULL},
  {"ldob25",NULL},
  {"ldob26",NULL},
  {"ldob27",NULL},
  {"ldob28",NULL},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_e[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"ldoe1",NULL},
  {"ldoe2",NULL},
  {"ldoe3",NULL},
  {"ldoe4",NULL},
  {"ldoe5",NULL},
  {"ldoe6",NULL},
  {"ldoe7",NULL},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_b[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"smpb1","vrm.mss"},
  {"smpb2","vrm.mx"},
  {"smpb3",NULL},
  {"smpb4",NULL},
  {"smpb5","vrm.cx"},
  {"smpb6","vrm.ebi"},
  {"smpb7",NULL},
  {"smpb8",NULL},
  {"smpb9",NULL},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_g[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"smpg1","vrm.mx"},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource clk_a[] =
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
static pm_pwr_resource *smps7_b_child_dep[] =
{
  &ldo_b[3],
  &ldo_b[6],
  &ldo_b[7],
  &ldo_b[10],
  &ldo_b[11],
};
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps8_b_child_dep[] =
{
  &ldo_b[8],
  &ldo_b[12],
  &ldo_b[13],
  &ldo_b[14],
};
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps9_b_child_dep[] =
{
  &ldo_b[18],
  &ldo_b[19],
  &ldo_b[20],
  &ldo_b[21],
  &ldo_b[22],
  &ldo_b[23],
};
// Component Resource Dependency Information
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info clk_dep_a[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // CLK_DIST
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
   // EMPTY
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // RF_CLK1
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // RF_CLK2
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // RF_CLK3
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // RF_CLK4
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // RF_CLK5
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // LN_BB_CLK1
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // LN_BB_CLK2
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // LN_BB_CLK3
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
   // EMPTY
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // DIV_CLK1
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
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2B
   {
      NULL,// parent resource
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
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L5B
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6B
   {
      &smps_b[7],// parent resource S7B
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
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L10B
   {
      &smps_b[7],// parent resource S7B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L11B
   {
      &smps_b[7],// parent resource S7B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L12B
   {
      &smps_b[8],// parent resource S8B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L13B
   {
      &smps_b[8],// parent resource S8B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L14B
   {
      &smps_b[8],// parent resource S8B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L15B
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L16B
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L17B
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L18B
   {
      &smps_b[9],// parent resource S9B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L19B
   {
      &smps_b[9],// parent resource S9B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L20B
   {
      &smps_b[9],// parent resource S9B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L21B
   {
      &smps_b[9],// parent resource S9B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L22B
   {
      &smps_b[9],// parent resource S9B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L23B
   {
      &smps_b[9],// parent resource S9B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L24B
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L25B
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L26B
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L27B
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L28B
   {
      NULL,// parent resource
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
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2E
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3E
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L4E
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L5E
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6E
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L7E
   {
      NULL,// parent resource
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
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S3B
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S4B
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
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
      smps7_b_child_dep,// child resource dependencies
      5,  // num vreg children
      0,  // num xob children
   },
   // S8B
   {
      NULL,// parent resource
      smps8_b_child_dep,// child resource dependencies
      4,  // num vreg children
      0,  // num xob children
   },
   // S9B
   {
      NULL,// parent resource
      smps9_b_child_dep,// child resource dependencies
      6,  // num vreg children
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

