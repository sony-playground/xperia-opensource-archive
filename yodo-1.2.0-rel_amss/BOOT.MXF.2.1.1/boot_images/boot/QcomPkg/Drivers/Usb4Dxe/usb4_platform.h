/**
 * @file usb4_platform.h
 *
 * @brief USB4_COMDEF types
 *
 * Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 */
#ifndef __USB4_PLATFORM_H__
#define __USB4_PLATFORM_H__

/*----------------------------------------------------------------------------
 * Include Files
 *-------------------------------------------------------------------------*/

#include <Uefi.h>
#include <Library/IoLib.h>
// #include <Library/DebugLib.h>
// #include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
// #include <Library/UefiRuntimeServicesTableLib.h>
// #include <Protocol/EFIUsb4Config.h>
#include <Protocol/EFIClock.h>
#include <Protocol/EFIHWIO.h>
#include <Protocol/EFITlmm.h>
#include <Protocol/EFIHALIOMMUProtocol.h>

// #include "VVDRV_deo_interrupt.h"
// #include "VVDRV_usb4_pd_api.h"
#include "usb4_dp_aux.h"
#include "usb4_platform_ahb_access.h"
#include "usb4_platform_defs.h"

/*----------------------------------------------------------------------------
 * Defines
 *-------------------------------------------------------------------------*/
/**
 *@brief USB4 Interrupts enum.
 *@note  Do not change enumerator values! Add new interrupts at the end (before VVDRV_USB4_INT_COUNT)
 */
typedef enum
{
    // 0 : usb4_pcie_ap_int
    // 1 : usb4_clx_exit_int
    // 2 : usb4_wake_sleep_int
    // 3 : usb4_uc_int
    // 4 : usb4_hia_int_ring_data
    // 5 : usb4_hia_int_ring_ctrl
    // 6 : usb4_dp_ap_int
    // 7 : emu PDPHY irq
    USB4_intType_UNUSED_INT_SOURCE   = -1,
    USB4_intType_PCIE_AP             =  0,
    USB4_intType_CLX_EXIT            =  1,
    USB4_intType_WAKE_SLEEP          =  2,
    USB4_intType_UC_INT              =  3,
    USB4_intType_HIA_RINGS           =  4,
    USB4_intType_DP_AP               =  6,
    USB4_intType_PD_CONNECT          =  7,
    USB4_intType_COUNT               =  8,  /**< Total interrupt count */
    
} USB4_intType;

typedef enum
{
    USB4_platform_sb_ctrl_sw_pulldown,
    USB4_platform_sb_ctrl_sw_pullup,
    USB4_platform_sb_ctrl_sw_nopull, /* asic: highz, rumi/ge: pull down */
    USB4_platform_sb_ctrl_hw_ctrl,
} USB4_platform_sb_ctrl;

///////////////////////////////
///////////////////////////////
///////////////////////////////
// Msg Ring
///////////////////////////////
///////////////////////////////
///////////////////////////////
typedef struct
{
    UINT8* m_pBuff;
    UINT32 m_size_bytes;
    UINT32 m_entrySizeBytes;
    UINT32 m_maxEntries;
    UINT32 m_printIdx;
    UINT32 m_pushIdx;
    UINT32 m_numMsgs;
} usb4_platform_uC_target_MsgRing_ctx_t;


///////////////////////////////
///////////////////////////////
///////////////////////////////
// Platform Interrupt
///////////////////////////////
///////////////////////////////
///////////////////////////////

/**
*@brief     Pointer to Interrupt Handler
*/
typedef void(*pIntHandler)(UINT32 intSource, void* userData);

/**
 * @brief Interrupt description class.
 */
typedef struct
{
    USB4_intType intType;           /**< USB4 interrupt type */
    // deo_interrupt_t deo_interrupt;  // IRQ details // TODO: AC port to UEFI
} USB4_intDesc;


typedef struct
{
    /** @brief target specific interupt vectors table */
    USB4_intDesc* m_interrupt_vectors;

    /** @brief number of vectors in #m_interrupt_vectors */
    UINT32 m_interrupt_vectors_size;
} usb4_platform_interrupts_ctx_t;


void Usb4PlatformInterruptsInit(usb4_platform_interrupts_ctx_t* usb4_platform_interrupts_ctx);
void Usb4PlatformInterruptsDeInit(usb4_platform_interrupts_ctx_t* usb4_platform_interrupts_ctx); // In place of destructor


/**
 * @brief Get interrupt descriptor according to the interrupt source which
 *        is platform specific. May be used to identify the interrupt type
 *        in terms of USB4
 * @param [in] intSource interrupt source
 * @return pointer to USB4_intDesc
 */
USB4_intDesc* Usb4PlatformInterruptsGetIntDescFromIntSource(usb4_platform_interrupts_ctx_t* usb4_platform_interrupts_ctx, UINT32 intSource);

/**
 * @brief Get interrupt descriptor according to the interrupt type which
 *        is platform specific. May be used to identify the interrupt source
 *        in terms of USB4
 * @param [in] intType interrupt type see #USB4_intType
 * @return pointer to #USB4_intDesc or NULL if not found
 */
USB4_intDesc* Usb4PlatformInterruptsGetIntDescFromIntType(usb4_platform_interrupts_ctx_t* usb4_platform_interrupts_ctx, USB4_intType intType);

/**
 * @brief Attach ISRs and configure #driverContext as userData
 * @param [in] userData #driverContext which is passed to isr
 * @return 0 on success, other on failure
 */
int Usb4PlatformInterruptsAttachInterrupts(usb4_platform_interrupts_ctx_t* usb4_platform_interrupts_ctx, void* userData);

/**
 * @brief Detach all attached interrupts.
 * @return 0 on success, other on failure
 */
int Usb4PlatformInterruptsDetachInterrupts(usb4_platform_interrupts_ctx_t* usb4_platform_interrupts_ctx); // Destructor

/**
 * @brief Attach ISR and configure #driverContext as userData
 * @param [in] intType interrupt type see #USB4_intType
 * @return 0 on success, other on failure
 */
int Usb4PlatformInterruptsAttachInterrupt(usb4_platform_interrupts_ctx_t* usb4_platform_interrupts_ctx, USB4_intType intType, void* userData);

/**
 * @brief Detach ISR
 * @param [in] intType interrupt type see #USB4_intType
 * @return 0 on success, other on failure
 */
int Usb4PlatformInterruptsDetachInterrupt(usb4_platform_interrupts_ctx_t* usb4_platform_interrupts_ctx, USB4_intType intType);


typedef enum
{
    USB4_DpPll_Config_Disable,
    USB4_DpPll_Config_8p1,
    USB4_DpPll_Config_5p4,
    USB4_DpPll_Config_2p7,
    USB4_DpPll_Config_1p62
} USB4_DpPll_Config;

typedef struct
{
    BOOLEAN bSscEnabled;
    BOOLEAN bUseDiffClock;/* Default FALSE */
    BOOLEAN pipeClockDisableInC3IndependentOfPowerdown;/* Default FALSE */
    BOOLEAN useLinearRedriverCableOptimizedPreset;/* Default FALSE */
    BOOLEAN bIsUsb4Device;
    UINT32 numLanes;
    USB4_DpPll_Config dpPllCfg;
} USB4_phyConfig;

typedef struct
{
    UINT8 L0_PRE_DEBUG_BUS_IDX10;
    UINT8 L1_PRE_DEBUG_BUS_IDX10;
    UINT8 L0_PRE_DEBUG_BUS_IDX32;
    UINT8 L1_PRE_DEBUG_BUS_IDX32;
    UINT8 DEBUG_BUS_IDX0;
    UINT8 DEBUG_BUS_IDX1;
    UINT8 DEBUG_BUS_IDX2;
    UINT8 DEBUG_BUS_IDX3;
    UINT8 PLL_DEBUG_BUS_SEL;
    UINT8 TXA_DEBUG_BUS_SEL;
    UINT8 TXB_DEBUG_BUS_SEL;
} USB4_phyDebugBusConfig;

typedef struct
{
    UINT8 debug_bus_0_status;
    UINT8 debug_bus_1_status;
    UINT8 debug_bus_2_status;
    UINT8 debug_bus_3_status;
} USB4_phyDebugBusStatus;

typedef struct
{
    UINT8 PCS_TC3_DEBUG_CLK_MUX_SEL;
    UINT8 PLL_CLK_DEBUG_SEL;
    UINT8 TXA_CLK_DEBUG_SEL;
    UINT8 TXB_CLK_DEBUG_SEL;
    UINT8 CLK_MUX_CTRL_DEBUG_CLK_SEL;
    UINT8 DEBUG_CLK_DIV_SEL;
    UINT8 CLK_MUX_CTRL_DEBUG_CLK_DIV;
} USB4_phyDebugClockConfig;

typedef struct
{
    UINT32 hor;
    UINT32 vert;
    UINT32 maxh;// = 0x40;
    UINT32 maxv;// = 0x80;
} USB4_eyeMonitorungConfigure;

typedef struct
{
    UINT32 rxa_errors;
    UINT32 rxb_errors;
} USB4_eyeMonitorungStatus;



///////////////////////////////
///////////////////////////////
///////////////////////////////
// Platform CIO PHY
///////////////////////////////
///////////////////////////////
///////////////////////////////
typedef struct
{
    // Common CIO PHY data structures
    UINT8* m_coreBaseAddress;
    UINT32 m_coreIndex;

    // CIO PHY target data structures
    UINT8* m_phyBaseAddress;

    // CIO PHY emulation data structures
    UINT32 m_numLanes; 
    UINT32 m_isUsb4Device; 
} usb4_platform_cio_phy_ctx_t;

// ASIC PHY
int Usb4PlatformCioPhyInit(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx, UINT32 coreIndex, UINT8* coreBaseAddress);
int Usb4PlatformCioPhyAssertReset(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx);
int Usb4PlatformCioPhyDeAssertReset(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx);
int Usb4PlatformCioPhyConfigure(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx, USB4_phyConfig* pPhyConfig);
int Usb4PlatformCioPhyStart(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx, USB4_phyConfig* pPhyConfig);
int Usb4PlatformCioPhyPowerDown(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx);
int Usb4PlatformCioPhyInitEyeMonitoring(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx, UINT32 initStage);
int Usb4PlatformCioPhyStartEyeMonitoring(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx, USB4_eyeMonitorungConfigure* pEyeMonitorungConfigure);
int Usb4PlatformCioPhyGetEyeMonitoringStatus(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx, USB4_eyeMonitorungStatus* pEyeMonitorungStatus);
int Usb4PlatformCioPhyConfigureREFGEEN(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx, BOOLEAN bEnable);
int Usb4PlatformCioPhyConfigureDPPLL(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx, USB4_phyConfig* pPhyConfig);
int Usb4PlatformCioPhyConfigureDebugBus(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx, USB4_phyDebugBusConfig* pDebugBusConfig);
int Usb4PlatformCioPhyConfigureDebugClk(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx, USB4_phyDebugClockConfig* pDebugClkConfig);
int Usb4PlatformCioPhyReadDebugBus(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx, USB4_phyDebugBusStatus* pDebugBusStatus);

// Emulation PHY
int Usb4PlatformCioEmulationPhyInit(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx, UINT32 coreIndex, UINT8* coreBaseAddress);
int Usb4PlatformCioEmulationPhyAssertReset(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx);
int Usb4PlatformCioEmulationPhyDeAssertReset(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx);
int Usb4PlatformCioEmulationPhyConfigure(usb4_platform_cio_phy_ctx_t* usb4_platform_cio_phy_ctx, USB4_phyConfig* pPhyConfig);


/*---------------------------------------------------------------------------*/
typedef enum
{
    USB4_uc_ioctl_cmd_BEGIN_HSE=0x1,
    USB4_uc_ioctl_cmd_ENABLE_PHY_PRESETS=0x2,
    USB4_uc_ioctl_cmd_LIMIT_VERBOSITY=0x3,
    USB4_uc_ioctl_cmd_COMPLETE_SLEEP=0x4,
    USB4_uc_ioctl_cmd_WAKE=0x5,
    USB4_uc_ioctl_cmd_PHYSICAL_DISCONNECT=0x6,
    USB4_uc_ioctl_cmd_START_TEST=0x81,
    USB4_uc_ioctl_cmd_STOP_TEST=0x82,
    USB4_uc_ioctl_cmd_INVALID=0x92,
} USB4_uc_ioctl_cmd;

//0 – device
//1 – cable disconnected
//2 – cable connected
//3 – system wake
typedef enum
{
    USB4_uc_wake_reason_DEVICE=0x0,
    USB4_uc_wake_reason_CABLE_DISCONNECT=0x1,
    USB4_uc_wake_reason_CABLE_CONNECT=0x2,
    USB4_uc_wake_reason_SYSTEM_WAKE=0x3,
    USB4_uc_wake_reason_UNDEFINED=0xf
} USB4_uc_wake_reason;

typedef enum
{
    USB4_uc_test_SB_EXCHANGE=0,
    USB4_uc_test_ENTER_LOOPBACK_MODE=1,
    USB4_uc_test_GENERATE_ERRORS=2,
    USB4_uc_test_SOME_TEST_TO_FAIL=5, /* I see it fails */
    USB4_uc_test_NOT_VALID_TEST=16,
} USB4_uc_test;

#pragma pack(push)
#pragma pack(1)

typedef union {
    struct {
        UINT32 cmd              : 8;
        UINT32 device_type      : 1;  /* 0x1 USB4, 0x0 TBT3 */
        UINT32 cc_orientation   : 1;  /* 0x0 CC1, 0x1 CC2 (flipped) */
        UINT32 reserved_0       : 1;
        UINT32 cable_type       : 2;  /* 0x0 passive, 0x1 usb4 active, 0x3 tbt3 active*/
        UINT32 cable_gen        : 1;  /* 0x0 gen2, 0x1 gen3 */
        UINT32 polarity_l0tx    : 1;
        UINT32 polarity_l0rx    : 1;
        UINT32 polarity_l1tx    : 1;
        UINT32 polarity_l1rx    : 1;
        UINT32 reserved_1       : 14;
    } beginHSE;
    struct {
        UINT32 cmd:8;
        UINT32 presetBits:16;
        UINT32 reserved:8;
    }enablePhyPresets;
    struct {
        UINT32 cmd:8;
        UINT32 minimumSeverityToOutput:8;
        UINT32 reserved:16;
    }limitVerbosity;
    struct {
        UINT32 cmd:8;
        UINT32 reserved:24;
    }completeSleep;
    struct {
        UINT32 cmd:8;
        UINT32 wakeUpReason:8;
        UINT32 reserved:16;
    }wake;
    struct {
        UINT32 cmd:8;
        UINT32 reserved:24;
    }physicalDisconnect;
    struct {
        UINT32 cmd:8;
        UINT32 testIndex:8;
        UINT32 testParams:16;
    }startTest;
    UINT32 raw;
} usb4_uc_ioctl_t;

//typedef union usb4_uc_ioctl_t
//{
//    UINT32 raw;
//    UC_SW_OPCODES opCode;
//    struct
//    {
//        UINT8 __;
//        USB4_PARAMS linkParams;
//    } beginHse;
//    struct
//    {
//        UINT16 __ : 8;
//        UINT16 bitmap : 16;
//    } setPresetEn;
//    struct
//    {
//        UINT8 __;
//        WAKE_REASON reason : 8;
//    } wake;
//    struct
//    {
//        UINT8 __;
//        UINT8 testIndex;
//        UINT16 testParams;
//    } runTest;
//} UC_SW_CMD;

#pragma pack(pop)

/*---------------------------------------------------------------------------*/
///////////////////////////////
///////////////////////////////
///////////////////////////////
// Platform uC
///////////////////////////////
///////////////////////////////
///////////////////////////////
typedef struct
{
  // ++++ Base Class
  // ---- Base Class


  // ++++ Absorb target specific private data structures
    /** @brief stores the core base address */
    UINT8*  m_coreBaseAddress;

    /** @brief Next PTR address in the ring for reading the addr during
               ISR handling of the ring, read from the uC Ring AHB  */
    UINT32* m_pNextPtrAddr;

    /** @brief Number of fresh entries in the ring added since the last ISR status was cleared */
    UINT32* m_pNumOfNewEntries;

    /** @brief core index */
    UINT32 m_coreIdx;
    
    /** @brief Number of ring entries, read from the uC Ring AHB */
    UINT32 m_numEntries;

    /** @brief Entry size in bytes, read from the uC Ring AHB */
    UINT32 m_entrySize_bytes;

    /** @brief The base address of events/entries, read from the uC Ring AHB */
    UINT8* m_pEventsAddr;

    /** @brief internal counter to parse ring events */
    UINT32 m_nextEvent;

    /** @brief last test result holder and counter*/
    UINT32 m_lastTestRes;
    UINT32 m_lastTestNumber;
    UINT32 m_numTestRes;

    /** @brief last proprietary error and counter*/
    UINT32 m_lastPropErr;
    UINT32 m_lastProgCnt;
    UINT32 m_numPropErr;

    /** @brief counter of "sleep done" events*/
    UINT32 m_sleepDoneCnt;

    usb4_platform_uC_target_MsgRing_ctx_t* m_MsgRing;
  // ---- Absorb target specific private data structures
} usb4_platform_uC_ctx_t;


void Usb4PlatformUcInit(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx, UINT8* coreBaseAddress, UINT32 coreIdx);
void Usb4PlatformUcDeInit(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx);

/**
 * @brief Load the FW to uC
 * @return 0 on success, other on failure
 */
int Usb4PlatformUcLoadFW(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx);

/**
 * @brief Set GO bit for uC
 * @return 0 on success, other on failure
 */
int Usb4PlatformUcActivateUc(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx);

/**
 * @brief Clear GO bit for uC - default empty implementation
 * @return 0 on success, other on failure
 */
int Usb4PlatformUcDeActivateUc(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx);

/** @brief perfrom the action specified  
 *  @param [in/out] pIoctl to execute
 *  @return 0 on success other on failure
 */
int Usb4PlatformUcIoctl(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx, usb4_uc_ioctl_t* pIoctl);

/**
 * @brief handler for Log Buffer printing
 * @return 0 on success, other on failure
 */
void Usb4PlatformUcHandleUcEvents(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx);

/**
 * @brief gets the last uc test results
 * @return 0 on success, other on failure
 */
int Usb4PlatformUcGetTestResult(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx, UINT32* testRes, UINT32* testNumber, UINT32* pNum);

/**
* @brief gets the last uc error, and number of errors since
*        last call
* @param [out] pLastErr output last result, valid if *pNum >= 1
* @param [out] pProgramCounter output last PC, valid if *pNum >= 1
* @param [out] pNum will hold number of results
* @return 0 on success, other on failure
*/
int Usb4PlatformUcGetPropreitryError(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx, UINT32* pLastErr, UINT32* pProgramCounter, UINT32* pNum);

/**
* @brief gets number of sleep done events since uC was activated
*        last call
* @param [out] pNum will hold number of results
* @return 0 on success, other on failure
*/
int Usb4PlatformUcGetSleepDoneCounter(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx, UINT32* pNumSleepDone);

/**
* @brief prints uc msgs received since last print
* @return 0 on success, other on failure
*/
int Usb4PlatformUcPrintUcMsgs(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx);

/**
* @brief return the last uc msg 
* @return 0 on success, other on failure
*/
int Usb4PlatformUcPopUcMsg(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx, UINT8* buff);

/**
* @brief return the last uc msg without taking here out
* @return 0 on success, other on failure
*/
int Usb4PlatformUcPeekUcMsg(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx, UINT8* buff);

int Usb4PlatformUcMaskIrq(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx, BOOLEAN bMask);

/**
* @brief return number of messages in the buffer
* @param [out] pNum output number of messages
* @return 0 on success, other on failure
*/
int Usb4PlatformUcGetNumUcMsgs(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx, UINT32* pNum);

/**
* @brief return the entry size of the ring
* @param [out] pSizeBytes ring entry size
* @return 0 on success, other on failure
*/
int Usb4PlatformUcGetUCEntrySizeBaytes(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx, UINT32* pSizeBytes);





/*---------------------------------------------------------------------------*/
///////////////////////////////
///////////////////////////////
///////////////////////////////
// Platform Base
///////////////////////////////
///////////////////////////////
///////////////////////////////
typedef struct
{
     // ++++ Base Class
     BOOLEAN m_bSkipLoadingFirmware; /* Needed to modify the behavior of uC activation */
     BOOLEAN m_bDoSidebandOverride;  /* Needed to modify the behavior of GCC resets*/
     USB4_platform_sb_ctrl m_sidebandOverrideValue;/* Needed to modify the behavior of GPIOs */
     BOOLEAN m_bSleepUnplugged;     /* Needed configure uC behavior during wake*/

     usb4_platform_interrupts_ctx_t* m_interrupts;
     /** @brief AHB access module */
     usb4_platform_ahb_access_ctx_t* m_ahbAccess;
     /** @brief GCC module */
     // usb4_gcc_ctx_t* m_GCC; // Absorbed into usb4_platform_ctx_t* for simplicity

     /** @brief PMIC module */
     // usb4_pmic* m_pmic;

     /** @brief PHY module */
     usb4_platform_cio_phy_ctx_t* m_PHY;
     usb4_platform_uC_ctx_t* m_uC;
     // VVDRV_usb4_pd* m_PD; // Pass CoreIdx since no data structure was created
     usb4_dp_aux_ctx_t* m_pDpAux;
     // ---- Base Class

     // ++++ Absorb target specific data structures
     /** @brief stores the core index */
     UINT32 m_coreIndex;
     UINT8* m_coreBaseAddress;
     void* m_pHandler; // Only used by GEN_EMU
     // deo_mutex_t* m_pMutex;  // TODO: AC port to UEFI

     /* Data that has to persist through sleep */
     UINT32 m_USBAP_RXTERM_BACKDOOR_STS;
     // ---- Absorb target specific data structures

     // UEFI specific
     EFI_CLOCK_PROTOCOL* ClockProtocol;
     EFI_HAL_IOMMU_PROTOCOL* IommuProtocol;
     HAL_IOMMU_fptable_t* SmmuTable;  
     VOID* Usb4SmmuDomain;
     EFI_HWIO_PROTOCOL *HWIOProtocol;
     EFI_TLMM_PROTOCOL *TLMMProtocol;
     UINT8* UsbHrAddr[USB4_NUM_OF_CORES]; // Virtual Address from MapRegionByAddress API. TODO: AC change to use Max Core
} usb4_platform_ctx_t;

    

#if 0 // TODO: AC port later since abstraction no longer needed
/**
 * @brief Accessors
 * @return pointer to private member
 */
VVHAL_usb4_platform_ahb_access* AHB(){return m_ahbAccess;};
VVHAL_usb4_gcc* GCC(){return m_GCC;};
VVHAL_usb4_pmic* PMIC() { return m_pmic; };
VVHAL_usb4_platform_cio_phy* PHY() {return m_PHY;};
VVHAL_usb4_platform_uC* uC(){ return m_uC; };
VVDRV_usb4_pd* PD(){ return m_PD; };
usb4_platform_interrupts_ctx_t* interrupts() { return m_interrupts; }
VVDRV_usb4_dp_aux* DpAux() { return m_pDpAux; }
#endif

/**
 * @brief Factory for platform object
 * @return new platfrom object on success, NULL on failure
 */
usb4_platform_ctx_t* Usb4PlatformCreate(UINT32 coreIndex);
void Usb4PlatformDeInit(usb4_platform_ctx_t* usb4_platform_ctx); // Destructor

#if 0 // +++ These are already defined in usb4_platform_target.h
    /**
     * @brief Construct all HW specific objects 
     * @return 0 on success, other on failure
     */
    virtual int Init() = 0; 
    
    /**
     * @brief Destruct all HW specific objects 
     */
    virtual void DeInit(); 
    
    /**
     * @brief Return Core Index from the instantiated platform
     * @return CoreIndex
     */
    virtual UINT32 GetCoreIndex() const = 0;

    /**
     * @brief Get platform specific address of HIA
     * @param[out] ppBase - Base address
     * @return 0 on success, other on failure
     */
    virtual int GetHIA_Base(UINT8** ppBase){ return -1; };

    /**
    * @brief Get platform specific address of the core
    * @param[out] ppBase - Base address
    * @return 0 on success, other on failure
    */
    virtual int GetCore_Base(UINT8** ppBase){ return -1; };

    /**
    * @brief Store platform specific data that needs to persist though sleep;
    * Platform specific implementation is not mandatory
    * @return 0 on success, other on failure
    */
    virtual int StorePersistentData(){ return 0; };

    /**
    * @brief Write back platform specific data that needs to persist though sleep;
    * Platform specific implementation is not mandatory
    * @return 0 on success, other on failure
    */
    virtual int WriteBackPersistentData(){ return 0; };

    /**
    * @brief Perform GCC, PHY and other actions needed to put platform to sleep
    * Platform specific implementation is not mandatory
    * @return 0 on success, other on failure
    */
    virtual int PutPlatformToSleep()
    {
        m_bSkipLoadingFirmware = TRUE;
        return 0;
    };

    /**
    * @brief Check if cable is connected prior to going to sleep. This impacts side-band override configuration
    * Platform specific implementation is not mandatory
    * @return 0 on success, other on failure
    */
    virtual int GetCablePluggedStatus()
    {
        return -1;
    }

    /**
    * @brief Perform GCC, PHY and other actions needed to wake platform from sleep
    * Platform specific implementation is not mandatory
    * @return 0 on success, other on failure
    */
    virtual int WakePlatformFromSleep()
    {
        return 0;
    };
    
    /**
     * @brief Configure side band overrides as needed
     * @return 0 on success, other on failure
     */
    virtual int PlatformPreReset()
    {
        return 0;
    };

    /**
     * @brief Configure side band overrides as needed
     * @return 0 on success, other on failure
     */
    virtual int PlatformPostReset()
    {
        return 0;
    };

    /**
     * @brief Configure side band mode and orientation
     * @param [in] bSwap - Normal or Swapped cable orientation (external muxes configuration)
     * @return 0 on success, other on failure
     */
    virtual int SideBandConfigure(BOOLEAN bSwap)
    {
        return 0;
    };

    /**
     * @brief Configure SBRX overrides
     * @param [in] gpioCtrl see #USB4_platform_sb_ctrl for additional details
     * @return 0 on success, other on failure
     */
    virtual int SideBandRxControl(USB4_platform_sb_ctrl gpioCtrl)
    { 
        return 0; 
    };
    
    /**
     * @brief Configure SBTX overrides
     * @param [in] gpioCtrl see #USB4_platform_sb_ctrl for additional details
     * @return 0 on success, other on failure
     */
    virtual int SideBandTxControl(USB4_platform_sb_ctrl gpioCtrl)
    { 
        (void) gpioCtrl;
        return 0; 
    };

    /**
     * @brief Override TX Enable in proprietary SB register
     * @param [in] overrideValue - 1 for Enable or 0 - Disable
     * @return 0 on success, other on failure
     */
    virtual int OverrideSbTxEnable(UINT32 overrideValue)
    {
        (void) overrideValue;
        return 0;
    };

    /**
     * @brief Update TDISCONNECTRX value
     * @param [in] overrideValue - new value
     * @return 0 on success, other on failure
     */
    virtual int OverrideSbTDisconnectRx(UINT32 overrideValue, UINT32* pPrevValue)
    {
        (void) overrideValue;
        (void) pPrevValue;
        return 0;
    };

    /**
    * @brief Lock mutex; This is not try lock. Failure means mutex is not valid/
    * @return 0 on success, other on failure
    */
    virtual int LockMutex()
    {
        return 0;
    };

    /**
    * @brief UnLock mutex; This is not try lock. Failure means mutex is not valid/
    * @return 0 on success, other on failure
    */
    virtual int UnlockMutex()
    {
        return 0;
    };
#endif // --- These are already defined in usb4_platform_target.h
#endif //__USB4_PLATFORM_H__
