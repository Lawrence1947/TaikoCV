#include "menu.h"

#include <stdio.h>
#include <math.h>

namespace game
{

void draw_transparent_text (cv::Mat& frame, const std::string& text,
                            cv::Point pos, double scale, int font,
                            cv::Scalar color, int thickness,
                            double alpha)
{
  alpha = std::clamp(alpha, 0.0, 1.0);
  cv::Mat overlay = frame.clone();
  cv::putText (overlay, text, pos, font, scale, color, thickness, cv::LINE_AA);
  cv::addWeighted (overlay, alpha, frame, 1.0 - alpha, 0.0, frame);
}
  
menu::menu (const cv::Size &screen_size_) : screen_size (screen_size_)
{
  original_data.main_screen = cv::imread ("../resources/main_menu/taiko_main_screen.jpg", cv::IMREAD_UNCHANGED);
  original_data.logo = cv::imread ("../resources/main_menu/taiko_logo.png", cv::IMREAD_UNCHANGED);

  /// main screen
  cv::Rect fullscreen (0, 0, screen_size.width, screen_size.height);
  main_frame = original_data.main_screen;

  text_params.pos = cv::Point ((screen_size.width - text_params.text_size.width) / 2, screen_size.height * 0.85);

  kernel::object main_screen (main_frame, fullscreen);
  objects.push_back (main_screen);

  /// logo
  cv::Size logo_size = original_data.logo.size ();

  cv::Rect corner (screen_size.width - logo_size.width / 4, 0, logo_size.width / 4, logo_size.height / 4);
  kernel::object logo (original_data.logo, corner);

  objects.push_back (logo);
}

void menu::update (const float delta_t)
{
  text_params.time += delta_t;

  double phase = 2.0 * M_PI * std::fmod (text_params.time, text_params.period) / text_params.period;
  double k = 0.5 * (1.0 + std::sin (phase));               // 0..1
  double alpha = text_params.alpha_min + (text_params.alpha_max - text_params.alpha_min) * k;

  main_frame = original_data.main_screen;
  cv::Mat shadow = main_frame.clone();
  cv::putText (shadow, text_params.text, text_params.pos + cv::Point (3, 3),
              text_params.font, text_params.scale, cv::Scalar(0, 0, 0), text_params.thickness + 3, cv::LINE_AA);
  cv::addWeighted (shadow, 0.4, main_frame, 0.6, 0.0, main_frame);

  draw_transparent_text (main_frame, text_params.text, text_params.pos, text_params.scale, text_params.font, cv::Scalar (0, 0, 255), text_params.thickness, alpha);

  objects[0 /*main_screen*/].set_image (main_frame);

  printf ("main menu: %f\n", delta_t);
}

menu::~menu () {}

}
