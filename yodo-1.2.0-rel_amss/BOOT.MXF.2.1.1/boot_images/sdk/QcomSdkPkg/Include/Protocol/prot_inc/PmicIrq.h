/** 
  @file  PmicIrq.h
  @brief PMIC IRQ related to UEFI.
*/
/*=============================================================================
Copyright (c) 2013 Qualcomm Technologies, Inc.  All Rights Reserved.
Qualcomm Technologies Proprietary and Confidential
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 02/16/13   al      created

=============================================================================*/
#ifndef __PMIC_IRQ_H__
#define __PMIC_IRQ_H__
/** @defgroup efi_pmic_gpio_protocol EFI_PMIC_GPIO_PROTOCOL
 *  @ingroup PMIC 
 */
 /** @defgroup  efi_pmic_gpio_protocol_prot PROTOCOL
 *  @ingroup efi_pmic_gpio_protocol 
 */ 
 /** @defgroup  efi_pmic_gpio_protocol_apis APIs
 *  @ingroup efi_pmic_gpio_protocol 
 */ 

/** @defgroup  efi_pmic_gpio_protocol_data DATA_STRUCTURES
 *  @ingroup efi_pmic_gpio_protocol 
 */

/** @ingroup efi_pmic_gpio_protocol_data
 * ! \enum EFI_PM_IRQ_TRIGGER_TYPE
 *  \brief Type definition for different IRQ triggers
 */
typedef enum 
{
  EFI_PM_IRQ_TRIGGER_ACTIVE_LOW,
  EFI_PM_IRQ_TRIGGER_ACTIVE_HIGH,
  EFI_PM_IRQ_TRIGGER_RISING_EDGE,
  EFI_PM_IRQ_TRIGGER_FALLING_EDGE,
  EFI_PM_IRQ_TRIGGER_DUAL_EDGE,
  EFI_PM_IRQ_TRIGGER_INVALID
} EFI_PM_IRQ_TRIGGER_TYPE;


/** @ingroup efi_pmic_gpio_protocol_data
 * ! \enum EFI_PM_IRQ_STATUS_TYPE
 *  \brief Type definition for different IRQ STATUS
 */
typedef enum
{
  EFI_PM_IRQ_STATUS_RT,
  EFI_PM_IRQ_STATUS_LATCHED,
  EFI_PM_IRQ_STATUS_PENDING,
  EFI_PM_IRQ_STATUS_INVALID
} EFI_PM_IRQ_STATUS_TYPE;





#endif /*__PMIC_IRQ_H__*/

