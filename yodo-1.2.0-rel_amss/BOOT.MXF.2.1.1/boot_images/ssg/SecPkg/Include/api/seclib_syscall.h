/* ====================================================================
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 * ====================================================================
*/
/**
 *  @file seclib_syscall_pub.h
 *  @brief Provide the SYSCALL API infrastructure
 */

#ifndef SECLIB_SYSCALL_H
#define SECLIB_SYSCALL_H

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include <stdint.h>
/*----------------------------------------------------------------------------
 * Documentation
 * -------------------------------------------------------------------------*/

/* SMC ID bit layout
 ___________________________________________________
|    |     |        |          |          |         |
| 31 |  30 |29----24|23------16|15-------8|7-------0|
|IRQ |AARCH|  Owner | Reserved |Service ID|  Func # |
|____|_____|________|__________|__________|_________|
                               \_________  _________/
                                         \/
                                     Command ID
*/

/*   Parameter ID bit layout
 ___________________________________________________________________________
|          |     |     |     |     |     |     |     |    |    |    |       |
|31------24|23-22|21-20|19-18|17-16|15-14|13-12|11-10|9--8|7--6|5--4|3-----0|
| Reserved | p10 | p9  | p8  | p7  | p6  | p5  | p4  | p3 | p2 | p1 | nargs |
|          |type |type |type |type |type |type |type |type|type|type|       |
|__________|_____|_____|_____|_____|_____|_____|_____|____|____|____|_______|

*/

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
/** General helper macro to create a bitmask from bits low to high. */
#define SECLIB_MASK_BITS(h,l)     ((0xffffffffu >> (UINT32_C(32) - ((h - l) + UINT32_C(1)))) << l)
/** Helper macro to extract the reserved bits from the SMC ID. */
#define SECLIB_SYSCALL_RESERVED(r0)   ((r0 & SECLIB_MASK_BITS(UINT32_C(23),UINT32_C(16))) >> UINT32_C(16))

/** Helper macro to extract the number of arguments from the parameter ID. */
#define SECLIB_SYSCALL_NUM_ARGS(r1)   (r1 & SECLIB_MASK_BITS(UINT32_C(3),UINT32_C(0)))

/** Helper macro to extract an argument type from the parameter ID; maximum 10 arguments. */
#define SECLIB_SYSCALL_ARG_TYPE(r1, n) \
  ((n<10)?((r1 & SECLIB_MASK_BITS(((n*2)+5),((n*2)+4))) >> ((n * 2) + 4)):0xFFFFFFFF)

/**
   Macro used to define an SMC ID based on the owner ID,
   service ID, and function number.
*/
#define SECLIB_SYSCALL_CREATE_SMC_ID(o, s, f) \
  ((uint32)((((o & UINT32_C(0x3f)) << UINT32_C(24) ) | (s & UINT32_C(0xff)) << UINT32_C(8)) | (f & UINT32_C(0xff))))

/** Parameter ID nargs bitmask. */
#define SECLIB_SYSCALL_PARAM_NARGS_MASK  SECLIB_MASK_BITS(UINT32_C(3),UINT32_C(0))
/** Parameter ID paramameter type bitmask. */
#define SECLIB_SYSCALL_PARAM_TYPE_MASK   SECLIB_MASK_BITS(UINT32_C(1),UINT32_C(0))

/** Internal helper macro for __SECLIB_SYSCALL_CREATE_PARAM_ID. */
#define _SECLIB_SYSCALL_CREATE_PARAM_ID(nargs, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, ...) \
  (((nargs)&SECLIB_SYSCALL_PARAM_NARGS_MASK)+ \
  (((p1)&SECLIB_SYSCALL_PARAM_TYPE_MASK)<<UINT32_C(4))+ \
  (((p2)&SECLIB_SYSCALL_PARAM_TYPE_MASK)<<UINT32_C(6))+ \
  (((p3)&SECLIB_SYSCALL_PARAM_TYPE_MASK)<<UINT32_C(8))+ \
  (((p4)&SECLIB_SYSCALL_PARAM_TYPE_MASK)<<UINT32_C(10))+ \
  (((p5)&SECLIB_SYSCALL_PARAM_TYPE_MASK)<<UINT32_C(12))+ \
  (((p6)&SECLIB_SYSCALL_PARAM_TYPE_MASK)<<UINT32_C(14))+ \
  (((p7)&SECLIB_SYSCALL_PARAM_TYPE_MASK)<<UINT32_C(16))+ \
  (((p8)&SECLIB_SYSCALL_PARAM_TYPE_MASK)<<UINT32_C(18))+ \
  (((p9)&SECLIB_SYSCALL_PARAM_TYPE_MASK)<<UINT32_C(20))+ \
  (((p10)&SECLIB_SYSCALL_PARAM_TYPE_MASK)<<UINT32_C(22)))

/** Internal helper macro for SECLIB_SYSCALL_CREATE_PARAM_ID_X */
#define __SECLIB_SYSCALL_CREATE_PARAM_ID(...) \
  _SECLIB_SYSCALL_CREATE_PARAM_ID(__VA_ARGS__, UINT32_C(0), UINT32_C(0), UINT32_C(0), UINT32_C(0), UINT32_C(0),\
                                  UINT32_C(0), UINT32_C(0), UINT32_C(0), UINT32_C(0), UINT32_C(0))

/** Macro used to create a parameter ID with no arguments. */
#define SECLIB_SYSCALL_CREATE_PARAM_ID_0 \
  __SECLIB_SYSCALL_CREATE_PARAM_ID(UINT32_C(0))
/** Macro used to create a parameter ID with one argument. */
#define SECLIB_SYSCALL_CREATE_PARAM_ID_1(p1) \
  __SECLIB_SYSCALL_CREATE_PARAM_ID(UINT32_C(1), p1)
/** Macro used to create a parameter ID with two arguments. */
#define SECLIB_SYSCALL_CREATE_PARAM_ID_2(p1, p2) \
  __SECLIB_SYSCALL_CREATE_PARAM_ID(UINT32_C(2), p1, p2)
/** Macro used to create a parameter ID with three arguments. */
#define SECLIB_SYSCALL_CREATE_PARAM_ID_3(p1, p2, p3) \
  __SECLIB_SYSCALL_CREATE_PARAM_ID(UINT32_C(3), p1, p2, p3)
/** Macro used to create a parameter ID with four arguments. */
#define SECLIB_SYSCALL_CREATE_PARAM_ID_4(p1, p2, p3, p4) \
  __SECLIB_SYSCALL_CREATE_PARAM_ID(UINT32_C(4), p1, p2, p3, p4)
/** Macro used to create a parameter ID with five arguments. */
#define SECLIB_SYSCALL_CREATE_PARAM_ID_5(p1, p2, p3, p4, p5) \
  __SECLIB_SYSCALL_CREATE_PARAM_ID(UINT32_C(5), p1, p2, p3, p4, p5)
/** Macro used to create a parameter ID with six arguments. */
#define SECLIB_SYSCALL_CREATE_PARAM_ID_6(p1, p2, p3, p4, p5, p6) \
  __SECLIB_SYSCALL_CREATE_PARAM_ID(UINT32_C(6), p1, p2, p3, p4, p5, p6)
/** Macro used to create a parameter ID with seven arguments. */
#define SECLIB_SYSCALL_CREATE_PARAM_ID_7(p1, p2, p3, p4, p5, p6, p7) \
  __SECLIB_SYSCALL_CREATE_PARAM_ID(UINT32_C(7), p1, p2, p3, p4, p5, p6, p7)
/** Macro used to create a parameter ID with eight arguments. */
#define SECLIB_SYSCALL_CREATE_PARAM_ID_8(p1, p2, p3, p4, p5, p6, p7, p8) \
  __SECLIB_SYSCALL_CREATE_PARAM_ID(UINT32_C(8), p1, p2, p3, p4, p5, p6, p7, p8)
/** Macro used to create a parameter ID with nine arguments. */
#define SECLIB_SYSCALL_CREATE_PARAM_ID_9(p1, p2, p3, p4, p5, p6, p7, p8, p9) \
  __SECLIB_SYSCALL_CREATE_PARAM_ID(UINT32_C(9), p1, p2, p3, p4, p5, p6, p7, p8, p9)
/** Macro used to create a parameter ID with ten arguments. */
#define SECLIB_SYSCALL_CREATE_PARAM_ID_10(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10) \
  __SECLIB_SYSCALL_CREATE_PARAM_ID(UINT32_C(10), p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)


/*----------------------------------------------------------------------------
 * Parameter ID values
 * -------------------------------------------------------------------------*/
#define SECLIB_SYSCALL_PARAM_TYPE_VAL              UINT32_C(0x0)
#define SECLIB_SYSCALL_PARAM_TYPE_BUF_RO           UINT32_C(0x1)
#define SECLIB_SYSCALL_PARAM_TYPE_BUF_RW           UINT32_C(0x2)

/*----------------------------------------------------------------------------
 * Owning Entity IDs (defined by ARM SMC doc)
 * -------------------------------------------------------------------------*/

/** ARM architecture call ID. */
#define SECLIB_OWNER_ARM                     UINT32_C(0)
/** CPU service call ID. */
#define SECLIB_OWNER_CPU                     UINT32_C(1)
/** SIP service call ID. */
#define SECLIB_OWNER_SIP                     UINT32_C(2)
/** OEM service call ID. */
#define SECLIB_OWNER_OEM                     UINT32_C(3)
/** Standard service call ID. */
#define SECLIB_OWNER_STD                     UINT32_C(4)

/*----------------------------------------------------------------------------
 * Service IDs
 * -------------------------------------------------------------------------*/

/* SIP service call groups */
#define SECLIB_SVC_BOOT               UINT32_C(1)       /**< Boot (cold boot/warm boot).    */
#define SECLIB_SVC_AUTH               UINT32_C(2)       /**< Message authentication         */
#define SECLIB_SVC_MINIDUMP           UINT32_C(3)       /**< Minidump                       */

/*----------------------------------------------------------------------------
 * SMC Interface Error Codes Enumaration
 * -------------------------------------------------------------------------*/
typedef enum
{
  SMC_SUCCESS                        =  0,   /**< Success, requested syscall was called. */
  SMC_ERR_UNKNOWN_SMC_ID             = -1L,  /**< ARM-defined error of 0xFFFFFFFF. */
  SMC_ERR_SYSCALL_FAILED             = -2L,  /**< Syscall function returned failure. */
  SMC_ERR_SYSCALL_NOT_AVAILABLE      = -3L,  /**< No function associated with the syscall definition. */
  SMC_ERR_RESERVED_FIELD_MBZ         = -4L,  /**< SMC ID error: reserved field must be zero. */
  SMC_ERR_NUM_ARGS_MISMATCH          = -5L,  /**< Number of arguments does not match the
                                                 function definition. */
  SMC_ERR_INDIRECT_PARAM_PTR_NOT_NS  = -6L,  /**< Indirect parameter pointer does not
                                                 point to NS memory. */
  SMC_ERR_BUF_LEN_NOT_FOUND          = -7L,  /**< No buffer length following the buffer pointer. */
  SMC_ERR_BUF_PTR_NOT_NS             = -8L,  /**< Buffer pointer does not point to NS memory. */
  SMC_ERR_PARAM_ID_MISMATCH          = -9L,  /**< Incorrect parameter ID from the NS world. */
  SMC_ERR_INVALID_PARAM_TYPE         = -10L, /**< Incorrect parameter ID type.*/
  SMC_ERR_COPY_INDIRECT_PARAM_FAILED = -11L, /**< Memcpy failed in smc handler. */
} SmcErrnoType;

/*----------------------------------------------------------------------------
                SIP service calls
 * -------------------------------------------------------------------------*/

/**
  System call to request the Pimem status and the size of the Pimem.

  @smc_id
    0x02000101

  @param_id
    0x00000000
*/
#define SECLIB_PIMEM_GET_STATUS_ID \
  SECLIB_SYSCALL_CREATE_SMC_ID(SECLIB_OWNER_SIP, SECLIB_SVC_BOOT, UINT32_C(0x1))

#define SECLIB_PIMEM_GET_STATUS_PARAM_ID \
  SECLIB_SYSCALL_CREATE_PARAM_ID_0

/**
  System call to determine whether auth is enabled.

  @smc_id
    0x02000102

  @param_id
    0x00000000
*/
#define SECLIB_AUTH_ENABLED_STATUS_ID \
  SECLIB_SYSCALL_CREATE_SMC_ID(SECLIB_OWNER_SIP, SECLIB_SVC_BOOT, UINT32_C(0x2))

#define SECLIB_AUTH_ENABLED_STATUS_PARAM_ID \
  SECLIB_SYSCALL_CREATE_PARAM_ID_0

/**
  System call to authenticate a signed binary blob of data.

  @smc_id
    0x02000201

  @param_id
    0x00000014
*/
#define SECLIB_AUTHENTICATE_SMC_ID \
  SECLIB_SYSCALL_CREATE_SMC_ID(SECLIB_OWNER_SIP, SECLIB_SVC_AUTH, UINT32_C(0x1))

#define SECLIB_AUTHENTICATE_PARAM_ID \
  SECLIB_SYSCALL_CREATE_PARAM_ID_4(SECLIB_SYSCALL_PARAM_TYPE_BUF_RO, \
                                   SECLIB_SYSCALL_PARAM_TYPE_VAL,    \
                                   SECLIB_SYSCALL_PARAM_TYPE_VAL,    \
                                   SECLIB_SYSCALL_PARAM_TYPE_VAL)

/**
  Wraps (encrypts) the input blob and returns encryption artifacts required to decrypt
  the wrapped blob.

  @smc_id
    0x02000301

  @param_id
    0x00000022
*/
#define SECLIB_WRAP_BLOB_SMC_ID \
  SECLIB_SYSCALL_CREATE_SMC_ID(SECLIB_OWNER_SIP, SECLIB_SVC_MINIDUMP, UINT32_C(0x1))

#define SECLIB_WRAP_BLOB_PARAM_ID \
  SECLIB_SYSCALL_CREATE_PARAM_ID_2(SECLIB_SYSCALL_PARAM_TYPE_BUF_RW, \
                                   SECLIB_SYSCALL_PARAM_TYPE_VAL)
#endif
