#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <fstream>
#include "utils.h"

class BoundingBoxer {
public:
  BoundingBoxer(std::string inputFilePath, int deviceNumber = 0,
               int cameraWidth = 10000, int cameraHeight = 10000);

  static void mouseHandler(int event, int x, int y, int, void* imgPointer);
  static cv::Point boundingCorner1, boundingCorner2;
  static cv::Rect boundingBox;
};
