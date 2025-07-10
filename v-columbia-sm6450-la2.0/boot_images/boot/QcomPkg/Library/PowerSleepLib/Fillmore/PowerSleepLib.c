/******************************************************************//**
 * @file PowerSleepLib.c
 *
 * @brief PowerSleepLib functions
 *
 * Copyright (c) 2017-2018, 2020, 2022 by Qualcomm Technologies, Inc.
 * All Rights Reserved.
 *
 *********************************************************************/
/*=======================================================================
                        Edit History

when       who     what, where, why
--------   ----    --------------------------------------------------- 
2020-06-28 am      Moved LPM callback invokation to SystemSleepLib
========================================================================*/

#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/QcomBaseLib.h>
#include <Library/ProcAsmLib.h>
#include <Library/TimerLib.h>
#include <Library/BaseLib.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <Library/rpmh_client.h>
#include <Library/PowerSleepLib.h>
#include <Library/SysSleepLib.h>
#include "PowerSleepLibInternal.h"
#include "PowerSleepTargetLib.h"
#include "PowerSleepCb.h"
#include "rsc_hwio.h"
#include "CoreVerify.h"

//SchedulerLib APIs
#include "list.h"
#include "interrupts.h"
#include "kernel/mutex.h"
#include "kernel/wait.h"

//--------------------------------------------------------------------------
// Scheduler Lib Declarations 
//--------------------------------------------------------------------------
#define BACKUP_SYSTEM_CONTEXT    0
#define RESTORE_SYSTEM_CONTEXT   1

UINTN BackupRestoreSystemCtxt (UINTN Operation);
extern uint32_t mpcore_get_curr_cpu(void);
extern uint32_t mpcore_get_active_mask(void);
extern mutex_t* init_mutex(uint64_t id);
extern UINT64 ReadQTimerPct (VOID);

//--------------------------------------------------------------------------
// Sleep Stats Defines 
//--------------------------------------------------------------------------
typedef enum
{
  PSLEEP_CORE_ACTIVE, //core is awake
  PSLEEP_CORE_C1,     //core is clock gated
  PSLEEP_CORE_C2,     //core is asleep but logic stays on. L1/L2 at retention
  PSLEEP_CORE_C3,     //core is in power collapse, prevent PLLs and rails from turning off
  PSLEEP_CORE_C4,     //core is in power collapse, allow PLLs and rails to turn off. 
                      //C4 is required on all cores in order to enter system D4
  PSLEEP_CORE_C4D4,   //Only applies to the last core to go down. 
  PSLEEP_CORE_OFF,    //core hasn't been brought up or is hotplugged
  PSLEEP_CORE_MAX,
} power_sleep_core_state;

typedef struct
{
  uint32 *dict_addr;	
  uint32 *base_addr;	
  sleep_stats_t lpm[POWER_SLEEP_STATS_NUM_STATS];
  boolean init;
} power_sleep_stats_t;

sleep_stats_t psleep_lpm_stats_copy[POWER_SLEEP_STATS_NUM_STATS];
static power_sleep_stats_t psleep_stats;

#define SLEEP_STATS_LOOKUP_OFFSET 4

//--------------------------------------------------------------------------
// RSC Defines 
//--------------------------------------------------------------------------
//Wake TCS 5
#define WAKE0_TCS 5
#define WAKE1_TCS 6

//Sleep TCS 2
#define SLEEP_TCS_START 3
#define WAKE_TCS_START 5
#define TCS_END 7
#define SLEEP0_TCS 3
#define SLEEP1_TCS 4

//HLOS DRV 2
#define HLOS_DRV 2

//Static backoff for RSC wakeup
#define RSC_BACKOFF 0x9600 //2mS in 19.2
#define LATE_WAKEUP_THRESHOLD 0x9600 //2mS in 19.2
#define MIN_C4D4_SLEEP_TIME 0x2EE00 //10mS in 19.2
#define MIN_C4_SLEEP_TIME 0x4B00 //1mS in 19.2

//--------------------------------------------------------------------------
// Globals 
//--------------------------------------------------------------------------
struct
{
  boolean                initialized;
  mutex_t                *lock;  //lock for configuring RSC info/globals
  uint32                 *dbg_state; //debug state for each core
  uint32                 num_cores_supported; //static value for number of supported cores (in config data) 
  power_sleep_core_state *core_states; //core states from psleep perspective
  uint32                 core_state_bmsk; //bmsk used to manipulate states
  uint32                 sched_cores_active; //cores being used from the scheduler's POV
  uint64                 wakeup_time; //wakeup time for c4d4
  uint32                 deepest_sleep_mode; //deepest sleep mode supported. Used in case CX collapse/AOSS sleep isn't supported
  rpmh_command_set_t     rpmh_sleep_config[WAKE_TCS_START - SLEEP_TCS_START];  //sleep set
  rpmh_command_set_t     rpmh_wake_config[TCS_END - WAKE_TCS_START]; //wake set
  boolean                cmd_sets_dirty; //Used to track if we've cleaned up from a prior cycle or not
}psleep;

//globals to track the index of the last inserted command into a TCS for each set
uint32 last_cmd_index[2] = {0, 0};
uint32 last_cmd_tcs[2] = {SLEEP_TCS_START, WAKE_TCS_START};

//lookup table for default sleep votes for ARC, VRM, BCM
uint32 default_sleep_votes[3] = {0, 0, 0x40000000};

//translation from address to default sleep vote
#define DEFAULT_SLEEP_DATA(address) default_sleep_votes[((address >> 16) - 3)]

#define PWR_SLEEP_LOCK    STR_OBJECT_ID('P','W','R','_','S','L','P',0)

#define PSLEEP_LOG_0(a)             DEBUG((EFI_D_WARN, a)) 
#define PSLEEP_LOG_1(a, b)          DEBUG((EFI_D_WARN, a, b)) 
#define PSLEEP_LOG_2(a, b, c)       DEBUG((EFI_D_WARN, a, b, c)) 
#define PSLEEP_LOG_3(a, b, c, d)    DEBUG((EFI_D_WARN, a, b, c, d)) 
#define PSLEEP_LOG_4(a, b, c, d, e) DEBUG((EFI_D_WARN, a, b, c, d, e)) 

//--------------------------------------------------------------------------
// PSCI Defines 
//--------------------------------------------------------------------------
extern int sleep_psci_call(long arg0, long arg1, long arg2, long arg3);

//power state ID encoding
//
//C4 + D4 + SYSTEM LPMs
#define CPU_C4      0x40000004
#define L3_D4       0x40
#define RSC_E2      0x200
#define PDC_F1      0x1000
#define PDC_F2      0x2000
#define PDC_F3      0x3000
#define PDC_F4      0x4000
#define SYS_CACHE   0x8000
#define POWER_DOWN  0x41000000

#define SLEEP_MODE_C4D4_CXSD  (CPU_C4 | L3_D4 | RSC_E2 | PDC_F4 | SYS_CACHE | POWER_DOWN)
#define SLEEP_MODE_C4D4_CXRET (CPU_C4 | L3_D4 | RSC_E2 | PDC_F3 | SYS_CACHE | POWER_DOWN)

#define SLEEP_MODE_C4 CPU_C4

#define POWER_SLEEP_PSCI_CPU_SUSPEND 0xC4000001

#define POWER_SLEEP_PSCI_CPU_SET_SUSPEND_MODE 0x8400000F

#define OS_INITIATED_MODE 0x1

//--------------------------------------------------------------------------
// Functions 
//--------------------------------------------------------------------------
//

/**
 * <!-- rsc_check_for_resource -->
 *
 * @brief Helper function to check if the given resource is already in the RSC (and therefore our global config)
 *
 * @param address : The resource to check
 * @param set     : The set to check
 *
 * @return TRUE if the resource is already configured in the RSC, FALSE otherwise
 */
boolean rsc_check_for_resource(uint32 address, rpmh_set_enum set)
{
  int set_start = (set == RPMH_SET_SLEEP) ? SLEEP_TCS_START : WAKE_TCS_START;
  int set_end = (set == RPMH_SET_SLEEP) ? WAKE_TCS_START : TCS_END;
  rpmh_command_set_t *cmd_set = (set == RPMH_SET_SLEEP) ? psleep.rpmh_sleep_config : psleep.rpmh_wake_config;
  //pull the sleep config from the RSC
  for(int tcs_id = set_start; tcs_id < set_end; tcs_id++)
  {
    uint32 index = tcs_id - set_start;
    for(int cmd = 0; cmd < cmd_set[index].num_commands; cmd++)
    {
      if(address == cmd_set[index].commands[cmd].address)
      {
        return TRUE;
      }
    } 
  }

  return FALSE;
}

/**
 * <!-- increment_cmd_index -->
 *
 * @brief Helper function to increment the global command index for the given set. This is used
 *        to determine the next open command in a given TCS for a particular set. This must be 
 *        called from a locked context  
 *
 * @param set : The set on which to increment the global command index
 */
static void increment_cmd_index(rpmh_set_enum set)
{
  //update our global command indexes
  CORE_VERIFY(set > RPMH_SET_ACTIVE);
  last_cmd_index[set - 1]++;              
  if(last_cmd_index[set -1] == IMAGE_TCS_SIZE)
  {
    last_cmd_tcs[set - 1]++;              
    last_cmd_index[set - 1] = 0;              
  }		    
}


/**
 * <!-- rsc_config_cmd -->
 *
 * @brief Helper function to configure the RSC with the given command. Must be called from a locked context
 *
 * @param ccommand : The command to populate into the TCS
 * @param set      : The set associated with the command. Used to determine which TCS to configure
 */
void rsc_config_cmd(rpmh_command_t *command, rpmh_set_enum set)
{
  CORE_VERIFY(set > RPMH_SET_ACTIVE);
  uint32 tcs_id = last_cmd_tcs[set - 1];	
  uint32 cmd_id = last_cmd_index[set - 1];
  uint32 cmd_en_bmsk = HWIO_INFI(APSS_RSC_RSCC_TCSm_DRV2_CMD_ENABLE, tcs_id, INDIVIDUAL_CMD_ENABLE_MASK);  

  //add a new request
  cmd_en_bmsk |= (1 << cmd_id);  
  HWIO_OUTFI2(APSS_RSC_RSCC_TCSm_CMDn_DRV2_MSGID, tcs_id, cmd_id, READ_OR_WRITE, 1);  
  HWIO_OUTFI2(APSS_RSC_RSCC_TCSm_CMDn_DRV2_MSGID, tcs_id, cmd_id, RES_REQ, command->completion);  
  HWIO_OUTFI2(APSS_RSC_RSCC_TCSm_CMDn_DRV2_MSGID, tcs_id, cmd_id, MSG_LENGTH, 8);  
  HWIO_OUTI2(APSS_RSC_RSCC_TCSm_CMDn_DRV2_ADDR, tcs_id, cmd_id, command->address);  
  HWIO_OUTI2(APSS_RSC_RSCC_TCSm_CMDn_DRV2_DATA, tcs_id, cmd_id, command->data);  


  //enable commands in this TCS
  HWIO_OUTFI(APSS_RSC_RSCC_TCSm_DRV2_CMD_ENABLE, tcs_id, INDIVIDUAL_CMD_ENABLE_MASK, cmd_en_bmsk);  

  increment_cmd_index(set);

}

/**
 * <!-- rsc_config_set -->
 *
 * @brief Helper function to configure the RSC with the given command set 
 *
 * @param tcs_id  : The TCS to configure
 * @param cmd_set : The command set to populate into the TCS
 */
void rsc_config_set(rpmh_command_set_t *cmd_set)
{
  //wake set: If command isn't already in the wake set, put it there
  //
  //sleep set: If command isn't already in the sleep set, put it there
  //           If there's a command thats in the wake set thats not in the sleep set, add a sleep set command

  CORE_VERIFY(cmd_set->num_commands <= IMAGE_TCS_SIZE);	

  //write the command specific details for wake
  for(int i = 0; i < cmd_set->num_commands; i++)
  {
    rpmh_command_t *cmd = &(cmd_set->commands[i]);	  
    if(!rsc_check_for_resource(cmd->address, cmd_set->set))
    {
      rsc_config_cmd(cmd, cmd_set->set);   
    }
  }    
}

/**
 * <!-- rsc_pull_rpmh_config -->
 *
 * @brief Helper function to configure the RSC with the given command set 
 *
 * @param tcs_id  : The TCS to configure
 * @param cmd_set : The command set to populate into the TCS
 */
//static
void rsc_pull_rpmh_config(void)
{
  int cmd = 0;
  uint32 cmd_en_bmsk = 0;

  for(rpmh_set_enum set = RPMH_SET_SLEEP; set <= RPMH_SET_WAKE; set++)
  {
    int set_start = (set == RPMH_SET_SLEEP) ? SLEEP_TCS_START : WAKE_TCS_START;
    int set_end = (set == RPMH_SET_SLEEP) ? WAKE_TCS_START : TCS_END;
    rpmh_command_set_t *cmd_set = (set == RPMH_SET_SLEEP) ? psleep.rpmh_sleep_config : psleep.rpmh_wake_config;
    //pull the sleep config from the RSC
    for(int tcs_id = set_start; tcs_id < set_end; tcs_id++)
    {
      uint32 index = tcs_id - set_start;
      cmd_set[index].num_commands = 0;
      cmd_set[index].set = set;
      cmd_en_bmsk = HWIO_INFI(APSS_RSC_RSCC_TCSm_DRV2_CMD_ENABLE, tcs_id, INDIVIDUAL_CMD_ENABLE_MASK);  
      cmd = 0;
      while((cmd_en_bmsk != 0) && (cmd < IMAGE_TCS_SIZE))
      {
        if(cmd_en_bmsk & (1 << cmd))
        {
          //found an enabled command. Save it locally		
          cmd_set[index].num_commands++;
          uint32 address = HWIO_INI2(APSS_RSC_RSCC_TCSm_CMDn_DRV2_ADDR, tcs_id, cmd);  
          cmd_set[index].commands[cmd].address = address;  
          cmd_set[index].commands[cmd].data = HWIO_INI2(APSS_RSC_RSCC_TCSm_CMDn_DRV2_DATA, tcs_id, cmd);  
          cmd_set[index].commands[cmd].completion = (boolean) HWIO_INFI2(APSS_RSC_RSCC_TCSm_CMDn_DRV2_MSGID, tcs_id, cmd, RES_REQ);  
          cmd_en_bmsk &= (~(1 << cmd));
          cmd++;


          //update our global command indexes
          increment_cmd_index(set);

          if((set == RPMH_SET_WAKE) && (!rsc_check_for_resource(address, RPMH_SET_SLEEP)))
          {
            //if this vote is in wake but not in sleep, add a sleep vote
            //note: last_cmd_tcs is the actual command index in hardware. We are using this to index into 
            //       our local array, so we need to back off the sleep_tcs_start amount
            rpmh_command_set_t *sleep_cmd_set = &(psleep.rpmh_sleep_config[last_cmd_tcs[RPMH_SET_SLEEP - 1] - SLEEP_TCS_START]);
            rpmh_command_t *sleep_cmd = &(sleep_cmd_set->commands[last_cmd_index[RPMH_SET_SLEEP -1]]);

            //add this to our structure of RPMh votes
            sleep_cmd->address = address;
            sleep_cmd->data = DEFAULT_SLEEP_DATA(address);
            sleep_cmd->completion = 0;
            sleep_cmd_set->num_commands++;
            CORE_VERIFY(sleep_cmd_set->num_commands <= IMAGE_TCS_SIZE);

            //add this to the actual RSC as well. Note that this will increment the global counters
            rsc_config_cmd(sleep_cmd, RPMH_SET_SLEEP);
          }
        }
      }
    }
  }
}

/**
 * <!-- rsc_clean_up -->
 *
 * @brief Clears out the rsc from a prior sleep cycle 
 */
void rsc_clean_up(void)
{
  //disable commands in the TCSs 
  for(int tcs_id = SLEEP_TCS_START; tcs_id < TCS_END; tcs_id++)
  {
    HWIO_OUTFI(APSS_RSC_RSCC_TCSm_DRV2_CMD_ENABLE, tcs_id, INDIVIDUAL_CMD_ENABLE_MASK, 0);  
  }  

  //reset our counters
  last_cmd_index[RPMH_SET_SLEEP - 1] = 0;
  last_cmd_index[RPMH_SET_WAKE - 1] = 0;
  last_cmd_tcs[RPMH_SET_SLEEP - 1] = SLEEP_TCS_START;
  last_cmd_tcs[RPMH_SET_WAKE - 1] = WAKE_TCS_START;

  psleep.cmd_sets_dirty = FALSE;	
}

/**
 * <!-- rsc_config_tcs_contents -->
 *
 * @brief Populate the TCS with the sleep/wake config data 
 */
//static
void rsc_config_tcs_contents(void)
{
  if(psleep.cmd_sets_dirty)
  {
    //in case we managed to get back into C4D4 without cleaning up, clean up from the last cycle	  
    rsc_clean_up();
  }	  
  psleep.cmd_sets_dirty = TRUE;	
  //set TCS to TCS mode	
  HWIO_OUTFI(APSS_RSC_RSCC_TCSm_DRV2_CONTROL, SLEEP0_TCS, AMC_MODE_TRIGGER, 0);  
  HWIO_OUTFI(APSS_RSC_RSCC_TCSm_DRV2_CONTROL, WAKE0_TCS, AMC_MODE_TRIGGER, 0);  
  HWIO_OUTFI(APSS_RSC_RSCC_TCSm_DRV2_CONTROL, SLEEP1_TCS, AMC_MODE_TRIGGER, 0);  
  HWIO_OUTFI(APSS_RSC_RSCC_TCSm_DRV2_CONTROL, WAKE1_TCS, AMC_MODE_TRIGGER, 0);  

  HWIO_OUTFI(APSS_RSC_RSCC_TCSm_DRV2_CONTROL, SLEEP0_TCS, AMC_MODE_EN, 0);  
  HWIO_OUTFI(APSS_RSC_RSCC_TCSm_DRV2_CONTROL, WAKE0_TCS, AMC_MODE_EN, 0);  
  HWIO_OUTFI(APSS_RSC_RSCC_TCSm_DRV2_CONTROL, SLEEP1_TCS, AMC_MODE_EN, 0);  
  HWIO_OUTFI(APSS_RSC_RSCC_TCSm_DRV2_CONTROL, WAKE1_TCS, AMC_MODE_EN, 0);  

  //grab config set by RPMh driver
  rsc_pull_rpmh_config();

  //merge the RPMh driver config and our static config
  uint32 num_sleep_sets = 0;	
  uint32 num_wake_sets = 0;	
  rpmh_command_set_t * sleep_set = psleep_rsc_cfg_get_set_cfg(RPMH_SET_SLEEP, &num_sleep_sets);
  rpmh_command_set_t * wake_set = psleep_rsc_cfg_get_set_cfg(RPMH_SET_WAKE, &num_wake_sets);

  for(int i = 0; i < num_sleep_sets; i++)
  {
    CORE_VERIFY(sleep_set[i].num_commands <= IMAGE_TCS_SIZE);	
    rsc_config_set(&(sleep_set[i]));
  }
  for(int i = 0; i < num_wake_sets; i++)
  {
    CORE_VERIFY(wake_set[i].num_commands <= IMAGE_TCS_SIZE);	
    rsc_config_set(&(wake_set[i]));
  }
}

/*
 * <!-- power_sleep_get_rsc_backoff -->
 *
 * @brief Retreive the RSC backoff time used by sleep 
 *
 * @return RSC backoff time in XO ticks (19.2Mhz)
 */
uint32 power_sleep_get_rsc_backoff(void)
{
  return (uint32)RSC_BACKOFF;
}

/**
 * <!-- power_sleep_get_lpm_counts -->
 *
 * @brief Returns statistics for the given sleep mode 
 *
 * @param sleep_mode : The sleep mode on which to return stats
 *
 * @return stats for the given sleep mode
 */
sleep_stats_t *power_sleep_get_lpm_counts(power_sleep_stats_enum_t sleep_mode)
{
  if(sleep_mode > POWER_SLEEP_STATS_LAST)
  {
    return NULL;
  }
  else
  {
    return &psleep_lpm_stats_copy[sleep_mode];
  }
}

/**
 * <!-- print_sleep_stats -->
 *
 * @brief Helper function to print out sleep stats 
 */
static void print_sleep_stats(void)
{
  UINTN core_num = mpcore_get_curr_cpu();

  SLEEP_DBG_LOG(core_num, "PowerSleepStats:\r\n");	
  for(int i = 0; i < POWER_SLEEP_STATS_NUM_STATS; i++)
  {
    uint32 stat_type = psleep_lpm_stats_copy[i].stat_type; 
    SLEEP_DBG_LOG(core_num, "\tMode: %c%c%c%c\r\n", stat_type, stat_type >> 0x8, stat_type >> 0x10, stat_type >> 0x18);
    SLEEP_DBG_LOG(core_num, "\tCount: 0x%08x\r\n", psleep_lpm_stats_copy[i].count);
    SLEEP_DBG_LOG(core_num, "\tEntered: 0x%08x\r\n", psleep_lpm_stats_copy[i].last_entered);
    SLEEP_DBG_LOG(core_num, "\tExited: 0x%08x\r\n", psleep_lpm_stats_copy[i].last_exited);
  }
}

/**
 * <!-- power_sleep_stats_init -->
 *
 * @brief Initialize power sleep stats structure 
 */
static void psleep_stats_init(void)
{
  if (!psleep_stats.init)
  {
    psleep_stats.dict_addr = (uint32 *)(AOP_SS_MSG_RAM_START_ADDRESS_BASE + AOP_SS_MSG_RAM_DRV15_BASE + SLEEP_STATS_LOOKUP_OFFSET); 
    psleep_stats.base_addr	= (uint32 *)(size_t)((*(psleep_stats.dict_addr)) + AOP_SS_MSG_RAM_START_ADDRESS_BASE);
    psleep_stats.init = TRUE;
    psleep_stats.lpm[POWER_SLEEP_STATS_C4D4].stat_type = '4d4c';
  }
}

/**
 * <!-- power_sleep_get_msg_ram_sleep_stats -->
 *
 * @brief Helper function to retrieve the system sleep stats from AOP message RAM 
 */
static void power_sleep_get_msg_ram_sleep_stats(void)
{
  psleep_stats_init();

  //copy aop stats from msg ram
  memcpy(&(psleep_stats.lpm[0]), psleep_stats.base_addr, sizeof(sleep_stats_t));
  memcpy(&(psleep_stats.lpm[1]), (psleep_stats.base_addr + (sizeof(sleep_stats_t) / 4)), sizeof(sleep_stats_t));

  //copy all stats locally
  for(int i = 0; i < POWER_SLEEP_STATS_NUM_STATS; i++)
  {
    memcpy(&psleep_lpm_stats_copy[i], &(psleep_stats.lpm[i]), sizeof(sleep_stats_t));
  }
}

/**
 * <!-- power_sleep_init -->
 *
 * @brief Initialize power sleep library 
 */
void power_sleep_init(void)
{
  PsleepCbInit();
  
  /* Function to set suspend mode to OS-Coordinated */
  /* Not doing error checking. 
	 This is only needed when using Gunyah Hypervisor PSCI interface.
	 If not using Gunyah interface NOT_IMPLEMENTED error is expected, and 
	 psci calls will pass-through to TZ which defaults to OS-init Mode. */
  sleep_psci_call(POWER_SLEEP_PSCI_CPU_SET_SUSPEND_MODE, OS_INITIATED_MODE, 0, 0);


}

/**
 * <!-- pdc_set_wakeup_time -->
 *
 * @brief Calculate and populate the wakeup time for the PDC 
 *
 * @param wakeup_time : The wakeup time that software needs to start
 */
static void pdc_set_wakeup_time(uint64 wakeup_time)
{
  CORE_VERIFY(wakeup_time > RSC_BACKOFF);	
  uint64 wakeup_time_adjusted = wakeup_time - RSC_BACKOFF;
  uint32 wakeup_hi = MATCH_VAL_HI(wakeup_time_adjusted);
  uint32 wakeup_lo = MATCH_VAL_LO(wakeup_time_adjusted);
  psleep.wakeup_time = wakeup_time;
  HWIO_OUTI(APSS_RSC_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd, HLOS_DRV, wakeup_lo);  
  HWIO_OUTFI(APSS_RSC_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd, HLOS_DRV, PDC_MATCH_VALUE_HI, wakeup_hi);  
  HWIO_OUTFI(APSS_RSC_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd, HLOS_DRV, PDC_MATCH_VALUE_VALID, 1);  
}

/**
 * <!-- update_core_states -->
 *
 * @brief Helper function to update core states based on what the scheduler may have done 
 *
 * @param init : If its at init time, set non-zero cores to active
 */
static void update_core_states(boolean init)
{
  //NOTE : Current core won't have been updated yet in the mpcore API, 
  //       so the current core will always show ACTIVE.	
  uint32 new_sched_cores_active = mpcore_get_active_mask ();
  for(int i = 0; i < psleep.num_cores_supported; i++)
  {
    uint32 core_bmsk = (1 << i);
    if((core_bmsk & new_sched_cores_active) != 0)
    {
      //if this is the first time we are checking, OR 
      //if mpcore has updated the state since the last check (i.e. has forced this core on)	    
      if((init) || ((new_sched_cores_active & core_bmsk) != (psleep.sched_cores_active & core_bmsk)))
      {	      
        psleep.core_state_bmsk |= (1 << i);	      
        psleep.core_states[i] = PSLEEP_CORE_ACTIVE;
      }
    }
    else
    {
      psleep.core_state_bmsk &= ~(1 << i);	      
      psleep.core_states[i] = PSLEEP_CORE_OFF;
    }
  }
  psleep.sched_cores_active = new_sched_cores_active;
}

/**
 * <!-- is_last_core -->
 *
 * @brief Helper function to determine if we are the last core down or not 
 *
 * @param core_num : The core number on which we are currently operating
 *
 * @return TRUE if we are the last core going down
 */
static boolean is_last_core(uint32 core_num)
{
  update_core_states(FALSE);

  //last core means the rest of the cores are asleep and we are the only one left active
  if((1 << core_num) == psleep.core_state_bmsk)
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

/**
 * <!-- set_current_core_state -->
 *
 * @brief Helper function to update our current understanding of core states 
 *
 * @param core_num  : The core number on which we are currently operating
 * @param new_state : The state we are trying to enter for the given core
 */
static void set_current_core_state(uint32 core_num, power_sleep_core_state new_state)
{
  update_core_states(FALSE);
  psleep.core_states[core_num] = new_state;
  if(new_state >= PSLEEP_CORE_C4)
  {
    psleep.core_state_bmsk &= ~(1 << core_num);	      
  }
  else
  {
    psleep.core_state_bmsk |= (1 << core_num);	      
  }
}

/**
* <!-- sleep_time_check -->
 *
 * @brief Helper function to determine if we have sufficient time to enter C4D4 
 *
 * @param wakeup_time : The time the client has requested to wake up
 *
 * @return TRUE if there is enough time to enter C4D4, FALSE otherwise
 */
static power_sleep_core_state sleep_time_check(uint64 wakeup_time)
{
  uint64 now = ReadQTimerPct();
  UINTN core_num = mpcore_get_curr_cpu();

  if (wakeup_time < (now + MIN_C4_SLEEP_TIME))
  {
    SLEEP_DBG_LOG(core_num, "NSFT for C4 @ %08x Req wake %08x @ %lX\r\n", now, wakeup_time, ReadQTimerPct ());
    return PSLEEP_CORE_ACTIVE;
  }
  else if(wakeup_time < (now + MIN_C4D4_SLEEP_TIME))
  {
    SLEEP_DBG_LOG(core_num, "NSFT for C4D4 @ %08x, => C4 wake to %08x @ %lX\r\n", now, wakeup_time, ReadQTimerPct ());
    return PSLEEP_CORE_C4;
  }
  else
  {
    return PSLEEP_CORE_C4D4;
  }
}

/**
 * <!-- power_sleep_enter_pc -->
 *
 * @brief Attempts to enter the deepest sleep mode possible for the running core 
 *
 * @param restore_ptr : The function pointer to call on wakeup from sleep
 * @param ctxt        : Client context to be passed along with the function pointer
 * @param wakeup_time : Absolute time in XO ticks (19.2Mhz) that we want the subsystem to wake up.
 *                      This should be the earliest wakeup time for any cores
 *
 * @return error code if there is an issue, SUCCESS otherwise
 */
power_sleep_pc_err_enum power_sleep_enter_pc(power_sleep_restore_fn restore_ptr, void * ctxt, uint64 wakeup_time)
{
  int psci_ret_val = 0;	
  uint32 sleep_mode = 0;
  uint32 local_state;
  boolean last_core;
  power_sleep_pc_err_enum ret_val = POWER_SLEEP_SUCCESS;

  //make sure we are initialized
  if (psleep.lock == NULL)
    psleep.lock = init_mutex(PWR_SLEEP_LOCK);

  mutex_acquire(psleep.lock);

  if(!psleep.initialized)
  {
    psleep.initialized = TRUE;	  
    psleep.num_cores_supported = psleep_get_num_cores();
    CORE_VERIFY_PTR(psleep.lock);
    psleep.core_states = (power_sleep_core_state *)malloc(sizeof(power_sleep_core_state) *  psleep.num_cores_supported);
    psleep.dbg_state   = (uint32 *)malloc(sizeof(uint32) *  psleep.num_cores_supported);
    psleep.cmd_sets_dirty = FALSE;	
    CORE_VERIFY_PTR(psleep.core_states);
    CORE_VERIFY_PTR(psleep.dbg_state);

    update_core_states(TRUE);
    psleep_stats_init();
    if(psleep_cx_sd_supported())
    {
      psleep.deepest_sleep_mode = SLEEP_MODE_C4D4_CXSD;
    }
    else
    {
      psleep.deepest_sleep_mode = SLEEP_MODE_C4D4_CXRET;
    }

  }

  //get current core states
  uint32 core_num = mpcore_get_curr_cpu();

  psleep.dbg_state[core_num] = 3;    

  if(is_last_core(core_num))
  {
    power_sleep_core_state time_for = sleep_time_check(wakeup_time);
    if(time_for == PSLEEP_CORE_C4D4)
    {
        //update state for C4D4	  
        
        // No code to execute here which acquires/will be blocked
        // on locks in last core pre-sleep operations

        rsc_config_tcs_contents();

        last_core = TRUE;
        sleep_mode =  psleep.deepest_sleep_mode;
        set_current_core_state(core_num, PSLEEP_CORE_C4D4);
    }
    else
    {
      //update state for C4	  
      last_core = FALSE;
      sleep_mode = SLEEP_MODE_C4;
      set_current_core_state(core_num, PSLEEP_CORE_C4);
    }
  }
  else
  {
    //update state for C4	  
    last_core = FALSE;
    sleep_mode = SLEEP_MODE_C4;
    set_current_core_state(core_num, PSLEEP_CORE_C4);
  }
  local_state = psleep.core_state_bmsk;  
  mutex_release(psleep.lock);

  if(last_core)
  {
    SLEEP_DBG_LOG (core_num, "==> PC %d => C4D4 (%02x) %lX\r\n", core_num, local_state, ReadQTimerPct ());
  }
  else
  {
    SLEEP_DBG_LOG (core_num, "==> PC %d => C4 (%02x)%lX\r\n", core_num, local_state, ReadQTimerPct ());
  }

  if( BackupRestoreSystemCtxt (BACKUP_SYSTEM_CONTEXT) == BACKUP_SYSTEM_CONTEXT)
  {
    if(last_core)
    {
      pdc_set_wakeup_time(wakeup_time);
      psleep_stats.lpm[POWER_SLEEP_STATS_C4D4].last_entered = ReadQTimerPct();
    }

    //SLEEP_DBG_LOG (core_num, "==> PC %d => issuing PSCI call %lX\r\n", core_num, ReadQTimerPct ());
    psci_ret_val = sleep_psci_call(POWER_SLEEP_PSCI_CPU_SUSPEND, sleep_mode, (uint64)restore_ptr, (uint64)ctxt);

    uint32 active_core_num = mpcore_get_curr_cpu();
    //if we end up here, something incorrect happened. Either a failure, or a short circuit such that we didn't actually
    //  enter sleep and thus didn't return to the scheduler context on wakeup
    switch(psci_ret_val)
    {
      case PSCI_SUCCESS :
        psleep.dbg_state[active_core_num] = 4;	    
        ret_val = POWER_SLEEP_INTERRUPT_PENDING;
        SLEEP_DBG_LOG (active_core_num, "==> ERR: Pending Intr @ %lX\r\n",ReadQTimerPct());
        break;
      case PSCI_INVALID_PARAMETERS :
        psleep.dbg_state[active_core_num] = 6;	    
        ret_val = POWER_SLEEP_ERROR_CORE_SHALLOW_SLEEP;
        SLEEP_DBG_LOG (active_core_num, "==> WARN: Another core entered a shallow sleep, couldn't enter C4D4\r\n");
        break;
      case PSCI_DENIED :
        psleep.dbg_state[active_core_num] = 7;	    
        ret_val = POWER_SLEEP_ERROR_CORE_RUNNNING;
        SLEEP_DBG_LOG (active_core_num, "==> WARN: Other core woke, couldn't enter C4D4\r\n");
        break;
      case PSCI_INVALID_ADDRESS :
        psleep.dbg_state[active_core_num] = 8;	    
        ret_val = POWER_SLEEP_ERROR_RESTORE_PTR;
        SLEEP_DBG_LOG (active_core_num, "==> ERR: INVAL_RESTORE_PTR\r\n");
        break;
      default :
        ret_val = POWER_SLEEP_OTHER_FAILURE;
        psleep.dbg_state[active_core_num] = 9;	    
        SLEEP_DBG_LOG (active_core_num, "==> ERR: Unexpected error!!\r\n");
        break;
    }

    //  PSCI returned an error, so we returned back to this context
    //  call restore abort to recover state, register contexts still intact
    SleepAborted (active_core_num, ret_val);

    mutex_acquire(psleep.lock);
    set_current_core_state(active_core_num, PSLEEP_CORE_ACTIVE);
    rsc_clean_up();
    mutex_release(psleep.lock);
  }
  else
  {
    mutex_acquire(psleep.lock);

    uint64 now = 0;

    //update core_state
    uint32 active_core_num = mpcore_get_curr_cpu();
    uint64 local_wakeup_time = psleep.wakeup_time;
    local_state = psleep.core_state_bmsk;

    psleep.dbg_state[active_core_num] = 1;	    
    set_current_core_state(active_core_num, PSLEEP_CORE_ACTIVE);

    //if we are the last core, do some extra work for system sleep stats
    last_core = (psleep.core_state_bmsk == (1 << active_core_num));
    if(last_core)
    {
      //increment count on successful wakeup only	    
      psleep_stats.lpm[POWER_SLEEP_STATS_C4D4].count++;
      now = ReadQTimerPct();
      psleep_stats.lpm[POWER_SLEEP_STATS_C4D4].last_exited = now;
      psleep_stats.lpm[POWER_SLEEP_STATS_C4D4].total_duration += (psleep_stats.lpm[POWER_SLEEP_STATS_C4D4].last_exited - 
		      psleep_stats.lpm[POWER_SLEEP_STATS_C4D4].last_entered);

      rsc_clean_up();
      
      // No code to execute here which acquires/will be blocked
      // on locks in last core post-sleep operations
    }

    mutex_release(psleep.lock);

    SLEEP_DBG_LOG(core_num, "==> %d Awake (%02x)\r\n", core_num, psleep.core_state_bmsk);

    if(last_core)
    {

      if(now > (psleep.wakeup_time + LATE_WAKEUP_THRESHOLD))
      {
        SLEEP_DBG_LOG(core_num, "==> WARN: Late Wakeup @ %08x (Exp: %08x)\r\n", now, local_wakeup_time);
      }

      //update stats
      power_sleep_get_msg_ram_sleep_stats();
      print_sleep_stats();
    }
  }

  return ret_val;
}

