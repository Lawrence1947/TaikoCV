#ifndef TIMER_H
#define TIMER_H

#include <chrono>

namespace kernel
{

class timer
{
  using clock    = std::chrono::steady_clock;
  using secondsf = std::chrono::duration<float>;

public:
  timer ();

  void tick ();

  float delta   () const { return delta_t; }
  float elapsed () const { return elapsed_t; }
  float fps     () const { return 1.0f / delta_t; }

  ~timer ();

private:
  float target_delta_t;
  float delta_t;
  float elapsed_t;
  clock::time_point prev_t;
};

}

#endif
