#include "Button_Driver.h"

// Holds the current state of the buttons
int buttonStates[7] = {0};

// Initialise the pins for the buttons
void Button_Init() {
	// Enable the clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
    
	// Set PE8 - 15 to 0, while leaving other bits the same
	GPIOE->MODER &= 0x0000FFFF;
}

// Returns 1 if the specified button is down
int Button_Down(int sw) {
	return (GPIOE->IDR & 1<<(sw+6)) > 0;
}

// Returns 1 if the specified button went down since the last call
int Button_Press_Debounced(int sw) {
	// The button has just been pressed if it wasn't down last time but is now
	int pressed = !buttonStates[sw] && Button_Down(sw);
	
	// Update the button state
	buttonStates[sw] = Button_Down(sw);
	
	return pressed;
}
