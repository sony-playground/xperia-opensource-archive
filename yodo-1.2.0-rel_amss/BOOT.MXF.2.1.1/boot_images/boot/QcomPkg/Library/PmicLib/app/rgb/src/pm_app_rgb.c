/*! \file
*  
*  \brief  pm_app_rgb_led.c
*  \details Implementation file for rgb led resourece type.
*
*  &copy; Copyright 2013-2020 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This document is created by a code generator, therefore this section will
not contain comments describing changes made to the module.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/app/rgb/src/pm_app_rgb.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
0/15/20    xp      Refine parameter of RGB app APIs
05/01/18   pxm     Fixed rgb_led_state array out of bound issue
02/29/17   sv      Added pm_rgb_get_pmic_index API
05/01/17   aab     Updated pm_rgb_led_config() to use max/min dim level config data
05/17/15   aab     Updated LPG Channel assignment to support 8998 target
03/31/15   aab     Added a call to select PWM source: pm_lpg_pwm_src_select()
06/24/14   aab     Cleaned up and added support for PMI8994
03/13/13   aab     Creation
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "pm_err_flags.h"
#include "CoreVerify.h"
#include "pm_app_rgb.h"
#include "pm_rgb_driver.h"
#include "pm_target_information.h"
#include "pm_pwm.h"

#define RED_INDEX   0
#define GREEN_INDEX 1
#define BLUE_INDEX  2
#define LED_ENABLE  1
#define LED_DISABLE 0

#define LUT_START_INDEX 0
#define LUT_END_INDEX   1
#define LUT_VALUE_DARK  0x00

static uint32 rgb_led_state[3]=
{
  [RED_INDEX]   = LED_DISABLE, 
  [GREEN_INDEX] = LED_DISABLE, 
  [BLUE_INDEX]  = LED_DISABLE
};

static pm_err_flag_type pm_rgb_config_pwm(pm_app_rgb_config_type *rgb_config, pm_rgb_specific_data_type *cfg_ptr);
static pm_err_flag_type pm_rgb_config_lpg(pm_app_rgb_config_type *rgb_config, pm_rgb_specific_data_type *cfg_ptr);
static pm_err_flag_type pm_rgb_led_config_internal(pm_app_rgb_config_type rgb_config);

pm_err_flag_type pm_rgb_led_blink(uint32 rgb_mask, uint32 dim_level)
{
  pm_app_rgb_config_type rgb_config =
                                    {
                                      .rgb_state  = PM_RGB_STATE_BLINK,
                                      .rgb_mask   = rgb_mask,
                                      .dim_level  = dim_level
                                    };
  return pm_rgb_led_config_internal(rgb_config);
}

pm_err_flag_type pm_rgb_led_config(uint32 rgb_mask, uint32 dim_level, boolean enable_rgb) 
{
  pm_rgb_state_type rgb_state = (enable_rgb) ? PM_RGB_STATE_GLOW : PM_RGB_STATE_OFF;
  pm_app_rgb_config_type rgb_config =
                                    {
                                      .rgb_state  = rgb_state,
                                      .rgb_mask   = rgb_mask,
                                      .dim_level  = dim_level
                                    };

  return pm_rgb_led_config_internal(rgb_config);
}

static pm_err_flag_type pm_rgb_led_config_internal(pm_app_rgb_config_type rgb_config)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;;
  static pm_rgb_specific_data_type *cfg_ptr = NULL;
  
  if(NULL == cfg_ptr)
  {
    cfg_ptr = (pm_rgb_specific_data_type *)pm_target_information_get_specific_info(PM_PROP_RGB_SPECIFIC_DATA);
    CORE_VERIFY_PTR(cfg_ptr);
  }

  if(cfg_ptr->is_lpg_supported)
  {
    err_flag = pm_rgb_config_lpg(&rgb_config, cfg_ptr);
  }
  else
  {
    err_flag = pm_rgb_config_pwm(&rgb_config, cfg_ptr);
  }

  return err_flag;
}

static pm_err_flag_type pm_rgb_config_lpg(pm_app_rgb_config_type *rgb_config, pm_rgb_specific_data_type *cfg_ptr)
{
    pm_err_flag_type err_flag    = PM_ERR_FLAG_SUCCESS;
    pm_lpg_chan_type led_channel = PM_LPG_CHAN_1;
    uint8 trig_ret_val = 0;
    uint32 pos_i = 0;
    uint32 led = 0;
    uint32 dim_level = 0;
    uint32 rgb_mask = 0;
    uint32 device_index = 0;
    pm_rgb_state_type rgb_state;
    boolean pattern_repeat = FALSE;

    if (cfg_ptr == NULL || rgb_config == NULL)
    {
        return PM_ERR_FLAG_INVALID_PARAMETER;
    }

    rgb_mask = rgb_config->rgb_mask;
    rgb_state = rgb_config->rgb_state;
    device_index = cfg_ptr->rgb_pmic;
    dim_level = rgb_config->dim_level;

    while (rgb_mask & PM_RGB_SEGMENT_ALL)
    {
        led = (1 << pos_i);

        if (rgb_mask & led)
        {
            led_channel = cfg_ptr->led_lpg_pwm_ch[pos_i];
            switch (rgb_state)
            {
                case PM_RGB_STATE_OFF:
                {
                    rgb_led_state[pos_i] = FALSE;

                    err_flag |= pm_lpg_pwm_enable(device_index, led_channel, FALSE); //Disable LPG

                    err_flag |= pm_rgb_enable(device_index, led, LED_DISABLE);

                    if (TRUE == cfg_ptr->is_rgb_sdam_trig_supported)
                    {
                       if (rgb_led_state[RED_INDEX] == FALSE && rgb_led_state[GREEN_INDEX] == FALSE && rgb_led_state[BLUE_INDEX] == FALSE)
                       {
                           err_flag |= pm_sdam_trig_seq(cfg_ptr->rgb_sdam_pmic, cfg_ptr->rgb_sdam, cfg_ptr->sdam_disable_arg, &trig_ret_val, PM_SDAM_TRIG_FNF);
                       }
                    }
                }
                break;

                case PM_RGB_STATE_BLINK:
                    pattern_repeat = TRUE; //no break statement since rest of the config are same as steady glow
                case PM_RGB_STATE_GLOW:
                {
                   if (TRUE == cfg_ptr->is_rgb_sdam_trig_supported)
                    {
                       err_flag |= pm_sdam_trig_seq(cfg_ptr->rgb_sdam_pmic, cfg_ptr->rgb_sdam, cfg_ptr->sdam_enable_arg, &trig_ret_val, PM_SDAM_TRIG_WAIT);
                    }

                    err_flag |= pm_lpg_pattern_config(device_index, led_channel, cfg_ptr->ramp_direction, pattern_repeat, cfg_ptr->ramp_toggle, cfg_ptr->en_pause_hi, cfg_ptr->en_pause_lo);
                    err_flag |= pm_lpg_pwm_clock_sel(device_index, led_channel, cfg_ptr->clock);
                    err_flag |= pm_lpg_pwm_set_pre_divide(device_index, led_channel, cfg_ptr->pre_div, cfg_ptr->exp);
                    err_flag |= pm_lpg_set_pwm_bit_size(device_index, led_channel, cfg_ptr->bit_size);
                    err_flag |= pm_lpg_config_pwm_type(device_index, led_channel, FALSE);
                    err_flag |= pm_lpg_pwm_set_pwm_value(device_index, led_channel, dim_level);  //Configure DIM level
                    err_flag |= pm_lpg_pwm_lut_index_set(device_index, led_channel, LUT_START_INDEX, LUT_END_INDEX);
                    err_flag |= pm_lpg_config_pause_time(device_index, led_channel, cfg_ptr->ramp_step_duration, cfg_ptr->hi_multiplier, cfg_ptr->low_multiplier);
                    err_flag |= pm_lpg_pwm_src_select(device_index, led_channel, PM_LPG_PWM_SRC_LUT);
                    err_flag |= pm_lpg_lut_config_set(device_index, LUT_START_INDEX, LUT_VALUE_DARK); //make LUT index 0 as 00 for dark
                    err_flag |= pm_lpg_lut_config_set(device_index, LUT_END_INDEX, dim_level);
                    err_flag |= pm_lpg_pwm_ramp_generator_enable(device_index, led_channel, TRUE);
                    err_flag |= pm_lpg_pwm_ramp_generator_start(device_index, led_channel);
                    err_flag |= pm_lpg_pwm_enable(device_index, led_channel, TRUE); //enable LPG
                    err_flag |= pm_rgb_enable(device_index, led, LED_ENABLE);
                    rgb_led_state[pos_i] = TRUE;
                }
                break;

                default:
                    return PM_ERR_FLAG_INVALID_PARAMETER;
            }
        }

        rgb_mask = rgb_mask & (~led);
        pos_i++;
    }

    return err_flag;
}

static pm_err_flag_type pm_rgb_config_pwm(pm_app_rgb_config_type *rgb_config, pm_rgb_specific_data_type *cfg_ptr)
{
    pm_err_flag_type     err_flag    = PM_ERR_FLAG_SUCCESS;
    pm_pwm_resource_type led_channel = PM_PWM_RESOURCE_PWM_1;
    uint8 trig_ret_val = 0;
    uint32 pos_i = 0;
    uint32 led = 0;
    uint32 dim_level = 0;
    uint32 rgb_mask = 0;
    pm_rgb_state_type rgb_state;

    if (cfg_ptr == NULL || rgb_config == NULL)
    {
        return PM_ERR_FLAG_INVALID_PARAMETER;
    }

    rgb_mask = rgb_config->rgb_mask;
    rgb_state = rgb_config->rgb_state;
    dim_level = rgb_config->dim_level;

    while (rgb_mask & PM_RGB_SEGMENT_ALL)
    {
        led = (1 << pos_i);

        if (rgb_mask & led)
        {
            led_channel = cfg_ptr->led_lpg_pwm_ch[pos_i];
            switch (rgb_state)
            {
                case PM_RGB_STATE_OFF:
                {
                    rgb_led_state[pos_i] = FALSE;

                    err_flag |= pm_pwm_enable_pwm(cfg_ptr->rgb_pmic, led_channel, FALSE); //Disable LPG

                    err_flag |= pm_rgb_enable(cfg_ptr->rgb_pmic, led, LED_DISABLE);

                    if (TRUE == cfg_ptr->is_rgb_sdam_trig_supported)
                    {
                       if (rgb_led_state[RED_INDEX] == FALSE && rgb_led_state[GREEN_INDEX] == FALSE && rgb_led_state[BLUE_INDEX] == FALSE)
                       {
                           err_flag |= pm_sdam_trig_seq(cfg_ptr->rgb_sdam_pmic, cfg_ptr->rgb_sdam, cfg_ptr->sdam_disable_arg, &trig_ret_val, PM_SDAM_TRIG_FNF);
                       }
                    }
                }
                break;

                case PM_RGB_STATE_BLINK:
                case PM_RGB_STATE_GLOW:
                {
                   if (TRUE == cfg_ptr->is_rgb_sdam_trig_supported)
                    {
                       err_flag |= pm_sdam_trig_seq(cfg_ptr->rgb_sdam_pmic, cfg_ptr->rgb_sdam, cfg_ptr->sdam_enable_arg, &trig_ret_val, PM_SDAM_TRIG_WAIT);
                    }
                   //config clock, pwm_freq_pre_div, pwm_lsb_msb, enable, pwm_sync		
                   err_flag |= pm_pwm_clock_config( cfg_ptr->rgb_pmic, led_channel, cfg_ptr->bit_size, cfg_ptr->clock, cfg_ptr->pre_div, cfg_ptr->exp);
                   err_flag |= pm_pwm_set_pwm_value(cfg_ptr->rgb_pmic, led_channel, dim_level);
                   err_flag |= pm_pwm_enable_pwm(cfg_ptr->rgb_pmic, led_channel, TRUE);
                   err_flag |= pm_rgb_enable(cfg_ptr->rgb_pmic, led, LED_ENABLE);
                   rgb_led_state[pos_i] = TRUE;
                }
                break;

                default:
                    return PM_ERR_FLAG_INVALID_PARAMETER;
            }
        }

        rgb_mask = rgb_mask & (~led);
        pos_i++;
    }

    return err_flag;
}

