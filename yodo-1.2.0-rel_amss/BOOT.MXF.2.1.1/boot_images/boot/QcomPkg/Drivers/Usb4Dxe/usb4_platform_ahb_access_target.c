/**---------------------------------------------------------------------------
 *   @file        usb4_platform_AHB_access_target.c
 *
 *   @brief   This function containf all Host router operations that are done through AHB,
 *            bypassing the usual enumeration flow access
 *
 *   Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------------------*/
#include <Usb4Log.h>
#include <Usb4Utils.h>
#include "usb4_hwio.h"
#include "msmhwio_usb4.h"
#include "pd_hwioreg_dut.h" // GE registers
#include "usb4_platform_ahb_access.h"

//#include "VVDRV_usb4_ring_iface.h"

// #include "VVDRV_usb4_port.h"
// #include "VVHAL_usb4_logger.h"   // Logging utilities
// #include "VVHAL_usb4_timer.h"
// #include "VVHAL_usb4_utils.h"
// #include "VVHAL_usb4_mem.h"
// #include <string.h>
// #include "VVHAL_usb4_platform_target.h"
// #include "VVHAL_usb4_platform_ahb_access_target.h"
// 
// #include "VVHAL_usb4_hwio.h"
// #include "VVHAL_usb4_hwioreg_core.h"

#ifdef RUMI
#include "msmhwio_tcsr.h"
#endif /* RUMI */

#ifdef SOC_TLMM
// TODO: AC need to port
// #include "msmhwio_tlmm.h"
#endif /* SOC_TLMM */

#ifdef USB4_COMPILING_USB31_SUITE
#include "HAL_ssusb_impl.h"
#ifdef __cplusplus
extern "C" {
#endif

void HAL_ssusb_SetVbusIndication(UINT8 instance, boolean state);

#ifdef __cplusplus
}
#endif
#endif /* USB4_COMPILING_USB31_SUITE */

/* --------------------------------------------------------------------------
 * Macros / Types
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Static Variables
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Global Variables
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Static Functions
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Global Functions
 *--------------------------------------------------------------------------*/

void Usb4PlatformAhbAccessInit(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, UINT8* coreBaseAddress, UINT32 USBAP_CFG_RXTERM_BACKDOOR_STS)
{
    usb4_platform_ahb_access_ctx->m_coreBaseAddress = coreBaseAddress;
    usb4_platform_ahb_access_ctx->m_USBAP_CFG_RXTERM_BACKDOOR_STS = USBAP_CFG_RXTERM_BACKDOOR_STS;
}


void Usb4PlatformAhbAccessDeInit(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx)
{
}


int Usb4PlatformAhbAccess_disable_lane1(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx)
{
    UINT8* base;
    
    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);
    
    base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + LANE_1_NULL_REG_BASE_OFFS;
    HWIO_OUTXF(base, USB4_L1_LANE_ADP_CS_1_STANDARD, LD, 0x1); // 0x4818401C ?
    
    return 0;
}

int Usb4PlatformAhbAccess_lane0_wait_for_cl0(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, UINT32 timeout_ms)
{
    int rc = 0;
    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);
    USB4_WHILE_WITH_TIMEOUT (2 != HWIO_INXF(usb4_platform_ahb_access_ctx->m_coreBaseAddress + LANE_0_NULL_REG_BASE_OFFS, USB4_L0_LANE_ADP_CS_1_STANDARD, ADAPTER_STATE),
                             timeout_ms, rc)
    USB4_ASSERT(0 == rc);
    return 0;
}

int Usb4PlatformAhbAccess_configure_L0_path(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, UINT32 path_index, usb4_pathN_cs* pPath)
{
    UINT32 cs1 = *(UINT32*)(&pPath->PATH_CS_1); // TODO: AC double check this pointer usage
    UINT32 cs0 = *(UINT32*)(&pPath->PATH_CS_0);

    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);
    HWIO_OUTXI(usb4_platform_ahb_access_ctx->m_coreBaseAddress + LANE_0_NULL_REG_BASE_OFFS, USB4_L0_PATH_n_CS_1_STANDARD,
            path_index, cs1);
    if (1 == pPath->PATH_CS_0.Valid)
    {                           
        usb4_utils_timer timer;
        timer.m_source = USB4_TIMER_SOURCE_QTIMER;
        pPath->PATH_CS_0.Valid = 0;
        HWIO_OUTXI(usb4_platform_ahb_access_ctx->m_coreBaseAddress + LANE_0_NULL_REG_BASE_OFFS, USB4_L0_PATH_n_CS_0_STANDARD,
                            path_index, cs0);
        usb4_timer_Sleep_ms(&timer, 1);
        pPath->PATH_CS_0.Valid = 1;
        HWIO_OUTXI(usb4_platform_ahb_access_ctx->m_coreBaseAddress + LANE_0_NULL_REG_BASE_OFFS, USB4_L0_PATH_n_CS_0_STANDARD,
                            path_index, cs0);
    }
    else
    {
        HWIO_OUTXI(usb4_platform_ahb_access_ctx->m_coreBaseAddress + LANE_0_NULL_REG_BASE_OFFS, USB4_L0_PATH_n_CS_0_STANDARD,
            path_index, cs0);
    }
    return 0;
}

int Usb4PlatformAhbAccess_configure_dpinap_aux_path(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, usb4_pathN_cs* pPath)
{
    UINT8* base;
    UINT32 cs1 = *(UINT32*)(&pPath->PATH_CS_1);
    UINT32 cs0 = *(UINT32*)(&pPath->PATH_CS_0);
    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);
    
    base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + DP_IN_0_ADAPTER_PORT_REG_BASE_OFFS;
    
    // TODO should use #port->WriteSegment() instead
    HWIO_OUTX(base, USB4_DPINAP_PATH_CS_1_AUX_STANDARD, cs1);
    HWIO_OUTX(base, USB4_DPINAP_PATH_CS_0_AUX_STANDARD, cs0);
    HWIO_OUTX(base, USB4_DPINAP_ADP_DP_CS_0_STANDARD, 0xC0090400);

    return 0;
}



int Usb4PlatformAhbAccess_configure_pcieap_ep_mode(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, boolean bEp)
{
    UINT8* base;
    UINT32 val = 0;

    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);

    base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + PCIEAP_CONFIG_PROP_REG_BASE_OFFS;
    val = (TRUE == bEp) ? 0x1 : 0x0;
    HWIO_OUTXF(base, USB4_PCIE_AP_CFG, PCIE_EP_MODE, val);

    return 0;
}

int Usb4PlatformAhbAccess_configure_pcieap_path(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, usb4_pathN_cs* pPath, 
                                                                 boolean bEp)
{
    UINT8* base;
    UINT32 cs1 = *(UINT32*)(&pPath->PATH_CS_1);
    UINT32 cs0 = *(UINT32*)(&pPath->PATH_CS_0);
    UINT32 val = 0;
    
    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);
    
    base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + PCIEAP_CONFIG_PROP_REG_BASE_OFFS;
    val = (TRUE == bEp) ? 0x1 : 0x0;
    HWIO_OUTXF(base, USB4_PCIE_AP_CFG, PCIE_EP_MODE, val);
    
    /* Experiment for Eran: */
    base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + PCIE_AP_PROP_REG_BASE_OFFS;
    HWIO_OUTXF(base, USB4_PCIE_AP_TX_CFG, WAIT_DLLP_CNT, 0);

    // Before setting up a PCIe Tunneling Path in a Device Router, a Connection 
    // Manager needs to set the PCIe Tunneling On field to 1b and the 
    // Configuration Valid bit to 1b in Router Configuration Space and poll 
    // the Configuration Ready field until it is set to 1b by the Device Router.
    //  A Host Router shall ignore this bit.
    // base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + ROUTER_CONFIG_REG_BASE_OFFS;
    // HWIO_OUTXF(base, USB4_RC_ROUTER_CS_5_STANDARD, PTO, 0x1);
    
    // HWIO_OUTXF(base, USB4_RC_ROUTER_CS_5_STANDARD, CV, 0x1); 
    //  A Host Router shall not set CR bit to 1b.
    
    // A Connection Manager needs to configure all of the Path Configuration Spaces for a PCIe
    // Path before setting the Path Enable bit to 1b in the PCIe Adapters at either end of the Path.
    base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + PCIE_ADAPTER_PORT_REG_BASE_OFFS;
    
    // TODO should use #port->WriteSegment() instead
    HWIO_OUTX(base, USB4_PCIE_AP_PATH_CS_1_STANDARD, cs1);
    // TODO maybe need to set valid field in a different write
    if( 1 == pPath->PATH_CS_0.Valid)
    {
        usb4_utils_timer timer;
        timer.m_source = USB4_TIMER_SOURCE_QTIMER;
        pPath->PATH_CS_0.Valid = 0;
        HWIO_OUTX(base, USB4_PCIE_AP_PATH_CS_0_STANDARD, cs0);
        usb4_timer_Sleep_ms(&timer, 1);
        pPath->PATH_CS_0.Valid = 1;
        HWIO_OUTX(base, USB4_PCIE_AP_PATH_CS_0_STANDARD, cs0);
    }
    else
    {
        HWIO_OUTX(base, USB4_PCIE_AP_PATH_CS_0_STANDARD, cs0);
    }
    
    // CM 0.7 5.2.1 path setup step 3:
    // The Connection Manager sets the Enable bit to 1b in the Port Configuration
    // Spaces of both Adapter Ports, which allows the Adapter Ports to send and
    // receive Transport Layer Packets on the Path.
    HWIO_OUTXF(base, USB4_PCIE_AP_ADP_PCIE_CS_0_STANDARD, PE, 0x1);
    
    
    return 0;
}

int Usb4PlatformAhbAccess_configure_hiaap_path(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, usb4_pathN_cs* pPath)
{
    UINT8* base;
    UINT32 cs1 = *(UINT32*)(&pPath->PATH_CS_1);
    UINT32 cs0 = *(UINT32*)(&pPath->PATH_CS_0);
    //UINT32 val = 0;
    
    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);
    
    base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + HOST_INTERFACE_AP_REG_BASE_OFFS;

    // Before setting up a PCIe Tunneling Path in a Device Router, a Connection 
    // Manager needs to set the PCIe Tunneling On field to 1b and the 
    // Configuration Valid bit to 1b in Router Configuration Space and poll 
    // the Configuration Ready field until it is set to 1b by the Device Router.
    //  A Host Router shall ignore this bit.
    // base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + ROUTER_CONFIG_REG_BASE_OFFS;
    // HWIO_OUTXF(base, USB4_RC_ROUTER_CS_5_STANDARD, PTO, 0x1);
    
    // HWIO_OUTXF(base, USB4_RC_ROUTER_CS_5_STANDARD, CV, 0x1); 
    //  A Host Router shall not set CR bit to 1b.
    
    // A Connection Manager needs to configure all of the Path Configuration Spaces for a PCIe
    // Path before setting the Path Enable bit to 1b in the PCIe Adapters at either end of the Path.
    base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + HOST_INTERFACE_AP_REG_BASE_OFFS;
    
    // TODO should use #port->WriteSegment() instead
    HWIO_OUTX(base, USB4_HI_PATH_CS_1_1_STANDARD, cs1);
    
    //need to set valid field in a different write due to known CR
    if( 1 == pPath->PATH_CS_0.Valid)
    {
        usb4_utils_timer timer;
        timer.m_source = USB4_TIMER_SOURCE_QTIMER;
        pPath->PATH_CS_0.Valid = 0;
        HWIO_OUTX(base, USB4_HI_PATH_CS_0_1_STANDARD, cs0);
        usb4_timer_Sleep_ms(&timer, 1);
        pPath->PATH_CS_0.Valid = 1;
        HWIO_OUTX(base, USB4_HI_PATH_CS_0_1_STANDARD, cs0);
    }
    else
    {
        HWIO_OUTX(base, USB4_HI_PATH_CS_0_1_STANDARD, cs0);
    }
    
    // CM 0.7 5.2.1 path setup step 3:
    // The Connection Manager sets the Enable bit to 1b in the Port Configuration
    // Spaces of both Adapter Ports, which allows the Adapter Ports to send and
    // receive Transport Layer Packets on the Path.
    // HWIO_OUTXF(base, USB4_PCIE_AP_ADP_PCIE_CS_0_STANDARD, PE, 0x1);
    
    return 0;
}

int Usb4PlatformAhbAccess_configure_usbap_usb4_mode(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx)
{
    UINT8* base;

    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);

#if defined(USB4_COMPILING_GEN_EMU)
    base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + GE_DUT_USER_REGS_REG_BASE_OFFS;
    HWIO_OUTXF(base, GE_DUT_USB4_CTRL_REG, USB31_CTRL_MODE, 1); // Configure CIO mode for usb4 controller
#else
    base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + USBAP_CONFIG_PROP_REG_BASE_OFFS;
    HWIO_OUTXF(base, USB4_USBAP_CFG_USB4_MODE, USB4_MODE, 1); // Configure CIO mode of USBAP
#endif /* !USB4_COMPILING_GEN_EMU */

    return 0;
}

int Usb4PlatformAhbAccess_PrepareUSB3Sleep(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx)
{
    UINT8* base;
    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);
    base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + USBAP_CONFIG_PROP_REG_BASE_OFFS;

    usb4_platform_ahb_access_ctx->m_USBAP_CFG_RXTERM_BACKDOOR_STS = HWIO_INXF(base, USB4_USBAP_CFG_RXTERM_BACKDOOR_STS, RX_TERM_STS);

    HWIO_OUTXF(base, USB4_USBAP_CFG_TXDETECTRX_STS, TXDETECTRX, 0x1);      /* Clear RX.Detect status */
    while(1!= HWIO_INXF(base, USB4_USBAP_CFG_TXDETECTRX_STS, TXDETECTRX))
        ; /* poll of rRxDetect status */

    return 0;
}

int Usb4PlatformAhbAccess_PrepareUSB3Wakeup(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx)
{
    UINT8* base;

    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);
    base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + USBAP_CONFIG_PROP_REG_BASE_OFFS;

    HWIO_OUTXF(base, USB4_USBAP_CFG_RXTERM_BACKDOOR_CTRL, RX_TERM_VALUE, usb4_platform_ahb_access_ctx->m_USBAP_CFG_RXTERM_BACKDOOR_STS);
    HWIO_OUTXF(base, USB4_USBAP_CFG_PHYSTATUS_EN, PHYSTATUS_EN, 0x1);  /* USB4_USBAP_CFG_PHYSTATUS_EN.PHYSTATUS_EN=1 */   

    return 0;
}

// TODO: AC Deprecated
int Usb4PlatformAhbAccess_AssertDeassertUSBReset(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx)
{
    UINT8* base;
    usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;
    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);
    base = usb4_platform_ahb_access_ctx->m_coreBaseAddress;

    /* reset the Controller and USBAP */
    HWIO_OUTXF(base + USBAP_CONFIG_PROP_REG_BASE_OFFS, USB4_USBAP_CFG_SYNC_RST, SYS_CLK_SYNC_RST_USB3, 0x1);      /* Assert USB4_USBAP_CFG_SYNC_RST */
    HWIO_OUTXF(base + GE_DUT_USER_REGS_REG_BASE_OFFS, GE_DUT_RESET_REG, USB4_USB_PIPE_ARES, 0x1);                /*  GE_DUT_RESET_REG.USB4_USB_PIPE_ARES */ 
    HWIO_OUTXF(base + GE_DUT_USER_REGS_REG_BASE_OFFS, GE_DUT_RESET_REG, USB4_CTRL_PIPE_ARES, 0x1);               /*  GE_DUT_RESET_REG.USB4_USB_PIPE_ARES */
    //HWIO_OUTXF(base + GE_DUT_USER_REGS_REG_BASE_OFFS, GE_DUT_USB31_RESET_REG, MASTER_ARES, 0x1);                 /* Assert GE_DUT_USB31_RESET.MASTER_ARES */
    //HWIO_OUTXF(base + GE_DUT_USER_REGS_REG_BASE_OFFS, GE_DUT_USB31_RESET_REG, SLEEP_ARES, 0x1);                  /* Assert GE_DUT_USB31_RESET.MASTER_ARES */
#if defined(RUMI)
    USB4_ERROR_STACK_MSG(-1, "cont without setting USB4_USBAP_CFG_PHYSTATUS_EN.PHYSTATUS_EN");
#else /* !RUMI */
    HWIO_OUTXF(base + USBAP_CONFIG_PROP_REG_BASE_OFFS, USB4_USBAP_CFG_PHYSTATUS_EN, PHYSTATUS_EN, 0x1);           /* USB4_USBAP_CFG_PHYSTATUS_EN.PHYSTATUS_EN */
#endif /* !RUMI */
    usb4_timer_Sleep_ms(&timer, 10);
    //HWIO_OUTXF(base + GE_DUT_USER_REGS_REG_BASE_OFFS, GE_DUT_USB31_RESET_REG, SLEEP_ARES, 0x0);                 /* Assert GE_DUT_USB31_RESET.MASTER_ARES */
    //HWIO_OUTXF(base + GE_DUT_USER_REGS_REG_BASE_OFFS, GE_DUT_USB31_RESET_REG, MASTER_ARES, 0x0);                /* Assert GE_DUT_USB31_RESET.MASTER_ARES */
    HWIO_OUTXF(base + GE_DUT_USER_REGS_REG_BASE_OFFS, GE_DUT_RESET_REG, USB4_CTRL_PIPE_ARES, 0x0);              /*  GE_DUT_RESET_REG.USB4_USB_PIPE_ARES */
    HWIO_OUTXF(base + GE_DUT_USER_REGS_REG_BASE_OFFS, GE_DUT_RESET_REG, USB4_USB_PIPE_ARES, 0x0);               /*  GE_DUT_RESET_REG.USB4_USB_PIPE_ARES */
    HWIO_OUTXF(base + USBAP_CONFIG_PROP_REG_BASE_OFFS, USB4_USBAP_CFG_SYNC_RST, SYS_CLK_SYNC_RST_USB3, 0x0);      /* Assert USB4_USBAP_CFG_SYNC_RST */
    usb4_timer_Sleep_ms(&timer, 10);

    return 0;
}

int Usb4PlatformAhbAccess_configure_usbap_device_mode(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, boolean bDevice)
{
    UINT8* base;
    UINT32 val = 0;

    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);

    base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + USBAP_CONFIG_PROP_REG_BASE_OFFS;

    val = (TRUE == bDevice) ? 0x1 : 0x0;    
    HWIO_OUTXF(base, USB4_USBAP_CFG_USB3_CTRL_MODE, USB3_CTRL_DEVICE_MODE, val); /* use it to enable USB AP CONFIG PROP configuration */
    
    if(TRUE != bDevice)
    {
       //  A Host Router shall not set CR bit to 1b. 
        //while(1 != HWIO_INXF(usb4_platform_ahb_access_ctx->m_coreBaseAddress + ROUTER_CONFIG_REG_BASE_OFFS, USB4_RC_ROUTER_CS_6_STANDARD, CR, 0x1));

        // A Connection Manager needs to configure all of the Path Configuration Spaces for a USB
        // Path before setting the Path Enable bit to 1b in the USB Adapters at either end of the Path.
        base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + USB_ADAPTER_PORT_REG_BASE_OFFS; 
        
        /* CM should write to the SCALE field. For device router this should be Hardwired to 0 */
       // HWIO_OUTXF(base, USB4_USB_AP_ADP_USB_CS_3_STANDARD, SCALE, 0x1); 
       // HWIO_OUTXF(base, USB4_USB_AP_ADP_USB_CS_2_STANDARD, CMR, 0x1);
        
        /* CM should write to Allocated bandwidth field for ISoC transfers. This field shall be hardwired to 0 for a Device Router */
       /* HWIO_OUTXF(base, USB4_USB_AP_ADP_USB_CS_2_STANDARD, ALLOCATED_DOWNSTREAM_BANDWIDTH, 0x1);
        HWIO_OUTXF(base, USB4_USB_AP_ADP_USB_CS_2_STANDARD, ALLOCATED_UPSTREAM_BANDWIDTH, 0x1);
        HWIO_OUTXF(base, USB4_USB_AP_ADP_USB_CS_2_STANDARD, CMR, 0x0); */
    }
    else
    {
        base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + USB_ADAPTER_PORT_PROP_REG_BASE_OFFS; 
        
        /* Write the CFG_DW2_FIX_VALUES_PROP.ADAPTER_TYPE_SUB_TYPE=1 for Path Manager to work */
        HWIO_OUTX(base, USBAP_STNDRD_BASIC_CFG_DW2_FIX_VALUES_PROP, 0x200101); 
    }

    return 0;
}

int Usb4PlatformAhbAccess_configure_usbap_path(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, usb4_pathN_cs* pPath, 
                                                                boolean bEnable)
{
    UINT8* base;
    UINT32 cs1 = *(UINT32*)(&pPath->PATH_CS_1);
    UINT32 cs0 = *(UINT32*)(&pPath->PATH_CS_0);

    // Before setting up a USB Tunneled Path in a Device Router, a Connection 
    // Manager needs to set the USB Tunneling ON field to 1b and the 
    // Configuration Valid bit to 1b in Router Configuration Space and poll 
    // the Configuration Ready field until it is set to 1b by the Device Router.
    //  A Host Router shall ignore this bit.
    // base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + ROUTER_CONFIG_REG_BASE_OFFS;
    // HWIO_OUTXF(base, USB4_RC_ROUTER_CS_5_STANDARD, UTO, 0x1);
    
    // HWIO_OUTXF(base, USB4_RC_ROUTER_CS_5_STANDARD, CV, 0x1); 
    //  A Host Router shall not set CR bit to 1b.
    
    // A router shall set HCI bit for USB Host controller implementation
    //HWIO_OUTXF(base, USB4_RC_ROUTER_CS_6_STANDARD, HCI, 0x1);

    // A Connection Manager needs to configure all of the Path Configuration Spaces for a USB
    // Path before setting the Path Enable bit to 1b in the USB Adapters at either end of the Path.
    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);
    base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + USB_ADAPTER_PORT_REG_BASE_OFFS;
    
    // TODO should use #port->WriteSegment() instead
    HWIO_OUTX(base, USB4_USB_AP_PATH_CS_1_STANDARD, cs1);
    
    //need to set valid field in a different write due to known CR
    if( 1 == pPath->PATH_CS_0.Valid)
    {
        usb4_utils_timer timer;
        timer.m_source = USB4_TIMER_SOURCE_QTIMER;
        pPath->PATH_CS_0.Valid = 0;
        HWIO_OUTX(base, USB4_USB_AP_PATH_CS_0_STANDARD, cs0);
        usb4_timer_Sleep_ms(&timer, 1);
        pPath->PATH_CS_0.Valid = 1;
        HWIO_OUTX(base, USB4_USB_AP_PATH_CS_0_STANDARD, cs0);
    }
    else
    {
        HWIO_OUTX(base, USB4_USB_AP_PATH_CS_0_STANDARD, cs0);
    }
      
    // CM 0.7 5.5.1 path setup step 3:
    // The Connection Manager sets the Path Enable & Valid bit to 1b in Port Configuration
    // Spaces of both Adapter Ports, which allows the Adapter Ports to send and
    // receive Transport Layer Packets on the Path.
    
    HWIO_OUTXF(base, USB4_USB_AP_ADP_USB_CS_0_STANDARD, VALID, 0x1);

    HWIO_OUTXF(base, USB4_USB_AP_ADP_USB_CS_0_STANDARD, PATH_ENABLE, bEnable);

    return 0;
}


int Usb4PlatformAhbAccess_USB3_VBUS_on_off(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, UINT32 CoreId, boolean State)
{
    UINT8* base;    
    // Before setting up a USB Tunneled Path in a Device Router, a Connection 
    // Manager needs to set the USB Tunneling ON field to 1b and the 
    // Configuration Valid bit to 1b in Router Configuration Space and poll 
    // the Configuration Ready field until it is set to 1b by the Device Router.
    //  A Host Router shall ignore this bit.
    // base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + ROUTER_CONFIG_REG_BASE_OFFS;
    // HWIO_OUTXF(base, USB4_RC_ROUTER_CS_5_STANDARD, UTO, 0x1);
    
    // HWIO_OUTXF(base, USB4_RC_ROUTER_CS_5_STANDARD, CV, 0x1); 
    //  A Host Router shall not set CR bit to 1b.
    
    // A router shall set HCI bit for USB Host controller implementation */
    //HWIO_OUTXF(base, USB4_RC_ROUTER_CS_6_STANDARD, HCI, 0x1);

    // A Connection Manager needs to configure all of the Path Configuration Spaces for a USB
    // Path before setting the Path Enable bit to 1b in the USB Adapters at either end of the Path.
    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);
    base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + USB_ADAPTER_PORT_REG_BASE_OFFS;
    
    // CM 0.7 5.5.1 path setup step 3:
    // The Connection Manager sets the Path Enable & Valid bit to 1b in Port Configuration
    // Spaces of both Adapter Ports, which allows the Adapter Ports to send and
    // receive Transport Layer Packets on the Path.

    HWIO_OUTXF(base, USB4_USB_AP_ADP_USB_CS_0_STANDARD, VALID, State);
    HWIO_OUTXF(base, USB4_USB_AP_ADP_USB_CS_0_STANDARD, PATH_ENABLE, State);

#ifdef USB4_COMPILING_USB31_SUITE
    boolean Vbus_State;  

    Vbus_State = State ? TRUE: FALSE;  
    HAL_ssusb_SetVbusIndication(CoreId, Vbus_State);
#endif  /* USB4_COMPILING_USB31_SUITE */

    return 0;
}


int Usb4PlatformAhbAccess_USB4_USBAP_mask_credits(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, boolean Credit)
{
    UINT8* base;    
    int credit_mask;

    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);
    base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + PG_PROP_REG_BASE_OFFS;
    
    credit_mask = Credit ? 0x0:0x2;
    HWIO_OUTX(base, USB4_PGRX_MASK_BUFFER, credit_mask);
    
    return 0;
}

int Usb4PlatformAhbAccessAssertUSBAPReset(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, boolean assert)
{
    UINT8* base;
    //VVHAL_usb4_timer timer(USB4_TIMER_SOURCE_QTIMER);
  
    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);
  
    base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + USBAP_CONFIG_PROP_REG_BASE_OFFS;
    HWIO_OUTXF(base, USB4_USBAP_CFG_SYNC_RST, SYS_CLK_SYNC_RST_USB3, assert);
  
     return 0;
}

int Usb4PlatformAhbAccessUSBAPPHYStatusEnable(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, boolean bEnable)
{
    UINT8 *base;

    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);

    base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + USBAP_CONFIG_PROP_REG_BASE_OFFS;
    HWIO_OUTXF(base, USB4_USBAP_CFG_PHYSTATUS_EN, PHYSTATUS_EN, bEnable); /* USB4_USBAP_CFG_PHYSTATUS_EN.PHYSTATUS_EN */

    return 0;
}


int Usb4PlatformAhbAccess_USB4_USBAP_BUF_access(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, boolean R_W)
{
    UINT8* base;    
    UINT32 RX_RD_DATA_127_96;
    UINT32 RX_RD_DATA_95_64; 
    UINT32 RX_RD_DATA_63_32; 
    UINT32 RX_RD_DATA_31_0;
    
    UINT32 TX_WR_DATA_127_96 = 0x35363738;
    UINT32 TX_WR_DATA_95_64 = 0x31323334;
    UINT32 TX_WR_DATA_63_32 = 0x25262728;
    UINT32 TX_WR_DATA_31_0 = 0x21222324;

    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);
    base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + USB_ADAPTER_PORT_PROP_REG_BASE_OFFS;
    
    HWIO_OUTXF(base, USBAP_TXBUF_WR_DATA_31_0_PROP, TXBUFF_WR_DATA_31_0, TX_WR_DATA_31_0);
    HWIO_OUTXF(base, USBAP_TXBUF_WR_DATA_63_32_PROP, TXBUFF_WR_DATA_63_32, TX_WR_DATA_63_32);
    HWIO_OUTXF(base, USBAP_TXBUF_WR_DATA_95_64_PROP, TXBUFF_WR_DATA_95_64, TX_WR_DATA_95_64);
    HWIO_OUTXF(base, USBAP_TXBUF_WR_DATA_127_96_PROP, TXBUFF_WR_DATA_127_96, TX_WR_DATA_127_96);

    HWIO_OUTXF(base, USBAP_TXBUF_CTRL_PROP, TXBUFF_WR_RDN, R_W);// Write the vlues to TX BUFF
    while(1!= HWIO_INXF(base, USBAP_TXBUF_STS_PROP, TXBUFF_ACCESS_COMPL));

    HWIO_OUTXF(base, USBAP_TXBUF_CTRL_PROP, TXBUFF_WR_RDN, ~R_W);// Read the values form TX BUFF

    RX_RD_DATA_31_0   = HWIO_INXF(base, USBAP_TXBUF_RD_DATA_31_0_PROP, TXBUFF_RD_DATA_31_0);
    RX_RD_DATA_63_32  = HWIO_INXF(base, USBAP_TXBUF_RD_DATA_63_32_PROP, TXBUFF_RD_DATA_63_32);
    RX_RD_DATA_95_64  = HWIO_INXF(base, USBAP_TXBUF_RD_DATA_95_64_PROP, TXBUFF_RD_DATA_95_64);
    RX_RD_DATA_127_96 = HWIO_INXF(base, USBAP_TXBUF_RD_DATA_127_96_PROP, TXBUFF_RD_DATA_127_96);

    while(1!= HWIO_INXF(base, USBAP_TXBUF_STS_PROP, TXBUFF_ACCESS_COMPL));

    USB4_ASSERT_MSG(TX_WR_DATA_31_0 == RX_RD_DATA_31_0,"USBAP RX & TX [31:0] BUF doesn't match");
    USB4_ASSERT_MSG(TX_WR_DATA_63_32 == RX_RD_DATA_63_32,"USBAP RX & TX [63:32] BUF doesn't match");
    USB4_ASSERT_MSG(TX_WR_DATA_95_64 == RX_RD_DATA_95_64,"USBAP RX & TX [95:64] BUF doesn't match");
    USB4_ASSERT_MSG(TX_WR_DATA_127_96 == RX_RD_DATA_127_96,"USBAP RX & TX [127:96] BUF doesn't match");
    
    return 0;
}

int Usb4PlatformAhbAccess_enable_usbap_XHCI_BW_negotiation(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, boolean CMR, UINT32 scale, UINT32 BW)
{
    UINT8* base;
    UINT32 val=0;
    UINT32 Consumed_UP_BW, Consumed_DN_BW = 0;

    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);
    base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + USB_ADAPTER_PORT_REG_BASE_OFFS;
    
    val = CMR ? 1:0;
    HWIO_OUTXF(base, USB4_USB_AP_ADP_USB_CS_3_STANDARD, SCALE, scale); 
    HWIO_OUTXF(base, USB4_USB_AP_ADP_USB_CS_2_STANDARD, CMR, val);
    
    if(1 == HWIO_INXF(base, USB4_USB_AP_ADP_USB_CS_1_STANDARD, XCA))
    {    
      
      Consumed_UP_BW = HWIO_INXF(base, USB4_USB_AP_ADP_USB_CS_1_STANDARD, CONSUMED_UPSTREAM_BANDWIDTH);
      Consumed_DN_BW = HWIO_INXF(base, USB4_USB_AP_ADP_USB_CS_1_STANDARD, CONSUMED_DOWNSTREAM_BANDWIDTH);
      /* CM should write to Allocated bandwidth field for ISoC transfers */
      //HWIO_OUTXF(base, USB4_USB_AP_ADP_USB_CS_2_STANDARD, ALLOCATED_DOWNSTREAM_BANDWIDTH, BW);
      //HWIO_OUTXF(base, USB4_USB_AP_ADP_USB_CS_2_STANDARD, ALLOCATED_UPSTREAM_BANDWIDTH, BW);

      HWIO_OUTX(base, USB4_USB_AP_ADP_USB_CS_2_STANDARD, 0x00080080);
      while(0 != HWIO_INXF(base, USB4_USB_AP_ADP_USB_CS_1_STANDARD, XCA));

      USB4_ASSERT_MSG(Consumed_UP_BW <= BW, "Consumed upstream BW is per BW negotiation of Allocated Upstream BW");
      USB4_ASSERT_MSG(Consumed_DN_BW <= BW, "Consumed downstream BW is per BW negotiation of Allocated Downstream BW");
    }

    return 0;
}

int Usb4PlatformAhbAccess_set_usbap_local_rxterm_Req(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, UINT8 RxTerm)
{
    UINT8* base;
    UINT32 val=0;

    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);

    base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + USB_ADAPTER_PORT_PROP_REG_BASE_OFFS;
    HWIO_OUTXF(base, USBAP_NUM_RXTERM_REQ_PROP, NUM_RXTERM_REQ, RxTerm);
 
    val = HWIO_INXF(base, USBAP_NUM_RXTERM_REQ_PROP, NUM_RXTERM_REQ);
    USB4_ASSERT_MSG(val == RxTerm,"USBAP RX Term value is not set correctly");
   
    return 0;
}

UINT32 Usb4PlatformAhbAccess_get_usbap_num_DP_packets(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, boolean Pkt_byte)
{
    UINT8* base, val;
    UINT8 link_rate = 0;

    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);

    base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + USB_ADAPTER_PORT_REG_BASE_OFFS;
    while(1 != HWIO_INXF(base, USB4_USB_AP_ADP_USB_CS_4_STANDARD, ULV));
    
    link_rate = HWIO_INXF(base, USB4_USB_AP_ADP_USB_CS_4_STANDARD, ACTUAL_LINK_RATE); // Get USBAP link rate 

    switch(link_rate)
    {
      case 0: USB4_ASSERT_MSG(link_rate==0,"USB3 Tunneled Link Rate is not 10Gbps");
      break;

      case 1: USB4_ASSERT_MSG(link_rate==1,"USB3 Tunneled Link Rate is not 20Gbps");
      break;

      default:
      break;
    }

    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);
    base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + USB_ADAPTER_PORT_PROP_REG_BASE_OFFS;

    if(Pkt_byte)
    {
       val =  HWIO_INXF(base, USBAP_NUM_USB3DP_PKT_TO_CTRL_PROP, NUM_USB3DP_PKT_TO_CTRL);
    }
    else
    {
       val =  HWIO_INXF(base, USBAP_NUM_USB3DP_BYTES_TO_CTRL_PROP, NUM_USB3DP_BYTES_TO_CTRL);
    }
          
    return val;
}

int Usb4PlatformAhbAccess_get_usbap_link_rate(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx)
{
    UINT8* base;
    UINT8 link_rate = 0;

    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);

    base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + USB_ADAPTER_PORT_REG_BASE_OFFS;
    while(1 != HWIO_INXF(base, USB4_USB_AP_ADP_USB_CS_4_STANDARD, ULV));
    
    link_rate = HWIO_INXF(base, USB4_USB_AP_ADP_USB_CS_4_STANDARD, ACTUAL_LINK_RATE); // Get USBAP link rate 

    switch(link_rate)
    {
      case 0: USB4_ASSERT_MSG(link_rate==0,"USB3 Tunneled Link Rate is not 10Gbps");
      break;

      case 1: USB4_ASSERT_MSG(link_rate==1,"USB3 Tunneled Link Rate is not 20Gbps");
      break;

      default:
      break;
    }
       
    return 0;
}

int Usb4PlatformAhbAccess_configure_HPE_retransmission_interval(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, UINT32 interval_ms)
{
    UINT8* base;
    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);
    
    base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + ROUTER_CONFIG_REG_BASE_OFFS;
    HWIO_OUTXF(base, USB4_RC_ROUTER_CS_4_STANDARD, NOTIFICATION_TIMEOUT, interval_ms);
    return 0;
}

int Usb4PlatformAhbAccess_pcieap_set_perst(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, UINT32 val)
{
    UINT8* base;
    UINT32 status;

    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);

    base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + PCIE_AP_PROP_REG_BASE_OFFS;
    status = 1;
    if (0x0 == val)
    {
        HWIO_OUTXF(base, USB4_PCIE_AP_PERST_CMD , SEND_PERST_ACTIVE, 0x1);
        //  HW clears this bit when all required PERST Inactive packets were sent
        while (0 != status)
        {
            status = HWIO_INXF(base, USB4_PCIE_AP_PERST_CMD , SEND_PERST_ACTIVE);
        }
    }
    else
    {
        HWIO_OUTXF(base, USB4_PCIE_AP_PERST_CMD , SEND_PERST_INACTIVE, 0x1);
        //  HW clears this bit when all required PERST Inactive packets were sent
        while (0 != status)
        {
            status = HWIO_INXF(base, USB4_PCIE_AP_PERST_CMD , SEND_PERST_INACTIVE);
        }
    }

    return 0;
}

UINT32 Usb4PlatformAhbAccess_pcieap_get_perst(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx)
{
    UINT8* base;
    UINT32 val;

    base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + PCIE_AP_PROP_REG_BASE_OFFS;
    val = HWIO_INXF(base, USB4_PCIE_AP_PERST_STATUS, PAP_RX_PERST_ACTIVE);

    return val;
}

int Usb4PlatformAhbAccess_dpin_write_common_cap(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, const USB4_dp_common_capability *cap) 
{
    UINT8* pBase;

    /* Set base address */
    pBase = usb4_platform_ahb_access_ctx->m_coreBaseAddress + DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS;

    HWIO_OUTXF(pBase,
               USB4_DPINAP_DP_COMMON_CAP_STANDARD,
               DPRX_CAPABILITIES_READ_DONE,
               cap->DPRXCapabilitiesReadDone);

    HWIO_OUTXF(pBase,
               USB4_DPINAP_DP_COMMON_CAP_STANDARD,
               DSC_NOT_SUPPORTED,
               cap->DSCNotSupported);

    HWIO_OUTXF(pBase,
               USB4_DPINAP_DP_COMMON_CAP_STANDARD,
               LTTPR_NOT_SUPPORTED,
               cap->LTTPRNotSupported);

    HWIO_OUTXF(pBase,
               USB4_DPINAP_DP_COMMON_CAP_STANDARD,
               SECONDARY_SPLIT_CAPABILITY,
               cap->SecondarySplitCapability);

    HWIO_OUTXF(pBase,
               USB4_DPINAP_DP_COMMON_CAP_STANDARD,
               FEC_NOT_SUPPORTED,
               cap->FECNotSupported);

    HWIO_OUTXF(pBase,
               USB4_DPINAP_DP_COMMON_CAP_STANDARD,
               TPS4_CAPABILITY,
               cap->TPS4Capability);

    HWIO_OUTXF(pBase,
               USB4_DPINAP_DP_COMMON_CAP_STANDARD,
               TPS3_CAPABILITY,
               cap->TPS3Capability);

    HWIO_OUTXF(pBase,
               USB4_DPINAP_DP_COMMON_CAP_STANDARD,
               MST_CAPABILITY,
               cap->MSTCapability);

    HWIO_OUTXF(pBase,
               USB4_DPINAP_DP_COMMON_CAP_STANDARD,
               MAXIMAL_LANE_COUNT,
               cap->MaximalLaneCount);

    HWIO_OUTXF(pBase,
               USB4_DPINAP_DP_COMMON_CAP_STANDARD,
               MAXIMAL_LINK_RATE,
               cap->MaximalLinkRate);

    HWIO_OUTXF(pBase,
               USB4_DPINAP_DP_COMMON_CAP_STANDARD,
               MAXIMAL_DPCD_REV,
               cap->MaximalDPCDRev);

    HWIO_OUTXF(pBase,
               USB4_DPINAP_DP_COMMON_CAP_STANDARD,
               PROTOCOL_ADAPTER_REVISION,
               cap->ProtocolAdapterVersion);

    return 0;           
}

/*-----------------------------------------------*/

int Usb4PlatformAhbAccess_dptx_reset(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx) 
{
    UINT8 *pBase = NULL;
    usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;
    pBase = usb4_platform_ahb_access_ctx->m_coreBaseAddress + MDSS_0_DPTX_0_AHBCLK_REG_BASE_OFFS;

    /* Perfrom reset */
    HWIO_OUTX(pBase, MDSS_0_DPTX_0_SW_RESET, 0x1);
    usb4_timer_Sleep_ms(&timer, 10);
    HWIO_OUTX(pBase, MDSS_0_DPTX_0_SW_RESET, 0x0);

    return 0;
}

/*-----------------------------------------------*/

int Usb4PlatformAhbAccess_mdp_reset(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx) 
{
    UINT8 *pBase = NULL;
    usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;
    pBase = usb4_platform_ahb_access_ctx->m_coreBaseAddress + GE_DUT_USER_REGS_REG_BASE_OFFS;

    /* Perfrom reset */
    HWIO_OUTXF(pBase, GE_DUT_DP_CTRL_STS_REG, MDP_RST, 0x1);
    usb4_timer_Sleep_ms(&timer, 10);
    HWIO_OUTXF(pBase, GE_DUT_DP_CTRL_STS_REG, MDP_RST, 0x0);

    return 0;
}

/*-----------------------------------------------*/

int Usb4PlatformAhbAccess_dpin_reset(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx)
{
    UINT32 BLOCK_TX_ACK;
    UINT32 RST_ACK_IRQ;
    UINT32 BLOCK_TX_ACK_IRQ;
    UINT8 *pBase = NULL;
    usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;
    UINT32 timeout_ms;
    UINT32 elapsed_ms;

    pBase = usb4_platform_ahb_access_ctx->m_coreBaseAddress + DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS;

    /* Read BLOCK_TX_ACK */
    BLOCK_TX_ACK = HWIO_INXF(pBase, USB4_DPINAP_RST, BLOCK_TX_ACK);

    /* Issue DPIN sw reset */
    if (0x0 == BLOCK_TX_ACK)
    {
        pBase = usb4_platform_ahb_access_ctx->m_coreBaseAddress + DP_IN_AP_AUX_PROP_REG_BASE_OFFS;

        /* Clear block_ack IRQ */
        HWIO_OUTX(pBase, USB4_DP_AUX_SW_INT_CLR, HWIO_FMSK(USB4_DP_AUX_SW_INT_CLR, BLOCK_TX_ACK_CLR));

        /* Enable block_ack */
        HWIO_OUTXF(pBase, USB4_DP_AUX_SW_INT_EN, BLOCK_TX_ACK_EN, 1);

        pBase = usb4_platform_ahb_access_ctx->m_coreBaseAddress + DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS;

        /* 	BLOCK DPIN */
        HWIO_OUTXF(pBase, USB4_DPINAP_RST, BLOCK_TX, 1);

        /* Wait for BLOCK_ACK IRQ */
        BLOCK_TX_ACK_IRQ = 0;
        pBase = usb4_platform_ahb_access_ctx->m_coreBaseAddress + DP_IN_AP_AUX_PROP_REG_BASE_OFFS;

       /* Setup alarm clock */
        elapsed_ms = 0;
        timeout_ms = 5000; 
        usb4_timer_Start(&timer);

       /* Wait */
        while (0 == BLOCK_TX_ACK_IRQ) 
        {

            BLOCK_TX_ACK_IRQ = 
                HWIO_INXF(pBase, USB4_DP_AUX_SW_INT_STATUS, BLOCK_TX_ACK_IRQ);

            USB4_ASSERT(0 == usb4_timer_GetElapsed_ms(&timer, &elapsed_ms));
            USB4_ASSERT(elapsed_ms < timeout_ms);
        }
    }

    /* Clear RST_ACK IRQ */
    pBase = usb4_platform_ahb_access_ctx->m_coreBaseAddress + DP_IN_AP_AUX_PROP_REG_BASE_OFFS;
    HWIO_OUTX(pBase, USB4_DP_AUX_SW_INT_CLR, HWIO_FMSK(USB4_DP_AUX_SW_INT_CLR, RST_ACK_CLR));

    /* Enable RST_ACK IRQ */
    pBase = usb4_platform_ahb_access_ctx->m_coreBaseAddress + DP_IN_AP_AUX_PROP_REG_BASE_OFFS;
    HWIO_OUTXF(pBase, USB4_DP_AUX_SW_INT_EN, RST_ACK_EN, 0x1);

    /* Reset DPIN */
    pBase = usb4_platform_ahb_access_ctx->m_coreBaseAddress + DPAP_CONFIG_PROP_REG_BASE_OFFS;
    HWIO_OUTXF(pBase, USB4_DPAP_CFG_DP_CLK_RESET, DP_SW_RST, 0x1);

    /* Wait for RST_ACK IRQ */
    RST_ACK_IRQ = 0;
    pBase = usb4_platform_ahb_access_ctx->m_coreBaseAddress + DP_IN_AP_AUX_PROP_REG_BASE_OFFS;

    /* Setup alarm clock */
    elapsed_ms = 0;
    timeout_ms = 5000; 
    usb4_timer_Start(&timer);

    while (0 == RST_ACK_IRQ) 
    {
        RST_ACK_IRQ = HWIO_INXF(pBase, USB4_DP_AUX_SW_INT_STATUS, RST_ACK_IRQ);
        
        USB4_ASSERT(0 == usb4_timer_GetElapsed_ms(&timer, &elapsed_ms));    
        USB4_ASSERT(elapsed_ms < timeout_ms);
    }

    /*  turn off reset */
    pBase = usb4_platform_ahb_access_ctx->m_coreBaseAddress + DPAP_CONFIG_PROP_REG_BASE_OFFS;
    HWIO_OUTXF(pBase, USB4_DPAP_CFG_DP_CLK_RESET, DP_SW_RST, 0);

    return 0;

}

int Usb4PlatformAhbAccess_dpin_reset_dropped_packet_counter(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx)
{
    UINT8 *pBase = NULL;
    pBase = usb4_platform_ahb_access_ctx->m_coreBaseAddress + DP_IN_AP_AUX_PROP_REG_BASE_OFFS;
    HWIO_OUTX(pBase,  USB4_DP_AUX_DROPPED_PKTS_CTL, 1);
    HWIO_OUTX(pBase,  USB4_DP_AUX_DROPPED_PKTS_CTL, 0);

    return 0;
}

int Usb4PlatformAhbAccess_dpin_get_dropped_packet_counter(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, UINT32 * pCount)
{
    UINT8 *pBase = NULL;
    USB4_ASSERT(NULL != pCount);
    pBase = usb4_platform_ahb_access_ctx->m_coreBaseAddress + DP_IN_AP_AUX_PROP_REG_BASE_OFFS;
    *pCount = HWIO_INXF(pBase,  USB4_DP_AUX_DROPPED_PKTS, NUM);

    return 0;
}


// #define USB4_SOME_ALIGN_WA_HACK

#if defined(USB4_SOME_ALIGN_WA_HACK)
static int read_localtime_middle(UINT8* pTmuBase, UINT32* pMiddle)
{
    UINT32 low;
    
    low = HWIO_INX(pTmuBase, USB4_RC_TMU_RTR_CS_1_STANDARD);
    *pMiddle = HWIO_INX(pTmuBase, USB4_RC_TMU_RTR_CS_2_STANDARD);
    (void) low;
    
    return 0;
}
#endif /* USB4_SOME_ALIGN_WA_HACK */

int Usb4PlatformAhbAccess_dpin_config_and_arm(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, USB4_api_dp_config* pCfg) 
{
    UINT8 *pBase = NULL;

    pBase = usb4_platform_ahb_access_ctx->m_coreBaseAddress + DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS;
    
    /* Has meaning only in MST mode */
    if (USB4_DP_CONFIG_STREAM_MODE_MST == pCfg->mode)
    {
        HWIO_OUTXF(pBase, USB4_DPINAP_STREAM_CFG_SIZE ,ALOC_SIZE, pCfg->num_alloc_size);
    }
   
    HWIO_OUTXF(pBase, USB4_DPINAP_STREAM_CFG_STREAM , MST_NSST, pCfg->mode);
    HWIO_OUTXF(pBase, USB4_DPINAP_BAUD_CFG, RATE, pCfg->rate);

#ifdef USB4_SOME_ALIGN_WA_HACK
        {
            UINT32 mid;
            UINT32 current_mask;
            UINT32 val;
            
            pBase = usb4_platform_ahb_access_ctx->m_coreBaseAddress + TMU_CONFIG_REG_BASE_OFFS;
            if (0 != read_localtime_middle(pBase, &mid))
            {
                USB4_ERROR_STACK(-1);
                return -1;
            }
            current_mask = mid & 0x20; // check bit 5
            val = current_mask;
            
            // poll over until bit 5 is changed
            while (val == current_mask)
            {
                if (0 != read_localtime_middle(pBase, &mid))
                {
                    USB4_ERROR_STACK(-1);
                    return -1;
                }
                val = mid & 0x20;
            }
            // set arm_en right after bit5 changed
        }
#endif /* USB4_SOME_ALIGN_WA_HACK */

    pBase = usb4_platform_ahb_access_ctx->m_coreBaseAddress + DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS;
    HWIO_OUTXF(pBase, USB4_DPINAP_CTRL ,ARM_EN, 1);

    return 0;
}

int Usb4PlatformAhbAccess_dpin_configure_hot_plug_notification(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, boolean bEnable)
{
    UINT8 *pBase = NULL;

    pBase = usb4_platform_ahb_access_ctx->m_coreBaseAddress + DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS;

    HWIO_OUTXF(pBase, USB4_DPINAP_ADP_CS_5_STANDARD , DHP, bEnable?0:1);
    return 0;
}

#ifdef RUMI
int Usb4PlatformAhbAccess_GE_issue_disconnect(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx)
{
    UINT32 coreIdx;
    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);

#ifndef SOC_TLMM
    HWIO_OUTXF(usb4_platform_ahb_access_ctx->m_coreBaseAddress + GE_DUT_USER_REGS_REG_BASE_OFFS, GE_DUT_USB4_CTRL_REG,
            SBTX_GPIO_OE,1);

    HWIO_OUTXF(usb4_platform_ahb_access_ctx->m_coreBaseAddress + GE_DUT_USER_REGS_REG_BASE_OFFS, GE_DUT_USB4_CTRL_REG,
            SBTX_GPIO_FUNC_SEL, 0);
#else
    
     coreIdx = (usb4_platform_ahb_access_ctx->m_coreBaseAddress == (UINT8 *)0x15600000)?0:1;

       switch(coreIdx)
       {
         case 0:
           HWIO_OUT(TLMM_GPIO_CFG168, 0x300); // DUT0 SBTX DIR_OUT
           HWIO_OUT(TLMM_GPIO_CFG169, 0x300); // DUT0 SBTX
           break;

         case 1:
           HWIO_OUT(TLMM_GPIO_CFG51, 0x300); // DUT1 SBTX DIR_OUT
           HWIO_OUT(TLMM_GPIO_CFG52, 0x300); // DUT1 SBTX
           break;         

         default:
         break; 
       }      
#endif /* SOC_TLMM */

    return 0;
}

int Usb4PlatformAhbAccess_GE_cancel_disconnect(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx)
{
    UINT32 coreIdx;
    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);

#ifndef SOC_TLMM
    HWIO_OUTXF(usb4_platform_ahb_access_ctx->m_coreBaseAddress + GE_DUT_USER_REGS_REG_BASE_OFFS, GE_DUT_USB4_CTRL_REG,
            SBTX_GPIO_FUNC_SEL, 1);
 
    HWIO_OUTXF(usb4_platform_ahb_access_ctx->m_coreBaseAddress + GE_DUT_USER_REGS_REG_BASE_OFFS, GE_DUT_USB4_CTRL_REG,
             SBTX_GPIO_OE,  0);
#else

      coreIdx = (usb4_platform_ahb_access_ctx->m_coreBaseAddress == (UINT8 *)0x15600000)?0:1;

       switch(coreIdx)
       {
         case 0:
           HWIO_OUT(TLMM_GPIO_CFG168, 0x104); // DUT0 SBTX DIR_OUT
           HWIO_OUT(TLMM_GPIO_CFG169, 0x104); // DUT0 SBTX
           break;

         case 1:
           HWIO_OUT(TLMM_GPIO_CFG51, 0x104); // DUT1 SBTX DIR_OUT
           HWIO_OUT(TLMM_GPIO_CFG52, 0x104); // DUT1 SBTX
           break;
     
         default:
         break; 
       }      
#endif /* SOC_TLMM */

    return 0;
}
#endif /* RUMI */

#ifdef USB4_COMPILING_GEN_EMU

int Usb4PlatformAhbAccess_GE_set_PHY_rate(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, UINT32 val)
{
    // UINT8* base;
    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);
    
    // base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + ROUTER_CONFIG_REG_BASE_OFFS;

    // // disalbe HP retries - accroding to SWI this is underfined
    // HWIO_OUTXF(base, USB4_RC_ROUTER_CS_4_STANDARD, NOTIFICATION_TIMEOUT, 0x0);
    // // Change GE rate
    // base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + GE_DUT_USER_REGS_REG_BASE_OFFS;
    // HWIO_OUTXF(base, GE_DUT_PHY_CONTROL2_REG, RATE, val);

    return 0;
}

int Usb4PlatformAhbAccess_GE_issue_disconnect(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx)
{
    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);

    HWIO_OUTXF2(usb4_platform_ahb_access_ctx->m_coreBaseAddress + GE_DUT_USER_REGS_REG_BASE_OFFS, GE_DUT_USB4_CTRL_REG,
            SBTX_GPIO_FUNC_SEL, SBTX_GPIO_OE, 0, 1);
    return 0;
}

int Usb4PlatformAhbAccess_GE_cancel_disconnect(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx)
{
    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);

    HWIO_OUTXF2(usb4_platform_ahb_access_ctx->m_coreBaseAddress + GE_DUT_USER_REGS_REG_BASE_OFFS, GE_DUT_USB4_CTRL_REG,
            SBTX_GPIO_FUNC_SEL, SBTX_GPIO_OE, 1, 0);
    return 0;
}

int Usb4PlatformAhbAccess_cp_fcm_send_perst(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx, boolean bActive)
{
    UINT8* cpPropBase = usb4_platform_ahb_access_ctx->m_coreBaseAddress + CP_PROP_REG_BASE_OFFS;
    UINT8* cpRamPropBase = usb4_platform_ahb_access_ctx->m_coreBaseAddress + CP_RAM_PROP_REG_BASE_OFFS;
    UINT8* pcieApBase = usb4_platform_ahb_access_ctx->m_coreBaseAddress + PCIE_ADAPTER_PORT_REG_BASE_OFFS;
    UINT8* ucPerBase = usb4_platform_ahb_access_ctx->m_coreBaseAddress + USB4_UC_PER_REG_BASE_OFFS;
    UINT32 cpAck;
    UINT32 val;
    UINT32 pcie_path_hopid;
    
    UINT32 pdf = (TRUE == bActive) ? 0x5 /*Active */: 0x6 /* Inactive */;
    
    USB4_ASSERT(NULL != usb4_platform_ahb_access_ctx->m_coreBaseAddress);
    
    pcie_path_hopid = HWIO_INXF(pcieApBase, USB4_PCIE_AP_PATH_CS_0_STANDARD, OUTPUT_HOPID);
    
    // Disable UC
    HWIO_OUTXF(ucPerBase, USB4_UC_REGS_INSIDE_USB4__CONTROL, UC_ENABLE, 0x0);
    
    // assumig PCIe egress path with HopID = X is set

    // a. Request uC access to CP Egress path
    //    Write: USB4_CTRL_PORT_EG_UC_PKT.EGRESS_UC_PKT_REQ = 1
    HWIO_OUTXF(cpPropBase, USB4_CTRL_PORT_EG_UC_PKT, EGRESS_UC_PKT_REQ, 0x1);
    
    // b. Wait for CP to acknowledge
    //    Read: USB4_CTRL_PORT_EG_UC_PKT.EGRESS_UC_PKT_UC_ACCESS = 1
    cpAck = 0;
    while (0x1 != cpAck)
    {
        cpAck = HWIO_INXF(cpPropBase, USB4_CTRL_PORT_EG_UC_PKT, EGRESS_UC_PKT_UC_ACCESS);
    }
    
    // c. Prepare the data in entry 0 of the CP Tx Buffer (single data beat)
    //    Write: USB4_CTRL_PORT_TXBUF_0.DATA = 0
    HWIO_OUTXI(cpRamPropBase, USB4_CTRL_PORT_TXBUF_n, 0x0, 0x0);
    
    // d. Prepare the packet header as follows
    //    Write: USB4_CTRL_PORT_EG_HEADER.EGRESS_PKT_PDF = 5 (PERST Active packet)
    //    Write: USB4_CTRL_PORT_EG_HEADER.EGRESS_PKT_HOPID = X (PCIe path HopID)
    //    Write: USB4_CTRL_PORT_EG_HEADER.EGRESS_PKT_LENGTH = 4
    HWIO_OUTXF(cpPropBase, USB4_CTRL_PORT_EG_HEADER, EGRESS_PKT_PDF, pdf);
    HWIO_OUTXF(cpPropBase, USB4_CTRL_PORT_EG_HEADER, EGRESS_PKT_HOPID, pcie_path_hopid);
    HWIO_OUTXF(cpPropBase, USB4_CTRL_PORT_EG_HEADER, EGRESS_PKT_LENGTH, 0x4);
    
    // e. Send the packet (use a single write to this reg)
    //    Write: USB4_CTRL_PORT_EG_UC_PKT.EGRESS_UC_PKT_DONE = 1
    //    Write: USB4_CTRL_PORT_EG_UC_PKT.EGRESS_UC_PKT_DMA = 1
    //    Write: USB4_CTRL_PORT_EG_UC_PKT.EGRESS_UC_PKT_REQ = 0
    val = HWIO_FVAL(USB4_CTRL_PORT_EG_UC_PKT, EGRESS_UC_PKT_DONE, 0x1) |
          HWIO_FVAL(USB4_CTRL_PORT_EG_UC_PKT, EGRESS_UC_PKT_DMA, 0x1) |
          HWIO_FVAL(USB4_CTRL_PORT_EG_UC_PKT, EGRESS_UC_PKT_REQ, 0x0);
    HWIO_OUTX(cpPropBase, USB4_CTRL_PORT_EG_UC_PKT, val);

    // TODO Enable UC back
    // HWIO_OUTXF(ucPerBase, USB4_UC_REGS_INSIDE_USB4__CONTROL, UC_ENABLE, 0x1);
    return 0;

}

#endif /* USB4_COMPILING_GEN_EMU */

int Usb4PlatformAhbAccess_configure_tmu_clocks(usb4_platform_ahb_access_ctx_t* usb4_platform_ahb_access_ctx)
{
    UINT8* base = NULL;

#if defined ASIC
    const UINT64 MASTER_CLOCK_FREQ = 250000000ULL;
#else
    const UINT64 MASTER_CLOCK_FREQ = 20000000ULL;
#endif

    /* Pre-compute values */
    const UINT64 MASTER_CLOCK_PERIOD_NANO_INTGR = (1000000000ULL / MASTER_CLOCK_FREQ);
    const UINT64 MASTER_CLOCK_PERIOD_NANO_FRAQ = (1000000000.0 / MASTER_CLOCK_FREQ - MASTER_CLOCK_PERIOD_NANO_INTGR);
    const UINT64 NUMBER_OF_TICKS_IN_1_MSEC = (MASTER_CLOCK_FREQ / 1000ULL);
    const UINT64 NUMBER_OF_TICKS_IN_16_USEC = (MASTER_CLOCK_FREQ / 1000000ULL * 16);

    /* Point to TMU base address */
    base = usb4_platform_ahb_access_ctx->m_coreBaseAddress + TMU_CONFIG_PROP_REG_BASE_OFFS;

    /*-----------------------------------------------*/
    /*          === Bi-Directional Mode ===         */
    /*-----------------------------------------------*/
    /* Set the input clock period in ns. */

    HWIO_OUTXF(base, USB4_TMU_CLK_CYCLE, TMU_CLK_CYCLE_INTGR, MASTER_CLOCK_PERIOD_NANO_INTGR);
    HWIO_OUTXF(base, USB4_TMU_CLK_CYCLE, TMU_CLK_CYCLE_FRAQ, MASTER_CLOCK_PERIOD_NANO_FRAQ);

    /*-----------------------------------------------*/
    /*          === Uni-Directional Mode ===         */
    /*-----------------------------------------------*/
    /* Set to the number of input clock ticks to get the required period. */

    /* Lowres (1msec) */
    HWIO_OUTX(base, USB4_TMU_CYCLES_CNT_TS_PACKET_INTERVAL_LOWRES, NUMBER_OF_TICKS_IN_1_MSEC);

    /* HiFi (16 usec) */
    HWIO_OUTX(base, USB4_TMU_CYCLES_CNT_TS_PACKET_INTERVAL_HIFI, NUMBER_OF_TICKS_IN_16_USEC);

    return 0;
}