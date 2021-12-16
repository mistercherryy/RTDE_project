#include <ur_rtde/rtde.h>
#include <ur_rtde/rtde_io_interface.h>

#include <bitset>
#include <chrono>
#include <iostream>
#include <thread>
#include <ur_rtde/rtde_receive_interface.h>

static void rtdeio_interface()
//int main(int argc, char* argv[]) 
{
    using namespace ur_rtde;
    
    //RTDE rtde("134.28.124.86");
    //RTDEIOInterface rtde_io("134.28.124.86");
    //RTDEReceiveInterface rtde_receive("134.28.124.86");


   // rtde_io.setAnalogOutputVoltage(0, 0.465);

    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    //rtde_io.setAnalogOutputVoltage(0, 0);

    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
/*
    RTDE::RobotCommand robot_cmd;
    robot_cmd.type_ = RTDE::RobotCommand::Type::SET_STD_ANALOG_OUT;
    robot_cmd.recipe_id_ = 5;
    robot_cmd.std_analog_output_mask_ = static_cast<uint8_t>(1u << 1);
    robot_cmd.std_analog_output_type_ = 1;  // set output type to voltage
    robot_cmd.std_analog_output_1_ = 0.465;
    rtde.send(robot_cmd);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    RTDE::RobotCommand robot_cmd;
    robot_cmd.type_ = RTDE::RobotCommand::Type::SET_STD_ANALOG_OUT;
    robot_cmd.recipe_id_ = 5;
    robot_cmd.std_analog_output_mask_ = static_cast<uint8_t>(1u << 1);
    robot_cmd.std_analog_output_type_ = 1;  // set output type to voltage
    robot_cmd.std_analog_output_1_ = 0.0;
    rtde.send(robot_cmd);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    */
}