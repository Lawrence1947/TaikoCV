#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>

const std::string WINDOW_NAME = "TaikoCV";

constexpr double min_division = 1e-16;

constexpr float target_fps = 60.f;


namespace key
{
  constexpr int escape = 27;
}

#endif