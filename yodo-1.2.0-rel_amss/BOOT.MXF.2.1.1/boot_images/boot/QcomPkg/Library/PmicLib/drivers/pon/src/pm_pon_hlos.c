/*! \file pm_hlos_pon.c
*  \n
*  \brief PMIC PowerON HLOS Peripheral driver
*  \n
*  \n This header file contains class implementation of the PON
*  \n peripheral APIs
*  \n
*  \n &copy; Copyright 2012-2020 QUALCOMM Technologies Incorporated, All Rights Reserved
*/
/*===================================================================
			        EDIT HISTORY FOR MODULE
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/pon/src/pm_pon_hlos.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
20/10/29   cg     Created
========================================================================== */

/*===========================================================================

INCLUDE FILES FOR MODULE

===========================================================================*/

#include "pm_version.h"
#include "pm_pon_hlos.h"
#include "hw_module_type.h"
#include "device_info.h"
#include "pm_comm.h"
#include "pm_utils.h"
#include "pm_config_target.h"
#include "pm_device.h"
#include "pm_sbl_boot.h"
#include "CoreVerify.h"
#include "pm_pon_target.h"


/*===========================================================================
                 #defines 
===========================================================================*/


#define SET_TYPE_OFFSET      0x11
#define POLARITY_HIGH_OFFSET 0x12
#define POLARITY_LOW_OFFSET  0x13

#define PMIO_PON_HLOS_PERPH_TYPE_ADDR         ( PON_HLOS_BASE + 0x00000004 )
#define PMIO_PON_HLOS_PERPH_SUBTYPE_ADDR      ( PON_HLOS_BASE + 0x00000005 )
#define PMIO_PON_HLOS_INT_EN_SET_ADDR         ( PON_HLOS_BASE + 0x00000015 )
#define PMIO_PON_HLOS_INT_EN_CLR_ADDR         ( PON_HLOS_BASE + 0x00000016 )
#define PMIO_PON_HLOS_INT_LATCHED_CLR_ADDR    ( PON_HLOS_BASE + 0x00000014 )
#define PMIO_PON_HLOS_INT_SET_TYPE_ADDR       ( PON_HLOS_BASE + 0x00000011 )
#define PMIO_PON_HLOS_INT_POLARITY_HIGH_ADDR  ( PON_HLOS_BASE + 0x00000012 )
#define PMIO_PON_HLOS_INT_POLARITY_LOW_ADDR   ( PON_HLOS_BASE + 0x00000013 )
#define PMIO_PON_HLOS_INT_RT_STS_ADDR         ( PON_HLOS_BASE + 0x00000010 )
#define PMIO_PON_HLOS_INT_LATCHED_STS_ADDR    ( PON_HLOS_BASE + 0x00000018 )
#define PMIO_PON_HLOS_INT_PENDING_STS_ADDR    ( PON_HLOS_BASE + 0x00000019 )

#define PON_HLOS_GEN3 0x9
#define SINGLE_SLAVE  1
/*===========================================================================
                 local global variable 
===========================================================================*/

static boolean pm_pon_hlos_initialized = FALSE;

typedef struct
{
  peripheral_info_type periph_info;
}pm_pon_hlos_data_type;

static pm_pon_hlos_data_type pm_pon_hlos_data_arr[PM_MAX_NUM_PMICS];

/*===========================================================================
                  Function Prototypes
===========================================================================*/


/*===========================================================================
                  Local Function
===========================================================================*/

pm_err_flag_type
pm_pon_hlos_init(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8   pmic_index  = 0;
  uint8   sid_index   = 0;

  peripheral_info_type  pon_hlos_peripheral_info;
  uint32         slave_count = 0;
  pm_device_info_type pmic_device_info;
  uint8 periph_type = 0;
  uint8 sub_type    = 0;
  
  if (pm_pon_hlos_initialized == TRUE)
  {
    return err_flag;
  }

  memset(&pon_hlos_peripheral_info, 0, sizeof(peripheral_info_type));
  pon_hlos_peripheral_info.base_address = PON_HLOS_BASE;

  /* i.Ensure that pmic device is initialized ii.check for vaid PON peripheral */
  err_flag = pm_device_setup();
  if(pm_is_pmic_present(PMIC_A) == FALSE)
  {
     //pm_log_message("Bootup: No PMIC on RUMI Target");
     return err_flag = PM_ERR_FLAG_SUCCESS;
  }
  
  err_flag |= pm_comm_read_byte(PMIC_A_SLAVEID_PRIM, PMIO_PON_HLOS_PERPH_TYPE_ADDR, &periph_type);
  err_flag |= pm_comm_read_byte(PMIC_A_SLAVEID_PRIM, PMIO_PON_HLOS_PERPH_SUBTYPE_ADDR, &sub_type);
  
  if ((periph_type != PM_HW_MODULE_PON) || (sub_type != PON_HLOS_GEN3 ) || (err_flag != PM_ERR_FLAG_SUCCESS))
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  
  /* Get PON perepheral type and perepheral sub type for each valid PMIC on target */
  for (pmic_index = 0; pmic_index < PM_MAX_NUM_PMICS; pmic_index += slave_count)
  {
    sid_index = pmic_index;
    if (pm_get_peripheral_info(sid_index, &pon_hlos_peripheral_info) == PM_ERR_FLAG_SUCCESS)
    {
      pm_pon_hlos_data_arr[pmic_index].periph_info = pon_hlos_peripheral_info;
    }
  
  pm_get_pmic_info(pmic_index, &pmic_device_info);
  slave_count = (pmic_device_info.ePmicModel == PMIC_IS_UNKNOWN) ? SINGLE_SLAVE : pmic_device_info.nSlaveCount ;
  }
  
  if (err_flag == PM_ERR_FLAG_SUCCESS)
  {
    pm_pon_hlos_initialized = TRUE;
  }

  return err_flag;
}


/*internal function to return slave id*/
static pm_err_flag_type pm_pon_hlos_get_info(uint8 pmic_device_index, uint32 *pon_hlos_slave_id)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  if (NULL == pon_hlos_slave_id)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  if (pm_pon_hlos_initialized == FALSE)
  {
    err_flag = pm_pon_hlos_init();
    if (pm_pon_hlos_initialized != TRUE)
    {
      return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
  }

  err_flag = pm_get_slave_id(pmic_device_index, 0, pon_hlos_slave_id);

  return err_flag;
}

/*===========================================================================

API Implementation

===========================================================================*/


pm_err_flag_type
pm_pon_hlos_irq_enable(uint32 pmic_device_index, pm_pon_hlos_irq_type irq, boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 mask = 1 << irq;
  pm_register_address_type irq_reg = enable ? PMIO_PON_HLOS_INT_EN_SET_ADDR : PMIO_PON_HLOS_INT_EN_CLR_ADDR;

  uint32 slave_id = 0;

  if (irq >= PM_PON_HLOS_IRQ_INVALID)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    err_flag = pm_pon_hlos_get_info(pmic_device_index, &slave_id);
    if (err_flag == PM_ERR_FLAG_SUCCESS)
    {
      err_flag = pm_comm_write_byte(slave_id, irq_reg, mask);
    }
  }

  return err_flag;
}


pm_err_flag_type
pm_pon_hlos_irq_clear(uint32  pmic_device_index, pm_pon_hlos_irq_type irq)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 slave_id = 0;
  uint8 mask = 1 << irq;

  if (irq >= PM_PON_HLOS_IRQ_INVALID)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    err_flag = pm_pon_hlos_get_info(pmic_device_index, &slave_id);
    if (err_flag == PM_ERR_FLAG_SUCCESS)
    {
      err_flag = pm_comm_write_byte(slave_id, PMIO_PON_HLOS_INT_LATCHED_CLR_ADDR, mask);
    }
  }

  return err_flag;
}


pm_err_flag_type
pm_pon_hlos_irq_set_trigger(uint32 pmic_device_index, pm_pon_hlos_irq_type irq, pm_irq_trigger_type trigger)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 slave_id = 0;
  uint8 mask = 1 << irq;
  uint8 set_type = 0;
  uint8 polarity_high = 0;
  uint8 polarity_low = 0;

  if (irq >= PM_PON_HLOS_IRQ_INVALID)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

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

  err_flag = pm_pon_hlos_get_info(pmic_device_index, &slave_id);
  
  if (err_flag == PM_ERR_FLAG_SUCCESS)
  {
    err_flag = pm_comm_write_byte_mask(slave_id, PMIO_PON_HLOS_INT_SET_TYPE_ADDR, mask, set_type);
    err_flag |= pm_comm_write_byte_mask(slave_id, PMIO_PON_HLOS_INT_POLARITY_HIGH_ADDR, mask, polarity_high);
    err_flag |= pm_comm_write_byte_mask(slave_id, PMIO_PON_HLOS_INT_POLARITY_LOW_ADDR, mask, polarity_low);
  }

  return err_flag;
}


pm_err_flag_type
pm_pon_hlos_irq_status(uint32 pmic_device_index, pm_pon_hlos_irq_type irq, pm_irq_status_type type, boolean *status)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 slave_id = 0;
  uint8 mask = 1 << irq;
  uint8 data = 0;
  pm_register_address_type reg = 0;

  if (status == NULL)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  if (irq >= PM_PON_HLOS_IRQ_INVALID)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  switch (type)
  {
  case PM_IRQ_STATUS_RT:
    reg = PMIO_PON_HLOS_INT_RT_STS_ADDR;
    break;
  case PM_IRQ_STATUS_LATCHED:
    reg = PMIO_PON_HLOS_INT_LATCHED_STS_ADDR;
    break;
  case PM_IRQ_STATUS_PENDING:
    reg = PMIO_PON_HLOS_INT_PENDING_STS_ADDR;
    break;
  default:
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  err_flag = pm_pon_hlos_get_info(pmic_device_index, &slave_id);
  if (err_flag == PM_ERR_FLAG_SUCCESS)
  {
    err_flag = pm_comm_read_byte(slave_id, reg, &data);
    *status = (data & mask) ? TRUE : FALSE;
  }

  return err_flag;
}
