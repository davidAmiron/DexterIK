#include "ros/ros.h"
#include "ros/console.h"
#include "std_msgs/Float32MultiArray.h"
#include <vector>

#include "Dexter.h"

int joint_count = 5;

Dexter d("192.168.1.240", 50000);

void control_callback(const std_msgs::Float32MultiArray::ConstPtr& angles)
{
	std::vector<float> data = angles->data;
	if (data.size() != joint_count)
	{
		ROS_ERROR("Got %d angles, need %d", (int)data.size(), joint_count);
		return;
	}

	d.move_to_joints(data);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "dexter_control");
	ros::NodeHandle node;
	ros::Subscriber sub = node.subscribe("control", 50, control_callback);
	ros::spin();

	return 0;
}