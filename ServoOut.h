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

#define SERVOOUT_WORK_SIZE(servos) ((servos * 4) + 1)


namespace rc
{

/*! 
 *  \brief     Class to encapsulate Servo Signal Output functionality.
 *  \details   This class provides a way to generate a Servo signal.
 *  \author    Daniel van den Ouden
 *  \date      Feb-2012
 *  \copyright Public Domain.
 */
class ServoOut
{
public:
	
	/*! \brief Constructs a ServoOut object.
	    \param p_pins Input buffer of pins to connect servos to.
		\param p_values Input buffer of values of servos in microseconds.
	    \param p_work Work buffer at least SERVOOUT_WORK_SIZE(p_maxServos) in size.
	    \param p_maxServos Maximum number of servos supported.*/
	ServoOut(const uint8_t* p_pins, const uint16_t* p_values, uint8_t* p_work, uint8_t p_maxServos);
	
	/*! \brief Updates all internal timings.*/
	void update();
	
	/*! \brief Handles timer interrupt.*/
	static void handleInterrupt();
	
private:
	/*! \brief Internal interrupt handling. */
	void isr();
	
	const uint8_t*  m_pins;
	const uint16_t* m_values;
	
	uint16_t* m_timings;
	uint8_t*  m_ports;
	uint8_t*  m_masks;
	
	uint8_t   m_maxServos;
	
	volatile uint8_t* m_activePort;
	         uint8_t  m_activeMask;
	volatile uint8_t* m_nextPort;
	         uint8_t  m_nextMask;
	uint8_t m_idx;
	
	static ServoOut* s_instance; //!< Singleton instance
};
/** \example servoout_example.pde
 * This is an example of how to use the ServoOut class.
 */

} // namespace end

#endif // INC_RC_SERVOOUT_H
