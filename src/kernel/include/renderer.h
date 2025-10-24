#ifndef RENDERER_H
#define RENDERER_H

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

#include "kernel/include/object.h"

namespace kernel
{

class renderer
{
public:
  explicit renderer (const cv::Size &screen_size_) : screen_size (screen_size_) {}

  void render (cv::Mat &frame, std::vector<kernel::object> objects);

protected:
  inline void blit_with_alpha (cv::Mat &frame, const cv::Mat &src, const cv::Rect &dst_rect);

private:
  cv::Size screen_size;
};

}

#endif