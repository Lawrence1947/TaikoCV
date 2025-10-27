#include "action.h"

#include <stdio.h>
#include <cstdlib>
#include <ctime>

namespace game
{
  
action::action (const cv::Size &screen_size_) : screen_size (screen_size_),
                                               circle_spawn_timer (0.0f)
{
  // Initialize random seed
  srand(static_cast<unsigned int>(time(nullptr)));

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

  int local_hit_x = screen_size.width / 5;
  int local_hit_y = lane_img.rows / 2;
  hit_x = screen_size.width / 5;
  hit_y = screen_size.height / 3 + lane_img.rows / 2;

  hit_r_outer = lane_img.rows / 5;
  hit_r_inner = (int)(hit_r_outer * 0.70);
  hit_r_big   = (int)(hit_r_outer * 1.45);

  // big circle for big taiko
  cv::circle (lane_img, cv::Point (local_hit_x, local_hit_y), hit_r_big, cv::Scalar (80, 80, 85), 3, cv::LINE_AA);

  // common circle for regular taiko
  cv::circle (lane_img, cv::Point (local_hit_x, local_hit_y), hit_r_outer, cv::Scalar (245, 245, 250), 5, cv::LINE_AA);

  // inner circle for good visual
  cv::circle (lane_img, cv::Point (local_hit_x, local_hit_y), hit_r_inner, cv::Scalar (48, 48, 54), cv::FILLED, cv::LINE_AA);

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

  // Initialize circles vector
  circles.resize(MAX_CIRCLES);
}

void action::reset ()
{
  for (auto &circle : circles)
  {
    circle.active = false;
  }
  update_circle_objects ();
}

void action::update (const float delta_t)
{
  // Update circle spawn timer
  circle_spawn_timer += delta_t;
  
  // Spawn new circle if interval has passed
  if (circle_spawn_timer >= CIRCLE_SPAWN_INTERVAL)
  {
    spawn_circle ();
    circle_spawn_timer -= CIRCLE_SPAWN_INTERVAL;
  }
  
  // Update all active circles
  update_circles (delta_t);
  
  // Update circle objects for rendering
  update_circle_objects ();
}

action::~action () 
{

}

void action::spawn_circle()
{
  // Find inactive circle
  for (auto &circle : circles)
  {
    if (!circle.active)
    {
      // Randomly choose color and size
      circle.color = (rand () % 2 == 0) ? taiko_color::red : taiko_color::blue;
      circle.size = (rand () % 2 == 0) ? taiko_size::small : taiko_size::big;
      
      // Start from right side of screen, at hit zone height
      circle.position = cv::Point (screen_size.width, hit_y);
      circle.speed = CIRCLE_SPEED;
      circle.active = true;
      
      break;
    }
  }
}

void action::update_circles(const float delta_t)
{
  for (auto& circle : circles)
  {
    if (circle.active)
    {
      // Move circle left
      circle.position.x -= circle.speed * delta_t;
      
      // Deactivate if off screen
      if (circle.position.x < -50) // 50 pixels buffer
      {
        circle.active = false;
      }
    }
  }
}

void action::update_circle_objects()
{
  // Remove old circle objects (keep only background, main_field, combo_panel)
  while (objects.size () > 3)
  {
    objects.pop_back ();
  }

  // Add active circles as objects
  for (const auto& circle : circles)
  {
    if (!circle.active)
      continue;

    const int ring_thickness = (circle.size == taiko_size::big) ? 12 : 8;

    int ring_r = (circle.size == taiko_size::big) ? hit_r_big : hit_r_outer;

    int border_r = ring_r - (ring_thickness / 2);
    int inner_edge_r = border_r - (ring_thickness / 2);
    int fill_r = std::max (1, inner_edge_r + 1);

    int pad = ring_thickness + 4;

    cv::Mat circle_img ( (border_r + pad) * 2, (border_r + pad) * 2, CV_8UC4, cv::Scalar (0, 0, 0, 0) );

    cv::Scalar fill_color = (circle.color == taiko_color::red)
                          ? cv::Scalar ( 40, 70, 249, 255 )
                          : cv::Scalar (192, 192, 102, 255 );

    cv::Point center (border_r + pad, border_r + pad);

    cv::circle (circle_img, center, fill_r, fill_color, cv::FILLED, cv::LINE_AA);

    cv::circle (circle_img, center, border_r, cv::Scalar (255, 255, 255, 255), ring_thickness, cv::LINE_AA);

    int cx = static_cast<int> (std::lround (circle.position.x));
    int cy = static_cast<int> (std::lround (circle.position.y));

    cv::Rect circle_rect (cx - (border_r + pad), cy - (border_r + pad), (border_r + pad) * 2, (border_r + pad) * 2);

    kernel::object circle_obj (circle_img, circle_rect);
    objects.push_back (circle_obj);
  }
}

}
