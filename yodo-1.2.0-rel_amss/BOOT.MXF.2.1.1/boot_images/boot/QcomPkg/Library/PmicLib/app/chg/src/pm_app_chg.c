/*! \file
*  
*  \brief  pm_app_chg.c
*  \details Implementation file for SBL charger float and also internal charger APIs.
*    
*  &copy; Copyright 2021-2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/17/20   zzx     Call Dp toggle api for CDP charger detection
01/06/20   xp      Creation
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_app_chg.h"
#include "pm_chg.h"
#include "pm_qbg.h"
#include "pm_utils.h"
#include "pm_log_utils.h"
#include "pm_bmd.h"
#include "pm_app_rgb.h"
#include "pm_rgb_driver.h"
#include "pm_scpq_driver.h"
#include "pm_schg_driver.h"
#include "pm_scpq_chgr.h"
#include "pm_scpq_chgr2.h"
#include "pm_schg_chgr.h"
#include "pm_scpq_usb.h"
#include "pm_schg_usb.h"
#include "pm_scpq_batif.h"
#include "pm_scpq_misc.h"
#include "pm_schg_misc.h"
#include "pm_scpq_dcdc.h"
#include "pm_schg_batif.h"
#include "pm_schg_dcdc.h"
#include "pm_scpq_typec.h"
#include "pm_schg_typec.h"
#include "CoreVerify.h"
#include "pm_target_information.h"
#include "qusb_dci_common.h"
#include "busywait.h"
#include "adc.h"
#include "pm_dt_parser.h"
#include "DDIPlatformInfo.h"


#ifdef FEATURE_XBOOT
#include <Library/SetChargerLib.h>
#endif /* FEATURE_XBOOT */

/***************************************************************************
*
*                           Macros and Definitions
*
****************************************************************************/
// sample vbat/ibat and toggle LED every 500ms
#define PM_WEAK_BATTERY_CHARGING_DELAY (500 * 1000)
#define PM_WAIT_FOR_APSD_DONE_DELAY    (50 * 1000) //50 ms

#define PM_CHG_CDP_DP_TOGGLE_MS   200  //200ms to toggle Dp for CDP port detection

#define BATTERY_UV_OC_VSYS_MIN_STEP_DOWN_INTERVAL_MS        (100)                   // 100 mS
#define VSYSMIN_RECOVER_STEP_MV                             (100)                   // 100 mV
#define BATTERY_UV_OC_I_PRE_CFG_IN_MA                       (250)                   // 250 mA
#define BATTERY_UV_OC_RECOVERY_TIME_IN_MS                   (50)                    //  50 mS
#define WDOG_PET_INTERVAL_MS                                (500)                   // 500 mS

#define SMB_139X_SID                                        (0xD)
#define SMB_139X_SCHG_PERPH0_BASE                           (0x2600)
#define SMB_139X_SCHG_PERPH1_BASE                           (0x2700)
#define SMB_139X_SCHG_PERPH2_BASE                           (0x2800)
#define SMB_139X_SCHG_PERPH0_CFG_SDCDC                      (SMB_139X_SCHG_PERPH0_BASE+0x7A)
#define MASK_CFG_EN_WIN_OV                                  (0x1<<5)
#define SMB_139X_SCHG_PERPH0_ENG_SDCDC_3LVL_B_LOOP_ERR_CFG  (SMB_139X_SCHG_PERPH0_BASE+0xC8)
#define MASK_ENG_X2_WIN_OV                                  (0x1<<3)
#define SMB_139X_SCHG_PERPH0_SOVP_CFG0                      (SMB_139X_SCHG_PERPH0_BASE+0x80)
#define MASK_CFG_EN_UV_RISE_DEB                             (0x1<<3)

#define PM_THERM_PULL_UP_30K (0)
#define PM_THERM_PULL_UP_100K (1)
#define PM_THERM_PULL_UP_400K (2)

#define PM_THERM_CHANNEL_30K (0x24)
#define PM_THERM_CHANNEL_100K (0x44)
#define PM_THERM_CHANNEL_400K (0x64)

#define PM_SDP_ICL_MA (500)
#define PM_CDP_ICL_MIN_MA (1500)

#define PM_DEFAULT_ACC0_DATA (0x8000)
#define PM_ACC0_POLL_INTERVAL (5 * 1000)  // 5ms each cycle
#define PM_ACC0_POLL_TIMEOUT (500 * 1000)  // Overall 500ms polling timeout

#define PM_ADC_POLL_INTERVAL (500)  // 500us each cycle
#define PM_ADC_POLL_TIMEOUT (300 * 1000)  // Overall 300ms polling timeout

/***************************************************************************
*
*                           Function Definitions
*
****************************************************************************/
static pm_err_flag_type pm_app_chg_apply_charger_config(void);
static pm_err_flag_type pm_app_chg_get_batt_id(pm_adc_pull_up_type pu_type, uint32 *batt_id_ohms);
static pm_err_flag_type pm_app_chg_enable_smb_protections(boolean enable);
static pm_err_flag_type pm_app_chg_get_2cell_vbat(uint32* vcell1, uint32* vcell2);
static void pm_app_chg_pet_wdog(void);
static pm_err_flag_type pm_app_chg_no_battery_boot_config(void);
static pm_err_flag_type pm_app_chg_wait_apsd_and_aicl_from_max(void);
static pm_err_flag_type pm_app_chg_is_dam_cable_connected(uint32 charger_index, boolean* connected);
static pm_err_flag_type pm_app_chg_get_icl_final(uint32 charger_index, uint32* icl_final);
static pm_err_flag_type pm_config_jeita();
static pm_err_flag_type pm_scpq_config_jeita(uint32 pmic_index);
static pm_err_flag_type pm_schg_config_jeita(uint32 pmic_index);

/***************************************************************************
*
*                           API Implementation
*
****************************************************************************/
pm_dt_charger_config *
pm_get_charger_dt_config(void)
{
  static pm_dt_charger_config *charger_dt_config = NULL;

  if(NULL == charger_dt_config)
  {
    charger_dt_config = (pm_dt_charger_config*)pm_dt_get_node(PMIC_DT_NODE_PM_CHARGER);
    CORE_VERIFY_PTR(charger_dt_config);
  }

  return charger_dt_config;
}

void 
pm_app_chg_get_debug_board_id_min_max(uint32* min, uint32* max)
{
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();

  if((NULL == min) || (NULL == max))
  {
    return;
  }

  *min = charger_dt_config->min_dbg_board_id;
  *max = charger_dt_config->max_dbg_board_id;
}

static pm_err_flag_type 
pm_app_chg_get_batt_id(pm_adc_pull_up_type pu_type, uint32 *batt_id_ohms)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  adc_status_type adc_status = ADC_STATUS_SUCCESS;
  adc_result_type adc_result = {0};
  const char *channel = NULL;

  if(NULL == batt_id_ohms || pu_type >= PM_BATT_ID_PU_INVALID)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  switch(pu_type)
  {
  case PM_ADC_PU_30K:
    channel = ADC_INPUT_BATT_ID_OHMS_PU_30K;
    break;
  case PM_ADC_PU_100K:
    channel = ADC_INPUT_BATT_ID_OHMS;
    break;
  case PM_ADC_PU_400K:
    channel = ADC_INPUT_BATT_ID_OHMS_PU_400K;
    break;
  default:
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  adc_status = adc_read(channel, &adc_result);
  if(adc_status != ADC_STATUS_SUCCESS)
  {
    pm_log_message("adc_read error: %d. %s %d", adc_status, __func__, __LINE__);
    return PM_ERR_FLAG_FAILURE;
  }

  *batt_id_ohms = adc_result.physical;

  return err_flag;
}


pm_err_flag_type 
pm_app_chg_is_debug_board_present(boolean* present)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  static boolean debug_board_detected = FALSE;
  static boolean debug_board_present = FALSE;
  uint32 battery_id = 0;
  uint32 battery_id_min = 0, battery_id_max = 0;

  if(NULL == present)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  if(FALSE == debug_board_detected)
  {
    // Read battery ID and compared with the configured debug board ID range
    err_flag = pm_app_chg_get_batt_id(PM_ADC_PU_30K, &battery_id);
    if(PM_ERR_FLAG_SUCCESS == err_flag)
    {
      pm_app_chg_get_debug_board_id_min_max(&battery_id_min, &battery_id_max);
      pm_log_message("Battery ID: %dOhm", battery_id);
      if((battery_id >= battery_id_min) &&
          (battery_id <= battery_id_max))
      {
        debug_board_present = TRUE;
      }
      else
      {
        debug_board_present = FALSE;
      }
    }

    debug_board_detected = TRUE;
  }

  *present = debug_board_present;

  return err_flag;
}


pm_err_flag_type 
pm_app_chg_dbc_condition_check(boolean* bypass_dbc)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();
  boolean debug_board_present = FALSE, battery_present = FALSE;
  uint32 therm = 0;
  boolean is_jig = FALSE;

  if(NULL == bypass_dbc)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  *bypass_dbc = (PM_IMG_LOADER == pm_get_img_type()) ? 
                        charger_dt_config->skip_loader_dbc : charger_dt_config->skip_core_dbc;

  //To prevent device shutdown by huge power consumption when customer skip dbc
  if((PM_IMG_LOADER == pm_get_img_type()) && (TRUE == *bypass_dbc))
  {
    err_flag |= pm_app_chg_wait_apsd_and_aicl_from_max();
  }

  err_flag |= pm_app_chg_is_debug_board_present(&debug_board_present);

  if(charger_dt_config->detect_jig_by_therm)
  {
    err_flag |= pm_get_batt_therm_ohms(&therm);
    pm_log_message("Therm: %d Ohm", therm);

    if((therm <= charger_dt_config->max_therm) &&
        (therm >= charger_dt_config->min_therm))
    {
      is_jig = TRUE;
      err_flag |= pm_app_chg_configure_usb_icl(charger_dt_config->jig_icl_ma);
    }

    debug_board_present |= is_jig;
  }

  err_flag |= pm_chg_is_battery_present(&battery_present);

  if((PM_ERR_FLAG_SUCCESS == err_flag) && 
  ((TRUE == debug_board_present) || (FALSE == battery_present)))
  {
    if(TRUE == debug_board_present)
    {
      pm_log_message("debug board connected");
      err_flag |= pm_chg_enable_usb_charging(FALSE);
      err_flag |= pm_chg_enable_wireless_charging(FALSE);
    }

    if(FALSE == battery_present)
    {
      pm_log_message("battery missing");
      err_flag |= pm_app_chg_no_battery_boot_config();
    }

    *bypass_dbc = TRUE; // Overwrite due to HW limitation
  }

  return err_flag;
}


// As a Workaround for Puhi/PM8350B reverse boost OCP issue
// This change is to limit IBAT to <4A and IOTG to <3A.
// This W/A only applicable for Puhi and use BIT[0] of SDAM16_MEM032 as flag to indicate if the w/a has been applied
pm_err_flag_type 
pm_app_chg_trim_otg_offset_and_gain(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_address_type trim_flag_address = 0x7F60;  // Address of Tokei.SDAM16_MEM032
  pm_register_address_type otg_offset_addr = 0x2CF5;
  pm_register_address_type otg_gain_addr = 0x2CF6;
  pm_register_data_type offset_data = 0, gain_data = 0;
  const pm_register_data_type trim_flag_mask = 0x1; // BIT[0] of SDAM16_MEM032
  pm_register_data_type data = 0;
  uint32 pmic_index_charger = PMIC_INDEX_MAX;

  err_flag = pm_chg_get_primary_charger_pmic_index(&pmic_index_charger);
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  if(NULL != pm_scpq_get_data(pmic_index_charger))
  {
    err_flag = pm_comm_read_byte(PMIC_A, trim_flag_address, &data);
    // Check if the BIT[0] of Tokei.SDAM16_MEM032 is 1.
    // 1: OTG has been trimed
    // 0: OTG trim has been reset
    if(trim_flag_mask & data)
    {
      return PM_ERR_FLAG_SUCCESS; // return as we only apply this sw W/A at 1st boot(after dvdd/xvdd reset)
    }

    /* W/A for otg offset trim */
    err_flag |= pm_comm_read_byte(pmic_index_charger, otg_offset_addr, &offset_data);
    //Adjust the offset_data
    if((0x0 <= offset_data) && (offset_data <= 0x4))
    {
      offset_data = 0x24 - offset_data;
    }
    else if((0x5 <= offset_data) && (offset_data <= 0x1F))
    {
      offset_data -= 5;
    }
    else if((0x20 <= offset_data) && (offset_data <= 0x3A))
    {
      offset_data += 5;
    }
    else if((0x3B <= offset_data) && (offset_data <= 0x3F))
    {
      offset_data = 0x3F;
    }
    // Write back the offset_data
    err_flag |= pm_comm_write_byte(pmic_index_charger, otg_offset_addr, offset_data);

    /* W/A for otg gain trim */
    err_flag |= pm_comm_read_byte(pmic_index_charger, otg_gain_addr, &gain_data);
    //Adjust the gain_data
    if((0x0 <= gain_data) && (gain_data <= 0x5))
    {
      gain_data = 0x26 - gain_data;
    }
    else if((0x6 <= gain_data) && (gain_data <= 0x1F))
    {
      gain_data -= 6;
    }
    else if((0x20 <= gain_data) && (gain_data <= 0x39))
    {
      gain_data += 6;
    }
    else if((0x3A <= gain_data) && (gain_data <= 0x3F))
    {
      gain_data = 0x3F;
    }
    // Write back the gain_data
    err_flag |= pm_comm_write_byte(pmic_index_charger, otg_gain_addr, gain_data);

    // Set flag to indicate dvdd/xvdd happened and we have applied this sw W/A
    err_flag |= pm_comm_write_byte_mask(PMIC_A, trim_flag_address, trim_flag_mask, trim_flag_mask);
  }

  return err_flag;
}


pm_err_flag_type 
pm_app_chg_init(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 charger_index = PMIC_INDEX_MAX;

  err_flag = pm_chg_get_primary_charger_pmic_index(&charger_index);
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  err_flag |= pm_app_chg_apply_charger_config();

#ifdef FEATURE_XBOOT
  err_flag |= pm_bmd_enable(charger_index, FALSE);
#else /* !FEATURE_XBOOT */
  err_flag |= pm_bmd_enable(charger_index, TRUE);
#endif /* !FEATURE_XBOOT */

  return err_flag;
}


// This function should be called if charging taking place. internal use only
static pm_err_flag_type 
pm_app_chg_output_charging_status(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  boolean power_by_usbin = FALSE;
  pm_chg_power_path_type power_path = PM_CHG_POWER_PATH_INVALID;
  pm_chg_charger_port_type charger_port = PM_CHARGER_PORT_TYPE_INVALID;
  char* charger_type = NULL;
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();
  static boolean float_icl_configured = FALSE;
  adc_status_type adc_status = ADC_STATUS_SUCCESS;
  adc_result_type vadc_result = {0, 0, 0};
  adc_result_type iadc_result = {0, 0, 0};
  pm_scpq_chgr_status_type chgr_sts = {.charger_status={PM_SCPQ_BATT_CHGR_STATUS_INVALID, FALSE, FALSE, FALSE}};
  char *chg_sts_str[PM_SCPQ_BATT_CHGR_STATUS_COUNT] = {"INHIBIT", "TRICKLE", "PRECHG", "FULLON", "TAPER", "TERMINATION", "PAUSE", "DISABLED", "INVALID"};
  char *chg_path = "USB";
  uint32 charger_index = PMIC_INDEX_MAX;
  pm_scpq_misc_vin_div16_mux_sel_type mux_sel = PM_SCPQ_MISC_VIN_DIV16_MUX_SEL_INVALID;
  char* adc_ch = "VWLS";
  static boolean sdp_detected_first_time = TRUE;


  err_flag |= pm_chg_get_primary_charger_pmic_index(&charger_index);
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  err_flag |= pm_chg_get_power_path(&power_path);

  if(power_path == PM_CHG_POWER_PATH_USBIN)
  {
    power_by_usbin = TRUE;
    mux_sel        = PM_SCPQ_MISC_VIN_DIV16_MUX_SEL_USB_IN;

    err_flag |= pm_chg_get_charger_port_type(&charger_port);

    switch(charger_port)
    {
    case PM_CHARGER_PORT_SDP_CHARGER:
      charger_type = "SDP";
      // Avoid SDP sink 3A when connecting device to SDP with DAM cable
      if(TRUE == sdp_detected_first_time)
      {
        sdp_detected_first_time = FALSE;
        if(NULL != pm_scpq_get_data(charger_index))
        {
          err_flag |= pm_scpq_typec_set_dam_icl(charger_index,PM_TYPEC_DAM_ICL_FMB);
        }
        else if(NULL != pm_schg_get_data(charger_index))
        {
          err_flag |= pm_schg_typec_set_dam_icl(charger_index,PM_SCHG_USB_TYPEC_DAM_ICL_FMB);
        }
      }
      break;
    case PM_CHARGER_PORT_OCP_CHARGER:
      charger_type = "OCP";
      break;
    case PM_CHARGER_PORT_CDP_CHARGER:
      charger_type = "CDP";
      break;
    case PM_CHARGER_PORT_DCP_CHARGER:
      charger_type = "DCP";
      break;
    case PM_CHARGER_PORT_FLOAT_CHARGER:
      charger_type = "Float";
      if(charger_dt_config->apply_float_charger_icl && !float_icl_configured)
      {
        err_flag |= pm_app_chg_configure_usb_icl(charger_dt_config->float_charger_icl_ma);
        float_icl_configured = TRUE;
      }
      break;
    case PM_CHARGER_PORT_QC_2P0_CHARGER:
      charger_type = "QC2";
      break;
    case PM_CHARGER_PORT_QC_3P0_CHARGER:
      charger_type = "QC3";
      break;
    default:
      charger_type = "Unknown";
      break;
    }
  }
  else if(power_path == PM_CHG_POWER_PATH_WIRELESS)
  {
    chg_path = "WLS";
    mux_sel = PM_SCPQ_MISC_VIN_DIV16_MUX_SEL_WLS_IN;
  }
  else
  {
    return err_flag;
  }

  chgr_sts.charger_status.battery_charger_status = FALSE;
  if(NULL != pm_scpq_get_data(charger_index))
  {
    err_flag |= pm_scpq_chgr_get_chgr_status(charger_index, &chgr_sts);
  }
  else if(NULL != pm_schg_get_data(charger_index))
  {
    err_flag |= pm_schg_chgr_get_chgr_status(charger_index, (pm_schg_chgr_status_type*)&chgr_sts);
  }

  /*Configuring the mux for USB/WLS voltage reading*/
  if(NULL != pm_scpq_get_data(charger_index))
  {
    pm_scpq_misc_set_vin_adc_mux_sel(charger_index, mux_sel);
    pm_busy_wait(10);
  }

  adc_status = adc_read(adc_ch, &vadc_result);
  if(adc_status != ADC_STATUS_SUCCESS)
  {
    pm_log_message("adc_read error: %d. %s %d", adc_status, __func__, __LINE__);
    return PM_ERR_FLAG_FAILURE;
  }

  // WLS_IN_I is the same ADC channel as USB_IN_I
  adc_status = adc_read(ADC_INPUT_USB_IN_I, &iadc_result);
  if(adc_status != ADC_STATUS_SUCCESS)
  {
    pm_log_message("ADC %s sts:%d", ADC_INPUT_USB_IN_I, adc_status, __func__, __LINE__);
    return PM_ERR_FLAG_FAILURE;
  }

  pm_log_message("Charger:%s V%s:%dmV I%s:%dmA CHG_STS:%s",
                  power_by_usbin ? charger_type : "Wireless",
                  chg_path,
                  vadc_result.physical,
                  chg_path,
                  iadc_result.physical,
                  chg_sts_str[chgr_sts.charger_status.battery_charger_status]);

  return err_flag;
}

static pm_err_flag_type
pm_app_chg_enable_bpd_cfg(boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();
  uint32 pmic_index = charger_dt_config->charger_pmic_index;

  if(NULL != pm_scpq_get_data(pmic_index))
  {
    err_flag = pm_scpq_batif_cfg_batt_missing_src(pmic_index, PM_SCPQ_BAT_MISS_SRC_CFG_PIN_SRC_EN, enable);
  }
  else if(NULL != pm_schg_get_data(pmic_index))
  {
    err_flag = pm_schg_batif_cfg_batt_missing_src(pmic_index, PM_SCHG_BAT_MISS_SRC_CFG__PIN_SRC_EN, enable);
  }
  else
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  return err_flag;
}


static pm_err_flag_type 
pm_app_chg_apply_charger_config(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();
  uint32 pmic_index = charger_dt_config->charger_pmic_index;
  pm_model_type pm_model = pm_get_pmic_model(pmic_index);

  // Configure BMD source. ID or Therm
  if(charger_dt_config->batt_detect_src < PM_BMD_SRC_INVALID)
  {
    pm_bmd_src_ctl_sel_type source = PM_BMD_SRC_INVALID;

    err_flag |= pm_bmd_get_src_type(pmic_index, &source);
    if(source != charger_dt_config->batt_detect_src)
    {
      err_flag |= pm_app_chg_enable_bpd_cfg(FALSE);

      err_flag |= pm_bmd_enable(pmic_index, FALSE);
      err_flag |= pm_bmd_src_ctl(pmic_index, charger_dt_config->batt_detect_src);
      err_flag |= pm_bmd_enable(pmic_index, TRUE);

      uint16 data0 = 0;
      int loop_count = PM_ACC0_POLL_TIMEOUT / PM_ACC0_POLL_INTERVAL;
      while(TRUE)
      {
        err_flag |= pm_qbg_get_last_burst_avg_acc_data(pmic_index, PM_QBG_ACC0, &data0);
        if((err_flag != PM_ERR_FLAG_SUCCESS) || (PM_DEFAULT_ACC0_DATA != data0) || (loop_count <= 0))
        {
          break;
        }
        else
        {
          pm_busy_wait(PM_ACC0_POLL_INTERVAL);
          --loop_count;
        }
      }

      err_flag |= pm_app_chg_enable_bpd_cfg(TRUE);
    }
  }

  if(pm_model != PMIC_IS_SMB2351) //SMB2351 doesn't have QBG and SCPQ module
  {
    pm_chg_battery_type battery_type = PM_CHG_BATT_TYPE_INVALID;
    pm_chg_2s_battery_option_type battery_2s_option = (pm_chg_2s_battery_option_type)charger_dt_config->batt_2s_option;

    uint8 channel_id = PM_THERM_CHANNEL_100K; // default 100K
    uint8 channel_id_from_register = PM_THERM_CHANNEL_100K; 
    uint8 pull_up = 0x2;  // default 100K, 0 - open, 0x1 - 30k pull-up, 0x2 - 100k pull-up, 0x3 - 400k pull-up
    uint8 default_pu = PM_THERM_PULL_UP_100K;
    boolean adc_conv_done = FALSE;

    err_flag |= pm_scpq_misc_get_batt_therm_ch_id_cfg(pmic_index, &channel_id_from_register);
    if(channel_id_from_register == PM_THERM_CHANNEL_100K)
    {
      default_pu = PM_THERM_PULL_UP_100K;
    }
    else if(channel_id_from_register == PM_THERM_CHANNEL_30K)
    {
      default_pu = PM_THERM_PULL_UP_30K;
    }
    else if(channel_id_from_register == PM_THERM_CHANNEL_400K)
    {
      default_pu = PM_THERM_PULL_UP_400K;
    }
    
    if((err_flag == PM_ERR_FLAG_SUCCESS) && (default_pu != charger_dt_config->batt_therm_pull_up))
    {
      if(charger_dt_config->batt_therm_pull_up == PM_THERM_PULL_UP_30K)
      {
        channel_id = PM_THERM_CHANNEL_30K;
        pull_up = 0x1;
      }
      else if(charger_dt_config->batt_therm_pull_up == PM_THERM_PULL_UP_400K)
      {
        channel_id = PM_THERM_CHANNEL_400K;
        pull_up = 0x3;
      }

      int loop_count = PM_ADC_POLL_TIMEOUT / PM_ADC_POLL_INTERVAL;
      while(loop_count-- > 0)
      {
        err_flag |= pm_scpq_misc_irq_status(pmic_index, PM_SCPQ_MISC_IRQ_ALL_CHNL_CONV_DONE, PM_IRQ_STATUS_LATCHED, &adc_conv_done);
                
        if((err_flag != PM_ERR_FLAG_SUCCESS) || adc_conv_done)
        {
          break;
        }
        else
        {
          pm_app_chg_pet_wdog();
          pm_busy_wait(PM_ADC_POLL_INTERVAL);
        }      
      }

      // We have no plan to write drive for periph ADC_CMN_BG. 
      // So we use pm_comm_write_byte to write value direct into this register.
      err_flag |= pm_comm_write_byte(pmic_index, 0x3061, pull_up);
      err_flag |= pm_scpq_misc_set_batt_therm_ch_id_cfg(pmic_index, channel_id);
     }     

    // configure QBG mode_ctl2 for ichg_fs_option
    if(charger_dt_config->apply_ichg_fs)
    {
      err_flag |= pm_qbg_set_qbg_mode_ctl2_ichg_fs_opt(pmic_index, (charger_dt_config->ichg_fs == PM_CHG_FS_24A) ? TRUE : FALSE);
    }

    //Puhi PBS OTP code will configure QBG_MAIN_QBG_MODE_CTL1, so read value and configure QBG_MAIN_CMN_ADC_CTL7 accordingly.
    err_flag |= pm_qbg_get_qbg_mode_ctl1_batt_opt(pmic_index, &battery_type);
    err_flag |= pm_qbg_get_qbg_mode_ctl3_batt_opt(pmic_index, &battery_2s_option);
    if(battery_type == PM_CHG_1S_BATT_TYPE  || (PM_CHG_DIS_VBAT_2S_MID == battery_2s_option) || (PM_CHG_EN_VBAT_2S_MID1 == battery_2s_option))
    {
      err_flag |= pm_qbg_set_tbat_thermal_calibration_method(pmic_index, PM_QBG_CAL_METHOD_ABS_CAL, PM_QBG_CAL_METHOD_RATIO_CAL);
    }
    else if(PM_CHG_EN_VBAT_2S_MID1_MID2 == battery_2s_option)
    {
      err_flag |= pm_qbg_set_tbat_thermal_calibration_method(pmic_index, PM_QBG_CAL_METHOD_RATIO_CAL, PM_QBG_CAL_METHOD_RATIO_CAL);
    }

    if(charger_dt_config->ignore_temp_in_dbc)
    {
      err_flag |= pm_scpq_batif_jeita_en_cfg(pmic_index, PM_SCPQ_BATIF_JEITA_AFP_COLD, FALSE);
      err_flag |= pm_scpq_batif_jeita_en_cfg(pmic_index, PM_SCPQ_BATIF_JEITA_AFP_HOT, FALSE);
      err_flag |= pm_scpq_batif_jeita_en_cfg(pmic_index, PM_SCPQ_BATIF_JEITA_HARD_LIMIT, FALSE);
    }
    else if(pm_get_img_type() == PM_IMG_LOADER)
    {
      err_flag |= pm_config_jeita();
    }
  }

  // configure float voltage threshold
  if(charger_dt_config->apply_float_voltage)
  {
    if(NULL != pm_schg_get_data(pmic_index))
    {
      err_flag |= pm_schg_chgr_set_float_volt(pmic_index, charger_dt_config->float_voltage_mv);
    }
    else if(NULL != pm_scpq_get_data(pmic_index))
    {
      err_flag |= pm_scpq_chgr_set_float_volt(pmic_index, charger_dt_config->float_voltage_mv);
    }
  }

  if(charger_dt_config->apply_vsysmin)
  {
    if(NULL != pm_schg_get_data(pmic_index))
    {
      err_flag |= pm_schg_dcdc_configure_vsysmin(pmic_index, charger_dt_config->vsysmin);
    }
    else if(NULL != pm_scpq_get_data(pmic_index))
    {
      err_flag |= pm_scpq_chgr_configure_vsysmin(pmic_index, charger_dt_config->vsysmin);
    }
  }

  // configure pre_charging current limit
  if(charger_dt_config->apply_pre_charge_current)
  {
    if(NULL != pm_schg_get_data(pmic_index))
    {
      err_flag |= pm_schg_chgr_set_charge_current(pmic_index, PM_SCHG_CHGR_PRE_CHARGE_CURRENT, charger_dt_config->pre_charge_ma);
    }
    else if(NULL != pm_scpq_get_data(pmic_index))
    {
      err_flag |= pm_scpq_chgr_set_charge_current(pmic_index, PM_SCPQ_CHGR_PRE_CHARGE_CURRENT, charger_dt_config->pre_charge_ma);
    }
  }

  // configure fast charging current limit
  if(charger_dt_config->apply_fast_charge_current)
  {
    if(NULL != pm_schg_get_data(pmic_index))
    {
      err_flag |= pm_schg_chgr_set_charge_current(pmic_index, PM_SCHG_CHGR_FAST_CHARGE_CURRENT, charger_dt_config->fast_charge_ma);
    }
    else if(NULL != pm_scpq_get_data(pmic_index))
    {
      err_flag |= pm_scpq_chgr_set_charge_current(pmic_index, PM_SCPQ_CHGR_FAST_CHARGE_CURRENT, charger_dt_config->fast_charge_ma);
    }
  }

  // configure usbin input current limit
  if(charger_dt_config->apply_icl)
  {
    err_flag |= pm_app_chg_configure_usb_icl(charger_dt_config->icl_ma);
  }

  if(charger_dt_config->usb_suspend)
  {
    if(NULL != pm_schg_get_data(pmic_index))
    {
      err_flag |= pm_schg_usb_set_usbin_suspend(pmic_index, TRUE);
    }
    else if(NULL != pm_scpq_get_data(pmic_index))
    {
      err_flag |= pm_scpq_usb_set_usbin_suspend(pmic_index, PM_SCPQ_USB_USBIN_SUSPEND, TRUE);
    }
  }


  // TODO: Implement API and using API call instead.
  err_flag |= pm_scpq_usb_set_input_priority(pmic_index, (pm_scpq_usb_input_priority_type)charger_dt_config->wls_usb_prior_swap);

  return err_flag;
}


pm_err_flag_type 
pm_app_chg_check_weak_battery_status(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_chg_charger_port_type charger_type = PM_CHARGER_PORT_TYPE_INVALID;
  uint32 battery_voltage = 0;
  int32 battery_current = 0;
#ifndef FEATURE_XBOOT
  uint32 cell_threshold = 0;
#endif /* !FEATURE_XBOOT */
  boolean charging_ongoing = FALSE;
  boolean light_on = FALSE;
  static boolean first_loop = TRUE;
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();
#ifndef FEATURE_XBOOT
  boolean battery_is_2s = FALSE;
#endif /* !FEATURE_XBOOT */

  uint32 pmic_index_charger = PMIC_INDEX_MAX;
  err_flag = pm_chg_get_primary_charger_pmic_index(&pmic_index_charger);
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  err_flag |= pm_chg_get_charger_port_type(&charger_type);
  
#ifndef FEATURE_XBOOT
  if(charger_type == PM_CHARGER_PORT_SDP_CHARGER)
  {
    cell_threshold = (PM_IMG_LOADER == pm_get_img_type()) ? 
                      charger_dt_config->loader_dbc_threshold + charger_dt_config->dbc_sdp_thd_inc : charger_dt_config->core_dbc_threshold;
  }
  else
  {
    cell_threshold = (PM_IMG_LOADER == pm_get_img_type()) ? 
                      charger_dt_config->loader_dbc_threshold : charger_dt_config->core_dbc_threshold;
  }

  err_flag |= pm_chg_is_2s_batt(&battery_is_2s);
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }
                            
  uint32 dbc_threshold = battery_is_2s ? (cell_threshold * 2) : cell_threshold;
#endif /* !FEATURE_XBOOT */

  while(TRUE)
  {
    err_flag = pm_chg_get_vbatt(&battery_voltage);
    err_flag |= pm_chg_get_ibatt(&battery_current);

    if(PM_ERR_FLAG_SUCCESS != err_flag)
    {
      return err_flag;
    }

    pm_log_message("VBAT: %dmV IBAT: %dmA", battery_voltage, battery_current);

#ifndef FEATURE_XBOOT
    if(battery_voltage > dbc_threshold)
    {
      break; // continue booting up since the voltage has crossed the threshold
    }
#endif /* !FEATURE_XBOOT */

    err_flag = pm_chg_is_charging_ongoing(&charging_ongoing);
    if(PM_ERR_FLAG_SUCCESS != err_flag)
    {
      return err_flag;
    }

    // Since USB charging is by default disabled in some charger PMIC,
    // we need some delay to double check if charging is really not happen.
    if(TRUE == first_loop)
    {
      first_loop = FALSE;

      if(NULL != pm_scpq_get_data(pmic_index_charger))
      {
        //Configure VPH_TRACK_SEL = 7% once if sw go to SBL charging loop (VBAT <= 3.3V)
        //This is to guarantee that the pre-charger has sufficient headroom. 
        err_flag |= pm_scpq_chgr_vph_track_threshold_sel(pmic_index_charger, PM_SCPQ_VPH_TRACK_SEL_7_PCT);
      }

      if(FALSE == charging_ongoing)
      {
        err_flag |= pm_busy_wait(PM_WEAK_BATTERY_CHARGING_DELAY);
        continue;
      }
    }

    if(FALSE == charging_ongoing)
    {
#ifdef FEATURE_XBOOT
      if (battery_voltage > charger_dt_config->core_dbc_threshold)
      {
         break; // continue booting up since the voltage has crossed the threshold
      }
      pm_log_message("Not charging. Shutdown");
#endif /* FEATURE_XBOOT */
      // Not charging and vbat lower than dead battery charging, shutdown
      err_flag |= pm_device_shutdown();
    }
    else
    {
#ifdef FEATURE_XBOOT
      err_flag |= pm_app_chg_configure_usb_icl_somc();
#endif /* FEATURE_XBOOT */
      // In charging, output charger information. Is it charged by USB or wireless
      // For USB charger, which charger type is connected.
      err_flag |= pm_app_chg_output_charging_status();
      // Delay a certain duration and toggle LED
      err_flag |= pm_busy_wait(PM_WEAK_BATTERY_CHARGING_DELAY);
      err_flag |= pm_rgb_led_config(PM_RGB_SEGMENT_R, PM_RGB_DIM_LEVEL_MID, light_on);
      light_on = (light_on == TRUE) ? FALSE : TRUE;

      if(PM_ERR_FLAG_SUCCESS != err_flag)
      {
        return err_flag;
      }

      pm_app_chg_pet_wdog();
#ifdef FEATURE_XBOOT
      pm_log_message("Primary Charging loop exit");
      break;
#endif /* FEATURE_XBOOT */
    }
  }

  // Turn off LED after exiting charging
  err_flag |= pm_rgb_led_config(PM_RGB_SEGMENT_R, PM_RGB_DIM_LEVEL_MID, FALSE);

#ifdef FEATURE_XBOOT
   err_flag |= pm_sbl_config_chg_parameters_somc(pmic_index_charger);
   err_flag |= pm_schg_usb_set_usbin_adptr_allowance_somc(pmic_index_charger);
#endif /* FEATURE_XBOOT */

  return err_flag;
}


static pm_err_flag_type 
pm_app_chg_is_dam_cable_connected(uint32 charger_index, boolean* connected)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  if((NULL == connected) || (charger_index > PMIC_INDEX_MAX))
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  if(NULL != pm_schg_get_data(charger_index))
  {
    err_flag |= pm_schg_typec_get_dam_connect_sts(charger_index, connected);
  }
  else if(NULL != pm_scpq_get_data(charger_index))
  {
    err_flag |= pm_scpq_typec_get_dam_connect_sts(charger_index, connected);
  }
  else
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  return err_flag;
}


static pm_err_flag_type 
pm_app_chg_get_icl_final(uint32 charger_index, uint32* icl_final)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_schg_dcdc_icl_status_type icl_schg = {0};
  pm_scpq_dcdc_icl_status_type icl_scpq = {0};

  if((NULL == icl_final) || (charger_index > PMIC_INDEX_MAX))
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  if(NULL != pm_schg_get_data(charger_index))
  {
    err_flag |= pm_schg_dcdc_get_icl_status(charger_index, &icl_schg);
    *icl_final = icl_schg.final_icl_status;
  }
  else if(NULL != pm_scpq_get_data(charger_index))
  {
    err_flag |= pm_scpq_dcdc_get_icl_status(charger_index, &icl_scpq);
    *icl_final = icl_scpq.icl_final_status;
  }
  else
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  return err_flag;
}


/*
 * Config ICL except :
 *     1. Charger type is SDP
 *     2. DAM cable connected without battery
 */
pm_err_flag_type 
pm_app_chg_configure_usb_icl(uint32 icl_ma)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_chg_charger_port_type charger_type = PM_CHARGER_PORT_TYPE_INVALID;
  uint32 final_icl          = 0;
  boolean is_dam_cable      = FALSE;
  boolean battery_present   = TRUE;
  uint32 charger_index = PMIC_INDEX_MAX;

  err_flag = pm_chg_get_primary_charger_pmic_index(&charger_index);
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  do
  {
    err_flag |= pm_chg_get_charger_port_type(&charger_type);
    err_flag |= pm_app_chg_is_dam_cable_connected(charger_index, &is_dam_cable);
    err_flag |= pm_chg_is_battery_present(&battery_present);
    if((err_flag != PM_ERR_FLAG_SUCCESS)
        || ((PM_CHARGER_PORT_SDP_CHARGER == charger_type) && (FALSE == is_dam_cable))
        || ((TRUE == is_dam_cable) && (FALSE == battery_present)))
    {
      break;
    }

    if(PM_CHARGER_PORT_SDP_CHARGER == charger_type)
    {
      // for SDP and DAM concurrency, we need to override as 500ma instead of USB500 mode.
      icl_ma = PM_SDP_ICL_MA;
    }
    else if(PM_CHARGER_PORT_CDP_CHARGER == charger_type)
    {
      icl_ma = PM_CDP_ICL_MIN_MA;
    }

    // Check and use the available charger driver
    if(NULL != pm_schg_get_data(charger_index))
    {
      //Set USBIN_MODE_CHG to USB_HIGH_CURRENT_MODE
      err_flag |= pm_schg_usb_configure_usbin_icl_options(charger_index, PM_SCHG_USB_ICL_OPTIONS_USBIN_MODE_CHG, TRUE);
      //Set ICL_OVERRIDE_AFTER_APSD
      err_flag |= pm_schg_usb_enable_icl_override_after_apsd(charger_index, TRUE);
      //Set ICL config
      err_flag |= pm_schg_usb_set_usbin_current_limit_cfg(charger_index, icl_ma);
      //Disable AICL to update ICL status
      err_flag |= pm_schg_usb_aicl_options_cfg(charger_index, PM_SCHG_USB_AICL_CFG_AICL_EN, FALSE);
      //Delay 10ms
      pm_busy_wait(10 * 1000);
      //Enable AICL
      err_flag |= pm_schg_usb_aicl_options_cfg(charger_index, PM_SCHG_USB_AICL_CFG_AICL_EN, TRUE);
    }
    else if(NULL != pm_scpq_get_data(charger_index))
    {
#ifdef FEATURE_XBOOT
      //Set USB51_MODE to 500mA mode
      err_flag |= pm_scpq_usb_configure_usb_icl_options(charger_index, PM_SCPQ_USB_ICL_OPTIONS_USB51_MODE, TRUE);
#endif /* FEATURE_XBOOT */
      //Set USBIN_MODE_CHG to USB_HIGH_CURRENT_MODE
      err_flag |= pm_scpq_usb_configure_usb_icl_options(charger_index, PM_SCPQ_USB_ICL_OPTIONS_USBIN_MODE_CHG, TRUE);
      //Set ICL_OVERRIDE_AFTER_APSD
      err_flag |= pm_scpq_usb_enable_icl_override_after_apsd(charger_index, TRUE);
      //Set ICL config
      err_flag |= pm_scpq_usb_set_icl_cfg(charger_index, icl_ma);
      //Disable AICL, then SCPQ_P_DCDC_ICL_STATUS | 0x2709 could be changed to icl_ma
      err_flag |= pm_scpq_usb_aicl_options_cfg(charger_index, PM_SCPQ_USB_AICL_EN, FALSE, USBIN_COLLAPSE_GF_5MS, USBIN_AICL_STEP_10MS);
      //Delay 10ms
      pm_busy_wait(10 * 1000);
      //Enable AICL
      err_flag |= pm_scpq_usb_aicl_options_cfg(charger_index, PM_SCPQ_USB_AICL_EN, TRUE, USBIN_COLLAPSE_GF_5MS, USBIN_AICL_STEP_10MS);
    }
    else
    {
      err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
  } while (FALSE);

  err_flag |= pm_app_chg_get_icl_final(charger_index, &final_icl);
  pm_log_message("%sICL final: %dmA", is_dam_cable ? "DAM Cable, " : "", final_icl);

  return err_flag;
}


/* Get the two cell vbat for 2S battery */
static pm_err_flag_type 
pm_app_chg_get_2cell_vbat(uint32* vcell1, uint32* vcell2)
{
  pm_err_flag_type err_flag  = PM_ERR_FLAG_SUCCESS;
  adc_status_type adc_status = ADC_STATUS_SUCCESS;
  adc_result_type adc_vbat = {0}, adc_vbat_mid = {0};
  boolean battery_is_2s = FALSE;

  if((NULL == vcell1) || (NULL == vcell2))
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  err_flag = pm_chg_is_2s_batt(&battery_is_2s);    
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  if(FALSE == battery_is_2s)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  // Get 2s battery S+ volt, sum of two cells voltage
  adc_status |= adc_read(ADC_INPUT_VBATT_2S, &adc_vbat);
  // Get 2s battery mid volt, one cell voltage
  adc_status |= adc_read(ADC_INPUT_VBATT_2S_MID, &adc_vbat_mid);

  if(adc_status != ADC_STATUS_SUCCESS)
  {
    pm_log_message("adc_read error: %d. %s %d", adc_status, __func__, __LINE__);
    return PM_ERR_FLAG_FAILURE;
  }

  *vcell2 = adc_vbat_mid.microvolts / 1000;
  *vcell1 = adc_vbat.microvolts / 1000 - *vcell2;

  return err_flag;
}


pm_err_flag_type 
pm_app_chg_battery_uv_oc_detection()
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 vcell              = 0;
  boolean recovered         = TRUE;
  boolean charging          = FALSE;
  boolean light_on          = TRUE;
  uint32 v_sys_min_backup = 3000; // default vsys_min is 3000mv.
  int32 v_sys_min_step = 0;
  uint32 v_float_backup = 0;
  uint32 i_pre_chg_backup = 0;
  uint32 charger_index = PMIC_INDEX_MAX;
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();
  boolean battery_is_2s = FALSE;

  err_flag = pm_chg_is_2s_batt(&battery_is_2s);    
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }
  
  uint32 vcell_thld = battery_is_2s ? charger_dt_config->uv_oc_2s_threshold : charger_dt_config->uv_oc_1s_threshold;

  err_flag = pm_chg_get_primary_charger_pmic_index(&charger_index);
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  if(NULL != pm_scpq_get_data(charger_index))
  {
    //Configure VPH_TRACK_SEL = 7% once if sw go to SBL charging loop (VBAT <= 3.3V)
    //This is to guarantee that the pre-charger has sufficient headroom. 
    err_flag |= pm_scpq_chgr_vph_track_threshold_sel(charger_index, PM_SCPQ_VPH_TRACK_SEL_7_PCT);
  }

  err_flag |= pm_chg_get_vbatt(&vcell);
  if((NULL != pm_scpq_get_data(charger_index)) && (vcell < vcell_thld))
  {
    //Get current V_sys_min, V_float, I_pre_chg settings, restore them after battery recovered
    err_flag |= pm_scpq_chgr_get_vsysmin_cfg(charger_index, &v_sys_min_backup);
    err_flag |= pm_scpq_chgr_get_float_volt_cfg(charger_index, &v_float_backup);
    err_flag |= pm_scpq_chgr_get_charge_current_cfg(charger_index, PM_SCPQ_CHGR_PRE_CHARGE_CURRENT, &i_pre_chg_backup);

    //Set V_sys_min = 4.6v, V_float = 4.5v(1S) / 9.0v(2S), IPRE_CFG = 250mA(1S) / 125mA(2S) 
    //This is to ensure battery can only charge in pre/trickle state with low charging current at the beginning
    err_flag |= pm_scpq_chgr_configure_vsysmin(charger_index, charger_dt_config->vsys_min_recover_mv);
    err_flag |= pm_scpq_chgr_set_float_volt(charger_index, charger_dt_config->vflt_recover_mv);
    err_flag |= pm_scpq_chgr_set_charge_current(charger_index, PM_SCPQ_CHGR_PRE_CHARGE_CURRENT, BATTERY_UV_OC_I_PRE_CFG_IN_MA);

    //Disable SMB1399 protections for 2s battery
    err_flag |= pm_app_chg_enable_smb_protections(FALSE);

    //Enable charging and charger wdog
    err_flag |= pm_chg_enable_usb_charging(TRUE);
    err_flag |= pm_chg_enable_wireless_charging(TRUE);
    err_flag |= pm_app_chg_enable_charger_wdog(TRUE);

    //Waiting for charging status update at 1st time charging enable
    err_flag |= pm_busy_wait(PM_WEAK_BATTERY_CHARGING_DELAY);

    //waiting for battery recovered
    while(vcell < vcell_thld)
    {
      pm_log_message("Vbat:%dmV", vcell);
      pm_busy_wait(BATTERY_UV_OC_RECOVERY_TIME_IN_MS * 1000);

      err_flag |= pm_chg_is_charging_ongoing(&charging);
      if(FALSE == charging)
      {
        recovered = FALSE;
        break;
      }

      err_flag |= pm_app_chg_output_charging_status();
      err_flag |= pm_rgb_led_config(PM_RGB_SEGMENT_R, PM_RGB_DIM_LEVEL_MID, light_on);
      light_on = (light_on == TRUE) ? FALSE : TRUE;

      err_flag |= pm_chg_get_vbatt(&vcell);
      if((vcell >= vcell_thld) && (TRUE == battery_is_2s))
      {
        // The required delay is different between protection IC. VBAT is close to VFloat before protect FET is closed.
        for(uint32 time = 0; time < charger_dt_config->uvp_recover_delay; time += WDOG_PET_INTERVAL_MS)
        {
          pm_app_chg_pet_wdog();
          uint32 uvp_recover_delay_remain = charger_dt_config->uvp_recover_delay - time;            
          if(uvp_recover_delay_remain > WDOG_PET_INTERVAL_MS) 
          {     
            uvp_recover_delay_remain = WDOG_PET_INTERVAL_MS;                
          }
          
          pm_busy_wait(uvp_recover_delay_remain * 1000);
      
          err_flag |= pm_rgb_led_config(PM_RGB_SEGMENT_R, PM_RGB_DIM_LEVEL_MID, light_on);
          light_on = (light_on == TRUE) ? FALSE : TRUE;
        }
        
        err_flag |= pm_chg_get_vbatt(&vcell);
      }

      // Pet the watch dog so it does not bark during recovery
      pm_app_chg_pet_wdog();
    }

    //Step down V_sys_min setting by 100ms/step whenever battery is recovered or not
    for(v_sys_min_step = charger_dt_config->vsys_min_recover_mv - v_sys_min_backup; v_sys_min_step >= 0; v_sys_min_step -= VSYSMIN_RECOVER_STEP_MV)
    {
      err_flag |= pm_scpq_chgr_configure_vsysmin(charger_index, v_sys_min_backup + v_sys_min_step);
      pm_busy_wait(BATTERY_UV_OC_VSYS_MIN_STEP_DOWN_INTERVAL_MS * 1000);
    }

    //Restore V_float, I_pre_chg settings whenever battery is recovered or not
    err_flag |= pm_scpq_chgr_set_float_volt(charger_index, v_float_backup);
    err_flag |= pm_scpq_chgr_set_charge_current(charger_index, PM_SCPQ_CHGR_PRE_CHARGE_CURRENT, i_pre_chg_backup);

    //Enable SMB1399 protections for 2s battery
    err_flag |= pm_app_chg_enable_smb_protections(TRUE);

    if(FALSE == recovered)
    {
      pm_log_message("battery recover failed");
      //Wait 1s to flush out the uart log
      pm_busy_wait(1 * 1000 * 1000);
      err_flag |= pm_device_shutdown();
    }

    pm_log_message("Battery recovered");
  }

  // Turn off LED after exiting recovery
  err_flag |= pm_rgb_led_config(PM_RGB_SEGMENT_R, PM_RGB_DIM_LEVEL_MID, FALSE);

  return err_flag;
}

/* SMB1399 protections for 2s battery UV/OC recovery */
static pm_err_flag_type 
pm_app_chg_enable_smb_protections(boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  boolean battery_is_2s = FALSE;

  err_flag = pm_chg_is_2s_batt(&battery_is_2s);    
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }  

  if(TRUE == battery_is_2s)
  {
    // D2 WIN_OV (0x267A[5])
    err_flag |= pm_comm_write_byte_mask_ex(1, SMB_139X_SID, SMB_139X_SCHG_PERPH0_CFG_SDCDC, MASK_CFG_EN_WIN_OV, enable ? MASK_CFG_EN_WIN_OV : 0);
    // X2 WIN_OV (0x26C8[3])
    err_flag |= pm_comm_write_byte_mask_ex(1, SMB_139X_SID, SMB_139X_SCHG_PERPH0_ENG_SDCDC_3LVL_B_LOOP_ERR_CFG, MASK_ENG_X2_WIN_OV, enable ? MASK_ENG_X2_WIN_OV : 0);
    // VBAT2_UV (0X2680[3])
    err_flag |= pm_comm_write_byte_mask_ex(1, SMB_139X_SID, SMB_139X_SCHG_PERPH0_SOVP_CFG0, MASK_CFG_EN_UV_RISE_DEB, enable ? MASK_CFG_EN_UV_RISE_DEB : 0);
  }

  return err_flag;
}


pm_err_flag_type
pm_app_chg_enable_charger_wdog(boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_chgr_wdog_cfg_type wdog_cfg = {0};
  uint32 charger_index = PMIC_INDEX_MAX;

  err_flag = pm_chg_get_primary_charger_pmic_index(&charger_index);
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  if(NULL != pm_scpq_get_data(charger_index))
  {
    err_flag |= pm_scpq_chgr_set_wd_bark_timeout(charger_index, 32 * 1000);
    err_flag |= pm_scpq_chgr_get_config_wdog(charger_index, &wdog_cfg);

    wdog_cfg.wdog_timer_en = enable;
    //if enable, charging will disable when charger wdog bite
    wdog_cfg.bite_wdog_disable_charging_cfg = enable;

    err_flag |= pm_scpq_chgr_config_wdog(charger_index, wdog_cfg);
  }

  return err_flag;
}


static void
pm_app_chg_pet_wdog(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 charger_index = PMIC_INDEX_MAX;

  err_flag = pm_chg_get_primary_charger_pmic_index(&charger_index);

  if(NULL != pm_scpq_get_data(charger_index))
  {
    err_flag |= pm_scpq_chgr_bark_bite_wdog_pet(charger_index);
    if(PM_ERR_FLAG_SUCCESS != err_flag)
    {
      pm_log_message("Pet Charger wdog failed");
    }
  }

  // Pet TME introduced watch dog enabling during boot, not charger wdog
  pm_watch_dog_pet();

  return;
}


static pm_err_flag_type 
pm_app_chg_no_battery_boot_config(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();

  if(charger_dt_config->apply_boot_wo_batt)
  {
    if(charger_dt_config->boot_wo_batt)
    {
      //Enable charging for booting up without battery
      err_flag |= pm_chg_enable_usb_charging(TRUE);
      err_flag |= pm_chg_enable_wireless_charging(TRUE);
      //Config usb ICL
      err_flag |= pm_app_chg_configure_usb_icl(charger_dt_config->icl_boot_wo_batt);
    }
    else
    {
      pm_log_message("No battery, Shutdown!");
      pm_device_shutdown();
    }
  }

  return err_flag;
}



static pm_err_flag_type
pm_app_chg_is_apsd_done(boolean* done)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 charger_index = PMIC_INDEX_MAX;

  err_flag = pm_chg_get_primary_charger_pmic_index(&charger_index);
  if(err_flag == PM_ERR_FLAG_SUCCESS)
  {
    if(NULL != pm_scpq_get_data(charger_index))
    {
      err_flag = pm_scpq_usb_get_apsd_status(charger_index, PM_SCPQ_USB_APSD_STATUS_APSD_DTC_STATUS_DONE , done);
    }
    else if(NULL != pm_schg_get_data(charger_index))
    {
      err_flag = pm_schg_usb_get_apsd_status(charger_index, PM_SCHG_USB_APSD_STATUS_APSD_DTC_STATUS_DONE, done);
    }
    else
    {
      err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
  }

  return err_flag;
}


static pm_err_flag_type
pm_app_chg_restart_aicl_at_max(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 charger_index = PMIC_INDEX_MAX;

  err_flag = pm_chg_get_primary_charger_pmic_index(&charger_index);
  if(err_flag == PM_ERR_FLAG_SUCCESS)
  {
    if(NULL != pm_scpq_get_data(charger_index))
    {
      //USBIN_AICL_START_AT_MAX = 1;
      err_flag |= pm_scpq_usb_aicl_options_cfg(charger_index, PM_SCPQ_USB_AICL_START_AT_MAX, TRUE, USBIN_COLLAPSE_GF_5MS, USBIN_AICL_STEP_10MS);
      //Restart_AICL = 1;
      err_flag |= pm_scpq_misc_aicl_cmd_enable(charger_index, PM_SCPQ_MISC_AICL_CMD_RESTART_AICL);
    }
    else if(NULL != pm_schg_get_data(charger_index))
    {
      err_flag |= pm_schg_usb_aicl_options_cfg(charger_index, PM_SCHG_USB_AICL_CFG_AICL_START_AT_MAX, TRUE);
      err_flag |= pm_schg_misc_aicl_cmd(charger_index, PM_SCHG_MISC_AICL_CMD_RESTART_AICL);
    }
    else
    {
      err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
  }

  return err_flag;
}

/*
  For AICL from max ->It means the input current is adjust from the max.(default it starts from 500ma)
  For example, ICL is set to max (e.g. 3A) and then reduce step by step till the proper ICL value is applied.
  OEMs often perfer start from the max. They observed issues that the power consumption is higher than 500ma and battery is absent.
  So if we skip DBC, then need to call this funtion to prevent device brown out by higher power consumption
*/
static pm_err_flag_type
pm_app_chg_wait_apsd_and_aicl_from_max(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 charger_index = PMIC_INDEX_MAX;
  boolean apsd_done = FALSE;
  boolean vbus_present = TRUE;

  err_flag = pm_chg_get_primary_charger_pmic_index(&charger_index);
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  // SBL waiting for APSD done
  while((TRUE == vbus_present) && (FALSE == apsd_done))
  {
    err_flag |= pm_chg_is_vbus_present(&vbus_present);
    err_flag |= pm_app_chg_is_apsd_done(&apsd_done);
    if(TRUE == apsd_done)
    {
      err_flag |= pm_app_chg_restart_aicl_at_max();
      break;
    }
    pm_busy_wait(PM_WAIT_FOR_APSD_DONE_DELAY);
  }

  return err_flag;
}

pm_err_flag_type
pm_app_chg_dead_battery_charging(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  boolean bypass_dbc = FALSE;

  err_flag |= pm_app_chg_dbc_condition_check(&bypass_dbc);
  if(TRUE == bypass_dbc)
  {
    return err_flag;
  }

  err_flag |= pm_app_chg_battery_uv_oc_detection();

  err_flag |= pm_chg_enable_usb_charging(TRUE);
  err_flag |= pm_chg_enable_wireless_charging(TRUE);

  err_flag |= pm_app_chg_enable_charger_wdog(TRUE);
  err_flag |= pm_app_chg_check_weak_battery_status();

  return err_flag;
}


pm_err_flag_type pm_config_jeita()
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 pmic_index = PMIC_INDEX_MAX;

  err_flag = pm_chg_get_primary_charger_pmic_index(&pmic_index);
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  if(NULL != pm_scpq_get_data(pmic_index))
  {
    err_flag = pm_scpq_config_jeita(pmic_index);
  }
  else if(NULL != pm_schg_get_data(pmic_index))
  {
    err_flag = pm_schg_config_jeita(pmic_index);
  }
  else
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  return err_flag;
}

pm_err_flag_type pm_scpq_config_jeita(uint32 pmic_index)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();
  uint32 code = 0;
  int32 temp = 0;
  uint16 adc_code = 0;
  
  // configure too cold AFP
  err_flag |= pm_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, charger_dt_config->too_cold_afp_threshold, &code);
  err_flag |= pm_scpq_batif_set_jeita_threshold_value(pmic_index, PM_SCPQ_BATIF_JEITA_THRESHOLD_TOO_COLD_AFP, code);
  err_flag |= pm_scpq_batif_jeita_en_cfg(pmic_index, PM_SCPQ_BATIF_JEITA_AFP_COLD, charger_dt_config->apply_too_cold_afp);
  
  // configure too hot AFP
  err_flag |= pm_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, charger_dt_config->too_hot_afp_threshold, &code);
  err_flag |= pm_scpq_batif_set_jeita_threshold_value(pmic_index, PM_SCPQ_BATIF_JEITA_THRESHOLD_TOO_HOT_AFP, code);
  err_flag |= pm_scpq_batif_jeita_en_cfg(pmic_index, PM_SCPQ_BATIF_JEITA_AFP_HOT, charger_dt_config->apply_too_hot_afp);

  //configure too cold
  err_flag |= pm_scpq_batif_get_jeita_threshold_value(pmic_index, PM_SCPQ_BATIF_JEITA_THRESHOLD_TOO_COLD, &adc_code);
  err_flag |= pm_get_batt_temp_of_adc_code(PM_ADC_PU_100K, (uint32)adc_code, &temp);
  err_flag |= pm_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, temp, &code);
  err_flag |= pm_scpq_batif_set_jeita_threshold_value(pmic_index, PM_SCPQ_BATIF_JEITA_THRESHOLD_TOO_COLD, code);

  //configure too hot
  err_flag |= pm_scpq_batif_get_jeita_threshold_value(pmic_index, PM_SCPQ_BATIF_JEITA_THRESHOLD_TOO_HOT, &adc_code);
  err_flag |= pm_get_batt_temp_of_adc_code(PM_ADC_PU_100K, (uint32)adc_code, &temp);
  err_flag |= pm_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, temp, &code);
  err_flag |= pm_scpq_batif_set_jeita_threshold_value(pmic_index, PM_SCPQ_BATIF_JEITA_THRESHOLD_TOO_HOT, code);
  
  //configure warm
  err_flag |= pm_scpq_batif_get_jeita_threshold_value(pmic_index, PM_SCPQ_BATIF_JEITA_THRESHOLD_WARM, &adc_code);
  err_flag |= pm_get_batt_temp_of_adc_code(PM_ADC_PU_100K, (uint32)adc_code, &temp);
  err_flag |= pm_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, temp, &code);
  err_flag |= pm_scpq_batif_set_jeita_threshold_value(pmic_index, PM_SCPQ_BATIF_JEITA_THRESHOLD_WARM, code);

  //configure cool  
  err_flag |= pm_scpq_batif_get_jeita_threshold_value(pmic_index, PM_SCPQ_BATIF_JEITA_THRESHOLD_COOL, &adc_code);
  err_flag |= pm_get_batt_temp_of_adc_code(PM_ADC_PU_100K, (uint32)adc_code, &temp);
  err_flag |= pm_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, temp, &code);
  err_flag |= pm_scpq_batif_set_jeita_threshold_value(pmic_index, PM_SCPQ_BATIF_JEITA_THRESHOLD_COOL, code);

  return err_flag;
}

pm_err_flag_type pm_schg_config_jeita(uint32 pmic_index)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();  
  uint32 code = 0;  
  int32 temp = 0;  
  uint16 adc_code = 0;
  
  // configure too cold AFP
  err_flag |= pm_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, charger_dt_config->too_cold_afp_threshold, &code);
  err_flag |= pm_schg_chgr_set_jeita_threshold_value(pmic_index, PM_SCHG_CHGR_JEITA_THRESHOLD_TOO_COLD_AFP, code);
  err_flag |= pm_schg_chgr_jeita_en_cfg(pmic_index, PM_SCHG_CHGR_JEITA_AFP_COLD, charger_dt_config->apply_too_cold_afp);
  
  // configure too hot AFP
  err_flag |= pm_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, charger_dt_config->too_hot_afp_threshold, &code);
  err_flag |= pm_schg_chgr_set_jeita_threshold_value(pmic_index, PM_SCHG_CHGR_JEITA_THRESHOLD_TOO_HOT_AFP, code);
  err_flag |= pm_schg_chgr_jeita_en_cfg(pmic_index, PM_SCHG_CHGR_JEITA_AFP_HOT, charger_dt_config->apply_too_hot_afp);

  //configure too cold
  err_flag |= pm_schg_chgr_get_jeita_threshold_value(pmic_index, PM_SCHG_CHGR_JEITA_THRESHOLD_TOO_COLD, &adc_code);
  err_flag |= pm_get_batt_temp_of_adc_code(PM_ADC_PU_100K, (uint32)adc_code, &temp);
  err_flag |= pm_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, (int32)temp, &code);
  err_flag |= pm_schg_chgr_set_jeita_threshold_value(pmic_index, PM_SCHG_CHGR_JEITA_THRESHOLD_TOO_COLD, code);

  //configure too hot
  err_flag |= pm_schg_chgr_get_jeita_threshold_value(pmic_index, PM_SCHG_CHGR_JEITA_THRESHOLD_TOO_HOT, &adc_code);  
  err_flag |= pm_get_batt_temp_of_adc_code(PM_ADC_PU_100K, (uint32)adc_code, &temp);
  err_flag |= pm_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, temp, &code);
  err_flag |= pm_schg_chgr_set_jeita_threshold_value(pmic_index, PM_SCHG_CHGR_JEITA_THRESHOLD_TOO_HOT, code);
  
  //configure hot
  err_flag |= pm_schg_chgr_get_jeita_threshold_value(pmic_index, PM_SCHG_CHGR_JEITA_THRESHOLD_HOT, &adc_code);
  err_flag |= pm_get_batt_temp_of_adc_code(PM_ADC_PU_100K, (uint32)adc_code, &temp);
  err_flag |= pm_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, temp, &code);
  err_flag |= pm_schg_chgr_set_jeita_threshold_value(pmic_index, PM_SCHG_CHGR_JEITA_THRESHOLD_HOT, code);

  //configure cold
  err_flag |= pm_schg_chgr_get_jeita_threshold_value(pmic_index, PM_SCHG_CHGR_JEITA_THRESHOLD_COLD, &adc_code);
  err_flag |= pm_get_batt_temp_of_adc_code(PM_ADC_PU_100K, (uint32)adc_code, &temp);
  err_flag |= pm_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, temp, &code);
  err_flag |= pm_schg_chgr_set_jeita_threshold_value(pmic_index, PM_SCHG_CHGR_JEITA_THRESHOLD_COLD, code);

  return err_flag;
}

