/*===============================================================================
  Copyright (c) 2022 Qualcomm Technologies, Inc.  All Rights Reserved.
  
  FILE: 		EFIQcomScmi.h
  DESCRIPTION:	
  
  REVISION HISTORY
  when       who     	what, where, why
  --------   ---     	--------------------------------------------------------
  05/10/22	 yanw  	    initial version
================================================================================*/
#ifndef _EFI_QCOM_SCMI_H_
#define _EFI_QCOM_SCMI_H_

#define EFI_SCMI_VENDOR_PMU_PROTOCOL_INIT_VER           0x00010001
#define EFI_RIMPS_LOGGING_PROTOCOL_INIT_VER           	0x00010001

typedef struct _SCMI_VENDOR_PMU_PROTOCOL SCMI_VENDOR_PMU_PROTOCOL;
typedef struct _RIMPS_LOGGING_PROTOCOL	 RIMPS_LOGGING_PROTOCOL;


typedef
EFI_STATUS (EFIAPI *SCMI_VENDOR_PMU_SET_MAP) (
  IN  SCMI_VENDOR_PMU_PROTOCOL  *This,
  IN  VOID                *Buf
  );
  
typedef
EFI_STATUS (EFIAPI *SCMI_VENDOR_PMU_SET_ENABLE_TRACE) (
  IN  SCMI_VENDOR_PMU_PROTOCOL  *This
  );
  
typedef
EFI_STATUS (EFIAPI *SCMI_VENDOR_PMU_SET_DISABLE_TRACE) (
  IN  SCMI_VENDOR_PMU_PROTOCOL  *This
  );
  
typedef
EFI_STATUS (EFIAPI *RIMPS_LOGGING_ENABLE) (
  IN  RIMPS_LOGGING_PROTOCOL  *This,
  IN  UINT32					BufSizeInKb,
  IN  BOOLEAN					AutoLogToFile
  );
  
typedef
EFI_STATUS (EFIAPI *RIMPS_LOGGING_DISABLE) (
  IN  RIMPS_LOGGING_PROTOCOL  *This
  );
  
typedef
EFI_STATUS (EFIAPI *RIMPS_LOGGING_WRITE_FILE) (
  IN  RIMPS_LOGGING_PROTOCOL  *This,
  IN  CHAR16*				  FileName
  );

struct _SCMI_VENDOR_PMU_PROTOCOL {
  UINT64										Revision;
  //SCMI_VENDOR_PMU_GET_VERSION                   GetVersion;
  //SCMI_VENDOR_PMU_SET_MAP						SetPmuMap;
  SCMI_VENDOR_PMU_SET_ENABLE_TRACE				SetEnableTrace;
  SCMI_VENDOR_PMU_SET_DISABLE_TRACE				SetDisableTrace;
};

struct _RIMPS_LOGGING_PROTOCOL {
	UINT64								Revision;
	RIMPS_LOGGING_ENABLE				EnableLogging;
	RIMPS_LOGGING_DISABLE				DisableLogging;
	RIMPS_LOGGING_WRITE_FILE			WriteLogFile;
};

#endif