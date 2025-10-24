/*******************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2013-2014,2016-2018,2020-2021 Qualcomm Technologies Incorporated.
 All rights reserved.
 ******************************************************************************/
/*==============================================================================
$Header: //components/rel/core.boot/6.1.1/QcomPkg/Include/api/boot/ddr_common.h#1 $
$DateTime: 2022/08/18 10:15:46 $
$Author: pwbldsvc $
================================================================================*/

#ifndef DDR_COMMON_H
#define DDR_COMMON_H

#if DSF_VERSION_V3_5
#include "ddr_common_v3_5.h"
#else
#define DDR_COMMON_H_MAJOR  05
#define DDR_COMMON_H_MINOR  00

/**
  @file ddr_common.h
  @brief
  Common definitions used by DDR drivers on all targets.
*/
/*=============================================================================
NOTE: The @brief description and any detailed descriptions above do not appear 
      in the PDF. 

      The ddr_mainpage.dox file contains all file/group descriptions that
      are in the output PDF generated using Doxygen and Latex. To edit or 
      update any of the file/group text in the PDF, edit the 
      ddr_mainpage.dox file or contact Tech Pubs.
=============================================================================*/
/*=============================================================================
                                EDIT HISTORY

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Include/api/boot/ddr_common.h#1 $ 
$DateTime: 2022/08/18 10:15:46 $
$Author: pwbldsvc $

when       who     what, where, why
--------   ---     ------------------------------------------------------------
10/19/21   mkma    LCP_DARE_ID update
01/04/19   dj      add new ddr type
10/07/16   rp      Cleaned up the unused structs and renamed all sdram to ddr for naming consistency
07/18/14   tw      added support for highest bank bit information
12/01/13   dp      Initial revision.
=============================================================================*/


 
 /*==========================================================================
                               INCLUDE FILES
===========================================================================*/
#include "comdef.h"
#include "DDRDetails.h"
 
// Add a definition of 'inline' to work around the QNPL comdef.h, which mysteriously omits a definition // of inline.
#if (! defined inline)
#define inline __inline
#endif /* (! defined inline) */

#define MAX_IDX 8

/** DDR interfaces. */
typedef enum
{
  DDR_CH_NONE   = 0x0,
  DDR_CH0       = 0x1,
  DDR_CH1       = 0x2,
  DDR_CH2       = 0x4,
  DDR_CH3       = 0x8,
  DDR_CH4       = 0x10,
  DDR_CH5       = 0x20,
  DDR_CH6       = 0x40,
  DDR_CH7       = 0x80,
  DDR_CH_MAX    = 0x7FFFFFFF  /**< Forces the enumerator to 32 bits. */
} DDR_CHANNEL;

/** DDR chip selects. */
typedef enum
{
  DDR_CS_NONE        = 0,                 /**< 0b00 -- no chip select. */
  DDR_CS0            = 1,                 /**< 0b01 -- chip select 0 only. */
  DDR_CS1            = 2,                 /**< 0x10 -- chip select 1 only. */
  DDR_CS_BOTH        = 3,                 /**< 0x11 -- Both chip selects. */
  DDR_CS_MAX         = 0x7FFFFFFF         /**< Forces the enumerator to 32 bits. */
} DDR_CHIPSELECT;

/** DDR SNS status. */
typedef enum
{
  DDR_UNAVAILABLE,               /**< DDR is unavailable on this chip select. */
  DDR_ACTIVE,                    /**< Active mode. */
  DDR_SELF_REFRESH,              /**< Self Refresh mode. */
  DDR_STALL,                     /**< Stalled mode. */
  DDR_DPD,                       /**< Deep Power Down mode. */
  DDR_STATUS_MAX = 0x7FFFFFFF    /**< Forces the enumerator to 32 bits. */
} DDR_SNS_STATUS;

/** DDR manufacturers. */
typedef enum
{
  RESERVED_0,                        /**< Reserved for future use. */
  SAMSUNG,                           /**< Samsung. */
  QIMONDA,                           /**< Qimonda. */
  ELPIDA,                            /**< Elpida Memory, Inc. */
  ETRON,                             /**< Etron Technology, Inc. */
  NANYA,                             /**< Nanya Technology Corporation. */
  HYNIX,                             /**< Hynix Semiconductor Inc. */
  MOSEL,                             /**< Mosel Vitelic Corporation. */
  WINBOND,                           /**< Winbond Electronics Corp. */
  ESMT,                              /**< Elite Semiconductor Memory Technology Inc. */
  RESERVED_1,                        /**< Reserved for future use. */
  SPANSION,                          /**< Spansion Inc. */
  SST,                               /**< Silicon Storage Technology, Inc. */
  ZMOS,                              /**< ZMOS Technology, Inc. */
  INTEL,                             /**< Intel Corporation. */
  NUMONYX = 254,                     /**< Numonyx, acquired by Micron Technology, Inc. */
  MICRON = 255,                      /**< Micron Technology, Inc. */
  DDR_MANUFACTURES_MAX = 0x7FFFFFFF  /**< Forces the enumerator to 32 bits. */
} DDR_MANUFACTURES;

/** DDR interleave type */
typedef enum
{
  DDR_CS0_INTERLEAVE = 1,
  DDR_CS1_INTERLEAVE = 2,
  DDR_CS0_CS1_INTERLEAVE = 3,
} ddr_interleave_type;     


/** @brief DDR states of all interfaces and chip selects. */
typedef struct
{
  DDR_SNS_STATUS ddr_cs0[MAX_IDX];    /**< Array of DDR status of chip select 0 for each channel. */
  DDR_SNS_STATUS ddr_cs1[MAX_IDX];    /**< Array of DDR status of chip select 1 for each channel. */

  uint32 clk_speed;           /**< Clock speed. */
  uint32 vddmx_voltage;       /**< VDDMX level in microvolts. */
  uint32 vddcx_voltage;       /**< VDDCX level in microvolts. */
} ddr_interface_state;

/** @brief DDR sizes and start addresses of all interfaces and chip selects. */
typedef struct
{
  uint32 ddr_cs0[MAX_IDX];       /**< DDR size of Interface0 and chip select 0. */
  uint32 ddr_cs1[MAX_IDX];       /**< DDR size of Interface0 and chip select 1. */
  
  uint64 ddr_cs0_addr[MAX_IDX];  /**< DDR start address of Interface0 and chip select 0. */
  uint64 ddr_cs1_addr[MAX_IDX];  /**< DDR start address of Interface0 and chip select 1. */
  
  uint32 highest_bank_bit; /**< DDR Highest bank bit based on detected topology */
} ddr_size_info;


/** @brief ddr information that are relevent to clients outside of ddr driver */
typedef struct
{
  ddr_size_info ddr_size; /**< DDR size and address configuration */  
  uint32 interleaved_memory; /**< Return whether the ddr is interleaved or not. */
  DDR_TYPE ddr_type;  /**< Return ddr type enum. */ 
} ddr_info;

typedef struct
{
  uint32 num_partitions;   /**< DDR size of Interface0/CS0 */
  uint64 ddr_addr;       /**< DDR start address of Interface0/CS0 */
} ddr_partitions;

typedef struct
{
  ddr_partitions ddr_cs0[MAX_IDX]; /**< Partition information for CS0 for each interface */
  ddr_partitions ddr_cs1[MAX_IDX]; /**< Partition information for CS1 for each interface */
} ddr_size_partition;

/** @brief DDR sizes and start addresses of all interfaces and chip selects. */
typedef struct
{
  uint32 ddr_cs0_mb[MAX_IDX];    /**< DDR size in MBytes of Interface and chip select 0. */
  uint32 ddr_cs1_mb[MAX_IDX];    /**< DDR size in MBytes of Interface and chip select 1. */
  
  uint8 ddr_cs0_io_width[MAX_IDX];    /**< DDR Device IO Width of Interface and chip select 0. */
  uint8 ddr_cs1_io_width[MAX_IDX];    /**< DDR Device IO Width of Interface and chip select 1. */
  
  uint64 ddr_cs0_addr[MAX_IDX];  /**< DDR start address of Interface and chip select 0. */
  uint64 ddr_cs1_addr[MAX_IDX];  /**< DDR start address of Interface and chip select 1. */
  
  uint64 ddr_cs0_remapped_addr[MAX_IDX];  /**< DDR remapped start address of Interface and chip select 0. */
  uint64 ddr_cs1_remapped_addr[MAX_IDX];  /**< DDR remapped start address of Interface and chip select 1. */
  
  uint32 highest_bank_bit; /**< DDR Highest bank bit based on detected topology */
} ddr_sns_size_info;



typedef enum 
{
    HYP = 0,
    TZ_TA_S1,
    TA_S2,
    TUI_VM, 
    OEM_VM,
    SMMU_PT,
    MTE_DATA_R0, 
    MTE_AT_R0, 
    MTE_DATA_R1, 
    MTE_AT_R1, 
    MTE_DATA_R2, 
    MTE_AT_R2, 
    MTE_DATA_R3, 
    MTE_AT_R3, 
    RESERVED_R14,
    RESERVED_R15
}DARE_REGION_ID;

typedef struct
{
    uint32 start_addr;
    uint32 end_addr;
    uint32 md_start_addr; 
    uint32 metadata_size_in_kb; 
    uint32 encrypt_key[4]; //128-bit encryption key
    uint32 encrypt_alpha_key[2]; //64-bit alpha key
    uint8  interrupt_en;       //1-> enable, 0 --> disable 
    uint8  secure_interrupt;  // 1--> secure (TZ), 0 --> NonSecure (HLOS)
    uint8  auth_error_disable; //1 --> DARE region will disable authentication and reporting of error on that region
    uint8  disable_after_first_error; //1 --> bypass authentication checks after the first authentication error
    uint8  inherit_master_scid; //1 --> DARE region will use same SCID as master SCID, 0--> will use SCID configured in LCP_GLOBAL_CFG0.LCP_DARE_ID    
    uint8  valid;
    uint8  type; // 0x1--> Encrypt, 0x2--> ECC, 0x4--> MTE, 0x8-->AT/SYNDROME , 0x10-> DARE 
    uint8  arc_en; //1 --> DARE with ANTI-REPLY COUNTER, 0 --> DARE w/o ANTI-REPLY COUNTER 

}LCP_REGION_CONFIG_STRUCT;
/** @} */ /* end_addtogroup ddr_data_structures */
#endif /* DSF_VERSION_X */

#endif  /* DDR_COMMON_H */
