/*===========================================================================
                              target_services_init.c

DESCRIPTION: Init code running from ddr for target specific power utils. 
             Note: File compiled with -mlong-calls which increases code size
             significantly. Only have this in DDR.
 

Copyright (c) 2019 QUALCOMM Technologies, Inc. (QTI). All Rights Reserved.
QUALCOMM Proprietary.  Export of this technology or software is regulated
by the U.S. Government. Diversion contrary to U.S. law prohibited.
===========================================================================*/
#include "aop_fsm.h"
#include "aop_services.h"
#include "aop_interrupt_table.h"
#include "unpa/unpa_resource.h"
#include "icb_aop.h"
#include "mi_pmu.h"
#include "HALhwio.h"
#include "aop_hwio.h"
#include "target_aop_qdss.h"
#include "CoreVerify.h"
#include "time_service.h"
#include "msg_ram_layout.h"
#include "aop_sleep.h"
#include "aop_ulog.h"
#include "pdc_global_hwio.h"
#include "aop_ipc.h"
#include "ChipInfo.h"
#include "arc_runtime.h"

//---------------------------------------------------------------------------
// Extern Declarations
//---------------------------------------------------------------------------
extern struct aop_log_entry *aop_log_data;
extern icb_handle_t cnoc_handle;
extern icb_handle_t mmnoc_handle;
extern icb_handle_t debug_handle;
extern void cnoc_callback(void *callback_data, uint32_t req_data);
extern void mmnoc_callback(void *callback_data, uint32_t req_data);
extern void debug_callback(void *callback_data, uint32_t req_data);
extern void aop_log_msg32(char *message, uint32 data);
extern void aop_services_isr (int irq);
extern void aop_timer_service_init(void);
extern SERVICE_DESCRIPTOR aop_services[];
//---------------------------------------------------------------------------

#define TWENTY_FIVE_MS  (19200 * 25)             // Twenty-Five MS in ticks

#define CX_COLLAPSE_SERVICE
#define QDSS_SUPPORT_SERVICE
#define BCM_WA_SERVICE
#define RAM_DUMP_SERVICE
#define BCM_CHANGE_DONE_SERVICE
#define PMU_ERROR_SERVICE
#define GDS_ERROR_SERVICE
#define PDC_WA_SERVICE
#define PDC_GLOBAL_SERVICE
#define TIMER_NOT_NEEDED(RSC) (!((RSC) & pending_resource_sets) || ((RSC) & resource_sets_on))
#ifdef CRASHDUMP_WITH_MMNOC // This is FALSE currently on Lahaina.  
#define SERVICE_DO_CRASHDUMP_NEEDS (SERVICE_RESOURCE_DDR_W_TO | SERVICE_RESOURCE_MMNOC_W_TO)
#define SERVICE_DO_WDOG_LOG_NEEDS  (SERVICE_RESOURCE_DDR | SERVICE_RESOURCE_MMNOC)
#define RAMDUMP_RESOUCRCES_COMPLETED (ddr_completed && mmnoc_completed)
#else  // Currently, Lahaina doesn't need MMNOC for crashdump.
#define SERVICE_DO_CRASHDUMP_NEEDS (SERVICE_RESOURCE_DDR_W_TO)
#define SERVICE_DO_WDOG_LOG_NEEDS  (SERVICE_RESOURCE_DDR)
#define RAMDUMP_RESOUCRCES_COMPLETED (ddr_completed)
#endif

#undef CSYSPWRREQ_SERVICE

/**
 * <!-- target_aop_service_init -->
 *
 * @brief Initialize the Target specific needs for the workarounds.   Basically, this function
 *        sets up the services structure for the common code, and registers all the interrupts.
 *
**/
__attribute__((section("rinit_code_sec_pool1")))
void target_aop_service_init(void)
{
#ifdef LOG_SERVICES
  aop_log_data = (struct aop_log_entry *) msg_ram_get_aop_logging_area();
  log_counts = (uint32 *) &aop_log_data[NUM_AOP_LOG_ENTRIES];
  memset((void *) aop_log_data, 0, 1024);
#endif

  CORE_VERIFY(cnoc_handle = icb_get_handle_ex(ICBID_MASTER_AOSS,ICBID_SLAVE_DCC_CFG, cnoc_callback, NULL));
  CORE_VERIFY(mmnoc_handle = icb_get_handle_ex(ICBID_MASTER_MDP0, ICBID_SLAVE_MNOC_HF_MEM_NOC, mmnoc_callback, NULL));
  CORE_VERIFY(debug_handle = icb_get_handle_ex(ICBID_MASTER_AOSS, ICBID_SLAVE_SNOC_MEM_NOC_SF,  debug_callback, NULL));

  aop_services_ptr = aop_services;
  aop_services_count = NUM_SERVICES;

  aop_log_msg32("SERV_PTR", (uint32) aop_services_ptr);
  aop_log_msg32("SERV_CNT", (uint32) aop_services_count);
#ifdef CX_COLLAPSE_SERVICE
  rex_set_interrupt_vector (CX_COLLAPSE_PDC_AOP_LOCK_REQ, aop_services_isr);
  rex_clear_interrupt      (CX_COLLAPSE_PDC_AOP_LOCK_REQ);
  rex_enable_interrupt     (CX_COLLAPSE_PDC_AOP_LOCK_REQ);

  rex_set_interrupt_vector (CX_COLLAPSE_PDC_AOP_UNLOCK_REQ, aop_services_isr);
  rex_clear_interrupt      (CX_COLLAPSE_PDC_AOP_UNLOCK_REQ);
  rex_enable_interrupt     (CX_COLLAPSE_PDC_AOP_UNLOCK_REQ);
#endif
#ifdef QDSS_SUPPORT_SERVICE
  // Debug PDC wrapper
  rex_set_interrupt_vector (DBG_RSRC_REL_PDC_AOP_LOCK_REQ, aop_services_isr);
  rex_set_interrupt_vector (DBG_RSRC_REL_PDC_AOP_UNLOCK_REQ, aop_services_isr);
  rex_clear_interrupt (DBG_RSRC_REL_PDC_AOP_LOCK_REQ);
  rex_clear_interrupt (DBG_RSRC_REL_PDC_AOP_UNLOCK_REQ);

  rex_enable_interrupt (DBG_RSRC_REL_PDC_AOP_LOCK_REQ);
#endif
  // BCM workaround IRQ
#ifdef BCM_WA_SERVICE
  rex_set_interrupt_vector (BCM_IRQ_4, aop_services_isr);
  rex_clear_interrupt (BCM_IRQ_4);
  rex_enable_interrupt (BCM_IRQ_4);
#endif
#ifdef BCM_CHANGE_DONE_SERVICE
  rex_set_interrupt_vector (BCM_IRQ_1, aop_services_isr);
  rex_clear_interrupt (BCM_IRQ_1);
  rex_enable_interrupt (BCM_IRQ_1);
#endif
#ifdef PMU_ERROR_SERVICE
  rex_set_interrupt_vector (MI_PMU_ERROR_IRQ, aop_services_isr);
  rex_clear_interrupt (MI_PMU_ERROR_IRQ);
  rex_enable_interrupt (MI_PMU_ERROR_IRQ);
#endif
#ifdef GDS_ERROR_SERVICE
  rex_set_interrupt_vector (GCC_GDS_HW_CTRL_IRQ, aop_services_isr);
  rex_clear_interrupt (GCC_GDS_HW_CTRL_IRQ);
  rex_enable_interrupt (GCC_GDS_HW_CTRL_IRQ);
#endif
#ifdef RAM_DUMP_SERVICE
  rex_set_interrupt_vector(AOP_PDC_IRQ_OUT_1, (rex_isr_func_type)aop_services_isr);
  rex_clear_interrupt (AOP_PDC_IRQ_OUT_1);
  rex_enable_interrupt(AOP_PDC_IRQ_OUT_1);
#endif
#ifdef CSYSPWRREQ_SERVICE
  rex_set_interrupt_vector(QDSS_CSYSPWRUPREQ_ASSERT, (rex_isr_func_type)aop_services_isr);
  rex_clear_interrupt (QDSS_CSYSPWRUPREQ_ASSERT);
  rex_enable_interrupt(QDSS_CSYSPWRUPREQ_ASSERT);

  rex_set_interrupt_vector(QDSS_CSYSPWRUPREQ_DEASSERT, (rex_isr_func_type)aop_services_isr);
  rex_clear_interrupt (QDSS_CSYSPWRUPREQ_DEASSERT);
#endif


  rex_set_interrupt_vector (PDC_AOP_SUMMARY_IRQ, aop_services_isr);
  rex_clear_interrupt (PDC_AOP_SUMMARY_IRQ);
  rex_enable_interrupt (PDC_AOP_SUMMARY_IRQ);

  aop_timer_service_init();
}
