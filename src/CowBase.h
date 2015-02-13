//==================================================
// Copyright (C) 2015 Team 1538 / The Holy Cows
//==================================================

#ifndef __COW_BASE_H__
#define __COW_BASE_H__

#include <WPILib.h>
#include "CowControlBoard.h"
#include "Controllers/OperatorController.h"
#include "Controllers/AutoModeController.h"
#include "Autonomous/AutoModes.h"
#include "CowLib/CowLib.h"
#include "CowConstants.h"

class CowBase : public IterativeRobot
{
private:
	CowRobot *m_Bot;
	CowControlBoard *m_ControlBoard;
	OperatorController *m_OpController;
	AutoModeController *m_AutoController;
	CowConstants *m_Constants;
	uint32_t m_PeriodicCount;
	uint8_t m_ScrollCount;
	uint8_t m_Banner[25];
public:
	CowBase();
	void RobotInit();
	void DisabledInit();
	void AutonomousInit();
	void TeleopInit();
	void DisabledContinuous();
	void AutonomousContinuous();
	void TeleopContinuous();
	void DisabledPeriodic();
	void AutonomousPeriodic();
	void TeleopPeriodic();
};

#endif

