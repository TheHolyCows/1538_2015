//==================================================
// Copyright (C) 2015 Team 1538 / The Holy Cows
//==================================================

#ifndef __PINCHER_H__
#define __PINCHER_H__

#include <WPILib.h>

class Pincher
{
public:
	Pincher(unsigned int intakeA,
			unsigned int intakeB,
			unsigned int extendMotorA,
			unsigned int extendMotorB);
	virtual ~Pincher();
	void handle();
	void UpdateSetPoint();
	float GetPosition();

private:
	CANTalon *m_IntakeA;
	CANTalon *m_IntakeB;
	CANTalon *m_ExtendMotorA;
	CANTalon *m_ExtendMotorB;
	Encoder *m_Encoder;
};

#endif /* __PINCHER_H__ */
