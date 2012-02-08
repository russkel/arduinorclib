#ifndef INC_TX_DUALRATES_H
#define INC_TX_DUALRATES_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** DualRates.h
** Dual Rates functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>


namespace tx {

/*! \brief Class to encapsulate Dual Rates functionality.*/
class DualRates
{
public:
	/*! \brief Constructs a DualRates object
	*/
	DualRates();
	
	/*! \brief Applies dual rates.
	    \p_value Source value to apply d/r to, range [-256 - 256].
		\p_expo Amount of d/r to apply, range [0 - 140].
		\return d/r applied p_value, range 140% [-358 - 358].*/
	int16_t apply(int16_t p_value, uint8_t p_rate) const;
	
private:
};

extern DualRates g_DualRates; //!< Global instance

} // namespace end

#endif // INC_TX_DUALRATES_H
