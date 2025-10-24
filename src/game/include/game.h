#ifndef GAME_H
#define GAME_H

#include <opencv2/opencv.hpp>

#include "menu.h"
#include "action.h"
#include "results.h"
#include "kernel/include/object.h"

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

  void on_key (int key);

  void update ();

  ~taiko ();

  cv::Size get_screen_size () const { return screen_size; }

  std::vector<kernel::object> &get_objects ();

private:
  // system info
  cv::Size screen_size;

  // game utils
  game_mode mode;

  // game modes
  menu main_menu;
  action playing;
  results result;
};

};

#endif
