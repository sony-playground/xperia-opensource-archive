/*============================================================================
@file npa_resource_common.h

NPA Resource Function/Structure Declarations

This file should be included only by people defining NPA resources or writing
plugins, NOT by NPA clients. The latter should use see npa.h

Copyright (c) 2009-2021 Qualcomm Technologies, Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary

==========================================================================*/
#ifndef NPA_RESOURCE_COMMON_H
#define NPA_RESOURCE_COMMON_H

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "npa_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------
 * Enumerations/Constants
 * -------------------------------------------------------------------------*/
/** @ingroup efi_npa_protocol_data
@{ */

/** 
 *  These is logically part of the npa_client_type enumeration, but
 * they aren't public client types.  Only resource authors should use
 * this type. */
#define NPA_CLIENT_INITIALIZE  NPA_CLIENT_RESERVED1
#define NPA_CLIENT_INTERNAL    NPA_CLIENT_RESERVED2
#define NPA_CLIENT_BATCH       NPA_CLIENT_RESERVED3

/** @} */ /* end_ingroup efi_npa_protocol_data */

/** @ingroup efi_npa_protocol_data
 *  Map client types enumerations onto bitfields for plugin usage.  The
 * plugin defines the supported plugins as the bitwise OR of supported
 * client types.
 *
 * If you add a new enum to the npa_client_type, this enum must be
 * updated to match 

 * Resource attributes are used to override default resource behavior */
typedef enum
{
  /** Use default resource behavior */ 
  NPA_RESOURCE_DEFAULT              = 0,          

  /** Invoke the driver function unconditionally - not just on state changes */
  NPA_RESOURCE_DRIVER_UNCONDITIONAL = 0x00000001, 

  /** Only allow one client of the resource to be created at a time */
  NPA_RESOURCE_SINGLE_CLIENT        = 0x00000002, 

  /** This resource is a vector resource */
  NPA_RESOURCE_VECTOR_STATE = 0x00000004, 

  /** Allow resource to be accessed remotely */
  NPA_RESOURCE_REMOTE_ACCESS_ALLOWED = 0x00000008, 

  /** Allow resource to be accessed from another process */
  NPA_RESOURCE_INTERPROCESS_ACCESS_ALLOWED = 0x00000008,
  
  /** Is a remote resource; set by the framework for all remote resources
     The value of this enum is used in NPADump.cmm (is_remote). Keep in sync */
  NPA_RESOURCE_REMOTE = 0x00000010,
  
  /** A state query to remote resources with this attribute returns
     remote state, if supported by protocol */
  NPA_RESOURCE_REMOTE_PROXY = 0x00000020,
  
  /** Is a remote resource that must not be initialized by NPA */
  NPA_RESOURCE_REMOTE_NO_INIT = 0x00000040,
  
  /** Resource supports suppressible requests; Vector resources or scalars with
   * custom update functions may use this attribute to tell NPA that they
   * aggregate required requests SEPARATELY into resource->required_state_vector
   * or NPA_RESOURCE_REQUIRED_REQUEST(resource) respectively. As before, the
   * overall aggregation must be in resource->state_vector or the return value
   * from the update function, respectively.
   */
  NPA_RESOURCE_SUPPORTS_SUPPRESSIBLE = 0x00000080,

  /** Vector resources that support suppressible requests AND have a
   * SUPPRESSIBLE dependency to another resource may define this attribute.
   * Alongside enabling NPA_RESOURCE_SUPPORTS_SUPPRESSIBLE,
   * it asks NPA to allocate a vector for the resource to aggregate
   * its suppressible requests separately. This vector may be accessed via
   * resource->suppressible_state_vector
   */
  NPA_RESOURCE_ALLOC_SUPPRESSIBLE_VECTOR = 0x00000180,

  /** Invoke the driver function unconditionally for the first request 
     to the resource */
  NPA_RESOURCE_DRIVER_UNCONDITIONAL_FIRST = 0x00000200,

  /** One-shot attribute that will cause the next request to the resource
   * to invoke the driver function, so long as the client is not issuing
   * a redundant request. The attribute is unset by the framework after
   * such a request. Set to the same value as UNCONDITIONAL_FIRST since
   * the latter only applies to the first request to the resource.
   */
  NPA_RESOURCE_DRIVER_UNCONDITIONAL_NEXT = 
                      NPA_RESOURCE_DRIVER_UNCONDITIONAL_FIRST,

  /** Allow NPA scheduler to fork a request to this resource in its LPR */
  NPA_RESOURCE_LPR_ISSUABLE = 0x00000400,

  /** Allows clients to switch type between required and suppressible */
  NPA_RESOURCE_ALLOW_CLIENT_TYPE_CHANGE = 0x00000800,
  
  /** Pre- and post-change events are enabled by default for all resources.
     The below attribute is provided for source-compatibility purposes */
  NPA_RESOURCE_ENABLE_PREPOST_CHANGE_EVENTS = 0x00001000,
  
  /** All IMPULSE requests will call the driver function, irrespective
     of the output of the update function */
  NPA_RESOURCE_IMPULSE_UNCONDITIONAL = 0x00002000,
  
  /** Gather request count and max durations for this resource */
  NPA_RESOURCE_GATHER_STATS = 0x00004000,

  /** The dump script will output resource state/client votes etc.
     in hex, if this attribute is set */
  NPA_RESOURCE_DUMP_STATE_HEX = 0x00008000,

} npa_resource_attribute;

/** @ingroup efi_npa_protocol_data */
typedef enum
{
  NPA_NODE_DEFAULT              = 0, /** Use default node behavior */

  /** Don't create a lock for this node.  If this attribute is defined,
   * it is the responsibility of the resource author to manage
   * concurrency.  */
  NPA_NODE_NO_LOCK              = 0x00000001,

  /** This node can be disabled at runtime */
  NPA_NODE_DISABLEABLE          = 0x00000002,

  /** This node is capable of forking; ignored */
  NPA_NODE_FORKABLE             = 0x00000004,

} npa_node_attribute;


/** @ingroup efi_npa_protocol_data 
 * Resource author query ids.  All resource author queries ids are in
 * 1024-2047 of the reserved section */
enum {
  NPA_RESOURCE_AUTHOR_QUERY_START = NPA_MAX_PUBLIC_QUERY,
  /** Get the resource attribute vector */
  NPA_QUERY_RESOURCE_ATTRIBUTES,
  /** Get the node attribute vector */
  NPA_QUERY_NODE_ATTRIBUTES,
  NPA_MAX_RESOURCE_AUTHOR_QUERY = 2047
};


/*----------------------------------------------------------------------------
 * Types/Typedefs
 * -------------------------------------------------------------------------*/
/** @ingroup efi_npa_protocol_data
 * User data - user defines (and must cast) to whatever they want */
typedef void * npa_user_data;


/** @ingroup efi_npa_protocol_data
 * Internal callback structure */
typedef struct npa_callback_event
{
  npa_callback  callback;
  npa_user_data context;
} npa_callback_event;


/** @ingroup efi_npa_protocol_data
 * Internal work request structure */
typedef struct npa_work_request
{
  npa_resource_state  state;    /** Valid for all */
  union                         /** Used for reference data */
  {
    npa_resource_state *vector;
    char               *string;
    void               *reference;
  } pointer;
  npa_resource_time   start;      /** valid for all */
  npa_resource_time   end;        /** Valid for ISOC */
  /** TODO: Frequency? Blob for adaptive data? */
} npa_work_request;


/** @ingroup efi_npa_protocol_data
 * npa_client structure definition */
typedef struct npa_client 
{
  struct npa_client       *prev, *next;   /** Linked list */
  const char              *name;          /** Name of element */
  const char              *resource_name; /** Creation name of resource
                                           * (may be alias)  */
  struct npa_resource     *resource;      /** Resource element is linked
                                           * to */
  npa_user_data            resource_data; /** Arbitrary resource data */
  npa_client_type          type;          /** Client type */
  npa_work_request         work[2];       /** Use ACTIVE/PENDING_REQUEST
                                           * macros to access */
  unsigned int             index;         /** Last request serviced */
  unsigned int             sequence;      /** Sequence number */
  struct npa_continuation *continuation;  /** Continuation */
  void                    *log_handle;    /** ULog handle associated with
                                           * a client */

  unsigned int             request_attr;  /** Request attributes */

  void (*issue_request)( npa_client_handle client, int new_request ); 
                                          /** Issue request function Sync/Async
                                          */

  struct npa_scheduler_data *request_ptr; /** Scheduler data structures.
                                           * NULL means schedule requests
                                           * have not been initialized yet. 
                                           */
} npa_client;


/** @ingroup efi_npa_protocol_data
 *  Helper macros for accessing the correct request structure, as they
 * are double buffered
 *
 * TODO: These macros will need to change if the buffering gets
 * greater than double buffered */

/* Access requests being processed */
#define NPA_ACTIVE_REQUEST( client )  ((client)->work[((client)->index)])
#define NPA_PENDING_REQUEST( client ) ((client)->work[((client)->index)^1])


/** @ingroup efi_npa_protocol_data
 * Remap request for NPA_MAX_STATE into request for the maximum of the
 * current resource
 *
 * This macro is for use in plugin functions */
#define NPA_REMAP_MAX_REQUEST( resource, client )                       \
  NPA_PENDING_REQUEST(client).state =                                   \
    (NPA_PENDING_REQUEST(client).state == NPA_MAX_STATE) ?              \
    client->resource->definition->max : NPA_PENDING_REQUEST(client).state


/** @ingroup efi_npa_protocol_data 
 * Event structure definition */
typedef struct npa_event
{
  struct npa_event          *prev, *next;    /** Linked list */
  const char                *name;           /** Event Name */
  const char                *resource_name;  /** Name of resource 
                                                (may be alias) */
  struct npa_resource       *resource;       /** Resource event is linked to */
  unsigned int               trigger_type;   /** Bitfield of one/more enums
                                                from npa_event_trigger_type */
  union 
  {
    npa_resource_state_delta watermark;
    npa_resource_state       threshold;
  } lo;
  union 
  {
    npa_resource_state_delta watermark;
    npa_resource_state       threshold;
  } hi;
  npa_callback_event         callback;       /** Callback */
} npa_event;

/** @ingroup efi_npa_protocol_data */
typedef union npa_event_list
{
  struct npa_event_header  *event_header;
  npa_event                *event;
}npa_event_list;

/** @ingroup efi_npa_protocol_data  
 * Return a pointer to the first event in a resource's event list */
#define NPA_EVENT_FIRST_EVENT( evt )  ( evt->resource->events.event_header->event )
/** @ingroup efi_npa_protocol_data 
 * Return a pointer to the next event in a resource's event list */
#define NPA_EVENT_NEXT_EVENT( evt )   ( evt->next )

/** @ingroup efi_npa_protocol_data 
 * Return a event's trigger type */
#define NPA_EVENT_TRIGGER_TYPE( evt ) ( evt->trigger_type & NPA_TRIGGER_TYPE_MASK )
/** @ingroup efi_npa_protocol_data 
 * Return 1 if the event is disabled, 0 otherwise */
#define NPA_IS_EVENT_DISABLED( evt )                                  \
  ( ( evt->trigger_type & NPA_TRIGGER_RESERVED_BIT_30 ) ? 1 : 0 )
/** @ingroup efi_npa_protocol_data
 *  Return 1 if the event is to be destroyed, 0 otherwise */
#define NPA_IS_EVENT_DESTROYED( evt )                                 \
  ( ( evt->trigger_type & NPA_TRIGGER_RESERVED_BIT_31 ) ? 1 : 0 )
/** @ingroup efi_npa_protocol_data
 * Return 1 if the event is not disabled or to be destroyed, 0 otherwise */
#define NPA_IS_EVENT_ACTIVE( evt )                                    \
  ( ( ( evt->trigger_type & NPA_TRIGGER_RESERVED_BIT_30 ) ||          \
      ( evt->trigger_type & NPA_TRIGGER_RESERVED_BIT_31 ) ) ? 0 : 1 )

/** @ingroup efi_npa_protocol_data */
typedef struct npa_custom_event
{
  const char         *name;      /** Event name */
  npa_callback        callback;  /** Callback */
  void               *data;      /** Data associated with this event structure */
} npa_custom_event;

/** @ingroup efi_npa_protocol_data */
typedef struct npa_link
{
  struct npa_link *next, *prev;
  const char      *name;
  struct npa_resource    *resource;
} npa_link;

/*======================================================================
  Resource types
======================================================================*/

/* Callback functions used to customize resource behavior */

/** @ingroup efi_npa_protocol_data
 *  Driver Function
 *
 * Typically the only function a node author needs to write. This
 * function applies the computed state to the given resource. */
typedef npa_resource_state (*npa_resource_driver_fcn) ( 
  struct npa_resource *resource,
  npa_client_handle    client,
  npa_resource_state   state 
  );


/** @ingroup efi_npa_protocol_data
 * Update Function
 *
 * The Update Function receives the new request and determines the new
 * state for the resource. This function is part of the plugin.  There
 * are number of standard plugins provided by the framework */
typedef npa_resource_state (*npa_resource_update_fcn)( 
  struct npa_resource *resource,
  npa_client_handle    client
  );
  

/** @ingroup efi_npa_protocol_data
 * Resource latency structure */
typedef struct npa_resource_latency {
  UINT32 request;  /* The request latency for the resource */
  UINT32 fork;     /* The fork latency for the resource */
  UINT32 notify;   /* The Notify latency for the resource */
} npa_resource_latency;
  

/** @ingroup efi_npa_protocol_data
 * Query Resource Function
 *
 * This is an optional function to enable the resource to support an
 * extended query API. If defined, it will be invoked for any
 * queries. If the query function does not wish to support the query,
 * it shall return NPA_QUERY_UNSUPPORTED_QUERY_ID.  If the query
 * function returns that the id is unsupported, the framework will
 * attempt to handle the query id.
 *
 * The resource is *not* locked when the query function is invoked.
 * If the query requires atomic processing, it is the responsibility
 * of the query function to lock the resource
 * 
 * This function takes a resource as the first parameter 
 * 
 */
typedef npa_query_status (*npa_resource_query_fcn)( 
  struct npa_resource *resource, 
  unsigned int         query_id, 
  npa_query_type      *query_result );

/** @ingroup efi_npa_protocol_data
 * Query Function 
 *
 * This is an optional function to enable the resource to support an
 * extended query API. If defined, it will be invoked for any
 * queries. If the query function does not wish to support the query,
 * it shall return NPA_QUERY_UNSUPPORTED_QUERY_ID.  If the query
 * function returns that the id is unsupported, the framework will
 * attempt to handle the query id.
 *
 * The resource is *not* locked when the query function is invoked.
 * If the query requires atomic processing, it is the responsibility
 * of the query function to lock the resource
 * 
 * This function takes a resource link as the first parameter. This
 * allows the user to access the resource name within there custom
 * query function.
 * 
 */
typedef npa_query_status (*npa_link_query_fcn)(
  struct npa_link  *resource_link,
  unsigned int     query_id,
  npa_query_type   *query_result );


/** @ingroup efi_npa_protocol_data
 *  Plugin Definition */
typedef struct npa_resource_plugin
{
  npa_resource_update_fcn  update_fcn;        /* Update function */
  unsigned int             supported_clients; /* Bitmask of supported clients */

  /* Plugin Vtable */

  /** Create Client Function - A new client has been created, allow 
   * the plugin a chance to do something before the new client is
   * returned to the user
   *
   * Note: This function has been deprecated in favor of the Extended
   * Client Create Function. It is an error for a plugin to define
   * both the Client Create Function and the Extended Client Create
   * Function */
  void (*create_client_fcn) ( npa_client * ); /* Client Create Function */


  /** Destroy Client Function - The client has been destroyed, allow
   * the plugin an opportunity to clean up before the client is
   * freed */
  void (*destroy_client_fcn)( npa_client * ); /* Client Destroy Function */


  /** Extended Client Create Function - A new client has been created,
   * allow the plugin a chance to do something before the new
   * client is returned to the user.  This function receives whatever
   * optional arguments the user may have passed in. If the third
   * argument is not NULL, the second argument is required to be the 
   * length of the buffer pointed by the third argument. This function
   * should return 0 if the extended creation was successful or a
   * non-zero error code if the extended creation failed.  In the
   * event of failure, the error code will be logged to the NPA log
   * and the user will receive a NULL handle 
   *
   * Note: It is an error for a plugin to define both the Client
   * Create Function and the Extended Client Create Function */
  unsigned int (*create_client_ex_fcn)( npa_client *, unsigned int, void * );


  /** Cancel Client Function - The user has canceled their client
   * request, allow the plugin an opportunity to flush any learned
   * state associated with the client.
   *
   * This function may be NULL - if so, cancel will behave the same as
   * complete. */
  void (*cancel_client_fcn) ( npa_client *); /* Cancel Client Function */

  /** Map client requests to a different/adjusted value before it enters the
   * request pipeline. This routine is invoked outside of the resource lock,
   * so the mapping must use static information or explicit protection. */
  npa_resource_state (*map_request_fcn)( npa_client*, npa_resource_state );

  /** Get pre/post change event data from resource before broadcasting it
   * to event listeners. These routines are invoked within the resource lock,
   * so the context is protected. */
  void * (*get_change_event_data_fcn)( struct npa_resource *, npa_event_type );
} npa_resource_plugin;


/*======================================================================

======================================================================*/

/** @ingroup efi_npa_protocol_data
 * Node Dependency structure
 *
 * A node defines its dependencies via a variable length array of
 * these structures.  The number of elements in the array is defined
 * by the dependency_count field in the node_definition structure
 */
typedef struct npa_node_dependency
{
  const char        *name;          /** Name of resource */
  npa_client_type    client_type;   /** Type of client to create */
  npa_client_handle  handle;        /** Client Handle - created by NPA */
}  npa_node_dependency;


/** @ingroup efi_npa_protocol_data
 * @brief Helper macro to access dependency client handles by index from within
 * a node's driver function. 
 *
 *    mynode_example_driver_fn ( npa_resource *resource,
 *                               npa_client_handle    client,
 *                               npa_resource_state   state )
 *   {
 *     npa_pass_request_attributes( client, NPA_DEPENDENCY(resource, 0) );
 *     npa_issue_required_request( NPA_DEPENDENCY(resource, 0), state );
 *     ...
 */
#define NPA_DEPENDENCY( resource, index ) \
  resource->node->dependencies[index].handle


/** @ingroup efi_npa_protocol_data
 * Resource Definition Structure
 *
 * A node defines its resources via a variable length array of
 * these structures.  The number of elements in the array is defined
 * by the resource_count field in the node_definition structure
 */
typedef struct npa_resource_definition
{
  const char            *name;          /** Name of resource */
  const char            *units;         /** Units for this resource */
  npa_resource_state     max;           /** Maximum state/length of vector resource */
  const npa_resource_plugin *plugin;    /** Plugin */
  unsigned int           attributes;    /** Resource Attributes */
  npa_user_data          data;          /** User data field  */
  npa_resource_query_fcn query_fcn;     /** Query Fcn */
  npa_link_query_fcn     link_query_fcn;      /** Query Link Fcn*/

 /** Handle to this resource 
  *
  * This field will be initialized in by the framework when the node
  * is created. Do not define or define as NULL  */
  struct npa_resource *handle;       
} npa_resource_definition;


/** @ingroup efi_npa_protocol
 * Get the resource associated with a given node, given the current resource  */
#define NPA_RESOURCE( resource, index ) \
  ((resource)->node->resources[(index)].handle)


/** @ingroup efi_npa_protocol_data
 * Node Definition Structure
 *
 * This is created by the Node author.  This can be constant */
typedef struct npa_node_definition
{
  const char                *name;         /** Node name */
  npa_resource_driver_fcn    driver_fcn;   /** Driver function used to
                                            * actually update resource */
  unsigned int               attributes;   /** Node Attributes */
  npa_user_data              data;         /** User data field  */
  unsigned int               dependency_count; /** Number of deps */
  npa_node_dependency       *dependencies;     /** Dep array */
  unsigned int               resource_count;   /** Number of resource */
  npa_resource_definition   *resources;        /** Resource Array */
} npa_node_definition;


/** @ingroup efi_npa_protocol_data 
 * Internal node structure */
typedef struct npa_resource
{
  /** The definition of the resource */
  npa_resource_definition  *definition; 
  unsigned int              index;

  /** Node pointer */
  npa_node_definition      *node;

  /** List of registered node users
   * These are head pointers to doubly-linked lists */
  npa_client               *clients;           /** client list */
  npa_event_list            events;            /** event list */

  /* Dynamic resource behavior */
  const npa_resource_plugin *active_plugin;    /** The current plugin */

  /* State fields */
  npa_resource_state        request_state;     /** Requested state */
  npa_resource_state        active_state;      /** Active state of the HW */
  npa_resource_state        required_state;    /** Active required agg */
  npa_resource_state        suppressible_state; /** Active suppressible agg */  
  npa_resource_state        internal_state[4]; /** Internal state field
                                                * used by plugin as
                                                * necessary */

  /** Pointer to the state_vector. Only non-NULL if NPA_RESOURCE_VECTOR_STATE
     attribute is defined. Length of vector is resource->definition->max */
  npa_resource_state       *state_vector;

  /** Pointer to the aggregation of required vector requests. For vector
   * resources that define NPA_RESOURCE_SUPPORTS_SUPPRESSIBLE, NPA allocates
   * and assigns a vector of size resource->definition->max to this pointer.
   * Access via NPA_RESOURCE_REQUIRED_VECTOR( resource )
   */
  npa_resource_state       *required_state_vector;

  /** Pointer to the aggregation of all suppressible vector requests. For vector
   * resources that define NPA_RESOURCE_ALLOC_SUPPRESSIBLE_VECTOR, NPA
   * allocates and assigns a vector of size resource->definition->max to this
   * pointer. Access via NPA_RESOURCE_SUPPRESSIBLE_VECTOR( resource )
   */
  npa_resource_state       *suppressible_state_vector;


  /** Dynamic state */
  npa_resource_state        active_max;        /** The current max */
  npa_resource_state_delta  active_headroom;   /** The current headroom */

  /** Set to the requesting client during driver calls, otherwise it's NULL. */
  npa_client               *current_client;  

  /** Locks */
  struct CoreMutex         *node_lock;         /* Node lock */
  struct CoreMutex         *event_lock;        /* Lock for events */

  /** Transaction this resource is part of */
  struct npa_transaction   *transaction;

  /** Resource specific NPA internal data - not for resource use */
  struct npa_resource_internal_data *_internal;

  unsigned int              sequence;          /** Sequence number */
  void                     *log_handle;        /** ULog handle associated
                                                * with a resource */
  npa_resource_latency     *latency;
} npa_resource;


/** Dummy declaration for SC purposes; code no longer uses join tokens */
typedef void* npa_join_token;

#ifdef __cplusplus
}
#endif

#endif /* NPA_RESOURCE_H */
