#include "ros/ros.h"
#include "std_msgs/Float32MultiArray.h"

#include <iostream>
#include <vector>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "button");
	ros::NodeHandle node;
	ros::Publisher control = node.advertise<std_msgs::Float32MultiArray>("/control", 50);

	std::vector<std::vector<float>> positions;
	positions.push_back({45, 0, 0, 0, 0});			// TODO: Figure out why the first
	positions.push_back({0, 0, 0, 0, 0});			//		 message is ignored
	positions.push_back({37, 30, 60, 30, -15});
	positions.push_back({37, 40, 70, 30, -25});
	positions.push_back({37, 50, 75, 30, -35});
	positions.push_back({37, 57, 75, 30, -35});
	positions.push_back({37, 66, 75, 30, -35});


	for (auto pos = positions.begin(); pos != positions.end(); ++pos)
	{
		std_msgs::Float32MultiArray msg;
		msg.data = *pos;
		control.publish(msg);
		ros::Duration(1).sleep();
		ros::spinOnce();

	}

	return 0;
}