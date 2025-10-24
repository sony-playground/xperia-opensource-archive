/** @file BamTargetLibNull.c
  
  Stub functions for BamTargetLib

  Copyright (c) 2014, 2022 Qualcomm Technologies, Inc. All rights reserved.
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 07/26/22   VC      Added bam_settings_get_properties 
 10/08/14   ck      Initial revision

=============================================================================*/


/*==========================================================================
                               INCLUDE FILES
===========================================================================*/
#include "com_dtypes.h"

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 

/** Maximum number of execution environments supported by a BAM */
#define BAM_MAX_EES 8

/** Maximum number of supergroups supported by a BAM */
#define BAM_MAX_SGS 32

/** @brief Security Configuration for a EE
 *
 *  This struct defines a BAM device's security configuration for a given EE
 *  vmid_ac - this vmid bit mask provide BAM pipe access to BAM
 *  device.
 *  pipe_mask_ac - pipemask for whom BAM device need pipe access
 *  control.
 *
 *
 *  @note This configuration is usually performed by the SROT at boot,
 *  instead of the driver load time.
 */
typedef struct
{
   uint32 pipe_mask; /**< -- Bitmask indicating pipes allocated to this EE */
   uint32 vmid; /**< -- VMID allocated for pipes transaction & access control */
   uint32 pipe_mask_ac; /**< Bitmask indicating pipes allocated for access contol*/
   uint32 vmid_ac; /**< -- VMID allocated for pipe access control*/
} bam_ee_sec_config_type;

/** @brief Security Configuration for a SG
 *
 *  This struct defines a BAM device's security configuration for a given SG
 *
 *  @note This configuration is usually performed by the SROT at boot,
 *  instead of the driver load time.
 */
typedef struct
{
   uint32 pipe_mask; /**< -- Bitmask indicating pipes allocated to this SG */
} bam_sg_sec_config_type;

/** @brief Security Configuration for a BAM
 *
 *  This struct defines a BAM device's security configuation for all EEs.
 *
 *  @note This configuration is usually performed by the SROT at boot,
 *  instead of the driver load time.
 */

typedef struct
{
   bam_ee_sec_config_type ee[BAM_MAX_EES]; /**< -- Security configuration of
                                                   all EEs */
   bam_sg_sec_config_type sg[BAM_MAX_SGS]; /**< -- Security configuration of
                                                   all SGs */
   uint32 ctrl_vmid;  /**< -- VMID for control and debug group */
   uint32 bam_irq_ee;  /**< -- Top level intruppt will routed to this EE */
} bam_sec_config_type;

/** @brief Bam Configuration

    Provides default Bam configuration.
 */
typedef struct _bamtgtcfg
{
    uint64 bam_pa;                   /**< -- Physical address of the BAM */
    uint32 options;                  /**< -- Options to configure; see BAM_TGT_CFG */
    uint32 cfg_bits;                 /**< -- BAM chicken bits */
    uint8  ee;                       /**< -- Local execution environment index */
    bam_sec_config_type *sec_config; /**< -- Security config for the BAM */
    uint32 size;                     /**< -- Size of the register space */
}bam_target_config_type;

/*==================================================================================================
                                        FUNCTION PROTOTYPES
==================================================================================================*/

bam_target_config_type* bam_settings_get_properties(void)
{
    return NULL;
}
