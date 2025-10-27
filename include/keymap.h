#ifndef KEYMAP_H
#define KEYMAP_H


namespace key
{
constexpr int escape = 27;        // esp

constexpr int enter = 13;         // enter

constexpr int left_blue = 100;    // d
constexpr int right_blue = 102;   // f

constexpr int left_red = 106;      // j
constexpr int right_red = 107;     // k

struct input_system
{
  bool is_enter_pressed = false;

  bool is_left_blue_pressed = false;
  bool is_right_blue_pressed = false;
  bool is_left_red_pressed = false;
  bool is_right_red_pressed = false;

  bool is_blue_pressed () { return is_left_blue_pressed || is_right_blue_pressed; }
  bool is_red_pressed () { return is_left_red_pressed || is_right_red_pressed; }

  void reset () 
  {
    is_enter_pressed = false;
    is_left_blue_pressed = false;
    is_right_blue_pressed = false;
    is_left_red_pressed = false;
    is_right_red_pressed = false;
  }
};
}




#endif