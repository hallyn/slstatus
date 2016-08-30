static char *
disk_free(const char *mountpoint)
{
	struct statvfs fs;

	if (statvfs(mountpoint, &fs) < 0) {
		fprintf(stderr, "Could not get filesystem info: %s\n",
						strerror(errno));
		return smprintf(UNKNOWN_STR);
	}
	return smprintf("%f", (float)fs.f_bsize * (float)fs.f_bfree / 1024 / 1024 / 1024);
}

static char *
disk_perc(const char *mountpoint)
{
	int perc = 0;
	struct statvfs fs;

	if (statvfs(mountpoint, &fs) < 0) {
		fprintf(stderr, "Could not get filesystem info: %s\n",
						strerror(errno));
		return smprintf(UNKNOWN_STR);
	}

	perc = 100 * (1.0f - ((float)fs.f_bfree / (float)fs.f_blocks));
	return smprintf("%d%%", perc);
}

static char *
disk_total(const char *mountpoint)
{
	struct statvfs fs;

	if (statvfs(mountpoint, &fs) < 0) {
		fprintf(stderr, "Could not get filesystem info: %s\n",
						strerror(errno));
		return smprintf(UNKNOWN_STR);
	}

	return smprintf("%f", (float)fs.f_bsize * (float)fs.f_blocks / 1024 / 1024 / 1024);
}

static char *
disk_used(const char *mountpoint)
{
	struct statvfs fs;

	if (statvfs(mountpoint, &fs) < 0) {
		fprintf(stderr, "Could not get filesystem info: %s\n",
						strerror(errno));
		return smprintf(UNKNOWN_STR);
	}

	return smprintf("%f", (float)fs.f_bsize * ((float)fs.f_blocks - (float)fs.f_bfree) / 1024 / 1024 / 1024);
}
