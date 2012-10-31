/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** PlaneModel.cpp
** Wing types, rudder types and tail types.
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
#else
	#include <wiring.h>
#endif

#include <PlaneModel.h>


namespace rc
{

// Public functions

PlaneModel::PlaneModel()
:
m_wing(WingType_Tailed),
m_tail(TailType_Normal),
m_rudder(RudderType_Normal),
m_ailerons(AileronCount_1),
m_elevonAil(50),
m_elevonEle(50),
m_ailvator(0),
m_vtailEle(50),
m_vtailRud(50)
{
	
}


void PlaneModel::setWingType(WingType p_type)
{
	m_wing = p_type;
}


PlaneModel::WingType PlaneModel::getWingType() const
{
	return m_wing;
}


void PlaneModel::setTailType(TailType p_type)
{
	m_tail = p_type;
}


PlaneModel::TailType PlaneModel::getTailType() const
{
	return m_tail;
}


void PlaneModel::setRudderType(RudderType p_type)
{
	m_rudder = p_type;
}


PlaneModel::RudderType PlaneModel::getRudderType() const
{
	return m_rudder;
}


void PlaneModel::setAileronCount(AileronCount p_count)
{
	m_ailerons = p_count;
}


PlaneModel::AileronCount PlaneModel::getAileronCount() const
{
	return m_ailerons;
}


void apply(int16_t p_ail, int16_t p_ele, int16_t p_rud)
{
	switch (m_wing)
	{
	default:
	case WingType_Tailed:
		switch (m_ailerons)
		{
		case AileronCount_4:
			m_servos[Servo_AIL4] = -p_ail;
			m_servos[Servo_AIL3] = p_ail;
			// FALL THROUGH
			
		case AileronCount_2:
			m_servos[Servo_AIL2] = -p_ail;
			// FALL THROUGH
			
		default:
		case AileronCount_1:
			m_servos[Servo_AIL1] = p_ail;
			break;
		}
		applyTail(p_ail, p_ele, p_rud);
		break;
		
	case WingType_Tailless:
		switch (m_ailerons)
		{
		case AileronCount_4:
			m_servos[Servo_AIL4] = -p_ail + p_ele;
			m_servos[Servo_AIL3] = p_ail + p_ele;
			// FALL THROUGH
		
		default:		
		case AileronCount_2:
			m_servos[Servo_AIL2] = -p_ail + p_ele;
			m_servos[Servo_AIL1] = p_ail + p_ele;
			break;
		}
		applyRudder(p_rud);
		break;
	}
}


int16_t getServo(Servo p_servo) const
{
	return m_servos[p_servo];
}


// Private functions

void applyTail(int16_t p_ail, int16_t p_ele, int16_t p_rud)
{
	switch (m_tail)
	{
	default:
	case TailType_Normal:
		m_servos[Servo_ELE1] = p_ele;
		m_servos[Servo_RUD1] = p_rud;
		break;
		
	case TailType_VTail:
		m_servos[Servo_ELE1] = p_rud + p_ele;
		m_servos[Servo_RUD1] = p_rud - p_ele;
		break;
		
	case TailType_Ailvator:
		m_servos[Servo_ELE1] = p_ele + p_ail;
		m_servos[Servo_ELE2] = p_ele - p_ail;
		m_servos[Servo_RUD1] = p_rud;
		break;
	}
}


void applyRudder(int16 p_rud)
{
	switch (m_rudder)
	{
	case RudderType_None:
		break;
	
	default:
	case RudderType_Normal:
		m_servos[Servo_RUD1] = p_rud;
		break;
		
	case RudderType_Winglet:
		m_servos[Servo_RUD1] = p_rud;
		m_servos[Servo_RUD2] = p_rud;
		break;
	}
}

// namespace end
}

