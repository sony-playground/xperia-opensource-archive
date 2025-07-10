#ifndef CHIPINFO_H
#define CHIPINFO_H

/*
 ===========================================================================

 FILE:         ChipInfo.h

 DESCRIPTION:
 This is the interface specification for the chip driver/service.

 ===========================================================================
 Copyright (c) 2016-2017, 2023 QUALCOMM Technologies Incorporated.

 ============================================================================
 $Header: //components/rel/aop.ho/4.0/aop_proc/core/api/systemdrivers/ChipInfo.h#3 $
 $DateTime: 2023/05/10 22:18:43 $
 $Author: pwbldsvc $
 */

/*=========================================================================
 Includes
 ==========================================================================*/
#include "DALStdDef.h"
#include "DALStdErr.h"
#include "ChipInfoDefs.h"

/** @cond */

/**
 @addtogroup functions
 @{
 */

/**
 * Returns the version of the chip as a ChipInfoVersionType
 *
 * @return  Chip version if successful,
 *          CHIPINFO_VERSION_UNKNOWN if called before ChipInfo is initialized
 */
ChipInfoVersionType ChipInfo_GetChipVersion(void);

/**
 * Returns the version of the chip as read from HW.
 * This "raw" version is a strictly increasing integer counter,
 * incremented for each new HW version. e.g.:
 * v1.0 = 0
 * v1.1 = 1
 * v1.2 = 2
 * v2.0 = 3
 * ...
 *
 * @return  Chip version as read from HW,
 *          CHIPINFO_RAW_VERSION_UNKNOWN if called before ChipInfo is initialized
 */
uint32 ChipInfo_GetRawChipVersion(void);

/**
 * Returns the chip ID as a ChipInfoIdType
 *
 * @return  Chip ID associated with the part number read from HW,
 *          CHIPINFO_ID_UNKNOWN if no associated chip id could be found, or if called before ChipInfo is initialized
 */
ChipInfoIdType ChipInfo_GetChipId(void);

/**
 * Returns the chip ID as read from HW (i.e. the JTAG ID)
 *
 * @return  Chip ID as read from HW, or
 *          CHIPINFO_RAW_ID_UNKNOWN if called before ChipInfo is initialized
 */
uint32 ChipInfo_GetRawChipId(void);

/**
 * Returns the name of the chip (e.g. MSM8998, MDM9665)
 *
 * @param[in,out] szChipIdStr   Pointer a buffer to hold the chip's name.
                                If called before ChipInfo is initialized, or if the
                                Chip ID string is unknown, the string "UNKNOWN" will
                                be copied into this buffer.
 * @param[in]     nMaxLength    Length of the string to copy. Max supported
 *                              size is CHIPINFO_MAX_ID_LENGTH
 *
 * @return  DAL_SUCCESS always
 */
DALResult ChipInfo_GetChipIdString(char *szChipIdStr, uint32 nMaxLength);

/**
 * Returns the chip's family as a ChipInfoFamilyType. This has no connection
 * to the architectural family - it's used to group all revisions of a specific chip
 *
 * @return  Chip Family if successful,
 *          CHIPINFO_FAMILY_UNKNOWN if no associated chip family can be found,
                or if called before ChipInfo is initialized
 *
 */
ChipInfoFamilyType ChipInfo_GetChipFamily(void);

/**
 * Returns the marketing name of the processor. This is typically the same 
 * as the ChipIdString.
 *
 * @param [in,out]  pszProcessorNameStr   Pointer to a buffer to hold the processor's name.
                                          If called before ChipInfo is initialized, or if the
                                          marketing name is unknown, the string "UNKNOWN" will
                                          be copied into this buffer.
 * @param [in]      nMaxLen               Length of the name buffer. At most CHIPINFO_MAX_NAME_LEN
 *                                        bytes will be copied.
 * @return  DAL_SUCCESS always
 */
DALResult ChipInfo_GetMarketingNameString(char *pszMarketingNameStr, uint32 nMaxLen);

/**
 * Returns whether or not the chip supports a modem.
 *
 * NOTE: This isn't intended to to be an exhaustive list of modems supported by this
 * chip, since there are far to many configurations to keep track of. The value
 * returned here should be treated as indicating the presence of a modem,
 * i.e. 0 = Modem not supported (e.g. SDA), nonzero = Modem supported (e.g. SDM)
 *
 * @return  Non-zero if modems are supported for this chip,
 *          CHIPINFO_MODEM_UNKNOWN if modems are not supported, or
 *            if called before ChipInfo is initialized
 */
ChipInfoModemType ChipInfo_GetModemSupport(void);

/**
 * Returns the chip's serial number
 *
 * @return  Serial number as read from HW, or
 *          CHIPINFO_SERIAL_NUM_UNKNOWN if called before ChipInfo is initialized
 */
ChipInfoSerialNumType ChipInfo_GetSerialNumber(void);

/**
 * Returns the foundry ID for the chip as a ChipInfoFoundryIdType
 *
 * @return  Foundry ID if successful,
 *          CHIPINFO_FOUNDRYID_UNKNOWN if called before ChipInfo is initialized
 */
ChipInfoFoundryIdType ChipInfo_GetFoundryId(void);

/**
 * Returns the chip's architecture family number as read from HW
 *
 * @return  Architectural family as read from HW, or
 *          CHIPINFO_RAW_DEVICE_FAMILY_UNKNOWN if called before ChipInfo is initialized
 */
uint32 ChipInfo_GetRawDeviceFamily(void);

/**
 * Returns the chip's device ID within its architectural family, as read from HW
 *
 * @return  Device number as read from HW,
 *          CHIPINFO_RAW_DEVICE_NUMBER_UNKNOWN if called before ChipInfo is initialized
 */
uint32 ChipInfo_GetRawDeviceNumber(void);

/**
 * Returns the chip's QFPROM chip ID, which can be used along with the
 * serial number to uniquely identify the chip
 *
 * @return  Chip ID as read from QFPROM fuses, if successful
 *          CHIPINFO_QFPROM_CHIPID_UNKNOWN if called before ChipInfo is initialized
 */
ChipInfoQFPROMChipIdType ChipInfo_GetQFPROMChipId(void);



/**
 * Retrieve a mask of CPUs in the current cluster which are marked as Disabled in the PTE fuses.
 * If the cluster has fewer than 32 CPUs, the additional CPUs are marked as Enabled.
 *
 * @param[in] nCPUCluster CPU cluster to check.
 * @param[out] nMask      Pointer to uint32 to hold a mask of disabled CPUs in the selected cluster
 *
 * @return  DAL_ERROR_OUT_OF_RANGE_PARAMETER  if nClusterIdx > number of clusters present
 *          DAL_ERROR for othe general errors
 *          DAL_SUCCESS otherwise
 */
DALResult ChipInfo_GetDisabledCPUs(uint32 nCPUCluster, uint32 *pnMask);

/**
 * Initialize the ChipInfo driver
 *
 * @return  DAL_SUCCESS always. Any missing/unknown information will be indicated as specified
                in the documentation for the above APIs.
 */
DALResult ChipInfo_Init(void);


/**
 * Get SKU and Product Code information for the current device.
 *
 * This information can be used to make functional decisions, e.g.,
 * selecting different DDR voltage plans.
 *
 * If the SKU_ID and/or P_CODE fuses are not blown on this device, the
 * value(s) returned by this function will be the corresponding
 * CHIPINFO_*_UNKNOWN value.
 *
 * @param[out] pInfo pointer to a caller-allocated buffer where SKU
 *                    information will be stored.
 *
 * @return CHIPINFO_ERROR_INVALID_PARAMETER if pInfo is NULL
 *         CHIPINFO_ERROR_NOT_SUPPORTED if this target doesn't support
 *          SKU information.
 *         CHIPINFO_SUCCESS otherwise
 */
ChipInfoResult ChipInfo_GetSKU(ChipInfoSKUInfoType *pInfo);

/**
 * Gets the HW Part(IP) level  Specific details from the fuse 
 * such as which all features are enabled/disabled in a HW Part.
 *
 * @param[in] ePart     The ChipInfoPartType being queried
 * @param[in] nIdx      Hardware instance of the selected part
 * @param[out] pnMask   Used to store the part specific details read from the QTV/PTE region.
 *                      The bit level interpretation of pnMask is specific to client and 
 *                      client needs to decode accordingly.
 *
 * @return CHIPINFO_ERROR_INVALID_PARAMETER if pnMask is NULL or ePart is Unknown.
 *         CHIPINFO_ERROR_OUT_OF_RANGE_PARAMETER if ePart is out of the defined range of Parts.
 *         CHIPINFO_ERROR_NOT_INITIALIZED if ChipInfoCtxt is not Initialized
 *         CHIPINFO_SUCCESS otherwise
 */
ChipInfoResult ChipInfo_GetDisabledFeatures(ChipInfoPartType ePart, uint32 nIdx, uint32 *pnMask);

/**
 * Check if the specified Part is enabled or Disabled
 *
 * @param[in] ePart     The ChipInfoPartType being queried
 * @param[in] nIdx      Hardware instance of the selected part
 * @param[out] pnMask   Pointer to boolean used to store the status of the selected part.
 *                      FALSE => part is either completely enabled or partially enabled, 
 *                      TRUE => Disabled completely.
 *                      Clients can make use of ChipInfo_GetDisabledFeatures API
 *                      to obtain disabled features info.
 *
 * @return CHIPINFO_ERROR_INVALID_PARAMETER if pnMask is NULL or ePart is Unknown.
 *         CHIPINFO_ERROR_OUT_OF_RANGE_PARAMETER if ePart is out of the defined range of Parts.
 *         CHIPINFO_ERROR_NOT_INITIALIZED if ChipInfoCtxt is not Initialized
 *         CHIPINFO_SUCCESS otherwise
 */
ChipInfoResult ChipInfo_IsPartDisabled(ChipInfoPartType ePart, uint32 nIdx, boolean *pnMask);


/**
 * @}
 */

#endif  /*  CHIPINFO_H */

