#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <iomanip>

using namespace cv;
using namespace std;






void compute_com(cv::Mat& grayImage, int threshold){
	int rows = grayImage.rows;
	int cols = grayImage.cols;

	long x_sum = 0, y_sum = 0, total_intensity = 0;

	for(int y = 0; y< rows; y++){
		for(int x = 0; x < cols; x++){
			uchar intensity = grayImage.at<uchar>(y, x);
			if(intensity > threshold){
				x_sum += x * intensity;
				y_sum += y * intensity;
				total_intensity += intensity;
			}
		}
	}

	if (total_intensity == 0 ) return;

	int x_bar = x_sum / total_intensity;
	int y_bar = y_sum / total_intensity;

	int arm_len = 10;
	for(int dx = -arm_len; dx <= arm_len; dx++){
		int x = x_bar + dx;
		if(x >= 0 && x <cols)
			grayImage.at<uchar>(y_bar, x) = 255;
	}

	for(int dy = -arm_len; dy <= arm_len; dy++){
		int y = y_bar + dy;
		if(y >= 0 && y < rows)
			grayImage.at<uchar>(y, x_bar) = 255;
	}
}


int main() {

	for(int i=0; i<200; i++){
	stringstream inputName, outputName;
        inputName << "frame" << setw(4) << setfill('0') << i << ".pgm";
        outputName << "annotated" << setw(4) << setfill('0') << i << ".pgm";

	Mat image = imread(inputName.str(), IMREAD_GRAYSCALE);
	
    	

    if (image.empty()) {
        cerr << "Could not open image" << endl;
        continue;
    }

    compute_com(image, 200);
    imwrite(outputName.str(), image);
	}
    return 0;
}
