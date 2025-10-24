/*===========================================================================

                    BOOT EXTERN DAL DRIVER DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external dal drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

  Copyright 2019-2020,2022 Qualcomm Technologies, Inc. All rights reserved.

============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
07/13/22   ds      heap init with reserved align carveout
08/02/19   ep      Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_error_if.h"
#include "boot_dal_if.h"
#include "DALHeap.h"
#include "DALSys.h"
#include "DalDevice.h"

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 


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
/*
bl_error_boot_type boot_dal_get_interface(void *ptr)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    boot_dal_if_type *dal_if = (boot_dal_if_type *)ptr;
    if(dal_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_DAL, BL_ERR_INVALID_PARAMETER);
      break;
    }
  
    dal_if->InitMod = DALSYS_InitMod;
    dal_if->DeInitMod = DALSYS_DeInitMod;
    dal_if->MemRegionAlloc = DALSYS_MemRegionAlloc;
    dal_if->MemInfo = DALSYS_MemInfo;
    dal_if->DeviceAttach = DAL_DeviceAttach;
    dal_if->DeviceAttachEx = DAL_DeviceAttachEx;
    dal_if->Close = DalDevice_Close;
    dal_if->DeviceDetach = DAL_DeviceDetach;
    dal_if->Malloc = DALSYS_Malloc;
    dal_if->Memalign = DALSYS_Memalign;
    dal_if->Free = DALSYS_Free;
    dal_if->HeapInit = DALSYS_HeapInit;
    dal_if->HeapDeInit = DALSYS_HeapDeInit;
    dal_if->HeapForceDeInit = DALSYS_HeapForceDeInit;

  } while(FALSE);

  return return_status;
}
*/

DALResult Boot_DALSYS_HeapInit(VOID *pHeapBase, UINT32 dwHeapSz, DALHEAP_MEM_TYPE memType)
{
  return DALSYS_HeapInit(pHeapBase, dwHeapSz, memType, 0, 0);
}

DALResult Boot_DALSYS_HeapInit_With_Aligned_Carveout(VOID *pHeapBase, UINT32 dwHeapSz, DALHEAP_MEM_TYPE memType, unsigned int alignment, unsigned int number_of_chunks)
{
  return DALSYS_HeapInit(pHeapBase, dwHeapSz, memType, alignment, number_of_chunks);
}

boot_dal_if_type dal_if = {
    DALSYS_InitMod,
    DALSYS_DeInitMod,
    DALSYS_MemRegionAlloc,
    DALSYS_MemInfo,
    DAL_DeviceAttach,
    DAL_DeviceAttachEx,
    DalDevice_Close,
    DAL_DeviceDetach,
    DALSYS_Malloc,
    DALSYS_Memalign,
    DALSYS_Free,
    Boot_DALSYS_HeapInit,
    DALSYS_HeapDeInit,
    DALSYS_HeapForceDeInit,
 
    DALSYS_GetDALPropertyHandle,
    DALSYS_GetDALPropertyHandleStr,
    DALSYS_GetPropertyValue,
    DALSYS_LogEvent,
    NULL,
    NULL,
    DALSYS_CacheCommand,
    DALSYS_EventCreate,
    DALSYS_DestroyObject,
    DALSYS_EventCtrlEx,
    DALSYS_SyncCreate,
    DALSYS_EventMultipleWait,
    DALSYS_MallocType,
    Boot_DALSYS_HeapInit_With_Aligned_Carveout
};
