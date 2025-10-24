/*
===========================================================================
*/
/**
  @file IPCCImage_Default.c

  Image specific stub config file for the IPC Controller driver.
*/
/*
  ====================================================================

  Copyright (c) 2018-2020 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/IPCCLib/image/uefi/IPCCImage_UEFI.c#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $
  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "IPCC_Image.h"
#include "HALhwio.h"
#include "IPCCHWIO.h"
#include "DDIHWIO.h"
#include "DalDevice.h"
#include "DALDeviceId.h"
#include "IPCC_OS.h"

/*=========================================================================
      Function Definitions
==========================================================================*/

void
IPCC_InitSubsysImage
(
   IPCCDrvCtxt* pDrv
)
{
  uint32_t nIdx;
  DalDeviceHandle* pHWIOHandler;
  DALResult nResult = DAL_ERROR;
  IPCCProtocolType* pProtocol;

  if ( pDrv == NULL || pDrv->pBSP == NULL ) return;

  /* Map to virtual address */
  if(DAL_DeviceAttach(DALDEVICEID_HWIO, &pHWIOHandler) == DAL_SUCCESS)
  {
    for ( nIdx = 0; nIdx < pDrv->pBSP->nNumProtocols; nIdx++ )
    {
      pProtocol = &pDrv->pBSP->pProtocols[nIdx];
      if ( pProtocol->nPhysBaseAddress != 0x0 ) 
      {
        nResult = DalHWIO_MapRegionByAddress(pHWIOHandler, (uint8_t *)pProtocol->nPhysBaseAddress,
                                             (uint8_t**)&(pProtocol->nVirtBaseAddress));
        /* Add client offset */
        if (!pProtocol->bDirectMapping)
        {
          pProtocol->nVirtBaseAddress += (pDrv->pBSP->eClient * (HWIO_ADDRXI2(0, IPC_ID, 0, 1) - HWIO_ADDRXI2(0, IPC_ID, 0, 0)));
        }

        /* Add protocol offset */
        pProtocol->nVirtBaseAddress += pProtocol->nOffset;

        /* Unable to map, use Phys = Virt */
        if ( nResult != DAL_SUCCESS )
        {
          /* Add base if it wasn't mapped */
          pProtocol->nVirtBaseAddress += pProtocol->nPhysBaseAddress;
        }
      }
    }
  }
  else
  {
    for ( nIdx = 0; nIdx < pDrv->pBSP->nNumProtocols; nIdx++ )
    {
      pProtocol = &pDrv->pBSP->pProtocols[nIdx];
      if ( pProtocol->nPhysBaseAddress != 0x0 ) 
      {
        /* Add client offset */
        if (!pProtocol->bDirectMapping)
        {
          pProtocol->nVirtBaseAddress += (pDrv->pBSP->eClient * ( HWIO_ADDRXI2(0, IPC_ID, 0, 1) - HWIO_ADDRXI2(0, IPC_ID, 0, 0) ) );
        }
        
        /* Add protocol offset and base */
        pProtocol->nVirtBaseAddress += pProtocol->nPhysBaseAddress + pProtocol->nOffset;
      }
    }

  }
}

void
IPCCLegacy_InitSubsysImage
(
   IPCCLegacyDrvCtxt* pLegacyDrv
)
{
  DalDeviceHandle *pHWIOHandler;
  uint32_t         nTableEntry;

  if ( pLegacyDrv == NULL ||
       pLegacyDrv->pLegacyBSP == NULL )
  {
    return;
  }

  /* Map to virtual address */
  if(DAL_DeviceAttach(DALDEVICEID_HWIO, &pHWIOHandler) == DAL_SUCCESS)
  {
    for ( nTableEntry = 0; nTableEntry < pLegacyDrv->pLegacyBSP->nNumRegs; nTableEntry++ ) 
    {
      if ( pLegacyDrv->pLegacyBSP->pReg[nTableEntry].nBaseAddress != 0x0 ) 
      {
        DalHWIO_MapRegionByAddress(pHWIOHandler, (uint8_t *)pLegacyDrv->pLegacyBSP->pReg[nTableEntry].nBaseAddress, 
                                      (uint8_t**)&(pLegacyDrv->pLegacyBSP->pReg[nTableEntry].nBaseAddress));
      }
    }
  }
}

