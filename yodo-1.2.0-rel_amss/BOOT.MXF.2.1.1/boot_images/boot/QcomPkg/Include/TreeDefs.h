#ifndef _TREE_DEFS_H
#define _TREE_DEFS_H

/*===========================================================================
  Copyright (c) 2020 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  ========================================================================= */

/*===========================================================================
                      EDIT HISTORY FOR FILE


# when       who     what, where, why
# --------   ---     ---------------------------------------------------------
07/29/20     pr     Initial Version
===========================================================================*/

#define dTPM    0x6454504D  //dTPM
#define fTPM    0x6654504D  //fTPM
#define sTPM    0x7354504D  //sTPM
#define TZEXEC_SVC_MSSECAPP_GET_TPM_CONFIG   0x0004001 // Command to query TPM type from MSsecapp
#define TZEXEC_TPM_TYPE_ID   0x0080000 // Command to query TPM type from TPMsecureapp

/* Status codes */
#define SUCCESS                 0
#define FAIL                    1

/*------------------------------------------------------------
-------------------------------------------------------------*/

typedef enum _BOOT_CONFIG_TYPE {
    BOOT_CONFIG_DEFAULT = 0,
    BOOT_CONFIG_SD_EDL = 2,
    BOOT_CONFIG_USB_EDL = 3,
    BOOT_CONFIG_SD_UFS_EDL = 5,
    BOOT_CONFIG_QSPI_EDL = 6,
    BOOT_CONFIG_SPI_EDL = 7,
    BOOT_CONFIG_UFS_EDL = 8
} BOOT_CONFIG_TYPE;

typedef enum _STORAGE_TYPE {
    STORAGE_TYPE_UFS = 0xfa,
    STORAGE_TYPE_NVME = 0xfb,
    STORAGE_TYPE_EMMC = 0xfc,
    STORAGE_TYPE_INVALID = 0xff
}STORAGE_TYPE;

/*  TPM Type Request structure */
/** @cond */
typedef struct TPM_TYPE_REQ_S
{
    /* Command ID */
    UINT32  commandId;
} __attribute__ ((packed)) TPM_TYPE_REQ_T , *PTPM_TYPE_REQ_T;
/** @endcond */

/*  TPM Type Response structure */
/** @cond */
typedef struct TPM_TYPE_RSP_S
{
    /* Command ID */
    UINT32  commandId;
    /* error return */
    UINT32  status;
    /* TPM type */
    UINT32  type;
} __attribute__ ((packed)) TPM_TYPE_RSP_T, *PTPM_TYPE_RSP_T;
/** @endcond */

#endif