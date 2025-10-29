#include "results.h"

#include <stdio.h>

namespace game
{
  
results::results (const cv::Size &screen_size_, results_data *res_data_) : screen_size (screen_size_), res_data (res_data_)
{
  // background
  original_data.background = cv::Mat::zeros(screen_size, CV_8UC3);

  cv::Rect fullscreen (0, 0, screen_size.width, screen_size.height);

  kernel::object background (original_data.background, fullscreen);

  objects.push_back (background);

  // results panel
  cv::Rect panel_rect (
    screen_size.width  / 5,
    screen_size.height / 5,
    screen_size.width  * 3 / 5,
    screen_size.height * 3 / 5
  );

  original_data.panel = cv::Mat (panel_rect.height, panel_rect.width, CV_8UC3, cv::Scalar (30, 30, 34));

  cv::rectangle (
    original_data.panel,
    cv::Rect (0, 0, original_data.panel.cols, original_data.panel.rows),
    cv::Scalar (180, 180, 190),
    6,
    cv::LINE_AA
  );

  std::string score_str     = "SCORE: "     + std::to_string (res_data->score);
  std::string max_combo_str = "MAX COMBO: " + std::to_string (res_data->max_combo);

  int font_face = cv::FONT_HERSHEY_TRIPLEX | cv::FONT_ITALIC;
  int baseline = 0;
  double font_scale = (panel_rect.height / 400.0);
  int thickness = std::max (2, (int)(font_scale * 3));

  cv::Size score_sz = cv::getTextSize (score_str, font_face, font_scale, thickness, &baseline);
  cv::Size combo_sz = cv::getTextSize (max_combo_str, font_face, font_scale, thickness, &baseline);

  int x_score = (original_data.panel.cols - score_sz.width) / 2;
  int x_combo = (original_data.panel.cols - combo_sz.width) / 2;

  int y_center = original_data.panel.rows / 2;
  int y_score  = y_center - combo_sz.height - 20;
  int y_combo  = y_center + combo_sz.height + 20;

  cv::Scalar text_shadow (0, 0, 0);
  cv::Scalar text_color  (235, 235, 235);

  cv::putText (original_data.panel, score_str, cv::Point (x_score + 3, y_score + 3),
              font_face, font_scale, text_shadow, thickness + 2, cv::LINE_AA);
  cv::putText (original_data.panel, score_str, cv::Point (x_score, y_score),
              font_face, font_scale, text_color, thickness, cv::LINE_AA);

  cv::putText (original_data.panel, max_combo_str, cv::Point (x_combo + 3, y_combo + 3),
              font_face, font_scale, text_shadow, thickness + 2, cv::LINE_AA);
  cv::putText (original_data.panel, max_combo_str, cv::Point (x_combo, y_combo),
              font_face, font_scale, text_color, thickness, cv::LINE_AA);

  kernel::object panel_obj (original_data.panel, panel_rect);
  objects.push_back (panel_obj);
}

void results::update (const float delta_t)
{
  
}

results::~results () 
{

}

}
