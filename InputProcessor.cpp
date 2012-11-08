/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** InputProcessor.cpp
** Base class for classes taking input
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <InputProcessor.h>


namespace rc
{

// Public functions

void InputProcessor::setInput(Input p_input)
{
	m_input = p_input;
}


Input InputProcessor::getInput() const
{
	return m_input;
}


// Protected functions

InputProcessor::InputProcessor(Input p_input)
:
m_input(p_input)
{
	
}


// namespace end
}
