#ifndef OBJECT_H
#define OBJECT_H

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

namespace kernel
{

class object
{
public:
  object (const cv::Mat &image_, const cv::Rect rect_) ;

  cv::Mat &get_image () { return image; }
  cv::Rect &get_rect () { return rect; }

  ~object ();
private:
  cv::Mat image;
  cv::Rect rect;
};

}

#endif