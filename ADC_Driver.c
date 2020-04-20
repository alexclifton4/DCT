#include "ADC_Driver.h"

// Initialise the pins for the buttons
void ADC_Init() {
	// Enable GPIO
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	GPIOC->MODER = 3 << 8; // Set 
	
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	ADC1->SQR3 = 14;
	ADC1->CR2 |= ADC_CR2_ADON;
	ADC1->CR1 |= ADC_CR1_DISCEN;
	ADC1->CR2 |= ADC_CR2_EOCS;
}

// Read a value from the ADC
int ADC_Read() {
	// Start a conversion
	ADC1->CR2 |= ADC_CR2_SWSTART;
	// Wait for the conversion
	while (!(ADC1->SR & ADC_SR_EOC)) {}
	
	return ADC1->DR;
}
