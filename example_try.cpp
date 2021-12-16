#include <iostream>
#include <thread>
#include <chrono>
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>



using namespace ur_rtde;


//static void example_try()
int main(int argc, char* argv[]) 
{
	// The constructor simply takes the IP address of the Robot
	RTDEControlInterface rtde_control("134.28.124.104");
	RTDEReceiveInterface rtde_receive("134.28.124.104");
	
	//SET STARTING JOINT AND LINEAR SPACE POSES
	std::vector<double> joint_q = { -0.343, -1.449, 2.122, -3.79, -1.536, 0 };
	std::vector<double> joint_q_two = { -0.327, -0.624, 1.062, -3.079, -1.534, 0.3 };
	std::vector<double> tcp_pose = { -1.169, 0.208, 0.346, 2.7, 1.652, -1.517 };
	std::vector<double> room_testj = { -1.035, -1.3172, 2.0733, -3.897, -1.5708, 0.785 };
	std::vector<double> room_tcp = { -0.7, 0.5, 0.5, 3.660, -0.458, -2.261 };
	
	//setting the TCP as 20cm from Z axis of tool space of robot
	std::vector<double> tcp_offset = {0,0,0.2,0,0,0};
	rtde_control.setTcp(tcp_offset);

	//START THE LOOP FOR ACTUAL COMMANDS
	while (rtde_receive.isConnected() && rtde_control.isConnected())
	{
		//rtde_control.isJointsWithinSafetyLimits(joint_q)
		
		/* clock_t clock(void) returns the number of clock ticks
					 elapsed since the program was launched.To get the number
					 of seconds used by the CPU, you will need to divide by
					CLOCKS_PER_SEC.where CLOCKS_PER_SEC is 1000000 on typical
					32 bit system.  */
		//std::clock_t start, end; //clock instantiated 

		//start the clock to count the time
		//start = clock();
		
		auto t1 = std::chrono::high_resolution_clock::now();

		
		// Move to initial joint position with a regular moveJ
		
			rtde_control.moveJ(joint_q, 0.5, 1, false);
			//rtde_control.servoJ(joint_q, 0, 0, 0.008, 0.1, 300);
			std::vector<double> a = rtde_control.getForwardKinematics(joint_q);
			std::vector<double> b = rtde_control.getInverseKinematics(tcp_pose);
			std::cout <<"Forward: " << a[0] << " " << a[1] << " " << a[2] << " " << a[3] << " " << a[4] << " " << a[5] << std::endl;
			
				

			if (rtde_control.isProgramRunning()) 
				
				std::cout << "MOVEJ Actual Q is: " << std::endl;
			for (const auto& d : rtde_receive.getActualQ())
				std::cout << d << " ";
			//std::this_thread::sleep_for(std::chrono::milliseconds(500));
			std::cout << std::endl;

				std::cout << "MOVEJ TCP POSE is: " << std::endl;
				for (const auto& e : rtde_receive.getActualTCPPose())
					std::cout << e << " ";
				std::this_thread::sleep_for(std::chrono::milliseconds(8));
				std::cout << std::endl;
			
			std::this_thread::sleep_for(std::chrono::milliseconds(8));

			// Move to secondary joint position with a regular moveL
			rtde_control.moveL(room_tcp, 0.5, 1, false);
			
			//instantiate another time after move command is executed
			auto t2 = std::chrono::high_resolution_clock::now();
		
			//rtde_control.servoL(tcp_pose, 0, 0, 0.008, 0.1, 1000);
			//rtde_control.moveL(tcp_pose,0.1,0.2,false);
			//std::cout << "Inverse: " << b[0] << " " << b[1] << " " << b[2] << " " << b[3] << " " << b[4] << " " << b[5] << std::endl;
			
			std::cout << "MAINMOVE Actual Q is: " << std::endl;
			for (const auto& d : rtde_receive.getActualQ())
				std::cout << d << " ";
			//std::this_thread::sleep_for(std::chrono::milliseconds(500));
			std::cout << std::endl;

			std::cout << "MAINMOVE TCP POSE is: " << std::endl;
			for (const auto& e : rtde_receive.getActualTCPPose())
				std::cout << e << " ";
			std::this_thread::sleep_for(std::chrono::milliseconds(8));
			std::cout << std::endl;
			rtde_control.stopJ(2);
		
			//end the clock time and then calculate
			//end = clock();
			//double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
			//std::cout << "Time taken by program is : " << std::fixed
			//	<< time_taken << std::setprecision(5);
			//std::cout << " sec " << std::endl;
		
			/* Getting number of milliseconds as a double. */
			
			std::chrono::duration<double, std::milli> ms_double = t2 - t1;
			std::cout << "TIME TAKEN: " << ms_double.count()/1000 << "SECONDS"<<std::endl;
		

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

	// Parameters

	
	

	

	//return 0;
}