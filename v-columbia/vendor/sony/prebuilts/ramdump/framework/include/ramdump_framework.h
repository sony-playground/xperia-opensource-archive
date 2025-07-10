/*
*  Copyright (C) 2014 Sony Mobile Communications Inc.
*  All rights, including trade secret rights, reserved.
*/
#ifndef _RAMDUMP_FRAMEWORK_H_
#define _RAMDUMP_FRAMEWORK_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <tlcore.h>
#include <rdlog.h>
#include <rdtags.h>
#ifdef __cplusplus
extern "C" {
#endif
/*Structure to Initialize and configure the necessary data.
*  creator_name: Creator of the tlcore file such as ssr_dumper etc.
*  dev_type: dump is of phone or accessory.
*  dump_type: Dump is systemDumper/ssrDumper/nativeDumper etc.
*/
struct ramdump_info {
	char creator_name[TLCORE_MAX_DUMPER_NAME_SZ];	/*Tlcore creator name */
	char creator_version[TLCORE_MAX_DUMPER_VERSION_SZ]; /*Creator Version */
	enum tlcore_device_type dev_type;	/* Device Type */
	enum tlcore_dump_type dump_type;	/* Dump Type */
};

struct ramdump_scn_info {
	uint32_t section_type;	/*Section type*/
	uint32_t section_attribute;	/*Section Attribute*/
	enum tlcore_scn_data_type section_data_type;	/*Section Data type */
	enum tlcore_scn_data_fmt section_data_fmt;	/*Section Data fmt */
	char name[TLCORE_MAX_NAME_SZ_V6];	/* Name of section */
	char core_name[TLCORE_MAX_CORE_NAME_SZ];     /* Core Name of section */
};

/***********************************************************************/
/*! RAMDUMP_FAILURE tlcore not collected.
*   RAMDUMP_SUCCESS tlcore collected in internal memory or extsd.
*   RAMDUMP_NO_SPACE tlcore not collected due to no free space.
*   RAMDUMP_DECRYPT_FAIL tlcore not dumped due to decryption fail.
*/
/***********************************************************************/
#define RAMDUMP_FAILURE		(1<<0)
#define RAMDUMP_SUCCESS		(1<<1)
#define RAMDUMP_NO_SPACE	(1<<2)
#define RAMDUMP_DECRYPT_FAIL	(1<<3)

/***********************************************************************/
/*! @brief This function initializes and configures the necessary
*		environment like graphics and mounts the partitions.
*   @param[in] config_xml_path XML Path to configure settings such as
*		mount target, archiver type, dump path etc
*   @retval int 0 for success. Others for error.
*/
/***********************************************************************/
int ramdump_init(const char *config_xml_path);

/***********************************************************************/
/*! @brief Gets the time of the crash
*   @param[out] struct tm time to get the complete crashtime
*   @retval int 0 for success. Others for error.
*/
/***********************************************************************/
int ramdump_get_crashtime(struct tm *crashtime);

/***********************************************************************/
/*! @brief Adds the sections information from XML to the tlcore queue
*   @param[in] target_xml_path Path to the target XML
*   @retval int 0 for success. Others for error.
*/
/***********************************************************************/
int ramdump_add_xml(const char *target_xml_path);

/***********************************************************************/
/*! @brief Add the file information from the file path to the tlcore queue
*   @param[in] rd_scn_info Section Information needed to create section
*   @param[in] file_path File path from where data needs to be read
*   @retval int 0 for success. Others for error.
*/
/***********************************************************************/
int ramdump_add_file(struct ramdump_scn_info *rd_scn_info,
			const char *file_path);

/***********************************************************************/
/*! @brief Add the file information form the file descriptor to the tlcore queue
*   @param[in] rd_scn_info Section Information needed to create section
*   @param[in] fd File Descriptor from where data needs to be read
*   @retval int 0 for success. Others for error.
*/
/***********************************************************************/
int ramdump_add_fd(struct ramdump_scn_info *rd_scn_info, int fd);

/***********************************************************************/
/*! @brief Add the command to the tlcore queue.
*   @param[in] rd_scn_info Section Information needed to create section
*   @param[in] file_path File path from where data needs to be read
*   @retval int 0 for success. Others for error.
*/
/***********************************************************************/
int ramdump_add_cmd(struct ramdump_scn_info *rd_scn_info, const char *cmd);

/***********************************************************************/
/*! @brief Add the buffer information form buffer to the tlcore queue
*   @param[in] rd_scn_info Section Information needed to create section
*   @param[in] buffer buffer from where data needs to be read
*   @param[in] buf_size Size of the data to be added to tlcore from buffer
*   @retval int 0 for success. Others for error.
*/
/***********************************************************************/
int ramdump_add_buffer(struct ramdump_scn_info *rd_scn_info, const char *buffer,
						uint64_t buf_size);

/***********************************************************************/
/*! @brief Add the platform specific areas into tlcore queue.
*   @param[in] section_attribute to be set. Valid attributes are
*	defined in tlcore.h
*   @retval int 0 for success. Others for error.
*/
/***********************************************************************/
int ramdump_add_platform_areas(uint32_t section_attribute);

/***********************************************************************/
/*! @brief Initializes the dump directory and returns the path in dump_path.
*   This API should be called after calling ramdump_init().
*   @param[out] path of the dump directory.
*   @param[in] size of the dump_path.
*   @retval int 0 for success. Others for error.
*/
/***********************************************************************/
int ramdump_init_dump_dir(char *dump_path, size_t size);

/***********************************************************************/
/*! @brief To check if creating full dump is allowed or not
*		based security parameters and build variant
*   @retval bool TRUE if allowed FALSE if not allowed
*/
/***********************************************************************/
bool ramdump_is_full_dump_allowed(void);

/***********************************************************************/
/*! @brief starts creating the tlcore using all queued scns at one shot.
*		Should be the last call after adding all sections.
*   @retval int 0 for success. Others for error.
*/
/***********************************************************************/
int ramdump_create_tlcore(struct ramdump_info *rd_info);

/***********************************************************************/
/*! @brief This function returns the dump result.
*   @retval int dump result with which dumper has exited.
*/
/***********************************************************************/
int ramdump_get_dump_result(void);

/***********************************************************************/
/*! @brief To allow creating only partial tlcore by setting a flag.
*   @retval void
*/
/***********************************************************************/
void ramdump_skip_full_tlcore(void);

/***********************************************************************/
/*! @brief Wrap up the tlcore generation and release all the resources
*	   Should be called once all the sections are added to the tlcore
*   @retval int 0 for success. Others for error.
*/
/***********************************************************************/
int ramdump_finish();

#ifdef __cplusplus
}
#endif
#endif /* _RAMDUMP_INTERFACE_H_ */
