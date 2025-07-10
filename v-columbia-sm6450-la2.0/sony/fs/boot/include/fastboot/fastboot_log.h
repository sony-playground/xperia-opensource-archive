/*
 * Copyright (C) 2020 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdarg.h>

void fastbootlog_ta(const char *fmt, ...);


#ifdef DEBUG
#undef DEBUG
#endif
#ifdef _DEBUG
#undef _DEBUG
#endif
#ifdef _DEBUG_PRINT
#undef _DEBUG_PRINT
#endif
#define _DEBUG_PRINT(PrintLevel, ...)              \
  do {                                             \
    if (DebugPrintLevelEnabled (PrintLevel)) {     \
      DebugPrint (PrintLevel, ##__VA_ARGS__);      \
      if(PrintLevel == EFI_D_ERROR) {              \
        fastbootlog_ta(__VA_ARGS__);               \
      }                                            \
    }                                              \
  } while (FALSE)
#define _DEBUG(Expression)   _DEBUG_PRINT Expression

#define DEBUG(Expression)        \
  do {                           \
    if (DebugPrintEnabled ()) {  \
      _DEBUG (Expression);       \
    }                            \
  } while (FALSE)

