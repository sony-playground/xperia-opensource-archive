/*! \file
 *  
 *  \brief  
 *   pm_config_target.c
 *  \details 
 *   This file contains customizable target specific 
 *   driver settings & PMIC registers. This file is generated from database functional
 *   configuration information that is maintained for each of the targets.
 *  
 *    PMIC code generation Version: 1.0.0.0
 *    PMIC code generation Resource Setting Information Version: VU.Please Provide Valid Label - Not Approved
 *    PMIC code generation Software Register Information Version: VU.Please Provide Valid Label - Not Approved
 *    PMIC code generation Processor Allocation Information Version: VU.Please Provide Valid Label - Not Approved
 *    This file contains code for Target specific settings and modes.
 *  
 *  &copy; Copyright 2010-2022, 2023 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/02/18   pxm     Revise LPG channel for RGB.
07/29/17   sv      Added support for pm_rgb_pmic_index_type config data
05/15/17   aab     Added more config items on sbl_schg_pbs_temp_monitor_config[]
05/01/17   aab     Added support for pm_rgb_specific_data_type config data
04/28/17   aab     Added pm_device_index_type config data
03/14/17   pxm     Enable ICL and set to 1500 mA.
02/13/17    al     Add support to read PBS from REV_ID
01/11/17   pxm     add support for PBS triggered AFP
12/16/16   pxm     Added support for fake battery id range configuration
10/20/16   aab     Added support for Batt_therm Out of bound temperature check
10/13/16   pxm     Updated charger Wdog default configuration
09/17/16   aab     Updated Wipower charger default power level. 
09/17/16   aab     Added WiPower charging wait time as configurable 
08/25/16   pxm     Add skin temperature threshold configuration parameter  
08/12/16   aab     Added debugboard detection support
07/05/16   aab     Cleanup unused data
05/27/16   pxm     Add sbl_schg_wipower_specific_data[1]
04/29/16   aab     Added sbl_pon_specific_data[]
03/24/16   al      Add keypress support
03/29/16   al      Updating for newer target
03/15/16   aab     Driver update (Support for PMI8998)
02/16/16   aab     Creation
===========================================================================*/
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_lpg_driver.h"
#include "pm_vib_driver.h"
#include "pm_resource_manager.h"
#include "pm_pbs_info.h"
#include "pm_pbs_driver.h"
#include "pm_config_target.h"
#include "pm_sbl_boot.h"
#include "pm_pwm.h"
#include "pm_chg.h"
#include "pm_qbg.h"
#include "pm_app_chg.h"
#include "pm_app_pon.h"

#include "rpmh_common.h"
#include "device_info.h"
#include "pm_rgb_driver.h"
#include "pm_app_haptics.h"

#include "pm_adc_config.h"

 /************************************************ DRIVER DATA *********************************/
                         //PMK8350#A, PM7xxx#B, NONE#C,D, PM8150C#E,F, PMR735A#G, NONE#H, PM7250B#I,J, NONE#K,L PM8010#M, PM8010#N /*
uint32 num_of_ldo[]        = { 0,       28,      0,  1,      11,   0,       7,        0,       0,  0,     0,  0,      7,      7 };  
uint32 num_of_smps[]       = { 0,        9,      0,  0,       8,   0,       3,        0,       0,  0,     0,  0,      0,      0 };  
uint32 num_of_gpio[]       = { 4,        9,      0,  8,      12,   0,       4,        0,      12,  0,     0,  0,      2,      2 };  
uint32 num_of_rtc[]        = { 1,        0,      0,  0,       0,   0,       0,        0,       0,  0,     0,  0,      0,      0 }; 
uint32 num_of_bob[]        = { 0,        0,      0,  0,       1,   0,       0,        0,       0,  0,     0,  0,      0,      0 }; 
uint32 num_of_vs[]         = { 0,        0,      0,  0,       0,   0,       0,        0,       0,  0,     0,  0,      0,      0 }; 
uint32 num_of_lpg_chan[]   = { 0,        0,      0,  0,       3,   0,       0,        0,       0,  0,     0,  0,      0,      0 }; 
uint32 num_of_pwron[]      = { 1,        1,      0,  1,       1,   0,       1,        0,       1,  0,     0,  0,      0,      0 };
uint32 num_of_misc[]       = { 1,        1,      0,  1,       1,   0,       1,        0,       1,  0,     0,  0,      1,      1 }; 
uint32 num_of_rgb[]        = { 0,        0,      0,  0,       1,   0,       0,        0,       0,  0,     0,  0,      0,      0 }; 
uint32 num_of_wled[]       = { 0,        0,      0,  1,       1,   0,       0,        0,       0,  0,     0,  0,      0,      0 }; 
uint32 num_of_charger[]    = { 0,        0,      0,  1,       0,   0,       0,        0,       1,  0,     0,  0,      0,      0 }; 
uint32 num_of_bmd[]        = { 0,        0,      0,  1,       0,   0,       0,        0,       1,  0,     0,  0,      0,      0 }; 
uint32 num_of_coincell[]   = { 0,        1,      0,  0,       0,   0,       0,        0,       0,  0,     0,  0,      0,      0 }; 
uint32 num_of_fg[]         = { 0,        0,      0,  1,       0,   0,       0,        0,       0,  0,     0,  0,      0,      0 }; 
uint32 num_of_ibb[]        = { 0,        0,      0,  1,       1,   0,       0,        0,       0,  0,     0,  0,      0,      0 }; 
uint32 num_of_lab[]        = { 0,        0,      0,  0,       0,   0,       0,        0,       0,  0,     0,  0,      0,      0 }; 
uint32 num_of_ab[]         = { 0,        0,      0,  1,       1,   0,       0,        0,       0,  0,     0,  0,      0,      0 }; 
uint32 num_of_oledb[]      = { 0,        0,      0,  1,       1,   0,       0,        0,       0,  0,     0,  0,      0,      0 }; 
uint32 num_of_vib[]        = { 0,        0,      0,  0,       0,   0,       0,        0,       1,  0,     0,  0,      0,      0 }; 
uint32 num_of_pbs_core[]   = { 3,        0,      0,  1,       1,   0,       0,        0,       1,  0,     0,  0,      0,      0 }; 
uint32 num_of_haptics[]    = { 0,        0,      0,  1,       0,   0,       0,        0,       0,  0,     0,  0,      0,      0 }; 
uint32 num_of_lcdb[]       = { 0,        0,      0,  1,       1,   0,       0,        0,       0,  0,     0,  0,      0,      0 }; 
uint32 num_of_pwm[]        = { 0,        1,      0,  0,       2,   0,       0,        0,       0,  0,     0,  0,      0,      0 }; 
uint32 num_of_sdam[]       = {48,        0,      0,  0,       0,   0,       0,        0,       4,  0,     0,  0,      0,      0 };
uint32 num_of_qgauge[]     = { 0,        0,      0,  0,       0,   0,       0,        0,       1,  0,     0,  0,      0,      0 };  

pm_swire_data pm_swire_lut[PM_SWIRE_MAP_NUMBER] =
{
  {PM_ASWIRE_MAP_SEL_0, PM_ESWIRE_MAP_SEL_1}, // MAP_A BOE
  {PM_ASWIRE_MAP_SEL_0, PM_ESWIRE_MAP_SEL_2}, // MAP_B
  {PM_ASWIRE_MAP_SEL_0, PM_ESWIRE_MAP_SEL_3}, // MAP_C Visionox
  {PM_ASWIRE_MAP_SEL_1, PM_ESWIRE_MAP_SEL_4}, // MAP_D
  {PM_ASWIRE_MAP_SEL_2, PM_ESWIRE_MAP_SEL_4}, // MAP_E
  {PM_ASWIRE_MAP_SEL_0, PM_ESWIRE_MAP_SEL_5}, // MAP_F
  {PM_ASWIRE_MAP_SEL_0, PM_ESWIRE_MAP_SEL_6}, // MAP_G
  {PM_ASWIRE_MAP_SEL_0, PM_ESWIRE_MAP_SEL_7}, // MAP_H
  {PM_ASWIRE_MAP_SEL_3, PM_ESWIRE_MAP_SEL_8}, // MAP_I for LGD
};

pm_lpg_specific_info_type lpg_specific[1] =  
{
    {49}
};

pm_vib_specific_data_type
vib_specific[1] = 
{
  {1200, 3100}
};


pm_sbl_pon_specific_data_type
sbl_pon_specific_data[1] = 
{
  {
    .s3_reset_timer_cfg = {
                            .timer_value_ms    = 16000,                           // s3 timer value  (max value: 128000 msec)
                            .reset_source_type = PM_APP_PON_RESET_SOURCE_KPDPWR,  // pm_app_pon_reset_source_type
                            .enable_config = PM_DISABLE_CONFIG                    // PM_DISABLE_CONFIG / PM_ENABLE_CONFIG
                          },
  }
};

pm_sbl_specific_data_type
sbl_specific_data[1] = 
{
  {
    .verbose_uart_logging = FALSE,      // Enable/disable verbose UART logging
    .rfclk2_config_flag   = FALSE,      // FALSE: Default, TRUE: Disable RFCLK2
    .swire_cfg            = {.supported = TRUE, //to be updated later 
                             .swire_map = PM_SWIRE_MAP_C, //NA- AMOLED is going to use 3rd party pmic.
                             .pmic_sid = 3, 
                             .map_reg = 0xF8B4,
                             .oledb_default_volt_cfg= {
                                                       .default_config_supported = FALSE,
                                                       .elvss_default_volt = -4000,
                                                       .elvdd_default_volt = 4600,
                                                       .oledb_default_volt = 6400,
                                                      }
                            },

    .inductor_cfg        = {
                             .supported = TRUE,
                             .cfg_value = 0x02,  // value for inductor config selection
                             .pmic_sid  = 0x0,
                             .reg_addr  = 0x7078, 
                           },                       
  }
};

pm_chg_charger_config_type pm_charger_config =
{
  .pmic_index_charger                 = 8,                                          // PMIC_I, Tioman(PM7250B)
  .dead_battery_threshold             = 3300,                                       // The threshold to boot up to UEFI. Revert to 3000 before mainline
  .ichg_fs_config                     = {.enable_config = PM_DISABLE_CONFIG},       // Support 10A or support 20A
  .battery_config                     = {.enable_config = PM_DISABLE_CONFIG},       // 1S battery, 2S battery with 0/1/2 MID(s)
  .debug_board_id_range               = {.min_in_ohm = 2000, .max_in_ohm = 14000 }, // The battery ID range for debug board
  .afp                                = {.too_hot_afp_threshold = 75, .enable_afp_hot = TRUE,
                                         .too_cold_afp_threshold = -272, .enable_afp_cold = TRUE},
  .no_battery_cfg                     = {.enable_config = PM_ENABLE_CONFIG,         // if bootup without battery then set usb icl to <value>
                                         .boot_without_battery = TRUE,
                                         .icl_value = 1000},
  .float_voltage_mv                   = {.enable_config = PM_DISABLE_CONFIG},       // float voltage threshold
  .pre_charging_current               = {.enable_config = PM_DISABLE_CONFIG},       // pre-charging current limit
  .fast_charging_current              = {.enable_config = PM_DISABLE_CONFIG},       // fast-charging current limit
  .usbin_input_current                = {.enable_config = PM_DISABLE_CONFIG}        // usbin input current limit
};

pm_qbg_ext_rsns_scale_loc_type pm_ext_rsns_scale_location =
{
  .pmic_index = PMIC_A,
  .sdam_index = PM_SDAM_23,
  .mem_index = 127
};

//Remove this config if PSI doesn't read the flag to configure slave charger related.
pm_chg_slave_charger_config_type pm_slave_charger_config = 
{
  .slave_charger_present = TRUE,
  .sdam_pmic = PMIC_A,
  .sdam_flag_addr = 0x7072 // Tokei SDAM01_MEM_050
};

pm_haptics_app_config pm_haptics_config =
{
  .haptics_pmic = PMIC_I,               // pmic index of haptics peripheral
  .is_external_boost_vdd = FALSE,        // is haptics vdd connected to VPH_PWR or external boost
  .haptics_gpio_pmic = PMIC_B,          // pmic index of GPIO which is used to enable external boost
  .gpio = PM_GPIO_5                     // GPIO number for external boost enable pin
};

pm_rgb_specific_data_type
rgb_specific_data =
{
  .clock                      = PM_LPG_PWM_19_2_MHZ,
  .pre_div                    = PM_LPG_PWM_PRE_DIV_6,
  .exp                        = PM_LPG_PWM_FREQ_EXPO_1,
  .bit_size                   = PM_PWM_SIZE__9BIT,
  .ramp_step_duration         = 255,
  .hi_multiplier              = 2,
  .low_multiplier             = 1,
  .rgb_sdam_pmic              = PMIC_A,
  .rgb_sdam                   = PM_SDAM_21,
  .sdam_enable_arg            = 1,
  .sdam_disable_arg           = 2,
  .is_rgb_sdam_trig_supported = FALSE,
  .is_lpg_supported           = TRUE, //PWM is supported
  .ramp_direction             = TRUE,
  .ramp_toggle                = FALSE,
  .en_pause_hi                = TRUE,
  .en_pause_lo                = TRUE,
  .rgb_dim_level_max          = 0x1FF,
  .led_lpg_pwm_ch             = {PM_LPG_CHAN_3, PM_LPG_CHAN_2, PM_LPG_CHAN_1}, //BLUE, GREEN, RED,
  .rgb_pmic                   = PMIC_E, //makuaC
};

/* Tokei */
pm_pbs_info_data_type pm_pbs_info_data_a =
{
  .pbs_otp_start_addr    = 0x0,                /* PBS OTP MEMORY Start Address */
  .pbs_otp_mem_size      = 512,                /* PBS OTP MEMORY Size */
  .pbs_ram_start_addr    = 0x1000,              /* PBS RAM MEMORY Start Address */
  .pbs_ram_mem_size      = 0x2000,               /* PBS RAM MEMORY Size */
  .skip_verify_supported = TRUE,               /* Skip Ram Image Word Range Supported */
  .skip_verify_start     = 0x5,                /* Skip Ram Image Word Range Start Word */
  .skip_verify_end       = 0x8,                /* Skip Ram Image Word Range End Word */
  .pbs_info_place_holder = PM_PBS_INFO_IN_PERIPH, /* Place where PBS Info stored */
  .perph_base_addr       = 0x1600,               /* Periph BASE_ADDRESS */
  .trim_num              = 0x00,               /* trim_num  */
  .tp_rev                = 0x00,               /* tp_rev    */
  .fab_id                = 0x00,               /* fab_id    */
  .wafer_id              = 0x00,               /* wafer_id  */
  .x_co_ordi             = 0x00,               /* x_co_ordi */
  .y_co_ordi             = 0x00,               /* y_co_ordi */
  .lot_id                = 0x00,               /* lot_id_01_00 */
  .mfg_id                = 0x00,               /* mfg_id    */
};

/*bompoka*/
pm_pbs_info_data_type pm_pbs_info_data_b =
{
  .pbs_otp_start_addr    = 0x0,                /* PBS OTP MEMORY Start Address */
  .pbs_otp_mem_size      = 512,                /* PBS OTP MEMORY Size */
  .pbs_ram_start_addr    = 0x800,              /* PBS RAM MEMORY Start Address */
  .pbs_ram_mem_size      = 512,                /* PBS RAM MEMORY Size */
  .skip_verify_supported = FALSE,              /* Skip Ram Image Word Range Supported */
  .skip_verify_start     = 0x5,                /* Skip Ram Image Word Range Start Word */
  .skip_verify_end       = 0x8,                /* Skip Ram Image Word Range End Word */
  .pbs_info_place_holder = PM_PBS_INFO_IN_PERIPH, /* Place where PBS Info stored */
  .perph_base_addr       = 0x1600,             /* REV_ID Periph BASE_ADDRESS */
  .trim_num              = 0xF0,               /* trim_num  */
  .tp_rev                = 0xF1,               /* tp_rev    */
  .fab_id                = 0xF2,               /* fab_id    */
  .wafer_id              = 0xF3,               /* wafer_id  */
  .x_co_ordi             = 0xF4,               /* x_co_ordi */
  .y_co_ordi             = 0xF5,               /* y_co_ordi */
  .lot_id                = 0xF6,               /* lot_id_11_10 */
  .mfg_id                = 0xFF,               /* mfg_id    */
};

//NO PMIC Installed 
pm_pbs_info_data_type pm_pbs_info_data_c =
{
};

//NO PMIC Installed 
pm_pbs_info_data_type pm_pbs_info_data_d =
{
  .pbs_otp_start_addr    = 0x0,                /* PBS OTP MEMORY Start Address */
  .pbs_otp_mem_size      = 512,                /* PBS OTP MEMORY Size */
  .pbs_ram_start_addr    = 0x800,              /* PBS RAM MEMORY Start Address */
  .pbs_ram_mem_size      = 256,                /* PBS RAM MEMORY Size */
  .skip_verify_supported = FALSE,              /* Skip Ram Image Word Range Supported */
  .skip_verify_start     = 0x5,                /* Skip Ram Image Word Range Start Word */
  .skip_verify_end       = 0x8,                /* Skip Ram Image Word Range End Word */
  .pbs_info_place_holder = PM_PBS_INFO_IN_PERIPH, /* Place where PBS Info stored */
  .perph_base_addr       = 0x1600,               /* Periph BASE_ADDRESS */
  .trim_num              = 0x00,               /* trim_num  */
  .tp_rev                = 0x00,               /* tp_rev    */
  .fab_id                = 0x00,               /* fab_id    */
  .wafer_id              = 0x00,               /* wafer_id  */
  .x_co_ordi             = 0x00,               /* x_co_ordi */
  .y_co_ordi             = 0x00,               /* y_co_ordi */
  .lot_id                = 0x00,               /* lot_id_01_00 */
  .mfg_id                = 0x00,               /* mfg_id    */
};

/*MakuaC*/
pm_pbs_info_data_type pm_pbs_info_data_e =
{
  .pbs_otp_start_addr    = 0x0,                /* PBS OTP MEMORY Start Address */
  .pbs_otp_mem_size      = 512,                /* PBS OTP MEMORY Size */
  .pbs_ram_start_addr    = 0x800,              /* PBS RAM MEMORY Start Address */
  .pbs_ram_mem_size      = 512,                /* PBS RAM MEMORY Size */
  .skip_verify_supported = FALSE,              /* Skip Ram Image Word Range Supported */
  .skip_verify_start     = 0x5,                /* Skip Ram Image Word Range Start Word */
  .skip_verify_end       = 0x8,                /* Skip Ram Image Word Range End Word */
  .pbs_info_place_holder = PM_PBS_INFO_IN_PERIPH, /* Place where PBS Info stored */
  .perph_base_addr       = 0x7000,               /* Periph BASE_ADDRESS */
  .trim_num              = 0x00,               /* trim_num  */
  .tp_rev                = 0x00,               /* tp_rev    */
  .fab_id                = 0x00,               /* fab_id    */
  .wafer_id              = 0x00,               /* wafer_id  */
  .x_co_ordi             = 0x00,               /* x_co_ordi */
  .y_co_ordi             = 0x00,               /* y_co_ordi */
  .lot_id                = 0x00,               /* lot_id_01_00 */
  .mfg_id                = 0x00,               /* mfg_id    */
};

//NO PMIC Installed 
pm_pbs_info_data_type pm_pbs_info_data_f =
{
};

/*Seco*/
pm_pbs_info_data_type pm_pbs_info_data_g =
{
  .pbs_otp_start_addr    = 0x0,                /* PBS OTP MEMORY Start Address */
  .pbs_otp_mem_size      = 512,                /* PBS OTP MEMORY Size */
  .pbs_ram_start_addr    = 0x800,              /* PBS RAM MEMORY Start Address */
  .pbs_ram_mem_size      = 256,                /* PBS RAM MEMORY Size */
  .skip_verify_supported = FALSE,              /* Skip Ram Image Word Range Supported */
  .skip_verify_start     = 0x5,                /* Skip Ram Image Word Range Start Word */
  .skip_verify_end       = 0x8,                /* Skip Ram Image Word Range End Word */
  .pbs_info_place_holder = PM_PBS_INFO_IN_PERIPH, /* Place where PBS Info stored */
  .perph_base_addr       = 0x1600,               /* Periph BASE_ADDRESS */
  .trim_num              = 0x00,               /* trim_num  */
  .tp_rev                = 0x00,               /* tp_rev    */
  .fab_id                = 0x00,               /* fab_id    */
  .wafer_id              = 0x00,               /* wafer_id  */
  .x_co_ordi             = 0x00,               /* x_co_ordi */
  .y_co_ordi             = 0x00,               /* y_co_ordi */
  .lot_id                = 0x00,               /* lot_id_01_00 */
  .mfg_id                = 0x00,               /* mfg_id    */
};

pm_pbs_info_data_type pm_pbs_info_data_h =
{
};

//Tioman
pm_pbs_info_data_type pm_pbs_info_data_i =
{
  .pbs_otp_start_addr    = 0x0,                   /* PBS OTP MEMORY Start Address */
  .pbs_otp_mem_size      = 512,                   /* PBS OTP MEMORY Size */
  .pbs_ram_start_addr    = 0x800,                 /* PBS RAM MEMORY Start Address */
  .pbs_ram_mem_size	     = 512,				 /* PBS RAM MEMORY Size */
  .skip_verify_supported = FALSE,              /* Skip Ram Image Word Range Supported */
  .skip_verify_start	 = 0x0,				 /* Skip Ram Image Word Range Start Word */
  .skip_verify_end	     = 0x0,				 /* Skip Ram Image Word Range End Word */
  .pbs_info_place_holder = PM_PBS_INFO_IN_OTP,    /* Place where PBS Info stored */
  .perph_base_addr	     = 0x7000,				 /* Periph BASE_ADDRESS */
  .trim_num			     = 0x00,				 /* trim_num  */
  .tp_rev 			     = 0x00,				 /* tp_rev	  */
  .fab_id 			     = 0x00,				 /* fab_id	  */
  .wafer_id			     = 0x00,				 /* wafer_id  */
  .x_co_ordi			 = 0x00,				 /* x_co_ordi */
  .y_co_ordi			 = 0x00,				 /* y_co_ordi */
  .lot_id 			     = 0x00,				 /* lot_id_01_00 */
  .mfg_id 			     = 0x00,				 /* mfg_id	  */
};

pm_pbs_info_data_type pm_pbs_info_data_j =
{
};

pm_pbs_info_data_type *pm_pbs_info_data[] = {&pm_pbs_info_data_a , &pm_pbs_info_data_b, &pm_pbs_info_data_c, &pm_pbs_info_data_d, &pm_pbs_info_data_e, &pm_pbs_info_data_f, &pm_pbs_info_data_g, &pm_pbs_info_data_h, &pm_pbs_info_data_i, &pm_pbs_info_data_j};


/* max_num_seqs, ram_start_addr, poff_trig_id, poff_otp_addr, warmreset_trig_id, warmreset_otp_addr */
pm_pbs_custom_seq_data_type pbs_custom_seq_data_a = {2, 0x07DC, 3, 0x000C, 2, 0x0008};

/* max_num_seqs, ram_start_addr, poff_trig_id, poff_otp_addr, warmreset_trig_id, warmreset_otp_addr */
pm_pbs_custom_seq_data_type pbs_custom_seq_data_b = {33, 0x0554, 2, 0x0008, 7, 0x001C};

pm_pbs_custom_seq_data_type* pbs_custom_seq_data[] = 
{
   NULL,
   NULL,
   NULL,
   NULL,
};


const uint8 pm_periph_bitmap[][PM_MAX_BITMAP_ENTRIES] =
{
  /* pmk8350 */
  {
      0xf2, 0xcb, 0xef, 0xff, 
      0xff, 0x3b, 0xfe, 0x03, 
      0x00, 0x00, 0xf3, 0x4f, 
      0x1f, 0x3f, 0xff, 0xff, 
      0xff, 0xff, 0xff, 0xff, 
      0x00, 0x00, 0x0f, 0x00, 
      0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x40, 
  },
  /* pm7xxx_Bompoka */
  {
      0x72, 0xef, 0x30, 0x70, 
      0x00, 0x00, 0x40, 0x02, 
      0x01, 0x00, 0x02, 0x40, 
      0x00, 0x00, 0x00, 0x00, 
      0x00, 0xff, 0x01, 0xfe, 
      0xff, 0xff, 0x3f, 0x00, 
      0xfe, 0xff, 0xff, 0x1f, 
      0x06, 0x01, 0x00, 0xc0, 
  },

  {
  },

  /* pm8350b */
  {
      0x72, 0xcf, 0xd9, 0xf3,
      0xc0, 0x7f, 0x41, 0x36,
      0x80, 0xc1, 0x02, 0xc0,
      0x00, 0x00, 0x00, 0x00,
      0x00, 0xff, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00,
      0x02, 0x00, 0x00, 0x80,
      0x00, 0x00, 0x07, 0x7F,
  },
  /* E - pm8150c_MakuaC */
   {
      0x72, 0x03, 0x00, 0x00,
      0x10, 0x10, 0xe6, 0xf2,
      0x00, 0x00, 0x00, 0x0a,
      0xc0, 0x00, 0x3f, 0x00,
      0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00,
      0xff, 0x0f, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00,
  },
  {
      0x02, 0x00, 0xf1, 0xff,
      0xff, 0x0f, 0x00, 0x00,
      0xff, 0x07, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00,
      0x03, 0x00, 0x0f, 0x30,
      0x00, 0x00, 0x09, 0x03,
      0x00, 0x10, 0x00, 0x00,
  },
 /* G- pmr735a - Seco */
  {
      0x72, 0xcf, 0x00, 0x30, 
      0x00, 0x00, 0x40, 0x02, 
      0x00, 0x00, 0x02, 0x40, 
      0x00, 0x00, 0x00, 0x00, 
      0x00, 0x0f, 0x00, 0x6e, 
      0x0f, 0x00, 0x00, 0x00, 
      0xfe, 0x00, 0x00, 0x00, 
      0x02, 0x00, 0x00, 0xc0, 
  },
//H
  {
  },
  {//I - Tioman
   0x72, 0x03, 0xff, 0x67, 
   0x10, 0x10, 0xe7, 0x12, 
   0x00, 0x01, 0x00, 0x0a, 
   0x40, 0x00, 0x3f, 0x00, 
   0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x0f, 0x00, 
   0xff, 0x0f, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 
  },
  {
   0x02, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x08, 0x00, 
   0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 
  },
  {},
  {},
  /* M_pm8010_1 */
  {
      0xf2, 0x02, 0x00, 0x00, 
      0x10, 0x10, 0x00, 0x00, 
      0x7f, 0x00, 0x02, 0x00, 
      0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 
      0x03, 0x00, 0x00, 0x00, 
      0x02, 0x00, 0x00, 0x00, 
      
  },
  /* N_pm8010_2 */
  {
      0xf2, 0x02, 0x00, 0x00, 
      0x10, 0x10, 0x00, 0x00, 
      0x7f, 0x00, 0x02, 0x00, 
      0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 
      0x03, 0x00, 0x00, 0x00, 
      0x02, 0x00, 0x00, 0x00, 
      
  },
  
};

/*key press in milli seconds for valid boot*/
pm_pwrkey_dbnc_chk_type pm_pon_pwrkey_dbnc_chk[] =
{
   {
      .chk_at = PM_PON_PWRKEY_DBNC_CHK_AT_CORE,  // check key press at
      .dbnc_time_msec = 400,                     // valid debounce time msec
      .sdam_dbnc_supported = TRUE,               // SDAM support for reading dbnc time
      .pmic_index = 0,                           // primary pmic index
      .min_pmic_rev = 2,                         // minimum revision of pmic supporting SDAM RTC VAL
      .sdam_periph_index = PM_SDAM_2,            // SDAM peripheral
      .sdam_key_press_offset = 26,               // MEM_026
      .sdam_key_release_offset = 30,             // MEM_030
   }
};


uint32 rpmh_drv_id [] = {(uint32)RSC_DRV_HLOS};

pm_qbg_tbat_cal_specific_data_type pm_qbg_tbat_cal_val = 
{
   .qbg_tbat_cal_fast_char = PM_ADC_CAL_ABX_CAL,
   .qbg_tbat_cal_xpm = PM_ADC_CAL_RATIO_CAL,
};

const pm_register_address_type
pm_tgt_sdam_base_address[] =
{
  [PMIC_A] = 0x7000,
  [PMIC_B] = 0x0,
  [PMIC_C] = 0x0,
  [PMIC_D] = 0x0,
  [PMIC_E] = 0x0,
  [PMIC_F] = 0x0,
  [PMIC_G] = 0x0,
  [PMIC_H] = 0x0,
  [PMIC_I] = 0xB000,
  [PMIC_J] = 0x0,
  [PMIC_K] = 0x0,
  [PMIC_L] = 0x0,
  [PMIC_M] = 0x0,
  [PMIC_N] = 0x0,
  [PMIC_O] = 0x0,
};

