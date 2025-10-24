#include "game.h"

#include "keymap.h"

namespace game
{

taiko::taiko (int screen_width_, int screen_height_) 
    : screen_size (screen_width_, screen_height_),
      mode (game_mode::main_menu),
      main_menu (screen_size),
      playing (screen_size),
      result (screen_size)
{}

void taiko::on_key (int key)
{
  if (key == key::left_blue)
    {
      left_blue_pressed = true;
    }
  else if (key == key::right_blue)
    {
      right_blue_pressed = true;
    }
  else if (key == key::left_red)
    {
      left_red_pressed = true;
    }
  else if (key == key::right_red)
    {
      right_red_pressed = true;
    }
  else if (key == key::enter)
    {
      enter_pressed = true;
    }
}

void taiko::drop_keys ()
{
  enter_pressed = false;
  left_blue_pressed = false;
  right_blue_pressed = false;
  left_red_pressed = false;
  right_blue_pressed = false;
}

void taiko::update (const float delta_t)
{
  if (mode == game_mode::main_menu)
    {
      main_menu.update (delta_t);
      if (enter_pressed)
        {
          mode = game_mode::action;
        }
    }
  else if (mode == game_mode::action)
    {
      playing.update (delta_t);
      if (enter_pressed)
        {
          mode = game_mode::results;
        }
    }
  else if (mode == game_mode::results)
    {
      result.update (delta_t);
      if (enter_pressed)
        {
          mode = game_mode::main_menu;
        }
    }
}

std::vector<kernel::object> &taiko::get_objects ()
{
  switch (mode)
    {
    case game_mode::main_menu:
      return main_menu.get_objects ();
    
    case game_mode::action:
      return playing.get_objects ();

    case game_mode::results:
      return result.get_objects ();
    }
}

taiko::~taiko ()
{

}


}