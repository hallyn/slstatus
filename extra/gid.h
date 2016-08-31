#include <unistd.h>

static char *
gid(void)
{
	gid_t gid = getgid();
	return smprintf("%d", gid);
}
