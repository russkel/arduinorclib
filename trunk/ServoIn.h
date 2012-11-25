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

#include <rc_config.h>


namespace rc
{

/*! 
 *  \brief     Class to encapsulate Servo Signal Input functionality.
 *  \details   This class provides a way to read and decode a Servo signal.
 *  \author    Daniel van den Ouden
 *  \date      Feb-2012
 *  \warning   This class should <b>NOT</b> be used together with the standard Arduino Servo library,
 *             use rc::ServoOut instead.
 *  \copyright Public Domain.
 */
class ServoIn
{
public:
	
	/*! \brief Constructs a ServoIn object.*/
	ServoIn();
	
	/*! \brief Starts measuring.
	    \param p_high Whether the incoming signal has high or low pulses.
	    \warning Do <b>NOT</b> use this together with the standard Arduino Servo library,
	             use rc::ServoOut instead.*/
	void start(bool p_high = true);
	
	/*! \brief Handles pin change interrupt, call in your interrupt handler.
	    \param p_servo For which servo the pin changed.
	    \param p_high Whether the pin is high or not.*/
	void pinChanged(uint8_t p_servo, bool p_high);
	
	/*! \brief Updates output buffer with new values.*/
	void update();
	
private:
	bool     m_high;                         //!< Whether pulses are high or low.
	uint16_t m_pulseStart[RC_MAX_CHANNELS];  //!< Last measured pulse start for each servo.
	uint16_t m_pulseLength[RC_MAX_CHANNELS]; //!< Last measured pulse length for each servo.
};
/** \example servoin_example.pde
 * This is an example of how to use the ServoIn class.
 */

} // namespace end

#endif // INC_RC_SERVOIN_H
