#include "OperatorController.h"

OperatorController::OperatorController(CowControlBoard *controlboard)
	:
	m_CB(controlboard),
	setPinchOnce(false)
{
}

void OperatorController::handle(CowRobot *bot)
{
	//printf("Controlling...\n");
	//bot->DriveSpeedTurn(m_CB->GetDriveStickY(), m_CB->GetSteeringX(), m_CB->GetSteeringButton(FAST_TURN));

	bot->GetHorizontalLift()->UpdateSetPoint(0);

	bot->DriveSpeedTurn(m_CB->GetDriveStickY(),
						m_CB->GetSteeringX(),
				 		m_CB->GetSteeringButton(FAST_TURN));


	bot->GetPincher()->ManualControl(m_CB->GetOperatorGamepadAxis(1), m_CB->GetOperatorGamepadAxis(0));

	if(m_CB->GetOperatorButton(2))
	{
		bot->GetVerticalLift()->UpdateSetPoint(CONSTANT("VERTICAL_ONE_TOTE"));
	}
	else if(m_CB->GetOperatorButton(5))
	{
		bot->GetVerticalLift()->UpdateSetPoint(CONSTANT("VERTICAL_TWO_TOTE"));
	}
	else if(m_CB->GetOperatorButton(8))
	{
		bot->GetVerticalLift()->UpdateSetPoint(CONSTANT("VERTICAL_THREE_TOTE"));
	}
	else if(m_CB->GetOperatorButton(4))
	{
		bot->GetVerticalLift()->UpdateSetPoint(CONSTANT("VERTICAL_BASE_TOTE"));
	}

	bot->GetVerticalLift()->UpdateSetPoint(bot->GetVerticalLift()->GetPosition() + m_CB->GetOperatorGamepadAxis(3)*1.5);
	//bot->GetHorizontalLift()->UpdateSetPoint(bot->GetVerticalLift()->GetPosition() + m_CB->GetOperatorGamepadAxis(2)*5.0);
	//bot->GetHorizontalLift()->

	float pincher_position = 0;
	if(m_CB->GetOperatorButton(3))
	{
		bot->GetPincher()->UpdateSetPoint(CONSTANT("PINCHER_OPEN"));
	}
	else if(m_CB->GetOperatorButton(1))
	{
		bot->GetPincher()->UpdateSetPoint(CONSTANT("PINCHER_CAN"));
	}
	else if(m_CB->GetOperatorButton(6))
	{
		bot->GetPincher()->UpdateSetPoint(CONSTANT("PINCHER_TOTE"));
	}
	else if(m_CB->GetOperatorButton(7) && !setPinchOnce)
	{
		bot->GetPincher()->UpdateSetPoint(bot->GetPincher()->GetPosition() + 150);
		setPinchOnce = true;
	}

	if(!m_CB->GetOperatorButton(7))
	{
		setPinchOnce = false;
	}

}

