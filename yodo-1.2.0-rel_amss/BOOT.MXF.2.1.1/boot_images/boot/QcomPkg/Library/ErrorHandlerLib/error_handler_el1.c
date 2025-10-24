/*=============================================================================

                             Boot Error Handler

GENERAL DESCRIPTION
  This file contains Boot Loader error handler.
  The BOOT error handler is called in the event an error is detected.

Copyright 2009-2022 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
05/24/22   rama    Error handling in XBLRamdumpMain
06/16/21   ds      add cache flush stub
04/30/21   rama    Changes for handling exceptions gracefully.
03/19/21   rama    Removed boot_crashdump.h
01/22/21   rhy     Added err_code in struct error_info_struct and added get_error_info()
01/19/21   rama    Removed boot_elf_load_deinit in boot_error_handler
11/12/20   rama    Added UCLib call in boot_init_stack_chk_canary
09/16/20   rama    Fix PBL interface parameter casting issue
09/10/20   ds      updates for PBL shared data
07/23/20   rama    Added pbl_shared_data_if
06/25/20   rama    Removed boot_query_xpu_violation API
05/29/20   rama    Replace boot_dload.h with boot_crashdump.h
05/10/20   ds      move to edk2 arm mmu/cache lib
05/14/20   rama    Added Arch-specific APIs for error handler and crashdump
05/07/20   ck      Replaced boot_pbl_get_flash_type with boot_pbl_get_media_type
02/24/20   ds      GET_ERROR_CODE changes to use line number and filename
02/12/20   rama    removed dal/crypto extern wrappers and added config context
01/25/19   yps     update compile-time stack pointer and size 
09/04/18   msantos moved sbl_save_regs here
08/29/18   msantos set dload cookie and warm reset if ramdump not allowed in boot_error_hander
08/09/17   yps     Replaced Macro __FILE__ with __FILE_BASENAME__
06/23/16   digant  error handler updates for aborts
06/02/16   digant  Api for xpu violation query
07/15/15   ck      Added call to boot_elf_load_deinit in boot_error_handler
04/15/15   ck      Inlined boot_init_stack_chk_canary as canary value is changed
06/11/14   kedara  Update to support 64-bit msm8996
05/30/14   kedara  Replace snprintf by qsnprintf, Remove __stack_chk_fail.
03/18/14   kedara  Save the registers early in the error handler.
                   Call sbl_error_handler after saving err_log so that it is present in 
                   the SBL crash dumps
03/18/14   ck      Updated boot_hw_reset calls as they now take a reset type parameter
08/19/13   yp      call boot_pm_vib_off to stop vibrate,when a error happen.
07/10/13   aus     Added support to save the registers and flush the L2 TCM to DDR
                   on SBL errors
05/23/12   kedara  Fix boot error log entry updation.
12/10/12   plc     Fix Klockwork errors
08/31/12   dh      Add log message to boot_error_handler
05/02/12   dh      Add __stack_chk_fail
03/14/12   dh      Rmove cache_mmu_disable
06/27/11   aus     Added support for flashless boot
09/10/10   aus     Enabling data cache and MMU in boot
08/18/10   aus     Code Clean-up
07/22/10   aus     Clean-up secboot 3
07/09/10   aus     Moved stack_ptr_addr definition to sbl specific sconscripts and sbl_dload_entry to 
                   boot_dload_handler.h
06/23/10   plc     Support DLOAD in secboot 3.0
05/26/10   plc     Initial port to secboot 3.0 common code  
12/28/09   ty      Initial port to BOOT
09/09/09   tnk     Removing of  MMU Disable in the osbl_error_handler path .


=============================================================================*/


/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include <HALhwio.h>
#include <HALbootHWIO.h>
#include <boot_sbl_shared.h>
#include <dload_dump.h>
#include <error_handler.h>
#include <boot_crashdump.h>
#include <boot_logger.h>
#include <boot_pmic_if.h>
#include <boot_fastcall_tz.h>
#include <stdio.h>
#include <string.h>
#include <boot_config_context.h>
#include <boot_error_if.h>
#include <boot_dal_if.h>
#include <boot_crypto_if.h>
#include <boot_reset_if.h>
#include <boot_error_handler_arch.h>
#include <sbl_crashdump_arch.h>
#include <boot_sbl_if.h>
#include <pbl_sbl_shared.h>
#include <boot_dbginfo_if.h>
#include <boot_media_interface_if.h>
#include <boot_logs_to_media.h>
/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
extern uintnt Image$$STACK_BASE$$Pointer[];
extern uintnt Image$$STACK$$Base[];
 
/**
 * Infinite loop
 */
#define INFINITE_LOOP() while(1)

#define MAX_BOOTLOG_SECONDARY_ENTRIES 2

/*Add one extra count to get the required count value since 
  shared IMEM is initialized with 0xFFFFFFFF */
#define MAX_BOOT_FAIL_COUNT 3
/*---------------------------------------------------------------------------
  Define just to make sure the link list doesn't go off into the weeds.
---------------------------------------------------------------------------*/
#define BOOT_MAX_NUM_ERROR_CALLBACKS 20
#define MAX_CALLSTACK_PRINT 10
exc_context exception_context = {0};

extern boot_crash_dump_type boot_crash_dump_data;

/* Function prototypes */
void boot_error_handler
(
  const char* filename_ptr,     /* File this function was called from -
                                   defined by __FILE__ */
  uint32      line,             /* Line number this function was called
                                   from - defined by  __LINE__ */
  uint32      err_code          /* Enum that describes error type */
);
static void boot_install_error_callback
(
  bl_error_callback_func_type,
  void *,
  bl_error_callback_node_type *node_ptr
);

/*---------------------------------------------------------------------------
  Define the BOOT ERROR Log entry types. 
  ---------------------------------------------------------------------------*/
typedef struct boot_err_log_entry_type
{
  uint32 error_type;
  uint32 line;
  const char   *filename;
} boot_err_log_entry_type;

typedef struct boot_err_count_type
{
  char *sbl_type;
  uint32 error_count;
} boot_err_count_type;


/*---------------------------------------------------------------------------
  Define the error logging and error callback variables.
  ---------------------------------------------------------------------------*/
/* Structure defining the layout of BOOT error records. */
typedef struct
{
  /* The primary BOOT error record. */
  boot_err_log_entry_type primary_log;

  /* The total number of errors logged. Store this after 1st error record. */
  boot_err_count_type     err_count;

  /* Array of records for subsequent BOOT errors. */
  boot_err_log_entry_type secondary_log[MAX_BOOTLOG_SECONDARY_ENTRIES];
} err_log_type;
static err_log_type err_log SECTION(".bss.ERR_DATA");

/* Structure defining the layout of BOOT error records. */
err_log_type *boot_err_log_ptr SECTION(".bss.ERR_DATA_PTR") = NULL;

/* Error handler callback data structures */
static bl_error_callback_node_type *err_cb_head_ptr = NULL;

/*Error message that can be logged using boot logger */
char error_message[BOOT_ERROR_MSG_LEN];

/*Error message that can be logged  for stack back trace */
static char func_name[BOOT_ERROR_MSG_LEN];

/* The global boot error interface structure */
boot_error_if_type bl_err_if = 
{
  boot_error_handler,
  boot_install_error_callback
};


typedef struct error_info_struct
{
  char *filename;
  uint32 line_num;
  bl_error_boot_type  err_code;
}error_info_struct;

static error_info_struct error_info = {NULL, 0, BL_ERR_NONE};

/* Stack protection canary. 
   With stack protection, when a vulnerable function is called, 
   the initial value of its guard variable is taken from this variable
   
   __stack_chk_guard and API __stack_chk_fail() are defined in QcomBaseLib.

   Canary is set to a random value in boot_init_stack_chk_canary
*/
extern void *__stack_chk_guard;

/*=============================================================================
   
                              FUNCTION DEFINITIONS

=============================================================================*/

/*===========================================================================

**  Function :  get_error_code

** ==========================================================================
*/
/*!
* 
* @brief
*   fills the filename and line number where error occured
*   and ORs(|) the group and error
*
* @par Dependencies
*   None
*   
* @param[in] void
*
* @retval
*   bl_error_boot_type
* 
* @par Side Effects
*   None
* 
*/
static bl_error_boot_type get_error_code(uint32 group, uint32 error, char* filename_ptr, uint32 line)
{
  if(error_info.filename == NULL && error_info.line_num == 0)
  {
    error_info.filename = filename_ptr;
    error_info.line_num = line;
    error_info.err_code = (group | error);
  }
  return ((error == BL_ERR_NONE) ? BL_ERR_NONE : (group | error));
}

get_error_code_fn_ptr get_error_code_ptr = &get_error_code;

/*===========================================================================

**  Function :  get_error_info

** ==========================================================================
*/
/*!
* 
* @brief
*   Get error code from error_info
*
* @par Dependencies
*   None
*   
* @param[in] void
*
* @retval
*   bl_error_boot_type
* 
* @par Side Effects
*   None
* 
*/
static bl_error_boot_type get_error_info(void)
{
    return error_info.err_code;
}

get_error_info_fn_ptr get_error_info_ptr = &get_error_info;

/*===========================================================================

**  Function :  clear_error_code

** ==========================================================================
*/
/*!
* 
* @brief
*   clears the error info - line_num and Filename
*
* @par Dependencies
*   None
*   
* @param[in] void
*
* @retval
*   None
* 
* @par Side Effects
*   None
* 
*/
static void clear_error_code(void)
{
    error_info.filename = NULL;
    error_info.line_num = 0;
    error_info.err_code = BL_ERR_NONE;
}

clear_error_code_fn_ptr clear_error_code_ptr = &clear_error_code;

/*===========================================================================

**  Function :  set_error_code

** ==========================================================================
*/
/*!
* 
* @brief
*   sets the error code
*
* @par Dependencies
*   None
*   
* @param[in] void
*
* @retval
*   None
* 
* @par Side Effects
*   None
* 
*/
static bl_error_boot_type set_error_code(bl_error_boot_type error_code)
{
  error_info.err_code = error_code;
  return error_info.err_code;
}

set_error_code_fn_ptr set_error_code_ptr = &set_error_code;


/*===========================================================================

**  Function :  is_jtag_connected

** ==========================================================================
*/
/*!
* 
* @brief
*   checks if jtag is connected 
*
* @par Dependencies
*   None
*   
* @param[in] void
*
* @retval
*   boolean
* 
* @par Side Effects
*   None
* 
*/
static boolean is_jtag_connected(void)
{
  return HWIO_INF(AOSS_CC_CDBGPWRUPREQ, STATUS);
}

/*===========================================================================

**  Function :  boot_store_boot_logs

** ==========================================================================
*/
/*!
* 
* @brief
*   This function writes boot logs into storage upon graceful errors
* 
* @param[in] boot_handle
* 
* @par Dependencies
*   None 
*   
* @retval
*   None
* 
* @par Side Effects
*   None
* 
*/
void boot_store_boot_logs(boot_handle config_context_handle)
{
  bl_error_boot_type status = BL_ERR_NONE;
  
  do
  {
    status = boot_init_logs_to_media(config_context_handle);
    if(status != BL_ERR_NONE)
    {
      break;
    }

    status = boot_save_logs_to_media(config_context_handle);
    if(status != BL_ERR_NONE)
    {
      break;
    }
  }while(FALSE);
}

/*===========================================================================

**  Function :  boot_error_handler

** ==========================================================================
*/
/*!
* 
* @brief
*   This function is the error handler for the BOOT and records the line 
*   number, filename & error type before jumping into the downloader. 
*   This function is also shared by exception handler and can log
*   multiple errors if called more than once.
* 
* @param[in] filename_ptr File this function was called from defined by __FILE__
* @param[in] line Line number this function was called from defined by __LINE__ 
* @param[in] err_code Enum that describes error type
*
* @par Dependencies
*   Exception handler. 
*   
* @retval
*   None
* 
* @par Side Effects
*   This function never returns.
* 
*/
void boot_error_handler
(
  const char* filename_ptr,     /* File this function was called from -
                                   defined by __FILE__ */
  uint32      line,             /* Line number this function was called
                                   from - defined by  __LINE__ */
  uint32      err_code          /* Enum that describes error type */
)
{
  register boot_err_log_entry_type *boot_err_log_entry_ptr = NULL;
  static uint32 error_handler_entry_count = 0;
  register uint32 i = 0;
  uintnt fp;
  uintnt lr;
  static exc_context* exc_context_ptr = NULL;
  boot_boolean oem_lcs_is_dev = FALSE;
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_reset_if_type *reset_if = NULL;

  
  if(error_info.filename != NULL && error_info.line_num != 0)
  {
	  filename_ptr = error_info.filename;
	  line = error_info.line_num;
  }
  do
  {

    return_status = boot_is_oem_lcs_dev_state(&oem_lcs_is_dev);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }
    return_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_RESET_INTERFACE, (void *)&reset_if);
    if(return_status != BL_ERR_NONE || reset_if == NULL)
    {
      break;
    }

    exc_context_ptr = (exc_context*)&exception_context;
    
    error_handler_entry_count++; /* Count the number of calls to this fn */
    

    /* Ensure boot error log entries are within bounds. Only
     MAX_BOOTLOG_SECONDARY_ENTRIES+1 error logs supported/
    */
    if((MAX_BOOTLOG_SECONDARY_ENTRIES + 1) >= error_handler_entry_count)
    {
      if(error_handler_entry_count == 1) /* Entering Error Handler for first time */
      {
        if (boot_get_exc_cookie(exc_context_ptr) == SBL1_EXC_CONTEXT_VALID_COOKIE)
        {
          boot_err_dump_exc_context(exc_context_ptr, error_message, BOOT_ERROR_MSG_LEN, EL_1);
        }
        /* Only log to boot logger if this is the first time entering error handler */
        snprintf(error_message, BOOT_ERROR_MSG_LEN, "Error code %lx at %s Line %lu", err_code, filename_ptr, line);
          
        boot_log_message(error_message);

        // BackTracing the stack to print the callstack in UART
        boot_log_message("Call Stack:");
        fp =  boot_get_frame_pointer();
        uint64 i = 0;
        while((fp!=0 && i < MAX_CALLSTACK_PRINT)&&(fp < (uint64)Image$$STACK_BASE$$Pointer)&&(fp > (uint64)Image$$STACK$$Base))
        {
          i++;
          __asm__ __volatile__("ldr %0, [%1,#8]":"=r"(lr):"r"(fp)); 
          __asm__ __volatile__("ldr %0, [%1]":"=r"(fp):"r"(fp));
        
          snprintf(func_name, 26 ,"func_addr  :   %08X", lr);
          boot_log_message(func_name);
        }

        boot_log_message("^^^^^^^^^^^^^^^^^^^^^");
        /* Pointer to the primary error log */
        boot_err_log_ptr = &err_log;
        boot_err_log_entry_ptr = &err_log.primary_log;

        /* Log that this is BOOT error */
        err_log.err_count.sbl_type = "BOOT";
      }
      else /* For all subsequent calls to this fn */
      {
        /* Pointer to the error log for subsequent errors */
        /* error_handler_entry_count of 2 corresponds to first
          element of secondary_log */
        boot_err_log_entry_ptr = &err_log.secondary_log[(error_handler_entry_count-2)];
      }

      /* Save total number of errors logged */
      err_log.err_count.error_count = error_handler_entry_count;

      /* Log the error type */
      boot_err_log_entry_ptr->error_type = err_code;

      /* Log the line number */
      boot_err_log_entry_ptr->line = line;

      /* Log the filename; no need to copy, const mem */
      boot_err_log_entry_ptr->filename = filename_ptr;


      if ( error_handler_entry_count == 1 )
      {
        /* Only try to execute the error callbacks the first time through
        the error handler in case one of the callbacks caused the
        subsequent error. */

        register bl_error_callback_node_type *node_ptr;

        for ( node_ptr = err_cb_head_ptr, i = 0;
          node_ptr != NULL && i < BOOT_MAX_NUM_ERROR_CALLBACKS;
          node_ptr = node_ptr->next_ptr, i++ )
        {
        node_ptr->data.cb_func( node_ptr->data.data_ptr );
        }
      }
#ifdef ENABLE_LOGS_TO_MEDIA
      boot_boolean booting_from_storage = FALSE;
      return_status = boot_media_booting_from_storage(CONFIG_CONTEXT_CRT_HANDLE, &booting_from_storage);

      if(booting_from_storage)
      {
        boot_store_boot_logs(CONFIG_CONTEXT_CRT_HANDLE);
      }
#endif
      if(oem_lcs_is_dev)
      {
        boot_dload_transition_pbl_forced_dload(CONFIG_CONTEXT_CRT_HANDLE);
      }
      else
      {
        reset_if->hw_reset(BOOT_HARD_RESET_TYPE);
      }
    }
  }
  while(FALSE);
#ifdef FEATURE_XBOOT /* Sony use powerdown instead of infinite-loop */
  boot_hw_powerdown();
#else /* !FEATURE_XBOOT */
  /* In case of re-entrant error handler or dload entry failure, just loop */
  INFINITE_LOOP();
#endif /* !FEATURE_XBOOT */

} /* boot_error_hander() */


/*===========================================================================

**  Function :  boot_install_error_callback

** ==========================================================================
*/
/*!
* 
* @brief
*   This function installs a callback function that will be executed when
*   an error occurs.
* 
* @param[in] cb_func Call back function 
* @param[in] data_ptr Pointer to the data
* @param[in] node_ptr Pointer to the node
*
* @par Dependencies
*   None 
*   
* @retval
*   None
* 
* @par Side Effects
*   None
* 
*/
static void boot_install_error_callback
(
  bl_error_callback_func_type cb_func,
  void *data_ptr,
  bl_error_callback_node_type *node_ptr
)
{
  BL_VERIFY( cb_func != NULL && node_ptr != NULL, BL_ERR_NULL_PTR_PASSED|BL_ERROR_GROUP_BOOT );
  node_ptr->data.cb_func = cb_func;
  node_ptr->data.data_ptr = data_ptr;
  node_ptr->next_ptr = err_cb_head_ptr;

  err_cb_head_ptr = node_ptr;

} /* boot_install_error_callback() */


/*===========================================================================

**  Function :  boot_nested_exception_c_handler

** ==========================================================================
*/
/*!
* 
* @brief
*   This function enables the JTAG interface and never returns.  It is
*   called when a nested exception occurs.
* 
*   Note: For security purposes, our main concern is concealing the hardware
*         key when the JTAG interface is enabled.  This is handled by hardware.
*         Because of this, it is not required that all memory and registers be
*         cleaned out before enabling the JTAG interface.  The hardware key is
*         never accessed or used by the BOOT. 
* 
* @par Dependencies
*   None
*   
* @retval
*   None
* 
* @par Side Effects
*   This function never returns.
* 
*/
void boot_nested_exception_c_handler( void )
{
 sbl_loop_here();  
} /* boot_nested_exception_c_handler() */


/*===========================================================================

**  Function :  boot_err_fatal

** ==========================================================================
*/
/*!
* 
* @brief
*   This function calls the SBL error handler.
*   
* @par Dependencies
*   None
*   
* @retval
*   None
* 
* @par Side Effects
*   None
*/
void boot_err_fatal( void )
{
  BL_ERR_FATAL( BL_ERR_OTHERS );
}


/*===========================================================================


**  Function :  boot_<exception_type>_c_handler

** ==========================================================================
*/
/*!
* 
* @brief
*   These are the exception handlers for the BOOT.  They include handlers for
*   each of the following exception types:
* 
*     - undefined instruction
*     - software interrupt
*     - prefetch abort
*     - data abort
*     - reserved
*     - IRQ
*     - FIQ
*   
*   The BOOT considers each of these exceptions a fatal error and handles
*   them by calling the boot_error_handler().  A separate handler is assigned
*   to each exception for the purpose of providing additional debug
*   information.  Each call to the BOOT_ERR_FATAL() provides filename, file
*   line number & SBL ERROR TYPE information.
* 
* @par Dependencies
*   None
*   
* @retval
*   None
* 
* @par Side Effects
*   These handlers never return.
* 
*/
void boot_undefined_instruction_c_handler( void )
{
  BL_ERR_FATAL(BL_ERR_UNDEF_INSTR);
}

void boot_swi_c_handler( void )
{
  BL_ERR_FATAL( BL_ERR_SWI );
}

void boot_prefetch_abort_c_handler( void )
{
  /* Don't use the global error handler pointer in case it's invalid and
     caused the abort */
  boot_error_handler( __FILE_BASENAME__, __LINE__, BL_ERR_PREFETCH_ABORT );
}

void boot_data_abort_c_handler( void )
{
  /* Don't use the global error handler pointer in case it's invalid and
     caused the abort */
  boot_error_handler( __FILE_BASENAME__, __LINE__, BL_ERR_DATA_ABORT );
}

void boot_reserved_c_handler( void )
{
  /* Don't use the global error handler pointer in case it's invalid and
     caused the abort */
  boot_error_handler( __FILE_BASENAME__, __LINE__, BL_ERR_RESERVED_HANDLER ); 
}

void boot_sync_c_handler ( void )
{
  uint32 sync_exception_type = BL_ERR_EXCEPTION_MAX;
  
  sync_exception_type = get_el1_sync_type();
  
  switch (sync_exception_type)
  { 
    case (BL_EXCEPTION_I_ABORT):
    boot_prefetch_abort_c_handler();
  break;
    case (BL_EXCEPTION_D_ABORT):  
      boot_data_abort_c_handler();
  break;
    case (BL_ERR_EXCEPTION_MAX):
      boot_undefined_instruction_c_handler();
  break;
    default:
      boot_reserved_c_handler();
  break;
  }
}

void boot_irq_c_handler( void )
{
  BL_ERR_FATAL( BL_ERR_IRQ );
}

void boot_fiq_c_handler( void )
{
  BL_ERR_FATAL( BL_ERR_FIQ );
}

void boot_sys_c_handler( void )
{
  BL_ERR_FATAL( BL_ERR_SYS );
}

/*===========================================================================


**  Function :  __rt_raise

** ==========================================================================
*/
/*!
* 
* @brief
*   This is the re-implementation of the C library runtime exception handler.
*   This gets called from the C library, for example, when integer
*   divide-by-zero occurs.  Re-implementing this handler prevents linking in
*   the standard C library signal handling routines and reduces the overall
*   image size.  The BOOT considers a C library runtime exception fatal.
* 
* @par Dependencies
*   None
*   
* @retval
*   None
* 
* @par Side Effects
*   This handler never returns.
* 
*/
void __rt_raise
( 
  int signal, 
  int type 
)
{
  BL_ERR_FATAL( BL_ERR_C_LIB_RT );
}




/*===========================================================================

**  Function :  boot_init_stack_chk_canary

** ==========================================================================
*/
/*!
* 
* @brief
*   Initialize stack protection canary to a random number.
*   Function is inlined as stack canary value will be changing.
*
* @par Dependencies
*   None
*   
* @retval
*   None
* 
* @par Side Effects
*   None
* 
*/
inline void boot_init_stack_chk_canary()
{
  uintnt new_canary_value = 0;
  
  /*config context get pointer result*/
  bl_error_boot_type return_status = BL_ERR_NONE;
  
  /*pointer to hold crypto interface table*/
  boot_crypto_if_type *crypto_if;
  do
  {
    return_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_CRYPTO_INTERFACE, (void **)&crypto_if);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }
    BL_VERIFY
    (
     (sizeof(new_canary_value) == crypto_if->uclib_get_prng_data(crypto_if->ucenv_get_env(),(uint8_t *)&new_canary_value,sizeof(new_canary_value))),
     BL_ERROR_GROUP_PRNG|BL_ERR_BUFFER_OVERFLOW
    );

    __stack_chk_guard = (void *)new_canary_value;
  }
  while(FALSE);
}

/*===========================================================================

**  Function :  boot_cache_flush_boot_regions

** ==========================================================================
*/
/*!
* 
* @brief
*   This Function flushes boot log, RW and ZI regions.
*
* @par Dependencies
*   None
*   
* @retval
*   TRUE on success.
* 
* @par Side Effects
*   None
* 
*/
boolean boot_cache_flush_boot_regions(void)
{
 return TRUE;
}

