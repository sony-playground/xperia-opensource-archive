/**---------------------------------------------------------------------------
 *   @file        usb4_router.cpp
 *
 *   @brief
 *
 *   Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------------------*/
#include <Usb4Utils.h>
#include <Usb4Log.h>
// #include "VVHAL_usb4_logger.h"
// #include "VVHAL_usb4_utils.h"
#include <string.h>

#include "usb4_router.h"

/* --------------------------------------------------------------------------
 * Macros / Types
 *--------------------------------------------------------------------------*/

#define ROUTER_OPERATION_METADATA_DW 25
#define ROUTER_OPERATION_DATA_DW 9

#pragma pack(push)
#pragma pack(1)

/**
 * @brief USB4 version 1.0 Table 8-49.
 * Buffer Allocation Request Router Completion Status and Metadata
 */
typedef struct
{
    UINT32 length       : 8;
    UINT32 reserved_0   : 24;
} USB4_BufferAlocationMetaData;

/**
 * @brief USB4 version 1.0 Table 8-50.
 * Buffer Allocation Request Router Completion Status Data DW structure
 */
typedef struct
{
    UINT32 parameter_index              : 16;
    UINT32 requested_buffer_allocation  : 16;
} USB4_BufferAlocationData;
#pragma pack(pop)

/** @brief USB4 version 1.0 Table 8-49, allocation status */
#define USB4_BUFFER_ALOCATION_STATUS_SUCCESS 0

/** @brief entry for device router map*/
typedef struct usb4_router_device_t
{
    UINT32 vendorId;
    UINT32 productId;
    const char*  driverFile;
} usb4_router_device;

/* TODO this is still not good enough */
#if defined(USB4_COMPILING_GEN_EMU) || defined (USB4_COMPILING_GEN_EMU_VELOCE)
#define ROUTER_DRIVER(fname)  fname
#else /* ASIC or RUMI */
#define ROUTER_DRIVER(fname) "../../../../../../../driver/common/router_drivers/" fname
#endif /* ASIC or RUMI */

#define ROUTER_PATH_MAX_CHARS 127

#if 0
static const char* s_search_paths[] =
{
    // current working dir
    "./",

    // test executes from vi_core/tests/platform/<test>/bin
    "../../../../driver/common/router_drivers/",

    // test executes from <vi_core>/tests/platform/<vi_target_vx>/tests/<template>/cmm/apps_proc0
    "../../../../../../../driver/common/router_drivers/",

    // test executes from convex/system_tests/cmm/<proc>
    "../../../drivers/vi_usb4/common/router_drivers/",
};
#endif

/** @brief mapping betwwen vendor and deivce id to the driver file */
static const usb4_router_device s_router_device_map[] =
{
    {0x8086, 0x15D3, "doc_gen_1.txt" },  
    {0x8086, 0x15EF, "lg.txt" },  
};

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

int Usb4RouterInit(usb4_router_ctx_t* router_ctx, usb4_ctrl_iface_ctx_t* pControl)
{
    UINT32 i;

    if (NULL == pControl)
    {
        USB4_ERROR_STACK_MSG(-1, "Pointer to HIA can't be null");
        goto ErrorHandling;
    }
    router_ctx->m_pControl = NULL;
    //    m_Ports(),
    //    m_cs(),
    router_ctx->m_topologyID = USB4_INVALID_TOPOLOGY_ID;
    router_ctx->m_bEnumerationError = FALSE;
    router_ctx->m_bInterdomainRouter = FALSE;
    router_ctx->m_bPcieTunneling = FALSE;
    router_ctx->m_bUsb3Tunneling = FALSE;
    router_ctx->m_bDpTunneling = FALSE;
    router_ctx->m_displayPortAdapter = 0;
    router_ctx->m_baMaxUSB3 = 0;
    router_ctx->m_baMinDPaux = 0;
    router_ctx->m_baMinDPmain = 0;
    router_ctx->m_baMaxPCIe = 0;
    router_ctx->m_baMaxHI = 0;
    router_ctx->m_bufferAllocationRequestSuceeded = FALSE;
    router_ctx->m_tmuCurrentMode = USB4_TMU_MODE_NOT_SET;
    router_ctx->m_tmuCachedUniSupport = -1;
    router_ctx->m_configurationFileLoaded = FALSE;
    router_ctx->m_bDisableWakeOnConnect = FALSE;
    router_ctx->m_bDisableWakeOnDisconnect = FALSE;
    router_ctx->m_bDisableWakeOnUsb4 = FALSE;
    router_ctx->m_bDisableWakeOnInterdomain = FALSE;

    router_ctx->m_pControl = pControl;
    router_ctx->m_topologyID = USB4_INVALID_TOPOLOGY_ID;
    router_ctx->m_bEnumerationError = FALSE;

    router_ctx->m_bInterdomainRouter = FALSE;

    router_ctx->m_bDpTunneling = FALSE;
    router_ctx->m_displayPortAdapter = 0;

    router_ctx->m_bPcieTunneling = FALSE;
    router_ctx->m_bUsb3Tunneling = FALSE;

    router_ctx->m_baMaxUSB3 = 0;
    router_ctx->m_baMinDPaux = 0;
    router_ctx->m_baMinDPmain = 0;
    router_ctx->m_baMaxPCIe = 0;
    router_ctx->m_baMaxHI = 0;
    router_ctx->m_bufferAllocationRequestSuceeded = FALSE;
    router_ctx->m_configurationFileLoaded = FALSE;

    router_ctx->m_tmuCurrentMode = USB4_TMU_MODE_NOT_SET;

    router_ctx->m_bDisableWakeOnConnect = FALSE;
    router_ctx->m_bDisableWakeOnDisconnect = FALSE;
    router_ctx->m_bDisableWakeOnUsb4 = FALSE;
    router_ctx->m_bDisableWakeOnInterdomain = FALSE;

    memset((void*)(&router_ctx->m_cs), 0, sizeof(router_ctx->m_cs));

    for (i = 0; i < USB4_MAX_PORTS_PER_ROUTER; i++)
    {
        if (0 != Usb4PortInit(&router_ctx->m_Ports[i], router_ctx->m_pControl, i))
        {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
        }
    }

    return 0;
ErrorHandling:
    //TODO: Create DeInit if needed.
    return -1;
} ;

int Usb4RouterSetRoute(usb4_router_ctx_t* router_ctx)
{
    return Usb4CtrlIfaceSetRoute(router_ctx->m_pControl, router_ctx->m_topologyID);
}

int Usb4RouterSearchCapability(usb4_router_ctx_t* router_ctx, USB4_ROUTER_CAP capIdRequested, UINT32* pCapLength)
{
    UINT32 NextCapabilityPointer = router_ctx->m_cs.ROUTER_CS_1.nextCapabilityPointer;
    UINT32 buffer;
    UINT8* pBuff = (UINT8*)(&buffer);
    UINT32 len;
    UINT32 capID;

    while(NextCapabilityPointer)
    {
        USB4_ASSERT(0 == Usb4CtrlIfaceSetType(router_ctx->m_pControl, USB4_cpDescriptorType_READ_REQUEST));
        USB4_ASSERT(0 == Usb4CtrlIfaceSetRoute(router_ctx->m_pControl, router_ctx->m_topologyID));
        USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(router_ctx->m_pControl, NextCapabilityPointer));
        USB4_ASSERT(0 == Usb4CtrlIfaceSetAdapter(router_ctx->m_pControl, 0));
        USB4_ASSERT(0 == Usb4CtrlIfaceSetCS(router_ctx->m_pControl, USB4_cpConfigSpace_ROUTER));
        USB4_ASSERT(0 == Usb4CtrlIfaceSetData(router_ctx->m_pControl, NULL, 4));

        if(0 != Usb4CtrlIfaceSend(router_ctx->m_pControl, USB4_SEND_CTRL_PACKET_TIMEOUT_US))
        {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
        }

        USB4_ASSERT(0 == Usb4CtrlIfaceGetData(router_ctx->m_pControl, pBuff, &len, 4));
        USB4_ASSERT(0 == Usb4CtrlIfacePop(router_ctx->m_pControl));
        USB4_ASSERT_MSG(len == sizeof(4), "Didn't read a complete DWORD");
        capID = (buffer & 0xFF00)>>0x8;
        if (capID == capIdRequested)
        {
            if (NULL != pCapLength)
            {
                if ((buffer & 0xFF) > (NextCapabilityPointer & 0xFF))
                {
                    *pCapLength = 4*((buffer & 0xFF) - (NextCapabilityPointer & 0xFF) - 1) ;
                }
            }
            return 0;
        }
        NextCapabilityPointer = buffer & 0xFF;
    }

ErrorHandling:
    return -1;
}

int Usb4RouterSearchVsecCapability(usb4_router_ctx_t* router_ctx, USB4_ROUTER_VSEC_CAP vsecCapIdRequested, UINT32* pCapLength, UINT32* pCapAddress)
{
    UINT32 NextCapabilityPointer = router_ctx->m_cs.ROUTER_CS_1.nextCapabilityPointer;
    usb4_router_VSEC_CS0_TYPE cs0;
    usb4_router_TBT3_VSEC6 vsec6;
    UINT8* pBuff;
    UINT32 len, header_len;

    if(USB4_ROUTER_VSEC_CAP_6 == vsecCapIdRequested)
    {
        pBuff = (UINT8*)(&vsec6);
        header_len = sizeof(vsec6);
    }
    else
    {
        pBuff = (UINT8*)(&cs0);
        header_len = sizeof(cs0);
    }

    while(NextCapabilityPointer)
    {
        USB4_ASSERT(0 == Usb4CtrlIfaceSetType(router_ctx->m_pControl, USB4_cpDescriptorType_READ_REQUEST));
        USB4_ASSERT(0 == Usb4CtrlIfaceSetRoute(router_ctx->m_pControl, router_ctx->m_topologyID));
        USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(router_ctx->m_pControl, NextCapabilityPointer));
        USB4_ASSERT(0 == Usb4CtrlIfaceSetAdapter(router_ctx->m_pControl, 0));
        USB4_ASSERT(0 == Usb4CtrlIfaceSetCS(router_ctx->m_pControl, USB4_cpConfigSpace_ROUTER));
        USB4_ASSERT(0 == Usb4CtrlIfaceSetData(router_ctx->m_pControl, NULL, header_len));

        if(0 != Usb4CtrlIfaceSend(router_ctx->m_pControl, USB4_SEND_CTRL_PACKET_TIMEOUT_US))
        {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
        }

        USB4_ASSERT(0 == Usb4CtrlIfaceGetData(router_ctx->m_pControl, pBuff, &len, header_len));
        USB4_ASSERT(0 == Usb4CtrlIfacePop(router_ctx->m_pControl));
        USB4_ASSERT_MSG(len == header_len, "Didn't read a complete header");

        if(USB4_ROUTER_VSEC_CAP_6 == vsecCapIdRequested)
        {
            if ((vsec6.VSEC6_CS0.capabilityID == USB4_ROUTER_CAP_VENDOR) && (vsec6.VSEC6_CS0.VSEC_ID == vsecCapIdRequested))
            {
                if (NULL != pCapLength)
                {
                    *pCapLength = 4*vsec6.VSEC6_CS1.VSEC_LENGTH;
                }
                if (NULL != pCapAddress)
                {
                    *pCapAddress = NextCapabilityPointer;
                }
                return 0;
            }
            NextCapabilityPointer = vsec6.VSEC6_CS0.nextCapabilityPointer; /* This is a place where other capabilities keep their next */
        }
        else
        {
            if ((cs0.capabilityID == USB4_ROUTER_CAP_VENDOR) && (cs0.VSEC_ID == vsecCapIdRequested))
            {
                if (NULL != pCapLength)
                {
                    *pCapLength = 4*cs0.VSEC_LENGTH;
                }
                if (NULL != pCapAddress)
                {
                    *pCapAddress = cs0.nextCapabilityPointer;
                }
                return 0;
            }
            NextCapabilityPointer = cs0.nextCapabilityPointer;
        }
    }

ErrorHandling:
    return -1;
}

int Usb4RouterVsec6AcceessPort(usb4_router_ctx_t* router_ctx, usb4_router_access_vsec6* pAccessVsec6)
{
    UINT32 capLength, capAddress;
    usb4_router_TBT3_VSEC6 vsec6;
    UINT8* pBuff;
    UINT32 header_len;

    USB4_ASSERT(NULL != pAccessVsec6);
    USB4_ASSERT(0 == Usb4RouterSearchVsecCapability(router_ctx, USB4_ROUTER_VSEC_CAP_6, &capLength, &capAddress));

    pBuff = (UINT8*)(&vsec6);
    header_len = sizeof(vsec6);
    USB4_ASSERT(header_len <= capLength);
    USB4_ASSERT(0 == Usb4RouterReadCapability(router_ctx, pBuff, header_len));
    if (NULL != pAccessVsec6->pNumberOfPorts)
    {
        *pAccessVsec6->pNumberOfPorts = vsec6.VSEC6_CS2.usb4Ports;
    }
    USB4_ASSERT(pAccessVsec6->portNumber < vsec6.VSEC6_CS2.usb4Ports);

    switch(pAccessVsec6->command)
    {
        case WRITE:
            USB4_ASSERT(NULL != pAccessVsec6->buff);
            capAddress = capAddress + vsec6.VSEC6_CS2.commonRegLen +
                vsec6.VSEC6_CS2.usb4PortRegLen*pAccessVsec6->portNumber + pAccessVsec6->offsetDwords;
            USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(router_ctx->m_pControl, capAddress));
            USB4_ASSERT(0 == Usb4RouterWriteCapability(router_ctx, pAccessVsec6->buff, pAccessVsec6->numDwords*sizeof(UINT32)));
            break;
        case READ:
            USB4_ASSERT(NULL != pAccessVsec6->buff);
            capAddress = capAddress + vsec6.VSEC6_CS2.commonRegLen +
                vsec6.VSEC6_CS2.usb4PortRegLen*pAccessVsec6->portNumber + pAccessVsec6->offsetDwords;
            USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(router_ctx->m_pControl, capAddress));
            USB4_ASSERT(0 == Usb4RouterReadCapability(router_ctx, pAccessVsec6->buff, pAccessVsec6->numDwords*sizeof(UINT32)));
            break;
        case SET_DPR:
        case CLEAR_DPR:
        case SET_EWI:
        case SET_IDD:
        case READ_BE:
        case SET_ENABLE_WAKE_EVENTS:
        case SET_L0C:
        case SET_L0D:
        case SET_L1C:
        case SET_L1D:
        case SET_SLI:
        case CLEAR_SLI:
        case SET_SLP:
        case SET_RS2:
        case CLEAR_RS2:
        case SET_RRS3:
        case CLEAR_RRS3:
            USB4_ASSERT_MSG(-1, "Error: Need to implements VSEC6 command");
            break;
        default:
            USB4_ASSERT_MSG(-1, "Wrong VSEC6 command");
    }

    return 0;
}

int Usb4RouterWriteFileToRouter(usb4_router_ctx_t* router_ctx, const char* fname)
{
    UINT32 transfer_data;
    usb4_ctrl_iface_trn transfer;
    FILE* pFile = NULL;
#if 0 // TODO: AC Implement File Open Vendor Config
    char buff[ROUTER_PATH_MAX_CHARS] = { 0x0 };
    UINT32 i;
#endif

    /* Verify file name is provided */
    USB4_ASSERT(NULL != fname);

    /* Read configuration space */
    USB4_ASSERT(0 == Usb4RouterReadCS(router_ctx));

    /* Check if the router was enumerated */
    USB4_ASSERT(router_ctx->m_cs.ROUTER_CS_3.tolpologyIdValid);


    /*-----------------------------------------*/
    /* === Setup transaction parameters  ===   */
    /*-----------------------------------------*/

    transfer.topologyId = ((UINT64)(router_ctx->m_cs.ROUTER_CS_2.topologyIdLow)) +
        ((UINT64)(router_ctx->m_cs.ROUTER_CS_3.topologyIdHigh) << 32);

    transfer.timeout_us = 10000;
    transfer.adapterNum = 0;
    transfer.type = USB4_cpDescriptorType_WRITE_REQUEST;
    transfer.cs = USB4_cpConfigSpace_ROUTER;
    transfer.pBuff = (UINT8*)&transfer_data;
    transfer.size_bytes = 4;

#if 0 // TODO: AC Implement File Open Vendor Config
    int d0;
    int d1;
    int d2;
    int d3;
    UINT32 counter;

    USB4_LOG_INFO("Configuring device ...");
    /* Try to open the file on different search paths*/
    for (i = 0; i < ARR_SIZE(s_search_paths); ++i)
    {
        snprintf(buff, sizeof(buff), "%s%s", s_search_paths[i], fname);
        USB4_LOG_INFO("Openning %s ... \n", buff);
        pFile = fopen(buff, "r");
        if (NULL != pFile)
        {
            USB4_LOG_INFO(" - Done!\n");
            break;
        }
    }
    USB4_ASSERT_MSG(NULL != pFile, "Could not open driver");

    while(!feof(pFile))
    {
        /* Read file */
        fscanf(pFile, "%x %x %x %x %x", &transfer.address, &d0, &d1, &d2, &d3);

        /* Write to device */
        transfer_data = d0  + (d1 << 8) + (d2 << 16) + (d3 << 24);
        USB4_ASSERT(0 == Usb4CtrlIfaceTransfer(router_ctx->m_pControl, &transfer));

        counter++;
    }

    fclose(pFile);
#endif
    pFile = NULL;
    // USB4_LOG_INFO("done.\n");
    Usb4Log(USB4_LOG_CM, Usb4RouterWriteFileToRouterDone__Info, 0);

    return 0;

#if 0 // TODO: AC Implement File Open Vendor Config
ErrorHandling:
    if (NULL != pFile)
    {
        fclose(pFile);
        pFile = NULL;
    }
    USB4_LOG_INFO("fail.\n");

    return -1;
#endif
}

/*---------------------------------------------*/

int Usb4RouterLoadVendorSettings(usb4_router_ctx_t* router_ctx)
{
    UINT32 vendorId;
    UINT32 productId;
    usb4_router_device curDevice;

    if (router_ctx->m_configurationFileLoaded)
    {
        return 0;
    }


    /* Load configuration space */
    USB4_ASSERT(0 == Usb4RouterReadCS(router_ctx));

    /* Make sure router is enumerated */
    USB4_ASSERT(router_ctx->m_cs.ROUTER_CS_3.tolpologyIdValid);

    /* Get product and vendor id */
    vendorId = router_ctx->m_cs.ROUTER_CS_0.vendorID;
    productId = router_ctx->m_cs.ROUTER_CS_0.productID;

    /* Search for device driver file */
    for (UINT32 i = 0; i < ARR_SIZE(s_router_device_map); i++)
    {
        curDevice = s_router_device_map[i];

        /* If device was found */
        if ((vendorId == curDevice.vendorId) && (productId == curDevice.productId))
        {
            // USB4_LOG_INFO("Detected vendor 0x%X product 0x%X\n", vendorId, productId);
            Usb4Log2(USB4_LOG_CM, Usb4RouterLoadVendorSettingsDetected__Params__Vendor_Product, 0, vendorId, productId);

            /* Load driver */
            if (0 != Usb4RouterWriteFileToRouter(router_ctx, curDevice.driverFile))
            {
                // USB4_LOG_WARNING("Failed to load the driver, continue gracefully...\n");
                // USB4_LOG_WARNING("Please check out what workspace root is correct\n");
                Usb4Log(USB4_LOG_CM, Usb4RouterLoadVendorSettingsFailedToLoadDriverContinueGracefully__Warn, 0);
                Usb4Log(USB4_LOG_CM, Usb4RouterLoadVendorSettingsPleaseCheckVendorSettingsFolder__Warn, 0);
            }
            router_ctx->m_configurationFileLoaded = TRUE;

            /* Stop the search */
            break;
        }
    }

    return 0;
}

/*---------------------------------------------*/

int Usb4RouterReadCapability(usb4_router_ctx_t* router_ctx, UINT8* pBuff, UINT32 capSize)
{
    UINT32 len;

    USB4_ASSERT(0 == Usb4CtrlIfaceSetType(router_ctx->m_pControl, USB4_cpDescriptorType_READ_REQUEST)); // TODO: AC I think code needs a SetType READ
    USB4_ASSERT(0 == Usb4CtrlIfaceSetData(router_ctx->m_pControl, NULL, capSize));

    if(0 != Usb4CtrlIfaceSend(router_ctx->m_pControl, USB4_SEND_CTRL_PACKET_TIMEOUT_US))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    USB4_ASSERT(0 == Usb4CtrlIfaceGetData(router_ctx->m_pControl, pBuff, &len, capSize));
    USB4_ASSERT(0 == Usb4CtrlIfacePop(router_ctx->m_pControl));
    USB4_ASSERT_MSG(len == capSize, "Didn't read a complete CS");

    return 0;
ErrorHandling:
    return -1;
}

int Usb4RouterWriteCapability(usb4_router_ctx_t* router_ctx, UINT8* pBuff, UINT32 write_len)
{
    UINT32 len;

    /* The rest of parameters were set elsewhere.. prior to this call... */
    USB4_ASSERT(0 == Usb4CtrlIfaceSetType(router_ctx->m_pControl, USB4_cpDescriptorType_WRITE_REQUEST));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetData(router_ctx->m_pControl, pBuff, write_len));

    if (0 != Usb4CtrlIfaceSend(router_ctx->m_pControl, USB4_SEND_CTRL_PACKET_TIMEOUT_US))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    USB4_ASSERT(0 == Usb4CtrlIfaceGetData(router_ctx->m_pControl, NULL, &len, write_len));
    USB4_ASSERT(0 == Usb4CtrlIfacePop(router_ctx->m_pControl));
    USB4_ASSERT_MSG(len == write_len, "Didn't write a complete buffer");

    return 0;
ErrorHandling:
    return -1;
}

int Usb4RouterReadCS(usb4_router_ctx_t* router_ctx)
{
    UINT8* pBuff = (UINT8*)(&router_ctx->m_cs);
    UINT32 len, adapter;

    /* CS was read already */
    if (0 != router_ctx->m_cs.ROUTER_CS_0.vendorID)
    {
        return 0;
    }

    USB4_ASSERT(0 == Usb4CtrlIfaceSetType(router_ctx->m_pControl, USB4_cpDescriptorType_READ_REQUEST));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetRoute(router_ctx->m_pControl, router_ctx->m_topologyID));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(router_ctx->m_pControl, 0));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetAdapter(router_ctx->m_pControl, 0));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetCS(router_ctx->m_pControl, USB4_cpConfigSpace_ROUTER)); /* Router Configuration Space */
    USB4_ASSERT(0 == Usb4CtrlIfaceSetData(router_ctx->m_pControl, NULL, sizeof(router_ctx->m_cs)));

    if(0 != Usb4CtrlIfaceSend(router_ctx->m_pControl, USB4_SEND_CTRL_PACKET_TIMEOUT_US))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    USB4_ASSERT(0 == Usb4CtrlIfaceGetData(router_ctx->m_pControl, pBuff, &len, sizeof(router_ctx->m_cs)));
    USB4_ASSERT(0 == Usb4CtrlIfaceGetAdapter(router_ctx->m_pControl, &adapter));
    USB4_ASSERT(0 == Usb4CtrlIfacePop(router_ctx->m_pControl));
    router_ctx->m_cs.ROUTER_CS_1.upstreamAdapter = adapter;
    USB4_ASSERT_MSG(len == sizeof(router_ctx->m_cs), "Didn't read a complete CS");

    return 0;
ErrorHandling:
    return -1;
}

int Usb4RouterWriteCS(usb4_router_ctx_t* router_ctx)
{
    UINT8* pBuff = (UINT8*)(&router_ctx->m_cs);
    BOOLEAN p_result;


    USB4_ASSERT(0 == Usb4CtrlIfaceSetType(router_ctx->m_pControl, USB4_cpDescriptorType_WRITE_REQUEST));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetRoute(router_ctx->m_pControl, router_ctx->m_topologyID));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(router_ctx->m_pControl, 0));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetAdapter(router_ctx->m_pControl, 0));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetCS(router_ctx->m_pControl, USB4_cpConfigSpace_ROUTER));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetData(router_ctx->m_pControl, pBuff, sizeof(router_ctx->m_cs)));

    if (0 != Usb4CtrlIfaceSend(router_ctx->m_pControl, USB4_SEND_CTRL_PACKET_TIMEOUT_US))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    /* Perfrom write reponse verification*/
    USB4_ASSERT(0  == Usb4CtrlIfaceVerifyReadWriteResponse(router_ctx->m_pControl, &p_result));
    USB4_ASSERT(TRUE == p_result);
    USB4_ASSERT(0 == Usb4CtrlIfacePop(router_ctx->m_pControl));
    return 0;

ErrorHandling:
    USB4_ASSERT(0 == Usb4CtrlIfacePop(router_ctx->m_pControl));
    return -1;
}

int Usb4RouterWriteCSDword(usb4_router_ctx_t* router_ctx, UINT32 start_dword, UINT32 number_of_dwords)
{
    UINT8* pBuff = (UINT8*)(&router_ctx->m_cs) + 4*start_dword;
    BOOLEAN p_result;


    USB4_ASSERT(0 == Usb4CtrlIfaceSetType(router_ctx->m_pControl, USB4_cpDescriptorType_WRITE_REQUEST));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetRoute(router_ctx->m_pControl, router_ctx->m_topologyID));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(router_ctx->m_pControl, start_dword));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetAdapter(router_ctx->m_pControl, 0));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetCS(router_ctx->m_pControl, USB4_cpConfigSpace_ROUTER));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetData(router_ctx->m_pControl, pBuff, number_of_dwords*4));

    if (0 != Usb4CtrlIfaceSend(router_ctx->m_pControl, USB4_SEND_CTRL_PACKET_TIMEOUT_US))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    /* Perfrom write reponse verification*/
    USB4_ASSERT(0  == Usb4CtrlIfaceVerifyReadWriteResponse(router_ctx->m_pControl, &p_result));
    USB4_ASSERT(TRUE == p_result);
    USB4_ASSERT(0 == Usb4CtrlIfacePop(router_ctx->m_pControl));
    return 0;

ErrorHandling:
    return -1;
}

int Usb4RouterWriteCSData(usb4_router_ctx_t* router_ctx, UINT32 start_dword, UINT32 number_of_dwords, UINT8* pBuff)
{
    BOOLEAN p_result;

    USB4_ASSERT(0 == Usb4CtrlIfaceSetType(router_ctx->m_pControl, USB4_cpDescriptorType_WRITE_REQUEST));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetRoute(router_ctx->m_pControl, router_ctx->m_topologyID));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(router_ctx->m_pControl, start_dword));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetAdapter(router_ctx->m_pControl, 0));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetCS(router_ctx->m_pControl, USB4_cpConfigSpace_ROUTER));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetData(router_ctx->m_pControl, pBuff, number_of_dwords*4));

    if (0 != Usb4CtrlIfaceSend(router_ctx->m_pControl, USB4_SEND_CTRL_PACKET_TIMEOUT_US))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    /* Perfrom write reponse verification*/
    USB4_ASSERT(0  == Usb4CtrlIfaceVerifyReadWriteResponse(router_ctx->m_pControl, &p_result));
    USB4_ASSERT(TRUE == p_result);
    USB4_ASSERT(0 == Usb4CtrlIfacePop(router_ctx->m_pControl));
    return 0;

ErrorHandling:
    USB4_ASSERT(0 == Usb4CtrlIfacePop(router_ctx->m_pControl));
    return -1;
}

int Usb4RouterPollCS_6_Mask(usb4_router_ctx_t* router_ctx, UINT64 usTimeout, UINT32 mask)
{
    UINT8* pBuff = (UINT8*)(&router_ctx->m_cs.ROUTER_CS_6);
    UINT32 len;
    UINT32 write_len = sizeof(UINT32);
    usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;
    UINT32 elapsed_us;

    USB4_ASSERT(0 == Usb4CtrlIfaceSetType(router_ctx->m_pControl, USB4_cpDescriptorType_READ_REQUEST));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetRoute(router_ctx->m_pControl, router_ctx->m_topologyID));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(router_ctx->m_pControl, 6));    //Read DWORD at address 6
    USB4_ASSERT(0 == Usb4CtrlIfaceSetAdapter(router_ctx->m_pControl, 0));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetCS(router_ctx->m_pControl, USB4_cpConfigSpace_ROUTER));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetData(router_ctx->m_pControl, NULL, write_len));

    usb4_timer_Start(&timer);
    do
    {
        if(0 != Usb4CtrlIfaceSend(router_ctx->m_pControl, usTimeout))
        {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
        }

        USB4_ASSERT(0 == Usb4CtrlIfaceGetData(router_ctx->m_pControl, pBuff, &len, write_len));
        USB4_ASSERT(0 == Usb4CtrlIfacePop(router_ctx->m_pControl));

        USB4_ASSERT_MSG(len == write_len, "Didn't read a complete CS");
        USB4_ASSERT(0 == usb4_timer_GetElapsed_us(&timer, &elapsed_us));
#ifndef USB4_COMPILING_GEN_EMU_VELOCE
        USB4_ASSERT_MSG(usTimeout > elapsed_us, "Timeout value exceeded");
#endif
    } while (mask != ((*(UINT32*)(&router_ctx->m_cs.ROUTER_CS_6)) & mask));

    return 0;
ErrorHandling:
    return -1;
}

int Usb4RouterPollRR(usb4_router_ctx_t* router_ctx, UINT64 usTimeout)
{
    usb4_router_cs_6 cs_6 = {0};
    cs_6.routerReady = 1;
    USB4_ASSERT(0 == Usb4RouterPollCS_6_Mask(router_ctx, usTimeout, *(UINT32*)(&cs_6)));
    return 0;
}

int Usb4RouterPollCR(usb4_router_ctx_t* router_ctx, UINT64 usTimeout)
{
    usb4_router_cs_6 cs_6 = {0};
    cs_6.configurationReady = 1;
    USB4_ASSERT(0 == Usb4RouterPollCS_6_Mask(router_ctx, usTimeout, *(UINT32*)(&cs_6)));

    return 0;
}

int Usb4RouterPollSLRP(usb4_router_ctx_t* router_ctx, UINT64 usTimeout)
{
    usb4_router_cs_6 cs_6 = {0};
    cs_6.sleepReady_SLPR = 1;
    USB4_ASSERT(0 == Usb4RouterPollCS_6_Mask(router_ctx, usTimeout, *(UINT32*)(&cs_6)));

    return 0;
}

int Usb4RouterGetBufferAllocations(usb4_router_ctx_t* router_ctx)
{
    int i;
    usb4_router_operations_cs bufferAllocation = {0};
    USB4_BufferAlocationMetaData* pMeta;
    USB4_BufferAlocationData* pData;
    usb4_buffer_allocation_index index;
    UINT32 routerId = USB4_LOWER32(router_ctx->m_topologyID);

    if (TRUE == router_ctx->m_bufferAllocationRequestSuceeded)
    {
        return 0; // Exit gracefully
    }

    bufferAllocation.ROUTER_CS_26.Opcode = USB4_ROUTER_OPERATION_BUFFER_ALLOCATION_REQUEST;
    if (0 != Usb4RouterIssueCommand(router_ctx, &bufferAllocation, 50000)) //10000
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    if (USB4_BUFFER_ALOCATION_STATUS_SUCCESS != bufferAllocation.ROUTER_CS_26.Status)
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    pMeta = (USB4_BufferAlocationMetaData*)(&(bufferAllocation.Metadata));
    router_ctx->m_bufferAllocationRequestSuceeded = TRUE;
    for (i = 0; i < pMeta->length; ++i)
    {
        pData = (USB4_BufferAlocationData*)(bufferAllocation.data + i);
        index = (usb4_buffer_allocation_index)(pData->parameter_index);

        switch (index)
        {
            case usb4_baMaxUSB3:
                router_ctx->m_baMaxUSB3 = pData->requested_buffer_allocation;
                // USB4_LOG_INFO("Router %x, usb4_baMaxUSB3 %d\n", routerId, router_ctx->m_baMaxUSB3);
                Usb4Log2(USB4_LOG_CM, Usb4RouterGetBufferAllocations__Params__Router_baMaxUSB3, 0, routerId, router_ctx->m_baMaxUSB3);
                break;

            case usb4_baMinDPaux:
                router_ctx->m_baMinDPaux = pData->requested_buffer_allocation;
                // USB4_LOG_INFO("Router %x, router_ctx->m_baMinDPaux %d\n", routerId, router_ctx->m_baMinDPaux);
                Usb4Log2(USB4_LOG_CM, Usb4RouterGetBufferAllocations__Params__Router_baMinDPaux, 0, routerId, router_ctx->m_baMinDPaux);
                break;

            case usb4_baMinDPmain:
                router_ctx->m_baMinDPmain = pData->requested_buffer_allocation;
                // USB4_LOG_INFO("Router %x, usb4_baMinDPmain %d\n", routerId, usb4_baMinDPmain);
                Usb4Log2(USB4_LOG_CM, Usb4RouterGetBufferAllocations__Params__Router_baMinDPmain, 0, routerId, usb4_baMinDPmain);
                break;

            case usb4_baMaxPCIe:
                router_ctx->m_baMaxPCIe = pData->requested_buffer_allocation;
                // USB4_LOG_INFO("Router %x, usb4_baMaxPCIe %d\n", routerId, usb4_baMaxPCIe);
                Usb4Log2(USB4_LOG_CM, Usb4RouterGetBufferAllocations__Params__Router_baMaxPCIe, 0, routerId, usb4_baMaxPCIe);
                break;

            case usb4_baMaxHI:
                router_ctx->m_baMaxHI = pData->requested_buffer_allocation;
                // USB4_LOG_INFO("Router %x, usb4_baMaxHI %d\n", routerId, usb4_baMaxHI);
                Usb4Log2(USB4_LOG_CM, Usb4RouterGetBufferAllocations__Params__Router_baMaxHI, 0, routerId, usb4_baMaxHI);
                break;

            case usb4_baReserved:
            default:
                // USB4_LOG_WARNING("Unsupported parameter index, data: 0x%08X\n",
                //         bufferAllocation.data[i]);
                Usb4Log1(USB4_LOG_CM, Usb4RouterGetBufferAllocationsUnsupportedParameter__Params__IndexData, 0, bufferAllocation.data[i]);
                break;
        }
    }

    return 0;
ErrorHandling:
    return -1;
}

BOOLEAN Usb4RouterIsEnumerated(usb4_router_ctx_t* router_ctx)
{
    UINT64 tid;

    if (USB4_INVALID_TOPOLOGY_ID == router_ctx->m_topologyID)
    {
        return FALSE;
    }

    tid = USB4_GET_UINT64(router_ctx->m_cs.ROUTER_CS_3.topologyIdHigh, router_ctx->m_cs.ROUTER_CS_2.topologyIdLow);

    if ((0x1 == router_ctx->m_cs.ROUTER_CS_3.tolpologyIdValid) &&
            (tid == router_ctx->m_topologyID))
    {
        return TRUE;
    }

    return FALSE;
}

int Usb4RouterEnumerate(usb4_router_ctx_t* router_ctx)
{
    UINT32 depth;

    if (TRUE == Usb4RouterIsEnumerated(router_ctx))
    {
        /* Enumeration was done previously */
        return 0;
    }

    // USB4_LOG_INFO("Will Enumerate router %x\n", USB4_LOWER32(router_ctx->m_topologyID));
    Usb4Log1(USB4_LOG_CM, Usb4RouterEnumerateWillEnumerate__Params__Router, 0, USB4_LOWER32(router_ctx->m_topologyID));

    USB4_ASSERT(0 == Usb4RouterReadCS(router_ctx));

    /* Enumerate: */
    router_ctx->m_cs.ROUTER_CS_2.topologyIdLow = USB4_LOWER32(router_ctx->m_topologyID);
    router_ctx->m_cs.ROUTER_CS_3.topologyIdHigh = USB4_UPPER32(router_ctx->m_topologyID);
    router_ctx->m_cs.ROUTER_CS_3.tolpologyIdValid = 1;

    depth = usb4_get_depth_from_topology(router_ctx->m_topologyID);
    USB4_ASSERT(depth < 7);

    router_ctx->m_cs.ROUTER_CS_1.depth = depth;
    router_ctx->m_cs.ROUTER_CS_4.cmUsb4Ver = 0x10; //Set bit 12, to signal that USB4 protocol is supported
    router_ctx->m_cs.ROUTER_CS_4.notificationTimeout = 0xFF; /* Reduce the frequency of notification retransmissions */
    if (depth > 0)
    {
        /* TODO: Enumerating device router - don't see any special actions yet */
    }

    USB4_ASSERT(0 == Usb4RouterWriteCSDword(router_ctx, 1, 4));

    USB4_ASSERT(0 == Usb4RouterPollRR(router_ctx, USB4_POLL_RR_TIMEOUT_US));

    if (0 == (router_ctx->m_cs.ROUTER_CS_4.usb4Version >> 5)) /* Major version is 0  = TBT3 router */
    {
        UINT32 len = 0;
        usb4_router_TBT3_VSEC1 vsec1 = {0};
        USB4_ASSERT(0 == Usb4RouterSearchVsecCapability(router_ctx, USB4_ROUTER_VSEC_CAP_1, &len, NULL));
        USB4_ASSERT(len >= sizeof(vsec1));
        USB4_ASSERT(0 == Usb4RouterReadCapability(router_ctx, (UINT8*)(&vsec1),
                    sizeof(vsec1)));

        if (0 != vsec1.VSEC_CS1.plugEventDisable)
        {
            vsec1.VSEC_CS1.plugEventDisable = 0;
            USB4_ASSERT(0 == Usb4RouterWriteCapability(router_ctx, (UINT8*)(&vsec1),
                        sizeof(vsec1)));
        }
    }

    USB4_ASSERT(0 == Usb4RouterEnumeratePorts(router_ctx));

    /* Sanity check - router_ctx->m_cs.ROUTER_CS_1.upstreamAdapter need to be Lane0. */
    if ((0 != router_ctx->m_topologyID) && (0 != router_ctx->m_cs.ROUTER_CS_1.upstreamAdapter))
    {
        usb4_port_ctx_t* port;
        port = Usb4RouterGetAdapterPortByNumber(router_ctx, router_ctx->m_cs.ROUTER_CS_1.upstreamAdapter);
        USB4_ASSERT(USB4_portType_LANE0 == Usb4PortGetPortType(port));
    }
    USB4_ASSERT(0 == Usb4RouterGetBufferAllocations(router_ctx));

    return 0;
}

int Usb4RouterEnumeratePorts(usb4_router_ctx_t* router_ctx)
{
    UINT32 i;
    int lane0 = -1;

    UINT32 max_ports;
    USB4_portType type;

    max_ports = Usb4RouterGetNumberOfAdapters(router_ctx);

    USB4_ASSERT_MSG(1 < max_ports, "Router reports 1 or less adapters. Error.");

    max_ports = MIN(USB4_MAX_PORTS_PER_ROUTER, max_ports);

    for (i = 1; i < max_ports; ++i) /* skip port0 (usb port) */
    {
        USB4_ASSERT(0 == Usb4PortReadCS(&router_ctx->m_Ports[i]));

        USB4_ASSERT(i == router_ctx->m_Ports[i].m_Number);

        type = Usb4PortGetPortType(&router_ctx->m_Ports[i]);
        if (USB4_portType_LANE0 == type)
        {
            if (lane0 < 0)
            {
                lane0 = i;
            }
            else
            {
                if ((lane0 + 1) == (int)(i))
                {
                    router_ctx->m_Ports[lane0].m_OtherLaneGroupNumber = i;
                    router_ctx->m_Ports[i].m_OtherLaneGroupNumber = lane0;
                    Usb4PortSetSubordinate(&router_ctx->m_Ports[i]);
                    router_ctx->m_Ports[i].m_hotplug.pLane0Hotplug = &router_ctx->m_Ports[lane0].m_hotplug;
                    lane0 = -1;
                }
            }

            USB4_ASSERT(0 == Usb4PortTmuTimeSync(&router_ctx->m_Ports[i], FALSE)); /* Disable time sync on all the ports, until TMU is configured */
        }

        if (USB4_portType_NOT_VALID != type)
        {
            // USB4_LOG_INFO("Router %x, Port %u has type %s, Total buffers %u\n", USB4_LOWER32(router_ctx->m_topologyID) ,i,
            //         Usb4PortGetName(&router_ctx->m_Ports[i]), Usb4PortGetFreeBuffers(&router_ctx->m_Ports[i]));
            Usb4Log3(USB4_LOG_CM, Usb4RouterEnumeratePorts__Params__Router_Port_TotalBuffers, 0, USB4_LOWER32(router_ctx->m_topologyID), i,
                    Usb4PortGetFreeBuffers(&router_ctx->m_Ports[i]));
        }
        else
        {
            // USB4_LOG_INFO("Router %x, Port %u has type %s\n", USB4_LOWER32(router_ctx->m_topologyID) ,i,
            //         Usb4PortGetName(&router_ctx->m_Ports[i]));
            Usb4Log2(USB4_LOG_CM, Usb4RouterEnumeratePorts__Params__Router_Port, 0, USB4_LOWER32(router_ctx->m_topologyID), i);
        }
    }

    return 0;
}

int Usb4RouterBondLanes(usb4_router_ctx_t* router_ctx, UINT32 adapter_first, UINT32 adapter_second)
{
    USB4_portState portState0, portState1;

    if (USB4_portType_LANE0 == Usb4PortGetPortType(&router_ctx->m_Ports[adapter_first]))
    {
        if (USB4_portType_LANE1 == Usb4PortGetPortType(&router_ctx->m_Ports[adapter_second]))
        {
            USB4_ASSERT(0 == Usb4PortGetPortState(&router_ctx->m_Ports[adapter_first], &portState0));
            USB4_ASSERT(0 == Usb4PortGetPortState(&router_ctx->m_Ports[adapter_second], &portState1));
            if ((USB4_portState_CL0 == portState0) && (USB4_portState_CL0 == portState1))
            {
                if (0 != Usb4PortBondLanes(&router_ctx->m_Ports[adapter_first]))
                {
                    USB4_ERROR_STACK(-1);
                    goto ErrorHandling;
                }
            }
        }
    }
    else
    {
        USB4_ASSERT_MSG(0, "Attempting to bond lanes on a non-usb4 port");
    }

    return 0;
ErrorHandling:
    return -1;
}

BOOLEAN Usb4RouterIsBonded(usb4_router_ctx_t* router_ctx, UINT32 adapter)
{
    if (USB4_portType_LANE0 == Usb4PortGetPortType(&router_ctx->m_Ports[adapter]))
    {
        return router_ctx->m_Ports[adapter].m_bIsBound;
    }

    if (USB4_portType_LANE1 == Usb4PortGetPortType(&router_ctx->m_Ports[adapter]))
    {
        return router_ctx->m_Ports[adapter-1].m_bIsBound;
    }

    return FALSE;
}

int Usb4RouterDfpConnected(usb4_router_ctx_t* router_ctx, UINT32 adapter, BOOLEAN* bConnected)
{
    USB4_portState portState;
    USB4_ASSERT(NULL != bConnected);
    USB4_ASSERT(adapter < Usb4RouterGetNumberOfAdapters(router_ctx));
    USB4_ASSERT (0 == Usb4PortGetPortState(&router_ctx->m_Ports[adapter], &portState));

    if ((portState >= USB4_portState_CL0) && (portState < USB4_portState_CLd))
    {
        *bConnected = TRUE;
    }
    else
    {
        *bConnected = FALSE;
    }
    return 0;
}

int Usb4RouterDfpInCL0(usb4_router_ctx_t* router_ctx, UINT32 adapter, BOOLEAN* bInCL0)
{
    USB4_portState portState;
    USB4_ASSERT(NULL != bInCL0);
    USB4_ASSERT(adapter < Usb4RouterGetNumberOfAdapters(router_ctx));
    USB4_ASSERT (0 == Usb4PortGetPortState(&router_ctx->m_Ports[adapter], &portState));

    if (portState == USB4_portState_CL0)
    {
        *bInCL0 = TRUE;
    }
    else
    {
        *bInCL0 = FALSE;
    }

    return 0;
}

int Usb4RouterDisconnectAdapter(usb4_router_ctx_t* router_ctx, UINT32 adapter)
{
    USB4_ASSERT(adapter < Usb4RouterGetNumberOfAdapters(router_ctx));

    if ((USB4_portType_LANE0 == Usb4PortGetPortType(&router_ctx->m_Ports[adapter]))||
            (USB4_portType_LANE1 == Usb4PortGetPortType(&router_ctx->m_Ports[adapter])))
    {
        USB4_ASSERT(0 == Usb4PortLaneDisable(&router_ctx->m_Ports[adapter]));
    }
    else
    {
        //TODO: Handle DP disconnect
    }
    return 0;
}

int Usb4RouterReconnectAdapter(usb4_router_ctx_t* router_ctx, UINT32 adapter)
{
    USB4_ASSERT(adapter < Usb4RouterGetNumberOfAdapters(router_ctx));

    if ((USB4_portType_LANE0 == Usb4PortGetPortType(&router_ctx->m_Ports[adapter]))||
            (USB4_portType_LANE1 == Usb4PortGetPortType(&router_ctx->m_Ports[adapter])))
    {
        USB4_ASSERT(0 == Usb4PortLaneEnable(&router_ctx->m_Ports[adapter]));
    }
    else
    {
        //TODO: Handle DP disconnect
    }
    return 0;
}

int Usb4RouterResetAdapter(usb4_router_ctx_t* router_ctx, UINT32 adapter)
{
    usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;

    USB4_ASSERT(adapter < Usb4RouterGetNumberOfAdapters(router_ctx));
    USB4_ASSERT(USB4_portType_LANE0 == Usb4PortGetPortType(&router_ctx->m_Ports[adapter]));


    USB4_ASSERT(0 == Usb4PortPortReset(&router_ctx->m_Ports[adapter], 1));
    usb4_timer_Sleep_ms(&timer, 10);  /* CM guide recommends waiting for 10msec */
    

    USB4_ASSERT(0 == Usb4PortPollForLockState(&router_ctx->m_Ports[adapter], 1));
    /* Both lanes will become locked */
    if (((adapter+1 < Usb4RouterGetNumberOfAdapters(router_ctx))) &&
            (USB4_portType_LANE1 == Usb4PortGetPortType(&router_ctx->m_Ports[adapter+1])))
    {
        USB4_ASSERT(0 == Usb4PortPollForLockState(&router_ctx->m_Ports[adapter+1], 1));
    }
    USB4_ASSERT(0 == Usb4PortPortReset(&router_ctx->m_Ports[adapter], 0));

    USB4_ASSERT(0 == Usb4PortLaneEnable(&router_ctx->m_Ports[adapter]));

    if (((adapter+1 < Usb4RouterGetNumberOfAdapters(router_ctx))) &&
            (USB4_portType_LANE1 == Usb4PortGetPortType(&router_ctx->m_Ports[adapter+1])))
    {
        USB4_ASSERT(0 == Usb4PortLaneEnable(&router_ctx->m_Ports[adapter+1]));
    }

    return 0;
}

int Usb4RouterAdapterHotPlug(usb4_router_ctx_t* router_ctx, UINT32 adapter, UINT32 unplug_flag)
{
    USB4_ASSERT(adapter < Usb4RouterGetNumberOfAdapters(router_ctx));

    if (1 == unplug_flag)
    {
        //TODO: Handle ADP un-plug. Revert resources to router?
    }
    else
    {
        //TODO: Handle ADP plug-in. Reserve resources from router?
    }

    if (USB4_portType_DP_OUT == Usb4PortGetPortType(&router_ctx->m_Ports[adapter]))
    {
        if (1 == unplug_flag)
        {
            router_ctx->m_bDpTunneling = FALSE;
            router_ctx->m_displayPortAdapter = 0;
        }
        else
        {
            router_ctx->m_bDpTunneling = TRUE;
            router_ctx->m_displayPortAdapter = adapter;
        }
    }

    return 0;
}

int Usb4RouterUnlockAdapter(usb4_router_ctx_t* router_ctx, UINT32 adapter)
{
    USB4_ASSERT(adapter < Usb4RouterGetNumberOfAdapters(router_ctx));
    USB4_ASSERT(0 == Usb4PortUnlock(&router_ctx->m_Ports[adapter]));
    /* Update complete configuration space - Needed to keep track of plugged status */
    USB4_ASSERT(0 == Usb4PortReadCS(&router_ctx->m_Ports[adapter]));
    return 0;
}

int Usb4RouterLoopingTopologyAdapter(usb4_router_ctx_t* router_ctx, UINT32 adapter)
{
    router_ctx->m_Ports[adapter].m_bIsLoop = TRUE;
    Usb4PortLaneDisable(&router_ctx->m_Ports[adapter]);
    return 0;
}

int Usb4RouterInterdomainAdapter(usb4_router_ctx_t* router_ctx, UINT32 adapter, BOOLEAN isInterdomain)
{
    if (isInterdomain)
    {
        if (0 != Usb4PortSetInterdomain(&router_ctx->m_Ports[adapter], TRUE))
        {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
        }
        router_ctx->m_Ports[adapter].m_bIsInterdomain = TRUE;
        router_ctx->m_bInterdomainRouter = TRUE;
    }
    else
    {
        router_ctx->m_Ports[adapter].m_bIsInterdomain = FALSE;
        if (0 != Usb4PortSetInterdomain(&router_ctx->m_Ports[adapter], FALSE))
        {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
        }
    }
    return 0;
ErrorHandling:
    return -1;
}

USB4_portType Usb4RouterGetPortType(usb4_router_ctx_t* router_ctx, UINT32 adapter)
{
    USB4_ASSERT(adapter < Usb4RouterGetNumberOfAdapters(router_ctx));

    return Usb4PortGetPortType(&router_ctx->m_Ports[adapter]);
#if 0
ErrorHandling:
    return USB4_portType_NOT_VALID;
#endif
}

usb4_port_ctx_t* Usb4RouterGetAdapterPortByNumber(usb4_router_ctx_t* router_ctx, UINT32 adapter)
{
    USB4_ASSERT(adapter < Usb4RouterGetNumberOfAdapters(router_ctx));

    return &router_ctx->m_Ports[adapter];
#if 0
ErrorHandling:
    return NULL;
#endif
}

UINT32 Usb4RouterGetNumberOfAdapters(usb4_router_ctx_t* router_ctx)
{
    return router_ctx->m_cs.ROUTER_CS_1.maxAdapter + 1;
}

int Usb4RouterAssignTopologyID(usb4_router_ctx_t* router_ctx, UINT64 topologyID)
{
    UINT32 i;

    USB4_ASSERT_MSG(USB4_INVALID_TOPOLOGY_ID != topologyID, "Invalid topology Id\n");

    router_ctx->m_topologyID = topologyID;

    for (i = 0; i < USB4_MAX_PORTS_PER_ROUTER; i++)
    {
        if (0 != Usb4PortSetTopologyId(&router_ctx->m_Ports[i], router_ctx->m_topologyID))
        {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
        }
    }

    return 0;
ErrorHandling:
    return 1;
};

int Usb4RouterGetTopologyId(usb4_router_ctx_t* router_ctx, UINT64* pRoute)
{
    if (USB4_INVALID_TOPOLOGY_ID == router_ctx->m_topologyID)
    {
        USB4_ERROR_STACK_MSG(-1, "Non assigned topology ID");
        return -1;
    }
    if (NULL == pRoute)
    {
        USB4_ERROR_STACK_MSG(-1, "Invlaid params");
        return -1;
    }

    *pRoute = router_ctx->m_topologyID;
    return 0;
}

usb4_port_ctx_t* Usb4RouterGetAdapterPortByType(usb4_router_ctx_t* router_ctx, USB4_portType type,
        UINT32 startFromAdapter)
{
    UINT32 adapter;

    if (USB4_portType_NOT_VALID == type)
    {
        return NULL;
    }

    for(adapter = startFromAdapter; adapter < Usb4RouterGetNumberOfAdapters(router_ctx); adapter++)
    {
        if (adapter >= USB4_MAX_PORTS_PER_ROUTER)
        {
            USB4_ASSERT(adapter >= USB4_MAX_PORTS_PER_ROUTER);
            break;
        }
        if (Usb4RouterGetPortType(router_ctx, adapter) == type)
        {
            return &router_ctx->m_Ports[adapter];
        }
    }

    return NULL;
};

usb4_port_ctx_t* Usb4RouterGetInterdomainAdapter(usb4_router_ctx_t* router_ctx, UINT32 startFromAdapter)
{
    UINT32 adapter;

    for(adapter = startFromAdapter; adapter < Usb4RouterGetNumberOfAdapters(router_ctx); adapter++)
    {
        if (router_ctx->m_Ports[adapter].m_bIsInterdomain)
        {
            return &router_ctx->m_Ports[adapter];
        }
    }

    return NULL;
};

int Usb4RouterEnablePcieTunneling(usb4_router_ctx_t* router_ctx)
{
    router_ctx->m_cs.ROUTER_CS_5.pcieTunnelingOn = 1;
    return 0;
}


int Usb4RouterEnableUsb3Tunneling(usb4_router_ctx_t* router_ctx)
{
    router_ctx->m_cs.ROUTER_CS_5.usb3TunnelingOn = 1;
    return 0;
}

int Usb4RouterSetConfigurationValid(usb4_router_ctx_t* router_ctx)
{
    router_ctx->m_cs.ROUTER_CS_5.configurationValid = 1;

    if (0 != Usb4RouterWriteCSDword(router_ctx, 5, 1))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    if (0 != Usb4RouterPollCR(router_ctx, 100000))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    return 0;
ErrorHandling:
    return -1;
}

int Usb4RouterSetNotificationTimeout(usb4_router_ctx_t* router_ctx, UINT8 timeout)
{
    router_ctx->m_cs.ROUTER_CS_4.notificationTimeout = timeout;

    if (0 != Usb4RouterWriteCSDword(router_ctx, 4, 1))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    return 0;
ErrorHandling:
    return -1;
}


int Usb4RouterIssueCommand(usb4_router_ctx_t* router_ctx, usb4_router_operations_cs* routerOperation,
        UINT64 usTimeout)
{
    UINT8* pBuff = (UINT8*)(routerOperation);
    UINT32 len;
    UINT32 write_len = sizeof(usb4_router_operations_cs);
    usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;
    UINT32 elapsed_us;
    BOOLEAN result;

    USB4_ASSERT(0 == Usb4CtrlIfaceSetType(router_ctx->m_pControl, USB4_cpDescriptorType_WRITE_REQUEST));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetRoute(router_ctx->m_pControl, router_ctx->m_topologyID));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(router_ctx->m_pControl, 9));    //DWORD at address ROUTER_CS_9
    USB4_ASSERT(0 == Usb4CtrlIfaceSetAdapter(router_ctx->m_pControl, 0));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetCS(router_ctx->m_pControl, USB4_cpConfigSpace_ROUTER));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetData(router_ctx->m_pControl, pBuff, write_len - 4)); /* Don't write the operation yet */

    if (0 != Usb4CtrlIfaceSend(router_ctx->m_pControl, USB4_SEND_CTRL_PACKET_TIMEOUT_US))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    USB4_ASSERT(0 == Usb4CtrlIfaceVerifyReadWriteResponse(router_ctx->m_pControl, &result));
    USB4_ASSERT(TRUE == result);
    USB4_ASSERT(0 == Usb4CtrlIfacePop(router_ctx->m_pControl));

    /* Now write a command DWORD */
    USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(router_ctx->m_pControl, 26));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetData(router_ctx->m_pControl, &pBuff[17], 1)); /* Don't write the operation yet */
    USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(router_ctx->m_pControl, 26));
    routerOperation->ROUTER_CS_26.OpValid = 1;
    USB4_ASSERT(0 == Usb4CtrlIfaceSetData(router_ctx->m_pControl, (UINT8*)(&routerOperation->ROUTER_CS_26), 4)); /* Don't write the operation yet */
    USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(router_ctx->m_pControl, 26));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetData(router_ctx->m_pControl, (UINT8*)(&(routerOperation->ROUTER_CS_26)), 1)); /* Don't write the operation yet */

    if (0 != Usb4CtrlIfaceSend(router_ctx->m_pControl, USB4_SEND_CTRL_PACKET_TIMEOUT_US))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    USB4_ASSERT(0 == Usb4CtrlIfaceVerifyReadWriteResponse(router_ctx->m_pControl, &result));
    USB4_ASSERT(TRUE == result);
    USB4_ASSERT(0 == Usb4CtrlIfacePop(router_ctx->m_pControl));

    USB4_ASSERT(0 == Usb4CtrlIfaceSetType(router_ctx->m_pControl, USB4_cpDescriptorType_READ_REQUEST));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(router_ctx->m_pControl, 9));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetAdapter(router_ctx->m_pControl, 0));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetCS(router_ctx->m_pControl, USB4_cpConfigSpace_ROUTER));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetData(router_ctx->m_pControl, NULL, write_len));

    usb4_timer_Start(&timer);
    do
    {
        if(0 != Usb4CtrlIfaceSend(router_ctx->m_pControl, usTimeout))
        {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
        }

        USB4_ASSERT(0 == Usb4CtrlIfaceGetData(router_ctx->m_pControl, pBuff, &len, write_len));
        USB4_ASSERT(0 == Usb4CtrlIfacePop(router_ctx->m_pControl));

        USB4_ASSERT_MSG(len == write_len, "Didn't read a complete CS");
        USB4_ASSERT(0 == usb4_timer_GetElapsed_us(&timer, &elapsed_us));;
#ifndef USB4_COMPILING_GEN_EMU_VELOCE
        USB4_ASSERT_MSG(usTimeout > elapsed_us, "Timeout value exceeded");
#endif
    } while (1 == routerOperation->ROUTER_CS_26.OpValid);

    return 0;
ErrorHandling:
    return -1;
}

int Usb4RouterIssueRouterOperation(usb4_router_ctx_t* router_ctx, usb4_router_operation_params* routerOperation, UINT64 usTimeout)
{

    usb4_ctrl_iface_trn transfer = {0};
    struct
    {
        UINT32 Opcode    :16;
        UINT32 resCs26   : 8;
        UINT32 Status    : 6;
        UINT32 ONS       : 1;
        UINT32 OpValid   : 1;
    }routerDW26_out = {0}, routerDW26_in = {0};

    UINT32 maxTimeOutForResponse_ms = 100;
    int rc = 0;

    /* Send the data */
    transfer.type = USB4_cpDescriptorType_WRITE_REQUEST;
    transfer.topologyId = router_ctx->m_topologyID;
    transfer.timeout_us = usTimeout;
    transfer.adapterNum = 0;
    transfer.address = ROUTER_OPERATION_DATA_DW;
    transfer.cs = USB4_cpConfigSpace_ROUTER;
    transfer.pBuff = (UINT8*)(&(routerOperation->data[0]));
    transfer.size_bytes = 16 * sizeof(UINT32);

    USB4_ASSERT(0 == Usb4CtrlIfaceTransfer(router_ctx->m_pControl, &transfer));

    /* Send metadata */
    transfer.type = USB4_cpDescriptorType_WRITE_REQUEST;
    transfer.address = ROUTER_OPERATION_METADATA_DW; //metaData
    transfer.size_bytes = 4;
    transfer.pBuff = (UINT8*)(&(routerOperation->metaData));
    USB4_ASSERT(0 == Usb4CtrlIfaceTransfer(router_ctx->m_pControl, &transfer));

    /* Initiate operation */
    transfer.type = USB4_cpDescriptorType_WRITE_REQUEST;
    transfer.address = 26;//ROUTER_CS_26
    routerDW26_out.Opcode = (UINT32)(routerOperation->opcode);
    routerDW26_out.OpValid = 1;
    transfer.size_bytes = sizeof(routerDW26_out);
    transfer.pBuff = (UINT8*)(&routerDW26_out);
    USB4_ASSERT(0 == Usb4CtrlIfaceTransfer(router_ctx->m_pControl, &transfer));

    /* Setup the command to poll execution status */
    transfer.type = USB4_cpDescriptorType_READ_REQUEST;
    transfer.timeout_us = usTimeout;
    transfer.address = 26;//ROUTER_CS_26
    transfer.size_bytes = sizeof(routerDW26_in);
    transfer.pBuff = (UINT8*)(&routerDW26_in);

    /* Wait for response */
    routerDW26_in.OpValid = 1;
    USB4_WHILE_WITH_TIMEOUT((0 != routerDW26_in.OpValid) &&
            (0 == Usb4CtrlIfaceTransfer(router_ctx->m_pControl, &transfer)),
            maxTimeOutForResponse_ms,
            rc)
        USB4_ASSERT(0 == rc);

    /* Operation executed */
    USB4_ASSERT(0 == routerDW26_in.OpValid);

    /* Operation not supported */
    USB4_ASSERT(0 == routerDW26_in.ONS);
    routerOperation->status = routerDW26_in.Status;

    /* Create transfer to read the metadata */
    transfer.type = USB4_cpDescriptorType_READ_REQUEST;
    transfer.timeout_us = usTimeout;
    transfer.address = ROUTER_OPERATION_METADATA_DW;
    transfer.size_bytes = 4;
    transfer.pBuff = (UINT8*)(&routerDW26_in);
    transfer.pBuff = (UINT8*)(&(routerOperation->metaData));
    USB4_ASSERT(0 == Usb4CtrlIfaceTransfer(router_ctx->m_pControl, &transfer));

    /* Create transfer to read the data */
    transfer.address = ROUTER_OPERATION_DATA_DW;
    transfer.size_bytes = 64;
    transfer.pBuff = (UINT8*)(&(routerOperation->data));
    USB4_ASSERT(0 == Usb4CtrlIfaceTransfer(router_ctx->m_pControl, &transfer));

    return 0;
}

int Usb4RouterQueryDpResource(usb4_router_ctx_t* router_ctx, UINT32 dpNumber)
{
    int result;
    usb4_router_operation_params oper = {};
    UINT64 timeout_ms = 1000;

    oper.opcode = USB4_ROUTER_OPERATION_QUERY_DP_RESOURCE_AVAILABILITY;
    oper.metaData = dpNumber;

    result = Usb4RouterIssueRouterOperation(router_ctx, &oper, timeout_ms);
    if (0 != result)
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }

    switch (oper.status)
    {
        case 0:
            return 0;
        case 1:
            USB4_ERROR_STACK_MSG(-1, "no DP resouce was detected");
            break;
        default:
            USB4_ERROR_STACK_MSG(-1, "Unknown status result");
            break;
    }

    return -1;
}

int Usb4RouterAllocateDeAllocateDpResource(usb4_router_ctx_t* router_ctx, UINT32 dpNumber, BOOLEAN allocate)
{
    int result;
    usb4_router_operation_params oper = {};
    UINT64 timeout_ms = 1000;

    if (TRUE == allocate)
    {
        oper.opcode = USB4_ROUTER_OPERATION_ALLOCATE_DP_RESOURCE;
    }
    else
    {
        oper.opcode = USB4_ROUTER_OPERATION_DE_ALLOCATE_DP_RESOURCE;
    }
    oper.metaData = dpNumber;

    result = Usb4RouterIssueRouterOperation(router_ctx, &oper, timeout_ms);
    if (0 != result)
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }

    switch (oper.status)
    {
        case 0:
            return 0;
        case 1:
            if (TRUE == allocate )
            {
                USB4_ERROR_STACK_MSG(-1, "Resource was not allocated");
            }else
            {
                USB4_ERROR_STACK_MSG(-1, "Resource was not deallocated");
            }
            break;
        default:
            USB4_ERROR_STACK_MSG(-1, "Unknown status result");
            break;
    }

    return -1;
}

int Usb4RouterPrepareSleep(usb4_router_ctx_t* router_ctx)
{
    USB4_portType type;
    usb4_usb4_port_cs usb4_port_cs = {0};
    UINT32 i;

    if (0x20 == router_ctx->m_cs.ROUTER_CS_4.usb4Version)
    {
        for (i = 1; i < Usb4RouterGetNumberOfAdapters(router_ctx); ++i) /* skip port0 (usb port) */
        {
            usb4_port_ctx_t* pPort = NULL;
            pPort = &router_ctx->m_Ports[i];
            type = Usb4PortGetPortType(pPort);
            if (USB4_portType_LANE0 == type)
            {
                USB4_ASSERT(0 == Usb4PortSearchCapability(pPort, USB4_USB4_PORT_CAPABILITY, NULL));
                if (0 != Usb4PortReadCapability(pPort, (UINT8*)(&usb4_port_cs), sizeof(usb4_port_cs)))
                {
                    USB4_ERROR_STACK(-1);
                    goto ErrorHandling;
                }

                /* Print statuses */
                // USB4_LOG_INFO("Wake sources: Topology %x, Port %u (%s), WakeonConnectStatus %u,"
                //         "WakeonDisconnectStatus %u, WakeonInterDomainStatus %u, WakeonUSB4WakeStatus %u\n",
                //         USB4_LOWER32(router_ctx->m_topologyID), pPort->m_Number, Usb4PortGetName(pPort),
                //         usb4_port_cs.PORT_CS_18.WakeonConnectStatus,
                //         usb4_port_cs.PORT_CS_18.WakeonDisconnectStatus,
                //         usb4_port_cs.PORT_CS_18.WakeonInterDomainStatus,
                //         usb4_port_cs.PORT_CS_18.WakeonUSB4WakeStatus);
                Usb4Log3(USB4_LOG_CM, Usb4RouterPrepareSleepWakeSources__Params__Topology_Port_WakeonConnectStatus, 0,
                        USB4_LOWER32(router_ctx->m_topologyID), pPort->m_Number, usb4_port_cs.PORT_CS_18.WakeonConnectStatus);
                Usb4Log3(USB4_LOG_CM, Usb4RouterPrepareSleepWakeSources__Params__WakeonDisconnectStatus_WakeonInterDomainStatus_WakeonUSB4WakeStatus, 0,
                        usb4_port_cs.PORT_CS_18.WakeonDisconnectStatus,
                        usb4_port_cs.PORT_CS_18.WakeonInterDomainStatus,
                        usb4_port_cs.PORT_CS_18.WakeonUSB4WakeStatus);

                usb4_port_cs.PORT_CS_19.EnableWakeOnUsb4Wake = 0;
                usb4_port_cs.PORT_CS_19.EnableWakeOnDisconnect = 0;
                usb4_port_cs.PORT_CS_19.EnableWakeOnConnect = 0;
                usb4_port_cs.PORT_CS_19.USB4PortIsConfigured = 0;


                if (router_ctx->m_cs.ROUTER_CS_1.upstreamAdapter == i)
                {
                    usb4_port_cs.PORT_CS_19.USB4PortIsConfigured = 1;
                    usb4_port_cs.PORT_CS_19.EnableWakeOnUsb4Wake = router_ctx->m_bDisableWakeOnUsb4?0:1;
                }
                else
                {
                    if (pPort->m_bIsInterdomain)
                    {
                        usb4_port_cs.PORT_CS_19.USB4PortIsConfigured = 1;
                        usb4_port_cs.PORT_CS_19.EnableWakeOnInterdomain = router_ctx->m_bDisableWakeOnInterdomain?0:1;
                    }
                    else if (1 == pPort->m_cs.ADP_CS_4.Plugged)
                    {
                        usb4_port_cs.PORT_CS_19.USB4PortIsConfigured = 1;
                        usb4_port_cs.PORT_CS_19.EnableWakeOnDisconnect = router_ctx->m_bDisableWakeOnDisconnect?0:1;
                        usb4_port_cs.PORT_CS_19.EnableWakeOnUsb4Wake = router_ctx->m_bDisableWakeOnUsb4?0:1;
                    }
                    else
                    {
                        usb4_port_cs.PORT_CS_19.EnableWakeOnConnect = router_ctx->m_bDisableWakeOnConnect?0:1;
                    }
                }

                if (0 != Usb4PortWriteCapability(pPort, (UINT8*)(&usb4_port_cs), sizeof(usb4_port_cs)))
                {
                    USB4_ERROR_STACK(-1);
                    goto ErrorHandling;
                }
            }
        }
    }
    else
    {
        /* TBT3 device router */
        usb4_router_access_vsec6 accessVsec6;
        UINT32 value = 0, i, numOfPorts = 2;
        UINT32 len = 0;
        usb4_router_TBT3_VSEC1 vsec1 = {0};
        UINT32 nextPortNumber = 0;
        usb4_port_ctx_t* pPort;
        USB4_portState portState;

        /* Prohibit hot plug/unplug notifications */
        USB4_ASSERT(0 == Usb4RouterSearchVsecCapability(router_ctx, USB4_ROUTER_VSEC_CAP_1, &len, NULL));
        USB4_ASSERT(len >= sizeof(vsec1));
        USB4_ASSERT(0 == Usb4RouterReadCapability(router_ctx, (UINT8*)(&vsec1),
                    sizeof(vsec1)));

        vsec1.VSEC_CS1.plugEventDisable = 0xF;
        USB4_ASSERT(0 == Usb4RouterWriteCapability(router_ctx, (UINT8*)(&vsec1),
                    sizeof(vsec1)));

        accessVsec6.buff = (UINT8*)(&value);
        accessVsec6.pNumberOfPorts = &numOfPorts;

        for (i = 0; i < numOfPorts; i++)
        {
            /* =============== ID_WAKE ==================*/
            accessVsec6.command = READ;
            accessVsec6.numDwords = 1;
            accessVsec6.offsetDwords = 43;
            accessVsec6.portNumber = i;
            USB4_ASSERT(0 == Usb4RouterVsec6AcceessPort(router_ctx, &accessVsec6));
            value &= ~(0x1L<<5);
            accessVsec6.command = WRITE;
            USB4_ASSERT(0 == Usb4RouterVsec6AcceessPort(router_ctx, &accessVsec6));

            /* =============== LC_SX_CTRL ==================*/
            accessVsec6.command = READ;
            accessVsec6.numDwords = 1;
            accessVsec6.offsetDwords = 150;
            accessVsec6.portNumber = i;
            USB4_ASSERT(0 == Usb4RouterVsec6AcceessPort(router_ctx, &accessVsec6));
            /* Expect first port in VSEC to correspond to the first port in the regular adapter CS */
            pPort = Usb4RouterGetAdapterPortByType(router_ctx, USB4_portType_LANE0, nextPortNumber);
            if (NULL != pPort)
            {
                nextPortNumber = pPort->m_Number + 1;
                USB4_ASSERT(0 == Usb4PortGetPortState(pPort, &portState));
                if ((USB4_portState_TRAINING<=portState)&&(portState < USB4_portState_CLd))
                {
                    value |= 0x766|(1<<16)|(1<<20)|(0xE0<<24);
                }
                else
                {
                    value |= 0x766|(0xA0<<24);
                }

            }
            else
            {
                value |= 0x766|(0xA0<<24);
            }
            accessVsec6.command = WRITE;
            USB4_ASSERT(0 == Usb4RouterVsec6AcceessPort(router_ctx, &accessVsec6));

        }
    }


    return 0;
ErrorHandling:
    return -1;
}

int Usb4RouterCheckSleepReady(usb4_router_ctx_t* router_ctx)
{
    if (0x20 == router_ctx->m_cs.ROUTER_CS_4.usb4Version)
    {
        if (1 == router_ctx->m_cs.ROUTER_CS_5.enterSleep)
        {
            USB4_ASSERT(0 == Usb4RouterPollSLRP(router_ctx, 50000));
        }
    }
    else
    {
        usb4_utils_timer timer;
        timer.m_source = USB4_TIMER_SOURCE_QTIMER;
        usb4_timer_Sleep_ms(&timer, 100);
    }
    return 0;
}

int Usb4RouterSetEnterSleep(usb4_router_ctx_t* router_ctx)
{
    if (0x20 == router_ctx->m_cs.ROUTER_CS_4.usb4Version)
    {
        if (router_ctx->m_cs.ROUTER_CS_6.routerReady || router_ctx->m_cs.ROUTER_CS_6.configurationReady)
        {
            router_ctx->m_cs.ROUTER_CS_5.enterSleep = 1;
            if (0 != router_ctx->m_topologyID)
            {
                router_ctx->m_cs.ROUTER_CS_5.enableWakeonPCIe = 1;
                router_ctx->m_cs.ROUTER_CS_5.enableWakeonDP = 1;
                if (0x20 == router_ctx->m_cs.ROUTER_CS_4.usb4Version)
                {
                    router_ctx->m_cs.ROUTER_CS_5.enableWakeonUSB3 = 1;
                }
            }
            USB4_ASSERT(0 == Usb4RouterWriteCSDword(router_ctx, 5, 1));
        }
    }
    return 0;
}

int Usb4RouterConfigureRequestRsFec(usb4_router_ctx_t* router_ctx, BOOLEAN bDisableRsFec)
{
    usb4_usb4_port_cs usb4_port_cs = {0};
    usb4_port_ctx_t* pPort;

    pPort = Usb4RouterGetAdapterPortByType(router_ctx, USB4_portType_LANE0, 0);
    USB4_ASSERT(NULL != pPort);
    USB4_ASSERT(0 == Usb4PortSearchCapability(pPort, USB4_USB4_PORT_CAPABILITY, NULL));
    USB4_ASSERT(0 == Usb4PortReadCapability(pPort, (UINT8*)(&usb4_port_cs), sizeof(usb4_port_cs)));
    usb4_port_cs.PORT_CS_19.RequestRS_FECGen2_RS2 = bDisableRsFec ? 0:1;
    usb4_port_cs.PORT_CS_19.RequestRS_FECGen3_RS3 = bDisableRsFec ? 0:1;
    USB4_ASSERT(0 == Usb4PortWriteCapability(pPort, (UINT8*)(&usb4_port_cs), sizeof(usb4_port_cs)));

    return 0;
}

int Usb4RouterLimitTargetLinkSpeedToGen2(usb4_router_ctx_t* router_ctx, BOOLEAN bLimitToGen2)
{
    usb4_lane_adp_cs lane_adp_cs = {0};
    UINT32 targetLinkSpeed = 0xC;
    UINT32 i;

#ifndef ASIC
    USB4_ASSERT_MSG(TRUE == bLimitToGen2, "Has to limit link speed to Gen2 on emulation");
#endif

    if (bLimitToGen2)
    {
        targetLinkSpeed = 0x8;
    }

    for (i = 1; i < Usb4RouterGetNumberOfAdapters(router_ctx); ++i) /* skip port0 (usb port) */
    {
        if (USB4_portType_LANE0 == Usb4PortGetPortType(&router_ctx->m_Ports[i]))
        {
            USB4_ASSERT(0 == Usb4PortReadLaneAdpCS(&router_ctx->m_Ports[i], &lane_adp_cs));

            lane_adp_cs.LANE_ADP_CS_1.TargetLinkSpeed = targetLinkSpeed;
            USB4_ASSERT(0 == Usb4PortWriteLaneAdpCS(&router_ctx->m_Ports[i], &lane_adp_cs));
            if (((i+1) < Usb4RouterGetNumberOfAdapters(router_ctx)) && (USB4_portType_LANE1 == Usb4PortGetPortType(&router_ctx->m_Ports[i+1])))
            {
                USB4_ASSERT(0 == Usb4PortReadLaneAdpCS(&router_ctx->m_Ports[i+1], &lane_adp_cs));
                lane_adp_cs.LANE_ADP_CS_1.TargetLinkSpeed = targetLinkSpeed;
                USB4_ASSERT(0 == Usb4PortWriteLaneAdpCS(&router_ctx->m_Ports[i+1], &lane_adp_cs));
            }
        }
    }
    return 0;
}


int Usb4RouterVerifyLinkSpeedWidth(usb4_router_ctx_t* router_ctx)
{
    usb4_lane_adp_cs lane_adp_cs = {0};
    int result = 0;
    UINT32 i;
    UINT32 exp_width;
    UINT32 exp_speed;
    UINT32 speed;
    UINT32 width;
    USB4_portType port;

    
    // USB4_HOST_ROUTER_0USB4_L0_LANE_ADP_CS_1_STANDARD . CURRENT_LINK_SPEED / NEGOTIATED_LINK_WIDTH
    for (i = 1; i < Usb4RouterGetNumberOfAdapters(router_ctx); ++i) /* skip port0 (usb port) */
    {
        port = Usb4PortGetPortType(&router_ctx->m_Ports[i]);
        if ((USB4_portType_LANE0 == port) || (USB4_portType_LANE1 == port))
        {
            USB4_ASSERT(0 == Usb4PortReadLaneAdpCS(&router_ctx->m_Ports[i], &lane_adp_cs));

            if (USB4_portType_LANE0 == port)
            {
                USB4_portState portState = (USB4_portState)(lane_adp_cs.LANE_ADP_CS_1.AdapterState);
                if ((portState < USB4_portState_CL0) || (portState > USB4_portState_CLd))
                {
                    // USB4_LOG_ERROR("Core[%u] Port Lane %u Link is down.\n",
                    //                               Usb4CtrlIfaceGetCoreIndex(router_ctx->m_pControl),
                    //                               (UINT32)(port - USB4_portType_LANE0));
                    Usb4Log2(USB4_LOG_CM, Usb4RouterVerifyLinkSpeedWidthPortLaneLinkIsDown__Params__Core_Lane, 0, 
                        Usb4CtrlIfaceGetCoreIndex(router_ctx->m_pControl), (UINT32)(port - USB4_portType_LANE0));
                    USB4_ERROR_STACK(-1);
                    result = -1;
                    break;
                }
            }

            exp_speed = (lane_adp_cs.LANE_ADP_CS_1.TargetLinkSpeed == 0x8) ? 2 : 3; // gen2 or gen3
            exp_width = (lane_adp_cs.LANE_ADP_CS_1.TargetLinkWidth == 0x1) ? 1 : 2; // 1 for 1 lane, 2 for dual
            
            speed = lane_adp_cs.LANE_ADP_CS_1.CurrentLinkSpeed == 0x8 ? 2 : 3;
            width = lane_adp_cs.LANE_ADP_CS_1.NegotiatedLinkWidth;
            
            if ((exp_width != width) || (exp_speed != speed))
            {
                // USB4_LOG_ERROR("Core[%u] Port Lane %u exp : Gen%ux%u, current: Gen%ux%u\n", 
                //               Usb4CtrlIfaceGetCoreIndex(router_ctx->m_pControl),
                //               (UINT32)(port - USB4_portType_LANE0),
                //               exp_speed, exp_width, speed, width);
                Usb4Log3(USB4_LOG_CM, Usb4RouterVerifyLinkSpeedWidth__Params__Core_PortLane_ExpGen, 0, 
                    Usb4CtrlIfaceGetCoreIndex(router_ctx->m_pControl),
                    (UINT32)(port - USB4_portType_LANE0),
                    exp_speed);
                Usb4Log3(USB4_LOG_CM, Usb4RouterVerifyLinkSpeedWidth__Params__ExpWidth_Speed_Width, 0, 
                    exp_width, speed, width);
                USB4_ERROR_STACK(-1);
                result = -1;
            }
            else
            {
                // USB4_LOG_INFO("Core[%u] Port Lane %u Link is in Gen%ux%u\n", 
                //              Usb4CtrlIfaceGetCoreIndex(router_ctx->m_pControl),
                //              (UINT32)(port - USB4_portType_LANE0),
                //              speed, width);
                Usb4Log4(USB4_LOG_CM, Usb4RouterVerifyLinkSpeedWidth__Params__Core_PortLane_Speed_Width, 0, 
                    Usb4CtrlIfaceGetCoreIndex(router_ctx->m_pControl),
                    (UINT32)(port - USB4_portType_LANE0),
                    speed, width);
            }
        }
    }
    
    return result;
}


int Usb4RouterLimitToSingleLane(usb4_router_ctx_t* router_ctx, BOOLEAN bLimitToSingleLane)
{
    UINT32 i;

    if (bLimitToSingleLane)
    {
        for (i = 1; i < Usb4RouterGetNumberOfAdapters(router_ctx); ++i) /* skip port0 (usb port) */
        {
            if (USB4_portType_LANE1 == Usb4PortGetPortType(&router_ctx->m_Ports[i]))
            {
                USB4_ASSERT(0 == Usb4PortLaneDisable(&router_ctx->m_Ports[i]));
            }
        }
    }
    return 0;
}


int Usb4RouterEnableLanes(usb4_router_ctx_t* router_ctx, BOOLEAN bLimitToSingleLane)
{
    UINT32 i;

    for (i = 1; i < Usb4RouterGetNumberOfAdapters(router_ctx); ++i) /* skip port0 (usb port) */
    {
        if (USB4_portType_LANE0 == Usb4PortGetPortType(&router_ctx->m_Ports[i]))
        {
            if (router_ctx->m_Ports[i].m_bIsDisabled)
            {
                USB4_ASSERT(0 == Usb4PortLaneEnable(&router_ctx->m_Ports[i]))
            }
        }

        if (USB4_portType_LANE1 == Usb4PortGetPortType(&router_ctx->m_Ports[i]))
        {
            if (bLimitToSingleLane)
            {
                USB4_ASSERT(0 == Usb4PortLaneDisable(&router_ctx->m_Ports[i]))
            }
            else
            {
                if (router_ctx->m_Ports[i].m_bIsDisabled)
                {
                    USB4_ASSERT(0 == Usb4PortLaneEnable(&router_ctx->m_Ports[i]))
                }
            }
        }
    }
    return 0;
}


int Usb4RouterCheckCLxCompatibility(usb4_router_ctx_t* router_ctx, USB4_CLx_mode CLxMode, BOOLEAN* pbIncompatible)
{
    UINT32 i;
    USB4_ASSERT(NULL != pbIncompatible);
    for (i = 1; i < Usb4RouterGetNumberOfAdapters(router_ctx); ++i) /* skip port0 (usb port) */
    {
        if (USB4_portType_LANE0 == Usb4PortGetPortType(&router_ctx->m_Ports[i]))
        {
            usb4_usb4_port_cs usb4_port_cs = {0};
            USB4_portState portState;

            if (0 == router_ctx->m_Ports[i].m_cs.ADP_CS_4.Plugged)
            {
                continue; /* No need to do anything with unplugged port */
            }

            /* Don't set CLx on inter-domain */
            if (TRUE == router_ctx->m_Ports[i].m_bIsInterdomain)
            {
                // USB4_LOG_INFO("CLx Not Supported due to interdomain link, Router 0x%x, Port %u", USB4_LOWER32(router_ctx->m_topologyID), i);
                Usb4Log2(USB4_LOG_CM, Usb4RouterCheckCLxCompatibilityCLxNotSupportedDueToInterdomainLink__Params__Router_Port, 0, USB4_LOWER32(router_ctx->m_topologyID), i);
                *pbIncompatible = TRUE;
                return 0;
            }

            /* Check bonded or L1 is disabled */
            if (FALSE == router_ctx->m_Ports[i].m_bIsBound)
            {
                USB4_ASSERT(0 == Usb4PortGetPortState(&router_ctx->m_Ports[i], &portState));

                if ((USB4_portState_CL0 == portState) && (FALSE == router_ctx->m_Ports[i+1].m_bIsDisabled))
                {
                    // USB4_LOG_INFO("CLx Not Supported due to 2 single links, Router 0x%x, Port %u", USB4_LOWER32(router_ctx->m_topologyID), i);
                    Usb4Log2(USB4_LOG_CM, Usb4RouterCheckCLxCompatibilityCLxNotSupportedDueTo2SingleLinks__Params__Router_Port, 0, USB4_LOWER32(router_ctx->m_topologyID), i);
                    *pbIncompatible = TRUE;
                    return 0;
                }
            }

            if (0x20 == router_ctx->m_cs.ROUTER_CS_4.usb4Version)
            {
                /* Check that link support CLx */
                USB4_ASSERT(0 == Usb4PortSearchCapability(&router_ctx->m_Ports[i], USB4_USB4_PORT_CAPABILITY, NULL));
                USB4_ASSERT(0 == Usb4PortReadCapability(&router_ctx->m_Ports[i], (UINT8*)(&usb4_port_cs), sizeof(usb4_port_cs)));
                if (0 == usb4_port_cs.PORT_CS_18.LinkCLxSupport_LCL)
                {
                    // USB4_LOG_INFO("CLx Not Supported due to PORT_CS_18.LinkCLxSupport bit clear, Router 0x%x, Port %u", USB4_LOWER32(router_ctx->m_topologyID), i);
                    Usb4Log2(USB4_LOG_CM, Usb4RouterCheckCLxCompatibilityCLxNotSupportedDueToPortCS18LinkCLxSupportBitClear__Params__RouterPort, 0,
                        USB4_LOWER32(router_ctx->m_topologyID), i);
                    *pbIncompatible = TRUE;
                    return 0;
                }
            }

            /* Set PM Secondary bit to 1 in the upstream facing port, to 0 in the downstream facing port;
             * I think I don't need to revert this even if subsequent router turns out to be incompatible...
             * since it's only a priority assignment */
            {
                usb4_lane_adp_cs lane_adp_cs;
                USB4_ASSERT(0 == Usb4PortReadLaneAdpCS(&router_ctx->m_Ports[i], &lane_adp_cs));
                lane_adp_cs.LANE_ADP_CS_1.PmSecondary_PMS =
                    (router_ctx->m_cs.ROUTER_CS_1.upstreamAdapter == i)?1:0;
                USB4_ASSERT(0 == Usb4PortWriteLaneAdpCS(&router_ctx->m_Ports[i], &lane_adp_cs));
            }
        }
    }

    *pbIncompatible = FALSE;
    return 0;
}

int Usb4RouterConfigureCLx(usb4_router_ctx_t* router_ctx, USB4_CLx_mode CLxMode)
{

    UINT32 i;

    for (i = 1; i < Usb4RouterGetNumberOfAdapters(router_ctx); ++i) /* skip port0 (usb port) */
    {
        if (USB4_portType_LANE0 == Usb4PortGetPortType(&router_ctx->m_Ports[i]))
        {
            usb4_lane_adp_cs lane_adp_cs;

            if (0 == router_ctx->m_Ports[i].m_cs.ADP_CS_4.Plugged)
            {
                continue; /* No need to do anything with unplugged port */
            }

            USB4_ASSERT(0 == Usb4PortReadLaneAdpCS(&router_ctx->m_Ports[i], &lane_adp_cs));
            switch (CLxMode)
            {
                default:
                case USB4_CL0:
                    lane_adp_cs.LANE_ADP_CS_1.CL0sEnable = 0;
                    lane_adp_cs.LANE_ADP_CS_1.CL1Enable = 0;
                    lane_adp_cs.LANE_ADP_CS_1.CL2Enable = 0;
                    break;
                case USB4_CL0s:
                    lane_adp_cs.LANE_ADP_CS_1.CL0sEnable = 1;
                    lane_adp_cs.LANE_ADP_CS_1.CL1Enable = 0;
                    lane_adp_cs.LANE_ADP_CS_1.CL2Enable = 0;
                    break;
                case USB4_CL1:
                    lane_adp_cs.LANE_ADP_CS_1.CL0sEnable = 1;
                    lane_adp_cs.LANE_ADP_CS_1.CL1Enable = 1;
                    lane_adp_cs.LANE_ADP_CS_1.CL2Enable = 0;
                    break;
                case USB4_CL2:
                    lane_adp_cs.LANE_ADP_CS_1.CL0sEnable = 1;
                    lane_adp_cs.LANE_ADP_CS_1.CL1Enable = 1;
                    lane_adp_cs.LANE_ADP_CS_1.CL2Enable = 1;
                    break;
            }
            USB4_ASSERT(0 == Usb4PortWriteLaneAdpCS(&router_ctx->m_Ports[i], &lane_adp_cs));
        }
    }
    return 0;
}

