/*! \file pm_clk_driver.c
 *  \n
 *  \brief  
 *  \n  
 *  \n &copy; Copyright 2013-2022 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

 
$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/clk/src/pm_clk_driver.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when        who     what, where, why
--------    ---     ----------------------------------------------------------
01/03/18    pxm     Support LN_BB_CLK3
11/12/17    aab     Moved common Register address defination to driver file  
07/16/14    akm     Comm change Updates
03/31/14    akm     Updated to the latest PMIC driver architecture  
09/25/13    kt      Updated clk module driver.
02/01/13    hw      Rearchitecting clk module driver to peripheral driver
========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_clk_driver.h"
#include "CoreVerify.h"

/*===========================================================================

                        MACRO AND TYPE DEFINITIONS

===========================================================================*/
enum {
  PMIC_CLK_DIV_MAX_HW_VER    = 0x10,
  PMIC_CLK_CALRC3_MAX_HW_VER = 0x21,
  PMIC_CLK_XO_MAX_HW_VER     = 0x65,
  PMIC_CLK_BB_MAX_HW_VER     = 0x90, 
  PMIC_CLK_RF_MAX_HW_VER     = 0x80, 
  PMIC_CLK_SLEEP_MAX_HW_VER  = 0xB0,  
  PMIC_CLK_DIST_MAX_HW_VER   = 0xC2, 
};

#define MAX_CALRC_SUPPORTED_ANA_REV  (0x00 << 8 | 0x01) // ANA_MAJOR 0 , ANA_MINOR 1

/*===========================================================================

                        STATIC VARIABLES

===========================================================================*/

/* Static global variable to store the CLK driver data */
static pm_clk_data_type *pm_clk_data_arr[PM_MAX_NUM_PMICS];

static pm_clk_type rf_clk_count, bb_clk_count, div_clk_count;

static pm_clk_register_info_type clk_reg =
{
  .peripheral_offset = 0x100,
  .revision2         = 0x001,
  .status1           = 0x008,
  .div_ctl1          = 0x043,
  .drv_n_ctrl        = 0x044, //drv_n_ctrl | drv_ctrl1 (legacy) 
  .drv_p_ctrl        = 0x04D, 
  .en_ctl            = 0x046,
  .pd_ctl            = 0x048,
  .pc_en_ctl         = 0x04A,
};

static pm_clk_xo_register_info_type clk_xo_reg =
{
  //  1.model_ctl1 - 2.xo_adj_fine
  .mode_ctl1 = 0x044, 
  .xo_adj_fine = 0x05B,
};

pm_clk_calrc_info_type clk_calrc_reg =
{
  .base_address   = 0x6400,
  .calrc_register =
  {
    .calrc_enable   = 0x69,
    .calrc_cfg      = 0x50, 
    .smpl_ctl1      = 0x48,
  }
};

// The index of each peripheral here equal to the peripheral offset in ipcat
static pm_clk_type clk_common[PM_MAX_NUM_CLKS];

/*===========================================================================

                     LOCAL FUNCTION PROTOTYPE

===========================================================================*/
static void 
pm_clk_periph_arr_init (peripheral_info_type *peripheral_info,  
                        uint8 pmic_index, 
                        uint8 clk_index, 
                        uint8 dig_maj_min);

void 
pm_calrc_driver_init (pm_comm_info_type *comm_ptr, 
                      peripheral_info_type *peripheral_info, 
                      uint8 pmic_index);
/*===========================================================================

                     INTERNAL DRIVER FUNCTIONS

===========================================================================*/

void 
pm_clk_driver_init (pm_comm_info_type *comm_ptr, 
                    peripheral_info_type *peripheral_info, 
                    uint8 pmic_index)
{
  pm_clk_data_type *clk_ptr = NULL;
  uint32 clk_index = 0;
  pm_register_address_type base_address = 0;
  pm_register_address_type periph_offset = 0;

  /* Initialize clock driver only for PMICs which have XO_CORE */
  if (pm_clk_data_arr[pmic_index] == NULL)
  {
    if ((peripheral_info->peripheral_subtype != PM_HW_MODULE_CLOCK_XO_CORE) &&
        (peripheral_info->peripheral_subtype != PM_HW_MODULE_CLOCK_XO_CORE_38P4MHZ) &&
        (peripheral_info->peripheral_subtype != PM_HW_MODULE_CLOCK_XO_CORE_76P8MHZ))
    {
      return;
    }
  }

  if ((peripheral_info->peripheral_subtype == PM_HW_MODULE_CLOCK_CALRC2) ||
      (peripheral_info->peripheral_subtype == PM_HW_MODULE_CLOCK_LFRC))
  {
    return;
  }
  else if (peripheral_info->peripheral_subtype == PM_HW_MODULE_CLOCK_CALRC3)
  {
    return pm_calrc_driver_init(comm_ptr, peripheral_info, pmic_index);
  }

  clk_ptr = pm_clk_data_arr[pmic_index];

  if (clk_ptr == NULL)
  {
    /*Initializing the counts for new pmic*/
    rf_clk_count = (pm_clk_type)PM_CLK_1;
    bb_clk_count = (pm_clk_type)PM_CLK_6 ;
    div_clk_count = (pm_clk_type)PM_CLK_11;

    pm_malloc(sizeof(pm_clk_data_type), (void **)&clk_ptr);

    /*clearing clk_common and clk_periph_index values for new pmic*/
    DALSYS_memset(clk_common, PM_CLK_TYPE_INVALID, sizeof(clk_common));
    DALSYS_memset(clk_ptr->clk_perph_index, PM_CLK_INVALID_DATA, sizeof(clk_ptr->clk_perph_index));

    /* Assign Comm ptr */
    clk_ptr->comm_ptr = comm_ptr;

    /* Store pointer to clock common */
    clk_ptr->clk_common = clk_common;

    /* Clock Register Info - Obtaining Data through dal config */
    clk_ptr->clk_reg_table = &clk_reg;

    clk_ptr->clk_xo_reg_table = &clk_xo_reg;

    clk_ptr->base_address = peripheral_info->base_address;

    DALSYS_memset(clk_ptr->periph_subtype, 0, sizeof(clk_ptr->periph_subtype));
    DALSYS_memset(clk_ptr->dig_maj_min, 0, sizeof(clk_ptr->dig_maj_min));

    pm_clk_data_arr[pmic_index] = clk_ptr;
  }

  if (clk_ptr != NULL)
  {
    base_address = clk_ptr->base_address;
    periph_offset = clk_ptr->clk_reg_table->peripheral_offset;

    /* Peripheral Baseaddress should be >= first peripheral's base addr */
    CORE_VERIFY(peripheral_info->base_address >= base_address);

    /* Calculate CLK peripheral index */
    clk_index = ((peripheral_info->base_address - base_address)/periph_offset);

    /* Peripheral Index should be less than max number of peripherals */
    CORE_VERIFY(clk_index < PM_MAX_NUM_CLKS);

    /* Save PMIC Clock's Peripheral digital version */
    clk_ptr->dig_maj_min[clk_index] = ((peripheral_info->digital_major_version << 0x4) | 
                                       (peripheral_info->digital_minor_version));

    pm_clk_periph_arr_init (peripheral_info, 
                            pmic_index, clk_index,
                            clk_ptr->dig_maj_min[clk_index]);

    /* PMIC CLK periph index mapping table */
    if (clk_common[clk_index] < PM_CLK_MAX_INDEX)
    {
      clk_ptr->clk_perph_index[clk_common[clk_index]] = clk_index;
    }

    /* Save Clock's Peripheral Subtype value */
    clk_ptr->periph_subtype[clk_index] = peripheral_info->peripheral_subtype;

    // update the clock peripheral count
    clk_ptr->num_of_peripherals = clk_index + 1;
  }
}


void 
pm_calrc_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info,  uint8 pmic_index)
{
  pm_clk_data_type        *clk_ptr          = pm_clk_data_arr[pmic_index];
  uint16                  analog_revision   = 0;

  if(clk_ptr == NULL)
  {
    return;
  }
  
  analog_revision  = (((peripheral_info->analog_major_version) << 8)  | (peripheral_info->analog_minor_version));

  if (clk_ptr->clk_calrc_reg_table == NULL)
  {
    clk_ptr->clk_calrc_reg_table = &clk_calrc_reg;
    clk_ptr->clk_calrc_reg_table->dig_maj_min = ((peripheral_info->digital_major_version << 4) | peripheral_info->digital_minor_version);
    
    if ((analog_revision > MAX_CALRC_SUPPORTED_ANA_REV) || 
        (clk_ptr->clk_calrc_reg_table->dig_maj_min > PMIC_CLK_CALRC3_MAX_HW_VER)) 
    {
      return;
    }
    
    clk_ptr->clk_calrc_reg_table->base_address = peripheral_info->base_address;
  }

  clk_ptr->clk_calrc_reg_table->num_of_peripherals++;
}

pm_clk_data_type* 
pm_clk_get_data (uint8 pmic_index)
{
  if(pmic_index < PM_MAX_NUM_PMICS)
  {
    return pm_clk_data_arr[pmic_index];
  }
  return NULL;
}


uint8 
pm_clk_get_num_peripherals (uint8 pmic_index)
{
  if((pmic_index < PM_MAX_NUM_PMICS) &&
      (pm_clk_data_arr[pmic_index] !=NULL))
  {
    return pm_clk_data_arr[pmic_index]->num_of_peripherals;
  }

  return 0;
}

static void 
pm_clk_periph_arr_init (peripheral_info_type *peripheral_info,  
                        uint8 pmic_index, 
                        uint8 clk_index, 
                        uint8 dig_maj_min)
{
  switch(peripheral_info->peripheral_subtype)
  {
    case PM_HW_MODULE_CLOCK_XO_CORE:
    case PM_HW_MODULE_CLOCK_XO_CORE_38P4MHZ:
    case PM_HW_MODULE_CLOCK_XO_CORE_76P8MHZ:
      CORE_VERIFY(dig_maj_min <= PMIC_CLK_XO_MAX_HW_VER);
      clk_common[clk_index] = PM_CLK_XO;
      break;
    case PM_HW_MODULE_CLOCK_CLK_DIST:
      CORE_VERIFY(dig_maj_min <= PMIC_CLK_DIST_MAX_HW_VER);
      clk_common[clk_index] = PM_CLK_DIST;
      break;

    case PM_HW_MODULE_CLOCK_BB_CLK:
      CORE_VERIFY(dig_maj_min <= PMIC_CLK_BB_MAX_HW_VER);
      clk_common[clk_index] = (pm_clk_type)(bb_clk_count);
      ++bb_clk_count;
      break;

    case PM_HW_MODULE_CLOCK_RF_CLK:
      CORE_VERIFY(dig_maj_min <= PMIC_CLK_RF_MAX_HW_VER);
      clk_common[clk_index] = (pm_clk_type)(rf_clk_count);
      ++rf_clk_count;
      break;

    case PM_HW_MODULE_CLOCK_DIV_CLK:
      CORE_VERIFY(dig_maj_min <= PMIC_CLK_DIV_MAX_HW_VER);
      clk_common[clk_index] = (pm_clk_type)(div_clk_count);
      ++div_clk_count;
      break;

    case PM_HW_MODULE_CLOCK_SLP_CLK:
      CORE_VERIFY(dig_maj_min  <= PMIC_CLK_SLEEP_MAX_HW_VER);
      clk_common[clk_index] = PM_CLK_SLEEP;
      break;
  }
}

