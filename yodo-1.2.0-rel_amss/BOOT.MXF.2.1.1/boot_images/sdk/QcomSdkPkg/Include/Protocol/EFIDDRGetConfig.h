/** 
  @file  EFIDDRGetConfig.h
  @brief DDRGetinfo EFI protocol interface.
*/
/*=============================================================================
  Copyright (c) 2017 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who       what, where, why
 --------   ---       -----------------------------------------------------------
 11/21/20   kns       Add shub freq functions to ddr info protocal
 12/18/18   dj        Add ddr info protocal
 05/01/17   daisond   Initial Revision
=============================================================================*/

#ifndef __EFIDDRGETINFO_H__
#define __EFIDDRGETINFO_H__
 

 
#include <DDRDetails.h>


/** @cond */
typedef struct _EFI_DDRGETINFO_PROTOCOL EFI_DDRGETINFO_PROTOCOL;
/** @endcond */


/** @ingroup efi_ddrgetinfo_protocol_data
  Protocol latest version. 
*/
#define EFI_DDRGETINFO_PROTOCOL_REVISION 0x0000000000070000

/** @ingroup efi_ddrgetinfo_protocol_data
 * Both the protocl version and the structure version should be same */
#if (EFI_DDRGETINFO_PROTOCOL_REVISION != DDR_DETAILS_STRUCT_VERSION)
ASSERT(FALSE);
#endif





/*  Protocol GUID definition */
/** @ingroup efi_ddrgetinfo_protocol_prot */
#define EFI_DDRGETINFO_PROTOCOL_GUID \
   { 0x1a7c0eb8, 0x5646, 0x45f7, { 0xab, 0x20, 0xea, 0xe5, 0xda, 0x46, 0x40, 0xa2 } }

  
/** @cond */
/**
  External reference to the DDRGetInfo Protocol GUID defined 
  in the .dec file. 
*/
extern EFI_GUID gEfiDDRGetInfoProtocolGuid;
/** @endcond */


/** @} */ /* end_addtogroup efi_ddrgetinfo_data_types */

/*==============================================================================

                             API IMPLEMENTATION

==============================================================================*/ 


/* ============================================================================
**  Function : EFI_DDRGETINFO_GETDDRDETAILS
** ============================================================================
*/
/** @ingroup efi_ddrgetinfo_protocol_apis
  @par Summary
  Gets the DDR Details
    
  @param[in]   This            Pointer to the EFI_DDRGETINFO_PROTOCOL instance.
  @param[out]  DetailsEntry    Pointer to DDR Details  
                        
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef 
EFI_STATUS
(EFIAPI *EFI_DDRGETINFO_GETDDRDETAILS)(
   IN EFI_DDRGETINFO_PROTOCOL *This,
   OUT struct ddr_details_entry_info   *DetailsEntry
   );

   
/* ============================================================================
**  Function : EFI_DDRGetInfo_GetDDRFreqTable
** ============================================================================
*/
/** @ingroup efi_ddrgetinfo_protocol_apis
  @par Summary
  Gets the DDR Clock plan table
    
  @param[in]   This            Pointer to the EFI_DDRGETINFO_PROTOCOL instance.
  @param[out]  ClkPlanTable    Pointer to DDR clock plan Table  
                        
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef 
EFI_STATUS
(EFIAPI *EFI_DDRGETINFO_GETDDRFREQTABLE)(
   IN EFI_DDRGETINFO_PROTOCOL *This,
   OUT struct ddr_freq_plan_entry_info   *clk_plan_tbl
   );

   
/* ============================================================================
**  Function : EFI_DDRGetInfo_GetDDRFreq
** ============================================================================
*/
/** @ingroup efi_ddrgetinfo_protocol_apis
  @par Summary
  Gets the Current DDR Freq
    
  @param[in]   This                Pointer to the EFI_DDRGETINFO_PROTOCOL instance.
  @param[out]  ddr_freq            Pointer to Current DDR clock frequency  
                        
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef 
EFI_STATUS
(EFIAPI *EFI_DDRGETINFO_GETDDRFREQ)(
   IN EFI_DDRGETINFO_PROTOCOL *This,
   OUT UINT32                 *ddr_freq
   );

   
/* ============================================================================
**  Function : EFI_DDRGetInfo_GetDDRMaxEnabledFreq
** ============================================================================
*/
/** @ingroup efi_ddrgetinfo_protocol_apis
  @par Summary
  Gets the DDR Max Enabled Freq
    
  @param[in]   This                Pointer to the EFI_DDRGETINFO_PROTOCOL instance.
  @param[out]  ddr_freq            Pointer to DDR Max Enabled frequency  
                        
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef 
EFI_STATUS
(EFIAPI *EFI_DDRGETINFO_GETDDRMAXENABLEDFREQ)(
   IN EFI_DDRGETINFO_PROTOCOL *This,
   OUT UINT32                 *ddr_freq
   );

   
/* ============================================================================
**  Function : EFI_DDRGetInfo_SetDDRFreq
** ============================================================================
*/
/** @ingroup efi_ddrgetinfo_protocol_apis
  @par Summary
  Gets the DDR Details
    
  @param[in]   This            Pointer to the EFI_DDRGETINFO_PROTOCOL instance.
  @param[in]   ddr_freq        DDR freq to be set in the system.
                        
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef 
EFI_STATUS
(EFIAPI *EFI_DDRGETINFO_SETDDRFREQ)(
   IN EFI_DDRGETINFO_PROTOCOL *This,
   IN UINT32                   ddr_freq
   );

/* ============================================================================
**  Function : EFI_DDRGETINFO_SETMAXNOMINALDDRFREQ
** ============================================================================
*/
/** @ingroup efi_ddrgetinfo_protocol_apis
  @par Summary
  Gets the DDR Details
    
  @param[in]   This            Pointer to the EFI_DDRGETINFO_PROTOCOL instance.
                        
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef 
EFI_STATUS
(EFIAPI *EFI_DDRGETINFO_SETMAXNOMINALDDRFREQ)(
   IN EFI_DDRGETINFO_PROTOCOL *This
   );

/* ============================================================================
**  Function : EFI_DDRGETINFO_SETLOWESTDDRFREQ
** ============================================================================
*/
/** @ingroup efi_ddrgetinfo_protocol_apis
  @par Summary
  Gets the DDR Details
    
  @param[in]   This            Pointer to the EFI_DDRGETINFO_PROTOCOL instance.
                        
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef 
EFI_STATUS
(EFIAPI *EFI_DDRGETINFO_SETLOWESTDDRFREQ)(
   IN EFI_DDRGETINFO_PROTOCOL *This
   );

/* ============================================================================
**  Function : EFI_DDRGETINFO_GETDDRREGIONSDATA
** ============================================================================
*/
/** @ingroup efi_ddrgetinfo_protocol_apis
  @par Summary
  Gets the DDR Details
    
  @param[in]   This            Pointer to the EFI_DDRGETINFO_PROTOCOL instance.
  @param[out]  DetailsEntry    Pointer to DDR Regions Data
                        
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef 
EFI_STATUS
(EFIAPI *EFI_DDRGETINFO_GETDDRMAPPEDREGIONS)(
   IN EFI_DDRGETINFO_PROTOCOL *This,
   OUT struct ddr_regions_data_info   *GetDDRMappedRegions
   );

/* ============================================================================
**  Function : EFI_DDRGetInfo_GetSHUBFreqTable
** ============================================================================
*/
/** @ingroup efi_ddrgetinfo_protocol_apis
  @par Summary
  Gets the SHUB Clock plan table
    
  @param[in]   This            Pointer to the EFI_DDRGETINFO_PROTOCOL instance.
  @param[out]  ClkPlanTable    Pointer to SHUB clock plan Table  
                        
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef 
EFI_STATUS
(EFIAPI *EFI_DDRGETINFO_GETSHUBFREQTABLE)(
   IN EFI_DDRGETINFO_PROTOCOL             *This,
   OUT struct shub_freq_plan_entry_info   *clk_plan_tbl
   );

/* ============================================================================
**  Function : EFI_DDRGetInfo_SetSHUBFreq
** ============================================================================
*/
/** @ingroup efi_ddrgetinfo_protocol_apis
  @par Summary
  Sets the SHUB clock frequency
    
  @param[in]   This         Pointer to the EFI_DDRGETINFO_PROTOCOL instance.
  @param[out]  shub_freq    SHUB freq to be set in the system. 
                        
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef 
EFI_STATUS
(EFIAPI *EFI_DDRGETINFO_SETSHUBFREQ)(
   IN EFI_DDRGETINFO_PROTOCOL    *This,
   IN UINT32                     shub_freq
   );

/* ============================================================================
**  Function : EFI_DDRGetInfo_GetSHUBFreq
** ============================================================================
*/
/** @ingroup efi_ddrgetinfo_protocol_apis
  @par Summary
  Gets the Current SHUB Freq
    
  @param[in]   This                Pointer to the EFI_DDRGETINFO_PROTOCOL instance.
  @param[out]  shub_freq           Pointer to Current SHUB clock frequency  
                        
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef 
EFI_STATUS
(EFIAPI *EFI_DDRGETINFO_GETSHUBFREQ)(
   IN EFI_DDRGETINFO_PROTOCOL   *This,
   OUT UINT32                   *shub_freq
   );
  
/* ============================================================================
**  Function : EFI_DDRGETINFO_GETDDRMISCINFO_SMEM_DATA
** ============================================================================
*/
/** @ingroup efi_ddrgetinfo_protocol_apis
  @par Summary
  Gets the loader to uefi smem data
    
  @param[in]   This                        Pointer to the EFI_DDRGETINFO_PROTOCOL instance.
  @param[out]  ddr_misc_data        Pointer to loader to uefi smem data
                        
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef 
EFI_STATUS
(EFIAPI *EFI_DDRGETINFO_GETDDRMISCINFO_SMEM_DATA)(
   IN EFI_DDRGETINFO_PROTOCOL   *This,
   OUT ddr_misc_info  *ddr_misc_data 
   );
/* ============================================================================
**  Function : EFI_DDRGetInfo_GetDDRSCTConfig
** ============================================================================
*/
/** @ingroup EFI_DDRGetInfo_GetDDRSCTConfig
  @par Summary
  Gets the DDR SCT Config Information
    
  @param[in]   This            Pointer to the EFI_DDRGETINFO_PROTOCOL instance.
  @param[out]  sct_config      Pointer to the SCT Configuration Information.
                        
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef 
EFI_STATUS
(EFIAPI *EFI_DDRGETINFO_GETDDRSCTCONFIG)(
   IN EFI_DDRGETINFO_PROTOCOL *This,
   OUT UINT8                  *sct_config
   );
   
/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup efi_ddrgetinfo_protocol_prot 
  @par Summary
  DDR Get Info Protocol interface.
*/

struct _EFI_DDRGETINFO_PROTOCOL {
   UINT64                                Revision;
   EFI_DDRGETINFO_GETDDRDETAILS          GetDDRDetails;
   EFI_DDRGETINFO_GETDDRFREQTABLE        GetDDRFreqTable;
   EFI_DDRGETINFO_GETDDRFREQ             GetDDRFreq;
   EFI_DDRGETINFO_SETDDRFREQ             SetDDRFreq;
   EFI_DDRGETINFO_GETDDRMAXENABLEDFREQ   GetDDRMaxEnabledFreq;
   EFI_DDRGETINFO_SETMAXNOMINALDDRFREQ   SetMaxNominalDDRFreq;       // Added in Version 4
   EFI_DDRGETINFO_SETLOWESTDDRFREQ       SetLowestDDRFreq;           // Added in Version 4
   EFI_DDRGETINFO_GETDDRMAPPEDREGIONS    GetDDRMappedRegions;        // Added in Version 5
   EFI_DDRGETINFO_GETSHUBFREQTABLE       GetSHUBFreqTable;           // Added in Version 6
   EFI_DDRGETINFO_SETSHUBFREQ            SetSHUBFreq;                // Added in Version 6
   EFI_DDRGETINFO_GETSHUBFREQ            GetSHUBFreq;                // Added in Version 6
   EFI_DDRGETINFO_GETDDRMISCINFO_SMEM_DATA  GetDDRmiscinfoSmemData;  // Added in Version 6
   EFI_DDRGETINFO_GETDDRSCTCONFIG        GetDDRSCTConfig;            // Added in Version 7   
}; 

#endif /* __EFIDDRGETINFO_H__ */

