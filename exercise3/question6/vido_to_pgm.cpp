#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <iomanip>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    if (argc < 2) {
        cout << "Usage: ./video_to_pgm <input_video>" << endl;
        return -1;
    }

    string videoPath = argv[1];
    VideoCapture cap(videoPath);

    if (!cap.isOpened()) {
        cerr << "Error opening video file" << endl;
        return -1;
    }

    int frameCount = 0;
    Mat frame, gray;

    while (cap.read(frame)) {
        // Uncomment ONE of the following lines depending on method:

        // 1. Balanced grayscale conversion
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        // 2. Use only the RED channel (for example)
        // extractChannel(frame, gray, 2);  // 0=Blue, 1=Green, 2=Red

        // Save as .pgm with sequential naming (0000, 0001, etc.)
        stringstream filename;
        filename << "frame" << setfill('0') << setw(4) << frameCount++ << ".pgm";

        imwrite(filename.str(), gray);
    }

    cap.release();
    cout << "Frames written: " << frameCount << endl;
    return 0;
}

