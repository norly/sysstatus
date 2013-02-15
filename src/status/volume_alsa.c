#include <alsa/asoundlib.h>

#include "common.h"


int status_volume_alsa(GlobalData *g,
                        char *cardname,
                        char *mixername,
                        snd_mixer_selem_channel_id_t channel)
{
  StatusItem s;
  char text[16] = { 0 };

  snd_mixer_t *handle = NULL;
  snd_mixer_elem_t *elem;
  snd_mixer_selem_id_t *sid;

  long min = 0, max = 0;
  long volume;
  int on_off;


  statusitem_init(&s);
  s.text = text;

  snd_mixer_selem_id_alloca(&sid);

  if (snd_mixer_open(&handle, 0) < 0) {
    return -1;
  }

  if (snd_mixer_attach(handle, cardname) < 0) {
    goto ERROR;
  }

  snd_mixer_selem_id_set_name(sid, mixername);

  if (snd_mixer_selem_register(handle, NULL, NULL) < 0) {
    goto ERROR;
  }

  if (snd_mixer_load(handle) < 0) {
    goto ERROR;
  }

  elem = snd_mixer_find_selem(handle, sid);
  if (!elem) {
    goto ERROR;
  }

  if (snd_mixer_selem_has_playback_volume(elem)
      && snd_mixer_selem_has_playback_channel(elem, channel)) {
    snd_mixer_selem_get_playback_switch(elem, channel, &on_off);
    snd_mixer_selem_get_playback_volume_range(elem, &min, &max);
    snd_mixer_selem_get_playback_volume(elem, channel, &volume);

    s.color = on_off ? "#22FF22" : "red";
    snprintf(text, sizeof(text), "Vol: %d", (int)volume);
  }

  snd_mixer_close(handle);

  line_append_item(g, &s);

  return 0;

  ERROR:

  snd_mixer_close(handle);
  return -1;
}
