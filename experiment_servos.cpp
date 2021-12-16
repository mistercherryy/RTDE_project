#include <iostream>
#include <thread>
#include <chrono>
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>


using namespace ur_rtde;

static void experiment_servos()
//int main(int argc, char* argv[]) 
{
	RTDEControlInterface rtde_control("134.28.124.104");
	RTDEReceiveInterface rtde_receive("134.28.124.104");
	std::vector<double> joint_q = { -0.343, -1.449, 2.122, -3.79, -1.536, 0 };
	std::vector<double> joint_q_two = { -0.327, -0.624, 1.062, -3.079, -1.534, 0.3 };
	std::vector<double> tcp_pose = { -1.169, 0.208, 0.346, 2.7, 1.652, -1.517 };
	std::vector<double> room_testj = { -1.035, -1.3172, 2.0733, -3.897, -1.5708, 0 };
	std::vector<double> room_tcp = { -0.5, 0.5, 0.5, 4.327, 1.188, -1.186 };
	std::vector<double> tcp_pose_inv = { -0.362609 ,-0.650487, 1.07051, -2.88926, -1.16308, 0.309214 };
	
	
	
		rtde_control.moveJ(joint_q, 0.1, 0.1, false);
		//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		//rtde_control.moveL(tcp_pose, 0.1, 0.2, false);
		//rtde_control.moveJ(tcp_pose_inv, 0.1, 0.1, false);
		rtde_control.servoJ(room_testj, 0.5, 0.5, 1.0 / 500, 0.05, 1200);
		rtde_control.servoStop();
		rtde_control.stopScript();
		rtde_control.stopJ();
		
	
		
}