#include "game.h"

#include "globals.h"
#include "keymap.h"
#include "common_math.h"

namespace game
{

taiko::taiko (int screen_width_, int screen_height_) 
    : screen_size (screen_width_, screen_height_),
      renderer (screen_size),
      mode (game_mode::main_menu),
      main_menu (screen_size),
      playing (screen_size),
      result (screen_size),
      menu_frame (screen_size, CV_8UC3, cv::Scalar (0, 0, 0)),
      action_frame (screen_size, CV_8UC3, cv::Scalar (0, 0, 0))
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

inline void taiko::update_menu_to_action (const float delta_t)
{
  menu_to_action_trans_elapsed += delta_t;
}

void taiko::update (const float delta_t)
{
  if (mode == game_mode::main_menu)
    {
      main_menu.update (delta_t);
      if (enter_pressed)
        {
          mode = game_mode::menu_to_action;
        }
    }
  else if (mode == game_mode::menu_to_action)
    {
      update_menu_to_action (delta_t);
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

void taiko::render (cv::Mat &frame)
{
  switch (mode)
    {
    case game_mode::main_menu:
      {
        renderer.render (frame, main_menu.get_objects ());
        break;
      }

    case game_mode::menu_to_action:
      {
        renderer.render (menu_frame, main_menu.get_objects ());
        renderer.render (action_frame, playing.get_objects ());

        double a = ease_in_out (menu_to_action_trans_elapsed / menu_to_action_trans_duration);
        a = clamp01 (a);

        cv::addWeighted (menu_frame, 1.0 - a, action_frame, a, 0.0, frame);
        if (a > 1.0 - min_division) 
          {
            menu_to_action_trans_elapsed = 0.0;
            mode = game_mode::action;
          }
        break;
      }
    
    case game_mode::action:
      {
        renderer.render (frame, playing.get_objects ());
        break;
      }

    case game_mode::results:
      {
        renderer.render (frame, result.get_objects ());
        break;
      }
    }
}

taiko::~taiko () {}

}