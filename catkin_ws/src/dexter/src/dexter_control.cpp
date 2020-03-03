#include "ros/ros.h"
#include "ros/console.h"
#include "std_msgs/Float32MultiArray.h"
#include <vector>

#include "Dexter.h"

int joint_count = 5;

Dexter d("192.168.1.240", 50000);

float rad_to_deg(float radians)
{
	return radians * (180.0 / 3.14159265);
}

void control_callback_deg(const std_msgs::Float32MultiArray::ConstPtr& angles)
{
	std::vector<float> data = angles->data;
	if (data.size() != joint_count)
	{
		ROS_ERROR("Got %d angles, need %d", (int)data.size(), joint_count);
		return;
	}

	d.move_to_joints(data);
}

void control_callback_rad(const std_msgs::Float32MultiArray::ConstPtr& angles)
{
	std::vector<float> data = angles->data;
	if (data.size() != joint_count)
	{
		ROS_ERROR("Got %d angles, need %d", (int)data.size(), joint_count);
		return;
	}

	std::transform(data.begin(), data.end(), data.begin(), rad_to_deg);

	d.move_to_joints(data);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "dexter_control");
	ros::NodeHandle node;
	ros::Subscriber sub_deg = node.subscribe("control/deg", 50, control_callback_deg);
	ros::Subscriber sub_rad = node.subscribe("control/rad", 50, control_callback_rad);
	ros::spin();

	return 0;
}