/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** DualRates.cpp
** Dual Rates functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoTXLib
** Website: http://sourceforge.net/p/arduinotxlib/
** -------------------------------------------------------------------------*/

#include <DualRates.h>


namespace tx
{

// Public functions

DualRates::DualRates()
{
	
}


int16_t DualRates::apply(int16_t p_value, uint8_t p_rate) const
{
	// there's a risk in overflows here, since 256 * 140 > 32K
	// so we do this unsigned..
	uint8_t neg = p_value < 0;
	uint16_t val = static_cast<uint16_t>(neg ? (-p_value) : p_value);
	val = (val * p_rate) / 100;
	return neg ? -static_cast<int16_t>(val) : static_cast<int16_t>(val);
}

// Define global instance
DualRates g_DualRates = DualRates();


// namespace end
}
