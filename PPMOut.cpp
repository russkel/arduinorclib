/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** PPMOut.cpp
** Pulse Position Modulation Output functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
#else
	#include <avr/interrupt.h>
	#include <wiring.h>
#endif

#include <PPMOut.h>


// Interrupt service routine
ISR(TIMER1_COMPA_vect)
{
	rc::PPMOut::handleInterrupt();
}


namespace rc
{

PPMOut* PPMOut::s_instance = 0;


// Public functions

PPMOut::PPMOut(uint8_t p_channels, int16_t* p_input, uint16_t* p_work, uint8_t p_maxChannels)
:
m_pulseLength(500),
m_pauseLength(10500),
m_center(1520),
m_travel(600),
m_channelCount(p_channels),
m_channels(p_input),
m_channelTimings(p_work),
m_timingCount((p_channels + 1) * 2),
m_timings(p_work + p_maxChannels)
{
	s_instance = this;
}


void PPMOut::start(bool p_a, bool p_invert, bool p_debug)
{
	// update all buffers before we start anything
	updateTimings();
	
	uint8_t pin = p_a ? 9 : 10;
	m_timingCount = 1;
	
	pinMode(pin, OUTPUT);
	digitalWrite(pin, p_invert ? HIGH : LOW);
	
	// First disable the timer interrupts
	TIMSK1 = 0;

	// Configure timer1 in CTC mode (Clear Timer on Compare Match) and Toggle OC1A/OC1B on Compare Match
	TCCR1A = p_a ? (1 << COM1A0) : (1 << COM1B0);
	
	// set up timer1 speed
	if (p_debug == false)
	{
		TCCR1B = ((1 << WGM12) | (1 << CS11)); // set at clk / 8
	}
	else
	{
		TCCR1B = ((1 << WGM12) | (1 << CS12) | (1 << CS10)); // set at clk / 1024
	}
	
	// set the compare register
	OCR1A = m_timings[0];
	TIMSK1 = (1 << OCIE1A) ;
}


void PPMOut::setChannelCount(uint8_t p_channels)
{
	m_channelCount = p_channels;
}


uint8_t PPMOut::getChannelCount() const
{
	return m_channelCount;
}


void PPMOut::setPulseLength(uint16_t p_length)
{
	m_pulseLength = p_length << 1;
}


uint16_t PPMOut::getPulseLength() const
{
	return m_pulseLength >> 1;
}


void PPMOut::setPauseLength(uint16_t p_length)
{
	m_pauseLength = p_length << 1;
}


uint16_t PPMOut::getPauseLength() const
{
	return m_pauseLength >> 1;
}


void PPMOut::setCenter(uint16_t p_center)
{
	m_center = p_center << 1;
}


uint16_t PPMOut::getCenter() const
{
	return m_center >> 1;
}


void PPMOut::setTravel(uint16_t p_travel)
{
	m_travel = p_travel << 1;
}


uint16_t PPMOut::getTravel() const
{
	return m_travel >> 1;
}


void PPMOut::loadFutaba()
{
	setCenter(1520);
	setTravel(600);
}


void PPMOut::loadJR()
{
	setCenter(1500);
	setTravel(600);
}


void PPMOut::update()
{
	for (uint8_t i = 0; i < m_channelCount; ++i)
	{
		m_channelTimings[i] = normalizedToTicks(m_channels[i]);
	}
}


void PPMOut::handleInterrupt()
{
	if (s_instance != 0)
	{
		s_instance->isr();
	}
}


// Private functions

uint16_t PPMOut::normalizedToTicks(int16_t p_normal) const
{
	// we have a normalized value [-256 - 256] which corresponds to full positive or negative servo movement
	// we need to scale this to a [0 - 2 * m_travel] timer ticks range
	// this needs to be done in multiple stages to prevent overflows while keeping maximum resolution
	p_normal += 256; // first we bring it up to [0 - 512]
	
	// calculate range
	uint16_t range = m_travel << 1;
	
	// we assume the range won't be more than 4000 ticks, 2 milliseconds
	// this means we have 4 bits of room to play with
	// we can safely multiply any 4 bit number with the range without having overflows
	// the normalized value is 10 bits in size
	// we will chop it up into two pieces of 4 bits and one piece of 2 bits
	// then we will do the multiplications, divide the results by 512, and shift the results back
	// then we'll piece the results back together to form the end result
	
	// cut  into pieces
	uint16_t p1 =  p_normal       & 0x0F; // bits 0-3
	uint16_t p2 = (p_normal >> 4) & 0x0F; // bits 4-7
	uint16_t p3 = (p_normal >> 8) & 0x03; // bits 8-9
	
	// multiply by end range
	p1 *= range;
	p2 *= range;
	p3 *= range;
	
	// divide by start range, shift back
	p1 >>= 9; // divide by 512
	p2 >>= 5; // divide by 32; ( / 512) << 4
	p3 >>= 1; // divide by 2;  ( / 512) << 8
	
	// piece it back together, offset with center
	return ((m_center - m_travel) + p1 + p2 + p3);
}


void PPMOut::updateTimings()
{
	uint16_t* scratch = m_timings;
	
	// copy all pre-calculated timings
	for (uint8_t i = 0; i < m_channelCount; ++i)
	{
		// set pulse length
		*scratch = m_pulseLength;
		++scratch;
		
		// set timing
		*scratch = m_channelTimings[i];
		++scratch;
	}
	
	// set final pulse length
	*scratch = m_pulseLength;
	++scratch;
	
	// set pause length
	*scratch = m_pauseLength - m_pulseLength;
	
	// update number of timings
	m_timingCount = (m_channelCount + 1) * 2;
}


void PPMOut::isr()
{
	// set the compare register with the next value
	OCR1A = m_timings[m_timingPos];
	
	// update position
	++m_timingPos;
	if (m_timingPos >= m_timingCount)
	{
		m_timingPos = 0;
		
		// we're at the end of frame here, so there's plenty of time to update
		updateTimings();
	}
}

// namespace end
}
