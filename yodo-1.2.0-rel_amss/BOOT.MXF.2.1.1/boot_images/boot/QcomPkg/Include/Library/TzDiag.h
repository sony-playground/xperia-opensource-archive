#ifndef __TZDIAGLIBLIB_H__
#define __TZDIAGLIBLIB_H__
/**
 * @file  TzDiag.h
 * @brief Contains prototypes for TzDiagLib. 
 */
/*
===============================================================================

                               Edit History

$Header:

when       who     what, where, why
--------   ---     ------------------------------------------------------------ 
09/09/20   dpk     Created. 

===============================================================================
              Copyright (c) 2020 QUALCOMM Technologies, Inc.
                         All Rights Reserved.
            Qualcomm Technologies Proprietary and Confidential.
===============================================================================
*/



/*=============================================================================
                      EXTERNAL FUNCTION PROTOTYPE
=============================================================================*/

/**
  This function extracts TZ Diag logs and prints in putty. It can print the logs in
  any of the below format and scenario associated to that device state. 
  Un-encrypted logs : When the device is non-secure or when TZ logs enable flag
                      is set in APDP.
  Encrypted logs    : Only when the device is secure and the encryption feature is 
                      enabled in the oem_config.xml in TZ.

  In any other case of device state, logs are not printed and this function simply
  returns.  

  @param[in] LogId    This is for future use. In case any options are required to 
                      access the logs. 

  @retval VOID

 **/
void tz_diag_log(uint8 LogId);


#endif