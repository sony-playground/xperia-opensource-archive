/*
 * Copyright (c) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <XBootTest.h>
#include <Uefi.h>

/* MicroSecondDelay*/
#include <Library/TimerLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/ShutdownServices.h>
#include <Library/XBootPALApiLib.h>
#include "xboot_pal_types.h"
#include <Library/TaApi.h>
#include <Library/MazeLib.h>
#include <Library/XResetReasonApiLib.h>
#include <Library/XResetReasonDefs.h>
#include <Library/XRestartReasonLib.h>
#include <Library/StartFlagApiLib.h> /* CheckFirstBoot */

#include <Library/ResetCfgProtocolWrapper.h>

/* XDEBUG */
#include <Library/XUtilLib.h>
#include <Library/PrintLib.h>

/* Internal */
#include <XBootTestIntern.h>

/* General fcs/main */
#include "fcsenv_def.h"
#include "fcs_defines.h"
#include "fcslog.h"
#include "fcserr.h"

/* Test Framework*/
#include "iterator.h"
#include "gen_tests.h"
#include "integration_uefi.h"

#define ARG_COUNT_MAX 10

/* Internal functions */
STATIC VOID XBootTestCmdLoop(IN EFI_SYSTEM_TABLE * SystemTable, CHAR8 Char);
STATIC VOID ParseCommand(CHAR8 * Command,
		UINT32 * Argc, CHAR8 * Argv[], UINT32 MaxArg);
STATIC VOID ApplyHWState(CHAR8 * StartupBitsStr, CHAR8 * WBReasonStr);
STATIC VOID Execute(UINT32 Argc, CHAR8 * Argv[]);
STATIC VOID TcList(VOID);
STATIC VOID PONState(VOID);
STATIC VOID USBState(VOID);
STATIC VOID ColdBoot(VOID);


/* Framework callback functions */
static void xboottest_export_tcstate(
		struct iterator_tcstate *tcstate);
static void xboottest_export_hwstate(
		struct integration_hwstate *state);
static void testlog(const char *fmt, ...);
static void intlog(const char *fmt, ...);

VOID EFIAPI XBootTestMain(IN EFI_SYSTEM_TABLE * SystemTable)
{
	EFI_STATUS Status;
	EFI_INPUT_KEY Key;
	CHAR8 Char = 0;

	fcslog("XBoot Tester\n");
	fcslog("XBootTest>");
	while (Char == 0) {
		Status = SystemTable->ConIn->ReadKeyStroke(
			SystemTable->ConIn, &Key);
		if (!EFI_ERROR(Status))
			Char = (CHAR8)Key.UnicodeChar;
		MicroSecondDelay(10000);
	}
	if (Char != 0) {
		(void)MazeStop();

		XBootTestCmdLoop(SystemTable, Char);
	}
	fcslog("XBoot Test End\n");
}

STATIC VOID XBootTestCmdLoop(IN EFI_SYSTEM_TABLE * SystemTable, CHAR8 Char)
{
	EFI_STATUS Status;
	EFI_INPUT_KEY Key;
	CHAR8 Cmd[256];
	UINTN CmdIdx = 0;
	UINT32 Argc = 0;
	CHAR8 *Argv[ARG_COUNT_MAX];

	Status = XBootPALApiInit();
	if (Status != EFI_SUCCESS) {
		DEBUG((EFI_D_ERROR, "XBootPALApiInit returned error %r\n",
			Status));
		return;
	}

	Status = Ta_Init();
	if (Status != EFI_SUCCESS) {
		DEBUG((EFI_D_ERROR, "Ta_Init returned error %r\n", Status));
		return;
	}

	CmdIdx = 0;
	Cmd[CmdIdx] = 0;
	while (1) {
		while ((Char != '\r') &&
				(Char != '\n') &&
				(CmdIdx < sizeof(Cmd) - 1)) {
			if (Char != 0) {
				Cmd[CmdIdx] = Char;
				CmdIdx++;
				Cmd[CmdIdx] = 0;
			}
			Status = SystemTable->ConIn->ReadKeyStroke(
				SystemTable->ConIn, &Key);
			if (!EFI_ERROR(Status)) {
				Char = (CHAR8)Key.UnicodeChar;
			} else {
				Char = 0;
				MicroSecondDelay(10000);
			}
		}
		Char = 0;
		ParseCommand(Cmd, &Argc, Argv, ARG_COUNT_MAX);
		if (Argc > 0) {
			if (AsciiStrnCmp(Argv[0],
					"shutdown",
					AsciiStrLen("shutdown")) == 0) {
				ShutdownDevice();
			} else if (AsciiStrnCmp(Argv[0],
					"hwstate",
					AsciiStrLen("hwstate")) == 0) {
				if (Argc == 3) {
					ApplyHWState(Argv[1], Argv[2]);
				} else {
					fcslog(
					"Unexpected number of arguments\n");
				}
			} else if (AsciiStrnCmp(Argv[0],
					"execute",
					AsciiStrLen("execute")) == 0) {
				Execute(Argc, Argv);
			} else if (AsciiStrnCmp(Argv[0],
					"list", AsciiStrLen("list")) == 0) {
				TcList();
			} else if (AsciiStrnCmp(Argv[0],
					"pon", AsciiStrLen("pon")) == 0) {
				PONState();
			} else if (AsciiStrnCmp(Argv[0],
					"usb", AsciiStrLen("usb")) == 0) {
				USBState();
			} else if (AsciiStrnCmp(Argv[0],
					"coldboot",
					AsciiStrLen("coldboot")) == 0) {
				ColdBoot();
			}
		}
		Cmd[0] = 0;
		CmdIdx = 0;
		Char = 0;
		fcslog("\nXBootTest>");
	}
}

STATIC VOID ParseCommand(CHAR8 *Command,
	UINT32 *Argc, CHAR8 *Argv[], UINT32 MaxArg)
{
	UINTN i, j, begin, CmdLen;

	CmdLen = AsciiStrLen(Command);
	begin = 0;
	j = 0;
	for (i = 0; ((i < CmdLen) &&
				(begin < CmdLen) &&
				(j < MaxArg)); i++) {
		if ((begin < i) && (Command[begin] == '"')) {
			/* In Quoted argument */
			if (Command[i] == '"') {
				Argv[j] = &Command[begin + 1];
				j++;
				Command[i] = 0; /* NULL terminate */
				begin = i + 1;
			}
		} else if (begin < i) {
			/* In argument */
			if ((Command[i] == ' ') ||
					(Command[i] == '\r') ||
					(Command[i] == '\n')) {
				Argv[j] = &Command[begin];
				j++;
				Command[i] = 0; /* NULL terminate */
				begin = i + 1;
			}
		} else {
			/* Between arguments */
			if (Command[i] == '"') {
				begin = i;
			} else if ((Command[i] == ' ') ||
					(Command[i] == '\r') ||
					(Command[i] == '\n')) {
				Command[i] = 0; /* NULL terminate */
				begin = i + 1;
			} else {
				begin = i;
			}
		}
	}
	if ((begin < i) && (j < MaxArg) && (Command[begin] != 0)) {
		Argv[j] = &Command[begin];
		j++;
	}
	*Argc = j;
}

STATIC UINTN A2UI(CHAR8 *In)
{
	UINTN i, InLen, Res;

	InLen = AsciiStrLen(In);
	Res = 0;
	for (i = 0; i < InLen; i++) {
		if ((In[i] >= '0') && (In[i] <= '9')) {
			Res = 10 * Res;
			Res += In[i] - '0';
		} else {
			return 0;
		}
	}
	return Res;
}

STATIC UINTN A2I(CHAR8 *In)
{
	UINTN i, InLen, Res;

	InLen = AsciiStrLen(In);
	Res = 0;
	i = 0;
	while ((i < InLen) && (In[i] == ' '))
		i++;
	if (In[i] == '-')
		Res = -A2UI(&In[i+1]);
	else if ((In[i] >= '0') && (In[i] <= '9'))
		Res = A2UI(&In[i]);
	return Res;
}

STATIC VOID PONState(VOID)
{
	if (xbpal_pwr_button_pressed())
		testlog("PON:Yes\n");
	else
		testlog("PON:No\n");
}

STATIC VOID USBState(VOID)
{
	if (xbpal_usb_vbus_detect())
		testlog("USB:Yes\n");
	else
		testlog("USB:No\n");
}

STATIC VOID ColdBoot(VOID)
{
	UINT32 cur_startup_bits = xbpal_get_startup_bits();

	if ((cur_startup_bits & XBPAL_STARTUP_MASK_ONKEY) ||
			(cur_startup_bits & XBPAL_STARTUP_MASK_VBUS) ||
			(cur_startup_bits == 0))
		testlog("CB:Yes\n");
	else
		testlog("CB:No\n");
}

STATIC UINT32 TranslateWBR(enum xbpal_warmboot_t warmboot_xboot)
{
	UINT32 wb = 0;

	/*
	 * SONY_RREASON_RTC_ALARM is intentionally missing since
	 * no such use case with the reason.
	 */
	if (warmboot_xboot == XBPAL_WB_SONY_SVC) {
		wb = SONY_RREASON_XFL;
	} else if (warmboot_xboot == XBPAL_WB_FB_SVC) {
		wb = SONY_RREASON_FB;
	} else if (warmboot_xboot == XBPAL_WB_FOTA) {
		wb = SONY_RREASON_FOTA;
	} else if (warmboot_xboot == XBPAL_WB_FOTA_CACHE) {
		wb = SONY_RREASON_FOTA_CACHE;
	} else if (warmboot_xboot == XBPAL_WB_FOTA_CRASH) {
		wb = SONY_RREASON_FOTA_CRASH;
	} else if (warmboot_xboot == XBPAL_WB_FOTA_HWWD) {
		wb = SONY_RREASON_FOTA_HWWD;
	} else if (warmboot_xboot == XBPAL_WB_NORMAL) {
		wb = SONY_RREASON_NORMAL;
	/*
	 * Currently recovery reason goes to normal kernel due to
	 * conflict with master reset.
	 * It will go to recovery after SOMC master reset solution is
	 * replaced with GOTA
	 *
	 * } else if (warmboot_xboot == SONY_RREASON_RECOVERY_MODE) {
	 *	 wb = XBPAL_WB_NORMAL;
	 */
	} else if (warmboot_xboot == XBPAL_WB_CRASH) {
		wb = SONY_RREASON_CRASH;
	} else if (warmboot_xboot == XBPAL_WB_RD_OK) {
		wb = SONY_RREASON_REBOOT_RD_OK;
	} else if (warmboot_xboot == XBPAL_WB_CRASH_ND) {
		wb = SONY_RREASON_NO_RD_IMAGE;
	} else if (warmboot_xboot == XBPAL_WB_RD_DECFAIL_NO_TL) {
		wb = SONY_RREASON_RD_DECFAIL_NO_TL;
	} else if (warmboot_xboot == XBPAL_WB_RD_DECFAIL_PART_TL) {
		wb = SONY_RREASON_RD_DECFAIL_PART_TL;
	} else if (warmboot_xboot == XBPAL_WB_RD_CRASH_EARLY_HWWD) {
		wb = SONY_RREASON_RD_EARLY_CRASH_HWWD;
	} else if (warmboot_xboot == XBPAL_WB_RD_CRASH_LATE_HWWD) {
		wb = SONY_RREASON_RD_CRASH_HWWD;
	} else if (warmboot_xboot == XBPAL_WB_RD_NO_SPACE) {
		wb = SONY_RREASON_RD_NO_SPACE;
	} else if (warmboot_xboot == XBPAL_WB_REBOOT_RD_CRASH) {
		wb = SONY_RREASON_REBOOT_RD_CRASH;
	} else if (warmboot_xboot == XBPAL_WB_REBOOT_RD_APPERR) {
		wb = SONY_RREASON_REBOOT_RD_APPERR;
	} else if (warmboot_xboot == XBPAL_WB_DMV_EIO) {
		wb = SONY_RREASON_DM_VERITY_LOG;
	} else if (warmboot_xboot == XBPAL_WB_DMV_ENFORCE) {
		wb = SONY_RREASON_DM_VERITY_ENF;
	} else if (warmboot_xboot == XBPAL_WB_DMV_KEYCLEAR) {
		wb = SONY_RREASON_DM_VERITY_KEYSCLEAR;
	} else if (warmboot_xboot == XBPAL_WB_CLEAR) {
		wb = SONY_RREASON_CLEAR;
	} else if (warmboot_xboot == XBPAL_WB_SYSTEM) {
		wb = SONY_RREASON_SYSTEM;
	} else if (warmboot_xboot == XBPAL_WB_NONE) {
		wb = SONY_RREASON_NONE;
	}

	return wb;
}

STATIC VOID ApplyHWState(CHAR8 *StartupBitsStr, CHAR8 *WBReasonStr)
{
	UINT32 StartupBits = A2UI(StartupBitsStr);
	UINT32 WBReason = A2UI(WBReasonStr);

	testlog("StartupBits: 0x%x\n", StartupBits);
	testlog("WBReason: 0x%x\n", WBReason);

	if ((StartupBits & XBPAL_STARTUP_MASK_ONKEY) ||
			(StartupBits & XBPAL_STARTUP_MASK_VBUS))
		gRT->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, NULL);
	else if (StartupBits & XBPAL_STARTUP_MASK_PLF_CRASHES) {
		SetSonyResetReason(TranslateWBR(WBReason));
		SetSonyRestartReason(TranslateWBR(WBReason));
		ResetCfgHardReset();
		gRT->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
	} else if (StartupBits & XBPAL_STARTUP_MASK_HARD_RESET) {
		SetSonyResetReason(TranslateWBR(WBReason));
		SetSonyRestartReason(TranslateWBR(WBReason));
		gRT->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
	}
}

STATIC VOID Execute(UINT32 Argc, CHAR8 *Argv[])
{
	int res = FCSERR_OK;
	struct iterator_info *it = NULL;
	struct iterator_tcstate TcState;
	struct iterator_tcstate *TcStatePtr = NULL;
	char *match = "";

	if ((Argc != 1) &&
			(Argc != 2) &&
			(Argc != 5) &&
			(Argc != 6)) {
		fcslog("Unexpected number of arguments\n");
		return;
	}

	if (Argc == 5) {
		TcState.n_failed = A2UI(Argv[1]);
		TcState.n_executed = A2UI(Argv[2]);
		TcState.next_module = A2UI(Argv[3]);
		TcState.next_module_item = A2I(Argv[4]);
		TcStatePtr = &TcState;
	} else if (Argc == 6) {
		/* match */
		TcState.n_failed = A2UI(Argv[2]);
		TcState.n_executed = A2UI(Argv[3]);
		TcState.next_module = A2UI(Argv[4]);
		TcState.next_module_item = A2I(Argv[5]);
		TcStatePtr = &TcState;
	}

	if ((Argc == 2) || (Argc == 6))
		match = Argv[1];

	res = setup_iterator(&it, TcStatePtr, xboottest_export_tcstate);
	if (res != FCSERR_OK) {
		fcslog("Failed to create test iterator!\n");
		goto exit;
	}
	res = setup_modules(it);
	if (res != FCSERR_OK) {
		fcslog("Failed to setup_modules!\n");
		goto exit;
	}

	res = integration_uefi_setup(intlog,
				it, xboottest_export_hwstate);
	if (res != FCSERR_OK) {
		fcslog("Failed to setup integration!\n");
		goto exit;
	}

	res = execute_module(testlog, it, match);
	if (res != FCSERR_OK) {
		fcslog("Function execute_module failed!\n");
		goto exit;
	}

	if (!more_modules(it))
		testlog("execute_module done! n_failed:%d, n_executed:%d\n",
			get_n_failed(it), get_n_executed(it));

exit:
	integration_uefi_teardown();
	teardown_iterator(it);
}

STATIC VOID TcList(VOID)
{
	int res = FCSERR_OK;
	struct iterator_info *it = NULL;

	res = setup_iterator(&it, NULL, xboottest_export_tcstate);
	if (res != FCSERR_OK) {
		fcslog("Failed to create test iterator!\n");
		goto exit;
	}
	res = setup_modules(it);
	if (res != FCSERR_OK) {
		fcslog("Failed to setup_modules!\n");
		goto exit;
	}

	print_modules(fcslog, it);

exit:
	teardown_iterator(it);
}

/* Framework callback functions */
static void xboottest_export_tcstate(
		struct iterator_tcstate *tcstate)
{
	fcslog("\nPARAM TCSTATE <<<<<<\n");
	if (tcstate != NULL) {
		fcslog("%u %u %u %d",
			tcstate->n_failed,
			tcstate->n_executed,
			tcstate->next_module,
			tcstate->next_module_item);
	}
	fcslog("\n>>>>>>> TCSTATE PARAM\n");
}

static void xboottest_export_hwstate(
		struct integration_hwstate *state)
{
	fcslog("\nPARAM HWSTATE <<<<<<\n");
	if (state != NULL) {
		fcslog("%u %u %u %u %u %u %u %u",
			state->startup_flags,
			state->wb_reason,
			state->reset_detect,
			state->usb_vbus_detect,
			state->usb_otg_detect,
			state->pwr_button_pressed_time,
			state->vldwn_button_pressed_time,
			state->vlup_button_pressed_time);
	}
	fcslog("\n>>>>>>> HWSTATE PARAM\n");
}

static void testlog(const char *fmt, ...)
{
	CHAR8 *Result = NULL;
	VA_LIST arg;

	VA_START(arg, fmt);

	fcslog("\nTEST <<<<<<\n");
	/*
	 * UEFI does not follow ANSI C. %s stands for
	 * Unicode string, and %a stands for ASCII string.
	 * Replace all %s occurences with %a
	 */
	Result = XReplace(fmt, "%s", "%a");
	if (Result) {
		AsciiInternalPrint(Result, gST->ConOut, arg);
		gBS->FreePool(Result);
	} else {
		AsciiInternalPrint(fmt, gST->ConOut, arg);
	}
	fcslog(">>>>>>> TEST\n\n");
	VA_END(arg);
}

static void intlog(const char *fmt, ...)
{
	CHAR8 *Result = NULL;
	VA_LIST arg;

	VA_START(arg, fmt);

	fcslog("\nINTEGRATION <<<<<<\n");
	/*
	 * UEFI does not follow ANSI C. %s stands for
	 * Unicode string, and %a stands for ASCII string.
	 * Replace all %s occurences with %a
	 */
	Result = XReplace(fmt, "%s", "%a");
	if (Result) {
		AsciiInternalPrint(Result, gST->ConOut, arg);
		gBS->FreePool(Result);
	} else {
		AsciiInternalPrint(fmt, gST->ConOut, arg);
	}
	fcslog(">>>>>>> INTEGRATION\n\n");
	VA_END(arg);
}

