/** @file
  Implements AutoLaunch parsing routines
   
  Copyright (c) 2020 Qualcomm Technologies, Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 05/20/19   ps      Initial version
=============================================================================*/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/QcomLib.h>
#include <Library/BaseLib.h>

/**
 *  user interface to input string in BDS menu.
 *
 * IN OUT InputString.
 */

VOID GetAutoLaunchUserInput(CHAR8 *InputString)
{ 
  UINT8 k = 0;
  EFI_INPUT_KEY  Key;
  Key.ScanCode = SCAN_NULL;
  Key.UnicodeChar = CHAR_NULL;

  //copy test app name
  do 
  {
    ReadAnyKey(&Key, 0);
    
    if(Key.UnicodeChar == CHAR_CARRIAGE_RETURN)
      break;
    else if(k > 0 && Key.UnicodeChar == CHAR_BACKSPACE)
    {
      InputString[k--] = '\0';
      continue;
    }
    AsciiPrint("%c",Key.UnicodeChar);  
    InputString[k++] = Key.UnicodeChar;
  }while(1);
  
  InputString[k] = '\0';

}

/**

  @param InputString      Input String
  @param InputStringSize  InputString's size
  @param PartitionLabel   Partition name from the input string
  @param AppName          AppName from the input string

**/

EFI_STATUS AutoLaunchParser(CHAR8 *InputString,
                      UINT32 InputStringSize,
                      CHAR16  *PartitionLabel,
                      CHAR8  *AppName)
{
  if(InputString == NULL || InputStringSize == 0)
    return EFI_NOT_FOUND;
  UINT8 k =0, i =0;
  //Get the Partition Name
  do 
  {
    if(InputString[i] == ' ')
    {
      i++;
      break;
    }
    PartitionLabel[k++] = InputString[i++];
  }while(i < InputStringSize);
  PartitionLabel[k] = '\0';
  k=0;

  //Get the AppName
  do 
  {
    if(InputString[i] == '\n' || InputString[i] == '\0')
    {
      break;
    }
    AppName[k++] = InputString[i++];
  }while(i < InputStringSize);

  AppName[k] = '\0';
  return EFI_SUCCESS;
}
