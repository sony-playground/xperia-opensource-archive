#ifndef LPM_VIOLATORS_H
#define LPM_VIOLATORS_H
/*===========================================================================
                             lpm_violators.h

DESCRIPTION:
  Debug feature to log lpm blockers.
 
Copyright (c) 2020 QUALCOMM Technologies, Inc. (QTI). All Rights Reserved.  
QUALCOMM Proprietary.  Export of this technology or software is regulated 
by the U.S. Government. Diversion contrary to U.S. law prohibited.
===========================================================================*/
typedef enum lpm_modes_supported
{
  DATA_LOGGED = 0x0,
  AOSS_SLEEP_LOGGED = 0xAA,
  CX_PC_LOGGED = 0xCC,
  DDR_LPM_LOGGED = 0xDD, 
  RPMH_RDSYST_VT_RO_MODE = 0x24, 
}LPM_MODE;

typedef enum rpmh_read_system_systems
{
   //0b1 = ARC, 0b10= BCM, 0b100 = VRM
   RPMH_RDSYST_VT_ARC = 0x1<<0,
   RPMH_RDSYST_VT_BCM = 0x1<<1,
   RPMH_RDSYST_VT_VRM = 0x1<<2,   
}RPMH_RDSYST_SYSTEMS;

/** 
 * <!-- log_lpm() -->
 *
 *  @brief: log lpm events, either exit or entry.
 *
 *  @param LPM_MODE = which type of mode was encountered
 *  @param bool: lpm_entered, true if lpm entered, false on exit
 *
 *  @return void
 */
void log_lpm(LPM_MODE stat, bool lpm_entered);

/** 
 * <!-- lpm_mon_init() -->
 *
 *  @brief: LPM monitoring init.
 *
 *  @param void: void
 *
 *  @return void
 */
void lpm_mon_init(void);

/** 
 * <!-- log_lpm_violators() -->
 *
 *  @brief: Periodic signal asserted, check what masters voted against a mode
 *
 *  @param void
 *
 *  @return void
 */
void log_lpm_violators(void);

#endif // LPM_VIOLATORS_H
