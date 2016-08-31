#include <time.h>

static char *
datetime(const char *timeformat)
{
	time_t t;
	char timestr[80];

	t = time(NULL);
	if (strftime(timestr, sizeof(timestr), timeformat, localtime(&t)) == 0)
		return smprintf(UNKNOWN_STR);

	return smprintf("%s", timestr);
}
