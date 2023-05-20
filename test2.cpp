#include <opencv2/opencv.hpp>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc.hpp>  
#include<iostream>  
using namespace std;
using namespace cv;
int main()
{
	VideoCapture capture;
	capture.open("Aim.mp4");
	int frames = capture.get(CAP_PROP_FRAME_COUNT);
	double fps = capture.get(CAP_PROP_FPS);
	Size size = Size(capture.get(CAP_PROP_FRAME_WIDTH), capture.get(CAP_PROP_FRAME_HEIGHT));
	Mat frame;
	namedWindow("videotest", WINDOW_NORMAL);
	namedWindow("test", WINDOW_NORMAL);
	namedWindow("result", WINDOW_NORMAL);
	for (;;)
	{
		capture >> frame;
		if (frame.empty())
		{
			break;
		}
		imshow("videotest", frame);
		Mat grayimg;
		frame.convertTo(frame, -1,1,-100);
		cvtColor(frame,grayimg , COLOR_BGR2GRAY);
		GaussianBlur(grayimg, grayimg, Size(5,5),0);
		threshold(grayimg, grayimg, 0, 255, THRESH_BINARY | THRESH_OTSU);
		Canny(grayimg, grayimg,255, 100, 3);
		
	
		vector<vector<Point>> contours;
		findContours(grayimg, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
		drawContours(frame, contours, -1, Scalar(0,105,150), 5);
		imshow("test", frame);
		imshow("reult",grayimg);
		waitKey(90);
	}
	capture.release();
}