/*===========================================================================

                    BOOT EXTERN PMIC DRIVER DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external pmic drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright 2019-2022 by Qualcomm Technologies, Incorporated.
                All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/05/22   ds      changes for moving heap registeration to top level
07/13/21   zxz     Added pm_pmic_dump_entry protocol
01/19/21   rhy     Added pm_pbus_logger
04/21/20   rhy     Added post tz device init
08/01/19   ep      Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_error_if.h"
#include "MIprogressive.h"
#include "boot_pmic_if.h"


/*battery threshold for enable the disply in RAMDUMP mode*/
#define BATT_DISPLAY_THRESHOLD   3700

static uint32 pmic_device_index = 1;

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/

boot_boolean boot_check_display_vbatt(void)
{

  UINT32 VBat = 0;
  UINT32 status = 0;

  status =  pm_chg_get_vbatt(&VBat);

  if ((VBat >= BATT_DISPLAY_THRESHOLD) && (status==0))
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}



/*===========================================================================

**  Function :  boot_pm_enable_led

** ==========================================================================
*/
/*!
 * @brief This function executes the pmic rgb led functions to turn on LED
 * @return Error flag.
 *
 */
pm_err_flag_type boot_pm_enable_led(uint32 led_color, boolean current_led_status)
{
  /* Enable LED based on input color parameter */
  return pm_rgb_led_config(led_color,
                           PM_RGB_DIM_LEVEL_HIGH,
                           current_led_status);
}



/*===========================================================================

**  Function :  boot_pm_vib_on

** ==========================================================================
*/
/*!
 * @brief This function initializes vibration driver voltage and turn on it
 * @return Error flag.
 *
 */

pm_err_flag_type boot_pm_vib_on(void)
{
  return pm_app_haptics_vib_ctrl(PM_ON);
}

/*===========================================================================

**  Function :  boot_pm_vib_off

** ==========================================================================
*/
/*!
 * @brief This function turn off vibration
 * @return Error flag.
 *
 */

pm_err_flag_type boot_pm_vib_off(void)
{
  return pm_app_haptics_vib_ctrl(PM_OFF);
}




/*===========================================================================

**  Function :  boot_pm_pon_wdog_disable

** ==========================================================================
*/
/*!
 *@brief  This function will disable the wdog with the given pmic_device_index.
 *
 *INPUT PARAMETERS
 *@param pmic_device_index
 *@param disable flag
 *
 *@return pm_err_flag_type.
 *
 *@par Dependencies
 * api boot_pm_pon_wdog_cfg() must have been called before calling this API
 *
 */
pm_err_flag_type boot_pm_pon_wdog_disable
(
  uint8 pmic_device_index,
  pm_on_off_type disable
)
{
#ifdef FIXME_REARCH
  return pm_pon_wdog_enable(pmic_device_index, disable);
#else
  return 0;
#endif
}

/*===========================================================================

**  Function :  boot_pm_aop_pre_init

** ==========================================================================
*/
/*!
 * @brief This function executes the pmic pre AOP initialization
 * @return Error flag.
 *
 */
pm_err_flag_type boot_pm_aop_pre_init(void)
{
  return pm_aop_pre_init();
}

/*===========================================================================

**  Function :  boot_pm_ldo_sw_enable

** ==========================================================================
*/
/*!
 *@brief Enables or disables a regulator or voltage switcher.
 *
 *  @param[in] pmic_chip            Primary PMIC: 0, Secondary PMIC: 1.
 *
 *  @param[in] ldo_peripheral_index LDO peripheral index. The first LDO
 *                                   peripheral starts at 0. See
 *                                  @xnameref{hdr:ldoPeripheralIndex}.
 *
 *  @param[in] on_off               Turns the regulator on and off.
 *                                  See #pm_on_off_type.
 *
 *  @return
 *  SUCCESS or Error -- See #pm_err_flag_type.
 */
pm_err_flag_type boot_pm_ldo_sw_enable (uint8 pmic_chip, uint8  ldo_peripheral_index, pm_on_off_type  on_off, boolean wait_for_settle)
{
  return pm_ldo_sw_enable(pmic_chip, ldo_peripheral_index, on_off, wait_for_settle);
}

/*!
 *@brief Enables or disables a regulator or voltage switcher.
 *
 *  @param[in] pmic_chip            Primary PMIC: 0, Secondary PMIC: 1.
 *
 *  @param[in] smps_peripheral_index SMPS peripheral index. The first SMPS
 *                                   peripheral starts at 0. See
 *                                  @xnameref{hdr:ldoPeripheralIndex}.
 *
 *  @param[in] on_off               Turns the regulator on and off.
 *                                  See #pm_on_off_type.
 *
 *  @return
 *  SUCCESS or Error -- See #pm_err_flag_type.
 */

pm_err_flag_type boot_pm_smps_sw_enable (uint8 pmic_chip, uint8  smps_peripheral_index, pm_on_off_type  on_off, boolean wait_for_settle)
{
  return pm_smps_sw_enable(pmic_chip, smps_peripheral_index, on_off, wait_for_settle);
}

/*===========================================================================

**  Function :  boot_pm_ldo_volt_level

** ==========================================================================
*/
/*!
 *@brief  Sets the voltage level for an LDO.
 *
 * @param[in] pmic_chip            Primary PMIC: 0, Secondary PMIC: 1.
 *
 * @param[in] ldo_peripheral_index LDO peripheral index. Starts from 0
 *                                 (for the first LDO peripheral).
 *                                 See @xnameref{hdr:ldoPeripheralIndex}.
 *
 * @param[in] volt_level           Voltage level.
 *
 * @return
 *  SUCCESS or Error -- See #pm_err_flag_type.
 */
pm_err_flag_type boot_pm_ldo_volt_level(uint8 pmic_chip, uint8 ldo_peripheral_index, pm_volt_level_type volt_level, boolean wait_for_settle)
{
  return pm_ldo_volt_level(pmic_chip, ldo_peripheral_index, volt_level, wait_for_settle);
}

/*===========================================================================

**  Function :  boot_pm_smps_volt_level

** ==========================================================================
*/
/*!
 *@brief  Sets the voltage level for an SMPS.
 *
 * @param[in] pmic_chip            Primary PMIC: 0, Secondary PMIC: 1.
 *
 * @param[in] ldo_peripheral_index SMPS peripheral index. Starts from 0
 *                                 (for the first SMPS peripheral).
 *                                 See @xnameref{hdr:SMPS PeripheralIndex}.
 *
 * @param[in] volt_level           Voltage level.
 *
 * @return
 *  SUCCESS or Error -- See #pm_err_flag_type.
 */
pm_err_flag_type boot_pm_smps_volt_level(uint8 pmic_chip, uint8 smps_peripheral_index, pm_volt_level_type volt_level, boolean wait_for_settle)
{
  return pm_smps_volt_level(pmic_chip, smps_peripheral_index, volt_level, wait_for_settle);
}


/*===========================================================================

**  Function :  boot_pm_ibb_ibb_module_rdy

** ==========================================================================
*/
/*!
 * @brief This function prepares module to be enabled or not
 *
 * @details
 *  This API prepares module to be enabled or not.
 *  When this is set to low, the IBB module cannot be enabled
 *  (powered-up) through S-Wire or IBB_ENABLE register
 *
 * @param[in] pmic_device_index.  Primary: 0 Secondary: 1
 * @param[in] ibb_rdy             TRUE if ready to be enabled else FALSE
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type boot_pm_ibb_ibb_module_rdy(uint32 device_index, boolean ibb_rdy)
{
  return pm_ibb_ibb_module_rdy(device_index, ibb_rdy);
}

/*===========================================================================

**  Function :  boot_pm_ibb_config_ibb_ctrl

** ==========================================================================
*/
/*!
 * @brief This function enables/disables module and makes S-wire ready for listening
 *
 * @details
 *  This API enables/disables module and makes S-wire ready for listening
 *
 * @param[in] pmic_device_index.  Primary: 0 Secondary: 1
 * @param[in] en_module      TRUE enables module and false disables module
 * @param[in] swire_rdy      TRUE ready to liste to to S-wire and FALSE not ready to listen to S-Wire
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
/*
pm_err_flag_type boot_pm_ibb_config_ibb_ctrl(uint32 device_index, boolean en_module, boolean swire_rdy)
{
  return pm_ibb_config_ibb_ctrl(device_index, en_module, swire_rdy);
}
*/
/*===========================================================================

**  Function :  boot_pm_ibb_get_ibb_status

** ==========================================================================
*/
/*!
 * @brief This reads the IBB module setting status
 *
 * @details
 *  This API reads the IBB module setting status
 *
 * @param[in] pmic_device_index.  Primary: 0 Secondary: 1
 * @param[in] ibb_status          Refer struct #pm_ibb_status_type for more info
 *
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
/*
pm_err_flag_type boot_pm_ibb_get_ibb_status(uint32 device_index, pm_ibb_status_type* ibb_status)
{
  return pm_ibb_get_ibb_status(device_index, ibb_status);
}
*/
/*===========================================================================

**  Function :  boot_pm_lab_config_current_sense

** ==========================================================================
*/
/*!
 * @brief This configures LAB current sense
 *
 * @details
 *  This API configures current sense tapping point and current
 *  sense gain
 *
 * @param[in] pmic_device_index.  Primary: 0 Secondary: 1
 * @param[in] isense_tap          : Current sense tapping point. Refer #pm_lab_isense_type for more info
 * @param[in] isense_gain         : Current sense gain. Refer #pm_lab_isense_type for more info
 *
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type boot_pm_lab_config_current_sense(uint32 device_index, pm_lab_isense_type isense_tap, pm_lab_isense_type isense_gain)
{
  return pm_lab_config_current_sense(device_index, isense_tap, isense_gain);
}

/*===========================================================================

**  Function :  boot_pm_lab_config_pulse_skip_ctrl

** ==========================================================================
*/
/*!
* @brief This configures LAB pulse skipping parameters
 *
 * @details
 *  This API configures pulse skipping parameters
 *
 * @param[in] pmic_device_index.  Primary: 0 Secondary: 1
 * @param[in] ps_threshold      : Threshold when pulse skipping mode is entered. Range is 20 to 50 mAmps
 * @param[in] select_ps_table   : TRUE to slected PS table, otherwise FALSE
 * @param[in] select_digital_ps : TRUE to slected DIGITAL PS, otherwise FALSE for ANALOG
 * @param[in] enable_ps         : TRUE to enable PS, otherwise FALSE to disable it
 *
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type boot_pm_lab_config_pulse_skip_ctrl(uint32 device_index, uint32 ps_threshold, boolean select_ps_table, boolean select_digital_ps, boolean enable_ps)
{
  return pm_lab_config_pulse_skip_ctrl(device_index, ps_threshold, select_ps_table, select_digital_ps, enable_ps);
}

/*===========================================================================

**  Function :  boot_pm_lab_lcd_amoled_sel

** ==========================================================================
*/
/*!
 * @brief This function configures module for AMOLED or LCD
 *
 * @details
 *  This API configures module for AMOLED or LCD
 *
 * @param[in] pmic_device_index.  Primary: 0 Secondary: 1
 * @param[in] en_amoled_mode      TRUE enables for AMOLED and FALSE for LCD
 *
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type boot_pm_lab_lcd_amoled_sel(uint32 device_index, boolean en_amoled_mode)
{
  return pm_lab_lcd_amoled_sel(device_index, en_amoled_mode);
}

/*===========================================================================

**  Function :  boot_pm_lab_lab_module_rdy

** ==========================================================================
*/
/*!
 * @brief This function configures module to be enabled or not enabled
 *
 * @details
 *  This API configures module to be enabled or not enabled
 *
 * @param[in] pmic_device_index.  Primary: 0 Secondary: 1
 * @param[in] lab_rdy             TRUE if ready to be enabled else FALSE
 *
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type boot_pm_lab_lab_module_rdy(uint32 device_index, boolean lab_rdy)
{
  return pm_lab_lab_module_rdy(device_index, lab_rdy);
}

/*===========================================================================

**  Function :  boot_pm_lab_ibb_rdy_en

** ==========================================================================
*/
/*!
 * @brief This function sets LAB to be enabled by IBB or not
 *
 * @details
 *  This API allows LAB to be enabled by IBB or not
 *
 * @param[in] pmic_device_index.  Primary: 0 Secondary: 1
 * @param[in] ibb_en_rdyTRUE      TRUE allows IBB module to enable LAB and FALSE won't
 *
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type boot_pm_lab_ibb_rdy_en(uint32 device_index, boolean ibb_rdy_en)
{
  return pm_lab_ibb_rdy_en(device_index, ibb_rdy_en);
}

/*===========================================================================

**  Function :  boot_pm_lab_get_lab_status

** ==========================================================================
*/
/*!
 * @brief This reads the LAB module setting status
 *
 * @details
 *  This API reads the LAB module setting status
 *
 * @param[in] pmic_device_index.  Primary: 0 Secondary: 1
 * @param[in] lab_status          Refer struct #pm_lab_status_type for more info
 *
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type boot_pm_lab_get_lab_status(uint32 device_index, pm_lab_status_type* lab_status)
{
  return pm_lab_get_lab_status(device_index, lab_status);
}

/*===========================================================================

**  Function :  boot_pm_wled_sel_ovp_thr

** ==========================================================================
*/
/*!
 * @brief This function selects OVP threshold
 *
 * @param[in] ovp_threshold_type
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 */
pm_err_flag_type boot_pm_wled_sel_ovp_thr(uint32 pmic_device_index, uint32 resource_index, pm_wled_ovp_threshold_type ovp_threshold_type)
{
  return pm_wled_sel_ovp_thr(pmic_device_index, resource_index, ovp_threshold_type);
}

/*===========================================================================

**  Function :  boot_pm_wled_sel_bst_ilimit

** ==========================================================================
*/
/*!
 * @brief This function selects boost current limit
 *
 * @param[in] bst_ilimit_type
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type boot_pm_wled_sel_bst_ilimit(uint32 pmic_device_index, uint32 resource_index, pm_wled_bst_ilimit_type bst_ilimit_type)
{
  return pm_wled_sel_bst_ilimit(pmic_device_index, resource_index, bst_ilimit_type);
}

/*===========================================================================

**  Function :  boot_pm_wled_set_fsw_ctrl

** ==========================================================================
*/
/*!
 *@brief  This function is used to set FSW.
 *
 *INPUT PARAMETERS
 *@param pmic_device_index
 *@param resource_index
 *@param fsw_khz
 *
 *@return pm_err_flag_type.
 *
 *@par Dependencies
 * api boot_pm_pon_wdog_cfg() must have been called before calling this API
 *
 */
pm_err_flag_type boot_pm_wled_set_fsw_ctrl(uint32 pmic_device_index, uint32 resource_index, uint32 fsw_khz)
{
  return pm_wled_set_fsw_ctrl(pmic_device_index, resource_index, fsw_khz);
}

/*===========================================================================

**  Function :  boot_pm_wled_set_led_duty_cycle

** ==========================================================================
*/
/*!
 *@brief  This function is uesd to set duty cycle.
 *
 *INPUT PARAMETERS
 *@param pmic_device_index
 *@param pm_wled_modulator_type
 *@param duty cycle data
 *
 *@return pm_err_flag_type.
 *
 *@par Dependencies
 * api boot_pm_pon_wdog_cfg() must have been called before calling this API
 *
 */
pm_err_flag_type boot_pm_wled_set_led_duty_cycle(uint32 pmic_device_index, pm_wled_modulator_type modulator, uint16 data)
{
  return pm_wled_set_led_duty_cycle(pmic_device_index, modulator, data);
}

/*===========================================================================

**  Function :  boot_pm_wled_enable_current_sink

** ==========================================================================
*/
/*!
 *@brief  This function is uesd to enable WLED current source.
 *
 *INPUT PARAMETERS
 *@param pmic_device_index
 *@param led_type
 *
 *@return pm_err_flag_type.
 */
pm_err_flag_type boot_pm_wled_enable_current_sink(uint32 pmic_device_index, pm_wled_led_type led_type)
{
  return pm_wled_enable_current_sink(pmic_device_index, led_type);
}

/*===========================================================================

**  Function :  boot_pm_wled_enable_modulator

** ==========================================================================
*/
/*!
 *@brief  This function is uesd to enable WLED modulator
 *
 *INPUT PARAMETERS
 *@param pmic_device_index
 *@param led_type
 *@param disable flag
 *
 *@return pm_err_flag_type.
 *
 */
pm_err_flag_type boot_pm_wled_enable_modulator(uint32 pmic_device_index, pm_wled_modulator_type modulator, boolean enable)
{
  return pm_wled_enable_modulator(pmic_device_index, modulator, enable);
}

/*===========================================================================

**  Function :  boot_pm_wled_en_sync

** ==========================================================================
*/
/*!
 *@brief  This function is used to enable WLED sync.
 *
 *INPUT PARAMETERS
 *@param pmic_device_index
 *@param led_type
 *@param disable flag
 *
 *@return pm_err_flag_type.
 *
 */
pm_err_flag_type boot_pm_wled_en_sync(uint32 pmic_device_index, pm_wled_led_type led_type, boolean enable)
{
  return pm_wled_en_sync(pmic_device_index, led_type, enable);
}


/*===========================================================================

**  Function :  boot_pm_chg_get_vbatt

** ==========================================================================
*/
/*!
 *@brief  This function is uesd to get battery voltage
 *
 *INPUT PARAMETERS
 *@param pVBat
 *
 *@return pm_err_flag_type.
 *
 */
pm_err_flag_type boot_pm_chg_get_vbatt(uint32 *pvbat)
{
  return pm_chg_get_vbatt(pvbat);
}


pm_err_flag_type boot_pm_lcdb_set_output_volt(uint32 device_index, int32 ldo_mv, int32 ncp_mv, boolean symmetry_ok)
{
  return pm_lcdb_set_output_volt(device_index, ldo_mv, ncp_mv, symmetry_ok);
}



bl_error_boot_type boot_set_pmic_device_index(uint32 _pmic_device_index)
{
  pmic_device_index = _pmic_device_index;

  return BL_ERR_NONE;
}

pm_err_flag_type boot_pm_app_pon_pshold_cfg(pm_app_pon_reset_cfg_type reset_type)
{
  return pm_app_pon_pshold_cfg(reset_type);
}

pm_err_flag_type boot_pm_app_pon_debug_hard_reset(void)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type boot_pm_oem_init(void)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type boot_pm_pon_wdog_cfg(uint32 pmic_device_index, uint32 s1_timer, uint32 s2_timer, pm_pon_reset_cfg_type reset_cfg_type)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type boot_pm_pon_wdog_enable(uint32 pmic_device_index, pm_on_off_type enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type boot_pm_post_tz_device_init(void)
{
  return PM_ERR_FLAG_SUCCESS;
}

/*===========================================================================
**  Function :  boot_pmic_get_interface
** ==========================================================================
*/
/*!
*
* @brief
*   This function initializes a boot_pmic_if
*
* @par Dependencies
*   None
*
*/
/*
bl_error_boot_type boot_pmic_get_interface(void *ptr)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    boot_pmic_if_type *pmic_if = (boot_pmic_if_type *)ptr;
    if(pmic_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_PMIC, BL_ERR_INVALID_PARAMETER);
      break;
    }

    pmic_if->pm_device_init = pm_device_init;
    pmic_if->pm_dev_get_power_on_reason = pm_pon_get_all_pon_reasons;
    pmic_if->pm_pbs_get_pon_reason_history = pm_pbs_get_pon_reason_history;
    pmic_if->pm_driver_init = pm_driver_init;
    pmic_if->pm_sbl_chg_init = pm_sbl_chg_init;
    pmic_if->pm_system_init = pm_system_init;
    pmic_if->pm_init_smem = pm_smem_init;
    pmic_if->pm_enable_led = boot_pm_enable_led;
    pmic_if->pm_app_pon_pshold_cfg = pm_app_pon_pshold_cfg;
    pmic_if->pm_vib_on = boot_pm_vib_on;
    pmic_if->pm_vib_off = boot_pm_vib_off;
    pmic_if->pm_infra_init = pm_infra_init;
    pmic_if->pm_pon_warm_reset_status = pm_pon_warm_reset_status;
    pmic_if->pm_pon_warm_reset_status_clear = pm_pon_warm_reset_status_clear;
    pmic_if->pm_pon_wdog_cfg = pm_pon_wdog_cfg;
    pmic_if->pm_pon_wdog_enable = pm_pon_wdog_enable;
    pmic_if->pm_pon_wdog_disable = boot_pm_pon_wdog_disable;
    pmic_if->pm_aop_pre_init = pm_aop_pre_init;
    pmic_if->check_display_vbatt = boot_check_display_vbatt;
    pmic_if->pm_ldo_sw_enable = pm_ldo_sw_enable;
    pmic_if->pm_smps_sw_enable = pm_smps_sw_enable;
    pmic_if->pm_ldo_volt_level = pm_ldo_volt_level;
    pmic_if->pm_smps_volt_level = pm_smps_volt_level;
    pmic_if->pm_ibb_ibb_module_rdy = pm_ibb_ibb_module_rdy;
    pmic_if->pm_ibb_config_ibb_ctrl = pm_ibb_config_ibb_ctrl;
    pmic_if->pm_ibb_get_ibb_status = pm_ibb_get_ibb_status;
    pmic_if->pm_lab_config_current_sense = pm_lab_config_current_sense;
    pmic_if->pm_lab_config_pulse_skip_ctrl = pm_lab_config_pulse_skip_ctrl;
    pmic_if->pm_lab_lcd_amoled_sel = pm_lab_lcd_amoled_sel;
    pmic_if->pm_lab_lab_module_rdy = pm_lab_lab_module_rdy;
    pmic_if->pm_lab_ibb_rdy_en = pm_lab_ibb_rdy_en;
    pmic_if->pm_lab_get_lab_status = pm_lab_get_lab_status;
    pmic_if->pm_wled_sel_ovp_thr = pm_wled_sel_ovp_thr;
    pmic_if->pm_wled_sel_bst_ilimit = pm_wled_sel_bst_ilimit;
    pmic_if->pm_wled_set_fsw_ctrl = pm_wled_set_fsw_ctrl;
    pmic_if->pm_wled_set_led_duty_cycle = pm_wled_set_led_duty_cycle;
    pmic_if->pm_wled_enable_current_sink = pm_wled_enable_current_sink;
    pmic_if->pm_wled_enable_modulator = pm_wled_enable_modulator;
    pmic_if->pm_wled_enable_module = pm_wled_enable_module;
    pmic_if->pm_wled_en_sync = pm_wled_enable_module;
    pmic_if->pm_chg_get_vbatt = pm_chg_get_vbatt;
    pmic_if->pm_lcdb_config_enable_ctrl = pm_lcdb_config_enable_ctrl;
    pmic_if->pm_lcdb_set_output_volt = pm_lcdb_set_output_volt;
    pmic_if->pm_lcdb_vreg_ok = pm_lcdb_vreg_ok;
    pmic_if->pm_app_pon_reset_cfg = pm_app_pon_reset_cfg;

  } while(FALSE);

  return return_status;
}
*/



boot_pmic_if_type pmic_if =
{
  pm_device_init,                  // pm_device_init
  pm_pon_get_all_pon_reasons,    // pm_dev_get_power_on_reason
  pm_app_pon_get_all_pon_events,      // pm_app_pon_get_all_pon_events
  pm_pbs_get_pon_reason_history,   // pm_pbs_get_pon_reason_history
  pm_driver_init,          // pm_driver_init
  pm_sbl_chg_init,        // pm_sbl_chg_init
  pm_system_init,            // pm_system_init
  pm_smem_init,          // pm_init_smem
  boot_pm_enable_led,        // pm_enable_led
  pm_app_pon_pshold_cfg,      // pm_app_pon_pshold_cfg
  boot_pm_vib_on,          // pm_vib_on
  boot_pm_vib_off,        // pm_vib_off
  pm_infra_init,          // pm_infra_init
  pm_pon_warm_reset_status,    // pm_pon_warm_reset_status
  pm_pon_warm_reset_status_clear,  // pm_pon_warm_reset_status_clear
  boot_pm_pon_wdog_cfg,        // pm_pon_wdog_cfg
  boot_pm_pon_wdog_enable,    // pm_pon_wdog_enable
  boot_pm_pon_wdog_disable,       // pm_pon_wdog_disable
  pm_aop_pre_init,                // pm_aop_pre_init
  boot_check_display_vbatt,    // check_display_vbatt
  pm_ldo_sw_enable,        // pm_ldo_sw_enable
  pm_smps_sw_enable,        // pm_smps_sw_enable
  pm_ldo_volt_level,        // pm_ldo_volt_level
  pm_smps_volt_level,          // pm_smps_volt_level
  pm_ibb_ibb_module_rdy,        // pm_ibb_ibb_module_rdy
  pm_ibb_config_ibb_ctrl,      // pm_ibb_config_ibb_ctrl
  pm_ibb_get_ibb_status,      // pm_ibb_get_ibb_status
  pm_lab_config_current_sense,  // pm_lab_config_current_sense
  pm_lab_config_pulse_skip_ctrl,  // pm_lab_config_pulse_skip_ctrl
  pm_lab_lcd_amoled_sel,      // pm_lab_lcd_amoled_sel
  pm_lab_lab_module_rdy,        // pm_lab_lab_module_rdy
  pm_lab_ibb_rdy_en,        // pm_lab_ibb_rdy_en
  pm_lab_get_lab_status,      // pm_lab_get_lab_status
  pm_wled_sel_ovp_thr,      // pm_wled_sel_ovp_thr
  pm_wled_sel_bst_ilimit,      // pm_wled_sel_bst_ilimit
  pm_wled_set_fsw_ctrl,        // pm_wled_set_fsw_ctrl
  pm_wled_set_led_duty_cycle,    // pm_wled_set_led_duty_cycle
  pm_wled_enable_current_sink,  // pm_wled_enable_current_sink
  pm_wled_enable_modulator,    // pm_wled_enable_modulator
  pm_wled_enable_module,      // pm_wled_enable_module
  boot_pm_wled_en_sync,      // pm_wled_en_sync
  pm_chg_get_vbatt,            // pm_chg_get_vbatt
  pm_lcdb_config_enable_ctrl,      // pm_lcdb_config_enable_ctrl
  pm_lcdb_set_output_volt,    // pm_lcdb_set_output_volt
  pm_lcdb_vreg_ok,          // pm_lcdb_vreg_ok
  pm_app_pon_reset_cfg,        // pm_app_pon_reset_cfg
  boot_set_pmic_device_index,      // set_pmic_device_index
  pm_chg_is_vbus_present,         // pm_chg_is_vbus_present
  pm_chg_get_typec_status,        // pm_chg_get_typec_status
  pm_wled_modulator_src_sel,      // pm_wled_modulator_src_sel
  pm_app_pon_debug_hard_reset,    // pm_app_pon_debug_hard_reset
  boot_pm_oem_init,               // pm_oem_init
  boot_pm_post_tz_device_init,    // pm_post_tz_device_init
  pm_pmic_dump_entry,             // pm_pmic_dump
  pm_pbus_logger,                 // pm_pbus_logger
  pm_psi_get_heap_buffer_info     // pm_psi_get_heap_buffer_info
};



