#ifndef INC_TX_PPM_H
#define INC_TX_PPM_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** PPM.h
** Pulse Position Modulation functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>


namespace tx
{

/*! \brief Class to encapsulate PPM functionality.*/
class PPM
{
public:
	
	/*! \brief Constructs a PPM object.
	    \param p_channels Number of active channels, <= p_maxChannels.
	    \param p_input External input buffer for channel values.
		\param p_work Work buffer, should be (p_maxChannels + 1) * 4 elements large.
		\param p_maxChannels Maximum number of channels supported. */
	PPM(uint8_t p_channels, int16_t* p_input, uint16_t* p_work, uint8_t p_maxChannels);
	
	/*! \brief Sets up timers and interrupts.
	    \param p_a Use compare A on true, compare B on false.*/
	void start(bool p_a);
	
	/*! \brief Sets channel count
	    \param p_channels Channel count.*/
	void setChannelCount(uint8_t p_channels);
	
	/*! \brief Gets channel count.
	    \return The amount of active channels.*/
	uint8_t getChannelCount() const;
	
	/*! \brief Sets pulse length
	    \param p_length Pulse length in microseconds.*/
	void setPulseLength(uint16_t p_length);
	
	/*! \brief Gets pulse length.
	    \return The current pulse length.*/
	uint16_t getPulseLength() const;
	
	/*! \brief Sets pause length
	    \param p_length Pause length in microseconds.*/
	void setPauseLength(uint16_t p_length);
	
	/*! \brief Gets pause length.
	    \return The current pause length.*/
	uint16_t getPauseLength() const;
	
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
	
	/*! \brief Updates channel timings, will be sent at next frame.*/
	void update();
	
	/*! \brief Handles timer interrupt.*/
	static void handleInterrupt();
	
private:
	/*! \brief convert a normalized value [-256 - 256] to timer ticks. */
	uint16_t normalizedToTicks(int16_t p_normal) const; 
	
	/*! \brief Update the entire timings buffer. */
	void updateTimings();
	
	/*! \brief Internal interrupt handling. */
	void isr();
	
	uint16_t m_pulseLength; //!< Pulse length in timer ticks.
	uint16_t m_pauseLength; //!< End of frame length in timer ticks.
	uint16_t m_center; //!< Servo center in timer ticks.
	uint16_t m_travel; //!< Servo travel in timer ticks.
	
	uint8_t  m_channelCount; //!< Number of active channels.
	int16_t* m_channels;     //!< External buffer with channel values, range [-256 - 256].
	
	volatile uint16_t* m_channelTimings; //!< Timings per channel, in timer ticks.
	
	uint8_t   m_timingCount; //!< Number of active timings.
	uint8_t   m_timingPos;   //!< Current position in timings buffer.
	uint16_t* m_timings;     //!< Timing values in timer ticks.
	
	static PPM* s_instance; //!< Singleton instance
};


} // namespace end

#endif // INC_TX_PPM_H
