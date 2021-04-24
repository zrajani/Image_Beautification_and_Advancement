#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;

int main(int argc, char** argv)
{
  //cv::namedWindow("Video Play",cv::WINDOW_AUTOSIZE);
  cv::VideoCapture cap;
  cap.open(string(argv[1]));

  cv::Mat frame;

  for(;;)
  {
    cap >> frame;
    if (frame.empty()) break;   // Run out of file

    cv::imshow  ("Simple Video", frame);

    if ( (char) cv::waitKey(33) >= 0 ) break;

  }

  return (0);
}
