/*=============================================================================
  
                     SCATTER LOADING DESCRIPTION FILE
  
  Copyright 2014, 2017 by Qualcomm Technologies, Inc. All Rights Reserved.
  
  GENERAL DESCRIPTION
  
  The scatter loading description file is used to define the SBL1 memory map.
=============================================================================*/
/*=============================================================================
  
                            EDIT HISTORY FOR FILE
   This section contains comments describing changes made to the module.
   Notice that changes are listed in reverse chronological order.
  
  
  when       who     what, where, why
  --------   ---     -------------------------------------------------------
  12/03/17   yps     Removed RAMDUMP_DLOAD_BUFFERS_RAM segment
  08/10/17   yps     Add RAMDUMP_DATA_ZI base and length
  01/26/17   yps     Upgrade compiler to CLANG38
  09/16/14   kpa     Relocate RAMDUMP_DLOAD_ZI section.
  11/20/14   ck      Refactored for QUSB driver
  10/01/14   kpa     Include Target_cust.h instead of boot_target_scl.h
  08/08/14   ck      Added RAMDUMP_DLOAD_ZI
  07/29/14   ck      Inital version.
=============================================================================*/

#include "Target_cust.h"

PHDRS {
  RAMDUMP_CODE_ROM PT_LOAD;
  STACK_IMEM PT_LOAD;
  RAMDUMP_CODE_RAM PT_LOAD;
}

SECTIONS
{
  /* This section contains XBLRamDump code and RO data */
  RAMDUMP_ROM SCL_RAMDUMP_CODE_BASE: 
  {
    /*Temporary solution until migrate to sectool v2. Because sectools doesn't have sign_id for ramdump*/
    Image$$RAMDUMP_CODE$$Base = .;
    *ModuleEntryPoint*.o*(.text*);     
    *(VECTOR_TABLE_EL1)
    *(.text .stub .text.* .rela.text .relaRAMDUMP_ROM*)
    *(BOOT_UTIL_ASM)
    *(ARM_MMU)
    *(.gcc_except_table  .got .got.plt )
    . = ALIGN(4096);
    Image$$RAMDUMP_CODE$$End = . ;
    Image$$RAMDUMP_CODE$$Length = Image$$RAMDUMP_CODE$$End - Image$$RAMDUMP_CODE$$Base;
    ASSERT(SIZEOF(RAMDUMP_ROM) <= SCL_RAMDUMP_CODE_SIZE, "Invalid size of RAMDUMP_ROM Section");
  } : RAMDUMP_CODE_ROM
  
  STACK SCL_RAMDUMP_DLOAD_BUFFERS_BASE: ALIGN(4096)
  {
    Image$$STACK$$Base = . ;
    . = . + SCL_STACK_SIZE;
    . = ALIGN(4096);
    Image$$STACK$$End =. ;
    Image$$STACK_BASE$$Pointer = . ;
    Image$$STACK$$Length = Image$$STACK$$End - Image$$STACK$$Base;
  } : STACK_IMEM 
  RAMDUMP_DATA_RO SCL_RAMDUMP_DATA_BASE : ALIGN(4096)
  {
    Image$$RAMDUMP_DATA_RO$$Base = .;
    /* RO DATA */
    *(RO)
    *(.constdata .rodata .rodata.* )
    . = ALIGN(4096);
    Image$$RAMDUMP_DATA_RO$$End = . ;
    Image$$RAMDUMP_DATA_RO$$Length = Image$$RAMDUMP_DATA_RO$$End - Image$$RAMDUMP_DATA_RO$$Base;
  }
  RAMDUMP_DATA_RW : ALIGN(4096)
  {
    Image$$RAMDUMP_DATA_RW$$Base = .;
    *(.data .data.* .data1 .rela.data .relaRAMDUMP_DATA_RW*)
    *(ERR_DATA_PTR ERR_DATA  .tdata)
    *(RW)
    . = ALIGN(4096);
    Image$$RAMDUMP_DATA_RW$$End = . ;
    Image$$RAMDUMP_DATA_RW$$Length = Image$$RAMDUMP_DATA_RW$$End - Image$$RAMDUMP_DATA_RW$$Base;
  } : RAMDUMP_CODE_RAM


  /* This section contains non DDR ZI. */
  RAMDUMP_DATA_ZI : ALIGN(4096)
  {
    Image$$RAMDUMP_DATA_ZI$$Base = . ;
    *(.bss.BOOT_UNCACHED_ZI_ZONE)    
    *(.bss.BOOT_DDR_ZI_DATA_ZONE) 
    *(.bss*)
    *(.dynbss)
    *(COMMON)
    . = ALIGN(4096);
    Image$$RAMDUMP_DATA_ZI$$End = . ;
    Image$$RAMDUMP_DATA_ZI$$Length = Image$$RAMDUMP_DATA_ZI$$End - Image$$RAMDUMP_DATA_ZI$$Base;
  } : RAMDUMP_CODE_RAM
  ASSERT(Image$$RAMDUMP_DATA_ZI$$End - SCL_RAMDUMP_DATA_BASE <= SCL_RAMDUMP_DATA_SIZE, "Invalid size of RAMDUMP_DATA Section");
  ASSERT((SCL_RAMDUMP_CODE_SIZE + SCL_RAMDUMP_DATA_SIZE) <= SCL_RAMDUMP_TOTAL_SIZE, "Invalid size of RamDump Image");
 
  Image$$RAMDUMP_DATA_ZI$$Length = SIZEOF(RAMDUMP_DATA_ZI);

  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }
  /* DWARF 3 */
  .debug_pubtypes 0 : { *(.debug_pubtypes) }
  .debug_ranges   0 : { *(.debug_ranges) }
  .gnu.attributes 0 : { KEEP (*(.gnu.attributes)) }
  .note.gnu.arm.ident 0 : { KEEP (*(.note.gnu.arm.ident)) }
  /DISCARD/ : { *(.ARM.exidx*) *(.note.GNU-stack) *(.gnu_debuglink) *(.gnu.lto_*) *(.init) *(.fini) }
}
