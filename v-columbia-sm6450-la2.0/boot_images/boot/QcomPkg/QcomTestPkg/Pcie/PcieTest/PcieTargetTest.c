/** @file PcieTargetTest.c
#
#  Pcie target specific tests
#
#  Copyright (c) 2020 - 2021 Qualcomm Technologies, Inc. All rights reserved.
#
#==============================================================================
#                              EDIT HISTORY
#
#
# when         who     what, where, why
# ----------   ---     ----------------------------------------------------------
# 03/09/2020   yg      Initial Revision
#==============================================================================
#**/

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include "pcie_host_r.h"
#include "PcieTest_i.h"
#include <Protocol/EfiQcPcie.h>
#include <Library/pcie_rp.h>
#include <Library/PcieTestUtils.h>
#include <string.h>

EFI_STATUS TargetPlatformOptionSelect (UINTN Argc, CHAR8** Argv, UINT32* ArgsConsumedPtr)
{
   // No special options for Waipio
   return EFI_SUCCESS;
}

typedef struct
{
   UINT32  core_idx;
   int     test;
   int     argc;
   char*   argv[4];
}test_info_type;

test_info_type ld_test[] =
{
   {0, LOCAL_DIGITAL_TEST, 0, {NULL},},
   {1, LOCAL_DIGITAL_TEST, 0, {NULL},},

   {0, LOCAL_DIGITAL_TEST, 2, {"ls", "3"},},
   {0, LOCAL_DIGITAL_TEST, 2, {"ls", "2"},},
   {0, LOCAL_DIGITAL_TEST, 2, {"ls", "1"},},


   {1, LOCAL_DIGITAL_TEST, 2, {"ls", "3"},},
   {1, LOCAL_DIGITAL_TEST, 2, {"ls", "2"},},
   {1, LOCAL_DIGITAL_TEST, 2, {"ls", "1"},},
   {1, LOCAL_DIGITAL_TEST, 4, {"ls", "4", "lw", "1"},},
   {1, LOCAL_DIGITAL_TEST, 4, {"ls", "3", "lw", "1"},},
   {1, LOCAL_DIGITAL_TEST, 4, {"ls", "2", "lw", "1"},},
   {1, LOCAL_DIGITAL_TEST, 4, {"ls", "1", "lw", "1"},},
};

test_info_type la_test[] =
{
   {0, LOCAL_ANALOG_TEST, 0, {NULL},},
   {1, LOCAL_ANALOG_TEST, 0, {NULL},},

   {0, LOCAL_ANALOG_TEST, 2, {"ls", "3"},},
   {0, LOCAL_ANALOG_TEST, 2, {"ls", "2"},},
   {0, LOCAL_ANALOG_TEST, 2, {"ls", "1"},},


   {1, LOCAL_ANALOG_TEST, 2, {"ls", "3"},},
   {1, LOCAL_ANALOG_TEST, 2, {"ls", "2"},},
   {1, LOCAL_ANALOG_TEST, 2, {"ls", "1"},},
   {1, LOCAL_ANALOG_TEST, 4, {"ls", "4", "lw", "1"},},
   {1, LOCAL_ANALOG_TEST, 4, {"ls", "3", "lw", "1"},},
   {1, LOCAL_ANALOG_TEST, 4, {"ls", "2", "lw", "1"},},
   {1, LOCAL_ANALOG_TEST, 4, {"ls", "1", "lw", "1"},},
};

test_info_type rl_test[] =
{

   {0, REMOTE_DIGITAL_TEST, 0, {NULL},},

   {0, REMOTE_DIGITAL_TEST, 2, {"ls", "3"},},
   {0, REMOTE_DIGITAL_TEST, 2, {"ls", "2"},},
   {0, REMOTE_DIGITAL_TEST, 2, {"ls", "1"},},
};

test_info_type aux_tests[] =
{
   {0, L0_TEST, 0, {NULL},},
   {0, MEMIO_TEST, 0, {NULL},},
   {0, EPCFG_TEST, 0, {NULL},},
};

void run_test_list (test_info_type* test_list, uint32 cnt)
{
   int i, core, test, argc;
   char** argv;

   for (i=0; i < cnt; ++i)
   {
      core = test_list[i].core_idx;
      test = test_list[i].test;
      argc = test_list[i].argc;
      argv = test_list[i].argv;

      switch (test)
      {
         case LOCAL_ANALOG_TEST:
         case LOCAL_DIGITAL_TEST:
           RunLoopbackTest (argc, argv, core, NULL, test);
           break;

         case REMOTE_DIGITAL_TEST:
           RunLoopbackTest (argc, argv, core, NULL, test);
           gBS->Stall (100000);
           break;

         case L0_TEST:
           RunASPMTest (core, ASPM_TYPE_L0s);
           break;

         case MEMIO_TEST:
           RunMemIOTest (core);
           break;

         case EPCFG_TEST:
           RunCfgSpaceTest (core);
           break;

         default:
           break;
      }

   }
}

void run_all_local_digital (void)
{
   run_test_list (ld_test, ARRAY_SIZE(ld_test));
}

void run_all_local_analog (void)
{
   run_test_list (la_test, ARRAY_SIZE(la_test));
}

void run_all_remote (void)
{
   run_test_list (rl_test, ARRAY_SIZE(rl_test));
}

void run_all_predefined (void)
{
   run_all_local_digital();
   run_all_local_analog();
   run_all_remote();

   run_test_list (aux_tests, ARRAY_SIZE(aux_tests));
}



