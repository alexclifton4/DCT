#include "LED_Driver.h"

// Initialise the pins for the buttons
void LED_Init() {
	// Enable the clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    
	// Set PD8 - 15 to 01, while leaving other bits the same
	GPIOD->MODER = (GPIOD->MODER & 0x0000FFFF) | 0x55550000;
}

void LED_Turn_On(int led){
	// The LED's GPIO pin number is six greater than the LED number
	GPIOD->BSRR |= 1 << (led + 6);
}

void LED_Turn_Off(int led) {
	// The last 2 bytes of the BSRR register are for turning GPIO pins off
	GPIOD->BSRR |= (1 << (led + 6)) << 16;
}
