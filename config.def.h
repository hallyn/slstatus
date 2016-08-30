/* See LICENSE file for copyright and license details. */

/* bar update interval in seconds (smallest value = 1) */
#define UPDATE_INTERVAL	1

/* text to show if no value can be retrieved */
#define UNKNOWN_STR	"n/a"

/*
 * Only uncomment the headers you need
 * and make sure to configure them if
 * required.
 */

/* battery_perc (battery percentage) [argument: battery name] */
/*#include "extra/battery_config.h"*/
/*#include "extra/battery.h"*/

/* cpu_perc (cpu usage in percent) [argument: NULL] */
#include "extra/cpu.h"

/*
- disk_perc (disk usage in percent) [argument: mountpoint]
- disk_total (disk usage in percent) [argument: mountpoint]
- disk_used (disk usage in percent) [argument: mountpoint]
*/
#include "extra/disk.h"

/* gid (gid of current user) [argument: NULL] */
/*#include "extra/gid.h"*/

/* cuid (uid of current user) [argument: NULL] */
/*#include "extra/uid.h"*/

/* ip (ip address) [argument: interface] */
/*#include "extra/ip.h"*/

/*
- ram_free (ram usage in percent) [argument: NULL]
- ram_perc (ram usage in percent) [argument: NULL]
- ram_total (ram usage in percent) [argument: NULL]
- ram_used (ram usage in percent) [argument: NULL]
*/
#include "extra/mem.h"

/* username (username of current user) [argument: NULL] */
/*#include "extra/username.h"*/

/*
- wifi_perc (wifi signal in percent) [argument: wifi card interface name]
- wifi_essid (wifi essid) [argument: wifi card interface name]
*/
/*#include "extra/wifi.h"*/

/* run_command (run custom shell command) [argument: command] */
/*#include "extra/cmd.h"*/
/* datetime (date and time) [argument: format] */
#include "extra/datetime.h"

/* entropy (available entropy) [argument: NULL] */
/*#include "extra/entropy.h"*/

/* hostname [argument: NULL] */
/*#include "extra/hostname.h"*/

/* load_avg (load average) [argument: NULL] */
/*#include "extra/load_avg.h"*/

/* temp (temperature in degrees) [argument: temperature file] */
/*#include "extra/temp.h"*/

/* uptime (uptime) [argument: NULL] */
/*#include "extra/uptime.h"*/

/* vol_perc (alsa volume and mute status in percent) [argument: soundcard] */
#include "extra/vol_config.h"
#include "extra/vol.h"

static const struct arg args[] = {
	/* function	format			argument */
	{ cpu_perc,	"[ CPU %4s ]",		NULL },
	{ ram_perc,	"[ Mem %3s ]",		NULL },
	{ vol_perc,	"[ Volume %4s ]",	"default" },
	{ disk_perc,	"[ HDD %3s ]",		"/" },
	{ datetime,	"[ %s ]",		"%F %T" },
};
