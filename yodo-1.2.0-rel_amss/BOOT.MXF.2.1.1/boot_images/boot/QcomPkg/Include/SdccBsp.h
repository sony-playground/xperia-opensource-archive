#ifndef SDCCBSP_H
#define SDCCBSP_H

/** @file SdccBsp.h
   
  This file external data structures, definitions for SDCC BSP 
  used exclusively by the SDCC driver. 

  Copyright (c) 2014 - 2022, Qualcomm Technologies, Inc. 
  All Rights Reserved. 
  Qualcomm Technologies Proprietary and Confidential
    
**/

/*=============================================================================
                              EDIT HISTORY


when         who    what, where, why
----------   ---    --------------------------------------------------------------
2022-02-17   jt     Update path length for device tree
2022-01-17   ss     Add support for sdcc bootup using Device Tree Config
2022-01-05   jt     Updates for Kailua
2021-09-28   ss     Added Config Api with config structure
2021-08-30   ss     Added Default Drive strength CTL0 and CTL1 macros
2021-07-22   vm     Add voltage ON/OFF support for SD Card
2021-07-16   jt     Allow logging of device tree entries
2021-05-24   jt     Add device tree support 
2020-06-04   jt     Add power management support 
2019-07-22   jt     Add sdcc_bsp_configure_smmu()
2019-06-10   jt     Add 202 MHz clock 
2018-07-13   jt     Add UHS-1 support 
2017-10-30   jt     Add sdcc_bsp_busy_wait()
2017-06-12   sb     Get platform specific speed config 
2017-01-17   jt     Add invalid clk entry 
2016-12-12   jt     Remove legacy code 
2015-04-02   bn     Added APIs to query HS200/400 supported frequecies. Clean up
2015-01-26   rm     Integraged HS200/HS400 support for eMMC from UEFI 3.0
2014-12-03   bn     Removed unused sdcc_bsp_config_clock(). Added sdcc_bsp_get_slot_count()
2014-11-07   bn     Added DDR50_DISABLED slot option 
2014-10-18   jb     Add target specific capability override
2014-06-18   bn     Initial version. Branched from 8994 UEFI

=============================================================================*/

/*****************************************************************************/
/*                    INCLUDES                                               */
/*****************************************************************************/

typedef enum  {
   SDCC_BSP_CLK_INVALID    = 0, 
   SDCC_BSP_CLK_144_KHZ    = 144000,
   SDCC_BSP_CLK_400_KHZ    = 400000,
   SDCC_BSP_CLK_20_MHZ     = 20000000,
   SDCC_BSP_CLK_24_MHZ     = 24000000, 
   SDCC_BSP_CLK_25_MHZ     = 25000000,
   SDCC_BSP_CLK_37_MHZ     = 37500000,
   SDCC_BSP_CLK_50_MHZ     = 50000000,
   SDCC_BSP_CLK_75_MHZ     = 75000000,
   SDCC_BSP_CLK_100_MHZ    = 100000000,
   SDCC_BSP_CLK_148_MHZ    = 148000000,
   SDCC_BSP_CLK_177_MHZ    = 177000000,
   SDCC_BSP_CLK_192_MHZ    = 192000000,
   SDCC_BSP_CLK_200_MHZ    = 200000000,
   SDCC_BSP_CLK_202_MHZ    = 202000000,
   SDCC_BSP_CLK_384_MHZ    = 384000000
   /* While adding an enumeration, the sorted order must be maintained.*/
} sdcc_bsp_clk_type;

/* Clock modes (need to correspond to EFIStorageDeviceMgmt.h) */
typedef enum
{
   SDCC_CLOCK_MODE_OFF = 0,
   SDCC_CLOCK_MODE_MINSVS = 1,
   SDCC_CLOCK_MODE_LOWSVS = 2,
   SDCC_CLOCK_MODE_SVS = 3,
   SDCC_CLOCK_MODE_NOM = 4,
   SDCC_CLOCK_MODE_TURBO = 5,
   SDCC_CLOCK_MODE_ON = SDCC_CLOCK_MODE_NOM,
   SDCC_CLOCK_MODE_MAX_COUNT = 6
} sdcc_bsp_clock_mode;

/* These enums should be in order based on level, starting with 1 (0 reserved for invalid) */
typedef enum
{
   SDCC_INVALID_SPEED = 0,
   SDCC_SDR12_MODE = 1,
   SDCC_DS_MODE = SDCC_SDR12_MODE,
   SDCC_SDR25_MODE = 2,
   SDCC_HS_MODE = SDCC_SDR25_MODE,
   SDCC_SDR50_MODE = 3,
   SDCC_DDR50_MODE = 4,
   SDCC_HS200_MODE = 5,
   SDCC_SDR104_MODE = SDCC_HS200_MODE,
   SDCC_HS400_MODE = 6,
   SDCC_MAX_SPEED_MODE = SDCC_HS400_MODE
} sdcc_bsp_speed_mode;


typedef struct {
   UINT32  ExtSlotNumber;
   UINT32  EmmcSlotNumber;
   UINT32  MAXSlotNumber;
   UINT32  SpeedMode;
   BOOLEAN DmaEnabled;
} sdcc_bsp_config;


/*****************************************************************************/
/*              DEFINITIONS AND CONSTANTS                                    */
/*****************************************************************************/

/* Slot type definitions for different slots on existing on the board in use */
#define SDCC_BSP_NO_SLOT             (0)       /* No physical slot exists. Like a DNI slot */
#define SDCC_BSP_EMBEDDED_MEM_SLOT   (1 << 0)  /* Embedded Memory Slot (eMMC, buried SD) */
#define SDCC_BSP_SD_SLOT             (1 << 1)  /* Open Slot where any kind of card can be inserted */
#define SDCC_BSP_8BIT_SLOT           (1 << 2)  /* Slot is 8 bit in width */
#define SDCC_BSP_DDR_SUPPORT_SLOT    (1 << 3)  /* Slot supports DDR */
#define SDCC_BSP_DDR50_DISABLED_SLOT (1 << 4)  /* Slot does not support DDR50 mode */

typedef UINT32 sdcc_bsp_slot_type;

/* bit-wise definitions for slot type external or internal */
#define SDCC_BSP_SLOT_INVALID        (0)       /* Invalid slot configuration */
#define SDCC_BSP_SLOT_INTERNAL       (1 << 0)  /* Internal Memory Slot */
#define SDCC_BSP_SLOT_EXTERNAL       (1 << 1)  /* External Memory Slot */

typedef UINT32 sdcc_bsp_slot_access_type;

/* GPIO control options for sdcc */
typedef enum
{
   SDCC_BSP_GPIO_OFF,
   SDCC_BSP_GPIO_ON, 
}sdcc_bsp_gpio_ctl_type;

/* SDCC voltage modes */
typedef enum
{
   SDCC_BSP_REGULATORS_OFF,
   SDCC_BSP_REGULATORS_ON,
} sdcc_bsp_regulator_mode;

/* Clock control operation */
#define SDCC_BSP_CLK_CONFIG_HCLK   (1 << 0)
#define SDCC_BSP_CLK_CONFIG_RESET  (1 << 1)
#define SDCC_BSP_CLK_CONFIG_MCLK   (1 << 2)

/* SDCC BSP Error Types */
typedef enum
{
   SDCC_BSP_NO_ERROR,
   SDCC_BSP_ERR_UNKNOWN,
   SDCC_BSP_ERR_INVALID_PARAM,
   SDCC_BSP_ERR_FEATURE_UNSUPPORTED,
   SDCC_BSP_ERR_PMIC,
   SDCC_BSP_ERR_DT
} sdcc_bsp_err_type;

/* Cache operations for sdcc */
typedef enum
{
   SDCC_BSP_CACHE_INVAL,
   SDCC_BSP_CACHE_FLUSH,
   SDCC_BSP_MEM_BARRIER
}sdcc_bsp_cache_op_type;

/** Structure used for initializing HWIO base address */
typedef struct sdcc_base_addr
{
  UINT32 sdc1_base_hc;       
  UINT32 sdc2_base_hc;
  UINT32 sdc3_base_hc;    
  UINT32 sdc4_base_hc;
} sdcc_base_addr_type;

typedef struct sdcc_hsr_settings
{
  UINT32 dll_config; 
  UINT32 dll_config_2; 
  UINT32 dll_config_3; 
  UINT32 dll_test_ctrl; 
  UINT32 ddr_config; 
  UINT32 dll_user_ctrl; 
} sdcc_bsp_hsr_settings_type; 

typedef struct sdcc_supported_frequencies
{
   UINT32 ds_mode; 
   UINT32 hs_mode; 
   UINT32 sdr12_mode;
   UINT32 sdr25_mode; 
   UINT32 sdr50_mode; 
   UINT32 ddr50_mode; 
   UINT32 hs200_mode; 
   UINT32 hs400_mode; 
} sdcc_bsp_supported_frequencies; 

#define SDCC_BSP_SLOT_0    0
#define SDCC_BSP_SLOT_1    1
#define SDCC_BSP_SLOT_2    2
#define SDCC_BSP_SLOT_3    3

#define SDCC_BSP_DEFAULT_DRIVE_STRENGTH                      0x1FE4
#define SDCC_BSP_DEFAULT_DRIVE_STRENGTH_CTL0                 0x1FE4
#define SDCC_BSP_DEFAULT_DRIVE_STRENGTH_CTL1                 0x1

#define SDCC_BSP_DT_PATH_LEN                                 0x28

#define SDCC_BSP_DT_LOG_STR_LEN                              0x80

#define SDCC_BSP_DLL_CONFIG_DEFAULT_VAL                      0x642C
#define SDCC_BSP_DLL_CONFIG_2_DEFAULT_MCLK_FREQ_CALC_VAL     0x2A
#define SDCC_BSP_DLL_CONFIG_3_DEFAULT_SDC4_CONFIG_MSB_VAL    0x10
#define SDCC_BSP_DDR_CONFIG_DEFAULT_RCLK_DELAY_VAL           104
#define SDCC_BSP_DLL_USER_CTRL_DEFAULT_VAL                   0x2C010800

/*****************************************************************************/
/*                           PROTOTYPES                                      */
/*****************************************************************************/
/*=============================================================================
 * FUNCTION      sdcc_bsp_target_cap_overrides
 *
 * DESCRIPTION   This function provides target specific cap overrides
 *
 * PARAMETERS    [IN]: slot number
 *               [IN/OUT]: Capability 0 (HC_REG_40_42)
 *               [IN/OUT]: Capability 1 (HC_REG_44_46)
 *
 * RETURN VALUE  None
 *
 *===========================================================================*/
void sdcc_bsp_target_cap_overrides (UINT32 slot_num, UINT32 *caps0, UINT32 *caps1); 

/*=============================================================================
 * FUNCTION      sdcc_bsp_get_base_addr
 *
 * DESCRIPTION   This function queries the SDCC register base addresses
 *
 * PARAMETERS    [OUT]: sdcc_base_addr_type pointer to retrieve the SDCC base addresses
 *
 * RETURN VALUE  sdcc_bsp_err_type
 *
 *===========================================================================*/
sdcc_bsp_err_type sdcc_bsp_get_base_addr (sdcc_base_addr_type *sdcc_base_addr);

/*=============================================================================
 * FUNCTION      sdcc_bsp_get_slot_type
 *
 * DESCRIPTION   This function determines and returns the slot type that exists
 *               on the board which is use.
 *
 * PARAMETERS    [IN]: slot number
 *
 * RETURN VALUE  sdcc_bsp_slot_type
 *
 *===========================================================================*/
sdcc_bsp_slot_type sdcc_bsp_get_slot_type (UINT32 slot_num);

/*=============================================================================
 * DESCRIPTION   This function determines and returns the slot type whether it 
 *               is external or internal memory that exists on the board.
 *
 * PARAMETERS    [IN]: slot number
 *
 * RETURN VALUE  sdcc_bsp_slot_access_type
 *===========================================================================*/
sdcc_bsp_slot_access_type sdcc_bsp_get_slot_access_type (UINT32 slot_num);

/*=============================================================================
 * FUNCTION      sdcc_bsp_get_hsr_settings
 *
 * DESCRIPTION   This function gets the HSR settings for DLL configuration
 *
 * PARAMETERS    [IN]: slot number
 *               [IN]: speed mode 
 *               [OUT]: hsr_settings
 *
 * RETURN VALUE  sdcc_bsp_err_type
 *
 *===========================================================================*/
sdcc_bsp_err_type sdcc_bsp_get_hsr_settings (UINT32 slot_num, sdcc_bsp_speed_mode speed_mode, 
                                             sdcc_bsp_hsr_settings_type *hsr_settings);

/*=============================================================================
 * FUNCTION      sdcc_bsp_gpio_control
 *
 * DESCRIPTION   This function enables/disables the GPIO interface to the 
 *               card slot.
 *
 * PARAMETERS    [IN]: slot number
 *               [IN]: state of the GPIO interface for the slot
 *
 * RETURN VALUE  sdcc_bsp_err_type.
 *
 *===========================================================================*/
sdcc_bsp_err_type sdcc_bsp_gpio_control (UINT32 slot_num, sdcc_bsp_gpio_ctl_type state);

/******************************************************************************
* FUNCTION      sdcc_bsp_get_max_supported_mclk_freq
*
* DESCRIPTION   Get the maximum mclock frequency supported
*
* PARAMETERS    [IN]: drive number
*
* RETURN VALUE  Clock frequency supported
*
******************************************************************************/
sdcc_bsp_clk_type sdcc_bsp_get_max_supported_clk (UINT32 driveno);

/******************************************************************************
* FUNCTION      sdcc_bsp_get_supported_freq
*
* DESCRIPTION   Get the supported frequency for various speed modes
*
* PARAMETERS    [IN]: drive number
*               [OUT]: Frequency for corresponding speed modes
*
* RETURN VALUE  None
*
******************************************************************************/
void sdcc_bsp_get_supported_freq (UINT32 driveno, sdcc_bsp_supported_frequencies *freq);

/******************************************************************************
* FUNCTION      sdcc_bsp_busy_wait
*
* DESCRIPTION   Waits for the specified amount of us
*
* PARAMETERS    [IN]: us to wait 
*
* RETURN VALUE  None
*
******************************************************************************/
void sdcc_bsp_busy_wait(UINT32 us);

/******************************************************************************
* Name: sdcc_enable_mclk
*
* Description:
*    This function is to enable the SDCC controller mclock.
*
* Arguments:
*    driveno          [IN] : drive number
*
* Returns:
*    sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_enable_mclk (UINT32 driveno);

/******************************************************************************
* Name: sdcc_disable_mclk
*
* Description:
*    This function is to disable the SDCC controller mclock.
*
* Arguments:
*    driveno          [IN] : drive number
*
* Returns:
*    sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_disable_mclk (UINT32 driveno);

/******************************************************************************
* Name: sdcc_set_mclk_frequency
*
* Description:
*    This function is to select the SDCC mclock frequency.
*
* Arguments:
*    driveno          [IN] : drive number
*    sdcc_mclk        [IN] : clock speed
*
* Returns:
*    sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_set_mclk_frequency (UINT32 driveno, sdcc_bsp_clk_type sdcc_mclk);

/******************************************************************************
* Name: sdcc_set_volt_corner_frequency
*
* Description:
*    This function is to set the SDCC mclock rate based on the voltage corner.
*
* Arguments:
*    driveno          [IN] : drive number
*    volt_corner      [IN] : voltage corner
*
* Returns:
*    sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_set_volt_corner_frequency (UINT32 driveno, UINT8 volt_corner);

/******************************************************************************
* Name: sdcc_reset_mclk
*
* Description:
*    This function resets the mclk
*
* Arguments:
*    driveno          [IN] : drive number
*
* Returns:
     sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_reset_mclk (UINT32 driveno);

/******************************************************************************
* FUNCTION      sdcc_bsp_cache_operation
*
* DESCRIPTION   Performs cache operations on the provided memory region.
*               Used for DMA related operations only.
*    
* PARAMETERS    [IN]: cache operation type
*               [IN]: start address of the memory region
*               [IN]: length of the memory region
*
* RETURN VALUE  None
*
******************************************************************************/
void sdcc_bsp_cache_operation (sdcc_bsp_cache_op_type op, void *addr, UINT32 length);

/******************************************************************************
* FUNCTION      sdcc_bsp_memory_barrier
*
* DESCRIPTION   Performs data memory barrier operation.
*    
* PARAMETERS    None
*
* RETURN VALUE  None
*
******************************************************************************/
void sdcc_bsp_memory_barrier(void);

/******************************************************************************
* Name: sdcc_ahb_clk_init
*
* Description:
*    This function is to initialize the SDCC AHB clock.
*
* Arguments:
*    driveno    [IN]: drive number
*
* Returns:
*    sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_ahb_clk_init (UINT32 driveno);

/******************************************************************************
* Name: sdcc_ahb_clk_disable
*
* Description:
*    This function is to disable the SDCC AHB clock.
*
* Arguments:
*    driveno    [IN]: drive number
*
* Returns:
*    sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_ahb_clk_disable (UINT32 driveno);

/******************************************************************************
* Name: sdcc_bsp_set_sdhc_base_clk
*
* Description:
*   This function overwrites SDHC Capabilities Register SD Base CLK frequency
*
* Arguments:
*    driveno    [IN]: drive number
*    value      [IN]: SD base clock frequency
*
* Returns:
*    NONE
*
******************************************************************************/
void sdcc_bsp_set_sdhc_base_clk (UINT32 driveno, UINT32 value);

/******************************************************************************
* FUNCTION      sdcc_bsp_get_slot_count
*
* DESCRIPTION   Get the maximum SDCC number of slots support
*
* PARAMETERS    [IN]: None
*
* RETURN VALUE  Maximum number of slots on the target
*
******************************************************************************/
UINT32 sdcc_bsp_get_slot_count (VOID);

/******************************************************************************
* FUNCTION      sdcc_bsp_get_platform_speed_config
*
* DESCRIPTION   Get the speed config based on the platform
*
* PARAMETERS    [IN]: driveno
*
* RETURN VALUE  Speed config based on the platform
*
******************************************************************************/
UINT8 sdcc_bsp_get_platform_speed_config (UINT32 driveno);

/******************************************************************************
* FUNCTION      sdcc_bsp_get_config
*
* DESCRIPTION   Get the SDCC configuration for differnt parameters from the target specific files
*
* PARAMETERS    [IN]: driveno , sdcc_bsp_config structure to populate
*
* RETURN VALUE  sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_bsp_get_config (UINT32 driveno, sdcc_bsp_config *sdcc_config_data);

/******************************************************************************
* FUNCTION      sdcc_bsp_get_rca
*
* DESCRIPTION   Get the SDCC Relative Card Address from the target specific files
*
* PARAMETERS    [IN]: driveno
*
* RETURN VALUE  RCA value
*
******************************************************************************/
UINT16 sdcc_bsp_get_rca (UINT32 driveno);

/******************************************************************************
* FUNCTION      sdcc_bsp_is_adma_supported()
*
* DESCRIPTION   Get the SDCC ADMA availability from the target specific files
*
* PARAMETERS    [IN]: None
*
* RETURN VALUE  Adma availability Boolean value
*
******************************************************************************/
BOOLEAN sdcc_bsp_is_adma_supported(VOID);

/******************************************************************************
* FUNCTION      sdcc_bsp_get_vreg_switch_status
*
* DESCRIPTION   Check whether PMIC APIs work (for UHS-1) by enabling the VDD
*
* PARAMETERS    [IN]: driveno
*
* RETURN VALUE  sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_bsp_get_vreg_switch_status (UINT32 driveno); 

/******************************************************************************
* FUNCTION      sdcc_bsp_lower_volt_level
*
* DESCRIPTION   Lower the VDD to 1.8V for UHS1
*
* PARAMETERS    [IN]: driveno
*
* RETURN VALUE  sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_bsp_lower_volt_level (UINT32 driveno);

/******************************************************************************
* FUNCTION      sdcc_bsp_configure_smmu
*
* DESCRIPTION   Configure the SMMU for SDCC
*
* PARAMETERS    [IN]: None
*
* RETURN VALUE  sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_bsp_configure_smmu();

/******************************************************************************
* FUNCTION      sdcc_bsp_default_volt_corner
*
* DESCRIPTION   Provides the default voltage corner 
*
* PARAMETERS    [OUT]: volt_corner
*
* RETURN VALUE  sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_bsp_default_volt_corner (UINT8 *volt_corner);

/******************************************************************************
* FUNCTION      sdcc_bsp_check_valid_operational_mode
*
* DESCRIPTION   Checks whether the voltage corner and speed mode are compatible
*
* PARAMETERS    [IN]: driveno
*               [IN]: volt_corner
*               [IN]: speed_mode
*
* RETURN VALUE  sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_bsp_check_valid_operational_mode (UINT32 driveno, 
                                                         UINT8 volt_corner, 
                                                         UINT8 speed_mode);

/******************************************************************************
* FUNCTION      sdcc_bsp_operational_mode_info
*
* DESCRIPTION   Provides information about speed modes and voltage corners
*               supported
*
* PARAMETERS    [IN]: driveno
*               [IN]: curr_speed_mode
*               [OUT]: caps
*
* RETURN VALUE  sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_bsp_operational_mode_info (UINT32 driveno,
                                                  sdcc_bsp_speed_mode curr_speed_mode, 
                                                  void *caps);
												  
/******************************************************************************
* FUNCTION      sdcc_bsp_volt_set
*
* DESCRIPTION   Turns on voltage regulators for SD Card(SDC2)
*
* PARAMETERS    [IN]: driveno
 *              [IN]: mode
*
* RETURN VALUE  sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_bsp_volt_set (UINT32 driveno, sdcc_bsp_regulator_mode mode);												 

#endif /* #ifndef SDCCBSP_H */

