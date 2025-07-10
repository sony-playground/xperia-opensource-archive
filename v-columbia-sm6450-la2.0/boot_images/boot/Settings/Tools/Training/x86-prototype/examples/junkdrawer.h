
#include <stdint.h>
#include <stdio.h>

#define boot_log_message puts
#define strlcat strncat
#define strlcpy strncpy

extern char *strError(int error);
