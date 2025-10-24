#ifndef RENDERER_H
#define RENDERER_H

#include <opencv2/core.hpp>

namespace kernel
{

class renderer
{
public:
  void render (cv::Mat &frame, const cv::Mat &image);

};

}

#endif