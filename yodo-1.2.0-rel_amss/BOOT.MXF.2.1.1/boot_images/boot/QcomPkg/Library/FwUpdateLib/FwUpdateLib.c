/** @file FwUpdatePhaseLib.c

  Copyright (c) 2012-2018, 2022 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

**/
/*=============================================================================
                              EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.



 when           who         what, where, why
 --------       ---         --------------------------------------------------
 2021/06/30     dmohan      Changes to support A/B Recovery feature
 2021/06/21     sood        Fixed MISRA rules : Updated GetTestHookData(), 
                            StateFwEntryRollbackAllStart(),StateFwEntryPostRollbackStart(),
                            ResetHookEntryToDefault(), GetTestHookData() with void paramater.
 2020/02/24     kbarad      Added CheckIfStorageHasNewContent() to check which storage has new content inside capsule
 2019/03/21     vkasilya    Added FW_STATE_PREPARE_UPDATE to find FW Back up phase started
 2019/03/15     vkasilya    ResetHookEntryToDefault() declaration moved to header and 
                            calling from FmpDeviceLib.c
 2019/03/13     vkasilya    Passing the progress fun ptr as a parameter to RunFwUpdateMain
 2019/02/11     rajb        Added test hook support to reset the device at different phases
                            of capsule update and also to widen progress bar width
 2019/02/01     rajb        Changes to show progress within backup phase
 2019/02/06     rajb        Skipping delete of partition contents in delete phase
 2019/02/01     rajb        Added support for progress bar rendering, during capsule update
 2018/11/06     prema       KW fixes
 2018/08/31     prema       Changes for SysFwVersion Entry handling to update SysFwVersion and ESRT entry
 2018/07/11     rajb        Allocating and initializing GPT backup data, correcting
                            few comments
 2018/06/28     prema       Handle to update AttemptCount in corner cases.
 2018/06/28     prema       Change to support multiple DPP entries and skip duplicate 
                            backup and delete operations in backup and rollback phase.
                            Changes to return unsupported for FAT and SSD Update types 
                            and to remove functions related to FAT and SSD processing
 2018/05/21     gparam      Changes to move all file based state-machine data to NV +
                            Cleanup of unused functions after the file to NV migration
 2018/03/23     prema       Handled HANDLE_ERROR_LABEL with proper function
 2017/07/11     hhovale     Dealing error case in state machine.
 2017/05/08     gparam      Changes to centralize ESRT update to DPP to the end of
                            SetImage API + Minor tweaks to logging
 2017/04/22     gparam      New API to extract the metadata for use in very
                            early stage of udpate to retrieve the LastAttemptVersion
                            for logging early errors + Changes to centralize
                            the recording of update status in DPP for future use +
                            Added back the support to record QC specific failure
                            results in COMMIT flag file evenfor capsule update
 2017/04/18     gparam      Changed the update status from internal type to
                            standard ones defined in EDK headers + Removed
                            unused/redundant definitions/parameters +
                            Using FwUpdateCapsulePhaseMain in place of
                            FwQcFirmwareUpdatePhaseMain as the udpate code is
                            moved to this function
 2017/02/22     ssumit      Added payload buffer and size to support SetImage function
 2017/02/22     pkn         Added changes required to support new update type - FWCLASS_GUID
 2017/02/13     gpavithr    Changes to use ESRTDxe inplace of local functions
                            to directly create and/or operate on ESRT table
 2016/12/06     ssumit      Mounted EFI Partition with WD Partition label
                            to overcome earlier mount failures of EFI Partition for WD.
                            This is temporary fix and should be reverted
                            once we have FIX from UEFI team to mount EFI Partition.
 2016/08/29     ltg         Added UFS support
 2015/03/22     mic         Added Fwupdate support for MSM8994 LiQUID only
 2015/02/05     al          Changing TPL_NOTIFY to TPL_CALLBACK
 2014/12/08     mic         Removed FwGetOsType API
 2013/06/28     niting      Added WARN macro to prevent message in PRODMODE
 2013/01/26     mic         Added workaround for authentication protocol issue
 2012/11/30     mic         Added ESRT entry print
 2012/11/15     mic         Fixed a corner case issue on GPT table switching
 2012/10/10     jd          Handle GPT switch based on firmware entry list
 2012/10/05     mic         Added Data-Driven update support
 2012/08/10     mic         Changed debug message level for critical errors
 2012/08/03     mic         Added maximum update attempts support
 2012/07/26     mic         Added configuration table pointer check before capsule
                                     processing
 2012/07/17     mic         Added ToolSupportProtocol for OPM handshake and removed
                                     ToolSupportLib
 2012/07/13     mic         Added WinSecApp OPM handshake support
 2012/06/25     mic         Added support for OPM keys update
 2012/06/21     rs          Adding support for FPDT ACPI table
 2012/06/18     jd          rename OEM_UPDATE_EVENT_GUID
 2012/06/12     rs          Added support for BreakChangeNumber
 2012/06/05     rs          Added support for UXCapsule
 2012/06/04     rs          Replaced AsciiPrint with DEBUG macro
 2012/05/15     mic         Added robustness of the reset logic
 2012/05/07     rs          Added support for decryption of Boot Firmware
 2012/05/03     mic         Initial version

=============================================================================*/

#include <Uefi.h>
#include <Uefi/UefiBaseType.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BootConfig.h>
#include <Pi/PiPeiCis.h>
#include <Library/QcomLib.h>
#include <Library/QcomBaseLib.h>
#include <Include/Library/FwCommonLib.h>
#include <Include/Library/FwUpdateLib.h>
#include <Include/api/storage/ufs_api.h>
#include <Include/Protocol/EFICardInfo.h>
#include <Library/SecBootSigLib.h>
#include <Protocol/EFIDpp.h>
#include <IndustryStandard/Acpi50.h>
#include <IndustryStandard/Bmp.h>
#include <Protocol/EFIEncryption.h>
#include <Protocol/EFIToolSupport.h>
#include <Protocol/EFIChipInfo.h>
#include <Protocol/EFIPlatformInfo.h>
#include "FwCapsule.h"
#include "FwEsrt.h"
#include "FwPayloadEntry.h"
#include "FwResourceCheck.h"
#include "FwEntryIO_helpers.h"
#include <Protocol/FirmwareManagement.h>
#include <Protocol/EFIRecovery.h>

#define max(a,b) (((a) > (b)) ? (a) : (b))


// Note: The order of string in below array should match
// the order of phase in QCOM_TEST_HOOK_PHASE
const CHAR16 *SysFwUpdatePhaseNames[QCOM_TESTHOOK_MAX] = 
{
  L"Prepare Update Phase",
  L"Backup Phase",
  L"Update Phase",
  L"Sync Phase",
  L"Rollback Phase"
};

/*extern variable*/
extern QPAYLOAD_METADATA_HEADER_V3    PayLoadHeader;
extern BOOLEAN                        bDoubleUpdateNeeded;
extern EFI_GUID                       gEfiMemCardInfoProtocolGuid;

/*global variable*/
QCOM_FW_UPDATE_MODE                   FWupdateMode                  = QCOM_FW_UPDATE_MODE_NOUPDATE;
QCFW_UPDATE_FLAG_VALUE	              gQcResultFlag                 = QCFW_UPDATE_SUCCESS;

/* Reset will be triggered before processing the given fw entry count */
UINT8   ResetPhaseData[QCOM_TESTHOOK_MAX] = {0};


// Progress Update
EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS    mProgressFuncSysFmp = NULL;

/**
 *  Function will reset the respective test hook variable and
 *  reset the device. Input of CurrentPhaseResetEntry value shall 
 *  be with respective to CurrentPhase.
 *
 * @param[in] CurrentPhase                      Used to differentiate the phase.
 * @param[in] CurrentFwEntryCount               Current index value.
 * @param[in] TotalFwEntries                    Max Fw Entry value in Capsule payload
 */
VOID
ResetHookPhaseAndSystem (
   IN QCOM_TEST_HOOK_PHASE              CurrentPhase,
   IN UINTN                             CurrentFwEntryCount,
   IN UINTN                             TotalFwEntries
   );

/**
 *  Function is to get test hook variable details and fills in the
 *
 * @return EFI_STATUS
 */
EFI_STATUS
GetTestHookData(VOID
  );

/**
*  Function to set the LUN (LUN1 or LUN2) as bootable where the
*  update was applied. It will determine the current bootable LUN
*  (LUN1 or LUN2) and it will set bootable the other LUN
*
* @return EFI_STATUS
*/
EFI_STATUS
SetBootableLUNPostUpdate(VOID);

/**
  Callback function to report the process of the firmware updating.
  Wrap the caller's version in this so that progress from the device lib is 
  within the expected range. 

  Capsule process : PROGRESS_CAPSULE_PROCESS_START          to PROGRESS_CAPSULE_PROCESS_END %
  Capsule Backup  : PROGRESS_CAPSULE_BACKUP_START           to PROGRESS_CAPSULE_BACKUP_END %
  Capsule Update  : PROGRESS_CAPSULE_UPDATE_START           to PROGRESS_CAPSULE_UPDATE_END %
  Capsule Delete  : PROGRESS_CAPSULE_BACKUP_DELETE_START    to PROGRESS_CAPSULE_BACKUP_DELETE_END %
  Capsule Commit  : PROGRESS_CAPSULE_BACKUP_DELETE_END + 1  to PROGRESS_CAPSULE_COMPLETED %

  @param[in]  Completion    A value between 1 and 100 indicating the current completion
  progress of the firmware update. Completion progress is
  reported as from 1 to 100 percent. A value of 0 is used by
  the driver to indicate that progress reporting is not supported.

  @retval EFI_SUCCESS       SetImage() continues to do the callback if supported.
  @retval other             SetImage() discontinues the callback and completes
 the update and returns.
*/

EFI_STATUS
EFIAPI
SysFwUpdateProgress (
  IN  UINTN     Completion
  )
{
  EFI_STATUS Status = EFI_UNSUPPORTED;

  if (mProgressFuncSysFmp == NULL)
  {
    return Status;
  }

  DEBUG((EFI_D_WARN,"Rendering Progress: %d\n", Completion));

  Status = mProgressFuncSysFmp(Completion);

  if (Status == EFI_UNSUPPORTED)
  {
    mProgressFuncSysFmp = NULL;
  }
  
  return Status;
}

/**
  Function to calculate convert the progress within a phase (0-100) to the progress
  segment given for that particular phase. This function converts this value to the
  full payload update progress and call the progress bar rendering function

  @param[in]  Completion            A value between 1 and 100 indicating the 
                                    completion in current phase of the system
                                    firmware update.
  @param[in]  PhaseCompletionStart  Progress value corresponding to the start
                                    of the current phase.
  @param[in]  PhaseCompletionEnd    Progress value corresponding to the end
                                    of the current phase.

  @retval EFI_SUCCESS       SetImage() continues to do the callback if supported.
  @retval other             SetImage() discontinues the callback and completes
 the update and returns.
*/

EFI_STATUS
EFIAPI
SysFwUpdateIntraPhaseProgress (
  IN  UINTN     Completion,
  IN  UINTN     PhaseCompletionStart,
  IN  UINTN     PhaseCompletionEnd
  )
{
  UINTN      CompletionTemp = Completion;

  //convert update progress range to (0 to 100 %)
  CompletionTemp = ((Completion * (PhaseCompletionEnd-PhaseCompletionStart))/ 100) + PhaseCompletionStart;

  DEBUG((EFI_D_WARN,"Progress span of current phase: [%d, %d]. Progress value within this span in (0-100 scale): %d\n", PhaseCompletionStart, PhaseCompletionEnd, Completion));

  return SysFwUpdateProgress(CompletionTemp);
}

/**
 * Function to update/clear QC result flag
 * 
 * @param QcResultFlag  -update result
 *
 * return EFI_STATUS
 */
EFI_STATUS
RecordQCResult (
  IN QCFW_UPDATE_FLAG_VALUE QcResultFlag
  )
{
  EFI_STATUS                Status                  = EFI_SUCCESS;
  QCFW_UPDATE_FLAG_VALUE    UpdateCommitFlagValue   = QCFW_UPDATE_INIT;

  switch(FWupdateMode)
  {
    case QCOM_FW_UPDATE_MODE_QCFW:
    case QCOM_FW_UPDATE_MODE_CAPSULE:
    
      UpdateCommitFlagValue = QcResultFlag;
      
      Status = SetQCResultFlag(UpdateCommitFlagValue);
      HANDLE_ERROR_LABEL(Status,SetQCResultFlag,FwUpdateClearFlagOrCapsuleExit);

      break;

    case QCOM_FW_UPDATE_MODE_NOUPDATE:
      // TODO: Giri: Check if we should set result flag to QCFW_UPDATE_UNKNOWN so that last update's value does not get reflected when queried
    default:
      break;
  }

FwUpdateClearFlagOrCapsuleExit:

  FWupdateMode = QCOM_FW_UPDATE_MODE_NOUPDATE;
  return Status ;
}

/**
 *  Update Sys Fw Ver Partition Entry.
 *
 *  @param FwVersion                   - Fw Version
 *  @param LowestSupportedFwVersion    - Lowest Supported Version
 *  @param LastAttemptStatus           - Last Attempt Status
 *  @param QcResultValue               - QC error codes corresponding to udpate status.
 *
 *  @return EFI_STATUS
 */

EFI_STATUS
RecordFwUpdateStatus(
  IN UINT32                   FwVersion,
  IN UINT32                   LowestSupportedFwVersion,
  IN UINT32                   LastAttemptStatus,
  IN QCFW_UPDATE_FLAG_VALUE   QcResultValue
  )
{
  EFI_STATUS Status = EFI_SUCCESS;

  if(LAST_ATTEMPT_STATUS_SUCCESS == LastAttemptStatus)
  {
    Status = QcomSetSysFwVersion(FwVersion, LowestSupportedFwVersion);
    HANDLE_ERR_CONTINUE(Status,QcomSetSysFwVersion);
  }
  
  // Print SysFwVersion info
  Status = QcomPrintSysFwVerPartitionData(EFI_D_WARN);
  HANDLE_ERR_CONTINUE(Status,RecordFwUpdateStatus-QcomPrintSysFwVerPartitionData);

  /*Do not consider error from this function as fatal as this is just an
    additional info for QcFwUpdateTool.exe which is an internal tool */
  RecordQCResult(QcResultValue);

  return EFI_SUCCESS;
}

/**
 *  CheckIfStorageHasNewContent function check if BOOT/GPP partitions has new content
 *  in given FwEntry list.
 *
 *  @param FwEntryList            Holds payload linklist
 *  @param NodeCount              Number of entries in payload linklist
 *  @param BootHasUpdate          Indicate whether any FwEntry in current
 *                                payload is targetting BOOT partitions
 *  @param BootHasUpdate          Indicate whether any FwEntry in current
 *                                payload is targetting GPP partitions
 *
 *  @return EFI_STATUS
 */

EFI_STATUS
CheckIfStorageHasNewContent (
  FW_LINKED_LIST_TYPE    *FwEntryList,
  UINTN                   NodeCount,
  BOOLEAN                *BootHasUpdate,
  BOOLEAN                *GppHasUpdate
  )
{
  UINTN                Index=0;
  QPAYLOAD_FW_ENTRY   *FwEntry = NULL;
  FW_LIST_NODE_TYPE   *Node = NULL;
  EFI_STATUS           Status = EFI_SUCCESS;
  EFI_GUID             BOOT_GUID;
  EFI_GUID             GPP_GUID;
  FWENTRY_DISK_PARTITION_TYPE   BootDiskPartType;
  FWENTRY_DISK_PARTITION_TYPE   GppDiskPartType;

  if ((NULL == BootHasUpdate) ||
      (NULL == GppHasUpdate))
  {
      Status = EFI_INVALID_PARAMETER;
      DEBUG_ERR_LABEL("Invalid parameter(s)", CheckIfStorageHasNewContentExit);
  }

  DEBUG((EFI_D_INFO, "CheckIfStorageHasNewContent: NodeCount=%d\n\n", NodeCount));

  Status = GetPartitionGUIDs(&BOOT_GUID, &GPP_GUID);
  HANDLE_ERROR_LABEL(Status, GetPartitionGUIDs, CheckIfStorageHasNewContentExit);

  Status = GetDiskPartAndGptNvType(
             BOOT_GUID,
             NULL,
             &BootDiskPartType
            );
  HANDLE_ERROR_LABEL(Status, GetDiskPartAndGptNvType (BOOT_GUID), CheckIfStorageHasNewContentExit);

  Status = GetDiskPartAndGptNvType(
             GPP_GUID,
             NULL,
             &GppDiskPartType
            );
  HANDLE_ERROR_LABEL(Status, GetDiskPartAndGptNvType (GPP_GUID), CheckIfStorageHasNewContentExit);

  *BootHasUpdate = FALSE;
  *GppHasUpdate = FALSE;

  Node = FwEntryList->Head;
  for(Index =0; ((Index < NodeCount) && (Node != NULL)); Index++)
  {
    FwEntry = (QPAYLOAD_FW_ENTRY*)Node->Data;
    if(FwEntry->Metadata.UpdatePath.DiskPartitionType == BootDiskPartType)
    {
       DEBUG((EFI_D_INFO, "NodeCount=%d..Accessing Boot Partition\n\n", NodeCount));
       *BootHasUpdate = TRUE;
    }
    else if(FwEntry->Metadata.UpdatePath.DiskPartitionType == GppDiskPartType)
    {
       DEBUG((EFI_D_INFO, " NodeCount=%d..Accessing Gpp Partition\n\n", NodeCount));
       *GppHasUpdate = TRUE;
    }
    Node = Node->Next;
  }

CheckIfStorageHasNewContentExit:

  return Status;
}

/**
 *  Function to backup FW entries in FwEntry linked list
 *
 * @return EFI_STATUS
 */

EFI_STATUS
StateFwEntryBackupStart (
   OUT UINT32                   *MsftAttemptStatus,
   OUT QCFW_UPDATE_FLAG_VALUE   *QcResultFlag
   )
{
  EFI_STATUS            Status              = EFI_SUCCESS;
  UINTN                 NodeCount           = 0;
  FW_LIST_NODE_TYPE     *Node               = NULL;
  QPAYLOAD_FW_ENTRY     *pFwEntry           = NULL;
  FW_LINKED_LIST_TYPE   *FwEntryList        = NULL;
  UINTN                 i                   = 0;

  if((MsftAttemptStatus == NULL) ||
     (QcResultFlag == NULL))
  {
    return EFI_INVALID_PARAMETER;
  }

  *MsftAttemptStatus = LAST_ATTEMPT_STATUS_ERROR_UNSUCCESSFUL;
  *QcResultFlag = QCFW_UPDATE_INIT;

  Status = FwGetFwEntryList(&FwEntryList);
  HANDLE_ERROR_LABEL(Status,FwGetFwEntryList,StateFwEntryBackupStartExit);

  Status = LinkedListGetHeadNode(FwEntryList,&Node);
  HANDLE_ERROR_LABEL(Status,LinkedListGetHeadNode,StateFwEntryBackupStartExit);

  if (Node == NULL)
  {
    return EFI_INVALID_PARAMETER;
  }

  Status= LinkedListGetNodeCount(FwEntryList,&NodeCount);
  HANDLE_ERROR_LABEL(Status,LinkedListGetNodeCount,StateFwEntryBackupStartExit);

  for (i = 0; i < NodeCount; i++)
  {
    ResetHookPhaseAndSystem(
      QCOM_TESTHOOK_BACKUP_PHASE, 
      (i + 1), 
      NodeCount
    );

    DEBUG((EFI_D_WARN,"    Backing up %d/%d FwEntry...\n", (i + 1), NodeCount));
    if (Node != NULL)
    {
      pFwEntry = (QPAYLOAD_FW_ENTRY*)Node->Data;
      if (pFwEntry != NULL)
      {
        if (pFwEntry->BackupAlreadyDone == TRUE)
        {
          // Skipping backup operation for PARTITION type fwentries. 
          DEBUG((EFI_D_WARN, "      Backup skipped as backup is already available!!!\n\n"));
        }
        else
        {
          // To ensure fail-safe update, backup need to be initiated for 
          // OEM-specific firmware component and DPP as these may involve file-based update.
          Status = FwEntryBackup(pFwEntry);
          if(EFI_ERROR(Status))
          {
            DEBUG((EFI_D_ERROR,"      Backup failed with error: %r\n\n", Status));
            goto StateFwEntryBackupStartExit;
          }
          else
          {
            DEBUG((EFI_D_ERROR,"      Backup Success\n\n"));
          }
        }

        Node = Node->Next;
      }
      else
      {
        Status = EFI_INVALID_PARAMETER;
        *QcResultFlag = QCFW_UPDATE_ERR_FWENTRY_NULL_ENTRY;
        DEBUG_ERR_LABEL("ListNode->Data == NULL ",StateFwEntryBackupStartExit);
      }
    }
    else
    {
      Status = EFI_INVALID_PARAMETER;
      *QcResultFlag = QCFW_UPDATE_ERR_LIST_NULL_NODE;
      DEBUG_ERR_LABEL("ListNode == NULL ",StateFwEntryBackupStartExit);
    }
  }

  Status = SetUpdateState(FW_STATE_UPDATE_START);
  HANDLE_ERROR_LABEL(Status,SetUpdateState(FW_STATE_UPDATE_START),StateFwEntryBackupStartExit);

  return EFI_SUCCESS;

StateFwEntryBackupStartExit:

  FwPrintFwEntry(pFwEntry,EFI_D_ERROR);

 return Status;
}

/**
 *  Function that confirms the validity of primary partitions
 *
 * @return EFI_STATUS
 */

EFI_STATUS
StateFwEntryPrepareUpdateStart (
   OUT UINT32                   *MsftAttemptStatus,
   OUT QCFW_UPDATE_FLAG_VALUE   *QcResultFlag
   )
{
  EFI_STATUS            Status                 = EFI_SUCCESS;
  UINTN                 NodeCount              = 0;
  FW_LIST_NODE_TYPE     *Node                  = NULL;
  QPAYLOAD_FW_ENTRY     *pFwEntry              = NULL;
  FW_LINKED_LIST_TYPE   *FwEntryList           = NULL;
  UINTN                 i                      = 0;
  BOOLEAN               BootBackupNeeded       = FALSE;
  BOOLEAN               GppBackupNeeded        = FALSE;
  EFI_RECOVERY_PROTOCOL *hRecoveryProtocol     = NULL;
  EFI_GUID              *PartitionGuid         = NULL;
   UINTN                 CapsulePendingListSize = 0;
  EFI_GUID              *CapsulePendingList    = NULL;
  BOOLEAN                IsRecoveryFailed      = FALSE;

  if((MsftAttemptStatus == NULL) ||
     (QcResultFlag == NULL))
  {
    return EFI_INVALID_PARAMETER;
  }

  *MsftAttemptStatus = LAST_ATTEMPT_STATUS_ERROR_UNSUCCESSFUL;
  *QcResultFlag = QCFW_UPDATE_INIT;

  Status = FwGetFwEntryList(&FwEntryList);
  HANDLE_ERROR_LABEL(Status,FwGetFwEntryList,StateFwEntryPrepareUpdateStartExit);

  Status = LinkedListGetHeadNode(FwEntryList,&Node);
  HANDLE_ERROR_LABEL(Status,LinkedListGetHeadNode,StateFwEntryPrepareUpdateStartExit);

  if (Node == NULL)
  {
    return EFI_INVALID_PARAMETER;
  }

  Status= LinkedListGetNodeCount(FwEntryList,&NodeCount);
  HANDLE_ERROR_LABEL(Status,LinkedListGetNodeCount,StateFwEntryPrepareUpdateStartExit);

  Status = CheckIfStorageHasNewContent(FwEntryList, NodeCount, &BootBackupNeeded, &GppBackupNeeded);
  HANDLE_ERROR_LABEL(Status, CheckIfStorageHasNewContent, StateFwEntryPrepareUpdateStartExit);

  DEBUG((EFI_D_INFO, "BootBackupNeeded = %d....GppBackupNeeded = %d\n", BootBackupNeeded, GppBackupNeeded));

  if(boot_from_ufs())
  {
    // if UFS device then boot partition backup not needed
    BootBackupNeeded = FALSE;
  }

  // Backup BOOT and GPP/LUN4 GPT to FAT
  DEBUG((EFI_D_INFO, "Calling BackupGPTTable() with BootBackupNeeded = %d  GppBackupNeeded = %d\n\n", BootBackupNeeded, GppBackupNeeded));
  Status = BackupGPTTable (BootBackupNeeded, GppBackupNeeded);
  HANDLE_ERROR_LABEL(Status,BackupGPTTable,StateFwEntryPrepareUpdateStartExit);

  // Get Recovery protocol interface
  Status = gBS->LocateProtocol(
    &gEfiRecoveryProtocolGuid,
    NULL,
    (VOID **)&hRecoveryProtocol
    );
  if (EFI_ERROR(Status))
  {
    DEBUG((EFI_D_ERROR, "Failed to locate Recovery Protocol.\n"));
    return Status;
  }

  CapsulePendingListSize = (NodeCount * sizeof(EFI_GUID));
  CapsulePendingList = AllocateZeroPool(CapsulePendingListSize);
  if( CapsulePendingList == NULL)
  {
    Status =  EFI_OUT_OF_RESOURCES;
    DEBUG_ERR_LABEL(
      "CapsulePendingList memory allocation failed\n",
      StateFwEntryPrepareUpdateStartExit
      );
  }

  // Capture partitions under update in CapsulePendingList
  for (i = 0; i < NodeCount; i++)
  {
    ResetHookPhaseAndSystem(
      QCOM_TESTHOOK_PREPARE_UPDATE_PHASE, 
      (i + 1), 
      NodeCount
    );

    if (Node != NULL)
    {
      pFwEntry = (QPAYLOAD_FW_ENTRY*)Node->Data;
      if (pFwEntry != NULL)
      {
        PartitionGuid =  &pFwEntry->Metadata.UpdatePath.PartitionTypeGUID;
        CopyGuid(&CapsulePendingList[i], PartitionGuid);
        DEBUG((EFI_D_INFO, "CapsulePendingList[%d]: %g", i, &CapsulePendingList[i]));
      }
      else
      {
        Status = EFI_INVALID_PARAMETER;
        *QcResultFlag = QCFW_UPDATE_ERR_FWENTRY_NULL_ENTRY;
        DEBUG_ERR_LABEL("ListNode->Data == NULL ",StateFwEntryPrepareUpdateStartExit);
      }
      Node = Node->Next;
    }
    else
    {
      Status = EFI_INVALID_PARAMETER;
      *QcResultFlag = QCFW_UPDATE_ERR_LIST_NULL_NODE;
      DEBUG_ERR_LABEL("ListNode == NULL ",StateFwEntryPrepareUpdateStartExit);
    }
  }

  DEBUG((EFI_D_WARN,"\n   Querying recovery status of partitions under update...\n"));

  Status = hRecoveryProtocol->CheckIfRecoveryFailed(
    hRecoveryProtocol,
    CapsulePendingList,
    CapsulePendingListSize,
    &IsRecoveryFailed
    );
  HANDLE_ERROR_LABEL(Status,CheckIfRecoveryFailed,StateFwEntryPrepareUpdateStartExit);

  if (IsRecoveryFailed)
  {
    // On recovery failure, mark fwupdate state = commmit_update_failure.
    // This is done to set fwupdate status = failed.
    Status = SetUpdateState(FW_STATE_COMMIT_UPDATE_FAILURE);
    HANDLE_ERROR_LABEL(Status,SetUpdateState(FW_STATE_COMMIT_UPDATE_FAILURE),StateFwEntryPrepareUpdateStartExit);
  }
  else
  {
    // Register paritions pending for update.
    Status = hRecoveryProtocol->SetPartitionsUnderUpdate(
      CapsulePendingList,
      CapsulePendingListSize
      );
    HANDLE_ERROR_LABEL(Status,SetPartitionsUnderUpdate,StateFwEntryPrepareUpdateStartExit);

    Status = SetUpdateState(FW_STATE_BACKUP_START);
    HANDLE_ERROR_LABEL(Status,SetUpdateState(FW_STATE_BACKUP_START),StateFwEntryPrepareUpdateStartExit);
  }

StateFwEntryPrepareUpdateStartExit:

  if (CapsulePendingList != NULL)
  {
    FreePool(CapsulePendingList);
    CapsulePendingList = NULL;
  }

  FwPrintFwEntry(pFwEntry,EFI_D_ERROR);

  return Status;
}

/**
 *  Function to allocate and init memory for all GPT backup table entries
 *
 * @return EFI_STATUS
 */
EFI_STATUS
AllocateAndInitGPTBackupData(
    ACTIVE_GPT_SUB_DATA **BootGPTSubData,
    ACTIVE_GPT_SUB_DATA **GppGPTSubData
)
{
  EFI_STATUS            Status = EFI_SUCCESS;
  UINT32                BootMaxEntries = 0;
  UINT32                GppMaxEntries = 0;

  if(boot_from_emmc())
  {
    BootMaxEntries = EMMC_BOOT_MAX_ENTRIES;
    GppMaxEntries = EMMC_GPP_MAX_ENTRIES;
  }
  else if(boot_from_ufs())
  {
    BootMaxEntries = UFS_BOOT_MAX_ENTRIES;
    GppMaxEntries = UFS_GPP_MAX_ENTRIES;
  }
  else if(boot_from_spi_nor())
  {
    BootMaxEntries = SPINOR_BOOT_MAX_ENTRIES;
    GppMaxEntries = NVME_GPP_MAX_ENTRIES;
  }
  else
  {
    //Returning unsupported if device is not booting with default boot options
    return EFI_UNSUPPORTED;
  }

  if (NULL != BootGPTSubData)
  {
    *BootGPTSubData = NULL;

    if (0 != BootMaxEntries)
    {
      Status = AllocateAndInitGPTSubData (BootMaxEntries, BootGPTSubData);
      HANDLE_ERROR_LABEL(Status, AllocateAndInitGPTSubData (BootMaxEntries),  AllocateMemoryForGPTBackupTableExit);
    }
  }
  
  if (NULL != GppGPTSubData)
  {
    *GppGPTSubData = NULL;

      if (0 != GppMaxEntries)
    {
      Status = AllocateAndInitGPTSubData (GppMaxEntries, GppGPTSubData);
      HANDLE_ERROR_LABEL(Status, AllocateAndInitGPTSubData (GppMaxEntries),  AllocateMemoryForGPTBackupTableExit);
    }
  }

  return EFI_SUCCESS;

 AllocateMemoryForGPTBackupTableExit:

  if ((BootGPTSubData != NULL) &&
    (*BootGPTSubData != NULL))
  {
    FreePool(*BootGPTSubData);
    *BootGPTSubData = NULL;
  }

  if ((GppGPTSubData != NULL) &&
    (*GppGPTSubData != NULL))
  {
    FreePool(*GppGPTSubData);
    *GppGPTSubData = NULL;
  }

  return Status;
}

/**
 *  Function to update FW entries in FwEntry linked list 
 *  into secondary partitions.
 *
 * @return EFI_STATUS
 */

EFI_STATUS
StateFwEntryUpdateStart(
   OUT UINT32                   *MsftAttemptStatus,
   OUT QCFW_UPDATE_FLAG_VALUE   *QcResultFlag,
   OUT BOOLEAN                  *BootLunPartitionsUpdated
)
{
  EFI_STATUS           Status         = EFI_SUCCESS;
  UINTN                NodeCount      = 0;
  FW_LIST_NODE_TYPE   *Node           = NULL;
  QPAYLOAD_FW_ENTRY   *pFwEntry       = NULL;
  FW_LINKED_LIST_TYPE *FwEntryList    = NULL;
  UINTN                i              = 0;
  EFI_GUID             BOOT_GUID;
  EFI_GUID             GPP_GUID;

  if((MsftAttemptStatus == NULL) ||
     (QcResultFlag == NULL))
  {
    return EFI_INVALID_PARAMETER;
  }

  Status = GetPartitionGUIDs(&BOOT_GUID, &GPP_GUID);
  HANDLE_ERROR_LABEL(Status, GetPartitionGUIDs, StateFwEntryUpdateStartExit);

  *MsftAttemptStatus = LAST_ATTEMPT_STATUS_ERROR_UNSUCCESSFUL;
  *QcResultFlag = QCFW_UPDATE_INIT;

  Status = FwGetFwEntryList(&FwEntryList);
  HANDLE_ERROR_LABEL(Status,FwGetFwEntryList,StateFwEntryUpdateStartExit);

  Status = LinkedListGetHeadNode(FwEntryList,&Node);
  HANDLE_ERROR_LABEL(Status,LinkedListGetHeadNode,StateFwEntryUpdateStartExit);

  if (Node == NULL)
  {
    Status = EFI_INVALID_PARAMETER;
    *QcResultFlag = QCFW_UPDATE_ERR_LIST_NULL_NODE;
    DEBUG_ERR_LABEL("ListNode == NULL ",StateFwEntryUpdateStartExit);
  }

  Status = LinkedListGetNodeCount(FwEntryList,&NodeCount);
  HANDLE_ERROR_LABEL(Status,LinkedListGetNodeCount,StateFwEntryUpdateStartExit);

  *BootLunPartitionsUpdated =  FALSE;

  for (i = 0; i < NodeCount; i++)
  {
    ResetHookPhaseAndSystem(
      QCOM_TESTHOOK_UPDATE_PHASE, 
      (i + 1), 
      NodeCount
    );

    DEBUG((EFI_D_WARN,"    Updating %d/%d FwEntry...\n", (i + 1), NodeCount));
    if (Node != NULL)
    {
      pFwEntry = (QPAYLOAD_FW_ENTRY*)Node->Data;
      if (pFwEntry != NULL)
      {
        DEBUG((EFI_D_INFO,"PartitionName: %s\n", pFwEntry->Metadata.UpdatePath.PartitionName));
        if (pFwEntry->Metadata.UpdateType == FWENTRY_UPDATE_TYPE_CUSTOM_FIRMWARE1)
        {
          /* Update should be targeted on primary partition for custom firmware component */
          Status = FwEntryUpdate(pFwEntry, FWENTRY_OPERATION_PATH_TYPE_DEST);
        }
        else if ((pFwEntry->Metadata.UpdateType == FWENTRY_UPDATE_TYPE_DPP_OEM) ||
                 (pFwEntry->Metadata.UpdateType == FWENTRY_UPDATE_TYPE_DPP_QCOM) ||
                 (pFwEntry->Metadata.UpdateType == FWENTRY_UPDATE_TYPE_OPM_PRIV_KEY))
        {
          /* Update should be targeted on primary partition for DPP files 
             as DPP protocol doesn't support writing into backup partition handle.
          */
          Status = FwEntryUpdate(pFwEntry, FWENTRY_OPERATION_PATH_TYPE_DEST);
        }
        else
        {
          /* As per the logic defined in FwEntrySetPartitionHandles,
             update backup location for UFS boot LUNs will point to inactive LUN.
             So, we can update the payload to this update backup path type for all 
             firmware components, except custom firmware.
          */
          Status = FwEntryUpdate(pFwEntry, FWENTRY_OPERATION_PATH_TYPE_BACKUP);
          if ((boot_from_ufs()) &&
              ((pFwEntry->Metadata.UpdatePath.DiskPartitionType == FWENTRY_UFS_LUN1) ||
               (pFwEntry->Metadata.UpdatePath.DiskPartitionType == FWENTRY_UFS_LUN2)))
          {
            if (!*BootLunPartitionsUpdated)
            {
              *BootLunPartitionsUpdated = TRUE;
            }
          }
        }

        if(EFI_ERROR(Status))
        {
          DEBUG((EFI_D_ERROR,"      Update failed with error: %r\n\n", Status));
          goto StateFwEntryUpdateStartExit;
        }
        else
        {
          FwEntryList->UpdatedTotalFvEntrySize += pFwEntry->FwEntrySize;
          SysFwUpdateIntraPhaseProgress(
            ((FwEntryList->UpdatedTotalFvEntrySize * 100) / FwEntryList->TotalFvEntrySize),
            PROGRESS_CAPSULE_UPDATE_START,
            PROGRESS_CAPSULE_UPDATE_END
            );
          DEBUG((EFI_D_ERROR,"      Update Success\n\n"));
        }
      }
      else
      {
        Status = EFI_INVALID_PARAMETER;
        *QcResultFlag = QCFW_UPDATE_ERR_FWENTRY_NULL_ENTRY;
        DEBUG_ERR_LABEL("ListNode->Data == NULL ",StateFwEntryUpdateStartExit);
      }
      Node = Node->Next;
    }
    else
    {
      Status = EFI_INVALID_PARAMETER;
      *QcResultFlag = QCFW_UPDATE_ERR_LIST_NULL_NODE;
      DEBUG_ERR_LABEL("ListNode == NULL ",StateFwEntryUpdateStartExit);
    }
  }

  Status = SetUpdateState(FW_STATE_SYNC_START);
  HANDLE_ERROR_LABEL(Status,SetUpdateState(FW_STATE_SYNC_START),StateFwEntryUpdateStartExit);

  return EFI_SUCCESS;

StateFwEntryUpdateStartExit:

  FwPrintFwEntry(pFwEntry,EFI_D_ERROR);

  return Status;
}

/**
 *  Function to update FW entries in FwEntry linked list 
 *  into primary partitions.
 * @return EFI_STATUS
 */

EFI_STATUS
StateFwEntrySyncStart(
   OUT UINT32                   *MsftAttemptStatus,
   OUT QCFW_UPDATE_FLAG_VALUE   *QcResultFlag,
   IN  BOOLEAN                   BootLunPartitionsUpdated
)
{
  GPT_TABLE_STATE      BOOT_GPT_STATE = ORIGINAL_TABLE;
  GPT_TABLE_STATE      GPP_GPT_STATE  = ORIGINAL_TABLE;
  EFI_STATUS           Status         = EFI_SUCCESS;
  UINTN                NodeCount      = 0;
  FW_LIST_NODE_TYPE   *Node           = NULL;
  QPAYLOAD_FW_ENTRY   *pFwEntry       = NULL;
  FW_LINKED_LIST_TYPE *FwEntryList    = NULL;
  UINTN                i              = 0;
  BOOLEAN              SwitchBootGpt  = FALSE;
  BOOLEAN              SwitchGppGpt   = FALSE;
  EFI_GUID             BOOT_GUID      = {0};
  EFI_GUID             GPP_GUID       = {0}; 
  EFI_STATUS           SyncStatus     = EFI_SUCCESS;
  QPAYLOAD_FW_ENTRY  **pFailedFwEntry = NULL;
  UINTN                j              = 0;

  if((MsftAttemptStatus == NULL) ||
     (QcResultFlag == NULL))
  {
    return EFI_INVALID_PARAMETER;
  }

  Status = GetPartitionGUIDs(&BOOT_GUID, &GPP_GUID);
  HANDLE_ERROR_LABEL(Status, GetPartitionGUIDs, StateFwEntrySyncStartExit);

  *MsftAttemptStatus = LAST_ATTEMPT_STATUS_ERROR_UNSUCCESSFUL;
  *QcResultFlag = QCFW_UPDATE_INIT;

  Status = FwGetFwEntryList(&FwEntryList);
  HANDLE_ERROR_LABEL(Status,FwGetFwEntryList,StateFwEntrySyncStartExit);

  Status = LinkedListGetHeadNode(FwEntryList,&Node);
  HANDLE_ERROR_LABEL(Status,LinkedListGetHeadNode,StateFwEntrySyncStartExit);

  if (Node == NULL)
  {
    Status = EFI_INVALID_PARAMETER;
    *QcResultFlag = QCFW_UPDATE_ERR_LIST_NULL_NODE;
    DEBUG_ERR_LABEL("ListNode == NULL ",StateFwEntrySyncStartExit);
  }

  Status = LinkedListGetNodeCount(FwEntryList,&NodeCount);
  HANDLE_ERROR_LABEL(Status,LinkedListGetNodeCount,StateFwEntrySyncStartExit);

  // Before proceeding with sync phase, switch backup GPT of boot and GPP/LUN4 partitions.
  Status = GetAllSwitchGptRequestsFromFwEntryList(FwEntryList, &SwitchBootGpt, &SwitchGppGpt);
  HANDLE_ERROR_LABEL(Status,GetAllSwitchGptRequestsFromFwEntryList,StateFwEntrySyncStartExit);

  // We might have encountered a reset hence first check if we have the right
  // backup GPT table if not correct it and then invalidate it
  DEBUG((EFI_D_INFO, "SwitchBootGpt: %d, SwitchGppGpt: %d\n", SwitchBootGpt, SwitchGppGpt));

  // Only do this is GPT switch is needed
  if (SwitchBootGpt)
  {
    // At this point, GPT backup should be available in NV from prepare update phase.
    Status = CmpGPTTable(BACKUP_GPT_TABLE, BOOT_GUID, &BOOT_GPT_STATE);
    HANDLE_ERROR_LABEL(Status,CmpGPTTable,StateFwEntrySyncStartExit);
  }
  DEBUG((EFI_D_INFO, "BOOT_GPT_STATE: %d\n", BOOT_GPT_STATE));

  if (SwitchGppGpt)
  {
    // At this point, GPT backup should be available in NV from prepare update phase.
    Status = CmpGPTTable(BACKUP_GPT_TABLE, GPP_GUID, &GPP_GPT_STATE);
    HANDLE_ERROR_LABEL(Status,CmpGPTTable,StateFwEntrySyncStartExit);
  }
  DEBUG((EFI_D_INFO, "GPP_GPT_STATE: %d\n", GPP_GPT_STATE));

  // boot GPT table for UFS system does not need to be modified
  if((BOOT_GPT_STATE == ORIGINAL_TABLE) && (SwitchBootGpt == TRUE) && (!boot_from_ufs()))
  {
    Status = ModifyAllBackupGptTablesForFailSafeUpdate(FwEntryList,
                                                       SwitchBootGpt,
                                                       FALSE);
    HANDLE_ERROR_LABEL(Status,ModifyAllBackupGptTablesForFailSafeUpdate,StateFwEntrySyncStartExit);
  }

  if ((GPP_GPT_STATE == ORIGINAL_TABLE) && (SwitchGppGpt == TRUE))
  {
    Status = ModifyAllBackupGptTablesForFailSafeUpdate(FwEntryList,
                                                       FALSE,
                                                       SwitchGppGpt) ;
    HANDLE_ERROR_LABEL(Status,ModifyAllBackupGptTablesForFailSafeUpdate,StateFwEntrySyncStartExit);
  }

  // Invalidate primary GPT
  Status = InvalidateAllPrimaryGPT(SwitchBootGpt, SwitchGppGpt);
  HANDLE_ERROR_LABEL(Status,InvalidateAllPrimaryGPT,StateFwEntrySyncStartExit);

  DEBUG((EFI_D_INFO, "BootLunPartitionsUpdated: %d\n", BootLunPartitionsUpdated));
  /* If the update phase has updated the inactive BOOT_LUN partitions with new content,
     identify the same and set it as active BOOT LUN.*/
  if (BootLunPartitionsUpdated)
  {
    Status = SetBootableLUNPostUpdate();
    HANDLE_ERROR_LABEL(Status, SetBootableLUNPostUpdate, StateFwEntrySyncStartExit);
  }

  pFailedFwEntry = AllocateZeroPool(NodeCount * sizeof(QPAYLOAD_FW_ENTRY *));
  if (pFailedFwEntry == NULL)
  {
    Status = EFI_OUT_OF_RESOURCES;
    DEBUG_ERR_LABEL(
      "pFailedFwEntry memory allocation failed\n",
      StateFwEntrySyncStartExit
      );
  }

  // Proceed with syncing the capsule contents to primary partitions.
  for (i = 0; i < NodeCount; i++)
  {
    ResetHookPhaseAndSystem(
      QCOM_TESTHOOK_SYNC_PHASE, 
      (i + 1), 
      NodeCount
    );

    DEBUG((EFI_D_WARN,"    Syncing %d/%d FwEntry...\n", (i + 1), NodeCount));
    if (Node != NULL)
    {
      pFwEntry = (QPAYLOAD_FW_ENTRY*)Node->Data;
      if (pFwEntry != NULL)
      {
        /* In UPDATE phase, primary and backup partitions within the inactive LUN 
           will be updated with new capsule contents. Users of this boot LUN, except 
           firmware update process will operate only within the active LUN. So,
           we will skip syncing for UFS boot LUNs.
        */
        if ((boot_from_ufs()) &&
            ((pFwEntry->Metadata.UpdatePath.DiskPartitionType == FWENTRY_UFS_LUN1) ||
             (pFwEntry->Metadata.UpdatePath.DiskPartitionType == FWENTRY_UFS_LUN2)))
        {
          DEBUG((EFI_D_WARN,"      Skip syncing for boot LUNs\n\n"));
        }
        else if (pFwEntry->Metadata.UpdateType == FWENTRY_UPDATE_TYPE_CUSTOM_FIRMWARE1)
        {
          /* Skip syncing for custom firmware component */
          DEBUG((EFI_D_WARN,"      Skip syncing for custom firmware\n\n"));
        }
        else if ((pFwEntry->Metadata.UpdateType == FWENTRY_UPDATE_TYPE_DPP_OEM) ||
                 (pFwEntry->Metadata.UpdateType == FWENTRY_UPDATE_TYPE_DPP_QCOM) ||
                 (pFwEntry->Metadata.UpdateType == FWENTRY_UPDATE_TYPE_OPM_PRIV_KEY))
        {
          /* Primary partition is already updated in update phase and syncing to 
             backup partition may not be required, as it will be handled in backup
             phase before next update begins. The older copy will be retained in 
             backup partition for fail-safe update.
          */
          DEBUG((EFI_D_WARN,"      Skip syncing for DPP files\n\n"));
        }
        else
        {
          Status = FwEntryUpdate(pFwEntry, FWENTRY_OPERATION_PATH_TYPE_DEST);
          if(EFI_ERROR(Status))
          {
            // Secondary partitions are updated with FMP payload in previous phase.
            // Any reset post the update phase will anyhow attempt to boot from updated partitions.
            // So, we will continue to make the partitions in sync even if we encounter
            // error in syncing any of the partitions.
            DEBUG((EFI_D_ERROR,"      Sync failed with error: %r. Continue!!!\n\n", Status));
            SyncStatus = Status;
            pFailedFwEntry[j++] = pFwEntry;
          }
          else
          {
            FwEntryList->SyncedTotalFvEntrySize += pFwEntry->FwEntrySize;
            SysFwUpdateIntraPhaseProgress(
              ((FwEntryList->SyncedTotalFvEntrySize * 100) / FwEntryList->TotalFvEntrySize),
              PROGRESS_CAPSULE_SYNC_START,
              PROGRESS_CAPSULE_SYNC_END
              );
            DEBUG((EFI_D_ERROR,"      Sync Success\n\n"));
          }
        }
      }
      else
      {
        Status = EFI_INVALID_PARAMETER;
        *QcResultFlag = QCFW_UPDATE_ERR_FWENTRY_NULL_ENTRY;
        DEBUG_ERR_LABEL("ListNode->Data == NULL ",StateFwEntrySyncStartExit);
      }
      Node = Node->Next;
    }
    else
    {
      Status = EFI_INVALID_PARAMETER;
      *QcResultFlag = QCFW_UPDATE_ERR_LIST_NULL_NODE;
      DEBUG_ERR_LABEL("ListNode == NULL ",StateFwEntrySyncStartExit);
    }
  }

  //Return on sync failure after we attempted to make all partitions in sync.
  HANDLE_ERROR_LABEL(SyncStatus,FwEntryUpdate,StateFwEntrySyncStartExit);

  //Mark sync SUCCCESS only when no errors identified in sync phase.
  Status = SetUpdateState(FW_STATE_COMMIT_UPDATE);
  HANDLE_ERR_CONTINUE(Status,SetUpdateState(FW_STATE_COMMIT_UPDATE));

  return EFI_SUCCESS;

StateFwEntrySyncStartExit:

  if (pFailedFwEntry)
  {
    while(j-- != 0)
    {
      FwPrintFwEntry(pFailedFwEntry[j],EFI_D_ERROR);
    }

    FreePool(pFailedFwEntry);
    pFailedFwEntry = NULL;
  }

  return (SyncStatus? SyncStatus : Status);
}

/**
*  Function to set the LUN (LUN1 or LUN2) as bootable where the
*  update was applied. It will determine the current bootable LUN
*  (LUN1 or LUN2) and it will set bootable the other LUN
*
* @return EFI_STATUS
*/
EFI_STATUS
SetBootableLUNPostUpdate(VOID)
{
  EFI_STATUS                 Status           = EFI_SUCCESS;
  EFI_MEM_CARDINFO_PROTOCOL *MemCardInfo      = NULL;
  UINT32                     currentBootLun   = 0;
  UINT32                     newBootLun       = 0;
  UINT32                     LunNumber1       = 1;
  UINT32                     LunNumber2       = 2;


  Status = GetBootLUN(&currentBootLun);
  HANDLE_ERROR_LABEL(Status, GetBootLUN, setBootableLUNPostUpdateExit);

  if (currentBootLun == LunNumber1)
  {
    newBootLun = LunNumber2;
  }
  else if (currentBootLun == LunNumber2)
  {
    newBootLun = LunNumber1;
  }
  else
  {
    Status = EFI_NOT_FOUND;
    DEBUG_ERR_LABEL("Could not determine Boot LUN", setBootableLUNPostUpdateExit);
  }

  Status = GetMemCardInfoHandle(&MemCardInfo);
  HANDLE_ERROR_LABEL(Status, GetMemCardInfoHandle, setBootableLUNPostUpdateExit);

  Status = MemCardInfo->SetBootLU(MemCardInfo, newBootLun);
  HANDLE_ERROR_LABEL(Status, MemCardInfo->GetBootLU, setBootableLUNPostUpdateExit);

setBootableLUNPostUpdateExit:
  return Status;
}

/**
 *  Function to update Flags/State in commit update state
 *
 * @return EFI_STATUS
 */
EFI_STATUS
StateFwEntryCommitUpdateStart(
  OUT UINT32                   *MsftAttemptStatus,
  OUT QCFW_UPDATE_FLAG_VALUE   *QcResultFlag
  )
{
  EFI_STATUS           Status         = EFI_SUCCESS;
  FW_LINKED_LIST_TYPE *FwEntryList    = NULL;
  FW_LIST_NODE_TYPE   *Node           = NULL;
  BOOLEAN              RestoreBootGpt = FALSE;
  BOOLEAN              RestoreGppGpt  = FALSE;

  if((MsftAttemptStatus == NULL) ||
     (QcResultFlag == NULL))
  {
    return EFI_INVALID_PARAMETER;
  }
  *MsftAttemptStatus = LAST_ATTEMPT_STATUS_ERROR_UNSUCCESSFUL;
  *QcResultFlag = QCFW_UPDATE_INIT;

  Status = FwGetFwEntryList(&FwEntryList);
  HANDLE_ERROR_LABEL(Status,FwGetFwEntryList,StateFwEntryCommitUpdateStartExit);

  Status = GetAllSwitchGptRequestsFromFwEntryList(FwEntryList, &RestoreBootGpt, &RestoreGppGpt);
  HANDLE_ERROR_LABEL(Status,GetAllSwitchGptRequestsFromFwEntryList,StateFwEntryCommitUpdateStartExit);

  // We could have come back to this state after a reboot, hence we need to verify
  // the state of the primary table and if is switched shows UEFI copied backup
  // table to primary

  Status = RestoreAllGPTTablesFromNV(PRIMARY_GPT_TABLE, RestoreBootGpt, RestoreGppGpt);
  HANDLE_ERROR_LABEL(Status,RestoreAllGPTTablesFromNV,StateFwEntryCommitUpdateStartExit);

  Status = RestoreAllGPTTablesFromNV(BACKUP_GPT_TABLE, RestoreBootGpt, RestoreGppGpt);
  HANDLE_ERROR_LABEL(Status,RestoreAllGPTTablesFromNV,StateFwEntryCommitUpdateStartExit);

  Status = LinkedListGetHeadNode(FwEntryList,&Node);
  HANDLE_ERROR_LABEL(Status,LinkedListGetHeadNode,StateFwEntryCommitUpdateStartExit);

  if (Node == NULL)
  {
    Status = EFI_INVALID_PARAMETER;
    *QcResultFlag = QCFW_UPDATE_ERR_LIST_NULL_NODE;
    DEBUG_ERR_LABEL("ListNode == NULL ",StateFwEntryCommitUpdateStartExit);
  }

  DEBUG((EFI_D_WARN,"GPT restore complete\n"));

  Status = SetUpdateState(FW_STATE_NOT_IN_PROGRESS);
  HANDLE_ERROR_LABEL(Status,SetUpdateState(FW_STATE_NOT_IN_PROGRESS),StateFwEntryCommitUpdateStartExit);

  Status = SetAttemptCount(0);
  //We want to continue if SetAttemptCount failed.
  HANDLE_ERR_CONTINUE(Status,SetAttemptCount(0));

  //Write the new BreakingChangeNumber to FS
  Status = SetBreakingChangeNumber(PayLoadHeader.BreakingChangeNumber);

  if(Status != EFI_SUCCESS)
  {
    *MsftAttemptStatus = LAST_ATTEMPT_STATUS_SUCCESS;
    *QcResultFlag = QCFW_UPDATE_SUCCESS;
    HANDLE_ERR_CONTINUE(Status,SetBreakingChangeNumber);
  }
  else if(bDoubleUpdateNeeded)
  {
    //This is a Breaking Change Case. A double-update is needed. Do not clear the commit flag

    // System Reset is still required if UpdateAttemptCountInFs failed.
    // Force Reset here.
    DEBUG((EFI_D_WARN,"\n\nDouble update required. Resetting System...\n\n"));
    gRT->ResetSystem(EfiResetCold,
                     EFI_SUCCESS,
                     0,
                     NULL) ;
  }
  else
  {
    //This is NOT a Breaking Change Case. A double-update is NOT needed. Clear the commit flag.
    /*Clear flag*/
    *MsftAttemptStatus = LAST_ATTEMPT_STATUS_SUCCESS;
    *QcResultFlag = QCFW_UPDATE_SUCCESS;
  }

  return EFI_SUCCESS;

StateFwEntryCommitUpdateStartExit:

    return Status;
}

/**
 *  Function to Rollback all FW entries
 *
 * @return EFI_STATUS
 */
EFI_STATUS
StateFwEntryRollbackAllStart(VOID
  )
{
  EFI_STATUS          Status       = EFI_SUCCESS;
  UINTN               i            = 0;
  UINTN               NodeCount    = 0;
  FW_LIST_NODE_TYPE   *Node        = NULL;
  QPAYLOAD_FW_ENTRY   *pFwEntry     = NULL;
  FW_LINKED_LIST_TYPE *FwEntryList = NULL;

  Status = FwGetFwEntryList(&FwEntryList);
  HANDLE_ERROR_LABEL(Status,FwGetFwEntryList,StateFwEntryRollbackAllStartExit);

  Status = LinkedListGetHeadNode(FwEntryList,&Node);
  HANDLE_ERROR_LABEL(Status,LinkedListGetHeadNode,StateFwEntryRollbackAllStartExit);

  if (Node == NULL)
  {
    Status = EFI_INVALID_PARAMETER;
    DEBUG_ERR_LABEL("ListNode == NULL ",StateFwEntryRollbackAllStartExit);
  }

  Status= LinkedListGetNodeCount(FwEntryList,&NodeCount);
  HANDLE_ERROR_LABEL(Status,LinkedListGetNodeCount,StateFwEntryRollbackAllStartExit);

  for (i = 0; i < NodeCount; i++)
  {
    if (Node != NULL)
    {
      ResetHookPhaseAndSystem(
        QCOM_TESTHOOK_ROLLBACK_PHASE, 
        (i + 1), 
        NodeCount
      );
    
      DEBUG((EFI_D_ERROR,"    Rollingback %d/%d FwEntry..\n", (i + 1), NodeCount));
      pFwEntry = (QPAYLOAD_FW_ENTRY*)Node->Data;

      if (pFwEntry != NULL)
      {
        /* LUN1 and LUN2 will not be roll back */
        if ((pFwEntry->Metadata.UpdatePath.DiskPartitionType == FWENTRY_UFS_LUN1)
         || (pFwEntry->Metadata.UpdatePath.DiskPartitionType == FWENTRY_UFS_LUN2))
        {
          DEBUG((EFI_D_ERROR, "      Rollback Success\n\n"));
          Node = Node->Next;
          continue;
        }
        
        Status = FwEntryRollback(pFwEntry);
        if(EFI_ERROR(Status))
        {
          FwPrintFwEntry(pFwEntry, EFI_D_ERROR);
          DEBUG((EFI_D_ERROR,"      Rollback failed\n\n"));
        }
        else
        {
          DEBUG((EFI_D_ERROR,"      Rollback Success\n\n"));
        }
        HANDLE_ERR_CONTINUE(Status,FwEntryRollback);
      }
      else
      {
        DEBUG((EFI_D_ERROR,"Node->Data == NULL\n"));
      }
      Node = Node->Next;
    }
    else
    {
      Status = EFI_INVALID_PARAMETER;
      DEBUG_ERR_LABEL("ListNode == NULL ",StateFwEntryRollbackAllStartExit);
    }
  }

  Status = SetUpdateState(FW_STATE_COMMIT_UPDATE_FAILURE);
  /*We want rollback to continue if SetUpdateState failed*/
  HANDLE_ERR_CONTINUE(Status,SetUpdateState(FW_STATE_COMMIT_UPDATE_FAILURE));

  return EFI_SUCCESS;

StateFwEntryRollbackAllStartExit:

  FwPrintFwList(FwEntryList,EFI_D_ERROR);

  return Status;

}

/**
 *  Function to Rollback all FW entries
 *
 * @return EFI_STATUS
 */
EFI_STATUS
StateFwEntryCommitUpdateFailureStart(VOID
  )
{
  EFI_STATUS          Status        = EFI_SUCCESS;
  FW_LINKED_LIST_TYPE *FwEntryList  = NULL;
  BOOLEAN             SwitchBootGpt = FALSE;
  BOOLEAN             SwitchGppGpt  = FALSE;

  Status = FwGetFwEntryList(&FwEntryList);
  HANDLE_ERR_CONTINUE(Status,FwGetFwEntryList);

  // Check if GPT tables has been switched
  Status = GetAllSwitchGptRequestsFromFwEntryList(FwEntryList, &SwitchBootGpt, &SwitchGppGpt);
  HANDLE_ERROR_LABEL(Status,GetAllSwitchGptRequestsFromFwEntryList,StateFwEntryCommitUpdateFailureStartExit);

  Status = RestoreAllGPTTablesFromNV(PRIMARY_GPT_TABLE, SwitchBootGpt, SwitchGppGpt);
  HANDLE_ERR_CONTINUE(Status,RestoreAllGPTTablesFromNV);

  Status = RestoreAllGPTTablesFromNV(BACKUP_GPT_TABLE, SwitchBootGpt, SwitchGppGpt);
  HANDLE_ERR_CONTINUE(Status,RestoreAllGPTTablesFromNV);

  Status = SetUpdateState(FW_STATE_NOT_IN_PROGRESS);
  /*We want post rollback to continue if SetUpdateState failed*/
  HANDLE_ERR_CONTINUE(Status,SetUpdateState(FW_STATE_NOT_IN_PROGRESS));

  Status = SetAttemptCount(0);
  //We want to continue if SetAttemptCount failed.
  HANDLE_ERR_CONTINUE(Status,SetAttemptCount(0));

StateFwEntryCommitUpdateFailureStartExit:

  return Status;

}


/**
  The user Entry Point for Application. The user code starts with this function
  as the real entry point for the application.

  @param[out] MsftAttemptStatus Result values corresponding to MSFT definitions.
  @param[out] QcResultFlag      Result values corresponding to QCOM definitions

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
FwUpdatePhaseMain (
  OUT UINT32                   *MsftAttemptStatus,
  OUT QCFW_UPDATE_FLAG_VALUE   *QcResultFlag

  )
{
  EFI_STATUS                        Status      = EFI_SUCCESS;
  EFI_STATUS                        PhaseStatus = EFI_SUCCESS;
  UINT8                             AttemptCnt  = 0;
  QCOM_FW_UPDATE_STATE_VARIABLES    UpdateState = FW_STATE_NOT_IN_PROGRESS;
  BOOLEAN                           BootLunPartitionsUpdated = FALSE;

  if((MsftAttemptStatus == NULL) ||
     (QcResultFlag == NULL))
  {
    return EFI_INVALID_PARAMETER;
  }

  *MsftAttemptStatus = LAST_ATTEMPT_STATUS_ERROR_UNSUCCESSFUL;
  *QcResultFlag = QCFW_UPDATE_INIT;

  while (FWupdateMode != QCOM_FW_UPDATE_MODE_NOUPDATE)
  {
    Status = GetUpdateState(&UpdateState) ;
    if (EFI_ERROR(Status))
    {
      *QcResultFlag = QCFW_UPDATE_ERR_FLAG_GET_STAMACHINE_STATE;
      HANDLE_ERROR_LABEL(Status,GetUpdateState,FwUpdatePhaseMainExit);
    }

    Status = GetAttemptCount(&AttemptCnt);
    if (EFI_ERROR(Status))
    {
      AttemptCnt = 0;
    }

    /* If update is in progress then need to perform a roll-back to abort if too many attempts have been made.*/
    if ((AttemptCnt > UPDATE_ATTEMPT_COUNT_MAX) &&
        (UpdateState != FW_STATE_COMMIT_UPDATE_FAILURE))
    {
      *QcResultFlag = QCFW_UPDATE_ERR_FLAG_STATE_EXCEEDED_UPDATE_ATTEMPT_MAX;
      if (UpdateState == FW_STATE_PREPARE_UPDATE)
      {
        /*Rollback is not required, but need to record error as we are
        aborting the update after repeated attempt to complete backup phase */
        Status = EFI_DEVICE_ERROR;
        DEBUG_ERR_LABEL("\nAborting. Reached update attempt limit.\n",FwUpdatePhaseMainExit);
      }
      else
      {
        /*Needs to rollback all*/
        DEBUG((EFI_D_WARN,"\nAborting. Reached update attempt limit. Current update attempt count is %d\n\n", AttemptCnt));
        UpdateState = FW_STATE_ROLLBACK_START;
        Status = SetUpdateState(FW_STATE_ROLLBACK_START);
        HANDLE_ERROR_LABEL(Status,SetUpdateState(FW_STATE_ROLLBACK_START),FwUpdatePhaseMainExit);
      }
    }

    Status = GetTestHookData();
    if (EFI_ERROR(Status))
    {
      // Fill with default value so that no reset is
      // triggered when variable not found
      SetMem (&ResetPhaseData, sizeof (ResetPhaseData), NO_RESET_IN_CURRENT_PHASE);
      Status = EFI_SUCCESS;
    }

    switch (UpdateState)
    {
    case FW_STATE_PREPARE_UPDATE:
      DEBUG((EFI_D_WARN,"\n  Phase 1: FwEntry Prepare Update start. Time (ms): %lld\n\n", GetTimerCountms ()));
      SysFwUpdateProgress(PROGRESS_CAPSULE_RECOVERY_STATUSCHK_START);
      Status = StateFwEntryPrepareUpdateStart(MsftAttemptStatus,QcResultFlag);
      HANDLE_ERROR_LABEL(Status,StateFwEntryPrepareUpdateStart,FwUpdatePhaseMainExit);
      SysFwUpdateProgress(PROGRESS_CAPSULE_RECOVERY_STATUSCHK_END);
      DEBUG((EFI_D_WARN,"\n  Phase 1 Done. Time (ms): %lld\n", GetTimerCountms ()));
      break;

    case FW_STATE_BACKUP_START:
      DEBUG((EFI_D_WARN,"\n  Phase 2: FwEntry Backup start. Time (ms): %lld\n\n", GetTimerCountms ()));
      SysFwUpdateProgress(PROGRESS_CAPSULE_BACKUP_START);
      Status = StateFwEntryBackupStart(MsftAttemptStatus,QcResultFlag);
      HANDLE_ERROR_LABEL(Status,StateFwEntryBackupStart,FwUpdatePhaseMainExit);
      SysFwUpdateProgress(PROGRESS_CAPSULE_BACKUP_END);
      DEBUG((EFI_D_WARN,"\n  Phase 2 Done. Time (ms): %lld\n", GetTimerCountms ()));
      break;

    case FW_STATE_UPDATE_START:
      DEBUG((EFI_D_WARN,"\n  Phase 3: FwEntry Update start. Time (ms): %lld\n\n", GetTimerCountms ()));
      SysFwUpdateProgress(PROGRESS_CAPSULE_UPDATE_START);
      Status = StateFwEntryUpdateStart(MsftAttemptStatus,QcResultFlag,&BootLunPartitionsUpdated);
      HANDLE_ERR_CONTINUE(Status,StateFwEntryUpdateStart);
      if (EFI_ERROR(Status))
      {
        HANDLE_ERROR_LABEL(SetUpdateState(FW_STATE_ROLLBACK_START),SetUpdateState(FW_STATE_ROLLBACK_START),FwUpdatePhaseMainExit);
      }
      SysFwUpdateProgress(PROGRESS_CAPSULE_UPDATE_END);
      DEBUG((EFI_D_WARN,"\n  Phase 3 Done. Time (ms): %lld\n", GetTimerCountms ()));
      break;

    case FW_STATE_SYNC_START:
      DEBUG((EFI_D_WARN,"\n  Phase 4: FwEntry Sync start. Time (ms): %lld\n\n", GetTimerCountms ()));
      SysFwUpdateProgress(PROGRESS_CAPSULE_SYNC_START);
      Status = StateFwEntrySyncStart(MsftAttemptStatus,QcResultFlag,BootLunPartitionsUpdated);
      SysFwUpdateProgress(PROGRESS_CAPSULE_SYNC_END);
      DEBUG((EFI_D_WARN,"\n  Phase 4 Done. Time (ms): %lld\n", GetTimerCountms ()));
      if (EFI_ERROR(Status))
      {
        // Ignore the sync failure as secondary partitions are already updated.
        Status = EFI_SUCCESS;
        DEBUG((EFI_D_WARN,"\n  Skipping Phase 5 as sync operation failed for one or more partitions.\n"));
        goto FwUpdatePhaseMainExit;
      }
      break;

    case FW_STATE_ROLLBACK_START:
      DEBUG((EFI_D_WARN,"\n  Error Phase 1: FwEntry rollback start. Time (ms): %lld\n\n", GetTimerCountms ()));
      Status = StateFwEntryRollbackAllStart();
      if (EFI_ERROR(Status))
      {
        HANDLE_ERROR_LABEL(SetUpdateState(FW_STATE_COMMIT_UPDATE_FAILURE),SetUpdateState(FW_STATE_COMMIT_UPDATE_FAILURE),FwUpdatePhaseMainExit);
      }
      DEBUG((EFI_D_WARN,"\n  Error Phase 1 Done. Time (ms): %lld\n", GetTimerCountms ()));
      break;

    case FW_STATE_COMMIT_UPDATE:
      DEBUG((EFI_D_WARN,"\n  Phase 5: FwEntry Commit update start. Time (ms): %lld\n\n", GetTimerCountms ()));
      SysFwUpdateProgress(PROGRESS_CAPSULE_COMMIT_UPDATE_START);
      Status = StateFwEntryCommitUpdateStart(MsftAttemptStatus,QcResultFlag);
      // GPT reverse swap failure. Log the error and continue.
      HANDLE_ERR_CONTINUE(Status,StateFwEntryCommitUpdateStart);
      if (EFI_ERROR(Status))
      {
        Status =  EFI_SUCCESS;
      }
      SysFwUpdateProgress(PROGRESS_CAPSULE_COMMIT_UPDATE_END);
      DEBUG((EFI_D_WARN,"\n  Phase 5 Done. Time (ms): %lld\n", GetTimerCountms ()));
      goto FwUpdatePhaseMainExit;

    case FW_STATE_COMMIT_UPDATE_FAILURE:
      DEBUG((
        EFI_D_WARN,
        "\n  Error Phase 2: FwEntry Commit update failure start. Time (ms): %lld\n\n",
        GetTimerCountms ()
        ));
      // On an abnormal reset just after recording FW_STATE_ROLLBACK_START, the device will continue
      // with rollback stage. At this point, PhaseStatus will have EFI_SUCESS instead of the error code
      // from update phase. So if PhaseStatus is EFI_SUCCESS while entering the rollback state, 
      // update the error to a generic error code so that update status is reported as a failure.
      if (PhaseStatus == EFI_SUCCESS)
      {
          PhaseStatus = EFI_DEVICE_ERROR;
      }
      Status = StateFwEntryCommitUpdateFailureStart();
      HANDLE_ERROR_LABEL(Status,StateFwEntryCommitUpdateFailureStart,FwUpdatePhaseMainExit);
      DEBUG((EFI_D_WARN,"\n  Error Phase 2 Done. Time (ms): %lld\n", GetTimerCountms ()));
      goto FwUpdatePhaseMainExit;

    default:
      return EFI_LOAD_ERROR ;
    }
    // Preserve the first error encountered
    PhaseStatus = EFI_ERROR(PhaseStatus) ? PhaseStatus : Status;
  }

FwUpdatePhaseMainExit:
  
  return (EFI_ERROR(PhaseStatus) ? PhaseStatus : Status);
}

/**
 * The user Entry Point for FirmwareUpdate.
 *
 * @param Image              -Image to update
 * @param Image              -Size of the image to update
 * @param MsftAttemptStatus  -Microsoft last attempt status 
 * @param QcResultFlag       -QCFirmwareUpdate result flag
 * @param Progress           -cb function ptr to report the Progress of FW update.
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS
EFIAPI
RunFwUpdateMain (
  IN  CONST VOID                                   *Image,
  IN  UINTN                                         ImageSize,
  OUT UINT32                                       *MsftAttemptStatus,
  OUT QCFW_UPDATE_FLAG_VALUE                       *QcResultFlag,
  IN  EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS Progress            OPTIONAL
  )
{
  EFI_STATUS                 Status = EFI_SUCCESS;

  *MsftAttemptStatus  = LAST_ATTEMPT_STATUS_ERROR_UNSUCCESSFUL;
  *QcResultFlag       = QCFW_UPDATE_INIT;
  
  // Initilize the Progress function, if defined.
  if (Progress != NULL) {
    mProgressFuncSysFmp = Progress;
  }
  
  FWupdateMode       = QCOM_FW_UPDATE_MODE_NOUPDATE;

  // Print SysFwVersion info
  Status = QcomPrintSysFwVerPartitionData(EFI_D_WARN);
  HANDLE_ERR_CONTINUE(Status,RunFwUpdateMain:QcomPrintSysFwVerPartitionData);

  FWupdateMode = QCOM_FW_UPDATE_MODE_CAPSULE;

  Status = FwUpdateCapsulePhaseMain((VOID *)Image,ImageSize,MsftAttemptStatus,QcResultFlag);
  HANDLE_ERROR_LABEL(Status,FwUpdateCapsulePhaseMain,RunFwUpdateMainExit);

RunFwUpdateMainExit:

   return Status;
}

/**
 * Gets the firmware version from the metadata file contained in the capsule payload
 *
 * @param Image - Payload to parse
 * @param ImageSize - Payload size
 * @param PayloadHeaderV3 - Payload header structure (optional)
 * @param MsftAttemptStatus - The last attempt status, which will be recorded in ESRT
 * @param QcResultFlag - QCFirmwareUpdate result flag
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS
EFIAPI
ExtractSystemFirmwareMetaDataHeader (
  IN VOID                          *Image,
  IN UINTN                          ImageSize,
  OUT QPAYLOAD_METADATA_HEADER_V3  *PayloadHeaderV3,
  OUT UINT32                       *MsftAttemptStatus,
  OUT QCFW_UPDATE_FLAG_VALUE       *QcResultFlag
  )
{
  EFI_STATUS Status               = EFI_SUCCESS;
  UINT32     Version              = 0;
  UINTN      PayloadHeaderV3Size  = sizeof (QPAYLOAD_METADATA_HEADER_V3);

  if ((Image == NULL) ||
      (PayloadHeaderV3 == NULL) ||
      (MsftAttemptStatus == NULL) ||
      (QcResultFlag == NULL))
  {
      Status = EFI_INVALID_PARAMETER;
      goto ExtractSystemFirmwareMetaDataExit;
  }
  
  /* Find payload format version from MetaData */
  Status = FwFindMetadata(
    Image,
    ImageSize,
    &Version,
    PayloadHeaderV3,
    &PayloadHeaderV3Size,
    NULL,
    NULL,
    MsftAttemptStatus,
    QcResultFlag
    );
  HANDLE_ERROR_LABEL(Status,FwFindMetadata,ExtractSystemFirmwareMetaDataExit);

ExtractSystemFirmwareMetaDataExit:

  return Status;
}

/**
 *  Function will reset the respective test hook variable and
 *  reset the device. Input of CurrentPhaseResetEntry value shall 
 *  be with respective to CurrentPhase.
 *
 * @param[in] CurrentPhase                      Used to differentiate the phase.
 * @param[in] CurrentFwEntryCount               Current index value.
 * @param[in] TotalFwEntries                    Max Fw Entry value in Capsule payload
 */
VOID
ResetHookPhaseAndSystem (
   IN QCOM_TEST_HOOK_PHASE              CurrentPhase,
   IN UINTN                             CurrentFwEntryCount,
   IN UINTN                             TotalFwEntries
   )
{
  EFI_STATUS    Status = EFI_SUCCESS;
  BOOLEAN       ResetRequired = FALSE;
  BOOLEAN       ResetCurrentPhaseInNV = FALSE;
  UINTN          Index = 0;

  if (NO_RESET_IN_CURRENT_PHASE == ResetPhaseData[CurrentPhase]) {
    // Return as current phase is not configured to reset for
    // any firmware entry count
    goto Exit;
  }

  // Check if user have requested for a reset for a firmware
  // entry count that is larger than the maximum number of firmware
  // entries in the current payload. If yes, reset the setting and
  // skip the reset operation
  if (TotalFwEntries < ResetPhaseData[CurrentPhase]) {
    ResetCurrentPhaseInNV = TRUE;
    ResetRequired = FALSE;

    DEBUG((EFI_D_WARN, "   Reset skipped during %s, as the Fw entry count %d configured for reset, exceeds \n",SysFwUpdatePhaseNames[CurrentPhase], ResetPhaseData[CurrentPhase]));
    DEBUG((EFI_D_WARN, "   the maximum number of firmware enries in current payload %d \n", TotalFwEntries));
  }

  // Check if current firmware entry is the one recorded in
  // reset data. If yes, enable reset and enable clearing this
  // setting in NV
  if (CurrentFwEntryCount == ResetPhaseData[CurrentPhase]) {
    ResetCurrentPhaseInNV = TRUE;
    ResetRequired = TRUE;
  }

  if (ResetCurrentPhaseInNV) {
    ResetPhaseData[CurrentPhase] = NO_RESET_IN_CURRENT_PHASE;
    Status = gRT->SetVariable (
      RESET_PHASE_DATA_NV,
      &gQcomTokenSpaceGuid,
      EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
      sizeof(ResetPhaseData),
      &ResetPhaseData
      );

    if (EFI_ERROR (Status)) { 
     DEBUG((EFI_D_WARN,"\n  Failed to set NV variable data during %s\n", SysFwUpdatePhaseNames[CurrentPhase]));
      goto Exit;
    }

   FlushVariableServicesIfSupported();
 
  }

  if(ResetRequired) {
    DEBUG((EFI_D_WARN,"\n   Resetting the device during %s, at start of firmware entry count '%d'\n", SysFwUpdatePhaseNames[CurrentPhase], CurrentFwEntryCount));

    for (Index = 5; Index > 0; Index--) {
      Print(L"Resetting system in %d seconds ...\n", Index);
      DEBUG((DEBUG_INFO, "Resetting system in %d seconds ...\n", Index));
      gBS->Stall(1000000);
    }

    gRT->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
    
    CpuDeadLoop();
  }

Exit:
    return;
}

/*
 *  Function will set the ResetEntryIndexInXXXXX phase variables to NO_RESET_IN_CURRENT_PHASE.
 */
VOID
ResetHookEntryToDefault(VOID
  )
{
  EFI_STATUS            Status = EFI_SUCCESS;

  SetMem (&ResetPhaseData, sizeof (ResetPhaseData), NO_RESET_IN_CURRENT_PHASE);

  Status = gRT->SetVariable (
    RESET_PHASE_DATA_NV,
    &gQcomTokenSpaceGuid,
    EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
    sizeof(ResetPhaseData),
    &ResetPhaseData
    );
  if (EFI_ERROR (Status)) { 
    DEBUG((EFI_D_WARN,"\n  Failed to set ResetPhaseData NV variable\n"));
  }
}

/**
 *  Function is to get test hook variable details and fills in the
 *
 * @return EFI_STATUS
 */
EFI_STATUS
GetTestHookData(VOID
  )
{
  EFI_STATUS            Status = EFI_SUCCESS;
  UINTN                 ResetPhaseDataSize = 0;

  ResetPhaseDataSize = sizeof(ResetPhaseData);

  Status = gRT->GetVariable (
    RESET_PHASE_DATA_NV,
    &gQcomTokenSpaceGuid,
    NULL,
    &ResetPhaseDataSize,
    &ResetPhaseData
    );

  if ((EFI_ERROR (Status)) ||
    (ResetPhaseDataSize != sizeof (ResetPhaseData)))
  {
    // TODO: Update to INFO type after testing
    DEBUG((EFI_D_WARN,": Failed to get ResetPhase test hook data with error: %r\n", Status));
    goto Exit;
  }

Exit:
  return Status;
}

