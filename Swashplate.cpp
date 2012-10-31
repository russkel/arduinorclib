/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Swashplate.cpp
** Swashplate functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Swashplate.h>
#include <util.h>


namespace rc
{

// Public functions

Swashplate::Swashplate()
:
m_type(Type_H1),
m_ailMix(0),
m_eleMix(0),
m_pitMix(0)
{
	
}


void Swashplate::setType(Type p_type)
{
	m_type = p_type;
}


Swashplate::Type Swashplate::getType() const
{
	return m_type;
}


void Swashplate::setAilMix(int8_t p_mix)
{
	m_ailMix = p_mix;
}


int8_t Swashplate::getAilMix() const
{
	return m_ailMix;
}


void Swashplate::setEleMix(int8_t p_mix)
{
	m_eleMix = p_mix;
}


int8_t Swashplate::getEleMix() const
{
	return m_eleMix;
}


void Swashplate::setPitMix(int8_t p_mix)
{
	m_pitMix = p_mix;
}


int8_t Swashplate::getPitMix() const
{
	return m_pitMix;
}


void Swashplate::apply(int16_t p_ail,
                       int16_t p_ele,
                       int16_t p_pit,
                       int16_t& p_ailOUT,
                       int16_t& p_eleOUT,
                       int16_t& p_pitOUT,
                       int16_t& p_ele2OUT) const
{
	p_ail = mix(p_ail, m_ailMix);
	p_ele = mix(p_ele, m_eleMix);
	p_pit = mix(p_pit, m_pitMix);
	
	switch (m_type)
	{
		case Type_H1:
		default:
		{
			p_ailOUT = p_ail;
			p_eleOUT = p_ele;
			p_pitOUT = p_pit;
		}
		break;
		
		case Type_H2:
		{
			p_eleOUT = p_ele;
			p_ailOUT = p_ail + p_pit;
			p_pitOUT = -p_ail + p_pit;
		}
		break;
		
		case Type_HE3:
		{
			p_eleOUT = p_ele + p_pit;
			p_ailOUT = p_ail + p_pit;
			p_pitOUT = -p_ail + p_pit;
		}
		break;
		
		case Type_HR3:
		{
			p_eleOUT = p_ele + p_pit;
			p_ailOUT = p_ail + p_pit -(p_ele >> 1);
			p_pitOUT = -p_ail + p_pit -(p_ele >> 1);
		}
		break;
		
		case Type_HN3:
		{
			p_eleOUT = p_ele + p_pit -(p_ail >> 1);
			p_ailOUT = p_ail + p_pit;
			p_pitOUT = -p_ele + p_pit -(p_ail >> 1);
		}
		break;
		
		case Type_H3:
		{
			p_eleOUT = p_ele + p_pit;
			p_ailOUT = -p_ele + p_ail + p_pit;
			p_pitOUT = -p_ele - p_ail + p_pit;
		}
		break;
		
		case Type_H4:
		{
			p_eleOUT  = p_ele + p_pit;
			p_ele2OUT = -p_ele + p_pit;
			p_ailOUT  = p_ail + p_pit;
			p_pitOUT  = -p_ail + p_pit;
		}
		break;
		
		case Type_H4X:
		{
			p_eleOUT  = (p_ele >> 1) - (p_ail >> 1) + p_pit;
			p_ele2OUT = -(p_ele >> 1) + (p_ail >> 1) + p_pit;
			p_ailOUT  = (p_ele >> 1) + (p_ail >> 1) + p_pit;
			p_pitOUT  = -(p_ele >> 1) - (p_ail >> 1) + p_pit;
		}
		break;
	}
}


// namespace end
}
