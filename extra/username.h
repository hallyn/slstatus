static char *
username(void)
{
	register struct passwd *pw;
	register uid_t uid;

	uid = geteuid();
	pw = getpwuid(uid);

	if (pw)
		return smprintf("%s", pw->pw_name);
	else {
		fprintf(stderr, "Could not get username: %s\n",
					strerror(errno));
		return smprintf(UNKNOWN_STR);
	}

	return smprintf(UNKNOWN_STR);
}
