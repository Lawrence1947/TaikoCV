#ifndef GAME_H
#define GAME_H

#include <opencv2/opencv.hpp>

#include "menu.h"
#include "action.h"
#include "results.h"

namespace game
{

enum class game_mode
{
  main_menu,
  action,
  results,

  COUNT
};

class taiko 
{
public:

  taiko (int screen_width_, int screen_height_);

  void on_key (int key);

  void update ();

  ~taiko ();

  int get_screen_width  () const { return screen_width; }
  int get_screen_height () const { return screen_height; }
  cv::Size get_screen_size () const { return screen_size; }

  cv::Mat &get_image () { return image; }

private:
  // system info
  int screen_width;
  int screen_height;
  cv::Size screen_size;

  // game objects
  cv::Mat image;

  // game utils
  game_mode mode;

  // game modes
  menu main_menu;
  action playing;
  results result;
};

};

#endif
