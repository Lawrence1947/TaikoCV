#ifndef MENU_H
#define MENU_H

#include <opencv2/opencv.hpp>

#include "kernel/include/object.h"

namespace game
{

struct menu_objects
{
  cv::Mat main_screen;
  cv::Mat logo;
};

class menu
{
public:
  menu (const cv::Size &screen_size_);

  void update ();

  std::vector<kernel::object> &get_objects () { return objects; }

  ~menu ();
private:
  const cv::Size screen_size;

  std::vector<kernel::object> objects;
  menu_objects original_data;
};

}

#endif