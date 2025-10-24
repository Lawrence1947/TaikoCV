#include "object.h"

namespace kernel
{

object::object (const cv::Mat &image_, const cv::Rect rect_) 
  : image (image_), rect (rect_)
{}

object::~object () {}

};
