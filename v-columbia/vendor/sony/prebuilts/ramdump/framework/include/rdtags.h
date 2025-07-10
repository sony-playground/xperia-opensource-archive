/*
 *  Copyright (C) 2012 Sony Mobile Communications AB.
 *  All rights, including trade secret rights, reserved.
 */

#ifndef _RDTAGS_H_
#define _RDTAGS_H_

#include <stdbool.h>

#define RDTAGS_FILE "rdtags"

/* This Function dump useful rdtags in to file stream
 * pointed by core and update written size in written
 * variable.
 *
 * Returns 0 in success, -1 when failed.
 *
 */
int rdtags_dumptags_to_core(FILE *core, unsigned int *written);


/* This function Checks the tagname is exists.
 *
 * Returns 0 in success, -1 when failed.
 */
int rdtags_tagexists(const char *tagname);

/* This function Checks the /proc/rdtags dir exists.
 *
 * Returns 0 in success, -1 when failed.
 */
int rdtags_direxists();

/* This function reads the tag and update the data and
 * data_size.
 *
 * Returns 0 in success, -1 when failed
 */
int rdtags_readtag(const char *tagname, char *data, int *data_size);

/* This function reads pstore sysfs entry, adds the tagname
 * and tagdata to a linked list.
 *
 * Returns 0 in success, -1 when failed.
 */
int rdtags_pmsg_taglist(void);

/* This function reads the tags from linked list based on boolean value
 * and returns tagdata if tagname is matched.
 *
 * Returns 0 in success, -1 when failed
 */
int rdtags_pmsg_readtag(const char *tagname, char *tagdata,
					bool multiple_tags);

/* This function free the list of pmsg tags */
void rdtags_free_pmsg_list(void);

/* This function creates the new tag with data of data_size.
 *
 * Returns 0 in success, -1 when failed.
 */
int rdtags_createtag(const char *tagname, char *data, int *data_size);


/* This function delete the tag tagname.
 *
 * Return 0 in success, -1 when failed.
 */
int rdtags_deletetag(const char *tagname);


/* This function clears the whole rdtags area.
 *
 * Returns 0 in success, -1 when failed.
 *
 */
int rdtags_clearalltags(void);


#endif
