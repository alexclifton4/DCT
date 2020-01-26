#include "MB_Button_Driver.h"

// Initialise the pins for the buttons
void MB_Button_Init() {
  // Enable the clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
    
	// Set PE8 - 15 to 0, while leaving other bits the same
	GPIOE->MODER &= 0x0000FFFF;

}

int MB_Button_Press() {
	return (GPIOE->IDR & (1<<8)) > 0;
}