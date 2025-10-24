/*
 * Copyright 2016, 2022 Sony Corporation
 * All rights, including trade secret rights, reserved.
 */

#include "sake_engine.h"
#include "sake_engine_internal.h"
#include "sake_alg.h"
#include "sake_cert.h"
#include "sake_hash.h"
#include "string.h"
#include <stdlib.h>
#include "fcserr.h"
#include "fcslog.h"

static void sake_certificate_datalist_destroy(struct CertificateData
					      *pCertificateDataList);

static int sake_get_chain_certificates(struct sake_internal_handle *handle,
				       const uint8_t *pCertificate,
				       uint32_t certificateLength,
				       struct CertificateData **
				       ppCertificateDataList);

static int sake_verify_cert_datalist(struct sake_internal_handle *handle,
				     struct CertificateData
				     *pCertificateDataList,
				     int32_t minAid);
static int sake_verify_signature(struct sake_internal_handle *handle,
				 const uint8_t *pSignatureData,
				 uint32_t signatureDataLength,
				 const uint8_t *pHashValue,
				 uint32_t hashValueLength,
				 struct PublicKey *pPublicKey);

int sake_verify_cert_chain(struct sake_internal_handle *handle,
			   const uint8_t *pCertChain,
			   uint32_t certChainLen)
{
	int32_t res = FCSERR_OK;
	struct CertificateData *pCertificateDataList = NULL;

	do {
		if (!pCertChain) {
			res = -FCSERR_EINVAL;
			break;
		}

		if (certChainLen < 4) {
			res = -FCSERR_ENOBUFS;
			break;
		}

		res = sake_get_chain_certificates(handle, pCertChain,
						     certChainLen,
						     &pCertificateDataList);
		if (res != FCSERR_OK)
			break;

		{
			res = sake_verify_cert_datalist(handle,
							pCertificateDataList,
							MINAID);
			if (res != FCSERR_OK)
				break;
		}
	} while (0);

	if (pCertificateDataList)
		sake_certificate_datalist_destroy(pCertificateDataList);

	return res;
}

/*
 * This function releases all memory in the certificate pointed to by pCert.
 */
void sake_free_certificate(struct CertificateData *cert)
{
	struct PublicKey *public_key;

	if (!cert) {
		FCS_LOG_ERR("Invalid argument\n");
		return;
	}

	public_key = &cert->publicKey;

	if (public_key->item_m.data) {
		free(public_key->item_m.data);
		public_key->item_m.data = 0;
	}
	if (public_key->item_e.data) {
		free(public_key->item_e.data);
		public_key->item_e.data = 0;
	}
}

/*
 * This function takes a certificate and adds the root certificate
 * to create a verifiable cert chain.
 */
static int sake_get_chain_certificates(struct sake_internal_handle *handle,
				       const uint8_t *pCertificate,
				       uint32_t certificateLength,
				       struct CertificateData **
				       ppCertificateDataList)
{
	int result = FCSERR_OK;
	int32_t shorten = 0;
	struct CertificateData *cert_data = NULL;
	struct CertificateData *cert_data_next = NULL;
	struct R_ITEM *public_key_member;

	if (!handle || !ppCertificateDataList) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	do {
		/* skip input parameter check since it is internal function */
		cert_data = malloc(sizeof(struct CertificateData));
		if (!cert_data) {
			result = -FCSERR_ENOMEM;
			break;
		}

		memset(cert_data, 0, sizeof(struct CertificateData));

		result = sake_get_certificate(cert_data, pCertificate,
					      certificateLength);
		if (result != FCSERR_OK)
			break;

		/* we are done with the current cert */
		cert_data_next = (struct CertificateData *)
			malloc(sizeof(struct CertificateData));
		if (!cert_data_next) {
			result = -FCSERR_ENOMEM;
			break;
		}


		if (handle->public_key.item_m.data[0] == 0)
			shorten = 1;

		public_key_member = &cert_data_next->publicKey.item_m;
		public_key_member->len  = handle->public_key.item_m.len -
			shorten;
		public_key_member->data = (uint8_t *)
			malloc(public_key_member->len);
		if (!public_key_member->data) {
			result = -FCSERR_ENOMEM;
			break;
		}

		memcpy(public_key_member->data, handle->public_key.item_m.data
		       + shorten, public_key_member->len);

		public_key_member = &cert_data_next->publicKey.item_e;
		public_key_member->len  = handle->public_key.item_e.len;
		public_key_member->data =
			(uint8_t *)malloc(public_key_member->len);
		if (!public_key_member->data) {
			result = -FCSERR_ENOMEM;
			break;
		}

		memcpy(public_key_member->data, handle->public_key.item_e.data,
		       public_key_member->len);
		cert_data_next->pNext = NULL;

		/* set return values */
		cert_data->pNext = cert_data_next;
		*ppCertificateDataList = cert_data;

	} while (0);

	if (result != FCSERR_OK)
		sake_certificate_datalist_destroy(cert_data);

	return result;
}


static int sake_verify_cert_datalist(struct sake_internal_handle *handle,
			     struct CertificateData
			     *pCertificateDataList,
			     int32_t minAid)
{
	int res = FCSERR_OK;
	struct CertificateData *pCert = pCertificateDataList;

	if (!handle || !pCertificateDataList) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	int32_t certificateHashLength = 0;
	uint8_t (*cert_revocation_list)[4] = 0;
	uint8_t pCertificateHash[HASH_SIZE];
	int32_t a, b, block, len;

	do {
		if (!pCert || !(pCert->pNext)) {
			res = -FCSERR_ESTATE;
			break;
		}

		while (pCert->pNext) {
			certificateHashLength = HASH_SIZE;

			res = sake_calculate_hash(handle->funcs.hash_functions,
						     pCert->pTBSCertificate,
						     pCert->
						     tBSCertificateLength,
						     handle->hash_type,
						     handle->hash_digest_size,
						     pCertificateHash);
			if (res != FCSERR_OK)
				break;

			res = sake_verify_signature(handle, pCert->pSignature,
						    pCert->signatureLength,
						    pCertificateHash,
						    certificateHashLength,
						    &pCert->pNext->publicKey);

			if (res != FCSERR_OK)
				break;

			if (0 != handle->cert_revocation_list_len) {
				cert_revocation_list = (uint8_t (*)[4])
					handle->cert_revocation_list;

				/* Make sure certificate is not on the CRL */
				for (a = 0; ((uint8_t)cert_revocation_list[a]
					     [0] != 0) ||
				     ((uint8_t)cert_revocation_list[a][1] != 0)
				     ||
				     ((uint8_t)cert_revocation_list[a][2] != 0)
				     ||
				     ((uint8_t)cert_revocation_list[a][3] != 0)
				     ; a++) {
					len = pCert->signatureLength;
					block = 1;
					for (b = 0; b < 4; b++) {
						if ((uint8_t)
						    cert_revocation_list[a][b]
						    != pCert->pSignature[len -
						    4 + b]) {
							block = 0;
							break;
						}
					}
					if (block == 1) {
						res = -FCSERR_ESTATE;
						break;
					}
				}
			}

			/* Next certificate in the chain... */
			pCert = pCert->pNext;
		}

		if (res != FCSERR_OK)
			break; /* get out of the outer loop */

		/*
		 * Verify the serial number - of the first certificate in the
		 * chain
		 */
		if (pCertificateDataList->serialNumber < minAid)
			res = -FCSERR_ESTATE;
	} while (0);

	return res;
}


static void sake_certificate_datalist_destroy(struct CertificateData *
					      certificate_datalist)
{
	struct CertificateData *current_cert;
	struct CertificateData *next_cert = 0;

	current_cert = certificate_datalist;
	while (current_cert != NULL) {
		next_cert = current_cert->pNext;
		sake_free_certificate(current_cert);
		free(current_cert);
		current_cert = next_cert;
	}
}

static int sake_verify_signature(struct sake_internal_handle *handle,
				 const uint8_t *pSignatureData,
				 uint32_t signatureDataLength,
				 const uint8_t *pHashValue,
				 uint32_t hashValueLength,
				 struct PublicKey *pPublicKey)
{
	uint32_t a;
	int result;
	uint8_t *rsaRes = NULL;
	uint8_t *padded = NULL;
	uint8_t sha_oid[SAKE_OID_SIZE] = SAKE_OID;

	if (!pPublicKey) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	padded = malloc(signatureDataLength);
	rsaRes = malloc(signatureDataLength);
	if (!padded || !rsaRes) {
		FCS_LOG_ERR("No memory\n");
		result = -FCSERR_ENOMEM;
		goto exit;
	}

	result = sake_pub_key_encrypt(handle, pSignatureData,
				      signatureDataLength,
				      rsaRes, pPublicKey->item_m.data,
				      pPublicKey->item_m.len, /* n-key here */
				      pPublicKey->item_e.data,
				      pPublicKey->item_e.len); /* e-key here */

	if (result != FCSERR_OK)
		goto exit;

	result = sake_add_padding(
		pHashValue, hashValueLength, padded, signatureDataLength);
	if (result != FCSERR_OK)
		goto exit;

	memcpy(padded + signatureDataLength - HASH_SIZE - SAKE_OID_SIZE,
	       sha_oid, SAKE_OID_SIZE);
	padded[signatureDataLength - HASH_SIZE - SAKE_OID_SIZE - 1] = 0;
	SAKE_DBGDUMP(padded, signatureDataLength);

	for (a = 0; a < signatureDataLength; a++) {
		if (padded[a] != rsaRes[a]) {
			result = -FCSERR_ESTATE;
			goto exit;
		}
	}

exit:
	free(padded);
	free(rsaRes);
	return result;
}


static int32_t GetTag(const uint8_t *pData, const uint8_t *pDataEnd,
		      int32_t *tag, uint32_t *len)
{
	/* sets tag to -1 on error */
	int32_t metaLen;
	int32_t lenOfLen;

	if (pData >= pDataEnd) {
		*tag = -1;
		return 0;
	}
	*tag = pData[0];
	lenOfLen = pData[1];
	if (lenOfLen == 0x82) {
		metaLen = 4;
		if (pData + 2 >= pDataEnd) {
			*tag = -1;
			return 0;
		}
		*len = (pData[2]<<8) | pData[3];
	} else if (lenOfLen == 0x81) {
		metaLen = 3;
		if (pData + 1 >= pDataEnd) {
			*tag = -1;
			return 0;
		}
		*len = pData[2];
	} else {
		metaLen = 2;
		*len = lenOfLen;
	}
	/* check if len is legal */
	if ((pData + metaLen + *len > pDataEnd) ||
	    (pData + metaLen + *len < pData)) {
		*tag = -1;
		return 0;
	}
	return metaLen;
}


int sake_get_certificate(struct CertificateData *pCert,
			 const uint8_t *pData,
			 uint32_t dataLen)
{
	int result = FCSERR_OK;
	uint32_t len;
	int32_t offs = 0;
	int32_t extOffs;
	int32_t tag;
	int32_t k;
	int32_t tbsCertOffs;
	const uint8_t *pDataEnd;

	if (!pCert || !pData) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	do {
		if (dataLen < 10) {
			result = -FCSERR_ENOBUFS;
			break;
		}

		pDataEnd = pData + dataLen;
		memset(pCert, 0, sizeof(struct CertificateData));

		/* Certificate  ::=  SEQUENCE */
		offs += GetTag(&pData[offs], pDataEnd, &tag, &len);
		if (tag != 0x30) {
			result = -FCSERR_EVCC;
			break;
		}
		/* TBSCertificate ::== SEQUENCE */
		pCert->pTBSCertificate = &pData[offs];
		offs += GetTag(&pData[offs], pDataEnd, &tag, &len);
		if (tag != 0x30) {
			result = -FCSERR_EVCC;
			break;
		}

		pCert->tBSCertificateLength = &pData[offs + len] -
			pCert->pTBSCertificate;
		tbsCertOffs = offs;
		offs += len;

		/* signatureAlgorithm ::== SEQUENCE */
		offs += GetTag(&pData[offs], pDataEnd, &tag, &len);
		if (tag != 0x30) {
			result = -FCSERR_EVCC;
			break;
		}
		offs += len;

		/* signatureValue ::== BIT STRING */
		offs += GetTag(&pData[offs], pDataEnd, &tag, &len);
		if (tag != 0x3) {
			result = -FCSERR_EVCC;
			break;
		}
		if (len < 129) {
			result = -FCSERR_EVCC;
			break;
		}
		/* First byte is a zero, skip this */
		pCert->signatureLength = len - 1;
		pCert->pSignature = &pData[offs + 1];

		offs = tbsCertOffs;

		/* version */
		offs += GetTag(&pData[offs], pDataEnd, &tag, &len);
		if (tag != 0xa0) {
			result = -FCSERR_EVCC;
			break;
		}
		offs += len;

		/* serialNumber */
		offs += GetTag(&pData[offs], pDataEnd, &tag, &len);
		if (tag != 0x2 || len < 1) {
			result = -FCSERR_EVCC;
			break;
		}
		/*
		 * Remove OpenSSL sign conversion - a leading zero
		 * is inserted to ensure a non negative number
		 */
		if (pData[offs] == 0) {
			offs++;
			len--;
		}
		if (len > 1) {
			pCert->serialNumber = (pData[offs] << 8) | pData[offs
				+ 1];
		} else if (len == 1) {
			pCert->serialNumber = pData[offs];
		} else {
			result = -FCSERR_EVCC;
			break;
		}
		offs += len;

		/* signature, issuer, validity, subject */
		for (k = 0; k < 4; k++) {
			offs += GetTag(&pData[offs], pDataEnd, &tag, &len);
			if (tag != 0x30) {
				result = -FCSERR_EVCC;
				break;
			}
			offs += len;
		}

		/* subjectPublicKeyInfo */
		offs += GetTag(&pData[offs], pDataEnd, &tag, &len);
		if (tag != 0x30) {
			result = -FCSERR_EVCC;
			break;
		}

		/* algorithm */
		offs += GetTag(&pData[offs], pDataEnd, &tag, &len);
		if (tag != 0x30) {
			result = -FCSERR_EVCC;
			break;
		}
		offs += len;

		/* subjectPublicKey */
		offs += GetTag(&pData[offs], pDataEnd, &tag, &len);
		if (tag != 0x03) {
			result = -FCSERR_EVCC;
			break;
		}
		extOffs = offs + len;
		offs++;  /* skip the zero */

		/* RSAPublicKey */
		offs += GetTag(&pData[offs], pDataEnd, &tag, &len);
		if (tag != 0x30) {
			result = -FCSERR_EVCC;
			break;
		}

		/* modulus */
		offs += GetTag(&pData[offs], pDataEnd, &tag, &len);
		if (tag != 0x02) {
			result = -FCSERR_EVCC;
			break;
		}
		offs++;
		len--;

		pCert->publicKey.item_m.len = len;
		pCert->publicKey.item_m.data = (uint8_t *)malloc(len);
		if (!pCert->publicKey.item_m.data) {
			result = -FCSERR_ENOMEM;
			break;
		}
		memcpy(pCert->publicKey.item_m.data, &pData[offs], len);
		offs += len;

		/* publicExponent */
		offs += GetTag(&pData[offs], pDataEnd, &tag, &len);
		if (tag != 0x02) {
			result = -FCSERR_EVCC;
			break;
		}

		pCert->publicKey.item_e.len = len;
		pCert->publicKey.item_e.data = (uint8_t *)malloc(len);
		if (!pCert->publicKey.item_e.data) {
			result = -FCSERR_ENOMEM;
			break;
		}
		memcpy(pCert->publicKey.item_e.data, &pData[offs], len);

		/* extensions */
		offs = extOffs;
		offs += GetTag(&pData[offs], pDataEnd, &tag, &len);
		if (tag != 0xa3) {
			result = -FCSERR_EVCC;
			break;
		}

		offs += GetTag(&pData[offs], pDataEnd, &tag, &len);
		if (tag != 0x30) {
			result = -FCSERR_EVCC;
			break;
		}

		offs += GetTag(&pData[offs], pDataEnd, &tag, &len);
		if (tag != 0x30) {
			result = -FCSERR_EVCC;
			break;
		}

		offs += GetTag(&pData[offs], pDataEnd, &tag, &len);
		if (tag != 0x6) {
			result = -FCSERR_EVCC;
			break;
		}
		offs += len;

		/* read SSN */
		offs += GetTag(&pData[offs], pDataEnd, &tag, &len);
		if (tag != 0x4) {
			result = -FCSERR_EVCC;
			break;
		}
		if (len != 3) {
			result = -FCSERR_EVCC;
			break;
		}
		if (pData[offs] != 0x2 || pData[offs + 1] != 0x1) {
			result = -FCSERR_EVCC;
			break;
		}
		pCert->ssn = pData[offs + 2];

	} while (0);

	if (result != FCSERR_OK)
		deinit_public_key(&pCert->publicKey);

	return result;
}

