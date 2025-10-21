#include <opencv2/opencv.hpp>

int main ()
{
  cv::namedWindow ("OpenCV test", cv::WINDOW_AUTOSIZE);

  cv::Mat image = cv::imread ("../resources/taiko_load.jpg", 1);

  cv::imshow ("OpenCV test", image);

  cv::waitKey (0);
  cv::destroyAllWindows ();
}