#include <stdio.h>

static char *
ram_free(void)
{
	long free;
	FILE *fp = fopen("/proc/meminfo", "r");

	if (fp == NULL) {
		fprintf(stderr, "Error opening meminfo file: %s\n",
						strerror(errno));
		return smprintf(UNKNOWN_STR);
	}

	fscanf(fp, "MemFree: %ld kB\n", &free);
	fclose(fp);
	return smprintf("%f", (float)free / 1024 / 1024);
}

static char *
ram_perc(void)
{
	int perc;
	long total, free, buffers, cached;
	FILE *fp = fopen("/proc/meminfo", "r");

	if (fp == NULL) {
		fprintf(stderr, "Error opening meminfo file: %s\n",
						strerror(errno));
		return smprintf(UNKNOWN_STR);
	}

	fscanf(fp, "MemTotal: %ld kB\n", &total);
	fscanf(fp, "MemFree: %ld kB\n", &free);
	fscanf(fp, "MemAvailable: %ld kB\nBuffers: %ld kB\n", &buffers, &buffers);
	fscanf(fp, "Cached: %ld kB\n", &cached);

	fclose(fp);
	perc = 100 * ((total - free) - (buffers + cached)) / total;
	return smprintf("%d%%", perc);
}

static char *
ram_total(void)
{
	long total;
	FILE *fp = fopen("/proc/meminfo", "r");

	if (fp == NULL) {
		fprintf(stderr, "Error opening meminfo file: %s\n",
						strerror(errno));
		return smprintf(UNKNOWN_STR);
	}

	fscanf(fp, "MemTotal: %ld kB\n", &total);
	fclose(fp);
	return smprintf("%f", (float)total / 1024 / 1024);
}

static char *
ram_used(void)
{
	long free, total, buffers, cached, used;
	FILE *fp = fopen("/proc/meminfo", "r");

	if (fp == NULL) {
		fprintf(stderr, "Error opening meminfo file: %s\n",
						strerror(errno));
		return smprintf(UNKNOWN_STR);
	}

	fscanf(fp, "MemTotal: %ld kB\n", &total);
	fscanf(fp, "MemFree: %ld kB\n", &free);
	fscanf(fp, "MemAvailable: %ld kB\nBuffers: %ld kB\n", &buffers, &buffers);
	fscanf(fp, "Cached: %ld kB\n", &cached);

	fclose(fp);
	used = total - free - buffers - cached;
	return smprintf("%f", (float)used / 1024 / 1024);
}
