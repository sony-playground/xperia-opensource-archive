/****************************************************************************
 Copyright (c) 2018, 2021 Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
08/12/21   ck           Initial version
================================================================================*/

#include "ddr_shared_interface.h"


void CORE_SW_DCB_Init(DDR_SHARED_STRUCT *ddr_shared_ptr)
{
}

void CORE_SW_DCB_Set_DDR_AOP_PARAMS(DDR_SHARED_STRUCT *ddr_shared_ptr)
{
}

uint8 CORE_SW_Get_Nearest_Enabled_Clock_Index(FREQ_STATE *freq_states, uint8 num_levels, uint32 freq_khz)
{
  return 1;
}

void CORE_SW_Set_Initial_Clock_Indices(DDR_SHARED_STRUCT *ddr_shared_ptr, uint32 ddr_khz, uint32 shub_khz, uint32 shrm_khz)
{
}

void CORE_SW_Set_Config(uint32 base_addr, uint16 reg_cnt, uint32 (*reg_offset_val_ptr)[2])
{
}

void CORE_SW_Set_PASR_DDR_INFO_TABLE(DDR_SHARED_STRUCT *ddr_shared_ptr)
{
}

uint32 CORE_SW_Get_Training_Checksum(DDR_SHARED_STRUCT *ddr_shared_ptr, uint32 seed)
{
  return 0;
}

void CORE_SW_Stack_Fill(void)
{
}

uint32 CORE_SW_Stack_Usage(void)
{
  return 0;
}

void CORE_SW_TRN_FRWK_Run_Switchboard(DDR_SHARED_STRUCT *ddr_shared_ptr, CORE_SW_TRN_SWITCHBOARD_STRUCT switchboard[MAX_NUM_TRAININGS])
{
}

void CORE_SW_Value_String(char *string, size_t length, uint32 value)
{
}

void CORE_SW_DDR_Abort_Info_Print(DDR_ABORT_STRUCT *ddr_abort_ptr, char *prefix, uint32 severity)
{
}

void CORE_SW_DDR_Print_and_Abort(DDR_SHARED_STRUCT *ddr_shared_ptr)
{
}
