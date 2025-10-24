#ifndef __EFIPSLEEP_H__
#define __EFIPSLEEP_H__

/** 
  @file  EFIPsleep.h
  @brief PSleep API.
*/
/*=============================================================================
  Copyright (c) 2018 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY

 when       who     what, where, why
 --------   ---     ----------------------------------------------------------

=============================================================================*/

/** @defgroup EFI_PSLEEP_PROTOCOL 
 *  @ingroup UEFI_CORE 
 */
 /** @defgroup  EFI_PSLEEP_PROTOCOL_prot PROTOCOL
 *  @ingroup EFI_PSLEEP_PROTOCOL 
 */ 
 /** @defgroup  EFI_PSLEEP_PROTOCOL_apis APIs
 *  @ingroup EFI_PSLEEP_PROTOCOL 
 */ 

/** @defgroup  EFI_PSLEEP_PROTOCOL_data DATA_STRUCTURES
 *  @ingroup EFI_PSLEEP_PROTOCOL 
 */ 

/** @ingroup EFI_PSLEEP_PROTOCOL_data
  Protocol version.
*/
#define EFI_PSLEEP_PROTOCOL_REVISION_2 0x0000000000020000

#define EFI_PSLEEP_PROTOCOL_REVISION EFI_PSLEEP_PROTOCOL_REVISION_2

/*===========================================================================
  EXTERNAL VARIABLES
===========================================================================*/
/**
  External reference to the PSLEEP Protocol GUID
*/
extern EFI_GUID gEfiPsleepProtocolGuid;

//--------------------------------------------------------------------------
// Sleep Stats Defines 
//--------------------------------------------------------------------------
/** @ingroup EFI_PSLEEP_PROTOCOL_data 
 */
typedef struct
{
  UINT32 stat_type;	  //type of sleep stat (ascii little endian)
  UINT32 count;           //# times this mode has been entered 
  UINT64 last_entered;    //last timestamp we entered this mode
  UINT64 last_exited;     //last timestamp we exited this mode
  UINT64 total_duration;  //total amount of time we've spent in this mode
} sleep_stats_t;

/** @ingroup EFI_PSLEEP_PROTOCOL_data
 */
typedef struct
{
  UINT64 Start_UEFI_LPM_Entry;
  UINT64 End_UEFI_LPM_Entry;
  UINT64 Start_UEFI_LPM_Exit;
  UINT64 End_UEFI_LPM_Exit;
} lpm_profiling_t;

/** @ingroup EFI_PSLEEP_PROTOCOL_data 
 */
typedef enum power_sleep_stats_enum_t
{
  POWER_SLEEP_STATS_AOSD = 0, // AOSS Sleep
  POWER_SLEEP_STATS_CXSD = 1, // CX Collapse
  POWER_SLEEP_STATS_C4D4 = 2, // Apps subsystem full PC
  POWER_SLEEP_STATS_LAST = POWER_SLEEP_STATS_C4D4,
  
  POWER_SLEEP_STATS_NUM_STATS = POWER_SLEEP_STATS_LAST + 1
} power_sleep_stats_enum_t;

//--------------------------------------------------------------------------
// Sleep Callback Defines 
//-------------------------------------------------------------------------- 
/** @ingroup EFI_PSLEEP_PROTOCOL_data 
 */
typedef enum
{
  PSLEEP_CB_C4D4_ENTER,
  PSLEEP_CB_C4D4_EXIT,
}psleep_cb_mode_enum;


//--------------------------------------------------------------------------
// Protocol Defines 
//--------------------------------------------------------------------------
/** @ingroup EFI_PSLEEP_PROTOCOL_apis 
*/
typedef void (*psleep_cb_fnc)(psleep_cb_mode_enum mode, void * data);

/** @ingroup EFI_PSLEEP_PROTOCOL_apis 
 * 
*/
typedef void (*PsleepRegisterSleepCb)(
  psleep_cb_fnc fnc, void *data
);

/** @ingroup EFI_PSLEEP_PROTOCOL_apis 
*/
typedef sleep_stats_t *(*PsleepGetLpmCount)(
  power_sleep_stats_enum_t sleep_mode
);

/** @ingroup EFI_PSLEEP_PROTOCOL_apis 
*/
typedef lpm_profiling_t *(*PsleepGetLPMProfiling)(void);

/** @ingroup EFI_PSLEEP_PROTOCOL_prot 
**/
typedef struct 
{
  UINT64                Version;
  PsleepRegisterSleepCb RegisterSleepCb; //registers a callback to be invoked on the way in/out of system sleep
  PsleepGetLpmCount     GetLpmCount;     //retrieves the stats for a given low power mode 
  PsleepGetLPMProfiling LPMProfiling;    //Added in EFI_PSLEEP_PROTOCOL_REVISION_2
}EFI_PSLEEP_PROTOCOL;


#endif //__EFIPSLEEP_H__
