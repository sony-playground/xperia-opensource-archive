/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize the display
 * @returns FCSERR_OK on success.
 */
int fcsgfx_init(void);

/**
 * Deinitialize the display
 * @param[in] clear	If set to true the display will
 *			be cleared. If false the printouts
 *			will remain on the display, but
 *			no new printouts will be displayed.
 * @returns FCSERR_OK on success.
 */
int fcsgfx_deinit(bool clear);

/**
 * Print "Ready" at the status segment of the display.
 * @returns FCSERR_OK on success.
 */
int fcsgfx_ready(void);

/**
 * Print "Working! Do not disconnect target." at the
 * status segment of the display.
 * @returns FCSERR_OK on success.
 */
int fcsgfx_running(void);

/**
 * Prints a string to the display.
 * @param[in] s		String to be printed
 * @param[in] newline	If true new line will be added at
 *			the end of the string s.
 * @returns FCSERR_OK on success.
 */
int fcsgfx_log(char *s, bool newline);

#ifdef __cplusplus
}
#endif
