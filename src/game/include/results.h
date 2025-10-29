#ifndef RESULTS_H
#define RESULTS_H

#include "kernel/include/object.h"

#include "globals.h"

namespace game
{

struct results_objects
{
  cv::Mat background;
  cv::Mat panel;
};

class results
{
public:
  results (const cv::Size &screen_size_, results_data &res_data);

  void update (const float delta_t);

  std::vector<kernel::object> &get_objects () { return objects; }

  ~results ();
private:
  const cv::Size screen_size;

  // results data
  results_data &res_data;

  std::vector<kernel::object> objects;
  results_objects original_data;
};

}

#endif