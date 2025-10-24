#ifndef COMMON_MATH_H
#define COMMON_MATH_H

#include <algorithm>

static inline double clamp01 (double x) 
{ 
  return std::max (0.0, std::min (1.0, x)); 
}

static inline double ease_in_out(double t) 
{
  t = clamp01 (t);
  return t * t * (3 - 2 * t);
}

#endif