/**
@file     UFS.h
@brief   Universal Flash Storage (UFS) DXE Header File

This file contains the definitions of the constants, data structures,
and interfaces for the UFS driver in UEFI.

 Copyright (c) 2013 - 2018, 2021-2022 Qualcomm Technologies, Inc. All rights reserved.
**/

/*=============================================================================
                              EDIT HISTORY


when            who   what, where, why
----------      ---   -----------------------------------------------------------
2022-05-09      sa    Added SharedIce Support.
2022-03-21      cm    Add API to return turbo mode support info
2021-04-28      jt    Add ICE support 
2020-03-31      jt    Add power management functions
2018-06-04      jt    Add clock macros 
2017-02-01      jt    Add read/write wrapper definitions
2016-09-21      jt    Secure write protect changes  
2016-06-28      jt    Add get/set boot LUN APIs  
2016-01-21      rh    Adding BlockIO2 
2015-03-26      rm    Add RPMB protocol and GUID
09-23-2014      rh    Use unique GUID for LUs, different from eMMC
05-05-2013      ai    Initial version

=============================================================================*/

#ifndef _UFS_H_
#define _UFS_H_

/** @name UFS Device Signature
      Signature as per UEFI requirement.
  */
/*@{*/
#define UFS_DEV_SIGNATURE SIGNATURE_32 ('u', 'f', 's', ' ')   /**< -- UFS  */
/*@}*/

#define UFS_UEFI_MAX_LUN_ACCESS              8

#define UFS_CLK_OFF   0

/**
  UFS Device Structure
  */
typedef struct {
  UINT32                        Signature;
  EFI_HANDLE                    ClientHandle;  /**< -- Client Handle */
  EFI_HANDLE                    DeviceHandle;  /**< -- Device Handle */
  EFI_BLOCK_IO_PROTOCOL         BlkIo;         /**< -- Block I/O */
  EFI_BLOCK_IO_CRYPTO_PROTOCOL  BlkIoCrypto;   /**< -- Block I/O Crypto */
  EFI_BLOCK_IO2_PROTOCOL        BlkIo2;        /**< -- Block I/O 2 */
  EFI_SDCC_RPMB_PROTOCOL        RPMB;          /**< -- RPMB protocol */
  EFI_MEM_CARDINFO_PROTOCOL     CardInfo;      /**< -- Memory card into */
  EFI_ERASE_BLOCK_PROTOCOL      EraseBlk;      /**< -- Erase block */
  EFI_STORAGE_WP_PROTOCOL       WriteProtect;  /**< -- Write Protect */
  EFI_STORAGE_DEV_MGMT_PROTOCOL DeviceMgmt;    /**< -- Device Management */
} UFS_DEV;


/**
   Reset the Block Device.
   
   @param  This                 Indicates a pointer to the calling context.
   @param  ExtendedVerification Driver may perform diagnostics on reset.
   
   @retval EFI_SUCCESS          The device was reset.
   @retval EFI_DEVICE_ERROR     The device is not functioning properly
                                and could not be reset.

**/
EFI_STATUS EFIAPI UFSReset (
   IN EFI_BLOCK_IO_PROTOCOL   *This,
   IN BOOLEAN                 ExtendedVerification
   );


/**
   Read BufferSize bytes from Lba into Buffer.
   
   @param  This          Indicates a pointer to the calling
                         context.
   @param  MediaId       Id of the media, changes every time the
                         media is replaced.
   @param  Lba           The starting Logical Block Address to
                         read from
   @param  BufferSize    Size of Buffer, must be a multiple of
                         device block size.
   @param  Buffer        A pointer to the destination buffer for
                         the data. The caller is responsible for
                         either having implicit or explicit
                         ownership of the buffer.
   @param  CryptoIndex   A pointer to the configuration table 
                         index.
   @param  CryptoIvInput A pointer to a buffer that contains 
                         additional cryptographic parameters.
   
   @retval EFI_SUCCESS           The data was read correctly from the device.
   @retval EFI_DEVICE_ERROR      The device reported an error while
                                 performing the read.
   @retval EFI_NO_MEDIA          There is no media in the device.
   @retval EFI_MEDIA_CHANGED     The MediaId does not matched the
                                 current device.
   @retval EFI_BAD_BUFFER_SIZE   The Buffer was not a multiple of the block
                                 size of the device.
   @retval EFI_INVALID_PARAMETER The read request contains LBAs that are not
                                 valid,or the buffer is not on proper alignment.
**/
EFI_STATUS EFIAPI UFSReadBlocks (
   IN VOID                    *This,
   IN UINT32                  MediaId,
   IN EFI_LBA                 Lba,
   IN UINT64                  BufferSize,
   OUT VOID                   *Buffer, 
   IN UINT64                  *CryptoIndex, 
   IN VOID                    *CryptoIvInput
   );

/**
   Write BufferSize bytes from Lba into Buffer.
   
   @param  This          Indicates a pointer to the calling 
                         context.
   @param  MediaId       The media ID that the write request is
                         for.
   @param  Lba           The starting logical block address to 
                         be written. The caller is responsible
                         for writing to only legitimate
                         locations.
   @param  BufferSize    Size of Buffer, must be a multiple of 
                         device block size.
   @param  Buffer        A pointer to the source buffer for the
                         data.
   @param  CryptoIndex   A pointer to the configuration table 
                         index.
   @param  CryptoIvInput A pointer to a buffer that contains 
                         additional cryptographic parameters.
   
   @retval EFI_SUCCESS           The data was written correctly to the device.
   @retval EFI_WRITE_PROTECTED   The device can not be written to.
   @retval EFI_DEVICE_ERROR      The device reported an error 
                                 while performing the write.
   @retval EFI_NO_MEDIA          There is no media in the device.
   @retval EFI_MEDIA_CHNAGED     The MediaId does not matched 
                                 the current device.
   @retval EFI_BAD_BUFFER_SIZE   The Buffer was not a multiple 
                                 of the block size of the device.
   @retval EFI_INVALID_PARAMETER The write request contains LBAs that are not
                                 valid or the buffer is not on proper
                                 alignment.
**/ 
EFI_STATUS EFIAPI UFSWriteBlocks (
    IN VOID                    *This,
   IN UINT32                  MediaId,
   IN EFI_LBA                 Lba,
    IN UINT64                   BufferSize,
    IN VOID                    *Buffer,
    IN UINT64                  *CryptoIndex, 
    IN VOID                    *CryptoIvInput
   );

/**
   Flush the Block Device.
   
   @param  This              Indicates a pointer to the calling context.
   
   @retval EFI_SUCCESS       All outstanding data was written to the device
   @retval EFI_DEVICE_ERROR  The device reported an error while 
                             writting back the data
   @retval EFI_NO_MEDIA      There is no media in the device.

**/
EFI_STATUS EFIAPI UFSFlushBlocks (
   IN EFI_BLOCK_IO_PROTOCOL  *This
   );

/**
   Function: RPMBReadCounterPkt
 
   This function retrieves Read Counter Response packet from flash device.
   The Response packet includes the Write Counter as well as the MAC which
   is used later to validate the Response packet
  
   @param  RespPktBuffer [OUT]    Pointer to the response from the Read
                                  Counter command
    
   @retval  RPMB_NO_ERROR           Successfully read the Counter packet.
   @retval  RPMB_ERR_INVALID_PARAM  NULL pointer is passed in to the function.
   @retval  RPMB_ERR_READ           Failed to read the Counter packet.
**/
INT32 
EFIAPI
RPMBReadCounterPkt (
   EFI_SDCC_RPMB_PROTOCOL       *This,
   UINT32                       *RespPktBuffer
   );

/**
 Function: RPMBProgProvisionKey
 
 This function programs the eMMC's key using the provided packet
 formatted as ProvisionKey command. 

 @param CmdPktBuffer  [IN] : Pointer to a ProvisionKey command packet
                             to be sent to eMMC to program its key
 @param RespPktBuffer [OUT]: Pointer to the response packet for the
                             ProvisionKey command
 
 @retval  RPMB_NO_ERROR            Successfully provision the eMMC's Key.
 @retval  RPMB_ERR_INVALID_PARAM   NULL pointer is passed in to the function.
 @retval  RPMB_ERR_GENERAL         Failed to provision the key (Key has been
                                   provisioned).
  
**/
INT32 
EFIAPI
RPMBProgProvisionKey (
   EFI_SDCC_RPMB_PROTOCOL       *This,
   UINT32                       *CmdPktBuffer,
   UINT32                       *RespPktBuffer 
   );

/**
  Function: RPMBReadBlocks
 
  This function reads the sectors from RPMB partition using the
  cmd packet buffers provided.
 
  @param   CmdPktBuffer  [IN] : Pointer to a formatted packet for Read Request 
  @param   PktCount      [IN] : How many half sectors to read   
  @param   DataBuffer    [OUT]: Pointer to data read from eMMC
 
  @retval  RPMB_NO_ERROR            Successfully read the Counter packet
  @retval  RPMB_ERR_INVALID_PARAM   NULL pointer is passed in to the function
  @retval  RPMB_ERR_READ            Failed to read the sectors
     
**/ 
INT32 
EFIAPI
RPMBReadBlocks (
   EFI_SDCC_RPMB_PROTOCOL       *This,
   UINT32                       *CmdPktBuffer,
   UINT32                       PktCount,
   UINT32                       *DataBuffer
   );  

/**
  Function: RPMBWriteBlocks
 
  This function writes the sectors to the RPMB partition using
  the provided cmd packet buffers
                       
  @param  CmdPktBuffer  [IN] :  Pointer to a formatted packets to be sent
                                to eMMC to write to RPMB partition
  @param  PktCount      [IN] :  Number of half sectors to write
  @param  RespPktBuffer [OUT]:  Pointer to the response packet from eMMC
 
  @retval  RPMB_NO_ERROR            Successfully Write the RPMB sectors.
                                    Caller should authenticate the Response
                                    packet and validate the Write Counter
  @retval  RPMB_ERR_INVALID_PARAM   NULL pointer is passed in to the function
  @retval  RPMB_ERR_WRITE           Failed to write the sectors
  
**/
INT32 
EFIAPI
RPMBWriteBlocks (
   EFI_SDCC_RPMB_PROTOCOL       *This,
   UINT32                       *CmdPktBuffer,
   UINT32                       PktCount,
   UINT32                       *RespPktBuffer 
   );

/**
  Function: UFSGetCardInfo
 
   This function retrieves the card information. 
  
   @param  card_info              Pointer to a UFS_CARD_INFO variable 
                                  that is used to store the retrieved
                                  card information
    
   @retval EFI_SUCCESS            The function completed successfully. 
   @retval EFI_INVALID_PARAMETER  The pass-in parameter is invalid.
**/
EFI_STATUS EFIAPI UFSGetCardInfo (
   EFI_MEM_CARDINFO_PROTOCOL   *This,
   MEM_CARD_INFO*              card_info
   );

/**
  Function: UFSCryptoReset
 
  Reset the block device hardware.
  
   @param  This                 Indicates a pointer to the calling context.
   @param  ExtendedVerification Indicates that the driver may perform a more exhaustive
                                verification operation during reset.
    
   @retval EFI_SUCCESS            The function completed successfully. 
   @retval EFI_DEVICE_ERROR       The block device could not be reset. 
   @retval EFI_INVALID_PARAMETER  The pass-in parameter is invalid.
**/
EFI_STATUS EFIAPI UFSCryptoReset (
    IN EFI_BLOCK_IO_CRYPTO_PROTOCOL   *This,
    IN BOOLEAN                        ExtendedVerification
    );

/**
  Function: UFSCryptoGetCapabilities
 
  Get the capabilities of the inline cryptographic engine.
  
   @param  This           Indicates a pointer to the calling context.
   @param  Capabilities   Indicates a pointer to the capabilities structure. 
    
   @retval EFI_SUCCESS            The function completed successfully. 
   @retval EFI_BUFFER_TOO_SMALL   The Capabilities structure was too small. 
   @retval EFI_DEVICE_ERROR       An error occurred when accessing the crypto engine. 
   @retval EFI_INVALID_PARAMETER  The pass-in parameter is invalid.
**/
EFI_STATUS EFIAPI UFSCryptoGetCapabilities (
    IN EFI_BLOCK_IO_CRYPTO_PROTOCOL      *This,
    OUT EFI_BLOCK_IO_CRYPTO_CAPABILITIES *Capabilities
    );

/**
  Function: UFSCryptoSetConfiguration
 
  Sets the configuration of the inline cryptographic engine.
  
   @param  This                 Indicates a pointer to the calling context.
   @param  ConfigurationCount   Number of entries to be configured. 
   @param  ConfigurationTable   Pointer to the configuration table.
   @param  ResultingTable       Optional pointer to the newly configured table. 
    
   @retval EFI_SUCCESS            The function completed successfully. 
   @retval EFI_DEVICE_ERROR       An error occurred when accessing the crypto enginer. 
   @retval EFI_INVALID_PARAMETER  The pass-in parameter is invalid.
   @retval EFI_OUT_OF_RESOURCES   The requested number of entries are not available
**/
EFI_STATUS EFIAPI UFSCryptoSetConfiguration (
    IN EFI_BLOCK_IO_CRYPTO_PROTOCOL                      *This,
    IN UINT64                                            ConfigurationCount, 
    IN EFI_BLOCK_IO_CRYPTO_CONFIGURATION_TABLE_ENTRY     *ConfigurationTable, 
    OUT EFI_BLOCK_IO_CRYPTO_RESPONSE_CONFIGURATION_ENTRY *ResultingTable
    );

/**
  Function: UFSCryptoGetConfiguration
 
  Gets the configuration of the inline cryptographic engine.
  
   @param  This                 Indicates a pointer to the calling context.
   @param  StartIndex           Table index to start the configuration. 
   @param  ConfigurationCount   Number of entries to configure.
   @param  KeyOwnerGuid         Optional parameter to filter entries for a specific owner. 
   @param  ConfigurationTable   Pointer to a table of configured table entries 
                                (table index, owner guid, capability) 
    
   @retval EFI_SUCCESS            The function completed successfully. 
   @retval EFI_DEVICE_ERROR       An error occurred when accessing the crypto enginer. 
   @retval EFI_INVALID_PARAMETER  The pass-in parameter is invalid.
**/
EFI_STATUS EFIAPI UFSCryptoGetConfiguration (	
    IN EFI_BLOCK_IO_CRYPTO_PROTOCOL                      *This,
    IN UINT64                                            StartIndex,
    IN UINT64                                            ConfigurationCount, 
    IN EFI_GUID                                          *KeyOwnerGuid, 
    OUT EFI_BLOCK_IO_CRYPTO_RESPONSE_CONFIGURATION_ENTRY *ConfigurationTable
    );

/**
  Function: UFSCryptoReadEx
 
  Read BufferSize bytes from Lba into Buffer, decrypting them inline if needed. 
  
   @param  This            Indicates a pointer to the calling context.
   @param  MediaId         Id of the media, changes every time the media is replaced.
   @param  Lba             The starting Logical Block Address to read from.
   @param  Token           A pointer to a token associated with the transaction. 
   @param  BufferSize      Size of Buffer, must be a multiple of device block size.
   @param  Buffer          A pointer to the destination buffer for the data.
   @param  Index           A pointer to the configuration table index. 
   @param  CryptoIvInput   A pointer to a buffer that contains additional cryptographic parameters.

   @retval EFI_SUCCESS           The data was read correctly from the device.
   @retval EFI_DEVICE_ERROR      The device reported an error while performing the read and/or
                                 decrypting the data.
   @retval EFI_NO_MEDIA          There is no media in the device.
   @retval EFI_MEDIA_CHANGED     The MediaId does not match the current device.
   @retval EFI_BAD_BUFFER_SIZE   The Buffer was not a multiple of the block size of the device.
   @retval EFI_INVALID_PARAMETER The read request contains LBAs that are not 
                                 valid, or the buffer is not on proper alignment.
**/
EFI_STATUS UFSCryptoReadEx (
    IN EFI_BLOCK_IO_CRYPTO_PROTOCOL  *This,
    IN UINT32                        MediaId,
    IN EFI_LBA                       Lba,
    IN OUT EFI_BLOCK_IO_CRYPTO_TOKEN *Token, 
    IN UINT64                        BufferSize,
    OUT VOID                         *Buffer, 
    IN UINT64                        *Index, 
    IN VOID                          *CryptoIvInput
    );

/**
  Function: UFSCryptoWriteEx
 
  Optionally encrypts Buffer inline and writes BufferSize bytes to Lba.
  
   @param  This            Indicates a pointer to the calling context.
   @param  MediaId         Id of the media, changes every time the media is replaced.
   @param  Lba             The starting Logical Block Address to write to.
   @param  Token           A pointer to a token associated with the transaction. 
   @param  BufferSize      Size of Buffer, must be a multiple of device block size.
   @param  Buffer          A pointer to the source buffer for the data.
   @param  Index           A pointer to the configuration table index. 
   @param  CryptoIvInput   A pointer to a buffer that contains additional cryptographic parameters.

   @retval EFI_SUCCESS           The data was written correctly to the device.
   @retval EFI_WRITE_PROTECTED   The device can not be written to.
   @retval EFI_DEVICE_ERROR      The device reported an error while performing the write or 
                                 encrypting blocks.
   @retval EFI_NO_MEDIA          There is no media in the device.
   @retval EFI_MEDIA_CHNAGED     The MediaId does not match the current device.
   @retval EFI_BAD_BUFFER_SIZE   The Buffer was not a multiple of the block size of the device.
   @retval EFI_INVALID_PARAMETER The write request contains LBAs that are not valid or the buffer 
                                 is not on proper alignment.
**/
EFI_STATUS UFSCryptoWriteEx (
    IN EFI_BLOCK_IO_CRYPTO_PROTOCOL  *This,
    IN UINT32                        MediaId, 
    IN EFI_LBA                       Lba, 
    IN OUT EFI_BLOCK_IO_CRYPTO_TOKEN *Token, 
    IN UINT64                        BufferSize,
    IN VOID                          *Buffer, 
    IN UINT64                        *Index, 
    IN VOID                          *CryptoIvInput
    );

/**
  Function: UFSCryptoFlushBlocks
 
  Flushes data to the block device. 
  
   @param  This            Indicates a pointer to the calling context.
   @param  Token           A pointer to a token associated with the transaction. 
    
   @retval EFI_SUCCESS            The function completed successfully. 
   @retval EFI_DEVICE_ERROR       An error occurred when doing the flush. 
   @return EFI_NO_MEDIA           There is no media in the device.
   @return EFI_MEDIA_CHANGED      The MediaId is not for the current media.  
   @retval EFI_INVALID_PARAMETER  The pass-in parameter is invalid.
**/
EFI_STATUS EFIAPI UFSCryptoFlushBlocks (
    IN EFI_BLOCK_IO_CRYPTO_PROTOCOL  *This, 
    IN OUT EFI_BLOCK_IO_CRYPTO_TOKEN *Token
    );

/**
   Read BufferSize bytes from Lba into Buffer.
   
   @param  This       Indicates a pointer to the calling context.
   @param  MediaId    Id of the media, changes every time the media is replaced.
   @param  Lba        The starting Logical Block Address to read from
   @param  BufferSize Size of Buffer, must be a multiple of device block size.
   @param  Buffer     A pointer to the destination buffer for the data.
                      The caller is responsible for either having implicit or
                      explicit ownership of the buffer.
   
   @retval EFI_SUCCESS           The data was read correctly from the device.
   @retval EFI_DEVICE_ERROR      The device reported an error while
                                 performing the read.
   @retval EFI_NO_MEDIA          There is no media in the device.
   @retval EFI_MEDIA_CHANGED     The MediaId does not matched the
                                 current device.
   @retval EFI_BAD_BUFFER_SIZE   The Buffer was not a multiple of the block
                                 size of the device.
   @retval EFI_INVALID_PARAMETER The read request contains LBAs that are not
                                 valid,or the buffer is not on proper alignment.
**/
EFI_STATUS UFSReadBlocksWrapper (
            IN EFI_BLOCK_IO_PROTOCOL  *This,
            IN UINT32                  MediaId,
            IN EFI_LBA                 Lba,
            IN UINTN                   BufferSize,
            OUT VOID                  *Buffer);

/**
   Write BufferSize bytes from Buffer to Lba.
   
   @param  This       Indicates a pointer to the calling context.
   @param  MediaId    The media ID that the write request is for.
   @param  Lba        The starting logical block address to be 
                      written. The   caller is responsible for
                      writing to only legitimate locations.
   @param  BufferSize Size of Buffer, must be a multiple of device block size.
   @param  Buffer     A pointer to the source buffer for the data.
   
   @retval EFI_SUCCESS           The data was written correctly to the device.
   @retval EFI_WRITE_PROTECTED   The device can not be written to.
   @retval EFI_DEVICE_ERROR      The device reported an error 
                                 while performing the write.
   @retval EFI_NO_MEDIA          There is no media in the device.
   @retval EFI_MEDIA_CHNAGED     The MediaId does not matched 
                                 the current device.
   @retval EFI_BAD_BUFFER_SIZE   The Buffer was not a multiple 
                                 of the block size of the device.
   @retval EFI_INVALID_PARAMETER The write request contains LBAs that are not
                                 valid or the buffer is not on proper
                                 alignment.
**/
EFI_STATUS UFSWriteBlocksWrapper (
            IN EFI_BLOCK_IO_PROTOCOL   *This,
            IN UINT32                  MediaId,
            IN EFI_LBA                 Lba,
            IN UINTN                   BufferSize,
            IN VOID                    *Buffer);

/**
  Read BufferSize bytes from Lba into Buffer.
  
  This function reads the requested number of blocks from the device. All the
  blocks are read, or an error is returned.
  If EFI_DEVICE_ERROR, EFI_NO_MEDIA,_or EFI_MEDIA_CHANGED is returned and
  non-blocking I/O is being used, the Event associated with this request will
  not be signaled.

  @param[in]       This       Indicates a pointer to the calling context.
  @param[in]       MediaId    Id of the media, changes every time the media is 
                              replaced.
  @param[in]       Lba        The starting Logical Block Address to read from.
  @param[in, out]  Token       A pointer to the token associated with the transaction.
  @param[in]       BufferSize Size of Buffer, must be a multiple of device block size.  
  @param[out]      Buffer     A pointer to the destination buffer for the data. The 
                              caller is responsible for either having implicit or 
                              explicit ownership of the buffer.

  @retval EFI_SUCCESS           The read request was queued if Token->Event is
                                not NULL.The data was read correctly from the
                                device if the Token->Event is NULL.
  @retval EFI_DEVICE_ERROR      The device reported an error while performing
                                the read.
  @retval EFI_NO_MEDIA          There is no media in the device.
  @retval EFI_MEDIA_CHANGED     The MediaId is not for the current media.
  @retval EFI_BAD_BUFFER_SIZE   The BufferSize parameter is not a multiple of the
                                intrinsic block size of the device.
  @retval EFI_INVALID_PARAMETER The read request contains LBAs that are not valid, 
                                or the buffer is not on proper alignment.
  @retval EFI_OUT_OF_RESOURCES  The request could not be completed due to a lack
                                of resources.
**/ 
EFI_STATUS UFSReadBlocksEx (
   IN     EFI_BLOCK_IO2_PROTOCOL *This,
   IN     UINT32                 MediaId,
   IN     EFI_LBA                Lba,
   IN OUT EFI_BLOCK_IO2_TOKEN    *Token,
   IN     UINTN                  BufferSize,
   OUT VOID                      *Buffer
   );

/**
  Write BufferSize bytes from Buffer to Lba.

  This function writes the requested number of blocks to the device. All blocks
  are written, or an error is returned.If EFI_DEVICE_ERROR, EFI_NO_MEDIA,
  EFI_WRITE_PROTECTED or EFI_MEDIA_CHANGED is returned and non-blocking I/O is
  being used, the Event associated with this request will not be signaled.

  @param[in]       This       Indicates a pointer to the calling context.
  @param[in]       MediaId    The media ID that the write request is for.
  @param[in]       Lba        The starting logical block address to be written. The
                              caller is responsible for writing to only legitimate
                              locations.
  @param[in, out]  Token      A pointer to the token associated with the transaction.
  @param[in]       BufferSize Size of Buffer, must be a multiple of device block size.
  @param[in]       Buffer     A pointer to the source buffer for the data.

  @retval EFI_SUCCESS           The write request was queued if Event is not NULL.
                                The data was written correctly to the device if
                                the Event is NULL.
  @retval EFI_WRITE_PROTECTED   The device can not be written to.
  @retval EFI_NO_MEDIA          There is no media in the device.
  @retval EFI_MEDIA_CHNAGED     The MediaId does not matched the current device.
  @retval EFI_DEVICE_ERROR      The device reported an error while performing the write.
  @retval EFI_BAD_BUFFER_SIZE   The Buffer was not a multiple of the block size of the device.
  @retval EFI_INVALID_PARAMETER The write request contains LBAs that are not valid, 
                                or the buffer is not on proper alignment.
  @retval EFI_OUT_OF_RESOURCES  The request could not be completed due to a lack
                                of resources.

**/
EFI_STATUS UFSWriteBlocksEx (
   IN     EFI_BLOCK_IO2_PROTOCOL *This,
   IN     UINT32                 MediaId,
   IN     EFI_LBA                Lba,
   IN OUT EFI_BLOCK_IO2_TOKEN    *Token,
   IN     UINTN                  BufferSize,
   OUT VOID                      *Buffer
   );

/**
  Reset the block device hardware.

  @param[in]  This                 Indicates a pointer to the calling context.
  @param[in]  ExtendedVerification Indicates that the driver may perform a more
                                   exhausive verfication operation of the device
                                   during reset.

  @retval EFI_SUCCESS          The device was reset.
  @retval EFI_DEVICE_ERROR     The device is not functioning properly and could
                               not be reset.
**/
EFI_STATUS EFIAPI UFSResetEx (
   IN EFI_BLOCK_IO2_PROTOCOL  *This,
   IN BOOLEAN                 ExtendedVerification
   );

/**
  Flush the Block Device.
 
  If EFI_DEVICE_ERROR, EFI_NO_MEDIA,_EFI_WRITE_PROTECTED or EFI_MEDIA_CHANGED
  is returned and non-blocking I/O is being used, the Event associated with
  this request will not be signaled.  

  @param[in]      This     Indicates a pointer to the calling context.
  @param[in,out]  Token    A pointer to the token associated with the transaction

  @retval EFI_SUCCESS          The flush request was queued if Event is not NULL.
                               All outstanding data was written correctly to the
                               device if the Event is NULL.
  @retval EFI_DEVICE_ERROR     The device reported an error while writting back
                               the data.
  @retval EFI_WRITE_PROTECTED  The device cannot be written to.
  @retval EFI_NO_MEDIA         There is no media in the device.
  @retval EFI_MEDIA_CHANGED    The MediaId is not for the current media.
  @retval EFI_OUT_OF_RESOURCES The request could not be completed due to a lack
                               of resources.
**/
EFI_STATUS EFIAPI UFSFlushBlocksEx (
   IN     EFI_BLOCK_IO2_PROTOCOL   *This,
   IN OUT EFI_BLOCK_IO2_TOKEN      *Token
   );

/**
  Erase blocks in the Block Device
 
  If EFI_DEVICE_ERROR, EFI_NO_MEDIA,_EFI_WRITE_PROTECTED or EFI_MEDIA_CHANGED
  is returned and non-blocking I/O is being used, the Event associated with
  this request will not be signaled.  

  @param[in]      This     Indicates a pointer to the calling context.
  @param[in,out]  Token    A pointer to the token associated with the transaction

  @retval EFI_SUCCESS          The flush request was queued if Event is not NULL.
                               All outstanding data was written correctly to the
                               device if the Event is NULL.
  @retval EFI_DEVICE_ERROR     The device reported an error while writting back
                               the data.
  @retval EFI_WRITE_PROTECTED  The device cannot be written to.
  @retval EFI_NO_MEDIA         There is no media in the device.
  @retval EFI_MEDIA_CHANGED    The MediaId is not for the current media.
  @retval EFI_OUT_OF_RESOURCES The request could not be completed due to a lack
                               of resources.
**/
EFI_STATUS EFIAPI UFSEraseBlocks (
   IN     EFI_BLOCK_IO_PROTOCOL *This,
   IN     UINT32 MediaId,
   IN     EFI_LBA LBA,
   IN OUT EFI_ERASE_BLOCK_TOKEN *Token,
   IN     UINTN Size
   );

#ifdef FEATURE_XBOOT
/**
  Erase blocks in the Block Device

  If EFI_DEVICE_ERROR, EFI_NO_MEDIA,_EFI_WRITE_PROTECTED or EFI_MEDIA_CHANGED
  is returned and non-blocking I/O is being used, the Event associated with
  this request will not be signaled.

  @param[in]      This     Indicates a pointer to the calling context.
  @param[in,out]  Token    A pointer to the token associated with the transaction

  @retval EFI_SUCCESS          The flush request was queued if Event is not NULL.
                               All outstanding data was written correctly to the
                               device if the Event is NULL.
  @retval EFI_DEVICE_ERROR     The device reported an error while writting back
                               the data.
  @retval EFI_WRITE_PROTECTED  The device cannot be written to.
  @retval EFI_NO_MEDIA         There is no media in the device.
  @retval EFI_MEDIA_CHANGED    The MediaId is not for the current media.
  @retval EFI_OUT_OF_RESOURCES The request could not be completed due to a lack
                               of resources.
**/
EFI_STATUS EFIAPI UfsNonSecureEraseBlocks (
   IN     EFI_BLOCK_IO_PROTOCOL *This,
   IN     UINT32 MediaId,
   IN     EFI_LBA LBA,
   IN     UINTN Size
   );

/**
  Purge blocks in the Block Device

  If EFI_DEVICE_ERROR, EFI_NO_MEDIA,_EFI_WRITE_PROTECTED or EFI_MEDIA_CHANGED
  is returned and non-blocking I/O is being used, the Event associated with
  this request will not be signaled.

  @param[in]      This     Indicates a pointer to the calling context.
  @param[in,out]  Token    A pointer to the token associated with the transaction

  @retval EFI_SUCCESS          The flush request was queued if Event is not NULL.
                               All outstanding data was written correctly to the
                               device if the Event is NULL.
  @retval EFI_DEVICE_ERROR     The device reported an error while writting back
                               the data.
  @retval EFI_WRITE_PROTECTED  The device cannot be written to.
  @retval EFI_NO_MEDIA         There is no media in the device.
  @retval EFI_MEDIA_CHANGED    The MediaId is not for the current media.
  @retval EFI_OUT_OF_RESOURCES The request could not be completed due to a lack
                               of resources.
**/
EFI_STATUS EFIAPI UfsPurgeBlocks (
   IN     EFI_BLOCK_IO_PROTOCOL *This,
   IN OUT EFI_ERASE_BLOCK_TOKEN *Token
   );
#endif /* FEATURE_XBOOT */

/**
  Get Active BOOT LU 

  @param[in]      This       Indicates a pointer to the calling context.
  @param[out]     BootLU     Pointer that contains the active 
                             BOOT LU (0 = disable BOOT 
                             LU, 1 = BOOT for A, 2 = BOOT for B)

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_INVALID_PARAMETER  Parameter is invalid 
**/
EFI_STATUS EFIAPI UFSGetActiveBootLU (
   IN      EFI_MEM_CARDINFO_PROTOCOL   *This,
   OUT     UINT32                      *BootLU);

/**
  Set Active BOOT LU 

  @param[in]  This      Indicates a pointer to the calling context.
  @param[in]  BootLU    LU to set as active (0 = disable BOOT 
                        LU, 1 = BOOT for A, 2 = BOOT for B)

  @retval EFI_SUCCESS             Operation completed successfully.
  @retval EFI_INVALID_PARAMETER   Parameter is invalid 
**/
EFI_STATUS EFIAPI UFSSetActiveBootLU (
   IN      EFI_MEM_CARDINFO_PROTOCOL   *This,
   IN      UINT32                      BootLU);

/**
  Gets supported LBA write protect types for the LU 

  @param[in]  This       Indicates a pointer to the calling context. 
  @param[out] LbaWpTypes LBA write protect types for the LU

  @retval EFI_SUCCESS             Operation completed successfully.
  @retval EFI_INVALID_PARAMETER   Parameter is invalid 
**/
EFI_STATUS EFIAPI UFSGetSupportedLbaWriteProtectTypes(
   IN EFI_STORAGE_WP_PROTOCOL *This, 
   OUT UINT32 *LbaWpTypes
);

/**
  Set LU write protect 

  @param[in]  This       Indicates a pointer to the calling context. 

  @retval EFI_SUCCESS             Operation completed successfully.
  @retval EFI_INVALID_PARAMETER   Parameter is invalid 
**/
EFI_STATUS EFIAPI UFSSetLUWriteProtect(
   IN EFI_STORAGE_WP_PROTOCOL *This
);

/**
  Sets LBA write protect for the given ranges

  @param[in]  This       Indicates a pointer to the calling context. 
  @param[in]  WpConfig   Pointer to the LBA ranges 

  @retval EFI_SUCCESS             Operation completed successfully.
  @retval EFI_INVALID_PARAMETER   Parameter is invalid 
**/
EFI_STATUS EFIAPI UFSSetLbaWriteProtect(
   IN EFI_STORAGE_WP_PROTOCOL *This,     
   IN EFI_WP_CONFIG *WpConfig
);

/**
  Clears secure write protect entries 

  @param[in]  This       Indicates a pointer to the calling context. 

  @retval EFI_SUCCESS             Operation completed successfully.
  @retval EFI_INVALID_PARAMETER   Parameter is invalid 
**/
EFI_STATUS EFIAPI UFSClearWriteProtect(
   IN EFI_STORAGE_WP_PROTOCOL *This
);

/**
  Gets write protection information of the LU

  @param[in]  This        Indicates a pointer to the calling context. 
  @param[out] ProtectInfo LUN Write protection information

  @retval EFI_SUCCESS             Operation completed successfully.
  @retval EFI_INVALID_PARAMETER   Parameter is invalid 
**/
EFI_STATUS EFIAPI UFSGetLUWriteProtectInfo(
   IN EFI_STORAGE_WP_PROTOCOL *This, 
   OUT EFI_WP_CONFIG *ProtectInfo
);

/**
  Gets the UFS device information 

  @param[in]  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance
  @param[out] DevInfo             Information about the UFS device information

  @retval EFI_SUCCESS             Function completed successfully.
  @retval EFI_INVALID_PARAMETER   Parameter is invalid.
  @retval EFI_OUT_OF_RESOURCES    Buffer could not be allocated.
  @retval EFI_DEVICE_ERROR        Device encountered an error getting the device information.
**/
EFI_STATUS EFIAPI UFSFillDeviceInfo (
    IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This, 
    OUT EFI_STORAGE_DEV_INFO *DevInfo
);

/**
  Gets the UFS error statistics 

  @param[in]  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance
  @param[out] ErrInfo             Information about the error statistics

  @retval EFI_SUCCESS             Function completed successfully.
  @retval EFI_INVALID_PARAMETER   Parameter is invalid.
**/
EFI_STATUS EFIAPI UFSGetErrorStats (
    IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This, 
    OUT EFI_STORAGE_ERR_STATS *ErrInfo
);

/**
  Gets the operational mode capabilities (number of gears/voltage corners) 

  @param[in]  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance
  @param[out] OpModeCaps          Information about the operational mode capabilities

  @retval EFI_SUCCESS             Function completed successfully.
  @retval EFI_INVALID_PARAMETER   Parameter is invalid.
**/
EFI_STATUS EFIAPI UFSGetOpModeCaps (
    IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This,
    OUT EFI_STORAGE_OP_MODE_CAPABILITIES *OpModeCaps
);

/**
  Gets the current UFS operational mode 

  @param[in]  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance
  @param[out] OpModeInfo          Information about the current operational mode

  @retval EFI_SUCCESS             Function completed successfully.
  @retval EFI_INVALID_PARAMETER   Parameter is invalid.
**/
EFI_STATUS EFIAPI UFSGetCurrentOpMode (
    IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This, 
    OUT EFI_STORAGE_OP_MODE_INFO *OpModeInfo
);

/**
  Sets the UFS speed (gear)

  @param[in]  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance
  @param[in]  SpeedLevel          Gear to set

  @retval EFI_SUCCESS             Speed level was set successfully.
  @retval EFI_INVALID_PARAMETER   Parameter is invalid. 
  @retval EFI_UNSUPPORTED         The speed level passed is unsupported with the current voltage corner.
  @retval EFI_DEVICE_ERROR        The speed level was not set successfully.
**/
EFI_STATUS EFIAPI UFSSetGear (
    IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This,
    IN UINT8 SpeedLevel
);

/**
  Sets the voltage corner that storage should enter

  @param[in]  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance
  @param[in]  VoltCorner          Voltage corner to enter

  @retval EFI_SUCCESS             No issues changing storage to the voltage corner.
  @retval EFI_INVALID_PARAMETER   Parameter is invalid. 
  @retval EFI_UNSUPPORTED         The voltage corner is unsupported with the current speed level.
  @retval EFI_DEVICE_ERROR        Issues were encountered while changing storage to the voltage corner.
**/
EFI_STATUS EFIAPI UFSSetVoltageCorner (
    IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This,
    IN EFI_STORAGE_VOLT_CORNER VoltCorner
);

/**
  Sets the storage operating mode (speed level + voltage corner)

  @param[in]  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance
  @param[in]  VoltCorner          Voltage corner to enter
  @param[in]  SpeedLevel          Speed level to be set

  @retval EFI_SUCCESS             Storage switched to the indicated speed level and voltage corner.
  @retval EFI_INVALID_PARAMETER   Parameter is invalid. 
  @retval EFI_UNSUPPORTED         The voltage corner and speed level combination is unsupported. 
  @retval EFI_DEVICE_ERROR        Issues were encountered while changing storage to the speed level and/or voltage corner. 
**/
EFI_STATUS EFIAPI UFSSetOperationalMode (
    IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This,
    IN EFI_STORAGE_VOLT_CORNER VoltCorner,
    IN UINT8 SpeedLevel
);

/**
  Configures any link parameters 

  @param[in]  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance
  @param[in]  Params              Link parameters to configure

  @retval EFI_SUCCESS             Function completed successfully.
  @retval EFI_INVALID_PARAMETER   Parameter is invalid.
  @retval EFI_DEVICE_ERROR        Issues were encountered when configuring the parameters given 
**/
EFI_STATUS EFIAPI UFSConfigLinkParams (
    IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This, 
    IN EFI_STORAGE_LINK_PARAMS *Params
); 

/**
  Changes the UFS link state (hibernate enter/exit)

  @param[in]  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance
  @param[in]  LinkState           The state to change the link to 

  @retval EFI_SUCCESS             Function completed successfully.
  @retval EFI_INVALID_PARAMETER   Parameter is invalid.
  @retval EFI_DEVICE_ERROR        Hibernate exit/enter failed. 
**/
EFI_STATUS EFIAPI UFSSetLinkState (
    IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This,
    IN EFI_STORAGE_LINK_STATE LinkState
);

/** 
  Sets the UFS device mode

  @param[in]  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance 
  @param[in]  DevMode             Device Mode

  @retval EFI_SUCCESS             Operation completed successfully.
  @retval EFI_INVALID_PARAMETER   Parameter is invalid. 
  @retval EFI_UNSUPPORTED         Device mode is not supported.
  @retval EFI_DEVICE_ERROR        Device reported an error.  
**/
EFI_STATUS EFIAPI UFSSetDeviceMode (
    IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This,
    IN EFI_STORAGE_DEV_MODE DevMode
);
   
#ifdef FEATURE_XBOOT
/**
  Gets the device descriptor.

  @param[in]  This              Indicates a pointer to the calling
                                context.
  @param[out] DeviceDescriptor  Pointer to a variable that the driver
                                returns with the retrieved device
                                descriptor.
  @param[in]  Size              device descriptor size.

  @retval EFI_SUCCESS             Operation completed successfully.
  @retval EFI_INVALID_PARAMETER   Parameter is invalid.
*/
EFI_STATUS EFIAPI UfsGetDeviceDescriptor (
   IN EFI_MEM_CARDINFO_PROTOCOL *This,
   OUT UINT8 *DeviceDescriptor,
   IN UINT32 Size
);

/**
  Gets the unit descriptor.

  @param[in]  This            Indicates a pointer to the calling
                              context.
  @param[in]  Lun             Logical Unit Number.
  @param[out] UnitDescriptor  Pointer to a variable that the driver
                              returns with the retrieved unit
                              descriptor.
  @param[in]  Size            unit descriptor size.

  @retval EFI_SUCCESS             Operation completed successfully.
  @retval EFI_INVALID_PARAMETER   Parameter is invalid.
*/
EFI_STATUS EFIAPI UfsGetUnitDescriptor (
   IN EFI_MEM_CARDINFO_PROTOCOL *This,
   IN UINT32 Lun,
   OUT UINT8 *UnitDescriptor,
   IN UINT32 Size
);
#endif /* FEATURE_XBOOT */

/**
  Function: UFSGetLevelShifterInfo 

Get information about Level Shifter

  @param  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance
  @param  LsInfo              Level Shifter Information
 
  @return EFI_SUCCESS             Operation completed successfully.
  @return EFI_INVALID_PARAMETER   Parameter is invalid.
  @return EFI_DEVICE_ERROR        Device reported an error.  
**/
EFI_STATUS EFIAPI UFSGetLevelShifterInfo (
    IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This,
    OUT EFI_STORAGE_LS_INFO *LsInfo
);

/** 
  Function: UFSGetTurboModeInfo 

  Get information about Turbo Mode enablement

  @param  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance 
  @param  TurboModeInfo       Turbo Mode enable Information

  @return EFI_SUCCESS             Operation completed successfully.
  @return EFI_INVALID_PARAMETER   Parameter is invalid. 
  @return EFI_DEVICE_ERROR        Device reported an error.  
**/
EFI_STATUS EFIAPI UFSGetTurboModeInfo (
    IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This, 
    OUT EFI_STORAGE_TURBOMODE_INFO *TurboModeInfo
);

/**
  Gets the Shared Ice Algorithm Info.

  @param[in]  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance
  @param[in]  SharedIceBuf        Buffer to share SharedIce info.  

  @retval EFI_SUCCESS             Function completed successfully.
  @retval EFI_INVALID_PARAMETER   Parameter is invalid.
**/
EFI_STATUS EFIAPI UFSGetSharedIceAlgo (
    IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This,
    IN EFI_STORAGE_SHARED_ICE_INFO *SharedIceBuf
);

/**
  Sets the Shared Ice Algorithm with values provided.

  @param[in]  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance
  @param[out] SharedIceBuf        Buffer to share SharedIce info. 

  @retval EFI_SUCCESS             Function completed successfully.
  @retval EFI_INVALID_PARAMETER   Parameter is invalid.
**/
EFI_STATUS EFIAPI UFSSetSharedIceAlgo (
    IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This,
    OUT EFI_STORAGE_SHARED_ICE_INFO *SharedIceBuf
);


#define UFS_DEV_FROM_BLOCKIO(a)   CR (a, UFS_DEV, BlkIo, UFS_DEV_SIGNATURE)
#define UFS_DEV_FROM_BLOCKIO_CRYPTO(a) CR (a, UFS_DEV, BlkIoCrypto, UFS_DEV_SIGNATURE)
#define UFS_DEV_FROM_BLOCKIO2(a)  CR (a, UFS_DEV, BlkIo2, UFS_DEV_SIGNATURE)
#define UFS_DEV_FROM_RPMB(a)        CR (a, UFS_DEV, RPMB, UFS_DEV_SIGNATURE)
#define UFS_DEV_FROM_CARD_INFO(a)   CR (a, UFS_DEV, CardInfo, UFS_DEV_SIGNATURE)
#define UFS_DEV_FROM_ERASE_BLOCK(a) CR (a, UFS_DEV, EraseBlk, UFS_DEV_SIGNATURE)
#define UFS_DEV_FROM_WRITE_PROTECT(a) CR (a, UFS_DEV, WriteProtect, UFS_DEV_SIGNATURE)
#define UFS_DEV_FROM_DEV_MGMT(a) CR (a, UFS_DEV, DeviceMgmt, UFS_DEV_SIGNATURE)

#define EFI_UFS_LUN_0_GUID \
    /* gEfiUFSLun0Guid */ \
    { 0x860845c1, 0xbe09, 0x4355, { 0x8b, 0xc1, 0x30, 0xd6, 0x4f, 0xf8, 0xe6, 0x3a } }

#define EFI_UFS_LUN_1_GUID \
    /* gEfiUFSLun1Guid */ \
    { 0x8d90d477, 0x39a3, 0x4a38, { 0xab, 0x9e, 0x58, 0x6f, 0xf6, 0x9e, 0xd0, 0x51 } }

#define EFI_UFS_LUN_2_GUID \
    /* gEfiUFSLun2Guid */ \
    { 0xedf85868, 0x87ec, 0x4f77, { 0x9c, 0xda, 0x5f, 0x10, 0xdf, 0x2f, 0xe6, 0x01 } }

#define EFI_UFS_LUN_3_GUID \
   /* gEfiUFSLun3Guid */ \
   { 0x1ae69024, 0x8aeb, 0x4df8, { 0xbc, 0x98, 0x00, 0x32, 0xdb, 0xdf, 0x50, 0x24 } }

#define EFI_UFS_LUN_4_GUID \
   /* gEfiUFSLun4Guid */ \
   { 0xd33f1985, 0xf107, 0x4a85, { 0xbe, 0x38, 0x68, 0xdc, 0x7a, 0xd3, 0x2c, 0xea } }

#define EFI_UFS_LUN_5_GUID \
   /* gEfiUFSLun5Guid */ \
   { 0x4ba1d05f, 0x088e, 0x483f, { 0xa9, 0x7e, 0xb1, 0x9b, 0x9c, 0xcf, 0x59, 0xb0 } }

#define EFI_UFS_LUN_6_GUID \
   /* gEfiUFSLun6Guid */ \
   { 0x4acf98f6, 0x26fa, 0x44d2, { 0x81, 0x32, 0x28, 0x2f, 0x2d, 0x19, 0xa4, 0xc5 } }

#define EFI_UFS_LUN_7_GUID \
   /* gEfiUFSLun7Guid */ \
   { 0x8598155f, 0x34de, 0x415c, { 0x8b, 0x55, 0x84, 0x3e, 0x33, 0x22, 0xd3, 0x6f } }

#define EFI_UFS_RPMB_LUN_GUID \
   /* gEfiUfsRPMBGuid */ \
   { 0x5397474e, 0xf75d, 0x44b3, { 0x8e, 0x57, 0xd9, 0x32, 0x4f, 0xcf, 0x6f, 0xe1 } }

#define EFI_UFS_DEVICE_WLUN_GUID \
   /* gEfiUfsDeviceWlunGuid */ \
   { 0xcbdca571, 0x5d36, 0x47a0, { 0x93, 0x18, 0x01, 0xb6, 0xf0, 0xca, 0xc8, 0xed } }

#endif /* _UFS_H_ */

