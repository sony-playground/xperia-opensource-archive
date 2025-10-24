#ifndef __PM_PMBUS_H__
#define __PM_PMBUS_H__


/*===========================================================================
                            PMIC VREG MODULE

DESCRIPTION
  This file contains the implementation of the VREG SMPS driver developed
  for the Qualcomm Power Management IC.

  Copyright (c) 2022 Qualcomm Technologies, Inc.  All Rights Reserved.
===========================================================================*/


/*===========================================================================
                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
06/04/21   st      New File.
===========================================================================*/


/*===========================================================================
                     INCLUDE FILES FOR MODULE
===========================================================================*/
#include "com_dtypes.h"
#include "pm_err_flags.h"
#include "pm_resources_and_types.h"
#include "Pmbus.h"
/*===========================================================================
                        TYPE DEFINITIONS
===========================================================================*/
/*!
 *  \brief 
 *  TI PMIC Index index. This enum type contains TI PMIC index that you may need. 
 */
enum
{
  PM_DBU_0,       /**< NA*/ 
  PM_DBU_1,       /**< DBU 1. MSS*/ 
  PM_DBU_2,       /**< DBU 2. MX*/
  PM_DBU_3,       /**< DBU 3. CX*/
  PM_DBU_4,       /**< DBU 4. */
  PM_DBU_5,       /**< DBU 5. */
  PM_DBU_6,       /**< DBU 6. */
  PM_DBU_7,       /**< DBU 7. */
  PM_DBU_8,       /**< DBU 8. */
  PM_DBU_9,       /**< DBU 9. */
  PM_DBU_10,      /**< DBU 10. */
  PM_DBU_11,      /**< DBU 11. */
  PM_DBU_12,      /**< DBU 12. */
  PM_DBU_13,      /**< DBU 13. casimir CX 1*/
  PM_DBU_14,      /**< DBU 14. casimir CX 2*/
  PM_DBU_15,      /**< DBU 15. casimir CX 3*/
  PM_DBU_16,      /**< DBU 16. casimir CX 4*/
  PM_DBU_17,      /**< DBU 17. casimir CX 5*/
  PM_DBU_18,      /**< DBU 18. casimir CX 6*/
  PM_DBU_19,      /**< DBU 19. casimir CX 7*/
  PM_DBU_20,      /**< DBU 20. casimir CX 8*/
  PM_DBU_INVALID  /**< Invalid DBU. */
};

/*===========================================================================

                        API PROTOTYPE

===========================================================================*/


/**
 * Sets the voltage of a TI Buck rail.
 
 *  @note1hang Differnt types of voltage rails (HFS, FTS, etc.) may have different
 *   programmable voltage steps. Only support the correct
 *   programmable steps. Do not round voltage values if the voltage
 *   selected is not part of the programmable steps.
 * 
 * @param[in] pmic_chip              
 *
 * @param[in] smps_peripheral_index  NA, added to keep it uniform with LDO/SMPS driver 
 * 
 * @param[in] volt_level Select the voltage.
 * 
 * @return 
 * Error flag type -- See #pm_err_flag_type.
 */
pm_err_flag_type 
pm_pmbus_volt_level_wrapper(uint8 pmic_chip, uint8 peripheral_index, pm_volt_level_type volt_level, boolean wait_for_settle);

#endif /* PM_PMBUS__H */
