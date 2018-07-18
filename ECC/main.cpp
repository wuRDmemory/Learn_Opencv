#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main() {

    Mat image1 = cv::imread("../images/aloeL.jpg", 1);
    Mat image2 = cv::imread("../images/aloeR.jpg", 1);

    Mat image1_resize, image2_resize;
    cv::resize(image1, image1_resize, cv::Size(160, 120));
    cv::resize(image2, image2_resize, cv::Size(160, 120));

    Mat image1_gray, image2_gray;
    cv::cvtColor(image1_resize, image1_gray, cv::COLOR_BGR2GRAY);
    cv::cvtColor(image2_resize, image2_gray, cv::COLOR_BGR2GRAY);

    const int WARP_MODE = cv::MOTION_HOMOGRAPHY;

    Mat warp_maxtrix;
    if (WARP_MODE == cv::MOTION_HOMOGRAPHY) {
        warp_maxtrix = Mat::eye(3, 3, CV_32F);
    } else {
        warp_maxtrix = Mat::eye(2, 3, CV_32F);
    }

    cv::TermCriteria criteria(cv::TermCriteria::COUNT | cv::TermCriteria::EPS, 1000, 1.0e-10);

    cv::findTransformECC(image1_gray, image2_gray, warp_maxtrix, WARP_MODE, criteria);

    Mat aligned;

    if (WARP_MODE == cv::MOTION_HOMOGRAPHY) {
        warpPerspective(image2_resize, aligned, warp_maxtrix, image1_resize.size(), cv::INTER_LINEAR | cv::WARP_INVERSE_MAP);
    }

    cv::imshow("img1", image1_resize);
    cv::imshow("img2", image2_resize);
    cv::imshow("img align", aligned);
    cv::waitKey(-1);

    return 0;
}