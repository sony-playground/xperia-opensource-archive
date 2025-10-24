/*===========================================================================
                              main.c

DESCRIPTION:

Copyright (c) 2016-2018 QUALCOMM Technologies, Inc. (QTI). All Rights Reserved.
QUALCOMM Proprietary.  Export of this technology or software is regulated
by the U.S. Government. Diversion contrary to U.S. law prohibited.
===========================================================================*/


//===========================================================================
//                     Includes and Variable Definitions
//===========================================================================

//---------------------------------------------------------------------------
// Include Files
//---------------------------------------------------------------------------
#include "rex.h"
#include <assert.h>
#include <string.h>

//---------------------------------------------------------------------------
// Forward Declarations
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// External References
//---------------------------------------------------------------------------
extern void init_phase_1(void);
extern void init_phase_2(void);
extern void aop_sleep_main (void);

rex_tcb_type main_idle_tcb;
REX_DECLARE_STACK(main_idle_stack, 768);

//===========================================================================
//                             Macro Definitions
//===========================================================================
#define SIG_RESUME_MAIN_IDLE   (1 << 0)
//===========================================================================
//                           Function Definitions
//===========================================================================

/**
 * <!-- pause_main_idle -->
 *
 * @brief waits on a continue signal from ddr_mgr to unblock
 *        init thread
 *
 * @return none
 */
void pause_main_idle(void)
{
  rex_wait(SIG_RESUME_MAIN_IDLE);
  rex_clr_sigs(&main_idle_tcb, SIG_RESUME_MAIN_IDLE);
}

/**
 * <!-- resume_main_idle -->
 *
 * @brief signals main_idle_tcb to proceed init
 *
 * @return none
 */
void resume_main_idle(void)
{
  rex_set_sigs(&main_idle_tcb, SIG_RESUME_MAIN_IDLE);
}


/**
 * <!-- main_idle -->
 *
 * @brief This is the idle task. All decisions of sleep are handled inside this task.
 *
 * @param 
 * @param 
 *
 * @return This function does not return from execution.
 */
void main_idle (dword param1)
{
  //spwan driver threads
  init_phase_2();
     
  while (1)
  {
    aop_sleep_main ();
  }
}

/**
 * <!-- main -->
 *
 * @brief The main entry point for the AOP software
 *
 * @return This function does not return. Execution is handed off to the main_idle task.
 */
int main(void)
{
  // Lock all interrupts until initialization is complete. Interrupts will be unlocked once the main idle
  // task stars running
  lock_ints ();
 
  //target specific init seq
  init_phase_1();
  
  // Start the first thread, and kick off the rex scheduler
  memset (&main_idle_tcb, 0, sizeof (main_idle_tcb));

  // Allow interrupts
  unlock_ints ();

  rex_def_task (&main_idle_tcb, main_idle_stack, REX_STACK_SIZE(main_idle_stack), 100, main_idle, 0);
  return 0;
}
