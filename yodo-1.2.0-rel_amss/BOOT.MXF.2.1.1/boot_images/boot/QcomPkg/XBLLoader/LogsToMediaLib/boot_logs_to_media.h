#ifndef _BOOT_LOGS_TO_MEDIA_H
#define _BOOT_LOGS_TO_MEDIA_H

/*===========================================================================

                                logs_to_media.h
                                Header File

GENERAL DESCRIPTION
  This header file contains target specific declarations and definitions
  
Copyright 2021 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who          what, where, why
--------   --------     ----------------------------------------------------------
06/23/22   ds           changes for FR78810 - stream logs to media
07/20/21   digants      Initial Revision
============================================================================*/

/*===========================================================================

                           INCLUDE FILES

===========================================================================*/
#include <boot_comdef.h>
#include <boot_config_context.h>
#include <boot_error_if.h>
#include <boot_logger_if.h>
/*=============================================================================

                            DEFINITIONS

=============================================================================*/

typedef enum
{
  BL_READ_ERROR = BL_ERR_CUSTOM_ERRORS_START,
  BL_WRITE_ERROR,
  BL_PARTITION_ERROR,
  BL_INIT_NOT_CALLED,
  BL_INCORRECT_LOG_BUFF_PARAMS
}bl_error_boot_logs_to_media_type;

typedef enum
{
  NONE = 0,
  COMPLETE_LOG_FLUSH,
  STREAMING_LOG,
  FEATURE_MAX
}media_logging_feature;

bl_error_boot_type boot_media_logger_get_interface(boot_registered_logger_if_type **logger_if);

bl_error_boot_type boot_init_logs_to_media(const boot_handle config_context_handle);

bl_error_boot_type boot_media_logger_set_feature_type(media_logging_feature feature);

bl_error_boot_type boot_save_logs_to_media(const boot_handle config_context_handle);

#endif  /* _BOOT_LOGS_TO_MEDIA_H */
