/**---------------------------------------------------------------------------
 *   @file usb4_frames_seg_calc.h
 *
 *   @brief   
 *
 *   Copyright (c) 2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/
#ifndef __USB4_FRAMES_SEG_CALC_H__
#define __USB4_FRAMES_SEG_CALC_H__

/* --------------------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------------------*/
// #include "VVHAL_usb4_comdef.h"
// #include "VVHAL_usb4_mem.h"         // usb4_buff
#include "usb4_mem.h"

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
/**
 * @brief randomize numSegments which their sum is size_bytes
 *        and each segement size is between 1B and max segment bytes
 * @param [in] total_bytes total transfer size in bytes
 * @param [in] maxSeg_bytes max segment size in bytes
 * @param [in] maxSegments maximum number of segments to split total bytes
 * @param [output] pSegments array[numSegments] contain fregment sizes
 * @param [output] pNumSegments number of segments to be used
 * @return 0 on success, other on failure
 */
int Usb4FramesSegCalcRandom(UINT32 total_bytes, 
                            UINT32 maxSeg_bytes, 
                            UINT32 maxSegments,
                            UINT32* pSegments,
                            UINT32* pNumSegments);


/**
 * @brief get number of segments if each segment is max sized
 * @param [in] size_bytes total transfer size in bytes
 * @param [out] pNumSegments  number of segments
 * @return 0 on success, other on failure
 */
int Usb4FramesSegCalcMaxSizeSegments(UINT32 total_bytes, 
                                     UINT32 seg_bytes, 
                                     UINT32 maxSegments,
                                     UINT32* pSegments,
                                     UINT32* pNumSegments);

#endif /* __USB4_FRAMES_SEG_CALC_H__ */
