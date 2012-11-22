/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** inputswitch_example.pde
** Demonstrate input switch functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <AIPin.h>
#include <InputSwitch.h>

// We create an AIPin on analog pin A0 as a source
rc::AIPin g_pin(A0, rc::Input_AIL);

// Create an InputSwitch which takes aileron input and writes as a switch
// The last parameter indicates whether it's a two (false) or three (true) position switch
rc::InputSwitch g_switch(rc::Input_AIL, rc::Switch_A, false);

void setup()
{
	g_switch.setUpMark(-128); // all values >= -128 are considered "Up"
	// in case of a tri state switch we can also specify a value for center position
}

void loop()
{
	g_pin.read(); // update the source pin
	rc::SwitchState state = g_switch.read(); // update the switch
	
	// you can also get the switch state like this:
	state = rc::getSwitchState(rc::Switch_A);
}
