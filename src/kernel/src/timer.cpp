#include "timer.h"

#include <thread>
#include <algorithm>

#include "globals.h"

namespace kernel
{

timer::timer () : 
  target_delta_t (1.f / target_fps),
  delta_t (0.f),
  elapsed_t (0.f),  
  prev_t (clock::now ()) {}

void timer::tick ()
{
  auto target_time = prev_t + secondsf(target_delta_t);

  auto now = clock::now();
  if (now < target_time)
    {
      std::this_thread::sleep_until (target_time);
      now = clock::now();
    }

  secondsf dt = now - prev_t;

  const float dt_min = 1.0f / 1000.0f;
  const float dt_max = 1.0f / 10.0f;
  delta_t = std::clamp (dt.count (), dt_min, dt_max);

  elapsed_t += delta_t;
  prev_t = now;
}

timer::~timer () {}

}