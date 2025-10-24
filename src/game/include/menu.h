#ifndef MENU_H
#define MENU_H

#include <opencv2/opencv.hpp>

#include <string>

#include "kernel/include/object.h"

namespace game
{

struct menu_objects
{
  cv::Mat main_screen;
  cv::Mat logo;
};

struct menu_text_params
{
  std::string text = "Press ENTER to start";
  double scale = 1.5;
  int thickness = 4;
  cv::Scalar color = cv::Scalar (0, 0, 255);
  int font = cv::FONT_HERSHEY_TRIPLEX | cv::FONT_ITALIC;

  // dynamic transparency
  double period = 1.6; // seconds
  double alpha_min = 0.35;
  double alpha_max = 0.95;

  // timer
  double time = 0.0;

  // position
  cv::Point pos;

  // size
  cv::Size text_size = cv::getTextSize (text, font, scale, thickness, nullptr);
};

class menu
{
public:
  menu (const cv::Size &screen_size_);

  void update (const float delta_t);

  std::vector<kernel::object> &get_objects () { return objects; }

  ~menu ();
private:
  const cv::Size screen_size;

  std::vector<kernel::object> objects;
  menu_objects original_data;
  menu_text_params text_params;
};

}

#endif