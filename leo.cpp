#include <iostream>
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>

using namespace ur_rtde;

static void leo()
//int main(int argc, char* argv[])
{
	/* RTDEReceiveInterface rtde_receive("127.0.0.1");
	std::vector<double> joint_positions = rtde_receive.getActualQ();
	std::cout << std::to_string(joint_positions) << std::endl;
	*/

	// The constructor simply takes the IP address of the Robotsad
	
	//RTDEControlInterface rtde_control("134.28.124.104");

	// First argument is the pose 6d vector followed by speed and acceleration
	//rtde_control.moveL({ -0.143, -0.435, 0.20, -0.001, 3.12, 0.04 }, 0.2, 0.2);
	
	//rtde_control.moveJ({ -0.79, -1,57 , 1,57 , -1,57, -1,57, 1,57 }, 0.1, 0.1);
	
	//rtde_control.stopJ();
	
	//std::cout << "completed" << std::endl;
	
	RTDEReceiveInterface rtde_receive("134.28.124.104");

	while (rtde_receive.isConnected())
	{
		std::cout << "Actual Q is: " << std::endl;
		for (const auto& d : rtde_receive.getActualQ()) 
			std::cout << d << " ";
			//std::this_thread::sleep_for(std::chrono::milliseconds(500));
			std::cout << std::endl;
		
		std::cout << "TCP POSE is: " << std::endl;
		for (const auto& e : rtde_receive.getActualTCPPose()) 
			std::cout << e << " ";
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			std::cout << std::endl;
		
	}

	do
	{
		std::cout << '\n' << "Lost connection to robot, waiting for user input before retrying...";
	} while (std::cin.get() != '\n');

	rtde_receive.reconnect();
	if (rtde_receive.isConnected())
	{
		std::cout << "Successfully Reconnected to Robot, Actual q is: " << std::endl;
		//for (const auto& d : rtde_receive.getActualQ())
			for (const auto& d : rtde_receive.getActualTCPPose())
			std::cout << d << " ";
	}



}

