#include <cv.h>
#include <highgui.h>

class Utils {
public:
  static int euclideanDistance(cv::Point a, cv::Point b);
  static void getImageData(cv::Mat img, uchar* imageData);
  static cv::Mat open(cv::Mat img, cv::Mat erodeKernel, cv::Mat dilateKernel);
  static cv::Mat horizontalConcatenation(cv::Mat m1, cv::Mat m2);
  static std::string folderPath(std::string filePath);
};
