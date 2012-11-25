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

#include <Arduino.h>

#include <inputchannel.h>
#include <rc_debug_lib.h>
#include <ServoIn.h>
#include <Timer1.h>


namespace rc
{

// Public functions

ServoIn::ServoIn()
:
m_high(true)
{
	
}


void ServoIn::start(bool p_high)
{
	RC_TRACE("start high: %d", p_high);
	m_high = p_high;
	
	// clean buffers
	uint16_t* results = getRawInputChannels();
	for (uint8_t i = 0; i < RC_MAX_CHANNELS; ++i)
	{
		m_pulseStart[i]  = 0;
		m_pulseLength[i] = 0;
		results[i]       = 0;
	}
	
	// start Timer 1
	rc::Timer1::start();
}


void ServoIn::pinChanged(uint8_t p_servo, bool p_high)
{
	// first things first, get Timer 1 count
	uint8_t oldSREG = SREG;
	cli();
	uint16_t cnt = TCNT1;
	SREG = oldSREG;
	
	if (p_high == m_high)
	{
		// start of pulse, cheat half a microsecond so we can detect errors
		m_pulseStart[p_servo] = (cnt == 0) ? 1 : cnt;
	}
	else
	{
		// end of pulse, clear length on error
		m_pulseLength[p_servo] = (m_pulseStart[p_servo] == 0) ? 0 : (cnt - m_pulseStart[p_servo]);
	}
}


void ServoIn::update()
{
	uint16_t* results = getRawInputChannels();
	for (uint8_t i = 0; i < RC_MAX_CHANNELS; ++i)
	{
		results[i] = m_pulseLength[i] >> 1;
	}
}


// namespace end
}
