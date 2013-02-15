#ifndef __STATUSES_H__
#define __STATUSES_H__

#include <alsa/asoundlib.h>

#include "common.h"

void status_battery(GlobalData *g, char *batname);
void status_cpuusage(GlobalData *g);
void status_datetime(GlobalData *g);
void status_fan(GlobalData *g, char *title, char *sysfile);
void status_memusage(GlobalData *g);
void status_netif(GlobalData *g, char *ifname);
void status_temp(GlobalData *g, char *title, char *sysfile);
void status_uptime(GlobalData *g);
int status_volume_alsa(GlobalData *g, char *cardname, char *mixername, snd_mixer_selem_channel_id_t channel);

#endif
