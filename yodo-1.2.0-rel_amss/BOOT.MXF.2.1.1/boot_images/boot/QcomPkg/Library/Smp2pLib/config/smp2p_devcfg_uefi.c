/*===========================================================================

                     SMP2P DEVICE CONFIGURATION

        This file provides the device configuration for SMP2P

  ---------------------------------------------------------------------------
  Copyright (c) 2018, 2020-2022 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ---------------------------------------------------------------------------
===========================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header:

when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/26/17   jlg     Established settings interface
===========================================================================*/

/*===========================================================================
                          INCLUDE FILES
===========================================================================*/
#include <Uefi.h>
#include <Protocol/EFIDtbExtn.h>
#include <Library/UefiBootServicesTableLib.h>
#include "IPCC.h"
#include "smem_type.h"
#include "smp2p_settings.h"
#include "smp2p_os_common.h"
#include <Library/DTBDefs.h>
#include <Protocol/EFIDtbExtn.h>


/*===========================================================================
                    CONSTANT / MACRO DECLARATIONS
===========================================================================*/

#define SMP2P_DT_RET_CHECK(ret)                                   \
  {                                                               \
    if (ret) {                                                    \
      DEBUG((EFI_D_ERROR, "smp2p DT parse return = %d\n", ret));                 \
      return ret;                                                 \
    }                                                             \
  }

#define SMP2P_DT_SUCCESS 0
/*===========================================================================
                      GLOBAL DATA DEFINATION
===========================================================================*/
/** Local processor info */
smp2p_proc_info_type smp2p_devcfg_proc_info = 
{ 
  /** This host name */
  "apps",
  
  /** This host SMEM ID */
  SMEM_APPS,
  
  /** Feature flags supported */
  SMP2P_FFLAGS_SSR_HANDSHAKE,
  
  /** Max number of entries */
  16
};

smp2p_interrupt_info_type *smp2p_devcfg_interrupt_info = NULL;
/** Interrupt info for connected subsystems, to be obtained from Settings device-tree */


/* =================
Parse SMP2P settings from SOC-specific Device-Tree Database.
========================*/

int smp2p_dt_parse(void)
{
  INT32 ret = SMP2P_DT_SUCCESS;
  UINT32 n_intr = 0;
  UINT32 idx = 0;
  EFI_DTB_EXTN_PROTOCOL *dtb_protocol = NULL;
  EFI_STATUS status = EFI_DEVICE_ERROR;
  FdtNodeHandle smp2p_dt_node_hdl, smp2p_intr_node_hdl;
  FdtNodeHandle *cache = NULL;
  
  status = gBS->LocateProtocol(&gEfiDtbExtnProtocolGuid, NULL,(VOID **)&dtb_protocol);
  if (EFI_ERROR(status)) 
  {
    DEBUG((EFI_D_ERROR, "%s: Locate DTB failed with error %r \n", __FUNCTION__, status));
    return -1;
  }
  ret = dtb_protocol->FdtGetNodeHandle(&smp2p_dt_node_hdl, "/sw/smp2p");
  SMP2P_DT_RET_CHECK(ret);
  ret = dtb_protocol->FdtGetUint32Prop(&smp2p_dt_node_hdl,"fflags",&(smp2p_devcfg_proc_info.fflags));
  SMP2P_DT_RET_CHECK(ret);
  ret = dtb_protocol->FdtGetUint32Prop(&smp2p_dt_node_hdl,"max-entries",&(smp2p_devcfg_proc_info.max_entries));
  SMP2P_DT_RET_CHECK(ret);
  
  ret = dtb_protocol->FdtGetNodeHandle(&smp2p_intr_node_hdl, "/sw/smp2p/smp2p-interrupts");
  SMP2P_DT_RET_CHECK(ret); 
  ret = dtb_protocol->FdtGetCountOfSubnodes(&smp2p_intr_node_hdl, &n_intr);
  SMP2P_DT_RET_CHECK(ret);
  
  if(n_intr > 0)
	cache = smp2p_os_malloc(n_intr * sizeof(FdtNodeHandle));
  if(!cache)
	  return -1;
  
  ret = dtb_protocol->FdtGetCacheOfSubnodes(&smp2p_intr_node_hdl, cache, (UINT32)n_intr);
  SMP2P_DT_RET_CHECK(ret);
  smp2p_devcfg_interrupt_info = smp2p_os_malloc(n_intr * sizeof(smp2p_interrupt_info_type));
  if(!smp2p_devcfg_interrupt_info)
  {
	smp2p_os_free(cache);
	return -1;
  }
  memset(smp2p_devcfg_interrupt_info,0,n_intr * sizeof(smp2p_interrupt_info_type));
    
  for(idx = 0; idx < n_intr; idx++)
  {
	ret = dtb_protocol->FdtGetUint32Prop(&cache[idx],"dest",&(smp2p_devcfg_interrupt_info[idx].dest));
	SMP2P_DT_RET_CHECK(ret);
	ret = dtb_protocol->FdtGetUint32Prop(&cache[idx],"proc",&(smp2p_devcfg_interrupt_info[idx].processor));
	SMP2P_DT_RET_CHECK(ret);
	ret = dtb_protocol->FdtGetUint32Prop(&cache[idx],"irq",&(smp2p_devcfg_interrupt_info[idx].irq));
	SMP2P_DT_RET_CHECK(ret);
  }
  
  smp2p_os_free(cache);
  return 0;
}