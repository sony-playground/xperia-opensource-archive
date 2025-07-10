/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef SAKE_CERT_H
#define SAKE_CERT_H

#include "sake_engine_internal.h"
#include "stdint.h"

#define MINAID 1


struct CertificateData {
	const uint8_t *pTBSCertificate;
	uint32_t tBSCertificateLength;
	struct PublicKey publicKey;
	const uint8_t *pSignature;
	uint32_t signatureLength;
	uint16_t serialNumber;
	uint32_t ssn;
	struct CertificateData *pNext;
};


/**
 *Verify the certificate chain.
 *
 * @param [in] handle         Handle, which was created by sake_init()
 *
 * @param [in] pCertChain     Should point to the Sake Response message.
 *
 * @param [in] certChainLen   Length of Sake Response Message.
 *
 * @return The function returns FCSERR_OK on success
 *  and a negative error code otherwise.
 */

int sake_verify_cert_chain(struct sake_internal_handle *handle,
			   const uint8_t *pCertChain,
			   uint32_t certChainLen);

/**
 * sake_get_certificate
 *
 * @param [in] pCert
 *
 * @param [in] pData
 *
 * @param [in] dataLen   Length of pData.
 *
 * @return The function returns FCSERR_OK on success
 *  and a negative error code otherwise.
 */
int sake_get_certificate(struct CertificateData *pCert,
			 const uint8_t *pData,
			 uint32_t dataLen);
/**
 *release the certificate data.
 *
 * @param [in] cert
 *
 */
void sake_free_certificate(struct CertificateData *cert);


#endif /* SAKE_CERT_H */

