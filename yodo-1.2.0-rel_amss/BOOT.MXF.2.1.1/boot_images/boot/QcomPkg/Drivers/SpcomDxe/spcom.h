#ifndef _SPCOM_H_
#define _SPCOM_H_

/**
 @file  spcom.h
 */
/*=============================================================================
 Copyright (c) 2021 Qualcomm Technologies, Incorporated.
 All rights reserved.
 Qualcomm Technologies, Confidential and Proprietary.
 =============================================================================*/

/*=============================================================================
 EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 04/14/21   nc      spcom_unregister_client crash fix
 01/11/21   vp      Load API's fix
 11/06/20   vp      Remove SPSS Production Flag
 06/15/20   vp      initial release
 =============================================================================*/

#include <comdef.h>
#include <Protocol/EFISpcom.h>
#include "spcom_os_al.h" // spcom operating system abstraction layer
/**
 * @brief - Secure Processor Communication API
 *
 * The API is based on Client/Server model.
 * The API resemble the trustzone QSEECOM API.
 * Currently expecting the Secure Processor side to have servers and the HLOS
 * side to have clients. Request is initiated by the client and responded by the
 * server.
 * This API should be used by Android (HLOS) User Space Application.
 * Message/Response are expected to be synchronous.
 */

/*===========================================================================*/
/*                           defines, enums , types                          */
/*===========================================================================*/

/* Uncomment one of the below two lines,
 * based on whether you want to run
 * sanity test or not
 */
//#define SPCOMDXE_SANITY_TEST
#undef SPCOMDXE_SANITY_TEST

/* Maximum number of logical channels supported */
#define SPCOM_MAX_CHANNELS     20

/* Maximum size (including null) for channel names - match glink */
#define SPCOM_CHANNEL_NAME_SIZE         32

/**
 * Request buffer size.
 * Any large data (multiply of 4KB) is provided by temp buffer in DDR.
 * Request shall provide the temp buffer physical address (align to 4KB).
 * Maximum request/response size of 268 is used to accommodate APDU size.
 * From kernel spcom driver perspective a PAGE_SIZE of 4K
 * is the actual maximum size for a single read/write file operation.
 */
#define SPCOM_MAX_REQUEST_SIZE          268
#define SPCOM_MAX_RESPONSE_SIZE         268

/**
 * Abstract spcom handle.
 * The actual struct definition is internal to the spcom driver.
 */
struct spcom_client; /* Forward declaration */
struct spcom_server; /* Forward declaration */


/*===========================================================================*/
/*                           RESET                                           */
/*===========================================================================*/

/**
 * spcom_reset_sp_subsystem() - send reset command to secure processor.
 *
 * Gracefully ask the remote SP to reset itself.
 * SP will probably initiate a Watch-Dog-Bite.
 *
 * return: 0 on success, negative error code on failure.
 */
int spcom_reset_sp_subsystem(void);

/*===========================================================================*/
/*                       IS SYSTEM UP                                        */
/*===========================================================================*/

/**
 * spcom_is_sp_subsystem_link_up() - check if SPSS link is up.
 *
 * return: true if link is up, false if link is down.
 */
boolean spcom_is_sp_subsystem_link_up(void);

EFI_STATUS spcom_is_app_loaded (const char *ch_name);

EFI_STATUS spcom_get_reserved_pil_region(const char *ch_name, void **buf, size_t size, boolean is_app_load);

EFI_STATUS spcom_clear_reserved_pil_region (const char *ch_name, void *buf, size_t size, boolean is_app_load);

EFI_STATUS spcom_load_app (const char *ch_name, EFI_GUID *appGuid, size_t image_size, size_t swap_size, size_t *load_resp_code);

EFI_STATUS spcom_load_app_from_buffer(const char *ch_name,
        void *image_buf, size_t image_size, size_t swap_size, size_t *load_resp_code);

/*===========================================================================*/
/*                           Client Send Message                             */
/*===========================================================================*/
EFI_STATUS spcom_register_client(struct spcom_client_info *info, struct spcom_client **client_ptr);

EFI_STATUS spcom_unregister_client(struct spcom_client **client_ptr);

/**
 * spcom_client_send_message_sync() - Send a synchronous request and response.
 *
 * @client:     a pointer to spcom client
 * @req_ptr:    a pointer to the request C struct representation
 * @req_size:   size of the request C struct
 * @resp_ptr:   a pointer to the response C struct representation
 * @resp_size:  size of the response C struct
 * @timeout_msec: Timeout in msec between command and response, 0=no timeout.
 *
 * return: 0 on success, negative error code on failure (see errno.h)
 */
EFI_STATUS spcom_client_send_message_sync(struct spcom_client  *client,
                                   void                 *req_ptr,
                                   size_t            req_size,
                                   void                 *resp_ptr,
                                   size_t            resp_size,
                                   size_t            *rx_size,
                                   size_t            timeout_msec);

/**
 * spcom_client_is_server_connected() - Check if remote server connected.
 *
 * This API checks that the logical channel is fully connected between
 * the client and the server.
 * Normally, the server should be up first and connect first.
 *
 * @client:     a pointer to spcom client
 *
 * return: true if server connected, false otherwise.
 */
boolean spcom_client_is_server_connected(struct spcom_client *client);


/*===========================================================================*/
/*                           Service                                         */
/*===========================================================================*/

/**
 * spcom_register_service() - register server for channel
 *
 * Only one client/Server can register on each side of a channel.
 *
 * @info:      Server configuration info (input).
 *
 * return: server handle on sucess, NULL on failure.
 */
EFI_STATUS spcom_register_service (struct spcom_service_info *info, struct spcom_server **server_ptr);

/**
 * spcom_unregister_service() - unregister server for channel
 *
 * @server:    server Handle.
 *
 * return: 0 on success, negative error code on failure (see errno.h)
 */
EFI_STATUS spcom_unregister_service(struct spcom_server *server);

/**
 * spcom_server_get_next_request_size() - get the size of the
 * next request
 *
 * This API MUST be called before calling spcom_server_wait_for_request().
 * The server should allocate the relevant buffer size.
 *
 * @server:    a pointer to spcom server
 *
 * return: size of request in bytes on success, negative value on failure (see errno.h)
 */
EFI_STATUS spcom_server_get_next_request_size(struct spcom_server *server, size_t timeout_msec);

/**
 * spcom_server_wait_for_request() - server wait for request
 *
 * @server:     a pointer to spcom server
 * @req_ptr:   a pointer to the request buffer
 * @req_size:  size of the buffer provided.
 * The server should provide a buffer of atleast the size
 * returned by spcom_server_get_next_request_size() and up to
 * SPCOM_MAX_REQUEST_SIZE.
 *
 * return: size of request on success, negative value on failure (see errno.h)
 */
EFI_STATUS spcom_server_wait_for_request(struct spcom_server  *server,
                                 void                  **req_ptr,
                                 size_t              *req_size);

/**
 * spcom_server_send_response() - Send a the response to request
 *
 * @server:    a pointer to spcom server
 * @resp_ptr:  a pointer to the response C struct representation
 * @resp_size:  size of the response C struct
 *
 * return: sent data size on success, negative value on failure (see errno.h)
 */
EFI_STATUS spcom_server_send_response(struct spcom_server     *server,
                              void                     *resp_ptr,
                              size_t                resp_size);

EFI_STATUS
spcom_server_get_next_request (struct spcom_server *server);

EFI_STATUS poll_on_nvm_ch (void);

EFI_STATUS spcom_init(void);


#ifdef SPCOMDXE_SANITY_TEST
EFI_STATUS spcom_sanity_test(void);
#endif


#endif /* _SPCOM_H_ */
