#include "menu.h"

#include <stdio.h>

namespace game
{
  
menu::menu (const cv::Size &screen_size_) : screen_size (screen_size_)
{
  original_data.main_screen = cv::imread ("../resources/main_menu/taiko_main_screen.jpg", cv::IMREAD_UNCHANGED);

  cv::Rect fullscreen (0, 0, screen_size.width, screen_size.height);

  kernel::object main_screen (original_data.main_screen, fullscreen);

  objects.push_back (main_screen);
}

void menu::update ()
{
  printf ("main menu\n");
}

menu::~menu () 
{

}

}
