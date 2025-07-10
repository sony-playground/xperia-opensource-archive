/*===========================================================================
                              aop_services.h

DESCRIPTION:

Copyright (c) 2017-2020 QUALCOMM Technologies, Inc. (QTI). All Rights Reserved.
QUALCOMM Proprietary.  Export of this technology or software is regulated
by the U.S. Government. Diversion contrary to U.S. law prohibited.
===========================================================================*/


//===========================================================================
//                     Includes and Variable Definitions
//===========================================================================

//---------------------------------------------------------------------------
// Include Files
//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rex.h"
#include "aop_fsm.h"
#include "time_service.h"
#include "target_aop_services.h"

// This code uses a very simple state machine.    When there are no requests pending, the
// IDLE State:   Used when no requests are pending
// IDLE->RESOURCE_WAIT State:  This state is entered when the first request comes in.
//   RESOURE_WAIT
//     Entry Actions:
//       Foreach Pending Request
//         Ensure any resources required to ENTER the workaround are available.
//         If they have not yet been requested, request them
//         If All Resources for Entry are available - 
//           Signal the FSM to EXIT the RESOURCE_WAIT state
//     Exit Actions:
//       Foreach Pending Request
//         If All Resources for Entry are available - 
//           Mark the request as no longer pending
//           Call the workaround
//             Note: The workaround returns any resources it may require, and may also
//                   update resources other workarounds may require.
//       Compile the list of currently required resources
//         If this set has not been voted, vote them
//       If there are any pending Requests, return to the RESOURCE_WAIT state
//       If all pending requests are done, return to the IDLE state.
//
typedef enum {
  AOP_SERVICES_IDLE,            // No Pending Requests
  AOP_SERVICES_RESOURCE_WAIT,   // Requests Pending/In Process
  NUM_SERVICES_FSM_STATES
} OPSCALING_FSM_STATES;

typedef enum {
  AOP_SERVICES_NEW            = 1, // Event sent when a new request comes in
  AOP_SERVICES_RESOURCE_READY = 2  // Event sent when a resource is READY, causes the 
                                   // FSM to evaluate if it can process any requests
} SEQUENCER_FSM_EVENTS;

typedef struct
{
  bool   enabled;
  uint64 callback_time;
  uint32  persisted_duration;
  PFV_W64  callback_fn;
} aop_task_timer_type;

typedef struct
{
  bool timer_init_done;
  uint64 min_timer;
#ifdef ATS_DEBUG
  uint64 lateness_seen;
  uint64 lateness_seen_max;
  uint64 timer_programmed;
#endif
  uint32 signals;
  rex_crit_sect_type timer_crit_sect;
  aop_task_timer_type timer_list[NUM_TIMER_CALLBACKS];
}aop_timer_service_type;

uint32_t aop_services_waitmask(void);
extern bool system_idle_check(void);
extern void aop_service_notify_idle(void);
extern void aop_service_cancel_notify_idle(void);

rex_tcb_type aop_services_tcb;

typedef struct service_descriptor {
  char     *name;
  uint32_t entry_resource_sets_needed;
  uint32_t current_resource_sets_needed;
  uint32_t (*perform_service)(void);
} SERVICE_DESCRIPTOR;

extern SERVICE_DESCRIPTOR *aop_services_ptr;
extern uint32_t           aop_services_count;

// This function is called when we have a new voltage wanted by the MC/SHUB FSM
extern void notify_new_service(uint32_t new_service);
 
// This function is called when we are notified that some resource is complete.
extern void signal_resource_done(void);
extern void target_aop_service_init(void);
void notify_new_service(uint32_t new_service);
void vote_resource_needs(uint32_t current_needs);
void aop_services_process(uint32_t rex_signals);
extern void aop_services_hipriority(void);
extern void aop_services_lopriority(void);

extern bool abort_service_now();
extern bool watchdog_interrupt_occurred;
extern void force_aop_abort(uint32_t crash_info);

#if  defined(LAHAINA_TARGET_CONFIG) || defined(cedros_TARGET_CONFIG) || defined(KODIAK_TARGET_CONFIG)
#define REQUIRES_SW_SDPM
extern void aop_services_signal_sdpm(void);
#endif

#define LOG_SERVICES

#ifdef LOG_SERVICES
#define NUM_AOP_LOG_ENTRIES (64 - ((NUM_SERVICES + 3) / 4))
volatile uint32 aop_log_index;
struct aop_log_entry {
  uint32        timestamp_lo;
  uint32        message[2];
  uint32        data;
};
uint32 *log_counts;
#endif

