#include "action.h"

#include <stdio.h>

namespace game
{
  
action::action (const cv::Size &screen_size_) : screen_size (screen_size_)
{
  original_data.background = cv::imread ("../resources/action/taiko_background.jpg", cv::IMREAD_UNCHANGED);

  cv::Rect fullscreen (0, 0, screen_size.width, screen_size.height);

  kernel::object background (original_data.background, fullscreen);

  objects.push_back (background);
}

void action::update (const float delta_t)
{
  
}

action::~action () 
{

}

}
