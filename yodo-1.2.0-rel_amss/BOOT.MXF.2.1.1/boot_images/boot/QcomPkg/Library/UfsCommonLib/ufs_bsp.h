#ifndef UFS_BSP_H
#define UFS_BSP_H
 /**********************************************************************
 * ufs_bsp.h
 *
 * UFS driver BSP.
 *
 * Copyright (c) 2008-2022
 * Qualcomm Technologies Incorporated.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 **********************************************************************

                             Edit History

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/UfsCommonLib/ufs_bsp.h#3 $
$DateTime: 2022/09/23 17:25:31 $ $Author: pwbldsvc $

when         who     what, where, why
----------   ---     --------------------------------------------------------------  
2022-09-16   jt      Add PHY init functions for Eye Monitor  
2022-07-11   jt      Add adapt to speed config
2022-06-10   jt      Add FUA value to configuration settings  
2022-06-07   jt      Add function to pass info to HLOS  
2022-05-14   sa      Added support for BlockIo2 with multiple doorbells.
2022-05-10   sa      Added support for SharedIce. 
2022 02-24   sa      Removed Unused header files.
2021-11-05   jt      Add refclk_freq to platform_config  
2021-09-08   jt      Add ability to check battery status 
2021-08-13   jt      Add device tree support 
2021-05-18   sa      Add UFS_GEAR_5 
2021-01-28   jt      Add reference clock  
2020-06-29   jt      Update logging function 
2020-03-31   jt      Add power management functions
2019-10-22   jt      Remove voltage switching 
2019-07-22   jt      Add SMMU configuration API  
2019-05-15   jt      Remove controller version flag  
2019-02-01   jt      Add UFS 3.0 support  
2018-11-29   jt      Secondary UFS enablement changes 
2018-09-24   jt      Modify ufs_mphy_init_item
2018-09-10   jt      Add flags to control PHY initialization  
2018-07-30   jt      Add controller specific PHY init capability 
2018-06-04   jt      Add clock info struct 
2017-07-31   jt      Add logging function  
2017-06-02   jt      Add function for non-HSG4 PHY init  
2017-01-25   jt      Add UFS device reset  
2016-11-01   jt      Add reset function  
2016-08-22   jt      Update for 8998v2  
2016-08-18   jt      Add DAL config 
2015-06-15   rh      Disable the PHY from decoding the LCC sequence
2013-06-20   rh      Initial version.
-----------------------------------------------------------------------------*/

#include "UfsHwioAll.h"
#include "ufs_osal.h"

// Define the number of HCI controller
#define MAX_UFS_HCI_ID        1

#define FLUSH                 1
#define INVAL                 2
#define CLEAN                 4

#define MPHY_INIT_BUSY_WAIT   0x00000001

/* Flags for controlling PHY init entries in ufs_mphy_init_item
 
   Bits 0-1: rate_modes
   Bits 2-3: gear_modes
   Bits 4-14: reserved
   Bit  15: stop- no more entries
*/

#define STOP_CONDITION 0x8000

#define RATE_SHFT 0x0
#define RATE_MASK 0x00000003

#define GEAR_SHFT 0x2
#define GEAR_MASK 0x0000000c

#define CONDITIONAL_FLAG(rate, gear) ((rate << RATE_SHFT) | (gear << GEAR_SHFT))

/* Default values of configuraable parameters */
#define DEV_INIT_TIMEOUT              2500000
#define UTRD_POLL_TIMEOUT            30000000
#define NUM_LINK_STARTUP_RETRIES            5
#define BATTERY_THRESHOLD_MV             3600

/* Device Tree Values */
#define DT_LOG_STR_LEN                     64
#define DT_PATH_LEN                        48

typedef enum {
   RATE_A = 0x1, 
   RATE_B = 0x2
} rate_modes;

typedef enum {
   DEFAULT_GEAR = 0x1,  /* represents HS-G3 and below */
   HS_G4 = 0x2,
   HS_G5 = 0x3
} gear_modes;

// Data structure used to initialize the UFS phy
struct ufs_mphy_init_item {
   uint16_t flags; 
   uint16_t offset; 
   uint8_t  val;
}; 

/* UFS Error Types */
typedef enum
{
   UFS_BSP_NO_ERROR,
   UFS_BSP_DEVICE_ERROR, 
   UFS_BSP_ERR_INVALID_PARAM,
   UFS_BSP_ERR_FEATURE_UNSUPPORTED, 
   UFS_BSP_ERR_PMIC,
   UFS_BSP_ERR_DT
} ufs_bsp_err_type;

/* UFS voltage modes */
typedef enum
{
   UFS_BSP_REGULATORS_OFF, 
   UFS_BSP_REGULATORS_ON, 
   UFS_BSP_REGULATORS_SLEEP
} ufs_bsp_regulator_mode;

/* UFS device states */
typedef enum
{
   DEV_ON = 1,
   DEV_SLEEP = 2,
   DEV_OFF = 3
} ufs_bsp_device_states;

/* Clock modes (need to correspond to EFIStorageDeviceMgmt.h) */
typedef enum 
{
   UFS_CLOCK_MODE_OFF = 0, 
   UFS_CLOCK_MODE_MINSVS = 1, 
   UFS_CLOCK_MODE_LOWSVS = 2,
   UFS_CLOCK_MODE_SVS = 3,  
   UFS_CLOCK_MODE_NOM = 4,
   UFS_CLOCK_MODE_TURBO = 5, 
   UFS_CLOCK_MODE_ON = UFS_CLOCK_MODE_NOM,
   UFS_CLOCK_MODE_MAX_COUNT = 6
} ufs_bsp_clock_mode;

/* These enums should be in order based on level, starting with 1 (0 reserved for invalid) */
typedef enum 
{
   UFS_GEAR_INVALID = 0,
   UFS_GEAR_1 = 1,
   UFS_GEAR_2 = 2,
   UFS_GEAR_3 = 3,
   UFS_GEAR_4 = 4,
   UFS_GEAR_5 = 5,
   UFS_MAX_GEAR = UFS_GEAR_5
} ufs_bsp_hs_gears;

/* UFS logging levels */
typedef enum
{
   UFS_LOG_ERROR = 0, 
   UFS_LOG_INFO
} ufs_bsp_log_level;

/* Time-related register values */
typedef struct 
{
   uint32_t DME_MAX_1US;
   uint32_t PA_VS_40NS;
   uint32_t SYSCLK_1US;
} ufs_bsp_time_values;

/* Check if the volt_corner and gear combination is valid */
ufs_bsp_err_type ufs_bsp_check_valid_operational_mode (uint8_t volt_corner, uint8_t gear);

/* Provide information about the gears and voltage corners supported for this target */
ufs_bsp_err_type ufs_bsp_operational_mode_info (uint8_t curr_gear, void *caps);

/* Get initial value of the voltage corner (only implemented for core) */
ufs_bsp_err_type ufs_bsp_default_volt_corner (uint8_t hostid, uint8_t *volt_corner);

/* Clock busy wait function, unit in uS*/
void ufs_bsp_busy_wait (uint32_t us);

/* Configuration of all clock sources */
void ufs_bsp_clk_set (uint8_t hostid, uint32_t mode);

/* Get the value of time-related registers to be programmed */
void ufs_bsp_get_time_reg_values (uint8_t volt_corner, ufs_bsp_time_values *reg);

/* HW control of clocks */
void ufs_bsp_clk_hw_control (uint8_t hostid, uint8_t enable);

void ufs_bsp_reset (uint8_t hostid); 
void ufs_bsp_device_reset (uint8_t hostid);

void ufs_bsp_enable_symbol_clk (void);

/* Set up UFS link to use auto-hibernation */
void ufs_bsp_autoH8 (uint8_t hostid, uint16_t idle_time_ms);

/* Get the data structure for the UFS PHY init table */
uint32_t ufs_bsp_get_mphy_init_item_table (struct ufs_mphy_init_item **itm);
uint32_t ufs_bsp_get_mphy_init_2_lane_item_table (struct ufs_mphy_init_item **itm);
uint32_t ufs_bsp_get_mphy_init_end_item_table (struct ufs_mphy_init_item **itm);

#ifdef FEATURE_UFS_EYEMON
uint32_t ufs_bsp_get_mphy_eom_item_table (struct ufs_mphy_init_item **itm);
uint32_t ufs_bsp_get_mphy_eom_2_lane_item_table (struct ufs_mphy_init_item **itm);
#endif 

uint32_t ufs_bsp_mphy_start (uint8_t hostid);
void ufs_bsp_post_link_init (uint8_t hostid);

/* Cache management wrapper */
void ufs_bsp_cache_op (void *addr, uint32_t len, uint32_t op);

/* Basic memory barrier function */
void ufs_bsp_memory_barrier (void);

/* Functions to manage transfer descriptor buffer */
void *ufs_bsp_allocate_xfer_buf (size_t size);
void  ufs_bsp_free_xfer_buf (void *pmem);

/* Functions to manage command descriptor buffer */
void *ufs_bsp_allocate_command_buf (size_t size); 
void ufs_bsp_free_command_buf (void *pmem); 

/* Map register into accessable memory region */
uintptr_t ufs_bsp_get_reg_baseaddress (uint8_t hostid);

/* UFS clock information */
typedef struct _UFS_CLOCK_INFO
{
   CHAR8* const clock_name;
   UINTN        clock_id;
   UINT32       freq[UFS_CLOCK_MODE_MAX_COUNT]; 
} UFS_CLOCK_INFO;

typedef struct _UFS_CLOCK_LIST
{
   UFS_CLOCK_INFO phy_axi_clk; 
   UFS_CLOCK_INFO ice_core_clk;
   UFS_CLOCK_INFO unipro_core_clk; 
   UFS_CLOCK_INFO aggre_phy_axi_clk; 
   UFS_CLOCK_INFO phy_ahb_clk; 
   UFS_CLOCK_INFO phy_aux_clk; 
   UFS_CLOCK_INFO tx_symbol_0_clk; 
   UFS_CLOCK_INFO rx_symbol_0_clk; 
   UFS_CLOCK_INFO rx_symbol_1_clk; 
   UFS_CLOCK_INFO ref_clkref_en; 
} UFS_CLOCK_LIST;

/* Speed configuration settings */
typedef struct {
   uint8_t     enable_hs;
   uint8_t     gear;
   uint8_t     num_lanes;
   uint8_t     rate; 
   uint8_t     adapt; 
} ufs_bsp_speed_config;

/* Timeout configuration settings */
typedef struct {
   uint32_t    fdevice_init_timeout_us; 
   uint32_t    utrd_poll_timeout_us;
} ufs_bsp_timeout_config; 

/* Configuration settings */
typedef struct {
   ufs_bsp_speed_config   init_speed_params; 
   ufs_bsp_speed_config   perf_speed_params; 
   ufs_bsp_timeout_config timeout_values; 
   uint8_t                fua_value; 
   uint8_t                num_linkstartup_retries;
   uint8_t                vcc25_switch_en;
   uint32_t               battery_threshold_mv; 
} ufs_bsp_config;

/* Settings on each platform */
typedef struct {
   uint8_t     slow_xfer;
   uint8_t     core_skip; 
   uint8_t     partial_init; 
   uint8_t     core_turbo_switch;
   uint32_t    refclk_freq; 
} ufs_bsp_platform_config;

/* Information to be passed to HLOS */
typedef struct {
   uint8_t     ufs_version;
} ufs_bsp_hlos_shared_info; 

/* Functions to get various configuration settings */
void ufs_bsp_get_platform_config (ufs_bsp_platform_config *cfg);
void ufs_bsp_get_default_config (uint8_t hostid, ufs_bsp_config *cfg); 
ufs_bsp_err_type ufs_bsp_get_dt_config (uint8_t hostid, ufs_bsp_config *cfg); 

#ifdef FEATURE_CORE_ONLY
/* Info to pass to HLOS */
void ufs_bsp_set_shared_info (uint8_t hostid, ufs_bsp_hlos_shared_info *info); 
#endif 

/* Log to serial function */ 
void ufs_bsp_log (char *str, ufs_bsp_log_level level);

ufs_bsp_err_type ufs_bsp_volt_set (uint8_t hostid, ufs_bsp_regulator_mode mode); 

ufs_bsp_err_type ufs_bsp_configure_smmu(); 

ufs_bsp_err_type ufs_bsp_get_vbatt (uint32_t *volt_mv);

#endif /* #ifndef UFS_BSP_H */

