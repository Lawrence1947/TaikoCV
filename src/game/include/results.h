#ifndef RESULTS_H
#define RESULTS_H

#include "kernel/include/object.h"

namespace game
{

struct results_objects
{
  cv::Mat background;
};

class results
{
public:
  results (const cv::Size &screen_size_);

  void update ();

  std::vector<kernel::object> &get_objects () { return objects; }

  ~results ();
private:
  const cv::Size screen_size;

  std::vector<kernel::object> objects;
  results_objects original_data;
};

}

#endif