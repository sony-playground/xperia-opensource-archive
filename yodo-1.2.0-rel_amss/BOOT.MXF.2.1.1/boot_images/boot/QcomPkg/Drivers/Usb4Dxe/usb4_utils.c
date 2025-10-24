/**---------------------------------------------------------------------------
 *   @file        usb4_utils.c
 *
 *   @brief   Header file for a utilities
 *
 *   Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/


#include "Library/QcomBaseLib.h"  /*Timer API */
#include "Library/UefiBootServicesTableLib.h"
#include <Protocol/EFIRng.h>
#include <Usb4Utils.h>

// TODO: AC Tthese timer APIs are not multithread safe
int usb4_timer_Sleep_us(usb4_utils_timer *This, UINT32 sleep_us)
{
  if (USB4_TIMER_SOURCE_QTIMER == This->m_source)
  {
    gBS->Stall(sleep_us);
  }
  return 0;
}

int usb4_timer_Sleep_ms(usb4_utils_timer *This, UINT32 sleep_ms)
{
  UINT32 sleep_us = sleep_ms*1000;
  if (USB4_TIMER_SOURCE_QTIMER == This->m_source)
  {
    gBS->Stall(sleep_us);
  }
  return 0;
}
 
int usb4_timer_Start(usb4_utils_timer *This)
{
  if (USB4_TIMER_SOURCE_QTIMER == This->m_source)
  {
    This->last_time_ms = GetTimerCountms();
    This->last_time_us = GetTimerCountus();
  }
  return 0;
}

int usb4_timer_GetElapsed_us(usb4_utils_timer *This, UINT32 *elapsed_us)
{
  if (USB4_TIMER_SOURCE_QTIMER == This->m_source)
  {
    *(elapsed_us) =  GetTimerCountus() - This->last_time_us;
  }
  return 0;
}

int usb4_timer_GetElapsed_ms(usb4_utils_timer *This, UINT32 *elapsed_ms)
{
  if (USB4_TIMER_SOURCE_QTIMER == This->m_source)
  {
    *(elapsed_ms) =  GetTimerCountms() - This->last_time_ms;
  }
  return 0;
}


UINT32 usb4_get_depth_from_topology(UINT64 topologyID)
{
    UINT32 depth = 0;
    while (0 != topologyID)
    {
        depth++;
        topologyID = topologyID >> 8;
    }
    return depth;
}

UINT64 usb4_next_router_topology(UINT64 topologyID, UINT32 port)
{
    UINT32 depth;
    depth = usb4_get_depth_from_topology(topologyID);
    return ((port << depth*8)| topologyID);
}

int usb4_get_router_and_port(UINT64 topologyID, UINT64* router, UINT32* port)
{
    UINT32 depth;
    UINT64 mask;
    depth = usb4_get_depth_from_topology(topologyID);
    USB4_ASSERT_MSG(depth > 0, "Can't get parent router for the host router")

    mask = 0x0ffULL<<((depth-1)*8);\
    *port = 0xFF&((topologyID & mask)>>((depth-1)*8));\
    *router = topologyID & ~mask;\

    return 0;
}



int usb4_utils_rand_uint8(UINT8 min, UINT8 max, UINT8* pRand)
{
  /** Randomize a range between min and max (inclusive) */

  if ((min > max) || (NULL == pRand))
  {
    USB4_ERROR_STACK_MSG(-1, "Invalid input\n");
    return -1;
  }
  // TODO deal with max=MAX, min=0 overflow
  *pRand = (Usb4UtilGetRandomNumber(max) % (max - min + 1)) + min;

  return 0;
}

int usb4_utils_rand_true_false(BOOLEAN* pRand)
{
  if ((NULL == pRand))
  {
    USB4_ERROR_STACK_MSG(-1, "Invalid input\n");
    return -1;
  }
  *pRand = (0 == Usb4UtilGetRandomNumber(256) % 2);

  return 0;
}

int usb4_utils_rand(UINT32 min, UINT32 max, UINT32* pRand)
{
  /** Randomize a range between min and max (inclusive) */

  if ((min > max) || (NULL == pRand))
  {
    USB4_ERROR_STACK_MSG(-1, "Invalid input\n");
    return -1;
  }

  *pRand = (Usb4UtilGetRandomNumber(max) % (max - min + 1)) + min;

  return 0;
}

int usb4_utils_rand_range(UINT32 min, 
                          UINT32 max,
                          UINT32* pStart,
                          UINT32* pEnd)
{
  int result = 0;
  /** Randomize range start */
  UINT32 rands[2];


  if ((min > max) || (NULL == pStart) || (NULL == pEnd))
  {
    USB4_ERROR_STACK_MSG(-1, "Invalid input\n");
    return -1;
  }

  for (UINT32 i = 0; i < ARR_SIZE(rands); ++i)
  {
    result = usb4_utils_rand(min, max, rands + i);
    if (0 != result)
    {
      USB4_ERROR_STACK(-1);
      return -1;
    }
  }

  if (rands[1] > rands[0])
  {
    *pStart = rands[0];
    *pEnd = rands[1];
  }
  else
  {
    *pStart = rands[1];
    *pEnd = rands[0];
  }

  return 0;
}


UINT32 Usb4UtilGetRandomNumber(UINT32 max)
{
   static EFI_QCOM_RNG_PROTOCOL *gRandProtocol = NULL;
   UINT8 RngValue = 0;
   EFI_STATUS Status;

   if (gRandProtocol == NULL)
   {
     //Get Rand Protocol
  	 Status = gBS->LocateProtocol(&gQcomRngProtocolGuid, NULL, (VOID **) &gRandProtocol);
     if (Status != EFI_SUCCESS)
     {
       USB4_ERR_FATAL("Unable to locate gQcomRngProtocolGuid", 0, 0, 0);
       return 0;
     }
   }

   // Get random number
   gRandProtocol->GetRNG(gRandProtocol, NULL, sizeof(RngValue), &RngValue);
   return RngValue%(max+1);
}

