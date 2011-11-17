
#ifndef __VOLUME_ALSA_H__
#define __VOLUME_ALSA_H__

#include <alsa/asoundlib.h>

int status_volume_alsa(char *cardname, char *mixername, snd_mixer_selem_channel_id_t channel);

#endif
