#ifndef INC_TX_CURVE_H
#define INC_TX_CURVE_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Curve.h
** Curve functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>


namespace tx
{

/*! \brief Class to encapsulate Curve functionality.*/
class Curve
{
public:
	enum
	{
		PointCount = 9 //!< Amount of points in the curve
	};
	
	/*! \brief Constructs a Curve object
	*/
	Curve();
	
	/*! \brief Sets a curve point.
	    \p_point The point to set.
		\p_value The value to set, range [-256 - 256].*/
	void setPoint(uint8_t p_point, int16_t p_value);
	
	/*! \brief Gets a curve point.
	    \p_point The point to get.
		\return The current value, range [-256 - 256].*/
	int16_t getPoint(uint8_t p_point) const;
	
	int16_t& operator[](uint8_t p_point);
	
	const int16_t& operator[](uint8_t p_point) const;
	
	/*! \brief Applies curve.
	    \p_value Source value to apply curve to, range [-256 - 256].
		\return curve applied p_value, range [-256 - 256].*/
	int16_t apply(int16_t p_value) const;
	
private:
	int16_t m_points[PointCount];
};

} // namespace end

#endif // INC_TX_CURVE_H
