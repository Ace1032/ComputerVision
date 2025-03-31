#include <opencv2/opencv.hpp>

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;

int main(){
	VideoCapture cap(0);
	if( !cap.isOpened()){
	return -1;
	}

	namedWindow("Camera live", WINDOW_AUTOSIZE);

	Mat frame;
	while(true){
		cap >> frame;
		if(frame.empty()) break;

		rectangle(frame, Point(0,0), Point(frame.cols-1, frame.rows-1), Scalar(0,0,255),4);

		int centerX = frame.cols /2;
		int centerY = frame.rows /2;

		line(frame, Point(centerX, 0), Point(centerX, frame.rows), Scalar(0, 255, 255), 1);
		line(frame, Point(0, centerY), Point(frame.cols, centerY), Scalar(0, 255, 255), 1);

		imshow("Camera live", frame);
		if(waitKey(30) >= 0) break;
	}
	return 0;
}
