/** 
  @file  DDRDetails.h
  @brief DDR device details shared structure interface.
*/
/*=============================================================================
  Copyright (c) 2017 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who       what, where, why
 --------   ---       -----------------------------------------------------------
 04/07/22   sareezsa  Conditional compilation of MAX_DDR_REGIONS macro
 11/21/20   kns       Add shub_freq_plan_entry structure
 12/18/18   dj        add ddr info protocal
 09/26/17   daisond   changed maximum size required for ddr params for all channels
 05/26/17   daisond   Initial Revision
=============================================================================*/

#ifndef DDRDETAILS_H
#define DDRDETAILS_H


/** @defgroup Protocols 
 * 
 */

/** @defgroup efi_ddrgetinfo_protocol EFI_DDRGETINFO_PROTOCOL
 *  @ingroup MEMORY 
 */ 

/** @defgroup  efi_ddrgetinfo_protocol_prot PROTOCOL
 *  @ingroup efi_ddrgetinfo_protocol 
 */ 

/** @defgroup  efi_ddrgetinfo_protocol_apis APIs
 *  @ingroup efi_ddrgetinfo_protocol 
 */ 

/** @defgroup  efi_ddrgetinfo_protocol_data DATA_STRUCTURES
 *  @ingroup efi_ddrgetinfo_protocol 
 */ 
 
/** @ingroup efi_ddrgetinfo_protocol 
  @par Summary
  DDR MACROS.

  @par Parameters
*/

#define MAX_IDX_CH 8
#ifndef MAX_DDR_REGIONS
#define MAX_DDR_REGIONS   4
#endif
#define MAX_SHUB_ENTRIES   8

#define DDR_DETAILS_STRUCT_VERSION 0x0000000000070000

#define DDR_REGIONS_ENTRY_SMEM_OFFSET sizeof(ddr_details_entry)
#define SHUB_FREQ_PLAN_ENTRY_SMEM_OFFSET (DDR_REGIONS_ENTRY_SMEM_OFFSET + sizeof(DDR_REGIONS_ENTRY))
#define DDR_MISC_INFO_SMEM_DATA_OFFSET (SHUB_FREQ_PLAN_ENTRY_SMEM_OFFSET + sizeof(shub_freq_plan_entry))
#define DDR_INFO_SMEM_END (DDR_MISC_INFO_SMEM_DATA_OFFSET + sizeof(ddr_misc_info))

/** DDR types. */
/** @ingroup efi_ddrgetinfo_protocol_data 
  @par Summary
  DDR_TYPE enum.

  @par Parameters
*/
typedef enum
{
  DDR_TYPE_NODDR = 0, 
  DDR_TYPE_LPDDR1 = 1,           /**< Low power DDR1. */
  DDR_TYPE_LPDDR2 = 2,       /**< Low power DDR2  set to 2 for compatibility*/
  DDR_TYPE_PCDDR2 = 3,           /**< Personal computer DDR2. */
  DDR_TYPE_PCDDR3 = 4,           /**< Personal computer DDR3. */
  
  DDR_TYPE_LPDDR3 = 5,           /**< Low power DDR3. */  
  DDR_TYPE_LPDDR4 = 6,           /**< Low power DDR4. */
  DDR_TYPE_LPDDR4X = 7,            /**< Low power DDR4x. */
  DDR_TYPE_LPDDR5 = 8,            /**< Low power DDR5. */
  DDR_TYPE_LPDDR5X = 9,           /**< Low power DDR5x. */

  DDR_TYPE_UNUSED = 0x7FFFFFFF  /**< For compatibility with deviceprogrammer(features not using DDR). */
} DDR_TYPE;

/** @ingroup efi_ddrgetinfo_protocol_data 
  @par Summary
  ddr_freq_table struct.

  @par Parameters
*/
struct ddr_freq_table{
   UINT32 freq_khz;
   UINT8  enable;
};

/** @ingroup efi_ddrgetinfo_protocol_data 
  @par Summary
  ddr_freq_plan_entry struct.

  @par Parameters
*/

typedef struct ddr_freq_plan_entry_info 
{
  struct ddr_freq_table ddr_freq[14];
  UINT8  num_ddr_freqs;
  UINT32* clk_period_address;
  UINT32  max_nom_ddr_freq;
}ddr_freq_plan_entry;

/** @ingroup efi_ddrgetinfo_protocol_data 
  @par Summary
  ddr_part_details struct.

  @par Parameters
*/

struct ddr_part_details
{

  UINT8 revision_id1[2];
  UINT8 revision_id2[2];
  UINT8 width[2];
  UINT8 density[2];
  
};


/** @ingroup efi_ddrgetinfo_protocol_data 
  @par Summary
  ddr_details_entry struct.

  @par Parameters
*/

typedef struct ddr_details_entry_info 
{

  UINT8   manufacturer_id;
  UINT8   device_type;  
  struct  ddr_part_details ddr_params[MAX_IDX_CH];
  ddr_freq_plan_entry     ddr_freq_tbl;
  UINT8   num_channels;
  UINT8   sct_config;
  
}ddr_details_entry;

/** @ingroup efi_ddrgetinfo_protocol_data 
  @par Summary
  DDR_REGIONS_STRUCT_ENTRY struct.

  @par Parameters
*/

typedef struct
{
    UINT64 start_address;           // region physical address
    UINT64 size;                  // size of region in bytes
    UINT64 mc_address;              // region MC view address
    UINT32 granule_size;            // size of segments in MB (1024 * 1024 bytes
    UINT8  ddr_rank;                // rank bitmask (Rank 0: 0x1, Rank 1: 0x2)
    UINT8  segments_start_index;    // index of first full segment in a region
    UINT64 segments_start_offset;   // offset in bytes to first full segment
}
DDR_REGIONS_STRUCT_ENTRY;

/** @ingroup efi_ddrgetinfo_protocol_data 
  @par Summary
  ddr_regions_data_info struct.

  @par Parameters
*/
typedef struct ddr_regions_data_info
{
  UINT32 no_of_ddr_regions;   /* No of DDR regions */
  UINT64 ddr_rank0_size;     /*Size in bytes */
  UINT64 ddr_rank1_size;     /*Size in bytes */
  UINT64 ddr_cs0_start_addr; /* DDR rank0 start address */
  UINT64 ddr_cs1_start_addr; /* DDR rank1 start address */
  UINT32 highest_bank_bit;   /* highest address bit for bank address */
  DDR_REGIONS_STRUCT_ENTRY ddr_region[MAX_DDR_REGIONS];
}DDR_REGIONS_ENTRY;

/** @ingroup efi_ddrgetinfo_protocol_data 
  @par Summary
  shub_freq_table struct.

  @par Parameters
*/
struct shub_freq_table
{
  UINT8 enable;
  UINT32 freq_khz;
};

/** @ingroup efi_ddrgetinfo_protocol_data 
  @par Summary
  shub_freq_plan_entry_info struct.

  @par Parameters
*/
typedef struct shub_freq_plan_entry_info
{
  UINT8 num_shub_freqs;
  struct shub_freq_table shub_freq[MAX_SHUB_ENTRIES];
} shub_freq_plan_entry;


/** @ingroup efi_ddrgetinfo_protocol_data 
  @par Summary
  _ddr_misc_info struct.

  @par Parameters
*/
typedef struct _ddr_misc_info 
{
  UINT32 dsf_version;
  UINT32 reserved[10];
}ddr_misc_info;

#endif /* DDRDETAILS_H */


