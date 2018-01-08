#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <sstream>
#include <fstream>

int angle = 0;
int cont = 0;

//30% posillo 60% florero

void getXYZ(int i, int j,int e){
  e*=0.3;
  float x = j;
  float y = i;
  float z = y;
  float d = (e-j);

  x = d * cos (angle);
  y = d * sin (angle);

  cont++;

  std::ofstream archivo ("prueba.txt" , std::fstream::app);

  if (archivo.is_open())
  {
    archivo<< x << " " << y << " " << z << std::endl;
    archivo.close();
  }
}

int main(int argc, char *argv[]) {

    for(int id = 0 ;id<72 ; id++){

      cv::Mat img = cv::imread("contoursP/"+std::to_string(id)+".png");

      cv::Mat f;
      cv::cvtColor(img, f, CV_BGR2GRAY);

      cv::Size s = f.size();
      //1080 1920

      cv::Vec3f intensity;

      int r,g,b,prom;

      for(int i=0;i<s.height;i++){
        for(int j=0;j<s.width;j++){
          intensity = f.at<cv::Vec3b>(i, j);
          r=intensity.val[0];
          g=intensity.val[1];
          b=intensity.val[2];
          prom=(r+g+b)/3;
          if(prom>240){
            getXYZ(i,j,(s.width)/2);
            break;
          }
        }
      }
    angle+=5;
  }
  std::cerr<< cont << std::endl;
}
