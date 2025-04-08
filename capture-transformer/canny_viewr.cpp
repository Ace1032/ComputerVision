#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global variables
Mat src, src_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
const char* window_name = "Edge Map";

void CannyThreshold(int, void*)
{
  blur(src_gray, detected_edges, Size(3,3));
  Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * ratio, kernel_size);
  dst = Scalar::all(0);
  src.copyTo(dst, detected_edges);
  imshow(window_name, dst);
}

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    printf("Usage: ./canny_viewer <image_path>\n");
    return -1;
  }

  src = imread(argv[1]);
  if (!src.data)
  {
    printf("Could not open or find the image\n");
    return -1;
  }

  dst.create(src.size(), src.type());
  cvtColor(src, src_gray, COLOR_BGR2GRAY);

  namedWindow(window_name, WINDOW_AUTOSIZE);
  createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);

  CannyThreshold(0, 0);
  waitKey(0);
  return 0;
}

