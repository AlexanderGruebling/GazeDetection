#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "opencv2/objdetect.hpp"

using namespace cv;
using namespace std;

int main()
{
	Mat image = imread("image.jpg");
	Mat frame_gray;
	resize(image, image, Size(), 0.5, 0.5);
	cvtColor(image, frame_gray, COLOR_BGR2GRAY);

	CascadeClassifier eye_cascade;
	std::vector<Rect> eyes;
	try {
		eye_cascade.load("haarcascade_eye.xml");
		eye_cascade.detectMultiScale(frame_gray, eyes);
	}
	catch (cv::Exception & e) {
		cerr << e.msg << endl;
	}

	for (size_t i = 0; i < eyes.size(); i++)
	{
		Point center(eyes[i].x + eyes[i].width / 2, eyes[i].y + eyes[i].height / 2);
		ellipse(image, center, Size(eyes[i].width / 2, eyes[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4);
		Mat faceROI = frame_gray(eyes[i]);
	}

	imshow("Display Window", image);
	waitKey(0);
	return 0;
}