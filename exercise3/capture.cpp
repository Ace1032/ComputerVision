#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#define HRES 640
#define VRES 480

int main(int argc, char** argv)
{
    int dev = 0;
    if (argc > 1) {
        sscanf(argv[1], "%d", &dev);
        cout << "Using camera device: " << dev << endl;
    } else {
        cout << "Using default camera device (0)" << endl;
    }

    VideoCapture cap(dev);
    if (!cap.isOpened()) {
        cerr << "ERROR: Unable to open the camera" << endl;
        return -1;
    }

    cap.set(CAP_PROP_FRAME_WIDTH, HRES);
    cap.set(CAP_PROP_FRAME_HEIGHT, VRES);

    namedWindow("Capture Example", WINDOW_AUTOSIZE);

    Mat frame, gray, canny_frame, cdst;
    vector<Vec4i> lines;

    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        cvtColor(frame, gray, COLOR_BGR2GRAY);
        Canny(gray, canny_frame, 50, 200, 3);
        cvtColor(canny_frame, cdst, COLOR_GRAY2BGR);

        HoughLinesP(canny_frame, lines, 1, CV_PI/180, 50, 50, 10);
        for (size_t i = 0; i < lines.size(); i++) {
            Vec4i l = lines[i];
            line(frame, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
        }

        imshow("Capture Example", frame);

        char c = (char)waitKey(10);
        if (c == 'q' || c == 27) break; // Press 'q' or ESC to quit
    }

    cap.release();
    destroyAllWindows();

    return 0;
}

