#include "timer.h"

#include <thread>

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
  auto curr_t = clock::now ();
  auto elapsed = curr_t - prev_t;
  float frame_delta_t = std::chrono::duration_cast<duration> (elapsed).count ();

  if (frame_delta_t < target_delta_t)
    {
      auto sleep_duration = duration (target_delta_t - frame_delta_t);
      std::this_thread::sleep_for (std::chrono::duration_cast<std::chrono::microseconds> (sleep_duration));
      curr_t = clock::now ();
      frame_delta_t = duration (target_delta_t - frame_delta_t).count ();
    }

  delta_t = frame_delta_t;
  elapsed_t += frame_delta_t;
  prev_t = curr_t;
}

timer::~timer () {}

}