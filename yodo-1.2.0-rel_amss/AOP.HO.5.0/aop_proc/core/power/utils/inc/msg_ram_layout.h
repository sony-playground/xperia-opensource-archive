#ifndef MSG_RAM_LAYOUT_H
#define MSG_RAM_LAYOUT_H
/*===========================================================================
                             msg_ram_layout.h

DESCRIPTION:
  Verbose description of what is defined by this header file. Typically
  describes the service provided by the structs, macros, etc. defined in
  this file.

Copyright (c) 2017-2020 QUALCOMM Technologies, Inc. (QTI). All Rights Reserved.  
QUALCOMM Proprietary.  Export of this technology or software is regulated 
by the U.S. Government. Diversion contrary to U.S. law prohibited.
===========================================================================*/


//===========================================================================
//                   Includes and Public Data Declarations
//===========================================================================

//---------------------------------------------------------------------------
// Include Files
//---------------------------------------------------------------------------
#include "msmhwiobase.h"
#include "rpmh_common.h"
#if defined(KAILUA_TARGET_CONFIG) || defined(LANAI_TARGET_CONFIG) || defined(HAMOA_TARGET_CONFIG)
#include "arc_rm_hwio.h"
#include "arc_vt_hwio.h"
#endif
#include "comdef.h"

#ifndef AOP_SS_MSG_RAM_START_ADDRESS_BASE
#define AOP_SS_MSG_RAM_START_ADDRESS_BASE (AOP_SS_MSG_RAM)
#endif

#ifndef AOP_SS_MSG_RAM_END_ADDRESS_BASE
#define AOP_SS_MSG_RAM_END_ADDRESS_BASE (AOP_SS_MSG_RAM + AOP_SS_MSG_RAM_SIZE - 1)
#endif

//---------------------------------------------------------------------------
// Constant / Define Declarations
//---------------------------------------------------------------------------
#define MSG_RAM_DRV_SIZE          0x400  // 1K
#define MSG_RAM_INFO_0_SIZE       sizeof(aop_info_0_t)
#define MSG_RAM_SMEM_TABLE_SIZE   sizeof(aop_smem_table_t)
#define MSG_RAM_GAP_SIZE          0xFC00  // 63K
#define MSG_RAM_SECTION_SIZE      (MSG_RAM_DRV_SIZE + MSG_RAM_GAP_SIZE)
#define MSG_RAM_SECTION(i)        (void *)(AOP_SS_MSG_RAM_START_ADDRESS_BASE + (i * MSG_RAM_SECTION_SIZE))
#define MSG_RAM_CMD_DB_DATA_SIZE  2  // Size in uint32 units.
#define SMEM_TABLE_MAX_SIZE       0xA
#define NUM_OF_DDR_REGISTERS      1

//---------------------------------------------------------------------------
// Type Declarations
//---------------------------------------------------------------------------

typedef struct
{
  void *start;   
  uint32 size; 
} msg_ram_sec_t;

/* ============AOP INFO0 Section============ */

typedef struct
{
  uint32 stat_type;       //type of sleep stat (ascii little endian)
  uint32 count;           //# times this mode has been entered 
  uint64 last_entered;    //last timestamp we entered this mode
  uint64 last_exited;     //last timestamp we exited this mode
  uint64 total_duration;  //total amount of time we've spent in this mode
} sleep_stats_t;

typedef struct aop_ddr_reg {
  uint32 address;
  uint32 data;
} aop_ddr_reg_t;

typedef struct aop_ddr_reg_data {
  uint32        timestamp_lo;
  aop_ddr_reg_t register_info[NUM_OF_DDR_REGISTERS];
} aop_ddr_reg_data_t ;

typedef struct
{
  uint32 boot_cookie_offset;   //boot cookie address
  uint32 sleep_stats_offset;   //sleep stats address
  uint32 wdog_cookie_offset;   //cti cookie offset
  uint32 cmd_db_data_offset[MSG_RAM_CMD_DB_DATA_SIZE];
  uint32 ddr_stats_dictionary_offset; //offset for the ddr_stats_dict_t structure
  uint32 aop_ddr_reg_data_offset;
  uint32 aop_ddr_residency_offset; // offset to the DDR frequency/LPM residency
  uint32 starc_residency_offset;   // offset to the STARC residency
  uint32 aop_lpm_mon_offset;  //log of lpm debugs
  uint32 aop_boot_time_offset; //aop bootup time address
  uint32 reserved_addrs[5];
} dict_t;


#if !defined(KAILUA_TARGET_CONFIG) && !defined(KAPITI_TARGET_CONFIG) && !defined(LANAI_TARGET_CONFIG) && !defined(HAMOA_TARGET_CONFIG) && !defined(PINNACLE_TARGET_CONFIG) && !defined(KUNO_TARGET_CONFIG)
  #define FREQ_SWITCH_COUNT 50
#else
  #define FREQ_SWITCH_COUNT 20
#endif

enum event {
   FREQ_CHANGE, // 0 Starting the frequency change
   FREQ_FLUSH,  // 1 Starting a flush
   FREQ_DONE,   // 2 Done - DDR_MGR Idle
   FREQ_PASR,   // 3 PASR Command Processed
   FREQ_PERF,   // 4 Performance Mode Command Processed
};

typedef struct freq_switch {
  uint64 timestamp;

  uint8  event;                 // Corresponds to the enum event above.
  uint8  powerstate_request;    // What is the Powerstate ARC state
  
  union {
    uint16 mc_steps;            // If event is 0, intermediate MC frequencies stepped through in the
                                // sequence to get to dest. LSByte is first step and MSByte is second.
                                // MSByte==0, one intermediate step. LSByte==0, no intermediate steps.
    uint16 bcm_acv_alc;         // If event is 2, BCM values for ALC (LSByte) and ACV (MSByte).
  };

  uint8  bcm_mc_request;        // What is BCM requesting for MC
  uint8  bcm_shub_request;      // What is BCM requesting for SHUB
  uint8  current_mc_cp;         // The current MC Clock Plan
  uint8  current_shub_cp;       // The current SHUB Clock Plan
} FREQ_SWITCH_TABLE;

typedef struct ddr_stats {

  uint32_t mc_count;
  uint32_t shub_count;
  uint32_t restore_count;
  uint32_t collapse_count;

  uint64_t mc_cp_history;             uint64_t shub_cp_history;   // Saves last 16 changes
  uint64_t mc_begin;                  uint64_t shub_begin;
  uint64_t previous_mc_begin;         uint64_t previous_shub_begin;
  uint64_t powerstate_collapse_begin; uint64_t powerstate_restore_begin;
  uint64_t mc_max;                    uint64_t mc_max_time;
  uint64_t shub_max;                  uint64_t shub_max_time;
  uint64_t powerstate_collapse_max;   uint64_t powerstate_collapse_max_time;
  uint64_t powerstate_restore_max;    uint64_t powerstate_restore_max_time;
  
  uint32_t flush_count; uint32_t pad; uint64_t flush_begin;
  uint64_t flush_max;                 uint64_t flush_max_time;

} DDR_STATS;

#define DDRMGR_FLAG_NEW             0xCA11C0DE
#define DDRMGR_FLAG_DONE            0x600D0000
#define DDRMGR_FLAG_SECURE          0x5EC00000

#define DDRMGR_LOG_STOP_FLAGS       0x0000000F
#define DDRMGR_LOG_STOP_MC          0x00000001
#define DDRMGR_LOG_STOP_SHUB        0x00000002
#define DDRMGR_LOG_STOP_COLLAPSE    0x00000004
#define DDRMGR_LOG_STOP_RESTORE     0x00000008
#define DDRMGR_DISABLE_T32_VOTES    0x10000000
#define DDRMGR_OPSCALE_SHUB_FLAG    0x20000000
#define DDRMGR_OVERRIDE_ALC_FLAG    0x40000000
#define DDRMGR_OPSCALE_BCM_FLAG     0x80000000

#define DDRMGR_TEST_BCM             0x00000001
#define DDRMGR_TEST_DDR             0x00000002
#define DDRMGR_TEST_CX_MX           0x00000004
#define DDRMGR_TEST_VRM             0x00000008
#define DDRMGR_TEST_ZERO_TEMP       0x00000010
#define DDRMGR_TEST_PERFMODE_SEEN   0x00100000
#define DDRMGR_TEST_FLOOR_SEEN      0x00200000
#define DDRMGR_TEST_CAPPED_SEEN     0x00400000
#define DDRMGR_TEST_FIXED_SEEN      0x00800000
#define DDRMGR_TEST_STARC_SEEN      0x01000000
#define DDRMGR_TEST_FAKE_FREQ       0x02000000
#define DDRMGR_TEST_PAIR_FIXED      0x04000000
#define DDRMGR_TEST_DELAY           0x000FFF00
#define DDRMGR_TEST_DELAY_SHIFT     8

#define DDRMGR_TEST_CLEAR_VOTES     0x20000000
#define DDRMGR_TEST_MIN_VOTES       0x40000000
#define DDRMGR_RUN_DDRMGR_TEST_CODE 0x80000000

typedef struct ddr_mgr_config_t
{
  uint32 ddr_mgr_test_info;         // Causes DDR_MGR to run internal tests (if enabled in build)
  uint32 ddr_mgr_test_count;        // Number of test interations run       (if enabled in build)
  uint32 ddr_mgr_operational_info;  // Enable/Disable SHUB op scaling as well as 
  uint32 ddr_config_status;         // Indicates when a new command is set/applied
  uint64_t alc_override_values;     // ALC Override values for the 16 CPs
  uint32_t ddraux_command_timeout;  // Timeout value for sequences in DDR_AUX.
  uint32_t log_stop_time;           // Stop local logging if processing is longer than this.
} DDR_MGR_CONFIG;


#if !defined(KAILUA_TARGET_CONFIG) && !defined(LANAI_TARGET_CONFIG) && !defined(KAPITI_TARGET_CONFIG) && !defined(HAMOA_TARGET_CONFIG) && !defined(PINNACLE_TARGET_CONFIG) && !defined(KUNO_TARGET_CONFIG)
typedef struct
{
  uint32 ddr_event_offset;       // Offset for the first DDR_EVENT;
  uint32 ddr_event_count;        // Number of possible DDR events.
  uint32 ddr_stats_offset;       // sleep stats address
  uint32 ddr_mgr_config_offset;  // Offset of the DDR config structure.
} ddr_stats_dict_t;

typedef struct ddr_mgr_info_t {
  ddr_stats_dict_t  dictionary;     // Dictionary of the below entries
  FREQ_SWITCH_TABLE freq_switch_events[FREQ_SWITCH_COUNT]; // Tracks the last FREQ_SWITCH_COUNT(50) events
  DDR_MGR_CONFIG    ddr_mgr_config; // The DDR_MGR config offset.
  DDR_STATS         ddr_stats;      // Saves overall statistics on DDR.
} DDR_MGR_INFO_T;
#else
//for waipio
typedef enum 
{
  IDLE                = 0x0,//this is not logged
  SHUB_FREQ_CHANGE    = 0x1,
  MC_FREQ_CHANGE      = 0x2,
  P_FREQ_CHANGE_UP    = 0x3,
  NORMAL_RESTORE      = 0x4,
  COLLAPSE            = 0x5,
  LLC_FLUSH           = 0x6,
  FLUSH_ABORT         = 0x7,
  SW_SEQ              = 0x8,
  CALL_PATH_SEQ       = 0x9, //needed for all 5.0 targets(DDR LLC support added) 
  NUM_SUBSEQ,
  NUM_SEQSEQ_LOGGED = NUM_SUBSEQ - 1,
}SUBSEQ_TYPE;

typedef struct
{
  uint32 seq_start_time_hi; //START time Upper value of GCNTR.
  uint32 seq_start_time_lo; //START time Lower value of GCNTR.
  uint32 seq_end_time; //Sequence end time relative to start time
  uint32 seq_mida_time; //midpoint a, relative to start time
  uint32 seq_midb_time; //midpoint b, relative to start time
  uint32 seq_cp; //freq cp
  uint32 seq_state; //ACV, ALC, PS, SEQ_TYPE
}freq_change_log_t;

typedef struct
{
 uint32 seq_count;
 uint32 last_start_time_hi;
 uint32 last_start_time_lo;
 uint32 worst_end_time;
 uint32 mida_worst_time;
 uint32 midb_worst_time;
}seq_stats_t;

typedef struct
{ /*Dictionary */
  uint32 ddr_mgr_config_offset;  // Offset of the DDR config structure.
  uint32 ddr_log_offset;         // Offset for the first DDR_EVENT;
  uint32 ddr_log_end_offset;     // End of log

} ddr_stats_dict_t;

typedef struct
{/*DDR AUX log module*/
  
  freq_change_log_t freq_sw_events[FREQ_SWITCH_COUNT];
  seq_stats_t seq_stats[NUM_SEQSEQ_LOGGED]; //Subsequence, number of times it was called. IDLE isn't logged

  uint32 mc_history;   //The last 8 MC CP history. Each hexa-digit represent a clock plan. LSB = newest. MSB = oldest
  uint32 shub_history; //The last 8 SHUB CP history.

  uint32 last_2_mc_changes_hi[2]; //last two mc changes
  uint32 last_2_mc_changes_lo[2];

  uint32 last_2_shub_changes_hi[2]; //last two shub changes
  uint32 last_2_shub_changes_lo[2];
  
}ddr_aux_log_t;


typedef struct ddr_mgr_info_t {
  ddr_stats_dict_t  dictionary;     // Dictionary of the below entries
  DDR_MGR_CONFIG    ddr_mgr_config; // The DDR_MGR config offset.
  ddr_aux_log_t    ddr_aux_log;   // data dump of DDR_AUX_LOG module
} DDR_MGR_INFO_T;
#endif
#if defined(KAPITI_TARGET_CONFIG) || defined(KAILUA_TARGET_CONFIG) || defined(LANAI_TARGET_CONFIG) || defined(HAMOA_TARGET_CONFIG) || defined(PINNACLE_TARGET_CONFIG) || defined(KUNO_TARGET_CONFIG)
  #define NUM_RES_MODES 19  // use starc to record ddr freq information, so we should give more space for this array.
#else
  #define NUM_RES_MODES 19  // 15 active possible, 4 possible Low Power states.
#endif
#define NUM_STARC_MODES 48

#define ROUND_4(x) (((x) + (0x3)) & (~0x3))
#ifdef LANAI_TARGET_CONFIG
  #define NUM_BCM_DRVS 23
  #define NUM_DRVS 25
#elif defined(KAILUA_TARGET_CONFIG)
  #define NUM_BCM_DRVS 20
  #define NUM_DRVS 22
#else
  #define NUM_BCM_DRVS 18
  #define NUM_DRVS 18
#endif

typedef struct
{
    uint32_t flag0;
    uint32_t flag1;
    uint32_t flag2;
    uint32_t flag3;
} PATH_STATE_INFO_T;

typedef struct ddr_residency_info
{
  uint32_t key1;         // Key to identify this is initialized
  uint32_t entry_count;  // Number of entries which follow
  struct stat_entry {
    uint32_t name;       // Unique ID of the mode
    uint32_t count;      // Number of instances used
    uint64_t total_duration; // Total time we spent in this mode.
  } entry[NUM_RES_MODES];
  union{
    uint32_t drv_mc0_vote[NUM_BCM_DRVS]; //To store DDR instant AB/IB vote
    uint32_t drv_arc_vote[ROUND_4(NUM_DRVS)/4]; //To store ARC RMs instant vote
  };
} DDR_RESIDENCY_INFO_T;

typedef struct starc_residency_info
{
  uint64_t starc_signature; // The initial STARC disabled mask received from BCM
  uint64_t ceiling_cps;     // The values currently set for Ceiling CP.
  uint64_t starc_residency_curr_time;  // Time above snapshot occurred
  uint64_t starc_residency_hist_time;  // The time we added resdiency to history
  uint32_t starc_residency_curr[NUM_STARC_MODES]; // Snapshots of residency
  uint32_t starc_residency_hist[NUM_STARC_MODES]; // Historical timestamps
} STARC_RESIDENCY_INFO_T;

typedef struct
{
  dict_t dictionary;            //dictionary for subsystems to lookup stats addresses
  uint32 boot_cookie;           //boot cookie indicating AOP is up and initialized
  uint32 reserved0;
  sleep_stats_t sleep_stats[3]; //sleep stats tracking sleep mode details
  uint32 wdog_cookie;
  aop_ddr_reg_data_t aop_ddr_reg_data;
  DDR_RESIDENCY_INFO_T ddr_residency;   // DDR Residency stats 
  STARC_RESIDENCY_INFO_T starc_residency; // STARC state Residency stats 
  uint64 aop_boot_time[2]; //0-start, 1-end
  uint32 reserved1[206-((sizeof(DDR_RESIDENCY_INFO_T)+
                         sizeof(STARC_RESIDENCY_INFO_T))/4)]; //decrease anytime something is added to the structure
} aop_info_0_t;

/* ============SMEM TABLE Section============ */

typedef struct
{
  uint32 smem_id;
  uint32 addr;
} smem_addr_t;

typedef enum
{
  SMEM_TABLE_SUCCESS,
  SMEM_TABLE_NOT_INITIALIZED,
  SMEM_TABLE_ID_NOT_FOUND,
} smem_table_err;

typedef struct
{
  uint32      initialized;                 //filled in by XBL once the table is initialized
  uint32      num_addrs;                   //size of the smem lookup table
  smem_addr_t table[SMEM_TABLE_MAX_SIZE];  //table of smem addresses
} aop_smem_table_t;

/* DDR DEBUG LOG placed in MSGRAM right after SMEM */
typedef struct
{
    uint32_t init;
    uint32_t rm_operational_level[2]; //DDRPS and LPINOC
    uint32_t arc_drv_rm_vote[22][2];  //DRV (0-21)'s votes on DDRPS and LPINOC
    uint32_t bcm_status_be_cd[13];    //BCM CD(0-12)
} DDR_DEBUG_LOG_T;

//---------------------------------------------------------------------------
// Forward Declarations
//---------------------------------------------------------------------------

//===========================================================================
//                             Function Definitions
//===========================================================================

//msg ram layout
//#define AOP_SS_MSG_RAM_SIZE_BASE                                    0x00100000
//#define AOP_SS_MSG_RAM_START_ADDRESS_BASE                           0x01300000
//#define AOP_SS_MSG_RAM_END_ADDRESS_BASE                             0x013fffff

/* ============Access Functions ============ */

/**
 * <!-- msg_ram_get_smem_addr -->
 *
 * @brief Retrieve an smem address from message ram. These addresses are populated by XBL. 
 *
 * @param smem_id : The smem ID correpsonding to the address we are retrieving
 * @param smem_addr : A pointer to a uint32 that will be filled in the the smem address value
 *
 * @return SMEM_TABLE_SUCCESS if we found the address, smem_err code otherwise
 */ 
smem_table_err msg_ram_get_smem_addr(uint32 smem_id, uint32 *smem_addr);

/**
 * <!-- msg_ram_get_wdog_cookie -->
 *
 * @brief Retrieve the wdog cookie from msg ram 
 *
 * @return the wdog cookie value
 */ 
uint32 msg_ram_get_wdog_cookie();

/**
 * <!-- msg_ram_get_wdog_cookie -->
 *
 * @brief Set the wdog cookie in msg ram 
 *
 * @param the dog cookie value to set
 */ 
void msg_ram_set_wdog_cookie(uint32 cookie_val);

/**
 * <!-- msg_ram_cmd_db_set_init -->
 *
 * @brief Initialize the dictionary entry for cmd_db
 */
void msg_ram_cmd_db_set_init(uint32 data[MSG_RAM_CMD_DB_DATA_SIZE]);

/**
 * <!-- msg_ram_get_sleep_stats_area -->
 *
 * @brief Return the pointer to a msg ram memory area where sleep stats are populated
 *
 */ 
void *msg_ram_get_sleep_stats_area (void);

/**
 * <!-- msg_ram_get_frequency_stats_area -->
 *
 * @brief Return the pointer to a msg ram memory area where frequency stats are populated
 *
 */ 
void *msg_ram_get_frequency_stats_area (void);

/**
 * <!-- msg_ram_ddrstats_set_init -->
 *
 * @brief Initialize the dictionary entry for ddr_statistics
 */
void msg_ram_ddrstats_set_init(void *ddr_stats_dictionary);

/**
 * <!-- msg_ram_get_ddr_debug_log_area -->
 *
 * @brief Return the pointer to a msg ram memory area where the AOP can dump ddr debug log
 *
 */
void *msg_ram_get_ddr_debug_log_area(void);

/**
 * <!-- msg_ram_get_aop_area -->
 *
 * @brief Return the pointer to a msg ram memory area where the AOP can put debug
 *
 */ 
void *msg_ram_get_aop_area (void);
/**
 * <!-- msg_ram_get_frequency_stats_area -->
 *
 * @brief Return the pointer to a msg ram memory area where frequency stats are populated
 *
 */ 
void *msg_ram_get_aop_logging_area (void);

/**
 * <!-- msg_ram_get_aop_prof_area -->
 *
 * @brief Return the pointer to a msg ram memory area where the AOP profiling stats are stored
 *
 */ 
void *msg_ram_get_aop_prof_area (void);


/**
 * <!-- msg_ram_get_ddr_reg_read_area -->
 *
 * @brief Return the pointer to a msg ram memory area where ddr register data are stored when apps requested
 *
 */
 
void *msg_ram_get_ddr_reg_read_area (void);

/**
 * <!-- msg_ram_get_residency_stats_area -->
 *
 * @brief Return the pointer to a msg ram memory area where residency stats are populated
 *
 */ 
void *msg_ram_get_residency_stats_area (void);

/**
 * <!-- msg_ram_get_vote_statis_area -->
 *
 * @brief Return the pointer to a msg ram memory area where vote info are populated
 *
 */
void *msg_ram_get_vote_statis_area (void);

/**
 * <!-- msg_ram_get_starc_stats_area -->
 *
 * @brief Return the pointer to a msg ram memory area where residency stats are populated
 *
 */ 
void *msg_ram_get_starc_stats_area (void);

/**
 * <!-- msg_ram_set_boot_cookie -->
 *
 * @brief Set the boot cookie to indicate AOP is initialized 
 */ 
void msg_ram_set_boot_cookie(void);

/**
 * <!-- msg_ram_set_lpm_debug_lookup -->
 *
 * @brief set msgram lookup for debug lpm logs
 */ 
void msg_ram_set_lpm_debug_lookup(uint32 buffer_addr);

/**
 * <!-- msg_ram_get_tz_area -->
 *
 * @brief Return the pointer to a msg ram memory area where frequency stats are populated
 *
 */ 
#if defined(Olympic_STUBS) || defined(PINNACLE_STUBS) || defined(KUNO_STUBS)
void *msg_ram_get_tz_area (void);
#endif

/**
 * <!-- msg_ram_set_init -->
 *
 * @brief Initialize the dictionary and sleep stats types 
 */ 
void msg_ram_init(void);

#endif // MSG_RAM_LAYOUT_H
