#ifndef INC_RC_PPMIN_H
#define INC_RC_PPMIN_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** PPMIn.h
** Pulse Position Modulation Input functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#define PPMIN_WORK_SIZE(channels) (channels)


namespace rc
{

/*! 
 *  \brief     Class to encapsulate PPM Input functionality.
 *  \details   This class provides a way to decode a PPM signal.
 *  \author    Daniel van den Ouden
 *  \date      Feb-2012
 *  \copyright Public Domain.
 */
class PPMIn
{
public:
	
	/*! \brief Constructs a PPMIn object.
	    \param p_results External buffer to store results, at least p_maxChannels in size.
	    \param p_work Work buffer at least PPMIN_WORK_SIZE(p_maxChannels) in size.
	    \param p_maxChannels Maximum number of channels supported.
		\param p_useMicroseconds Whether the results should be stored in microseconds or normalized.*/
	PPMIn(int16_t* p_results, uint16_t* p_work, uint8_t p_maxChannels, bool p_useMicroseconds = false);
	
	/*! \brief Checks if the input signal is stable.
	    \return Return true if a stable signal has been received. */
	bool isStable() const;
	
	/*! \brief Gets the number of channels in the signal.
	    \return The number of channels found in the last received signal. */
	uint8_t getChannels() const;
	
	/*! \brief Sets servo center.
	    \param p_center Center of servo in microseconds.*/
	void setCenter(uint16_t);
	
	/*! \brief Gets the servo center.
	    \return The servo center in microseconds.*/
	uint16_t getCenter() const;
	
	/*! \brief Sets maximum travel from center.
	    \param p_travel Travel of servo in microseconds.*/
	void setTravel(uint16_t);
	
	/*! \brief Gets maximum travel from center.
	    \return Travel of servo in microseconds.*/
	uint16_t getTravel() const;
	
	/*! \brief Sets timings according to Futaba standards, center 1520, travel 600.*/
	void loadFutaba();
	
	/*! \brief Sets timings according to JR standards, center 1500, travel 600.*/
	void loadJR();
	
	/*! \brief Handles pin change interrupt, call in your interrupt handler.
	    \param p_high Whether the pin is high or not.*/
	void pinChanged(bool p_high);
	
	/*! \brief Updates the result buffer with new values.
	    \return Whether anything has been updated.*/
	bool update();
	
private:
	/*! \brief convert a timer ticks value to a normalized value [-256 - 256].
	    \param p_ticks Input in timer ticks.
	    \return Normalized value, range [-256 - 256].*/
	int16_t ticksToNormalized(uint16_t p_ticks) const; 
	
	enum State
	{
		State_Startup,   //!< Just started, no signal received yet.
		State_Listening, //!< Received first end of frame.
		State_Stable,    //!< Received second end of frame, stable.
		State_Confused   //!< Something unexpected happened.
	};
	
	State   m_state;    //!< Current state of input signal.
	uint8_t m_channels; //!< Number of channels in input signal.
	
	uint16_t m_center; //!< Servo center in timer ticks.
	uint16_t m_travel; //!< Servo travel in timer ticks.
	
	int16_t*  m_results;     //!< Results buffer.
	uint16_t* m_work;        //!< Work buffer.
	uint8_t   m_maxChannels; //!< Maximum number of channels to fit buffers.
	uint8_t   m_idx;         //!< Current index in buffer.
	
	bool          m_useMicroseconds; //!< Whether the results should be stored in microseconds or normalized values.
	volatile bool m_newFrame;        //!< Whether a new frame is available or not.
	
	uint16_t m_lastTime;      //!< Time of last interrupt.
};


} // namespace end

#endif // INC_RC_PPMIN_H
