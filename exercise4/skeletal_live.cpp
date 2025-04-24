#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
	VideoCapture cap(0);
	if(!cap.isOpened()){
	cerr <<"Error: Could not open camera."<<endl;
	return -1;
	}

	int frame_count =0;
	const int max_frames = 3000;

	while(frame_count<max_frames){
		Mat src, gray, binary, mfblur;
		cap>>src;
		if(src.empty()) break;

		cvtColor(src, gray, COLOR_BGR2GRAY);

		threshold(gray, binary, 170, 255, THRESH_BINARY);
		binary = 255 - binary;

		medianBlur(binary, mfblur, 3);

		Mat skel(mfblur.size(), CV_8UC1, Scalar(0));
		Mat temp, eroded;
		Mat element = getStructuringElement(MORPH_CROSS, Size(3, 3));
		bool done = false;
		int iterations =0;

		do{
			erode(mfblur, eroded, element);
			dilate(eroded, temp, element);
			subtract(mfblur, temp, temp);
			bitwise_or(skel, temp, skel);
			eroded.copyTo(mfblur);
			done = (countNonZero(mfblur)== 0);
			iterations++;
		} while(!done && (iterations <100));

		imshow("Skeleton Tranform", skel);
		imshow("Original", src);


	//	ostringstream filename;
	//	filename <<"frames/frame_"<<setfill('0')<<frame_count <<".jpg";
	//	imwrite(filename.str(), skel);

	//	frame_count++;

		if(waitKey(1)>=0) break;

	}
		cap.release();
		destroyAllWindows();
		cout<<"Finished. frames saved: "<<frame_count<<endl;
		return 0;

	
}
