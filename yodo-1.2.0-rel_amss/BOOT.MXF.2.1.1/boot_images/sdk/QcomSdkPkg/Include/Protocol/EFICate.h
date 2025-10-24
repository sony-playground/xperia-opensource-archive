/**
  @file  EFICate.h
  @brief CATE Protocol for UEFI.
*/

/*=============================================================================
  Copyright (c) 2018,2020 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when        who        what, where, why
 ---------   --------   --------------------------------------------------------
 24JUL2020   naveiyer   Implemented setargs and launch commands
 01/17/20    yw         add new APIs to modify test in joblist, and to get
                        joblist result
 01/25/18    yw         Created.

=============================================================================*/
#ifndef __EFICATE_H__
#define __EFICATE_H__

/*===========================================================================
  MACRO DECLARATIONS
===========================================================================*/
/** @defgroup efi_cate_protocol EFI_CATE_PROTOCOL
 *  @ingroup UEFI_CORE 
 */
 
  /** @defgroup  efi_cate_protocol_prot PROTOCOL
 *  @ingroup efi_cate_protocol 
 */ 
 /** @defgroup  efi_cate_protocol_apis APIs
 *  @ingroup efi_cate_protocol 
 */ 

/** @defgroup  efi_cate_protocol_data DATA_STRUCTURES
 *  @ingroup efi_cate_protocol 
 
/** @ingroup efi_cate_protocol */
#define      TfPrint(fmt, ...)    \
    DEBUG((EFI_D_WARN, fmt, ##__VA_ARGS__))

// Configurable Properties
#define MIN_TEST_PERIOD 50
#define MAX_TEST_NAME_LENGTH 32
#define MAX_TEST_NUM 200
#define MAX_BUF_SIZE 2048

// Parameter Types
#define TF_PARAM_IDENTIFIER_SIZE 2  /**< -- # of bytes in each TF_PARAM_*              */
#define TF_PARAM_UINT8  "0"         /**< -- Specifies that the parameter is a uint8    */
#define TF_PARAM_UINT16 "1"         /**< -- Specifies that the parameter is a uint16   */
#define TF_PARAM_UINT32 "2"         /**< -- Specifies that the parameter is a uint32   */
#define TF_PARAM_INT8   "3"         /**< -- Specifies that the parameter is a byte     */
#define TF_PARAM_INT16  "4"         /**< -- Specifies that the parameter is a int16    */
#define TF_PARAM_INT32  "5"         /**< -- Specifies that the parameter is a int32    */
#define TF_PARAM_STRING "6"         /**< -- Specifies that the parameter is a string   */

/**
 * @ingroup efi_cate_protocol_data
 *  @brief Testing Framework User (APTTESTS) Response Codes
   @detail
   These are the values that should be returned from test cases.
 */
typedef enum
{
   TF_RESULT_CODE_SUCCESS     = 0,     /**< -- if test case runs successfully          */
   TF_RESULT_CODE_FAILURE     = 1,     /**< -- if test case run unsuccessfully         */
   TF_RESULT_CODE_BAD_PARAM   = 2      /**< -- if test case's parameters are invalid   */
} TF_TestCaseResponseCodes;


/** @brief Test Case Function Pointer Type -- Version 0
    @detail
    Function prototype of test case entry points; no return buffer.
 */
typedef UINT32 (*TF_TCFunctionPtr)(UINT32 dwParam, CHAR8 *apszParam[]);

/** @ingroup efi_cate_protocol_data
 * @brief Testing Framwork Parameter Descriptions
    @detail
    Description of a test case parameter's type, name and help/description.
 */
typedef struct 
{
   CHAR8 *pszType;         /**< -- parameter's type. Values are of type TF_PARAM        */ 
   CHAR8 *pszName;         /**< -- name of the parameter. Nullable                      */ 
   CHAR8 *pszHelpString;   /**< -- General help info about this parameter. Nullable     */
} TF_ParamDescr;

/** @ingroup efi_cate_protocol_data
 * @brief Testing Framework Test Context description
    @detail
    Used to describe a test case's context: what the test case is being used on
 */
typedef struct
{
   UINT8 cSubsysId;            /**< -- Subsystem id of the test case                   */
   UINT16 wContextId;          /**< -- Context id of the test case                     */
} TF_ContextDescr;

/** @ingroup efi_cate_protocol_data 
 * @brief Help Description
   @detail 
   Contains information about a specific test case. 
   Parameter information does not need to be included.
 */
typedef struct 
{
   CONST CHAR8 *pszFunctionDescr;  /**< --  Test case description. Should not be NULL    */
   UINT32 dwParametersLength;      /**< --  Number of parameters expected.   Can be zero */
   CONST TF_ParamDescr *pParameters;/**< --  Parameter descriptions. Can be NULL         */
} TF_HelpDescr;

/** @ingroup efi_cate_protocol_data 
 * @brief Testing Framework Test Function Description
    @detail
    Describes everything about a test case needed to run it. The testing table is
    an array of these elements. Each one of these is used to register a single
    test case into the Test Framework.
 */
typedef struct 
{
   CONST CHAR8 *pszTestName;        /**< --  Unique name for the test case. Nonnullable  */
   TF_TCFunctionPtr pTestFunc;     /**< --  Pointer to test entry point. Nonnullable    */
   CONST TF_HelpDescr *pHelp;      /**< --  Information about test case. Nullable       */
   CONST TF_ContextDescr *pContext;/**< --  Context the tc desiged for. Nullable        */
   UINT32 dwTestFuncType;          /**< --  Determines version for pTestFunc member;
                                            must be listed as at least the 5th member
                                            of this struct so it gets initialized to
                                            0 in old test case code.                    */
} TF_TestFunction_Descr;

/** @ingroup efi_cate_protocol_data 
  @par Summary
  TF_TestList_Descr struct.

  @par Parameters
*/
typedef struct 
{
   CONST CHAR8 *pszName;        				/**< --  Unique name for the test list  */
   CONST TF_TestFunction_Descr** TestList;        /**< --  array of the test list        **/
   
} TF_TestList_Descr;


/** @ingroup efi_cate_protocol 
  Protocol version.
*/
#define EFI_CATE_PROTOCOL_VERSION 		0x0000000000010001
#define EFI_CATE_PROTOCOL_VERSION_V2 	0x0000000000010002

/*  Protocol GUID definition */

#define EFI_CATE_PROTOCOL_GUID \
  { 0x3bec87db, 0x4e76, 0x491c, { 0x96, 0x6c, 0x7c, 0xa5, 0x81, 0x2a, 0x64, 0xc9 } }

/** @cond */
/*===========================================================================
  EXTERNAL VARIABLES
===========================================================================*/
/**
  External reference to the CATE Protocol GUID.
*/
extern EFI_GUID gEfiCateProtocolGuid;

/** @endcond */

/*===========================================================================
  TYPE DEFINITIONS
===========================================================================*/

/* EFI_CATE_ADD_TESTS */
/** @ingroup efi_cate_protocol_apis 
  @par Summary
  add test cases into test framework

  @return
  EFI_SUCCESS -- Function completed successfully.
 */
typedef EFI_STATUS (EFIAPI *EFI_CATE_ADD_TESTS)(
  IN CONST TF_TestFunction_Descr** Tests,
  IN UINTN							Num_Tests
);
 

/* EFI_CATE_REMOVE_TESTS */
/** @ingroup efi_cate_protocol_apis
  @par Summary
  remove test cases from test framework

  @return
  EFI_SUCCESS -- Function completed successfully.
 */

typedef EFI_STATUS (EFIAPI *EFI_CATE_REMOVE_TESTS)(
  IN CONST TF_TestFunction_Descr** Tests,
  IN UINTN							Num_Tests
);

/** @ingroup efi_cate_protocol_data 
  @par Summary
  CATE_TEST_ATTRI_TYPE enum.

  @par Parameters
*/
typedef enum
{
	CATE_TEST_PARAMS = 1,
	CATE_TEST_TIMEOUT,
} CATE_TEST_ATTRI_TYPE;


/* EFI_CATE_MODIFY_TEST_ATTRIB_IN_JOBLIST */
/** @ingroup efi_cate_protocol_apis
  @par Summary
  modify attribute of a test def in joblist

  @return
  EFI_SUCCESS -- Function completed successfully.
 */
typedef EFI_STATUS (EFIAPI *EFI_CATE_MODIFY_TEST_ATTRIB_IN_JOBLIST)(
  IN CONST CHAR8* JobListName,
  IN CONST CHAR8* JobName,
  IN CATE_TEST_ATTRI_TYPE AttriToChange,
  IN VOID*	Value
);

/** @ingroup efi_cate_protocol_data 
  @par Summary
  CATE_TEST_RESULT_TYPE enum.

  @par Parameters
*/
typedef enum {
	TEST_NONE			= 0,
	TEST_PASS 			= 1,
	TEST_FAILURE		= 2,
	TEST_BAD_PARAM		= 3,
	TEST_TIMEOUT		= 4,  // only used by uefi side
} CATE_TEST_RESULT_TYPE;

/** @ingroup efi_cate_protocol_data 
  @par Summary
  CATE_CMD_RESULT_TYPE enum.

  @par Parameters
*/
typedef enum {
	CMD_RET_NONE		= 0,
	CMD_RET_PASS 		= 1,
	CMD_RET_FAILURE		= 2,
	CMD_RET_BAD_PARAM	= 3,
	CMD_RET_TIMEOUT		= 4,  // only used by uefi side
} CATE_CMD_RESULT_TYPE;

#define	CMD_RESULT_BIT_SHIFT	4
#define CMD_RESULT_BIT_MASK		(((1<<CMD_RESULT_BIT_SHIFT)-1)<<CMD_RESULT_BIT_SHIFT)
#define TEST_RESULT_BIT_MASK    0xf

#define READ_CMD_RESULT(r)		(((r)&CMD_RESULT_BIT_MASK)>>CMD_RESULT_BIT_SHIFT)
#define READ_TEST_RESULT(r) 	((r)&TEST_RESULT_BIT_MASK)

/** @ingroup efi_cate_protocol_data 
  @par Summary
  CATE_JOBLIST_SUB_RESULT_TYPE enum.

  @par Parameters
*/
typedef struct
{
	CHAR8 TestName[16];
	CHAR8 Result; 		/* MSB 4 bits for cmd result, LSB 4 bits for test result */
} CATE_JOBLIST_SUB_RESULT_TYPE;

/** @ingroup efi_cate_protocol_apis */
typedef 
EFI_STATUS (EFIAPI *EFI_CATE_CHECK_JOBLIST_RESULT)(
  IN 		CONST CHAR8* 					JobListName,
  OUT		CATE_TEST_RESULT_TYPE*  		JobListResult,
  OUT 		CATE_JOBLIST_SUB_RESULT_TYPE* 	JobListSubResult,
  IN OUT 	UINT32*							SubResultBufSize
);

/* EFI_CATE_HANDLE_COMMAND */
/** @ingroup efi_cate_protocol_apis
  @par Summary
  process given command

  @return
  EFI_SUCCESS -- Function completed successfully.
 */
typedef EFI_STATUS (EFIAPI *EFI_CATE_HANDLE_COMMAND)(
   IN CONST CHAR8* Request
);

/* EFI_CATE_SET_APP_ARGS */
/** @ingroup efi_cate_protocol_apis
  @par Summary
  set one-huge-ASCII-string argument for an app

  @return
  EFI_SUCCESS -- Function completed successfully.
 */
typedef EFI_STATUS (EFIAPI *EFI_CATE_SET_APP_ARGS)(
  CHAR8 *app_name,
  CHAR8 *argv
);

/** @ingroup efi_cate_protocol_data
 * App and CPU number to launch that app on.
 */
typedef struct
{
  CHAR8 *app_name;
  INT32 cpu_num; // If negative, then no CPU preference.
} APP_N_CPU_NUM;

/* EFI_CATE_LAUNCH_APPS */
/** @ingroup efi_cate_protocol_apis
  @par Summary
  launch apps, optionally, on specific cpus

  @return
  EFI_SUCCESS -- Function completed successfully.
 */
typedef EFI_STATUS (EFIAPI *EFI_CATE_LAUNCH_APPS)(
  UINT32 app_cpu_arr_cnt,
  // Array of app_cpu_arr_cnt struct APP_N_CPU_NUMs.
  APP_N_CPU_NUM *app_cpu_arr
);

/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup efi_cate_protocol_prot
  @par Summary
  CATE Protocol interface.

  @par Parameters
  @inputprotoparams
*/
typedef struct _EFI_CATE_PROTOCOL {
  UINT64                                 Version;
  EFI_CATE_ADD_TESTS                     AddTests;
  EFI_CATE_REMOVE_TESTS                  RemoveTests;
  EFI_CATE_HANDLE_COMMAND                HandleCommand;
  EFI_CATE_MODIFY_TEST_ATTRIB_IN_JOBLIST ModifyTestAttribInJobList;//added in v2
  EFI_CATE_CHECK_JOBLIST_RESULT          CheckJobListResult;      // added in v2
  EFI_CATE_SET_APP_ARGS                  SetAppArgs;
  EFI_CATE_LAUNCH_APPS                   LaunchApps;
} EFI_CATE_PROTOCOL;

#endif  /* __EFICATE_H__ */
