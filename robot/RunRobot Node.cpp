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
#include <ros/ros.h>
#include <Robot.h>
using namespace std;
using namespace robot;
/*
 * 
 */
int main(int argc, char** argv) {

    ros::init(argc,argv,"SKYNET IS LOVE. SKYNET IS LIFE");
    ros::NodeHandle nh;
    Robot assem1 = new Robot();
    assem1.Initialize();
    
    while(ros::ok())
    {
            ros::Timer timer = ros::NodeHandle::createTimer(ros::Duration(0.01),assem1.UpdatePosition());//update the popsition every 10ms to not bog down the processor
            assem1.Run();//move the robot. State Machine
    }
}

