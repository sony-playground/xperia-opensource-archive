/**
 * @file ddi_memcpy.s
 * @brief
 * DDI memcpy APIs.
 */
/*=============================================================================

                                ddi memcpy
                                Source File
GENERAL DESCRIPTION
This file defines the DDI specific memcpy

  Copyright (c) 2021 QUALCOMM Technologies Incorporated.
  All rights reserved.
  Qualcomm Confidential and Proprietary.
===============================================================================

===============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

===============================================================================
when       who     what, where, why
--------   ---     ------------------------------------------------------------
04/20/21   lj      Initial version
==============================================================================*/

//#define DDI_MEMTEST_SIMD_LOAD_PAIR

/* ============================================================================
**  Function : ddi_memset
** ============================================================================
*/
/*!
*   @brief
*   memset by minimum 32x64bits unit resolution
*
*   @param addr        -   [IN] Destination address, uint64
*   @param addr        -   [IN] value, uint64
*   @param addr        -   [IN] number of longword(64bits)
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/
#if defined(DDI_MEMTEST_SIMD_LOAD_PAIR)

.global ddi_memset512
.type ddi_memset512,@function

ddi_memset512:
    cbz     x2, 81f
    lsr     x2, x2, #6
    mov   V3.d[0], x1
	mov   V4.d[0], x1
	mov   V5.d[0], x1
	mov   V6.d[0], x1
	mov   V3.d[1], x1
	mov   V4.d[1], x1
	mov   V5.d[1], x1
	mov   V6.d[1], x1

ddi_memset8_64:
    prfm  PSTL1STRM, [x0, #0]
    st1  {v3.2D, v4.2D, v5.2D, v6.2D}, [x0], #64
    st1	 {v3.2D, v4.2D, v5.2D, v6.2D}, [x0], #64
    st1	 {v3.2D, v4.2D, v5.2D, v6.2D}, [x0], #64
    st1	 {v3.2D, v4.2D, v5.2D, v6.2D}, [x0], #64
    st1  {v3.2D, v4.2D, v5.2D, v6.2D}, [x0], #64
    st1	 {v3.2D, v4.2D, v5.2D, v6.2D}, [x0], #64
    st1	 {v3.2D, v4.2D, v5.2D, v6.2D}, [x0], #64
    st1	 {v3.2D, v4.2D, v5.2D, v6.2D}, [x0], #64

    subs    x2, x2, #1
    bne     ddi_memset8_64
81:
    ret

#else
.global ddi_memset512
.type ddi_memset512,@function

ddi_memset512:
    cbz     x2, 81f
    lsr     x2, x2, #6
    mov   x3, x1
    mov   x4, x1

ddi_memset32_16:

	prfm  PSTL1STRM, [x0, #0]
  stp   x3, x4, [x0], #16
  stp   x3, x4, [x0], #16
  stp   x3, x4, [x0], #16
  stp   x3, x4, [x0], #16
  stp   x3, x4, [x0], #16
  stp   x3, x4, [x0], #16
  stp   x3, x4, [x0], #16
  stp   x3, x4, [x0], #16
  stp   x3, x4, [x0], #16
  stp   x3, x4, [x0], #16
  stp   x3, x4, [x0], #16
  stp   x3, x4, [x0], #16
  stp   x3, x4, [x0], #16
  stp   x3, x4, [x0], #16
  stp   x3, x4, [x0], #16
  stp   x3, x4, [x0], #16
	stp   x3, x4, [x0], #16
	stp   x3, x4, [x0], #16
	stp   x3, x4, [x0], #16
	stp   x3, x4, [x0], #16
	stp   x3, x4, [x0], #16
	stp   x3, x4, [x0], #16
	stp   x3, x4, [x0], #16
	stp   x3, x4, [x0], #16
	stp   x3, x4, [x0], #16
	stp   x3, x4, [x0], #16
	stp   x3, x4, [x0], #16
	stp   x3, x4, [x0], #16
	stp   x3, x4, [x0], #16
	stp   x3, x4, [x0], #16
	stp   x3, x4, [x0], #16
	stp   x3, x4, [x0], #16

    subs    x2, x2, #1
    bne     ddi_memset32_16
81:
    ret

#endif
/* ============================================================================
**  Function : ddi_memcpy
** ============================================================================
*/
/*!
*   @brief
*   memcpy by minimum 32x64bits unit resolution
*
*   @param addr        -   [IN] Destination address, uint64
*   @param addr        -   [IN] Source address, uint64
*   @param addr        -   [IN] number of longword(64bits)
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/
#if defined(DDI_MEMTEST_SIMD_LOAD_PAIR)
.global ddi_memcpy256
.type ddi_memcpy256,@function

ddi_memcpy256:
    cbz     x2, 82f
    lsr     x2, x2, #5

ddi_memcpy4_64:
	prfm  PLDL1STRM, [x1, #0]
    prfm  PSTL1STRM, [x0, #0]
    ld1  {v3.2D, v4.2D, v5.2D, v6.2D}, [x1], #64
    st1  {v3.2D, v4.2D, v5.2D, v6.2D}, [x0], #64
    ld1  {v3.2D, v4.2D, v5.2D, v6.2D}, [x1], #64
    st1	 {v3.2D, v4.2D, v5.2D, v6.2D}, [x0], #64
    ld1  {v3.2D, v4.2D, v5.2D, v6.2D}, [x1], #64
    st1	 {v3.2D, v4.2D, v5.2D, v6.2D}, [x0], #64
    ld1  {v3.2D, v4.2D, v5.2D, v6.2D}, [x1], #64
    st1	 {v3.2D, v4.2D, v5.2D, v6.2D}, [x0], #64

    subs    x2, x2, #1
    bne     ddi_memcpy4_64
82:

#else
.global ddi_memcpy256
.type ddi_memcpy256,@function

ddi_memcpy256:
    cbz     x2, 82f
    lsr     x2, x2, #5

ddi_memcpy32:
	prfm  PLDL1STRM, [x1, #0]
	prfm  PSTL1STRM, [x0, #0]
    ldp   x3, x4, [x1], #16
    ldp   x5, x6, [x1], #16
    stp   x3, x4, [x0], #16
    stp   x5, x6, [x0], #16
    ldp   x3, x4, [x1], #16
    ldp   x5, x6, [x1], #16
    stp   x3, x4, [x0], #16
    stp   x5, x6, [x0], #16
    ldp   x3, x4, [x1], #16
    ldp   x5, x6, [x1], #16
    stp   x3, x4, [x0], #16
    stp   x5, x6, [x0], #16
    ldp   x3, x4, [x1], #16
    ldp   x5, x6, [x1], #16
    stp   x3, x4, [x0], #16
    stp   x5, x6, [x0], #16
    ldp   x3, x4, [x1], #16
    ldp   x5, x6, [x1], #16
    stp   x3, x4, [x0], #16
    stp   x5, x6, [x0], #16
    ldp   x3, x4, [x1], #16
    ldp   x5, x6, [x1], #16
    stp   x3, x4, [x0], #16
    stp   x5, x6, [x0], #16
    ldp   x3, x4, [x1], #16
    ldp   x5, x6, [x1], #16
    stp   x3, x4, [x0], #16
    stp   x5, x6, [x0], #16
    ldp   x3, x4, [x1], #16
    ldp   x5, x6, [x1], #16
    stp   x3, x4, [x0], #16
    stp   x5, x6, [x0], #16

    subs    x2, x2, #1
    bne     ddi_memcpy32
82:
    ret
#endif

/* ============================================================================
**  Function : ddi_memcpy
** ============================================================================
*/
/*!
*   @brief
*   General memcpy
*
*   @param addr        -   [IN] Destination address, uint64
*   @param addr        -   [IN] Source address, uint64
*   @param addr        -   [IN] size
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/
#if defined(DDI_MEMTEST_SIMD_LOAD_PAIR)

.global ddi_memcpy
.type ddi_memcpy,@function

ddi_memcpy:
    and   x5, x2, #0x1F
    subs  x2, x2, x5
    cbz   x5, 1f

3:
    ldr   x3, [x1], #8
    str   x3, [x0], #8
    subs  x5, x5, #1
    bne   3b


1:
    cbz   x2, 83f
2:
	prfm  PLDL1STRM, [x1, #0]
	prfm  PSTL1STRM, [x0, #0]
    ld1  {v3.2D, v4.2D, v5.2D, v6.2D}, [x1], #64
    st1  {v3.2D, v4.2D, v5.2D, v6.2D}, [x0], #64
    ld1  {v3.2D, v4.2D, v5.2D, v6.2D}, [x1], #64
    st1  {v3.2D, v4.2D, v5.2D, v6.2D}, [x0], #64
    ld1  {v3.2D, v4.2D, v5.2D, v6.2D}, [x1], #64
    st1  {v3.2D, v4.2D, v5.2D, v6.2D}, [x0], #64
    ld1  {v3.2D, v4.2D, v5.2D, v6.2D}, [x1], #64
    st1  {v3.2D, v4.2D, v5.2D, v6.2D}, [x0], #64    

    subs    x2, x2, #32
    bne     2b
83:
    ret

#else

.global ddi_memcpy
.type ddi_memcpy,@function

ddi_memcpy:
    and     x5, x2, #7
    subs  x2, x2, x5
    cbz     x5, 1f

3:
    ldr   x3, [x1], #8
    str   x3, [x0], #8
    subs  x5, x5, #1
    bne     3b
1:
    cbz   x2, 83f
2:

    ldp     x3, x4, [x1], #16
    stp     x3, x4, [x0], #16
    ldp     x3, x4, [x1], #16
    stp     x3, x4, [x0], #16
    ldp     x3, x4, [x1], #16
    stp     x3, x4, [x0], #16
    ldp     x3, x4, [x1], #16
    stp     x3, x4, [x0], #16

    subs    x2, x2, #8
    bne     2b
83:
    ret
#endif


/* ============================================================================
**  Function : ddi_memread
** ============================================================================
*/
/*!
*   @brief
*   memread by minimum 32x64bits unit resolution
*
*   @param addr        -   [IN] Destination value, uint64
*   @param addr        -   [IN] Source address, uint64
*   @param addr        -   [IN] number of longword(64bits)
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/
.global ddi_memread256
.type ddi_memread256,@function

ddi_memread256:
    cbz     x2, 84f
    lsr     x2, x2, #8

ddi_memread32:
	prfm  PLDL1STRM, [x1, #0]
    ldp   x3, x4, [x1], #16
    ldp   x5, x6, [x1], #16
    ldp   x3, x4, [x1], #16
    ldp   x5, x6, [x1], #16
    ldp   x3, x4, [x1], #16
    ldp   x5, x6, [x1], #16
    ldp   x3, x4, [x1], #16
    ldp   x5, x6, [x1], #16
    ldp   x3, x4, [x1], #16
    ldp   x5, x6, [x1], #16
    ldp   x3, x4, [x1], #16
    ldp   x5, x6, [x1], #16
    ldp   x3, x4, [x1], #16
    ldp   x5, x6, [x1], #16
    ldp   x3, x4, [x1], #16
    ldp   x5, x6, [x1], #16

    subs    x2, x2, #1
    bne     ddi_memread32
84:
    ret


/* ============================================================================
**  Function : ddi_memcmp
** ============================================================================
*/
/*!
*   @brief
*   general memory compare
*
*   @param addr        -   [IN] source address, uint64
*   @param addr        -   [IN] pattern address, uint64
*   @param addr        -   [IN] number of longword(64bits)
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval 0 if there is no mismatch found
*          non-0 which is address mismatch found
*
*   @sa None
*/

.global ddi_memcmp
.type ddi_memcmp,@function

ddi_memcmp:
    mov     x7, xZR
    and     x5, x2, #1
    cbz     x5, 10f
    ldr   x3, [x0], #8
    ldr   x4, [x1], #8
    EOR   x7, x3, x4
    subs    x2, x2, #1
    cbnz  x7, 13f
10:
  cbz     x2, 85f
11:
    ldp     x3, x4, [x0], #16
    ldp     x5, x6, [x1], #16
    EOR     x7, x3, x5
    cbnz    x7, 12f
    EOR     x7, x4, x6
    cbnz    x7, 13f
    subs    x2, x2, #2
    bne     11b
    MOV     x0, xZR
    b       85f
12:
    SUB     x0, x0 , #8
13:
    SUB     x0, x0 , #8
85:
    ret

/* ============================================================================
**  Function : ddi_memcmptoval
** ============================================================================
*/
/*!
*   @brief
*   memcmp to specific value minimum 32x64bits unit resolution
*
*   @param addr        -   [IN] source address, uint64
*   @param addr        -   [IN] comparing value, uint64
*   @param addr        -   [IN] number of longword(64bits)
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval 0 if there is no mismatch found
*          non-0 which is address mismatch found
*
*   @sa None
*/

.global ddi_memcmptoval
.type ddi_memcmptoval,@function

ddi_memcmptoval:
    mov     x7, xZR
    and     x5, x2, #1
    cbz     x5, 20f
    ldr   x3, [x0], #8
    EOR   x7, x3, x1
    subs    x2, x2, #1
    cbnz  x7, 23f
20:
  cbz     x2, 86f
21:
    ldp     x3, x4, [x0], #16
    EOR     x7, x3, x1
    cbnz    x7, 22f
    EOR     x7, x4, x1
    cbnz    x7, 23f
    subs    x2, x2, #2
    bne     21b
    MOV     x0, xZR
    b       86f
22:
    SUB     x0, x0 , #8
23:
    SUB     x0, x0 , #8
86:
    ret
