#include "CowBase.h"
#include <string.h>

CowBase::CowBase()
	:
	m_ControlBoard(new CowControlBoard()),
	m_OpController(new OperatorController(m_ControlBoard)),
	m_AutoController(new AutoModeController()),
	m_Constants(CowConstants::GetInstance()),
	m_PeriodicCount(0),
	m_ScrollCount(0)
{	
	CowConstants::GetInstance()->RestoreData();
	m_Bot = new CowRobot();
	const char *banner = "Team 1538 The Holy Cows";

	//SetPeriod(HZ(ROBOT_HZ));
	//GetWatchdog().SetEnabled(false);
	printf("Done constructing CowBase!\n");

	strcpy((char *)m_Banner, banner);
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

void CowBase::DisabledPeriodic()
{
	//m_Bot->GyroHandleCalibration();
	m_PeriodicCount++;
	if(m_Bot->GetDisplay())
	{
		if((m_PeriodicCount % 10) == 0)
		{
			m_ScrollCount++;

			m_Bot->GetDisplay()->WriteAscii(0, m_Banner[(m_ScrollCount)%24]);
			m_Bot->GetDisplay()->WriteAscii(1, m_Banner[(m_ScrollCount+1)%24]);
			m_Bot->GetDisplay()->WriteAscii(2, m_Banner[(m_ScrollCount+2)%24]);
			m_Bot->GetDisplay()->WriteAscii(3, m_Banner[(m_ScrollCount+3)%24]);
			m_Bot->GetDisplay()->Display();
//			if (m_ScrollCount == '~')
//			{
//				m_ScrollCount = '!';
//			}
		}
	}


//	if(m_ControlBoard->GetAutoSelectButton())
//	{
//		if(m_ControlBoard->GetDriveButton(3))
//		{
//			m_Bot->Reset();
//			m_Constants->RestoreData();
//			AutoModes::GetInstance()->NextMode();
//		}
////		else
////		{
////			m_Bot->GyroFinalizeCalibration();
////		}
//	}
	
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
