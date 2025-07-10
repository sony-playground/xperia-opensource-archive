/*! \file
*
*  \brief  pm_schg_typec.c driver implementation.
*  \details charger driver implementation.
*  &copy;
*   Copyright (c) 2017,2022 ,2023 Qualcomm Technologies, Inc. All rights reserved.
*   Confidential and Proprietary - Qualcomm Technologies, Inc.
*/

/*===========================================================================

EDIT HISTORY FOR MODULE


when        who    what, where, why
--------    ---    -------------------------------------------------------------
04/18/18    dc     Update dfp mask for not consider dfp in case of RA-Open
05/14/18    ra     Support for Debug Accessory Mode
04/06/18    dc     Fix source/dfp mode detection
02/20/18    richaa Removing obsolete code
10/18/17    richaa Initial revision
=============================================================================== */

/*=============================================================================

          INCLUDE FILES

===============================================================================*/
#include "pm_schg_driver.h"
#include "pm_schg_typec.h"

/*===========================================================================
                       MACRO DECLARATIONS
===========================================================================*/

#define ADDRESS(x) (schg_ptr->schg_register->typec_register->base_address + schg_ptr->schg_register->typec_register->x)
#define SLAVE_ID   (schg_ptr->comm_ptr->slave_id)

/*===========================================================================

FUNCTION DEFINITIONS

===========================================================================*/
pm_err_flag_type pm_schg_usb_get_typec_status(uint32 pmic_index, pm_chg_typec_status_type *typec_status)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 typec_port_status[6] = {0};
  pm_schg_data_type *schg_ptr = pm_schg_get_data(pmic_index);

  if(NULL == schg_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(typec_status == NULL)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type address = ADDRESS(typec_snk_status);
    err_flag = pm_comm_read_byte_array(SLAVE_ID, address, 6, (uint8 *)&typec_port_status);

    if(typec_port_status[0] & 0x02)
    {
      typec_status->dfp_curr_adv = PM_TYPEC_CURR_ADV_3A;
    }
    else if(typec_port_status[0] & 0x04)
    {
      typec_status->dfp_curr_adv = PM_TYPEC_CURR_ADV_1P5A;
    }
    else if(typec_port_status[0] & 0x08)
    {
      typec_status->dfp_curr_adv = PM_TYPEC_CURR_ADV_STD;
    }
    else
    {
      typec_status->dfp_curr_adv = PM_TYPEC_CURR_ADV_INVALID;
    }

    if(typec_port_status[2] & 0x08)
    { //DFP mode - RD/Open on CC1/CC2
      typec_status->ufp_conn_type = PM_CHG_TYPEC_UFP_ATTACHED;
    }
    else if(typec_port_status[2] & 0x04)
    { //DFP mode - RD/RA on CC1/CC2
      typec_status->ufp_conn_type = PM_CHG_TYPEC_UFP_ATTACHED_POWER_CABLE;
    }
    else if(typec_port_status[2] & 0x10)
    { //	DFP mode - RD/RD on CC1/CC2
      typec_status->ufp_conn_type = PM_CHG_TYPEC_UFP_DEBUG_ACCESSORY;
    }
    else if(typec_port_status[2] & 0x01)
    { //DFP mode - RA/RA on CC1/CC2
      typec_status->ufp_conn_type = PM_CHG_TYPEC_UFP_AUDIO_ADAPTER;
    }
    else
    {
      typec_status->ufp_conn_type = PM_CHG_TYPEC_UFP_INVALID;
    }

    typec_status->vbus_sts          = (typec_port_status[5] & 0x20) ? TRUE : FALSE;
    typec_status->vbus_err_sts      = (typec_port_status[5] & 0x10) ? TRUE : FALSE;
    typec_status->debounce_done_sts = (typec_port_status[5] & 0x08) ? TRUE : FALSE;
    typec_status->vconn_oc_sts      = (typec_port_status[5] & 0x04) ? TRUE : FALSE;
    typec_status->ccout_out_hiz_sts = (typec_port_status[5] & 0x01) ? TRUE : FALSE;
    typec_status->cc_out_sts        = (typec_port_status[5] & 0x02) ? PM_CHG_TYPEC_ORIENTATION_PLUG_FLIP : PM_CHG_TYPEC_ORIENTATION_PLUG_UNFLIP;
  }

  return err_flag;
}

pm_err_flag_type pm_schg_usb_get_typec_vbus_status(uint32 pmic_index, boolean *vbus_status)
{
  pm_err_flag_type err_flag  = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data = 0x00;
  pm_register_data_type vbus_status_mask = 0x20;

  pm_schg_data_type *schg_ptr  = pm_schg_get_data(pmic_index);
  if(NULL == schg_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(vbus_status == NULL)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type address = ADDRESS(typec_misc_status);
    err_flag = pm_comm_read_byte(SLAVE_ID, address, &data);

    *vbus_status = (data & vbus_status_mask) ? TRUE : FALSE;
  }

  return err_flag;
}

pm_err_flag_type pm_schg_usb_typec_get_port_role(uint32 pmic_index, pm_chg_typec_port_role_type *port_role)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 typec_port_status[4] = {0};
  uint8 current_adv_mask = 0x0E;
  uint8 dfp_mask = 0x0D;
  uint8 dam_sink_mask = 0x70;
  uint8 dam_typec_state_machine = 0x2C;
  pm_schg_data_type *schg_ptr = pm_schg_get_data(pmic_index);

  if(NULL == port_role)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  *port_role = PM_CHG_TYPEC_ROLE_INVALID;

  if(NULL == schg_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type address = ADDRESS(typec_snk_status);

    err_flag = pm_comm_read_byte_array(SLAVE_ID, address, sizeof(typec_port_status), typec_port_status);
    if(PM_ERR_FLAG_SUCCESS != err_flag)
    {
      return err_flag;
    }

    if(current_adv_mask & typec_port_status[0])
    {
      *port_role = PM_CHG_TYPEC_ROLE_UFP;
    }
    else if(dfp_mask & typec_port_status[2])
    {
      *port_role = PM_CHG_TYPEC_ROLE_DFP;
    }
    else if ((dam_sink_mask & typec_port_status[0]) || (dam_typec_state_machine & typec_port_status[3]))
    {
	  *port_role = PM_CHG_TYPEC_ROLE_UFP;
    }
    else
    {
      *port_role = PM_CHG_TYPEC_ROLE_NONE;
    }
  }

  return err_flag;
}

pm_err_flag_type pm_schg_usb_typec_set_port_role(uint32 pmic_index, pm_chg_typec_port_role_type port_role)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data = 0x00;
  uint8 mask = 0x06;
  pm_schg_data_type *schg_ptr = pm_schg_get_data(pmic_index);

  if(NULL == schg_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type type_c_mode_cfg = ADDRESS(typec_mode_cfg);
    if(port_role >= PM_CHG_TYPEC_ROLE_INVALID || port_role <= PM_CHG_TYPEC_ROLE_NONE)
    {
      return PM_ERR_FLAG_INVALID_PARAMETER;
    }
    else
    {
      if(port_role == PM_CHG_TYPEC_ROLE_DFP)
      {
        data = port_role << 2;
      }
    }

    err_flag = pm_comm_write_byte_mask(SLAVE_ID, type_c_mode_cfg, mask, data);
  }
  return err_flag;
}

pm_err_flag_type pm_schg_usb_typec_vconn_enable(uint32 pmic_index, pm_schg_usb_typec_vconn_enable_type enable_type)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_schg_data_type *schg_ptr = pm_schg_get_data(pmic_index);
  pm_register_data_type data = 0x00;
  uint8 mask = 0x03;

  if(NULL == schg_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(enable_type >= PM_SCHG_USB_TYPEC_VCONN_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type type_c_intrpt_enb_software_ctrl = ADDRESS(typec_vconn_control);
    data = enable_type;
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, type_c_intrpt_enb_software_ctrl, mask, data);
  }

  return err_flag;
}

pm_err_flag_type pm_schg_usb_typec_disable(uint32 pmic_index, boolean disable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_schg_data_type *schg_ptr = pm_schg_get_data(pmic_index);
  uint8 mask = 0x01;

  if(NULL == schg_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type type_c_intrpt_enb_software_ctrl = ADDRESS(typec_mode_cfg);
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, type_c_intrpt_enb_software_ctrl, mask, disable ? 0x1 : 0x0);
  }

  return err_flag;
}

pm_err_flag_type pm_schg_usb_typec_enable_try_sink_mode(uint32 pmic_index, boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_schg_data_type *schg_ptr = pm_schg_get_data(pmic_index);
  pm_register_data_type data = (enable ? 0x1 : 0x0) << 4;
  pm_register_data_type mask = 0x10;

  if(NULL == schg_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type type_c_cfg_3 = ADDRESS(typec_mode_cfg);

    err_flag = pm_comm_write_byte_mask(SLAVE_ID, type_c_cfg_3, mask, data);
  }

  return err_flag;
}

pm_err_flag_type pm_schg_typec_en_dbg_access_snk(uint32 pmic_index, boolean EnDbgAccessSnk)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_schg_data_type *schg_ptr = pm_schg_get_data(pmic_index);
  pm_register_data_type data = EnDbgAccessSnk;
  pm_register_data_type mask = 0x01;

  if(NULL == schg_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type type_c_snk_cfg = ADDRESS(typec_debug_access_snk_cfg);
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, type_c_snk_cfg, mask, data);
  }

  return err_flag;
}

pm_err_flag_type pm_schg_typec_dam_en_aicl(uint32 pmic_index, boolean en_aicl)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_schg_data_type *schg_ptr = pm_schg_get_data(pmic_index);
  pm_register_data_type data = en_aicl ? 0x00 : 0xFF; // bit[3] = 0 will enable AICL
  pm_register_data_type mask = 0x08;
  if (NULL == schg_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type type_c_snk_cfg = ADDRESS(typec_debug_access_snk_cfg);
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, type_c_snk_cfg, mask, data);
  }
  return err_flag;
}

pm_err_flag_type pm_schg_typec_en_chg_on_dam_snk(uint32 pmic_index, boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_schg_data_type *schg_ptr = pm_schg_get_data(pmic_index);
  pm_register_data_type data = enable ? PM_BIT(1) : 0;
  pm_register_data_type mask = PM_BIT(1);

  if(NULL == schg_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type type_c_snk_cfg = ADDRESS(typec_debug_access_snk_cfg);
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, type_c_snk_cfg, mask, data);
  }

  return err_flag;
}


pm_err_flag_type pm_schg_typec_en_fmb(uint32 pmic_index, boolean EnFmb)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_schg_data_type *schg_ptr = pm_schg_get_data(pmic_index);
  pm_register_data_type data = EnFmb << 4;
  pm_register_data_type mask = 0x10;

  if(NULL == schg_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type type_c_snk_cfg = ADDRESS(typec_debug_access_snk_cfg);
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, type_c_snk_cfg, mask, data);
  }

  return err_flag;
}

pm_err_flag_type pm_schg_typec_get_dam_connect_sts(uint32 pmic_index, boolean *ConnectSts)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_schg_data_type *schg_ptr = pm_schg_get_data(pmic_index);
  pm_register_data_type data = 0;
  uint8 mask = 0x3F;

  if(NULL == schg_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type type_c_access_status = ADDRESS(typec_debug_access_status);
    err_flag = pm_comm_read_byte_mask(SLAVE_ID, type_c_access_status, mask, &data);
    if(ConnectSts != NULL)
    {
      *ConnectSts = data ? 1 : 0;
    }
  }

  return err_flag;
}

pm_err_flag_type pm_schg_typec_set_dam_icl(uint32 pmic_index, pm_schg_usb_typec_dam_icl_sel icl_sel)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_schg_data_type *schg_ptr = pm_schg_get_data(pmic_index);
  pm_register_data_type data = icl_sel << 2;
  pm_register_data_type mask = 0x04;

  if(NULL == schg_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type type_c_snk_cfg = ADDRESS(typec_debug_access_snk_cfg);
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, type_c_snk_cfg, mask, data);
  }

  return err_flag;
}

pm_err_flag_type pm_schg_typec_get_usb_connector_type(uint32 device_index, pm_typec_connector_type *usb_connector)
{
  pm_err_flag_type    err_flag    = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data = 0x00;
  uint8 mask = 0x01;
  pm_schg_data_type *schg_ptr  = pm_schg_get_data(device_index);
  
  if(NULL == schg_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(usb_connector == NULL)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type address = ADDRESS(typec_u_usb_cfg);
    err_flag = pm_comm_read_byte_mask(SLAVE_ID, address, mask, &data);
    *usb_connector = (pm_typec_connector_type)data;
  }
  
  return err_flag;
}
