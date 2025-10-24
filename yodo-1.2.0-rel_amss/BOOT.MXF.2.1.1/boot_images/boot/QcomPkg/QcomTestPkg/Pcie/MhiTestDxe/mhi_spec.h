#ifndef MHI_SPEC_H
#define MHI_SPEC_H
/**
 *  @file mhi_spec.h
 *
 *  @brief This file contains the interface for elements defined in the MHI specification.
 */
/*============================================================================
               Copyright (c) 2021 Qualcomm Technologies, Inc.
               All Rights Reserved.
               Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/

 /* *****************************************************
 * MHI SPEC DATA Structres                            *
 * ****************************************************/
#include "comdef.h"

#define RING_EL_SIZE 16

#define MAX_NUM_CHANS 128

#define MHI_MIN_TRANSFER_SIZE 1
#define MHI_MAX_TRANSFER_SIZE 65535

#define CHAN_IS_INBOUND(ch_id) ((ch_id) & 0x1)

/** MHI Channel States */
typedef enum _mhi_ch_state
{
  MHI_CH_STATE_DISABLED=0x0,        /**< Channel is disabled. This is the reset state */
  MHI_CH_STATE_ENABLED=0x1,         /**< Channel is enabled. Doorbells can be processed */
  MHI_CH_STATE_RUNNING=0x2,         /**< Channel is running. */
  MHI_CH_STATE_SUSPENDED=0x3,       /**< Channel is suspended */
  MHI_CH_STATE_STOPPED=0x4,         /**< Channel is stopped using channel stop command */
  MHI_CH_STATE_ERROR=0x5,           /**< Channel error has occurred */
  MHI_CH_STATE_MAX,                 /**< Channel state max */
  _MHI_CH_STATE_I32=0x7fffffff,     /**< Force enum size to 32-bit */
}mhi_ch_state_t;

/** MHI Channel Type */
typedef enum _mhi_ch_type
{
   MHI_CH_TYPE_INVALID=0x0,         /**< Channel is not valid */
   MHI_CH_TYPE_OUTBOUND=0x1,        /**< Outbound channel (host to device) */
   MHI_CH_TYPE_INBOUND=0x2,         /**< Inbound channel (device to host) */
   MHI_CH_TYPE_MAX,                 /**< Channel type max */
   _MHI_CH_TYPE_I32=0x7fffffff,     /**< Force enum size to 32-bit */
}mhi_ch_type_t;

/** MHI Event Ring Type */
typedef enum _mhi_er_type
{
   MHI_ER_TYPE_NOT_VALID=0x0,       /**< Event ring not valid */
   MHI_ER_TYPE_VALID=0x1,           /**< Event ring valid */
   MHI_ER_TYPE_VALID_EXTENDED=0x2,  /**< Event ring valid extended context */
   MHI_ER_TYPE_MAX,                 /**< Event ring type max size */
   _MHI_ER_TYPE_I32=0x7fffffff,     /**< Force enum size to 32-bit */
}mhi_er_type_t;

/** MHI Exec Envs */
typedef enum _mhi_exec_env
{
   MHI_EXEC_ENV_INVALID=0x0,        /** Exec env is not valid */
   MHI_EXEC_ENV_SBL_EE=0x1,         /** SBL EE */
   MHI_EXEC_ENV_AMSS_EE=0x2,        /** AMSS EE */
   MHI_EXEC_ENV_RDDM_EE=0x3,        /** RDDM EE */
   MHI_EXEC_ENV_MAX,                /** Exec env max */
   _MHI_EXEC_ENV_I32=0x7fffffff,    /**< Force enum size to 32-bit */
}mhi_exec_env_t;

typedef enum _mhi_ctxt_type
{
   MHI_CTXT_TYPE_CHAN=0x0,
   MHI_CTXT_TYPE_EVENT=0x1,
   MHI_CTXT_TYPE_MAX,
   _MHI_CTXT_TYPE_I32=0x7fffffff,
}mhi_ctxt_type_t;

/** Channel Context */
typedef PACKED struct PACKED_POST _mhi_ch_ctx
{
   mhi_ch_state_t chstate;  /**< Channel state. See mhi_ch_state_t type */
   mhi_ch_type_t  chtype;   /**< Channel type. see mhi_ch_type_t type */
   uint32         erindex;  /**< Index number of event ring associated with channel */
   uint64         rbase;    /**< Ring address pointer of the ring associated with channel */
   uint64         rlen;     /**< Ring length in bytes. Must be a multiple of ring element size */
   uint64         rp;       /**< Read pointer to 64-bit address in host space */
   uint64         wp;       /**< Write pointer to 64-bit address in host space */
}mhi_ch_ctx_t;

/** Event Context */
typedef PACKED struct PACKED_POST _mhi_ev_ctx
{
   uint32 res:8;           /**< Reserved */
   uint32 intmodc:8;       /**< Interrupt moderation counter */
   uint32 intmodt:16;      /**< Interrupt moderation timer */
   mhi_er_type_t ertype;   /**< Event ring type. Identifies if the event ring context is valid */
   uint32 msivec;          /**< MSI Vector associated with the event ring */
   uint64 rbase;           /**< Base address pointer of the event ring */
   uint64 rlen;            /**< Size of the ring (in bytes). Total size must be multiple of event ring element size */
   uint64 rp;              /**< Ring read pointer */
   uint64 wp;              /**< Ring write pointer */
}mhi_ev_ctx_t;

/** Extended event context with IPCC support */
typedef PACKED struct PACKED_POST _mhi_ev_ctx_ex
{
   mhi_ev_ctx_t ev_ctxt;   /**< Base event context structure */
   uint64 ippc_addr;       /**< IPCC address */
   uint32 ipcc_data;       /**< IPCC data */
}mhi_ev_ctx_ex_t;

/** Command Ring Context */
typedef PACKED struct PACKED_POST _mhi_cr_ctx
{
   uint32 res;     /**< Reserved */
   uint32 res1;    /**< Reserved */
   uint32 res2;    /**< Reserved */
   uint64 rbase;   /**< Base address of command ring */
   uint64 rlen;    /**< Size of the ring (in bytes). Total size must be multiple of command ring element size */
   uint64 rp;      /**< Command ring read pointer */
   uint64 wp;      /**< Command ring write pointer */
}mhi_cr_ctx_t;

/** Generic Context */
typedef PACKED struct PACKED_POST _mhi_generic_ctx
{
   uint32 res;             /**< Reserved */
   uint32 res1;            /**< Reserved */
   uint32 res2;            /**< Reserved */
   uint64 rbase;           /**< Base address pointer of the event ring */
   uint64 rlen;            /**< Size of the ring (in bytes). Total size must be multiple of event ring element size */
   uint64 rp;              /**< Ring read pointer */
   uint64 wp;              /**< Ring write pointer */
}mhi_generic_ctx_t;

/** Union of possible contexts (CR, ER, and CH)  */
typedef PACKED union PACKED_POST _mhi_ring_ctx
{
   mhi_cr_ctx_t        cmd;    /**< Command context */
   mhi_ev_ctx_t         ev;    /**< Event Context */
   mhi_ch_ctx_t         ch;    /**< Channel Context */
   mhi_generic_ctx_t   gen;    /**< Generic context */
   mhi_ev_ctx_ex_t   ev_ex;    /**< Extended event context */
}mhi_ring_ctx_t;

/** Ring Element Types */
typedef enum  _mhi_r_el_type
{
   MHI_RING_EL_TYPE_RESERVED=0,                /**< Reserved type */
   MHI_RING_EL_TYPE_NOOP=1,                    /**< No op */
   MHI_RING_EL_TYPE_TRANSFER=2,                /**< Transfer */
   MHI_RING_EL_TYPE_RESET_CH_CMD=16,           /**< Reset Channel command */
   MHI_RING_EL_TYPE_STOP_CH_CMD=17,            /**< Stop channel command */
   MHI_RING_EL_TYPE_START_CH_CMD=18,           /**< Start channel command */
   MHI_RING_EL_TYPE_START_ALL_CHS_CMD=20,      /**< Start all channels command */
   MHI_RING_EL_TYPE_STOP_ALL_CHS_CMD=21,       /**< Stop all channels command */
   MHI_RING_EL_TYPE_MHI_STATE_CHG=32,          /**< MHI state change notification */
   MHI_RING_EL_TYPE_MHI_CMD_COMPLETE_EVENT=33, /**< Command completion event */
   MHI_RING_EL_TYPE_TRANSFER_EVENT=34,         /**< Transfer event */
   MHI_RING_EL_TYPE_EXEC_ENV_CHG=64,           /**< Execution environment state change notification */
   MHI_RING_EL_TYPE_CTX_UPDATE_CMD=100,        /**< Context update command */
   MHI_RING_EL_TYPE_MAP_IO_CMD=101,            /**< Map IO command */
   MHI_RING_EL_TYPE_CONFIG_EVT=110,            /**< Config event */
   MHI_RING_EL_TYPE_SYS_ERR_CMD=255,           /**< System error command */
   _MHI_RING_EL_TYPE_I32=0x7fffffff,           /**< Force enum size to 32-bit */
}mhi_ring_el_t;

/** Completion codes */
typedef enum _mhi_cmd_complete_code
{
   MHI_CMD_CODE_INVALID=0,                  /**< Undefined completion code */
   MHI_CMD_CODE_SUCCESS=1,                  /**< Successful completion of the operation */
   MHI_CMD_CODE_EOT=2,                      /**< Successful completion of the transfer operation, but less bytes were
                                                   transferred from device to host than requested by TD */
   MHI_CMD_CODE_OVERFLOW=3,                 /**< Overflow completion code indicates transfer unit could not be contained
                                                 in a single TD. Applies only to inbound channels */
   MHI_CMD_CODE_EOB=4,                      /**< End of Block. Successful completion of operation and EOB condition encountered */
   MHI_CMD_CODE_UNDEFINED_ERR=16,           /**< Generic error code used by the device when other code does not apply */
   MHI_CMD_CODE_RING_EL_ERROR=17,           /**< Ring element parameter error condition */
   _MHI_CMD_CODE_I32=0x7fffffff,            /**< Force enum size to 32-bit */
}mhi_cmd_complete_code_t;

/** Ring elements **************************************/

/** Transfer Ring Element structure */
typedef PACKED struct PACKED_POST _mhi_tr_element_t
{
    uint64 ptr;                            /**< Pointer to TRB */
    uint32 len:16;                         /**< Length of buffer */
    uint32 res:16;                         /**< RESERVED */
    uint32 chain:1;                        /**< Chain bit */
    uint32 res1:7;                         /**< RESERVED */
    uint32 ieob:1;                         /**< Interrupt on end of block */
    uint32 ieot:1;                         /**< Interrupt on end of transfer */
    uint32 bei:1;                          /**< Block event interrupt */
    uint32 res2:5;                         /**< RESERVED */
    mhi_ring_el_t type:8;                  /**< Ring element type */
    uint32 res3:8;                         /**< RESERVED */
}mhi_tr_element_t;

/** Noop command */
typedef PACKED struct PACKED_POST _mhi_noop_cmd_element
{
    uint64 res;                            /**< RESERVED */
    uint32 res1;                           /**< RESERVED */
    uint32 res2:16;                        /**< RESERVED */
    mhi_ring_el_t type:8;                  /**< Ring element type */
    uint32 res3:8;                         /**< RESERVED */
}mhi_noop_cmd_element_t;

/** Reset channel command */
typedef PACKED struct PACKED_POST _mhi_reset_cmd_element
{
    uint64 res;                            /**< RESERVED */
    uint32 res1;                           /**< RESERVED */
    uint32 res2:16;                        /**< RESERVED */
    mhi_ring_el_t type:8;                  /**< Ring element type */
    uint32 chid:8;                         /**< Channel ID */
}mhi_reset_cmd_element_t;

/** Stop channel command */
typedef PACKED struct PACKED_POST _mhi_stop_cmd_element
{
    uint64 res;                            /**< RESERVED */
    uint32 res1;                           /**< RESERVED */
    uint32 res2:16;                        /**< RESERVED */
    mhi_ring_el_t type:8;                  /**< Ring element type */
    uint32 chid:8;                         /**< Channel ID */
}mhi_stop_cmd_element_t;

/** Start channel command */
typedef PACKED struct PACKED_POST _mhi_start_cmd_element
{
    uint64 res;                            /**< RESERVED */
    uint32 seqnum;                         /**< Sequence number */
    uint32 reliable:1;                     /**< Reliable */
    uint32 res2:15;                        /**< RESERVED */
    mhi_ring_el_t type:8;                  /**< Ring element type */
    uint32 chid:8;                         /**< Channel ID */
}mhi_start_cmd_element_t;

/** Start all channels command */
typedef PACKED struct PACKED_POST _mhi_start_all_cmd_element
{
    uint64 res;                            /**< RESERVED */
    uint32 res1;                           /**< RESERVED */
    uint32 res2:16;                        /**< RESERVED */
    mhi_ring_el_t type:8;                  /**< Ring element type */
    uint32 res3:8;                         /**< RESERVED */
}mhi_start_all_cmd_element_t;

/** Stop all channels command */
typedef PACKED struct PACKED_POST _mhi_stop_all_cmd_element
{
    uint64 res;                            /**< RESERVED */
    uint32 res1;                           /**< RESERVED */
    uint32 res2:16;                        /**< RESERVED */
    mhi_ring_el_t type:8;                  /**< Ring element type */
    uint32 res3:8;                         /**< RESERVED */
}mhi_stop_all_cmd_element_t;

/** Context update command */
typedef PACKED struct PACKED_POST _mhi_ctx_update_cmd_element
{
    uint64 ptr;                            /**< Pointer to context */
    uint32 size;                           /**< Size of context */
    mhi_ctxt_type_t ctxt_type:1;           /**< Context type */
    uint32 res2:15;                        /**< RESERVED */
    mhi_ring_el_t type:8;                  /**< Ring element type */
    uint32 id:8;                           /**< Context ID  */
}mhi_ctx_update_cmd_element_t;

/** Map IO command */
typedef PACKED struct PACKED_POST _mhi_map_io_cmd_element
{
    uint64 pa;                             /**< Physical address to map */
    uint32 size;                           /**< Size of memory region */
    uint32 res2:16;                        /**< RESERVED */
    mhi_ring_el_t type:8;                  /**< Ring element type */
    uint32 res3:8;                         /**< RESERVED */
}mhi_map_io_cmd_element_t;

/** Config event */
typedef PACKED struct PACKED_POST _mhi_config_evt_element_t
{
    uint64 bar;                            /**< BAR address */
    uint32 num_er:16;                      /**< Number of event rings */
    uint32 er_base_idx:16;                 /**< Event ring base index per EE */
    uint32 res2:16;                        /**< RESERVED */
    mhi_ring_el_t type:8;                  /**< Ring element type */
    uint32 res3:8;                         /**< RESERVED */
}mhi_config_evt_element_t;

/** Transfer Completion Event */
typedef PACKED struct PACKED_POST _mhi_transfer_event_element
{
   uint64 ptr;                             /**< Pointer to TRE (Transfer Ring Element ) */
   uint32 len:16;                          /**< Length of transfer */
   uint32 res:8;                           /**< RESERVED */
   mhi_cmd_complete_code_t code:8;         /**< Event code */
   uint32 res1:16;                         /**< RESERVED */
   mhi_ring_el_t type:8;                   /**< Ring element type */
   uint32 chid:8;                          /**< Channel ID */
}mhi_transfer_event_element_t;

/** Command Completion Event  */
typedef PACKED struct PACKED_POST _mhi_cmd_complete_event
{
   uint64 ptr;                            /**< Pointer to CRE (Command Ring Element ) */
   uint32 res:24;                         /**< RESERVED */
   mhi_cmd_complete_code_t code:8;        /**< Event code */
   uint32 res1:16;                        /**< RESERVED */
   mhi_ring_el_t type:8;                  /**< Ring element type */
   uint32 res2:8;                         /**< RESERVED */
}mhi_cmd_complete_event_t;

/** MHI State Change Event  */
typedef PACKED struct PACKED_POST _mhi_state_chg_event
{
   uint64 res;                            /**< RESERVED */
   uint32 res1:24;                        /**< RESERVED */
   mhi_state_t mhistate:8;                /**< MHI state */
   uint32 res2:16;                        /**< RESERVED */
   mhi_ring_el_t type:8;                  /**< Ring element type */
   uint32 res3:8;                         /**< RESERVED */
}mhi_state_chg_event_t;

/** Execution Environment (EE) Change Event  */
typedef PACKED struct PACKED_POST _mhi_exec_env_chg_event
{
   uint64 res;                            /**< RESERVED */
   uint32 res1:24;                        /**< RESERVED */
   uint32 exec_env:8;                     /**< Execution environment */
   uint32 res2:16;                        /**< RESERVED */
   mhi_ring_el_t type:8;                  /**< Ring element type */
   uint32 res3:8;                         /**< RESERVED */
}mhi_exec_env_chg_event_t;

/** System Error Command */
typedef PACKED struct PACKED_POST _mhi_sys_err_cmd_element
{
   uint64 res;                            /**< RESERVED */
   uint32 res1;                           /**< RESERVED */
   uint32 res2:16;                        /**< RESERVED */
   mhi_ring_el_t type:8;                  /**< Ring element type */
   uint32 res3:8;                         /**< RESERVED */
}mhi_sys_err_cmd_element_t;

/** Generic Ring Element structure. Used to determine ring type */
typedef PACKED struct PACKED_POST _mhi_generic_element
{
    uint64 res;                           /**< RESERVED */
    uint32 res1;                          /**< RESERVED */
    uint32 res2:16;                       /**< RESERVED */
    mhi_ring_el_t type:8;                 /**< Ring element type */
    uint32 res3:8;                        /**< RESERVED */
}mhi_generic_element_t;

/** Generic ring element used for logging */
typedef PACKED struct PACKED_POST
{
    uint64 part1;                         /**< Part 1 */
    uint32 part2;                         /**< Part 2 */
    uint32 part3;                         /**< Part 3 */
}mhi_log_element_t;

/** Union of possible ring elements */
typedef PACKED union PACKED_POST _mhi_ring_element
{
    mhi_tr_element_t               tr;                /**< Transfer Ring element */
    mhi_noop_cmd_element_t         cmdNoop;           /**< No-op command element */
    mhi_reset_cmd_element_t        cmdReset;          /**< Reset command element */
    mhi_stop_cmd_element_t         cmdStop;           /**< Stop command element */
    mhi_start_cmd_element_t        cmdStart;          /**< Start command element */
    mhi_start_all_cmd_element_t    cmdStartAll;       /**< Start all command element */
    mhi_stop_all_cmd_element_t     cmdStopAll;        /**< Stop all command element */
    mhi_ctx_update_cmd_element_t   cmdCtxUpdate;      /**< Context update command element */
    mhi_map_io_cmd_element_t       cmdMapIo;          /**< Map IO command element */
    mhi_config_evt_element_t       evtConfig;         /**< Config event element */
    mhi_transfer_event_element_t   tEvent;            /**< Transfer Completion event   */
    mhi_cmd_complete_event_t       cmdCompleteEvent;  /**< Command completion event */
    mhi_state_chg_event_t          stateChgEvent;     /**< State change event */
    mhi_exec_env_chg_event_t       exec_env_ChgEvent; /**< Execution Environment state change event */
    mhi_sys_err_cmd_element_t      sysErr;            /**< System error command element */
    mhi_generic_element_t          rel;               /**< Generic ring element */
}mhi_ring_element_t;

/** MHI Memory allocations */
typedef PACKED struct PACKED_POST _mhi_host_addr
{
   uint64 mhictrlbase;  /**< Base address of memory region in host address space where control data structures reside */
   uint64 mhictrllimit; /**< Upper limit of ctrl address space */
   uint64 mhidatabase;  /**< Base address of region in host address space where MHI data buffers reside */
   uint64 mhidatalimit; /**< Upper limit of data region */
}mhi_host_addr_t;

typedef enum  _mhictrl_int_status
{
   MHI_CTRL_CLEAR=0x0,                              /**< MHI Control Clear */
   MHI_CTRL_INT=0x1,                                /**< MHI Control Interrupt set */
   MHI_CRDB_INT=0x2,                                /**< MHI Command Ring Doorbell Interrupt Set */
   _MHI_CTRL_INT_STS_I32=0x7fffffff,                /**< Force enum size to 32-bit */
}mhictrl_int_status;

typedef union _mhi_interrupts
{
  mhictrl_int_status ctrl;                          /**< Control interrupts */
  uint32 chdb[4];                                   /**< Channel doorbell interrupt mask */
  uint32 erdb[4];                                   /**< Event doorbell interrupt mask */
}mhi_interrupts_t;

#endif

