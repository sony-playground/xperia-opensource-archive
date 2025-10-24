/*! \file
*
*  \brief  pm_schg_driver.c driver implementation.
*  \details charger driver implementation.
*  &copy;
*  Copyright (c) 2017-2022 Qualcomm Technologies, Inc.  All Rights Reserved.
*  Qualcomm Technologies Proprietary and Confidential.
*/

/*===========================================================================

EDIT HISTORY FOR MODULE


when       who    what, where, why
--------   ---    ----------------------------------------------------------
08/01/18    ivy   Added support to set batt therm pull up to register
06/29/18    dc    Expand ICL Status API for Max ICL
06/21/18    cs    Added support for multi-port.
05/17/18    ivy   Added support for Qi charging ICL register
05/14/18    ra    Support for Debug Accessory Mode
03/01/18    ra    Adding skin and die temp registers
03/05/18    pxm   Remove unused registers.
01/23/18    aab   Added support for USB typec APIs
01/15/18    ra    Adding JEITA registers
11/12/17    aab   Moved common Register address defination to driver file
12/19/16    sm    Added API to get SCHG Charger PmicIndex
09/07/16    sm    Added pm_schg_get_dig_major API to return digital major
04/18/14    al    Initial revision
========================================================================== */

/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include "pm_schg_driver.h"
#include "CoreVerify.h"
#include "hw_module_type.h"

/*===========================================================================

                        STATIC VARIABLES

===========================================================================*/

/* Static global variable to store the SCHG driver data */
static pm_schg_data_type *pm_schg_data_arr[PM_MAX_NUM_PMICS];
static pm_register_data_type dig_major = 0;

#define SCHG_MISC_REVISION2       0x1601
#define SCHG_SLAVE_ID             0x2
#define PMIC_SCHG_MISC_MAX_HW_VER 0x2 

static schg_chgr_register_ds schg_chgr_reg =
{
  .base_address                        = 0x1000,
  .battery_charger_status_1            = 0x06,
  .battery_charger_status_3            = 0x09,
  .charging_enable_cmd                 = 0x42,
  .charger_cfg2                        = 0x51,
  .pre_charge_current_cfg              = 0x60,
  .fast_charge_current_cfg             = 0x61,
  .termination_charge_current_cfg      = 0x62,
  .tccc_charge_current_termination_cfg = 0x63,
  .float_voltage_cfg                   = 0x70,
  .jeita_fvcomp_cold_cfg               = 0x86,
  .jeita_en_cfg                        = 0x90,
  .jeita_fvcomp_hot_cfg                = 0x91,
  .jeita_cccomp_hot_cfg                = 0x92,
  .jeita_cccomp_cold_cfg               = 0x93,
  .jeita_hot_threshold_msb             = 0x94,
  .jeita_hot_threshold_lsb             = 0x95,
  .jeita_cold_threshold_msb            = 0x96,
  .jeita_cold_threshold_lsb            = 0x97,
  .jeita_thot_threshold_msb            = 0x98,
  .jeita_thot_threshold_lsb            = 0x99,
  .jeita_tcold_threshold_msb           = 0x9A,
  .jeita_tcold_threshold_lsb           = 0x9B,
  .jeita_thot_afp_threshold_msb        = 0x9C,
  .jeita_thot_afp_threshold_lsb        = 0x9D,
  .jeita_tcold_afp_threshold_msb       = 0x9E,
  .jeita_tcold_afp_threshold_lsb       = 0x9F
};

static schg_dcdc_register_ds schg_dcdc_reg =
{
  .base_address           = 0x1100,
  .perph_type             = 0x04,
  .perph_subtype          = 0x05,
  .icl_max_status         = 0x06,
  .power_path_status      = 0x0B,
  .lockbit_d1             = 0xD1,
  .lockbit_d2             = 0xD2,
  .otg_status             = 0x0D,
  .int_rt_sts             = 0x10,
  .int_set_type           = 0x11,
  .int_polarity_high      = 0x12,
  .int_polarity_low       = 0x13,
  .int_latched_clr        = 0x14,
  .int_en_set             = 0x15,
  .int_en_clr             = 0x16,
  .int_latched_sts        = 0x18,
  .int_pending_sts        = 0x19,
  .int_mid_sel            = 0x1A,
  .int_priority           = 0x1B,
  .cmd_otg                = 0x40,
  .bat_uvlo_threshold_cfg = 0x51,
  .otg_current_limit_cfg  = 0x52,
  .otg_cfg                = 0x53,
  .vsysmin_cfg            = 0x83
};

static schg_batif_register_ds schg_batif_reg =
{
  .base_address           = 0x1200,
  .batt_miss_sts          = 0x06,
  .int_rt_sts             = 0x10,
  .int_set_type           = 0x11,
  .int_polarity_high      = 0x12,
  .int_polarity_low       = 0x13,
  .int_latched_clr        = 0x14,
  .int_en_set             = 0x15,
  .int_en_clr             = 0x16,
  .int_latched_sts        = 0x18,
  .int_pending_sts        = 0x19,
  .ship_mode              = 0x40,
  .low_batt_threshold_cfg = 0x61,
  .bat_miss_src_cfg       = 0x70,
  .fake_batid_ch_en       = 0x91,
};

static schg_usb_register_ds schg_usb_reg =
{
  .base_address            = 0x1300,
  .apsd_status             = 0x07,
  .apsd_result_status      = 0x08,
  .int_rt_sts              = 0x10,
  .int_set_type            = 0x11,
  .int_polarity_high       = 0x12,
  .int_polarity_low        = 0x13,
  .int_latched_clr         = 0x14,
  .int_en_set              = 0x15,
  .int_en_clr              = 0x16,
  .int_latched_sts         = 0x18,
  .int_pending_sts         = 0x19,
  .cmd_il                  = 0x40,
  .cmd_apsd                = 0x41,
  .usbin_adapter_allow_cfg = 0x60,
  .usbin_options_1_cfg     = 0x62,
  .usbin_load_cfg          = 0x65,
  .usbin_icl_options       = 0x66,
  .usbin_current_limit_cfg = 0x70,
  .usbin_aicl_options_cfg  = 0x80
};

static schg_typec_register_ds schg_typec_reg =
{
  .base_address               = 0x1500,
  .perph_type                 = 0x04,
  .perph_subtype              = 0x05,
  .lockbit_d1                 = 0xD1,
  .lockbit_d2                 = 0xD2,
  .typec_snk_status           = 0x06,
  .typec_misc_status          = 0x07,
  .typec_mode_cfg             = 0x44,
  .typec_vconn_control        = 0x46,
  .typec_debug_access_snk_cfg = 0x4A,
  .typec_debug_access_status  = 0x07
};

static schg_misc_register_ds schg_misc_reg =
{
  .base_address           = 0x1600,
  .wdog_status            = 0x0C,
  .sysok_reason_status    = 0x0D,
  .int_rt_sts             = 0x10,
  .int_set_type           = 0x11,
  .int_polarity_high      = 0x12,
  .int_polarity_low       = 0x13,
  .int_latched_clr        = 0x14,
  .int_en_set             = 0x15,
  .int_en_clr             = 0x16,
  .int_latched_sts        = 0x18,
  .int_pending_sts        = 0x19,
  .afp_mode               = 0x41,
  .bark_bite_wdog_pet     = 0x43,
  .aicl_cmd               = 0x44,
  .wd_cfg                 = 0x51,
  .snarl_bark_bite_wd_cfg = 0x53,
  .aicl_rerun_time_cfg    = 0x61,
  .thermreg_src_cfg       = 0x70,
  .die_temp_h_msb         = 0xA0,
  .die_temp_h_lsb         = 0xA1,
  .die_temp_l_msb         = 0xA2,
  .die_temp_l_lsb         = 0xA3
};

static schg_bob_register_ds schg_bob_reg =
{
  .base_address       = 0x1900,
  .perph_type         = 0x04,
  .perph_subtype      = 0x05,
  .multi_port_arbiter = 0x06
};

static schg_register_ds schg_reg =
{
  .chgr_register  = &schg_chgr_reg,
  .dcdc_register  = &schg_dcdc_reg,
  .batif_register = &schg_batif_reg,
  .usb_register   = &schg_usb_reg,
  .typec_register = &schg_typec_reg,
  .misc_register  = &schg_misc_reg,
  .bob_register   = &schg_bob_reg
};

/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/
void pm_schg_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint32 pmic_index)
{
  pm_schg_data_type *schg_ptr = NULL;
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 num_of_peripherals = 0;

  /*return if coincell since it is not supported at the moment*/
  if (PM_HW_MODULE_CHARGER_COINCELL == peripheral_info->peripheral_subtype)
  {
    return;
  }

  schg_ptr = pm_schg_data_arr[pmic_index];

  if (NULL == schg_ptr)
  {
    num_of_peripherals = pm_target_information_get_periph_count_info(PM_PROP_CHARGER_NUM, pmic_index);
    if (num_of_peripherals == 0)
    {
      return;
    }

    pm_malloc(sizeof(pm_schg_data_type), (void **)&schg_ptr);

    /* Assign Comm ptr */
    schg_ptr->comm_ptr = comm_ptr;

    /* schg Register Info - Obtaining Data through dal config */
    schg_ptr->schg_register = &schg_reg;
    CORE_VERIFY_PTR(schg_ptr->schg_register);

    schg_ptr->num_of_peripherals = num_of_peripherals;

    pm_schg_data_arr[pmic_index] = schg_ptr;

    err_flag = pm_comm_read_byte(SCHG_SLAVE_ID, SCHG_MISC_REVISION2, &dig_major);
    CORE_VERIFY((err_flag == PM_ERR_FLAG_SUCCESS) && (dig_major <= PMIC_SCHG_MISC_MAX_HW_VER));
  }
}

pm_schg_data_type *pm_schg_get_data(uint32 pmic_index)
{
  if (pmic_index < PM_MAX_NUM_PMICS)
  {
    return pm_schg_data_arr[pmic_index];
  }

  return NULL;
}

uint32 pm_schg_get_num_peripherals(uint32 pmic_index)
{
  if ((pmic_index < PM_MAX_NUM_PMICS) && (pm_schg_data_arr[pmic_index] != NULL))
  {
    return pm_schg_data_arr[pmic_index]->num_of_peripherals;
  }

  return 0;
}

uint8 pm_schg_get_dig_major(void)
{
  return dig_major;
}

void pm_schg_get_pmic_info(uint32 *pmic_index, uint32 *slave_id, uint32 *charger_count, uint32 max_charger)
{
  uint32 i = 0, count = 0;

  if (NULL == pmic_index || NULL == slave_id || NULL == charger_count)
  {
    return;
  }

  for (i = 0; (i < PM_MAX_NUM_PMICS) && (count < max_charger); i++)
  {
    if (pm_schg_data_arr[i] != NULL)
    {
      pmic_index[count] = pm_schg_data_arr[i]->comm_ptr->pmic_index;
      slave_id[count] = pm_schg_data_arr[i]->comm_ptr->slave_id;
      count++;
    }
  }
  *charger_count = count;
  return;
}

