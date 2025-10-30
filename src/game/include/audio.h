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

}

}

#endif