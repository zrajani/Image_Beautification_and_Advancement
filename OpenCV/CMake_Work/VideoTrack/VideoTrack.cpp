#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <fstream>

using namespace std;

int g_slider_position = 0;
int g_run = 1, g_dontset = 0; //start in single step mode
cv::VideoCapture g_cap;

void onTrackbarSlide (int pos, void *)
{
  g_cap.set (cv::CAP_PROP_POS_FRAMES, pos);
  if(!g_dontset)
    g_run = 1;
  g_dontset = 0;
}

int main (int argc, char** argv)
{
  cv::namedWindow("VideoTrackBall", cv::WINDOW_AUTOSIZE);
  g_cap.open(string(argv[1]));
  int frames = (int) g_cap.get(cv::CAP_PROP_FRAME_COUNT);
  int tmpw = (int) g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
  int tmph = (int) g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);

  std::cout << "Video has " << frames << "frames of dimesnions( "<< tmpw <<", " << tmph << ")."<<endl;

  cv::createTrackbar("Position", "VideoTrackBall", &g_slider_position, frames, onTrackbarSlide);

  cv::Mat frame;

  for (; ;)
  {
    if(g_run != 0)
    {
      g_cap >> frame; if(frame.empty()) break;
      int current_pos = (int) g_cap.get(cv::CAP_PROP_POS_FRAMES);
      g_dontset = 1;

      cv::setTrackbarPos("Position","VideoTrackBall",current_pos);
      cv::imshow("VideoTrackBall",frame);

      g_run-=1;
    }
    char c = (char) cv::waitKey(10);
    if( c == 's' ) //single step
    { g_run = 1; cout <<"Single step run = " <<g_run <<endl;}
    if( c == 'r' ) //run mode
    { g_run = -1; cout << "Run mode, run = "<<g_run<<endl;}
    if( c == 27 )
      break;

  }

  return (0);
}
