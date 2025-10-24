/*******************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2019,2022 Qualcomm Technologies Incorporated.
 All rights reserved.
 ******************************************************************************/
/*==============================================================================
$Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Kailua/Library/DSFTargetLib/interface/header/api/ddr_fw_func.h#1 $
$DateTime: 2022/08/18 10:15:46 $
$Author: pwbldsvc $
==============================================================================*/

#ifndef __DDR_FW_FUNC_H__
#define __DDR_FW_FUNC_H__

#include "ddr_shared_interface.h"

void DDR_FW_Enter(void *buffer_ptr, size_t size);
DDR_SHARED_STRUCT* DDR_FW_Get_DDR_SHARED_STRUCT_Pointer(void);
void DDR_FW_Init(void);
void DDR_FW_Init_APPs(void);
void DDR_FW_Train(void);
void DDR_FW_Restore(void);
void DDR_FW_Exit(void);

// Frequency Switch
void DDR_FW_DDR_Freq_Switch_Prework(uint8 new_clk_idx);
void DDR_FW_DDR_Freq_Switch_Work(uint8 new_clk_idx);
void DDR_FW_DDR_Freq_Switch_Postwork(uint8 new_clk_idx);

// SDI
void DDR_FW_SDI_Get_Version(DSF_VERSION_STRUCT *dsf_version);
void DDR_FW_SDI_Recover(void);
void DDR_FW_SDI_Dump(void *buffer_ptr, size_t size);

// eCDT (used by DDI for providing QDUTT information)
int DDR_FW_eCDT_Get_Voltage_Override_Values(uint8 clk_idx, uint32 *buffer_ptr, size_t size);
int DDR_FW_eCDT_Get_Interface_Parameter_Values(uint8 clk_idx, uint32 *buffer_ptr, size_t size);
int DDR_FW_eCDT_Get_AC_Timing_Values(uint32 *buffer_ptr, size_t size);
int DDR_FW_eCDT_Get_Safe_Mode_Values(uint32 *buffer_ptr, size_t size);

// MC (used by DDI for reading mode register values)
uint32 DDR_FW_MC_MR_Read(uint8 channel, uint8 rank, uint32 address);

// MC (used by DDI for DRAM retention testing)
void DDR_FW_MC_Auto_Refresh_Ctrl(uint8 enable);
void DDR_FW_MC_Enter_Self_Refresh(void);
void DDR_FW_MC_Exit_Self_Refresh(void);

// X,Y Offset (used by DDI for margin testing)
void DDR_FW_Axis_Offset_Init(uint8 clk_idx);
boolean DDR_FW_X_Axis_Offset_CA(int offset);
boolean DDR_FW_Y_Axis_Offset_CA(int offset);
boolean DDR_FW_X_Axis_Offset_RD(int offset);
boolean DDR_FW_Y_Axis_Offset_RD(int offset);
boolean DDR_FW_X_Axis_Offset_WR(int offset);
boolean DDR_FW_Y_Axis_Offset_WR(int offset);

// X,Y Plot (used by DDI for providing QDUTT information)
boolean DDR_FW_XY_Plot_CA(uint8 clk_idx, uint32* ddi_data_offset_ptr, uint8 x_step, uint8 y_step);
boolean DDR_FW_XY_Plot_RD(uint8 clk_idx, uint32* ddi_data_offset_ptr, uint8 x_step, uint8 y_step);
boolean DDR_FW_XY_Plot_WR(uint8 clk_idx, uint32* ddi_data_offset_ptr, uint8 x_step, uint8 y_step);

// IOCTL
int DDR_FW_IOCTL(int cmd, void *arg, size_t size);

#endif /* __DDR_FW_FUNC_H__ */
 
