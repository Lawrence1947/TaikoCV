#include "beatmap.h"

namespace game
{

static taiko_color parse_color (const std::string &s)
{
  return (s == "red") ? taiko_color::red : taiko_color::blue;
}
static taiko_size parse_size (const std::string &s)
{
  return (s == "big") ? taiko_size::big : taiko_size::small;
}

beatmap::beatmap (const std::string &path)
{
  load_beatmap (path);
}


bool beatmap::load_beatmap (const std::string &path)
{
  std::ifstream f (path);
  if (!f) 
    return false;

  nlohmann::json j; f >> j;

  audio_path    = j.value ("audio", "");
  offset_ms     = j.value ("offset_ms", 0);
  scroll_speed  = j.value ("scroll_speed_px_s", 500.0f);
  lead_margin_px= j.value ("lead_margin_px", 60);

  notes.clear();
  for (auto &jn : j["notes"])
  {
    map_note n;
    n.t_ms   = jn.value ("t", 0);
    n.color  = parse_color (jn.value ("color", "red"));
    n.size   = parse_size (jn.value ("size",  "small"));
    notes.push_back (n);
  }

  std::sort (notes.begin(), notes.end(),
            [](const map_note&a, const map_note&b){ return a.t_ms < b.t_ms; });
  return true;
}

}