#include "iostream"
#include "stdio.h"
#include "string"

#include "ros/ros.h"

#include "tesseract/baseapi.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include "cv_bridge/cv_bridge.h"
#include "zuman_msgs/Instruction.h"
#include "image_transport/image_transport.h"

using namespace cv;
using namespace ros;
using namespace std;
using namespace cv_bridge;
using namespace sensor_msgs;

Mat frame;
bool tune, detect;
void imageCallback(const sensor_msgs::ImageConstPtr& msg);
void LandmarkHandler(const zuman_msgs::Instruction::ConstPtr& msg);


class Landmark {

public:
	Landmark();
	// char * recognizeLandmark(Mat frame);
	void locateLandmark(Publisher publisher, zuman_msgs::Instruction instruction);
	void tuneWithLandmark(Publisher publisher, zuman_msgs::Instruction instruction);

private:
	tesseract::TessBaseAPI *tesseract;
	pair<int, Mat> detectLandmark(Mat frame);
	char * recognizeLandmark();
};

int main(int argc, char* argv[]) {

	init(argc, argv, "landmark");
	cout << "start" << endl;
	NodeHandle nh;
	Landmark* landmark = new Landmark();
	VideoCapture camera(0);
	if (camera.isOpened()) {
		// cout >> "Success..Camera" >> endl;
		camera.set(CAP_PROP_FPS, 1);
		//namedWindow("Stream", WINDOW_AUTOSIZE);
	}
	else {
		// cout >> "Failed...Camera" >> endl;
		return 1;
	}
	Mat Maxi;
	Mat gray;

	Publisher publisher = nh.advertise<zuman_msgs::Instruction>("hw_landmark", 10);
	zuman_msgs::Instruction instruction;
	ros::Subscriber sub = nh.subscribe("hw_landmark", 10, LandmarkHandler);

	
	
	
	// image_transport::ImageTransport it(nh);
	// image_transport::Subscriber subscriber = it.subscribe("camera/image", 1, imageCallback);

	while (waitKey(10) != 'c')
	{
		//	instruction.command = "detect";
		//	instruction.arg1 = 0;
		//	instruction.arg2 = 0;

		//	publisher.publish(instruction);
	
		if (detect)
		{
			detect = false;
			camera >> frame;
			cvtColor(frame, gray, CV_RGB2GRAY);

			reduce(gray, Maxi, 0, CV_REDUCE_MAX);
			reduce(gray, Maxi, 1, CV_REDUCE_MAX);

			frame = frame / int(Maxi.at<uchar>(0, 0)) * 255 * 1;



			landmark->locateLandmark(publisher, instruction);


		}
		if (tune)
		{
			tune = false;
			camera >> frame;
			cvtColor(frame, gray, CV_RGB2GRAY);

			reduce(gray, Maxi, 0, CV_REDUCE_MAX);
			reduce(gray, Maxi, 1, CV_REDUCE_MAX);

			frame = frame / int(Maxi.at<uchar>(0, 0)) * 255 * 1;

		

			landmark->tuneWithLandmark(publisher, instruction);


		}
		spinOnce();
	}
	return 0;
}

void imageCallback(const sensor_msgs::ImageConstPtr& msg) {
	try {
		frame = toCvShare(msg, "bgr8")->image;
		//imshow("Stream", frame);
		// waitKey(30);
	}
	catch (cv_bridge::Exception& e) {
		ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
	}
}

Landmark::Landmark() {
	// OCR
	tesseract = new tesseract::TessBaseAPI();

	if (tesseract->Init(NULL, "eng")) {
		fprintf(stderr, "Could not initialize tesseract.\n");
		exit(1);
	}
	else {
		ROS_INFO("%s", "OCR Success");
	}
	tesseract->SetVariable("tessedit_char_whitelist", "0123456789");
}

void Landmark::locateLandmark(Publisher publisher, zuman_msgs::Instruction instruction) {

	int resultant = 0;
	char * landmarkText;

	if (!frame.empty()) {
		resize(frame,frame,Size(frame.cols / 2, frame.rows / 2));
		pair <int, Mat> resultpr = Landmark::detectLandmark(frame);
		resultant = resultpr.first;
		imshow("Stream", frame);
		frame = resultpr.second;

		// cout << "begin tes" << endl;
		if (!resultpr.second.empty())
		{
			Mat Max, Min;
			cvtColor(frame, frame, CV_RGB2GRAY);
			reduce(frame, Max, 0, CV_REDUCE_MAX);
			reduce(frame, Max, 1, CV_REDUCE_MAX);
			reduce(frame, Min, 0, CV_REDUCE_MIN);
			reduce(frame, Min, 1, CV_REDUCE_MIN);
			int thres = (Max.at<uchar>(0, 0) + 2 * Min.at<uchar>(0, 0)) / 3;
			threshold(frame, frame, thres, 255, 0);
			imshow("landmark", frame);
			landmarkText = Landmark::recognizeLandmark();
		}
	}
	else {
		printf("No captured frame -- Break!");
		//return
	}

	if (true) {

		if (resultant % 4 == 1) {
			cout << "turn right and ";

			instruction.command = "rotate";
			instruction.arg1 = -10;         // Right
			instruction.arg2 = 0;

			publisher.publish(instruction);
		}		if (resultant == 0) {
			cout << "nothing found";

			instruction.command = "rotate";
			instruction.arg1 = -30;         // Right
			instruction.arg2 = 0;

			publisher.publish(instruction);
		} if (resultant % 4 == 2) {
			cout << "turn left and ";

			instruction.command = "rotate";
			instruction.arg1 = 10;         // left
			instruction.arg2 = 0;

			publisher.publish(instruction);
		} if (resultant < 16 && resultant > 3) {
			cout << "move forwards";

			instruction.command = "move";
			instruction.arg1 = 30;
			instruction.arg2 = 0;

			publisher.publish(instruction);
		} if (resultant > 15) {
			cout << "stop moving forward";

			instruction.command = "move";
			instruction.arg1 = 0;
			instruction.arg2 = 0;

			publisher.publish(instruction);
		} if (resultant == 16) {
			cout << " , you have reached your destination , you are next to landmark " << landmarkText;
			instruction.command = "rotate";
			instruction.arg1 = 90;
			instruction.arg2 = 0;

			publisher.publish(instruction);
			
			instruction.command = "again";
			instruction.arg1 = 0;
			instruction.arg2 = 0;

			publisher.publish(instruction);
			
			
		}
		else{
			instruction.command = "again";
			instruction.arg1 = 1;
			instruction.arg2 = 0;

			publisher.publish(instruction);
		}
		cout<<endl;
	}

}



void Landmark::tuneWithLandmark(Publisher publisher, zuman_msgs::Instruction instruction) {

	int resultant = 0;
	char * landmarkText;

	if (!frame.empty()) {
		resize(frame,frame,Size(frame.cols / 2, frame.rows / 2));
		pair <int, Mat> resultpr = Landmark::detectLandmark(frame);
		resultant = resultpr.first;
		imshow("Stream", frame);
	}
	// cout << "begin tes" << endl;


	if (true) {

		if (resultant % 4 == 1) {
			cout << "move right ";

			instruction.command = "move";
			instruction.arg1 = -10;         // Right
			instruction.arg2 = 0; 

				publisher.publish(instruction);
		} if (resultant % 4 == 2) {
			cout << "move left ";

			instruction.command = "move";
			instruction.arg1 = 10;         // Right
			instruction.arg2 = 0;

			publisher.publish(instruction);
		} if (resultant == 16) {
			cout << " , you are by the landmark ";
			
			instruction.command = "again";
			instruction.arg1 = 0;
			instruction.arg2 = 0;

			publisher.publish(instruction);
			
			
		}
		else{
			instruction.command = "again";
			instruction.arg1 = 1;
			instruction.arg2 = 0;

			publisher.publish(instruction);
		}
		cout << endl;
	}

}



pair<int, Mat> Landmark::detectLandmark(Mat frame) {

	int results = 0;
	Mat gray;

	Size size(frame.size().width, frame.size().height);
	resize(frame, frame, size);
	cvtColor(frame, gray, COLOR_BGR2GRAY);
	//equalizeHist(gray, gray);
	blur(gray, gray, Size(15, 15));

	// Detect plates
	vector<Vec3f> circles;

	//imshow("Streamblur", gray);
	// Apply the Hough Transform to find the circles
	HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
		2, // change this value to detect circles with different distances to each other
		100, 30, 15, 0 // change the last two parameters
					   // (min_radius & max_radius) to detect larger circles
	);

	Rect roi_b;

	size_t x = 4;
	for (int i = 1; i < circles.size(); i++) {
		Point ctr(circles[i][0], circles[i][1]);
		if (abs(circles[i][0] - circles[i - 1][0]) < abs(circles[i][2] - circles[i - 1][2])) {
			if (abs(circles[i][1] - circles[i - 1][1]) < abs(circles[i][2] - circles[i - 1][2]) && circles[i][2]>roi_b.width / 2) {
				roi_b.x = circles[i][0] - circles[i][2];
				roi_b.y = circles[i][1] - circles[i][2];
				roi_b.width = circles[i][2] * 2;
				roi_b.height = circles[i][2] * 2;
			}
		}
	}
	roi_b.x += roi_b.width / 4;
	roi_b.y += roi_b.height / 4;
	roi_b.width = roi_b.width / 2;
	roi_b.height = roi_b.height / 2;
	// Set Region of Interest
	rectangle(frame, roi_b, Scalar(0, 255, 0), 2, 8, 0);

	results = 0;

	if (roi_b.width > 0) {
		if (((2 * roi_b.x) + (roi_b.width) - (frame.size().width / 6)) >= (frame.size().width)) {
			results += 1;
		} if (((2 * roi_b.x) + (roi_b.width) + (frame.size().width / 6)) < (frame.size().width)) {
			results += 2;
		} if ((roi_b.width * 3.5) < (frame.size().width)) {
			results += 4;
		}
		else {
			results += 16;
		}
	}

	Size size2(frame.size().width, frame.size().height);
	resize(frame, frame, size2);
	pair <int, Mat> resultpair;
	resultpair.first = results;
	resultpair.second = frame(roi_b & Rect(0, 0, frame.cols, frame.rows));

	return resultpair;
}

char * Landmark::recognizeLandmark() {

	char * outText;

	cout << "setImage begin" << endl;
	tesseract->SetImage((uchar*)frame.data, frame.size().width, frame.size().height, frame.channels(), frame.step1());
	cout << "setImage" << endl;
	tesseract->Recognize(0);
	cout << "recognize" << endl;

	outText = tesseract->GetUTF8Text();

	ROS_INFO("%s", outText);
	return outText;
}





void LandmarkHandler(const zuman_msgs::Instruction::ConstPtr& msg)
{

	if (msg->command == "detect")
		detect = true;

	if (msg->command == "tune")
		tune = true;
}

