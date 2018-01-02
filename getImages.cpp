#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <sstream>
#include <unistd.h>
#include <thread>

cv::VideoCapture TheVideoCapturer;
cv::Mat bgrMap;
cv::Mat contours;
int cont=0;

void tomar_foto(){
  int numSnapshot = 0;
  cv::Mat bgrMap1;
  std::string snapshotFilename = "0";

  while(cont < 36){
    usleep(45000000/36);
    TheVideoCapturer.retrieve(bgrMap1);
    cv::cvtColor(bgrMap1, contours, CV_BGR2GRAY);
    cv::imwrite("images/"+ snapshotFilename + ".png", contours);
    numSnapshot++;
    snapshotFilename = static_cast<std::ostringstream*>(&(std::ostringstream() << numSnapshot))->str();
    cont++;
  }
}

int main(int argc, char *argv[]) {
  char key = 0;

  TheVideoCapturer.open("http://192.168.1.39:8080/video?x.mjpeg");

  if (!TheVideoCapturer.isOpened()) {
    std::cerr<<"Could not open video"<<std::endl;
    return -1;
  }

  std::thread fotografo;
  fotografo=std::thread(tomar_foto);

  while(TheVideoCapturer.grab() && cont<36){
    TheVideoCapturer.retrieve(bgrMap);
    cv::waitKey(20);
  }

  fotografo.join();

/*
  while (key!=27 && TheVideoCapturer.grab()) {
    TheVideoCapturer.retrieve(bgrMap);

    //cv::flip(bgrMap, bgrMap, 1);  //+++

 //   cv::imshow("BGR image", bgrMap);
    //  contours = bgrMap;
    //cv::Canny(bgrMap, contours,500,1000, 5, true);

    cv::cvtColor(bgrMap, contours, CV_BGR2GRAY);

    cv::imshow("Negative", contours);

    if (key == 115) {
      cv::imwrite(snapshotFilename + ".png", contours);
      numSnapshot++;
      snapshotFilename = static_cast<std::ostringstream*>(&(std::ostringstream() << numSnapshot))->str();
	   }

  key=cv::waitKey(20);
}*/
}
