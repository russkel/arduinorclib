/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ppm_example.pde
** Demonstrate Pulse Position Modulation functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <PPM.h>


#define CHANNELS 4

uint8_t  g_pins[CHANNELS] = {a0, a1, a2, a3}; // Input pins
int16_t  g_input[CHANNELS]; // normalized input buffer (range [-256 - 256]
uint16_t g_work[CHANNELS + ((CHANNELS + 1) * 2)]; // we need to have a buffer of channels + ((channels + 1) * 2) in size

// PPM requires two buffers:
//     Input buffer containing normalized input samples, range [-256 - 256]
//     Work buffer of ((channels + 1) * 2) elements
// This setup removes any limit on the number of channels you want, and makes sure the library doesn't use more
// memory than it really needs, since the client code supplies the buffers.
tx::PPM g_PPM(CHANNELS, g_input, g_work, CHANNELS);

void setup()
{
	for (uint8_t i = 0;  i < CHANNELS; ++i)
	{
		// set up input pins
		pinMode(g_pins[i], INPUT);
		
		// fill input buffer, convert raw values to normalized ones
		g_input[i] = map(analogRead(g_pins[i]), 0, 1024, -256, 256);
	}
	
	// initialize PPM with some settings
	g_PPM.setPulseLength(448);
	g_PPM.setPauseLength(10448);
	g_PPM.setCenter(1520);
	g_PPM.setTravel(600);
	
	// start PPM, use pin 9 (use false to use pin 10 as output)
	g_PPM.start(true);
}

void loop()
{
	// update the input buffer
	for (uint8_t i = 0;  i < CHANNELS; ++i)
	{
		g_input[i] = map(analogRead(g_pins[i]), 0, 1024, -256, 256);
	}
	
	// tell PPM there are new values available in the input buffer
	g_PPM.update();
}
