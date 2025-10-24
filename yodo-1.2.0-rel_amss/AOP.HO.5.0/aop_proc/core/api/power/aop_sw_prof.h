#ifndef AOP_SW_PROF_H
#define AOP_SW_PROF_H 

#include "comdef.h"

/*===========================================================================

                           FUNCTION DECLARATIONS

===========================================================================*/


/*===========================================================================
FUNCTION AOP_PROF_START

DESCRIPTION:
  Starts the AOP SW profiling for the task that is passed (note the priority of the task is passed, not the name of the task). This saves the temporary start time for this instance of the task
  as well as increments the count of total times the driver has been used. 

RETURN VALUE:
  None
===========================================================================*/
void aop_prof_start(
  uint32 priority,
  unsigned long t_id
);


/*===========================================================================
FUNCTION AOP_PROF_END

DESCRIPTION:
  Called when an instance of a task has either finished or been blocked/suspended. This will record the end time, as well as calculate how long the particular instance took. It will then take this
  total run time and add it to the total time run for that task, as well as compare it to the worst_case value. (Note the priority of the task is passed, not the name of the task). 

RETURN VALUE:
  None
===========================================================================*/
void aop_prof_end(
  uint32 priority,
  unsigned long t_id
);



/*===========================================================================
FUNCTION ISR_START

DESCRIPTION:
  Records the start time whenever an ISR is called. This function will associate the start time with whatever task was currently running when the ISR started.  

RETURN VALUE:
  None
===========================================================================*/
void isr_start(
  uint32 curr_pri,
  unsigned long t_id
);



/*===========================================================================
FUNCTION ISR_END

DESCRIPTION:
  Marks the end of the running of the ISR 

RETURN VALUE:
  None
===========================================================================*/
void isr_end(
  uint32 curr_pri,
  unsigned long t_id
);


/*===========================================================================
FUNCTION log_last_used

DESCRIPTION:
  Adds to the log of the most recently used tasks. This is a circular log. Takes the task name and timestamp that it started .

RETURN VALUE:
  None
===========================================================================*/
void log_last_used(
  uint32 pri,
  unsigned long t_id
);

/*===========================================================================
FUNCTION AOP_SW_PROF_INIT

DESCRIPTION:
  Sets the memory address of the structure storing AOP profiling stats to the appropriate memory location in msg ram.

RETURN VALUE:
  None
===========================================================================*/
void aop_sw_prof_init(
);


#endif /* END AOP_SW_PROF_H */ 