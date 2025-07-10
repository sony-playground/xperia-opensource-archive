/*===============================================================================
  Copyright (c) 2020 Qualcomm Technologies, Inc.  All Rights Reserved.
  
  FILE:         ParserDxe.c
  DESCRIPTION:    
  
  REVISION HISTORY
  when       who         what, where, why
  --------   ---         --------------------------------------------------------
  05/05/20   yw         initial version
================================================================================*/
#include <Protocol/EFIParser.h>
#include <Library/KernelLib.h>
#include <Library/ParserLib.h>
#include <Library/UefiBootServicesTableLib.h>

LockHandle* ParserLockPtr;

/* Open Parser for the buffer passed in
 * If ParseOptions pointer is NULL then default values are used (ie # is comment char)
 *
 * @param
 * @param[IN]  Buffer     : Buffer containing the data to be parsed
 * @param[IN]  BufferSize : Size of the data in buffer
 * @param[IN]  Popt       : ParseOptions (Only comment char is supported now)
 * @param[OUT] Pd         : Ptr to parser descriptor
 *
 * @retval EFI_SUCCESS      Parser opened successfully.
 * */
STATIC EFI_STATUS
EFI_Parser_OpenParser(
    IN  UINT8*             Buffer,
    IN  UINT32             BufferSize,
    IN  ParseOptionsType*  Popt OPTIONAL,
    OUT INTN*			  Pd
   )
{
	INTN Desc = -1;
	if (Pd==NULL)
		return EFI_INVALID_PARAMETER;
	
	AcquireLock(ParserLockPtr);
	Desc = OpenParser(Buffer, BufferSize, Popt);
	ReleaseLock(ParserLockPtr);
	*Pd = Desc;
	
	return (Desc>=0)?EFI_SUCCESS:EFI_UNSUPPORTED;
}


/*
 * Close the parser context and release the resources.
 *
 * @param[IN] Pd  : Parser Descriptor
 *
 * @retval EFI_SUCCESS      Parser closed successfully.
 * */
STATIC EFI_STATUS
EFI_Parser_CloseParser (
	IN  INTN            Pd
	)
{
	INTN Ret = -1;
	
	AcquireLock(ParserLockPtr);
	Ret = CloseParser(Pd);
	ReleaseLock(ParserLockPtr);
	
	return (Ret>=0)?EFI_SUCCESS:EFI_UNSUPPORTED; 
}

/*
 * Enumerate the key values by getting callback for each item. Optional Section string can
 * be specified to get the values only for the specified section. If the Section pointer is
 * NULL then all values with their Section string is returned.
 *
 * @param[IN] Pd            : Parser Descriptor
 * @param[IN] Section       : Optional Section, if specified, only key-value pairs for the specified section are returned.
 * @param[IN] CallBackFunc  : Callback function to get the callback with all the enumerated values.
 *
 * @retval EFI_SUCCESS      
 * */
STATIC EFI_STATUS
EFI_Parser_EnumKeyValues(
	IN  INTN                      Pd,
    IN  UINT8*                    Section   OPTIONAL,
    IN  KeyValueCallBackFuncType  CallBackFunc
	)
{
	INTN Ret = EnumKeyValues(Pd, Section, CallBackFunc);
	return (Ret>=0)?EFI_SUCCESS:EFI_UNSUPPORTED; 
}

/*
 * Re-open parser for repeated further processing
 *
 * @param[IN] Pd            : Parser Descriptor
 *
 * @retval EFI_SUCCESS      Parser re-opened successfully.
 * */
STATIC EFI_STATUS
EFI_Parser_ReopenParser(
	IN INTN Pd
	)
{
	INTN Ret = ReopenParser(Pd);
	return (Ret>=0)?EFI_SUCCESS:EFI_UNSUPPORTED; 
}


/**
  Parser protocol defination
  
**/
STATIC EFI_PARSER_PROTOCOL ParserProtocol =
{
   EFI_PARSER_PROTOCOL_VERSION_V1,
   EFI_Parser_OpenParser,
   EFI_Parser_CloseParser,
   EFI_Parser_EnumKeyValues,
   EFI_Parser_ReopenParser
};

/**
  The Entry Point for parser module. 

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurred when executing this entry point.

**/
 
EFI_STATUS EFIAPI 
ParserDxeEntry
(
  IN EFI_HANDLE ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
)
{
	EFI_HANDLE Handle = NULL;
    EFI_STATUS Status;
	
	Status = InitLock("ParsrLck", &ParserLockPtr);
	if (EFI_ERROR(Status)) {
		DEBUG ((EFI_D_ERROR, "Failed to init lock\n"));
		goto ParserEntryExit;
	}
	
	Status = gBS->InstallMultipleProtocolInterfaces(
                    &Handle,
                    &gEfiParserProtocolGuid,
                    (VOID **)&ParserProtocol,
                    NULL );
    if (EFI_ERROR(Status)) {
        DEBUG ((EFI_D_ERROR, "Failed to install parser protocol.\n"));
    }
	
ParserEntryExit:
	return Status;
}