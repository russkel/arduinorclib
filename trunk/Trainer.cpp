/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Trainer.cpp
** Trainer port functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <rc_debug_lib.h>
#include <Trainer.h>
#include <util.h>


namespace rc
{

// Public functions

Trainer::Trainer()
:
m_enabled(false),
m_destination(0xFF),
m_studentRate(100),
m_teacherRate(0)
{
	
}


void Trainer::setEnabled(bool p_enabled)
{
	RC_TRACE("set enabled: %d", p_enabled);
	m_enabled = p_enabled;
}


bool Trainer::isEnabled() const
{
	return m_enabled;
}


void Trainer::setAsInputSource(Input p_destination)
{
	RC_TRACE("set as input source: %d", p_destination);
	RC_ASSERT(p_destination < Input_Count);
	
	m_destination = static_cast<uint8_t>(p_destination);
}


Input Trainer::getInputDestination() const
{
	if (m_destination & _BV(7) || m_destination == 0xFF)
	{
		return Input_None; // currently set as output source
	}
	return static_cast<Input>(m_destination);
}


void Trainer::setAsOutputSource(Output p_destination)
{
	RC_TRACE("set as output source: %d", p_destination);
	RC_ASSERT(p_destination < Output_Count);
	
	m_destination = static_cast<uint8_t>(p_destination) & _BV(7); // bit 7 is output flag
}


Output Trainer::getOutputDestination() const
{
	if (m_destination & _BV(7) == 0  || m_destination == 0xFF)
	{
		return Output_None; // currently set as output source
	}
	return static_cast<Output>(m_destination & 0x7F);
}


void Trainer::setStudentRate(uint8_t p_rate)
{
	RC_TRACE("set trainer rate: %u%%", p_rate);
	RC_ASSERT_MINMAX(p_rate, 0, 100);
	
	m_studentRate = p_rate;
}


uint8_t Trainer::getStudentRate() const
{
	return m_studentRate;
}


void Trainer::setTeacherRate(uint8_t p_rate)
{
	RC_TRACE("set source rate: %u%%", p_rate);
	RC_ASSERT_MINMAX(p_rate, 0, 100);
	
	m_teacherRate = p_rate;
}


uint8_t Trainer::getTeacherRate() const
{
	return m_teacherRate;
}


uint16_t Trainer::apply(uint16_t p_teacher, uint16_t p_student, bool p_active)
{
	if (m_enabled && p_active)
	{
		return rc::clamp140(rc::mix(p_student, static_cast<int8_t>(m_studentRate)) +
		                    rc::mix(p_teacher, static_cast<int8_t>(m_teacherRate)));
	}
	return p_teacher;
}


void Trainer::apply(uint16_t p_student, bool p_active)
{
	if (p_active)
	{
		Input i = getInputDestination();
		if (i != Input_None)
		{
			rc::setInput(i, apply(rc::getInput(i), p_student, p_active));
		}
		Output o = getOutputDestination();
		if (o != Output_None)
		{
			rc::setOutput(o, apply(rc::getOutput(o), p_student, p_active));
		}
	}
}


// namespace end
}
