//==================================================
// Copyright (C) 2015 Team 1538 / The Holy Cows
//==================================================

#ifndef __COW_ROBOT_H__
#define __COW_ROBOT_H__

#include <WPILib.h>
#include "Controllers/GenericController.h"
#include "Subsystems/Pincher.h"
#include "Subsystems/Spool.h"
#include "CowLib/CowLib.h"
#include "CowControlBoard.h"
#include "CounterBase.h"
#include "CowConstants.h"
#include "CowLib/CowAlphaNum.h"


class CowRobot
{
public:
private:
	int m_DSUpdateCount;
	
	GenericController *m_Controller;
	
	// Drive Motors
	CANTalon *m_LeftDriveA;
	CANTalon *m_LeftDriveB;
	CANTalon *m_LeftDriveC;

	CANTalon *m_RightDriveA;
	CANTalon *m_RightDriveB;
	CANTalon *m_RightDriveC;

	Talon *m_Roller;
	
	Gyro *m_Gyro;
	Encoder *m_DriveEncoder;
	
	Pincher *m_Pincher;
	Spool *m_VerticalLift;
	Spool *m_HorizontalLift;

	CowLib::CowAlphaNum *m_LEDDisplay;

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
	void SetController(GenericController *controller);
	void PrintToDS();
	double GetDriveDistance();
	bool DriveDistanceWithHeading(double heading, double distance);
	bool DriveWithHeading(double heading, double speed);
	void DriveSpeedTurn(float speed, float turn, bool quickTurn);
	void DriveLeftRight(float leftDriveValue, float rightDriveValue);
	void QuickTurn(float turn);
	
	void SetRollerSpeed(float val);

	CowLib::CowAlphaNum *GetDisplay()
	{
		return m_LEDDisplay;
	}

	Gyro *GetGyro()
	{
		return m_Gyro;
	}

	Encoder *GetEncoder()
	{
		return m_DriveEncoder;
	}

	Spool *GetVerticalLift()
	{
		return m_VerticalLift;
	}

	Spool *GetHorizontalLift()
	{
		return m_HorizontalLift;
	}

	void handle();
};

#endif
