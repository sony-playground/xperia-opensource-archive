/** @file

  MacroUtility.h

  Copyright (c) 2022 Qualcomm Technologies, Inc. All rights reserved.

**/
/*=============================================================================
EDIT HISTORY


when       who     what, where, why
--------   ---     -----------------------------------------------------------
07/01/20   shl     Initial revision
=============================================================================*/

#ifndef _MACRO_UTILITY_H_
#define _MACRO_UTILITY_H_


#define ALIGN_UP(size, alignment)  (((size) + ((alignment)-1)) & ~((alignment)-1))
#define ADDR_SIZE                  64
#define PAGE_SIZE                  4096
#define ADDR_ALIGN(x)              ALIGN_UP(x, ADDR_SIZE)
#define PAGE_ALIGN(x)              ALIGN_UP(x, PAGE_SIZE)  


#define EXIT_IF_TRUE(xx)                                                     \
  do                                                                         \
  {                                                                          \
     if((xx))                                                                \
     {                                                                       \
        DEBUG((EFI_D_ERROR, "%a..%a:%d Failed! input = 0x%x  \n",__FILE__, __FUNCTION__, __LINE__, (xx))); \
        goto ErrorExit;                                                      \
     }                                                                       \
  } while(0)


#define PRINT_IF_TRUE(xx)                                                    \
  do                                                                         \
  {                                                                          \
     if((xx))                                                                \
     {                                                                       \
        DEBUG((EFI_D_ERROR, "%a..%a: %d Failed! input = 0x%x  \n",__FILE__, __FUNCTION__, __LINE__, (xx))); \
     }                                                                       \
  } while(0)


#define PARAM_CHECK_EXIT_IF_TRUE(xx)                                         \
  do                                                                         \
  {                                                                          \
     if((xx))                                                                \
     {                                                                       \
        DEBUG((EFI_D_ERROR, "%a..%a:%d Failed!   \n",__FILE__, __FUNCTION__, __LINE__ )); \
        Status = EFI_INVALID_PARAMETER;                                      \
        goto ErrorExit;                                                      \
     }                                                                       \
  } while(0)


#define TPM_CMD_EXIT_TRUE(xx)                                                \
  do                                                                         \
  {                                                                          \
     if((xx) )                                                               \
     {                                                                       \
        DEBUG((EFI_D_ERROR, " %a..%a: %d TPM cmd Failed! rspCode = 0x%x  \n", __FILE__, __FUNCTION__, __LINE__, (xx))); \
        Status = EFI_DEVICE_ERROR;                                       \
        goto ErrorExit;                                                      \
     }                                                                       \
  } while(0)


#define TEST_RESULT_PRINT(xx)                                                \
  do                                                                         \
  {                                                                          \
     if( TestPrint == FALSE )                                                \
        break;                                                               \
                                                                             \
     if((xx) == EFI_SUCCESS)                                                 \
     {                                                                       \
        DEBUG((EFI_D_ERROR, "%a() success! \n",__FUNCTION__));               \
     }                                                                       \
     else                                                                    \
     {                                                                       \
        DEBUG((EFI_D_ERROR, "%a() failed! Status = 0x%x  \n",__FUNCTION__, (xx))); \
     }                                                                       \
  } while(0)


#define ALLOCATE_MEMORY_CHECK(xx)                                            \
  do                                                                         \
  {                                                                          \
     if((xx) == NULL )                                                       \
     {                                                                       \
        DEBUG((EFI_D_ERROR, " Allocate memory failed %a..%a: %d Failed! \n", __FILE__, __FUNCTION__, __LINE__)); \
        Status = EFI_OUT_OF_RESOURCES;                                       \
        goto ErrorExit;                                                      \
     }                                                                       \
  } while(0)


#define FREE_MEMORY(xx)              \
  do                                 \
  {                                  \
     if((xx) != NULL )               \
     {                               \
        FreePool((xx));              \
     }                               \
  } while(0)


#define SWAP_16(xx)  ((xx) & 0xFF00 )>>8  | ((xx) & 0x00FF )<<8

#define SWAP_32(xx)  ((xx) & 0xFF000000)>>24 | ((xx) & 0x00FF0000)>>8 | ((xx) & 0x0000FF00)<<8  | ((xx) & 0x00000000FF)<<24 


#endif //_MACRO_UTILITY_H_
