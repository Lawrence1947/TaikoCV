#ifndef RESULTS_H
#define RESULTS_H

#include "kernel/include/object.h"

namespace game
{

class results
{
public:
  results ();

  void update ();

  std::vector<kernel::object> &get_objects () { return objects; }

  ~results ();
private:
  std::vector<kernel::object> objects;
};

}

#endif