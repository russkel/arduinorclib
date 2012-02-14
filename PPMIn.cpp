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
#include <util.h>


namespace rc
{

// Public functions

PPMIn::PPMIn(int16_t* p_results, uint16_t* p_work, uint8_t p_maxChannels, bool p_useMicroseconds)
:
m_state(State_Startup),
m_channels(0),
m_results(p_results),
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
					m_newFrame = true;
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
				m_results[i] = microsToNormalized(m_work[i] >> 1);
			}
		}
	}
	else
	{
		return false;
	}
}


// namespace end
}
