/**---------------------------------------------------------------------------
 *   @file usb4_frames_seg_calc.c
 *
 *   @brief   
 *
 *   Copyright (c) 2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------------------*/
#include "Usb4Utils.h"
#include "usb4_frames_seg_calc.h"

// #include "VVHAL_usb4_logger.h"      // logger
// #include "VVHAL_usb4_mem.h"         // mem_alloc / free
// #include "VVHAL_usb4_utils.h"       // VVHAL_usb4_utils_rand

/* --------------------------------------------------------------------------
 * Macros / Types
 *--------------------------------------------------------------------------*/


/* --------------------------------------------------------------------------
 * Static Variables
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Global Variables
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Static Functions
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Global Functions
 *--------------------------------------------------------------------------*/

int Usb4FramesSegCalcRandom(UINT32 total_bytes, 
                            UINT32 maxSeg_bytes, 
                            UINT32 maxSegments,
                            UINT32* pSegments,
                            UINT32* pNumSegments)
{
  UINT32 i;
  UINT32 n;
  UINT32 sum;
  double scale;
  int result;

  if ((0 == total_bytes) || (0 == maxSeg_bytes) || (0 == maxSegments))
  {
    USB4_ERROR_STACK_MSG(-1, "Invliad sizes");
    return -1;
  }

  if ((NULL == pSegments) || (NULL == pNumSegments))
  {
    USB4_ERROR_STACK_MSG(-1, "Null input");
    return -1;
  }

  if ((maxSeg_bytes * maxSegments) < total_bytes)
  {
    USB4_ERROR_STACK_MSG(-1, "Not enough segments for total bytes");
    return -1;
  }

  // randmoize n = number of segments 
  result = usb4_utils_rand(1, maxSegments, &n);
  if (0 != result)
  {
    USB4_ERROR_STACK(result);
    return -1;
  }

  *pNumSegments = n;


  // Generate random n numbers
  sum = 0;
  for (i = 0; i < n; ++i)
  {
    result = usb4_utils_rand(1, maxSeg_bytes, (pSegments + i));
    if (0 != result)
    {
      USB4_ERROR_STACK(result);
      return -1;
    }

    sum += pSegments[i];
  }

  // Scale to desired size_bytes
  scale = (1.0 * total_bytes) / sum;
  sum = 0;
  for (i = 0; i < n; ++i)
  {
    pSegments[i] = (UINT32)(scale * pSegments[i]);
    if (0 == pSegments[i])
    {
      // this could happen when scale < 1
      USB4_ERROR_STACK_MSG(-1, "Seg calc is wrong... size is 0");
      return -1;
    }
    sum += pSegments[i];
  }

  // take rounding issues into account
  while(sum++ < total_bytes) 
  {
    result = usb4_utils_rand(0, (n-1), &i);
    if (0 != result)
    {
      USB4_ERROR_STACK(result);
      return -1;
    }

    pSegments[i] = pSegments[i] + 1;
  }

  return 0;
}

int Usb4FramesSegCalcMaxSizeSegments(UINT32 total_bytes, 
                                     UINT32 seg_bytes, 
                                     UINT32 maxSegments,
                                     UINT32* pSegments,
                                     UINT32* pNumSegments)
{
  UINT32 num;
  UINT32 size_bytes;

  if ((0 == total_bytes) || (0 == seg_bytes) || (0 == maxSegments))
  {
    USB4_ERROR_STACK_MSG(-1, "Invalid input");
    return -1;
  }

  if ((NULL == pSegments) || (NULL == pNumSegments))
  {
    USB4_ERROR_STACK_MSG(-1, "NULL input");
    return -1;
  }

  num = total_bytes / seg_bytes;

  // Take rounding issues into account
  if (total_bytes > (num * seg_bytes))
  {
    ++num;
  }

  if (num > maxSegments)
  {
    USB4_ERROR_STACK_MSG(-1, "Not enough segments");
    return -1;
  }


  for (UINT32 i = 0; i < num; ++i)
  {
    size_bytes = (total_bytes > seg_bytes) ? seg_bytes : total_bytes;
    pSegments[i] = size_bytes;
    total_bytes -= size_bytes;
  }

  *pNumSegments = num;

  return 0;
}

