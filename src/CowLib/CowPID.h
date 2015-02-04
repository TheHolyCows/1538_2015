//==================================================
// Copyright (C) 2015 Team 1538 / The Holy Cows
//==================================================

#ifndef __COW_PID_H__
#define __COW_PID_H__

namespace CowLib
{
	class CowPID
	{
	public:
		CowPID();
		virtual ~CowPID();
		void UpdatePV(float pv);
		void UpdateSP(float sp);
		void Update();

	private:
		float m_PV;
		float m_SP;
	};
}

#endif /* __COW_PID_H__ */
