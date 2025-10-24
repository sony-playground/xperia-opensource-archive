/*===========================================================================

                    BOOT CHIPINFO INTERFACE DEFINITIONS

DESCRIPTION
  Contains definition for chip info if

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2022 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/05/22   rama    Initial revision
===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <boot_chipinfo_if.h>


/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 

/*=========================================================================

**  FUNCTION  boot_get_chip_version

===========================================================================*/
/**
  Return the version of the chip as a ChipInfoVersionType

  This function is a wrapper around ChipInfo_GetChipVersion(). It provides
  chip version retrieval.

  @return
  ChipInfoVersionType *                -- pointer to store version of the chip
  BL_ERR_NONE                          -- on success

  @dependencies
  None.

  @sa
  ChipInfo_GetChipVersion().
*/
static bl_error_boot_type boot_get_chip_version(ChipInfoVersionType *chipinfo_version)
{
  bl_error_boot_type status = BL_ERR_NONE;

  if(chipinfo_version == NULL)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CHIPINFO_IF, BL_ERR_NULL_PTR_PASSED);
  }
  else
  {
    *chipinfo_version = ChipInfo_GetChipVersion();
  }

  return status;
}

/*=========================================================================

**  FUNCTION  boot_get_raw_chip_version

===========================================================================*/
/**
  Return the version of the chip as raw value

  This function is a wrapper around ChipInfo_GetRawChipVersion(). It provides
  raw chip version retrieval.

  @return
  uint32 *                           -- pointer to store raw version of the chip
  BL_ERR_CHIPINFO_INTERFACE_FAILURE  -- failure in interface

  @dependencies
  None.

  @sa
  ChipInfo_GetRawChipVersion().
*/
static bl_error_boot_type boot_get_raw_chip_version(uint32 *raw_chip_version)
{
  bl_error_boot_type status = BL_ERR_NONE;

  if(raw_chip_version == NULL)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CHIPINFO_IF, BL_ERR_NULL_PTR_PASSED);
  }
  else
  {
    *raw_chip_version = ChipInfo_GetRawChipVersion();
  }

  return status;
}

/*=========================================================================

**  FUNCTION  boot_get_chip_id

===========================================================================*/
/**
  Return the ID of the chip value

  This function is a wrapper around ChipInfo_GetChipId(). It provides
  chip ID retrieval.

  @return
  ChipInfoVersionType *               -- pointer to store ID of the chip
  BL_ERR_CHIPINFO_INTERFACE_FAILURE   -- failure in interface

  @dependencies
  None.

  @sa
  ChipInfo_GetChipId().
*/
static bl_error_boot_type boot_get_chip_id(ChipInfoIdType *chipinfo_id)
{
  bl_error_boot_type status = BL_ERR_NONE;

  if(chipinfo_id == NULL)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CHIPINFO_IF, BL_ERR_NULL_PTR_PASSED);
  }
  else
  {
    *chipinfo_id = ChipInfo_GetChipId();
  }

  return status;
}

/*=========================================================================

**  FUNCTION  boot_get_raw_chip_version

===========================================================================*/
/**
  Return the ID of the chip as raw value

  This function is a wrapper around ChipInfo_GetRawChipId(). It provides
  raw chip ID retrieval.

  @return
  uint32 *                            -- pointer to store raw ID of the chip
  BL_ERR_CHIPINFO_INTERFACE_FAILURE   -- failure in interface

  @dependencies
  None.

  @sa
  ChipInfo_GetRawChipId().
*/
static bl_error_boot_type boot_get_raw_chip_id(uint32 *chipinfo_raw_id)
{
  bl_error_boot_type status = BL_ERR_NONE;

  if(chipinfo_raw_id == NULL)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CHIPINFO_IF, BL_ERR_NULL_PTR_PASSED);
  }
  else
  {
    *chipinfo_raw_id = ChipInfo_GetRawChipId();
  }

  return status;
}

/*=========================================================================

**  FUNCTION  boot_get_chip_id_string

===========================================================================*/
/**
  Return the ID of the chip as string value

  This function is a wrapper around ChipInfo_GetChipIdString(). It provides
  chip ID string retrieval.

  @return
  char *                              -- buffer to store the string
  uint32                              -- max size of the buffer(CHIPINFO_MAX_ID_LENGTH)
  BL_ERR_CHIPINFO_INTERFACE_FAILURE   -- failure in interface

  @dependencies
  None.

  @sa
  ChipInfo_GetChipIdString().
*/
static bl_error_boot_type boot_get_chip_id_string(char *chipinfo_id_string, uint32 len)
{
  DALResult dal_status = DAL_SUCCESS;
  bl_error_boot_type status = BL_ERR_NONE;

  if(chipinfo_id_string == NULL || len == 0)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CHIPINFO_IF, BL_ERR_NULL_PTR_PASSED);
  }
  else
  {
    dal_status = ChipInfo_GetChipIdString(chipinfo_id_string, len);
    if(dal_status != DAL_SUCCESS)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_CHIPINFO_IF, BL_ERR_CHIPINFO_INTERFACE_FAILURE);
    }
  }

  return status;
}

/*=========================================================================

**  FUNCTION  boot_get_chip_family

===========================================================================*/
/**
  Return the family of the chip value

  This function is a wrapper around ChipInfo_GetChipFamily(). It provides
  chip family retrieval.

  @return
  ChipInfoFamilyType *                -- pointer to store family of the chip
  BL_ERR_CHIPINFO_INTERFACE_FAILURE   -- failure in interface

  @dependencies
  None.

  @sa
  ChipInfo_GetChipFamily().
*/
static bl_error_boot_type boot_get_chip_family(ChipInfoFamilyType *chipinfo_family)
{
  bl_error_boot_type status = BL_ERR_NONE;

  if(chipinfo_family == NULL)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CHIPINFO_IF, BL_ERR_NULL_PTR_PASSED);
  }
  else
  {
    *chipinfo_family = ChipInfo_GetChipFamily();
  }

  return status;
}

/*=========================================================================

**  FUNCTION  boot_get_marketing_name_string

===========================================================================*/
/**
  Return the marketing name of the chip as string value

  This function is a wrapper around ChipInfo_GetMarketingNameString(). It provides
  marketing name string retrieval.

  @return
  char *                              -- pointer to store marketing name of the chip
  uint32                              -- max length of the buffer(CHIPINFO_MAX_NAME_LEN)
  BL_ERR_CHIPINFO_INTERFACE_FAILURE   -- failure in interface

  @dependencies
  None.

  @sa
  ChipInfo_GetMarketingNameString().
*/
static bl_error_boot_type boot_get_marketing_name_string(char *chipinfo_marketing_name_string, uint32 len)
{
  DALResult dal_status = DAL_SUCCESS;
  bl_error_boot_type status = BL_ERR_NONE;

  if(chipinfo_marketing_name_string == NULL || len == 0)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CHIPINFO_IF, BL_ERR_NULL_PTR_PASSED);
  }
  else
  {
    dal_status = ChipInfo_GetMarketingNameString(chipinfo_marketing_name_string, len);
    if(dal_status != DAL_SUCCESS)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_CHIPINFO_IF, BL_ERR_CHIPINFO_INTERFACE_FAILURE);
    }
  }

  return status;
}

/*=========================================================================

**  FUNCTION  boot_get_modem_support

===========================================================================*/
/**
  Return the version of the chip as raw value

  This function is a wrapper around ChipInfo_GetModemSupport(). It provides
  modem support state retrieval.

  @return
  ChipInfoModemType *                 -- pointer to modem support state of the chip
  BL_ERR_CHIPINFO_INTERFACE_FAILURE   -- failure in interface

  @dependencies
  None.

  @sa
  ChipInfo_GetModemSupport().
*/
static bl_error_boot_type boot_get_modem_support(ChipInfoModemType *chipinfo_modem)
{
  bl_error_boot_type status = BL_ERR_NONE;

  if(chipinfo_modem == NULL)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CHIPINFO_IF, BL_ERR_NULL_PTR_PASSED);
  }
  else
  {
    *chipinfo_modem = ChipInfo_GetModemSupport();
  }

  return status;
}

/*=========================================================================

**  FUNCTION  boot_get_serial_number

===========================================================================*/
/**
  Return the serial number of the chip

  This function is a wrapper around ChipInfo_GetSerialNumber(). It provides
  chip family retrieval.

  @return
  ChipInfoSerialNumType *                 -- pointer to store serial number of the chip
  BL_ERR_CHIPINFO_INTERFACE_FAILURE   -- failure in interface

  @dependencies
  None.

  @sa
  ChipInfo_GetSerialNumber().
*/
static bl_error_boot_type boot_get_serial_number(ChipInfoSerialNumType *chipinfo_serial_num)
{
  bl_error_boot_type status = BL_ERR_NONE;

  if(chipinfo_serial_num == NULL)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CHIPINFO_IF, BL_ERR_NULL_PTR_PASSED);
  }
  else
  {
    *chipinfo_serial_num = ChipInfo_GetSerialNumber();
  }

  return status;
}

/*=========================================================================

**  FUNCTION  boot_get_foundry_id

===========================================================================*/
/**
  Return the foundry ID of the chip

  This function is a wrapper around ChipInfo_GetFoundryId(). It provides
  chip foundry ID retrieval.

  @return
  ChipInfoFoundryIdType *             -- pointer to store foundry ID of the chip
  BL_ERR_CHIPINFO_INTERFACE_FAILURE   -- failure in interface

  @dependencies
  None.

  @sa
  ChipInfo_GetFoundryId().
*/
static bl_error_boot_type boot_get_foundry_id(ChipInfoFoundryIdType *chipinfo_foundry_id)
{
  bl_error_boot_type status = BL_ERR_NONE;

  if(chipinfo_foundry_id == NULL)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CHIPINFO_IF, BL_ERR_NULL_PTR_PASSED);
  }
  else
  {
    *chipinfo_foundry_id = ChipInfo_GetFoundryId();
  }

  return status;
}

/*=========================================================================

**  FUNCTION  boot_get_raw_device_family

===========================================================================*/
/**
  Return the raw device family of the chip

  This function is a wrapper around ChipInfo_GetRawDeviceFamily(). It provides
  raw device family retrieval.

  @return
  uint32 *                            -- pointer to store device family of the chip
  BL_ERR_CHIPINFO_INTERFACE_FAILURE   -- failure in interface

  @dependencies
  None.

  @sa
  ChipInfo_GetRawDeviceFamily().
*/
static bl_error_boot_type boot_get_raw_device_family(uint32 *chipinfo_raw_device_family)
{
  bl_error_boot_type status = BL_ERR_NONE;

  if(chipinfo_raw_device_family == NULL)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CHIPINFO_IF, BL_ERR_NULL_PTR_PASSED);
  }
  else
  {
    *chipinfo_raw_device_family = ChipInfo_GetRawDeviceFamily();
  }

  return status;
}

/*=========================================================================

**  FUNCTION  boot_get_raw_device_number

===========================================================================*/
/**
  Return the raw device number of the chip

  This function is a wrapper around ChipInfo_GetRawDeviceNumber(). It provides
  raw device number retrieval.

  @return
  uint32 *                            -- pointer to store raw device number of the chip
  BL_ERR_CHIPINFO_INTERFACE_FAILURE   -- failure in interface

  @dependencies
  None.

  @sa
  ChipInfo_GetRawDeviceNumber().
*/
static bl_error_boot_type boot_get_raw_device_number(uint32 *chipinfo_raw_device_number)
{
  bl_error_boot_type status = BL_ERR_NONE;

  if(chipinfo_raw_device_number == NULL)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CHIPINFO_IF, BL_ERR_NULL_PTR_PASSED);
  }
  else
  {
    *chipinfo_raw_device_number = ChipInfo_GetRawDeviceNumber();
  }

  return status;
}

/*=========================================================================

**  FUNCTION  boot_get_qfprom_chip_id

===========================================================================*/
/**
  Return the qfprom chip ID of the chip

  This function is a wrapper around ChipInfo_GetQFPROMChipId(). It provides
  qfprom chip ID retrieval.

  @return
  ChipInfoQFPROMChipIdType *          -- pointer to store qfprom chip ID
  BL_ERR_CHIPINFO_INTERFACE_FAILURE   -- failure in interface

  @dependencies
  None.

  @sa
  ChipInfo_GetQFPROMChipId().
*/
static bl_error_boot_type boot_get_qfprom_chip_id(ChipInfoQFPROMChipIdType *qfprom_chip_id)
{
  bl_error_boot_type status = BL_ERR_NONE;

  if(qfprom_chip_id == NULL)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CHIPINFO_IF, BL_ERR_NULL_PTR_PASSED);
  }
  else
  {
    *qfprom_chip_id = ChipInfo_GetQFPROMChipId();
  }

  return status;
}

/*=========================================================================

**  FUNCTION  boot_get_defective_part

===========================================================================*/
/**
  Return the defective part of the chip

  This function is a wrapper around ChipInfo_GetDefectivePart(). It provides
  defective part retrieval.

  @return
  ChipInfoPartType *                  -- pointer to store defective part
  uint32                              -- size of buffer
  BL_ERR_CHIPINFO_INTERFACE_FAILURE   -- failure in interface

  @dependencies
  None.

  @sa
  ChipInfo_GetDefectivePart().
*/
static bl_error_boot_type boot_get_defective_part(ChipInfoPartType chipinfo_part, uint32 * mask)
{
  DALResult dal_status = DAL_SUCCESS;
  bl_error_boot_type status = BL_ERR_NONE;

  if(mask == NULL)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CHIPINFO_IF, BL_ERR_NULL_PTR_PASSED);
  }
  else
  {
    dal_status = ChipInfo_GetDefectivePart(chipinfo_part, mask);
    if(dal_status != DAL_SUCCESS)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_CHIPINFO_IF, BL_ERR_CHIPINFO_INTERFACE_FAILURE);
    }
  }

  return status;
}

/*=========================================================================

**  FUNCTION  boot_get_defective_cpus

===========================================================================*/
/**
  Return the defective part of the chip

  This function is a wrapper around ChipInfo_GetDefectiveCPUs(). It provides
  defective part retrieval.

  @return
  ChipInfoPartType *                  -- pointer to store defective part
  uint32                              -- size of buffer
  BL_ERR_CHIPINFO_INTERFACE_FAILURE   -- failure in interface

  @dependencies
  None.

  @sa
  ChipInfo_GetDefectiveCPUs().
*/
static bl_error_boot_type boot_get_defective_cpus(uint32 cpu_cluster, uint32 * mask)
{
  DALResult dal_status = DAL_SUCCESS;
  bl_error_boot_type status = BL_ERR_NONE;

  if(mask == NULL)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CHIPINFO_IF, BL_ERR_NULL_PTR_PASSED);
  }
  else
  {
    dal_status = ChipInfo_GetDefectiveCPUs(cpu_cluster, mask);
    if(dal_status != DAL_SUCCESS)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_CHIPINFO_IF, BL_ERR_CHIPINFO_INTERFACE_FAILURE);
    }
  }

  return status;
}

/*=========================================================================

**  FUNCTION  boot_get_chipinfo_data

===========================================================================*/
/**
  Return the chip ID, version and family in one call

  This function is a wrapper around ChipInfo_GetDefectiveCPUs(). It provides
  defective part retrieval.

  @return
  ChipInfoIdType *                    -- pointer to store chip id
  ChipInfoVersionType                 -- pointer to store chip version
  ChipInfoFamilyType                  -- pointer to store chip family
  BL_ERR_CHIPINFO_INTERFACE_FAILURE   -- failure in interface

  @dependencies
  None.

  @sa
  ChipInfo_GetDefectiveCPUs().
*/
static bl_error_boot_type boot_get_chipinfo_data(ChipInfoIdType *cID, ChipInfoVersionType *cVersion, ChipInfoFamilyType *cFamily)
{
  bl_error_boot_type status = BL_ERR_NONE;

  do
  {
    if(cID == NULL || cVersion == NULL || cFamily == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    status = boot_get_chip_id(cID);
    if(status != BL_ERR_NONE)
    {
      break;
    }

    status = boot_get_chip_version(cVersion);
    if(status != BL_ERR_NONE)
    {
      break;
    }

    status = boot_get_chip_family(cFamily);
    if(status != BL_ERR_NONE)
    {
      break;
    }

  }while(FALSE);

return status;
}

/*=========================================================================

**  FUNCTION  boot_chipinfo_init

===========================================================================*/
/**
  Return the defective part of the chip

  This function is a wrapper around ChipInfo_Init().

  @return
  BL_ERR_CHIPINFO_INTERFACE_FAILURE   -- failure in interface

  @dependencies
  None.

  @sa
  ChipInfo_Init().
*/
static bl_error_boot_type boot_chipinfo_init(void)
{
  DALResult dal_status = ChipInfo_Init();
  if(dal_status != DAL_SUCCESS)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_CHIPINFO_IF, BL_ERR_CHIPINFO_INTERFACE_FAILURE);
  }

  return BL_ERR_NONE;
}

boot_chipinfo_if_type chipinfo_if = {
  boot_get_chip_version,
  boot_get_raw_chip_version,
  boot_get_chip_id,
  boot_get_raw_chip_id,
  boot_get_chip_id_string,
  boot_get_chip_family,
  boot_get_marketing_name_string,
  boot_get_modem_support,
  boot_get_serial_number,
  boot_get_foundry_id,
  boot_get_raw_device_family,
  boot_get_raw_device_number,
  boot_get_qfprom_chip_id,
  boot_get_defective_part,
  boot_get_defective_cpus,
  boot_get_chipinfo_data,
  boot_chipinfo_init
};