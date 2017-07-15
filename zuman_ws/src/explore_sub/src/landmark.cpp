#include "iostream"
#include "stdio.h"
#include "string"
#include <stdexcept>
#include <fstream>

#include "ros/ros.h"

#include "tesseract/baseapi.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"


#include "cv_bridge/cv_bridge.h"
#include "zuman_msgs/Instruction.h"
#include "image_transport/image_transport.h"

using namespace cv;
using namespace ros;
using namespace std;
using namespace cv_bridge;
using namespace sensor_msgs;



int thresh = 50, N = 5 , frameheight = 0,lmheight = 0;
double anglerot;

vector<string> lmname;
vector<Point> lmpos;
vector<int> lmnum;

Point lmdpos;
int lmdnum;
string landmarkText;

Mat frame;
bool tune = false, detect = false,sendcommand = false;
void imageCallback(const sensor_msgs::ImageConstPtr& msg);
void LandmarkHandler(const zuman_msgs::Instruction::ConstPtr& msg);










static double angle(Point pt1, Point pt2, Point pt0)
{
	double dx1 = pt1.x - pt0.x;
	double dy1 = pt1.y - pt0.y;
	double dx2 = pt2.x - pt0.x;
	double dy2 = pt2.y - pt0.y;
	return (dx1*dx2 + dy1*dy2) / sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

// returns sequence of squares detected on the image.
// the sequence is stored in the specified memory storage
static void findSquares(const Mat& image, vector<vector<Point> >& squares)
{
	squares.clear();

	//s    Mat pyr, timg, gray0(image.size(), CV_8U), gray;

	// down-scale and upscale the image to filter out the noise
	//pyrDown(image, pyr, Size(image.cols/2, image.rows/2));
	//pyrUp(pyr, timg, image.size());


	// blur will enhance edge detection
	Mat timg(image);
	cv::medianBlur(image, timg, 9);
	Mat gray0(timg.size(), CV_8U), gray;

	vector<vector<Point> > contours;

	// find squares in every color plane of the image
	for (int c = 0; c < 3; c++)
	{
		int ch[] = { c, 0 };
		mixChannels(&timg, 1, &gray0, 1, ch, 1);

		// try several threshold levels
		for (int l = 0; l < N; l++)
		{
			// hack: use Canny instead of zero threshold level.
			// Canny helps to catch squares with gradient shading
			if (l == 0)
			{
				// apply Canny. Take the upper threshold from slider
				// and set the lower to 0 (which forces edges merging)
				Canny(gray0, gray, 5, thresh, 5);
				// dilate canny output to remove potential
				// holes between edge segments
				dilate(gray, gray, Mat(), Point(-1, -1));
			}
			else
			{
				// apply threshold if l!=0:
				//     tgray(x,y) = gray(x,y) < (l+1)*255/N ? 255 : 0
				gray = gray0 >= (l + 1) * 255 / N;
			}

			// find contours and store them all as a list
			findContours(gray, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

			vector<Point> approx;

			// test each contour
			for (size_t i = 0; i < contours.size(); i++)
			{
				// approximate contour with accuracy proportional
				// to the contour perimeter
				approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

				// square contours should have 4 vertices after approximation
				// relatively large area (to filter out noisy contours)
				// and be convex.
				// Note: absolute value of an area is used because
				// area may be positive or negative - in accordance with the
				// contour orientation
				if (approx.size() == 4 &&
					fabs(contourArea(Mat(approx))) > 1000 &&
					isContourConvex(Mat(approx)))
				{
					double maxCosine = 0;

					for (int j = 2; j < 5; j++)
					{
						// find the maximum cosine of the angle between joint edges
						double cosine = fabs(angle(approx[j % 4], approx[j - 2], approx[j - 1]));
						maxCosine = MAX(maxCosine, cosine);
					}

					// if cosines of all angles are small
					// (all angles are ~90 degree) then write quandrange
					// vertices to resultant sequence
					if (maxCosine < 0.3)
						squares.push_back(approx);
				}
			}
		}
	}
}


Rect getMSquare(Mat& image, const vector<vector<Point> >& squares)
{
	int biggestInd = -1 , biggestArea = 0;
	for (size_t i = 0; i < squares.size(); i++)
	{
		

		int n = (int)squares[i].size();
		Mat meanclr;
		Rect r = boundingRect(squares[i]);
		cvtColor(image(r), meanclr, CV_BGR2GRAY);
		reduce(meanclr, meanclr, 0, CV_REDUCE_AVG);
		reduce(meanclr, meanclr, 1, CV_REDUCE_AVG);
		//dont detect the border or difinitely wrong rects
		bool wrong = false;
		for(int j = 0; j < (int)squares[i].size(); j++ )
		{
			if(squares[i][j].y>image.rows-4||squares[i][j].y<4)
			{
				wrong = true;
			}
		}
		if(r.width<image.cols*.9&&!wrong&&r.area()>biggestArea&&int(meanclr.at<uchar>(0, 0))>160)
		{
			//cout << int(meanclr.at<uchar>(0, 0)) << endl;
			biggestArea = r.area();
			biggestInd = i;
		//	rectangle(image, r, Scalar(0, 0, 255));
		//	polylines(image, &p, &n, 1, true, Scalar(0, 255, 0), 3, CV_AA);
		}
	}
	Rect rect;
	if (biggestInd >= 0)
		rect = boundingRect(squares[biggestInd]);
	else
		rect = Rect(0, 0, 0, 0);



		rectangle(image, rect, Scalar(0, 0, 255),10);
	////imshow(wndname, image);
	return rect;
}













string exec(const char* cmd) {
	char buffer[128];
	std::string result = "";
	FILE* pipe = popen(cmd, "r");
	if (!pipe) throw std::runtime_error("popen() failed!");
	try {
		while (!feof(pipe)) {
			if (fgets(buffer, 128, pipe) != NULL)
				result += buffer;
		}
	}
	catch (...) {
		pclose(pipe);
		throw;
	}
	pclose(pipe);
	return result;
}


class Landmark {

public:
	Landmark();
	// char * recognizeLandmark(Mat frame);
	void locateLandmark(Publisher publisher, zuman_msgs::Instruction instruction);
	void tuneWithLandmark(Publisher publisher, zuman_msgs::Instruction instruction);


private:
	tesseract::TessBaseAPI *tesseract;
	pair<int, Mat> detectLandmark(Mat frame);
	string recognizeLandmark();
};

int main(int argc, char* argv[]) {

	init(argc, argv, "landmark");
	cout << "start" << endl;


	landmarkText = "";


	ifstream myfile("/home/grad/lms.txt");



	string landmarkname;
	int lmx = 0, lmy = 0;
	string line;
	if (myfile.is_open())
	{
		int linetype = 0 % 4;
		while (getline(myfile, line))
		{
			if (linetype == 3)
			{
				lmnum.push_back(atoi(line.c_str()));
				lmname.push_back(landmarkname);
				lmpos.push_back(Point(lmx, lmy));
			}			
			if (linetype == 2)
			{
				lmy = atoi(line.c_str());
			}
			if (linetype == 1)
				lmx = atoi(line.c_str());
			if (linetype == 0)
			{
				landmarkname = line;
				for (int j = 0;j < landmarkname.size();j++)
				{
					if (landmarkname.at(j) == '\r' || landmarkname.at(j) == '\n')
						landmarkname.erase(landmarkname.begin() + j);
				}
			}
			linetype = (linetype + 1) % 4;
		}
		myfile.close();
	}

	else
	{
		cout << "Unable to open landmarks file";
		return 0;
	}


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
		camera >> frame;
		//imshow("Stream", frame);
		//	instruction.command = "detect";
		//	instruction.arg1 = 0;
		//	instruction.arg2 = 0;

		//	publisher.publish(instruction);

		if (detect)
		{
			cvtColor(frame, gray, CV_RGB2GRAY);

			reduce(gray, Maxi, 0, CV_REDUCE_MAX);
			reduce(gray, Maxi, 1, CV_REDUCE_MAX);

		//	frame = frame / int(Maxi.at<uchar>(0, 0)) * 255 * 1;



			landmark->locateLandmark(publisher, instruction);


		}
		if (tune)
		{
			tune = false;
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
		////imshow("Stream", frame);
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
	
	int resultant = 0 ;

	if (!frame.empty()) {
		//resize(frame,frame,Size(frame.cols * 4, frame.rows * 4));
		pair <int, Mat> resultpr = Landmark::detectLandmark(frame);
		resultant = resultpr.first;
		//resize(frame,frame,Size(frame.cols / 4, frame.rows / 4));
		//imshow("Stream", frame);
		frameheight = frame.rows;
		frame = resultpr.second;
		lmheight = frame.rows;
		
		// cout << "begin tes" << endl;
		if (resultpr.second.cols > 0)
		{
			//resize(frame,frame,Size(frame.cols / 4, frame.rows / 4));
			Mat Max, Min;
			cvtColor(frame, frame, CV_RGB2GRAY);
			reduce(frame, Max, 0, CV_REDUCE_MAX);
			reduce(frame, Max, 1, CV_REDUCE_MAX);
			reduce(frame, Min, 0, CV_REDUCE_MIN);
			reduce(frame, Min, 1, CV_REDUCE_MIN);
			int thres = (Max.at<uchar>(0, 0) + 2 * Min.at<uchar>(0, 0)) / 3;
			threshold(frame, frame, thres, 255, 0);
			//imshow("landmark", frame);
			if (landmarkText == "")
				landmarkText = Landmark::recognizeLandmark();
		}
	}
	else {
		printf("No captured frame -- Break!");
		//return
	}

	if (sendcommand) {
		sendcommand = false;
		if (resultant == 0) {
			cout << "nothing found";

			instruction.command = "rotate";
			instruction.arg1 = -26.5;        // Right
			instruction.arg2 = 0;

			publisher.publish(instruction);
		} else if (resultant % 4 == 1) {
			cout << "turn right by "<<anglerot<<" degrees";

			instruction.command = "rotate";
			instruction.arg1 = -anglerot;         // Right
			instruction.arg2 = 0;

			publisher.publish(instruction);
		 
		} else if (resultant % 4 == 2) {
			cout << "turn left by "<<anglerot<<" degrees";

			instruction.command = "rotate";
			instruction.arg1 = anglerot;         // left
			instruction.arg2 = 0;

			publisher.publish(instruction);
		} else if (resultant < 16 && resultant > 3) {
			cout << "move forwards by "<< frameheight/lmheight*8.5*4/3<< " cm";

			instruction.command = "move";
			instruction.arg1 = frameheight/lmheight*8.5*4/3;
			instruction.arg2 = 0;

			publisher.publish(instruction);
		} else if (resultant > 15 && resultant != 16) {
			cout << "stop moving forward";

			instruction.command = "move";
			instruction.arg1 = 0;
			instruction.arg2 = 0;

			publisher.publish(instruction);
		} else if (resultant == 16) {
			
			detect = false;
			if (landmarkText == "")
			{
				cout << "you are next to a landmark but I can't tell which one";

				instruction.command = "arrived";
				instruction.arg1 = -1;
				instruction.arg2 = 0;

				publisher.publish(instruction);

			}
			else
			{
				cout << "you are next to landmark : " << landmarkText<<endl;
				cout << " landmark num : "<< lmnum[lmdnum];

				instruction.command = "arrived";
				instruction.arg1 = lmnum[lmdnum];
				instruction.arg2 = 0;

				publisher.publish(instruction);

				landmarkText = "";
			}
		}

		cout << endl;
	}

}



void Landmark::tuneWithLandmark(Publisher publisher, zuman_msgs::Instruction instruction) {

	int resultant = 0;

	if (!frame.empty()) {
		//resize(frame,frame,Size(frame.cols / 2, frame.rows / 2));
		pair <int, Mat> resultpr = Landmark::detectLandmark(frame);
		resultant = resultpr.first;
		frameheight = frame.rows;
		//imshow("Stream", frame);
		lmheight = resultpr.second.rows;
	}
	// cout << "begin tes" << endl;


	if (true) {

		if (resultant % 4 == 1) {
			cout << "move right ";
			cout <<float(anglerot*22/7/180);
			instruction.command = "move";
			instruction.arg1 = -1*tan(float(anglerot*22/7/180))*frameheight/lmheight*8.5*8/3;         // Right
			instruction.arg2 = 0;

			publisher.publish(instruction);
		} else if (resultant % 4 == 2) {
			cout << "move left ";
			cout <<anglerot;

			instruction.command = "move";
			instruction.arg1 = tan(float(anglerot*22/7/180))*frameheight/lmheight*8.5*8/3;         // Right
			instruction.arg2 = 0;

			publisher.publish(instruction);
		} else if (resultant == 0) {
			cout << "I am lost";

			instruction.command = "tuned";
			instruction.arg1 = -1;
			instruction.arg2 = 0;

			publisher.publish(instruction);


		}else {
			cout << "you are tuned with the landmark ";

			instruction.command = "tuned";
			instruction.arg1 = 0;
			instruction.arg2 = 0;

			publisher.publish(instruction);


		}

		cout << endl;
	}

}



pair<int, Mat> Landmark::detectLandmark(Mat frame) {

	
	Mat frameproc = frame * 1;

	vector<vector<Point> > squares;
	findSquares(frameproc, squares);
	Rect roi_b = getMSquare(frameproc, squares);

	rectangle(frame, roi_b, Scalar(0, 255, 0), 2, 8, 0);

	
	
	//roi_b.x += roi_b.width / 4;
	//roi_b.y += roi_b.height / 4;
	//roi_b.width = roi_b.width / 2;
	//roi_b.height = roi_b.height / 2;
	// Set Region of Interest
	
	int results = 0;

	if (roi_b.width > 0) 
	{
		anglerot = abs(roi_b.x+(roi_b.width/2)-(frame.cols/2))*26.5/frame.cols;
		if (((2 * roi_b.x) + (roi_b.width) - (frame.size().width / 6)) >= (frame.size().width)) {
			results += 1;
		} if (((2 * roi_b.x) + (roi_b.width) + (frame.size().width / 6)) < (frame.size().width)) {
			results += 2;
		} if ((roi_b.width * 1.4) < (frame.size().width)) {
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
	resultpair.second = frame(roi_b);
	imwrite("/home/grad/lm.pbm", resultpair.second);
	return resultpair;
}

string Landmark::recognizeLandmark() {

	char * output;

	//cout << "setImage begin" << endl;
	tesseract->SetImage((uchar*)frame.data, frame.size().width, frame.size().height, frame.channels(), frame.step1());
	cout << "setImage" << endl;
	tesseract->Recognize(0);
	cout << "recognize" << endl;

	output = tesseract->GetUTF8Text();

	string output2 = exec("ocrad /home/grad/lm.pbm").c_str();

	string output_total = "";
	if (strlen(output)>0)
	{
		output_total = output_total + string(output);
	}

	output_total = output_total + "        " + output2;
	string outText = "";
	for (int i = 0; i<lmpos.size();i++)
	{
		if (output_total.find(lmname[i]) != std::string::npos)
		{
			outText = lmname[i];
			lmdnum = i;
			lmdpos = lmpos[i];
		}
	}

	ROS_INFO("%s", outText.c_str());
	return outText;
}





void LandmarkHandler(const zuman_msgs::Instruction::ConstPtr& msg)
{

	if (msg->command == "detect")
	{
		detect = true;
		sendcommand = true;
	}
	if (msg->command == "cancel_detect")
	{
		detect = false;
		sendcommand = false;
	}
	if (msg->command == "tune")
		tune = true;
}
