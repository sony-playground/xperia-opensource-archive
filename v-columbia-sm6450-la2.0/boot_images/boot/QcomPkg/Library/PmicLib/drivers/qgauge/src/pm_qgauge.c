/*! \file
*
*  \brief  pm_qgauge.c driver implementation.
*  \details qguage driver implementation.
*  &copy;
*  Copyright (c) 2018-2023 Qualcomm Technologies, Inc.  All Rights Reserved.
*  Qualcomm Technologies Proprietary and Confidential.
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE


$Header: //components/rel/core.boot/6.0/QcomPkg/Library/PmicLib/drivers/qgauge/src/pm_qgauge.c#4 $
$Author: pwbldsvc $
$DateTime: 2023/01/17 22:05:47 $
when        who    what, where, why
--------    ---    ----------------------------------------------------------
02/21/18    sv     Initial revision
========================================================================== */

/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include "pm_chg.h"
#include "pm_qgauge.h"
#include "pm_qgauge_driver.h"

/*===========================================================================
                        MACRO DECLARATIONS
===========================================================================*/
    
#define QGAUGE_VBAT_NUMR  194637   //LSB value 194.637uV
#define QGAUGE_VBATT_DENR    1000

#define QGAUGE_IBAT_NUMR_PMI632  152593 //LSB value is 152.593uA
#define QGAUGE_IBAT_NUMR  305185
#define QGAUGE_IBATT_DENR    1000

#define QGAUGE_BAT_THRESHOLD_NUMR 49920
#define QGAUGE_BAT_THRESHOLD_DENR 1000

#define ADDRESS(x) (qgauge_ptr->qgauge_register->base_address + qgauge_ptr->qgauge_register->x)
#define SLAVE_ID   (qgauge_ptr->comm_ptr->slave_id)

/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/



pm_err_flag_type pm_qgauge_irq_enable(uint32 device_index, pm_qgauge_irq_type irq, boolean enable)
{
    pm_err_flag_type    err_flag    = PM_ERR_FLAG_SUCCESS;
    pm_register_address_type irq_reg;
    pm_register_data_type data = 1 << irq;

    pm_qgauge_data_type *qgauge_ptr  = pm_qgauge_get_data(device_index);

    if(NULL == qgauge_ptr)
    {
        err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
    else if(irq >= PM_QGAUGE_IRQ_INVALID)
    {
        err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
    }
    else
    {
        if(enable)
        {
            irq_reg = qgauge_ptr->qgauge_register->base_address + qgauge_ptr->qgauge_register->int_en_set;
        }
        else
        {
            irq_reg = qgauge_ptr->qgauge_register->base_address + qgauge_ptr->qgauge_register->int_en_clr;
        }

        err_flag = pm_comm_write_byte(qgauge_ptr->comm_ptr->slave_id, irq_reg, data);
    }
    return err_flag;
}

pm_err_flag_type pm_qgauge_irq_clear(uint32  device_index, pm_qgauge_irq_type irq)
{
    pm_err_flag_type    err_flag    = PM_ERR_FLAG_SUCCESS;
    pm_register_data_type data = 1 << irq;
    pm_register_address_type int_latched_clr;
    pm_qgauge_data_type *qgauge_ptr  = pm_qgauge_get_data(device_index);

    if(NULL == qgauge_ptr)
    {
        err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
    else if(irq >= PM_QGAUGE_IRQ_INVALID)
    {
        err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
    else
    {
        int_latched_clr = qgauge_ptr->qgauge_register->base_address + qgauge_ptr->qgauge_register->int_latched_clr;
        err_flag = pm_comm_write_byte(qgauge_ptr->comm_ptr->slave_id, int_latched_clr, data);
    }

    return err_flag;
}


pm_err_flag_type pm_qgauge_irq_set_trigger(uint32 device_index, pm_qgauge_irq_type irq, pm_irq_trigger_type trigger)
{
    pm_err_flag_type    err_flag    = PM_ERR_FLAG_SUCCESS;
    uint8 mask = 1 << irq;
    pm_register_data_type set_type, polarity_high, polarity_low;
    pm_register_address_type int_set_type, int_polarity_high, int_polarity_low;

    pm_qgauge_data_type *qgauge_ptr  = pm_qgauge_get_data(device_index);

    if(NULL == qgauge_ptr)
    {
        err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
    else if(irq >= PM_QGAUGE_IRQ_INVALID)
    {
        err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
    else
    {
        int_set_type = qgauge_ptr->qgauge_register->base_address + qgauge_ptr->qgauge_register->int_set_type;
        int_polarity_high = qgauge_ptr->qgauge_register->base_address + qgauge_ptr->qgauge_register->int_polarity_high;
        int_polarity_low = qgauge_ptr->qgauge_register->base_address + qgauge_ptr->qgauge_register->int_polarity_low;

        switch (trigger)
        {
        case PM_IRQ_TRIGGER_ACTIVE_LOW:
            set_type = 0x00;
            polarity_high = 0x00;
            polarity_low = 0xFF;
            break;
        case PM_IRQ_TRIGGER_ACTIVE_HIGH:
            set_type = 0x00;
            polarity_high = 0xFF;
            polarity_low = 0x00;
            break;
        case PM_IRQ_TRIGGER_RISING_EDGE:
            set_type = 0xFF;
            polarity_high = 0xFF;
            polarity_low = 0x00;
            break;
        case PM_IRQ_TRIGGER_FALLING_EDGE:
            set_type = 0xFF;
            polarity_high = 0x00;
            polarity_low = 0xFF;
            break;
        case PM_IRQ_TRIGGER_DUAL_EDGE:
            set_type = 0xFF;
            polarity_high = 0xFF;
            polarity_low = 0xFF;
            break;
        default:
            return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
        }
        err_flag = pm_comm_write_byte_mask(qgauge_ptr->comm_ptr->slave_id, int_set_type, mask, set_type);
        err_flag |= pm_comm_write_byte_mask(qgauge_ptr->comm_ptr->slave_id, int_polarity_high, mask, polarity_high);
        err_flag |= pm_comm_write_byte_mask(qgauge_ptr->comm_ptr->slave_id, int_polarity_low, mask, polarity_low);
    }

    return err_flag;
}


pm_err_flag_type pm_qgauge_irq_status(uint32 device_index, pm_qgauge_irq_type irq, pm_irq_status_type type, boolean *status)
{
    pm_err_flag_type    err_flag    = PM_ERR_FLAG_SUCCESS;
    pm_register_data_type data;
    uint8 mask = 1 << irq;
    pm_register_address_type int_sts;
    pm_qgauge_data_type *qgauge_ptr  = pm_qgauge_get_data(device_index);

    if(NULL == qgauge_ptr)
    {
        err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
    else if(irq >= PM_QGAUGE_IRQ_INVALID)
    {
        err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
    }
    else
    {
        switch (type)
        {
        case PM_IRQ_STATUS_RT:
            int_sts = qgauge_ptr->qgauge_register->base_address + qgauge_ptr->qgauge_register->int_rt_sts;
            break;
        case PM_IRQ_STATUS_LATCHED:
            int_sts = qgauge_ptr->qgauge_register->base_address + qgauge_ptr->qgauge_register->int_latched_sts;
            break;
        case PM_IRQ_STATUS_PENDING:
            int_sts = qgauge_ptr->qgauge_register->base_address + qgauge_ptr->qgauge_register->int_pending_sts;
            break;
        default:
            return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
        }

        err_flag = pm_comm_read_byte_mask(qgauge_ptr->comm_ptr->slave_id, int_sts, mask, &data);
        *status = data ? TRUE : FALSE;
    }
    return err_flag;
}



pm_err_flag_type pm_qgauge_get_status(uint32 device_index, pm_qgauge_status_type* qgauge_status)
{
   pm_err_flag_type  err_flag  = PM_ERR_FLAG_SUCCESS;
   pm_register_data_type data;
   pm_register_address_type reg; 

   pm_qgauge_data_type *qgauge_ptr  = pm_qgauge_get_data(device_index);

   if(NULL == qgauge_ptr)
   {
      err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
   }
   else if(NULL == qgauge_status)
   {
      err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
   }
   else
   {
     reg = qgauge_ptr->qgauge_register->base_address + qgauge_ptr->qgauge_register->status1;
     err_flag = pm_comm_read_byte(qgauge_ptr->comm_ptr->slave_id, reg, &data);
     qgauge_status->qg_ok                   = (data & 0x80)? TRUE : FALSE;
     qgauge_status->s5_ocv_validate_done    = (data & 0x40)? TRUE : FALSE;
     qgauge_status->pre_esr_meas_done       = (data & 0x20)? TRUE : FALSE;
     qgauge_status->esr_meas_done           = (data & 0x10)? TRUE : FALSE;
     qgauge_status->fsm_forced              = (data & 0x08)? TRUE : FALSE;
     qgauge_status->batfet_open             = (data & 0x02)? TRUE : FALSE;
     qgauge_status->battery_present         = (data & 0x01)? TRUE : FALSE;

     reg = qgauge_ptr->qgauge_register->base_address + qgauge_ptr->qgauge_register->status2;
     err_flag |= pm_comm_read_byte(qgauge_ptr->comm_ptr->slave_id, reg, &data);
     qgauge_status->adc_conv_fault_occured  = (data & 0x04)? TRUE : FALSE;
     qgauge_status->good_ocv                = (data & 0x02)? TRUE : FALSE;
     qgauge_status->forced_disable          = (data & 0x01)? TRUE : FALSE;

   }
   
   return err_flag ;
};


pm_err_flag_type pm_qgauge_get_vbat(uint32 device_index, uint32* vbat_inmv)
{
   pm_err_flag_type  err_flag  = PM_ERR_FLAG_SUCCESS;
   pm_register_data_type adc_vbat_lsb;
   pm_register_data_type adc_vbat_msb=0;
   pm_register_address_type reg; 
   uint32 temp =0;

   pm_qgauge_data_type *qgauge_ptr  = pm_qgauge_get_data(device_index);

   if(NULL == qgauge_ptr)
   {
      err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
   }
   else if(NULL == vbat_inmv)
   {
      err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
   }
   else
   {
     reg = qgauge_ptr->qgauge_register->base_address + qgauge_ptr->qgauge_register->last_adc_v_data0;
     err_flag = pm_comm_read_byte(qgauge_ptr->comm_ptr->slave_id, reg, &adc_vbat_lsb);

     reg = qgauge_ptr->qgauge_register->base_address + qgauge_ptr->qgauge_register->last_adc_v_data1;
     err_flag |= pm_comm_read_byte(qgauge_ptr->comm_ptr->slave_id, reg, &adc_vbat_msb);
     
     temp = (uint32)(adc_vbat_msb << 8);
     temp = temp | adc_vbat_lsb;
     /* {MSB,LSB} to decode the voltage level, refer register description. */
     temp = (((uint64)temp)*QGAUGE_VBAT_NUMR/QGAUGE_IBATT_DENR);
     *vbat_inmv = temp/1000;
   }
   
   return err_flag ;
};


pm_err_flag_type pm_qgauge_get_ibat(uint32 device_index, int32* ibat_inma)
{
   pm_err_flag_type  err_flag  = PM_ERR_FLAG_SUCCESS;
   pm_register_data_type adc_ibat_lsb;
   pm_register_data_type adc_ibat_msb;
   pm_register_address_type reg; 
   int32 temp =0;
   uint32 pmi_index = 0x0;

   pm_qgauge_data_type *qgauge_ptr  = pm_qgauge_get_data(device_index);

   if(NULL == qgauge_ptr)
   {
      err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
   }
   else if(NULL == ibat_inma)
   {
      err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
   }
   else
   {
     reg = qgauge_ptr->qgauge_register->base_address + qgauge_ptr->qgauge_register->last_adc_i_data0;
     err_flag = pm_comm_read_byte(qgauge_ptr->comm_ptr->slave_id, reg, &adc_ibat_lsb);

     reg = qgauge_ptr->qgauge_register->base_address + qgauge_ptr->qgauge_register->last_adc_i_data1;
     err_flag |= pm_comm_read_byte(qgauge_ptr->comm_ptr->slave_id, reg, &adc_ibat_msb);
     
     temp = (((int32)(adc_ibat_msb << 8)) | adc_ibat_lsb);
     
     if(temp & 0x8000) //if it is a negative number apply 2's compliment.
     {
         temp = (~temp)&(0x7FFF);
         temp = temp+1;
         temp = (-1)* temp;
     }
     
     /* {MSB,LSB} to decode the voltage level, refer register description. */
	 err_flag |= pm_chg_get_primary_charger_pmic_index(&pmi_index);
	 if(pm_get_pmic_model(pmi_index) == PMIC_IS_PMI632)
	 {
       *ibat_inma = (((int64)temp)*QGAUGE_IBAT_NUMR_PMI632/QGAUGE_IBATT_DENR);  //in uA
       *ibat_inma /= 1000;
	 }
	 else
	 {
       *ibat_inma = (((int64)temp)*QGAUGE_IBAT_NUMR/QGAUGE_IBATT_DENR);  //in uA
       *ibat_inma /= 1000;
	 } 
   }
   
   return err_flag ;
};


pm_err_flag_type pm_qgauge_set_vbat_empty_threshold(uint32 device_index, uint32 vbatEmptyThreshold)
{
   pm_err_flag_type  err_flag  = PM_ERR_FLAG_SUCCESS;
   pm_register_data_type vbatthreshold =0;
   pm_register_address_type reg; 
   

   pm_qgauge_data_type *qgauge_ptr  = pm_qgauge_get_data(device_index);

   if(NULL == qgauge_ptr)
   {
      err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
   }
   else
   {
     reg = qgauge_ptr->qgauge_register->base_address + qgauge_ptr->qgauge_register->vbat_empty_threshold;
     
     //need to get the right formula     
     vbatthreshold = ((int64)vbatEmptyThreshold * QGAUGE_BAT_THRESHOLD_DENR)/QGAUGE_BAT_THRESHOLD_NUMR;

     err_flag = pm_comm_write_byte(qgauge_ptr->comm_ptr->slave_id, reg, vbatthreshold);
   }
   
   return err_flag ;
};

pm_err_flag_type pm_qgauge_set_vbat_low_threshold(uint32 device_index, uint32 vbatlowThreshold)
{
   pm_err_flag_type  err_flag  = PM_ERR_FLAG_SUCCESS;
   pm_register_data_type vbatthreshold =0;
   pm_register_address_type reg; 

   pm_qgauge_data_type *qgauge_ptr  = pm_qgauge_get_data(device_index);

   if(NULL == qgauge_ptr)
   {
      err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
   }
   else
   {
     reg = qgauge_ptr->qgauge_register->base_address + qgauge_ptr->qgauge_register->vbat_low_threshold;
     
     //need to get the right formula     
     vbatthreshold = ((int64)vbatlowThreshold * QGAUGE_BAT_THRESHOLD_DENR)/QGAUGE_BAT_THRESHOLD_NUMR;

     err_flag = pm_comm_write_byte(qgauge_ptr->comm_ptr->slave_id, reg, vbatthreshold);
   }
   
   return err_flag ;
};

pm_err_flag_type pm_qgauge_get_qgauge_pmic_info(uint8 *pmic_index, uint8 *slave_id)
{
    if((pmic_index == NULL)|| (slave_id == NULL))
    {
      return PM_ERR_FLAG_INVALID_PARAMETER;
    }

    pm_qgauge_get_pmic_info(pmic_index, slave_id);
    if(*pmic_index >= PM_MAX_NUM_PMICS || *slave_id >= PM_MAX_NUM_SLAVE_IDS)
    {
        return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
    else
    {
        return PM_ERR_FLAG_SUCCESS;
    }
}

pm_err_flag_type pm_qgauge_get_pon_ocv_acc_data(uint32 device_index, pm_qg_acc_index_type acc_index, uint16* data)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_address_type reg;
  pm_qgauge_data_type* qgauge_ptr = pm_qgauge_get_data(device_index);
  if(NULL == qgauge_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(NULL == data || acc_index >= PM_QG_ACC_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    reg = qgauge_ptr->qgauge_register->base_address + qgauge_ptr->qgauge_register->pon_ocv_acc0_data0;
    reg = reg + 2 * acc_index;
    err_flag = pm_comm_read_byte_array(qgauge_ptr->comm_ptr->slave_id, reg, 2, (uint8*)data);
  }
  return err_flag;
}
