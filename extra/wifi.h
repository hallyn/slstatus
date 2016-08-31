#include <linux/wireless.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>

static char *
wifi_perc(const char *wificard)
{
	int strength;
	char buf[255];
	char *datastart;
	char path[64];
	char status[5];
	char needle[strlen(wificard)+2];
	FILE *fp = fopen(path, "r");

	strlcpy(path, "/sys/class/net/", sizeof(path));
	strlcat(path, wificard, sizeof(path));
	strlcat(path, "/operstate", sizeof(path));

	if(fp == NULL) {
		fprintf(stderr, "Error opening wifi operstate file: %s\n",
							strerror(errno));
		return smprintf(UNKNOWN_STR);
	}

	fgets(status, 5, fp);
	fclose(fp);
	if(strcmp(status, "up\n") != 0)
		return smprintf(UNKNOWN_STR);

	fp = fopen("/proc/net/wireless", "r");
	if (fp == NULL) {
		fprintf(stderr, "Error opening wireless file: %s\n",
						strerror(errno));
		return smprintf(UNKNOWN_STR);
	}

	strlcpy(needle, wificard, sizeof(needle));
	strlcat(needle, ":", sizeof(needle));
	fgets(buf, sizeof(buf), fp);
	fgets(buf, sizeof(buf), fp);
	fgets(buf, sizeof(buf), fp);

	datastart = strstr(buf, needle);
	if (datastart != NULL) {
		datastart = strstr(buf, ":");
		sscanf(datastart + 1, " %*d   %d  %*d  %*d		  %*d	   %*d		%*d		 %*d	  %*d		 %*d", &strength);
	}

	fclose(fp);
	return smprintf("%d%%", strength);
}

static char *
wifi_essid(const char *wificard)
{
	char id[IW_ESSID_MAX_SIZE+1];
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	struct iwreq wreq;

	memset(&wreq, 0, sizeof(struct iwreq));
	wreq.u.essid.length = IW_ESSID_MAX_SIZE+1;
	sprintf(wreq.ifr_name, wificard);
	if(sockfd == -1) {
		fprintf(stderr, "Cannot open socket for interface: %s: %s\n",
						wificard, strerror(errno));
		return smprintf(UNKNOWN_STR);
	}
	wreq.u.essid.pointer = id;
	if (ioctl(sockfd,SIOCGIWESSID, &wreq) == -1) {
		fprintf(stderr, "Get ESSID ioctl failed for interface %s: %s\n",
						wificard, strerror(errno));
		return smprintf(UNKNOWN_STR);
	}

	if (strcmp((char *)wreq.u.essid.pointer, "") == 0)
		return smprintf(UNKNOWN_STR);
	else
		return smprintf("%s", (char *)wreq.u.essid.pointer);
}
