/*! \file
*
*  \brief  pm_scpq_driver.c driver implementation.
*  \details charger driver implementation.
*  &copy;
*  Copyright (c) 2020-2022 Qualcomm Technologies, Inc.  All Rights Reserved.
*  Qualcomm Technologies Proprietary and Confidential.
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE


when        who    what, where, why
--------    ---    ----------------------------------------------------------
12/02/19    zzx    Initial revision
========================================================================== */

/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include "pm_scpq_driver.h"
#include "CoreVerify.h"
#include "hw_module_type.h"

/*===========================================================================

                        STATIC VARIABLES

===========================================================================*/

/* Static global variable to store the SCPQ driver data */
static pm_scpq_data_type *pm_scpq_data_arr[PM_MAX_NUM_PMICS];

#define SCPQ_MISC_REVISION2   0x2C01
#define SCPQ_SLAVE_ID         0x3

static scpq_chgr2_register_ds scpq_chgr2_reg =
{
  .peripheral_offset   = 0x000,
  .int_latched_clr     = 0x14,
  .int_en_set          = 0x15,
  .int_en_clr          = 0x16,
  .bat_2s_charge_cfg   = 0x80,
};

static scpq_chgr_register_ds scpq_chgr_reg =
{
  .peripheral_offset   = 0x100,
  .charger_status      = 0x06,
  .vsys_min_cfg        = 0x40,
  .vph_pre_chg_cfg     = 0x41,
  .chg_en              = 0x46,
  .ipre_cfg            = 0x50,
  .ichg_cfg            = 0x54,
  .vflt_cfg            = 0x58,
  .chg_term_cfg        = 0x60,
  .wd_cfg              = 0x94,
  .wd_bb_time_sel      = 0x95,
  .wd_snarl_time_sel   = 0x96,
  .bark_bite_wdog_pet  = 0x97,
};


static scpq_dcdc_register_ds scpq_dcdc_reg =
{
  .peripheral_offset   = 0x200,
  .perph_type          = 0x04,
  .perph_subtype       = 0x05,
  .icl_max_status      = 0x06,
  .power_path_status   = 0x0B,
  .lockbit_d1          = 0xD1,
  .lockbit_d2          = 0xD2,
  .bst_status          = 0x0D, // bst = boost
  .int_rt_sts          = 0x10,
  .int_set_type        = 0x11,
  .int_polarity_high   = 0x12,
  .int_polarity_low    = 0x13,
  .int_latched_clr     = 0x14,
  .int_en_set          = 0x15,
  .int_en_clr          = 0x16,
  .int_latched_sts     = 0x18,
  .int_pending_sts     = 0x19,
  .int_mid_sel         = 0x1A,
  .int_priority        = 0x1B,
  .bst_en              = 0x50, // bst = boost
  .bst_cfg             = 0x56  // bst = boost
};


static scpq_batif_register_ds scpq_batif_reg =
{
  .peripheral_offset       = 0x300,
  .int_rt_sts              = 0x10,
  .int_set_type            = 0x11,
  .int_polarity_high       = 0x12,
  .int_polarity_low        = 0x13,
  .int_latched_clr         = 0x14,
  .int_en_set              = 0x15,
  .int_en_clr              = 0x16,
  .int_latched_sts         = 0x18,
  .int_pending_sts         = 0x19,
  .ship_mode               = 0x52,
  .afp_mode                = 0x53,
  .bpd_cfg                 = 0x60,  // Battery Missing Pin Source
  .batt_diffsense_cfg      = 0x68,
  .jeita_en_cfg            = 0x7F,
  .jeita_thot_thd_msb      = 0x84,
  .jeita_thot_thd_lsb      = 0x85,
  .jeita_warm_thd_msb      = 0x86,
  .jeita_warm_thd_lsb      = 0x87,
  .jeita_cool_thd_msb      = 0x88,
  .jeita_cool_thd_lsb      = 0x89,
  .jeita_tcold_thd_msb     = 0x8A,
  .jeita_tcold_thd_lsb     = 0x8B,
  .jeita_thot_afp_thd_msb  = 0x8C,
  .jeita_thot_afp_thd_lsb  = 0x8D,
  .jeita_tcold_afp_thd_msb = 0x8E,
  .jeita_tcold_afp_thd_lsb = 0x8F
};


static scpq_usb_register_ds scpq_usb_reg =
{
  .peripheral_offset       = 0x400,
  .apsd_status             = 0x0A,
  .apsd_result_status      = 0x0B,
  .qc_change_status        = 0x0C,
  .qc_pulse_count_status   = 0x0D,
  .int_rt_sts              = 0x10,
  .int_set_type            = 0x11,
  .int_polarity_high       = 0x12,
  .int_polarity_low        = 0x13,
  .int_latched_clr         = 0x14,
  .int_en_set              = 0x15,
  .int_en_clr              = 0x16,
  .int_latched_sts         = 0x18,
  .int_pending_sts         = 0x19,
  .usbin_adapter_allow_cfg = 0x40,
  .apsd_cmd                = 0x45,
  .usb_icl_options         = 0x50,
  .usb_icl_override        = 0x51,
  .usb_icl_cfg             = 0x52,
  .usb_suspend             = 0x54,
  .usb_aicl_cfg            = 0x60,
  .inov_cfg                = 0x68,
  .input_swap_ctl          = 0x80
};

static scpq_wls_register_ds scpq_wls_reg =
{
  .peripheral_offset       = 0x500,
  .int_rt_sts              = 0x10,
  .int_latched_sts         = 0x18,
  .int_pending_sts         = 0x19,
  .wls_icl_cfg             = 0x52,
  .wls_suspend             = 0x54
};


static scpq_typec_register_ds scpq_typec_reg =
{
  .peripheral_offset          = 0x600,
  .perph_type                 = 0x04,
  .perph_subtype              = 0x05,
  .typec_snk_status           = 0x06,
  .typec_debug_access_status  = 0x07,
  .typec_misc_status          = 0x0B,
  .typec_mode_cfg             = 0x44,
  .typec_vconn_control        = 0x46,
  .typec_debug_access_snk_cfg = 0x4A,
  .lockbit_d1                 = 0xD1
};


static scpq_misc_register_ds scpq_misc_reg =
{
  .peripheral_offset          = 0x700,
  .sysok_reason_status        = 0x0D,
  .int_rt_sts                 = 0x10,
  .int_set_type               = 0x11,
  .int_polarity_high          = 0x12,
  .int_polarity_low           = 0x13,
  .int_latched_clr            = 0x14,
  .int_en_set                 = 0x15,
  .int_en_clr                 = 0x16,
  .int_latched_sts            = 0x18,
  .int_pending_sts            = 0x19,
  .aicl_cmd                   = 0x50,
  .aicl_rerun_time_cfg        = 0x54,
  .therm_reg_src_cfg          = 0x60,
  .die_temp_h_thd_msb         = 0x64,
  .die_temp_h_thd_lsb         = 0x65,
  .die_temp_l_thd_msb         = 0x66,
  .die_temp_l_thd_lsb         = 0x67,
  .batt_therm_ch_id           = 0x9A,
  .batt_therm_ch_en           = 0x99,
  .vin_div16_mux_sel          = 0xBC
};


/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/
void pm_scpq_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint32 pmic_index)
{
  pm_scpq_data_type *scpq_ptr = NULL;
  uint8 num_of_peripherals = 0;

  scpq_ptr = pm_scpq_data_arr[pmic_index];
  if(NULL == scpq_ptr)
  {
    num_of_peripherals = pm_target_information_get_periph_count_info(PM_PROP_CHARGER_NUM, pmic_index);
    if(num_of_peripherals == 0)
    {
      return;
    }

    pm_malloc(sizeof(pm_scpq_data_type), (void**)&scpq_ptr);
    CORE_VERIFY(NULL != scpq_ptr);

    /* Assign Comm ptr */
    scpq_ptr->comm_ptr = comm_ptr;

    /* scpq Register Info - Obtaining Data through dal config */
    scpq_ptr->chgr2_register = &scpq_chgr2_reg;
    scpq_ptr->chgr_register  = &scpq_chgr_reg;
    scpq_ptr->dcdc_register  = &scpq_dcdc_reg;
    scpq_ptr->batif_register = &scpq_batif_reg;
    scpq_ptr->usb_register   = &scpq_usb_reg;
    scpq_ptr->wls_register   = &scpq_wls_reg,
    scpq_ptr->typec_register = &scpq_typec_reg;
    scpq_ptr->misc_register  = &scpq_misc_reg;

    scpq_ptr->base_address = peripheral_info->base_address;

    scpq_ptr->num_of_peripherals = num_of_peripherals;

    pm_scpq_data_arr[pmic_index] = scpq_ptr;
  }
}

pm_scpq_data_type* pm_scpq_get_data(uint32 pmic_index)
{
  if(pmic_index < PM_MAX_NUM_PMICS)
  {
    return pm_scpq_data_arr[pmic_index];
  }

  return NULL;
}


void pm_scpq_get_pmic_info(uint32 *pmic_index, uint32 *slave_id, uint32* charger_count, uint32 max_charger)
{
  uint32 i = 0, count = 0;

  if(NULL == pmic_index || NULL == slave_id || NULL == charger_count)
  {
    return;
  }

  for(i = 0; (i < PM_MAX_NUM_PMICS) && (count < max_charger); i++)
  {
    if(pm_scpq_data_arr[i] != NULL)
    {
      pmic_index[count] = pm_scpq_data_arr[i]->comm_ptr->pmic_index;
      slave_id[count]   = pm_scpq_data_arr[i]->comm_ptr->slave_id;
      count++;
    }
  }

  *charger_count = count;
}

