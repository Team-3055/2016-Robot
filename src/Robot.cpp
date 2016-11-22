#include "WPILib.h"
#include <iostream>
#include "math.h"
using namespace std;

class Robot: public IterativeRobot
{

private:
	//Auto
	int autoLoopCounter = 0;

	//Xbox Controllers
	Joystick *xbox = new Joystick(0);
	Joystick *xbox2 = new Joystick(1);

	//Motor Contollers
	Talon *lDMotor1 = new Talon(0);
	Talon *lDMotor2 = new Talon(1);
	Talon *rDMotor1 = new Talon(2);
	Talon *rDMotor2 = new Talon(3);
	Talon *lLift = new Talon(4);
	Talon *rLift = new Talon(5);
	Talon *Chain = new Talon(6);
	Spark *lShooter = new Spark(7);
	Spark *rShooter = new Spark(8);

	//Encoder
	//Encoder *LiftEnc = new Encoder(0,1, false, Encoder::EncodingType::k4X);

	int MaxHeight = 10;

	//Motor Declarations
	double rDrive, lDrive, lsmotor, rsmotor, chain, llmotor, rlmotor;
	RobotDrive *robotDrive = new RobotDrive(rDMotor1, rDMotor2, lDMotor1, lDMotor2);

	//Camera Decalarations
	string IPTable="10.30.55.5";
	//NetworkTable *CameraTable = new NetworkTable(0);

	//default declarations
	LiveWindow *lw = LiveWindow::GetInstance();
	SendableChooser *chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;


	void RobotInit()
	{
		Encoder *LiftEnc = new Encoder(0,1, false, Encoder::EncodingType::k4X);
		chooser = new SendableChooser();
		chooser->AddDefault(autoNameDefault, (void*)&autoNameDefault);
		chooser->AddObject(autoNameCustom, (void*)&autoNameCustom);
		SmartDashboard::PutData("Auto Modes", chooser);
		//SmartDashboard::GetValue(IPTable);
		LiftEnc->GetPeriod();
		//SmartDashboard::PutNumber("Encoder value", LiftEnc->GetPeriod());
		//SmartDashboard::PutData("Encoder value", LiftEnc);
		//CameraTable->SetIPAddress("10.30.55.2");
		//CameraTable = CameraTable->GetValue("10.30.55.5");
	}


	/**
	 * This autonomous (along with the chooser code above) shows how to select between different autonomous modes
	 * using the dashboard. The sendable chooser code works with the Java SmartDashboard. If you prefer the LabVIEW
	 * Dashboard, remove all of the chooser code and uncomment the GetString line to get the auto name from the text box
	 * below the Gyro
	 *
	 * You can add additional auto modes by adding additional comparisons to the if-else structure below with additional strings.
	 * If using the SendableChooser make sure to add them to the chooser code above as well.
	 */
	void AutonomousInit()
	{
		autoSelected = *((std::string*)chooser->GetSelected());
		std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;

		autoLoopCounter = 0;
	}

	void AutonomousPeriodic()
	{
		if(autoLoopCounter < 500 && autoSelected == autoNameCustom){
			//Custom Auto goes here
			robotDrive->TankDrive(.9,.9);
			autoLoopCounter++;
		} else {
			//Default Auto goes here
			robotDrive->TankDrive(0,0,0,0);
		}
	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		//plsB_better

		 //Tank Drive
		rDrive= xbox->GetRawAxis(1);
		lDrive= xbox->GetRawAxis(5);
		robotDrive->TankDrive(-lDrive, -rDrive);

		 //Chain
		 Chain->Set(xbox2->GetRawAxis(1));

		 //Arm lift
		 /*if(LiftEnc->GetDistance() < MaxHeight){
			 lLift->Set(xbox2->GetRawAxis(5));
		 	 rLift->Set(xbox2->GetRawAxis(5));
		 }else{
			 lLift->Set(0);
			 rLift->Set(0);
		 }*/


		 //button for setting up arm for pull
		 //condition for encoder value set to zero because i need measurements
		 //don't forget measurements corey, just don't.

		 /*
	     if (xbox2->GetRawButton(5) && LiftEnc->GetDistance() < MaxHeight){
			 lLift->Set(-1);
			 rLift->Set(-1);
		 }else{
			 lLift->Set(0);
			 rLift->Set(0);
		 }

		 if (xbox2->GetRawButton(6)){
			 lLift->Set(1);
		 	 rLift->Set(1);
		 }else{
			 lLift->Set(0);
			 rLift->Set(0);
		 }
		 */


		 //Shooter
		 if(xbox2->GetRawButton(1)){
		  	lShooter->Set(-.25);
		 	rShooter->Set(.25);
		 if(xbox2->GetRawButton(2)){
			 lShooter->Set(-.1);
			 rShooter->Set(.1);

		 }
		 }else{
		 	lShooter->Set(0);
		 	rShooter->Set(0);
		 	 }

	}

	 void TestPeriodic()
	 {

		 lw->Run();
	 }
};

START_ROBOT_CLASS(Robot)
