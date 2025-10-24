#include "game.h"

#include "keymap.h"

namespace game
{

taiko::taiko (int screen_width_, int screen_height_) 
    : screen_width (screen_width_), 
      screen_height (screen_height_),
      screen_size (screen_width_, screen_height_),
      mode (game_mode::main_menu),
      main_menu (),
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

      

    case game_mode::COUNT:
      // impossible case
      break;
    }


  cv::Mat original_image = cv::imread ("../resources/taiko_main_screen.jpg", 1);
  cv::Mat resized_image;
  
  cv::resize (original_image, resized_image, get_screen_size (), 0, 0, cv::INTER_LINEAR);
  image = resized_image;
}

taiko::~taiko ()
{

}


}