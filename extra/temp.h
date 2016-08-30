static char *
temp(const char *file)
{
	int temperature;
	FILE *fp = fopen(file, "r");

	if (fp == NULL) {
		fprintf(stderr, "Could not open temperature file: %s\n",
							strerror(errno));
		return smprintf(UNKNOWN_STR);
	}

	fscanf(fp, "%d", &temperature);
	fclose(fp);
	return smprintf("%d°C", temperature / 1000);
}
