/*
 * Copyright 2021 Sony Corporation.
 * All rights, including trade secret rights, reserved.
 */

/*
 * xboot_print_oem_rr
 *   print OEM RESET REASON value
 */

void xboot_print_oem_rr(void);


/*
 * xboot_print_temp
 *   print current templature
 */

void xboot_print_temp(void);


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
void xboot_print_info_corner(void);
