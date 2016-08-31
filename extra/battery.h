#include <stdio.h>
#include <string.h>

static char *
battery_perc(const char *battery)
{
	int now, full, perc;
	char batterynowfile[64];
	char batteryfullfile[64];
	FILE *fp;

	strlcpy(batterynowfile, BATTERY_PATH, sizeof(batterynowfile));
	strlcat(batterynowfile, battery, sizeof(batterynowfile));
	strlcat(batterynowfile, "/", sizeof(batterynowfile));
	strlcat(batterynowfile, BATTERY_NOW, sizeof(batterynowfile));

	fp = fopen(batterynowfile, "r");

	strlcpy(batteryfullfile, BATTERY_PATH, sizeof(batteryfullfile));
	strlcat(batteryfullfile, battery, sizeof(batteryfullfile));
	strlcat(batteryfullfile, "/", sizeof(batteryfullfile));
	strlcat(batteryfullfile, BATTERY_FULL, sizeof(batteryfullfile));

	if (fp == NULL ) {
		fprintf(stderr, "Error opening battery file: %s: %s\n",
						batterynowfile,
						strerror(errno));
		return smprintf(UNKNOWN_STR);
	}

	fscanf(fp, "%i", &now);
	fclose(fp);

	fp = fopen(batteryfullfile, "r");
	if (fp == NULL) {
		fprintf(stderr, "Error opening battery file: %s\n",
						strerror(errno));
		return smprintf(UNKNOWN_STR);
	}

	fscanf(fp, "%i", &full);
	fclose(fp);

	perc = now / (full / 100);

	return smprintf("%d%%", perc);
}
