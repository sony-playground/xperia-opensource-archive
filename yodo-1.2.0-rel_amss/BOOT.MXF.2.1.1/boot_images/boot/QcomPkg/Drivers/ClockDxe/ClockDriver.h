#ifndef __CLOCKDRIVER_H__
#define __CLOCKDRIVER_H__
/*
===========================================================================
*/
/**
  @file ClockDriver.h

  Internal header file for the clock device driver.
*/
/*
  ====================================================================

  Copyright (c) 2020-2021 QUALCOMM Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Drivers/ClockDxe/ClockDriver.h#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $

  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "stdbool.h"
#include "stddef.h"
#include "stdint.h"
#include "ClockDefs.h"
#include "DALSys.h"
#include "ULogFront.h"
#include "ClockBSP.h"
#include "npa.h"
#include "ClockSWEVT.h"
#include "CoreVerify.h"


/*=========================================================================
      Macro Definitions
==========================================================================*/

/**
 * Macro lock the driver mutex.
 */
#define DALCLOCK_LOCK(drvCtxt) DALSYS_SyncEnter(drvCtxt->hLock)


/**
 * Macro try-lock the driver mutex.
 */
#define DALCLOCK_TRYLOCK(drvCtxt) DALSYS_SyncTryEnter(drvCtxt->hLock)


/**
 * Macro to free the driver mutex.
 */
#define DALCLOCK_FREE(drvCtxt) DALSYS_SyncLeave(drvCtxt->hLock)


/**
 * Check if source is controlled by an NPA resource.
 */
#define CLOCK_SOURCE_NPA_CONTROLLED(src) \
  ((src)->szName && (src)->szName[0] == '/')


/**
 * NPA client name used for internal clock driver clients.
 */
#define CLOCK_NPA_CLIENT_NAME  "clock"


/**
 * Convert an NPA state to a frequency in Hz.
 */
#define NPA_TO_HZ(state) \
  (uint32_t)((state) == NPA_MAX_STATE ? (state) : (state) * 1000)


/*
 * Macros for checking, setting and clearing the unified flag bits in the
 * driver nodes.  Note these work on any structure containing an "nFlags"
 * field.
 */
#define CLOCK_FLAG_IS_SET(ptr, flag) (((ptr)->nFlags & CLOCK_FLAG_##flag) ? TRUE : FALSE)
#define CLOCK_FLAG_SET(ptr, flag)    ((ptr)->nFlags |= CLOCK_FLAG_##flag)
#define CLOCK_FLAG_CLEAR(ptr, flag)  ((ptr)->nFlags &= ~CLOCK_FLAG_##flag)


/*
 * Macros for checking, setting and clearing the global flag bits in the
 * driver context.  Note these work only on the "nGlobalFlags" field
 * within the driver context structure.
 */
#define CLOCK_GLOBAL_FLAG_IS_SET(flag) ((pDrvCtxt->pBSP->nFlags & CLOCK_GLOBAL_FLAG_##flag) ? TRUE : FALSE)
#define CLOCK_GLOBAL_FLAG_SET(flag)    (pDrvCtxt->pBSP->nFlags |= CLOCK_GLOBAL_FLAG_##flag)
#define CLOCK_GLOBAL_FLAG_CLEAR(flag)  (pDrvCtxt->pBSP->nFlags &= ~CLOCK_GLOBAL_FLAG_##flag)


/*
 * Macros for checking, setting and clearing flags passed to public APIs.
 */
#define CLOCK_API_FLAG_IS_SET(flags, api, flag) ((flags & CLOCK_##api##_FLAG_##flag) ? TRUE : FALSE)
#define CLOCK_API_FLAG_SET(flags, api, flag)    (flags |= CLOCK_##api##_FLAG_##flag)
#define CLOCK_API_FLAG_CLEAR(flags, api, flag)  (flags &= ~CLOCK_##api##_FLAG_##flag)


/*
 * Macro to check if a clock is stubbed on the current running platform.
 */
#define CLOCK_STUBBED(ptr) \
  ( \
    ((ptr->nFlags & CLOCK_FLAG_STUB_HW_RUMI) && \
     DalPlatformInfo_Platform() == DALPLATFORMINFO_TYPE_RUMI) || \
    ((ptr->nFlags & CLOCK_FLAG_STUB_HW_VIRTIO) && \
     DalPlatformInfo_Platform() == DALPLATFORMINFO_TYPE_VIRTIO) \
  )

/*
 * Values used for making NPA requests on clock sources.
 *  0:          Everything related to XO can be turned off.
 *  0xFFFFFFFF: Everything possible in the chain (crystal to pad) must be on.
 */
#define CLOCK_SOURCE_NOT_REQUIRED     0
#define CLOCK_SOURCE_REQUIRED         0xFFFFFFFF


/*
 * Default size of the BIST ULOG log buffer.
 *
 * NOTE: The log size should be specified in powers of 2.
 */
#define CLOCK_DEFAULT_LOG_SIZE         4096
#define CLOCK_BIST_DEFAULT_LOG_SIZE    65536


/*
 * Macro to force an enumeration to be a full 32 bits wide.
 */
#define CLOCK_ENUM_32BITS(name) CLOCK_##name##_32BITS = 0x7FFFFFFF


/*
 * Clock ID macros.
 */
#define CLOCK_MAKE_ID(cat, idx)   (((cat) << 16) | (idx))
#define CLOCK_GET_ID_CATEGORY(id) (((id) & 0xFFFF0000) >> 16)
#define CLOCK_GET_ID_INDEX(id)    ((id) & 0xFFFF)
#define CLOCK_ID_INVALID          0


/*
 * Reference count helper macros.
 */
#define CLOCK_REF_COUNT_REQ(x) \
  ((x)->RefCount.nRequired)

#define CLOCK_REF_COUNT_SUPP(x) \
  ((x)->RefCount.nSuppressible)

#define CLOCK_REF_COUNT_TOTAL(x) \
  (CLOCK_REF_COUNT_REQ(x) + CLOCK_REF_COUNT_SUPP(x))

#define CLOCK_REF_COUNT(x, suppressible) \
  (suppressible == true ? CLOCK_REF_COUNT_SUPP(x) : CLOCK_REF_COUNT_REQ(x))

#define CLOCK_REF_COUNT_INC(x, suppressible) \
  (suppressible == true ? (x)->RefCount.nSuppressible++ : (x)->RefCount.nRequired++)

#define CLOCK_REF_COUNT_DEC(x, suppressible) \
  (suppressible == true ? (x)->RefCount.nSuppressible-- : (x)->RefCount.nRequired--)


/*
 * Linked list macros.
 */
#define CLOCK_INSERT_LL_NODE(list, node) \
  Clock_InsertLLNode((ClockLLNodeType **)(list), (ClockLLNodeType *)(node))

#define CLOCK_REMOVE_LL_NODE(list, node, cleanup) \
  Clock_RemoveLLNode((ClockLLNodeType **)(list), (ClockLLNodeType *)(node), cleanup)

#define CLOCK_LL_NODE(x) \
  (&((x)->LLNode))

#define CLOCK_LL_NEXT(x) \
  (CLOCK_LL_NODE(x)->pNext)

#define CLOCK_LL_HEAD(x) \
  ((ClockLLNodeType **)&(x))
  
/*
 * Rail index masking macros.
 */
#define CLOCK_RAIL_MASK_SET(mask, index) \
  ( (mask) & (0x1 << (index)) )

/*=========================================================================
      Type Definitions
==========================================================================*/

/*
 * ClockIdCategoryType
 *
 * Clock ID categories.
 */
typedef enum
{
  CLOCK_ID_CATEGORY_NONE = 0,
  CLOCK_ID_CATEGORY_CLOCK,
  CLOCK_ID_CATEGORY_POWERDOMAIN,
  CLOCK_ID_CATEGORY_SOURCE,
  CLOCK_ID_CATEGORY_DEBUGMUX,
  CLOCK_ID_CATEGORY_DIVIDER,

  CLOCK_ID_CATEGORY_TOTAL,
} ClockIdCategoryType;


typedef struct ClockPDCtxt ClockPDCtxt;

typedef struct ClockClientCtxt ClockClientCtxt;
struct ClockClientCtxt
{
  /* Linked list chaining field - must be first in struct */
  ClockClientCtxt *pNext;

  char        *szName; /**< String name of client. */
  ClockPDCtxt *pPD;    /**< Pointer to PD this client belongs to. */
  uint32_t     nFlags; /**< Flags for this client. */
};


typedef struct ClockPDCtxt ClockPDCtxt;
struct ClockPDCtxt
{
  /* Linked list chaining field - must be first in struct */
  ClockPDCtxt *pNext;

  uint32_t         nId;         /**< Kernel identifier for this PD. */
  char            *szName;      /**< String name of PD. */
  ClockClientCtxt *pClients;    /**< Pointer to linked list of client contexts. */
};


/**
 *  Linked list node structure for storing callbacks
 */
typedef struct ClockCallbackNodeType ClockCallbackNodeType;
struct ClockCallbackNodeType
{
  /* Linked list chaining field - must be first in struct */
  ClockCallbackNodeType  *pNext;          /**< Linked list chaining field */

  ClockIdType              nResourceID;    /**< ID of resource */
  ClockCallbackEventType  eEvent;         /**< Event type for this callback */
  ClockCallbackFn          pfnCallback;    /**< Callback function pointer */
  ClockCallbackCtxt        CallbackCtxt;   /**< Callback function context */
};


/**
 * Clock driver context.
 */
typedef struct
{
  ClockBSPType      *pBSP;                    /**< Main clock driver BSP data. */
  DALSYSSyncObj      LockObj;                 /**< Sync object storage */
  DALSYSSyncHandle   hLock;                   /**< Handle to our mutex for Serializing Core functionality */
  DALSYSSyncObj      DebugLockObj;            /**< Sync object storage */
  DALSYSSyncHandle   hDebugLock;              /**< Handle to our mutex for Serializing Debug/Test functionality */
  ULogHandle         hClockLog;               /**< Handle to our ULOG log */
  ULogHandle         hClockBISTLog;           /**< Handle to our BIST ULOG log */
  uint32_t           nBISTLogSize;            /**< Size of the BIST ULOG log */
  void              *pImageCtxt;              /**< Image context */
  ClockPDCtxt           *pPDs;                   /**< Linked list of PD contexts */
  ClockHandle            hClient;                /**< Handle to internal client */
  bool                   bBISTEnabled;           /**< Flag used to enable the BIST */
  bool                   bColdStart;              /**< FALSE on wake up from hibernate */
  bool                   bDCVSEnabled;           /**< DCVS state */
  bool                   bSuspendVoltageRequest; /**< Voltage suspension state */
  DALSYS_PROPERTY_HANDLE_DECLARE(hProp);    /**< Handle to our DEVCFG */
  DalDeviceHandle       *phHWIO;                 /**< Handle to HWIO driver */
  ClockCallbackNodeType *pCallbacks[CLOCK_ID_CATEGORY_TOTAL]; /**< Per resource type head of registered callbacks' linked list */
} ClockDrvCtxt;


typedef void (*ClockCleanupFunc)(void *pData);


/*=========================================================================
      Function Definitions
==========================================================================*/

/* =========================================================================
**  Function : Clock_DriverInit
** =========================================================================*/
/**
  Initialize the clock driver.

  This function initializes the clock driver, it is the main init entry
  point.

  @return
  CLOCK_SUCCESS -- Init was successful.
  CLOCK_ERROR -- Initialization failed.

  @dependencies
  None.
*/

ClockResult Clock_DriverInit
(
  void
);


/* =========================================================================
**  Function : ClockStub_DriverInit
** =========================================================================*/
/**
  Initialize the clock driver stub.

  This function initializes the clock driver, it is the main init entry
  point.

  @return
  CLOCK_SUCCESS -- Init was successful.
  CLOCK_ERROR -- Initialization failed.

  @dependencies
  None.
*/

ClockResult ClockStub_DriverInit
(
  void
);


/* =========================================================================
**  Function : Clock_DriverDeInit
** =========================================================================*/
/**
  De-initialize the clock driver.

  This function shuts-down the clock driver.  It is not expected to ever
  be called.

  @return
  CLOCK_SUCCESS -- Init was successful.
  CLOCK_ERROR -- Initialization failed.

  @dependencies
  None.
*/

ClockResult Clock_DriverDeInit
(
  void
);


/* =========================================================================
**  Function : ClockStub_DriverDeInit
** =========================================================================*/
/**
  De-initialize the clock driver stub.

  This function shuts-down the clock driver.  It is not expected to ever
  be called.

  @return
  CLOCK_SUCCESS -- Init was successful.
  CLOCK_ERROR -- Initialization failed.

  @dependencies
  None.
*/

ClockResult ClockStub_DriverDeInit
(
  void
);


/* =========================================================================
**  Function : Clock_InitBases
** =========================================================================*/
/**
  Initialize clock register bases.

  This function initializes register bases used by the clock driver. It maps
  each address used by the driver to its virtual representation.

  @return
  CLOCK_SUCCESS -- Initialization was successful.
  CLOCK_ERROR -- Initialization failed.

  @dependencies
  None.
*/

ClockResult Clock_InitBases
(
  void
);


/* =========================================================================
**  Function : Clock_InitTarget
** =========================================================================*/
/**
  Initialize the target specific portion of the clock driver.

  This function initializes the portion of the clock driver that is specific
  to the image and chipset we are running on.

  @return
  CLOCK_SUCCESS -- Init was successful.
  CLOCK_ERROR -- Initialization failed.

  @dependencies
  None.
*/

ClockResult Clock_InitTarget
(
  void
);


/* =========================================================================
**  Function : Clock_FrameworkInit
** =========================================================================*/
/**
  Hook for a framework shim to initialize.

  This function initializes the portion of the clock driver that is specific
  to the framework we are running on.

  @return
  CLOCK_SUCCESS -- Init was successful.
  CLOCK_ERROR -- Initialization failed.

  @dependencies
  None.
*/

ClockResult Clock_FrameworkInit
(
  void
);


/* =========================================================================
**  Function : ClockStub_InitTarget
** =========================================================================*/
/**
  Initialize the target specific portion of the clock driver.

  This function initializes the portion of the clock driver that is specific
  to the image and chipset we are running on.

  @return
  CLOCK_SUCCESS -- Init was successful.
  CLOCK_ERROR -- Initialization failed.

  @dependencies
  None.
*/

ClockResult ClockStub_InitTarget
(
  void
);


/* =========================================================================
**  Function : Clock_InitDCVS
** =========================================================================*/
/**
  Initialize the NPA DCVS nodes for this image in the clock driver.

  This function initializes the DCVS module for the current image.  This
  will define and create the required NPA nodes.  Nodes will be be
  active until DalClock_EnableDCVS has been called.

  @return
  CLOCK_SUCCESS -- Init was successful.
  CLOCK_ERROR -- Initialization failed.

  @dependencies
  None.
*/

ClockResult Clock_InitDCVS
(
  void
);


/* =========================================================================
**  Function : Clock_InitNPA
** =========================================================================*/
/**
  Initialize the generic NPA resources.

  This function initializes the generic NPA resources that control domain
  frequencies.

  @return
  CLOCK_SUCCESS -- Init was successful.
  CLOCK_ERROR -- Initialization failed.

  @dependencies
  None.
*/

ClockResult Clock_InitNPA
(
  void
);


/* =========================================================================
**  Function : Clock_TestClock
** =========================================================================*/
/**
  Perform a non-destructive built-in self test on the specified clock node
  in the driver.

  @param ClockId [in] -- Clock ID of the clock to be tested.

  @return
  CLOCK_SUCCESS -- BIST was successful.
  CLOCK_ERROR -- BIST failed.

  @dependencies
  Core and image initialization must be complete prior to running the test.
*/

ClockResult Clock_TestClock
(
  ClockIdType ClockId
);


/* =========================================================================
**  Function : Clock_BIST
** =========================================================================*/
/**
  Perform a non-destructive built-in self test on all clock nodes in the
  driver.

  @return
  CLOCK_SUCCESS -- BIST was successful.
  CLOCK_ERROR -- BIST failed.

  @dependencies
  Core and image initialization must be complete prior to running the BIST.
*/

ClockResult Clock_BIST
(
  void
);


/* =========================================================================
**  Function : Clock_ImageBIST
** =========================================================================*/
/**
  Perform a non-destructive built-in self test on the image specific portion
  of the clock driver.

  @param *bBISTPassed [in/out] -- Pointer to the main BIST passed bool.
  @param *nFailedTests [in/out] -- Pointer to the main BIST value which stores
                                   number of failed tests.

  @return
  CLOCK_SUCCESS -- Image BIST was successful.
  CLOCK_ERROR -- Image BIST failed.

  @dependencies
  Core and image initialization must be complete prior to running the Image BIST.
*/

ClockResult Clock_ImageBIST
(
  bool     *bBISTPassed,
  uint32_t *nFailedTests
);


/* =========================================================================
**  Function : Clock_FindClockConfig
** =========================================================================*/
/**
  Finds a particular clock configuration in the BSP.

  This function finds a particular clock configuration in the BSP based on
  the specified frequency and match criteria.

  @param *pDomain[in] -- Pointer to a clock domain.
  @param nFreqHz [in] -- Frequency in Hz
  @param eMatch [in] -- Match criteria
  @param **pMatchingConfig [out] -- Matching configuration

  @return
  CLOCK_SUCCESS -- A matching configuration was found.
  CLOCK_ERROR -- A matching configuration was not found.

  @dependencies
  None.
*/

ClockResult Clock_FindClockConfig
(
  ClockDomainNodeType  *pDomain,
  uint32_t              nFreqHz,
  ClockFrequencyType    eMatch,
  ClockMuxConfigType  **pMatchingConfig
);


/* =========================================================================
**  Function : Clock_SetClockConfig
** =========================================================================*/
/**
  Sets a clock configuration.

  This function configures a clock domain to a particular configuration.
  It is used internally only.

  @param  hClient [in] -- Handle to the client.
  @param *pClockDomain [in] -- Clock domain to configure.
  @param *pNewConfig [in] -- New configuration to use.

  @return
  CLOCK_SUCCESS -- The domain was successfully configured.
  CLOCK_ERROR -- The domain configuration failed.

  @dependencies
  The clock mutex must be locked.
*/

ClockResult Clock_SetClockConfig
(
  ClockHandle          hClient,
  ClockDomainNodeType *pDomain,
  ClockMuxConfigType  *pNewConfig
);


/* =========================================================================
**  Function : Clock_EnableSourceInternal
** =========================================================================*/
/**
  Requests to enable a source.

  This function enables a source, generally as a result of a call to
  Clock_EnableClockDomain().  CPU based source requests are tracked
  independently of non-CPU based as the former will be automatically
  released when the CPU goes to sleep.
  A reference count is maintained so callers must ensure that all Enables
  and Disables are matched.

  @param  hClient [in] -- Handle to the client.
  @param *pSource [in] -- Pointer to a source node.
  @param bSuppressibleRequest [in] -- TRUE if this is a source request is for a suppressible clock.

  @return
  CLOCK_SUCCESS -- The source was successfully enabled.
  CLOCK_ERROR -- The source was not enabled.

  @dependencies
  The clock mutex must be locked prior to calling this function.
*/

ClockResult Clock_EnableSourceInternal
(
  ClockHandle          hClient,
  ClockSourceNodeType *pSource,
  bool                 bSuppressibleRequest
);


/* =========================================================================
**  Function : Clock_DisableSourceInternal
** =========================================================================*/
/**
  Disables a source.

  This function disables a source, generally as a result of a call to
  Clock_DisableClockDomain().
  A reference count is maintained so callers must ensure that all Enables
  and Disables are matched.

  @param  hClient [in]              -- Handle to the client.
  @param *pSource [in] -- Pointer to a source node.
  @param bSuppressibleRequest [in] -- TRUE if this is a source request is for a suppressible clock.

  @return
  CLOCK_SUCCESS -- The source was successfully disabled.
  CLOCK_ERROR -- The source was not disabled.

  @dependencies
  The clock mutex must be locked prior to calling this function.
*/

ClockResult Clock_DisableSourceInternal
(
  ClockHandle          hClient,
  ClockSourceNodeType *pSource,
  bool                 bSuppressibleRequest
);


/* =========================================================================
**  Function : Clock_FindSourceConfig
** =========================================================================*/
/**
  Finds a particular source configuration in the BSP.

  This function finds a particular source configuration in the BSP based on
  the specified frequency and match criteria.

  @param *pSource [in] -- Pointer to a source node.
  @param nFreqHz [in] -- Frequency in Hz
  @param eMatch [in] -- Match criteria
  @param **pMatchingConfig [out] -- Matching configuration

  @return
  CLOCK_SUCCESS -- A matching configuration was found.
  CLOCK_ERROR -- A matching configuration was not found.

  @dependencies
  None.
*/
ClockResult Clock_FindSourceConfig
(
  const ClockSourceFreqConfigType  *aBSP,
  uint32_t                          nBSPLen,
  uint32_t                          nFreqHz,
  ClockFrequencyType                eMatch,
  const ClockSourceFreqConfigType **pMatchingConfig
);


/* =========================================================================
**  Function : Clock_ConfigSource
** =========================================================================*/
/**
  Configures a source.

  This function configures a source, generally a PLL.  This can only be
  done if there are no users of the source and we own the PLL.

  @param *pSource [in] -- Pointer to a source node.
  @param *pConfig [in] -- New configuration.

  @return
  CLOCK_SUCCESS -- The source was successfully configures.
  CLOCK_ERROR -- The source was not configured, either due to invalid
               parameter or (more likely) the source was in use.

  @dependencies
  The clock mutex must be locked prior to calling this function.
*/

ClockResult Clock_ConfigSource
(
  ClockSourceNodeType              *pSource,
  const ClockSourceFreqConfigType  *pConfig
);


/* =========================================================================
**  Function : Clock_DetectSourceConfig
** =========================================================================*/
/**
  Detect a source configuration.

  This function detects a source configuration by reading the HW state
  and matching it with the BSP data. It will set the various bookkeeping
  fields to match the detected configuration.

  @param *pSource [in] -- Pointer to a source node.

  @return
  CLOCK_SUCCESS -- The source configuration was successfully detected.
  CLOCK_ERROR -- The source configuration was not found.

  @dependencies
  The clock mutex must be locked prior to calling this function.
*/

ClockResult Clock_DetectSourceConfig
(
  ClockSourceNodeType *pSource
);

/* =========================================================================
**  Function : Clock_InitSource
** =========================================================================*/
/**
  Configures a source.

  This function initializes a source, generally a PLL, from the current BSP
  data.

  @param *pSource           [in] -- Pointer to a source node.

  @return
  CLOCK_SUCCESS -- The source was successfully initialized.
  CLOCK_ERROR -- The source was not initialized, generally because the source
               has no valid BSP data.

  @dependencies
  The clock mutex should be locked prior to calling this function or
  we should be a single execution thread environment (like boot).
*/

ClockResult Clock_InitSource
(
  ClockSourceNodeType             *pSource,
  const ClockSourceFreqConfigType *pSourceFreqConfig
);


/* =========================================================================
**  Function : Clock_GetPropertyValue
** =========================================================================*/
/**
  Retrieve a clock driver property from the environment store.

  This function retrieves the given clock property from the relevant
  storage location (may be DAL properties DB or another source).

  @param *szName [in] -- Name of the property to look up
  @param *pValue [out] -- Location to store the result

  @return
  CLOCK_SUCCESS if property was found and retrieved, CLOCK_ERROR otherwise.

  @dependencies
  None.
*/

ClockResult Clock_GetPropertyValue
(
  const char              *szName,
  ClockPropertyValueType  *pValue
);


/* =========================================================================
**  Function : Clock_MapHWIORegion
** =========================================================================*/
/**
  Map a HWIO region into memory for the clock driver.

  This function maps a physical HWIO region into memory for the clock driver
  using environment appropriate APIs.  If the mapping is not available
  the virtual address will be set to the provided physical address.

  @param nPhysAddr [in] -- Physical address.
  @param nSizeBytes [in] -- Size of the region in bytes.
  @param *pnVirtAddr [out] -- Location to store the mapped address.

  @return
  CLOCK_SUCCESS if mapping was ok, otherwise error code based on failure.

  @dependencies
  None.
*/

ClockResult Clock_MapHWIORegion
(
  uintptr_t  nPhysAddr,
  uint32_t   nSizeBytes,
  uintptr_t *pnVirtAddr
);


/* =========================================================================
**  Function : Clock_MapAddress
** =========================================================================*/
/**
  Map a single address to its virtual representation.

  This function maps a single address to its virtual representation.

  @param *pnAddr [in/out] -- Pointer to physical address to map. Updated
                             to mapped virtual address.

  @return
  CLOCK_SUCCESS if mapping was ok, otherwise error code based on failure.

  @dependencies
  None.
*/

ClockResult Clock_MapAddress
(
  uintptr_t *pnAddr
);


/* =========================================================================
**  Function : Clock_InitVoltage
** =========================================================================*/
/**
  Initialize voltage tracking subsystem.

  This function prepares the voltage tracking module for managing voltage
  requests.

  @return
  CLOCK_SUCCESS -- Initialization was successful.
  CLOCK_ERROR -- Initialization failed.

  @dependencies
  None.
*/

ClockResult Clock_InitVoltage
(
  void
);


/* =========================================================================
**  Function : Clock_VoltageRequest
** =========================================================================*/
/**
  Make a voltage regulator request.

  This function is used internally for a clock domain to make a voltage
  regulator level request.

  @param nRailMask [in] -- 32-bit mask indicating the set of rail indices being requested.
  @param *pCurrentRequest [in/out] -- Pointer to currently requested voltage config.
                                      Updated to pNewRequest.
  @param *pNewRequest [in] -- New voltage requirement.

  @return
  CLOCK_SUCCESS -- Request was successful.
  CLOCK_ERROR -- Request failed.

  @dependencies
  The clock mutex must be locked.
*/

ClockResult Clock_VoltageRequest
(
  uint32_t               nRailMask,
  ClockVRegRequestType  *pCurrentRequest,
  ClockVRegRequestType  *pNewRequest
);


/* =========================================================================
**  Function : Clock_VoltageSuspend
** =========================================================================*/
/**
  Make a request to suspend voltage requests.

  This function is used internally to suspend voltage requests.

  @param *pRail [in] -- Pointer to rail being suspended.

  @return
  CLOCK_SUCCESS -- Request was successful.
  CLOCK_ERROR   -- Request failed.

  @dependencies
  The clock mutex must be locked.
*/

ClockResult Clock_VoltageSuspend
(
  ClockRailType *pRail
);


/* =========================================================================
**  Function : Clock_VoltageResume
** =========================================================================*/
/**
  Make a request to resume voltage requests.

  This function is used internally to resume voltage requests.

  @param *pRail [in] -- Pointer to rail being resumed.
  @param bUpdate [in] -- Flag to update voltage request immediately upon resume.

  @return
  CLOCK_SUCCESS -- Request was successful.
  CLOCK_ERROR   -- Request failed.

  @dependencies
  The clock mutex must be locked.
*/

ClockResult Clock_VoltageResume
(
  ClockRailType *pRail,
  bool           bUpdate
);


/*=========================================================================
**  Function : Clock_IsBSPSupported
** =========================================================================*/
/**

  This function validates the specified BSP config is supported on the
  executing target chip and version.

  @param pHWVersion [in] - HW Version

  @return
  TRUE - HW version is supported.
  FALSE - HW version is not supported.

  @dependencies
  None.
*/

bool Clock_IsBSPSupported
(
  const ClockHWVersionType *pHWVersion
);


/*=========================================================================
**  Function : Clock_GetDrvCtxt
** =========================================================================*/
/**
  Returns driver context.

  This function is used to get the driver context.


  @return
  Pointer to clock driver context.

  @dependencies
  None.
*/

ClockDrvCtxt * Clock_GetDrvCtxt
(
  void
);


/*=========================================================================
**  Function : Clock_GetMappedSource
** =========================================================================*/
/**
  Map mux select value to internal source node.

  @return
  CLOCK_SUCCESS -- Mapped source was found.
  CLOCK_ERROR -- No mapped source found.

  @dependencies
  None.
*/

ClockResult Clock_GetMappedSource
(
  const ClockSourceMapType   *aSourceMap,
  uint32_t                    nMuxSel,
  const ClockSourceMapType  **pMatchingSourceMap
);


/*=========================================================================
**  Function : Clock_GetRequiredCorner
** =========================================================================*/
/**
  Get required corner for frequency.

  @return
  CLOCK_SUCCESS -- Required corner found.
  CLOCK_ERROR -- No suitable corner found.

  @dependencies
  None.
*/

ClockResult Clock_GetRequiredCorner
(
  const ClockFMaxType *aFMax,
  uint32_t             nFreqHz,
  rail_voltage_level  *peVRegLevel
);


/*=========================================================================
**  Function : Clock_SetThreadPriority
** =========================================================================*/
/**
  Set priority of current thread.

  @param nPriority[in]      - Thread priority to set.
  @param nPrevPriority[out] - Original priority before setting new one.

  @dependencies
  None.
*/

void Clock_SetThreadPriority
(
  uint32_t  nPriority,
  uint32_t *nPrevPriority
);


/*=========================================================================
**  Function : Clock_AssignNPAState
** =========================================================================*/
/**
  Invoke an NPA driver function and assign the resource state.

  This function calls an NPA node driver function with nRequest, and
  assigns the resource state to the return value. This function bypasses
  the NPA aggregation layer and can be used to override the current request
  state of a node.

  @param *pResource [in] -- Pointer to NPA resource to assign.
  @param nRequest [in] -- New request state.

  @return
  npa_resource_state -- Active state of the resource.

  @dependencies
  The NPA node pointed to by pResource must have already been created.
*/

npa_resource_state Clock_AssignNPAState
(
  npa_resource        *pResource,
  npa_resource_state   nRequest
);


/*=========================================================================
**  Function : Clock_RestoreNPAState
** =========================================================================*/
/**
  Invoke an NPA driver function and assign the current request state.

  This function calls an NPA node driver function with the current aggregated
  request state, and assigns the resource state to the return value.

  @param *pResource [in] -- Pointer to NPA resource to assign.

  @return
  npa_resource_state -- Active state of the resource.

  @dependencies
  The NPA node pointed to by pResource must have already been created.
*/

npa_resource_state Clock_RestoreNPAState
(
  npa_resource *pResource
);


/*=========================================================================
**  Function : Clock_GetClockNode
** =========================================================================*/
/**
  Return pointer to clock node for a given ID.

  @param ClockId[in] -- Clock identifier to look up.

  @return
  ClockNodeType* if found; NULL otherwise.
*/

ClockNodeType *Clock_GetClockNode
(
  ClockIdType ClockId
);


/*=========================================================================
**  Function : Clock_GetSourceNode
** =========================================================================*/
/**
  Return pointer to source node for a given ID.

  @param SourceId[in] -- Source identifier to look up.

  @return
  ClockSourceNodeType* if found; NULL otherwise.
*/

ClockSourceNodeType *Clock_GetSourceNode
(
  ClockIdType SourceId
);


/*=========================================================================
**  Function : Clock_GetPowerDomainNode
** =========================================================================*/
/**
  Return pointer to power domain node for a given ID.

  @param PowerDomainId[in] -- Power domain identifier to look up.

  @return
  ClockPowerDomainNodeType* if found; NULL otherwise.
*/

ClockPowerDomainNodeType *Clock_GetPowerDomainNode
(
  ClockIdType PowerDomainId
);


/*=========================================================================
**  Function : Clock_GetDebugMuxNode
** =========================================================================*/
/**
  Return pointer to debug mux node for a given ID.

  @param DebugMuxId[in] -- Debug mux identifier to look up.

  @return
  ClockDebugMuxType* if found; NULL otherwise.
*/

ClockDebugMuxType *Clock_GetDebugMuxNode
(
  ClockIdType DebugMuxId
);


/*=========================================================================
**  Function : Clock_GetDividerNode
** =========================================================================*/
/**
  Return pointer to clock node for a given ID.

  @param DividerId[in] -- Divider identifier to look up.

  @return
  ClockDividerNodeType* if found; NULL otherwise.
*/

ClockDividerNodeType *Clock_GetDividerNode
(
  ClockIdType DividerId
);


/*=========================================================================
**  Function : Clock_GetClientRefCount
** =========================================================================*/
/**
  Return pointer to client reference count designated for the requested client.

  @param hClient [in] -- Handle to the client.
  @param *pClients[in] -- Pointed to linked list of client reference counts.

  @return
  ClockClientRefCountType * if found; NULL otherwise.
*/
ClockClientRefCountType * Clock_GetClientRefCount
(
  ClockHandle              hClient,
  ClockClientRefCountType *pClients
);


/*=========================================================================
**  Function : Clock_InsertRefCountClient
** =========================================================================*/
/**
  Insert reference count for client/resource tuple in resource linked list.

  @param hClient [in] -- Handle to the client.
  @param *pClients[in] -- Pointed to linked list of client reference counts.

  @return
  CLOCK_SUCCESS -- Successfully inserted ref count into linked list.
  CLOCK_ERROR -- Failed to insert ref count into linked list.
*/
ClockResult Clock_InsertRefCountClient
(
  ClockHandle               hClient,
  ClockClientRefCountType **pClients
);


/*=========================================================================
**  Function : Clock_AttachPD
** =========================================================================*/
/**
  PD-specific version of client attach API.

  @param hClient [in/out] -- Handle to the client.
  @param nPDId [in] -- Unique PD identifier.
  @param szName [in] -- Unique string identifier for client.

  @return
  CLOCK_SUCCESS -- Successfully attached (hClient/pDataFwk updated).
  CLOCK_ERROR -- Failed to attach.
*/
ClockResult Clock_AttachPD
(
  ClockHandle *hClient,
  int          nPDId,
  const char  *szName
);


/*=========================================================================
**  Function : Clock_InsertLLNode
** =========================================================================*/
/**
  Inserts node into linked list of like resources.

  @param pListHead [in] -- Pointer to head of list.
  @param pNode [in] -- Pointer to node being inserted into list.

  @return
  None.
*/
void Clock_InsertLLNode
(
  ClockLLNodeType **pListHead,
  ClockLLNodeType  *pNode
);


/*=========================================================================
**  Function : Clock_RemoveLLNode
** =========================================================================*/
/**
  Removes node from linked list of like resources.

  @param pListHead [in] -- Pointer to head of list.
  @param pNode [in] -- Pointer to node being removed from list.
  @param pfCleanup [in] -- Optional pointer to function that performs deep
                           deletion of node contents.

  @return
  CLOCK_SUCCESS -- Successfully removed from linked list.
  CLOCK_ERROR -- Failed to remove from linked list.
*/
ClockResult Clock_RemoveLLNode
(
  ClockLLNodeType **pListHead,
  ClockLLNodeType  *pNode,
  ClockCleanupFunc  pfCleanup
);


/*=========================================================================
**  Function : Clock_InitSourcesSoft
** =========================================================================*/
/**
  Initialize context data that requires dynamic memory allocation for sources.

  @return
    CLOCK_SUCCESS - Contexts were setup.
    CLOCK_ERROR - Something unexpected prevented setup.
*/
ClockResult Clock_InitSourcesSoft
(
  void
);


/*=========================================================================
**  Function : Clock_EnableSourcePostProcess
** =========================================================================*/
/**
  Hook for images to perform any post 'source enable' event processing.

  @param pClientRefCount - Pointer to ref count for this client.
  @param pSource - Pointer to source node.

  @return
  None.
*/
void Clock_EnableSourcePostProcess
(
  ClockClientRefCountType *pClientRefCount,
  ClockSourceNodeType     *pSource
);


/*=========================================================================
**  Function : Clock_DisableSourcePostProcess
** =========================================================================*/
/**
  Hook for images to perform any post 'source disable' event processing.

  @param pClientRefCount - Pointer to ref count for this client.
  @param pSource - Pointer to source node.

  @return
  None.
*/
void Clock_DisableSourcePostProcess
(
  ClockClientRefCountType *pClientRefCount,
  ClockSourceNodeType     *pSource
);


/*=========================================================================
**  Function : Clock_CreatePDEventProcess
** =========================================================================*/
/**
  Hook for images to perform any post 'PD creation' event processing.

  @param pPD - Pointer to PD context.

  @return
  None.
*/
void Clock_CreatePDEventProcess
(
  ClockPDCtxt *pPD
);


/*=========================================================================
**  Function : Clock_DestroyPDEventProcess
** =========================================================================*/
/**
  Hook for images to perform any post 'PD destruction' event processing.

  @param pPD - Pointer to PD context.

  @return
  None.
*/
void Clock_DestroyPDEventProcess
(
  ClockPDCtxt *pPD
);


/*=========================================================================
**  Function : Clock_GetRailNode
** =========================================================================*/
/**
  Return a pointer to the rail node for a given rail name.

  @param szRail [in] -- Name of the NPA node of the rail to look up.

  @return
  ClockRailType* if found; NULL otherwise.

*/
ClockRailType *Clock_GetRailNode(const char *szRail);


/*=========================================================================
**  Function : Clock_GetFrequencyPlan
** =========================================================================*/
/**
  See DDIClock.h. Legacy until we can move clients to Clock_Query.
*/
ClockResult Clock_GetFrequencyPlan
(
  ClockHandle         hClient,
  ClockIdType         ClockId,
  ClockFreqPlanType **aFreqPlan,
  uint32_t           *nSize
);


/*=========================================================================
**  Function : Clock_GetDomainNumPerfLevels
** =========================================================================*/
/**
  Get the number of supported performance levels for a given domain.

  @param pDomain[in] -- Domain for which to return the performance levels.

  @return
  uint32_t -- Number of supported performance levels.
*/
uint32_t Clock_GetDomainNumPerfLevels
(
  ClockDomainNodeType *pDomain
);


/*=========================================================================
**  Function : Clock_GetDomainPerfLevelConfig
** =========================================================================*/
/**
  Get frequency configuration for a given performance level.

  @param pDomain[in] -- Domain for which to return the performance level.
  @param nPerfLevel[in] -- Which performance level to return.

  @return
  ClockMuxConfigType* if supported performance level; NULL otherwise.
*/
ClockMuxConfigType *Clock_GetDomainPerfLevelConfig
(
  ClockDomainNodeType *pDomain,
  uint32_t             nPerfLevel
);


/* =========================================================================
**  Function : Clock_MapAlias
** =========================================================================*/
/**
  Map from alias to actual HW name.

  Map from a generic alias to the actual name specified by HW. If there
  is a mapping for the requested alias, then the actual HW name is copied
  into szNameBuf. If there is no mapping, then the requested alias is copied
  instead.

  Note: CLOCK_MAX_NAME_LEN can be used to allocate a buffer large enough
        to store the mapped name.

  @param hClient [in] Handle to the client.
  @param szAlias[in] Alias to map.
  @param szNameBuf[out] Output buffer where mapped alias is copied.
  @param nNameBufLen[in] szNameBuf length.

  @return
  CLOCK_ERROR_INVALID_PARAMETER -- Null pointer or invalid client identifier.
  CLOCK_ERROR_INSUFFICIENT_BUFFER_LEN -- szNameBuf not large enough for mapped name.
  CLOCK_ERROR_INTERNAL -- Error executing this function.
  CLOCK_ERROR_NOT_SUPPORTED -- Function not supported.
  CLOCK_SUCCESS -- Mapped name copied to szNameBuf.
*/
ClockResult Clock_MapAlias
(
  ClockHandle  hClient,
  const char  *szAlias,
  char        *szNameBuf,
  uint32_t     nNameBufLen
);


/*
 * Object-specific functions that implement generic Clock.h versions. These
 * could be removed if the internal driver code switches to the public
 * interfaces, but for now keeping them to reduce the amount of driver code
 * churn.
 */
ClockResult Clock_GetClockId(ClockHandle hClient, const char  *szName,ClockIdType *pId);
ClockResult Clock_GetDebugMuxId(ClockHandle hClient, const char *szName, ClockIdType *pId);
ClockResult Clock_GetDividerId(ClockHandle hClient, const char *szName, ClockIdType *pId);
ClockResult Clock_GetPowerDomainId(ClockHandle hClient, const char *szName, ClockIdType *pId);
ClockResult Clock_GetSourceId(ClockHandle hClient, const char *szName, ClockIdType *pId);
ClockResult Clock_EnableClockEx(ClockHandle hClient, ClockIdType ClockId, uint32_t nFlags);
#define Clock_EnableClock(hClient, ClockId) \
  Clock_EnableClockEx(hClient, ClockId, 0)
ClockResult Clock_EnablePowerDomain(ClockHandle hClient, ClockIdType PowerDomainId);
ClockResult Clock_EnableSource(ClockHandle hClient, ClockIdType SourceId);
ClockResult Clock_DisableClockEx(ClockHandle hClient, ClockIdType ClockId, uint32_t nFlags);
#define Clock_DisableClock(hClient, ClockId) \
  Clock_DisableClockEx(hClient, ClockId, 0)
ClockResult Clock_DisablePowerDomain(ClockHandle hClient, ClockIdType PowerDomainId);
ClockResult Clock_DisableSource(ClockHandle hClient, ClockIdType SourceId);
ClockResult Clock_SetClockFrequency(ClockHandle hClient, ClockIdType ClockId, uint32_t nFreq,ClockFrequencyType eMatch, uint32_t *pnResultFreq);
ClockResult Clock_SetSourceFrequency(ClockHandle hClient, ClockIdType SourceId, uint32_t nFreq, ClockFrequencyType eMatch, uint32_t *pnResultFreq);
ClockResult Clock_GetClockFrequency(ClockHandle hClient, ClockIdType ClockId, uint32_t *pnFrequencyHz);
ClockResult Clock_GetSourceFrequency(ClockHandle hClient, ClockIdType SourceId, uint32_t *pnFrequencyHz);
ClockResult Clock_IsClockEnabled(ClockHandle hClient, ClockIdType ClockId, bool *pbIsEnabled);
ClockResult Clock_IsClockOn(ClockHandle hClient, ClockIdType ClockId, bool *pbIsOn);
ClockResult Clock_SetClockDivider(ClockHandle hClient, ClockIdType ClockId, uint32_t nDivider);
ClockResult Clock_SetDividerDivider(ClockHandle hClient, ClockIdType DividerId, uint32_t nDivider);
ClockResult Clock_ConfigClock(ClockHandle hClient, ClockIdType ClockId, ClockConfigType eConfig);
ClockResult Clock_MeasureClockFrequency(ClockHandle hClient, ClockIdType ClockId, uint32_t *pnFrequencyHz);
ClockResult Clock_QueryClock(ClockHandle hClient, ClockIdType ClockId, ClockQueryType eQuery, uint32_t nIndex, ClockQueryResultType *pResult);


#endif /* !__CLOCK_DRIVER_H__ */
