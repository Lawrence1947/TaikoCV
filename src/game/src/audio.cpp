// src/game/src/audio.cpp
#define MINIAUDIO_IMPLEMENTATION
#include "audio.h"

namespace game
{

namespace audio
{
ma_engine g_engine;
bool      g_inited = false;

bool init()
{
  if (g_inited) return true;
  if (ma_engine_init(NULL, &g_engine) != MA_SUCCESS)
      return false;
  g_inited = true;
  return true;
}

void shutdown()
{
  if (!g_inited) return;
  ma_engine_uninit(&g_engine);
  g_inited = false;
}

bool load_music(music &m, const std::string &path)
{
  if (!g_inited) return false;
  if (ma_sound_init_from_file(&g_engine,
                              path.c_str(),
                              MA_SOUND_FLAG_STREAM,
                              NULL, NULL,
                              &m.sound) != MA_SUCCESS)
      return false;
  m.loaded = true;
  return true;
}

void play_music(music &m, bool loop)
{
  if (!m.loaded) return;
  ma_sound_set_looping(&m.sound, loop ? MA_TRUE : MA_FALSE);
  ma_sound_start(&m.sound);
}

void stop_music(music &m)
{
  if (!m.loaded) return;
  ma_sound_stop(&m.sound);
}

float get_music_time_s(music &m)
{
  if (!m.loaded) return 0.f;

  ma_uint64 pcmPos = 0;
  ma_sound_get_cursor_in_pcm_frames(&m.sound, &pcmPos);

  ma_format format;
  ma_uint32 channels;
  ma_uint32 sampleRate;
  ma_sound_get_data_format(&m.sound, &format, &channels, &sampleRate, NULL, 0);

  if (sampleRate == 0) return 0.f;
  return static_cast<float>(pcmPos) / static_cast<float>(sampleRate);
}

void unload_music(audio::music &m)
{
  if (!m.loaded) return;
  ma_sound_uninit(&m.sound);
  m.loaded = false;
}
}

}
