#ifndef INC_TX_EXPO_H
#define INC_TX_EXPO_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Expo.h
** Exponential functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoTXLib
** Website: http://sourceforge.net/p/arduinotxlib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>


namespace tx
{

/*! \brief Class to encapsulate Exponential functionality.*/
class Expo
{
public:
	/*! \brief Constructs an Expo object
	*/
	Expo();
	
	/*! \brief Applies expo.
	    \p_value Source value to apply expo to, range [-256 - 256].
		\p_expo Amount of expo to apply, range [-100 - 100].
		\return expo applies p_value.*/
	int16_t apply(int16_t p_value, int8_t p_expo) const;
	
private:
};

extern Expo g_Expo; //!< Global instance

} // namespace end

#endif // INC_TX_EXPO_H
