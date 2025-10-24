# 1 "/local/mnt/workspace/CRMBuilds/AOP.HO.5.0-00285-KAILUA_E-1_20221205_024556/b/HY11_1/aop_proc/core/kernel/rex/target/kailua/aop_devcfg.scl"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 358 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/local/mnt/workspace/CRMBuilds/AOP.HO.5.0-00285-KAILUA_E-1_20221205_024556/b/HY11_1/aop_proc/core/kernel/rex/target/kailua/aop_devcfg.scl" 2
# 19 "/local/mnt/workspace/CRMBuilds/AOP.HO.5.0-00285-KAILUA_E-1_20221205_024556/b/HY11_1/aop_proc/core/kernel/rex/target/kailua/aop_devcfg.scl"
PHDRS
{
  AOPSS_DEVCFG_DATA PT_LOAD;
  AOPSS_DEVCFG_CODE PT_LOAD;
}

SECTIONS
{






   AOPSS_DEVCFG_DATA_TOP 0x81C80000:
  {
    *(aop_devcfg_top_sec)
  } : AOPSS_DEVCFG_DATA

  AOPSS_DEVCFG_DATA_REST:
  {
    *(.data .data*)
    *(.bss .bss*)
    KEEP(*\devcfg_main.o(.data*))

    *(pm_ddr_reclaim_pool)
    *(pm_dram_reclaim_pool)
  } : AOPSS_DEVCFG_DATA

  . = ALIGN(0x1000);







  AOPSS_DEVCFG_CODE_ALL :
  {
    *(InRoot$$Sections .text .text*)
    *(.rodata .rodata*)
  } : AOPSS_DEVCFG_CODE

  __aop_devcfg_size_left = 0x81CA0000 - .;

  AOPSS_DEVCFG_CODE_ZI:
  {
    . = . + __aop_devcfg_size_left;
  } : AOPSS_DEVCFG_CODE
  ASSERT(. <= 0x81CA0000, "Overflow past AOP_DEVCFG_END");

  /DISCARD/ :
  {
    * (.ARM.extab*)
    * (.ARM.exid*)
    * (.got)
  }

}
