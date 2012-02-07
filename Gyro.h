#ifndef INC_TX_GYRO_H
#define INC_TX_GYRO_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Gyro.h
** Gyro functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoTXLib
** Website: http://sourceforge.net/p/arduinotxlib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>


namespace tx
{

/*! \brief Class to encapsulate Gyro functionality.*/
class Gyro
{
public:
	enum Type //!< Type of gyro
	{
		Type_Normal, //!< Normal (Rate mode) gyro
		Type_AVCS    //!< Heading hold gyro, also capable of rate mode
	};

	enum Mode //!< Mode in which the gyro is operating, only for AVCS type gyros
	{
		Mode_Normal, //!< Normal mode (Rate mode)
		Mode_AVCS    //!< AVCS mode (Heading hold mode)
	};

	
	/*! \brief Constructs a Gyro object
	*/
	Gyro();
	
	/*! \brief Sets gyro type
	    \p_type Gyro mode to set.*/
	void setType(Type p_type);
	
	/*! \brief Gets gyro type.
	    \return The gyro type currently set.*/
	Type getType() const;
	
	/*! \brief Sets gyro mode.
	    \p_mode The mode to set.*/
	void setMode(Mode p_mode);
	
	/*! \brief Gets gyro mode.
	    \return The gyro mode currently set.*/
	Mode getMode() const;
	
	/*! \brief Applies gyro.
	    \p_gain The amount of gain to use, range [0 - 100].
		\return Normalized channel value, range [-256 - 256].*/
	int16_t apply(int8_t p_gain) const;
	
private:
	Type m_type; //!< Gyro type
	Mode m_mode; //!< Mode of operation (in case of AVCS type)
};

extern Gyro g_Gyro; //!< Global instance

} // namespace end

#endif // INC_TX_GYRO_H
