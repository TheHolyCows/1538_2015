//==================================================
// Copyright (C) 2015 Team 1538 / The Holy Cows
//==================================================

#ifndef __COW_ALPHA_NUM_H__
#define __COW_ALPHA_NUM_H__

#include <stdint.h>
#include <WPILib.h>

namespace CowLib
{
	class CowAlphaNum
	{
	public:
		CowAlphaNum(uint8_t address);
		virtual ~CowAlphaNum();
		void WriteAscii(uint32_t n, uint8_t c);
		void WriteRaw(uint32_t n, uint16_t d);
		void Display();

	private:
		uint16_t m_DisplayBuffer[4];
		uint8_t m_Address;
		uint8_t m_Register;
		I2C *m_I2C;
	};
}

#endif /* __COW_ALPHA_NUM_H__ */
