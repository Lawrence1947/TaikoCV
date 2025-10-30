#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>

const std::string WINDOW_NAME = "TaikoCV";

constexpr double min_division = 1e-16;

constexpr float target_fps = 60.f;

// menu
constexpr double menu_to_action_trans_duration = 1.6;
constexpr double action_to_results_trans_duration = 1.6;
constexpr double results_to_menu_trans_duration = 1.6;

// result
struct results_data
{
  int current_combo;
  int max_combo;
  int score;

  results_data () { reset (); }

  void reset ()
  {
    current_combo = 0;
    max_combo = 0;
    score = 0;
  }
};

// common
enum class taiko_color
{
  red,
  blue
};

enum class taiko_size
{
  small,
  big
};

#endif