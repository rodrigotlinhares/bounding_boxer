#include "bounding_boxer.h"

cv::Point BoundingBoxer::boundingCorner1;
cv::Point BoundingBoxer::boundingCorner2;
cv::Rect BoundingBoxer::boundingBox;

BoundingBoxer::BoundingBoxer(std::string inputFilePath, int deviceNumber,
                           int cameraWidth, int cameraHeight) {
  std::string folderPath = Utils::folderPath(inputFilePath);
  std::ifstream input(&inputFilePath[0]);
  std::ofstream output;
  output.open(&(folderPath + "output.dat")[0], std::ifstream::out | std::ifstream::app);
  std::string imageName;
  cv::Mat image;

  cv::namedWindow("Bounding Box Selection");
  cv::setMouseCallback("Bounding Box Selection", BoundingBoxer::mouseHandler, &image);
  while(input >> imageName) {
    BoundingBoxer::boundingCorner1 = cv::Point(-1, -1);
    BoundingBoxer::boundingCorner2 = cv::Point(-1, -1);
    BoundingBoxer::boundingBox = cv::Rect(cv::Point(-1, -1), cv::Point(-1, -1));
    image = cv::imread(folderPath + imageName);

    cv::imshow("Bounding Box Selection", image);
    int key = cv::waitKey();
    if(key == 'q')
      break;

    cv::Rect bb = BoundingBoxer::boundingBox;
    output << imageName << " 1 " << bb.x << " " << bb.y << " " << bb.width << " " << bb.height
           << "\n";
  }
}

void BoundingBoxer::mouseHandler(int event, int x, int y, int, void* imgPointer) {
  cv::Mat img = *(cv::Mat*)imgPointer;
  cv::Mat imgCopy;
  img.copyTo(imgCopy);

  if(event == CV_EVENT_LBUTTONDOWN) {
    if(BoundingBoxer::boundingCorner1 == cv::Point(-1, -1)) {
      BoundingBoxer::boundingCorner1 = cv::Point(x, y);
      return;
    }

    if(BoundingBoxer::boundingCorner2 == cv::Point(-1, -1)) {
      BoundingBoxer::boundingCorner2 = cv::Point(x, y);
      BoundingBoxer::boundingBox = cv::Rect(BoundingBoxer::boundingCorner1,
                                           BoundingBoxer::boundingCorner2);
      rectangle(imgCopy, BoundingBoxer::boundingBox, cv::Scalar(0, 0, 255));
    }

    cv::Point newPoint(x, y);
    int distanceTL = Utils::euclideanDistance(newPoint, BoundingBoxer::boundingCorner1);
    int distanceBR = Utils::euclideanDistance(newPoint, BoundingBoxer::boundingCorner2);
    cv::Point closest = distanceTL < distanceBR ? BoundingBoxer::boundingCorner1 :
                                                  BoundingBoxer::boundingCorner2;

    if(closest == BoundingBoxer::boundingCorner1)
      BoundingBoxer::boundingCorner1 = newPoint;
    else
      BoundingBoxer::boundingCorner2 = newPoint;

    img.copyTo(imgCopy);
    BoundingBoxer::boundingBox = cv::Rect(BoundingBoxer::boundingCorner1,
                                         BoundingBoxer::boundingCorner2);
    rectangle(imgCopy, BoundingBoxer::boundingBox, cv::Scalar(0, 0, 255));
    cv::imshow("Bounding Box Selection", imgCopy);
  }
}

int main(int argc, const char** argv) {
  if(argc == 1) {
    std::cout << "Error: output folder path not specified." << std::endl;
    return 1;
  }
  
  BoundingBoxer p(argv[1]);
  return 0;
}
