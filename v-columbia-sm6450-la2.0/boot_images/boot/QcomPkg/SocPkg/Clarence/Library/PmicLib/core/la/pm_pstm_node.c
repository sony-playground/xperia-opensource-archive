/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                  PMIC Startup Services

GENERAL DESCRIPTION
  This file contains initialization functions and corresponding variable
  declarations to support interaction with the Qualcomm Pmic chips.

  Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     		what, where, why
--------   ---     		----------------------------------------------------------
11/08/22   udumpala      New File
===========================================================================*/
/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include "npa_resource.h"
#include "npa_resource_common.h"
#include "DALSys.h"
#include "pm_log_utils.h"
#include "pm_prm_device.h"
#include "pmapp_npa.h"
#include "pm_prm_stubs.h"
#include "pm_rpmh.h"
#include "cmd_db.h"

/*===========================================================================

                LOCAL FUNCTION PROTOTYPES

===========================================================================*/

npa_resource_state
pm_pstm_driver_function (npa_resource *resource, npa_client_handle  client, npa_resource_state state);

/*===========================================================================

                VARIABLES DEFINITIONS

===========================================================================*/

extern boolean bPMICStub;

pm_pstm_rsrc_data_type pm_pstm_data_sd_mmc_vdd =
{    
  .cmd_db_name = "vrm.sd",
};

pm_pstm_rsrc_data_type pm_pstm_data_sd_mmc_vdd_px2 =
{    
  .cmd_db_name = "vrm.px2",
};

npa_resource_definition pm_pstm_rsrc_sd_mmc_vdd = 
{
  .name = PMIC_NPA_GROUP_ID_SD_MMC_VDD_PSTM,
  .units = "mV", 
  .max = PMIC_NPA_MODE_ID_GENERIC_MAX-1, 
  .plugin = &npa_max_plugin,
  .attributes = (NPA_RESOURCE_DEFAULT |  
                 NPA_RESOURCE_DRIVER_UNCONDITIONAL_FIRST), 
  .data = &pm_pstm_data_sd_mmc_vdd,    
};

npa_resource_definition pm_pstm_rsrc_sd_mmc_vdd_px2 = 
{
  .name = PMIC_NPA_GROUP_ID_SD_MMC_VDD_PX2_PSTM,
  .units = "mV", 
  .max = PMIC_NPA_MODE_ID_GENERIC_MAX-1, 
  .plugin = &npa_max_plugin,
  .attributes = (NPA_RESOURCE_DEFAULT |  
                 NPA_RESOURCE_DRIVER_UNCONDITIONAL_FIRST), 
  .data = &pm_pstm_data_sd_mmc_vdd_px2,    
};

npa_node_definition pm_pstm_node_sd_mmc_vdd = 
{
  .name = PMIC_NPA_CLIENT_NODE_SD_MMC_VDD_PSTM,
  .driver_fcn = pm_pstm_driver_function, 
  .attributes = NPA_NODE_DEFAULT,
  .data = NULL, 
  .dependency_count = 0, 
  .dependencies = NULL, 
  .resource_count = 1, 
  .resources = &pm_pstm_rsrc_sd_mmc_vdd,
};

npa_node_definition pm_pstm_node_sd_mmc_vdd_px2 = 
{
  .name = PMIC_NPA_CLIENT_NODE_SD_MMC_VDD_PX2_PSTM,
  .driver_fcn = pm_pstm_driver_function, 
  .attributes = NPA_NODE_DEFAULT,
  .data = NULL, 
  .dependency_count = 0, 
  .dependencies = NULL, 
  .resource_count = 1, 
  .resources = &pm_pstm_rsrc_sd_mmc_vdd_px2,
};

void pm_pstm_nas_cb (void *npa_rsrc);

npa_resource_state
pm_pstm_driver_function (npa_resource *resource, npa_client_handle client, npa_resource_state state)
{
  pm_pstm_rsrc_data_type  *rsrc_data = NULL;
  pm_rpmh_data_type       *rpmh_data = NULL; 
  uint32                  msg_id     = 0;
  boolean                 is_nas_req = FALSE;
  rpmh_command_set_t      active_set; 
  rpmh_command_set_t      sleep_set;
  
  rsrc_data = (pm_pstm_rsrc_data_type*)resource->definition->data;
  rpmh_data = &rsrc_data->rpmh_data;

  DALSYS_memset(&active_set, 0, sizeof(rpmh_command_set_t));
  DALSYS_memset(&sleep_set,  0, sizeof(rpmh_command_set_t));

  if(npa_request_has_attribute(client, NPA_REQUEST_NEXT_AWAKE)) 
  {
    is_nas_req = TRUE;
    
    rpmh_data->nas_req_cnt += 1; 
    
    npa_notify_next_awake(pm_pstm_nas_cb, (void *)resource);
  }

  if(rpmh_data->nas_req_cnt > 0 &&
     is_nas_req != TRUE)
  {
    PM_LOG_MSG_INFO("Imm Req before NAS CB for %s by %s", 
                        client->resource_name, 
                        resource->definition->name);

    /* Make nas request count zero for nas cb to ignore this rsrc */ 
    rpmh_data->nas_req_cnt = 0;
  }

  if(client->type == NPA_CLIENT_REQUIRED ||
     client->type == NPA_CLIENT_SUPPRESSIBLE)
  {   
    rpmh_data->active_set   = resource->request_state;
    rpmh_data->sleep_set    = NPA_RESOURCE_REQUIRED_REQUEST(resource);
    rpmh_data->dirty_active = TRUE;
    rpmh_data->dirty_sleep  = TRUE;
  }
  else 
  {
    //Return state during initialization call
    return state;
  }
  
  pm_rpmh_create_cmd_set(&active_set, &sleep_set, rpmh_data, is_nas_req);
                         
  pm_rpmh_post_set(&active_set, &sleep_set, rpmh_data, &msg_id, is_nas_req);

  if (!(msg_id == 0 || 
      npa_request_has_attribute(client, NPA_REQUEST_FIRE_AND_FORGET)))
  {
    pm_rpmh_barrier_single(msg_id);
  }

  PM_LOG_MSG_INFO("Done Rsrc=%a, Client=%a state=%d, Type=0x%x, attr=0x%x",
                      client->resource_name, client->name, state, 
                      client->type, client->request_attr);
  
return state;
}

void
pm_pstm_node_init (void)
{
  pm_pstm_data_sd_mmc_vdd.rpmh_data.address = cmd_db_query_addr(pm_pstm_data_sd_mmc_vdd.cmd_db_name); //cmd_db_query_addr("vrm.sd");
  pm_pstm_data_sd_mmc_vdd_px2.rpmh_data.address = cmd_db_query_addr(pm_pstm_data_sd_mmc_vdd_px2.cmd_db_name); //= cmd_db_query_addr("vrm.px2");
  
  if (bPMICStub == TRUE)
  {
    npa_stub_resource(pm_pstm_rsrc_sd_mmc_vdd.name);
  }
  else
  {
    if(pm_pstm_data_sd_mmc_vdd.rpmh_data.address == 0)
    {
      PM_LOG_MSG_ERR_FATAL("Unable to get VRM address for SD_MMC_VDD_PSTM");
    }
    npa_define_node(&pm_pstm_node_sd_mmc_vdd, NULL, NULL);
    
    if(pm_pstm_data_sd_mmc_vdd_px2.rpmh_data.address == 0)
    {
      PM_LOG_MSG_ERR_FATAL("Unable to get VRM address for SD_MMC_VDD_PX2_PSTM");
    }
    npa_define_node(&pm_pstm_node_sd_mmc_vdd_px2, NULL, NULL);
  }
}

void pm_pstm_nas_cb(void *npa_rsrc)
{
  npa_resource            *resource    = NULL; 
  pm_pstm_rsrc_data_type  *rsrc_data   = NULL;
  uint32                 msg_id      = 0;
  rpmh_command_set_t     active_set; 
  rpmh_command_set_t     sleep_set;
 
  DALSYS_memset(&active_set, 0, sizeof(rpmh_command_set_t));
  DALSYS_memset(&sleep_set,  0, sizeof(rpmh_command_set_t));
  
  if (npa_rsrc == NULL)
  {
    PM_LOG_MSG_ERR_FATAL("Invalid Resource in NAS Callback");
  }
  
  resource = (npa_resource*)npa_rsrc;
  
  /* Lock resource to protect against parallel on-going immediate reqeust */
  npa_resource_lock(resource);
  
  rsrc_data=(pm_pstm_rsrc_data_type*)resource->definition->data;
 
  if (rsrc_data->rpmh_data.nas_req_cnt == 0)
  {
    /* Un-lock Resource */
    npa_resource_unlock(resource);
    return; 
  }
  
  rsrc_data->rpmh_data.nas_req_cnt = 0; 

  rsrc_data->rpmh_data.active_set   = resource->active_state;
  rsrc_data->rpmh_data.sleep_set    = NPA_RESOURCE_REQUIRED_REQUEST(resource);
  rsrc_data->rpmh_data.dirty_active = TRUE;
  rsrc_data->rpmh_data.dirty_sleep  = TRUE;
  
  pm_rpmh_create_cmd_set(&active_set, &sleep_set, &rsrc_data->rpmh_data, 0);
  
  pm_rpmh_post_set(&active_set, &sleep_set, &rsrc_data->rpmh_data, &msg_id, 0);

  PM_LOG_MSG_INFO("Done NAS_CB: rsrc=%s, AS=%d, SS=%d, msg_id=%d", 
                      resource->definition->name,
                      rsrc_data->rpmh_data.active_set,
                      rsrc_data->rpmh_data.sleep_set, msg_id); 

  /* Un-lock Resource */  
  npa_resource_unlock(resource);                  
                   
  return;
}