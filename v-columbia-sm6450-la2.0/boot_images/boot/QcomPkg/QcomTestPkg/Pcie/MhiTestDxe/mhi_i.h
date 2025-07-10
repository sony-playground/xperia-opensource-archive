#ifndef MHI_I_H
#define MHI_I_H
/**
 *  @file mhi_i.h
 *
 *  @brief This file contains the internal MHI interface.
 */
/*============================================================================
               Copyright (c) 2021 Qualcomm Technologies, Inc.
               All Rights Reserved.
               Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "mhi.h"
#include "mhi_status.h"
#include "mhi_spec.h"
#include "mhi_tgt_config.h"
#include "mhi_log.h"
#include "list.h"
#include "pcie_osal.h"
#include "pcie_host_r.h"
#include "com_dtypes.h"
//#include "memheap.h"
#include <stddef.h>
#include <stdint.h>
//#include "sleep_npa.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define MHI_MAX_NUM_MSI_VECTORS 32

#define U64_UPPER(val) (((val) >> 32) & 0xffffffff)
#define U64_LOWER(val) ((val) & 0xffffffff)

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

typedef struct {
   uint64 seg_addr;
   uint64 seg_size;
}bhie_vector_table_t;

typedef struct {
   bhie_vector_table_t *bhie_vec_tbl;
}bhie_ctx_t;

typedef enum {
   MHI_PCIE_L0_LATENCY       = 0x0,        /**< PCIE L0 latency request */
   MHI_PCIE_NO_LATENCY_VOTE  = 0xDEADBEEF, /**< No vote for PCIe link */
   MHI_PCIE_MAX_LATENCY_VOTE = 0x7fffffff, /**< Force enum size to 32-bit */
} mhi_pcie_latency_vote_t;

/** Virtual address type */
typedef pcie_osal_va_t mhi_va_t;

/** Physical address type */
typedef pcie_osal_pa_t mhi_pa_t;

/** IO virtual address type */
typedef uint64 mhi_iova_t;

/** Forward declarations for structures nested in each other */
typedef struct mhi_drv_t mhi_drv_t;
typedef struct mhi_dev_t mhi_dev_t;
typedef struct mhi_logical_ctxt_t mhi_logical_ctxt_t;

/** Issue request type */
typedef struct
{
   uint32 state;     		      /**< State of last Resource node voted by client */
} mhi_issue_req_t;

/** Client context type */
typedef struct
{
   mhi_cb_t cb;       			                     /**< Client-specific callback */
   mhi_dev_t *dev;     			                     /**< Device */
   mhi_issue_req_t issue_req[MHI_MAX_NUM_NODES];    /**< issue client request */
} mhi_client_ctxt_t;

typedef struct
{
   mhi_int_cb_t cb;
   void *ctxt;
   uint32 vector;
   boolean in_use;
} mhi_msi_t;

/** Internal channel states (separate from MHI channel states) */
typedef enum
{
   MHI_CHAN_STATE_INIT,
   MHI_CHAN_STATE_OPEN,
   MHI_CHAN_STATE_DISCONNECTED,
   MHI_CHAN_STATE_CLOSING,
   MHI_CHAN_STATE_CLOSED
} mhi_chan_state_t;

/** Channel context */
typedef struct
{
   pcie_osal_sync_t sync;                 /**< Channel-level sync */
   pcie_osal_event_t ack_write;           /**< Worker thread event object */
   mhi_client_ctxt_t *client_ctxt;        /**< Client context */
   mhi_cb_t close_cb;                     /**< Close callback */
   mhi_chan_state_t state;                /**< Internal channel state */
   uint32 ch_id;                          /**< Channel ID */
   boolean in_use;
   boolean pending_ack;
   void *tr;                              /**< Buffer for transfer ring */
   uint32 num_elems;                      /**< Number of transfer ring elements */
   uintptr_t doorbell_addr;
} mhi_chan_t;

/** Channel work type */
typedef struct
{
   mhi_client_ctxt_t *client_ctxt;  /**< Client context opening the channel */
   mhi_cb_t cb;                     /**< Client callback for channel open */
   uint32 ch_id;                    /**< Channel ID */
} mhi_ch_work_t;

/** Command ring */
typedef struct
{
   mhi_cr_ctx_t ctx;
   void *buf;
   uint32 num_elems;
} mhi_cmd_ring_t;

/** Event ring */
typedef struct
{   
   uint32 num_elems;
   uint32 host_rd_index;
   void *buf;
   uintptr_t doorbell_addr;
   mhi_ev_ctx_t ctx;
} mhi_ev_ring_t;

/** Device context */
struct mhi_dev_t
{
   mhi_drv_t *drv;                        /**< Driver object */
   const mhi_dev_cfg_t *cfg;              /**< Target config */
   pcie_osal_sync_t sync;                 /**< Device-wide sync */
   pcie_osal_thread_t thread;             /**< Worker thread object */
   pcie_osal_event_t worker_event;        /**< Worker thread event object */

   list_t work_list;                      /**< Work queue */
   mhi_dev_info_t dev_info;               /**< Device info */
   uint32 mhi_ver;                        /**< MHI version */
   uint32 log_id;                         /**< ID used in logs for this device */
   mhi_state_t state;                     /**< MHI state */
   mhi_exec_env_t exec_env;               /**< Execution environment */

   mhi_va_t bar_va;
   mhi_va_t ch_db_base_va;                /**< Channel doorbell base virtual address */
   pcie_dev_t *pcie_dev_h;
   pcie_rsrc_t pcie_res;
   mhi_resources_t resources;
   mhi_msi_t msis[MHI_MAX_NUM_MSI_VECTORS];  
   uint32 active_latency_min_val;
   uint32 resume_latency_min_val;
   int32 bus_node_vote_counter;
   int32 device_wake_assert_vote;
   uint32 device_wake_state;
   int mhi_latency_vote;                    /**< MHI pcie latency vote */
   uint32 mhi_pcie_latency;                 /**< MHI pcie latency */
   pcie_osal_sync_t mhi_latency_sync;       /**< MHI pcie latency sync */
   int mhi_cpu_latency_vote;                /**< MHI cpu latency vote */
   pcie_osal_sync_t mhi_cpu_latency_sync;   /**< MHI cpu latency sync */
   pcie_osal_event_t image_dw_event;        /**< Mission mode image download event object */
   pcie_osal_event_t mhi_m0_event;	        /**< MHI M0 event object */
   boolean waiting_for_m0_event;	           /**< MHI M0 event flag */
   //npa_client_handle  mhi_npa_cpu_latency_handle;       /** < -- Resource handle for client for cpu latency   */

   mhi_cmd_ring_t cmd_ring;    /**< Command ring */

   mhi_chan_t *chans;          /**< Channels */
   mhi_ch_ctx_t *ch_ctx_arr;   /**< Channel context array (CCA) */

   mhi_ev_ring_t *evt_rings;   /**< Event Ring(s) */
   mhi_ev_ctx_t *ev_ctx_arr;   /**< Event Context Array (ECA) */

   /* BHIe fields */
   bhie_ctx_t  bhie_ctx;
};

/** Driver context */
struct mhi_drv_t
{
   const mhi_tgt_config_t *tgt_config;    /**< Target config */
   pcie_osal_sync_t sync;                 /**< Main sync for driver */
   pcie_osal_thread_t thread;             /**< Worker thread object */
   pcie_osal_event_t worker_event;        /**< Worker thread event object */
   list_t new_notify_items;               /**< List of newly-queued notify items */
   list_t notify_list;                    /**< List for notifications */
   list_t new_pcie_device_list;           /**< List of new PCIe devices */
   list_t device_list;                    /**< List of devices */
   list_t client_list;                    /**< List of clients */
   list_t closed_client_list;             /**< List of closed clients devices */
   list_t active_bus_latency_list;        /**< List of clients in order of active bus latency */
   list_t bus_resume_latency_list;        /**< List of clients in order of bus resume latency */
   boolean pcie_link_down;
   boolean client_request_pending;
   boolean sys_err; 
   boolean client_notify_sys_err;
};

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/

/**
 * This function notifies the MHI client of this device about the MHI event.
 *
 * @param[in]  event  MHI Event to notify the client about
 * @param[in]  dev    MHI device handle
 *
 * @return none
 */
void mhi_drv_notify_clients(mhi_event_t event, mhi_dev_t *dev);

mhi_dev_t *mhi_dev_handle_get(void);
#endif

