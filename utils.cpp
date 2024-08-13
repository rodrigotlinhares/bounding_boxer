#include "utils.h"

int Utils::euclideanDistance(cv::Point a, cv::Point b) {
  int diff_x = a.x - b.x;
  int diff_y = a.y - b.y;
  return sqrt(diff_x * diff_x + diff_y * diff_y);
}

void Utils::getImageData(cv::Mat img, uchar* imageData) {
  int imgSize = img.rows * img.cols;
  int i = 0;
  for(int row = 0; row < img.rows; row++) {
    for(int col = 0; col < img.cols; col++) {
      cv::Vec3b pixel = img.at<cv::Vec3b>(row, col);
      imageData[i] = pixel[2];
      imageData[i+1] = pixel[1];
      imageData[i+2] = pixel[0];
      i += 3;
    }
  }
}

cv::Mat Utils::open(cv::Mat img, cv::Mat erodeKernel, cv::Mat dilateKernel) {
  cv::Mat eroded, dilated;
  erode(img, eroded, erodeKernel);
  dilate(eroded, dilated, dilateKernel);
  return dilated;
}

cv::Mat Utils::horizontalConcatenation(cv::Mat m1, cv::Mat m2) {
  cv::Mat result(m1.rows, m1.cols + m2.cols, m1.type());
  cv::Mat left(result, cv::Range(0, m1.rows), cv::Range(0, m1.cols));
  cv::Mat right(result, cv::Range(0, m2.rows), cv::Range(m1.cols, m1.cols + m2.cols));
  m1.copyTo(left);
  m2.copyTo(right);
  return result;
}

std::string Utils::folderPath(std::string filePath) {
  int i = filePath.size() - 1;
  while(filePath[i] != '/')
    i--;
  std::string result(filePath.substr(0, i + 1));
  if(result[result.size() - 1] != ('/'))
    result += "/";
  return result;
}
