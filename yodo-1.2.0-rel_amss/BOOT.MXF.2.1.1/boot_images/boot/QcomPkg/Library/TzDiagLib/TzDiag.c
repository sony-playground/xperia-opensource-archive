/**
 * @file  TzDiag.c
 * @brief Extracts TZ Diag log and display on serial console. 
 *        More information about the library structure is mentioned below.
 *
 *        Main linking settings file path. TARGET DEPENDENT ::
 *            \QcomPkg\SocPkg\<Target_Name>\Common\Core.dsc.inc
 *     
 *        This library inf file path. TARGET INDEPENDENT ::
 *            \QcomPkg\Library\TzDiagLib\TzDiag.inf
 *     
 *        Config files. TARGET INDEPENDENT ::
 *            \QcomPkg\Library\TzDiagLib\TzDiagConfig.c      (Contains target info)
 *            \QcomPkg\Library\TzDiagLib\TzDiagConfig.h
 *            \QcomPkg\Library\TzDiagLib\TzDiagConfigInfo.h  (Contains target info)
 *     
 *        Main source file and the public header file path. TARGET INDEPENDENT :: 
 *            \QcomPkg\Library\TzDiagLib\TzDiag.c
 *            \QcomPkg\Include\Library\TzDiag.h
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

#include <Uefi.h>
#include <Protocol/EFIPIL.h>
#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/QcomLib.h>
#include <Library/DebugLib.h>
#include <Library/ParserLib.h>
#include <Library/QcomTargetLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/TargetResetLib.h>
#include <Protocol/EFIDALSYSProtocol.h>
#include <Library/CacheMaintenanceLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UncachedMemoryAllocationLib.h>
#include <string.h>
#include <Library/SerialPortLib.h>
#include <Include/scm_sip_interface.h>
#include <object.h>
#include <Guid/EventGroup.h>
#include <Library/QcomBaseLib.h>
#include <Protocol/EFIScm.h>
#include <Protocol/EFIShmBridge.h>
#include <Protocol/EFIChipInfo.h>
#include <TzDiagConfig.h>



#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))
#define CONVERT_VERSION_TO_U32(major, minor, patch) \
  (((major & 0x3FF) << 22) | ((minor & 0x3FF) << 12) | (patch & 0xFFF))


// Encrypted log information.
#define TZBSP_AES_256_ENCRYPTED_KEY_SIZE 256
#define TZBSP_NONCE_LEN 12
#define TZBSP_TAG_LEN 16
#define ENCRYPTED_TZ_LOG_ID 0
#define ENCRYPTED_QSEE_LOG_ID 1
#define LOG_BUF_SIZE 0x3000

// Un-encrypted log information.
#define TZBSP_DIAG_NUM_OF_VMID 16
#define TZBSP_DIAG_INT_NUM  64
#define TZBSP_CPU_COUNT 8
#define TZBSP_DIAG_VMID_DESC_LEN 7
#define TZBSP_MAX_INT_DESC 16
#define TZ_DIAG_FEATURE_ID 6 
#define LATEST_TZ_FVER_MAJOR 9
#define LATEST_TZ_FVER_MINOR 2
#define LATEST_TZ_FVER_PATCH 0

// Debug policy information.
#define SEC_DBG_SERIAL_NUM_MAX_COUNT 200
#define SEC_DBG_CERT_ARRAY_SIZE       4


// Error codes
#define ERROR_SECURITY_STATE 0xFFFFFFFF
#define EFI_FAILURE                (80)

#define SECBOOT_OTP_ROOT_OF_TRUST_BYTE_SIZE 48

// Secure state bit positions.
typedef enum {
  SECCTRL_SECBOOT_ENABLED_SHIFT = 0x0,
  SECCTRL_SEC_HW_KEY_PROGRAMMED_SHIFT = 0x1,
  SECCTRL_DEBUG_DISABLE_CHECK_SHIFT = 0x2,
  SECCTRL_ANTI_ROLLBACK_CHECK_SHIFT = 0x3,
  SECCTRL_FUSE_CONFIG_CHECK_SHIFT = 0x4,
  SECCTRL_RPMB_PROVISIONED_CHECK_SHIFT = 0x5,
  SECCTRL_DEBUG_IMAGE_CHECK_SHIFT = 0x6,
  SECCTRL_MISC_DEBUG_CHECK_SHIFT = 0x7,
  SECCTRL_TZ_DEBUG_CHECK_SHIFT = 0x8,
  SECCTRL_MSS_DEBUG_CHECK_SHIFT = 0x9,
  SECCTRL_CP_DEBUG_CHECK_SHIFT = 0xA,
  SECCTRL_NS_DEBUG_CHECK_SHIFT = 0xB,
} tzbsp_secctrl_statue_shift;


typedef enum
{
  SMC_CALL_FAILED,
  TZ_VERSION_OLDER_THAN_920,
  TZ_VERSION_920_OR_NEWER
} version_check_t;


struct tzbsp_encr_log_t {
	/* Magic Number */
	UINT32 magic_num;
	/* version NUMBER */
	UINT32 version;
	/* encrypted log size */
	UINT32 encr_log_buff_size;
	/* Wrap value*/
	UINT16 wrap_count;
	/* AES encryption key wrapped up with oem public key*/
	UINT8 key[TZBSP_AES_256_ENCRYPTED_KEY_SIZE];
	/* Nonce used for encryption*/
	UINT8 nonce[TZBSP_NONCE_LEN];
	/* Tag to be used for Validation */
	UINT8 tag[TZBSP_TAG_LEN];
	/* Encrypted log buffer */
	UINT8 log_buf[1];
};


typedef struct tzbsp_log_pos_16_s
{
  /* Ring buffer wrap-around ctr */
  uint16_t wrap;

  /* Ring buffer current position */
  uint16_t offset;
} tzbsp_log_pos_16_t;


typedef struct tzbsp_log_pos_32_s
{
  /* Ring buffer wrap-around ctr */
  uint32_t wrap;

  /* Ring buffer current position */
  uint32_t offset;
} tzbsp_log_pos_32_t;


typedef struct tzbsp_diag_int_s
{
  /* Type of Interrupt/exception */
  uint16_t int_info;

  /* Availability of the slot */
  uint8_t avail;

  /* Reserved for future use. */
  uint8_t spare;

  /* Interrupt Number for IRQ and FIQ interrupts */
  uint32_t int_num;

  /* ASCII text describing type of interrupt e.g. Secure Timer, EBI XPU. This
   * string is always null terminated, supporting at most \c TZBSP_MAX_INT_DESC
   * characters. Any additional characters are truncated. */
  uint8_t int_desc[TZBSP_MAX_INT_DESC];

  /* Number of this interrupt seen per CPU. */
  uint32_t int_count[TZBSP_CPU_COUNT];
} tzbsp_diag_int_t;


/* Reset Infor Table */
typedef struct tzbsp_diag_reset_info_s
{
  /* Reset Reason - Security Violation */
  uint32 reset_type;

  /* Number of resets that occured for above CPU */
  uint32 reset_cnt;
} tzbsp_diag_reset_info_t;


/* warm boot reason for cores */
typedef struct tzbsp_diag_wakeup_info_s
{
  /* Wake source info : APCS_GICC_HPPIR */
  uint32 HPPIR;
  /* Wake source info : APCS_GICC_AHPPIR */
  uint32 AHPPIR;

} tzbsp_diag_wakeup_info_t;


typedef struct tzbsp_diag_log_16_s
{
  /* Ring buffer position mgmt */
  tzbsp_log_pos_16_t   log_pos;

  /* open ended array to the end of the 4K IMEM buffer */
  uint8             log_buf[1];
} tzbsp_diag_log_16_t;


typedef struct tzbsp_diag_log_32_s
{
  /* Ring buffer position mgmt */
  tzbsp_log_pos_32_t   log_pos;

  /* open ended array to the end of the 4K IMEM buffer */
  uint8             log_buf[1];
} tzbsp_diag_log_32_t;


typedef PACKED struct tzbsp_diag_vmid_s
{
  /* Virtual Machine Identifier */
  uint8 vmid;

  /* ASCII Text */
  uint8 desc[TZBSP_DIAG_VMID_DESC_LEN];
} tzbsp_diag_vmid_t;


/* Boot Info Table */
typedef struct tzbsp_diag_boot_info_s
{
  /* Warmboot entry CPU Counter */
  uint32_t warm_entry_cnt;

  /* Warmboot exit CPU Counter */
  uint32_t warm_exit_cnt;

  /* Power collapse termination entry counter. */
  uint32_t term_entry_cnt;

  /* Power collapse termination exit counter. The number of times CPU fell
   * through the WFI without entering power collapse. */
  uint32_t term_exit_cnt;

  /* Warmboot entry CPU Counter */
  uint32_t psci_entry_cnt;

  /* Warmboot exit CPU Counter */
  uint32_t psci_exit_cnt;

  /* Last Warmboot Jump Address */
  uint64_t warm_jmp_addr;

  /* Last Warmboot Jump Address Instruction */
  uint32_t warm_jmp_instr;
} tzbsp_diag_boot_info_t;


/* Diagnostic Table */
typedef struct tzbsp_diag_16_s
{
  /* Magic Number */
  uint32_t magic_num;

  /* Major.Minor version */
  uint32_t version;

  /* Number of CPU's */
  uint32_t cpu_count;

  /* Offset of VMID Table */
  ////TODO:  this should go.
  uint32_t vmid_info_off;

  /* Offset of Boot Table */
  uint32_t boot_info_off;

  /* Offset of Reset Table */
  uint32_t reset_info_off;

  /* Offset of Interrupt Table */
  uint32_t int_info_off;

  /* Ring Buffer Offset */
  uint32_t ring_off;

  /* Ring Buffer Len */
  uint32_t ring_len;

  /* Offset for Wakeup info */
  uint32_t wakeup_info_off;

  /* VMID to EE Mapping. */ //TODO:  this should go.
  tzbsp_diag_vmid_t vmid[TZBSP_DIAG_NUM_OF_VMID];

  /* Boot Info */
  tzbsp_diag_boot_info_t  boot_info[TZBSP_CPU_COUNT];

  /* Reset Info */
  tzbsp_diag_reset_info_t reset_info[TZBSP_CPU_COUNT];

  /* Length of the interrupt table */
  uint32_t num_interrupts;
  tzbsp_diag_int_t  int_info[TZBSP_DIAG_INT_NUM];

  /* Wake up info */
  tzbsp_diag_wakeup_info_t  wakeup_info[TZBSP_CPU_COUNT];

  uint8_t key[TZBSP_AES_256_ENCRYPTED_KEY_SIZE];

  uint8_t nonce[TZBSP_NONCE_LEN];

  uint8_t tag[TZBSP_TAG_LEN];

  /* We need at least 2K for the ring buffer */
  /* TZ Ring Buffer */
  tzbsp_diag_log_16_t log;
} tzbsp_diag_16_t;


typedef struct tzbsp_diag_32_s
{
  /* Magic Number */
  uint32_t magic_num;

  /* Major.Minor version */
  uint32_t version;

  /* Number of CPU's */
  uint32_t cpu_count;

  /* Offset of VMID Table */
  ////TODO:  this should go.
  uint32_t vmid_info_off;

  /* Offset of Boot Table */
  uint32_t boot_info_off;

  /* Offset of Reset Table */
  uint32_t reset_info_off;

  /* Offset of Interrupt Table */
  uint32_t int_info_off;

  /* Ring Buffer Offset */
  uint32_t ring_off;

  /* Ring Buffer Len */
  uint32_t ring_len;

  /* Offset for Wakeup info */
  uint32_t wakeup_info_off;

  /* VMID to EE Mapping. */ //TODO:  this should go.
  tzbsp_diag_vmid_t vmid[TZBSP_DIAG_NUM_OF_VMID];

  /* Boot Info */
  tzbsp_diag_boot_info_t  boot_info[TZBSP_CPU_COUNT];

  /* Reset Info */
  tzbsp_diag_reset_info_t reset_info[TZBSP_CPU_COUNT];

  /* Length of the interrupt table */
  uint32_t num_interrupts;
  tzbsp_diag_int_t  int_info[TZBSP_DIAG_INT_NUM];

  /* Wake up info */
  tzbsp_diag_wakeup_info_t  wakeup_info[TZBSP_CPU_COUNT];

  uint8_t key[TZBSP_AES_256_ENCRYPTED_KEY_SIZE];

  uint8_t nonce[TZBSP_NONCE_LEN];

  uint8_t tag[TZBSP_TAG_LEN];

  /* We need at least 2K for the ring buffer */
  /* TZ Ring Buffer */
  tzbsp_diag_log_32_t log;
} tzbsp_diag_32_t;


typedef struct __attribute__((__packed__))
{
    uint32_t magic; /* Version of Debug Policy */
    uint32_t size;  /* Fixed size debug policy*/
    uint32_t revision; /* Revision of the debug policy*/
    struct {
            uint32_t enable_online_crash_dumps          :  1;
            uint32_t enable_offline_crash_dumps         :  1;
            uint32_t enable_jtag                        :  1;
            uint32_t enable_logs                        :  1;
            uint32_t enable_modem_inv_debug             :  1;
            uint32_t enable_modem_ninv_debug            :  1;
            uint32_t enable_apps_inv_debug              :  1;
            uint32_t enable_debug_level_bit0            :  1;
            uint32_t enable_debug_level_bit1            :  1;
            uint32_t reserved_bits_with_serialnum       : 15; // reserved for QCT, must be 0
            uint32_t enable_nonsecure_crash_dumps       :  1;
            uint32_t enable_apps_encrypted_mini_dumps   :  1;
            uint32_t enable_mpss_encrypted_mini_dumps   :  1;
            uint32_t enable_lpass_encrypted_mini_dumps  :  1;
            uint32_t enable_css_encrypted_mini_dumps    :  1;
            uint32_t enable_adsp_encrypted_mini_dumps   :  1;
            uint32_t enable_cdsp_encrypted_mini_dumps   :  1;
            uint32_t enable_wlan_encrypted_mini_dumps   :  1;
            uint32_t reserved_bits_without_serialnum    : 16; // reserved for QCT, must be 0
            uint32_t oem_reserved_bits                  : 16; // reserved for OEM
    } flags;
    uint32_t image_id_bitmap; /* Image ID Bit Map */
    uint32_t root_cert_hash_count; /* Root Cert Hash Count */
    uint8_t  root_cert_hash_array[SEC_DBG_CERT_ARRAY_SIZE][SECBOOT_OTP_ROOT_OF_TRUST_BYTE_SIZE]; /* Hash Array*/
    int32_t serial_num_count; /* Serial Number Count */
    uint32_t serial_num_array[SEC_DBG_SERIAL_NUM_MAX_COUNT]; /* Serial Numbers */
    uint32_t root_cert_hash_count_qc; /* Root Cert Hash Count */
    uint8_t  root_cert_hash_array_qc[SEC_DBG_CERT_ARRAY_SIZE][SECBOOT_OTP_ROOT_OF_TRUST_BYTE_SIZE]; /* Hash Array*/
} sec_dbg;

//void *tz_diag_get_tz_log_struct (void);
//BOOLEAN tz_diag_is_encryption_supported(void);


static tzbsp_diag_config_info_t *pTzDiagConfigInfo = NULL;
static BOOLEAN bIsTzDiagInitialized = FALSE;
static void *pTzDiagImemAddr = NULL;
static BOOLEAN bIsTzDiagEncFeatSupported = FALSE;

/*=============================================================================
                      Internal FUNCTION DEFINITIONS
=============================================================================*/

static EFI_STATUS tz_diag_initialization(void)
{
    EFI_STATUS             status = EFI_FAILURE;
    EFI_CHIPINFO_PROTOCOL  *mChipInfoProtocol;
    EFIChipInfoFamilyType  ChipFamily = EFICHIPINFO_FAMILY_UNKNOWN;

    if (bIsTzDiagInitialized)
    {
        return EFI_SUCCESS;
    }
        
    do 
    {
        status = gBS->LocateProtocol (
                      &gEfiChipInfoProtocolGuid,
                      NULL,
                      (VOID **) &mChipInfoProtocol
                      );
        if (EFI_ERROR(status))
        {
            DEBUG((EFI_D_ERROR,"Failed to locate chipinfo protocol %r\n",status));
            break;
        }
        
        status = mChipInfoProtocol->GetChipFamily(mChipInfoProtocol,&ChipFamily);
        if (EFI_ERROR(status))
        {
            DEBUG((EFI_D_ERROR,"failed to read ChipFamily :%r\n",status));
            break;
        }
		
        pTzDiagConfigInfo = tz_diag_get_config_info(ChipFamily);
        if (pTzDiagConfigInfo == NULL)
        {
            DEBUG((EFI_D_ERROR,"No config info found for this target\n"));
            break;
        }
		
        pTzDiagImemAddr = (void *)((*((UINTN *)(pTzDiagConfigInfo->pDiagAddr))) & 0xFFFFFFFF);
        bIsTzDiagEncFeatSupported = pTzDiagConfigInfo->bIsDiagEncFeatSupported;
		
        bIsTzDiagInitialized = TRUE;
        status = EFI_SUCCESS;
    } while(0);

    return status;
}

/**
  This function is used to get protocol interface for the syscall driver.
  This interface is used to access some of the functionalities in TZ using system calls.

  @param[in] VOID
 
  @retval Valid interface Pointer, if it succeed.
  @retval Otherwise NULL

 **/
 static QCOM_SCM_PROTOCOL *tz_diag_get_qcom_protocol(void)
{
    static QCOM_SCM_PROTOCOL *pScmProtocol = NULL;
    EFI_STATUS status;

    if (pScmProtocol == NULL)
    {
        status = gBS->LocateProtocol (&gQcomScmProtocolGuid, NULL, (VOID**)&pScmProtocol); 
        if (EFI_ERROR(status))
        {
            pScmProtocol = NULL;
            DEBUG((EFI_D_ERROR,"tz_diag_get_qcom_protocol(): LocateProtocol failed. Error: 0x%x \n", status));
        }
    }

    return pScmProtocol;
}

/**
  This function is used to get the current secure state of the device.
  This is used to identify whether the device is secure or not.

  @param[out] pSecurityState    Pointer to hold the security state of the device, 
                                upon successful execution of this function.
  @param[out] Size              Size of the array pointed by pSecurityState.
 
  @retval EFI_SUCCESS  If no error.
  @retval Otherwise    Error specific to scenario.

 **/
static EFI_STATUS tz_diag_get_security_state(UINT32 *pSecurityState, UINT32 Size)
{
    QCOM_SCM_PROTOCOL *pScmProtocol = NULL;
    EFI_STATUS status = EFI_FAILURE;
    UINT64 param[SCM_MAX_NUM_PARAMETERS] = {0};
    UINT64 results[SCM_MAX_NUM_RESULTS] = {0};
    tz_get_secure_state_rsp_t *pSysCallRsp = (tz_get_secure_state_rsp_t *)results;
    UINT32 i = 0;

    do
    {
        if (pSecurityState == NULL)
        {
            status = EFI_INVALID_PARAMETER;
            break;
        }

        // Reset the state.
        for (i = 0; i < Size; i++)
        {
            pSecurityState[i] = 0;
        }

        pScmProtocol = tz_diag_get_qcom_protocol();
        if (pScmProtocol == NULL)
        {
            break;
        }

        status = pScmProtocol->ScmSipSysCall(pScmProtocol, 
                                             TZ_INFO_GET_SECURE_STATE, 
                                             TZ_INFO_GET_SECURE_STATE_PARAM_ID, 
                                             param, 
                                             results);
        if (EFI_ERROR(status)) 
        {
            DEBUG((EFI_D_ERROR, "tz_diag_get_security_state(): System call failed. Error: 0x%x \n", status));
            status = ERROR_SECURITY_STATE;
            break;
        }

        if (pSysCallRsp->common_rsp.status != 1) 
        {
            DEBUG((EFI_D_WARN, "tz_diag_get_security_state(): Invalid response, (0x%x)",pSysCallRsp->common_rsp.status));
            status = ERROR_SECURITY_STATE;
            break;
        }

        *pSecurityState = (UINT32)pSysCallRsp->status_0;
    } while(0);

    return status;
}

/**
  This function is used to check whether the device is secure or not,
  based on the information obtained from get secure state.

  @param[out] pIsSecureDevice    Pointer to hold the device state, 
                                 upon successful execution of this function.
  
  @retval EFI_SUCCESS  If no error.
  @retval Otherwise    Error specific to scenario.

 **/
static EFI_STATUS tz_diag_is_secure_device(BOOLEAN *pIsSecureDevice)
{
    EFI_STATUS status = EFI_FAILURE;
    UINT32 secure_state = 0;

    do
    {
        if (pIsSecureDevice == NULL)
        {
            status = EFI_INVALID_PARAMETER;
            break;
        }
        *pIsSecureDevice = FALSE;

        status = tz_diag_get_security_state(&secure_state, 1);
        if (EFI_ERROR(status)) 
        {
            break;
        }

        if (!CHECK_BIT(secure_state, SECCTRL_SECBOOT_ENABLED_SHIFT) && 
            !CHECK_BIT(secure_state, SECCTRL_TZ_DEBUG_CHECK_SHIFT) && 
            !CHECK_BIT(secure_state, SECCTRL_CP_DEBUG_CHECK_SHIFT)) 
        {
            *pIsSecureDevice = TRUE;
        }
		
    } while(0);

    return status;
}

/**
  This function is used to get the debug policy information.

  @param[out] pDebugPolicy    Pointer to which the debug policy information is copied to, 
                              upon successful execution of this function.
  @param[in]  Size            Size of pDebugPolicy structure.

  @retval EFI_SUCCESS  If no error.
  @retval Otherwise    Error specific to scenario.

 **/
static EFI_STATUS tz_diag_get_debug_policy(sec_dbg *pDebugPolicy, UINT32 Size)
{
    static BOOLEAN is_debug_policy_available = FALSE;
    sec_dbg *p_debug_policy = (sec_dbg*)UncachedAllocateAlignedPool(sizeof(sec_dbg), 4096);
    EFI_STATUS status = EFI_FAILURE;
    UINT64 param[SCM_MAX_NUM_PARAMETERS] = {0};
    UINT64 results[SCM_MAX_NUM_RESULTS] = {0};
    QCOM_SCM_PROTOCOL *pScmProtocol = NULL;

    do
    {
        if ((p_debug_policy == NULL) || (pDebugPolicy == NULL) || (Size != sizeof(sec_dbg)))
        {
            status = EFI_INVALID_PARAMETER;
            break;
        }
        memset(pDebugPolicy, 0, sizeof(sec_dbg));

        if (!is_debug_policy_available)
        {
            if (p_debug_policy == NULL)
            {
                status = EFI_INVALID_PARAMETER;
                break;
            }
            memset(p_debug_policy, 0, sizeof(sec_dbg));

            param[0] = (UINT64)p_debug_policy;
            param[1] = (UINT64)sizeof(sec_dbg);

            pScmProtocol = tz_diag_get_qcom_protocol();
            if (pScmProtocol == NULL)
            {
                break;
            }

            status = pScmProtocol->ScmSipSysCall(pScmProtocol, 
                                                 TZ_READ_DEBUG_POLICY_CONTENT, 
                                                 TZ_READ_DEBUG_POLICY_CONTENT_PARAM_ID, 
                                                 param, 
                                                 results);
            if (EFI_ERROR(status))
            {
                DEBUG((EFI_D_ERROR,"tz_diag_get_debug_policy(): System call failed. Error: 0x%x \n", status));
                break;
            }
        }

        memscpy(pDebugPolicy, Size, p_debug_policy, sizeof(sec_dbg));
    } while(0);

    return status;
}

/**
  This function is used to check the version, which in turn used to interpret the IMEM area,
  in unencrypted logs case. 

  @param[out] pVersion    Holds the version number if this function executes successfully.

  @retval EFI_SUCCESS  If no error.
  @retval Otherwise    Error specific to scenario.

 **/
static EFI_STATUS tz_diag_version_check(version_check_t *pVersion)
{
    EFI_STATUS status = EFI_FAILURE;
    UINT64 param[SCM_MAX_NUM_PARAMETERS] = {0};
    UINT64 results[SCM_MAX_NUM_RESULTS] = {0};
    tz_feature_version_req_t *pSysCallReq = (tz_feature_version_req_t*)param;
    tz_feature_version_rsp_t *pSysCallRsp = (tz_feature_version_rsp_t*)results;
    QCOM_SCM_PROTOCOL *pScmProtocol = NULL;
	UINT32 latest_version = 0;
    static BOOLEAN tz_version_available = FALSE;

    do
    {
        if (tz_version_available == TRUE)
        {
            status = EFI_SUCCESS;
            break;
        }

        if (pVersion == NULL)
        {
            status = EFI_INVALID_PARAMETER;
            break;
        }
		
        pScmProtocol = tz_diag_get_qcom_protocol();
        if (pScmProtocol == NULL)
        {
            break;
        }

        pSysCallReq->feature_id = TZ_DIAG_FEATURE_ID;
        status = pScmProtocol->ScmSipSysCall (pScmProtocol,
                                              TZ_INFO_GET_FEATURE_VERSION_ID,
                                              TZ_INFO_GET_FEATURE_VERSION_ID_PARAM_ID,
                                              param,
                                              results);
        if (EFI_ERROR(status)) 
        {
            DEBUG((EFI_D_ERROR, "tz_diag_get_feature_version(): System call failed. Error: 0x%x \n", status));
            break;
        }
		
        if (pSysCallRsp->common_rsp.status != 1) {
            status = EFI_DEVICE_ERROR;
            DEBUG((EFI_D_ERROR, "tz_diag_get_feature_version(): Invalid response, 0x%x \n", pSysCallRsp->common_rsp.status));
            break;
        }
		
        latest_version = CONVERT_VERSION_TO_U32(LATEST_TZ_FVER_MAJOR, LATEST_TZ_FVER_MINOR, LATEST_TZ_FVER_PATCH);
		if (pSysCallRsp->version < latest_version) 
        {
            *pVersion = TZ_VERSION_OLDER_THAN_920;
        } 
        else 
        {
            *pVersion = TZ_VERSION_920_OR_NEWER;
        }

        tz_version_available = TRUE;
    } while(0);

  return status;
}

/**
  This function must be called only when it is confirmed that the logs are not
  encrypted and can access IMEM directly.

  @param VOID

  @retval VOID

 **/
static void tz_diag_read_display_unencrpted_log(void)
{
    CHAR8* log_start = NULL;
    UINT32 log_len_1 = 0, log_len_2 = 0;
    void *pTzLog = NULL;
    UINT32 log_buf_size = 0;
    version_check_t version_check = SMC_CALL_FAILED;
    UINT32 i = 0;
    tzbsp_log_pos_32_t latest_tz_log_pos = {0};
    EFI_STATUS status = EFI_FAILURE;

    DEBUG((EFI_D_ERROR,"\n------------- TZ DIAG LOG START -------------\n"));

    do
	{
        /* This checks whether the TZ Diag logs in unencrypted format supported or not */
        pTzLog = pTzDiagImemAddr;
        if (pTzLog == NULL)
        {
          DEBUG((EFI_D_INFO,"tz_diag_read_display_unencrpted_log(): Invalid diag structure base."));
          break;
        }

        status = tz_diag_version_check(&version_check);
        if (EFI_ERROR(status)) 
        {
            DEBUG((EFI_D_ERROR, "tz_diag_read_display_unencrpted_log(): Version check failed. Error: 0x%x \n", status));
            break;
        }

        if (TZ_VERSION_OLDER_THAN_920 == version_check) 
        {
          log_buf_size = ((tzbsp_diag_16_t *) pTzLog)->ring_len;
          log_start = (CHAR8*)pTzLog + ((tzbsp_diag_16_t *) pTzLog)->ring_off + latest_tz_log_pos.offset;
          if ((((tzbsp_diag_16_t *) pTzLog)->log).log_pos.wrap == latest_tz_log_pos.wrap) 
          {
            log_len_1 = (((tzbsp_diag_16_t *) pTzLog)->log).log_pos.offset - latest_tz_log_pos.offset;
            for (i = 0; i < log_len_1; i++)
            {
              DEBUG((EFI_D_ERROR,"%c", log_start[i]));
            }
          }
          else if ((((tzbsp_diag_16_t *) pTzLog)->log).log_pos.wrap == latest_tz_log_pos.wrap + 1 && \
                (((tzbsp_diag_16_t *) pTzLog)->log).log_pos.offset <= latest_tz_log_pos.offset) 
          {
            log_len_1 = log_buf_size - latest_tz_log_pos.offset;
            for (i = 0; i < log_len_1; i++)
            {
              DEBUG((EFI_D_ERROR,"%c", log_start[i]));
            }
            if ((((tzbsp_diag_16_t *) pTzLog)->log).log_pos.offset != 0) 
            {
              log_len_2 = (((tzbsp_diag_16_t *) pTzLog)->log).log_pos.offset;
              for (i = 0; i < log_len_2; i++)
              {
                DEBUG((EFI_D_ERROR,"%c", ((CHAR8*)pTzLog + ((tzbsp_diag_16_t *) pTzLog)->ring_off)[i]));
              }
            }
          }
          else 
          {
            DEBUG((EFI_D_ERROR,"tz_diag_read_display_unencrpted_log(): TZ_VERSION_OLDER_THAN_920: Log size exceeds maximum size 0x%x \n", log_buf_size));
            break;
          }
        } 
        else if (TZ_VERSION_920_OR_NEWER == version_check) 
        {
          log_buf_size = ((tzbsp_diag_32_t *) pTzLog)->ring_len;
          log_start = (CHAR8*)pTzLog + ((tzbsp_diag_32_t *) pTzLog)->ring_off + latest_tz_log_pos.offset;
          if ((((tzbsp_diag_32_t *) pTzLog)->log).log_pos.wrap == latest_tz_log_pos.wrap) 
          {
            log_len_1 = (((tzbsp_diag_32_t *) pTzLog)->log).log_pos.offset - latest_tz_log_pos.offset;
            for (i = 0; i < log_len_1; i++)
            {
              DEBUG((EFI_D_ERROR,"%c", log_start[i]));
            }
          }
          else if ((((tzbsp_diag_32_t *) pTzLog)->log).log_pos.wrap == latest_tz_log_pos.wrap + 1 && \
                (((tzbsp_diag_32_t *) pTzLog)->log).log_pos.offset <= latest_tz_log_pos.offset) 
          {
            log_len_1 = log_buf_size - latest_tz_log_pos.offset;
            for (i = 0; i < log_len_1; i++)
            {
              DEBUG((EFI_D_ERROR,"%c", log_start[i]));
            }
        
            if ((((tzbsp_diag_32_t *) pTzLog)->log).log_pos.offset != 0) 
            {
              log_len_2 = (((tzbsp_diag_32_t *) pTzLog)->log).log_pos.offset;
              for (i = 0; i < log_len_2; i++)
              {
                DEBUG((EFI_D_ERROR,"%c", ((CHAR8*)pTzLog + ((tzbsp_diag_32_t *) pTzLog)->ring_off)[i]));
              }
            }
          }	
          else 
          {
            DEBUG((EFI_D_ERROR,"tz_diag_read_display_unencrpted_log(): TZ_VERSION_920_OR_NEWER: Log size exceeds maximum size 0x%x \n", log_buf_size));
            break;
          }
        }
        else 
        {
          DEBUG((EFI_D_ERROR,"tz_diag_read_display_unencrpted_log(): SMC call to obtain TZ version failed. \n"));
          break;
        }
    } while(0);

    DEBUG((EFI_D_ERROR,"------------- TZ DIAG LOG END -------------\n\n"));  

    return;
}

/**
  This function is used to check whether the logs are encrypted or not. 

  @param[out] pIsDiagEncrypted    To get the encryption status information.

  @retval EFI_SUCCESS  If no error.
  @retval Otherwise    Error specific to scenario.

 **/
static EFI_STATUS tz_diag_is_log_encrypted(BOOLEAN *pIsDiagEncrypted)
{
    QCOM_SCM_PROTOCOL *pScmProtocol = 0;
    UINT64 param[SCM_MAX_NUM_PARAMETERS] = {0};
    UINT64 results[SCM_MAX_NUM_RESULTS] = {0};
    EFI_STATUS status = EFI_FAILURE;
	
    do
    {
        if (pIsDiagEncrypted == NULL)
        {
            status = EFI_INVALID_PARAMETER;
            break;
        }
        *pIsDiagEncrypted = FALSE;

        // If encryption feature is not supported, just return saying that the encryption is not enabled. 
        if (!bIsTzDiagEncFeatSupported)
       	{
            status = EFI_SUCCESS;
        }

        pScmProtocol = tz_diag_get_qcom_protocol();
        if (pScmProtocol == NULL)
        {
            break;
        }

        status = pScmProtocol->ScmSipSysCall(pScmProtocol, 
                                             TZ_OS_LOG_ENCR_ALLOWED_ID, 
                                             TZ_OS_LOG_ENCR_ALLOWED_ID_PARAM_ID, 
                                             param, 
                                             results);
        if (EFI_ERROR(status))
        {
            DEBUG((EFI_D_ERROR,"tz_diag_is_log_encrypted(): System call failed. Error: 0x%x \n", status));
            break;
        }

        *pIsDiagEncrypted = (results[1] == 1) ? TRUE : FALSE;

    } while (0);

    return status;
}

/**
  This function must be called only when the log encryption is enabled. 
  If called otherwise, the system may crash.

  @param[in] LogId    Type of logs to extract in an encrypted format.
                      Only TZ Diag logs are supported with id, ENCRYPTED_TZ_LOG_ID.

  @retval VOID

 **/
static void tz_diag_read_display_encrpted_log(UINT32 LogId)
{
    struct tzbsp_encr_log_t *encr_log_head;
    UINT32 log_buf_size = LOG_BUF_SIZE;
    UINT8 *log_buf = NULL;
    EFI_STATUS status = EFI_FAILURE;

    QCOM_SCM_PROTOCOL *pScmProtocol = 0;
    UINT64 param[SCM_MAX_NUM_PARAMETERS] = {0};
    UINT64 results[SCM_MAX_NUM_RESULTS] = {0};
	UINT32 i = 0;

    DEBUG((EFI_D_ERROR,"\n-------- ENCRYPTED TZ DIAG LOG START --------\n"));

    do
    {
        /* Allocate memory for the encrypted log buffer. This should be the size of TZ diag buffer */
        log_buf = (UINT8 *)UncachedAllocatePool(log_buf_size);
        if (log_buf == NULL)
        {
            DEBUG((EFI_D_ERROR,"tz_diag_read_display_encrpted_log(): Buffer allocation failed. \n"));
            break;
        }

        memset(log_buf, 0, log_buf_size);

        pScmProtocol = tz_diag_get_qcom_protocol();
        if (pScmProtocol == NULL)
        {
            break;
        }

        param[0] = (UINT32)(uintptr_t) log_buf;
        param[1] = (UINT32) log_buf_size;
        param[2] = (UINT32) LogId;
        status = pScmProtocol->ScmSipSysCall(pScmProtocol, 
                                             TZ_OS_REQUEST_ENCR_LOG_BUFFER_ID, 
                                             TZ_OS_REQUEST_ENCR_LOG_BUFFER_ID_PARAM_ID, 
                                             param, 
                                             results);
        if (EFI_ERROR(status))
        {
            DEBUG((EFI_D_ERROR,"tz_diag_read_display_encrpted_log(): System call failed. Error: 0x%x \n", status));
            break;
        }

        encr_log_head = (struct tzbsp_encr_log_t *)(log_buf);

        // Magic_Num.
        // Version.
        // Encr_Log_Buff_Size.
        // Wrap_Count.
        DEBUG((EFI_D_ERROR,
 	    		"\nMagic_Num :\n0x%x\n"
 	    		"\nVersion :\n%d\n"
 	    		"\nEncr_Log_Buff_Size :\n%d\n"
 	    		"\nWrap_Count :\n%d\n",
 	    		encr_log_head->magic_num,
 	    		encr_log_head->version,
 	    		encr_log_head->encr_log_buff_size,
 	    		encr_log_head->wrap_count));

        // Key
        DEBUG((EFI_D_ERROR,"\nKey : \n"));
        UINT8 *key = (UINT8 *)encr_log_head->key;
        for (i = 0; i < TZBSP_AES_256_ENCRYPTED_KEY_SIZE; i++) 
        {
            DEBUG((EFI_D_ERROR,"%02x ", *key++));
            if ((i + 1) % 32 == 0)
            {
                DEBUG((EFI_D_ERROR,"\n"));
            }
        }
        DEBUG((EFI_D_ERROR,"\n"));

        // Nonce.
        DEBUG((EFI_D_ERROR,"\nNonce : \n"));
        UINT8 *nonce = (UINT8 *)encr_log_head->nonce;
        for (i = 0; i < TZBSP_NONCE_LEN; i++) 
        {
            DEBUG((EFI_D_ERROR,"%02x ", *nonce++));
        }
        DEBUG((EFI_D_ERROR,"\n"));

        // Tag.
        DEBUG((EFI_D_ERROR,"\nTag : \n"));
        UINT8 *tag = (UINT8 *)encr_log_head->tag;
        for (i = 0; i < TZBSP_TAG_LEN; i++) 
        {
            DEBUG((EFI_D_ERROR,"%02x ", *tag++));
        }
        DEBUG((EFI_D_ERROR,"\n"));

        // Log.
        DEBUG((EFI_D_ERROR,"\nLog : \n"));
        UINT8 *log_buf = (UINT8 *)encr_log_head->log_buf;
        for (i = 0; i < encr_log_head->encr_log_buff_size; i++) 
        {
            DEBUG((EFI_D_ERROR,"%02x ", *log_buf++));
            if ((i + 1) % 32 == 0)
            {
                DEBUG((EFI_D_ERROR,"\n"));
            }
        }
        DEBUG((EFI_D_ERROR,"\n"));
    } while (0);		

    DEBUG((EFI_D_ERROR,"\n-------- ENCRYPTED TZ DIAG LOG END --------\n"));

    if (log_buf != NULL)
    {
        UncachedFreePool(log_buf);
    }

    return;
}

/*=============================================================================
                      EXTERNAL FUNCTION DEFINITIONS
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
void tz_diag_log(uint8 LogId)
{
    EFI_STATUS status = EFI_FAILURE;
    BOOLEAN is_encrypted = FALSE;
    BOOLEAN is_secure = FALSE;
    BOOLEAN is_log_available = FALSE;
	sec_dbg debug_policy = {0};

    status = tz_diag_initialization();
    if (EFI_ERROR(status))
    {
        return;
    }

    do
    {
        /* 
           When TZ_OS_LOG_ENCR_ALLOWED_ID syscall returns FALSE, it doesnt mean that the device is non-secure.
           This status is also possible when the debug policy is enabled. 
           So, get the device state first and then choose the mode to extract TZ diag logs. 
        */
        status = tz_diag_is_secure_device(&is_secure);

        if (EFI_ERROR(status))
        {
            break;
        }

        /* 
           On a secure device if any information is not appropriate, checks are added in such a way that the process terminates.  
           This is to avoid any violations which may cause due to improper information. 
        */
        if (is_secure)
        {
            /* 
               This is the first option to choose, if the device is secure. Check whether the logs are encrypted or not.
               If the logs are encrypted, extract encrypted logs and print. 
            */
            status = tz_diag_is_log_encrypted(&is_encrypted);
            if (EFI_ERROR(status))
            {
                break;
            }

            if (is_encrypted)
            {
                tz_diag_read_display_encrpted_log(ENCRYPTED_TZ_LOG_ID);
                break;
            }
            else
            {
                /* 
                   If the logs not encrypted on a secure device, extract debug policy flags and check whether the logs are enabled or not. 
                   Plain TZ Diag is available on a Secure device, when APDP is used with TZ logs enable flag or Offline Dumps flag.
                */
                status = tz_diag_get_debug_policy(&debug_policy, sizeof(sec_dbg));
                if (status == EFI_SUCCESS)
                {
                    if (debug_policy.flags.enable_logs == 1 || debug_policy.flags.enable_offline_crash_dumps == 1)
                    {
                        /* 
                           If logs are enabled in debug policy, extract unencrypted logs directly from IMEM in the later stage. 
                           Otherwise, logs are not at all available in any case. 
                        */
                        is_log_available = TRUE;
                    }
                }
            }
        }
        else
        {
            /*
               The device is non-secure, extract unencrypted logs directly from IMEM.
            */
            is_log_available = TRUE;
        }
		
        if (is_log_available)
        {
            tz_diag_read_display_unencrpted_log();
        }
    } while(0);

    return;
}
