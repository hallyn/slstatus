#include <stdio.h>
#include <stdlib.h>

static char *
load_avg(void)
{
	double avgs[3];

	if (getloadavg(avgs, 3) < 0) {
		fprintf(stderr, "Error getting load avg.\n");
		return smprintf(UNKNOWN_STR);
	}

	return smprintf("%.2f %.2f %.2f", avgs[0], avgs[1], avgs[2]);
}
