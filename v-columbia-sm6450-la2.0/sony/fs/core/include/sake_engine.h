/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#ifndef SAKE_ENGINE_H
#define SAKE_ENGINE_H

#include "fcs_crypto.h"

typedef void *sake_handle_t;

struct sake_ext_hash_functions {
	hash_init_t hash_init;
	hash_reinit_t hash_reinit;
	hash_update_t hash_update;
	hash_get_hash_size_t hash_get_hash_size;
	hash_final_t hash_final;
	hash_deinit_t hash_deinit;
};

struct  sake_ext_rsa_functions {
	rsa_encrypt_nopad_t encrypt_no_pad;
};

struct sake_ext_functions {
	struct sake_ext_hash_functions hash_functions;
	struct sake_ext_rsa_functions rsa_functions;
};

/**
 * Constructor / Destructor
 */

/**
 *  Initializes and gives back a handle to the sake handler. The handle is
 *  allocated by the function and should be de-allocated by a call to
 *  sake_deinit().
 *
 *  @param [out] handle                 Handle pointer, which should be used in
 *                                      consecutive calls to the sake lib.
 *
 *  @param [in]  pub_hash               Asn.1 encoded public hash
 *                                      Expected format
 *                                      0x02, lenbyte, <hash bytes...>
 *
 *  @param [in]  rsa_pub_key            Asn.1 encoded rsa public key as
 *                                      specified in @file fcs_crypto.h
 *
 *  @param [in]  crl                    Asn.1 encoded certificate revocation
 *                                      list (CRL) Expected format
 *                                      0x30, 0x82, totlenhigh, totlenlow,
 *                                      0x02, 0x01, listversion (set to 0 if
 *                                      not told otherwise),
 *                                      0x02, 0x01, numcerts,
 *                                      0x02, 0x82, listlenhighbyte,
 *                                      listlenlowbyte,
 *                                      <list of certs 4bytes each>
 *
 *  @param [in]  hash type
 *
 *  @param [in]  ext_functions          Externally implemented functions, e.g.
 *                                      crypto etc.
 *
 *  @returns int
 *
 */

int sake_init(sake_handle_t *handle,
	      uint8_t *pub_hash,
	      asn_rsa_public_key_t rsa_pub_key,
	      uint8_t *crl,
	      struct sake_ext_functions ext_functions);

/**
 *  De-Initializes and de-allocates memory allocated by the sake handler
 *  for the session in question.
 *
 *  @param [in]  handle            Handle, which was created by a call to
 *                                 sake_init(..)
 *
 *  @returns int
 */
int sake_deinit(sake_handle_t handle);

/**
 * Returns a Sake Hello message that can be sent to a SECS server for
 * authentication. The SECS server either rejects it (permission denied)
 * or authenticates it by creating a signed Sake Response message.
 *
 * @param [in,out] handle     Handle, which was created by sake_init()
 *
 * @param [out] hello_msg     Copy of the Sake Hello message if it exist.
 *
 * @param [in] hello_msg_len  The length allocated for message.
 *
 * @return                    The function returns FCSERR_OK on success
 *                            and a negative error code otherwise.
 */
int  sake_get_hello_message(sake_handle_t handle, uint8_t *hello_msg,
			    size_t hello_msg_len);

/**
 * Returns the length of the saved Sake Hello message
 *
 * @param [in,out] handle     Handle, which was created by sake_init()
 *
 * @return                    Returns the length of the saved hello message or
 *                            zero of it not exist.
 */
size_t  sake_get_hello_message_length(sake_handle_t handle);

/**
 * Composes a Sake Hello message that can be sent to a SECS server for
 * authentication. The SECS server either rejects it (permission denied)
 * or authenticates it by creating a signed Sake Response message.
 *
 * @param [in,out] handle     Handle, which was created by sake_init()
 *
 * @param [out] hello_msg_len The length of the Sake Hello message.
 *
 * @param [in] rand_buf       Should point to a buffer with random bytes.
 *
 * @param [in] rand_buf_len   Number of random bytes. This value must be at
 *                            least 20. It can be larger than 20 but there
 *                            should be no reason to increase this value as
 *                            long as the bytes really are random.
 *
 * @param [in] imei           (Optional)Should point to a null terminated
 *                            string containing the IMEI number. If parameter
 *                            is not NULL it should point to a string
 *                            containing 14 digits.
 *
 * @param [in] dev_id         (Optional)Should point to a null terminated
 *                            string containing a device unique identifier.
 *                            If not NULL it can have any length.
 *
 * @param [in] rev_str        Should point to a null terminated string that
 *                            says what loader version we are running on. This
 *                            information is logged on the SECS server for
 *                            statistical purposes.
 *
 * @param [in] ssn            What purpose the authentication is for.
 *                            SSN 0 = Activation, SSN 1 = Factory.
 *
 * @return The function returns FCSERR_OK on success
 *  and a negative error code otherwise.
 */
int sake_compose_hello_message(sake_handle_t handle,
			       size_t *hello_msg_len,
			       const uint8_t *rand_buf,
			       size_t rand_buf_len,
			       const char *imei,
			       const char *dev_id,
			       const char *rev_str,
			       uint_fast16_t ssn);

/**
 * Checks a Sake Response message that has been created by the SECS server.
 *
 * This function can only be called if the sake_compose_hello_message() has
 * been called previously, because the Hello Message and Response Message must
 * match on some points.
 *
 * @param [in] handle         Handle, which was created by sake_init()
 *
 * @param [in] resp_msg       Should point to the Sake Response message.
 *
 * @param [in] resp_msg_len   Length of Sake Response Message.
 *
 * @return The function returns FCSERR_OK on success
 *  and a negative error code otherwise.
 */
int sake_check_response_message(sake_handle_t handle,
				const uint8_t *resp_msg,
				size_t resp_msg_len);

#endif /* SAKE_ENGINE_H */
