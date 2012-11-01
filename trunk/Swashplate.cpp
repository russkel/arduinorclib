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
	apply(p_ail, p_ele, p_pit);
	p_ailOUT  = getOutput(Output_AIL1);
	p_eleOUT  = getOutput(Output_ELE1);
	p_pitOUT  = getOutput(Output_PIT1);
	p_ele2OUT = getOutput(Output_ELE2);
}


void Swashplate::apply(int16_t p_ail, int16_t p_ele, int16_t p_pit) const
{
	p_ail = mix(p_ail, m_ailMix);
	p_ele = mix(p_ele, m_eleMix);
	p_pit = mix(p_pit, m_pitMix);
	
	switch (m_type)
	{
		case Type_H1:
		default:
		{
			setOutput(Output_AIL1, p_ail);
			setOutput(Output_ELE1, p_ele);
			setOutput(Output_PIT,  p_pit);
		}
		break;
		
		case Type_H2:
		{
			setOuput(Output_ELE1,  p_ele);
			setOuput(Output_AIL1,  p_ail + p_pit);
			setOuput(Output_PIT,  -p_ail + p_pit);
		}
		break;
		
		case Type_HE3:
		{
			setOuput(Output_ELE1,  p_ele + p_pit);
			setOuput(Output_AIL1,  p_ail + p_pit);
			setOuput(Output_PIT,  -p_ail + p_pit);
		}
		break;
		
		case Type_HR3:
		{
			setOuput(Output_ELE1,  p_ele + p_pit);
			setOuput(Output_AIL1,  p_ail + p_pit -(p_ele >> 1));
			setOuput(Output_PIT,  -p_ail + p_pit -(p_ele >> 1));
		}
		break;
		
		case Type_HN3:
		{
			setOuput(Output_ELE1,  p_ele + p_pit -(p_ail >> 1));
			setOuput(Output_AIL1,  p_ail + p_pit);
			setOuput(Output_PIT,  -p_ele + p_pit -(p_ail >> 1));
		}
		break;
		
		case Type_H3:
		{
			setOuput(Output_ELE1,  p_ele + p_pit);
			setOuput(Output_AIL1, -p_ele + p_ail + p_pit);
			setOuput(Output_PIT,  -p_ele - p_ail + p_pit);
		}
		break;
		
		case Type_H4:
		{
			setOuput(Output_ELE1,  p_ele + p_pit);
			setOuput(Output_ELE2, -p_ele + p_pit);
			setOuput(Output_AIL1,  p_ail + p_pit);
			setOuput(Output_PIT,  -p_ail + p_pit);
		}
		break;
		
		case Type_H4X:
		{
			setOuput(Output_ELE1,  (p_ele >> 1) - (p_ail >> 1) + p_pit);
			setOuput(Output_ELE2, -(p_ele >> 1) + (p_ail >> 1) + p_pit);
			setOuput(Output_AIL1,  (p_ele >> 1) + (p_ail >> 1) + p_pit);
			setOuput(Output_PIT,  -(p_ele >> 1) - (p_ail >> 1) + p_pit);
		}
		break;
	}
}


// namespace end
}
