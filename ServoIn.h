#ifndef INC_RC_SERVOIN_H
#define INC_RC_SERVOIN_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ServoIn.h
** Servo Signal Input functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>


namespace rc
{

/*! 
 *  \brief     Class to encapsulate Servo Siganl Input functionality.
 *  \details   This class provides a way to read and decode a Servo signal.
 *  \author    Daniel van den Ouden
 *  \date      Feb-2012
 *  \copyright Public Domain.
 */
class ServoIn
{
public:
	
	/*! \brief Constructs a ServoIn object.*/
	ServoIn();
	
private:
	
};


} // namespace end

#endif // INC_RC_SERVOIN_H
