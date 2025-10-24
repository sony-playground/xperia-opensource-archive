/**
 @file  spcom_os_al.c
 */
/*=============================================================================
 Copyright (c) 2021 Qualcomm Technologies, Incorporated.
 All rights reserved.
 Qualcomm Technologies, Confidential and Proprietary.
 =============================================================================*/

/*=============================================================================
 EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 07/29/21   vp      Logging improvements
 04/29/21   vp      Increase event timeout to one minute
 02/24/21   vp      Increase event timeout
 06/15/20   vp      initial release
 =============================================================================*/

/*
 * Secure-Processor-Communication (SPCOM).
 *
 * This driver provides communication to Secure Processor (SP)
 * over G-Link transport layer.
 */

#include <stdio.h>  // vsnprintf()
#include <stdarg.h> // va_start()

#include <assert.h>

#include "spcom_os_al.h"       // include files, types, os services

#include <Protocol/EFIGLink.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * ----------------------------------------------------------------------*/

EFI_GLINK_PROTOCOL * glink_protocol = NULL;

#define WAIT_FOR_EVENT_TIMEOUT_MSEC   60*1000 //1 minute

boolean
spcom_os_is_event_signaled (struct spcom_os_event *event)
{
   glink_err_type ret = GLINK_STATUS_FAILURE;
   if (event->glink_handle)
   {
	   glink_protocol->GlinkRxPoll (event->glink_handle, &ret);
   }

   return event->signaled_by_poll;
}

int
spcom_os_init_event (struct spcom_os_event *event)
{
   event->signaled_by_poll = false;
   return 0;
}

int
spcom_os_set_event_glink_handle (struct spcom_os_event *event,
                                 void *glink_handle)
{
   event->glink_handle = glink_handle;
   return 0;
}

/* Return the time left in msec */
int
spcom_os_wait_for_event_with_timeout (struct spcom_os_event *event,
                                      size_t timeout_msec)
{
   boolean signaled = false;
   
   if(event == NULL)
   {
	   return -1;
   }
   
   if (event->glink_handle == NULL)
   {
	   return -1;
   }

   while (timeout_msec)
   {
      signaled = spcom_os_is_event_signaled (event);
      if (signaled)
      {
         return timeout_msec;
      }
      
      spcom_os_msleep (1); // 1 msec
      timeout_msec--;
   }
   
   return timeout_msec; // Time left
}

/* Return the time left in msec */
/*
 * If timeout value is not provided for polling,
 * 500 ms timeout should be used, instead of
 * infinite wait.
 */
int
spcom_os_wait_for_event (struct spcom_os_event *event)
{
   boolean signaled = false;
   size_t timeout_msec = WAIT_FOR_EVENT_TIMEOUT_MSEC;

   if (event->glink_handle == NULL)
      return -1;

   while (timeout_msec)
   {
      signaled = spcom_os_is_event_signaled (event);
      if (signaled)
      {
         return timeout_msec;
      }

      spcom_os_msleep (1); // 1 msec
      timeout_msec--;
   }
   return timeout_msec; // Time left
}

int
spcom_os_signal_event (struct spcom_os_event *event)
{
   event->signaled_by_poll = true;
   return 0;
}

int
spcom_os_reset_event (struct spcom_os_event *event)
{
   event->signaled_by_poll = false;
   return 0;
}

void*
spcom_os_malloc (size_t size)
{
   void *pMem = NULL;

   pMem = AllocateZeroPool (size);
   if (!pMem)
   {
      LOGE("AllocateZeroPool, size=0x%x", size);
   }
   return pMem;
}

void
spcom_os_free (void *pMem)
{
   FreePool (pMem);
}

void
spcom_os_msleep (size_t msec)
{
   gBS->Stall (msec * 1000);
}

volatile int spcom_hold_on_assert = 0;
volatile int spcom_brk_on_assert = 1;
static int spcom_assert_dummy_counter = 0;
void
spcom_os_assert (boolean all_ok)
{
   if (!all_ok)
   {
      if (spcom_brk_on_assert)
      {
         // One of the following should work, depends on the compiler:
         //__brk(); // BKPT
         // __asm__ ("BKPT");
         // __asm__ __volatile__ ("bkpt #0");
         __builtin_trap (); // BKPT
      }
      while (spcom_hold_on_assert)
      {
         spcom_assert_dummy_counter++;
      }
   }
}

void
spcom_os_al_init (void)
{
   if (glink_protocol == NULL)
   {
      EFI_STATUS status;

      status = gBS->LocateProtocol (&gEfiGLINKProtocolGuid, NULL,
                                    (void**) &glink_protocol);
      if (status != EFI_SUCCESS)
      {
         LOGE("LocateProtocol, gEfiGLINKProtocolGuid %r", status);
         return;
      }
   }
}
