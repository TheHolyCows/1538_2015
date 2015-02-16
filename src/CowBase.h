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
	void DisplayDiag(bool, CowLib::CowAlphaNum *);
	void DisplayNextState(CowLib::CowAlphaNum *);

	CowRobot *m_Bot;
	CowControlBoard *m_ControlBoard;
	OperatorController *m_OpController;
	AutoModeController *m_AutoController;
	CowConstants *m_Constants;
	uint8_t m_UserState;
	uint32_t m_UserPeriodicCount;
	uint8_t m_UserScrollCount;
	bool m_ButtonPressedOnce;

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

