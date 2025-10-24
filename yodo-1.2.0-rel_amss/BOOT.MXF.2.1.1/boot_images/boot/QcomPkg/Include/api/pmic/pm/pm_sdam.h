#ifndef __PM_SDAM_H__
#define __PM_SDAM_H__

/** @file pm_sdam.h
 *
 *  \brief This header file contains API and type definitions for PBS Client driver.
*/
/*
 *  Copyright (c) 2018 - 2022 Qualcomm Technologies, Inc.
 *  All Rights Reserved.
 *  Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Include/api/pmic/pm/pm_sdam.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/24/18   rl      Created.
=============================================================================*/
/*===========================================================================

                        HEADER FILES

===========================================================================*/
#include "pm_err_flags.h"
#include "com_dtypes.h"
#include "pm_resources_and_types.h"

/*===========================================================================

                        TYPE DEFINITIONS

===========================================================================*/
/**
  @enum pm_sdam_type
  @brief SDAM peripheral index
 */
typedef enum
{
  PM_SDAM_1,
  PM_SDAM_2,
  PM_SDAM_3,
  PM_SDAM_4,
  PM_SDAM_5,
  PM_SDAM_6,
  PM_SDAM_7,
  PM_SDAM_8,
  PM_SDAM_9,
  PM_SDAM_10,
  PM_SDAM_11,
  PM_SDAM_12,
  PM_SDAM_13,
  PM_SDAM_14,
  PM_SDAM_15,
  PM_SDAM_16,
  PM_SDAM_17,
  PM_SDAM_18,
  PM_SDAM_19,
  PM_SDAM_20,
  PM_SDAM_21,
  PM_SDAM_22,
  PM_SDAM_23,
  PM_SDAM_24,
  PM_SDAM_25,
  PM_SDAM_26,
  PM_SDAM_27,
  PM_SDAM_28,
  PM_SDAM_29,
  PM_SDAM_30,
  PM_SDAM_31,
  PM_SDAM_32,
  PM_SDAM_33,
  PM_SDAM_34,
  PM_SDAM_35,
  PM_SDAM_36,
  PM_SDAM_37,
  PM_SDAM_38,
  PM_SDAM_39,
  PM_SDAM_40,
  PM_SDAM_41,
  PM_SDAM_42,
  PM_SDAM_43,
  PM_SDAM_44,
  PM_SDAM_45,
  PM_SDAM_46,
  PM_SDAM_47,
  PM_SDAM_48,
  PM_SDAM_49,
  PM_SDAM_50,
  PM_SDAM_51,
  PM_SDAM_52,
  PM_SDAM_53,
  PM_SDAM_54,
  PM_SDAM_55,
  PM_SDAM_56,
  PM_SDAM_57,
  PM_SDAM_58,
  PM_SDAM_59,
  PM_SDAM_60,
  PM_SDAM_61,
  PM_SDAM_62,
  PM_SDAM_63,
  PM_SDAM_64,
  PM_SDAM_65,
  PM_SDAM_66,
  PM_SDAM_67,
  PM_SDAM_68,
  PM_SDAM_69,
  PM_SDAM_70,
  PM_SDAM_71,
  PM_SDAM_72,
  PM_SDAM_INVALID
}pm_sdam_type;

/**
  @enum pm_sdam_trig_type
  @brief Type of trigger,
         FNF or Wait for completion
 */
typedef enum
{
  PM_SDAM_TRIG_FNF,
  PM_SDAM_TRIG_WAIT,
  PM_SDAM_TRIG_INVALID,
}pm_sdam_trig_type;
/*===========================================================================

                        API PROTOTYPE

===========================================================================*/

/**
 * @name pm_sdam_trig_seq
 *
 * @brief Triggers corressponding sequence
 *
 * @param[in] pmic_chip. Primary PMIC: 0 Secondary PMIC: 1
 *
 * @param[in] rsrc_index. SDAM resource index
 *
 * @param[in] trig_arg:  Argument to be passed to SDAM for trigger sequence
 *
 * param[in] trig_fnf_wait: Currently two trigger types are supported
 *                         PM_SDAM_FNF - Fire and forget
 *                         PM_SDAM_WAIT - Wait for sequence completion
 *
 * @param[out] trig_ret_val: value returned by sdam sequence
 *
 * @return
 *  SUCCESS or Error -- See #pm_err_flag_type.
 */
pm_err_flag_type
pm_sdam_trig_seq ( uint32 pmic_chip, pm_sdam_type rsrc_index,
                   uint8 trig_arg, uint8 *trig_ret_val,
                   pm_sdam_trig_type trig_fnf_wait );


/**
 * @name pm_sdam_mem_write
 *
 * @brief Writes SDAM memory
 *
 * @param[in] pmic_chip. Primary PMIC: 0 Secondary PMIC: 1
 *
 * @param[in] rsrc_index. SDAM resource index
 *
 * @param[in] start_addr: 8-bit address from where to start writing to memory
 *                        example: 0x9 if want to start writing from 9th byte of ram
 *
 * param[in] data_ptr: Pointer to the array that needs to be written
 * @return
 *  SUCCESS or Error -- See #pm_err_flag_type.
 */
pm_err_flag_type
pm_sdam_mem_write ( uint32 pmic_chip, pm_sdam_type rsrc_index,
                    uint8 start_addr, uint32 num_bytes, uint8 *data_ptr);


/**
 * @name pm_sdam_mem_read
 *
 * @brief Reads SDAM memory
 *
 * @param[in] pmic_chip. Primary PMIC: 0 Secondary PMIC: 1
 *
 * @param[in] rsrc_index. SDAM resource index
 *
 * @param[in] start_addr: 8-bit address from where to start writing to memory
 *                        example: 0x9 if want to start writing from 9th byte of ram
 *
 * param[out] data_ptr: Pointer to the array where read bytes need to be stored
 *
 * @return
 *  SUCCESS or Error -- See #pm_err_flag_type.
 */
pm_err_flag_type
pm_sdam_mem_read ( uint32 pmic_chip, pm_sdam_type rsrc_index,
                   uint8 start_addr, uint32 num_bytes, uint8 *data_ptr);


#endif /* __PM_SDAM_H__ */
