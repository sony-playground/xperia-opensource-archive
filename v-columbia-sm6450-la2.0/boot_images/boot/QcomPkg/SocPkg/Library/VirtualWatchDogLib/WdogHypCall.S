//============================================================================
//
// Call HYP for WDOG functionality
//
// Copyright 2020-2021 by Qualcomm Technologies, Inc.  All Rights Reserved 
//============================================================================

//============================================================================
//
//                       EDIT HISTORY FOR MODULE
//
// when      who     what, where, why
// --------  -----   ----------------------------------------------------------
// 10/13/21  rbv     Updated Hyp to have two output parameters
// 08/14/20  ai      Initial revision.
//============================================================================

  ASM_GLOBAL ASM_PFX(WdogHypCall)


#define FuncPrologue                        \
    stp           x29, x30, [sp, #-0x10]!;  \
    mov           x29,sp                    \

#define PushOutputParam                     \
    stp           x3, x4, [sp, #-0x10]!;    \    	

#define PopOutputParam                      \
    ldp           x3, x4, [sp], #0x10;      \

#define FuncEpilogue                        \
    ldp           x29, x30, [sp], #0x10  ;  \
    ret

.text
.align 3

//============================================================================
// UINTN WdogHypCall (
//   IN  UINT32        SmcId,
//   IN  UINT32        Arg1,
//   IN  UINT32        Arg2,
//   IN OUT VOID       *Resp1,
//   IN OUT VOID       *Resp2
// )
//
// @retval           0 - Success
// @retval  Pos or Neg - Failed
//============================================================================

ASM_PFX(WdogHypCall):
    FuncPrologue
    PushOutputParam
    smc #0
    PopOutputParam
    // Check if passed output parameters are not Null and then store output
    cbz           x3, Exit;
    str           x1, [x3];
    cbz           x4, Exit;
    str           x2, [x4];
Exit:
    FuncEpilogue


