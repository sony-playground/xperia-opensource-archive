#ifndef __PWR_UTILS_LVL_H__
#define __PWR_UTILS_LVL_H__
/*===========================================================================
                        pwr_utils_lvl.h

DESCRIPTION:
  This file provides APIs to convert SW virtual corner/level (vlvl) to HW 
  corner/level (hlvl) and vice versa.

Copyright (c) 2019-2021 QUALCOMM Technologies, Inc. (QTI). All Rights Reserved.  
QUALCOMM Proprietary.  Export of this technology or software is regulated 
by the U.S. Government. Diversion contrary to U.S. law prohibited.
===========================================================================*/

//===========================================================================
//                      Includes and Type Definitions
//===========================================================================

//---------------------------------------------------------------------------
//  Include Files
//---------------------------------------------------------------------------
#include "comdef.h"

//---------------------------------------------------------------------------
//  Type Definitions
//---------------------------------------------------------------------------
/* Enum of all SW corners. These values are expected to remain same through
 * out the lifetime of the chip */
enum
{
  RAIL_VOLTAGE_LEVEL_OFF            = 0x0,    // 0
  RAIL_VOLTAGE_LEVEL_RET            = 0x10,   // 16
  RAIL_VOLTAGE_LEVEL_MIN_SVS        = 0x30,   // 48
  RAIL_VOLTAGE_LEVEL_LOW_SVS_D2     = 0x34,   // 52
  RAIL_VOLTAGE_LEVEL_LOW_SVS_D1     = 0x38,   // 56
  RAIL_VOLTAGE_LEVEL_LOW_SVS_D0     = 0x3C,   // 60
  RAIL_VOLTAGE_LEVEL_LOW_SVS        = 0x40,   // 64
  RAIL_VOLTAGE_LEVEL_LOW_SVS_P1     = 0x48,   // 72 
  RAIL_VOLTAGE_LEVEL_LOW_SVS_L1     = 0x50,   // 80 
  RAIL_VOLTAGE_LEVEL_LOW_SVS_L2     = 0x60,   // 96
  RAIL_VOLTAGE_LEVEL_SVS            = 0x80,   // 128
  RAIL_VOLTAGE_LEVEL_SVS_L0         = 0x90,   // 144
  RAIL_VOLTAGE_LEVEL_SVS_L1         = 0xC0,   // 192
  RAIL_VOLTAGE_LEVEL_SVS_L2         = 0xE0,   // 224
  RAIL_VOLTAGE_LEVEL_NOM            = 0x100,  // 256
  RAIL_VOLTAGE_LEVEL_NOM_L0         = 0x120,  // 288
  RAIL_VOLTAGE_LEVEL_NOM_L1         = 0x140,  // 320
  RAIL_VOLTAGE_LEVEL_NOM_L2         = 0x150,  // 336
  RAIL_VOLTAGE_LEVEL_TUR            = 0x180,  // 384
  RAIL_VOLTAGE_LEVEL_TUR_L0         = 0x190,  // 400
  RAIL_VOLTAGE_LEVEL_TUR_L1         = 0x1A0,  // 416
  RAIL_VOLTAGE_LEVEL_TUR_L2         = 0x1B0,  // 432
  RAIL_VOLTAGE_LEVEL_TUR_L3         = 0x1C0,  // 448
  RAIL_VOLTAGE_SUPER_TURBO          = 0x1D0,  // 464
  RAIL_VOLTAGE_SUPER_TURBO_NO_CPR   = 0x1E0,  // 480

  RAIL_VOLTAGE_LEVEL_MAX            = RAIL_VOLTAGE_SUPER_TURBO_NO_CPR,
  RAIL_VOLTAGE_LEVEL_NUM_LEVELS     = 25,
  RAIL_VOLTAGE_LEVEL_INVALID        = -1,
  RAIL_VOLTAGE_LEVEL_OVERLIMIT      = -2
};

/* Enum of all DDR resource levels/corners */
enum
{
  DDRSS_LEVEL_OFF = 0x0,               /* D3 + SHRM Gated + SC flush */
  DDRSS_LEVEL_PHY_COLLAPSED = 0x20,    /* D3 PHY Collapsed */
  DDRSS_LEVEL_PLL_DISABLED = 0x80,     /* PLL Disabled */
  DDRSS_LEVEL_ACTIVE = 0xA0,
  DDRSS_LEVEL_MAX = DDRSS_LEVEL_ACTIVE,
  DDRSS_LEVEL_INVALID = -1,
  DDRSS_LEVEL_NUM_LEVELS = 4
};

/* Enum for XO resource levels/corners */
enum
{
  XO_LEVEL_CRYSTAL_OFF = 0x0,
  XO_LEVEL_PMIC_BUFFER_OFF = 0x20,
  XO_LEVEL_SOC_BUFFER_OFF = 0x50,
  XO_LEVEL_ON = 0x80,
  XO_LEVEL_MAX = XO_LEVEL_ON,
  XO_LEVEL_INVALID = -1,
  XO_LEVEL_NUM_LEVELS = 4
};

/* Enum for LPI_NOC PathState resource levels/corners */
enum
{
  LPI_NOC_LEVEL_OFF = 0x0,
  LPI_NOC_LEVEL_ON  = 0x1,
  LPI_NOC_LEVEL_MAX = LPI_NOC_LEVEL_ON,
  LPI_NOC_LEVEL_INVALID = -1,
  LPI_NOC_LEVEL_NUM_LEVELS = 4
};

/* Enum for DEEP_SLEEP RM levels/corners */
enum
{
  DS_LEVEL_OFF = 0x0,
  DS_LEVEL_ON  = 0x1,
  DS_LEVEL_MAX = DS_LEVEL_ON,
  DS_LEVEL_INVALID = -1,
  DS_LEVEL_NUM_LEVELS = 4
};

/* Enum for QLINK resource levels/corners */
enum
{
  QLNK_LEVEL_OFF = 0x0,
  QLNK_LEVEL_ON  = 0x1,
  QLNK_LEVEL_MAX = QLNK_LEVEL_ON,
  QLNK_LEVEL_INVALID = -1,
  QLNK_LEVEL_NUM_LEVELS = 4
};

//---------------------------------------------------------------------------
// Constant / Define Declarations
//---------------------------------------------------------------------------
#define VOLTAGE_OFFSET  0   // VRM offsets in vote table.
#define ENABLE_OFFSET   4
#define MODE_OFFSET     8
#define HEADROOM_OFFSET 12


//===========================================================================
//                       Function Declarations
//===========================================================================

/**
 * <!-- pwr_utils_lvl_init -->
 *
 * @brief This function should be called during subsystem initialization time
 *        as it sets up resources and supported levels on a given target.
 */
void pwr_utils_lvl_init (void);

/**
 * <!-- pwr_utils_lvl_resource_idx -->
 *
 * @brief Returns the resource index corresponding to input name that
 *        can be used for subsequently for querying hlvls and vlvls.
 *
 * @note This resource index is for power utils lvl functions only. It 
 *       has no relevance outside of it.
 *
 * @param res_name: Resource name e.g. cx.lvl, mx.lvl, etc
 * 
 * @return Resource index (>=0) if successful else -1.
 */
int pwr_utils_lvl_resource_idx (const char *res_name);

/**
 * <!-- pwr_utils_hlvl -->
 *
 * @brief This function returns the HW corner (hlvl) that corresponds to 
 *        input SW corner (vlvl) and resource id.
 *
 * @see pwr_utils_lvl_resource_idx
 *
 * @param resource_idx: Resoruce index for which we are querying hlvl usually
 *                      obtained by pwr_utils_lvl_resource_idx.
 * @param vlvl: SW corner level we want to map to hlvl.
 *
 * @return HW corner level (>=0) if successful else -1.
 */
int pwr_utils_hlvl (int resource_idx, int vlvl);

/**
 * <!-- pwr_utils_hlvl_named_resource -->
 *
 * @brief This function returns the HW corner (hlvl) that corresponds to
 *        input SW corner (vlvl) and resource.
 *
 * @note Unlike @pwr_utils_hlvl, this function has to perform some extra
 *       internal look up each time to obtain HW corner. So if client
 *       expects to query same resource multiple times, he should consider
 *       using pwr_utils_hlvl instead for improved efficiency.
 *
 * @param resource: Resource name for which we are querying hlvl e.g. 
 *                  cx.lvl, mx.lvl.
 * @param vlvl: SW corner we want to map to hlvl.
 *
 * @return HW corner level (>=0) if successful else -1.
 */
int pwr_utils_hlvl_named_resource (const char *resource, int vlvl);

/**
 * <!-- pwr_utils_vlvl -->
 *
 * @brief This function returns the SW corner (vlvl) corresponding to 
 *        input HW corner (hlvl) and rail id.
 *
 * @see pwr_utils_lvl_resource_idx
 *
 * @param resource_idx: Resource index for which we are querying vlvl,
 *                      usually obtained by pwr_utils_lvl_resource_idx.
 * @param hlvl: HW corner which we want to map to SW corner (vlvl).
 *
 * @return Valid SW corner if successful else < 0
 */
int pwr_utils_vlvl (int resource_idx, int hlvl);

/**
 * <!-- pwr_utils_vlvl_named_resource -->
 *
 * @brief This function returns the SW corner (vlvl) for the input resource
 *        name and HW corner (hlvl).
 *
 * @note Unlike @pwr_utils_vlvl, this function has to perform some extra
 *       internal look up each time to obtain SW corner. So if client
 *       expects to query for same resource multiple times, he should consider
 *       using pwr_utils_vlvl instead for improved efficiency.
 *
 * @param resource: Resource name for which we are querying vlvl e.g. 
 *                  cx.lvl, mx.lvl.
 * @param hlvl: HW corner which we want to map to SW corner (vlvl).
 *
 * @return Valid SW corner if successful else < 0
 */
int pwr_utils_vlvl_named_resource (const char *resource, int hlvl);

/** 
 * <!-- pwr_utils_max_vlvl -->
 *
 * @brief Returns the max vlvl supported by the resource on this target
 */
unsigned int pwr_utils_max_vlvl (int resource_idx);

/**
 * <!-- pwr_utils_mol_vlvl -->
 *
 * @brief This function returns the Minimum operating level(MOL) in terms of vlvl
 *        of the given rail
 *
 * @see pwr_utils_lvl_resource_idx
 *
 * @param resource_idx: Resource index for which we are querying MOL,
 *                      usually obtained by pwr_utils_lvl_resource_idx.
 * 
 * @return MOL in vlvl, if successful else -1
 */
int pwr_utils_mol_vlvl (int resource_idx);

/**
 * <!-- pwr_utils_mol_hlvl -->
 *
 * @brief This function returns the Minimum operating level(MOL) in terms of hlvl
 *        of the given rail.
 *
 * @see pwr_utils_lvl_resource_idx
 *
 * @param resource_idx: Resource index for which we are querying MOL,
 *                      usually obtained by pwr_utils_lvl_resource_idx.
 * 
 * @return  MOL corner level (>=0) if successful else -1
 */
int pwr_utils_mol_hlvl (int resource_idx);

/**
 * <!-- pwr_utils_mol_hlvl_named_resource -->
 *
 * @brief This function returns the Minimum operating level(MOL) HW corner(hlvl)  
 *        corresponding to rail id.
 *
 * @note Unlike @pwr_utils_mol_hlvl, this function has to perform some extra
 *       internal look up each time to obtain SW corner. So if client
 *       expects to query for same resource multiple times, he should consider
 *       using pwr_utils_mol_hlvl instead for improved efficiency.
 *
 * @param resource: Resource name for which we are querying MOL hlvl e.g. 
 *                  cx.lvl, mx.lvl.
 *
 * @return HW corner level (>=0) if successful else -1
 */
int pwr_utils_mol_hlvl_named_resource (const char *resource);

void translate_reg_name(char* translated_name, const char *reg_name, uint32 *offset);
#endif
