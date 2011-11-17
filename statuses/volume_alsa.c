#include <alsa/asoundlib.h>
#include "volume_alsa.h"

int status_volume_alsa(char *cardname, char *mixername, snd_mixer_selem_channel_id_t channel)
{
	snd_mixer_t *handle = NULL;
	snd_mixer_elem_t *elem;
	snd_mixer_selem_id_t *sid;
	
	long min = 0, max = 0;
	long volume;
	int on_off;
	
	
	snd_mixer_selem_id_alloca(&sid);

	if (snd_mixer_open(&handle, 0) < 0)
		return -1;
	
	if (snd_mixer_attach(handle, cardname) < 0)
		goto ERROR;
	
	snd_mixer_selem_id_set_name(sid, mixername);
	
	if (snd_mixer_selem_register(handle, NULL, NULL) < 0)
		goto ERROR;
	
	if (snd_mixer_load(handle) < 0)
		goto ERROR;
	
	elem = snd_mixer_find_selem(handle, sid);
	if (!elem)
		goto ERROR;
	
	if (snd_mixer_selem_has_playback_volume(elem) && snd_mixer_selem_has_playback_channel(elem, channel))
	{
		snd_mixer_selem_get_playback_switch(elem, channel, &on_off);
		if (on_off)
			fputs("^fg(#22FF22)", stdout);
		else
			fputs("^fg(red)", stdout);
		
		snd_mixer_selem_get_playback_volume_range(elem, &min, &max);
		
		snd_mixer_selem_get_playback_volume(elem, channel, &volume);
		fputs("^ca(1, amixer sset Master toggle)", stdout);
		fputs("^ca(4, amixer sset Master 2+ unmute)", stdout);
		fputs("^ca(5, amixer sset Master 2- unmute)", stdout);
		printf(" Vol: %d ", (int)volume);
		fputs("^ca()", stdout);
		fputs("^ca()", stdout);
		fputs("^ca()", stdout);
	}

	snd_mixer_close(handle);

	return 0;
	
	ERROR:
	
	snd_mixer_close(handle);
	return -1;
}
