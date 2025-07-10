/*
 * Copyright 2021 Sony Corporation.
 * All rights, including trade secret rights, reserved.
 */

#include <Library/hw_X_target.h>

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EFITsens.h>
#include "boot_comdef.h"
#include <Library/PcdLib.h>
#include "boot_shared_imem_cookie.h" /* boot_shared_imem_cookie_ptr */

struct boot_shared_imem_cookie_type *boot_shared_imem_cookie_ptr;

/*
 * xboot_print_oem_rr
 *   print OEM RESET REASON value
 */

void xboot_print_oem_rr(void)
{
    uint32 oemrr = 0xdeadd00d;
    const char * const s[55] = {
        "NONE",
        "NON_SECURE_WDT",
        "SECURE_WDT",
        "AHB_TIMEOUT",
        "RPM_WDOG",
        "RPM_ERR",
        "NOC_ERROR",
        "BIMC_ERROR",
        "SMEM",
        "XPU_VIOLATION",
        "SMMU_FAULT",
        "QSEE_ERR",
        "EL3_SP_EL0_SYNCH",
        "EL3_SP_EL0_IRQ",
        "EL3_SP_EL0_FIQ",
        "EL3_SP_EL0_ERR",
        "EL3_SP_EL3_SYNCH",
        "EL3_SP_EL3_IRQ",
        "EL3_SP_EL3_FIQ",
        "EL3_SP_EL3_ERR",
        "EL3_LEL64_SYNCH",
        "EL3_LEL64_IRQ",
        "EL3_LEL64_FIQ",
        "EL3_LEL64_ERR",
        "EL3_LEL32_SYNCH",
        "EL3_LEL32_IRQ",
        "EL3_LEL32_FIQ",
        "EL3_LEL32_ERR",
        "EL1_SP_EL0_SYNCH",
        "EL1_SP_EL0_IRQ",
        "EL1_SP_EL0_FIQ",
        "EL1_SP_EL0_ERR",
        "EL1_SP_EL1_SYNCH",
        "EL1_SP_EL1_IRQ",
        "EL1_SP_EL1_FIQ",
        "EL1_SP_EL1_ERR",
        "EL1_LEL64_SYNCH",
        "EL1_LEL64_IRQ",
        "EL1_LEL64_FIQ",
        "EL1_LEL64_ERR",
        "EL1_LEL32_SYNCH",
        "EL1_LEL32_IRQ",
        "EL1_LEL32_FIQ",
        "EL1_LEL32_ERR",
        "RPM_DRIVER_ERR",
        "RESET_TIMER_EXP",
        "ICE_ERR",
        "LMH_DRIVER_ERR",
        "ACCESS_CONTROL",
        "CLOCK",
        "GIC_CPU_MAP_INVALID",
        "SEC_WDT_TIMER_TRIGGER",
        "FAULT_DETECTED",
        "MON_PREFETCH_ABT",
        "MON_DATA_ABT"
    };

    boot_shared_imem_cookie_ptr = (struct boot_shared_imem_cookie_type *)((UINT64)PcdGet32(PcdIMemCookiesBase));
    if (boot_shared_imem_cookie_ptr != NULL) {
        oemrr = *((uint32*)
              ((uint64)boot_shared_imem_cookie_ptr+0x7a4));
    }

    if (oemrr < 55) {
        DEBUG((EFI_D_ERROR, "OEMRR %a\n", s[oemrr]));
    }
}

/*
 * xboot_print_temp
 *   print current templature
 */

void xboot_print_temp(void)
{
    EFI_TSENS_PROTOCOL *Tsens = NULL;
    int32 nDeciDegC;
    int32 nDegC;

    EFI_STATUS Status = gBS->LocateProtocol(&gEfiTsensProtocolGuid, NULL, (VOID**)&Tsens);
    if (Status == EFI_SUCCESS) {
        if (Tsens->GetTemp(0, &nDeciDegC) == EFI_SUCCESS) {
            nDegC = nDeciDegC / 10;
            DEBUG((EFI_D_ERROR, "cpu.temp=%dC.\n", nDegC));
        }
    }
}

/*
 * xboot_print_info_corner
 *   print info after DDR memory have ready.
 *   recommended to move into informaion prints into here
 *   because IMEM LOG_BUF (SCL_SBL1_BOOT_LOG_BUF_SIZE) is
 *   really precious and limited. Here is good place after
 *   DDR LOG_BUF (SCL_SBL1_DDR_BOOT_LOG_BUF_SIZE) is ready
 *   limitation is reduced very much (but please note it's
 *   still not inifinity...)
 */
void xboot_print_info_corner(void)
{
    /* print OEMRR message if found in IMEM */
    xboot_print_oem_rr();

    /* print current templature */
    xboot_print_temp();
}
