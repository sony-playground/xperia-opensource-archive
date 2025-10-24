/*! \file pm_pon.c
*  \n
*  \brief This file contains the implementation of the PowerON peripheral driver APIs.
*  \n
*  \n &copy; Copyright 2012-2018 QUALCOMM Technologies Incorporated, All Rights Reserved
*/
/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/drivers/pon/src/pm_pon.c#2 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/03/18   akm     Updated pm_err_flags
02/02/17   akm     Moved PMIC,SPMI out to Systemdrivers
11/14/16   akt     Removed compiler warnings(CR-1038901)
07/17/16   aab     Updated pm_pon_ps_hold_cfg() to support xbl_sec_image
03/28/16   aab     Added pm_pon_gp_reset_cfg() and pm_pon_get_reset_config_val()
02/16/15   vtw     Updated for the APPs level API support.
06/24/13   ps      Added PON Stage3 reset config API CR#495834
02/27/13   kt      Added PON Reasons and IRQ related APIs
01/24/13   umr     Add new version support.
11/20/12   umr     Created
========================================================================== */

/*===========================================================================
                  INCLUDE
===========================================================================*/
#include "pm_pon.h"
#include "pmio_pon.h"
#include "hw_module_type.h"
#include "device_info.h"
#include "pm_comm.h"
#include "pm_pon_cfg.h"
#include "pm_target_information.h"
#include "pm_config_target.h"
#include "time_service.h"

/*===========================================================================
                        TYPE DEFINITIONS
===========================================================================*/


/* PMIC A Primary SlaveID */
#define PON_RESET_CFG_WARM_RESET_VAL                      0x01
#define PON_RESET_CFG_IMMEDIATE_X_VDD_SHUTDOWN_VAL        0x02
#define PON_RESET_CFG_NORMAL_SHUTDOWN_VAL                 0x04
#define PON_RESET_CFG_D_VDD_SHUTDOWN_VAL                  0x05
#define PON_RESET_CFG_X_VDD_SHUTDOWN_VAL                  0x06

#define PON_RESET_CFG_HARD_RESET_VAL                      0x07
#define PON_RESET_CFG_D_VDD_HARD_RESET_VAL                0x08
#define PON_RESET_CFG_X_VDD_HARD_RESET_VAL                0x09

#define PON_RESET_CFG_DVDD_HARD_RESET_VAL                 0x08
#define PON_RESET_CFG_XVDD_HARD_RESET_VAL                 0x09
#define PON_RESET_CFG_WARM_RESET_AND_DVDD_SHUTDOWN_VAL    0x0A
#define PON_RESET_CFG_WARM_RESET_AND_XVDD_SHUTDOWN_VAL    0x0B
#define PON_RESET_CFG_WARM_RESET_AND_SHUTDOWN_VAL         0x0C
#define PON_RESET_CFG_WARM_RESET_THEN_HARD_RESET_VAL      0x0D
#define PON_RESET_CFG_WARM_RESET_THEN_DVDD_HARD_RESET_VAL 0x0E
#define PON_RESET_CFG_WARM_RESET_THEN_XVDD_HARD_RESET_VAL 0x0F

#define PON_PBS_PON_SW_CFG_ADDR                           0x860
#define PON_PBS_PON_SW_CFG_VAL                            0x80
#define PON_PBS_DIG_MAJ_VAL                               0x02

/* PON_DVDD_RB_SPARE reg Warm Reset indicating bit mask */
#define PON_DVDD_RB_SPARE_WARM_RESET_MASK                 0x01

#define PON_PBS_SUBTYPE 0x8

typedef struct
{
  uint16 reset_ctl_addr;
  uint16 reset_ctl2_addr;
  uint16 reset_en_mask;
  uint16 reset_type_mask;
}pon_ps_hold_reg_info_type;

typedef struct
{
  uint16 ctl_addr;
  uint16 kpwpwr_mask;
  uint16 cblpwr_mask;
  uint16 pon1_mask;
  uint16 usb_chg_mask;
  uint16 dc_chg_mask;
  uint16 rtc_mask;
  uint16 smpl_mask;
}pon_trigger_en_reg_info_type;


typedef struct 
{
  uint16 s1_timer_addr; 
  uint16 s1_timer_mask; 
  uint16 s2_timer_addr;
  uint16 s2_timer_mask;
  uint16 reset_ctl_addr;
  uint16 reset_ctl2_addr;
  uint16 reset_en_mask;
  uint16 reset_type_mask;
}pon_reset_reg_info_type;


static pon_reset_reg_info_type
pon_gp1_reg =
{
  PMIO_PON_GP1_RESET_S1_TIMER_ADDR,
  PMIO_PON_GP1_RESET_S1_TIMER_S1_TIMER_BMSK,
  PMIO_PON_GP1_RESET_S2_TIMER_ADDR,
  PMIO_PON_GP1_RESET_S2_TIMER_S2_TIMER_BMSK,
  PMIO_PON_GP1_RESET_S2_CTL_ADDR,
  PMIO_PON_GP1_RESET_S2_CTL2_ADDR,
  PMIO_PON_GP1_RESET_S2_CTL2_S2_RESET_EN_BMSK,
  PMIO_PON_GP1_RESET_S2_CTL_RESET_TYPE_BMSK
};

static pon_reset_reg_info_type
pon_gp2_reg =
{
  PMIO_PON_GP2_RESET_S1_TIMER_ADDR,
  PMIO_PON_GP2_RESET_S1_TIMER_S1_TIMER_BMSK,
  PMIO_PON_GP2_RESET_S2_TIMER_ADDR,
  PMIO_PON_GP2_RESET_S2_TIMER_S2_TIMER_BMSK,
  PMIO_PON_GP2_RESET_S2_CTL_ADDR,
  PMIO_PON_GP2_RESET_S2_CTL2_ADDR,
  PMIO_PON_GP2_RESET_S2_CTL2_S2_RESET_EN_BMSK,
  PMIO_PON_GP2_RESET_S2_CTL_RESET_TYPE_BMSK
};


/*===========================================================================
                        GLOBAL
===========================================================================*/

static pon_trigger_en_reg_info_type
pon_trigger_en_reg =
{
  PMIO_PON_PON_TRIGGER_EN_ADDR,
  PMIO_PON_PON_TRIGGER_EN_KPDPWR_N_BMSK,
  PMIO_PON_PON_TRIGGER_EN_CBLPWR_N_BMSK,
  PMIO_PON_PON_TRIGGER_EN_PON1_BMSK,
  PMIO_PON_PON_TRIGGER_EN_USB_CHG_BMSK,
  PMIO_PON_PON_TRIGGER_EN_DC_CHG_BMSK,
  PMIO_PON_PON_TRIGGER_EN_RTC_BMSK,
  PMIO_PON_PON_TRIGGER_EN_SMPL_BMSK,
};

static pon_ps_hold_reg_info_type
pon_ps_hold_reg;

static pon_ps_hold_reg_info_type
pon_ps_hold_reg_v2 =
{
  PMIO_PON_PS_HOLD_RESET_CTL_ADDR,
  PMIO_PON_PS_HOLD_RESET_CTL2_ADDR,
  PMIO_PON_PS_HOLD_RESET_CTL2_S2_RESET_EN_BMSK,
  PMIO_PON_PS_HOLD_RESET_CTL_RESET_TYPE_BMSK
};


static pon_ps_hold_reg_info_type
pon_ps_hold_reg_v3 =
{
  PMIO_PON_PBS_PS_HOLD_SW_CTL_ADDR,
  PMIO_PON_PBS_PS_HOLD_RESET_CTL2_ADDR,
  PMIO_PON_PBS_PS_HOLD_SW_CTL_RESET_TYPE_BMSK,
  PMIO_PON_PBS_PS_HOLD_RESET_CTL2_S2_RESET_EN_BMSK,
};


static boolean
pm_pon_initialized = FALSE;

/*=========================================================================
      Function Prototypes
==========================================================================*/
pm_err_flag_type
pm_pon_get_reset_config_val(pm_pon_reset_cfg_type pon_reset_cfg, uint8* pon_reset_cfg_val);

/*=========================================================================
      Functions
==========================================================================*/

/* =========================================================================
**  Function : pm_pon_init
** =========================================================================*/
/**
  Initial for Power on sequence.
*/
pm_err_flag_type pm_pon_init(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8  periph_type = 0, periph_subtype = 0;
  uint8  dig_major = 0;
  uint8  warm_reset_reason[2] = {0};
  uint8  prim_pm_slave_id_0 = (pm_is_pmiclib_arch_pre7() ?
                              (PM_PRIMARY_SLAVE_ID * 2):
                              PM_PRIMARY_SLAVE_ID);

  if (pm_pon_initialized == TRUE)
  {
    return err_flag;
  }

  /* Read PON Peripheral info and check if it's valid */
  err_flag |= pm_comm_read_byte(prim_pm_slave_id_0, PMIO_PON_PERPH_TYPE_ADDR, 
                               &periph_type, 0);

  /* Read PON Peripheral info and check if it's valid */
  err_flag |= pm_comm_read_byte(prim_pm_slave_id_0, PMIO_PON_PERPH_SUBTYPE_ADDR, 
                               &periph_subtype, 0);

  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  if (periph_type != PM_HW_MODULE_PON)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  if(periph_subtype == PON_PBS_SUBTYPE)
  {
    pon_ps_hold_reg.reset_ctl_addr  = pon_ps_hold_reg_v3.reset_ctl_addr;
    pon_ps_hold_reg.reset_ctl2_addr = pon_ps_hold_reg_v3.reset_ctl2_addr;
    pon_ps_hold_reg.reset_en_mask   = pon_ps_hold_reg_v3.reset_en_mask;
    pon_ps_hold_reg.reset_type_mask = pon_ps_hold_reg_v3.reset_type_mask;
  }
  else
  {
    pon_ps_hold_reg.reset_ctl_addr  = pon_ps_hold_reg_v2.reset_ctl_addr;
    pon_ps_hold_reg.reset_ctl2_addr = pon_ps_hold_reg_v2.reset_ctl2_addr;
    pon_ps_hold_reg.reset_en_mask   = pon_ps_hold_reg_v2.reset_en_mask;
    pon_ps_hold_reg.reset_type_mask = pon_ps_hold_reg_v2.reset_type_mask;
  }


  /* Read Dig Major Version info */
  err_flag = pm_comm_read_byte(prim_pm_slave_id_0, PMIO_PON_REVISION2_ADDR, 
                               &dig_major, 0);

  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  if (!dig_major)
  {
    /* Only needed on very first peripheral versions */
    pon_ps_hold_reg.reset_ctl2_addr = pon_ps_hold_reg.reset_ctl_addr;
  }

  if(periph_subtype != PON_PBS_SUBTYPE)
  {
    /* Read Warm Reset reason */
    err_flag = pm_comm_read_byte_array(prim_pm_slave_id_0,
                                      PMIO_PON_WARM_RESET_REASON1_ADDR, 2,
                                      warm_reset_reason, 0);
  
    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
      return err_flag;
    }
  
    /* Update the DVDD_RB_SPARE register bit <0> to 1 if Warm Reset occured */
    if ((warm_reset_reason[0] != 0) || (warm_reset_reason[1] != 0))
    {
      err_flag = pm_comm_write_byte_mask(prim_pm_slave_id_0,
                                    PMIO_PON_DVDD_RB_SPARE_ADDR,
                                    PON_DVDD_RB_SPARE_WARM_RESET_MASK, 0x01, 0);
  
      if (err_flag != PM_ERR_FLAG_SUCCESS)
      {
        return err_flag;
      }
    }
  }
  pm_pon_initialized = TRUE;
  return err_flag;
}

/* =========================================================================
**  Function : pm_pon_ps_hold_cfg
** =========================================================================*/
/**
  Configure for PSHOLD.
*/
pm_err_flag_type pm_pon_ps_hold_cfg(uint32 pmic_device_index, pm_pon_reset_cfg_type ps_hold_cfg)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 ps_hold_cfg_val = PON_RESET_CFG_WARM_RESET_VAL;
  uint32 slave_id = 0;
  uint8  dig_major = 0;

  /* Init pmic comm interface. */
  err_flag = pm_comm_channel_init_internal();
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  /* Get PMIC device Primary slave id value since PON module
     is on the Primary slave id index 0 */
  err_flag = pm_get_slave_id(pmic_device_index, 0, &slave_id);

  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }
  if (ps_hold_cfg >= PM_PON_RESET_CFG_INVALID)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
      return err_flag;
    }
  }

  switch (ps_hold_cfg)
  {
     case PM_PON_RESET_CFG_WARM_RESET:
       ps_hold_cfg_val = PON_RESET_CFG_WARM_RESET_VAL;
       break;

     case PM_PON_RESET_CFG_NORMAL_SHUTDOWN:
       ps_hold_cfg_val = PON_RESET_CFG_NORMAL_SHUTDOWN_VAL;
       break;

     case PM_PON_RESET_CFG_D_VDD_BATT_REMOVE_SHUTDOWN:
       ps_hold_cfg_val = PON_RESET_CFG_D_VDD_SHUTDOWN_VAL;
       break;

     case PM_PON_RESET_CFG_D_VDD_BATT_REMOVE_HARD_RESET:
       ps_hold_cfg_val = PON_RESET_CFG_D_VDD_HARD_RESET_VAL;
       break;

     case PM_PON_RESET_CFG_X_VDD_COIN_CELL_REMOVE_SHUTDOWN:
       ps_hold_cfg_val = PON_RESET_CFG_X_VDD_SHUTDOWN_VAL;
       break;

     case PM_PON_RESET_CFG_HARD_RESET:
       ps_hold_cfg_val = PON_RESET_CFG_HARD_RESET_VAL;
       break;

    case PM_PON_RESET_CFG_IMMEDIATE_X_VDD_COIN_CELL_REMOVE_SHUTDOWN:
      ps_hold_cfg_val = PON_RESET_CFG_IMMEDIATE_X_VDD_SHUTDOWN_VAL;
      break;

    case PM_PON_RESET_CFG_D_VDD_COIN_CELL_REMOVE_HARD_RESET:
      ps_hold_cfg_val = PON_RESET_CFG_D_VDD_HARD_RESET_VAL;
      break;

    case PM_PON_RESET_CFG_X_VDD_COIN_CELL_REMOVE_HARD_RESET:
      ps_hold_cfg_val = PON_RESET_CFG_X_VDD_HARD_RESET_VAL;
      break;

    case PM_PON_RESET_CFG_WARM_RESET_THEN_X_VDD_COIN_CELL_REMOVE_HARD_RESET:
       ps_hold_cfg_val = PON_RESET_CFG_WARM_RESET_THEN_XVDD_HARD_RESET_VAL;
       break;

     default:
       return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  /* Disable reset */
  err_flag = pm_comm_write_byte(slave_id, pon_ps_hold_reg.reset_ctl2_addr, 0x0, 0);

  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }
  /* Requires 10 sleep clock cycles of delay */
  busywait(300); /* Requires 10 sleep clock cycles of delay */

  err_flag = pm_comm_read_byte(slave_id, PMIO_PON_REVISION2_ADDR, 
                               &dig_major, 0);

  if(ps_hold_cfg_val == PON_RESET_CFG_WARM_RESET_VAL && dig_major >= PON_PBS_DIG_MAJ_VAL)
  {
    err_flag |= pm_comm_write_byte(slave_id, PON_PBS_PON_SW_CFG_ADDR, PON_PBS_PON_SW_CFG_VAL, 0);
  }

  err_flag |= pm_comm_write_byte(slave_id, pon_ps_hold_reg.reset_ctl_addr, ps_hold_cfg_val, 0);

  /* Enable reset */
  err_flag |= pm_comm_write_byte(slave_id, pon_ps_hold_reg.reset_ctl2_addr, pon_ps_hold_reg.reset_en_mask, 0);

  return err_flag;
}



pm_err_flag_type pm_pon_gp_reset_cfg( uint32  pmic_device_index, pm_pon_reset_source_type reset_source, pm_pon_reset_cfg_type reset_cfg_type) 
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
    uint8 reset_en;
    uint8 reset_val = 0;
    uint32 slave_id = 0;
    pon_reset_reg_info_type *reset_reg = NULL;  

    /* Get PMIC device Primary slave id value since PON module
       is on the Primary slave id index 0 */
    err_flag = pm_get_slave_id(pmic_device_index, 0, &slave_id);
    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
      return PM_ERR_FLAG_INVALID_PARAMETER;
    }

    if (reset_cfg_type >= PM_PON_RESET_CFG_INVALID)
    {
       return PM_ERR_FLAG_INVALID_PARAMETER;
    }



    switch (reset_source)
    {
       case PM_PON_RESET_SOURCE_GP1:
         reset_reg = &pon_gp1_reg; 
         break;
    
       case PM_PON_RESET_SOURCE_GP2:
         reset_reg = &pon_gp2_reg;
         break;
    
       default:
         return PM_ERR_FLAG_INVALID_PARAMETER;
    }

    err_flag |= pm_pon_get_reset_config_val(reset_cfg_type, &reset_val);
    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
       return err_flag;
    }

    //Read reset status
    err_flag |= pm_comm_read_byte(slave_id, reset_reg->reset_ctl2_addr, &reset_en, 0);
    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
       return err_flag;
    }
    reset_en = reset_en & reset_reg->reset_en_mask;

    if (reset_en)
    {
      err_flag |= pm_comm_write_byte_mask(slave_id, reset_reg->reset_ctl2_addr, reset_reg->reset_en_mask, 0x0, 0);//Disable Reset

      busywait(300); /* Requires 8 sleep clock cycles of delay */ 
    }

    
    /* Configure reset value */
    err_flag |= pm_comm_write_byte_mask(slave_id, reset_reg->reset_ctl_addr, reset_reg->reset_type_mask, reset_val, 0);
 
    
    if (reset_en)
    {  /* Enable reset if it was already in enable state */
       err_flag |= pm_comm_write_byte_mask(slave_id, reset_reg->reset_ctl2_addr, reset_reg->reset_en_mask, 0xFF, 0); 
       if (err_flag != PM_ERR_FLAG_SUCCESS)
       {
         return err_flag;
       }
    }
  
    return err_flag;
}


pm_err_flag_type pm_pon_get_reset_config_val(pm_pon_reset_cfg_type pon_reset_cfg, uint8* pon_reset_cfg_val)
{
   pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

   //Map App level allowed config enums to PON config enums
   switch (pon_reset_cfg)
   {
     case PM_PON_RESET_CFG_WARM_RESET:
       *pon_reset_cfg_val = PON_RESET_CFG_WARM_RESET_VAL;
       break;

     case PM_PON_RESET_CFG_NORMAL_SHUTDOWN:
       *pon_reset_cfg_val = PON_RESET_CFG_NORMAL_SHUTDOWN_VAL;
       break;

     case PM_PON_RESET_CFG_D_VDD_BATT_REMOVE_SHUTDOWN:
       *pon_reset_cfg_val = PON_RESET_CFG_D_VDD_SHUTDOWN_VAL;
       break;

     case PM_PON_RESET_CFG_D_VDD_BATT_REMOVE_HARD_RESET:
       *pon_reset_cfg_val = PON_RESET_CFG_D_VDD_HARD_RESET_VAL;
       break;

     case PM_PON_RESET_CFG_X_VDD_COIN_CELL_REMOVE_SHUTDOWN:
       *pon_reset_cfg_val = PON_RESET_CFG_X_VDD_SHUTDOWN_VAL;
       break;

     case PM_PON_RESET_CFG_HARD_RESET:
       *pon_reset_cfg_val = PON_RESET_CFG_HARD_RESET_VAL;
       break;

    case PM_PON_RESET_CFG_IMMEDIATE_X_VDD_COIN_CELL_REMOVE_SHUTDOWN:
      *pon_reset_cfg_val = PON_RESET_CFG_IMMEDIATE_X_VDD_SHUTDOWN_VAL;
      break;

    case PM_PON_RESET_CFG_X_VDD_COIN_CELL_REMOVE_HARD_RESET:
      *pon_reset_cfg_val = PON_RESET_CFG_X_VDD_HARD_RESET_VAL;
      break;

    case PM_PON_RESET_CFG_WARM_RESET_THEN_X_VDD_COIN_CELL_REMOVE_HARD_RESET:
       *pon_reset_cfg_val = PON_RESET_CFG_WARM_RESET_THEN_XVDD_HARD_RESET_VAL;
       break;

     default:
       err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
       break;
  }

  return err_flag;
}

