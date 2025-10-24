/**---------------------------------------------------------------------------
 *   @file        usb4_platform_target.h
 *
 *   @brief   Header file for a full USB4 API
 *
 *   Copyright (c) 2018-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/
#ifndef __USB4_PLATFORM_TARGET_H__
#define __USB4_PLATFORM_TARGET_H__

#include "usb4_platform.h"
// #include "VVDRV_deo_mutex.h"

/*----------------------------------------------------------------------------
 * Defines
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Type Definitions
 *--------------------------------------------------------------------------*/
///////////////////////////////
///////////////////////////////
///////////////////////////////
// Platform Target Specific
///////////////////////////////
///////////////////////////////
///////////////////////////////

/**
 * @brief initialize platform clocks, populate interrupts, etc ...
 * @return 0 on success, other on failure
 */
int Usb4PlatformInit(usb4_platform_ctx_t* usb4_platform_ctx, UINT32 coreIndex);

/**
 * @brief Returns core index for the platform
 * @return core index value
 */
UINT32 Usb4PlatformGetCoreIndex(usb4_platform_ctx_t* usb4_platform_ctx);

/**
 * @brief Get platform specific address of HIA
 * @param[out] ppBase - Base address
 * @return 0 on success, other on failure
 */
int Usb4PlatformGetHIA_Base(usb4_platform_ctx_t* usb4_platform_ctx, UINT8** ppBase);

/**
 * @brief Get platform specific address of sideband
 * @param[out] ppBase - Base address
 * @return 0 on success, other on failure
 */
int Usb4PlatformGetCore_Base(usb4_platform_ctx_t* usb4_platform_ctx, UINT8** ppBase);

/**
 * @brief Store platform specific data thwa needs to persist though sleep;
 * Platform specific implementation is not mandatory
 * @return 0 on success, other on failure
 */
int Usb4PlatformStorePersistentData(usb4_platform_ctx_t* usb4_platform_ctx);

/**
 * @brief Write back platform specific data that needs to persist though sleep;
 * Platform specific implementation is not mandatory
 * @return 0 on success, other on failure
 */
int Usb4PlatformWriteBackPersistentData(usb4_platform_ctx_t* usb4_platform_ctx);

/**
 * @brief Perform GCC, PHY and other actions needed to put platform to sleep
 * Platform specific implementation is not mandatory
 * @return 0 on success, other on failure
 */
int Usb4PlatformPutPlatformToSleep(usb4_platform_ctx_t* usb4_platform_ctx);

/**
 * @brief Check if cable is connected prior to going to sleep. This impacts
 *        side-band override configuration Platform specific implementation 
 *        is not mandatory
 * @return 0 on success, other on failure
 */
int Usb4PlatformGetCablePluggedStatus(usb4_platform_ctx_t* usb4_platform_ctx);

/**
 * @brief Perform GCC, PHY and other actions needed to wake platform from 
 *        sleep Platform specific implementation is not mandatory
 * @return 0 on success, other on failure
 */
int Usb4PlatformWakePlatformFromSleep(usb4_platform_ctx_t* usb4_platform_ctx);

/**
 * @brief Configure side band overrides as needed
 * @return 0 on success, other on failure
 */
int Usb4PlatformPlatformPreReset(usb4_platform_ctx_t* usb4_platform_ctx);

/**
 * @brief Configure side band overrides as needed
 * @return 0 on success, other on failure
 */
int Usb4PlatformPlatformPostReset(usb4_platform_ctx_t* usb4_platform_ctx);

/**
 * @brief Target specific Tlmm initialization for GPIO
 * @return 0 on success, other on failure
 */
int Usb4PlatformInitTlmm(usb4_platform_ctx_t* usb4_platform_ctx);

/**
* @brief Configure side band orientation
* @param [in] bFlipped - Normal or flipped cable orientation (external muxes configuration)
* @return 0 on success, other on failure
*/
int Usb4PlatformSideBandSetOrientation(usb4_platform_ctx_t* usb4_platform_ctx, boolean bFlipped);

/**
 * @brief Configure side band mode and orientation
 * @param [in] bSwap - Normal or Swapped cable orientation (external muxes configuration)
 * @return 0 on success, other on failure
 */
int Usb4PlatformSideBandConfigure(usb4_platform_ctx_t* usb4_platform_ctx, BOOLEAN bSwap);

/**
 * @brief HW control SBRX required
 * @param [in] gpioCtrl see #USB4_platform_sb_ctrl for additional details
 * @return 0 on success, other on failure
 */
int Usb4PlatformSideBandRxControl(usb4_platform_ctx_t* usb4_platform_ctx, USB4_platform_sb_ctrl gpioCtrl);

/**
 * @brief SB GPIO configuration
 * @param [in] gpioCtrl see #USB4_platform_sb_ctrl for additional details
 * @return 0 on success, other on failure
 */
int Usb4PlatformSideBandTxControl(usb4_platform_ctx_t* usb4_platform_ctx, USB4_platform_sb_ctrl gpioCtrl);

/**
 * @brief Override TX Enable in proprietary SB register
 * @param [in] overrideValue - 1 for Enable or 0 - Disable
 * @return 0 on success, other on failure
 */
int Usb4PlatformOverrideSbTxEnable(usb4_platform_ctx_t* usb4_platform_ctx, UINT32 overrideValue);

/**
 * @brief Update TDISCONNECTRX value
 * @param [in] overrideValue - new value
 * @return 0 on success, other on failure
 */
int Usb4PlatformOverrideSbTDisconnectRx(usb4_platform_ctx_t* usb4_platform_ctx, UINT32 overrideValue, UINT32* pPrevValue);

/**
 * @brief Lock mutex; This is not try lock. Failure means mutex is not valid/
 * @return 0 on success, other on failure
 */
int Usb4PlatformLockMutex(usb4_platform_ctx_t* usb4_platform_ctx);

/**
 * @brief UnLock mutex; This is not try lock. Failure means mutex is not valid/
 * @return 0 on success, other on failure
 */
int Usb4PlatformUnlockMutex(usb4_platform_ctx_t* usb4_platform_ctx);



///////////////////////////////
///////////////////////////////
///////////////////////////////
// Msg Ring
///////////////////////////////
///////////////////////////////
///////////////////////////////
/**
 * @brief initialize the class buffers 0 to all counters etc..
 * @param [in] max_entries - max number of entries that the msg ring will store
 * @param [in] entrySize_bytes - size in bytes of each entry
 * @return 0 on success other on failure
 */
int Usb4PlatformUcMsgRingInit(usb4_platform_uC_target_MsgRing_ctx_t* usb4_platform_uC_target_MsgRing_ctx, UINT32 max_entries, UINT32 entrySize_bytes);

/**
 * @brief Destroy the ring and dealocate the buffers
 */
void Usb4PlatformUcMsgRingDestroy(usb4_platform_uC_target_MsgRing_ctx_t* usb4_platform_uC_target_MsgRing_ctx);

/**
 * @brief initialize the class buffers 0 to all counters etc..
 * @param [in] pmsg pointer to the element to push
 * @return 0 on success other on failure
 */
int Usb4PlatformUcMsgRingPush(usb4_platform_uC_target_MsgRing_ctx_t* usb4_platform_uC_target_MsgRing_ctx, UINT8* pMsg);

/**
 * @brief Getter for number of messages in the ring
 * @param [out] pNum number of messages, valid on success
 * @return 0 on success other on failure
 */
int Usb4PlatformUcMsgRingGetNumMsgs(usb4_platform_uC_target_MsgRing_ctx_t* usb4_platform_uC_target_MsgRing_ctx, UINT32* pNum);

/**
 * @brief Getter for entry size
 * @param [out] pSizeBytes size in bytes of every entry
 * @return 0 on success other on failure
 */
int Usb4PlatformUcMsgRingGetEntrySize(usb4_platform_uC_target_MsgRing_ctx_t* usb4_platform_uC_target_MsgRing_ctx, UINT32* pSizeBytes);

/**
 * @brief prints messages recieved after last print
 * @param[in] coreIndex - Core index the message was generated on
 * @return 0 on success other on failure
 */
int Usb4PlatformUcMsgRingPrintMsgs(usb4_platform_uC_target_MsgRing_ctx_t* usb4_platform_uC_target_MsgRing_ctx, UINT32 coreIndex);

/**
 * @brief return a message from the massage ring
 * massage will not be able to retrive once again
 * @return 0 on success other on failure
 */
int Usb4PlatformUcMsgRingPop(usb4_platform_uC_target_MsgRing_ctx_t* usb4_platform_uC_target_MsgRing_ctx, UINT8* pMsg);

/**
 * @brief return a message from the massage ring
 * massage will be able to retrive once again
 * @return 0 on success other on failure
 */
int Usb4PlatformUcMsgRingPeek(usb4_platform_uC_target_MsgRing_ctx_t* usb4_platform_uC_target_MsgRing_ctx, UINT8* pMsg);




#if 0 // Absorbed by base class
class VVHAL_usb4_platform_uC_target : public VVHAL_usb4_platform_uC
{
public:

    /**
     * @brief Load the FW to uC
     * @return 0 on success, other on failure
     */
    virtual int LoadFW();

    /**
     * @brief Set Go bit for uC
     * @return 0 on success, other on failure
     */
    virtual int ActivateUc();

    /**
     * @brief Clear GO bit for uC
     * @return 0 on success, other on failure
     */
    virtual int DeActivateUc();

    /** @override */ //TODO add documentation
    virtual int Ioctl(usb4_uc_ioctl_t* action);

    /**
     * @brief handler for UC events
     */
    virtual void HandleUcEvents();

    /**
     * @brief prints uc msgs received since last print
     * @return num of msgs printed
     */
    virtual int PrintUcMsgs();

    /**
     * @brief gets the last uc test results, and number of results since
     *        last call
     * @param [out] pLastRes output last result, valid if *pNum >= 1
     * @param [out] pLastTestNum test number of the last test, valid if *pNum >= 1
     * @param [out] pNum will hold number of results
     * @return 0 on success, other on failure
     */
    virtual int GetTestResult(UINT32* pLastRes, UINT32* pLastTestNum, UINT32* pNum);

    /**
     * @brief gets the last uc error, and number of errors since
     *        last call
     * @param [out] pLastErr output last result, valid if *pNum >= 1
     * @param [out] pProgramCounter output last PC, valid if *pNum >= 1
     * @param [out] pNum will hold number of results
     * @return 0 on success, other on failure
     */
    virtual int GetPropreitryError(UINT32* pLastErr, UINT32* pProgramCounter, UINT32* pNum);

    /**
    * @brief gets number of sleep done events since uC was activated
    *        last call
    * @param [out] pNum will hold number of results
    * @return 0 on success, other on failure
    */
    virtual int GetSleepDoneCounter(UINT32* pNumSleepDone);

    /**
     * @brief returns a uc msg (after pop the msg cannot be retrieve)
     * @param [out] buff to hold the returned massage
     * @return 0 on success, other on failure
     */
    virtual int PopUcMsg(UINT8* buff);


    /**
     * @brief returns a uc msg (after peek the msg is still in here place)
     * @param [out] buff to hold the returned massage
     * @return 0 on success, other on failure
     */
    virtual int PeekUcMsg(UINT8* buff);


    /**
     * @brief returns the number of massages in the ring
     * @param [out] pNum to hold the returned number
     * @return 0 on success, other on failure
     */
    virtual int GetNumUcMsgs(UINT32* pNum);

	/**
	 * @brief returns the Entry size in bytes
	 * @param [out] pSizeBytes to hold the returned number
	 * @return 0 on success, other on failure
	 */
	int GetUCEntrySizeBaytes(UINT32* pSizeBytes);


private:

    /**
     * @brief masks the interrupts acording to bMask
     * @param [in] bMask true = disable irq false = enable irq
     * @return 0 on success, other on failure
     */
    int MaskIrq(BOOLEAN bMask);

};
#endif // Absorbed by base class


/**
 * @brief Target specific platform class.
 *        Keeps target specific platform information
 */


/*----------------------------------------------------------------------------
 * Enumerations Definitions
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Function Declarations
 *--------------------------------------------------------------------------*/


#endif //__USB4_PLATFORM_TARGET_H__
