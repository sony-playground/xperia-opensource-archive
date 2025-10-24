#ifndef BOOT_CRYPTO_IF_H
#define BOOT_CRYPTO_IF_H
/*===========================================================================

                    BOOT EXTERN CRYPTO AUTH DRIVER DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external authentication drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2012-2015,2020 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
10/07/21   rama    Change crypto_bam_enable return type to CeMLErrorType
11/12/20   rama    Added UCLib APIs to crypto interface
05/29/20   rama    Expose crypto_bam_enable
09/24/15   kpa     Added boot_crypto_bam_enable
09/23/14   ck      Removed feature flag as API is always enabled in XBL
10/15/13   kpa     Added boot_CeMLHashSetParam
06/14/13   plc     Add boot_securemsm_write_shk
04/03/13   dh      Add boot_PrngML_getdata_lite
11/08/12   kpa     Update to directly call Crypto api's.
07/20/12   kpa     Change Api return types to success.
06/11/12   kpa     Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/

#include "boot_comdef.h"
#include "boot_error_if.h"
#include "CeML.h"
#include "uclib.h"

#define NON_BLOCK_MODE_ENABLE 0x1
#define NON_BLOCK_MODE_DISABLE 0x0

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 


typedef struct boot_crypto_if_type
{
  env_t*        (*ucenv_get_env)(void);
  size_t        (*uclib_get_prng_data)(env_t *env, uint8_t *buf, size_t buf_sz);
  CeMLErrorType (*CeMLInit)(void);
  CeMLErrorType (*CeMLHashInit)(CeMLCntxHandle ** _h, CeMLHashAlgoType pAlgo);
  CeMLErrorType (*CeMLHashUpdate)(CeMLCntxHandle *_h, CEMLIovecListType ioVecIn);
  CeMLErrorType (*CeMLHashFinal)(CeMLCntxHandle *_h, CEMLIovecListType *ioVecOut); 
  CeMLErrorType (*CeMLHashDeInit)(CeMLCntxHandle **_h);
  CeMLErrorType (*CeMLDeInit)(void);
  CeMLErrorType (*CeMLHashSetParam)(CeMLCntxHandle *_h, CeMLHashParamType nParamID, const void *pParam, uint64 cParam, CeMLHashAlgoType pAlgo);
  CeMLErrorType (*crypto_bam_enable)(void);
} boot_crypto_if_type;

typedef enum
{
  BL_ERR_UCLIB_GET_ENV       = BL_ERR_CUSTOM_ERRORS_START,
  BL_ERR_UCLIB_GET_PRNG_DATA
}bl_error_boot_crypto_type;

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
//bl_error_boot_type boot_crypto_get_interface(void *ptr);

extern boot_crypto_if_type crypto_if;
extern CeMLErrorType crypto_bam_enable(void);


#endif /* BOOT_CRYPTO_IF_H */
