/*===========================================================================
                              aop_services_init.c

DESCRIPTION:

Copyright (c) 2019 QUALCOMM Technologies, Inc. (QTI). All Rights Reserved.
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

#include "aop_fsm.h"
#include "unpa/unpa_resource.h"
#include "aop_services.h"
#include "aop_sleep.h"
#include "time_service.h"
#include "HALhwio.h"
#include "aop_hwio.h"
#include "rex.h"
#include "aop_interrupt_table.h"
#include "CoreVerify.h"
#include "pwr_utils_lvl.h"
#include "pwr_utils_lvl_target.h"
#include "cmd_db.h"
#include "qmp_msg_driver.h"
#if defined(DEBUG_LPM_VIOLATORS)
#include "lpm_violators.h"
#endif
//---------------------------------------------------------------------------
// Extern Declarations
//---------------------------------------------------------------------------
extern aop_timer_service_type ats;
extern void aop_services_isr (int irq);


extern pwr_utils_lvl_res_t *g_res;
extern size_t g_res_count;

extern pwr_utils_mol_res_t *g_res_mol;
extern size_t g_res_mol_count;

//adb debug clients
extern unpa_client *cx_adb_client;
extern unpa_client *aoss_adb_client;
//adb debug qmp cb
extern void aoss_sleep_disable( char* msg, EDGE sub );
extern void _ddr_collapse_disable( char* msg, EDGE sub );
extern void cx_collpase_disable( char* msg, EDGE sub );
extern void crash_dump_control( char* msg, EDGE sub );
extern void peg_rail_to_corner( char* msg, EDGE sub );

extern AOP_FSM aop_services_fsm;

extern void service_idle_entry (AOP_FSM *fsm, unsigned int event);
extern void service_resource_entry (AOP_FSM *fsm, unsigned int event);
extern void aop_services_main_loop(dword unused);
extern unsigned int service_resource_exit (AOP_FSM *fsm, unsigned int event, unsigned int next_state);

rex_tcb_type aop_services_tcb;
REX_DECLARE_STACK(aop_services_stack, 172 * sizeof(rex_stack_word_type));

/**
 * <!-- aop_timer_service_init -->
 *
 * @brief Initializes timer, timer isr
 *
 * @return none
 */
__attribute__((section("rinit_code_sec_pool1")))
void aop_timer_service_init(void)
{
  if (!ats.timer_init_done)
  {
    rex_init_crit_sect(&ats.timer_crit_sect);
    // Enable the QTimer interrupt
    rex_set_interrupt_vector(AOP_QTIMER_INTR_1, (rex_isr_func_type)aop_services_isr);
    rex_clear_interrupt (AOP_QTIMER_INTR_1);
    rex_enable_interrupt (AOP_QTIMER_INTR_1);
    ats.timer_init_done = TRUE;
  }
}

/**
 * <!-- pwr_utils_lvl_init -->
 *
 * @brief This function should be called during subsystem initialization time
 *        as it sets up rails and supported corner for a given target.
 */
__attribute__((section("rinit_code_sec_pool1")))
void pwr_utils_lvl_init (void)
{
  uint32 i;
  pwr_utils_lvl_res_t *res;
  const char *res_name;
  uint32 data_len;
  uint8 aux_len;

  /* When we get chip id APIs, set pointer using those */
  g_res = res_target;
  g_res_count = sizeof (res_target)/sizeof (res_target[0]);

  for (i = 0; i < g_res_count; i++)
  {
    res = &g_res[i];
    res_name = res->name;
    data_len = cmd_db_query_len (res_name);
    aux_len = (uint8)data_len;

    if (data_len == 0)
    {
      /* nothing to do - vlvls already set to NULL with count 0 at 
       * declaraion */
      continue;
    }

    res->vlvls = (uint16 *)malloc (data_len);
    CORE_VERIFY (res->vlvls != NULL);
    res->count = data_len / sizeof(uint16);

    cmd_db_query_aux_data (res_name, &aux_len, (uint8 *)res->vlvls);
    CORE_VERIFY (data_len == (uint32)aux_len);

  }
}

/**
 * <!-- pwr_utils_mol_init -->
 *
 * @brief This function should be called during subsystem initialization time
 *        as it sets up rails and mol corner for a given target.
 */
__attribute__((section("rinit_code_sec_pool1")))
void pwr_utils_mol_init (void)
{
  uint32 i;
  pwr_utils_mol_res_t *res;
  const char *res_name;
  uint32 data_len;
  uint8 aux_len;

  /* When we get chip id APIs, set pointer using those */
  g_res_mol = res_mol_target;
  g_res_mol_count = sizeof (res_mol_target)/sizeof (res_mol_target[0]);

  for (i = 0; i < g_res_mol_count; i++)
  {
    res = &g_res_mol[i];
    res_name = res->name;
    data_len = cmd_db_query_len (res_name);
    aux_len = (uint8)data_len;

    if (data_len == 0)
    {
      /* nothing to do - vlvls already set to NULL with count 0 at 
       * declaraion */
      continue;
    }

    cmd_db_query_aux_data (res_name, &aux_len, (uint8 *)&res->mol);
    CORE_VERIFY (data_len == (uint32)aux_len);
  }
}


/**
 * <!-- service_fsm_init -->
 *
 * @brief Initialize the FSM and the rex thread which will perform the work.
 *
 * @param[in] callback_data - Client data passed as a part of client registration
 * @param[in] req_data      - RPMh request id associated with this callback
 * 
**/
__attribute__((section("rinit_code_sec_pool1")))
void service_fsm_init(void)
{
  aop_fsm_init(&aop_services_fsm, NUM_SERVICES_FSM_STATES, "Workaround FSM");
  aop_fsm_init_state(&aop_services_fsm, AOP_SERVICES_IDLE,
                 &service_idle_entry, NULL, "Idle");
  aop_fsm_init_state(&aop_services_fsm, AOP_SERVICES_RESOURCE_WAIT,
                 &service_resource_entry,
                 &service_resource_exit, "Wait for Resources");

  // Add each of the events to each of the states.
  // NEW_WANT can occur at any time.
  aop_fsm_add_event(&aop_services_fsm, AOP_SERVICES_IDLE,          AOP_SERVICES_NEW,
                    FALSE, AOP_SERVICES_RESOURCE_WAIT);
  aop_fsm_add_event(&aop_services_fsm, AOP_SERVICES_RESOURCE_WAIT, AOP_SERVICES_NEW,
                    FALSE, AOP_SERVICES_RESOURCE_WAIT);

  // Resource ready should only occur if we are waiting for a resource
  aop_fsm_add_event(&aop_services_fsm, AOP_SERVICES_RESOURCE_WAIT, AOP_SERVICES_RESOURCE_READY,
                    FALSE, AOP_SERVICES_RESOURCE_WAIT);

  target_aop_service_init();

  memset(&aop_services_tcb, 0, sizeof(aop_services_tcb));
  rex_def_task(&aop_services_tcb, aop_services_stack,
               REX_STACK_SIZE(aop_services_stack),
               AOP_SERVICES_PRIORITY_LO, &aop_services_main_loop, 0);
}

/** 
 * <!-- aop_adb_debug_init() -->
 *
 * @brief adds qmp cbs for various lpm disable/enables
 *
 * @param void
 *
 * @return void
 */
__attribute__((section("rinit_code_sec_pool1")))
void aop_adb_debug_init(void)
{
	CORE_VERIFY ( MSG_SUCCESS == qmp_msg_register_cb(aoss_sleep_disable, "aoss_slp") );
	CORE_VERIFY ( MSG_SUCCESS == qmp_msg_register_cb(_ddr_collapse_disable, "ddr_mol") );
	CORE_VERIFY ( MSG_SUCCESS == qmp_msg_register_cb(cx_collpase_disable, "cx_mol") );
	CORE_VERIFY ( MSG_SUCCESS == qmp_msg_register_cb(crash_dump_control, "crash_dump") );
	//CORE_VERIFY ( MSG_SUCCESS == qmp_msg_register_cb(peg_rail_to_corner, "peg_rail") );
	
	cx_adb_client = unpa_create_client ("adb_vote", UNPA_CLIENT_REQUIRED, "cx.lvl");
 	CORE_VERIFY (cx_adb_client != NULL);
    aoss_adb_client = unpa_create_client ("adb_vote", UNPA_CLIENT_REQUIRED, "/sleep/aoss");
	CORE_VERIFY (aoss_adb_client != NULL);

#if defined(DEBUG_LPM_VIOLATORS)
	lpm_mon_init();
#endif
}
