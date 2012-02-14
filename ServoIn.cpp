/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ServoIn.cpp
** Servo Signal Input functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
#else
	#include <avr/interrupt.h>
	#include <wiring.h>
#endif

#include <ServoIn.h>
#include <util.h>


namespace rc
{

// Public functions

ServoIn::ServoIn()
:
m_state(State_Startup),
m_ticks(1520),
m_lastTime(0)
{
	// check if Timer 1 is running or not
	if ((TCCR1B & ((1 << CS12) | (1 << CS11) | (1 << CS10))) == 0)
	{
		// start Timer 1
		TCCR1B |= (1 << CS11);
	}
}


bool ServoIn::isStable() const
{
	return m_state == State_Stable;
}


void ServoIn::pinChanged(bool p_high)
{
	// first things first, get Timer 1 count
	uint8_t oldSREG = SREG;
	cli();
	uint16_t cnt = TCNT1;
	SREG = oldSREG;
	
	switch (m_state)
	{
	default:
	case State_Startup:
		{
			if (p_high)
			{
				m_state = State_Listening;
			}
		}
		break;
	
	case State_Listening:
		{
			if (p_low)
			{
				if (cnt - m_lastTime >= 6000)
				{
					m_state = State_Confused;
				}
				else
				{
					m_ticks = cnt - m_lastTime;
					m_state = State_Stable;
				}
			}
		}
		break;
	
	case State_Stable:
		{
			if (p_high)
			{
				if (cnt - m_lastTime > 30000)
				{
					m_state = State_Confused;
				}
			}
			else
			{
				if (cnt - m_lastTime >= 6000)
				{
					m_state = State_Confused;
				}
				else
				{
					m_ticks = cnt - m_lastTime;
				}
			}
		}
		break;
	}
	m_lastTime = cnt;
}


int16_t ServoIn::getValue(bool p_useMicroseconds)
{
	if (p_useMicroseconds)
	{
		return m_ticks >> 1;
	}
	else
	{
		return microsToNormalized(m_ticks >> 1);
	}
}


// namespace end
}
