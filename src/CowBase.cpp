#include "CowBase.h"
#include <string.h>

CowBase::CowBase()
	:
	m_ControlBoard(new CowControlBoard()),
	m_OpController(new OperatorController(m_ControlBoard)),
	m_AutoController(new AutoModeController()),
	m_Constants(CowConstants::GetInstance())
{	
	CowConstants::GetInstance()->RestoreData();
	m_Bot = new CowRobot();

	m_Display = new CowDisplay(m_Bot);

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

void CowBase::DisabledPeriodic()
{
	//m_Bot->GyroHandleCalibration();
	if(m_Display)
	{
		m_Display->DisplayPeriodic();
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
