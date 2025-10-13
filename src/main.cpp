#include <opencv2/opencv.hpp>

int main ()
{
    setenv("QT_LOGGING_RULES", "*=false", 1);
    cv::namedWindow ("OpenCV test", cv::WINDOW_AUTOSIZE);

    cv::Mat image = cv::Mat::zeros(480, 640, CV_8UC3);
    image.setTo (cv::Scalar (255, 0, 0));

    cv::putText (image, "Test Image", cv::Point (50, 50), cv::FONT_HERSHEY_SIMPLEX,
            1, cv::Scalar (0, 255, 0), 2);

    cv::imshow ("OpenCV test", image);

    cv::waitKey (0);
    cv::destroyAllWindows ();
}