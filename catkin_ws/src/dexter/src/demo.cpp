#include "ros/ros.h"
#include "std_msgs/Float32MultiArray.h"

#include <iostream>
#include <vector>


// A very basic movement demo
int main(int argc, char **argv)
{
	ros::init(argc, argv, "button");
	ros::NodeHandle node;
	ros::Publisher control = node.advertise<std_msgs::Float32MultiArray>("/control", 50);

	std::vector<std::vector<float>> positions;
	positions.push_back({45, 0, 0, 0, 0});			// TODO: Figure out why the first
	positions.push_back({0, 0, 0, 0, 0});			//		 message is ignored
	positions.push_back({0, 45, 30, 0, 0});
	positions.push_back({0, 15, 60, 0, 0});
	positions.push_back({30, 45, -45, 0, 0});
	positions.push_back({90, 45, -45, 0, 0});
	positions.push_back({90, 45, -45, 20, -20});
	positions.push_back({90, 45, -45, -20, 20});
	positions.push_back({0, 0, 0, 0, 0});




	for (auto pos = positions.begin(); pos != positions.end(); ++pos)
	{
		std_msgs::Float32MultiArray msg;
		msg.data = *pos;
		control.publish(msg);
		ros::Duration(2).sleep();
		ros::spinOnce();

	}

	return 0;
}