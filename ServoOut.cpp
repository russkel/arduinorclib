/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ServoOut.cpp
** Servo Signal Output functionality
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
#include <pins_arduino.h>

#include <ServoOut.h>


// Interrupt service routine
ISR(TIMER1_COMPB_vect)
{
	rc::ServoOut::handleInterrupt();
}



namespace rc
{

ServoOut* ServoOut::s_instance = 0;


// Public functions

ServoOut::ServoOut(const uint8_t* p_pins, const uint16_t* p_values, uint8_t* p_work, uint8_t p_maxServos)
:
m_pins(p_pins),
m_values(p_values),
m_timings(reinterpret_cast<uint16_t*>(p_work)),
m_ports(reinterpret_cast<uint8_t*>(m_timings + p_maxServos)),
m_masks(m_ports + p_maxServos),
m_maxServos(p_maxServos),
m_activePort(0),
m_activeMask(0xFF),
m_nextPort(0),
m_nextMask(0),
m_idx(0)
{
	s_instance = this;
}


void ServoOut::update()
{
	uint16_t totalTime = 0;
	uint8_t idx = 0;
	for (uint8_t i = 0; i < m_maxServos; ++i)
	{
		if (m_pins[i] != 0)
		{
			uint8_t bit = digitalPinToBitMask(m_pins[i]);
			uint8_t port = digitalPinToPort(m_pins[i]);
			volatile uint8_t* out = portOutputRegister(port);
			
		}
	}
}


void ServoOut::handleInterrupt()
{
	if (s_instance != 0)
	{
		s_instance->isr();
	}
}


// Private functions

void ServoOut::isr()
{
	if (m_activePort != 0)
	{
		// set active pin to low, no need to do ~here, already been taken care of
		*m_activePort &= m_activeMask;
	}
	if (m_nextPort != 0)
	{
		// set next pin to high
		*m_nextPort |= m_nextMask;
	}
	// update compare register
	OCR1A += m_timings[m_idx];
	
	m_activePort = m_nextPort;
	m_activeMask = ~m_nextMask;
	
	++m_idx;
	if (m_idx >= m_maxServos || m_timings[m_idx] == 0)
	{
		m_idx = 0;
	}
	
	// get next port and mask
	m_nextPort = reinterpret_cast<volatile uint8_t*>(m_ports[m_idx]);
	m_nextMask = m_masks[m_idx];
}
/*

handle interrupt()
{
	active pin != 0?
		set active pin to low
	next pin != 0?
		set next pin high
	update compare register
	active pin = next pin
	get next pin
}

*/

// namespace end
}
