/*===============================================================================
  Copyright (c) 2017-2018, 2022 Qualcomm Technologies, Inc.  All Rights Reserved.
  
  FILE:         pil_config.h
  DESCRIPTION:    
  
  REVISION HISTORY
  when       who         what, where, why
  --------   ---         --------------------------------------------------------
  08/08/22   cm           Added PIL_CONFIG_MAX and PIL_CONFIG_STR_MAX_LEN
                          removed PIL_CONFIG_FILE definition
  06/14/17   yw           initial version

================================================================================*/

#ifndef __PIL_CONFIG_H__
#define __PIL_CONFIG_H__

#include <Protocol/EFIPIL.h>
#include <scm_sip_interface.h>

#define NAME_MAX_LENGTH2 128
#define PIL_CONFIG_MAX 2
#define PIL_CONFIG_STR_MAX_LEN 32
#define MEDIA_TYPE_NETWORK L"Network"
#define MEDIA_TYPE_FLASH   L"Flash"

#define BUILD_VAR_NAME(b,s,n)  \
       AsciiStrToUnicodeStr(s, b); \
       StrnCatS(b, NAME_MAX_LENGTH2, n, NAME_MAX_LENGTH2)

VOID SetPilConfigIndex(UINT8);
PIL_SUBSYS_CFG_TYPE* PilInitCfgByUnicodeName(CHAR16*);
EFI_STATUS InitImageList(CHAR8*);
PIL_SUBSYS_CFG_TYPE* PilDuplicateCfg(PIL_SUBSYS_CFG_TYPE*);
#endif