//==================================================
// Copyright (C) 2014 Team 1538 / The Holy Cows
//==================================================

#ifndef __COW_ROBOT_H__
#define __COW_ROBOT_H__


#include <WPILib.h>
#include "Controllers/GenericController.h"
//#include "Subsystems/Intake.h"
//#include "Subsystems/Winch.h"
#include "CowLib/CowLib.h"
#include "CowControlBoard.h"
#include "CounterBase.h"
#include "CowConstants.h"

class CowRobot
{
public:
private:
	int m_DSUpdateCount;
	
	GenericController* m_Controller;
	
	// Drive Motors
	Talon *m_RightDrive;
	Talon *m_LeftDrive;
	
	//CowLib::CowGyro* m_Gyro;
	Encoder* m_DriveEncoder;
	
	float m_LeftDriveValue;
	float m_RightDriveValue;

	double m_PreviousGyroError;
	double m_PreviousDriveError;
		
	void SetLeftMotors(float val);
	void SetRightMotors(float val);
public:
	CowRobot();
	void Reset();
	void GyroHandleCalibration();
	void GyroFinalizeCalibration();
	void SetController(GenericController* controller);
	void PrintToDS();
	double GetDriveDistance();
	bool DriveDistanceWithHeading(double heading, double distance);
	bool DriveWithHeading(double heading, double speed);
	void DriveSpeedTurn(float speed, float turn, bool quickTurn);
	void DriveLeftRight(float leftDriveValue, float rightDriveValue);
	void QuickTurn(float turn);
	
	void handle();
};

#endif
