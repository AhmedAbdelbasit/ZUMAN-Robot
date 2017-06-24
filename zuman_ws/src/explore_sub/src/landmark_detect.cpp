#include "ros/ros.h"

#include "tesseract/baseapi.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include "cv_bridge/cv_bridge.h"
#include "image_transport/image_transport.h"

#include "landmark.cpp"

using namespace ros;

int main(int argc, char* argv[]) {

    init(argc, argv, "landmark_detect");

    NodeHandle nh;

    namedWindow("Stream");
    startWindowThread();

    image_transport::ImageTransport it(nh);
    image_transport::Subscriber subscriber = it.subscribe("camera/image", 1, imageCallback);

    Landmark* landmark = new Landmark();

    spin();

    return 0;
}
