/*===============================================================================
  Copyright (c) 2020-2021 Qualcomm Technologies, Inc.  All Rights Reserved.
  
  FILE:         EFISSR.h
  DESCRIPTION:    
  
  REVISION HISTORY
  when       who         what, where, why
  --------   ---         --------------------------------------------------------
  09/10/20   yw          initial version

================================================================================*/

#ifndef __EFI_SSR_H__
#define __EFI_SSR_H__

/** @defgroup EFI_TEST_SSR_PROTOCOL  EFI_TEST_SSR_PROTOCOL 
 *  @ingroup UEFI_CORE 
 */
 /** @defgroup  EFI_TEST_SSR_PROTOCOL_prot PROTOCOL
 *  @ingroup EFI_TEST_SSR_PROTOCOL 
 */ 
 /** @defgroup  EFI_TEST_SSR_PROTOCOL_apis APIs
 *  @ingroup EFI_TEST_SSR_PROTOCOL 
 */ 

/** @defgroup  EFI_TEST_SSR_PROTOCOL_data DATA_STRUCTURES
 *  @ingroup EFI_TEST_SSR_PROTOCOL 
 */

/** @ingroup  EFI_TEST_SSR_PROTOCOL_data 
 */
#define EFI_SSR_PROTOCOL_VERSION_V1 0x0000000000010001

#define EFI_SSR_PROTOCOL_GUID \
  { 0x3966ae2d, 0x2972, 0x4560, { 0xba, 0xfb, 0x1a, 0x9d, 0x5e, 0xe7, 0xe6, 0xe0 } }

#define EFI_TEST_SSR_PROTOCOL_GUID  \
  { 0xd2119ae7, 0xf9d7, 0x4d33, { 0xa5, 0x18, 0xf8, 0x06, 0xb6, 0xb8, 0x92, 0x95 } }
  
extern EFI_GUID gEfiSSRProtocolGuid;
extern EFI_GUID gEfiTestSSRProtocolGuid;

/** @ingroup EFI_TEST_SSR_PROTOCOL_apis
  enable ssr for the subsystem with given ID

  @param[in]  SubsysID         subsystem ID which will be ssr enabled

  @retval EFI_SUCCESS          success.
  
**/
typedef
EFI_STATUS
(EFIAPI *EFI_SSR_REGISTER_SUBSYS) (
   IN UINT32                           SubsysID
   );

/**@ingroup EFI_TEST_SSR_PROTOCOL_data
**/ 
typedef enum
{
    SSR_PRE_SHUTDOWN,
    SSR_POST_SHUTDOWN,
    SSR_PRE_RESTART,
    SSR_POST_RESTART,
    SSR_PROXY_UNVOTE,
    SSR_POST_UNVOTE
} SSR_EVENT_TYPE;

/** @ingroup EFI_TEST_SSR_PROTOCOL_data
**/
typedef    EFI_STATUS    (*SSR_DRIVER_CB_FUNC)(SSR_EVENT_TYPE, VOID*);

/**@ingroup EFI_TEST_SSR_PROTOCOL_data
**/
typedef struct
{
    SSR_DRIVER_CB_FUNC    Cb;
    VOID*                Arg;
} SSR_DRIVER_CB_TYPE;


/** @ingroup EFI_TEST_SSR_PROTOCOL_apis
  driver register ssr callbacks for a subsystem

  @param[in]  DrvName                  name of driver
  @param[in]  SubsysID                 subsystem ID which the driver will register
  @param[in]  SSR_DRIVER_CB_TYPE    callback struct including callback func and args
  @param[in]  Prio                    priority of the callback, 0 is highest

  @retval EFI_SUCCESS          success.
  
**/
typedef
EFI_STATUS
(EFIAPI *EFI_SSR_REGISTER_CALLBACK_FOR_SUBSYS)(
   IN CHAR8*                            DrvName,
   IN UINT32                            SubsysId,
   IN SSR_DRIVER_CB_TYPE*               Cb,
   IN UINT32                            Prio
);

/**@ingroup EFI_TEST_SSR_PROTOCOL_data
**/
typedef enum
{
    SYSTEM_RESTART = 0,    // default
    SUBSYS_RESTART,
} RESTART_LEVEL;


/** @ingroup EFI_TEST_SSR_PROTOCOL_apis
  change restart level for specific subsystem

  @param[in]  SubsysID         subsystem ID which will be ssr enabled
  @param[in]  Level            restart level that the subsystem will change to

  @retval EFI_SUCCESS          success.
  
**/
typedef
EFI_STATUS
(EFIAPI *EFI_SSR_MODIFY_RESTART_LEVEL) (
   IN UINT32                           SubsysId,
   IN RESTART_LEVEL                       Level
   ); 

/** @ingroup EFI_TEST_SSR_PROTOCOL_apis
 * 
**/
typedef 
EFI_STATUS 
(EFIAPI *EFI_SSR_UN_REGISTER_CALLBACK_FOR_SUBSYS)(
	IN CHAR8* DrvName,
	IN UINT32 SubsysId
);      

/**@ingroup EFI_TEST_SSR_PROTOCOL_prot
**/   
typedef struct _EFI_SSR_PROTOCOL {
   UINT64                                    Revision;
   EFI_SSR_REGISTER_SUBSYS                   RegisterSubsys;
   EFI_SSR_REGISTER_CALLBACK_FOR_SUBSYS      RegisterCbForSubsys;
} EFI_SSR_PROTOCOL;

/**@ingroup EFI_TEST_SSR_PROTOCOL_prot
**/
typedef struct _EFI_TEST_SSR_PROTOCOL {
   UINT64                                    Revision;
   EFI_SSR_REGISTER_SUBSYS                   RegisterSubsys;
   EFI_SSR_REGISTER_CALLBACK_FOR_SUBSYS      RegisterCbForSubsys;
   EFI_SSR_MODIFY_RESTART_LEVEL              ModifyRestartLvl;
   EFI_SSR_UN_REGISTER_CALLBACK_FOR_SUBSYS   UnRegisterCbForSubsys;
} EFI_TEST_SSR_PROTOCOL;

#endif // __EFI_SSR_H__