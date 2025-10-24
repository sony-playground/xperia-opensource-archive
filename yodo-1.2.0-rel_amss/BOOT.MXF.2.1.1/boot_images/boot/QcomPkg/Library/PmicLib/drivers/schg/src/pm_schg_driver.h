#ifndef __PM_SCHG_DRIVER_H__
#define __PM_SCHG_DRIVER_H__

/*! \file pm_schg_driver.h
 *  \n
 *  \brief This file contains functions prototypes and variable/type/constant
*          declarations for supporting SMBB peripheral
 *  \n
 *  \n &copy;
 *  Copyright (c) 2017-2022 Qualcomm Technologies, Inc.  All Rights Reserved.
 *  Qualcomm Technologies Proprietary and Confidential.
 */

/*===========================================================================

                        EDIT HISTORY

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when        who    what, where, why
--------    ---    ----------------------------------------------------------
08/01/18    ivy    Added support to set batt therm pull up to register
06/29/18    dc     Expand ICL Status API for Max ICL
06/21/18    cs     Added support for multi-port.
05/17/18    ivy    Added support for Qi charging ICL register
05/14/18    ra     Support for Debug Accessory Mode
03/01/18    ra     Adding skin and die temp registers
02/28/18    pxm    Remove unused APIs and registers.
01/15/18    ra     Adding JEITA registers
10/24/17    ra     update register map for PM855B
09/19/17    cs     updated register map
02/17/17    pxm    Added sysok_reason_status in schg_misc_register_ds struct
02/08/17    ll     Added otg_eng_otg_cfg in schg_otg_register_ds and eng_ssupply_cfg2 in schg_dc_register_ds
02/03/17    sm     Added type_c_cfg_3 in schg_usb_register_ds struct
12/06/16    sm     Added eng_ssupply_cfg3 in schg_dc_register_ds struct
12/19/16    mr     Added API to get SCHG Charger PmicIndex
11/14/16    sm     Added eng_buckboost_cfg1 in schg_misc_register_ds struct
09/07/16    sm     Added pm_schg_get_dig_major API to return digital major
01/13/16    al     Created
========================================================================== */
/*===========================================================================

                     INCLUDE FILES

===========================================================================*/
#include "pm_target_information.h"

/*===========================================================================

                     STRUCTURE TYPE AND ENUM

===========================================================================*/

/************************************************************************/
/* register definitions                                                 */
/************************************************************************/

typedef struct
{
  pm_register_address_type base_address;                        //0x1000
  pm_register_address_type battery_charger_status_1;            //0x06
  pm_register_address_type battery_charger_status_3;            //0x09
  pm_register_address_type charging_enable_cmd;                 //0x42
  pm_register_address_type charger_cfg2;                        //0x51
  pm_register_address_type pre_charge_current_cfg;              //0x60
  pm_register_address_type fast_charge_current_cfg;             //0x61
  pm_register_address_type termination_charge_current_cfg;      //0x62
  pm_register_address_type tccc_charge_current_termination_cfg; //0x63
  pm_register_address_type float_voltage_cfg;                   //0x70
  pm_register_address_type jeita_fvcomp_cold_cfg;               //0x86
  pm_register_address_type jeita_en_cfg;                        //0x90
  pm_register_address_type jeita_fvcomp_hot_cfg;                //0x91
  pm_register_address_type jeita_cccomp_hot_cfg;                //0x92
  pm_register_address_type jeita_cccomp_cold_cfg;               //0x93
  pm_register_address_type jeita_hot_threshold_msb;             //0x94
  pm_register_address_type jeita_hot_threshold_lsb;             //0x95
  pm_register_address_type jeita_cold_threshold_msb;            //0x96
  pm_register_address_type jeita_cold_threshold_lsb;            //0x97
  pm_register_address_type jeita_thot_threshold_msb;            //0x98
  pm_register_address_type jeita_thot_threshold_lsb;            //0x99
  pm_register_address_type jeita_tcold_threshold_msb;           //0x9A
  pm_register_address_type jeita_tcold_threshold_lsb;           //0x9B
  pm_register_address_type jeita_thot_afp_threshold_msb;        //0x9C
  pm_register_address_type jeita_thot_afp_threshold_lsb;        //0x9D
  pm_register_address_type jeita_tcold_afp_threshold_msb;       //0x9E
  pm_register_address_type jeita_tcold_afp_threshold_lsb;       //0x9F
} schg_chgr_register_ds;

typedef struct schg_dcdc_register_ds
{
  pm_register_address_type base_address;           //0x1100
  pm_register_address_type perph_type;             //0x04
  pm_register_address_type perph_subtype;          //0x05
  pm_register_address_type icl_max_status;         //0x06
  pm_register_address_type power_path_status;      //0x0B
  pm_register_address_type lockbit_d1;             //0xD1
  pm_register_address_type lockbit_d2;             //0xD2
  pm_register_address_type otg_status;             //0x0D
  pm_register_address_type int_rt_sts;             //0x10
  pm_register_address_type int_set_type;           //0x11
  pm_register_address_type int_polarity_high;      //0x12
  pm_register_address_type int_polarity_low;       //0x13
  pm_register_address_type int_latched_clr;        //0x14
  pm_register_address_type int_en_set;             //0x15
  pm_register_address_type int_en_clr;             //0x16
  pm_register_address_type int_latched_sts;        //0x18
  pm_register_address_type int_pending_sts;        //0x19
  pm_register_address_type int_mid_sel;            //0x1A
  pm_register_address_type int_priority;           //0x1B
  pm_register_address_type cmd_otg;                //0x40
  pm_register_address_type bat_uvlo_threshold_cfg; //0x51
  pm_register_address_type otg_current_limit_cfg;  //0x52
  pm_register_address_type otg_cfg;                //0x53
  pm_register_address_type vsysmin_cfg;            //0x83
} schg_dcdc_register_ds;

typedef struct
{
  pm_register_address_type base_address;           //0x1200
  pm_register_address_type batt_miss_sts;          //0x06
  pm_register_address_type int_rt_sts;             //0x10
  pm_register_address_type int_set_type;           //0x11
  pm_register_address_type int_polarity_high;      //0x12
  pm_register_address_type int_polarity_low;       //0x13
  pm_register_address_type int_latched_clr;        //0x14
  pm_register_address_type int_en_set;             //0x15
  pm_register_address_type int_en_clr;             //0x16
  pm_register_address_type int_latched_sts;        //0x18
  pm_register_address_type int_pending_sts;        //0x19
  pm_register_address_type ship_mode;              //0x40
  pm_register_address_type low_batt_threshold_cfg; //0x61
  pm_register_address_type bat_miss_src_cfg;       //0x70
  pm_register_address_type fake_batid_ch_en;       //0x91
} schg_batif_register_ds;

typedef struct
{
  pm_register_address_type base_address;            //0x1300
  pm_register_address_type apsd_status;             //0x07
  pm_register_address_type apsd_result_status;      //0x08
  pm_register_address_type int_rt_sts;              //0x10
  pm_register_address_type int_set_type;            //0x11
  pm_register_address_type int_polarity_high;       //0x12
  pm_register_address_type int_polarity_low;        //0x13
  pm_register_address_type int_latched_clr;         //0x14
  pm_register_address_type int_en_set;              //0x15
  pm_register_address_type int_en_clr;              //0x16
  pm_register_address_type int_latched_sts;         //0x18
  pm_register_address_type int_pending_sts;         //0x19
  pm_register_address_type cmd_il;                  //0x40
  pm_register_address_type cmd_apsd;                //0x41
  pm_register_address_type usbin_adapter_allow_cfg; //0x60
  pm_register_address_type usbin_options_1_cfg;     //0x62
  pm_register_address_type usbin_load_cfg;          //0x65
  pm_register_address_type usbin_icl_options;       //0x66
  pm_register_address_type usbin_current_limit_cfg; //0x70
  pm_register_address_type usbin_aicl_options_cfg;  //0x80
} schg_usb_register_ds;

typedef struct
{
  pm_register_address_type base_address;               //0x1500
  pm_register_address_type perph_type;                 //0x04
  pm_register_address_type perph_subtype;              //0x05
  pm_register_address_type lockbit_d1;                 //0xD1
  pm_register_address_type lockbit_d2;                 //0xD2
  pm_register_address_type typec_snk_status;           //0x06
  pm_register_address_type typec_misc_status;          //0x07
  pm_register_address_type typec_mode_cfg;             //0x44
  pm_register_address_type typec_vconn_control;        //0x46
  pm_register_address_type typec_debug_access_snk_cfg; //0x4A
  pm_register_address_type typec_debug_access_status;  //0x07
} schg_typec_register_ds;

typedef struct
{
  pm_register_address_type base_address;           //0x1600
  pm_register_address_type wdog_status;            //0x0C
  pm_register_address_type sysok_reason_status;    //0x0D
  pm_register_address_type int_rt_sts;             //0x10
  pm_register_address_type int_set_type;           //0x11
  pm_register_address_type int_polarity_high;      //0x12
  pm_register_address_type int_polarity_low;       //0x13
  pm_register_address_type int_latched_clr;        //0x14
  pm_register_address_type int_en_set;             //0x15
  pm_register_address_type int_en_clr;             //0x16
  pm_register_address_type int_latched_sts;        //0x18
  pm_register_address_type int_pending_sts;        //0x19
  pm_register_address_type afp_mode;               //0x41
  pm_register_address_type bark_bite_wdog_pet;     //0x43
  pm_register_address_type aicl_cmd;               //0x44
  pm_register_address_type wd_cfg;                 //0x51
  pm_register_address_type snarl_bark_bite_wd_cfg; //0x53
  pm_register_address_type aicl_rerun_time_cfg;    //0x61
  pm_register_address_type thermreg_src_cfg;       //0x70
  pm_register_address_type die_temp_h_msb;         //0xA0
  pm_register_address_type die_temp_h_lsb;         //0xA1
  pm_register_address_type die_temp_l_msb;         //0xA2
  pm_register_address_type die_temp_l_lsb;         //0xA3
} schg_misc_register_ds;

typedef struct
{
  pm_register_address_type base_address;       //0x1900
  pm_register_address_type perph_type;         //0x04
  pm_register_address_type perph_subtype;      //0x05
  pm_register_address_type multi_port_arbiter; //0x06
} schg_bob_register_ds;

typedef struct
{
  schg_chgr_register_ds  *chgr_register;
  schg_dcdc_register_ds  *dcdc_register;
  schg_batif_register_ds *batif_register;
  schg_usb_register_ds   *usb_register;
  schg_typec_register_ds *typec_register;
  schg_misc_register_ds  *misc_register;
  schg_bob_register_ds   *bob_register;
} schg_register_ds;

typedef struct
{
  pm_comm_info_type *comm_ptr;
  schg_register_ds  *schg_register;
  uint32             num_of_peripherals;
} pm_schg_data_type;

/*===========================================================================

                     FUNCTION DECLARATION

===========================================================================*/
void pm_schg_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint32 pmic_index);

pm_schg_data_type *pm_schg_get_data(uint32 pmic_index);

uint8 pm_schg_get_dig_major(void);

void pm_schg_get_pmic_info(uint32 *pmic_index, uint32 *slave_id, uint32 *charger_count, uint32 max_charger);

#endif // __PM_SCHG_DRIVER_H__
