/**---------------------------------------------------------------------------
 *   @file        usb4_cm.c
 *
 *   @brief   Implementation for a Connection Manager
 *
 *   Copyright (c) 2019-2021 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/

#include <Usb4Utils.h>
#include <stdint.h>
#include <Protocol/EFIUsb4Config.h>
#include "usb4_cm.h"
#include "Usb4Log.h"   // Logging utilities
#include "usb4_mem.h"
#include "usb4_platform_target.h"
#include "usb4_gcc.h"

// #include "VVHAL_usb4_timer.h"
// #include "VVHAL_usb4_utils.h"
// #include <new>

/*----------------------------------------------------------------------------
 * Global data structures
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Local variables
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * usb4_cm_ctx_t Class methods
 *--------------------------------------------------------------------------*/

// TODO: AC add this to main USB4
int Usb4CmInit(usb4_cm_ctx_t* usb4_cm_ctx, UINT32 coreId)
{
    UINT32 i;

    if (TRUE == usb4_cm_ctx->m_bInitialized)
    {
        // exit gracefully on re-init!
        return 0;
    }

    usb4_cm_ctx->m_pHI_Base = 0;
    // m_HIA(&m_logger); // Refer to invocation of Usb4HiaInit()
    // m_control(&m_logger, m_HIA), // Replaced with Usb4CtrlIfaceInit() below
    usb4_cm_ctx->m_router_index = 0;
    // m_routers(),
    // m_interdomainData.m_UUID(),
    usb4_cm_ctx->m_pHotplug = NULL;
    // m_localUUID(),
    // m_interdomainData(),
    // m_path_manager(),
    usb4_cm_ctx->m_bUsePollingForControlPackets = FALSE;
    usb4_cm_ctx->m_bCmTreadLocked = FALSE;
    usb4_cm_ctx->m_domainTmuMode = USB4_TMU_MODE_NOT_SET;
    usb4_cm_ctx->m_bWakeInterruptHappened = FALSE;
    // m_wakeReason(),
    // usb4_cm_ctx->m_pQdrv = NULL; // Checked later
    // m_pdInfo(), // TODO: AC need to investigate how to hook into PD
    // m_logger(), // Refer to invocation of Usb4CmLoggerInit()
    usb4_cm_ctx->m_quirks = 0;

    if (USB4_NUM_OF_CORES < coreId)
    {
        USB4_ERROR_STACK_MSG(-1, "Core index out of range");
        return -1;
    }

    USB4_ASSERT(0 == Usb4CmLoggerInit(&usb4_cm_ctx->m_logger, usb4_cm_ctx, coreId));

    if (NULL == usb4_cm_ctx->m_pQdrv)
    {
        // usb4_cm_ctx->m_pQdrv = new (std::nothrow) VVDRV_usb4_qdrv(*this);
        usb4_cm_ctx->m_pQdrv = usb4_mem_alloc(sizeof(usb4_qdrv_ctx_t), 0);
        if (NULL == usb4_cm_ctx->m_pQdrv)
        {
            USB4_ERROR_STACK_MSG(-1, "Creation on instance failed");
            goto ErrorHandling;
        }
    }

    // if (0 != usb4_cm_ctx->m_pQdrv->Init(usb4_cm_ctx->m_pParams->coreIndex))
    if (0 != Usb4QDrvInit(usb4_cm_ctx->m_pQdrv, usb4_cm_ctx, coreId))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

// TODO: AC
// +++ Deprecated, need to find new place
#if 0
    if (0 != Usb4CmConfig(usb4_cm_ctx, bSkipPDinit))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }
#endif
// --- Deprecated, need to find new place

    for (i=0; i<4; i++)
    {
        usb4_utils_rand(0, UINT32_MAX, &usb4_cm_ctx->m_localUUID[i]);
    }

    usb4_mem_memset((UINT8*)(&usb4_cm_ctx->m_pdInfo), 0, sizeof(usb4_cm_ctx->m_pdInfo));
    usb4_mem_memset((UINT8*)(&usb4_cm_ctx->m_interdomainData), 0, sizeof(usb4_cm_ctx->m_interdomainData));

    /* Temporary hack to signify that enable needs to be called */
    // dbaum - commented hacks out usb4_cm_ctx->m_routers[0].m_bPcieTunneling = FALSE;

    usb4_cm_ctx->m_quirks = 0;
    usb4_cm_ctx->m_bInitialized = TRUE;
    return 0;
ErrorHandling:
    return -1;
}

int Usb4CmDeInit(usb4_cm_ctx_t* usb4_cm_ctx)
{
    if (FALSE == usb4_cm_ctx->m_bInitialized)
    {
        return 0;
    }

    while (0 != Usb4CmTryLockCm(usb4_cm_ctx)){};

    usb4_cm_ctx->m_bInitialized = FALSE;

    if ((NULL == usb4_cm_ctx->m_pQdrv) || (NULL == usb4_cm_ctx->m_pQdrv->m_Platform))
    {
        USB4_ERROR_STACK(-1);
        USB4_ASSERT(0 == Usb4CmUnlockCm(usb4_cm_ctx));
        return -1;
    }

    if (0 != Usb4QDrvPhysicalDisconnectUc(usb4_cm_ctx->m_pQdrv))
    {
        USB4_ERROR_STACK(-1);
    }

    if (0 != Usb4PlatformInterruptsDetachInterrupts(usb4_cm_ctx->m_pQdrv->m_Platform->m_interrupts))
    {
       USB4_ERROR_STACK(-1);
    }

    if (0 != Usb4PathManagerDestroyPaths(&usb4_cm_ctx->m_path_manager))
    {
       USB4_ERROR_STACK(-1);
    }

    if (0 != Usb4CmLoggerDeInit(&usb4_cm_ctx->m_logger))
    {
       USB4_ERROR_STACK(-1);
    }

    if (0 != Usb4CtrlIfaceUnInit(&usb4_cm_ctx->m_control))
    {
        USB4_ERROR_STACK(-1);
    }

    USB4_ASSERT(0 == Usb4CmUnlockCm(usb4_cm_ctx));

    if (NULL != usb4_cm_ctx->m_pQdrv->m_Platform->m_uC)
    {
        USB4_ASSERT(0 == Usb4PlatformUcDeActivateUc(usb4_cm_ctx->m_pQdrv->m_Platform->m_uC));
    }

//    if (NULL != usb4_cm_ctx->m_pQdrv->m_Platform->m_GCC)
    {
      usb4_cm_ctx->m_pQdrv->m_Platform->m_bDoSidebandOverride = TRUE;
      usb4_cm_ctx->m_pQdrv->m_Platform->m_sidebandOverrideValue = USB4_platform_sb_ctrl_sw_pulldown;
      USB4_ASSERT(0 == Usb4PlatformPlatformPreReset(usb4_cm_ctx->m_pQdrv->m_Platform));
      USB4_ASSERT(0 == Usb4PlatformUcDeActivateUc(usb4_cm_ctx->m_pQdrv->m_Platform->m_uC));
      //USB4_ASSERT(0 == m_pQdrv->m_Platform->PHY()->PowerDown())
      USB4_ASSERT(0 == Usb4GccConfigureGccMUXs(usb4_cm_ctx->m_pQdrv->m_Platform, 2));
#ifndef USB4_USE_ENABLE_ALL_CLKS_CMM
      USB4_ASSERT(0 == Usb4GccAssertReset(usb4_cm_ctx->m_pQdrv->m_Platform, USB4_GCC_RESET_ALL));
      USB4_ASSERT(0 == Usb4GccDeAssertReset(usb4_cm_ctx->m_pQdrv->m_Platform, USB4_GCC_RESET_ALL));
#endif // ~USB4_USE_ENABLE_ALL_CLKS_CMM
      USB4_ASSERT(0 == Usb4GccConfigureGccMUXs(usb4_cm_ctx->m_pQdrv->m_Platform, 0));
      USB4_ASSERT(0 == Usb4PlatformOverrideSbTxEnable(usb4_cm_ctx->m_pQdrv->m_Platform, 0));
    }
    usb4_mem_free(usb4_cm_ctx->m_pQdrv);
    usb4_cm_ctx->m_pQdrv = NULL;
    usb4_cm_ctx->m_pParams = NULL;

    return 0;
}

usb4_ctrl_iface_ctx_t* Usb4CmControl(usb4_cm_ctx_t* usb4_cm_ctx)
{
    return &usb4_cm_ctx->m_control;
}

usb4_path_manager_ctx_t* Usb4CmPathManager(usb4_cm_ctx_t* usb4_cm_ctx)
{
    return &usb4_cm_ctx->m_path_manager;
}

usb4_hia_ctx_t* Usb4CmHIA(usb4_cm_ctx_t* usb4_cm_ctx)
{
    return &usb4_cm_ctx->m_HIA;
}

int Usb4CmEnable(usb4_cm_ctx_t* usb4_cm_ctx)
{
#ifndef USB4_LOAD_FIRMWARE_ONLY
    UINT32 i;
#endif // ~USB4_LOAD_FIRMWARE_ONLY

    /* Prevent repeated calls */
    if (TRUE ==  usb4_cm_ctx->m_routers[0].m_bPcieTunneling)
    {
        return 0;
    }

    if (0 != Usb4QDrvSetPollingMode(usb4_cm_ctx->m_pQdrv, TRUE))
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }

    USB4_ASSERT(0 == Usb4QDrvOpen(usb4_cm_ctx->m_pQdrv)); /* Reset HW and re-load FW */

#ifndef USB4_LOAD_FIRMWARE_ONLY
    USB4_ASSERT(0 == Usb4PlatformGetHIA_Base(usb4_cm_ctx->m_pQdrv->m_Platform, &usb4_cm_ctx->m_pHI_Base));

    if (0 != Usb4HiaInit(&usb4_cm_ctx->m_HIA, usb4_cm_ctx->m_pHI_Base))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    if (usb4_cm_ctx->m_control.m_HIA) // AC: added if m_HIA is NULL, it was never activated previously, invoking will cause NULL pointer dereference
    {
      if (0 != Usb4CtrlIfaceUnInit(&usb4_cm_ctx->m_control))
      {
          USB4_ERROR_STACK(-1);
          goto ErrorHandling;
      }
    }

    // m_control(&m_logger, m_HIA) replaced with API below.  Adaptation of 2 phase init.
    Usb4CtrlIfaceInit(&usb4_cm_ctx->m_control, &usb4_cm_ctx->m_HIA);
    
    if (0 != Usb4CtrlIfaceEnable(&usb4_cm_ctx->m_control, usb4_cm_ctx->m_pHI_Base))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }



    for (i = 0; i < USB4_MAX_SUPPORTED_ROUTERS; i++)
    {
        if (0 != Usb4RouterInit(&usb4_cm_ctx->m_routers[i], &usb4_cm_ctx->m_control))
        {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
        }
    }

    /* Qualcomm Host router always has all tunnelings enabled */
    usb4_cm_ctx->m_routers[0].m_bPcieTunneling = TRUE;
    usb4_cm_ctx->m_routers[0].m_bUsb3Tunneling = TRUE;
    usb4_cm_ctx->m_routers[0].m_bDpTunneling = TRUE;

    USB4_ASSERT(0 == Usb4PathManagerInit(&usb4_cm_ctx->m_path_manager, usb4_cm_ctx->m_routers));

#ifdef USB4_SKIP_DMA_INIT_AND_USE_DEFAULT_DMA_POOL /* Temporary workaround */
    usb4_cm_ctx->m_path_manager.m_bSkipUsbPathBuild = FALSE;
#endif

//TODO: See if this needs to be done here or as a reaction to PDC interrupt for cable connect.
//    if (0 != m_routers[0].ConfigLaneReversal())
//    {
//        USB4_ERROR_STACK(-1);
//        goto ErrorHandling;
//    }
//
//    if (0 != m_routers[0].ConfigTBT3())
//    {
//        USB4_ERROR_STACK(-1);
//        goto ErrorHandling;
//    }
//
//    if (0 != m_routers[0].ConfigGen3())
//    {
//        USB4_ERROR_STACK(-1);
//        goto ErrorHandling;
//    }

    if (usb4_cm_ctx->m_pParams->bPCIeEP)
    {
        USB4_ASSERT(0 == Usb4PlatformAhbAccess_configure_pcieap_ep_mode(usb4_cm_ctx->m_pQdrv->m_Platform->m_ahbAccess, TRUE));
    }
    else
    {
        USB4_ASSERT(0 == Usb4PlatformAhbAccess_configure_pcieap_ep_mode(usb4_cm_ctx->m_pQdrv->m_Platform->m_ahbAccess, FALSE));
    }

    if (usb4_cm_ctx->m_pParams->bUSB3Device)
    {
        USB4_ASSERT(0 == Usb4PlatformAhbAccess_configure_usbap_device_mode(usb4_cm_ctx->m_pQdrv->m_Platform->m_ahbAccess, TRUE));
    }
    else
    {
        USB4_ASSERT(0 == Usb4PlatformAhbAccess_configure_usbap_device_mode(usb4_cm_ctx->m_pQdrv->m_Platform->m_ahbAccess, FALSE));
    }

    if (0 != Usb4QDrvSetPollingMode(usb4_cm_ctx->m_pQdrv, usb4_cm_ctx->m_pParams->bPollingMode))
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }

    usb4_cm_ctx->m_domainTmuMode = (USB4_tmu_mode)(usb4_cm_ctx->m_pParams->tmuMode);

#endif // ~USB4_LOAD_FIRMWARE_ONLY
    return 0;
#ifndef USB4_LOAD_FIRMWARE_ONLY
ErrorHandling:
    return -1;
#endif // ~USB4_LOAD_FIRMWARE_ONLY
}


int Usb4CmDisable(usb4_cm_ctx_t* usb4_cm_ctx)
{
    if (FALSE ==  usb4_cm_ctx->m_routers[0].m_bPcieTunneling)
    {
        return 0;
    }
    /* setting m_bPcieTunneling to FALSE will force CM->Enable() to re-run 
       initialization of all structures, path building, etc.. */
    usb4_cm_ctx->m_routers[0].m_bPcieTunneling = FALSE;

    while (0 != Usb4CmTryLockCm(usb4_cm_ctx))
    {};

    USB4_ASSERT(0 == Usb4QDrvSetPollingMode(usb4_cm_ctx->m_pQdrv, TRUE));
    Usb4PathManagerDestroyPaths(&usb4_cm_ctx->m_path_manager); /* control port may not be operational */
    Usb4QDrvPhysicalDisconnectUc(usb4_cm_ctx->m_pQdrv); /* uC May not be operational */
    USB4_ASSERT(0 == Usb4PlatformOverrideSbTxEnable(usb4_cm_ctx->m_pQdrv->m_Platform, 0));

    USB4_ASSERT(0 == Usb4CmUnlockCm(usb4_cm_ctx));
    return 0;
}




usb4_router_ctx_t* Usb4CmRouter(usb4_cm_ctx_t* usb4_cm_ctx)
{
    return &usb4_cm_ctx->m_routers[usb4_cm_ctx->m_router_index];
}

boolean Usb4CmIsUSB3Device(usb4_cm_ctx_t* usb4_cm_ctx)
{
    return (usb4_cm_ctx->m_pParams->bUSB3Device);
}

int Usb4CmCheckNumberInterdomainRouters(usb4_cm_ctx_t* usb4_cm_ctx, UINT32* pNum)
{
    UINT32 i;
    UINT32 num = 0;
    
    if (NULL == pNum)
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }
        
    for (i = 0; i < USB4_MAX_SUPPORTED_ROUTERS; i++)
    {
        if (usb4_cm_ctx->m_routers[i].m_bInterdomainRouter)
        {
            ++num;
        }
    }
    
    *pNum = num;
    
    return 0;
}

int Usb4CmActivateInterdmainDataPath(usb4_cm_ctx_t* usb4_cm_ctx, const USB4_host_iface_config_t* pCfg)
{
    USB4_adapter_path_config_t adapterCfg = {};
    UINT32 ringIdx = pCfg->ifaceIndex + 1; // index in the ring array and not 1/2 for data ring
    // USB4_hia_ring_cfg ringCfg = USB4_DEFAULT_RING_CFG(ringIdx + 1);
    USB4_hi_ring_cfg ringCfg = {};
    USB4_ASSERT((ringIdx > 0) && (ringIdx < USB4_HI_TOTAL_RINGS));

    while (0 != Usb4CmTryLockCm(usb4_cm_ctx))
    {};

    adapterCfg.portType = USB4_portType_HIA;
    adapterCfg.interdomainRouterIndex = pCfg->interdomainRouterIndex;
    adapterCfg.interdomainAdapterIndex = pCfg->interdomainAdapterIndex;
    adapterCfg.bSetUpPath = TRUE;
    adapterCfg.bEnableSegments = TRUE;
    
    USB4_ASSERT(0 == Usb4PathManagerSetUpInterdomainPath(&usb4_cm_ctx->m_path_manager, &adapterCfg));

    ringCfg.mode = USB4_HI_RING_MODE_FRAMED;
    ringCfg.sof_pdf_bmsk = 0x2;
    ringCfg.eof_pdf_bmsk = 0x4;
    ringCfg.ring_size = 0x10;
    ringCfg.b_e2e_flow_ontrol_enabled = FALSE;
    ringCfg.b_no_snoop_flag = FALSE;
    ringCfg.b_ring_valid = TRUE; // enable the ring
    
    USB4_ASSERT(0 == Usb4HiaConfigRing(&usb4_cm_ctx->m_HIA, ringIdx, USB4_HI_RING_TYPE_TRANSMIT, &ringCfg));
    
    ringCfg.rcv_data_buffer_size_bytes = USB4_HI_RING_MAX_SIZE_BYTES; // max 4KB
    ringCfg.rcv_transmit_e2e_hopid = 0x0;     // for receieve ring only if b_e2e_flow_ontrol_enabled
    USB4_ASSERT(0 == Usb4HiaConfigRing(&usb4_cm_ctx->m_HIA, ringIdx, USB4_HI_RING_TYPE_RECEIVE, &ringCfg));
    USB4_ASSERT(0 == Usb4CmUnlockCm(usb4_cm_ctx));
    return 0;    
}

int Usb4CmFindRouterByTopology(usb4_cm_ctx_t* usb4_cm_ctx, UINT64 router_topologyID)
{
    UINT32 i;
    for (i = 0; i < USB4_MAX_SUPPORTED_ROUTERS; i++)
    {
        if (router_topologyID == usb4_cm_ctx->m_routers[i].m_topologyID)
        {
            usb4_cm_ctx->m_router_index = i;
            return 0;
        }
    }
    return -1;
}

int Usb4CmFindRouterByTopologyByIndex(usb4_cm_ctx_t* usb4_cm_ctx, UINT64 router_topologyID, UINT32* index)
{
    UINT32 i;
    for (i = 0; i < USB4_MAX_SUPPORTED_ROUTERS; i++)
    {
        if (router_topologyID == usb4_cm_ctx->m_routers[i].m_topologyID)
        {
            *index = i;
            return 0;
        }
    }
    return -1;
}

int Usb4CmPlaceRouterByTopology(usb4_cm_ctx_t* usb4_cm_ctx, UINT64 router_topologyID)
{
    UINT32 i;
    for (i = 0; i < USB4_MAX_SUPPORTED_ROUTERS; i++)
    {
        if (USB4_INVALID_TOPOLOGY_ID == usb4_cm_ctx->m_routers[i].m_topologyID)
        {
            if (0 != Usb4RouterAssignTopologyID(&usb4_cm_ctx->m_routers[i], router_topologyID))
            {
                USB4_ERROR_STACK(-1);
                return -1;
            }
        }

        // This will return the found matching router 
        // (may be the one that was set right now)
        if (router_topologyID == usb4_cm_ctx->m_routers[i].m_topologyID)
        {
            usb4_cm_ctx->m_router_index = i;
            return 0;
        }
    }
    return -1;
}

int Usb4CmRemoveRoutersBeyondTopology(usb4_cm_ctx_t* usb4_cm_ctx, UINT64 router_topologyID)
{
    UINT32 i;
    int rc = 0;
    for (i = 0; i < USB4_MAX_SUPPORTED_ROUTERS; i++)
    {
        if (Usb4RouterIsEnumerated(&usb4_cm_ctx->m_routers[i]) &&
           (router_topologyID == (router_topologyID & usb4_cm_ctx->m_routers[i].m_topologyID)))
        {
            if (usb4_cm_ctx->m_routers[i].m_topologyID >= router_topologyID)
            {
                if (0 != Usb4RouterInit(&usb4_cm_ctx->m_routers[i], &usb4_cm_ctx->m_control))
                {
                    USB4_ERROR_STACK(-1);
                    /* Continue for all routers, even if there was an error */
                    rc = -1;
                }
            }
        }
    }
    return rc;
}

int Usb4CmSwitchHotplugSmInstance(usb4_cm_ctx_t* usb4_cm_ctx)
{
    UINT64 router_topologyID = 0;
    UINT32 adapter;
    usb4_port_ctx_t* pPort;

    USB4_ASSERT(0 == Usb4CtrlIfaceGetRoute(&usb4_cm_ctx->m_control, &router_topologyID));
    USB4_ASSERT(0 == Usb4CtrlIfaceGetAdapter(&usb4_cm_ctx->m_control, &adapter));

    if (0 == adapter) /* This looks like ERR_ENUM or ERR_NUA interdomain notification */
    {
        USB4_ASSERT(0 == usb4_get_router_and_port(router_topologyID, &router_topologyID, &adapter));
    }

    /* Assigns topology ID to the router */
    USB4_ASSERT(0 == Usb4CmPlaceRouterByTopology(usb4_cm_ctx, router_topologyID));
    if (0 != Usb4RouterEnumerate(Usb4CmRouter(usb4_cm_ctx)))/* Enumeration will take no action if the router was enumerated previously */
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }
    pPort = Usb4RouterGetAdapterPortByNumber(Usb4CmRouter(usb4_cm_ctx), adapter);
    USB4_ASSERT(NULL != pPort);
    usb4_cm_ctx->m_pHotplug = &(pPort->m_hotplug);
    /* Keep state in a struct located in a lane 0 adapter */
    if (usb4_cm_ctx->m_pHotplug->pLane0Hotplug)
    {
        usb4_cm_ctx->m_pHotplug = usb4_cm_ctx->m_pHotplug->pLane0Hotplug;
    }
    return 0;
}

int Usb4CmRouteControlPacket(usb4_cm_ctx_t* usb4_cm_ctx, USB4_cpHandlingMethod* method)
{
    USB4_cpDescriptorType desc_type;
    UINT64 router_topologyID;
    USB4_cpNotificationEvent event;

    *method = USB4_cpHandlingMethod_STATELESS;

    USB4_ASSERT(0 == Usb4CmSwitchHotplugSmInstance(usb4_cm_ctx));
    USB4_ASSERT(0 == Usb4CtrlIfaceGetType(&usb4_cm_ctx->m_control, &desc_type));

    switch (desc_type)
    {
        case USB4_cpDescriptorType_HOT_PLUG_EVENT:
        {
            USB4_portType type;
            usb4_port_ctx_t* port;
            
            USB4_ASSERT(0 == Usb4CmParseHpe(usb4_cm_ctx)) //TODO: Extend for multiple state machines

            if(FALSE == usb4_cm_ctx->m_pHotplug->record_was_updated)
            {
                *method = USB4_cpHandlingMethod_NO_ACTION;
                break;
            }

            type = Usb4RouterGetPortType(Usb4CmRouter(usb4_cm_ctx), usb4_cm_ctx->m_pHotplug->adapter_first);
            port = Usb4RouterGetAdapterPortByNumber(Usb4CmRouter(usb4_cm_ctx), usb4_cm_ctx->m_pHotplug->adapter_first);
            switch (type)
            {
                case USB4_portType_DP_IN:
                    *method = USB4_cpHandlingMethod_NO_ACTION;
                    break;
                case USB4_portType_DP_OUT:
                    *method = USB4_cpHandlingMethod_ADAPTER_PORT_SM;
                    break;
                case USB4_portType_LANE0:
                    *method = USB4_cpHandlingMethod_USB4_PORT_SM;
                    if ((0 == usb4_cm_ctx->m_pHotplug->adapter_second) && (0 != port->m_OtherLaneGroupNumber))
                    {
                        usb4_cm_ctx->m_pHotplug->adapter_second = port->m_OtherLaneGroupNumber;
                        usb4_cm_ctx->m_pHotplug->adapter_second_action = USB4_HPE_NO_ACTION;
                    }
                    usb4_cm_ctx->m_pHotplug->next_router_topologyID = usb4_next_router_topology(usb4_cm_ctx->m_pHotplug->router_topologyID, usb4_cm_ctx->m_pHotplug->adapter_first);
                    break;
                case USB4_portType_LANE1:
                    *method = USB4_cpHandlingMethod_USB4_PORT_SM;
                    if (0 == usb4_cm_ctx->m_pHotplug->adapter_second)
                    {
                        USB4_ASSERT(0 != port->m_OtherLaneGroupNumber);
                        usb4_cm_ctx->m_pHotplug->adapter_second = usb4_cm_ctx->m_pHotplug->adapter_first;
                        usb4_cm_ctx->m_pHotplug->adapter_first = port->m_OtherLaneGroupNumber;
                        usb4_cm_ctx->m_pHotplug->adapter_second_action = usb4_cm_ctx->m_pHotplug->adapter_first_action;
                        usb4_cm_ctx->m_pHotplug->adapter_first_action = USB4_HPE_NO_ACTION;
                    }
                    usb4_cm_ctx->m_pHotplug->next_router_topologyID = usb4_next_router_topology(usb4_cm_ctx->m_pHotplug->router_topologyID, usb4_cm_ctx->m_pHotplug->adapter_first);
                    break;
                default:
                    USB4_ASSERT_MSG(-1, "Unexpected port type generated HPE\n");
                    break;
            }
            break;
        }
        case USB4_cpDescriptorType_INTERDOMAIN_REQUEST:
            *method = USB4_cpHandlingMethod_INTERDOMAIN_PROTOCOL;
            break;
        case USB4_cpDescriptorType_INTERDOMAIN_RESPONSE:
            if (usb4_cm_ctx->m_interdomainData.interdomainTopologyID)
            {
                USB4_ASSERT(0 == Usb4CtrlIfaceGetRoute(&usb4_cm_ctx->m_control, &router_topologyID));
				if (0 == router_topologyID)
				{
          Usb4Log(USB4_LOG_CM, Usb4CmRouteControlPacketGotInterdomainRoute0UsingHardCodedValue__Warn, 0);
					// USB4_LOG_WARNING("Warning: got interdomain_route = 0; using hard coded value.\n");
					router_topologyID = 0x2;
				}
				if (router_topologyID == usb4_cm_ctx->m_interdomainData.interdomainTopologyID)
                {
                    *method = USB4_cpHandlingMethod_INTERDOMAIN_SM;
                    break;
                }
                else
                {
                    //TODO: Validate what topology is written in an interdomain packet.
                    Usb4Log(USB4_LOG_CM, Usb4CmRouteControlPacketUnrelatedInterdomainPacketsReceivedDuringActiveHotplugSuspiciousActivity__Warn, 0);
                    // USB4_LOG_WARNING("Unrelated interdomain packets received during active hotplug. Suspicious activity.\n");
                }
            }
            *method = USB4_cpHandlingMethod_INTERDOMAIN_PROTOCOL;
            break;
        case USB4_cpDescriptorType_NOTIFICATION:
            USB4_ASSERT(0 == Usb4CtrlIfaceGetEventCode(&usb4_cm_ctx->m_control, &event));
            switch(event)
            {
                case USB4_cpNotificationEvent_ERR_ENUM:
                    *method = USB4_cpHandlingMethod_INTERDOMAIN_SM;
                    usb4_cm_ctx->m_pHotplug->hotplug_state = USB4_HOTPLUG_INTDOM_HANDLE_ERR_ENUM;
                    break;
                case USB4_cpNotificationEvent_ERR_NUA:
                    /* Router on the other side is not initialized. Give it some time. */
                    *method = USB4_cpHandlingMethod_USB4_PORT_SM;
                    usb4_cm_ctx->m_pHotplug->hotplug_state = USB4_HOTPLUG_DOWNSTREAM_PORT_RESET;
                    break;
                case USB4_cpNotificationEvent_ERR_LINK:
                    USB4_ASSERT(0 == Usb4CmParseErrLink(usb4_cm_ctx));
                    if(FALSE == usb4_cm_ctx->m_pHotplug->record_was_updated)
                    {
                        *method = USB4_cpHandlingMethod_NO_ACTION;
                    }
                    else
                    {
                        *method = USB4_cpHandlingMethod_USB4_PORT_SM;
                    }
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return 0;
}
//USB4_cpDescriptorType_HOT_PLUG_EVENT
//USB4_cpNotificationEvent_ERR_LINK

int Usb4CmControlPacketHandler(usb4_cm_ctx_t* usb4_cm_ctx) // boolean bYieldControl, boolean* pbIdle  Absorbed into usb4_cm_ctx
{
    USB4_cpHandlingMethod method;
    if (usb4_cm_ctx->m_pbIdle)
    {
        usb4_cm_ctx->m_pbIdle = TRUE;
    }
    if (0 != Usb4CmTryLockCm(usb4_cm_ctx))
    {
        return 0;
    }
    while((0 == Usb4CtrlIfaceProcessDeferred(&usb4_cm_ctx->m_control)) ||(0 == Usb4CtrlIfacePeek(&usb4_cm_ctx->m_control))) /* Multiple packets could have arrived */
    {
        if (usb4_cm_ctx->m_pbIdle)
        {
            usb4_cm_ctx->m_pbIdle = FALSE;
        }
        
        if (usb4_cm_ctx->m_pParams->bPollingMode)
        {
            Usb4PlatformUcHandleUcEvents(usb4_cm_ctx->m_pQdrv->m_Platform->m_uC); /* Handle uC events to prevent overflow and capture all of them */
        }

        /* Handle errors */
        USB4_ASSERT(0 == Usb4CtrlIfaceHandleErrorNotifications(&usb4_cm_ctx->m_control, NULL));

        USB4_ASSERT(0==Usb4CmRouteControlPacket(usb4_cm_ctx, &method));
        switch(method)
        {
            case USB4_cpHandlingMethod_ADAPTER_PORT_SM:
                /* Handle DisaplyPort adapter */
                if (0 != Usb4CmAdapterPortHotPlugHandler(usb4_cm_ctx))
                {
                    USB4_ERROR_STACK(-1);
                    goto ErrorHandling;
                }
                break;

            case USB4_cpHandlingMethod_USB4_PORT_SM:
                if (USB4_HPE_OUT == usb4_cm_ctx->m_pHotplug->adapter_first_action)
                {
                    if (0 != Usb4CmHandleLaneUnplug(usb4_cm_ctx))
                    {
                        USB4_ERROR_STACK(-1);
                        goto ErrorHandling;
                    }
                }
                else
                {

                    if (0 != Usb4CmUSB4PortHotPlugHandler(usb4_cm_ctx))
                    {
                        USB4_ERROR_STACK(-1);
                        goto ErrorHandling;
                    }
                }
                break;

            case USB4_cpHandlingMethod_INTERDOMAIN_SM:
                if (0 != Usb4CmInterdomainHotPlugHandler(usb4_cm_ctx))
                {
                    USB4_ERROR_STACK(-1);
                    goto ErrorHandling;
                }
                break;
            case USB4_cpHandlingMethod_INTERDOMAIN_PROTOCOL:
                if (0 != Usb4CmInterdomainProtocolHandler(usb4_cm_ctx))
                {
                    USB4_ERROR_STACK(-1);
                    goto ErrorHandling;
                }
                break;
            case USB4_cpHandlingMethod_STATELESS:
                if (0 != Usb4CmStatelessPacketsHandler(usb4_cm_ctx))
                {
                    USB4_ERROR_STACK(-1);
                    goto ErrorHandling;
                }
                break;
            case USB4_cpHandlingMethod_NO_ACTION:
            default:
                break;
        }

        if (TRUE == usb4_cm_ctx->m_bYieldControl)
        {
        	break;
        }
    }
    USB4_ASSERT(0 == Usb4CmUnlockCm(usb4_cm_ctx));
    return 0;
ErrorHandling:
    USB4_ASSERT(0 == Usb4CmUnlockCm(usb4_cm_ctx));
    return -1;
}

int Usb4CmEnableTunneling(usb4_cm_ctx_t* usb4_cm_ctx)
{
    UINT32 i;

    /* Enable tunneling - if there is appropriate upstream adapter port, and,
     * upstream router has tunneling enabled;
     * TODO: Not handling xHCI host in the device router at this time. */
    for (i = 1; i < USB4_MAX_SUPPORTED_ROUTERS; i++)
    {
        UINT64 upstream_topologyID;
        UINT32 upstream_router_index;
        UINT32 adapter;
        usb4_port_ctx_t* port;

        if ((USB4_INVALID_TOPOLOGY_ID == usb4_cm_ctx->m_routers[i].m_topologyID) ||
            (usb4_cm_ctx->m_routers[i].m_bPcieTunneling) || /* Router was configured already */
            (usb4_cm_ctx->m_routers[i].m_bUsb3Tunneling) ||
            (usb4_cm_ctx->m_routers[i].m_bDpTunneling))
        {
            continue;
        }

        USB4_ASSERT(0 == usb4_get_router_and_port(usb4_cm_ctx->m_routers[i].m_topologyID, &upstream_topologyID, &adapter));
        USB4_ASSERT(0 == Usb4CmFindRouterByTopologyByIndex(usb4_cm_ctx, upstream_topologyID, &upstream_router_index));

#ifdef USB4_CONCURENCY_ENABLED
    #if defined(DISABLE_PCIE_TUNNELING)
        #error -- PCIE tunneling disabled --
    #endif
    #if defined(DISABLE_USB_TUNNELING)
        #error -- USB tunneling disabled --
    #endif
#endif //USB4_CONCURENCY_ENABLED

#ifndef DISABLE_PCIE_TUNNELING
        port = Usb4RouterGetAdapterPortByType(&usb4_cm_ctx->m_routers[i], USB4_portType_UPSTREAM_PCIE_ADAPTER, 0);
        if ((NULL != port) && (usb4_cm_ctx->m_routers[upstream_router_index].m_bPcieTunneling))
        {
            if (0 != Usb4RouterEnablePcieTunneling(&usb4_cm_ctx->m_routers[i]))
            {
                USB4_ERROR_STACK(-1);
                goto ErrorHandling;
            }
            usb4_cm_ctx->m_routers[i].m_bPcieTunneling = TRUE;
        }
#endif /* DISABLE_PCIE_TUNNELING */
        
#ifndef DISABLE_USB_TUNNELING
        port = Usb4RouterGetAdapterPortByType(&usb4_cm_ctx->m_routers[i], USB4_portType_UPSTREAM_USB3_ADAPTER, 0);
        if ((NULL != port) && (usb4_cm_ctx->m_routers[upstream_router_index].m_bUsb3Tunneling))
        {
            if (0 != Usb4RouterEnableUsb3Tunneling(&usb4_cm_ctx->m_routers[i]))
            {
                USB4_ERROR_STACK(-1);
                goto ErrorHandling;
            }
            usb4_cm_ctx->m_routers[i].m_bUsb3Tunneling = TRUE;
        }
#endif /* DISABLE_USB_TUNNELING */

#ifndef DISABLE_DP_TUNNELING
        port = Usb4RouterGetAdapterPortByType(&usb4_cm_ctx->m_routers[i], USB4_portType_DP_OUT, 0);
        if ((NULL != port) && (usb4_cm_ctx->m_routers[upstream_router_index].m_bDpTunneling))
        {
            usb4_cm_ctx->m_routers[i].m_bDpTunneling = TRUE;
        }
#endif /* DISABLE_DP_TUNNELING */

        if (0 != Usb4RouterSetConfigurationValid(&usb4_cm_ctx->m_routers[i]))
        {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
        }
    }
    return 0;

ErrorHandling:
    return -1;
}

int Usb4CmConfig(usb4_cm_ctx_t* usb4_cm_ctx, const USB4_cfgParams_t* pParams)
{
    UINT32 coreIdx;
    
    if (NULL != pParams) // Reverse the check to avoid static analysis error
    {
        usb4_cm_ctx->m_pParams = pParams;
    }
    else if (NULL == usb4_cm_ctx->m_pParams) 
    {
        USB4_ERROR_STACK_MSG(-1, "pParams NULL is not supported on 1st call");
        return -1;
    }

    coreIdx = Usb4PlatformGetCoreIndex(usb4_cm_ctx->m_pQdrv->m_Platform);
    if (coreIdx != usb4_cm_ctx->m_pParams->coreIndex)
    {
        USB4_ERROR_STACK_MSG(-1, "Wrong core index");
        return -1;
    }

    if ((TRUE == usb4_cm_ctx->m_pParams->bUseRealPD) || (TRUE == usb4_cm_ctx->m_pParams->bToggleTypeC))
    {
        // TODO: Dror, when this change to auto ?
        Usb4Log(USB4_LOG_CM, Usb4CmConfigHardcodedPdConfigToSRCDFP__Info, 0);
        // USB4_LOG_INFO("Hardcoded pd config to SRC_DFP \n");
        USB4_PD_POWER_ROLE role = USB4_PD_POWER_ROLE_SRC_DFP; //TODO: Dror, when this changes?
        USB4_PD_ATTACH_MODE mode;

        mode = (FALSE != usb4_cm_ctx->m_pParams->bUseTBT3Mode) ? 
                    USB4_PD_ATTACH_MODE_TBT3 : USB4_PD_ATTACH_MODE_USB4;

        // if (0 != usb4_cm_ctx->m_pQdrv->m_Platform->PD()->Config(role, mode)) // TODO: AC ERROR port PD code
        role = (USB4_PD_POWER_ROLE)role; // Until porting is finished
#if 0
        if (0 != VVDRV_pd_api_config(usb4_cm_ctx->m_pQdrv->m_Platform->m_coreIndex, role, mode)) // TODO: AC ERROR port PD code
        {
            USB4_ERROR_STACK_MSG(-1, "m_PD.Init failed\n");
            return -1;
        }
#endif
    }

    return 0;
}

// +++ Deprecated
int Usb4CmHandleHostRouterCableConnect(usb4_cm_ctx_t* usb4_cm_ctx, UINT32 msTimeout,
                                                const USB4_PD_INFO* pInfo)
{
    UINT32 timeout;
    usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;

    USB4_ASSERT(0 == Usb4CmNotifyUsb4CableEvent(usb4_cm_ctx, pInfo));

    usb4_cm_ctx->m_bYieldControl = TRUE;
    usb4_cm_ctx->m_pbIdle = (BOOLEAN)NULL;

    timeout = 0;
    if (0 != msTimeout)
    {
        while (timeout < msTimeout)
        {
            USB4_ASSERT(0 == Usb4CmControlPacketHandler(usb4_cm_ctx)); // 2 parameters absorbed into usb4_cm_ctx TRUE, NULL
            usb4_timer_Sleep_ms(&timer, 1);
            timeout++;
        }
    }

    return 0;
}
// --- Deprecated


int Usb4CmGetRouterByIdx(usb4_cm_ctx_t* usb4_cm_ctx, UINT32 idx, usb4_router_ctx_t** ppRouter)
{
    if ((NULL == ppRouter) || (idx >= ARR_SIZE(usb4_cm_ctx->m_routers)))
    {
        USB4_ERROR_STACK_MSG(-1, "Invalid input args\n");
        goto ErrorHandling;
    }
    
    *ppRouter = &usb4_cm_ctx->m_routers[idx];
    return  0;
    
ErrorHandling:
    return -1;
}

int Usb4CmPrepareSleep(usb4_cm_ctx_t* usb4_cm_ctx)
{
    UINT32 i,j, countOfRouters = 0;

    usb4_cm_ctx->m_bWakeInterruptHappened = FALSE;
    usb4_mem_memset((UINT8*)(&usb4_cm_ctx->m_wakeReason), 0, sizeof(usb4_cm_ctx->m_wakeReason));

    while (0 != Usb4CmTryLockCm(usb4_cm_ctx));

    for (i = 0; i < USB4_MAX_SUPPORTED_ROUTERS; i++)
    {
        if (Usb4RouterIsEnumerated(&usb4_cm_ctx->m_routers[i]))
        {
            countOfRouters++;
        }
        else
        {
            break;
        }
    }

    USB4_ASSERT(0 == Usb4PlatformGetCablePluggedStatus(usb4_cm_ctx->m_pQdrv->m_Platform)) /* Needed to determine SB override configuration */

    if (0 != (usb4_cm_ctx->m_quirks & USB4_CM_QUIRK_DISABLE_WAKE_ON_CONNECT))
    {
        usb4_cm_ctx->m_routers[0].m_bDisableWakeOnConnect = TRUE;
    }

    if (0 != (usb4_cm_ctx->m_quirks & USB4_CM_QUIRK_DISABLE_WAKE_ON_DISCONNECT))
    {
        usb4_cm_ctx->m_routers[0].m_bDisableWakeOnDisconnect = TRUE;
    }

    if (0 != (usb4_cm_ctx->m_quirks & USB4_CM_QUIRK_DISABLE_WAKE_ON_USB4_EVENT))
    {
        usb4_cm_ctx->m_routers[0].m_bDisableWakeOnUsb4 = TRUE;
    }

    if (0 != (usb4_cm_ctx->m_quirks & USB4_CM_QUIRK_DISABLE_WAKE_ON_INTERDOMAIN))
    {
        usb4_cm_ctx->m_routers[0].m_bDisableWakeOnInterdomain = TRUE;
    }

    /* Configure sleep for all routers - 4.5.1 Entry to Sleep */
    for (i = 0; i < countOfRouters; i++)
    {
        j = countOfRouters - 1 - i;
        USB4_ASSERT(0 == Usb4RouterPrepareSleep(&usb4_cm_ctx->m_routers[j])) /* Function tests if the request is applicable */
    }

    /* Hanlde notifications if arrived */
    {
        usb4_utils_timer timer;
        timer.m_source = USB4_TIMER_SOURCE_QTIMER;

        USB4_ASSERT(0 == Usb4CmUnlockCm(usb4_cm_ctx));
        usb4_timer_Sleep_ms(&timer, 5);
        while (0 != Usb4CmTryLockCm(usb4_cm_ctx));
    }

    countOfRouters = 0;
    for (i = 0; i < USB4_MAX_SUPPORTED_ROUTERS; i++)
    {
        if (Usb4RouterIsEnumerated(&usb4_cm_ctx->m_routers[i]))
        {
            countOfRouters++;
        }
        else
        {
            break;
        }
    }

    for (i = 0; i < countOfRouters; i++)
    {
        j = countOfRouters - 1 - i;
        USB4_ASSERT(0 == Usb4RouterSetEnterSleep(&usb4_cm_ctx->m_routers[j])) /* Activates sleep on TBT3 Devce routers */
    }

    /* Validate status for all routers */
    for (i = 0; i < countOfRouters; i++)
    {
        j = countOfRouters - 1 - i;
        USB4_ASSERT(0 == Usb4RouterCheckSleepReady(&usb4_cm_ctx->m_routers[j])) /* Function tests if the request is applicable */
    }

    USB4_ASSERT(0 == Usb4CmUnlockCm(usb4_cm_ctx));

    return 0;
}

int Usb4CmActivateSleep(usb4_cm_ctx_t* usb4_cm_ctx)
{

    while (0 != Usb4CmTryLockCm(usb4_cm_ctx));
    USB4_ASSERT(0 == Usb4QDrvInitSleep(usb4_cm_ctx->m_pQdrv));
    USB4_ASSERT(0 == Usb4CmUnlockCm(usb4_cm_ctx));

    return 0;
}


int Usb4CmWakeFlow(usb4_cm_ctx_t* usb4_cm_ctx, USB4_uc_wake_reason reason)
{
    boolean bSkipDpPathBuild, bSkipPciePathBuild, bSkipUsbPathBuild;

    if (usb4_cm_ctx->m_bWakeInterruptHappened)
    {
        Usb4Log(USB4_LOG_CM, Usb4CmWakeFlowCoreWasWakenUpInISR__Info, 0);
        // USB4_LOG_INFO("CM WakeFlow: Core was waken up in ISR\n");
        return 0;
    }

    if (0 != Usb4CmWake(usb4_cm_ctx, USB4_CM_WAKE_DO_PLATFORM_ACTIONS, USB4_uc_wake_reason_UNDEFINED))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    /* setting m_bPcieTunneling to FALSE will force CM->Enable() to re-run 
       initialization of all structures, path building, etc.. */
    usb4_cm_ctx->m_routers[0].m_bPcieTunneling = FALSE;

    /* Store path building configuration */
    bSkipDpPathBuild = usb4_cm_ctx->m_path_manager.m_bSkipDpPathBuild;
    bSkipPciePathBuild = usb4_cm_ctx->m_path_manager.m_bSkipPciePathBuild;
    bSkipUsbPathBuild = usb4_cm_ctx->m_path_manager.m_bSkipUsbPathBuild;

// +++ Deprecated
#if 0
    if (0 != Usb4CmInit(usb4_cm_ctx, NULL))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }
#endif
// --- Deprecated

    if (0 != Usb4CmEnable(usb4_cm_ctx))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    /* Recover path building configuration */
    usb4_cm_ctx->m_path_manager.m_bSkipDpPathBuild = bSkipDpPathBuild;
    usb4_cm_ctx->m_path_manager.m_bSkipPciePathBuild = bSkipPciePathBuild;
    usb4_cm_ctx->m_path_manager.m_bSkipUsbPathBuild = bSkipUsbPathBuild;

    if (0 != Usb4CmWake(usb4_cm_ctx, USB4_CM_WAKE_DO_WRITE_BACK_PERSISTENT_DATA, USB4_uc_wake_reason_UNDEFINED))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    /* Will get real WAKE reason from ISR or presume System */
    if (0 != Usb4CmWake(usb4_cm_ctx, USB4_CM_WAKE_DO_LAUNCH_UC, reason))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }
    return 0;

ErrorHandling:
    return -1;
}

int Usb4CmWake(usb4_cm_ctx_t* usb4_cm_ctx, USB4_cm_wake_stage_type wakeStage, USB4_uc_wake_reason reason) // default: USB4_uc_wake_reason reason = USB4_uc_wake_reason_UNDEFINED
{
    if (USB4_CM_WAKE_DO_LAUNCH_UC == wakeStage)
    {
        UINT32 isUsb4Device;
        usb4_usb4_port_cs usb4_port_cs = {0};
        usb4_port_ctx_t* pPort;

        isUsb4Device = (FALSE == usb4_cm_ctx->m_pParams->bUseTBT3Mode) ? 0x1 : 0x0;

        USB4_ASSERT(0 == Usb4QDrvCableConnectedHandler(usb4_cm_ctx->m_pQdrv, isUsb4Device, usb4_cm_ctx->m_pParams->numLanes));

        if (USB4_uc_wake_reason_UNDEFINED == reason)
        {
            reason = USB4_uc_wake_reason_SYSTEM_WAKE;
            Usb4Log(USB4_LOG_CM, Usb4CmWakeSystemInitiated__Info, 0);
            // USB4_LOG_INFO("CM Wake: System initiated\n");
        }

        /* Position changed due to temporary workaround - uC issue*/
        /* Enumeration will take no action if the router was enumerated previously
                   Need to enumerate to set topology valid, or Hot plug will not arrive.... */
        while (0 != Usb4CmTryLockCm(usb4_cm_ctx))
        {};
        USB4_ASSERT(0 == Usb4CmPlaceRouterByTopology(usb4_cm_ctx, 0)); /* Current router is a host router */
        USB4_ASSERT(0 == Usb4RouterEnumerate(Usb4CmRouter(usb4_cm_ctx)));
        USB4_ASSERT(0 == Usb4RouterConfigureRequestRsFec(Usb4CmRouter(usb4_cm_ctx), usb4_cm_ctx->m_pParams->bDisableRS_FEC));
        USB4_ASSERT(0 == Usb4RouterLimitTargetLinkSpeedToGen2(Usb4CmRouter(usb4_cm_ctx), usb4_cm_ctx->m_pParams->bLimitToGen2));
//        USB4_ASSERT(0 == Usb4RouterLimitToSingleLane(Usb4CmRouter(usb4_cm_ctx), usb4_cm_ctx->m_pParams->numLanes < 2));
        USB4_ASSERT(0 == Usb4RouterEnableLanes(Usb4CmRouter(usb4_cm_ctx), usb4_cm_ctx->m_pParams->numLanes < 2));
        /* Hanlde notifications if arrived */
        {
            usb4_utils_timer timer;
            timer.m_source = USB4_TIMER_SOURCE_QTIMER;

            USB4_ASSERT(0 == Usb4CmUnlockCm(usb4_cm_ctx));
            usb4_timer_Sleep_ms(&timer, 100);
            while (0 != Usb4CmTryLockCm(usb4_cm_ctx));
        }

        USB4_ASSERT(0 == Usb4QDrvWake(usb4_cm_ctx->m_pQdrv, wakeStage, reason));
        /* Enumeration will take no action if the router was enumerated previously
           Need to enumerate to set topology valid, or Hot plug will not arrive.... */
        //USB4_ASSERT(0 == PlaceRouterByTopology(0)); /* Current router is a host router */
        //USB4_ASSERT(0 == Router().Enumerate());

        /* Get wake reason */
        pPort = Usb4RouterGetAdapterPortByType(Usb4CmRouter(usb4_cm_ctx), USB4_portType_LANE0, 0);
        USB4_ASSERT(NULL != pPort);
        USB4_ASSERT(0 == Usb4PortSearchCapability(pPort, USB4_USB4_PORT_CAPABILITY, NULL));
        USB4_ASSERT(0 == Usb4PortReadCapability(pPort, (UINT8*)(&usb4_port_cs), sizeof(usb4_port_cs)));

        /* Print statuses */
//        USB4_LOG_INFO("Wake sources: Topology %x, Port %u (%s), WakeonConnectStatus %u,"
//                "WakeonDisconnectStatus %u, WakeonInterDomainStatus %u, WakeonUSB4WakeStatus %u\n",
//                            0, pPort->m_Number, pPort->GetName(),
//                            usb4_port_cs.PORT_CS_18.WakeonConnectStatus,
//                            usb4_port_cs.PORT_CS_18.WakeonDisconnectStatus,
//                            usb4_port_cs.PORT_CS_18.WakeonInterDomainStatus,
//                            usb4_port_cs.PORT_CS_18.WakeonUSB4WakeStatus);
        Usb4Log3(USB4_LOG_CM, Usb4CmWake__Params__SourcesTopology_Port_WakeonConnectStatus, 0, 
            0, pPort->m_Number, usb4_port_cs.PORT_CS_18.WakeonConnectStatus);
        Usb4Log3(USB4_LOG_CM, Usb4CmWake__Params__WakeonDisconnectStatus_WakeonInterDomainStatus_WakeonUSB4WakeStatus, 0, 
            usb4_port_cs.PORT_CS_18.WakeonDisconnectStatus,
            usb4_port_cs.PORT_CS_18.WakeonInterDomainStatus,
            usb4_port_cs.PORT_CS_18.WakeonUSB4WakeStatus);
        usb4_cm_ctx->m_wakeReason.WakeonConnectStatus     = usb4_port_cs.PORT_CS_18.WakeonConnectStatus;
        usb4_cm_ctx->m_wakeReason.WakeonDisconnectStatus  = usb4_port_cs.PORT_CS_18.WakeonDisconnectStatus;
        usb4_cm_ctx->m_wakeReason.WakeonInterDomainStatus = usb4_port_cs.PORT_CS_18.WakeonInterDomainStatus;
        usb4_cm_ctx->m_wakeReason.WakeonUSB4WakeStatus    = usb4_port_cs.PORT_CS_18.WakeonUSB4WakeStatus;

        if (TRUE == usb4_cm_ctx->m_pQdrv->m_Platform->m_bSleepUnplugged)
        {
            USB4_ASSERT(1 == usb4_port_cs.PORT_CS_18.WakeonConnectStatus) /* Sanity test */
            if (USB4_PD_CC_ORIENTATION_OPEN != usb4_cm_ctx->m_pdInfo.cc_orientation)
            {
                USB4_ASSERT(0 == Usb4CmPreHsEstablishment(usb4_cm_ctx));
                USB4_ASSERT(0 == Usb4QDrvEstablishHsConnection(usb4_cm_ctx->m_pQdrv, &usb4_cm_ctx->m_pdInfo));
                if ((0 != usb4_cm_ctx->m_pParams->controlPacketsTimeout_ms)&&(TRUE == usb4_cm_ctx->m_pParams->bPollingMode))
                {
                    USB4_ASSERT(0 == Usb4CmUnlockCm(usb4_cm_ctx)); /* Next function takes lock */
                    USB4_ASSERT(0 == Usb4CmWaitForCl0(usb4_cm_ctx, usb4_cm_ctx->m_pParams->controlPacketsTimeout_ms));
                }
            }
        }
        USB4_ASSERT(0 == Usb4CmUnlockCm(usb4_cm_ctx));
    }
    else
    {
        USB4_ASSERT(0 == Usb4QDrvWake(usb4_cm_ctx->m_pQdrv, wakeStage, reason));
    }

    return 0;
}

int Usb4CmNotifyUsb4CableEvent(usb4_cm_ctx_t* usb4_cm_ctx, const USB4_PD_INFO* pInfo)
{
    /* Update member with current information. Will be used during link establishment */

    UINT32 isUsb4Device;
    
    if (NULL != pInfo)
    {
        usb4_cm_ctx->m_pdInfo = *pInfo;
    }

    isUsb4Device = (USB4_PD_ATTACH_MODE_USB4 == usb4_cm_ctx->m_pdInfo.current_mode) ? 0x1 : 0x0;
    
    USB4_ASSERT(0 == Usb4QDrvCableConnectedHandler(usb4_cm_ctx->m_pQdrv, isUsb4Device, usb4_cm_ctx->m_pParams->numLanes));

    USB4_ASSERT(0 == Usb4CmPreHostRouterEnumeration(usb4_cm_ctx));
    /* Enumeration will take no action if the router was enumerated previously
       Need to enumerate to set topology valid, or Hot plug will not arrive.... */
    while (0 != Usb4CmTryLockCm(usb4_cm_ctx))
    {};
    USB4_ASSERT(0 == Usb4CmPlaceRouterByTopology(usb4_cm_ctx, 0)); /* Current router is a host router */
    USB4_ASSERT(0 == Usb4RouterEnumerate(Usb4CmRouter(usb4_cm_ctx)));
    USB4_ASSERT(0 == Usb4RouterConfigureRequestRsFec(Usb4CmRouter(usb4_cm_ctx), usb4_cm_ctx->m_pParams->bDisableRS_FEC));
    USB4_ASSERT(0 == Usb4RouterLimitTargetLinkSpeedToGen2(Usb4CmRouter(usb4_cm_ctx), usb4_cm_ctx->m_pParams->bLimitToGen2));
    // USB4_ASSERT(0 == Usb4RouterLimitToSingleLane(Usb4CmRouter(usb4_cm_ctx), usb4_cm_ctx->m_pParams->numLanes < 2));
    USB4_ASSERT(0 == Usb4RouterEnableLanes(Usb4CmRouter(usb4_cm_ctx), usb4_cm_ctx->m_pParams->numLanes < 2));
    // USB4_ASSERT(0 == Usb4CmUnlockCm(usb4_cm_ctx));
    
    if (USB4_PD_CC_ORIENTATION_OPEN != usb4_cm_ctx->m_pdInfo.cc_orientation)
    {
        USB4_ASSERT(0 == Usb4CmPreHsEstablishment(usb4_cm_ctx));
        USB4_ASSERT(0 == Usb4QDrvEstablishHsConnection(usb4_cm_ctx->m_pQdrv, &usb4_cm_ctx->m_pdInfo));
        if ((0 != usb4_cm_ctx->m_pParams->controlPacketsTimeout_ms) && 
            (TRUE == usb4_cm_ctx->m_pParams->bPollingMode))
        {
            USB4_ASSERT(0 == Usb4CmUnlockCm(usb4_cm_ctx)); /* Next function takes lock */
            USB4_ASSERT(0 == Usb4CmWaitForCl0(usb4_cm_ctx, usb4_cm_ctx->m_pParams->controlPacketsTimeout_ms));
        }
    }

    USB4_ASSERT(0 == Usb4CmUnlockCm(usb4_cm_ctx));
    return 0;
}

int Usb4CmWaitForHostConnectStateMachine(usb4_cm_ctx_t* usb4_cm_ctx,
                                         UINT32 timeout_ms, 
                                         UINT32 maxidle_ms)
{
    usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;
    UINT32 elapsed_ms = 0;
    UINT32 read_elapsed_ms = 0;
    UINT32 iter_ms = 0;
    UINT32 idle_ms = 0;
    boolean bIdle = FALSE;

    usb4_timer_Start(&timer);
    while ((elapsed_ms < timeout_ms) && (idle_ms < maxidle_ms))
    {
        if (TRUE == usb4_cm_ctx->m_pParams->bPollingMode)
        {
        
            usb4_cm_ctx->m_bYieldControl = TRUE;
            usb4_cm_ctx->m_pbIdle = (BOOLEAN)NULL;
            // in interrupt mode this control packet handler will be called from isr
            USB4_ASSERT(0 == Usb4CmControlPacketHandler(usb4_cm_ctx)); // 2 parameters absorbed into usb4_cm_ctx TRUE, NULL
        }
        USB4_ASSERT(0 == usb4_timer_GetElapsed_ms(&timer, &read_elapsed_ms));
        iter_ms = read_elapsed_ms - elapsed_ms;
        elapsed_ms = read_elapsed_ms;
        idle_ms = (TRUE == bIdle) ? idle_ms + iter_ms : 0;
    }
    return 0;
}


int Usb4CmResetHostInterface(usb4_cm_ctx_t* usb4_cm_ctx)
{
    UINT32 LastErr,  ProgramCounter, Num;
    USB4_ASSERT(0 == Usb4HiaPlatformReset(&usb4_cm_ctx->m_HIA));

    USB4_ASSERT(0 == Usb4PlatformUcGetPropreitryError(usb4_cm_ctx->m_pQdrv->m_Platform->m_uC, &LastErr, &ProgramCounter, &Num));
    if (Num > 0)
    {
        Usb4Log2(USB4_LOG_CM, Usb4CmResetHostInterfaceWARNING__Params__Core_uCSignalledError, 0, Usb4PlatformGetCoreIndex(usb4_cm_ctx->m_pQdrv->m_Platform), LastErr);
        // USB4_LOG_WARNING("Core[%u] uC signalled error %u\n", Usb4PlatformGetCoreIndex(usb4_cm_ctx->m_pQdrv->m_Platform), LastErr);
        if (3 == LastErr)
        {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
        }
    }

    if (0 != Usb4HiaInit(&usb4_cm_ctx->m_HIA, usb4_cm_ctx->m_pHI_Base))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    if (0 != Usb4CtrlIfaceUnInit(&usb4_cm_ctx->m_control))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    if (0 != Usb4CtrlIfaceEnable(&usb4_cm_ctx->m_control, usb4_cm_ctx->m_pHI_Base))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    {
        UINT32 ringIdx = 1; // index in the ring array and not 1/2 for data ring
        // USB4_hia_ring_cfg ringCfg = USB4_DEFAULT_RING_CFG(ringIdx + 1);
        USB4_hi_ring_cfg ringCfg = {};

        ringCfg.mode = USB4_HI_RING_MODE_FRAMED;
        ringCfg.sof_pdf_bmsk = 0x2;
        ringCfg.eof_pdf_bmsk = 0x4;
        ringCfg.ring_size = 0x10;
        ringCfg.b_e2e_flow_ontrol_enabled = FALSE;
        ringCfg.b_no_snoop_flag = FALSE;
        ringCfg.b_ring_valid = TRUE; // enable the ring
        ringCfg.rcv_transmit_e2e_hopid = 0x0;     // for receieve ring only if b_e2e_flow_ontrol_enabled
        ringCfg.rcv_data_buffer_size_bytes  = 0;
        USB4_ASSERT(0 == Usb4HiaConfigRing(&usb4_cm_ctx->m_HIA, ringIdx, USB4_HI_RING_TYPE_TRANSMIT, &ringCfg));
        ringCfg.rcv_data_buffer_size_bytes = USB4_HI_RING_MAX_SIZE_BYTES; // max 4KB
        USB4_ASSERT(0 == Usb4HiaConfigRing(&usb4_cm_ctx->m_HIA, ringIdx, USB4_HI_RING_TYPE_RECEIVE, &ringCfg));

        ringIdx = 2;
        ringCfg.rcv_data_buffer_size_bytes  = 0;
        USB4_ASSERT(0 == Usb4HiaConfigRing(&usb4_cm_ctx->m_HIA, ringIdx, USB4_HI_RING_TYPE_TRANSMIT, &ringCfg));
        ringCfg.rcv_data_buffer_size_bytes = USB4_HI_RING_MAX_SIZE_BYTES; // max 4KB
        USB4_ASSERT(0 == Usb4HiaConfigRing(&usb4_cm_ctx->m_HIA, ringIdx, USB4_HI_RING_TYPE_RECEIVE, &ringCfg));
    }
    return 0;
ErrorHandling:
    return -1;
}

int Usb4CmPreHostRouterEnumeration(usb4_cm_ctx_t* usb4_cm_ctx)
{
	if (0 != (usb4_cm_ctx->m_quirks & USB4_CM_QUIRK_DISABLE_HPE_DPIN))
	{
		USB4_ASSERT(0 == Usb4PlatformAhbAccess_dpin_configure_hot_plug_notification(usb4_cm_ctx->m_pQdrv->m_Platform->m_ahbAccess, 0)); /* Enabled POR */
	}
	if (0 != (usb4_cm_ctx->m_quirks & USB4_CM_QUIRK_RELAXED_DISCONNECT_DETECTION))
    {
	    /* Update from 14usec to 20usec (time is counted in 52nsec units) */
	    USB4_ASSERT(0 == Usb4PlatformOverrideSbTDisconnectRx(usb4_cm_ctx->m_pQdrv->m_Platform, 0x180, NULL));
    }

    return 0;
}

int Usb4CmPreHsEstablishment(usb4_cm_ctx_t* usb4_cm_ctx)
{
	if (0 != (usb4_cm_ctx->m_quirks & USB4_CM_QUIRK_DISABLE_HPE_L0))
	{
		/* TODO: For future targets accomodate multiple downstream ports */
		usb4_port_ctx_t* port = Usb4RouterGetAdapterPortByType(&usb4_cm_ctx->m_routers[0], USB4_portType_LANE0, 0);
    if (port)
    {
		  USB4_ASSERT(0 == Usb4PortConfigureDHP(port, 0));
    }
    else
    {
      USB4_ERROR_STACK(-1);
      return -1;
    }
	}
	if (0 != (usb4_cm_ctx->m_quirks & USB4_CM_QUIRK_DISABLE_HPE_L1))
	{
		usb4_port_ctx_t* port = Usb4RouterGetAdapterPortByType(&usb4_cm_ctx->m_routers[0], USB4_portType_LANE1, 0);
    if (port)
    {
		  USB4_ASSERT(0 == Usb4PortConfigureDHP(port, 0));
    }
    else
    {
      USB4_ERROR_STACK(-1);
      return -1;
    }
	}
  return 0;
}

int Usb4CmToggleSwliOnDpInOut(usb4_cm_ctx_t* usb4_cm_ctx, USB4_portType portType)
{
    UINT32 i;
    usb4_port_ctx_t *pPort;

    if (USB4_portType_DP_IN == portType)
    {
        pPort = Usb4RouterGetAdapterPortByType(&usb4_cm_ctx->m_routers[0], USB4_portType_DP_IN, 0);
        if (NULL != pPort)
        {
            usb4_adp_dp_in_cs dpInCs;
            USB4_ASSERT(0 == Usb4PortSearchCapability(pPort, USB4_DP_ADAPTER_PORT_CAPABILITY, NULL));
            USB4_ASSERT(0 == Usb4PortReadCapability(pPort, (UINT8*)(&dpInCs), sizeof(dpInCs))); // TODO: AC verify whether it's Usb4PortReadCapability vs. Usb4PortReadCapabilityDword

            dpInCs.ADP_DP_CS_2.swli = 1;

            USB4_ASSERT(0 == Usb4PortWriteCapability(pPort, (UINT8*)(&dpInCs), sizeof(dpInCs))); // TODO: AC verify whether it's Usb4PortWriteCapability vs. Usb4PortWriteCapabilityDword

            {
                usb4_utils_timer timer;
                timer.m_source = USB4_TIMER_SOURCE_QTIMER;
                usb4_timer_Sleep_ms(&timer, 100);
            }

            dpInCs.ADP_DP_CS_2.swli = 0;

            USB4_ASSERT(0 == Usb4PortWriteCapability(pPort, (UINT8*)(&dpInCs), sizeof(dpInCs))); // TODO: AC verify whether it's Usb4PortWriteCapability vs. Usb4PortWriteCapabilityDword
        }
        return 0;
    }

    for (i = USB4_MAX_SUPPORTED_ROUTERS - 1; i > 0 /* Skip Host router */; i--)
    {
        UINT32 adapter;
        if (FALSE == Usb4RouterIsEnumerated(&usb4_cm_ctx->m_routers[i]))
        {
            continue;
        }
        adapter = 0;
        pPort = Usb4RouterGetAdapterPortByType(&usb4_cm_ctx->m_routers[i], portType, adapter);
        while (NULL != pPort)
        {
            if (USB4_HPE_IN == pPort->m_hotplug.adapter_first_action)
            {
                usb4_adp_dp_out_cs dpOutCs;
                USB4_ASSERT(0 == Usb4PortSearchCapability(pPort, USB4_DP_ADAPTER_PORT_CAPABILITY, NULL));
                USB4_ASSERT(0 == Usb4PortReadCapability(pPort, (UINT8*)(&dpOutCs), sizeof(dpOutCs))); // TODO: AC verify whether it's Usb4PortReadCapability vs. Usb4PortReadCapabilityDword

                dpOutCs.ADP_DP_CS_2.swli = 1;

                USB4_ASSERT(0 == Usb4PortWriteCapability(pPort, (UINT8*)(&dpOutCs), sizeof(dpOutCs))); // TODO: AC verify whether it's Usb4PortWriteCapability vs. Usb4PortWriteCapabilityDword

                {
                    usb4_utils_timer timer;
                    timer.m_source = USB4_TIMER_SOURCE_QTIMER;
                    usb4_timer_Sleep_ms(&timer, 100);
                }

                dpOutCs.ADP_DP_CS_2.swli = 0;

                USB4_ASSERT(0 == Usb4PortWriteCapability(pPort, (UINT8*)(&dpOutCs), sizeof(dpOutCs))); // TODO: AC verify whether it's Usb4PortWriteCapability vs. Usb4PortWriteCapabilityDword

            }
            adapter = pPort->m_Number + 1;
            pPort = Usb4RouterGetAdapterPortByType(&usb4_cm_ctx->m_routers[i], portType, adapter);
        }

    }

    return 0;
}


int Usb4CmTryLockCm(usb4_cm_ctx_t* usb4_cm_ctx)
{
    if (TRUE == usb4_cm_ctx->m_bCmTreadLocked)
    {
        return -1;
    }

    USB4_ASSERT(0 == Usb4PlatformLockMutex(usb4_cm_ctx->m_pQdrv->m_Platform));
    if (TRUE == usb4_cm_ctx->m_bCmTreadLocked)
    {
        USB4_ASSERT(0 == Usb4PlatformUnlockMutex(usb4_cm_ctx->m_pQdrv->m_Platform))
        return -1;
    }
    usb4_cm_ctx->m_bCmTreadLocked = TRUE;
    USB4_ASSERT(0 == Usb4PlatformUnlockMutex(usb4_cm_ctx->m_pQdrv->m_Platform));
    return 0;
}

int Usb4CmUnlockCm(usb4_cm_ctx_t* usb4_cm_ctx)
{
    usb4_cm_ctx->m_bCmTreadLocked = 0;
    return 0;
}


int Usb4CmConfigureCLx(usb4_cm_ctx_t* usb4_cm_ctx, USB4_CLx_mode CLxMode, boolean* pbIncompatible)
{
    UINT32 i, ri;
    UINT32 maxRouterIndex = 0;
    USB4_ASSERT(NULL != pbIncompatible);

    *pbIncompatible = FALSE;

    //Check for TBT3 Active cable - doesn't support CLx
    if ((USB4_CL0 != CLxMode)&&(USB4_PD_CABLE_TYPE_ACTIVE_TBT3 == usb4_cm_ctx->m_pdInfo.cable_type))
    {
        Usb4Log(USB4_LOG_CM, Usb4CmConfigureCLxWARNING__Params__ActiveTBT3CableDoesntSupportClx, 0);
        // USB4_LOG_WARNING("Warning: Active TBT3 cable doesn't support CLx\n");
        *pbIncompatible = TRUE;
        return 0;
    }

    while (0 != Usb4CmTryLockCm(usb4_cm_ctx))
    {};

    for (i = 0; i < USB4_MAX_SUPPORTED_ROUTERS; i++)
    {
        ri = USB4_MAX_SUPPORTED_ROUTERS - 1 - i;
        if (FALSE == Usb4RouterIsEnumerated(&usb4_cm_ctx->m_routers[ri]))
        {
            continue;
        }
        if(0 == maxRouterIndex)
        {
            maxRouterIndex = ri;
        }
        /* Use separate function to test compatibility before doing any actual changes */
        USB4_ASSERT(0 == Usb4RouterCheckCLxCompatibility(&usb4_cm_ctx->m_routers[ri], CLxMode, pbIncompatible));
        if (TRUE == *pbIncompatible)
        {
            USB4_ASSERT(0 == Usb4CmUnlockCm(usb4_cm_ctx));
            return 0;
        }
    }

    for (i = 0; i <= maxRouterIndex; i++)
    {
        ri = maxRouterIndex - i;
        USB4_ASSERT(0 == Usb4RouterConfigureCLx(&usb4_cm_ctx->m_routers[ri], CLxMode));
    }
    USB4_ASSERT(0 == Usb4CmUnlockCm(usb4_cm_ctx));
    return 0;
}

int Usb4CmWaitForCl0(usb4_cm_ctx_t* usb4_cm_ctx, UINT32 timeout_ms)
{
    usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;

    UINT32 mask = 0x0;
    UINT32 exp_mask = 0x1;
    UINT32 elapsed_ms = 0x0;
    usb4_port_ctx_t *downstreamPort0, *downstreamPort1;
    USB4_portState portState;

    USB4_ASSERT(0 != timeout_ms);

    downstreamPort0 = Usb4RouterGetAdapterPortByType(&usb4_cm_ctx->m_routers[0], USB4_portType_LANE0, 0);
    downstreamPort1 = Usb4RouterGetAdapterPortByType(&usb4_cm_ctx->m_routers[0], USB4_portType_LANE1, 0);
    USB4_ASSERT(NULL != downstreamPort0);
    USB4_ASSERT(NULL != downstreamPort1);

    USB4_ASSERT(0 == usb4_timer_Start(&timer));

    exp_mask = (0x2 == usb4_cm_ctx->m_pParams->numLanes) ? 0x3 : 0x1;
    while ((mask != exp_mask) && (elapsed_ms < timeout_ms))
    {
        if (0 == Usb4CmTryLockCm(usb4_cm_ctx))
        {
          USB4_ASSERT(0 == Usb4PortGetPortState(downstreamPort0, &portState));
          if (USB4_portState_CL0 == portState)
          {
              mask |= 0x1;
          }
          if (0x2 == usb4_cm_ctx->m_pParams->numLanes)
          {
              USB4_ASSERT(0 == Usb4PortGetPortState(downstreamPort1, &portState));
              if (USB4_portState_CL0 == portState)
              {
                  mask |= 0x2;
              }
          }
          USB4_ASSERT(0 == Usb4CmUnlockCm(usb4_cm_ctx));
        }
        if (0 != usb4_timer_GetElapsed_ms(&timer, &elapsed_ms))
        {
            USB4_ERROR_STACK(-1);
            return -1;
        }
    }

    if (mask != exp_mask)
    {
        USB4_ERROR_STACK_MSG(-1, "failed to reach CL0");
        return -1;
    }

    return 0;
}
/* --------------------------------------------------------------------------
 * Static Functions
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Global Functions
 *--------------------------------------------------------------------------*/

