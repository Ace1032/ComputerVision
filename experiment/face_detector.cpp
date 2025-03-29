
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;
using namespace std;

int main(){
	VideoCapture cap(0);
	if( !cap.isOpened()){
		cerr <<"Error: camera not accessible\n";
		return -1;
	}

	CascadeClassifier face_cascade;
	if (!face_cascade.load("/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml")){
	cerr<<"Enter: Could not load face cascade\n";
	return -1;
	}


	namedWindow("Camera live", WINDOW_AUTOSIZE);

	Mat frame, gray;
	vector<Rect> faces;

	while(true){
		cap >> frame;
		if(frame.empty()) break;
		
		cvtColor(frame, gray, COLOR_BGR2GRAY);
		equalizeHist(gray, gray);

		face_cascade.detectMultiScale(gray, faces);

		for(const auto& face : faces){
			rectangle(frame, face, Scalar(0,255,0),2);
		}

		imshow("Face Detector", frame);




		if(waitKey(30) == 27) break;
	}
	return 0;
}
