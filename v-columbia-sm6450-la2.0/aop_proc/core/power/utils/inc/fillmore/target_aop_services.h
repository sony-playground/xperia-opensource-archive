#ifndef __TARGET_AOP_SERVICES_H__
#define __TARGET_AOP_SERVICES_H__
/*===========================================================================
                              target_aop_services.h

DESCRIPTION:

Copyright (c) 2020 QUALCOMM Technologies, Inc. (QTI). All Rights Reserved.
QUALCOMM Proprietary.  Export of this technology or software is regulated
by the U.S. Government. Diversion contrary to U.S. law prohibited.
===========================================================================*/


//===========================================================================
//                     Includes and Variable Definitions
//===========================================================================

//---------------------------------------------------------------------------
// Include Files
//---------------------------------------------------------------------------
#define HUSH_TIMER_LOG  // Do not log TIMER signals/interrupts to MSGRAM

#define SERVICE_RESOURCE_CNOC       1     // Ensure CNOC is on before service
#define SERVICE_RESOURCE_DDR        2     // Ensure full path to DDR is on before service
#define SERVICE_RESOURCE_DDR_W_TO   4     // Either RESOURCE_DDR above or a TIMEOUT 2ms
#define SERVICE_RESOURCE_ABORT      8     // ABORT!
#define SERVICE_RESOURCE_MMNOC      0x10  // Ensure MMNOC is on
#define SERVICE_RESOURCE_MMNOC_W_TO 0x20  // Either RESOURCE_DDR above or a TIMEOUT 2ms
#define MAX_SERVICE_RESOURCE        0x20

#define AOP_SERVICES_PRIORITY_HI 125
#define AOP_SERVICES_PRIORITY_LO 105

#define AOP_SERVICES_TIMEOUT  (1920000)
#define NUM_TIMER_CALLBACKS 8  // qmp timeout, DDR_MGR test, ddrmgr timeout, OPSCALING POLL, AOP_SERVICES, wdog, bcm_agg, debug_cx_collapse are known users.

// The following correspond to the position in the array
enum services {
  BCM_WORKAROUND,     // 0
  CX_COLLAPSE_CHANGE, // 1
  DBG_SIG_LOCK,       // 2
  DBG_SIG_UNLOCK,     // 3
  PDC_GLOBAL_CHANGE,  // 4
  LOG_ABORT_ISR,      // 5
  CRASH_DUMP_NEEDED,  // 6
  BCM_CHANGE_DONE,    // 7
  PDC_WA,             // 8
  AOP_TIMER_CHECK,    // 9
  SYSPWRRQ_CHANGE,    // 10
  SYSTEM_IDLE,        // 11
  LCX_OL_PRE,         // 12
  PMU_ERROR,          // 13
  GDS_ERROR,          // 14
  ICB_ASYNC,          // 15
  DDR_LOG,            // 16
  NUM_SERVICES,       // 17
};

#define BCM_WORKAROUND_SEQ_SIG     (1 << BCM_WORKAROUND)
#define CX_COLLAPSE_CHANGE_SIG     (1 << CX_COLLAPSE_CHANGE)
#define DBG_SIG_PDC_LOCK_SIG       (1 << DBG_SIG_LOCK)
#define DBG_SIG_PDC_UNLOCK_SIG     (1 << DBG_SIG_UNLOCK)
#define PDC_GLOBAL_CHANGE_SIG      (1 << PDC_GLOBAL_CHANGE)
#define LOG_WATCHDOG_BITE_SIG      (1 << LOG_ABORT_ISR)
#define CRASH_DUMP_REQUIRED_SIG    (1 << CRASH_DUMP_NEEDED)
#define BCM_CHANGE_DONE_SIG        (1 << BCM_CHANGE_DONE)
#define PDC_AOP_SUMMARY_SIG        (1 << PDC_WA)
#define AOP_TIMER_CHECK_SIG        (1 << AOP_TIMER_CHECK)
#define CSYSPWRREQ_CHANGE_SIG      (1 << SYSPWRRQ_CHANGE)
#define SYSTEM_IDLE_SIG            (1 << SYSTEM_IDLE)
#define LCX_OL_PRE                 (1 << LCX_OL_PRE)
#define PMU_ERROR_SIG              (1 << PMU_ERROR)
#define GDS_ERROR_SIG              (1 << GDS_ERROR)
#define ICB_ASYNC_SIG              (1 << ICB_ASYNC)
#define DDR_LOG_SIG                (1 << DDR_LOG)

// Before adding a new signal/service above, add it to the waitmask below too
#define SERVICES_TIMER_SIGNAL      0x80000000 // Included in AOP_SERVICES_WAIT
#define RESOURCE_SIGNAL            0x40000000 // Included in AOP_SERVICES_WAIT

#define PASR_CMD_FINISHED_SIG      0x20000000 // Used only when blocked on PASR TCS

#define AOP_SERVICES_WAIT (SERVICES_TIMER_SIGNAL | RESOURCE_SIGNAL | ((1 << NUM_SERVICES)-1)) // The OR of the above signals

#define AOP_ABORT_DDRMGR_TIMEOUT        0x01        // DDR_MGR sequencer running timeout
#define AOP_ABORT_SHRM_TIMEOUT          0x02        // DDR_MGR timeout waiting for SHRM
#define AOP_ABORT_ARC_RESOURCE_TIMEOUT  0x04        // DDR_MGR timeout waiting for resources
#define AOP_ABORT_PMIC_RESOURCE_TIMEOUT 0x08        // DDR_MGR timeout waiting for resources
#define AOP_ABORT_SERVICE_TIMEOUT       0x10        // A Service has requested that we abort
#define AOP_ABORT_BUS_TIMEOUT           0x20        // Bus code requests that we abort
#define AOP_ABORT_WLAN_ABORT            0x40        // Bus code requests that we abort
#define AOP_ABORT_CLOCK_ERROR           0x80        // Clock code polling has failed.
#define AOP_ABORT_CX_COLLAPSE_TIMEOUT   0x100       // Postwork from Cx arc timeout
#define AOP_ABORT_QMP_TIMEOUT           0x200       // Servicing qmp msg queue took long
#define AOP_ABORT_PLL0_LOST_LOCK        0x400       // PLL0 lost lock
#define AOP_ABORT_DDRMGR_VOLTAGES       0x800       // DDR AUX VOLTAGE TCSs busy

#endif //__TARGET_AOP_SERVICES_H__
