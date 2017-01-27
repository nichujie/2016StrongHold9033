#ifndef ROBOT_H
#define ROBOT_H
#include <inttypes.h> // constant width integers (ie- int8_t)
#include "WPILib.h" // robot stuff
#include <AHRS.h>

class Robot: public IterativeRobot {

public:
    Robot(); 

public:
	//robot parts:
   	RobotDrive robotdrv;
  	VictorSP motor4;
	Solenoid noid1;
	Joystick driveCtl;
	Compressor airPump; // compressor
	AHRS *ahrs;
	//Encoder *enc;	
	
	// functions inherited from the IterativeRobot base-class:
	void RobotInit(); //run once on startup

	void AutonomousInit();
	void AutonomousPeriodic();

	void TeleopInit();
	void TeleopPeriodic();

	
	void TestInit()
		{ std::cout <<"Testing mode enabled...\nCurrently doing: (NULL)" <<std::endl; }
	void TestPeriodic()
		{  }

	void DisabledInit()
		{ std::cout <<"Disabled" <<std::endl; }

	
};


#endif
