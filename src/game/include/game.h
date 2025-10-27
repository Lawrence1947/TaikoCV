#ifndef GAME_H
#define GAME_H

#include <opencv2/opencv.hpp>

#include "keymap.h"

#include "menu.h"
#include "action.h"
#include "results.h"

#include "kernel/include/object.h"
#include "kernel/include/timer.h"
#include "kernel/include/renderer.h"

namespace game
{

enum class game_mode
{
  main_menu,
  menu_to_action,
  action,
  results
};

class taiko 
{
public:

  taiko (int screen_width_, int screen_height_);

  void drop_keys ();
  void on_keys (int key);

  void update (const float delta_t);

  void render (cv::Mat &frame);

  ~taiko ();

  cv::Size get_screen_size () const { return screen_size; }

private:

  inline void update_menu_to_action (const float delta_t);

private:
  // system info
  cv::Size screen_size;

  // results
  results_data res_data;

  // kernel utils
  kernel::renderer renderer;

  // game utils
  game_mode mode;

  // game modes
  menu main_menu;
  action playing;
  results result;

  // keys
  key::input_system input;

private:
  // cached data
  cv::Mat menu_frame;
  cv::Mat action_frame;

  double menu_to_action_trans_elapsed = 0.0;
};

};

#endif
