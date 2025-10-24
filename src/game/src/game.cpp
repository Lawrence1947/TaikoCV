#include "game.h"

#include "keymap.h"

namespace game
{

taiko::taiko (int screen_width_, int screen_height_) 
    : screen_size (screen_width_, screen_height_),
      mode (game_mode::main_menu),
      main_menu (screen_size),
      playing (),
      result ()
{}

void taiko::on_key (int key)
{
  if (key == key::left_blue)
    {
      mode = game_mode::main_menu;
    }
  else if (key == key::right_blue)
    {
      mode = game_mode::action;
    }
  else if (key == key::left_red)
    {
      mode = game_mode::results;
    }
}

void taiko::update ()
{
  switch (mode)
    {
    case game_mode::main_menu:
      main_menu.update ();
      break;
    
    case game_mode::action:
      playing.update ();
      break;

    case game_mode::results:
      result.update ();
      break;
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