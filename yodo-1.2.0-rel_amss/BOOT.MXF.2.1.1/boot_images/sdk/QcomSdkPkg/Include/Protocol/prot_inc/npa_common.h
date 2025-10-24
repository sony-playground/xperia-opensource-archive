/*============================================================================
@file npa_common.h

NPA client API. This is NOT the API for resource authors. 

The interface uses strings and opaque types. This is done intentionally to
minimize client dependencies on the implementation. The data structures and
implementation can change radically without requiring changes to client code.

Copyright (c) 2009-2021 Qualcomm Technologies, Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary

============================================================================*/
#ifndef NPA_COMMON_H
#define NPA_COMMON_H

/** @defgroup efi_npa_protocol EFI_NPA_PROTOCOL
 *  @ingroup SOCINFRA 
 */
 /** @defgroup  efi_npa_protocol_prot PROTOCOL
 *  @ingroup efi_npa_protocol 
 */ 
 /** @defgroup  efi_npa_protocol_apis APIs
 *  @ingroup efi_npa_protocol 
 */ 

/** @defgroup  efi_npa_protocol_data DATA_STRUCTURES
 *  @ingroup efi_npa_protocol 
 */
/*----------------------------------------------------------------------------
* Common DataType Defines [dont use com_dtpyes.h for EDK complience]
*----------------------------------------------------------------------------*/

typedef	 UINT32      uint32_t;
typedef  UINT64      uint64_t;
typedef  INT32       int32_t;
typedef  INT64       int64_t;
typedef  UINT8       uint8_t;
typedef  INT8        int8_t; 

typedef  UINT32      uint32;
typedef  UINT64      uint64;
typedef  UINT8       uint8;
typedef  INT32       int32;
typedef  INT64       int64;
typedef  INT8        int8; 

typedef  BOOLEAN            boolean; 

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------
 * Enumerations
 * -------------------------------------------------------------------------*/

/** @ingroup efi_npa_protocol_data
 *  NPA status */
typedef enum
{
  NPA_SUCCESS = 0,
  NPA_ERROR   = -1, /** General error */
} npa_status;

/** @ingroup efi_npa_protocol_data
 *  Client work models; clients may only be of one of these types */
typedef enum
{
  NPA_NO_CLIENT          = 0x7fffffff, /** Do not create a client */
  NPA_CLIENT_RESERVED1   = (1 << 0), /** Reserved client type */
  NPA_CLIENT_RESERVED2   = (1 << 1), /** Reserved client type */

  NPA_CLIENT_CUSTOM1     = (1 << 2), /** Custom client types - can be */
  NPA_CLIENT_CUSTOM2     = (1 << 3), /** customized by resource */
  NPA_CLIENT_CUSTOM3     = (1 << 4), 
  NPA_CLIENT_CUSTOM4     = (1 << 5), 

  /* Standard client types */
  NPA_CLIENT_REQUIRED    = (1 << 6), /** Request must honor request */
  NPA_CLIENT_ISOCHRONOUS = (1 << 7), /** Placeholder for isochronous
                                      ** work model */
  NPA_CLIENT_IMPULSE     = (1 << 8), /** Poke the resource - node
                                      ** defines the impulse
                                      ** response */
  NPA_CLIENT_LIMIT_MAX   = (1 << 9), /** Set maximum value for the
                                      ** resource */
  NPA_CLIENT_VECTOR      = (1 << 10), /** Vector request */
  NPA_CLIENT_SUPPRESSIBLE = (1 << 11), /** Suppressible Scalar
                                        * request */
  /** Suppressible Vector request */
  NPA_CLIENT_SUPPRESSIBLE_VECTOR = ((1 << 12) | NPA_CLIENT_VECTOR), 

  /** Another block of custom client types; can be customized by resource */
  NPA_CLIENT_CUSTOM5     = (1 << 13),
  NPA_CLIENT_CUSTOM6     = (1 << 14),

  /** Suppressible requests with additional semantics. For RPM remote
     resources, clients of these types only affect the active set */
  NPA_CLIENT_SUPPRESSIBLE2 = (1 << 15),
  NPA_CLIENT_SUPPRESSIBLE2_VECTOR = (1 << 16),
  
  NPA_CLIENT_RESERVED3    = (1 << 17),   /** Reserved client type */

} npa_client_type;


/** @ingroup efi_npa_protocol_data
 *  Event trigger types - these are the types of event triggers that
 * can be generated  */
typedef enum 
{
  NPA_TRIGGER_RESERVED_EVENT_0,
  NPA_TRIGGER_RESERVED_EVENT_1,
  NPA_TRIGGER_RESERVED_EVENT_2,
  
  NPA_TRIGGER_CHANGE_EVENT,
  NPA_TRIGGER_WATERMARK_EVENT,
  NPA_TRIGGER_THRESHOLD_EVENT,

  NPA_TRIGGER_MAX_EVENT = 0x0000ffff,

  NPA_TRIGGER_RESERVED_BIT_30 = 0x40000000,
  /** Cast to int to suppress a compiler warning */
  NPA_TRIGGER_RESERVED_BIT_31 = ( int )0x80000000
}  npa_event_trigger_type;

#define NPA_TRIGGER_TYPE_MASK  NPA_TRIGGER_MAX_EVENT

/** @ingroup efi_npa_protocol_data 
 * Event types */
typedef enum
{
  NPA_EVENT_RESERVED,                 /** Reserved event */
  NPA_EVENT_RESERVED_1,               /** Reserved event */
  NPA_EVENT_RESERVED_2,               /** Reserved event */

  /** Watermark events */
  NPA_EVENT_HI_WATERMARK,       /** Resource passed hi watermark */
  NPA_EVENT_LO_WATERMARK,       /** Resource passed lo watermark */

  /** State change event */
  NPA_EVENT_CHANGE,             /** Resource changed state */

  /** Threshold events */
  NPA_EVENT_THRESHOLD_LO,      
  NPA_EVENT_THRESHOLD_NOMINAL,
  NPA_EVENT_THRESHOLD_HI,

  /** Custom events */
  NPA_EVENT_CUSTOM,

  NPA_NUM_EVENT_TYPES
} npa_event_type;


/** @ingroup efi_npa_protocol_data
 *  Retain some fork/join type and function definitions for source
 * compatibility reasons */
 
/* Fork preference */
typedef enum
{
  NPA_FORK_DEFAULT = 0,  /** Up to resource/extension author */
  NPA_FORK_DISALLOWED,   /** Disable forking */
  NPA_FORK_ALLOWED,      /** Explicitly allow forking */
} npa_fork_pref;

/** @ingroup efi_npa_protocol_data
 *  User-specified callback that is invoked when a resource
 * or transaction is joined
 *
 * The first arg is the resource handle (if a resource is joined) or
 * the transaction handle (if a transaction is joined).
 * The second arg is the context data passed into npa_fork_resource(),
 * npa_fork_transaction() or npa_fork_transaction_extension().
 */
typedef unsigned int (*npa_join_function) ( void *, void * );

/** @ingroup efi_npa_protocol_data
@{ */
typedef enum
{ /** Default request behavior */
  NPA_REQUEST_DEFAULT            = 0,

  /** Hint that the client does not want to wait for request completion */
  NPA_REQUEST_FIRE_AND_FORGET    = 0x00000001,
  
  /** The NEXT_AWAKE request attribute is a hint to the resource that this
   * request applies at next wakeup. In the case of RPM-based resources, the
   * attribute signifies that the request goes into NAS (Next Active Set)
   * rather than the current Active Set.
   */
  NPA_REQUEST_NEXT_AWAKE       = 0x00000002,

  /** The CHANGED_TYPE attribute signals to the resource that the client
   * has just changed type from required to suppressible or suppressible
   * to required and the resource must re-aggregate accordingly.
   */
  NPA_REQUEST_CHANGED_TYPE      = 0x00000004,
  /** The resource will attempt to process the request but the request may
   * not necessarily be serviced. Clients will typically use this attribute
   * if they would like a resource at a certain level, but can continue
   * without, if the request is not honored.
   */
  NPA_REQUEST_BEST_EFFORT         = 0x00000008,

  /** Reserved for use within NPA */
  NPA_REQUEST_RESERVED_ATTRIBUTE1 = 0x00000010,

  /** When executing LPR-issuable scheduled requests at sleep entry,
   * the scheduler peeks ahead in the request queue to see if there are
   * any more requests to this resource scheduled to apply at next wakeup.
   * If there are, it sets this attribute on the request to inform the
   * resource of this.
   * Set by the framework. Do not set on client handle yourself.
   */
  NPA_REQUEST_MULTIPLE_NEXT_AWAKE = 0x00000020,

  /** Reserved for use within NPA */
  NPA_REQUEST_RESERVED_ATTRIBUTE2 = 0x00000040,

  /** Reserved for use within NPA */
  NPA_REQUEST_RESERVED_ATTRIBUTE3 = 0x00000080,
  NPA_REQUEST_LAST_IN_BATCH = NPA_REQUEST_RESERVED_ATTRIBUTE3,

  /** ENUM_MAX should be set to the next higher power of 2 */ 
  NPA_REQUEST_ENUM_MAX         = 0x00000100,

} npa_request_attribute;

/** Resource independent maximum value
 *
 * Note: This will not work for resources with signed state values.
 * This may need to be revisited.  
 */
#define NPA_MAX_STATE 0xffffffff

/** Public Resource Query IDs
 *
 * Note: All the public resource queries return a type of
 * npa_resource_state  */
enum {
  /** Query the current state of the resource */
  NPA_QUERY_CURRENT_STATE,    
  /** Query the active maximum state supported by the resource. The
   * active max may be lower than the resource maximum due to
   * limit_max request */
  NPA_QUERY_ACTIVE_MAX, 
  /** Query the absolute max of the resource.  This may be greater than
   * the resource's active max if there are active limit_max
   * requests  */
  NPA_QUERY_RESOURCE_MAX,
  /** Query the enabled/disabled state of the resource 
   *   Non-zero if resource is disabled */
  NPA_QUERY_RESOURCE_DISABLED,
  /** Query all of the latencies for the resource */
  NPA_QUERY_RESOURCE_LATENCY,
  /** Query the request latency for the resource */
  NPA_QUERY_RESOURCE_REQUEST_LATENCY,
  /** Query the fork latency for the resource */
  NPA_QUERY_FORK_REQUEST_LATENCY,
  /** Query the Notify latency for the resource */
  NPA_QUERY_NOTIFY_REQUEST_LATENCY,
  /** Deprecated - Query the join latency for the resource 
   * Use NPA_QUERY_NOTIFY_REQUEST_LATENCY instead
   */
  NPA_QUERY_JOIN_REQUEST_LATENCY = NPA_QUERY_NOTIFY_REQUEST_LATENCY,

  /** End public resource query space */
  NPA_MAX_PUBLIC_QUERY     = 1023,

  /** Reserved section of query space */
  NPA_QUERY_RESERVED_BEGIN = 1024,
  
  /** Query availability of remote resource, used in NPA remoting */
  NPA_QUERY_REMOTE_RESOURCE_AVAILABLE = 1025,
  
  NPA_QUERY_RESERVED_END   = 4095

  /** Resource-specific query ids beyond this */
};

/* Query Status */
typedef enum {
  NPA_QUERY_SUCCESS = 0,
  NPA_QUERY_UNSUPPORTED_QUERY_ID,
  NPA_QUERY_UNKNOWN_RESOURCE,
  NPA_QUERY_NULL_POINTER,
  NPA_QUERY_NO_VALUE, /** Used if no current state information is available. */
} npa_query_status;

/*----------------------------------------------------------------------------
 * Types/Typedefs
 * -------------------------------------------------------------------------*/
/** Work request types */
typedef unsigned int npa_resource_state; 
typedef          int npa_resource_state_delta; 

typedef UINT32 npa_time_sclk;
typedef npa_time_sclk npa_resource_time;

/** Callback Type */
typedef void ( *npa_callback )( void         *context,
                                unsigned int  event_type, 
                                void         *data,       
                                unsigned int  data_size );

typedef void ( *npa_simple_callback )( void *context );

/** Handle to the client */
typedef struct npa_client * npa_client_handle;

/** Event structure */
typedef struct npa_event * npa_event_handle;

/** Custom event handle */
typedef struct npa_custom_event * npa_custom_event_handle;

/** Opaque handle to a batch of requests, for use in
 * npa_batch_scalar/vector_request and npa_issue_batch_request API.
*/
typedef struct npa_batch_request * npa_batch_request_handle;

/** Event data structure - passed to npa_event callback */
typedef struct npa_event_data
{
  const char               *resource_name;
  npa_resource_state        state;
  npa_resource_state_delta  headroom;
} npa_event_data;

/** Query handle to the resource */
typedef struct npa_link * npa_query_handle;

/** Query Type
 *
 * Mulitple types can be passed via the query API. The enum defines
 * which type is in the union */
typedef enum
{
   NPA_QUERY_TYPE_STATE,
   NPA_QUERY_TYPE_VALUE,
   NPA_QUERY_TYPE_NAME,
   NPA_QUERY_TYPE_REFERENCE,
   NPA_QUERY_TYPE_VALUE64,

   NPA_QUERY_NUM_TYPES
} npa_query_type_enum;

/** The actual type being passed to the query API */
typedef struct npa_query_type
{
  npa_query_type_enum type;
  union
  {
    npa_resource_state  state;
    unsigned int        value;
    unsigned long long  value64;
    char               *name;
    void               *reference;
  } data;
} npa_query_type;
/** @} */ /* end_ingroup efi_npa_protocol_data */

#ifdef __cplusplus
}
#endif

#endif /* NPA_COMMON_H */
