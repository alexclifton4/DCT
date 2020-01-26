#include "STM32F407xx.h"
#include "Board_LED.h"
#include "PB_LCD_Drivers.h"
#include "MB_Button_Driver.h"
#include <stdio.h>

uint32_t LEDState = 0;

void SysTick_Handler (void) {
	LEDState = 1 - LEDState;
}

int main(void){
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/2);
	LED_Initialize();
	MB_Button_Init();
	
	PB_LCD_Init();
	PB_LCD_Clear();
	PB_LCD_WriteString("Hello, World!", 16);
	
	while(1) {
		if (LEDState) LED_On(0);
		else LED_Off(0);
		
		PB_LCD_GoToXY(0,1);
		
		char text [16];
		snprintf(text, 16, "Press: %d", MB_Button_Press());
		PB_LCD_WriteString(text, 16);
	}
}