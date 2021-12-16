#include <ur_rtde/rtde_io_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
#include <iostream>
#include <thread>
#include <ur_rtde/rtde.h>
#include <bitset>
#include <chrono>


using namespace ur_rtde;

static void analog_output_test()
//int main(int argc, char* argv[])
{
    RTDEIOInterface rtde_io("134.28.124.104");
    RTDEIOInterface rtde_iomax("134.28.124.86");
    RTDEReceiveInterface rtde_receive("134.28.124.104");

    while(true)
        ///set for Analogout0:
        std::this_thread::sleep_for(std::chrono::milliseconds(750));
    std::cout << "waited 750ms" << std::endl;

    rtde_io.setAnalogOutputVoltage(0, 0.3);
    std::cout << "given voltage from LEFT controlbox" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(750));
    std::cout << "waited 750ms" << std::endl;

    rtde_io.setAnalogOutputVoltage(0, 0);
    std::cout << "set voltage from left controlbox to zero" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "Opening finished" << std::endl;

    ///set for Analogoutmax to close:
    std::this_thread::sleep_for(std::chrono::milliseconds(750));
    std::cout << "Waited 750ms" << std::endl;

    rtde_iomax.setAnalogOutputVoltage(0, 0.3);
    std::cout << "given voltage from RIGHT controlbox" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    std::cout << "waited 500ms" << std::endl;

    rtde_iomax.setAnalogOutputVoltage(0, 0);
    std::cout << "set voltage from left controlbox to zero" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "closing finished" << std::endl;






}