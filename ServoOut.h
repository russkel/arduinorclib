#ifndef INC_RC_SERVOOUT_H
#define INC_RC_SERVOOUT_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ServoOut.h
** Servo Signal Output functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>


namespace rc
{

/*! 
 *  \brief     Class to encapsulate Servo Siganl Output functionality.
 *  \details   This class provides a way to generate a Servo signal.
 *  \author    Daniel van den Ouden
 *  \date      Feb-2012
 *  \copyright Public Domain.
 */
class ServoOut
{
public:
	
	/*! \brief Constructs a ServoOut object.*/
	ServoOut();
	
private:
	
};


} // namespace end

#endif // INC_RC_SERVOOUT_H
