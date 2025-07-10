/*============================================================================
@file npa_resource.h

NPA Resource Function/Structure Declarations

This file should be included only by people defining NPA resources or writing
plugins, NOT by NPA clients. The latter should use see npa.h

Copyright (c) 2009-2020 Qualcomm Technologies, Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary

==========================================================================*/
#ifndef NPA_RESOURCE_H
#define NPA_RESOURCE_H

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include <npa.h>
#include <npa_resource_common.h>

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------
 * NPA Resource API
 * -------------------------------------------------------------------------*/

/**
 * <!-- npa_define_node_cb -->
 *
 * @brief Define a new NPA node with an optional registration of a creation
 * completed callback. 
 *
 * Define a new node.  Simply adding the definition of a new node may
 * not be sufficient to create the node and all of its associated
 * resources and add it to the resource graph.  In order to construct
 * the node/resources, all of the nodes' dependencies must exist. When
 * all the dependencies exist, the resource will be constructed,
 * initialized, and added to the resource graph.  Only after the
 * resource is initialized and added to the graph can clients be
 * created against it.
 * 
 * Resource names must be globally unique. A resource will not be
 * created if there is already an existing resource with the same
 * name and a fatal error will be triggered
 * 
 * The initial state vector must have an initial state value for each
 * resource defined by the given node.  Behavior is undefined if the
 * initial state vector has a different size than the resource vector.
 * 
 * The define_event callback will be invoked after the node is fully
 * constructed.  The callback can be NULL if creation notification is
 * unneeded. If invoked, the callback arguments are (context, 0,
 * node->name, sizeof(const char *)).
 * 
 * @param node : Definition of node to be created 
 * @param initial_state : State vector to initialize the resources with 
 * @param define_cb : Optional callback to be invoked upon successful 
 *        creation of the node.  
 * @param context : User supplied context argument
 */
void npa_define_node_cb( npa_node_definition *node, 
                         npa_resource_state   initial_state[],
                         npa_callback         node_cb,
                         void                *context);



/**
 * <!-- npa_alias_resource_cb -->
 *
 * @brief Create an alias for an existing resource with an optional
 * registration of a creation completed callback. 
 *
 * This allows the same resource to be accessed with
 * multiple names.
 *
 * The alias doesn't exist until alias_event is triggered
 *
 * An error fatal will occur if there is already a resource with the
 * requested alias name
 *
 * @param resource_name : The name of the resource to be linked
 * @param alias_name : The alias for the resource
 * @param alias_cb : Optional callback to be invoked upon successful
 *        alias creation of the alias.  The arguments will be ( context,
 *        0, *alias_name, strlen(alias_name) )
 * @param context : User supplied context argument
 */ 
void npa_alias_resource_cb( const char   *resource_name, 
                            const char   *alias_name,
                            npa_callback  alias_cb,
                            void         *context);

/**
 * <!-- npa_define_marker -->
 *
 * @brief Define an npa marker
 *
 * A marker is a name in the npa resource space.  It allows
 * users/subsystems to signal existence without having to define a
 * full NPA resource.
 *     
 * Markers can be listed as dependencies, or used to trigger a
 * resource_available callback, however markers do not support client
 * requests and do not have a meaningful state.  In order to depend
 * on a marker, a resource should define the dependency's client type
 * as NPA_NO_CLIENT.  Dependencies defined as NPA_NO_CLIENT will
 * cause node creation to be properly dependent, but will not
 * allocate a client.
 *
 * An error fatal will occur if there is already a resource with the
 * requested marker name
 *
 * @param marker_name : The name of the marker to create.  The string
 *        is not copied, so the pointer must point to a static string.
 *
 */ 
void npa_define_marker( const char *marker_name );


/**
 * <!-- npa_define_marker_with_attributes -->
 *
 * @brief Define an npa marker with specific resource attribute(s)
 *
 * A marker is a name in the npa resource space.  It allows
 * users/subsystems to signal existence without having to define a
 * full NPA resource.
 *  
 * Markers can be listed as dependencies, or used to trigger a
 * resource_available callback, however markers do not support client
 * requests and do not have a meaningful state.  In order to depend
 * on a marker, a resource should define the dependency's client type
 * as NPA_NO_CLIENT.  Dependencies defined as NPA_NO_CLIENT will
 * cause node creation to be properly dependent, but will not
 * allocate a client.
 *
 * An error fatal will occur if there is already a resource with the
 * requested marker name
 *
 * This function only supports the resource attribute
 * NPA_RESOURCE_INTERPROCESS_ACCESS_ALLOWED for now. This is to
 * allow markers to work across address space. If it is called
 * with other attributes, there will be an error fatal.
 * 
 * @param marker_name : The name of the marker to create.  The string
 *        is not copied, so the pointer must point to a static string.
 * @param attributes: the resource attribute(s) of the marker
 */
void npa_define_marker_with_attributes( const char             *marker_name,
                                        npa_resource_attribute  attributes );


/**
 * <!-- npa_stub_resource -->
 *
 * @brief Define an stub resource
 *
 * Stub resources are used to satisfy dependencies, similar to
 * markers, but they allow clients to be created, requests issued,
 * etc.  A stub resource does not do anything with client requests,
 * and will always have a state of 0
 *
 * Currently it is an error to redefine a resource defined as a stub
 * resource, either as another stub or as a real resource.  It is
 * hoped that future versions of the framework will allow stub
 * resources to be redefined as real resources.
 * 
 * @param stub_name : The name of the marker to create.  The string
 *        is not copied, so the pointer must point to a static string.
 */ 
#define npa_stub_resource( stub_name ) \
  npa_alias_resource_cb( "/dev/null", stub_name, NULL, NULL );


/*======================================================================
  Author API

  These are special purpose functions intended for use by the node
  author.  
  ======================================================================*/

/** 
 * <!-- npa_issue_dependency_request -->
 *
 * @brief Issue a request to a dependency
 *
 * This function may be used by a resource to issue a request to its
 * dependency. It takes the current client to the resource as one of its
 * parameters and issues a required request, a suppressible request or both
 * on the appropriate dependency client handles, based on the current client's
 * type and request attributes.
 *
 * @param cur_client : The current client to the resource that is invoking this
 *                     routine
 * @param req_client : The required client handle to the resource's 
 * dependency. If there is no required client, pass NULL.
 * @param req_state : A required request to place on the dependency
 * @param sup_client : The suppressible client handle to the resource's 
 * dependency. If there is no suppressible client, pass NULL
 * @param sup_state : A suppressible request to place on the dependency
 */
void npa_issue_dependency_request( npa_client_handle cur_client,
                                   npa_client_handle req_client,
                                   npa_resource_state req_state,
                                   npa_client_handle sup_client,
                                   npa_resource_state sup_state );


/** 
 * <!-- npa_issue_dependency_vector_request -->
 *
 * @brief Issue a vector request to a dependency 
 *
 * This function may be used by a resource to issue a request to its
 * dependency. It takes the current client to the resource as one of its
 * parameters and issues a required request, a suppressible request or both
 * on the appropriate dependency client handles, based on the current client's
 * type and request attributes.
 *
 * @param cur_client : The current client to the resource that is invoking this
 *                     routine
 * @param req_client : The required client handle to the resource's 
 * dependency. If there is no required client, pass NULL.
 * @param req_num_elems : Number of elements in the required vector request
 * @param req_vector : A required vector request to place on the dependency
 * @param sup_client : The suppressible client handle to the resource's 
 * dependency. If there is no suppressible client, pass NULL
 * @param sup_num_elems : Number of elements in the suppressible vector request
 * @param sup_vector : A suppressible vector request to place on the dependency
 */
void npa_issue_dependency_vector_request( npa_client_handle cur_client,
                                          npa_client_handle req_client,
                                          unsigned int req_num_elems,
                                          npa_resource_state *req_vector,
                                          npa_client_handle sup_client,
                                          unsigned int sup_num_elems,
                                          npa_resource_state *sup_vector );


/**
 * <!-- npa_assign_resource_state -->
 *
 * @brief Assign the resource state directly, bypassing the update and
 * driver functions.  This will trigger events as necessary.
 *
 * This function is intended for use in a compound node when one
 * resource's state change can cause another coupled resource's state
 * to change. This function must be called from within the node's
 * atomic section - which means it can be invoked from within the
 * update or driver function.  It require the npa_resource *, which
 * can be retrieved for coupled resources from the current resource
 * by the NPA_RESOURCE macro.
 *
 * @param resource : Resource whose state is changing
 * @param state : New state of the resource
 */
void npa_assign_resource_state( npa_resource       *resource,
                                npa_resource_state  state );


/**
 * <!-- npa_query_get_resource -->
 *
 * @brief Retrieve the resource associated with the given query handle.
 *
 * This function is intended to be used by resources that wish to define a
 * query API that goes beyond what npa_resource_query_fcn can support.
 *   
 * @param query_handle : Handle to resource being queried
 *
 * @return Pointer to resource associated with the query handle
 */
npa_resource *npa_query_get_resource( npa_query_handle query_handle ); 


/**
 * <!-- npa_enable_node -->
 *
 * @brief Enable/re-enable the given node.  
 *
 * If the node being enabled is not currently defined, this node is
 * assumed to be hotpluggable.  In this case, this function will make a
 * copy of all the relevant node data and define the node for the user.
 * This copy allows the user definition of the node to be removed at a
 * later time, through the function npa_disable_node().  If this enable
 * call is defining the node, resources within the node may not be
 * available upon completion of the call depending on the node's
 * dependencies.  This mirrors the functionality of npa_define_node().
 *
 * If the node is being enabled for the first time, the default state
 * vector defines the initial state of the resource in the node. If the
 * node is being re-enabled, the resources will be reinitialized with
 * the previous resource state if the node has valid clients.  If no
 * clients exist, the resources will be re-initialized with the default
 * state vector. In either case, an enabled node will have its driver
 * function invoked with an INITIALIZE client, so it can reset as
 * necessary.  
 *
 * If the default state vector is NULL, resources will be initialized
 * to 0.
 *
 * Note: In order to enable a node, the node must have the
 * NPA_NODE_DISABLEABLE attribute defined and can not define the
 * NPA_NODE_NO_LOCK attribute
 *
 * Note: It is an error to attempt to enable/disable a node if the node
 * definition passed in is inconsistent (different resources,
 * dependencies, etc) with the node as defined in the resource graph.
 *
 * Note: This function may be used to construct a resource, much like
 * npa_define_node().  Unlike that function, this does not provide for
 * a callback when the node has been constructed. This is because the
 * callback functionality is only relevant if this call is being used
 * to define the resource (i.e., the first invocation) and not on
 * subsequent invocations, and if you are using this function in that
 * circumstance, the expectation is that the driver can be unloaded and
 * the framework has no way to validate the callback function pointer
 * and would be at risk of calling a function is not present
 *
 * @note If this call is being used to re-enable a previously disabled
 * node, the enable call must be made from the same thread that invoked
 * npa_disable_node.
 *
 * @param node : definition of node to be enabled
 * @param default_state : vector of default state for the node
 */
void npa_enable_node( npa_node_definition *node, npa_resource_state default_state[] );


/**
 * <!-- npa_disable_node -->
 *
 * @brief Disable the given node. 
 *
 * When a node is disabled, the node is first locked and all the node
 * dependency requests are canceled.  The node is then left in a locked
 * state, which prohibits other client operations from happening while
 * the node is disabled.
 *
 * A disabled node will still respond to queries and event registration
 * as these do not use the node lock.  Note that it is not currently
 * legal to disable a node with a custom query function. If necessary,
 * this restriction can be removed.
 *
 * Note: In order to enable a node, the node must have the
 * NPA_NODE_DISABLEABLE attribute defined and can not define the
 * NPA_NODE_NO_LOCK attribute
 *
 * Note: The behavior of this function is undefined if the node is
 * disabled before it has been fully constructed.
 *
 * @param node : Pointer to a node definition that is to be disabled
 */
void npa_disable_node( npa_node_definition *node ); 


/**
 * <!-- npa_fork_resource -->
 *
 * @brief Stubbed. Retained only for source compatibility with client code.
 *
 * @return Always NULL.
 */
npa_join_token npa_fork_resource( npa_resource       *resource,
                                  npa_join_function   join_func,
                                  void               *join_data );


/**
 * <!-- npa_resource_lock -->
 *
 * @brief  Lock the resource.
 *
 * If the resource is forked, it will be joined before this function returns.
 * Note that the resource shares its lock with other resources in the node.
 * So this will, in effect, lock the node.
 *
 * @param resource : Handle to the resource
 */
void npa_resource_lock( npa_resource *resource );


/**
 * <!-- npa_resource_unlock -->
 *
 * @brief  Unlock the resource (and by extension, the node) that was previously
 * locked by npa_resource_lock.
 *   
 * @param resource : Handle to the resource
 */
void npa_resource_unlock( npa_resource *resource );


/**
 * <!-- npa_request_has_request -->
 *
 * @brief Returns true if the current request  has the given attribute set.
 * 
 * Attributes may be set on client handles and this is cached in the resource
 * structure for the duration of the request.
 *
 * @param client : Handle to the client to check
 * @param attr : The attribute to test for
 *
 * @return TRUE if the attribute is present
 */
unsigned int npa_request_has_attribute( npa_client_handle     client,
                                        npa_request_attribute attr );


/**
 * <!-- npa_get_request_attributes -->
 *
 * @brief  Returns a bitset representing all  request attributes set on this client.
 *
 * @param client : Handle of the npa_client to read
 */
unsigned int npa_get_request_attributes( npa_client_handle client );


/**
 * <!-- npa_pass_request_attributes -->
 *
 * @brief Add request attributes of the 'current' client to the 'dependency' client.
 *
 * Does not unset any attributes set previously on the 'dependency' client.
 *
 * @param current : Handle of a npa_client whose attributes will be applied
 *                  to the other.
 * @param dependency : Handle of a npa_client whose attributes will be updated. 
 *
 * @return The dependency client handle passed in
 */
npa_client_handle  npa_pass_request_attributes( npa_client_handle current,
                                  npa_client_handle dependency );


/*======================================================================
  Plugin API
  ======================================================================*/
/**
 * <!-- npa_change_resource_plugin -->
 *
 * @brief Change the plugin for the given resource.
 *
 * The new plugin must support all the client work models supported by
 * the plugin that was in the resource definition.  If the new plugin
 * is NULL, the original plugin will be restored.
 *
 * If they exist, the client destroy function of the plugin being
 * replaced and the client create function of the new plugin will be
 * invoked for all clients of the resource.
 *
 * It is a fatal error to attempt to change the plugin for a resource
 * that does not exist.
 *
 * @param resource_name : name of the resource whose plugin is to be changed
 * @param plugin : new plugin to use, NULL to restore original plugin
 */
void npa_change_resource_plugin( const char                *resource_name,
                                 const npa_resource_plugin *plugin );


/*======================================================================
  Standard Plugins

  These plugins are intended for common cases.  If there is not one
  sufficient for the resource author's needs, they should create a new
  plugin.

  The plugins typically use the first two elements of the resource's
  internal state array. The binary_plugin/update function uses all
  4 elements of the internal state array.
  ======================================================================*/

/* Resource state is either max value or off(0) if there is atleast one active
   non-zero request or not, respectively */
extern const npa_resource_plugin npa_binary_plugin;

/* Resource state is the max of active requests */
extern const npa_resource_plugin npa_max_plugin;

/* Resource state is the min of active requests */
extern const npa_resource_plugin npa_min_plugin;

/* Resource state is the sum of active requests */
extern const npa_resource_plugin npa_sum_plugin;

/* Resource state is always the last client request, irrespective of
 * other client requests.
 *
 * This can be used if the resource requests are logical (enums or the
 * like) and the resource will examines the client request in the
 * driver function. */
extern const npa_resource_plugin npa_identity_plugin;

/* Resource state is always on (max value), irrespective of client requests */
extern const npa_resource_plugin npa_always_on_plugin;

/* Resource only supports impulse clients */
extern const npa_resource_plugin npa_impulse_plugin;

/* Resource state is the bitwise OR of active requests */
extern const npa_resource_plugin npa_or_plugin;

/* Resource state is the bitwise AND of active requests, with each request
   reduced to 0 or 1, depending on whether it was non-zero or zero */
extern const npa_resource_plugin npa_binary_and_plugin;

/* Resource supports no clients - used for markers */
extern const npa_resource_plugin npa_no_client_plugin;

/* Update functions used by the above plugins.
 * Resource authors who define custom client_create/destroy functions
 * will need to create their own plugins, but can use these routines
 * as their update functions.
 */

/** Min update */
npa_resource_state npa_min_update_fcn( npa_resource      *resource,
                                       npa_client_handle  client);

/** Max update */
npa_resource_state npa_max_update_fcn( npa_resource      *resource,
                                       npa_client_handle  client );

/** Sum update */
npa_resource_state npa_sum_update_fcn( npa_resource      *resource,
                                       npa_client_handle  client );
                                       
/** Binary update - see comment against plugin above */
npa_resource_state npa_binary_update_fcn( npa_resource      *resource,
                                          npa_client_handle  client );
                                          
/** Bitwise OR update */
npa_resource_state npa_or_update_fcn( npa_resource       *resource,
                                      npa_client_handle   client);
                                      
/** Binary AND update - see comment against plugin above */
npa_resource_state npa_binary_and_update_fcn( npa_resource       *resource,
                                              npa_client_handle   client);
                                      
/** Identity update */
npa_resource_state npa_identity_update_fcn( npa_resource      *resource,
                                            npa_client_handle  client );
                                     
/** Always On update */
npa_resource_state npa_always_on_update_fcn( npa_resource      *resource,
                                             npa_client_handle  client );
                                             
/** Impulse update */
npa_resource_state npa_impulse_update_fcn( npa_resource      *resource,
                                           npa_client_handle  client );
  
/* Helper macros to access aggregated required and suppressible states
   for scalar resources */
#define NPA_REQUIRED_INDEX      0
#define NPA_SUPPRESSIBLE_INDEX  1
#define NPA_SUPPRESSIBLE2_INDEX 2
#define NPA_SEMIACTIVE_INDEX    3

#define NPA_RESOURCE_REQUIRED_REQUEST( resource ) \
  MIN( resource->internal_state[NPA_REQUIRED_INDEX], resource->active_max )
#define NPA_RESOURCE_SUPPRESSIBLE_REQUEST( resource ) \
  MIN( resource->internal_state[NPA_SUPPRESSIBLE_INDEX], resource->active_max )
#define NPA_RESOURCE_SUPPRESSIBLE2_REQUEST( resource ) \
  MIN( resource->internal_state[NPA_SUPPRESSIBLE2_INDEX], resource->active_max )
#define NPA_RESOURCE_SEMIACTIVE_REQUEST( resource ) \
  MIN( resource->internal_state[NPA_SEMIACTIVE_INDEX], resource->active_max )

/* Helper macros to access aggregated required and suppressible states
   for vector resources. Only use with vector resources */
#define NPA_RESOURCE_REQUIRED_VECTOR( resource ) resource->required_state_vector
#define NPA_RESOURCE_SUPPRESSIBLE_VECTOR( resource ) \
  resource->suppressible_state_vector
  
/*======================================================================
  Internal Client API

  Note: The internal client type is created/destroyed via the standard
  client api. 
  ======================================================================*/

/**
 * <!-- npa_issue_internal_request -->
 *
 * @brief  Issue the INTERNAL client work request
 *
 * Note: The semantics of an internal client request are
 * resource/plugin specific, there's no general API for setting the
 * work request fields - it's the responsibility of the user to set the
 * internal client state appropriately outside of the framework.  This
 * function is used to issue the request after the internal fields have
 * been established.
 *
 * The client must be of INTERNAL work model. Clients with internal
 * client types are created/destroyed via the standard client api.
 *
 * @param client : handle to client being used
 */
void npa_issue_internal_request( npa_client_handle client );

/*======================================================================
  Event API
  ======================================================================*/

/**
 * <!-- npa_resource_add_system_event_callback -->
 *
 * @brief Add a system event callback function to a resource
 *  
 * The callback function will be invoked on such event modifications as follows:
 * 1) A change event is created or destroyed;
 * 2) A watermark or threshold event is enabled, disabled or destroyed;
 * 3) Event watermarks or thresholds are changed.
 *
 * When invoked, the callback arguments will be 
 * (context, 0, npa_event *, sizeof(npa_event) ); 
 *
 * Note: a resource supports only one system event callback, so it is an error
 * to add a second. It is hoped that future versions will relax this 
 * restriction.
 *
 * @param resource_name : name of the resource that is to be used
 * @param callback : callback to be invoked
 * @param context : context to be passed back in callback invocation
 *
 * @return NPA_SUCCESS on success, NPA_ERROR otherwise.
 */
npa_status npa_resource_add_system_event_callback( const char   *resource_name,
                                                   npa_callback  callback,
                                                   void         *context );


/**
 * <!-- npa_resource_remove_system_event_callback -->
 *
 * @brief Remove a system event callback function from a resource
 *  
 * The callback and context pointers should be the same as those when the 
 * callback is added.
 *
 * @param resource_name : name of the resource that is to be used
 * @param callback : callback to be invoked
 * @param context : context to be passed back in callback invocation
 *
 * @return NPA_SUCCESS on success, NPA_ERROR otherwise.
 */
npa_status npa_resource_remove_system_event_callback( const char   *resource_name,
                                                      npa_callback  callback,
                                                      void         *context );


/* Legacy API - invoke callback functions with dal_event callback.
 *
 * These calls are deprecated and should not be used by new code
 */
/**
 * <!-- npa_define_node_dal -->
 *
 * @brief  Define an NPA node
 *
 * Define a new node.  Simply adding the definition of a new node may
 * not be sufficient to create the node and all of its associated
 * resources and add it to the resource graph.  In order to construct
 * the node/resources, all of the nodes' dependencies must exist. When
 * all the dependencies exist, the resource will be constructed,
 * initialized, and added to the resource graph.  Only after the
 * resource is initialized and added to the graph can clients be
 * created against it.
 *
 * Resource names must be globally unique. A resource will not be
 * created if there is already an existing resource with the same
 * name and a fatal error will be triggered
 *  
 * The initial state vector must have an initial state value for each
 * resource defined by the given node.  Behavior is undefined if the
 * initial state vector has a different size than the resource vector.
 *  
 * The define_event will be triggered after the node is fully
 * constructed.  The define_event can be NULL if creation
 * notification is unneeded.
 *
 * If the event is a callback event, the arguments will be 
 * (user_data, 0, node->name, sizeof(const char *)).
 *
 * @param node : Definition of node to be created 
 * @param initial_state : State vector to initialize the resources with 
 * @param dal_event : Optional dal_event to be triggered upon
 *      successful creation of the node.  The arguments will be (
 *      context, 0, *alias_name, strlen(alias_name) )
 *
 * @note npa_define_node_cb is the prefered API for new code
 */
#define npa_define_node_dal( a, b, dal_event ) \
  npa_define_node_cb( a, b, NPA_DAL_CALLBACK(dal_event) )


/**
 * <!-- npa_define_node -->
 *
 * @brief Compatibility wrapper for npa_define_node_dal. 
 *
 * See npa_define_node_dal for API details.
 *
 * @note npa_define_node_cb is the preferred API for new code
 */
#define npa_define_node    npa_define_node_dal


/**
 * <!-- npa_alias_resource_dal -->
 *
 * @brief Create an alias for an existing resource.  This allows the same resource to be accessed with multiple names.
 *
 * The alias doesn't exist until alias_event is triggered
 *
 * An error fatal will occur if there is already a resource with the
 * requested alias name
 *
 * @param resource_name : The name of the resource to be linked
 * @param alias_name : The alias for the resource
 * @param dal_event : Optional event to be triggered upon successful
 *     alias creation of the alias.  
 * @param context : User supplied context argument
 *
 * @note  Legacy API - deprecated and should not be used by new code
 */
#define npa_alias_resource_dal( a, b, dal_event ) \
  npa_alias_resource_cb( a, b, NPA_DAL_CALLBACK(dal_event) ) 


/**
 * <!-- npa_define_node -->
 *
 * @brief Compatibility wrapper for npa_alias_resoruce_dal
 *
 * @note Legacy API - deprecated and should not be used by new code
 */
#define npa_alias_resource npa_alias_resource_dal

#ifdef __cplusplus
}
#endif

#endif /* NPA_RESOURCE_H */
