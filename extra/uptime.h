#include <sys/sysinfo.h>

static char *
uptime(void)
{
	struct sysinfo info;
	int hours = 0;
	int minutes = 0;

	sysinfo(&info);
	hours = info.uptime / 3600;
	minutes = (info.uptime - hours * 3600 ) / 60;

	return smprintf("%dh %dm", hours, minutes);
}
