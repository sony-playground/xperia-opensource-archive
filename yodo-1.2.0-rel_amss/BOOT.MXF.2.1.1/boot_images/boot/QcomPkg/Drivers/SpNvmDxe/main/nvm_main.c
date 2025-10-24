/**
 @file  nvm_main.c
 */
/*=============================================================================
 Copyright (c) 2020 - 2021 Qualcomm Technologies, Incorporated.
 All rights reserved.
 Qualcomm Technologies, Confidential and Proprietary.
 =============================================================================*/

/*=============================================================================
 EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 07/29/21   vp      Logging improvements
 05/19/21   vp      Poll for commit from sTPM, only on create partition
 04/19/21   av      Open sTPM nvm channel only if TPM type is sTPM
 02/16/21   vp      support polling SegDb commit post App partition commit
 03/09/20   ll      initial release
=============================================================================*/
#include <Uefi.h>
#include "QcomLib.h"//#include <Library/QcomLib.h>
#include <PrintShLib.h>
#include <string.h>		// memset()
#include "stringl/stringl.h"  // strnlen()

#include "osCommon.h"  
#include "SecNvmDefs.h"
#include "SecNvmManager.h"

#include <stdio.h>

//Test
#include <Protocol/EFISpcom.h>
EFI_SPCOM_PROTOCOL * SpcomProtocol;

#define SKP_APP_NAME "sp_nvm"

//class descriptor for SecNvmManager
static const struct Class _SecNvmManager = {
      sizeof(struct SecNvmManager),
      SecNvmManager_ctor, 
      SecNvmManager_dtor
};
/** 
 * init SecNvmMemManager 
 * Start Routine for each NVM applications
 */ 
EFI_STATUS nvm_main(const char* appNames[], int apps_num)
{
    EFI_STATUS ret = EFI_SUCCESS;

    LOGI("++++  START NVM Dxe +++++");
    LOGI("NVM Dxe start, apps num [%d]\n", apps_num);

    if (apps_num > 2) {
      //Currently only supports max 2 channels/apps for UEFI
      return EFI_INVALID_PARAMETER;
    }
    // allocate application amount of secnvm manager
    struct SecNvmManager * secNvmManagers_ptr[apps_num];

    for (int i = 0; i < apps_num; i++) {
        LOGI("appNames[%d]: %a \n",  i, appNames[i]);
        secNvmManagers_ptr[i] = new((const void *)&_SecNvmManager, appNames[i]);

        ret = secNvmManagers_ptr[i]->startSpcomServer(secNvmManagers_ptr[i]);
        if (ret != EFI_SUCCESS)
        {
            LOGE("startSpcomServer returns Error:[%d]\n", ret);
            return ret;
        }

        while (secNvmManagers_ptr[i]->m_state != SEC_NVM_INIT_DONE_STATE){
            /* Even tho it's called receive requests, it will only call get request once for UEFI NVMDxe
            This is taken from HLOS multi-thread version. This is due to UEFI NvmDxe is using single
            thread with callback. This will only called for SKP NVM initialization*/
            ret = secNvmManagers_ptr[i]->receiveRequests(secNvmManagers_ptr[i]);
            if (ret != EFI_SUCCESS) {
                LOGE("receiveRequests returns Error:[%d]. Stop further get requests \n", ret);
                break;
            }
			/* Each App Partition commit is followed by SegDb commit.
			 *
			 * As part of create, app partition receives a commit, secnvm moves to SEC_NVM_CREATE_DONE_STATE.
			 * To supplement the app commit, commit on segdb will be received, so need to polled for.
			 *
			 * stpm_lite does a commit on init on the very first boot, secnvm moves to SEC_NVM_INIT_DONE_STATE.
			 * To supplement this app commit, commit on segdb will be received, so need to polled for.
			 */
			if (i == 1) {
				if (secNvmManagers_ptr[i]->m_state == SEC_NVM_CREATE_DONE_STATE ||
						secNvmManagers_ptr[i]->m_state == SEC_NVM_INIT_DONE_STATE){
					ret = secNvmManagers_ptr[0]->receiveRequests(secNvmManagers_ptr[0]);
					if (ret != EFI_SUCCESS) {
						LOGE("Error:[%d] received for seg_db commit, post app partition commit %d.\n", ret);
						break;
					}
				/*
				 * stpm_lite does not do a commit on subsequent boots, it just opens partition and moves on.
				 * So, to avoid polling further, we exit on receiving open partition request from stpm_lite.
				 *
				 */
				} else if (secNvmManagers_ptr[i]->m_state == SEC_NVM_OPEN_STATE) {
					break;
				}
			}
		}
	}
    return ret;
}
