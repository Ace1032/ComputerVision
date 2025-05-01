#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>
#include <filesystem>
#include <iostream>

using namespace std;
using namespace cv;
using namespace cv::ml;
namespace fs = std::filesystem;

vector<Mat> loadImages(const string& folder) {
    vector<Mat> images;
    for (const auto& entry : fs::directory_iterator(folder)) {
        Mat img = imread(entry.path().string(), IMREAD_GRAYSCALE);
        if (!img.empty()) {
            resize(img, img, Size(64, 64));
            images.push_back(img);
        }
    }
    return images;


}

void computeHOGs(const vector<Mat>& images, vector<Mat>& gradient_lst, HOGDescriptor& hog) {
    for (const auto& img : images) {
        vector<float> descriptors;
        hog.compute(img, descriptors);
        gradient_lst.push_back(Mat(descriptors).clone().reshape(1,1));
    		}
}





int main() {
    HOGDescriptor hog(Size(64, 64), Size(16,16), Size(8,8), Size(8,8), 9);

    vector<Mat> posImgs = loadImages("data/positive");
    vector<Mat> negImgs = loadImages("data/negative");

    vector<Mat> features;
    computeHOGs(posImgs, features, hog);
    Mat posLabels = Mat::ones(posImgs.size(), 1, CV_32S);

    vector<Mat> negFeatures;
    computeHOGs(negImgs, negFeatures, hog);
    Mat negLabels = Mat::zeros(negImgs.size(), 1, CV_32S);

    features.insert(features.end(), negFeatures.begin(), negFeatures.end());
    Mat labels;
    vconcat(posLabels, negLabels, labels);

    Mat trainingData;
    vconcat(features, trainingData);

    Ptr<SVM> svm = SVM::create();
    svm->setKernel(SVM::LINEAR);
    svm->setType(SVM::C_SVC);
    svm->setC(0.01);
    svm->train(trainingData, ROW_SAMPLE, labels);
    svm->save("stop_sign_svm.yml");

    cout << "SVM trained and saved as stop_sign_svm.yml" << endl;
    return 0;
}
