#include "menu.h"

#include <stdio.h>

namespace game
{
  
menu::menu (const cv::Size &screen_size_) : screen_size (screen_size_)
{
  original_data.main_screen = cv::imread ("../resources/taiko_main_screen.jpg", cv::IMREAD_UNCHANGED);
  original_data.logo = cv::imread ("../resources/taiko_logo.png", cv::IMREAD_UNCHANGED);

  cv::Size logo_size = original_data.logo.size ();

  cv::Rect fullscreen (0, 0, screen_size.width, screen_size.height);
  // cv::Rect logo_rect (screen_size.width / 2 - logo_size.width / 2, screen_size.height / 4 + logo_size.height / 2, logo_size.width, logo_size.height);
  cv::Rect logo_rect (0, 0, logo_size.width, logo_size.height);

  kernel::object main_screen (original_data.main_screen, fullscreen);
  kernel::object logo (original_data.logo, logo_rect);

  objects.push_back (main_screen);
  objects.push_back (logo);
}

void menu::update ()
{
  // cv::Mat original_image = 
  // cv::Mat resized_image;
  
  // cv::resize (original_image, resized_image, get_screen_size (), 0, 0, cv::INTER_LINEAR);
  // image = resized_image;

  printf ("menu\n");
}

menu::~menu () 
{

}

}
