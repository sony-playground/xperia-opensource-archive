/** @file BdsInputLib.h
   
  Contains AutoLaunch feature parsing routines

  Copyright (c) 2020 Qualcomm Technologies, Inc. All rights reserved. 
 
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 05/20/19   ps      Initial version
=============================================================================*/
/**
 *  user interface to input string in BDS menu.
 *
 * IN OUT InputString.
 */

VOID GetAutoLaunchUserInput(CHAR8 *InputString);


/**

  @param InputString      Input String
  @param InputStringSize  InputString's size
  @param GUID             GUID of test app.
  @param PartitionLabel   Partition name from the input string
  @param AppName          AppName from the input string

**/
EFI_STATUS AutoLaunchParser(CHAR8 *InputString, UINT32 InputStringSize, CHAR16 *PartitionLabel, CHAR8 *AppName);
