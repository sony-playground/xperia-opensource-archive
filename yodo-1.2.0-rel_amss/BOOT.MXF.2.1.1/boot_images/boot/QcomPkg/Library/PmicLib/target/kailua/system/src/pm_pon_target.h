#ifndef __PMIC_SBL_PON_TARGET_H__
#define __PMIC_SBL_PON_TARGET_H__

/*! \file pm_sbl_pon_target.h
*  \n
*  \brief This file contains PMIC device initialization function and globals declaration.
*  \n
*  \n &copy; Copyright 2016-2022 Qualcomm Technologies Inc, All Rights Reserved
*/
/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/target/kailua/system/src/pm_pon_target.h#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
05/04/16   aab     Added multiple common function used by app level API and target specific functions
03/28/16   aab     Added pm_tgt_get_gp1_cfg()
10/08/15   aab     Creation
========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "com_dtypes.h"
#include "pm_config_target.h"
#include "pm_pon.h"



/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/

#define PON_HLOS_BASE_ADDRESS 0x1300

#define SDAM02_BASE_ADDR 0x7100  //software spare register
#define SDAM03_BASE_ADDR 0x7200   //pon reasons
#define SDAM05_BASE_ADDR 0x7400   //pon event logging
#define SDAM48_BASE_ADDR 0x9F00  //pon triggers

#define MEM_OFFSET_START        0x40
#define PON_EVENT_LOG_AREA_SIZE ((127 - 11 + 1) * 2) // MEM_011 to MEM_127 on SDMA05&06
#define EIGHT_BYTES             8
#define MAX_PON_EVENT_PER_SDAM (PON_EVENT_LOG_AREA_SIZE / 4) // 4 bytes each log item

/*Legacy PON reasons SDAM address */

#define BOOT1_PON_REASON1_ADDR        (SDAM03_BASE_ADDR + MEM_OFFSET_START + 41)
#define BOOT1_WARM_RESET_REASON1_ADDR (SDAM03_BASE_ADDR + MEM_OFFSET_START + 42)
#define BOOT1_ON_REASON_ADDR          (SDAM03_BASE_ADDR + MEM_OFFSET_START + 43)
#define BOOT1_POFF_REASON1_ADDR       (SDAM03_BASE_ADDR + MEM_OFFSET_START + 44) 
#define BOOT1_OFF_REASON_ADDR         (SDAM03_BASE_ADDR + MEM_OFFSET_START + 45)
#define BOOT1_FAULT_REASON1_ADDR      (SDAM03_BASE_ADDR + MEM_OFFSET_START + 46)
#define BOOT1_FAULT_REASON2_ADDR      (SDAM03_BASE_ADDR + MEM_OFFSET_START + 47)
#define BOOT1_S3_RESET_REASON_ADDR    (SDAM03_BASE_ADDR + MEM_OFFSET_START + 48)
#define BOOT3_ON_REASON_ADDR          (SDAM03_BASE_ADDR + MEM_OFFSET_START + 59)


/*SOFT RB SPARE reg */
#define PMIO_PON_PBS_SOFT_RB_SPARE_ADDR (SDAM02_BASE_ADDR + MEM_OFFSET_START + 8)

/* PON trigger configuration */
#define PON_TRIG_CFG_PID_ADDR           (SDAM48_BASE_ADDR + MEM_OFFSET_START + 8 )
#define PON_TRIG_PID_ADDR_INDEX         (0)
#define PON_TRIG_SID_ADDR_INDEX         (1)
#define PON_TRIG_SET_TYPE_ADDR_INDEX    (2)
#define PON_TRIG_POL_HIGH_ADDR_INDEX    (3)
#define PON_TRIG_POL_LOW_ADDR_INDEX     (4)
#define PON_TRIG_EN_ADDR_INDEX          (5)

#define PON_TRIGGER_CONFIG_END_TABLE_SID           0xFF
#define PON_TRIGGER_CONFIG_LAST_EE_ADDR            (SDAM48_BASE_ADDR + MEM_OFFSET_START + 5)
#define PON_TRIGGER_CONFIG_STATUS_SEMAPHORE_ADDR   (SDAM48_BASE_ADDR + MEM_OFFSET_START + 6)


#define PON_PBS_GP1_RESET_S1_TIMER_ADDR             0x85C
#define PON_PBS_GP1_RESET_S1_TIMER_S1_TIMER_BMSK    0x0F
#define PON_PBS_GP1_RESET_S2_TIMER_ADDR             0x85D
#define PON_PBS_GP1_RESET_S2_TIMER_S2_TIMER_BMSK    0x07
#define PON_PBS_GP1_RESET_SW_CTL_ADDR               0x85E
#define PON_PBS_GP1_RESET_S2_CTL2_ADDR              0x85F
#define PON_PBS_GP1_RESET_S2_CTL2_S2_RESET_EN_BMSK  0x80
#define PON_PBS_GP1_RESET_SW_CTL_RESET_TYPE_BMSK    0xFF

#define PON_LOG_SDAM_COUNT_ADDR          (SDAM05_BASE_ADDR + MEM_OFFSET_START + 5)
#define PON_LOG_ENQUEUE_ADDR             (SDAM05_BASE_ADDR + MEM_OFFSET_START + 6)
#define PON_LOG_ENQUEUE_SDAM_NUM         (SDAM05_BASE_ADDR + MEM_OFFSET_START + 7)
#define PON_PBS_PON_LOGGING_AREA_START   (SDAM05_BASE_ADDR + MEM_OFFSET_START + 11)
#define PON_PBS_PON_LOGGING_AREA_END     (SDAM05_BASE_ADDR + MEM_OFFSET_START + 127)
#define PON_LOG_PUSH_PTR_INDEX(x)        (x - (MEM_OFFSET_START + 11))

/*Mask crated using: SID<<12|pid<<4|irq */
#define PON_PBS_KEYPD_PWR_N_S2_RSN     0x0080
#define PON_PBS_RESIN_N_S2_RSN         0x0081
#define PON_PBS_KPDPWR_AND_RESIN_RSN   0x0082
#define PON_PBS_PMIC_WD_RSN            0x0083
#define PON_PBS_PS_HOLD_RSN            0x0084
#define PON_PBS_SW_RST_RSN             0x0085
#define PON_PBS_RESIN_N_DEB_RSN        0x0086
#define PON_PBS_KEYPD_PWR_N_RSN        0x0087
#define PON_PBS_SMPL_RSN               0x0640
#define PON_PBS_PON1_RSN               0x18C1
#define PON_PBS_CBLPWR_RSN             0x18C0
#define PON_PBS_SYS_OK_RSN             0x71C2
#define PON_PBS_RTC_ALARM_RSN          0x0621

#define PON_PBS_RAW_XVDD_RB_MASK             0x8000    
#define PON_PBS_RAW_DVDD_RB_MASK             0x4000  
#define PON_PBS_IMMEDIATE_XVDD_SHUTDOWN_MASK 0x2000
#define PON_PBS_S3_RESET_MASK                0xF0  
#define PON_PBS_S3_RESET_BSHIFT              4  

#define PM_PON_OPTION_USB_CHG_REDGE_REG (SDAM02_BASE_ADDR + MEM_OFFSET_START + 95)

#define PON_HLOS_BASE                         0x00001300


typedef enum
{
   PM_PON_PBS_STATE_DVDD_CONFIG = 0x00  ,
   PM_PON_PBS_STATE_PON         = 0x01  ,
   PM_PON_PBS_STATE_POFF        = 0x02  ,
   PM_PON_PBS_STATE_ON          = 0x03  ,
   PM_PON_PBS_STATE_RESET       = 0x04  ,
   PM_PON_PBS_STATE_OFF         = 0x05  ,
   PM_PON_PBS_STATE_FAULT       = 0x06  ,
   PM_PON_PBS_STATE_WARM_RESET  = 0x07  ,
   PM_PON_PBS_STATE_INVALID     = 0x08  ,
   PM_PON_PBS_STATE_COUNT = PM_PON_PBS_STATE_INVALID
}pm_pon_pbs_state_type;


typedef enum
{
  PM_PON_EVENT_RESERVED                = 0x00,
  PM_PON_EVENT_PON_TRIGGER             = 0x01,
  PM_PON_EVENT_OTP_COPY                = 0x02,
  PM_PON_EVENT_TRIM_COMPLETE           = 0x03,
  PM_PON_EVENT_XVLO_CHECK_COMPLETE     = 0x04,
  PM_PON_EVENT_PMIC_CHECK_COMPLETE     = 0x05,
  PM_PON_EVENT_RESET_TRIGGER           = 0x06,
  PM_PON_EVENT_RESET_TYPE              = 0x07,
  PM_PON_EVENT_WARM_RESET_COUNT        = 0x08,
  PM_PON_EVENT_FAULT_REASON_PART1      = 0x09,
  PM_PON_EVENT_FAULT_REASON_PART2      = 0x0A,
  PM_PON_EVENT_PBS_FAULT               = 0x0B,
  PM_PON_EVENT_FUNDAMENTAL_RESET       = 0x0C,
  PM_PON_EVENT_PON_SEQUENCE_START      = 0x0D,
  PM_PON_EVENT_PON_SUCCESS             = 0x0E,
  PM_PON_EVENT_PSHOLD_POLL             = 0x0F,
  PM_PON_EVENT_FAULT_PMIC_A            = 0x10,
  PM_PON_EVENT_FAULT_PMIC_B            = 0x11,
  PM_PON_EVENT_FAULT_PMIC_C            = 0x12,
  PM_PON_EVENT_FAULT_PMIC_D            = 0x13,
  PM_PON_EVENT_FAULT_PMIC_E            = 0x14,
  PM_PON_EVENT_FAULT_PMIC_F            = 0x15,
  PM_PON_EVENT_FAULT_PMIC_G            = 0x16,
  PM_PON_EVENT_FAULT_PMIC_H            = 0x17,
  PM_PON_EVENT_FAULT_PMIC_I            = 0x18,
  PM_PON_EVENT_FAULT_PMIC_J            = 0x19,
  PM_PON_EVENT_FAULT_PMIC_K            = 0x1A,
  PM_PON_EVENT_FAULT_PMIC_L            = 0x1B,
  PM_PON_EVENT_FAULT_PMIC_M            = 0x1C,
  PM_PON_EVENT_FAULT_PMIC_N            = 0x1D,
  PM_PON_EVENT_INVALID,
  PM_PON_EVENT_COUNT = PM_PON_EVENT_INVALID
}pm_pon_event_type;

typedef struct
{
  pm_pon_pbs_state_type pon_state:8;
  pm_pon_event_type event:8;
  uint16 data;
}pm_pon_logging_type;


typedef struct
{
  uint8 pid           :8;
  uint8 sid           :8;
  uint8 irq_type      :8; //0=level, 1= edge
  uint8 polarity_high :8;
  uint8 polarity_low  :8;
  uint8 int_en        :8;
  uint8 trig_index    :8;
  uint8 trig_mask     :8;	
}pm_pon_trigger_config_type;

typedef struct
{
  uint8 state;
  uint8 event;
  uint8 byte1;
  uint8 byte0;
} pm_pon_log_type;


//API used to get pmic specific PS HOLD configuration
pm_err_flag_type 
pm_tgt_get_pshold_reset_cfg( uint32                      pmic_index,
                             pm_app_pon_reset_cfg_type   app_pshold_cfg,
                             pm_pon_reset_cfg_type*      pshold_cfg);


//API used to get  pmic specific PON Reset configuration
pm_err_flag_type
pm_tgt_get_kpdpwr_reset_cfg( uint32                        pmic_index,
                             pm_app_pon_reset_cfg_type     app_kpdpwr_reset_cfg,
                             pm_pon_reset_cfg_type*        kpdpwr_reset_cfg);

//API used to do target specific PSHOLD configuration
pm_err_flag_type
pm_pon_tgt_specific_pshold_cfg(uint32 pmic_index, pm_app_pon_reset_cfg_type pon_cfg);


//API used to do target specific PON Reset configuration 
pm_err_flag_type 
pm_pon_tgt_specific_kpd_reset_cfg(uint32 pmic_index, pm_app_pon_reset_cfg_type app_pon_reset_cfg);

/*API to do target specific settings for ramdump debug before hard reset*/
pm_err_flag_type
pm_pon_target_debug_hard_reset( void );

/*API to return pre-defined PON TRIGGERS ENABLED*/
pm_err_flag_type
pm_pon_target_get_pon_trigger_config( pm_pon_trigger_type trigger, pm_pon_trigger_config_type *trigger_config);

/*returns PON event, include pon history*/
pm_err_flag_type
pm_pon_get_pon_log(pm_pon_event_type event, uint16 *return_data);

pm_err_flag_type 
pm_pon_get_pon_events(pm_pon_log_type** events, uint16* log_size);

/*Find if specific state occurred in last pon behavior, exclude pon history*/
pm_err_flag_type
pm_last_pon_find_state(pm_pon_pbs_state_type state, boolean* state_found);

/* Get index of expected event from start_index
 * @param index[in] the start index to search for the given event
 * @param event[in] the event we want to find
 * @param next_index[out] the next index
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not avaiable on this
 *                                              version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 */
pm_err_flag_type pm_get_next_event_index(int start_index, uint8 event, int* next_index);

/* Get a PON log item on given index
 * @param index[in] the index of log
 * @param log[out] the required log on the index. Caller must allocate memory for log pointer
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not avaiable on this
 *                                              version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 */
pm_err_flag_type pm_get_a_pon_log(int index, pm_pon_log_type* log);

/* Get the index of last valid log
 * @last_index: the index of last valid log
 * @return: pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not avaiable on this
 *                                              version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 */
pm_err_flag_type pm_get_last_valid_log_index(int* last_index);

/*
 * Get the string to know which PMIC suffer FAULT
 * @param event[in] the event of PON log which tells fault type
 * @param fault_pmic[out] Pass out the string indicating which PMIC suffer the fault.
 *                        Must be not NULL
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not avaiable on this
 *                                              version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 */
pm_err_flag_type pm_pon_get_fault_pmic_string(pm_pon_event_type event, char* fault_pmic, int size);

/*
 * Get target specific pon trigger string
 * @param pon_dataset[in] the sdam stored pon log dataset
 * @param pon_trig_str_p[out] Pass out the string pointer indicating target specific pon trigger string
 *                        Must be not NULL
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not avaiable on this
 *                                              version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 */
pm_err_flag_type pm_get_target_specific_pon_trig_string(uint16 pon_dataset, char** pon_trig_str);


/*
 * Retrieve the PC address of PBS fault with string. It is read from SDAM. It can also be read from PBS_CORE peripheral as well.
 * @param str[out]: The string format of PC of PBS Fault. 
 *                  NOTE: The caller need to allocate the memoery for str before calling this function.
 * @param size[in]: The size of str. Need to >= 4, otherwise the address cannot be output properly
 */
void pm_pon_get_pbs_fault_pc(char* str, int size);


/*
 * Retrieve the return address address of PBS fault with string. It is read from SDAM. It can also be read from PBS_CORE peripheral as well.
 * @param str[out]: The string format of PC of PBS Fault. 
 *                  NOTE: The caller need to allocate the memoery for str before calling this function.
 * @param size[in]: The size of str. Need to >= 4, otherwise the address cannot be output properly
 */
void pm_pon_get_pbs_fault_return_address_pc(char* str, int size);


/*
 * Retrieve the PBS nack reason. Read it from SDAM and then parse according to CDoS.
 * @param str[out]: The string format of PBS Nack reason. 
 *                  NOTE: The caller need to allocate the memoery for str before calling this function.
 * @param size[in]: The size of str. Need to >= 32
 */
void pm_pon_get_pbs_nack_reason(char* str, int size);

#endif //__PMIC_SBL_PON_TARGET_H__
