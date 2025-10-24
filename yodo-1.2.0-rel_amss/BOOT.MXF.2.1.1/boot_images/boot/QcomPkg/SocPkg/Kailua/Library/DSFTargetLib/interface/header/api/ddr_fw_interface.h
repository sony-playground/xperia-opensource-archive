#ifndef __DDRFW_INTERFACE_H__
#define __DDRFW_INTERFACE_H__
/*
===========================================================================

FILE:         ddr_fw_interface.h

DESCRIPTION:  
   This file declare APIs that gets called by core_sw.
   ddr_fw expose APIs in this file to core_sw .

Copyright 2019,2022 by Qualcomm Technologies, Inc.  All Rights Reserved.
===========================================================================

                             Edit History


when       who       what, where, why
--------   ---       --------------------------------------------------------
01/25/19   daisond   Initial version

===========================================================================
*/
/*==============================================================================
                                  INCLUDES
==============================================================================*/
#include "ddr_shared_interface.h"

/*==============================================================================
                                  FUNCTION POINTER DECLARATIONS
==============================================================================*/
extern void (*fptr_HAL_DDR_FW_Enter)(void *buffer_ptr, size_t size);
extern void (*fptr_HAL_DDR_FW_Exit)(void);
extern DDR_SHARED_STRUCT* (*fptr_HAL_DDR_FW_Get_DDR_SHARED_STRUCT_Pointer)(void); 
extern void (*fptr_HAL_DDR_FW_Init)(void);
extern void (*fptr_HAL_DDR_FW_Train)(void);
extern void (*fptr_HAL_DDR_FW_Restore)(void);

// Frequency Switch
extern void (*fptr_HAL_DDR_FW_DDR_Freq_Switch_Prework)(uint8 new_clk_idx);
extern void (*fptr_HAL_DDR_FW_DDR_Freq_Switch_Work)(uint8 new_clk_idx);
extern void (*fptr_HAL_DDR_FW_DDR_Freq_Switch_Postwork)(uint8 new_clk_idx);

// SDI
extern void (*fptr_HAL_DDR_FW_SDI_Get_Version)(DSF_VERSION_STRUCT *dsf_version);
extern void (*fptr_HAL_DDR_FW_SDI_Recover)(void);
extern void (*fptr_HAL_DDR_FW_SDI_Dump)(void *buffer_ptr, size_t size);

// eCDT (used by DDI for providing QDUTT information)
extern int (*fptr_HAL_DDR_FW_eCDT_Get_Voltage_Override_Values)(uint8 clk_idx, uint32 *buffer_ptr, size_t size);
extern int (*fptr_HAL_DDR_FW_eCDT_Get_Interface_Parameter_Values)(uint8 clk_idx, uint32 *buffer_ptr, size_t size);
extern int (*fptr_HAL_DDR_FW_eCDT_Get_AC_Timing_Values)(uint32 *buffer_ptr, size_t size);
extern int (*fptr_HAL_DDR_FW_eCDT_Get_Safe_Mode_Values)(uint32 *buffer_ptr, size_t size);

// MC (used by DDI for reading mode register values)
extern uint32 (*fptr_HAL_DDR_FW_MC_MR_Read)(uint8 channel, uint8 rank, uint32 address);

// MC (used by DDI for DRAM retention testing)
extern void (*fptr_HAL_DDR_FW_MC_Auto_Refresh_Ctrl)(uint8 enable);
extern void (*fptr_HAL_DDR_FW_MC_Enter_Self_Refresh)(void);
extern void (*fptr_HAL_DDR_FW_MC_Exit_Self_Refresh)(void);

// X,Y Offset (used by DDI for margin testing)
extern void (*fptr_HAL_DDR_FW_Axis_Offset_Init)(uint8 clk_idx);
extern boolean (*fptr_HAL_DDR_FW_X_Axis_Offset_CA)(int offset);
extern boolean (*fptr_HAL_DDR_FW_Y_Axis_Offset_CA)(int offset);
extern boolean (*fptr_HAL_DDR_FW_X_Axis_Offset_RD)(int offset);
extern boolean (*fptr_HAL_DDR_FW_Y_Axis_Offset_RD)(int offset);
extern boolean (*fptr_HAL_DDR_FW_X_Axis_Offset_WR)(int offset);
extern boolean (*fptr_HAL_DDR_FW_Y_Axis_Offset_WR)(int offset);

// X,Y Plot (used by DDI for providing QDUTT information)
extern boolean (*fptr_HAL_DDR_FW_XY_Plot_CA)(uint8 clk_idx, uint32* ddi_data_offset_ptr, uint8 x_step, uint8 y_step);
extern boolean (*fptr_HAL_DDR_FW_XY_Plot_RD)(uint8 clk_idx, uint32* ddi_data_offset_ptr, uint8 x_step, uint8 y_step);
extern boolean (*fptr_HAL_DDR_FW_XY_Plot_WR)(uint8 clk_idx, uint32* ddi_data_offset_ptr, uint8 x_step, uint8 y_step);

// IOCTL
extern int (*fptr_HAL_DDR_FW_IOCTL)(int cmd, void *arg, size_t size);

/* ============================================================================
**  Function : HAL_DDR_FW_Enter
** ============================================================================
*/
/*!
*   @brief
*   This function provides a buffer for DCB, FLASH_PARAMS, and LOCAL_VARS
*   Safe to call HAL_DDR_FW and HAL_CORE_SW functions after this call
*   
*   @param buffer_ptr   -  [IN] pointer to buffer
*   @param size         -  [IN] size of buffer
*   
*   @par Dependencies
*   None 
*   
*   @par Side Effects
*   None
*
*   @retval
*   None
*   
*   @sa None
*/
void HAL_DDR_FW_Enter(void *buffer_ptr, size_t size);


/* ============================================================================
**  Function : HAL_DDR_FW_Exit
** ============================================================================
*/
/*!
*   @brief
*   This function performs final configuration such as enabling power saving features
*   
*   @param
*   None
*   
*   @par Dependencies
*   None 
*   
*   @par Side Effects
*   None
*
*   @retval
*   None
*   
*   @sa None
*/
void HAL_DDR_FW_Exit(void);

/* ============================================================================
**  Function : HAL_DDR_FW_Get_DDR_SHARED_STRUCT_Pointer
** ============================================================================
*/
/*!
*   @brief
*   This function returns a pointer to DDR_SHARED_STRUCT
*   
*   @param
*   None
*   
*   @par Dependencies
*   None
*   
*   @par Side Effects
*   None
*   
*   @retval
*   pointer to DDR_SHARED_STRUCT
*   
*   @sa None
*/
DDR_SHARED_STRUCT* HAL_DDR_FW_Get_DDR_SHARED_STRUCT_Pointer(void); 

/* ============================================================================
**  Function : HAL_DDR_FW_Init
** ============================================================================
*/
/*!
*   @brief
*   This function initializes DDR
*   
*   @param
*   None
*   
*   @par Dependencies
*   Requires information is populated in DDR_SHARED_STRUCT
*   
*   @par Side Effects
*   None
*   
*   @retval
*   None
*   
*   @sa None
*/
void HAL_DDR_FW_Init(void);

/* ============================================================================
**  Function : HAL_DDR_FW_Train
** ============================================================================
*/
/*!
*   @brief
*   This function performs DDR training
*   
*   @param
*   None
*   
*   @par Dependencies
*   Requires DDR has been initialized
*   
*   @par Side Effects
*   None
*   
*   @retval
*   None
*   
*   @sa None
*/
void HAL_DDR_FW_Train(void);

/* ============================================================================
**  Function : HAL_DDR_FW_Restore
** ============================================================================
*/
/*!
*   @brief
*   This function restores training results
*   
*   @param
*   None
*   
*   @par Dependencies
*   None
*   
*   @par Side Effects
*   None
*   
*   @retval
*   None
*   
*   @sa None
*/
void HAL_DDR_FW_Restore(void);

/* ============================================================================
**  Function : HAL_DDR_FW_DDR_Freq_Switch_Prework
** ============================================================================
*/
/*!
*   @brief
*   This function is called right before clock switching occurs
*
*   @param new_clk_idx  -  [IN] DDR clock index being switched to
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*   
*   @retval
*   None
*
*   @sa None
*/
void HAL_DDR_FW_DDR_Freq_Switch_Prework(uint8 new_clk_idx);

/* ============================================================================
**  Function : HAL_DDR_FW_DDR_Freq_Switch_Work
** ============================================================================
*/
/*!
*   @brief
*   This function is called right after prework function
*
*   @param new_clk_idx  -  [IN] DDR clock index being switched to
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*   
*   @retval
*   None
*
*   @sa None
*/
void HAL_DDR_FW_DDR_Freq_Switch_Work(uint8 new_clk_idx);

/* ============================================================================
**  Function : HAL_DDR_FW_DDR_Freq_Switch_Postwork
** ============================================================================
*/
/*!
*   @brief
*   This function is called right after changing clock frequency
*
*   @param new_clk_idx  -  [IN] DDR clock index being switched to
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*   
*   @retval
*   None
*
*   @sa None
*/
void HAL_DDR_FW_DDR_Freq_Switch_Postwork(uint8 new_clk_idx);

/* ============================================================================
**  Function : HAL_DDR_FW_DDR_Freq_Switch_Postwork
** ============================================================================
*/
/*!
*   @brief
*   This function is called right after changing clock frequency
*
*   @param new_clk_idx  -  [IN] DDR clock index being switched to
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*   
*   @retval
*   None
*
*   @sa None
*/
void HAL_DDR_FW_DDR_Freq_Switch_Postwork(uint8 new_clk_idx);

/* ============================================================================
**  Function : HAL_DDR_FW_SDI_Get_Version
** ============================================================================
*/
/*!
*   @brief
*   This function returns the SDI version in DDR_FW
*   
*   @param dsf_version  -   [IN/OUT] pointer to structure to populate with DSF code version
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*   
*   @retval
*   None
*
*   @sa None
*/
void HAL_DDR_FW_SDI_Get_Version(DSF_VERSION_STRUCT *dsf_version);

/* ============================================================================
**  Function : HAL_DDR_FW_SDI_Recover
** ============================================================================
*/
/*!
*   @brief
*   This function recovers DDR for SDI
*   
*   @param
*   None
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*   
*   @retval
*   None
*
*   @sa None
*/
void HAL_DDR_FW_SDI_Recover(void);

/* ============================================================================
**  Function : HAL_DDR_FW_SDI_Dump
** ============================================================================
*/
/*!
*   @brief
*   This function performs a register dump in a buffer provided
*   
*   @param buffer_ptr   -  [IN] pointer to buffer
*   @param size         -  [IN] size of buffer
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*   
*   @retval
*   None
*
*   @sa None
*/
void HAL_DDR_FW_SDI_Dump(void *buffer_ptr, size_t size);

/* ============================================================================
**  Function : HAL_DDR_FW_eCDT_Get_Voltage_Override_Values
** ============================================================================
*/
/*!
*   @brief
*   This function gets the current eCDT voltage overrides for a specificed DDR clock index
*   
*   @param clk_idx      -  [IN] DDR clock index
*   @param buffer_ptr   -  [IN] pointer to buffer for storing index and value
*   @param size         -  [IN] size of buffer
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*   
*   @retval
*   Returns number of bytes used in buffer
*
*   @sa None
*/
int HAL_DDR_FW_eCDT_Get_Voltage_Override_Values(uint8 clk_idx, uint32 *buffer_ptr, size_t size);

/* ============================================================================
**  Function : HAL_DDR_FW_eCDT_Get_Interface_Parameter_Values
** ============================================================================
*/
/*!
*   @brief
*   This function gets the current eCDT SoC/DRAM interface parameters for a specificed DDR clock index
*   
*   @param clk_idx      -  [IN] DDR clock index
*   @param buffer_ptr   -  [IN] pointer to buffer for storing index and value
*   @param size         -  [IN] size of buffer
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*   
*   @retval
*   Returns number of bytes used in buffer
*
*   @sa None
*/
int HAL_DDR_FW_eCDT_Get_Interface_Parameter_Values(uint8 clk_idx, uint32 *buffer_ptr, size_t size);

/* ============================================================================
**  Function : HAL_DDR_FW_eCDT_Get_AC_Timing_Values
** ============================================================================
*/
/*!
*   @brief
*   This function gets the current eCDT AC timing values
*   
*   @param buffer_ptr   -  [IN] pointer to buffer for storing index and value
*   @param size         -  [IN] size of buffer
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*   
*   @retval
*   Returns number of bytes used in buffer
*
*   @sa None
*/
int HAL_DDR_FW_eCDT_Get_AC_Timing_Values(uint32 *buffer_ptr, size_t size);

/* ============================================================================
**  Function : HAL_DDR_FW_eCDT_Get_Safe_Mode_Values
** ============================================================================
*/
/*!
*   @brief
*   This function gets the current eCDT safe mode values
*   
*   @param buffer_ptr   -  [IN] pointer to buffer for storing index and value
*   @param size         -  [IN] size of buffer
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*   
*   @retval
*   Returns number of bytes used in buffer
*
*   @sa None
*/
int HAL_DDR_FW_eCDT_Get_Safe_Mode_Values(uint32 *buffer_ptr, size_t size);

/* ============================================================================
**  Function : HAL_DDR_FW_MC_MR_Read
** ============================================================================
*/
/*!
*   @brief
*   This function reads the value from a mode register
*   
*   @param channel          - [IN] channel selected to read
*   @param rank             - [IN] rank selected to read
*   @param address          - [IN] address selected to read
*
*   @par Dependencies
*   Frequency set point (FSP) read is dependent on current DDR frequency
*
*   @par Side Effects
*   Hang may occur if called for a disabled channel or unpopulated rank
*   
*   @retval
*   Returns the value read from a mode register
*   Bits [7:0] are the value read from the lower byte
*   Bits [15:8] are the value read from the upper byte
*
*   @sa None
*/
uint32 HAL_DDR_FW_MC_MR_Read(uint8 channel, uint8 rank, uint32 address);

/* ============================================================================
**  Function : HAL_DDR_FW_MC_Auto_Refresh_Ctrl
** ============================================================================
*/
/*!
*   @brief
*   This function controls periodic auto refresh
*   
*   @param enable   -  [IN] 0: disable periodic auto refresh, 1: enable
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*   
*   @retval
*   None
*
*   @sa None
*/
void HAL_DDR_FW_MC_Auto_Refresh_Ctrl(uint8 enable);

/* ============================================================================
**  Function : HAL_DDR_FW_MC_Enter_Self_Refresh
** ============================================================================
*/
/*!
*   @brief
*   This function puts the memory device in self refresh
*   
*   @param
*   None
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*   
*   @retval
*   None
*
*   @sa None
*/
void HAL_DDR_FW_MC_Enter_Self_Refresh(void);

/* ============================================================================
**  Function : HAL_DDR_FW_MC_Exit_Self_Refresh
** ============================================================================
*/
/*!
*   @brief
*   This function takes the memory device out of self refresh
*   
*   @param
*   None
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*   
*   @retval
*   None
*
*   @sa None
*/
void HAL_DDR_FW_MC_Exit_Self_Refresh(void);

/* ============================================================================
**  Function : HAL_DDR_FW_XY_Plot_CA
** ============================================================================
*/
/*!
*   @brief
*   This function creates a plot by offseting from trainined position
*   
*   @param clk_idx              -  [IN] DDR clock index
*   @param ddi_data_offset_ptr  -  [IN] pointer to offset in DDR partition
*   @param x_step               -  [IN] number of steps to offset for each data point on x-axis
*   @param y_step               -  [IN] number of steps to offset for each data point on y-axis
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*   
*   @retval
*   Returns FALSE if plot encounters an error saving data to DDR partition
*
*   @sa None
*/
boolean HAL_DDR_FW_XY_Plot_CA(uint8 clk_idx, uint32* ddi_data_offset_ptr, uint8 x_step, uint8 y_step);

/* ============================================================================
**  Function : HAL_DDR_FW_XY_Plot_RD
** ============================================================================
*/
/*!
*   @brief
*   This function creates a plot by offseting from trainined position
*   
*   @param clk_idx              -  [IN] DDR clock index
*   @param ddi_data_offset_ptr  -  [IN] pointer to offset in DDR partition
*   @param x_step               -  [IN] number of steps to offset for each data point on x-axis
*   @param y_step               -  [IN] number of steps to offset for each data point on y-axis
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*   
*   @retval
*   Returns FALSE if plot encounters an error saving data to DDR partition
*
*   @sa None
*/
boolean HAL_DDR_FW_XY_Plot_RD(uint8 clk_idx, uint32* ddi_data_offset_ptr, uint8 x_step, uint8 y_step);

/* ============================================================================
**  Function : HAL_DDR_FW_XY_Plot_WR
** ============================================================================
*/
/*!
*   @brief
*   This function creates a plot by offseting from trainined position
*   
*   @param clk_idx              -  [IN] DDR clock index
*   @param ddi_data_offset_ptr  -  [IN] pointer to offset in DDR partition
*   @param x_step               -  [IN] number of steps to offset for each data point on x-axis
*   @param y_step               -  [IN] number of steps to offset for each data point on y-axis
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*   
*   @retval
*   Returns FALSE if plot encounters an error saving data to DDR partition
*
*   @sa None
*/
boolean HAL_DDR_FW_XY_Plot_WR(uint8 clk_idx, uint32* ddi_data_offset_ptr, uint8 x_step, uint8 y_step);

/* ============================================================================
**  Function : HAL_DDR_FW_Axis_Offset_Init
** ============================================================================
*/
/*!
*   @brief
*   This function initializes data structures needed by [X,Y]_Axis_Offset functions
*   
*   @param clk_idx  -  [IN] DDR clock index
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*   
*   @retval
*   None
*
*   @sa None
*/
void HAL_DDR_FW_Axis_Offset_Init(uint8 clk_idx);

/* ============================================================================
**  Function : HAL_DDR_FW_X_Axis_Offset_CA
** ============================================================================
*/
/*!
*   @brief
*   This function offsets from trainined position
*   
*   @param offset   -  [IN] number of steps to offset from trained position
*
*   @par Dependencies
*   Must call HAL_DDR_FW_Axis_Offset_Init first
*
*   @par Side Effects
*   None
*   
*   @retval
*   Returns TRUE if offset saturates
*
*   @sa None
*/
boolean HAL_DDR_FW_X_Axis_Offset_CA(int offset);

/* ============================================================================
**  Function : HAL_DDR_FW_Y_Axis_Offset_CA
** ============================================================================
*/
/*!
*   @brief
*   This function offsets from trainined position
*   
*   @param offset   -  [IN] number of steps to offset from trained position
*
*   @par Dependencies
*   Must call HAL_DDR_FW_Axis_Offset_Init first
*
*   @par Side Effects
*   None
*   
*   @retval
*   None
*
*   @sa None
*/
boolean HAL_DDR_FW_Y_Axis_Offset_CA(int offset);

/* ============================================================================
**  Function : HAL_DDR_FW_X_Axis_Offset_RD
** ============================================================================
*/
/*!
*   @brief
*   This function offsets from trainined position
*   
*   @param offset   -  [IN] number of steps to offset from trained position
*
*   @par Dependencies
*   Must call HAL_DDR_FW_Axis_Offset_Init first
*
*   @par Side Effects
*   None
*   
*   @retval
*   Returns TRUE if offset saturates
*
*   @sa None
*/
boolean HAL_DDR_FW_X_Axis_Offset_RD(int offset);

/* ============================================================================
**  Function : HAL_DDR_FW_Y_Axis_Offset_RD
** ============================================================================
*/
/*!
*   @brief
*   This function offsets from trainined position
*   
*   @param offset   -  [IN] number of steps to offset from trained position
*
*   @par Dependencies
*   Must call HAL_DDR_FW_Axis_Offset_Init first
*
*   @par Side Effects
*   None
*   
*   @retval
*   Returns TRUE if offset saturates
*
*   @sa None
*/
boolean HAL_DDR_FW_Y_Axis_Offset_RD(int offset);

/* ============================================================================
**  Function : HAL_DDR_FW_X_Axis_Offset_WR
** ============================================================================
*/
/*!
*   @brief
*   This function offsets from trainined position
*   
*   @param offset   -  [IN] number of steps to offset from trained position
*
*   @par Dependencies
*   Must call HAL_DDR_FW_Axis_Offset_Init first
*
*   @par Side Effects
*   None
*   
*   @retval
*   Returns TRUE if offset saturates
*
*   @sa None
*/
boolean HAL_DDR_FW_X_Axis_Offset_WR(int offset);

/* ============================================================================
**  Function : HAL_DDR_FW_Y_Axis_Offset_WR
** ============================================================================
*/
/*!
*   @brief
*   This function offsets from trainined position
*   
*   @param offset   -  [IN] number of steps to offset from trained position
*
*   @par Dependencies
*   Must call HAL_DDR_FW_Axis_Offset_Init first
*
*   @par Side Effects
*   None
*   
*   @retval
*   Returns TRUE if offset saturates
*
*   @sa None
*/
boolean HAL_DDR_FW_Y_Axis_Offset_WR(int offset);

/* ============================================================================
**  Function : HAL_DDR_FW_IOCTL
** ============================================================================
*/
/*!
*   @brief
*   This function is modeled after Linux kernel ioctl based interfaces:
*   https://www.kernel.org/doc/html/latest/driver-api/ioctl.html.
*   Parameters are interpeted based on the command requested.
*   
*   @param cmd      -  [IN] command number
*   @param arg      -  [IN/OUT] pointer to arguments
*   @param size     -  [IN] size of arguments
*
*   @par Dependencies
*   Must call HAL_DDR_FW_Init first
*
*   @par Side Effects
*   None
*   
*   @retval
*   Returns 0 on success
*
*   @sa None
*/
int HAL_DDR_FW_IOCTL(int cmd, void *arg, size_t size);

enum
{
    DDR_FW_IOW_Disable_Features,
    DDR_FW_IOW_Set_ICEMEM_Key_and_Alpha,
    DDR_FW_IO_End_of_Boot,
    DDR_FW_IOW_Store_Fuse_Data,
};

/* ============================================================================
**  Command : DDR_FW_IOW_Disable_Features
** ============================================================================
*/
/*!
*   @brief
*   This command disables features.
*   
*   @param cmd      -  [IN] DDR_FW_IOW_Disable_Features
*   @param arg      -  [IN] 64-bit mask indicating which features to disable
*   @param size     -  [IN] sizeof(uint64)
*
*   @par Dependencies
*   Must call between HAL_DDR_FW_Init and HAL_DDR_FW_Exit
*
*   @par Side Effects
*   None
*   
*   @retval
*   Returns 0 on success
*
*   @sa None
*/

enum
{
    DDR_FW_DISABLE_ICEMEM  = 1 << 0,
    DDR_FW_DISABLE_DDR_ECC = 1 << 1,
    DDR_FW_DISABLE_MTE     = 1 << 2,
    DDR_FW_DISABLE_DARE    = 1 << 3,
    DDR_FW_DISABLE_MIPC    = 1 << 4,
};

/* ============================================================================
**  Command : DDR_FW_IOW_Set_ICEMEM_Key_and_Alpha
** ============================================================================
*/
/*!
*   @brief
*   This command sets encryption key and alpha for ICMEM.
*   
*   @param cmd      -  [IN] DDR_FW_IOW_Set_ICEMEM_Key_and_Alpha
*   @param arg      -  [IN] 128-bit key followed by 64-bit alpha
*   @param size     -  [IN] sizeof(uint32 * 6)
*
*   @par Dependencies
*   Must call between HAL_DDR_FW_Init and HAL_DDR_FW_Exit
*
*   @par Side Effects
*   None
*   
*   @retval
*   Returns 0 on success
*
*   @sa None
*/

typedef struct
{
    uint32 key[4];
    uint32 alpha[2];
}
DDR_FW_ICEMEM_Key_and_Alpha;

/* ============================================================================
**  Command : DDR_FW_IOW_Store_Fuse_Data
** ============================================================================
*/
/*!
*   @brief
*   This command writes fuse data to buffer_i
*   
*   @param cmd      -  [IN] DDR_FW_IOW_Store_Fuse_Data
*   @param arg      -  [IN] 32-bit address followed by 32-bit value
*   @param size     -  [IN] sizeof(uint32 * 2)
*
*   @par Dependencies
*   Must call between HAL_DDR_FW_Init and HAL_DDR_FW_Exit
*
*   @par Side Effects
*   None
*   
*   @retval
*   Returns 0 on success
*
*   @sa None
*/

typedef struct
{
    uint32 address;
    uint32 value;
}
DDR_FW_Fuse_Data;

#endif // __DDRFW_INTERFACE_H__
