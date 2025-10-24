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
 12/18/18   dj        add ddr info protocal
 09/26/17   daisond   changed maximum size required for ddr params for all channels
 05/26/17   daisond   Initial Revision
=============================================================================*/

#ifndef DDRDETAILS_H
#define DDRDETAILS_H

#define MAX_IDX_CH 8

#define DDR_DETAILS_STRUCT_VERSION 0x0000000000030000

/** DDR types. */
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


struct ddr_freq_table{
   UINT32 freq_khz;
   UINT8  enable;
};

typedef struct ddr_freq_plan_entry_info 
{
  struct ddr_freq_table ddr_freq[14];
  UINT8  num_ddr_freqs;
  UINT32* clk_period_address;
}ddr_freq_plan_entry;

struct ddr_part_details
{

  UINT8 revision_id1[2];
  UINT8 revision_id2[2];
  UINT8 width[2];
  UINT8 density[2];
  
};

typedef struct ddr_details_entry_info 
{

  UINT8   manufacturer_id;
  UINT8   device_type;  
  struct  ddr_part_details ddr_params[MAX_IDX_CH];
  ddr_freq_plan_entry     ddr_freq_tbl;
  UINT8   num_channels;
  
}ddr_details_entry;


#endif /* DDRDETAILS_H */


