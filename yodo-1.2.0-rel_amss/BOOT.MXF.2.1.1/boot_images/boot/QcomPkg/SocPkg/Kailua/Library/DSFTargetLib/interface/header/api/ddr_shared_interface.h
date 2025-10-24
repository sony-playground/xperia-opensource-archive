#ifndef __SHARED_INTERFACE_H__
#define __SHARED_INTERFACE_H__
/*
===========================================================================

FILE:         ddr_shared_interface.h

DESCRIPTION:  
  This is the file which contains structures required for both core_sw and ddr_fw

Copyright 2019,2021-22 by Qualcomm Technologies, Inc.  All Rights Reserved.
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
#include "HAL_SNS_DDR.h"

#define DSF_INTERFACE_VERSION   22

// Debug print controls
#define CORE_SW_PRINTS      0
#define CORE_SW_SEVERITY    DDR_DETAIL

// Defines for boot training status (DDR_FW_PTR->misc.ddr.boot_training_status)
#define TRAINING_NOT_STARTED    (0)
#define TRAINING_IN_PROGRESS    (1)
#define TRAINING_COMPLETED      (2)
#define CA_TRAINING_IN_PROGRESS (3)

#define CONVERT_CYC_TO_PS        1000000000

#define DDR_FW_BUFFER_MAX_SIZE (1024*64)
#define SDI_DUMP_BUFFER_MAX_SIZE (1024*2)
#define DCB_MAX_SIZE ((1024*50)+4) // must be multiple of 4, must not be multiple of 512

#define MAX_NUM_LCP_ADDR_REGIONS 16
typedef struct
{
    uint32 start;       // Upper 20 bits (35:16) of region's starting address 
    uint32 end;         // Upper 20 bits (35:16) of regino's ending address
    uint32 metadata;    // Upper 20 bits (35:16) of starting address of associated metadata region
    uint32 metadata_size_in_kb;   // metadata region size round up to 64KB for DARE only
    uint8  attr;        // Region attributes (bit 0 - Encrypt, bit 1 - ECC, bit 2 - MTE, bit 3 - Meta Deta, bit 4 - DARE)
    uint8  arc_en;      // 1 --> DARE with ANTI-REPLY COUNTER, 0 --> DARE w/o ANTI-REPLY COUNTER
    uint8  reserved1;   // Reserved for future use
    uint8  reserved2;   // Reserved for future use
}
LCP_ADDR_REGIONS_STRUCT;

// Indices for DCB header
enum
{
    DCB_CRC_IDX,
    DCB_SIZE_IDX,
    DSF_MAINLINE_VERSION_IDX,
    DSF_MAJOR_VERSION_IDX,
    DSF_MINOR_VERSION_IDX,
    DDI_INPUT_IDX,
    RUNTIME_IDX,
    LCP_INPUT_STRUCT_IDX,
    MC_PXI_PRE_TRAINING_CFG_IDX,
    MC_PXI_RD_CFG_IDX,
    MC_PXI_WR_CFG_IDX,
    MC_PXI_RCW_CFG_IDX,
    MC_PXI_WRLVL_CFG_IDX,
    MC_PXI_CBT_CFG_IDX,
    SAVE_RESTORE_IDX,
    TRAINING_PARAMS_IDX,
    LCP_IDX,
    PMIC_SETTINGS_IDX,
    RECLAIM_IDX,
    // All data stored below this line will be cleared at the end of DDR_FW_Init
    MC_STATES_IDX = RECLAIM_IDX,
    SHUB_STATES_IDX,
    SHRM_STATES_IDX,
    DEFAULT_ALC_POLICY_IDX,
    ALC_TIMINGS_IDX,
    ALC_POLICY_INDEX_IDX,
    PERF_MODE_ALC_POLICY_IDX,
    MIN_DDR_SHUB_RATIO_IDX,
    MIN_SHUB_CP_IDX,
    ECDT_PRE_DEVICE_INIT_IDX,
    ECDT_POST_DEVICE_INIT_IDX,
    DDRSS_CFG_IDX,
    NOC_CFG_IDX,
    SHRM_CFG_IDX,
#if PLATFORM_ID >= WAIPIO_ID
    SHRM2_CFG_IDX,
#endif
    MCCC_MSTR_CFG_IDX,
    MCCC_SLV_CFG_IDX,
    DDRPHY_CFG_IDX,
    MC_CFG_IDX,
    LLCC_CFG_IDX,
    AHB2PHY_CFG_IDX,
    SHRM_DUMP_IDX,
    DCB_IDX_MAX,
};

enum
{
    DDR_FW_PLATFORM_DEFAULT,
    DDR_FW_PLATFORM_SLT,
    DDR_FW_PLATFORM_VELOCE,
    DDR_FW_PLATFORM_RUMI,
    DDR_FW_PLATFORM_MAX = 0xF
};

enum
{
    DDR_FW_PRODUCT_SEGMENT_DEFAULT,
    DDR_FW_PRODUCT_SEGMENT_MOBILE,
    DDR_FW_PRODUCT_SEGMENT_AUTOMOTIVE,
    DDR_FW_PRODUCT_SEGMENT_COMPUTE,
    DDR_FW_PRODUCT_SEGMENT_MAX = 0xF
};

enum
{
    DDR_FW_SOC_DRAM_INTERFACE_DEFAULT,
    DDR_FW_SOC_DRAM_INTERFACE_POP,
    DDR_FW_SOC_DRAM_INTERFACE_EXTERNAL,
    DDR_FW_SOC_DRAM_INTERFACE_MODULE,
    DDR_FW_SOC_DRAM_INTERFACE_MAX = 0xF
};

enum
{
    DDR_FW_PRODUCT_VARIANT_DEFAULT,
    DDR_FW_PRODUCT_VARIANT_PRO,
    DDR_FW_PRODUCT_VARIANT_MAX = 0xF
};
#define DC 0xFFFFFFFF

typedef enum
{
    UNCATEGORIZED,
    INVALID_ECDT_ENTRY,
    LIMIT_EXCEEDED,
    NO_MEMORY_DEVICE_DETECTED,
    ONLY_RANK_1_OF_MEMORY_DEVICE_DETECTED,
    MEMORY_DEVICE_DOES_NOT_MATCH_OTHER_CHANNELS,
    READ_ZERO_EYE_OPENING,
    WRITE_ZERO_EYE_OPENING,
    RCW_TRAINING_FAIL,
    DIT_READ_FAIL,
    DCB_LOAD_FAIL,
    DCB_VERSION_INCORRECT,
    SDI_VERSION_INCORRECT,
    MANAGER_VERSION_INCORRECT,
    DRAM_DCC_FAIL,
    DCC_FAIL,
    LLCC_AS_TCM_FAIL,
    LLCC_LCP_CFG_FAIL,
    NON_HASHED_SEGMENT_START_OR_END_EXCEEDS_MAX_SEGMENT, 
}
DDR_ABORT_REASON;

typedef struct
{
    uint32  reason;
    uint32  freq;
    uint32  ch;
    uint32  cs;
    uint32  byte;
    uint32  bit;
    uint32  limit;
    int     value;
}
DDR_ABORT_STRUCT;

typedef struct
{
    uint32 mainline;
    uint32 major;
    uint32 minor;
}
DSF_VERSION_STRUCT;

typedef struct
{
    DSF_VERSION_STRUCT                          dsf_code_version;               // needed at this location for debug
    DSF_VERSION_STRUCT                          shrm_code_version;              // needed at this location for debug
    DSF_VERSION_STRUCT                          dsf_training_version;           // needed at this location for debug
	uint32                                      shrm_waiti_addr;                // needed for SDI DCC SHRM LL to store WFI Address
    uint32                                      dcb_crc;                        // CRC of DDR config block
    
	uint8                                       num_ddr_levels;                 // number of DDR clock plan indices populated from DCB   
	uint8                                       num_shub_levels;                // number of SHUB clock plan indices populated from DCB    
	uint8                                       num_shrm_levels;                // number of SHRM clock plan indices populated from DCB    
	uint8                                       ddr_max_freq_idx;               // highest enabled DDR clock index

    struct detected_ddr_device_params           device_params;
    ddr_sns_size_info                           ddr_size_info;
    DDR_ABORT_STRUCT                            ddr_abort_info;                 // records information for categorizing aborts
    
    uint32                                      buffer_e_size;                  // Size of data in buffer_e
    uint32                                      buffer_i_size;                  // Size of data in buffer_i
    
    LCP_ADDR_REGIONS_STRUCT                     lcp_addr_regions[MAX_NUM_LCP_ADDR_REGIONS];
    
    uint64                                      ioctl_enabled_features;         // records if features are enabled which can be disabled through DDR_FW_IOCTL()

    union // Pointers require union with double to make the size the same for 32 bit and 64 bit processors
    {
        uint8                                   *ptr;                           // pointer to buffer_e
        double                                  rsvd;
    }
    buffer_e;

    union // Pointers require union with double to make the size the same for 32 bit and 64 bit processors
    {
        uint8                                   *ptr;                           // pointer to buffer_i
        double                                  rsvd;
    }
    buffer_i;
    
    union // Pointers require union with double to make the size the same for 32 bit and 64 bit processors
    { 
        struct ddr_params_partition             *ptr;                           // pointer to buffer for data stored in flash
        double                                  rsvd;   
    }
    flash_params;

    union // Pointers require union with double to make the size the same for 32 bit and 64 bit processors
    {
        uint16                                  (*ptr)[DCB_IDX_MAX][2];         // pointer to buffer for DCB
        double                                  rsvd;
    }
    dcb;

    union // Pointers require union with double to make the size the same for 32 bit and 64 bit processors
    {
        DDR_AOP_PARAMS                          *ptr;                           // pointer to buffer for DDR_AOP_PARAMS
        double                                  rsvd;
    }
    ddr_aop_params;

    uint8                                       ddr_init_clk_idx;               // initial DDR clock index
    uint8                                       shub_init_clk_idx;              // initial SHUB clock index
    uint8                                       shrm_init_clk_idx;              // initial SHRM clock index

    uint32                                      enabled_channels;               // mask indicating which channels are enabled
    uint8                                       enabled_chipselects;            // mask indicating which chipsets are enabled
    uint8                                       total_channels;                 // number of supported channels
    uint8                                       num_channel;                    // number of enabled channels    

    uint8                                       jtag_connected;                 // 0: JTAG not connected, 1: JTAG connected
    uint8                                       target_silicon;                 // 0: emulation platform, 1: ASIC (silicon)
    uint32                                      platform_id;                    // SoC platform ID
    uint32                                      chip_version;                   // SoC chip version
    uint32                                      serial_num;                     // SoC serial number
    uint32                                      platform_info;                  // platform information (development, test, etc)
                                                                                // Bits 3:0   - DDR_FW_PLATFORM enum value
                                                                                // Bits 7:4   - DDR_FW_PRODUCT_SEGMENT enum value
                                                                                // Bits 11:8  - DDR_FW_SOC_DRAM_INTERFACE enum value
                                                                                // Bits 15:12 - Reserved
                                                                                // Bits 23:16 - PCB major version
                                                                                // Bits 31:24 - Reserved
    
    uint8                                       extended_term_log_en;           // 0: disable extended terminal logging, 1: enable
    uint32                                      print_severity;                 // ddr_log_level enum value for specific prints
}
DDR_SHARED_STRUCT;

#define MAX_NUM_TRAININGS   44
#define MAX_GROUP_STR_LEN   14
#define MAX_NAME_STR_LEN    25

typedef void (*CORE_SW_TRN_FUNC_PTR)(void);

typedef struct
{
    union
    {
        CORE_SW_TRN_FUNC_PTR    ptr;                        // training function pointer
        double                  rsvd;
    }
    func;
    char                    group[MAX_GROUP_STR_LEN];       // name of training group
    char                    name[MAX_NAME_STR_LEN];         // name of training function
    uint8                   enabled;                        // 0: disabled, 1: enabled
    uint8                   flag[MAX_NUM_CLOCK_PLAN_IDX];   // flag indicating if training function should be called
                                                            // 0: never, 1: always, 2: only if highest enabled clock index, 3: if not highest enabled clock index
}
CORE_SW_TRN_SWITCHBOARD_STRUCT;

#endif
