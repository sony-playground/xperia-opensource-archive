/*! \file pm_sbl_pon_target.c
*  \n
*  \brief This file contains PMIC device initialization function where initial PMIC
*  \n SBL settings are configured through the PDM auto-generated code.
*  \n
*  \n &copy; Copyright 2015-2012, 2022 Qualcomm Technologies Inc, All Rights Reserved
*/
/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/target/kailua/system/src/pm_pon_target.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/16/18   aab     Updated as per PON App reset recomendation doc  
05/04/16   aab     Removed Resin and KeyCombo tables since its content is the same as Keypad power table. 
                    Also, removed PMK from all tables as it is not supported in this target
                     Change all PM8005 configuation to NO Config needed
04/29/16   aab     Updated to support GP1 configuration for kpad/resin/key combo PON reset configuration
03/28/16   aab     Added pm_tgt_get_gp1_cfg() and updated config tables for 8998 target
10/08/15   aab     Created
========================================================================== */
/*===========================================================================

                     INCLUDE FILES

===========================================================================*/
#include "pm_pon_target.h"
#include "pm_app_pon.h"
#include "pm_sdam.h"
#include "pm_version.h"
#include "pm_utils.h"
#include "pm_comm.h"
#include <string.h>
#include <stdio.h>

/*===========================================================================

                     PreProcessors

===========================================================================*/

#define PON_DEBUG_HR_SDAM_MEM_ADDR  18
#define BYTE_CNT                    1
#define PON_DEBUG_HR_VAL            0xFF

// PBS_FAULT_PC_STATUS_LSB: SDAM01.MEM_030 ---- 0x705E
#define ADDR_PBS_FAULT_PC_LSB (0x705E)

// PBS_FAULT_RA_PC_STATUS_LSB: SDAM01.MEM_032 ---- 0x7060
#define ADDR_PBS_FAULT_RA_PC_LSB (0x7060)

// PBS_NACK_REASON: SDAM01.MEM_034  ---- 0x7062
#define ADDR_PBS_NACK_REASON (0x7062)


/*===========================================================================

                     Global Variables

===========================================================================*/
//PSHOlD config:  PON PS Hold config
static const pm_pon_reset_cfg_type
pm_app_pon_pshold_reset_cfg_arr[PM_APP_PON_CFG_MAX][PM_MAX_NUM_PMICS] =
{     //PMK8550             PM8550              PM8550VS            PM8550VS/E         PM8550VS           PM8550VE              PM8550VS         PM8550B                empty              empty              PM735D              PM735D                PM8010             PM8010     
   {PON_WARM_RST,      PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED }, //Warm Reset
   {PON_HARD_RST,      PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED }, //Hard Reset
   {PON_SHDN,          PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED }, //Shutdown
   {PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED }, //Dvdd hard reset
   {PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED }  //DVDD Shutdown
};


//PSHOlD config:  PON GP1 config
static const pm_pon_reset_cfg_type
pm_app_pon_pshold_gp1_reset_cfg_arr[PM_APP_PON_CFG_MAX][PM_MAX_NUM_PMICS] =
{     //PMK8550             PM8550              PM8550VS            PM8550VS/E         PM8550VS           PM8550VE              PM8550VS         PM8550B                empty              empty              PM735D              PM735D                PM8010             PM8010     
   {PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED }, //Warm Reset
   {PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED }, //Hard Reset
   {PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED }, //Shutdown
   {PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED }, //Dvdd hard reset
   {PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED }  //DVDD Shutdown
};


//Kpdpwr / Resin /Key Combo(Resin_and_Kpdpwr):  PON Keypad Power S2 Config
static const pm_pon_reset_cfg_type
pm_app_pon_kpdpwr_reset_cfg_arr[PM_APP_PON_CFG_MAX][PM_MAX_NUM_PMICS] =
{      //PMK8550             PM8550              PM8550VS            PM8550VS/E         PM8550VS           PM8550VE              PM8550VS         PM8550B                empty              empty              PM735D              PM735D                PM8010             PM8010     
   {PON_WARM_RST,      PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED }, //Warm Reset
   {PON_HARD_RST,      PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED }, //Hard Reset
   {PON_SHDN,          PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED }, //Shutdown
   {PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED }, //Dvdd hard reset
   {PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED }  //DVDD Shutdown
};

pm_pon_trigger_config_type 
pon_defined_triggers[PM_PON_TRIGGER_INVALID] = 
{
 [PM_PON_TRIGGER_KPDPWR]  = { .pid = 0x08, .sid = 0x00, .irq_type = 0x00, .polarity_high = 0x80, .polarity_low  = 0x00, .int_en  = 0x80, .trig_index = 0x00, .trig_mask = 0x80}, //keypad_pwr
 [PM_PON_TRIGGER_SMPL]    = { .pid = 0x64, .sid = 0x00, .irq_type = 0x00, .polarity_high = 0x01, .polarity_low  = 0x00, .int_en  = 0x01, .trig_index = 0x01, .trig_mask = 0x01}, //SMPL
 [PM_PON_TRIGGER_PON1]    = { .pid = 0x8C, .sid = 0x01, .irq_type = 0x00, .polarity_high = 0x01, .polarity_low  = 0x00, .int_en  = 0x01, .trig_index = 0x02, .trig_mask = 0x01}, //PON1; also same as CABLEPWR
 [PM_PON_TRIGGER_USB_CHG] = { .pid = 0x1C, .sid = 0x03, .irq_type = 0x04, .polarity_high = 0x04, .polarity_low  = 0x00, .int_en  = 0x04, .trig_index = 0x03, .trig_mask = 0x04}, //sys okay
 [PM_PON_TRIGGER_RTC]     = { .pid = 0x62, .sid = 0x00, .irq_type = 0x00, .polarity_high = 0x02, .polarity_low  = 0x00, .int_en  = 0x02, .trig_index = 0x04, .trig_mask = 0x02}, //rtc
 [PM_PON_TRIGGER_CBLPWR]  = { .pid = 0x8C, .sid = 0x01, .irq_type = 0x00, .polarity_high = 0x01, .polarity_low  = 0x00, .int_en  = 0x01, .trig_index = 0x02, .trig_mask = 0x01}, //same as PON1
 [PM_PON_TRIGGER_DC_CHG]  = { .pid = 0x00, .sid = 0x00, .irq_type = 0x00, .polarity_high = 0x00, .polarity_low  = 0x00, .int_en  = 0x00, .trig_index = 0x00, .trig_mask = 0x00}, //undefined currently
};

/*===========================================================================

                        FUNCTION Prototypes

===========================================================================*/
pm_err_flag_type 
pm_tgt_get_pshold_gp1_reset_cfg( uint32                      pmic_index,
                                 pm_app_pon_reset_cfg_type   app_pshold_gp1_cfg,
                                 pm_pon_reset_cfg_type*      pshold_gp1_cfg);


/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/
pm_err_flag_type 
pm_tgt_get_pshold_reset_cfg( uint32                      pmic_index,
                             pm_app_pon_reset_cfg_type   app_pshold_cfg,
                             pm_pon_reset_cfg_type*      pshold_cfg)
{
  if( (pmic_index         >=  PM_MAX_NUM_PMICS)   ||  
      (app_pshold_cfg     >=  PM_APP_PON_CFG_MAX) ||
      (pshold_cfg         ==  NULL) )
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  *pshold_cfg = pm_app_pon_pshold_reset_cfg_arr[app_pshold_cfg][pmic_index];

  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type 
pm_tgt_get_pshold_gp1_reset_cfg( uint32                      pmic_index,
                                 pm_app_pon_reset_cfg_type   app_pshold_gp1_cfg,
                                 pm_pon_reset_cfg_type*      pshold_gp1_cfg)
{
  if( (pmic_index           >=  PM_MAX_NUM_PMICS)   ||  
      (app_pshold_gp1_cfg   >=  PM_APP_PON_CFG_MAX) ||
      (pshold_gp1_cfg       ==  NULL) )
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  *pshold_gp1_cfg = pm_app_pon_pshold_gp1_reset_cfg_arr[app_pshold_gp1_cfg][pmic_index];

  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type
pm_tgt_get_kpdpwr_reset_cfg( uint32                        pmic_index,
                             pm_app_pon_reset_cfg_type     app_kpdpwr_reset_cfg,
                             pm_pon_reset_cfg_type*        kpdpwr_reset_cfg)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

    if( (pmic_index             >= PM_MAX_NUM_PMICS)   || 
        (app_kpdpwr_reset_cfg   >= PM_APP_PON_CFG_MAX) ||
        (kpdpwr_reset_cfg       == NULL) )
    {
       return PM_ERR_FLAG_INVALID_PARAMETER;
    }

    *kpdpwr_reset_cfg = pm_app_pon_kpdpwr_reset_cfg_arr[app_kpdpwr_reset_cfg][pmic_index];

    return err_flag;
}

pm_err_flag_type
pm_pon_tgt_specific_pshold_cfg(uint32 pmic_index, pm_app_pon_reset_cfg_type app_pshold_cfg)
{
   pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
   pm_pon_reset_cfg_type       pshold_gp1_cfg  = PM_PON_RESET_CFG_INVALID;

   if( (pmic_index >=  PM_MAX_NUM_PMICS ) || (app_pshold_cfg >=  PM_APP_PON_CFG_MAX))
   {
     return PM_ERR_FLAG_INVALID_PARAMETER;
   }

   //GP1 Reset Config
   err_flag |= pm_tgt_get_pshold_gp1_reset_cfg(pmic_index, app_pshold_cfg,  &pshold_gp1_cfg); 
   if (pshold_gp1_cfg != PON_NO_CFG_NEEDED) 
   { 
       err_flag |= pm_pon_gp_reset_cfg( pmic_index, PM_PON_RESET_SOURCE_GP1, pshold_gp1_cfg);
   }
   
   return err_flag;
}

pm_err_flag_type 
pm_pon_tgt_specific_kpd_reset_cfg(uint32 pmic_index, pm_app_pon_reset_cfg_type app_pon_reset_cfg) 
{ 
   pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS; 
   //Add target specific config
   return err_flag; 
} 

pm_err_flag_type
pm_pon_target_debug_hard_reset( void )
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  uint8 data = PON_DEBUG_HR_VAL;

  err_flag = pm_sdam_mem_write ( PMIC_A, PM_SDAM_1, PON_DEBUG_HR_SDAM_MEM_ADDR, BYTE_CNT, &data);

  return err_flag;

}

pm_err_flag_type
pm_pon_target_get_pon_trigger_config( pm_pon_trigger_type trigger, pm_pon_trigger_config_type *trigger_config)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  if((trigger >= PM_PON_TRIGGER_INVALID) || (NULL == trigger_config))
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    *trigger_config = pon_defined_triggers[trigger];
  }

  return err_flag;
}

pm_err_flag_type pm_pon_get_fault_pmic_string(pm_pon_event_type event, char* fault_pmic, int size)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  if(NULL == fault_pmic)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  switch(event)
  {
  case PM_PON_EVENT_FAULT_REASON_PART1:
  case PM_PON_EVENT_FAULT_REASON_PART2:
  case PM_PON_EVENT_FAULT_PMIC_A:
    strlcpy(fault_pmic, "Azura", size);
    break;
  case PM_PON_EVENT_FAULT_PMIC_B:
    strlcpy(fault_pmic, "Humu", size);
    break;
  case PM_PON_EVENT_FAULT_PMIC_C:
    strlcpy(fault_pmic, "V6_C", size);
    break;
  case PM_PON_EVENT_FAULT_PMIC_D:
    strlcpy(fault_pmic, "V6_D", size);
    break;
  case PM_PON_EVENT_FAULT_PMIC_E:
    strlcpy(fault_pmic, "V6_E", size);
    break;
  case PM_PON_EVENT_FAULT_PMIC_F:
    strlcpy(fault_pmic, "V8_F", size);
    break;
  case PM_PON_EVENT_FAULT_PMIC_G:
    strlcpy(fault_pmic, "V6_G", size);
    break;
  case PM_PON_EVENT_FAULT_PMIC_H:
    strlcpy(fault_pmic, "Kohala", size);
    break;
  default: // do nothing
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  return err_flag;
}


#define SUPPORT_PMIC_PBS_MISC1_MASK (0x1C0)
#define INTRRUPT_VREG_OCP (0)
pm_err_flag_type pm_get_target_specific_pon_trig_string(uint16 pon_dataset, char** pon_trig_str)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;

  if(NULL == pon_trig_str)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else if(SUPPORT_PMIC_PBS_MISC1_MASK == (pon_dataset & SUPPORT_PMIC_PBS_MISC1_MASK))
  {
    // on Kailua, PSB MISC1 BIT0 trigger on support PMIC is OCP of regulator
    uint8 slave_id = pon_dataset >> 12; // SID: [15:12]
    uint8 int_index = pon_dataset & 0xF;
    if((INTRRUPT_VREG_OCP == int_index) && (PMIC_A != slave_id))
    {
      pm_malloc(20, (void**)pon_trig_str);

      snprintf(*pon_trig_str, 20, "PMIC_%c OCP", 'A' + slave_id);
      err_flag = PM_ERR_FLAG_SUCCESS;
    }
  }

  return err_flag;
}


void pm_pon_get_pbs_fault_pc(char* str, int size)
{
  uint16 data = 0;
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  if(NULL != str)
  {
    err_flag = pm_comm_read_byte_array(PMIC_A, ADDR_PBS_FAULT_PC_LSB, 2, (uint8*)&data);
    if(PM_ERR_FLAG_SUCCESS == err_flag)
    {
      snprintf(str, size, "0x%04X", data);
    }
  }
}


void pm_pon_get_pbs_fault_return_address_pc(char* str, int size)
{
  uint16 data = 0;
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  if(NULL != str)
  {
    err_flag = pm_comm_read_byte_array(PMIC_A, ADDR_PBS_FAULT_RA_PC_LSB, 2, (uint8*)&data);
    if(PM_ERR_FLAG_SUCCESS == err_flag)
    {
      snprintf(str, size, "0x%04X", data);
    }
  }
}


#define NACK_REASON_CNT (7)
void pm_pon_get_pbs_nack_reason(char* str, int size)
{
  uint8 data = 0;
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  char reasons[NACK_REASON_CNT][32] = {
    "Wait TO",  // 0
    "RAM1 Load Fail",  // 1
    "WR cnt exceed",  // 2
    "RST Arg Missed", // 3
    "S4 Reset", // 4
    "INT Mod Lockup", // 5
    "SW Nack",  // 6
  };

  if(NULL != str)
  {
    err_flag = pm_comm_read_byte(PMIC_A, ADDR_PBS_NACK_REASON, &data);
    if((PM_ERR_FLAG_SUCCESS == err_flag) && (data < NACK_REASON_CNT))
    {
      strlcpy(str, reasons[data], size);
    }
  }
}

