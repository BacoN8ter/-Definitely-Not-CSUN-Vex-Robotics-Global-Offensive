/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RunRobot Node.cpp
 * Author: nathan
 *
 * Created on April 2, 2017, 12:28 PM
 */

#include <cstdlib>
#include "Robot.h"
using namespace std;
using namespace robot;
/*
 * 
 */
int main(int argc, char** argv) {

    ros::init(argc,argv,"RunRobot_ros");
    ROS_INFO_STREAM_ONCE("SKYNET IS LOVE. SKYNET IS LIFE");
    ros::NodeHandle nh;
    Robot assem1;
    assem1.Initialize();
    ros::Rate rate(10);
    while(ros::ok())
    {
            //ros::Timer timer = nh.createTimer(ros::Duration(0.01),Robot::UpdatePosition);//update the popsition every 10ms to not bog down the processor
            assem1.Run(assem1);//move the robot. State Machine
            
    }
}

