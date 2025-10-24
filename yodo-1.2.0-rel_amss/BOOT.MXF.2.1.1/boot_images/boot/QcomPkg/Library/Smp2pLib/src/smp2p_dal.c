
/*===========================================================================

               S M P 2 P   D A L S Y S

===========================================================================*/
/**
  @file smp2p_dal.c
*/
/* Abstracts the OS specific implementation of system function implemented by
   DALSYS.
*/


/* NOTE: For the output PDF generated using Doxygen and Latex, all file and
         group descriptions are maintained in the SMEM_mainpage file. To change
         any of the the file/group text for the PDF, edit the SMEM_mainpage
         file, or contact Tech Pubs.

         The above description for this file is part of the "smem" group
         description in the SMEM_mainpage file.
*/

/*===========================================================================
Copyright (c) 2012-2016, 2017, 2020, 2021 Qualcomm Technologies Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary.
===========================================================================*/


/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/Smp2pLib/src/smp2p_dal.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/26/17   jlg     Moved some structure definitions to smp2p_settings.h
09/07/15   rv      Moved OS timetick init from smp2p_os_log() to smp2p_init()
07/23/14   bc      Adding Sensor processor support
06/13/14   bc      Added QDI support
09/25/13   pa      Remove self-checking code from early smp2p development.
06/25/13   pa      Fix minor bugs in smp2p_os_log.
02/12/13   pa      Convert ASSERT_BRK to ASSERT.
01/14/13   pa      Updated to newer SMEM_* defines SMEM_WCN and SMEM_ADSP.
10/25/12   pa      Initial revision.
===========================================================================*/

/*===========================================================================
                        INCLUDE FILES
===========================================================================*/

#include "comdef.h"
//#include "LoaderUtils.h"
#include "smp2p_internal.h"
#include "smp2p_settings.h"
#include "DALSys.h"
#include "DALDeviceId.h"
#include "TimetickUEFI.h"
#include "err.h"
#include "assert.h"
#include <Library/KernelLib.h>
#include <Library/BaseLib.h>
#include <Uefi.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/ArmLib.h>
#include "Protocol/EFISmem.h"
#include <Protocol/EFIIPCC.h>

#ifdef FEATURE_SMP2P_QDI
#include "smp2p_qdi_driver.h"
#endif /* FEATURE_SMP2P_QDI */

#ifndef ERR_FATAL
#define ERR_FATAL(str, a, b, c) ASSERT(0)
#endif

extern EFI_SMEM_PROTOCOL *smp2pi_smem_protocol_iface;

extern const smp2p_proc_info_type smp2p_devcfg_proc_info;
extern smp2p_interrupt_info_type *smp2p_devcfg_interrupt_info;
/*===========================================================================
                      LOCAL TYPE DEFINITIONS
===========================================================================*/

/** Defines the header word of the log entry */
typedef union
{
  struct
  {
    /* id of the remote processor */
    uint8  remote_id;

    /* state of the connection */
    uint8  state;

    /* id of the event */
    uint16 event_id;
  } fields;
  uint32 all;
} smp2p_log_header_type;

/** Defines the SMP2P log entry.
 *  Order and size is meant to mimic SMEM log. */
typedef struct
{
  /* timestamp of when the event occurred */
  uint32 timestamp;

  /* header for this log entry */
  smp2p_log_header_type header;

  /* caller data 1 */
  uint32 data1;

  /* caller data 2 */
  uint32 data2;
} smp2p_log_entry_type;

/*===========================================================================
                        EXTERNAL DATA DEFINITIONS
===========================================================================*/

/** The count of interrupts triggered to the local proc as part of loopback */
//extern uint32 smp2p_lb_int_count;

/** Main SMP2P info data structure */
extern smp2p_info_type smp2p_info[SMEM_NUM_HOSTS];

/** Pointer to critical section for the SMP2P local log */
extern void * smp2p_log_cs;

/*===========================================================================
                        LOCAL DATA DEFINITIONS
===========================================================================*/

/** The handle for DALIPCINT: outgoing interrupts. */
static EFIIPCC_Handle smp2p_intr_handle = NULL;
EFI_IPCC_PROTOCOL *pIpccProtocol = NULL;

/** DAL Timetick handle */
//static DalDeviceHandle * smp2p_timetick_handle = NULL;

/** This is the global structure which holds information about interrupts on
 *  this processor. */
smp2p_interrupt_info_type smp2p_interrupt_table[SMEM_NUM_HOSTS];

#ifdef SMP2P_LOG_LOCAL

/** SMP2P local log */
static smp2p_log_entry_type smp2p_log[SMP2P_LOG_NUM_ENTRIES];

/** SMP2P local log index.
 *  Points to the next entry to write to in the log. */
static uint32 smp2p_log_idx = 0;

#endif

/** Device configuration interrupts info array */
static smp2p_interrupt_info_type *smp2p_interrupt_info;

/*===========================================================================
                      FUNCTION DEFINITIONS
===========================================================================*/

/*===========================================================================
  FUNCTION  smp2p_target_init_interrupts
===========================================================================*/
/**
  This function initializes the interprocessor interrupts for this target.
  
  @return
  None

  @sideeffect
  Initializes the interrupt table

  @dependencies
  None
*/
/*==========================================================================*/
static void smp2p_target_init_interrupts(void)
{
  uint32 i;
  smp2p_interrupt_info_type *intr_info = 0;
  
  /* Clear out the interrupt table */
  for( i = 0; i < SMEM_NUM_HOSTS; i++ )
  {
    smp2p_interrupt_table[i].dest      = SMEM_INVALID_HOST;
    smp2p_interrupt_table[i].processor = SMP2P_NULL_CLIENT;
    smp2p_interrupt_table[i].irq       = SMP2P_NULL_SIGNAL;
  }

  smp2p_interrupt_info = (smp2p_interrupt_info_type *)smp2p_devcfg_interrupt_info;
  
  for (i = 0; smp2p_interrupt_info[i].dest != SMEM_INVALID_HOST; i++)
  {
    intr_info = &smp2p_interrupt_info[i];

    if (intr_info->dest >= SMEM_NUM_HOSTS)
  {
      ERR_FATAL("smp2p_target_init_interrupts: DevCfg invalid destination=%d, i=%d.", 
              intr_info->dest, i, 0);
      return;
  }

    smp2p_interrupt_table[intr_info->dest].dest         = intr_info->dest;
    smp2p_interrupt_table[intr_info->dest].processor    = intr_info->processor;
    smp2p_interrupt_table[intr_info->dest].irq          = intr_info->irq;
  }
}

/*===========================================================================
  FUNCTION  smp2p_target_init
===========================================================================*/
/**
  This function initialize the processor info and interprocessor interrupts 
  for this target.

  @return
  None

  @sideeffect
  Initializes processor info and the interrupt table

  @dependencies
  None
*/
/*==========================================================================*/
void smp2p_target_init(void)
{
  EFI_STATUS status;
  int ret = 0;
  EFI_GUID smem_guid = EFI_SMEM_PROTOCOL_GUID;
  
  status = gBS->LocateProtocol(&smem_guid, NULL,
                               (void**)&smp2pi_smem_protocol_iface);
							   
  if(status != EFI_SUCCESS)
  {
    return;
  }
  
  ret = smp2p_dt_parse();
  if(ret)
  {
	ERR_FATAL("smp2p_dt_parse failed %d", ret, 0, 0);
  }
	  
  /* Update the global processor info */
  smp2p_proc_info = smp2p_devcfg_proc_info;
  
  /* Initialize interrupts */
  smp2p_target_init_interrupts();
}

/*===========================================================================
  FUNCTION  smp2p_os_init_event
===========================================================================*/
/**
  Initializes the OS specific event object.

  @param [in]   os_params   Pointer to the OS specific params struct

  @return
  SMP2P_STATUS_SUCCESS - Event initialized.
  SMP2P_STATUS_FAILURE - Failure occurred.

  @dependencies
  None.
*/
/*=========================================================================*/
int32 smp2p_os_init_event(smp2p_os_params_type * os_params)
{	
	os_params->hEvent = EventInit(0,0,SCHED_EVENT_FLAG_AUTOUNSIGNAL);
	return SMP2P_STATUS_SUCCESS;
}

/*===========================================================================
  FUNCTION  smp2p_os_deinit_event
===========================================================================*/
/**
  De-initialize the OS specific event object.

  @param [in]   os_params   Pointer to the OS specific params struct

  @return
  SMP2P_STATUS_SUCCESS - Event de-initialized.
  SMP2P_STATUS_FAILURE - Failure occurred.

  @dependencies
  None.
*/
/*=========================================================================*/
int32 smp2p_os_deinit_event(smp2p_os_params_type * os_params)
{
  DALResult result;
  
  result = DALSYS_DestroyObject(os_params->hEvent);
  if (DAL_SUCCESS != result)
  {
    return SMP2P_STATUS_FAILURE;
  }

  return SMP2P_STATUS_SUCCESS;
}

/*===========================================================================
  FUNCTION  smp2p_os_send_event
===========================================================================*/
/**
  Triggers the OS specific event object.

  @param [in]   os_params   Pointer to the OS specific params struct

  @return
  SMP2P_STATUS_SUCCESS - Event initialized.
  SMP2P_STATUS_FAILURE - Failure occurred.

  @dependencies
  None.
*/
/*=========================================================================*/
int32 smp2p_os_send_event(smp2p_os_params_type * os_params)
{
#ifdef FEATURE_SMP2P_QDI
  if( os_params->smp2p_qdi_context )
  {
    return smp2p_qdi_signal_send_event( os_params->smp2p_qdi_context );
  }
#endif /* FEATURE_SMP2P_QDI */
  return NO_ERROR == EventSignal(os_params->hEvent, TRUE) ?
         SMP2P_STATUS_SUCCESS :
         SMP2P_STATUS_FAILURE;
}

/*===========================================================================
  FUNCTION  smp2p_os_wait
===========================================================================*/
/**
  Blocks on the OS specific event object found in the context.

  @param [in]   ctx   Pointer to the SMP2P context struct

  @return
  SMP2P_STATUS_SUCCESS - Event initialized.
  SMP2P_STATUS_FAILURE - Failure occurred.

  @dependencies
  None.
*/
/*=========================================================================*/
int32 smp2p_os_wait(smp2p_context_type * ctx)
{
	EventWait(ctx->os_params.hEvent);
	return SMP2P_STATUS_SUCCESS;
}

/*===========================================================================
  FUNCTION  smp2p_os_wait_multiple
===========================================================================*/
/**
  Blocks on the OS specific events object found in an array of contexts.

  @param [in]   ctx_arr     Array of one or more pointers to SMP2P contexts
                            to wait on.
  @param [in]   ctx_count   Number of valid contexts in ctx array
  @param [out]  trigger_idx Index of context which was triggered

  @return
  SMP2P_STATUS_SUCCESS - Event initialized.
  SMP2P_STATUS_FAILURE - Failure occurred.

  @dependencies
  None.
*/
/*=========================================================================*/
int32 smp2p_os_wait_multiple
(
  smp2p_context_type ** ctx_arr,
  uint32                ctx_count,
  uint32              * trigger_idx
)
{
  DALSYSEventHandle events_ptr[SMEM_NUM_HOSTS];
  DALResult result;
  uint32 i;

  /* map the OS params into an array which DAL accepts */
  for (i=0; i<ctx_count; i++)
  {
    events_ptr[i] = ctx_arr[i]->os_params.hEvent;
  }

  result = DALSYS_EventMultipleWait(
            events_ptr,
            ctx_count,
            DALSYS_EVENT_TIMEOUT_INFINITE,
            trigger_idx);

  return DAL_SUCCESS == result ?
         SMP2P_STATUS_SUCCESS :
         SMP2P_STATUS_FAILURE;
}

/*===========================================================================
  FUNCTION  smp2p_os_register_interrupt
===========================================================================*/
/**
  This function registers SMP2P interrupts.

  @return
  None
*/
/*=========================================================================*/
void smp2p_os_register_interrupt(void)
{
  smp2p_interrupt_info_type * intr;
  uint32 i;
  EFIIPCCErr ret;

  /* Create Incoming Interrupt Controller Handle */
  if(gBS->LocateProtocol (&gEfiIpccProtocolGuid, NULL,(VOID**) &pIpccProtocol) == EFI_SUCCESS )
  {
	pIpccProtocol->IpccAttach(&smp2p_intr_handle, EFI_IPCC_P_MPROC);
  }

  for (i=0; i<SMEM_NUM_HOSTS; i++)
  {
    /* Register the SMP2P-specific interrupt */
    intr = (smp2p_interrupt_info_type *)&smp2p_interrupt_table[i];

    if (intr->irq != SMP2P_NULL_SIGNAL)
    {
      ret = pIpccProtocol->IpccRegisterInterrupt(
            smp2p_intr_handle,
            intr->processor,
            intr->irq,
            intr->irq,
            (EFIIPCC_CB)smp2pi_isr,
            (EFIIPCC_CBData)intr->dest);
			
     if ((ret != EFI_IPCC_EOK) && 
         (ret != EFI_IPCC_EARG) &&
         (ret != EFI_IPCC_ENOTSUPPORTED))
      {
        ERR_FATAL("smp2p_register_interrupt: SMP2P ISR for host %d failed to "
                  "register.", i, 0, 0);
      }
    }
  }
}

/*===========================================================================
  FUNCTION  smp2p_os_send_interrupt
===========================================================================*/
/**
  This function sends out the interprocessor interrupts.

  @param[in] dest Destination processor to interrupt

  @return
  None
*/
/*=========================================================================*/
void smp2p_os_send_interrupt(smem_host_type dest)
{
  /* just count the number of interrupts triggered to the local processor
   * for loopback */
  if (SMP2P_LPBK_HOST == dest)
  {
    //smp2p_lb_int_count++;
  }

  /* Send interrupt if it is valid */
  else if (SMP2P_NULL_SIGNAL != smp2p_interrupt_table[dest].irq)
  {
	pIpccProtocol->IpccTrigger(smp2p_intr_handle,smp2p_interrupt_table[dest].processor,
                 smp2p_interrupt_table[dest].irq,
                 smp2p_interrupt_table[dest].irq);
  }
}

/*===========================================================================
  FUNCTION  smp2p_os_cs_create
===========================================================================*/
/**
  Creates the critical section used to acquire access to SMP2P from different
  tasks.

  @return
  Pointer to critical section object

  @dependencies
  None.

  @sideeffects
  None.
*/
/*=========================================================================*/
void * smp2p_os_cs_create(void)
{
  LockHandle* Smp2pCSPtr = (LockHandle*)0xdeadbeef;/*Initialized it with a dummy value so that its neither null nor a dangling pointer (done to solve MISRA violation)*/
  InitRecursiveLock (0, &Smp2pCSPtr);
  return Smp2pCSPtr;
}

/*===========================================================================
  FUNCTION  smp2p_os_cs_lock
===========================================================================*/
/**
  Locks the critical section used by SMP2P.

  This function uses the OS-supplied mutual exclusion primitives so that
  multiple tasks can lock access to SMP2P.

  @param[in] cs Pointer to the critical section object

  @return
  None

  @dependencies
  None.

  @sideeffects
  Prevents context switch.
*/
/*==========================================================================*/
void smp2p_os_cs_lock(VOID* cs)
{
	AcquireLock (cs);
}

/*===========================================================================
  FUNCTION  smp2p_os_cs_unlock
===========================================================================*/
/**
  Releases the critical section used by SMP2P.

  This function uses the OS-supplied mutual exclusion primitives so that
  multiple tasks can unlock access to SMP2P.

  @param[in] cs Pointer to the critical section object

  @return
  None

  @dependencies
  None.

  @sideeffects
  Allows context switch.
*/
/*==========================================================================*/
void smp2p_os_cs_unlock(VOID* cs)
{
	ReleaseLock (cs); 
}

/*===========================================================================
  FUNCTION  smp2p_os_timetick_init
===========================================================================*/
/**
  Creates the handle for the OS-specific timetick handle, if necessary.

  @return
  SMEM_ERROR on failure
  SMEM_SUCCESS on success
*/
/*=========================================================================*/
int32 smp2p_os_timetick_init(void)
{
  return SMP2P_STATUS_SUCCESS;
}

/*===========================================================================
  FUNCTION  smp2p_os_timetick_get
===========================================================================*/
/**
  Returns the current timetick value.

  @return
  The current timetick value, measured in ticks.
  0 if an error occurred.
*/
/*=========================================================================*/
uint32 smp2p_os_timetick_get(void)
{
	return 0;
}

/*===========================================================================
  FUNCTION  smp2p_os_log
===========================================================================*/
/**
  This function writes an event entry into the SMP2P log.

  If SMP2P_LOG_LOCAL is defined, this function writes entries to a local
  circular buffer.  If SMP2P_LOG_SMEM is defined, this function writes
  entries to the SMEM log.  These options are not mutually exclusive.

  @param[in]  event_id  An event identifier for this event
                        For example, an event may be receiving data, or
                        creating a new entry.
  @param[in]  remote_id Identifier of the remote endpoint.  If not applicable,
                        set to -1.
  @param[in]  data1     First data word.  Usually specific to the event_id.
  @param[in]  data2     Second data word.  Usually specific to the event_id.
  @param[in]  flags     Flags param. 
                        SMP2P_FLAGS_STM prevents this function from locking as 
                        well as from logging to SMEM log (which required 
                        interprocessor lock).

  @return
  None.
*/
/*=========================================================================*/
void smp2p_os_log
(
  uint32 event_id,
  int32  remote_id,
  uint32 data1,
  uint32 data2,
  uint32 flags
)
{
#ifdef SMP2P_LOG_LOCAL
  {
    smp2p_log_entry_type   entry;
    smp2p_log_entry_type * entry_ptr;
    uint8 remote_state = (remote_id >= 0 && remote_id < SMEM_NUM_HOSTS) ?
                          smp2p_info[remote_id].state : -1;

    /* fill in the local entry */
    entry.header.fields.event_id  = event_id;
    entry.header.fields.remote_id = remote_id;
    entry.header.fields.state     = remote_state;
    entry.timestamp               = smp2p_os_timetick_get();
    entry.data1                   = data1;
    entry.data2                   = data2;

    if (!(flags & SMP2P_FLAGS_STM))
    {
      /* lock here to protect the global log */
      smp2p_os_cs_lock(smp2p_log_cs);
    }

    /* set the pointer to the entry in question */
    entry_ptr = &smp2p_log[smp2p_log_idx];

    /* update index, and handle wrap around case */
    smp2p_log_idx = (smp2p_log_idx + 1) % SMP2P_LOG_NUM_ENTRIES;

    /* copy the data there */
    memcpy(entry_ptr, &entry, sizeof(entry));

    if (!(flags & SMP2P_FLAGS_STM))
    {
      smp2p_os_cs_unlock(smp2p_log_cs);
    }
  }
#endif

#ifdef SMP2P_LOG_SMEM
  /* If STM (single threaded mode) is specified, skip logging */
  if (!(flags & SMP2P_FLAGS_STM))
  {
    smp2p_log_header_type header;
    uint8 remote_state = (remote_id >= 0 && remote_id < SMEM_NUM_HOSTS) ?
                          smp2p_info[remote_id].state : -1;

    header.fields.event_id   = event_id;
    header.fields.remote_id  = remote_id;
    header.fields.state      = remote_state;
    SMEM_LOG_EVENT(SMP2P_SMEM_LOG_EVENT_ID, header.all, data1, data2);
  }
#endif
}

/*===========================================================================
  FUNCTION  smp2p_os_malloc
===========================================================================*/
/**
  Dynamically allocate a region of memory from the heap.  The region should be
  freed using \c smp2p_os_free when no longer used.

  @param[in]  size   The number of bytes to be allocated.

  @return    The pointer to the region of memory that was allocated.
             NULL if the allocation failed.
*/
/*=========================================================================*/
void * smp2p_os_malloc(uint32 size)
{
  void * pMem;
  EFI_STATUS efiStatus;
  efiStatus = gBS->AllocatePool( EfiBootServicesData, size, &pMem );
  return (EFI_SUCCESS == efiStatus)? pMem: NULL;
}

/*===========================================================================
  FUNCTION  smp2p_os_free
===========================================================================*/
/**
  Free a region of memory that was allocated by \c smp2p_os_malloc.

  @param[in] pMem    A reference to the region of memory to be freed.

  @return    0 if succesful.
             Negative value if an error occurred.
*/
/*=========================================================================*/
int32 smp2p_os_free(void * pMem)
{
	gBS->FreePool( pMem );
	return 0;
}

/*===========================================================================
  FUNCTION  smp2p_mem_copy
===========================================================================*/
/**
  Copies bytes from the source buffer to the destination buffer.

  This function ensures that there will not be a copy beyond the size of 
  the destination buffer.

  The result of calling this on overlapping source and destination
  buffers is undefined.
  
  @param[out] dst       Destination buffer.
  @param[in]  dst_size  Size of the destination buffer in bytes.
  @param[in]  src       Source buffer.
  @param[in]  copy_size Number of bytes to copy from source buffer.

  @return
  The number of bytes copied to the destination buffer.  It is the
  caller's responsibility to check for trunction if it cares about it -
  truncation has occurred if the return value is less than src_size.
*/
/*==========================================================================*/
uint32 smp2p_mem_copy
(
  void       *dst, 
  uint32     dst_size, 
  const void *src, 
  uint32     copy_size
)
{
  uint32 ret_size;

  ret_size = memscpy(dst, dst_size, src, copy_size);
  return ret_size;
}

/*===========================================================================
  FUNCTION  smp2p_mem_move
===========================================================================*/
/**
  Moves bytes from the source buffer to the destination buffer.

  This function ensures that there will not be a copy beyond 
  the size of the destination buffer. 

  This function should be used in preference to memscpy() if there
  is the possiblity of source and destination buffers overlapping.
  The result of the operation is defined to be as if the copy were from
  the source to a temporary buffer that overlaps neither source nor
  destination, followed by a copy from that temporary buffer to the
  destination.
   
  @param[out] dst       Destination buffer.
  @param[in]  dst_size  Size of the destination buffer in bytes.
  @param[in]  src       Source buffer.
  @param[in]  copy_size Number of bytes to copy from source buffer.
   
  @return 
  The number of bytes copied to the destination buffer.  It is the
  caller's responsibility to check for trunction if it cares about it -
  truncation has occurred if the return value is less than src_size.
*/
/*==========================================================================*/
uint32 smp2p_mem_move
(
  void       *dst, 
  uint32     dst_size, 
  const void *src, 
  uint32     copy_size
)
{
  uint32 ret_size;

  ret_size = memsmove(dst, dst_size, src, copy_size);
  return ret_size;
}
