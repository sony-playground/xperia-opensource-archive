#ifndef MHI_STATUS_H
#define MHI_STATUS_H
/**
 *  @file mhi_status.h
 *
 *  @brief Internal MHI status codes.
 */
/*============================================================================
               Copyright (c) 2021 Qualcomm Technologies, Inc.
               All Rights Reserved.
               Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
/** Status values used by internal APIs */
#define SUCCESS        0
#define RING_EMPTY     1
#define RING_FULL      2
#define RING_THROTTLED 3
#define TRB_INCOMPLETE 4
#define REQUESTQ_EMPTY 5
#define BADTRB         6
#define SYSERR         7
#define PENDING_EVENT  8
#define INVALIDCH      9
#define NULL_PTR       10
#define LINK_BUSY      11
#define LINK_ERROR     12
#define PENDING        13
#define CACHE_PENDING  14
#define INVALID_OFFSET 15
#define ABORT          16
#define NOMEM          17
#define ALREADY_OPEN   18
#define NOT_SUPPORTED  19
#define DISCONNECTED   20
#define ERROR          0xFFFFFFFF

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/

#endif

