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
 *  \brief     Class to encapsulate Servo Signal Input functionality.
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
	
	/*! \brief Checks if the input signal is stable.
	    \return Return true if a stable signal has been received. */
	bool isStable() const;
	
	/*! \brief Handles pin change interrupt, call in your interrupt handler.
	    \param p_high Whether the pin is high or not.*/
	void pinChanged(bool p_high);
	
	/*! \brief Gets the current value of the servo signal.
	    \param p_useMicroseconds Whether the result should be in microseconds or normalized.
	    \return The current value of the servo signal in microseconds or normalized, range [-256 - 256].*/
	int16_t getValue(bool p_useMicroseconds = false) const;
	
private:
	enum State
	{
		State_Startup,   //!< Just started, no signal received yet.
		State_Listening, //!< Received first high signal.
		State_Stable,    //!< Received first low signal, stable.
		State_Confused   //!< Something unexpected happened (too much time between signals).
	};
	
	State    m_state;    //!< Current state of input signal.
	uint16_t m_ticks;    //!< Current value in ticks
	uint16_t m_lastTime; //!< Time of last interrupt.
};


} // namespace end

#endif // INC_RC_SERVOIN_H
