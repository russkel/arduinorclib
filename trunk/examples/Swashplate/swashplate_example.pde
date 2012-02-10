/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** swashplate_example.pde
** Demonstrate Swashplate functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Swashplate.h>


tx::Swashplate g_swash;

void setup()
{
	// use the most common type of CCPM swash
	g_swash.setType(tx::Swashplate::Type_HR3);
	
	// set up mixes
	g_swash.setAilMix(50);
	g_swash.setEleMix(50);
	g_swash.setPitMix(50);
}

void loop()
{
	// we use a0,a1,a2 as input pin
	int16_t ail = map(analogRead(a0), 0, 1024, -256, 256);
	int16_t ele = map(analogRead(a1), 0, 1024, -256, 256);
	int16_t pit = map(analogRead(a2), 0, 1024, -256, 256);
	
	int16_t dummy; // we need a dummy value
	
	// apply swashplate mixing
	g_swash.apply(ail, ele, pit, ail, ele, pit, dummy);
	
	// we can then use the transformed values for further modification
	// or we can transmit them using the PPM class
}
