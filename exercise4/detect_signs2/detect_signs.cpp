#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>
#include <iostream>

using namespace cv;
using namespace std;
using namespace cv::ml;


int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Usage: ./detect_signs_hog <video_file>" << endl;
        return -1;
    }



    Ptr<SVM> svm = SVM::load("stop_sign_svm.yml");
    if (svm->empty()) {
        cerr << "Failed to load SVM model." << endl;
        return -1;
    }


    HOGDescriptor hog(Size(64, 64), Size(16,16), Size(8,8), Size(8,8), 9);
    hog.setSVMDetector(svm->getSupportVectors().row(0));


    VideoCapture cap(argv[1]);
    if (!cap.isOpened()) {
        cerr << "Error opening video file." << endl;
        return -1;
    }


    Mat frame, gray;
    while (cap.read(frame)) {
        resize(frame, frame, Size(frame.cols / 2, frame.rows / 2));
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        vector<Rect> detections;
        hog.detectMultiScale(gray, detections, 0, Size(8,8), Size(32,32), 1.05, 2);

        for (const Rect& r : detections) {
            rectangle(frame, r, Scalar(0, 255, 0), 2);
            putText(frame, "Stop Sign", Point(r.x, r.y - 5), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0,255,0), 2);
        }

        imshow("HOG + SVM Detection", frame);
        if (waitKey(30) == 27) break; 
    }

    cap.release();
    destroyAllWindows();
    return 0;
}
