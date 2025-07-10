# 1 "/local/mnt/workspace/CRMBuilds/AOP.HO.4.0-00571-WAIPIO_E-1_20231026_070056/b/HY11_1/aop_proc/core/kernel/rex/target/waipio/aop_devcfg.scl"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 355 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/local/mnt/workspace/CRMBuilds/AOP.HO.4.0-00571-WAIPIO_E-1_20231026_070056/b/HY11_1/aop_proc/core/kernel/rex/target/waipio/aop_devcfg.scl" 2
# 19 "/local/mnt/workspace/CRMBuilds/AOP.HO.4.0-00571-WAIPIO_E-1_20231026_070056/b/HY11_1/aop_proc/core/kernel/rex/target/waipio/aop_devcfg.scl"
PHDRS
{
  AOPSS_DEVCFG_DATA PT_LOAD;
  AOPSS_DEVCFG_CODE PT_LOAD;
}

SECTIONS
{






   AOPSS_DEVCFG_DATA_TOP 0x80880000:
  {
    *(aop_devcfg_top_sec)
  } : AOPSS_DEVCFG_DATA

  AOPSS_DEVCFG_DATA_REST:
  {
    *(.data .data*)
    *(.bss .bss*)
    *(pm_ddr_reclaim_pool)
    *(pm_dram_reclaim_pool)
    KEEP(*\devcfg_main.o(.data*))
  } : AOPSS_DEVCFG_DATA

  . = ALIGN(0x1000);







  AOPSS_DEVCFG_CODE_ALL :
  {
    *(InRoot$$Sections .text .text*)
    *(.rodata .rodata*)
  } : AOPSS_DEVCFG_CODE

  __aop_devcfg_size_left = 0x808A0000 - .;
  AOPSS_DEVCFG_CODE_ZI:
  {
    . = . + __aop_devcfg_size_left;
  } : AOPSS_DEVCFG_CODE

  /DISCARD/ :
  {
    * (.ARM.extab*)
    * (.ARM.exid*)
    * (.got)
  }

}
