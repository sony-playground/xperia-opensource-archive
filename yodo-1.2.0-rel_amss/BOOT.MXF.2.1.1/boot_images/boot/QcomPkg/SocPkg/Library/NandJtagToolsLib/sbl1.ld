/*=============================================================================
  
                     SCATTER LOADING DESCRIPTION FILE
  
  Copyright (c) 2020 by Qualcomm Technologies, Inc. 
  All Rights Reserved.
  
  GENERAL DESCRIPTION
  
  The scatter loading description file is used to define the NAND Programmer memory map.
=============================================================================*/
/*=============================================================================
    
                            EDIT HISTORY FOR FILE
   This section contains comments describing changes made to the module.
   Notice that changes are listed in reverse chronological order.
  
  
  when         who     what, where, why
  ----------   ---     -------------------------------------------------------
  2020-06-04    sa      Inital revision.
=============================================================================*/

/*=============================================================================
     NOTE:  The linker script name *has* to be "sbl1.ld" as the build rules
     use that name to check for linker script presence
=============================================================================*/

#include "Target_cust.h"

PHDRS {
  NAND_PROGRAMMER_CODE_ROM PT_LOAD;    
  NAND_PROGRAMMER_CODE_STACK PT_LOAD;
  NAND_PROGRAMMER_CODE_RAM PT_LOAD;
  NAND_PROGRAMMER_CODE_RAM_ZI PT_LOAD;
}

SECTIONS
{
  /*  This section of 128KB contains Nand Programmer code */
  NAND_PROGRAMMER_CODE SCL_BOOT_IMEM_BASE_ADDR: 
  {
    *nand_entry.o* (ModuleEntryPoint)
	*nand_core.o* (RO)
    *(.text .stub .text.*)
    *(ARM_MMU)
    *(RO)
    *(.gcc_except_table  .got .got.plt )
    /* RO DATA */
    *(.constdata .rodata .rodata.* .gnu.linkonce.r.*)
    ASSERT(SIZEOF(NAND_PROGRAMMER_CODE) <= SIZE_128KB, "Nand Programmer code is greater than dedicated 128KB");
  } : NAND_PROGRAMMER_CODE_ROM
  
  /* Stack location = IMEM Base + 128KB CODE_ROM + 32KB Stack */
  NAND_PROGRAMMER_STACK (SCL_BOOT_IMEM_BASE_ADDR + SIZE_128KB) : 
  {
    . = . + SIZE_128KB;
    Image$$NAND_PROGRAMMER_STACK$$Start = . ;
  } : NAND_PROGRAMMER_CODE_STACK

  /* The rest of the section contains Nand Programmer Code RAM and ZI */
  NAND_PROGRAMMER_RW :
  {
    *(.data .data.* .data1)
    *(RW)
  } : NAND_PROGRAMMER_CODE_RAM

  /**/
  NAND_PROGRAMMER_ZI :
  {
    Image$$NAND_PROGRAMMER_ZI$$Start = . ;
    *nand_entry*.o* (.bss)
    *(COMMON)
    *(.bss*)
    *(CACHE_MMU_ZI)
    *(ZI)
     ASSERT(. <= SCL_BOOT_IMEM_BASE_ADDR + SIZE_2MB, "Nand Programmer ZI is greater than dedicated ");
  } : NAND_PROGRAMMER_CODE_RAM_ZI

  NAND_PROGRAMMER_IMEM_END :
  {  
     Image$$NAND_PROGRAMMER_ZI$$End = . ;
  }
  
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
