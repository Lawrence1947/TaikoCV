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

  // auto drawButton = [&](cv::Mat& img, const std::string& text, int x, int y, bool active){
  //   cv::Scalar color = active ? cv::Scalar(0,200,255) : cv::Scalar(90,90,90);
  //   cv::rectangle(img, {x,y}, {x+60,y+60}, color, cv::FILLED);
  //   cv::putText(img, text, {x+15,y+40}, cv::FONT_HERSHEY_SIMPLEX, 0.8, {0,0,0}, 2, cv::LINE_AA);
  // };

  // drawButton(image, "Z",   40,  80, true);
  // drawButton(image, "X",  120,  80, true);
  // drawButton(image, ".",  200,  80, true);
  // drawButton(image, "/",  280,  80, true);
}

taiko::~taiko ()
{

}


}