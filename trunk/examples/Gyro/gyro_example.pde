/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** gyro_example.pde
** Demonstrate Gyro functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Gyro.h>


tx::Gyro g_gyro;

void setup()
{
	// set up the gyro type
	g_gyro.setType(tx::Gyro::Type_AVCS);
}

void loop()
{
	// we use a switch to change between gyro modes
	g_gyro.setMode(digitalRead(3) == HIGH ? tx::Gyro::Mode_AVCS : tx::Gyro::Mode_Normal);
	
	// we use a knob to set the gain
	int8_t gain = map(analogRead(a0), 0, 1024, 0, 100);
	
	// get the normalized channel value corresponding to the mode and gain
	int16_t chGyro = g_gyro.apply(gain);
}
