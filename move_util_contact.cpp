#include <ur_rtde/rtde_control_interface.h>


using namespace ur_rtde;


//RTDEControlInterface rtde_control("127.0.0.1");
static void move_util_contact()
//int main(int argc, char* argv[])
{
	RTDEControlInterface rtde_control("134.28.124.104");

	// Parameters
	std::vector<double> speed = { 0, 0, -0.100, 0, 0, 0 };
	rtde_control.moveUntilContact(speed);
	rtde_control.stopScript();
	//return 0;
}