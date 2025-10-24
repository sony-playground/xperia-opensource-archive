/*=============================================================================

                            SLVCOM CORE

 Slave Communication Core.

 Copyright  2021-2022 Qualcomm Technologies, Inc. All Rights Reserved.
 Qualcomm Technologies, Inc. Confidential and Proprietary.

=============================================================================*/

/*=============================================================================

                         EDIT HISTORY FOR FILE

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/SlvcomLib/src/slvcom_core.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
===========================================================================*/


/*=============================================================================

                           INCLUDE FILES

=============================================================================*/
#include "com_dtypes.h"
#include "slvcom.h"
#include "slvcom_cfg.h"
#include "slvcom_list.h"
#include "slvcom_log.h"
#include "slvcom_os.h"
#include "slvcom_spi.h"
#include "slvcom_gpio.h"
#include "slvcom_target.h"

/*=============================================================================

                         MACRO DECLARATIONS

=============================================================================*/
#undef  SLVCOM_LOG_TAG
#define SLVCOM_LOG_TAG "CORE"

/* Maximum write protocol overhead is 5 bytes (in Full AHB write) */
#define SLVCOM_WR_PROTOCOL_OVERHEAD              (5)
#define SLVCOM_WR_PROTOCOL_OVERHEAD_IN_WORDS     (2)

#define SLVCOM_WR_BUF_SIZE_IN_BYTES              SLVCOM_CFG_WR_BUF_SIZE
#define SLVCOM_WR_BUF_SIZE_IN_WORDS           \
            (SLVCOM_CFG_WR_BUF_SIZE / sizeof(uint32))

#define SLVCOM_WR_BUF_SIZE_IN_WORDS_FOR_USE   \
            (SLVCOM_WR_BUF_SIZE_IN_WORDS - SLVCOM_WR_PROTOCOL_OVERHEAD_IN_WORDS)

/* Maximum read protocol overhead is (5 + ideal bytes) bytes (in Full AHB read) */
#define SLVCOM_RD_PROTOCOL_OVERHEAD              (5 + SLVCOM_CFG_READ_IDEAL_BYTES)
/* Max two words are sufficient, but keep spare word incase IDEAL bytes increases */
#define SLVCOM_RD_PROTOCOL_OVERHEAD_IN_WORDS     (3)

#define SLVCOM_RD_BUF_SIZE_IN_BYTES               SLVCOM_CFG_RD_BUF_SIZE
#define SLVCOM_RD_BUF_SIZE_IN_WORDS           \
            (SLVCOM_CFG_RD_BUF_SIZE / sizeof(uint32))

#define SLVCOM_RD_BUF_SIZE_IN_WORDS_FOR_USE   \
            (SLVCOM_RD_BUF_SIZE_IN_WORDS - SLVCOM_RD_PROTOCOL_OVERHEAD_IN_WORDS)

/* Convert register 7 bit address to 8 bit register write address */
#define SLVCOM_WR_OPERATION_ADDR(addr_7bit)      (((uint8)addr_7bit) << 1)

/* Convert register 7 bit address to 8 bit register read address */
#define SLVCOM_RD_OPERATION_ADDR(addr_7bit)      ((((uint8)addr_7bit) << 1) | 1)

/* Notify event array size */
#define SLVCOM_MAX_NOTIFY_EVENTS                  SLVCOM_EVENT_LAST

/*=============================================================================

                         TYPE DEFINITIONS

=============================================================================*/

/**
 * MASTER_COMMAND register
 * *** DO NOT CHANGE ***
 */
typedef union {
  struct {
    uint32 RESERVED : 28;
    uint32 RESET_READ_FIFO : 1;
    uint32 RESET_WRITE_FIFO : 1;
    uint32 SLAVE_OK_TO_SLEEP : 2;
  } bitfield;
  uint32 value;
} slvcom_reg_master_command_type;

/**
 * SLAVE_STATUS register
 * *** DO NOT CHANGE ***
 */
typedef union {
  struct {
    uint32 RESERVED : 27;
	// uint32 BT_ERROR : 1;
	// uint32 DSP_ERROR : 1;
    uint32 AHB_READY : 1;
    uint32 TO_MASTER_FIFO_READY : 1;
    uint32 TO_SLAVE_FIFO_READY : 1;
    uint32 APPLICATION_RUNNING : 1;
    uint32 READY : 1;
  } bitfield;
  uint32 value;
} slvcom_reg_slave_status_type;

/**
 * SLAVE_STATUS_AUTO_CLEAR register
 * *** DO NOT CHANGE ***
 */
typedef union {
  struct {
    uint32 RESERVED : 17;
    uint32 SS_IN_ERROR : 1;
    uint32 OK_TO_SLEEP_CLEARED : 1;
    uint32 TO_SLAVE_FIFO_RESET_COMPLETE : 1;
    uint32 TO_MASTER_FIFO_RESET_COMPLETE : 1;
    uint32 ERROR_AHB_BUS_ERR : 1;
    uint32 ERROR_AHB_ILLEGAL_ADDRESS : 1;
    uint32 ERROR_TRUNCATED_WRITE : 1;
    uint32 ERROR_TRUNCATED_READ : 1;
    uint32 ERROR_READ_FIFO_ACCESS : 1;
    uint32 ERROR_READ_FIFO_BUS_ERR : 1;
    uint32 ERROR_READ_FIFO_UNDERUN : 1;
    uint32 ERROR_WRITE_FIFO_ACCESS : 1;
    uint32 ERROR_WRITE_FIFO_BUS_ERR : 1;
    uint32 ERROR_WRITE_FIFO_OVERRUN : 1;
    uint32 RESET_OCCURRED : 1;
  } bitfield;
  uint32 value;
} slvcom_reg_slave_status_auto_clear_type;

/**
 * FIFO_FILL register
 * *** DO NOT CHANGE ***
 */
typedef union {
  struct {
    uint32 TO_MASTER_FIFO_USED : 16;
    uint32 TO_SLAVE_FIFO_FREE : 16;
  } bitfield;
  uint32 value;
} slvcom_reg_fifo_fill_type;

/**
 * SLV Status registers
 * *** DO NOT CHANGE ***
 */
typedef struct {
  slvcom_reg_slave_status_type            slave_status;
  uint32                                 timestamp;
  slvcom_reg_slave_status_auto_clear_type slave_status_auto_clear;
  slvcom_reg_fifo_fill_type               fifo_fill;
} slvcom_status_regs_type;

/**
 * Operation type
 */
typedef enum
{
  SLVCOM_OPERATION_REG  = 1,
  SLVCOM_OPERATION_FIFO = 2,
  SLVCOM_OPERATION_AHB  = 3,
} slvcom_operation_type;

/**
 * State type
 */
typedef enum {
  SLVCOM_STATE_SLEEP = 0,
  SLVCOM_STATE_READY = 1,
  SLVCOM_STATE_RESET = 0xDEAD
} slvcom_state_type;

/**
 * Client Statistics
 */
typedef struct
{
  uint32 unused;
} slvcom_client_stat_type;

/**
 * Client structure
 */
typedef struct slvcom_client_struct slvcom_client_type;
struct slvcom_client_struct
{

  /* Client name */
  char                  client_name[SLVCOM_MAX_CLIENT_NAME_LENGTH];

  /* Client private data pointer.
   * This data is passed back to client in the notification callbacks */
  void                  *priv;

  /* Client notification callbacks to notify the SLV events */
  slvcom_notification_cb notify_cb;

  /* Bitfield for specifying various options */
  uint32                options;

  /* Bitfield that indicates client interested events */
  uint32                events_required;
  
  slvcom_client_stat_type stat;

  uint32                 enabled_secmode;

  SLVCOM_LINK(slvcom_client_type, link);
};

/**
 * SLVCOM info
 */
typedef struct {
  /* Initialize state */
  boolean inited;
  boolean target_no_support;
  
  /* Mutex used to protect common data */
  slvcom_os_mutex_type mutex;

  /* SLVCOM status */
  slvcom_state_type state;

  /* Read buffer */
  uint8 *rd_buf_paddr;
  uint8 *rd_buf_vaddr;

  /* Write buffer */
  uint8 *wr_buf_paddr;
  uint8 *wr_buf_vaddr;

  /* SLV status registers latest values */
  slvcom_status_regs_type status_regs;

  /* Client handles list */
  SLVCOM_LIST(slvcom_client_type, client_list);
  
#if defined(SLVCOM_FEATURE_FULL_SUPPORT)
  /* Activity counter */
  uint32 activity_cnt;

  /* Inactivity timer */
  slvcom_os_timer_type inactivity_timer;
  boolean inactivity_timer_en;
  
  /* SLV to MSM interrupt */
  slvcom_gpio_type *slv_isr_handle;
#endif

#if defined(SLVCOM_FEATURE_SECMODE_SUPPORT)
  /* TZ NS GPIO */
  slvcom_gpio_type *gpio_tz_ns_handle;

  /* Secmode enable count */
  uint32 secmode_total_count;
#endif
} slvcom_info_type;

/* Notify event type */
typedef struct {
  slvcom_event_type      event;
  slvcom_event_data_type event_data;
} slvcom_notify_event_type;

/*=============================================================================

                       LOCAL DATA DECLARATIONS

=============================================================================*/
/** SLVCOM info */
static slvcom_info_type slvcom_info;

#if defined(SLVCOM_FEATURE_FULL_SUPPORT)
/** Notify event array */
static uint32                  slvcom_notify_event_index = 0;
static slvcom_notify_event_type slvcom_notify_event[SLVCOM_MAX_NOTIFY_EVENTS];
#endif /* SLVCOM_FEATURE_FULL_SUPPORT */

/*=============================================================================

                     PUBLIC VARIABLE DECLARATIONS

=============================================================================*/


/*=============================================================================

                     LOCAL FUNCTION DEFINATION

=============================================================================*/

/*=============================================================================
  FUNCTION  slvcom_update_activity
=============================================================================*/
/**
 *
 *
 */
/*===========================================================================*/
static void slvcom_update_activity(void)
{
#if defined(SLVCOM_FEATURE_FULL_SUPPORT)
  /* Update the activity count to indicate activity is happing */
  slvcom_info.activity_cnt++;
  
  if (!slvcom_info.inactivity_timer_en)
  {
    /* Start inactivity timer to monitor ideal/inactivity */
    slvcom_info.inactivity_timer_en = TRUE;
    slvcom_os_timer_set(&slvcom_info.inactivity_timer,
                       SLVCOM_CFG_MAX_IDEAL_TIMEOUT / 2);
  }
#endif /* SLVCOM_FEATURE_FULL_SUPPORT */
}

/*=============================================================================
  FUNCTION  slvcom_internal_write
=============================================================================*/
/**
 * Common write
 *
 */
/*===========================================================================*/
static slvcom_err_type slvcom_internal_write
(
  slvcom_operation_type operation,
  uint8                reg_start_addr,
  slvcom_ahb_addr_type  ahb_addr,
  uint32               num_words,
  uint8                *write_buf,
  uint32               write_buf_size,
  boolean              update_activity
)
{
  uint8  *spi_wr_buf;
  uint32 spi_wr_len;
  uint32 curr_num_words;
  uint32 curr_num_bytes;

  slvcom_err_type err;

  /* Validate the arguments */
  if ((num_words == 0) || (write_buf == NULL) || (write_buf_size < (num_words * 4)))
  {
    SLVCOM_LOG_ERR(6, "Write invalid args operation=%d, reg_start_addr=0x%02X, "
        "ahb_addr=0x%X, num_words=%d, write_buf=0x%X, write_buf_size=%d.",
        operation, reg_start_addr, ahb_addr, num_words, write_buf, write_buf_size);
    return SLVCOM_ERR_INVALID_PARAM;
  }
  
  if (update_activity == TRUE)
  {
    slvcom_update_activity();  
  }

  spi_wr_buf = slvcom_info.wr_buf_vaddr;
  
  while (num_words)
  {
    curr_num_words = (num_words < SLVCOM_WR_BUF_SIZE_IN_WORDS_FOR_USE) ?
                      num_words : SLVCOM_WR_BUF_SIZE_IN_WORDS_FOR_USE;
    curr_num_bytes = curr_num_words * 4;

    /* Prepare SPI write buffer for SPI transfer */
    spi_wr_len = 0;
    spi_wr_buf[spi_wr_len++] = SLVCOM_WR_OPERATION_ADDR(reg_start_addr);

    if (operation == SLVCOM_OPERATION_AHB)
    {
      /* REG_ADDR+W + AHB_ADDR + CLIENT_DATA
       * Copy AHB_ADDR */
      slvcom_os_memcopy(&spi_wr_buf[spi_wr_len],
                       SLVCOM_WR_BUF_SIZE_IN_BYTES - spi_wr_len,
                       &ahb_addr, sizeof(slvcom_ahb_addr_type));

      spi_wr_len += sizeof(slvcom_ahb_addr_type);
      ahb_addr   += curr_num_bytes;
    }

    /* Copy CLIENT_DATA */
    slvcom_os_memcopy(&spi_wr_buf[spi_wr_len],
                     SLVCOM_WR_BUF_SIZE_IN_BYTES - spi_wr_len,
                     write_buf, curr_num_bytes);

    spi_wr_len += curr_num_bytes;
    write_buf  += curr_num_bytes;

    /* SPI transfer */
    err = slvcom_spi_transfer(slvcom_info.wr_buf_paddr, spi_wr_buf, spi_wr_len,
                             slvcom_info.rd_buf_paddr, slvcom_info.rd_buf_vaddr, spi_wr_len);
    if (err != SLVCOM_ERR_NONE)
    {
      return err;
    }

    num_words -= curr_num_words;

    if (operation == SLVCOM_OPERATION_REG)
    {
      reg_start_addr += curr_num_words;
    }
  }

  return SLVCOM_ERR_NONE;
}

/*=============================================================================
  FUNCTION  slvcom_internal_read
=============================================================================*/
/**
 * Common read
 *
 */
/*===========================================================================*/
static slvcom_err_type slvcom_internal_read
(
  slvcom_operation_type operation,
  uint8                reg_start_addr,
  slvcom_ahb_addr_type  ahb_addr,
  uint32               num_words,
  uint8                *read_buf,
  uint32               read_buf_size,
  boolean              update_activity
)
{
  uint8  *spi_wr_buf;
  uint32 spi_wr_len;
  uint32 curr_num_words;
  uint32 curr_num_bytes;

  slvcom_err_type err;

  /* Validate the arguments */
  if ((num_words == 0) || (read_buf == NULL) || (read_buf_size < (num_words * 4)))
  {
    SLVCOM_LOG_ERR(6, "Read invalid args operation=%d, reg_start_addr=0x%02X, "
                  "ahb_addr=0x%X, num_words=%d, read_buf=0x%X, read_buf_size=%d.",
                  operation, reg_start_addr, ahb_addr, num_words, read_buf, read_buf_size);
    return SLVCOM_ERR_INVALID_PARAM;
  }

  if (update_activity == TRUE)
  {
    slvcom_update_activity();      
  }
  
  spi_wr_buf = slvcom_info.wr_buf_vaddr;

  while (num_words)
  {
    curr_num_words = (num_words < SLVCOM_RD_BUF_SIZE_IN_WORDS_FOR_USE) ?
                      num_words : SLVCOM_RD_BUF_SIZE_IN_WORDS_FOR_USE;
    curr_num_bytes = curr_num_words * 4;
    memset(slvcom_info.wr_buf_vaddr, 0, SLVCOM_WR_BUF_SIZE_IN_BYTES);
    memset(slvcom_info.rd_buf_vaddr, 0, SLVCOM_WR_BUF_SIZE_IN_BYTES);

    /* Prepare SPI write buffer for SPI transfer */
    spi_wr_len = 0;
    spi_wr_buf[spi_wr_len++] = SLVCOM_RD_OPERATION_ADDR(reg_start_addr);

    if (operation == SLVCOM_OPERATION_AHB)
    {
      slvcom_os_memcopy(&spi_wr_buf[spi_wr_len],
                       SLVCOM_WR_BUF_SIZE_IN_BYTES - spi_wr_len,
                       &ahb_addr, sizeof(slvcom_ahb_addr_type));

      spi_wr_len += sizeof(slvcom_ahb_addr_type);
      ahb_addr   += curr_num_bytes;
    }

    /* SPI transfer */
    err = slvcom_spi_transfer(slvcom_info.wr_buf_paddr, slvcom_info.wr_buf_vaddr, 
                             spi_wr_len + SLVCOM_CFG_READ_IDEAL_BYTES + curr_num_bytes, 
                             slvcom_info.rd_buf_paddr, slvcom_info.rd_buf_vaddr,
                             spi_wr_len + SLVCOM_CFG_READ_IDEAL_BYTES + curr_num_bytes);
    if (err != SLVCOM_ERR_NONE)
    {
      return err;
    }

    /* Discard first write number bytes and ideal bytes from read buffer and copy the actual
     * data to client read buffer  */
    slvcom_os_memcopy(read_buf, curr_num_bytes,
                     &slvcom_info.rd_buf_vaddr[spi_wr_len + SLVCOM_CFG_READ_IDEAL_BYTES],
                     curr_num_bytes);

    num_words -= curr_num_words;
    read_buf  += curr_num_bytes;

    if (operation == SLVCOM_OPERATION_REG)
    {
      reg_start_addr += curr_num_words;
    }
  }

  return SLVCOM_ERR_NONE;
}

/*=============================================================================
  FUNCTION  slvcom_slave_wakeup
=============================================================================*/
/**
 *
 *
 */
/*===========================================================================*/
static slvcom_err_type slvcom_slave_wakeup(void)
{
  /* Check if Secmode is enabled or not */
#ifdef SLVCOM_FEATURE_SECMODE_SUPPORT
#if 0 /* Not required for Aurora */
  if(slvcom_info.secmode_total_count == 0)
  {
    return SLVCOM_ERR_SECMODE_NOT_ENABLED;
  }
#endif

  /* In Secure Modes, SLV is not expected to be Ready as it might not be booted 
     completely. So, we need to go ahead and read TZ regs on SPI */
  slvcom_info.state = SLVCOM_STATE_READY;
  return SLVCOM_ERR_NONE;
  
#else /* SLVCOM_FEATURE_SECMODE_SUPPORT */

  slvcom_err_type err;
  slvcom_err_type ret_val;
  uint32         retry_cnt;

  /* If SLV is already ready, no need to check again */
  if (slvcom_info.state == SLVCOM_STATE_READY)
  {
    return SLVCOM_ERR_NONE;
  }

  SLVCOM_LOG_DBG(1, "slvcom_slave_wakeup! slvcom_info.state=%d.", slvcom_info.state);

  /* If state is reset, just try once to see slave is ready */
  if (slvcom_info.state == SLVCOM_STATE_RESET)
  {
    retry_cnt = 1;
    ret_val   = SLVCOM_ERR_RESET;
  }
  else
  {
    retry_cnt = SLVCOM_CFG_SLAVE_WAKEUP_TRY_CNT;
    ret_val   = SLVCOM_ERR_NOT_RESPONSIVE;
  }

  do {
    /* Wakeup the SLV Slave */
    slvcom_reg_slave_status_type slave_status;

    /* Read SLAVE_STATUS register to see slave is ready */
    err = slvcom_internal_read(SLVCOM_OPERATION_REG, SLVCOM_REG_SLAVE_STATUS, 0,
                              1, (uint8*)&slave_status, sizeof(slave_status), 
                              FALSE);
    if (err != SLVCOM_ERR_NONE)
    {
      SLVCOM_LOG_ERR(1, "slvcom_internal_read() failed! err=%d.", err);
      slvcom_spi_sleep();
      return err;
    }
    /* Check SLAVE_STATUS.READY */
    if (slave_status.bitfield.READY)
    {
      /* Update the state to ready */
      slvcom_info.state = SLVCOM_STATE_READY;
      break;
    }

    retry_cnt--;

    if (retry_cnt)
    {
      slvcom_os_sleep(SLVCOM_CFG_SLAVE_WAKEUP_DELAY_USEC);
    }
  } while (retry_cnt);

  if (slvcom_info.state == SLVCOM_STATE_READY)
  {
    ret_val = SLVCOM_ERR_NONE;
  }
  else
  {
    SLVCOM_LOG_ERR(1, "SLV Slave is not responding! ret_val=%d.", ret_val);

    /* SLV Slave is not responding or it is in reset, so it okay inform SPI to goto sleep */
    slvcom_spi_sleep();
  }
  
  return ret_val;
  
#endif /* SLVCOM_FEATURE_SECMODE_SUPPORT */
}

#if defined(SLVCOM_FEATURE_FULL_SUPPORT)
/*=============================================================================
  FUNCTION  slvcom_queue_notify_event
=============================================================================*/
/**
 *
 *
 */
/*===========================================================================*/
static void slvcom_queue_notify_event
(
  slvcom_event_type      event,
  slvcom_event_data_type *event_data
)
{
  slvcom_notify_event_type *notify_event;

  if (slvcom_notify_event_index >= SLVCOM_MAX_NOTIFY_EVENTS)
  {
    SLVCOM_LOG_FATAL(2, "Reached the max notify events! Increase "
      "SLVCOM_MAX_NOTIFY_EVENTS value. slvcom_notify_event_index = %d, "
      "SLVCOM_MAX_NOTIFY_EVENTS = %d.",
      slvcom_notify_event_index, SLVCOM_MAX_NOTIFY_EVENTS);
    return;
  }

  notify_event = &slvcom_notify_event[slvcom_notify_event_index++];

  notify_event->event = event;

  if (event_data)
  {
    notify_event->event_data = *event_data;
  }
  else
  {
    memset(&notify_event->event_data, 0, sizeof(slvcom_event_data_type));
  }
}

/*=============================================================================
  FUNCTION  slvcom_notify_client_events
=============================================================================*/
/**
 *
 *
 */
/*===========================================================================*/
static void slvcom_notify_client_events(void)
{
  slvcom_client_type *client;
  uint32 indx;

  for (indx = 0; indx < slvcom_notify_event_index; indx++)
  {
    slvcom_notify_event_type *notify_event = &slvcom_notify_event[indx];

    for (client = SLVCOM_LIST_HEAD(slvcom_info.client_list);
         client;
         client = SLVCOM_LINK_NEXT(client->link))
    {
      /* Notify the events which client is interested */
      if ((client->events_required & (1 << notify_event->event)) && 
          (client->notify_cb != NULL))
      {
        client->notify_cb(client, client->priv, notify_event->event,
                          &notify_event->event_data);
      }
    }
  }
  slvcom_notify_event_index = 0;
}

/*=============================================================================
  FUNCTION  slvcom_inactivity_timer_cb
=============================================================================*/
/**
 *
 *
 */
/*===========================================================================*/
static void slvcom_inactivity_timer_cb(void *unused)
{
  int try_lock;

  try_lock = slvcom_os_mutex_try_lock(&slvcom_info.mutex);
  if (try_lock)
  {
    /* Something already running, so don’t go sleep.
     * Postpone the inactivity timeout */
    slvcom_info.inactivity_timer_en = TRUE;
    slvcom_os_timer_set(&slvcom_info.inactivity_timer,
                       SLVCOM_CFG_MAX_IDEAL_TIMEOUT / 2);
    return;
  }
  /* Got the lock, Check if there is activity happing */
  if (slvcom_info.activity_cnt)
  {
    /* Activity happening, postpone the inactivity timeout */
    slvcom_info.activity_cnt = 0;

    slvcom_info.inactivity_timer_en = TRUE;
    slvcom_os_timer_set(&slvcom_info.inactivity_timer,
                       SLVCOM_CFG_MAX_IDEAL_TIMEOUT / 2);

    goto UNLOCK_RETURN;
  }

  /** There is no activity */
  
  slvcom_info.inactivity_timer_en = FALSE;

  if (slvcom_info.state == SLVCOM_STATE_RESET)
  {
    /* SLV is in reset state, so just notify SPI controller to go to sleep */
    slvcom_spi_sleep();
  }
  else
  {
    slvcom_reg_master_command_type master_cmd;
    slvcom_err_type err;
	
	SLVCOM_LOG_DBG(1, "Entering Sleep slvcom_info.state=%d ", slvcom_info.state);

    /* Set MASTER_STATUS.SLAVE_OK_TO_SLEEP to
     * inform SLV, it is okay to go to sleep */
    master_cmd.value = 0;
    master_cmd.bitfield.SLAVE_OK_TO_SLEEP = 1;

    err = slvcom_internal_write(SLVCOM_OPERATION_REG, SLVCOM_REG_MASTER_COMMAND, 0,
                               1, (uint8*)&master_cmd, sizeof(master_cmd), FALSE);
    if (err != SLVCOM_ERR_NONE)
    {
      SLVCOM_LOG_ERR(1, "slvcom_internal_write() failed! err=%d.", err);
    }

    /* Notify SPI controller to go to sleep */
    slvcom_spi_sleep();

    /* Update the state */
    slvcom_info.state = SLVCOM_STATE_SLEEP;
  }

UNLOCK_RETURN:
  slvcom_os_mutex_unlock(&slvcom_info.mutex);
}

/*=============================================================================
FUNCTION  slvcom_slave_status_auto_clear_handler
=============================================================================*/
/**
*
*
*/
/*===========================================================================*/
static void slvcom_slave_status_auto_clear_handler
(
  slvcom_reg_slave_status_auto_clear_type slave_status_auto_clear
)
{
  /* Check if there are any status updates */
  if (!slave_status_auto_clear.value)
  {
    return;
  }

  /* Update SLAVE_STATUS_AUTO_CLEAR shadow */
  slvcom_info.status_regs.slave_status_auto_clear = slave_status_auto_clear;

  if (slave_status_auto_clear.bitfield.ERROR_WRITE_FIFO_OVERRUN)
  {
    slvcom_queue_notify_event(SLVCOM_EVENT_ERROR_WRITE_FIFO_OVERRUN, NULL);
  }
  if (slave_status_auto_clear.bitfield.ERROR_WRITE_FIFO_BUS_ERR)
  {
    slvcom_queue_notify_event(SLVCOM_EVENT_ERROR_WRITE_FIFO_BUS_ERR, NULL);
  }
  if (slave_status_auto_clear.bitfield.ERROR_WRITE_FIFO_ACCESS)
  {
    slvcom_queue_notify_event(SLVCOM_EVENT_ERROR_WRITE_FIFO_ACCESS, NULL);
  }
  if (slave_status_auto_clear.bitfield.ERROR_READ_FIFO_UNDERUN)
  {
    slvcom_queue_notify_event(SLVCOM_EVENT_ERROR_READ_FIFO_UNDERUN, NULL);
  }
  if (slave_status_auto_clear.bitfield.ERROR_READ_FIFO_BUS_ERR)
  {
    slvcom_queue_notify_event(SLVCOM_EVENT_ERROR_READ_FIFO_BUS_ERR, NULL);
  }
  if (slave_status_auto_clear.bitfield.ERROR_READ_FIFO_ACCESS)
  {
    slvcom_queue_notify_event(SLVCOM_EVENT_ERROR_READ_FIFO_ACCESS, NULL);
  }
  if (slave_status_auto_clear.bitfield.ERROR_TRUNCATED_READ)
  {
    slvcom_queue_notify_event(SLVCOM_EVENT_ERROR_TRUNCATED_READ, NULL);
  }
  if (slave_status_auto_clear.bitfield.ERROR_TRUNCATED_WRITE)
  {
    slvcom_queue_notify_event(SLVCOM_EVENT_ERROR_TRUNCATED_WRITE, NULL);
  }
  if (slave_status_auto_clear.bitfield.ERROR_AHB_ILLEGAL_ADDRESS)
  {
    slvcom_queue_notify_event(SLVCOM_EVENT_ERROR_AHB_ILLEGAL_ADDRESS, NULL);
  }
  if (slave_status_auto_clear.bitfield.ERROR_AHB_BUS_ERR)
  {
    slvcom_queue_notify_event(SLVCOM_EVENT_ERROR_AHB_BUS_ERR, NULL);
  }
  if (slave_status_auto_clear.bitfield.TO_MASTER_FIFO_RESET_COMPLETE)
  {
    slvcom_queue_notify_event(SLVCOM_EVENT_TO_MASTER_FIFO_RESET_COMPLETE, NULL);
  }
  if (slave_status_auto_clear.bitfield.TO_SLAVE_FIFO_RESET_COMPLETE)
  {
    slvcom_queue_notify_event(SLVCOM_EVENT_TO_SLAVE_FIFO_RESET_COMPLETE, NULL);
  }
}

/*=============================================================================
FUNCTION  slvcom_fifo_fill_handler
=============================================================================*/
/**
*
*
*/
/*===========================================================================*/
static void slvcom_fifo_fill_handler
(
  slvcom_reg_fifo_fill_type fifo_fill
)
{
  slvcom_reg_fifo_fill_type shadow_fifo_fill = slvcom_info.status_regs.fifo_fill;

  /* Update FIFO_FILL shadow */
  slvcom_info.status_regs.fifo_fill = fifo_fill;

  if (shadow_fifo_fill.bitfield.TO_MASTER_FIFO_USED !=
      fifo_fill.bitfield.TO_MASTER_FIFO_USED)
  {
    slvcom_event_data_type event_data = { 0 };

    event_data.to_master_fifo_used = fifo_fill.bitfield.TO_MASTER_FIFO_USED;

    /* Queue event to notify the clients */
    slvcom_queue_notify_event(SLVCOM_EVENT_TO_MASTER_FIFO_USED, &event_data);
  }

  if (shadow_fifo_fill.bitfield.TO_SLAVE_FIFO_FREE !=
      fifo_fill.bitfield.TO_SLAVE_FIFO_FREE)
  {
    slvcom_event_data_type event_data = { 0 };
    event_data.to_slave_fifo_free = fifo_fill.bitfield.TO_SLAVE_FIFO_FREE;

    /* Queue event to notify the clients */
    slvcom_queue_notify_event(SLVCOM_EVENT_TO_SLAVE_FIFO_FREE, &event_data);
  }
}

/*=============================================================================
FUNCTION  slvcom_timestamp_handler
=============================================================================*/
/**
*
*
*/
/*===========================================================================*/
static void slvcom_timestamp_handler
(
  uint64 msm_timetick,
  uint32 slv_timestamp
)
{
  if (slvcom_info.status_regs.timestamp != slv_timestamp)
  {
    slvcom_event_data_type event_data = { 0 };

    /* Update shadow */
    slvcom_info.status_regs.timestamp = slv_timestamp;

    /* Update the event data */
    event_data.timestamp.msm_timetick = msm_timetick;
    event_data.timestamp.slv_timestamp = slv_timestamp;

    /* Queue event to notify the clients */
    slvcom_queue_notify_event(SLVCOM_EVENT_TIMESTAMP, &event_data);
  }
}

/*=============================================================================
FUNCTION  slvcom_slave_status_handler
=============================================================================*/
/**
*
*
*/
/*===========================================================================*/
static void slvcom_slave_status_handler
(
  slvcom_reg_slave_status_type slave_status
)
{
  slvcom_reg_slave_status_type shadow_slave_status;
  slvcom_event_data_type event_data = { 0 };

  shadow_slave_status = slvcom_info.status_regs.slave_status;

  /* Check if there are any status updates */
  if (shadow_slave_status.value == slave_status.value)
  {
    return;
  }

  /* Update the shadow */
  slvcom_info.status_regs.slave_status = slave_status;

  /* Check for any changes */
  if (shadow_slave_status.bitfield.APPLICATION_RUNNING != slave_status.bitfield.APPLICATION_RUNNING)
  {
    event_data.application_running = slave_status.bitfield.APPLICATION_RUNNING;
    slvcom_queue_notify_event(SLVCOM_EVENT_APPLICATION_RUNNING, &event_data);
  }

  if (shadow_slave_status.bitfield.TO_SLAVE_FIFO_READY != slave_status.bitfield.TO_SLAVE_FIFO_READY)
  {
    event_data.to_slave_fifo_ready = slave_status.bitfield.TO_SLAVE_FIFO_READY;
    slvcom_queue_notify_event(SLVCOM_EVENT_TO_SLAVE_FIFO_READY, &event_data);
  }

  if (shadow_slave_status.bitfield.TO_MASTER_FIFO_READY != slave_status.bitfield.TO_MASTER_FIFO_READY)
  {
    event_data.to_master_fifo_ready = slave_status.bitfield.TO_MASTER_FIFO_READY;
    slvcom_queue_notify_event(SLVCOM_EVENT_TO_MASTER_FIFO_READY, &event_data);
  }

  if (shadow_slave_status.bitfield.AHB_READY != slave_status.bitfield.AHB_READY)
  {
    event_data.ahb_ready = slave_status.bitfield.AHB_READY;
    slvcom_queue_notify_event(SLVCOM_EVENT_AHB_READY, &event_data);
  }

#if 0
  if (shadow_slave_status.bitfield.DSP_ERROR != slave_status.bitfield.DSP_ERROR)
  {
	event_data.dsp_error = slave_status.bitfield.DSP_ERROR;
	slvcom_queue_notify_event(SLVCOM_EVENT_DSP_ERROR, &event_data);
  }

  if (shadow_slave_status.bitfield.BT_ERROR != slave_status.bitfield.BT_ERROR)
  {
	event_data.bt_error = slave_status.bitfield.BT_ERROR;
	slvcom_queue_notify_event(SLVCOM_EVENT_BT_ERROR, &event_data);
  }
#endif // comment
}

/*=============================================================================
  FUNCTION  slvcom_slv_isr
=============================================================================*/
/**
 *
 *
 */
/*===========================================================================*/
static void slvcom_slv_isr(void *unused)
{
  slvcom_status_regs_type slv_status_regs;
  uint64                 msm_timetick;
  slvcom_err_type         err;
  static uint32          spurious_intr_cnt;

  /* Get current MSM time tick to notify the clients when there is
   * SLV timestamp change */
  msm_timetick = slvcom_os_timetick_get();

  slvcom_os_mutex_lock(&slvcom_info.mutex);

  SLVCOM_LOG_DBG(2, "slvcom_slv_isr spurious_intr_cnt=%d, slvcom_info.state=%d.", spurious_intr_cnt, slvcom_info.state);
  
  /* Read SLAVE_STATUS, TIMESTAMP, SLAVE_STATUS_AUTO_CLEAR, and FIFO_FILL
   * registers in single transaction */
  err = slvcom_internal_read(SLVCOM_OPERATION_REG,
                            SLVCOM_REG_SLAVE_STATUS,
                            0,
                            sizeof(slv_status_regs) / sizeof(uint32),
                            (uint8*)&slv_status_regs,
                            sizeof(slv_status_regs),
                            TRUE);
  if (err != SLVCOM_ERR_NONE)
  {
    SLVCOM_LOG_FATAL(1, "slvcom_internal_read is failed! err=%d", err);
    goto UNLOCK_RETURN;
  }

  /* If SLV is in reset or sleep state, check the SLV SPI is ready
   * SLAVE_STATUS.READY first */
  if ((slvcom_info.state == SLVCOM_STATE_RESET) ||
      (slvcom_info.state == SLVCOM_STATE_SLEEP))
  {
    if (slv_status_regs.slave_status.bitfield.READY)
    {
      /* SLV SPI slave is ready, so move to ready state */
      slvcom_info.state = SLVCOM_STATE_READY;

      spurious_intr_cnt = 0;
    }
    else
    {
      spurious_intr_cnt++;
      /* This looks to be spurious interrupt */
      if (spurious_intr_cnt < 5)
      {
        SLVCOM_LOG_ERR(1, "Spurious interrupt from SLV count=%d.", spurious_intr_cnt);
      }
      else
      {
        SLVCOM_LOG_FATAL(1, "Spurious interrupt from SLV count=%d.", spurious_intr_cnt);
      }
      goto UNLOCK_RETURN;
    }
  }

  /* Check the status registers and notify the clients.
   * First start with reset status */

  if (slv_status_regs.slave_status_auto_clear.bitfield.RESET_OCCURRED)
  {
    /* SLV reset happened */
    SLVCOM_LOG_ERR(0, "SLV reset happened!");

    if (slvcom_info.state != SLVCOM_STATE_RESET)
    {
       /* Update the state */
       slvcom_info.state = SLVCOM_STATE_RESET;

       /* Clear status register values */
       memset(&slvcom_info.status_regs, 0, sizeof(slvcom_status_regs_type));

       /* Queue event to notify the clients */
       slvcom_queue_notify_event(SLVCOM_EVENT_RESET_OCCURRED, NULL);
    }

    goto UNLOCK_CLIENT_NOTIFY;
  }

  /* Timestamp */
  slvcom_timestamp_handler(msm_timetick, slv_status_regs.timestamp);

  /* SLAVE_STATUS_AUTO_CLEAR */
  slvcom_slave_status_auto_clear_handler(slv_status_regs.slave_status_auto_clear);

  /* SLAVE_STATUS */
  slvcom_slave_status_handler(slv_status_regs.slave_status);

  /* FIFO_FILL */
  slvcom_fifo_fill_handler(slv_status_regs.fifo_fill);

UNLOCK_CLIENT_NOTIFY:
  slvcom_os_mutex_unlock(&slvcom_info.mutex);
  slvcom_notify_client_events();
  return;

UNLOCK_RETURN:
  slvcom_os_mutex_unlock(&slvcom_info.mutex);
}
#endif /* SLVCOM_FEATURE_FULL_SUPPORT */

/*=============================================================================
  FUNCTION  slvcom_client_write
=============================================================================*/
/**
 * Common write
 *
 */
/*===========================================================================*/
static slvcom_err_type slvcom_client_write
(
  slvcom_handle_type    handle,
  slvcom_operation_type operation,
  uint8                reg_start_addr,
  slvcom_ahb_addr_type  ahb_addr,
  uint32               num_words,
  uint8                *write_buf,
  uint32               write_buf_size
)
{
  slvcom_err_type err;

  SLVCOM_LOG_DBG(7, "Write start handle=0x%X, operation=%d, reg_start_addr=0x%02X, ahb_addr=0x%X, "
        "num_words=%d, write_buf=0x%X, write_buf_size=%d.", handle, operation, reg_start_addr,
        ahb_addr, num_words, write_buf, write_buf_size);

  slvcom_os_mutex_lock(&slvcom_info.mutex);

  /* Wakeup SLV before starting SPI transfer */
  err = slvcom_slave_wakeup();
  if (err != SLVCOM_ERR_NONE)
  {
    SLVCOM_LOG_ERR(1, "SLV slave wakeup failed! err=%d.", err);
    goto UNLOCK_RETURN;
  }

  /* Call internal write function */
  err = slvcom_internal_write(operation, reg_start_addr, ahb_addr,
                             num_words, write_buf, write_buf_size, TRUE);
  if (err != SLVCOM_ERR_NONE)
  {
    SLVCOM_LOG_ERR(1, "slvcom_internal_write failed! err=%d.", err);
    goto UNLOCK_RETURN;
  }

UNLOCK_RETURN:
  slvcom_os_mutex_unlock(&slvcom_info.mutex);

  SLVCOM_LOG_DBG(7, "Write end err=%d, handle=0x%X, operation=%d, reg_start_addr=0x%02X, "
        "ahb_addr=0x%X, num_words=%d, write_buf=0x%X.", err, handle, operation,
        reg_start_addr, ahb_addr, num_words, write_buf);
  return err;
}

/*=============================================================================
  FUNCTION  slvcom_client_read
=============================================================================*/
/**
 * Common read
 *
 */
/*===========================================================================*/
slvcom_err_type slvcom_client_read
(
  slvcom_handle_type    handle,
  slvcom_operation_type operation,
  uint8                reg_start_addr,
  slvcom_ahb_addr_type  ahb_addr,
  uint32               num_words,
  uint8                *read_buf,
  uint32               read_buf_size
)
{
  slvcom_err_type err;

  SLVCOM_LOG_DBG(7, "Read start handle=0x%X, operation=%d, reg_start_addr=0x%02X, ahb_addr=0x%X, "
        "num_words=%d, read_buf=0x%X, read_buf_size=%d.", handle, operation, reg_start_addr,
        ahb_addr, num_words, read_buf, read_buf_size);

  slvcom_os_mutex_lock(&slvcom_info.mutex);

  /* Wakeup SLV before starting SPI transfer */
  err = slvcom_slave_wakeup();
  if (err != SLVCOM_ERR_NONE)
  {
    SLVCOM_LOG_ERR(1, "SLV wakeup failed! err=%d.", err);
    goto UNLOCK_RETURN;
  }

  /* Call internal read function */
  err = slvcom_internal_read(operation, reg_start_addr, ahb_addr,
                            num_words, read_buf, read_buf_size, TRUE);
  if (err != SLVCOM_ERR_NONE)
  {
    SLVCOM_LOG_ERR(1, "slvcom_internal_read failed! err=%d.", err);
    goto UNLOCK_RETURN;
  }

UNLOCK_RETURN:
  slvcom_os_mutex_unlock(&slvcom_info.mutex);

  SLVCOM_LOG_DBG(7, "Read end err=%d, handle=0x%X, operation=%d, reg_start_addr=0x%02X, "
        "ahb_addr=0x%X, num_words=%d, read_buf=0x%X.", err, handle, operation,
        reg_start_addr, ahb_addr, num_words, read_buf);
  return err;
}

/*=============================================================================

                     PUBLIC FUNCTION DEFINATION

=============================================================================*/

/*=============================================================================
  FUNCTION  slvcom_init
=============================================================================*/
/**
 * Initializes the SLVCOM driver
 *
 */
/*===========================================================================*/
void slvcom_init(void)
{
  slvcom_err_type err;

  if (slvcom_info.inited == TRUE || slvcom_info.target_no_support == TRUE)
  {
    SLVCOM_LOG_DBG(0, "slvcom already Initialized or not supported!");
    return;
  }

  memset(&slvcom_info, 0, sizeof(slvcom_info));
  
  /* Initialize the log first */
  slvcom_log_init();

  /* Check if current target is a SLV HW or not */
  if(slvcom_is_target_supported() == FALSE)
  {
    SLVCOM_LOG_DBG(0, "SLVCOM is not supported on this target");
    slvcom_info.inited = FALSE;
    slvcom_info.target_no_support = TRUE;
    return;
  }
  
  /* SLVCOM is supported on this target */
  slvcom_info.target_no_support = FALSE;
  
  /* Initialize SLVCOM state  */
  slvcom_info.state = SLVCOM_STATE_RESET;

  /* Initialize the os layer */
  slvcom_os_init();

  /* Common mutex for protecting common resources */
  slvcom_os_mutex_init(&slvcom_info.mutex);

  /* Initialize the clients list */
  SLVCOM_LIST_INIT(slvcom_info.client_list);

  /* Initialize the SPI interface */
  slvcom_spi_init(SLVCOM_CFG_WR_BUF_SIZE, SLVCOM_CFG_RD_BUF_SIZE, 
                 &slvcom_info.wr_buf_paddr, &slvcom_info.wr_buf_vaddr,
                 &slvcom_info.rd_buf_paddr, &slvcom_info.rd_buf_vaddr);

#if defined(SLVCOM_FEATURE_FULL_SUPPORT)
  /* Initialize inactivity timer */
  slvcom_os_timer_init(&slvcom_info.inactivity_timer,
                      slvcom_inactivity_timer_cb,
                      NULL);
#endif /* SLVCOM_FEATURE_FULL_SUPPORT */

#if defined(SLVCOM_FEATURE_SECMODE_SUPPORT)
  /* Initialize TZ NS GPIO init */
  {
    slvcom_gpio_cfg_type gpio_cfg;

    memset(&gpio_cfg, 0, sizeof(slvcom_gpio_cfg_type));
    gpio_cfg.dir = SLVCOM_GPIO_DIR_OUT;

    err = slvcom_gpio_init((slvcom_gpio_id_type)SLVCOM_CFG_GPIO_TZ_NS, &gpio_cfg, 
                          &slvcom_info.gpio_tz_ns_handle);
    if (err != SLVCOM_ERR_NONE)
    {
      SLVCOM_LOG_FATAL(1, "slvcom_gpio_init(TZ_NS) failed! err=%d", err);
    }
  }
#endif

#if 0
  /* Read SLAVE_STATUS, TIMESTAMP, SLAVE_STATUS_AUTO_CLEAR, and FIFO_FILL
   * registers in single transaction */
  err = slvcom_internal_read(SLVCOM_OPERATION_REG,
                            SLVCOM_REG_SLAVE_STATUS,
                            0,
                            sizeof(slvcom_info.status_regs) / sizeof(uint32),
                            (uint8*)&slvcom_info.status_regs,
                            sizeof(slvcom_info.status_regs),
                            FALSE);
  if (err != SLVCOM_ERR_NONE)
  {
    SLVCOM_LOG_FATAL(1, "slvcom_internal_read is failed! err=%d", err);
  }
  
  SLVCOM_LOG_INFO(1, "slave_status=0x%08X", slvcom_info.status_regs.slave_status.value);
  SLVCOM_LOG_INFO(1, "timestamp=0x%08X", slvcom_info.status_regs.timestamp);
  SLVCOM_LOG_INFO(1, "slave_status_auto_clear=0x%08X", slvcom_info.status_regs.slave_status_auto_clear.value);
  SLVCOM_LOG_INFO(1, "fifo_fill=0x%08X", slvcom_info.status_regs.fifo_fill.value);
  
  /* Close SPI as its opened for internal Read */
  slvcom_spi_sleep();
  
  /* Check SLV status */
  if (!slvcom_info.status_regs.slave_status_auto_clear.bitfield.RESET_OCCURRED)
  {
    if (slvcom_info.status_regs.slave_status.bitfield.READY)
    {
      slvcom_info.state = SLVCOM_STATE_READY;
    }
  }
#else
  slvcom_info.state = SLVCOM_STATE_READY;
#endif
  
#if defined(SLVCOM_FEATURE_FULL_SUPPORT)
  /* Register ISR for SLV to MSM */
  err = slvcom_gpio_reg_int_isr(SLVCOM_CFG_GPIO_SLV_TO_MODEM,
                               SLVCOM_GPIO_INT_TRIGGER_HIGH,
                               slvcom_slv_isr,
                               NULL,
                               &slvcom_info.slv_isr_handle);
  if (err != SLVCOM_ERR_NONE)
  {
    SLVCOM_LOG_FATAL(1, "slvcom_gpio_reg_int_isr failed! err=%d", err);
  }
#endif /* SLVCOM_FEATURE_FULL_SUPPORT */

  /* SLVCOM Initialization is done */
  slvcom_info.inited = TRUE;
}

/*=============================================================================
  FUNCTION  slvcom_open
=============================================================================*/
/**
 * Opens/creates a handle to interact with Slave.
 *
 * @param[in]  open_config   Pointer to the open configuration structure.
 *                           This structure must filled by the clients.
 *                           Use SLVCOM_OPEN_CONFIG_INIT() macro function to
 *                           initialize the structure before setting any
 *                           member of structure.
 * @param[out]  handle       The handle to be used to interact with Slave.
 *
 * @return
 * Sets the handle and returns SLVCOM_ERR_NONE if function is successful,
 * otherwise returns status code (see slvcom_err_type enumeration).
 *
 */
/*===========================================================================*/
slvcom_err_type slvcom_open
(
  slvcom_open_config_type *open_config,
  slvcom_handle_type      *handle
)
{
  slvcom_client_type *client;

#if defined(SLVCOM_FEATURE_FULL_SUPPORT)
  slvcom_reg_slave_status_type slave_status;
  boolean                     notify_event = FALSE;
#endif /* SLVCOM_FEATURE_FULL_SUPPORT */

  /* Validate the client parameters */
  if (handle == NULL || open_config == NULL)
  {
    SLVCOM_LOG_ERR(0, "Invalid handle pointer or config is NULL");
    return SLVCOM_ERR_INVALID_PARAM;
  }
  
  if (slvcom_info.inited == FALSE && slvcom_info.target_no_support == TRUE)
  {
    SLVCOM_LOG_ERR(0, "SLVCOM is not supported!");
    return SLVCOM_ERR_NOT_SUPPORTED;
  }
  else if(slvcom_info.inited == FALSE)
  {
    SLVCOM_LOG_ERR(0, "SLVCOM is not initialized!");
    return SLVCOM_ERR_NOT_INITIALIZED;
  }
  
  slvcom_os_mutex_lock(&slvcom_info.mutex);

  /* Check if any client is present with same name */
  client = SLVCOM_LIST_HEAD(slvcom_info.client_list);
  while(client)
  {
    if(strcmp(client->client_name, open_config->name) == 0)
    {
      //Found client with same name already. This could be duplicate.
      slvcom_os_mutex_unlock(&slvcom_info.mutex);
      
      SLVCOM_LOG_ERR(1, "Client already exists (0x%X)!", client);
      return SLVCOM_ERR_DUPLICATE_CLIENT;
    }
    client = SLVCOM_LINK_NEXT(client->link);
  }

  /* Allocate new client */
  client = slvcom_os_calloc(1, sizeof(slvcom_client_type));
  if (client == NULL)
  {
    SLVCOM_LOG_ERR(1, "Client structure allocation failed! size=%d",
                  sizeof(slvcom_client_type));
    return SLVCOM_ERR_INVALID_PARAM;
  }

  /* Client structure */
  strlcpy(client->client_name, open_config->name, SLVCOM_MAX_CLIENT_NAME_LENGTH);
  client->priv              = open_config->priv;
  client->notify_cb         = open_config->notify_cb;
  client->options           = open_config->options;
  client->events_required   = open_config->events_required;

  /* Return client structure as handle */
  *handle = (slvcom_handle_type)client;

  /* Add client to list */
  SLVCOM_LIST_ADD(slvcom_info.client_list, client, link);

#if defined(SLVCOM_FEATURE_FULL_SUPPORT)
  /* Notify the SLV slave status to client */
  if ((slvcom_info.state != SLVCOM_STATE_RESET) && client->notify_cb)
  {
    slave_status = slvcom_info.status_regs.slave_status;
    notify_event = TRUE;
  }
#endif /* SLVCOM_FEATURE_FULL_SUPPORT */

  slvcom_os_mutex_unlock(&slvcom_info.mutex);

  SLVCOM_LOG_INFO(3, "Client handle open success. client=0x%X, notify_cb=0x%X, "
          "priv=0x%X.", client, client->notify_cb, client->priv);

#if defined(SLVCOM_FEATURE_FULL_SUPPORT)
  /* Notify the latest slave status to client */
  if (notify_event == TRUE)
  {
    slvcom_event_data_type event_data = { 0 };

    event_data.application_running = slave_status.bitfield.APPLICATION_RUNNING;
    client->notify_cb(client, client->priv, SLVCOM_EVENT_APPLICATION_RUNNING, &event_data);

    event_data.to_slave_fifo_ready = slave_status.bitfield.TO_SLAVE_FIFO_READY;
    client->notify_cb(client, client->priv, SLVCOM_EVENT_TO_SLAVE_FIFO_READY, &event_data);

    event_data.to_master_fifo_ready = slave_status.bitfield.TO_MASTER_FIFO_READY;
    client->notify_cb(client, client->priv, SLVCOM_EVENT_TO_MASTER_FIFO_READY, &event_data);

    event_data.ahb_ready = slave_status.bitfield.AHB_READY;
    client->notify_cb(client, client->priv, SLVCOM_EVENT_AHB_READY, &event_data);

#if 0 // Helios CPAS does not have these fields
	event_data.dsp_error = slave_status.bitfield.DSP_ERROR;
    client->notify_cb(client, client->priv, SLVCOM_EVENT_DSP_ERROR, &event_data);

	event_data.bt_error = slave_status.bitfield.BT_ERROR;
    client->notify_cb(client, client->priv, SLVCOM_EVENT_BT_ERROR, &event_data);	
#endif
  }
#endif /* SLVCOM_FEATURE_FULL_SUPPORT */
  return SLVCOM_ERR_NONE;
}

/*=============================================================================
  FUNCTION  slvcom_close
=============================================================================*/
/**
 * Closes the specified handle. No further operation are allowed with Slave.
 *
 * @param[in/out]  handle     Client handle return by slvcom_open()..
 *
 * @return
 * Sets the handle to NULL and returns SLVCOM_ERR_NONE if function is
 * successful, otherwise returns status code (see slvcom_err_type enumeration).
 *
 */
/*===========================================================================*/
slvcom_err_type slvcom_close
(
  slvcom_handle_type *handle
)
{
  /* TODO */
  return SLVCOM_ERR_NONE;
}

/*=============================================================================
  FUNCTION  slvcom_deinit
=============================================================================*/
/**
 * De-Initializes the SLVCOM driver
 *
 */
/*===========================================================================*/
void slvcom_deinit(void)
{
#if defined(SLVCOM_FEATURE_SECMODE_SUPPORT) || defined(SLVCOM_FEATURE_FULL_SUPPORT)
  slvcom_err_type err;
#endif

  slvcom_client_type *client;
  
  if (slvcom_info.inited == FALSE)
  {
    SLVCOM_LOG_ERR(0, "SLVCOM is not initialized!");
    return;
  }
  
  slvcom_os_mutex_lock(&slvcom_info.mutex);
  
  /* Reset SLVCOM state  */
  slvcom_info.state = SLVCOM_STATE_RESET;
  
#if defined(SLVCOM_FEATURE_FULL_SUPPORT)
  /* De-Initialize inactivity timer */
  slvcom_os_timer_deinit(&slvcom_info.inactivity_timer);

  /* Unregister SLV interrupt ISR */
  err = slvcom_gpio_dereg_int_isr(slvcom_info.slv_isr_handle);
  if (err != SLVCOM_ERR_NONE)
  {
    SLVCOM_LOG_FATAL(1, "slvcom_gpio_reg_int_isr failed! err=%d", err);
  }
#endif /* SLVCOM_FEATURE_FULL_SUPPORT */

  /* Remove all the clients from slvcom client list */
  client = SLVCOM_LIST_HEAD(slvcom_info.client_list);
  while(client)
  {
    SLVCOM_LIST_REMOVE(slvcom_info.client_list, client, link);
    slvcom_close((slvcom_handle_type *)client);
    slvcom_os_free(client);
    client = SLVCOM_LIST_HEAD(slvcom_info.client_list);
  }
  
  slvcom_os_mutex_unlock(&slvcom_info.mutex);
  
#if defined(SLVCOM_FEATURE_SECMODE_SUPPORT)
  /* Set gpio to non-secure so that hlos can continue communication */
  err = slvcom_gpio_out(slvcom_info.gpio_tz_ns_handle, SLVCOM_GPIO_VALUE_HIGH);
  if (err != SLVCOM_ERR_NONE)
  {
    SLVCOM_LOG_FATAL(1, "slvcom_gpio_out failed while deinit! err=%d", err);
  }
  
  /* TZ NS GPIO deinit */
  err = slvcom_gpio_deinit(slvcom_info.gpio_tz_ns_handle);
  if (err != SLVCOM_ERR_NONE)
  {
    SLVCOM_LOG_FATAL(1, "slvcom_gpio_init failed! err=%d", err);
  }
#endif
  
  /* De-initialize SPI */
  slvcom_spi_deinit();
  
  /* Update the init state */
  slvcom_info.inited = FALSE;
  
  /* De-init Mutex */
  slvcom_os_mutex_deinit(&slvcom_info.mutex);
} /* slvcom_deinit */

/*=============================================================================
  FUNCTION  slvcom_reg_read
=============================================================================*/
/**
 * Read from the one or more contiguous registers.
 *
 * @param[in]  handle         Client handle return by slvcom_open()..
 * @param[in]  reg_start_addr 7bit start address of the registers to read from.
 * @param[in]  num_regs       Number of contiguous registers to read, starting
 *                            from reg_start_addr.
 * @param[out] read_buf       Buffer to read from the registers.
 * @param[in]  read_buf_size  Read Buffer size in bytes, it should be greater
 *                            than or equal to sizeof(uint32) * num_regs.
 *
 * @return
 * SLVCOM_ERR_NONE if function is successful,
 * Otherwise returns error code (see slvcom_err_type enumeration).
 *
 * @sideeffects  Causes the Slave SPI slave to wakeup. Depending up on
 * the operation, it may also wakeup the complete Slave.
 */
/*===========================================================================*/
slvcom_err_type slvcom_reg_read
(
  slvcom_handle_type handle,
  uint8             reg_start_addr,
  uint8             num_regs,
  void              *read_buf,
  uint32            read_buf_size
)
{
  if (slvcom_info.inited == FALSE && slvcom_info.target_no_support == TRUE)
  {
    SLVCOM_LOG_ERR(0, "SLVCOM is not supported!");
    return SLVCOM_ERR_NOT_SUPPORTED;
  }
  else if(slvcom_info.inited == FALSE)
  {
    SLVCOM_LOG_ERR(0, "SLVCOM is not initialized!");
    return SLVCOM_ERR_NOT_INITIALIZED;
  }
  
  return slvcom_client_read(handle, SLVCOM_OPERATION_REG, reg_start_addr, 0,
                           num_regs, read_buf, read_buf_size);
}

/*=============================================================================
  FUNCTION  slvcom_reg_write
=============================================================================*/
/**
 * Write into the one or more contiguous registers.
 *
 * @param[in]  handle         Client handle return by slvcom_open()..
 * @param[in]  reg_start_addr 7bit start address of the registers to write into.
 * @param[in]  num_regs       Number of contiguous registers to write, starting
 *                            from reg_start_addr.
 * @param[in]  write_buf      Buffer to write into the registers.
 * @param[in]  write_buf_size Write Buffer size in bytes, it should be greater
 *                            than or equal to sizeof(uint32) * num_regs.
 *
 * @return
 * SLVCOM_ERR_NONE if function is successful,
 * Otherwise returns error code (see slvcom_err_type enumeration).
 *
 * @sideeffects  Causes the Slave SPI slave to wakeup. Depending up on
 * the operation, it may also wakeup the complete Slave.
 */
/*===========================================================================*/
slvcom_err_type slvcom_reg_write
(
  slvcom_handle_type handle,
  uint8             reg_start_addr,
  uint8             num_regs,
  void              *write_buf,
  uint32            write_buf_size
)
{
  if (slvcom_info.inited == FALSE && slvcom_info.target_no_support == TRUE)
  {
    SLVCOM_LOG_ERR(0, "SLVCOM is not supported!");
    return SLVCOM_ERR_NOT_SUPPORTED;
  }
  else if(slvcom_info.inited == FALSE)
  {
    SLVCOM_LOG_ERR(0, "SLVCOM is not initialized!");
    return SLVCOM_ERR_NOT_INITIALIZED;
  }
  
  return slvcom_client_write(handle, SLVCOM_OPERATION_REG, reg_start_addr, 0,
                            num_regs, write_buf, write_buf_size);
}

/*=============================================================================
  FUNCTION  slvcom_fifo_read
=============================================================================*/
/**
 * Read data from the TO_MASTER_FIFO.
 *
 * @param[in]  handle         Client handle return by slvcom_open()..
 * @param[in]  num_words      Number of words(32bits) to read from the
 *                            TO_MASTER_FIFO.
 * @param[out] read_buf       Buffer to read from the TO_MASTER_FIFO.
 * @param[in]  read_buf_size  Read Buffer size in bytes, it should be greater
 *                            than or equal to sizeof(uint32) * num_words.
 *
 * @return
 * SLVCOM_ERR_NONE if function is successful,
 * Otherwise returns error code (see slvcom_err_type enumeration).
 *
 * @sideeffects  Causes the Slave SPI slave to wakeup. Depending up on
 * the operation, it may also wakeup the complete Slave.
 */
/*===========================================================================*/
slvcom_err_type slvcom_fifo_read
(
  slvcom_handle_type handle,
  uint32            num_words,
  void              *read_buf,
  uint32            read_buf_size
)
{
  if (slvcom_info.inited == FALSE && slvcom_info.target_no_support == TRUE)
  {
    SLVCOM_LOG_ERR(0, "SLVCOM is not supported!");
    return SLVCOM_ERR_NOT_SUPPORTED;
  }
  else if(slvcom_info.inited == FALSE)
  {
    SLVCOM_LOG_ERR(0, "SLVCOM is not initialized!");
    return SLVCOM_ERR_NOT_INITIALIZED;
  }
  
  return slvcom_client_read(handle, SLVCOM_OPERATION_FIFO, SLVCOM_REG_TO_MASTER_FIFO,
                           0, num_words, read_buf, read_buf_size);
}

/*=============================================================================
  FUNCTION  slvcom_fifo_write
=============================================================================*/
/**
 * Write data to the TO_SLAVE_FIFO.
 *
 * @param[in]  handle         Client handle return by slvcom_open()..
 * @param[in]  num_words      Number of words(32bits) to write to the
 *                            TO_SLAVE_FIFO.
 * @param[in]  write_buf      Buffer to write into the TO_SLAVE_FIFO.
 * @param[in]  write_buf_size Write Buffer size in bytes, it should be greater
 *                            than or equal to sizeof(uint32) * num_words.
 *
 * @return
 * SLVCOM_ERR_NONE if function is successful,
 * Otherwise returns error code (see slvcom_err_type enumeration).
 *
 * @sideeffects  Causes the Slave SPI slave to wakeup. Depending up on
 * the operation, it may also wakeup the complete Slave.
 */
/*===========================================================================*/
slvcom_err_type slvcom_fifo_write
(
  slvcom_handle_type handle,
  uint32            num_words,
  void              *write_buf,
  uint32            write_buf_size
)
{
  if (slvcom_info.inited == FALSE && slvcom_info.target_no_support == TRUE)
  {
    SLVCOM_LOG_ERR(0, "SLVCOM is not supported!");
    return SLVCOM_ERR_NOT_SUPPORTED;
  }
  else if(slvcom_info.inited == FALSE)
  {
    SLVCOM_LOG_ERR(0, "SLVCOM is not initialized!");
    return SLVCOM_ERR_NOT_INITIALIZED;
  }
  
  return slvcom_client_write(handle, SLVCOM_OPERATION_FIFO, SLVCOM_REG_TO_SLAVE_FIFO,
                            0, num_words, write_buf, write_buf_size);
}

/*=============================================================================
  FUNCTION  slvcom_ahb_read
=============================================================================*/
/**
 * Slave AHB memory read.
 *
 * @param[in]  handle         Client handle return by slvcom_open()..
 * @param[in]  ahb_start_addr 32bit AHB start address.
 * @param[in]  num_words      Number of words(32bits) to read.
 * @param[out] read_buf       Buffer to read from the AHB memory.
 * @param[in]  read_buf_size  Read Buffer size in bytes, it should be greater
 *                            than or equal to sizeof(uint32) * num_words.
 *
 * @return
 * SLVCOM_ERR_NONE if function is successful,
 * Otherwise returns error code (see slvcom_err_type enumeration).
 *
 * @sideeffects  Causes the Slave SPI slave to wakeup. Depending up on
 * the operation, it may also wakeup the complete Slave.
 */
/*===========================================================================*/
slvcom_err_type slvcom_ahb_read
(
  slvcom_handle_type   handle,
  slvcom_ahb_addr_type ahb_start_addr,
  uint32              num_words,
  void                *read_buf,
  uint32              read_buf_size
)
{
  slvcom_err_type ret;
  if (slvcom_info.inited == FALSE && slvcom_info.target_no_support == TRUE)
  {
    SLVCOM_LOG_ERR(0, "SLVCOM is not supported!");
    return SLVCOM_ERR_NOT_SUPPORTED;
  }
  else if(slvcom_info.inited == FALSE)
  {
    SLVCOM_LOG_ERR(0, "SLVCOM is not initialized!");
    return SLVCOM_ERR_NOT_INITIALIZED;
  }
  
  ret = slvcom_client_read(handle, SLVCOM_OPERATION_AHB, SLVCOM_REG_TO_MASTER_AHB,
                           ahb_start_addr, num_words, read_buf, read_buf_size);
  SLVCOM_LOG_DBG(4, "slvcom_ahb_read() done: AHB:0x%08X, NumWords:%d, BufSize:%d, ret:%d", ahb_start_addr, num_words, read_buf_size, ret);
  return ret;
}

/*=============================================================================
  FUNCTION  slvcom_ahb_write
=============================================================================*/
/**
 * Slave AHB memory write.
 *
 * @param[in]  handle         Client handle return by slvcom_open()..
 * @param[in]  ahb_start_addr 32bit AHB start address.
 * @param[in]  num_words      Number of words(32bits) to write.
 * @param[in]  write_buf      Buffer to write into the AHB memory.
 * @param[in]  write_buf_size Write Buffer size in bytes, it should be greater
 *                            than or equal to sizeof(uint32) * num_words.
 *
 * @return
 * SLVCOM_ERR_NONE if function is successful,
 * Otherwise returns error code (see slvcom_err_type enumeration).
 *
 * @sideeffects  Causes the Slave SPI slave to wakeup. Depending up on
 * the operation, it may also wakeup the complete Slave.
 */
/*===========================================================================*/
slvcom_err_type slvcom_ahb_write
(
  slvcom_handle_type   handle,
  slvcom_ahb_addr_type ahb_start_addr,
  uint32              num_words,
  void                *write_buf,
  uint32              write_buf_size
)
{
  if (slvcom_info.inited == FALSE && slvcom_info.target_no_support == TRUE)
  {
    SLVCOM_LOG_ERR(0, "SLVCOM is not supported!");
    return SLVCOM_ERR_NOT_SUPPORTED;
  }
  else if(slvcom_info.inited == FALSE)
  {
    SLVCOM_LOG_ERR(0, "SLVCOM is not initialized!");
    return SLVCOM_ERR_NOT_INITIALIZED;
  }
  
  return slvcom_client_write(handle, SLVCOM_OPERATION_AHB, SLVCOM_REG_TO_SLAVE_AHB,
                            ahb_start_addr, num_words, write_buf, write_buf_size);
}

/*=============================================================================
  FUNCTION  slvcom_secmode_enable
=============================================================================*/
/**
 * THIS API IS ONLY AVAILABLE IN THE TZ
 *
 * Makes the NS(S=Secure) to Active low to indicate SECURE(TZ) communication
 * mode is active.
 *
 * @param[in]  handle         Client handle return by slvcom_open()..
 *
 * @return
 * SLVCOM_ERR_NONE if function is successful,
 * Otherwise returns error code (see slvcom_err_type enumeration).
 */
/*===========================================================================*/
slvcom_err_type slvcom_secmode_enable(slvcom_handle_type handle)
{
#if defined(SLVCOM_FEATURE_SECMODE_SUPPORT)
  slvcom_err_type err;
  uint32 count;
  slvcom_client_type *client = (slvcom_client_type *)handle;
  
  if (slvcom_info.inited == FALSE && slvcom_info.target_no_support == TRUE)
  {
    SLVCOM_LOG_ERR(0, "SLVCOM is not supported!");
    return SLVCOM_ERR_NOT_SUPPORTED;
  }
  else if(slvcom_info.inited == FALSE)
  {
    SLVCOM_LOG_ERR(0, "SLVCOM is not initialized!");
    return SLVCOM_ERR_NOT_INITIALIZED;
  }
  
  /* Increment counts */
  slvcom_os_mutex_lock(&slvcom_info.mutex);
  
  count = slvcom_info.secmode_total_count++;
  client->enabled_secmode++;
  
  if(count == 0)
  {
    err = slvcom_gpio_out(slvcom_info.gpio_tz_ns_handle, SLVCOM_GPIO_ENSECMODE_ASSERTION);
    if (err != SLVCOM_ERR_NONE)
    {
      SLVCOM_LOG_FATAL(1, "slvcom_gpio_out failed! err=%d", err);
    }
  }

  slvcom_os_mutex_unlock(&slvcom_info.mutex);
  
  return SLVCOM_ERR_NONE;
#else
  return SLVCOM_ERR_NOT_SUPPORTED;
#endif
}

/*=============================================================================
  FUNCTION  slvcom_secmode_disable
=============================================================================*/
/**
 * THIS API IS ONLY AVAILABLE IN THE TZ
 *
 * Makes the NS(S=Secure) to Active high to indicate SECURE(TZ) communication
 * mode is *not* active.
 *
 * @param[in]  handle         Client handle return by slvcom_open()..
 *
 * @return
 * SLVCOM_ERR_NONE if function is successful,
 * Otherwise returns error code (see slvcom_err_type enumeration).
 */
/*===========================================================================*/
slvcom_err_type slvcom_secmode_disable(slvcom_handle_type handle)
{
#if defined(SLVCOM_FEATURE_SECMODE_SUPPORT)
  slvcom_err_type err;
  uint32 count;
  slvcom_client_type *client = (slvcom_client_type *)handle;
  
  if (slvcom_info.inited == FALSE && slvcom_info.target_no_support == TRUE)
  {
    SLVCOM_LOG_ERR(0, "SLVCOM is not supported!");
    return SLVCOM_ERR_NOT_SUPPORTED;
  }
  else if(slvcom_info.inited == FALSE)
  {
    SLVCOM_LOG_ERR(0, "SLVCOM is not initialized!");
    return SLVCOM_ERR_NOT_INITIALIZED;
  }
  
  /* Decrement counts */
  slvcom_os_mutex_lock(&slvcom_info.mutex);
  
  /* Check if this client actually enabled or not */
  if(client->enabled_secmode == 0)
  {
    slvcom_os_mutex_unlock(&slvcom_info.mutex);
    SLVCOM_LOG_ERR(1, "This client didnt enable secmode to disable. handle: 0x%x", handle);
    return SLVCOM_ERR_INVALID_SECMODE_ERR;
  }
  client->enabled_secmode--;
  count = --slvcom_info.secmode_total_count;
  
  if(count == 0)
  {
    err = slvcom_gpio_out(slvcom_info.gpio_tz_ns_handle, SLVCOM_GPIO_DISSECMODE_ASSERTION);
    if (err != SLVCOM_ERR_NONE)
    {
      SLVCOM_LOG_FATAL(1, "slvcom_gpio_out failed! err=%d", err);
    }
    slvcom_spi_sleep();
    slvcom_info.state = SLVCOM_STATE_SLEEP;
  }

  slvcom_os_mutex_unlock(&slvcom_info.mutex);
  
  return SLVCOM_ERR_NONE;
#else
  return SLVCOM_ERR_NOT_SUPPORTED;
#endif
}
