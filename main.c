#include <stdio.h>
#include "STM32F407xx.h"
#include "main.h"
#include "util.h"

#include "PB_LCD_Drivers.h"
#include "Button_Driver.h"
#include "LED_Driver.h"
#include "ADC_Driver.h"

#include "Modes.h"

struct State state;

// Interrupt happens once per second
void SysTick_Handler (void) {
	// Do something depending on the current mode
	switch (state.currentMode) {
		case Frequency:
			tickFrequency(&state);
			break;
		case Capacitance:
			tickCapacitance(&state);
			break;
        default:
            // Don't do anything for other modes
            break;
	}
}

///////////////////
// Main Function //
///////////////////
int main(void){
	// Initialise the board
	SystemCoreClockUpdate();
	// Setup SysTick to interrupt once per second
	SysTick_Config(SystemCoreClock);
	
	// Initialise buttons, LEDs and ADC
	Button_Init();
	LED_Init();
	ADC_Init();
	
	// Initialise the LCD display
	PB_LCD_Init();
	PB_LCD_Clear();
	
	// Start in Voltage mode
	state.offset = 0;
	state.showLive = 1;
	switchToVoltage(&state);
	
	///////////////////////
	// Main program loop //
	///////////////////////
	while(1) {
		// Do something depending on the current mode
		switch (state.currentMode) {
			case Voltage:
				updateVoltage(&state);
				break;
			case Current:
				updateCurrent(&state);
				break;
			case Resistance:
				updateResistance(&state);
				break;
			case Capacitance:
				// Capacitance measures the frequency and then performs a calculation
				// Therefore, it does not need it's own update method
				/* FALL THROUGH */
			case Frequency:
				updateFrequency(&state);
				break;
		}
		
		// Check if show live button is pressed
		if (Button_Press_Debounced(8)) {
			state.showLive = 1 - state.showLive;
			// Clear averaging
			for (int i = 0; i < AVERAGE_READINGS; i++) {
				state.readings[i] = 0;
			}
			state.readingsIndex = 0;
			
			// If not show live, put on the LED
			if (state.showLive == 0) {
				LED_Turn_On(8);
			} else {
				LED_Turn_Off(8);
			}
		}
			
		// Check if we should switch modes
		if (Button_Press_Debounced(2)) {
			switchToVoltage(&state);
		} else if (Button_Press_Debounced(3)) {
			switchToCurrent(&state);
		} else if (Button_Press_Debounced(4)) {
			switchToResistance(&state);
		} else if (Button_Press_Debounced(5)) {
			switchToCapacitance(&state);
		} else if (Button_Press_Debounced(6)) {
			switchToFrequency(&state);
		}
	}
}
