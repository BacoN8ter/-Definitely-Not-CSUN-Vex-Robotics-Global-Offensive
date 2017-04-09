/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Robot.cpp
 * Author: nathan
 * 
 * Created on April 2, 2017, 12:27 PM
 */

#include "Robot.h"
#define KpT 0.9
#define KpD 4.5
#define TimeStep 100.0
using namespace robot;
        
    Robot::Robot() {
        this->Initialize();
    }

    Robot::~Robot() {
    }

    void Robot::Initialize()
    {
        ros::NodeHandle nh;
        localPose.x = 0;
        localPose.y = 0;
        localPose.theta = 0;//degrees
        
        sub_gyro = nh.subscribe("gyro",1000,&gyroCallback,this);
        sub_leftDriveEnc = nh.subscribe("leftDriveEnc",1000,&leftDriveEncCallback,this);
        sub_rightDriveEnc = nh.subscribe("rightDriveEnc",1000,&rightDriveEncCallback,this);
        sub_wayPoint = nh.subscribe("waypoint",1000,&wayPointCallback,this);
                
    }
    
    //turns the desired amount of degrees in the proper direction
    void Robot::Turn(double targetAngle)
    {
        //current difference between the angle calculated and the current for
        //proportional control turning
        double difference = (targetAngle - localPose.theta);
        //calculate to see if it is faster to turn left or right
        while(difference > 180)
        {
                difference -= 360;
        }
        while(difference < -180)
        {
                difference += 360;
        }
        //p control
        while(abs(difference) > 1)
        {
            difference = (targetAngle - localPose.theta);
            while(difference > 180)
            {
                    difference -= 360;
            }
            while(difference < -180)
            {
                    difference += 360;
            }

            int power = difference * KpT;
            power = power < -100 ? -100 : power;
            power = power > 100 ? 100 : power;
            motor[leftBack] = power;
            motor[leftFront] = power;
            motor[leftTop] = power;
            motor[rightBack] = -power;
            motor[rightFront] = -power;
            motor[rightTop] = -power;
        }
    }

    //everything put together in order to travel to target point from current point
    void Robot::Move()
    {
        //turn to angle
        Turn(AngleBetween(localPose.x, localPose.y, wayPoint.x, wayPoint.y));
        //calculate hypotenuse
        float difference = sqrt(pow(localPose.x - wayPoint.x, 2) + pow(localPose.y - wayPoint.y, 2));
        //p control for driving the hypotenuse
        while(difference > 0.05)
        {
            difference -= sqrt(pow(xSpeed, 2) + pow(ySpeed, 2));

            int power = difference * KpD;
            power = power < 10 ? 10 : power;
            //float angleOffset = (AngleBetween(Bot.X, Bot.Y, X, Y) - Bot.Heading);
            power = power >= 100 ? 100 : power;

            motor[leftTop] = power;// + angleOffset;
            motor[leftFront] = power;// + angleOffset;
            motor[leftBack] = power;// + angleOffset;

            motor[leftTop] = power;// - angleOffset;
            motor[leftFront] = power;// - angleOffset;
            motor[leftBack] = power;// + angleOffset;
        }
    }
    
    void Robot::UpdatePosition()
    {
        float distance = CalculateDistance(leftDriveEnc,rightDriveEnc);

        localPose.theta = gyro.w % 360; //this keeps the robot direction constrained to the range 0-360 degrees

        //calculate the distance the robot has traveled along its path (the hypotenuse)
        xSpeed = cosh(localPose.theta) * distance;
        ySpeed = sinh(localPose.theta) * distance;
        //updates the robots position based on the displacement calculated above
        localPose.x += xSpeed;
        localPose.y += ySpeed;
    }
    
    void Robot::Stop()
    {
        motor[leftBack] = 0;
        motor[leftFront] = 0;
        motor[leftTop] = 0;
        motor[rightBack] = 0;
        motor[rightFront] = 0;
        motor[rightTop] = 0;
    }
    
    void Robot::Run()
    {
        FSM();
    }
    
    void leftDriveEncCallback(Encoder& robotEncoder)
    {
        Robot::leftDriveEnc = robotEncoder;
    }
    void rightDriveEncCallback(Encoder& robotEncoder)
    {
        Robot::rightDriveEnc = robotEncoder;
    }
    void wayPointCallback(geometry_msgs::Pose2D& newWaypoint)
    {
        Robot::wayPoint = newWaypoint;
    }
    void gyroCallback(tf::Quaternion& rpy)
    {
         Robot::gyro = rpy;
    }
   
    
