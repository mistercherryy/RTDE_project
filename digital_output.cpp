#include <ur_rtde/rtde_io_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
#include <iostream>
#include <thread>
#include <ur_rtde/rtde.h>
#include <bitset>
#include <chrono>

#include "Library.h"	// Access library details
#include "DeviceList.h" // Access devices and communication state
#include "SenseGlove.h" // SenseGlove interface through which we access data.
#include "Tracking.h"


using namespace ur_rtde;
//***output4 is going to open the gripper by In4 on motordriver

//***output7 is going to close the gripper by In3 on motordriver

static void digital_output()

//int main(int argc, char* argv[]) 
{
    RTDEIOInterface rtde_io104("134.28.124.104");   //to open the gripper
    RTDEIOInterface rtde_io86("134.28.124.86");     //to close the gripper
    RTDEReceiveInterface rtde_receive("134.28.124.104");

    std::cout << "Testing " << SGCore::Library::Version() << std::endl;
    std::cout << "=======================================" << std::endl;

    if (SGCore::DeviceList::SenseCommRunning()) //check if the Sense Comm is running. If not, warn the end user.
    {
        SGCore::SG::SenseGlove testGlove;
        
        if (SGCore::SG::SenseGlove::GetSenseGlove(testGlove)) //retrieves the first Sense Glove it can find. Returns true if one can be found
        {
            std::cout << "Activating " << testGlove.ToString() << " on key press." << std::endl;
            //system("pause");
            float maxGlove = 196;
            float maxGpr = 67;
            float speed = 13.4;
            float minGlove = 0;
            float minGrp = 0;
            float grp_previous, grp_current, time;
            grp_previous = 0;
            float tol = 5;

            while (true) {
                //std::cout << "Getting new Pose" << std::endl;
                //Retrieving Glove Pose: The position / rotation of the glove, as well as its sensor angles placed in the right direction.
                SGCore::SG::SG_GlovePose glovePose;

                if (testGlove.GetGlovePose(glovePose))
                {
                    //As an example, lets calculate fingertip positions.

                    //If we wish to calculate hand variables, we need a "hand profile" to tell the Sense Glove our hand lengths.
                    SGCore::SG::SG_HandProfile handProfile = SGCore::SG::SG_HandProfile::Default(testGlove.IsRight()); //create a default profile, either left or right.
                    SGCore::Kinematics::BasicHandModel handModel = SGCore::Kinematics::BasicHandModel::Default(testGlove.IsRight()); //create a default profile, either left or right.
                    std::vector<SGCore::Kinematics::Vect3D> tipPositions = glovePose.CalculateFingerTips(handProfile); //calculates fingertip position


                    std::cout << std::endl;

                    float dThumbMiddle = tipPositions[0].DistTo(tipPositions[2])-20; //calculates the distance between thumb (0) and middle finger (1), in mm.
                    std::cout << "The distance between thumb and middle finger is " << std::to_string(dThumbMiddle) << "mm." << std::endl;
                    //20 is given as an offset due to thickness of fingers. Normally distTo() calculates distance between sensors of glove fingertips.
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));

                    
                   // grp_current = myMap(dThumbMiddle);
                    grp_current = (dThumbMiddle - minGlove) * (maxGpr - minGrp) / (maxGlove - minGlove) + minGrp;
                    time = 1000*abs(grp_current- grp_previous)/speed;

                    if ((grp_current - grp_previous)>tol) {
                        rtde_io104.setAnalogOutputVoltage(0, 0.3);
                        std::cout << "OPEN THE GRIPPER" << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds((int) time));
                        rtde_io104.setAnalogOutputVoltage(0, 0);
                    }

                    if((grp_current - grp_previous)< -tol) {
                        rtde_io86.setAnalogOutputVoltage(0, 0.3);
                        std::cout << "CLOSE THE GRIPPER" << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds((int)time));
                        rtde_io86.setAnalogOutputVoltage(0, 0);
                    }

                    grp_previous = grp_current;

                    

                }
                
                std::this_thread::sleep_for(std::chrono::milliseconds(100)); //wait for 100ms.
            }
        }
    }
    
    else
        std::cout << "SenseComm is not running. Please start it and try again." << std::endl;

    std::cout << "=======================================" << std::endl;
    std::cout << "Press any key to exit." << std::endl;
    system("pause");

    


}




/*static float myMap(float x) {
    return (x-minGlove)*(maxGpr-minGrp)/(maxGlove-minGlove)+minGrp;
}
*/