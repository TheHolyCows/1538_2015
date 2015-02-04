//==================================================
// Copyright (C) 2015 Team 1538 / The Holy Cows
//==================================================

#ifndef __SPOOL_H__
#define __SPOOL_H__

#include <WPILib.h>

class Spool
{
public:
	Spool();
	virtual ~Spool();
	void handle();
	void UpdateSetPoint();
	float GetPosition();

private:
	CANTalon *m_MotorA;
	CANTalon *m_MotorB;
	Encoder *m_Encoder;
};

#endif /* __SPOOL_H__ */
