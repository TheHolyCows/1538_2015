#include "CowBase.h"
#include <string.h>

CowBase::CowBase()
	:
	m_ControlBoard(new CowControlBoard()),
	m_OpController(new OperatorController(m_ControlBoard)),
	m_AutoController(new AutoModeController()),
	m_Constants(CowConstants::GetInstance()),
	m_UserState(0),
	m_UserPeriodicCount(0),
	m_UserScrollCount(0),
	m_ButtonPressedOnce(false)
{	
	CowConstants::GetInstance()->RestoreData();
	m_Bot = new CowRobot();

	//SetPeriod(HZ(ROBOT_HZ));
	//GetWatchdog().SetEnabled(false);
	printf("Done constructing CowBase!\n");
}

void CowBase::RobotInit()
{
}

void CowBase::DisabledInit()
{
	CowConstants::GetInstance()->RestoreData();
}

void CowBase::AutonomousInit()
{
	//m_Bot->GyroFinalizeCalibration();
	
	m_AutoController->SetCommandList(AutoModes::GetInstance()->GetCommandList());
	m_Bot->SetController(m_AutoController);
	m_Bot->Reset();
}
void CowBase::TeleopInit()
{
	//m_Bot->GyroFinalizeCalibration();

	m_Bot->SetController(m_OpController);
	m_Bot->Reset();
	//m_Bot->SetWinchState(m_WinchState);
	//m_WinchState = Winch::READY_TO_FIRE;
}

void CowBase::DisabledContinuous()
{
	//taskDelay(WAIT_FOREVER);
}

void CowBase::AutonomousContinuous()
{
	//taskDelay(WAIT_FOREVER);
}

void CowBase::TeleopContinuous()
{
	//taskDelay(WAIT_FOREVER);
}

void CowBase::DisplayNextState(CowLib::CowAlphaNum *display)
{
	if (m_UserState == 0)
	{
		m_UserState = 1;
		display->SetBanner("Mode 1.0 ");
	}
	else if (m_UserState == 1)
	{
		m_UserState = 2;
		display->SetBanner("Mode 2.0 ");
	}
	else if (m_UserState == 2)
	{
		m_UserState = 3;
		display->SetBanner("Mode 3.0 ");
	}
	else if (m_UserState == 3)
	{
		m_UserState = 0;
		display->SetBanner("Team 1538 The Holy Cows ");
	}

	m_UserScrollCount = 0;
	display->SetBannerPosition(m_UserScrollCount);
	display->DisplayBanner();
}

void CowBase::DisplayDiag(bool user, CowLib::CowAlphaNum *display)
{
	m_UserPeriodicCount++;

	if (user)
	{
		DisplayNextState(display);
	}
	else if (m_UserState == 0)
	{
		if ((m_UserPeriodicCount % 10) == 0)
		{
			m_UserScrollCount++;
			display->SetBanner("Team 1538 The Holy Cows ");
			display->SetBannerPosition(m_UserScrollCount);
			display->DisplayBanner();
		}
	}
	else
	{
		if ((m_UserPeriodicCount % 300) == 0)
		{
			DisplayNextState(display);
		}
		else if ((m_UserPeriodicCount % 10) == 0)
		{
			m_UserScrollCount++;
			display->SetBannerPosition(m_UserScrollCount);
			display->DisplayBanner();
		}
	}
}

void CowBase::DisabledPeriodic()
{
	//m_Bot->GyroHandleCalibration();

	bool userButtonPressed = GetUserButton();
	bool buttonValue = false;

	if (userButtonPressed && !m_ButtonPressedOnce)
	{
		buttonValue = true;
		m_ButtonPressedOnce = true;
	}
	else if(!userButtonPressed && m_ButtonPressedOnce)
	{
		m_ButtonPressedOnce = false;
	}

	if (m_Bot->GetDisplay())
	{
		DisplayDiag(buttonValue, m_Bot->GetDisplay());
	}

	if(m_ControlBoard->GetAutoSelectButton())
	{
		m_Constants->RestoreData();

//		if(m_ControlBoard->GetDriveButton(0))
//		{
//			//m_Bot->Reset();
//			//AutoModes::GetInstance()->NextMode();
//		}
//		else
//		{
//			m_Bot->GyroFinalizeCalibration();
//		}
	}
	
//	m_Bot->PrintToDS();
}
void CowBase::AutonomousPeriodic()
{
//	m_Bot->DriveLeftRight(1, 1);
//	m_Bot->PrintToDS();
	m_Bot->handle();
}
void CowBase::TeleopPeriodic()
{
//	if(m_ControlBoard->GetAutoSelectButton())
//	{
//		m_Bot->Reset();
//		m_Constants->RestoreData();
//	}
//
//	m_Bot->PrintToDS();
	m_Bot->handle();
	//exit(1);
}

START_ROBOT_CLASS(CowBase);
