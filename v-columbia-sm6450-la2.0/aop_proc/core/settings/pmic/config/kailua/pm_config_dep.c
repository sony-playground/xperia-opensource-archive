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

$Header: //components/rel/aop.ho/4.0/aop_proc/core/settings/pmic/config/kailua/pm_config_dep.c#2 $ 

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
   {"smpd1","vrm.gfx"},
   {"smpd2",NULL},
   {"smpd3",NULL},
   {"smpd4","vrm.lcx"},
   {"smpd5",NULL},
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
   {"smpf3",NULL},
   {"smpf4","vrm.ebi"},
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
   {"lnbclka4",NULL}, //5c
   {NULL,NULL},  //5d
   {"divclka1",NULL},   //5e
   {NULL,NULL},
   {NULL,NULL},
};

// Component Resource Child Depend Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *
bob1_b_child_dep[] = 
{

};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *
bob2_b_child_dep[] = 
{

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
bob_dep_b[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // B1
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // B2
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
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
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L2
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L3
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L4
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
    // L5
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L7
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L8
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L9
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L10
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L11
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L12
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L13
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L14
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L15
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L16
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L17
   {
      NULL, //parent resource
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
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L2
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L3
   {
      NULL, //parent resource
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
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L2
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L3
   {
      NULL, //parent resource
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
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L2
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L3
   {
      NULL, //parent resource
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
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L2
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L3
   {
      NULL, //parent resource
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
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L2
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L3
   {
      NULL, //parent resource
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
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L2
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L3
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L4
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
    // L5
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L7
   {
      NULL, //parent resource
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
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L2
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L3
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L4
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
    // L5
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L7
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
ldo_dep_i[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L2
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L3
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L4
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
    // L5
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L7
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
ldo_dep_j[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L2
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L3
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,    // num vreg children
      0,    // num xob children
   },
   // L4
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
    // L5
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6
   {
      NULL, //parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L7
   {
      NULL, //parent resource
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
    ldo_dep_i,
    ldo_dep_j,
    ldo_dep_k,
    ldo_dep_l,
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
    ldo_i,
    ldo_j,
    ldo_k,
    ldo_l,
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

