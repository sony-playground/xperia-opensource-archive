/*! \file
 *  
 *  \brief  pm_dtb_parser.c ----This file contains the implementation of dtb parsing
 *  
 *  &copy; Copyright 2021-2022 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================
  EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.


  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/utils/src/pm_dt_parser.c#4 $
  $Author: pwbldsvc $
  $DateTime: 2022/12/01 01:05:41 $
  when       who     what, where, why
  --------   ---     ---------------------------------------------------------- 

  03/29/21   al      Created

  ===========================================================================*/

/*===========================================================================

  INCLUDE FILES 

  ===========================================================================*/

#include <stdio.h>
#include "CoreVerify.h"
#include "comdef.h"
#include "DTBExtnLib.h"

#include "pm_dt_parser.h"
#include "pm_utils.h"
#include "pm_log_utils.h"

#define FDT_RETURNED_SUCCESS    0
#define DTB_LINE_BUF_SIZE       0x80
#define SIZE_OF_ARR(arr)        (sizeof(arr)/sizeof(arr[0]))

static void *fdt_handle;

static pm_dt_pvc_config         *pvc_dt_config;
static pm_dt_mgpi_config        *mgpi_dt_config;
static pm_dt_charger_config     *charger_dt_config;
static pm_access_ctrl_config    *access_dt_ctrl; 
static pm_dt_haptics_config     *haptics_dt_config;
static pm_dt_display_config     *display_dt_config;
static pm_dt_pon_config         *pon_dt_config;
static pm_dt_sw_config          *sw_dt_config;
static pm_dt_camera_config      *camera_dt_config;
static pm_dt_psi_config         *psi_dt_config;

static char* node_str_arr[] = 
{
  [PMIC_DT_NODE_PM_SW_CONFIG]  = "/sw/pmic/pm/sw-config",   
  [PMIC_DT_NODE_PM_PON]        = "/sw/pmic/pm/pon",   
  [PMIC_DT_NODE_PM_CHARGER]    = "/sw/pmic/pm/charger", 
  [PMIC_DT_NODE_PM_HAPTICS]    = "/sw/pmic/pm/haptics",    
  [PMIC_DT_NODE_PM_DISPLAY]    = "/sw/pmic/pm/display",         
  [PMIC_DT_NODE_PM_CAMERA]     = "/sw/pmic/pm/camera",     
  [PMIC_DT_NODE_ARB_ACCESS]    = "/sw/pmic/arb/access",    
  [PMIC_DT_NODE_ARB_MGPI]      = "/sw/pmic/arb/mgpi",   
  [PMIC_DT_NODE_ARB_PVC]       = "/sw/pmic/arb/pvc",
  [PMIC_DT_NODE_OPSI_CONFIG]   = "/sw/pmic/psi", 
};


static void 
pm_dt_error_chk(pm_err_flag_type err_flag, char* msg)
{
  if(err_flag != PM_ERR_FLAG_SUCCESS) 
  { 
    pm_log_message("PM_DT_PARSING_ERR: %s", msg); 
  } 
}

static pm_err_flag_type
pm_get_uint32_value(fdt_node_handle* hNode_ptr, const char* label, uint32* ptr)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;  
  uint32 value = 0;
  int fdt_ret = 0;
  
  fdt_ret = fdt_get_uint32_prop(hNode_ptr, label, &value);
  
  if((fdt_ret == FDT_RETURNED_SUCCESS) && (ptr != NULL))
  { 
    *ptr = value;
  }
  
  err_flag = (fdt_ret == FDT_RETURNED_SUCCESS) ? PM_ERR_FLAG_SUCCESS : PM_ERR_FLAG_FAILURE;
  
  return err_flag;
}

static pm_err_flag_type
pm_get_uint16_value(fdt_node_handle* hNode_ptr, const char* label, uint16* ptr)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;  
  uint16 value = 0;
  int fdt_ret = 0;
  
  fdt_ret = fdt_get_uint16_prop(hNode_ptr, label, &value);
  
  if((fdt_ret == FDT_RETURNED_SUCCESS) && (ptr != NULL))
  { 
    *ptr = value;
  }
  
  err_flag = (fdt_ret == FDT_RETURNED_SUCCESS) ? PM_ERR_FLAG_SUCCESS : PM_ERR_FLAG_FAILURE;
  
  return err_flag;
}

static pm_err_flag_type
pm_get_uint8_value(fdt_node_handle* hNode_ptr, const char* label, uint8* ptr)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;    
  uint8 value = 0;
  int fdt_ret = 0;
  
  fdt_ret = fdt_get_uint8_prop( hNode_ptr, label, &value );
  
  if((fdt_ret == FDT_RETURNED_SUCCESS) && (ptr != NULL))
  { 
    *ptr = value;
  }
  
  err_flag = (fdt_ret == FDT_RETURNED_SUCCESS) ? PM_ERR_FLAG_SUCCESS : PM_ERR_FLAG_FAILURE;
  
  return err_flag;
}

static pm_err_flag_type
pm_target_information_dt_init(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  int fdt_ret = FDT_RETURNED_SUCCESS;
 
  if(pm_get_img_type() == PM_IMG_CORE) //core doesn't need blob handle
  {
    err_flag = PM_ERR_FLAG_SUCCESS;
  }
  else
  {
    fdt_ret = fdt_get_blob_handle(&fdt_handle, DEFAULT_BLOB_ID);
    err_flag = (fdt_ret != FDT_RETURNED_SUCCESS || fdt_handle == NULL) 
                ? PM_ERR_FLAG_FAILURE : err_flag;
  }  

  return err_flag;
}

uint32
pm_dt_get_node_prop_size(uint32 node_id, const char *prop_name)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  int fdt_ret = FDT_RETURNED_SUCCESS;
  fdt_node_handle hNode = {0};
  uint32 size = 0;

  err_flag = pm_target_information_dt_init();
  
  if((PM_ERR_FLAG_SUCCESS == err_flag) && (node_id < SIZE_OF_ARR(node_str_arr)))
  {
    fdt_ret |= fdt_get_node_handle(&hNode, fdt_handle, node_str_arr[node_id]);
    
    fdt_ret |= fdt_get_prop_size(&hNode, prop_name, &size);
    
    size = (fdt_ret != FDT_RETURNED_SUCCESS) ? 0 : size;
  }
  
  return size;
}

pm_err_flag_type
pm_dt_get_node_prop_value(uint32 node_id, const char *prop_name, uint32 size, uint32 *prop_list)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  int fdt_ret = FDT_RETURNED_SUCCESS;
  fdt_node_handle hNode = {0};

  err_flag |= pm_target_information_dt_init();
  
  if((PM_ERR_FLAG_SUCCESS == err_flag) && (node_id < SIZE_OF_ARR(node_str_arr)))
  {
    // null check handled by fdt api's 
    fdt_ret |= fdt_get_node_handle(&hNode, fdt_handle, node_str_arr[node_id]);
   
    // size check handled by fdt api's 
    fdt_ret |= fdt_get_uint32_prop_list(&hNode, prop_name, prop_list, size);
    
    err_flag = (fdt_ret != FDT_RETURNED_SUCCESS ) ? PM_ERR_FLAG_FAILURE : err_flag;
  }
  else
  {
    err_flag = PM_ERR_FLAG_FAILURE;
  }
  
  return err_flag;
}

/*parse sw node*/
static void*
pm_dt_parse_sw_config(uint32 prop_id)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  int fdt_ret = FDT_RETURNED_SUCCESS;
  static boolean parsed = FALSE;
  fdt_node_handle hNode = {0}; 
  uint32 size = 0;

  if(parsed)
  {
    return sw_dt_config;
  }

  pm_malloc(sizeof(pm_dt_sw_config), (void**)&sw_dt_config);
  fdt_ret = fdt_get_node_handle(&hNode, fdt_handle, node_str_arr[prop_id]);
  
  if(fdt_ret == FDT_RETURNED_SUCCESS)
  {  
    err_flag |= pm_get_uint32_value( &hNode, "verbose", &sw_dt_config->verbose );
    err_flag |= pm_get_uint32_value( &hNode, "apply-rsns-trim", &sw_dt_config->apply_rsns_trim);
    err_flag |= pm_get_uint32_value( &hNode, "rsns-trim-value", &sw_dt_config->rsns_trim_value);
    err_flag |= pm_get_uint32_value( &hNode, "primming-enable", &sw_dt_config->primming_enable);
 
    fdt_ret = fdt_get_prop_size(&hNode, "driver-post-init", &size);
    if((size > 0) && (fdt_ret == FDT_RETURNED_SUCCESS))
    {
      sw_dt_config->post_driver_init_count = size / (5 * sizeof(uint32)); //divide by 5 since there are 5 members per entry
      
      pm_malloc(size, (void**)&sw_dt_config->post_driver_init);
      
      fdt_ret = fdt_get_uint32_prop_list(&hNode, "driver-post-init", sw_dt_config->post_driver_init, size); 
    }

    pm_dt_error_chk(err_flag, "sw-config");

    parsed = TRUE;
  }
  else
  {
    pm_free((void**)&sw_dt_config);
  }

  return sw_dt_config;
}


/*parse PON node*/
static void*
pm_dt_parse_pon_config(uint32 prop_id)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  static boolean parsed = FALSE;
  fdt_node_handle hNode = {0};
  char node_buf[DTB_LINE_BUF_SIZE] = {0};    
  int fdt_ret = FDT_RETURNED_SUCCESS;
  uint32 size = 0;
  
  if(parsed)
  {
    return pon_dt_config;
  }

  pm_malloc(sizeof(pm_dt_pon_config), (void**)&pon_dt_config);
  
  snprintf(node_buf, DTB_LINE_BUF_SIZE, "%s/pshold", node_str_arr[prop_id]);
  fdt_ret = fdt_get_node_handle(&hNode, fdt_handle, node_buf);
  if(fdt_ret == FDT_RETURNED_SUCCESS)
  {
    err_flag = pm_get_uint8_value( &hNode, "enable", &pon_dt_config->pshold_enable );  
    err_flag |= pm_get_uint8_value( &hNode, "reset-type", &pon_dt_config->ps_hold_reset_type );
    pm_dt_error_chk(err_flag, "pshold");
  }

  snprintf(node_buf, DTB_LINE_BUF_SIZE, "%s/smpl", node_str_arr[prop_id]);
  fdt_ret = fdt_get_node_handle(&hNode, fdt_handle, node_buf);
  if(fdt_ret == FDT_RETURNED_SUCCESS)
  {
    err_flag |= pm_get_uint8_value( &hNode, "enable", &pon_dt_config->enable_smpl );
    err_flag |= pm_get_uint32_value( &hNode, "smpl-delay", &pon_dt_config->smpl_delay );
    pm_dt_error_chk(err_flag, "smpl");
  }

  snprintf(node_buf, DTB_LINE_BUF_SIZE, "%s/s2-kpdpwr", node_str_arr[prop_id]);
  fdt_ret = fdt_get_node_handle(&hNode, fdt_handle, node_buf);
  if(fdt_ret == FDT_RETURNED_SUCCESS)
  {
    err_flag |= pm_get_uint8_value( &hNode, "enable", &pon_dt_config->s2_kpdpwr_enable);  
    err_flag |= pm_get_uint8_value( &hNode, "reset-type", &pon_dt_config->s2_kpdpwr_reset_type);      
    err_flag |= pm_get_uint32_value( &hNode, "s1-ms", &pon_dt_config->s2_kpdpwr_s1_ms );  
    err_flag |= pm_get_uint32_value( &hNode, "s2-ms", &pon_dt_config->s2_kpdpwr_s2_ms);
    pm_dt_error_chk(err_flag, "s2-kpdpwr");
  }

  snprintf(node_buf, DTB_LINE_BUF_SIZE, "%s/s2-kpdpwr-resin", node_str_arr[prop_id]);
  fdt_ret = fdt_get_node_handle(&hNode, fdt_handle, node_buf);
  if(fdt_ret == FDT_RETURNED_SUCCESS)
  {
    err_flag = pm_get_uint8_value( &hNode, "enable", &pon_dt_config->s2_kpdpwr_resin_enable);
    err_flag |= pm_get_uint8_value( &hNode, "reset-type", &pon_dt_config->s2_kpdpwr_resin_reset_type);        
    err_flag |= pm_get_uint32_value( &hNode, "s1-ms", &pon_dt_config->s2_kpdpwr_resin_s1_ms);  
    err_flag |= pm_get_uint32_value( &hNode, "s2-ms", &pon_dt_config->s2_kpdpwr_resin_s2_ms);
    pm_dt_error_chk(err_flag, "s2-kpdpwr-resin");
  }

  snprintf(node_buf, DTB_LINE_BUF_SIZE, "%s/s2-resin", node_str_arr[prop_id]);
  fdt_ret = fdt_get_node_handle(&hNode, fdt_handle, node_buf);
  if(fdt_ret == FDT_RETURNED_SUCCESS)
  { 
    err_flag = pm_get_uint8_value( &hNode, "enable", &pon_dt_config->s2_resin_enable );   
    err_flag |= pm_get_uint8_value( &hNode, "reset-type", &pon_dt_config->s2_resin_reset_type );       
    err_flag |= pm_get_uint32_value( &hNode, "s1-ms", &pon_dt_config->s2_resin_s1_ms );  
    err_flag |= pm_get_uint32_value( &hNode, "s2-ms", &pon_dt_config->s2_resin_s2_ms );
    pm_dt_error_chk(err_flag, "s2_resin");
  }

  snprintf(node_buf, DTB_LINE_BUF_SIZE, "%s/s3-reset", node_str_arr[prop_id]);
  fdt_ret = fdt_get_node_handle( &hNode, fdt_handle, node_buf );
  if(fdt_ret == FDT_RETURNED_SUCCESS)
  {    
    err_flag = pm_get_uint8_value( &hNode, "enable", &pon_dt_config->s3_enable );
    err_flag = pm_get_uint8_value( &hNode, "s3-src", &pon_dt_config->s3_reset_src );  
    err_flag |= pm_get_uint32_value( &hNode, "timer-value-ms", &pon_dt_config->s3_reset_timer_value_ms );
    pm_dt_error_chk(err_flag, "s3-reset");
  }

  snprintf(node_buf, DTB_LINE_BUF_SIZE, "%s/uvlo-config", node_str_arr[prop_id]);
  fdt_ret = fdt_get_node_handle(&hNode, fdt_handle, node_buf);
  fdt_ret |= fdt_get_prop_size(&hNode, "config-value", &size);
  if((size > 0) && (fdt_ret == FDT_RETURNED_SUCCESS))
  {
    pon_dt_config->uvlo_config_count = size / (4 * sizeof(uint32));  //divide by 4 since there are 4 members per entry
    pm_malloc(sizeof(uint32) * size,(void**)&pon_dt_config->uvlo_cfg);
    
    fdt_ret = fdt_get_uint32_prop_list(&hNode, "config-value", pon_dt_config->uvlo_cfg, size);

    }   
    
  snprintf(node_buf, DTB_LINE_BUF_SIZE, "%s/ovlo-config", node_str_arr[prop_id]);
  fdt_ret = fdt_get_node_handle(&hNode, fdt_handle, node_buf);
  fdt_ret |= fdt_get_prop_size(&hNode, "config-value", &size);
  if((size > 0) && (fdt_ret == FDT_RETURNED_SUCCESS))
  {
    pon_dt_config->ovlo_config_count = size / (4 * sizeof(uint32));  //divide by 4 since there are 4 members per entry
    pm_malloc(sizeof(uint32) * size,(void**)&pon_dt_config->ovlo_cfg);
    
    fdt_ret = fdt_get_uint32_prop_list(&hNode, "config-value", pon_dt_config->ovlo_cfg, size);
  }

  snprintf(node_buf, DTB_LINE_BUF_SIZE, "%s/long-pwrkey-dbnc-chk", node_str_arr[prop_id]);
  fdt_ret = fdt_get_node_handle(&hNode, fdt_handle, node_buf);
  if(fdt_ret == FDT_RETURNED_SUCCESS)
  {
    err_flag = pm_get_uint32_value( &hNode, "dbnc-time-ms", &pon_dt_config->dbnc_time_ms);  
    err_flag |= pm_get_uint8_value( &hNode, "chk-at", &pon_dt_config->dbnc_chk_at);
    pm_dt_error_chk(err_flag, "long-pwrkey-dbnc-chk");
  }

  snprintf(node_buf, DTB_LINE_BUF_SIZE, "%s/pre-psi", node_str_arr[prop_id]);
  fdt_ret = fdt_get_node_handle(&hNode, fdt_handle, node_buf);
  if(fdt_ret == FDT_RETURNED_SUCCESS)
  {
    err_flag |= pm_get_uint8_value( &hNode, "vreg-sp-value", &pon_dt_config->vreg_sp_flag_val);  
    err_flag |= pm_get_uint8_value( &hNode, "pre-psi-value", &pon_dt_config->pre_psi_flag_val);
    pm_dt_error_chk(err_flag, "pre-psi");
  }

  parsed = TRUE;

  return pon_dt_config;
}

/*parse display node*/
static void*
pm_dt_parse_display_config(uint32 prop_id)
{
  static boolean parsed = FALSE;
  fdt_node_handle hNode = {0};  
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  int fdt_ret = FDT_RETURNED_SUCCESS;

  if(parsed)
  {
    return display_dt_config;
  }
  
  pm_malloc(sizeof(pm_dt_display_config), (void**)&display_dt_config);

  fdt_ret = fdt_get_node_handle(&hNode, fdt_handle, node_str_arr[prop_id]);
  if(fdt_ret == FDT_RETURNED_SUCCESS)
  {
    err_flag |= pm_get_uint8_value( &hNode, "swire-map", &display_dt_config->swire_map );
    err_flag |= pm_get_uint32_value( &hNode, "apply-default-volt", (uint32*)&display_dt_config->apply_default_volt );
    err_flag |= pm_get_uint32_value( &hNode, "default-elvss", (uint32*)&display_dt_config->default_elvss );
    err_flag |= pm_get_uint32_value( &hNode, "default-elvdd", (uint32*)&display_dt_config->default_elvdd );
    err_flag |= pm_get_uint32_value( &hNode, "default-oledb", (uint32*)&display_dt_config->default_oledb );
    pm_dt_error_chk(err_flag, "display");

    parsed = TRUE;
  }
  else
  {
    pm_free((void**)&display_dt_config);
  }
  
  return display_dt_config;
}


/*parse haptics node*/
static void*
pm_dt_parse_haptics_config(uint32 prop_id)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  static boolean parsed = FALSE;
  fdt_node_handle hNode = {0};
  int fdt_ret = FDT_RETURNED_SUCCESS;

  if(parsed)
  {
    return haptics_dt_config;
  }

  pm_malloc(sizeof(pm_dt_haptics_config), (void**)&haptics_dt_config);

  fdt_ret = fdt_get_node_handle(&hNode, fdt_handle, node_str_arr[prop_id]);
  if(fdt_ret == FDT_RETURNED_SUCCESS)
  {
    err_flag |= pm_get_uint32_value( &hNode, "ext-boost-vdd", &haptics_dt_config->ext_boost_vdd );  
    err_flag |= pm_get_uint32_value( &hNode, "vmax-hdrm", &haptics_dt_config->vmax_hdrm );  
    err_flag |= pm_get_uint32_value( &hNode, "vmax-mv", &haptics_dt_config->vmax_mv );
    err_flag |= pm_get_uint32_value( &hNode, "tlra-ol", &haptics_dt_config->tlra_ol );
    err_flag |= pm_get_uint32_value( &hNode, "autores-cfg", &haptics_dt_config->autores_cfg );  
    err_flag |= pm_get_uint32_value( &hNode, "vbatt-min", &haptics_dt_config->vbatt_min_mv );  
    err_flag |= pm_get_uint32_value( &hNode, "boost-cfg-bob", &haptics_dt_config->boost_cfg_bob );
	err_flag |= pm_get_uint32_value( &hNode, "lra-resistance", &haptics_dt_config->lra_resistance ); 
	err_flag |= pm_get_uint32_value( &hNode, "swr-io-volt", &haptics_dt_config->swr_io_volt ); 
    pm_dt_error_chk( err_flag, "haptics" );

    parsed = TRUE;
  }
  else
  {
    pm_free((void**)&haptics_dt_config);
  }

  return haptics_dt_config;
}


static void*
pm_dt_parse_access_ctrl_config(uint32 prop_id)
{
  static boolean parsed = FALSE;  
  fdt_node_handle hNode = {0};  
  
  uint32 size = 0, num_of_items = 0;
  int fdt_ret = FDT_RETURNED_SUCCESS;

  if(parsed)
  {
    return access_dt_ctrl;
  }

  pm_malloc(sizeof(pm_access_ctrl_config), (void**)&access_dt_ctrl);  
  fdt_ret = fdt_get_node_handle(&hNode, fdt_handle, node_str_arr[prop_id]);
  if(fdt_ret != FDT_RETURNED_SUCCESS)
  {
    return access_dt_ctrl;
  }
  
  //none
  fdt_ret |= fdt_get_prop_size(&hNode, "none", &size);   
  if((size > 0) && (fdt_ret == FDT_RETURNED_SUCCESS))
  {
    num_of_items = size / (4 * sizeof(uint32));
    access_dt_ctrl->none_count = num_of_items;
    pm_malloc(size, (void**)&access_dt_ctrl->none_owner);
    fdt_ret = fdt_get_uint32_prop_list(&hNode, "none", access_dt_ctrl->none_owner, size);
  }
  
  //apps  
  fdt_ret |= fdt_get_prop_size(&hNode, "apps", &size);   
  if((size > 0) && (fdt_ret == FDT_RETURNED_SUCCESS))
  {
    num_of_items = size / (4 * sizeof(uint32));
    access_dt_ctrl->apps_count = num_of_items;
    pm_malloc(size, (void**)&access_dt_ctrl->apps_owner);
    fdt_ret = fdt_get_uint32_prop_list(&hNode, "apps", access_dt_ctrl->apps_owner, size);
  }  
  
  //tz 
  fdt_ret |= fdt_get_prop_size(&hNode, "tz", &size);
  if((size > 0) && (fdt_ret == FDT_RETURNED_SUCCESS))
  {
    num_of_items = size / (4 * sizeof(uint32));
    access_dt_ctrl->tz_count = num_of_items;
    pm_malloc(size, (void**)&access_dt_ctrl->tz_owner);
    fdt_ret = fdt_get_uint32_prop_list(&hNode, "tz", access_dt_ctrl->tz_owner, size);
  } 

  //mss  
  fdt_ret |= fdt_get_prop_size(&hNode, "mss", &size);   
  if((size > 0) && (fdt_ret == FDT_RETURNED_SUCCESS))
  {
    num_of_items = size / (4 * sizeof(uint32));
    access_dt_ctrl->mss_count = num_of_items;
    pm_malloc(size, (void**)&access_dt_ctrl->mss_owner);
    fdt_ret = fdt_get_uint32_prop_list(&hNode, "mss", access_dt_ctrl->mss_owner, size);
  }

  //uefi  
  fdt_ret |= fdt_get_prop_size(&hNode, "uefi", &size);   
  if((size > 0) && (fdt_ret == FDT_RETURNED_SUCCESS))
  {
    num_of_items = size / (4 * sizeof(uint32));
    access_dt_ctrl->uefi_count = num_of_items;
    pm_malloc(size, (void**)&access_dt_ctrl->uefi_owner);
    fdt_ret = fdt_get_uint32_prop_list(&hNode, "uefi", access_dt_ctrl->uefi_owner, size);
  }

  //adsp 
  fdt_ret |= fdt_get_prop_size(&hNode, "adsp", &size);   
  if((size > 0) && (fdt_ret == FDT_RETURNED_SUCCESS))
  {
    num_of_items = size / (4 * sizeof(uint32));
    access_dt_ctrl->adsp_count = num_of_items;
    pm_malloc(size, (void**)&access_dt_ctrl->adsp_owner);
    fdt_ret = fdt_get_uint32_prop_list(&hNode, "adsp", access_dt_ctrl->adsp_owner, size);
  }

  //aop
  fdt_ret |= fdt_get_prop_size(&hNode, "aop", &size);   
  if((size > 0) && (fdt_ret == FDT_RETURNED_SUCCESS))
  {
    num_of_items = size / (4 * sizeof(uint32));
    access_dt_ctrl->aop_count = num_of_items;
    pm_malloc(size, (void**)&access_dt_ctrl->aop_owner);
    fdt_ret = fdt_get_uint32_prop_list(&hNode, "aop", access_dt_ctrl->aop_owner, size);
  } 

  //secpro 
  fdt_ret |= fdt_get_prop_size(&hNode, "secpro", &size);   
  if((size > 0) && (fdt_ret == FDT_RETURNED_SUCCESS))
  {
    num_of_items = size / (4 * sizeof(uint32));
    access_dt_ctrl->secpro_count = num_of_items;
    pm_malloc(size, (void**)&access_dt_ctrl->secpro_owner);
    fdt_ret = fdt_get_uint32_prop_list(&hNode, "secpro", access_dt_ctrl->secpro_owner, size);
  }
  
  //ssc 
  fdt_ret |= fdt_get_prop_size(&hNode, "ssc", &size);   
  if((size > 0) && (fdt_ret == FDT_RETURNED_SUCCESS))
  {
    num_of_items = size / (4 * sizeof(uint32));
    access_dt_ctrl->ssc_count = num_of_items;
    pm_malloc(size, (void**)&access_dt_ctrl->ssc_owner);
    fdt_ret = fdt_get_uint32_prop_list(&hNode, "ssc", access_dt_ctrl->ssc_owner, size);
  }
  
  //invalid
  fdt_ret |= fdt_get_prop_size(&hNode, "invalid", &size);   
  if((size > 0) && (fdt_ret == FDT_RETURNED_SUCCESS))
  {
    num_of_items = size / (4 * sizeof(uint32));
    access_dt_ctrl->invalid_count = num_of_items;
    pm_malloc(size, (void**)&access_dt_ctrl->invalid_owner);
    fdt_ret = fdt_get_uint32_prop_list(&hNode, "invalid", access_dt_ctrl->invalid_owner, size);
  }
  
  parsed = TRUE;
  
  return access_dt_ctrl;
}


/*parse charger node*/
static void*
pm_dt_parse_charger_config(uint32 prop_id)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  static boolean parsed = FALSE;
  fdt_node_handle hNode = {0}; 
  int fdt_ret = FDT_RETURNED_SUCCESS;

  if(parsed)
  {
    return charger_dt_config;
  }

  pm_malloc(sizeof(pm_dt_charger_config), (void**)&charger_dt_config);

  fdt_ret = fdt_get_node_handle(&hNode, fdt_handle, node_str_arr[prop_id]);
  if(fdt_ret == FDT_RETURNED_SUCCESS)
  {
    err_flag |= pm_get_uint8_value( &hNode, "parallel-charger", &charger_dt_config->parallel_charger );
    err_flag |= pm_get_uint32_value( &hNode, "charger-pmic-index", &charger_dt_config->charger_pmic_index );
    err_flag |= pm_get_uint32_value( &hNode, "loader-dbc-threshold", &charger_dt_config->loader_dbc_threshold );
    err_flag |= pm_get_uint32_value( &hNode, "dbc-sdp-thd-inc", &charger_dt_config->dbc_sdp_thd_inc );
    err_flag |= pm_get_uint8_value( &hNode, "skip-loader-dbc", &charger_dt_config->skip_loader_dbc );
    err_flag |= pm_get_uint32_value( &hNode, "core-dbc-threshold", &charger_dt_config->core_dbc_threshold );
    err_flag |= pm_get_uint8_value( &hNode, "skip-core-dbc", &charger_dt_config->skip_core_dbc );

    err_flag |= pm_get_uint32_value( &hNode, "uv-oc-1s-threshold", &charger_dt_config->uv_oc_1s_threshold );
    err_flag |= pm_get_uint32_value( &hNode, "uv-oc-2s-threshold", &charger_dt_config->uv_oc_2s_threshold );

    err_flag |= pm_get_uint8_value( &hNode, "apply-ichg-fs", &charger_dt_config->apply_ichg_fs);
    err_flag |= pm_get_uint32_value( &hNode, "ichg-fs", &charger_dt_config->ichg_fs );

    err_flag |= pm_get_uint32_value( &hNode, "batt-2s-option", &charger_dt_config->batt_2s_option );


    err_flag |= pm_get_uint8_value( &hNode, "apply-too-hot-afp", &charger_dt_config->apply_too_hot_afp);
    err_flag |= pm_get_uint32_value( &hNode, "too-hot-afp-threshold", &charger_dt_config->too_hot_afp_threshold );

    err_flag |= pm_get_uint8_value( &hNode, "apply-too-cold-afp", &charger_dt_config->apply_too_cold_afp );
    err_flag |= pm_get_uint32_value( &hNode, "too-cold-afp-threshold", (uint32*)&charger_dt_config->too_cold_afp_threshold );


    err_flag |= pm_get_uint8_value( &hNode, "apply-boot-wo-batt", &charger_dt_config->apply_boot_wo_batt );
    err_flag |= pm_get_uint8_value( &hNode, "boot-wo-batt", &charger_dt_config->boot_wo_batt );
    err_flag |= pm_get_uint32_value( &hNode, "icl-boot-wo-batt", &charger_dt_config->icl_boot_wo_batt );

    err_flag |= pm_get_uint8_value( &hNode, "apply-float-voltage", &charger_dt_config->apply_float_voltage );
    err_flag |= pm_get_uint32_value( &hNode, "float-voltage-mv", &charger_dt_config->float_voltage_mv );

    err_flag |= pm_get_uint8_value( &hNode, "apply-pre-charge-current", &charger_dt_config->apply_pre_charge_current );
    err_flag |= pm_get_uint32_value( &hNode, "pre-charge-ma", &charger_dt_config->pre_charge_ma );

    err_flag |= pm_get_uint8_value( &hNode, "apply-fast-charge-current", &charger_dt_config->apply_fast_charge_current );
    err_flag |= pm_get_uint32_value( &hNode, "fast-charge-ma", &charger_dt_config->fast_charge_ma);

    err_flag |= pm_get_uint8_value( &hNode, "apply-icl", &charger_dt_config->apply_icl );
    err_flag |= pm_get_uint32_value( &hNode, "icl-ma", &charger_dt_config->icl_ma );

    err_flag |= pm_get_uint8_value( &hNode, "apply-float-charger-icl", &charger_dt_config->apply_float_charger_icl );
    err_flag |= pm_get_uint32_value( &hNode, "float-charger-icl-ma", &charger_dt_config->float_charger_icl_ma);

    err_flag |= pm_get_uint8_value( &hNode, "apply-vsysmin", &charger_dt_config->apply_vsysmin );
    err_flag |= pm_get_uint32_value( &hNode, "vsysmin", &charger_dt_config->vsysmin );

    err_flag |= pm_get_uint8_value( &hNode, "usb-suspend", &charger_dt_config->usb_suspend );

    err_flag |= pm_get_uint32_value( &hNode, "wls-usb-prior-swap", &charger_dt_config->wls_usb_prior_swap );
    err_flag |= pm_get_uint32_value( &hNode, "batt-detect-src", &charger_dt_config->batt_detect_src );
    err_flag |= pm_get_uint32_value( &hNode, "max-dbg-board-id", &charger_dt_config->max_dbg_board_id );
    err_flag |= pm_get_uint32_value( &hNode, "min-dbg-board-id", &charger_dt_config->min_dbg_board_id );

    err_flag |= pm_get_uint8_value( &hNode, "detect-jig-by-therm", &charger_dt_config->detect_jig_by_therm );
    err_flag |= pm_get_uint32_value( &hNode, "max-therm", &charger_dt_config->max_therm );
    err_flag |= pm_get_uint32_value( &hNode, "min-therm", &charger_dt_config->min_therm );
    err_flag |= pm_get_uint32_value( &hNode, "jig-icl-ma", &charger_dt_config->jig_icl_ma );
    err_flag |= pm_get_uint32_value( &hNode, "uvp-recover-delay", &charger_dt_config->uvp_recover_delay );

    err_flag |= pm_get_uint8_value( &hNode, "ignore-temp-in-dbc", &charger_dt_config->ignore_temp_in_dbc );

    err_flag |= pm_get_uint32_value( &hNode, "batt-therm-pull-up", &charger_dt_config->batt_therm_pull_up);

    err_flag |= pm_get_uint8_value( &hNode, "ibat-via-ext-sense", &charger_dt_config->ibat_via_ext_sense );
    err_flag |= pm_get_uint32_value( &hNode, "ext-rsns-adc-scale", &charger_dt_config->ext_rsns_adc_scale);

    
    err_flag |= pm_get_uint32_value( &hNode, "vbat-thd-rtc-pon", &charger_dt_config->vbat_thd_rtc_pon);
    err_flag |= pm_get_uint32_value( &hNode, "vsys-min-recover-mv", &charger_dt_config->vsys_min_recover_mv);
    err_flag |= pm_get_uint32_value( &hNode, "vflt-recover-mv", &charger_dt_config->vflt_recover_mv);

    pm_dt_error_chk( err_flag, "charger" );

    parsed = TRUE;
  }
  else
  {
    pm_free((void**)&charger_dt_config);
  }

  return charger_dt_config;
}


/*parse mgpi node*/
static void*
pm_dt_parse_mgpi_config(uint32 prop_id)
{
  static boolean parsed = FALSE;
  fdt_node_handle hNode= {0};
  int fdt_ret = FDT_RETURNED_SUCCESS;
  uint32 size = 0;  

  if(parsed)
  {
    return mgpi_dt_config;
  }

  pm_malloc(sizeof(pm_dt_mgpi_config), (void**)&mgpi_dt_config);

  fdt_ret = fdt_get_node_handle(&hNode, fdt_handle, node_str_arr[prop_id]);
  
  if(fdt_ret != FDT_RETURNED_SUCCESS) 
  {
    parsed = TRUE;
    return mgpi_dt_config;  
  }
  
  fdt_ret = fdt_get_prop_size(&hNode, "port-cfg", &size);
  
  if((size > 0) && (fdt_ret == FDT_RETURNED_SUCCESS))
  {
    mgpi_dt_config->cfg_count = size / (10 * sizeof(uint32));
    
    pm_malloc(size, (void**)&mgpi_dt_config->cfg_data);
    
    fdt_ret = fdt_get_uint32_prop_list(&hNode, "port-cfg", mgpi_dt_config->cfg_data, size); 
  }

  parsed = TRUE;

  return mgpi_dt_config;
}


/*parse pvc node*/
static void*
pm_dt_parse_pvc_config(uint32 prop_id)
{
  int fdt_ret = FDT_RETURNED_SUCCESS; 
  static boolean parsed = FALSE;
  fdt_node_handle hNode = {0};
  char node_buf[DTB_LINE_BUF_SIZE] = {0};

  int i = 0, i_addr_cfg = 0;
  uint32 count = 0, addr_cfg_count = 0, size = 0, addr_size = 0;
  uint32 *ptr = NULL, *pt_addr_cfg = NULL;
  char *walk = NULL;
  uint32 *walk_addr_cfg = NULL;
  
  if(parsed)
  {
    return pvc_dt_config;
  }
  
  pm_malloc(sizeof(pm_dt_pvc_config), (void**)&pvc_dt_config);

  fdt_ret = fdt_get_node_handle(&hNode, fdt_handle, node_str_arr[prop_id]);
  fdt_ret |= fdt_get_count_of_subnodes(&hNode, &count);  
  
  if((fdt_ret == FDT_RETURNED_SUCCESS) && (count > 0) )
  {
    pvc_dt_config->node_count = count;  
  }
  else
  {
    return pvc_dt_config;
  }  

  pm_malloc(count * sizeof(pm_pvc_node_type), (void**)&pvc_dt_config->pvc_node);
  
  pm_malloc(count * sizeof(uint32), (void**)&ptr);
  fdt_ret = fdt_get_size_of_subnode_names(&hNode, ptr, count);
  CORE_VERIFY_PTR(ptr);

  for(i = 0, size = 0; i < count ; i++)
  {
    size += ptr[i]; 
  }

  if(NULL != ptr)
  {
    pm_free((void**)&ptr);
  }

  pm_malloc(size, (void**)&ptr);
  walk = (char*)ptr;
  fdt_ret |= fdt_get_subnode_names(&hNode, ptr, size); 

  if(fdt_ret == FDT_RETURNED_SUCCESS)
  {
    for(i = 0; i < count; i++)
    {
      snprintf(node_buf, DTB_LINE_BUF_SIZE,"%s/%s", node_str_arr[prop_id], walk);
      fdt_ret = fdt_get_node_handle(&hNode, fdt_handle, node_buf);
      if(fdt_ret == FDT_RETURNED_SUCCESS)
      {
        pm_get_uint32_value( &hNode, "pvc-port-id", &(pvc_dt_config->pvc_node[i].pvc_port_id) );
        pm_get_uint32_value( &hNode, "spmi-prioriety", &(pvc_dt_config->pvc_node[i].spmi_prioriety) );
      }    
    
      fdt_ret = fdt_get_prop_size(&hNode, "addr-cfg", &addr_size);  
      if((addr_size > 0) && (fdt_ret == FDT_RETURNED_SUCCESS))
      {
        addr_cfg_count = addr_size / (sizeof(int32) * 2);
        pvc_dt_config->pvc_node[i].addr_cfg_count = addr_cfg_count;
        
        pm_malloc(sizeof(SpmiCfg_Ppid) * addr_cfg_count,(void**)&(pvc_dt_config->pvc_node[i].addr_cfg));
        pm_malloc(addr_size, (void**)&pt_addr_cfg);
        
        fdt_ret = fdt_get_uint32_prop_list( &hNode, "addr-cfg", pt_addr_cfg, addr_size );
        if(fdt_ret == FDT_RETURNED_SUCCESS)
        {
          walk_addr_cfg = pt_addr_cfg;      
          for (i_addr_cfg = 0; i_addr_cfg < addr_cfg_count ; i_addr_cfg++) 
          {
            pvc_dt_config->pvc_node[i].addr_cfg[i_addr_cfg].slaveId = *walk_addr_cfg++;
            pvc_dt_config->pvc_node[i].addr_cfg[i_addr_cfg].address = *walk_addr_cfg++;
          }  
        }   
        
        if(pt_addr_cfg)
        {
          pm_free((void**)&pt_addr_cfg);
        }             
      }
    
      walk += strlen(walk) + 1;
    }         
  }

  if(NULL != ptr)
  {
    pm_free((void**)&ptr);
  }

  parsed = TRUE;

  return pvc_dt_config;
}

/*parse CAMERA node*/
static void*
pm_dt_parse_camera_config(uint32 prop_id)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  static boolean parsed = FALSE;
  fdt_node_handle hNode = {0};
  int fdt_ret = FDT_RETURNED_SUCCESS;
  uint32 size = 0;

  if(parsed)
  {
    return camera_dt_config;
  }

  pm_malloc(sizeof(pm_dt_camera_config), (void**)&camera_dt_config);
  
  fdt_ret = fdt_get_node_handle(&hNode, fdt_handle, node_str_arr[prop_id]);
  if(fdt_ret == FDT_RETURNED_SUCCESS)
  {
    fdt_ret = fdt_get_prop_size(&hNode, "rst-signal", &size);
    size = size < (2 * sizeof (uint32)) ? size : (2 * sizeof (uint32));

    fdt_ret = fdt_get_uint32_prop_list(&hNode, "rst-signal", camera_dt_config->reset_gpio, size);
    err_flag = fdt_ret;
    pm_dt_error_chk(err_flag, "camera-gpio");
    parsed = TRUE;
  }
  else
  {
    pm_free((void**)&camera_dt_config);
  }

  return camera_dt_config;
}

/*parse psi node*/
static void*
pm_dt_parse_psi_seq_config(uint32 prop_id)
{
  static boolean parsed = FALSE;
  fdt_node_handle hNode = {0};
  char node_buf[DTB_LINE_BUF_SIZE] = {0}; 
  int fdt_ret = FDT_RETURNED_SUCCESS;
  uint32 seq_size = 0;
  uint32 clogic_size = 0;
  if(parsed)
  {
    return psi_dt_config;
  }

  pm_malloc(sizeof(pm_dt_psi_config), (void**)&psi_dt_config);
  snprintf(node_buf, DTB_LINE_BUF_SIZE, "%s/pm-psi-variant", node_str_arr[prop_id]);
  fdt_ret = fdt_get_node_handle(&hNode, fdt_handle, node_buf);
  if(fdt_ret == FDT_RETURNED_SUCCESS)
  {
    pm_get_uint8_value( &hNode, "major", &psi_dt_config->psi_variant_major);
    pm_get_uint16_value( &hNode, "minor", &psi_dt_config->psi_variant_minor);
  }

  snprintf(node_buf, DTB_LINE_BUF_SIZE, "%s/pm-psi-seq", node_str_arr[prop_id]);
  fdt_ret = fdt_get_node_handle(&hNode, fdt_handle, node_buf);
  if(fdt_ret == FDT_RETURNED_SUCCESS)
  {
    pm_get_uint32_value( &hNode, "opsi-settings-version", &psi_dt_config->version );
    
    fdt_ret = fdt_get_prop_size(&hNode, "post-device-opsi", &seq_size);

    if((seq_size > 0) && (fdt_ret == FDT_RETURNED_SUCCESS))
    {
      psi_dt_config->settings_count = seq_size / (PM_OEM_PSI_SEQ_STEP_LENGTH * sizeof(uint32)); //divide by 9 since there are 9 members per entry
      pm_malloc(seq_size, (void**)&psi_dt_config->opsi_seq);    
      fdt_ret = fdt_get_uint32_prop_list(&hNode, "post-device-opsi", psi_dt_config->opsi_seq, seq_size); 
    }
    
    // get clogic Values
    pm_malloc(sizeof(pm_dt_psi_cond_config), (void**)&psi_dt_config->clogic);
    snprintf(node_buf, DTB_LINE_BUF_SIZE, "%s/pm-psi-clogic", node_str_arr[prop_id]);
    fdt_ret = fdt_get_node_handle(&hNode, fdt_handle, node_buf);
    if(fdt_ret == FDT_RETURNED_SUCCESS)
    {
      pm_get_uint32_value( &hNode, "clogic-version", &psi_dt_config->clogic->clogic_version );
      fdt_ret = fdt_get_prop_size(&hNode, "clogic-data", &clogic_size); 
      psi_dt_config->clogic->clogic_count = clogic_size / (PM_OEM_PSI_CLOGIC_STEP_LENGTH * sizeof(uint32));
      if(fdt_ret == FDT_RETURNED_SUCCESS)
      {
        pm_malloc(clogic_size, (void**)&psi_dt_config->clogic->clogic_data);
        fdt_ret = fdt_get_uint32_prop_list(&hNode, "clogic-data", psi_dt_config->clogic->clogic_data, clogic_size); 
      }
    }

    parsed = TRUE;
  }
  else
  {
    pm_free((void**)&psi_dt_config);
  }

  return psi_dt_config;
}

void *
pm_dt_get_node( pmic_dt_node_type node )
{
  void * node_prop = NULL;

  CORE_VERIFY(PM_ERR_FLAG_SUCCESS == pm_target_information_dt_init());

  switch( node )
  {
    case PMIC_DT_NODE_PM_SW_CONFIG:       
      node_prop = (void*)pm_dt_parse_sw_config( node );
      break;

    case PMIC_DT_NODE_OPSI_CONFIG:       
      node_prop = (void*)pm_dt_parse_psi_seq_config( node );
      break;

    case PMIC_DT_NODE_PM_PON:
      node_prop = (void*)pm_dt_parse_pon_config( node ); 
      break;

    case PMIC_DT_NODE_PM_CHARGER:
      node_prop = (void*)pm_dt_parse_charger_config( node );
      break;

    case PMIC_DT_NODE_PM_HAPTICS: 
      node_prop = (void*)pm_dt_parse_haptics_config( node );
      break;

    case PMIC_DT_NODE_PM_DISPLAY: 
      node_prop = (void*)pm_dt_parse_display_config( node );
      break;

    case PMIC_DT_NODE_PM_CAMERA:   
      node_prop = (void*)pm_dt_parse_camera_config( node );
      break;

    case PMIC_DT_NODE_ARB_ACCESS:      
      node_prop = (void*)pm_dt_parse_access_ctrl_config( node );
      break;

    case PMIC_DT_NODE_ARB_MGPI:      
      node_prop = (void*)pm_dt_parse_mgpi_config( node );
      break;

    case PMIC_DT_NODE_ARB_PVC:
      node_prop = (void*)pm_dt_parse_pvc_config( node );
      break;

    default:
     break;
  }
  
  return node_prop;      
}

