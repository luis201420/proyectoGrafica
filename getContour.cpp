#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <sstream>

int main(int argc, char *argv[]) {
  std::string a;
  if(argc > 1){
    a=argv[1];
  }
  else{
    a="e";
  }
  if(a!="e"){
    cv::Mat img = cv::imread("images/"+a+".png");

    cv::Mat f;
    cv::cvtColor(img, f, CV_BGR2GRAY);

    cv::Size s = f.size();
    std::cerr << s.height << " " << s.width << std::endl;

    cv::Vec3f intensity;

    int r,g,b,prom;

    for(int i=0;i<s.height;i++){
      for(int j=0;j<s.width;j++){
        intensity = f.at<cv::Vec3b>(i, j);
        r=intensity.val[0];
        g=intensity.val[1];
        b=intensity.val[2];
        prom=(r+g+b)/3;
        if(prom<230){
          intensity.val[0]=0;
          intensity.val[1]=0;
          intensity.val[2]=0;
          f.at<cv::Vec3b>(i, j) = intensity;
        }
      }
    }

  cv::imwrite("contours/"+ a + ".png", f);
  }
}
