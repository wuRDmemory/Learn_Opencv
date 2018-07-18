#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

vector<cv::Point> dst_points;

static void onMouse( int event, int x, int y, int flag, void* userdata)
{
    if( event != EVENT_LBUTTONDOWN )
        return;

    dst_points.emplace_back(Point(x, y));

    Mat src = static_cast<Mat*>(userdata)->clone();
    printf(">>> (%d %d) \n", src.size().width, src.size().height);
    cv::circle(src, Point(x, y), 4, Scalar(0, 255, 100), 2);

    cv::imshow("mouse", src);
}

int main() {
    Mat img1 = cv::imread("/home/ubuntu/Datum/datum/Learn_Opencv/homography_first_image.jpg");
    Mat img2 = cv::imread("/home/ubuntu/Datum/datum/Learn_Opencv/homography_second_image.jpg");

    cv::imshow("img2", img2);
    cv::setMouseCallback("img2", onMouse, &img2);

    while (dst_points.size() < 4) {
        cv::waitKey(100);
        // cv::imshow("img2", img2);
    }

    cv::Size src_size = img1.size();
    int h = src_size.height, w = src_size.width;

    vector<Point> src_points;
    src_points.emplace_back(Point(0, 0));
    src_points.emplace_back(Point(w, 0));
    src_points.emplace_back(Point(w, h));
    src_points.emplace_back(Point(0, h));

    Mat homography = cv::findHomography(src_points, dst_points);
    Mat img3 = Mat::zeros(img2.size(), img2.type());
    cv::warpPerspective(img1, img3, homography, img3.size());

    img3.copyTo(img2, img3);

    cv::imshow("merge", img2);
    cv::waitKey(-1);

    return 0;
}