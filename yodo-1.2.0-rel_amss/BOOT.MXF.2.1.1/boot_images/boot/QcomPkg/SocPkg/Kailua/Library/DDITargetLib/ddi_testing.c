/**
 * @file ddi_testing.c
 * @brief
 * DDI testing entry point
 */
/*=============================================================================

                                DDI Test cases
                                Source File
GENERAL DESCRIPTION
This file defines the entry point for DDI testing

  Copyright (c) 2016-2017,2020-2022 QUALCOMM Technologies Incorporated.
  All rights reserved.
  Qualcomm Confidential and Proprietary.
===============================================================================

===============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

===============================================================================
when       who     what, where, why
--------   ---     ------------------------------------------------------------
07/19/17   na      Initial version
==============================================================================*/

/*==============================================================================
                                  INCLUDES
==============================================================================*/
#include <string.h>

#include "boot_util.h"
#include "ddr_external.h"
#include "ddr_params.h"
#include "boot_crashdump.h"
#include "ddi_drivers.h"
#include "ddi_testing.h"
#include "ddi_flash_params.h"

/*==============================================================================
                                  DATA
==============================================================================*/

extern ddi_test_case_func test_case_list[];
extern uint8 ddi_number_of_cmds;

// output report counter
//Reservation for storing DDI Cookie
uint64 ddi_report_offset = 4; //(uint32)

#if DDI_PRINT_ENABLE
char ddi_log_string[100];
#endif

/*==============================================================================
                                  FUNCTIONS
==============================================================================*/


/* ============================================================================
**  Function : ddi_run_command_setparam
** ============================================================================
*/
/*!
*   @brief
*   This function is called to do nothing
*
*   @param None
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/

void ddi_run_command_setparam(void);


#if defined FEATURE_BOOT_DDI_ENABLE
/* ============================================================================
**  Function : ddi_rhd_command
** ============================================================================
*/
/*!
*   @brief
*   based on input command ID, Add amount of header for skipping
*
*   @param cmd         -   [IN] pointer to DCB data for command header
*   @param input_iter  -   [IN] pointer to current DCB offset
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/

void ddi_rhd_command(ddi_command_header* cmd, uint64* input_iter)
{
  switch(cmd->cmd_id)
  {
    case 0: //    {DDI_POST_DDR_STEP, ddi_run_command_rd}
      *input_iter += sizeof(ddi_rd_params);
    break;
    case 1: //    {DDI_POST_DDR_STEP, ddi_run_command_wr}
      *input_iter += (((ddi_wr_params*)(*input_iter))->pattern_size*sizeof(uint64));
      *input_iter += sizeof(ddi_wr_params);
    break;
    case 2: //    {DDI_POST_DDR_STEP, ddi_run_command_rdwr}
      *input_iter += (((ddi_rdwr_params*)(*input_iter))->pattern_size*sizeof(uint64));
      *input_iter += sizeof(ddi_rdwr_params);
    break;
    case 3: //    {DDI_POST_DDR_STEP, ddi_run_command_delay}
      *input_iter += sizeof(ddi_delay_params);
    break;
    case 4: //    {DDI_POST_DDR_STEP, ddi_run_command_freq}
      *input_iter += sizeof(ddi_freq_params);
    break;
    case 5: //    {DDI_POST_DDR_STEP, ddi_run_command_retention}
      // not implemented
      break;
    case 6: //    {DDI_POST_DDR_STEP, ddi_run_command_plot}
      *input_iter += sizeof(ddi_plot_params);
    break;
    case 7: //    {DDI_POST_DDR_STEP, ddi_run_command_phy_update}
      *input_iter += sizeof(ddi_mod_phy_offset_params);
    break;

    case 8: //    {DDI_PRE_DDR_STEP, ddi_get_device_info}
    case 9: //    {DDI_PRE_DDR_STEP, ddi_read_ecdt_parameters}
    case 10://    {DDI_PRE_DDR_STEP, ddi_get_ac_timing}
    case 11://    {DDI_PRE_DDR_STEP, ddi_get_safe_mode_info}
    case 12://    {DDI_PRE_DDR_STEP, ddi_run_command_empty}
    case 13://    {DDI_PRE_DDR_STEP, ddi_run_command_empty}
    default:
      break;

  }
}

/* ============================================================================
**  Function : ddi_run_command
** ============================================================================
*/
/*!
*   @brief
*   based on input command ID, calls DDI test function
*
*   @param cmd         -   [IN] pointer to DCB data for command header
*   @param input_iter  -   [IN] pointer to current DCB offset
*   @param output_iter -   [IN] pointer to current DDR partition offset
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/

ddi_error ddi_run_command(ddi_command_header* cmd, uint64* input_iter, uint64* output_iter)
{
  test_case_func test;
  ddi_error ret;
  test = (test_case_func)test_case_list[cmd->cmd_id].func_ptr;
  if (test == NULL)
    ret = DDI_CMD_INVALID_INPUT;
  else
    ret = test(cmd->cmd_id, (void*)(*input_iter), output_iter);

  return ret;
}


/* ============================================================================
**  Function : ddi_run_commands
** ============================================================================
*/
/*!
*   @brief
*   high-level algorithm for running DDI test cases
*
*   @param cmds_hdr    -   [IN] pointer to DCB data for commands header
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/
ddr_ddi_result_code ddi_run_commands(ddi_commands_header* cmds_hdr, ddi_step_param step)
{
  // trackers for input and output offsets
  ddi_command_header* cmd_hdr;
  uint64 cmdpkt_pos = (uint64)((void*)cmds_hdr + sizeof(ddi_commands_header));
  uint64 output_pos = ddi_report_offset;
  uint8 num_cmds = cmds_hdr->num_cmds;
  ddr_ddi_result_code ret=DDR_DDI_SUCCESS;

  do
  {
    cmdpkt_pos = (uint64)((void*)cmds_hdr + sizeof(ddi_commands_header));
    for (uint8 i = 0; i < num_cmds; i++)
    {
      cmd_hdr = (ddi_command_header*)cmdpkt_pos;
      cmdpkt_pos += sizeof(ddi_command_header);

      if ( cmd_hdr->cmd_id >= ddi_number_of_cmds)
      {
        ret=DDR_DDI_FAIL;
      }
      else
      {
        if (test_case_list[cmd_hdr->cmd_id].ddi_step & step)
        {
          //Check buffer overread
          uint64 buf_rp = cmdpkt_pos;
		  ddi_rhd_command(cmd_hdr, &buf_rp);
		  if(buf_rp > ((uint64)ddr_external_read_ddi_binary() + ddr_external_get_ddi_binary_size()))
		  	// If DCB DDI buffer is overread, abort remaining commands and exit
		  	break;

          if(ddi_run_command(cmd_hdr, &cmdpkt_pos, &output_pos) != DDI_CMD_COMPLETE)
            ret=DDR_DDI_FAIL;
        }
        ddi_rhd_command(cmd_hdr, &cmdpkt_pos);
      }
    }
  } while(cmds_hdr->boot_id == DDI_BOOT_ID_REPEAT);

  ddi_report_offset = output_pos;

/*
  +------------+------------------------------+
  | BootID     | EDL     | HLOS     | FACTORY |
  | ddi_code   |         |          |         |
  +------------+------------------------------+
  |INCOMPLETE  | FAIL    | FAIL     | FAIL    |
  |COMPLETE    | SUCCESS | CONTINUE | SUCCESS |
  |FAIL        | FAIL    | FAIL     | FAIL    |
  |INVAL_INPUT | FAIL    | FAIL     | FAIL    |
  +------------+------------------------------+
*/
  if(ret!= DDR_DDI_FAIL && cmds_hdr->boot_id == DDI_BOOT_ID_HLOS)
    ret=DDR_DDI_CONTINUE;

  return ret;
}

/* ============================================================================
**  Function : ddr_ddi_testing
** ============================================================================
*/
/*!
*   @brief
*   checks version number and decides whether test should be run or not
*
*   @param ddi_data    -   [IN] pointer to DCB data for all DDI input
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval boolean
*
*   @sa None
*/
ddr_ddi_result_code ddr_ddi_testing(ddi_step_param step)
{
  ddr_ddi_result_code ret;
  void* ddi_data = ddr_external_read_ddi_binary();

  if (ddi_data == NULL)
    return DDR_DDI_INVALID;

  ddi_commands_header* cmds_hdr = (ddi_commands_header*)ddi_data;
  uint32 major = cmds_hdr->ddi_version >> 16;
  uint32 minor = cmds_hdr->ddi_version & 0xFF;
  if (major != DDI_MAJOR_VERSION || minor != DDI_MINOR_VERSION)
  {
    return DDR_DDI_INVALID;
  }

  ret=ddi_run_commands((ddi_commands_header*)ddi_data, step);

  return ret;
}

#endif //FEATURE_BOOT_DDI_ENABLE
/* ============================================================================
**  Function : ddi_pre_entry
** ============================================================================
*/
/*!
*   @brief
*   entry point for ddi testing
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/
void ddi_pre_entry(void)
{
#if defined FEATURE_BOOT_DDI_ENABLE
  ddr_ddi_testing(DDI_PRE_DDR_GROUP);
#endif
}

/* ============================================================================
**  Function : ddi_entry
** ============================================================================
*/
/*!
*   @brief
*   entry point for ddi testing
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/
ddi_exit_code ddi_entry(ddi_result_code *ddi_test_result_code )
{
  ddr_ddi_result_code ret=DDR_DDI_INVALID;
  ddi_exit_code exit_code = DDI_EXIT_EDL;
  ddi_mode_code ddi_mode;

#if defined FEATURE_BOOT_DDI_ENABLE

  ddi_mode = ddi_get_mode();

  if(ddi_mode==DDI_QDUTT_MODE)
  {
  ret=ddr_ddi_testing(DDI_POST_DDR_GROUP);
  if(ret==DDR_DDI_CONTINUE)
      exit_code = DDI_EXIT_HLOS;
  else
      exit_code = DDI_EXIT_EDL;	
}
  else if(ddi_mode==DDI_QDUTT_MEMTEST_MODE)
{
  ret=ddr_ddi_testing(DDI_MEMTEST_GROUP);
	exit_code = DDI_EXIT_EDL;
  }
  else if(ddi_mode==DDI_FACTORY_MODE)
  {
    ret=ddr_ddi_testing(DDI_FACTORY_GROUP);
    if (ret==DDR_DDI_SUCCESS)
	  exit_code= DDI_EXIT_RESET;
	else
	  exit_code= DDI_EXIT_EDL;	
  }
  else
  {

  	exit_code= DDI_EXIT_HLOS;
}

  if (ret==DDR_DDI_SUCCESS)
    *ddi_test_result_code= DDI_RESULT_PASS;
  else
    *ddi_test_result_code= DDI_RESULT_FAIL;

#endif

    return exit_code;
}

/* ============================================================================
**  Function : ddi_set_param
** ============================================================================
*/
/*!
*   @brief
*   set DDI parameter after DDR initialization
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/
void ddi_set_param(void)
{
  #if defined FEATURE_BOOT_DDI_ENABLE
  ddi_run_command_setparam();
  #endif
}

/* ============================================================================
**  Function : ddi_get_mode
** ============================================================================
*/
/*!
*   @brief
*   Get QDUTT DDI mode
*
*   @param None
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_mode_code
*
*   @sa None
*/
ddi_mode_code ddi_get_mode(void)
{
  ddi_mode_code ret=DDI_NOOP_MODE;

  #if defined FEATURE_BOOT_DDI_ENABLE
  void* ddi_data = ddr_external_read_ddi_binary();

  if (ddi_data == NULL)
    return DDI_NOOP_MODE;

  ddi_commands_header* cmds_hdr = (ddi_commands_header*)ddi_data;
  uint32 major = cmds_hdr->ddi_version >> 16;
  uint32 minor = cmds_hdr->ddi_version & 0xFF;
  uint8 num_cmds = cmds_hdr->num_cmds;
  uint8 boot_id = cmds_hdr->boot_id;
  if (major != DDI_MAJOR_VERSION || minor != DDI_MINOR_VERSION)
  {
    return DDI_NOOP_MODE;
  }

  if(boot_id == DDI_BOOT_ID_FACTORY) //Factory Test mode
  {
    return DDI_FACTORY_MODE;
  }

  // trackers for input and output offsets
  ddi_command_header* cmd_hdr;
  uint64 cmdpkt_pos = (uint64)((void*)cmds_hdr + sizeof(ddi_commands_header));
  ret=DDI_QDUTT_MODE;

  for (uint8 i = 0; i < num_cmds; i++)
  {
    cmd_hdr = (ddi_command_header*)cmdpkt_pos;
    cmdpkt_pos += sizeof(ddi_command_header);

    if ( cmd_hdr->cmd_id >= ddi_number_of_cmds)
    {
      ret=DDI_NOOP_MODE;
      break;
    }

    if ((test_case_list[cmd_hdr->cmd_id].ddi_step & (DDI_MEMTEST_GROUP|DDI_POST_DDR_GROUP))==DDI_MEMTEST_GROUP)
    {
      ret=DDI_QDUTT_MEMTEST_MODE;
      break;
    }
    else
    {
      ddi_rhd_command(cmd_hdr, &cmdpkt_pos);
    }
  }
#endif
  return ret;
}


/* ============================================================================
**  Function : ddi_get_DDIpartition_offset
** ============================================================================
*/
/*!
*   @brief
*   Get DDR partition offset of DDI report section
*
*   @param None
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval offset of DDR partition
*
*   @sa None
*/
uint32 ddi_get_DDIpartition_offset(void)
{
  uint32 ret=DDI_OUTPUT_SECTION_START_IN_DDR;
#if defined FEATURE_BOOT_DDI_ENABLE
  ddi_commands_header* cmds_hdr = (ddi_commands_header*)ddr_external_read_ddi_binary();

  if (cmds_hdr != NULL)
    ret= cmds_hdr->Reportoffset;
#endif
  return ret;
}


/* ============================================================================
**  Function : ddi_get_DDIpartition_size
** ============================================================================
*/
/*!
*   @brief
*   Get DDR partition size of DDI report section
*
*   @param None
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval size DDI outputsection in DDR partition
*
*   @sa None
*/
uint32 ddi_get_DDIpartition_size(void)
{
  uint32 ret=(DDI_OUTPUT_SECTION_END_IN_DDR-DDI_OUTPUT_SECTION_START_IN_DDR);
#if defined FEATURE_BOOT_DDI_ENABLE
  ddi_commands_header* cmds_hdr = (ddi_commands_header*)ddr_external_read_ddi_binary();

  if (cmds_hdr != NULL)
    ret= cmds_hdr->Reportsize;
#endif
  return ret;
}



/* ============================================================================
**  Function : ddi_get_MRpartition_offset
** ============================================================================
*/
/*!
*   @brief
*   Get DDR partition offset of MR record section
*
*   @param None
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval offset of DDR partition
*
*   @sa None
*/
uint32 ddi_get_MRpartition_offset(void)
{
  uint32 ret=DDI_OUTPUT_SECTION_START_IN_DDR;
#if defined FEATURE_BOOT_DDI_ENABLE
  ddi_commands_header* cmds_hdr = (ddi_commands_header*)ddr_external_read_ddi_binary();

  if (cmds_hdr != NULL)
    ret= cmds_hdr->MRrecordoffset;
#endif
  return ret;
}


/* ============================================================================
**  Function : ddi_get_MRpartition_size
** ============================================================================
*/
/*!
*   @brief
*   Get DDR partition size of MR record section
*
*   @param None
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval size MR record outputsection in DDR partition
*
*   @sa None
*/
uint32 ddi_get_MRpartition_size(void)
{
  uint32 ret=(DDI_OUTPUT_SECTION_END_IN_DDR-DDI_OUTPUT_SECTION_START_IN_DDR);
#if defined FEATURE_BOOT_DDI_ENABLE
  ddi_commands_header* cmds_hdr = (ddi_commands_header*)ddr_external_read_ddi_binary();

  if (cmds_hdr != NULL)
    ret= cmds_hdr->MRrecordsize;
#endif
  return ret;
}

