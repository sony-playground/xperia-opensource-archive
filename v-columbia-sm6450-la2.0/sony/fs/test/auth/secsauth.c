/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "SECSExported.h"

const char *url = "http://safesemla.extranet.sonyericsson.com/dispatch";
const int buffersize = 8192;

#define DEBUG 0

void main(int argc, char *argv[])
{
	int ret = -1;
	unsigned int handle;
	unsigned int retval;
	unsigned int challen;
	unsigned int resplen = buffersize;
	FILE *inputfile = NULL;
	FILE *outputfile = NULL;
	unsigned char response[buffersize];
	unsigned char challenge[buffersize];
	char message[buffersize];

	if (argc != 3) {
		fprintf(stderr, "Usage: %s inputfile outputfile\n", argv[0]);
		goto leave;
	}

	inputfile = fopen(argv[1], "rb");
	if (inputfile == NULL) {
		fprintf(stderr, "Can not open input file %s, errno=%d\n",
				argv[1], errno);
		goto leave;
	}

	outputfile = fopen(argv[2], "wb");
	if (outputfile == NULL) {
		fprintf(stderr, "Can not open output file, errno=%d\n", errno);
		goto leave;
	}

	/* obtain file size */
	fseek(inputfile , 0 , SEEK_END);
	challen = ftell(inputfile);
	rewind(inputfile);
	retval = fread(challenge, challen, 1, inputfile);
	if (ferror(inputfile)) {
		fprintf(stderr, "Can not read input file, errno=%d\n", errno);
		goto leave;
	}
#if DEBUG
	int i;

	fprintf(stderr, "Read challenge:\n");
	for (i = 0; i < challen; i++)
		fprintf(stderr, "0x%X ", challenge[i]);
	fprintf(stderr, "\n");
	fflush(stderr);
#endif

	retval = SGN_GetHandle(url, NULL, &handle);
	if (retval != SECS_SUCCESS) {
		fprintf(stderr, "SGN_GetHandle failed: %d\n", retval);
		goto leave;
	}

	retval = SGN_SakeAuthenticate(challenge, challen, response,
					&resplen, handle);
	if (retval != SECS_SUCCESS) {
		fprintf(stderr, "SGN_SakeAuthenticate failed: %d\n", retval);
		retval = SGN_ReadErrorMessage(message, resplen, retval, handle);
		if (retval != SECS_SUCCESS) {
			fprintf(stderr, "SGN_ReadErrorMessage failed: %d\n",
				retval);
			goto leave;
		} else {
			fprintf(stderr, "Error message %s\n", message);
			goto leave;
		}
	}

	retval = fwrite(response, resplen, 1, outputfile);
	if (ferror(outputfile)) {
		fprintf(stderr,
		"Can not write outputfile, errno=%d, retval=%d, resplen=%d\n",
		errno, retval, resplen);
		goto leave;
	}
	ret = 0;

leave:
	if (inputfile != NULL)
		fclose(inputfile);
	if (outputfile != NULL)
		fclose(outputfile);
	exit(ret);
}
