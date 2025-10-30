#include "action.h"

#include <stdio.h>
#include <cstdlib>
#include <ctime>

#include "globals.h"

#include <iostream>

namespace game
{
  
action::action (const cv::Size &screen_size_, results_data &res_data_) 
          : screen_size (screen_size_),
            circle_spawn_timer (0.f),
            res_data (res_data_),
            bm ("../maps/test_map/test_map.json")
{
  audio::init ();

  if (!bm.audio_path.empty ())
  {
    if (audio::load_music (music_track, bm.audio_path))
      {
        audio::play_music (music_track, false);
        std::cout << "[audio] loaded and started: " << bm.audio_path << "\n";
      }
    else
      {
        std::cout << "[audio] FAILED to load: " << bm.audio_path << "\n";
      }
  }
  else
  {
    std::cout << "[audio] beatmap has empty audio_path\n";
  }

  // Initialize random seed
  srand(static_cast<unsigned int> (time(nullptr)));

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

  hit_right_big_border = hit_x + hit_r_big;
  hit_left_big_border = hit_x - hit_r_big;
  hit_right_small_border = hit_x + hit_r_outer;
  hit_left_small_border = hit_x - hit_r_outer;

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

  kernel::object combo_panel (original_data.combo_panel, combo_rect);
  objects.push_back (combo_panel);

  update_combo_panel ();

  // Initialize circles vector
  circles.resize(MAX_CIRCLES);
}

void action::update_combo_panel ()
{
  cv::Rect lane (0, screen_size.height / 3, screen_size.width, screen_size.height / 4);
  cv::Rect combo_rect (0, lane.y, lane.height, lane.height);

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

  std::string current_combo_str = std::to_string (res_data.current_combo);
  
  int font_face = cv::FONT_HERSHEY_TRIPLEX | cv::FONT_ITALIC;
  double font_scale = 1.5;
  int thickness = 3;
  
  int baseline = 0;
  cv::Size current_combo_str_size = cv::getTextSize (current_combo_str, font_face, font_scale, thickness, &baseline);

  int str_x = combo_rect.size ().width / 2 - current_combo_str_size.width / 2;
  int str_y = lane.y / 2.1 - current_combo_str_size.height / 2;
  
  cv::Scalar text_color (0, 0, 0);
  
  cv::putText (original_data.combo_panel, current_combo_str, cv::Point (str_x, str_y), 
              font_face, font_scale, text_color, thickness, cv::LINE_AA);

  objects[2].set_image (original_data.combo_panel);
}

void action::draw_results_data(cv::Mat &frame)
{
  std::string score_str = "Score: " + std::to_string (res_data.score);
  std::string max_combo_str = "Max combo: " + std::to_string (res_data.max_combo);
  
  int font_face = cv::FONT_HERSHEY_TRIPLEX | cv::FONT_ITALIC;
  double font_scale = 1.5;
  int thickness = 3;
  
  int baseline = 0;
  cv::Size score_str_size = cv::getTextSize (score_str, font_face, font_scale, thickness, &baseline);
  cv::Size max_combo_str_size = cv::getTextSize (max_combo_str, font_face, font_scale, thickness, &baseline);
  
  int margin_x = 20;
  int margin_y = 40;
  
  int max_str_width = std::max (score_str_size.width, max_combo_str_size.width);
  int total_height = score_str_size.height + max_combo_str_size.height + 25;
  
  int bg_x = frame.size ().width - max_str_width - margin_x * 2;
  int bg_y = margin_y / 2;
  
  cv::rectangle(frame, 
                cv::Rect (bg_x, bg_y, max_str_width + 2 * margin_x, total_height + margin_y),
                cv::Scalar (32, 32, 36),
                cv::FILLED);             
  
  cv::rectangle(frame,
                cv::Rect (bg_x, bg_y, max_str_width + 2 * margin_x, total_height + margin_y),
                cv::Scalar (100, 100, 110),
                2,
                cv::LINE_AA);
  
  int score_x = frame.size ().width - max_str_width - margin_x;
  int max_combo_x = score_x;

  int score_y = margin_y + score_str_size.height;
  int max_combo_y = score_y + max_combo_str_size.height + 15;
  
  cv::Scalar text_color (230, 230, 230);
  
  cv::putText (frame, score_str, cv::Point (score_x, score_y), 
              font_face, font_scale, text_color, thickness, cv::LINE_AA);
  cv::putText (frame, max_combo_str, cv::Point (max_combo_x, max_combo_y), 
              font_face, font_scale, text_color, thickness, cv::LINE_AA);
}

void action::draw_keys (cv::Mat &frame, key::input_system &input)
{
  const int cy = frame.size ().height / 1.15; 
  draw_key (frame, cv::Point (frame.size ().width / 10 - screen_size.height / 5, cy), "D", input.is_left_blue_pressed, cv::Scalar (192, 192, 102, 255 ));
  draw_key (frame, cv::Point (2 * frame.size ().width / 10 - screen_size.height / 5, cy), "F", input.is_right_blue_pressed, cv::Scalar (192, 192, 102, 255 ));
  draw_key (frame, cv::Point (8 * frame.size ().width / 10, cy), "J", input.is_left_red_pressed, cv::Scalar ( 40, 70, 249, 255 ));
  draw_key (frame, cv::Point (9 * frame.size ().width / 10, cy), "K", input.is_right_red_pressed, cv::Scalar ( 40, 70, 249, 255 ));
}

void action::draw_key (cv::Mat &frame, cv::Point pos, const char *label, bool is_down, cv::Scalar color)
{
  cv::Rect r (pos.x, pos.y, screen_size.height / 5, screen_size.height / 6);
  cv::Scalar bg = is_down ? cv::Scalar(60, 60, 60) : color;
  
  cv::rectangle (frame, r, bg, cv::FILLED, cv::LINE_AA);
  cv::rectangle (frame, r, {180, 180, 180}, 1, cv::LINE_AA);

  int baseline = 0;
  cv::Size size = cv::getTextSize (label, cv::FONT_HERSHEY_SIMPLEX, 0, 0, &baseline);
  cv::Point tp (r.x + (r.width - size.width) / 2, r.y + (r.height - size.height) / 2 + 5);
  cv::putText (frame, label, tp, cv::FONT_HERSHEY_SIMPLEX, 3, {230, 230, 230}, 5, cv::LINE_AA);
}

void action::reset ()
{
  for (auto &circle : circles)
  {
    circle.active = false;
  }
  update_circle_objects ();
  elapsed = 0.f;
}

void action::update (const float delta_t, key::input_system &input)
{
  float audio_time_s = 0.f;
  bool  have_audio   = music_track.loaded;

  if (have_audio)
    {
      audio_time_s = audio::get_music_time_s (music_track);
    }

  float map_time_s = 0.f;
  if (have_audio)
    {
      map_time_s = audio_time_s + bm.offset_ms * 0.001f;
      elapsed    = map_time_s;
    }
  else
    {
      elapsed += delta_t;
      map_time_s = elapsed;
    }

  try_spawn_notes_from_map (map_time_s);

  update_combo_panel ();
  draw_keys (objects[0].get_image (), input);
  draw_results_data (objects[0].get_image ());
  handle_key_press (input);

  update_circles (0.f);
  update_circle_objects ();
}

void action::try_spawn_notes_from_map (float map_time_s)
{
  if (next_note_idx >= bm.notes.size())
    return;

  const int start_x = screen_size.width + bm.lead_margin_px;
  const int dist_px = start_x - hit_x;
  const float lead_time_s = dist_px / bm.scroll_speed;

  while (next_note_idx < bm.notes.size())
  {
    const auto &mn = bm.notes[next_note_idx];
    float t_hit_s = mn.t_ms * 0.001f;

    if (map_time_s < t_hit_s - lead_time_s)
      break;

    spawn_circle_from_note (mn, map_time_s);
    ++next_note_idx;
  }
}

void action::spawn_circle_from_note (const map_note &note, float now_s)
{
  for (auto &c : circles)
  {
    if (!c.active)
    {
      const int start_x = screen_size.width + bm.lead_margin_px;

      c.color    = note.color;
      c.size     = note.size;
      c.position = cv::Point2f((float)start_x, (float)hit_y);
      c.speed    = bm.scroll_speed;
      c.active   = true;

      c.spawn_t  = now_s;
      c.start_x  = (float)start_x;

      return;
    }
  }
}

action::~action () 
{

}

void action::spawn_circle ()
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

void action::update_circles (const float /*delta_t*/)
{
  float t_now = elapsed;   // <-- вот так

  for (auto &c : circles)
  {
    if (!c.active) continue;

    float lived = t_now - c.spawn_t;
    if (lived < 0.f) lived = 0.f;

    c.position.x = c.start_x - c.speed * lived;

    if (c.position.x < hit_left_big_border)
    {
      c.active = false;
      res_data.current_combo = 0;
    }
  }

  res_data.max_combo = std::max (res_data.current_combo, res_data.max_combo);
}

void action::update_circle_objects ()
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

bool action::could_circle_be_hitted (const taiko_circle &circle)
{
  int circle_x = static_cast<int> (std::lround (circle.position.x));
  bool pass_left_small_border = hit_right_small_border > circle_x - hit_r_outer + min_division;
  bool pass_left_big_border = hit_right_big_border > circle_x - hit_r_big + min_division;
  bool not_pass_right_small_border = circle_x + hit_r_outer > hit_left_small_border + min_division;
  bool not_pass_right_big_border = circle_x + hit_r_big > hit_left_big_border + min_division;
  return (circle.size == taiko_size::small 
      ? (pass_left_small_border && not_pass_right_small_border)
      : (pass_left_big_border && not_pass_right_big_border));
}

void action::handle_key_press (key::input_system &input)
{
  bool is_blue = input.is_blue_pressed ();
  bool is_red = input.is_red_pressed ();
  if (!is_red && !is_blue)
    return;

  taiko_color color_pressed = (is_blue ? taiko_color::blue : taiko_color::red);

  for (auto &circle : circles)
  {
    if (!circle.active || !could_circle_be_hitted (circle))
      continue;

    if (color_pressed == circle.color)
      {
        res_data.score += 300;
        ++res_data.current_combo;
        circle.active = false;
      }
  }
}

}
