#include "AutoModes.h"

AutoModes *AutoModes::m_SingletonInstance = NULL;

AutoModes *AutoModes::GetInstance()
{
	if(m_SingletonInstance == NULL)
	{
		m_SingletonInstance = new AutoModes();
	}
	return m_SingletonInstance;
}

AutoModes::AutoModes()
{	
	// Set up our selection order
	m_Modes["Default"];
	m_Modes["Default"].push_back(RobotCommand(CMD_WAIT, 0, 0, 1.5));
	m_Modes["Default"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 100, 0, 1.5));
	m_Modes["Default"].push_back(RobotCommand(CMD_WAIT, 0, 0, 5));
	m_Modes["Default"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 100, 0, 1000));

	m_Iterator = m_Modes.begin();
}

std::deque<RobotCommand> AutoModes::GetCommandList()
{
	return m_Iterator->second;
}

const char *AutoModes::GetName()
{
	return m_Iterator->first;
}

void AutoModes::NextMode()
{
	m_Iterator++;
	if(m_Iterator == m_Modes.end())
	{
		m_Iterator = m_Modes.begin();
	}
}
