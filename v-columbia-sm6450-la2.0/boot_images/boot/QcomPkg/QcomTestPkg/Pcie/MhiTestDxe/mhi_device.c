/**
 *  @file mhi_device.c
 *
 *  @brief This file contains the device-level MHI implementation.
 */
/*============================================================================
               Copyright (c) 2021 Qualcomm Technologies, Inc.
               All Rights Reserved.
               Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "mhi_device.h"
#include "mhi_mmio.h"
#include "mhi_utils.h"
#include "mhi_link.h"
#include "Library/pcie_host_r.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define SET_REG_VAL    1
/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
/** Type of work to be performed */
typedef enum
{
   MHI_WORK_IS_IPC_MSG,    /**< IPC message; ctxt is message */
   MHI_WORK_IS_CH_OPEN,    /**< Channel open; ctxt is mhi_ch_work_t */
   MHI_WORK_IS_CH_CLOSE,   /**< Channel close */
} mhi_dev_work_type_t;

/** Work element type to queue in the work list */
typedef struct
{
   list_t link;                     /**< Link for list */
   void *ctxt;                      /**< Work context - specific to the type of work */
   mhi_dev_work_type_t work_type;   /**< Work type */
} mhi_dev_work_el_t;

/*----------------------------------------------------------------------------
 * Static Function Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/
mhi_dev_t *dev_handle;

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * -------------------------------------------------------------------------*/

/**
 * This function updates MHI state.
 *
 * @attention Context: worker thread only
 *
 * @param[in]  dev        Device context
 * @param[in]  req_state  Requested state
 *
 * @return New state (may not match requested state, e.g. SYSERR occurred)
 */
static mhi_state_t mhi_dev_update_state(mhi_dev_t *dev, mhi_state_t req_state);



/**
 * This function sets the MHI device state
 *
 * @attention Context: worker thread only
 *
 * @param[in]  dev        Device context
 * @param[in]  state      Requesting MHI device state
 *
 * @return SUCCESS indicates the operation succeeded. Other values include:
 *         * ERROR: the operation failed
 */
int32 mhi_set_device_state(mhi_dev_t *dev, mhi_state_t state);

/**
 * This function votes for PCIe L0 state
 *
 * @param[in]  dev        Device context
 * @param[in]  vote       Boolean vote
 *
 * @return SUCCESS indicates the operation succeeded. Other values include:
 *         * ERROR: the operation failed
 */
uint32 mhi_dev_vote_for_pcie_l0(mhi_dev_t *dev, boolean vote);


/* Channel start/stop routines */

static int32 mhi_dev_chan_start(mhi_dev_t *dev, uint32 ch_id)
{
   int32 status = SUCCESS;
   mhi_start_cmd_element_t *cmd_ring_el, *cmd_ring_buf = NULL;
   mhi_cmd_ring_t *cmd_ring = &(dev->cmd_ring);
   mhi_cr_ctx_t *cr_ctx = &(cmd_ring->ctx);
   uint32 wr_index, rd_index = 0;
   uintptr_t db_addr = 0;

   mhi_ev_ring_t *primary_er = &(dev->evt_rings[0]);
   mhi_ev_ctx_t *primary_er_ctxt = &(dev->ev_ctx_arr[0]);
   mhi_cmd_complete_event_t *evt_ring_el, *evt_ring_buf = NULL;
   uint32 host_rd_index, host_wr_index, dev_rd_index = 0;
   uint32 num_elems = 0;

   cmd_ring_buf = (mhi_start_cmd_element_t*) (cmd_ring->buf);
   if(!cmd_ring_buf)
   {
      MHI_LOG_HIGH("ERROR: Command ring buffer not allocated \n");
      return ERROR;
   }

   /* ToDo : have separate ring insertion helper function */
   wr_index = (cmd_ring->ctx.wp - cmd_ring->ctx.rbase)/RING_EL_SIZE;
   rd_index = (cmd_ring->ctx.rp - cmd_ring->ctx.rbase)/RING_EL_SIZE;

   MHI_LOG_HIGH("Command ring write index is %u, read index is %u\n",
                wr_index, rd_index);

   if(wr_index + 1 == rd_index)
   {
      MHI_LOG_HIGH("ERROR: Command ring is full\n");
      return ERROR;
   }

   cmd_ring_el = (mhi_start_cmd_element_t*) (cmd_ring_buf + wr_index);
   pcie_osal_memset(cmd_ring_el, 0, sizeof(*cmd_ring_el));

   /* Insert channel start command into the command ring, increment wp */
   cmd_ring_el->chid = ch_id;
   cmd_ring_el->type = MHI_RING_EL_TYPE_START_CH_CMD;
   cmd_ring_el->reliable = FALSE;
   if(wr_index == (cmd_ring->num_elems - 1))
   {
      cr_ctx->wp = cr_ctx->rbase;
   }
   else
   {
      cr_ctx->wp += RING_EL_SIZE;
   }

   db_addr = dev->bar_va + CRDB_LOWER;

   /* Ring command ring doorbell */
   mhi_mmio_ring_db(db_addr, cr_ctx->wp);

   /* ToDo: move this to asynchronous processing */
   MHI_LOG_HIGH("Rang cmd ring doorbell, waiting\n");
   pcie_osal_busywait(100 * 1000);
   MHI_LOG_HIGH("Checking for command completion\n");

   /* Poll for the command completion event on primary ER */
   evt_ring_buf = (mhi_cmd_complete_event_t*)primary_er->buf;

   num_elems = primary_er->num_elems;

   host_rd_index = primary_er->host_rd_index;
   dev_rd_index = (primary_er_ctxt->rp - primary_er_ctxt->rbase)/RING_EL_SIZE;
   host_wr_index = (primary_er_ctxt->wp - primary_er_ctxt->rbase)/RING_EL_SIZE;

   MHI_LOG_HIGH("Primary ER, Host rd index = %u, device rd index = %u\n",
                host_rd_index, dev_rd_index);

   while(host_rd_index != dev_rd_index)
   {
     evt_ring_el = evt_ring_buf + host_rd_index;

     MHI_LOG_HIGH("Device sent event of type %u\n", evt_ring_el->type);

     /* ToDo: add check for invalid event */

     if(evt_ring_el->type == MHI_RING_EL_TYPE_MHI_CMD_COMPLETE_EVENT)
     {
        MHI_LOG_HIGH("Device sent command completion event\n", evt_ring_el->type);

        if(evt_ring_el->ptr != cr_ctx->rp)
        {
           MHI_LOG_ERROR("Out of order command ring completion\n", evt_ring_el->type);
           status = ERROR;
        }

        /* Update cmd ring read pointer */
        cr_ctx->rp += RING_EL_SIZE;
        if(cr_ctx->rp >= (cr_ctx->rbase + cr_ctx->rlen))
        {
           cr_ctx->rp = cr_ctx->rbase;
        }

        if(evt_ring_el->code == MHI_CMD_CODE_SUCCESS)
        {
           MHI_LOG_HIGH("Start channel command successful!\n");
        }
        else
        {
           MHI_LOG_HIGH("Start channel command failed - completion code %u!\n",
           evt_ring_el->code);
           status = ERROR;
        }
     }

     host_rd_index = (host_rd_index + 1) % num_elems;
     host_wr_index = (host_wr_index + 1) % num_elems;
   }

   /* Update Host's cached read pointer */
   primary_er->host_rd_index = host_rd_index;

   /* Recycle these events by updating ER's write pointer, ring doorbell */
   primary_er_ctxt->wp = primary_er_ctxt->rbase + (host_wr_index * RING_EL_SIZE);
   mhi_mmio_ring_db(primary_er->doorbell_addr, primary_er_ctxt->wp);

   return status;
}

#if 0
/**
 * This function issues MHI_NOTIFY updates to clients.
 *
 * @attention Context: worker thread only
 *
 * @param[in]  dev    Device context
 * @param[in]  ch_id  Channel ID
 * @param[in]  event  Which notify event
 *
 * @return None
 */
static void mhi_dev_client_notify(mhi_dev_t *dev, uint32 ch_id, mhi_event_t event)
{
   mhi_chan_t *chan = dev->chans[ch_id];
   mhi_cb_payload_t data;

   MHI_LOG_HIGH("[0x%x][CH %u] Issuing MHI_NOTIFY event %d",
                dev->log_id,
                ch_id,
                event);

   data.op = MHI_NOTIFY;
   data.status = MHI_SUCCESS;
   data.user_data = chan->client_ctxt->cb.user_data;
   data.dev_info = dev->dev_info;
   data.op_payload.notify.event = event;
   data.ch_id = ch_id;

   chan->client_ctxt->cb.cb_func(&data);
}

/**
 * This function queues an item in the work list to be processed by the
 * worker thread and signals the worker thread to run.
 *
 * @param[in]  dev        Device context
 * @param[in]  work_type  Type of work
 * @param[in]  ctxt       Context specific to type of work
 *
 * @return SUCCESS or an error code
 */
static int32 mhi_dev_queue_work(mhi_dev_t *dev, mhi_dev_work_type_t work_type,
                                void *ctxt)
{
   mhi_dev_work_el_t *work_el = NULL;

   work_el = pcie_osal_malloc(sizeof(mhi_dev_work_el_t));
   if (work_el == NULL)
   {
      return NOMEM;
   }

   work_el->work_type = work_type;
   work_el->ctxt = ctxt;

   pcie_osal_sync_enter(&dev->sync);
   list_add_tail(&dev->work_list, &work_el->link);
   pcie_osal_sync_leave(&dev->sync);

   pcie_osal_event_signal(&dev->worker_event);

   return SUCCESS;
}
#endif

 /**
 *  This function controls the Q6 sleep latency
 *
 *  @param[in]  dev      mhi device handle
 *  @param[in]  control  control to complete/issue request
 *
 *  @return
 *  Status of the operation
 * */

uint32 mhi_vote_for_cpu_latency(mhi_dev_t *dev, boolean ctrl)
{
   #ifdef NOT_USED_IN_UEFI
   pcie_osal_sync_enter(&dev->mhi_cpu_latency_sync);


   if (ctrl == TRUE) {
      dev->mhi_cpu_latency_vote++;
   } else {
      dev->mhi_cpu_latency_vote--;
   }

   if(dev->mhi_cpu_latency_vote < 0) {
      dev->mhi_cpu_latency_vote = 0;
   }

   if (dev->mhi_cpu_latency_vote > 0) {
      /* vote for CPU lateny of 1us */
      npa_issue_required_request(dev->mhi_npa_cpu_latency_handle, 0x1);
   } else {
      npa_complete_request(dev->mhi_npa_cpu_latency_handle);
   }

   pcie_osal_sync_leave(&dev->mhi_cpu_latency_sync);
   #endif

  return MHI_SUCCESS;
}

static int32 mhi_dev_first_m0_setup(mhi_dev_t *dev)
{
   uint32 status;

   status = mhi_mmio_get_ch_db_base_addr((uintptr_t)dev->resources.mem_sections[0].va, &dev->ch_db_base_va);
   if (status != SUCCESS)
   {
      MHI_LOG_ERROR("mhi_dev_first_m0_setup: mhi_mmio_get_ch_db_base_addr failed with %d - assuming SYSERR");
      return SYSERR;
   }

   return SUCCESS;
}

/**
 * This is the main workloop for the device.
 *
 * @param[in]  ctxt  Workloop context
 *
 * @return None
 */
static int mhi_dev_worker(void *ctxt)
{
   mhi_dev_t *dev = (mhi_dev_t*)ctxt;
   //mhi_dev_work_el_t *work_el;
   //mhi_dev_work_el_t *next;
   mhi_state_t state, ret_state;
   mhi_ee_t ee;
   mhi_exec_env_t exec_en;
   int32 status;
   uint32 i;
   uint64 local_qtime;
   uint64 dev_qtime;
   mhi_chan_t *chan;
   uint32 rdata;

   for ( ; ; )
   {
      pcie_osal_event_wait(&dev->worker_event);

      MHI_LOG_MED("Worker thread active");

      mhi_vote_for_cpu_latency(dev, TRUE);

      pcie_osal_sync_enter(&dev->sync);

      status = mhi_dev_get_ee(dev, &ee);
      if (status != SUCCESS)
      {
         // pcie_dump_regs(dev->pcie_dev_h);
	      MHI_LOG_FATAL("mhi_dev_worker : mhi_dev_get_ee failed");
      }

      /* Currently giving the MHI_DEV_EE_CHANGED notification only if it is MHI_EXEC_ENV_AMSS_EE */
      if (((mhi_exec_env_t)ee != dev->exec_env) && ((ee == MHI_EE_AMSS) || (ee == MHI_EE_RDDM))) {
	 exec_en = (ee == MHI_EE_AMSS) ? MHI_EXEC_ENV_AMSS_EE : MHI_EXEC_ENV_RDDM_EE;
	 mhi_dev_update_exev_env(dev, exec_en);

         pcie_osal_sync_leave(&dev->sync);

	 /* notification about the EE update */
	 mhi_drv_notify_clients(MHI_DEV_EE_CHANGED, dev);
      } else {
	 /* TODO : currently simply updating the ee need to take care of handling others */
	 MHI_LOG_MED("mhi_dev_worker: execution environment is %d", ee);

	 if (dev->exec_env != (mhi_exec_env_t)ee) {
	    mhi_dev_update_exev_env(dev, (mhi_exec_env_t)ee);
	 }

         pcie_osal_sync_leave(&dev->sync);
      }

      pcie_osal_sync_enter(&dev->sync);

      /* handle different state transistions */
      status = mhi_get_device_state(dev, &state);
      if (status != SUCCESS) {
         MHI_LOG_ERROR("mhi_dev_worker : Failed to get the mhi device state");
         pcie_osal_sync_leave(&dev->sync);
         return MHI_ERROR;
      }
      MHI_LOG_HIGH("mhi_dev_worker : Current MHI state %d", state);

      /* update the device state only if the device state has changed */
      switch (state) {
	 case MHI_STATE_READY :
	    /* TODO: need to make the dev->state to default MHI_READY after moselle poweroff */
	    dev->state = MHI_STATE_READY;
	    dev->device_wake_state = MHI_NODE_STATE_ASSERTED;
	    ret_state = mhi_dev_update_state(dev, MHI_STATE_M0);

	    /* Initialize waiting for M0 event to false */
	    dev->waiting_for_m0_event = FALSE;

	    status = mhi_dev_first_m0_setup(dev);
	    if (status != MHI_SUCCESS)
	    {
	       MHI_LOG_FATAL("mhi_dev_worker: mhi_dev_first_m0_setup failed");
	    }
	    break;
	 case MHI_STATE_M0 :
	    MHI_LOG_MED("MHI device state updated from %d --> %d", dev->state, MHI_STATE_M0);
	    dev->state = MHI_STATE_M0;
            /* TODO: Review in Phase2 if can be abstracted at a better place ? */
	    //pcie_control_l1ss_inact_interrupt(dev->pcie_dev_h, FALSE);

	    /* signal the event only if there is any device wake request */
	    if (dev->waiting_for_m0_event == TRUE) {
	       pcie_osal_event_signal(&dev->mhi_m0_event);
	       MHI_LOG_HIGH("mhi_dev_worker : signaled M0 event");
	    }

	    status = mhi_dev_sync_time(dev, &local_qtime, &dev_qtime);
	    if (status != SUCCESS)
	    {
	       MHI_LOG_HIGH("mhi_dev_worker : mhi_dev_sync_time Failed");
	    }

	    break;
	 case MHI_STATE_M1 :
            ret_state = mhi_dev_update_state(dev, MHI_STATE_M2);

            if (dev->device_wake_state == MHI_NODE_STATE_ASSERTED) {
               MHI_LOG_HIGH("mhi_dev_worker : device_wake asserted when device requested for MHI_STATE_M2");
	    }

	    status = mhi_dev_sync_time(dev, &local_qtime, &dev_qtime);
	    if (status != SUCCESS)
	    {
	       MHI_LOG_HIGH("mhi_dev_worker : mhi_dev_sync_time Failed");
	    }

	    /* start the inactivity timer only if no client votes for PCIE bus */
            if (dev->bus_node_vote_counter == 0) {
               /* TODO: Review in Phase2 if can be abstracted at a better place ? */
	       //status = pcie_control_l1ss_inact_interrupt(dev->pcie_dev_h, TRUE);
               /* if the status is not SUCCESS, what to do here */
	    }
            break;
	 case MHI_STATE_SYSERR :
	    MHI_LOG_MED("case MHI_STATE_SYSERR");
	    if(dev->drv->client_notify_sys_err == TRUE)
		  {
	    	MHI_LOG_MED("Inform the clients");
			pcie_osal_sync_leave(&dev->sync);
			mhi_drv_notify_clients(MHI_DEV_SYS_ERR, dev);
			pcie_osal_sync_enter(&dev->sync);
			dev->drv->client_notify_sys_err = FALSE;
		  }
		break;
	 default: MHI_LOG_HIGH("mhi_dev_worker : Invalid MHI state");
      }

      pcie_osal_sync_leave(&dev->sync);

      for (i = 0; i < dev->cfg->num_chans; i++)
      {
         chan = &dev->chans[i];
         if (chan != NULL && chan->state == MHI_CHAN_STATE_OPEN && chan->pending_ack == TRUE)
         {
            status = mhi_dev_vote_for_pcie_l0(dev, TRUE);
            if (status != MHI_SUCCESS) {
               MHI_LOG_ERROR("mhi_dev_worker : voting for mhi_dev_vote_for_pcie_l0 failed");
               break;
            }

            status = mhi_mmio_read((uintptr_t)dev->ch_db_base_va, CHDB_OFFSET(i) + DB_HIGH_OFFSET, &rdata);
            if (status != MHI_SUCCESS)
            {
               MHI_LOG_ERROR("mhi_dev_worker : mhi_mmio_read failed");
               break;
            }

            status = mhi_dev_vote_for_pcie_l0(dev, FALSE);
            if (status != MHI_SUCCESS) {
               MHI_LOG_ERROR("mhi_dev_worker : remoe vote for mhi_dev_vote_for_pcie_l0 failed");
               break;
            }

            MHI_LOG_HIGH("mhi_dev_worker : rdata for chdb 0x%x chid %d", rdata, i);
            if (rdata & MHI_CHANNEL_ACK_MASK)
            {
               pcie_osal_event_signal(&chan->ack_write);
            }
         }
      }

      mhi_vote_for_cpu_latency(dev, FALSE);

      MHI_LOG_MED("Worker thread idle");
   }

   // Will never reach this point
   return MHI_SUCCESS;
}

/**
 * This function updates MHI state.
 *
 * @attention Context: worker thread only
 *
 * @param[in]  dev        Device context
 * @param[in]  req_state  Requested state
 *
 * @return New state (may not match requested state, e.g. SYSERR occurred)
 */
static mhi_state_t mhi_dev_update_state(mhi_dev_t *dev, mhi_state_t req_state)
{
   mhi_state_t prev_state;
   //int32 status;

   prev_state = dev->state;

   if (req_state == prev_state)
   {
      MHI_LOG_MED("mhi_dev_update_state : Already device is in requested state state is %d", dev->state);
      return dev->state;
   }

   mhi_set_device_state(dev, req_state);
   dev->state = req_state;
   MHI_LOG_HIGH("mhi_dev_update_state : MHI device state updated from %d --> %d", prev_state, dev->state);
   return dev->state;
}

/**
 * Interrupt handler for bhi interrupts
 */
static void bhi_msi_cb(uint32 vector, void *ctxt)
{
   mhi_dev_t *dev = (mhi_dev_t *)ctxt;

   mhi_vote_for_cpu_latency(dev, TRUE);

   MHI_LOG_HIGH("bhi_msi_cb : signaling worker thread");
   pcie_osal_event_signal(&dev->worker_event);

   mhi_vote_for_cpu_latency(dev, FALSE);
}

/**
 * Interrupt handler for mhi interrupts
 */
static void mhi_msi_cb(uint32 vector, void *ctxt)
{
   mhi_dev_t *dev = (mhi_dev_t *)ctxt;

   mhi_vote_for_cpu_latency(dev, TRUE);

   MHI_LOG_HIGH("mhi_msi_cb : signaling worker thread");
   pcie_osal_event_signal(&dev->worker_event);

   mhi_vote_for_cpu_latency(dev, FALSE);
}

void mhi_dev_update_exev_env(mhi_dev_t *dev, mhi_exec_env_t exec_env)
{
   MHI_LOG_HIGH("[0x%x] Exec env changed from %d to %d",
	 dev->log_id,
	 dev->exec_env,
	 exec_env);

   pcie_osal_sync_enter(&dev->sync);
   dev->exec_env = exec_env;
   pcie_osal_sync_leave(&dev->sync);
}

uint32 mhi_dev_vote_for_pcie_l0(mhi_dev_t *dev, boolean vote)
{
   uint32 status;

   pcie_osal_sync_enter(&dev->mhi_latency_sync);
   if (vote == TRUE) {
      dev->mhi_latency_vote++;
   } else {
      dev->mhi_latency_vote--;
   }

   if (dev->mhi_latency_vote < 0 ) {
      dev->mhi_latency_vote = 0;
   }

   pcie_osal_sync_leave(&dev->mhi_latency_sync);

   status = mhi_dev_process_bus_latency(dev);
   if (status != MHI_SUCCESS) {
      MHI_LOG_FATAL("mhi_dev_vote_for_pcie_l0 : mhi_dev_process_bus_latency failed");
      return MHI_ERROR;
   }

   return MHI_SUCCESS;
}

static void mhi_dev_msi_cb(uint32 vector, void *ctxt)
{
   mhi_msi_t *msi = ctxt;
   mhi_dev_t *dev;
   uint32 status;

   if (dev_handle == NULL) {
      MHI_LOG_ERROR("mhi_dev_msi_cb : dev handle is NULL");
      return ;
   }

   dev = dev_handle;

   /* vote for L0 */
   status = mhi_dev_vote_for_pcie_l0(dev, TRUE);
   if (status != MHI_SUCCESS) {
      MHI_LOG_FATAL("mhi_dev_msi_cb : voting for mhi_dev_vote_for_pcie_l0 failed");
      return;
   }

   msi->cb(msi->vector, msi->ctxt);

   /* remov e mhi vote for L0 */
   status =mhi_dev_vote_for_pcie_l0(dev, FALSE);
   if (status != MHI_SUCCESS) {
      MHI_LOG_FATAL("mhi_dev_msi_cb : removing vote for mhi_dev_vote_for_pcie_l0 failed");
      return;
   }
}

mhi_dev_t *mhi_dev_handle_get(void)
{
	return dev_handle;
}

/**
 * This function initializes the command ring context
 * for the specified device.
 *
 * @param[in]  dev  Device context
 *
 * @return SUCCESS or an error code
 */
static int32 mhi_dev_init_cmd_ring(mhi_dev_t *dev)
{
   int32 cr_buf_size = 0;
   int alignment = 12; /* 4KB expressed as power of two */

   dev->cmd_ring.num_elems = dev->cfg->num_cr_elems;
   cr_buf_size = dev->cmd_ring.num_elems * (RING_EL_SIZE);

   dev->cmd_ring.buf = pcie_osal_malloc_aligned(cr_buf_size, alignment);
   if(!dev->cmd_ring.buf)
   {
      MHI_LOG_ERROR("Could not allocate cmd ring buffer");
      return NOMEM;
   }

   /* Initialize Command Ring Context */
   dev->cmd_ring.ctx.rbase = (uint64)dev->cmd_ring.buf;
   dev->cmd_ring.ctx.rlen = cr_buf_size;
   dev->cmd_ring.ctx.wp = dev->cmd_ring.ctx.rbase;
   dev->cmd_ring.ctx.rp = dev->cmd_ring.ctx.rbase;

   return SUCCESS;
}

/**
 * This function initializes the event ring(s)
 * for the specified device.
 *
 * @param[in]  dev  Device context
 *
 * @return SUCCESS or an error code
 */
static int32 mhi_dev_init_evt_rings(mhi_dev_t *dev)
{
   mhi_ev_ring_t *evt_ring = NULL;
   mhi_ev_ctx_t   *evt_ring_ctxt = NULL;
   uint32 alloc_size = 0;
   uint32 num_ers = dev->cfg->num_ers;
   int32 status = ERROR;
   int32 i = 0;

   if(num_ers < 1)
   {
      return ERROR;
   }

   alloc_size = num_ers * sizeof(mhi_ev_ctx_t);
   dev->ev_ctx_arr = pcie_osal_malloc(alloc_size);
   if(!(dev->ev_ctx_arr))
   {
      goto cleanup;
   }

   alloc_size = num_ers * sizeof(mhi_ev_ring_t);
   dev->evt_rings = pcie_osal_malloc(alloc_size);
   if(!(dev->evt_rings))
   {
      goto cleanup;
   }

   for(i = 0; i < num_ers; i++)
   {
      evt_ring = &(dev->evt_rings[i]);
      evt_ring->num_elems = dev->cfg->num_er_elems;
      alloc_size = evt_ring->num_elems * RING_EL_SIZE;
      evt_ring->buf = pcie_osal_malloc(alloc_size);
      if(!(evt_ring->buf))
      {
         status = NOMEM;
         goto cleanup;
      }
      evt_ring->host_rd_index = 0;

      evt_ring_ctxt = &(dev->ev_ctx_arr[i]);
      evt_ring_ctxt->rbase = (uint64)evt_ring->buf;
      evt_ring_ctxt->rlen = evt_ring->num_elems * RING_EL_SIZE;
      evt_ring_ctxt->rp = evt_ring_ctxt->rbase;

      evt_ring_ctxt->ertype = MHI_ER_TYPE_VALID;

      /* ToDo : Initialize interrupt related config params */
      evt_ring_ctxt->msivec = 0;
      evt_ring_ctxt->intmodc = 0;
      evt_ring_ctxt->intmodt = 0;

      /* Initially Event ring is full of elements for the device
         to consume */
      evt_ring_ctxt->wp
         = evt_ring_ctxt->rbase + ((evt_ring->num_elems - 1) * RING_EL_SIZE);
   }
   status = SUCCESS;

cleanup:
   if(status != SUCCESS)
   {
      /* To do : cleanup */
   }

   return status;
}

/**
 * This function initializes the channels.
 *
 * @param[in]  dev  Device context
 *
 * @return SUCCESS or an error code
 */
static int32 mhi_dev_init_chans(mhi_dev_t *dev)
{
   mhi_chan_t *chan;
   mhi_ch_ctx_t *chan_ctx;
   //uint32 ch_id;
   size_t size;
   uint32 i;
   int32 status = ERROR;

   size = sizeof(mhi_chan_t) * dev->cfg->num_chans;
   dev->chans = pcie_osal_malloc(size);
   if (dev->chans == NULL)
   {
      return NOMEM;
   }
   pcie_osal_memset(dev->chans, 0, size);

   size = sizeof(mhi_ch_ctx_t) * dev->cfg->num_chans;
   dev->ch_ctx_arr = pcie_osal_malloc(size);
   if(dev->ch_ctx_arr == NULL)
   {
      status = NOMEM;
      goto cleanup;
   }
   pcie_osal_memset(dev->ch_ctx_arr, 0, size);

   for (i = 0; i < dev->cfg->num_chans; i++)
   {
      chan = &dev->chans[i];
      chan_ctx = &dev->ch_ctx_arr[i];

      chan->state = MHI_CHAN_STATE_INIT;
      if (pcie_osal_sync_init(&chan->sync, PCIE_OSAL_SYNC_FLAG_NONE))
      {
         return ERROR;
      }

      if (pcie_osal_event_init(&chan->ack_write))
      {
         MHI_LOG_HIGH("mhi_dev_init_chans : pcie_osal_event_init Failed for chid %d", i);
         return ERROR;
      }
      chan->pending_ack = FALSE;

      chan->num_elems = dev->cfg->num_tr_elems;

      size = chan->num_elems * RING_EL_SIZE;
      chan->tr = pcie_osal_malloc(size);
      if(chan->tr == NULL)
      {
         MHI_LOG_ERROR("mhi_dev_init_chans: Alloc failure");
         status = NOMEM;
         goto cleanup;
      }
      chan_ctx->rbase = (uint64)chan->tr;
      chan_ctx->rp = chan_ctx->wp = chan_ctx->rbase;
      chan_ctx->rlen = chan->num_elems * RING_EL_SIZE;

      /* For now, all channel operations will use event ring 1.
         Event ring 0 is used for command responses. */
      chan_ctx->erindex = 1;

      /* Odd channels are inbound, even channels are outbound */
      chan_ctx->chtype = (i % 2) ? MHI_CH_TYPE_INBOUND : MHI_CH_TYPE_OUTBOUND;

      /* Initial channel state is DISABLED */
      chan_ctx->chstate = MHI_CH_STATE_ENABLED;
   }
   status = SUCCESS;

cleanup:
   /* ToDo : cleanup for errors */
   return status;
}

/**
 * This function initializes the device MHI registers.
 *
 * @param[in]  dev  Device context
 *
 * @return SUCCESS or an error code
 */
static int32 mhi_dev_init_mmio(mhi_dev_t *dev)
{
   int32 status = ERROR;
   uint32 i = 0;
   uint32 erdb_offset, chdb_offset = 0;
   uint64 cmd_ring_ctx_addr = (UINT64) &((dev->cmd_ring).ctx);
   uint64 ev_ctx_arr_addr   = (UINT64) (dev->ev_ctx_arr);
   uint64 ch_ctx_arr_addr   = (UINT64) (dev->ch_ctx_arr);
   mhi_ev_ring_t *evt_ring = NULL;
   mhi_ev_ctx_t *er_ctx = NULL;
   mhi_chan_t *chan = NULL;

   if(!ev_ctx_arr_addr || !ch_ctx_arr_addr)
   {
      MHI_LOG_ERROR("ECA and/or CCA not initialized\n");
      status = ERROR;
      goto cleanup;
   }

   /* Initialize CRCBAP (Command Ring Context Base Addr Ptr */
   status = mhi_mmio_write(dev->bar_va,
                           CRCBAP_LOWER,
                           U64_LOWER(cmd_ring_ctx_addr));
   if(SUCCESS != status)
   {
      goto cleanup;
   }
   status = mhi_mmio_write(dev->bar_va,
                           CRCBAP_UPPER,
                           U64_UPPER(cmd_ring_ctx_addr));
   if(SUCCESS != status)
   {
      goto cleanup;
   }

   /* Initialize ECABAP (Event Context Array Base Addr Ptr) */
   status = mhi_mmio_write(dev->bar_va,
                           ECABAP_LOWER,
                           U64_LOWER(ev_ctx_arr_addr));
   if(SUCCESS != status)
   {
      goto cleanup;
   }
   status = mhi_mmio_write(dev->bar_va,
                           ECABAP_UPPER,
                           U64_UPPER(ev_ctx_arr_addr));
   if(SUCCESS != status)
   {
      goto cleanup;
   }

   /* Initiailize CCABAP (Channel Context Array Base Addr Ptr) */
   status = mhi_mmio_write(dev->bar_va,
                           CCABAP_LOWER,
                           U64_LOWER(ch_ctx_arr_addr));
   if(SUCCESS != status)
   {
      goto cleanup;
   }
   status = mhi_mmio_write(dev->bar_va,
                           CCABAP_UPPER,
                           U64_UPPER(ch_ctx_arr_addr));
   if(SUCCESS != status)
   {
      goto cleanup;
   }

   /* Initialize the number of event rings (NER) */
   status = mhi_mmio_write_reg_field(dev->bar_va,
                                     MHICFG,
                                     MHICFG_NER_MASK,
                                     MHICFG_NER_SHIFT,
                                     dev->cfg->num_ers);
   if(SUCCESS != status)
   {
      goto cleanup;
   }

   /* Initialize number of HW accelerated event rings - currently 0 */
   status = mhi_mmio_write_reg_field(dev->bar_va,
                                     MHICFG,
                                     MHICFG_NHWER_MASK,
                                     MHICFG_NHWER_SHIFT,
                                     0);
   if(SUCCESS != status)
   {
      goto cleanup;
   }

   /* Initialize MHICTRL & MHIDATA base & limit registers */
   mhi_mmio_write(dev->bar_va, MHICTRLBASE_LOWER, 0x0);
   mhi_mmio_write(dev->bar_va, MHICTRLBASE_UPPER, 0x0);
   mhi_mmio_write(dev->bar_va, MHIDATABASE_LOWER, 0x0);
   mhi_mmio_write(dev->bar_va, MHIDATABASE_UPPER, 0x0);

   mhi_mmio_write(dev->bar_va, MHICTRLLIMIT_LOWER, 0xFFFFFFFF);
   mhi_mmio_write(dev->bar_va, MHICTRLLIMIT_UPPER, 0x0);
   mhi_mmio_write(dev->bar_va, MHIDATALIMIT_LOWER, 0xFFFFFFFF);
   mhi_mmio_write(dev->bar_va, MHIDATALIMIT_UPPER, 0x0);

   /* In this implementation, we keep DEVICE_WAKE asserted.
      This may change in the future */
   mhi_mmio_device_wake_db(dev->bar_va, TRUE);

   /* Initialize Event Ring Doorbell registers */
   mhi_mmio_read(dev->bar_va, ERDBOFF, &erdb_offset);

   for(i = 0; i < dev->cfg->num_ers; i++)
   {
      evt_ring = &(dev->evt_rings[i]);
      er_ctx = &(dev->ev_ctx_arr[i]);

      /* Each event ring doorbell register is 8 bytes wide */
      evt_ring->doorbell_addr = (dev->bar_va) + erdb_offset + (8 * i);

      mhi_mmio_ring_db(evt_ring->doorbell_addr,
                       er_ctx->wp);
   }

   /* Get channel doorbell register locations */
   mhi_mmio_read(dev->bar_va, CHDBOFF_OFFSET, &chdb_offset);
   for(i = 0; i < dev->cfg->num_chans; i++)
   {
      chan = &(dev->chans[i]);

      chan->doorbell_addr = (dev->bar_va) + chdb_offset + (8 * i);
   }

cleanup:
   return status;
}

/*----------------------------------------------------------------------------
 * Externalized Function Definitions
 * -------------------------------------------------------------------------*/

/**
 * This function initializes an MHI device.
 *
 * // TODO
 * Accessing the device is not allowed in this function, since these accesses
 * may fail if the device crashes or is not in the correct state. Similarly,
 * no IPC messages to the base driver are allowed in this function for the
 * same reasons.
 *
 * @param[in]  drv          Driver context
 * @param[in]  dev_info     Device info
 * @param[in]  cfg          Configuration
 * @param[in]  pcie_dev_h   PCIe device handle
 * @param[in]  pcie_res     PCIe resources
 * @param[out] dev_ctxt     Device context
 *
 * @return SUCCESS or an error code
 */
int32 mhi_dev_init(mhi_drv_t *drv, const mhi_dev_info_t *dev_info, const mhi_dev_cfg_t *cfg,
                   pcie_dev_t *pcie_dev_h, const pcie_rsrc_t *pcie_res, mhi_dev_t **dev_ctxt)
{
   mhi_dev_t *dev;
   mhi_int_trigger_params_t trgi_parms;
   uint32 i;
   int ret;
   pcie_osal_mem_info_t mem_info;

   dev = pcie_osal_malloc(sizeof(*dev));
   if (dev == NULL)
   {
      MHI_LOG_FATAL("[0x%x] Failed to allocate dev ctxt",
                    dev_info->instance_id);
      return ERROR;
   }
   pcie_osal_memset(dev, 0, sizeof(*dev));

   dev->drv = drv;
   dev->state = MHI_STATE_RESET;
   dev->exec_env = MHI_EXEC_ENV_INVALID;
   dev->cfg = cfg;
   dev->dev_info = *dev_info;
   dev->pcie_dev_h = pcie_dev_h;
   dev->pcie_res = *pcie_res;
   dev->log_id = dev_info->instance_id;

   /* Initialize the device_wake_assert_vote to ZERO */
   dev->device_wake_assert_vote = 0;

   /* Initialize the MHI vote for PCIE L0 */
   dev->mhi_latency_vote = 0;
   dev->mhi_pcie_latency = MHI_PCIE_L0_LATENCY;

   /* Initialize the MHI cpu latency vote */
   dev->mhi_cpu_latency_vote = 0;

   /* Initialize waiting for M0 event to false */
   dev->waiting_for_m0_event = FALSE;

   for (i = 0; i < MHI_MAX_NUM_MEM_SECTIONS; i++)
   {
      mhi_mem_resource_t *mem = &dev->resources.mem_sections[i];
      pcie_mem_region_t *bar = &dev->pcie_res.bars[i];
      pcie_osal_memset(&mem_info, 0, sizeof(mem_info));

      mem->pa = bar->pa;
      mem->size = bar->sz;

      if (cfg->mhi_bar_idx == i)
      {

         ret = pcie_osal_mem_region_map(mem->pa,
                                        mem->size,
                                        PCIE_OSAL_MEM_DEVICE,
                                        &mem_info);
         if (ret)
         {
            MHI_LOG_FATAL("[0x%x] Failed to map BAR", dev->log_id);
         }

         mem->va = (void *)mem_info.va;
         dev->bar_va = mem_info.va + cfg->mhi_offset;

         MHI_LOG_HIGH("Mapped MHI MMIO. Base : 0x%x, MHI Offset : 0x%x\n",
                      mem->va,
                      dev->bar_va);

         // mem->va = (void *)dev->cfg->mhi_bar_va;
         // dev->bar_va = dev->cfg->mhi_bar_va + cfg->mhi_offset;
      }
      else
      {
         mem->va = NULL;
      }
   }

   //pcie_enable_device(dev->pcie_dev_h, 0x7);
   pcie_enable_device(dev->pcie_dev_h);


   list_init(&dev->work_list);

   ret = pcie_osal_sync_init(&dev->sync, PCIE_OSAL_SYNC_FLAG_NONE);
   if (ret)
   {
      MHI_LOG_FATAL("[0x%x] Failed to init sync", dev->log_id);
   }

   ret = pcie_osal_sync_init(&dev->mhi_latency_sync, PCIE_OSAL_SYNC_FLAG_NONE);
   if (ret)
   {
      MHI_LOG_FATAL("[0x%x] Failed to init sync", dev->log_id);
   }

   ret = pcie_osal_sync_init(&dev->mhi_cpu_latency_sync, PCIE_OSAL_SYNC_FLAG_NONE);
   if (ret)
   {
      MHI_LOG_FATAL("[0x%x] Failed to init sync", dev->log_id);
   }

   ret = pcie_osal_event_init(&dev->image_dw_event);
   if (ret)
   {
      MHI_LOG_FATAL("pcie_osal_event_init failed");
   }

   ret = pcie_osal_event_init(&dev->mhi_m0_event);
   if (ret)
   {
      MHI_LOG_FATAL("pcie_osal_event_init failed form m0_event");
   }
   ret = pcie_osal_event_init(&dev->worker_event);
   if (ret)
   {
      MHI_LOG_FATAL("[0x%x] Failed to create event", dev->log_id);
   }

   ret = pcie_osal_thread_spawn(&dev->thread,
                                cfg->thread_name,
                                mhi_dev_worker,
                                dev,
                                cfg->thread_priority);
   if (ret)
   {
      MHI_LOG_FATAL("[0x%x] Failed to spawn thread", dev->log_id);
   }

   ret = mhi_dev_int_register(dev, dev->cfg->mhi_msi_vector, mhi_msi_cb, dev, &trgi_parms);
   if (ret != SUCCESS)
   {
      MHI_LOG_FATAL("mhi_dev_int_register failed for 0x%x", dev->cfg->mhi_msi_vector);
   }

   ret = mhi_dev_int_register(dev, dev->cfg->bhi_msi_vector, bhi_msi_cb, dev, &trgi_parms);
   if (ret != SUCCESS)
   {
      MHI_LOG_FATAL("mhi_dev_int_register failed for 0x%x", dev->cfg->bhi_msi_vector);
   }

   #ifdef NOT_USED_IN_UEFI
   dev->mhi_npa_cpu_latency_handle = npa_create_sync_client(SLEEP_USEC_NORMAL_LATENCY_NODE_NAME, "mhi_dev_client", NPA_CLIENT_REQUIRED);
   if (dev->mhi_npa_cpu_latency_handle == NULL) {
      MHI_LOG_FATAL("mhi npa_create_sync_client failed");
   }
   #endif

   ret = mhi_dev_init_cmd_ring(dev);
   if (ret != SUCCESS)
   {
      MHI_LOG_FATAL("mhi_dev_init : Failed to initialize command ring");
   }

   ret = mhi_dev_init_evt_rings(dev);
   if (ret != SUCCESS)
   {
      MHI_LOG_FATAL("mhi_dev_init : Failed to initialize event rings");
   }

   ret = mhi_dev_init_chans(dev);
   if (ret != SUCCESS)
   {
      MHI_LOG_FATAL("mhi_dev_init : Failed to initialize channels");
   }

   *dev_ctxt = dev;
   dev_handle = dev;

   MHI_LOG_HIGH("[0x%x] Initialized successfully", dev->log_id);

   return SUCCESS;
}

/**
 * This function deinitializes an MHI device.
 *
 * @param[in]  dev  Device context
 *
 * @return SUCCESS or an error code
 */
int32 mhi_dev_deinit(mhi_dev_t *dev)
{
   return NOT_SUPPORTED;
}

/**
 * This function queues a channel open request.
 *
 * @param[in]  client_ctxt  Client context
 * @param[in]  ch_id        Channel ID
 * @param[in]  cb           Callback
 *
 * @return SUCCESS or an error code
 */
int32 mhi_dev_queue_chan_open(mhi_client_ctxt_t *client_ctxt, uint32 ch_id, mhi_cb_t *cb)
{
   return NOT_SUPPORTED;
}

/**
 * This function queues a channel close request.
 *
 * @param[in]  client_ctxt  Client context
 * @param[in]  ch_id        Channel ID
 * @param[in]  cb           Callback
 *
 * @return SUCCESS or an error code
 */
int32 mhi_dev_queue_chan_close(mhi_client_ctxt_t *client_ctxt, uint32 ch_id, mhi_cb_t *cb)
{
   return NOT_SUPPORTED;
}

/**
 * This function queues a transfer.
 *
 * @param[in]  client_ctxt  Client context
 * @param[in]  ch_id        Channel ID
 * @param[in]  op           Which transfer operation
 * @param[in]  data         Transfer buffer
 * @param[in]  size         Buffer size
 * @param[in]  cb           Callback
 *
 * @return SUCCESS or an error code
 */
int32 mhi_dev_queue_transfer(mhi_client_ctxt_t *client_ctxt, uint32 ch_id,
                             mhi_op_t op, void *data, size_t size, mhi_cb_t *cb)
{
   return NOT_SUPPORTED;
}

/**
 * This function allocates an MHI buffer.
 *
 * @param[in]  dev      Device context
 * @param[in]  mem_cfg  Which memory config
 * @param[out] buffer   Allocated buffer
 * @param[in]  size     Desired buffer size
 *
 * @return SUCCESS or an error code
 */
int32 mhi_dev_buffer_allocate(mhi_dev_t *dev, mhi_mem_cfg_t mem_cfg,
                              void **buffer, size_t size)
{
   return NOT_SUPPORTED;
}

/**
 * This function frees an MHI buffer.
 *
 * @param[in]  dev      Device context
 * @param[in]  mem_cfg  Which memory config
 * @param[in]  buffer   Allocated buffer
 *
 * @return SUCCESS or an error code
 */
int32 mhi_dev_buffer_free(mhi_dev_t *dev, mhi_mem_cfg_t mem_cfg, void *buffer)
{
   return NOT_SUPPORTED;
}

/**
 * This function gets the current execution environment.
 *
 * @param[in]  dev    MHI Device handle
 * @param[out] ee     Execution environment
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
int32 mhi_dev_get_ee(mhi_dev_t *dev, mhi_ee_t *ee)
{
   int32 status;
   uint32 exec_ee;

   /* vote for L0 */
   status = mhi_dev_vote_for_pcie_l0(dev, TRUE);
   if (status != MHI_SUCCESS) {
      // pcie_dump_regs(dev->pcie_dev_h);
      MHI_LOG_FATAL("mhi_dev_get_ee : voting for mhi_dev_vote_for_pcie_l0 failed");
      return ERROR;
   }

   status = mhi_mmio_bhi_get_exe_ee((uintptr_t)dev->resources.mem_sections[0].va, &exec_ee);
   if (status != MHI_SUCCESS) {
      return ERROR;
   }
   *ee = exec_ee;

   /* remove mhi vote for L0 */
   status = mhi_dev_vote_for_pcie_l0(dev, FALSE);
   if (status != MHI_SUCCESS) {
      MHI_LOG_FATAL("mhi_dev_get_ee : removing vote for mhi_dev_vote_for_pcie_l0 failed");
      return ERROR;
   }


   return SUCCESS;
}

/**
 * This function gets the curent MHI device state.
 *
 * @attention Context: worker thread only
 *
 * @param[in]  dev        Device context
 * @param[out] state      Current MHI device state
 *
 * @return SUCCESS indicates the operation succeeded. Other values include:
 *         * ERROR: the operation failed
 */
int32 mhi_get_device_state(mhi_dev_t *dev, mhi_state_t *state)
{
   int32 status;
   uint32 dev_state;

   status = mhi_mmio_get_dev_state((uintptr_t)dev->resources.mem_sections[0].va, &dev_state);
   if (status != MHI_SUCCESS) {
      return ERROR;
   }

   /* check for syserror */
   if ((dev_state & MHISTATUS_SYSERR_MASK) >> MHISTATUS_SYSERR_SHIFT) {
      *state = MHI_STATE_SYSERR;
   } else {
      *state = (dev_state & MHISTATUS_MHISTATE_MASK) >> MHISTATUS_MHISTATE_SHIFT;
   }

   MHI_LOG_MED("mhi_get_device_state : state is %d and 0x%x\n", *state, dev_state);
   return SUCCESS;
}

/**
 * This function sets the MHI device state
 *
 * @attention Context: worker thread only
 *
 * @param[in]  dev        Device context
 * @param[in]  state      Requesting MHI device state
 *
 * @return SUCCESS indicates the operation succeeded. Other values include:
 *         * ERROR: the operation failed
 */
int32 mhi_set_device_state(mhi_dev_t *dev, mhi_state_t state)
{
   int32 status;

   if (dev->state == state) {
      MHI_LOG_MED("mhi_set_device_state : Already device is in requested state state is %d", dev->state);
      return SUCCESS;
   }

   status = mhi_mmio_set_dev_state((uintptr_t)dev->resources.mem_sections[0].va, (uint32)state);
   if (status != MHI_SUCCESS) {
      return ERROR;
   }

   return SUCCESS;
}

/**
 * This function executes the BHIe image download protocol.
 *
 * @param[in]  dev    Device context
 * @param[in]  image  Pointer to image buffer
 * @param[in]  size   Size of image buffer in bytes
 *
 * @return SUCCESS indicates the operation succeeded. Other values include:
 *         ERROR: the operation failed
 *         NOMEM: memory allocation failure
 */
int mhi_dev_execute_bhie(mhi_dev_t *dev, void *image, size_t image_size)
{
   int32 status = SUCCESS;
   uint32 i = 0;

   uint64 image_addr = (uint64)image;

   bhie_vector_table_t *bhie_vector_table = (dev->bhie_ctx).bhie_vec_tbl;
   uint32 bhie_vector_table_size = 0;
   uint32 num_entries = 0;
   uint32 entry_size = 512*1024; /* Clean this up */
   uint32 last_entry_size = 0;

   uint32 bhie_offset = 0;
   uintptr_t bhie_start_addr = (uintptr_t)NULL;
   uint32 bhie_sequence_num = 0;
   uint32 bhie_tx_status = 0;
   uint32 bhie_errdbg1 = 0;

   uint32 count = 0;
   uint32 step = 500;
   uint32 timeout = 1000000;

   num_entries = image_size/entry_size;

   if(! ((dev->cfg)->uses_bhie) )
   {
      MHI_LOG_ERROR("mhi_dev_execute_bhie: Device does not support BHIe\n");
      return ERROR;
   }

   if(image_size % entry_size)
   {
      num_entries += 1;
      last_entry_size = image_size % entry_size;
   }
   else
   {
      last_entry_size = entry_size;
   }

   bhie_vector_table_size = num_entries * sizeof(bhie_vector_table_t);

   bhie_vector_table  = pcie_osal_malloc(bhie_vector_table_size);
   if(!bhie_vector_table)
   {
      MHI_LOG_ERROR("Alloc failed for bhie vector table");
      return NOMEM;
   }
   pcie_osal_memset(bhie_vector_table, 0, bhie_vector_table_size);

   MHI_LOG_HIGH("Allocated bhie vector table with %u entries. Image size = %u\n",
                num_entries, image_size);

   MHI_LOG_HIGH("mhi_dev_execute_bhie: Image addr = 0x%llx\n\n",
                image_addr);

   for(i = 0; i < num_entries - 1; i++)
   {
      bhie_vector_table[i].seg_addr = image_addr + (entry_size * i);
      bhie_vector_table[i].seg_size = entry_size;

      MHI_LOG_HIGH("BHIe vector tbl entry %u: Addr = 0x%llx, Size = %u\n",
                   i, bhie_vector_table[i].seg_addr, bhie_vector_table[i].seg_size);
   }

   bhie_vector_table[i].seg_addr = image_addr + (entry_size * i);
   bhie_vector_table[i].seg_size = last_entry_size;
   MHI_LOG_HIGH("BHIe vector tbl entry %u: Addr = 0x%llx, Size = %u\n",
                   i, bhie_vector_table[i].seg_addr, bhie_vector_table[i].seg_size);

   /* Now program the BHIe registers and trigger the image transfer */

   /* First determine where the BHIe registers are located.
      This can be obtained from the BHIEOFF (BHIe offset) register */
   status = mhi_mmio_read(dev->bar_va, BHIEOFF, &bhie_offset);
   if(SUCCESS != status)
   {
      MHI_LOG_ERROR("Could not read BHIEOFF register");
      goto cleanup;
   }

   MHI_LOG_HIGH("BHIEOFF is %u\n", bhie_offset);
   bhie_start_addr = dev->bar_va + bhie_offset;

   status = mhi_mmio_write(bhie_start_addr,
                           BHIE_TXVECADDR_LOW_OFFSET,
                           U64_LOWER((UINT64)bhie_vector_table));
   if(SUCCESS != status)
   {
      goto cleanup;
   }

   status = mhi_mmio_write(bhie_start_addr,
                           BHIE_TXVECADDR_HIGH_OFFSET,
                           U64_UPPER((UINT64)bhie_vector_table));
   if(SUCCESS != status)
   {
      goto cleanup;
   }

   status = mhi_mmio_write(bhie_start_addr,
                           BHIE_TXVECSIZE_OFFSET,
                           bhie_vector_table_size);
   if(SUCCESS != status)
   {
      goto cleanup;
   }

   bhie_sequence_num = pcie_osal_rand() & BHIE_TXVECDB_SEQNUM_MASK;
   //MHI_LOG_HIGH("Random BHIe sequence number  is %u\n", bhie_sequence_num);

   status = mhi_mmio_write_reg_field(bhie_start_addr,
                                     BHIE_TXVECDB_OFFSET,
                                     BHIE_TXVECDB_SEQNUM_MASK,
                                     BHIE_TXVECDB_SEQNUM_SHIFT,
                                     bhie_sequence_num);

   if(SUCCESS != status)
   {
      goto cleanup;
   }

   /* Wait until TXVECSTATUS is updated by the device */
   do {
      mhi_mmio_read_reg_field(bhie_start_addr,
                              BHIE_TXVECSTATUS_OFFSET,
                              BHIE_TXVECSTATUS_STATUS_MASK,
                              BHIE_TXVECSTATUS_STATUS_SHIFT,
                              &bhie_tx_status);
      pcie_osal_busywait (step);
      count = count + step;
   }while(!bhie_tx_status  && count < timeout);

   MHI_LOG_HIGH("BHIe TX status - %u\n", bhie_tx_status);

   if(BHIE_TXVECSTATUS_STATUS_XFER_COMPL != bhie_tx_status)
   {
      MHI_LOG_ERROR("ERROR: BHIe transfer failed\n", bhie_tx_status);
      status = ERROR;
   }
   else
   {
      MHI_LOG_ERROR("BHIe transfer SUCCESS\n", bhie_tx_status);
   }

   mhi_mmio_read(dev->bar_va, BHI_ERRDBG1_OFFSET, &bhie_errdbg1);

   MHI_LOG_HIGH("BHIe ERRDBG1 - %u\n", bhie_errdbg1);

cleanup:
   return status;
}

/**
 * This function transfers the the image to the device
 *
 * @param[in]  dev     Device context
 * @param[in]  image   Image to be transfered
 * @param[in]  size    Size of the image transferred
 *
 * @return SUCCESS or an error code
 */
int32 mhi_dev_transfer_image(mhi_dev_t *dev, void *image, size_t size)
{
   bhi_status_t bhi_status;
   mhi_state_t  mhi_state;
   uint32 seq_num;
   int32 status;

   //mhi_mmio_bhi_set_int_vec(dev->bar_va, dev->cfg->bhi_msi_vector);

   mhi_mmio_bhi_set_addr(dev->bar_va, (uint64)image);

   mhi_mmio_bhi_set_size(dev->bar_va, size);

   mhi_mmio_bhi_ring_db(dev->bar_va, 1);

   do
   {
      pcie_osal_sleep(5, TRUE);
      status = mhi_mmio_bhi_get_status(dev->bar_va, &bhi_status, &seq_num);
   } while (status == SUCCESS && bhi_status == BHI_STATUS_RESET);

   MHI_LOG_HIGH("mhi_dev_transfer_image: bhi_status 0x%x\n", bhi_status);

   if (status != SUCCESS)
   {
      MHI_LOG_ERROR("mhi_dev_transfer_image: status 0x%x ,seq_num 0x%x", status, seq_num);
      return status;
   }

   if (bhi_status != BHI_STATUS_COMPLETE)
   {
      MHI_LOG_ERROR("mhi_dev_transfer_image: bhi_status 0x%x ,seq_num 0x%x", bhi_status, seq_num);
      return SYSERR;
   }

   /* Wait until the device transitions to MHI READY.
      Once device is READY, initialize the device's MHI registers */
   do
   {
      pcie_osal_sleep(5, TRUE);
      status = mhi_get_device_state(dev, &mhi_state);
   } while (status == SUCCESS && mhi_state == MHI_STATE_RESET);

   MHI_LOG_HIGH("mhi_dev_transfer_image: mhi_state 0x%x\n", mhi_state);

   if(mhi_state == MHI_STATE_READY)
   {
      MHI_LOG_HIGH("mhi_dev_transfer_image: Device transitioned to READY\n");

      /* Initialize the following MHI registers
         CRCBAP - Command Ring Context Base Address Pointer
         CCABAP - Channel Context Array Base Address Pointer
         ECABAP - Event Context Array Base Address Pointer */
      status = mhi_dev_init_mmio(dev);
      if(SUCCESS != status)
      {
         MHI_LOG_ERROR("mhi_dev_transfer_image: MMIO init failed\n");
      }

      /* Set MHI State to M0 */
      mhi_dev_update_state(dev, MHI_STATE_M0);
   }

   return status;
}

/**
 * This function rings the DEVICE_WAKE doorbell
 *
 * @param[in]  client_ctxt  Client context
 * @param[in]  state        value requested by client to be written
 *             (0-de-assert, 1-assert)
 *
 * @return void
 */
void mhi_drv_vote_device_wake(mhi_handle_t dev_h, uint32 state)
{
   mhi_client_ctxt_t *client_ctxt = (mhi_client_ctxt_t *)dev_h;
   //int result;

   pcie_osal_sync_enter(&client_ctxt->dev->sync);

   if (state == MHI_NODE_STATE_ASSERTED) { /* vote for device wake assert */
      client_ctxt->dev->device_wake_assert_vote++;
   } else { /* vote for device wake de-assert */
      client_ctxt->dev->device_wake_assert_vote--;
      /* handling the negative device wake de-assert vote */
      if (client_ctxt->dev->device_wake_assert_vote < 0) {
	 client_ctxt->dev->device_wake_assert_vote = 0;
      }
   }

   /* if device_wake is asserted then wait for M0 */
   if (state == MHI_NODE_STATE_ASSERTED) {

      mhi_drv_device_wake(client_ctxt, MHI_NODE_STATE_ASSERTED);

      if (client_ctxt->dev->state != MHI_STATE_M0) {

         MHI_LOG_HIGH("mhi_drv_vote_device_wake : Waiting for M0");

         /* reset the event event */
         pcie_osal_event_reset(&client_ctxt->dev->mhi_m0_event);

         client_ctxt->dev->waiting_for_m0_event = TRUE;

         pcie_osal_sync_leave(&client_ctxt->dev->sync);

         /* Wait for MHI M0, then only return from this API */
         pcie_osal_event_wait(&client_ctxt->dev->mhi_m0_event);

         MHI_LOG_HIGH("mhi_drv_vote_device_wake : Received Waiting for M0 Event");

         //if(PCIE_OSAL_EVENT_WAIT_SUCCESS != result) {
            // pcie_dump_regs(client_ctxt->dev->pcie_dev_h);
            // MHI_LOG_FATAL("mhi_drv_vote_device_wake : Waiting for M0 Event Failed %d", result);
         // }
         pcie_osal_sync_enter(&client_ctxt->dev->sync);
         client_ctxt->dev->waiting_for_m0_event = FALSE;
      }

   } else if (state == MHI_NODE_STATE_DEASSERTED) {

      /* if no client voted for device_wake_assert */
      if (client_ctxt->dev->device_wake_assert_vote == 0) {

	 /* de-assert device wake only if the device is in M0, because if the device is in any
	  * other state then it is implicit the device wake is already de-asserted */
	 if (client_ctxt->dev->state == MHI_STATE_M0) {

	    mhi_drv_device_wake(client_ctxt, MHI_NODE_STATE_DEASSERTED);

	    /* if the PCIe link is in L1ss, then we can wait here till MHI is in M2
	     * provided there are not much transactions happening now on the link */
	 } else {

	    MHI_LOG_HIGH("mhi_drv_vote_device_wake : MHI state not in MHI_STATE_M0, current MHI state %d", client_ctxt->dev->state);
	 }
      }

   } else {

      MHI_LOG_HIGH("mhi_drv_vote_device_wake : Invalid device_wake state from client 0x%x", dev_h);
   }
   pcie_osal_sync_leave(&client_ctxt->dev->sync);
}

/**
 * This function rings the DEVICE_WAKE doorbell
 *
 * @param[in]  client_ctxt  Client context
 * @param[in]  state        value requested by client to be written
 *             (0-de-assert, 1-assert)
 *
 * @return void
 */
void mhi_drv_device_wake(mhi_handle_t dev_h, uint32 state)
{
    mhi_client_ctxt_t *client_ctxt = (mhi_client_ctxt_t *)dev_h;
    uint32 status;

    if (client_ctxt->dev->device_wake_state == state) {
     MHI_LOG_LOW("device_wake_state already in the requested state %d", state);
       return ;
    }

   /* vote for PCIE latency L0 and bring PCIE RC out of l1ss sleep */
   status = mhi_dev_vote_for_pcie_l0(client_ctxt->dev, TRUE);
   if (status != MHI_SUCCESS) {
       // pcie_dump_regs(client_ctxt->dev->pcie_dev_h);
      MHI_LOG_FATAL("mhi_drv_device_wake : voting for mhi_dev_vote_for_pcie_l0 failed");
      return;
   }

    /* Passing the bar_base as by default bar_base will point to mhi base address */
    mhi_mmio_device_wake_db((uintptr_t)client_ctxt->dev->resources.mem_sections[0].va, state);
    client_ctxt->dev->device_wake_state = state;

    MHI_LOG_HIGH("device_wake_state is set to %d", state);

   /* remove mhi vote for L0 */
   status = mhi_dev_vote_for_pcie_l0(client_ctxt->dev, FALSE);
   if (status != MHI_SUCCESS) {
      MHI_LOG_FATAL("mhi_drv_device_wake : removing vote for mhi_dev_vote_for_pcie_l0 failed");
      return;
   }
}

 /**
 * This function is used to trigger an MHI SYS ERR on the device. If clients
 * should be notified, they must immediately stop accessing the device, release
 * MHI resources, and close the device.
 *
 * @param[in]  dev_h           Device handle
 * @param[in]  notify_clients  Whether to notify clients a SYS ERR has occurred
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */

int32 mhi_dev_trigger_sys_error(mhi_dev_t *dev, boolean notify_clients)
{
	mhi_state_t ret_state;
	int32 status = SUCCESS;
	uint64 local_time, dev_time;

	if(dev == NULL)
	{
	    MHI_LOG_ERROR("mhi_dev_trigger_sys_error : Invalid Param");
		return ERROR;
	}

	/* vote for PCIE latency L0 and bring PCIE RC out of l1ss sleep */
	status = mhi_dev_vote_for_pcie_l0(dev, TRUE);
	if (status != MHI_SUCCESS) {
	   // pcie_dump_regs(dev->pcie_dev_h);
	   MHI_LOG_FATAL("mhi_dev_trigger_sys_error : voting for mhi_dev_vote_for_pcie_l0 failed");
	   return status;
	}

	pcie_osal_sync_enter(&dev->sync);

	dev->drv->client_notify_sys_err = notify_clients;

	ret_state = mhi_dev_update_state(dev, MHI_STATE_SYSERR);

	if(ret_state != MHI_STATE_SYSERR)
	{
		MHI_LOG_ERROR("ERROR : mhi_dev_trigger_sys_error : updated value not correct");
		status = ERROR;
	}

	pcie_osal_sync_leave(&dev->sync);

	/* remove mhi vote for L0 */
	status = mhi_dev_vote_for_pcie_l0(dev, FALSE);
	if (status != MHI_SUCCESS) {
	   MHI_LOG_FATAL("mhi_dev_trigger_sys_error : removing vote for mhi_dev_vote_for_pcie_l0 failed");
	   return status;
	}

	status = mhi_dev_sync_time(dev, &local_time, &dev_time);
	if (status != SUCCESS)
	{
	   MHI_LOG_HIGH("mhi_dev_trigger_sys_error : mhi_dev_sync_time Failed");
	}

	return status;
}


 /**
 * This function is used to trigger an MHI reset on the device.
 *
 * @param[in]  dev_h           Device handle
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
int32 mhi_dev_trigger_device_reset(mhi_dev_t *dev)
{
   int status = SUCCESS;

   if(dev == NULL)
   {
      MHI_LOG_ERROR("mhi_dev_trigger_device_reset : Invalid Param");
      return ERROR;
   }

   /* vote for PCIE latency L0 and bring PCIE RC out of l1ss sleep */
   status = mhi_dev_vote_for_pcie_l0(dev, TRUE);
   if (status != MHI_SUCCESS) {
      // pcie_dump_regs(dev->pcie_dev_h);
      MHI_LOG_FATAL("mhi_dev_trigger_device_reset : voting for mhi_dev_vote_for_pcie_l0 failed");
      return status;
   }

   mhi_mmio_device_reset_db((uintptr_t)dev->resources.mem_sections[0].va, SET_REG_VAL);

   MHI_LOG_HIGH("device_reset_register is set to 1");
   /* remove mhi vote for L0 */
   status = mhi_dev_vote_for_pcie_l0(dev, FALSE);
   if (status != MHI_SUCCESS) {
      MHI_LOG_FATAL("mhi_dev_trigger_device_reset : removing vote for mhi_dev_vote_for_pcie_l0 failed");
      return status;
   }

   return status;
}

 /**
 * This function is used to process the latency request from the client of this device.
 *
 * @param[in]  dev_h           Device handle
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *         * MHI_ERROR: the operation failed
 *         * MHI_INVALID_PARAM: an invalid parameter was passed
 */
uint32 mhi_dev_process_bus_latency(mhi_dev_t *dev)
{
   uint32 latency;
   pcie_status_t status = PCIE_SUCCESS;
   boolean mhi_vote = FALSE;

   /* TODO : if the MHI is in M2/M3 need to check if we can process this bus latency request,
    * need to check if there is some dependency to be maintained */

   /* NOTE : Client should first give active/resume latency, then only they have to assert/deassert bus vote */

   /* check if MHI vote for L0 is there */
   pcie_osal_sync_enter(&dev->mhi_latency_sync);

   if (dev->mhi_latency_vote > 0) {
      mhi_vote = TRUE;
      latency = dev->mhi_pcie_latency;
   }

   pcie_osal_sync_leave(&dev->mhi_latency_sync);

   if (mhi_vote == FALSE) {
      pcie_osal_sync_enter(&dev->sync);

      /* If there is no client voted for bus go with minumum of resume bus latency */
      if (dev->bus_node_vote_counter == 0) {
	 latency = dev->resume_latency_min_val;
#if 0
	 /* if the MHI is in M2 state, then start the link inactivity timer */
	 if (dev->state == MHI_STATE_M2) {
	    status = pcie_control_l1ss_inact_interrupt(dev->pcie_dev_h, TRUE);
	    if (status != PCIE_SUCCESS) {
	       MHI_LOG_ERROR("mhi_dev_process_bus_latency : pcie_control_l1ss_inact_interrupt failed");
	    }
	 }
#endif
      } else {
	 /* If there is any client voted for bus go with minumum of active bus latency */
	 latency = dev->active_latency_min_val;
      }

      pcie_osal_sync_leave(&dev->sync);
   }

   if (status != PCIE_SUCCESS) {
      MHI_LOG_ERROR("mhi_dev_process_bus_latency : failed");
      return MHI_ERROR;
   }

   /*
   status = pcie_request_link_latency(dev->pcie_dev_h, latency, PCIE_NO_STM);
   if (status != PCIE_SUCCESS) {
      MHI_LOG_LOW("mhi_dev_process_bus_latency : pcie link latency request failed");
      return MHI_ERROR;
   }*/

   /*
   if (mhi_vote == FALSE) {
      pcie_osal_sync_enter(&dev->sync);
      if (dev->bus_node_vote_counter == 0 && dev->state == MHI_STATE_M2) {
         status = pcie_control_l1ss_inact_interrupt(dev->pcie_dev_h, TRUE);
         if (status != PCIE_SUCCESS) {
            MHI_LOG_ERROR("mhi_dev_process_bus_latency : pcie_control_l1ss_inact_interrupt failed");
         }
      }
      pcie_osal_sync_leave(&dev->sync);
   }*/

   return MHI_SUCCESS;
}

/**
 * This function extract ther resources from the device handle
 *
 * @param[in]  dev        Device context
 * @param[in]  resources  Device's resources
 *
 * @return SUCCESS
 */
int32 mhi_dev_get_resources(mhi_dev_t *dev, mhi_resources_t *resources)
{
   *resources = dev->resources;

   return MHI_SUCCESS;
}

/**
 * This function registers a particular interrupt vector corresponding to every client
 *
 * @param[in]  dev              Device context
 * @param[in]  vector           Vector number
 * @param[in]  cb               Callback
 * @param[in]  ctxt             Context
 * @param[in]  trigger_params   Interrupt trigger parameters
 *
 * @return SUCCESS
 */
int32 mhi_dev_int_register(mhi_dev_t *dev, uint32 vector, mhi_int_cb_t cb,
                           void *ctxt, mhi_int_trigger_params_t *trigger_params)
{
   pcie_status_t pcie_status;
   mhi_msi_t *msi;
   uint64 iova;
   uint32 data;

   if (vector >= MHI_MAX_NUM_MSI_VECTORS)
   {
      MHI_LOG_FATAL("mhi_dev_int_register: Invalid vector number %d", vector);
      return NOT_SUPPORTED;
   }

   pcie_osal_sync_enter(&dev->sync);

   // TODO: track which client registered a particular vector?

   msi = &dev->msis[vector];
   if (msi->in_use)
   {
      pcie_osal_sync_leave(&dev->sync);
      MHI_LOG_FATAL("mhi_dev_int_register: msi cntxt is already in use %d", vector);
      return ERROR;
   }

   pcie_status = pcie_register_msi_callback(dev->pcie_dev_h,
                                            vector,
                                            mhi_dev_msi_cb,
                                            msi,
                                            &iova,
                                            &data);
   if (pcie_status != PCIE_SUCCESS)
   {
      pcie_osal_sync_leave(&dev->sync);
      MHI_LOG_FATAL("pcie_register_msi_callback failed with %d", pcie_status);
   }

   msi->cb = cb;
   msi->ctxt = ctxt;
   msi->vector = vector;
   msi->in_use = TRUE;

   trigger_params->iova = iova;
   trigger_params->data = data;
   trigger_params->vector = vector;

   pcie_osal_sync_leave(&dev->sync);

   return SUCCESS;
}

/**
 * This function is used to unregister an interrupt.
 *
 * @param[in]  dev    MHI Device handle
 * @param[in]  vector Interrupt vector number
 *
 * @return SUCCESS indicates the operation succeeded. Other values include:
 *       * NOT_SUPPORTED: If invalid vector number is passed
 */
int32 mhi_dev_int_unregister(mhi_dev_t *dev, uint32 vector)
{
   pcie_status_t pcie_status;
   mhi_msi_t *msi;

   if (vector >= MHI_MAX_NUM_MSI_VECTORS)
   {
      MHI_LOG_FATAL("mhi_dev_int_unregister: Invalid vector number %d", vector);
      return NOT_SUPPORTED;
   }

   pcie_osal_sync_enter(&dev->sync);

   msi = &dev->msis[vector];

   pcie_status = pcie_unregister_msi_callback(dev->pcie_dev_h, msi->vector, msi->cb);

   if (pcie_status != PCIE_SUCCESS)
   {
      pcie_osal_sync_leave(&dev->sync);
      MHI_LOG_FATAL("pcie_unregister_msi_callback failed with %d", pcie_status);
      return ERROR;
   }

   msi->cb = NULL;
   msi->ctxt = NULL;
   msi->vector = MHI_MAX_NUM_MSI_VECTORS;
   msi->in_use = FALSE;

   pcie_osal_sync_leave(&dev->sync);

   return SUCCESS;
}

/**
 * This function is used to synchronize time between host and device by capturing
 * the corresponding timestamps.
 *
 * @param[in]  dev    MHI Device handle
 * @param[out] local_ticks  Host time in ticks
 * @param[out] dev_ticks    Device time in ticks
 *
 * @return SUCCESS indicates the operation succeeded. Other values include:
 *       * NOT_SUPPORTED: If invalid vector number is passed
 */
int32 mhi_dev_sync_time(mhi_dev_t *dev, uint64 *local_ticks, uint64 *dev_ticks)
{
   int status;
   uint32 qtime_low;
   uint32 qtime_high;
   uint64 dev_time_aggre;

   /* TODO : vote for device wake assert */
   status = mhi_dev_vote_for_pcie_l0(dev, TRUE);
   if (status != MHI_SUCCESS) {
      // pcie_dump_regs(dev->pcie_dev_h);
      MHI_LOG_FATAL("mhi_dev_sync_time : voting for mhi_dev_vote_for_pcie_l0 failed");
      return ERROR;
   }

   *local_ticks = pcie_osal_get_systime_ticks();
   mhi_mmio_read((uintptr_t)dev->resources.mem_sections[0].va, PCIE_MHI_QTIMER_LOW_OFFSET, &qtime_low);
   mhi_mmio_read((uintptr_t)dev->resources.mem_sections[0].va, PCIE_MHI_QTIMER_HIGH_OFFSET, &qtime_high);
   dev_time_aggre = qtime_high;
   dev_time_aggre = ((dev_time_aggre << 32) | qtime_low);
   *dev_ticks = dev_time_aggre;

   MHI_LOG_HIGH("mhi_dev_time_sync : local time tick : 0x%llx\n", *local_ticks);
   MHI_LOG_HIGH("mhi_dev_time_sync : device time tick : 0x%llx\n", *dev_ticks);
//   MHI_LOG_HIGH("mhi_dev_time_sync : local tick : 0x%llx device tick : 0x%llx\n", *local_ticks, *dev_ticks);

   status = mhi_dev_vote_for_pcie_l0(dev, FALSE);
   if (status != MHI_SUCCESS) {
      // pcie_dump_regs(dev->pcie_dev_h);
      MHI_LOG_FATAL("mhi_dev_sync_time : Removing vote for mhi_dev_vote_for_pcie_l0 failed");
      return ERROR;
   }

   /* TODO : vote for device wake deassert */
   return SUCCESS;
}

/**
 * This function is used to assert the device wake in pre_STM and STM context
 * and poll for MHI_M0 or MHI_SYS_ERROR.
 *
 * @param[in]  dev    MHI Device handle
 *
 * @return MHI_SUCCESS indicates the operation succeeded. Other values include:
 *       * MHI_ERROR: If operaton failed.
 */
int32 mhi_dev_wake_device_stm(mhi_dev_t *dev)
{
   mhi_state_t state;
   int timeout = 50; /* 50ms */
   int status;
   uint32 exec_ee;

   if (dev == NULL)
   {
      MHI_LOG_LOW("mhi_dev_wake_device : Invalid argument");
      return MHI_ERROR;
   }

   if ((dev->state != MHI_STATE_M0) && (dev->state != MHI_STATE_SYSERR))
   {
      /* Assert device wake */
      mhi_mmio_device_wake_db((uintptr_t)dev->resources.mem_sections[0].va, MHI_NODE_STATE_ASSERTED);
      MHI_LOG_HIGH("mhi_dev_wake_device_stm : Device Wake ASSERTED");

      do
      {
         /* Poll for MHI_STATE_M0 for 50ms */
         status = mhi_get_device_state(dev, &state);
         if (status != MHI_SUCCESS)
         {
            MHI_LOG_HIGH("mhi_dev_wake_device_stm : mhi_get_device_state failed");
            break;
         }

         pcie_osal_busywait(5000); /* 5ms busy wait */
         timeout = timeout - 5;
      } while (((state != MHI_STATE_M0) && (state != MHI_STATE_SYSERR)) && timeout > 0);

      /* check if the execution ee is also returning all 0xFFFF_FFFF */
      status = mhi_mmio_bhi_get_exe_ee((uintptr_t)dev->resources.mem_sections[0].va, &exec_ee);
      if (status != MHI_SUCCESS) {
         MHI_LOG_HIGH("mhi_dev_wake_device_stm : mhi_mmio_bhi_get_exe_ee failed");
         return MHI_ERROR;
      }
      dev->state = state;
   }

   return MHI_SUCCESS;
}

int32 mhi_dev_channel_open(mhi_dev_t *dev, mhi_ch_work_t *ch_work)
{
   mhi_chan_t *chan;
   uint32 ch_id;
   int32 status = SUCCESS;

   if (dev == NULL || ch_work == NULL)
   {
      MHI_LOG_ERROR("mhi_dev_channel_open : Invalid arguments");
      return MHI_INVALID_PARAM;
   }

   ch_id = ch_work->ch_id;
   if (ch_id > dev->cfg->num_chans)
   {
      MHI_LOG_ERROR("mhi_dev_channel_open : Invalid channel ch_id %d", ch_id);
      return MHI_INVALID_PARAM;
   }

   chan = &dev->chans[ch_id];
   if (chan == NULL)
   {
      MHI_LOG_ERROR("mhi_dev_channel_open : chan is null %d", ch_id);
      return MHI_ERROR;
   }

   pcie_osal_sync_enter(&chan->sync);

   do
   {
      if (chan->in_use)
      {
         MHI_LOG_ERROR("mhi_dev_channel_open : ch_id %d is already in use", ch_id);
         status =  MHI_ERROR;
         break;
      }

      if (chan->state == MHI_CHAN_STATE_OPEN)
      {
         MHI_LOG_ERROR("mhi_dev_channel_open : Failed to open channel - channel %d already opened", ch_id);
         status =  MHI_ERROR;
         break;
      }

      /* Issue channel start command */
      status = mhi_dev_chan_start(dev, ch_id);
      if(SUCCESS != status)
      {
         MHI_LOG_ERROR("mhi_dev_channel_open : Failed to start channel %u", ch_id);
         break;
      }

      chan->state = MHI_CHAN_STATE_OPEN;
      chan->ch_id = ch_id;
      chan->client_ctxt = ch_work->client_ctxt;
      chan->in_use = TRUE;

      MHI_LOG_HIGH("mhi_dev_channel_open : channel opened for ch_id %d with status %d\n",
                   ch_id, status);

      status = MHI_SUCCESS;
   } while(0);

   pcie_osal_sync_leave(&chan->sync);

   return status;
}

int32 mhi_dev_channel_close(mhi_dev_t *dev, mhi_ch_work_t *ch_work)
{
   mhi_chan_t *chan;
   uint32 ch_id;
   int32 status = SUCCESS;

   if (dev == NULL || ch_work == NULL)
   {
      MHI_LOG_ERROR("mhi_dev_channel_close : Invalid arguments");
      return MHI_INVALID_PARAM;
   }

   ch_id = ch_work->ch_id;
   if (ch_id > dev->cfg->num_chans)
   {
      MHI_LOG_ERROR("mhi_dev_channel_close : Invalid channel ch_id %d", ch_id);
      return MHI_INVALID_PARAM;
   }

   chan = &dev->chans[ch_id];
   if (chan == NULL)
   {
      MHI_LOG_ERROR("mhi_dev_channel_close : chan is null %d", ch_id);
      return MHI_ERROR;
   }

   pcie_osal_sync_enter(&chan->sync);

   do
   {
      if (!chan->in_use || chan->state != MHI_CHAN_STATE_OPEN)
      {
         MHI_LOG_ERROR("mhi_dev_channel_close : ch_id %d is not in use", ch_id);
         status = MHI_ERROR;
         break;
      }

      if (chan->client_ctxt != ch_work->client_ctxt)
      {
         MHI_LOG_ERROR("ERROR: mhi_dev_channel_close : invalid client for ch_id %d", ch_id);
         status = MHI_ERROR;
         break;
      }

      chan->client_ctxt = NULL;
      chan->state = MHI_CHAN_STATE_CLOSED;
      chan->in_use = FALSE;

      MHI_LOG_HIGH("mhi_dev_channel_close : channel closed for ch_id %d with status %d", ch_id, status);

      status = MHI_SUCCESS;
   } while(0);

   pcie_osal_sync_leave(&chan->sync);

   return status;
}

int32 mhi_dev_channel_write(mhi_dev_t *dev,
                            uint32 ch_id,
                            void *data,
                            size_t size,
                            mhi_cb_t *cb)
{
   mhi_chan_t *chan = NULL;
   mhi_ch_ctx_t *chan_ctx = NULL;
   //size_t  retsize;
   mhi_status_t status = SUCCESS;

   uint32 er_index = 0;
   uint32 host_wr_index, host_rd_index, dev_rd_index = 0;
   mhi_ev_ctx_t *er_ctx = NULL;
   mhi_ev_ring_t *er = NULL;
   mhi_transfer_event_element_t *evt_ring_el, *evt_ring_buf = NULL;

   uint32 chan_wr_index, chan_rd_index, num_elems = 0;
   mhi_tr_element_t *new_tr_el = NULL;

   if (ch_id > dev->cfg->num_chans)
   {
      MHI_LOG_ERROR("mhi_dev_channel_write : invalid ch_id %d", ch_id);
      return MHI_INVALID_PARAM;
   }

   chan = &dev->chans[ch_id];
   if (chan == NULL)
   {
      MHI_LOG_ERROR("mhi_dev_channel_write : chan is null %d", ch_id);
      return MHI_ERROR;
   }

   chan_ctx = &(dev->ch_ctx_arr[ch_id]);

   er_index = chan_ctx->erindex;
   //MHI_LOG_ERROR("mhi_dev_channel_write : Evt ring number for channel %u is %u\n",
                  //ch_id, er_index);

   er = &(dev->evt_rings[er_index]);
   er_ctx = &(dev->ev_ctx_arr[er_index]);

   pcie_osal_sync_enter(&chan->sync);

   if (!chan->in_use || chan->state != MHI_CHAN_STATE_OPEN)
   {
      MHI_LOG_ERROR("mhi_dev_channel_write : ch_id %d is not in use", ch_id);
      status = MHI_ERROR;
      goto cleanup;
   }

   /*
   if (chan->client_ctxt != client_ctxt)
   {
      MHI_LOG_ERROR("ERROR: mhi_dev_channel_write : invalid client for ch_id %d", ch_id);
      status = MHI_ERROR;
      break;
   }*/

   num_elems = chan->num_elems;
   chan_wr_index = (chan_ctx->wp - chan_ctx->rbase)/RING_EL_SIZE;
   chan_rd_index = (chan_ctx->rp - chan_ctx->rbase)/RING_EL_SIZE;

   /* Firstly check for ring full condition */
   if((chan_wr_index + 1) % num_elems
      == chan_rd_index)
   {
      MHI_LOG_ERROR("ERROR: mhi_dev_channel_write : ring full for ch_id %d", ch_id);
      status = MHI_ERROR;
      goto cleanup;
   }

   new_tr_el = (mhi_tr_element_t*)(chan_ctx->wp);
   new_tr_el->type = MHI_RING_EL_TYPE_TRANSFER;
   new_tr_el->ptr = (uint64)data;
   new_tr_el->len = size;
   new_tr_el->chain = 0;
   new_tr_el->ieot = 1;
   new_tr_el->ieob = 0;
   new_tr_el->bei = 1; /* ToDo : change this once we start using interrupts */

   chan_wr_index = (chan_wr_index + 1) % num_elems;
   chan_ctx->wp = chan_ctx->rbase + (chan_wr_index * RING_EL_SIZE);
   mhi_mmio_ring_db(chan->doorbell_addr, chan_ctx->wp);
   //MHI_LOG_HIGH("mhi_dev_channel_write: ch_id %u, 0x%x offset, data 0x%llx\n",
               //ch_id, CHDB_OFFSET(ch_id), chan_ctx->wp);

   pcie_osal_busywait(100 * 1000);

   /* Poll for transfer completion event in the channel's event ring */
   evt_ring_buf = (mhi_transfer_event_element_t*)(er->buf);
   host_rd_index = er->host_rd_index;
   dev_rd_index = (er_ctx->rp - er_ctx->rbase)/RING_EL_SIZE;
   host_wr_index = (er_ctx->wp - er_ctx->rbase)/RING_EL_SIZE;

   //MHI_LOG_HIGH("ER %u, Host rd index = %u, device rd index = %u\n",
                  //er_index, host_rd_index, dev_rd_index);

   while(host_rd_index != dev_rd_index)
   {
      evt_ring_el = evt_ring_buf + host_rd_index;

      //MHI_LOG_HIGH("Device sent event of type %u\n", evt_ring_el->type);

      /* ToDo: add check for invalid event */

      if(evt_ring_el->type == MHI_RING_EL_TYPE_TRANSFER_EVENT)
      {
         //MHI_LOG_HIGH("Device sent transfer completion event\n", evt_ring_el->type);

         if(evt_ring_el->code == MHI_CMD_CODE_EOT)
         {
            //MHI_LOG_HIGH("Transfer completed with EOT!! \n");
            //MHI_LOG_HIGH("%u bytes written \n", evt_ring_el->len);
         }
         else
         {
            MHI_LOG_HIGH("Transfer failed - completion code %u!\n",
            evt_ring_el->code);
            status = ERROR;
         }
      }

      host_rd_index = (host_rd_index + 1) % num_elems;
      host_wr_index = (host_wr_index + 1) % num_elems;
   }

   /* Update Host's cached read pointer */
   er->host_rd_index = host_rd_index;

   /* Recycle these events by updating ER's write pointer, ring doorbell */
   er_ctx->wp = er_ctx->rbase + (host_wr_index * RING_EL_SIZE);
   mhi_mmio_ring_db(er->doorbell_addr, er_ctx->wp);

   pcie_osal_sync_leave(&chan->sync);

cleanup:
   return status;
}

int32 mhi_dev_channel_read(mhi_dev_t *dev,
                           uint32 ch_id,
                           void *data,
                           size_t size,
                           uint32 *bytes_read,
                           mhi_cb_t *cb)
{
   mhi_chan_t *chan = NULL;
   mhi_ch_ctx_t *chan_ctx = NULL;
   //size_t  retsize;
   mhi_status_t status = SUCCESS;

   uint32 er_index = 0;
   uint32 host_wr_index, host_rd_index, dev_rd_index = 0;
   mhi_ev_ctx_t *er_ctx = NULL;
   mhi_ev_ring_t *er = NULL;
   mhi_transfer_event_element_t *evt_ring_el, *evt_ring_buf = NULL;

   uint32 chan_wr_index, chan_rd_index, num_elems = 0;
   mhi_tr_element_t *new_tr_el = NULL;

   if (ch_id > dev->cfg->num_chans)
   {
      MHI_LOG_ERROR("mhi_dev_channel_read : invalid ch_id %d", ch_id);
      return MHI_INVALID_PARAM;
   }

   chan = &dev->chans[ch_id];
   if (chan == NULL)
   {
      MHI_LOG_ERROR("mhi_dev_channel_read : chan is null %d", ch_id);
      return MHI_ERROR;
   }

   chan_ctx = &(dev->ch_ctx_arr[ch_id]);

   er_index = chan_ctx->erindex;
   //MHI_LOG_ERROR("mhi_dev_channel_read : Evt ring number for channel %u is %u\n",
   //               ch_id, er_index);

   er = &(dev->evt_rings[er_index]);
   er_ctx = &(dev->ev_ctx_arr[er_index]);

   pcie_osal_sync_enter(&chan->sync);

   if (!chan->in_use || chan->state != MHI_CHAN_STATE_OPEN)
   {
      MHI_LOG_ERROR("mhi_dev_channel_read : ch_id %d is not in use", ch_id);
      status = MHI_ERROR;
      goto cleanup;
   }

   /*
   if (chan->client_ctxt != client_ctxt)
   {
      MHI_LOG_ERROR("ERROR: mhi_dev_channel_write : invalid client for ch_id %d", ch_id);
      status = MHI_ERROR;
      break;
   }*/

   num_elems = chan->num_elems;
   chan_wr_index = (chan_ctx->wp - chan_ctx->rbase)/RING_EL_SIZE;
   chan_rd_index = (chan_ctx->rp - chan_ctx->rbase)/RING_EL_SIZE;

   /* Firstly check for ring full condition */
   if((chan_wr_index + 1) % num_elems
      == chan_rd_index)
   {
      MHI_LOG_ERROR("ERROR: mhi_dev_channel_read : ring full for ch_id %d", ch_id);
      status = MHI_ERROR;
      goto cleanup;
   }

   new_tr_el = (mhi_tr_element_t*)(chan_ctx->wp);
   new_tr_el->type = MHI_RING_EL_TYPE_TRANSFER;
   new_tr_el->ptr = (uint64)data;
   new_tr_el->len = size;
   new_tr_el->chain = 0;
   new_tr_el->ieot = 1;
   new_tr_el->ieob = 0;
   new_tr_el->bei = 1; /* ToDo : change this once we start using interrupts */

   chan_wr_index = (chan_wr_index + 1) % num_elems;
   chan_ctx->wp = chan_ctx->rbase + (chan_wr_index * RING_EL_SIZE);
   mhi_mmio_ring_db(chan->doorbell_addr, chan_ctx->wp);
   //MHI_LOG_HIGH("mhi_dev_channel_read: ch_id %u, 0x%x offset, data 0x%llx\n",
                //ch_id, CHDB_OFFSET(ch_id), chan_ctx->wp);

   pcie_osal_busywait(50 * 1000);

   /* Poll for transfer completion event in the channel's event ring */
   evt_ring_buf = (mhi_transfer_event_element_t*)(er->buf);
   host_rd_index = er->host_rd_index;
   dev_rd_index = (er_ctx->rp - er_ctx->rbase)/RING_EL_SIZE;
   host_wr_index = (er_ctx->wp - er_ctx->rbase)/RING_EL_SIZE;

   /*MHI_LOG_HIGH("ER %u, Host rd index = %u, device rd index = %u\n",
                  er_index, host_rd_index, dev_rd_index);*/

   /* Blocking read in polling mode */
   while(host_rd_index == dev_rd_index){
      dev_rd_index = (er_ctx->rp - er_ctx->rbase)/RING_EL_SIZE;
   }

   /* Unblocked, now advance until device's read pointer */
   while(host_rd_index != dev_rd_index)
   {
      evt_ring_el = evt_ring_buf + host_rd_index;

      //MHI_LOG_HIGH("Device sent event of type %u\n", evt_ring_el->type);

      /* ToDo: add check for invalid event */

      if(evt_ring_el->type == MHI_RING_EL_TYPE_TRANSFER_EVENT)
      {
         //MHI_LOG_HIGH("Device sent transfer completion event\n", evt_ring_el->type);

         if(evt_ring_el->code == MHI_CMD_CODE_EOT)
         {
            //MHI_LOG_HIGH("Transfer completed with EOT!! \n");
            //MHI_LOG_HIGH("%u bytes read \n", evt_ring_el->len);
            *bytes_read = evt_ring_el->len;
         }
         else
         {
            MHI_LOG_HIGH("Transfer failed - completion code %u!\n",
            evt_ring_el->code);
            status = ERROR;
         }
      }

      host_rd_index = (host_rd_index + 1) % num_elems;
      host_wr_index = (host_wr_index + 1) % num_elems;
   }

   /* Update Host's cached read pointer */
   er->host_rd_index = host_rd_index;

   /* Recycle these events by updating ER's write pointer, ring doorbell */
   er_ctx->wp = er_ctx->rbase + (host_wr_index * RING_EL_SIZE);
   mhi_mmio_ring_db(er->doorbell_addr, er_ctx->wp);

   pcie_osal_sync_leave(&chan->sync);

cleanup:
   return status;
}
