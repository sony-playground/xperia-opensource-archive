/**
 *  @file mhi_driver.c
 *
 *  @brief This file contains the driver-level MHI implementation.
 */
/*============================================================================
               Copyright (c) 2021-2022 Qualcomm Technologies, Inc.
               All Rights Reserved.
               Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "mhi_driver.h"
#include "mhi_device.h"
#include "list.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
/** Macro to create an instance ID out of the PCIe vendor and device IDs */
#define MHI_GET_INSTANCE_ID(vendor_id, device_id) \
   ((((vendor_id) & 0xffff) << 16) | ((device_id) & 0xffff))

#define MHI_LATENCY_MAX_VALUE  0xFFFFFFFF
#define MHI_NODE_ASSERT        1
#define MHI_NODE_DEASSERT      0

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
/** Element for a list of notify callbacks */
typedef struct
{
   list_t link;          /**< Link for list */
   mhi_cb_t cb;          /**< Callback */
   mhi_dev_id_t dev_id;  /**< Device ID of interest */
} mhi_notify_el_t;

/** Element for a list of PCIe devices */
typedef struct
{
   list_t link;                 /**< Link for list */
   pcie_dev_t *dev_h;           /**< Handle to the PCIe device */
   pcie_rsrc_t res;             /**< PCIe resources */
   pcie_device_info_t dev_ids;  /**< PCIe device IDs */
} mhi_pcie_dev_t;

/** Element for a list of devices */
typedef struct
{
   list_t link;              /**< Link for list */
   mhi_dev_info_t dev_info;  /**< Device info */
   mhi_dev_t *dev;           /**< Pointer to the device */
} mhi_dev_el_t;

/** Element for a list of client contexts */
typedef struct
{
   list_t link;                    /**< Link for list */
   mhi_client_ctxt_t client_ctxt;  /**< Client context */
} mhi_client_el_t;

/** Element for a list of closed client contexts */
typedef struct
{
   list_t link;                    /**< Link for list */
   mhi_dev_t *dev;           /**< Pointer to the device */
   mhi_cb_t cb; /**< callback for MHI_DEV_CLOSED notification */
} mhi_closed_client_el_t;

/** Element for a list of min bus latency voting */
typedef struct
{
   list_t link;                    /**< Link for list */
   mhi_client_ctxt_t *client_ctxt;  /**< Client context */
} mhi_bus_min_latency_t;
/*----------------------------------------------------------------------------
 * Static Function Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/
/** MHI driver context */
static mhi_drv_t *mhi_drv = NULL;

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * -------------------------------------------------------------------------*/
/**
 * This function signals the worker thread that new work is ready.
 *
 * @return None
 */
static void mhi_drv_work_added(void)
{
   MHI_LOG_LOW("Going to signal mhi_drv_worker");
   pcie_osal_event_signal(&mhi_drv->worker_event);
}

/**
 * This function is the callback for PCIe device adds.
 *
 * @param[in]  dev_h    PCIe device handle
 * @param[in]  payload  PCIe callback payload
 * @param[in]  ctxt     Client context
 *
 * @return None
 */
static void mhi_drv_pcie_probe_cb(pcie_dev_t *dev_h, const pcie_dev_probe_cb_payload_t *payload,
                                  void *ctxt)
{
   mhi_pcie_dev_t *dev_el;
   pcie_status_t pstatus = PCIE_SUCCESS;

   MHI_LOG_HIGH("PCIe probe cb for /0x%x/0x%x",
                payload->dev_ids.vendor_id,
                payload->dev_ids.device_id);

   dev_el = pcie_osal_malloc(sizeof(mhi_pcie_dev_t));
   if (dev_el == NULL)
   {
      MHI_LOG_FATAL("Failed to allocate memory for received PCIe dev");
      /*adding return statement to fix kw error*/
      return;
   }

   dev_el->dev_h = dev_h;
   dev_el->res = payload->rsrc;
   dev_el->dev_ids = payload->dev_ids;

   pstatus = pcie_enable_device (dev_h);
   if (pstatus != PCIE_SUCCESS)
   {
      MHI_LOG_FATAL("Device enable failed\n");
      return;
   }

   pcie_osal_sync_enter(&mhi_drv->sync);
   list_add_tail(&mhi_drv->new_pcie_device_list, &dev_el->link);
   pcie_osal_sync_leave(&mhi_drv->sync);

   mhi_drv_work_added();
}

#ifdef MHI_NOT_IMPLEMENTED
static void mhi_drv_pcie_cb(uint32 status)
{
   mhi_notify_el_t *notify_el;
   mhi_notify_el_t *next;
   mhi_cb_payload_t data;

   MHI_LOG_HIGH("mhi_drv_pcie_cb : callback notification status 0x%x", status);

   if (status == PCIE_LINK_DOWN) {
      mhi_drv->pcie_link_down = TRUE;
	  mhi_drv->sys_err        = TRUE;
	  mhi_drv_work_added();
   } else if (status == PCIE_LINK_UP) { /* to make sure that MHI_DEV_CONNECTED notification is sent only after link down */
      pcie_osal_sync_enter(&mhi_drv->sync);

      mhi_drv->client_notify_sys_err = TRUE;

      list_for_each_item (&mhi_drv->notify_list, mhi_notify_el_t, link, notify_el, next)
      {
	 pcie_osal_sync_leave(&mhi_drv->sync);

	 data.op = MHI_NOTIFY;
	 data.status = MHI_SUCCESS;
	 data.user_data = notify_el->cb.user_data;
	 data.dev_info.dev_id = MHI_DEV_ID_MOSELLE;
	 data.dev_info.instance_id = MHI_GET_INSTANCE_ID(0x17CB, 0x1105);
	 data.op_payload.notify.event = MHI_DEV_CONNECTED;
	 MHI_LOG_HIGH("mhi_drv_pcie_cb : Issuing MHI_NOTIFY: event %d, dev 0x%x", data.op_payload.notify.event, data.dev_info.instance_id);

	 notify_el->cb.cb_func(&data);

	 pcie_osal_sync_enter(&mhi_drv->sync);
      }
      mhi_drv->pcie_link_down = FALSE;
      pcie_osal_sync_leave(&mhi_drv->sync);
   } else {
      MHI_LOG_LOW("mhi_drv_pcie_cb : Invalid pcie status %d", status);
   }
}
#endif

/**
 * This function notifies a client for registration events, such as
 * when a new device arrives.
 *
 * @param[in]  notify_el  Notify element
 * @param[in]  event      Which notify event
 * @param[in]  dev_el     Device element
 *
 * @return None
 */
static void mhi_drv_notify(mhi_notify_el_t *notify_el, mhi_event_t event,
                           mhi_dev_el_t *dev_el)
{
   mhi_cb_payload_t data;

   MHI_LOG_HIGH("Issuing MHI_NOTIFY: event %d, dev 0x%x",
                event,
                dev_el->dev_info.instance_id);

   data.op = MHI_NOTIFY;
   data.status = MHI_SUCCESS;
   data.user_data = notify_el->cb.user_data;
   data.dev_info = dev_el->dev_info;
   data.op_payload.notify.event = event;

   notify_el->cb.cb_func(&data);
}

/**
 * This function notifies all applicable clients for registration events,
 * such as when a new device arrives.
 *
 * @param[in]  event      Which notify event
 * @param[in]  dev_el     Device element
 *
 * @return None
 */
static void mhi_drv_notify_all(mhi_event_t event, mhi_dev_el_t *dev_el)
{
   mhi_notify_el_t *notify_el;
   mhi_notify_el_t *next;

   pcie_osal_sync_enter(&mhi_drv->sync);
   list_for_each_item (&mhi_drv->notify_list, mhi_notify_el_t, link, notify_el, next)
   {
      if (notify_el->dev_id == dev_el->dev_info.dev_id ||
          notify_el->dev_id == MHI_DEV_ID_ALL)
      {
         pcie_osal_sync_leave(&mhi_drv->sync);
         mhi_drv_notify(notify_el, event, dev_el);
         pcie_osal_sync_enter(&mhi_drv->sync);
      }
   }
   pcie_osal_sync_leave(&mhi_drv->sync);
}

/**
 * This function notifies all applicable clients for registration events,
 * such as when a new device arrives.
 *
 * @param[in]  event      Which notify event
 * @param[in]  dev_el     Device element
 *
 * @return None
 */
void mhi_drv_notify_clients(mhi_event_t event, mhi_dev_t *dev)
{
   mhi_client_el_t *client_el;
   mhi_client_el_t *client_next;
   mhi_cb_payload_t data;

   MHI_LOG_MED("mhi_driver.c : mhi_drv_notify_clients");
   pcie_osal_sync_enter(&mhi_drv->sync);

   /* Notification callback to the clients with the current dev */
   list_for_each_item (&mhi_drv->client_list, mhi_client_el_t, link, client_el, client_next)
   {
   MHI_LOG_MED("mhi_driver.c : mhi_drv_notify_clients : parsing list");

     if (dev == client_el->client_ctxt.dev)
     {
	 data.op = MHI_NOTIFY;
	 data.status = MHI_SUCCESS;
	 data.user_data = client_el->client_ctxt.cb.user_data;
	 data.dev_info = client_el->client_ctxt.dev->dev_info;
	 data.op_payload.notify.event = event;

	 MHI_LOG_MED("Issuing MHI_NOTIFY: event %d, dev 0x%x", data.op_payload.notify.event, data.dev_info.instance_id);

         pcie_osal_sync_leave(&mhi_drv->sync);
	 client_el->client_ctxt.cb.cb_func(&data);
         pcie_osal_sync_enter(&mhi_drv->sync);
      }
   }
   pcie_osal_sync_leave(&mhi_drv->sync);
}

/**
 * This function looks up the device context in the list of devices from the
 * unique instance ID.
 *
 * @param[in]  instance_id  Unique instance ID
 *
 * @return Device context
 */
static mhi_dev_t *mhi_drv_get_dev(uint32 instance_id)
{
   mhi_dev_el_t *dev_el;
   mhi_dev_el_t *next;

   list_for_each_item (&mhi_drv->device_list, mhi_dev_el_t, link, dev_el, next)
   {
      if (dev_el->dev_info.instance_id == instance_id)
      {
         return dev_el->dev;
      }
   }

   return NULL;
}

/**
 * This function is called to initialize a device. It also adds an element for
 * the device in the device list.
 *
 * @param[in]  pcie_dev_h    PCIe device handle
 * @param[in]  pcie_res      PCIe resources
 * @param[in]  pcie_dev_ids  PCIe device IDs
 *
 * @return Device context or NULL if not supported
 */
static mhi_dev_t *mhi_drv_init_dev(pcie_dev_t *pcie_dev_h, const pcie_rsrc_t *pcie_res,
                                   const pcie_device_info_t *pcie_dev_ids)
{
   const mhi_dev_cfg_t *cfg = NULL;
   mhi_dev_el_t *dev_el;
   uint32 instance_id;
   int32 status;
   uint32 i;
   //mhi_int_trigger_params_t trgi_parms;

   instance_id = MHI_GET_INSTANCE_ID(pcie_dev_ids->vendor_id, pcie_dev_ids->device_id);

   for (i = 0; i < mhi_drv->tgt_config->num_devs; i++)
   {
      if (pcie_dev_ids->vendor_id == mhi_drv->tgt_config->dev_cfgs[i].pcie_vendor_id &&
          pcie_dev_ids->device_id == mhi_drv->tgt_config->dev_cfgs[i].pcie_device_id)
      {
         cfg = &mhi_drv->tgt_config->dev_cfgs[i];
      }
   }
   if (cfg == NULL)
   {
      MHI_LOG_HIGH("No config found for 0x%x - not supported", instance_id);
      return NULL;
   }

   dev_el = pcie_osal_malloc(sizeof(mhi_dev_el_t));
   if (dev_el == NULL)
   {
      MHI_LOG_FATAL("No memory for 0x%x", instance_id);
      /*adding return to fix kw error*/
      return NULL;

   }

   dev_el->dev_info.instance_id = instance_id;
   dev_el->dev_info.dev_id = cfg->dev_id;

   status = mhi_dev_init(mhi_drv,
                         &dev_el->dev_info,
                         cfg,
                         pcie_dev_h,
                         pcie_res,
                         &dev_el->dev);
   if (status != SUCCESS)
   {
      MHI_LOG_FATAL("mhi_dev_init failed for 0x%x", instance_id);
   }

   pcie_osal_sync_enter(&mhi_drv->sync);
   list_add_tail(&mhi_drv->device_list, &dev_el->link);
   pcie_osal_sync_leave(&mhi_drv->sync);

   mhi_drv_notify_all(MHI_DEV_CONNECTED, dev_el);

   return dev_el->dev;
}

/**
 * This function notifies the clients in case of sys error.
 *
 * @return None
 */
static void mhi_drv_process_handle_sys_err()
{
   // mhi_status_t status;
   // mhi_client_el_t *client_el = NULL;
   mhi_dev_t *dev = NULL;

   if(mhi_drv->sys_err == TRUE)
   {
      pcie_osal_sync_enter(&mhi_drv->sync);
      dev = mhi_dev_handle_get();
      pcie_osal_sync_leave(&mhi_drv->sync);

      if (dev == NULL) {
	 MHI_LOG_ERROR("mhi_driver.c : mhi_drv_process_handle_sys_err : dev is NULL");
	 return ;
      }

#if 0 /* we don't need to trigger syserr for link down because, after the link is down
       * we are causing un-necessary transction over the controller */
      status = mhi_dev_trigger_sys_error(dev, TRUE);
      if(status != SUCCESS)
      {
	 MHI_LOG_ERROR("mhi_driver.c : mhi_drv_worker : sys_err failed");
      }
#endif
      if(dev->drv->client_notify_sys_err == TRUE)
      {
	 mhi_drv_notify_clients(MHI_DEV_SYS_ERR, dev);
	 dev->drv->client_notify_sys_err = FALSE;
      }
      mhi_drv->sys_err = FALSE;
   }
}

/**
 * This function processes new PCIe devices.
 *
 * @return None
 */
static void mhi_drv_process_new_pcie_devs(void)
{
   mhi_pcie_dev_t *dev_el;
   mhi_pcie_dev_t *next;

   pcie_osal_sync_enter(&mhi_drv->sync);

   list_for_each_item (&mhi_drv->new_pcie_device_list, mhi_pcie_dev_t, link, dev_el, next)
   {
      list_del(&dev_el->link);

      pcie_osal_sync_leave(&mhi_drv->sync);

      mhi_drv_init_dev(dev_el->dev_h, &dev_el->res, &dev_el->dev_ids);

      pcie_osal_free(dev_el);
      pcie_osal_sync_enter(&mhi_drv->sync);
   }

   pcie_osal_sync_leave(&mhi_drv->sync);
}

/**
 * This function processes new notify items by issuing notifications
 * for existing devices then moving the notify object to the notify
 * list.
 *
 * @return None
 */
static void mhi_drv_process_new_notify_items(void)
{
   mhi_notify_el_t *notify_el;
   mhi_notify_el_t *next;
   mhi_dev_el_t *dev;
   mhi_dev_el_t *next_dev;

   pcie_osal_sync_enter(&mhi_drv->sync);

   list_for_each_item (&mhi_drv->new_notify_items, mhi_notify_el_t, link, notify_el, next)
   {
      list_del(&notify_el->link);

      /* Send notifications for the devices that are already connected */
      list_for_each_item (&mhi_drv->device_list, mhi_dev_el_t, link, dev, next_dev)
      {
         if (notify_el->dev_id == dev->dev_info.dev_id ||
             notify_el->dev_id == MHI_DEV_ID_ALL)
         {
            pcie_osal_sync_leave(&mhi_drv->sync);
            mhi_drv_notify(notify_el, MHI_DEV_CONNECTED, dev);
            pcie_osal_sync_enter(&mhi_drv->sync);
         }
      }

      list_add_tail(&mhi_drv->notify_list, &notify_el->link);
   }

   pcie_osal_sync_leave(&mhi_drv->sync);
}

/**
 * This function processes new PCIe devices.
 *
 * @return None
 */
static void mhi_drv_process_closed_clients(void)
{
   mhi_closed_client_el_t *closed_client_el = NULL;
   mhi_closed_client_el_t *next = NULL;
   mhi_client_el_t *client_el = NULL;
   mhi_client_el_t *client_next = NULL;
   mhi_dev_el_t *dev_el = NULL;
   mhi_dev_el_t *dev_next = NULL;
   uint32 client_count = 0;
   mhi_cb_payload_t data;
   //mhi_dev_t *dev = NULL;
   //pcie_status_t status = PCIE_SUCCESS;
   mhi_event_t event_type = MHI_DEV_CLOSED;


   pcie_osal_sync_enter(&mhi_drv->sync);

   /* if there are no clients who requested for mhi_dev_close return */
   if (list_is_empty(&mhi_drv->closed_client_list))
   {
      pcie_osal_sync_leave(&mhi_drv->sync);
      return;
   }

   list_for_each_item (&mhi_drv->device_list, mhi_dev_el_t, link, dev_el, dev_next)
   {
      client_count = 0;

      /* count the number of clients for the current device */
      list_for_each_item (&mhi_drv->client_list, mhi_client_el_t, link, client_el, client_next)
      {
         if (dev_el->dev == client_el->client_ctxt.dev)
         {
            client_count++;
         }

      }

      /* if the client count for the current device, then call the pcie_shutdown and
	   notify the clients who provieded the callback */
      if (!client_count)
      {
         /*
         status = pcie_suspend(dev_el->dev->pcie_dev_h);
         if (status != PCIE_SUCCESS)
         {
            MHI_LOG_HIGH("mhi_drv_process_closed_clients : pcie_suspend failed");
            event_type = MHI_DEV_SYS_ERR;
         }*/

         /* Notify the clients with MHI_DEV_CLOSED or MHI_DEV_SYS_ERR mhi status */

         list_for_each_item (&mhi_drv->closed_client_list, mhi_closed_client_el_t, link, closed_client_el, next)
         {
            if (dev_el->dev == closed_client_el->dev)
            {
               data.op = MHI_NOTIFY;
               data.status = MHI_SUCCESS;
               data.user_data = closed_client_el->cb.user_data;
               data.dev_info = closed_client_el->dev->dev_info;
               data.op_payload.notify.event = event_type;

               MHI_LOG_HIGH("mhi_drv_process_closed_clients : Issuing MHI_NOTIFY: event %d, dev 0x%x", data.op_payload.notify.event, data.dev_info.instance_id);

               pcie_osal_sync_leave(&mhi_drv->sync);
               closed_client_el->cb.cb_func(&data);
               pcie_osal_sync_enter(&mhi_drv->sync);

               list_del(&closed_client_el->link);
               pcie_osal_free(closed_client_el);
            }
         }
   //TODO: not removing the device from the device list because curently we are not calling pcie_suspend
   // list_del(&dev_el->link);
   // pcie_osal_free(dev_el);

      }
   }

   pcie_osal_sync_leave(&mhi_drv->sync);
}

static void mhi_drv_process_clients_request(void)
{
#if 0 /* Currently we made mhi_issue_req as synchronous, so don't need worker thread
	 can be enabled later if needed */

   mhi_client_el_t *client_el = NULL;
   mhi_dev_t *dev = NULL;
   uint32 min_latency = 0xFFFFF; //TODO : need to maximum values

   pcie_osal_sync_enter(&mhi_drv->sync);

   if (mhi_drv->client_request_pending == FALSE) {
      pcie_osal_sync_leave(&mhi_drv->sync);
      return;
   }

   //TODO : assuming there is only one mhi device connected and all the current client belong to moselle only.
   client_el = list_get_item(&mhi_drv->client_list, mhi_client_el_t, link);
   if (client_el == NULL) { // if there is not client added yet in the list
      MHI_LOG_MED("mhi_drv_process_clients_request : ERROR : no client added yet in the list");
      pcie_osal_sync_leave(&mhi_drv->sync);
      return;
   }

   dev = client_el->client_ctxt.dev;

   if (dev->bus_node_vote_counter == 0) { /* If there is no client voted for bus */
      pcie_request_link_latency(dev->pcie_dev_h, dev->resume_latency_min_val);
      min_latency = dev->resume_latency_min_val;
   } else {
      pcie_request_link_latency(dev->pcie_dev_h, dev->active_latency_min_val);
      min_latency = dev->active_latency_min_val;
   }

   if (dev->device_wake_assert_vote > 0) { /* even if one client voted for device wake assert */
      mhi_drv_device_wake(&client_el->client_ctxt, MHI_NODE_STATE_ASSERTED);
   } else { /* de-assert device wake if no client voted for assert */
      /* De-assert device wake only if there are no votes for the bus and minimum_latency is not L0 */
      if (dev->bus_node_vote_counter == 0 && min_latency != 0) {
	 /* de-assert the device wake */
	 mhi_drv_device_wake(&client_el->client_ctxt, MHI_NODE_STATE_DEASSERTED);
      }
   }

   mhi_drv->client_request_pending = FALSE;

   pcie_osal_sync_leave(&mhi_drv->sync);
#endif
}

/**
 * This function is the driver-level worker thread.
 *
 * @param[in]  ctxt  Context
 *
 * @return None
 */
static int mhi_drv_worker(void *ctxt)
{
   MHI_LOG_HIGH("mhi_drv_worker spawned\n");
   for ( ; ; )
	{
      pcie_osal_event_wait(&mhi_drv->worker_event);

      MHI_LOG_HIGH("mhi_drv_worker signaled, executing loop\n");

      mhi_drv_process_handle_sys_err();
      mhi_drv_process_new_notify_items();
      mhi_drv_process_new_pcie_devs();
      mhi_drv_process_closed_clients();
      mhi_drv_process_clients_request();
   }
   return 0;
}

/*----------------------------------------------------------------------------
 * Externalized Function Definitions
 * -------------------------------------------------------------------------*/
/**
 * This function performs driver-level initialization.
 *
 * @param[in]  tgt_config  Target configuration
 *
 * @return SUCCESS or an error code
 */
int32 mhi_drv_init(const mhi_tgt_config_t *tgt_config)
{
   pcie_device_info_t device_id;
   pcie_status_t pcie_status;
   int ret;

   if (mhi_drv != NULL)
   {
      return SUCCESS;
   }

   mhi_drv = pcie_osal_malloc(sizeof(*mhi_drv));
   if (mhi_drv == NULL)
   {
      MHI_LOG_FATAL("pcie_osal_malloc failed");
      /*adding return to fix kw error*/
      return ERROR;
   }
   pcie_osal_memset(mhi_drv, 0, sizeof(*mhi_drv));

   mhi_drv->tgt_config = tgt_config;

   ret = pcie_osal_sync_init(&mhi_drv->sync, PCIE_OSAL_SYNC_FLAG_NONE);
   if (ret)
   {
      MHI_LOG_FATAL("pcie_osal_sync_init failed");
   }

   ret = pcie_osal_event_init(&mhi_drv->worker_event);
   if (ret)
   {
      MHI_LOG_FATAL("pcie_osal_event_init failed");
   }

   ret = pcie_osal_thread_spawn(&mhi_drv->thread,
                                tgt_config->drv_thread_name,
                                &mhi_drv_worker,
                                mhi_drv,
                                tgt_config->drv_thread_priority);
   if (ret)
   {
      MHI_LOG_FATAL("pcie_osal_thread_spawn failed");
   }

   list_init(&mhi_drv->new_notify_items);
   list_init(&mhi_drv->notify_list);
   list_init(&mhi_drv->new_pcie_device_list);
   list_init(&mhi_drv->device_list);
   list_init(&mhi_drv->client_list);
   list_init(&mhi_drv->closed_client_list);
   list_init(&mhi_drv->active_bus_latency_list);
   list_init(&mhi_drv->bus_resume_latency_list);

   device_id.class_id = PCIE_ID_ANY;
   device_id.device_id = PCIE_ID_ANY;
   device_id.vendor_id = PCIE_ID_ANY;

   pcie_status = pcie_register_device(&device_id, mhi_drv_pcie_probe_cb, mhi_drv);
   if (pcie_status != PCIE_SUCCESS)
   {
      MHI_LOG_FATAL("pcie_register_device failed");
   }

   mhi_drv->pcie_link_down        = FALSE;
   mhi_drv->sys_err               = FALSE;
   mhi_drv->client_notify_sys_err = TRUE;  // TODO : Need to change after discussion

   //pcie_register_device_cb(mhi_drv_pcie_cb);

   MHI_LOG_MED("Driver-layer initialization complete\n");

   return SUCCESS;
}

/**
 * This function performs driver-level deinitialization.
 *
 * @return SUCCESS or an error code
 */
int32 mhi_drv_deinit(void)
{
   return NOT_SUPPORTED;
}

/**
 * This function registers a callback to receive notifications for a given
 * device ID.
 *
 * @param[in]  dev_id  Device ID
 * @param[in]  cb      Client-supplied callback
 *
 * @return SUCCESS or an error code
 */
int32 mhi_drv_register(mhi_dev_id_t dev_id, mhi_cb_t *cb)
{
   mhi_notify_el_t *notify_el;

   notify_el = pcie_osal_malloc(sizeof(mhi_notify_el_t));
   if (notify_el == NULL)
   {
      MHI_LOG_ERROR("ERROR: mhi_drv_register failed - no memory");
      return NOMEM;
   }

   notify_el->cb = *cb;
   notify_el->dev_id = dev_id;

   pcie_osal_sync_enter(&mhi_drv->sync);
   list_add_tail(&mhi_drv->new_notify_items, &notify_el->link);
   pcie_osal_sync_leave(&mhi_drv->sync);

   MHI_LOG_HIGH("Client registered for notifications for dev ID 0x%x", dev_id);

   mhi_drv_work_added();

   return SUCCESS;
}

/**
 * This function unregisters a callback that receives notifications for a given
 * device ID.
 *
 * @param[in]  dev_id  Device ID
 * @param[in]  cb      Client-supplied callback
 *
 * @return SUCCESS or an error code
 */
int32 mhi_drv_unregister(mhi_dev_id_t dev_id, mhi_cb_t *cb)
{
   mhi_notify_el_t *notify_el;
   mhi_notify_el_t *next;

   pcie_osal_sync_enter(&mhi_drv->sync);
   
   list_for_each_item (&mhi_drv->notify_list, mhi_notify_el_t, link, notify_el, next)
   { 
      if (notify_el->dev_id == dev_id &&
          notify_el->cb.cb_func == cb->cb_func)
      {
         list_del(&notify_el->link);
         pcie_osal_free(notify_el);
         MHI_LOG_HIGH("Client unregistered for notifications for dev ID 0x%x", dev_id);
      }
   }
   pcie_osal_sync_leave(&mhi_drv->sync);

   return SUCCESS;
}

/**
 * This function opens a specific device and registers a device-specific callback.
 *
 * @param[in]  dev_info     Device info
 * @param[in]  cb           Client-supplied callback
 * @param[out] client_ctxt  Client context
 *
 * @return SUCCESS or an error code
 */
int32 mhi_drv_open_dev(const mhi_dev_info_t *dev_info, mhi_cb_t *cb,
                       mhi_client_ctxt_t **client_ctxt)
{
   mhi_client_el_t *client_el;
   mhi_dev_t *dev;

   pcie_osal_sync_enter(&mhi_drv->sync);
   dev = mhi_drv_get_dev(dev_info->instance_id);
   pcie_osal_sync_leave(&mhi_drv->sync);

   if (dev == NULL)
   {
      MHI_LOG_ERROR("ERROR: mhi_drv_open_dev failed for dev 0x%x - not found",
                    dev_info->instance_id);
      return ERROR;
   }

   client_el = pcie_osal_malloc(sizeof(mhi_client_el_t));
   if (client_el == NULL)
   {
      MHI_LOG_ERROR("ERROR: mhi_drv_open_dev failed for dev 0x%x - no memory",
                    dev_info->instance_id);
      return NOMEM;
   }

   client_el->client_ctxt.cb = *cb;
   client_el->client_ctxt.dev = dev;

   pcie_osal_sync_enter(&mhi_drv->sync);
   list_add_tail(&mhi_drv->client_list, &client_el->link);
   pcie_osal_sync_leave(&mhi_drv->sync);

   MHI_LOG_HIGH("Dev 0x%x successfully opened by client", dev_info->instance_id);
   memset(client_el->client_ctxt.issue_req,0,MHI_MAX_NUM_NODES*sizeof(mhi_issue_req_t));
   //client_el->client_ctxt.issue_req[MHI_NODE_ACTIVE_BUS_LATENCY_US].state = PCIE_DEFAULT_LINK_ACTIVE_LATENCY;
   //client_el->client_ctxt.issue_req[MHI_NODE_BUS_RESUME_LATENCY_US].state = PCIE_DEFAULT_LINK_RESUME_LATENCY;

   *client_ctxt = &client_el->client_ctxt;

   return SUCCESS;
}

int32 mhi_drv_active_node_check(mhi_client_ctxt_t *client_ctxt)
{
	if(client_ctxt->issue_req[MHI_NODE_DEVICE_WAKE].state != MHI_NODE_STATE_DEASSERTED)
	{
	MHI_LOG_MED("mhi_drv_active_node_check : Failed : state : %d",client_ctxt->issue_req[MHI_NODE_DEVICE_WAKE].state);
	return ERROR;
	}

	if(client_ctxt->issue_req[MHI_NODE_BUS_VOTE].state != MHI_NODE_STATE_DEASSERTED)
	{
	MHI_LOG_MED("mhi_drv_active_node_check : Failed : state : %d",client_ctxt->issue_req[MHI_NODE_BUS_VOTE].state);
	return ERROR;
	}

	return SUCCESS;
}

/**
 * This function closes a specific device and registers a device-specific callback.
 *
 * @param[in]  dev 	    Device info
 * @param[in]  cb           Optional Client-supplied callback
 *
 * @return SUCCESS or an error code
 */
int32 mhi_drv_close_dev(mhi_client_ctxt_t *client_ctxt, mhi_cb_t *cb)
{
   mhi_closed_client_el_t *closed_client_el = NULL;
   mhi_client_el_t *client_el = NULL;
   mhi_client_el_t *client_next = NULL;
   mhi_bus_min_latency_t *bus_latency_el = NULL;
   mhi_bus_min_latency_t *bus_latency_next = NULL;

   closed_client_el = pcie_osal_malloc(sizeof(mhi_closed_client_el_t));
   if (closed_client_el == NULL)
   {
      MHI_LOG_ERROR("ERROR: mhi_drv_close_dev failed for dev 0x%x - no memory", client_ctxt->dev->dev_info.instance_id);
      return NOMEM;
   }

   if (cb) {
      closed_client_el->cb = *cb;
   }
   closed_client_el->dev = client_ctxt->dev;

   pcie_osal_sync_enter(&mhi_drv->sync);

	/* delete the current client from the active_bus_latency_list */
	list_for_each_item (&mhi_drv->active_bus_latency_list, mhi_bus_min_latency_t, link, bus_latency_el, bus_latency_next)
	{
		if (bus_latency_el->client_ctxt == client_ctxt)
		{
			MHI_LOG_MED("Client there in the active_bus_latency_list : deleting");
			list_del(&bus_latency_el->link);
			pcie_osal_free(bus_latency_el);
			break;
		}
	}

	/* delete the current client from the bus_resume_latency_list */
	list_for_each_item (&mhi_drv->bus_resume_latency_list, mhi_bus_min_latency_t, link, bus_latency_el, bus_latency_next)
	{
		if (bus_latency_el->client_ctxt == client_ctxt)
		{
			MHI_LOG_MED("Client there in the bus_resume_latency_list : deleting");
			list_del(&bus_latency_el->link);
			pcie_osal_free(bus_latency_el);
			break;
		}
	}

   /* delete the current client from the client_list */
   list_for_each_item (&mhi_drv->client_list, mhi_client_el_t, link, client_el, client_next)
   {
      if (&client_el->client_ctxt == client_ctxt)
      {
			if(mhi_drv_active_node_check(client_ctxt) != SUCCESS)
			{
				MHI_LOG_MED("mhi_drv_close_dev : Vote not removed");
  			    pcie_osal_sync_leave(&mhi_drv->sync);
				return ERROR;
			}
	 list_del(&client_el->link);
	 pcie_osal_free(client_el);
	 break;
      }
   }

   list_add_tail(&mhi_drv->closed_client_list, &closed_client_el->link);
   pcie_osal_sync_leave(&mhi_drv->sync);

   MHI_LOG_HIGH("Dev 0x%x successfully closed by client", closed_client_el->dev->dev_info.instance_id);

   mhi_drv_work_added();

   return SUCCESS;
}

uint32 mhi_drv_get_min_val(uint32 node)
{
	mhi_bus_min_latency_t *bus_el_t = NULL;
	list_t *node_list;

	if(node == MHI_NODE_ACTIVE_BUS_LATENCY_US)
	{
		node_list = &mhi_drv->active_bus_latency_list;
	}
	else
	{
		node_list = &mhi_drv->bus_resume_latency_list;
	}

	if (!list_is_empty(node_list))
	{
		pcie_osal_sync_enter(&mhi_drv->sync);
		bus_el_t = list_get_item(node_list, mhi_bus_min_latency_t, link);
		pcie_osal_sync_leave(&mhi_drv->sync);

      if(bus_el_t)
      {
         if(bus_el_t->client_ctxt)
         {
            return bus_el_t->client_ctxt->issue_req[node].state;
         }
      }
	}
	return MHI_LATENCY_MAX_VALUE;
}

mhi_bus_min_latency_t *mhi_drv_get_client_node(mhi_client_ctxt_t *client_ctxt, mhi_node_t node)
{
	mhi_bus_min_latency_t *new_client = NULL;
	list_t *node_list;
    mhi_bus_min_latency_t *client_el = NULL;
    mhi_bus_min_latency_t *client_next = NULL;

	if(node == MHI_NODE_ACTIVE_BUS_LATENCY_US)
	{
		node_list = &mhi_drv->active_bus_latency_list;
	}
	else
	{
		node_list = &mhi_drv->bus_resume_latency_list;
	}

	list_for_each_item(node_list, mhi_bus_min_latency_t, link, client_el, client_next)
	{
		if (client_el->client_ctxt == client_ctxt)
		{
			MHI_LOG_LOW("mhi_drv_get_client_node : client matched : %#X , %#X",client_el->client_ctxt,client_ctxt);
			list_del(&client_el->link);
		    return client_el;
		}
	}

	new_client = pcie_osal_malloc(sizeof(mhi_bus_min_latency_t));
	return new_client;
}

/**
 * This function adds the new client in the sorted client list.
 *
 * @param[in]  new_client 	New Client to be added to the list
 * @param[in]  head         Pointer to the head of the list
 * @param[in]  node         Node requested by the client
 * @param[in]  val          Value corresponding to the node
 *
 * @return void
 */
void mhi_drv_add_node_bus(mhi_bus_min_latency_t *new_client, list_t *list_head, mhi_node_t node, uint32 val)
{
    mhi_bus_min_latency_t *client_bus_el = NULL;
    mhi_bus_min_latency_t *client_bus_next = NULL;
	mhi_bus_min_latency_t *client_head = NULL;
    list_t *client_prev_list = NULL;
	list_t *node_list;

	if(node == MHI_NODE_ACTIVE_BUS_LATENCY_US)
	{
		node_list = &mhi_drv->active_bus_latency_list;
	}
	else
	{
		node_list = &mhi_drv->bus_resume_latency_list;
	}

	if (list_is_empty(list_head))
	{
		MHI_LOG_LOW("mhi_drv_add_node_bus : list empty");
		list_add_head(list_head, &new_client->link);
		return;
	}

	client_head = list_get_item(list_head, mhi_bus_min_latency_t, link);
   if(!client_head)
   {
      return;
   }

	client_prev_list = client_head->link.prev;

	list_for_each_item(node_list, mhi_bus_min_latency_t, link, client_bus_el, client_bus_next)
	{
		if (client_bus_el->client_ctxt->issue_req[node].state >= val)
		{
			_list_insert(client_prev_list, &client_bus_el->link, &new_client->link);
			return;
		}
		client_prev_list = &client_bus_el->link;
	}
	list_add_tail(list_head,&new_client->link);
}

uint32 mhi_update_latency_list(mhi_client_ctxt_t *client_ctxt, list_t *list_head)
{
   mhi_bus_min_latency_t *client_bus_el = NULL;
   mhi_bus_min_latency_t *client_bus_next = NULL;

   /* if the list is empty return SUCCESS */
   if (list_is_empty(list_head)) {
      return MHI_SUCCESS;
   }

   /* check if the current client ctxt is present in the list */
   list_for_each_item(list_head, mhi_bus_min_latency_t, link, client_bus_el, client_bus_next)
   {
      /* if the client is present in the list, then delete the client from the list */
      if (client_bus_el->client_ctxt == client_ctxt)
      {
	 /* deleting the element from the list instead of updating the element and sorting because,
	  * sorting also will take time and also sorting doesnot help because, we need to override
	  * the value given by client in client ctxt with the default */
	 list_del(&client_bus_el->link);
	 /* TODO: instead of deleting the node, update the node and place it at the end of the list */
	 pcie_osal_free(client_bus_el);
	 break;
      }
   }

   return MHI_SUCCESS;
}

uint32 mhi_get_first_element_in_list(list_t *list_head, uint32 node)
{
   /* TBD */
   return MHI_SUCCESS;
}

/**
 * This function calls the function to add new client in the sorted client list and get the
 * first element of the list.
 *
 * @param[in]  client_ctxt 	Client Context
 * @param[in]  node         Node requested by the client
 * @param[in]  val          Value corresponding to the node
 *
 * @return Minimum calculated value
 */
uint32 mhi_node_bus_min_latency(mhi_client_ctxt_t *client_ctxt, mhi_node_t node, uint32 val)
{
	mhi_bus_min_latency_t *bus_el_t = NULL;
	mhi_bus_min_latency_t *client_node = NULL;
   uint32 min_latency = 0;

	client_node = mhi_drv_get_client_node(client_ctxt, node);
	if (client_node == NULL)
	{
	  MHI_LOG_ERROR("ERROR: mhi_drv_close_dev failed for dev 0x%x - no memory", client_ctxt->dev->dev_info.instance_id);
	  return NOMEM;
	}
	client_node->client_ctxt = client_ctxt;

	if(node == MHI_NODE_ACTIVE_BUS_LATENCY_US)
	{
		mhi_drv_add_node_bus(client_node, &mhi_drv->active_bus_latency_list, node, val);
		bus_el_t = list_get_item(&mhi_drv->active_bus_latency_list, mhi_bus_min_latency_t, link);
	}
	else if(node == MHI_NODE_BUS_RESUME_LATENCY_US)
	{
		mhi_drv_add_node_bus(client_node, &mhi_drv->bus_resume_latency_list, node, val);
		bus_el_t = list_get_item(&mhi_drv->bus_resume_latency_list, mhi_bus_min_latency_t, link);
	}

   if(bus_el_t)
   {
      if(bus_el_t->client_ctxt)
      {
         min_latency = bus_el_t->client_ctxt->issue_req[node].state;
      }
      else
      {
         min_latency = 0;
      }
   }

   return min_latency;
}

int32 mhi_drv_issue_request_stm(mhi_client_ctxt_t *client_ctxt, uint32 stm_info)
{
   int32 status;

   MHI_LOG_MED("mhi_drv_issue_request_stm : triggering link in L0 state stm mode 0x%x", stm_info);

   /*
   status = pcie_request_link_latency(client_ctxt->dev->pcie_dev_h, 0, stm_info);
   if (status != PCIE_SUCCESS) {
      MHI_LOG_HIGH("mhi_drv_issue_request_stm : pcie_request_link_latency failed");
      return status;
   }*/

   status = mhi_dev_wake_device_stm(client_ctxt->dev);
   if (status != MHI_SUCCESS) {
      MHI_LOG_HIGH("mhi_drv_issue_request_stm : Device wake up failed");
   }

   return status;
}

int32 mhi_drv_issue_request(mhi_client_ctxt_t *client_ctxt, mhi_node_t node, uint32 state)
{
   /* TBD */
   return MHI_SUCCESS;
}

int32 mhi_drv_complete_request(mhi_client_ctxt_t *client_ctxt , mhi_node_t node)
{
   /* TBD */
   return MHI_SUCCESS;
}

int32 mhi_drv_trigger_shutdown(mhi_dev_t *dev)
{
   if (dev == NULL)
   {
      MHI_LOG_ERROR("ERROR: mhi_drv_trigger_shutdown : dev handle NULL");
      return ERROR;
   }

	mhi_drv_notify_clients(MHI_DEV_SHUTDOWN_REQ, dev);

	return SUCCESS;
}
