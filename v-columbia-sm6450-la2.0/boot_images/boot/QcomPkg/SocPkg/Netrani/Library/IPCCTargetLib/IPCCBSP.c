/*
===========================================================================
*/
/**
  @file IPCCBSP.c

  Image specific config file for the IPC Controller driver.
*/
/*
  ====================================================================

  Copyright (c) 2018-2021 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  $Header: //components/rel/core.boot/6.0/QcomPkg/SocPkg/Netrani/Library/IPCCTargetLib/IPCCBSP.c#2 $
  $DateTime: 2021/10/01 18:48:20 $
  $Author: pwbldsvc $
  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "IPCC_Internal.h"


/*=========================================================================
      Macros
==========================================================================*/

/*
 *  Clients for this target are AOP to TMESS
 */
#define NUM_CLIENTS      (IPCC_C_IPA - IPCC_C_AOP + 1)



/*=========================================================================
      Static definitions
==========================================================================*/

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

IPCCClientType IPCCClient[NUM_CLIENTS] = 
{
};

IPCCClientType IPCCClientComputeL0[NUM_CLIENTS];

IPCCClientType IPCCClientComputeL1[NUM_CLIENTS];

IPCCClientType IPCCClientPcieMSI[NUM_CLIENTS];


IPCCProtocolType IPCCProtocols[] =
{
  {
    .nProtocolId = IPCC_P_MPROC,
    .nNumSigs = 4,
    .nNumClients = NUM_CLIENTS,
    .nInterrupt = 261,
    .nPhysBaseAddress = 0x0ED10000,
    .nOffset = 0x0,
    .pClients = &IPCCClient[0],
    .bLegacySupported = 1,
    .bIPCCModeSupported = 1,
  },
  {
    .nProtocolId = IPCC_P_COMPUTEL0,
    .nNumSigs = 32,
    .nNumClients = NUM_CLIENTS,
    .nInterrupt = 262,
    .nPhysBaseAddress = 0x00400000,
    .nOffset = 0x0,
    .pClients = &IPCCClientComputeL0[0],
    .bLegacySupported = 0,
    .bIPCCModeSupported = 1,
  },
  {
    .nProtocolId = IPCC_P_COMPUTEL1,
    .nNumSigs = 32,
    .nNumClients = NUM_CLIENTS,
    .nInterrupt = 263,
    .nPhysBaseAddress = 0x00400000,
    .nOffset = 0x40000,
    .pClients = &IPCCClientComputeL1[0],
    .bLegacySupported = 0,
    .bIPCCModeSupported = 1,
  },
  {
    .nProtocolId = IPCC_P_PCIEMSI,
    .nNumSigs = 32,
    .nNumClients = NUM_CLIENTS,
    .nInterrupt = 746,
    .nPhysBaseAddress = 0x00400000,
    .nOffset = 0x80000,
    .pClients = &IPCCClientPcieMSI[0],
    .bLegacySupported = 0,
    .bIPCCModeSupported = 1,
  },
};

IPCCBSPDataType IPCCBSPData =
{
  .pProtocols = &IPCCProtocols[0],
  .nNumProtocols = (sizeof(IPCCProtocols)/sizeof(IPCCProtocolType)),
  .eClient = IPCC_C_APPS,
};