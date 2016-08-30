static char *
run_command(const char* command)
{
	int good;
	FILE *fp = popen(command, "r");
	char buffer[64];

	if (fp == NULL) {
		fprintf(stderr, "Could not get command output for: %s: %s\n",
						command, strerror(errno));
		return smprintf(UNKNOWN_STR);
	}

	fgets(buffer, sizeof(buffer)-1, fp);
	pclose(fp);
	for (int i = 0 ; i != sizeof(buffer); i++) {
		if (buffer[i] == '\0') {
			good = 1;
			break;
		}
	}
	if (good)
		buffer[strlen(buffer)-1] = '\0';
	return smprintf("%s", buffer);
}
