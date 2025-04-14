#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    Mat mat_frame, mat_gray, mat_diff, mat_gray_prev;
    VideoCapture vcap;
    unsigned int diffsum, maxdiff;
    double percent_diff;
    char difftext[20];

    // Open the default camera (device 0)
    if (!vcap.open(0))
    {
        cerr << "Error opening video stream or file" << endl;
        return -1;
    }

    cout << "Opened default camera interface" << endl;

    // Wait for first valid frame
    while (!vcap.read(mat_frame)) {
        cout << "No frame available, waiting..." << endl;
        waitKey(33);
    }

    // Convert first frame to grayscale
    cvtColor(mat_frame, mat_gray, COLOR_BGR2GRAY);

    mat_diff = mat_gray.clone();
    mat_gray_prev = mat_gray.clone();

    maxdiff = mat_diff.cols * mat_diff.rows * 255;

    while (true)
    {
        if (!vcap.read(mat_frame)) {
            cerr << "No frame" << endl;
            waitKey();
        }

        // Convert to grayscale
        cvtColor(mat_frame, mat_gray, COLOR_BGR2GRAY);

        // Frame difference
        absdiff(mat_gray_prev, mat_gray, mat_diff);

        // Total pixel difference
        diffsum = (unsigned int)sum(mat_diff)[0];

        percent_diff = ((double)diffsum / (double)maxdiff) * 100.0;
        printf("percent diff = %lf%%\n", percent_diff);
        sprintf(difftext, "%8d", diffsum);

        // Show motion change if greater than threshold
        if (percent_diff > 0.5)
        {
            putText(mat_diff, difftext, Point(30, 30),
                    FONT_HERSHEY_COMPLEX_SMALL, 0.8,
                    Scalar(200, 200, 250), 1, LINE_AA);
        }

        // Show frames
        imshow("Gray Example", mat_gray);
        imshow("Gray Previous", mat_gray_prev);
        imshow("Gray Diff", mat_diff);

        // Exit on 'q'
        char c = (char)waitKey(33);
        if (c == 'q' || c == 27) break;

        // Update previous frame
        mat_gray_prev = mat_gray.clone();
    }

    return 0;
}
