/*********************************************************************
 * Copyright (c) 2008 Sony Ericsson Mobile Communications AB.        *
 * Copyright (c) 2012 Sony Mobile Communications AB.                 *
 * All rights, including trade secret rights, reserved.              *
 *********************************************************************/

#ifndef __INCLUSION_GUARD_SECSDEPRECATED_INCLUDED_H_
#define __INCLUSION_GUARD_SECSDEPRECATED_INCLUDED_H_

#include <stddef.h>

/*
This file contains all functions and types in the SECS API that has been deprecated.
If any function declared here for some reason should _not_ be deprecated,
feel free to move it back to SECSExported.h
*/

/// The available certificate types.
////////////////////////////////////////////////////////////////////
typedef enum SGN_CertificateType {
  _CERTIFICATE_PROD_CA_VER1 = 7,
  _CERTIFICATE_PROD_CA_VER2,
  _CERTIFICATE_CMLA_BULK,
  _CERTIFICATE_CMLA,
  _CERTIFICATE_SEMCDRM,
  _CERTIFICATE_VIACCESS,
  _CERTIFICATE_MICROSOFT,
  _CERTIFICATE_MARLIN,
  _CERTIFICATE_HDCP_AV8100
} T_SGN_CertificateType;
////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
/**
 * Data about a CMLA blob.
 * \deprecated No longer used.
 */
typedef struct SECS_CMLABlobInfo {
  /// Number of certificates(?)
  unsigned  int CertCount;
  /// The file name.
  char Filename[MAXFILENAME];
} T_SECS_CMLABlobInfo;

// StorageType values
#define SGN_STYPE_GDFS 0
#define SGN_STYPE_TA   1
#define SGN_STYPE_TA_ONEUNIT 2
#define SGN_STYPE_TA_SEMC_S1 3

#define SGN_STYPE_UNDEFINED 999

////////////////////////////////////////////////////////////////////////////////////

/**
 * \defgroup SecsDeprecated Deprecated SECS API Functions
 */
/*@{*/

/**
 * Fetches a Sony Connect Certificate/CMLA Certificate
 * @param ProdMode [in] Production Mode
 * @param CertType [in] Certificate type
 * @param pIMEIStr [in] IMEI number (14 digits + null termination)
 * @param pucData [out] Certificate
 * @param puiDataLength [out] Length of Certificate
 * @param handleIndex [in] Handle index recived from SECS::SGN_GetHandle() or SECS::SGN_GetExtHandle().
 * @return SECS::T_SECSErrorCodesExp
 * \deprecated Use SECS::SGN_GetDrmCertificate() instead.
 */

SECS_API unsigned int SGN_GetCertificateGDFS(
  T_SGN_ProdModeType ProdMode,
  int CertType,
  const char* pIMEIStr,
  unsigned char* pucData,
  unsigned int *puiDataLength,
  unsigned int handleIndex);


/**
 * Create a Simlock signature
 * @param pResultBuffer [out] Result buffer contains simlock signature.
 * @param pResultLen [out] Result length.
 * @param pGdfFileBuffer [in] Input GDFS data i.e simlock.gdf in a buffer.
 * @param GdfBufferLength [in] Gdf buffer length.
 * @param CodeCount [in] Number of used key codes (i.e 12).
 * @param pKeyBuffer [out] Keycode block containing CodeCount keycodes (each keycode is 16 bytes of digits).
 * @param pIMEIStr [in] IMEI (14 digits + null termination).
 * @param ProdMode [in] Production mode.
 * @param handleIndex [in] Handle index recieved from SECS::SGN_GetHandle() or SECS::SGN_GetExtHandle().
 * @return SECS::T_SECSErrorCodesExp
 * \deprecated Use SGN_Signature_v2() instead.
 */

SECS_API unsigned int SGN_SimlockSignature(unsigned char *pResultBuffer,
                       unsigned int *pResultLen,
                       const unsigned char *pGdfFileBuffer,
                       unsigned int GdfBufferLength,
                       int CodeCount,
                       unsigned char *pKeyBuffer,
                       const char *pIMEIStr,
                       T_SGN_ProdModeType ProdMode,
                       unsigned int handleIndex);

/**
 * Create a Simlock signature.
 * @param pResultBuffer [out] Result buffer contains simlock signature. If the buffer is too small
 * you will get a #SGN_SGNTOOL_EXCEEDS_BUFFER error, and <b><i>pResultLen</i></b>
 * will be set to the expected buffer size.
 * @param pResultLen [in/out] Result Length.
 * @param pResultTaMepd [out] Output Mepd data, if applicable, or NULL (e.g., for A1, A2).
 * If applicable and the buffer is too small you will get a #SGN_SGNTOOL_EXCEEDS_BUFFER error, and
 * <b><i>pResultTaMepdLen</i></b> will be set to the expected buffer size.
 * @param pResultTaMepdLen [in/out] Length of output Mepd data, if any. Set to 0 if pResultTaMepd is NULL.
 * @param pStorageFileBuffer [in] Input buffer data i.e simlock.gdf in a buffer.
 * @param storageBufferLength [in] buffer length
 * @param storageType [in] Storage type that buffer came from. Use #SGN_STYPE_TA_ONEUNIT for HB109 Open
 * @param codeCount [in] Number of used KeyCodes (e.g, 12 or 5)
 * @param pKeyBuffer [out] Keycode block containing CodeCount keycodes (each keycode is 16 bytes of digits)
 * @param pIMEIStr [in] IMEI str (14 digits + null termination)
 * @param pDeviceIdStr [in] Device Id str, or NULL if not applicable, such as for A1, A2 and S1 (HB109 Open).
 * @param prodMode [in] Production Mode
 * @param handleIndex [in] Handle index recieved from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_SimlockSignature_v3(
  unsigned char* pResultBuffer,
  unsigned int* pResultLen,
  unsigned char* pResultTaMepd,
  unsigned int* pResultTaMepdLen,
  const unsigned char* pStorageFileBuffer,
  unsigned int storageBufferLength,
  int storageType,
  int codeCount,
  unsigned char* pKeyBuffer,
  const char* pIMEIStr,
  const char* pDeviceIdStr,
  T_SGN_ProdModeType prodMode,
  unsigned int handleIndex);

/**
 * Create a simlock signature using the key specified by the version response.
 * @param pVersionResponse [in] The version response string recieved from the phone.
 * @param pResultBuffer [out] Result buffer contains simlock signature. If the buffer is too small
 * you will get a #SGN_SGNTOOL_EXCEEDS_BUFFER error, and <b><i>pResultLen</i></b>
 * will be set to the expected buffer size.
 * @param pResultLen [in/out] Result Length.
 * @param pResultTaMepd [out] Output Mepd data, if applicable, or NULL (e.g., for A1, A2).
 * If applicable and the buffer is too small you will get a #SGN_SGNTOOL_EXCEEDS_BUFFER error, and
 * <b><i>pResultTaMepdLen</i></b> will be set to the expected buffer size.
 * @param pResultTaMepdLen [in/out] Length of output Mepd data, if any. Set to 0 if pResultTaMepd is NULL.
 * @param pStorageFileBuffer [in] Input buffer data i.e simlock.gdf in a buffer.
 * @param storageBufferLength [in] buffer length
 * @param storageType [in] Storage type that buffer came from. Use #SGN_STYPE_TA_ONEUNIT for HB109 Open
 * @param codeCount [in] Number of used KeyCodes (e.g, 12 or 5).
 * @param pKeyBuffer [out] Keycode block containing CodeCount keycodes (each keycode is 16 bytes of digits).
 * @param pIMEIStr [in] IMEI str (14 digits + null termination).
 * @param pDeviceIdStr [in] Device Id str, or NULL if not applicable, such as for A1, A2 and S1 (HB109 Open).
 * @param prodMode [in] Production Mode.
 * @param handleIndex [in] Handle index recieved from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_SimlockSignature_v4(
  const char* pVersionResponse,
  unsigned char* pResultBuffer,
  unsigned int* pResultLen,
  unsigned char* pResultTaMepd,
  unsigned int* pResultTaMepdLen,
  const unsigned char* pStorageFileBuffer,
  unsigned int storageBufferLength,
  int storageType,
  int codeCount,
  unsigned char* pKeyBuffer,
  const char* pIMEIStr,
  const char* pDeviceIdStr,
  T_SGN_ProdModeType prodMode,
  unsigned int handleIndex);


/**
 * Creates a Simlock signature from a list of units (for a ResetStation).
 * @param pGdfsNewUnits [out] Pointer to first item in an array of new GDFSUnits.
 *    Note: Sequence {6:0, 14:0, 28:0, 2128:1, 2129:1=(New GDFSSignature)}
 *    Note: 2128:1,2129:1 empty with size 2035 bytes
 * @param NewUnitCount [out] Number of GDFS units used.
 * @param CodeCount [in] Number of used KeyCodes (i.e 12 for A1/A2)
 * @param pKeyBuffer [in] KeyCode strings (each string 16 digits)
 * @param pIMEIStr [in] IMEI str (14 digits + null termination)
 * @param ProdMode [in] Production Mode
 * @param handleIndex [in] Handle index recieved from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */

SECS_API unsigned int SGN_SimlockRSSignature(
  T_SECS_GDFSUnitData *pGdfsNewUnits,
  unsigned int NewUnitCount,
  int CodeCount,
  unsigned char *pKeyBuffer,
  const char *pIMEIStr,
  T_SGN_ProdModeType ProdMode,
  unsigned int handleIndex);


/**
 * Create a Simlock signature.
 * @param pResultBuffer [out] Result buffer contains simlock signature.
 * @param pResultLen [out] Result length.
 * @param pStorageFileBuffer [in] Input buffer data i.e simlock.gdf in a buffer
 * @param StorageBufferLength [in] buffer length
 * @param iStorageType [in] Storage type that buffer came from (TA not supported. For S1, use SGN_SimlockSignature_v3 instead).
 * @param CodeCount [in] Number of used KeyCodes (i.e 12)
 * @param pKeyBuffer [out] Keycode block containing CodeCount keycodes (each keycode is 16 bytes of digits)
 * @param pIMEIStr [in] IMEI str (14 digits + null termination)
 * @param ProdMode [in] Production Mode
 * @param handleIndex [in] Handle index recieved from SECS::SGN_GetHandle() or SECS::SGN_GetExtHandle().
 * @return SECS::T_SECSErrorCodesExp
 * \deprecated Use SGN_SimlockSignature_v3() instead.
 */

SECS_API unsigned int SGN_SimlockSignature_v2(unsigned char *pResultBuffer,
                     unsigned int *pResultLen,
                     const unsigned char *pStorageFileBuffer,
                     unsigned int StorageBufferLength,
                     int iStorageType,
                     int CodeCount,
                     unsigned char *pKeyBuffer,
                     const char *pIMEIStr,
                     T_SGN_ProdModeType ProdMode,
                     unsigned int handleIndex);

/**
 * Create a Simlock signature in the Customer service flow
 * Used by: CS.
 * @param pCurrentUnits [in] The array of input units.
 * @param currentUnitCount [in] The number of input units.
 * @param pNewUnits [out] The array of output units.
 * @param newUnitCount [in] The number of output units.
 * @param pIMEIStr [in] The IMEI string (14 digits + null termination).
 * @param sequenceID [in] A number identifying the signing sequence to run. Currently supported IDs are given by enum #SequenceIds.
 * @param handleIndex [in] Handle index recieved from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp

 <H3>Function call</H3>

 Each SECS_UnitData in array pCurrentUnits must contain a legal UnitName corresponding to the SequenceID.
 All required units for a given SequenceID must be present in the array and no other units may be persent in the array.
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
SECS_API unsigned int SGN_SimlockCSSignature_v2(
  const T_SECS_UnitData* pCurrentUnits,
  unsigned int currentUnitCount,
  T_SECS_UnitData* pNewUnits,
  unsigned int newUnitCount,
  const char* pIMEIStr,
  unsigned int sequenceID,
  unsigned int handleIndex);

/**
 * This function takes a revision number <b><i>revisionNumber</i></b>, a requested format <b><i>requestedFormat</i></b>,
 * and an IMEI number <b><i>pIMEIStr</i></b> as input, and returns the corresponding S1 OTP configuration in <b><i>OTPData</i></b>
 * and the length of the configuration in <b><i>otpDataSize</i></b>. If the first digit of the IMEI number is 0 an R&D OTP configuration
 * will be returned, otherwise a LIVE OTP configuration will be returned.<br>
 * @param OTPData [out] Contains the resulting OTP data. Allocated/deleted by the caller.
 * @param otpDataSize [in/out] Contains the length of the resulting OTP data. As input parameter, this is the maximum size allocated for the OTP data buffer.
 * @param revisionNumberOut [out] The 32 bit revision number of the OTP data returned. This is usually the same as the value specified in the
 * <b><i>revisionNumber</i></b> parameter, but is different in case the special revision number value used to get the latest configuration is specified.
 * @param revisionNumber [in] The requested 32 bit revision number, e.g. 0. If the value 0xffffffff is specified the most recent OTP configuration is returned.
 * @param requestedFormat [in] The requested 8 bit format. This parameter currently only supports the value 1.
 * @param pIMEIStr [in] The IMEI number, used to determine whether an R&D or LIVE OTP configuration is requested.
 * @param pDeviceIdStr [in] The device ID. This parameter is for possible future purposes but is not currently used.
 * @param handleIndex [in] Handle recieved from SECS::SGN_GetHandle() or SECS::SGN_GetExtHandle().
 * @return SECS::T_SECSErrorCodesExp
 * \deprecated Use the SECS::SGN_S1OTP_v2 function instead.
 */

#ifdef __cplusplus // the reference "&" makes this not compile under c.

SECS_API unsigned int SGN_S1OTP(
  unsigned char* OTPData,
  size_t& otpDataSize,
  unsigned long int& revisionNumberOut,
  const unsigned long int revisionNumber,
  const unsigned short requestedFormat,
  const char* pIMEIStr,
  const char* pDeviceIdStr,
  unsigned int handleIndex);

#endif

/**
 * Takes a revision string <b><i>revisionString</i></b> and an IMEI number <b><i>pIMEIStr</i></b> as input,
 * and returns the corresponding S1 OTP configuration in <b><i>OTPData</i></b> and the length of the configuration in <b><i>otpDataSize</i></b>.
 * If the first digit of the IMEI number is 0 and the second digit is not 1 then an R&D OTP configuration will be returned,
 * otherwise a LIVE OTP configuration will be returned.
 * @param pOTPData [out] This parameter will contain the resulting OTP data (allocated/deleted by the caller).
 * If the buffer is too small you will get a #SGN_SGNTOOL_EXCEEDS_BUFFER error, and <b><i>otpDataSize</i></b>
 * will be set to the expected buffer size.
 * @param pOtpDataSize [in/out] This parameter will contain the length of the resulting OTP data.
 * As input parameter, this is the maximum size allocated for the OTP data buffer.
 * @param pRevStr [in] The requested OTP revision as a nullterminated string (case sensitive), e.g. R1A.
 * @param pIMEIStr [in] The IMEI number, used to determine whether an R&D or LIVE OTP configuration is requested.
 * @param handleIndex [in] Handle index recieved from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 * \deprecated Use the SECS::SGN_GetSecurityPropertiesWithSmk function instead.
 */
SECS_API unsigned int SGN_S1OTP_v2(
  unsigned char* pOTPData,
  size_t* pOtpDataSize,
  const char* pRevStr,
  const char* pIMEIStr,
  const unsigned int handleIndex);

/**
 * Generates a device key (used for DRM certificates) for the IMEI number
 * <b><i>pIMEIStr</i></b> and returns it in <b><i>pDK</i></b>.
 * @param pIMEIStr [in] IMEI number (14 digits + null termination).
 * @param pDK [out] Pre-allocated buffer that will contain the device key.
 * If the buffer is too small you will get a #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, and <b><i>pDKLength</i></b>
 * will be set to the expected buffer size.
 * @param pDKLength [in/out] As input parameter this is the length of the buffer. A buffer length
 * of at least 16 bytes is recommended. As output parameter this is the actual length of the device key returned.
 * @param handleIndex [in] Handle index recieved from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 * \deprecated Use the SECS::SGN_GetSecurityPropertiesWithSmk function instead.
 */
SECS_API unsigned int SGN_GenerateDeviceKey(
  const char* pIMEIStr,
  unsigned char* pDK,
  unsigned int* pDKLength,
  unsigned int handleIndex);

/**
 * Generates a <b><i>numBits</i></b> bit device key based on the SMK <b><i>pSmkName</i></b> for the IMEI number
 * <b><i>pIMEIStr</i></b> and returns it in <b><i>deviceKeyBuf</i></b>.
 * @param pSmkName [in] The requested Super Master Key (SMK) as a null terminated
 * string (case sensitive). If set to NULL, the default SMK will be used.
 * @param numBits [in] The requested number of bits in the device key. Please note that only values between 1 and 160 are valid.
 * If the specified number of bits is not evenly divisible by 8, the resulting device key will be contained
 * in the first <b><i>numBits</i></b> bits of <b><i>deviceKeyBuf</i></b>, and the unused bits at the end of the
 * last byte will be set to 0.
 * @param pIMEIStr [in] IMEI number (14 digits + null termination).
 * @param pDKBuf [out] Pre-allocated buffer that will contain the device key.
 * If the buffer is too small you will get a #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, and <b><i>deviceKeyBufLen</i></b>
 * will be set to the expected buffer size.
 * @param pDKBufLen [in/out] As input parameter this is the length (in bytes) of the buffer.
 * As output parameter this is the actual length (in bytes) of the device key returned.
 * @param handleIndex [in] Handle index recieved from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 * \deprecated Use the SECS::SGN_GetSecurityPropertiesWithSmk function instead.
 */
SECS_API unsigned int SGN_GenerateDeviceKey_v2(
  const char* pSmkName,
  unsigned int numBits,
  const char* pIMEIStr,
  unsigned char* pDKBuf,
  unsigned int* pDKBufLen,
  unsigned int handleIndex);

/**
 * Create a Simlock signature TA for TI.
 * @param pResultBuffer [out] Result buffer that contains simlock signature.
 * @param pResultLen [out] Result Length.
 * @param pResultTaMepd [out] TA MEPD data.
 * @param pResultTaMepdLen [out] TA MEPD data length.
 * @param pGdfFileBuffer [in] Input GDFS data i.e simlock.gdf in a buffer.
 * @param GdfBufferLength [in] Gdf buffer length.
 * @param CodeCount [in] Number of used KeyCodes (e.g. 5 or 12 or ...).
 * @param pKeyBuffer [out] KeyCode strings (each string 16 digits).
 * @param pIMEIStr [in] IMEI (14 digits + null termination).
 * @param pDeviceKeyStr [in] Device id.
 * @param ProdMode [in] Production Mode.
 * @param handleIndex [in] Handle index recieved from SECS::SGN_GetHandle() or SECS::SGN_GetExtHandle().
 * @return SECS::T_SECSErrorCodesExp
 * \deprecated Reason unknown.
 */

SECS_API unsigned int SGN_SimlockSignatureTA(unsigned char *pResultBuffer,
                       unsigned int *pResultLen,
                       unsigned char* pResultTaMepd,
                       unsigned int* pResultTaMepdLen,
                       const unsigned char *pGdfFileBuffer,
                       unsigned int GdfBufferLength,
                       int CodeCount,
                       unsigned char *pKeyBuffer,
                       const char *pIMEIStr,
                       const char* pDeviceKeyStr,
                       T_SGN_ProdModeType ProdMode,
                       unsigned int handleIndex);

/**
 * Create a Simlock signature TA for A2.
 * @param pResultBuffer [out] Result buffer contains simlock signature.
 * @param pResultLen [out] Result Length.
 * @param pGdfFileBuffer [in] Input GDFS data i.e simlock.gdf in a buffer.
 * @param GdfBufferLength [in] Gdf buffer length.
 * @param CodeCount [in] Number of used KeyCodes (e.g. 5 or 12 or ...).
 * @param pKeyBuffer [out] KeyCode strings (each string 16 digits).
 * @param pIMEIStr [in] IMEI (14 digits + null termination).
 * @param ProdMode [in] Production Mode.
 * @param handleIndex [in] Handle index recieved from SECS::SGN_GetHandle() or SECS::SGN_GetExtHandle().
 * @return SECS::T_SECSErrorCodesExp
 * \deprecated Reason unknown.
 */

SECS_API unsigned int SGN_SimlockSignatureTAA2(unsigned char *pResultBuffer,
                         unsigned int *pResultLen,
                         const unsigned char *pGdfFileBuffer,
                         unsigned int GdfBufferLength,
                         int CodeCount,
                         unsigned char *pKeyBuffer,
                         const char *pIMEIStr,
                         T_SGN_ProdModeType ProdMode,
                         unsigned int handleIndex);

/**
 * Verifies a Simlock signature using units read from ME (<b><i>pGdfsCurrentUnits</i></b>)
 * and returns SECS_SUCCESS if successful, otherwise an error code is returned.
 * @param pGdfsCurrentUnits [in/out] Pointer to first item in an array of current GDFSUnits.
 * Note: Sequence {6:0, 14:0, 28:0, 2128:1, 2129:1=(Current GDFSSignature)}
 * @param currentUnitCount [in/out] Number of GDFS units used.
 * @param pIMEIStr [in] IMEI str (14 digits + null termination)
 * @param prodMode [in] Production Mode
 * @param handleIndex [in] Handle index recieved from SGN_GetHandle() or SGN_GetExtHandle()
 * @return #T_SECSErrorCodesExp
 * \deprecated No longer in use.
 */
SECS_API unsigned int SGN_VerifySimlockSignature(
  T_SECS_GDFSUnitData *pGdfsCurrentUnits,
  unsigned int currentUnitCount,
  const char *pIMEIStr,
  T_SGN_ProdModeType prodMode,
  unsigned int handleIndex);

/**
 * Verify a Simlock signature using units reads from ME (<b><i>pGdfsCurrentUnits</i></b>)
 * and returns SECS_SUCCESS if successful, otherwise an error code is returned.<br><br>
 * \attention This function calls a function on the server that is not completely implemented.
 * Either complete the implementation or remove this function!
 * @param pGdfsCurrentUnits [in/out] Pointer to first item in an array of current GDFSUnits.
 * Note: Sequence {6:0, 14:0, 28:0, 2128:1, 2129:1=(Current GDFSSignature)}
 * @param currentUnitCount [in/out] Number of GDFS units used.
 * @param pIMEIstr [in] IMEI str (14 digits + null termination)
 * @param prodMode [in] Production Mode
 * @param pDeviceKeyStr [in] Device Id
 * @param handleIndex [in] Handle index recieved from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 * \deprecated No longer in use.
 */
SECS_API unsigned int SGN_VerifySimlockSignatureTA(
  T_SECS_GDFSUnitData *pGdfsCurrentUnits,
  unsigned int currentUnitCount,
  const char *pIMEIstr,
  const char* pDeviceKeyStr,
  T_SGN_ProdModeType prodMode,
  unsigned int handleIndex);

/**
 * @return SECS::T_SECSErrorCodesExp
 * \deprecated No longer supported by the SECS API, will return SECS_ERROR_DEPRECATED if called.
 */

SECS_API unsigned int SGN_GetCID(
  unsigned short *pCID,
  const char *pIMEIStr,
  unsigned int handleIndex);


/**
 * @return SECS::T_SECSErrorCodesExp
 * \deprecated No longer supported by the SECS API, will return SECS_ERROR_DEPRECATED if called.
 */

SECS_API unsigned int SGN_SendSMS(const char *SmsText, unsigned int handleIndex);


/**
 * @return SECS::T_SECSErrorCodesExp
 * \deprecated This function will return SECS_ERROR_DEPRECATED if called. Use SEMCSC to sign a01 files instead.
 */

SECS_API unsigned int SGN_EromCertSignature(
  char *pA01FileName,
  char *pResultFile,
  int CCount,
  char *pCTags[],
  int CType,
  unsigned int handleIndex);


/**
 * @return SECS::T_SECSErrorCodesExp
 * \deprecated Returns SECS_ERROR_DEPRECATED if called.
 */

SECS_API unsigned int SGN_VerifyEromImage(
  char *FileName,
  char *paVerifyResult[],
  char *paVerifyRootResult[],
  unsigned int handleIndex);


/**
 * @return SECS::T_SECSErrorCodesExp
 * \deprecated This function returns SECS_ERROR_DEPRECATED if called. CROD messages are no longer supported by the SECS API.
 */

SECS_API unsigned int SGN_CRODMessage(
  unsigned char *pMsgBuffer,
  int *pMsgLen,
  char *pCTags[],
  int CType,
  int TCount,
  char *pTTags[],
  int TType,
  int PType,
  int CrodCmd,
  unsigned int handleIndex);


/**
 * @return SECS::T_SECSErrorCodesExp
 * \deprecated This function will return SECS_ERROR_DEPRECATED if called.
 */
 
SECS_API unsigned int SGN_SignImage(T_SGN_SignTypes SignType,
                  unsigned char *pInput,
                  unsigned int InputSize,
                  unsigned char **pResultBuffer,
                  unsigned int *ResultSize,
                  int CCount,
                  char *pCTags[],
                  int CType,
                  char *pSSWCTag,
                  int CSSWType,
                  bool sha1_only,
                  bool tail_only,
                  bool DoPad0,
                  unsigned int handleIndex);


/**
  * Sends echo to the server with handle index <b><i>handleIndex</i></b> and returns SECS_SUCCESS
  * if a reply is received, otherwise an error code is returned.
  * @param handleIndex [in] Handle index received from SECS::SGN_GetHandle() or SECS::SGN_GetExtHandle().
  * @return SECS::T_SECSErrorCodesExp
  * \deprecated Use SECS::SGN_CheckServer_v2() instead.
  */

SECS_API unsigned int SGN_CheckServer(unsigned int handleIndex);


/**
 * Create a Simlock signature in the Customer service flow.
 * @param pGdfsCurrentUnits [in] Result buffer contains simlock signature.
 * @param CurrentUnitCount [in] Result length.
 * @param pGdfsNewUnits [out] Pointer to first item in an array of current GDFSUnits.
 * Note: Sequence {6:0, 14:0, 28:0, 2026:0, 2027:0, 2028:0, 2126:1, 2127:1, 2128:1, 2129:1}
 * @param NewUnitCount [out] Number of GDFS units used.
 * @param pIMEIStr [in] IMEI (14 digits + null termination).
 * @param handleIndex [in] Handle index recieved from SECS::SGN_GetHandle() or SECS::SGN_GetExtHandle().
 * @return SECS::T_SECSErrorCodesExp
 * \deprecated Use SECS::SGN_SimlockCSSignature_v2() instead.
 */

SECS_API unsigned int SGN_SimlockCSSignature(const T_SECS_GDFSUnitData *pGdfsCurrentUnits,
                       unsigned int CurrentUnitCount,
                       T_SECS_GDFSUnitData *pGdfsNewUnits,
                       unsigned int NewUnitCount,
                       const char *pIMEIStr,
                       unsigned int handleIndex);


/**
 * Gets data from first step in a P22 sequence
 * @param KeyType [in] The key type.
 * @param pStepOneData [out] Data from step one
 * @param pStepOneLength [out] Length of data
 * @param pIMEIStr [in] IMEI (14 digits + null termination).
 * @param handleIndex [in] Handle index recieved from SECS::GetHandle() or SECS::GetExtHandle().
 * @return SECS::T_SECSErrorCodesExp
 * \deprecated Use SECS::SGN_GetStepOneData_v2() instead.
 */
SECS_API unsigned int SGN_GetStepOneData(
  T_SGN_KeyType KeyType,
  unsigned char *pStepOneData,
  unsigned int *pStepOneLength,
  const char* pIMEIStr,
  unsigned int handleIndex );

/**
 * Returns key id and key name for all rows the keystore database where key type is <b><i>KeyType</i></b>
 * in <b><i>pOutputString</i></b>.
 * @param pOutputstring [out] Pre-allocated buffer that will contain a list of keystore content on the form <b>key_id:key_name</b> as a "," separated string.
 * @param pOutputStringLen [in/out] As input parameter this is length of allocated buffer.
 * As output parameter this is the actual length of the keystore content returned.
   * @param KeyStoreType [in] key store type. Possible values are:
 * - _CERT
 * - _PIN
 * - _TAC
 * - _P22
 * - _CFG
 * - _ROOT
 * - _SLF
 * - _DEVICE
 * - _CERTTYPE
 * @param handleIndex [in] Handle index recieved from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 * \note This function may under certain circumstances return a non-null terminated string.
 * \deprecated Not supported by the SECS API anymore.
*/
SECS_API unsigned int SGN_DoListKeystoreByKeyType(
  char *pOutputstring,
  unsigned int *pOutputStringLen,
  T_SGN_KeyStoreTypes KeyStoreType,
  unsigned int handleIndex);

/**
 * Returns a CS status string in <b><i>StatusString</i></b> on the
 * format "x of y", where x is the number of used credits and y is the number of
 * available credits for a certain period of time.<br>
 * Used by: CS.
 * @param StatusString [out] Pre-allocated string buffer that will contain the status string.
 * @param StatusStringLength [in] Length of allocated result buffer. A buffer length of at least 10 bytes is recommended.
 * @param handleIndex        [in] Handle index recieved from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 * \deprecated SECS no longer supports quota. This function returns SECS_ERROR_DEPRECATED if called.
 */
SECS_API unsigned int SGN_CSUserStatus(
  char *StatusString,
  unsigned int StatusStringLength,
  unsigned int handleIndex);

/**
 * Returns a comma separated list of all P22 and P96 keys available in the keystore database in <b><i>KIDbuf</i></b>.
 * @param pKIDbuf [out] Pre-allocated buffer that will contain the comma separated list of keys.
 * Each key is on the format key_id:key_name, e.g. 12:KID1.
 * If the buffer is too small you will get a ::SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error.
 * @param KIDbuflen [in] The size of the buffer.
 * @param handleIndex [in] Handle index recieved from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_ListKIDs(
  char *pKIDbuf,
  int KIDbuflen,
  unsigned int handleIndex);

/**
 * Returns all signature types in <b><i>pOutputstring</i></b>.
 * @param pOutputstring [out] A pre-allocated buffer that will contain a list of signature types in a "," separated string on format "n : SIGNTYPE"
 * @param pOutputStringLen [in/out] As input parameter this is the length of the pre-allocated buffer.
 * As output parameter this is the actual length of the buffer returned.
 * @param handleIndex [in] Handle index recieved from SGN_GetHandle() or SGN_GetExtHandle().
 * \deprecated This function will return SECS_ERROR_DEPRECATED if called.
 */
SECS_API unsigned int SGN_DoListSignTypes(
  char *pOutputstring,
  unsigned int *pOutputStringLen,
  unsigned int handleIndex);

/**
 * Releases the memory pointed to by <b><i>pMem</i></b>.
 * @param pMem [in] Pointer to memory allocated in other DLL's
 * @param handleIndex [in] Handle index recieved from SGN_GetHandle() or SGN_GetExtHandle().
 * \deprecated This function will return SECS_ERROR_DEPRECATED if called.
 */
SECS_API unsigned int SGN_ReleaseBufferMemory(
  void *pMem,
  unsigned int handleIndex);

/**
 * This function determines the status of a dongle <b><i>dongleId</i></b>, similar to SGN_IsActiveDongle(),
 * and returns the result in <b><i>pResult</i></b>.
 * @param pDongleId [in] The id of the dongle.
 * @param pStatus [out] Will contain one of the following four different statuses:
 *                      0: the dongle is unknown (doesn't exist in the database)
 *                      1: the dongle is active
 *                      2: the dongle has expired (see pTimespan)
 *                      3: the dongle has been manually blocked
 * @param pTimeSpan [out] Pre-allocated buffer which should receive the active timespan in all successful
 *                        cases except when dongle is unknown. The returned time span is on the
 *                        form YYYY-MM-DD hh:mm:ss -- YYYY-MM-DD hh:mm:ss and is a null terminated string.
 * @param pTimeSpanLen [in/out] Length of the preallocated buffer pTimeSpan. Should be at least 43 bytes.
 *                              If the buffer is too small you will get a #SGN_SGNTOOL_EXCEEDS_BUFFER error,
 *                              and <b><i>pTimeSpanLen</i></b> will be set to the expected buffer size.
 * @param handleIndex [in] Handle index recieved from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 */
SECS_API unsigned int SGN_GetDongleStatus(
  const char* pDongleId,
  unsigned int* pStatus,
  char* pTimeSpan,
  unsigned int* pTimeSpanLen,
  unsigned int handleIndex);

/**
 * Returns a signed Remote Lock for S1 in state _NOT_LOCKABLE.
 * @param prodMode [in] Production Mode
 * @param pIMEIStr [in] An ASCII string with the IMEI number (14 digits + null termination)
 * @param pVersionResponse [in] Version response string from device. The S1_ROOT tag is used to derive the proper signing cert to create a SIN image.
 * @param pResBuf [out] A buffer where the result will be put. If the buffer is too small you will get a
 * #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, and <b><i>pResLen</i></b> will be set to the expected buffer size.
 * @param pResLen [in/out] Size of pResBuf. This will be set to the size of the result before returning.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 * \deprecated Use the SECS::SGN_GetSignedRemoteLockWithState function instead.
 */
SECS_API unsigned int SGN_GetSignedRemoteLock(
  T_SGN_ProdModeType prodMode,
  const char* pIMEIStr,
  const char* pVersionResponse,
  unsigned char* pResBuf,
  unsigned int* pResLen,
  unsigned int handleIndex);

/**
 * Returns a signed Remote Lock for S1 in state LOCKED.
 * @param prodMode [in] Production Mode
 * @param pIMEIStr [in] An ASCII string with the IMEI number (14 digits + null termination)
 * @param pVersionResponse [in] Version response string from device. The S1_ROOT tag is used to derive the proper signing cert to create a SIN image.
 * @param pPassphrase [in] User selected plain-text passphrase as a null terminated string.
 * @param pResBuf [out] A buffer where the result will be put. If the buffer is too small you will get a
 * #SGN_SGNTOOL_TOCRYPTO_EXCEEDS_BUFFER error, and <b><i>pResLen</i></b> will be set to the expected buffer size.
 * @param pResLen [in/out] Size of pResBuf. This will be set to the size of the result before returning.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 * \deprecated This function will return SECS_ERROR_DEPRECATED if called. Use the SECS::SGN_GetSignedRemoteLockWithState function instead.
 */
SECS_API unsigned int SGN_GetSignedLockedRemoteLock(
  T_SGN_ProdModeType prodMode,
  const char* pIMEIStr,
  const char* pVersionResponse,
  const char* pPassphrase,
  unsigned char* pResBuf,
  unsigned int* pResLen,
  unsigned int handleIndex);

/**
 * Sets the connection timeout to <b><i>timeout</i></b> for the opened handle <b><i>handleIndex</i></b>.
 * @param timeout [in] Timeout in seconds.
 * @param handleIndex [in] Handle index received from SGN_GetHandle() or SGN_GetExtHandle().
 * @return #T_SECSErrorCodesExp
 * \deprecated Use the SECS::SGN_SetConnectionTimout function instead.
 */
SECS_API unsigned int SGN_SetConnectionOptions(
  unsigned int timeout,
  unsigned int handleIndex);

/*@}*/

#endif // INCLUSION_GUARD
