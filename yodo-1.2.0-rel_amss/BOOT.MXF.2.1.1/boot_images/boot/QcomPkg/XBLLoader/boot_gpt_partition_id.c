/**
 * @file boot_gpt_partition_id.c
 * @brief
 * Source file contains the GUID for sbl2,sbl3,tz,rpm and appsbl
 *
 */

/*==========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ---------------------------------------------------------
04/04/22   rhy     Added GUID for IPA_FW
01/05/22   ck      Added GUID for DMA_GSIFW partition
05/24/21   rama    xbl_sc_logs_partition_id
12/11/20   ds      aop_config image loading changes
12/01/20   ds      xbl_sc_test_mode_partition_id
01/18/18   vk      Add FlexSku guid
06/22/17   ds      coldplug changes
05/30/17   vk      Add MISC image GUIDs
10/14/16   kpa     Added GUID for XBLConfig image partition
07/19/16   kpa     Added GUID for SHRM and AOP image partitions
10/15/15   wg      Added GUID for ABL.fv and ABL.fv backup partitions
09/15/15   as      Added GUID for Boot Shared Variables
07/10/15   kpa     Added GUID for sti_partition_id
06/05/15   as      Added GUID for BERT partition
05/19/15   as      Added GUID for Recovery RPM partition
05/05/15   kpa     Added GUID for APDP partition
03/02/15   kpa     Added GUID for QSEE Dev config image partition.
01/23/15   ck      Corrected QSEE recovery partition GUID
10/30/14   ck      Added recovery partitions and GUID for ACPI partition
10/14/14   kpa     Added GUID for PMIC partition
03/21/14   ck      Added GUID for SEC partition
10/17/13   ck      Split TZ into QSEE and QHEE and created GUID's for them.
03/19/13   dh      Added GUID for ram dump parition
12/05/12   jz      Added GUID for CDT partition
07/20/12   dh      Add GUID for ddr training parameter partition
03/22/12   dh      Add GUID for wdog debug image
04/05/11   plc     Add GUID info for SBL1
03/24/11   dh      Initial creation

============================================================================
Copyright 2011-2018,2020-2022 by Qualcomm Technologies Incorporated.  All Rights Reserved.
                            All Rights Reserved.
                    Qualcomm Confidential and Proprietary
===========================================================================*/

/*==========================================================================
                             INCLUDE FILES
===========================================================================*/
#include "boot_comdef.h"
#include "coldplug_api.h"

/*define GUID for SBL1*/
/*This is the GUID that PBL expects to identify and load the first SBL*/
struct coldplug_guid sbl1_partition_id =
      /*{DEA0BA2C-CBDD-4805-B4F9-F428251C3E98}*/
      { 0xDEA0BA2C, 0xCBDD, 0x4805, { 0xB4, 0xF9, 0xF4, 0x28, 0x25, 0x1C, 0x3E, 0x98 } };

/*define GUID for SBL2*/
struct coldplug_guid sbl2_partition_id =
      /*{8C6B52AD-8A9E-4398-AD09-AE916E53AE2D}*/
      { 0x8C6B52AD, 0x8A9E, 0x4398, { 0xAD, 0x09, 0xAE, 0x91, 0x6E, 0x53, 0xAE, 0x2D } };

/*define GUID for SBL3*/
struct coldplug_guid sbl3_partition_id =
      /*{05E044DF-92F1-4325-B69E-374A82E97D6E}*/
      { 0x05E044DF, 0x92F1, 0x4325, { 0xB6, 0x9E, 0x37, 0x4A, 0x82, 0xE9, 0x7D, 0x6E } };

/*define GUID for APPSBL*/
struct coldplug_guid appsbl_partition_id =
      /*{400FFDCD-22E0-47E7-9A23-F16ED9382388}*/
      { 0x400FFDCD, 0x22E0, 0x47E7, { 0x9A, 0x23, 0xF1, 0x6E, 0xD9, 0x38, 0x23, 0x88 } };

/*define GUID for QSEE*/
struct coldplug_guid qsee_partition_id =
      /*{A053AA7F-40B8-4B1C-BA08-2F68AC71A4F4}*/
      { 0xA053AA7F, 0x40B8, 0x4B1C, { 0xBA, 0x08, 0x2F, 0x68, 0xAC, 0x71, 0xA4, 0xF4 } };

/*define GUID for QHEE*/
struct coldplug_guid qhee_partition_id =
      /*{E1A6A689-0C8D-4CC6-B4E8-55A4320FBD8A}*/
      { 0xE1A6A689, 0x0C8D, 0x4CC6, { 0xB4, 0xE8, 0x55, 0xA4, 0x32, 0x0F, 0xBD, 0x8A } };

/*define GUID for RPM*/
struct coldplug_guid rpm_partition_id =
      /*{098DF793-D712-413D-9D4E-89D711772228}*/
      { 0x098DF793, 0xD712, 0x413D, { 0x9D, 0x4E, 0x89, 0xD7, 0x11, 0x77, 0x22, 0x28 } };

/*define GUID for wdog debug image*/
struct coldplug_guid wdt_partition_id =
      /*{D4E0D938-B7FA-48C1-9D21-BC5ED5C4B203}*/
      { 0xD4E0D938, 0xB7FA, 0x48C1, { 0x9D, 0x21, 0xBC, 0x5E, 0xD5, 0xC4, 0xB2, 0x03 } };

/*define GUID for DDR params partiton*/
struct coldplug_guid ddr_params_partition_id =
      /*{20A0C19C-286A-42FA-9CE7-F64C3226A794}*/
      { 0x20A0C19C, 0x286A, 0x42FA, { 0x9C, 0xE7, 0xF6, 0x4C, 0x32, 0x26, 0xA7, 0x94 } };

/*define GUID for CDT partition*/
struct coldplug_guid cdt_partition_id =
      /*{a19f205f-ccd8-4b6d-8f1e-2d9bc24cffb1}*/
      { 0xA19F205F, 0xCCD8, 0x4B6D, { 0x8F, 0x1E, 0x2D, 0x9B, 0xC2, 0x4C, 0xFF, 0xB1 } };

/*define GUID for Ram Dump partition*/
struct coldplug_guid raw_dump_partition_id =
      /*{66C9B323-F7FC-48B6-BF96-6F32E335A428}*/
      { 0x66C9B323, 0xF7FC, 0x48B6, { 0xBF, 0x96, 0x6F, 0x32, 0xE3, 0x35, 0xA4, 0x28 } };

/*define GUID for Ram Dump partition*/
struct coldplug_guid xbl_ramdump_partition_id =
      /*{0382F197-E41F-4E84-B18B-0B564AEAD875}*/
      { 0x0382F197, 0xE41F, 0x4E84, { 0xB1, 0x8B, 0x0B, 0x56, 0x4A, 0xEA, 0xD8, 0x75 } };

/*define GUID for SECDATA partition*/
struct coldplug_guid secdata_partition_id =
      /*{76CFC7EF-039D-4E2C-B81E-4DD8C2CB2A93}*/
      { 0x76CFC7EF, 0x039D, 0x4E2C, { 0xB8, 0x1E, 0x4D, 0xD8, 0xC2, 0xCB, 0x2A, 0x93 } };

/*define GUID for PMIC config data partition*/
struct coldplug_guid pmic_partition_id =
      /*{C00EEF24-7709-43D6-9799-DD2B411E7A3C}*/
      { 0xC00EEF24, 0x7709, 0x43D6, { 0x97, 0x99, 0xDD, 0x2B, 0x41, 0x1E, 0x7A, 0x3C } };

/*define GUID for TZ enumeration image partition*/
struct coldplug_guid qsee_devcfg_image_partition_id =
      /*{F65D4B16-343D-4E25-AAFC-BE99B6556A6D}*/
      { 0xF65D4B16, 0x343D, 0x4E25, { 0xAA, 0xFC, 0xBE, 0x99, 0xB6, 0x55, 0x6A, 0x6D } };

/*define GUID for APDP config data partition*/
struct coldplug_guid apdp_partition_id =
      /*{E6E98DA2-E22A-4D12-AB33-169E7DEAA507}*/
      { 0xE6E98DA2, 0xE22A, 0x4D12, { 0xAB, 0x33, 0x16, 0x9E, 0x7D, 0xEA, 0xA5, 0x07 } };

/*define GUID for ACPI table partition*/
struct coldplug_guid acpi_partition_id =
      /*{2A21D307-A03B-484C-A151-09A0D97716A8}*/
      { 0x2A21D307, 0xA03B, 0x484C, { 0xA1, 0x51, 0x09, 0xA0, 0xD9, 0x77, 0x16, 0xA8 } };

/*define GUID for BERT partition*/
struct coldplug_guid bert_partition_id =
      /*{0E444367-F7DB-46B5-9BE7-403996654F5C}*/
      { 0x0E444367, 0xF7DB, 0x46B5, { 0x9B, 0xE7, 0x40, 0x39, 0x96, 0x65, 0x4F, 0x5C } };

/*define GUID for STI image partition*/
struct coldplug_guid sti_partition_id =
      /*{AA9A5C4C-4F1F-7D3A-014A-22BD33BF7191}*/
      { 0xAA9A5C4C, 0x4F1F, 0x7D3A, { 0x01, 0x4A, 0x22, 0xBD, 0x33, 0xBF, 0x71, 0x91 } };

/*define GUID for boot shared variables partition*/
struct coldplug_guid boot_shared_variables_partition_id =
      /*{3E8954C9-F738-4ED6-8AD1-229E60E9B6C8}*/
      { 0x3E8954C9, 0xF738, 0x4ED6, { 0x8A, 0xD1, 0x22, 0x9E, 0x60, 0xE9, 0xB6, 0xC8 } };

/*define GUID for ABL image partition*/
struct coldplug_guid abl_partition_id =
      /*{BD6928A1-4CE0-A038-4F3A-1495E3EDDFFB}*/
      { 0xBD6928A1, 0x4CE0, 0xA038, { 0x4F, 0x3A, 0x14, 0x95, 0xE3, 0xED, 0xDF, 0xFB } };

/*define GUID for SHRM image partition*/
struct coldplug_guid shrm_partition_id =
      /*{CB74CA22-2F0D-4B82-A1D6-C4213F348D73}*/
      { 0xCB74CA22, 0x2F0D, 0x4B82, { 0xA1, 0xD6, 0xC4, 0x21, 0x3F, 0x34, 0x8D, 0x73 } };

/*define GUID for AOP image partition*/
struct coldplug_guid aop_partition_id =
      /*{D69E90A5-4CAB-0071-F6DF-AB977F141A7F}*/
      { 0xD69E90A5, 0x4CAB, 0x0071, { 0xF6, 0xDF, 0xAB, 0x97, 0x7F, 0x14, 0x1A, 0x7F } };

/*define GUID for AOP Config image partition*/
struct coldplug_guid aop_config_partition_id =
      /*{3D12F234-C882-4B46-A20C-17D52C8FC03D}*/
      { 0x3D12F234, 0xC882, 0x4B46, { 0xA2, 0x0C, 0x17, 0xD5, 0x2C, 0x8F, 0xC0, 0x3D } };

/*define GUID for XBLConfig image partition*/
struct coldplug_guid XBLConfig_partition_id =
      /*{5A325AE4-4276-B66D-0ADD-3494DF27706A}*/
      { 0x5A325AE4, 0x4276, 0xB66D, { 0x0A, 0xDD, 0x34, 0x94, 0xDF, 0x27, 0x70, 0x6A } };

/*define GUID for multi image (MISC OEM) partition*/
struct coldplug_guid multi_image_partition_id =
      /*{E126A436-757E-42D0-8D19-0F362F7A62B8}*/
      { 0xE126A436, 0x757E, 0x42D0, { 0x8D, 0x19, 0x0F, 0x36, 0x2F, 0x7A, 0x62, 0xB8 } };

/*define GUID for multi image (MISC QTI) partition*/
struct coldplug_guid multi_image_qti_partition_id =
      /*{846C6F05-EB46-4C0A-A1A3-3648EF3F9D0E}*/
      { 0x846C6F05, 0xEB46, 0x4C0A, { 0xA1, 0xA3, 0x36, 0x48, 0xEF, 0x3F, 0x9D, 0x0E } };

/*define GUID for logfs image partition*/
struct coldplug_guid logfs_partition_id =
      /*{BC0330EB-3410-4951-A617-03898DBE3372}*/
      { 0xBC0330EB, 0x3410, 0x4951, { 0xA6, 0x17, 0x03, 0x89, 0x8D, 0xBE, 0x33, 0x72 } };

/*define GUID for CPUCPFW image partition*/
struct coldplug_guid cpucpfw_partition_id =
      /*{1E8615BD-6D8C-41AD-B3EA-50E8BF40E43F}*/
      { 0x1E8615BD, 0x6D8C, 0x41AD, { 0xB3, 0xEA, 0x50, 0xE8, 0xBF, 0x40, 0xE4, 0x3F } };

/*define GUID for CPUCP_DTB image partition*/
struct coldplug_guid cpucp_dtb_partition_id =
      /*{7426906A-89DB-4F46-BA5A-222ED0D3069B}*/
      { 0x7426906A, 0x89DB, 0x4F46, { 0xBA, 0x5A, 0x22, 0x2E, 0xD0, 0xD3, 0x06, 0x9B } };

/*define GUID for SMSS image partition*/
struct coldplug_guid smss_image_partition_id =
      /*{DF2E6DD2-296D-4CAA-867B-2E92E2F9B6C3}*/
      { 0xDF2E6DD2, 0x296D, 0x4CAA, { 0x86, 0x7B, 0x2E, 0x92, 0xE2, 0xF9, 0xB6, 0xC3 } };

/*define GUID for XBL_SC_TEST_MODE partition*/
struct coldplug_guid xbl_sc_test_mode_partition_id =
      /*{91FDD2B9-8ED3-4176-BC42-260F2E34D04A}*/
      { 0x91FDD2B9, 0x8ED3, 0x4176, { 0xBC, 0x42, 0x26, 0x0F, 0x2E, 0x34, 0xD0, 0x4A } };

struct coldplug_guid xbl_sc_logs_partition_id =
      /*{F7EECB66-781A-439A-8955-70E12ED4A7A0}*/
      { 0xF7EECB66, 0x781A, 0x439A, { 0x89, 0x55, 0x70, 0xE1, 0x2E, 0xD4, 0xA7, 0xA0 } };

/*define GUID for DMA_GSIFW image partition*/
struct coldplug_guid dma_gsifw_partition_id =
      /*{F3678373-234F-4C02-9DE5-158A6F4BAB94}*/
      { 0xF3678373, 0x234F, 0x4C02, { 0x9D, 0xE5, 0x15, 0x8A, 0x6F, 0x4B, 0xAB, 0x94 } };

/*define GUID for DDR TEST partition*/
struct coldplug_guid ddr_test_partition_id =
      /*{2D58205E-BA35-4BF9-B6C1-C6FDC80A373B}*/
      { 0x2D58205E, 0xBA35, 0x4BF9, { 0xB6, 0xC1, 0xC6, 0xFD, 0xC8, 0x0A, 0x37, 0x3B } };

/*define GUID for IPA_FW image partition*/
struct coldplug_guid ipa_fw_partition_id =
      /*{DA6CC9A3-5A29-4DC6-A0C2-273B5D665D29}*/
      { 0xDA6CC9A3, 0x5A29, 0x4DC6, { 0xA0, 0xC2, 0x27, 0x3B, 0x5D, 0x66, 0x5D, 0x29 } };

/* Recovery Partitions */
/* define GUID for SBL1 RECOVERY */
struct coldplug_guid sbl1_recovery_partition_id =
  /*{7A3DF1A3-A31A-454D-BD78-DF259ED486BE}*/
  { 0x7A3DF1A3, 0xA31A, 0x454D, { 0xBD, 0x78, 0xDF, 0x25, 0x9E, 0xD4, 0x86, 0xBE } };

/* define GUID for QSEE RECOVERY */
struct coldplug_guid qsee_recovery_partition_id =
  /*{C832EA16-8B0D-4398-A67B-EBB30EF98E7E}*/
  { 0xC832EA16, 0x8B0D, 0x4398, { 0xA6, 0x7B, 0xEB, 0xB3, 0x0E, 0xF9, 0x8E, 0x7E } };

/* define GUID for APPSBL RECOVERY */
struct coldplug_guid appsbl_recovery_partition_id =
  /*{9F234B5B-0EFB-4313-8E4C-0AF1F605536B}*/
  { 0x9F234B5B, 0x0EFB, 0x4313, { 0x8E, 0x4C, 0x0A, 0xF1, 0xF6, 0x05, 0x53, 0x6B } };

/*define GUID for PMIC config data RECOVERY partition*/
struct coldplug_guid pmic_recovery_partition_id =
      /*{D9BD7CD9-B1BA-4F3B-A6CE-0E348A1116E9}*/
      { 0xD9BD7CD9, 0xB1BA, 0x4F3B, { 0xA6, 0xCE, 0x0E, 0x34, 0x8A, 0x11, 0x16, 0xE9 } };

/*define GUID for RPM RECOVERY partition*/
struct coldplug_guid rpm_recovery_partition_id =
      /*{B7804414-8E65-4A1D-93FD-9D9BF5621306}*/
      { 0xB7804414, 0x8E65, 0x4A1D, { 0x93, 0xFD, 0x9D, 0x9B, 0xF5, 0x62, 0x13, 0x06 } };

/*define GUID for ABL RECOVERY partition*/
struct coldplug_guid abl_recovery_partition_id =
      /*{DC6278E6-0799-4616-BD72-28D60D15921C}*/
      { 0xDC6278E6, 0x0799, 0x4616, { 0xBD, 0x72, 0x28, 0xD6, 0x0D, 0x15, 0x92, 0x1C } };

/*define GUID for SHRM image RECOVERY partition*/
struct coldplug_guid shrm_recovery_partition_id =
      /*{39FD6C00-49EB-6BD1-6899-2FB849DD4F75}*/
      { 0x39FD6C00, 0x49EB, 0x6BD1, { 0x68, 0x99, 0x2F, 0xB8, 0x49, 0xDD, 0x4F, 0x75 } };

/*define GUID for AOP image RECOVERY partition*/
struct coldplug_guid aop_recovery_partition_id =
      /*{B8B27C4C-4B5B-8AB2-502F-A792B590A896}*/
      { 0xB8B27C4C, 0x4B5B, 0x8AB2, { 0x50, 0x2F, 0xA7, 0x92, 0xB5, 0x90, 0xA8, 0x96 } };

/*define GUID for AOP image RECOVERY partition*/
struct coldplug_guid aop_config_recovery_partition_id =
      /*{77036CD4-03D5-42BB-8ED1-37E5A88BAA34}*/
      { 0x77036CD4, 0x03D5, 0x42BB, { 0x8E, 0xD1, 0x37, 0xE5, 0xA8, 0x8B, 0xAA, 0x34 } };

/*define GUID for CPUCPFW image RECOVERY partition*/
struct coldplug_guid cpucpfw_recovery_partition_id =
      /*{6C1111FB-5354-41DE-AC17-5B6E542BE836}*/
      { 0x6C1111FB, 0x5354, 0x41DE, { 0xAC, 0x17, 0x5B, 0x6E, 0x54, 0x2B, 0xE8, 0x36 } };

/*define GUID for CPUCP DTB RECOVERY partition*/
struct coldplug_guid cpucp_dtb_recovery_partition_id =
      /*{7426906A-89DB-4F46-BA5A-222ED0D3069B}*/
      { 0x7426906A, 0x89DB, 0x4F46, { 0xBA, 0x5A, 0x22, 0x2E, 0xD0, 0xD3, 0x06, 0x9B } };
      

/*define GUID for XBLConfig image RECOVERY partition*/
struct coldplug_guid XBLConfig_recovery_partition_id =
      /*{F462E0EA-A20E-4B10-867A-2D4455366548}*/
      { 0xF462E0EA, 0xA20E, 0x4B10, { 0x86, 0x7A, 0x2D, 0x44, 0x55, 0x36, 0x65, 0x48 } };

/*define GUID for CDT RECOVERY partition*/
struct coldplug_guid cdt_recovery_partition_id =
      /*{9BE6FA9C-C5A7-4BAA-9740-8D93C5084BD9}*/
      { 0x9BE6FA9C, 0xC5A7, 0x4BAA, { 0x97, 0x40, 0x8D, 0x93, 0xC5, 0x08, 0x4B, 0xD9 } };

/*define GUID for DDR params RECOVERY partiton*/
struct coldplug_guid ddr_params_recovery_partition_id =
      /*{78A54EF3-D7D7-4518-91D5-1E972C82B282}*/
      { 0x78A54EF3, 0xD7D7, 0x4518, { 0x91, 0xD5, 0x1E, 0x97, 0x2C, 0x82, 0xB2, 0x82 } };

/*define GUID for APDP config data RECOVERY partition*/
struct coldplug_guid apdp_recovery_partition_id =
      /*{110F198D-8174-4193-9AF1-5DA94CDC59C9}*/
      { 0x110F198D, 0x8174, 0x4193, { 0x9A, 0xF1, 0x5D, 0xA9, 0x4C, 0xDC, 0x59, 0xC9 } };

/*define GUID for Ram Dump RECOVERY partition*/
struct coldplug_guid ram_dump_recovery_partition_id =
      /*{91B713F3-0F22-4916-9660-B96EF7164757}*/
      { 0x91B713F3, 0x0F22, 0x4916, { 0x96, 0x60, 0xB9, 0x6E, 0xF7, 0x16, 0x47, 0x57 } };

/*define GUID for multi image (MISC OEM) RECOVERY partition*/
struct coldplug_guid multi_image_recovery_partition_id =
      /*{3E3E3ECD-C512-4F95-9144-6063826A8970}*/
      { 0x3E3E3ECD, 0xC512, 0x4F95, { 0x91, 0x44, 0x60, 0x63, 0x82, 0x6A, 0x89, 0x70 } };

/*define GUID for multi image (MISC QTI) RECOVERY partition*/
struct coldplug_guid multi_image_qti_recovery_partition_id =
      /*{D30C8B21-DDD9-45B6-8DE0-3165D34395C9}*/
      { 0xD30C8B21, 0xDDD9, 0x45B6, { 0x8D, 0xE0, 0x31, 0x65, 0xD3, 0x43, 0x95, 0xC9 } };

/*define GUID for QSEE DEVCFG image RECOVERY partition*/
struct coldplug_guid qsee_devcfg_image_recovery_partition_id =
      /*{169534E7-7809-4240-9763-0BA5DC37B5FF}*/
      { 0x169534E7, 0x7809, 0x4240, { 0x97, 0x63, 0x0B, 0xA5, 0xDC, 0x37, 0xB5, 0xFF } };

/*define GUID for SEC RECOVERY partition*/
struct coldplug_guid secdata_recovery_partition_id =
      /*{76CFC7EF-039D-4E2C-B81E-4DD8C2CB2A93}*/
      { 0x76CFC7EF, 0x039D, 0x4E2C, { 0xB8, 0x1E, 0x4D, 0xD8, 0xC2, 0xCB, 0x2A, 0x93 } };

/*define GUID for QHEE image RECOVERY partition*/
struct coldplug_guid qhee_image_recovery_partition_id =
      /*{CB45ECA0-504E-42BB-91BA-C9B3236F6A6E}*/
      { 0xCB45ECA0, 0x504E, 0x42BB, { 0x91, 0xBA, 0xC9, 0xB3, 0x23, 0x6F, 0x6A, 0x6E } };

/*define GUID for SMSS image RECOVERY partition*/
struct coldplug_guid smss_image_recovery_partition_id =
      /*{FDF56B51-D67E-4081-A4E2-975A0997200D}*/
      { 0xFDF56B51, 0xD67E, 0x4081, { 0xA4, 0xE2, 0x97, 0x5A, 0x09, 0x97, 0x20, 0x0D } };

/*define GUID for Ram Dump RECOVERY partition*/
struct coldplug_guid xbl_ramdump_recovery_partition_id =
      /*{FF608BF6-AEDF-4084-BEC5-C92AB4E4534D}*/
      { 0xFF608BF6, 0xAEDF, 0x4084, { 0xBE, 0xC5, 0xC9, 0x2A, 0xB4, 0xE4, 0x53, 0x4D } };

/*define GUID for DDR CAL RECOVERY partition*/
struct coldplug_guid ddr_cal_recovery_partition_id =
      /*{CB198EDD-9EBD-48A1-9BB6-BB3194BF2E51}*/
      { 0xCB198EDD, 0x9EBD, 0x48A1, { 0x9B, 0xB6, 0xBB, 0x31, 0x94, 0xBF, 0x2E, 0x51 } };
