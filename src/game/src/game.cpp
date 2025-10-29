#include "game.h"

#include "globals.h"
#include "keymap.h"
#include "common_math.h"

namespace game
{

taiko::taiko (int screen_width_, int screen_height_) 
    : screen_size (screen_width_, screen_height_),
      res_data (),
      renderer (screen_size),
      mode (game_mode::main_menu),
      main_menu (screen_size),
      playing (screen_size, res_data),
      result (screen_size, res_data),
      menu_frame (screen_size, CV_8UC3, cv::Scalar (0, 0, 0)),
      action_frame (screen_size, CV_8UC3, cv::Scalar (0, 0, 0)),
      results_frame (screen_size, CV_8UC3, cv::Scalar (0, 0, 0))
{
  res_data.reset ();
}

void taiko::on_keys (int key)
{
  if (key == key::left_blue)
    {
      input.is_left_blue_pressed = true;
    }
  else if (key == key::right_blue)
    {
      input.is_right_blue_pressed = true;
    }
  else if (key == key::left_red)
    {
      input.is_left_red_pressed = true;
    }
  else if (key == key::right_red)
    {
      input.is_right_red_pressed = true;
    }
  else if (key == key::enter)
    {
      input.is_enter_pressed = true;
    }
}

void taiko::drop_keys ()
{
  input.reset ();
}

inline void taiko::update_menu_to_action (const float delta_t)
{
  menu_to_action_trans_elapsed += delta_t;
}

inline void taiko::update_action_to_results (const float delta_t)
{
  action_to_results_trans_elapsed += delta_t;
}

inline void taiko::update_results_to_menu (const float delta_t)
{
  results_to_menu_trans_elapsed += delta_t;
}

void taiko::update (const float delta_t)
{
  if (mode == game_mode::main_menu)
    {
      main_menu.update (delta_t);
      if (input.is_enter_pressed)
        {
          mode = game_mode::menu_to_action;
          menu_frame = cv::Mat (screen_size, CV_8UC3, cv::Scalar (0, 0, 0));
          action_frame = cv::Mat (screen_size, CV_8UC3, cv::Scalar (0, 0, 0));
        }
    }
  else if (mode == game_mode::menu_to_action)
    {
      update_menu_to_action (delta_t);
    }
  else if (mode == game_mode::action)
    {
      playing.update (delta_t, input);
      if (input.is_enter_pressed)
        {
          mode = game_mode::action_to_results;
          action_frame = cv::Mat (screen_size, CV_8UC3, cv::Scalar (0, 0, 0));
          results_frame = cv::Mat (screen_size, CV_8UC3, cv::Scalar (0, 0, 0));
          playing.reset ();
        }
    }
  else if (mode == game_mode::action_to_results)
    {
      update_action_to_results (delta_t);
    }
  else if (mode == game_mode::results)
    {
      result.update (delta_t);
      if (input.is_enter_pressed)
        {
          mode = game_mode::results_to_menu;
          menu_frame = cv::Mat (screen_size, CV_8UC3, cv::Scalar (0, 0, 0));
          results_frame = cv::Mat (screen_size, CV_8UC3, cv::Scalar (0, 0, 0));
        }
    }
  else if (mode == game_mode::results_to_menu)
    {
      update_results_to_menu (delta_t);
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

    case game_mode::action_to_results:
      {
        renderer.render (action_frame, playing.get_objects ());
        renderer.render (results_frame, result.get_objects ());

        double a = ease_in_out (action_to_results_trans_elapsed / action_to_results_trans_duration);
        a = clamp01 (a);

        cv::addWeighted (action_frame, 1.0 - a, results_frame, a, 0.0, frame);
        if (a > 1.0 - min_division) 
          {
            action_to_results_trans_elapsed = 0.0;
            mode = game_mode::results;
          }
        break;
      }

    case game_mode::results:
      {
        renderer.render (frame, result.get_objects ());
        break;
      }

    case game_mode::results_to_menu:
      {
        renderer.render (results_frame, result.get_objects ());
        renderer.render (menu_frame, main_menu.get_objects ());

        double a = ease_in_out (results_to_menu_trans_elapsed / results_to_menu_trans_duration);
        a = clamp01 (a);

        cv::addWeighted (results_frame, 1.0 - a, menu_frame, a, 0.0, frame);
        if (a > 1.0 - min_division) 
          {
            results_to_menu_trans_elapsed = 0.0;
            mode = game_mode::main_menu;
            res_data.reset ();
          }
        break;
      }
    }
}

taiko::~taiko () {}

}