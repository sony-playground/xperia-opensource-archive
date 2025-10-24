#ifndef AOP_SLEEP_H
#define AOP_SLEEP_H
/*===========================================================================
                             aop_sleep.h

DESCRIPTION:
  Verbose description of what is defined by this header file. Typically
  describes the service provided by the structs, macros, etc. defined in
  this file.

Copyright (c) 2016 QUALCOMM Technologies, Inc. (QTI). All Rights Reserved.  
QUALCOMM Proprietary.  Export of this technology or software is regulated 
by the U.S. Government. Diversion contrary to U.S. law prohibited.
===========================================================================*/


//===========================================================================
//                   Includes and Public Data Declarations
//===========================================================================

//---------------------------------------------------------------------------
// Include Files
//---------------------------------------------------------------------------
#include <string.h>

//---------------------------------------------------------------------------
// Constant / Define Declarations
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Type Declarations
//---------------------------------------------------------------------------
enum aop_sleep_signal_enum
{
  QMP_MESSAGE_RECVD_SIG = 1 << 0,
#if defined(DEBUG_LPM_VIOLATORS)
  LOG_LPM_VIOLATORS_REQ = 1 << 1,
#endif
  THERM_INT_RECVD_SIG = 1 << 2,
};

typedef enum aop_sleep_state_enum_type
{
  AOP_SLEEP_IDLE,
  AOP_SLEEP_WFI_ENTER,
  AOP_SLEEP_WFI_EXIT,
} aop_sleep_state_enum_type;

typedef enum
{
  AOSS_SLEEP_ALLOWED,
  AOSS_SLEEP_BLOCKED,
  AOSS_SLEEP_STATE_MAX = AOSS_SLEEP_BLOCKED,
} aoss_sleep_sw_state;

//Pointer to a function returning Void taking no parameters. Used for idle cb
typedef void (*PFV_V)(void);
//---------------------------------------------------------------------------
// Forward Declarations
//---------------------------------------------------------------------------

//===========================================================================
//                             Function Definitions
//===========================================================================

/**
 * <!-- aop_register_idle_cb -->
 *
 * @brief Register a function to be called from the idle thread after a period of time
 *
 * @param[in] period   - The number of ticks in the future to set the timer
 * @param[in] callback - The function to call.
 * 
**/
int aop_register_idle_cb(PFV_V callback);

/**
 * <!-- aop_cancel_idle_cb -->
 *
 * @brief Cancel a previously registered callback function
 *
 * @param[in] callback - The function to have been called.
 * 
**/
int aop_cancel_idle_cb(PFV_V callback);

/**
 * <!-- aop_busy -->
 *
 * @brief This function is used to prevent AOSS sleep if AOP is likely busy.
 *
 * @return none
 */
 extern uint32 aop_busy_mask;
 void aop_busy(uint32 thread_mask, bool busy);

#define VOLTAGE_FSM_MASK   0x01
#define FREQUENCY_FSM_MASK 0x02
#define BCM_MASK           0x04

#endif // AOP_SLEEP_H
