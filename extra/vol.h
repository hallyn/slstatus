#include <alsa/asoundlib.h>

static char *
vol_perc(const char *soundcard)
{
	int mute = 0;
	long vol = 0, max = 0, min = 0;
	snd_mixer_t *handle;
	snd_mixer_elem_t *pcm_mixer, *mas_mixer;
	snd_mixer_selem_id_t *vol_info, *mute_info;

	snd_mixer_open(&handle, 0);
	snd_mixer_attach(handle, soundcard);
	snd_mixer_selem_register(handle, NULL, NULL);
	snd_mixer_load(handle);

	snd_mixer_selem_id_malloc(&vol_info);
	snd_mixer_selem_id_malloc(&mute_info);
	if (vol_info == NULL || mute_info == NULL) {
		fprintf(stderr, "Could not get alsa volume.\n");
		return smprintf(UNKNOWN_STR);
	}
	snd_mixer_selem_id_set_name(vol_info, ALSA_CHANNEL);
	snd_mixer_selem_id_set_name(mute_info, ALSA_CHANNEL);
	pcm_mixer = snd_mixer_find_selem(handle, vol_info);
	mas_mixer = snd_mixer_find_selem(handle, mute_info);

	snd_mixer_selem_get_playback_volume_range((snd_mixer_elem_t *)pcm_mixer, &min, &max);
	snd_mixer_selem_get_playback_volume((snd_mixer_elem_t *)pcm_mixer, SND_MIXER_SCHN_MONO, &vol);
	snd_mixer_selem_get_playback_switch(mas_mixer, SND_MIXER_SCHN_MONO, &mute);

	if (vol_info)
		snd_mixer_selem_id_free(vol_info);
	if (mute_info)
		snd_mixer_selem_id_free(mute_info);
	if (handle)
		snd_mixer_close(handle);

	if (!mute)
		return smprintf("mute");
	else
		return smprintf("%d%%", (vol * 100) / max);
}
