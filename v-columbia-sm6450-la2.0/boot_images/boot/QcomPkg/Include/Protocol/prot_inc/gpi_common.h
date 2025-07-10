#ifndef __GPI_COMMON_H__
#define __GPI_COMMON_H__

/**
  @file  gpi_common.h
  @brief GPI public data structures and APIs.

*/
/*
===============================================================================

Edit History

$Header:

when       who     what, where, why
--------   ---     ------------------------------------------------------------
02/26/20   da      Initial

===============================================================================
              Copyright (c) 2020 QUALCOMM Technologies, Inc.
                         All Rights Reserved.
            Qualcomm Technologies Proprietary and Confidential.
===============================================================================
*/

/* *********************************************************************************************** */
/*                                         DEFINITIONS                                             */
/* *********************************************************************************************** */

typedef unsigned long  U_LONG;

#define RESERVED_VALUE                                0xFFFF

/* *********************************************************************************************** */
/*                                       DATA STRUCTURES                                           */
/* *********************************************************************************************** */

/* GSI HW Instance */
typedef enum
{
   QUP_0   = 0,
   QUP_1   = 1,
   QUP_2   = 2,
   QUP_SSC = 99
}QUP_BLOCK_TYPE;

/** @name GPI Channel Command Type */
typedef enum
{
   GPI_CHAN_CMD_ALLOCATE      = 0,   /* Request channel allocation    */
   GPI_CHAN_CMD_START         = 1,   /* Request channel start         */
   GPI_CHAN_CMD_STOP          = 2,   /* Request channel stop          */
   GPI_CHAN_CMD_RESET         = 9,   /* Request channel reset         */
   GPI_CHAN_CMD_DE_ALLOC      = 10,  /* Request channel de-allocation */
   GPI_CHAN_CMD_DB_STOP       = 11,  /* Request channel doorbell stop */

   /* Async commands */
   /* generic (starts from 0x10) */
   QUP_CMD_GSI_STOP_ON_EOT    = 16,  /* Stop channel when current transfer is finished              */

   /* protocol specific (starts from 0x20) */
   QUP_CMD_UART_SW_STALE      = 32,  /* Force UART RX channel flush all its data and close transfer */
   QUP_CMD_UART_RFR_READY     = 33,  /* Set RFR signal to "ready" state                             */
   QUP_CMD_UART_RFR_NOT_READY = 34,  /* Set RFR signal to "not ready" state                         */
   QUP_CMD_UART_BREAK_START   = 35,  /* Initiate RX-break condition on TX channel                   */
   QUP_CMD_UART_BREAK_STOP    = 36,  /* Finish RX-break condition on TX channel                     */

   /* GENERIC_CMD_IBI (starts from 0x90), local definitions not in HPG */
   GENERIC_CMD_IBI            = 144,

   GPI_CHAN_CMD_NONE          = 0xFF
}GPI_CHAN_CMD;


/** @name GPI Channel State */
typedef enum
{
   GPI_CHAN_DISABLED      = 0,
   GPI_CHAN_ALLOCATED     = 1,
   GPI_CHAN_RUNNING       = 2,
   GPI_CHAN_STOPPED       = 3,
   GPI_CHAN_STOP_IN_PROG  = 4,
   GPI_CHAN_ERROR         = 15
}GPI_CHAN_STATE;

/** @name GPI Ring Element */
typedef PACKED struct _gpi_ring_elem
{
   UINT32 dword_0;
   UINT32 dword_1;
   UINT32 dword_2;
   UINT32 ctrl;
}gpi_ring_elem;

/** @name GPI Execution Env */
typedef enum
{
   GPI_SDC_EE   = 0x0,
   GPI_SSC_EE   = 0x1,
   GPI_MSS_EE   = 0x2,
   GPI_ADSP_EE  = 0x3,
   GPI_BOOT_EE  = 0x4,
   GPI_TZ_EE    = 0x5,
   GPI_APPS_EE  = 0x6,

   GPI_EXEC_ENV_MAX
}GPI_EXEC_ENV;

/** @name GPI protocol Type */
typedef enum
{
   GPI_SPI_PROTOCOL   = 1,
   GPI_UART_PROTOCOL  = 2,
   GPI_I2C_PROTOCOL   = 3,
   GPI_I3C_PROTOCOL   = 4,

   GPI_MAX_PROTOCOL
}GPI_PROTOCOL;

#define GSI_CHAN_PER_GPII     2

/** @name Channel Type */
typedef enum
{
   GPI_OUTBOUND_CHAN = 0,
   GPI_INBOUND_CHAN  = 1,
   GPI_EVT_RING      = 2
}GPI_CHAN_TYPE;

/** @name TRE Type - combination of Majo/Minor types */
typedef enum
{
   GPI_TRE_INVALID       = 0,
   GPI_TRE_NOOP          = 1,
   /* DMA */
   GPI_TRE_DMA_W_BUFFER  = 16,
   GPI_TRE_DMA_TX_IMM    = 17,
   GPI_TRE_DMA_W_SGL     = 18,
   /* SPI - UART - I2C */
   GPI_TRE_GO            = 32,
   GPI_TRE_CONFIG_0      = 34,
   GPI_TRE_CONFIG_1      = 35,
   GPI_TRE_CONFIG_2      = 36,
   GPI_TRE_CONFIG_3      = 37,
   /* Lock */
   GPI_TRE_LOCK          = 48,
   GPI_TRE_UNLOCK        = 49
}GPI_TRE_TYPE;

/** @name SPI GO Command Type */
typedef enum
{
   GPI_SPI_GO_CMD_INVALID      = 0,
   GPI_SPI_GO_CMD_TX_ONLY      = 1,
   GPI_SPI_GO_CMD_RX_ONLY      = 2,
   GPI_SPI_GO_CMD_FULL_DUPLEX  = 3,
   GPI_SPI_GO_CMD_TX_RX        = 7,
   GPI_SPI_GO_CMD_CS_ASSERT    = 8,
   GPI_SPI_GO_CMD_CS_DEASSERT  = 9,
   GPI_SPI_GO_CMD_SCK_ONLY     = 10
}GPI_SPI_GO_CMD_TYPE;

/** @name UART GO Command Type */
typedef enum
{
   GPI_UART_GO_CMD_INVALID      = 0,
   GPI_UART_GO_CMD_START_TRANS  = 1,
   GPI_UART_GO_CMD_START_BREAK  = 8,
   GPI_UART_GO_CMD_STOP_BREAK   = 9,
   GPI_UART_GO_CMD_RESET_RFR_N  = 10,
   GPI_UART_GO_CMD_SET_RFR_N    = 11,
   GPI_UART_GO_CMD_SW_RX_STALE  = 12
}GPI_UART_GO_CMD_TYPE;

/** @name I2C GO Command Type */
typedef enum
{
   GPI_I2C_GO_CMD_TX_ONLY       = 1,
   GPI_I2C_GO_CMD_RX_ONLY       = 2,
   GPI_I2C_GO_CMD_TX_THEN_RX    = 3,
   GPI_I2C_GO_CMD_TX_ADDR_ONLY  = 4,
   GPI_I2C_GO_CMD_BUS_CLEAR     = 6,
   GPI_I2C_GO_CMD_STOP_ONLY     = 7,
}GPI_I2C_GO_CMD_TYPE;

/** @name I3C GO Command Type */
typedef enum
{
   GPI_I3C_GO_CMD_PRIVATE_WRITE         = 9,
   GPI_I3C_GO_CMD_PRIVATE_READ          = 10,
   GPI_I3C_GO_CMD_HDR_DDR_WRITE         = 11,
   GPI_I3C_GO_CMD_HDR_DDR_READ          = 12,
   GPI_I3C_GO_CMD_DIRECT_CCC_ADDR_ONLY      = 13,
   GPI_I3C_GO_CMD_BROADCAST_CCC_ADDR_ONLY   = 14,
   GPI_I3C_GO_CMD_READ_IBI              = 15,
   GPI_I3C_GO_CMD_BROADCAST_CCC_WRITE   = 16,
   GPI_I3C_GO_CMD_DIRECT_CCC_WRITE      = 17,
   GPI_I3C_GO_CMD_DIRECT_CCC_READ       = 18,
}GPI_I3C_GO_CMD_TYPE;

/** @name GPI status return */
typedef enum
{
   GPI_STATUS_SUCCESS            = 0x0,
   GPI_STATUS_ERROR              = 0x1,
   GPI_STATUS_RING_FULL          = 0x2,
   GPI_STATUS_GSI_NOT_READY      = 0x3,
   GPI_STATUS_GPII_NUM_EXCEEDED  = 0x4,
   GPI_STATUS_WP_OUT_OF_SYNC     = 0x5,
   GPI_STATUS_INVALID_CHAN       = 0x6
}GPI_RETURN_STATUS;

/* Event Ring Completion Status */
typedef enum
{
   EVT_COMPLETION_INVALID   = 0,
   EVT_COMPLETION_SUCCESS   = 1,
   EVT_COMPLETION_EOT       = 2,
   EVT_COMPLETION_OVERFLOW  = 3,
   EVT_COMPLETION_EOB       = 4,
   EVT_COMPLETION_OOB       = 5,
   EVT_COMPLETION_DB_MODE   = 6,
   EVT_COMPLETION_UNDEF     = 16,
   EVT_COMPLETION_MALFORMED = 17,

   EVT_COMPLETION_OTHER = RESERVED_VALUE
}GPI_EVT_CODE;

/* GPI Event Ring Element Type */
typedef enum
{
   EVT_STATE_CHANGE         = 32,
   EVT_CMD_COMPLETION       = 33,
   EVT_XFER_COMPLETION      = 34,
   EVT_IMM_CMD_COMPLETION   = 35,
   EVT_IMM_DATA             = 48,
   EVT_QUP_NOTIF            = 49,
   EVT_I3C_IBI_OWN_CHG      = 50,
   EVT_I3C_IBI_REC          = 51,
   EVT_EE_STATE_CHANGE      = 64,

   GPI_EVT_OTHER            = 0xFF
} GPI_EVT_TYPE;

/* GPI Event Ring Element Type */
typedef enum
{
   /* Global error */
   GPI_ERROR_GLOBAL         = 0,

   /* General errors */
   BREAK_POINT              = 1,
   BUS_ERROR                = 2,
   CMD_FIFO_OVRFLOW         = 3,
   MCS_STACK_OVRFLOW        = 4,

   GPI_ERROR_OTHER          = 0xFF
} GPI_ERROR_TYPE;

/** @name GPI debug registers
 *  
 */
typedef struct _gpi_debug_regs
{
   U_LONG irq_type;
   U_LONG GSI_CH_IRQ;
   U_LONG EV_CH_IRQ;
   U_LONG GLOB_IRQ_STTS;
   U_LONG IEOB_IRQ;
   U_LONG INTER_EE_GSI_CH_IRQ;
   U_LONG INTER_EE_EV_CH_IRQ;
   U_LONG GSI_IRQ_STTS;
   U_LONG ERROR_LOG;
   U_LONG DEBUG_PC;
   U_LONG CH_0_CNTXT;
   U_LONG CH_1_CNTXT;
   U_LONG CH_0_SCRATCH_0;
   U_LONG CH_1_SCRATCH_0;
   U_LONG R_0_LEN;
   U_LONG R_1_LEN;
   U_LONG EVT_RING_RP;
   U_LONG local_rp;
   U_LONG CHAN_0_RP;
   U_LONG CHAN_0_WP;
   U_LONG CHAN_1_RP;
   U_LONG CHAN_1_WP;
   U_LONG DEBUG_SW_RF_10_READ;
   U_LONG DEBUG_SW_RF_11_READ;
   U_LONG DEBUG_SW_RF_12_READ;
   U_LONG DEBUG_SW_RF_21_READ;
}gpi_debug_regs;

/** @name GPI result
 *  chan:      Channel type: inbound, outbound, or event ring
 *  type:      type of event this result is for, if GPI_EVT_OTHER then error happened
 *  code:      Event code
 *  status:    Holds protocol specific TRE notification passed from GSI
 *  length:    if type is EVT_XFER_COMPLETION, length is the # of bytes processed
 *             if type is QUP_NOTIF_EVT, length will be the QUP Count
 *             if type is IMM_DATA_EVT, length is the Number of bytes received
 *  dword_0:   if IMM_DATA_EVT, dword_0 is the Immediate Data Bytes [3-0]
 *             if QUP_NOTIF_EVT, dword_0 is the QUP Status
 *             if CMD_COMPLETION_EVT then it represents the new chan state
 *             if GPI_EVT_OTHER, dword_0 holds the error type GPI_ERROR_TYPE
 *  dword_1:   if IMM_DATA_EVT, dword_1 is the Immediate Data Bytes [7-4]
 *             if QUP_NOTIF_EVT, dword_1 is the Timestamp
 *             if GPI_EVT_OTHER and dword_0 is GPI_ERROR_GLOBAL, dword_1 holds the error value
 *  user_data: user context
 */
typedef struct _gpi_result_type
{
   GPI_CHAN_TYPE    chan;
   GPI_EVT_TYPE     type;
   GPI_EVT_CODE     code;
   UINT32           status;
   UINT32           length;
   UINT32           tre_idx;
   UINT32           dword_0;
   UINT32           dword_1;
   void *           user_data;
}gpi_result_type;

/** Ring info provided by clients.
 *  Clients allocate their respective channel TRE rings tailored to their specific needs.
 *  NOTE: clients should not allocate more than the size MAX_NUM_GPI_RING_ELEM defined above,
 *        due to memory restrictions.
 *
 *  tre_ring_size: Number of TRE's per ring
 *  ring_base_pa:  Physical address of the TRE ring base
 *  ring_base_va:  Virtual address of the TRE ring base
 */
typedef struct _gpi_tre_ring
{
   UINT8         tre_ring_size;
   U_LONG      ring_base_pa;
   U_LONG      ring_base_va;
}gpi_tre_ring;

/** @name GPI Handle */
typedef void * GPI_CLIENT_HANDLE;

/** @name Client callback signature */
typedef void(*client_cb)(gpi_result_type *);

/** @name GPI TRE Request */
typedef PACKED struct _gpi_tre_req
{
   GPI_CLIENT_HANDLE  handle;
   GPI_CHAN_TYPE      chan;
   gpi_ring_elem    * tre_list;
   UINT32             num_tre;
   void             * user_data;
}gpi_tre_req;

/** @name GPI interface parameters
 *
 *  [in, out] gpi_handle      GPI Interface client handle
 *  [in] gpii_id              GPI interface of this channel (from config file?)
 *  [in] protocol             SPI, UART, I2C, I3C
 *  [in] se                   SE instance
 *  [in] chan                 Inbound/Outbound channel settings
 *  [in] int_modt_val         Interrupt moderation timer value (optional)
 *  [in] int_modc_val         Interrupt moderation counter value (optional)
 *  [in] irq_mode             GPII in irq mode if true, otherwise polling
 *  [in] cb                   Callback function for tre requests
 *  [in] user_data            To be included in results passed to clients in non-transfer callbacks
 */
typedef struct _gpi_iface_params
{
   GPI_CLIENT_HANDLE  gpi_handle;
   UINT8              gpii_id;
   QUP_BLOCK_TYPE     qup_type;
   GPI_PROTOCOL       protocol;
   UINT8              se;
   gpi_tre_ring       chan[GSI_CHAN_PER_GPII];
   UINT32             int_modt_val;
   UINT32             int_modc_val;
   BOOLEAN            irq_mode;
   client_cb          cb;
   void             *user_data;
}gpi_iface_params;

/** @name Channel status
 *
 *  num_avail_tre     Number of available TRE's
 *  rp_index          RP index, 0..(tre_ring_size - 1)
 *  wp_index          WP index, 0..(tre_ring_size - 1)
 *  chan_state        Channel current state
 */
typedef struct _chan_status_info
{
   UINT8  num_avail_tre;
   UINT8  rp_index;
   UINT8  wp_index;
   GPI_CHAN_STATE  chan_state;
}chan_status_info;

typedef struct _gpi_sgl_elem
{
    UINT32 PTR_31_00;
    UINT32 PTR_63_32;
    UINT32 length;
    UINT32 rsvd;
} gpi_sgl_elem;

#endif /* __GPI_COMMON_H__ */
