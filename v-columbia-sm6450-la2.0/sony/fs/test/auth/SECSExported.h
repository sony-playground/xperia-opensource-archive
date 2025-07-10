/*
 * Copyright (c) 2014 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef __INCLUSION_GUARD_SECSEXPORTED_INCLUDED_H_
#define __INCLUSION_GUARD_SECSEXPORTED_INCLUDED_H_

#include <stddef.h>

/*! \mainpage
This documentation describes the functions available in the SECS API,
the data structures used, and the error codes returned.<br>
<br>
<H3>NOTE: The documentation is confidential which means that it may not be entered into metadoc.</H3>

<H3>General</H3>
This documentation describes the functions available in the SECS API,
the data structures used, and the error codes returned.
This document is either SECSExported.h or generated using doxygen from SECSExported.h.
The SECSExported.h format is therefore the source document and is the one that is version controlled.
This document is confidential and must for example not be entered into metadoc.
The latest version can be found on the sec-net and in the future often also via netshare.
Parts have been inspired or copied from the FxTool developers guide.

<H3>Developers guide</H3>
The SECS.dll is used to access the functions of a SECS server.
The SECS.dll is used by for example FxTool, Flash Gordon II & 3 and Signatory.

<H4>Error handling</H4>
All functions return #SECS_SUCCESS on success and some error code from #T_SECSErrorCodesExp on error.
An error message can be obtained using SGN_ReadErrorMessage() or SGN_ReadFullFactoryErrorMessage().
If the error code is #SECS_ERROR_SGN_ERRORCODE, there is further information about the error and a further error code available in the text error message obtained by these two functions.

SGN_ReadFullFactoryErrorMessage()
SGN_ReadCompoundErrorMessage()

<H3>Abbreviations/definitions</H3>
<TABLE>
<TR><TD>SECS</TD><TD>SECurity Servers</TD></TR>
<TR><TD>CS</TD><TD>Customer Services</TD></TR>
<TR><TD>SGN</TD><TD>Sign/Signing/Signature</TD></TR>
<TR><TD>EMMA III</TD><TD>CS client/server solution.</TD></TR>
<TR><TD>IMEI</TD><TD>14 ASCII digit null terminated string. Longer IMEI should be truncated to length 14 by removing any check digits and software revision numbers (SVN).</TD></TR>
</TABLE>
*/

#ifdef DOXYGEN
  // This class just makes doxygen happy enough to include the function documentations below...
  class SECS {
  public:
//# define CONSTANT const
# define SECS_RETURN_CODE T_SECSErrorCodesExp
# define EXCLUDE_DEPRECATED
#else
//# define CONSTANT
# define SECS_RETURN_CODE unsigned int
#endif

//////////////////////////////////////////////////////////////////
// SECSExported.h : exported header for the SECS DLL
//
#ifdef __cplusplus
# ifdef WIN32
#  ifdef SECS_EXPORTS
#   define SECS_API extern "C" __declspec(dllexport)
#  else
#   define SECS_API extern "C" __declspec(dllimport)
#  endif
# else
#  define SECS_API extern "C"
# endif
#else
// compiled as C
# ifdef WIN32
#  ifdef SECS_EXPORTS
#   define SECS_API __declspec(dllexport)
#  else
#   define SECS_API __declspec(dllimport)
#  endif
# else
#  define SECS_API
# endif
# define bool int
#endif

//////////////////////////////////////////////////////////////////
//

/**
 * \defgroup ErrorCodeExp SECS API Error Codes
 */
/*@{*/
  enum T_SECSErrorCodesExp {

  /// Operation succeeded.
  SECS_SUCCESS = 0,

  ////////////////////////////////////////////////////////////////
  // Fatal error codes

  /// Normally a default error. Probable causes are a problem with the DLL, its environment or its inputs.
  SECS_ERROR_GENERAL = 0x1010,
  /// A new thread cannot be started since the maximum number of threads has been reached.
  SECS_ERROR_NO_HANDLE_LEFT,
  /// An input buffer expected to contain values was NULL.
  SECS_ERROR_PASSED_NULL_POINTER,
  /// This error code is not used.
  SECS_ERROR_NOT_RECOVERY_LOADER,
  /// The IMEI number is not 14 digits long.
  SECS_ERROR_IMEI_NOT_CORRECT,
  /// The device ID is either NULL or not 16 bytes long.
  SECS_ERROR_DEVICE_ID_NOT_CORRECT,

  ////////////////////////////////////////////////////////////////
  // Part 22 Error codes

  /// This error code is not used.
  SECS_ERROR_PART_22_UNLOCK_ERROR,

  ////////////////////////////////////////////////////////////////
  // Certificate reset errorcodes

  /// Error loading or using the local client certificate.
  SECS_ERROR_BAD_CERTIFICATE,
  /// This error code is not used.
  SECS_ERROR_LOADING_SW_COMPONENT,
  /// This error code is not used.
  SECS_ERROR_NO_CARD_IN_READER,
  /// This error code is not used.
  SECS_ERROR_GET_SERIAL_NUMBER,
  /// This error code is not used.
  SECS_ERROR_GET_PIN_AND_KEY_FROM_SERIAL,
  /// This error code is not used.
  SECS_ERROR_VERIFY_PIN,
  /// This error code is not used.
  SECS_ERROR_SELECT_KEY,
  /// This error code is not used.
  SECS_ERROR_AUTHENTICATION_RESPONSE_ERROR,

  ////////////////////////////////////////////////////////////////
  // Certificate general errorcodes

  /// Failed to flash certificate on ME.
  SECS_ERROR_PUT_CERTIFICATE_ERROR,
  /// This error code is not used.
  SECS_ERROR_CERTIFICATE_DATA_NOT_FOUND,
  /// This error code is not used.
  SECS_ERROR_CERTIFICATE_DATA_UNKNOWN_ERROR,

  ////////////////////////////////////////////////////////////////
  // SGN_TOOL

  /// This error code is not used.
  SECS_ERROR_SGN_EROMCERTSIGNATURE,
  /// This error code is not used.
  SECS_ERROR_SGN_VERIFYEROM,
  /// This error code is not used.
  SECS_ERROR_SGN_CRODMESSAGE,
  /// This error code is not used.
  SECS_ERROR_SGN_SIMLOCKSIGNATURE,
  /// This error code is not used.
  SECS_ERROR_SGN_GETSIGNCONFIG,
  /// This error code is not used.
  SECS_ERROR_SGN_GETTACLIST,
  /// SGN Tool object could not be initialized.
  SECS_ERROR_SGN_NOT_INITIALIZED,
  /// This error code is not used.
  SECS_ERROR_SGN_WINLOGINIT,
  /// Either you have not initialized the objects, or are trying to do too many simultaneous invocations (max 64 allowed).
  SECS_ERROR_THREADTABLE_NOT_INITIALIZED,
  /// Could not find the SGNTool DLL.
  SECS_ERROR_SGNOBJECT_NOT_INITIALIZED,
  /// A result buffer that was expected to be pre-allocated was NULL.
  SECS_ERROR_SGN_MISSING_TARGET,
  /// The specified DRM certificate type is unknown.
  SECS_ERROR_SGN_WRONG_CERTTYPE,
  /// This error code is not used.
  SECS_ERROR_SGN_GETCERTIFICATE,
  /// The pre-allocated result buffer is too small to contain the result.
  SECS_ERROR_SGN_BUFFERLENGTH,
  /// This error code is not used.
  SECS_ERROR_SGN_MAXKEYCODES,
  /// This error code is not used.
  SECS_ERROR_SGN_UNKNOWN_ERRORCODE,
  /// General error. There is further information about the error and a further error code available in the text error message obtained by these two functions.
  SECS_ERROR_SGN_ERROR,
  /// An error code returned by the server or the DLL. For more information, read the translated error code.
  SECS_ERROR_SGN_ERRORCODE,
  /// The specified production mode is not a valid production mode.
  SECS_ERROR_PRODMODE_NOTDEFINED,
  /// This error code is not used.
  SECS_ERROR_SSWCTAG_AND_CTAG_NOTDEFINED,
  /// This error code is not used.
  SECS_ERROR_SSWCTAG_NOTDEFINED,
  /// The SIM lock current GDFS unit count is 0.
  SECS_ERROR_CUNIT_EQZERO,
  /// The SIM lock new GDFS unit count is 0.
  SECS_ERROR_NEWCUNIT_EQZERO,
  /// The SIM lock GDFS unit count is invalid.
  SECS_ERROR_WRONG_UNIT_COUNT,
  /// The SIM lock GDFS unit sequence is incorrect.
  SECS_ERROR_BAD_UNIT_SEQUENCE,
  /// The size of the GDFS data is too small.
  SECS_ERROR_INSUFFICIENT_GDFS_DATA,
  /// The specified parameter value is outside the expected range.
  SECS_ERROR_PARAMETER_OUT_OF_RANGE,
  /// The input parameters do not have the expected values.
  SECS_ERROR_BAD_PARAMETERS,
  /// Could not get a CMLA certificate from the database.
  SECS_GETNEXTCERT_FAILED,
  /// The handle index must be a value between 1 and 64.
  SECS_ERROR_BAD_HANDLE_INDEX,
  /// The version response did not contain a valid HWCONF_PK_HASH tag.
  SECS_ERROR_BAD_VERSION_RESPONSE,
  /// The version response string does not contain an expected tag.
  SECS_ERROR_MISSING_VERSION_RESPONSE_TAG,
  /// The specified DRM generation is not supported.
  SECS_ERROR_UNSUPPORTED_DRM_GENERATION,
  /// The specified DRM certificate type is not supported for the specified DRM generation.
  SECS_ERROR_UNSUPPORTED_DRM_CERTIFICATE_TYPE,
  /// Some input parameter was too large for SECS client to handle.
  SECS_ERROR_PARAMETER_TOO_LARGE,
  /// No Transaction ID was supplied, NULL passed.
  SECS_ERROR_PASSED_NULL_TRID,
  /// No Transaction ID Signature was supplied, NULL passed.
  SECS_ERROR_PASSED_NULL_TRID_SIGNATURE,
  /// An input buffer expected to contain values was empty.
  SECS_ERROR_PASSED_ZERO_LEN,
  /// No Transaction ID Signature was supplied, length 0 passed.
  SECS_ERROR_PASSED_ZERO_LEN_TRID_SIGNATURE,
  /// No IMEI number was supplied, NULL passed.
  SECS_ERROR_PASSED_NULL_IMEI,
  /// This is not an error code as such, it is just a value used for debug purposes.
  SECS_END_OF_NORMAL_ERROR_CODES,


  ////////////////////////////////////////////////////////////////
  /// Returned by deprecated functions
  SECS_ERROR_DEPRECATED = 0x40001010,

  ////////////////////////////////////////////////////////////////
  /**************************************************************/
  ////////////////////////////////////////////////////////////////
  // Warning codes
  ////////////////////////////////////////////////////////////////

  // Certificate reset warnings
  /// This error code is not used.
  SECS_WRN_MESSAGE = 0x80001010,
  /// Returned by functions that are not yet fully implemented.
  SECS_WRN_NOT_YET_IMPLEMENTED,
};
/*@}*/


//////////////////////////////////////////////////////////////////
//  Data types
//////////////////////////////////////////////////////////////////
/**
 * \defgroup PubTypes Public Data Types
 */
/*@{*/

#define MAXFILENAME          260
#define MAXURLSTRING         260
#define MAXTAGSIZE           32
#define MAXNOOFTACS          65
#define MAXNOOFKEYCODES      16
#define MAXKEYCODELENGTH     16
#define IMEILENGTH           14
#define MIN_DEVICE_ID_LENGTH 16
#define MAXDONGLEIDLENGTH    128

/// The available production modes.
typedef enum SGN_ProdModeType { _TEST=0, _LIVE } T_SGN_ProdModeType;

/// DON'T CARE  (The available log levels)
typedef enum SGN_LogLevel { _NONE=0, _ERR, _WRN, _INFO, _DEB, _LOG, _DUMP } T_SGN_LogLevel;

/// The available protocol types.
typedef enum SGN_ProtocolType { _PROTOCOL_P22=1, _PROTOCOL_RSA } T_SGN_ProtocolType;
/// The available key types.
typedef enum SGN_KeyType { _A0_RESET=1, _A1_RESET, _UMTS_TEST, _DUMMY_1, _DUMMY_2,
                           _DB2020_RESET, _DB31XX_RESET, _DB2010_RESET, _DB2000_RESET} T_SGN_KeyType;
/// The available device types.
typedef enum SGN_DeviceType { _AUTO=1, _SMARTCARD, _P22ALGORITHM, _P96ALGORITHM} T_SGN_DeviceType;
/// The available key store types.
typedef enum SGN_KeyStoreTypes { _CERT=1, _PIN, _TAC, _P22, _CFG, _ROOT, _SLF, _DEVICE, _CERTTYPE} T_SGN_KeyStoreTypes;
/// The available types of signatures.
typedef enum SGN_SignTypes { _SIGNTYPE_SSW=0, _SIGNTYPE_FOTA, _SIGNTYPE_SFA, _SIGNTYPE_EMBEDDEDS1, _SIGNTYPE_S1, _SIGNTYPE_UNDEF=99 } T_SGN_SignTypes;
/// The available remote lock states.
typedef enum SGN_RemoteLockState { _NOT_LOCKABLE=0, _UNLOCKED, _LOCKED } T_SGN_RemoteLockState;
//////////////////////////////////////////////////////////////////
/**
 * Additional configuration used when getting an extended handle.
 * Note that CertNameStr, LogLevel and LogFilename are not used for anything.
 * Nothing will be logged, neither to file nor to stdout.
 */
typedef struct ExtendedSECSConfig {
  /// Device type.
  /** @param uiDeviceType dev type.
  */
  unsigned  int uiDeviceType;
  /// Key type.
  unsigned  int uiKeyType;
  /// DON'T CARE (Certificate name string)
  char CertNameStr[MAXTAGSIZE];
  /// DON'T CARE (Log level)
  T_SGN_LogLevel LogLevel;
  /// DON'T CARE (Log file name)
  char LogFilename[MAXFILENAME];
} T_ExtendedSECSConfig;
//////////////////////////////////////////////////////////////////
/**
 * Represents a unit of GDFS data.
 */
typedef struct SECS_GDFSUnitData {
  /// The block number of this GDFS unit.
  unsigned char GDFSBlockNumber;
  /// The unit number of this GDFS unit.
  unsigned short GDFSUnitNumber;
  /// The number of valid bytes in this GDFS unit.
  unsigned int GDFSDataSize;
  /// The GDFS data.
  char* GDFSData;
} T_SECS_GDFSUnitData;
//////////////////////////////////////////////////////////////////
/**
 * Represents a unit of data, irrespective of whether it is GDFS, TA or something else.
 */
typedef struct SECS_UnitData {
  /// The name of the unit describing the Data.
  char* UnitName;
  /// The size of written Data. If no data is written, DataSize contains the allocated size for Data.
  unsigned int DataSize;
  /// The Data corresponding to the unit name.
  char* Data;
} T_SECS_UnitData;

typedef struct SGN_LastRequestInfo {
  char authCertId[MAXDONGLEIDLENGTH];
  char url[MAXURLSTRING];
  char proxy[MAXURLSTRING];
} T_SGN_LastRequestInfo;

/**
 *  The enum of known sequenceIDs.
 */
enum SequenceIds {
  /// Hardware platform A1
  HWP_A1 = 0,
  /// Hardware platform S1 Locosto. (As far as is currently known, this can also be used for Neptune.)
  HWP_S1_Locosto = 1,
  /// Hardware platform A2
  HWP_A2 = 2,
  // All input data stored in unit 2010 instead of three separate units.
  HWP_S1_ONEUNIT = 3,
  HWP_SEMC_S1 = 4,
  /// The number of hardware platforms.
  NBR_HWP
};

// DRM Generation values
#define SGN_DRM_GEN0 0
#define SGN_DRM_GEN1 3
#define SGN_DRM_GEN4 4
#define SGN_DRM_GEN4_WITH_CKB0 0x00010004
#define SGN_DRM_GEN4_WITH_CKB1 0x00110004
#define SGN_DRM_GEN4_WITH_CKB2 0x00210004

// Certificate type and License key type values
#define SGN_CERTIFICATE_PROD_CA_VER1   7
#define SGN_CERTIFICATE_PROD_CA_VER2   8
#define SGN_CERTIFICATE_CMLA_BULK      9
#define SGN_CERTIFICATE_CMLA          10
#define SGN_CERTIFICATE_SEMCDRM       11
#define SGN_CERTIFICATE_VIACCESS      12
#define SGN_CERTIFICATE_MICROSOFT     13
#define SGN_CERTIFICATE_MARLIN        14
#define SGN_CERTIFICATE_HDCP_AV8100   15
#define SGN_CERTIFICATE_CDMA_AKEY     16
#define SGN_CERTIFICATE_PLAYREADY     17
#define SGN_CERTIFICATE_MARLIN_IMPORT 18
#define SGN_CERTIFICATE_DTCP_IP       19
#define SGN_CERTIFICATE_WIDEVINE      20
#define SGN_CERTIFICATE_MIRRORLINK    21
#define SGN_CERTIFICATE_HDCP2         22
#define SGN_CERTIFICATE_CKB           23
#define SGN_LICENSE_PVK               24
#define SGN_LICENSE_OVK               25
#define SGN_CERTIFICATE_TBK           26
#define SGN_CERTIFICATE_ANDATT        27

// RSA Sign type values
#define SGN_RSASIGN_OTHER    0
#define SGN_RSASIGN_LOADER   1
#define SGN_RSASIGN_SEMCBOOT 2

/*@}*/

//#ifndef EXCLUDE_DEPRECATED
  #include "SECSDeprecated.h"
//#endif

/**
 * \defgroup SecsAPI SECS API Functions
 */
/*@{*/

//////////////////////////////////////////////////////////////////
// Methods - GENERAL
//

/**
 * Returns the handle to use during communication within thread.
 * Within thread means every thread calling SECS should have a separate handle, or that many
 * threads may not share a single handle. On the other hand, one handle should be used for
 * as long as is possible, probably during the entire communication session with a device.<br>
 * Alternative method to SGN_GetExtHandle() that provides fewer configurable parameters.<br>
 * @param pURL [in] URL address to server.
 * @param pRootStr [in] Address to source structure.
 * @param pHandleIndex [out] Pointer to a handle index.
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetHandle(
  const char* pURL,
  const char* pRootStr,
  unsigned int* pHandleIndex);

/**
 * Returns the handle to use during communication within thread.
 * Alternative method to SGN_GetHandle() that provides more configurable parameters.<br>
 * @param pURL [in] URL address to server.
 * @param pRootStr [in] Address to source structure.
 * @param pHandleIndex [out] Pointer to a HandleIndex.
 * @param pExtendedSECSConfig [in] Pointer to ExtendedSECSConfig.
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetExtHandle(
  const char* pURL,
  const char* pRootStr,
  unsigned int* pHandleIndex,
  const T_ExtendedSECSConfig* pExtendedSECSConfig);

/**
 * Releases the handle \p handleIndex.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_ReleaseHandle(unsigned int handleIndex);

/**
 * Set proxy used to communicate with server through the specified handle. It works like this:
 *
 * - If you call the function with a non-NULL and a non-empty string as ProxyName, the supplied
 *   proxy will be used.
 * - If you do not call the function or call it with NULL or an empty string as ProxyName on a
 *   Windows operating system, the following registry entry will be used as proxy:
 *   \\HKEY_LOCAL_MACHINE\\SOFTWARE\\Sony Ericsson\\SECS\\proxy. If the registry has no such value,
 *   the default WinHTTP proxy will be used.
 * - If you do not call the function or call it with NULL or an empty string as ProxyName on a
 *   Linux operating system, the environment variable http_proxy/https_proxy will be used as proxy
 *   (as documented by cURL). If the environment has no such variable, no proxy will be used.
 *
 * The proxy specification is interpreted like this (whether supplied from SGN_SetProxy() or the registry):
 * "SYSTEM" (without the quotes) means that a system defined proxy should be used. "NONE" (without the
 * quotes) means that no proxy should be used. All other values are interpreted as host names.
 *
 * @param ProxyName (in) A string with the server name
 * @param handleIndex (in) handleIndex received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_SetProxy(
  const char* ProxyName,
  unsigned int handleIndex);

/**
 * Set the authenticate certificate ID (see SGN_GetLastRequestInfo() ) to be used for authentication
 * in client request. This is a good idea if there are multiple certificates available from
 * a usable certificate issuer, in which case the SECS client will use this information to choose
 * correctly. It is not necessary to use this API. If it is not used, the SECS client will use the
 * first certificate by a usable certificate issuer.
 * @param AuthCertId (in) A string with the client authentication certificate ID, e.g. 'RD4200000007'
 * @param handleIndex (in) handleIndex received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_SetAuthCertId(
  const char* AuthCertId,
  unsigned int handleIndex);

/**
 * Set the authentication certificate file name to be used for client authentication when
 * using curl (which is used for Linux).
 * The cert file must be a PEM format combined public cert and private key file.
 * @param pAuthCertFile [in] A string with a path to the client certificate file.
 * @param pPassphrase [in] A string containing the passphrase for the private key stored in \p pAuthCertFile.
 * If the cert file has no passphrase, this parameter should be set to NULL or an empty string.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_SetAuthCertFile(
    const char* pAuthCertFile,
    const char* pPassphrase,
    unsigned int handleIndex);

/**
 * Prepare the usage of a authentication token via a PKCS#11 engine by setting the engine and module names.
 * This method of authentication is only available when using curl (which is used for Linux).
 * @param pEngineName [in] A string with the file name of the PKCS#11 engine, for instance 'engine_pkcs11.so'.
 * If the engine is not located in the OS standard library path the full path of the engine .so file should be supplied,
 * for instance '/usr/lib/ssl/engines/engine_pkcs11.so'.
 * @param pModuleName [in] A string with the file name of the PKCS#11 module, for instance 'libaetpkss.so'. If the module
 * is not located in the OS standard library path the full path of the module .so file should be supplied.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_PrepareAuthPKCS11Engine(
    const char* pEngineName,
    const char* pModuleName,
    unsigned int handleIndex);

/**
 * Set the usage of a authentication token when authenticating server access.
 * Tokens will be scanned and the token matching \p pTokenName will be activated. If no matching token was found,
 * the call will fail. The token will not be used for authentication until a call accessing the server is made.
 * Note that a successful call to SGN_PrepareAuthPKCS11Engine() must be made before calling SGN_SetAuthToken().
 * @param pTokenName [in] A string with the name of the token which should be used.
 * @param pPassphrase [in] A string containing the passphrase for the authentication token.
 * If the authentication token has no passphrase, this parameter should be set to NULL or an empty string.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_SetAuthToken(
    const char* pTokenName,
    const char* pPassphrase,
    unsigned int handleIndex);

/**
 * Translates the error code \p ErrorCode into readable text and returns it in \p Message,
 * e.g. the error code 4112 (SECS_ERROR_GENERAL) is translated to the string "SECS_ERROR_GENERAL".
 * @param Message [out] The readable text corresponding to the error code ErrorCode, or the string
 * "Can't translate error code" if the error code does not have a translation.
 * @param MessageSize [in] The size of the allocated readable text buffer. A size of at least 1k is recommended.
 * @param ErrorCode [in] The error code that is to be translated to text.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_ReadErrorMessage(
  char* Message,
  int MessageSize,
  unsigned int ErrorCode,
  unsigned int handleIndex);

/**
 * Translates the error code \p ErrorCode into long readable text
 * and returns it in \p Message (by using SGN_ReadErrorMessage() ).
 * @param Message [out] Error message.
 * @param MessageSize [in] Message size allocated. A size of at least 2k is recommended.
 * @param ErrorCode [in] Error code that will be translated.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_ReadFullFactoryErrorMessage(
  char* Message,
  int MessageSize,
  unsigned int ErrorCode,
  unsigned int handleIndex);

/**
 * Returns a string containing the complete error status. This API may be useful for printing the complete error status to a log etc.
 * when an error occurs. The message string contains TAGS and associated values the same way as FxTool and S1 Loaders/S1 Boot does.
 * This string should be forwards compatible, that is, new tags may be added in the future without breaking backwards compatibility.
 * The calling process must handle this. For instance, it is a bad idea to get the last tag and assume it is a specific tag.
 * The TAGS defined today are those in the example:
 *  CODE="0x1010";MESSAGE="text";EXTRA="";STATUS_CODE="-5000";STATUS_MESSAGE="text";EXTRA_CODE="6";SECS_API="SGN_SakeAuthenticate";
 *  SECS_TIME="20101224 14:00:00 (client)";SECS_SERVER="http://example.com/dispatch:80";
 *  SECS_PROXY="http://proxy.example.com";AUTH_CERT="text";SECS_INPARAMS="[inparams]".
 * TAGS may be empty and in that case the tag will look like MESSAGE="";
 * @param pMessage [out] Error message to receive the null terminated error status string.
 * @param messageSize [in] Message size allocated. A size of at least 2k is recommended.
 * @param errorCode [in] Error code that will be translated.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_ReadCompoundErrorMessage(
  char* pMessage,
  int messageSize,
  unsigned int errorCode,
  unsigned int handleIndex);

/**
 * Returns data from first step in a P22/P96 sequence in \p pStepOneData. In contrast to SGN_CSGetStepOneData_v2() this function accepts any valid P22/P96 key.
 * @param pKeyName [in] Name of a valid P22/P96 key (P22("KIDXXYY"), P96("KIDEXXYY", "KIDP96...")).
 * @param pStepOneData [out] Pre-allocated buffer that will contain the step one data.
 * If the buffer is too small you will get a #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, and \p pStepOneLength
 * will be set to the expected buffer size.
 * @param pStepOneLength [in/out] As input parameter, this is the size of the buffer.
 * A buffer size of at least 1024 bytes is recommended. As output parameter, this is the actual
 * length of the step one data returned.
 * @param pIMEIStr [in] IMEI (14 digits + null termination).
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetStepOneData_v2(
  const char* pKeyName,
  unsigned char* pStepOneData,
  unsigned int* pStepOneLength,
  const char* pIMEIStr,
  unsigned int handleIndex);

/**
 * Executes step 3 in a P22/P96 sequence
 * This has to be executed within 2 minutes of SGN_GetStepOneData() or SGN_ExecuteStepThree() will return an error.
 * @param pChallenge [in] Pointer to a challenge from ME (3 Bytes for P22, longer for P96).
 * @param challengeLen [in] Length of challenge data.
 * @param pResponse [out] Pre-allocated buffer that will contain the step three data, i.e. the algorithm response to the challenge from the ME.
 * If the buffer is too small you will get a #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, and \p pResponseLength
 * will be set to the expected buffer size.
 * @param pResponseLength [in/out] As input parameter, this is the size of the pre-allocated buffer. A buffer of at least 128 bytes is recommended.
 * As output parameter, this is the actual length of the response returned.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_ExecuteStepThree(
  const unsigned char* pChallenge,
  unsigned int challengeLen,
  unsigned char* pResponse,
  unsigned int* pResponseLength,
  unsigned int handleIndex);

/**
 * Executes step 3 in a P22/P96 sequence using transaction ID (TrID) for verification.
 * This has to be executed within 2 minutes of SGN_GetStepOneData() or SGN_ExecuteStepThree() will return an error.
 * @param pChallenge [in] Pointer to a challenge from ME (3 Bytes for P22, longer for P96).
 * @param challengeLen [in] Length of challenge data.
 * @param pResponse [out] Pre-allocated buffer that will contain the step three data, i.e. the algorithm response to the challenge from the ME.
 * If the buffer is too small you will get a #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, and \p pResponseLength
 * will be set to the expected buffer size.
 * @param pResponseLength [in/out] As input parameter, this is the size of the pre-allocated buffer. A buffer of at least 128 bytes is recommended.
 * As output parameter, this is the actual length of the response returned.
 * @param pTrID [in] Null terminated transaction ID on format TAG1="VALUE";TAG2="VALUE"
 * @param pTrIDSignature [in] TrID signature calculated over pTrID (signing certificate name should be part of pTrID).
 * @param trIDSignatureLength [in] Length of TrID signature in bytes.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_ExecuteStepThreeWithTrID(
  const unsigned char* pChallenge,
  unsigned int challengeLen,
  unsigned char* pResponse,
  unsigned int* pResponseLength,
  const char* pTrID,
  const unsigned char* pTrIDSignature,
  unsigned int trIDSignatureLength,
  unsigned int handleIndex);

/**
 * Executes steps in a P22/P96 sequence by calculating a response \p pResponse
 * to the challenge \p pChallenge.
 * @param pKeyName [in] KeyName
 * @param pIMEIStr [in] IMEI (14 digits + null termination)/OTP info
 * @param pChallenge [in] Pointer to a challenge from ME.
 * @param challengeLen [in] Length of challenge data
 * @param pResponse [out] Pointer to a  Algorithm response to the challenge.
 * If the buffer is too small you will get a #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, and \p pResponseLength
 * will be set to the expected buffer size.
 * @param pResponseLength [out] Length of the response
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_UnlockLoader(
  const char* pKeyName,
  const char* pIMEIStr,
  const unsigned char* pChallenge,
  unsigned int challengeLen,
  unsigned char* pResponse,
  unsigned int* pResponseLength,
  unsigned int handleIndex);

/**
 * Returns the data from first step in a P22/P96 sequence in \p pStepOneData. In contrast with SGN_GetStepOneData_v2() this function only
 * accepts keys that CS are allowed to use.
 * @param pKeyName [in] The name of a valid P22/P96 key.
 * @param pStepOneData [out] Pre-allocated buffer that will contain the step one data.
 * If the buffer is too small you will get a #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, and \p pStepOneLength
 * will be set to the expected buffer size.
 * @param pStepOneLength [in/out] As input parameter, this is the size of the buffer.
 * A buffer size of at least 1024 bytes is recommended. As output parameter, this is the actual
 * length of the step one data returned.
 * @param pIMEIStr [in] IMEI (14 digits + null termination).
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_CSGetStepOneData_v2(
  const char* pKeyName,
  unsigned char* pStepOneData,
  unsigned int* pStepOneLength,
  const char* pIMEIStr,
  unsigned int handleIndex);

/**
 * Returns the data from first step in a P22/P96 sequence using transaction ID (TrID) for verification.
 * @param pKeyName [in] The name of a valid P22/P96 key.
 * @param pStepOneData [out] Pre-allocated buffer that will contain the step one data.
 * If the buffer is too small you will get a #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, and \p pStepOneLength
 * will be set to the expected buffer size.
 * @param pStepOneLength [in/out] As input parameter, this is the size of the buffer.
 * A buffer size of at least 1024 bytes is recommended. As output parameter, this is the actual
 * length of the step one data returned.
 * @param pIMEIStr [in] IMEI (14 digits + null termination).
 * @param pTrID [in] Null terminated transaction ID on format TAG1="VALUE";TAG2="VALUE"
 * @param pTrIDSignature [in] TrID signature calculated over pTrID (signing certificate name should be part of pTrID).
 * @param trIDSignatureLength [in] Length of TrID signature in bytes.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetStepOneDataWithTrID(
  const char* pKeyName,
  unsigned char* pStepOneData,
  unsigned int* pStepOneLength,
  const char* pIMEIStr,
  const char* pTrID,
  const unsigned char* pTrIDSignature,
  unsigned int trIDSignatureLength,
  unsigned int handleIndex);

/**
 * Authorizes a user to use some specific loader functionality on a specific device using the S1 SAKE protocol.
 * @param pHello [in] Hello message from loader.
 * @param helloLength [in] Length of hello message in bytes.
 * @param pResponse [out] A buffer where the response message will be put.
 * @param pResponseLength [in/out] As input parameter, this is the size of the buffer.
 * As output parameter, this is the actual length of the response message returned.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_SakeAuthenticate(
  const unsigned char* pHello,
  unsigned int helloLength,
  unsigned char* pResponse,
  unsigned int* pResponseLength,
  unsigned int handleIndex);

/**
 * Authorizes a user towards a loader using the S1 SAKE protocol and transaction ID (TrID) for verification.
 * @param pHello [in] Hello message from loader.
 * @param helloLength [in] Length of hello message in bytes.
 * @param pResponse [out] A buffer where the response message will be put.
 * @param pResponseLength [in/out] As input parameter, this is the size of the buffer.
 * As output parameter, this is the actual length of the response message returned.
 * @param pTrID [in] Null terminated transaction ID on format TAG1="VALUE";TAG2="VALUE"
 * @param pTrIDSignature [in] TrID signature calculated over pTrID (signing certificate name should be part of pTrID).
 * @param trIDSignatureLength [in] Length of TrID signature in bytes.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_SakeAuthenticateWithTrID(
  const unsigned char* pHello,
  unsigned int helloLength,
  unsigned char* pResponse,
  unsigned int* pResponseLength,
  const char* pTrID,
  const unsigned char* pTrIDSignature,
  unsigned int trIDSignatureLength,
  unsigned int handleIndex);

/** Returns a DRM certificate of type \p certType for production mode \p prodMode on the
 * format specified by the DRM generation \p drmGeneration in \p pData.
 * Please note that all certificate types are not available for all DRM generations.
 * @param prodMode [in] Production Mode. Possible values are:
 * - #_TEST
 * - #_LIVE
 * @param drmGeneration [in] DRM certificate generation. If an invalid value is specified, a #SECS_ERROR_UNSUPPORTED_DRM_GENERATION error will be returned.
 * Possible values are:
 * - #SGN_DRM_GEN0
 * - #SGN_DRM_GEN1
 * - #SGN_DRM_GEN4
 * @param certType [in] Certificate type. The table below shows the possible certificate types
 * and the DRM generations for which they are supported.
 * <br><br>
 * <TABLE>
 * <TR><TD><b>Certificate type</b><TD><b>#SGN_DRM_GEN0</b><TD><b>#SGN_DRM_GEN1</b><TD><b>#SGN_DRM_GEN4</b>
 * <TR><TD>#SGN_CERTIFICATE_PROD_CA_VER1  <TD>x<TD>-<TD>-
 * <TR><TD>#SGN_CERTIFICATE_PROD_CA_VER2  <TD>x<TD>-<TD>-
 * <TR><TD>#SGN_CERTIFICATE_CMLA_BULK     <TD>x<TD>-<TD>-
 * <TR><TD>#SGN_CERTIFICATE_CMLA          <TD>x<TD>x<TD>-
 * <TR><TD>#SGN_CERTIFICATE_SEMCDRM       <TD>x<TD>x<TD>-
 * <TR><TD>#SGN_CERTIFICATE_VIACCESS      <TD>x<TD>x<TD>-
 * <TR><TD>#SGN_CERTIFICATE_MICROSOFT     <TD>-<TD>x<TD>-
 * <TR><TD>#SGN_CERTIFICATE_MARLIN        <TD>-<TD>-<TD>x
 * <TR><TD>#SGN_CERTIFICATE_HDCP_AV8100   <TD>-<TD>-<TD>x
 * <TR><TD>#SGN_CERTIFICATE_CDMA_AKEY     <TD>-<TD>-<TD>x
 * <TR><TD>#SGN_CERTIFICATE_PLAYREADY     <TD>-<TD>-<TD>x
 * <TR><TD>#SGN_CERTIFICATE_MARLIN_IMPORT <TD>-<TD>-<TD>x
 * <TR><TD>#SGN_CERTIFICATE_DTCP_IP       <TD>-<TD>-<TD>x
 * <TR><TD>#SGN_CERTIFICATE_WIDEVINE      <TD>-<TD>-<TD>x
 * <TR><TD>#SGN_CERTIFICATE_MIRRORLINK    <TD>-<TD>-<TD>x
 * <TR><TD>#SGN_CERTIFICATE_HDCP2         <TD>-<TD>-<TD>x
 * <TR><TD>#SGN_CERTIFICATE_CKB           <TD>-<TD>-<TD>x
 * </TABLE>
 * <br>
 * @param pIMEIStr [in] IMEI number (14 digits + null termination).
 * @param pData [out] Pre-allocated buffer that will contain the resulting DRM certificate.
 * If the buffer is too small you will get a #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, and \p pDataLength
 * will be set to the expected buffer size.
 * @param pDataLength [in/out] As input parameter this is the length of the buffer.
 * As output parameter this is the actual length of the DRM certificate returned.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetDrmCertificate(
  T_SGN_ProdModeType prodMode,
  int drmGeneration,
  int certType,
  const char* pIMEIStr,
  unsigned char* pData,
  unsigned int* pDataLength,
  unsigned int handleIndex);

/** Returns a DRM certificate the same way as SGN_GetDrmCertificate(), with the addition of a certificate ID string.
 * Note that not all DRM certificates have certificate IDs. Currently only CMLA, Marlin, HDCP and Widevine have IDs.
 * The purpose of the certificate ID is to store it (for instance in HPDD) for later retrieval and checks.
 * For CDMA A-KEY, the ID is actually the key in encrypted form. It should be sent to HPDD for distribution to operators.
 * @param prodMode [in] Production Mode. Possible values are:
 * - #_TEST
 * - #_LIVE
 * @param drmGeneration [in] DRM certificate generation. If an invalid value is specified, a #SECS_ERROR_UNSUPPORTED_DRM_GENERATION error will be returned.
 * Possible values are:
 * - #SGN_DRM_GEN0
 * - #SGN_DRM_GEN1
 * - #SGN_DRM_GEN4
 * @param certType [in] Certificate type. See SGN_GetDrmCertificate() for valid types and generations.
 * @param pIMEIStr [in] IMEI number (14 digits + null termination).
 * @param pData [out] Pre-allocated buffer that will contain the resulting DRM certificate.
 * If the buffer is too small you will get a #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, and \p pDataLength
 * will be set to the expected buffer size.
 * @param pDataLength [in/out] As input parameter this is the length of the buffer.
 * As output parameter this is the actual length of the DRM certificate returned.
 * @param pCertId [out] Pre-allocated buffer that will contain the certId.
 * If the buffer is too small you will get a #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, the certIdLength will <b>not</b> indicate the needed length since it is input parameter only.
 * The maximum lengths of the different certIds are semi-static and known. A buffer length of at least 578 bytes is recommended.
 * - CMLA: A hexstring of about 42 bytes in length. (example: 0740020000031B3799781D2B1450D348230A698F75)
 * - Marlin: A URL like urn with a hexstring identifier at the end (example: urn:marlin:organization:seacert:semc:clientnemo:011b8b73)
 * - HDCP: A hexstring 16 bytes in length. The Key Selection Vector (KSV) is used as ID. (example: 8b3ca4f934)
 * - AKEY: A encryption key name followed by a hexstring (divided by a colon) (example: SECSHPDD_1:feab1289...2376dc)
 * Note that CMLA uses uppercase hex but all other uses lowercase hex for legacy reasons.
 * @param certIdLength [in] Length of certId buffer.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetDrmCertificateAndId(
  T_SGN_ProdModeType prodMode,
  int drmGeneration,
  int certType,
  const char* pIMEIStr,
  unsigned char* pData,
  unsigned int* pDataLength,
  char* pCertId,
  unsigned int certIdLength,
  unsigned int handleIndex);

/** Returns a DRM certificate the same way as SGN_GetDrmCertificateAndId() (with the addition of a certificate ID string).
 * Note: Will use a combined device key (DK) compatible with HwConfig v5.
 * @param prodMode [in] Production Mode. Possible values are:
 * - #_TEST
 * - #_LIVE
 * @param drmGeneration [in] DRM certificate generation. If an invalid value is specified, a #SECS_ERROR_UNSUPPORTED_DRM_GENERATION error will be returned.
 * Possible values are:
 * - #SGN_DRM_GEN0
 * - #SGN_DRM_GEN1
 * - #SGN_DRM_GEN4
 * @param certType [in] Certificate type. See SGN_GetDrmCertificate() for valid types and generations.
 * @param pIMEIStr [in] IMEI number (14 digits + null termination).
 * @param pSmkName [in] The requested Super Master Key (SMK) as a null terminated
 * string (case sensitive). If set to NULL the default SMK will be used.
 * @param pData [out] Pre-allocated buffer that will contain the resulting DRM certificate.
 * If the buffer is too small you will get a #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, and \p pDataLength
 * will be set to the expected buffer size.
 * @param pDataLength [in/out] As input parameter this is the length of the buffer.
 * As output parameter this is the actual length of the DRM certificate returned.
 * @param pCertId [out] Pre-allocated buffer that will contain the certId.
 * If the buffer is too small you will get a #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, the certIdLength will <b>not</b> indicate the needed length since it is input parameter only.
 * The maximum lengths of the different certIds are semi-static and known. A buffer length of at least 578 bytes is recommended.
 * - CMLA: A hexstring of about 42 bytes in length. (example: 0740020000031B3799781D2B1450D348230A698F75)
 * - Marlin: A URL like urn with a hexstring identifier at the end (example: urn:marlin:organization:seacert:semc:clientnemo:011b8b73)
 * - HDCP: A hexstring 16 bytes in length. The Key Selection Vector (KSV) is used as ID. (example: 8b3ca4f934)
 * - AKEY: A encryption key name followed by a hexstring (divided by a colon) (example: SECSHPDD_1:feab1289...2376dc)
 * Note that CMLA uses uppercase hex but all other uses lowercase hex for legacy reasons.
 * @param certIdLength [in] Length of certId buffer.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetDrmCertificateAndIdWithSmkCombDK(
  T_SGN_ProdModeType prodMode,
  int drmGeneration,
  int certType,
  const char* pIMEIStr,
  const char* pSmkName,
  unsigned char* pData,
  unsigned int* pDataLength,
  char* pCertId,
  unsigned int certIdLength,
  unsigned int handleIndex);

/** Returns a DRM certificate the same way as SGN_GetDrmCertificateAndIdWithSmkCombDK()
 * with the addition of all private keys in plain text for test DRM certificates. For
 * live DRM certificates no plain text keys will be returned.
 * Note: Usage is for test purposes in R&D org.
 * @param prodMode [in] Production Mode. Possible values are:
 * - #_TEST
 * - #_LIVE
 * @param drmGeneration [in] DRM certificate generation. If an invalid value is specified, a #SECS_ERROR_UNSUPPORTED_DRM_GENERATION error will be returned.
 * Possible values are:
 * - #SGN_DRM_GEN0
 * - #SGN_DRM_GEN1
 * - #SGN_DRM_GEN4
 * @param certType [in] Certificate type. See SGN_GetDrmCertificate() for valid types and generations.
 * @param purpose [in] Purpose for certificate blob, the following purposes are defined:
 * - 0: Normal, use any available certificate.
 * - 1: Integration, use a specific certificate. All subsequent calls will receive the same data, encrypted for specific IMEI.
 * - 2..: Future use.
 * @param pIMEIStr [in] IMEI number (14 digits + null termination).
 * @param pSmkName [in] The requested Super Master Key (SMK) as a null terminated
 * string (case sensitive). If set to NULL the default SMK will be used.
 * @param pData [out] Pre-allocated buffer that will contain the resulting DRM certificate.
 * If the buffer is too small you will get a #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, and \p pDataLength
 * will be set to the expected buffer size.
 * @param pDataLength [in/out] As input parameter this is the length of the buffer.
 * As output parameter this is the actual length of the DRM certificate returned.
 * @param pCertId [out] Pre-allocated buffer that will contain the certId.
 * If the buffer is too small you will get a #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, the certIdLength will <b>not</b> indicate the needed
 * length since it is input parameter only.
 * The maximum lengths of the different certIds are semi-static and known. A buffer length of at least 578 bytes is recommended.
 * - CMLA: A hexstring of about 42 bytes in length. (example: 0740020000031B3799781D2B1450D348230A698F75)
 * - Marlin: A URL like urn with a hexstring identifier at the end (example: urn:marlin:organization:seacert:semc:clientnemo:011b8b73)
 * - HDCP: A hexstring 16 bytes in length. The Key Selection Vector (KSV) is used as ID. (example: 8b3ca4f934)
 * - AKEY: A encryption key name followed by a hexstring (divided by a colon) (example: SECSHPDD_1:feab1289...2376dc)
 * Note that CMLA uses uppercase hex but all other uses lowercase hex for legacy reasons.
 * @param certIdLength [in] Length of certId buffer.
 * @param pPlainKeys [out] Pre-allocated buffer that will contain the private keys in plain text (ASCII). This data will be suitable to
 * write to a file as is. Each key will be on a separate line together with key index and length. The key data will be in ASCII hex format.
 * If the buffer is too small you will get a #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, the plainKeysLength will <b>not</b> indicate the needed
 * length since it is input parameter only.
 * The maximum length depends of the number and size of the private keys. Currently Marlin is largest with 12K data.
 * @param plainKeysLength [in] Length of plainKeys buffer.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetDrmCertificateAndIdPlainKeysWithSmkCombDK(
  T_SGN_ProdModeType prodMode,
  int drmGeneration,
  int certType,
  unsigned int purpose,
  const char* pIMEIStr,
  const char* pSmkName,
  unsigned char* pData,
  unsigned int* pDataLength,
  char* pCertId,
  unsigned int certIdLength,
  char* pPlainKeys,
  unsigned int plainKeysLength,
  unsigned int handleIndex);

/** Returns a License Key and its ID string.
 * @param prodMode [in] Production Mode. Possible values are:
 * - #_TEST
 * - #_LIVE
 * @param licType [in] License type.
 * The values currently supported are:
 * - #SGN_LICENSE_PVK
 * - #SGN_LICENSE_OVK
 * @param pIMEIStr [in] IMEI number (14 digits + null termination).
 * @param pVersionResponse [in] Version response string from device. The S1_ROOT tag is used to derive the proper signing cert to create a SIN image.
 * @param pData [out] Pre-allocated buffer that will contain the resulting license key.
 * If the buffer is too small you will get a #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, and \p pDataLength
 * will be set to the expected buffer size.
 * @param pDataLength [in/out] As input parameter this is the length of the buffer.
 * As output parameter this is the actual length of the license key returned.
 * @param pId [out] Pre-allocated buffer that will contain the license ID.
 * If the buffer is too small you will get a #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, the idLength will <b>not</b> indicate the needed length since it is input parameter only.
 * The maximum lengths of the license IDs for different cert types are semi-static and known. A buffer length of at least 578 bytes is recommended.
 * - PVK: A file name containing batch id and PVK hash which is normally 78 bytes in length (example: SONY_0807_2726C83992BB7FD0A722C2C29D2E900109168E71EE5AB2CEA500D4DAF453955F.bin)
 * - OVK: A 32 byte binary ID in hex followed by a 20 byte hash in hex, separated by a colon. Total length 64 + 1 + 40 = 105 bytes.
 * @param idLength [in] Length of id buffer.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetLicenseKey(
  T_SGN_ProdModeType prodMode,
  int licType,
  const char* pIMEIStr,
  const char* pVersionResponse,
  unsigned char* pData,
  unsigned int* pDataLength,
  char* pId,
  unsigned int idLength,
  unsigned int handleIndex);

/** Returns a License Key and its ID string using transaction ID (TrID) for verification. See SGN_GetLicenseKey() for details.
 * @param prodMode [in] Production Mode. Possible values are:
 * - #_TEST
 * - #_LIVE
 * @param licType [in] License type.
 * The values currently supported are:
 * - #SGN_LICENSE_PVK
 * - #SGN_LICENSE_OVK
 * @param pIMEIStr [in] IMEI number (14 digits + null termination).
 * @param pVersionResponse [in] Version response string from device. The S1_ROOT tag is used to derive the proper signing cert to create a SIN image.
 * @param pData [out] Pre-allocated buffer that will contain the resulting license key.
 * If the buffer is too small you will get a #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, and \p pDataLength
 * will be set to the expected buffer size.
 * @param pDataLength [in/out] As input parameter this is the length of the buffer.
 * As output parameter this is the actual length of the license key returned.
 * @param pId [out] Pre-allocated buffer that will contain the license ID.
 * If the buffer is too small you will get a #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, the idLength will <b>not</b> indicate the needed length since it is input parameter only.
 * The maximum lengths of the license IDs for different cert types are semi-static and known. A buffer length of at least 578 bytes is recommended.
 * - PVK: A file name containing batch id and PVK hash which is normally 78 bytes in length (example: SONY_0807_2726C83992BB7FD0A722C2C29D2E900109168E71EE5AB2CEA500D4DAF453955F.bin)
 * - OVK: A 32 byte binary ID in hex followed by a 20 byte hash in hex, separated by a colon. Total length 64 + 1 + 40 = 105 bytes.
 * @param idLength [in] Length of id buffer.
 * @param pTrID [in] Null terminated transaction ID on format TAG1="VALUE";TAG2="VALUE"
 * @param pTrIDSignature [in] TrID signature calculated over pTrID (signing certificate name should be part of pTrID).
 * @param trIDSignatureLength [in] Length of TrID signature in bytes.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetLicenseKeyWithTrID(
  T_SGN_ProdModeType prodMode,
  int licType,
  const char* pIMEIStr,
  const char* pVersionResponse,
  unsigned char* pData,
  unsigned int* pDataLength,
  char* pId,
  unsigned int idLength,
  const char* pTrID,
  const unsigned char* pTrIDSignature,
  unsigned int trIDSignatureLength,
  unsigned int handleIndex);

/**
 * Generates a RCK (Rooting Control Key) based on the SMK \p pSmkName for the IMEI number
 * \p pIMEIStr and returns it in \p pRCKBuf.
 * @param pIMEIStr [in] IMEI number (14 digits + null termination).
 * @param pSmkName [in] The requested Super Master Key (SMK) as a null terminated
 * string (case sensitive). If set to NULL, the default RCK SMK will be used.
 * @param pRCKBuf [out] Pre-allocated buffer that will contain the device key.
 * If the buffer is too small you will get a #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, and \p pRCKLength
 * will be set to the expected buffer size.
 * @param pRCKBufLen [in/out] As input parameter this is the length of the buffer. A buffer length
 * of at least 16 bytes is recommended. As output parameter this is the actual length of the device key returned.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GenerateRootControlKey(
  const char* pIMEIStr,
  const char* pSmkName,
  unsigned char* pRCKBuf,
  unsigned int* pRCKBufLen,
  unsigned int handleIndex);

/**
 * Encrypts a buffer \p pRsaBuf using RSA and the key from a certain certificate \p pCertName.
 * @param pRsaBuf [in/out] Buffer to be encrypted
 * @param RsaLength [in] Length of buffer, must be 128/256
 * @param pCertName [in] Name of certificate
 * @param type [in] #SGN_RSASIGN_LOADER, #SGN_RSASIGN_SEMCBOOT or #SGN_RSASIGN_OTHER
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_RSASign(
  char* pRsaBuf,
  int RsaLength,
  const char* pCertName,
  int type,
  unsigned int handleIndex);

/**
 * Approves RSA Signing of a buffer when using a signing key which is configured to need special approval.
 * Use SGN_RSASign() for the actual signing. The RSA buf used in the approval should be identical to what
 * is later used in SGN_RSASign().
 * @param pInfo [in] Meta data for signing. Could be filename of input data or other revision information.
 * Used for tracking and debugging. If too long it will be silently truncated (currently at 255 chars). The
 * call will fail if very long (~ 2kB).
 * @param pRsaBuf [in/out] Buffer to be approved
 * @param RsaLen [in] Length of buffer, must be 128/256
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_ApproveRSASign(
    const char* pInfo,
    char* pRsaBuf,
    int RsaLen,
    unsigned int handleIndex);

/**
 * Returns a signed HW configuration for S1.
 * @param hwConfRev [in] Hw configuration revision string, e.g. HWC_Rhine_Dev_001.
 * @param nbrOfDeviceIds [in] Number of device IDs, e.g. 2.
 * @param deviceIdLen [in] An array of ints containing the length of each individual device id.
 * @param deviceId [in] All device id as binary data. Binary data is a byte array with byte order as specified by data
 * from boot/loader. Number of bytes must equal the sum of all device id lengths.
 * @param pCertName [in] A string with the name of the certificate used for RSA signing. E.g. S1_HWConf_Test_0d89_0001
 * @param pIMEIStr [in] An ASCII string with the IMEI number (14 digits + null termination)
 * @param securityFlags [in] Zero means security will be enabled in the hw config, use one for security off.
 * @param resBuf [out] A buffer where the result will be put. If the buffer is too small you will get a
 * #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, and \p resLen will be set to the expected buffer size.
 * @param resLen [in/out] Size of resBuf. This will be set to the size of the result before returning.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetSignedHwConfig(
  const char* hwConfRev,
  int nbrOfDeviceIds,
  const unsigned int* deviceIdLen,
  const char* deviceId,
  const char* pCertName,
  const char* pIMEIStr,
  unsigned int securityFlags,
  char* resBuf,
  unsigned int* resLen,
  unsigned int handleIndex);

/**
 * Returns a signed HW configuration for S1. This function differs from SGN_GetSignedHwConfig() by having an SMK name
 * as input (see SGN_GetDrmCertificateAndIdWithSmkCombDK() ). Also, instead of an IMEI as input a list of phone IDs is
 * used. The first number in the list is used for binding S1 security, that is, the same function that the old IMEI had.
 * If this function is called with no SMK name (NULL) and a list containing only one IMEI, the result is the same as from
 * SGN_GetSignedHwConfig().
 * @param hwConfRev [in] Hw configuration revision string, e.g. HWC_Rhine_Dev_001.
 * @param nbrOfDeviceIds [in] Number of device IDs, e.g. 2.
 * @param deviceIdLen [in] An array of ints containing the length of each individual device id.
 * @param deviceId [in] All device id as binary data. Binary data is a byte array with byte order as specified by data
 * from boot/loader. Number of bytes must equal the sum of all device id lengths.
 * @param pCertName [in] A string with the name of the certificate used for RSA signing, e.g. S1_HWConf_Test_0d89_0001
 * @param nbrOfPhoneIds [in] Number of phone IDs, e.g. 1.
 * @param phoneIdType [in] An array of types for each phone ID. IMEI(0), MEID(1) ...
 * @param phoneId [in] All phone id data as null terminated strings concatenated together (separated by the null termination).
 * @param pSmkName [in] The requested Super Master Key (SMK) as a null terminated string (case sensitive).
 * If set to NULL the default SMK will be used.
 * @param securityFlags [in] Zero means security will be enabled in the hw config, use one for security off.
 * @param resBuf [out] A buffer where the result will be put. If the buffer is too small you will get a
 * #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, and \p resLen will be set to the expected buffer size.
 * @param resLen [in/out] Size of resBuf. This will be set to the size of the result before returning.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetSignedHwConfigWithIdList(
  const char* hwConfRev,
  int nbrOfDeviceIds,
  const unsigned int* deviceIdLen,
  const char* deviceId,
  const char* pCertName,
  int nbrOfPhoneIds,
  const unsigned int* phoneIdType,
  const char* phoneId,
  const char* pSmkName,
  unsigned int securityFlags,
  char* resBuf,
  unsigned int* resLen,
  unsigned int handleIndex);

/**
 * Takes an existing HW config, sets the security flag and resigns it with the certificate that has the higest AID.
 * @param hwConf [in] Old Hw configuration data
 * @param hwConfLen [in] Length of HW configuration data
 * @param versionResponse [in] A version response string.
 * @param securityFlags [in] Zero means security will be enabled in the hw config, use one for security off.
 * @param resBuf [out] A buffer where the result will be put. If the buffer is too small you will get a
 * #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, and \p resLen will be set to the expected buffer size.
 * @param resLen [in/out] Size of resBuf. This will be set to the size of the result before returning.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_SetSecurityInHwConfig(
  const char* hwConf,
  unsigned int hwConfLen,
  const char* versionResponse,
  unsigned int securityFlags,
  char* resBuf,
  unsigned int* resLen,
  unsigned int handleIndex);

/**
 * Takes an existing HW config, sets the SW AID and resigns it with the certificate that has the highest AID.
 * @param hwConf [in] Old Hw configuration data
 * @param hwConfLen [in] Length of HW configuration data
 * @param versionResponse [in] A version response string.
 * @param swAid [in] The SW AID to change to.
 * @param resBuf [out] A buffer where the result will be put. If the buffer is too small you will get a
 * #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, and \p resLen will be set to the expected buffer size.
 * @param resLen [in/out] Size of resBuf. This will be set to the size of the result before returning.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_SetSwAidInHwConfig(
  const char* hwConf,
  unsigned int hwConfLen,
  const char* versionResponse,
  unsigned int swAid,
  char* resBuf,
  unsigned int* resLen,
  unsigned int handleIndex);

/**
 * Takes an existing HW config, sets the SW AID and resigns it with the certificate that has the highest AID.
 * Transaction ID (TrID) is used for verification.
 * @param hwConf [in] Old Hw configuration data
 * @param hwConfLen [in] Length of HW configuration data
 * @param versionResponse [in] A version response string.
 * @param swAid [in] The SW AID to change to.
 * @param resBuf [out] A buffer where the result will be put. If the buffer is too small you will get a
 * #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, and \p resLen will be set to the expected buffer size.
 * @param resLen [in/out] Size of resBuf. This will be set to the size of the result before returning.
 * @param pTrID [in] Null terminated transaction ID on format TAG1="VALUE";TAG2="VALUE"
 * @param pTrIDSignature [in] TrID signature calculated over pTrID (signing certificate name should be part of pTrID).
 * @param trIDSignatureLength [in] Length of TrID signature in bytes.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_SetSwAidInHwConfigWithTrID(
  const char* hwConf,
  unsigned int hwConfLen,
  const char* versionResponse,
  unsigned int swAid,
  char* resBuf,
  unsigned int* resLen,
  const char* pTrID,
  const unsigned char* pTrIDSignature,
  unsigned int trIDSignatureLength,
  unsigned int handleIndex);

/**
 * Returns a signed Alt Root data blob (also called Super Secure).
 * @param pRevision [in] Alt Root data revision string, e.g. AR_Cust7915_001.
 * @param pIMEIStr [in] An ASCII string with the IMEI number (14 digits + null termination)
 * @param pResBuf [out] A buffer where the result will be put. If the buffer is too small you will get a
 * #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, and \p pResLen will be set to the expected buffer size.
 * @param pResLen [in/out] Size of pResBuf. This will be set to the size of the result before returning.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetSignedAltRoot(
    const char* pRevision,
    const char* pIMEIStr,
    unsigned char* pResBuf,
    unsigned int* pResLen,
    unsigned int handleIndex);

/**
 * Returns a signed Alt Root from payload data (also called Super Secure).
 * @param pIMEIStr [in] An ASCII string with the IMEI number (14 digits + null termination)
 * @param pCertName Name of certificate to be used.
 * @param altType Type of certificate.
 * @param pDataBuf Payload data buffer.
 * @param dataLen Size of Payload data buffer.
 * @param pResBuf [out] A buffer where the result will be put. If the buffer is too small you will get a
 * @param pResLen [in/out] Size of pResBuf. This will be set to the size of the result before returning.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetSignedAltRootWithPayload(
    const char* pIMEIStr,
    const char* pCertName,
    unsigned int altType,
    const char* pDataBuf,
    unsigned int dataLen,
    unsigned char* pResBuf,
    unsigned int* pResLen,
    unsigned int handleIndex);

/**
 * Returns a Device Keystore in a signed CMS structure.
 * @param pKsRev [in] Device Keystore revision string, e.g. DKS_Yoshino_Dev_001.
 * @param nbrOfDeviceIds [in] Number of device IDs, e.g. 2.
 * @param pDeviceIdLen [in] An array of ints containing the length of each individual device id.
 * @param pDeviceId [in] All device id as binary data. Binary data is a byte array with byte order as specified by data
 * from boot/loader. Number of bytes must equal the sum of all device id lengths.
 * @param counter [in] Rollback counter that should be set as CMS attribute.
 * @param pCertName [in] A string with the name of the certificate used for RSA signing of CMS.
 * @param pResBuf [out] A buffer where the result will be put. If the buffer is too small you will get a
 * #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, and \p resLen will be set to the expected buffer size.
 * @param pResLen [in/out] Size of resBuf. This will be set to the size of the result before returning.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetSignedDeviceKeystore(
    const char* pKsRev,
    int nbrOfDeviceIds,
    const unsigned int* pDeviceIdLen,
    const unsigned char* pDeviceId,
    unsigned int counter,
    const char* pCertName,
    unsigned char* pResBuf,
    unsigned int* pResLen,
    unsigned int handleIndex);

/**
 * Returns a security property (sec prop) corresponding to specified revision and IMEI. IMEI controls whether
 * a LIVE or R&D sec prop is returned. Part of sec prop may be dynamically generated (for example DRM device key, DK)
 * according to the template stored on the server.
 * @param pSecPropBuf [out] This parameter will contain the resulting sec prop data on successful return (allocated/deleted by the caller).
 * If the buffer is too small you will get a #SGN_SGNTOOL_EXCEEDS_BUFFER error, and \p pSecPropLength
 * will be set to the expected buffer size.
 * @param pSecPropLength [in/out] This parameter will contain the length of the resulting data.
 * As input parameter, this is the maximum size allocated for the data buffer.
 * @param pRevision [in] The requested sec prop revision as a nullterminated string (case sensitive), e.g. SP_APQ8064_001.
 * @param pIMEIStr [in] The IMEI number, used to determine R&D or LIVE data where applicable (again, for DRM device key).
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetSecurityProperties(
  unsigned char* pSecPropBuf,
  unsigned int* pSecPropLength,
  const char* pRevision,
  const char* pIMEIStr,
  unsigned int handleIndex);

/**
 * Alias for SGN_GetSecurityPropertiesWithSmk
 */
SECS_API unsigned int SGN_GetSecurityProperties_v2(
  unsigned char* pSecPropBuf,
  unsigned int* pSecPropLength,
  T_SGN_ProdModeType prodMode,
  const char* pRevision,
  const char* pIMEIStr,
  const char* pSmkName,
  unsigned int handleIndex);

/**
 * Returns a security property (sec prop) corresponding to specified revision, production mode and IMEI.
 * Production mode (prodMode) controls whether a LIVE or R&D sec prop is returned. Part of sec prop may
 * be dynamically generated (for example DRM device key, DK) according to the template stored on the server.
 * @param pSecPropBuf [out] This parameter will contain the resulting sec prop data on successful return (allocated/deleted by the caller).
 * If the buffer is too small you will get a #SGN_SGNTOOL_EXCEEDS_BUFFER error, and \p pSecPropLength
 * will be set to the expected buffer size.
 * @param pSecPropLength [in/out] This parameter will contain the length of the resulting data.
 * As input parameter, this is the maximum size allocated for the data buffer.
 * @param prodMode [in] Production Mode
 * @param pRevision [in] The requested sec prop revision as a nullterminated string (case sensitive), e.g. SP_APQ8064_001.
 * @param pIMEIStr [in] The IMEI number, used to calculate any device key.
 * @param pSmkName [in] The requested Super Master Key (SMK) as a null terminated
 * string (case sensitive). If set to NULL the default SMK will be used (as used by SGN_GetSecurityProperties() ).
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetSecurityPropertiesWithSmk(
  unsigned char* pSecPropBuf,
  unsigned int* pSecPropLength,
  T_SGN_ProdModeType prodMode,
  const char* pRevision,
  const char* pIMEIStr,
  const char* pSmkName,
  unsigned int handleIndex);

/**
 * If an error has occurred this function returns the extended error message and error code in \p pMessage and
 * \p errorCode. The error code and message may come from the communication component used in Windows or Linux.
 * If no error that has an extended error message has occurred an empty string and 0 (ERROR_SUCCESS) will be returned.
 * @param pMessage [out] Result buffer that will contain the extended error message.
 * @param messageLimit [in] The size of the result buffer. A buffer size of at least 2 kB is recommended.
 * If there is insufficient space in  the result buffer, the extended error message will be truncated.
 * @param errorCode [out] The error code from Windows or libcurl in Linux.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_ReadExtendedErrorMessage(
  char* pMessage,
  int messageLimit,
  unsigned int* errorCode,
  unsigned int handleIndex);

/**
 * Returns Paf for the IMEI number \p pIMEIStr.
 * @param pPaf [out] This parameter will contain 0 if \p pIMEIStr is a test IMEI number,
 * otherwise it will contain 1. It takes pre-commercial and special test TACs into consideration (from server rev R10A001).
 * @param pIMEIStr [in] IMEI str (14 digits + null termination)
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetPaf(
  unsigned char* pPaf,
  const char* pIMEIStr,
  unsigned int handleIndex);

/**
 * Sends echo to the server with handle index \p handleIndex and returns SECS_SUCCESS
 * if a reply is received, otherwise an error code is returned.
 * @param upgradeMode [in] If set to 1 (true) execution will only be allowed on server in upgrade mode (also called, server in TEST MODE).
 * If set to 0 (false) execution will only be allowed on server NOT in upgrade mode (normal production mode).
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_CheckServer_v2(
  bool upgradeMode,
  unsigned int handleIndex);

/**
 * Sets the connection timeout to \p timeout for the opened handle \p handleIndex.
 * If a timeout is not set by calling this function (or set to 0), the OS default timeout is used (curl for Linux).
 * @param timeout [in] Timeout in seconds.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_SetConnectionTimeout(
  unsigned int timeout,
  unsigned int handleIndex);

/**
 * Sets the connection retry count to \p retries for the opened handle \p handleIndex.
 * The default retry count is 5. A retry count is mostly useful when using https authentication in an internet
 * environment (where a lot of things may go wrong).
 * @param retries [in] Retry count. A retry count of 0 means only one attempt will be made (no retries).
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_SetConnectionRetries(
  unsigned int retries,
  unsigned int handleIndex);

/**
 * Returns the version numbers for the dispatcher, crypto, keystore, and SECS in \p pVersions.
 * @param pVersions [out] Pre-allocated buffer that will contain the list of versions in a "," separated string NULL terminated on successful return.
 * Since there is no buffersize check, it is recommended to allocate at least 2048 bytes for this buffer.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetVersions(
  char* pVersions,
  unsigned int handleIndex);

/**
 * Returns the version numbers for the dispatcher, crypto, keystore, and SECS in \p pVersionsBuffer.
 * @param pVersionsBuffer [out] Pre-allocated buffer that will contain the list of versions in a "," separated NULL
 * terminated string on successful return.
 * @param versionsBufferLength [in] Size of allocated buffer.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetVersions_v2(
  char* pVersionsBuffer,
  unsigned int versionsBufferLength,
  unsigned int handleIndex);

/**
 * Returns the version of the SECS client in \p pVersionBuffer.
 * @param pVersionBuffer [out] Pre-allocated buffer that will contain the SECS version in a NULL
 * terminated string on successful return. A size of 128 bytes can be considered safe. If the buffer
 * is too small you will get a #SECS_ERROR_SGN_BUFFERLENGTH error and a truncated version string will
 * be put in \p pVersionBuffer.
 * @param versionBufferLength [in] Size of allocated buffer.
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetClientVersion(
  char* pVersionBuffer,
  unsigned int versionBufferLength);

/**
 * Returns \p noOfBytes random bytes in the result buffer \p pRandomBytes.
 * @param noOfBytes [in] Number of bytes (must a value between 1 and 2048).
 * @param pRandomBytes [out] Pre-allocated buffer with size \p noOfBytes.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetRandomBytes(
  unsigned int noOfBytes,
  unsigned char* pRandomBytes,
  unsigned int handleIndex);

/**
 * Returns certificate status of the server in \p pStatusBuffer.
 * @param pStatusBuffer [out] Pre-allocated buffer that will contain the server status in XML format.
 * A buffer length > 4k is recommended. If the buffer is too small you will get a #SGN_SGNTOOL_EXCEEDS_BUFFER error,
 * and \p pStatusBufferLen will be set to the expected buffer size.
 * @param pStatusBufferLen [in/out] As input parameter this shall contain the length of the pre-allocated buffer.<br>
 * As output parameter this will contain the actual length of the server status returned.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetStatus(
  char* pStatusBuffer,
  unsigned int* pStatusBufferLen,
  unsigned int handleIndex);

/**
 * Returns detailed certificate status of the server in \p pStatusBuffer,
 * i.e. status, certificate type, owner, and number of certificates are returned for
 * all certificate types.
 * @param pStatusBuffer [out] Pre-allocated buffer that will contain the detailed server status
 * in XML format. A buffer length > 4k is recommended. If the buffer is too small you will get a
 * #SGN_SGNTOOL_EXCEEDS_BUFFER error, and \p pStatusBufferLen
 * will be set to the expected buffer size.
 * @param pStatusBufferLen [in/out] As input parameter this shall contain the length of the pre-allocated buffer.<br>
 * As output parameter this will contain the actual length of the detailed server status returned.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetFullStatus(
  char* pStatusBuffer,
  unsigned int* pStatusBufferLen,
  unsigned int handleIndex);

/**
 * Sends the ME challenge \p pChallenge to the dongle with chip ID \p pChipID,
 * and returns the response in \p pResponse.
 * @param pChipID [in] ChipID as a array of bytes, e.g. "D0000301FFFFFF05" for ES5
 * should be an array of length 8 containing values 0xD0,0x00,0x03,0x01,0xFF,0xFF,0xFF,0x05
 * @param ChipIDLen [in] ChipID length, such as strlen(ChipID) unless you have null-bytes in the pChipID.
 * @param pChallenge [in] Challenge (16 bytes).
 * @param pResponse  [out] Response  (16 bytes).
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_DongleAuthenticate_v2(
  const unsigned char* pChipID,
  unsigned int ChipIDLen,
  const unsigned char* pChallenge,
  unsigned char* pResponse,
  unsigned int handleIndex);

/**
 * Sends the ME challenge \p pChallenge to a dongle with a hard-coded chip ID,
 * and returns the response in \p pResponse.
 * @param pChallenge [in] Challenge (16 bytes)
 * @param pResponse [out] Response  (16 bytes)
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_DongleAuthenticate(
  const unsigned char* pChallenge,
  unsigned char* pResponse,
  unsigned int handleIndex);

/**
 * Sends the challenge \p pEncryptedSignatureFromME to the dongle with chip ID \p pChipID,
 * and returns the response in \p pSignatureFromDongle.
 * @param pChipID [in] ChipID as a array of bytes, e.g. "D0000301FFFFFF05" for ES5
 * should be an array of length 8 containing values 0xD0,0x00,0x03,0x01,0xFF,0xFF,0xFF,0x05
 * @param ChipIDLen [in] ChipID length
 * @param pEncryptedSignatureFromME [in] EncryptedSignature fetched from ME >= 16 bytes
 * @param pSignatureFromDongle [out] Calculated Signature from Dongle >= 16 bytes
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_DongleSignature_v2(
  const unsigned char* pChipID,
  unsigned int ChipIDLen,
  const unsigned char* pEncryptedSignatureFromME,
  unsigned char* pSignatureFromDongle,
  unsigned int handleIndex);

/**
 * Sends the challenge \p pEncryptedSignatureFromME to a dongle with a hard-coded chip ID,
 * and returns the response in \p pSignatureFromDongle.
 * @param pEncryptedSignatureFromME [in] EncryptedSignature fetched from ME >= 16 bytes
 * @param pSignatureFromDongle [out] Calculated Signature from Dongle >= 16 bytes
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_DongleSignature(
  const unsigned char* pEncryptedSignatureFromME,
  unsigned char* pSignatureFromDongle,
  unsigned int handleIndex);

/**
 * Returns OTP content for the Chip ID \p pChipID in the result buffer \p pOtpData.
 * @param prodMode [in] Production Mode
 * @param pChipID [in] ChipID
 * @param chipIDLen [in] ChipID length
 * @param pOtpData [out] OTPContent (16*4 bytes). If the buffer is too small a
 * #SGN_SGNTOOL_EXCEEDS_BUFFER error will be returned.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetLithiumOTPRegisters(
  T_SGN_ProdModeType prodMode,
  const unsigned char* pChipID,
  unsigned int chipIDLen,
  unsigned char* pOtpData,
  unsigned int handleIndex);

/**
 * Returns the customer ID corresponding to the chip ID \p pChipID in \p pOtpData.
 * @param pChipID [in] ChipID
 * @param chipIDLen [in] ChipID length
 * @param pOtpData [out] Pre-allocated buffer that will contain the customer ID.
 * A buffer size of at least 4 bytes is recommended. If the buffer is too small a
 * #SGN_SGNTOOL_EXCEEDS_BUFFER error will be returned.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetCustomerID(
  const unsigned char* pChipID,
  unsigned int chipIDLen,
  unsigned char* pOtpData,
  unsigned int handleIndex);

/**
 * Returns a signed Remote Lock for S1 with state.
 * @param prodMode [in] Production Mode
 * @param state [in] Lock state. State _NOT_LOCKABLE is defined for backward compatibility and should not be used.
 * @param pIMEIStr [in] An ASCII string with the IMEI number (14 digits + null termination)
 * @param pVersionResponse [in] Version response string from device. The S1_ROOT tag is used to derive the proper signing cert to create a SIN image.
 * @param pXperiaId [in] Unique ID generated by MyXperia web service as a null terminated string. Must be supplied for state _LOCKED.
 * @param pResBuf [out] A buffer where the result will be put. If the buffer is too small you will get a
 * #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, and \p pResLen will be set to the expected buffer size.
 * @param pResLen [in/out] Size of pResBuf. This will be set to the size of the result before returning.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetSignedRemoteLockWithState(
  T_SGN_ProdModeType prodMode,
  T_SGN_RemoteLockState state,
  const char* pIMEIStr,
  const char* pVersionResponse,
  const char* pXperiaId,
  unsigned char* pResBuf,
  unsigned int* pResLen,
  unsigned int handleIndex);

/**
 * Returns a signed Remote Lock for S1 with state using transaction ID (TrID) for verification.
 * @param prodMode [in] Production Mode
 * @param state [in] Lock state. State _NOT_LOCKABLE is defined for backward compatibility and should not be used.
 * @param pIMEIStr [in] An ASCII string with the IMEI number (14 digits + null termination)
 * @param pVersionResponse [in] Version response string from device. The S1_ROOT tag is used to derive the proper signing cert to create a SIN image.
 * @param pXperiaId [in] Unique ID generated by MyXperia web service as a null terminated string. Must be supplied for state _LOCKED.
 * @param pResBuf [out] A buffer where the result will be put. If the buffer is too small you will get a
 * #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, and \p pResLen will be set to the expected buffer size.
 * @param pResLen [in/out] Size of pResBuf. This will be set to the size of the result before returning.
 * @param pTrID [in] Null terminated transaction ID on format TAG1="VALUE";TAG2="VALUE"
 * @param pTrIDSignature [in] TrID signature calculated over pTrID (signing certificate name should be part of pTrID).
 * @param trIDSignatureLength [in] Length of TrID signature in bytes.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetSignedRemoteLockWithStateWithTrID(
  T_SGN_ProdModeType prodMode,
  T_SGN_RemoteLockState state,
  const char* pIMEIStr,
  const char* pVersionResponse,
  const char* pXperiaId,
  unsigned char* pResBuf,
  unsigned int* pResLen,
  const char* pTrID,
  const unsigned char* pTrIDSignature,
  unsigned int trIDSignatureLength,
  unsigned int handleIndex);

/**
 * Returns a Trusted Execution Environment binding key for the Trustonic TEE solution.
 * Part one of the result (pCmdBuf) is a CMP GenerateAuthToken command wrapped in a DRM
 * certificate structure and intended to be provisioned to the device as a DRM certificate.
 * Part two of the result (pReceipt) is a base64 formatted SD.Receipt intended to be part
 * of the receipt structure for the device, later to be included in a receipt report sent
 * to Trustonic for multiple devices.
 * @param prodMode [in] Production Mode
 * @param pIMEIStr [in] An ASCII string with the IMEI number (14 digits + null termination)
 * @param pSmkName [in] The requested Super Master Key (SMK) as a null terminated
 * string (case sensitive). If set to NULL the default SMK will be used.
 * @param pVersionResponse [in] Version response string from device. The S1_ROOT tag is used.
 * @param pSuid [in] SoC Unique ID, null terminated string with the SUID in ASCII hex format.
 * The SUID must be obtained from the device, 32 chars + null termination.
 * @param pCmdBuf [out] A buffer where the formatted command will be put. If the buffer is too small you will get a
 * #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, and \p pCmdLen will be set to the expected buffer size.
 * @param pCmdLen [in/out] Size of pCmdBuf. This will be set to the size of the result before returning.
 * @param pReceipt [out] A buffer where the base64 formatted receipt will be put. If the buffer is too small you will get a
 * #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error. However, \p receiptLen will not be set to the expected buffer size.
 * @param receiptLen [in] Size of pReceipt, it must be at least 1025 bytes.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetTeeBindingKey(
  T_SGN_ProdModeType prodMode,
  const char* pIMEIStr,
  const char* pSmkName,
  const char* pVersionResponse,
  const char* pSuid,
  unsigned char* pCmdBuf,
  unsigned int* pCmdLen,
  char* pReceipt,
  unsigned int receiptLen,
  unsigned int handleIndex);

/**
 * Simlock signature for CS using transaction ID (TrID) for verification.
 * @param pCurrentUnits [in] The array of input units.
 * @param currentUnitCount [in] The number of input units.
 * @param pNewUnits [out] The array of output units.
 * @param newUnitCount [in] The number of output units.
 * @param pIMEIStr [in] The IMEI string (14 digits + null termination).
 * @param sequenceID [in] A number identifying the signing sequence to run. Currently supported IDs are given by enum #SequenceIds.
 * @param pTrID [in] Null terminated transaction ID on format TAG1="VALUE";TAG2="VALUE"
 * @param pTrIDSignature [in] TrID signature calculated over pTrID (signing certificate name should be part of pTrID).
 * @param trIDSignatureLength [in] Length of TrID signature in bytes.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp

 <H3>Function call</H3>

 Each SECS_UnitData in array pCurrentUnits must contain a legal UnitName corresponding to the SequenceID.
 All required units for a given SequenceID must be present in the array and no other units may be present in the array.
 The order within the array regarding their UnitName is irrelevant.
 DataSize must be equal to the size of the written data in Data.
 There is no limit to the size of Data.

 The CurrentUnitCount must be equal to the number of SECS_UnitData in array pCurrentUnits.

 Each SECS_UnitData in arra pNewUnits must contain a legal UnitName corresponding to the SequenceID.
 All required units for a given SequenceID must be present in the array and no other units may be present in the array.
 The order within the array regarding their UnitName is irrelevant.
 DataSize must be equal to the allocated size of Data.
 The allocated size is the maximum size any implemented sequence requires (this could be found in the sequence specification).

 The NewUnitCount must be equal to the number of SECS_UnitData in array pNewUnits.

 <H3>Return from function</H3>
 Only data in array pNewUnits is changed. All other parameters are unchanged (should be defined as consts).
 Each SECS_UnitData in array pNewUnits will contain the Data corresponding to the UnitName after the signing
 is finished according to the given SequenceID.
 DataSize will contain the size of the data in Data.

 <H2>SequenceID specification</H2>
 For all known sequenceIDs, each input unit has the same name as the corresponding output unit.

 <H3>SequenceID 0</H3>
 Platform: A1. Size of unit data: max 2kB.
 <TABLE>
 <TR><TD>Input note<TD>output note<TD>Unitnames
 <TR><TD>-<TD>1<TD>GD_COPS_Dynamic1Variable
 <TR><TD>-<TD>1<TD>GD_COPS_Dynamic2Variable
 <TR><TD>-<TD>1<TD>GD_COPS_Dynamic3Variable
 <TR><TD>-<TD>2<TD>GD_LOSE_TEMP_UNIT1
 <TR><TD>-<TD>2<TD>GD_LOSE_TEMP_UNIT2
 <TR><TD>-<TD>2<TD>GD_LOSE_TEMP_UNIT3
 <TR><TD>-<TD>3<TD>GD_APPLICATION_BUFFER_DATA_ARRAY[0]
 <TR><TD>-<TD>3<TD>GD_APPLICATION_BUFFER_DATA_ARRAY[1]
 <TR><TD>-<TD>2<TD>GD_APPLICATION_BUFFER_DATA_ARRAY[2]
 <TR><TD>-<TD>4<TD>GD_APPLICATION_BUFFER_DATA_ARRAY[3]
 </TABLE>
 Notes: 1) Contains GD_LOSE_TEMP_UNITx, 2) Reset to 0x00 (size 1), 3) Empty (size 0), 4) Signing data

 <H3>SequenceID 1</H3>
 Platform: S1 Locosto. (As far as is currently known, this can also be used for Neptune.) Size of unit data: max 5kB.<br>
 <br>
 The following input/output units are required:<br>
 <br>
 <TABLE>
 <TR><TD><b>Name</b><TD><b>Input</b><TD><b>Output</b>
 <TR><TD>TA_APPLICATION_BUFFER_DATA_ARRAY[0]<TD>Ignored<TD>Unit is returned unchanged
 <TR><TD>TA_APPLICATION_BUFFER_DATA_ARRAY[1]<TD>Ignored<TD>Unit is returned unchanged
 <TR><TD>TA_APPLICATION_BUFFER_DATA_ARRAY[2]<TD>Ignored<TD>Unit is empty
 <TR><TD>TA_APPLICATION_BUFFER_DATA_ARRAY[3]<TD>Old signature in binary format<TD>New signature in binary format
 <TR><TD>TA_MEPD_DATA<TD>Old simlock data (corresponding to the old signature) in binary format, currently also ignored
 <TD>New new simlock data in binary format
 <TR><TD>TA_LOOSE_TEMP<TD>Simlock data to be signed in binary format<TD>Unit is empty
 <TR><TD>VERSION_RESPONSE<TD>Version response<TD>Unit is empty
 </TABLE>

 If the unit TA_APPLICATION_BUFFER_DATA_ARRAY[3] is not big enough to contain the new signature you will get
 a #SGN_SGNTOOL_SIMLOCK_SIGNATURE_LEN_ERROR error, and the length of TA_APPLICATION_BUFFER_DATA_ARRAY[3] will be set to the
 expected buffer length.

 If the unit TA_MEPD_DATA is not big enough to contain the output MEPD data you will get a
 #SGN_SGNTOOL_TA_SIMLOCK_DATA_LEN_ERROR error, and the length of TA_MEPD_DATA will be set to the expected buffer length.

 <H3>SequenceID 2</H3>
 Platform: A2. Size of unit data: max 2kB.
 *   Unit names and notes are the same as SequenceID 0.

 <H3>SequenceID 3</H3>
 Platform: S1. Functionality same as sequence ID 2, unit names are the same as sequenceID 1.
 All input data is in unit 2010 instead of using three separate units. The name TA_SIMLOCK_DATA is an alias for TA_MEPD_DATA.
 The data format for TA_SIMLOCK_DATA/TA_MEPD_DATA is binary as read from TA in phone device (as always for this API).
 Size of unit data: max 5kB.<br>
 <br>
 The following input/output units are required:<br>
 <br>
 <TABLE>
 <TR><TD><b>Name</b><TD><b>Input</b><TD><b>Output</b>
 <TR><TD>TA_APPLICATION_BUFFER_DATA_ARRAY[0]<TD>Ignored<TD>Unit data is returned unchanged
 <TR><TD>TA_APPLICATION_BUFFER_DATA_ARRAY[1]<TD>Ignored<TD>Unit data is returned unchanged
 <TR><TD>TA_APPLICATION_BUFFER_DATA_ARRAY[2]<TD>Ignored<TD>Unit is empty
 <TR><TD>TA_APPLICATION_BUFFER_DATA_ARRAY[3]<TD>Old signature in binary format<TD>New signature in binary format
 <TR><TD>TA_SIMLOCK_DATA<TD>Old simlock data (corresponding to the old signature) in binary format
 <TD>Exact copy of input unit 2010 in binary format
 <TR><TD>TA_LOOSE_TEMP<TD>Simlock data to be signed in binary format (all data is in unit 2010)<TD>Unit is empty
 <TR><TD>VERSION_RESPONSE<TD>Version response<TD>Unit is empty
 </TABLE>

 If the unit TA_APPLICATION_BUFFER_DATA_ARRAY[3] is not big enough to contain the new signature you will get
 a #SGN_SGNTOOL_SIMLOCK_SIGNATURE_LEN_ERROR error, and the length of TA_APPLICATION_BUFFER_DATA_ARRAY[3] will be set to the
 expected buffer length.

 If the unit TA_SIMLOCK_DATA is not big enough to contain the copy of input unit 2010 you will get a
 #SGN_SGNTOOL_TA_SIMLOCK_DATA_LEN_ERROR error, and the length of TA_SIMLOCK_DATA will be set to the expected buffer length.
 */
SECS_API unsigned int SGN_SimlockCSSignatureWithTrID(
  const T_SECS_UnitData* pCurrentUnits,
  unsigned int currentUnitCount,
  T_SECS_UnitData* pNewUnits,
  unsigned int newUnitCount,
  const char* pIMEIStr,
  unsigned int sequenceID,
  const char* pTrID,
  const unsigned char* pTrIDSignature,
  unsigned int trIDSignatureLength,
  unsigned int handleIndex);

/**
 * Create a S1 simlock signature for the data in \p unitDataFile, using the simlock key
 * specified by the version response \p versionResponse and the production mode \p prodMode,
 * and return the result in \p signature.
 * @param versionResponse [in] Version response string received from the device. The simlock key specified in the
 * SIM_LOCK_ROOT tag corresponding to \p prodMode will be used.
 * If \p prodMode is TEST and there is no test key is specified, a #SGN_CRYPTO_NO_SIMLOCK_TEST_KEY_SPECIFIED
 * error will be returned.
 * If \p prodMode is LIVE and there is no live key specified a #SGN_CRYPTO_NO_SIMLOCK_LIVE_KEY_SPECIFIED
 * error will be returned.
 * @param prodMode Production mode.
 * @param pIMEIStr [in] IMEI string (14 digits + null termination).
 * @param unitDataFile [in] Data to be signed in the form of a simlock.ta file in ASCII format. This file must contain unit number,
 * unit length, and unit data for unit 2010. Any other units in this file will be ignored.
 * @param unitDataFileLen [in] Length of the simlock.ta file to be signed.
 * @param signature [out] Output buffer that will contain the simlock signature. If the buffer is too small
 * an #SGN_SGNTOOL_SIMLOCK_SIGNATURE_LEN_ERROR error will be returned, and \p pSignatureLen
 * will be set to the expected buffer size.
 * @param pSignatureLen [in/out] Length of the simlock signature buffer.
 * @param keyCodes [out] Output buffer that will contain the generated key codes (each key code is 16 bytes of digits).
 * If the buffer is too small an #SGN_SGNTOOL_S1_SIMLOCK_KEYCODES_LEN_ERROR error will be returned, and \p pKeyCodesLen
 * will be set to the expected buffer size.
 * @param pKeyCodesLen [in/out] Length of the key code buffer.
 * @param pNumKeyCodes [out] Number of generated key codes (e.g 4).
 * @param modifiedUnitData [out] The modified unit 2010 in binary format. If the buffer is too small
 * an #SGN_SGNTOOL_S1_SIMLOCK_MODIFIED_DATA_LEN_ERROR error will be returned, and \p pModifiedUnitDataLen
 * will be set to the expected buffer size.
 * @param pModifiedUnitDataLen [in/out] Length of the modified unit 2010.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_S1SimlockSignature(
  const char* versionResponse,
  T_SGN_ProdModeType prodMode,
  const char* pIMEIStr,
  const unsigned char* unitDataFile,
  unsigned int unitDataFileLen,
  unsigned char* signature,
  unsigned int* pSignatureLen,
  unsigned char* keyCodes,
  unsigned int* pKeyCodesLen,
  unsigned int* pNumKeyCodes,
  unsigned char* modifiedUnitData,
  unsigned int* pModifiedUnitDataLen,
  unsigned int handleIndex);

/**
 * Create a S1 simlock signature for the data in \p unitDataFile, using the simlock key/cert
 * specified by \p pCertName and return the result in \p signature. \p pCertName is used as is
 * without any automatic logic to figure out what certificate to use in the signature (as in SGN_S1SimlockSignature() ).
 * The main use of this function should be for test when a specific signing cert is needed. It is not recommended for production.
 * @param pCertName [in] A string with the name of the certificate used for signing. E.g. S1_SL_Test_0d89_0001
 * @param pIMEIStr [in] IMEI string (14 digits + null termination).
 * @param unitDataFile [in] Data to be signed in the form of a simlock.ta file in ASCII format. This file must contain unit number,
 * unit length, and unit data for unit 2010. Any other units in this file will be ignored.
 * @param unitDataFileLen [in] Length of the simlock.ta file to be signed.
 * @param signature [out] Output buffer that will contain the simlock signature. If the buffer is too small
 * an #SGN_SGNTOOL_SIMLOCK_SIGNATURE_LEN_ERROR error will be returned, and \p pSignatureLen
 * will be set to the expected buffer size.
 * @param pSignatureLen [in/out] Length of the simlock signature buffer.
 * @param keyCodes [out] Output buffer that will contain the generated key codes (each key code is 16 bytes of digits).
 * If the buffer is too small an #SGN_SGNTOOL_S1_SIMLOCK_KEYCODES_LEN_ERROR error will be returned, and \p pKeyCodesLen
 * will be set to the expected buffer size.
 * @param pKeyCodesLen [in/out] Length of the key code buffer.
 * @param pNumKeyCodes [out] Number of generated key codes (e.g 4).
 * @param modifiedUnitData [out] The modified unit 2010 in binary format. If the buffer is too small
 * an #SGN_SGNTOOL_S1_SIMLOCK_MODIFIED_DATA_LEN_ERROR error will be returned, and \p pModifiedUnitDataLen
 * will be set to the expected buffer size.
 * @param pModifiedUnitDataLen [in/out] Length of the modified unit 2010.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_S1SimlockSignatureWithCert(
  const char* pCertName,
  const char* pIMEIStr,
  const unsigned char* unitDataFile,
  unsigned int unitDataFileLen,
  unsigned char* signature,
  unsigned int* pSignatureLen,
  unsigned char* keyCodes,
  unsigned int* pKeyCodesLen,
  unsigned int* pNumKeyCodes,
  unsigned char* modifiedUnitData,
  unsigned int* pModifiedUnitDataLen,
  unsigned int handleIndex);

#if 0
/**
 * Create a S1 simlock signature same as SGN_S1SimlockSignature(), but in case of controlled rooting, \p pSmkName
 * is used to generate RCK (see SGN_GenerateRootControlKey() ).
 * @param versionResponse [in] Version response string received from the device. The simlock key specified in the
 * SIM_LOCK_ROOT tag corresponding to \p prodMode will be used.
 * If \p prodMode is TEST and there is no test key is specified, a #SGN_CRYPTO_NO_SIMLOCK_TEST_KEY_SPECIFIED
 * error will be returned.
 * If \p prodMode is LIVE and there is no live key specified a #SGN_CRYPTO_NO_SIMLOCK_LIVE_KEY_SPECIFIED
 * error will be returned.
 * @param prodMode Production mode.
 * @param pIMEIStr [in] IMEI string (14 digits + null termination).
 * @param pSmkName [in] Super Master Key (SMK) for RCK generation as a null terminated
 * string (case sensitive). If set to NULL the default SMK (RCK_SMK_P) will be used. If default SMK is used, the resulting simlock data
 * and signature will be same as from SGN_S1SimlockSignature().
 * @param unitDataFile [in] Data to be signed in the form of a simlock.ta file in ASCII format. This file must contain unit number,
 * unit length, and unit data for unit 2010. Any other units in this file will be ignored.
 * @param unitDataFileLen [in] Length of the simlock.ta file to be signed.
 * @param signature [out] Output buffer that will contain the simlock signature. If the buffer is too small
 * an #SGN_SGNTOOL_SIMLOCK_SIGNATURE_LEN_ERROR error will be returned, and \p pSignatureLen
 * will be set to the expected buffer size.
 * @param pSignatureLen [in/out] Length of the simlock signature buffer.
 * @param keyCodes [out] Output buffer that will contain the generated key codes (each key code is 16 bytes of digits).
 * If the buffer is too small an #SGN_SGNTOOL_S1_SIMLOCK_KEYCODES_LEN_ERROR error will be returned, and \p pKeyCodesLen
 * will be set to the expected buffer size.
 * @param pKeyCodesLen [in/out] Length of the key code buffer.
 * @param pNumKeyCodes [out] Number of generated key codes (e.g 4).
 * @param modifiedUnitData [out] The modified unit 2010 in binary format. If the buffer is too small
 * an #SGN_SGNTOOL_S1_SIMLOCK_MODIFIED_DATA_LEN_ERROR error will be returned, and \p pModifiedUnitDataLen
 * will be set to the expected buffer size.
 * @param pModifiedUnitDataLen [in/out] Length of the modified unit 2010.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_S1SimlockSignatureWithSmk(
  const char* versionResponse,
  T_SGN_ProdModeType prodMode,
  const char* pIMEIStr,
  const char* pSmkName,
  const unsigned char* unitDataFile,
  unsigned int unitDataFileLen,
  unsigned char* signature,
  unsigned int* pSignatureLen,
  unsigned char* keyCodes,
  unsigned int* pKeyCodesLen,
  unsigned int* pNumKeyCodes,
  unsigned char* modifiedUnitData,
  unsigned int* pModifiedUnitDataLen,
  unsigned int handleIndex);
#endif

/**
 * Create a S1 simlock signature for the data in \p unitDataFile, using the simlock key
 * specified by the version response \p versionResponse and the production mode \p prodMode,
 * and return the result in \p signature.
 * The generated key codes are put together in a block and then encrypted. The result is delivered in \p keyCodeBlock
 * @param versionResponse [in] Version response string received from the device. The simlock key specified in the
 * S1_ROOT (or older SIM_LOCK_ROOT) tag corresponding to \p prodMode will be used.
 * If \p prodMode is TEST and there is no test key is specified, a #SGN_CRYPTO_NO_SIMLOCK_TEST_KEY_SPECIFIED
 * error will be returned.
 * If \p prodMode is LIVE and there is no live key specified a #SGN_CRYPTO_NO_SIMLOCK_LIVE_KEY_SPECIFIED
 * error will be returned.
 * @param prodMode Production mode.
 * @param pIMEIStr [in] IMEI string (14 digits + null termination).
 * @param unitDataFile [in] Data to be signed in the form of a simlock.ta file in ASCII format. This file must contain unit number,
 * unit length, and unit data for unit 2010. Any other units in this file will be ignored.
 * @param unitDataFileLen [in] Length of the simlock.ta file to be signed.
 * @param signature [out] Output buffer that will contain the simlock signature. If the buffer is too small
 * an #SGN_SGNTOOL_SIMLOCK_SIGNATURE_LEN_ERROR error will be returned, and \p pSignatureLen
 * will be set to the expected buffer size.
 * @param pSignatureLen [in/out] Length of the simlock signature buffer.
 * @param keyCodeBlock [out] Output buffer that will contain the block of all generated key codes as a null terminated string,
 * encrypted for security. If the buffer is too small an #SGN_SGNTOOL_S1_SIMLOCK_KEYCODES_LEN_ERROR error will be returned,
 * and \p pKeyCodeBlockLen will be set to the expected buffer size.
 * @param pKeyCodeBlockLen [in/out] Length of the buffer for the encrypted key code block, a size of 1024 bytes is recommended.
 * @param modifiedUnitData [out] The modified unit 2010 in binary format. If the buffer is too small
 * an #SGN_SGNTOOL_S1_SIMLOCK_MODIFIED_DATA_LEN_ERROR error will be returned, and \p pModifiedUnitDataLen
 * will be set to the expected buffer size.
 * @param pModifiedUnitDataLen [in/out] Length of the modified unit 2010.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_S1SimlockSignatureSecure(
  const char* versionResponse,
  T_SGN_ProdModeType prodMode,
  const char* pIMEIStr,
  const unsigned char* unitDataFile,
  unsigned int unitDataFileLen,
  unsigned char* signature,
  unsigned int* pSignatureLen,
  char* keyCodeBlock,
  unsigned int* pKeyCodeBlockLen,
  unsigned char* modifiedUnitData,
  unsigned int* pModifiedUnitDataLen,
  unsigned int handleIndex);

/**
 * Create a S1 simlock signature for the data in \p unitDataFile, using the simlock key/cert
 * specified by the \p pCertName and return the result in \p signature. \p pCertName is used as is
 * without any logic trying to figure out what certificate to use in the signature (as in SGN_S1SimlockSignature() ).
 * The generated key codes are put together in a block and then encrypted. The result is delivered in \p keyCodeBlock
 * The main use of this function should be for test when a specific signing cert is needed. It is not recommended for production.
 * @param pCertName [in] A string with the name of the certificate used for signing. E.g. S1_SL_Test_0d89_0001
 * @param pIMEIStr [in] IMEI string (14 digits + null termination).
 * @param unitDataFile [in] Data to be signed in the form of a simlock.ta file in ASCII format. This file must contain unit number,
 * unit length, and unit data for unit 2010. Any other units in this file will be ignored.
 * @param unitDataFileLen [in] Length of the simlock.ta file to be signed.
 * @param signature [out] Output buffer that will contain the simlock signature. If the buffer is too small
 * an #SGN_SGNTOOL_SIMLOCK_SIGNATURE_LEN_ERROR error will be returned, and \p pSignatureLen
 * will be set to the expected buffer size.
 * @param pSignatureLen [in/out] Length of the simlock signature buffer.
 * @param keyCodeBlock [out] Output buffer that will contain the block of all generated key codes encrypted for security as a null terminated string.
 * If the buffer is too small an #SGN_SGNTOOL_S1_SIMLOCK_KEYCODES_LEN_ERROR error will be returned, and \p pKeyCodeBlockLen
 * will be set to the expected buffer size.
 * @param pKeyCodeBlockLen [in/out] Length of the buffer for the encrypted key code block, a size of 1024 bytes is recommended.
 * @param modifiedUnitData [out] The modified unit 2010 in binary format. If the buffer is too small
 * an #SGN_SGNTOOL_S1_SIMLOCK_MODIFIED_DATA_LEN_ERROR error will be returned, and \p pModifiedUnitDataLen
 * will be set to the expected buffer size.
 * @param pModifiedUnitDataLen [in/out] Length of the modified unit 2010.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_S1SimlockSignatureSecureWithCert(
  const char* pCertName,
  const char* pIMEIStr,
  const unsigned char* unitDataFile,
  unsigned int unitDataFileLen,
  unsigned char* signature,
  unsigned int* pSignatureLen,
  char* keyCodeBlock,
  unsigned int* pKeyCodeBlockLen,
  unsigned char* modifiedUnitData,
  unsigned int* pModifiedUnitDataLen,
  unsigned int handleIndex);

/**
 * Re-customize simlock with strict check of signature for old data. Same basic functionality as
 * SGN_S1SimlockCSSignature(), but strict signature check and input/output parameters on the
 * form like SGN_S1SimlockSignature().
 * oldUnitData and oldSignature are both binary data from device (Misc TA units 2010 and 2129 respectively).
 * oldSignature is checked for oldUnitData and failure is returned if validation is not successful.
 * New customization from ASCII hex file unitDataFile is applied and resulting data is returned in
 * modifiedUnitData and signature (both binary). They should be written back to the device (Misc TA units
 * 2010 and 2129 respectively).
 * Used for Late Customization.
 * @param versionResponse [in] Version response string received from the device. The simlock key specified in the
 * S1_ROOT (or older SIM_LOCK_ROOT) tag corresponding to \p prodMode will be used.
 * If \p prodMode is TEST and there is no test key is specified, a #SGN_CRYPTO_NO_SIMLOCK_TEST_KEY_SPECIFIED
 * error will be returned.
 * If \p prodMode is LIVE and there is no live key specified a #SGN_CRYPTO_NO_SIMLOCK_LIVE_KEY_SPECIFIED
 * error will be returned.
 * @param prodMode Production mode.
 * @param pIMEIStr [in] IMEI string (14 digits + null termination).
 * @param oldUnitData [in] Data containing the old simlock, in binary form.
 * @param oldUnitDataLen [in] Length of the old unit data in bytes.
 * @param oldSignature [in] Data containing the old signature, in binary form.
 * @param oldSignatureLen [in] Length of the old signature in bytes.
 * @param unitDataFile [in] Data containing new customization in the form of a simlock.ta file in ASCII format. This file must contain unit number,
 * unit length, and unit data for unit 2010. Any other units in this file will be ignored.
 * @param unitDataFileLen [in] Length of the unit data file in bytes.
 * @param modifiedUnitData [out] The modified unit 2010 in binary format. If the buffer is too small
 * an #SGN_SGNTOOL_S1_SIMLOCK_MODIFIED_DATA_LEN_ERROR error will be returned, and \p pModifiedUnitDataLen
 * will be set to the expected buffer size.
 * @param pModifiedUnitDataLen [in/out] Length of the modified unit buffer, will contain actual length on successful return.
 * @param signature [out] Output buffer that will contain the simlock signature. If the buffer is too small
 * an #SGN_SGNTOOL_SIMLOCK_SIGNATURE_LEN_ERROR error will be returned, and \p pSignatureLen
 * will be set to the expected buffer size.
 * @param pSignatureLen [in/out] Length of the simlock signature buffer, will contain actual length on successful return.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_S1SimlockLCSignature(
  const char* versionResponse,
  T_SGN_ProdModeType prodMode,
  const char* pIMEIStr,
  const unsigned char* oldUnitData,
  unsigned int oldUnitDataLen,
  const unsigned char* oldSignature,
  unsigned int oldSignatureLen,
  const unsigned char* unitDataFile,
  unsigned int unitDataFileLen,
  unsigned char* modifiedUnitData,
  unsigned int* pModifiedUnitDataLen,
  unsigned char* signature,
  unsigned int* pSignatureLen,
  unsigned int handleIndex);

/**
 * Create a S1 simlock signature for the data in the input unit \p TA_LOOSE_TEMP,
 * using the live simlock key from the input unit \p VERSION_RESPONSE, and return
 * the result in the output unit \p TA_APPLICATION_BUFFER_DATA_ARRAY[3].
 * If no live simlock key is specified in the S1_ROOT (or older SIM_LOCK_ROOT) tag in the input unit
 * \p VERSION_RESPONSE, a #SGN_CRYPTO_NO_SIMLOCK_LIVE_KEY_SPECIFIED error will be returned.
 *
 * @param inputUnits [in] The array of input units.
 * @param inputUnitCount [in] The number of input units.
 * @param outputUnits [out] The array of output units.
 * @param outputUnitCount [in] The number of allocated output units.
 * @param pIMEIStr [in] The IMEI string (14 digits + null termination).
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 *
 * The following input/output units are required:<br><br>
 * <TABLE>
 * <TR><TD><b>Name</b><TD><b>Input</b><TD><b>Output</b>
 * <TR><TD>TA_APPLICATION_BUFFER_DATA_ARRAY[0]<TD>Ignored<TD>Unit data is returned unchanged
 * <TR><TD>TA_APPLICATION_BUFFER_DATA_ARRAY[1]<TD>Ignored<TD>Unit data is returned unchanged
 * <TR><TD>TA_APPLICATION_BUFFER_DATA_ARRAY[2]<TD>Ignored<TD>Unit is empty
 * <TR><TD>TA_APPLICATION_BUFFER_DATA_ARRAY[3]<TD>Old S1 simlock signature in binary format<TD>New S1 simlock signature in binary format
 * <TR><TD>TA_SIMLOCK_DATA<TD>Old unit 2010 S1 simlock data (corresponding to the old S1 simlock signature) in binary format<TD>
 * The modified unit 2010 S1 simlock data in binary format
 * <TR><TD>TA_LOOSE_TEMP<TD>The unit 2010 S1 simlock data to be signed in binary format<TD>Unit is empty
 * <TR><TD>VERSION_RESPONSE<TD>Version response<TD>Unit is empty
 * </TABLE>
 *
 * If the output unit \p TA_APPLICATION_BUFFER_DATA_ARRAY[3] is not big enough to contain the new signature
 * an #SGN_SGNTOOL_SIMLOCK_SIGNATURE_LEN_ERROR error will be returned, and the length of \p TA_APPLICATION_BUFFER_DATA_ARRAY[3]
 * will be set to the expected buffer length.
 *
 * If the output unit \p TA_SIMLOCK_DATA is not big enough to contain the modified unit 2010 data an
 * #SGN_SGNTOOL_S1_SIMLOCK_MODIFIED_DATA_LEN_ERROR error will be returned, and the length of \p TA_SIMLOCK_DATA
 * will be set to the expected buffer length.
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_S1SimlockCSSignature(
  const T_SECS_UnitData* inputUnits,
  unsigned int inputUnitCount,
  T_SECS_UnitData* outputUnits,
  unsigned int outputUnitCount,
  const char* pIMEIStr,
  unsigned int handleIndex);

/**
 * Simlock signature for CS using transaction ID (TrID) for verification. See SGN_S1SimlockCSSignature() for details.
 * @param inputUnits [in] The array of input units.
 * @param inputUnitCount [in] The number of input units.
 * @param outputUnits [out] The array of output units.
 * @param outputUnitCount [in] The number of allocated output units.
 * @param pIMEIStr [in] The IMEI string (14 digits + null termination).
 * @param pTrID [in] Null terminated transaction ID on format TAG1="VALUE";TAG2="VALUE"
 * @param pTrIDSignature [in] TrID signature calculated over pTrID (signing certificate name should be part of pTrID).
 * @param trIDSignatureLength [in] Length of TrID signature in bytes.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_S1SimlockCSSignatureWithTrID(
  const T_SECS_UnitData* inputUnits,
  unsigned int inputUnitCount,
  T_SECS_UnitData* outputUnits,
  unsigned int outputUnitCount,
  const char* pIMEIStr,
  const char* pTrID,
  const unsigned char* pTrIDSignature,
  unsigned int trIDSignatureLength,
  unsigned int handleIndex);

/**
 * Returns a signed data blob containing Generic Unlock Codes. The clear text unlock codes are returned in
 * the \p pCodeBlock parameter.
 * @param prodMode [in] Production Mode
 * @param pIMEIStr [in] An ASCII string with the IMEI number (14 digits + null termination)
 * @param pVersionResponse [in] Version response string from device. The S1_ROOT tag is used to derive the proper signing cert to create a SIN image.
 * @param pResBuf [out] Output buffer that will contain the resulting data blob. If the buffer is too small a
 * #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error will be returned, and \p pResLen will be set to the expected buffer size.
 * @param pResLen [in/out] Size of pResBuf. This will be set to the size of the result before returning.
 * @param pCodeBlock [out] Output buffer that will contain the block of all generated unlock codes in clear text, as a null terminated string.
 * If the buffer is too small a #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error will be returned, and \p pCodeBlockLen will be set
 * to the expected buffer size.
 * @param pCodeBlockLen [in/out] Size of pCodeBlock. This will be set to the size of the result before returning.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetSignedGenericUnlockCodes(
    T_SGN_ProdModeType prodMode,
    const char* pIMEIStr,
    const char* pVersionResponse,
    unsigned char* pResBuf,
    unsigned int* pResLen,
    char* pCodeBlock,
    unsigned int* pCodeBlockLen,
    unsigned int handleIndex);

/**
 * Returns a signed data blob containing Generic Unlock Codes. The encrypted unlock codes are returned in
 * the \p pCodeBlock parameter.
 * @param prodMode [in] Production Mode
 * @param pIMEIStr [in] An ASCII string with the IMEI number (14 digits + null termination)
 * @param pVersionResponse [in] Version response string from device. The S1_ROOT tag is used to derive the proper signing cert to create a SIN image.
 * @param pResBuf [out] Output buffer that will contain resulting data blob. If the buffer is too small a
 * #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error will be returned, and \p pResLen will be set to the expected buffer size.
 * @param pResLen [in/out] Size of pResBuf. This will be set to the size of the result before returning.
 * @param pCodeBlock [out] Output buffer that will contain the block of all generated unlock codes as a null terminated string, encrypted for security.
 * If the buffer is too small a #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error will be returned, and \p pCodeBlockLen will be set
 * to the expected buffer size.
 * @param pCodeBlockLen [in/out] Size of pCodeBlock. This will be set to the size of the result before returning.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetSignedGenericUnlockCodesSecure(
    T_SGN_ProdModeType prodMode,
    const char* pIMEIStr,
    const char* pVersionResponse,
    unsigned char* pResBuf,
    unsigned int* pResLen,
    char* pCodeBlock,
    unsigned int* pCodeBlockLen,
    unsigned int handleIndex);

/**
 * Creates a signed Debug Policy for use in a QC device. The data returned is a signed ELF that needs
 * to be further signed/formatted to be S1 compatible. The list of Image ID, Root Cert Hash and signing
 * cert chain are all bound by the template revision to specific values.
 * @param pRevision [in] The requested Debug Policy revision as a nullterminated string (case sensitive), e.g. DBGP_MSM8996_001.
 * @param flagsHigh [in] Debug Policy Flags, high 32 bits
 * @param flagsLow [in] Debug Policy Flags, low 32 bits
 * @param deviceId [in] Device Id from QC device, also called Serial Number in QC documentation. Only one can be set.
 * @param pResBuf [out] A buffer where the result will be put. If the buffer is too small you will get a
 * #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, and \p pResLen will be set to the expected buffer size.
 * @param pResLen [in/out] Size of pResBuf. This will be set to the size of the result before returning.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetSignedDebugPolicy(
    const char* pRevision,
    unsigned int flagsHigh,
    unsigned int flagsLow,
    unsigned int deviceId,
    unsigned char* pResBuf,
    unsigned int* pResLen,
    unsigned int handleIndex);

/**
 * Enables the JTAG functionality of the R&D certificate specified by the version
 * string \p version and writes the data found in \p pCertBuffer
 * into it. The certificate is then resigned and returned in the buffer \p pCertBuffer.
 * @param pCertBuffer [in/out] Pre-allocated certificate buffer. As input parameter this contains data the user wants to change from
 *                             the default values set in the R&D certificate, and these values are changed only if it
 *                             is allowed by the corresponding certificate mask. As output parameter
 *                             this contains the resulting R&D certificate with JTAG enabled.
 * @param certBufferLen [in] The size of the result buffer. The size required varies
 *                           depending on the R&D certificate type, i.e. Locosto or Neptune.
 * @param pVersion [in] A version string used to determine the certificate type and to find the certificate mask, the R&D certificate, and the private key used to sign it.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_EnableJTAG(
  unsigned char* pCertBuffer,
  unsigned int certBufferLen,
  const char* pVersion,
  unsigned int handleIndex);

/**
 * This function determines if the dongle \p dongleId is currently active or not,
 * and returns the result in \p pResult.
 * @param dongleId [in] The id of the dongle.
 * @param pResult [out] Will contain 1 if the dongle is active, or 0 if the dongle is inactive (or does not exist).
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_IsActiveDongle(
  const unsigned char* dongleId,
  unsigned int* pResult,
  unsigned int handleIndex);

/**
 * This function determines the status of an authentication certificate in \p pAuthCertId,
 * and returns the result in \p pResult.
 * @param pAuthCertId [in] The id of the authentication certificate (dongle or card).
 * @param pStatus [out] Will contain the status according to the following:
 *                      0: the certificate is unknown (doesn't exist in the database)
 *                      1: the certificate is active
 *                      2: the certificate has expired (see pTimespan)
 *                      3: the certificate has been manually blocked
 * @param pTimeSpan [out] Pre-allocated buffer which should receive the active timespan in all successful
 *                        cases except when certificate is unknown. The returned time span is on the
 *                        form YYYY-MM-DD hh:mm:ss -- YYYY-MM-DD hh:mm:ss and is a null terminated string.
 * @param pTimeSpanLen [in/out] Length of the preallocated buffer pTimeSpan. Should be at least 43 bytes.
 *                              If the buffer is too small you will get a #SGN_SGNTOOL_EXCEEDS_BUFFER error,
 *                              and \p pTimeSpanLen will be set to the expected buffer size.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetAuthCertStatus(
  const char* pAuthCertId,
  unsigned int* pStatus,
  char* pTimeSpan,
  unsigned int* pTimeSpanLen,
  unsigned int handleIndex);

/**
 * This function changes the expiration time for the authentication certificate \p pAuthCertId.
 * @param pAuthCertId [in] The id of the authentication certificate (dongle or card).
 * @param pExpTime [in] The desired new expiration time in a null terminated string on either of the
 *                      the forms YYYYMMDD, YYYY-MM-DD or YYYY-MM-DD hh:mm:ss.
 *                      The time part will be set to 00:00:00 if hh:mm:ss is omitted.
 *                      If the format is incorrect the expiration time will be reset to a safe value,
 *                      use SGN_GetAuthCertStatus() to check the result of the database transaction.
 * @param pResult [out] Will contain 1 if the certificate was found in the database, or 0 if it was not.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_SetAuthCertExpiration(
  const char* pAuthCertId,
  const char* pExpTime,
  unsigned int* pResult,
  unsigned int handleIndex);

/**
 * Returns information about the last successful client request, i.e. authenticate certificate ID, URL, and proxy.
 * Authentication certificate ID is only updated on a successful client request, however URL and proxy configuration
 * is returned even if no connection to a server has been made.
 * @param pInfo [out] Contains last request information.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetLastRequestInfo(
  T_SGN_LastRequestInfo* pInfo,
  unsigned int handleIndex);

/**
 * Checks if the IMEI number \p pIMEIStr belongs to a TAC reserved for pre-commercial use.
 * @param pResult [out] This parameter will contain 1 if \p pIMEIStr belongs to a TAC
 * reserved for pre-commercial use, otherwise it will contain 0.
 * @param pIMEIStr [in] IMEI str (14 digits + null termination)
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_CheckPreCommercialIMEI(
  unsigned int* pResult,
  const char* pIMEIStr,
  unsigned int handleIndex);

/**
 * Gets the classification for IMEI/MEID number \p pIMEIStr. Will return 0 for dev/test,
 * 1 for pre-commercial and 2 for commercial. This function can be used instead of SGN_GetPaf() to get
 * ProdMode. The result should be interpreted as 0 -> TEST, 1 or 2 -> LIVE (or 0 -> TEST, everything else -> LIVE).
 * SGN_CheckPreCommercialIMEI() is superseeded by this function. This function will give the correct
 * result for pre-commercial where SGN_CheckPreCommercialIMEI() might not in special cases.
 * @param pResult [out] This parameter will contain 0 if \p pIMEIStr should be used for
 * dev/prototype production, 1 if \p pIMEIStr should be used for pre-commercial production
 * and 2 if \p pIMEIStr should be used for commercial/HVM production.
 * @param pIMEIStr [in] IMEI str (14 digits + null termination)
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetIMEIClassification(
  unsigned int* pResult,
  const char* pIMEIStr,
  unsigned int handleIndex);
/*@}*/


#ifdef DOXYGEN
  }; // end of class Methods.
#endif


#endif // INCLUSION_GUARD
