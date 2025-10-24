/**
  @file bamosal.c
  @brief
  This file contains implementation of interfaces that provide a thin 
  abstraction to various OS-specific APIs used by the BAM driver.
  
*/
/*
===============================================================================

                             Edit History


when       who     what, where, why
--------   ---     ------------------------------------------------------------
07/26/22   VC      Added BAM device initialize config functions (bam_osal_init & bam_osal_deinit)
03/17/14   RL      Support for 64bit
04/12/12   NK      New funciton for destroying mutexes
11/27/11   RL      DAL free bam
03/31/11   MK      Created

===============================================================================
                   Copyright (c) 2011-2016, 2022 QUALCOMM Technologies Incorporated.
                          All Rights Reserved.
                        Qualcomm Confidential and Proprietary.
===============================================================================
*/

#include "com_dtypes.h"
#include <Uefi.h>
#include <Library/PcdLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Protocol/LoadedImage.h> 
#include <Library/CacheMaintenanceLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UncachedMemoryAllocationLib.h>
#include <Library/PcdLib.h>
#include <Library/ArmLib.h>
#include "bamosal.h"
#include "bam.h"
#include "bamtgtcfg.h"
#include "BamSettings.h"
#include "DTBExtnLib.h"
#include "DALSys.h"

#define DEVICESPACE_MAGIC_NUMBER  0xDEADCAFE

#define BAM_NODE_NAME   "/soc/bam_config"

#define BAM_DT_CHECK_ERROR(x)                                         \
{                                                                     \
  if (ret_value) {                                                    \
    DEBUG((EFI_D_ERROR,"%s, ret Value = %d\n", u##x, ret_value));     \
    goto __EXIT;                                                      \
  }                                                                   \
}

extern bam_target_config_type* bam_tgt_config_ptr;

/* ============================================================================
**  Function : bam_osal_malloc
** ============================================================================
*/
/**
  Mallocs a memory (virtual) using OS Malloc API.
    
  Mallocs a memory (virtual) using OS Malloc API. The memory allocated
  is for SW usage only.
    
  @param[in]  size    Size of the memory to be allocated

  @return
  Pointer to the memory allocated. NULL if failed.
  
  @sa
  bam_osal_mallocmemregion, bam_osal_free
*/
void * bam_osal_malloc(uint32 size)
{
    void *mem;
    EFI_STATUS            status;
    status=gBS->AllocatePool(EfiBootServicesData,size,(VOID**)&mem);

    if (EFI_SUCCESS != status)
    {
        DEBUG((EFI_D_INFO, "Allocate memory of size 0x%x     [FAILED]\n",size));
        return NULL;
    }
    return mem;
}

/* ============================================================================
**  Function : bam_osal_free
** ============================================================================
*/
/**
  Frees the memory allocated by bam_osal_malloc.
    
  Frees the memory (virtual) using OS Free API.   
    
  @param[in,out]  mem    Pointer to the memory to be freed

  @return
  None.
  
  @sa
  bam_osal_malloc.
*/
void bam_osal_free(void *pmem)
{
    gBS->FreePool(pmem);
}

/* ============================================================================
**  Function : bam_osal_memcpy
** ============================================================================
*/
/**
  Copies data in memory.

  Copies data in memory.

  @param[out]  dst    Pointer to the destination memory
  @param[in]   src    Pointer to the source memory
  @param[in]   size   size of data to be copied

  @return
  None.

  @sa
  bam_osal_malloc.
*/
void bam_osal_memcpy(void *dst, void* src, uint32 size)
{

}
/* ============================================================================
**  Function : bam_osal_mallocmemregion
** ============================================================================
*/
/**
  Allocates a physically contiguous memory location using OS specific API.
    
  Allocates a physically contiguous memory location using OS specific API. The
  memory allocated is expected to be share-able with the hw.
      
  @param[out]  meminfo    Info structure for the memory allocated.
  @param[in]      size    Size of the memory to be allocated.

  @return
  None.
  
  @sa
  bam_osal_freememregion.
*/
void bam_osal_mallocmemregion(bam_osal_meminfo *meminfo, uint32 size)
{

    if ( meminfo == NULL )
        return;
    /* in UEFI for device space VA:PA mapping is 1:1 and it's pre-mapped */
    /* if the physical address is given: indicates that we want to map an
     * address in the device space
     */
    if ( meminfo->pa )
    {
        meminfo->va = meminfo->pa;
        meminfo->size = size;
        meminfo->handle = (void*)DEVICESPACE_MAGIC_NUMBER ;
        return;
    }
    meminfo->handle = UncachedAllocatePool(size);

    if (NULL == meminfo->handle )
    {
        DEBUG((EFI_D_INFO, "Failed: Allocate memory of size 0x%x\n",size));
        return;
    }

    meminfo->size = size;
    meminfo->pa   = ConvertToPhysicalAddress(meminfo->handle);
    meminfo->va   = (UINTN)meminfo->handle;
   
    return;
}

/* ============================================================================
**  Function : bam_osal_freememregion
** ============================================================================
*/
/**
  Frees the memory allocated using bam_osal_mallocmemregion.
    
  Frees the memory allocated using bam_osal_mallocmemregion.
    
  @param[in]  meminfo    Info structure for the memory region to be freed.

  @return
  None.
 
  @sa
  bam_osal_mallocmemregion.
*/
void bam_osal_freememregion(bam_osal_meminfo *meminfo)
{
    if ( meminfo == NULL )
        return;

    if ( meminfo->handle  && meminfo->handle != (void*)DEVICESPACE_MAGIC_NUMBER )
        UncachedFreePool(meminfo->handle);

    meminfo->pa = 0;
    meminfo->va = 0;
    meminfo->size = 0;
    meminfo->handle = 0;
}

/* ============================================================================
**  Function : bam_osal_cachecmd
** ============================================================================
*/
/**
  Performs a cache maintanence operation.
    
  Performs a cache maintanence operation.
    
  @param[in]  cache_op    Cache Operation to perform (clean/flush/invalidate)
  @param[in]  address     Memory for which cache maintanence to be performed. 
  @param[in]  size        Size of the memory

  @return
  None.
  
*/
void bam_osal_cachecmd(bam_cache_op_type cache_op,bam_vaddr address, uint32 size)
{
    if( cache_op & BAM_CACHE_FLUSH )
    {
        WriteBackInvalidateDataCacheRange((void*)address,size);
    }
    if( cache_op & BAM_CACHE_CLEAN )
    {
        WriteBackDataCacheRange( (void *)address, size );
    }
    if( cache_op & BAM_CACHE_INVALIDATE )
    {
        InvalidateDataCacheRange( (void *)address, size );
    }
}

/* ============================================================================
**  Function : bam_osal_memorybarrier
** ============================================================================
*/
/**
  Performs a processor specific memory barrier operation.
    
  Performs a processor specific memory barrier operation.
    
  @param  None

  @return
  None.
  
*/
void bam_osal_memorybarrier(void)
{
     ArmDataMemoryBarrier();
}

/* ============================================================================
**  Function : bam_osal_init
** ============================================================================
*/
/**
  Initializes BAM device config .

  Initializes OSAL Interfaces. Performs any initialization pertaining to the
  BAM device config.

  @param  None

  @return
  None.

*/
void bam_osal_init(void)
{
  bam_target_config_type *dcfg = NULL;
  void* blob = NULL; 
  fdt_node_handle hNode;
  int ret_value = -1;
  uint32 prop_size = 0;

  bam_tgt_config_ptr = NULL;

  ret_value = fdt_get_blob_handle(&blob, DEFAULT_BLOB_ID);
  BAM_DT_CHECK_ERROR("Unable to get blob handle");
  
  ret_value = fdt_get_node_handle(&hNode, blob, BAM_NODE_NAME);
  BAM_DT_CHECK_ERROR("Unable to get BAM node handle");
  
  dcfg = bam_osal_malloc(sizeof(bam_target_config_type));
  if(!dcfg) {
    ret_value = -1;
    BAM_DT_CHECK_ERROR("Failed malloc BAM config");
  }

  DALSYS_memset((void *)dcfg, 0, sizeof(bam_target_config_type));

  ret_value = fdt_get_uint64_prop(&hNode, "bam_pa", (uint64 *)&dcfg->bam_pa);
  BAM_DT_CHECK_ERROR("Unable to get bam_pa");

  ret_value = fdt_get_uint32_prop(&hNode, "options", (uint32 *)&dcfg->options);
  BAM_DT_CHECK_ERROR("Unable to get BAM options");

  ret_value = fdt_get_uint32_prop(&hNode, "cfg_bits", (uint32 *)&dcfg->cfg_bits);
  BAM_DT_CHECK_ERROR("Unable to get BAM cfg_bits");

  ret_value = fdt_get_uint8_prop(&hNode, "ee", (uint8 *)&dcfg->ee);
  BAM_DT_CHECK_ERROR("Unable to get BAM ee");

  ret_value = fdt_get_prop_size(&hNode, "sec_config", &prop_size);
  BAM_DT_CHECK_ERROR("Unable to get BAM sec_config prop size");

  if (64 == (8 * prop_size)) {
    ret_value = fdt_get_uint64_prop(&hNode, "sec_config", (uint64 *)&dcfg->sec_config);
  } else {
    ret_value = fdt_get_uint32_prop(&hNode, "sec_config", (uint32 *)&dcfg->sec_config);
  }
  BAM_DT_CHECK_ERROR("Unable to get BAM sec_config");

  ret_value = fdt_get_uint32_prop(&hNode, "size", (uint32 *)&dcfg->size);
  BAM_DT_CHECK_ERROR("Unable to get BAM size"); 

__EXIT:
  if (ret_value) {
    if(dcfg)
    {
      bam_osal_free(dcfg);
      dcfg = NULL;
    }
  }

  bam_tgt_config_ptr = dcfg;
}
/* ============================================================================
**  Function : bam_osal_deinit
** ============================================================================
*/
/**
  DeInitializes OSAL Interfaces.

  Deinitializes OSAL Interfaces. Performs any deinitialization pertaining to the
  OS specific APIs.

  @param  None

  @return
  None.

*/
void bam_osal_deinit(void)
{
  if(bam_tgt_config_ptr) {
    bam_osal_free(bam_tgt_config_ptr);
    bam_tgt_config_ptr = NULL;
  }
}
/* ============================================================================
**  Function : bam_osal_syncinit
** ============================================================================
*/
/**
  Initializes a sync object.
    
  Initializes a sync object.
    
  @param[in,out] sync     Pointer to the object to be used for sync

  @return
  Success of the operation.
 
*/
bam_status_type bam_osal_syncinit(bam_osal_sync_type *sync)
{
  return BAM_SUCCESS;
}
/* ============================================================================
**  Function : bam_osal_syncdestroy
** ============================================================================
*/
/**
  Destroys a synchronization object.

  Destroys a synchronization object.

  @param[in,out]  sync    Sync object to be destroyed

  @return
  None.
  
*/
bam_status_type bam_osal_syncdestroy(bam_osal_sync_type *sync)
{
   return BAM_SUCCESS; 
}
/* ============================================================================
**  Function : bam_osal_syncenter
** ============================================================================
*/
/**
  Enters into a synchronized context.
    
  Enters into a synchronized context.
    
  @param[in,out]  sync    Sync object to be used

  @return
  None.
  
*/
void bam_osal_syncenter(bam_osal_sync_type *sync)
{
}

/* ============================================================================
**  Function : bam_osal_syncleave
** ============================================================================
*/
/**
  Leaves a synchronized context.
    
  Leaves a synchronized context.
    
  @param[in,out]  sync    Sync object to be used

  @return
  None.
  
*/
void bam_osal_syncleave(bam_osal_sync_type *sync)
{
}


/* ============================================================================
**  Function : bam_osal_isrinstall
** ============================================================================
*/
/**
  Registers an isr to an IRQ id.
    
  Registers with the interrupt controller, an ISR to service an IRQ.
    
  @param[in,out]  irqhandle    Handle to be used with the interrupt controller
  @param[in]      irq          IRQ ID to be registered for
  @param[in,out]  isr          ISR to be invoked to the service the irq
  @param[in,out]  data         data to be supplied to the isr upon invocation

  @return
  Success of the operation.
    
  @sa
  Other_Relevant_APIS_or_Delete.
*/
bam_status_type bam_osal_isrinstall(bam_osal_irq_type *irqhandle,uint32 irq,void *isr, void *data)
{
   return BAM_SUCCESS;
}

/* ============================================================================
**  Function : bam_osal_isruninstall
** ============================================================================
*/
/**
  Deregisters the ISR from the interrupt controller.
    
  Deregisters the ISR from the interrupt controller.
    
  @param[in,out]  irqhandle    Interrupt controller handle to be used

  @return
  None.
  
*/
void bam_osal_isruninstall(bam_osal_irq_type *irqhandle)
{
}

/* ============================================================================
**  Function : bam_osal_israck
** ============================================================================
*/
/**
  Acknowledges the IRQ.
    
  Acknowledges the IRQ. Some OS implementations require the ISR to ack the IRQ
  to re-activate the IRQ.
    
  @param[in,out]  irqhandle    Interrupt handle

  @return
  None.
  
*/
void bam_osal_israck(bam_osal_irq_type *irqhandle)
{
}

/* ============================================================================
**  Function : bam_osal_clock_ctl_init
** ============================================================================
*/
/**
  Initializes a clock control object.

  Initializes a clock control object.

  @param[in,out] clock_ctl     Pointer to the object to be used for clock control
  @param[in,out] clock_id      Pointer to the object to identify the clock

  @return
  Success of the operation.

*/
bam_status_type bam_osal_clock_ctl_init(bam_osal_clock_ctl_type *clock_ctl, void* clock_id)
{
  return BAM_SUCCESS;
}

/* ============================================================================
**  Function : bam_osal_clock_ctl_deinit
** ============================================================================
*/
/**
  Deinitializes a clock control object.

  Deinitializes a clock control object.

  @param[in,out] clock_ctl     Pointer to the object to be used for clock control

  @return
  Success of the operation.

*/
bam_status_type bam_osal_clock_ctl_deinit(bam_osal_clock_ctl_type *clock_ctl)
{
  return BAM_SUCCESS;
}

/* ============================================================================
**  Function : bam_osal_clock_ctl_enable
** ============================================================================
*/
/**
  Turn on clock.

  Turn on clock.

  @param[in,out]  clock_ctl    clock control object to be used

  @return
  Success of the operation.

*/
bam_status_type bam_osal_clock_ctl_enable(bam_osal_clock_ctl_type *clock_ctl)
{
  return BAM_SUCCESS;
}

/* ============================================================================
**  Function : bam_osal_syncleave
** ============================================================================
*/
/**
  Turn off clock.

  Turn off clock.

  @param[in,out]  clock_ctl    clock control object to be used

  @return
  Success of the operation.

*/
bam_status_type bam_osal_clock_ctl_disable(bam_osal_clock_ctl_type *clock_ctl)
{
  return BAM_SUCCESS;
}


/* ============================================================================
**  Function : bam_osal_debug
** ============================================================================
*/
/**
  Debug message logging interface.
    
  Debug message logging interface. Depending upon the OSAL implementation, it
  could be printed to a term window or sent as a diag msg or saved to a file
    
  @param[in]  fmt    Format similar to printf
  @param[in]  ...    Variable list of arguments to be processed

  @return
  None.
  
*/
#ifdef BAM_OSAL_DEBUG
void bam_osal_debug(bam_osal_msg_type msgLevel, const char *fmt, ...)
{

}
#endif

