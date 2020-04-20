#include "Util.h"

// Scale a number from one range to another
float scale(float value, float fromLow, float fromHigh, float toLow, float toHigh) {
	return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}

// Average the values in the readings array
float averageReading(struct State* state) {
	float total = 0;
	for (int i = 0; i < AVERAGE_READINGS; i++) {
		total += state->readings[i];
	}
	return total / AVERAGE_READINGS;
}
