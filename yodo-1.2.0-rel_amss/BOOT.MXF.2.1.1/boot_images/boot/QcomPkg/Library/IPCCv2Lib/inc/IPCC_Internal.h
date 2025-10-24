#ifndef __IPCC_INTERNAL_H__
#define __IPCC_INTERNAL_H__
/*
===========================================================================
*/
/**
  @file IPCC_Internal.h
  @brief Private interface include file for accessing the IPCC internal
  device driver definitions.

  The IPCCInternal.h file is the private API interface to the Inter-Processor 
  Communication Controller driver.
*/
/*
  ===========================================================================

  Copyright (c) 2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

  ===========================================================================

  $Header: //components/dev/core.boot/6.1/shantonu.core.boot.6.1.ipccHwMemOpt_uefi/QcomPkg/Library/IPCCLib/inc/IPCC_Internal.h#1 $
  $DateTime: 2022/06/08 16:30:11 $
  $Author: shantonu $

  ===========================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "IPCC.h"
#include "IPCC_OS.h"


/*=========================================================================
      Type Definitions
==========================================================================*/

#define IPCC_GET_CID(x) (((x)>>16)&0xffff)
#define IPCC_GET_SID(x) ((x)&0xffff)
#define IPCC_SET_CID(x) (((x)&0xffff)<<16)
#define IPCC_SET_SID(x) ((x)&0xffff)

/*=========================================================================
      Type Definitions
==========================================================================*/

/**
 * Signifies no interrupt assignment
 */
#define IPCC_INT_NONE ((uint16_t)-1)

/**
 * IPCC Rx edge info
 */
typedef struct _IPCCRxDataType
{
  IPCC_Signal             nSignalLow;
  IPCC_Signal             nSignalHigh;
  IPCC_CB                 pfnCb;
  IPCC_CBData             nArg;
  bool                    bIsland;
  struct _IPCCRxDataType* pNext;
}
IPCCRxDataType;

/**
 * IPCC Client config data
 */
typedef struct
{
  IPCCRxDataType* pList;
  #ifdef IPCC_SUPPORT_LEGACY_MODE
  bool            bUseLegacyByDefault;
  #endif
  #ifdef IPCC_HWMEMOPT
  IPCC_Client     eClient;
  #endif

} IPCCClientType;

/** 
 * IPCC Protocol config definition 
 */
typedef struct
{
  uint16_t        nProtocolId;
  uint16_t        nNumSigs;
  uint8_t         nNumClients;
  uint16_t        nInterrupt;
  uintptr_t       nPhysBaseAddress;
  uintptr_t       nVirtBaseAddress;
  IPCCClientType *pClients;
  #ifdef IPCC_SUPPORT_LEGACY_MODE
  uint8_t         bLegacySupported;
  uint8_t         bIPCCModeSupported;
  #endif
  #ifdef IPCC_CLEAR_ON_RECV_FEATURE
  uint8_t         bClearOnRecvEn;
  #endif
  #ifdef IPCC_DIRECT_MAPPING_FEATURE
  uint8_t         bDirectMapping;
  #endif

} IPCCProtocolType;

/**
 * IPCC Tx Common Driver Info
 */
typedef struct
{
  IPCC_Protocol          eProtocol;
  uint32_t               nRefs;
}
IPCCTxDrvInfoType;


/**
 * IPCC Tx Common Driver Info
 */
typedef struct
{
  IPCCTxDrvInfoType         TxProtocolDrv[IPCC_P_TOTAL];
  uint32_t                  nRefs;
}
IPCCTxDrvType;

/**
 * IPCC Rx Common Driver Info
 */
typedef struct
{
  IPCC_Protocol          eProtocol;
  IPCCOSMutex            sMutex;
  IPCCOSInterruptHandle  hInterruptHandle;
  uint32_t               nRefs;
}
IPCCRxDrvInfoType;

/**
 * IPCC Rx Common Driver Info
 */
typedef struct
{
  IPCCRxDrvInfoType         RxProtocolDrv[IPCC_P_TOTAL];
  uint32_t                  nRefs;
}
IPCCRxDrvType;


/** 
  * Definition of Legacy Register Type
  */
typedef struct
{
  uintptr_t           nBaseAddress;
  uint32_t            nOffset;
}
IPCCLegacyRegisterType;

/**
 * Definition for Legacy data type
 */
typedef struct
{
  IPCC_CB     pfnCb;
  IPCC_CBData nArg;
  uint32_t    nOutMask;
  uint32_t    nInterruptId;
  bool        bIslandMode;
}
IPCCLegacyDataType;

/**
 * Definition for Legacy edge
 */
typedef struct
{
  IPCCLegacyRegisterType* pReg;
  IPCCLegacyDataType*     pLegacyData;
  uint32_t                nCount;
}
IPCCLegacyType;

/**
 * Definition for Legacy BSP Data
 */
typedef struct
{
  IPCCLegacyType*         pLegacyData;
  uint32_t                nCount;
  IPCCLegacyRegisterType* pReg;
  uint32_t                nNumRegs;
}
IPCCLegacyBSPDataType;

/**
 * IPCC Legacy driver context
 */
typedef struct
{
  IPCCLegacyBSPDataType* pLegacyBSP;
  IPCCOSInterruptHandle  hInterruptHandle;
  uint32_t               nRefs;
}
IPCCLegacyDrvCtxt;


/**
 * Top Level IPCC Config Type
 */
typedef struct
{
  IPCCProtocolType *pProtocols;
  uint32_t          nNumProtocols;
  IPCC_Client       eClient;
  #ifdef IPCC_NO_TME
  uint8_t           bIPCCMode;
  #endif
}
IPCCBSPDataType;

/**
 * IPCC Driver context
 */
typedef struct
{
  IPCCBSPDataType*   pBSP;
  IPCCRxDrvType*     pRxDrv;
  IPCCTxDrvType*     pTxDrv;
  IPCCLegacyDrvCtxt* pLegacyDrv;
}
IPCCDrvCtxt;

/**
 * IPCC Client context definition
 */
typedef struct
{
  IPCCProtocolType*   pProtocol;
  IPCCRxDrvInfoType*  pRxDrv;
  IPCCTxDrvInfoType*  pTxDrv;
  IPCCLegacyDrvCtxt*  pLegacyDrv;
}
IPCCClientCtxt;

/*==============================================================================
  Prototypes
==============================================================================*/

#ifdef IPCC_SUPPORT_EXTENDED_APIS
/* =============================================================================
**  Function : IPCCInternal_ToggleInterrupt
** ===========================================================================*/
/**
  Enables or disable the input interrupt(s).

  @param[in]  pClientCtxt  Pointer to client context
  @param[in]  eCID         IPCC client ID of the source
  @param[in]  nSignalLow   Lowest signal number to toggle
  @param[in]  nSignalHigh  Highest signal number to toggle
  @param[in]  bEnable      Flag to indicate enable/disable request

  @return
  IPCC_EOK -- Successfully toggled the interrupt.
  IPCC_EARG -- Invalid argument(s) passed by client.

  @dependencies
  None.
*/

static IPCCErr IPCCInternal_ToggleInterrupt
(
  IPCCClientCtxt *pClientCtxt,
  IPCC_Client     eCID,
  IPCC_Signal     nSignalLow,
  IPCC_Signal     nSignalHigh,
  bool            bEnable
);
#endif /* IPCC_SUPPORT_EXTENDED_APIS */

/* =============================================================================
**  Function : IPCCInternal_FindPhysClientIdx
** ===========================================================================*/
/**
  Internal function to find the array index of a virtual client in the protocol
  client list. Caller **must** check for error return code.

  @param[in]  eVirtClient     Virtual client ID
  @param[in]  pProtocol       Pointer to protocol data
  @param[out] pnPhysClientIdx Pointer to fill up client array index

  @return
  IPCC_EOK -- Index found successfully
  IPCC_EARG -- Invalid argument
  IPCC_ENOTSUPPORTED -- Virtual client is not a participant in the protocol

  @dependencies
  None.
*/

IPCCErr IPCCInternal_FindPhysClientIdx
(
  IPCC_Client       eVirtClient,
  IPCCProtocolType *pProtocol,
  uint32_t         *pnPhysClientIdx
);

#endif /* __IPCC_INTERNAL_H__ */
