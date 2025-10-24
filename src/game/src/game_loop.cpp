#include "game_loop.h"

#include <opencv2/opencv.hpp>

#include "globals.h"
#include "keymap.h"
#include "system/include/screen.h"
#include "kernel/include/renderer.h"

#include <stdio.h>

namespace game
{

main_loop::main_loop () : is_running (true), timer ()
{
  system_utils::screen s;
  screen_width = s.get_width ();
  screen_height = s.get_height ();
}

int main_loop::run ()
{
  cv::namedWindow (WINDOW_NAME, cv::WINDOW_NORMAL);
  cv::setWindowProperty (WINDOW_NAME, cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);

  cv::Size screen_size (screen_width, screen_height);
  cv::Mat frame (screen_size, CV_8UC3, cv::Scalar (0, 0, 0));

  cv::Mat original_image = cv::imread ("../resources/taiko_load.jpg", 1);
  cv::Mat resized_image;
  
  cv::resize (original_image, resized_image, screen_size, 0, 0, cv::INTER_LINEAR);

  kernel::renderer renderer;

  while (is_running)
  {
    timer.tick ();

    int key = cv::waitKey(1);
    if (key == key::escape)
      {
        is_running = false;
      }

      renderer.render (frame, resized_image);

      cv::imshow (WINDOW_NAME, frame);
  }
  
  cv::destroyAllWindows ();
  return 0;
}

main_loop::~main_loop ()
{

}

  
}