#include <stdio.h>
#include <stdlib.h>

static char *
hostname(void)
{
	char hostname[HOST_NAME_MAX];
	FILE *fp = fopen("/proc/sys/kernel/hostname", "r");

	if (fp == NULL) {
		fprintf(stderr, "Could not open hostname file: %s\n",
						strerror(errno));
		return smprintf(UNKNOWN_STR);
	}

	fgets(hostname, sizeof(hostname), fp);
	/* FIXME: needs improvement */
	memset(&hostname[strlen(hostname)-1], '\0',
		sizeof(hostname) - strlen(hostname));
	fclose(fp);
	return smprintf("%s", hostname);
}
