/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** SwashToThrottleMix.cpp
** Swashplate to Throttle mix functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <SwashToThrottleMix.h>
#include <rc_debug_lib.h>
#include <util.h>


namespace rc
{

// Public functions

SwashToThrottleMix::SwashToThrottleMix(uint8_t p_ail, uint8_t p_ele)
:
m_ail(p_ail),
m_ele(p_ele)
{
	
}


void SwashToThrottleMix::setAilMix(uint8_t p_mix)
{
	RC_TRACE("set ail mix: %u", p_mix);
	RC_ASSERT_MINMAX(p_mix, 0, 100);
	
	m_ail = p_mix;
}
	

uint8_t SwashToThrottleMix::getAilMix() const
{
	return m_ail;
}


void SwashToThrottleMix::setEleMix(uint8_t p_mix)
{
	RC_TRACE("set ele mix: %u", p_mix);
	RC_ASSERT_MINMAX(p_mix, 0, 100);
	
	m_ele = p_mix;
}
	

uint8_t SwashToThrottleMix::getEleMix() const
{
	return m_ele;
}


int16_t SwashToThrottleMix::apply(int16_t p_thr, int16_t p_ail, int16_t p_ele) const
{
	RC_ASSERT_MINMAX(p_thr, -256, 256);
	RC_ASSERT_MINMAX(p_ail, -358, 358);
	RC_ASSERT_MINMAX(p_ele, -358, 358);
	
	// the amount of mix to add is simply ail + ele
	int16_t mix = rc::clamp140(rc::mix(p_ail, m_ail) + rc::mix(p_ele, m_ele));
	
	// mix is strongest around center throttle, no mix at full or no throttle.
	int16_t thr = 256 - (p_thr > 0 ? p_thr : -p_thr);
	
	// we're going to have overflows if we multiply by thr, so we divide that by two
	// same as mix = (mix * thr) / 256; but without overflows
	mix = (mix * (thr / 2)) / 128;
	
	return rc::clampNormalized(p_thr + mix);
}


void SwashToThrottleMix::apply() const
{
	rc::setInput(Input_THR, apply(rc::getInput(Input_THR), rc::getInput(Input_AIL), rc::getInput(Input_ELE)));
}


// namespace end
}

