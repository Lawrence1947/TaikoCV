#ifndef AUDIO_H
#define AUDIO_H

#include <string>

#define MINIAUDIO_IMPLEMENTATION
#define MA_ENABLE_MP3
#include "third_party/macron/miniaudio.h"

namespace game
{

namespace audio
{

inline ma_engine g_engine;
inline bool g_inited = false;

inline void debug_device ()
{
  if (!g_inited) {
    printf ("audio not inited\n");
    return;
  }

  ma_device *pDevice = ma_engine_get_device (&g_engine);
  if (pDevice == NULL) {
    printf("engine has no device (!)\n");
    return;
  }

  printf ("device type: %d\n", pDevice->type);  // ma_device_type_playback = 1
  printf ("backend: %d\n", pDevice->pContext->backend); // pulse/alsa/wasapi
  printf ("sampleRate: %d\n", pDevice->sampleRate);
  printf ("channels: %d\n", pDevice->playback.channels);
}

struct music
{
  ma_sound sound {};
  bool loaded = false;
};

inline bool load_music(music &m, const std::string &path)
{
  if (!g_inited) 
    return false;
  if (ma_sound_init_from_file(&g_engine, path.c_str(), MA_SOUND_FLAG_STREAM, NULL, NULL, &m.sound) != MA_SUCCESS)
    return false;
  m.loaded = true;
  return true;
}

inline bool init()
{
  if (g_inited)
    return true;

  ma_result r = ma_engine_init (NULL, &g_engine);
  if (r != MA_SUCCESS) 
    {
      fprintf(stderr, "ma_engine_init failed: %d\n", r);
      return false;
    }

  g_inited = true;

  // debug_device ();

  return true;
}

inline void shutdown ()
{
  if (!g_inited) 
    return;

  ma_engine_uninit (&g_engine);
  g_inited = false;
}

inline bool play_once (const char* path)
{
  if (!g_inited) 
    return false;

  ma_result r = ma_engine_play_sound (&g_engine, path, NULL);
  return r == MA_SUCCESS;
}

inline void play_music(music &m, bool loop = false)
{
  if (!m.loaded) return;
  ma_sound_set_looping(&m.sound, loop ? MA_TRUE : MA_FALSE);
  ma_sound_start(&m.sound);
}

inline void stop_music(music &m)
{
  if (!m.loaded) return;
  ma_sound_stop(&m.sound);
}

inline float get_music_time_s(music &m)
{
  if (!m.loaded) return 0.f;
  ma_uint64 pcmPos = 0;
  ma_sound_get_cursor_in_pcm_frames(&m.sound, &pcmPos);

  ma_uint32 sampleRate = 0;
  ma_uint32 channels   = 0;
  ma_format format;
  ma_sound_get_data_format(&m.sound, &format, &channels, &sampleRate, NULL, 0);

  if (sampleRate == 0) return 0.f;
  return (float)pcmPos / (float)sampleRate;
}

}

}

#endif