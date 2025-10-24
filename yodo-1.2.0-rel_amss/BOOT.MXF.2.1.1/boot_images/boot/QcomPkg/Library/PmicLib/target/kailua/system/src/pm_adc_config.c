/*! \file pm_adc_config.c
 *  \n
 *  \n &copy; Copyright 2019-2022 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/target/kailua/system/src/pm_adc_config.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when         who     what, where, why
----------   ---     ----------------------------------------------------------
2019-11-15   rh      Initial creation

========================================================================== */

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_adc_config.h"
#include "CoreVerify.h"
#include "pm_utils.h"
#include "pm_dt_parser.h"
#include "pm_chg.h"

/*===========================================================================

                        REGISTER DEFINES 

===========================================================================*/
#define ADC_CMN2_EXT_SNS_RESISTOR_SEL_ADDR       0x305E 

#define ADC_CMN2_EXT_SNS_RESISTOR_SEL_MASK       0x3 

#define ADC_CMN2_EXT_SNS_RESISTOR_SEL_EXT_RES_1MOHM_VAL           0 
#define ADC_CMN2_EXT_SNS_RESISTOR_SEL_EXT_RES_2MOHM_VAL           1 
#define ADC_CMN2_EXT_SNS_RESISTOR_SEL_EXT_RES_3MOHM_VAL           2 

#define ADC_CMN2_TRIM_EXT_SNS_K_RES1_D0_ADDR     0x30F7
#define ADC_CMN2_TRIM_EXT_SNS_K_RES1_D1_ADDR     0x30F8
#define ADC_CMN2_TRIM_EXT_SNS_K_RES2_D0_ADDR     0x30F9
#define ADC_CMN2_TRIM_EXT_SNS_K_RES2_D1_ADDR     0x30FA
#define ADC_CMN2_TRIM_EXT_SNS_K_RES3_D0_ADDR     0x30FB
#define ADC_CMN2_TRIM_EXT_SNS_K_RES3_D1_ADDR     0x30FC

#define QBG_MAIN_CMN_ADC_CTL7_ADDR               0x4f4d 
#define QBG_MAIN_CMN_ADC_CTL7_TBAT_CAL_SEL_FAST_CHAR_BSFT        4 
#define QBG_MAIN_CMN_ADC_CTL7_TBAT_CAL_SEL_FAST_CHAR_SEL_MASK    0x30 
#define QBG_MAIN_CMN_ADC_CTL7_TBAT_CAL_SEL_XPM_BSFT              2 
#define QBG_MAIN_CMN_ADC_CTL7_TBAT_CAL_SEL_XPM_SEL_MASK          0x0C 


/*===========================================================================

                        STATIC VARIABLES 

===========================================================================*/

/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/
pm_err_flag_type pm_ext_rsns_program(uint32 slave_id, int32 r_trim_val)
{
   pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
   uint8 res_config = 0;
   uint8 trim_k_val[2] = {0};
   uint16 reg_addr = 0;
   int32 k_actual = 0;
   int32 k_actual_comp = 0;

   /* Read the Rsens configuration */
   err_flag = pm_comm_read_byte(slave_id, ADC_CMN2_EXT_SNS_RESISTOR_SEL_ADDR, &res_config);
   if(err_flag != PM_ERR_FLAG_SUCCESS)
   {
     return err_flag;
   }

   switch (res_config & ADC_CMN2_EXT_SNS_RESISTOR_SEL_MASK) 
   {
      case ADC_CMN2_EXT_SNS_RESISTOR_SEL_EXT_RES_1MOHM_VAL:
         reg_addr = ADC_CMN2_TRIM_EXT_SNS_K_RES1_D0_ADDR;
         break;
      case ADC_CMN2_EXT_SNS_RESISTOR_SEL_EXT_RES_2MOHM_VAL:
         reg_addr = ADC_CMN2_TRIM_EXT_SNS_K_RES2_D0_ADDR;
         break;
      case ADC_CMN2_EXT_SNS_RESISTOR_SEL_EXT_RES_3MOHM_VAL:
         reg_addr = ADC_CMN2_TRIM_EXT_SNS_K_RES3_D0_ADDR;
         break;
      default:
         return PM_ERR_FLAG_INVALID_PARAMETER;
   }

   /* Do the calculation for the K value                                          */
   /* 1. Calculate K_actual = K_reg - 65536
    * 2. Calculate calibrated K_actual_comp = K_actual * (1 + R_cal_val/100)
    * 3. Calculate new calibrated K_reg_comp = K_actual_comp + 65536
    * 4. Verify 0 < K_reg_comp < 65536, to avoid overflow */
   err_flag = pm_comm_read_byte_array(slave_id, reg_addr, 2, trim_k_val);
   if(err_flag != PM_ERR_FLAG_SUCCESS)
   {
     return err_flag;
   }

   k_actual = trim_k_val[1] << 8 | trim_k_val[0];
   k_actual -= 65536;
   k_actual_comp = k_actual * (100 + r_trim_val) / 100;
   k_actual_comp += 65536;
   trim_k_val[0] = k_actual_comp & 0xff;
   trim_k_val[1] = (k_actual_comp >> 8) & 0xff;

   if (k_actual_comp < 0 || k_actual_comp > 65536) 
   {
      return PM_ERR_FLAG_INVALID_PARAMETER;
   }

   /* Write the resulting value into TRIM registers */
   err_flag = pm_comm_write_byte(slave_id, reg_addr, trim_k_val[0]);
   err_flag |= pm_comm_write_byte(slave_id, reg_addr + 1, trim_k_val[1]);

   return err_flag;
}


pm_err_flag_type pm_ext_rsns_init()
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 chgr_pmic_index = PMIC_INDEX_MAX;

  err_flag = pm_chg_get_primary_charger_pmic_index(&chgr_pmic_index);
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  pm_dt_sw_config* sw_config_dt = pm_dt_get_node(PMIC_DT_NODE_PM_SW_CONFIG);
  if(NULL != sw_config_dt)
  {
    if(sw_config_dt->apply_rsns_trim)
    {
      uint8 flag = 0;
      err_flag = pm_comm_read_byte_mask(EXT_RSNS_TRIM_FLAG_SID, 
        EXT_RSNS_TRIM_FLAG_ADDR, EXT_RSNS_TRIM_FLAG_MASK, &flag);
      if((PM_ERR_FLAG_SUCCESS == err_flag) && (0 == flag))
      {
        err_flag = pm_ext_rsns_program(chgr_pmic_index, sw_config_dt->rsns_trim_value);
        err_flag |= pm_comm_write_byte_mask(EXT_RSNS_TRIM_FLAG_SID,
          EXT_RSNS_TRIM_FLAG_ADDR, EXT_RSNS_TRIM_FLAG_MASK, EXT_RSNS_TRIM_FLAG_MASK);
      }
    }
  }

  return err_flag;
}


pm_err_flag_type pm_qbg_tbat_cal_type_init()
{
  pm_qbg_tbat_cal_specific_data_type *qbg_tbat_cal_data = NULL;
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 tbat_cfg = 0;
  uint32 chgr_pmic_index = PMIC_INDEX_MAX;

  err_flag = pm_chg_get_primary_charger_pmic_index(&chgr_pmic_index);
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  /* Read the Rsens configuration */
  err_flag = pm_comm_read_byte(chgr_pmic_index, QBG_MAIN_CMN_ADC_CTL7_ADDR, &tbat_cfg);
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  qbg_tbat_cal_data = (pm_qbg_tbat_cal_specific_data_type*)pm_target_information_get_specific_info(PM_PROP_QBG_TBAT_CAL_SPECIFIC_DATA);
  CORE_VERIFY_PTR(qbg_tbat_cal_data);

  tbat_cfg = tbat_cfg & ~(QBG_MAIN_CMN_ADC_CTL7_TBAT_CAL_SEL_FAST_CHAR_SEL_MASK |
                          QBG_MAIN_CMN_ADC_CTL7_TBAT_CAL_SEL_XPM_SEL_MASK);
  tbat_cfg = tbat_cfg | qbg_tbat_cal_data->qbg_tbat_cal_fast_char << QBG_MAIN_CMN_ADC_CTL7_TBAT_CAL_SEL_FAST_CHAR_BSFT |
                        qbg_tbat_cal_data->qbg_tbat_cal_xpm << QBG_MAIN_CMN_ADC_CTL7_TBAT_CAL_SEL_XPM_BSFT;

  /* Write the resulting value into TRIM registers */
  err_flag = pm_comm_write_byte(chgr_pmic_index, QBG_MAIN_CMN_ADC_CTL7_ADDR, tbat_cfg);

  return err_flag;
}

