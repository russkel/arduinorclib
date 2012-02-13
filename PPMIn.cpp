/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** PPMIn.cpp
** Pulse Position Modulation Input functionality
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

#include <PPMIn.h>


namespace rc
{

// Public functions

PPMIn::PPMIn(uint16_t* p_work, uint8_t p_maxChannels)
:
m_state(State_Startup),
m_channels(0),
m_work(p_work),
m_maxChannels(p_maxChannels),
m_idx(0),
m_lastTime(0)
{
	// check if Timer 1 is running or not
	if ((TCCR1B & ((1 << CS12) | (1 << CS11) | (1 << CS10))) == 0)
	{
		// start Timer 1
		TCCR1B |= (1 << CS11);
	}
}


bool PPMIn::isStable() const
{
	return m_state == State_Stable;
}


uint8_t PPMIn::getChannels() const
{
	return m_channels;
}


void PPMIn::setCenter(uint16_t p_center)
{
	m_center = p_center << 1;
}


uint16_t PPMIn::getCenter() const
{
	return m_center >> 1;
}


void PPMIn::setTravel(uint16_t p_travel)
{
	m_travel = p_travel << 1;
}


uint16_t PPMIn::getTravel() const
{
	return m_travel >> 1;
}


void PPMIn::loadFutaba()
{
	setCenter(1520);
	setTravel(600);
}


void PPMIn::loadJR()
{
	setCenter(1500);
	setTravel(600);
}


void PPMIn::pinChanged(bool p_high)
{
	if (p_high/* == false*/)
	{
		// only interested in signal going high
		return;
	}
	
	// first things firs, get Timer 1 count
	uint8_t oldSREG = SREG;
	cli();
	uint16_t cnt = TCNT1;
	SREG = oldSREG;
	
	switch (m_state)
	{
	default:
	case State_Startup:
		{
			if (cnt - m_lastTime > 15000)
			{
				m_state = State_Listening;
				m_channels = 0;
			}
		}
		break;
	
	case State_Listening:
		{
			if (cnt - m_lastTime > 15000)
			{
				m_state = State_Stable;
				m_idx = 0;
			}
			else
			{
				if (m_channels < m_maxChannels)
				{
					m_work[m_channels] = cnt - m_lastTime;
				}
				++m_channels;
			}
		}
		break;
	
	case State_Stable:
		{
			if (cnt - m_lastTime > 15000)
			{
				if (m_idx == m_channels)
				{
					m_idx = 0;
				}
				else
				{
					m_state = State_Confused;
				}
			}
			else
			{
				if (m_idx < m_maxChannels)
				{
					m_work[m_idx] = cnt - m_lastTime;
				}
				++m_idx;
			}
		}
		break;
	}
	m_lastTime = cnt;
}


// Private functions


// namespace end
}
