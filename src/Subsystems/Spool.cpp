#include "Spool.h"
#include <iostream>
#include "../CowConstants.h"


Spool::Spool(std::string name, uint8_t motorAID, uint8_t motorBID, uint8_t encA, uint8_t encB)
	:
	m_Name(name),
	m_MotorA(new CANTalon(motorAID)),
	m_MotorB(new CANTalon(motorBID)),
	m_Encoder(new Encoder(encA, encB, true, Encoder::k1X)),
	m_PIDEnabled(true),
	m_PIDOutput(0),
	m_PID_P(0),
	m_PID_D(0),
	m_PID_P_Previous(0),
	m_ManualSpeed(0)
{
	m_Encoder->SetDistancePerPulse(0.01745327777778);
}

Spool::Spool(std::string name, uint8_t motorAID, uint8_t encA, uint8_t encB)
	:
	m_Name(name),
	m_MotorA(new CANTalon(motorAID)),
	m_MotorB(NULL),
	m_Encoder(new Encoder(encA, encB, true, Encoder::k1X)),
	m_PIDEnabled(true),
	m_PIDOutput(0),
	m_PID_P(0),
	m_PID_D(0),
	m_PID_P_Previous(0),
	m_ManualSpeed(0)
{
	m_Encoder->SetDistancePerPulse(0.01745327777778);
}

Spool::~Spool()
{
	if(m_MotorA)
	{
		delete m_MotorA;
	}

	if(m_MotorB)
	{
		delete m_MotorB;
	}

	if(m_Encoder)
	{
		delete m_Encoder;
	}
}

void Spool::handle()
{
	std::string PID_P_CONSTANT = m_Name + "_PID_P";
	std::string PID_D_CONSTANT = m_Name + "_PID_D";


	m_PID_P = m_SetPoint - m_Encoder->GetDistance();
	m_PID_D = m_PID_P - m_PID_P_Previous;
	m_PIDOutput = (m_PID_P * CONSTANT(PID_P_CONSTANT.c_str()) + (m_PID_D * CONSTANT(PID_D_CONSTANT.c_str())));
	m_PIDOutput = -m_PIDOutput;
	m_PID_P_Previous = m_PID_P;
	std::cout << "sp: " << m_SetPoint << " pv: " << m_Encoder->GetDistance() << std::endl;
	if(m_PIDEnabled)
	{
		//Todo: Write PID shit
		m_MotorA->Set(m_PIDOutput);

		if(m_MotorB)
		{
			m_MotorB->Set(m_PIDOutput);
		}
	}
	else
	{
		m_MotorA->Set(m_ManualSpeed);
		if(m_MotorB)
		{
			m_MotorB->Set(m_ManualSpeed);
//			std::cout << m_Name
//					  << " c:"
//					  << m_MotorA->GetOutputCurrent()
//					  << ", "
//					  << m_MotorB->GetOutputCurrent()
//					  << ", enc: "
//					  << m_Encoder->GetDistance()
//					  << std::endl;
		}
		else
		{
//			std::cout << m_Name
//					  << " c:"
//					  << m_MotorA->GetOutputCurrent()
//					  << ", enc: "
//					  << m_Encoder->GetDistance()
//					  << std::endl;
		}


	}
}

void Spool::UpdateSetPoint(float setpoint)
{
	m_SetPoint = setpoint;
}

void Spool::UpdateManualSpeeds(float speeds)
{
	m_ManualSpeed = speeds;
}

void Spool::EnablePID()
{
	m_PIDEnabled = true;
}

void Spool::DisablePID()
{
	m_PIDEnabled = false;
}

float Spool::GetPosition()
{
	return 0;
}
