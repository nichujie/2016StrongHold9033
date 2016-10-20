#include "Robot.h"
float SpeedGear=0.8f;
//static bool rotate=true;
//robotdrv:
// constructor
Robot::Robot() : 	// member initializations (constructor)
	robotdrv(0,1,2,3),
	motor4(4),		//robot arm
	noid1(0),		//Solenoid
	driveCtl(0),	//Logitech controllers
	airPump(0)      //compressor
	{
		try {
				ahrs = new AHRS(SPI::Port::kMXP);
	        } catch (std::exception &ex ) {
	            std::string err_string = "Error instantiating navX MXP:  ";
	            err_string += ex.what();
	            //DriverStation::ReportError(err_string.c_str());
	        }
	robotdrv.SetExpiration(0.1);
	}

// on startup
void Robot::RobotInit()  {
	//setup the auto-chooser:
	ahrs->Reset();
	noid1.Set(false);
	airPump.SetClosedLoopControl(true);
	//chooser->AddDefault(autoStopAtObstacle, (void*) &autoStopAtObstacle);
	//chooser->AddObject(autoLowBar, (void*) &autoLowBar);
	//chooser->AddObject(autoSeeSaws, (void*) &autoSeeSaws);
	//SmartDashboard::PutData("Auto Modes", chooser);
	//CameraServer::GetInstance()->SetSize(0);
	//get camera feed and post it to the smartdashboard

	std::cout <<"Hello world!\n" <<std::endl;
}


/**Notes on autonomous chooing code:
 * This autonomous (along with the chooser code above) shows how to select between different autonomous modes
 * using the dashboard. The sendable chooser code works with the Java SmartDashboard. If you prefer the LabVIEW
 * Dashboard, remove all of the chooser code and uncomment the GetString line to get the auto name from the text box
 * below the Gyro
 *
 * You can add additional auto modes by adding additional comparisons to the if-else structure below with additional strings.
 * If using the SendableChooser make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit(){
	noid1.Set(false);
	airPump.SetClosedLoopControl(true);
	robotdrv.SetSafetyEnabled(false);
	//motor4.SetSpeed(-0.3f);
	//Wait(3.5f);
	robotdrv.Drive(-0.5f,0);
	Wait(4.0f);
	//robotdrv.Drive(-0.5f,0);
	//Wait(1);
	//robotdrv.Drive(-0.6f,0);
	//Wait(1.5f);
	//robotdrv.TankDrive(0.5f,-0.5f);
	/*while(rotate && ahrs->GetAngle()<60.0f){
		robotdrv.TankDrive(-0.5f,0.5f);
	}*/
	//Wait(0.8f);
	//motor4.SetSpeed(0.3f);
	//Wait(3.0f);
	//noid1.Set(true);		//Shoot the ball
	robotdrv.Drive(0,0);
	//noid1.Set(false);

}

void Robot::AutonomousPeriodic(){
	/* requires ultrasonic sensor :(
	if (autoSelected == autoLowBar) {}
	else if (autoSelected == autoSeeSaws) {}
	else { // default autonomous code
		// drive forward and stop 3 feet in front of the vertical obstacle.
		// the robot and field are built in inches, so it's probably best not to use metric =(
		if (sonar.GetRangeInches() > STOPPING_DISTANCE_INCHES)
			myRobot.Drive(-0.3f, 0);
		else myRobot.Drive(-0.5f, 0);
	} */
	//SmartDashboard::PutNumber("Angle:",ahrs->GetAngle());
}


void Robot::TeleopInit(){
	airPump.SetClosedLoopControl(true);
	noid1.Set(false);
	//tele-op has started.
	std::cout <<"\nTeleop has started - Awaiting your command\n";
	robotdrv.SetSafetyEnabled(false);
}

void Robot::TeleopPeriodic(){
	//rotate=false;
	//drive the robot
	robotdrv.TankDrive(SpeedGear*driveCtl.GetRawAxis(3),SpeedGear*driveCtl.GetRawAxis(1));
	//Shoot the ball
	if(airPump.GetPressureSwitchValue()==1) SmartDashboard::PutString("Shoot:","able");
	else SmartDashboard::PutString("Shoot:","unable");
	static bool state = true;
	// print "Shoot!!" to the console when we shoot (for good luck)
	if ( state && (driveCtl.GetRawButton(1))) {
		//std::cout <<"Shoot!!" <<std::endl;
		state = false;
		noid1.Set(true);
	} else {
		noid1.Set(false);
		state=true;
	}
	//static bool motorstate=false;
	//if(driveCtl.GetRawButton(4)&&motorstate==false){ motor4.Set(0.6f); Wait(0.2f); motor4.StopMotor(); motorstate=true; }
	//else if(driveCtl.GetRawButton(2)&&motorstate==true){ motor4.Set(-0.6f); Wait(0.2f); motor4.StopMotor(); motorstate=false; }
	if(driveCtl.GetRawButton(5)) motor4.SetSpeed(0.3f);
	else if(driveCtl.GetRawButton(6)) motor4.SetSpeed(-0.3f);
	else motor4.SetSpeed(0);
	//motor4.Set(-0.3f*driveCtl.GetRawButton(2));
	 SmartDashboard::PutNumber("Angle:",ahrs->GetAngle());
//	 SmartDashboard::PutNumber("POV:",driveCtl.GetPOV());
//	std::cout<<"Raw Count:"<<enc->Get()<<"   "<<enc->GetRaw()<<"\n";
//	std::cout<<"Rate:"<<enc->GetRate()<<"\n";
			Wait(0.005);
}

// make it happen (macro defined in WPILib.h)
START_ROBOT_CLASS(Robot)
