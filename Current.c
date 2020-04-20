#include <stdio.h>
#include "Modes.h"
#include "PB_LCD_Drivers.h"
#include "LED_Driver.h"
#include "ADC_Driver.h"
#include "Button_Driver.h"
#include "Util.h"

void switchToCurrent(struct State* state) {
	state->currentMode = Current;
	PB_LCD_GoToXY(0,0);
	PB_LCD_WriteString("Current   ", 11);
	
	LED_Turn_On(3);
	LED_Turn_Off(2);
	LED_Turn_Off(4);
	
	// Reset averaging
	for (int i = 0; i < AVERAGE_READINGS; i++) {
		state->readings[i] = 0;
	}
	state->readingsIndex = 0;
}

void updateCurrent(struct State* state) {
	// Take a reading and add it to the averaging list
	state->readings[state->readingsIndex] = ADC_Read();
	state->readingsIndex = (state->readingsIndex + 1) % AVERAGE_READINGS;
	
	// Get the averaged value and scale it to the range
	//float current = scale(averageReading(), 0, ADC_MAX, CURRENT_MIN, CURRENT_MAX);
	float current = scale(ADC_Read(), 0, ADC_MAX, CURRENT_MIN, CURRENT_MAX);
	
	// Display the current
	PB_LCD_GoToXY(0, 1);
	char text [7];
	snprintf(text, 7, "%.3fA", current);
	PB_LCD_WriteString(text, 7);
	
	// Check if we should switch modes
	if (Button_Press_Debounced(2)) {
		switchToVoltage(state);
	} else if (Button_Press_Debounced(4)) {
		switchToResistance(state);
	}
}
