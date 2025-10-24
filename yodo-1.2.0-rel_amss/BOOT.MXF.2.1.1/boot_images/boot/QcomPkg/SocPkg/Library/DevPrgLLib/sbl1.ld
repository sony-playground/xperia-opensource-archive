/*=============================================================================

                     SCATTER LOADING DESCRIPTION FILE

  Copyright 2022 by Qualcomm Technologies, Inc. All Rights Reserved.

  GENERAL DESCRIPTION

  The scatter loading description file is used to define the DEVPRG memory map.
=============================================================================*/
/*=============================================================================

                            EDIT HISTORY FOR FILE
   This section contains comments describing changes made to the module.
   Notice that changes are listed in reverse chronological order.


when        who       what, where, why
----------  --------  -------------------------------------------------------
2022-04-27  wkimberl  Inital version for DevPrg Lite

=============================================================================*/

#include "Target_cust.h"

PHDRS {
  ZIDATA_BUFFERS PT_LOAD;
  CODE_IMEM PT_LOAD;
  RODATA_IMEM PT_LOAD;
  STACK_IMEM PT_LOAD;
  RWDATA_IMEM PT_LOAD;
  ZIDATA_IMEM PT_LOAD;
}

SECTIONS
{
  DEVPRG_ZI_BUFFERS 0x14699000 : ALIGN(4096)
  {
    Image$$DEVPRG_ZI_BUFFERS$$Base = . ;
    devprgb_*(.bss*)
    devprgb_*(COMMON)
    . = ALIGN(4096);
    Image$$DEVPRG_ZI_BUFFERS$$End = . ;
    Image$$DEVPRG_ZI_BUFFERS$$Length = Image$$DEVPRG_ZI_BUFFERS$$End - Image$$DEVPRG_ZI_BUFFERS$$Base;
  } : ZIDATA_BUFFERS
    ASSERT(SIZEOF(DEVPRG_ZI_BUFFERS) <= SIZE_68KB, "XBLLoader: DEVPRG LITE Image Size Overflow");

/*  DEVPRG_STACK 0x14699000 : ALIGN(4096)
  {
    Image$$STACK$$Base = . ;
    . = . + SCL_STACK_SIZE;
    . = ALIGN(4096);
    Image$$STACK$$End =. ;
    Image$$STACK_BASE$$Pointer = . ;
    Image$$STACK$$Length = Image$$STACK$$End - Image$$STACK$$Base;
  } : STACK_IMEM
*/

   /*====================== Sections in BOOT IMEM ===============================*/
  /*  This section contains DEVPRG's code and ro data */
  DEVPRG_CODE SCL_DEVPRG_BASE: ALIGN(4096)
  {
    Image$$DEVPRG_CODE$$Base = . ;
    Image$$DEVPRG_VECTOR_TABLE$$Start = . ;
    *(DEVPRG_VECTOR_TABLE)
    Image$$DEVPRG_VECTOR_TABLE$$End = . ;
    *(.text* )
    . = ALIGN(4096);
    Image$$DEVPRG_CODE$$End = . ;
    Image$$DEVPRG_CODE$$Length = Image$$DEVPRG_CODE$$End - Image$$DEVPRG_CODE$$Base ;
    ASSERT((Image$$DEVPRG_VECTOR_TABLE$$End - Image$$DEVPRG_VECTOR_TABLE$$Start) <= SCL_SBL1_VECTOR_TABLE_SIZE, "DevPrg: SBL1_VECTOR_TABLE Region Overflow");
  } : CODE_IMEM

  DEVPRG_DATA_RO : ALIGN(4096)
  {
    Image$$DEVPRG_DATA_RO$$Base = . ;
    *(.rodata* )
    boot_dal.* (.data*)
    . = ALIGN(4096);
    Image$$DEVPRG_DATA_RO$$End = . ;
    Image$$DEVPRG_DATA_RO$$Length = Image$$DEVPRG_DATA_RO$$End - Image$$DEVPRG_DATA_RO$$Base ;
  } : RODATA_IMEM

  DEVPRG_DATA_RW  : ALIGN(4096)
  {
    Image$$DEVPRG_DATA_RW$$Base = . ;
    *(.data* )
    . = ALIGN(4096);
    Image$$DEVPRG_DATA_RW$$End = . ;
    Image$$DEVPRG_DATA_RW$$Length = Image$$DEVPRG_DATA_RW$$End - Image$$DEVPRG_DATA_RW$$Base;
  }:RWDATA_IMEM

  DEVPRG_STACK : ALIGN(4096)
  {
    Image$$STACK$$Base = . ;
    . = . + SCL_STACK_SIZE;
    . = ALIGN(4096);
    Image$$STACK$$End =. ;
    Image$$STACK_BASE$$Pointer = . ;
    Image$$STACK$$Length = Image$$STACK$$End - Image$$STACK$$Base;
  } : STACK_IMEM


  /*====================== Sections in DDR =========================*/

  /* This section is for DeviceProgrammer DDR buffers, they are 2MB in size.
   * Align the buffers to 2MB boundary to use L2 MMU tables to mark them
   * as Cached. They can be marked as L3 (4K) but boot has more L2 tables
   * available making it more robust. */

/*  .= Image$$DEVPRG_DATA_RW$$End ;*/
  DEVPRG_DATA_ZI :ALIGN(4096)
  {
    Image$$DEVPRG_DATA_ZI$$Base = . ;
    Image$$DEVPRG_UNCACHED_ZI$$Base = . ;
    *(.bss.DEVPRG_UNCACHED_ZI_ZONE)
    Image$$DEVPRG_UNCACHED_ZI$$End = . ;
    Image$$DEVPRG_UNCACHED_ZI$$ZI$$Length= Image$$DEVPRG_UNCACHED_ZI$$End - Image$$DEVPRG_UNCACHED_ZI$$Base;
    *(.bss*)
    *(COMMON)
    . = ALIGN(4096);
    Image$$DEVPRG_DATA_ZI$$End = . ;
    Image$$DEVPRG_DATA_ZI$$Length = Image$$DEVPRG_DATA_ZI$$End - Image$$DEVPRG_DATA_ZI$$Base;
  } : ZIDATA_IMEM
  ASSERT((SIZEOF(DEVPRG_CODE)+ SIZEOF(DEVPRG_DATA_RO) + SIZEOF(DEVPRG_STACK) + SIZEOF(DEVPRG_DATA_RW) + SIZEOF(DEVPRG_DATA_ZI) )
  <= SIZE_400KB, "XBLLoader: DEVPRG LITE Image Size Overflow");
/*    ASSERT((SIZEOF(DEVPRG_CODE)+ SIZEOF(DEVPRG_DATA_RO) + SIZEOF(DEVPRG_DATA_RW) + SIZEOF(DEVPRG_DATA_ZI) )
  <= SIZE_400KB, "XBLLoader: DEVPRG LITE Image Size Overflow"); */


  /*======================================================================*/


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
