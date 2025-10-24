#ifndef BOOT_SAHARA_INTERNAL_H
#define BOOT_SAHARA_INTERNAL_H

/*=============================================================================

                               Boot Sahara
                               Header File
GENERAL DESCRIPTION
  This file provides the APIs to enter the Sahara Protocol.
  
EXTERNALIZED FUNCTIONS
  
INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright 2010-2014,2017, 2020-2022 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
02/11/22   rama    Support for enabling sahara logging feature
04/28/21   rhy     Changed boot_sahara_asynch_read to boot_sahara_read
02/09/21   ck      Corrected image_id type in boot_sahara_data
12/11/20   rhy     Added SAHARA_STATE_RESET_RCVD_WITH_STATUS_EQ_ERR to pass error to upper layers
11/22/20   rhy     Moved boot_sahara_status to boot_sahara.h and added boot_sahara_get_status()
09/25/20   rhy     Removed boot_sahara_mem_debug_tbl. Added boot_sahara_mem_debug_handle
05/15/20   rhy     Moved boot sahara dispatch tbl to boot_sahara
01/12/20   rhy     intial revision


=============================================================================*/

/*===========================================================================
 
                           INCLUDE FILES

===========================================================================*/
#include "MIprogressive.h"
#include "boot_elf_header.h"
#include "boot_error_if.h"
#include "boot_sahara_command_handler_if.h"
#include "boot_ramdump_table_if.h"

/*===========================================================================

                      PUBLIC DATA DECLARATIONS

===========================================================================*/

/* Sahara Protocol Version */
#define SAHARA_VERSION_MAJOR 2
#define SAHARA_VERSION_MAJOR_SUPPORTED 1
#define SAHARA_VERSION_MINOR 5

#define SAHARA_MAX_PACKET_SIZE_IN_BYTES 0x400
#define SAHARA_MAX_CMD_TEMP_DATA_RESP_BUF_IN_BYTES 0x08
#define SAHARA_MAX_MEMORY_DATA_SIZE_IN_BYTES 0x1000

/* Sahara Interface Version */
#define SAHARA_INTERFACE_VERSION 0x00010000
#define SAHARA_INTERFACE_DISPATCH_VERSION  0x00010002
#define SAHARA_INTERFACE_AUTH_VERSION      0x00010000
#define SAHARA_INTERFACE_MEMDEBUG_VERSION  0x00010000

/* Sahara V1 HELLO and HELLO_RESP packet lengths in bytes */
#define SAHARA_PACKET_HELLO_LENGTH_V1      0x14
#define SAHARA_PACKET_HELLO_RESP_LENGTH_V1 0x14

/* Sahara command IDs */
enum boot_sahara_cmd_id
{
  SAHARA_NO_CMD_ID                = 0x00,
  SAHARA_HELLO_ID                 = 0x01, /* sent from target to host */
  SAHARA_HELLO_RESP_ID            = 0x02, /* sent from host to target */
  SAHARA_READ_DATA_ID             = 0x03, /* sent from target to host */
  SAHARA_END_IMAGE_TX_ID          = 0x04, /* sent from target to host */
  SAHARA_DONE_ID                  = 0x05, /* sent from host to target */
  SAHARA_DONE_RESP_ID             = 0x06, /* sent from target to host */
  SAHARA_RESET_ID                 = 0x07, /* sent from host to target */
  SAHARA_RESET_RESP_ID            = 0x08, /* sent from target to host */
  SAHARA_MEMORY_DEBUG_ID          = 0x09, /* sent from target to host */
  SAHARA_MEMORY_READ_ID           = 0x0A, /* sent from host to target */
  SAHARA_CMD_READY_ID             = 0x0B, /* sent from target to host */
  SAHARA_CMD_SWITCH_MODE_ID       = 0x0C, /* sent from host to target */
  SAHARA_CMD_EXEC_ID              = 0x0D, /* sent from host to target */
  SAHARA_CMD_EXEC_RESP_ID         = 0x0E, /* sent from target to host */
  SAHARA_CMD_EXEC_DATA_ID         = 0x0F, /* sent from host to target */
  SAHARA_64_BITS_MEMORY_DEBUG_ID  = 0x10, /* sent from target to host */
  SAHARA_64_BITS_MEMORY_READ_ID   = 0x11, /* sent from host to target */
  
  /* place all new commands above this */
  SAHARA_LAST_CMD_ID,
  SAHARA_MAX_CMD_ID               = 0x7FFFFFFF /* To ensure 32-bits wide */
};

enum boot_sahara_state
{
  SAHARA_STATE_ENTRY,                // entry state
  SAHARA_STATE_WAIT_HELLO_RESP,      // waiting for HELLO before anything else
  SAHARA_STATE_WAIT_RESET,           // waiting for RESET from host
  SAHARA_STATE_WAIT_DONE,            // waiting for DONE from host
  SAHARA_STATE_WAIT_MEMORY_READ,     // waiting for MEMORY_READ packets
  SAHARA_STATE_WAIT_CMD_EXEC,        // waiting for CMD_EXEC packets from host
  SAHARA_STATE_WAIT_CMD_EXEC_DATA,   // waiting for CMD_EXEC_DATA packet from 
  SAHARA_STATE_DATA_READ_PAYLOAD,    // waiting for image transfer
  SAHARA_STATE_RESET_RCVD_WITH_STATUS_EQ_ERR,  // Return Status to upper layers if Status is bad
  SAHARA_STATE_MAX_CODE = 0x7FFFFFFF /* To ensure 32-bits wide */
};

enum boot_sahara_packet_direction
{
  SAHARA_PACKET_TRANSMIT = 0,       // Transmitting packet
  SAHARA_PACKET_RECEIVE,            // Receiving packet
  SAHARA_PACKET_MAX = 0x7FFFFFFF    // To ensure 32-bits wide
};

enum boot_ssa_length_update_state
{
  SSA_LENGTH_QUEUE = 0,          // Queue length for delayed update
  SSA_LENGTH_NO_QUEUE,           // Update length via RMB immediately
  SSA_LENGTH_FLUSH,              // Update stored length.
  SSA_LENGTH_MAX = 0x7FFFFFFF    // To ensure 32-bits wide
};

/* Status of all image transfers */
enum boot_sahara_mode
{
  SAHARA_MODE_IMAGE_TX_PENDING  = 0x0,
  SAHARA_MODE_IMAGE_TX_COMPLETE = 0x1,
  SAHARA_MODE_MEMORY_DEBUG      = 0x2,
  SAHARA_MODE_COMMAND           = 0x3,

  /* place all new commands above this */
  SAHARA_MODE_LAST,
  SAHARA_MODE_MAX = 0x7FFFFFFF
};

/* Executable commands when target is in command mode */
enum boot_sahara_exec_cmd_id
{
  SAHARA_EXEC_CMD_NOP                      = 0x00,
  SAHARA_EXEC_CMD_SERIAL_NUM_READ          = 0x01,
  SAHARA_EXEC_CMD_MSM_HW_ID_READ           = 0x02,
  SAHARA_EXEC_CMD_OEM_PK_HASH_READ         = 0x03,
  SAHARA_EXEC_CMD_SWITCH_TO_DMSS_DLOAD     = 0x04,
  SAHARA_EXEC_CMD_SWITCH_TO_STREAM_DLOAD   = 0x05,  
  SAHARA_EXEC_CMD_READ_DEBUG_DATA          = 0x06,
  SAHARA_EXEC_CMD_GET_SOFTWARE_VERSION_SBL = 0x07,
  SAHARA_EXEC_CMD_GET_COMMAND_ID_LIST      = 0x08,
  SAHARA_EXEC_CMD_GET_TRAINING_DATA        = 0x09,
  
  /* place all new commands above this */
  SAHARA_EXEC_CMD_LAST,
  SAHARA_EXEC_CMD_MAX                      = 0x7FFFFFFF
};

enum boot_sahara_image_type
{
  SAHARA_IMAGE_TYPE_BINARY = 0,     /* Binary format */
  SAHARA_IMAGE_TYPE_ELF,            /* ELF format */
  SAHARA_IMAGE_UNKNOWN = 0x7FFFFFFF /* To ensure 32-bits wide */
};

enum boot_sahara_context_flag
{
    SAHARA_CLOSE_CONTEXT =          0, /* Called from _open, _read or _readAsynch context*/
    SAHARA_OPEN_READ_ASYNCH_CONTEXT,   /* Called from _close context */
    
    SAHARA_UNKNOWN_CONTEXT =        0x7FFFFFFF
};

enum boot_sahara_is_blocking_flag
{
    SAHARA_READ_NO_BLOCKING =   0,
    SAHARA_READ_BLOCKING,
    
    SAHARA_UNKNOWN_BLOCKING =       0x7FFFFFFF
};

/*=============================================================================
  Sahara protocol packet defintions
=============================================================================*/
/* ***NOTE: all length fields are in bytes */

/* HELLO command packet type - sent from target to host
     indicates start of protocol on target side */
struct sahara_packet_hello
{
  uint32 command;                 /* command ID */
  uint32 length;                  /* packet length incl command and length */
  uint32 version;                 /* target protocol version number */
  uint32 version_supported;       /* minimum protocol version number supported */
                                  /*   on target */
  uint32 cmd_packet_length;       /* maximum packet size supported for command */
                                  /*   packets */
  uint32 mode;                    /* expected mode of target operation */
  uint32 reserved0;               /* reserved field */
  uint32 reserved1;               /* reserved field */
  uint32 reserved2;               /* reserved field */
  uint32 reserved3;               /* reserved field */
  uint32 reserved4;               /* reserved field */
  uint32 reserved5;               /* reserved field */
};

/* HELLO_RESP command packet type - sent from host to target
     response to hello, protocol version running on host and status sent */
struct sahara_packet_hello_resp
{
  uint32 command;                 /* command ID */
  uint32 length;                  /* packet length incl command and length */
  uint32 version;                 /* host protocol version number */
  uint32 version_supported;       /* minimum protocol version number supported */
                                  /*   on host */
  uint32 status;                  /* OK or error condition */
  uint32 mode;                    /* mode of operation for target to execute */
  uint32 reserved0;               /* reserved field */
  uint32 reserved1;               /* reserved field */
  uint32 reserved2;               /* reserved field */
  uint32 reserved3;               /* reserved field */
  uint32 reserved4;               /* reserved field */
  uint32 reserved5;               /* reserved field */
};

/* READ_DATA command packet type - sent from target to host
     sends data segment offset and length to be read from current host 
     image file */
struct sahara_packet_read_data
{
  uint32 command;                 /* command ID */
  uint32 length;                  /* packet length incl command and length */
  uint32 image_id;                /* ID of image to be transferred */
  uint32 data_offset;             /* offset into image file to read data from */
  uint32 data_length;             /* length of data segment to be retreived */
                                  /*   from image file */
};

/* END_IMAGE_TX command packet type - sent from target to host
     indicates end of a single image transfer and status of transfer */
struct sahara_packet_end_image_tx
{
  uint32 command;                 /* command ID */
  uint32 length;                  /* packet length incl command and length */
  uint32 image_id;                /* ID of image to be transferred */
  uint32 status;                  /* OK or error condition */
};

/* DONE packet type - sent from host to target
     indicates end of single image transfer */
struct sahara_packet_done
{
  uint32 command;                 /* command ID */
  uint32 length;                  /* packet length incl command and length */
};

/* DONE_RESP packet type - sent from target to host
     indicates end of all image transfers */
struct sahara_packet_done_resp
{
  uint32 command;                 /* command ID */
  uint32 length;                  /* packet length incl command and length */
  uint32 image_tx_status;         /* indicates if all images have been  */
                                  /*   transferred; */
                                  /*   0 = IMAGE_TX_PENDING */
                                  /*   1 = IMAGE_TX_COMPLETE */
};

/* RESET packet type - sent from host to target
     indicates to target to reset */
struct sahara_packet_reset
{
  uint32 command;                 /* command ID */
  uint32 length;                  /* packet length incl command and length */
};

/* RESET_RESP packet type - sent from target to host
     indicates to host that target has reset */
struct sahara_packet_reset_resp
{
  uint32 command;                 /* command ID */
  uint32 length;                  /* packet length incl command and length */
};

/* MEMORY_DEBUG packet type - sent from target to host
     sends host the location and length of memory region table */
struct sahara_packet_memory_debug
{
  uint32 command;                 /* command ID */
  uint32 length;                  /* packet length incl command and length */
  uint32 memory_table_addr;       /* location of memory region table */
  uint32 memory_table_length;     /* length of memory table */
};

/* MEMORY_DEBUG packet type - sent from target to host
     sends host the location and length of memory region table */
struct sahara_packet_memory_debug_64bit
{
  uint32 command;                 /* command ID */
  uint32 length;                  /* packet length incl command and length */
  uint64 memory_table_addr;       /* location of memory region table */
  uint64 memory_table_length;     /* length of memory table */
};

/* MEMORY_READ packet type - sent from host to target
     sends memory address and length to read from target memory */
struct sahara_packet_memory_read
{
  uint32 command;                 /* command ID */
  uint32 length;                  /* packet length incl command and length */
  uint32 memory_addr;             /* memory location to read from */
  uint32 memory_length;           /* length of data to send */
};

/* SAHARA_MEMORY_READ_64BITS_ID packet type - sent from host to target
     sends 64 bits memory address and length to read from target memory */
struct sahara_packet_memory_read_64bit
{
  uint32 command;                 /* command ID */
  uint32 length;                  /* packet length incl command and length */
  uint64 memory_addr;             /* memory location to read from */
  uint64 memory_length;           /* length of data to send */
};


/* CMD_READY packet type - sent from target to host
     indicates to host that target is ready to accept commands */
struct sahara_packet_cmd_ready
{
  uint32 command;                 /* command ID */
  uint32 length;                  /* packet length incl command and length */
};

/* CMD_SWITCH_MODE packet type - sent from host to target
     indicates to target to switch modes */
struct sahara_packet_cmd_switch_mode
{
  uint32 command;                 /* command ID */
  uint32 length;                  /* packet length incl command and length */
  uint32 mode;                    /* mode of operation for target to execute */
};

/* CMD_EXEC packet type - sent from host to target
     indicates to target to execute given client_command */
struct sahara_packet_cmd_exec
{
  uint32 command;                 /* command ID */
  uint32 length;                  /* packet length incl command and length */
  uint32 client_command;          /* command ID for target Sahara client  */
                                  /*   execute */
};

/* CMD_EXEC_RESP packet type - sent from target to host
     indicates to host that target has successfully executed command
     and length of data response */
struct sahara_packet_cmd_exec_resp
{
  uint32 command;                 /* command ID */
  uint32 length;                  /* packet length incl command and length */
  uint32 client_command;          /* command ID for target Sahara client to */
                                  /*   execute */
  uint32 resp_length;             /* length of response returned from command */
                                  /*   execution */
};

/* CMD_EXEC_DATA packet type - sent from host to target
     indicates that host is ready to receive data after command execution */
struct sahara_packet_cmd_exec_data
{
  uint32 command;                 /* command ID */
  uint32 length;                  /* packet length incl command and length */
  uint32 client_command;          /* command ID for target Sahara client to */
                                  /*   execute */
};

/* COMMAND packet type - indicates a generic command packet */
struct sahara_packet_command
{
  uint32 command;                 /* command ID */
  uint32 length;                  /* packet length incl command and length */
};

/*=============================================================================
  Sahara protocol client defintions
=============================================================================*/
/* NOTE: Unless specified, all length fields/parameters are in bytes */

/* This structure can be used to retrieve information of the last
   image transferred to memory */
struct boot_sahara_binary_image_info{
  /* image ID - set by Sahara */
  uint32 image_id;

  /* image header - pointer must be initialized by caller of
     boot_sahara_entry before entering into Sahara to a valid
     array large enough to hold the expected binary image header */
  uint8* header;
};

struct boot_sahara_elf_image_info{
  /* image type - set by Sahara */
  uint32 image_id;

  /* ELF image header - set by Sahara */
  Elf32_Ehdr elf_header;

  /* Program headers - pointer must be initialized by caller of
     boot_sahara_entry before entering into Sahara */
  struct progressive_boot_block* prog_headers;

  /* Hash table - set by Sahara */
  uint8* hash_table;

  /* Shared segment index in program headers - set by Sahara */
  uint32 shared_seg_index;
  
  /* ELF image physical entry point - set by Sahara */
  uint32 entry_address;

  /* size of prog_headers buffer - must be initialized by caller of
     boot_sahara_entry before entering into Sahara */
  uint32 prog_headers_size;
  
  /*Total size of loaded elf segments - set by Sahara */
  uint32  total_elf_segments_size;
  
};

struct boot_sahara_shared_data{
  /* Expected Image - must be initialized by caller of
     boot_sahara_entry before entering into Sahara */
  uint32 expected_image;

  /* Expected Image Type - must be initialized by caller of
     boot_sahara_entry before entering into Sahara */
  enum boot_sahara_image_type expected_image_type;

  /* Pointer to current image info
     Must of type boot_sahara_binary_image_info* or boot_sahara_elf_image_info*
     Must be initialized by caller of
     boot_sahara_entry before entering into Sahara
   */
  void* cur_image;

  /* Indicates if image transfer is complete - set by Sahara */
  boolean image_rx_complete;

  /* Is secure boot enabled - set by Sahara by calling auth_enabled
                              during initialization */
  boolean is_secure;
};

typedef struct boot_sahara_cmd_exec_data
{
    // Pointer to command execution response information
    uint32             sahara_cmd_exec_client_command;
    uint32             sahara_cmd_exec_data_length;
    uint8*             sahara_cmd_temp_data_resp_buf;
    
    /* This points to actual data. 
        1. resp buffer (sahara_cmd_temp_data_resp_buf) or
        2. DDR training data
    */
    uint8*             sahara_cmd_exec_data;
    
}boot_sahara_cmd_exec_data;

typedef struct boot_sahara_data
{
    
    /* Revision number of the boot_sahara_entry() interface used
    *   Should be set to SAHARA_INTERFACE_VERSION
    */
    uint32                          revision;

    uint32                          image_id;
    volatile enum boot_sahara_state sahara_state;
    volatile boolean                sahara_done;
    uint8*                          sahara_packet_buffer;
    boot_sahara_status              status;
    volatile enum boot_sahara_mode  sahara_mode;
    uint32                          sahara_major_version;
    uint32                          sahara_major_version_supported;
    boolean                         sahara_mem_debug_enabled;
    
    // is_last_image is used so that boot_sahara has no dependency on upper layer
    boolean              is_last_image;

}boot_sahara_data;

typedef struct boot_sahara_callback_parameters
{
    // callback parameters
    uint32                          sahara_rx_bytes_read;
    enum boot_sahara_bulk_error     sahara_rx_err_code;
    volatile boolean                sahara_rx_complete;
    uint32                          sahara_tx_bytes_read;
    enum boot_sahara_bulk_error     sahara_tx_err_code;
    volatile boolean                sahara_tx_complete;
}boot_sahara_callback_parameters;

typedef struct boot_sahara_mem_debug_handle
{
    /* Save ramdump_table_handle */
    void*                           ramdump_table_handle;
    
    /* Sahara Memory Debug Buffer */
    uint8*                          sahara_mem_debug_buffer;
    
    /* Function table used for memory debug */
    ramdump_table_if*              mem_debug_tbl;
    
}boot_sahara_mem_debug_handle;

typedef struct boot_sahara_info
{
    boot_sahara_data                    sahara_data;
    
    boot_sahara_callback_parameters     sahara_cb_parameters;
    
    boot_sahara_command_handler_if*     sahara_cmd_handler_tbl;
    
    boot_sahara_cmd_exec_data           sahara_cmd_data;
    
    /* Dispatch table used for transfers */
    boot_sahara_dispatch_tbl*           dispatch_tbl;
    
    /* Ramdump dload handle and Function table for memory debug */
    boot_sahara_mem_debug_handle        mem_debug_handle;
    
}boot_sahara_info;
/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

===========================================================================*/


//===========================================================================
//
//                      EXPOSED FUNCTION DECLARATIONS
//
//===========================================================================

boot_sahara_status boot_sahara_entry(boot_sahara_info *);

boot_sahara_status boot_sahara_end(boot_sahara_info *);

boot_sahara_status boot_sahara_read(boot_sahara_info *, void *ram_addr, uint64, uint32 );

boot_sahara_status boot_sahara_poll(boot_sahara_info *);

bl_error_boot_type boot_sahara_enumeration_init( boot_sahara_dispatch_tbl * );

bl_error_boot_type boot_sahara_enumeration_deinit(boot_sahara_dispatch_tbl * );

void boot_sahara_set_last_image(boot_sahara_info *, boolean);

#endif  /* BOOT_SAHARA_INTERNAL_H */
