/*===========================================================================
                              main.c

DESCRIPTION:

Copyright (c) 2016-2019 QUALCOMM Technologies, Inc. (QTI). All Rights Reserved.
QUALCOMM Proprietary.  Export of this technology or software is regulated
by the U.S. Government. Diversion contrary to U.S. law prohibited.
===========================================================================*/


//===========================================================================
//                     Includes and Variable Definitions
//===========================================================================

//---------------------------------------------------------------------------
// Include Files
//---------------------------------------------------------------------------

#include <assert.h>
#include "cortex-m3.h"
#include "comdef.h"
#include "time_service.h"
#include "aop_interrupt_table.h"
#include "rex.h"
#include <string.h>
#include "rpmh_client.h"
#include "pdc_global.h"
#include "pdc_seq.h"
#include "pdc_tcs.h"
#include "cmd_db_int.h"
#include "cmd_db_aop.h"
#include "icb_aop.h"
#include "clock.h"
#include "dog.h"
#include "aop_mpu.h"
#include "qmp_msg_driver.h"
#include "aop_ulog.h"
#include "pm_resources_and_types.h"
#include "vrm.h"
#include "CoreVerify.h"
#include "DALStdDef.h"
#include "aop_sw_prof.h"
#include "pm_app_pwr.h"
#include "PlatformInfo.h"
#include "rinit.h"
#include "sysdbg.h"
#include "aop_settings.h"
#include "dbginfolib.h"

//===========================================================================
//                             Macro Definitions
//===========================================================================
#define AUTO_MODE_VAL     0x6

//---------------------------------------------------------------------------
//                           External References
//---------------------------------------------------------------------------
extern void pause_main_idle(void);
extern void resume_main_idle(void);
extern void aop_sleep_init (void);
extern void service_fsm_init(void);
extern void pm_init (void);
extern void vrm_task_init(void);
extern void aop_sleep_main (void);
extern void ddr_mgr_init(void);
extern void pdcTcs_initialize(void);
extern void arc_init (void);
extern void pwr_utils_lvl_init (void);
extern void pwr_utils_mol_init (void);
extern void arc_test (void);
extern void cpr_init (void);
extern void cpr_extra_init(void);
extern void IPCC_Init(void);
extern void xport_qmp_init(void *arg);
#ifdef XPORT_QMP_TEST
extern void xport_qmp_test_init(void);
#endif
extern void unpa_init (void);
extern void aop_server_init (void);
extern void aop_cx_collapse_init (void);
extern void msg_ram_init (void);
extern void arc_runtime_init (void);
extern void dacc_init(void);
extern void msg_ram_set_boot_cookie (void);
extern void msg_ram_set_boot_time (uint64 start_time, uint64 end_time);
extern void aop_sleep_stats_init (void);
extern void qmp_msg_init(void);
extern void QDSSInit(void);
extern void aop_qdss_init (void);
extern void lpi_mx_scaling(void);
extern DALResult ChipInfo_Init(void);
extern void pil_driver_init(void);
extern void timer_service_late_init(void);
extern void pre_rpmh_init_reset(void);
extern void arc_thermal_ol_init(void);
extern void aop_adb_debug_init(void);

extern void aop_reclaim_code_ram_pool(void);
extern void mode_disablement_init(void);
void debug_init (void);
extern void aop_cx_ret_init(void);
extern void gpu_acd_init(void);

extern void aop_cpr_reclaim_code_ram_pool(void);
extern void ACAOPInit(void);
extern void pdc_tcs_qmp_init(void);

uint64_t start_boot_time;

/**
 * <!-- set_pmic_modes -->
 *
 * @brief Sets the pmic mode for system rails - CX, MX and EBI to auto mode
 *
 * @return none
 */
__attribute__((section("rinit_code_sec_pool1")))
void set_pmic_modes (void)
{
  CORE_VERIFY (vrm_arc_drv_mode_update ("vrm.cx", AUTO_MODE_VAL) == VRM_SUCCESS);

  CORE_VERIFY (vrm_arc_drv_mode_update ("vrm.mx", AUTO_MODE_VAL) == VRM_SUCCESS);

  CORE_VERIFY (vrm_arc_drv_mode_update ("vrm.ebi", AUTO_MODE_VAL) == VRM_SUCCESS);
}


/**
 * <!-- init_phase_1 -->
 *
 * @brief unthreaded init sequence
 *
 * @return none
 */
__attribute__((section("rinit_code_sec_pool1")))
void init_phase_1(void)
{
	int ret_val;
  /* Timer service init */
  time_service_init ();

  start_boot_time = time_service_now();

  /* Enable MPU to detect null pointer dereference and stack overflow */
  aop_mpu_init ();

  /* Populate chip info*/
  ChipInfo_Init();
  PlatformInfo_Init();

  /* Verify xPU configurations */
  ACAOPInit();

  /* Configure AOP interrupts and register exception ISRs */
  aop_interrupt_init ();

  aop_settings_lkup_init();

    //rpmh_init_reset
  pre_rpmh_init_reset();

  /* PDC global wrapper init */
  pdc_global_init ();

  msg_ram_init();

  //store aop sw profiling stats in message ram 
  aop_sw_prof_init();

  /* PDC SEQ common (instance agnostic) init */
  pdc_seq_driver_init();

  cmd_db_aop_init ();
  cmd_db_init ();

  mode_disablement_init();

  pwr_utils_lvl_init();
  pwr_utils_mol_init();

  timer_service_late_init();

  rpmh_client_init ();

  unpa_init ();


  pm_init ();

#if !defined(KAILUA_STUBS)
  aop_reclaim_code_ram_pool();
#endif

  /* Initializing CPR HW blocks */
  cpr_init();

#if !defined(KAILUA_STUBS)
  aop_cpr_reclaim_code_ram_pool();
#endif

  /* Initializing ARC HW accelerator */
  arc_init ();

  Clock_Init();

  icb_init();

  if (dbgil_get_crashdump_options() & (DBGIL_CDO_NS_DUMP | DBGIL_CDO_SEC_FULL_DUMP | DBGIL_CDO_MINI_DUMP))
  {
    system_debug_main();
  }

  aop_server_init();

  /* Initialize PDC TCSs for various DRVs */
  pdc_tcs_init();

  aop_sleep_init();

  aop_sleep_stats_init();

  IPCC_Init();

  xport_qmp_init(NULL);

  arc_runtime_init ();

  dacc_init();

  /* All entry additions to Cmd DB must be completed prior to this call */
  cmd_db_aop_update_msg_ram_info();

  debug_init();

  QDSSInit();

  ret_val = rinit_module_init ("limits");
  CORE_VERIFY ((ret_val == RINIT_SUCCESS) ||
               (ret_val == RINIT_UNKNOWN_MODULE));
}


/**
 * <!-- init_phase_2 -->
 *
 * @brief threaded init sequence, spawns driver threads
 *
 * @return none
 */
__attribute__((section("rinit_code_sec_pool1")))
void init_phase_2(void)
{
  qmp_msg_init();
  gpu_acd_init();

  /* Need to call after qmp_msg_init */
  Clock_PostInit();

  pil_driver_init();

#ifdef XPORT_QMP_TEST
  xport_qmp_test_init();
#endif

  vrm_task_init();

  service_fsm_init();

  ddr_mgr_init();

  /* We pause this thread, to avoid a race in running icb_post_init
     concurrent with or before reinit_gcc */
  pause_main_idle();

  icb_post_init();
  gpu_acd_init();

  aop_cx_collapse_init();

  aop_qdss_init();

  aop_adb_debug_init();

  cpr_extra_init();

  /* Initialize watchdog timer */
  dog_init();

  arc_thermal_ol_init();

  pdc_tcs_qmp_init();

  /* Let other subsystems know we are open for business */
  msg_ram_set_boot_cookie();

  msg_ram_set_boot_time(start_boot_time, time_service_now());
}


