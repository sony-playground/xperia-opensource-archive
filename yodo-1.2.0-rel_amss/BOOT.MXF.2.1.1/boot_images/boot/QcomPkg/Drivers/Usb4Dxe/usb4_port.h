/**---------------------------------------------------------------------------
 * @file usb4_port.h
 *
 * @brief   
 *
 * Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/
#ifndef __USB4_PORT_H_
#define __USB4_PORT_H_

/* --------------------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------------------*/

#include <Usb4Utils.h>
#include "usb4_ctrl_iface.h"
#include "usb4_operation.h"
// #include "VVHAL_usb4_comdef.h"
// #include "VVDRV_usb4_operation.h"

/* --------------------------------------------------------------------------
 * Macros / Types
 *--------------------------------------------------------------------------*/
/** @brief operation defined by usb4 sepc */
#if 0
typedef enum
{
  USB4_PORT_OPERATION_SET_TX_COMP          = 0x4D435854,
  USB4_PORT_OPERATION_SET_RX_COMP          = 0x4D435852, 
  USB4_PORT_OPERATION_START_BER_TEST       = 0x52454253, 
  USB4_PORT_OPERATION_END_BER_TEST         = 0x52454245,
  USB4_PORT_OPERATION_END_BURST_TEST       = 0x52454242,
  USB4_PORT_OPERATION_READ_BRUST_TEST      = 0x52454252,
  USB4_PORT_OPERATION_ENTER_EI_TEST        = 0x54494545,
  USB4_PORT_OPERATION_ROUTER_OFFLINE_MODE  = 0x4e45534c,
  USB4_PORT_OPERATION_ENUMERATE_RETIMERS   = 0x4D554E45,
  USB4_PORT_OPERATION_READ_LANE_MARGIN_CAP = 0x50434452,
  USB4_PORT_OPERATION_RUN_HW_LANE_MARG     = 0x474D4852,
  USB4_PORT_OPERATION_RUN_SW_LANE_MARG     = 0x474D5352,
  USB4_PORT_OPERATION_READ_SW_MARG_ERR     = 0x57534452,
  /* operation completion indicated by OPCODE register acc. to 8.3.2 Port Operations */
  USB4_PORT_OPERATION_RC_SUCCESS           = 0,
  USB4_PORT_OPERATION_RC_NOT_SUPP          = 0x444D4321,   // '!CMD'
  USB4_PORT_OPERATION_RC_FAIL              = 0x20525245    // 'ERR '
} USB4_PORT_OPERATION;
#endif

typedef enum {
  USB4_portType_NOT_VALID = -1,
  USB4_portType_CONTROL = 0,
  USB4_portType_HIA = 1,
  USB4_portType_LANE0 = 2,
  USB4_portType_LANE1 = 3,
  USB4_portType_UPSTREAM_PCIE_ADAPTER = 4,
  USB4_portType_UPSTREAM_USB3_ADAPTER = 5,
  USB4_portType_DP_IN = 6,
  USB4_portType_DP_OUT = 7,
  USB4_portType_DOWNSTREAM_PCIE_ADAPTER = 8,
  USB4_portType_DOWNSTREAM_USB3_ADAPTER = 9,
  USB4_portType_RESERVED = 10,
  USB4_portType_ENUM_SIZE = 12
} USB4_portType;

typedef enum {
  USB4_portState_DISABLED = 0,//   Disabled state
  USB4_portState_TRAINING = 1,//Training or Lane Bonding state
  USB4_portState_CL0      = 2,//CL0 state
  USB4_portState_TxCL0    = 3,//Transmitter in CL0s state
  USB4_portState_RxCL0    = 4,//Receiver in CL0s state
  USB4_portState_CL1      = 5,//CL1 state
  USB4_portState_CL2      = 6,//CL2 state
  USB4_portState_CLd      = 7,//CLd state
} USB4_portState;

#define USB4_LANE_ADAPTER_TMU_CAPABILITY  (0x3)
#define USB4_PCIE_ADAPTER_PORT_CAPABILITY (0x4)
#define USB4_USB3_ADAPTER_PORT_CAPABILITY (0x4)
#define USB4_DP_ADAPTER_PORT_CAPABILITY   (0x4)
#define USB4_USB4_PORT_CAPABILITY (0x6)
#define USB4_USB4_LANE_CAPABILITY (0x1)

#pragma pack(push)
#pragma pack(1)

/** 4.1.1.3.2  CM access to SB configuration space */
typedef struct
{
  UINT32 target;  /**< destination adapter */
  UINT32 address; /**< dwrod offset in adapter cs */
  UINT32 wnr;     /**< 1 write, 0 read */
  UINT32 len;     /**< lenth of data in bytes */
  UINT32 index;   /**< retimer index if applicable */
  UINT8* pData;   /**< buffer pointer with size len for the transfer */
} USB4_portSbAccesses;

#if 0
typedef struct
{
  USB4_PORT_OPERATION op_code;
  UINT8* metaData;
  UINT8* data;
} USB4_port_operation;
#endif

typedef struct
{
  struct
  {
    UINT32 NextCapabilityPointer:8;
    UINT32 CapabilityID:8;
    UINT32 res1:16;
  }TMU_ADP_CS_0;

  struct
  {
    UINT32 TxTimeToWire:32;
  }TMU_ADP_CS_1;

  struct
  {
    UINT32 RxTimeToWire:32;
  }TMU_ADP_CS_2;

  struct
  {
    UINT32 res1:29;
    UINT32 EnableUniDirectionalMode_UDM:1;
    UINT32 InterDomainMaster_IDM:1;
    UINT32 InterDomainSlave_IDS:1;
  }TMU_ADP_CS_3;

  struct
  {
    UINT32 RXTSNOSCounter:16;
    UINT32 TXTSNOSCounter:16;
  }TMU_ADP_CS_4;

  struct
  {
    UINT32 RXPacketCounter:16;
    UINT32 TXPacketCounter:16;
  }TMU_ADP_CS_5;

  struct //0x10
  {
    UINT32 res0:1;
    UINT32 dts:1;
    UINT32 dc1:1;
    UINT32 dc2:1;
    UINT32 res1:12;
    UINT32 VendorDefined:16;
  }TMU_ADP_CS_6;

  struct
  {
    UINT32 LostTSNOSCounter:10;
    UINT32 LostPacketCounter:10;
    UINT32 BadPacketCounter:10;
    UINT32 res1:2;
  }TMU_ADP_CS_7;
} USB4_adapter_tmu_capability;

typedef struct
{
  struct
  {
    UINT32 NextCapabilityPointer:8;
    UINT32 CapabilityID:8;
    UINT32 res1:16;
  }TMU_ADP_CS_0;

  struct
  {
    UINT32 TxTimeToWire:32;
  }TMU_ADP_CS_1;

  struct
  {
    UINT32 RxTimeToWire:32;
  }TMU_ADP_CS_2;

  struct
  {
    UINT32 res1:29;
    UINT32 EnableUniDirectionalMode_UDM:1;
    UINT32 InterDomainMaster_IDM:1;
    UINT32 InterDomainSlave_IDS:1;
  }TMU_ADP_CS_3;  

  struct
  {
    UINT32 RXTSNOSCounter:16;
    UINT32 TXTSNOSCounter:16;
  }TMU_ADP_CS_4; 

  struct
  {
    UINT32 RXPacketCounter:16;
    UINT32 TXPacketCounter:16;
  }TMU_ADP_CS_5; 

  struct //0x10
  {
    UINT32 res0:1;
    UINT32 dts:1;
    UINT32 dc1:1;
    UINT32 dc2:1;
    UINT32 res1:12;
    UINT32 VendorDefined:16;
  }TMU_ADP_CS_6; 

  struct
  {
    UINT32 LostTSNOSCounter:10;
    UINT32 LostPacketCounter:10;
    UINT32 BadPacketCounter:10;
    UINT32 res1:2;

  }TMU_ADP_CS_7;

  struct
  {
    UINT32 val;
  }TMU_ADP_CS_8;

  struct
  {
    UINT32 val;
  }TMU_ADP_CS_9;

  struct
  {
    UINT32 val;
  }TMU_ADP_CS_10;

  struct
  {
    UINT32 val;
  }TMU_ADP_CS_11;

  struct
  {
    UINT32 val;
  }TMU_ADP_CS_12;

  struct
  {
    UINT32 val;
  }TMU_ADP_CS_13;
} USB4_adapter_dp_out_tmu_capability;

typedef struct
{
  struct
  {
    // DW0 address 23 in port cs
    UINT32 nextCapabilityPointer : 8;
    UINT32 capabilityID          : 8;
    UINT32 resCs0                : 16;
  } PORT_CS_0;
  struct
  {
    // DW1 address 24 in port cs
    UINT32 Address               : 8;
    UINT32 Length                : 8;
    UINT32 Target                : 3;
    UINT32 resCs0                : 1;
    UINT32 RetimerInex           : 4;
    UINT32 WnR                   : 1;
    UINT32 NoResponse_NR         : 1;
    UINT32 ResultCode_RC         : 1;
    UINT32 resCs0_1              : 4;
    UINT32 Pending_PND           : 1;
  } PORT_CS_1;
  // DW2 - 17  address 25 - 31 in port cs
  struct
  {
    UINT32 Data[16];
  } PORT_CS_2_17;
  struct
  {
    UINT32 CableUSB4Version                : 8;
    UINT32 BondingEnabled_BE               : 1;
    UINT32 TBT3CompatiableMode_TCM         : 1;
    UINT32 LinkCLxSupport_LCL              : 1;
    UINT32 RS_FECEnabled_Gen2_RE2          : 1;
    UINT32 RS_FECEnabled_Gen3_RE3          : 1;
    UINT32 LinkInitializationInProgress_LIP: 1;
    UINT32 resCs18                         : 2;
    UINT32 WakeonConnectStatus             : 1;
    UINT32 WakeonDisconnectStatus          : 1;
    UINT32 WakeonUSB4WakeStatus            : 1;
    UINT32 WakeonInterDomainStatus         : 1;
    UINT32 resCs18_01                      :12;
  } PORT_CS_18;
  struct
  {
    UINT32 DownstreamPortReset_DPR         : 1;
    UINT32 RequestRS_FECGen2_RS2           : 1;
    UINT32 RequestRS_FECGen3_RS3           : 1;
    UINT32 USB4PortIsConfigured            : 1;
    UINT32 USB4PortIsInterDomain_PID       : 1;
    UINT32 resCs19                         :11;
    UINT32 EnableWakeOnConnect             : 1;
    UINT32 EnableWakeOnDisconnect          : 1;
    UINT32 EnableWakeOnUsb4Wake            : 1;
    UINT32 EnableWakeOnInterdomain         : 1;
    UINT32 resCs19_1                       :12;
  } PORT_CS_19;
} usb4_usb4_port_cs;

typedef struct
{
  //    struct
  //    {
  //        UINT32 resCs0;
  //    } ADP_CS_0;
  struct
  {
    UINT32 NextCapabilityPointer            : 8;
    UINT32 MaxCounterSets                   :11;
    UINT32 CountersConfigurationSpaceFlag   : 1;
    UINT32 resCs1                           :12;
  } ADP_CS_1;
  struct
  {
    UINT32 AdapterTypeSubType               : 8;
    UINT32 AdapterTypeVersion               : 8;
    UINT32 AdapterTypeProtocol              : 8;
    UINT32 resCs2                           : 8;

  } ADP_CS_2;
  struct
  {
    UINT32 resCs3                           :20;
    UINT32 AdapterNumber                    : 6;
    UINT32 resCs3_1                         : 3;
    UINT32 HECError                         : 1;
    UINT32 FlowControlError                 : 1;
    UINT32 SharedBufferingCapable           : 1;

  } ADP_CS_3;
  struct
  {
    UINT32 NonFlowControlledBuffers         :10;
    UINT32 resCs4                           :10;
    UINT32 TotalBuffers                     :10;
    UINT32 Plugged                          : 1;
    UINT32 Lock                             : 1;

  } ADP_CS_4;
  struct
  {
    UINT32 MaxInputHopID                    :11;
    UINT32 MaxOutputHopID                   :11;
    UINT32 LinkCreditsAllocated             : 7;
    UINT32 HECErrorEnable                   : 1;
    UINT32 FlowControlErrorEnable           : 1;
    UINT32 DisableHotPlugEvents             : 1;
  } ADP_CS_5;
} usb4_adp_cs;


typedef struct
{
  struct
  {
    UINT32 nextCapabilityPointer : 8;
    UINT32 capabilityID          : 8;
    UINT32 SupportedLinkSpeeds   : 4;
    UINT32 SupportedLinkWidths   : 6;
    UINT32 CL0sSupport           : 1;
    UINT32 CL1Support            : 1;
    UINT32 CL2Support            : 1;
    UINT32 resCs0                : 3;
  } LANE_ADP_CS_0;
  struct
  {
    UINT32 TargetLinkSpeed       : 4;
    UINT32 TargetLinkWidth       : 6;
    UINT32 CL0sEnable            : 1;
    UINT32 CL1Enable             : 1;
    UINT32 CL2Enable             : 1;
    UINT32 resCs1                : 1;
    UINT32 LaneDisable_LD        : 1;
    UINT32 LaneBonding_LB        : 1;
    UINT32 CurrentLinkSpeed      : 4;
    UINT32 NegotiatedLinkWidth   : 6;
    UINT32 AdapterState          : 4;
    UINT32 PmSecondary_PMS       : 1;
    UINT32 resCs1_1              : 1;
  } LANE_ADP_CS_1;
  struct
  {
    UINT32 LogicalLayerErrors       : 7;
    UINT32 resCs2                   : 9;
    UINT32 LogicalLayerErrorsEnable : 7;
    UINT32 resCs2_1                 : 9;
  } LANE_ADP_CS_2;
} usb4_lane_adp_cs;

typedef struct
{
  struct
  {
    UINT32 ReceivedPacketsLow:32;
  } CNT_CS_0;

  struct
  {
    UINT32 ReceivedPacketsHigh:32;
  } CNT_CS_1;
  struct
  {
    UINT32 DroppedPackets:32;
  } CNT_CS_2;
} usb4_adapter_counter_set;

typedef struct
{
  struct
  {
    UINT32 VendorDefined                    : 6;
    UINT32 resCs0                           :11;
    UINT32 PathCreditsAllocated             : 7;
    UINT32 resCs0_1                         : 7;
    UINT32 VendorDefined_1                  : 1;
  } PATH0_CS_0;
  struct
  {
    UINT32 VendorDefined                    :12;
    UINT32 CounterID                        :11;
    UINT32 CounterEnable                    : 1;
    UINT32 resCs1_1                         : 8;
  } PATH0_CS_1;
} usb4_path0_cs;

typedef struct
{
  struct
  {
    UINT32 OutputHopID                      :11;
    UINT32 OutputAdapter                    : 6;
    UINT32 PathCreditsAllocated             : 7;
    UINT32 resCs0_1                         : 7;
    UINT32 Valid                            : 1;
  } PATH_CS_0;
  struct
  {
    UINT32 Weight                           : 8;
    UINT32 Priority                         : 3;
    UINT32 resCs1                           : 1;
    UINT32 CounterID                        :11;
    UINT32 CounterEnable                    : 1;
    UINT32 IngressFlowControl               : 1;
    UINT32 EgressFlowControl                : 1;
    UINT32 IngressSharedBufferingEnable     : 1;
    UINT32 EgressSharedBufferingEnable      : 1;
    UINT32 PendingPackets                   : 1;
    UINT32 resCs1_1                         : 3;
  } PATH_CS_1;
} usb4_pathN_cs;

//struct usb4_pathN_cs_ProtocolAdapter
//{
//    struct
//    {
//        UINT32 OutputHopID                      :11;
//        UINT32 OutputAdapter                    : 6;
//        UINT32 PathCreditsAllocated             : 7;
//        UINT32 resCs0_1                         : 7;
//        UINT32 Valid                            : 1;
//    } PATH0_CS_0;
//    struct
//    {
//        UINT32 Weight                           : 8;
//        UINT32 Priority                         : 3;
//        UINT32 resCs1                           : 1;
//        UINT32 CounterID                        :11;
//        UINT32 CounterEnable                    : 1;
//        UINT32 IngressFlowControl               : 1;
//        UINT32 EgressFlowControl                : 1;
//        UINT32 IngressSharedBufferingEnable     : 1;
//        UINT32 EgressSharedBufferingEnable      : 1;
//        UINT32 PendingPackets                   : 1;
//        UINT32 resCs1_1                         : 3;
//    } PATH0_CS_1;
//};

typedef struct
{
  struct
  {
    UINT32 nextCapabilityPointer :8;
    UINT32 capabilityID          :8;
    UINT32 Link                  :1;
    UINT32 TxEI                  :1;
    UINT32 RxEI                  :1;
    UINT32 Rst                   :1;
    UINT32 PathCreditsAllocated  :5;
    UINT32 LTSSM                 :4;
    UINT32 resCs0                :2;
    UINT32 PathEnable            :1;
  } ADP_PCIE_CS_0;
} usb4_adp_pcie_cs;

typedef struct
{
  struct
  {
    UINT32 nextCapabilityPointer : 8;
    UINT32 capabilityID          : 8;
    UINT32 resCs0                :14;
    UINT32 Valid                 : 1;
    UINT32 PathEnable            : 1;
  } ADP_USB_CS_0;
  struct
  {
    UINT32 ConsumedUpstreamBandwidth    :12;
    UINT32 ConsumedDownstreamBandwidth  :12;
    UINT32 resCs1                       : 7;
    UINT32 xHCIControllerACK_XCA        : 1;
  }ADP_USB_CS_1;
  struct
  {
    UINT32 AllocatedUpstreamBandwidth   :12;
    UINT32 AllocatedDownstreamBandwidth :12;
    UINT32 resCs2                       : 7;
    UINT32 ConnectionManagerRequest_CMR : 1;
  }ADP_USB_CS_2;
  struct
  {
    UINT32 Scale                        : 6;
    UINT32 resCs3                       :26;
  }ADP_USB_CS_3;
  struct
  {
    UINT32 ActualLinkRate               : 7;
    UINT32 UsbLinkValid_ULV             : 1;
    UINT32 PortLinkState_PLS            : 4;
    UINT32 MaximumSupportedLinkRate     : 7;
    UINT32 resCs4                       :13;
  }ADP_USB_CS_4;
} usb4_adp_usb3_cs;


typedef struct
{
  struct
  {
    UINT32 nextCapabilityPointer :8;
    UINT32 capabilityID          :8;
    UINT32 videoHopId            :11;
    UINT32 reserved_0            :3;
    UINT32 auxEnable             :1;
    UINT32 videoEnable           :1;
  } ADP_DP_CS_0;

  struct
  {
    UINT32 auxTxHopId            :11;
    UINT32 auxRxHopId            :11;
    UINT32 reserved_0            :10;
  } ADP_DP_CS_1;

  struct
  {
    UINT32 reserved_1            :3;
    UINT32 swli                  :1;
    UINT32 reserved_2            :2;
    UINT32 hpdStatus             :1;
    UINT32 reserved_3            :25;
  } ADP_DP_CS_2;

  struct
  {
    UINT32 reserved_1            :9;
    UINT32 hpdc                  :1;
    UINT32 hpds                  :1;
    UINT32 reserved_2            :21;
  } ADP_DP_CS_3;

  struct
  {
    UINT32 ProtocolAdapterVersion    :4;
    UINT32 MaximalDPCDRev            :4;
    UINT32 MaximalLinkRate           :4;
    UINT32 MaximalLaneCount          :3;
    UINT32 MSTCapability             :1;
    UINT32 reserved_1                :6;
    UINT32 TPS3Capability            :1;
    UINT32 reserved_2                :1;
    UINT32 TPS4Capability            :1;
    UINT32 FECNotSupported           :1;
    UINT32 SecondarySplitCapability  :1;
    UINT32 LTTPRNotSupported         :1;
    UINT32 reserved_3                :1;
    UINT32 DSCNotSupported           :1;
    UINT32 reserved_4                :2;
  } DP_LOCAL_CAP;

  struct
  {
    UINT32 ProtocolAdapterVersion    :4;
    UINT32 MaximalDPCDRev            :4;
    UINT32 MaximalLinkRate           :4;
    UINT32 MaximalLaneCount          :3;
    UINT32 MSTCapability             :1;
    UINT32 reserved_1                :6;
    UINT32 TPS3Capability            :1;
    UINT32 reserved_2                :1;
    UINT32 TPS4Capability            :1;
    UINT32 FECNotSupported              :1;
    UINT32 SecondarySplitCapability  :1;
    UINT32 LTTPRNotSupported           :1;
    UINT32 reserved_3                :1;
    UINT32 DSCNotSupported             :1;
    UINT32 reserved_4                :2;
  } DP_REMOTE_CAP;

  struct
  {
    UINT32 LaneCount                 :3;
    UINT32 reserved_1                :5;
    UINT32 LinkRate                  :4;
    UINT32 reserved_2                :5;
    UINT32 reserved_3                :15;
  } DP_STATUS;

  struct
  {
    UINT32 ProtocolAdapterVersion    :4;
    UINT32 MaximalDPCDRev            :4;
    UINT32 MaximalLinkRate           :4;
    UINT32 MaximalLaneCount          :3;
    UINT32 MSTCapability             :1;
    UINT32 reserved_1                :6;
    UINT32 TPS3Capability            :1;
    UINT32 reserved_2                :1;
    UINT32 TPS4Capability            :1;
    UINT32 FECNotSupported           :1;
    UINT32 SecondarySplitCapability  :1;
    UINT32 LTTPRNotSupported         :1;
    UINT32 reserved_3                :1;
    UINT32 DSCNotSupported           :1;
    UINT32 reserved_4                :1;
    UINT32 DPRXCapabilitiesReadDone  :1;
  } DP_COMMON_CAP;

} usb4_adp_dp_in_cs;


typedef struct
{
  struct
  {
    UINT32 nextCapabilityPointer :8;
    UINT32 capabilityID          :8;
    UINT32 videoHopId            :11;
    UINT32 reserved_0            :3;
    UINT32 auxEnable             :1;
    UINT32 videoEnable           :1;
  } ADP_DP_CS_0;

  struct
  {
    UINT32 auxTxHopId            :11;
    UINT32 auxRxHopId            :11;
    UINT32 reserved_0            :10;
  } ADP_DP_CS_1;

  struct
  {
    UINT32 reserved_1               :3;
    UINT32 swli                     :1;
    UINT32 reserved_2               :2;
    UINT32 hpdStatus                :1;
    UINT32 reserved_3               :1;
    UINT32 MaximumAccumulationCycles:16;
    UINT32 resetved_4               :8;
  } ADP_DP_CS_2;

  struct
  {
    UINT32 VendorDefined            :32;
  } ADP_DP_CS_3;

  struct
  {
    UINT32 ProtocolAdapterVersion    :4;
    UINT32 MaximalDPCDRev            :4;
    UINT32 MaximalLinkRate           :4;
    UINT32 MaximalLaneCount          :3;
    UINT32 MSTCapability             :1;
    UINT32 reserved_1                :6;
    UINT32 TPS3Capability            :1;
    UINT32 reserved_2                :1;
    UINT32 TPS4Capability            :1;
    UINT32 FECNotSupported           :1;
    UINT32 SecondarySplitCapability  :1;
    UINT32 LTTPRNotSupported         :1;
    UINT32 reserved_3                :1;
    UINT32 DSCNotSupported           :1;
    UINT32 reserved_4                :2;
  } DP_LOCAL_CAP;

  struct
  {
    /**
      0h – 2h: Reserved
3h: Reserved for TBT3
4h: Version 1.0
5h – Fh: Reserved
*/
    UINT32 ProtocolAdapterVersion    :4;
    UINT32 MaximalDPCDRev            :4;
    UINT32 MaximalLinkRate           :4;
    UINT32 MaximalLaneCount          :3;
    UINT32 MSTCapability             :1;
    UINT32 reserved_1                :6;
    UINT32 TPS3Capability            :1;
    UINT32 reserved_2                :1;
    UINT32 TPS4Capability            :1;
    UINT32 FECNotSupported           :1;
    UINT32 SecondarySplitCapability  :1;
    UINT32 LTTPRNotSupported         :1;
    UINT32 reserved_3                :1;
    UINT32 DSCNotSupported           :1;
    UINT32 reserved_4                :2;
  } DP_REMOTE_CAP;

  struct
  {
    UINT32 LaneCount                 :3;
    UINT32 reserved_1                :5;

    /**
0h: 1.62GHz
1h: 2.7GHz
2h: 5.4GHz
3h: 8.1GHz
4h – Fh: Reserved
*/ 
    UINT32 LinkRate                  :4;
    UINT32 reserved_2                :5;
    UINT32 reserved_3                :8;

    /**
      A Connection Manager uses this bit for the
      handshake defined in Section 10.4.2.1.
      */ 
    UINT32 CMHandshake_CMHS          :1;
    /**
      A Connection Manager uses this bit to indicate
      whether the DP IN Adapter is a USB4 DP IN Adapter
      or a TBT3 DP IN Adapter.
0: TBT3
1: USB4
*/
    UINT32 DPInAdapterUSB4Flag_UF    :1;
    UINT32 reserved_4                :5;
  } DP_STATUS_CTRL;

  struct
  {
    UINT32 ProtocolAdapterVersion    :4;
    UINT32 MaximalDPCDREv            :4;
    UINT32 MaximalLinkRate           :4;
    UINT32 MaximalLaneCount          :3;
    UINT32 MSTCapability             :1;
    UINT32 reserved_1                :6;
    UINT32 TPS3Capability            :1;
    UINT32 reserved_2                :1;
    UINT32 TPS4Capability            :1;
    UINT32 FECNotSupported           :1;
    UINT32 SecondarySplitCapability  :1;
    UINT32 LTTPRNotSupported         :1;
    UINT32 reserved_3                :1;
    UINT32 DSCNotSupported           :1;
    UINT32 reserved_4                :2;
  } DP_COMMON_CAP;

  struct 
  {
    UINT32 reserved_1                :32;
  }ADP_DP_CS_8;
} usb4_adp_dp_out_cs;

#pragma pack(pop)

typedef enum
{
  USB4_HPE_NO_ACTION = 0,
  USB4_HPE_IN,
  USB4_HPE_OUT
} USB4_HPE_parsed;

typedef enum
{
  USB4_SINGLE_LANE_CL0 = 0,
  USB4_L1_IN_CL0,
  USB4_HOTPLUG_ENUMERATE_NEW_ROUTER,
  USB4_HOTPLUG_DISABLE_LANE1,
  USB4_HOTPLUG_BOND_LANES,
  USB4_HOTPLUG_CHECK_LANES_BONDED,
  USB4_HOTPLUG_BUILD_PATHS,
  USB4_HOTPLUG_DOWNSTREAM_PORT_RESET,
  USB4_HOTPLUG_INTDOM_HANDLE_ERR_ENUM,
  USB4_HOTPLUG_INTDOM_PROCESS_UUIDS,
  USB4_HOTPLUG_INTDOM_CHECK_X2_SUPPORT,
  USB4_HOTPLUG_INTDOM_SLAVE,
  USB4_HOTPLUG_INTDOM_MASTER,
  USB4_HOTPLUG_INTDOM_MASTER_BOND,
  USB4_L0_IN_CLd,
} USB4_hotplug_state;

typedef struct USB4_hotplug_struct
{
  UINT32 retries;
  UINT64 router_topologyID;
  UINT32 router_index;
  UINT64 next_router_topologyID; /* Generated from router_topologyID and adapter_first */
  UINT32 next_router_index;
  //UINT32 router_index;
  UINT32 adapter_first;
  UINT32 adapter_second;
  USB4_HPE_parsed adapter_first_action;
  USB4_HPE_parsed adapter_second_action;
  BOOLEAN record_was_updated;
  UINT32 modifiedAdapter;
  USB4_hotplug_state hotplug_state;
  struct USB4_hotplug_struct* pLane0Hotplug;
} USB4_hotplug_t;

#define USB4_PACKET_PENDING_TIMEOUT_USEC (100000)
#define USB4_T_TEARDOWN_USEC (2)
#define USB4_INVALID_FREE_BUFFERS_VALUE (0xDEADBEEF)

typedef struct
{
  BOOLEAN m_bIsSubordinate;
  BOOLEAN m_bUnsupportedUdapter;
  usb4_ctrl_iface_ctx_t* m_pControl;

  /* Configuration space info */
  UINT32 m_referenceCountIngressSharedFlowControl;
  UINT32 m_freeBuffers;

  USB4_adapter_tmu_capability m_adapterTmuCapability;
  UINT64 m_topologyID;
  usb4_adp_cs m_cs;
  UINT32 m_Number; /**< Index in the array of ports,
                     should be equal to the port number
                     in the configuration space */
  UINT32 m_OtherLaneGroupNumber; /**< Port number of the second lane in the group */

  /* Work in progress */
  USB4_hotplug_t m_hotplug;

  BOOLEAN m_bIsBound; /**< USB4 Port is a 2 lane bound group */
  BOOLEAN m_bIsDisabled; /**< Is set only if the lane was explicitly disabled */
  BOOLEAN m_bIsLoop; /**< Port leads to a loop in the topology */
  BOOLEAN m_bIsInterdomain; /**< Port leads to a different domain */
  BOOLEAN m_bIsSegmenEnabled; /**< Adapter port segment has been enabled */
} usb4_port_ctx_t;


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

/**
 * @brief Return current value of free buffers
 * This function prevents inadvertent change of the value from other layers
 * @return number of free buffers
 */
UINT32 Usb4PortGetFreeBuffers(usb4_port_ctx_t* usb4_port_ctx);

/**
 * @brief Read through port configuration space capabilities and until an ID matches
 * a requested capability. Read a single DWORD only
 * @param[in] capIdRequested - ID of the requested capability
 * @param[in] pCapLength - Length of the found capability
 * @return 0 on success other on failure
 */
int Usb4PortSearchCapability(usb4_port_ctx_t* usb4_port_ctx, UINT8 capIdRequested, UINT32* pCapLength);

/**
 * @brief Read a complete capability once SearchCapability() succeeded (mandatory)
 * @param[out] pBuff - Buffer to read the capability into (at least one dword)
 * @param[in] capSize - Buffer size
 * @return 0 on success other on failure
 */
int Usb4PortReadCapability(usb4_port_ctx_t* usb4_port_ctx, UINT8* pBuff, UINT32 capSize);

/**
 * @brief Read a complete capability once SearchCapability() succeeded (mandatory)
 * @param[out] pBuff - Buffer to read the capability into (at least one dword)
 * @param[in] dwordIndex - index of DWORD in the capability, starting with 0
 * @return 0 on success other on failure
 */
int Usb4PortReadCapabilityDword(usb4_port_ctx_t* usb4_port_ctx, UINT8* pBuff, UINT32 dwordIndex);

/**
 * @brief Write capability to the same address as the one used in a previous read command
 * @param[in] pBuff - Buffer to write
 * @param[in] write_len - buffer length
 * @return 0 on success other on failure
 */
int Usb4PortWriteCapability(usb4_port_ctx_t* usb4_port_ctx, UINT8* pBuff, UINT32 write_len);

/**
 * @brief Write capability DWORD to the same address (with offset) as the one used in a previous read command
 * @param[in] pBuff - Buffer to write
 * @param[in] dwordIndex - index of DWORD in the capability, starting with 0
 * @return 0 on success other on failure
 */
int Usb4PortWriteCapabilityDword(usb4_port_ctx_t* usb4_port_ctx, UINT8* pBuff, UINT32 dwordIndex);


/**
 * @brief This function returns port name in human readable format
 * @return string
 */
char const* Usb4PortGetName(usb4_port_ctx_t* usb4_port_ctx);

/**
 * @brief This function initializes object members
 * @param [in] pControl - pointer to the control port interface
 * @param [in] number - index of the port in the array of ports
 * @return 0 on success other on failure
 */
int Usb4PortInit(usb4_port_ctx_t* usb4_port_ctx, usb4_ctrl_iface_ctx_t* pControl, UINT32 number);

/**
 * @brief This function sets to topology Id of the parent router
 *        Function assumes a valid topology id (no check)
 * @param [in] topologyId - router topology ID
 * @return 0 on success other on failure
 */
int Usb4PortSetTopologyId(usb4_port_ctx_t* usb4_port_ctx, UINT64 topologyId);

/**
 * @brief This function returns a port type of the current object
 * @return Port Type
 */
USB4_portType Usb4PortGetPortType(usb4_port_ctx_t* usb4_port_ctx);

/**
 * @brief This function returns a port state
 * @param[out] portState - Port State
 * @return 0 on success other on failure
 */
int Usb4PortGetPortState(usb4_port_ctx_t* usb4_port_ctx, USB4_portState* portState);

/**
 * @brief Read Lane configuration space
 * @param[out] lane_adp_cs - Configuration space
 * @return 0 on success other on failure
 */
int Usb4PortReadLaneAdpCS(usb4_port_ctx_t* usb4_port_ctx, usb4_lane_adp_cs* lane_adp_cs);

/**
 * @brief Read Lane configuration space
 * @param[in] lane_adp_cs - Configuration space
 * @return 0 on success other on failure
 */
int Usb4PortWriteLaneAdpCS(usb4_port_ctx_t* usb4_port_ctx, usb4_lane_adp_cs* lane_adp_cs);


/**
 * @brief Read Lane configuration space
 * @param[out] dualLaneSupported - TRUE is Dual Lane is supported
 * @return 0 on success other on failure
 */
int Usb4PortIsDualLaneSupported(usb4_port_ctx_t* usb4_port_ctx, BOOLEAN* dualLaneSupported);

/**
 * @brief Configure lane to establish a dual lane connection
 * @return 0 on success other on failure
 */
int Usb4PortConfigureDualLane(usb4_port_ctx_t* usb4_port_ctx);

/**
 * @brief This marks port as a subordinate
 * @return 0 on success other on failure
 */
int Usb4PortSetSubordinate(usb4_port_ctx_t* usb4_port_ctx);

/**
 * @brief Read USB4 configuration space
 * @param[out] dualLaneSupported - TRUE is Bonding Enabled bit is set
 * @return 0 on success other on failure
 */
int Usb4PortIsBondingEnabled(usb4_port_ctx_t* usb4_port_ctx, BOOLEAN* bondingEnabled);

/**
 * @brief Bond primary and secondary lanes. Call this
 * on primary lane adapter only
 * @return 0 on success other on failure
 */
int Usb4PortBondLanes(usb4_port_ctx_t* usb4_port_ctx);

/**
 * @brief Get current link width
 * @param[out] linkWidth - Negotiated link width
 * @return 0 on success other on failure
 */
int Usb4PortGetNegotiatedLinkWidth(usb4_port_ctx_t* usb4_port_ctx, UINT32* linkWidth);

/**
 * @brief Disable USB4 Lane
 * @return 0 on success other on failure
 */
int Usb4PortLaneDisable(usb4_port_ctx_t* usb4_port_ctx);

/**
 * @brief Enable USB4 Lane (if disabled)
 * @return 0 on success other on failure
 */
int Usb4PortLaneEnable(usb4_port_ctx_t* usb4_port_ctx);


/**
 * @brief Set/Clear Reset USB4 Port
 * @param[in] set - Set or Clear the reset bit
 * @return 0 on success other on failure
 */
int Usb4PortPortReset(usb4_port_ctx_t* usb4_port_ctx, UINT32 set);

/**
 * @brief Read port configuration space and update it's members
 * @return 0 on success other on failure
 */
int Usb4PortReadCS(usb4_port_ctx_t* usb4_port_ctx);

/**
 * @brief Read port configuration space and update it's members
 *
 * @return 0 on success other on failure
 */
int Usb4PortReadCSDword(usb4_port_ctx_t* usb4_port_ctx, UINT32 start_dword, UINT32 number_of_dwords);

/**
 * @brief Write port configuration space
 * @return 0 on success other on failure
 */
int Usb4PortWriteCS(usb4_port_ctx_t* usb4_port_ctx);

/**
 * @brief Unlock DFP
 * @return 0 on success other on failure
 */
int Usb4PortUnlock(usb4_port_ctx_t* usb4_port_ctx);

/**
 * @brief Poll for a specific lock state. May hung forever
 * @param[in] lock - Desired lock state
 * @return 0 on success other on failure
 */
int Usb4PortPollForLockState(usb4_port_ctx_t* usb4_port_ctx, UINT32 lock);

/**
 * @brief Poll for Packet pending by HOPID and Path type
 * @param[in] HopID - Entry to the routing table
 * @return 0 on success other on failure
 */
int Usb4PortPollforPP(usb4_port_ctx_t* usb4_port_ctx, UINT32 HopID);

/**
 * @brief Configure port as an interdomain port
 * @param[in] isInterdomain - flag describing the current status of the port
 * @return 0 on success other on failure
 */
int Usb4PortSetInterdomain(usb4_port_ctx_t* usb4_port_ctx, BOOLEAN isInterdomain);

/**
 * @brief Set Enable bit in the adapter configuration space.
 * @param[in] enable - Enable/Disable segment
 * @return 0 on success other on failure
 */
int Usb4PortEnableSegment(usb4_port_ctx_t* usb4_port_ctx, BOOLEAN enable);

/**
 * @brief Clear the valid bit of the path CS, and wait for
 * pending bit to clear or for timeout
 * @param[in] HopID - Entry to the routing table. If 0, use adapter
 * port specific single entry
 * @return 0 on success other on failure
 */
int Usb4PortInvalidateSegment(usb4_port_ctx_t* usb4_port_ctx, UINT32 HopID);

/**
 * @brief Return index to the entry into the routing table of adapter port
 * @param[out] hopID - ingress hop ID
 * @param[in] bIsAux - Specifies if this is an AUX path of the display port
 * @return 0 on success other on failure
 */
int Usb4PortGetAdapterHopID(usb4_port_ctx_t* usb4_port_ctx, UINT32 *hopID, BOOLEAN bIsAux);

/**
 * @brief Return index to the free entry into the routing table
 * @param[out] hopID - ingress hop ID
 * @return 0 on success other on failure
 */
int Usb4PortGetFreeHopID(usb4_port_ctx_t* usb4_port_ctx, UINT32 *hopID);

/**
 * @brief Read path CS data
 * @param[in] HopID - Entry to the routing table
 * @param[out] path - path CS data
 * @return 0 on success other on failure
 */
int Usb4PortReadSegment(usb4_port_ctx_t* usb4_port_ctx, UINT32 HopID, usb4_pathN_cs* path);

/**
 * @brief Write path CS data, and update count of free buffers, if shared flow control is enabled
 * @param[in] HopID - Entry to the routing table
 * @param[in] path - path CS data
 * @return 0 on success other on failure
 */
int Usb4PortWriteSegment(usb4_port_ctx_t* usb4_port_ctx, UINT32 HopID, usb4_pathN_cs* path);

/**
 * @brief Write usb4_adp_cs with new value, and update the number of free buffers for this port
 * @param[in] linkCreditsAllocated - Number of link credits to assign to shared buffer
 * @return 0 on success other on failure
 */
int Usb4PortUpdateLinkCreditsAllocated(usb4_port_ctx_t* usb4_port_ctx, UINT32 linkCreditsAllocated);

/**
 * @brief issueing a port operation according to the operation sent
 * @param operation to execute  
 * @return 0 on success other on failure
 */
int Usb4PortIssuePortOperation(usb4_port_ctx_t* usb4_port_ctx, USB4_port_operation* operationData);

/**
  * @brief request part of port operation according to the operation sent
  * @param operation to execute
  * @param target local/remote
  * @return 0 on success other on failure
  */
int Usb4PortPortOperationRequest(usb4_port_ctx_t* usb4_port_ctx, USB4_port_operation* operationData, USB4_sb_target target);

/**
  * @brief completion part of port operation according to the operation sent
  * @param operation to execute
  * @param target local/remote
  * @return 0 on success other on failure
  */
int Usb4PortPortOperationCompletion(usb4_port_ctx_t* usb4_port_ctx, USB4_port_operation* operationData, USB4_sb_target target);

/**
 * @brief writing transfer ditails to port capability
 * @param transfer ditails  
 * @return 0 on success other on failure
 */
int Usb4PortOperationSbCs(usb4_port_ctx_t* usb4_port_ctx, USB4_portSbAccesses* trnasDitails);

/**
 * @brief Write "DHP" bit into adapter configuration space
 * @param Value of the bit to write
 * @return 0 on success other on failure
 */
int Usb4PortDisableHotPlugNotification(usb4_port_ctx_t* usb4_port_ctx, BOOLEAN bDisable);

/**
 * @brief Update member variable depicting a number of total buffers
 * This is needed sonce the number of total buffers assigned to the port may change
 * after lanes bonding.
 * @return 0 on success other on failure
 */
int Usb4PortUpdateTotalBuffers(usb4_port_ctx_t* usb4_port_ctx);

/**
 * @brief Configure hot plug notification generation
 * @param[in] bEnable - ....
 * @return 0 on success other on failure
 */
int Usb4PortConfigureDHP(usb4_port_ctx_t* usb4_port_ctx, BOOLEAN bEnable);

/**
 * @brief Disable/Enable time sync on the port
 * @param[in] bEnable - Enable/Disable of time sync
 * @return 0 on success other on failure
 */
int Usb4PortTmuTimeSync(usb4_port_ctx_t* usb4_port_ctx, BOOLEAN bEnable);

/**
 * @brief Set unidirectional/bidirectional mode
 * @param[in] bUniDir - ....
 * @return 0 on success other on failure
 */
int Usb4PortTmuUniDirectionalMode(usb4_port_ctx_t* usb4_port_ctx, BOOLEAN bUniDir);

/**
 * @brief configures the port as interdomain master
 * @return 0 on success other on failure
 */
int Usb4PortTMUSetInterdomainMaster(usb4_port_ctx_t* usb4_port_ctx);

/**
 * @brief configures the port as interdomain slave
 * @return 0 on success other on failure
 */
int Usb4PortTMUSetInterdomainSlave(usb4_port_ctx_t* usb4_port_ctx);

/**
 * @brief gets the counter set specified by id
 * @param setId counter set id
 * @param pCounterSet pointer to the counter set to get 
 * @return 0 on success other on failure
 */
int Usb4PortGetCounterSet(usb4_port_ctx_t* usb4_port_ctx, UINT32 setId, usb4_adapter_counter_set *pCounterSet);

/**
 * @brief gets the counter set specified by id
 * @param setId counter set id
 * @return 0 on success other on failure
 */
int Usb4PortClearCounterSet(usb4_port_ctx_t* usb4_port_ctx, UINT32 setId);

#endif /* __USB4_PORT_H_ */
