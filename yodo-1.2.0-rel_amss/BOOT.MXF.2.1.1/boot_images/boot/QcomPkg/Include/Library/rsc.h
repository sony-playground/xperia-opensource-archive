#ifndef _RSC_H_
#define _RSC_H_

/*==============================================================================
  FILE:         rsc.h

  OVERVIEW:     This file contains APIs for external modules to interact with
                RSC HW block(s).

  DEPENDENCIES: None
                
                Copyright (c) 2017, 2021 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================*/

#include <stddef.h>
#include "HALcomdef.h"

/*=======================================================================
 *                           MACRO DEFINITIONS
 *======================================================================*/
#define SIMPLE_8BIT_MODE 8
#define EXTENDED_16BIT_MODE 16

#define EXTENDED_32BIT_MODE 32

#ifdef RSC_DYNAMIC_SEQ

#include "comdef.h"
#include "CoreMutex.h"
#include "CoreVerify.h"

#define RSC_SEQ_LOCK(handle)    Core_MutexLock((CoreMutex *)handle->lock)
#define RSC_SEQ_UNLOCK(handle)  Core_MutexUnlock((CoreMutex *)handle->lock)
#define RSC_MUTEX_CREATE(lock)  lock = (void *)Core_MutexCreate(CORE_MUTEXATTR_DEFAULT); \
                                CORE_VERIFY_PTR(lock)

#else /* RSC_DYNAMIC_SEQ */

#define RSC_SEQ_LOCK(handle)
#define RSC_SEQ_UNLOCK(handle)
#define RSC_MUTEX_CREATE(lock)

#endif /* RSC_DYNAMIC_SEQ */

//---------------------------------------------------------------------------
//  Type Declarations
//---------------------------------------------------------------------------
/* Enum to indicate RSC sequencer API return types. */
typedef enum
{
  RSC_SUCCESS = 0,
  RSC_INVALID_HANDLE = 1,
  RSC_INVALID_PARAM = 2,
  RSC_NO_SEQ_MEMORY = 3,
  RSC_INVALID_MODE_INDEX = 4,
  RSC_MEM_ALLOC_FAIL = 5,
  RSC_ERROR = 0xFFFFFFFF
}rsc_result_t;

/*=======================================================================
 *                           TYPE DEFINITIONS
 *======================================================================*/
/**
 * @brief Generic enumeration that can be used for different
 * RSC sequence mode ID's
 */
typedef enum
{
  /* RSC parent modes */
  RSC_PARENT_MODE_SS_LPM,    /* Subsystem sleep */
  RSC_PARENT_MODE_CHIP_LPM,  /* Subsystem sleep + PDC handshake for chip sleep */

  RSC_NUM_LOW_POWER_MODES
 }rsc_low_power_mode_type;
 
/**
 * @brief Forward declaration of RSC low power mode structure.
 */
struct rsc_hal_bsp_mode_s;

/**
 * @brief Forward declaration of RSC instance parameter info.
 */
struct rsc_hal_param_info_s;

/**
 * @brief Structure containing information about a specific RSC instance.
 */
typedef struct rsc_s
{
  const char *name;                  			/* Name of the rsc instance - same as controlled entity e.g core_n, clust_m */
  uint8 op_mode;                     			/* RSC sequencer will work in simple or extended mode (8 bit vs 16 bit) */
  struct rsc_hal_bsp_mode_s* modes;  			/* List of modes in this rsc */
  uint32 mode_count;                 			/* Number of modes supported in the above list */

  /* Internal fields */
  uint8 *phys_addr;                       /* Instance physical address in memory map */
  uint8 *addr;                        		/* Instance virtual address in memory map */
  uint8 hidden_tcs_drv_owner;             /* Hidden TCS DRV owner */
  void  *lock;                      			/* Mutex to prevent multiple operations on this instance */
  uint16  copied_cmds;                    /* Number of commands copied on this SPM instance */

  /* Dynamic mode support */
  struct rsc_hal_bsp_mode_s *dyn_modes;   /* List of dynamic modes for this RSC */
  uint32 dyn_mode_count;             			/* Number of mode in above list */

  /* Param info */
  struct rsc_hal_param_info_s *param_cfg_info; 	/* Holds RSC configuration information */

  /* Onetime boolean values */
  boolean ts_init_done;							        /* Time stamp initialization done are not */
}rsc_t;

typedef struct rsc_s* rsc_handle;
typedef uint32 rsc_cmd_t;
//typedef uint16 rsc_cmd_t;
/*=======================================================================
 *                           GLOBAL FUNCTIONS
 *======================================================================*/

 /**
 * <!-- rsc_get_count -->
 *
 * @brief Returns the number of RSC instances found for a given entity(i.e name)
 *
 * @param entity: Pointer to the RSC instance name
 *
 * @return 0 = If no RSC instances found
          >0 = if the given instance is found
 */
uint32 rsc_get_count(const char *entity);

/**
 * <!-- rsc_get_handles -->
 *
 * @brief Returns the RSC handles associated with input entity in passed
 *        buffer. It will return minimum of available handles and handle
 *        buffer size.
 *
 * @param entity: Name of the RSC handles are requested for (e.g apss etc).
 * @param count: Number of elements input buffer can accomodate.
 * @param handles: Input buffer where RSC handles will be returned.
 *
 * @return Number of RSC handles returned for the entity (ideally it should
 *         be equal to count parameter).
 */
uint32 rsc_get_handles(const char *entity, uint32 count, rsc_handle *handle);


/**
 * <!-- rsc_program_dyn_cmd_seq -->
 *
 * @brief Programs input command sequence to RSC HW dynamically.
 *
 * @param handle: Handle to the RSC where we want to program the sequence.
 * @param seq: Array of RSC commands.
 * @param seq_length: Length of above array.
 * @mode_id: Dynamic mode id assosicated with the new command sequence.
 *
 * @return RSC_SUCCESS if sequence was updated successfully else error
 *         code - see rsc_result_t.
 */

rsc_result_t rsc_program_dyn_cmd_seq(rsc_handle handle, rsc_cmd_t  *seq,
                              uint16 seq_length, uint32 *mode_id);

/**
 * <!-- rsc_trigger_seq -->
 *
 * @brief Trigger RSC sequencer for a given handle and mode id.
 *
 * @param handle: Handle to the RSC instance to trigger.
 * @param mode_id: LPM mode id to be trigger.
 *
 * @return RSC_SUCCESS if sequence was updated successfully else error
 *         code - see rsc_result_t.
 */
rsc_result_t rsc_trigger_seq(rsc_handle handle, uint32 mode_id);

/**
 * <!-- rsc_driver_init -->
 *
 * @brief Populate available RSC instances. This information is useful for the
 *        clients to initialize respective subsystem RSC.
 *
 * @note This function must be called before calling any other RSC function.
 */
void rsc_driver_init(void);

/**
 * <!-- rsc_instance_init -->
 *
 * @brief Populate RSC instance parameters for respective RSC instance i.e .pss
 *
 * @param handle: Handle to RSC instance (apss) which needs to be initialized.
 *
 * @return RSC error code (@see rsc_result_t)
 */
rsc_result_t rsc_instance_init(rsc_handle handle);

/**
 * <!-- rsc_ts_init -->
 *
 * @brief Initialize time stamp (ts) unit for RSC(apss).
 *
 * @param handle: Handle to RSC instance (apss) to which ts needs to be initialized.
 *
 * @return RSC error code (@see rsc_result_t)
 */
rsc_result_t rsc_ts_init(rsc_handle handle);

/**
 * <!-- rsc_set_low_power_mode -->
 *
 * @brief Sets a low power mode in RSC. The configured low power mode
 *        settings will take place next time RSC state machine kicks
 *        in.
 *
 * @param handle: Handle to RSC which needs to be configured for low power mode.
 * @param mode_id: Low power mode id (typically corresponds to the ones defined
 *              in subsystem HPG).
 *
 * @return RSC error code (@see rsc_result_t)
 */
rsc_result_t rsc_set_low_power_mode(rsc_handle handle, uint8 mode_id);

/**
 * <!-- rsc_get_time_stamp -->
 *
 * @brief Get the time stamp information for RSC instance and respective lpm mode_id
 *
 * @param handle: Handle to RSC which time stamp needs to be queried.
 * @param mode_id: Low power mode id (typically corresponds to the ones defined
 *              in subsystem HPG).
 *
 * @return RSC error code (@see rsc_result_t)
 */
rsc_result_t rsc_get_time_stamp(rsc_handle handle, uint8 mode_id);

/**
 * <!-- rsc_conf_hidden_tcs_ownership -->
 * 
 * @brief Configure the hidden TCS ownership to respective DRV
 *
 * @param handle: Handle to RSC which time stamp needs to be queried.
 * @param drv_id: Id of the DRV owner.
 *
 * @return RSC error code (@see rsc_result_t)
 */
rsc_result_t rsc_conf_hidden_tcs_ownership(rsc_handle handle, uint8 drv_id);


/**
 * <!-- rsc_pcie_disable_force_wake -->
 *
 * @brief Disable force wake for PCIE RSC
 *
 * @param rsc_handle: Handle to the PCIE RSC
 *
 * @return none
 */
void rsc_pcie_disable_force_wake(rsc_handle handle);

/**
 * <!-- rsc_is_pcie -->
 *
 * @brief check if the handle is a PCIE RSC
 *
 * @param handle to the RSC instance
 *
 * @return true if the RSC is PCIE.
 */
int rsc_is_pcie(rsc_handle handle);



/**
 * <!-- rsc_is_cam -->
 *
 * @brief check if the handle is a CAM RSC
 *
 * @param handle to the RSC instance
 *
 * @return true if the RSC is CAM.
 */
int rsc_is_cam(rsc_handle handle);

#endif

