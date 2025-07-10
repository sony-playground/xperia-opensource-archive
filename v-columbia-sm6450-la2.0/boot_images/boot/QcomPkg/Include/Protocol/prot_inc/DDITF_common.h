
/*==============================================================================

FILE: DDITF_common.h

      Copyright (c) 2020 Qualcomm Technologies, Incorporated.
              All Rights Reserved.
       Qualcomm Technologies Proprietary and Confidential.
==============================================================================*/

#ifndef __DDITF_COMMON_H__
#define __DDITF_COMMON_H__

/** @brief Test Case Function Pointer Type -- Version 0
    @detail
    Function prototype of test case entry points; no return buffer.
 */
typedef UINT32 (*TF_TCFunctionPtr)(UINT32 dwParam, char *apszParam[]);

/** @brief Testing Framwork Parameter Descriptions
    @detail
    Description of a test case parameter's type, name and help/description.
 */
typedef struct 
{
   char *pszType;         /**< -- parameter's type. Values are of type TF_PARAM        */ 
   char *pszName;         /**< -- name of the parameter. Nullable                      */ 
   char *pszHelpString;   /**< -- General help info about this parameter. Nullable     */
} TF_ParamDescr;

/** @brief Testing Framework Test Context description
    @detail
    Used to describe a test case's context: what the test case is being used on
 */
typedef struct
{
   UINT8 cSubsysId;            /**< -- Subsystem id of the test case                   */
   UINT16 wContextId;          /**< -- Context id of the test case                     */
} TF_ContextDescr;

/** @brief Help Description
   @detail 
   Contains information about a specific test case. 
   Parameter information does not need to be included.
 */
typedef struct 
{
   const char *pszFunctionDescr;  /**< --  Test case description. Should not be NULL    */
   UINT32 dwParametersLength;      /**< --  Number of parameters expected.   Can be zero */
   const TF_ParamDescr *pParameters;/**< --  Parameter descriptions. Can be NULL         */
} TF_HelpDescr;

/** @brief Testing Framework Test Function Description
    @detail
    Describes everything about a test case needed to run it. The testing table is
    an array of these elements. Each one of these is used to register a single
    test case into the Test Framework.
 */
typedef struct 
{
   const char *pszTestName;        /**< --  Unique name for the test case. Nonnullable  */
   TF_TCFunctionPtr pTestFunc;     /**< --  Pointer to test entry point. Nonnullable    */
   const TF_HelpDescr *pHelp;      /**< --  Information about test case. Nullable       */
   const TF_ContextDescr *pContext;/**< --  Context the tc desiged for. Nullable        */
   UINT32 dwTestFuncType;          /**< --  Determines version for pTestFunc member;
                                            must be listed as at least the 5th member
                                            of this struct so it gets initialized to
                                            0 in old test case code.                    */
} TF_TestFunction_Descr;

#endif /*__DDITF_COMMON_H__*/
