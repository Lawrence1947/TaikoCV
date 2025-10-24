#include "game_loop.h"

#include <opencv2/opencv.hpp>

#include <stdio.h>

#include "globals.h"
#include "keymap.h"

#include "kernel/include/renderer.h"

#include "game.h"

namespace game
{

main_loop::main_loop (taiko &taiko_game_) 
    : is_running (true), 
      timer (), 
      taiko_game (taiko_game_)
{}

int main_loop::run ()
{
  cv::Size screen_size (taiko_game.get_screen_width (), taiko_game.get_screen_height ());
  cv::Mat frame (screen_size, CV_8UC3, cv::Scalar (0, 0, 0));

  kernel::renderer renderer (screen_size);

  while (is_running)
  {
    timer.tick ();

    int key = cv::waitKey(1);
    if (key == key::escape)
      {
        is_running = false;
      }
    taiko_game.on_key (key);

    taiko_game.update ();

    renderer.render (frame, taiko_game.get_image ());

    cv::imshow (WINDOW_NAME, frame);
  }
  
  cv::destroyAllWindows ();
  return 0;
}

main_loop::~main_loop () {}
  
}