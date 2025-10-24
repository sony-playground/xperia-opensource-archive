/*============================================================================

FILE:      dog.h

DESCRIPTION: Function declarations

PUBLIC CLASSES:  Not Applicable

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A

                Copyright 2019 Qualcomm Technologies, Inc.
                         All Rights Reserved.
          Proprietary and Confidential - Qualcomm Technologies, Inc

$Header: //components/rel/aop.ho/5.0/aop_proc/core/kernel/rex/inc/common/dog.h#1 $
$Date: 2021/10/26 $

============================================================================*/

#ifndef DOG_H
#define DOG_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdint.h>

#ifdef USE_AOP_PMIC
/* Includes for PMIC wdog */
#include "pm_pon.h"

/* Includes for PMIC RTC */
#include "pm_rtc.h"
#endif /* USE_AOP_PMIC */

#define DOG_STATS_ENTRIES 4
typedef enum
{
  DOG_KICK,
  DOG_BARK,
  DOG_PAUSE,
  DOG_UNPAUSE,
  PMIC_DOG_KICK,
  PMIC_DOG_CFG,
  PMIC_DOG_DECFG,
} dog_event_type;

typedef struct 
{
  dog_event_type dog_event;
  void          *dog_event_source;
  uint64_t       timestamp;
} dog_stats_entry_type;

typedef struct
{
  dog_stats_entry_type entries[DOG_STATS_ENTRIES];
  unsigned             index;
} dog_stats_type;

/* Start the watchdog. */
void dog_init(void);

/**
 * <!-- dog_enable -->
 *
 * @brief Enable/disable wdog timer along with the timed
 *        interrupt to pet
 *  
 * @param enabled: true or false 
 * 
 * @return none
 */
void dog_enable(bool enabled);

/**
 * <!-- dog_pause -->
 *
 * @brief During local WFI AOP must disable dog
 *  
 * @param is_paused: true or false
 * @return none
 */
void dog_pause(bool is_paused);


/* PMIC WDOG */

#define PMIC_WDOG_MAX_SLEEP_TIME 0x112A8800 // 15 sec

void pmic_wdog_pet(bool unconditional);

/* PMIC RTC Logging */

void pmic_rtc_init(void);

#ifdef __cplusplus
};
#endif // __cplusplus

#endif /* DOG_H */
