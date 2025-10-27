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
  cv::Mat frame (taiko_game.get_screen_size (), CV_8UC3, cv::Scalar (0, 0, 0));

  while (is_running)
    {
      // global tick
      timer.tick ();

      // handle keys
      taiko_game.drop_keys ();
      int key = cv::waitKey(1);
      if (key == key::escape)
        {
          is_running = false;
        }
      taiko_game.on_keys (key);

      // update state
      taiko_game.update (timer.delta ());

      // render frame
      taiko_game.render (frame);

      // show image
      cv::imshow (WINDOW_NAME, frame);

      // debug
      // printf ("FPS: %.1f\n", timer.fps ());
    }
  
  cv::destroyAllWindows ();
  return 0;
}

main_loop::~main_loop () {}
  
}