/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** InputSwitch.cpp
** Class which takes input from the input buffer and acts like a switch
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <InputSwitch.h>
#include <rc_debug_lib.h>


namespace rc
{

// Public functions

InputSwitch::InputSwitch(Input p_source, Switch p_destination, bool p_tri)
:
InputProcessor(p_source),
SwitchSource(p_tri ? SwitchType_TriState : SwitchType_BiState, p_destination),
m_up(p_tri ? 128 : 0),
m_center(p_tri ? -128 : 0)
{
	
}


void InputSwitch::setUpMark(int16_t p_mark)
{
	RC_TRACE("set up mark: %d", p_mark);
	m_up = p_mark;
}


int16_t InputSwitch::getUpMark() const
{
	return m_up;
}


void InputSwitch::setCenterMark(int16_t p_mark)
{
	RC_TRACE("set center mark: %d", p_mark);
	m_center = p_mark;
}


int16_t InputSwitch::getCenterMark() const
{
	return m_center;
}


SwitchState InputSwitch::read(int16_t p_value) const
{
	if (p_value >= m_up)
	{
		return writeSwitchState(SwitchState_Up);
	}
	else if (p_value >= m_center)
	{
		return writeSwitchState(SwitchState_Center);
	}
	return writeSwitchState(SwitchState_Down);
}


SwitchState InputSwitch::read() const
{
	if (m_source == Input_None)
	{
		return writeSwitchState(SwitchState_Disconnected);
	}
	return read(getInput(m_source));
}


// namespace end
}
