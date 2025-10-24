#include "menu.h"

#include <stdio.h>
#include <string>

namespace game
{
  
menu::menu (const cv::Size &screen_size_) : screen_size (screen_size_)
{
  original_data.main_screen = cv::imread ("../resources/main_menu/taiko_main_screen.jpg", cv::IMREAD_UNCHANGED);

  cv::Rect fullscreen (0, 0, screen_size.width, screen_size.height);
  cv::Mat frame = original_data.main_screen;

  std::string text = "Press ENTER to start";
  constexpr double scale = 1.4;
  constexpr int thickness = 4;
  cv::Scalar color (0, 0, 255);
  int font = cv::FONT_HERSHEY_TRIPLEX | cv::FONT_ITALIC;

  cv::Size textSize = cv::getTextSize(text, font, scale, thickness, nullptr);
  int x = (screen_size.width - textSize.width) / 2;
  int y = screen_size.height * 0.85;

  cv::putText (frame, text, {x + 2, y + 2}, font, scale, cv::Scalar (0, 0, 0), thickness + 2, cv::LINE_AA);

  cv::putText (frame, text, {x, y}, font, scale, color, thickness, cv::LINE_AA);

  kernel::object main_screen (frame, fullscreen);
  objects.push_back (main_screen);
}

void menu::update (const float delta_t)
{
  printf ("main menu: %f\n", delta_t);
}

menu::~menu () {}

}
