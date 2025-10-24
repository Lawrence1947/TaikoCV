#ifndef GAME_H
#define GAME_H

#include <opencv2/opencv.hpp>

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
  action,
  results
};

class taiko 
{
public:

  taiko (int screen_width_, int screen_height_);

  void drop_keys ();
  void on_key (int key);

  bool is_blue_pressed () { return left_blue_pressed || right_blue_pressed; }
  bool is_red_pressed () { return left_red_pressed || right_red_pressed; }

  void update (const float delta_t);

  void render (cv::Mat &frame);

  ~taiko ();

  cv::Size get_screen_size () const { return screen_size; }

  std::vector<kernel::object> &get_objects ();

private:

  void menu_to_action_transition ();

private:
  // system info
  cv::Size screen_size;

  // kernel utils
  kernel::renderer renderer;

  // game utils
  game_mode mode;

  // game modes
  menu main_menu;
  action playing;
  results result;

  // keys
  bool enter_pressed = false;
  bool left_blue_pressed = false;
  bool right_blue_pressed = false;
  bool left_red_pressed = false;
  bool right_red_pressed = false;
};

};

#endif
