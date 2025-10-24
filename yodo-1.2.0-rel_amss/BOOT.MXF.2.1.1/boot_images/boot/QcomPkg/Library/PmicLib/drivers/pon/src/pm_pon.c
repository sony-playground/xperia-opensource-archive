/*! \file pm_pon.c
*  \n
*  \brief PMIC PowerON Peripheral driver
*  \n
*  \n This header file contains class implementation of the PON
*  \n peripheral APIs
*  \n
*  \n &copy; Copyright 2012-2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/
/*===================================================================
			        EDIT HISTORY FOR MODULE
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/pon/src/pm_pon.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
10/18/17   pxm     Correct PON reason reading
08/22/17   czq     Support for PON_RESET_CFG_WARM_RESET_THEN_DVDD_SHUTDOWN_VAL.
05/09/17   czq     correct some faults in API pm_pon_gen1_config_uvlo(). 
01/06/17   al      Updated pon_init for pon_gen2 warm reset
11/11/16   aab     Updated pon_gen2_uvlo_threshold_val[]
05/06/16   aab     Updated pm_pon_overtemp_reset_cf() and pm_pon_get_reset_config_val()
05/02/16   aab     Support for RUMI with no pmic card.
03/28/16   aab     Added pm_pon_gp_reset_cfg() and pm_pon_get_reset_config_val()
03/22/16   aab     Added pm_pon_get_fault_reasons() updated pm_pon_get_all_pon_reasons() 
03/22/16   aab     Updated pm_pon_config_uvlo() Added pm_pon_gen1_config_uvlo()
12/07/15   aab     Updated to support PON GEN2 peripheral
09/16/15   al      Updating xvdd status read 
08/08/15   aab     Updated pm_pon_init() to support PON APIs with out doing pm init
11/12/15   kt      Updated pm_pon_ps_hold_cfg API.
11/19/14   al      Removing loader specific 
09/15/14   aab     Added PON Reasons status log
07/16/14   akm     Comm change Updates
08/19/14   al      Adding API to configure PON trigger
12/04/13   aab     Added PM_PON_RESET_CFG_D_VDD_BATT_REMOVE_HARD_RESET
11/01/13   sv      Applying CR538994 Changes with power up failure fix. (CR-570053)
10/24/13   sv      Reverting CR538994 Changes (CR-566323)
06/24/13   ps      Added PON Stage3 reset config API CR#495834 
02/27/13   kt      Added PON Reasons and IRQ related APIs  
01/24/13   umr     Add new version support.
11/20/12   umr     Created
========================================================================== */

/*===========================================================================

INCLUDE FILES FOR MODULE

===========================================================================*/

#include "pm_version.h"
#include "pm_pon.h"
#include "pm_app_pon.h"
#include "pmio_pon.h"
#include "hw_module_type.h"
#include "device_info.h"
#include "pm_comm.h"
#include "pm_utils.h"
#include "pm_config_target.h"
#include "pm_device.h"
#include "pm_sbl_boot.h"
#include "pm_pon_target.h"
#include "CoreVerify.h"


/*===========================================================================
                 #defines 
===========================================================================*/

#define PON_ON_REASON_WARM_SEQ_BMSK  0x40

#define PON_RESET_CFG_INVALID_VAL    0xFF

#define INT_SET_TYPE_OFFSET          0x11  

#define SET_TYPE_OFFSET      0x11
#define POLARITY_HIGH_OFFSET 0x12
#define POLARITY_LOW_OFFSET  0x13
	  

/* PON_DVDD_RB_SPARE reg Warm Reset indicating bit mask */
#define PON_DVDD_RB_SPARE_WARM_RESET_MASK                 0x01
#define PM_PON_MAX_SPARE_BIT_MASK                         0xFF
#define PMIO_PON_TRIGGER_EDGE_CONFIG                      0x881

/* length of array */
#define ARRAY_LENGTH(x)  (sizeof(x) / sizeof(x[0]))

#define WAIT_FOR_SLEEP_CLK_CYCLE(num_of_sleep_cycle)  pm_busy_wait((3052*num_of_sleep_cycle)/100) //sleep cycle is 32.7645KHz

#define SUPPORTED_DIG_VERSION (0x02<<8 | 0x00) // DIG_MAJOR 1 , DIG_MINOR 2
#define SUPPORTED_ANA_VERSION (0x01<<8 | 0x00) // ANA_MAJOR 0 , ANA_MINOR 0
#define SUPPORTED_PBS_GEN     (0x08)
#define ALLOW_WARM_RESET      (1<<7)

/*===========================================================================
                 local global variable 
===========================================================================*/

static boolean pm_pon_initialized = FALSE;
static boolean pon_log_data_captured = FALSE;

typedef struct 
{
  uint16              s1_timer_addr;
  uint16              s1_timer_mask;
  uint16              s2_timer_addr;
  uint16              s2_timer_mask;
  uint16              reset_ctl_addr;
  uint16              reset_ctl2_addr;
  uint16              reset_en_mask;
  uint16              reset_type_mask;
  pm_pon_irq_type     irq         :8;
  pm_irq_trigger_type trigger_type:8;
}pon_reset_reg_info_type;

typedef struct
{
  uint16                reset_ctl_addr;
  uint16                reset_ctl2_addr;
  uint16                reset_en_mask;
  uint16                reset_type_mask;
  pm_pon_irq_type       irq : 8;
  pm_irq_trigger_type   trigger_type : 8;
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
  uint16 pon_reason1_addr;
  uint16 warm_reset_reason1_addr;
  uint16 on_reason_addr;
  uint16 poff_reason1_addr;
  uint16 off_reason_addr;
  uint16 fault_reason1_addr;
  uint16 fault_reason2_addr;
  uint16 s3_reset_reason_addr;
}pm_reason_addr_type;


pm_reason_addr_type pon_reasons_addr =
{
  .pon_reason1_addr        = BOOT1_PON_REASON1_ADDR,
  .warm_reset_reason1_addr = BOOT1_WARM_RESET_REASON1_ADDR,
  .on_reason_addr          = BOOT1_ON_REASON_ADDR,
  .poff_reason1_addr       = BOOT1_POFF_REASON1_ADDR,
  .off_reason_addr         = BOOT1_OFF_REASON_ADDR,
  .fault_reason1_addr      = PMIO_PON_PBS_FAULT_REASON1_ADDR,
  .fault_reason2_addr      = PMIO_PON_PBS_FAULT_REASON2_ADDR,
  .s3_reset_reason_addr    = PMIO_PON_PBS_S3_RESET_REASON_ADDR,
};

typedef struct
{
  uint8 mask;
  uint8 shift;
}pm_pon_reg_mask_shift_info_type;


static pon_reset_reg_info_type
pon_kpdpwr_reg =
{
  .s1_timer_addr     = PMIO_PON_PBS_KPDPWR_N_RESET_S1_TIMER_ADDR,
  .s1_timer_mask     = PMIO_PON_PBS_KPDPWR_N_RESET_S1_TIMER_S1_TIMER_BMSK,
  .s2_timer_addr     = PMIO_PON_PBS_KPDPWR_N_RESET_S2_TIMER_ADDR,
  .s2_timer_mask     = PMIO_PON_PBS_KPDPWR_N_RESET_S2_TIMER_S2_TIMER_BMSK,
  .reset_ctl_addr    = PMIO_PON_PBS_KPDPWR_N_RESET_S2_SW_CTL_ADDR,
  .reset_ctl2_addr   = PMIO_PON_PBS_KPDPWR_N_RESET_S2_CTL2_ADDR,
  .reset_en_mask     = PMIO_PON_PBS_KPDPWR_N_RESET_S2_CTL2_S2_RESET_EN_BMSK,
  .reset_type_mask   = PMIO_PON_PBS_KPDPWR_N_RESET_S2_SW_CTL_RESET_TYPE_BMSK,
  .irq               = PM_PON_IRQ_KPDPWR_N_S2,
  .trigger_type      = PM_IRQ_TRIGGER_ACTIVE_HIGH,
};


static pon_reset_reg_info_type
pon_resin_reg =
{
  .s1_timer_addr     = PMIO_PON_PBS_RESIN_N_RESET_S1_TIMER_ADDR,
  .s1_timer_mask     = PMIO_PON_PBS_RESIN_N_RESET_S1_TIMER_S1_TIMER_BMSK,
  .s2_timer_addr     = PMIO_PON_PBS_RESIN_N_RESET_S2_TIMER_ADDR,
  .s2_timer_mask     = PMIO_PON_PBS_RESIN_N_RESET_S2_TIMER_S2_TIMER_BMSK,                       
  .reset_ctl_addr    = PMIO_PON_PBS_RESIN_N_RESET_SW_CTL_ADDR,
  .reset_ctl2_addr   = PMIO_PON_PBS_RESIN_N_RESET_S2_CTL2_ADDR,
  .reset_en_mask     = PMIO_PON_PBS_RESIN_N_RESET_S2_CTL2_S2_RESET_EN_BMSK,
  .reset_type_mask   = PMIO_PON_PBS_RESIN_N_RESET_SW_CTL_RESET_TYPE_BMSK,
  .irq               = PM_PON_IRQ_RESIN_N_S2,
  .trigger_type      = PM_IRQ_TRIGGER_ACTIVE_HIGH,
};

static pon_reset_reg_info_type
pon_resin_and_kpdpwr_reg =
{
  .s1_timer_addr   = PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S1_TIMER_ADDR,
  .s1_timer_mask   = PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S1_TIMER_S1_TIMER_BMSK,
  .s2_timer_addr   = PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_TIMER_ADDR,
  .s2_timer_mask   = PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_TIMER_S2_TIMER_BMSK,
  .reset_ctl_addr  = PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_SW_CTL_ADDR,
  .reset_ctl2_addr = PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_CTL2_ADDR,
  .reset_en_mask   = PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_CTL2_S2_RESET_EN_BMSK,
  .reset_type_mask = PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_SW_CTL_RESET_TYPE_BMSK,
  .irq             = PM_PON_IRQ_RESIN_AND_KPDPWR_S2,
  .trigger_type    = PM_IRQ_TRIGGER_ACTIVE_HIGH,
};

/*
static pon_reset_reg_info_type
pon_gp1_reg =
{
  .s1_timer_addr   = PON_PBS_GP1_RESET_S1_TIMER_ADDR,
  .s1_timer_mask   = PON_PBS_GP1_RESET_S1_TIMER_S1_TIMER_BMSK,
  .s2_timer_addr   = PON_PBS_GP1_RESET_S2_TIMER_ADDR,
  .s2_timer_mask   = PON_PBS_GP1_RESET_S2_TIMER_S2_TIMER_BMSK,
  .reset_ctl_addr  = PON_PBS_GP1_RESET_SW_CTL_ADDR,
  .reset_ctl2_addr = PON_PBS_GP1_RESET_S2_CTL2_ADDR,
  .reset_en_mask   = PON_PBS_GP1_RESET_S2_CTL2_S2_RESET_EN_BMSK,
  .reset_type_mask = PON_PBS_GP1_RESET_SW_CTL_RESET_TYPE_BMSK
};
*/

static pon_ps_hold_reg_info_type
  pon_ps_hold_reg =
{
  .reset_ctl_addr  = PMIO_PON_PBS_PS_HOLD_SW_CTL_ADDR,
  .reset_ctl2_addr = PMIO_PON_PBS_PS_HOLD_RESET_CTL2_ADDR,
  .reset_en_mask   = PMIO_PON_PBS_PS_HOLD_RESET_CTL2_S2_RESET_EN_BMSK,
  .reset_type_mask = PMIO_PON_PBS_PS_HOLD_SW_CTL_RESET_TYPE_BMSK,
  .irq             = PM_PON_IRQ_PS_HOLD,
  .trigger_type    = PM_IRQ_TRIGGER_FALLING_EDGE,
};


static pm_register_data_type pon_reset_cfg_val[] =
{
  [PM_PON_RESET_CFG_WARM_RESET]                                         = 0x01,
  [PM_PON_RESET_CFG_HARD_RESET]                                         = 0x07,
  [PM_PON_RESET_CFG_NORMAL_SHUTDOWN]                                    = 0x04,
  [PM_PON_RESET_CFG_D_VDD_BATT_REMOVE_HARD_RESET]                       = PON_RESET_CFG_INVALID_VAL,
  [PM_PON_RESET_CFG_D_VDD_BATT_REMOVE_SHUTDOWN]                         = PON_RESET_CFG_INVALID_VAL,
  [PM_PON_RESET_CFG_X_VDD_COIN_CELL_REMOVE_SHUTDOWN]                    = PON_RESET_CFG_INVALID_VAL,
  [PM_PON_RESET_CFG_X_VDD_COIN_CELL_REMOVE_HARD_RESET]                  = PON_RESET_CFG_INVALID_VAL,
  [PM_PON_RESET_CFG_IMMEDIATE_X_VDD_COIN_CELL_REMOVE_SHUTDOWN]          = PON_RESET_CFG_INVALID_VAL,
  [PM_PON_RESET_CFG_WARM_RESET_THEN_D_VDD_BATT_REMOVE_SHUTDOWN]         = PON_RESET_CFG_INVALID_VAL,
  [PM_PON_RESET_CFG_WARM_RESET_THEN_X_VDD_COIN_CELL_REMOVE_SHUTDOWN]    = PON_RESET_CFG_INVALID_VAL,
  [PM_PON_RESET_CFG_WARM_RESET_THEN_SHUTDOWN]                           = PON_RESET_CFG_INVALID_VAL,
  [PM_PON_RESET_CFG_WARM_RESET_THEN_HARD_RESET]                         = PON_RESET_CFG_INVALID_VAL,
  [PM_PON_RESET_CFG_WARM_RESET_THEN_D_VDD_BATT_REMOVE_HARD_RESET]       = PON_RESET_CFG_INVALID_VAL,
  [PM_PON_RESET_CFG_WARM_RESET_THEN_X_VDD_COIN_CELL_REMOVE_HARD_RESET]  = PON_RESET_CFG_INVALID_VAL,
};

static pm_register_address_type pon_spare_register_addr[] =
{
  [PM_PON_PERPH_SPARE] = PMIO_PON_PBS_PERPH_RB_SPARE_ADDR,
  [PM_PON_DVDD_SPARE]  = PMIO_PON_PBS_DVDD_RB_SPARE_ADDR,
  [PM_PON_XVDD_SPARE]  = PMIO_PON_PBS_XVDD_RB_SPARE_ADDR,
  [PM_PON_SOFT_SPARE]  = PMIO_PON_PBS_SOFT_RB_SPARE_ADDR, 
};

static pon_reset_reg_info_type *pon_reset_reg[] =
{
  [PM_PON_RESET_SOURCE_KPDPWR]           = &pon_kpdpwr_reg,
  [PM_PON_RESET_SOURCE_RESIN]            = &pon_resin_reg,
  [PM_PON_RESET_SOURCE_RESIN_AND_KPDPWR] = &pon_resin_and_kpdpwr_reg,
  [PM_PON_RESET_SOURCE_RESIN_OR_KPDPWR]  = NULL,
  [PM_PON_RESET_SOURCE_GP1]              = NULL,
  [PM_PON_RESET_SOURCE_GP2]              = NULL,
};

static uint32
pon_s1_timer_val[] =
{ 0, 32, 56, 80, 128, 184, 272, 408, 608, 904, 1352, 2048, 3072, 4480, 6720, 10256 }; //Unit:ms

static uint32
pon_s2_timer_val[] =
{ 0, 10, 50, 100, 250, 500, 1000, 2000 }; //Unit:ms

static uint32
pon_s3_timer_val[] =
{ 0, 8, 16, 32, 63, 125, 250, 500, 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000 }; //For Tokei 2.0 and later S3_TIMER, unit:ms

static uint32
pon_s3_timer_tokei_v1_val[] =
{ 0, 2000, 4000, 8000, 16000, 32000, 64000, 128000 }; //For Tokei 1.x S3_TIMER, unit:ms

static uint32
pon_debounce_time_val[] =
{ 60, 120, 240, 490, 980, 2000, 3900, 7800, 15600, 31200, 62500, 125000, 250000 }; //Unit:ms

static uint32
pon_uvlo_hyst_val[] =
{ 150, 300, 450, 600 }; //Unit:mV

static uint32
pon_uvlo_threshold_val[] =
{ 1500, 1550, 1600, 1650, 1700, 1750, 1800, 1850, 1900, 1950, 2000, 2050, 2100, 2150, 2200, 2250, 2300,
  2350, 2400, 2450, 2500, 2550, 2600, 2650, 2700, 2750, 2800, 2850, 2900, 2950, 3000, 3050 }; //Unit:mV

static uint32
pon_ovlo_hyst_val[] =
{ 250, 500, 1000, 2000 }; //Unit:mV

static uint32
pon_ovlo_threshold_val[] =
{ 4200, 4300, 4400, 4500, 4600, 4700, 4800, 4900, 5000, 5100, 
  5200, 5300, 5400, 5500, 5600, 5700, 5800, 5900, 6000, 6100, 6200, 6300 }; //Unit:mV

typedef struct
{
  peripheral_info_type periph_info;
}pm_pon_data_type;

static pm_pon_data_type pm_pon_data_arr[PM_MAX_NUM_PMICS];

static uint8 pm_pon_event_logging[PON_EVENT_LOG_AREA_SIZE] = {0};
pm_pon_log_type pm_pon_logs[MAX_PON_EVENT_PER_SDAM] = {0}; // index 0 stores the latest log. larger indes means older log


/*===========================================================================
                  Function Prototypes
===========================================================================*/


/*===========================================================================
                  Local Function
===========================================================================*/

/*internal function to return slave id*/
static pm_err_flag_type pm_pon_get_pon_info(uint8 pmic_device_index, uint32 *pon_slave_id)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  if (NULL == pon_slave_id)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (pm_pon_initialized != TRUE)
    {
      return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
  }

  err_flag = pm_get_slave_id(pmic_device_index, 0, pon_slave_id);

  return err_flag;
}

static pm_err_flag_type pm_pon_event_store_and_sort(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 pon_events_logged[PON_EVENT_LOG_AREA_SIZE] = {0};
  uint8 push_ptr = 0, sdam_count = 0, enqueue_sdam_num = 0;
  pm_pon_log_type log = {0};
  int i = 0, index = 0;

  if(pon_log_data_captured == FALSE)
  {
    err_flag |= pm_comm_read_byte(0, PON_LOG_ENQUEUE_ADDR, &push_ptr);
    err_flag |= pm_comm_read_byte(0, PON_LOG_SDAM_COUNT_ADDR, &sdam_count);
    err_flag |= pm_comm_read_byte(0, PON_LOG_ENQUEUE_SDAM_NUM, &enqueue_sdam_num);

    // if sdam_count == 1, each SDAM contains half of the total size
    // otherwise, the SDAM stores the whole size
    uint32 read_size = (PON_EVENT_LOG_AREA_SIZE >> 1);
    err_flag |= pm_comm_read_byte_array(0, PON_PBS_PON_LOGGING_AREA_START, read_size, pon_events_logged);
    if(0 != sdam_count)
    {
      // 0: Only use 1 SDAM
      // 1: Use 2 SDAM
      // Currently only extend to 2 continuous SDAM.
      err_flag |= pm_comm_read_byte_array(0, PON_PBS_PON_LOGGING_AREA_START + 0x100, read_size, pon_events_logged + read_size);
    }
    push_ptr = PON_LOG_PUSH_PTR_INDEX(push_ptr) + (enqueue_sdam_num * read_size);

  	if(push_ptr >= PON_EVENT_LOG_AREA_SIZE)
  	{
  		return PM_ERR_FLAG_FAILURE | err_flag;
  	}

    for(i = 0; i < push_ptr; i++)
    {
      pm_pon_event_logging[i] = pon_events_logged[push_ptr - i - 1];
    }

    for(i = 0; i < (PON_EVENT_LOG_AREA_SIZE - push_ptr); i++)
    {
      pm_pon_event_logging[push_ptr + i] = pon_events_logged[PON_EVENT_LOG_AREA_SIZE - i - 1] ;
    }

    if(err_flag == PM_ERR_FLAG_SUCCESS)
    {
      pon_log_data_captured = TRUE;
    } 

    for(i = 0; i < MAX_PON_EVENT_PER_SDAM; ++i)
    {
      index = i * 4;
      log.byte0 = pm_pon_event_logging[index];
      log.byte1 = pm_pon_event_logging[index + 1];
      log.event = pm_pon_event_logging[index + 2];
      log.state = pm_pon_event_logging[index + 3];
      pm_pon_logs[i] = log;
    }
  } 

  return err_flag;  
}

pm_err_flag_type 
pm_pon_get_pon_events(pm_pon_log_type** events, uint16* log_size)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;  
  
  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (pm_pon_initialized != TRUE)
    {
      return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
  }  
  
  *events = pm_pon_logs;

   *log_size =  MAX_PON_EVENT_PER_SDAM;

  return err_flag;
  
}


pm_err_flag_type pm_pon_get_pon_log(pm_pon_event_type event, uint16* return_data)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;  
  boolean event_found = FALSE;
  uint8 data0 = 0;
  uint8 data1 = 0;
  int i = 0;

  if (NULL == return_data)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  err_flag = pm_pon_event_store_and_sort();

  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }
  
  for(i = 0; i < PON_EVENT_LOG_AREA_SIZE - 2; i += 4)
  {	
    if(event == pm_pon_event_logging[i+2])
    {
      data0 = pm_pon_event_logging[i];
      data1 = pm_pon_event_logging[i+1];
      event_found = TRUE;
      break;
    }
  }
  
  if(event_found == FALSE)
  {
     *return_data = 0x00;
  }
  else
  {
    *(uint16*)return_data = (data1<<8) | data0;
  }
  
  return err_flag;
  
}

// Only search in last pon behavior
pm_err_flag_type pm_last_pon_find_state(pm_pon_pbs_state_type state, boolean* state_found)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  int i = 0;

  if(NULL == state_found)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  *state_found = FALSE;

  err_flag = pm_pon_event_store_and_sort();
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  // i start from 1 to ignore the latest PON successful event log
  for(i = 1; i < MAX_PON_EVENT_PER_SDAM; i++)
  {
    if((PM_PON_EVENT_PON_SUCCESS == pm_pon_logs[i].event) || (PM_PON_EVENT_RESERVED == pm_pon_logs[i].event))
    {
      break; //break when we reach the penultimate PON Successful event or invalid event
    }
    else if(state == pm_pon_logs[i].state)
    {
      *state_found = TRUE;
      break;
    }
  }

  return err_flag;
}

pm_err_flag_type pm_get_next_event_index(int start_index, uint8 event, int* next_index)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  if((start_index >= MAX_PON_EVENT_PER_SDAM)
    || (NULL == next_index)
    || ((FALSE == pon_log_data_captured) && (PM_ERR_FLAG_SUCCESS != pm_pon_event_store_and_sort())))
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  *next_index = -1;

  while(start_index < MAX_PON_EVENT_PER_SDAM)
  {
    if(event == pm_pon_logs[start_index].event)
    {
      *next_index = start_index;
      break; // Find the expected event. 
    }

    ++start_index;
  }

  return err_flag;
}

pm_err_flag_type pm_get_a_pon_log(int index, pm_pon_log_type* log)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  if((index >= MAX_PON_EVENT_PER_SDAM)
    || (NULL == log)
    || ((FALSE == pon_log_data_captured) && (PM_ERR_FLAG_SUCCESS != pm_pon_event_store_and_sort())))
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  *log = pm_pon_logs[index];

  return err_flag;
}

pm_err_flag_type pm_get_last_valid_log_index(int* last_index)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  int index = MAX_PON_EVENT_PER_SDAM - 1; // The index of last log

  if((NULL == last_index)
    || ((FALSE == pon_log_data_captured) && (PM_ERR_FLAG_SUCCESS != pm_pon_event_store_and_sort())))
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  *last_index = -1;

  while(index >= 0)
  {
    if(0 != pm_pon_logs[index].event)
    {
      *last_index = index;
      break;
    }

    --index;
  }

  return err_flag;
}

/*===========================================================================

API Implementation

===========================================================================*/

pm_err_flag_type
pm_pon_init(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8   pmic_index  = 0;
  uint8   sid_index   = 0;

  peripheral_info_type  pon_pbs_peripheral_info;
  uint8   warm_reset_reason = 0;
  uint32         slave_count = 0;
  pm_device_info_type pmic_device_info;
  uint8 periph_type = 0;
  uint32 primary_pmic_index = 0;
  uint16 dig_version = 0;
  uint16 ana_version = 0;
  uint8 periph_subtype = 0;
  
  if (pm_pon_initialized == TRUE)
  {
    return err_flag;
  }

  memset(&pon_pbs_peripheral_info, 0, sizeof(peripheral_info_type));
  pon_pbs_peripheral_info.base_address = PON_PBS_BASE;

  /* i.Ensure that pmic device is initialized ii.check for vaid PON peripheral */
  err_flag = pm_device_setup();
  if(pm_is_pmic_present(PMIC_A) == FALSE)
  {
     //pm_log_message("Bootup: No PMIC on RUMI Target");
     return err_flag = PM_ERR_FLAG_SUCCESS;
  }
  
  err_flag |= pm_comm_read_byte(PMIC_A_SLAVEID_PRIM, PMIO_PON_PBS_PERPH_TYPE_ADDR, &periph_type);
  
  if ((periph_type != PM_HW_MODULE_PON) || (err_flag != PM_ERR_FLAG_SUCCESS))
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  
  
  /* Get PON perepheral type and perepheral sub type for each valid PMIC on target */
  for (pmic_index = 0; pmic_index < PM_MAX_NUM_PMICS; pmic_index += slave_count)
  {
    sid_index = pmic_index;
    if (pm_get_peripheral_info(sid_index, &pon_pbs_peripheral_info) == PM_ERR_FLAG_SUCCESS)
    {
      pm_pon_data_arr[pmic_index].periph_info = pon_pbs_peripheral_info;
    }
  
  pm_get_pmic_info(pmic_index, &pmic_device_info);
  slave_count = (pmic_device_info.ePmicModel == PMIC_IS_UNKNOWN) ? 1 : pmic_device_info.nSlaveCount ;
  }
  
  primary_pmic_index = pm_get_primary_pmic_index();
  
  dig_version = pm_pon_data_arr[primary_pmic_index].periph_info.digital_major_version << 8 | pm_pon_data_arr[primary_pmic_index].periph_info.digital_minor_version ;
  ana_version = pm_pon_data_arr[primary_pmic_index].periph_info.analog_major_version << 8 | pm_pon_data_arr[primary_pmic_index].periph_info.analog_minor_version ;
  periph_subtype = pm_pon_data_arr[primary_pmic_index].periph_info.peripheral_subtype;
  
  if(dig_version > SUPPORTED_DIG_VERSION || ana_version > SUPPORTED_ANA_VERSION || periph_subtype != SUPPORTED_PBS_GEN)
  {
    CORE_VERIFY(0);
  }

  /*core doesn't need since loader would write and also core may not have write access*/
  if(pm_get_img_type() == PM_IMG_LOADER)
  {
     /* Read ON reason and write the DVDD_RB_SPARE register bit <0> to 1 if Warm Reset occured */
     err_flag |= pm_comm_read_byte(PMIC_A_SLAVEID_PRIM, BOOT1_ON_REASON_ADDR, &warm_reset_reason);
     if (warm_reset_reason & PON_ON_REASON_WARM_SEQ_BMSK)
     {
       err_flag |= pm_comm_write_byte_mask(PMIC_A_SLAVEID_PRIM, PMIO_PON_PBS_DVDD_RB_SPARE_ADDR, PON_DVDD_RB_SPARE_WARM_RESET_MASK, 0x01);
     }
	 /*enable warm reset bit on revision 02.00 onwards*/
	 if(dig_version >= (0x02<<8 | 0x00))
     {
       err_flag |= pm_comm_write_byte_mask(PMIC_A_SLAVEID_PRIM, PMIO_PON_PBS_PON_SW_CFG_ADDR, PMIO_PON_PBS_PON_SW_CFG_WARM_RESET_RMSK, ALLOW_WARM_RESET);
     }
  }
  
  err_flag |= pm_pon_event_store_and_sort(); //store and sort pon events

  if (err_flag == PM_ERR_FLAG_SUCCESS)
  {
    pm_pon_initialized = TRUE;
  }

  return err_flag;
}


pm_err_flag_type
pm_pon_ps_hold_cfg(uint32 pmic_device_index, pm_pon_reset_cfg_type ps_hold_cfg)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 ps_hold_cfg_val = 0;
  uint32 slave_id = 0;

  if (ps_hold_cfg >= PM_PON_RESET_CFG_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  } 
  else if (pon_reset_cfg_val[ps_hold_cfg] == PON_RESET_CFG_INVALID_VAL)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  } 
  else
  {
    err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);
    if (err_flag == PM_ERR_FLAG_SUCCESS)
    {
      ps_hold_cfg_val = pon_reset_cfg_val[ps_hold_cfg];

      /* i.) Disable reset ii.) wait for 10 sleep clock cycles iii.)config and iv.) enable reset */
      err_flag = pm_comm_write_byte(slave_id, pon_ps_hold_reg.reset_ctl2_addr, 0x0);
      //disable and clear irq
      err_flag |= pm_pon_irq_enable(PMIC_A, pon_ps_hold_reg.irq, FALSE);
      err_flag |= pm_pon_irq_clear(PMIC_A, pon_ps_hold_reg.irq);

      //set type
      err_flag |= pm_pon_irq_set_trigger(PMIC_A, pon_ps_hold_reg.irq, pon_ps_hold_reg.trigger_type);

      err_flag |= pm_comm_write_byte(slave_id, pon_ps_hold_reg.reset_ctl_addr, ps_hold_cfg_val);
      WAIT_FOR_SLEEP_CLK_CYCLE(8);
      err_flag |= pm_comm_write_byte(slave_id, pon_ps_hold_reg.reset_ctl2_addr, pon_ps_hold_reg.reset_en_mask);
      WAIT_FOR_SLEEP_CLK_CYCLE(3);

      //enable interrupt
      err_flag |= pm_pon_irq_enable(PMIC_A, pon_ps_hold_reg.irq, TRUE);
    }
  }

  return err_flag;
}


pm_err_flag_type
pm_pon_reset_source_cfg(uint32 pmic_device_index, pm_pon_reset_source_type reset_source,
                        uint32 s1_timer_ms, uint32 s2_timer_ms, pm_pon_reset_cfg_type reset_cfg)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 reset_en, reset_val = 0;
  uint8 s1_timer_id = 0;
  uint8 s2_timer_id = 0;
  uint32 slave_id = 0;
  pon_reset_reg_info_type *reset_reg = NULL;

  if (reset_cfg >= PM_PON_RESET_CFG_INVALID)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  reset_reg = pon_reset_reg[reset_source];
  if (reset_reg == NULL)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  /*read current enabled status*/
  err_flag = pm_comm_read_byte(slave_id, reset_reg->reset_ctl2_addr, &reset_en);
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  /*isable and wait for 8 sleep clock cycle*/
  err_flag = pm_comm_write_byte_mask(slave_id, reset_reg->reset_ctl2_addr, reset_reg->reset_en_mask, 0x0);

  //disable and clear irq
  err_flag |= pm_pon_irq_clear(PMIC_A, reset_reg->irq);
  err_flag |= pm_pon_irq_enable(PMIC_A, reset_reg->irq, FALSE);  


  /* Calc and configure S1 and S2 timer. Get the upper limit if a value falls in between */
  s1_timer_id = pm_utils_get_upper_idx(s1_timer_ms, pon_s1_timer_val, ARRAY_LENGTH(pon_s1_timer_val));
  s2_timer_id = pm_utils_get_upper_idx(s2_timer_ms, pon_s2_timer_val, ARRAY_LENGTH(pon_s2_timer_val));
  err_flag |= pm_comm_write_byte_mask(slave_id, reset_reg->s1_timer_addr, reset_reg->s1_timer_mask, s1_timer_id);
  WAIT_FOR_SLEEP_CLK_CYCLE(8);
  err_flag |= pm_comm_write_byte_mask(slave_id, reset_reg->s2_timer_addr, reset_reg->s2_timer_mask, s2_timer_id);
  WAIT_FOR_SLEEP_CLK_CYCLE(8);

  //set type
  err_flag |= pm_pon_irq_set_trigger(PMIC_A, reset_reg->irq, reset_reg->trigger_type);

  //reenable s2 reset_reset_en
  /* Configure reset value */
  reset_val = pon_reset_cfg_val[reset_cfg];
  if (reset_val < PON_RESET_CFG_INVALID_VAL)
  {
    err_flag |= pm_comm_write_byte_mask(slave_id, reset_reg->reset_ctl_addr, reset_reg->reset_type_mask, reset_val);
    WAIT_FOR_SLEEP_CLK_CYCLE(8);
  } 
  else
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  /* Enable reset if it was already in enable state */
  //disable and clear irq
    err_flag |= pm_pon_irq_enable(PMIC_A, reset_reg->irq, FALSE);
    err_flag |= pm_pon_irq_clear(PMIC_A, reset_reg->irq);  
	
	err_flag |= pm_comm_write_byte_mask(slave_id, reset_reg->reset_ctl2_addr, reset_reg->reset_en_mask, 0xFF);
	
  //disable irq, clear irq, enable irq
    err_flag |= pm_pon_irq_clear(PMIC_A, reset_reg->irq);
    err_flag |= pm_pon_irq_enable(PMIC_A, reset_reg->irq, FALSE);
    err_flag |= pm_pon_irq_enable(PMIC_A, reset_reg->irq, TRUE);

  return err_flag;
}


pm_err_flag_type
pm_pon_gp_reset_cfg(uint32  pmic_device_index, pm_pon_reset_source_type reset_source, pm_pon_reset_cfg_type reset_cfg_type)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  return err_flag;
}


pm_err_flag_type
pm_pon_reset_source_ctl(uint32 pmic_device_index, pm_pon_reset_source_type reset_source, pm_on_off_type on_off)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 slave_id = 0;
  pon_reset_reg_info_type *reset_reg = NULL;
  uint8 data = (on_off == PM_ON) ? 0xFF : 0;

  reset_reg = pon_reset_reg[reset_source];

  if (NULL == reset_reg)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);  
  
    if (err_flag == PM_ERR_FLAG_SUCCESS)
    {
      err_flag = pm_comm_write_byte_mask(slave_id, reset_reg->reset_ctl2_addr, reset_reg->reset_en_mask, data);
      WAIT_FOR_SLEEP_CLK_CYCLE(3);
    }
  }

  return err_flag;
}


pm_err_flag_type
pm_pon_stage3_reset_source_cfg(uint32 pmic_device_index, pm_pon_reset_source_type reset_source, uint32 s3_timer_ms)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 s3_timer_id = 0;
  uint32 slave_id = 0;
  pm_register_data_type pon_pbs_revision[2];
  pm_register_data_type pon_perph_type[2];

  if (reset_source > PM_PON_RESET_SOURCE_RESIN_OR_KPDPWR)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);

  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }


  /* Write to Set Stage 3 reset source, write once register */
  err_flag = pm_comm_write_byte_mask(slave_id, PMIO_PON_PBS_RESET_S3_SRC_ADDR, PMIO_PON_PBS_RESET_S3_SRC_RMSK, reset_source);
  WAIT_FOR_SLEEP_CLK_CYCLE(5);

  /* Calc S3 timer id, unlock secure register and set stage 3 reset timer*/
  pm_comm_read_byte_array(slave_id, PMIO_PON_PBS_REVISION1_ADDR, 2, pon_pbs_revision);
  pm_comm_read_byte_array(slave_id, PMIO_PON_PBS_PERPH_TYPE_ADDR, 2, pon_perph_type);
  if((pon_perph_type[0] == PM_HW_MODULE_PON) && (pon_perph_type[1] == PM_HW_MODULE_PON_PBS_GEN3)
      && (pon_pbs_revision[0] < 2) && (pon_pbs_revision[1] < 2))
  {
    // For Tokei v1.x chip
    s3_timer_id = pm_utils_get_upper_idx(s3_timer_ms, pon_s3_timer_tokei_v1_val, ARRAY_LENGTH(pon_s3_timer_tokei_v1_val));
  }
  else
  {
    s3_timer_id = pm_utils_get_upper_idx(s3_timer_ms, pon_s3_timer_val, ARRAY_LENGTH(pon_s3_timer_val));
  }

  err_flag |= pm_comm_write_byte_mask(slave_id, PMIO_PON_PBS_RESET_S3_TIMER_ADDR, PMIO_PON_PBS_RESET_S3_TIMER_RMSK, s3_timer_id);
  WAIT_FOR_SLEEP_CLK_CYCLE(5);

  return err_flag;
}


pm_err_flag_type                                      
pm_pon_get_fsm_current_state(uint8 pmic_device_index, pm_pon_fsm_status_type *pon_fsm_status)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  
  uint32 slave_id = 0;
  
  uint8 fsm_status[2] = {0, 0};

  if (pon_fsm_status == NULL)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);
    if (err_flag == PM_ERR_FLAG_SUCCESS)
    {
      err_flag = pm_comm_read_byte_array(slave_id, PMIO_PON_PBS_HW_FSM_STATUS_ADDR, 2, fsm_status);

      pon_fsm_status->hw_fsm = (pm_pon_hw_fsm_status_type)(fsm_status[0] & PMIO_PON_PBS_HW_FSM_STATUS_RMSK);

      pon_fsm_status->pbs_fsm = (pm_pon_pbs_fsm_status_type)(fsm_status[1] & PMIO_PON_PBS_PBS_FSM_STATUS_RMSK);
    }
  }

  return err_flag;
}

pm_err_flag_type
pm_pon_get_pon_reason(uint32 pmic_device_index, pm_pon_reason_type *reason)  
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 slave_id = 0;
  uint16 pon_reason_raw = 0;
  pm_pon_on_state_reason_type on_state_reason = {0};

  if (reason == NULL)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);

  	//update for hard_reset
  	err_flag |= pm_pon_get_on_reason(pmic_device_index, &on_state_reason);
  	reason->hard_reset = on_state_reason.hard_reset_seq ? TRUE : FALSE;

    err_flag |= pm_pon_get_pon_log(PM_PON_EVENT_PON_TRIGGER, &pon_reason_raw);
    if (err_flag == PM_ERR_FLAG_SUCCESS)
    {
      reason->sid = (pon_reason_raw & 0xF000)>>12;
      reason->pid = (pon_reason_raw & 0x0FF0)>>4;
      reason->irq  = pon_reason_raw & 0x7;
      reason->known_rsn = TRUE;
      switch(pon_reason_raw) //SID<<12|pid<<4|irq
      {      
      case PON_PBS_KEYPD_PWR_N_RSN:  
        reason->kpdpwr = TRUE;
        break;
      case PON_PBS_SMPL_RSN: 
        reason->smpl = TRUE;
          break;
      case PON_PBS_PON1_RSN:
        reason->pon1 = TRUE;
        break;
      case PON_PBS_CBLPWR_RSN:
        reason->cblpwr = TRUE;
        break;
      case PON_PBS_SYS_OK_RSN: 
        reason->usb_chg = TRUE;
        break;
      case PON_PBS_RTC_ALARM_RSN:
        reason->rtc = TRUE;
        break;
      default:
        reason->known_rsn = FALSE;
        break;      
      }
    }
  }

  return err_flag;
}

pm_err_flag_type
pm_pon_get_poff_reason(uint32 pmic_device_index, pm_pon_poff_reason_type *reason)   
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 slave_id = 0;
  uint16 poff_reason_raw = 0;

  if (reason == NULL)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  } else
  {
    err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);
    err_flag |= pm_pon_get_pon_log(PM_PON_EVENT_RESET_TRIGGER, &poff_reason_raw);
    if (err_flag == PM_ERR_FLAG_SUCCESS)
    {
      reason->sid = (poff_reason_raw & 0xF000) >> 12;
      reason->pid = (poff_reason_raw & 0x0FF0) >> 4;
      reason->irq = poff_reason_raw & 0x7;
      reason->known_rsn = TRUE;
      switch (poff_reason_raw) //SID<<12|pid<<4|irq
      {
        case PON_PBS_KEYPD_PWR_N_S2_RSN :
        case PON_PBS_KEYPD_PWR_N_RSN :
          reason->kpdpwr = TRUE;
          break;
        case PON_PBS_RESIN_N_S2_RSN :
        case PON_PBS_RESIN_N_DEB_RSN :
          reason->resin = TRUE;
          break;
        case PON_PBS_KPDPWR_AND_RESIN_RSN :
          reason->kpdpwr_and_resin = TRUE;
          break;
        case PON_PBS_PMIC_WD_RSN :
          reason->pmic_wd = TRUE;
          break;
        case PON_PBS_PS_HOLD_RSN:
          reason->ps_hold = TRUE;
          break;
        case PON_PBS_SW_RST_RSN :
          reason->soft = TRUE;
          break;
        default:
          reason->known_rsn = FALSE;
          break;
      }
    }
  }

  return err_flag;
}


pm_err_flag_type
pm_pon_get_warm_reset_reason(uint32 pmic_device_index, pm_pon_warm_reset_reason_type *reason)  
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 slave_id = 0;
  uint16 pon_reason_raw = 0;

  if (reason == NULL)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);
  err_flag |= pm_pon_get_pon_log(PM_PON_EVENT_PON_TRIGGER, &pon_reason_raw);  
    if (err_flag == PM_ERR_FLAG_SUCCESS)
    {
    reason->sid = (pon_reason_raw & 0xF000)>>12;
    reason->pid = (pon_reason_raw & 0x0FF0)>>4;
    reason->irq = pon_reason_raw & 0x7;
    reason->known_rsn = TRUE;
    switch(pon_reason_raw) //SID<<12|pid<<4|irq
    {
      case PON_PBS_KEYPD_PWR_N_S2_RSN : 
            case PON_PBS_KEYPD_PWR_N_RSN : 
            reason->kpdpwr = TRUE;
            break;
            case PON_PBS_RESIN_N_S2_RSN : 
            case PON_PBS_RESIN_N_DEB_RSN :
            reason->resin = TRUE;
            break;
            case PON_PBS_KPDPWR_AND_RESIN_RSN : 
            reason->kpdpwr_and_resin = TRUE;
            break;
            case PON_PBS_PMIC_WD_RSN : 
            reason->pmic_wd = TRUE;
            break;
            case PON_PBS_PS_HOLD_RSN : 
            reason->ps_hold = TRUE;
            break;
            case PON_PBS_SW_RST_RSN : 
            reason->soft = TRUE;
            break;
            default:
      reason->known_rsn = FALSE;
      break;    
    }
    }
  }

  return err_flag;
}


pm_err_flag_type
pm_pon_get_on_reason(uint32 pmic_device_index, pm_pon_on_state_reason_type *reason)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 slave_id = 0;
  uint16 pon_reason_raw = 0;

  if (reason == NULL)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);
    err_flag |= pm_pon_get_pon_log(PM_PON_EVENT_RESET_TYPE, &pon_reason_raw); 
    pon_reason_raw &= 0xFF;
    if (err_flag == PM_ERR_FLAG_SUCCESS)
    {
      reason->warm_seq       = (pon_reason_raw == 1 ) ? TRUE : FALSE;
      reason->pon_seq        = (pon_reason_raw == 1 ) ? FALSE : TRUE; //if warm reset sequence ran then PON sequence will be FALSE.
      reason->shutdown_seq   = (pon_reason_raw == 4 ) ? TRUE : FALSE;
      reason->hard_reset_seq = (pon_reason_raw == 7 ) ? TRUE : FALSE;
    }
  }

  return err_flag;
}


pm_err_flag_type
pm_pon_get_off_reason(uint32 pmic_device_index, pm_pon_off_state_reason_type *reason)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 slave_id = 0;
  uint16 pon_reason_raw = 0;

  if (reason == NULL)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);

    err_flag |= pm_pon_get_pon_log(PM_PON_EVENT_FUNDAMENTAL_RESET, &pon_reason_raw);

    if (err_flag == PM_ERR_FLAG_SUCCESS)
    {
      //15=XVDD,14=DVDD,13=RAW_XVDD,7-4=S3_REASON"; break;
      reason->raw_xvdd_rb_occured       = (pon_reason_raw & PON_PBS_RAW_XVDD_RB_MASK) ? TRUE : FALSE;
      reason->raw_dvdd_rb_occured       = (pon_reason_raw & PON_PBS_RAW_DVDD_RB_MASK) ? TRUE : FALSE;
      reason->immediate_xvdd_shutdown   = (pon_reason_raw & PON_PBS_IMMEDIATE_XVDD_SHUTDOWN_MASK) ? TRUE : FALSE;
      reason->s3_reset = (pon_reason_raw & PON_PBS_S3_RESET_MASK) >> PON_PBS_S3_RESET_BSHIFT;
      reason->fault_seq = 0;
      reason->poff_seq = 0;
    }
  }

  return err_flag;
}


pm_err_flag_type
pm_pon_get_stage3_reset_reason(uint32 pmic_device_index, pm_pon_stage3_reset_reason_type *reason)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 slave_id = 0;

  if (reason == NULL)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id); 
    if (err_flag == PM_ERR_FLAG_SUCCESS && pon_reasons_addr.s3_reset_reason_addr)
    {
      err_flag = pm_comm_read_byte(slave_id, pon_reasons_addr.s3_reset_reason_addr, (uint8 *)reason);
    }
  }

  return err_flag;
}


pm_err_flag_type
pm_pon_get_all_pon_reasons(uint32 pmic_device_index, uint64 *pon_reasons) 
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  uint32 slave_id = 0;

  if (pon_reasons == NULL)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);

    if (err_flag == PM_ERR_FLAG_SUCCESS && pon_reasons_addr.pon_reason1_addr)
    {
      err_flag = pm_comm_read_byte_array(slave_id, pon_reasons_addr.pon_reason1_addr, 8, (uint8 *)pon_reasons);
    }
  }

  return err_flag;
}


pm_err_flag_type
pm_pon_get_fault_reason(uint32 pmic_device_index, pm_pon_fault_state_reason_type *reason)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 slave_id = 0;

  if (reason == NULL)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);
	
    if (err_flag == PM_ERR_FLAG_SUCCESS && pon_reasons_addr.fault_reason1_addr)
    {
      err_flag = pm_comm_read_byte_array(slave_id, pon_reasons_addr.fault_reason1_addr, 2, (uint8*)reason);
    }
  }

  return err_flag;
}

pm_err_flag_type
pm_pon_get_fault_reasons(uint32 pmic_device_index, uint64 *fault_reasons)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 slave_id = 0;

  if (fault_reasons == NULL)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);
	
    if (err_flag == PM_ERR_FLAG_SUCCESS && pon_reasons_addr.fault_reason1_addr)
    {
      err_flag = pm_comm_read_byte_array(slave_id, pon_reasons_addr.fault_reason1_addr, 3, (uint8 *)fault_reasons); //only3 fault reasons
    }
  }

  return err_flag;
}


pm_err_flag_type
pm_pon_debounce_ctl(uint32 pmic_device_index, uint32 time_delay)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  uint32 slave_id = 0;
  uint8 time_id = pm_utils_get_upper_idx(time_delay, pon_debounce_time_val,
                                         ARRAY_LENGTH(pon_debounce_time_val));

  err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);
  if (err_flag == PM_ERR_FLAG_SUCCESS)
  {
    err_flag = pm_comm_write_byte_mask(slave_id, PMIO_PON_PBS_DEBOUNCE_CTL_ADDR,
                                       PMIO_PON_PBS_DEBOUNCE_CTL_DEBOUNCE_BMSK, time_id);
    /* Wait for 5 sleep clock cycle */
    WAIT_FOR_SLEEP_CLK_CYCLE(5);
  }

  return err_flag;
}

pm_err_flag_type
pm_pon_irq_enable(uint32 pmic_device_index, pm_pon_irq_type irq, boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 mask = 1 << irq;
  pm_register_address_type irq_reg = enable ? PMIO_PON_PBS_INT_EN_SET_ADDR : PMIO_PON_PBS_INT_EN_CLR_ADDR;

  uint32 slave_id = 0;

  if (irq >= PM_PON_IRQ_INVALID)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);
    if (err_flag == PM_ERR_FLAG_SUCCESS)
    {
      err_flag = pm_comm_write_byte(slave_id, irq_reg, mask);
    }
  }

  return err_flag;
}


pm_err_flag_type
pm_pon_irq_clear(uint32  pmic_device_index, pm_pon_irq_type irq)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 slave_id = 0;
  uint8 mask = 1 << irq;

  if (irq >= PM_PON_IRQ_INVALID)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);
    if (err_flag == PM_ERR_FLAG_SUCCESS)
    {
      err_flag = pm_comm_write_byte(slave_id, PMIO_PON_PBS_INT_LATCHED_CLR_ADDR, mask);
    }
  }

  return err_flag;
}


pm_err_flag_type
pm_pon_irq_set_trigger(uint32 pmic_device_index, pm_pon_irq_type irq, pm_irq_trigger_type trigger)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 slave_id = 0;
  uint8 mask = 1 << irq;
  uint8 set_type = 0;
  uint8 polarity_high = 0;
  uint8 polarity_low = 0;

  if (irq >= PM_PON_IRQ_INVALID)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  switch (trigger)
  {
  case PM_IRQ_TRIGGER_ACTIVE_LOW:
    set_type = 0x00;
    polarity_high = 0x00;
    polarity_low = 0xFF;
    break;
  case PM_IRQ_TRIGGER_ACTIVE_HIGH:
    set_type = 0x00;
    polarity_high = 0xFF;
    polarity_low = 0x00;
    break;
  case PM_IRQ_TRIGGER_RISING_EDGE:
    set_type = 0xFF;
    polarity_high = 0xFF;
    polarity_low = 0x00;
    break;
  case PM_IRQ_TRIGGER_FALLING_EDGE:
    set_type = 0xFF;
    polarity_high = 0x00;
    polarity_low = 0xFF;
    break;
  case PM_IRQ_TRIGGER_DUAL_EDGE:
    set_type = 0xFF;
    polarity_high = 0xFF;
    polarity_low = 0xFF;
    break;
  default:
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);
  
  if (err_flag == PM_ERR_FLAG_SUCCESS)
  {
    err_flag = pm_comm_write_byte_mask(slave_id, PMIO_PON_PBS_INT_SET_TYPE_ADDR, mask, set_type);
    err_flag |= pm_comm_write_byte_mask(slave_id, PMIO_PON_PBS_INT_POLARITY_HIGH_ADDR, mask, polarity_high);
    err_flag |= pm_comm_write_byte_mask(slave_id, PMIO_PON_PBS_INT_POLARITY_LOW_ADDR, mask, polarity_low);
  }

  return err_flag;
}


pm_err_flag_type
pm_pon_irq_status(uint32 pmic_device_index, pm_pon_irq_type irq, pm_irq_status_type type, boolean *status)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 slave_id = 0;
  uint8 mask = 1 << irq;
  uint8 data = 0;
  pm_register_address_type reg = 0;

  if (status == NULL)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  if (irq >= PM_PON_IRQ_INVALID)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  switch (type)
  {
  case PM_IRQ_STATUS_RT:
    reg = PMIO_PON_PBS_INT_RT_STS_ADDR;
    break;
  case PM_IRQ_STATUS_LATCHED:
    reg = PMIO_PON_PBS_INT_LATCHED_STS_ADDR;
    break;
  case PM_IRQ_STATUS_PENDING:
    reg = PMIO_PON_PBS_INT_PENDING_STS_ADDR;
    break;
  default:
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);
  if (err_flag == PM_ERR_FLAG_SUCCESS)
  {
    err_flag = pm_comm_read_byte(slave_id, reg, &data);
    *status = (data & mask) ? TRUE : FALSE;
  }

  return err_flag;
}


pm_err_flag_type
pm_pon_config_uvlo(uint32 pmic_device_index, uint32 threshold_mv, uint32 hyst_mv, boolean enable)
{
  pm_err_flag_type  err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 uvlo_thresh_data = 0;
  uint8 uvlo_hyst_data   = 0;
  uint8 uvlo_ctl_data    = 0;
  uint32 slave_id = 0;

  //Calculate UVLO HYST
  uvlo_hyst_data = pm_utils_get_upper_idx(hyst_mv, pon_uvlo_hyst_val, ARRAY_LENGTH(pon_uvlo_hyst_val));
  uvlo_thresh_data = pm_utils_get_upper_idx(threshold_mv, pon_uvlo_threshold_val, ARRAY_LENGTH(pon_uvlo_threshold_val));

  uvlo_ctl_data = (enable << PMIO_PON_PBS_UVLO_CTL_UVLO_EN_SHIFT) | (uvlo_hyst_data << PMIO_PON_PBS_UVLO_CTL_UVLO_HYST_SHIFT) | uvlo_thresh_data;

  err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);
  if (err_flag == PM_ERR_FLAG_SUCCESS)
  {
    //Config UVLO CTL
    err_flag |= pm_comm_write_byte(slave_id, PMIO_PON_PBS_UVLO_CTL_ADDR, uvlo_ctl_data);
    WAIT_FOR_SLEEP_CLK_CYCLE(3);
  }

  return err_flag;
}

pm_err_flag_type
pm_pon_config_ovlo(uint32 pmic_device_index, uint32 threshold_mv, uint32 hyst_mv, boolean enable)
{
  pm_err_flag_type  err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 ovlo_thresh_data = 0, ovlo_hyst_data = 0, ovlo_ctl_data = 0; 
  uint32 slave_id = 0;

  //Calculate OVLO HYST
  ovlo_hyst_data = pm_utils_get_upper_idx(hyst_mv, pon_ovlo_hyst_val, ARRAY_LENGTH(pon_ovlo_hyst_val));
  ovlo_thresh_data = pm_utils_get_upper_idx(threshold_mv, pon_ovlo_threshold_val, ARRAY_LENGTH(pon_ovlo_threshold_val));

  ovlo_ctl_data = (enable << PMIO_PON_PBS_OVLO_CTL_OVLO_EN_SHIFT) | (ovlo_hyst_data << PMIO_PON_PBS_OVLO_CTL_OVLO_HYST_SHIFT) | ovlo_thresh_data;

  err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);
  
  if (err_flag == PM_ERR_FLAG_SUCCESS)
  {
    //Config OVLO CTL
    err_flag |= pm_comm_write_byte(slave_id, PMIO_PON_PBS_OVLO_CTL_ADDR, ovlo_ctl_data);
    WAIT_FOR_SLEEP_CLK_CYCLE(3);
  }
  
  return err_flag;
}


pm_err_flag_type
pm_pon_warm_reset_status(uint32 pmic_device_index, boolean *status)
{
  pm_err_flag_type   err_flag = PM_ERR_FLAG_SUCCESS;
  uint8              data = 0;
  uint32 slave_id = 0;

  if (status == NULL)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);
    if(pm_is_pmic_present(PMIC_A) == FALSE)
    {
       //pm_log_message("Bootup: No PMIC on RUMI Target");
       return err_flag = PM_ERR_FLAG_SUCCESS;
    }

    if (err_flag == PM_ERR_FLAG_SUCCESS)
    {
      /*spare register stores warm reset info*/
      err_flag = pm_comm_read_byte(slave_id, PMIO_PON_PBS_DVDD_RB_SPARE_ADDR, &data);
      *status = (data & PON_DVDD_RB_SPARE_WARM_RESET_MASK) ? TRUE : FALSE;
    }
  }

  return err_flag;
}

pm_err_flag_type
pm_pon_warm_reset_status_clear(uint32 pmic_device_index)
{
  pm_err_flag_type   err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 slave_id = 0;

  err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);
  if(pm_is_pmic_present(PMIC_A) == FALSE)
  {
     //pm_log_message("Bootup: No PMIC on RUMI Target");
     return err_flag = PM_ERR_FLAG_SUCCESS;
  }

  if (err_flag == PM_ERR_FLAG_SUCCESS)
  {
    err_flag = pm_comm_write_byte_mask(slave_id, PMIO_PON_PBS_DVDD_RB_SPARE_ADDR, PON_DVDD_RB_SPARE_WARM_RESET_MASK, 0x00);
  }

  return err_flag;
}


pm_err_flag_type
pm_pon_pbl_get_status(uint32  pmic_device_index, pm_pon_pbl_status_type pbl_status, boolean *status)
{
  pm_err_flag_type   err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type  data = 0;
  uint32 slave_id = 0;

  if (status == NULL)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  err_flag = pm_comm_read_byte(slave_id, PMIO_PON_PBS_PON_PBL_STATUS_ADDR, &data);

  if (pbl_status == PM_PON_PBL_DVDD_RB_OCCURRED)
  {
    *status = (data & PMIO_PON_PBS_PON_PBL_STATUS_DVDD_RB_OCCURRED_BMSK) ? TRUE : FALSE;
  }
  else if (pbl_status == PM_PON_PBL_XVDD_RB_OCCURRED)
  {
    *status = (data & PMIO_PON_PBS_PON_PBL_STATUS_XVDD_RB_OCCURRED_BMSK) ? TRUE : FALSE;
  }
  else
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }

  return err_flag;
}


pm_err_flag_type
pm_pon_get_spare_reg(uint32 pmic_device_index, pm_pon_spare_reg_type spare_reg, uint8 *data_ptr)
{
  pm_err_flag_type   err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_address_type  spare_register_addr =  0x00;
  uint32 slave_id = 0;

  if ((spare_reg >= PM_PON_SPARE_INVALID) || (!data_ptr))
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);
    if (err_flag == PM_ERR_FLAG_SUCCESS)
    {
      spare_register_addr = pon_spare_register_addr[spare_reg];
      err_flag = pm_comm_read_byte(slave_id, spare_register_addr, data_ptr);
    }
  }

  return err_flag;
}


pm_err_flag_type
pm_pon_set_spare_reg(uint32 pmic_device_index, pm_pon_spare_reg_type spare_reg, uint8 set_value, uint8 mask)
{
  pm_err_flag_type	 err_flag = PM_ERR_FLAG_SUCCESS;

  pm_register_address_type  spare_register_addr;

  uint32 slave_id = 0;

  if ((spare_reg >= PM_PON_SPARE_INVALID)
      || (mask > PM_PON_MAX_SPARE_BIT_MASK))
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);
  if (err_flag == PM_ERR_FLAG_SUCCESS)
  {
    spare_register_addr = pon_spare_register_addr[spare_reg];
    err_flag = pm_comm_write_byte_mask(slave_id, spare_register_addr, mask, set_value);
  }

  return err_flag;
}


pm_err_flag_type
pm_pon_trigger_enable_status(uint32 pmic_device_index, pm_pon_trigger_type trigger, boolean *status)
{
  pm_err_flag_type   err_flag = PM_ERR_FLAG_SUCCESS;
 
  pm_register_data_type pon_trigger[EIGHT_BYTES] = {0};

  uint32 slave_id = 0;
  
  pm_register_address_type reg_addr = 0;
  
  pm_pon_trigger_config_type trigger_config = { 0 };

  if ((trigger >= PM_PON_TRIGGER_INVALID) || (NULL == status))
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {  
    err_flag |= pm_pon_get_pon_info(pmic_device_index, &slave_id);
  
    err_flag |= pm_pon_target_get_pon_trigger_config(trigger, &trigger_config);
  
    if ((err_flag == PM_ERR_FLAG_SUCCESS) && trigger_config.pid)
    {
    reg_addr = PON_TRIG_CFG_PID_ADDR + (trigger_config.trig_index * EIGHT_BYTES);
    
      err_flag = pm_comm_read_byte_array(slave_id, reg_addr, EIGHT_BYTES, pon_trigger);
    
      *status =  (pon_trigger[PON_TRIG_EN_ADDR_INDEX] & (trigger_config.trig_mask)) ? TRUE : FALSE;
    }
  }

  return err_flag;
}

pm_err_flag_type
pm_pon_trigger_enable(uint32 pmic_device_index, pm_pon_trigger_type trigger, boolean enable)
{
  pm_err_flag_type   err_flag = PM_ERR_FLAG_SUCCESS;
 
  uint8 mask = 0;
  uint8 data = 0x00;
  uint32 slave_id = 0;
  pm_register_address_type reg_addr = 0x00;
  
  pm_pon_trigger_config_type trigger_config = { 0 };

  if (trigger >= PM_PON_TRIGGER_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    err_flag |= pm_pon_get_pon_info(pmic_device_index, &slave_id);
  
   err_flag |= pm_pon_target_get_pon_trigger_config(trigger, &trigger_config);
  
    if ((err_flag == PM_ERR_FLAG_SUCCESS) && trigger_config.pid )
    {
      data = (enable) ? trigger_config.trig_mask : 0x00;
    
      mask = trigger_config.trig_mask;
    
      reg_addr = (PON_TRIG_CFG_PID_ADDR + PON_TRIG_EN_ADDR_INDEX)+ (trigger_config.trig_index * EIGHT_BYTES);
    
      err_flag = pm_comm_write_byte_mask(slave_id, reg_addr, mask, data);
	  
	  //write to level/edge irq of peripheral irq as well
	  
	  reg_addr = (trigger_config.pid * 0x100)+ INT_SET_TYPE_OFFSET;
	  
	  err_flag = pm_comm_write_byte_mask(trigger_config.sid, reg_addr, trigger_config.trig_mask, data);
	  
    }
  }

  return err_flag;
}


pm_err_flag_type pm_pon_set_option_bit(uint32 pmic_device_index, pm_pon_option_bit_type cfg_field, boolean cfg_data)
{
   pm_err_flag_type   err_flag       = PM_ERR_FLAG_SUCCESS;
   pm_pon_trigger_config_type trigger_config = { 0 };
   pm_pon_trigger_type trigger;
   pm_register_data_type mask = 0x00;
   uint8 irq_type  = 0;
   uint8 polarity_high = 0;
   uint8 polarity_low = 0;

   uint32 slave_id = 0;
   pm_register_address_type irq_type_reg_addr = 0;
   pm_register_address_type polarity_high_reg_addr = 0;
   pm_register_address_type polarity_low_reg_addr = 0;


   switch (cfg_field)
   {
   case PM_PON_OPTION_DC_CHG_REDGE_PON :
      trigger = PM_PON_TRIGGER_DC_CHG;
      irq_type = cfg_data ? 0xFF : 0x00; //0=level, 1=edge
      polarity_high = 0xFF;
      polarity_low = 0x0;
      break;

   case PM_PON_OPTION_USB_CHG_REDGE_PON :
      //trigger = PM_PON_TRIGGER_PON1;
      irq_type = cfg_data ? 0x1 : 0x00; //0=level, 1=edge
      err_flag |= pm_comm_write_byte(pmic_device_index, PM_PON_OPTION_USB_CHG_REDGE_REG, irq_type);
      return err_flag;
      break;

   case PM_PON_OPTION_CBLPWR_FEDGE_PON :
      trigger = PM_PON_TRIGGER_CBLPWR;
      irq_type = cfg_data ? 0xFF : 0x00; //0=level, 1=edge
      polarity_high = 0x0;
      polarity_low = 0xFF;
      break;

   case PM_PON_OPTION_PON1_REDGE_PON :
      trigger = PM_PON_TRIGGER_PON1;
      irq_type = cfg_data ? 0xFF : 0x00; //0=level, 1=edge
      polarity_high = 0xFF;
      polarity_low = 0x0;
      break;

   case PM_PON_OPTION_KPDPWR_FEDGE_PON:
      trigger = PM_PON_TRIGGER_KPDPWR;
      irq_type = cfg_data ? 0xFF : 0x00; //0=level, 1=edge
      polarity_high = 0x0;
      polarity_low = 0xFF;
      break;

   default:
      trigger = PM_PON_TRIGGER_INVALID;
      break;
   }

   err_flag |= pm_pon_get_pon_info(pmic_device_index, &slave_id);

   if ((trigger != PM_PON_TRIGGER_INVALID) && (err_flag == PM_ERR_FLAG_SUCCESS) && (cfg_field != PM_PON_OPTION_USB_CHG_REDGE_PON))
   {
      err_flag |= pm_pon_target_get_pon_trigger_config(trigger, &trigger_config);

      if (trigger_config.pid != 0x00)
      {
         mask = trigger_config.trig_mask;

         //write to sdam configuration
         //1.high polarity 2. low_polarity 3.set type
         irq_type_reg_addr = (PON_TRIG_CFG_PID_ADDR + PON_TRIG_SET_TYPE_ADDR_INDEX) + (trigger_config.trig_index * EIGHT_BYTES);
         polarity_high_reg_addr = (PON_TRIG_CFG_PID_ADDR + PON_TRIG_POL_HIGH_ADDR_INDEX) + (trigger_config.trig_index * EIGHT_BYTES);
         polarity_low_reg_addr = (PON_TRIG_CFG_PID_ADDR + PON_TRIG_POL_LOW_ADDR_INDEX) + (trigger_config.trig_index * EIGHT_BYTES);

         err_flag |= pm_comm_write_byte_mask(slave_id, irq_type_reg_addr, mask, irq_type);
         err_flag |= pm_comm_write_byte_mask(slave_id, polarity_high_reg_addr, mask, polarity_high);
         err_flag |= pm_comm_write_byte_mask(slave_id, polarity_low_reg_addr, mask, polarity_low);

         //write to pmic irq registers
         //1.high polarity 2. low_polarity 3.set type
         //slave_id; pid*100+irq; mask

         irq_type_reg_addr = (trigger_config.pid * 0x100) + SET_TYPE_OFFSET;
         polarity_high_reg_addr = (trigger_config.pid * 0x100) + POLARITY_HIGH_OFFSET;
         polarity_low_reg_addr = (trigger_config.pid * 0x100) + POLARITY_LOW_OFFSET;

         slave_id = trigger_config.sid;
         err_flag |= pm_comm_write_byte_mask(slave_id, irq_type_reg_addr, mask, irq_type);
         err_flag |= pm_comm_write_byte_mask(slave_id, polarity_high_reg_addr, mask, polarity_high);
         err_flag |= pm_comm_write_byte_mask(slave_id, polarity_low_reg_addr, mask, polarity_low);

      }
   }

   return err_flag;
}


