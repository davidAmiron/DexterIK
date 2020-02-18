#include "ros/ros.h"
#include <trac_ik/trac_ik.hpp>
#include <kdl/chainiksolverpos_nr_jl.hpp>

using std::cout;
using std::endl;

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
	for (int i = 0; i < joints.rows(); i++) {
		cout << "\tJoint " << i << ": " << joints(i) << endl;
	}
	cout << endl;
}

void do_stuff() {
	TRAC_IK::TRAC_IK tracik_solver("kp0093_1", "kp0093_1_186_kp0093-01_toolinterface",
		"/robot_description", 5, 1e-2);

	KDL::Chain chain;
	KDL::JntArray lower_limits, upper_limits;

	bool valid = tracik_solver.getKDLChain(chain);

	valid = tracik_solver.getKDLLimits(lower_limits, upper_limits);

	// Create forward kinematics solver
	KDL::ChainFkSolverPos_recursive fk_solver(chain);

	KDL::JntArray starting_guess(chain.getNrOfJoints());
	starting_guess(0) = 0;
	starting_guess(1) = 0;
	starting_guess(2) = 0;
	starting_guess(3) = 0;
	starting_guess(4) = 0;

	KDL::JntArray joint_test_positions(chain.getNrOfJoints());
	joint_test_positions(0) = 0;
	joint_test_positions(1) = 0;
	joint_test_positions(2) = 0;
	joint_test_positions(3) = 0;
	joint_test_positions(4) = 0;
	
	KDL::Frame end_effector_pose;
	fk_solver.JntToCart(joint_test_positions, end_effector_pose);
	cout << "Frame with all joints 0" << endl;
	print_frame(end_effector_pose);

	KDL::Frame frame(KDL::Rotation::RPY(-1.57, 0, -1.9), KDL::Vector(0, 0, 0.6));
	cout << "Desired Frame" << endl;
	print_frame(frame);

	KDL::JntArray result_joints;
	int rc = tracik_solver.CartToJnt(starting_guess, frame, result_joints);
	cout << "rc: " << rc << endl;
	cout << "Result Joints" << endl;
	print_joints(result_joints);

}

int main(int argc, char **argv) {

	ros::init(argc, argv, "ik_tests");
	ros::NodeHandle nh("~");

	//int num_samples




	do_stuff();




	return 0;
}