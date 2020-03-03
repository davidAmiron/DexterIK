#include "ros/ros.h"
#include "ros/console.h"
#include "std_msgs/Float32MultiArray.h"
#include "geometry_msgs/Pose.h"
#include <vector>
#include <trac_ik/trac_ik.hpp>
#include <kdl/chainiksolverpos_nr_jl.hpp>

#include "Dexter.h"

using std::cout;
using std::endl;

int joint_count = 5;

Dexter d("192.168.1.240", 50000);

void print_frame(KDL::Frame frame) {
	cout << "Frame Position:" << endl;
	cout << "\tx: " << frame.p[0] << endl;
	cout << "\ty: " << frame.p[1] << endl;
	cout << "\tz: " << frame.p[2] << endl;

	double roll, pitch, yaw;
	frame.M.GetRPY(roll, pitch, yaw);
	cout << "Frame Orientation:" << endl;
	cout << "\troll: " << roll << endl;
	cout << "\tpitch: " << pitch << endl;
	cout << "\tyaw: " << yaw << endl;

	cout << endl;
}

void print_joints(KDL::JntArray joints) {
	cout << "Joint Array:" << endl;
	for (int i = 0; i < joints.rows(); i++)
	{
		cout << "\tJoint " << i << ": " << joints(i) << endl;
	}
	cout << endl;
}

float rad_to_deg(float radians)
{
	return radians * (180.0 / 3.14159265);
}

float deg_to_rad(float degrees)
{
	return degrees * (3.14159265 / 180.0);
}

std::vector<float> jnt_array_to_vector(KDL::JntArray joints)
{
	std::vector<float> joints_v;
	for (int i = 0; i < joints.rows(); i++)
	{
		joints_v.push_back(joints(i));
	}

	return joints_v;
}

// Send joints, joints are in radians
void send_joints(std::vector<float> joints)
{
	if (joints.size() != joint_count)
	{
		ROS_ERROR("Got %d angles, need %d", (int)joints.size(), joint_count);
		return;
	}

	d.move_to_joints(joints);
}

void control_callback_deg(const std_msgs::Float32MultiArray::ConstPtr& angles)
{
	std::vector<float> joints = angles->data;
	std::transform(joints.begin(), joints.end(), joints.begin(), deg_to_rad);
	send_joints(joints);
}

void control_callback_rad(const std_msgs::Float32MultiArray::ConstPtr& angles)
{
	send_joints(angles->data);
}

void control_callback_pos(const geometry_msgs::Pose::ConstPtr& pose)
{
	TRAC_IK::TRAC_IK tracik_solver("kp0093_1", "kp0093_1_186_kp0093-01_toolinterface",
		"/robot_description", 5, 1e-2);

	KDL::Chain chain;
	KDL::JntArray lower_limits, upper_limits;

	bool valid = tracik_solver.getKDLChain(chain);
	valid = tracik_solver.getKDLLimits(lower_limits, upper_limits);

	KDL::JntArray starting_guess(chain.getNrOfJoints());
	starting_guess(0) = 0;
	starting_guess(1) = 0;
	starting_guess(2) = 0;
	starting_guess(3) = 0;
	starting_guess(4) = 0;

	KDL::Frame frame(KDL::Rotation::Quaternion(pose->orientation.x,
											   pose->orientation.y,
											   pose->orientation.z,
											   pose->orientation.w),
					 KDL::Vector(pose->position.x,
					 			 pose->position.y,
					 			 pose->position.z)
	);

	KDL::JntArray result_joints;
	int rc = tracik_solver.CartToJnt(starting_guess, frame, result_joints);

	cout << "rc: " << rc << endl;

	print_frame(frame);
	print_joints(result_joints);

	//cout << "Publishing" << endl;
	//cout << jnt_array_to_vector(result_joints)[0] << endl;
	send_joints(jnt_array_to_vector(result_joints));

}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "dexter_control");
	ros::NodeHandle node;
	ros::Subscriber sub_deg = node.subscribe("control/deg", 50, control_callback_deg);
	ros::Subscriber sub_rad = node.subscribe("control/rad", 50, control_callback_rad);
	ros::Subscriber sub_ik = node.subscribe("control/pos", 50, control_callback_pos);
	ros::spin();

	return 0;
}