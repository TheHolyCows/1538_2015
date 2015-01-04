#include "AutoModeController.h"

AutoModeController::AutoModeController()
	:
	m_Timer(new Timer()),
	m_CurrentCommand(RobotCommand()),
	m_Fired(false),
	m_SmartLoaded(false),
	m_ChangedSetpoint(false)
{
	m_Timer->Start();
	reset();
}

void AutoModeController::SetCommandList(deque<RobotCommand> list)
{
	m_CommandList = list;
}

void AutoModeController::reset()
{
	//CowConstants * rc = CowConstants::GetInstance();
	//bot->GetGyro()->Reset();
	//bot->GetEncoder()->Reset();

	//m_CommandList.clear();
	//m_CurrentCommand = RobotCommand();
}


void AutoModeController::handle(CowRobot* bot)
{
	bool result = false;
	
	// Run the command
	switch(m_CurrentCommand.m_Command)
	{
		case CMD_NULL:
		{
			doNothing(bot);
			
			result = true;
			break;
		}
		case CMD_WAIT:
		{
			bot->DriveWithHeading(m_CurrentCommand.m_Heading, 0);
			doNothing(bot);
			break;
		}
		case CMD_TURN:
		{
			result = bot->DriveWithHeading(m_CurrentCommand.m_Heading, 0);
			break;
		}
		case CMD_DRIVE_DISTANCE:
		{
			result = bot->DriveDistanceWithHeading(m_CurrentCommand.m_Heading, m_CurrentCommand.m_EncoderCount);
			break;
		}
		default:
		{
			doNothing(bot);
			result = true;
			break;
		}
	}
	
	// Check if this command is done
	if(result == true || m_CurrentCommand.m_Command == CMD_NULL || m_Timer->Get() > m_CurrentCommand.m_Timeout)
	{
		if(m_CurrentCommand.m_Command == CMD_DETECT_HOT && m_Timer->Get() > m_CurrentCommand.m_Timeout)
		{
			m_CommandList = *(m_CurrentCommand.m_HotGoalLeftCommandList);
		}
		// This command is done, go get the next one
		if(m_CommandList.size() > 0 )
		{			
			m_CurrentCommand = m_CommandList.front();
			m_CommandList.pop_front();
			
			if(!m_CurrentCommand.m_Command == CMD_NULL)
				printf("Time elapsed: %f\n", m_Timer->Get());
						
			m_Fired = false;
			m_SmartLoaded = false;
			m_ChangedSetpoint = false;
		}
		else
		{
			//we're done clean up
			m_CurrentCommand = RobotCommand();
		}
		m_Timer->Reset();
	}
}

// Drive Functions
void AutoModeController::doNothing(CowRobot* bot)
{
	bot->DriveLeftRight(0, 0);
}
