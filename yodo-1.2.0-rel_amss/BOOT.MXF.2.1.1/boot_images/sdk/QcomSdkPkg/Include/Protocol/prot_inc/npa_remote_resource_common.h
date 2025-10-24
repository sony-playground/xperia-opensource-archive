/*==========================================================================
@file npa_remote_resource_common.h

NPA Remoting API

Copyright (c) 2020 Qualcomm Technologies, Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary

============================================================================*/
#ifndef NPA_REMOTE_RESOURCE_COMMON_H
#define NPA_REMOTE_RESOURCE_COMMON_H

#include <npa_resource_common.h>

#ifdef __cplusplus
extern "C" {
#endif

/* NPA Remoting supports the fol. attributes in remote_resource definitions.
 * 
 * NPA_RESOURCE_REMOTE indicates that the resource is hosted remotely
 * and need not be explicitly specified. The attribute is set internally
 * by the framework within npa_remote_define_resource.
 *
 * NPA_RESOURCE_REMOTE_PROXY needs to be explicitly set in the remote
 * resource definition. All resources created via npa_remote_define_resource
 * are local proxies to remote resources. Although it is ultimately the
 * individual protocol that determines what to do when this attribute is set,
 * NPA recommends that this attribute be used to mean that the local proxy
 * mirrors the state of the remote resource. So, when a client issues a state
 * query, the protocol does something protocol-specific to read the actual
 * remote state, at the time of query. This is not required or enforced by NPA.
 *
 * NPA_RESOURCE_REMOTE_NO_INIT may be specified explicitly or is set
 * internally by the framework when local_aggregation_no_initial_request is
 * specified as the driver function. The protocol implementation is expected
 * to check for this attribute when client->type is NPA_CLIENT_INITIALIZE
 * and not issue an initial request to the remote resource, if set.
 */

/** @ingroup efi_npa_protocol_data
 *  Definition of a remote resource */
typedef struct npa_remote_resource_definition
{
  char                      *local_resource_name;
  char                      *remote_resource_name;
  char                      *protocol_type;
  const npa_resource_plugin *plugin;
  npa_resource_driver_fcn    driver_fcn; 
  const char                *units;
  npa_resource_state         max;           
  unsigned int               attributes;
  /** Data field for resource authors, access via resource->definition->data */
  npa_user_data              data;

 /** Handle to this resource; the field will be initialized in/by the framework
    when the node is created. Do not define or define as NULL */
  npa_resource *handle;
} npa_remote_resource_definition;

/** @ingroup efi_npa_protocol_data
 *  The continuation structure that is passed around from routine to routine
   during remote resource definition. The protocol query routine, when invoked
   with NPA_QUERY_REMOTE_RESOURCE_AVAILABLE, must cast 
   'npa_query_type->data.reference' into this type and use
   'npa_remote_node_continuation->node->name' as name of the remote resource
   whose availability is being sought.
 */
typedef struct npa_remote_node_continuation
{
  npa_node_definition *node;
  npa_resource_state   initial_state;
  npa_callback         callback;
  npa_user_data        cb_data;
  npa_remote_resource_definition *definition;
} npa_remote_node_continuation;

#ifdef __cplusplus
}
#endif

#endif /* NPA_REMOTE_RESOURCE_COMMON_H */
