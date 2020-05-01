#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Modes.h"
#include "PB_LCD_Drivers.h"
#include "LED_Driver.h"
#include "ADC_Driver.h"
#include "Button_Driver.h"
#include "Util.h"

void switchToFrequency(struct State* state) {
	state->currentMode = Frequency;
	
	LED_Turn_On(6);
	LED_Turn_Off(2);
	LED_Turn_Off(3);
	LED_Turn_Off(4);
	LED_Turn_Off(5);

	state->lastFrequencyReading = 0;
	state->lastFrequencyChange = 0;
}

void updateFrequency(struct State* state) {
	// Read the voltage
	int reading = ADC_Read();

	// Compare to the last reading
	int readingChange;
	if (reading > state->lastFrequencyReading) {
		// Has gone up
		readingChange = 1;
	}
	else {
		// Has gone down
		readingChange = -1;
	}

	// If the change has changed since last time, there has been a min or max
	if (readingChange != state->lastFrequencyChange) {
		// Increment the frequency counter
		state->frequencyCounter++;
	}

	// Set previous values
	state->lastFrequencyReading = reading;
	state->lastFrequencyChange = readingChange;
}

void tickFrequency(struct State* state) {
	// One second has been reached
	// The board records all maxima and minima over a second, so the frequency is half of this
	int frequency = state->frequencyCounter / 2;

	// Display the frequency
	PB_LCD_GoToXY(0, 0);
	char text[16];
	snprintf(text, 16, "Freq: %dHz", frequency);
	PB_LCD_WriteString(text, 16);

	// Reset the counter
	state->frequencyCounter = 0;
}
