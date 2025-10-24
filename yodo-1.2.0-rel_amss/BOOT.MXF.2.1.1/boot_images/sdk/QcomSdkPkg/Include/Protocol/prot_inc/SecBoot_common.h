#ifndef SECBOOT_COMMON_H_
#define SECBOOT_COMMON_H_

/** @file SecBoot_common.h

  Copyright (c)2020 Qualcomm Technologies, Incorporated. All Rights Reserved.
 
   
**/

/*==========================================================================
          EDIT HISTORY FOR FILE


when       who     what, where, why
--------   ---     ----------------------------------------------------------


==========================================================================*/

/*========================================================================

                       Type Definitions

=========================================================================*/

/* ASN.1 data holder */

/** @ingroup efi_asn1x509_protocol_data 
  @par Summary
  secasn1_data_type struct.

  @par Parameters
*/
typedef struct secasn1_data_type
{
  const UINT8 *data;
  const UINT8 *data_bound;
  UINT32       len;
} secasn1_data_type;

#endif /* SECBOOT_COMMON_H_ */
