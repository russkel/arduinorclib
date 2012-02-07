#include <Expo.h>

namespace tx
{

enum
{
	EXPO_POINTS = 15 //!< number of points to interpolate over, not including 0 and 1
};

// Pre-calculated expo points based on x^3 and x^(1/3)
static const uint8_t s_expoPos[EXPO_POINTS] = {0, 1, 2, 4, 8, 14, 21, 32, 46, 63, 83, 108, 137, 171, 210};
static const uint8_t s_expoNeg[EXPO_POINTS] = {101, 128, 147, 161, 174, 185, 194, 203, 211, 219, 226, 232, 239, 245, 251};

// Public functions

Expo::Expo()
{
	
}


int16_t Expo::apply(int16_t p_value, int8_t p_expo) const
{
	if (p_expo == 0)
	{
		// early abort
		return p_value;
	}
	
	// select the expo array
	const uint8_t* exparr = p_expo > 0 ? s_expoPos : s_expoNeg;
	if (p_expo < 0)
	{
		// ABS
		p_expo = -p_expo;
	}
	
	// save sign
	int16_t neg = p_value < 0 ? 1 : 0;
	if (neg)
	{
		p_value = -p_value;
	}
	
	uint8_t index = p_value >> 4;   // divide by EXPO_POINTS + 1
	uint8_t rem   = p_value & 0x0F; // remainder of divide by EXPO_POINTS + 1
	
	// linear interpolation on array values
	uint16_t lowval = static_cast<uint16_t>(index == 0 ? 0 : (index > EXPO_POINTS ? 256 : exparr[index - 1]));
	++index;
	uint16_t highval = static_cast<uint16_t>(index == 0 ? 0 : (index > EXPO_POINTS ? 256 : exparr[index - 1]));
	
	lowval  = lowval * ((EXPO_POINTS + 1) - rem);
	highval = highval * rem;
	
	uint16_t expoval = (lowval + highval) >> 4; // divide by EXPO_POINTS + 1
	
	// get weighted average between linear and expo value
	uint16_t out = ((p_value * (100 - p_expo)) + (expoval * p_expo)) / 100;
	
	return neg ? -out : out;
}


// Define global instance
Expo g_Expo = Expo();


// namespace end
}
