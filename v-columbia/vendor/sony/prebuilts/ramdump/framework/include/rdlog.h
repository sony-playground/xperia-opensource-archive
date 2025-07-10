/*
 * Copyright (C) 2012 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef _RDLOG_H_
#define _RDLOG_H_

#ifdef __cplusplus
extern "C" {
#endif
/***********************************************************************/
/*! @brief Re-directs the logs to the specified path.
*   @param[in] path Path to which logs need to be saved.
*   @retval int 0 for success. Others for error.
*/
/***********************************************************************/
int log_redirect(const char *path);

/***********************************************************************/
/*! @brief gets the complete path of the ramdump log. If klogger is started, tha path used by it
*   @param[out] path Path to which logs are being saved.
*   @param[in] Size of the allocated buffer for path.
*   @retval int 0 for success. Others for error.
*/
/***********************************************************************/
int get_rdlog_path(char *path, size_t size);

/***********************************************************************/
/*! @brief Sets the print tag.
*   @param[in] tag tag name that is appended to all the prints.
*   @retval int 0 for success. Others for error.
*/
/***********************************************************************/
int set_printtag(const char *tag);

/***********************************************************************/
/*! @brief Starts a thread that polls for data from kernel log and store it
*   in the given path.
*   @param[in] path path where log needs to be stored.
*   @retval int 0 for success. Others for error.
*/
/***********************************************************************/
int start_klogger(const char *path);

/***********************************************************************/
/*! @brief Stops the thread that was started by start_klogger() function.
 */
/***********************************************************************/
void stop_klogger(void);


/***********************************************************************/
/*! @brief Returns only the file name from the given path.
*   @param[in] path The abosule path of the file.
*   @retval A pointer to the file name is returned.
*/
/***********************************************************************/
char *get_file_name(const char *path);

#define  LOG_LEVEL_INFO	" <I>"
#define  LOG_LEVEL_WARN	" <W>"
#define LOG_LEVEL_ERROR	" <E>"
#define LOG_LEVEL_DEBUG	" <D>"

int log_print(const char *fmt, ...);


#define __FILE_NAME__ get_file_name(__FILE__)

#ifdef ANDROID
#include <android/log.h>
int android_log_print(int prio, const char *fmt, ...);

#define PRINT_ERROR(fmt, ...)					\
({								\
log_print(LOG_LEVEL_ERROR " %s(%d): " fmt,			\
			__FILE_NAME__, __LINE__, ##__VA_ARGS__);	\
android_log_print(ANDROID_LOG_ERROR, " %s(%d): " fmt,		\
			__FILE_NAME__, __LINE__, ##__VA_ARGS__);	\
})
#define PRINT_WARN(fmt, ...)					\
({								\
log_print(LOG_LEVEL_WARN " %s(%d): " fmt,			\
			__FILE_NAME__, __LINE__, ##__VA_ARGS__);	\
android_log_print(ANDROID_LOG_WARN, " %s(%d): " fmt,		\
			__FILE_NAME__, __LINE__, ##__VA_ARGS__);	\
})
#else
#define PRINT_ERROR(fmt, ...)					\
log_print(LOG_LEVEL_ERROR " %s(%d): " fmt,			\
			__FILE_NAME__, __LINE__, ##__VA_ARGS__)
#define PRINT_WARN(fmt, ...)					\
log_print(LOG_LEVEL_WARN " %s(%d): " fmt,			\
			__FILE_NAME__, __LINE__, ##__VA_ARGS__)
#endif

#ifdef DEBUG_PRINT_EN
#ifdef ANDROID
#define PRINT_DEBUG(fmt, ...)					\
({								\
log_print(LOG_LEVEL_DEBUG " %s(%d): " fmt,			\
			__FILE_NAME__, __LINE__, ##__VA_ARGS__);	\
android_log_print(ANDROID_LOG_DEBUG, " %s(%d): " fmt,		\
			__FILE_NAME__, __LINE__, ##__VA_ARGS__)	\
})
#else
#define PRINT_DEBUG(fmt, ...)					\
log_print(LOG_LEVEL_DEBUG " %s(%d): " fmt,			\
			__FILE_NAME__, __LINE__, ##__VA_ARGS__)
#endif
#else
#define PRINT_DEBUG(fmt, ...)
#endif

#define PRINT_INFO(fmt, ...)					\
log_print(LOG_LEVEL_INFO " %s(%d): " fmt,			\
			__FILE_NAME__, __LINE__, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif
#endif /* _RDLOG_H_ */
