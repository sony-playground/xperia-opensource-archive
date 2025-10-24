/*===========================================================================

                    BOOT MEMORY MGR DEFINITIONS

DESCRIPTION
  Contains wrapper definition for memory mgr

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
  Copyright 2019,2022 Qualcomm Technologies, Inc. All rights reserved.

============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
05/19/22   rama    Fix error code in boot_free_DALSYS
12/16/21   rama    Added boot_malloc_uncached_DALSYS
08/02/19   ep      Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_error_if.h"
#include "boot_memory_mgr_if.h"
#include "DALSys.h"
#include "DALHeap.h"

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 


static bl_error_boot_type boot_malloc_DALSYS(uint32 dwSize, void **ppMem)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  DALResult result;

  result = DALSYS_Malloc(dwSize, (void *)ppMem);
  if((result != 0) || (ppMem == NULL))
  {
    return_status = GET_ERROR_CODE(BL_ERROR_GROUP_MEMORY_MGR, BL_ERR_MEMORY_ALLOC_FAIL);
  }

  return return_status;
}


static bl_error_boot_type boot_memalign_DALSYS(uint32 dwSize, uint32 alignment, void **ppMem)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  DALResult result;

  result = DALSYS_Memalign(dwSize, alignment, (void *)ppMem);
  if((result != 0) || (ppMem == NULL))
  {
    return_status = GET_ERROR_CODE(BL_ERROR_GROUP_MEMORY_MGR, BL_ERR_MEMORY_ALLOC_FAIL);
  }

  return return_status;
}

static bl_error_boot_type boot_malloc_uncached_DALSYS(uint32 dwSize, void **ppMem)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  DALResult result;

  result = DALSYS_MallocType(dwSize, ppMem, DALHEAP_UNCACHED);
  if((result != 0) || (ppMem == NULL))
  {
    return_status = GET_ERROR_CODE(BL_ERROR_GROUP_MEMORY_MGR, BL_ERR_MEMORY_ALLOC_FAIL);
  }

  return return_status;
}

static bl_error_boot_type boot_free_DALSYS(void *pmem)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  DALResult result;

  result = DALSYS_Free(pmem);
  if(result != 0)
  {
    return_status = GET_ERROR_CODE(BL_ERROR_GROUP_MEMORY_MGR, BL_ERR_MEMORY_DEALLOC_FAIL);
  }

  return return_status;
}



/*===========================================================================
**  Function :  boot_memory_mgr_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_memory_mgr_get_interface
*
* @par Dependencies
*   None 
* 
*/

bl_error_boot_type boot_memory_mgr_get_interface_dal(boot_memory_mgr_if_type *memory_mgr_if)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    if(memory_mgr_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_MEMORY_MGR, BL_ERR_INVALID_PARAMETER);
      break;
    }

    memory_mgr_if->malloc = boot_malloc_DALSYS;
    memory_mgr_if->memalign = boot_memalign_DALSYS;
    memory_mgr_if->free = boot_free_DALSYS;

  } while(FALSE);

  return return_status;
}


boot_memory_mgr_if_type memory_mgr_dal = 
{
  boot_malloc_DALSYS,
  boot_memalign_DALSYS,
  boot_malloc_uncached_DALSYS,
  boot_free_DALSYS
};
