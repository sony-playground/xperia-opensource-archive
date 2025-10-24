/*
================================================================================
*/
/**
  @file IPCCBSP.c

  Image specific config file for the IPCC driver.
*/
/*
  ==============================================================================

  Copyright (c) 2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

  ==============================================================================

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Kailua/Library/IPCCTargetLib/IPCCBSP.c#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $

  ==============================================================================
*/

/*==============================================================================
  Includes
==============================================================================*/

#include "IPCC_Internal.h"


/*==============================================================================
  Macros
==============================================================================*/

/* Clients for this target are AOP to IPA */
#define NUM_CLIENTS      (IPCC_C_IPA - IPCC_C_AOP + 1)


/*==============================================================================
  Data
==============================================================================*/

IPCCLegacyRegisterType IPCCLegacyRegister[] =
{
};

IPCCLegacyType IPCCLegacy[] =
{
};

IPCCLegacyBSPDataType IPCCLegacyBSPData =
{
  &IPCCLegacy[0],
  sizeof(IPCCLegacy)/sizeof(IPCCLegacyType),
  &IPCCLegacyRegister[0],
  sizeof(IPCCLegacyRegister)/sizeof(IPCCLegacyRegister[0])
};

IPCCClientType IPCCClient[NUM_CLIENTS];

IPCCClientType IPCCClientComputeL0[NUM_CLIENTS];

IPCCClientType IPCCClientComputeL1[NUM_CLIENTS];

IPCCClientType IPCCClientPcieMSI[NUM_CLIENTS];

IPCCProtocolType IPCCProtocols[] =
{
  {
    .nProtocolId        = IPCC_P_MPROC,
    .nNumSigs           = 4,
    .nNumClients        = NUM_CLIENTS,
    .bIsSupported       = 1,
    .nInterrupt         = 261,
    .nPhysBaseAddress   = 0x00400000,
    .nOffset            = 0x0,
    .pClients           = &IPCCClient[0],
    .bLegacySupported   = 0,
    .bIPCCModeSupported = 1,
    .bClearOnRecvEn     = 1,
  },
  {
    .nProtocolId        = IPCC_P_COMPUTEL0,
    .nNumSigs           = 32,
    .nNumClients        = NUM_CLIENTS,
    .bIsSupported       = 1,
    .nInterrupt         = 262,
    .nPhysBaseAddress   = 0x00400000,
    .nOffset            = 0x40000,
    .pClients           = &IPCCClientComputeL0[0],
    .bLegacySupported   = 0,
    .bIPCCModeSupported = 1,
    .bClearOnRecvEn     = 1,
  },
  {
    .nProtocolId        = IPCC_P_COMPUTEL1,
    .nNumSigs           = 32,
    .nNumClients        = NUM_CLIENTS,
    .bIsSupported       = 1,
    .nInterrupt         = 263,
    .nPhysBaseAddress   = 0x00400000,
    .nOffset            = 0x80000,
    .pClients           = &IPCCClientComputeL1[0],
    .bLegacySupported   = 0,
    .bIPCCModeSupported = 1,
    .bClearOnRecvEn     = 1,
  },
  {
    .nProtocolId        = IPCC_P_PCIEMSI,
    .nNumSigs           = 32,
    .nNumClients        = NUM_CLIENTS,
    .bIsSupported       = 1,
    .nInterrupt         = 746,
    .nPhysBaseAddress   = 0x00400000,
    .nOffset            = 0xC0000,
    .pClients           = &IPCCClientPcieMSI[0],
    .bLegacySupported   = 0,
    .bIPCCModeSupported = 1,
    .bClearOnRecvEn     = 1,
  },
};

IPCCBSPDataType IPCCBSPData =
{
  .pProtocols    = &IPCCProtocols[0],
  .nNumProtocols = (sizeof(IPCCProtocols)/sizeof(IPCCProtocolType)),
  .eClient       = IPCC_C_APPS,
};
