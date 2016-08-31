#include <stdio.h>

static char *
entropy(void)
{
	int entropy = 0;
	FILE *fp = fopen("/proc/sys/kernel/random/entropy_avail", "r");

	if (fp == NULL) {
		fprintf(stderr, "Could not open entropy file.\n");
		return smprintf(UNKNOWN_STR);
	}

	fscanf(fp, "%d", &entropy);
	fclose(fp);
	return smprintf("%d", entropy);
}
