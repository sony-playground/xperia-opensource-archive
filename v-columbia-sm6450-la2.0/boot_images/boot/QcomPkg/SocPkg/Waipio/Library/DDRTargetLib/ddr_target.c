/**
 * @file ddr_target.c
 * @brief
 * Target specific DDR drivers.
 */
/*==============================================================================
                                EDIT HISTORY

================================================================================
when       who     what, where, why
--------   ---     -------------------------------------------------------------
05/11/21   mkma    ddr_get_syndrome_regions API added
02/16/21   mkma    updated boot_mode support changes
02/09/21   mkma    updated vdd2h pmic
01/28/21   mkma    updated DDR flags for SOC and freq set to 200
12/09/20   rama    Removed boot_extern_platforminfo_interface.h
03/18/20   rama    Removed boothw_target.h
01/16/19   dj      Judge whether a LP5 or LP4 device
12/18/18   dj      change register used for getting serial ID of the MSM 
09/26/17   daison  Use DDR_CH_ALL instead of interface_name parameter
07/28/15   rp      Added ddr_post_training function to support conditional loading of ddr training
07/20/15   tw      enable one time training
07/01/15   tw      added bimc remapper api call
06/20/14   tw      added ddr_pre_init api to capture any target specific 
                   workarounds that needs to be applied prior to ddr init
05/28/14   tw      cleaned up sbl <-> ddr driver dependencies around ddr training
                   implementation of cx\mx\cpr hash to force retraining
03/12/14   sr      Initial version.
================================================================================
                   Copyright 2014-2021  Qualcomm Technologies Incorporated
                              All Rights Reserved
                     Qualcomm Confidential and Proprietary
==============================================================================*/
/*==============================================================================
                                  INCLUDES
==============================================================================*/
#include <string.h>
#include "ddr_common.h"
#include "ddr_drivers.h"
#include "ddr_internal.h"
#include "ddr_sync.h"
#include "ddr_log.h"
#include "ddr_params.h"
#include "ddr_target.h"
#include "HAL_SNS_DDR.h"
#include "ddr_config.h"
#include "ClockBoot.h"
#include "icbcfg.h"
#include <stddef.h>
#include "ddr_external.h"
#include "pm_ldo.h"
#include "CoreVerify.h"
#include "cpr.h"
#include "crc.h"
#include "pm_smps.h"
#include "pm_resources_and_types.h"
#include "PlatformInfo.h"
#include "ChipInfo.h"
#include "ddr_hwio.h"
#include "Target_cust.h"
//#include "llcc.h"  //DS_Enable
#include "ddr_sdi_log.h"
//#include "ddrss_init_sdi.h"  //DS_Enable
#include "core_sw_interface.h"
#include "ddr_fw_interface.h"
#include "pm_gpio.h"
#include "pm_version.h"
#include "pm_sdam.h"
#include "boot_build_component.h"
#include <DDIPlatformInfo.h>

#define LP5_TRAINING_ENABLED TRUE 
#define LP4_TRAINING_ENABLED FALSE 
#define LP5_ONE_TIME_TRAINING TRUE
#define LP4_ONE_TIME_TRAINING FALSE

#define DDR_DECODE_STORE_OFFSET 85
#define NUM_OF_SDAM_BYTE_TO_READ 1

/*==============================================================================
                                  MACROS
==============================================================================*/
/* Macro for round-up division */
#define div_ceil(n, d)  (((n) + (d) - 1) / (d))

#define EIGHT_SEGMENT_MASK 0xFF
#define FOUR_SEGMENT_MASK  0xF

#define DDR_COLLAPSE_CP    0x2
#define PMIC_VDDQ PMIC_H
#define PMIC_VDDQ_SMPS PM_SMPS_3
#define PMIC_VDD2H         PMIC_C
#define PMIC_VDD2H_SMPS    PM_SMPS_10

#define BASE_DDR_SS_REG 0x9080000
#define MC4_MC5_FUSE 0x3

#define MTE_FUSE 0x176004F0

#define MTE_DATA 0x80000000
#define MTE_SYNDROME 0xC0000000
#define DDR_LOG_LEN 110
#define DDR_FREQ_SET_EN 0
/*==============================================================================
                                  DATA
==============================================================================*/

/* DDR interface status, keeps track of active interfaces and their status */
extern ddr_interface_state ddr_status;
extern  boolean boot_dload_is_dload_mode_set( void );

extern ddr_info ddr_physical_size;
extern ddr_size_info ddr_system_size;

extern DDR_SDI_LOGS *ddr_sdi_logs_ptr;

static railway_voter_t ebi_pin = NULL;
static railway_voter_t cx_pin = NULL;
static boot_mode_type g_boot_mode = BOOT_MODE_XBL;

static uint32 DDR_PerfLvl = 1;
static uint32 DDR_FreqKHz = 200000;

/*Indicates ddr initialization is done or not, FALSE by default*/
extern boolean ddr_init_done;
/*==============================================================================
                                  FUNCTIONS
==============================================================================*/

void print_ddr_frequency(void);
void ddr_freq_set_min_max(uint8 min, uint8 max);
void ddr_devicetree_helper_uint32(const char *entry_name, char *dt_name, uint32 *retval);

void ddr_freq_set_min_max(uint8 min, uint8 max)
{
  uint8 i;
  uint8 num_levels = ddr_shared_data->num_ddr_levels;
  if (max > num_levels)
    max = num_levels;
  for (i = 0; i < num_levels; i++)
  {
    if (i >= min && i <= max)
      ddr_driver_struct->aop_params->mc_states[i].freq_enable = TRUE;
    else
      ddr_driver_struct->aop_params->mc_states[i].freq_enable = FALSE;
  }
    
}
boot_mode_type ddr_get_boot_mode( void )
{
	return g_boot_mode;
}

/* ============================================================================
**  Function : ddr_target_init
** ============================================================================
*/
/*!
*   @brief
*   This function is called at the end of ddr init to initialize any
*   target specific configurations
*
*   @details
*   Target specific configurations such as override of timing registers and
*   calling target specific init functions will be captured in this api
*
*   @param
*   None
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
void ddr_target_init(boot_mode_type boot_mode)
{
  uint32 chip_plat_ver_info;
  uint8 data = 0xFF;
  uint32 err;
  uint32 platform_key = 0;
  DalDeviceHandle        *phPlatformInfo = NULL;  
  //DalPlatformInfoPlatformInfoType pInfo = {0};
  DALResult                     eResult; 
  DalPlatformInfoPlatformType platform = DalPlatformInfo_Platform();
  
  uint32 val_extnd_term;
  ddr_devicetree_helper_uint32("extnd_term_log_flag", "/soc/ddr_target_dt", &val_extnd_term);
  dt_target_entries.extnd_term_log_flag = val_extnd_term;

  if(boot_mode >=BOOT_MODE_MAX)
  {
    HAL_EXT_CORE_SW_DDR_printf (DDR_ERROR, "Invalid boot mode in ddr_target_init"); 
    ddr_abort();
  }
  
  g_boot_mode = boot_mode;//save device type
  if (phPlatformInfo == NULL)
  {
    eResult = DAL_DeviceAttach(DALDEVICEID_PLATFORMINFO, &phPlatformInfo);
    CORE_VERIFY(eResult == DAL_SUCCESS);
  }
  eResult = DalPlatformInfo_GetKeyValue(phPlatformInfo, DALPLATFORMINFO_KEY_SLT, &platform_key); 
  if (dt_target_entries.extnd_term_log_flag != 0)
    {
      ddr_shared_data->extended_term_log_en = 1;
    }
  else
    {
      ddr_shared_data->extended_term_log_en = platform_key;
    }
  ddr_shared_data->target_silicon = 0;
  
  if (platform != DALPLATFORMINFO_TYPE_RUMI)
  {
    ddr_shared_data->target_silicon = 1;
    if(g_boot_mode == 0 ) //if (PcdGet32 (PcdBuildType) == 0)
    {
      int rail = rail_id("vdda_ebi");
      CORE_VERIFY(rail!=RAIL_NOT_SUPPORTED_BY_RAILWAY);    
      ebi_pin = railway_create_voter(rail, RAILWAY_DDR_TRAINING_VOTER_ID);
      railway_corner_vote(ebi_pin, RAILWAY_TURBO);
      railway_transition_rails();
      err = pm_smps_sw_mode(2, PM_SMPS_6, PM_SW_MODE_NPM); // CX SMPS6C to PWM
      CORE_VERIFY(err == PM_ERR_FLAG_SUCCESS);
      err = pm_smps_sw_mode(7, PM_SMPS_2, PM_SW_MODE_NPM); // VDDA_EBI SMPS2C to PWM
      CORE_VERIFY(err == PM_ERR_FLAG_SUCCESS);   
	  
	  /* VDD2H init value to 1.080V. This overrides PSI configured voltage */
      err = pm_smps_volt_level(2, PM_SMPS_10, 1080 * 1000, TRUE);
      CORE_VERIFY(err == PM_ERR_FLAG_SUCCESS); 
    }
  }
  ddr_shared_data->jtag_connected = HWIO_INF(AOSS_CC_CDBGPWRUPREQ, STATUS); 
  
  chip_plat_ver_info =  HWIO_IN(TCSR_SOC_HW_VERSION);
  
  ddr_shared_data->serial_num = ChipInfo_GetSerialNumber();

  /* extract upper 16 bit and store it in platform field of ddr_misc */
  ddr_shared_data->platform_id  = chip_plat_ver_info >> 16 /*& 0xFFFF0000*/ ;
  /* extract lower 16 bits and store it in version field of ddr_misc */
  ddr_shared_data->chip_version  = chip_plat_ver_info & 0x0000FFFF ;

  ddr_shared_data->total_channels = 0xF;
  ddr_shared_data->enabled_channels = 0xF;
  ddr_shared_data->num_channel = 4;
  ddr_shared_data->ddr_init_clk_idx = 1; //set initial clk plan to 200
  ddr_shared_data->enabled_chipselects = 3;
  ddr_shared_data->device_params.device_type = DDR_TYPE_LPDDR5;
  //ddr_shared_data->platform_info = DDR_FW_PLATFORM_RUMI;
  if (platform != DALPLATFORMINFO_TYPE_RUMI)
  {
    if((HWIO_DDR_REG_FUSE_INPUTS_STATUS_INM(MC4_MC5_FUSE)) == MC4_MC5_FUSE)
    {
      HAL_EXT_CORE_SW_DDR_printf (DDR_ERROR, "Fuse not blown correctly"); 
      ddr_abort();
    }
    if((HWIO_DDR_REG_FUSE_INPUTS_STATUS_INM(MC4_MC5_FUSE)) == 0)
    {
      HAL_EXT_CORE_SW_DDR_printf (DDR_ERROR, "Fuse not blown");
      ddr_abort();
    }
    /* This PMIC call is made in order to know whether we have LP5 or LP4 on the chip */
    /* if data == 0x0 then it is LP5, if data ==0x1 then it is LP4x */
    err = pm_sdam_mem_read(PMIC_A, PM_SDAM_1, DDR_DECODE_STORE_OFFSET, NUM_OF_SDAM_BYTE_TO_READ, &data); 
    if(err != PM_ERR_FLAG_SUCCESS)
    {
      HAL_EXT_CORE_SW_DDR_printf (DDR_BOOTLOG, "pmic ddr detect failed");
    }
    /* if MC4 fuse is set to 0x1 ; then it is LP5 device */
    if(HWIO_DDR_REG_FUSE_INPUTS_STATUS_INM(HWIO_DDR_REG_FUSE_INPUTS_STATUS_MC4_FUSE_STATUS_BMSK))
    {
      HAL_EXT_CORE_SW_DDR_printf (DDR_BOOTLOG, "LP5 DDR detected"); 
         ddr_shared_data->device_params.device_type = DDR_TYPE_LPDDR5;
      if(err == PM_ERR_FLAG_SUCCESS && data != 0x0)
      {
         HAL_EXT_CORE_SW_DDR_printf (DDR_ERROR, "Mismatch between fuse detect and pmic detect");
         ddr_abort();
      }
    }
  }


  /*eResult = DalPlatformInfo_GetPlatformInfo (phPlatformInfo, &pInfo);
  CORE_VERIFY(eResult == DAL_SUCCESS);
  // If platform_info = 0xDEADBEEF, 0xAD => major version and 0xBE => minor version.
  uint32 major = pInfo.version & 0x00FF0000;
  uint32 minor = pInfo.version & 0x000000FF;*/
}


/* ============================================================================
**  Function : ddr_is_shrm_load_required
** ============================================================================
*/
/*!
*   @brief
*   This function is used to cehck if shrm elf loading is required
*
*   
*  @param  None
*   
*   @par Dependencies
*   None
*   
*   @par Side Effects
*   None
*   
*   @retval True if shrm elf loading is required, false if not
*   
*   @sa None
*/
boolean ddr_is_shrm_load_required()
{
  if(g_boot_mode == BOOT_MODE_DEVICEPROGRAMMER)  //if (PcdGet32 (PcdBuildType) == SBL_BUILD_DEVICEPROGRAMMER_DDR)
  {
    return FALSE;
  }
  if ((HWIO_INF(AOSS_CC_RESET_FSM_CTRL, FIRST_PASS_COMPLETE) && HWIO_AOSS_CC_ALT_RESET_ENABLE_INM(HWIO_AOSS_CC_ALT_RESET_ENABLE_ALLOW_BIMC_ALT_ARES_BMSK)) ||
            HWIO_INF(AOSS_CC_RESET_FSM_STATUS, FIRST_PASS_EXPIRE)||(!HWIO_INF(AOSS_CC_RESET_FSM_CTRL, FIRST_PASS_COMPLETE)))
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}  

/* ============================================================================
**  Function : ddr_target_sdi_pass_init
** ============================================================================
*/
/*!
*   @brief
*   This function is called by ddr_initialize_device, handles none cold boot DDR init pass
*
*   @details
*   None
*
*   @param
*   clk_speed: target clock to be initialized
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/

boolean ddr_target_sdi_pass_init(uint32 clk_speed)
{
  char ddr_log_string[200];
  pm_err_flag_type pm_status;
  
  snprintf(ddr_log_string, 200, "PASS1 Cookie =  0x%x",ddr_sdi_logs_ptr->pass1_enter_cookie->p_cookie_value);
  boot_log_message(ddr_log_string);
  
  //First pass complete && bimc alt_ares set) or first_pass_expire -> full ddr init     
  /*
  SDI is skipped      :AOSS REG pass1 complete = 0  , AOSS REG pass1 expire = 0 , we check for AOSS REG pass1 complete = 0 only and then call HAL DDR INIT 
  SDI is hanged       :AOSS REG pass1 expire = 1 ,  in this case ALT ARES will be set to 1 by HW , so we check for EXPIRE only and then call HAL DDR INIT 
                      ( no need to  check for ALT ARES specially for this case in order to call HAL DDR INIT) 
  SDI failed in DDR SDI ( ddr sdi init ):AOSS REG pass1 complete = 1  , AOSS REG pass1 expire = 0  , TZ SDI set ALT ARES , so we check for AOSS pass1 complete = 1 & ALT ARES to call HAL DDR INIT 

  */
  if ((HWIO_INF(AOSS_CC_RESET_FSM_CTRL, FIRST_PASS_COMPLETE) && HWIO_AOSS_CC_ALT_RESET_ENABLE_INM(HWIO_AOSS_CC_ALT_RESET_ENABLE_ALLOW_BIMC_ALT_ARES_BMSK)) ||
            HWIO_INF(AOSS_CC_RESET_FSM_STATUS, FIRST_PASS_EXPIRE)||(!HWIO_INF(AOSS_CC_RESET_FSM_CTRL, FIRST_PASS_COMPLETE)))
  {
    ddr_sdi_logs_ptr->pass2_cookie->p_cookie_value = DDR_FULLY_INIT_PASS2_START;
    snprintf(ddr_log_string, 200, "ALT_ARES Set, Before HAL_DDR_Init(), DBG PDC Tr = 0x%x, First Pass expire = 0x%x, First Pass complete = 0x%x , BIMC Alt ARES  = 0x%x , PASS2 Cookie = 0x%x ",
           (HWIO_INF(AOSS_CC_RESET_FSM_STATUS, DBG_PDC_TRIGGER)), (HWIO_INF(AOSS_CC_RESET_FSM_STATUS, FIRST_PASS_EXPIRE)), 
           (HWIO_INF(AOSS_CC_RESET_FSM_CTRL, FIRST_PASS_COMPLETE))  , HWIO_AOSS_CC_ALT_RESET_ENABLE_INM(HWIO_AOSS_CC_ALT_RESET_ENABLE_ALLOW_BIMC_ALT_ARES_BMSK),
           ddr_sdi_logs_ptr->pass2_cookie->p_cookie_value);
    boot_log_message(ddr_log_string);
    snprintf(ddr_log_string, 200, "SHRM run state = 0x%x ",HWIO_SHRM2_CSR_SHRM_SPROC_STATUS_IN);
    boot_log_message(ddr_log_string);
    
    /* Set VDDQ initially to 0.5 V for LP5 */
	//if (ddr_shared_data->device_params.device_type == DDR_TYPE_LPDDR5) 
	if(HWIO_DDR_REG_FUSE_INPUTS_STATUS_INM(HWIO_DDR_REG_FUSE_INPUTS_STATUS_MC4_FUSE_STATUS_BMSK))	
	{
	   ddr_shared_data->device_params.device_type = DDR_TYPE_LPDDR5;	
	   pm_status = pm_smps_volt_level(PMIC_VDDQ,  PMIC_VDDQ_SMPS, 500000, TRUE);
	
      if (pm_status != PM_ERR_FLAG_SUCCESS)
      {
         snprintf(ddr_log_string, 200, "Unable to set VDDQ to 0.5 Volt");
         boot_log_message(ddr_log_string);
      }
	}
    HAL_CORE_SW_DCB_Init(ddr_shared_data);  
    HAL_CORE_SW_DCB_Set_DDR_AOP_PARAMS(ddr_shared_data);
    ddr_get_shub_shrm_freq();
    HAL_DDR_FW_Init();
	ddr_init_done = TRUE;
    snprintf(ddr_log_string, 200, "pass1 fail case, full ddr_init_done = %d ",ddr_init_done);
    boot_log_message(ddr_log_string);
    ddr_sdi_logs_ptr->pass2_cookie->p_cookie_value = DDR_FULLY_INIT_PASS2_COMPLETE;
    
    snprintf(ddr_log_string, 200, "ALT_ARES Set,HAL_DDR_Init() completed, DBG PDC Tr = 0x%x, First Pass expire = 0x%x, First Pass complete = 0x%x , BIMC Alt ARES  = 0x%x , PASS2 Cookie = 0x%x ",
           (HWIO_INF(AOSS_CC_RESET_FSM_STATUS, DBG_PDC_TRIGGER)), (HWIO_INF(AOSS_CC_RESET_FSM_STATUS, FIRST_PASS_EXPIRE)), 
           (HWIO_INF(AOSS_CC_RESET_FSM_CTRL, FIRST_PASS_COMPLETE))  , HWIO_AOSS_CC_ALT_RESET_ENABLE_INM(HWIO_AOSS_CC_ALT_RESET_ENABLE_ALLOW_BIMC_ALT_ARES_BMSK),
           ddr_sdi_logs_ptr->pass2_cookie->p_cookie_value);

    boot_log_message(ddr_log_string);
    snprintf(ddr_log_string, 200, "SHRM run state = 0x%x ",HWIO_SHRM2_CSR_SHRM_SPROC_STATUS_IN);
    boot_log_message(ddr_log_string);
  }
  else
  {
    ddr_sdi_logs_ptr->pass2_cookie->p_cookie_value = DDR_RECOVER_PASS2_START;
   
    snprintf(ddr_log_string, 200, "HAL_DDR_SDI_Recover() start:  DBG PDC Tr = 0x%x, First Pass expire = 0x%x, First Pass complete = 0x%x , BIMC Alt ARES  = 0x%x , PASS2 Cookie = 0x%x ",
           (HWIO_INF(AOSS_CC_RESET_FSM_STATUS, DBG_PDC_TRIGGER)), (HWIO_INF(AOSS_CC_RESET_FSM_STATUS, FIRST_PASS_EXPIRE)), 
           (HWIO_INF(AOSS_CC_RESET_FSM_CTRL, FIRST_PASS_COMPLETE))  , HWIO_AOSS_CC_ALT_RESET_ENABLE_INM(HWIO_AOSS_CC_ALT_RESET_ENABLE_ALLOW_BIMC_ALT_ARES_BMSK),
           ddr_sdi_logs_ptr->pass2_cookie->p_cookie_value);
    boot_log_message(ddr_log_string);
    snprintf(ddr_log_string, 200, "SHRM run state = 0x%x ",HWIO_SHRM2_CSR_SHRM_SPROC_STATUS_IN);
    boot_log_message(ddr_log_string);
      
    //do DDRSS_SDI_Recover 
    HAL_DDR_FW_SDI_Recover(); 
    ddr_sdi_logs_ptr->pass2_cookie->p_cookie_value = DDR_RECOVER_PASS2_COMPLETE;
   
    snprintf(ddr_log_string, 200, "HAL_DDR_SDI_Recover() end : DBG PDC Tr = 0x%x, First Pass expire = 0x%x, First Pass complete = 0x%x , BIMC Alt ARES  = 0x%x , PASS2 Cookie = 0x%x ",
           (HWIO_INF(AOSS_CC_RESET_FSM_STATUS, DBG_PDC_TRIGGER)), (HWIO_INF(AOSS_CC_RESET_FSM_STATUS, FIRST_PASS_EXPIRE)), 
           (HWIO_INF(AOSS_CC_RESET_FSM_CTRL, FIRST_PASS_COMPLETE))  , HWIO_AOSS_CC_ALT_RESET_ENABLE_INM(HWIO_AOSS_CC_ALT_RESET_ENABLE_ALLOW_BIMC_ALT_ARES_BMSK),
           ddr_sdi_logs_ptr->pass2_cookie->p_cookie_value);
    boot_log_message(ddr_log_string);
    snprintf(ddr_log_string, 200, "SHRM run state = 0x%x ",HWIO_SHRM2_CSR_SHRM_SPROC_STATUS_IN);
    boot_log_message(ddr_log_string);
    snprintf(ddr_log_string, 200, "ddr_init status = %d  DDR recover normal pass2",ddr_init_done);
    boot_log_message(ddr_log_string);
  }
  HWIO_OUTF(AOSS_CC_RESET_FSM_CTRL, DDR_OUT_OF_SELF_RFRSH, 1);
  return ddr_init_done;
}

/* ============================================================================
**  Function : ddr_pre_init
** ============================================================================
*/
/*!
*   @brief
*   This function is called before ddr is initialized. It will take care of any
*   pre initialization workarounds.
*
*   @details
*   This function is called before ddr is initialized. It will take care of any
*   pre initialization workarounds.
*
*   @param
*   boolean -
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
boolean ddr_pre_init()
{
  return TRUE;
}

void init_aop_params()
{
      uint8 i=0;
      ddr_driver_struct->aop_params = ddr_shared_data->ddr_aop_params.ptr;
      for(i=0 ; i<ddr_shared_data->num_ddr_levels; i++)
      {
           ddr_driver_struct->vddq_plan[i].clk_idx = ddr_driver_struct->aop_params->mc_states[i].clk_idx;
           ddr_driver_struct->vddq_plan[i].freq_khz = ddr_driver_struct->aop_params->mc_states[i].freq_khz;
           ddr_driver_struct->vddq_plan[i].vddq = 500000;
      }
}

void fill_aop_params()
{
      uint8 i=0;
      ddr_driver_struct->aop_params = ddr_shared_data->ddr_aop_params.ptr;
      for(i=0 ; i<ddr_shared_data->num_ddr_levels; i++)
      {
           ddr_driver_struct->vddq_plan[i].clk_idx = ddr_driver_struct->aop_params->mc_states[i].clk_idx;
           ddr_driver_struct->vddq_plan[i].freq_khz = ddr_driver_struct->aop_params->mc_states[i].freq_khz;
           ddr_driver_struct->vddq_plan[i].vddq = (uint32)(ddr_driver_struct->aop_params->aop_pmic_settings[0].values[ddr_driver_struct->aop_params->mc_states[i].pmic_mode_cfg])*1000;
      }
}


/* ========================================================================
**  Function : DDR_InitRails
** ======================================================================*/
/*
    initialize voltage rail handles

    @param None
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
static void DDR_InitRails()
{
  static boolean bIsInit = FALSE;

  if(bIsInit)
  {
    return;
  }

  /* Initialize CX & VDDA_EBI Rails */
  if (!cx_pin)
  {
    cx_pin = railway_create_voter(rail_id("vddcx"), RAILWAY_DDR_TRAINING_VOTER_ID);
  }

  if (!ebi_pin)
  {
    ebi_pin = railway_create_voter(rail_id("vdda_ebi"), RAILWAY_DDR_TRAINING_VOTER_ID);
  }

  railway_corner_vote(cx_pin, RAILWAY_NOMINAL);
  railway_corner_vote(ebi_pin, RAILWAY_SVS);
  railway_transition_rails();

  bIsInit = TRUE;
}


/* ============================================================================
**  Function : DDR_MapCorner
** ============================================================================
*/
/**
  Due to memory constraint, we cannot use voltage code in MC/SHUB table.
  This driver is used for convert voltage corner to railway corner

  @params
     rail - VOLTAGE_RAIL value
  @return
    railway corner value

  @dependencies
    None.

  @sa
    None
*/
static railway_corner DDR_MapCorner( VOLTAGE_RAIL rail )
{
  switch (rail)
  {
    case VDD_RET:   return RAILWAY_RETENTION;
    case MIN_SVS:   return RAILWAY_SVS_MIN;
    case LOW_SVS:   return RAILWAY_SVS_LOW;
    case SVS:       return RAILWAY_SVS;
    case SVS_L1:    return RAILWAY_SVS_HIGH;
    case NOMINAL:   return RAILWAY_NOMINAL;
    case TURBO:     return RAILWAY_TURBO;
    case TURBO_L1:  return RAILWAY_SUPER_TURBO;
    default:        return RAILWAY_NO_REQUEST;
  };
}

/* =========================================================
**  Function : DDR_GetFreqInKhz()
** =======================================================*/
/* 
 * @param None
 * @return The clock rate of DDR in kHz
 */
uint32 DDR_GetFreqInKhz()
{
  return DDR_FreqKHz;
  // return ddr_driver_struct->aop_params->mc_states[DDR_PerfLvl].freq_khz;
}

/* =========================================================
**  Function : DDR_GetPerfLevel()
** =======================================================*/
/* 
 * @param None
 * @return performance level for ddr
 */
uint32 DDR_GetPerfLevel()
{
  return DDR_PerfLvl;
}


/* =========================================================================
**  Function : DDR_FindBIMCLevel
** =========================================================================*/
/*!
    Find the table line that meets or exceeds the request.

    @param -  nFreqHz [in] Frequency to search for in the table
    @param -  pConfigTable [in] Table to search
    @param -  nTableLimit [in] Length of table 
    @return - index to the table row to be used.

    @dependencies
    None.

    @sa None
*/
static uint32 DDR_FindBIMCLevel
( 
  uint32 nFreqKHz,
  FREQ_STATE *pDDRConfig
)
{
  uint32 index;
  uint32 nMaxDDRLevels = ddr_shared_data->num_ddr_levels;

  /* Start with index-1 since index-0 is for DDR power collapsed */
  for(index = 1; (index < nMaxDDRLevels) && (pDDRConfig[index].freq_khz != 0); index++)
  {
    if( (pDDRConfig[index].freq_enable) && (pDDRConfig[index].freq_khz >= nFreqKHz) )
    {
      return index;
    }
  }

  /* If not found, return index of highest enable clock plan in the table */
  if ( index == nMaxDDRLevels )
  {
    for ( index = nMaxDDRLevels-1; index > 0; index-- )
    {
      if ( pDDRConfig[index].freq_enable == TRUE )
        return index;
    }
  }

  return 0;
}


/* =========================================================================
**  Function : DDR_SetBIMCSpeed
** =========================================================================*/
/*!
    Switch DDR and the related BIMC roots to the requested frequency

    @param -  nFreqHz [in] Frequency to search for in the table
    @return - FALSE on fail, TRUE on success

    @dependencies
    None.

    @sa None
*/
boolean DDR_SetBIMCSpeed(uint32 nFreqKHz )
{
  railway_corner    vdda, vddcx;
  uint32            nCurrKHz, nCurrLvlIdx, nNewLvlIdx; 
  FREQ_STATE       *pCurrDDRCfg;
  FREQ_STATE       *pNewDDRCfg;
  pm_err_flag_type  pm_status;
  FREQ_STATE       *pMCCfg;
  vddq_state       *pVddqCfg;

  /* Init rails */
  DDR_InitRails();

  /* Get MC configure data */
  pMCCfg = (FREQ_STATE *)(ddr_driver_struct->aop_params->mc_states);
  pVddqCfg = (vddq_state *)(ddr_driver_struct->vddq_plan);

  /* Find current level */
  nCurrKHz = DDR_GetFreqInKhz();
  nCurrLvlIdx = DDR_FindBIMCLevel ( nCurrKHz, pMCCfg );
  pCurrDDRCfg = &pMCCfg[nCurrLvlIdx];

  /* Find new level */
  nNewLvlIdx = DDR_FindBIMCLevel ( nFreqKHz, pMCCfg );
  pNewDDRCfg = &pMCCfg[nNewLvlIdx];
  nFreqKHz = pMCCfg[nNewLvlIdx].freq_khz;

  // Change VDDA_EBI rail if increase
  if ( pMCCfg[nCurrLvlIdx].vdda < pMCCfg[nNewLvlIdx].vdda )
  {
    vdda = DDR_MapCorner( pMCCfg[nNewLvlIdx].vdda );
    railway_corner_vote( ebi_pin, vdda);
    railway_transition_rails();
  }

  if (pVddqCfg[nCurrLvlIdx].vddq < pVddqCfg[nNewLvlIdx].vddq)
  {
    pm_status = pm_smps_volt_level(PMIC_VDDQ, PMIC_VDDQ_SMPS, pVddqCfg[nNewLvlIdx].vddq, TRUE);
    if (pm_status != PM_ERR_FLAG_SUCCESS)
    {
      return FALSE;
    }
  }

  /* 
   * Vote for higher voltage before the switch if the new frequency is more
   * than the current frequency.
   */
  if ( nCurrKHz < nFreqKHz )
  {
    vddcx = DDR_MapCorner( pMCCfg[nNewLvlIdx].vddcx );
    /* CPU and Buses are running at NOMINAL or higher.  Do not scale voltage below NOMINAL */
    if ( vddcx >= RAILWAY_NOMINAL )
    {
      // Change VDD_CX rail
      railway_corner_vote(cx_pin, vddcx);
      railway_transition_rails();
    }
  }

  if (pMCCfg[nCurrLvlIdx].pmic_mode_cfg < pMCCfg[nNewLvlIdx].pmic_mode_cfg )
  {
    pm_status = pm_smps_volt_level(PMIC_VDD2H, PMIC_VDD2H_SMPS, ddr_driver_struct->aop_params->aop_pmic_settings[2].values[pMCCfg[nNewLvlIdx].pmic_mode_cfg] * 1000, TRUE);
    if (pm_status != PM_ERR_FLAG_SUCCESS)
    {
      return FALSE;
    }
  }
  /* Trigger switch to new frequency and next domain. */
  ddr_pre_clock_switch( nCurrKHz, nFreqKHz);
  ddr_clock_switch( nCurrKHz, nFreqKHz);

  /* 
   * Vote for lower voltage after the switch if the new frequency is less
   * than the current frequency.
   */
  if ( nCurrKHz > nFreqKHz )
  {
    /* CPU and Buses are running at NOMINAL or higher.  Do not scale voltage below NOMINAL */
    vddcx = DDR_MapCorner( pNewDDRCfg->vddcx );
    if ( vddcx < RAILWAY_NOMINAL )
    {
      vddcx = RAILWAY_NOMINAL;
    }

    railway_corner_vote(cx_pin, vddcx);
    railway_transition_rails();
  }

  if (pVddqCfg[nCurrLvlIdx].vddq > pVddqCfg[nNewLvlIdx].vddq)
  {
    pm_status = pm_smps_volt_level(PMIC_VDDQ,  PMIC_VDDQ_SMPS, pVddqCfg[nNewLvlIdx].vddq, TRUE);
    if(pm_status != PM_ERR_FLAG_SUCCESS)
    {
      return FALSE;
    }
  }

  // Change VDDA_EBI rail if decrease
  if ( pMCCfg[nCurrLvlIdx].vdda > pMCCfg[nNewLvlIdx].vdda )
  {
    vdda = DDR_MapCorner( pMCCfg[nNewLvlIdx].vdda );
    railway_corner_vote( ebi_pin, vdda );
    railway_transition_rails();
  }
  if (pMCCfg[nCurrLvlIdx].pmic_mode_cfg > pMCCfg[nNewLvlIdx].pmic_mode_cfg)
  {
    pm_status = pm_smps_volt_level(PMIC_VDD2H, PMIC_VDD2H_SMPS, ddr_driver_struct->aop_params->aop_pmic_settings[2].values[pMCCfg[nNewLvlIdx].pmic_mode_cfg] * 1000, TRUE);
    if (pm_status != PM_ERR_FLAG_SUCCESS)
    {
      return FALSE;
    }
  }

  DDR_PerfLvl = nNewLvlIdx;
  DDR_FreqKHz = pMCCfg[nNewLvlIdx].freq_khz;
  return TRUE;
}

/* ============================================================================
**  Function : ddr_post_init
** ============================================================================
*/
/*!
*   @brief
*   This function is called after ddr is initialized. It will take care of any
*   post initialization activities such as ddr training.
*
*   @details
*   This function is called after ddr is initialized. It will take care of any
*   post initialization activities such as ddr training.
*
*   @param
*   boolean -
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
boolean ddr_post_init()
{
  char ddr_log_string[DDR_LOG_LEN];
  uint32 i , size_cs0 = 0, size_cs1 = 0;
  pm_err_flag_type pm_status;
  uint32 value = 0;
  uint64 disable_mask = 0;
  
  DalPlatformInfoPlatformType platform = DalPlatformInfo_Platform();
  memset((void*)ddr_driver_struct, 0x0, sizeof(DDR_DRIVER_STRUCT));
  init_aop_params();

  snprintf (ddr_log_string, DDR_LOG_LEN, "DSF version = %03d.%02d.%02d",
            ((ddr_shared_data->dsf_code_version) >> 16),(((ddr_shared_data->dsf_code_version) & 0x0000FF00)>>8), ((ddr_shared_data->dsf_code_version) & 0x000000FF));

  boot_log_message(ddr_log_string);
  
  snprintf (ddr_log_string, DDR_LOG_LEN, "Manufacturer ID = 0x%x, Device Type = 0x%x", ddr_shared_data->device_params.manufacturer_id,
            ddr_shared_data->device_params.device_type);
  boot_log_message(ddr_log_string);
  
  for (i = 0; i < ddr_get_max_channels(); i++)
  {
    size_cs0+= ddr_shared_data->ddr_size_info.ddr_cs0_mb[i];
    size_cs1+= ddr_shared_data->ddr_size_info.ddr_cs1_mb[i];
  }
  snprintf (ddr_log_string, DDR_LOG_LEN, "Rank 0 size = %d MB, Rank 1 size = %d MB", size_cs0, size_cs1);
  boot_log_message(ddr_log_string);
  
  if (platform != DALPLATFORMINFO_TYPE_RUMI)
  {
    if(g_boot_mode == 0 ) //if (PcdGet32 (PcdBuildType) == 0)
    {
      railway_corner_vote(ebi_pin, RAILWAY_NO_REQUEST);
      railway_transition_rails();
    }
    // Clock_SetBIMCSpeed(300000);
    // print_ddr_frequency();
  }
    /* Set VDDQ initially to 0.5 V for LP5 until DDR training is done*/
	if (ddr_shared_data->device_params.device_type == DDR_TYPE_LPDDR5)
	{
      pm_status = pm_smps_volt_level(PMIC_VDDQ,  PMIC_VDDQ_SMPS, 500000, TRUE);
	
      if (pm_status != PM_ERR_FLAG_SUCCESS)
      {
        return FALSE;
      }
	}
	//Call to disable MTE
    disable_mask = DDR_FW_DISABLE_MTE;
    value =HAL_DDR_FW_IOCTL(DDR_FW_IOW_Disable_Features, &disable_mask, sizeof(disable_mask));
	  
	return TRUE;
}

uint8 ddr_max_enabled_freq()
{
   uint8 index=0;
   uint8 num_levels = ddr_shared_data->num_ddr_levels;
   for (index = num_levels-1; index >= 0; index--)
   {
     if (ddr_driver_struct->aop_params->mc_states[index].freq_enable == TRUE)
       break;
   } 
   return index;
}

void print_ddr_frequency()
{
  uint32 clk_period;
  char ddr_freq[70];
  
  clk_period = HWIO_MC_BROADCAST_ORMC5_GLOBAL_DDR_CLK_PERIOD_CFG_INM(HWIO_MC_BROADCAST_ORMC5_GLOBAL_DDR_CLK_PERIOD_CFG_DDR_CLK_PERIOD_BMSK);
  snprintf (ddr_freq, 70, "Current DDR Freq = %d MHz", 1000000/clk_period);
  boot_log_message(ddr_freq);
  snprintf (ddr_freq, 70, "Max enabled DDR Freq = %d MHz", (ddr_driver_struct->aop_params->mc_states[ddr_max_enabled_freq()].freq_khz/1000));
  boot_log_message(ddr_freq);
}

/* ============================================================================
**  Function : ddr_pre_clock_switch
** ============================================================================
*/
/*!
*   @brief
*   This function is called right before clock switching occures.
*   The function will configure the ddr such that no data loss will occur
*
*   @details
*   DDR will be stalled and new timing parameter is loaded into shadow.
*   Depending on bumping up or stepping down clock speed, we will load the
*   shadow register value to actual registers before or after clock switch
*   has occurred.
*
*   @param curr_clk   -   [IN] the current clock speed
*   @param new_clk    -  [IN] the clock speed we are switching to
*   @param new_clk    -  [IN] interface to switch clock for
*
*   @par Dependencies
*
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/

void ddr_pre_clock_switch(uint32 curr_clk, uint32 new_clk)
{
  uint8 clk_idx = HAL_CORE_SW_Get_Nearest_Enabled_Clock_Index(ddr_shared_data->ddr_aop_params.ptr->mc_states, ddr_shared_data->num_ddr_levels, new_clk);
  HAL_DDR_FW_DDR_Freq_Switch_Prework(clk_idx);
} /* ddr_pre_clock_switch */


/* ============================================================================
**  Function : ddr_clock_switch
** ============================================================================
*/
/*!
*   @brief
*   This function is called right after pre clock switching function.
*   The function will actually do the real clock switch
*
*   @details
*   DDR will be stalled and new timing parameter is loaded into shadow.
*   Depending on bumping up or stepping down clock speed, we will load the
*   shadow register value to actual registers before or after clock switch
*   has occurred.
*
*   @param curr_clk   -   [IN] the current clock speed
*   @param new_clk    -  [IN] the clock speed we are switching to
*   @param new_clk    -  [IN] interface to switch clock for
*
*   @par Dependencies
*
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/

void ddr_clock_switch(uint32 curr_clk, uint32 new_clk)
{
  uint8 clk_idx = HAL_CORE_SW_Get_Nearest_Enabled_Clock_Index(ddr_shared_data->ddr_aop_params.ptr->mc_states, ddr_shared_data->num_ddr_levels, new_clk);
  HAL_DDR_FW_DDR_Freq_Switch_Work(clk_idx);
} /* ddr_clock_switch */


/* ============================================================================
**  Function : ddr_post_clock_switch
** ============================================================================
*/
/*!
*   @brief
*   This function is called right after clock switching occurs.
*   The function will configure the ddr such that no data loss will occur
*
*   @details
*   DDR will be unstalled.
*   Depending on bumping up or stepping down clock speed, we will load the
*   shadow register value to actual registers before or after clock switch
*   has occurred.
*
*   @param curr_clk          -  [IN] the current clock speed
*   @param new_clk           -  [IN] the clock speed we are switching to
*   @param interface_name    -  [IN] interface to switch clock for
*
*   @par Dependencies
*   This code has to be on IRAM because ddr is unavailable during clock switching
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/

void ddr_post_clock_switch(uint32 curr_clk, uint32 new_clk)
{
     uint8 clk_idx = HAL_CORE_SW_Get_Nearest_Enabled_Clock_Index(ddr_shared_data->ddr_aop_params.ptr->mc_states, ddr_shared_data->num_ddr_levels, new_clk);
     HAL_DDR_FW_DDR_Freq_Switch_Postwork(clk_idx);
} /* ddr_post_clock_switch */

/* ============================================================================
**  Function : ddr_pre_vddmx_switch
** ============================================================================
*/
/*!
*   @brief
*   This function is called right before voltage switch occurs.
*
*   @param vddmx_microvolts - vddmx voltage in microvolts
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/

void ddr_pre_vddmx_switch(uint32 vddmx_microvolts)
{
  /* Stepping Down in VDDCX voltage */
  ddr_status.vddmx_voltage = vddmx_microvolts;
} /* ddr_pre_vddmx_switch */

/* ============================================================================
**  Function : ddr_post_vddmx_switch
** ============================================================================
*/
/*!
*   @brief
*   This function is called right after voltage switch occurs.
*
*   @param vddmx_microvolts - vddmx voltage in microvolts
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/

void ddr_post_vddmx_switch(uint32 vddmx_microvolts)
{

} /* ddr_post_vddmx_switch */

/* ============================================================================
**  Function : ddr_pre_vddcx_switch
** ============================================================================
*/
/*!
*   @brief
*   This function is called right before vddcx switch.
*
*   @param settings - contains the VDDCX voltage level we just switched to
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/
void ddr_pre_vddcx_switch(uint32 vddcx_microvolts)
{
} /* ddr_pre_vddcx_switch */

/* ============================================================================
**  Function : ddr_post_vddcx_switch
** ============================================================================
*/
/*!
*   @brief
*   This function is called right after VDDCX is switched
*
*   @param none
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/

void ddr_post_vddcx_switch(uint32 vddcx_microvolts)
{
} /* ddr_post_vddcx_switch */

/* ============================================================================
**  Function : ddr_pre_xo_shutdown
** ============================================================================
*/
/**
*   @brief
*   Called right before XO shutdown. Puts DDR into self refresh mode and
*   disables CDC and I/O calibration.
*
*   @param[in]  clk_speed    Current clock speed
*
*   @return
*   None
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   ddr_post_xo_shutdown
*/

void ddr_pre_xo_shutdown(uint32 clk_speed)
{
  ddr_enter_self_refresh_all(clk_speed);
} /* ddr_pre_xo_shutdown */

/* ============================================================================
**  Function : ddr_post_xo_shutdown
** ============================================================================
*/
/**
*   @brief
*   Called right after XO wakeup. Takes DDR out of self refresh mode and enables
*   CDC and I/O calibration.
*
*   @param[in]  clk_speed    Current clock speed
*
*   @return
*   None
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   ddr_pre_xo_shutdown
*/

void ddr_post_xo_shutdown(uint32 clk_speed)
{
  ddr_exit_self_refresh_all(clk_speed);

} /* ddr_post_xo_shutdown */

/* ============================================================================
**  Function : ddr_check_partition
** ============================================================================
*/
/*!
*   @brief
*   A helper function for ddr_dmm_partition to check the given interface and partition
*   whether we can put into dpd or full\partial self refresh
*
*   @details
*   Given the retention and active state, put the corresponding ddr interface
*   into self refresh, or deep power down when possible
*
*   Truth table for active and retention state:
*                        Active State:0         |      Active_state:1
*   Retention_state:0    self refresh/dpd       |      Invalid config, assume to be
*                                               |      Active retention
*   Retention_state:1    self refresh retention |      Active Retention
*
*   @param interface_name   -  [IN] the interface to check for
*   @param chip_sel         -  [IN] the chip select on the interface to check for
*   @param retention_state  -  [IN] the retention state for the partitions given
*   @param active_state     -  [IN] the active state for the partitions given
*   @param num_partitions   -  [IN] the number of partitions on this interface
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval
*   None
*
*   @sa None
*/
void ddr_check_partition(DDR_CHANNEL interface_name, DDR_CHIPSELECT chip_sel, uint32 retention_state, uint32 active_state, uint8 num_partitions)
{

} /* ddr_check_partition */

/* ============================================================================
**  Function : ddr_dmm_partition
** ============================================================================
*/
/*!
*   @brief
*   Given the retention and active state, put the corresponding ddr interface
*   into self refresh, or deep power down when possible
*
*   @details
*   Given the retention and active state, put the corresponding ddr interface
*   into self refresh, or deep power down when possible
*
*   Truth table for active and retention state:
*                        Active State:0         |      Active_state:1
*   Retention_state:0    self refresh/dpd       |      Invalid config, assume to be
*                                               |      Active retention
*   Retention_state:1    self refresh retention |      Active Retention
*
*   @param retention_state  -  [IN] the retention state for the partitions given
*   @param active_state     -  [IN] the active state for the partitions given
*
*   @par Dependencies
*   Caller of this API has to take care not to put ddr interface that is in use
*   into self refresh or deep power down.
*
*   @par Side Effects
*   None
*
*   @retval
*  None
*
*   @sa None
*/

void ddr_dmm_partition(uint32 retention_state, uint32 active_state)
{
}
/* =============================================================================
**  Function : ddr_params_is_training_required
** =============================================================================
*/
/**
*   @brief
*   Indicate whether DDR parameter training is required or not. Training is
*   required if and only if DDR itself (e.g. PCDDR3) requires parameter training
*   and DDR parameter partition is invalid. LPDDR3 will always require training syncronization
*   to be done between rpm and sbl
*
*   @param  None
*
*   @retval  TRUE   Training required
*   @retval  FALSE  Training not required
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
boolean ddr_params_is_training_required( void )
{
  DalPlatformInfoPlatformType platform;
  platform = DalPlatformInfo_Platform();
  boolean training_required;
  
  if ((platform != DALPLATFORMINFO_TYPE_RUMI) &&
      (platform != DALPLATFORMINFO_TYPE_VIRTIO))
  {
		training_required = LP5_TRAINING_ENABLED;
  }
  else
  {
    training_required = FALSE;
  }
  return training_required;
} /* ddr_params_is_training_required */


/* ============================================================================
**  Function : ddr_is_training_required
** ============================================================================
*/
/*!
*   @brief
*   This function will parse the crc hash and determine if training is required
*   based on serial number, mx\cx\rbcpr hash
*
*   @details
*   This function will parse the crc hash and determine if training is required
*   based on serial number, mx\cx\rbcpr hash
*
*   @param
*   None
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval  boolean - Training required/Not required
*
*   @sa None
*/
boolean ddr_is_training_required(void)
{
  uint32 serial_number;

  /* cx/mx/vdda hash variables */
  uint32 combined_checksum = cpr_cx_mx_settings_checksum();

  /* compare checksum for training data in our partition with DDR_STRUCT to see if training is required */
  serial_number =  ChipInfo_GetSerialNumber(); //HWIO_IN(SP_CNOC_SP_SCSR_SERIAL_NUM); 

  HAL_EXT_CORE_SW_DDR_printf ( DDR_NORMAL, "DDR: The serial number is 0x%x", serial_number);

  /* combine serial number with voltage checksum for a new seed */
  combined_checksum = serial_number ^ combined_checksum;
  

  HAL_EXT_CORE_SW_DDR_printf (DDR_NORMAL, "DDR: Checksum on flash is %d", ddr_shared_data->flash_params.ptr->checksum);
  HAL_EXT_CORE_SW_DDR_printf (DDR_NORMAL, "DDR: Recomputed checksum is %d", HAL_CORE_SW_Get_Training_Checksum(ddr_shared_data, combined_checksum));


  if (ddr_shared_data->flash_params.ptr->checksum  != HAL_CORE_SW_Get_Training_Checksum(ddr_shared_data, combined_checksum))
  {
    HAL_EXT_CORE_SW_DDR_printf (DDR_NORMAL, "DDR: Training is required");

    return TRUE;
  }

  HAL_EXT_CORE_SW_DDR_printf (DDR_NORMAL, "DDR: Training is not required");
  return FALSE;
} /* ddr_is_training_required */

/* =============================================================================
**  Function : ddr_do_phy_training_init
** =============================================================================
*/
/**
*   @brief
*   Indicates that PHY training needs to be done in SBL1.
*
*   @param  None
*
*   @retval  None
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
void ddr_do_phy_training_init( void )
{
  char ddr_log_string[50];
  snprintf(ddr_log_string, 50, "DDR: Start of DDR Training Init");
  boot_log_message(ddr_log_string);
  HAL_DDR_FW_Train();    
  DDR_SetBIMCSpeed(ddr_search_nominal_freq());
  print_ddr_frequency();
  snprintf(ddr_log_string, 50, "DDR: End of DDR Training Init");
  boot_log_message(ddr_log_string);
} /* ddr_do_phy_training */

/* =============================================================================
**  Function : ddr_do_phy_training_restore
** =============================================================================
*/
/**
*   @brief
*   Restore training data results, if phy training is already done
*
*   @param  None
*
*   @retval  TRUE   Training required
*   @retval  FALSE  Training not required
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
boolean ddr_do_phy_training_restore( void )
{
  boolean return_status = 0;
  uint32 ott_enable_dt_flag;
  ddr_devicetree_helper_uint32("ddr_trng_always_en", "/soc/ddr_target_dt", &ott_enable_dt_flag);
  dt_target_entries.ddr_trng_always_en = ott_enable_dt_flag;
  /* If DDR detected is LP5 */
  if (ddr_shared_data->device_params.device_type == DDR_TYPE_LPDDR5)
  {
    if(dt_target_entries.ddr_trng_always_en == 0)
    {
    #if LP5_ONE_TIME_TRAINING
      char ddr_log_string[50];  
      if (ddr_is_training_required())
      {
    #endif
        memset(ddr_shared_data->flash_params.ptr, 0x0, sizeof(struct ddr_params_partition));  
        return_status = TRUE;
    #if LP5_ONE_TIME_TRAINING
      }
      else 
      {
         snprintf(ddr_log_string, 50, "DDR: Start of DDR Training Restore");
         boot_log_message(ddr_log_string);
         HAL_DDR_FW_Restore();
         DDR_SetBIMCSpeed(ddr_search_nominal_freq());
         print_ddr_frequency();
         snprintf(ddr_log_string, 50, "DDR: End of DDR Training Restore");
         boot_log_message(ddr_log_string);
         return_status = FALSE;
      }
    #endif
    }
    else
    {
        memset(ddr_shared_data->flash_params.ptr, 0x0, sizeof(struct ddr_params_partition));  
        return_status = TRUE;
    }
    return return_status;
  }
  else
  {
    #if LP4_ONE_TIME_TRAINING
    char ddr_log_string[50];  
    if (ddr_is_training_required())
    {
    #endif
        memset(ddr_shared_data->flash_params.ptr, 0x0, sizeof(struct ddr_params_partition));  
        return TRUE;
    #if LP4_ONE_TIME_TRAINING
    }
    else 
    {
         snprintf(ddr_log_string, 50, "DDR: Start of DDR Training Restore");
         boot_log_message(ddr_log_string);
         HAL_DDR_FW_Restore();
         DDR_SetBIMCSpeed(ddr_search_nominal_freq());
         print_ddr_frequency();
         snprintf(ddr_log_string, 50, "DDR: End of DDR Training Restore");
         boot_log_message(ddr_log_string);
         return FALSE;
    }
    #endif
  }
} /* ddr_do_phy_training */

/* =============================================================================
**  Function : ddr_post_training
** =============================================================================
*/
/**
*   @brief
*   This function is called after ddr training. It will take care of all post
*   training activities such as computing checksum over training data.
*
*   @param  None
*
*   @retval  TRUE If one time training is enabled
*   @retval  FALSE If one time training is disabled
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
boolean ddr_post_training(void)
{
  uint32 serial_number;
  char ddr_log_string[50];
  // uint8 min_ddr_freq = 0;
  // uint8 max_ddr_freq = 8;
  uint32 combined_checksum = cpr_cx_mx_settings_checksum();

  serial_number = ChipInfo_GetSerialNumber(); //HWIO_IN(SP_CNOC_SP_SCSR_SERIAL_NUM);
  snprintf(ddr_log_string, 50, "DDR: serial # 0x%x",serial_number);
  boot_log_message(ddr_log_string);

  /* combine serial number with voltage checksum for a new seed */
  combined_checksum = serial_number ^ combined_checksum;

  /* update training data checksum */
  ddr_shared_data->flash_params.ptr->checksum = HAL_CORE_SW_Get_Training_Checksum(ddr_shared_data, combined_checksum);

  if (ddr_shared_data->device_params.device_type == DDR_TYPE_LPDDR5)
  return LP5_ONE_TIME_TRAINING;
  else
  return LP4_ONE_TIME_TRAINING;
}

/*===========================================================================

**  Function :  ddr_post_setup

** ==========================================================================
*/
/*!
* 
* @brief
*    Function which gets executed after DDR setup operations are complete
* 
* @par Dependencies
*   None
*   
* @retval. 
*    None
* @par Side Effects
*   None
*/

void ddr_post_setup()
{
  char mte_log_str[110],ch;	
  uint32 size=0x8000;
  volatile uint32 *datavalptr = (uint32*) MTE_DATA;
  volatile uint32 *syndromevalptr = (uint32*) MTE_SYNDROME;
  volatile uint32 val_pre=0,val_post=0;

  if(g_boot_mode == BOOT_MODE_DEVICEPROGRAMMER ) //if (PcdGet32 (PcdBuildType) == SBL_BUILD_DEVICEPROGRAMMER_DDR)
  {
    return;
  }
  if(g_boot_mode !=  BOOT_MODE_RAMDUMP ) //if (!boot_dload_is_dload_mode_set()) 
  {
    // Load normal Vddq plan
    fill_aop_params();
    //DDR_SetBIMCSpeed(768000);
    DDR_SetBIMCSpeed(1555000);
    if(ddr_shared_data->ioctl_enabled_features & DDR_FW_DISABLE_MTE){
      snprintf(mte_log_str, 110, "IOCTL MTE state = 0x%x ", ddr_shared_data->ioctl_enabled_features & DDR_FW_DISABLE_MTE);  
      boot_log_message(mte_log_str);
      /*
      *  MTE test
      */
      *datavalptr = (ddr_shared_data->lcp_addr_regions[0].start << 0x10); //left shift by 4 bits, add 0x0000 to get data start address 
      *syndromevalptr = (ddr_shared_data->lcp_addr_regions[1].start << 0x10); //left shift by 4 bits, add 0x0000 to get syndrome start address 
       
       val_pre = *syndromevalptr ; //read MTE tag before writing to MTE
       ch = val_pre+1;
       memset((void*)datavalptr, ch, size);//write 4k data to flush the cache and update icemem region
       val_post = *syndromevalptr ; //read icemem data after writing to icemem
       if(val_post != val_pre)
         snprintf(mte_log_str, 110, "MTE TEST passed");
       else
         snprintf(mte_log_str, 110, "MTE TEST failed");
         boot_log_message(mte_log_str); 
       }
       else
       {
          snprintf(mte_log_str, 110, "IOCTL LCP enabled feature set = 0x%x ", ddr_shared_data->ioctl_enabled_features);  
          boot_log_message(mte_log_str);	  
        }
        /*if (ddr_shared_data->device_params.device_type == DDR_TYPE_LPDDR5)
        {
                DDR_SetBIMCSpeed(ddr_search_nominal_freq());
        }
        else
        {
                DDR_SetBIMCSpeed(ddr_search_nominal_freq());
        }*/
    }

//Reference code for setting a particular frequency for debugging. Enable the flag when needed
#if DDR_FREQ_SET_EN
   uint8 min_ddr_freq = 0;
   uint8 max_ddr_freq = 0;
   uint8 index=0;
   uint8 num_levels = ddr_shared_data->num_ddr_levels;
   for (index = num_levels-1; index >= 0; index--)
   {
     if (ddr_driver_struct->aop_params->mc_states[index].freq_enable == TRUE)
       break;
   } 
   max_ddr_freq = index;
   min_ddr_freq = 2;
   max_ddr_freq = 2;
  if(ddr_shared_data->chip_version == 0x200)
   ddr_freq_set_min_max(min_ddr_freq, max_ddr_freq);
#endif
   /* Put LLCC in cacheable mode. Do this WA in DDR driver till DSF moves it inside their code */
  //HAL_DDR_LLCC_cacheable_mode_override_ctrl(DDR_CH_ALL_TEST, CACHEABLE);
}

/*DDDR memory mapping block defined in memory map */
typedef struct 
{
   uint64 start_address;
   uint64 size;
}dram_mmap_blocks_table;

/* 2 MEM MAP BLOCKS */
dram_mmap_blocks_table dram_mmap_table[] =
{
 /* DRAM MMAP block1 */ {  0x80000000,  0x80000000}, /* Base 0x8000_0000   Size 2 GB*/
 /* DRAM MMAP block2 */ { 0x800000000, 0x800000000}  /* Base 0x8_0000_0000 Size 32 GB*/
};

void ddr_regions_remapper(void)
{
  uint64 ddr_cs0_address=0, ddr_cs1_address=0;
  uint64 ddr_cs0_size=0, ddr_cs1_size=0;
  icbcfg_remap_info_type remap_info;
  uint8 index=0, i=0, region_idx=0, cs=0;
  uint64 src_address=0, dest_address=0, remap_size=0;
  uint64 cs_size=0, cs_address=0;


  ddr_cs0_size = (uint64)(ddr_system_size.ddr_cs0[0])*1024*1024;
  ddr_cs1_size = (uint64)(ddr_system_size.ddr_cs1[0])*1024*1024;
  ddr_cs0_address = ddr_shared_data->ddr_size_info.ddr_cs0_addr[0];
  ddr_cs1_address = ddr_shared_data->ddr_size_info.ddr_cs1_addr[0];
  ddr_driver_struct->ddr_regions_info.ddr_rank0_size = ddr_system_size.ddr_cs0[0];
  ddr_driver_struct->ddr_regions_info.ddr_rank1_size =  ddr_system_size.ddr_cs1[0];
  /* Memory mapping blocks */
  ddr_driver_struct->memmap_info.no_of_blocks = (sizeof(dram_mmap_table)/sizeof(dram_mmap_table[0]));
  for(i=0; i< ddr_driver_struct->memmap_info.no_of_blocks; i++)
  {
     ddr_driver_struct->memmap_info.memmap[i].start_address = dram_mmap_table[i].start_address; 
     ddr_driver_struct->memmap_info.memmap[i].size          = dram_mmap_table[i].size; 
  }

  for(cs=0,i=0; cs<2; cs++)
  {
    /* Map DDR rank0 */
    if(cs==0)
    {
       cs_size    = ddr_cs0_size;
       cs_address = ddr_cs0_address;
    }
    /* Map DDR rank1 */
    if(cs==1)
    {
        cs_size    = ddr_cs1_size;
        cs_address = ddr_cs1_address;
    }
    /*Map DDR Rank0 first, followed by DDR Rank1 */
    while(cs_size!=0 && i<ddr_driver_struct->memmap_info.no_of_blocks)
    {
        src_address = cs_address;
        dest_address = ddr_driver_struct->memmap_info.memmap[i].start_address;
        if(cs_size <= ddr_driver_struct->memmap_info.memmap[i].size)
        {
          remap_size = cs_size;
        }
        else
        {
          remap_size = ddr_driver_struct->memmap_info.memmap[i].size;
        }
        cs_size -= remap_size;
        cs_address += remap_size;
        ddr_driver_struct->memmap_info.memmap[i].start_address +=  remap_size;
        ddr_driver_struct->memmap_info.memmap[i].size -= remap_size;
        /*If the memory map block becomes 0; move to next mem map block*/
        if(ddr_driver_struct->memmap_info.memmap[i].size == 0)
        {
          i=i+1;
        }
        /*Update DDR region info*/
        ddr_driver_struct->ddr_regions_info.ddr_region[region_idx].mc_address = src_address;
        ddr_driver_struct->ddr_regions_info.ddr_region[region_idx].start_address = dest_address;
        ddr_driver_struct->ddr_regions_info.ddr_region[region_idx].size = remap_size;
        if(cs == 0)
        {
          ddr_driver_struct->ddr_regions_info.ddr_region[region_idx].ddr_rank = DDR_CS0; 
        }
        if(cs == 1)
        {
          ddr_driver_struct->ddr_regions_info.ddr_region[region_idx].ddr_rank = DDR_CS1; 
        }
            region_idx++;
    }
  }

    /* Update the no of DDR regions in the structure */
    ddr_driver_struct->ddr_regions_info.no_of_ddr_regions = region_idx;

    /* Map the DDR regions using ICB API */
    for(region_idx=0 ; region_idx < ddr_driver_struct->ddr_regions_info.no_of_ddr_regions; region_idx++) 
    {
      remap_info.dest_addr    = ddr_driver_struct->ddr_regions_info.ddr_region[region_idx].start_address;
      remap_info.src_addr     = ddr_driver_struct->ddr_regions_info.ddr_region[region_idx].mc_address;
      remap_info.size         = ddr_driver_struct->ddr_regions_info.ddr_region[region_idx].size;
      remap_info.interleaved  = ICBCFG_REMAP_INTERLEAVE_DEFAULT;
      remap_info.deinterleave = FALSE;
      ICB_RemapEx("/dev/icbcfg/boot", &ddr_physical_size, region_idx, &remap_info);
    }
 
    /* Update remapped address for DDR CS0 */
    for (i = 0; i < ddr_get_max_channels(); i++)
    {
       ddr_shared_data->ddr_size_info.ddr_cs0_remapped_addr[i] = ddr_system_size.ddr_cs0_addr[i] = 
       ddr_driver_struct->ddr_regions_info.ddr_region[0].start_address;
    }

    /* Update remapped address for DDR CS1 */
    if(ddr_driver_struct->ddr_regions_info.ddr_rank1_size != 0)
    {
       /* Find the index of first DDR CS1 region */
       for(index=0; index<ddr_driver_struct->ddr_regions_info.no_of_ddr_regions; index++)
       {
          if(ddr_driver_struct->ddr_regions_info.ddr_region[index].ddr_rank == DDR_CS1)
             break;
       }
       for (i = 0; i < ddr_get_max_channels(); i++)
       {
          ddr_shared_data->ddr_size_info.ddr_cs1_remapped_addr[i] = ddr_system_size.ddr_cs1_addr[i] =
          ddr_driver_struct->ddr_regions_info.ddr_region[index].start_address;
       }
    }
    /* Update CS0 and CS1 start address */
    ddr_driver_struct->ddr_regions_info.ddr_cs0_start_addr = ddr_shared_data->ddr_size_info.ddr_cs0_remapped_addr[0];
    ddr_driver_struct->ddr_regions_info.ddr_cs1_start_addr = ddr_shared_data->ddr_size_info.ddr_cs1_remapped_addr[0];
} /* ddr_remapper */

void ddr_regions_remapper_16GB(void)
{
  uint64 ddr_cs0_address=0, ddr_cs1_address=0;
  uint64 ddr_cs0_size=0, ddr_cs1_size=0;
  icbcfg_remap_info_type remap_info;
  uint8 index=0, i=0, region_idx=0;

  ddr_cs0_size = (uint64)(ddr_system_size.ddr_cs0[0])*1024*1024;
  ddr_cs1_size = (uint64)(ddr_system_size.ddr_cs1[0])*1024*1024;
  ddr_cs0_address = ddr_shared_data->ddr_size_info.ddr_cs0_addr[0];
  ddr_cs1_address = ddr_shared_data->ddr_size_info.ddr_cs1_addr[0];
  ddr_driver_struct->ddr_regions_info.ddr_rank0_size = ddr_system_size.ddr_cs0[0];
  ddr_driver_struct->ddr_regions_info.ddr_rank1_size =  ddr_system_size.ddr_cs1[0];
  /* Memory mapping blocks */
  ddr_driver_struct->memmap_info.no_of_blocks = 2;                       /* 2 MEM MAP BLOCKS */
  ddr_driver_struct->memmap_info.memmap[0].start_address = 0x80000000;   /* Base 0x8000_0000 */
  ddr_driver_struct->memmap_info.memmap[0].size          = 0x80000000;   /* 2 GB*/
  ddr_driver_struct->memmap_info.memmap[1].start_address = 0x800000000;  /* Base 0x8_0000_0000 */
  ddr_driver_struct->memmap_info.memmap[1].size          = 0x800000000;  /* 32 GB*/ 
  
  /* Update the no of DDR regions in the structure */
  ddr_driver_struct->ddr_regions_info.no_of_ddr_regions = 2;
  ddr_driver_struct->ddr_regions_info.ddr_region[0].mc_address = ddr_cs0_address;
  ddr_driver_struct->ddr_regions_info.ddr_region[0].start_address = 0x80000000;
  ddr_driver_struct->ddr_regions_info.ddr_region[0].size = 0x200000000;
  ddr_driver_struct->ddr_regions_info.ddr_region[0].ddr_rank = DDR_CS0; 
  ddr_driver_struct->ddr_regions_info.ddr_region[1].mc_address = ddr_cs1_address;
  ddr_driver_struct->ddr_regions_info.ddr_region[1].start_address = 0x800000000;
  ddr_driver_struct->ddr_regions_info.ddr_region[1].size = 0x200000000;
  ddr_driver_struct->ddr_regions_info.ddr_region[1].ddr_rank = DDR_CS1; 

    /* Map the DDR regions using ICB API */
    for(region_idx=0 ; region_idx < ddr_driver_struct->ddr_regions_info.no_of_ddr_regions; region_idx++) 
    {
      remap_info.dest_addr    = ddr_driver_struct->ddr_regions_info.ddr_region[region_idx].start_address;
      remap_info.src_addr     = ddr_driver_struct->ddr_regions_info.ddr_region[region_idx].mc_address;
      remap_info.size         = ddr_driver_struct->ddr_regions_info.ddr_region[region_idx].size;
      remap_info.interleaved  = ICBCFG_REMAP_INTERLEAVE_DEFAULT;
      remap_info.deinterleave = FALSE;
      ICB_RemapEx("/dev/icbcfg/boot", &ddr_physical_size, region_idx, &remap_info);
    }
 
    /* Update remapped address for DDR CS0 */
    for (i = 0; i < ddr_get_max_channels(); i++)
    {
       ddr_shared_data->ddr_size_info.ddr_cs0_remapped_addr[i] = ddr_system_size.ddr_cs0_addr[i] = 
       ddr_driver_struct->ddr_regions_info.ddr_region[0].start_address;
    }

    /* Update remapped address for DDR CS1 */
    if(ddr_driver_struct->ddr_regions_info.ddr_rank1_size != 0)
    {
       /* Find the index of first DDR CS1 region */
       for(index=0; index<ddr_driver_struct->ddr_regions_info.no_of_ddr_regions; index++)
       {
          if(ddr_driver_struct->ddr_regions_info.ddr_region[index].ddr_rank == DDR_CS1)
             break;
       }
       for (i = 0; i < ddr_get_max_channels(); i++)
       {
          ddr_shared_data->ddr_size_info.ddr_cs1_remapped_addr[i] = ddr_system_size.ddr_cs1_addr[i] =
          ddr_driver_struct->ddr_regions_info.ddr_region[index].start_address;
       }
    }
    /* Update CS0 and CS1 start address */
    ddr_driver_struct->ddr_regions_info.ddr_cs0_start_addr = ddr_shared_data->ddr_size_info.ddr_cs0_remapped_addr[0];
    ddr_driver_struct->ddr_regions_info.ddr_cs1_start_addr = ddr_shared_data->ddr_size_info.ddr_cs1_remapped_addr[0];
} /* ddr_remapper */

/* =============================================================================
**  Function : ddr_remapper
** =============================================================================
*/
/**
*   @brief
*   configures ddr to be remapped based on density
*
*   @param void
*
*   @retval  void
*
*   @dependencies
*   ddr initialization has already finished
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
void ddr_remapper(void)
{
    ddr_regions_remapper();
} /* ddr_remapper */

/* =============================================================================
**  Function : get_clk_period_regaddr
** =============================================================================
*/
/**
*   @brief
*   Get the DDR clock period register.
*
*   @param void
*
*   @retval  void
*
*   @dependencies
*   clk_period_regaddr
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
uint32* get_clk_period_regaddr()
{
	uint32 *clock_addr = 0;
	
	clock_addr = (uint32*)HWIO_MCCC_CLK_PERIOD_ADDR;
	return clock_addr;
}

/* =============================================================================
**  Function : get_ssr_cookie_addr
** =============================================================================
*/
/**
*   @brief
*   Get the SSR cookie addr
*
*   @param void
*
*   @retval  void
*
*   @dependencies
*   SSR cookie address
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
uint32* get_ssr_cookie_addr()
{
	uint32 *ssr_cookie_addr = 0;
	
	ssr_cookie_addr = (uint32*)SDI_DDR_IMEM_START_ADDR;
	return ssr_cookie_addr;
}
/* =============================================================================
**  Function : ddr_get_syndrome_regions
** =============================================================================
*/
/**
*   @brief
*   return the LCP(MTE) tag area start and size .. NOTE : MTE Tag area has to be a contiguous chunk of memory
*
*   @param  syndrome_start_addr[out]  - start address 
*   @param  syndrome_size[out]        - cumulative size of all tag regions (contiguous)
*   @param  region_count[out]         - if MTE is not enabled, then region_count will be zero, otherwise non-zero.
*
*   @retval  BL_ERR_NONE         if MTE is enabled
*   @retval  bl_error_boot_type  if MTE is enabled but syndrome regions are non-contiguous or params error
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
bl_error_boot_type ddr_get_syndrome_regions(struct syndrome_struct *tag, uint32 *region_count)
{
    uint32 idx=0,ret_idx=0;
    uint64 curr_reg_startaddr=0x0, curr_reg_endaddr=0x0,size=0x0, total_size=0x0, prev_reg_endaddr=0x0;
    bl_error_boot_type status = BL_ERR_NONE;
    
    //Check whether MTE is enabled or not . DDR_FW_DISABLE_MTE, 
    //and if MTE is enabled ioctl_enabled_features would be 4
    if (tag == NULL || region_count == NULL || ddr_shared_data == NULL)
    {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_DDR, BL_ERR_NULL_PTR_PASSED);
        goto exit;
    }
    if(ddr_shared_data->ioctl_enabled_features & DDR_FW_DISABLE_MTE)
    {    
        
        for (idx = 0; (idx < MAX_NUM_LCP_ADDR_REGIONS) && (ret_idx <NUM_OF_SYNDROME_REGIONS); idx++){
            if(ddr_shared_data->lcp_addr_regions[idx].attr == 0x8)//checking only tag regions
            {
                curr_reg_startaddr = (ddr_shared_data->lcp_addr_regions[idx].start << 0x10); //left shift by 4 bits, add 0x0000 to start address 
                curr_reg_endaddr = (ddr_shared_data->lcp_addr_regions[idx].end<< 0x10) | 0xFFFF; //left shift by 4 bits, add 0xFFFF to end address 
                size = (curr_reg_endaddr - curr_reg_startaddr) + 1;
                total_size =  total_size + size;
                if(curr_reg_startaddr !=  prev_reg_endaddr + 1)
                { //non-contiguous regions
                    *(&tag->start_addr + ret_idx) = (uint64)curr_reg_startaddr;
                    *(&tag->size+ret_idx) = (uint64)size;
                    if(prev_reg_endaddr!=0)
                    {//first region
                        ret_idx++;
                    }
                }
                else
                { //contiguous regions, update only end address
                    *(&tag->size+ret_idx) = total_size;
                }
                prev_reg_endaddr = curr_reg_endaddr;
            }
            else if(ddr_shared_data->lcp_addr_regions[idx].attr == 0)
            {//reached end of ECC regions
                break;
            }
        }
        if((prev_reg_endaddr!=0)&&(ret_idx==0)){//single region
            ret_idx++;
            status = BL_ERR_NONE;
        }
        else //non contigious regions
        {
            status = GET_ERROR_CODE(BL_ERROR_GROUP_DDR, BL_ERR_INITIALIZATION_ERROR);//non-contiguous regions are not expected for MTE					
        }
    }
    *region_count = ret_idx; //return region count
    exit:
    return status;
}

