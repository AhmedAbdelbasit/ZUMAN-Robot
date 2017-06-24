#include "iostream"
#include "stdio.h"

#include "ros/ros.h"

#include "tesseract/baseapi.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include "cv_bridge/cv_bridge.h"
#include "image_transport/image_transport.h"

using namespace cv;
using namespace ros;
using namespace std;
using namespace cv_bridge;
using namespace sensor_msgs;

Mat frame;

void imageCallback(const sensor_msgs::ImageConstPtr& msg);

class Landmark {

public:
    Landmark();
    void recognizeLandmark(Mat frame);
    void locateLandmark();

private:
    tesseract::TessBaseAPI *tesseract;
    pair<int, Mat> detectLandmark(Mat frame);
};

void imageCallback(const sensor_msgs::ImageConstPtr& msg) {
    try {
        frame = toCvShare(msg, "bgr8")->image;
		imshow("Stream", frame);
		waitKey(30);
	} catch (cv_bridge::Exception& e) {
		ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
	}
}

Landmark::Landmark() {
    // OCR
    tesseract = new tesseract::TessBaseAPI();

    if (tesseract->Init(NULL, "eng")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    } else {
		ROS_INFO("%s", "OCR Success");
	}
}

void Landmark::locateLandmark() {

    int resultant = 0;

    while (1) {
        if (!frame.empty()) {
            pair <int, Mat> resultpr = Landmark::detectLandmark(frame);
            resultant = resultpr.first;
        } else {
            printf("No captured frame -- Break!");
            break;
        }

        if (resultant == 0) {
            cout << "nothing found";
        } if (resultant % 4 == 1) {
            cout << "turn right and ";
            //code to turn right
        } if (resultant % 4 == 2) {
            cout << "turn left and ";
            //code to turn left
        } if (resultant<16 && resultant>3) {
            cout << "move forwards";
            //code to move forwards
        } if (resultant>15) {
            cout << "stop moving forward";
            //code to stop moving forwards
        } if (resultant == 16) {
            cout << " , you have reached your destination";
            //code to do after the destination is reached;
        }
    }
}

pair<int, Mat> Landmark::detectLandmark(Mat frame) {

    int results = 0;
	Mat gray;

	Size size(frame.size().width, frame.size().height);
	resize(frame, frame, size);
	cvtColor(frame, gray, COLOR_BGR2GRAY);
	equalizeHist(gray, gray);
	blur(gray, gray, Size(15, 15));

	// Detect plates
	vector<Vec3f> circles;

	// Apply the Hough Transform to find the circles
	HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
		2, // change this value to detect circles with different distances to each other
		100, 30, 15, min(frame.size().height, frame.size().width) // change the last two parameters
					   // (min_radius & max_radius) to detect larger circles
	);

	Rect roi_b;

	size_t x = 4;
	for (int i = 1; i < circles.size(); i++) {
		Point ctr(circles[i][0], circles[i][1]);
		if (abs(circles[i][0] - circles[i - 1][0]) < abs(circles[i][2] - circles[i - 1][2])) {
			if (abs(circles[i][1] - circles[i - 1][1]) < abs(circles[i][2] - circles[i - 1][2])&& circles[i][2]>roi_b.width/2) {
				roi_b.x = circles[i][0] - circles[i][2];
				roi_b.y = circles[i][1] - circles[i][2];
				roi_b.width = circles[i][2] * 2;
				roi_b.height = circles[i][2] * 2;
			}
		}
	}

	// Set Region of Interest
	rectangle(frame, roi_b, Scalar(0, 255, 0), 2, 8, 0);

	results = 0;

	if (roi_b.width > 0) {
		if (((2 * roi_b.x) + (roi_b.width) - (frame.size().width / 6)) >= (frame.size().width)) {
			results += 1;
		} if (((2 * roi_b.x) + (roi_b.width) + (frame.size().width / 6)) < (frame.size().width)) {
			results += 2;
		} if ((roi_b.width * 2) < (frame.size().width))	{
			results += 4;
		} else {
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

void Landmark::recognizeLandmark(Mat frame) {

    char* outText;

    tesseract->SetImage((uchar*)frame.data, frame.size().width, frame.size().height, frame.channels(), frame.step1());
	tesseract->Recognize(0);

	outText = tesseract->GetUTF8Text();

	ROS_INFO("%s", outText);
}
