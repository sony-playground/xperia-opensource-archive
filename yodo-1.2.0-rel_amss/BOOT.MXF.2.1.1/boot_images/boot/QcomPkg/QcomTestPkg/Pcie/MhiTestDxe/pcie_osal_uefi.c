/**
  @file pcie_osal_uefi.c
  @brief Internal interface include file for the PCIe target specific
  configuration layer.

  This file contains definitions of constants, data structures, and
  interfaces that provide target specific configuration data.

*/
/*
===============================================================================

                             Edit History


   when       who     what, where, why
   --------   ---     ------------------------------------------------------------
   05/21/21   nr      Created

===============================================================================
                   Copyright (c) 2021 QUALCOMM Technologies Incorporated
                          All Rights Reserved.
                        Qualcomm Confidential and Proprietary.
===============================================================================
*/
#include "com_dtypes.h"
#include <Base.h>
#include <PiDxe.h>
#include <Library/ArmLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/QcomBaseLib.h>
#include <Library/TzRngLib.h>

#include "pcie_osal.h"
#include "Library/pcie_host_r.h"

#include <Library/UefiBootServicesTableLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Protocol/EFIChipInfo.h>
#include <Protocol/EFIPlatformInfo.h>


void pcie_osal_init(void)
{
   DALSYS_InitMod (NULL);
}

void pcie_osal_deinit(void)
{
}

void pcie_osal_log_init(pcie_osal_log_client_t client, const char *name, size_t size,
                        pcie_osal_log_level_t filter_level)
{
}

void _pcie_osal_log(pcie_osal_log_client_t client, pcie_osal_log_level_t level,
                    uint32 num_args, const char *fmt, ...)
{
   VA_LIST  Marker;
   VA_START (Marker, fmt);
   AsciiPrint (fmt, Marker);
   VA_END (Marker);
}

void pcie_osal_log_string(pcie_osal_log_client_t client,
                          pcie_osal_log_level_t level,
                          const char *fmt, ...)
{
   VA_LIST  Marker;
   VA_START (Marker, fmt);
   AsciiPrint (fmt, Marker);
   VA_END (Marker);
}

uint64 pcie_osal_get_systime_ticks(void)
{
   return GetTimerCountms ();
}

void* pcie_osal_malloc(size_t size)
{
	void *buff; //*MapHandle;
	
//	buff = AllocatePages (EFI_SIZE_TO_PAGES(size)); // Keep it simple for now
   buff = AllocatePool (size);
   return buff;
}

void pcie_osal_free(void *ptr)
{
   FreePool (ptr);
}

void* pcie_osal_malloc_aligned(size_t size, uint8 align)
{
   return AllocatePages (EFI_SIZE_TO_PAGES(size)); // Keep it simple for now
}

void pcie_osal_free_aligned(void *ptr)
{
//   FreePages (ptr, number of pages);
}

void* pcie_osal_memset(void *ptr, uint8 val, size_t size)
{
   SetMem(ptr, size, val);
   return ptr;
}

void pcie_osal_busywait(uint32 time_us)
{
   gBS->Stall(time_us);
}

int pcie_osal_mem_region_map(pcie_osal_pa_t pa, size_t size, pcie_osal_mem_props_t mem_props,
                             pcie_osal_mem_info_t *mem_info)
{
  EFI_STATUS status = 0;
  EFI_GCD_MEMORY_SPACE_DESCRIPTOR Descriptor;

  /* Both memprop options can by satisfied by UC MMIO space type */

  status = gDS->GetMemorySpaceDescriptor(pa, &Descriptor);

  if (EFI_ERROR(status))
  {
     DEBUG ((EFI_D_ERROR,"Cannot get memory descriptor\n"));
     return -1;
  }

  if (Descriptor.GcdMemoryType != EfiGcdMemoryTypeMemoryMappedIo)
  {
     if (Descriptor.GcdMemoryType != EfiGcdMemoryTypeNonExistent)
     {
        status = gDS->RemoveMemorySpace(pa, size);
        DEBUG ((EFI_D_WARN, "Region is being remapped to correct type\n"));
     }

     status = gDS->AddMemorySpace (EfiGcdMemoryTypeMemoryMappedIo,
                                   pa, size, EFI_MEMORY_UC);
     if (EFI_ERROR(status))
     {
        DEBUG ((EFI_D_ERROR, "Unable to add memory space: addr=0x%lx, size=0xlx\n", pa, size));
        return -1;
     }

     status = gDS->SetMemorySpaceAttributes (pa, size, EFI_MEMORY_UC);
     if (EFI_ERROR(status))
     {
         DEBUG ((EFI_D_ERROR, "Fail to set memory attibute: addr=0x%lx, size=0xlx\n", pa, size));
         return -1;
     }
  }

  mem_info->va = mem_info->pa = pa;
  mem_info->size = size;

  return status;
}

void pcie_osal_memory_barrier(void)
{
   ArmDataMemoryBarrier ();
   ArmDataSynchronizationBarrier ();
}

int pcie_osal_isr_register(pcie_osal_irq_t *irq, uint32 irq_id, pcie_osal_cb_t isr, void *ctxt)
{
   return 0;
}

int pcie_osal_irq_enable(pcie_osal_irq_t *irq)
{
   return 0;
}

int pcie_get_target_platform_info (uint32* chip_id_ptr, uint32* chip_ver_ptr, uint32* chip_family_ptr, uint32* plat_type_ptr)
{
  EFI_STATUS                  Status;
  EFI_CHIPINFO_PROTOCOL      *pChipInfo;
  EFI_PLATFORMINFO_PROTOCOL  *pPlatformInfo;
  EFIChipInfoIdType           ChipId;
  EFIChipInfoVersionType      Version;
  EFIChipInfoFamilyType       ChipFamily;
  EFI_PLATFORMINFO_PLATFORM_INFO_TYPE PlatformInfo;

  if (plat_type_ptr)
  {
     Status = gBS->LocateProtocol (&gEfiPlatformInfoProtocolGuid, NULL,
                                   (VOID **) &pPlatformInfo);
     if (EFI_ERROR(Status))
       return 1;

     Status = pPlatformInfo->GetPlatformInfo(pPlatformInfo, &PlatformInfo);
     if (EFI_ERROR(Status))
       return 2;

     *plat_type_ptr = PlatformInfo.platform;
  }

  Status = gBS->LocateProtocol (&gEfiChipInfoProtocolGuid, NULL,
                               (VOID **) &pChipInfo);
  if (EFI_ERROR(Status))
    return 3;

  if (chip_id_ptr)
  {
     Status = pChipInfo->GetChipId(pChipInfo, &ChipId);
     if (Status != EFI_SUCCESS)
       return 4;

     *chip_id_ptr = ChipId;
  }

  if (chip_ver_ptr)
  {
     Status = pChipInfo->GetChipVersion(pChipInfo, &Version);
     if (Status != EFI_SUCCESS)
       return 5;

     *chip_ver_ptr = Version;
  }

  if (chip_family_ptr)
  {
     Status = pChipInfo->GetChipFamily(pChipInfo, &ChipFamily);
     if (Status != EFI_SUCCESS)
       return 6;

     *chip_family_ptr = ChipFamily;
  }

   return 0;
}

int pcie_osal_sync_init(pcie_osal_sync_t *sync, uint32 flags)
{
   EFI_STATUS status = EFI_SUCCESS;

   sync->lock = MutexInit(0);

   if(NULL == sync->lock)
   {
      return -1;
   }

   return status;
}

int pcie_osal_sync_deinit(pcie_osal_sync_t *sync)
{
   MutexDestroy(sync->lock);
   return EFI_SUCCESS;
}

void pcie_osal_sync_enter(pcie_osal_sync_t *sync)
{
   MutexAcquire(sync->lock);
}

void pcie_osal_sync_leave(pcie_osal_sync_t *sync)
{
   MutexRelease(sync->lock);
}

int pcie_osal_event_init(pcie_osal_event_t *event)
{
   /* Initialize event with 'auto-unsignal' flag set.
    * This is to ensure that the signal is cleared once 
    * the waiting thread is woken up.
    */
   event->evt = EventInit(0, 0, 1);
   if(NULL == event->evt)
   {
      return -1;
   }

   return EFI_SUCCESS;
}

int pcie_osal_event_deinit(pcie_osal_event_t *event)
{
   EventDestroy(event->evt);
   return EFI_SUCCESS;
}

void pcie_osal_event_reset(pcie_osal_event_t *event)
{
   EFI_STATUS status = EFI_SUCCESS;

   status = EventUnsignal(event->evt);
   if (EFI_ERROR(status))
   {
      DEBUG ((EFI_D_ERROR, "Event Reset failed - 0x%x\n", status));
   }
}

void pcie_osal_event_wait(pcie_osal_event_t *event)
{
   EFI_STATUS status = EFI_SUCCESS;
   
   status = EventWait(event->evt);
   if (EFI_ERROR(status))
   {
      DEBUG ((EFI_D_ERROR, "Event Wait failed - 0x%x\n", status));
   }
}

void pcie_osal_event_signal(pcie_osal_event_t *event)
{
   EFI_STATUS status = EFI_SUCCESS;

   /* TBD - determine whether 'reschedule' should be TRUE or false.
    * Currently it is FALSE.
    */
   status = EventSignal(event->evt, FALSE);
   if (EFI_ERROR(status))
   {
      DEBUG ((EFI_D_ERROR, "Event Signal failed - 0x%x\n", status));
   }
}

void pcie_osal_sleep(uint32 time_ms, boolean non_deferrable)
{
   uint64 time_us = time_ms * 1000;
   gBS->Stall(time_us);
}

int pcie_osal_thread_spawn(pcie_osal_thread_t *thread, const char *name,
                           pcie_osal_cb_t fcn, void *ctxt, uint32 priority)
{
   Thread* osal_thread = NULL;
   uint64 stack_size = PCIE_OSAL_DEFAULT_STACK_SIZE;

   osal_thread = ThreadCreate(name, fcn, ctxt, priority, stack_size);
   if(NULL == osal_thread)
   {
      return -1;
   }
   ThreadResume(osal_thread);
   ThreadDetach(osal_thread);

   thread->_thread = (void*)osal_thread;
   thread->_ctxt = ctxt;
   thread->_fcn = fcn;

   return 0;
}

uint32 pcie_osal_rand()
{
   return (uint32)GetRNGVal();
}

#ifdef UNUSED_APIS_ADD_IMPLEMENTATION_AND_MOVE_OUT
uint64 pcie_osal_get_elapsed_time(uint64 t1, uint64 t2, pcie_osal_time_unit_t unit)
{
}

int pcie_osal_mem_region_unmap(pcie_osal_mem_info_t *mem_info)
{
}

pcie_osal_pa_t pcie_osal_va_to_pa(pcie_osal_va_t va)
{
}

void pcie_osal_cache_ctrl(pcie_osal_cache_op_t op, pcie_osal_va_t va, size_t size)
{
}

int pcie_osal_sync_init(pcie_osal_sync_t *sync, uint32 flags)
{
}

int pcie_osal_sync_deinit(pcie_osal_sync_t *sync)
{
}

void pcie_osal_sync_enter(pcie_osal_sync_t *sync)
{
}

void pcie_osal_sync_leave(pcie_osal_sync_t *sync)
{
}

int pcie_osal_event_init(pcie_osal_event_t *event)
{
}

int pcie_osal_event_deinit(pcie_osal_event_t *event)
{
}

void pcie_osal_event_reset(pcie_osal_event_t *event)
{
}

void pcie_osal_event_wait(pcie_osal_event_t *event)
{
}

void pcie_osal_event_signal(pcie_osal_event_t *event)
{
}

void pcie_osal_sleep(uint32 time_ms, boolean non_deferrable)
{
   gBS->Stall(time_us);
}

int pcie_osal_thread_spawn(pcie_osal_thread_t *thread, const char *name,
                           pcie_osal_cb_t fcn, void *ctxt, uint32 priority)
{
}

void* pcie_osal_memset(void *ptr, uint8 val, size_t size)
{
}

size_t pcie_osal_memscpy(void *dst, size_t dst_size, const void *src, size_t src_size)
{
}

size_t pcie_osal_strlcpy(char *dst, const char *src, size_t dst_size)
{
}

uint32 pcie_osal_atomic_set(uint32 *ptr, uint32 value)
{
}

uint32 pcie_osal_atomic_read(uint32 *ptr)
{
}

void pcie_osal_atomic_set_bit(uint32 *ptr, uint32 bit)
{
}

void pcie_osal_atomic_clear_bit(uint32 *ptr, uint32 bit)
{
}

uint32 pcie_osal_atomic_inc(uint32 *ptr)
{
}

uint32 pcie_osal_atomic_dec(uint32 *ptr)
{
}

int pcie_osal_isr_unregister(pcie_osal_irq_t *irq)
{
}

int pcie_osal_irq_disable(pcie_osal_irq_t *irq)
{
}

boolean pcie_osal_irq_is_set(pcie_osal_irq_t *irq)
{
}

int pcie_osal_isq_mask(pcie_osal_irq_t *irq)
{
}

int pcie_osal_isq_unmask(pcie_osal_irq_t *irq)
{
}

int pcie_osal_irq_ack(pcie_osal_irq_t *irq)
{
}

#endif

