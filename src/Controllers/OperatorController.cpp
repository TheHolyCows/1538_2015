#include "OperatorController.h"

OperatorController::OperatorController(CowControlBoard *controlboard)
	:
	m_CB(controlboard)
{
}

void OperatorController::handle(CowRobot *bot)
{
	//printf("Controlling...\n");
	//bot->DriveSpeedTurn(m_CB->GetDriveStickY(), m_CB->GetSteeringX(), m_CB->GetSteeringButton(FAST_TURN));

	if(m_CB->GetSteeringButton(6))
	{

		bot->GetHorizontalLift()->UpdateSetPoint(-15);

		bot->SetRollerSpeed(1);
	}
	else
	{
		bot->SetRollerSpeed(0);
	}

	bot->DriveSpeedTurn(m_CB->GetDriveStickY(),
						m_CB->GetSteeringX(),
						m_CB->GetSteeringButton(FAST_TURN));

	bot->GetVerticalLift()->UpdateManualSpeeds(m_CB->GetOperatorGamepadAxis(2));
	bot->GetHorizontalLift()->UpdateManualSpeeds(m_CB->GetOperatorGamepadAxis(1));


}

