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

int main(int argc, char** argv)
{
    int dev = 0;
    if (argc > 1)
    {
        sscanf(argv[1], "%d", &dev);
        printf("Using camera device: %s\n", argv[1]);
    }
    else
    {
        printf("Using default camera device 0\n");
    }

    VideoCapture capture(dev);
    if (!capture.isOpened())
    {
        cerr << "ERROR: Could not open camera " << dev << endl;
        return -1;
    }

    capture.set(CAP_PROP_FRAME_WIDTH, HRES);
    capture.set(CAP_PROP_FRAME_HEIGHT, VRES);

    Mat frame, gray;
    vector<Vec3f> circles;

    namedWindow("Capture Example", WINDOW_AUTOSIZE);

    while (true)
    {
        capture >> frame;
        if (frame.empty()) break;

        cvtColor(frame, gray, COLOR_BGR2GRAY);
        GaussianBlur(gray, gray, Size(9, 9), 2, 2);

        HoughCircles(gray, circles, HOUGH_GRADIENT, 1, gray.rows / 8, 100, 50, 0, 0);

        printf("circles.size = %zu\n", circles.size());

        for (size_t i = 0; i < circles.size(); i++)
        {
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            circle(frame, center, 3, Scalar(0, 255, 0), -1, LINE_AA);
            circle(frame, center, radius, Scalar(0, 0, 255), 3, LINE_AA);
        }

        imshow("Capture Example", frame);

        char c = (char)waitKey(10);
        if (c == 'q' || c == 27) break;  // Press 'q' or ESC to exit
    }

    capture.release();
    destroyAllWindows();
    return 0;
}
