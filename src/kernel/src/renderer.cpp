#include "renderer.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

#include "globals.h"

namespace kernel
{

void renderer::render (cv::Mat &frame, std::vector<kernel::object> objects)
{
  for (auto &object : objects)
    {
      blit_with_alpha (frame, object.get_image (), object.get_rect ());
    }
}

inline void renderer::blit_with_alpha (cv::Mat &frame, const cv::Mat &src, const cv::Rect &dst_rect)
{
  if (src.empty ()) 
    return;

  cv::Rect bounds (0, 0, frame.cols, frame.rows);
  cv::Rect roi = dst_rect & bounds;
  if (roi.empty ()) 
    return;

  float sx = static_cast<float> (src.cols) / dst_rect.width;
  float sy = static_cast<float> (src.rows) / dst_rect.height;

  cv::Rect src_rect (
    static_cast<int> ((roi.x - dst_rect.x) * sx),
    static_cast<int> ((roi.y - dst_rect.y) * sy),
    static_cast<int> (roi.width * sx),
    static_cast<int> (roi.height * sy)
  );
  src_rect &= cv::Rect(0, 0, src.cols, src.rows);
  if (src_rect.empty ()) 
    return;

  cv::Mat src_cut = src (src_rect);
  cv::Mat src_resized;
  cv::resize (src_cut, src_resized, roi.size (), 0, 0, cv::INTER_NEAREST);

  cv::Mat src_bgr;
  cv::Mat mask;

  if (src_resized.channels() == 4)
    {
      std::vector<cv::Mat> ch;
      cv::split (src_resized, ch);
      cv::threshold (ch[3], mask, 0, 255, cv::THRESH_BINARY);
      cv::merge (std::vector<cv::Mat>{ch[0], ch[1], ch[2]}, src_bgr);
    }
  else if (src_resized.channels() == 3)
    {
      src_bgr = src_resized;
      mask = cv::Mat(roi.size(), CV_8UC1, cv::Scalar(255));
    }
  else 
    {
      return;
    }

  if (src_bgr.depth () != CV_8U)
    {
      src_bgr.convertTo (src_bgr, CV_8UC3);
    }

  cv::Mat dst_roi = frame (roi);
  src_bgr.copyTo (dst_roi, mask);
}

}