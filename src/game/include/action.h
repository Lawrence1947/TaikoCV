#ifndef ACTION_H
#define ACTION_H

#include "kernel/include/object.h"

namespace game
{

struct action_objects
{
  cv::Mat background;
};

class action
{
public:
  action (const cv::Size &screen_size_);

  void update ();

  std::vector<kernel::object> &get_objects () { return objects; }

  ~action ();
private:
  const cv::Size screen_size;

  std::vector<kernel::object> objects;
  action_objects original_data;
};

}

#endif