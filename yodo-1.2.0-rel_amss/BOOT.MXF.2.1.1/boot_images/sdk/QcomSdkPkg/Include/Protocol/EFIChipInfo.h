/**
  @file  EFIChipInfo.h
  @brief ChipInfo EFI protocol interface.
*/
/*=============================================================================
  Copyright (c) 2011-2012,2014-2017, 2019, 2022 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 09/08/22   ara     Added SKU support
 01/28/16   pbitra  Moved chipinfo enums to EFIChipInfoTypes.h
 05/26/15   pbitra  Added APQ8096 support.
 07/29/14   pbitra  Updated the latest ChipIds and Families.
 05/03/12   vishalo Merge in Techpubs Doxygen changes
 03/26/12   llg     (Tech Pubs) Edited/added Doxygen comments and markup.
 10/21/11   llg     (Tech Pubs) Edited/added Doxygen comments and markup.
 06/14/11   pbi     Created.
=============================================================================*/

#ifndef __EFICHIPINFO_H__
#define __EFICHIPINFO_H__


#include "EFIChipInfoTypes.h"



 /** @cond */
typedef struct _EFI_CHIPINFO_PROTOCOL EFI_CHIPINFO_PROTOCOL;
/** @endcond */

/** @addtogroup efi_chipInfo_protocol_data
@{ */
/**
  Protocol version.
*/
// v3: Added GetSKU API
#define EFI_CHIPINFO_PROTOCOL_REVISION_3  0x0000000000010003

#define EFI_CHIPINFO_PROTOCOL_REVISION EFI_CHIPINFO_PROTOCOL_REVISION_3


 /**  Protocol GUID definition */
#define EFI_CHIPINFO_PROTOCOL_GUID \
   { 0x61224FBE, 0xB240, 0x4D53, { 0xB6, 0x61, 0xA9, 0xA1, 0xF3, 0x43, 0xB0, 0x5C } }
/** @} */ /* end_addtogroup efi_chipInfo_protocol_data */
/** @cond */
/**
  External reference to the CHIPINFO Protocol GUID defined
  in the .dec file.
*/
extern EFI_GUID gEfiChipInfoProtocolGuid;
/** @endcond */

/*==============================================================================

                             API IMPLEMENTATION

==============================================================================*/


/* ============================================================================
**  Function : EFI_DalChipInfo_GetChipVersion
** ============================================================================
*/
/** @ingroup efi_chipInfo_protocol_apis
  @par Summary
  Gets the chip version.

  @param[in]   This       Pointer to the EFI_CHIPINFO_PROTOCOL instance.
  @param[out]  pnVersion  Pointer to the #EFIChipInfoVersionType type
                          passed by the caller that will be populated by
                          the driver.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef
EFI_STATUS
(EFIAPI *EFI_DALCHIPINFO_GETCHIPVERSION)(
   IN EFI_CHIPINFO_PROTOCOL *This,
   OUT EFIChipInfoVersionType *pnVersion
   );

/* ============================================================================
**  Function : EFI_DalChipInfo_GetRawChipVersion
** ============================================================================
*/
/** @ingroup efi_chipInfo_protocol_apis
  @par Summary
  Gets the chip version as read from the hardware register.

  @param[in]   This       Pointer to the EFI_CHIPINFO_PROTOCOL instance.
  @param[out]  pnVersion  Pointer to a UINT32 passed by the caller that
                          will be populated by the driver.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef
EFI_STATUS
(EFIAPI *EFI_DALCHIPINFO_GETRAWCHIPVERSION)(
   IN EFI_CHIPINFO_PROTOCOL* This,
   OUT UINT32 *pnVersion
   );

/* ============================================================================
**  Function : EFI_DalChipInfo_GetChipId
** ============================================================================
*/
/** @ingroup efi_chipInfo_protocol_apis
  @par Summary
  Gets the chip ID.

  @param[in]   This  Pointer to the EFI_CHIPINFO_PROTOCOL instance.
  @param[out]  peId  Pointer to the #EFIChipInfoIdType enumeration
                     passed by the caller that will be populated by
                     the driver.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef
EFI_STATUS
(EFIAPI *EFI_DALCHIPINFO_GETCHIPID)(
   IN EFI_CHIPINFO_PROTOCOL *This,
   OUT EFIChipInfoIdType *peId
   );

/* ============================================================================
**  Function : EFI_DalChipInfo_GetRawChipId
** ============================================================================
*/
/** @ingroup efi_chipInfo_protocol_apis
  @par Summary
  Gets the chip ID as read from the hardware register.

  @param[in]   This       Pointer to the EFI_CHIPINFO_PROTOCOL instance.
  @param[out]  pnId       Pointer to a UINT32 passed by the caller that
                          will be populated by the driver.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef
EFI_STATUS
(EFIAPI *EFI_DALCHIPINFO_GETRAWCHIPID)(
   IN EFI_CHIPINFO_PROTOCOL *This,
   OUT UINT32 *pnId
   );

/* ============================================================================
**  Function : EFI_DalChipInfo_GetChipIdString
** ============================================================================
*/
/** @ingroup efi_chipInfo_protocol_apis
  @par Summary
  Gets the string representing the chip name. The pin configuration can be
  overwritten by any user after the retrieval.

  @param[in]   This        Pointer to the EFI_CHIPINFO_PROTOCOL instance.
  @param[out]  szIdString  Pointer passed by the caller that will be
                           populated by the driver.
  @param[in]   nMaxLength  Length of the string  to be passed by the caller.
                           EFICHIPINFO_MAX_ID_LENGTH is the maximum length
                           supported.
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef
EFI_STATUS
(EFIAPI *EFI_DALCHIPINFO_GETCHIPIDSTRING)(
   IN EFI_CHIPINFO_PROTOCOL *This,
   OUT CHAR8 *szIdString,
   IN UINT32 nMaxLength
   );

/* ============================================================================
**  Function : EFI_DalChipInfo_GetChipFamily
** ============================================================================
*/
/** @ingroup efi_chipInfo_protocol_apis
  @par Summary
  Gets the chip family.

  @param[in]   This        Pointer to the EFI_CHIPINFO_PROTOCOL instance.
  @param[out]  peFamily    Pointer to the #EFIChipInfoFamilyType enumeration
                           passed by the caller that will be populated by
                           the driver.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef
EFI_STATUS
(EFIAPI *EFI_DALCHIPINFO_GETCHIPFAMILY)(
   IN EFI_CHIPINFO_PROTOCOL *This,
   OUT EFIChipInfoFamilyType *peFamily
   );

/* ============================================================================
**  Function : EFI_DalChipInfo_GetModemSupport
** ============================================================================
*/
/** @ingroup efi_chipInfo_protocol_apis
  @par Summary
  Gets the modem support information of the chip.

  @param[in]   This       Pointer to the EFI_CHIPINFO_PROTOCOL instance.
  @param[out]  pnModem    Pointer to the #EFIChipInfoModemType type
                          passed by the caller that will be populated by
                          the driver.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef
EFI_STATUS
(EFIAPI *EFI_DALCHIPINFO_GETMODEMSUPPORT)(
   IN EFI_CHIPINFO_PROTOCOL *This,
   OUT EFIChipInfoModemType *pnModem
   );


/* ============================================================================
**  Function : EFI_DalChipInfo_GetProcessorNameString
** ============================================================================
*/
/** @ingroup efi_chipInfo_protocol_apis
  @par Summary
  Gets the string representing the processor name.

  @param[in]   This        Pointer to the EFI_CHIPINFO_PROTOCOL instance.
  @param[out]  szNameString  Pointer passed by the caller that will be
                           populated by the driver.
  @param[in]   nMaxLength  Length of the string  to be passed by the caller.
                           EFICHIPINFO_MAX_NAME_LENGTH is the maximum length
                           supported.
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef
EFI_STATUS
(EFIAPI *EFI_DALCHIPINFO_GETPROCESSORNAMESTRING)(
   IN EFI_CHIPINFO_PROTOCOL *This,
   OUT CHAR8 *szNameString,
   IN UINT32 nMaxLength
   );

/* ============================================================================
**  Function : EFI_DalChipInfo_GetSerialNumber
** ============================================================================
*/
/** @ingroup efi_chipInfo_protocol_apis
  @par Summary
  Gets the Serial number of this device.

  @param[in]   This        Pointer to the EFI_CHIPINFO_PROTOCOL instance.
  @param[in,out]  peId       Pointer to a DalChipInfoSerialNumType variable
                             passed by the caller that will be populated by
                             the driver.
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef
EFI_STATUS
(EFIAPI *EFI_DALCHIPINFO_GETSERIALNUMBER)(
   IN EFI_CHIPINFO_PROTOCOL *This,
   OUT EFIChipInfoSerialNumType *peId
   );

/* ============================================================================
**  Function : EFI_DalChipInfo_GetFoundryId
** ============================================================================
*/
/** @ingroup efi_chipInfo_protocol_apis
  @par Summary
  Gets the Foundry Id.

  @param[in]   This        Pointer to the EFI_CHIPINFO_PROTOCOL instance.
  @param[in,out]  peId       Pointer to a DalChipInfoFoundryIdType type
                             structure passed by the caller that
                             will be populated by the driver.
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef
EFI_STATUS
(EFIAPI *EFI_DALCHIPINFO_GETFOUNDRYID)(
   IN EFI_CHIPINFO_PROTOCOL *This,
   OUT EFIChipInfoFoundryIdType *peId
   );




/* ============================================================================
**  Function : EFI_DalChipInfo_GetRawDeviceFamily
** ============================================================================
*/
/** @ingroup efi_chipInfo_protocol_apis
  @par Summary
   Returns the RawDeviceFamily as read from TCSR_SOC_VERSION register.

  @param[in]   This        Pointer to the EFI_CHIPINFO_PROTOCOL instance.
  @param[in,out]  peId       Pointer to a uint32 type variable
                             passed by the caller that
                             will be populated by the driver.
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef
EFI_STATUS
(EFIAPI *EFI_DALCHIPINFO_GETRAWDEVICEFAMILY)(
   IN EFI_CHIPINFO_PROTOCOL *This,
   OUT UINT32 *pnId
   );



/* ============================================================================
**  Function : EFI_DalChipInfo_GetRawDeviceNumber
** ============================================================================
*/
/** @ingroup efi_chipInfo_protocol_apis
  @par Summary
  Returns the RawDeviceNumber as read from TCSR_SOC_VERSION register.

  @param[in]   This        Pointer to the EFI_CHIPINFO_PROTOCOL instance.
  @param[in,out]  peId       Pointer to a uint32 type variable
                            passed by the caller that
                             will be populated by the driver.
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef
EFI_STATUS
(EFIAPI *EFI_DALCHIPINFO_GETRAWDEVICENUMBER)(
   IN EFI_CHIPINFO_PROTOCOL *This,
   OUT UINT32 *pnId
   );

/* ============================================================================
**  Function : EFI_DalChipInfo_GetQFPROMChipId
** ============================================================================
*/
/** @ingroup efi_chipInfo_protocol_apis
  @par Summary
  Gets the QFPROM Chip Id of this device.

  @param[in]   This        Pointer to the EFI_CHIPINFO_PROTOCOL instance.
  @param[in,out]  peId       Pointer to a DalChipInfoQFPROMChipIdType variable
                             passed by the caller that will be populated by
                             the driver.
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef
EFI_STATUS
(EFIAPI *EFI_DALCHIPINFO_GETQFPROMCHIPID)(
   IN EFI_CHIPINFO_PROTOCOL *This,
   OUT EFIChipInfoQFPROMChipIdType *pnId
   );

/* ============================================================================
**  Function : EFI_DalChipInfo_GetMarketingNameString
** ============================================================================
*/
/** @ingroup efi_chipInfo_protocol_apis
  @par Summary
  Gets the string representing the chip's marketing name.

  @param[in]   This        Pointer to the EFI_CHIPINFO_PROTOCOL instance.
  @param[out]  szNameString  Pointer passed by the caller that will be
                           populated by the driver.
  @param[in]   nMaxLength  Length of the string  to be passed by the caller.
                           EFICHIPINFO_MAX_NAME_LENGTH is the maximum length
                           supported.
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef
EFI_STATUS
(EFIAPI *EFI_DALCHIPINFO_GETMARKETINGNAMESTRING)(
   IN EFI_CHIPINFO_PROTOCOL *This,
   OUT CHAR8 *szNameString,
   IN UINT32 nMaxLength
   );

/* ============================================================================
**  Function : EFI_DalChipInfo_GetDefectivePart
** ============================================================================
*/
/** @ingroup efi_chipInfo_protocol_apis
  @par Summary
  Gets the defectiveness of the selected part

  @param[in]   This     Pointer to the EFI_CHIPINFO_PROTOCOL instance.
  @param[in]   ePart    The EFIChipInfoPartType to check
  @param[out]  pnMask   Pointer to hold a mask signifying defectiveness.
                          A non-zero mask implies that the part is defective

  @return
  EFI_SUCCESS         -- Function completed successfully. \n
  EFI_NOT_FOUND       -- The specified part is out of range
  EFI_PROTOCOL_ERROR  -- Error occurred during the operation.
*/
typedef
EFI_STATUS
(EFIAPI *EFI_DALCHIPINFO_GETDEFECTIVEPART)(
   IN EFI_CHIPINFO_PROTOCOL *This,
   IN EFIChipInfoPartType ePart,
   OUT UINT32 *pnMask
   );

/* ============================================================================
**  Function : EFI_DalChipInfo_GetDefectiveCPUs
** ============================================================================
*/
/** @ingroup efi_chipInfo_protocol_apis
 * @par Summary
 * Gets the cores within the selected cluster which are marked "defective"
 * in PTE fuses
 *
 * @param[in]   This          Pointer to the EFI_CHIPINFO_PROTOCOL instance
 * @param[in]   nCPUCluster   The cluster whose defective cores need to be retrieved
 * @param[out]  pnMask        Mask of defective cores in this cluster.
 *
 * @return
 * EFI_SUCCESS        -- Function completed successfully \n
 * EFI_NOT_FOUND      -- The provided nCPUCluster is outside the range of supported clusters \n
 * EFI_PROTOCOL_ERROR -- Other error occured during the operation
 */
typedef
EFI_STATUS
(EFIAPI *EFI_DALCHIPINFO_GETDEFECTIVECPUS)(
    IN EFI_CHIPINFO_PROTOCOL *This,
    IN UINT32 nCPUCluster,
    OUT UINT32 *pnMask
    );

/* ============================================================================
**  Function : EFI_DalChipInfo_GetSKU
** ============================================================================
*/
/** @ingroup efi_chipInfo_protocol_apis
 * @par Summary
 * Get SKU and Product Code information for the current device
 *
 * @param[in]   This          Pointer to the EFI_CHIPINFO_PROTOCOL instance
 * @param[out]  pInfo         pointer to a caller-allocated buffer where SKU
 *                            information will be stored
 *
 * @return
 * EFI_SUCCESS            -- SKU information was stored in pInfo successfully \n
 * EFI_INVALID_PARAMETER  -- pInfo was invalid \n
 * EFI_UNSUPPORTED        -- SKU information is not available \n
 * EFI_PROTOCOL_ERROR     -- Other errors
 */
typedef
EFI_STATUS
(EFIAPI *EFI_DALCHIPINFO_GETSKU)(
    IN EFI_CHIPINFO_PROTOCOL *This,
    OUT EFIChipInfoSKUType *pInfo
    );


/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup efi_chipInfo_protocol_prot
  @par Summary
  Chip Information Protocol interface.

  @par Parameters
  @inputprotoparams{chip_info_proto_params.tex}
*/
struct _EFI_CHIPINFO_PROTOCOL {
   UINT64                                 Revision;
   EFI_DALCHIPINFO_GETCHIPVERSION         GetChipVersion;
   EFI_DALCHIPINFO_GETRAWCHIPVERSION      GetRawChipVersion;
   EFI_DALCHIPINFO_GETCHIPID              GetChipId;
   EFI_DALCHIPINFO_GETRAWCHIPID           GetRawChipId;
   EFI_DALCHIPINFO_GETCHIPIDSTRING        GetChipIdString;
   EFI_DALCHIPINFO_GETCHIPFAMILY          GetChipFamily;
   EFI_DALCHIPINFO_GETMODEMSUPPORT        GetModemSupport;
   EFI_DALCHIPINFO_GETPROCESSORNAMESTRING GetProcessorNameString;
   EFI_DALCHIPINFO_GETSERIALNUMBER        GetSerialNumber;
   EFI_DALCHIPINFO_GETFOUNDRYID           GetFoundryId;
   EFI_DALCHIPINFO_GETRAWDEVICEFAMILY     GetRawDeviceFamily;
   EFI_DALCHIPINFO_GETRAWDEVICENUMBER     GetRawDeviceNumber;
   EFI_DALCHIPINFO_GETQFPROMCHIPID        GetQFPROMChipId;
   EFI_DALCHIPINFO_GETMARKETINGNAMESTRING GetMarketingNameString;
   EFI_DALCHIPINFO_GETDEFECTIVEPART       GetDefectivePart;
   EFI_DALCHIPINFO_GETDEFECTIVECPUS       GetDefectiveCPUs;
   EFI_DALCHIPINFO_GETSKU                 GetSKU;
};

#endif /* __EFICHIPINFO_H__ */

