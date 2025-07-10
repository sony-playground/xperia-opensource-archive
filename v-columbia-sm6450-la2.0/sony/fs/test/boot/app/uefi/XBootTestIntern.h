/*
 * Copyright (c) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef __X_BOOT_TEST_INTERN__H__
#define __X_BOOT_TEST_INTERN__H__

#include <Uefi.h>
#include <Base.h>
#include <Protocol/SimpleTextOut.h>

/* Needed bu log functions */
UINTN AsciiInternalPrint(
	IN CONST CHAR8 *Format,
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL * Console,
	IN VA_LIST Marker
);

#endif
