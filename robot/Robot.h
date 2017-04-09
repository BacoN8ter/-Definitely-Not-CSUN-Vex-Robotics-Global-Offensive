/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Robot.h
 * Author: nathan
 *
 * Created on April 2, 2017, 12:27 PM
 */

#ifndef ROBOT_H
#define ROBOT_H
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <Enums.h>
#include <RobotMath.h>
#include <ros/ros.h>
#include <Locomotion.cpp>
#include <geometry_msgs/Pose2D.h>
#include <tf/tf.h>

namespace robot
{
    class Robot {
    public:
        Robot();
        virtual ~Robot();
        
        ros::Subscriber sub_leftDriveEnc,
                        sub_rightDriveEnc,
                        sub_wayPoint,
                        sub_gyro;
       
        geometry_msgs::Pose2D localPose,
                              prevPose;
        Encoder leftDriveEnc,
                rightDriveEnc;
        
        geometry_msgs::Pose2D wayPoint;
                              
        geometry_msgs::Quaternion gyro;
        float xSpeed,
              ySpeed;//speed of the robot
        
        float wheelCircumference = 20.0;  // wheel circumfrence for vex omni. unit determines measurement of system. i.e circ -> inches means x,y -> inches
        
        SubStates subState = IdleClaw;
        Phase phase = Instruction;
        
        int motor[6];//list of motors. 0->5 for the left and right side motors
        
        void Initialize();
        void Stop();
        void Turn(double targetAngle);
        void Move();
        void UpdatePosition();
        void Run();
    private:
        void leftDriveEncCallback(Encoder& robotEncoder);
        void rightDriveEncCallback(Encoder& robotEncoder);
        void wayPointCallback(geometry_msgs::Pose2D& newWaypoint);
        void gyroCallBack(tf::Quaternion& rpy);
        

    };
}
#endif /* ROBOT_H */

