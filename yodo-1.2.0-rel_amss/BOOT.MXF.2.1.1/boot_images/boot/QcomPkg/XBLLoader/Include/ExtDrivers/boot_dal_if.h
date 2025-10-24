#ifndef BOOT_DAL_IF_H
#define BOOT_DAL_IF_H
/*===========================================================================

                    BOOT DAL IF DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external dal drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright 2019 - 2020,2022 Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
07/13/22   ds      heap init with reserved align carveout
05/12/20   rhy     Added DALSYS_MallocType
08/02/19   ep      Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "DALFramework.h"
#include "DALHeap.h"

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/



typedef struct boot_dal_if_type
{

//  DALResult (*MemDescInit)(DALSYSMemHandle hMem,
//                                 DALSysMemDescList *pMemDescList,
//                                uint32 dwNumBufs);
//  DALSysMemDescBuf *(*MemDescBufPtr)(DALSysMemDescList *pMemDescList, uint32 idx);
  void (*InitMod)(DALSYSConfig *pCfg);
  void (*DeInitMod)(void);
  DALResult (*MemRegionAlloc)(uint32 dwAttribs,
                              DALSYSMemAddr VirtualAddr,
                              DALSYSMemAddr PhysicalAddr,
                              uint32 dwLen,
                              DALSYSMemHandle *phMem,
                              DALSYSMemObj *pMemObj);
  DALResult (*MemInfo)(DALSYSMemHandle hMem, DALSYSMemInfo *pMemInfo);
  DALResult (*DeviceAttach)(DALDEVICEID DeviceId, DalDeviceHandle **phDevice);
  DALResult (*DeviceAttachEx)(const char *pszArg,
                              DALDEVICEID DeviceId,
                              DALInterfaceVersion ClientVersion,
                              DalDeviceHandle **phDevice);
  DALResult (*Close)(DalDeviceHandle *hDevice);
  DALResult (*DeviceDetach)(DalDeviceHandle *hDevice);
  DALResult (*Malloc)(uint32 dwSize, void **ppMem);
  DALResult (*Memalign)(UINT32 dwSize, UINT32 alignment, VOID **ppMem);
  DALResult (*Free)(void *pmem);
  DALResult (*HeapInit)(VOID *pHeapBase, UINT32 dwHeapSz, DALHEAP_MEM_TYPE memType);
  DALResult (*HeapDeInit)(VOID *pHeapBase);
  DALResult (*HeapForceDeInit)(VOID *pHeapBase);

  DALResult (*GetDALPropertyHandle)(DALDEVICEID DeviceId, DALSYSPropertyHandle hDALProps);
  DALResult (*GetDALPropertyHandleStr)(const char *pszDevName, DALSYSPropertyHandle hDALProps);
  DALResult (*GetPropertyValue)(DALSYSPropertyHandle hDALProps, const char *pszName, uint32 dwId, DALSYSPropertyVar *pDALPropVar);
  void (*LogEvent)(DALDEVICEID DeviceId, uint32 dwLogEventType, const char * pszFmt, ...);
  UINTN (*memscpy)(VOID * pDest, UINTN iDestSz, VOID * pSrc, UINTN iSrcSize);
  VOID * (*memset)(VOID * buffer, UINT8 value, UINTN length);

  DALResult (*CacheCommand)(uint32 CacheCmd, DALSYSMemAddr VirtualAddr, uint32 dwLen);
  DALResult (*EventCreate)(uint32 dwAttribs, DALSYSEventHandle *phEvent, DALSYSEventObj *pEventObj);
  DALResult (*DestroyObject)(DALSYSObjHandle hObj);
  DALResult (*EventCtrlEx)(DALSYSEventHandle hEvent, uint32 dwCtrl, uint32 dwParam, void *pPayload, uint32 dwPayloadSize);
  DALResult (*SyncCreate)(uint32 dwAttribs, DALSYSSyncHandle *phSync, DALSYSSyncObj *pSyncObj);
  DALResult (*EventMultipleWait)(DALSYSEventHandle* phEvent, int nEvents, uint32 dwTimeoutUs, uint32 *pdwEventIdx);
  DALResult (*DALSYS_MallocType)(unsigned int dwSize, VOID **ppMem, DALHEAP_MEM_TYPE memType);
  DALResult (*HeapInit_with_reserved_aligned_carveout)(VOID *pHeapBase, UINT32 dwHeapSz, DALHEAP_MEM_TYPE memType, unsigned int alignment, unsigned int number_of_chunks);
} boot_dal_if_type;


/*===========================================================================
**  Function :  boot_dal_get_interface
** ==========================================================================
*/
/*!
*
* @brief
*   This function initializes a boot_dal_get_interface
*
* @par Dependencies
*   None
*
*/

//bl_error_boot_type boot_dal_get_interface(void *ptr);

extern boot_dal_if_type dal_if;


#endif /* BOOT_DAL_IF_H */
