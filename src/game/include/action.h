#ifndef ACTION_H
#define ACTION_H

#include <opencv2/opencv.hpp>
#include <vector>

#include "keymap.h"
#include "globals.h"

#include "kernel/include/object.h"
#include "beatmap.h"
#include "audio.h"

namespace game
{

struct taiko_circle
{
  taiko_color color;
  taiko_size  size;
  cv::Point2f position;
  float       speed;
  bool        active;

  float spawn_t;
  float start_x;

  taiko_circle ()
    : color   (taiko_color::red),
      size    (taiko_size::small),
      position(0.f, 0.f),
      speed   (0.f),
      active  (false),
      spawn_t (0.f),
      start_x (0.f)
  {}
};

struct action_objects
{
  cv::Mat background;
  cv::Mat main_field;
  cv::Mat combo_panel;
};

class action
{
public:
  action (const cv::Size &screen_size_, results_data &res_data_, game_mode &mode_);

  void reset ();

  void play ();

  void update (const float delta_t, key::input_system &input);

  std::vector<kernel::object> &get_objects () { return objects; }

  ~action ();

private:
  void spawn_circle();
  void update_circles(const float delta_t);
  void update_circle_objects ();
  bool could_circle_be_hitted (const taiko_circle &circle);

  void try_spawn_notes_from_map (float prev_map_time_s, float curr_map_time_s);
  void spawn_circle_from_note (const map_note &note, float now_s);

  void handle_key_press (key::input_system &input);
  void draw_keys (cv::Mat &frame, key::input_system &input);
  void draw_key (cv::Mat &frame, cv::Point pos, const char *label, bool is_down, cv::Scalar color);

  void draw_results_data (cv::Mat &frame);

  void update_combo_panel ();

private:
  const cv::Size screen_size;

  std::vector<kernel::object> objects;
  action_objects original_data;

  // hit params
  int hit_x;
  int hit_y;

  int hit_r_outer;
  int hit_r_inner;
  int hit_r_big;

  int hit_right_big_border;
  int hit_left_big_border;
  int hit_right_small_border;
  int hit_left_small_border;

  int miss_streak = 0;

  // results data
  results_data &res_data;

  // Taiko circles system
  std::vector<taiko_circle> circles;
  float circle_spawn_timer;
  static constexpr float CIRCLE_SPAWN_INTERVAL = 0.5f; // spawn every 1 second for testing
  static constexpr float CIRCLE_SPEED = 500.0f; // pixels per second
  static constexpr int MAX_CIRCLES = 10; // maximum active circless

  // audio
  beatmap bm;
  audio::music music_track;
  size_t next_note_idx = 0;

  // time
  float elapsed = 0.f;
  float prev_map_time_s = 0.f;

  // game
  game_mode &mode;
};

}

#endif