#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

#define HRES 640
#define VRES 480

// Display window
const char timg_window_name[] = "Edge Detector Transform";

int lowThreshold = 0;
const int max_lowThreshold = 100;
int kernel_size = 3;
int edgeThresh = 1;
int ratio_val = 3; // renamed to avoid conflict with std::ratio

Mat canny_frame, timg_gray, timg_grad;
Mat frame;

// Callback for trackbar
void CannyThreshold(int, void*)
{
    if (frame.empty()) return;

    cvtColor(frame, timg_gray, COLOR_RGB2GRAY);
    blur(timg_gray, canny_frame, Size(3, 3));
    Canny(canny_frame, canny_frame, lowThreshold, lowThreshold * ratio_val, kernel_size);

    timg_grad = Scalar::all(0);
    frame.copyTo(timg_grad, canny_frame);

   // imshow(timg_window_name, timg_grad);

    imwrite("canny_output.jpg", timg_grad);
}

int main(int argc, char** argv)
{

	// No arguments? Use default webcam
    if (argc == 1)
    {
        cout << "Using default camera (device 0)" << endl;
        VideoCapture capture(0);
        if (!capture.isOpened()) {
            cerr << "Error: Could not open camera.\n";
            return -1;
        }

        capture.set(CAP_PROP_FRAME_WIDTH, HRES);
        capture.set(CAP_PROP_FRAME_HEIGHT, VRES);

        namedWindow(timg_window_name, WINDOW_AUTOSIZE);
        createTrackbar("Min Threshold:", timg_window_name, &lowThreshold, max_lowThreshold, CannyThreshold);

        while (true)
        {
            capture >> frame;
            if (frame.empty()) break;

            CannyThreshold(0, 0);

            char key = (char)waitKey(33);
            if (key == 'q') break;
        }

        capture.release();
        destroyAllWindows();
    }
    else
    {
        // Try to read image from argument
        frame = imread(argv[1]);
        if (frame.empty())
        {
            cerr << "Error: Could not read image file " << argv[1] << endl;
            return -1;
        }

        cout << "Applying Canny edge detection to image: " << argv[1] << endl;

        namedWindow(timg_window_name, WINDOW_AUTOSIZE);
        createTrackbar("Min Threshold:", timg_window_name, &lowThreshold, max_lowThreshold, CannyThreshold);

        // Show the result and wait for user to close
        CannyThreshold(0, 0);
        waitKey(0);
        destroyAllWindows();
    }

    return 0;
    }

