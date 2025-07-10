#ifndef __IPCC_INTERNAL_H__
#define __IPCC_INTERNAL_H__
/*
===========================================================================
*/
/**
  @file IPCCInternal.h
  @brief Private interface include file for accessing the IPCC internal
  device driver definitions.

  The IPCCInternal.h file is the private API interface to the Inter-Processor 
  Communication Controller driver.
*/
/*
  ===========================================================================

  Copyright (c) 2018-2020 Qualcomm Technologies Incorporated.  
  All Rights Reserved.
  Qualcomm Proprietary and Confidential.

  ===========================================================================

  $Header: //components/rel/core.boot/6.0/QcomPkg/Library/IPCCLib/inc/IPCC_Internal.h#2 $
  $DateTime: 2020/12/09 19:33:30 $
  $Author: pwbldsvc $

  when       who     what, where, why
  --------   ---     ---------------------------------------------------------- 
  05/18/18   cp      Initial revision.

  ===========================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "IPCC.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
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
  bool            bUseLegacyByDefault;
}
IPCCClientType;

/** 
 * IPCC Protocol config definition 
 */
typedef struct
{
  uint16_t        nProtocolId;
  uint16_t        nNumSigs;
  uint8_t         nNumClients;
  uint8_t         bIsIslandInterrupt;
  uint16_t        nInterrupt;
  uintptr_t       nPhysBaseAddress;
  uintptr_t       nVirtBaseAddress;
  uintptr_t       nOffset;
  IPCCClientType* pClients;
  uint8_t         bLegacySupported;
  uint8_t         bIPCCModeSupported;
  uint8_t         bClearOnRecvEn;
  uint8_t         bDirectMapping;
}
IPCCProtocolType;

/**
 * IPCC Tx Common Driver Info
 */
typedef struct
{
  IPCC_Protocol          eProtocol;
  IPCC_Client            eClient;
  uint32_t               nRefs;
}
IPCCTxDrvInfoType;


/**
 * IPCC Tx Common Driver Info
 */
typedef struct
{
  IPCCTxDrvInfoType         TxProtocolDrv[IPCC_P_TOTAL];
  IPCC_Client               eClient;
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
  IPCC_Client               eClient;
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
}
IPCCLegacyDataType;

/**
 * Definition for Legacy edge
 */
typedef struct
{
  IPCCLegacyRegisterType* pReg;
  IPCCLegacyDataType*     pLegacyData;
  bool                    bIslandMode;
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
  IPCCProtocolType* pProtocols;
  uint32_t          nNumProtocols;
  IPCC_Client       eClient;
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

#endif /*__IPCC_INTERNAL_H__*/
