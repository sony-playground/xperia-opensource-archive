/*===========================================================================

            GLink SMEM transport Configuration Structures

=============================================================================

  @file
    xport_smem_config.c

    Contains structures to be used in Glink SMEM trasnport configuration.

  Copyright (c) 2014 - 2015,2017-2022 Qualcomm Technologies, Inc.
  All rights reserved.
  Qualcomm Confidential and Proprietary
===========================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/GLinkLib/xport_smem/src/xport_smem_config.c#1 $

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
10/15/18   mad     Removed MPSS edge 
05/11/15   an      QoS support
02/13/15   bc      Decrease the fifo size due to lack of space
01/14/15   bc      Update outgoing interrupt
01/13/15   bc      Update more processors
06/17/14   an      Initial version
===========================================================================*/

/*===========================================================================
                        INCLUDE FILES
===========================================================================*/
#include "xport_smem_config.h"
#include "xport_smem_qos_generic.h"
#include <Protocol/EFIIPCC.h>
#include <Library/DTBExtnUEFILib.h>

/*===========================================================================
                    CONSTANT / MACRO DECLARATIONS
===========================================================================*/
#define XPORT_SMEM_DT_RET_CHECK(ret)                                   \
  {                                                               \
    if (ret) {                                                    \
      DEBUG((EFI_D_ERROR, "xport-smem DT parse return = %d\n", ret));                 \
      return ret;                                                 \
    }                                                             \
  }
  
#define XPORT_SMEM_DT_SUCCESS 0

/*===========================================================================
                    Type declarations
===========================================================================*/
/* Structure of xport-smem-config items in Device-Tree database */
typedef struct _xport_smem_dt_config_type
{
  smem_host_type remote_host;           /* Remote host ID          */
  uint32 fifo_size;                     /* Tx FIFO size            */
  uint32 mtu_size;                      /* Tx MTU size             */
  os_ipc_intr_type irq_out;             /* Outgoing interrupt      */
  uint32 default_qos;                   /* Whether this uses the default QoS interface (always true) */
  uint32 custom_fifo_alloc;             /* whether custom fifo allocation routine is used */
  uint32 clear_interrupt;               /* Whether this edge uses an explicit interrupt clear routine */
} xport_smem_dt_config_type;  

/*===========================================================================
                    Function declarations
===========================================================================*/
static const char* glink_host_name_from_smem_id(smem_host_type id);

/*===========================================================================
                        DATA DECLARATIONS
===========================================================================*/
static glink_transport_qos_if_type xport_smem_qos_config = 
{
  /** Provides maximum data rate (tokens/sec) associated with transport. */
  20000,
  /** Provides data rate achievable by the transport for given request. */
  xport_smem_get_req_rate_generic,
  /** Allocates context structure to use by transport servicing given QoS request. */
  xport_smem_alloc_req_ctx_generic,
  /** Frees context structure used by transport servicing given QoS request. */
  xport_smem_free_req_ctx_generic,
  /** Starts QoS mode. */
  xport_smem_start_req_generic,
  /** Stops QoS mode. */
  xport_smem_stop_req_generic,
  /** Provides ramp up time in microseconds. */
  xport_smem_get_ramp_time_generic
};

xport_smem_config_type *xport_smem_config = NULL;
uint32 xport_smem_config_num = 0;
const smem_host_type xport_smem_this_host = SMEM_APPS;

xport_smem_config_type* xport_smem_get_config(uint32 ind)
{
  if (ind >= xport_smem_config_num)
  {
    return NULL;
  }

  return &xport_smem_config[ind];
}

/*===========================================================================
FUNCTION      xport_smem_config_init
===========================================================================*/
/**

  Initializes SMEM transport configuration by reading from DeviceTree database.
  Must be called before any other operations are done.

  @return     Returns error code.

  @sideeffects  None.
*/
/*=========================================================================*/
int xport_smem_config_init(void)
{
  INT32 ret = XPORT_SMEM_DT_SUCCESS;
  UINT32 n_cfg = 0;
  UINT32 idx = 0;
  EFI_DTB_EXTN_PROTOCOL *dtb_protocol = NULL;
  EFI_STATUS status = EFI_DEVICE_ERROR;
  FdtNodeHandle xport_smem_dt_node_hdl;
  FdtNodeHandle *cache = NULL;
  xport_smem_dt_config_type dt_cfg;
    
  status = gBS->LocateProtocol(&gEfiDtbExtnProtocolGuid, NULL,(VOID **)&dtb_protocol);
  if (EFI_ERROR(status)) 
  {
    DEBUG((EFI_D_ERROR, "%s: Locate DTB failed with error %r \n", __FUNCTION__, status));
    return -1;
  }
  ret = dtb_protocol->FdtGetNodeHandle(&xport_smem_dt_node_hdl, "/sw/glink/xport-smem-config");
  XPORT_SMEM_DT_RET_CHECK(ret);
  ret = dtb_protocol->FdtGetCountOfSubnodes(&xport_smem_dt_node_hdl, &n_cfg);
  XPORT_SMEM_DT_RET_CHECK(ret);
  
  if(n_cfg > 0)
	cache = glink_os_calloc(n_cfg * sizeof(FdtNodeHandle));
  if(!cache)
	  return -1;
  
  ret = dtb_protocol->FdtGetCacheOfSubnodes(&xport_smem_dt_node_hdl, cache, (UINT32)n_cfg);
  XPORT_SMEM_DT_RET_CHECK(ret);
  xport_smem_config = glink_os_calloc(n_cfg * sizeof(xport_smem_config_type));
  if(!xport_smem_config)
  {
	glink_os_free(cache);
	return -1;
  }
      
  for(idx = 0; idx < n_cfg; idx++)
  {
	memset(&dt_cfg, 0, sizeof(dt_cfg));
	ret = dtb_protocol->FdtGetPropValuesOfNode(&cache[idx], "wwwwwwww", (VOID*)&(dt_cfg), sizeof(dt_cfg));
	XPORT_SMEM_DT_RET_CHECK(ret);
	
    xport_smem_config[idx].remote_ss = glink_host_name_from_smem_id(dt_cfg.remote_host);
	if(!xport_smem_config[idx].remote_ss) 
	{
	  glink_os_free(cache);
	  glink_os_free(xport_smem_config);
	  return -1;
	}
	xport_smem_config[idx].remote_host = dt_cfg.remote_host;
	xport_smem_config[idx].fifo_size = dt_cfg.fifo_size;
	xport_smem_config[idx].mtu_size = dt_cfg.mtu_size;
	xport_smem_config[idx].irq_out.client = dt_cfg.irq_out.client;
	xport_smem_config[idx].irq_out.signal = dt_cfg.irq_out.signal;
	
	if(!dt_cfg.default_qos)/* We only support default QoS */
	{
	  glink_os_free(cache);
	  glink_os_free(xport_smem_config);
	  return -1;
	}
	xport_smem_config[idx].qos_api = &xport_smem_qos_config;
	
	if(!dt_cfg.custom_fifo_alloc)
	{
	  xport_smem_config[idx].alloc_fifo = NULL; /* No custom FIFO alloc is needed. So use default */
	}
  
    if(!dt_cfg.clear_interrupt)
	{
	  xport_smem_config[idx].clear_interrupt = NULL; /* No interrupt clear routine is needed */
	}
  }
  xport_smem_config_num = n_cfg;
  
  glink_os_free(cache);
  return 0;
}

/*===========================================================================
FUNCTION      glink_host_name_from_smem_id
===========================================================================*/
/**
  Return the host name string (mostly used in debug logs), given the SMEM ID.
  
  @param[in]  id   The SMEM ID that needs to be translated to string.
  
  @return     Returns string constant corresponding to remote subsystem name.

  @sideeffects  None.
*/
/*=========================================================================*/
static const char* glink_host_name_from_smem_id(smem_host_type id)
{
	switch(id)
	{
	case SMEM_APPS:
	  return "apss";
	case SMEM_MODEM:
	  return "mpss";
	case SMEM_ADSP:
	  return "lpass";
	case SMEM_SSC:
	  return "dsps";
	case SMEM_WCN:
	  return "wcnss";
	case SMEM_CDSP:
	  return "cdsp";
	case SMEM_RPM:
	  return "rpm";
	case SMEM_TZ:
	  return "tz";
	case SMEM_SPSS:
	  return "spss";
	case SMEM_NPU:
	  return "npu";
	case SMEM_WPSS:
	  return "wpss";
	default:
	  return NULL;
	}
}