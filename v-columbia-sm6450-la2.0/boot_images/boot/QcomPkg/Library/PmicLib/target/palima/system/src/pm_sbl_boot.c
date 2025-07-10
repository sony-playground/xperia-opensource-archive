/*! \file pm_sbl_boot.c
*  \n
*  \brief This file contains PMIC device initialization function where initial PMIC
*  \n SBL settings are configured through the PDM auto-generated code.
*  \n
*  \n &copy; Copyright 2013-2023 Qualcomm Technologies Inc, All Rights Reserved
*/
/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


$Header: //components/rel/core.boot/6.0/QcomPkg/Library/PmicLib/target/palima/system/src/pm_sbl_boot.c#9 $
$Author: pwbldsvc $
$DateTime: 2023/05/01 05:04:44 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/10/21   pxm     move dp toggle inside charger applicable condition.
08/07/19   yps     Free pmic config buffer after pmic initialization
05/07/18   pxm     Remove pm_config_wlan_active_and_retention_level and auto power on check on PM855B
06/05/17   aab     Updated pm_config_wlan_active_and_retention_level() 
12/05/17   aab     Added support to log number of SPMI transaction
11/19/17   aab     Updated check to support RUMI with out PMIC.      
07/21/17   czq     Use Spare reg PON_PERPH_RB_SPARE instead of PON_DVDD_RB_SPARE
07/10/17   sv      Updated auto power on check API.
05/15/17   aab     Updated pm_sbl_chg_init() to call updated temp monitoring function
02/17/17   pxm     Called function to check if auto power on. 
01/11/17   pxm     add support for PBS triggered AFP
12/27/16   al      Porting fix to set LDO5 voltage with micro volt's.  
10/21/16   akm     Added pm_get_pon_reason_history, pm_pbs_header_info_init in pm_sbl_pre_config
10/07/16   aab     Call pm_sbl_config_skin_temp_threshold() for targets that require charging
09/13/16   aab     Updated logging text 
08/25/16   pxm     Config skin temperature threshold for all target
07/31/16   aab     Added num spmi transaction conditional logging
07/14/16   aab     Updated to support target with out PMI8998
06/02/16   aab     Updated pm_device_programmer_init()
03/23/16   aab     Updated pm_config_ssc_active_and_retention_level()
02/18/16   aab     Updated pm_sbl_chg_init()
02/18/16   aab     Added pm_system_init()
02/18/16   aab     Renamed pm_set_ssc_active_and_retention_levels_mv()  to pm_config_ssc_active_and_retention_level() 
02/05/16   aab     Added pm_set_ssc_active_and_retention_levels_mv()
01/25/16   aab     Updated pm_device_init() and pm_sbl_chg_init()to support RUMI targets with out PMIC 
12/22/15   aab     Added Support for PMI8998 SBL Charging
12/10/15   aab     Added Cx/Mx pvs_retention_data[]  
12/04/15   aab     Updated to support msm8998
10/14/15   aab     Branch from 8996 target
========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_err_flags.h"
#include "pm_boot.h"
#include "pm_ldo.h"
#include "pm_sbl_boot.h"
#include "pm_device.h"
#include "pm_config_sbl.h"
#include "pm_config_sbl_test.h"
#include "pm_pbs_info.h"
#include "pm_target_information.h"
#include "pm_sbl_boot_target.h"
#include "pm_log_utils.h"
#include "pm_pbs.h"
#include "DALDeviceId.h"
#include "DDIPlatformInfo.h"
#include "DDIChipInfo.h"
#include "pmio_pon.h"
#include "CoreVerify.h"
#include "railway.h"
#include "SpmiBus.h"
#include "pm_chg.h"
#include "pm_app_chg.h"
#include "GPIO.h"
#include "pm_dt_parser.h"
#include "qusb_ldr_utils.h"
#include "pm_gpio_driver.h"
#include "pm_gpio.h"
#include "ChipInfo.h"
#include "boot_reset_if.h"
/*===========================================================================

                     PROTOTYPES 

===========================================================================*/
static pm_err_flag_type pm_sbl_pre_config(void);
static pm_err_flag_type pm_sbl_target_detect(void);
static pm_err_flag_type pm_config_wlan_active_and_retention_level(void);
static pm_err_flag_type pm_sbl_no_battery_boot_config(void);
static pm_err_flag_type pm_leica2_sid_programming (void);
static pm_err_flag_type pm_detect_tofino_palima (void);

/*===========================================================================

                        GLOBALS and TYPE DEFINITIONS 

===========================================================================*/
boolean pm_ram_image_loaded_flag = FALSE;
static pm_sbl_specific_data_type *sbl_param_ptr = NULL;

#define SLAVE_CHARGER_NOT_PRESENT 0x0
#define SLAVE_CHARGER_PRESENT     0x1
#define SPMI_SLAVE_ID_REG 0x6f1

#define SDAM_PMIC       PMIC_A
#define SDAM_FLAG_ADDR  0x7072

#define PM_LEICA_GPIO_DISABLE     0xffff
#define LEICA_REVISION_SUB_TYPE   0x105

#define PRIMARY_BUS 0
#define SDAM_46_MEM_126 0x9DBE
#define BOB_CFG  0x1
#define HBST_CFG 0x0

#define CLK_LEICA2_LFRC_AON_TRIM 0x51f2
#define REVID_TP_REV			0x1F1

#define TOFINO_DETECTED         0x1
#define PALIMA_DETECTED         0x0

#define RTC_ALARM_DATA				    0x6240
#define RTC_ALARM_DATA_SIZE				4
#define DISABLE_RTC_ALARM        		0x00
#define DISABLE_RTC_ALARM_ADDR        	0x6246
#define CLEAR_RTC_ALARM          		0x01
#define CLEAR_RTC_ALARM_ADDR          	0x6248
/*===========================================================================

                        FUNCTION DEFINITIONS 

===========================================================================*/
static pm_err_flag_type 
pm_device_auto_boot_check(void) 
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS; 
  pm_pon_reason_type pon_reason = {0}; 
  uint8 rtc_data[4]={0};
  
  //Fix for Automatic-PON due to RTC ALARM
  err_flag |= pm_comm_read_byte_array(PMIC_A, RTC_ALARM_DATA, RTC_ALARM_DATA_SIZE, rtc_data);
  err_flag |= pm_pon_get_pon_reason(PMIC_A, &pon_reason); 
  
  if( err_flag != PM_ERR_FLAG_SUCCESS ) 
  { 
    return err_flag; 
  }
  
  if (pon_reason.rtc && !(rtc_data))
  {
    err_flag |= pm_comm_write_byte(PMIC_A, DISABLE_RTC_ALARM_ADDR, DISABLE_RTC_ALARM); //disable rtc alarm for xvdd
    err_flag |= pm_comm_write_byte(PMIC_A, CLEAR_RTC_ALARM_ADDR, CLEAR_RTC_ALARM); //clear rtc alarm for RTC power on
    pm_log_message("Shutting down due to RTC silicon HW Bug, unexpected wakeup");
    boot_hw_powerdown();//shutdown
  }
  return err_flag;
}  

pm_err_flag_type 
pm_device_init ( void )
{
  static pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 initial_num_spmi_transn = pm_get_num_spmi_transaction(0);

  pm_target_information_init();
  
  err_flag |= pm_device_setup();
  
  err_flag |= pm_target_specific_device_setup();

  if( (pm_is_target_pre_silicon() == TRUE) && (pm_is_pmic_present(PMIC_A) == FALSE) )
  {
    pm_log_message("Bootup: No PMIC on RUMI Target");
    return err_flag = PM_ERR_FLAG_SUCCESS;
  }
  
  pm_comm_info_init();

  err_flag |= pm_device_pre_init();

  err_flag |= pm_pon_init();

  err_flag |= pm_pbs_info_rom_init();  

  err_flag |= pm_sbl_pre_config(); 

  err_flag |= pm_sbl_config(); 
  if (err_flag == PM_ERR_FLAG_SUCCESS)
  {
    pm_ram_image_loaded_flag = TRUE;
  }
  
  err_flag |= pm_device_auto_boot_check();
  
  err_flag |= pm_sbl_config_test(); /* SBL Configuration validation, only executes complete code if spare reg 0x88F bit 0 is set*/

  err_flag |= pm_pbs_info_ram_init();  /* Read PBS INFO for the pmic ram devices */

  err_flag |= pm_pbs_ram_version_validation_test(); /* PBS RAM Version validation, only executes complete code if spare reg 0x88F bit 0 is set*/

  err_flag |= pm_device_post_init(); 

  //Write to Spare bit for pm_device_init_status
  if(err_flag == PM_ERR_FLAG_SUCCESS)
  {
    err_flag = pm_comm_write_byte_mask( PMIC_A_SLAVEID_PRIM, 
                                       PMIO_PON_PBS_PERPH_RB_SPARE_ADDR, 
                              PON_PERPH_RB_SPARE_DEVICE_INIT_MASK,
                              PON_PERPH_RB_SPARE_DEVICE_INIT_MASK ); 
  }

  pm_log_message("Device Init # SPMI Transn: %d", 
                  pm_get_num_spmi_transaction(initial_num_spmi_transn));
              
  return err_flag; 
}



pm_err_flag_type
pm_sbl_chg_init (void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 initial_num_spmi_transn = 0;
  boolean applicable = FALSE;

  err_flag |= pm_sbl_is_charging_applicable(&applicable);
  if (TRUE == applicable)
  {
    err_flag |= pm_sbl_chg_pre_init();

    err_flag |= pm_app_chg_init();

    //Handle Usb charger and dp toggle for CDP
    qusb_ldr_utils_handle_charger();

    err_flag |= pm_app_chg_dead_battery_charging();

    err_flag |= pm_sbl_chg_post_init();
  }

  pm_log_message("CHG Init # SPMI Transn: %d", pm_get_num_spmi_transaction(initial_num_spmi_transn));

  return err_flag;
}

pm_err_flag_type
pm_infra_init (void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  if( (pm_is_target_pre_silicon() == TRUE) && (pm_is_pmic_present(PMIC_A) == FALSE) )
  {
    pm_log_message("Bootup: No PMIC on RUMI Target");
    return err_flag = PM_ERR_FLAG_SUCCESS;
  }

  err_flag |= pm_device_setup();
  pm_target_information_init();
  pm_comm_info_init();

  err_flag |= pm_pon_init();

  return err_flag;
}



static pm_err_flag_type
pm_sbl_pre_config(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_dt_haptics_config *haptics_dt_config = NULL;
  uint32 data = 0;

  if (sbl_param_ptr == NULL)
  {
     sbl_param_ptr = (pm_sbl_specific_data_type*)pm_target_information_get_specific_info(PM_PROP_SBL_SPECIFIC_DATA);
  }
  CORE_VERIFY_PTR(sbl_param_ptr);

  err_flag |= pm_log_pon_reasons();

  err_flag |= pm_sbl_target_detect();
  
  haptics_dt_config = (pm_dt_haptics_config*)pm_dt_get_node(PMIC_DT_NODE_PM_HAPTICS);
  
  CORE_VERIFY_PTR(haptics_dt_config);
 
  data = haptics_dt_config->boost_cfg_bob ? BOB_CFG : HBST_CFG ;
  
  err_flag |= pm_comm_write_byte_ex(PRIMARY_BUS, SDAM_PMIC, SDAM_46_MEM_126, data);
  
  return err_flag;
}


pm_err_flag_type
pm_sbl_target_detect(void) /* SBL Target detect */
{
   static pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS; 

   return err_flag;
}


pm_err_flag_type 
pm_system_init(void)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

    return err_flag;
}

// Adjust the SID assignment for the Interlago, 0xB -> 0x9 / 0xC -> 0xB
static pm_err_flag_type 
pm_app_chg_set_parallel_charger_alt_sid(uint32 sid)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type pmic_type, pmic_subtype;

  err_flag = PM_ERR_FLAG_SUCCESS;
  err_flag |= pm_comm_read_byte_ex(1, sid, 0x104, &pmic_type);
  if (err_flag != PM_ERR_FLAG_SUCCESS) 
  {
    // Device not found
    return PM_ERR_FLAG_SUCCESS;
  }
  err_flag |= pm_comm_read_byte_ex(1, sid, 0x105, &pmic_subtype);
  if (err_flag != PM_ERR_FLAG_SUCCESS) 
  {
    return PM_ERR_FLAG_SUCCESS;
  }
  if (pmic_type == 0x51)
  {
    if (pmic_subtype == 0x39)
    {
      err_flag |= pm_comm_write_byte_ex(1, sid, 0x6f1, 0xb9);
    }
    if (pmic_subtype == 0x35)
    {
      err_flag |= pm_comm_write_byte_ex(1, sid, 0x6f2, 0xb9);
    }
  }

  return err_flag;
}


/*
 * Set SDAM Flag to detect slave charger presence.
 * PSI will read flag and not configure slave charger related.
 * So OEMs that don't use slave charger can re-use the GPIO reserved for Slave Charger.
 * Sets up secondary spmi bus if slave chargers are used
 * set flag to 0 = SLAVE_CHARGER_NOT_PRESENT
 *             1 = SLAVE_CHARGER_PRESENT
 */
static pm_err_flag_type 
pm_target_setup_parallel_charger(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 spmiClkDiv = 0x2;
  
  pm_dt_charger_config *chgr_dt_config = NULL;
  
  chgr_dt_config = (pm_dt_charger_config*)pm_dt_get_node(PMIC_DT_NODE_PM_CHARGER);
  
  if( chgr_dt_config == NULL )
  {
    err_flag = pm_comm_write_byte(PMIC_A, SDAM_FLAG_ADDR, 0); //write 0 to sdam register
    return PM_ERR_FLAG_SUCCESS;  //Do nothing if we don't have parallel_charger config
  }   

  err_flag = pm_comm_write_byte(PMIC_A, SDAM_FLAG_ADDR, chgr_dt_config->parallel_charger);
  
  /* work around to enable secondary bus only if slave pmic is present*/
  if (chgr_dt_config->parallel_charger)
  {
    err_flag |= pm_comm_write_byte(0, 0x12E5, spmiClkDiv);

/* Workaround for slave mode exit
1. SPMI_MASTER2.PAD_SHARING = 0x1
    - Delay 5uS
2. SPMI_MASTER2.EN_CTL = 0x80
    - Delay 100uS
3. SPMI_MASTER2.PAD_SHARING = 0x0
    - Delay = 20uS
4. SPMI_MASTER2.EN_CTL = 0x0
    - Delay = 5uS
5. SPMI_MASTER2.EN_CTL = 0x80
*/
    err_flag |= pm_comm_write_byte(0, 0x12EB, 0x1);
    busywait(5);

    err_flag |= pm_comm_write_byte(0, 0x1246, 0x80);
    busywait(100);

    err_flag |= pm_comm_write_byte(0, 0x12EB, 0x0);
    busywait(20);

    err_flag |= pm_comm_write_byte(0, 0x1246, 0x0);
    busywait(5);

    err_flag |= pm_comm_write_byte(0, 0x1246, 0x80);
    busywait(100);

    /*Enable Secondary bus with busId 1 */
    SpmiBus_EnableAuxBus(1);

    /* work around to move the interlago SID from 0xb/0xc to 0x9/0xb */
    err_flag |= pm_app_chg_set_parallel_charger_alt_sid(0xb);
    err_flag |= pm_app_chg_set_parallel_charger_alt_sid(0xc);
  }


  return err_flag;
}

pm_err_flag_type
pm_target_specific_device_setup(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  
  err_flag |= pm_version_deinit();
  
  // PSI will read the flag to determine if need to configure slave charger related.
  err_flag |= pm_target_setup_parallel_charger();
  pm_leica2_sid_programming ();

  err_flag |= pm_version_detect();
  
  err_flag |= pm_detect_tofino_palima();

  return err_flag;
}

pm_err_flag_type 
pm_sbl_is_charging_applicable(boolean* applicable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  DalPlatformInfoPlatformType platform_type = DALPLATFORMINFO_TYPE_UNKNOWN;
  pm_model_type pmic_model = PMIC_IS_UNKNOWN;
  uint32 device_index_charger = PMIC_D;
  *applicable = FALSE;

  if (pm_is_target_pre_silicon() == TRUE)
  {
    pm_log_message("Pre-SIL. No CHG Support");
    return PM_ERR_FLAG_SUCCESS; 
  }

  platform_type = DalPlatformInfo_Platform();
  pmic_model = pm_get_pmic_model(device_index_charger);
  if( ((platform_type == DALPLATFORMINFO_TYPE_MTP)
    || (platform_type == DALPLATFORMINFO_TYPE_FLUID)
    || (platform_type == DALPLATFORMINFO_TYPE_LIQUID)
    || (platform_type == DALPLATFORMINFO_TYPE_QRD)
	|| (platform_type == DALPLATFORMINFO_TYPE_IDP)
	|| (platform_type == DALPLATFORMINFO_TYPE_CDP)
    || (platform_type == DALPLATFORMINFO_TYPE_HDK)) &&
       (pmic_model == PMIC_IS_PM8350B))
  {
	pm_log_message("Charging applicable is true");
    *applicable = TRUE;
  }

  return err_flag;
}

pm_err_flag_type
pm_update_leica2_details (void)
{
  uint8 leica_count = 0;
  uint8 leica_1_pmic ,leica_1_gpio ;
  uint8 leica_2_pmic ,leica_2_gpio ;
  pm_err_flag_type err_flag   = PM_ERR_FLAG_SUCCESS;

  pm_dt_camera_config *camera_dt = (pm_dt_camera_config*)pm_dt_get_node(PMIC_DT_NODE_PM_CAMERA);
  
  if(camera_dt->leica2_1_gpio[0] != PM_LEICA_GPIO_DISABLE && camera_dt->leica2_1_gpio[1] != PM_LEICA_GPIO_DISABLE){
    leica_count ++;
    /*Updating first leica GPIO connections in SDAM*/
    leica_1_pmic = camera_dt->leica2_1_gpio[0];
    leica_1_gpio = camera_dt->leica2_1_gpio[1];
    pm_comm_write_byte(PMIC_A, 0x72B8, leica_1_pmic);
    pm_comm_write_byte(PMIC_A, 0x72B9, leica_1_gpio);
  }
  
  if(camera_dt->leica2_2_gpio[0] != PM_LEICA_GPIO_DISABLE && camera_dt->leica2_2_gpio[1] != PM_LEICA_GPIO_DISABLE){
    leica_count ++;
    /*Updating second leica GPIO connections in SDAM*/
    leica_2_pmic = camera_dt->leica2_2_gpio[0];
    leica_2_gpio = camera_dt->leica2_2_gpio[1];
    pm_comm_write_byte(PMIC_A, 0x72BA, leica_2_pmic);
    pm_comm_write_byte(PMIC_A, 0x72BB, leica_2_gpio);
  }
  
  pm_comm_write_byte(PMIC_A, 0x72B7, leica_count);
  
  return err_flag;
}

pm_err_flag_type
pm_gpio_update_config(uint32 pmic, uint32 peripheral_base)
{
  pm_comm_write_byte(pmic,(peripheral_base + 0x46),0x0);
  pm_comm_write_byte(pmic,(peripheral_base + 0x41),0x01);
  pm_comm_write_byte(pmic,(peripheral_base + 0xDA),0x0F);
  pm_comm_write_byte(pmic,(peripheral_base + 0x40),0x01);
  return PM_ERR_FLAG_SUCCESS;
}

static pm_err_flag_type
pm_leica2_sid_programming (void)
{
  pm_err_flag_type err_flag   = PM_ERR_FLAG_SUCCESS;
  pm_err_flag_type err_gpio   = PM_ERR_FLAG_FAILURE;
  uint8 data;
  uint8 leica2_1_detection = 0;
  uint8 leica2_2_detection = 0;
  uint8 leica2_1_aon_trim = 0, leica2_2_aon_trim = 0;
  uint8 leica2_1_revid_tp_rev = 0,leica2_2_revid_tp_rev = 0;
  
  GPIOClientHandleType GPIOHandle;
  GPIOResult bGPIOResult;
  GPIOKeyType GPIOKey_LEA = 0, GPIOKey_LEB = 0;
  GPIOConfigType GPIOConfig;

  pm_dt_camera_config *camera_dt = (pm_dt_camera_config*)pm_dt_get_node(PMIC_DT_NODE_PM_CAMERA);
  
  pm_update_leica2_details();
  if (GPIO_SUCCESS != GPIO_Attach(GPIO_DEVICE_TLMM, &GPIOHandle)) {
      return err_gpio;
  }
 
  /* Register the pin of interest */
  if (camera_dt->reset_gpio[0] != PM_LEICA_GPIO_DISABLE) {
    bGPIOResult = GPIO_RegisterPinExplicit(GPIOHandle, camera_dt->reset_gpio[0], 
                                           GPIO_ACCESS_SHARED, &GPIOKey_LEA);
    if (bGPIOResult != GPIO_SUCCESS) { 
      return err_gpio; 
    }
  }

  if (camera_dt->reset_gpio[1] != PM_LEICA_GPIO_DISABLE) {
    bGPIOResult = GPIO_RegisterPinExplicit(GPIOHandle, camera_dt->reset_gpio[1], 
                                                      GPIO_ACCESS_SHARED, &GPIOKey_LEB);
    if (bGPIOResult != GPIO_SUCCESS) { 
      return err_gpio; 
    }
  }

  /* Setup the enable pin to output */
  GPIOConfig.func = 0;
  GPIOConfig.dir = GPIO_OUT;
  GPIOConfig.pull = GPIO_NP;
  GPIOConfig.drive = 1;    // 0.01mA, rounded up to 2mA
  GPIOConfig.unused = 0;  //KW Error Fix
  
  //Init SDAM Leica2 BAD to 0
  pm_comm_write_byte(PMIC_A, 0x72BC, 0x0);
  pm_comm_write_byte(PMIC_A, 0x72BD, 0x0);

  
  if(camera_dt->leica2_1_gpio[0] != PM_LEICA_GPIO_DISABLE && camera_dt->leica2_1_gpio[1] != PM_LEICA_GPIO_DISABLE){
     /*Both PMIC & MSM GPIOs are toggled here*/
     //Keep this GPIO-HIGH 
     leica2_1_detection = 1;
     pm_gpio_update_config(camera_dt->leica2_1_gpio[0], camera_dt->leica2_1_gpio[1]*0x100);
     pm_comm_write_byte(camera_dt->leica2_1_gpio[0],((camera_dt->leica2_1_gpio[1]*0x100) + 0x46),0x80);
     pm_comm_write_byte(camera_dt->leica2_1_gpio[0],((camera_dt->leica2_1_gpio[1]*0x100) + 0x44),0x80);
     //Keep the second GPIO - LOW
     if(camera_dt->leica2_2_gpio[0] != PM_LEICA_GPIO_DISABLE && camera_dt->leica2_2_gpio[1] != PM_LEICA_GPIO_DISABLE){
        pm_comm_write_byte(camera_dt->leica2_2_gpio[0],((camera_dt->leica2_2_gpio[1]*0x100) + 0x44),0);
        pm_comm_write_byte(camera_dt->leica2_2_gpio[0],((camera_dt->leica2_2_gpio[1]*0x100) + 0x46),0x80);
      }
  }

  //Handling MSM GPIO Case 
  if(camera_dt->reset_gpio[0] != PM_LEICA_GPIO_DISABLE){
     leica2_1_detection = 1;
     bGPIOResult = GPIO_ConfigPin(GPIOHandle, GPIOKey_LEA, GPIOConfig);
     if (bGPIOResult != GPIO_SUCCESS) { 
       return err_gpio; 
     }

     bGPIOResult = GPIO_WritePin(GPIOHandle, GPIOKey_LEA, GPIO_HIGH);
     if (bGPIOResult != GPIO_SUCCESS) { 
       return err_gpio; 
     }

     if (camera_dt->reset_gpio[1] != PM_LEICA_GPIO_DISABLE) {
       bGPIOResult = GPIO_ConfigPin(GPIOHandle, GPIOKey_LEB, GPIOConfig);
       if (bGPIOResult != GPIO_SUCCESS) { 
         return err_gpio; 
       }
   
       bGPIOResult = GPIO_WritePin(GPIOHandle, GPIOKey_LEB, GPIO_LOW);
       if (bGPIOResult != GPIO_SUCCESS) { 
         return err_gpio; 
       }
     }
   }

   if(leica2_1_detection){
     busywait(2000);
     err_flag |= pm_comm_write_byte_ex(0, 0xc, SPMI_SLAVE_ID_REG, 0x8);
     err_flag = pm_comm_read_byte_ex(0, 0x8, LEICA_REVISION_SUB_TYPE, &data);
     if(err_flag){
       pm_log_message("Updating Leica2_1 SDAM Flag with Bad Leica details");
       pm_comm_write_byte(PMIC_A, 0x72BC, 0x1);
     }
     else{
       pm_comm_write_byte(PMIC_A, 0x72BC, 0x0);
       pm_log_message("Leica2_1 read successfull - Subtype ID is %d",data);
  
	   err_flag |= pm_comm_read_byte_ex(0, 0x8, CLK_LEICA2_LFRC_AON_TRIM, &leica2_1_aon_trim);
	   err_flag |= pm_comm_read_byte_ex(0, 0x8, REVID_TP_REV, &leica2_1_revid_tp_rev);
	   if((leica2_1_aon_trim > 0xF) && (leica2_1_revid_tp_rev < 0x1A))
	   {
		   err_flag |= pm_comm_write_byte_ex(0, 0x8, CLK_LEICA2_LFRC_AON_TRIM, 0x7);
	   }
     }
   }

  if(camera_dt->leica2_2_gpio[0] != PM_LEICA_GPIO_DISABLE && camera_dt->leica2_2_gpio[1] != PM_LEICA_GPIO_DISABLE){
     leica2_2_detection = 1;
     pm_gpio_update_config(camera_dt->leica2_2_gpio[0], camera_dt->leica2_2_gpio[1]*0x100);
     pm_comm_write_byte(camera_dt->leica2_2_gpio[0],((camera_dt->leica2_2_gpio[1]*0x100) + 0x46),0x80);
     pm_comm_write_byte(camera_dt->leica2_2_gpio[0],((camera_dt->leica2_2_gpio[1]*0x100) + 0x44),0x80);
   }
   // Second Leica set to SID of 0x9
   if (camera_dt->reset_gpio[1] != PM_LEICA_GPIO_DISABLE) {
     leica2_2_detection = 1;
     if (camera_dt->reset_gpio[1] != PM_LEICA_GPIO_DISABLE) {
       bGPIOResult = GPIO_ConfigPin(GPIOHandle, GPIOKey_LEB, GPIOConfig);
       if (bGPIOResult != GPIO_SUCCESS) { 
         return err_gpio; 
       }
     }
     bGPIOResult = GPIO_WritePin(GPIOHandle, GPIOKey_LEB, GPIO_HIGH);
     if (bGPIOResult != GPIO_SUCCESS) { 
       return err_gpio; 
     }
   }
   if(leica2_2_detection){
     busywait(2000);
     err_flag |= pm_comm_write_byte_ex(0, 0xc, SPMI_SLAVE_ID_REG, 0x9);
     err_flag = pm_comm_read_byte_ex(0, 0x9, LEICA_REVISION_SUB_TYPE, &data);
     if(err_flag){
       pm_log_message("Updating Leica2_2 SDAM Flag with Bad Leica details");
       pm_comm_write_byte(PMIC_A, 0x72BD, 0x1);
     }
     else{
       pm_comm_write_byte(PMIC_A, 0x72BD, 0x0);
       pm_log_message("Leica2_2 read successfull - Subtype ID is %d",data);
   
	   err_flag |= pm_comm_read_byte_ex(0, 0x9, CLK_LEICA2_LFRC_AON_TRIM, &leica2_2_aon_trim);
	   err_flag |= pm_comm_read_byte_ex(0, 0x9, REVID_TP_REV, &leica2_2_revid_tp_rev);
	   if((leica2_2_aon_trim > 0xF) && (leica2_2_revid_tp_rev < 0x1A))
	   {
		   pm_comm_write_byte_ex(0, 0x9, CLK_LEICA2_LFRC_AON_TRIM, 0x7);

	   }
     }
   }

  return err_flag;
}

static pm_err_flag_type
pm_detect_tofino_palima (void)
{
  pm_err_flag_type err_flag   = PM_ERR_FLAG_SUCCESS;
  ChipInfo_Init();
  if(CHIPINFO_ID_SM_TOFINO == ChipInfo_GetChipId())
  {
    pm_log_message("Tofino Chip Detected");
    err_flag = pm_comm_write_byte_ex(0, 0x0, 0x707B,TOFINO_DETECTED); 
  }
  else{
    pm_log_message("Palima Chip Detected");
    err_flag = pm_comm_write_byte_ex(0, 0x0, 0x707B,PALIMA_DETECTED); 
  }

  return err_flag;
}
