static char *
ip(const char *interface)
{
	struct ifaddrs *ifaddr, *ifa;
	int s;
	char host[NI_MAXHOST];

	if (getifaddrs(&ifaddr) == -1) {
		fprintf(stderr, "Error getting IP address: %s\n",
						strerror(errno));
		return smprintf(UNKNOWN_STR);
	}

	/* get the ip address */
	for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr == NULL)
			continue;

		s = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, NI_MAXHOST,
								NULL, 0, NI_NUMERICHOST);

		if ((strcmp(ifa->ifa_name, interface) == 0) && (ifa->ifa_addr->sa_family == AF_INET)) {
			if (s != 0) {
				fprintf(stderr, "Error getting IP address.\n");
				return smprintf(UNKNOWN_STR);
			}
			return smprintf("%s", host);
		}
	}

	/* free the address */
	freeifaddrs(ifaddr);

	return smprintf(UNKNOWN_STR);
}
