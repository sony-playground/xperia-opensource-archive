/*! \file pm_clk.c
 *  \n 
 *  \brief Implementation file for CLOCK public APIs. 
 *  \n  
 *  \n &copy; Copyright 2013-2021 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

 
$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/clk/src/pm_clk.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
07/16/2014 akm     Comm change Updates
03/31/14   akm     Updated to the latest PMIC driver architecture 
09/25/13   kt      Updated clk module driver.
02/01/13   hw      Rearchitecting clk module driver to peripheral driver
===========================================================================*/
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_clk.h"
#include "pm_clk_driver.h"

/*===========================================================================
					 	   
		              DEFINITIONS
						   
===========================================================================*/

#define SLAVE_ID     clk_ptr->comm_ptr->slave_id
#define REG_CLK(reg) ((clk_ptr->base_address) + \
	                    ((pm_register_address_type)(clk_ptr->clk_reg_table->peripheral_offset*periph_index)) + \
                      (clk_ptr->clk_reg_table->reg))
#define DIG_MAJ_VER_4                    4
#define PC_EN_MASK                       0x01
#define PM_CLK_DEFAULT_DRV_STRENGTH_MASK 0x03
#define PM_CLK_N_P_DRV_STRENGTH_MASK     0x3F
#define PM_CLK_DRV_STRENGTH_INVALID      0x40
#define MIN_HW_VER_RF_BB_CLK_P_N_RATIO   0x60
#define DRV_STR_LEGACY_MASK              0x03
#define CLK_OK_STATUS_MSK                0x80
#define CLK_SW_EN_CTL_MSK                0x80

/*===========================================================================

                     API IMPLEMENTATION 

===========================================================================*/

pm_err_flag_type 
pm_clk_drv_strength (uint32 pmic_chip, 
                     pm_clk_type periph, 
                     pm_clk_drv_strength_type drive_strength)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_clk_data_type *clk_ptr = pm_clk_get_data(pmic_chip);
  pm_register_address_type reg = 0;
  uint32 periph_index = 0;

  if ((clk_ptr == NULL) || (periph >= PM_CLK_MAX_INDEX) || 
      (drive_strength >= PM_CLK_DRV_STRENGTH_INVALID))
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  periph_index = clk_ptr->clk_perph_index[periph];

  if((periph_index == PM_CLK_INVALID_DATA) || 
     (periph_index >= PM_MAX_NUM_CLKS))
  {
    return PM_ERR_FLAG_INVALID_PERIPHERAL;
  }

  uint32 peripheral_subtype = clk_ptr->periph_subtype[periph_index];

  if ((peripheral_subtype != PM_HW_MODULE_CLOCK_RF_CLK) && 
      (peripheral_subtype != PM_HW_MODULE_CLOCK_BB_CLK) && 
      (peripheral_subtype != PM_HW_MODULE_CLOCK_SLP_CLK))
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  if ((peripheral_subtype == PM_HW_MODULE_CLOCK_SLP_CLK) && 
      (drive_strength > DRV_STR_LEGACY_MASK))
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  /*TODO: Currently only supports N_DRVCTRL on RF/LNBB, check if need to extend
   * this for P_DRV_CTRL */
  reg = REG_CLK(drv_ctl1);

  /* Set strength */
  err_flag = pm_comm_write_byte_mask(clk_ptr->comm_ptr->slave_id, reg, PM_CLK_N_P_DRV_STRENGTH_MASK, (pm_register_data_type)(drive_strength));  

  /* Let the user know if we were successful or not */
  return err_flag;
}

pm_err_flag_type 
pm_clk_sw_enable (uint32 pmic_chip, 
                  pm_clk_type periph, 
                  pm_on_off_type on_off)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_clk_data_type *clk_ptr = pm_clk_get_data(pmic_chip);
  pm_register_address_type reg = 0;
  pm_register_data_type data = (PM_ON == on_off) ? 0xFF : 0x00;
  uint32 periph_index = 0;

  if ((clk_ptr == NULL) || 
      (periph >= PM_CLK_MAX_INDEX))
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  periph_index = clk_ptr->clk_perph_index[periph];

  if ((periph_index == PM_CLK_INVALID_DATA) || 
      (periph_index >= PM_MAX_NUM_CLKS))
  {
    return PM_ERR_FLAG_INVALID_PERIPHERAL;
  }

  uint32 peripheral_subtype = clk_ptr->periph_subtype[periph_index];

  /* No en_ctl support for CLK_DIST */
  if (!(peripheral_subtype) || 
      (peripheral_subtype == PM_HW_MODULE_CLOCK_CLK_DIST))
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  reg = REG_CLK(en_ctl);

  err_flag =  pm_comm_write_byte_mask(clk_ptr->comm_ptr->slave_id, reg , CLK_SW_EN_CTL_MSK, data); // 7

  return err_flag;
}

pm_err_flag_type 
pm_clk_pin_ctrled (uint32 pmic_chip, 
                   pm_clk_type periph, 
                   pm_on_off_type on_off)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_clk_data_type *clk_ptr = pm_clk_get_data(pmic_chip);
  pm_register_address_type reg = 0;
  pm_register_data_type data = (PM_ON == on_off) ? 0xFF : 0x00 ;
  uint32 periph_index = 0;

  if ((clk_ptr == NULL) || 
      (periph >= PM_CLK_MAX_INDEX))
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  periph_index = clk_ptr->clk_perph_index[periph];

  if((periph_index == PM_CLK_INVALID_DATA) || 
      (periph_index >= PM_MAX_NUM_CLKS))
  {
    return PM_ERR_FLAG_INVALID_PERIPHERAL;
  }

  uint32 peripheral_subtype = clk_ptr->periph_subtype[periph_index];

  /* pin control enable supported only for Clock Buffers RF/LNBB */
  if ((peripheral_subtype != PM_HW_MODULE_CLOCK_RF_CLK) && 
      (peripheral_subtype != PM_HW_MODULE_CLOCK_BB_CLK))
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  uint8 hw_ver = (clk_ptr->dig_maj_min[periph_index] >> 4);

  reg = (hw_ver >= DIG_MAJ_VER_4) ? REG_CLK(pc_en_ctl) : REG_CLK(en_ctl) ;

  err_flag = pm_comm_write_byte_mask(SLAVE_ID, reg , PC_EN_MASK, data); // 0   

  return err_flag;
}

pm_err_flag_type 
pm_clk_pull_down (uint32 pmic_chip, 
                  pm_clk_type periph, 
                  pm_on_off_type on_off)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_clk_data_type *clk_ptr = pm_clk_get_data(pmic_chip);
  pm_register_address_type reg = 0;
  pm_register_data_type data = (PM_ON == on_off) ? 0xFF : 0x00 ;
  uint8 periph_index = 0;

  if ((clk_ptr == NULL) || 
      (periph >= PM_CLK_MAX_INDEX))
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  periph_index = clk_ptr->clk_perph_index[periph];

  if((periph_index == PM_CLK_INVALID_DATA) || 
      (periph_index >= PM_MAX_NUM_CLKS))
  {
    return PM_ERR_FLAG_INVALID_PERIPHERAL;
  }
  
  uint32 periph_subtype = clk_ptr->periph_subtype[periph_index];

  /* pull-down ctl supported only for Clock Buffers RF/LNBB */
  if ((periph_subtype != PM_HW_MODULE_CLOCK_RF_CLK) && 
      (periph_subtype != PM_HW_MODULE_CLOCK_BB_CLK))
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  
  reg = REG_CLK(pd_ctl);

  err_flag = pm_comm_write_byte_mask(clk_ptr->comm_ptr->slave_id, reg , 0x80, data); // 7

  return err_flag;
}


pm_err_flag_type 
pm_clk_set_out_clk_div (uint32 pmic_chip, 
                        pm_clk_type clk, 
                        uint32 divider)
{
  pm_err_flag_type         err_flag   = PM_ERR_FLAG_SUCCESS;
  pm_register_address_type reg;
  pm_register_data_type    data = 0;
  uint8 mask = 0x07;

  pm_clk_data_type *clk_ptr = pm_clk_get_data(pmic_chip);

  if ((clk_ptr == NULL) || 
      (clk >= PM_CLK_MAX_INDEX))
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  uint8 periph_index = clk_ptr->clk_perph_index[clk];

  if (clk_ptr->periph_subtype[periph_index] != PM_HW_MODULE_CLOCK_DIV_CLK)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  /*data = log2divider*/
  while (divider && (data < 7))
  {
    divider >>= 1;
    data++;
  }

 reg = REG_CLK(div_ctl1);

  err_flag = pm_comm_write_byte_mask(clk_ptr->comm_ptr->slave_id, reg, mask, data);

  return err_flag;
}

pm_err_flag_type 
pm_clk_get_status (uint32 pmic_chip, 
                   pm_clk_type clk, 
                   pm_clk_status_type *clk_status)
{
  pm_clk_data_type*             clk_ptr = pm_clk_get_data(pmic_chip);
  pm_err_flag_type             err_flag = PM_ERR_FLAG_SUCCESS;
  uint32                   periph_index = 0;
  pm_register_address_type          reg = 0;
  pm_register_data_type            data = 0;
  uint8                            mask = PM_CLK_N_P_DRV_STRENGTH_MASK;
  boolean                     read_flag = TRUE;

  if ((clk_ptr == NULL) || (clk >= PM_CLK_MAX_INDEX))
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  if (clk_status == NULL)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER; 
  }

  periph_index = clk_ptr->clk_perph_index[clk];
  uint32 periph_subtype = clk_ptr->periph_subtype[periph_index];

  reg = REG_CLK(drv_ctl1);

  switch (periph_subtype)
  {
    case PM_HW_MODULE_CLOCK_RF_CLK:
    case PM_HW_MODULE_CLOCK_BB_CLK:
      if(clk_ptr->dig_maj_min[periph_index] < MIN_HW_VER_RF_BB_CLK_P_N_RATIO)
      {
        mask = PM_CLK_DEFAULT_DRV_STRENGTH_MASK;
      }
      break;
    case PM_HW_MODULE_CLOCK_SLP_CLK:
      mask = PM_CLK_DEFAULT_DRV_STRENGTH_MASK;
      break;
    default:
      read_flag = FALSE;
      break;
  }

  /* get drive strength */
  if (read_flag)
  {
    err_flag = pm_comm_read_byte_mask(clk_ptr->comm_ptr->slave_id, reg, mask, &data);
    clk_status->clk_drv_strength = (uint8)data;
  }
  else
  {
    clk_status->clk_drv_strength = PM_CLK_DRV_STRENGTH_INVALID;
  }

  /* Clock OK status */
  reg = REG_CLK(status1);

  err_flag |= pm_comm_read_byte(clk_ptr->comm_ptr->slave_id, reg, &data);
  clk_status->clk_ok = (data & CLK_OK_STATUS_MSK) ? PM_ON : PM_OFF;

  /* Enable status */
  reg = REG_CLK(en_ctl);

  err_flag |= pm_comm_read_byte(clk_ptr->comm_ptr->slave_id, reg, &data);

  clk_status->clk_sw_enable = (data & CLK_SW_EN_CTL_MSK) ? PM_ON : PM_OFF;

  if ((periph_subtype == PM_HW_MODULE_CLOCK_RF_CLK) || 
      (periph_subtype == PM_HW_MODULE_CLOCK_BB_CLK))
  {
    /* Pin_ctrl status */
    uint8 hw_ver = (clk_ptr->dig_maj_min[periph_index] >> 4);

    reg = (hw_ver >= DIG_MAJ_VER_4) ? REG_CLK(pc_en_ctl) : REG_CLK(en_ctl) ;

    err_flag |= pm_comm_read_byte_mask(SLAVE_ID, reg, PC_EN_MASK, &data);

    clk_status->clk_pin_ctrled = (data & 0x01) ? PM_ON : PM_OFF;

    /* PD config */
    reg = REG_CLK(pd_ctl);

    err_flag = pm_comm_read_byte(clk_ptr->comm_ptr->slave_id, reg, &data);  

    clk_status->clk_pull_down = (data & 0x80) ? PM_ON : PM_OFF;
  }
  else
  {
    clk_status->clk_pin_ctrled = PM_INVALID;
    clk_status->clk_pull_down  = PM_INVALID;
  }

  /* DIV control */
  if (periph_subtype == PM_HW_MODULE_CLOCK_DIV_CLK)
  {
    reg = REG_CLK(div_ctl1);
    err_flag = pm_comm_read_byte(clk_ptr->comm_ptr->slave_id, reg, &data);
    clk_status->clk_out_div = data & 0x7;
  }
  else
  {
    clk_status->clk_out_div = 0;
  }

  return err_flag;
}

