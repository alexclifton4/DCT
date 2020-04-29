#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Modes.h"
#include "PB_LCD_Drivers.h"
#include "LED_Driver.h"
#include "ADC_Driver.h"
#include "Button_Driver.h"
#include "Util.h"

void switchToCapacitance(struct State* state) {
	state->currentMode = Capacitance;

	LED_Turn_On(5);
	LED_Turn_Off(2);
	LED_Turn_Off(3);
	LED_Turn_Off(4);
	LED_Turn_Off(6);

	state->lastFrequencyReading = 0;
	state->lastFrequencyChange = 0;
}

void tickCapacitance(struct State* state) {
	// One second has been reached
	// The board records all maxima and minima over a second, so the frequency is half of this
	int frequency = state->frequencyCounter / 2;

	// Calculate frequency using following formula:
	//		C = 1 / (4PI^2 x 110 x 10^-6 x f^2)
	// or	C = 1 / (0.00434 x f^2)
	// The capacitance here is in micro Farads
	float capacitance = 1 / (0.00434 * frequency * frequency) * 1000;

	// Display the capacitance
	PB_LCD_GoToXY(0, 0);
	char text[16];
	snprintf(text, 16, "Cap.: %.5fuF", capacitance);
	PB_LCD_WriteString(text, 16);

	// Reset the counter
	state->frequencyCounter = 0;
}