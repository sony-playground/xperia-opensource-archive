/**
 *  @file seclib_ac.c
 *  @brief Access control initialization/configuration API's
 */

/**
  Copyright (c) 2021, Qualcomm Technologies, Inc. All rights reserved.
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 08/16/21   ck      Added edit history and copyright

=============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include <stdint.h>
#define SECLIB_SUCCESS 0
#define ACSecDomainId void
#define ACSecDomainPerm void
#define bool uint8_t
#define seclib_err_t uint32_t

/*----------------------------------------------------------------------------
 * Function Prototypes and Definitions
 * -------------------------------------------------------------------------*/
static void ACxBLSCClientErrReportingCtrl(uint32_t xpu_id, bool bEnable);
static int ACxBLSCFindxPUIdFromAddr(uintptr_t start_addr, uintptr_t end_addr);

/*----------------------------------------------------------------------------
 * Function definitions
 * -------------------------------------------------------------------------*/
/**
 *  @brief   Access control initialization.
 *           Refer header file for more details.
 */
seclib_err_t ACxBLSCInit(void)
{
   return SECLIB_SUCCESS;
}

/**
 *  @brief API to protect the memory regions
 */
seclib_err_t ACxBLSCxPUProtectRegion(uintptr_t start_addr, uintptr_t end_addr, ACSecDomainPerm *sdArray, uint32_t sdCount)
{
   return SECLIB_SUCCESS;	
}

/**
 *  @brief API to unprotect the memory regions
 */
seclib_err_t ACxBLSCxPUUnProtectRegion(uintptr_t start_addr, uintptr_t end_addr, ACSecDomainId *sdUnlockQAD, uint32_t sdCount)
{
   return SECLIB_SUCCESS;	
}

/**
 *  @brief API to clear the CPZ (secure) contents in DDR
 */
seclib_err_t ACClearSecureDDRRegions(void)
{
   return SECLIB_SUCCESS;	
}

/**
 *  @brief API to enable or disable error reporting
 */
seclib_err_t ACConfigureErrorReporting(uintptr_t start_addr, uintptr_t end_addr, ACSecDomainId *sdUnlockQAD, uint32_t sdCount, bool enable)
{
   return SECLIB_SUCCESS;	
}
