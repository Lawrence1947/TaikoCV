#include "renderer.h"

#include <opencv2/opencv.hpp>

#include "globals.h"

namespace kernel
{

void renderer::render (cv::Mat &frame, const cv::Mat &image)
{
  image.convertTo (frame, CV_8UC3, 1.);
}

}