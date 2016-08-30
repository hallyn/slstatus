/* See LICENSE file for copyright and license details. */

#include <alsa/asoundlib.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <ifaddrs.h>
#include <limits.h>
#include <linux/wireless.h>
#include <locale.h>
#include <netdb.h>
#include <pwd.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <sys/socket.h>
#include <sys/sysinfo.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <X11/Xlib.h>

#undef strlcat
#undef strlcpy

#include "strlcat.h"
#include "strlcpy.h"

typedef char *(*op_fun)();
struct arg {
	op_fun func;
	const char *format;
	const char *args;
};

static void setstatus(const char *);
static char *smprintf(const char *, ...);

static Display *dpy;

#include "config.h"

static void
setstatus(const char *str)
{
	/* set WM_NAME via X11 */
	XStoreName(dpy, DefaultRootWindow(dpy), str);
	XSync(dpy, False);
}

static char *
smprintf(const char *fmt, ...)
{
	va_list ap;
	char *ret;
	int len;

	va_start(ap, fmt);
	len = vsnprintf(NULL, 0, fmt, ap);
	va_end(ap);

	ret = malloc(++len);
	if (ret == NULL) {
		perror("malloc");
		exit(1);
	}

	va_start(ap, fmt);
	vsnprintf(ret, len, fmt, ap);
	va_end(ap);

	return ret;
}

int
main(void)
{
	size_t i;
	char status_string[4096];
	char *res, *element;
	struct arg argument;

	dpy = XOpenDisplay(0x0);
	if (!dpy) {
		fprintf(stderr, "Cannot open display!\n");
		exit(1);
	}

	for (;;) {
		memset(status_string, 0, sizeof(status_string));
		for (i = 0; i < sizeof(args) / sizeof(args[0]); ++i) {
			argument = args[i];
			if (argument.args == NULL)
				res = argument.func();
			else
				res = argument.func(argument.args);
			element = smprintf(argument.format, res);
			if (element == NULL) {
				element = smprintf(UNKNOWN_STR);
				fprintf(stderr, "Failed to format output.\n");
			}
			strlcat(status_string, element, sizeof(status_string));
			free(res);
			free(element);
		}

		setstatus(status_string);
		sleep(UPDATE_INTERVAL -1);
	}

	XCloseDisplay(dpy);
	return (0);
}
