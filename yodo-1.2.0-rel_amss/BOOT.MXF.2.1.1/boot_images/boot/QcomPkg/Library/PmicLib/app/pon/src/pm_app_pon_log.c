/*! \file pm_app_pon_log.c
*  
*  \brief Implementation file for PON APP level logger APIs.
*    
*  &copy; Copyright 2016-2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/
/*===================================================================
EDIT HISTORY FOR MODULE
 This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Date  2018/07/02 $ 
$Change  16554216 $

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/app/pon/src/pm_app_pon_log.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
01/10/17   aab     Updated PON logging Text
09/13/16   aab     Updated PON logging
08/03/16   akm     Creation
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_pon.h"
#include "pm_device.h"
#include "pm_app_pon.h"
#include "pmio_pon.h"
#include "pm_err_flags.h"
#include "device_info.h"
#include "hw_module_type.h"
#include "pm_config_target.h"
#include "pm_sbl_boot_target.h"
#include "pm_pon_target.h"
#include "pm_app_pon_log.h"
#include "pm_target_information.h"
#include "CoreVerify.h"
#include "pm_log_utils.h"
#include <string.h> 

#include "pm_dt_parser.h"

/*===========================================================================

                     Global Variables

===========================================================================*/
boolean g_fault_captured = FALSE;


typedef struct
{
  uint8 pon_reason1;
  uint8 pon_reason2;
  uint8 poff_reason1;
  uint8 poff_reason2;
  uint8 warm_reset_reason1;
  uint8 warm_reset_reason2;
  uint8 soft_reset_reason1;
  uint8 soft_reset_reason2;
}pm_reason_status_type;

typedef struct
{
  uint8 pon_reason1;
  uint8 reserved1;
  uint8 warm_reset_reason1;
  uint8 reserved2;
  uint8 on_reason;
  uint8 poff_reason1;
  uint8 reserved3;
  uint8 off_reason;
}pm_pon_gen2_reason_status_type;

typedef struct
{
  uint8 fault_reason1;
  uint8 fault_reason2;
  uint8 s3_reset_reason;
  uint8 soft_reset_reason1;
}pm_pon_gen2_fault_status_type;


enum
{
  PON_EVENT_LOG_LEVEL_MIN,
  PON_EVENT_LOG_LEVEL_VERBOSE,
  PON_EVENT_LOG_LEVEL_RAWDATA,
  PON_EVENT_LOG_LEVEL_MAX = 0x7F,
};

#define PON_POS_INVALID 0xFF
#define RESET_TYPE_COUNT 8

#define PON_EVENT_LOG_SIGNATURE 0x474F4C50
#define PON_EVENT_LOG_VERSION   0x01
/*===========================================================================

                   Function Prototypes

===========================================================================*/

static pm_err_flag_type pm_pon_parse_pon_pbs_log(void);
static pm_err_flag_type pm_get_fault_reason_string(pm_pon_event_type event, uint8 fault1, uint8 fault2, uint8 fault3, char* fault_string, uint8 fault_string_size);
static void pm_log_fault_reason(pm_pon_event_type event, uint8 fault1, uint8 fault2, uint8 fault3);
static void pm_log_fundamental_reset(pm_pon_log_type pon_log);
static void pm_log_pon_trigger(pm_pon_log_type log);

/*===========================================================================

                   API Implementation

===========================================================================*/
pm_err_flag_type 
pm_app_pon_get_all_pon_events(pm_pon_reason_events_data_type *pon_reason_events_ptr )
{
  
  pm_err_flag_type  err_flag = PM_ERR_FLAG_SUCCESS;
  pm_pon_log_type *pon_events_addr = NULL;
  uint16 pon_event_log_size = 0;   
  uint32 copy_count = 0; 
  uint8 state= 0;
  uint8 event= 0;
  uint8 byte1= 0;
  uint8 byte0= 0;
  uint32 pon_event = 0;
  err_flag = pm_pon_get_pon_events(&pon_events_addr, &pon_event_log_size);
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  
  pon_reason_events_ptr->signature = PON_EVENT_LOG_SIGNATURE;
  pon_reason_events_ptr->version =   PON_EVENT_LOG_VERSION;
  
  if(pon_event_log_size > PON_EVENT_DUMP_FILE_SIZE)
  {
    pon_event_log_size = PON_EVENT_DUMP_FILE_SIZE; // Copy only till the Size of Dump
  }
  for(copy_count = 0; copy_count < pon_event_log_size; copy_count++)
  {
    state = pon_events_addr->state;
    event = pon_events_addr->event;
    byte1 = pon_events_addr->byte1;
    byte0 = pon_events_addr->byte0;
    pon_event = (uint32)(byte0 << 24) | (uint32)(byte1 <<16) | (uint32)(event << 8) | (uint32)state ; 

    pon_reason_events_ptr->pon_rsn_hist_data[copy_count] = pon_event;
    pon_events_addr++;
  }
  
  return err_flag;
    
}

pm_err_flag_type
pm_log_pon_reasons(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_model_type pmic_model = PMIC_IS_INVALID;
  uint8 pmic_index = 0;
  uint8 sid_index = 0;
  uint32 pon_peripheral_index = 8;
  boolean fault_occurred = FALSE;
  uint64 fault_reasons = 0x00;
  peripheral_info_type pon_peripheral_info = {0};

  memset(&pon_peripheral_info, 0, sizeof(peripheral_info_type));
  pon_peripheral_info.base_address = pon_peripheral_index * 0x0100;

  //Check if there is a fault during last PON
  err_flag = pm_last_pon_find_state(PM_PON_PBS_STATE_FAULT, &fault_occurred);

  //Log PON reasons for all PMIC
  for(pmic_index = 0; pmic_index < PM_MAX_NUM_PMICS; pmic_index++)
  {
    pmic_model = pm_get_pmic_model(pmic_index);
    if((pmic_model != PMIC_IS_INVALID) && (pmic_model != PMIC_IS_UNKNOWN))
    {
      //Get PON perepheral type and perepheral sub type for each valid PMIC on target
      sid_index = pmic_index;
  
      pm_get_peripheral_info(sid_index, &pon_peripheral_info);

      if(pon_peripheral_info.peripheral_subtype < PM_HW_MODULE_PON_LV_PON_GEN2_PRIMARY)
      {
        continue;
      }

      if(fault_occurred)
      {
        fault_reasons = 0x00;
        err_flag |= pm_pon_get_fault_reasons(pmic_index, &fault_reasons);
        if(err_flag != PM_ERR_FLAG_SUCCESS)
        {
          return err_flag;
        }
        //Don't print useless Fault_N and RESTART_PON message
        if(fault_reasons & (~(uint64)((PMIO_PON_PBS_FAULT_REASON2_FAULT_N_BMSK | PMIO_PON_PBS_FAULT_REASON2_RESTART_PON_BMSK) << 8)))
        {
          pm_log_message("PM%d 0x%llx", pmic_index, (uint64)fault_reasons);
        }
      }
    }
  }

  sid_index = pm_get_primary_pmic_index();

  pm_get_peripheral_info(sid_index, &pon_peripheral_info);
  if(pon_peripheral_info.peripheral_subtype >= PM_HW_MODULE_PON_PBS_GEN3)
  {
    err_flag |= pm_pon_parse_pon_pbs_log();
  }

  return err_flag;
}

static pm_err_flag_type pm_pon_parse_pon_pbs_log()
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  // default FALSE. Only when we need to debug some complicate case, we set it TRUE in engineer build.
  boolean verbose_pon_logging = FALSE;
  pm_pon_log_type pon_log = {0};
  uint16 pon_dataset = 0;
  int start_index = 0, end_index = 0, last_valid_index = 0;
  int next_pon_success_index = 0;
  int warm_reset_count = 0;
  pm_dt_sw_config *sw_config_dt = NULL;
  
  sw_config_dt = pm_dt_get_node(PMIC_DT_NODE_PM_SW_CONFIG);
  if((sw_config_dt != NULL) && (sw_config_dt->verbose != PON_EVENT_LOG_LEVEL_MIN))
  {
    verbose_pon_logging = TRUE;
  }

  char *reset_type[RESET_TYPE_COUNT] = {NULL, "Warm Reset", NULL, NULL, "Shutdown", NULL, NULL, "Hard Reset"};

  err_flag |= pm_get_last_valid_log_index(&last_valid_index);
  err_flag |= pm_get_next_event_index(0, PM_PON_EVENT_PON_SUCCESS, &start_index);
  if((last_valid_index < 0) || (0 != start_index))
  {
    // we expect the log is not empty and the first log is PON_SUCCESS. otherwise just return
    pm_log_message("INVALID LOG");
    return err_flag;
  }

  // Usualy we only output log for last PON log. For warm reset case, we output the logs for all the 3 reset
  do
  {
    // start_index point to the index of PON_SUCCESS
    err_flag |= pm_get_next_event_index(start_index + 1, PM_PON_EVENT_PON_SUCCESS, &next_pon_success_index);
    if(next_pon_success_index < 0)
    {
      // no more PON_SUCCESS log
      end_index = last_valid_index;
    }
    else // next_pon_success_index >= 0. Found the next PON_SUCCESS event
    {
      if(next_pon_success_index > last_valid_index)
      {
        // shouldn't hit here
        break;
      }

      if(next_pon_success_index <= start_index + 1)  // Can this if removed?
      {
        // Do nothing if the rest log is just PON_SUCCESS
        break;
      }
      end_index = next_pon_success_index - 1;
    }

    // Clear warm_reset_count. if it it non-zero, it can be retrieved in log
    warm_reset_count = 0;

    while(end_index >= start_index)
    {
      // parsing log one by one here
      if(pm_get_a_pon_log(end_index, &pon_log) != PM_ERR_FLAG_SUCCESS)
      {
        // end of parsing
        return err_flag;
      }

      pon_dataset = (pon_log.byte1 << 8) | pon_log.byte0;

      switch(pon_log.event)
      {
      case PM_PON_EVENT_PON_TRIGGER:
      case PM_PON_EVENT_RESET_TRIGGER:
        pm_log_pon_trigger(pon_log);
        break;
      case PM_PON_EVENT_XVLO_CHECK_COMPLETE:
        if(verbose_pon_logging)
        {
          pm_log_message("xVLO:0x%04X", pon_dataset);
        }
        break;
      case PM_PON_EVENT_RESET_TYPE:
        // 1: Warm Reset
        // 4: Shut Down
        // 7: Hard Reset
        if((pon_log.byte0 < RESET_TYPE_COUNT) && (NULL != reset_type[pon_log.byte0]))
        {
          pm_log_message("Reset Type: %s", reset_type[pon_log.byte0]);
        }
        else
        {
          // Usually not hit here
          pm_log_message("Unexpected reset type: 0x%02X", pon_log.byte0);
        }
        break;
      case PM_PON_EVENT_WARM_RESET_COUNT:
        // Byte0: warm reset count
        if(pon_log.byte0 != 0)
        {
          pm_log_message("Warm reset count:0x%x", pon_log.byte0);
          warm_reset_count = pon_log.byte0;
        }
        break;
      case PM_PON_EVENT_PBS_FAULT:
        pm_log_message("PBS fault PC: 0X%04X", pon_dataset);
        break;
      case PM_PON_EVENT_FUNDAMENTAL_RESET:
        pm_log_fundamental_reset(pon_log);
        break;
      case PM_PON_EVENT_FAULT_REASON_PART2:
        pm_log_fault_reason(pon_log.event, 0, 0, pon_log.byte0);
        g_fault_captured = g_fault_captured || (pon_log.byte0 != 0);
        break;
      case PM_PON_EVENT_FAULT_REASON_PART1:
      case PM_PON_EVENT_FAULT_PMIC_A:
      case PM_PON_EVENT_FAULT_PMIC_B:
      case PM_PON_EVENT_FAULT_PMIC_C:
      case PM_PON_EVENT_FAULT_PMIC_D:
      case PM_PON_EVENT_FAULT_PMIC_E:
      case PM_PON_EVENT_FAULT_PMIC_F:
      case PM_PON_EVENT_FAULT_PMIC_G:
      case PM_PON_EVENT_FAULT_PMIC_H:
      case PM_PON_EVENT_FAULT_PMIC_I:
      case PM_PON_EVENT_FAULT_PMIC_J:
      case PM_PON_EVENT_FAULT_PMIC_K:
      case PM_PON_EVENT_FAULT_PMIC_L:
      case PM_PON_EVENT_FAULT_PMIC_M:
      case PM_PON_EVENT_FAULT_PMIC_N:
        pm_log_fault_reason(pon_log.event, pon_log.byte0, pon_log.byte1, 0);
        g_fault_captured = g_fault_captured || (pon_log.byte0 != 0) || ((pon_log.byte1 & ~PMIO_PON_PBS_FAULT_REASON2_RESTART_PON_BMSK)!= 0);
        break;
      case PM_PON_EVENT_PON_SUCCESS:
        if(verbose_pon_logging)
        {
          pm_log_message("PON success. State: 0x%02X, data: 0x%04X", pon_log.state, pon_dataset);
        }
        break;
      case PM_PON_EVENT_PSHOLD_POLL:
        if(verbose_pon_logging)
        {
          pm_log_message("PS_HOLD %s. state: 0x%02X, data: 0x%04X", (pon_log.state == 0x01 ? "PON" : (pon_log.state == 0x07 ? "warm reset" : "unknown")),
                          pon_log.state, pon_dataset);
        }
        break;
      case PM_PON_EVENT_OTP_COPY:
        if(verbose_pon_logging)
        {
          pm_log_message("PM_PON_EVENT_OTP_COPY");
        }
        break;
      case PM_PON_EVENT_PON_SEQUENCE_START:
        if(verbose_pon_logging)
        {
          pm_log_message("Begin PON. state: 0x%02X, data: 0x%04X", pon_log.state, pon_dataset);
        }
        break;
      case PM_PON_EVENT_TRIM_COMPLETE:
        if(verbose_pon_logging)
        {
          pm_log_message("Trim copy: 0x%04X", pon_dataset);
        }
        break;
      case PM_PON_EVENT_PMIC_CHECK_COMPLETE:
        if(verbose_pon_logging)
        {
          pm_log_message("PMIC found on bus: 0x%04X", pon_dataset);
        }
        break;
      default:
        pm_log_message("State 0x%02X Event 0x%02X. Data: 0x%04X", pon_log.state, pon_log.event, pon_dataset);
        break;
      }

      --end_index;
    }

    start_index = next_pon_success_index;
  } while((warm_reset_count > 1) && (start_index < (MAX_PON_EVENT_PER_SDAM - 1)));

  return err_flag;
}

void pm_pon_output_log_buffer()
{
  int index = 0;
  pm_pon_log_type log = {0};
  pm_dt_sw_config *sw_config_dt = pm_dt_get_node(PMIC_DT_NODE_PM_SW_CONFIG);

  if(g_fault_captured ||
      ((sw_config_dt != NULL) && (sw_config_dt->verbose == PON_EVENT_LOG_LEVEL_MAX)))
  {
    while(PM_ERR_FLAG_SUCCESS == pm_get_a_pon_log(index, &log))
    {
      pm_log_message("[Log0x%02d]:State: 0x%02X Event: 0x%02X Data: 0x%04X",
                    index, log.state, log.event, (log.byte1 << 8) | log.byte0);
      ++index;
    }
  }
}


// GP_FAULT2: PBS1 Watch Dog. fault_reason1[2]
// GP_FAULT3: PBS2 Watch Dog. fault_reason1[3]
// GP_FAULT4: PBS3 Watch Dog. fault_reason3[0]
#define IDX_PBS1_WD (2)
#define IDX_PBS2_WD (3)
#define IDX_PBS3_WD (0)
#define IDX_PBS_NACK (5)

#define GP_FAULT_OFFSET (4)

// 0x1234 plus '\0', need 7 bytes. pad to 8 bytes for alignment
#define SIZE_UINT16 (8)
#define SIZE_NACK_REASON (32)
// We may need to move this API to target folder as GP_FAULT is possible different between target.
static pm_err_flag_type pm_get_fault_reason_string(pm_pon_event_type event, uint8 fault1, uint8 fault2, uint8 fault3, char* fault_string, uint8 fault_string_size)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  char* fault_reason1[8] = {"GP_FAULT0", "GP_FAULT1", "GP_FAULT2", "GP_FAULT3", "MGB_FAULT", "OVLO", "UVLO", "AVDD_RB"};
  char* fault_reason2[8] = {"", "", "PMIC_RB", "FAULT_N", "FAULT_WATCHDOG_TO", "PBS_NACK", "RESTART_PON", "OTST3"};
//  char* fault_reason3[8] = {"GP_FAULT4", "GP_FAULT5", "GP_FAULT6", "GP_FAULT7", "GP_FAULT8", "GP_FAULT9", "GP_FAULT10", "GP_FAULT11" };

  char* gp_fault_primary_pmic[] = {"INTR_WDOG", "PBUS_FAULT", "PBS1_WDOG", "PBS2_WDOG", "PBS3_WDOG", 
                            "SPMI1_SLAVE_WDOG", "SPMI2_SLAVE_WDOG", "XO_HALT", " ", " ", " ", " " };
  char* gp_fault_follower_pmic[] = {"MISC_VREG_OCP", "PBUS FAULT", "SPMI1_SLAVE_WDOG", "INTR_WDOG", "PBS_WDOG", " ", " ", " ", " ", " " , " ", " "};

  boolean string_not_empty = FALSE;
  uint8 index = 0;

  if((fault1 == 0 && fault2 == 0 && fault3 == 0) || (NULL == fault_string) || (fault_string_size == 0))
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  if(fault1 != 0)
  {
    for(index = 0; index < 8; ++index)
    {
      if((fault1 & (1 << index)) != 0)
      {
        if(TRUE == string_not_empty)
        {
          strlcat(fault_string, "|", fault_string_size);
        }
        else
        {
          string_not_empty = TRUE;
        }

        if(index < 4)//in fault reason1 till bit position 3, fault is a type of gp_fault
        {
          if(event == PM_PON_EVENT_FAULT_REASON_PART1)// for PMK PMIC
          {
            strlcat(fault_string, gp_fault_primary_pmic[index], fault_string_size);
            if((IDX_PBS1_WD == index) || (IDX_PBS2_WD == index))
            {
              char fault_pc[SIZE_UINT16] = {0};
              pm_pon_get_pbs_fault_pc(fault_pc, sizeof(fault_pc) / sizeof(char));
              strlcat(fault_string, ". PC: ", fault_string_size);
              strlcat(fault_string, fault_pc, fault_string_size);

              char fault_ra_pc[SIZE_UINT16] = {0};
              pm_pon_get_pbs_fault_return_address_pc(fault_ra_pc, sizeof(fault_ra_pc) / sizeof(char));
              strlcat(fault_string, ", RA: ", fault_string_size);
              strlcat(fault_string, fault_ra_pc, fault_string_size);
            }
          }
          else
          {
            // For flollwer PMICs
            strlcat(fault_string, gp_fault_follower_pmic[index], fault_string_size);
          }
        }
        else  // index >= 4
        {
          strlcat(fault_string, fault_reason1[index], fault_string_size); 
        }
      }
    }
  }

  if(fault2 != 0)
  {
    if((fault2 & 0x3) != 0)
    {
      pm_log_message("UNEXPECTED fault reason2: 0x%02X", fault2);
    }

    for(index = 2; index < 8; ++index)
    {
      if((fault2 & (1 << index)) != 0)
      {
        if(TRUE == string_not_empty)
        {
          strlcat(fault_string, "|", fault_string_size);
        }
        else
        {
          string_not_empty = TRUE;
        }

        strlcat(fault_string, fault_reason2[index], fault_string_size);
        if(IDX_PBS_NACK == index)
        {
          // Out put the PBS Nack reason
          char nack_reason[SIZE_NACK_REASON] = {0};

          pm_pon_get_pbs_nack_reason(nack_reason, sizeof(nack_reason) / sizeof(char));
          strlcat(fault_string, ": ", fault_string_size);
          strlcat(fault_string, nack_reason, fault_string_size);
        }
      }
    }
  }

  if((fault3 != 0) && (event == PM_PON_EVENT_FAULT_REASON_PART2))
  {
    for(index = 0; index < 8; ++index)
    {
      if((fault3 & (1 << index)) != 0)
      {
        if(TRUE == string_not_empty)
        {
          strlcat(fault_string, "|", fault_string_size);
        }
        else
        {
          string_not_empty = TRUE;
        }

         // adding offset 4 , as gp_fault 0-3 are present in fault reason1.
        strlcat(fault_string, gp_fault_primary_pmic[index + GP_FAULT_OFFSET], fault_string_size);
        if(IDX_PBS3_WD == index)
        {
          char fault_pc[SIZE_UINT16] = {0};
          pm_pon_get_pbs_fault_pc(fault_pc, sizeof(fault_pc) / sizeof(char));
          strlcat(fault_string, ". PC: ", fault_string_size);
          strlcat(fault_string, fault_pc, fault_string_size);
          
          char fault_ra_pc[SIZE_UINT16] = {0};
          pm_pon_get_pbs_fault_return_address_pc(fault_ra_pc, sizeof(fault_ra_pc) / sizeof(char));
          strlcat(fault_string, ", RA: ", fault_string_size);
          strlcat(fault_string, fault_ra_pc, fault_string_size);
        }
      }
    }
  }

  return err_flag;
}

static void pm_log_fundamental_reset(pm_pon_log_type pon_log)
{
  boolean xvdd_reset = FALSE;
  char* s3_reason = NULL;
  uint8 state = pon_log.state;
  uint8 pon_pbl_status = pon_log.byte1;
  uint8 s3_reset_reason = pon_log.byte0;

  if(pon_pbl_status & 0x80)
  {
    xvdd_reset = TRUE;
  }

  s3_reset_reason = s3_reset_reason & 0xF0; // Only bit[7:4] are valid
  if((state != 0)
    || (((pon_pbl_status & 0xC0) == 0) && (s3_reset_reason != 0))
    || ((s3_reason != 0) && (0 != (s3_reset_reason & (s3_reset_reason - 1)))))
  {
    // state == 0 means fault
    // if s3 is non-zero, we expect either xvdd_reset or dvdd_reset is set. Actually both should be set.
    // if s3 reason is non-zero, we expect only one bit is set
    pm_log_message("unexpected fundamental reset log. state: 0x%02X, pon_pbl_status: 0x%02X, s3_reset_reason: 0x%02X", state, pon_pbl_status, s3_reset_reason);
  }

  // bit7: KPDPWR_ANDOR_RESIN
  // bit6: PBS_NACK
  // bit5: PBS_WATCHDOG_TO
  // bit4: FAULT_N
  if((s3_reset_reason & 0x80) != 0)
  {
    s3_reason = "keypad S3";
  }
  else if((s3_reset_reason & 0x40) != 0)
  {
    s3_reason = "PBS_NACK S3";
  }
  else if((s3_reset_reason & 0x20) != 0)
  {
    s3_reason = "FAULT WD TO S3";
  }
  else if((s3_reset_reason & 0x10) != 0)
  {
    s3_reason = "FAULT_N S3";
  }

  s3_reset_reason = s3_reset_reason & 0xF0; // only bit[7:4] are valid.
  if((pon_pbl_status & 0xC0) != 0)
  {
    pm_log_message("%s reset%s%s", (xvdd_reset ? "xVdd" : "dVdd"), 
      (NULL != s3_reason) ? ". " : "", (NULL != s3_reason ? s3_reason : ""));
  }
}

static void pm_log_pon_trigger(pm_pon_log_type log)
{
  uint16 pon_dataset = (log.byte1 << 8) | log.byte0;
  uint8 sid = (pon_dataset & 0xF000) >> 12;
  uint8 pid = (pon_dataset & 0x0FF0) >> 4;
  uint8 trigger = pon_dataset & 0x7;
  pm_pon_event_type event = log.event;
  char* reset_type = NULL;
  char* pon_trigger_string = NULL;

  if(PM_PON_EVENT_PON_TRIGGER == event)
  {
    reset_type = "PON";
  }
  else if(PM_PON_EVENT_RESET_TRIGGER == event)
  {
    reset_type = "Reset";
  }
  else
  {
    // Do nothing for unexpected state type
    return;
  }

  switch(pon_dataset)
  {
  case PON_PBS_KEYPD_PWR_N_S2_RSN:
    pon_trigger_string = "PWR key S2";
    break;
  case PON_PBS_RESIN_N_S2_RSN:
    pon_trigger_string = "Resin S2";
    break;
  case PON_PBS_KPDPWR_AND_RESIN_RSN:
    pon_trigger_string = "PWR & Resin S2";
    break;
  case PON_PBS_PMIC_WD_RSN:
    pon_trigger_string = "WDog S2";
    break;
  case PON_PBS_PS_HOLD_RSN:
    pon_trigger_string = "PSHOLD";
    break;
  case PON_PBS_SW_RST_RSN:
    pon_trigger_string = "SW Reset";
    break;
  case PON_PBS_RESIN_N_DEB_RSN:
    pon_trigger_string = "Resin DEB";
    break;
  case PON_PBS_KEYPD_PWR_N_RSN:
    pon_trigger_string = "PWR key DEB";
    break;
  case PON_PBS_SMPL_RSN:
    pon_trigger_string = "SMPL";
    break;
  case PON_PBS_PON1_RSN:
    pon_trigger_string = "PON1";
    break;
  case PON_PBS_CBLPWR_RSN:
    pon_trigger_string = "CBLPWR";
    break;
  case PON_PBS_SYS_OK_RSN:
    pon_trigger_string = "SYSOK";
    break;
  case PON_PBS_RTC_ALARM_RSN:
    pon_trigger_string = "RTC";
    break;
  default:
    if(PM_ERR_FLAG_SUCCESS != pm_get_target_specific_pon_trig_string(pon_dataset, &pon_trigger_string))
    {
      pon_trigger_string = NULL;
    }
    break;
  }

  if(NULL != pon_trigger_string)
  {
    if(pon_dataset != PON_PBS_SW_RST_RSN) // ignore useless SW Reset message
    {
      pm_log_message("%s by %s", reset_type, pon_trigger_string);
    }
  }
  else
  {
    pm_log_message("%s. trigger SID:0x%X, PID:0x%X, INT:0x%X", reset_type, sid, pid, trigger);
  }
}

static void pm_log_fault_reason(pm_pon_event_type event, uint8 fault1, uint8 fault2, uint8 fault3)
{
#define FAULT_REASONS_SIZE 64
#define FAULT_PMIC_NAME_SIZE 16
  char fault_reasons[FAULT_REASONS_SIZE] = {0};
  char fault_pmic_name[FAULT_PMIC_NAME_SIZE] = {0};

  //Don't print useless Fault_N and RESTART_PON message, so clear them
  fault2 &= ~(PMIO_PON_PBS_FAULT_REASON2_FAULT_N_BMSK | PMIO_PON_PBS_FAULT_REASON2_RESTART_PON_BMSK);

  if(PM_ERR_FLAG_SUCCESS == pm_get_fault_reason_string(event, fault1, fault2, fault3, fault_reasons, FAULT_REASONS_SIZE)
    && (PM_ERR_FLAG_SUCCESS == pm_pon_get_fault_pmic_string(event, fault_pmic_name, FAULT_PMIC_NAME_SIZE)))
  {
    pm_log_message("%s on %s", fault_reasons, fault_pmic_name);
  }
}

