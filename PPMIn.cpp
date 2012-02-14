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

PPMIn::PPMIn(uint16_t* p_work, uint8_t p_maxChannels, bool p_useMicroseconds)
:
m_state(State_Startup),
m_channels(0),
m_center(1520),
m_range(600),
m_work(p_work),
m_maxChannels(p_maxChannels),
m_idx(0),
m_useMicroseconds(p_useMicroseconds),
m_newFrame(false),
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
	if (p_high)
	{
		// only interested in signal going low
		return;
	}
	
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
				m_newFrame = true;
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


bool PPMIn::update()
{
	if (m_newFrame)
	{
		m_newFrame = false;
		if (m_useMicroseconds)
		{
			for (uint8_t i = 0; i < m_channels && i < m_maxChannels; ++i)
			{
				m_results[i] = m_work[i] >> 1;
			}
		}
		else
		{
			for (uint8_t i = 0; i < m_channels && i < m_maxChannels; ++i)
			{
				m_results[i] = ticksToNormalized(m_work[i]);
			}
		}
	}
	else
	{
		return false;
	}
}


// Private functions

int16_t PPMIn::ticksToNormalized(uint16_t p_ticks) const
{
	// first we clip values, early abort.
	if (p_tick >= m_center + m_travel)
	{
		return 256;
	}
	else if (p_tick <= m_center - m_travel)
	{
		return -256;
	}
	
	// get the absolute delta ABS(p_tick - m_center)
	uint16_t delta = (p_tick > m_center) ? (p_ticks - m_center) : (m_center - p_ticks);
	
	// we need to multiply by end range 256 and divide by start range m_travel
	// and we need to do this without risking overflows...
	
	// The max value in delta will be m_range, about 2000. This gives us 5 bits of room to play with
	// So instead of multiplying with 256 and dividing by m_travel,
	// we multiply by 32 and divide by m_travel / 8
	// we lose the last three bits of the division, but that's not going to make much of a difference...
	// the least significant bit of m_travel is 0 anyway, so the actual loss is just 2 bits.
	delta <<= 5;
	delta /= (m_travel >> 3);
	
	return (p_ticks >= m_center) ? delta : -delta;
}


// namespace end
}
