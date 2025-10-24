#ifndef SBL_CRASHDUMP_ARCH_H
#define SBL_CRASHDUMP_ARCH_H

/*===========================================================================

                       Boot Error Handler Arch Header File

GENERAL DESCRIPTION
  This header file contains declarations and definitions for the BOOT Arch 
  specific crashdump handler.  It is called in the event a BOOT failure is detected.
    
Copyright 2020 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
06/22/21   rama    EL3 minidump changes.
05/29/20   rama    Added crashdump version and cookie macros
04/21/20   rama    Initial revision
============================================================================*/

/*===========================================================================
 
                           INCLUDE FILES

===========================================================================*/
#include "boot_comdef.h"
#include <boot_config_context.h>

/*==========================================================================
                          PUBLIC DATA DECLARATIONS
===========================================================================*/
#define NUM_ARM_REGISTERS 16 // Arm
#define NUM_AARCH64_REGISTERS 31 // Aarch64
#define BOOT_CRASH_DUMP_VERSION 2 // Version 2 adds support for Aarch64 and more special registers
#define BOOT_CRASH_DUMP_COOKIE 0x45525220 // Cookie "ERR "

typedef enum
{
  ARM_SVC_R0 = 0,
  ARM_SVC_R1,
  ARM_SVC_R2,
  ARM_SVC_R3,
  ARM_SVC_R4,
  ARM_SVC_R5,
  ARM_SVC_R6,
  ARM_SVC_R7,
  ARM_SVC_R8,
  ARM_SVC_R9,
  ARM_SVC_R10,
  ARM_SVC_R11,
  ARM_SVC_R12,
  ARM_SVC_SP,
  ARM_SVC_LR,
  ARM_SVC_SPSR,
  ARM_SVC_PC,
  ARM_CPSR,
  ARM_SYS_SP,
  ARM_SYS_LR,
  ARM_IRQ_SP,
  ARM_IRQ_LR,
  ARM_IRQ_SPSR,
  ARM_ABT_SP,
  ARM_ABT_LR,
  ARM_ABT_SPSR,
  ARM_UND_SP,
  ARM_UND_LR,
  ARM_UND_SPSR,
  ARM_FIQ_R8,
  ARM_FIQ_R9,
  ARM_FIQ_R10,
  ARM_FIQ_R11,
  ARM_FIQ_R12,
  ARM_FIQ_SP,
  ARM_FIQ_LR,
  ARM_FIQ_SPSR,
  SIZEOF_ARM_REGISTERS
} arm_register_type;

typedef enum
{
  AARCH64_X0 = 0,
  AARCH64_X1,
  AARCH64_X2,
  AARCH64_X3,
  AARCH64_X4,
  AARCH64_X5,
  AARCH64_X6,
  AARCH64_X7,
  AARCH64_X8,
  AARCH64_X9,
  AARCH64_X10,
  AARCH64_X11,
  AARCH64_X12,
  AARCH64_X13,
  AARCH64_X14,
  AARCH64_X15,
  AARCH64_X16,
  AARCH64_X17,
  AARCH64_X18,
  AARCH64_X19,
  AARCH64_X20,
  AARCH64_X21,
  AARCH64_X22,
  AARCH64_X23,
  AARCH64_X24,
  AARCH64_X25,
  AARCH64_X26,
  AARCH64_X27,
  AARCH64_X28,
  AARCH64_X29,
  AARCH64_X30,
  SIZEOF_AARCH64_REGISTERS
} aarch64_register_type;

typedef struct
{
  uint32 crash_dump_cookie;            // Crash dump magic cookie
  uint32 version;                      // Version of the data structure
  uint32 regs[SIZEOF_ARM_REGISTERS];   // General registers
  uint32 sbl_ddr_dump_addr;            // Location in DDR where SBL DDR region is dumped
  uint32 sbl_ddr_addr;                 // Address of SBL DDR region
  uint32 sbl_ddr_size;                 // Size of SBL DDR region
  uint32 sbl_l2_dump_addr;             // Location in DDR where SBL L2 region is dumped
  uint32 sbl_l2_addr;                  // Address of SBL L2 region
  uint32 sbl_l2_size;                  // Size of SBL L2 region
  uint32 sbl_pcie_coredump_addr;       // Address of PCIe register dump
  uint32 sbl_pcie_coredump_size;       // Size of PCIe register dump region
} boot_crash_dump_arm_type;

typedef struct
{
  uint32 crash_dump_cookie;            // Crash dump magic cookie
  uint32 version;                      // Version of the data structure
  uint64 regs[SIZEOF_AARCH64_REGISTERS];  // General registers
  uint64 pc;                           // Special registers
  uint64 sp_elx;                       //reg_elx indicates the register will either be EL3 or EL1
  uint64 actlr_elx;
  uint64 elr_elx;
  uint64 esr_elx;
  uint64 far_elx;
  uint64 mair_elx;
  uint64 sctlr_elx;
  uint64 spsr_elx;
  uint64 tcr_elx;
  uint64 tpidr_elx;
  uint64 ttbr0_elx;
  uint64 vbar_elx;
  uint64 ccsidr_el1;
  uint64 clidr_el1;
  uint64 cntkctl_el1;
  uint64 cpacr_el1;
  uint64 csselr_el1;
  uint64 midr_el1;
  uint64 mpidr_el1;
  uint64 sbl_ddr_dump_addr;            // Location in DDR where SBL DDR region is dumped
  uint64 sbl_ddr_addr;                 // Address of SBL DDR region
  uint64 sbl_ddr_size;                 // Size of SBL DDR region
  uint64 sbl_boot_imem_dump_addr;      // Location in DDR where BOOT IMEM region is dumped
  uint64 sbl_boot_imem_addr;           // Address of BOOT IMEM region
  uint64 sbl_boot_imem_size;           // Size of BOOT IMEM region
  uint64 sbl_shared_imem_dump_addr;    // Location in DDR where SHARED IMEM region is dumped
  uint64 sbl_shared_imem_addr;         // Address of SHARED IMEM region
  uint64 sbl_shared_imem_size;         // Size of SHARED IMEM region  
} boot_crash_dump_aarch64_type;



typedef union 
{
  boot_crash_dump_arm_type 	boot_crash_dump_arm_data;
  boot_crash_dump_aarch64_type boot_crash_dump_aarch64_data;
}boot_crash_dump_type;

/*===========================================================================
**  Function :  sbl_save_regs
** ==========================================================================
*/
/*!
* 
* @brief
*   Save current registers at the time of crash
*
* @par Dependencies
*  None        
*   
*/


void sbl_save_regs(boot_crash_dump_type* boot_crash_dump_data_ptr);

/*===========================================================================
**  Function :  boot_crash_dump_handler
** ==========================================================================
*/
/*!
* 
* @brief
*   This fills the boot_crash_dump_data struct for use by
*   simulator tool, and copies it and other boot memory
*   regions to an unused region for dumping
*
* @param[in] boot_handle  config context handle passed by caller
*            ramdump_type  MINIDUMPS/FULL DUMPS allowed
*        
* @par Dependencies
*  none
* 
* @param[out] BL_ERR_NONE on success
*/
bl_error_boot_type boot_crash_dump_handler(boot_handle config_context_handle, uint32 ramdump_type);

/*===========================================================================
**  Function :  boot_get_frame_pointer
** ==========================================================================
*/
/*!
* 
* @brief
*   This gets the frame pointer from boot_crashdump_data
*
* @param[in] None
*        
* @par Dependencies
*  none
*   
*/
uintnt boot_get_frame_pointer(void);
#endif  /* SBL_CRASHDUMP_ARCH_H */
