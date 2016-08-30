static char *
uid(void)
{
	/* FIXME: WHY USE register modifier? */
	register uid_t uid;

	uid = geteuid();

	if (uid)
		return smprintf("%d", uid);
	else {
		fprintf(stderr, "Could not get uid.\n");
		return smprintf(UNKNOWN_STR);
	}

	return smprintf(UNKNOWN_STR);
}
