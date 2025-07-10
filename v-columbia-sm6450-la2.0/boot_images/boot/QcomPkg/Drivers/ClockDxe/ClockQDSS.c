/*
===========================================================================
*/
/**
  @file ClockQDSS.c

*/
/*
  ====================================================================

  Copyright (c) 2021 Qualcomm Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================
  $Header: //components/rel/core.boot/6.0/QcomPkg/Drivers/ClockDxe/ClockQDSS.c#2 $
  $DateTime: 2021/07/13 16:02:24 $
  $Author: pwbldsvc $
  ====================================================================
*/

/*=========================================================================
      Include Files
==========================================================================*/

#include <stdio.h>
#include "ClockQMP.h"
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EFINpa.h>


/*=========================================================================
      Macros
==========================================================================*/

#define CLOCK_QDSS_BUFFER_SIZE  64
#define ARR_SIZE( a )  ( sizeof( (a) ) / sizeof( (a[0]) ) )

  
/*=========================================================================
      Prototypes
==========================================================================*/

static npa_resource_state Clock_NPAQDSSNodeDriverFunc
(
  npa_resource       *pResource,
  npa_client_handle   hClient,
  npa_resource_state  nState
);


/*=========================================================================
      Data
==========================================================================*/

/*
 * Clock QDSS NPA resources.
 */
static npa_resource_definition Clock_aNPAQDSSResources[] =
{
  {
    .name       = "/clk/qdss",
    .units      = "State",
    .plugin     = &npa_max_plugin,
    .attributes = NPA_RESOURCE_DEFAULT,
    .max        = NPA_MAX_STATE,
    .data       = "qdss",
  },
  {
    .name       = "/clk/qdss_ao",
    .units      = "State",
    .plugin     = &npa_max_plugin,
    .attributes = NPA_RESOURCE_DEFAULT,
    .max        = NPA_MAX_STATE,
    .data       = "qdss_ao",
  },
};

/*
 * Clock QDSS NPA node.
 */
static npa_node_definition Clock_NPAQDSSNode =
{
  .name           = "/node/clk/qdss",
  .driver_fcn     = Clock_NPAQDSSNodeDriverFunc,
  .attributes     = NPA_NODE_DEFAULT,
  .resource_count = ARR_SIZE(Clock_aNPAQDSSResources),
  .resources      = Clock_aNPAQDSSResources,
};


/*=========================================================================
      Functions
==========================================================================*/

/* =========================================================================
**  Function : Clock_InitQDSS
** =========================================================================*/
/**
  See ClockImage.h
*/
ClockResult Clock_InitQDSS
(
  void
)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_NPA_PROTOCOL *QDSSNpaProtocol = NULL;
  npa_client_handle reqClientLocal = NULL;

  Status = Clock_QmpInit();

  if (EFI_ERROR(Status))
  {
    DEBUG((EFI_D_ERROR, "QDSS glink init fail\n"));
    return CLOCK_ERROR;
  }

  Status = gBS->LocateProtocol(&gEfiNpaProtocolGuid, NULL, (void**)&QDSSNpaProtocol);
  if (EFI_ERROR(Status))
  {
    DEBUG((EFI_D_ERROR, "Cannot locate NPA protocol\n"));
    return CLOCK_ERROR;
  }

  Status = QDSSNpaProtocol->DefineNodeCb(&Clock_NPAQDSSNode, NULL, NULL, NULL);
  if (EFI_ERROR(Status))
  {
    DEBUG((EFI_D_ERROR, "Cannot define QDSS NPA node\n"));
    return CLOCK_ERROR;
  }

  Status = QDSSNpaProtocol->CreateSyncClientEx(
             "/clk/qdss",                                                  
             "UEFI Clock QDSS req client",                                                
             NPA_CLIENT_REQUIRED,
             0,
             NULL,
             &reqClientLocal);
             
  if (EFI_ERROR(Status))
  {
    DEBUG((EFI_D_ERROR, "Cannot create QDSS client\n"));
    return CLOCK_ERROR;
  }

  Status = QDSSNpaProtocol->ScalarRequest(
              reqClientLocal,        
              CLOCK_QDSS_LEVEL_DEBUG);

  if (EFI_ERROR(Status))
  {
    DEBUG((EFI_D_ERROR, "Cannot send QDSS request\n"));
    return CLOCK_ERROR;
  }            

  Clock_QmpDeInit();
  return CLOCK_SUCCESS;

} /* END Clock_InitQDSS */


/* =========================================================================
**  Function : Clock_NPAQDSSNodeDriverFunc
** =========================================================================*/
/**
  QDSS NPA node driver function.

  @param *pResource [in] -- Pointer to resource whose state changed.
  @param hClient    [in] -- Client handle that triggered the change.
  @param nState     [in] -- New request state.

  @return
  npa_resource_state -- The new active state of the resource.

  @dependencies
  None.
*/

static npa_resource_state Clock_NPAQDSSNodeDriverFunc
(
  npa_resource       *pResource,
  npa_client_handle   hClient,
  npa_resource_state  nState
)
{
  const char      *szResource = pResource->definition->data;
  char             szRequest[CLOCK_QDSS_BUFFER_SIZE];
  int              nChar;
  glink_err_type   eGLinkErr;

  if (hClient->type == NPA_CLIENT_INITIALIZE)
  {
    return 0;
  }

  nChar = snprintf(szRequest, CLOCK_QDSS_BUFFER_SIZE,
    "{class: clock, res: %s, val: %d}", szResource, nState);

  if (nChar < 0 || nChar >= CLOCK_QDSS_BUFFER_SIZE)
  {
    DEBUG((EFI_D_ERROR, "QDSS request buffer too small. Size is %d. Tried to write %d.",
      CLOCK_QDSS_BUFFER_SIZE, nChar + 1));
    return pResource->active_state;
  }

  eGLinkErr = Clock_QmpSendMsg(szRequest, CLOCK_QDSS_BUFFER_SIZE);
  if (EFI_ERROR(eGLinkErr))
  {
    DEBUG((EFI_D_ERROR, "Unable to send QDSS request to AOP: 0x%x.", eGLinkErr));
    return pResource->active_state;
  }

  return nState;

} /* END Clock_NPAQDSSNodeDriverFunc */


