#ifndef BEATMAP_H
#define BEATMAP_H

#include <vector>
#include <string>
#include <fstream>

#include "nlohmann/json.hpp"

#include "globals.h"

namespace game
{

struct map_note
{
  int t_ms;
  taiko_color color;
  taiko_size  size;
};

class beatmap
{
public:
  beatmap (const std::string &path);

  bool load_beatmap (const std::string &path);

  ~beatmap () {}

private:
  int offset_ms = 0;
  float scroll_speed = 500.0f;
  int lead_margin_px = 60;

  std::string audio_path;
  std::vector<map_note> notes;
};

}

#endif