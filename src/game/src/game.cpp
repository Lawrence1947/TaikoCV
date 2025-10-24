#include "game.h"

namespace game
{

taiko::taiko (int screen_width_, int screen_height_) 
    : screen_width (screen_width_), 
      screen_height (screen_height_),
      screen_size (screen_width_, screen_height_)
{}

void taiko::update ()
{
  cv::Mat original_image = cv::imread ("../resources/taiko_main_screen.jpg", 1);
  cv::Mat resized_image;
  
  cv::resize (original_image, resized_image, get_screen_size (), 0, 0, cv::INTER_LINEAR);
  image = resized_image;
}

taiko::~taiko ()
{

}


}