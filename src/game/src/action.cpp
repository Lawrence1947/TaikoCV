#include "action.h"

#include <stdio.h>

namespace game
{
  
action::action (const cv::Size &screen_size_) : screen_size (screen_size_)
{
  // background
  original_data.background = cv::imread ("../resources/action/taiko_background.jpg", cv::IMREAD_UNCHANGED);

  cv::Rect fullscreen (0, 0, screen_size.width, screen_size.height);

  kernel::object background (original_data.background, fullscreen);

  objects.push_back (background);


  // main_field
  original_data.main_field = cv::Mat (screen_size.height / 4, screen_size.width, CV_8UC3, cv::Scalar (32, 32, 36));
  cv::rectangle (original_data.main_field, cv::Rect (0, 0, original_data.main_field.cols, original_data.main_field.rows), cv::Scalar (100, 100, 110), 2, cv::LINE_AA);

  cv::Rect lane (0, screen_size.height / 3, screen_size.width, screen_size.height / 4);

  cv::Mat &lane_img = original_data.main_field;

  hit_x = screen_size.width / 5;
  hit_y = lane_img.rows / 2;

  hit_r_outer = lane_img.rows / 5;
  hiy_r_inner = (int)(hit_r_outer * 0.70);
  hiy_r_big   = (int)(hit_r_outer * 1.45);

  // big circle for big taiko
  cv::circle (lane_img, cv::Point (hit_x, hit_y), hiy_r_big, cv::Scalar (80, 80, 85), 3, cv::LINE_AA);

  // common circle for regular taiko
  cv::circle (lane_img, cv::Point (hit_x, hit_y), hit_r_outer, cv::Scalar (245, 245, 250), 5, cv::LINE_AA);

  // inner circle for good visual
  cv::circle (lane_img, cv::Point (hit_x, hit_y), hiy_r_inner, cv::Scalar (48, 48, 54), cv::FILLED, cv::LINE_AA);

  kernel::object main_filed (original_data.main_field, lane);

  objects.push_back (main_filed);

  // combo panel
  cv::Rect combo_rect (0, lane.y, lane.height, lane.height);

  original_data.combo_panel = cv::Mat (combo_rect.height, combo_rect.width, CV_8UC3, cv::Scalar (60, 65, 100));

  cv::rectangle (original_data.combo_panel, cv::Rect (0, 0, original_data.combo_panel.cols, original_data.combo_panel.rows), cv::Scalar (150, 165, 205), 2, cv::LINE_AA);

  cv::Mat &p = original_data.combo_panel;

  int cx = p.cols / 2;
  int cy = p.rows / 2;

  int r_outer = p.rows / 2.5;
  int r_inner = (int)(r_outer * 0.82);

  cv::circle (p, cv::Point (cx, cy), r_outer, cv::Scalar (220, 220, 215), 6, cv::LINE_AA);

  cv::circle (p, cv::Point (cx, cy), r_inner, cv::Scalar (235, 230, 225), cv::FILLED, cv::LINE_AA);

  cv::line (p, cv::Point (cx, cy - r_inner), cv::Point (cx, cy + r_inner), cv::Scalar (180, 180, 180), 3,cv::LINE_AA);
  cv::circle (p, cv::Point (cx, cy), r_outer, cv::Scalar (160, 160, 160), 2, cv::LINE_AA);

  kernel::object combo_panel (original_data.combo_panel, combo_rect);
  objects.push_back (combo_panel);
}

void action::update (const float delta_t)
{
  
}

action::~action () 
{

}

}
