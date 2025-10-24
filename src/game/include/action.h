#ifndef ACTION_H
#define ACTION_H

#include "kernel/include/object.h"

namespace game
{

class action
{
public:
  action ();

  void update ();

  std::vector<kernel::object> &get_objects () { return objects; }

  ~action ();
private:
  std::vector<kernel::object> objects;
};

}

#endif