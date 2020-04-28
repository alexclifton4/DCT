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

	// Reset averaging
	for (int i = 0; i < AVERAGE_READINGS; i++) {
		state->readings[i] = 0;
	}
	state->readingsIndex = 0;
}

void updateCapacitance(struct State* state) {
	// Take a reading and add it to the averaging list
	state->readings[state->readingsIndex] = ADC_Read();

	// Get the capacitance depending on averaging mode
	float capacitance;
	if (state->showLive) {
		// Get the averaged value and scale it to the range
		capacitance = scale(averageReading(state), ADC_MIN, ADC_MAX, CAPACITANCE_MIN, CAPACITANCE_MAX);
		// Increment the readings index so that the next value goes to the next position in the array
		state->readingsIndex = (state->readingsIndex + 1) % AVERAGE_READINGS;

	}
	else {
		// Not in live mode so update display after a while
		if (state->readingsIndex > AVERAGE_READINGS) {
			state->mostRecentAverage = averageReading(state);
			state->readingsIndex = 0;
		}
		// Get the most recent value and scale to range
		capacitance = scale(state->mostRecentAverage, ADC_MIN, ADC_MAX, CAPACITANCE_MIN, CAPACITANCE_MAX);
		state->readingsIndex++;
	}

	// Display the capacitance
	PB_LCD_GoToXY(0, 0);
	char text[16];
	snprintf(text, 16, "Capacitance: %.3fuF", capacitance - state->offset); // The offset is subtracted from the value
	PB_LCD_WriteString(text, 16);

	// Display a graphic
	// Work out how many lines to draw
	int lines = fabs((capacitance / CAPACITANCE_MAX * 16));

	// Add the correct no. of lines
	char bottomLine[16] = "";
	for (int i = 0; i < lines; i++) {
		if (capacitance > 0) {
			// Use vertical line
			strcat(bottomLine, "|");
		}
		else {
			// Use horizontal line
			strcat(bottomLine, "-");
		}
	}
	snprintf(bottomLine, 16, "%-16s", bottomLine);
	// Display the lines
	PB_LCD_GoToXY(0, 1);
	PB_LCD_WriteString(bottomLine, 16);

	// Check if calibration button is pressed
	if (Button_Press_Debounced(9)) {
		// Read the current value and store as offset
		state->offset = 5 - capacitance;
	}
}
