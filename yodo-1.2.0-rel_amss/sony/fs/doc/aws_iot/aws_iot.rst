Introduction
============

Every device in the AWS IoT platform must contain a device
certificate, uniquely identifying it to the cloud services. These
certificates are signed by a common CA certificate, which has been
registered as a trusted certificate in the AWS IoT system.

This document describes how to handle keys and certificates for
projects that utilize security servers in conjunction with the AWS IoT
platform\ [#aws]_.

.. seealso::

   `Use Your Own Certificate
   <http://docs.aws.amazon.com/iot/latest/developerguide/device-certs-your-own.html>`_
   in the AWS IoT documentation.

Terminology
===========

Definitions
-----------

Security Server
   A server computer designed to securely store cryptographic keys,
   and to provide an API to perform operations with those keys.

Server Administrator
   The person, or team, responsible for provisioning cryptographics
   keys and certificates to the Security Server.

Project
   This is the organization that is responsible for the execution of a
   product project. This is sometimes, but certainly not always, the
   same organization that is responsible for the Security Server.

CSR
   Certificate Signing Request, as specified in [RFC2986]_.

TLS
   Transport Layer Security, a protocol for encrypting and
   authenticating network traffic.

TEE
   Trusted Execution Environment, an isolated environment inside the
   device, which is used to prevent leakage of sensitive information,
   such as encryption keys. An example of an implementation of TEE is
   the ARM Security Extensions (TrustZone).

Requirements
------------

The key words "MUST", "MUST NOT", "REQUIRED", "SHALL", "SHALL NOT",
"SHOULD", "SHOULD NOT", "RECOMMENDED", "MAY", and "OPTIONAL" in this
document are to be interpreted as described in [RFC2119]_.

CA Certificate
==============

This section describes the process of generating a new CA certificate,
and registering it with the AWS IoT platform. The process is
illustrated in :numref:`regrootca`, and described below.

.. note::
   Although the diagram implies that this is an automated process with
   a well-defined API, the process MAY, and most likely will, be
   handled manually.

.. _regrootca:

.. uml::
   :align: center
   :caption: Registration of CA certificate

   hide footbox

   participant "Project" as prj
   participant "Server Administrator" as admin
   participant "AWS IoT" as aws

   activate prj
   prj -> aws: getRegistrationCode()
   activate aws
   aws -> prj: RegistrationCode
   deactivate aws

   ...

   prj -> admin: getCACertificate(RegistrationCode, CAInfo)
   activate admin
   admin -> prj: CACertificate, VerificationCertificate
   deactivate admin

   prj -> aws: registerCACertificate(CACertificate, VerificationCertificate)
   activate aws
   aws -> prj: CertID
   deactivate aws

   prj -> aws: updateCACertificate(CertID, ACTIVE)
   activate aws
   aws -> prj: OK
   deactivate aws

The first step in registering a CA certificate is to fetch the
registration code. To register a CA certificate with the AWS IoT
platform, a registration code is necessary. The code can be fetched
through the AWS CLI::

   $ aws iot get-registration-code

.. note::
   In the normal case, all the interaction with the AWS IoT platform
   SHOULD be handled by the Project, but the entire registration
   process MAY be handled by the Server Administrator where
   appropriate.

The registration code is then sent to the Server Administrator, who
generates a new private key for the CA certificate, the CA certificate
itself, and the corresponding verification certificate. The request
SHOULD also include enough information, such as the Distinguished Name
of the certificate subject, for the Server Administrator to be able to
generate correct certificates.

The verification certificate, which is used to prove that we have
access to the private key, MUST have the CA certificate as issuer, and
MUST contain the registration code in the Common Name (CN) field. The
CA certificate, and the private key, is either generated directly on
the Security Server, or installed there by the Server Administrator.

.. note::
   In order to register a new CA certificate, it is necessary to log
   in to an AWS account with the necessary access permissions. Due to
   this, it is not strictly necessary to keep the registration code
   secure. Despite this, the code, and certificates containing the
   code, SHOULD be encrypted whenever possible.

Once the CA certificate has been generated, it needs to be registered
with the AWS IoT platform. In order to do so, the CA certificate and
the corresponding verification certificate is sent to AWS. This can be
done through the AWS CLI::

   $ aws iot register-ca-certificate --ca-certificate <ca-file> \
   --verification-certificate <ver-file>

If the registration is successful, a certificate ID is returned for
the CA certificate. This ID is used for subsequent changes to the CA
certificate in the AWS IoT platform.

As the last step, the CA certificate needs to be activated. Until the
CA certificate is activated, no devices bound to that CA certificate
may connect to the AWS IoT platform. This can be accomplished with the
AWS CLI as follows::

   $ aws iot update-ca-certificate --certificate-id <ca-id> --new-status ACTIVE

.. note::
   It is possible to register and activate the certificate in one
   operation. For more details, see the AWS IoT documentation.


Device Certificate
==================

In order to connect to AWS IoT, every device MUST have a unique
identity. To prove the identity of a device, a Device Certificate is
used as the client certificate when connecting with TLS.

A Device Certificate MUST be unique, and MUST be generated during
manufacturing. Access to this functionality MUST be protected by an
appropriate authorization system, to prevent unauthorized generation
of certificates. To avoid leaking the key, the RSA keypair SHOULD be
generated inside the device. After the key is generated, it needs to
be used to generate a Device Certificate. This SHOULD be done by
building a CSR, which is sent to the Security Server for signing. The
resulting Device Certificate MUST then be written to the device. The
entire process is illustrated in :numref:`generatecert`.

.. _generatecert:

.. uml::
   :align: center
   :caption: High-level overview of Device Certificate provisioning

   hide footbox

   participant Server as srv
   participant "Factory Tool" as factory
   participant Flashloader as ldr

   activate factory
   factory -> ldr: getCSR()
   activate ldr
   ldr -> factory: CSR
   deactivate ldr

   factory -> srv: getCertificate(CSR)
   activate srv
   srv -> factory: Certificate
   deactivate srv

   factory -> ldr: setCertificate(Certificate)
   activate ldr
   ldr -> factory: OK
   deactivate ldr

Depending on the capabilities of the specific device, the key
generation MAY be performed inside a TEE. The explanation in the
following two paragraphs is only relevant when a TEE is used.

Under normal circumstances, the TEE does not have direct access to
storage or communication links, so many I/O operations need to be
handled outside the TEE. In order to securely store the private key,
it MUST be encrypted, using a hardware key only accessible by the TEE,
before it is moved outside of the TEE. The certificate generation
process can be seen in :numref:`teegeneration`.

When a Device Certificate is generated by the TEE, it is not
immediately available from the normal software, running outside of the
TEE. In order to use the Device Certificate for TLS authentication, a
call must be made into the TEE, to sign (or encrypt, where applicable)
the necessary data during the TLS handshake. After the TLS handshake
and key is complete, the session key is available outside of the TEE.

.. _teegeneration:

.. uml::
   :align: center
   :caption: CSR generation with TEE

   hide footbox

   participant Flashloader as ldr
   participant TEE as tee
   database "Flash Memory" as flash

   [-> ldr: getCSR()
   activate ldr

   ldr -> tee: generatePrivateKey()
   activate tee
   tee -> ldr: EncryptedPrivateKey, PublicKey
   deactivate tee

   ldr -> ldr: Info = generateRequestInfo(PublicKey)

   ldr -> tee: sign(Info, EncryptedPrivateKey)
   activate tee
   tee -> ldr: Signature
   deactivate tee

   ldr -> ldr: CSR = buildCSR(Info, Signature)

   ldr -> flash: write(EncryptedPrivateKey)
   activate flash
   flash -> ldr: OK
   deactivate flash

   [<- ldr: CSR
   deactivate ldr

   ...

   [-> ldr: setCertificate(Certificate)
   activate ldr
   ldr -> flash: write(Certificate)
   activate flash
   flash -> ldr: OK
   deactivate flash
   [<- ldr: OK
   deactivate ldr

Once the Device Certificate is generated and provisioned into the
device, it MUST be registered in the AWS IoT system. Registration can
be done in two ways: either the Device Certificate is automatically
registered at the first connection attempt\ [#autoreg]_, or it may be
manually registered using the following command::

   $ aws iot register-certificate --certificate-pem <cert-file> --ca-certificate-pem <ca-file>

The last remaining step is to activate the certificate. This MUST be
done, so that the device can continue to communicate with the AWS IoT
platform::

   $ aws iot update-certificate --certificate-id xxxxxxxxxxx --new-status ACTIVE

Once all of this is done, the device is ready to be used.

.. rubric:: Footnotes

.. [#aws] For details about AWS IoT, see https://aws.amazon.com/iot-platform/

.. [#autoreg] This is achieved by enabling the Just-in-Time
              registration feature in AWS IoT
