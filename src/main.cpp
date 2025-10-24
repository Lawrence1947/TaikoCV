
#include <opencv2/opencv.hpp>

#include "globals.h"

#include "system/include/screen.h"

#include "game/include/game_loop.h"
#include "game/include/game.h"

int main ()
{
  cv::setUseOptimized(false);
  cv::setNumThreads(1);

  cv::namedWindow (WINDOW_NAME, cv::WINDOW_NORMAL);
  cv::setWindowProperty (WINDOW_NAME, cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);

  system_utils::screen s;
  game::taiko taiko_game (s.get_width (), s.get_height ());

  game::main_loop app (taiko_game);
  return app.run ();
}