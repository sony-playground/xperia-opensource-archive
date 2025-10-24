/*! \file pm_clk_driver_init.c
 *  \n
 *  \brief This file contains CLOCK peripheral driver initialization during which the driver
 *         driver data is stored.
 *  \n
 *  \n &copy; Copyright 2013-2018 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/drivers/clk/src/init/pm_clk_driver_init.c#3 $

when        who     what, where, why
--------    ---     ----------------------------------------------------------
08/12/13    aks      Fix KW Errors
04/12/13    aks      Created as part of Code refactoring.
========================================================================== */
/*===========================================================================

                     INCLUDE FILES

===========================================================================*/
#include "pm_clk_driver.h"
#include "pm_version.h"
#include "pm_target_information.h"
#include "device_info.h"
#include "pm_debug.h"
#include "hw_module_type.h"
#include "pm_version.h"

/*===========================================================================

                        MACRO AND TYPE DEFINITIONS

===========================================================================*/
enum {
  PMIC_CLK_DIV_MAX_HW_VER    = 0x10,
  PMIC_CLK_CALRC3_MAX_HW_VER = 0x21,
  PMIC_CLK_XO_MAX_HW_VER     = 0x50,
  PMIC_CLK_BB_MAX_HW_VER     = 0x90, 
  PMIC_CLK_RF_MAX_HW_VER     = 0x80, 
  PMIC_CLK_SLEEP_MAX_HW_VER  = 0xB0,  
  PMIC_CLK_DIST_MAX_HW_VER   = 0xC2, 
};


/*===========================================================================

                        STATIC VARIABLES 

===========================================================================*/

static pm_clk_register_info_type clk_reg = 
{
  .peripheral_offset = 0x100,
  .STATUS1           = 0x08 ,            
  .EN_CTL            = 0x46 ,  
  .TIMER             = 0x4C ,
  .INT_EN_SET        = 0x15 ,  
  .INT_EN_CLR        = 0x16 ,
};

static pm_clk_type clk_common[PM_MAX_NUM_CLKS] ;

static pm_clk_type rf_clk_count, bb_clk_count, div_clk_count;

/* extern global variable to store the CLK driver data */
extern pm_clk_data_type *pm_clk_data_arr[PM_MAX_NUM_PMICS];

/*===========================================================================

                     LOCAL FUNCTION PROTOTYPE

===========================================================================*/
//static void pm_clk_periph_map_init(pm_clk_data_type *clk_ptr);
static void 
pm_clk_periph_arr_init (peripheral_info_type *peripheral_info,  
                        uint8 pmic_index, 
                        uint8 clk_index, 
                        uint8 dig_maj_min);

/*===========================================================================

                     INTERNAL DRIVER FUNCTIONS 

===========================================================================*/
__attribute__((section("rinit_code_sec_pool1")))
void pm_clk_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint8 pmic_index)
{
    pm_clk_data_type *clk_ptr = NULL;
    uint32 clk_index = 0;
    pm_register_address_type base_address = 0;
    pm_register_address_type periph_offset = 0, clk_dist_status_reg = 0;
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
    uint8 data = 0;

    pm_debug_info_type *pmic_debug = pm_get_debug_info();
    CORE_VERIFY_PTR(pmic_debug);
    pmic_debug->pm_clk_data_arr = pm_clk_data_arr;

    /* Initialize clock driver only for PMICs which have XO_CORE */
    if (pm_clk_data_arr[pmic_index] == NULL)
    {
     if ((peripheral_info->peripheral_subtype != PM_HW_MODULE_CLOCK_XO_CORE) &&
         (peripheral_info->peripheral_subtype != PM_HW_MODULE_CLOCK_XO_CORE_38P4MHZ)&&
         (peripheral_info->peripheral_subtype != PM_HW_MODULE_CLOCK_XO_CORE_76P8MHZ))
       {
           return;
       }
    }

    if ((peripheral_info->peripheral_subtype == PM_HW_MODULE_CLOCK_CALRC2) || 
        (peripheral_info->peripheral_subtype == PM_HW_MODULE_CLOCK_CALRC3) || 
        (peripheral_info->peripheral_subtype == PM_HW_MODULE_CLOCK_LFRC))
    {
       return;
    }

    clk_ptr = pm_clk_data_arr[pmic_index];
    
    if (clk_ptr == NULL)
    {
      /*Initializing the counts for new pmic*/
      rf_clk_count = (pm_clk_type)PM_CLK_1;
      bb_clk_count = (pm_clk_type)PM_CLK_6 ;
      div_clk_count = (pm_clk_type)PM_CLK_11;
      
      pm_malloc(sizeof(pm_clk_data_type), (void **)&clk_ptr);
      
      /*clearing clk _common values for new pmic*/
      memset(clk_common, PM_CLK_TYPE_INVALID, sizeof(clk_common));
      memset(clk_ptr->clk_common, PM_CLK_TYPE_INVALID, sizeof(clk_ptr->clk_common));
      memset(clk_ptr->clk_perph_index, PM_CLK_INVALID_DATA, sizeof(clk_ptr->clk_perph_index));
      
      /* Assign Comm ptr */
      clk_ptr->comm_ptr = comm_ptr;
      
      /* Clock Register Info */
      clk_ptr->clk_reg_table = &clk_reg;
      
      clk_ptr->base_address = peripheral_info->base_address;
      
      /* Work-around for the wrong LN_BB_CLK base address on PMD9635 PMICs */
      if (pm_get_pmic_model(pmic_index) == PMIC_IS_PMD9635)
      {
          clk_ptr->clk_perph_index[PM_CLK_LN_BB] = 2;
      }
     
      memset(clk_ptr->periph_subtype, 0, sizeof(clk_ptr->periph_subtype));
      memset(clk_ptr->dig_maj_min, 0, sizeof(clk_ptr->dig_maj_min));
      
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
                              pmic_index, 
                              clk_index,
                              clk_ptr->dig_maj_min[clk_index]);

      clk_ptr->clk_common[clk_index] = clk_common[clk_index];

      /* PMIC CLK periph index mapping table */
      if (clk_common[clk_index] < PM_CLK_MAX_INDEX)
      {
        clk_ptr->clk_perph_index[clk_common[clk_index]] = clk_index;
      }
      
      /* Save Clock's Peripheral Subtype value */
      clk_ptr->periph_subtype[clk_index] = peripheral_info->peripheral_subtype;

      clk_ptr->num_of_peripherals = clk_index + 1;
	  
      if(peripheral_info->peripheral_subtype == PM_HW_MODULE_CLOCK_CLK_DIST)
      {
        clk_dist_status_reg = peripheral_info->base_address + clk_reg.STATUS1;

        err_flag = pm_comm_read_byte(clk_ptr->comm_ptr->slave_id, clk_dist_status_reg, &data, 0);
        CORE_VERIFY(err_flag == PM_ERR_FLAG_SUCCESS);
        if((data & 0x7) == 5) //If XO_DIV is clock source then XO is always on.
        {
          clk_ptr->xo_always_on = TRUE;
        }
      }
    }
}

__attribute__((section("rinit_code_sec_pool1")))
uint8 pm_clk_get_num_peripherals(uint8 pmic_index)
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
      clk_common[clk_index] =(pm_clk_type)(bb_clk_count);
      ++bb_clk_count;
      break;
    
    case PM_HW_MODULE_CLOCK_RF_CLK:
      CORE_VERIFY(dig_maj_min <= PMIC_CLK_RF_MAX_HW_VER);
      clk_common[clk_index] =(pm_clk_type)(rf_clk_count);
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
    
    default:
      break;
  }
}

