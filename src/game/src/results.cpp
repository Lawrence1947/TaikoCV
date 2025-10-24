#include "results.h"

#include <stdio.h>

namespace game
{
  
results::results (const cv::Size &screen_size_) : screen_size (screen_size_)
{
  original_data.background = cv::Mat::zeros(screen_size, CV_8UC3);

  cv::Rect fullscreen (0, 0, screen_size.width, screen_size.height);

  kernel::object background (original_data.background, fullscreen);

  objects.push_back (background);
}

void results::update (const float delta_t)
{
  printf ("results: %f\n", delta_t);
}

results::~results () 
{

}

}
