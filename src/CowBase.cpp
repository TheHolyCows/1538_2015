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

void CowBase::DisplayUpdateState(CowLib::CowAlphaNum *display)
{
	switch (m_UserState)
	{
	case 0 :
		if (m_PrevUserState != m_UserState)
		{
			m_PrevUserState = m_UserState;
			m_UserScrollCount = 0;
			display->SetBanner("Team 1538 The Holy Cows ");
		}
		else
		{
			m_UserScrollCount++;
		}
		display->SetBannerPosition(m_UserScrollCount);
		display->DisplayBanner();
		break;
	case 1 :
		m_UserScrollCount = 0; // not scrolling the voltage
		if (m_PrevUserState != m_UserState)
		{
			m_PrevUserState = m_UserState;
			display->SetBanner("Volt");
		}
		else
		{
			if (m_UserStatePeriodicCount == 50)
			{
				PowerDistributionPanel *pdp = m_Bot->GetPowerDistributionPanel();
				if (pdp)
				{
					char volt[64];
					sprintf(volt, "%.1fv ", pdp->GetVoltage());
					std::string msg(volt);
					msg = msg + " ";
					display->SetBanner(msg);
				}
				else
				{
					display->SetBanner("?");
				}
			}
		}
		display->SetBannerPosition(m_UserScrollCount);
		display->DisplayBanner();
		break;
	case 2 :
		m_UserScrollCount = 0; // not scrolling the voltage
		if (m_PrevUserState != m_UserState)
		{
			m_PrevUserState = m_UserState;
			display->SetBanner("Mode");
		}
		else
		{
			if (m_UserStatePeriodicCount == 50)
			{
				display->SetBanner("?   ");
			}
		}
		display->SetBannerPosition(m_UserScrollCount);
		display->DisplayBanner();
		break;
	default :
		break;
	}
}

void CowBase::DisplayNextState(CowLib::CowAlphaNum *display)
{
	switch (m_UserState)
	{
	case 0 :
		m_PrevUserState = 0;
		m_UserState = 1;
		break;
	case 1 :
		m_PrevUserState = 1;
		m_UserState = 2;
		break;
	case 2 :
		m_PrevUserState = 2;
		m_UserState = 0;
		break;
	default :
		break;
	}
}

void CowBase::DisplayState(bool user, CowLib::CowAlphaNum *display)
{
	m_UserPeriodicCount++;
	m_UserStatePeriodicCount++;

	if (user)
	{
		m_UserStatePeriodicCount = 0;
		DisplayNextState(display);
		DisplayUpdateState(display);
	}
	else
	{
		if ((m_UserState == 0) && ((m_UserStatePeriodicCount % 10) == 0))
		{
			DisplayUpdateState(display);
		}
		else if ((m_UserStatePeriodicCount % 300) == 0)
		{
			m_UserStatePeriodicCount = 0;
			DisplayNextState(display);
			DisplayUpdateState(display);
		}
		else if ((m_UserStatePeriodicCount % 10) == 0)
		{
			DisplayUpdateState(display);
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
		DisplayState(buttonValue, m_Bot->GetDisplay());
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
