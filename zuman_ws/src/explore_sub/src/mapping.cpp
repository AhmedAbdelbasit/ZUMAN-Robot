#include "iostream"
#include "stdio.h"
#include "string"
#include <fstream>

#include "ros/ros.h"

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



void MappingHandler(const zuman_msgs::Instruction::ConstPtr& msg);



Point oriento(0,0);

class AstarNode
{
public:
	double cost = 0;
	double heur = 0;
	Point position = Point(0, 0);
	Point parent = Point(0, 0);
	void operator=(AstarNode other)
	{
		cost = other.cost;
		heur = other.heur;
		position.x = other.position.x;
		position.y = other.position.y;
		parent.x = other.parent.x;
		parent.y = other.parent.y;
	}

};
bool operator==(AstarNode thisone, AstarNode other)
{
	return (thisone.position.x == other.position.x&&thisone.position.y == other.position.y);
}
bool operator!=(AstarNode thisone, AstarNode other)
{
	return (thisone.position.x != other.position.x || thisone.position.y != other.position.y);
}

string mapaddress = "C:\\hu\\map.bmp";

bool nextstep = false, mapway = false, firststep = true, remapobs = false, nextismapway = false, nextisrotcam = false, nextistune = false, firstmap = false, landmark = false, located = false;

bool destinationreached = false, destinationtobereached = false, destinationtobetuned = false;

int arg1 = 0, arg2 = 0, angleofcamabs = 0;


vector<Point> MapTheWay(Mat map, Point startpoint, Point goalpoint,bool reversed =false)
{
	oriento = Point(0,0);
	bool sub = false;
	bool strict = true;
	if (map.size == 0)
		return vector<Point>();

	if (startpoint == Point(0, 0))
		return vector<Point>();

	if (goalpoint == Point(0, 0))
		return vector<Point>();
	Mat map2 = map * 1;
	cvtColor(map, map, CV_BGR2GRAY);
	Mat route = map * 0;
	bool possible = false;
	for (int x = -1;x <= 1;x++)
		for (int y = -1;y <= 1;y++)
		{
			if (x != 0 || y != 0)
			{
				if (!(startpoint.x + x < 0 || startpoint.y + y < 0 || startpoint.x + x >= map.cols || startpoint.y + y >= map.rows))
				{
					if (!(startpoint.x < 0 || startpoint.y < 0 || startpoint.x >= map.cols || startpoint.y >= map.rows))
					{
						if (abs(x) + abs(y) <= 1 || sub)
							if (map.at<uchar>(startpoint.y + y, startpoint.x + x)>8)
								possible = true;
					}
				}
			}
		}
	if (!possible)
	{
		cout << "all ways blocked" << endl;
		return vector<Point>();
	}
	Point start = startpoint, goal = goalpoint;
	vector<AstarNode> frontier, explored;
	AstarNode next, now;
	now.position.x = goal.x;
	now.position.y = goal.y;
	now.parent.x = goal.x;
	now.parent.y = goal.y;
	now.cost = 0;
	now.heur = sqrt((goal.x - start.x)*(goal.x - start.x) + (goal.y - start.y)*(goal.y - start.y));
	frontier.push_back(now);
	if (reversed)
	{
		start -= oriento;
	}
	while (now.position.x != start.x || now.position.y != start.y)
	{
		//cout << "frontier count : " << frontier.size()<<endl;
		//cout << "explored count : " << explored.size()<<endl;
		//waitKey(1);
		//////cout << "(" << now.position.x << " , " << now.position.y << ")" << endl;
		//////cout << "heur =  " << now.heur;
		for (int i = 0; i <1;i++)
		{
			if (find(explored.begin(), explored.end(), now) == explored.end())
				explored.push_back(now);
			for (int x = -1;x <= 1;x++)
			{
				for (int y = -1;y <= 1;y++)
				{
					if (abs(x) + abs(y) > 1)
					{
						if (sub)
						{
							next.cost = now.cost + sqrt(2);
						}
						else
						{
							next.cost = now.cost + map.cols*map.rows;
						}
					}
					else
					{
						next.cost = now.cost + 1;
					}
					if (now.position.x + x < 0 || now.position.y + y < 0 || now.position.x + x >= map.cols || now.position.y + y >= map.rows)
					{

						next.cost += map.cols*map.rows;
					}
					else if (map.at<uchar>(Point(now.position.x + x, now.position.y + y)) < 8)
					{

						next.cost += map.cols*map.rows;
					}
					if (next.cost < map.cols*map.rows)
					{
						if ((map.at<uchar>(next.position) != 127)||!strict)
							next.cost = 0;
						next.heur = sqrt((now.position.x + x - start.x)*(now.position.x + x - start.x) + (now.position.y + y - start.y)*(now.position.y + y - start.y));
						next.position.x = now.position.x + x;
						next.position.y = now.position.y + y;
						next.parent.x = now.position.x;
						next.parent.y = now.position.y;
						//////cout << "ho";
						if (find(frontier.begin(), frontier.end(), next) == frontier.end() && std::find(explored.begin(), explored.end(), next) == explored.end())
						{
							//cout << "hi";
							frontier.push_back(next);
							circle(map2, next.position, 0, Scalar(255, 0, 0));
						}


					}
				}
			}
		}
		//cout << endl;
		////cout << frontier.size()<<endl;
		AstarNode candidate;
		candidate.heur = abs(map.cols*map.rows * 10000000);
		candidate.cost = abs(map.cols*map.rows * 10000000);
		int candnum = 0;
		for (int i = 0; i < frontier.size();i++)
		{
			////cout << "hello";
			if (find(explored.begin(), explored.end(), frontier[i]) == explored.end() && (candidate.heur + candidate.cost) >= (frontier[i].cost + frontier[i].heur))
			{
				//cout << "now1_";
				candidate = frontier[i];
				candnum = i;
			}
			//	else if (find(explored.begin(), explored.end(), frontier[i]) != explored.end() && (candidate.heur + candidate.cost) >= (frontier[i].cost + frontier[i].heur))
			//	{
			//		//cout << "now2_";
			//		int numm = find(explored.begin(), explored.end(), frontier[i]) - explored.begin();
			//		if ((explored[numm].heur + explored[numm].cost) >= (frontier[i].cost) + frontier[i].heur)
			//		{
			//			explored[numm] = frontier[i];
			//			candidate = frontier[i];
			//			candnum = i;
			//		}
			//	}


		}			bool check1 = (now != candidate);
		now = candidate;
		if (check1)
		{
			//cout << "_hi";
			circle(map2, candidate.position, 0, Scalar(0, 0, 0));
			circle(map2, goal, 3, Scalar(0, 0, 0));
			circle(map2, start, 3, Scalar(0, 0, 0));
			////cout << "hello";
			explored.push_back(candidate);
			frontier.erase(frontier.begin() + candnum);
		}
		else
		{
			Mat MAP;
			resize(map2, MAP, Size(724, 300));
			//imshow("map", MAP);
			cout << "no path found";
			return vector<Point>();

		}
		Mat MAP;
		resize(map2, MAP, Size(724, 300));
		//imshow("map", MAP);
	}
	circle(map2, now.position, 0, Scalar(128, 128, 128));
	Mat MAP;
	resize(map2, MAP, Size(724, 300));
	//imshow("map", MAP);
	vector<Point> output;
	if(reversed&&oriento!=Point(0,0))
		output.push_back(start+oriento);
	output.push_back(now.position);
	circle(map2, now.position, 0, Scalar(0, 255, 255));
	while (now.position.x != goal.x || now.position.y != goal.y)
	{
		AstarNode parenter;
		parenter.position.x = now.parent.x;
		parenter.position.y = now.parent.y;
		if (find(explored.begin(), explored.end(), parenter) != explored.end())
		{
			now = explored[find(explored.begin(), explored.end(), parenter) - explored.begin()];
			output.push_back(now.position);
			circle(map2, now.position, 0, Scalar(0, 255, 255));
			Mat MAP;
			resize(map2, MAP, Size(724, 300));
			//imshow("map", MAP);
		}
	}
	if (reversed)
	{
		reverse(output.begin(), output.end());
	}

	return output;
}


int next_step(vector<Point> &way)
{
	if (way.size()>0)
	{
		Point now, next;
		now = way[0];
		if (way.size() > 1)
			 next = way[1];
		else
			next = way[0];
		int result = 8;
		if (next.y < now.y&&next.x == now.x)
			result = 0;
		if (next.y < now.y&&next.x < now.x)
			result = 1;
		if (next.y == now.y&&next.x < now.x)
			result = 2;
		if (next.y > now.y&&next.x < now.x)
			result = 3;
		if (next.y > now.y&&next.x == now.x)
			result = 4;
		if (next.y > now.y&&next.x > now.x)
			result = 5;
		if (next.y == now.y&&next.x > now.x)
			result = 6;
		if (next.y < now.y&&next.x > now.x)
			result = 7;
		Mat map = imread(mapaddress), map2;
		if (map.size == 0)
			return 8;
		cvtColor(map, map2, CV_BGR2GRAY);

		if (((map2.at<uchar>(now) == 195 || map2.at<uchar>(now) == 200) && (map2.at<uchar>(next) != 195 && map2.at<uchar>(next) != 200) && !landmark)||destinationtobereached)
		{
			landmark = true;

			Point lm[4] = { now ,now ,now ,now };
			bool lmb[4] = { false ,false ,false ,false };
			bool found = false;
			if (map2.at<uchar>(now) == 200)
			{
				found = true;
				//landmark = false;
			}
			while (!found)
			{
				if (lmb[0] == false)
				{
					lm[0].y--;
					if (map2.at<uchar>(lm[0]) < 8)
						lmb[0] = true;

				}
				if (lmb[1] == false)
				{
					lm[1].x--;
					if (map2.at<uchar>(lm[1]) < 8)
						lmb[1] = true;

				}
				if (lmb[2] == false)
				{
					lm[2].y++;
					if (map2.at<uchar>(lm[2]) < 8)
						lmb[2] = true;

				}
				if (lmb[3] == false)
				{
					lm[3].x++;
					if (map2.at<uchar>(lm[3]) < 8)
						lmb[3] = true;

				}

				for (int i = 0;i < 4;i++)
				{
					if (map2.at<uchar>(lm[i]) == 200)
					{
						found = true;
						angleofcamabs = i * 90;
					}
				}
				if (lmb[0] && lmb[1] && lmb[2] && lmb[3])
					return 8;

			}


		}
		else
		{
			landmark = false;
		}
		//cout << int(map.at<uchar>(next)) << endl;
		circle(map, way[way.size() - 1], 0, Scalar(0, 255, 0));
		circle(map, next, 0, Scalar(0, 0, 255));

		Mat MAP = map * 1;
		resize(MAP, MAP, Size(724, 300));
		//imshow("map", MAP);
		if (!landmark && !firststep&&way.size()>1)
			way.erase(way.begin());
		return result;
	}

	return 8;
}





vector<string> lmname;
vector<Point> lmpos;
vector<int> lmnum;


int main(int argc, char* argv[])
{
	init(argc, argv, "mapping");
	cout << "start" << endl;
	NodeHandle nh;




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







	bool straightline = true;
	int straightlength = 0, testlength = 0;
	Point start, goal;
	int angleofrotation = 0;
	int angleof1strot = 0;
	int angleofrobot = 0, lastanglerobot = 0;
	vector<Point> way, currentline;

	Publisher publisher = nh.advertise<zuman_msgs::Instruction>("hw_map", 10);
	zuman_msgs::Instruction instruction;

	ros::Subscriber sub = nh.subscribe("hw_map", 10, MappingHandler);


	Mat map = imread(mapaddress);

	while (1)
	{
		if (remapobs/*obstacle*/)
		{
			remapobs = false;
			angleofrobot = lastanglerobot;
			if (!destinationreached)
			{
				while ((testlength - arg1) >= 60)
				{
					arg1 += 30;
					currentline.erase(currentline.end() - 1);
				//	cout << arg1 << endl;
				}
				if ((testlength - arg1) > 30)
					arg1 += 30;
				cout << "move " << 30 - (testlength - arg1) << " cm backwards" << endl;

				if (currentline.size()>1)
					circle(map, currentline[currentline.size() - 1], 0, Scalar(0, 0, 0));

				instruction.command = "move";
				instruction.arg1 = -1 * (30 - (testlength - arg1));
				instruction.arg2 = 0;

				publisher.publish(instruction);

				if (currentline.size()>1)
					start = currentline[currentline.size() - 2];
				nextstep = false;
				nextismapway = true;
				nextisrotcam = false;
				straightlength = 0;
				continue;
			}
		}
		lastanglerobot = angleofrobot;
		if (mapway||(nextstep&&nextismapway))
		{
			oriento = Point(0, 0);
			if (firstmap)
			{
				map = imread(mapaddress);
				Mat map2;
				cvtColor(map, map2, CV_BGR2GRAY);
				if (arg1 > 0 && arg2 > 0)
				{
					int src, dst;
					for (int i = 0; i<lmnum.size();i++)
					{
						if (lmnum[i] == arg1)
						{
							src = i;
							break;
						}
					}
					for (int i = 0; i<lmnum.size();i++)
					{
						if (lmnum[i] == arg2)
						{
							dst = i;
							break;
						}
					}
					start.x = lmpos[src].x;
					start.y = lmpos[src].y;
					goal.x = lmpos[dst].x;
					goal.y = lmpos[dst].y;
					if (start != Point(0, 0) && goal != Point(0, 0))
					{
						if (map2.at<uchar>(Point(start.x, start.y + 1)) == 195)
						{
							oriento = Point(-1, 0);
							angleofrobot = 90;
						}
						if (map2.at<uchar>(Point(start.x, start.y - 1)) == 195)
						{
							oriento = Point(1, 0);
							angleofrobot = -90;
						}
						if (map2.at<uchar>(Point(start.x + 1, start.y)) == 195)
						{
							oriento = Point(0, 1);
							angleofrobot = 180;
						}
						if (map2.at<uchar>(Point(start.x - 1, start.y)) == 195)
						{
							oriento = Point(0, -1);
							angleofrobot = 0;
						}
						if (map2.at<uchar>(Point(goal.x, goal.y + 1)) == 195)
						{
							goal.y = goal.y + 2;
						}
						else if (map2.at<uchar>(Point(goal.x, goal.y - 1)) == 195)
						{
							goal.y = goal.y - 2;
						}
						else if (map2.at<uchar>(Point(goal.x + 1, goal.y)) == 195)
						{
							goal.x = goal.x + 2;
						}
						else if (map2.at<uchar>(Point(goal.x - 1, goal.y)) == 195)
						{
							goal.x = goal.x - 2;
						}
						located = true;
					}
					else
					{
						cout << "landmark doen't exist";
						located = false;
					}
				else
				{
					cout << "I don't know where I am";
					located = false;
				}
				nextstep = false;

				instruction.command = "move";
				instruction.arg1 = 0;
				instruction.arg2 = 0;

				publisher.publish(instruction);
			}

			currentline.clear();
			
			if (start.x < goal.x)
			{
				way = MapTheWay(map, goal, start, true);
			}
			else
			{
				way = MapTheWay(map, start, goal);
			}
			
			mapway = false;
			firststep = true;
			firstmap = false;
			nextismapway = false;
			destinationreached = false;
			destinationtobereached = false;
			destinationtobetuned = false;
			straightlength = 0;



		}
		if (nextstep&&located)//&&!(destinationreached||destinationtobereached))
		{
			if (!way.empty()&&!nextisrotcam&&!nextistune)
				currentline.push_back(way[0]);
			int action = next_step(way);
			if (!destinationreached&&!destinationtobereached)
			{
				if (action != 8)
					angleofrotation = (action * 45) % 360 - angleofrobot;
				else
					angleofrotation = 0;
				if (angleofrotation > 180)
					angleofrotation -= 360;
				if (angleofrotation <= -180)
					angleofrotation += 360;
				if (angleofrotation != 0)
				{
					if (!firststep)
					{
						straightline = false;
					}
					else
					{
						straightline = true;

					}
					angleofrobot += angleofrotation;
					angleofrobot %= 360;
					if (angleofrobot > 180)
						angleofrobot -= 360;
					if (angleofrobot <= -180)
						angleofrobot += 360;
				}
				else
				{
					straightline = true;
				}

				if (straightline == true)
				{
					if (firststep)
					{
						cout << "rotate by " << angleofrotation << " degrees ccw" << endl;

						instruction.command = "rotate";
						instruction.arg1 = angleofrotation;
						instruction.arg2 = 0;


						publisher.publish(instruction);
						nextstep = false;

					}
					else if (nextistune)
					{
						cout << "tuning" << endl;


						instruction.command = "tune";
						instruction.arg1 = 0;
						instruction.arg2 = 0;

						publisher.publish(instruction);
						
						if(destinationtobetuned)
						{
							destinationtobetuned = false;
							destinationreached = true;
						}
						nextstep = false;
						landmark = false;
						straightlength -= 30;
						nextistune = false;
					}
					else if (nextisrotcam)
					{
						int camfinrotangle = angleofcamabs - angleofrobot;
						if (camfinrotangle > 180)
						{
							camfinrotangle -= 360;
						}
						if (camfinrotangle <= -180)
						{
							camfinrotangle += 360;
						}
						cout << "rotate cam to angle " << camfinrotangle << endl;

						instruction.command = "rotatecam";
						instruction.arg1 = camfinrotangle;
						instruction.arg2 = 0;

						publisher.publish(instruction);
						nextstep = false;
						nextistune = true;
						nextisrotcam = false;
						
						straightlength -= 30;


					}
					else if (landmark)
					{

						cout << "move " << straightlength << " cm forwards";

						cout << " and then rotate by " << angleofrotation << " degrees ccw" << endl;


						instruction.command = "move_rotate";
						instruction.arg1 = straightlength;
						instruction.arg2 = angleofrotation;

						publisher.publish(instruction);

						nextstep = false;
						nextisrotcam = true;

						testlength = straightlength;
						straightlength = 0;

					}
					straightlength += 30;
					//	waitKey(1);
				}
				else if (nextistune)
				{
					cout << "tuning" << endl;


					instruction.command = "tune";
					instruction.arg1 = 0;
					instruction.arg2 = 0;

					publisher.publish(instruction);
					
					if(destinationtobetuned)
					{
						destinationtobetuned = false;
						destinationreached = true;
					}
					nextstep = false;
					landmark = false;
					nextistune = false;
				}
				else if (nextisrotcam)
				{
					int camfinrotangle = angleofcamabs - angleofrobot;
					if (camfinrotangle > 180)
					{
						camfinrotangle -= 360;
					}
					if (camfinrotangle <= -180)
					{
						camfinrotangle += 360;
					}
					cout << "rotate cam to angle " << camfinrotangle<< endl;

					instruction.command = "rotatecam";
					instruction.arg1 = camfinrotangle;
					instruction.arg2 = 0;

					publisher.publish(instruction);
					nextstep = false;
					nextistune = true;
					nextisrotcam = false;
					


				}
				else
				{
					//		arg2 = 1;
					cout << "move " << straightlength << " cm forwards";

					cout << " and then rotate by " << angleofrotation << " degrees ccw" << endl;


					instruction.command = "move_rotate";
					instruction.arg1 = straightlength;
					instruction.arg2 = angleofrotation;

					publisher.publish(instruction);


					

					nextstep = false;
					testlength = straightlength;
					straightlength = 30;
					waitKey(1);
				}




				if (action == 8)
				{
					destinationtobereached = true;
				}

				firststep = false;
			}
			else if (destinationtobereached)
			{

				nextstep = false;
				cout << "move " << straightlength << " cm forwards"<<endl;


				instruction.command = "move";
				instruction.arg1 = straightlength;
				instruction.arg2 = 0;

				publisher.publish(instruction);
				way.clear();
				destinationtobetuned = true;
				destinationtobereached = false;
				nextisrotcam = true;
				testlength = straightlength;	
				straightlength = 0;
				waitKey(1);
			}
			else if (destinationreached)
			{

				nextstep = false;
				

				instruction.command = "reached";
				instruction.arg1 = 0;
				instruction.arg2 = 0;

				publisher.publish(instruction);
				way.clear();
				cout << "you have reached your destination or an error occured" << endl;
				straightlength = 0;
				waitKey(1);
			}
			//cout<<"angle of robot = "<<angleofrobot << endl;
		}

		spinOnce();
	}
}



void MappingHandler(const zuman_msgs::Instruction::ConstPtr& msg)
{
	if (msg->command == "map_way")
	{
		firstmap = true;
		mapway = true;
		arg1 = msg->arg1;
		arg2 = msg->arg2;
	}
	if (msg->command == "next_step")
	{
		nextstep = true;
		arg1 = msg->arg1;
		arg2 = msg->arg2;
	}
	if (msg->command == "remap")
	{
		remapobs = true;
		arg1 = msg->arg1;
		arg2 = msg->arg2;
	}

}