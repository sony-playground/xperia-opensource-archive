/******************************************************************************
  *                    ____                                                   *
  *                   / ___|  ___  _ __                                       *
  *                   \___ \ / _ \| '_ \| | | |                               *
  *                   ___ ) | (_) | | | | |_| |                               *
  *                   |____/ \___/|_| |_|\__, |                               *
  *                                       |___/                               *
  *                                                                           *
 ******************************************************************************
  *Copyright (c) 2016 Sony Mobile Communications Inc.                         *
  *All rights, including trade secret rights, reserved.                       *
 ******************************************************************************
  *DESCRIPTION:                                                               *
  * Used to parse asahi signatures.                                           *
  *                                                                           *
  *HOW TO USE:                                                                *
  *                                                                           *
  *  required operation =   ------------------------>                         *
  *  optional operation =   ---------------------//->                         *
  *                                                                           *
  *  *-------------------- *                          *--------------------  **
  *  *       Client        *                          *   asahi  Parser      **
  *  *-------------------- *                          *--------------------  **
  *  void  **handle;                                                          *
  *  uint8_t asahi_buffer[];                                                  *
  *  size_t length_asahi_buffer;                                              *
  *  (1)---asahiparser_init(&handle, asahi_buffer, length_asahi_buffer)-->    *
  *                                                                           *
  *  (2)---asahiparser_deinit(handle)------------------------------------>    *
  *                                                                           *
  *NOTE: All functions / methods returns a int status / error code,    *
  *      which indicates the outcome of the operation, thus all return values *
  *      should be checked with the s1 utility macros, i.e. as exemplified    *
  *      below.                                                               *
  *                                                                           *
  *      int res;                                                             *
  *                                                                           *
  *      res = asahiparser_init(&handle, ...);                                *
  *      if(SUCCEEDED(res)){                                                  *
  *        // Operation succeeded / is allowed, do something                  *
  *      }else{                                                               *
  *        // Operation failed / is not allowed, do something else            *
  *      }                                                                    *
  *                                                                           *
  *NOTE: The ASAHI parser operates directly on the ASAHI buffer provided when *
  *      creating the ASAHI parser, thus this memory buffer must be kept      *
  *      intact during the entire session. Once asahiparser_deinit(...) is    *
  *      called, the client can destroy its ASAHI buffer.                     *
  *                                                                           *
  *NOTE: As the ASAHI parser operates directly on the ASAHI buffer provided   *
  *      at creation time, it  d o e s  n o t  copy any data. This means that *
  *      when e.g. requesting specific attributes, only a pointer to correct  *
  *      part in the ASAHI buffer is given to the client, i.e. no copy of     *
  *      data is done at any time.                                            *
  *                                                                           *
  *NOTE: After done with the ASAHI parser, the client should call             *
  *      asahiparser_deinit()                                                 *
  *                                                                           *
*****************************************************************************/
#ifndef ASAHI_PARSER_H_
#define ASAHI_PARSER_H_

#include <stdlib.h>
#include <stdint.h>

#define ASAHI_NONE       (0)
#define ASAHI_SHA1_RSA   (1)
#define ASAHI_SHA256_RSA (2)

/**
 / Initializes and gives back a handle to the ASAHI parser. The handle is
 * allocated by the function and should be de-allocated by a call to
 * asahiparser_deinit().
 *
 * NOTE: The ASAHI parser operates on the raw ASAHI buffer directly, thus the
 * client must keep this buffer alive during the entire session.
 *
 * The handler is retrieved if the asahibuffer contains valid ASAHI data,
 * otherwise the handler is NULL.
 *
 * @param [out] handle           Session handle, which should be used in
 *                               consecutive calls to the parser
 * @param [in]  asahibuffer      A pointer to the asahi buffer binary data (The
 *                               client must keep the raw ASAHI buffer alive
 *                               during the entire session.)
 * @param [in]  asahibuffer_size Size, in bytes, of the raw ASAHI buffer
 *
 * @returns int
 */
int asahiparser_init(
		void  **handle,
		uint8_t *asahibuffer,
		size_t asahibuffer_size);

/**
 * Shuts down and de-allocates memory for the ASAHI parser that was created
 * and initialized by a call to asahiparser_init(...). After this call, the
 * client is free to remove (free memory used by) the raw ASAHI buffer.
 *
 * @param [in]  handle         Session handle
 *
 * @returns int
 */
int asahiparser_deinit(
		void  *handle);

/**
 * Allocate a buffer of DER encoded certificates from the certificate chain
 * in the ASAHI data.
 * Buffer should be deallocated by caller.
 *
 * @param [in]  handle                  Session handle
 * @param [out] certificate_chain       Pointer to the certificate chain
 * @param [out] certificate_chain_size  Length, in bytes, of the certificate
 *                                      chain buffer.
 *
 * @returns int
 */
int asahiparser_get_certificate_chain(
		void  *handle,
		uint8_t **certificate_chain,
		size_t *certificate_chain_size);

/**
 *Get the signature algorithm for RSA signature that exists in the ASAHI data.
 *
 * @param [in]  handle                  Session handle
 * @param [out] algorithm               Signature algorithm
 *
 * @returns int
 */
int asahiparser_get_signature_algorithm(
		void  *handle,
		uint8_t *algorithm);

/**
 * Retrieves a pointer to the RSA signature that exists in the ASAHI data.
 * NOTE: Pointer should NOT be deallocated by caller.
 *
 * @param [in]  handle              Session handle
 * @param [out] rsa_signature       Pointer to the RSA signature
 * @param [out] rsa_signature_size  Length, in bytes, of the RSA signature
 *
 * @returns int
 */
int asahiparser_get_rsa_signature(
		void  *handle,
		uint8_t **rsa_signature,
		size_t *rsa_signature_size);

#endif /* ASAHI_PARSER_H_ */
