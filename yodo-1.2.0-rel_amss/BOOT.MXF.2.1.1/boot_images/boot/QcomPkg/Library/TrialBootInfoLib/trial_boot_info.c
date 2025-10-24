/*===========================================================================

                       Trial Boot Info Source File

GENERAL DESCRIPTION
  This file contains functions to update Trial Boot Info in Trial Boot Info Partition

Copyright 2022 Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/

/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
05/27/21   sp      Initial Revision
=============================================================================*/

/*=============================================================================
                            INCLUDE FILES FOR MODULE
=============================================================================*/
#include <string.h>
#include "TrialBootInfoLib.h"
#include "trial_boot_info.h"



/*==============================================================================
**  Functions
**============================================================================*/

/*=========================================================================

**  Function :  tbi_enable_trial_boot

** ==========================================================================
*/
/*!
*
* @brief
*   This api sets trial boot enable bit and writes into storage
*
*/
trial_boot_status tbi_enable_trial_boot()
{
  trial_boot_status status = TBI_SUCCESS;
  trial_boot_info_type *trial_boot_info_ptr = NULL;

  do
  {
    status = tbi_get_trial_boot_info (&trial_boot_info_ptr);
    if (status != TBI_SUCCESS)
    {
      break;
    }

    if (trial_boot_info_ptr == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }

    trial_boot_info_ptr->trial_boot_enable = TBI_ENABLE_TRIAL_BOOT;
    status = tbi_write_partition (trial_boot_info_ptr);
    if ( status != TBI_SUCCESS)
    {
      break;
    }
  }while(FALSE);

  return status;
}

/*=========================================================================

**  Function :  tbi_is_trial_boot_enabled

** ==========================================================================
*/
/*!
*
* @brief
*   This api reads trial boot info from storage and check whether trial boot is enabled or not
*
*   @param[in] pointer to hold trial_boot_enabled value
*              0 - Trial boot is not enabled
*              1 - Trial boot is enabled
*/
trial_boot_status tbi_is_trial_boot_enabled (uint8 *is_trial_boot_enabled)
{
  trial_boot_status status = TBI_SUCCESS;
  trial_boot_info_type *trial_boot_info_ptr = NULL;
  *is_trial_boot_enabled = 0;

  do
  {
    if (is_trial_boot_enabled == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }
  
    status = tbi_get_trial_boot_info (&trial_boot_info_ptr);
    if (status != TBI_SUCCESS)
    {
      break;
    }

    if (trial_boot_info_ptr == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }

    if (trial_boot_info_ptr->magic_cookie == TBI_MAGIC_COOKIE && trial_boot_info_ptr->trial_boot_enable == TBI_ENABLE_TRIAL_BOOT)
    {
      *is_trial_boot_enabled = 0x1;
    }
  }while(FALSE);

  return status;
}

/*=========================================================================

**  Function :  tbi_max_attempts_reached

** ==========================================================================
*/
/*!
*
* @brief
*   This api reads trial boot info from storage and check whether max boot attempts of trial boots reached
*
*   @param[in] pointer to hold max_attempts_reached value
*              0 - Max attempts not reached
*              1 - Max attempts reached
*/
trial_boot_status tbi_max_attempts_reached(uint8 *is_max_attempts_reached)
{
  trial_boot_status status = TBI_SUCCESS;
  trial_boot_info_type *trial_boot_info_ptr = NULL;
  *is_max_attempts_reached = 0;

  do
  {
    if (is_max_attempts_reached == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }

    status = tbi_get_trial_boot_info (&trial_boot_info_ptr);
    if (status != TBI_SUCCESS)
    {
      break;
    }

    if (trial_boot_info_ptr == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }

    if (trial_boot_info_ptr->magic_cookie == TBI_MAGIC_COOKIE && 
        trial_boot_info_ptr->trial_boot_enable == TBI_ENABLE_TRIAL_BOOT && 
        trial_boot_info_ptr->trial_boot_failed_attempts >= trial_boot_info_ptr->trial_boot_max_attempts)
    {
      *is_max_attempts_reached = 0x1;
    }
  }while(FALSE);

  return status; 
}


/*=========================================================================

**  Function :  tbi_get_curr_failed_attempts

** ==========================================================================
*/
/*!
*
* @brief
*   This api reads trial boot info from storage and returns current number of failed boot attempts
*
*   @param[in] pointer to hold current failed attempts
*/
trial_boot_status tbi_get_curr_failed_attempts(uint32 *trial_boot_failed_attempts)
{
  trial_boot_status status = TBI_SUCCESS;
  trial_boot_info_type *trial_boot_info_ptr = NULL;
  *trial_boot_failed_attempts = 0;

  do
  {
    if (trial_boot_failed_attempts == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }

    status = tbi_get_trial_boot_info (&trial_boot_info_ptr);
    if (status != TBI_SUCCESS)
    {
      break;
    }

    if (trial_boot_info_ptr == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }

    if (trial_boot_info_ptr->magic_cookie == TBI_MAGIC_COOKIE && trial_boot_info_ptr->trial_boot_enable == TBI_ENABLE_TRIAL_BOOT)
    {
      *trial_boot_failed_attempts = trial_boot_info_ptr->trial_boot_failed_attempts;
    }
   }while(FALSE);

  return status; 
}

/*=========================================================================

**  Function :  tbi_increment_failed_boot_attempts

** ==========================================================================
*/
/*!
*
* @brief
*   This api writes current number of failed boot attempts to storage
*
*/
trial_boot_status tbi_increment_failed_boot_attempts()
{
  trial_boot_status status = TBI_SUCCESS;

  trial_boot_info_type *trial_boot_info_ptr = NULL;

  do
  {
    status = tbi_get_trial_boot_info (&trial_boot_info_ptr);
    if (status != TBI_SUCCESS)
    {
      break;
    }

    if (trial_boot_info_ptr == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }

    if (trial_boot_info_ptr->magic_cookie == TBI_MAGIC_COOKIE && trial_boot_info_ptr->trial_boot_enable == TBI_ENABLE_TRIAL_BOOT && 
        trial_boot_info_ptr->trial_boot_failed_attempts < trial_boot_info_ptr->trial_boot_max_attempts)
    {
      trial_boot_info_ptr->trial_boot_failed_attempts++;
    }
    else
    {
      status = TBI_MAX_ATTEMPTS_REACHED;
      break;
    }

    status = tbi_write_partition (trial_boot_info_ptr);
    if ( status != TBI_SUCCESS)
    {
      break;
    }
  }while(FALSE);

  return status;
}

/*=========================================================================

**  Function :  tbi_induce_trial_boot_failure

** ==========================================================================
*/
/*!
*
* @brief
*   This api writes the current_boot_failed_attempts as max_attempts ​
*
*/
trial_boot_status  tbi_induce_trial_boot_failure()
{ 
  trial_boot_status status = TBI_SUCCESS;
  trial_boot_info_type *trial_boot_info_ptr = NULL;

  do
  {
    status = tbi_get_trial_boot_info (&trial_boot_info_ptr);
    if (status != TBI_SUCCESS)
    {
      break;
    }

    if (trial_boot_info_ptr == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }

    if (trial_boot_info_ptr->magic_cookie == TBI_MAGIC_COOKIE && trial_boot_info_ptr->trial_boot_enable == TBI_ENABLE_TRIAL_BOOT)
    {
      trial_boot_info_ptr->trial_boot_failed_attempts = TBI_MAX_ATTEMPTS;
      trial_boot_info_ptr->trial_boot_max_attempts = TBI_MAX_ATTEMPTS;
      status = tbi_write_partition (trial_boot_info_ptr);
      if ( status != TBI_SUCCESS)
      {
        break;
      }
    }

  }while(FALSE);

  return status;
}


/*=========================================================================

**  Function :  tbi_clear_partition

** ==========================================================================
*/
/*!
*
* @brief
*   This api clears trial boot info partition
*
*/
trial_boot_status tbi_clear_partition()
{
  trial_boot_status status = TBI_SUCCESS;
  trial_boot_info_type *trial_boot_info_ptr = NULL;

  do
  {
    status = tbi_get_trial_boot_info (&trial_boot_info_ptr);
    if (status != TBI_SUCCESS)
    {
      break;
    }

    if (trial_boot_info_ptr == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }

    memset((void *)(trial_boot_info_ptr), 0, sizeof(trial_boot_info_type));

    status = tbi_write_partition (trial_boot_info_ptr);
  }while(FALSE);

  return status;
}