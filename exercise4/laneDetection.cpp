#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
	if(argc< 2){
		cout <<"usage : ./lane_detector <vidio_file>"<<endl;
		return -1;
	}
	String videoPath = argv[1];
	VideoCapture cap(videoPath);

	if(!cap.isOpened()){
	cerr<<"Error: Could not open a video file."<<endl;
	return -1;
	}

	Mat frame, gray, edges, cdst, cdstP;

	while(true){
		cap >> frame;
		if(frame.empty())
			break;

		cvtColor(frame, gray, COLOR_BGR2GRAY);

		Canny(gray, edges, 50, 200, 3);

		cvtColor(edges, cdst, COLOR_GRAY2BGR);
		cdstP = frame.clone();

		//hough tranformation
		vector<Vec2f> lines;
		HoughLines(edges, lines, 1, CV_PI / 180, 150);
		for(size_t i = 0; i< lines.size(); i++){
			float rho = lines[i][0], theta = lines[i][1];
			Point pt1, pt2;
			double a =cos(theta), b=sin(theta);
			double x0 = a* rho, y0 = b * rho;
			pt1.x = cvRound(x0 + 1000 * (-b));
			pt1.y = cvRound(y0 + 1000 * (a));
			pt2.x = cvRound(x0 - 1000 * (-b));
			pt2.y = cvRound(y0 - 1000 * (a));
			line(cdst, pt1, pt2, Scalar(0, 255, 0), 2, LINE_AA);
		}

		// Probabilistic Hough Tranformation
		vector<Vec4i> linesP;
		HoughLinesP(edges, linesP, 1, CV_PI/ 180, 50, 50, 10);
		for(size_t i = 0; i< linesP.size(); i++){
			Vec4i l = linesP[i];
			line(cdstP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 0, 0), 2, LINE_AA);
		}

		
		imshow("standard Hough", cdst);
		imshow("Probabilistic Hough", cdstP);

		if(waitKey(30) >=0 ){
		break;
		}


	}

	cap.release();
	destroyAllWindows();
	return 0;
}
