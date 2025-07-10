/**
  @file  EFIChipInfo.h
  @brief ChipInfo EFI protocol interface.
*/
/*=============================================================================
  Copyright (c) 2011-2012,2014-2017, 2019, 2022-23 Qualcomm Technologies, Incorporated.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 02/12/22   ara     Added SKU support
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

/** @addtogroup efi_chipInfo_constants
@{ */
/**
  Protocol version.
*/
#define EFI_CHIPINFO_PROTOCOL_REVISION_3 0x0000000000010003
#define EFI_CHIPINFO_PROTOCOL_REVISION_4  0x0000000000010004
#define EFI_CHIPINFO_PROTOCOL_REVISION_5  0x0000000000010005

#define EFI_CHIPINFO_PROTOCOL_REVISION EFI_CHIPINFO_PROTOCOL_REVISION_5
/** @} */ /* end_addtogroup efi_chipInfo_constants */

/*  Protocol GUID definition */
/** @ingroup efi_chipInfo_protocol */
#define EFI_CHIPINFO_PROTOCOL_GUID \
   { 0x61224FBE, 0xB240, 0x4D53, { 0xB6, 0x61, 0xA9, 0xA1, 0xF3, 0x43, 0xB0, 0x5C } }

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
/** @ingroup efi_chipInfo_getChipVersion
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
/** @ingroup efi_chipInfo_getRawChipVersion
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
/** @ingroup efi_chipInfo_getChipId
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
/** @ingroup efi_chipInfo_getRawChipId
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
/** @ingroup efi_chipInfo_getChipIdString
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
/** @ingroup efi_chipInfo_getChipFamily
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
/** @ingroup efi_chipInfo_getModemSupport
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
/** @ingroup efi_chipInfo_getProcessorNameString
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
/** @ingroup efi_chipInfo_getSerialNumber
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
/** @ingroup efi_chipInfo_getFoundryId
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
/** @ingroup efi_chipInfo_getRawDeviceFamily
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
/** @ingroup efi_chipInfo_GETRAWDEVICENUMBER
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
/** @ingroup efi_chipInfo_getQFPROMChipId
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
/** @ingroup efi_chipInfo_getMarketingNameString
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
**  Note: This API is deprecated. Please make use of 
**  EFI_ChipInfo_GetDisabledFeatures / EFI_ChipInfo_IsPartDisabled APIs
** ============================================================================
*/
/** @ingroup efi_chipInfo_getDefectivePart
  @par Summary
  Gets the defectiveness of the selected part
  Note: This API is deprecated. Please make use of 
  EFI_ChipInfo_GetDisabledFeatures / EFI_ChipInfo_IsPartDisabled APIs

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
/** @ingroup efi_chipInfo_getDefectiveCPUs
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
/** @ingroup EFI_DalChipInfo_GetSKU
 * @par Summary
 * Get SKU and Product Code information for the current device
 *
 * @param[in]   This          Pointer to the EFI_CHIPINFO_PROTOCOL instance
 * @param[out]  pInfo         pointer to a caller-allocated buffer where SKU
 *                            information will be stored
 *
 * @return
 * EFI_SUCCESS        -- Function completed successfully \n
 * EFI_NOT_FOUND      -- The provided nCPUCluster is outside the range of supported clusters \n
 * EFI_PROTOCOL_ERROR -- Other error occured during the operation
 */
typedef
EFI_STATUS
(EFIAPI *EFI_DALCHIPINFO_GETSKU)(
    IN EFI_CHIPINFO_PROTOCOL *This,
    OUT EFIChipInfoSKUInfoType *pInfo
    );

/* ============================================================================
**  Function : EFI_ChipInfo_GetNumFunctionalClusters
** ============================================================================
*/
/** @ingroup EFI_ChipInfo_GetNumFunctionalClusters
 * Get the number of functional clusters.
 *
 * This is the total number of functional clusters based on partial
 * binning and SKUing. A cluster is deemed functional if it has at least
 * one functional core. There will always be at least 1 functional
 * cluster: the one that's running this code.
 *
 * @param[out] pnNumClusters    buffer to store the number of clusters
 *
 * @return
 * EFI_SUCCESS            -- the number of clusters was successfully retrieved \n
 *                            and stored in pnNumClusters; \n
 * EFI_INVALID_PARAMETER  -- pnNumClusters is invalid; \n
 * EFI_NOT_READY          -- this function was called before EFIChipInfo has \n
 *                            initialized. *pnNumClusters will not be updated.
 */
typedef
EFI_STATUS
(EFIAPI *EFI_CHIPINFO_GETNUMFUNCTIONALCLUSTERS)(
    IN EFI_CHIPINFO_PROTOCOL *This,
    OUT UINT32 *pnNumClusters
    );

/* ============================================================================
**  Function : EFI_ChipInfo_GetBootClusterAndCore
** ============================================================================
*/
/** @ingroup EFI_ChipInfo_GetBootClusterAndCore
 * Get the boot cluster and core.
 *
 * @param[out] pnCluster   buffer to store the boot cluster index (zero-indexed).
 * @param[out] pnCore      buffer to store the boot core index (zero-indexed).
 *
 * @return
 * EFI_SUCCESS            -- both pointers were filled correctly; \n
 * EFI_INVALID_PARAMETER  -- either pointer is invalid; \n
 * EFI_NOT_READY          -- this function was called before EFIChipInfo has \n
 *                          initialized. Neither pointer will be updated.
 */
typedef
EFI_STATUS
(EFIAPI *EFI_CHIPINFO_GETBOOTCLUSTERANDCORE)(
    IN EFI_CHIPINFO_PROTOCOL *This,
    OUT UINT32 *pnCluster,
    OUT UINT32 *pnCore
    );

/* ============================================================================
**  Function : EFI_ChipInfo_GetDisabledFeatures
** ============================================================================
*/
/** @ingroup efi_chipInfo_protocol_apis
  @par Summary
  Gets the Part(IP) Specific details from the fuse.

  @param[in]   This     Pointer to the EFI_CHIPINFO_PROTOCOL instance.
  @param[in]   ePart    The EFIChipInfoPartType to check
  @param[in]   nIdx		Hardware instance of the selected part
  @param[out]  pnMask   Used to store the part specific details read from the QTV/PTE region.
                        The bit level interpretation of pnMask is specific to client and 
                        client needs to decode accordingly.

  @return
  EFI_SUCCESS         -- Function completed successfully. \n
  EFI_NOT_FOUND       -- The specified part is out of range
  EFI_PROTOCOL_ERROR  -- Error occurred during the operation.
*/
typedef
EFI_STATUS
(EFIAPI *EFI_CHIPINFO_GETDISABLEDFEATURES)(
   IN EFI_CHIPINFO_PROTOCOL *This,
   IN EFIChipInfoPartType ePart,
   IN UINT32 nIdx,
   OUT UINT32 *pnMask
   );
   
/* ============================================================================
**  Function : EFI_ChipInfo_IsPartDisabled
** ============================================================================
*/
/** @ingroup efi_chipInfo_protocol_apis
  @par Summary
  Check if the specified Part is enabled or Disabled

  @param[in]   This     Pointer to the EFI_CHIPINFO_PROTOCOL instance.
  @param[in]   ePart    The EFIChipInfoPartType to check
  @param[in]   nIdx     Hardware instance of the selected part
  @param[out]  pnMask   Pointer to boolean used to store the status of the selected part.
                        A non-zero mask implies that the part is Disabled completely.
                        FALSE => part is either completely enabled or partially enabled, 
                        TRUE => Disabled completely.
                        Clients can make use of ChipInfo_GetDisabledFeatures API
                        to obtain disabled features info.

  @return
  EFI_SUCCESS         -- Function completed successfully. \n
  EFI_NOT_FOUND       -- The specified part is out of range
  EFI_PROTOCOL_ERROR  -- Error occurred during the operation.
*/
typedef
EFI_STATUS
(EFIAPI *EFI_CHIPINFO_ISPARTDISABLED)(
   IN EFI_CHIPINFO_PROTOCOL *This,
   IN EFIChipInfoPartType ePart,
   IN UINT32 nIdx,
   OUT BOOLEAN *pnMask
   );

/* ============================================================================
**  Function : EFI_ChipInfo_GetDisabledCPUs
** ============================================================================
*/
/** @ingroup efi_chipInfo_protocol_apis
 * @par Summary
 * Gets the cores within the selected cluster which are marked "disabled"
 * in PTE fuses
 *
 * @param[in]   This          Pointer to the EFI_CHIPINFO_PROTOCOL instance
 * @param[in]   nCPUCluster   The cluster whose disabled cores need to be retrieved
 * @param[out]  pnMask        Mask of disabled cores in this cluster.
 *
 * @return
 * EFI_SUCCESS        -- Function completed successfully \n
 * EFI_NOT_FOUND      -- The provided nCPUCluster is outside the range of supported clusters \n
 * EFI_PROTOCOL_ERROR -- Other error occured during the operation
 */
typedef
EFI_STATUS
(EFIAPI *EFI_CHIPINFO_GETDISABLEDCPUS)(
    IN EFI_CHIPINFO_PROTOCOL *This,
    IN UINT32 nCPUCluster,
    OUT UINT32 *pnMask
    );

/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup efi_chipInfo_protocol
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
   EFI_DALCHIPINFO_GETSKU                 GetSKU;                   /* Added in EFI_CHIPINFO_PROTOCOL_REVISION_3 */
   EFI_CHIPINFO_GETNUMFUNCTIONALCLUSTERS  GetNumFunctionalClusters; /* Added in EFI_CHIPINFO_PROTOCOL_REVISION_4 */
   EFI_CHIPINFO_GETBOOTCLUSTERANDCORE     GetBootClusterAndCore;    /* Added in EFI_CHIPINFO_PROTOCOL_REVISION_4 */
   EFI_CHIPINFO_GETDISABLEDFEATURES       GetDisabledFeatures;       /* Added in EFI_CHIPINFO_PROTOCOL_REVISION_5 */
   EFI_CHIPINFO_ISPARTDISABLED            IsPartDisabled;            /* Added in EFI_CHIPINFO_PROTOCOL_REVISION_5 */
   EFI_CHIPINFO_GETDISABLEDCPUS           GetDisabledCPUs;           /* Added in EFI_CHIPINFO_PROTOCOL_REVISION_5 */
};

#endif /* __EFICHIPINFO_H__ */

