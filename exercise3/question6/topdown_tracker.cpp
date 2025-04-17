#include <opencv2/opencv.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace cv;
using namespace std;

int main() {

	for (int i = 0; i < 200; ++i) {
		stringstream inputName, outputName;
        	inputName << "frame" << setw(4) << setfill('0') << i << ".pgm";
        	outputName << "topdown" << setw(4) << setfill('0') << i << ".pgm";

		Mat gray = imread(inputName.str(), IMREAD_GRAYSCALE);

		if (gray.empty()) {
            		cerr << "Could not open " << inputName.str() << endl;
            		continue;
        	}

		Mat thresh;
		threshold(gray, thresh, 200, 255, THRESH_BINARY);

		Moments m = moments(thresh, true);
		if (m.m00 == 0) {
			imwrite(outputName.str(), gray);
			continue;
		}

		int x = static_cast<int>(m.m10 / m.m00);
        	int y = static_cast<int>(m.m01 / m.m00);

		int size = 10;
        	line(gray, Point(x - size, y), Point(x + size, y), Scalar(255), 1);
        	line(gray, Point(x, y - size), Point(x, y + size), Scalar(255), 1);

        	imwrite(outputName.str(), gray);

	}
	return 0;
}
