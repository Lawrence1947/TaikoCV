#ifndef ACTION_H
#define ACTION_H

#include <opencv2/opencv.hpp>

#include "kernel/include/object.h"

namespace game
{

struct action_objects
{
  cv::Mat background;
  cv::Mat main_field;
  cv::Mat combo_panel;
};

class action
{
public:
  action (const cv::Size &screen_size_);

  void update (const float delta_t);

  std::vector<kernel::object> &get_objects () { return objects; }

  ~action ();
private:
  const cv::Size screen_size;

  std::vector<kernel::object> objects;
  action_objects original_data;

  int hit_x;
  int hit_y;

  int hit_r_outer;
  int hiy_r_inner;
  int hiy_r_big;
};

}

#endif