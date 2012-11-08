#ifndef INC_RC_CONFIGURABLEINPUT_H
#define INC_RC_CONFIGURABLEINPUT_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ConfigurableInput.h
** Base class for classes having an input
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <input.h>


namespace rc
{

/*! 
 *  \brief     Base class for classes having configurable input
 *  \details   If a class can use configurable input, derive from this.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class ConfigurableInput
{
public:
	/*! \brief Sets the input index.
	    \param p_input Index to use as source input.*/
	void setInput(Input p_input);
	
	/*! \brief Gets the input index.
	    \return Index currently used as source input.*/
	Input getInput() const;

protected:
	/*! \brief Constructs a DualRates object
	    \param p_input Index to use as source input.*/
	ConfigurableInput(Input p_input = Input_None);

	Input m_input;
};


} // namespace end

#endif // INC_RC_CONFIGURABLEINPUT_H
