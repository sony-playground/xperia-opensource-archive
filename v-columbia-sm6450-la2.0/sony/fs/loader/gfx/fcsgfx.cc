/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "fcsgfx.h"
#include <fcntl.h>
#include <time.h>
#include <pthread.h>
#include <linux/input.h>
#include <string.h>
#include <minui.h>
#include <unistd.h>
#include <errno.h>
#include <semaphore.h>
#include <signal.h>
#include <time.h>

extern "C" {
#include "fcserr.h"
#include <fcslog.h>
#include "fcsenv_def.h"
#include "protocol_util.h"
#include "ta_interface.h"
}

/* Display layout
 * ------------------------------
 * |HEADER SEGMENT		|
 * |.LOGS...			|
 * |.LOGS...			|
 * |.LOGS...			|
 * |.LOGS...			|
 * |.	STATUS SEGMENT		|
 * |.				|
 * |STATIC SEGMENT		|
 * ------------------------------
 */
/* Maximum number of lines kept in the log buffer*/
#define MAX_NBLINES 2048
/* Number of lines for the header segment*/
#define HEAD_NBLINES 4
/* Number of lines for the status segment*/
#define STATUS_NBLINES 5
/* Number of lines for the static segment*/
#define STATIC_NBLINES 2
/* Number of lines by which the log will be scrolled */
#define NB_SCROLL_LINES 2
/* Number of seconds after which the display brightness
 * will be decreased to 0 if there is no activity */
#define DISPLAY_DIMMING_TIME 300

#define MAX(x, y) ((x) > (y)?(x):(y))
#define MIN(x, y) ((x) < (y)?(x):(y))

enum fcsgfx_color {
	BLACK,
	WHITE,
	BLUE,
	YELLOW,
	RED,
	GREEN
};

enum fcsgfx_buffer_type {
	FCSGFX_HEAD_BUF = 0,
	FCSGFX_LOG_BUF,
	FCSGFX_STATUS_BUF,
	FCSGFX_STATIC_BUF,
	FCSGFX_NBR_BUF
};

enum {
	FCSGFX_STATE_RUNNING,
	FCSGFX_STATE_READY
};

/*Overwriting circular buffer*/
struct log_buffer {
	char *line[MAX_NBLINES];
	int head;
	bool wrap;
	size_t line_length;
	int nb_rows;
	int vpos;
};

struct print_buffer {
	char *buf;
	int nb_lines;
	size_t size;
};

struct fcsgfx_context {
	int char_w;
	int char_h;
	int fb_w; /* frame buffer width */
	int fb_h; /* frame buffer height */
	int cols;
	int state;
	print_buffer print_buf[FCSGFX_NBR_BUF];
	log_buffer log_buf;
	bool init_done;
	timer_t disp_timer_id;
	bool disp_br_on;
};

static void fcsgfx_set_disp_timer(void);

static pthread_t ptchild;
static pthread_t ptchild_key;
static pthread_mutex_t fcsgfx_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t display_update_done = PTHREAD_COND_INITIALIZER;
static sem_t sem;

static struct fcsgfx_context fcsgfx_ctx = {};

/**
 * Signal handler used to exit the fcsgfx threads.
 * @param[in]	sig_num	Only SIGUSR1 is supported.
 * @returns none.
 */
static void thread_cancel_signal_handler(int sig_num)
{
	if (sig_num == SIGUSR1)
		pthread_exit(0);
}

/**
 * Signal handler registration function.
 * @returns none.
 */
static void register_thread_signal_handler()
{
	struct sigaction action;
	memset(&action, 0, sizeof(action));
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	action.sa_handler = &thread_cancel_signal_handler;

	sigaction(SIGUSR1, &action, NULL);
}

/**
 * Init the log buffer.
 * @param[in] line_length	Number of characters that can be
 *			 	printed on one line of the display.
 * @returns FCSERR_OK on success.
 */
static int init_logbuf(int line_length)
{
	for (int i = 0; i < MAX_NBLINES; i++) {
		fcsgfx_ctx.log_buf.line[i] = (char*)calloc(1, line_length);
		if (fcsgfx_ctx.log_buf.line[i] == NULL) {
			FCS_LOG_ERR("Memory allocation fail\n");
			return -FCSERR_ENOMEM;
		}
	}

	fcsgfx_ctx.log_buf.head = 0;
	fcsgfx_ctx.log_buf.wrap = false;
	fcsgfx_ctx.log_buf.line_length = line_length;
	fcsgfx_ctx.log_buf.nb_rows = (fcsgfx_ctx.fb_h / fcsgfx_ctx.char_h) -
			HEAD_NBLINES - STATIC_NBLINES - STATUS_NBLINES;
	fcsgfx_ctx.log_buf.vpos = 0;

	return FCSERR_OK;
}

/**
 * Init a print buffer.
 * @param[in] pos	Type of buffer to be initialized.
 *			See enum fcsgfx_buffer_type.
 * @returns FCSERR_OK on success.
 */
static int init_print_buf(int pos)
{
	int nb_lines = 0;

	switch (pos) {
	case FCSGFX_HEAD_BUF:
		nb_lines = HEAD_NBLINES;
		break;
	case FCSGFX_LOG_BUF:
		nb_lines = fcsgfx_ctx.log_buf.nb_rows;
		break;
	case FCSGFX_STATUS_BUF:
		nb_lines = STATUS_NBLINES;
		break;
	case FCSGFX_STATIC_BUF:
		nb_lines = STATIC_NBLINES;
		break;
	default:
		return -FCSERR_EINVAL;
	}

	fcsgfx_ctx.print_buf[pos].buf = (char *)calloc(1, nb_lines * fcsgfx_ctx.cols);

	if (fcsgfx_ctx.print_buf[pos].buf == NULL) {
		FCS_LOG_ERR("Memory allocation fail\n");
		return -FCSERR_ENOMEM;
	}

	fcsgfx_ctx.print_buf[pos].nb_lines = nb_lines;
	fcsgfx_ctx.print_buf[pos].size = nb_lines * fcsgfx_ctx.cols;

	return FCSERR_OK;
}

/**
 * Set an RGBA color
 * @param[in] col Color to be set
 * @returns FCSERR_OK on success.
 */
static void fcsgfx_setcolor(int col)
{
	switch (col) {
	case BLACK:
		gr_color(0, 0, 0, 255);
		break;
	case WHITE:
		gr_color(255, 255, 255, 255);
		break;
	case BLUE:
		gr_color(0, 191, 255, 255);
		break;
	case YELLOW:
		gr_color(255, 195, 0, 255);
		break;
	case RED:
		gr_color(255, 0, 0, 255);
		break;
	case GREEN:
		gr_color(0, 255, 0, 255);
		break;
	default:
		break;
	}
}

/**
 * Get number of rows in a string buffer.
 *
 * @param[in]	str 	Null terminated string buffer.
 * @param[out]	nrows	Number of rows in str.
 *
 * @returns FCSERR_OK on success.
 */
static int fcsgfx_get_nrows(const char *str, int *nrows)
{
	int i = 0;
	if (str == NULL || nrows == NULL) {
		FCS_LOG_ERR("Invalid input \n");
		return -FCSERR_EINVAL;
	}

	*nrows = 0;
	/* Find the number of new lines in the text buffer */
	while (str[i] != '\0') {
		if (str[i] == '\n')
			(*nrows)++;
		i++;
	}
	return FCSERR_OK;
}

/**
 * Add a string to a print buffer.
 * @param[in] str	String to be added.
 * @param[in] pos	Index of the print buffer.
 * @param[in] clr	Clear the complete buffer before
 * 			adding the string.
 * @returns FCSERR_OK on success.
 */
static int fcsgfx_add_text(const char *str, int pos, bool clr)
{
	int res;
	int buf_eol_count = 0;
	int str_eol_count = 0;
	char *cpos;
	int diff;
	char *text_buffer;
	int max_len = 0;
	int shift_size;

	if (str == NULL)
		return -FCSERR_EINVAL;

	if (clr) {
		free(fcsgfx_ctx.print_buf[pos].buf);
		fcsgfx_ctx.print_buf[pos].buf = NULL;
	}

	if (fcsgfx_ctx.print_buf[pos].buf == NULL) {
		res = init_print_buf(pos);
		if (res != FCSERR_OK)
			return res;
	}

	text_buffer = fcsgfx_ctx.print_buf[pos].buf;

	/* Find the number of new lines in the print text buffer
	 * and in the string that should be added */
	res = fcsgfx_get_nrows(text_buffer, &buf_eol_count);
	if (res != FCSERR_OK)
		return res;

	res = fcsgfx_get_nrows(str, &str_eol_count);
	if (res != FCSERR_OK)
		return res;

	/* FIFO with fcsgfx_ctx.print_buf[pos].nb_lines
	 * Remove the first lines and move the content
	 * to the beginning of the buffer*/
	if (buf_eol_count + str_eol_count >
			fcsgfx_ctx.print_buf[pos].nb_lines) {
		do {
			cpos = strchr(text_buffer, '\n');
			if (cpos == NULL)
				break;
			cpos++;
			diff = (int)(cpos - text_buffer);
			shift_size = fcsgfx_ctx.print_buf[pos].size - diff;
			memmove(text_buffer, cpos, shift_size);
			text_buffer[shift_size] = '\0';
			str_eol_count--;
		} while (str_eol_count > 0);
	}

	max_len = fcsgfx_ctx.print_buf[pos].size -
			strlen(text_buffer) - 1;

	strncat(text_buffer, str, strnlen(str, max_len));

	sem_post(&sem);

	return FCSERR_OK;
}

/**
 * Draw a print buffer to the display.
 * @param[in] pos	Index of the print buffer.
 * @returns none.
 */
static void fcsgfx_draw_buf(int pos)
{
	int x;
	int y;
	char *tbuf = fcsgfx_ctx.print_buf[pos].buf;
	int ptrlen;
	int buflen = strlen(fcsgfx_ctx.print_buf[pos].buf);
	char *ptr;
	char *ptr1;
	char *str;
	fcsgfx_color color;
	bool bold = false;

	if (tbuf == NULL)
		return;

	str = (char *)malloc(fcsgfx_ctx.cols + 1);
	if (str == NULL)
		return;

	switch (pos) {
	case FCSGFX_HEAD_BUF:
		color = BLUE;
		x = 0;
		y = 0;
		break;
	case FCSGFX_LOG_BUF:
		color = WHITE;
		x = 0;
		y = fcsgfx_ctx.char_h * HEAD_NBLINES;
		break;
	case FCSGFX_STATIC_BUF:
		bold = true;
		color = BLUE;
		x = 0;
		y = fcsgfx_ctx.fb_h - STATIC_NBLINES * fcsgfx_ctx.char_h;
		break;
	case FCSGFX_STATUS_BUF:
		if (fcsgfx_ctx.state == FCSGFX_STATE_READY)
			color = GREEN;
		else
			color = RED;

		x = (fcsgfx_ctx.fb_w - (buflen + 1) * fcsgfx_ctx.char_w) / 2;
		y = fcsgfx_ctx.char_h *
				(HEAD_NBLINES + fcsgfx_ctx.log_buf.nb_rows + STATIC_NBLINES);
		break;
	default:
		goto exit;
	}

	if (x < 0)
		x = 0;

	/* Prepare and print the text to the display */
	ptr = tbuf;
	while (ptr != (tbuf + buflen)) {
		ptr1 = strchr(ptr, '\n');
		/* Print last row and break */
		if (ptr1 == NULL) {
			fcsgfx_setcolor(color);
			gr_text(gr_sys_font(), x, y, ptr, bold);
			break;
		}

		/* Do line feed (increase y by the character height) */
		ptrlen = ptr1 - ptr;
		if (ptrlen == 0) {
			y += fcsgfx_ctx.char_h;
			ptr = ptr + 1;
			continue;
		}

		/* Make sure we do not print outside the display */
		ptrlen = (ptrlen > fcsgfx_ctx.cols) ? fcsgfx_ctx.cols : ptrlen;

		/* Clear and copy wanted part of string */
		memset(str, 0, fcsgfx_ctx.cols + 1);
		strncpy(str, ptr, ptrlen);

		/* Do printing and line feed */
		ptr = ptr + ptrlen + 1;

		if (strncmp(str, "[ERROR", strlen("[ERROR")) == 0)
			fcsgfx_setcolor(RED);
		else
			fcsgfx_setcolor(color);

		gr_text(gr_sys_font(), x, y, str, bold);

		y += fcsgfx_ctx.char_h;

		/* Make sure we do not overwrite the
		 * static and status part of the display
		 */
		if (pos == FCSGFX_LOG_BUF &&
			y > (fcsgfx_ctx.char_h *
				(HEAD_NBLINES + fcsgfx_ctx.log_buf.nb_rows)))
			break;
	}

exit:
	free(str);
}

/**
 * Add a string to the header buffer and draw
 * it on the display.
 * @param[in] str	String to be added.
 * @returns none.
 */
static void fcsgfx_print_head(const char *str)
{
	fcsgfx_add_text(str, FCSGFX_HEAD_BUF, false);
	return;
}
/**
 * Add data to the log buffer
 * @param[in]	buf	Data to be added
 * @param[in]	nbytes	Number of bytes to be added
 */
static void fcsgfx_add_data_to_log_buf(char *buf, size_t nbytes)
{
	char *log_buffer;

	if (fcsgfx_ctx.log_buf.head == MAX_NBLINES) {
		fcsgfx_ctx.log_buf.head = 0;
		fcsgfx_ctx.log_buf.wrap = true;
	}

	log_buffer = fcsgfx_ctx.log_buf.line[fcsgfx_ctx.log_buf.head];

	memcpy(log_buffer, buf, MIN(nbytes, fcsgfx_ctx.log_buf.line_length));
	log_buffer[MIN(nbytes, fcsgfx_ctx.log_buf.line_length - 1)] = '\0';

	fcsgfx_ctx.log_buf.head++;

	return;
}
/**
 * Add a string to the log buffer and draw
 * it on the display.
 * @param[in] str	String to be added.
 * @returns none.
 */
static void fcsgfx_print(const char *str)
{
	size_t offset = 0;
	char *eol_pos = NULL;
	char *tmp_str = (char*)malloc(strlen(str) + 1);

	strncpy(tmp_str, str, strlen(str) + 1);

	/* Put every new line from the input str buffer in a
	 * separate line in the log buffer */
	do {
		eol_pos = strchr(tmp_str, '\n');
		if (eol_pos == NULL) {
			if (strlen(tmp_str) != 0)
				fcsgfx_add_data_to_log_buf(tmp_str, strlen(tmp_str) + 1);
		} else {
			eol_pos++;
			offset = eol_pos - tmp_str;
			fcsgfx_add_data_to_log_buf(tmp_str, offset);
			/* Remove the first line and move the rest of the string
			 * to the beginning */
			memmove(tmp_str, eol_pos, strlen(eol_pos) + 1);
		}
	} while (eol_pos != NULL);

	/* Draw the string if scrolling position is 0 */
	if (fcsgfx_ctx.log_buf.vpos == 0) {
		fcsgfx_add_text(str, FCSGFX_LOG_BUF, false);
	}

	sem_post(&sem);
	free(tmp_str);
	return;
}

/**
 * Copy data from the log buffer to the log print buffer,
 * depending on the current scroll position.
 * Should be called when a scrolling event is registered.
 * @returns none.
 */
static int set_print_log_buf()
{
	int nb_lines=0;
	size_t size=0;
	int i=0;
	char *p_buf = fcsgfx_ctx.print_buf[FCSGFX_LOG_BUF].buf;
	print_buffer print_buf = fcsgfx_ctx.print_buf[FCSGFX_LOG_BUF];
	int log_buf_line_len;

	if (fcsgfx_ctx.log_buf.head == 0) {
		FCS_LOG_ERR("Invalid state \n");
		return -FCSERR_EINVAL;
	}

	if (p_buf == NULL) {
		FCS_LOG_ERR("Invalid state \n");
		return -FCSERR_EINVAL;
	}

	/* Clear the current print buffer */
	memset(p_buf, '\0', fcsgfx_ctx.print_buf[FCSGFX_LOG_BUF].size);

	/* Find the start line position (i) from the log ring buffer */
	if ((fcsgfx_ctx.log_buf.head - print_buf.nb_lines - fcsgfx_ctx.log_buf.vpos) > 0)
		i = fcsgfx_ctx.log_buf.head - print_buf.nb_lines - fcsgfx_ctx.log_buf.vpos;
	else if (fcsgfx_ctx.log_buf.wrap) {
		i = MAX((MAX_NBLINES - fcsgfx_ctx.log_buf.vpos), 0);
	}

	/* Copy the content from the log buffer to the print buffer */
	while ((nb_lines < print_buf.nb_lines)) {

		/* If the log buffer is overwritten, reset i to 0 if we
		 * reach the end of the buffer */
		if (fcsgfx_ctx.log_buf.wrap && (i >= MAX_NBLINES))
			i = 0;

		/* Check if we have reached the end of the log buffer if
		 * it is not overwritten */
		if (!fcsgfx_ctx.log_buf.wrap && i >= fcsgfx_ctx.log_buf.head)
			break;

		log_buf_line_len = strlen(fcsgfx_ctx.log_buf.line[i]);
		size += log_buf_line_len;
		/* break if the print buffer is full */
		if (size > print_buf.size)
			break;
		memcpy(p_buf, fcsgfx_ctx.log_buf.line[i], log_buf_line_len);
		nb_lines++;
		i++;
		p_buf += log_buf_line_len;
	}

	return 0;
}

/**
 * Events input callback.
 * @param[in] fd	Input file descriptor.
 * @param[in] epevents	Registered events.
 * @returns FCSERR_OK on success.
 */
static int input_callback(int fd, uint32_t epevents)
{
	struct input_event ev;
	int ret = FCSERR_OK;
	int vpos_max;
	bool update = false;

	/* Check if an input event is registered*/
	if (ev_get_input(fd, epevents, &ev) == -1) {
		return -1;
	}

	fcsgfx_set_disp_timer();

	pthread_mutex_lock(&fcsgfx_mutex);
	if (ev.code == KEY_VOLUMEUP) {
		/* Increase the scroll position (vpos) if
		 * a volume up event is registered */
		if (fcsgfx_ctx.log_buf.wrap)
			vpos_max = MAX_NBLINES -
				fcsgfx_ctx.log_buf.head % MAX_NBLINES;
		else
			vpos_max = fcsgfx_ctx.log_buf.head -
				fcsgfx_ctx.print_buf[FCSGFX_LOG_BUF].nb_lines;

		if (fcsgfx_ctx.log_buf.vpos < vpos_max) {
			fcsgfx_ctx.log_buf.vpos += NB_SCROLL_LINES;
			update = true;
		}
	}

	/* Decrease the scroll position (vpos) if
	 * a volume down event is registered */
	if (ev.code == KEY_VOLUMEDOWN && (fcsgfx_ctx.log_buf.vpos > 0)) {
		fcsgfx_ctx.log_buf.vpos -= NB_SCROLL_LINES;
		update = true;
	}

	if (update) {
		ret = set_print_log_buf();
		if (ret == FCSERR_OK) {
			sem_post(&sem);
		}
	}
	pthread_mutex_unlock(&fcsgfx_mutex);
	return ret;
}
/**
 * Display timer handler that will be executed
 * when the timer expires.
 * @param[in]	signum	The number of the signal that is raised
 * 			when the timer expires.
 * @returns none.
 */
static void fcsgfx_disp_timer_handler(int signum)
{
	int fd;
	int ret;

	if (signum != SIGALRM)
		return;

	/* Set the display brightness */
	fd = open(DISPLAY_BRIGHTNESS, O_WRONLY);
	if (fd < 0) {
		FCS_LOG_ERR("Failed to open %s\n", DISPLAY_BRIGHTNESS);
		return;
	}

	ret = write(fd, BRIGHTNESS_OFF, sizeof(BRIGHTNESS_OFF));
	if (ret <= 0)
		FCS_LOG_ERR("Failed to write to %s\n", DISPLAY_BRIGHTNESS);
	else
		fcsgfx_ctx.disp_br_on = false;

	close(fd);
	return;
}

/**
 * Set the timer interval.
 * @returns none.
 */
static void fcsgfx_set_disp_timer(void)
{
	int fd;
	int ret;
	struct itimerspec interval;

	interval.it_value.tv_sec = DISPLAY_DIMMING_TIME;
	interval.it_value.tv_nsec = 0;
	interval.it_interval.tv_sec = 0;
	interval.it_interval.tv_nsec = 0;

	timer_settime(fcsgfx_ctx.disp_timer_id, 0, &interval, NULL);

	/* Turn on the display brightness if it is off */
	if (!fcsgfx_ctx.disp_br_on) {
		fd = open(DISPLAY_BRIGHTNESS, O_WRONLY);
		if (fd < 0) {
			FCS_LOG_ERR("Failed to open %s\n", DISPLAY_BRIGHTNESS);
			return;
		}

		ret = write(fd, BRIGHTNESS_LEVEL, sizeof(BRIGHTNESS_LEVEL));
		if (ret <= 0)
			FCS_LOG_ERR("Failed to write to %s\n", DISPLAY_BRIGHTNESS);
		else
			fcsgfx_ctx.disp_br_on = true;

		close(fd);
	}

	return;
}

/**
 * Thread function used for drawing to the display.
 * @param[in] arg	Thread arguments.
 * @returns none.
 */
static void *fcsgfx_worker(void *arg)
{
	(void)arg;
	int sval;
	int i;

	register_thread_signal_handler();

	while (1) {
		/* Drawing to the display line by line can be
		 * a slow operation, so only draw when the
		 * semaphore count reaches 0 */
		sem_wait(&sem);
		sem_getvalue(&sem, &sval);

		if (sval == 0) {
			/* Restart the display timer */
			fcsgfx_set_disp_timer();

			fcsgfx_setcolor(BLACK);
			gr_clear();

			for (i = 0; i < FCSGFX_NBR_BUF; i++) {
				if (fcsgfx_ctx.print_buf[i].buf == NULL)
					continue;

				fcsgfx_draw_buf(i);
			}

			gr_flip();
			if (!fcsgfx_ctx.init_done)
				pthread_cond_signal(&display_update_done);

		}
	}
	return NULL;
}

/**
 * Thread function used for waiting for an input event.
 * @param[in] arg	Thread arguments.
 * @returns none.
 */
static void *fcsgfx_worker_key(void *arg) {

	(void)arg;

	register_thread_signal_handler();

	while (true) {
		if (!ev_wait(-1)) {
			ev_dispatch();
		}
	}

	return NULL;
}

int fcsgfx_init()
{
	int ret;
	int fd = -1;
	char *footer = NULL;
	char boot_version[256];
	char ta_disp[2];
	struct sigaction sig;

	if (fcsgfx_ctx.init_done)
		return FCSERR_OK;

	ret = get_miscta_unit_data(
			TA_XFL_ENABLE_DISPLAY, ta_disp, sizeof(ta_disp));

	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Failed to read from MiscTA\n");
		goto exit;
	}

	if (ta_disp[0] != 0x01) {
		FCS_LOG_ERR("Display not enabled\n");
		ret = -FCSERR_EACCES;
		goto exit;
	}

	sem_init(&sem, 0, 0);
	memset(&sig, 0, sizeof(struct sigaction));
	sig.sa_handler = fcsgfx_disp_timer_handler;
	sig.sa_flags = SA_RESTART;
	sigaction(SIGALRM, &sig, NULL);
	timer_create(CLOCK_REALTIME, NULL, &fcsgfx_ctx.disp_timer_id);

	/* Init the input event callback and thread */
	ev_init(input_callback, false);

	ret = pthread_create(&ptchild_key, NULL, &fcsgfx_worker_key, (void *)NULL);
	if (0 != ret) {
		FCS_LOG_ERR("pthread_create fail (errno=%d)\n", errno);
		ret = -FCSERR_ESTATE;
		goto exit;
	}

	if (gr_init() < 0) {
		ret = -FCSERR_ESTATE;
		FCS_LOG_ERR("gr_init failed\n");
		goto exit;
	}

	/* Set display brightness */
	fd = open(DISPLAY_BRIGHTNESS, O_WRONLY);
	if (fd < 0) {
		FCS_LOG_ERR("Failed to open %s\n", DISPLAY_BRIGHTNESS);
		ret = -FCSERR_EOPEN;
		goto exit;
	}

	ret = write(fd, BRIGHTNESS_LEVEL, sizeof(BRIGHTNESS_LEVEL));
	if (ret <= 0) {
		FCS_LOG_ERR("Failed to write to %s\n", DISPLAY_BRIGHTNESS);
		ret = -FCSERR_EIO;
		goto exit;
	}

	fcsgfx_ctx.disp_br_on = true;
	gr_font_size(gr_sys_font(), &fcsgfx_ctx.char_w, &fcsgfx_ctx.char_h);
	fcsgfx_ctx.fb_w = gr_fb_width();
	fcsgfx_ctx.fb_h = gr_fb_height();
	fcsgfx_ctx.cols = fcsgfx_ctx.fb_w / fcsgfx_ctx.char_w;
	pthread_mutex_lock(&fcsgfx_mutex);
	fcsgfx_ctx.state = FCSGFX_STATE_READY;
	pthread_mutex_unlock(&fcsgfx_mutex);
	fcsgfx_setcolor(BLACK);
	gr_clear();

	ret = init_logbuf(fcsgfx_ctx.fb_w / fcsgfx_ctx.char_w);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("init_logbuf fail\n");
		goto exit;
	}

	ret = get_miscta_unit_data(
			TA_S1_BOOT_VERSION_UNIT, boot_version, sizeof(boot_version));

	if (ret == FCSERR_OK) {
		asprintf(&footer, "%s%s\n%s%s", "Xboot ver:", boot_version,
				"XFL ver:", BUILD_NUMBER);
	}
	else
		asprintf(&footer, "\n%s%s%s", "XFL ver:", BUILD_NUMBER, "\n");

	fcsgfx_ctx.init_done = true;

	ret = pthread_create(&ptchild, NULL, &fcsgfx_worker, (void *)NULL);
	if (0 != ret) {
		FCS_LOG_ERR("pthread_create fail (errno=%d)\n", errno);
		ret = -FCSERR_ESTATE;
		goto exit;
	}

	ret = fcsgfx_add_text(footer, FCSGFX_STATIC_BUF, false);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("fcsgfx_add_text fail (%d)\n", ret);
		goto exit;
	}

	fcsgfx_print_head("\nXperia Flash Loader\n");
	fcsgfx_print_head("\n-------------------\n");

exit:
	if (ret == FCSERR_OK)
		fcsgfx_ctx.init_done = true;
	else
		fcsgfx_ctx.init_done = false;

	if (fd != -1)
		close(fd);

	if (footer)
		free(footer);

	return ret;
}

int fcsgfx_deinit(bool clear)
{
	int ret;

	if (fcsgfx_ctx.init_done == false)
		return FCSERR_OK;

	pthread_mutex_lock(&fcsgfx_mutex);
	fcsgfx_ctx.state = FCSGFX_STATE_READY;
	ret = fcsgfx_add_text("\nNow it is safe to disconnect the device\n",
			FCSGFX_STATUS_BUF, true);

	fcsgfx_ctx.init_done = false;
	/* Wait until the last buffer is printed */
	pthread_cond_wait(&display_update_done, &fcsgfx_mutex);
	if (clear) {
		/* Exit the input and display threads*/
		pthread_kill(ptchild, SIGUSR1);
		pthread_kill(ptchild_key, SIGUSR1);
		sem_destroy(&sem);

		/* Clear and power down the display */
		fcsgfx_setcolor(BLACK);
		gr_clear();
		gr_flip();
		gr_exit();
		ev_exit();

		for (int i = 0; i < FCSGFX_NBR_BUF; i++) {
			if (fcsgfx_ctx.print_buf[i].buf != NULL) {
				free(fcsgfx_ctx.print_buf[i].buf);
				fcsgfx_ctx.print_buf[i].buf = NULL;
			}
		}

		for (int i = 0; i < MAX_NBLINES; i++) {
			if (fcsgfx_ctx.log_buf.line[i] != NULL) {
				free(fcsgfx_ctx.log_buf.line[i]);
				fcsgfx_ctx.log_buf.line[i] = NULL;
			}
		}
		fcsgfx_ctx.disp_br_on = false;
		timer_delete(fcsgfx_ctx.disp_timer_id);
		signal(SIGALRM, SIG_DFL);
	}

	pthread_mutex_unlock(&fcsgfx_mutex);
	return ret;
}

int fcsgfx_ready()
{
	int ret;

	if (fcsgfx_ctx.init_done == false)
		return -FCSERR_ESTATE;

	pthread_mutex_lock(&fcsgfx_mutex);
	fcsgfx_ctx.state = FCSGFX_STATE_READY;
	ret = fcsgfx_add_text("\nReady\n", FCSGFX_STATUS_BUF, true);
	pthread_mutex_unlock(&fcsgfx_mutex);
	return ret;
}

int fcsgfx_running()
{
	int ret;

	if (fcsgfx_ctx.init_done == false)
		return -FCSERR_ESTATE;

	pthread_mutex_lock(&fcsgfx_mutex);
	fcsgfx_ctx.state = FCSGFX_STATE_RUNNING;
	ret = fcsgfx_add_text("\nWorking! Do not disconnect target.\n",
			FCSGFX_STATUS_BUF, true);
	pthread_mutex_unlock(&fcsgfx_mutex);
	return ret;
}

int fcsgfx_log(char *s, bool newline)
{
	char *log = NULL;
	int ret;

	if (fcsgfx_ctx.init_done == false)
		return -FCSERR_ESTATE;

	/* fcsgfx_log can be called from FCS_LOG_ERR while the
	 * mutex is already acquired. Do not draw to the
	 * display if the mutex can't be locked */
	ret = pthread_mutex_trylock(&fcsgfx_mutex);
	if (ret != 0)
		return -FCSERR_ESTATE;

	if (newline) {
		ret = asprintf(&log, "%s\n", s);
		if (ret == -1) {
			pthread_mutex_unlock(&fcsgfx_mutex);
			return -FCSERR_ENOMEM;
		}
		fcsgfx_print(log);
	} else
		fcsgfx_print(s);

	pthread_mutex_unlock(&fcsgfx_mutex);

	if (log)
		free(log);

	return FCSERR_OK;
}
