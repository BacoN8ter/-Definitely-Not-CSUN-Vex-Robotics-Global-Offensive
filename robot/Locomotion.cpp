/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <Robot.h>
#include <Enums.h>
using namespace robot;
    ////////////////////////////////////////////////////////////////////////
    States IdleRobotState(States state)
    {
        Robot::Stop();
        /*"roaming phase" -> findObj*/
        /*"instruction phase" -> GoToObj*/
        if(Robot::phase == Roam)
        {
            return FindObj;
        }
        if(Robot::phase == Instruction)
        {
            return GoToObj;
        }
        else
        {
            return IdleRobot;
        }
    }

    States FindObjState(States state)
    {
            /* search for object */
    }

    States GoToObjState(States state)
    {
        /*at obj position and see it -> GrabObj*/
        Robot::Move();
        
        if(ComparePosition(Robot::localPose.x,Robot::wayPoint.x) && ComparePosition(Robot::localPose.y,Robot::wayPoint.y))
        {
            return GrabObj;
        }
        else
        {
            return GoToObj;
        }
    }

    States GrabObjState(States state)
    {
        switch(Robot::subState)
        {
            case IdleClaw:
                Robot::subState = OpenClaw;
                break;

            case OpenClaw:
                /*open the claw*/
                /*Drive forward to pick up obj*/
                Robot::subState = CloseClaw;
                break;

            case CloseClaw:
                /*CloseClaw*/
                Robot::subState = LiftClaw;
                break;

            case LiftClaw:
                /*obj has been grabbed and lifted -> update map*/
                return UpdateMap;
                break;
        }
        return GrabObj;
    }

    States UpdateMapState(States state)
    {
        /*map updated -> GoToFence*/
        if(true)
        {
            return GoToFence;
        }
        else
        {
            return UpdateMap;
        }
    }

    States GoToFenceState(States state)
    {
        /*found a fence spot ->score*/
        if(true)
        {
            return Score;
        }
        else
        {
        }
    }

    States ScoreState(States state)
    {
        switch(Robot::subState)
        {
            case LiftClaw:
                /*lift Claw and approach fence*/
                Robot::subState = OpenClaw;
                break;

            case OpenClaw:
                /*Open claw*/
                Robot::subState = IdleClaw;
                break;

            case IdleClaw:
                /*obj have been dropped -> idle state*/
                /*get distance and low claw again*/
                return IdleRobot;
                break;
        }
        return Score;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////
    void FSM()
    {
        //test movement with random points
        /*while(true)
        {
        Move(rand() % 50 + 20, rand() % 50 + 20);
        Stop();
        Move(0, 0);
        Stop();
        }*/

        //FSM
        States state = Start;
        switch(state)
        {
        case Start:
            state = IdleRobot;
            break;

        case IdleRobot:
            state = IdleRobotState(state);
            break;

        case FindObj:
            state = FindObjState(state);
            break;

        case GoToObj:
            state = GoToObjState(state);
            break;

        case GrabObj:
            state = GrabObjState(state);
            break;

        case UpdateMap:
            state = UpdateMapState(state);
            break;

        case GoToFence:
            state = GoToFenceState(state);
            break;

        case Score:
            state = ScoreState(state);
            break;

        }
    }
