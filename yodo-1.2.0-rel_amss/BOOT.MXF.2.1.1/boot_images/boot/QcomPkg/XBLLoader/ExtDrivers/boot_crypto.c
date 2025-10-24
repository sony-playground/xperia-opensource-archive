/*===========================================================================

                    BOOT CRYPTO WRAPPER DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external authentication drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2019-2020 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
11/12/20   rama    Added UCLib to crypto interface
07/23/19   ep      Created the file

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/

#include "boot_error_if.h"
#include "MIprogressive.h"
#include "boot_crypto_if.h"
#include "CeML.h"
#include <uclib.h>

/*===========================================================================
                           DEFINITIONS
===========================================================================*/


/*===========================================================================
                      FUNCTION DEFINITIONS
===========================================================================*/ 



/*===========================================================================
**  Function :  boot_crypto_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_crypto_if
*
* @par Dependencies
*   None 
* 
*/
/*
bl_error_boot_type boot_crypto_get_interface(void *ptr)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    boot_crypto_if_type *crypto_if = (boot_crypto_if_type *)ptr;
    if(crypto_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CRYPTO, BL_ERR_INVALID_PARAMETER);
      break;
    }

    crypto_if->PrngML_getdata_lite = PrngML_getdata_lite;
    crypto_if->CeMLInit = CeMLInit;
    crypto_if->CeMLHashInit = CeMLHashInit;
    crypto_if->CeMLHashUpdate = CeMLHashUpdate;
    crypto_if->CeMLHashFinal = CeMLHashFinal;
    crypto_if->CeMLHashDeInit = CeMLHashDeInit;
    crypto_if->CeMLDeInit = CeMLDeInit;
    crypto_if->CeMLHashSetParam = CeMLHashSetParam;
    crypto_if->crypto_bam_enable = NULL;  //crypto_bam_enable not suported for this target

  } while(FALSE);

  return return_status;
}
*/

boot_crypto_if_type crypto_if = {
  ucenv_get_env,
  uclib_get_prng_data,
  CeMLInit,
  CeMLHashInit,
  CeMLHashUpdate,
  CeMLHashFinal,
  CeMLHashDeInit,
  CeMLDeInit,
  CeMLHashSetParam,
  NULL  //crypto_bam_enable not suported for this target
};
