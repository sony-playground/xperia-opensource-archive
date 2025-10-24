/*
 * Open a GPT table and show the slot flags and whether GUIDs are active
 * or inactive.
 */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>

#define GPT_ENTRY_SIZE (128)
#define GPT_MAGIC_SIZE (8)
#define GPT_PART_ID_SIZE (16)
#define GPT_MAX_NAME_SIZE (72)

#define SLOT_ATTR_PRIORITY_BIT (48)
#define SLOT_ATTR_ACTIVE_BIT (50)
#define SLOT_ATTR_MAX_RETRY_BIT (51)
#define SLOT_ATTR_SUCCESSFUL_BIT (54)
#define SLOT_ATTR_UNBOOTABLE_BIT (55)
#define PRIORITY ((uint64_t)0x3 << SLOT_ATTR_PRIORITY_BIT)
#define ACTIVE ((uint64_t)0x1 << SLOT_ATTR_ACTIVE_BIT)
#define MAX_RETRY ((uint64_t)0x7 << SLOT_ATTR_MAX_RETRY_BIT)
#define SUCCESSFUL ((uint64_t)0x1 << SLOT_ATTR_SUCCESSFUL_BIT)
#define UNBOOTABLE ((uint64_t)0x1 << SLOT_ATTR_UNBOOTABLE_BIT)

uint8_t tama_inactive[] =  /* 77036CD4-03D5-42BB-8ED1-37E5A88BAA34 */
{0xd4, 0x6c, 0x03, 0x77, 0xd5, 0x03, 0xbb, 0x42,
	0x8e, 0xd1, 0x37, 0xe5, 0xa8, 0x8b, 0xaa, 0x34};

struct gpt_part_info {
	uint8_t guid_type[GPT_PART_ID_SIZE];
	uint8_t guid_id[GPT_PART_ID_SIZE];
	uint64_t start;
	uint64_t end;
	uint64_t attribute;
	char _name[GPT_MAX_NAME_SIZE];
	char name[GPT_MAX_NAME_SIZE / 2];
};

struct gpt_header {
	char magic[GPT_MAGIC_SIZE];
	uint32_t revision;
	uint32_t hdr_size;
	uint32_t hdr_crc;
	uint32_t reserved;
	uint64_t lba_cur;
	uint64_t lba_bkp;
	uint64_t lba_1st;
	uint64_t lba_lst;
	uint8_t disk_guid[GPT_PART_ID_SIZE];
	uint64_t lba_part_entries;
	uint32_t nbr_part;
	uint32_t size_part_entry;
	uint32_t pa_crc;
};

static int is_slot(char *part, size_t partlen)
{
	int i;

	if (!part || partlen < 3)
		return 0;

	for (i = 0; i < partlen + 1; i++) {
		if (part[i] == '_' && (part[i+1] == 'a' || part[i+1] == 'b'))
			return 1;
	}

	return 0;
}

static uint64_t swap64(uint64_t x)
{
	x = (x & 0x00000000FFFFFFFF) << 32 | (x & 0xFFFFFFFF00000000) >> 32;
	x = (x & 0x0000FFFF0000FFFF) << 16 | (x & 0xFFFF0000FFFF0000) >> 16;
	x = (x & 0x00FF00FF00FF00FF) << 8  | (x & 0xFF00FF00FF00FF00) >> 8;
	return x;
}

int main(int argc, char *argv[])
{
	int res, i, j, retry, prio;
	size_t read;
	FILE *fpi = NULL;
	struct gpt_header gpth;
	struct gpt_part_info *plist = NULL;

	if (argc < 2) {
		fpi = fopen("partition-image-LUN0.bin", "r");
	} else if (argc == 2) {
		fpi = fopen(argv[1], "r");
	} else {
		printf("Give Zero or One input parameters. If no parameters\n");
		printf("given it will try to open partition-image-LUN0.bin.");
		return 0;
	}

	if (fpi == NULL) {
		printf("Failed to open file, errno=%d\n", errno);
		return -1;
	}

	res = fseek(fpi, 0x1000, SEEK_SET);
	if (res < 0) {
		printf("Failed to seek, errno=%d\n", errno);
		goto exit;
	}

	read = fread(&gpth, sizeof(gpth), 1, fpi);
	if (read < 1) {
		printf("Failed to read data, read=%zd, errno=%d\n",
				read, errno);
		res = -1;
		goto exit;
	}

	if (strncmp(gpth.magic, "EFI PART", 8)) {
		printf("Not gpt header\n");
		goto exit;
	}

	printf("Number of partitions: %d, only list those with slots below\n",
			gpth.nbr_part);
	/* Some kind of sanity check */
	if (gpth.nbr_part < 1 || gpth.nbr_part > 128) {
		printf("Something wrong, too many partitions\n");
		goto exit;
	}

	plist = malloc((GPT_ENTRY_SIZE + 128/2)*gpth.nbr_part);
	if (!plist) {
		printf("Out of memory\n");
		goto exit;
	}

	/* Jump to partition table */
	res = fseek(fpi, 0x2000, SEEK_SET);
	if (res < 0) {
		printf("Failed to seek, errno=%d\n", errno);
		goto exit;
	}

	printf("PART\tATTRIBUTE\t ACTIVE\tSUCC\tUNBOOT\t");
	printf("RETRY\tPRIO\tGUID\tNAME\n");
	printf("------------------------------------------------------");
	printf("--------------------------------\n");
	for (i = 0; i < gpth.nbr_part; i++) {
		read = fread(&plist[i], GPT_ENTRY_SIZE, 1, fpi);
		if (read < 1) {
			printf("Failed to read: i=%d read=%zd errno=%d",
					i, read, errno);
			goto exit;
		}

		j = 0;
		while (j < GPT_MAX_NAME_SIZE) {
			plist[i].name[j/2] = plist[i]._name[j];
			if (plist[i]._name[j] == '\0')
				break;
			j++;
			j++;
		}
		if (is_slot(plist[i].name, strlen(plist[i].name))) {
			/* Position in partition list */
			printf("%2d\t", i);

			/* Print the full attribute field */
			printf("%.16zX", swap64(plist[i].attribute));

			/* Is partition active? */
			if (plist[i].attribute & ACTIVE)
				printf(" YES\t");
			else
				printf("  NO\t");

			/* Is partition successful? */
			if (plist[i].attribute & SUCCESSFUL)
				printf("YES\t");
			else
				printf(" NO\t");

			/* Is partition unbootable?  */
			if (plist[i].attribute & UNBOOTABLE)
				printf("YES\t");
			else
				printf(" NO\t");

			/* Get retry counter */
			retry = 7&(plist[i].attribute>>SLOT_ATTR_MAX_RETRY_BIT);
			if (retry)
				printf("%X\t", retry);
			else
				printf("\t");

			/* Get prio */
			prio = 3&(plist[i].attribute>>SLOT_ATTR_PRIORITY_BIT);
			if (prio)
				printf("%X\t", prio);
			else
				printf("\t");

			/* Check if partition is active or not */
			if (memcmp(plist[i].guid_type, &tama_inactive[0], 16))
				printf("A\t");
			else
				printf("I\t");

			/* Print partition name */
			printf("%s\n", plist[i].name);
		}
	}
	printf("------------------------------------------------------");
	printf("--------------------------------\n");
	printf("A (Active) I (Inactive)\n");
	printf("------------------------------------------------------");
	printf("--------------------------------\n");


exit:
	free(plist);
	fclose(fpi);
	if (res < 0)
		printf("Failed..\n");
}
