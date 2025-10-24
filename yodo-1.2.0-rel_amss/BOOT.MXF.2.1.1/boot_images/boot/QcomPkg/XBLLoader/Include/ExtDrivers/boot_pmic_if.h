#ifndef BOOT_PMIC_IF_H
#define BOOT_PMIC_IF_H

/*===========================================================================

                    BOOT PMIC IF WRAPPERS DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external pmic drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2019-2022 by Qualcomm Technologies Incorporated.  All Rights Reserved.
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
08/01/19   ep      Created teh file

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "pm.h"
#include "pm_ldo.h"
#include "pm_lab.h"
#include "pm_ibb.h"
#include "pm_app_rgb.h"
#include "pm_wled.h"
#include "pm_chg.h"
#include "pm_lcdb.h"
#include "pm_app_haptics.h"
#include "pm_app_pon_log.h"
#include "pm_pon.h"
#include "pm_dump.h"
#include "pm_pbus.h"
#include "pm_pbs.h"

typedef struct boot_pmic_if_type
{
  pm_err_flag_type (*pm_device_init)(void);
  pm_err_flag_type (*pm_dev_get_power_on_reason)(unsigned pmic_device_index, uint64 * pwr_on_reason);
  pm_err_flag_type (*pm_app_pon_get_all_pon_events)(pm_pon_reason_events_data_type* pon_events_log); 
  pm_err_flag_type (*pm_pbs_get_pon_reason_history)(pm_pbs_pon_reason_history_data_type *pon_reason_history_ptr );
  pm_err_flag_type (*pm_driver_init)(void);
  pm_err_flag_type (*pm_sbl_chg_init)(void);
  pm_err_flag_type (*pm_system_init)(void);
  pm_err_flag_type (*pm_init_smem)(void);
  pm_err_flag_type (*pm_enable_led)(uint32, boolean);
  pm_err_flag_type (*pm_app_pon_pshold_cfg)(pm_app_pon_reset_cfg_type);
  pm_err_flag_type (*pm_vib_on)(void);
  pm_err_flag_type (*pm_vib_off)(void);
  pm_err_flag_type (*pm_infra_init)(void);
  pm_err_flag_type (*pm_pon_warm_reset_status)(unsigned pmic_device_index, boolean *status);
  pm_err_flag_type (*pm_pon_warm_reset_status_clear)(unsigned pmic_device_index);
  pm_err_flag_type (*pm_pon_wdog_cfg)(uint32 pmic_device_index, uint32 s1_timer, uint32 s2_timer, pm_pon_reset_cfg_type reset_cfg_type);
  pm_err_flag_type (*pm_pon_wdog_enable)(uint32 pmic_device_index,pm_on_off_type enable);
  pm_err_flag_type (*pm_pon_wdog_disable)(uint8 pmic_device_index, pm_on_off_type disable);
  pm_err_flag_type (*pm_aop_pre_init)(void);
  boot_boolean     (*check_display_vbatt)(void);
  pm_err_flag_type (*pm_ldo_sw_enable)(uint8 pmic_chip, uint8  ldo_peripheral_index, pm_on_off_type  on_off, boolean wait_for_settle);
  pm_err_flag_type (*pm_smps_sw_enable)(uint8 pmic_chip, uint8  smps_peripheral_index, pm_on_off_type  on_off, boolean wait_for_settle);
  pm_err_flag_type (*pm_ldo_volt_level)(uint8 pmic_chip, uint8 ldo_peripheral_index, pm_volt_level_type volt_level, boolean wait_for_settle);
  pm_err_flag_type (*pm_smps_volt_level)(uint8 pmic_chip, uint8 smps_peripheral_index, pm_volt_level_type volt_level, boolean wait_for_settle);
  pm_err_flag_type (*pm_ibb_ibb_module_rdy)(uint32 device_index, boolean ibb_rdy);
  pm_err_flag_type (*pm_ibb_config_ibb_ctrl)(uint32 device_index, boolean en_module, boolean swire_rdy);
  pm_err_flag_type (*pm_ibb_get_ibb_status)(uint32 device_index, pm_ibb_status_type* ibb_status);
  pm_err_flag_type (*pm_lab_config_current_sense)(uint32 device_index, pm_lab_isense_type isense_tap, pm_lab_isense_type isense_gain);
  pm_err_flag_type (*pm_lab_config_pulse_skip_ctrl)(uint32 device_index, uint32 ps_threshold, boolean select_ps_table, boolean select_digital_ps, boolean enable_ps);
  pm_err_flag_type (*pm_lab_lcd_amoled_sel)(uint32 device_index, boolean en_amoled_mode);
  pm_err_flag_type (*pm_lab_lab_module_rdy)(uint32 device_index, boolean lab_rdy);
  pm_err_flag_type (*pm_lab_ibb_rdy_en)(uint32 device_index, boolean ibb_rdy_en);
  pm_err_flag_type (*pm_lab_get_lab_status)(uint32 device_index, pm_lab_status_type* lab_status);
  pm_err_flag_type (*pm_wled_sel_ovp_thr)(uint32 pmic_device_index, uint32 resource_index, pm_wled_ovp_threshold_type ovp_threshold_type);
  pm_err_flag_type (*pm_wled_sel_bst_ilimit)(uint32 pmic_device_index, uint32 resource_index, pm_wled_bst_ilimit_type bst_ilimit_type);
  pm_err_flag_type (*pm_wled_set_fsw_ctrl)(uint32 pmic_device_index, uint32 resource_index, uint32 fsw_khz);
  pm_err_flag_type (*pm_wled_set_led_duty_cycle)(uint32 pmic_device_index, pm_wled_modulator_type modulator, uint16 data);
  pm_err_flag_type (*pm_wled_enable_current_sink)(uint32 pmic_device_index, pm_wled_led_type led_type);
  pm_err_flag_type (*pm_wled_enable_modulator)(uint32 pmic_device_index, pm_wled_modulator_type modulator, boolean enable);
  pm_err_flag_type (*pm_wled_enable_module)(uint32 pmic_device_index, uint32 resource_index, boolean enable);
  pm_err_flag_type (*pm_wled_en_sync)(uint32 pmic_device_index, pm_wled_led_type led_type, boolean enable);
  pm_err_flag_type (*pm_chg_get_vbatt)(uint32 *pvbat);
  pm_err_flag_type (*pm_lcdb_config_enable_ctrl)(uint32 device_index, pm_lcdb_enable_ctl_type ctl_type, boolean enable);
  pm_err_flag_type (*pm_lcdb_set_output_volt)(uint32 device_index, int32 ldo_mv, int32 ncp_mv, boolean symmetry_ok);
  pm_err_flag_type (*pm_lcdb_vreg_ok)(uint32 device_index, boolean *vreg_ok);
  pm_err_flag_type (*pm_app_pon_reset_cfg)(pm_app_pon_reset_source_type app_pon_reset_source, pm_app_pon_reset_cfg_type app_pon_reset_cfg, uint32 s1_timer, uint32 s2_timer);
  bl_error_boot_type (*set_pmic_device_index)(uint32);
  pm_err_flag_type (*pm_chg_is_vbus_present)(boolean *status);
  pm_err_flag_type (*pm_chg_get_typec_status)(pm_chg_typec_status_type *typec_status);
  pm_err_flag_type (*pm_wled_modulator_src_sel)( uint32 pmic_device_index, pm_wled_modulator_type modulator, pm_wled_modulator_src_type src );
  pm_err_flag_type (*pm_app_pon_debug_hard_reset)(void);
  pm_err_flag_type (*pm_oem_init)(void);
  pm_err_flag_type (*pm_post_tz_device_init)(void);
  pm_err_flag_type (*pm_pmic_dump)(uint8* buf, uint64 offset , uint64 size);
  pm_err_flag_type (*pm_pbus_logger)(uint8, pm_pbus_data_type *);
  pm_err_flag_type (*pm_psi_get_heap_buffer_info)(void **base_addr, uint32 *buf_size);
} boot_pmic_if_type;

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

//bl_error_boot_type boot_pmic_get_interface(void *ptr);

extern boot_pmic_if_type pmic_if;


#endif /* BOOT_PMIC_IF_H */
