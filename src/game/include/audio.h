#ifndef AUDIO_H
#define AUDIO_H

#include <string>

#include "third_party/macron/miniaudio.h"

namespace game
{

namespace audio
{
  extern ma_engine g_engine;
  extern bool      g_inited;

  bool init();
  void shutdown();

  struct music
  {
    ma_sound sound{};
    bool     loaded = false;
  };

  bool load_music(music &m, const std::string &path);
  void play_music(music &m, bool loop = false);
  void stop_music(music &m);

  float get_music_time_s(music &m);

  void unload_music(music &m);
}

}

#endif