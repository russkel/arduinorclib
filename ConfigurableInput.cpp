/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ConfigurableInput.cpp
** Base class for classes having an input
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <ConfigurableInput.h>


namespace rc
{

// Public functions

void ConfigurableInput::setInput(Input p_input)
{
	m_input = p_input;
}


Input ConfigurableInput::getInput() const
{
	return m_input;
}


// Protected functions

ConfigurableInput::ConfigurableInput(Input p_input)
:
m_input(p_input)
{
	
}


// namespace end
}
