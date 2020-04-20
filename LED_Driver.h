#ifndef __LED_DRIVER_H
#define __LED_DRIVER_H

#include "stm32f407xx.h"

void LED_Init(void);
void LED_Turn_On(int led);
void LED_Turn_Off(int led);

#endif
