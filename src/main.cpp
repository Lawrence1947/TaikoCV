#include <opencv2/opencv.hpp>

#include "globals.h"

// #include "system/include/screen.h"

#include "game/include/game_loop.h"

int main ()
{
  // cv::namedWindow (WINDOW_NAME, cv::WINDOW_NORMAL);
  // cv::setWindowProperty (WINDOW_NAME, cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);

  // system_utils::screen s;

  // const int screen_width = s.get_width ();
  // const int screen_height = s.get_height (); 
  
  // cv::Mat original_image = cv::imread ("../resources/taiko_load.jpg", 1);
  // cv::Mat resized_image;

  // cv::Size screen_size (screen_width, screen_height);
  // cv::resize (original_image, resized_image, screen_size, 0, 0, cv::INTER_LINEAR);

  // cv::imshow (WINDOW_NAME, resized_image);

  // cv::waitKey (0);
  // cv::destroyAllWindows ();

  game::main_loop app;
  return app.run ();
}