#include <ur_rtde/rtde_control_interface.h>
#include <thread>
#include <chrono>

using namespace ur_rtde;
using namespace std::chrono;

static void servoj()
//int main(int argc, char* argv[])
{
    RTDEControlInterface rtde_control("134.28.124.104");

    // Parameters
    double velocity = 0.2;
    double acceleration = 0.2;
    double dt = 1.0 / 500; // 2ms
    double lookahead_time = 0.03;
    double gain = 2000;
    std::vector<double> joint_q = { -0.343, -1.449, 2.122, -3.79, -1.536, 0 };
    std::vector<double> room_testj = { -1.035, -1.3172, 2.0733, -3.897, -1.5708, 0 };

    while (true) {
        // Move to initial joint position with a regular moveJ
        rtde_control.moveJ(joint_q, 0.2, 0.2, false);

        // Execute 500Hz control loop for 2 seconds, each cycle is ~2ms
        for (unsigned int i = 0; i < 1000; i++)
        {
            auto t_start = high_resolution_clock::now();
            rtde_control.servoJ(room_testj, velocity, acceleration, dt, lookahead_time, gain);
            //joint_q[0] += 0.001;
            //joint_q[1] -= 0.0005;

            //joint_q[4] -= 0.001;
            //joint_q[5] -= 0.001;
            //std::this_thread::sleep_for(std::chrono::milliseconds(2));
            // joint_q[5] += 0.002;
             //joint_q[5] -= 0.002;

            auto t_stop = high_resolution_clock::now();
            auto t_duration = std::chrono::duration<double>(t_stop - t_start);

            if (t_duration.count() < dt)
            {
                std::this_thread::sleep_for(std::chrono::duration<double>(dt - t_duration.count()));
            }
        }

        rtde_control.servoStop();
        rtde_control.stopScript();
    }
    //return 0;
}