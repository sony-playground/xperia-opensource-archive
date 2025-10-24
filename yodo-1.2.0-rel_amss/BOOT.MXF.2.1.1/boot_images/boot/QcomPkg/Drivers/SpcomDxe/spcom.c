/**
 @file  spcom.c
 */
/*=============================================================================
 Copyright (c) 2021 Qualcomm Technologies, Incorporated.
 All rights reserved.
 Qualcomm Technologies, Confidential and Proprietary.
 =============================================================================*/

/*=============================================================================
 EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 10/07/21   vp      Log SPU Shared Registers & update timeouts
 07/29/21   vp      Logging improvements
 05/19/21   vp      Increase SPCOM_SERVER_CMD_TIMEOUT to 300 ms
 04/29/21   vp      Increase open channel timeout to one second
 04/19/21   av      Open sTPM nvm channel only if TPM type is sTPM
 04/14/21   nc      spcom_unregister_client crash fix
 02/24/21   vp      Expose poll_on_nvm_ch for spcomdxe clients
 02/16/21   vp      Fix wrong length passed to notify_server_request_cb()
 02/08/21   vp      Fix stpm channel names
 01/11/21   vp      Load API's fix and add new line character in log prints.
 12/16/20   nc      Change stpm_lite to stpm_lite_msft and minor bug fixes
 12/10/20   vp      Change log level from error to info, for success cases
 11/06/20   vp      Update PIL region memory map & reduce SPSS timeout to 90ms
 06/15/20   vp      initial release
 =============================================================================*/
/*
 * Secure-Processor-Communication (SPCOM).
 *
 * This driver provides communication to Secure Processor (SP)
 * over G-Link transport layer.
 *
 * No message routing is use, but using the G-Link "multiplexing" feature
 * to use a dedicated logical channel for UEFI/HLOS and SP Application-Pair.
 *
 * UEFI Application can either be Client or Server.
 * Messaging is allays point-to-point between 2 UEFI<=>SP applications.
 *
 * This driver registers to G-Link callbacks to be aware on channel state.
 * A notify callback is called upon channel connect/disconnect.
 *
 */

#include "stringl/stringl.h"  // strnlen()

#include <Protocol/EFIGLink.h>
#include <Protocol/EFIHWIO.h>
#include <Library/glink.h>

#include "spcom.h"

#include <Uefi.h>
#include <Library/QcomLib.h>
#include <PrintShLib.h>
#include <HALhwio.h>
#include "HALbootHWIO.h"
#include <Library/UefiBootServicesTableLib.h>

extern EFI_GLINK_PROTOCOL * glink_protocol;

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * ----------------------------------------------------------------------*/

/* "SPCM" string */
#define SPCOM_MAGIC_ID ((size_t)(0x5350434D))

/* Request/Response */
#define SPCOM_FLAG_REQ         BIT(0)
#define SPCOM_FLAG_RESP        BIT(1)
#define SPCOM_FLAG_ENCODED     BIT(2)
#define SPCOM_FLAG_NON_ENCODED BIT(3)

/* SPCOM driver name */
#define DEVICE_NAME    "spcom"
static const char *skp_ch_name = "sp_kernel";

#define SPCOM_MAX_CHANNELS     20

const char* nvmAppNamesList[] = {
   "sec_nvm_sp_nvm",
   "sec_nvm_stpm_lite_msft"
};

// SPSS Apps Info
typedef struct _sp_app_info_t {
    const char*     ch_name;
    uint32_t        id;
    uint64_t        app_load_ddr_offset;
    uint32_t        app_load_size;
    uint64_t        cmd_buf_ddr_offset;
    uint32_t        cmd_buf_size;
} sp_app_info_t;

static sp_app_info_t sp_apps_info[] = {
      /*
       * asym_cryptoapp, cryptoapp, macchiato
       * entry are added, just to check its load status
       * using spcom_is_app_loaded() api
       */
       {
           .ch_name = "asym_cryptoapp",
           .id = 0x3D86A887,
       },
       {
           .ch_name = "cryptoapp",
           .id = 0xEF80345E,
       },
       {
           .ch_name = "macchiato",
           .id = 0x09068e40,
       },
       {
           .ch_name = "stpm_lite_msft",
           .id = 0xC58B78EB,
           /* The 12 KB region is shared memory
            * region, used for TPM clients in UEFI
            * with sTPM_lite application in SPU
            */
           .cmd_buf_ddr_offset = 0x85972000,
           .cmd_buf_size = 12 *1024,
       },
       {
           .ch_name = "stpm_full_msft",
           .id = 0xbbbbbbbb,
           .app_load_ddr_offset = 0x85860000,
           .app_load_size = 1024 *1024,
       },
       {
           .ch_name = "sec_nvm_stpm_lite_msft",
           .cmd_buf_ddr_offset = 0x85960000,
           .cmd_buf_size = 36 *1024,
       },
       {
           .ch_name = "sec_nvm_sp_nvm",
           .cmd_buf_ddr_offset = 0x85969000,
           .cmd_buf_size = 36 *1024,
       },
       /* This app is used for test purposes */
       {
           .ch_name = "echo",
           .id = 0x174A9EF9,
           .app_load_ddr_offset = 0x85975000,
           .app_load_size = 64 * 1024,
       }
};

/* sp_nvm and stpm_lite_nvm */
#define SPCOM_MAX_NVM_SERVICES     2

/* Maximum command size */
#define SPCOM_MAX_COMMAND_SIZE (PAGE_SIZE)

/* Maximum input size */
#define SPCOM_MAX_READ_SIZE    (PAGE_SIZE)

/* Maximum channel name size (including null) - matching GLINK_NAME_SIZE */
#define MAX_CH_NAME_LEN        32

/* Connection negotiation timeout, if remote channel is open */
#define OPEN_CHANNEL_TIMEOUT_MSEC      2000

#define SPCOM_SERVER_CMD_TIMEOUT       1000

#define NVM_CHANNEL_POLL_TIMEOUT       1
/*
 * After both sides get CONNECTED,
 * there is a race between once side queuing rx buffer and the other side
 * trying to call glink_tx() , this race is only on the 1st tx.
 * do tx retry with some delay to allow the other side to queue rx buffer.
 */
#define TX_RETRY_DELAY_MSEC    10

/* number of tx retries */
#define TX_MAX_RETRY   100

/* SPCOM_MAX_REQUEST_SIZE-or-SPCOM_MAX_RESPONSE_SIZE + header */
#define SPCOM_RX_BUF_SIZE      300

/* The SPSS RAM size is 256 KB so SP App must fit into it */
#define SPCOM_MAX_APP_SIZE     SZ_256K

/*
 * ACK timeout from remote side for TX data.
 * Normally, it takes few msec for SPSS to response with ACK for TX data.
 * However, due to SPSS limitations, the SPSS might disable interrupts
 * for a very long time.
 */
#define TX_DONE_TIMEOUT_MSEC   1000

/*
 * Initial transaction id, use non-zero nonce for debug.
 * Incremented by client on request, and copied back by remote server on response.
 */
#define INITIAL_TXN_ID 0x12345678

/**
 * struct spcom_msg_hdr - Request/Response message header between HLOS and SP.
 *
 * This header is proceeding any request specific parameters.
 * The transaction id is used to match request with response.
 * Note: glink API provides the rx/tx data size, so user payload size is
 * calculated by reducing the header size.
 */
struct spcom_msg_hdr
{
   uint32_t reserved; /* for future use */
   uint32_t txn_id; /* transaction id */
   char buf[0]; /* Variable buffer size, must be last field */
}__attribute__((__packed__));

#define SPCOM_CMD_RESET_SP        0x52455354 /* "REST" = 0x52455354 */

/**
 * struct spcom_reset_cmd_req - Reset Request sent to SP
 */
struct spcom_reset_cmd_req
{
   uint32_t cmd_id;
}__attribute__((__packed__));

/**
 * struct spcom_reset_resp - Reset Response from SP.
 */
struct spcom_reset_resp
{
   uint32_t error_code; /* 0 for success, errors based on errno.h */
}__attribute__((__packed__));

/**
 * struct spcom_client - Client handle
 */
struct spcom_client
{
   struct spcom_channel *ch;
};

/**
 * struct spcom_server - Server handle
 */
struct spcom_server
{
   struct spcom_channel *ch;
   int next_request_size;
   bool got_request;
   void * server_param;
};

/**
 * struct spcom_channel - channel context
 */
struct spcom_channel
{
   char name[MAX_CH_NAME_LEN];
   void *glink_handle;
   size_t txn_id; /* incrementing nonce per channel */
   boolean is_server; /* for txn_id and response_timeout_msec */
   void
   (*notify_server_request_cb) (struct spcom_server *, const void*, size_t,
                                void**, size_t * const, void * server_param);
   /*
    * glink state: CONNECTED / LOCAL_DISCONNECTED, REMOTE_DISCONNECTED
    */
   glink_channel_event_type glink_state;

   /* Events notification */
   struct spcom_os_event connect;
   struct spcom_os_event disconnect;
   struct spcom_os_event tx_done;
   struct spcom_os_event rx_done;

   /*
    * Only one client per channel.
    * Only one rx/tx transaction at a time (request + response).
    */
   int ref_count;

   /* link UP/DOWN callback */
   void
   (*notify_link_state_cb) (boolean up);

   /* abort flags */
   boolean rx_abort;
   boolean tx_abort;

   /* rx data info */
   size_t rx_buf_size; /* allocated rx buffer size */
   boolean rx_buf_ready;
   size_t actual_rx_size; /* actual data size received */
   const void *glink_rx_buf; /* provided by glink callback */

   /* debug */
   int rx_done_counter;
   int tx_done_counter;

   size_t magic; /* unique value to verify context is valid, see SPCOM_MAGIC_ID */
};

/**
 * struct spcom_device - device state structure.
 */
struct spcom_device
{
   /* G-Link channels */
   struct spcom_channel channels[SPCOM_MAX_CHANNELS];

   /* G-Link channels */
   struct spcom_server nvm_servers[SPCOM_MAX_NVM_SERVICES];

   /* Link state */
   struct spcom_os_event link_state_changed;
   glink_link_state_type link_state;
};

#ifdef SPCOMDXE_SANITY_TEST
typedef enum {
     ARI_FUSE_NOT_CONFIGURED = 0x0,
     ARI_FUSE_NO_CAP         = 0x1,
     ARI_FUSE_ON             = 0x2,
     ARI_FUSE_RESERVED       = 0x3, // also interpreted as ON
} sp_health_ari_on_fuse_t;
/**
 * Enums used to request SP health data.
 * More than single value can be requested
 * TODO: define as bits
 */
typedef enum {
    SP_HEALTH_ARI_MODE = 0,
    SP_HEALTH_ARI_FUSE_GAUGE = 1,
    SP_HEALTH_FIPS_ENABLED = 2,
    SP_HEALTH_FIPS_SELF_TEST = 3,
    SP_HEALTH_SENSORS_CALIBRATED = 4,
    SP_HEALTH_ALL_TESTS = 5,
    SP_HEALTH_GET_ARI_ON_FUSE = 6,
    SP_HEALTH_LAST         //Used to know how many enums there are
} sp_health_status_t;

typedef struct
{
   uint32_t ari_mode;
   uint32_t ari_fuse_gauge;
   uint32_t fips_enabled;
   uint32_t fips_self_test_passed;
   uint32_t sensors_calibrated;
   uint32_t ari_on_fuse;
   uint32_t por_indicator;
   uint32_t por_counter;
   uint32_t aux_data0;
   uint32_t aux_data1;
   uint32_t aux_data2;
   uint32_t aux_data3;
   uint32_t iar_ce_status;
} sp_health_status_data;

typedef struct _sp_health_request_t {
    uint32_t cmd_opcode;
    uint32_t type_of_check;
} sp_health_request_t;

typedef struct _sp_health_response_t {
    uint32_t error_code;
    sp_health_status_data checks_values;
} sp_health_response_t;
#endif


#define MAX_APP_SIZE  (200 * 1024)
#define SWAP_APP_SIZE  (512 * 1024)
uint32_t SPCOM_CMD_LOAD_APP = 0x4C4F4144; /* "LOAD" = 0x4C4F4144 */

/**
 * struct spcom_load_app_req - Load App Request sent to SP
 *
 * The application image binary is placed on DDR buffer.
 * The application image is encrypted and signed.
 * The DDR buffer address and size should be 4K aligned for XPU protection.
 * The size of the app DDR buffer is larger than the image size to allow saving
 * the app heap and stack on swap in/out.
 */
struct __attribute__((__packed__)) spcom_load_app_req {
       uint32_t cmd_id;        /* SPCOM_CMD_LOAD_APP */
       uint32_t image_size;
       uint64_t buf_phys_addr; /* kernel physical address */
       char ch_name[16];
       uint32_t full_ddr_swap_size; /* ION buffer size */
       uint32_t cmac[(16/sizeof(uint32_t))];
};

/**
 * struct spcom_load_app_resp - Load App Response from SP.
 */
struct spcom_load_app_resp {
       uint32_t error_code; /* 0 for success, errors based on errno.h */
};

typedef struct _sp_sysparam_read_request_t {
    uint32_t cmd_opcode;
    uint32_t sysparam_id;
    uint32_t sysparam_arg1;
    uint32_t sysparam_arg2;
} sp_sysparam_read_request_t;

typedef struct _sp_sysparam_read_response_t {
    uint32_t error_code;
    uint32_t sysparam_value;
} sp_sysparam_read_response_t;

/**
 * List of predefined SP system parameters.
 */
typedef enum {
    SP_SYSPARAM_ID_FIRST,
    SP_SYSPARAM_ID_BUILD_VERSION = SP_SYSPARAM_ID_FIRST,    // Read-Only
    SP_SYSPARAM_ID_BUILD_VERSION_HASH,                      // Read-Only
    SP_SYSPARAM_ID_ARI_CONFIG,                              // Write-Only
    SP_SYSPARAM_ID_APP_BUILD_VERSION,                       // Read-Only
    SP_SYSPARAM_ID_APP_BUILD_VERSION_HASH,                  // Read-Only
    SP_SYSPARAM_ID_HW_VERSION,                              // Read-Only
    SP_SYSPARAM_ID_FIPS_OVERRIDE,                           // Write-Only
    SP_SYSPARAM_ID_LAST,
} sp_sysparam_id_enum;

typedef enum _sp_command_enum {
    SP_CMD_ID_FIRST = 1000,
    SP_CMD_ID_CHECK_SP_HEALTH = SP_CMD_ID_FIRST,
    SP_CMD_ID_SYSPARAM_READ,
    SP_CMD_ID_SYSPARAM_WRITE,
} sp_command_enum;

#define SP_CNOC_SP_SCSR_BASE_ADDR                 0x1880000
#define SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS     0x188101C
#define SP_CNOC_SP_SCSR_RMB_ERR_STATUS            0x188103C
#define SP_CNOC_SP_SCSR_RMB_ERR_STATUS_SPAREm(m)  (0x188200C + (0x4*m))
#define SP_SCSR_REGISTER_ACCESS_ERROR             0xDEADBEEF

static const char *spcom_edge = "spss";
static const char *spcom_transport = "SMEM";

/* Device Driver State */
static struct spcom_device *spcom_dev;
static boolean spcom_link_up_registered = false;
static glink_link_handle_type glink_link_handle = NULL;
static glink_link_state_type glink_link_state = GLINK_LINK_STATE_DOWN;

// Health API/System Params service client variables
struct spcom_client* g_service_client = NULL;
uint32_t g_active_service_client_counter = 0;

// Apploader Service client
struct spcom_client* skp_service_client = NULL;
uint32_t skp_active_service_client_counter = 0;

STATIC UINT32* gpSPRegister = NULL;

/* static functions declaration */
static EFI_STATUS
spcom_open (struct spcom_channel *ch, unsigned int timeout_msec);
static EFI_STATUS
spcom_close (struct spcom_channel *ch);
static EFI_STATUS
spcom_suspend (void);
static EFI_STATUS
spcom_sleep (int timeout_msec);
static EFI_STATUS
spcom_exit_channel (struct spcom_channel *ch);
static EFI_STATUS spcom_map_sp_registers( VOID );
static UINT32 spcom_read_sp_registers(UINT32 addr);

static boolean
spcom_is_link_up (void)
{
   EFI_STATUS status = EFI_SUCCESS;
   glink_err_type ret = GLINK_STATUS_FAILURE;

   if (spcom_dev == NULL)
   {
      LOGE("spcom_is_link_up: spcom_dev NULL \r\n");
      return false;
   }

   if (glink_link_handle == NULL)
   {
      LOGE("spcom_is_link_up: glink_link_handle NULL \r\n");
      return false;
   }

   if (spcom_dev->link_state == GLINK_LINK_STATE_UP)
   {
      LOGI("spcom_is_link_up:: glink is up already.  \r\n");
      return true;
   }

   status = glink_protocol->GlinkLinkStatePoll (glink_link_handle,
                                               &glink_link_state, &ret);

   if (GLINK_STATUS_SUCCESS == ret && EFI_SUCCESS == status)
   {
      if (spcom_dev->link_state == GLINK_LINK_STATE_UP)
      {
         LOGI("spcom_is_link_up:: glink is up.  \r\n");
         return true;
      }
      else
      {
         LOGE("spcom_is_link_up:: glink is not up. link_state = %d \r\n",
               spcom_dev->link_state);
         return false;
      }
   }
   else
   {
      LOGE("spcom_is_link_up:: GlinkLinkStatePoll failed"
            " status = %x, glinkRet = %d. \r\n", status, ret);
      return false;
   }
}

/**
 * spcom_is_channel_open() - channel is open on this side.
 *
 * Channel might not be fully connected if remote side didn't open the channel
 * yet.
 */
static inline boolean
spcom_is_channel_open (struct spcom_channel *ch)
{
   return (ch->glink_handle != NULL);
}

/**
 * spcom_is_channel_connected() - channel is fully connected by both sides.
 */
static inline boolean
spcom_is_channel_connected (struct spcom_channel *ch)
{
   return spcom_os_is_event_signaled (&ch->connect);
}

/*======================================================================*/
/*             GLINK CALLBACKS                                         */
/*======================================================================*/

/**
 * spcom_link_state_notif_cb() - glink callback for link state change.
 *
 * glink notifies link layer is up, before any channel opened on remote side.
 * Calling glink_open() locally allowed only after link is up.
 * Notify link down, normally upon Remote Subsystem Reset (SSR).
 * Note: upon SSR, glink will also notify each channel about remote disconnect,
 * and abort any pending rx buffer.
 */
static void
spcom_link_state_notif_cb (glink_link_info_type *cb_info, void *priv)
{
   spcom_dev->link_state = cb_info->link_state;

   LOGI("spcom_link_state_notif_cb called. transport = %a remote_ss = %a\n", cb_info->xport, cb_info->remote_ss);

   switch (cb_info->link_state)
   {
      case GLINK_LINK_STATE_UP:
         LOGI("Received SPCOM_LINK_STATE_NOTIF_CB_UP\n");
         break;
      case GLINK_LINK_STATE_DOWN:
         LOGI("Received SPCOM_LINK_STATE_NOTIF_CB_DOWN\n");
         break;
      default:
    	 LOGE("Received SPCOM_LINK_STATE_NOTIF_CB_UNK, cb_info->link_state\n");
         break;
   }
   spcom_os_signal_event (&spcom_dev->link_state_changed);
}

/**
 * spcom_notify_rx() - glink callback on receiving data.
 *
 * Glink notify rx data is ready. The glink internal rx buffer was
 * allocated upon glink_queue_rx_intent().
 */
static void
spcom_notify_rx (glink_handle_type handle, const void *priv,
                 const void *pkt_priv, const void *buf, size_t size,
                 size_t intent_used)
{
   struct spcom_channel *ch = (struct spcom_channel *) priv;

   if (!ch)
   {
      LOGE("SPCOM_NOTIFY_RX_INVAL\n");
      return;
   }

   ch->actual_rx_size = size;
   ch->glink_rx_buf = (void *) buf;
   spcom_os_signal_event (&ch->rx_done);
}

/**
 * spcom_notify_tx_done() - glink callback on ACK sent data.
 *
 * after calling glink_tx() the remote side ACK receiving the data.
 */
static void
spcom_notify_tx_done (glink_handle_type handle, const void *priv,
                      const void *pkt_priv, const void *buf, size_t size)
{
   struct spcom_channel *ch = (struct spcom_channel *) priv;

   if (!ch)
   {
      LOGE("SPCOM_NOTIFY_DONE_INVAL\n");
      return;
   }

   spcom_os_signal_event (&ch->tx_done);
}

/**
 * spcom_notify_state() - glink callback on channel connect/disconnect.
 *
 * Channel is fully CONNECTED after both sides opened the channel.
 * Channel is LOCAL_DISCONNECTED after both sides closed the channel.
 * If the remote side closed the channel, it is expected that the local side
 * will also close the channel.
 * Upon connection, rx buffer is allocated to receive data,
 * the maximum transfer size is agreed by both sides.
 */
static void
spcom_notify_state (glink_handle_type handle, const void *priv,
                    glink_channel_event_type event)
{
   int ret;
   EFI_STATUS status = EFI_SUCCESS;
   struct spcom_channel *ch = (struct spcom_channel *) priv;
   LOGI("spcom_notify_state, event [%d].\n", event);

   switch (event)
   {
      case GLINK_CONNECTED:
         LOGI("GLINK_CONNECTED, ch name [%a].\n", ch->name);

         /*
          * if spcom_notify_state() is called within glink_open()
          * then ch->glink_handle is not updated yet.
          */
         if (!ch->glink_handle)
         {
            LOGI("update glink_handle, ch [%a].\n", ch->name);
            ch->glink_handle = handle;
         }
         spcom_os_set_event_glink_handle (&ch->connect, handle);
         spcom_os_set_event_glink_handle (&ch->disconnect, handle);
         spcom_os_set_event_glink_handle (&ch->tx_done, handle);
         spcom_os_set_event_glink_handle (&ch->rx_done, handle);

         /* prepare default rx buffer after connected */
         status = glink_protocol->GlinkQueueRxIntent (ch->glink_handle, ch,
                                                      ch->rx_buf_size, &ret);
         if (EFI_ERROR (status) || (GLINK_STATUS_SUCCESS != ret))
         {
        	 LOGI("spcom_rx:: GlinkQueueRxIntent failure status = %x, glink_ret = %d.  \r\n", status, ret);
         }
         else
         {
        	LOGI("rx buf is ready, size [%d].\n", ch->rx_buf_size);
            ch->rx_buf_ready = true;
         }

         spcom_os_signal_event (&ch->connect);
         break;
      case GLINK_LOCAL_DISCONNECTED:
         /*
          * Channel state is GLINK_LOCAL_DISCONNECTED
          * only after *both* sides closed the channel.
          */
         LOGI("GLINK_LOCAL_DISCONNECTED, ch [%a].\n", ch->name);
         spcom_os_signal_event (&ch->disconnect);
         break;
      case GLINK_REMOTE_DISCONNECTED:
         /*
          * Remote side initiates glink_close().
          * This is not expected on normal operation.
          * This may happen upon remote SSR.
          */
         LOGI("GLINK_REMOTE_DISCONNECTED, ch [%a].\n", ch->name);
         /*
          * after glink_close(),
          * expecting notify GLINK_LOCAL_DISCONNECTED
          */
         spcom_close (ch);
         spcom_exit_channel (ch); /* reset channel context */
         break;
      default:
         LOGE("SPCOM_NOTIFY_STATE_UNK_EV, event\n");
         return;
   }

   ch->glink_state = event;
}

/**
 * spcom_notify_rx_intent_req() - glink callback on intent request.
 *
 * glink allows the remote side to request for a local rx buffer if such
 * buffer is not ready.
 * However, for spcom simplicity on SP, and to reduce latency, we decided
 * that glink_tx() on both side is not using INTENT_REQ flag, so this
 * callback should not be called.
 * Anyhow, return "false" to reject the request.
 */
static boolean
spcom_notify_rx_intent_req (glink_handle_type handle, const void *priv,
                            size_t req_size)
{
   LOGE("SPCOM_NOTIFY_RX_INTENT_REQ\n");

   return false;
}

/**
 * spcom_notify_rx_abort() - glink callback on aborting rx pending buffer.
 *
 * Rx abort may happen if channel is closed by remote side, while rx buffer is
 * pending in the queue.
 */
static void
spcom_notify_rx_abort (glink_handle_type handle, const void *priv,
                       const void *pkt_priv)
{
   struct spcom_channel *ch = (struct spcom_channel *) priv;

   LOGI("ch [%a] pending rx aborted.\n", ch->name);

   if (spcom_is_channel_open (ch))
   {
      ch->rx_abort = true;
      spcom_os_signal_event (&ch->rx_done);
   }
}

/**
 * spcom_notify_tx_abort() - glink callback on aborting tx data.
 *
 * This is probably not relevant, since glink_txv() is not used.
 * Tx abort may happen if channel is closed by remote side,
 * while multiple tx buffers are in a middle of tx operation.
 */
static void
spcom_notify_tx_abort (glink_handle_type handle, const void *priv,
                       const void *pkt_priv)
{
   struct spcom_channel *ch = (struct spcom_channel *) priv;

   LOGE("ch [%a] pending tx aborted.\n", ch->name);

   if (spcom_is_channel_connected (ch))
   {
      spcom_os_signal_event (&ch->tx_done);
      ch->tx_abort = true;
   }
}

static void spcom_check_if_spss_crashed (void)
{
	EFI_STATUS status = EFI_SUCCESS;
	uint32 sp2soc = 0xFF;
	uint32 rmberr = 0x88;
	uint32 spare0 = 0x77;
	uint32 spare1 = 0x77;
	uint32 spare2 = 0x77;

	status =  spcom_map_sp_registers();
	if (EFI_ERROR (status))
	{
		LOGE("spcom_map_sp_registers failed status = %x \r\n", status);
		return;
	}
	/*
	 * Check PBL error registers, to see
	 * if SPU has crashed
	 */
	sp2soc = spcom_read_sp_registers(SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS);
	if(sp2soc == SP_SCSR_REGISTER_ACCESS_ERROR){
		return;
	}
	LOGE("value at SP2SOC_IRQ_STATUS 0x%x is = 0x%x", SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS, sp2soc);

	rmberr = spcom_read_sp_registers(SP_CNOC_SP_SCSR_RMB_ERR_STATUS);
	if(rmberr == SP_SCSR_REGISTER_ACCESS_ERROR){
		return;
	}
	LOGE("value at RMB_ERR_STATUS 0x%x is = 0x%x", SP_CNOC_SP_SCSR_RMB_ERR_STATUS, rmberr);

	spare0 = spcom_read_sp_registers(SP_CNOC_SP_SCSR_RMB_ERR_STATUS_SPAREm(0));
	if(spare0 == SP_SCSR_REGISTER_ACCESS_ERROR){
		return;
	}
	LOGE("value at spare0 0x%x is = 0x%x", SP_CNOC_SP_SCSR_RMB_ERR_STATUS_SPAREm(0), spare0);

	spare1 = spcom_read_sp_registers(SP_CNOC_SP_SCSR_RMB_ERR_STATUS_SPAREm(1));
	if(spare1 == SP_SCSR_REGISTER_ACCESS_ERROR){
		return;
	}
	LOGE("value at spare1 0x%x is = 0x%x", SP_CNOC_SP_SCSR_RMB_ERR_STATUS_SPAREm(1), spare1);

	spare2 = spcom_read_sp_registers(SP_CNOC_SP_SCSR_RMB_ERR_STATUS_SPAREm(2));
	if(spare2 == SP_SCSR_REGISTER_ACCESS_ERROR){
		return;
	}
	LOGE("value at spare2 0x%x is = 0x%x", SP_CNOC_SP_SCSR_RMB_ERR_STATUS_SPAREm(2), spare2);

	return;
}

static EFI_STATUS
spcom_register_link_up_notification (void)
{
   EFI_STATUS status = EFI_SUCCESS;
   glink_err_type ret = GLINK_STATUS_FAILURE;
   glink_link_id_type link_info = {};
   int i = 0;
   uint32 sp2soc = 0xFF;

   status =  spcom_map_sp_registers();
   if (EFI_ERROR (status))
   {
      return status;
   }

   /* Register for native transport notifications */
   GLINK_LINK_ID_STRUCT_INIT(link_info);
   link_info.xport = spcom_transport;
   link_info.remote_ss = spcom_edge; /* notify only spss link up */

   link_info.link_notifier = &spcom_link_state_notif_cb;

   /*Register link state callback*/
   status = glink_protocol->GlinkRegisterLinkStateCB (&link_info, NULL, &ret);
   if ((EFI_ERROR (status)) || (GLINK_STATUS_SUCCESS != ret))
   {
      LOGE("spcom_glink_Init:: registerLinkStateCB failed"
            " status = %x, glinkRet = %d. \r\n", status, ret);
      return EFI_DEVICE_ERROR;
   }
   else
   {
      glink_link_handle = link_info.handle;
   }

   /* NOTE: UEFI Application that communicates with SP should be loaded after SPSS-PIL */
   /* Check sp2soc value for 90 ms before attempting sending any cmds to SPU */

   while (i++ < 9)
   {
      sp2soc = spcom_read_sp_registers(SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS);
      if(sp2soc == SP_SCSR_REGISTER_ACCESS_ERROR){
         return EFI_DEVICE_ERROR;
      }
      if (sp2soc == 0x0300000F){
         status = glink_protocol->GlinkLinkStatePoll (glink_link_handle, &glink_link_state, &ret);
         if (glink_link_state == GLINK_LINK_STATE_UP){
            break;
         }
      }
      spcom_os_msleep (10); //10 ms
   }

   if (glink_link_state != GLINK_LINK_STATE_UP)
   {
	   LOGE("After GlinkLinkStatePoll, , glink NOT UP\n");
	   spcom_check_if_spss_crashed();
       return EFI_TIMEOUT;
   }

   return status;
}

/*======================================================================*/
/*             UTILITIES                                               */
/*======================================================================*/

/**
 * spcom_init_open_config() - Fill glink_open() configuration parameters.
 *
 * @cfg: glink configuration struct pointer
 * @name: channel name
 * @priv: private caller data, provided back by callbacks, channel state.
 *
 * specify callbacks and other parameters for glink open channel.
 */
static void
spcom_init_open_config (glink_open_config_type *cfg, const char *name,
                        void *priv)
{
   cfg->notify_rx = spcom_notify_rx;
   cfg->notify_rxv = NULL;
   cfg->notify_tx_done = spcom_notify_tx_done;
   cfg->notify_state = spcom_notify_state;
   cfg->notify_rx_intent_req = spcom_notify_rx_intent_req;
   cfg->notify_rx_sigs = NULL;
   cfg->notify_rx_abort = spcom_notify_rx_abort;
   cfg->notify_tx_abort = spcom_notify_tx_abort;

   cfg->options = 0; /* not using GLINK_OPT_INITIAL_XPORT */
   cfg->priv = priv; /* provided back by callbacks */

   cfg->name = name;

   cfg->transport = spcom_transport;
   cfg->remote_ss = spcom_edge;
}

/**
 * spcom_init_channel() - initialize channel state.
 *
 * @ch: channel state struct pointer
 * @name: channel name
 */
static EFI_STATUS
spcom_init_channel (struct spcom_channel *ch, const char *name)
{
   if (!ch || !name || !name[0])
   {
      LOGE("SPCOM_INIT_CH_INVAL\n");
      return EFI_INVALID_PARAMETER;
   }

   if (strnlen (name, sizeof(ch->name)) > sizeof(ch->name) - 1)
   { /* last place for NULL */
      LOGE("SPCOM_INIT_NAME_TOO_LONG\n");
      return EFI_INVALID_PARAMETER;
   }

   strlcpy (ch->name, name, sizeof(ch->name));

   spcom_os_init_event (&ch->connect);
   spcom_os_init_event (&ch->disconnect);
   spcom_os_init_event (&ch->tx_done);
   spcom_os_init_event (&ch->rx_done);

   ch->glink_state = GLINK_LOCAL_DISCONNECTED;
   ch->actual_rx_size = 0;
   ch->rx_buf_size = SPCOM_RX_BUF_SIZE;

   return EFI_SUCCESS;
}

static EFI_STATUS
spcom_exit_channel (struct spcom_channel *ch)
{
   /* keep the channel name, just reset the events */

   spcom_os_reset_event (&ch->connect);
   spcom_os_reset_event (&ch->disconnect);
   spcom_os_reset_event (&ch->tx_done);
   spcom_os_reset_event (&ch->rx_done);

   ch->glink_state = GLINK_LOCAL_DISCONNECTED;
   ch->actual_rx_size = 0;
   ch->rx_buf_size = SPCOM_RX_BUF_SIZE;

   ch->magic = 0xDEADBEEF; /* protect from user using invalid client handle */

   return EFI_SUCCESS;
}

/**
 * spcom_find_channel_by_name() - find a channel by name.
 *
 * @name: channel name
 *
 * Return: a channel state struct.
 */
static struct spcom_channel *
spcom_find_channel_by_name (const char *name)
{
   int i;
   for (i = 0; i < SPCOM_MAX_CHANNELS; i++)
   {
      struct spcom_channel *ch = &spcom_dev->channels[i];

      if (strcmp (ch->name, name) == 0)
      {
         LOGI("channel [%a] found.\n", ch->name);
         return ch;
      }
   }
   LOGI("failed to find channel [%a].\n", name);

   return NULL;
}

/**
 * spcom_open() - Open glink channel and wait for connection ACK.
 *
 * @ch: channel state struct pointer
 *
 * Normally, a local client opens a channel after remote server has opened
 * the channel.
 */
static EFI_STATUS
spcom_open (struct spcom_channel *ch, unsigned int timeout_msec)
{
   EFI_STATUS status = EFI_SUCCESS;
   int ret = 0;
   glink_open_config_type cfg = {};
   long timeleft = 0;
   const char *name = NULL;
   glink_handle_type handle = 0;

   name = ch->name;

   /* only one client may use the channel */
   if (ch->ref_count)
   {
      LOGE("SPCOM_OPEN_BUSY\n");
      return EFI_DEVICE_ERROR;
   }
   ch->ref_count++;
   ch->txn_id = INITIAL_TXN_ID;
   ch->rx_abort = 0;
   ch->tx_abort = 0;

   LOGI("ch [%a] opened, count [%d]\n", name, ch->ref_count);

   LOGI("Open channel [%a] timeout_msec [%d].\n", name, timeout_msec);

   if (spcom_is_channel_open (ch))
   {
      LOGI("channel [%a] already open.\n", name);
      return EFI_SUCCESS;
   }

   spcom_init_open_config (&cfg, name, ch);

   /* init spcom_os_event before calling glink_open() */
   spcom_os_reset_event (&ch->connect);

   status = glink_protocol->GlinkOpen (&cfg, &handle, &ret);
   if ((EFI_ERROR (status)) || (GLINK_STATUS_SUCCESS != ret))
   {
      LOGE("spcom_open:: GlinkOpen failed "
            "status = %x, glinkRet = %d. \r\n", status, ret);
      return status;
   }
   LOGI("glink_open [%a] ok.\n", name);

   ch->glink_handle = handle;
   /* must provide handle before polling event */
   spcom_os_set_event_glink_handle (&ch->connect, handle);
   spcom_os_set_event_glink_handle (&ch->disconnect, handle);
   spcom_os_set_event_glink_handle (&ch->tx_done, handle);
   spcom_os_set_event_glink_handle (&ch->rx_done, handle);

   LOGI("Wait for connection on channel [%a] timeout_msec [%d].\n", name, timeout_msec);

   /* Wait for remote side to connect */
   if (timeout_msec)
   {
      timeleft = spcom_os_wait_for_event_with_timeout (&(ch->connect),
                                                       timeout_msec);
      if (timeleft == 0)
      {
         LOGE("Channel [%a] is NOT connected.\n", name);
         spcom_check_if_spss_crashed();
         status = EFI_TIMEOUT;
      }
      else
      {
         LOGI("Channel [%a] fully connect.\n", name);
      }
   }
   else
   {
      LOGI("wait for connection ch [%a] no timeout.\n", name);
      timeleft = spcom_os_wait_for_event (&(ch->connect));
      if (timeleft == 0)
      {
         LOGE("Channel [%a] is NOT connected.\n", name);
         spcom_check_if_spss_crashed();
         status = EFI_TIMEOUT;
      }
      else
      {
         LOGI("Channel [%a] fully connect.\n", name);
      }
   }

   return status;
}

/**
 * spcom_close() - Close glink channel.
 *
 * @ch: channel state struct pointer
 *
 * A calling API functions should wait for disconnecting by both sides.
 */
static EFI_STATUS
spcom_close (struct spcom_channel *ch)
{
   EFI_STATUS status = EFI_SUCCESS;
   int ret = 0;

   if (!spcom_is_channel_open (ch))
   {
      LOGE("SPCOM_CLOSE_CLOSED\n");
      return EFI_SUCCESS;
   }

   status = glink_protocol->GlinkClose (ch->glink_handle, &ret);
   if ((EFI_ERROR (status)) || (GLINK_STATUS_SUCCESS != ret))
   {
      LOGE("spcom_close:: GlinkClose failed "
            "status = %x, glinkRet = %d. \r\n", status, ret);
   }
   LOGI("GlinkClose ok.\n");

   ch->glink_handle = NULL;
   ch->ref_count = 0;

   ch->txn_id = INITIAL_TXN_ID; /* use non-zero nonce for debug */

   LOGI("Channel closed [%a].\n", ch->name);

   return status;
}

/**
 * spcom_tx() - Send data and wait for ACK or timeout.
 *
 * @ch: channel state struct pointer
 * @buf: buffer pointer
 * @size: buffer size
 *
 * ACK is expected within a very short time (few msec).
 */
static EFI_STATUS
spcom_tx (struct spcom_channel *ch, void *buf, size_t size, size_t timeout_msec)
{
   EFI_STATUS status = EFI_SUCCESS;
   int ret = 0;
   void *pkt_priv = NULL;
   size_t tx_flags = 0; /* don't use GLINK_TX_REQ_INTENT */
   long timeleft = 0;
   int retry = 0;
   
   /* reset spcom_os_event before calling glink */
   spcom_os_reset_event (&ch->tx_done);

   for (retry = 0; retry < TX_MAX_RETRY; retry++)
   {

      glink_protocol->GlinkRxPoll (ch->glink_handle, &ret); // glink check his own DB ??

      status = glink_protocol->GlinkTx (ch->glink_handle, pkt_priv, buf, size,
                                        tx_flags, &ret);

      if ((EFI_ERROR (status)) || (GLINK_STATUS_SUCCESS != ret))
      {
          LOGI("spcom_tx:: glink tx failed status = %d.ret = %d \r\n", status, ret);
      }
      if (ret == GLINK_STATUS_NO_REMOTE_INTENT_FOUND)
      {
         //LOGE("glink_tx() fail, try again.");
         /*
          * Delay to allow remote side to queue rx buffer.
          * This may happen after the first channel connection.
          */
         spcom_os_msleep (TX_RETRY_DELAY_MSEC);
      }
      else if (ret != GLINK_STATUS_SUCCESS)
      {
         LOGE("SPCOM_TX_GLINK_TX_FAILED: %d\n", ret);
         return EFI_DEVICE_ERROR;
      }
      else
      {
         break; /* no retry needed */
      }
   }
   if (retry == TX_MAX_RETRY)
   {
      LOGE("SPCOM_TX_GLINK_TX_MAX_RETRY status = %d.ret = %d \r\n", status, ret);
      spcom_check_if_spss_crashed();
      return EFI_TIMEOUT;
   }

   /* Wait for Tx Completion */
   timeleft = spcom_os_wait_for_event_with_timeout (&ch->tx_done, timeout_msec);
   
   if (timeleft == 0)
   {
	  spcom_check_if_spss_crashed();
      return EFI_TIMEOUT;
   }
   else if (ch->tx_abort)
   {
      return EFI_ABORTED;
   }
   
   ch->tx_done_counter++;
   return status;
}

EFI_STATUS
poll_on_nvm_ch (void)
{
   void *req_ptr;
   void *resp_ptr;
   size_t req_size = 0;
   size_t resp_size = 0;
   EFI_STATUS status = EFI_SUCCESS;
   struct spcom_server *server;
   struct spcom_channel *server_ch;

   for (int i = (SPCOM_MAX_NVM_SERVICES-1); i >= 0; --i)
   {
      server = &spcom_dev->nvm_servers[i];
      server_ch    = server->ch;

      if(!server_ch || strcmp (server_ch->name, nvmAppNamesList[i]) != 0)
      {
         LOGE("[%a] service is not registered, skip polling on this NVM channel\n",
               server_ch->name);
         continue;
      }

      /*
       * If the channel is server, it should be nvm channel
       * either "sp_nvm" or "sTPM_lite_nvm"
       */
      status = spcom_server_get_next_request_size (server, NVM_CHANNEL_POLL_TIMEOUT);

      if (EFI_ERROR (status) || server->next_request_size <= 0)
      {
         LOGI("spcom_server_get_next_request_size status "
               "%d size = %d\n", status, server->next_request_size);
         continue;
      }

      status = spcom_server_wait_for_request (server, &req_ptr,
                                              &req_size);

      if (EFI_ERROR (status))
      {
         LOGE("spcom_server_wait_for_request status %d \n", status);
         return status;
      }

      server->ch->notify_server_request_cb (server, req_ptr,
                                            req_size,
                                            (void**) &resp_ptr,
                                            &resp_size,
                                            server->server_param);

      if (!resp_ptr || !resp_size)
      {
         LOGE("Invalid parameter.\n");
         return EFI_INVALID_PARAMETER;
      }

      status = spcom_server_send_response (server, resp_ptr,
                                           resp_size);
      if (EFI_ERROR (status))
      {
         LOGE("spcom_server_send_response status %d \n", status);
         return status;
      }

   }
   return status;
}


/**
 * spcom_rx() - Wait for received data until timeout, unless pending rx data is
 * already ready
 *
 * @ch: channel state struct pointer
 * @buf: buffer pointer
 * @size: buffer size
 *
 * ACK is expected within a very short time (few msec).
 */
static int
spcom_rx (struct spcom_channel *ch, void *buf, size_t size, size_t timeout_msec)
{
   EFI_STATUS status = EFI_SUCCESS;
   int ret = 0;
   long timeleft = 1;

   /* check for already pending data */
   if (ch->actual_rx_size)
   {
	  LOGI("already pending data size [%d].\n", ch->actual_rx_size);
      /* reset the event for next time */
      spcom_os_reset_event (&ch->rx_done);
      goto copy_buf;
   }

   /*
    * Check if rx is for "stpm_lite", if yes
    * poll on nvm channnel's too in round
    * robin fashion, to service nvm command from
    * sTPM_Lite SPU Application
    */

   /* Wait for Rx response */
   LOGI("Wait for Rx done, timeout_msec [%d].\n", timeout_msec);
   if (timeout_msec)
    timeleft = spcom_os_wait_for_event_with_timeout (&ch->rx_done,
                                                    timeout_msec);
   else
    timeleft = spcom_os_wait_for_event (&ch->rx_done);

   spcom_os_reset_event (&ch->rx_done);
   if (ch->rx_abort)
   {
    LOGE("SPCOM_RX_RX_ABT\n");
    return -1;
   }
   else if (ch->actual_rx_size > 0)
   {
    LOGI("actual_rx_size is [%d].\n", ch->actual_rx_size);
   }
   else
   {
    LOGE("SPCOM_RX_RX_SZ_ZERO, timeleft %d\n", timeleft);
    return -1; //E_NO_DATA;
   }

   copy_buf:

   if (!ch->glink_rx_buf)
   {
      LOGE("SPCOM_RX_GLINK_RX_BUF_INVAL\n");
      return -1;
   }

   /* Copy from glink buffer to spcom buffer */
   size = MIN (ch->actual_rx_size, size);
   memscpy (buf, size, ch->glink_rx_buf, size);

   /* free glink buffer after copy to spcom buffer */
   status = glink_protocol->GlinkRxDone (ch->glink_handle, ch->glink_rx_buf,
   false,
                                         &ret);

   if (EFI_ERROR (status) || (GLINK_STATUS_SUCCESS != ret))
   {
	  LOGE("spcom_rx:: GlinkRxDone failure status = %x, glink_ret = %d.  \r\n", status, ret);
      status = EFI_DEVICE_ERROR;
   }

   ch->glink_rx_buf = NULL;
   ch->actual_rx_size = 0;
   ch->rx_done_counter++;

   /* queue rx buffer for the next time */
   status = glink_protocol->GlinkQueueRxIntent (ch->glink_handle, ch,
                                                ch->rx_buf_size, &ret);
   if (EFI_ERROR (status) || (GLINK_STATUS_SUCCESS != ret))
   {
      LOGE("spcom_rx:: GlinkQueueRxIntent failure status = %x, glink_ret = %d.  \r\n", status, ret);
      return -1;
   }
   else
   {
      LOGI("queue rx_buf_size[%d], size[%d].\n", ch->rx_buf_size, size);
   }

   return size;
}

/*======================================================================*/
/*             SERVER API                                               */
/*======================================================================*/

/**
 * spcom_get_next_request_size() - get request size.
 * already ready
 *
 * @ch: channel state struct pointer
 *
 * Server needs the size of the next request to allocate a request buffer.
 * Initially used intent-request, however this complicated the remote side,
 * so both sides are not using glink_tx() with INTENT_REQ anymore.
 */
EFI_STATUS
spcom_get_next_request_size (struct spcom_channel *ch, size_t *rx_size, size_t timeout_msec)
{
   EFI_STATUS status = EFI_SUCCESS;
   int timeleft;
   *rx_size = -1;

   /* check if already got it via callback */
   if (ch->actual_rx_size)
   {
	  LOGI("next-req-size already ready ch [%a] size [%d].\n", ch->name, ch->actual_rx_size);
      goto exit_ready;
   }

   LOGI("Wait for Rx Done, ch [%a].\n", ch->name);
   if (timeout_msec)
      timeleft = spcom_os_wait_for_event_with_timeout (&ch->rx_done,
                                                       timeout_msec);
   else
      timeleft = spcom_os_wait_for_event (&ch->rx_done);

   /* NOTE: Remote clients might not be connected yet.*/
   spcom_os_reset_event (&ch->rx_done);

   if (ch->rx_abort)
   {
      LOGE("rx aborted.\n");
      return EFI_ABORTED;
   }
   else if (ch->actual_rx_size > 0)
   {
      LOGI("actual_rx_size is [%d].\n", ch->actual_rx_size);
   }
   else
   {
      LOGI("actual_rx_size is zero. timeleft [%d]\n", timeleft);
      return EFI_NO_RESPONSE;
   }

   exit_ready:
      *rx_size = (size_t) ch->actual_rx_size;
   if (*rx_size > sizeof(struct spcom_msg_hdr))
   {
      *rx_size -= sizeof(struct spcom_msg_hdr);
   }
   else
   {
      LOGE("rx size [%d] too small.\n", *rx_size);
      return EFI_BUFFER_TOO_SMALL;
   }

   return status;
}

/**
  spcom_read_sp_registers ()

  @brief
  Reads a SP shared register
 */
static UINT32 spcom_read_sp_registers(UINT32 addr)
{
  UINT32 val = SP_SCSR_REGISTER_ACCESS_ERROR;

  if (gpSPRegister != NULL)
  {
    addr = ((addr - SP_CNOC_SP_SCSR_BASE_ADDR) + (UINT32) gpSPRegister);
    val = in_dword(addr);
  }

  return val;
}
/**
  spcom_map_sp_registers ()

  @brief
  Initializes HWIOProtocol variable and maps SP region
 */
static EFI_STATUS spcom_map_sp_registers(VOID)
{
  EFI_STATUS         status = 0;
  EFI_HWIO_PROTOCOL *pHWIOProtocol = NULL;

  status = gBS->LocateProtocol(&gEfiHwioProtocolGuid, NULL, (void**)&pHWIOProtocol);
  if ((EFI_ERROR(status)) || (pHWIOProtocol == NULL))
  {
	LOGE("%a failed to get HWIO protocol, status [0x%x] \r\n", __FUNCTION__, status );
    return EFI_DEVICE_ERROR;
  }

  /* Map SP shared registers */
  status = pHWIOProtocol->MapRegionByAddress(pHWIOProtocol,
                                             (UINT8*) SP_CNOC_SP_SCSR_BASE_ADDR,
                                             (UINT8**) &gpSPRegister);
  if ((status != EFI_SUCCESS) || (gpSPRegister == NULL))
  {
	LOGE("%a MapRegionByAddress() failed = %r \r\n", __FUNCTION__, status );
    return EFI_DEVICE_ERROR;
  }

  return status;
}

/*======================================================================*/
/*             is SP up ?                           */
/*======================================================================*/

boolean
spcom_is_sp_subsystem_link_up (void)
{
   if (!spcom_link_up_registered)
   {
      if (EFI_ERROR (spcom_register_link_up_notification())){
         LOGE("spcom_register_link_up_notification failed\n");
         return false;
      }
      spcom_link_up_registered = true;
   }
   return spcom_is_link_up ();
}
/*
**************************************************** 
         SPSS_REGION: 0x85700000 to 0x85995000
****************************************************
Usecase                             Size  Start Addr
****************************************************
SPU Firmware plus boot apps          896  0x85700000
sTPM-Lite Image                      512  0x857E0000
sTPM-Full Image                     1024  0x85860000
sTPM-Lite NVM Data                    36  0x85960000
SegDB                                 36  0x85969000
UEFI-SPU SPCOM  - sTPM_lite channel    8  0x85972000
Echoapp                               48  0x85989000
Reserved                            1280  0x85995000
****************************************************

Reserved DDR region could be requested either for,
1. Loading a SPU APP
2. Communicating with a SPU APP for payload larger than 268

is_app_load flag will help determine the usecase for which
memory is requested for.
‬
*/


EFI_STATUS
spcom_get_reserved_pil_region (const char *ch_name, void **buf, size_t size,
                               boolean is_app_load)
{

   for (int i = 0; i < (sizeof(sp_apps_info) / sizeof(sp_apps_info[0])); i++)
   {
      if (strcmp (ch_name, sp_apps_info[i].ch_name) == 0)
      {
         if (is_app_load)
         {
            if (!sp_apps_info[i].app_load_ddr_offset
                  || size > sp_apps_info[i].app_load_size)
            {
               return EFI_UNSUPPORTED;
            }
            *buf = (void *)sp_apps_info[i].app_load_ddr_offset;
            return EFI_SUCCESS;
         }
         else
         {
            if (!sp_apps_info[i].cmd_buf_ddr_offset
                  || size > sp_apps_info[i].cmd_buf_size)
            {
               return EFI_UNSUPPORTED;
            }
            *buf = (void *)sp_apps_info[i].cmd_buf_ddr_offset;
            return EFI_SUCCESS;
         }
      }
   }
   return EFI_NOT_FOUND;
}

EFI_STATUS
spcom_clear_reserved_pil_region (const char *ch_name, void *buf, size_t size,
                               boolean is_app_load)
{
   for (int i = 0; i < (sizeof(sp_apps_info) / sizeof(sp_apps_info[0])); i++)
   {
      if (strcmp (ch_name, sp_apps_info[i].ch_name) == 0)
      {
         if (is_app_load)
         {
            if (!sp_apps_info[i].app_load_ddr_offset
                  || size > sp_apps_info[i].app_load_size)
            {
               return EFI_UNSUPPORTED;
            }
            memset (buf, 0, size);
            return EFI_SUCCESS;
         }
         else
         {
            if (!sp_apps_info[i].cmd_buf_ddr_offset
                  || size > sp_apps_info[i].cmd_buf_size)
            {
               return EFI_UNSUPPORTED;
            }
            memset (buf, 0, size);
            return EFI_SUCCESS;

         }
      }
   }
   return EFI_NOT_FOUND;
}

/* Ideally we should not find more than 1 handle */
HandleInfo HandleInfoList[4];
UINT32 MaxHandles;
PartiSelectFilter HandleFilter;

EFI_STATUS
spcom_load_app (const char *ch_name, EFI_GUID *appGuid, size_t image_size, size_t swap_size, size_t *load_resp_code)
{
   UINT32 Attribs = 0;
   EFI_STATUS Status = EFI_SUCCESS;
   UINT32 *MemLoc = NULL;
   EFI_BLOCK_IO_PROTOCOL *BlkIo = NULL;
   UINTN ImgSize = 0;
   
   /* Select the BlkIo handle that represents the partition by the
    * referenced GUID type in GPT partition on Non removable media
    * ie eMMC device */
   Attribs |= BLK_IO_SEL_MEDIA_TYPE_NON_REMOVABLE;
   Attribs |= BLK_IO_SEL_PARTITIONED_GPT;
   Attribs |= BLK_IO_SEL_STRING_CASE_INSENSITIVE;
   Attribs |= BLK_IO_SEL_MATCH_PARTITION_TYPE_GUID;

   if (!appGuid){
      LOGE("Invalid GUID\n");
      return EFI_INVALID_PARAMETER;
   }

   HandleFilter.PartitionType = appGuid;

   MaxHandles = sizeof(HandleInfoList) / sizeof(*HandleInfoList);
   HandleFilter.VolumeName = 0;

   Status = GetBlkIOHandles (Attribs, &HandleFilter, HandleInfoList,
                             &MaxHandles);
   if (Status != EFI_SUCCESS)
   {
      LOGE("GetBlkIOHandles failed Status: %d\n", Status);
      return Status;
   }

   /* Having more than one partition is considered ambiguity, so return
    * invalid param */
   if (MaxHandles > 1)
   {
      LOGE("Invalid MaxHandles = %d\n",MaxHandles);
      return EFI_INVALID_PARAMETER;
   }

   if (MaxHandles == 0)
   {
      LOGE("Image partition label not found\n");
      return EFI_NOT_FOUND;
   }

   /* Get the Block IO protocol instance from the handle */
   BlkIo = HandleInfoList[0].BlkIo;

   /* Get the partition size and round it up to EFI_PAGE_SIZE
    * LBA numbers are 0-based, so total blocks = LastBlock + 1 */
   ImgSize = (BlkIo->Media->LastBlock + 1) * BlkIo->Media->BlockSize;

   if(image_size > ImgSize){
      LOGE("Invalid Image size = %d, for partition size = %d\n",image_size,ImgSize);
      return EFI_INVALID_PARAMETER;
   }

   MemLoc = spcom_os_malloc (ImgSize);
   if (MemLoc == NULL)
   {
      LOGE("spcom_load_app, malloc failed\n");
      Status = EFI_OUT_OF_RESOURCES;
      goto ErrorExit;
   }

   Status = BlkIo->ReadBlocks (BlkIo, BlkIo->Media->MediaId, 0, ImgSize,
                               MemLoc);
   if (EFI_ERROR(Status)){
      LOGE("ReadBlocks failed Status: %d\n", Status);
      goto ErrorExit;
   }

   Status = spcom_load_app_from_buffer (ch_name, MemLoc, image_size,
                                        swap_size, load_resp_code);

   ErrorExit:
   if (MemLoc)
   {
      spcom_os_free (MemLoc);
   }
   return Status;
}

EFI_STATUS
spcom_connect_skp_service_client (struct spcom_client** client)
{
   EFI_STATUS status = EFI_SUCCESS;
   struct spcom_client_info reg_info = {};
   bool is_connected = false;
   uint32_t timeout_msec = TX_DONE_TIMEOUT_MSEC;   //1000 ms

   // Client pointer to pointer is NULL or
   // client already initialized
   if (!client || (*client))
   {
      LOGE("Bad client parameter.\n");
      return EFI_INVALID_PARAMETER;
   }

   //Reuse already connected service client
   if (!skp_active_service_client_counter)
   {
      skp_service_client = NULL;
      reg_info.ch_name =  skp_ch_name;
      status = spcom_register_client (&reg_info, &skp_service_client);
      if(EFI_ERROR(status)){
         LOGE("spcom register returned %d.\n", status);
         return status;
      }

      if (!skp_service_client)
      {
         LOGE("spcom register failed.\n");
         return EFI_DEVICE_ERROR;
      }


      // wait for remote SP App to connect
      while (!is_connected)
      {
         is_connected = spcom_client_is_server_connected (skp_service_client);
         spcom_os_msleep (10);
         timeout_msec -= 10;
         if (timeout_msec == 0)
         {
            spcom_unregister_client (&skp_service_client);
            skp_service_client = NULL;
            LOGE("Timeout wait for ch CONNECT.\n");
            spcom_check_if_spss_crashed();
            return EFI_TIMEOUT;
         }
      }
   }

   *client = skp_service_client;
   if (!skp_active_service_client_counter)
      skp_active_service_client_counter++;

   return status;
}

EFI_STATUS spcom_load_app_from_buffer(const char *ch_name,
        void *image_buf, size_t image_size, size_t swap_size, size_t *load_resp_code)
{
    struct spcom_client* skp_service_client = NULL;
    struct spcom_load_app_req *req = NULL;
    struct spcom_load_app_resp *resp = NULL;
    void *app_buf;
    int app_buf_size = 0;
    size_t rx_size = 0;
    EFI_STATUS ret = 0;
    int timeout_msec = 0;

    if (ch_name == NULL || image_buf == NULL
            || image_size == 0 ) {
        LOGE("invalid parameters.\n");
        return EFI_INVALID_PARAMETER;
    }

    if (strnlen(ch_name, SPCOM_CHANNEL_NAME_SIZE) > (SPCOM_CHANNEL_NAME_SIZE - 1)) {
        LOGE("ch_name [%a] too long.\n", ch_name);
        return EFI_INVALID_PARAMETER;
    }

    if (image_size > MAX_APP_SIZE) {
        LOGE("image_size [%zu] > %d KB.\n", image_size, MAX_APP_SIZE);
        return EFI_INVALID_PARAMETER;
    }

    if(load_resp_code == NULL)
    {
        LOGE("Load App load_resp_code is NULL\n");
        return EFI_INVALID_PARAMETER;
    }

    ret = spcom_is_app_loaded (ch_name);
    if (ret != EFI_NOT_FOUND) {
        if (ret == EFI_SUCCESS){
           LOGE("%a App is already loaded\n", ch_name);
           ret = EFI_LOAD_ERROR;
        }else{
           LOGE("spcom_is_app_loaded ret %d\n", ret);
        }
        goto exit_err;
    }

    req = spcom_os_malloc(sizeof(*req));
    if (!req) {
        LOGE("malloc failure.\n");
        return EFI_INVALID_PARAMETER;
    }
    resp = spcom_os_malloc(sizeof(*resp));
    if (!resp) {
        LOGE("malloc failure.\n");
        ret = EFI_INVALID_PARAMETER;
        goto exit_err;
    }
    app_buf_size = swap_size;//SWAP_APP_SIZE;
    ret = spcom_get_reserved_pil_region(ch_name, &app_buf, image_size, true);

    if (EFI_ERROR(ret)) {
        LOGE("spcom_get_reserved_pil_region failed.\n");
        ret = EFI_OUT_OF_RESOURCES;
        goto exit_err;
    } else {
        LOGI("spcom_get_reserved_pil_region ok.\n");
        memset(app_buf, 0, image_size); /* reset the buffer */
    }

    memscpy(app_buf, image_size, image_buf, image_size);

    /* Prepare Request */
    req->cmd_id = SPCOM_CMD_LOAD_APP;
    req->image_size = image_size;
    req->full_ddr_swap_size = app_buf_size;
    req->buf_phys_addr = (uint64_t)app_buf;
    strlcpy(req->ch_name, ch_name, sizeof(req->ch_name));


    ret = spcom_connect_skp_service_client (&skp_service_client);

    if (EFI_ERROR (ret)){
        LOGE("spcom_register_client() for skp failed. %d \n", ret);
        ret = EFI_DEVICE_ERROR;
        goto exit_err;
    }

    /* Send the request to SKP */
    timeout_msec = 15000;
    ret = spcom_client_send_message_sync(skp_service_client,
                                      req, sizeof(*req),
                                      resp, sizeof(*resp),
                                      &rx_size,
                                      timeout_msec);

    LOGI("Load App [%a] ret [%d]\n", ch_name, ret);

    *load_resp_code =  resp->error_code;

    if (EFI_ERROR(ret)) {
        LOGE("Load App [%a] failed, ret [%d] \n", ch_name, ret);
        goto exit_err;
    }

    /* Check the response */
    if (resp->error_code == 0) {
        LOGE("Load App [%a] completed ok.\n", ch_name);
    } else {
        LOGE("Load App [%a] failed. Resp code [%d].\n", ch_name, resp->error_code);
        goto exit_err;
    }

    spcom_os_free(req);
    spcom_os_free(resp);

    req = NULL;
    resp = NULL;

exit_err:
    if (req != NULL)
       spcom_os_free(req);
    if (resp != NULL)
       spcom_os_free(resp);

   return ret;
}

/*======================================================================*/
/*             Client API for kernel drivers                           */
/*======================================================================*/

/**
 * spcom_register_client() - register a client.
 *
 * @info: channel name and ssr callback.
 *
 * Return: client handle
 */
EFI_STATUS
spcom_register_client (struct spcom_client_info *info,
                       struct spcom_client **client_ptr)
{
   EFI_STATUS ret = EFI_SUCCESS;
   const char *name = NULL;
   struct spcom_channel *ch = NULL;
   struct spcom_client *client = NULL;

   if (spcom_dev == NULL)
   {
      LOGE("SPCOM_REG_CLIENT_DEV_NULL\n");
      return EFI_DEVICE_ERROR;
   }

   if (!spcom_link_up_registered)
   {
      spcom_register_link_up_notification ();
      spcom_link_up_registered = true;
   }

   if (!spcom_is_link_up ())
   {
      LOGE("SPCOM_REG_CLIENT_LINK_DOWN\n");
      return EFI_DEVICE_ERROR;
   }

   if (!info)
   {
      LOGE("SPCOM_REG_CLIENT_INFO_INVAL\n");
      return EFI_INVALID_PARAMETER;
   }

   if (!client_ptr)
   {
      LOGE("SPCOM_REG_CLIENT_CLIENT_INVAL\n");
      return EFI_INVALID_PARAMETER;
   }

   if (info->ch_name == NULL)
   {
      LOGE("SPCOM_REG_CLIENT_NULL_CHNAME\n");
      return EFI_INVALID_PARAMETER;
   }

   if (info->ch_name[0] == 0)
   {
      LOGE("SPCOM_REG_CLIENT_EMPTY_CHNAME\n");
      return EFI_INVALID_PARAMETER;
   }

   name = info->ch_name;
   *client_ptr = NULL;

   if (strnlen (name, sizeof(ch->name)) >= sizeof(ch->name))
   { // Need NULL termination space.
      LOGE("SPCOM_REG_CLIENT_NAME_TOO_LONG\n");
      spcom_os_assert (false);
      return EFI_INVALID_PARAMETER;
   }

   client = spcom_os_malloc (sizeof(*client));
   if (!client)
      return EFI_OUT_OF_RESOURCES;

   ch = spcom_find_channel_by_name (name);
   if (!ch)
   {
	  LOGI("channel [%a] doesn't exist , allocate a channel\n", name);
      ch = spcom_find_channel_by_name (""); /* find unused channel */
      if (!ch)
      {
         LOGE("SPCOM_REG_CLIENT_NO_FREE_CHANNEL\n");
         spcom_os_free (client);
         return EFI_DEVICE_ERROR;
      }
      spcom_init_channel (ch, name);
   }

   client->ch = ch; /* backtrack */

   ret = spcom_open (ch, OPEN_CHANNEL_TIMEOUT_MSEC);
   if (EFI_ERROR (ret))
   {
      LOGE("SPCOM_REG_CLIENT_OPEN_FAIL\n");
      spcom_os_free (client);
      return ret;
   }
   else
   {
      LOGI("channel [%a] is open.\n", name);
   }

   ch->magic = SPCOM_MAGIC_ID;

   *client_ptr = client;

   return EFI_SUCCESS;
}

/**
 * spcom_unregister_client() - unregister a client.
 *
 * @client: client handle
 */
EFI_STATUS
spcom_unregister_client (struct spcom_client **client_ptr)
{
   EFI_STATUS ret = EFI_SUCCESS;
   struct spcom_channel *ch = NULL;
   struct spcom_client *client = *client_ptr;

   LOGI("spcom_unregister_client\n");
   if (spcom_dev == NULL)
   {
      LOGE("SPCOM_UNREG_NULL_DEV\n");
      return EFI_DEVICE_ERROR;
   }

   if (!client)
   {
      LOGE("SPCOM_UNREG_NULL_CLIENT\n");
      return EFI_INVALID_PARAMETER;
   }

   if (!client->ch)
   {
      LOGE("SPCOM_UNREG_NULL_CHANNEL\n");
      return EFI_INVALID_PARAMETER;
   }
   ch = client->ch;

   if (!spcom_is_channel_open (ch))
   {
      LOGE("Channel already closed, probably after SSR.\n");
      /* NOTE: spcom_close() and spcom_exit_channel() already called. */
      memset (*client_ptr, 0, sizeof(**client_ptr));
      spcom_os_free (*client_ptr);
      *client_ptr = NULL;
      return EFI_SUCCESS;
   }

   if (client->ch->magic != SPCOM_MAGIC_ID)
   {
      LOGE("SPCOM_UNREG_HANDLE_INVAL\n");
      return EFI_INVALID_PARAMETER;
   }

   if (!spcom_is_link_up ())
   {
      LOGE("SPCOM_UNREG_LINK_DOWN\n");
   }

   if (spcom_is_channel_open (ch))
   {
      long timeleft = 0;

      spcom_os_reset_event (&ch->disconnect);

      ret = spcom_close (ch);

      if (EFI_ERROR (ret))
      {
         LOGE("SPCOM_UNREG_CLIENT_CLOSE_FAIL\n");
         return ret;
      }

      LOGI("Wait for event GLINK_LOCAL_DISCONNECTED, ch [%a].\n", ch->name);
      timeleft = spcom_os_wait_for_event_with_timeout (&ch->disconnect, 3000);

      if (timeleft == 0)
      {
         LOGE("SPCOM_UNREG_DISCON_NOT_SIGN\n");
         spcom_check_if_spss_crashed();
         ret = EFI_TIMEOUT;
      }
      else
      {
         LOGI("GLINK_LOCAL_DISCONNECTED event signaled, ch [%a].\n", ch->name);
      }
   }
   else
   {
      LOGE("SPCOM_UNREG_ALREADY_CLOSED\n");
   }

   spcom_exit_channel (ch); /* reset channel context */

   memset (*client_ptr, 0, sizeof(**client_ptr));
   spcom_os_free (*client_ptr);
   *client_ptr = NULL;

   return EFI_SUCCESS;
}

/**
 * spcom_client_send() - Send request
 *
 * @client:    a pointer to spcom client
 * @req_ptr:   a pointer to the request C struct representation
 * @req_size:  size of the request C struct
 *
 * return: 0 on success, negative error code on failure (see errno.h)
 */
static EFI_STATUS
spcom_client_send (struct spcom_client *client, void *req_ptr, size_t req_size)
{
   EFI_STATUS ret = EFI_SUCCESS;
   struct spcom_channel *ch = NULL;
   struct spcom_msg_hdr *hdr = NULL;
   void *tx_buf = NULL;
   int tx_buf_size = 0;

   if (!client || !req_ptr || !client->ch)
   {
      LOGE("SPCOM_CLIENT_SEND_NULL_PARAM\n");
      return EFI_INVALID_PARAMETER;
   }

   if (client->ch->magic != SPCOM_MAGIC_ID)
   {
      LOGE("SPCOM_CLIENT_SEND_HANDLE_INVAL\n");
      return EFI_INVALID_PARAMETER;
   }

   if (req_size > SPCOM_MAX_REQUEST_SIZE)
   {
	  LOGE("SPCOM_CLIENT_SEND_REQ_SZ_MAX, req_size , SPCOM_MAX_REQUEST_SIZE\n");
      return EFI_INVALID_PARAMETER;
   }
   if (req_size == 0)
   {
      LOGE("SPCOM_CLIENT_SEND_REQ_SZ_ZERO\n");
      return EFI_INVALID_PARAMETER;
   }

   ch = client->ch;

   /* Check if remote side connect */
   if (!spcom_is_channel_connected (ch))
   {
      LOGE("SPCOM_CLIENT_SEND_NOT_CONNECTED\n");
      return EFI_DEVICE_ERROR;
   }

   /* Allocate Buffers*/
   tx_buf_size = sizeof(*hdr) + req_size;
   tx_buf = spcom_os_malloc (tx_buf_size);
   if (tx_buf == NULL)
      return EFI_OUT_OF_RESOURCES;

   /* Prepare Tx Buf */
   hdr = tx_buf;

   /* Header */
   hdr->txn_id = ch->txn_id;
   ch->txn_id++; /* client sets the request txn_id */

   /* copy user buf */
   memscpy (hdr->buf, req_size, req_ptr, req_size);

   /*
    * remote side should have rx buffer ready.
    * tx_done is expected to be received quickly.
    */
   ret = spcom_tx (ch, tx_buf, tx_buf_size, TX_DONE_TIMEOUT_MSEC);
   if (EFI_ERROR (ret))
      LOGE("SPCOM_CLIENT_SEND_TX_FAIL %d\n", ret);
   spcom_os_free (tx_buf);

   return ret;
}

/**
 * spcom_client_receive() - Receive Response
 *
 * @client:    a pointer to spcom client
 * @resp_ptr:  a pointer to the response C struct representation
 * @resp_size:  size of the response C struct
 * @timeout_msec: Timeout in msec between command and response, 0=no timeout.
 *
 * return: 0 on success, negative error code on failure (see errno.h)
 */
static EFI_STATUS
spcom_client_receive (struct spcom_client *client, void *resp_ptr,
                      size_t resp_size, size_t *rx_size, size_t timeout_msec)
{
   EFI_STATUS ret = EFI_SUCCESS;
   struct spcom_channel *ch = NULL;
   struct spcom_msg_hdr *hdr = NULL;
   void *rx_buf = NULL;
   int rx_buf_size = 0;
   int size = 0;

   if (!client || !resp_ptr || !client->ch)
   {
      LOGE("SPCOM_CLIENT_RCV_NULL_PARAM\n");
      return EFI_INVALID_PARAMETER;
   }

   if (client->ch->magic != SPCOM_MAGIC_ID)
   {
      LOGE("SPCOM_CLIENT_RCV_HANDLE_INVAL\n");
      return EFI_INVALID_PARAMETER;
   }

   if (resp_size == 0)
   {
      LOGE("SPCOM_CLIENT_RCV_REQ_SZ_ZERO\n");
      return EFI_INVALID_PARAMETER;
   }

   if (resp_size > SPCOM_MAX_RESPONSE_SIZE)
   {
	  LOGE("SPCOM_CLIENT_RCV_RESP_SZ_MAX, resp_size, SPCOM_MAX_RESPONSE_SIZE\n");
      return EFI_INVALID_PARAMETER;
   }

   ch = client->ch;

   /* Allocate Buffers*/
   rx_buf_size = sizeof(*hdr) + resp_size;
   rx_buf = spcom_os_malloc (rx_buf_size);
   if (rx_buf == NULL)
      return EFI_OUT_OF_RESOURCES;

   ret = spcom_rx (ch, rx_buf, rx_buf_size, timeout_msec);
   
   if (EFI_ERROR (ret))
   {
      spcom_os_free (rx_buf);
      LOGE("spcom_rx ret err %d\n", ret);
      spcom_check_if_spss_crashed();
      return ret;
   }
   else
   {
      size = ret; /* actual_rx_size */
      size -= sizeof(*hdr); /* reduce header size */
   }

   hdr = rx_buf;

   /* Copy response without header */
   memscpy (resp_ptr, size, hdr->buf, size);

   /* free the rx buffer with the header */
   spcom_os_free (rx_buf);

   *rx_size = size;

   return EFI_SUCCESS;
}

/**
 * spcom_client_send_message_sync() - Send a synchronous request and response.
 *
 * @client:    a pointer to spcom client
 * @req_ptr:   a pointer to the request C struct representation
 * @req_size:  size of the request C struct
 * @resp_ptr:  a pointer to the response C struct representation
 * @resp_size:  size of the response C struct
 * @timeout_msec: Timeout in msec between command and response, 0=no timeout.
 *
 * return: 0 on success, negative error code on failure (see errno.h)
 */
EFI_STATUS
spcom_client_send_message_sync (struct spcom_client *client, void *req_ptr,
                                size_t req_size, void *resp_ptr,
                                size_t resp_size, size_t *rx_size,
                                   size_t            timeout_msec)
{
   EFI_STATUS ret = EFI_SUCCESS;
   //int resp = 0;
   //int     use_listener = 0;
   //boolean is_blown = false;
   *rx_size = 0;
   if (spcom_dev == NULL)
   {
      LOGE("SPCOM_CLIENT_SEND_SYNC_NULL_DEV\n");
      return EFI_DEVICE_ERROR;
   }

   if (!spcom_is_link_up ())
   {
      LOGE("SPCOM_CLIENT_SEND_SYNC_LINK_DOWN\n");
      return EFI_DEVICE_ERROR;
   }

   if (!client || !req_ptr || !resp_ptr || !client->ch)
   {
      LOGE("SPCOM_CLIENT_SEND_SYNC_NULL_PARAM\n");
      return EFI_INVALID_PARAMETER;
   }

   if (client->ch->magic != SPCOM_MAGIC_ID)
   {
      LOGE("SPCOM_CLIENT_SEND_SYNC_HANDLE_INVAL\n");
      return EFI_DEVICE_ERROR;
   }

   /* Verify that the channel is connected, to protect after SSR. */
   if (!spcom_client_is_server_connected (client))
   {
      LOGE("SPCOM_CLIENT_SEND_SYNC_NOT_CONNECTED\n");
      return EFI_DEVICE_ERROR;
   }

   /* send message to SPU */
   ret = spcom_client_send (client, req_ptr, req_size);

   if (EFI_ERROR (ret))
   {
      return ret;
   }

   ret = spcom_client_receive (client, resp_ptr, resp_size, rx_size,
                               timeout_msec);

   return ret;
}

/**
 * spcom_client_is_server_connected() - is remote server connected.
 *
 * @client: client handle
 */
boolean
spcom_client_is_server_connected (struct spcom_client *client)
{
   boolean connected = false;

   if (spcom_dev == NULL)
   {
      LOGE("SPCOM_CLIENT_SRV_CONNECTED_NULL_DEV\n");
      return false;
   }

   if (!client)
   {
      LOGE("SPCOM_CLIENT_SRV_CONNECTED_NULL_PARAM\n");
      return false;
   }

   if (!spcom_is_link_up ())
   {
      LOGE("SPCOM_CLIENT_SRV_CONNECTED_LINK_DOWN\n");
      return false;
   }

   if (!spcom_is_channel_open (client->ch))
   {
      LOGE("SPCOM_CLIENT_SRV_CONNECTED_CLOSED\n");
      return false;
   }

   connected = spcom_is_channel_connected (client->ch);

   return connected;
}

EFI_STATUS
spcom_connect_service_client (struct spcom_client** client)
{
   EFI_STATUS status = EFI_SUCCESS;
   struct spcom_client_info reg_info = {};
   bool is_connected = false;
   uint32_t timeout_msec = TX_DONE_TIMEOUT_MSEC;   //1000 ms

   // Client pointer to pointer is NULL or
   // client already initialized
   if (!client || (*client))
   {
      LOGE("Bad client parameter.\n");
      return EFI_INVALID_PARAMETER;
   }

   //Reuse already connected service client
   if (!g_active_service_client_counter)
   {
      g_service_client = NULL;
      reg_info.ch_name = "cryptoapp";
      status = spcom_register_client (&reg_info, &g_service_client);
      if(EFI_ERROR(status)){
         LOGE("spcom register returned %d.\n", status);
         return status;
      }

      if (!g_service_client)
      {
         LOGE("spcom register failed.\n");
         return EFI_DEVICE_ERROR;
      }


      // wait for remote SP App to connect
      while (!is_connected)
      {
         is_connected = spcom_client_is_server_connected (g_service_client);
         spcom_os_msleep (10);
         timeout_msec -= 10;
         if (timeout_msec == 0)
         {
            spcom_unregister_client (&g_service_client);
            g_service_client = NULL;
            LOGE("Timeout wait for ch CONNECT.\n");
            spcom_check_if_spss_crashed();
            return EFI_TIMEOUT;
         }
      }
   }

   *client = g_service_client;
   if (!g_active_service_client_counter)
      g_active_service_client_counter++;

   return status;
}

EFI_STATUS spcom_is_app_loaded (const char *ch_name)
{
   EFI_STATUS status = EFI_SUCCESS;
   size_t rx_size = 0;

   struct spcom_client* service_client = NULL;

   status = spcom_connect_service_client (&service_client);

   // Error when sending the message
   if (EFI_ERROR (status))
   {
	  LOGE("client SP_CMD_ID_SYSPARAM_READ send failed (%d).\n", status);
      return status;
   }

   sp_sysparam_read_request_t req = {};
   sp_sysparam_read_response_t rsp = {};

   // Send command to SP side
   req.cmd_opcode = SP_CMD_ID_SYSPARAM_READ;
   req.sysparam_id = SP_SYSPARAM_ID_APP_BUILD_VERSION;
   req.sysparam_arg1 = 0;
   req.sysparam_arg2 = 0;
   for (int i = 0; i < (sizeof(sp_apps_info) / sizeof(sp_apps_info[0])); i++)
   {
      if (strcmp (ch_name, sp_apps_info[i].ch_name) == 0)
      {
         req.sysparam_arg1 = sp_apps_info[i].id;
         break;
      }
   }
   if (req.sysparam_arg1 == 0)
   {
      return EFI_INVALID_PARAMETER;
   }

   // Send command to SP side
   status = spcom_client_send_message_sync (service_client, &req, sizeof(req),
                                            &rsp, sizeof(rsp), &rx_size,
                                            TX_DONE_TIMEOUT_MSEC);

   // Error when sending the message
   if (EFI_ERROR (status))
   {
	   LOGE("client SP_CMD_ID_SYSPARAM_READ send failed (%d).\n", status);
   }
   else
   {
      if (rsp.error_code == 0)
      {
    	  LOGI("Build Version of %a, v%d.%d\n", ch_name,
                     ((uint32_t) -1 == rsp.sysparam_value) ?
                           0 : (rsp.sysparam_value >> 16),
                     ((uint32_t) -1 == rsp.sysparam_value) ?
                           0 : (rsp.sysparam_value & 0xFFFF));
      }
      else
      {
    	 LOGE("SP SP_CMD_ID_SYSPARAM_READ response error [%d]\n", rsp.error_code);
         status = EFI_NOT_FOUND;

      }
   }

   return status;
}

int
spcom_reset_sp_subsystem (void)
{
   return 0;
}

/*======================================================================*/
/*    Server API for kernel drivers          */
/*======================================================================*/

/**
 * store_nvm_server_info() - store the server info in spcom_device.
 *
 * @server: server handle
 * @ch_name: channel name and ssr callback.
 *
 */
static void
store_nvm_server_info(struct spcom_server *server ,const char *ch_name)
{
   if (strcmp (ch_name, nvmAppNamesList[0]) == 0)
   {
      spcom_dev->nvm_servers[0] = *server;
   } else if (strcmp (ch_name, nvmAppNamesList[1])== 0)
   {
      spcom_dev->nvm_servers[1] = *server;
   }
}

/**
 * clear_nvm_server_info() - clear the server info in spcom_device.
 *
 * @server: server handle
 * @ch_name: channel name and ssr callback.
 *
 */
static void
clear_nvm_server_info(const char *ch_name)
{
   if (strcmp (ch_name, nvmAppNamesList[0]) == 0)
   {
      memset (&spcom_dev->nvm_servers[0], 0, sizeof(struct spcom_server));
   } else if (strcmp (ch_name, nvmAppNamesList[1])== 0)
   {
      memset (&spcom_dev->nvm_servers[1], 0, sizeof(struct spcom_server));
   }
}

/**
 * spcom_register_service() - register a server.
 *
 * @info: channel name and ssr callback.
 *
 * Return: server handle
 */
EFI_STATUS
spcom_register_service (struct spcom_service_info *info,
                        struct spcom_server **server_ptr)
{
   EFI_STATUS ret = EFI_SUCCESS;
   const char *name;
   struct spcom_channel *ch;
   struct spcom_server *server;

   if (spcom_dev == NULL)
   {
      LOGE("spcom not ready yet.\n");
      return EFI_INVALID_PARAMETER;
   }

   if (!spcom_is_link_up ())
   {
      LOGE("LINK is DOWN.\n");
      return EFI_INVALID_PARAMETER;
   }

   if (!info)
   {
      LOGE("Invalid parameter.\n");
      return EFI_INVALID_PARAMETER;
   }

   if (!server_ptr)
   {
      LOGE("Invalid spcom register server\n");
      return EFI_INVALID_PARAMETER;
   }

   if (info->ch_name == NULL)
   {
      LOGE("Invalid NULL ch name.\n");
      return EFI_INVALID_PARAMETER;
   }

   if (info->ch_name[0] == 0)
   {
      LOGE("Invalid EMPTY ch name.\n");
      return EFI_INVALID_PARAMETER;
   }

   name = info->ch_name;
   *server_ptr = NULL;

   if (strlen (name) > sizeof(ch->name) - 1)
   {
      LOGE("name too long\n");
      return EFI_INVALID_PARAMETER;
   }

   server = spcom_os_malloc (sizeof(*server));
   if (!server)
      return EFI_OUT_OF_RESOURCES;

   ch = spcom_find_channel_by_name (name);
   if (!ch)
   {
	  LOGI("channel [%a] doesn't exist , allocate a channel\n", name);
      ch = spcom_find_channel_by_name (""); /* find unused channel */
      if (!ch)
      {
         LOGE("no free channel\n");
         return EFI_DEVICE_ERROR;
      }
      spcom_init_channel (ch, name);
   }

   server->ch = ch; /* backtrack */
   ch->is_server = true;
   ch->notify_server_request_cb = info->notify_server_request_cb;

   ret = spcom_open (ch, OPEN_CHANNEL_TIMEOUT_MSEC);
   if (EFI_ERROR (ret))
   {
      LOGE("failed to open channel [%a].\n", name);
      spcom_os_free (server);
      server = NULL;
      return EFI_DEVICE_ERROR;
   }

   ch->magic = SPCOM_MAGIC_ID;

   *server_ptr = server;
   server->server_param = info->server_param;

   /* if nvm service, then store the server info in spcom_device */
   store_nvm_server_info(server,name);

   return EFI_SUCCESS;
}

/**
 * spcom_unregister_service() - unregister a server.
 *
 * @server: server handle
 */
EFI_STATUS
spcom_unregister_service (struct spcom_server *server)
{
   struct spcom_channel *ch;

   if (!server)
   {
      LOGE("Invalid parameter.\n");
      return EFI_INVALID_PARAMETER;
   }

   if (server->ch->magic != SPCOM_MAGIC_ID)
   {
      LOGE("Invalid handle.\n");
      return EFI_INVALID_PARAMETER;
   }

   ch = server->ch;

   if (!spcom_is_link_up ())
   {
      LOGE("LINK is DOWN, but need to cleanup anyway.\n");
   }

   if (spcom_is_channel_open (ch))
   {
      long timeleft = 0;

      spcom_os_reset_event (&ch->disconnect);

      spcom_close (ch);

      LOGI("Wait for event GLINK_LOCAL_DISCONNECTED, ch [%a].\n", ch->name);
      timeleft = spcom_os_wait_for_event_with_timeout (&ch->disconnect, 3000);
      if (timeleft == 0)
      {
    	  LOGE("GLINK_LOCAL_DISCONNECTED event NOT signaled, ch [%a].\n", ch->name);
      }
      else
      {
    	  LOGI("GLINK_LOCAL_DISCONNECTED event signaled, ch [%a].\n", ch->name);
      }
      spcom_exit_channel (ch); /* reset channel context */
   }
   else
   {
      LOGE("ch [%a] already closed.\n", ch->name);
   }

   clear_nvm_server_info(ch->name);

   memset (ch, 0, sizeof(*ch));

   spcom_os_free (server);

   return EFI_SUCCESS;
}

/**
 * spcom_server_get_next_request_size() - get request size.
 *
 * @server: server handle
 *
 * Return: request size in bytes.
 */
EFI_STATUS
spcom_server_get_next_request_size (struct spcom_server *server, size_t timeout_msec)
{
   EFI_STATUS status = EFI_SUCCESS;
   size_t size;
   struct spcom_channel *ch;
   if (!server)
   {
      LOGE("Invalid server parameter.\n");
      return EFI_INVALID_PARAMETER;
   }

   if (server->ch == NULL)
   {
      LOGE("Invalid NULL ch handle.\n");
      return EFI_INVALID_PARAMETER;
   }

   if (server->ch->magic != SPCOM_MAGIC_ID)
   {
      LOGE("Invalid handle.\n");
      return EFI_INVALID_PARAMETER;
   }

   if (!spcom_is_link_up ())
   {
      LOGE("Link is down.\n");
      return false;
   }

   ch = server->ch;

   if (!ch->is_server)
   {
      LOGE("ch is not server ?.\n");
      return EFI_INVALID_PARAMETER;
   }

   if (server->next_request_size > 0)
   {
      LOGE("already got request size.\n");
      return EFI_SUCCESS;
   }

   if (!spcom_is_channel_open (ch))
   {
      LOGE("channel is not open.\n");
      return EFI_INVALID_PARAMETER;
   }

   status = spcom_get_next_request_size (ch, &size, timeout_msec);

   server->next_request_size = size;

   LOGI("next_request_size [%d].\n", size);

   return status;
}

/**
 * spcom_server_wait_for_request() - wait for request.
 *
 * @server: server handle
 * @req_ptr: request buffer pointer
 * @req_size: max request size
 *
 * Return: request size in bytes.
 */
EFI_STATUS
spcom_server_wait_for_request (struct spcom_server *server, void **req_ptr,
                               size_t* req_size)
{
   int ret;
   struct spcom_channel *ch;
   struct spcom_msg_hdr *hdr;
   void *rx_buf;
   int rx_buf_size;
   size_t timeout_msec = 0; /* blocking until ready */

   if (!server || !req_ptr)
   {
      LOGE("Invalid parameter.\n");
      return EFI_INVALID_PARAMETER;
   }

   if (server->ch->magic != SPCOM_MAGIC_ID)
   {
      LOGE("Invalid handle.\n");
      return EFI_INVALID_PARAMETER;
   }

   if (server->next_request_size == 0)
   {
	  LOGE("please call spcom_server_get_next_request_size() first.\n");
      return EFI_INVALID_PARAMETER;
   }

   ch = server->ch;

   if (!ch->is_server)
   {
      LOGE("ch is not server ?.\n");
      return EFI_INVALID_PARAMETER;
   }

   /* Allocate Buffers*/
   rx_buf_size = sizeof(*hdr) + server->next_request_size;
   rx_buf = spcom_os_malloc (rx_buf_size);
   if (!rx_buf)
      return EFI_OUT_OF_RESOURCES;

   ret = spcom_rx (ch, rx_buf, rx_buf_size, timeout_msec);
   if (EFI_ERROR (ret))
   {
      LOGE("rx error %d.\n", ret);
      goto exit_err;
   }
   else
   {
      LOGI("*req_size: %d.\n", ret);
      *req_size = ret; /* actual_rx_size */
   }

   // got the request , so clear it.
   server->next_request_size = 0;
   server->got_request = true;

   hdr = rx_buf;

   if (ch->is_server)
   {
      ch->txn_id = hdr->txn_id;
      LOGI("request txn_id [0x%x].\n", (int) ch->txn_id);
   }

   /* copy data to user without the header */
   if (*req_size > sizeof(*hdr))
   {
      *req_size -= sizeof(*hdr);
      *req_ptr = hdr->buf;
      LOGI("New *req_size [0x%x].,req_ptr[0x%x] \n", *req_size, *req_ptr);
      //memcpy (req_ptr, hdr->buf, size);
   }
   else
   {
      LOGE("rx size [%d] too small.\n", *req_size);
      goto exit_err;
   }

   //spcom_os_free (rx_buf);
   return EFI_SUCCESS;
exit_err: spcom_os_free (rx_buf);
   return EFI_DEVICE_ERROR;

}

/**
 * spcom_server_send_response() - Send response
 *
 * @server: server handle
 * @resp_ptr: response buffer pointer
 * @resp_size: response size
 */
EFI_STATUS
spcom_server_send_response (struct spcom_server *server, void *resp_ptr,
                            size_t resp_size)
{
   int ret;
   struct spcom_channel *ch;
   struct spcom_msg_hdr *hdr;
   void *tx_buf;
   int tx_buf_size;

   if (!server || !resp_ptr || !resp_size)
   {
      LOGE("Invalid parameter.\n");
      return EFI_INVALID_PARAMETER;
   }

   if (server->ch->magic != SPCOM_MAGIC_ID)
   {
      LOGE("Invalid handle.\n");
      return EFI_INVALID_PARAMETER;
   }

   if (resp_size > SPCOM_MAX_RESPONSE_SIZE)
   {
      LOGE("resp_size [%d] > max resp size [%d].\n", resp_size,
      SPCOM_MAX_RESPONSE_SIZE);
      return EFI_INVALID_PARAMETER;
   }

   if (server->got_request == false)
   {
      LOGE("please get request before sending response.\n");
      return EFI_INVALID_PARAMETER;
   }

   ch = server->ch;

   if (!ch->is_server)
   {
      LOGE("ch is not server ?.\n");
      return EFI_INVALID_PARAMETER;
   }

   /* Check if remote side connect */
   if (!spcom_is_channel_connected (ch))
   {
      LOGE("ch [%a] remote side not connect.\n", ch->name);
      return EFI_DEVICE_ERROR;
   }

   /* Allocate Buffers*/
   tx_buf_size = sizeof(*hdr) + resp_size;
   tx_buf = spcom_os_malloc (tx_buf_size);

   if (tx_buf == NULL)
      return EFI_OUT_OF_RESOURCES;

   /* Prepare Tx Buf */
   hdr = tx_buf;

   /* Header */
   hdr->txn_id = ch->txn_id;

   /* copy user buf */
   memscpy (hdr->buf, resp_size, resp_ptr, resp_size);

   /*
    * remote side should have rx buffer ready.
    * tx_done is expected to be received quickly.
    */
   ret = spcom_tx (ch, tx_buf, tx_buf_size, TX_DONE_TIMEOUT_MSEC);
   if (EFI_ERROR (ret))
      LOGE("tx error %d.\n", ret);
   spcom_os_free (tx_buf);

   server->got_request = false; // for next time

   return ret;
}

EFI_STATUS
spcom_server_get_next_request (struct spcom_server *server)
{
   EFI_STATUS status = EFI_SUCCESS;
   void *req_ptr;
   void *resp_ptr;
   size_t req_size = 0;
   size_t resp_size = 0;

   /*
    * 1. Poll on server channel for 1000 ms (TODO: Should we get the timeout from service?)
    * 2. Notify server, with the request and get back response.
    * 3. Send the response received from the server, to SPU
    */

   status = spcom_server_get_next_request_size (server, SPCOM_SERVER_CMD_TIMEOUT);

   if (EFI_ERROR (status) || server->next_request_size <= 0)
   {
	  LOGE("spcom_server_get_next_request_size status %d size = %d\n", status, server->next_request_size);
	  spcom_check_if_spss_crashed();
      return status;
   }

   status = spcom_server_wait_for_request (server, &req_ptr, &req_size);

   if (EFI_ERROR (status))
   {
	  LOGE("spcom_server_wait_for_request status %d \n", status);
	  spcom_check_if_spss_crashed();
      return status;
   }
   
   server->ch->notify_server_request_cb (server, req_ptr,
                                         req_size,
                                         (void**) &resp_ptr, &resp_size, server->server_param);

   if (!resp_ptr || !resp_size)
   {
      LOGE("Invalid parameter.\n");
      return EFI_INVALID_PARAMETER;
   }

   status = spcom_server_send_response (server, resp_ptr, resp_size);
   
   return status;
}

/*======================================================================*/
/*                             spcom_sanity_test                              */
/*======================================================================*/
#ifdef SPCOMDXE_SANITY_TEST

EFI_STATUS
spcom_sanity_test ()
{
   /*
    * The Test does the following,
    * 1. Check if cryptoapp is loaded (This sends the command to cryptoapp)
    * 2. Request health status of SPU
    */
   EFI_STATUS status = EFI_SUCCESS;
   size_t rx_size = 0;

   struct spcom_client* service_client = NULL;
   LOGE("spcom_sanity_test () \n");

   status = spcom_connect_service_client (&service_client);

   if (EFI_ERROR(status))
   {
      LOGE("spcom_connect_service_client failed (%d).\n", status);
      return status;
   }

   const char *crypto = "cryptoapp";
   status = spcom_is_app_loaded (crypto);

   if (EFI_ERROR(status))
   {
      LOGE("spcom_is_app_loaded (%d).\n", status);
      return status;
   }

   sp_health_request_t req = {};
   sp_health_response_t rsp = {};

   // Send command to SP side
   req.cmd_opcode = SP_CMD_ID_CHECK_SP_HEALTH;
   req.type_of_check = SP_HEALTH_ARI_MODE;

   // Send command to SP side
   status = spcom_client_send_message_sync (service_client, &req, sizeof(req),
                                         &rsp, sizeof(rsp),&rx_size,
                                         TX_DONE_TIMEOUT_MSEC);

   // Error when sending the message
   if (EFI_ERROR(status))
   {
      LOGE("client CHECK_SP_HEALTH_CMD_ID send failed (%d).\n", status);
   }
   else
   {
      if (rsp.error_code == 0)
      {
         LOGE("Sensors Calibration: %a, ARI mode: %d, ARI fuse: %d, ARI Gauge: %d\n",
               (rsp.checks_values.sensors_calibrated) ? "Ok" : "None",
               rsp.checks_values.ari_mode,
               rsp.checks_values.ari_on_fuse,
               rsp.checks_values.ari_fuse_gauge));

         if ((sp_health_ari_on_fuse_t) rsp.checks_values.ari_on_fuse == ARI_FUSE_ON
               || (sp_health_ari_on_fuse_t) rsp.checks_values.ari_on_fuse
                     == ARI_FUSE_RESERVED)
         {
        	 LOGE("POR indicator: %d, POR counter %d",
                  rsp.checks_values.por_indicator,
                  rsp.checks_values.por_counter);
         }
      }
      else
      {
         LOGE("Failed to read SP Health Info.[%d]\n", rsp.error_code);
      }
   }
   return status;
}
#endif

/*======================================================================*/
/*                             spcom_init                              */
/*======================================================================*/

EFI_STATUS
spcom_init (void)
{
   spcom_os_al_init (); /* call it before any log print ! */

   LOGI("spcom_init() version 1.0 22-June-2020\n");

   spcom_dev = spcom_os_malloc (sizeof(*spcom_dev));
   if (spcom_dev == NULL)
      return EFI_OUT_OF_RESOURCES;
   memset(spcom_dev, 0, sizeof(*spcom_dev));

   spcom_dev->link_state = GLINK_LINK_STATE_DOWN;

   spcom_os_init_event (&spcom_dev->link_state_changed);

   return EFI_SUCCESS;
}
