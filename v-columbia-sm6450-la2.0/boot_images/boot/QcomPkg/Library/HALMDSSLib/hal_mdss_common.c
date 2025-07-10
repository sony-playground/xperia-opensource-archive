/*=============================================================================
 
  File: hal_mdss_common.c
 
  Common mdss driver
  
 
  Copyright (c) 2011-2015 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
=============================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

#include "hal_mdss_common.h"
#include "msmhwiobase.h"
#include "mdsshalhwio.h"


/*============================================================================
*       HAL Globals
============================================================================*/

/* These are mapped addresses to the register bases supplied by OS */
uintPtr MDSS_BASE_PTR = 0;

uintPtr SEC_CTRL_BASE_PTR = 0;

/*============================================================================
*       HAL Private Functions
============================================================================*/
      

/*============================================================================
*       HAL Public Functions
============================================================================*/


/****************************************************************************
HAL_MDSS_SetBaseAddress()

Description:
*
* Setups global register base address pointers
*/
void HAL_MDSS_SetBaseAddress(HAL_MDP_SWMappedHWBaseAddressesType *pMappedBaseAddress)
{

    if (0 != pMappedBaseAddress->uMdpAddress)
    {
        MDSS_BASE_PTR      = pMappedBaseAddress->uMdpAddress;
        SEC_CTRL_BASE_PTR  = pMappedBaseAddress->uSecCtrlAddress;
    }
}

/****************************************************************************
*
** FUNCTION: HAL_MDSS_ReadRegister()
*/
/*!
* \brief
*     HAL_MDSS_ReadRegister --- Validate an address and read back the register value
*
* \param [in]   uAddress      - Address that will be read
* \param [out]  pValue        - Value read back for the specified address
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_MDSS_ReadRegister(uint32 uAddress, uint32 *pValue)
{
  HAL_MDSS_ErrorType eStatus = HAL_MDSS_STATUS_SUCCESS;

  if ((0    == MDSS_BASE_PTR) ||
      (NULL == pValue))
  {
    eStatus = HAL_MDSS_STATUS_FAILED_NOT_SUPPORTED;
  }
  else if ((uAddress  <  MDSS_BASE_PTR) ||
           (uAddress  >= (MDSS_BASE_PTR + MDSS_BASE_SIZE)))
  {
    eStatus = HAL_MDSS_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  {
   *pValue = in_dword((uint64)uAddress);
  }

  return eStatus;
}


#ifdef __cplusplus
}
#endif
