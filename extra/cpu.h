#include <stdio.h>

static char *
cpu_perc(void)
{
	int perc;
	long double a[4], b[4];
	FILE *fp = fopen("/proc/stat","r");

	if (fp == NULL) {
		fprintf(stderr, "Error opening stat file: %s\n",
						strerror(errno));
		return smprintf(UNKNOWN_STR);
	}

	fscanf(fp, "%*s %Lf %Lf %Lf %Lf", &a[0], &a[1], &a[2], &a[3]);
	fclose(fp);

	/* wait a second (for avg values) */
	sleep(1);

	fp = fopen("/proc/stat","r");
	if (fp == NULL) {
		fprintf(stderr, "Error opening stat file: %s\n",
						strerror(errno));
		return smprintf(UNKNOWN_STR);
	}

	fscanf(fp, "%*s %Lf %Lf %Lf %Lf", &b[0], &b[1], &b[2], &b[3]);
	fclose(fp);
	perc = 100 * ((b[0]+b[1]+b[2]) - (a[0]+a[1]+a[2])) / ((b[0]+b[1]+b[2]+b[3]) - (a[0]+a[1]+a[2]+a[3]));
	return smprintf("%d%%", perc);
}
