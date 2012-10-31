#ifndef INC_RC_PLANEMODEL_H
#define INC_RC_PLANEMODEL_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** PlaneModel.h
** Wing types, rudder types and tail types.
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>


namespace rc
{

/*! 
 *  \brief     Class to encapsulate mixing for various plane models.
 *  \details   This class provides mixing for all sorts of plane models.
 *  \author    Daniel van den Ouden
 *  \date      Oct-2012
 *  \copyright Public Domain.
 */
class PlaneModel
{
public:
	enum WingType //! Type of wings
	{
		WingType_Tailed,  //!< Tailed setup with separate control surfaces for elevator
		WingType_Tailless //!< Tailless setup/Flying wing, uses elevon for combined aileron/elevator action
	};
	
	enum TailType //! Type of tails, only for tailed wings
	{
		TailType_Normal,  //!< Normal tail with servo for elevator and rudder
		TailType_VTail,   //!< V-Tail/Butterfly tail/Ruddervators setup with two servos for combined elevator and rudder 
		TailType_Ailvator //!< Ailvator, three servos, one for tail, two for combined elevator and aileron.
	};
	
	enum RudderType //! Type of rudder, only for tailless wings
	{
		RudderType_None,   //!< No rudder available
		RudderType_Normal, //!< Single servo for rudder
		RudderType_Winglet //!< Dual servo for winglets (rudders on wingtips)
	};
	
	enum AileronCount //! Number of Aileron servos
	{
		AileronCount_1 = 1, //!< Single aileron servo, not in combination with tailless wings or flaps
		AileronCount_2 = 2, //!< Dual aileron servos
		AileronCount_4 = 4  //!< Four aileron servos
	};
	
	enum Servo //! Servo index
	{
		Servo_AIL1, //!< Aileron servo 1
		Servo_AIL2, //!< Aileron servo 2
		Servo_AIL3, //!< Aileron servo 3
		Servo_AIL4, //!< Aileron servo 4
		Servo_ELE1, //!< Elevator servo 1/V-Tail 1
		Servo_ELE2, //!< Elevator servo 2
		Servo_RUD1, //!< Rudder servo 1/V-Tail 2
		Servo_RUD2, //!< Rudder servo 2
		
		Servo_Count
	}
	
	/*! \brief Constructs a PlaneModel object*/
	PlaneModel();
	
	/*! \brief Sets wing type
	    \param p_type Wing type to set.*/
	void setWingType(WingType p_type);
	
	/*! \brief Gets wing type.
	    \return The wing type currently set.*/
	WingType getWingType() const;
	
	/*! \brief Sets tail type
	    \param p_type Tail type to set.*/
	void setTailType(TailType p_type);
	
	/*! \brief Gets tail type.
	    \return The tail type currently set.*/
	TailType getTailType() const;
	
	/*! \brief Sets rudder type
	    \param p_type Rudder type to set.*/
	void setRudderType(RudderType p_type);
	
	/*! \brief Gets rudder type.
	    \return The rudder type currently set.*/
	RudderType getRudderType() const;
	
	/*! \brief Sets the number of aileron servos
	    \param p_count Number of aileron servos.*/
	void setAileronCount(AileronCount p_count);
	
	/*! \brief Gets number of aileron servos.
	    \return The number of aileron servos.*/
	AileronCount getAileronCount() const;
	
	/*! \brief Applies input to the servos.
	    \param p_ail Aileron input, range 140% [-358 - 358].
		\param p_ele Elevator input, range 140% [-358 - 358].
		\param p_rud Rudder input, range 140% [-358 - 358].*/
	void apply(int16_t p_ail, int16_t p_ele, int16_t p_rud);
	
	/*! \brief Gets the position of a servo.
	    \param p_servo The servo to get the position of.
		\return Servo position, range 140% [-358 - 358].*/
	int16_t getServo(Servo p_servo) const;
	
private:
	void applyTail(int16_t p_ail, int16_t p_ele, int16_t p_rud);
	void applyRudder(int16_t p_rud);
	
	WingType     m_wing;     //!< Wing type
	TailType     m_tail;     //!< Tail type
	RudderType   m_rudder;   //!< Rudder type
	AileronCount m_ailerons; //!< Number of aileron servos
	
	int8_t m_elevonAil; //!< Amount of aileron mixing in ailevon (tailless wings)
	int8_t m_elevonEle; //!< Amount of elevator mixing in ailevon (tailless wings)
	
	int8 m_ailvator; //!< Amount of aileron to elevator mix
	
	int8 m_vtailEle; //!< Amount of elevator mix in V-Tail
	int8 m_vtailRud; //!< Amount of rudder mix in V-Tail
	
	int16_t[Servo_Count] m_servos; //!< Servo positions
};

/** \example planemodel_example.pde
 * This is an example of how to use the PlaneModel class.
 */


} // namespace end

#endif // INC_RC_PLANEMODEL_H
