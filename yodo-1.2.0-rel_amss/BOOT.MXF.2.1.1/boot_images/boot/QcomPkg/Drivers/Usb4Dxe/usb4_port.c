/**---------------------------------------------------------------------------
 *   @file        usb4_port.cpp
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
#include <Usb4Log.h>
// #include "VVHAL_usb4_utils.h"
#include "usb4_operation.h"
#include <string.h>
#include "usb4_port.h"

#define SB_RESPONSE_TIMEOUT_MS      2000

/* --------------------------------------------------------------------------
 * Macros / Types
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Static Variables
 *--------------------------------------------------------------------------*/

char const* USB4_portTypeString[USB4_portType_ENUM_SIZE] =
{
       "NOT_VALID",
       "CONTROL",
       "HIA",
       "LANE0",
       "LANE1",
       "UPSTREAM_PCIE_ADAPTER",
       "UPSTREAM_USB3_ADAPTER",
       "DP_IN",
       "DP_OUT",
       "DOWNSTREAM_PCIE_ADAPTER",
       "DOWNSTREAM_USB3_ADAPTER",
        "RESERVED"};

/* --------------------------------------------------------------------------
 * Global Variables
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Static Functions
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Global Functions
 *--------------------------------------------------------------------------*/


char const* Usb4PortGetName(usb4_port_ctx_t* usb4_port_ctx)
{
  return USB4_portTypeString[(int)(Usb4PortGetPortType(usb4_port_ctx))+1];
}

int Usb4PortInit(usb4_port_ctx_t* usb4_port_ctx, usb4_ctrl_iface_ctx_t* pControl, UINT32 number)
{
  if (NULL == pControl)
  {
    USB4_ERROR_STACK_MSG(-1, "Pointer to HIA can't be null");
    return -1;
  }
  usb4_port_ctx->m_bIsSubordinate = FALSE;
  usb4_port_ctx->m_bUnsupportedUdapter = FALSE;
  usb4_port_ctx->m_pControl = NULL;
  usb4_port_ctx->m_referenceCountIngressSharedFlowControl = 0;
  usb4_port_ctx->m_freeBuffers = USB4_INVALID_FREE_BUFFERS_VALUE;
  // m_adapterTmuCapability();
  usb4_port_ctx->m_topologyID = 0;
  // m_cs();
  usb4_port_ctx->m_Number = 0;
  usb4_port_ctx->m_OtherLaneGroupNumber = 0;
  // m_hotplug();
  usb4_port_ctx->m_bIsBound = FALSE;
  usb4_port_ctx->m_bIsDisabled = FALSE;
  usb4_port_ctx->m_bIsLoop = FALSE;
  usb4_port_ctx->m_bIsInterdomain = FALSE;
  usb4_port_ctx->m_bIsSegmenEnabled = FALSE;

  usb4_port_ctx->m_bIsSubordinate = FALSE;
  memset(&usb4_port_ctx->m_cs, 0, sizeof(usb4_port_ctx->m_cs));
  memset(&usb4_port_ctx->m_adapterTmuCapability, 0, sizeof(usb4_port_ctx->m_adapterTmuCapability));
  usb4_port_ctx->m_referenceCountIngressSharedFlowControl = 0;
  usb4_port_ctx->m_topologyID = 0;

  usb4_port_ctx->m_freeBuffers = USB4_INVALID_FREE_BUFFERS_VALUE;
  usb4_port_ctx->m_bIsBound = FALSE;
  usb4_port_ctx->m_bIsDisabled = FALSE;
  usb4_port_ctx->m_bIsLoop = FALSE;
  usb4_port_ctx->m_bIsInterdomain = FALSE;
  usb4_port_ctx->m_bUnsupportedUdapter = FALSE;
  usb4_port_ctx->m_bIsSegmenEnabled = FALSE;

  usb4_port_ctx->m_Number = number;
  usb4_port_ctx->m_pControl = pControl;

  memset((UINT8*)(&usb4_port_ctx->m_hotplug), 0, sizeof(USB4_hotplug_t));

  return 0;
};

int Usb4PortSetTopologyId(usb4_port_ctx_t* usb4_port_ctx, UINT64 topologyId)
{
  // Assumes a valid topologyId (verified by router)
  usb4_port_ctx->m_topologyID = topologyId;
  return 0;
}

UINT32 Usb4PortGetFreeBuffers(usb4_port_ctx_t* usb4_port_ctx)
{
  return usb4_port_ctx->m_freeBuffers;
}

int Usb4PortSearchCapability(usb4_port_ctx_t* usb4_port_ctx, UINT8 capIdRequested, UINT32* pCapLength)
{
  UINT32 NextCapabilityPointer = usb4_port_ctx->m_cs.ADP_CS_1.NextCapabilityPointer;
  UINT32 buffer;
  UINT8* pBuff = (UINT8*)(&buffer);
  UINT32 len;
  UINT32 capID;

  // pCapLength is allowed to be NULL (default parameter)

  if (usb4_port_ctx->m_bUnsupportedUdapter)
  {
    return 0;
  }

  while(NextCapabilityPointer)
  {
    USB4_ASSERT(0 == Usb4CtrlIfaceSetType(usb4_port_ctx->m_pControl, USB4_cpDescriptorType_READ_REQUEST));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetRoute(usb4_port_ctx->m_pControl, usb4_port_ctx->m_topologyID));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(usb4_port_ctx->m_pControl, NextCapabilityPointer));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetAdapter(usb4_port_ctx->m_pControl, usb4_port_ctx->m_Number));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetCS(usb4_port_ctx->m_pControl, USB4_cpConfigSpace_ADAPTER));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetData(usb4_port_ctx->m_pControl, NULL, 4));

    if(0 != Usb4CtrlIfaceSend(usb4_port_ctx->m_pControl, USB4_SEND_CTRL_PACKET_TIMEOUT_US))
    {
      USB4_ERROR_STACK(-1);
      goto ErrorHandling;
    }

    USB4_ASSERT(0 == Usb4CtrlIfaceGetData(usb4_port_ctx->m_pControl, pBuff, &len, 4));
    USB4_ASSERT(0 == Usb4CtrlIfacePop(usb4_port_ctx->m_pControl));
    USB4_ASSERT_MSG(len == 4, "Didn't read a complete DWORD");
    capID = (buffer & 0xFF00)>>0x8;
    if (capID == capIdRequested)
    {
      if (NULL != pCapLength)
      {
        if ((buffer & 0xFF) > (NextCapabilityPointer & 0xFF))
        {
          *pCapLength = 4 * ((buffer & 0xFF) - (NextCapabilityPointer & 0xFF) - 1);
        }
      }
      return 0;
    }
    NextCapabilityPointer = buffer & 0xFF;
  }

ErrorHandling:
  return -1;
}

int Usb4PortReadCapability(usb4_port_ctx_t* usb4_port_ctx, UINT8* pBuff, UINT32 capSize)
{
  UINT32 len;

  if (usb4_port_ctx->m_bUnsupportedUdapter)
  {
    return 0;
  }
  USB4_ASSERT(0 == Usb4CtrlIfaceSetType(usb4_port_ctx->m_pControl, USB4_cpDescriptorType_READ_REQUEST));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetData(usb4_port_ctx->m_pControl, NULL, capSize));

  if(0 != Usb4CtrlIfaceSend(usb4_port_ctx->m_pControl, USB4_SEND_CTRL_PACKET_TIMEOUT_US))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  USB4_ASSERT(0 == Usb4CtrlIfaceGetData(usb4_port_ctx->m_pControl, pBuff, &len, capSize));
  USB4_ASSERT(0 == Usb4CtrlIfacePop(usb4_port_ctx->m_pControl));
  USB4_ASSERT_MSG(len == capSize, "Didn't read a complete CS");

  return 0;
ErrorHandling:
  return -1;
}

int Usb4PortReadCapabilityDword(usb4_port_ctx_t* usb4_port_ctx, UINT8* pBuff, UINT32 dwordIndex)
{
  UINT32 len;
  UINT32 capabilityAddress;

  if (usb4_port_ctx->m_bUnsupportedUdapter)
  {
    return 0;
  }
  USB4_ASSERT(0 == Usb4CtrlIfaceGetTxAddress(usb4_port_ctx->m_pControl, &capabilityAddress));
  /* The rest of parameters were set elsewhere.. prior to this call... */
  USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(usb4_port_ctx->m_pControl, capabilityAddress+dwordIndex));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetType(usb4_port_ctx->m_pControl, USB4_cpDescriptorType_READ_REQUEST));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetData(usb4_port_ctx->m_pControl, NULL, 4));

  if(0 != Usb4CtrlIfaceSend(usb4_port_ctx->m_pControl, USB4_SEND_CTRL_PACKET_TIMEOUT_US))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  USB4_ASSERT(0 == Usb4CtrlIfaceGetData(usb4_port_ctx->m_pControl, pBuff+dwordIndex*4, &len, 4));
  USB4_ASSERT(0 == Usb4CtrlIfacePop(usb4_port_ctx->m_pControl));
  USB4_ASSERT_MSG(len == 4, "Didn't read a complete CS");
  USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(usb4_port_ctx->m_pControl, capabilityAddress));
  return 0;
ErrorHandling:
  return -1;
}

int Usb4PortWriteCapability(usb4_port_ctx_t* usb4_port_ctx, UINT8* pBuff, UINT32 write_len)
{
  UINT32 len;

  if (usb4_port_ctx->m_bUnsupportedUdapter)
  {
    return 0;
  }
  /* The rest of parameters were set elsewhere.. prior to this call... */
  USB4_ASSERT(0 == Usb4CtrlIfaceSetType(usb4_port_ctx->m_pControl, USB4_cpDescriptorType_WRITE_REQUEST));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetData(usb4_port_ctx->m_pControl, pBuff, write_len));

  if (0 != Usb4CtrlIfaceSend(usb4_port_ctx->m_pControl, USB4_SEND_CTRL_PACKET_TIMEOUT_US))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  USB4_ASSERT(0 == Usb4CtrlIfaceGetData(usb4_port_ctx->m_pControl, NULL, &len, write_len));
  USB4_ASSERT(0 == Usb4CtrlIfacePop(usb4_port_ctx->m_pControl));
  USB4_ASSERT_MSG(len == write_len, "Didn't write a complete buffer");

  return 0;
ErrorHandling:
  return -1;
}

int Usb4PortWriteCapabilityDword(usb4_port_ctx_t* usb4_port_ctx, UINT8* pBuff, UINT32 dwordIndex)
{
  UINT32 len;
  UINT32 write_len = 4;
  UINT32 capabilityAddress;

  if (usb4_port_ctx->m_bUnsupportedUdapter)
  {
    return 0;
  }
  USB4_ASSERT(0 == Usb4CtrlIfaceGetTxAddress(usb4_port_ctx->m_pControl, &capabilityAddress));
  /* The rest of parameters were set elsewhere.. prior to this call... */
  USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(usb4_port_ctx->m_pControl, capabilityAddress+dwordIndex));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetType(usb4_port_ctx->m_pControl, USB4_cpDescriptorType_WRITE_REQUEST));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetData(usb4_port_ctx->m_pControl, pBuff+4*dwordIndex, write_len));

  if (0 != Usb4CtrlIfaceSend(usb4_port_ctx->m_pControl, USB4_SEND_CTRL_PACKET_TIMEOUT_US))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  USB4_ASSERT(0 == Usb4CtrlIfaceGetData(usb4_port_ctx->m_pControl, NULL, &len, write_len));
  USB4_ASSERT(0 == Usb4CtrlIfacePop(usb4_port_ctx->m_pControl));
  USB4_ASSERT_MSG(len == write_len, "Didn't write a complete buffer");
  USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(usb4_port_ctx->m_pControl, capabilityAddress));
  return 0;
ErrorHandling:
  return -1;
}

int Usb4PortUpdateTotalBuffers(usb4_port_ctx_t* usb4_port_ctx)
{
  UINT32 controlPathBuffers = 0;
  if (usb4_port_ctx->m_cs.ADP_CS_4.TotalBuffers > 0)
  {
    if ((USB4_portType_LANE0 == Usb4PortGetPortType(usb4_port_ctx)) || (USB4_portType_LANE1 == Usb4PortGetPortType(usb4_port_ctx)))
    {
      usb4_pathN_cs path;
      if (0 == Usb4PortReadSegment(usb4_port_ctx, 0, &path)) /* Control path */
      {
        controlPathBuffers = path.PATH_CS_0.PathCreditsAllocated;
      }
    }
    USB4_ASSERT(usb4_port_ctx->m_cs.ADP_CS_4.TotalBuffers >= controlPathBuffers);
    usb4_port_ctx->m_freeBuffers = usb4_port_ctx->m_cs.ADP_CS_4.TotalBuffers - controlPathBuffers;
  }
  else
  {
    usb4_port_ctx->m_freeBuffers = 0;
  }
  return 0;
}

int Usb4PortConfigureDHP(usb4_port_ctx_t* usb4_port_ctx, BOOLEAN bEnable)
{
  USB4_ASSERT(0 ==Usb4PortReadCS(usb4_port_ctx));
  usb4_port_ctx->m_cs.ADP_CS_5.DisableHotPlugEvents = bEnable?0:1;
  USB4_ASSERT(0 ==Usb4PortWriteCS(usb4_port_ctx));
  return 0;
}

int Usb4PortReadCS(usb4_port_ctx_t* usb4_port_ctx)
{
  UINT8* pBuff = (UINT8*)(&usb4_port_ctx->m_cs);
  UINT32 len;
  UINT32 start_address = 1;
  UINT32 data_size = sizeof(usb4_port_ctx->m_cs);
  if (usb4_port_ctx->m_bUnsupportedUdapter)
  {
    return 0;
  }

  USB4_ASSERT(0 == Usb4CtrlIfaceSetType(usb4_port_ctx->m_pControl, USB4_cpDescriptorType_READ_REQUEST));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetRoute(usb4_port_ctx->m_pControl, usb4_port_ctx->m_topologyID));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(usb4_port_ctx->m_pControl, start_address));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetAdapter(usb4_port_ctx->m_pControl, usb4_port_ctx->m_Number));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetCS(usb4_port_ctx->m_pControl, USB4_cpConfigSpace_ADAPTER));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetData(usb4_port_ctx->m_pControl, NULL, data_size));

  if(0 != Usb4CtrlIfaceSend(usb4_port_ctx->m_pControl, USB4_SEND_CTRL_PACKET_TIMEOUT_US))
  {
    // USB4_LOG_INFO("Send read failed on timeout\n");
    Usb4Log(USB4_LOG_CM, Usb4PortReadCSsendReadFailedOnTimeout__Info, 0);
    goto UnsupportedAdapter;
  }

  USB4_ASSERT(0 == Usb4CtrlIfaceGetData(usb4_port_ctx->m_pControl, pBuff, &len, sizeof(usb4_port_ctx->m_cs)));
  USB4_ASSERT(0 == Usb4CtrlIfacePop(usb4_port_ctx->m_pControl));
  USB4_ASSERT_MSG(len == sizeof(usb4_port_ctx->m_cs), "Didn't read a complete buffer");

  if ((0 == usb4_port_ctx->m_cs.ADP_CS_2.AdapterTypeProtocol) &&
      (0 == usb4_port_ctx->m_cs.ADP_CS_2.AdapterTypeSubType) &&
      (0 == usb4_port_ctx->m_cs.ADP_CS_2.AdapterTypeVersion))
  {
    // USB4_LOG_INFO("0 == AdapterTypeProtocol == AdapterTypeSubType == AdapterTypeVersion\n");
    Usb4Log(USB4_LOG_CM, Usb4PortReadCSUnsupportedAdapterNullProtocolNullSubTypeNullVersion__Info, 0);
    goto UnsupportedAdapter;
  }

  if(USB4_INVALID_FREE_BUFFERS_VALUE == usb4_port_ctx->m_freeBuffers)
  {
    USB4_ASSERT(0 == Usb4PortUpdateTotalBuffers(usb4_port_ctx));
  }

  return 0;

UnsupportedAdapter:
  // USB4_LOG_WARNING("Found unsupported adapter number %u\n", usb4_port_ctx->m_Number);
  Usb4Log1(USB4_LOG_CM, Usb4PortReadCSFoundUnsupportedAdapterNumber__Params__Numbers, 0, usb4_port_ctx->m_Number);
  usb4_port_ctx->m_bUnsupportedUdapter = TRUE;
  usb4_port_ctx->m_freeBuffers = USB4_INVALID_FREE_BUFFERS_VALUE;
  return 0;
}

int Usb4PortWriteCS(usb4_port_ctx_t* usb4_port_ctx)
{
  UINT8* pBuff = (UINT8*)(&usb4_port_ctx->m_cs);
  UINT32 len;
  if (usb4_port_ctx->m_bUnsupportedUdapter)
  {
    return 0;
  }
  USB4_ASSERT(0 == Usb4CtrlIfaceSetType(usb4_port_ctx->m_pControl, USB4_cpDescriptorType_WRITE_REQUEST));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetRoute(usb4_port_ctx->m_pControl, usb4_port_ctx->m_topologyID));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(usb4_port_ctx->m_pControl, 1));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetAdapter(usb4_port_ctx->m_pControl, usb4_port_ctx->m_Number));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetCS(usb4_port_ctx->m_pControl, USB4_cpConfigSpace_ADAPTER));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetData(usb4_port_ctx->m_pControl, pBuff, sizeof(usb4_port_ctx->m_cs)));

  if(0 != Usb4CtrlIfaceSend(usb4_port_ctx->m_pControl, USB4_SEND_CTRL_PACKET_TIMEOUT_US))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  USB4_ASSERT(0 == Usb4CtrlIfaceGetData(usb4_port_ctx->m_pControl, NULL, &len, sizeof(usb4_port_ctx->m_cs)));
  USB4_ASSERT(0 == Usb4CtrlIfacePop(usb4_port_ctx->m_pControl));
  USB4_ASSERT_MSG(len == sizeof(usb4_port_ctx->m_cs), "Didn't write a complete CS");
  return 0;
ErrorHandling:
  return -1;
}

USB4_portType Usb4PortGetPortType(usb4_port_ctx_t* usb4_port_ctx)
{
  UINT32* pBuff = (UINT32*)(&usb4_port_ctx->m_cs.ADP_CS_2);

  if (usb4_port_ctx->m_bUnsupportedUdapter)
  {
    return USB4_portType_NOT_VALID;
  }

  switch(*pBuff & 0xffffff) /* Table 8-10 USB4 spec 0.95 */
  {
    case 0:
    default:
      return USB4_portType_NOT_VALID;
    case 0x000001:
      {
        if (usb4_port_ctx->m_bIsSubordinate)
        {
          return USB4_portType_LANE1;
        }
        else
        {
          return USB4_portType_LANE0;
        }
      }
    case 0x000002:
      return USB4_portType_HIA;
    case 0x100101:
      return USB4_portType_DOWNSTREAM_PCIE_ADAPTER;
    case 0x100102:
      return USB4_portType_UPSTREAM_PCIE_ADAPTER;
    case 0x0E0102:
      return USB4_portType_DP_OUT;
    case 0x0E0101:
      return USB4_portType_DP_IN;
    case 0x200101:
      return USB4_portType_DOWNSTREAM_USB3_ADAPTER;
    case 0x200102: /* Temporary change for CR#QCTDD06642901 due to incorrect Adapter value in USBAP Device mode*/ 
      if (0 == usb4_port_ctx->m_topologyID)
        return USB4_portType_DOWNSTREAM_USB3_ADAPTER;
      else
        return USB4_portType_UPSTREAM_USB3_ADAPTER; 
  }
}

int Usb4PortReadLaneAdpCS(usb4_port_ctx_t* usb4_port_ctx, usb4_lane_adp_cs* lane_adp_cs)
{
  if (0 != Usb4PortSearchCapability(usb4_port_ctx, USB4_USB4_LANE_CAPABILITY, NULL))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  if (0 != Usb4PortReadCapability(usb4_port_ctx, (UINT8*)(lane_adp_cs), sizeof(usb4_lane_adp_cs)))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }
  return 0;
ErrorHandling:
  return -1;
}

int Usb4PortWriteLaneAdpCS(usb4_port_ctx_t* usb4_port_ctx, usb4_lane_adp_cs* lane_adp_cs)
{

  if (0 != Usb4PortSearchCapability(usb4_port_ctx, USB4_USB4_LANE_CAPABILITY, NULL))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  if (0 != Usb4PortWriteCapability(usb4_port_ctx, (UINT8*)(lane_adp_cs), sizeof(usb4_lane_adp_cs)))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }
  return 0;
ErrorHandling:
  return -1;
}

int Usb4PortGetPortState(usb4_port_ctx_t* usb4_port_ctx, USB4_portState* portState)
{
  usb4_lane_adp_cs lane_adp_cs;

  memset((UINT8*)(&lane_adp_cs), 0, sizeof(lane_adp_cs));

  if (0 != Usb4PortReadLaneAdpCS(usb4_port_ctx, &lane_adp_cs))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  *portState = (USB4_portState)(lane_adp_cs.LANE_ADP_CS_1.AdapterState);
  return 0;
ErrorHandling:
  return -1;
};

int Usb4PortIsDualLaneSupported(usb4_port_ctx_t* usb4_port_ctx, BOOLEAN* dualLaneSupported)
{
  usb4_lane_adp_cs lane_adp_cs;

  memset((UINT8*)(&lane_adp_cs), 0, sizeof(lane_adp_cs));

  if (0 != Usb4PortReadLaneAdpCS(usb4_port_ctx, &lane_adp_cs))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  *dualLaneSupported = (0x3 == lane_adp_cs.LANE_ADP_CS_0.SupportedLinkWidths);

  return 0;
ErrorHandling:
  return -1;
}

int Usb4PortConfigureDualLane(usb4_port_ctx_t* usb4_port_ctx)
{
  usb4_lane_adp_cs lane_adp_cs;

  if (0 != Usb4PortReadLaneAdpCS(usb4_port_ctx, &lane_adp_cs))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  lane_adp_cs.LANE_ADP_CS_1.TargetLinkWidth = 3;

  if (0 != Usb4PortWriteCapability(usb4_port_ctx, (UINT8*)(&lane_adp_cs), sizeof(lane_adp_cs)))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  return 0;
ErrorHandling:
  return -1;
}

int Usb4PortSetSubordinate(usb4_port_ctx_t* usb4_port_ctx)
{
  usb4_port_ctx->m_bIsSubordinate = TRUE;
  return 0;
};

int Usb4PortBondLanes(usb4_port_ctx_t* usb4_port_ctx)
{
  usb4_lane_adp_cs lane_adp_cs;

  memset((UINT8*)(&lane_adp_cs), 0, sizeof(lane_adp_cs));

  if (0 != Usb4PortSearchCapability(usb4_port_ctx, USB4_USB4_LANE_CAPABILITY, NULL))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  if (0 != Usb4PortReadCapability(usb4_port_ctx, (UINT8*)(&lane_adp_cs), sizeof(lane_adp_cs)))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  if (0 == (lane_adp_cs.LANE_ADP_CS_0.SupportedLinkWidths & 0x2))
  {
    USB4_ERROR_STACK_MSG(-1,"Attempting to bond lanes on a port that doesn't support this.");
    goto ErrorHandling;
  }

  if (3 != lane_adp_cs.LANE_ADP_CS_1.TargetLinkWidth)
  {
    USB4_ERROR_STACK_MSG(-1,"Target link width was not configured for dual lane");
    goto ErrorHandling;
  }

  lane_adp_cs.LANE_ADP_CS_1.LaneBonding_LB = 1;

  if (0 != Usb4PortWriteCapability(usb4_port_ctx, (UINT8*)(&lane_adp_cs), sizeof(lane_adp_cs)))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  return 0;
ErrorHandling:
  return -1;
};

int Usb4PortGetNegotiatedLinkWidth(usb4_port_ctx_t* usb4_port_ctx, UINT32* linkWidth)
{
  usb4_lane_adp_cs lane_adp_cs;

  USB4_ASSERT(NULL != linkWidth);

  memset((UINT8*)(&lane_adp_cs), 0, sizeof(lane_adp_cs));

  if (0 != Usb4PortSearchCapability(usb4_port_ctx, USB4_USB4_LANE_CAPABILITY, NULL))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  if (0 != Usb4PortReadCapability(usb4_port_ctx, (UINT8*)(&lane_adp_cs), sizeof(lane_adp_cs)))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  *linkWidth = lane_adp_cs.LANE_ADP_CS_1.NegotiatedLinkWidth;

  return 0;
ErrorHandling:
  return -1;
}

int Usb4PortLaneDisable(usb4_port_ctx_t* usb4_port_ctx)
{
  usb4_lane_adp_cs usb4_lane_adp_cs;

  memset((UINT8*)(&usb4_lane_adp_cs), 0, sizeof(usb4_lane_adp_cs));

  if (0 != Usb4PortSearchCapability(usb4_port_ctx, USB4_USB4_LANE_CAPABILITY, NULL))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  if (0 != Usb4PortReadCapability(usb4_port_ctx, (UINT8*)(&usb4_lane_adp_cs), sizeof(usb4_lane_adp_cs)))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  usb4_lane_adp_cs.LANE_ADP_CS_1.LaneDisable_LD = 1;

  if (0 != Usb4PortWriteCapability(usb4_port_ctx, (UINT8*)(&usb4_lane_adp_cs), sizeof(usb4_lane_adp_cs)))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  usb4_port_ctx->m_bIsDisabled = TRUE;
  return 0;
ErrorHandling:
  return -1;
}

int Usb4PortLaneEnable(usb4_port_ctx_t* usb4_port_ctx)
{
  usb4_lane_adp_cs usb4_lane_adp_cs;

  memset((UINT8*)(&usb4_lane_adp_cs), 0, sizeof(usb4_lane_adp_cs));

  if (0 != Usb4PortSearchCapability(usb4_port_ctx, USB4_USB4_LANE_CAPABILITY, NULL))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  if (0 != Usb4PortReadCapability(usb4_port_ctx, (UINT8*)(&usb4_lane_adp_cs), sizeof(usb4_lane_adp_cs)))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  if (1 == usb4_lane_adp_cs.LANE_ADP_CS_1.LaneDisable_LD)
  {
    usb4_lane_adp_cs.LANE_ADP_CS_1.LaneDisable_LD = 0;

    if (0 != Usb4PortWriteCapability(usb4_port_ctx, (UINT8*)(&usb4_lane_adp_cs), sizeof(usb4_lane_adp_cs)))
    {
      USB4_ERROR_STACK(-1);
      goto ErrorHandling;
    }
  }
  usb4_port_ctx->m_bIsDisabled = FALSE;
  return 0;
ErrorHandling:
  return -1;
}

int Usb4PortIsBondingEnabled(usb4_port_ctx_t* usb4_port_ctx, BOOLEAN *bondingEnabled)
{
  usb4_usb4_port_cs usb4_port_cs;

  memset((UINT8*)(&usb4_port_cs), 0, sizeof(usb4_port_cs));

  USB4_ASSERT(NULL != bondingEnabled);

  if (0 != Usb4PortSearchCapability(usb4_port_ctx, USB4_USB4_PORT_CAPABILITY, NULL))
  {
    *bondingEnabled = TRUE; /* TODO: Write the TBT3 compatible solution */
    return 0;
  }

  if (0 != Usb4PortReadCapability(usb4_port_ctx, (UINT8*)(&usb4_port_cs), sizeof(usb4_port_cs)))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }
  *bondingEnabled = (1 == usb4_port_cs.PORT_CS_18.BondingEnabled_BE);
  return 0;
ErrorHandling:
  return -1;
}

int Usb4PortPortReset(usb4_port_ctx_t* usb4_port_ctx, UINT32 set)
{
  usb4_usb4_port_cs usb4_port_cs;
  if (0 != Usb4PortSearchCapability(usb4_port_ctx, USB4_USB4_PORT_CAPABILITY, NULL))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  if (0 != Usb4PortReadCapability(usb4_port_ctx, (UINT8*)(&usb4_port_cs), sizeof(usb4_port_cs)))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  usb4_port_cs.PORT_CS_19.DownstreamPortReset_DPR = (set & 1);

  if (0 != Usb4PortWriteCapability(usb4_port_ctx, (UINT8*)(&usb4_port_cs), sizeof(usb4_port_cs)))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  if (0 == set)
  {
    usb4_port_ctx->m_bIsBound = FALSE; /**< USB4 Port is a 2 lane bound group */
    usb4_port_ctx->m_bIsDisabled = FALSE;
    usb4_port_ctx->m_bIsLoop = FALSE; /**< Port leads to a loop in the topology */
    usb4_port_ctx->m_bIsInterdomain = FALSE; /**< Port leads to a different domain */
    usb4_port_ctx->m_freeBuffers = USB4_INVALID_FREE_BUFFERS_VALUE;
    usb4_port_ctx->m_referenceCountIngressSharedFlowControl = 0;
    USB4_ASSERT(0 == Usb4PortReadCS(usb4_port_ctx));
  }

  return 0;
ErrorHandling:
  return -1;
}

int Usb4PortUnlock(usb4_port_ctx_t* usb4_port_ctx)
{
  UINT8* pBuff = (UINT8*)(&usb4_port_ctx->m_cs.ADP_CS_4);
  UINT32 len;
  UINT32 write_len = sizeof(UINT32);

  usb4_port_ctx->m_cs.ADP_CS_4.Lock = 0;

  USB4_ASSERT(0 == Usb4CtrlIfaceSetType(usb4_port_ctx->m_pControl, USB4_cpDescriptorType_WRITE_REQUEST));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetRoute(usb4_port_ctx->m_pControl, usb4_port_ctx->m_topologyID));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(usb4_port_ctx->m_pControl, 4));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetAdapter(usb4_port_ctx->m_pControl, usb4_port_ctx->m_Number));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetCS(usb4_port_ctx->m_pControl, USB4_cpConfigSpace_ADAPTER));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetData(usb4_port_ctx->m_pControl, pBuff, write_len));

  if (0 != Usb4CtrlIfaceSend(usb4_port_ctx->m_pControl, USB4_SEND_CTRL_PACKET_TIMEOUT_US))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  USB4_ASSERT(0 == Usb4CtrlIfaceGetData(usb4_port_ctx->m_pControl, NULL, &len, write_len));
  USB4_ASSERT(0 == Usb4CtrlIfacePop(usb4_port_ctx->m_pControl));
  USB4_ASSERT_MSG(len == write_len, "Didn't write a complete CS");

  return 0;
ErrorHandling:
  return -1;
}

int Usb4PortPollForLockState(usb4_port_ctx_t* usb4_port_ctx, UINT32 lock)
{
  do
  {
    if (0 != Usb4PortReadCS(usb4_port_ctx))
    {
      USB4_ERROR_STACK(-1);
      goto ErrorHandling;
    }
  }while ((lock & 1) != usb4_port_ctx->m_cs.ADP_CS_4.Lock);

  return 0;
ErrorHandling:
  return -1;
}

int Usb4PortSetInterdomain(usb4_port_ctx_t* usb4_port_ctx, BOOLEAN isInterdomain)
{
  usb4_usb4_port_cs usb4_port_cs;
  if (0 != Usb4PortSearchCapability(usb4_port_ctx, USB4_USB4_PORT_CAPABILITY, NULL))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  if (0 != Usb4PortReadCapability(usb4_port_ctx, (UINT8*)(&usb4_port_cs), sizeof(usb4_port_cs)))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }
  usb4_port_cs.PORT_CS_19.USB4PortIsInterDomain_PID = (isInterdomain ? 1 : 0);
  if (0 != Usb4PortWriteCapability(usb4_port_ctx, (UINT8*)(&usb4_port_cs), sizeof(usb4_port_cs)))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }
  return 0;
ErrorHandling:
  return -1;
}

int Usb4PortEnableSegment(usb4_port_ctx_t* usb4_port_ctx, BOOLEAN enable)
{
  if (usb4_port_ctx->m_bIsSegmenEnabled == enable)
  {
    return 0;
  }
  USB4_portType type = Usb4PortGetPortType(usb4_port_ctx);
  switch(type)
  {
    case USB4_portType_HIA:
      // nothing to do here...
      break;

    case USB4_portType_DOWNSTREAM_USB3_ADAPTER:
    case USB4_portType_UPSTREAM_USB3_ADAPTER:
      {
        usb4_adp_usb3_cs adp_usb_cs;
        if (0 != Usb4PortSearchCapability(usb4_port_ctx, USB4_USB3_ADAPTER_PORT_CAPABILITY, NULL))
        {
          USB4_ERROR_STACK(-1);
          goto ErrorHandling;
        }

        if (0 != Usb4PortReadCapability(usb4_port_ctx, (UINT8*)(&adp_usb_cs),
              sizeof(adp_usb_cs)))
        {
          USB4_ERROR_STACK(-1);
          goto ErrorHandling;
        }
        adp_usb_cs.ADP_USB_CS_0.PathEnable = (enable?1:0);
        adp_usb_cs.ADP_USB_CS_0.Valid      = 1;
        if (0 != Usb4PortWriteCapability(usb4_port_ctx, (UINT8*)(&adp_usb_cs),
              sizeof(adp_usb_cs)))
        {
          USB4_ERROR_STACK(-1);
          goto ErrorHandling;
        }

        if (enable == 0)
        {
          USB4_ASSERT(0 == Usb4PortPollforPP(usb4_port_ctx, 8));
        }
        break;
      }
    case USB4_portType_DOWNSTREAM_PCIE_ADAPTER:
    case USB4_portType_UPSTREAM_PCIE_ADAPTER:
      {
        usb4_adp_pcie_cs adp_pcie_cs;
        if (0 != Usb4PortSearchCapability(usb4_port_ctx, USB4_PCIE_ADAPTER_PORT_CAPABILITY, NULL))
        {
          USB4_ERROR_STACK(-1);
          goto ErrorHandling;
        }

        if (0 != Usb4PortReadCapability(usb4_port_ctx, (UINT8*)(&adp_pcie_cs),
              sizeof(usb4_adp_pcie_cs)))
        {
          USB4_ERROR_STACK(-1);
          goto ErrorHandling;
        }
        adp_pcie_cs.ADP_PCIE_CS_0.PathEnable = (enable?1:0);
        if (0 != Usb4PortWriteCapability(usb4_port_ctx, (UINT8*)(&adp_pcie_cs),
              sizeof(usb4_adp_pcie_cs)))
        {
          USB4_ERROR_STACK(-1);
          goto ErrorHandling;
        }
        break;
      }

    case USB4_portType_DP_IN:
      {
        usb4_adp_dp_in_cs dpInCs;
        USB4_ASSERT(0 == Usb4PortSearchCapability(usb4_port_ctx, USB4_DP_ADAPTER_PORT_CAPABILITY, NULL));
        USB4_ASSERT(0 == Usb4PortReadCapability(usb4_port_ctx, (UINT8*)(&dpInCs), sizeof(dpInCs)));

        /* Enable DP In */
        dpInCs.ADP_DP_CS_0.auxEnable = (enable ? 1 : 0);
        dpInCs.ADP_DP_CS_0.videoEnable = (enable ? 1 : 0);
        USB4_ASSERT(0 == Usb4PortWriteCapability(usb4_port_ctx, (UINT8*)(&dpInCs), sizeof(dpInCs)));

        break;
      }
    case USB4_portType_DP_OUT:
      {
        usb4_adp_dp_out_cs dpOutCs;
        USB4_ASSERT(0 == Usb4PortSearchCapability(usb4_port_ctx, USB4_DP_ADAPTER_PORT_CAPABILITY, NULL));
        USB4_ASSERT(0 == Usb4PortReadCapability(usb4_port_ctx, (UINT8*)(&dpOutCs), sizeof(dpOutCs)));

        /* Write video and aux HOP id */
        dpOutCs.ADP_DP_CS_0.videoHopId = 0x9;
        dpOutCs.ADP_DP_CS_1.auxRxHopId = 0x8;
        dpOutCs.ADP_DP_CS_1.auxTxHopId = 0x8;

        USB4_ASSERT(0 == Usb4PortWriteCapability(usb4_port_ctx, (UINT8*)(&dpOutCs), sizeof(dpOutCs)));

        dpOutCs.ADP_DP_CS_0.auxEnable = (enable ? 1 : 0);
        dpOutCs.ADP_DP_CS_0.videoEnable = (enable ? 1 : 0);
#ifdef USB4_DP_TOGGLE_SWLI_EXPERIMENT_06_2020
        dpOutCs.ADP_DP_CS_2.swli = 1;

        USB4_ASSERT(0 == Usb4PortWriteCapability(usb4_port_ctx, (UINT8*)(&dpOutCs), sizeof(dpOutCs)));

        {
          usb4_utils_timer timer;
          timer.m_source = USB4_TIMER_SOURCE_QTIMER;
          usb4_timer_Sleep_ms(&timer, 100);
        }

        dpOutCs.ADP_DP_CS_2.swli = 0;
#endif  /* USB4_DP_TOGGLE_SWLI_EXPERIMENT_06_2020 */

        USB4_ASSERT(0 == Usb4PortWriteCapability(usb4_port_ctx, (UINT8*)(&dpOutCs), sizeof(dpOutCs)));
        break;
      }
    default:
      // USB4_LOG_ERROR("Port type: %u\n", type);
      Usb4Log1(USB4_LOG_CM, Usb4PortEnableSegmentPortType__Params__Type, 0, type);
      USB4_ERROR_STACK_MSG(-1, "enable port not implemented");
      goto ErrorHandling;
  }

  usb4_port_ctx->m_bIsSegmenEnabled = enable;
  return 0;
ErrorHandling:
  return -1;
}

int Usb4PortInvalidateSegment(usb4_port_ctx_t* usb4_port_ctx, UINT32 HopID)
{
  usb4_pathN_cs path;

  if (0 == HopID)
  {
    USB4_ASSERT(0 == Usb4PortGetAdapterHopID(usb4_port_ctx, &HopID, FALSE));
  }

  if (0 != Usb4PortReadSegment(usb4_port_ctx, HopID, &path))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  if(path.PATH_CS_0.Valid)
  {
    usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;
    UINT32 elapsed_us;

#ifdef USB4_WA_CR_QCTDD06911734_FCM_junk_credit_grant
    /* For the host USB4 port SRC, check that PP is 0, before setting valid to 0 */
    if ((0 == usb4_port_ctx->m_topologyID) && (USB4_portType_LANE0 == Usb4PortGetPortType(usb4_port_ctx)))
    {
      usb4_timer_Start(&timer);
      do
      {
        if (0 != Usb4PortReadSegment(usb4_port_ctx, HopID, &path))
        {
          USB4_ERROR_STACK(-1);
          goto ErrorHandling;
        }

        USB4_ASSERT(0 == usb4_timer_GetElapsed_us(&timer, &elapsed_us));
#ifndef USB4_COMPILING_GEN_EMU_VELOCE
        USB4_ASSERT_MSG(USB4_PACKET_PENDING_TIMEOUT_USEC > elapsed_us, "Packet pending timeout value exceeded");
#endif
      }while (1 == path.PATH_CS_1.PendingPackets);
    }
#endif

    path.PATH_CS_0.Valid = 0;
    if (0 != Usb4PortWriteSegment(usb4_port_ctx, HopID, &path))
    {
      USB4_ERROR_STACK(-1);
      goto ErrorHandling;
    }

    usb4_timer_Start(&timer);
    do
    {
      if (0 != Usb4PortReadSegment(usb4_port_ctx, HopID, &path))
      {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
      }

      USB4_ASSERT(0 == usb4_timer_GetElapsed_us(&timer, &elapsed_us));
#ifndef USB4_COMPILING_GEN_EMU_VELOCE
      USB4_ASSERT_MSG(USB4_PACKET_PENDING_TIMEOUT_USEC > elapsed_us, "Packet pending timeout value exceeded");
#endif
    }while (1 == path.PATH_CS_1.PendingPackets);
    /* Duration during which packet transmission is
       permitted on a removed Path after the Pending
       Packets bit was set to 0b. */
    // timer.Sleep_us(USB4_T_TEARDOWN_USEC);
    usb4_timer_Sleep_us(&timer, USB4_T_TEARDOWN_USEC);
  }

  return 0;
ErrorHandling:
  return -1;
}

int Usb4PortGetAdapterHopID(usb4_port_ctx_t* usb4_port_ctx, UINT32 *hopID, BOOLEAN bIsAux)
{
  USB4_ASSERT(NULL != hopID);

  switch(Usb4PortGetPortType(usb4_port_ctx))
  {
    case USB4_portType_UPSTREAM_PCIE_ADAPTER:
    case USB4_portType_UPSTREAM_USB3_ADAPTER:
    case USB4_portType_DOWNSTREAM_PCIE_ADAPTER:
    case USB4_portType_DOWNSTREAM_USB3_ADAPTER:
      *hopID = 8;
      break;
    case USB4_portType_CONTROL:
      *hopID = 0;
      break;
    case USB4_portType_DP_IN:
    case USB4_portType_DP_OUT:
      if (bIsAux)
      {
        *hopID = 8;
      }
      else
      {
        *hopID = 9;
      }
      break;
    case USB4_portType_HIA:
      USB4_ASSERT(0 == Usb4PortGetFreeHopID(usb4_port_ctx, hopID));
      break;
    default:
      USB4_ASSERT_MSG(FALSE, "Can't determine hopID for this type");
  }

  return 0;
}

int Usb4PortGetFreeHopID(usb4_port_ctx_t* usb4_port_ctx, UINT32 *hopID)
{
  UINT32 startHopId, i;
  USB4_ASSERT(NULL != hopID);

    switch(Usb4PortGetPortType(usb4_port_ctx))
    {
      case USB4_portType_LANE0:
        startHopId = 8;
        break;
      case USB4_portType_HIA:
        startHopId = 1;
        break;
      default:
        USB4_ASSERT_MSG(FALSE, "Can't determine hopID for this type");
    }

  /* Search for invalid paths between startHopId and m_freeHopID - 1
   * TODO: This is somewhat inefficient, so look for a better algorithm */
  for (i = startHopId; i <= usb4_port_ctx->m_cs.ADP_CS_5.MaxInputHopID; i++)
  {
    usb4_pathN_cs path;

    if (0 != Usb4PortReadSegment(usb4_port_ctx, i, &path))
    {
      USB4_ERROR_STACK(-1);
      goto ErrorHandling;
    }

    if (0 == path.PATH_CS_0.Valid)
    {
      /* Use this hop id, since the path is invalid;
       * Don't consume free paths from the end of the table */
      *hopID = i;
      return 0;
    }
  }

ErrorHandling:
  return -1;
}

int Usb4PortReadSegment(usb4_port_ctx_t* usb4_port_ctx, UINT32 HopID, usb4_pathN_cs* path)
{
  UINT8* pBuff = (UINT8*)(path);
  UINT32 len;

  //USB4_LOG_INFO("ReadSegment Topology %x,  Port %u has type %s\n",
  //                USB4_LOWER32(m_topologyID), m_Number, GetName());

  USB4_ASSERT(0 == Usb4CtrlIfaceSetType(usb4_port_ctx->m_pControl, USB4_cpDescriptorType_READ_REQUEST));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetRoute(usb4_port_ctx->m_pControl, usb4_port_ctx->m_topologyID));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(usb4_port_ctx->m_pControl, HopID * 2));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetAdapter(usb4_port_ctx->m_pControl, usb4_port_ctx->m_Number));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetCS(usb4_port_ctx->m_pControl, USB4_cpConfigSpace_PATH));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetData(usb4_port_ctx->m_pControl, NULL, sizeof(usb4_pathN_cs)));

  if(0 != Usb4CtrlIfaceSend(usb4_port_ctx->m_pControl, USB4_SEND_CTRL_PACKET_TIMEOUT_US))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  USB4_ASSERT(0 == Usb4CtrlIfaceGetData(usb4_port_ctx->m_pControl, pBuff, &len, sizeof(usb4_pathN_cs)));
  USB4_ASSERT(0 == Usb4CtrlIfacePop(usb4_port_ctx->m_pControl));
  USB4_ASSERT_MSG(len == sizeof(usb4_pathN_cs), "Didn't read a complete Path CS");

  return 0;
ErrorHandling:
  return -1;
}

int Usb4PortPollforPP(usb4_port_ctx_t* usb4_port_ctx, UINT32 HopID)
{
  UINT32 pollingForPP = 0;
  usb4_pathN_cs path;
  UINT8* pBuff = (UINT8*)(&path);
  UINT32 len;

  USB4_ASSERT(0 == Usb4CtrlIfaceSetRoute(usb4_port_ctx->m_pControl, usb4_port_ctx->m_topologyID));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(usb4_port_ctx->m_pControl, HopID * 2));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetAdapter(usb4_port_ctx->m_pControl, usb4_port_ctx->m_Number));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetCS(usb4_port_ctx->m_pControl, USB4_cpConfigSpace_PATH));

  /* Poll for PP (Packet Pending) is 0 */
  USB4_ASSERT(0 == Usb4CtrlIfaceSetType(usb4_port_ctx->m_pControl, USB4_cpDescriptorType_READ_REQUEST));
  // TODO: AC ERROR why NULL parameter here, results in uninitialized usage
  USB4_ASSERT(0 == Usb4CtrlIfaceSetData(usb4_port_ctx->m_pControl, NULL, 4));
  do
  {
    USB4_ASSERT(0 == Usb4CtrlIfaceSend(usb4_port_ctx->m_pControl, USB4_SEND_CTRL_PACKET_TIMEOUT_US));
    // TODO: AC ERROR why + 4 offset? usb4_pathN_cs is UINT32 only 
    // USB4_ASSERT(0 == Usb4CtrlIfaceGetData(usb4_port_ctx->m_pControl, pBuff + 4, &len, 4));
    USB4_ASSERT(0 == Usb4CtrlIfaceGetData(usb4_port_ctx->m_pControl, pBuff, &len, 4));
    USB4_ASSERT(0 == Usb4CtrlIfacePop(usb4_port_ctx->m_pControl));
    USB4_ASSERT_MSG(len == 4, "Didn't read a complete DWORD");
    USB4_ASSERT_MSG(pollingForPP++ < 1000, "Packet pending looks stuck\n");
  } while (1 == path.PATH_CS_1.PendingPackets);

  return 0;
}

int Usb4PortWriteSegment(usb4_port_ctx_t* usb4_port_ctx, UINT32 HopID, usb4_pathN_cs* path)
{
  UINT8* pBuff = (UINT8*)(path);
  UINT32 len;

  /* Keep track of m_referenceCountIngressSharedFlowControl, and m_freeBuffers */
  if (path->PATH_CS_1.IngressSharedBufferingEnable)
  {
    if (1 == path->PATH_CS_0.Valid)
    {
      if (0 == usb4_port_ctx->m_referenceCountIngressSharedFlowControl)
      {
        USB4_ASSERT(usb4_port_ctx->m_freeBuffers >= usb4_port_ctx->m_cs.ADP_CS_5.LinkCreditsAllocated);
        usb4_port_ctx->m_freeBuffers -= usb4_port_ctx->m_cs.ADP_CS_5.LinkCreditsAllocated;
      }
      usb4_port_ctx->m_referenceCountIngressSharedFlowControl++;
    }
    else
    {
      usb4_port_ctx->m_referenceCountIngressSharedFlowControl--;
      if (0 == usb4_port_ctx->m_referenceCountIngressSharedFlowControl)
      {
        usb4_port_ctx->m_freeBuffers += usb4_port_ctx->m_cs.ADP_CS_5.LinkCreditsAllocated;
      }
    }
  }
  else
  {
    USB4_portType port = Usb4PortGetPortType(usb4_port_ctx);
    if ((USB4_portType_LANE0 == port) && (path->PATH_CS_1.IngressFlowControl))
    {
      if (1 == path->PATH_CS_0.Valid)
      {
        if (usb4_port_ctx->m_freeBuffers >= path->PATH_CS_0.PathCreditsAllocated)
        {
          /* Update USB4 port with the new value of free buffers... */
          usb4_port_ctx->m_freeBuffers -= path->PATH_CS_0.PathCreditsAllocated;
        }
        else
        {
          USB4_ASSERT(usb4_port_ctx->m_freeBuffers > 0);
          path->PATH_CS_0.PathCreditsAllocated = usb4_port_ctx->m_freeBuffers;
          usb4_port_ctx->m_freeBuffers = 0;
        }
      }
      else
      {
        usb4_port_ctx->m_freeBuffers += path->PATH_CS_0.PathCreditsAllocated;
      }
    }
  }

  /* Experiment: Update Non flow controlled buffers */
  if (USB4_portType_LANE0 == Usb4PortGetPortType(usb4_port_ctx))
  {
    UINT32 value =  usb4_port_ctx->m_freeBuffers;

    /* Keep some credits for control port and such - hub will hang if all credits are written as no-flow control */
    if (value + 8 > usb4_port_ctx->m_cs.ADP_CS_4.TotalBuffers)
    {
      value = usb4_port_ctx->m_cs.ADP_CS_4.TotalBuffers - 8;
    }

    //        // This is an intel hub specific hack - if too much non flow control credits are written,
    //        // hub fails to produce response
    //        if (m_topologyID != 0)
    //        {
    //            if (m_freeBuffers > 0x46)
    //            {
    //                value = 0x46;
    //            }
    //        }

    if (value != usb4_port_ctx->m_cs.ADP_CS_4.NonFlowControlledBuffers)
    {
      // USB4_LOG_DEBUG("\nWrite NonFlowControlledBuffers Topology %x, Port %u (%s), NonFlowControlledBuffers %u, Total buffers %u\n",
      //    USB4_LOWER32(usb4_port_ctx->m_topologyID), usb4_port_ctx->m_Number, Usb4PortGetName(usb4_port_ctx), value, usb4_port_ctx->m_cs.ADP_CS_4.TotalBuffers);
      Usb4Log4(USB4_LOG_CM, Usb4PortWriteSegmentWriteNonFlowControlledBuffers__Params__Topology_Port_NonFlowControlledBuffers_TotalBuffers, 0, 
          USB4_LOWER32(usb4_port_ctx->m_topologyID), usb4_port_ctx->m_Number, value, usb4_port_ctx->m_cs.ADP_CS_4.TotalBuffers);
      /* Read modify write */
      USB4_ASSERT(0 ==Usb4PortReadCS(usb4_port_ctx));
      usb4_port_ctx->m_cs.ADP_CS_4.NonFlowControlledBuffers = value;
      USB4_ASSERT(0 ==Usb4PortWriteCS(usb4_port_ctx));
    }
  }

#if 0
  USB4_LOG_DEBUG("\nWriteSegment Topology %x, Port %u (%s),\n"
      "Input HopID: %u\n"
      "   PATH_CS_0.OutputHopID %u;\n"
      "   PATH_CS_0.OutputAdapter %u;\n"
      "   PATH_CS_0.PathCreditsAllocated %u;\n"
      "   PATH_CS_0.Valid %u;\n\n"
      "   PATH_CS_1.Weight %u;\n"
      "   PATH_CS_1.Priority %u;\n"
      "   PATH_CS_1.CounterID %u;\n"
      "   PATH_CS_1.CounterEnable %u;\n"
      "   PATH_CS_1.IngressFlowControl %u;\n"
      "   PATH_CS_1.EgressFlowControl %u;\n"
      "   PATH_CS_1.IngressSharedBufferingEnable %u;\n"
      "   PATH_CS_1.EgressSharedBufferingEnable %u;\n"
      "   PATH_CS_1.PendingPackets %u;\n"
      "   Adapter has %u buffers left\n\n",
      USB4_LOWER32(usb4_port_ctx->m_topologyID), usb4_port_ctx->m_Number, Usb4PortGetName(usb4_port_ctx),
      (UINT32)HopID,
      (UINT32)path->PATH_CS_0.OutputHopID         ,
      (UINT32)path->PATH_CS_0.OutputAdapter       ,
      (UINT32)path->PATH_CS_0.PathCreditsAllocated,
      (UINT32)path->PATH_CS_0.Valid               ,
      (UINT32)path->PATH_CS_1.Weight                      ,
      (UINT32)path->PATH_CS_1.Priority                    ,
      (UINT32)path->PATH_CS_1.CounterID                   ,
      (UINT32)path->PATH_CS_1.CounterEnable               ,
      (UINT32)path->PATH_CS_1.IngressFlowControl          ,
      (UINT32)path->PATH_CS_1.EgressFlowControl           ,
      (UINT32)path->PATH_CS_1.IngressSharedBufferingEnable,
      (UINT32)path->PATH_CS_1.EgressSharedBufferingEnable ,
      (UINT32)path->PATH_CS_1.PendingPackets              ,
      usb4_port_ctx->m_freeBuffers);
#endif
  Usb4Log3(USB4_LOG_CM, Usb4PortWriteSegment__Params__Topology_Port_InputHopID, 0, 
      USB4_LOWER32(usb4_port_ctx->m_topologyID), 
      usb4_port_ctx->m_Number, 
      (UINT32)HopID);
  Usb4Log3(USB4_LOG_CM, Usb4PortWriteSegment__Params__CS0OutputHopID_CS0OutputAdapter_CS0PathCreditsAllocated, 0, 
      (UINT32)path->PATH_CS_0.OutputHopID, 
      (UINT32)path->PATH_CS_0.OutputAdapter, 
      (UINT32)path->PATH_CS_0.PathCreditsAllocated);
  Usb4Log3(USB4_LOG_CM, Usb4PortWriteSegment__Params__CS0Valid_CS1Weight_CS1Priority, 0, 
      (UINT32)path->PATH_CS_0.Valid,
      (UINT32)path->PATH_CS_1.Weight,
      (UINT32)path->PATH_CS_1.Priority);
  Usb4Log3(USB4_LOG_CM, Usb4PortWriteSegment__Params__CS1CounterID_CounterEnable_IngressFlowControl, 0, 
      (UINT32)path->PATH_CS_1.CounterID,
      (UINT32)path->PATH_CS_1.CounterEnable,
      (UINT32)path->PATH_CS_1.IngressFlowControl);
  Usb4Log3(USB4_LOG_CM, Usb4PortWriteSegment__Params__CS1EgressFlowControl_CS1IngressSharedBufferingEnable_CS1EgressSharedBufferingEnable, 0, 
      (UINT32)path->PATH_CS_1.EgressFlowControl,
      (UINT32)path->PATH_CS_1.IngressSharedBufferingEnable,
      (UINT32)path->PATH_CS_1.EgressSharedBufferingEnable);
  Usb4Log2(USB4_LOG_CM, Usb4PortWriteSegment__Params__CS1PendingPackets_freeBuffers, 0,
      (UINT32)path->PATH_CS_1.PendingPackets,
      usb4_port_ctx->m_freeBuffers);

  //Andreyb: Workaround for number of credits latching
  if (1 == path->PATH_CS_0.Valid)
  {
    if (0 == usb4_port_ctx->m_topologyID)
    {
      /* First write CS1 and then CS0 */
      USB4_ASSERT(0 == Usb4CtrlIfaceSetType(usb4_port_ctx->m_pControl, USB4_cpDescriptorType_WRITE_REQUEST));
      USB4_ASSERT(0 == Usb4CtrlIfaceSetRoute(usb4_port_ctx->m_pControl, usb4_port_ctx->m_topologyID));
      USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(usb4_port_ctx->m_pControl, (HopID * 2)+1));
      USB4_ASSERT(0 == Usb4CtrlIfaceSetAdapter(usb4_port_ctx->m_pControl, usb4_port_ctx->m_Number));
      USB4_ASSERT(0 == Usb4CtrlIfaceSetCS(usb4_port_ctx->m_pControl, USB4_cpConfigSpace_PATH));
      USB4_ASSERT(0 == Usb4CtrlIfaceSetData(usb4_port_ctx->m_pControl, pBuff+4, 4));
      USB4_ASSERT(0 == Usb4CtrlIfaceSend(usb4_port_ctx->m_pControl, USB4_SEND_CTRL_PACKET_TIMEOUT_US));
      USB4_ASSERT(0 == Usb4CtrlIfaceGetData(usb4_port_ctx->m_pControl, NULL, &len, 4));
      USB4_ASSERT(0 == Usb4CtrlIfacePop(usb4_port_ctx->m_pControl));
      USB4_ASSERT_MSG(len == 4, "Didn't write a complete Path CS");

      USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(usb4_port_ctx->m_pControl, HopID * 2));
      USB4_ASSERT(0 == Usb4CtrlIfaceSetData(usb4_port_ctx->m_pControl, pBuff, 4));
      USB4_ASSERT(0 ==  Usb4CtrlIfaceSend(usb4_port_ctx->m_pControl, USB4_SEND_CTRL_PACKET_TIMEOUT_US));
      USB4_ASSERT(0 == Usb4CtrlIfaceGetData(usb4_port_ctx->m_pControl, NULL, &len, 4));
      USB4_ASSERT(0 == Usb4CtrlIfacePop(usb4_port_ctx->m_pControl));
      USB4_ASSERT_MSG(len == 4, "Didn't write a complete Path CS");
    }
    else
    {
      USB4_ASSERT(0 == Usb4CtrlIfaceSetType(usb4_port_ctx->m_pControl, USB4_cpDescriptorType_WRITE_REQUEST));
      USB4_ASSERT(0 == Usb4CtrlIfaceSetRoute(usb4_port_ctx->m_pControl, usb4_port_ctx->m_topologyID));
      USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(usb4_port_ctx->m_pControl, HopID * 2));
      USB4_ASSERT(0 == Usb4CtrlIfaceSetAdapter(usb4_port_ctx->m_pControl, usb4_port_ctx->m_Number));
      USB4_ASSERT(0 == Usb4CtrlIfaceSetCS(usb4_port_ctx->m_pControl, USB4_cpConfigSpace_PATH));;
      USB4_ASSERT(0 == Usb4CtrlIfaceSetData(usb4_port_ctx->m_pControl, pBuff, 8));
      USB4_ASSERT(0 ==  Usb4CtrlIfaceSend(usb4_port_ctx->m_pControl, USB4_SEND_CTRL_PACKET_TIMEOUT_US));
      USB4_ASSERT(0 == Usb4CtrlIfaceGetData(usb4_port_ctx->m_pControl, NULL, &len, 8));
      USB4_ASSERT(0 == Usb4CtrlIfacePop(usb4_port_ctx->m_pControl));
      USB4_ASSERT_MSG(len == 8, "Didn't write a complete Path CS");
    }
  }
  else
  {
    UINT32 pollingForPP = 0;
    /* First write CS0 and then CS1 */
    USB4_ASSERT(0 == Usb4CtrlIfaceSetType(usb4_port_ctx->m_pControl, USB4_cpDescriptorType_WRITE_REQUEST));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetRoute(usb4_port_ctx->m_pControl, usb4_port_ctx->m_topologyID));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(usb4_port_ctx->m_pControl, HopID * 2));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetAdapter(usb4_port_ctx->m_pControl, usb4_port_ctx->m_Number));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetCS(usb4_port_ctx->m_pControl, USB4_cpConfigSpace_PATH));;
    USB4_ASSERT(0 == Usb4CtrlIfaceSetData(usb4_port_ctx->m_pControl, pBuff, 4));
    USB4_ASSERT(0 == Usb4CtrlIfaceSend(usb4_port_ctx->m_pControl, USB4_SEND_CTRL_PACKET_TIMEOUT_US));
    USB4_ASSERT(0 == Usb4CtrlIfaceGetData(usb4_port_ctx->m_pControl, NULL, &len, 4));
    USB4_ASSERT(0 == Usb4CtrlIfacePop(usb4_port_ctx->m_pControl));
    USB4_ASSERT_MSG(len == 4, "Didn't write a complete Path CS");

    USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(usb4_port_ctx->m_pControl, (HopID * 2) + 1));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetData(usb4_port_ctx->m_pControl, pBuff + 4, 4));
    USB4_ASSERT(0 == Usb4CtrlIfaceSend(usb4_port_ctx->m_pControl, USB4_SEND_CTRL_PACKET_TIMEOUT_US));
    USB4_ASSERT(0 == Usb4CtrlIfaceGetData(usb4_port_ctx->m_pControl, NULL, &len, 4));
    USB4_ASSERT(0 == Usb4CtrlIfacePop(usb4_port_ctx->m_pControl));
    USB4_ASSERT_MSG(len == 4, "Didn't write a complete Path CS");

    /* Poll for PP (Packet Pending) is 0 */
    USB4_ASSERT(0 == Usb4CtrlIfaceSetType(usb4_port_ctx->m_pControl, USB4_cpDescriptorType_READ_REQUEST));
    USB4_ASSERT(0 == Usb4CtrlIfaceSetData(usb4_port_ctx->m_pControl, NULL, 4));
    do
    {
      USB4_ASSERT(0 == Usb4CtrlIfaceSend(usb4_port_ctx->m_pControl, USB4_SEND_CTRL_PACKET_TIMEOUT_US));
      USB4_ASSERT(0 == Usb4CtrlIfaceGetData(usb4_port_ctx->m_pControl, pBuff + 4, &len, 4));
      USB4_ASSERT(0 == Usb4CtrlIfacePop(usb4_port_ctx->m_pControl));
      USB4_ASSERT_MSG(len == 4, "Didn't read a complete DWORD");
      USB4_ASSERT_MSG(pollingForPP++ < 1000, "Packet pending looks stuck\n");
    } while (1 == path->PATH_CS_1.PendingPackets);
  }
  return 0;
}

int Usb4PortUpdateLinkCreditsAllocated(usb4_port_ctx_t* usb4_port_ctx, UINT32 linkCreditsAllocated)
{
  if ((0 == usb4_port_ctx->m_referenceCountIngressSharedFlowControl) &&
      (usb4_port_ctx->m_cs.ADP_CS_5.LinkCreditsAllocated != linkCreditsAllocated))
  {
    usb4_port_ctx->m_cs.ADP_CS_5.LinkCreditsAllocated = linkCreditsAllocated;
    return Usb4PortWriteCS(usb4_port_ctx);
  }
  else
  {
    return 0;
  }
}
                                        
int Usb4PortIssuePortOperation(usb4_port_ctx_t* usb4_port_ctx, USB4_port_operation* operationData)
{
  USB4_portSbAccesses transferDetails = {0};
  transferDetails.target = USB4_SB_PORT_ACCESS;
  transferDetails.index = 0;

  //writing to metadata
  if (NULL != operationData->metaData && operationData->metaDataDwNum != 0)
  {
    transferDetails.address = USB4_SB_REG_METADATA;
    transferDetails.wnr  = USB4_SB_WNR_WRITE;
    transferDetails.len = operationData->metaDataDwNum*4;//in bytes
    transferDetails.pData  = operationData->metaData;
    USB4_ASSERT_MSG(0 == Usb4PortOperationSbCs(usb4_port_ctx, &transferDetails),"failed: writing to metadata");
  } 

  //writing to data
  if (NULL !=  operationData->data && operationData->dataDwNum != 0)
  {
    transferDetails.address = USB4_SB_REG_DATA;
    transferDetails.wnr  = USB4_SB_WNR_WRITE;
    transferDetails.len = operationData->dataDwNum*4;//16;//in bytes
    transferDetails.pData  = operationData->data;
    USB4_ASSERT_MSG(0 == Usb4PortOperationSbCs(usb4_port_ctx, &transferDetails),"failed: writing to data");
  }

  //writing the opcode will initiate the operation
  transferDetails.address = USB4_SB_REG_OPCODE;
  transferDetails.wnr  = USB4_SB_WNR_WRITE;
  transferDetails.len = 4;//in bytes
  transferDetails.pData  =  (UINT8*)(&operationData->op_code);
  USB4_ASSERT_MSG(0 == Usb4PortOperationSbCs(usb4_port_ctx, &transferDetails),"failed:writing to opcode");

  /* Completion Opcode: 0 for success */
  transferDetails.address = USB4_SB_REG_OPCODE;
  transferDetails.wnr  = USB4_SB_WNR_READ;
  USB4_ASSERT_MSG(0 == Usb4PortOperationSbCs(usb4_port_ctx, &transferDetails),"failed: reading opcode");
  memcpy((UINT8*)(&operationData->op_code), transferDetails.pData, 4);

  USB4_ASSERT_MSG(USB4_PORT_OPERATION_RC_FAIL != operationData->op_code,"operation failed to execute");
  if(USB4_PORT_OPERATION_RC_NOT_SUPP == operationData->op_code)
  {
    // USB4_LOG_WARNING("operation not supported\n");
    Usb4Log(USB4_LOG_CM, Usb4PortIssuePortOperationXOpeationNotSupported__Warn, 0);
  }

  /* Completion Data */
  if(operationData->data && operationData->ComplDataDwNum != 0)
  {
      transferDetails.address = USB4_SB_REG_DATA;
      transferDetails.wnr  = USB4_SB_WNR_READ;
      transferDetails.len = operationData->ComplDataDwNum*4;//in bytes; 0 to 3 completion DW (Table 8-55. List of Port Operations)
      USB4_ASSERT_MSG(0 == Usb4PortOperationSbCs(usb4_port_ctx, &transferDetails),"failed: reading from data");
      memcpy(operationData->data, transferDetails.pData, transferDetails.len);
  }

  /* Completion metadata */
  if(operationData->metaData && operationData->ComplMetaDataDwNum != 0)
  {
      transferDetails.address = USB4_SB_REG_METADATA;
      transferDetails.wnr  = USB4_SB_WNR_READ;
      transferDetails.len = operationData->ComplMetaDataDwNum*4;//in bytes; 0 to 1 completion DW (Table 8-55. List of Port Operations)
      USB4_ASSERT_MSG(0 == Usb4PortOperationSbCs(usb4_port_ctx, &transferDetails),"failed: reading from metadata");
      memcpy(operationData->metaData, transferDetails.pData, transferDetails.len);
  }
  return 0;
} 



int Usb4PortPortOperationRequest(usb4_port_ctx_t* usb4_port_ctx, USB4_port_operation* operationData, USB4_sb_target target)
{
    USB4_portSbAccesses transferDetails = {0};
     transferDetails.target = USB4_SB_PORT_ACCESS;
     transferDetails.index = 0;

     //writing to metadata
     if (NULL != operationData->metaData && operationData->metaDataDwNum != 0)
     {
         transferDetails.address = USB4_SB_REG_METADATA;
         transferDetails.wnr  = USB4_SB_WNR_WRITE;
         transferDetails.len = operationData->metaDataDwNum*4;//in bytes
         transferDetails.pData  = operationData->metaData;
         USB4_ASSERT_MSG(0 == Usb4PortOperationSbCs(usb4_port_ctx, &transferDetails),"failed: writing to metadata");
     }

     //writing to data
     if (NULL !=  operationData->data && operationData->dataDwNum != 0)
     {
         transferDetails.address = USB4_SB_REG_DATA;
         transferDetails.wnr  = USB4_SB_WNR_WRITE;
         transferDetails.len = operationData->dataDwNum*4;//16;//in bytes
         transferDetails.pData  = operationData->data;
         USB4_ASSERT_MSG(0 == Usb4PortOperationSbCs(usb4_port_ctx, &transferDetails),"failed: writing to data");
     }

     //writing the opcode will initiate the operation
     transferDetails.address = USB4_SB_REG_OPCODE;
     transferDetails.wnr  = USB4_SB_WNR_WRITE;
     transferDetails.len = 4;//in bytes
     transferDetails.pData  =  (UINT8*)(&operationData->op_code);
     USB4_ASSERT_MSG(0 == Usb4PortOperationSbCs(usb4_port_ctx, &transferDetails),"failed:writing to opcode");

    return 0;
}



int Usb4PortPortOperationCompletion(usb4_port_ctx_t* usb4_port_ctx, USB4_port_operation* operationData, USB4_sb_target target)
{
    USB4_portSbAccesses transferDetails = {0};
    transferDetails.target = USB4_SB_PORT_ACCESS;
    transferDetails.index = 0;

    /* Completion Opcode: 0 for success */
    transferDetails.address = USB4_SB_REG_OPCODE;
    transferDetails.wnr  = USB4_SB_WNR_READ;
    transferDetails.len = 4;//in bytes
    transferDetails.pData  =  (UINT8*)(&operationData->op_code);
    USB4_ASSERT_MSG(0 == Usb4PortOperationSbCs(usb4_port_ctx, &transferDetails),"failed: reading opcode");
    memcpy((UINT8*)(&operationData->op_code), transferDetails.pData, 4);

    USB4_ASSERT_MSG(USB4_PORT_OPERATION_RC_FAIL != operationData->op_code,"operation failed to execute");
    if(USB4_PORT_OPERATION_RC_NOT_SUPP == operationData->op_code)
    {
        // USB4_LOG_WARNING("operation not supported\n");
        Usb4Log(USB4_LOG_CM, Usb4PortPortOperationCompletionOperationNotSupported__Warn, 0);
    }

    /* Completion Data */
    if(operationData->data && operationData->ComplDataDwNum != 0)
    {
        transferDetails.address = USB4_SB_REG_DATA;
        transferDetails.wnr  = USB4_SB_WNR_READ;
        transferDetails.len = operationData->ComplDataDwNum*4;//in bytes; 0 to 3 completion DW (Table 8-55. List of Port Operations)
        USB4_ASSERT_MSG(0 == Usb4PortOperationSbCs(usb4_port_ctx, &transferDetails),"failed: reading from data");
        memcpy(operationData->data, transferDetails.pData, transferDetails.len);
    }

    /* Completion metadata */
    if(operationData->metaData && operationData->ComplMetaDataDwNum != 0)
    {
        transferDetails.address = USB4_SB_REG_METADATA;
        transferDetails.wnr  = USB4_SB_WNR_READ;
        transferDetails.len = operationData->ComplMetaDataDwNum*4;//in bytes; 0 to 1 completion DW (Table 8-55. List of Port Operations)
        USB4_ASSERT_MSG(0 == Usb4PortOperationSbCs(usb4_port_ctx, &transferDetails),"failed: reading from metadata");
        memcpy(operationData->metaData, transferDetails.pData, transferDetails.len);
    }

    return 0;
}



int Usb4PortUsb4PortOperationSbCs(usb4_port_ctx_t* usb4_port_ctx, USB4_portSbAccesses* transferDetails)
{
  usb4_ctrl_iface_trn transfer = {0};
  usb4_usb4_port_cs portCs;
  BOOLEAN exitCondition; 
  UINT32 timeoutForResponseMsec = SB_RESPONSE_TIMEOUT_MS;
  UINT32 elapsedTime_ms = 0;
  usb4_utils_timer timer;
  timer.m_source = USB4_TIMER_SOURCE_QTIMER;
  UINT32 wnr = transferDetails->wnr;

  /* Prepare data to send to sideband */
  memset((void*)(&portCs), 0, sizeof(portCs));
  portCs.PORT_CS_1.Target = transferDetails->target;
  portCs.PORT_CS_1.Address = transferDetails->address;//SB register address
  portCs.PORT_CS_1.WnR = wnr;
  portCs.PORT_CS_1.Length = transferDetails->len;
  portCs.PORT_CS_1.RetimerInex = transferDetails->index;
  portCs.PORT_CS_1.Pending_PND = 0;

  /* CMD */
  transfer.topologyId = usb4_port_ctx->m_topologyID;
  transfer.timeout_us = 10000;
  transfer.adapterNum = usb4_port_ctx->m_Number;
  transfer.cs = USB4_cpConfigSpace_ADAPTER;
  transfer.type = USB4_cpDescriptorType_WRITE_REQUEST;

//  /* Perfrom transaction to port capability */    
//  USB4_ASSERT(0 == Usb4CtrlIfaceTransfer(usb4_port_ctx->m_pControl, &transfer));

  /* WRITE DATA */
  if(USB4_SB_WNR_WRITE == wnr)
  {
    /* data */
    memcpy((void*)(&portCs.PORT_CS_2_17), transferDetails->pData, transferDetails->len); 
    transfer.address = USB4_SB_CS_2_OFFS;
    transfer.size_bytes = sizeof(portCs.PORT_CS_2_17);
    transfer.pBuff = (UINT8*)(&portCs.PORT_CS_2_17);
    //USB4_LOG_INFO("PORT_CS_2 %x\n",(portCs.PORT_CS_2_17.Data[0]));
    USB4_ASSERT(0 == Usb4CtrlIfaceTransfer(usb4_port_ctx->m_pControl, &transfer));
  }  

  /* CMD with pending=1 */
  portCs.PORT_CS_1.Pending_PND = 1; 
  transfer.address = USB4_SB_CS_1_OFFS;
  transfer.size_bytes = sizeof(portCs.PORT_CS_1);
  transfer.pBuff = (UINT8*)(&portCs.PORT_CS_1);
  USB4_ASSERT(0 == Usb4CtrlIfaceTransfer(usb4_port_ctx->m_pControl, &transfer));

  /* Setup the command to poll execution status */
  transfer.type = USB4_cpDescriptorType_READ_REQUEST;
  transfer.address = USB4_SB_CS_1_OFFS;
  transfer.size_bytes = sizeof(portCs.PORT_CS_1);
  memset((UINT8*)(&portCs.PORT_CS_1), 0, transfer.size_bytes);
  transfer.pBuff = (UINT8*)(&portCs.PORT_CS_1);

  /* Wait for response */
  if(0 == usb4_port_ctx->m_topologyID)
  {
    exitCondition = FALSE;
    USB4_ASSERT(0 == usb4_timer_Start(&timer)); 
    do
    {
      USB4_ASSERT(0 == Usb4CtrlIfaceTransfer(usb4_port_ctx->m_pControl, &transfer));
      exitCondition = (0 == portCs.PORT_CS_1.Pending_PND) || (elapsedTime_ms > timeoutForResponseMsec);
      USB4_ASSERT(0 == usb4_timer_GetElapsed_ms(&timer, &elapsedTime_ms));
    } while(FALSE == exitCondition);

    USB4_ASSERT_MSG(0 == portCs.PORT_CS_1.ResultCode_RC, "RC: Operation failed\n");
  }
  else
  {
    //TBD
  }

  USB4_ASSERT_MSG(0 == portCs.PORT_CS_1.Pending_PND, "PND was not cleared\n")


  /* READ DATA */
  if(USB4_SB_WNR_READ == wnr)
  {
    /* data */
    transfer.type = USB4_cpDescriptorType_READ_REQUEST;
    transfer.address = USB4_SB_CS_2_OFFS;
    transfer.size_bytes = sizeof(portCs.PORT_CS_2_17);
    transfer.pBuff = (UINT8*)(&portCs.PORT_CS_2_17);

    //clear read buff
    memset((void*)(transfer.pBuff), 0, transfer.size_bytes);
    USB4_ASSERT(0 == Usb4CtrlIfaceTransfer(usb4_port_ctx->m_pControl, &transfer));
    // USB4_LOG_INFO("read data %x\n",*((UINT32*)(transfer.pBuff)));
    Usb4Log1(USB4_LOG_CM, Usb4PortUsb4PortOperationSbCsReadData__Params__pBuffAddr, 0, *((UINT32*)(transfer.pBuff)));
    memcpy(transferDetails->pData, (void*)(transfer.pBuff), transferDetails->len);
  }

  return 0;
}

int Usb4PortDisableHotPlugNotification(usb4_port_ctx_t* usb4_port_ctx, BOOLEAN bDisable)
{
  usb4_port_ctx->m_cs.ADP_CS_5.DisableHotPlugEvents = bDisable?1:0;
  return Usb4PortWriteCS(usb4_port_ctx);
}

int Usb4PortTmuTimeSync(usb4_port_ctx_t* usb4_port_ctx, BOOLEAN bEnable)
{
  UINT32 capSize=0;

  if (0 != usb4_port_ctx->m_adapterTmuCapability.TMU_ADP_CS_0.CapabilityID) /* If the capability was read before */
  {
    if ((bEnable?0:1) == usb4_port_ctx->m_adapterTmuCapability.TMU_ADP_CS_6.dts) /* Prevent multiple enables/disables */
    {
      return 0;
    }
  }
  else
  {
    USB4_ASSERT(0 == Usb4PortSearchCapability(usb4_port_ctx, USB4_LANE_ADAPTER_TMU_CAPABILITY, &capSize));
    USB4_ASSERT(0 == Usb4PortReadCapability(usb4_port_ctx, (UINT8*)(&usb4_port_ctx->m_adapterTmuCapability), MIN(capSize, sizeof(usb4_port_ctx->m_adapterTmuCapability))));
  }

  USB4_ASSERT(0 == Usb4PortSearchCapability(usb4_port_ctx, USB4_LANE_ADAPTER_TMU_CAPABILITY, &capSize));
  USB4_ASSERT(0 == Usb4PortReadCapabilityDword(usb4_port_ctx, (UINT8 *)(&usb4_port_ctx->m_adapterTmuCapability), 6));
  usb4_port_ctx->m_adapterTmuCapability.TMU_ADP_CS_6.dts = bEnable?0:1;
  USB4_ASSERT(0 == Usb4PortWriteCapabilityDword(usb4_port_ctx, (UINT8 *)(&usb4_port_ctx->m_adapterTmuCapability), 6));
  return 0;
}

int Usb4PortTmuUniDirectionalMode(usb4_port_ctx_t* usb4_port_ctx, BOOLEAN bUniDir)
{
  UINT32 capSize=0;

  if (0 != usb4_port_ctx->m_adapterTmuCapability.TMU_ADP_CS_0.CapabilityID) /* If the capability was read before */
  {
    if ((bUniDir?1:0) == usb4_port_ctx->m_adapterTmuCapability.TMU_ADP_CS_3.EnableUniDirectionalMode_UDM) /* Prevent multiple enables/disables */
    {
      return 0;
    }
  }
  else
  {
    USB4_ASSERT(0 == Usb4PortSearchCapability(usb4_port_ctx, USB4_LANE_ADAPTER_TMU_CAPABILITY, &capSize));
    USB4_ASSERT(0 == Usb4PortReadCapability(usb4_port_ctx, (UINT8 *)(&usb4_port_ctx->m_adapterTmuCapability), MIN(capSize, sizeof(usb4_port_ctx->m_adapterTmuCapability))));
  }

  USB4_ASSERT(0 == Usb4PortSearchCapability(usb4_port_ctx, USB4_LANE_ADAPTER_TMU_CAPABILITY, &capSize));
  USB4_ASSERT(0 == Usb4PortReadCapabilityDword(usb4_port_ctx, (UINT8 *)(&usb4_port_ctx->m_adapterTmuCapability), 3));
  usb4_port_ctx->m_adapterTmuCapability.TMU_ADP_CS_3.EnableUniDirectionalMode_UDM = bUniDir?1:0;
  USB4_ASSERT(0 == Usb4PortWriteCapabilityDword(usb4_port_ctx, (UINT8 *)(&usb4_port_ctx->m_adapterTmuCapability), 3));

  return 0;
}

/*-------------------------------------------------------*/

int Usb4PortTMUSetInterdomainMaster(usb4_port_ctx_t* usb4_port_ctx)
{
  USB4_ASSERT(0 == Usb4PortSearchCapability(usb4_port_ctx, USB4_LANE_ADAPTER_TMU_CAPABILITY, NULL));

  USB4_ASSERT(0 == Usb4PortReadCapability(usb4_port_ctx, 
        (UINT8 *)(&usb4_port_ctx->m_adapterTmuCapability),
        sizeof(usb4_port_ctx->m_adapterTmuCapability)));

  usb4_port_ctx->m_adapterTmuCapability.TMU_ADP_CS_3.InterDomainMaster_IDM = 1;
  usb4_port_ctx->m_adapterTmuCapability.TMU_ADP_CS_3.InterDomainSlave_IDS = 0;

  USB4_ASSERT(0 == Usb4PortWriteCapability(usb4_port_ctx,      
        (UINT8 *)(&usb4_port_ctx->m_adapterTmuCapability),
        sizeof(usb4_port_ctx->m_adapterTmuCapability)));

  return 0;
}

/*-------------------------------------------------------*/

int Usb4PortTMUSetInterdomainSlave(usb4_port_ctx_t* usb4_port_ctx)
{
  USB4_ASSERT(0 == Usb4PortSearchCapability(usb4_port_ctx, USB4_LANE_ADAPTER_TMU_CAPABILITY, NULL));

  USB4_ASSERT(0 == Usb4PortReadCapability(usb4_port_ctx, 
        (UINT8*)(&usb4_port_ctx->m_adapterTmuCapability),
        sizeof(usb4_port_ctx->m_adapterTmuCapability)));

  usb4_port_ctx->m_adapterTmuCapability.TMU_ADP_CS_3.InterDomainMaster_IDM = 0;
  usb4_port_ctx->m_adapterTmuCapability.TMU_ADP_CS_3.InterDomainSlave_IDS = 1;


  USB4_ASSERT(0 == Usb4PortWriteCapability(usb4_port_ctx,      
        (UINT8*)(&usb4_port_ctx->m_adapterTmuCapability),
        sizeof(usb4_port_ctx->m_adapterTmuCapability)));

  return 0;
}

/*-------------------------------------------------------*/

int Usb4PortGetCounterSet(usb4_port_ctx_t* usb4_port_ctx, UINT32 setId, usb4_adapter_counter_set *pCounterSet)
{
  UINT32 len;

  /* Validate the id is leagal */
  if (usb4_port_ctx->m_cs.ADP_CS_1.MaxCounterSets < setId)
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  USB4_ASSERT(0 == Usb4CtrlIfaceSetType(usb4_port_ctx->m_pControl, USB4_cpDescriptorType_READ_REQUEST));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetRoute(usb4_port_ctx->m_pControl, usb4_port_ctx->m_topologyID));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(usb4_port_ctx->m_pControl, setId * sizeof(usb4_adapter_counter_set) / 4));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetAdapter(usb4_port_ctx->m_pControl, usb4_port_ctx->m_Number));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetCS(usb4_port_ctx->m_pControl, USB4_cpConfigSpace_COUNTERS));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetData(usb4_port_ctx->m_pControl, (UINT8*)(pCounterSet),
        sizeof(usb4_adapter_counter_set)));

  if(0 != Usb4CtrlIfaceSend(usb4_port_ctx->m_pControl, USB4_SEND_CTRL_PACKET_TIMEOUT_US))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  USB4_ASSERT(0 == Usb4CtrlIfaceGetData(usb4_port_ctx->m_pControl, (UINT8*)(pCounterSet), 
        &len, sizeof(usb4_adapter_counter_set)));
  USB4_ASSERT(0 == Usb4CtrlIfacePop(usb4_port_ctx->m_pControl));
  USB4_ASSERT_MSG(len == sizeof(usb4_adapter_counter_set), "Didn't read a complete Counter CS");

  return 0;
ErrorHandling:
  return -1;
}

/*-------------------------------------------------------*/

int Usb4PortClearCounterSet(usb4_port_ctx_t* usb4_port_ctx, UINT32 setId)
{
  usb4_adapter_counter_set counterSet;

  /* Validate the id is leagal */
  if (usb4_port_ctx->m_cs.ADP_CS_1.MaxCounterSets < setId)
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  USB4_ASSERT(0 == Usb4CtrlIfaceSetType(usb4_port_ctx->m_pControl, USB4_cpDescriptorType_WRITE_REQUEST));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetRoute(usb4_port_ctx->m_pControl, usb4_port_ctx->m_topologyID));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetAddress(usb4_port_ctx->m_pControl, setId * sizeof(usb4_adapter_counter_set) / 4));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetAdapter(usb4_port_ctx->m_pControl, usb4_port_ctx->m_Number));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetCS(usb4_port_ctx->m_pControl, USB4_cpConfigSpace_COUNTERS));
  USB4_ASSERT(0 == Usb4CtrlIfaceSetData(usb4_port_ctx->m_pControl, (UINT8*)(&counterSet),
        sizeof(counterSet)));

  if(0 != Usb4CtrlIfaceSend(usb4_port_ctx->m_pControl, USB4_SEND_CTRL_PACKET_TIMEOUT_US))
  {
    USB4_ERROR_STACK(-1);
    goto ErrorHandling;
  }

  return 0;
ErrorHandling:
  return -1;
}

/*-------------------------------------------------------*/
