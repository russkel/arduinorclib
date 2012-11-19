/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** DIPin.cpp
** Digital input read functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Arduino.h>

#include <DIPin.h>
#include <rc_debug_lib.h>


namespace rc
{

// Public functions

DIPin::DIPin(uint8_t p_pin)
:
m_reversed(false)
{
	setPin(p_pin);
}


void DIPin::setPin(uint8_t p_pin)
{
	RC_TRACE("set pin: %u", p_pin);
	m_pin = p_pin;
	pinMode(p_pin, INPUT);
}


uint8_t DIPin::getPin() const
{
	return m_pin;
}


DIPin& DIPin::operator = (uint8_t p_rhs)
{
	setPin(p_rhs);
	return *this;
}


DIPin::operator uint8_t () const
{
	return m_pin;
}


void DIPin::setReverse(bool p_reversed)
{
	RC_TRACE("set reverse: %d", p_reversed);
	m_reversed = p_reversed;
}
	

bool DIPin::isReversed() const
{
	return m_reversed;
}


bool DIPin::read() const
{
	bool raw = digitalRead(m_pin);
	
	return m_reversed ? !raw : raw;
}


// namespace end
}
