#ifndef RENDERER_H
#define RENDERER_H

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

namespace kernel
{

class renderer
{
public:
  explicit renderer (cv::Size &screen_size_) : screen_size (screen_size_) {}

  void render (cv::Mat &frame, const cv::Mat &image);

private:
  cv::Size screen_size;
};

}

#endif