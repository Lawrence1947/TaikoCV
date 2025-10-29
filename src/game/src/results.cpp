#include "results.h"

#include <stdio.h>

namespace game
{
  
results::results (const cv::Size &screen_size_, results_data &res_data_) : screen_size (screen_size_), res_data (res_data_)
{
  objects.reserve (2);
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

  kernel::object panel_obj (original_data.panel, panel_rect);
  objects.push_back (panel_obj);
}

void results::update (const float /*delta_t*/)
{
  cv::Mat &frame = original_data.panel;

  frame.setTo(cv::Scalar(30, 30, 34));

  cv::rectangle(frame,
                cv::Rect(0, 0, frame.cols, frame.rows),
                cv::Scalar(180, 180, 190),
                6, cv::LINE_AA);

  std::string score_str     = "SCORE: "     + std::to_string(res_data.score);
  std::string max_combo_str = "MAX COMBO: " + std::to_string(res_data.max_combo);

  int font_face = cv::FONT_HERSHEY_TRIPLEX | cv::FONT_ITALIC;
  double font_scale = (frame.rows / 400.0);
  int thickness = std::max(2, (int)(font_scale * 3));
  int base = 0;

  cv::Size sz_score = cv::getTextSize(score_str, font_face, font_scale, thickness, &base);
  cv::Size sz_combo = cv::getTextSize(max_combo_str, font_face, font_scale, thickness, &base);

  int x_score = (frame.cols - sz_score.width) / 2;
  int x_combo = (frame.cols - sz_combo.width) / 2;
  int y_center = frame.rows / 2;
  int y_score  = y_center - sz_combo.height - 20;
  int y_combo  = y_center + sz_combo.height + 20;

  cv::Scalar shadow(0,0,0), color(235,235,235);

  cv::putText(frame, score_str,     {x_score+3, y_score+3},  font_face, font_scale, shadow, thickness+2, cv::LINE_AA);
  cv::putText(frame, score_str,     {x_score,   y_score  },  font_face, font_scale, color,  thickness,   cv::LINE_AA);
  cv::putText(frame, max_combo_str, {x_combo+3, y_combo+3},  font_face, font_scale, shadow, thickness+2, cv::LINE_AA);
  cv::putText(frame, max_combo_str, {x_combo,   y_combo  },  font_face, font_scale, color,  thickness,   cv::LINE_AA);

  objects[1].set_image(frame);
}

results::~results () 
{

}

}
