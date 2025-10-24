#ifndef DDI_DRIVERS_H
#define DDI_DRIVERS_H

#define DDI_DRIVERS_H_MAJOR  01
#define DDI_DRIVERS_H_MINOR  02


/**
  @file ddi_drivers.h
  @brief
  Function headers of DDR drivers on all targets.
*/
/*=============================================================================
NOTE: The @brief description and any detailed descriptions above do not appear
      in the PDF.

=============================================================================*/
/*=============================================================================
  Copyright (c) 2021-2022 Qualcomm Technologies, Inc.
  All rights reserved.
  Qualcomm Technolgoies, Inc. Confidential and Proprietary.
=============================================================================*/
/*=============================================================================
                                EDIT HISTORY


when       who     what, where, why
--------   ---     ------------------------------------------------------------
04/27/21   jh      Initial revision.
=============================================================================*/
#include <ddr_common.h>

typedef enum
{
  DDI_PRE_DDR_GROUP=0x1,
  DDI_POST_DDR_GROUP=0x2,
  DDI_MEMTEST_GROUP=0x4,
  DDI_FACTORY_GROUP=0x8,
}ddi_step_param;


typedef enum
{
  DDI_EXIT_HLOS,
  DDI_EXIT_EDL,
  DDI_EXIT_RESET,
}ddi_exit_code;


typedef enum
{
  DDI_RESULT_PASS,
  DDI_RESULT_FAIL,
}ddi_result_code;


typedef enum
{
  DDI_NOOP_MODE,
  DDI_FACTORY_MODE,
  DDI_QDUTT_MEMTEST_MODE,
  DDI_QDUTT_MODE,
}ddi_mode_code;


/* ============================================================================
**  Function : ddi_pre_entry
** ============================================================================
*/
/*!
*   @brief
*   DDI entry function
*
*   @param  None.
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/
void ddi_pre_entry(void);

/* ============================================================================
**  Function : ddi_entry
** ============================================================================
*/
/*!
*   @brief
*   DDI entry function
*
*   @param  ddi_result_code
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/
ddi_exit_code ddi_entry(ddi_result_code *ddi_test_result_code );


/* ============================================================================
**  Function : ddi_set_param
** ============================================================================
*/
/*!
*   @brief
*   set DDI parameter after DDR initialization 
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/
void ddi_set_param(void);

/* ============================================================================
**  Function : ddi_get_mode
** ============================================================================
*/
/*!
*   @brief
*   Get QDUTT DDI mode
*
*   @param None
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval ddi_mode_code
*
*   @sa None
*/
ddi_mode_code ddi_get_mode(void);

/* ============================================================================
**  Function : ddi_get_DDIpartition_offset
** ============================================================================
*/
/*!
*   @brief
*   Get DDR partition offset of DDI report section
*
*   @param None
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval offset of DDR partition
*
*   @sa None
*/
uint32 ddi_get_DDIpartition_offset(void);


/* ============================================================================
**  Function : ddi_get_DDIpartition_size
** ============================================================================
*/
/*!
*   @brief
*   Get DDR partition size of DDI report section
*
*   @param None
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval size DDI outputsection in DDR partition
*
*   @sa None
*/
uint32 ddi_get_DDIpartition_size(void);


/* ============================================================================
**  Function : ddi_get_MRpartition_offset
** ============================================================================
*/
/*!
*   @brief
*   Get DDR partition offset of MR record section
*
*   @param None
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval offset of DDR partition
*
*   @sa None
*/
uint32 ddi_get_MRpartition_offset(void);


/* ============================================================================
**  Function : ddi_get_MRpartition_size
** ============================================================================
*/
/*!
*   @brief
*   Get DDR partition size of MR record section
*
*   @param None
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval size MR record outputsection in DDR partition
*
*   @sa None
*/
uint32 ddi_get_MRpartition_size(void);


#endif /* DDI_DRIVERS_H */
