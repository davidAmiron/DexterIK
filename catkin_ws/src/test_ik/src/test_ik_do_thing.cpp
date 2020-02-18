#include "ros/ros.h"
#include <trac_ik/trac_ik.hpp>
#include <kdl/chainiksolverpos_nr_jl.hpp>

using std::cout;
using std::endl;

void do_stuff() {
	TRAC_IK::TRAC_IK tracik_solver("kp0093_1", "kp0093_1_186_kp0093-01_toolinterface",
		"/robot_description", 0.005, 1e-5);

	cout << "Hi" << endl;
	KDL::Chain chain;
	KDL::JntArray lower_limits, upper_limits;

	bool valid = tracik_solver.getKDLChain(chain);

	std::cout << valid << std::endl;

	valid = tracik_solver.getKDLLimits(lower_limits, upper_limits);
	cout << valid << endl;

	cout << chain.getNrOfJoints() << endl;


	// Create forward kinematics solver
	KDL::ChainFkSolverPos_recursive fk_solver(chain);

	KDL::JntArray joint_test_positions(chain.getNrOfJoints());
	joint_test_positions(0) = 0;
	joint_test_positions(1) = 0;
	joint_test_positions(2) = 0;
	joint_test_positions(3) = 0;
	joint_test_positions(4) = 0;
	
	KDL::Frame end_effector_pose;
	fk_solver.JntToCart(joint_test_positions, end_effector_pose);

	//cout << end_effector_pose << endl;

}

int main(int argc, char **argv) {

	ros::init(argc, argv, "ik_tests");
	ros::NodeHandle nh("~");

	//int num_samples




	do_stuff();




	return 0;
}